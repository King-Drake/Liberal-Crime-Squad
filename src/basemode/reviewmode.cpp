

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


#include "../includes64.h"
#include "../constStringreviewmode.h"

int getkeyAlt();
void pressAnyKey();
bool is_page_up(const int c);
bool is_page_down(const int c);
int eraseAlt(void);
void printPromotionScreen(const vector<DeprecatedCreature *> temppool, const vector<int> level, const int page) {
	printPromotionHeader();
	printfunds();
	for (int p = page * PAGELENGTH, iteration = 0; p < len(temppool) && p < page*PAGELENGTH + PAGELENGTH; p++, iteration++)
	{
		printPromotionScreenSetup(iteration);
		bool iAmTheLeader = true;
		for (int p2 = 0; p2 < CreaturePool::getInstance().lenpool() && iAmTheLeader; p2++)
		{
			if (pool[p2]->getCreatureHealth().alive == 1 && pool[p2]->id == temppool[p]->hireid)
			{
				printname(pool[p2]->hiding, pool[p2]->location, pool[p2]->flag, pool[p2]->getNameAndAlignment().name);
				printPromotionScreenSetupB(iteration);
				for (int p3 = 0; p3 < CreaturePool::getInstance().lenpool(); p3++)
				{
					if (pool[p3]->getCreatureHealth().alive == 1 && pool[p3]->id == pool[p2]->hireid)
					{
						if (temppool[p]->flag&CREATUREFLAG_LOVESLAVE) {
							printIsLoveSlave();
						}
						else if (!subordinatesleft(*pool[p3]) && !(temppool[p]->flag&CREATUREFLAG_BRAINWASHED))
						{
							printIsBrainWashed();
						}
						else {
							printname(pool[p3]->hiding, pool[p3]->location, pool[p3]->flag, pool[p3]->getNameAndAlignment().name);
						}
						break;
					}
				}
				iAmTheLeader = false;
			}
		}
		if (iAmTheLeader) {
			printIAmLeader();
		}
		printPromotionScreenSetupD(iteration, level[p]);
		printname(temppool[p]->hiding, temppool[p]->location, temppool[p]->flag, temppool[p]->getNameAndAlignment().name);
	}
	printPromotionFooter(len(temppool) > PAGELENGTH);
}
/* base - review - assemble a squad */
void assemblesquad(Deprecatedsquadst *cursquad)
{
	int culloc = -1;
	if (cursquad != NULL) culloc = cursquad->squad[0]->location;
	char newsquad = 0;
	if (cursquad == NULL)
	{
		cursquad = new Deprecatedsquadst;
		cursquad->id = cursquadid;
		cursquadid++;
		newsquad = 1;
	}
	vector<DeprecatedCreature *> temppool;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		if (pool[p]->is_active_liberal() &&
			(pool[p]->location == culloc || culloc == -1))
		{
			temppool.push_back(pool[p]);
		}
	sortliberals(temppool, activesortingchoice[SORTINGCHOICE_ASSEMBLESQUAD]);
	//BUILD LIST OF BASES FOR EACH SQUAD IN CASE IT ENDS UP EMPTY
	//THEN WILL DROP ITS LOOT THERE
	// Must be declared before new squads are formed
	// In order to assure squadloc contains the locations of all current squads
	vector<int> squadloc;
	squadloc.resize(len(squad));
	for (int sl = 0; sl < len(squad); sl++)
	{
		squadloc[sl] = squad[sl]->squad[0]->location;
		if (squadloc[sl] != -1) if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,squadloc[sl]) == RENTING_NOCONTROL)
			squadloc[sl] = -1;
	}
	int page = 0;
	while (true)
	{
		int partysize = cursquad->squadsize();
		printAssembleSquadHeader(partysize, newsquad, cursquad->name);

		for (int p = page * 19, iteration = 0; p < len(temppool) && p < page * 19 + 19; p++, iteration++)
		{
			printCreatureNameForSquad(iteration, temppool[p]->getNameAndAlignment().name);
			char bright = 0;
			int skill = 0;
			for (int sk = 0; sk < SKILLNUM; sk++)
			{
				skill += (int)temppool[p]->get_skill(sk);
				if (temppool[p]->get_skill_ip(sk) >= 100 + (10 * temppool[p]->get_skill(sk)) &&
					temppool[p]->get_skill(sk) < temppool[p]->skill_cap(sk))
				{
					bright = 1;
				}
			}
			printTotalSkill(iteration, skill, bright);
			printhealthstat(temppool[p]->getCreatureHealth(), iteration + 2, 33, FALSE);
			if (temppool[p]->squadid == cursquad->id)
			{
				printSquadGreen(iteration);
			}
			else if (temppool[p]->squadid != -1)
			{
				printSquadYellow(iteration);
			}
			else if (cursquad->squad[0] != NULL)
			{
				if (cursquad->squad[0]->location != temppool[p]->location)
				{
					printSquadAway(iteration);
				}
			}
			printCreatureTypename(iteration, temppool[p]->getCreatureHealth().align, temppool[p]->get_type_name());
		}
		printAddOrRemoveFromSquad(partysize);


		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(temppool)) page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + c - 'a';
			if (p < len(temppool))
			{
				char conf = 1;
				if (cursquad->squad[0] != NULL)
				{
					if (cursquad->squad[0]->location != temppool[p]->location)
					{

						printSquadMustBeInSameLocation();
						pressAnyKey();
						conf = 0;
					}
				}
				if (!temppool[p]->canwalk() &&
					!(temppool[p]->flag & CREATUREFLAG_WHEELCHAIR))
				{

					printSquadMustBeAbleToMove();
					pressAnyKey();
					conf = 0;
				}
				if (conf)
				{
					if (temppool[p]->squadid == cursquad->id)
					{
						bool flipstart = 0;
						for (int pt = 0; pt < 6; pt++)
						{
							if (cursquad->squad[pt] == temppool[p])
							{
								flipstart = 1;
								cursquad->squad[pt]->squadid = -1;
							}
							if (flipstart&&pt < 5)cursquad->squad[pt] = cursquad->squad[pt + 1];
						}
						if (flipstart)cursquad->squad[5] = NULL;
					}
					else if (partysize < 6)
					{
						for (int pt = 0; pt < 6; pt++)
						{
							if (cursquad->squad[pt] == NULL)
							{
								removesquadinfo(*temppool[p]);
								cursquad->squad[pt] = temppool[p];
								temppool[p]->squadid = cursquad->id;
								break;
							}
						}
					}
				}
			}
		}
		if (c == 't')
		{
			sorting_prompt(SORTINGCHOICE_ASSEMBLESQUAD);
			sortliberals(temppool, activesortingchoice[SORTINGCHOICE_ASSEMBLESQUAD], true);
		}
		if (c == 'v')
		{

			printPressLetterToViewLiberalDetails();
			int c2 = getkeyAlt();
			if (c2 >= 'a'&&c2 <= 's')
			{
				int p = page * 19 + c2 - 'a';
				if (p < len(temppool))
				{
					//Create a temporary squad from which to view this character - even if they already have a squad.
					Deprecatedsquadst *oldactivesquad = activesquad;
					int oldSquadID = temppool[p]->squadid;
					//create a temp squad containing just this liberal
					activesquad = new Deprecatedsquadst;
					strcpy(activesquad->name, CONST_TEMPORARY_SQUAD_CAMELCAPS.c_str());
					activesquad->id = cursquadid;
					activesquad->squad[0] = temppool[p];
					temppool[p]->squadid = activesquad->id;
					fullstatus(0);
					delete_and_nullify(activesquad);
					temppool[p]->squadid = oldSquadID;
					activesquad = oldactivesquad;
				}
			}
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR)
		{
			//CHECK IF GOOD (either has at least one Liberal or is empty)
			bool good = true; // Start off at true for empty squads
			for (int p = 0; p < 6; p++)
				if (cursquad->squad[p])
				{  // It is good if either there is at least one Liberal, or if the squad is completely empty
					if (cursquad->squad[p]->getCreatureHealth().align == 1)
					{
						good = true; break;
					} // We found a Liberal, it's good
					else good = false; // We found a non-Liberal, this is bad unless we can find a Liberal too
				}
			if (good) break;
			else
			{  // At this point we have a non-empty squad, none of whose members are Liberal
				printSquadCannotBeOnlyConservative();
				pressAnyKey();
			}
		}
		if (c == '9')
		{
			for (int p = 0; p < 6; p++)
			{
				if (cursquad->squad[p] != NULL)
				{
					cursquad->squad[p]->squadid = -1;
					cursquad->squad[p] = NULL;
				}
			}
		}
	}
	//FINALIZE NEW SQUADS
	if (newsquad)
	{
		bool hasmembers = cursquad->squadsize() > 0;
		if (hasmembers)
		{
			printGiveThisSquadAName(cursquad->name);
			squad.push_back(cursquad);
		}
		else delete cursquad;
	}

	nukeAllEmptySquads(squadloc, mode);
}

vector<DeprecatedCreature *> countLiberals(const short mode) {
	vector<DeprecatedCreature *> temppool;
	switch (mode) {
	case REVIEWMODE_LIBERALS:
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (pool[p]->is_active_liberal())
				temppool.push_back(pool[p]);
		}
		break;
	case REVIEWMODE_HOSTAGES:
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (pool[p]->getCreatureHealth().align != ALIGN_LIBERAL && pool[p]->getCreatureHealth().alive)
				temppool.push_back(pool[p]);
		}
		break;
	case REVIEWMODE_CLINIC:
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (pool[p]->clinic && pool[p]->getCreatureHealth().alive)
				temppool.push_back(pool[p]);
		}
		break;
	case REVIEWMODE_JUSTICE:
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (pool[p]->is_imprisoned())
				temppool.push_back(pool[p]);
		}
		break;
	case REVIEWMODE_SLEEPERS:
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (pool[p]->is_lcs_sleeper())
				temppool.push_back(pool[p]);
		}
		break;
	case REVIEWMODE_DEAD:
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (!pool[p]->getCreatureHealth().alive)
				temppool.push_back(pool[p]);
		}
		break;
	case REVIEWMODE_AWAY:
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if ((pool[p]->dating || pool[p]->hiding) && pool[p]->getCreatureHealth().alive)
				temppool.push_back(pool[p]);
		}
		break;
	}
	return temppool;
}
string getHealthStat(CreatureHealth g, const char smll);
void evaluateLiberals(vector<DeprecatedCreature *> temppool, const int page, const short mode) {
	for (int p = page * 19, iteration = 0; p < len(temppool) && p < page * 19 + 19; p++, iteration++)
	{
		printEvaluateLiberalsHeader(iteration, temppool[p]->getNameAndAlignment().name);
		char bright = 0;
		int skill = 0;
		for (int sk = 0; sk < SKILLNUM; sk++)
		{
			skill += (int)temppool[p]->get_skill(sk);
			if (temppool[p]->get_skill_ip(sk) >= 100 + (10 * temppool[p]->get_skill(sk)) &&
				temppool[p]->get_skill(sk) < temppool[p]->skill_cap(sk))bright = 1;
		}
		printLiberalHealthStat(bright, iteration, skill, getHealthStat(temppool[p]->getCreatureHealth(), true));

		setColorAndPositionForReviewmode(mode, iteration, LocationsPool::getInstance().getLocationNameWithGetnameMethod(temppool[p]->location, true, true));

		switch (mode)
		{
		case REVIEWMODE_LIBERALS:
		{
			char usepers = 1;
			if (temppool[p]->squadid != -1)
			{
				int sq = getsquad(temppool[p]->squadid);
				if (sq != -1)
				{
					if (squad[sq]->activity.type != ACTIVITY_NONE)
					{
						printREVIEWMODE_LIBERALS();
						usepers = 0;
					}
				}
			}
			if (usepers)
			{  // Let's add some color here...
				printREVIEWMODE_LIBERALS(temppool[p]->activity_type(), temppool[p]->getActivityString());
			}
			break;
		}
		case REVIEWMODE_HOSTAGES:
		{

			printREVIEWMODE_HOSTAGES(temppool[p]->joindays);
			break;
		}
		case REVIEWMODE_JUSTICE:
		{
			
			printREVIEWMODE_JUSTICE(temppool[p]->getCreatureJustice().deathpenalty, temppool[p]->getCreatureJustice().sentence, LocationsPool::getInstance().getLocationType(temppool[p]->location));
			
			break;
		}
		case REVIEWMODE_CLINIC:
		{
			printREVIEWMODE_CLINIC(temppool[p]->clinic);
			break;
		}
		case REVIEWMODE_SLEEPERS:
		{
			printREVIEWMODE_SLEEPERS(temppool[p]->getCreatureHealth().align, temppool[p]->get_type_name());
			break;
		}
		case REVIEWMODE_DEAD:
		{
			printREVIEWMODE_DEAD(temppool[p]->deathdays);
			break;
		}
		case REVIEWMODE_AWAY:
		{
			printREVIEWMODE_AWAY(temppool[p]->hiding, temppool[p]->dating);
			break;
		}
		}
	}
}
void review_mode(const short mode)
{
	DeprecatedCreature *swap = NULL;
	int swapPos = 0;
	vector<DeprecatedCreature *> temppool = countLiberals(mode);


	if (!len(temppool)) return;
	sortliberals(temppool, activesortingchoice[reviewmodeenum_to_sortingchoiceenum(mode)]);
	int page = 0;
	int c;
	do
	{
		printReviewStringsHeader(mode);

		evaluateLiberals(temppool, page, mode);

		printPressLetterToViewStats();
		if (swap) {
			printSwapMe(swap->getNameAndAlignment().name);
		}
		else {
			printReorderLiberals();
		}
		printSortPeople();

		c = getkeyAlt();

		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		else
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(temppool)) page++;
		else
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + (int)(c - 'a');
			if (p < len(temppool))
			{
				int page = 0;
				//const int pagenum=2;
				while (true) // a while(true) loop within a while(true) loop  //TODO FIXME
				{
					printProfileHeader(temppool[p]->getCreatureHealth().align != 1);
					if (page == 0) {
						printliberalstats(*temppool[p]);
					}
					else if (page == 1) printliberalskills(temppool[p]->getCreatureJustice(), temppool[p]->getListOfCreatureSkills());
					else if (page == 2) printliberalcrimes(temppool[p]->getCreatureJustice());
					// Add removal of squad members member
					if (temppool[p]->is_active_liberal() &&
						temppool[p]->hireid != -1)  // If alive and not own boss? (suicide?)
					{

						printRemoveLiberal();
						int boss = getpoolcreature(temppool[p]->hireid);
						if (pool[boss]->location == temppool[p]->location) {
							printKillLiberal();
						}
					}
					printReviewModeNameFooter(temppool[p]->getCreatureHealth().align != 1, len(temppool) > 1);
					const int d = getkeyAlt();
					if (len(temppool) > 1 && ((d == KEY_LEFT) || (d == KEY_RIGHT)))
					{
						int sx = 1;
						if (d == KEY_LEFT) sx = -1;
						p = (p + len(temppool) + sx) % len(temppool);
						continue;
					}else
					if (d == KEY_DOWN)
					{
						page++;
						if (page > 2) page = 0;
						continue;
					}else
					if (d == KEY_UP)
					{
						page--;
						if (page < 0) page = 2;
						continue;
					}else
					if (d == 'n')
					{
						printWhatIsNewName();
						temppool[p]->new_name();
					}
					else if (d == 'g' && temppool[p]->getCreatureHealth().align == 1)
					{
						temppool[p]->gender_liberal++;
						if (temppool[p]->gender_liberal > 2)
							temppool[p]->gender_liberal = 0;
					}
					else if (d == 'r' && temppool[p]->is_active_liberal() &&
						temppool[p]->hireid != -1)  // If alive and not own boss? (suicide?)
					{
						int boss = getpoolcreature(temppool[p]->hireid);
						printReleaseLiberalPrompt();
					
						if (getkeyAlt() == 'c')
						{
							// Release squad member
							printHasBeenReleased(temppool[p]->getNameAndAlignment().name);
							pressAnyKey();
							// Chance of member going to police if boss has criminal record and
							// if they have low heart
							// TODO: Do law check against other members?
							if (temppool[p]->get_attribute(ATTRIBUTE_HEART, true) < temppool[p]->get_attribute(ATTRIBUTE_WISDOM, true) + LCSrandom(5)
								&& iscriminal(pool[boss]->getCreatureJustice()))
							{
								printTestifiesAgainstBoss(temppool[p]->getNameAndAlignment().name, pool[boss]->getNameAndAlignment().name);
								criminalize(*pool[boss], LAWFLAG_RACKETEERING);
								pool[boss]->another_confession();
								// TODO: Depending on the crime increase heat or make seige
								if (LocationsPool::getInstance().get_specific_integer(INT_GETHEAT,pool[boss]->base) > 20)
									LocationsPool::getInstance().setSiegetimeuntillocated(pool[boss]->base, 3);
								else
									LocationsPool::getInstance().addHeat(pool[boss]->base, 20);
							}
												   // Remove squad member
							removesquadinfo(*temppool[p]);
							cleangonesquads();
							delete_and_remove(temppool, p, pool, getpoolcreature(temppool[p]->id));
							break;
						}
					}
					else if (d == 'k' && temppool[p]->is_active_liberal() &&
						temppool[p]->hireid != -1)  // If alive and not own boss? (suicide?)
					{
						// Kill squad member
						int boss = getpoolcreature(temppool[p]->hireid);
						if (pool[boss]->location != temppool[p]->location) break;
						printKillAllyPrompt(pool[boss]->getNameAndAlignment().name);
						
						if (getkeyAlt() == 'c')
						{
							temppool[p]->die();
							cleangonesquads();
							stat_kills++;

							printPerformsExecution(pool[boss]->getNameAndAlignment().name, temppool[p]->getNameAndAlignment().name);
							pressAnyKey();
							if (boss != -1)
							{
								if (LCSrandom(pool[boss]->get_attribute(ATTRIBUTE_HEART, false)) > LCSrandom(3))
								{
									printLosesHeart(pool[boss]->getNameAndAlignment().name);
									pool[boss]->adjust_attribute(ATTRIBUTE_HEART, -1);
									pressAnyKey();
								}
								else if (!LCSrandom(3))
								{
									printGainsWisdom(pool[boss]->getNameAndAlignment().name);
									pool[boss]->adjust_attribute(ATTRIBUTE_WISDOM, +1);
									pressAnyKey();
								}
							}
							break;
						}
					}
					else break;
				}
			}
		}
		else
		if (c == 't')
		{
			sorting_prompt(reviewmodeenum_to_sortingchoiceenum(mode));
			sortliberals(temppool, activesortingchoice[reviewmodeenum_to_sortingchoiceenum(mode)], true);
		}
		else
		// Reorder squad
		if (c == 'z')
		{
			if (len(temppool) <= 1) continue;
			printSwapSquadMember();
			if (!swap) {
				int c = getkeyAlt();
				if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
				if (c<'a' || c>'s') continue; // Not within correct range
											  // Get first member to swap
				int p = page * 19 + c - 'a';
				if (p < len(temppool)) swap = temppool[swapPos = p];
			}
			else { // non-null swap
				printNameWith(swap->getNameAndAlignment().name);
				int c = getkeyAlt();
				if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
				if (c<'a' || c>'s') continue; // Not within correct range
				int p = page * 19 + c - 'a';
				if (p < len(temppool) && temppool[p] != swap)
				{
					DeprecatedCreature* swap2 = temppool[p];
					for (int i = 0; i < CreaturePool::getInstance().lenpool(); i++)
						if (pool[i]->id == swap->id)
						{
							pool.erase(pool.begin() + i);
							break;
						}
					for (int i = 0; i < CreaturePool::getInstance().lenpool(); i++)
						if (pool[i]->id == swap2->id)
						{
							pool.insert(pool.begin() + i + (swapPos < p), swap);
							break;
						}
					temppool.erase(temppool.begin() + swapPos);
					temppool.insert(temppool.begin() + p, swap);
					swap = NULL;
				}
			}
		}
		
	}while (c != 'x' && c != ENTER && c != ESC && c != SPACEBAR);
}
/* base - review - assign new bases to the squadless */
void squadlessbaseassign()
{
	int page_lib = 0, page_loc = 0, selectedbase = 0;
	vector<DeprecatedCreature *> temppool;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) if (pool[p]->is_active_liberal() && pool[p]->squadid == -1) temppool.push_back(pool[p]);
	if (!len(temppool)) return;
	sortliberals(temppool, activesortingchoice[SORTINGCHOICE_BASEASSIGN]);
	vector<int> temploc;
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++) if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,l) >= 0 && !LocationsPool::getInstance().isThereASiegeHere(l)) temploc.push_back(l);
	if (!len(temploc)) return;
	while (true)
	{
		printBaseAssignmentHeader();
		printfunds();
		for (int p = page_lib * 19, iteration = 0; p < len(temppool) && p < page_lib * 19 + 19; p++, iteration++)
		{
			// Red name if location under siege
			printLiberalNameInLocation(temppool[p]->base == temppool[p]->location,
				LocationsPool::getInstance().isThereASiegeHere(temppool[p]->base),
				multipleCityMode && LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, temppool[p]->base) != LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, temploc[selectedbase]),
				iteration,
				temppool[p]->getNameAndAlignment().name,
				LocationsPool::getInstance().getLocationNameWithGetnameMethod(temppool[p]->base, true, true)			
			);
		}
		for (int p = page_loc * 9, iteration = 0; p < len(temploc) && p < page_loc * 9 + 9; p++, iteration++)
		{
			printBaseName(p == selectedbase, iteration, LocationsPool::getInstance().getLocationNameWithGetnameMethod(temploc[p], true, true));
		}
		printBaseAssignmentFooter(len(temppool) > 19, len(temploc) > 9);
		int c = getkeyAlt();
		//PAGE UP (people)
		if (is_page_up(c) && page_lib > 0) page_lib--;
		//PAGE DOWN (people)
		if (is_page_down(c) && (page_lib + 1) * 19 < len(temppool)) page_lib++;
		//PAGE UP (locations)
		if (c == ','&&page_loc > 0) page_loc--;
		//PAGE DOWN (locations)
		if (c == '.' && (page_loc + 1) * 9 < len(temploc)) page_loc++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page_lib * 19 + c - 'a';
			// Assign new base, IF the selected letter is a liberal, AND the Liberal is not under siege or in a different city
			if (p < len(temppool)
				&& !(temppool[p]->base == temppool[p]->location && LocationsPool::getInstance().isThereASiegeHere(temppool[p]->base))
				&& !(multipleCityMode && LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,temppool[p]->base) != LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,temploc[selectedbase])))
			{
				temppool[p]->base = temploc[selectedbase];
			}
		}
		if (c >= '1'&&c <= '9')
		{
			int p = page_loc * 9 + c - '1';
			if (p < len(temploc)) selectedbase = p;
		}
		if (c == 't')
		{
			sorting_prompt(SORTINGCHOICE_BASEASSIGN);
			sortliberals(temppool, activesortingchoice[SORTINGCHOICE_BASEASSIGN], true);
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}
void sortbyhire(vector<DeprecatedCreature *> &temppool, vector<int> &level)
{
	vector<DeprecatedCreature *> newpool;
	level.clear();
	for (int i = len(temppool) - 1; i >= 0; i--)
		if (temppool[i]->hireid == -1)
		{
			newpool.insert(newpool.begin(), temppool[i]);
			level.insert(level.begin(), 0);
			temppool.erase(temppool.begin() + i);
		}
	bool changed;
	do
	{
		changed = false;
		for (int i = 0; i < len(newpool); i++)
			for (int j = len(temppool) - 1; j >= 0; j--)
				if (temppool[j]->hireid == newpool[i]->id)
				{
					newpool.insert(newpool.begin() + i + 1, temppool[j]);
					level.insert(level.begin() + i + 1, level[i] + 1);
					temppool.erase(temppool.begin() + j);
					changed = true;
				}
	} while (changed);
	temppool.clear();
	for (int p = 0; p < len(newpool); p++)
		temppool.push_back(newpool[p]);
}

bool printAttemptNewPromotion(const vector<DeprecatedCreature *> temppool, const int p) {

	for (int p2 = 0; p2 < CreaturePool::getInstance().lenpool(); p2++)
	{
		if (pool[p2]->getCreatureHealth().alive == 1 && pool[p2]->id == temppool[p]->hireid)
		{
			printJustThis(pool[p2]->getNameAndAlignment().name);
			for (int p3 = 0; p3 < CreaturePool::getInstance().lenpool(); p3++)
			{
				// Can't promote if new boss can't accept more subordinates
				if (pool[p3]->getCreatureHealth().alive == 1 && pool[p3]->id == pool[p2]->hireid &&
					(temppool[p]->flag&CREATUREFLAG_BRAINWASHED || subordinatesleft(*pool[p3])))
				{
					temppool[p]->hireid = pool[p2]->hireid;
					return true;
				}
			}
			return false;
		}
	}
	return false;
}
vector<DeprecatedCreature *> getAllLiberals() {

	vector<DeprecatedCreature *> temppool;
	for (DeprecatedCreature* p : pool) {
		if (p->getCreatureHealth().alive&&p->getCreatureHealth().align == 1) {
			temppool.push_back(p);
		}
	}
	return temppool;
}
/* base - review - promote liberals */
void promoteliberals()
{
	vector<DeprecatedCreature *> temppool = getAllLiberals();
	if (!len(temppool)) return;
	//SORT
	vector<int> level;
	sortbyhire(temppool, level);
	//PROMOTE
	int page = 0;
	int c;
	do
	{
		printPromotionScreen(temppool, level, page);


		c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1)*PAGELENGTH < len(temppool)) page++;
		if (c >= 'a'&&c <= 'a' + PAGELENGTH)
		{
			int p = page * PAGELENGTH + (int)(c - 'a');
			// *JDS* can't promote liberals in hiding OR loveslaves
			bool creatureIsNeitherHidingNorLoveslave = p < len(temppool) && !temppool[p]->hiding && !(temppool[p]->flag&CREATUREFLAG_LOVESLAVE);
			if (creatureIsNeitherHidingNorLoveslave)
			{
				if (printAttemptNewPromotion(temppool, p)) {
					sortbyhire(temppool, level);
				}
			}
		}
	} while (c != 'x' && c != ENTER && c != ESC && c != SPACEBAR);
}
bool iterateReview(int &page) {

	music.play(MUSIC_REVIEWMODE);
	printReviewHeader();
	int n[8] = { 0,0,0,0,0,0,0,0 };
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->is_active_liberal()) n[0]++; // Active Liberals
		if (pool[p]->getCreatureHealth().align != ALIGN_LIBERAL && pool[p]->getCreatureHealth().alive) n[1]++; // Hostages
		if (pool[p]->clinic && pool[p]->getCreatureHealth().alive) n[2]++; // Hospital
		if (pool[p]->is_imprisoned()) n[3]++; // Justice System
		if (pool[p]->is_lcs_sleeper()) n[4]++; // Sleepers
		if (!pool[p]->getCreatureHealth().alive) n[5]++; // The Dead
		if ((pool[p]->dating || pool[p]->hiding) && pool[p]->getCreatureHealth().alive) n[6]++; // Away
	}
	n[7] += consolidateSiegeLoot();

	
	for (int p = page * 19, iteration = 0; p < len(squad) + REVIEWMODENUM + 1 && p < page * 19 + 19; p++, iteration++)
	{
		if (p < len(squad))
		{
			printSquadName(squad[p]->name, activesquad == squad[p], iteration);
			
			if (squad[p]->squad[0] != NULL)
			{
				if (squad[p]->squad[0]->location != -1) {
					printSquadLocationAndSiegeStatus(squad[p]->squad[0]->location, iteration, activesquad == squad[p]);
				}

				std::string str = getactivity(squad[p]->activity);

				int activityTypeID = squad[p]->activity.type;

				if (squad[p]->activity.type == ACTIVITY_NONE)
				{
					bool haveact = false, multipleact = false;
					for (int p2 = 0; p2 < 6; p2++)
					{
						if (squad[p]->squad[p2] == NULL) continue;
						const std::string str2 = squad[p]->squad[p2]->getActivityString();
						activityTypeID = squad[p]->squad[p2]->activity_type();
						if (haveact&&str != str2) multipleact = true;
						str = str2, haveact = true;
					}
					if (multipleact)
					{
						activityTypeID = ACTIVITYNUM;
						str = CONST_ACTING_INDIVIDUALLY_CAMELCAPS;
					}
				}
				printReviewActivity(activityTypeID, iteration, str);
			}
		}
		else {
			printReviewModeOptions(p - len(squad), iteration, n[p - len(squad)]);
		}


	}
	printReviewModeFooter(music.isEnabled());
	int c = getkeyAlt();
	if (is_page_up(c) && page > 0) page--;
	if (is_page_down(c) && (page + 1) * 19 < len(squad) + REVIEWMODENUM) page++;
	if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) return false;
	if (c >= 'a'&&c <= 's')
	{
		int sq = page * 19 + c - 'a';
		if (sq < len(squad) && sq >= 0)
		{
			if (squad[sq] == activesquad)assemblesquad(squad[sq]);
			else activesquad = squad[sq];
		}
	}
	if (c >= '1'&&c <= '7') review_mode(c - '1');
	if (c == '8') equipmentbaseassign();
	if (c == 'z')
	{
		assemblesquad(NULL);
		if (!activesquad&&len(squad))
			activesquad = squad[len(squad) - 1];
	}
	if (c == 't') squadlessbaseassign();
	if (c == 'u') promoteliberals();
	if (c == 'v')
	{
		char clearformess = false;
		fundreport(clearformess);
		if (clearformess) eraseAlt();
	}
	if (c == 'y') music.enableIf(!music.isEnabled());

	return true;
}
/* base - review and reorganize liberals */
void review()
{
	int page = 0;
	while (iterateReview(page))
	{

	}
}
