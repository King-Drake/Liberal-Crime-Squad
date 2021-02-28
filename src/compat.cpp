//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//Copyright (c) 2004 by Kevin Sadler                                                    //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//This file is part of Liberal Crime Squad.                                             //
//                                                                                      //
//    Liberal Crime Squad is free software; you can redistribute it and/or modify       //
//    it under the terms of the GNU General Public License as published by              //
//    the Free Software Foundation; either version 2 of the License, or                 //
//    (at your option) any later version.                                               //
//                                                                                      //
//    Liberal Crime Squad is distributed in the hope that it will be useful,            //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of                    //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                     //
//    GNU General Public License for more details.                                      //
//                                                                                      //
//    You should have received a copy of the GNU General Public License                 //
//    along with Liberal Crime Squad; if not, write to the Free Software                //
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA         //
//////////////////////////////////////////////////////////////////////////////////////////
/**
* compat.cpp
*
* Compatibility Functions to support ports to non-Windows Platforms
*
* Liberal Crime Squad
*
* Abstract
*
* Portability Functions
*
* These functions are intended to replace explicit calls to Windows API.
*/
#include "includes53.h"
#include "constStringcompat.h"
#include "../cursesAlternative.h"

/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
// Re-seed the Random Number Generator every time it's called
extern bool MORERANDOM;
extern unsigned long seed[RNG_SIZE];

int ptime = GetTickCount();
void alarmset(int t)
{
	ptime = GetTickCount() + t;
}
void alarmwait()
{
	while (ptime > (int)GetTickCount());
}
void pause_ms(int t)
{
	alarmset(t);
	refreshAlt();
	alarmwait();
}
// FNV-1a 32-bit hash function (fast and effective) -- helper function for getSeed()
void fnvHash(unsigned long &fnv_hash, unsigned long num)
{
	fnv_hash *= 16777619UL; // multiply by the FNV-1a hash's 32-bit prime
	fnv_hash &= 0xffffffffUL; // keep the number 32-bit (we could be on a 64-bit system)
	fnv_hash ^= (num & 0xffUL); // xor together with number's 1st byte
	num >>= 8; // right shift number to 2nd byte
	fnv_hash *= 16777619UL; // multiply by the FNV-1a hash's 32-bit prime
	fnv_hash &= 0xffffffffUL; // keep the number 32-bit (we could be on a 64-bit system)
	fnv_hash ^= (num & 0xffUL); // xor together with number's 2nd byte
	num >>= 8; // right shift number to 3rd byte
	fnv_hash *= 16777619UL; // multiply by the FNV-1a hash's 32-bit prime
	fnv_hash &= 0xffffffffUL; // keep the number 32-bit (we could be on a 64-bit system)
	fnv_hash ^= (num & 0xffUL); // xor together with number's 3rd byte
	num >>= 8; // right shift number to 4th byte
	fnv_hash *= 16777619UL; // multiply by the FNV-1a hash's 32-bit prime
	fnv_hash &= 0xffffffffUL; // keep the number 32-bit (we could be on a 64-bit system)
	fnv_hash ^= (num & 0xffUL); // xor together with number's 4th byte
}
// A high-quality RNG seed with multiple sources of entropy hashed together with FNV-1a hash
unsigned long getSeed()
{
	unsigned long _seed = 2166136261UL; // start out at the FNV-1a hash's 32-bit offset basis
// We're on Windows and can use the Win32 API as entropy sources
	fnvHash(_seed, GetTickCount()); /* ms since system boot */
	fnvHash(_seed, GetCurrentProcessId()); /* process ID for current process */
	SYSTEM_INFO info; /* a whole bunch of system info */
	GetSystemInfo(&info); /* get the system info */
	fnvHash(_seed, (unsigned long)info.lpMinimumApplicationAddress); /* pointer to minimum accessible memory location */
	fnvHash(_seed, (unsigned long)info.lpMaximumApplicationAddress); /* pointer to maximum accessible memory location */

	return _seed;
}
// Return a random number from 1 to 0xffffffff (any 32-bit integer except 0), using all of seed[].
// This is a 32-bit version of George Marsaglia's xorshift pseudorandom number generator with 128-bit state space.
// 32-bit xorshift RNGs produce values in the range from 1 to 0xffffffff (any 32-bit integer except 0),
// and don't allow the values to be zero... if they do return zero they've been improperly initialized,
// and would continue to output nothing but zeros forever unless the problem is rectified.
// So there's a recovery mechanism in place in case it's about to return a zero value, to fix that.
// It's a nice ultrafast 32-bit pseudorandom number generator with good randomness properties, small state space, and very short code.
unsigned long r_num()
{
	while (true) // this loop is in case of error, so the recovery mechanism can work... it'll exit with a return value upon success
	{
		unsigned long t = seed[0] ^ ((seed[0] << 11) & 0xffffffff); // set temp variable and keep it within 32 bits
		if (MORERANDOM) {
			t ^= getSeed(); // add entropy
		}// MORERANDOM
		seed[0] = seed[1]; seed[1] = seed[2]; seed[2] = seed[3]; // shift variables
		seed[3] = seed[3] ^ (seed[3] >> 19) ^ t ^ (t >> 8); // calculate random number
		if (seed[3]) return seed[3]; // return a number unless it's zero, in which case it was initialized wrong
		initMainRNG(); // recovery mechanism in case things were badly initialized
	}
}
// Picks a random number from 0 to max-1
long LCSrandom(long max)
{  // This expects r_num() to return a random number between 1 and 0xffffffff (any 32-bit integer except 0)... which it does
	return (long)(max*(((long double)(r_num() - 1)) / ((long double)0xffffffffUL)));
}
// Returns a random number from 0 to 0xffffffff (any 32-bit integer), only using seed[0].
// This is a linear congruential generator using parameters suggested in a paper by Pierre L'Ecuyer
// that has better randomness characteristics than most linear congruential generators (the simplest type of RNG).
// No linear congruential generators is very random though, so this is just used to help initialize the xorshift RNG.
unsigned long r_num2()
{
	return seed[0] = (seed[0] * 32310901UL + 433494437UL) & 0xffffffff; // return a random number, kept within 32 bits
}
// Initializes the xorshift Random Number Generator with help getSeed() and r_num2()
void initMainRNG()
{
	// we got 4 integers to initialize, which we'll get from a well-seeded linear congruential generator
	seed[0] = getSeed(); // seed the linear congruential generator
	for (int i = RNG_SIZE - 1; i >= 0; i--) seed[i] = r_num2(); // initialize all the integers
}
// Copies a xorshift Random Number Generator from src to dest
void copyRNG(unsigned long(&dest)[RNG_SIZE], unsigned long(&src)[RNG_SIZE])
{
	for (int i = 0; i < RNG_SIZE; i++) dest[i] = src[i]; // copy all the integers
}
// Sets up another xorshift Random Number Generator whose state space is passed as an argument
void initOtherRNG(unsigned long(&rng)[RNG_SIZE])
{
	r_num(); // randomize main xorshift RNG beforehand
	copyRNG(rng, seed); // copy main xorshift RNG to the one we're setting up
	r_num(); // randomize main xorshift RNG afterwards
}
