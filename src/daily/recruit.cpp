

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

#include "../includes41.h"
#include "../constStringrecruit.h"
Deprecatedrecruitst::Deprecatedrecruitst(DeprecatedCreature *cr, int id) {
	recruit = cr;
	recruiter_id = id;
	//Has heard of the LCS
	if ((int)LCSrandom(100) < attitude[VIEW_LIBERALCRIMESQUAD])
	{
		//Likes the LCS
		if ((int)LCSrandom(100) < attitude[VIEW_LIBERALCRIMESQUADPOS])
			eagerness1 = 3;
		//Doesn't like the LCS
		else eagerness1 = 0;
	}
	else eagerness1 = 2;
}
Deprecatedrecruitst::~Deprecatedrecruitst()
{
	delete recruit;
}
char Deprecatedrecruitst::eagerness()
{
	char eagerness_temp = eagerness1;
	//Moderates are decidedly less interested
	if (recruit->align == 0) eagerness_temp -= 2;
	//Conservatives are extremely uninterested
	if (recruit->align == -1) eagerness_temp -= 4;
	return eagerness_temp;
}
/* recruiting */
vector<RecruitData> recruitable_creatures;
// Return the difficulty of tracking this character type down, for the
// purpose of the activation menu. 0 is trivial, 10 is impossible.
int recruitFindDifficulty(int creatureType)
{
	for (int i = 0; i < len(recruitable_creatures); i++)
		if (recruitable_creatures[i].type == creatureType)
			return recruitable_creatures[i].difficulty;
	return 10; // No RecruitData; assume impossible to recruit
}
string recruitName(int creatureType) {

	for (int i = 0; i < len(recruitable_creatures); i++)
		if (recruitable_creatures[i].type == creatureType)
			return recruitable_creatures[i].name;
	return MISSING_NO;
}

void recruitment_activity(DeprecatedCreature &cr)
{
	int ocursite = getCurrentSite();
	setCurrentSite(cr.location);
	int type = cr.activity_arg();
	int difficulty = recruitFindDifficulty(type);
	string name = recruitName(type);
	if (type >= 0)
	{
		music.play(MUSIC_RECRUITING);
		cr.train(SKILL_STREETSENSE, 5);
		printAdventuresInRecruitment();
		printcreatureinfo(&cr);
		makedelimiter();
		printAskAroundForARecruit(cr.getNameAndAlignment().name, name);
		pressAnyKey();
		int recruitCount = 0;
		if (difficulty < 10)
			// Generate recruitment candidates
			for (recruitCount = 0; recruitCount < 5; recruitCount++)
			{
				if (recruitCount == 0 || cr.skill_roll(SKILL_STREETSENSE) >(difficulty + recruitCount * 2))
				{
					make_creature_without_encounter_array(recruitCount, type);
					encounter[recruitCount].namecreature();
				}
				else break;
			}
		if (recruitCount == 0) {
			printWasUnableToTrackDown(cr.getNameAndAlignment().name, name);
			pressAnyKey();
			setCurrentSite(ocursite);
			return;
		}
		else if (recruitCount == 1) {
			printSetupAMeeting(cr.getNameAndAlignment().name, encounter[0].align, encounter[0].getNameAndAlignment().name, get_age_string(encounter[0].getCreatureBio(), encounter[0].animalgloss));
			pressAnyKey();
			printAdventuresInRecruitment();
			printcreatureinfo(&encounter[0]);
			makedelimiter();
			talk(cr, 0);
		}
		else {
			while (true)
			{
				printAdventuresInRecruitment();
				printcreatureinfo(&cr);
				makedelimiter();
				printFoundMultipleRecruits(cr.getNameAndAlignment().name);
				for (int i = 0; i < recruitCount; i++) {
					printSingleRecruit(i, encounter[i].align, encounter[i].getNameAndAlignment().name, get_age_string(encounter[i].getCreatureBio(), encounter[i].animalgloss));
				}
				printPressEnterToCallItADay(recruitCount);
				int c = getkeyAlt();
				if (c == ENTER || c == ESC) break;
				c -= 'a';
				if (c >= 0 && c < ENCMAX - 1 && encounter[c].getNameAndAlignment().exists)
				{
					int id = encounter[c].id;
					printAdventuresInRecruitment();
					printcreatureinfo(&encounter[c]);
					makedelimiter();
					talk(cr, c);
					if (encounter[c].id == id) delenc(c, 0);
					recruitCount--;
					if (recruitCount <= 0) break;
				}
			}
		}
	}
	setCurrentSite(ocursite);
}