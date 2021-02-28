




/*
	File created by Chris Johnson.
	These were previously all in game.cpp.

	This file includes all the the enums, defines, and included headers required globally by all components.

	All code released under GNU GPL.
*/
#include <windows.h>
#include <vector>
#include <map>
#include <deque>
#include "cmarkup/Markup.h"
using namespace std;

/* Determine size of vectors and any other container that implements the size() function.
This basically includes all types of containers except for the C++11 std::forward_list. */
template <class Container> inline long len(const Container& x)
{
	return x.size();
}
/* Determine array size in pickrandom() and various functions throughout the code.
Only works on actual arrays, not on vectors or other containers. */
template <typename T, size_t N> inline long len(const T(&x)[N])
{
	return N;
}
/* Override of the prior function for null-terminated C-strings as char arrays.
This override allows pickrandom() to pick a random character from a C-string we have as a char array. */
template <size_t N> inline long len(const char(&x)[N])
{
	return strlen(x);
}
/* Override of the prior function for null-terminated C-strings as char pointers.
This override allows pickrandom() to pick a random character from a C-string we have as a char pointer. */
inline long len(const char* x)
{
	return strlen(x);
}
/* Override for when it doesn't work with const in front of the char*
(compilers are weird about template function overrides) */
inline long len(char* x)
{
	return strlen(x);
}
enum LCSIO_FLAGS
{
	LCSIO_PRE_ART = 1, /// Append the given file name to the art directory path.
	LCSIO_PRE_HOME = 2 /// Append the given file name to the home directory path.
};
#include <iostream>
bool LCSOpenFileCPP(std::string filename, std::ios_base::openmode mode, int flags, std::fstream &file);
#define CH_USE_CP437


// initfile.cpp

#include "../common/stringconversion.h"
//for int stringtobool(std::string boolstr);
//#include "../common/consolesupport.h"
// for void begin_cleartype_fix();
#include "../title/titlescreen.h"
extern short interface_pgup;
extern short interface_pgdn;
extern bool fixcleartype;
const string CONST_INIT_TXT = "init.txt";

const string tag_fixcleartype = "fixcleartype";
const string tag_autosave = "autosave";
const string tag_page = "page";
const string tag_brackets = "brackets";
const string tag_azerty = "azerty";
const string tag_pagekeys = "pagekeys";
//#endif//INITFILE_CPP
//#endif// INCLUDES_H_INCLUDED
