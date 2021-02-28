


/*
Copyright (c) 2002,2003,2004 by Tarn Adams                                            //
//
This file is part of Liberal Crime Squad.                                             //
//
Liberal Crime Squad is free software; you can redistribute it and/or modify     //
it under the terms of the GNU General Public License as published by            //
the Free Software Foundation; either version 2 of the License, or               //
(at your option) any later version.                                             //
//
Liberal Crime Squad is distributed in the hope that it will be useful,          //
but WITHOUT ANY WARRANTY; without even the implied warranty of                  //
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the                  //
GNU General Public License for more details.                                    //
//
You should have received a copy of the GNU General Public License               //
along with Liberal Crime Squad; if not, write to the Free Software              //
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   02111-1307   USA     //
*/
/*
This file was created by Chris Johnson (grundee@users.sourceforge.net)
by copying code from game.cpp.
To see descriptions of files and functions, see the list at
the bottom of includes.h in the top src folder.
*/
// Note: this file is encoded in the PC-8 / Code Page 437 / OEM-US character set
// (The same character set used by Liberal Crime Squad when it is running)
// Certain special characters won't display correctly unless your text editor is
// set to use that character set, such as this e with an accent: é
// In Windows Notepad with the Terminal font, OEM/DOS encoding it should work fine.
// You can set this in Notepad by going to Format->Font and choosing the Terminal font,
// then choosing OEM/DOS in the Script dropdown box.
// In Notepad++ go to the Encoding menu, Character sets, Western European, OEM-US... easy!
// In Code::Blocks's editor go to Settings->Editor->the Other Settings tab and
// then pick WINDOWS-437 from the dropdown box and then choose the radio button
// to make this the default encoding and disable auto-detection of the encoding.
// Then close the file and reopen it (since Code::Blocks detects the encoding
// when it opens the file and it can't be changed after that; what we changed was
// how it detects encoding for files it opens in the future, not files already open).
// In Microsoft Visual C++, right-click the file in the Solution Explorer,
// In MS-DOS Editor (included with Windows as EDIT.COM in your system32 directory),
// the codepage will be correct already since it's running in a console window just
// like Liberal Crime Squad. Well OK, the encoding might be wrong, but then it's wrong
// in Liberal Crime Squad TOO, and to fix it, go to Control Panel, Regional and Language Settings,
// Advanced tab, and choose English (United States) from the dropdown box as the encoding
// for non-Unicode applications, then press OK.
// If you have a Linux or other UNIX-based system you are obviously smart enough
// to figure out for yourself how to open a file in OEM-US PC-8 codepage 437 in
// your favorite text editor. If you're on Mac OS X, well that's UNIX-based, figure
// it out for yourself.
#include "../includes40.h"
#include "../constStringsiege.h"
#include <algorithm>
void statebrokenlaws(int loc)
{
	music.play(MUSIC_SIEGE);
	short breakercount[LAWFLAGNUM] = { 0 };
	int typenum = 0, criminalcount = 0, kidnapped = 0;
	string kname;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive || pool[p]->location != loc) continue;
		if (pool[p]->flag&CREATUREFLAG_KIDNAPPED)
		{
			kname = pool[p]->propername;
			kidnapped++;
		}
		if (iscriminal(pool[p]->getCreatureJustice())) criminalcount++;
		CreatureJustice cr_just = pool[p]->getCreatureJustice();
		for (int i = 0; i < LAWFLAGNUM; i++) if (cr_just.crimes_suspected[i]) breakercount[i]++;
	}
	for (int i = 0; i < LAWFLAGNUM; i++) if (breakercount[i]) typenum++;
	printBrokenLawsHeader(LocationsPool::getInstance().isThisUnderAttack(loc), LocationsPool::getInstance().getSiegeEscalationState(loc));
	//KIDNAP VICTIM
	if (kidnapped)
	{
		printReleaseKidnapped(kname, kidnapped);
	}
	//TREASON
	else if (breakercount[LAWFLAG_TREASON])
		printSpecificCrime(LAWFLAG_TREASON);
	//TERRORISM
	else if (breakercount[LAWFLAG_TERRORISM])
		printSpecificCrime(LAWFLAG_TERRORISM);
	//MURDERER
	else if (breakercount[LAWFLAG_MURDER])
		printSpecificCrime(LAWFLAG_MURDER);
	//KIDNAPPER
	else if (breakercount[LAWFLAG_KIDNAPPING])
		printSpecificCrime(LAWFLAG_KIDNAPPING);
	//BANK ROBBER
	else if (breakercount[LAWFLAG_BANKROBBERY])
		printSpecificCrime(LAWFLAG_BANKROBBERY);
	//ARSONIST
	else if (breakercount[LAWFLAG_ARSON])
		printSpecificCrime(LAWFLAG_ARSON);
	//BURN FLAG
	else if (breakercount[LAWFLAG_BURNFLAG])
	{
		printBurnedFlag(lawList[LAW_FLAGBURNING]);
	}
	//SPEECH
	else if (breakercount[LAWFLAG_SPEECH])
		printSpecificCrime(LAWFLAG_SPEECH);
	//BROWNIES
	else if (breakercount[LAWFLAG_BROWNIES])
		printSpecificCrime(LAWFLAG_BROWNIES);
	//ESCAPED
	else if (breakercount[LAWFLAG_ESCAPED])
		printSpecificCrime(LAWFLAG_ESCAPED);
	//HELP ESCAPED
	else if (breakercount[LAWFLAG_HELPESCAPE])
		printSpecificCrime(LAWFLAG_HELPESCAPE);
	//JURY
	else if (breakercount[LAWFLAG_JURY])
		printSpecificCrime(LAWFLAG_JURY);
	//RACKETEERING
	else if (breakercount[LAWFLAG_RACKETEERING])
		printSpecificCrime(LAWFLAG_RACKETEERING);
	//EXTORTION
	else if (breakercount[LAWFLAG_EXTORTION])
		printSpecificCrime(LAWFLAG_EXTORTION);
	//ASSAULT
	else if (breakercount[LAWFLAG_ARMEDASSAULT])
		printSpecificCrime(LAWFLAG_ARMEDASSAULT);
	//ASSAULT
	else if (breakercount[LAWFLAG_ASSAULT])
		printSpecificCrime(LAWFLAG_ASSAULT);
	//CAR THEFT
	else if (breakercount[LAWFLAG_CARTHEFT])
		printSpecificCrime(LAWFLAG_CARTHEFT);
	//CC FRAUD
	else if (breakercount[LAWFLAG_CCFRAUD])
		printSpecificCrime(LAWFLAG_CCFRAUD);
	//THIEF
	else if (breakercount[LAWFLAG_THEFT])
		printSpecificCrime(LAWFLAG_THEFT);
	//PROSTITUTION
	else if (breakercount[LAWFLAG_PROSTITUTION])
		printSpecificCrime(LAWFLAG_PROSTITUTION);
	//HIRE ILLEGAL
	else if (breakercount[LAWFLAG_HIREILLEGAL])
		printHireIllegal(lawList[LAW_IMMIGRATION] < 1);
	//COMMERCE
	else if (breakercount[LAWFLAG_COMMERCE])
		printSpecificCrime(LAWFLAG_COMMERCE);
	//INFORMATION
	else if (breakercount[LAWFLAG_INFORMATION])
		printSpecificCrime(LAWFLAG_INFORMATION);
	//UNLAWFUL BURIAL
	else if (breakercount[LAWFLAG_BURIAL])
		printSpecificCrime(LAWFLAG_BURIAL);
	//BREAKING
	else if (breakercount[LAWFLAG_BREAKING])
		printSpecificCrime(LAWFLAG_BREAKING);
	//VANDALISM
	else if (breakercount[LAWFLAG_VANDALISM])
		printSpecificCrime(LAWFLAG_VANDALISM);
	//RESIST
	else if (breakercount[LAWFLAG_RESIST])
		printSpecificCrime(LAWFLAG_RESIST);
	//DISTURBANCE
	else if (breakercount[LAWFLAG_DISTURBANCE])
		printSpecificCrime(LAWFLAG_DISTURBANCE);
	//PUBLIC NUDITY
	else if (breakercount[LAWFLAG_PUBLICNUDITY])
		printSpecificCrime(LAWFLAG_PUBLICNUDITY);
	//LOITERING
	else if (breakercount[LAWFLAG_LOITERING])
		printSpecificCrime(LAWFLAG_LOITERING);
	//THEY WERE LOOKING FOR SOMEONE ELSE
	else printHarboringFugitive();
	printBrokenLawsFooter(kidnapped, typenum);
	pressAnyKey();
}




void createNewStoryMassacre(const int loc, const int killnumber) {

	Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
	ns->type = NEWSSTORY_MASSACRE;
	ns->loc = loc;
	ns->crime.push_back(LocationsPool::getInstance().getSiegeType(loc));
	ns->crime.push_back(killnumber);
	newsstory.push_back(ns);
}

void createNewStoryFieldAttack(const int loc) {
	Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
	if (LocationsPool::getInstance().isThisUnderAttack(loc)) ns->type = NEWSSTORY_SQUAD_FLEDATTACK;
	else ns->type = NEWSSTORY_SQUAD_ESCAPED;
	ns->positive = 1;
	ns->loc = loc;
	ns->siegetype = LocationsPool::getInstance().getSiegeType(loc);
	newsstory.push_back(ns);
}

/* TODO
make it less likely to be raided based on:
- the number of sleepers.
- how effective said sleepers are.
- what action each sleeper is doing (promoting liberalism decreases chance while promoting conservatism increases chance)
- what the sleeper does for a living (police officers are more influential than janitors, for instance)
make it more likely to be raided:
- when a liberal hacks or steals credit cards.
- dead bodies in the base. [DONE]
*/
/* siege - gives up on sieges with empty locations */
/* Work in progress. It works, but needs to be called in more places. */
/* Currently, it only works when you confront a siege and then fail. */
/* siege - handles giving up */

void surrenderToAuthorities(const int loc) {


	music.play(MUSIC_SIEGE);
	int polsta = find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION, loc);
	//END SIEGE
	printTheyConfiscateEverything(LocationsPool::getInstance().getSiegeType(loc), LocationsPool::getInstance().getSiegeEscalationState(loc));
	int kcount = 0, pcount = 0, icount = 0;
	string kname;
	string pname;
	string pcname;
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != loc || !pool[p]->getNameAndAlignment().alive) continue;
		if (pool[p]->flag&CREATUREFLAG_ILLEGALALIEN) icount++;
		if (pool[p]->flag&CREATUREFLAG_MISSING&&pool[p]->getNameAndAlignment().align == -1)
		{
			kcount++;
			kname = pool[p]->propername;
			if (pool[p]->getNameAndAlignment().type == CREATURE_RADIOPERSONALITY) offended_amradio = 1;
			if (pool[p]->getNameAndAlignment().type == CREATURE_NEWSANCHOR) offended_cablenews = 1;
			//clear InterrogationST data if deleted
			delete pool[p]->activity.intr();
		}
	}
	//CRIMINALIZE POOL IF FOUND WITH KIDNAP VICTIM OR ALIEN
	if (kcount) criminalizepool(LAWFLAG_KIDNAPPING, -1, loc);
	if (icount) criminalizepool(LAWFLAG_HIREILLEGAL, -1, loc);
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_FIREMEN && hasPrintingPress(loc))
		criminalizepool(LAWFLAG_SPEECH, -1, loc); // Criminalize pool for unacceptable speech
												  //LOOK FOR PRISONERS (MUST BE AFTER CRIMINALIZATION ABOVE)
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != loc || !pool[p]->getNameAndAlignment().alive) continue;
		if (iscriminal(pool[p]->getCreatureJustice()) && !(pool[p]->flag&CREATUREFLAG_MISSING&&pool[p]->getNameAndAlignment().align == -1))
		{
			pcount++;
			pname = pool[p]->propername;
			pcname = pool[p]->getNameAndAlignment().name;
		}
	}
	if (kcount == 1)
	{
		printSingleKidnapFreed(kname);
	}
	if (kcount > 1)
	{
		printKidnapFreed();
	}
	if (pcount == 1)
	{
		printSingleLiberalTaken(pname, pcname);
	}
	if (pcount > 1)
	{
		printLiberalsTakenToPolice(pcount);
	}
	if (ledger.get_funds() > 0)
	{
		if (ledger.get_funds() <= 2000 || LocationsPool::getInstance().getSiegeType(loc) == SIEGE_FIREMEN)
		{
			printFundsIntact();
		}
		else
		{
			int confiscated = LCSrandom(LCSrandom(ledger.get_funds() - 2000) + 1) + 1000;
			if (ledger.get_funds() - confiscated > 50000)
				confiscated += ledger.get_funds() - 30000 - LCSrandom(20000) - confiscated;
			printMoneyConfiscated(confiscated);
			ledger.subtract_funds(confiscated, EXPENSE_CONFISCATED);
		}
	}
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_FIREMEN)
	{
		if (hasPrintingPress(loc))
		{
			printPrintingpressDismantled();
			deletePrintingPress(loc);
		}
	}
	else
	{
		if (LocationsPool::getInstance().get_specific_integer(INT_GETCOMPOUNDWALLS, loc))
		{
			printCompoundDismantled();
			deleteCompoundWalls(loc);
		}
	}
	if (LocationsPool::getInstance().isThisAFront(loc) != -1)
	{
		printBusinessFrontTaken();
		deleteBusinessFront(loc);
	}
	pressAnyKey();
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_FIREMEN)
		offended_firemen = 0; // Firemen do not hold grudges
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != loc) continue;
		//ALL KIDNAP VICTIMS FREED REGARDLESS OF CRIMES
		if ((pool[p]->flag & CREATUREFLAG_MISSING) ||
			!pool[p]->getNameAndAlignment().alive)
		{
			// Clear actions for anybody who was tending to this person
			for (int i = 0; i < CreaturePool::getInstance().lenpool(); i++)
				if (pool[i]->getNameAndAlignment().alive&&pool[i]->activity_type() == ACTIVITY_HOSTAGETENDING && pool[i]->activity.arg == pool[p]->id)
					pool[i]->set_activity_type(ACTIVITY_NONE);
			removesquadinfo(*pool[p]);
			delete_and_remove(pool, p);
			continue;
		}
		//TAKE SQUAD EQUIPMENT
		if (pool[p]->squadid != -1)
		{
			int sq = getsquad(pool[p]->squadid);
			if (sq != -1)delete_and_clear(squad[sq]->loot);
		}
		pool[p]->drop_weapons_and_clips(NULL);
		if (iscriminal(pool[p]->getCreatureJustice()))
		{
			removesquadinfo(*pool[p]);
			pool[p]->location = polsta;
			pool[p]->set_activity_type(ACTIVITY_NONE);
		}
	}
}

void surrenderAndDie(const int loc) {


	//OTHERWISE IT IS SUICIDE
	int killnumber = 0;
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != loc) continue;
		if (pool[p]->getNameAndAlignment().alive&&pool[p]->getNameAndAlignment().align == 1) stat_dead++;
		killnumber++;
		removesquadinfo(*pool[p]);
		pool[p]->die();
		pool[p]->location = -1;
	}
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_CCS && LocationsPool::getInstance().getLocationType(loc) == SITE_INDUSTRY_WAREHOUSE)
		CCSCapturesSite(loc);
	printEveryoneHereIsDead(LocationsPool::getInstance().getLocationName(loc));
	if (!endcheck(-2)) music.play(MUSIC_SIEGE); // play correct music for if we lost the game or didn't lose it
	pressAnyKey();
	createNewStoryMassacre(loc, killnumber);
	//MUST SET cursite TO SATISFY endcheck() CODE
	int tmp = getCurrentSite();
	setCurrentSite(loc);
	endcheck();
	setCurrentSite(tmp);
}
void giveup()
{
	int loc = -1;
	if (selectedsiege != -1)loc = selectedsiege;
	if (activesquad != NULL)loc = activesquad->squad[0]->location;
	if (loc == -1)return;
	if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, loc) > 1)LocationsPool::getInstance().setRenting(loc, RENTING_NOCONTROL);
	//IF POLICE, END SIEGE
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_POLICE ||
		LocationsPool::getInstance().getSiegeType(loc) == SIEGE_FIREMEN)
	{
		surrenderToAuthorities(loc);
		endLocationSiege(loc);
	}
	else
	{
		surrenderAndDie(loc);
		endLocationSiege(loc);
	}
	//CONFISCATE MATERIAL
	deleteLocationLoot(loc);
	deleteLocationVehicles(loc);
	gamelog.newline();
}
void resolvesafehouses()
{
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++)
	{
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, l) >= 0 && LocationsPool::getInstance().isThereASiegeHere(l))
		{
			cleangonesquads();
			selectedsiege = l; // hack for calling giveup()
			giveup();
		}
	}
}

void statebrokenlaws(CreatureJustice cr, const int flag)
{
	bool kidnapped = (flag&CREATUREFLAG_KIDNAPPED);
	bool criminal = false;
	bool breakercount[LAWFLAGNUM];
	for (int i = 0; i < LAWFLAGNUM; i++) {
		if (cr.crimes_suspected[i]) {
			breakercount[i] = true;
			criminal = true;
		}
		else {
			breakercount[i] = false;
		}
	}
	if (!criminal && !kidnapped) return;

	printWantedFor();
	//KIDNAP VICTIM
	if (kidnapped) {
		printRehab();
	}
	else {
		printMostSeriousCrime(breakercount);
	}
}
/* siege - updates upcoming sieges */
int allCreatureHeatGeneration(const int l, int& numpres) {
	int crimes = 0;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		// Sleepers and people not at this base don't count
		if (pool[p]->location != l || pool[p]->flag & CREATUREFLAG_SLEEPER)continue;
		if (!pool[p]->getNameAndAlignment().alive) // Corpses attract attention
		{
			crimes += 5;
			continue;
		}
		if (pool[p]->flag & CREATUREFLAG_KIDNAPPED && pool[p]->align != 1)
		{
			crimes += 5 * pool[p]->joindays; // Kidnapped persons increase heat
			continue;
		}
		if (pool[p]->align != 1)continue; // Non-liberals don't count other than that
		numpres++;
		// Accumulate heat from liberals who have it, but let them bleed it off in the process
		if (pool[p]->heat > 0)
		{
			crimes += pool[p]->heat / (pool[p]->activity_type() == ACTIVITY_NONE ? 60 : 10) + 1;
			pool[p]->heat -= min(pool[p]->activity_type() == ACTIVITY_NONE ? pool[p]->heat / 10 : 5, pool[p]->heat);
		}
	}
	return crimes;
}
void possibleWarningFromSleepers(const int l) {
	int policesleeperwarning = 0;
	for (int pl = 0; pl < CreaturePool::getInstance().lenpool(); pl++)
	{
		if (pool[pl]->flag & CREATUREFLAG_SLEEPER &&
			pool[pl]->location != -1 &&
			LocationsPool::getInstance().getLocationType(pool[pl]->location) == SITE_GOVERNMENT_POLICESTATION &&
			LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, pool[pl]->location) == LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, l))
		{
			//if(pool[pl]->infiltration*100>LCSrandom(50))
			{
				policesleeperwarning = 1;
				break;
			}
		}
	}
	if (policesleeperwarning)
	{
		printPoliceSleeperWarning(LocationsPool::getInstance().getLocationName(l), LocationsPool::getInstance().getSiegeEscalationState(l));
		pressSpecificKey('x', ESC);
	}
}

void policeSiegePrintNonePresent(const int l) {
	printPoliceSiegeEmptyHeader(LocationsPool::getInstance().getLocationName(l));
	pressAnyKey();
	int y = 0;
	vector<string> corpseList;
	vector<string> kidnapList;
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != l) continue;
		if (!pool[p]->getNameAndAlignment().alive)
		{
			printCorpseRecoveredByPolice(pool[p]->getNameAndAlignment().name, y);
			pressAnyKey();
			delete_and_remove(pool, p);
			y++;
			continue;
		}
		if (pool[p]->align != 1)
		{
			printKidnapRecoveredByPolice(pool[p]->getNameAndAlignment().name, y);
			pressAnyKey();
			delete_and_remove(pool, p);
			y++;
			continue;
		}
	}
	gamelog.newline();
	deleteLocationLoot(l);
	deleteLocationVehicles(l);
}

void policeSiegePrintSomePresent(const int l) {

	music.play(MUSIC_SIEGE);
	printPoliceSiegeHeader(LocationsPool::getInstance().getLocationName(l));
	LocationsPool::getInstance().clearunderattack(l);
	pressAnyKey();
	//MENTION ESCALATION STATE
	if (LocationsPool::getInstance().getSiegeEscalationState(l) >= 1)
	{
		printSWATArrival();
		pressAnyKey();
	}
	if (LocationsPool::getInstance().getSiegeEscalationState(l) >= 2)
	{
		printTankArrival(LocationsPool::getInstance().get_specific_integer(INT_DOWEHAVETANKTRAPS, l));
		pressAnyKey();
	}
	if (LocationsPool::getInstance().getSiegeEscalationState(l) >= 3)
	{
		printJetBombers();
		pressAnyKey();
	}
	statebrokenlaws(l);
	policeSiege(l);
}
void policeSiegePrint(const int l, const int numpres) {
	LocationsPool::getInstance().setSiegetimeuntillocated(l, -2);
	LocationsPool::getInstance().clearHeat(l);
	if (numpres > 0)
	{
		policeSiegePrintSomePresent(l);
	}
	else
	{
		policeSiegePrintNonePresent(l);
	}
}

void possiblyWarnOfCorpSiege(const int l) {

	LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CORPORATE, LCSrandom(3) + 1);
	// *JDS* CEO sleepers may give a warning before corp raids
	int ceosleepercount = 0;
	for (int pl = 0; pl < CreaturePool::getInstance().lenpool(); pl++)
	{
		if (pool[pl]->flag & CREATUREFLAG_SLEEPER&&
			pool[pl]->type == CREATURE_CORPORATE_CEO)
		{
			ceosleepercount = 1;
		}
	}
	if (ceosleepercount || !LCSrandom(5))
	{
		printCorpSiegeWarning(ceosleepercount, LocationsPool::getInstance().getLocationName(l));
		pressAnyKey();
	}
}
void printEveryoneInjured(const int l) {
	printEveryoneInjuredHeader();
	vector<pair<string, int> > killList;
	vector<pair<string, int> > injuredList;
	for (int i = 0; i < CreaturePool::getInstance().lenpool(); i++)
	{
		if (pool[i]->location == l)
		{
			if (LCSrandom(2))
			{
				int namelength = len(pool[i]->getNameAndAlignment().name);
				pool[i]->blood -= LCSrandom(101 - pool[i]->juice / 10) + 10;
				if (pool[i]->blood < 0)
				{
					killList.push_back(make_pair(pool[i]->getNameAndAlignment().name, pool[i]->align));
					pool[i]->die();
				}
				else
				{
					injuredList.push_back(make_pair(pool[i]->getNameAndAlignment().name, pool[i]->align));
				}
			}
		}
	}
	printKillList(killList);
	printInjuredList(injuredList);
}
void CCSSiegePrint(const int l, const int numpres) {


	if (LocationsPool::getInstance().get_specific_integer(INT_GETHEAT, l) && LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CCS) == -1 && !LocationsPool::getInstance().isThereASiegeHere(l) && !LCSrandom(60) && numpres > 0)
	{
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CCS, LCSrandom(3) + 1);
		// CCS sleepers may give a warning before raids
		int ccssleepercount = 0;
		for (int pl = 0; pl < CreaturePool::getInstance().lenpool(); pl++)
		{
			if (pool[pl]->flag & CREATUREFLAG_SLEEPER &&
				(pool[pl]->type == CREATURE_CCS_VIGILANTE || pool[pl]->type == CREATURE_CCS_ARCHCONSERVATIVE ||
					pool[pl]->type == CREATURE_CCS_MOLOTOV || pool[pl]->type == CREATURE_CCS_SNIPER))
			{
				ccssleepercount = 1;
				break;
			}
		}
		if (ccssleepercount > 0)
		{
			printCCSSleeperWarning(LocationsPool::getInstance().getLocationName(l));
			pressAnyKey();
		}
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CCS) > 0)LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CCS, LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CCS) - 1); // CCS raid countdown!
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CCS) == 0 && !LocationsPool::getInstance().isThereASiegeHere(l) && numpres > 0)
	{
		music.play(MUSIC_SIEGE);
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CCS, -1);
		// CCS raid!
		printCCSRaid(LocationsPool::getInstance().getLocationName(l));
		pressAnyKey();
		if (!(LocationsPool::getInstance().get_specific_integer(INT_DOWEHAVETANKTRAPS, l)) &&
			!LCSrandom(5))
		{
			// CCS Carbombs safehouse!!
			printCCSCarbomb();
			pressAnyKey();
			printEveryoneInjured(l);
			pressAnyKey();
		}
		else
		{
			// CCS Raids safehouse
			printCCSRaidSafehouse();
			pressAnyKey();
			CCSSiege(l);
		}
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CCS) == 0)LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CCS, -1); // Silently call off foiled ccs raids
}

bool incomingRaidFiremen(const int l) {
	return lawList[LAW_FREESPEECH] == -2 && LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_FIREMEN) == 0;
}

void theFiremenHaveRaidedEmptySafehouse(const int l) {

	LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_FIREMEN, -1);
	printFiremenSiegeEmpty(LocationsPool::getInstance().getLocationName(l));
	pressAnyKey();
	int y = 0;
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != l)continue;
		if (!pool[p]->getNameAndAlignment().alive)
		{

			printCorpseRecovery(y++, pool[p]->getNameAndAlignment().name);
			pressAnyKey();
			delete_and_remove(pool, p);
			continue;
		}
		if (pool[p]->align != 1)
		{
			printKidnapRescue(y++, pool[p]->getNameAndAlignment().name);
			pressAnyKey();
			delete_and_remove(pool, p);
			continue;
		}
	}
	deleteLocationLoot(l);
	printFiremenSiegeEmpty(hasPrintingPress(l), hasBusinessFront(l));
	if (hasPrintingPress(l))
	{
		deletePrintingPress(l);
		offended_firemen = 0;
	}
	if (hasBusinessFront(l))
	{
		deleteBusinessFront(l);
	}
	gamelog.newline();
}

void possiblyWarnOfCIARaid(const int l) {
	int agentsleepercount = 0;
	for (int pl = 0; pl < CreaturePool::getInstance().lenpool(); pl++)
	{
		if (pool[pl]->flag & CREATUREFLAG_SLEEPER&&
			pool[pl]->type == CREATURE_AGENT)
		{
			//if(pool[pl]->infiltration*100>LCSrandom(100))
			{
				agentsleepercount = 1;
				break;
			}
		}
	}
	if (agentsleepercount)
	{
		printCIASiegeWarning(LocationsPool::getInstance().getLocationName(l));
		pressAnyKey();
	}
}

void possiblyWarnOfFiremenSiege(const int l) {

	int firemensleepercount = 0;
	for (int pl = 0; pl < CreaturePool::getInstance().lenpool(); pl++)
		if (pool[pl]->flag & CREATUREFLAG_SLEEPER &&
			pool[pl]->type == CREATURE_FIREFIGHTER &&
			LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, pool[pl]->location) == LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, l))
			firemensleepercount++;
	if (LCSrandom(firemensleepercount + 1) > 0 || !LCSrandom(10))
	{
		printFiremenSiege(firemensleepercount > 0, l);
		pressAnyKey();
	}
}
void huntingSiegePrint(const int l, int& numpres) {


	//HUNTING
	if (getTimeUntilSiege(l) > 0)
	{
		if (LocationsPool::getInstance().isThisAFront(l) == -1 || LCSrandom(2))
		{
			LocationsPool::getInstance().setTimeUntilSiege(l, getTimeUntilSiege(l) - 1);
			// Hunt faster if location is extremely hot
			huntFasterIfSiteIncrediblyHot(l);
		}
	}
	//CHECK FOR CRIMINALS AT THIS BASE
	//int heatprotection=0;
	int crimes = allCreatureHeatGeneration(l, numpres);
	// Determine how effective your current safehouse
	// is at keeping the police confused
	updateLocationHeatProtection(l);
	// Let the place cool off if not accumulating heat
	letPlaceCoolOffUnlessCrime(crimes, l);
	// Sleepers at the police department may give a warning just before police raids
	if (getTimeUntilSiege(l) == 1)
	{
		possibleWarningFromSleepers(l);
	}
	//COPS RAID THIS LOCATION
	if (!getTimeUntilSiege(l))
	{
		policeSiegePrint(l, numpres);
	}
	//OTHER OFFENDABLE ENTITIES
	//CORPS
	if (LocationsPool::getInstance().get_specific_integer(INT_GETHEAT, l) && LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CORPORATE) == -1 && !LocationsPool::getInstance().isThereASiegeHere(l) && offended_corps && !LCSrandom(600) && numpres > 0)
	{
		possiblyWarnOfCorpSiege(l);
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CORPORATE) > 0) {
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CORPORATE, LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CORPORATE) - 1); // Corp raid countdown!
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CORPORATE) == 0 && !LocationsPool::getInstance().isThereASiegeHere(l) && offended_corps&&numpres > 0)
	{
		music.play(MUSIC_SIEGE);
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CORPORATE, -1);
		// Corps raid!
		corporateSiegePrint(LocationsPool::getInstance().getLocationName(l));
		pressAnyKey();
		corporateSiege(l);
		offended_corps = 0;
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CORPORATE) == 0) {
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CORPORATE, -1); // Silently call off foiled corp raids
	}
	//CONSERVATIVE CRIME SQUAD
	bool ccs_active = endgamestate >= ENDGAME_CCS_APPEARANCE && endgamestate < ENDGAME_CCS_DEFEATED;
	bool target_interesting = endgamestate >= ENDGAME_CCS_SIEGES || hasPrintingPress(l);
	if (ccs_active && target_interesting)
	{
		CCSSiegePrint(l, numpres);
	}
	//CIA
	if (LocationsPool::getInstance().get_specific_integer(INT_GETHEAT, l) && LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CIA) == -1 && !LocationsPool::getInstance().isThereASiegeHere(l) && offended_cia && !LCSrandom(300) && numpres > 0)
	{
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CIA, LCSrandom(3) + 1);
		// *JDS* agent sleepers may give a warning before cia raids
		possiblyWarnOfCIARaid(l);
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CIA) > 0)LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CIA, LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CIA) - 1); // CIA raid countdown!
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CIA) == 0 && !LocationsPool::getInstance().isThereASiegeHere(l) && offended_cia&&numpres > 0)
	{
		music.play(MUSIC_SIEGE);
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CIA, -1);
		// CIA raids!
		printCIASiege(LocationsPool::getInstance().getLocationName(l), hasCameras(l), hasAGenerator(l));
		pressAnyKey();
		CIASiege(l);
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_CIA) == 0) {
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_CIA, -1); // Silently call off foiled cia raids
	}
	//HICKS
	if (!LocationsPool::getInstance().isThereASiegeHere(l) && offended_amradio&&attitude[VIEW_AMRADIO] <= 35 && !LCSrandom(600) && numpres > 0)
	{
		music.play(MUSIC_SIEGE);
		printRadioHicksSiege(l);
		pressAnyKey();
		hicksSiege(l);
		offended_amradio = 0;
	}
	if (!LocationsPool::getInstance().isThereASiegeHere(l) && offended_cablenews&&attitude[VIEW_CABLENEWS] <= 35 && !LCSrandom(600) && numpres > 0)
	{
		music.play(MUSIC_SIEGE);
		printCableHicksSiege(l);
		pressAnyKey();
		hicksSiege(l);
		offended_cablenews = 0;
	}
	//Firemen
	if (lawList[LAW_FREESPEECH] == -2 && LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_FIREMEN) == -1 && !LocationsPool::getInstance().isThereASiegeHere(l) &&
		offended_firemen && numpres > 0 && hasPrintingPress(l) && !LCSrandom(90))
	{
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_FIREMEN, LCSrandom(3) + 1);
		// Sleeper Firemen can warn you of an impending raid
		possiblyWarnOfFiremenSiege(l);
	}
	else if (LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_FIREMEN) > 0) LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_FIREMEN, LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_FIREMEN) - 1);
	else if (incomingRaidFiremen(l) && !LocationsPool::getInstance().isThereASiegeHere(l) && numpres > 0)
	{
		music.play(MUSIC_SIEGE);
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_FIREMEN, -1);
		// Firemen raid!
		printFiremenRaid(LocationsPool::getInstance().getLocationName(l));
		pressAnyKey();
		printFiremenRaid2();
		pressAnyKey();
		firemanSiege(l);
		offended_firemen = 0;
	}
	else if (incomingRaidFiremen(l))
	{
		theFiremenHaveRaidedEmptySafehouse(l);
	}
	else if (lawList[LAW_FREESPEECH] <= -1 && LocationsPool::getInstance().getTimeUntilSiege(l, SIEGE_FIREMEN) == 0) {
		LocationsPool::getInstance().setTimeUntilSiege(l, SIEGE_FIREMEN, -1);
		offended_firemen = 0;
	}

}

//TODO There is an absurd amount of duplicated code here
void siegecheck(char canseethings)
{
	if (disbanding)return;
	// Upkeep - even base-less should be considered.
	// XXX - candidate to create nice function?
	// Cleanse record on things that aren't illegal right now
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		pool[p]->clear_no_longer_crimes();
	}
	if (lawList[LAW_FREESPEECH] > -2)offended_firemen = 0;
	//FIRST, THE COPS
	int numpres;
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++)
	{
		if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISSITECLOSED, find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION, l)))
		{
			dropHeatByFivePercent(l);
		}
		if (LocationsPool::getInstance().isThereASiegeHere(l))continue;
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, l) == RENTING_NOCONTROL)continue;
		numpres = 0;
		if (getTimeUntilSiege(l) == -2)
		{
			//IF JUST SIEGED, BUY SOME TIME
			LocationsPool::getInstance().setTimeUntilSiege(l, -1);
		}
		else
		{
			huntingSiegePrint(l, numpres);
		}
	}
}
/* siege - checks how many people are eating at the site */
int numbereating(int loc)
{
	int eaters = 0;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) //Must be here, alive, Liberal, and not a sleeper, to count as an eater
		if (pool[p]->location == loc && pool[p]->getNameAndAlignment().alive&&pool[p]->align == 1 && !(pool[p]->flag&CREATUREFLAG_SLEEPER)) eaters++;
	return eaters;
}
void noOneIsThere(const int l) {
	printConservativesRaidedUnoccupiedSafehouse(LocationsPool::getInstance().getLocationName(l));
	if (LocationsPool::getInstance().getSiegeType(l) == SIEGE_CCS && LocationsPool::getInstance().getLocationType(l) == SITE_INDUSTRY_WAREHOUSE)
		CCSCapturesSite(l);
	pressAnyKey();
	int y = 0;
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != l) continue;
		if (!pool[p]->getNameAndAlignment().alive)
		{
			printCorpseRecovered(pool[p]->getNameAndAlignment().name, y);
			y++;
			pressAnyKey();
			delete_and_remove(pool, p);
			continue;
		}
		if (pool[p]->align != 1)
		{
			printLiberalRescued(pool[p]->getNameAndAlignment().name, y);
			y++;
			pressAnyKey();
			delete_and_remove(pool, p);
			continue;
		}
	}
	deleteLocationLoot(l);
	deleteLocationVehicles(l);
	gamelog.newline();
	endLocationSiege(l);
}


void airStrike(const char clearformess, const int l, int &num_liberals) {


	bool hit = true;
	printCONST_YOU_HEAR_PLANES_STREAK_OVERHEAD(clearformess);
	pressAnyKey();
	bool hasAAGun = siteHasAAGun(l);
	bool hasGenerator = hasAGenerator(l);
	if (hasAAGun)
	{
 printCONST_THE_THUNDER_OF_THE_ANTI_AIRCRAFT_GUN_SHAKES_THE_COMPOUND(clearformess);
		pressAnyKey();
		if (clearformess) eraseAlt();
		else makedelimiter();
		if (LCSrandom(5))
		{
			hit = false;
			if (LCSrandom(2)) {
				printCONST_YOU_DIDN_T_SHOOT_ANY_DOWN_BUT_YOU_VE_MADE_THEM_THINK_TWICE(clearformess);
			}
			else
			{
				printCONST_HIT_ONE_OF_THE_BOMBERS_SLAMS_INTO_TO_THE_GROUND(clearformess);
				pressAnyKey();
				printCONST_IT_S_ALL_OVER_THE_TV_EVERYONE_IN_THE_LIBERAL_CRIME_SQUAD_GAINS_20_JUICE(clearformess);
				for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) addjuice(*pool[p], 20, 1000);
			}
			gamelog.newline();
			pressAnyKey();
		}
		else
		{
			printCONST_A_SKILLED_PILOT_GETS_THROUGH(clearformess);
			pressAnyKey();
		}
	}
	if (hit)
	{
		printCONST_EXPLOSIONS_ROCK_THE_COMPOUND(clearformess);
		pressAnyKey();
		if (hasAAGun && !LCSrandom(3))
		{
			printCONST_THE_ANTI_AIRCRAFT_GUN_TAKES_A_DIRECT_HIT(clearformess);
			pressAnyKey();
			printCONST_THERE_S_NOTHING_LEFT_BUT_SMOKING_WRECKAGE(clearformess);
			pressAnyKey();
			deleteAAGun(l);
		}
		else if (hasGenerator && !LCSrandom(3))
		{
			printCONST_THE_GENERATOR_HAS_BEEN_DESTROYED(clearformess);
			pressAnyKey();
			printCONST_THE_LIGHTS_FADE_AND_ALL_IS_DARK(clearformess);
			pressAnyKey();
			deleteGeneratorLightsOff(l);
		}
		if (!LCSrandom(2))
		{
			vector<int> pol;
			for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) if (pool[p]->getNameAndAlignment().alive&&pool[p]->location == l) pol.push_back(p);
			if (len(pol))
			{
				if (clearformess) eraseAlt();
				else makedelimiter();
				int targ = pickrandom(pol);
				if ((int)LCSrandom(100) > pool[targ]->juice)
				{
					printWasKilledInBombing(pool[targ]->getNameAndAlignment().name);
					if (pool[targ]->align == 1) stat_dead++, num_liberals--;
					removesquadinfo(*pool[targ]);
					pool[targ]->die();
				}
				else
				{
					printNarrowlyAvoidsDeath(pool[targ]->getNameAndAlignment().name);
				}
				pressAnyKey();
			}
		}
		else
		{
			printNoOneIsHurt(clearformess);
			pressAnyKey();
		}
	}
}
void shotAtBySniper(const char clearformess, const int l, int &num_liberals) {

	vector<int> pol;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) if (pool[p]->getNameAndAlignment().alive&&pool[p]->location == l) pol.push_back(p);
	if (len(pol))
	{
		if (clearformess) eraseAlt();
		else makedelimiter();
		int targ = pickrandom(pol);
		if ((int)LCSrandom(50) > pool[targ]->juice)
		{
			printShotBySniper(pool[targ]->getNameAndAlignment().name);
			if (pool[targ]->align == 1) stat_dead++, num_liberals--;
			removesquadinfo(*pool[targ]);
			pool[targ]->die();
		}
		else
		{
			printMissedBySniper(pool[targ]->getNameAndAlignment().name);
			
		}
		pressAnyKey();
	}
}

void generateReporterDuringSiege(const int l) {


	string repname = generate_name();
	printReporterEnteredCompound(repname);
	pressAnyKey();
	int segmentpower = printBestLCSMemberForNews(repname, l);
	pressAnyKey();
	//CHECK PUBLIC OPINION
	change_public_opinion(VIEW_LIBERALCRIMESQUAD, 20);
	change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, (segmentpower - 25) / 2, segmentpower + 50);
	for (int v = 0; v < 5; v++) change_public_opinion(LCSrandom(VIEWNUM - 3), (segmentpower - 25) / 2);
}
int siegeDontAttack(const int l, const bool clearformess, int num_liberals) {

	char no_bad = 1;
	//CUT LIGHTS
	if (!getLightsOff(l) &&
		!(hasAGenerator(l)) && !LCSrandom(10))
	{
		no_bad = 0;
		printThePoliceCutLights(clearformess);
		pressAnyKey();
		setLightsOff(l);
	}
	//SNIPER
	if (!(hasBasicCompoundWalls(l)) && !LCSrandom(5))
	{
		no_bad = 0;
		shotAtBySniper(clearformess, l, num_liberals);
	}
	if (LocationsPool::getInstance().getSiegeEscalationState(l) >= 3 && !LCSrandom(3))
	{
		no_bad = 0;
		//AIR STRIKE!
		airStrike(clearformess, l, num_liberals);
	}
	if ((LocationsPool::getInstance().get_specific_integer(INT_DOWEHAVETANKTRAPS, l)) &&
		LocationsPool::getInstance().getSiegeEscalationState(l) >= 3 && !LCSrandom(15))
	{
		no_bad = 0;
		//ENGINEERS
		printEngineersRemoveTankTrap(clearformess);
		pressAnyKey();
		printTanksMoveToEntrance(clearformess);
		pressAnyKey();
		LocationsPool::getInstance().deleteTankTraps(l);
	}
	//NEED GOOD THINGS TO BALANCE THE BAD
	// ELITE REPORTER SNEAKS IN
	if (!LCSrandom(20) && no_bad&&num_liberals > 0)
	{
		generateReporterDuringSiege(l);
	}
	return num_liberals;
}
/* siege - updates sieges in progress */
void siegeturn(char clearformess)
{
	if (disbanding)return;
	// Count people at each location
	//int hs=-1;
	int* liberalcount = new int[LocationsPool::getInstance().lenpool()];
	char* food_prep = new char[LocationsPool::getInstance().lenpool()];
	// Clear food_prep and liberalcount lists
	std::memset(food_prep, 0, LocationsPool::getInstance().lenpool());
	std::memset(liberalcount, 0, sizeof(int)*LocationsPool::getInstance().lenpool());
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive)continue; // Dead people don't count
		if (pool[p]->align != 1)continue; // Non-liberals don't count
		if (pool[p]->location == -1)continue; // Vacationers don't count
		liberalcount[pool[p]->location]++;
	}
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++)
		if (LocationsPool::getInstance().isThereASiegeHere(l))
		{
			//resolve sieges with no people
			if (liberalcount[l] == 0)
			{
				noOneIsThere(l);
			}
			if (!LocationsPool::getInstance().isThisUnderAttack(l))
			{
				// Seperate logging message.
				logADayPasses();
				//EAT
				bool starving = false;
				int eaters = numbereating(l);
				if (LocationsPool::getInstance().get_specific_integer(INT_GETSTORESAMOUNT, l) == 0 && eaters > 0)
				{
					starving = true;
					printYourLiberalsAreStarving(clearformess);
					pressAnyKey();
				}
				if (LocationsPool::getInstance().get_specific_integer(INT_GETSTORESAMOUNT, l) >= eaters) reduceCompoundStores(l, eaters);
				else emptyCompoundStores(l);
				//ATTACK!
				char attack = 0;
				for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
				{
					if (!pool[p]->getNameAndAlignment().alive || pool[p]->location != l) continue;
					if (starving) pool[p]->blood -= LCSrandom(8) + 4;
					// Check if liberal starved to death.
					if (pool[p]->blood <= 0)
					{
						pool[p]->die();
						printHasStarvedToDeath(pool[p]->getNameAndAlignment().name, clearformess);
						pressAnyKey();
					}
				}
				if (!LCSrandom(12))attack = 1;
				if (attack)
				{
					printTheCopsAreComing(clearformess);
					pressAnyKey();
					setUnderAttack(l);
				}
				else {
					liberalcount[l] = siegeDontAttack(l, clearformess, liberalcount[l]);
				}
				gamelog.newline(); // single blank line after every siege day
			}
		}
	delete[] liberalcount;
	delete[] food_prep;
}
/* siege - checks how many days of food left at the site */
int fooddaysleft(int loc)
{
	int eaters = numbereating(loc);
	if (eaters == 0) return -1;
	return LocationsPool::getInstance().get_specific_integer(INT_GETSTORESAMOUNT, loc) / eaters + ((LocationsPool::getInstance().get_specific_integer(INT_GETSTORESAMOUNT, loc) % eaters) > eaters / 2);
}
/* siege - what happens when you escaped the siege */
void escapesiege(char won)
{
	//TEXT IF DIDN'T WIN
	if (!won)
	{
		music.play(MUSIC_CONQUER);
		//GIVE INFO SCREEN
		printYouHaveEscaped();
		int homes = -1;
		if (activesquad)
			if (activesquad->squad[0] != NULL)
				homes = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, activesquad->squad[0]->location);
		pressAnyKey();
		//dump retrieved loot in homeless shelter - is there anywhere better to put it?
		if (activesquad&&homes != -1) dumpLootAtLocation(homes, activesquad->loot);
		activesquad = NULL; //active squad cannot be disbanded in removesquadinfo,
							//but we need to disband current squad as the people are going to be 'away'.
							//GET RID OF DEAD, etc.
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) > 1)LocationsPool::getInstance().setRenting(getCurrentSite(), RENTING_NOCONTROL);
		baseEveryoneLeftAtHomelessShelter(homes);
		deleteLocationLoot(getCurrentSite());
		deleteLocationVehicles(getCurrentSite());
		deleteCompoundWalls(getCurrentSite());
		emptyCompoundStores(getCurrentSite());
		deleteBusinessFront(getCurrentSite());
		LocationsPool::getInstance().initLocation(getCurrentSite());
	}
	//SET UP NEW SIEGE CHARACTERISTICS, INCLUDING TIMING
	endLocationSiege(getCurrentSite());
	if (won&&LocationsPool::getInstance().getSiegeType(getCurrentSite()) == SIEGE_POLICE)
	{
		escalateSite(getCurrentSite());
		if (police_heat < 4) police_heat++;
	}
}

/* siege - flavor text when you fought off the raid */
void conquertext()
{
	//GIVE INFO SCREEN
	music.play(MUSIC_CONQUER);
	printConquerText(LocationsPool::getInstance().getSiegeType(getCurrentSite()) == SIEGE_POLICE);
	pressSpecificKey('c', 'x');
	//while (getkeyAlt() != 'c');
}
void addTank() {

	make_creature_without_encounter_array(ENCMAX - 9, CREATURE_TANK);
}

void checkIfRunningFromCops() {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	if (encounter[0].exists&&encounter[0].type == CREATURE_COP)
	{
		sitestory->crime.push_back(CRIME_FOOTCHASE);
		criminalizeparty(LAWFLAG_RESIST);
	}
}

void addNewLineIfFoughtThisRound();
// Siege -- Mass combat outside safehouse
char sally_forth_aux(int loc)
{
	reloadparty();
	siegest siege = getWholeSiege(loc);
	setCurrentSite(loc);
	emptyEncounter();
	switch (siege.siegetype)
	{
	case SIEGE_CIA:
	case SIEGE_HICKS:
	case SIEGE_CORPORATE:
	case SIEGE_CCS:
	case SIEGE_FIREMEN:
	default:
		// So yeah, WTF is the reason there isn't a break statement here???
		// If everything ends up in the SIEGE_POLICE case we shouldn't even have a switch statement here at all.
	case SIEGE_POLICE: // Currently only police sieges should allow this
					   // SWAT teams
		if (siege.escalationstate == 0)
			fillEncounter(CREATURE_SWAT, ENCMAX - 9);
		// Military
		else if (siege.escalationstate >= 1)
			fillEncounter(CREATURE_SOLDIER, ENCMAX - 9);
		// M1 Tank
		if (siege.escalationstate >= 2 && !(LocationsPool::getInstance().get_specific_integer(INT_DOWEHAVETANKTRAPS, loc)))
			addTank();
		break;
	}
	mode = GAMEMODE_CHASEFOOT;
	music.play(MUSIC_DEFENSE);
	bool ranaway = false;
	while (true)
	{
		// Count heroes
		int partysize = 0, partyalive = 0;
		countHeroes(partysize, partyalive);
		// Count bad guys
		int encsize = encounterSize();
		// Let's roll
		autopromote(loc);
		printLocationName(LocationsPool::getInstance().getLocationName(loc));

		// Player's party
		if (partyalive == 0) party_status = -1;
		printparty();
		if (partyalive > 0)
		{
			// Options
			printSiegeOptions(partysize, party_status);
		}
		else
		{
			endcheck(END_BUT_NOT_END); // play the right music in case we're dead
			printReflectOnYourConJudgement();
		}
		// Enemies
		printencounter();
		// check if we fought the previous loop; if so, add a blank gamelog line
		addNewLineIfFoughtThisRound();
		int c = getkeyAlt();
		// Reflecting on your poor judgment
		if (partyalive == 0 && c == 'c' && !endcheck())
		{
			mode = GAMEMODE_BASE;
			return 0;
		}
		// Providing orders
		if (partyalive > 0)
		{
			// Reorder
			if (c == 'o'&&partysize > 1) orderparty();
			// View status
			if (c == '0') party_status = -1;
			// Character info
			party_status = print_character_info(c, party_status);
			// Surrender
			if (c == 'g') giveup();
			// Run away
			if (c == 'd')
			{
				checkIfRunningFromCops();
				evasiverun();
				enemyattack();
				creatureadvance();
				ranaway = true;
			}
			if (c == 'f')
			{
				youattack();
				enemyattack();
				creatureadvance();
			}
			if (c == 'e') LocationsPool::getInstance().equipLoc(loc, -1);
			// Check for victory
			partysize = 0, partyalive = 0;
			countHeroes(partysize, partyalive);
			int baddiecount = baddieCount();
			if (partyalive && !baddiecount)
			{
				cancelOutBleeding();
				mode = GAMEMODE_BASE;
				if (ranaway)
				{
					music.play(MUSIC_CONQUER);
					printYoureFree();
					pressAnyKey();
					escapesiege(false);
					return 1;
				}
				else
				{
					music.play(MUSIC_CONQUER);
					printSiegeIsBroken();
					pressAnyKey();
					conquertext();
					escapesiege(true);
					return 2;
				}
			}
		}
	}
	mode = GAMEMODE_BASE;
	return 1;
}

void createNewStoryEscape(const int loc) {
	Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
	ns->type = NEWSSTORY_SQUAD_ESCAPED;
	ns->positive = 1;
	ns->loc = loc;
	ns->siegetype = LocationsPool::getInstance().getSiegeType(loc);
	newsstory.push_back(ns);
	sitestory = ns;

	char result = sally_forth_aux(loc);

	if (result == 2) ns->type = NEWSSTORY_SQUAD_BROKESIEGE;


	// If you fail, make sure the safehouse isn't under siege anymore by
	// forcing you to give up.
	if (result == 0)
	{
		logDefeat();
		resolvesafehouses();
	}
}
/* siege - prepares for exiting the siege to fight the attackers head on */
void sally_forth()
{
	//GIVE INFO SCREEN
	music.play(MUSIC_DEFENSE);
	printSallyForthSiege();
	int loc = getEscapeEngageLocation();
	if (loc == -1)return;
	printSallyForthFooter();
	pressAnyKey();
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_CCS && LocationsPool::getInstance().getLocationType(loc) == SITE_INDUSTRY_WAREHOUSE)
		CCSCapturesSite(loc); // CCS Captures warehouse -- this will be reversed if you fight them off
							  //CRIMINALIZE
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_POLICE) criminalizepool(LAWFLAG_RESIST, -1, loc);
	//DELETE ALL SQUADS IN THIS AREA UNLESS THEY ARE THE activesquad
	deleteAllSquadsInActiveAreaExceptActive(loc);
	// No squads at the location? Form a new one.
	formANewSquadIfThereAreNone();
	//MAKE SURE PARTY IS ORGANIZED
	autopromote(loc);
	//START FIGHTING
	createNewStoryEscape(loc);
}

/* siege - prepares for entering site mode to fight the siege */
void escape_engage()
{
	music.play(MUSIC_DEFENSE);
	//GIVE INFO SCREEN
	printEscapeEngageInfo();

	int loc = getEscapeEngageLocation();
	if (loc == -1) return;

	printEscapeEngageInfoFooter(LocationsPool::getInstance().siteHasCameras(loc), LocationsPool::getInstance().hasTraps(loc));
	pressAnyKey();
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_CCS && LocationsPool::getInstance().getLocationType(loc) == SITE_INDUSTRY_WAREHOUSE)
		CCSCapturesSite(loc); // CCS Captures warehouse -- this will be reversed if you fight them off
							  //CRIMINALIZE
	if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_POLICE) criminalizepool(LAWFLAG_RESIST, -1, loc);
	//DELETE ALL SQUADS IN THIS AREA UNLESS THEY ARE THE activesquad
	deleteAllSquadsInActiveAreaExceptActive(loc);
	// No squads at the location? Form a new one.
	formANewSquadIfThereAreNone();
	//MAKE SURE PARTY IS ORGANIZED
	autopromote(loc);
	//START FIGHTING
	createNewStoryFieldAttack(loc);
	mode_site(loc);
}

/* siege - flavor text when you crush a CCS safe house */
void conquertextccs()
{
	music.play(MUSIC_CONQUER);
	//GIVE INFO SCREEN
	printConquerTextCCS(ccs_siege_kills, ccs_kills);
	if (ccs_kills >= 3)
	{
		juiceEntireCreaturePool(200, 1000);
	}
	pressSpecificKey('c', 'x');
	//while (getkeyAlt() != 'c');
}