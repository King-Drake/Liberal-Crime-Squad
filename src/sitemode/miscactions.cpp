
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

#include "../includes13.h"
#include "../constStringmiscactions.h"
UnlockAttempt unlock(short type)
{
	int difficulty = 0;
	if (type == UNLOCK_DOOR) {
		if (securityable(LocationsPool::getInstance().getLocationType(getCurrentSite())) == 1)
			difficulty = DIFFICULTY_CHALLENGING;
		else if (securityable(LocationsPool::getInstance().getLocationType(getCurrentSite())) > 1)
			difficulty = DIFFICULTY_HARD;
		else
			difficulty = DIFFICULTY_EASY;
	}
	else {
		if (unlockDifficulty.count(type)) {
			difficulty = unlockDifficulty[type];
		}
	}
	int maxattack = -1;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->getNameAndAlignment().alive)
			{
				if (activesquad->squad[p]->get_skill(SKILL_SECURITY) > maxattack)
				{
					maxattack = activesquad->squad[p]->get_skill(SKILL_SECURITY);
				}
			}
		}
	}
	vector<int> goodp;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->getNameAndAlignment().alive)
			{
				if (activesquad->squad[p]->get_skill(SKILL_SECURITY) == maxattack)
				{
					goodp.push_back(p);
				}
			}
		}
	}
	if (len(goodp))
	{
		int p = pickrandom(goodp);
		//lock pick succeeded.
		if (activesquad->squad[p]->skill_check(SKILL_SECURITY, difficulty))
		{
			//skill goes up in proportion to the chance of you failing.
			if (maxattack <= difficulty)
			{
				switch (fieldskillrate)
				{
				case FIELDSKILLRATE_FAST:
					activesquad->squad[p]->train(SKILL_SECURITY, 10 * difficulty); break;
				case FIELDSKILLRATE_CLASSIC:
					activesquad->squad[p]->train(SKILL_SECURITY, 1 + (difficulty - maxattack)); break;
				case FIELDSKILLRATE_HARD:
					activesquad->squad[p]->train(SKILL_SECURITY, 0); break;
				}
			}
			clearmessagearea(false);
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
			addstrAlt(singleSpace, gamelog);
			switch (type)
			{
			case UNLOCK_DOOR:addstrAlt(CONST_UNLOCKS_THE_DOOR, gamelog); break;
			case UNLOCK_CAGE_HARD:
			case UNLOCK_CAGE:addstrAlt(CONST_UNLOCKS_THE_CAGE, gamelog); break;
			case UNLOCK_SAFE:addstrAlt(CONST_CRACKS_THE_SAFE, gamelog); break;
			case UNLOCK_ARMORY:addstrAlt(CONST_OPENS_THE_ARMORY, gamelog); break;
			case UNLOCK_CELL:addstrAlt(CONST_UNLOCKS_THE_CELL, gamelog); break;
			case UNLOCK_VAULT:addstrAlt(CONST_CRACKS_THE_COMBO_LOCKS, gamelog); break;
			}
			addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
			gamelog.newline();
			for (int j = 0; j < 6; j++) //If people witness a successful unlock, they learn a little bit.
			{
				if (j == p) continue;
				if (activesquad->squad[j] != NULL &&
					activesquad->squad[j]->getNameAndAlignment().alive&&
					activesquad->squad[j]->get_skill(SKILL_SECURITY) < difficulty)
				{
					if (activesquad->squad[j]->getNameAndAlignment().alive)
					{
						switch (fieldskillrate)
						{
						case FIELDSKILLRATE_FAST:
							activesquad->squad[j]->train(SKILL_SECURITY, 5 * difficulty); break;
						case FIELDSKILLRATE_CLASSIC:
							activesquad->squad[j]->train(SKILL_SECURITY, difficulty - activesquad->squad[j]->get_skill(SKILL_SECURITY)); break;
						case FIELDSKILLRATE_HARD:
							activesquad->squad[j]->train(SKILL_SECURITY, 0); break;
						}
					}
				}
			}
			pressAnyKey();
			return UNLOCKED;
		}
		else
		{
			clearmessagearea(false);
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			int i;
			//gain some experience for failing only if you could have succeeded.
			for (i = 0; i < 3; i++)
			{
				if (activesquad->squad[p]->skill_check(SKILL_SECURITY, difficulty))
				{
					switch (fieldskillrate)
					{
					case FIELDSKILLRATE_FAST:
						activesquad->squad[p]->train(SKILL_SECURITY, 50); break;
					case FIELDSKILLRATE_CLASSIC:
						activesquad->squad[p]->train(SKILL_SECURITY, 10); break;
					case FIELDSKILLRATE_HARD:
						activesquad->squad[p]->train(SKILL_SECURITY, 10); break;
					}
					mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
					addstrAlt(CONST_IS_CLOSE_BUT_CAN_T_QUITE_GET_THE_LOCK_OPEN, gamelog);
					gamelog.newline();
					break;
				}
			}
			if (i == 3)
			{
				mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_CAN_T_FIGURE_THE_LOCK_OUT, gamelog);
				gamelog.newline();
			}
			pressAnyKey();
			return LOUD_FAILURE;
		}
	}
	else
	{
		clearmessagearea();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_YOU_CAN_T_FIND_ANYONE_TO_DO_THE_JOB, gamelog);
		gamelog.newline();
		pressAnyKey();
	}
	return NEVERMIND;
}
/* bash attempt */
UnlockAttempt bash()
{

	int difficulty = 0;
	bool crowable = false;
	
		if (!securityable(LocationsPool::getInstance().getLocationType(getCurrentSite())))
		{
			difficulty = DIFFICULTY_EASY; // Run down dump
			crowable = true;
		}
		else if (LocationsPool::getInstance().getLocationType(getCurrentSite()) != SITE_GOVERNMENT_PRISON &&
			LocationsPool::getInstance().getLocationType(getCurrentSite()) != SITE_GOVERNMENT_INTELLIGENCEHQ)
		{
			difficulty = DIFFICULTY_CHALLENGING; // Respectable place
			crowable = true;
		}
		else
		{
			difficulty = DIFFICULTY_FORMIDABLE; // Very high security
			crowable = false;
		}
	
	if (crowable)
	{
		//if(!squadhasitem(*activesquad,ITEM_WEAPON,WEAPON_CROWBAR))
		//{
		crowable = false;
		for (int p = 0; p < 6; p++)
		{
			if (activesquad->squad[p] != NULL)
			{
				if (activesquad->squad[p]->get_weapon().get_specific_bool(BOOL_AUTO_BREAK_LOCK_))
					crowable = true;
			}
		}
		if (!crowable) //didn't find in hands of any squad member
		{
			for (int l = 0; l < len(activesquad->loot); l++)
			{
				if (activesquad->loot[l]->whatIsThis() == THIS_IS_WEAPON)
				{
					Weapon *w = static_cast<Weapon*>(activesquad->loot[l]); //cast -XML
					if (w->get_specific_bool(BOOL_AUTO_BREAK_LOCK_))
						crowable = true;
				}
			}
		}
		//}
	}
	int maxp = 0;
	if (!crowable)
	{
		int maxattack = 0;
		for (int p = 0; p < 6; p++)
		{
			if (activesquad->squad[p] != NULL)
			{
				if (activesquad->squad[p]->getNameAndAlignment().alive)
				{
					if (activesquad->squad[p]->get_attribute(ATTRIBUTE_STRENGTH, true)*
						activesquad->squad[p]->get_weapon().get_bashstrengthmod() > maxattack)
					{
						maxattack = static_cast<int>(activesquad->squad[p]->get_attribute(ATTRIBUTE_STRENGTH, true)*
							activesquad->squad[p]->get_weapon().get_bashstrengthmod());
						maxp = p;
					}
				}
			}
		}
	}
	difficulty = static_cast<int>(difficulty / activesquad->squad[maxp]->get_weapon().get_bashstrengthmod());
	if (crowable || activesquad->squad[maxp]->attribute_check(ATTRIBUTE_STRENGTH, difficulty))
	{
		clearmessagearea(false);
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, activesquad->squad[maxp]->getNameAndAlignment().name, gamelog);
		addstrAlt(singleSpace, gamelog);
		
			if (crowable) addstrAlt(CONST_USES_A_CROWBAR_ON_THE_DOOR, gamelog);
			else if (activesquad->squad[maxp]->get_weapon().get_bashstrengthmod() > 1)
				addstrAlt(CONST_SMASHES_IN_THE_DOOR, gamelog);
			else if (activesquad->squad[maxp]->flag&CREATUREFLAG_WHEELCHAIR)
				addstrAlt(CONST_RAMS_OPEN_THE_DOOR, gamelog);
			else addstrAlt(CONST_KICKS_IN_THE_DOOR, gamelog);
		
		addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
		gamelog.newline();
		pressAnyKey();
		int timer = 5;
		if (crowable) timer = 20;
		if (sitealarmtimer<0 || sitealarmtimer>timer)
			sitealarmtimer = timer;
		else sitealarmtimer = 0;
		//Bashing doors in secure areas sets off alarms
		if ((LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_GOVERNMENT_PRISON ||
			LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_GOVERNMENT_INTELLIGENCEHQ) &&
			!isThereASiteAlarm())
		{
			setSiteAlarmOne();
			set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(17, 1, CONST_ALARMS_GO_OFF_EXCLAMATION, gamelog);
			gamelog.newline();
			pressAnyKey();
		}
		return UNLOCKED;
	}
	else
	{
		clearmessagearea(false);
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, activesquad->squad[maxp]->getNameAndAlignment().name, gamelog);
		
			if (activesquad->squad[maxp]->flag&CREATUREFLAG_WHEELCHAIR)
				addstrAlt(CONST_RAMS_INTO_THE_DOOR, gamelog);
			else addstrAlt(CONST_KICKS_THE_DOOR, gamelog);
		
		addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
		gamelog.newline();
		pressAnyKey();
		if (sitealarmtimer < 0) sitealarmtimer = 25;
		else if (sitealarmtimer > 10) sitealarmtimer -= 10;
		else sitealarmtimer = 0;
		return LOUD_FAILURE;
	}
}
/* computer hack attempt */
UnlockAttempt hack(short type)
{
	int difficulty = 0;
	switch (type)
	{
	case HACK_SUPERCOMPUTER:difficulty = DIFFICULTY_HEROIC; break;
	case HACK_VAULT:difficulty = DIFFICULTY_CHALLENGING; break;
	}
	int maxattack = 0, maxblindattack = -3, hacker = -1, blind = -1;
	for (int p = 0; p < 6; p++) if (activesquad->squad[p] != NULL)
		if (activesquad->squad[p]->getNameAndAlignment().alive && activesquad->squad[p]->get_skill(SKILL_COMPUTERS))
		{
			int roll = activesquad->squad[p]->skill_roll(SKILL_COMPUTERS);
			if (!activesquad->squad[p]->special[SPECIALWOUND_RIGHTEYE] &&
				!activesquad->squad[p]->special[SPECIALWOUND_LEFTEYE])
			{  // we got a blind person here
				roll -= 3; // blindness handicaps you by 3, highest roll you can get is 15 instead of 18
				if (roll > maxblindattack) maxblindattack = roll, blind = p; // best blind hacker so far
			}
			else
			{  // we got someone who can see here
				if (roll > maxattack) maxattack = roll, hacker = p; // best hacker with eyeballs so far
			}
		}
	if (blind > -1 && (hacker == -1 || (maxblindattack > maxattack&&maxblindattack > 0)))
		hacker = blind, maxattack = maxblindattack, blind = true; // the best hacker is a blind person
	else if (blind > -1 && hacker == -1 && maxblindattack <= 0)
		blind = true; // we only have a blind hacker, and their roll with the handicap is 0 or less
	else blind = false; // either our hacker has eyeballs or there is no hacker at all
	if (hacker > -1)
	{
		activesquad->squad[hacker]->train(SKILL_COMPUTERS, difficulty);
		if (maxattack > difficulty)
		{
			clearmessagearea();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, activesquad->squad[hacker]->getNameAndAlignment().name, gamelog);
			if (!blind) addstrAlt(CONST_HAS, gamelog);
			switch (type)
			{
			case HACK_SUPERCOMPUTER:addstrAlt(CONST_BURNED_A_DISK_OF_TOP_SECRET_FILES, gamelog); break;
			case HACK_VAULT:addstrAlt(CONST_DISABLED_THE_SECOND_LAYER_OF_SECURITY, gamelog); break;
			}
			if (blind)
				addstrAlt(CONST_DESPITE_BEING_BLIND, gamelog);
			addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
			gamelog.newline();
			pressAnyKey();
			return UNLOCKED;
		}
		else
		{
			clearmessagearea();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, activesquad->squad[hacker]->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_COULDN_T, gamelog);
			if (blind) addstrAlt(CONST_SEE_HOW_TO, gamelog);
			switch (type)
			{
			case HACK_SUPERCOMPUTER:addstrAlt(CONST_BYPASS_THE_SUPERCOMPUTER_SECURITY, gamelog); break;
			case HACK_VAULT:addstrAlt(CONST_BYPASS_THE_VAULT_S_ELECTRONIC_LOCK, gamelog); break;
			}
			gamelog.newline();
			pressAnyKey();
			return LOUD_FAILURE;
		}
	}
	else
	{
		clearmessagearea();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_YOU_CAN_T_FIND_ANYONE_TO_DO_THE_JOB, gamelog);
		gamelog.newline();
		if (blind)
		{  // your only hacker was blind and had a skill roll, after the handicap, of 0 or less
			pressAnyKey();
			mvaddstrAlt(17, 1, CONST_INCLUDING_THE_BLIND_HACKER_YOU_BROUGHT, gamelog);
			gamelog.newline();
		}
		pressAnyKey();
	}
	return NEVERMIND;
}
/* run a broadcast */
char run_broadcast(bool tv_broadcase)
{
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	setSiteAlarmOne();
	int enemy = 0;
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].exists&&encounter[e].alive)
		{
			if (encounter[e].align == -1)enemy++;
		}
	}
	if (enemy > 0)
	{
		clearmessagearea();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_THE_CONSERVATIVES_IN_THE_ROOM_HURRY_THE_SQUAD_SO, gamelog);
		mvaddstrAlt(17, 1, CONST_THE_BROADCAST_NEVER_HAPPENS, gamelog);
		gamelog.newline();
		pressAnyKey();
		return 0;
	}
	criminalizeparty(LAWFLAG_DISTURBANCE);
	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (tv_broadcase) {
		mvaddstrAlt(16, 1, CONST_THE_SQUAD_STEPS_IN_FRONT_OF_THE_CAMERAS_AND, gamelog);
	}
	else {
		mvaddstrAlt(16, 1, CONST_THE_SQUAD_TAKES_CONTROL_OF_THE_MICROPHONE_AND, gamelog);
	}
	int viewhit = LCSrandom(VIEWNUM);
	if (discussesIssues.count(viewhit)) {
		mvaddstrAlt(17, 1, discussesIssues[viewhit], gamelog);
	}
	else {
		mvaddstrAlt(17, 1, discussesIssues[VIEW_LIBERALCRIMESQUADPOS], gamelog);
	}
	gamelog.newline();
	pressAnyKey();
	int segmentpower = 0, partysize = activesquadAlive();
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (!activesquad->squad[p]->getNameAndAlignment().alive)continue;
			segmentpower += activesquad->squad[p]->get_attribute(ATTRIBUTE_INTELLIGENCE, true);
			segmentpower += activesquad->squad[p]->get_attribute(ATTRIBUTE_HEART, true);
			segmentpower += activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA, true);
			segmentpower += activesquad->squad[p]->get_skill(SKILL_MUSIC);
			segmentpower += activesquad->squad[p]->get_skill(SKILL_RELIGION);
			segmentpower += activesquad->squad[p]->get_skill(SKILL_SCIENCE);
			segmentpower += activesquad->squad[p]->get_skill(SKILL_BUSINESS);
			segmentpower += activesquad->squad[p]->get_skill(SKILL_PERSUASION);
			activesquad->squad[p]->train(SKILL_PERSUASION, 50);
		}
	}
	// LCS colors enhance the broadcast significantly
	if (tv_broadcase) {
		if (activesquad->stance == SQUADSTANCE_BATTLECOLORS)
			segmentpower = (segmentpower * 3) / 2;
	}
	int segmentbonus = segmentpower / 4;
	if (partysize > 1)segmentpower /= partysize;
	segmentpower += segmentbonus;
	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (tv_broadcase) {
		if (segmentpower < 25)mvaddstrAlt(16, 1, CONST_THE_SQUAD_LOOKS_COMPLETELY_INSANE, gamelog);
		else if (segmentpower < 35)mvaddstrAlt(16, 1, CONST_THE_SHOW_REALLY_SUCKS, gamelog);
		else if (segmentpower < 45)mvaddstrAlt(16, 1, CONST_IT_IS_A_VERY_BORING_HOUR, gamelog);
		else if (segmentpower < 55)mvaddstrAlt(16, 1, CONST_IT_IS_MEDIOCRE_TV, gamelog);
		else if (segmentpower < 70)mvaddstrAlt(16, 1, CONST_THE_SHOW_WAS_ALL_RIGHT, gamelog);
		else if (segmentpower < 85)mvaddstrAlt(16, 1, CONST_THE_SQUAD_PUT_ON_A_GOOD_SHOW, gamelog);
		else if (segmentpower < 100)mvaddstrAlt(16, 1, CONST_IT_WAS_THOUGHT_PROVOKING_EVEN_HUMOROUS, gamelog);
		else mvaddstrAlt(16, 1, CONST_IT_WAS_THE_BEST_HOUR_OF_CABLE_TV_EVER, gamelog);
	}
	else {
		if (segmentpower < 25)mvaddstrAlt(16, 1, CONST_THE_SQUAD_SOUNDS_WHOLLY_INSANE, gamelog);
		else if (segmentpower < 35)mvaddstrAlt(16, 1, CONST_THE_SHOW_REALLY_SUCKS, gamelog);
		else if (segmentpower < 45)mvaddstrAlt(16, 1, CONST_IT_IS_A_VERY_BORING_HOUR, gamelog);
		else if (segmentpower < 55)mvaddstrAlt(16, 1, CONST_IT_IS_MEDIOCRE_RADIO, gamelog);
		else if (segmentpower < 70)mvaddstrAlt(16, 1, CONST_THE_SHOW_WAS_ALL_RIGHT, gamelog);
		else if (segmentpower < 85)mvaddstrAlt(16, 1, CONST_THE_SQUAD_PUT_ON_A_GOOD_SHOW, gamelog);
		else if (segmentpower < 100)mvaddstrAlt(16, 1, CONST_IT_WAS_THOUGHT_PROVOKING_EVEN_HUMOROUS, gamelog);
		else mvaddstrAlt(16, 1, CONST_IT_WAS_THE_BEST_HOUR_OF_AM_RADIO_EVER, gamelog);
	}
	gamelog.newline();
	pressAnyKey();
	//CHECK PUBLIC OPINION
	change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	if (tv_broadcase) {
		change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, (segmentpower - 50) / 10);
		if (viewhit != VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit, (segmentpower - 50) / 5, 1);
		else change_public_opinion(viewhit, segmentpower / 10);
	}
	else {
		change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, (segmentpower - 50) / 2);
		if (viewhit != VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit, (segmentpower - 50) / 2, 1);
		else change_public_opinion(viewhit, segmentpower / 2);
	}
	//PRISONER PARTS
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->is_holding_body() && activesquad->squad[p]->is_prisoner_alive())
			{
				if (((activesquad->squad[p]->get_prisoner_type() == CREATURE_NEWSANCHOR) && tv_broadcase) || ((activesquad->squad[p]->get_prisoner_type() == CREATURE_RADIOPERSONALITY) && !tv_broadcase))
				{
					clearmessagearea();
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(16, 1, CONST_THE_HOSTAGE, gamelog);
					addstrAlt(activesquad->squad[p]->get_prisoner_name(), gamelog);
					addstrAlt(CONST_IS_FORCED_ON_TO, gamelog);
					viewhit = LCSrandom(VIEWNUM);
					if (discussIssues.count(viewhit)) {
						mvaddstrAlt(17, 1, discussIssues[viewhit], gamelog);
					}
					else {
						mvaddstrAlt(17, 1, discussIssues[VIEW_LIBERALCRIMESQUADPOS], gamelog);
					}
					gamelog.newline();
					int usegmentpower = 10; //FAME BONUS
					usegmentpower += activesquad->squad[p]->prisoner_usegment_power();
					if (tv_broadcase) {
						if (viewhit != VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit, (usegmentpower - 10) / 2);
						else change_public_opinion(viewhit, usegmentpower / 2, 1);
					}
					else {
						if (viewhit != VIEW_LIBERALCRIMESQUAD)change_public_opinion(viewhit, (usegmentpower - 10) / 2, 1, 80);
						else change_public_opinion(viewhit, usegmentpower / 2);
					}
					segmentpower += usegmentpower;
					pressAnyKey();
				}
				else
				{
					clearmessagearea();
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(16, 1, activesquad->squad[p]->get_prisoner_name(), gamelog);
					addstrAlt(CONST_THE_HOSTAGE_IS_KEPT_OFF_AIR, gamelog);
					gamelog.newline();
					pressAnyKey();
				}
			}
		}
	}
	if (sitealienate >= 1 && segmentpower >= 40)
	{
		sitealienate = 0;
		clearmessagearea();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_MODERATES_AT_THE_STATION_APPRECIATED_THE_SHOW, gamelog);
		gamelog.newline();
		mvaddstrAlt(17, 1, CONST_THEY_NO_LONGER_FEEL_ALIENATED, gamelog);
		gamelog.newline();
		pressAnyKey();
	}
	//POST-SECURITY BLITZ IF IT SUCKED
	if (((segmentpower < 85 && segmentpower >= 25) && tv_broadcase) || ((segmentpower < 90) && !tv_broadcase))
	{
		clearmessagearea();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_SECURITY_IS_WAITING_FOR_THE_SQUAD, gamelog);
		mvaddstrAlt(17, 1, CONST_AFTER_THE_SHOW, gamelog);
		gamelog.newline();
		pressAnyKey();
		int numleft = LCSrandom(8) + 2;
		fillEncounter(CREATURE_SECURITYGUARD, numleft);
	}
	else
	{
		clearmessagearea();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		if (tv_broadcase) {
			mvaddstrAlt(16, 1, CONST_THE_SHOW_WAS_SO, gamelog);
			if (segmentpower < 50)
				addstrAlt(CONST_HILARIOUS, gamelog);
			else
				addstrAlt(CONST_ENTERTAINING, gamelog);
			addstrAlt(CONST_THAT_SECURITY_WATCHED_IT, gamelog);
		}
		else {
			mvaddstrAlt(16, 1, CONST_THE_SHOW_WAS_SO_GOOD_THAT_SECURITY_LISTENED_TO_IT, gamelog);
		}
		mvaddstrAlt(17, 1, CONST_AT_THEIR_DESKS_THE_SQUAD_MIGHT_YET_ESCAPE, gamelog);
		gamelog.newline();
		pressAnyKey();
	}
	return 1;
}
/* rescues people held at the activeparty's current location */
void partyrescue(short special)
{
	int freeslots = 0;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL)freeslots++;
	}
	int hostslots = 0;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->getNameAndAlignment().alive&&!activesquad->squad[p]->is_holding_body())
			{
				hostslots++;
			}
		}
	}
	vector<DeprecatedCreature*> waiting_for_rescue;

	whoAreWaitingForRescue(waiting_for_rescue, getCurrentSite(), special);
	for (int pl = 0; pl < len(waiting_for_rescue); pl++)
	{
		if (LCSrandom(2) && freeslots)
		{
			for (int p = 0; p < 6; p++)
			{
				if (activesquad->squad[p] == NULL)
				{
					activesquad->squad[p] = waiting_for_rescue[pl];
					activesquad->squad[p]->squadid = activesquad->id;
					criminalize(*activesquad->squad[p], LAWFLAG_ESCAPED);
					activesquad->squad[p]->flag |= CREATUREFLAG_JUSTESCAPED;
					break;
				}
			}
			hostslots++;
			freeslots--;
			clearmessagearea();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, CONST_YOU_VE_RESCUED, gamelog);
			addstrAlt(waiting_for_rescue[pl]->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_FROM_THE_CONSERVATIVES, gamelog);
			gamelog.newline();
			printparty();
			pressAnyKey();
			waiting_for_rescue[pl]->location = -1;
			waiting_for_rescue[pl]->base = activesquad->squad[0]->base;
			waiting_for_rescue.erase(waiting_for_rescue.begin() + pl);
			--pl;
		}
	}
	for (int pl = 0; pl < len(waiting_for_rescue); pl++)
	{
		if (hostslots)
		{
			for (int p = 0; p < 6; p++)
			{
				if (activesquad->squad[p] != NULL)
				{
					if (activesquad->squad[p]->getNameAndAlignment().alive&&!activesquad->squad[p]->is_holding_body())
					{
						activesquad->squad[p]->make_prisoner(waiting_for_rescue[pl]);
						waiting_for_rescue[pl]->squadid = activesquad->id;
						criminalize(*waiting_for_rescue[pl], LAWFLAG_ESCAPED);
						waiting_for_rescue[pl]->flag |= CREATUREFLAG_JUSTESCAPED;
						clearmessagearea();
						set_color_easy(WHITE_ON_BLACK_BRIGHT);
						mvaddstrAlt(16, 1, CONST_YOU_VE_RESCUED, gamelog);
						addstrAlt(waiting_for_rescue[pl]->getNameAndAlignment().name, gamelog);
						addstrAlt(CONST_FROM_THE_CONSERVATIVES, gamelog);
						gamelog.newline();
						pressAnyKey();
						clearmessagearea();
						mvaddstrAlt(16, 1, waiting_for_rescue[pl]->getNameAndAlignment().name, gamelog);
						addstrAlt(singleSpace, gamelog);
						addstrAlt(pickrandom(was_abused), gamelog);
						mvaddstrAlt(17, 1, CONST_SO, gamelog);
						addstrAlt(activesquad->squad[p]->getNameAndAlignment().name, gamelog);
						addstrAlt(CONST_WILL_HAVE_TO_HAUL_A_LIBERAL, gamelog);
						gamelog.newline();
						waiting_for_rescue[pl]->location = -1;
						waiting_for_rescue[pl]->base = activesquad->squad[p]->base;
						printparty();
						pressAnyKey();
						waiting_for_rescue.erase(waiting_for_rescue.begin() + pl);
						--pl;
						break;
					}
				}
			}
			hostslots--;
		}
		if (!hostslots)break;
	}
	if (len(waiting_for_rescue) == 1)
	{
		clearmessagearea();
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_THERE_S_NOBODY_LEFT_TO_CARRY, gamelog);
		addstrAlt(waiting_for_rescue[0]->getNameAndAlignment().name, gamelog);
		addstrAlt(singleDot, gamelog);
		gamelog.newline();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(17, 1, CONST_YOU_LL_HAVE_TO_COME_BACK_LATER, gamelog);
		gamelog.newline();
		pressAnyKey();
	}
	else if (len(waiting_for_rescue) > 1)
	{
		clearmessagearea();
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_THERE_S_NOBODY_LEFT_TO_CARRY_THE_OTHERS, gamelog);
		gamelog.newline();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(17, 1, CONST_YOU_LL_HAVE_TO_COME_BACK_LATER, gamelog);
		gamelog.newline();
		pressAnyKey();
	}
}
/* everybody reload! */
void reloadparty(bool wasteful)
{
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL)continue;
		if (!activesquad->squad[p]->getNameAndAlignment().alive)continue;
		if (activesquad->squad[p]->has_thrown_weapon)
		{
			activesquad->squad[p]->ready_another_throwing_weapon();
		}
		else if (activesquad->squad[p]->can_reload())
		{
			activesquad->squad[p]->reload(wasteful);
		}
	}
}