

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


#include "../includes60.h"
#include "../constStringcommonactions.h"
#include <algorithm>
/* common - tests if the person is a wanted criminal */
// *JDS* Checks if the character is a criminal
bool iscriminal(CreatureJustice cr)
{
	for (int i = 0; i < LAWFLAGNUM; i++) if (cr.crimes_suspected[i]) return true;
	return false;
}
/* common - determines how long a creature's injuries will take to heal */
int clinictime(DeprecatedCreature &g)
{
	int time = 0;
	for (int w = 0; w < BODYPARTNUM; w++)
		if ((g.getCreatureHealth().wound[w] & WOUND_NASTYOFF) && (g.getCreatureHealth().blood < 100))
			time++;
	if (g.getCreatureHealth().blood <= 10)time++;
	if (g.getCreatureHealth().blood <= 50)time++;
	if (g.getCreatureHealth().blood < 100)time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_RIGHTLUNG])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_LEFTLUNG])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_HEART])time += 2;
	if (!g.getCreatureHealth().special[SPECIALWOUND_LIVER])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_STOMACH])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_RIGHTKIDNEY])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_LEFTKIDNEY])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_SPLEEN])time++;
	if (g.getCreatureHealth().special[SPECIALWOUND_RIBS] < RIBNUM)time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_NECK])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_UPPERSPINE])time++;
	if (!g.getCreatureHealth().special[SPECIALWOUND_LOWERSPINE])time++;
	return time;
}
/* common - sends somebody to the hospital */
/***************************************************
* *JDS* Hospitalize -- sends current person to the *
* specified clinic or hospital.                    *
***************************************************/
void hospitalize(int loc, DeprecatedCreature &patient)
{
	// He's dead, Jim
	if (!patient.getCreatureHealth().alive)return;
	int time = clinictime(patient);
	if (time > 0)
	{
		Deprecatedsquadst* patientsquad = NULL;
		if (patient.squadid != -1)
			patientsquad = squad[getsquad(patient.squadid)];
		patient.clinic = time;
		patient.squadid = -1;
		patient.location = loc;
		// Inform about the hospitalization
		makedelimiter();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 1, patient.getNameAndAlignment().name, gamelog);
		addstrAlt(WILL_BE_AT_SPACE, gamelog);
		addstrAlt(LocationsPool::getInstance().getLocationName(loc), gamelog);
		addstrAlt(FOR_SPACE, gamelog);
		addstrAlt(time, gamelog);
		addstrAlt(singleSpace, gamelog);
		if (time > 1)addstrAlt(CONST_X_MONTHS, gamelog);
		else addstrAlt(CONST_X_MONTH, gamelog);
		addstrAlt(singleDot, gamelog);
		gamelog.nextMessage(); //Time for the next message.
		pressAnyKey();
		if (patientsquad)
		{  // Reorganize patient's former squad
			bool flipstart = 0;
			for (int p = 0; p < 6; p++)
			{
				if (patientsquad->squad[p] == &patient)
				{
					patientsquad->squad[p] = NULL;
					flipstart = 1;
				}
				if (flipstart&&p < 5) patientsquad->squad[p] = patientsquad->squad[p + 1];
			}
			if (flipstart) patientsquad->squad[5] = NULL;
		}
	}
}
/* returns the amount of heat associated with a given crime */
int lawflagheat(int lawflag)
{
	// Note that for the purposes of this function, we're not looking at how severe the crime is,
	// but how vigorously it is pursued by law enforcement. This determines how quickly they raid
	// you for it, and how much of a penalty you get in court for it. Some crimes are inflated
	// heat, others are deflated (such as the violent crimes).
	//
	// - Jonathan S. Fox
	switch (lawflag)
	{
	case LAWFLAG_TREASON:return 100;
	case LAWFLAG_TERRORISM:return 100;
	case LAWFLAG_MURDER:return 20;
	case LAWFLAG_KIDNAPPING:return 20;
	case LAWFLAG_BANKROBBERY:return 20;
	case LAWFLAG_ARSON:return 50;
	case LAWFLAG_BURNFLAG:return 0;
	case LAWFLAG_SPEECH:return 0;
	case LAWFLAG_BROWNIES:return 50;
	case LAWFLAG_ESCAPED:return 50;
	case LAWFLAG_HELPESCAPE:return 50;
	case LAWFLAG_JURY:return 0;
	case LAWFLAG_RACKETEERING:return 50;
	case LAWFLAG_EXTORTION:return 20;
	case LAWFLAG_ARMEDASSAULT:return 0;   // XXX: This is on the same level as HARMFUL_SPEECH?
	case LAWFLAG_ASSAULT:return 0;        // Fox: Yes. You get too many assault charges to put heat on it.
	case LAWFLAG_CARTHEFT:return 0;
	case LAWFLAG_CCFRAUD:return 20;
	case LAWFLAG_THEFT:return 0;
	case LAWFLAG_PROSTITUTION:return 0;
	case LAWFLAG_HIREILLEGAL:return 10;
		//case LAWFLAG_GUNUSE:return 1;
		//case LAWFLAG_GUNCARRY:return 0;
	case LAWFLAG_COMMERCE:return 20;
	case LAWFLAG_INFORMATION:return 50;
	case LAWFLAG_BURIAL:return 0;
	case LAWFLAG_BREAKING:return 0;
	case LAWFLAG_VANDALISM:return 0;
	case LAWFLAG_RESIST:return 10;
	case LAWFLAG_DISTURBANCE:return 0;
	case LAWFLAG_PUBLICNUDITY:return 0;
	case LAWFLAG_LOITERING:return 0;
	default:return 0;
	}
}
/* common - applies a crime to a person */
void criminalize(DeprecatedCreature &cr, short crime)
{
	if (mode == GAMEMODE_SITE)
	{
		if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
		{
			// Do not criminalize the LCS for self-defense against
			// extrajudicial raids
			if (LocationsPool::getInstance().getSiegeType(getCurrentSite()) != SIEGE_POLICE)
				return;
		}
		else if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
			// Do not criminalize the LCS for crimes against the CCS
			return;
	}
	cr.criminalize_me(crime, true);
}
/* common - applies a crime to everyone in the active party */
void criminalizeparty(short crime)
{
	if (!activesquad) return;
	for (int p = 0; p < 6; p++)
		if (activesquad->squad[p])
		{
			if (!activesquad->squad[p]->getCreatureHealth().alive) continue;
			criminalize(*(activesquad->squad[p]), crime);
		}
}

// *JDS* Scarefactor is the severity of the case against you; if you're a really
// nasty person with a wide variety of major charges against you, then scarefactor
// can get up there
int scare_factor(int lawflag, int crimenumber) {
	return lawflagheat(lawflag) * crimenumber;
}
void addjuice(DeprecatedCreature &cr, long juice, long cap);
/* common - gives juice to everyone in the active party */
void juiceparty(long juice, long cap)
{
	if (activesquad != NULL)
		for (int p = 0; p < 6; p++)
			if (activesquad->squad[p] != NULL)
				if (activesquad->squad[p]->getCreatureHealth().alive)
					addjuice(*activesquad->squad[p], juice, cap);
}
/* common - removes the liberal from all squads */
void removesquadinfo(DeprecatedCreature &cr)
{
	if (cr.squadid != -1)
	{
		long sq = getsquad(cr.squadid);
		if (sq != -1)
		{
			bool flipstart = 0;
			for (int pt = 0; pt < 6; pt++)
			{
				if (squad[sq]->squad[pt] == &cr)flipstart = 1;
				if (flipstart&&pt < 5)squad[sq]->squad[pt] = squad[sq]->squad[pt + 1];
			}
			if (flipstart)squad[sq]->squad[5] = NULL;
		}
		cr.squadid = -1;
	}
}

// Picks a random option, based on the weights provided
int choose_one(const int * weight_list, int number_of_options, int default_value)
{
	int weight_total = 0;
	for (int option = 0; option < number_of_options; option++)
		weight_total += weight_list[option];
	if (weight_total < 1) return default_value; // No acceptable results; use default
	int choose = LCSrandom(weight_total);
	for (int option = 0; option < number_of_options; option++)
	{
		choose -= weight_list[option];
		if (choose < 0)return option;
	}
	return number_of_options;
}
/* common - assigns a new base to all members of a squad */
void basesquad(Deprecatedsquadst *st, long loc)
{
	for (int p = 0; p < 6; p++) if (st->squad[p] != NULL) st->squad[p]->base = loc;
}

// Determines the number of subordinates a creature may command
int maxsubordinates(const DeprecatedCreature& cr)
{
	//brainwashed recruits can't recruit normally
	if (cr.flag & CREATUREFLAG_BRAINWASHED)return 0;
	int recruitcap = 0;
	//Cap based on juice
	if (cr.juice >= 500)      recruitcap += 6;
	else if (cr.juice >= 200) recruitcap += 5;
	else if (cr.juice >= 100) recruitcap += 3;
	else if (cr.juice >= 50)  recruitcap += 1;
	//Cap for founder
	if (cr.hireid == -1 && cr.getCreatureHealth().align == 1) recruitcap += 6;
	return recruitcap;
}
int loveslaves(const DeprecatedCreature& cr);
// Determines the number of love slaves a creature may recruit,
// based on max minus number they already command
int loveslavesleft(const DeprecatedCreature& cr)
{
	// Get maximum lovers
	int loveslavecap = cr.get_skill(SKILL_SEDUCTION) / 2 + 1;
	// -1 if they're a love slave (their boss is a lover)
	if (cr.flag & CREATUREFLAG_LOVESLAVE) loveslavecap--;
	// Subtract number of love slaves they have
	loveslavecap -= loveslaves(cr);
	// If they can have more, return that number
	if (loveslavecap > 0) return loveslavecap;
	// If they're at 0 or less, return 0
	else return 0;
}

/* common - Sort a list of creatures.*/
inline bool sort_name(const DeprecatedCreature* first, const DeprecatedCreature* second) { return strcmp(first->getNameAndAlignment().name.data(), second->getNameAndAlignment().name.data()) < 0; }
bool sort_locationandname(const DeprecatedCreature* first, const DeprecatedCreature* second)
{
	return first->location < second->location
		|| (first->location == second->location
			&&sort_name(first, second));
}
bool sort_squadorname(const DeprecatedCreature* first, const DeprecatedCreature* second)
{
	// Use getsquad to treat members of a new squad being assembled as if not in a squad.
	bool first_in_squad = getsquad(first->squadid) != -1;
	bool second_in_squad = getsquad(second->squadid) != -1;
	bool a = ((first_in_squad && !second_in_squad) //Squad member should come before squadless.
		|| (first_in_squad
			&& first->squadid < second->squadid) //Older squads above newer.
		|| (!first_in_squad && !second_in_squad
			&& sort_name(first, second))); //Sort squadless by name.
										   //Sort members of same squad in the order they are in the squad.
	if (first_in_squad && first->squadid == second->squadid)
		for (int j = 0; j < 6; j++)
			if (squad[getsquad(first->squadid)]->squad[j]->id == first->id) return true;
			else if (squad[getsquad(first->squadid)]->squad[j]->id == second->id) return false;
			return a;
}
bool sort_none(const DeprecatedCreature* first, const DeprecatedCreature* second);
void sortliberals(std::vector<DeprecatedCreature *>& liberals, short sortingchoice, bool dosortnone)
{
	if (!dosortnone&&sortingchoice == SORTING_NONE) return;
	switch (sortingchoice)
	{
	case SORTING_NONE: sort(liberals.begin(), liberals.end(), sort_none); break;
	case SORTING_NAME: sort(liberals.begin(), liberals.end(), sort_name); break;
	case SORTING_LOCATION_AND_NAME: sort(liberals.begin(), liberals.end(), sort_locationandname); break;
	case SORTING_SQUAD_OR_NAME: sort(liberals.begin(), liberals.end(), sort_squadorname); break;
	}
}
map<short, string> trainingActivitySorting;
vector<string> methodOfSorting;
vector<file_and_text_collection> common_text_file_collection = {
	customText(&methodOfSorting, MOSTLY_ENDINGS_FOLDER + METHOD_OF_SORTING_TXT),
};
/* common - Prompt to decide how to sort liberals.*/
void sorting_prompt(short listforsorting)
{
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(1, 1, CHOOSE_HOW_TO_SORT_LIST);
	if (trainingActivitySorting.count(listforsorting)) {
		addstrAlt(trainingActivitySorting[listforsorting]);
	}
	else {
		addstrAlt(trainingActivitySorting[SORTINGCHOICENUM]);
	}
	for (int i = 0; i < len(methodOfSorting); i++) {
		mvaddstrAlt(3 + i, 2, methodOfSorting[i]);
	}
	while (true)
	{
		int c = getkeyAlt();
		if (c == 'a')
		{
			activesortingchoice[listforsorting] = SORTING_NONE; break;
		}
		else if (c == 'b')
		{
			activesortingchoice[listforsorting] = SORTING_NAME; break;
		}
		else if (c == 'c')
		{
			activesortingchoice[listforsorting] = SORTING_LOCATION_AND_NAME; break;
		}
		else if (c == 'd')
		{
			activesortingchoice[listforsorting] = SORTING_SQUAD_OR_NAME; break;
		}
		else if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}
/* common - Returns appropriate sortingchoice enum value for a reviewmode enum value.
Is currently unnecessary unless the enums are changed.*/
short reviewmodeenum_to_sortingchoiceenum(short reviewmode)
{
	switch (reviewmode)
	{
	case REVIEWMODE_LIBERALS: return SORTINGCHOICE_LIBERALS;
	case REVIEWMODE_HOSTAGES: return SORTINGCHOICE_HOSTAGES;
	case REVIEWMODE_CLINIC: return SORTINGCHOICE_CLINIC;
	case REVIEWMODE_JUSTICE: return SORTINGCHOICE_JUSTICE;
	case REVIEWMODE_SLEEPERS: return SORTINGCHOICE_SLEEPERS;
	case REVIEWMODE_DEAD: return SORTINGCHOICE_DEAD;
	case REVIEWMODE_AWAY: return SORTINGCHOICE_AWAY;
	default: return 0;//-1;
	}
}
//string selectA;
//string selectAn;
//string enterDash;
/* common - Displays options to choose from and returns an int corresponding
to the index of the option in the vector. */
int choiceprompt(const string &firstline, const string &secondline,
	const vector<string> &option, const string &optiontypename,
	bool allowexitwochoice, const string &exitstring)
{
	int page = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, firstline);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(1, 0, secondline);
		//Write options
		for (int p = page * 19, y = 2; p < len(option) && p < page * 19 + 19; p++, y++)
		{
			mvaddcharAlt(y, 0, 'A' + y - 2); addstrAlt(spaceDashSpace);
			addstrAlt(option[p]);
		}
		set_color_easy(WHITE_ON_BLACK);
		moveAlt(22, 0);
		switch (optiontypename[0])
		{
		case 'a': case 'e': case 'i': case 'o': case 'u':
		case 'A': case 'E': case 'I': case 'O': case 'U':
			addstrAlt(selectAn + optiontypename); break;
		default:
			addstrAlt(selectA + optiontypename); break;
		}
		mvaddstrAlt(23, 0, addpagestr());
		moveAlt(24, 0);
		if (allowexitwochoice) addstrAlt(enterDash + exitstring);
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(option)) page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + c - 'a';
			if (p < len(option)) return p;
		}
		if (allowexitwochoice && (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR)) break;
	}
	return -1;
}
/* common - Displays a list of things to buy and returns an int corresponding
to the index of the chosen thing in the nameprice vector. */
int buyprompt(const string &firstline, const string &secondline,
	const vector< pair<string, int> > &nameprice, int namepaddedlength,
	const string &producttype, const string &exitstring)
{
	int page = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(0, 0, firstline);
		mvaddstrAlt(1, 0, secondline);
		//Write wares and prices
		for (int p = page * 19, y = 2; p < len(nameprice) && p < page * 19 + 19; p++)
		{
			if (nameprice[p].second > ledger.get_funds())
				set_color_easy(BLACK_ON_BLACK_BRIGHT);
			else set_color_easy(WHITE_ON_BLACK);
			mvaddcharAlt(y, 0, 'A' + y - 2); addstrAlt(spaceDashSpace);
			addstrAlt(nameprice[p].first);
			moveAlt(y++, namepaddedlength + 4); //Add 4 for start of line, eg A - .
			addstrAlt(DOLLARSIGN + tostring(nameprice[p].second));
		}
		set_color_easy(WHITE_ON_BLACK);
		moveAlt(22, 0);
		switch (producttype[0])
		{
		case 'a': case 'e': case 'i': case 'o': case 'u':
		case 'A': case 'E': case 'I': case 'O': case 'U':
			addstrAlt(selectAn + producttype); break;
		default:
			addstrAlt(selectA + producttype); break;
		}
		mvaddstrAlt(23, 0, addpagestr());
		mvaddstrAlt(24, 0, enterDash + exitstring);
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(nameprice)) page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + c - 'a';
			if (p < len(nameprice) && nameprice[p].second <= ledger.get_funds())
				return p;
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
	return -1;
}
/* tells how many total members a squad has (including dead members) */
int squadsize(const Deprecatedsquadst *st)
{
	int partysize = 0;
	if (st) for (int p = 0; p < 6; p++) if (st->squad[p]) partysize++;
	return partysize;
}
/* tells how many members a squad has who are alive */
int squadalive(const Deprecatedsquadst *st)
{
	int partyalive = 0;
	if (st) for (int p = 0; p < 6; p++) if (st->squad[p]) if (st->squad[p]->getCreatureHealth().alive) partyalive++;
	return partyalive;
}