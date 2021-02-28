


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
//TODO: This file probably shouldn't have any nextMessage calls in it.
//That will depend on the chase and fight code, I think...And the code that
//handles the squad moving around the site. For now, this'll do. I must remember
//to come back here and finish the job.

#include "../includes61.h"
#include "../constStringhaulkidnap.h"
void printKidnapString(const string aname, const string tname, const string weapon) {


	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(CONST_SHOWS, gamelog);
	addstrAlt(tname, gamelog);
	addstrAlt(CONST_X_THE_, gamelog);
	addstrAlt(weapon, gamelog);
	addstrAlt(singleSpace, gamelog);
	mvaddstrAlt(17, 1, CONST_AND_SAYS, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	if (lawList[LAW_FREESPEECH] == -2) { 
		addstrAlt(CONST_PLEASE_BE_COOL, gamelog);
	}
	else { 
		addstrAlt(CONST_BITCH_BE_COOL, gamelog);
	}
	pressAnyKey();
	gamelog.newline();

}
void printFailedKidnapString(const string aname, const string tname) {

	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(CONST_GRABS_AT, gamelog);
	addstrAlt(tname, gamelog);
	gamelog.newline(); //New line.
	mvaddstrAlt(17, 1, CONST_BUT, gamelog);
	addstrAlt(tname, gamelog);
	addstrAlt(CONST_WRITHES_AWAY, gamelog);
	gamelog.newline(); //New line.
	pressAnyKey();
	gamelog.newline();

}
void printAmateurKidnapString(const string aname, const string tname) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(CONST_SNATCHES, gamelog);
	addstrAlt(tname, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.newline(); //New line.
	pressAnyKey();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, tname, gamelog);
	addstrAlt(CONST_IS_STRUGGLING_AND_SCREAMING, gamelog);
	gamelog.newline(); //New line.
	pressAnyKey();
	gamelog.newline();

}
/* roll on the kidnap attempt and show the results */
bool attemptKidnap(DeprecatedCreature &a, DeprecatedCreature &t, const bool amateur)
{
	if (amateur)
	{
		//BASIC ROLL
		int aroll = a.skill_roll(SKILL_HANDTOHAND);
		int droll = t.attribute_check(ATTRIBUTE_AGILITY, true);
		a.train(SKILL_HANDTOHAND, droll);
		clearmessagearea();
		//HIT!
		if (aroll > droll)
		{
			printAmateurKidnapString(a.getNameAndAlignment().name, t.getNameAndAlignment().name);

			return 1;
		}
		else
		{
			printFailedKidnapString(a.getNameAndAlignment().name, t.getNameAndAlignment().name);

			return 0;
		}
	}
	else
	{
		printKidnapString(a.getNameAndAlignment().name, t.getNameAndAlignment().name, a.get_weapon().get_name(2));

		return 1;
	}
}
/* hostage freed due to host unable to haul */
void freehostage(DeprecatedCreature &cr, char situation)
{
	if (!cr.is_holding_body())return;
	if (cr.is_prisoner_alive())
	{
		if (situation == 0)
		{
			if (cr.is_prisoner_non_LCS())addstrAlt(CONST_AND_A_HOSTAGE_IS_FREED, gamelog);
			else
			{
				addstrAlt(AND, gamelog);
				addstrAlt(cr.get_prisoner_name(), gamelog);
				if (cr.prisoner->flag & CREATUREFLAG_JUSTESCAPED)addstrAlt(CONST_IS_RECAPTURED, gamelog);
				else addstrAlt(CONST_IS_CAPTURED, gamelog);
			}
			gamelog.newline(); //New line.
		}
		else if (situation == 1)
		{
			clearmessagearea();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			if (cr.is_prisoner_non_LCS())mvaddstrAlt(16, 1, CONST_A_HOSTAGE_ESCAPES, gamelog);
			else
			{
				mvaddstrAlt(16, 1, cr.get_prisoner_name(), gamelog);
				if (cr.prisoner->flag & CREATUREFLAG_JUSTESCAPED)addstrAlt(CONST_X_IS_RECAPTURED, gamelog);
				else addstrAlt(CONST_X_IS_CAPTURED, gamelog);
			}
			gamelog.newline(); //New line.
		}
		else if (situation == 2)
		{
			//Don't print anything.
		}
		if (cr.is_prisoner_non_LCS())
		{
			for (int e = 0; e < ENCMAX; e++)
			{
				if (encounter[e].getNameAndAlignment().exists == 0)
				{
					encounter[e] = *cr.prisoner;
					encounter[e].make_existing();
					conservatise(e);
					break;
				}
			}
			cr.delete_prisoner();
		}
		else capturecreature(*cr.prisoner);
	}
	else
	{
		if (!cr.is_prisoner_non_LCS())
		{
			cr.prisoner_dies();
		}
	}
	cr.discard_body();
	if (situation == 1)
	{
		printparty();
		if (mode == GAMEMODE_CHASECAR ||
			mode == GAMEMODE_CHASEFOOT) printchaseencounter();
		else printencounter();
		pressAnyKey();
	}
}
bool reconsiderKidnapping(const string name) {
	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 1, name);
	addstrAlt(CONST_IS_THE_ONLY_VIABLE_TARGET);
	mvaddstrAlt(12, 1, CONST_STILL_KIDNAP_Y_N);
	int c = pressSpecificKey('y', 'n');
	if (c == 'n') {
		return true;
	}
	else
		return false;
}
void amateurKidnapping(const int kidnapper, const int t) {

	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();

	alienationcheck(1);
	if (!isThereASiteAlarm())setSiteAlarmOne();
	sitecrime += 5;
	criminalizeparty(LAWFLAG_KIDNAPPING);
	if (activesquad->squad[kidnapper]->is_holding_body())
	{
		if (activesquad->squad[kidnapper]->get_prisoner_type() == CREATURE_RADIOPERSONALITY) offended_amradio = 1;
		if (activesquad->squad[kidnapper]->get_prisoner_type() == CREATURE_NEWSANCHOR) offended_cablenews = 1;
	}
	else
	{
		if (encounter[t].type == CREATURE_RADIOPERSONALITY) offended_amradio = 1;
		if (encounter[t].type == CREATURE_NEWSANCHOR) offended_cablenews = 1;
	}
}
/* prompt after you've said you want to kidnap someone */
void kidnapattempt()
{
	short kidnapper = -1;
	party_status = -1;
	int available = 0;
	char availslot[6] = { 0,0,0,0,0,0 };
	for (int p = 0; p < 6; p++) {
		if (activesquad->squad[p] != NULL) {
			if (activesquad->squad[p]->getCreatureHealth().alive&&!activesquad->squad[p]->is_holding_body())
			{
				available++;
				availslot[p] = 1;
			}
		}
	}
	if (!available)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_NO_ONE_CAN_DO_THE_JOB);
		mvaddstrAlt(17, 1, CONST_X_SOME_WHITESPACE);
		pressAnyKey();
		return;
	}
	do
	{
		printparty();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 20, CHOOSE_A_LIBERAL_TO + CONST_DO_THE_JOB);
		int c = getkeyAlt();
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) return;
		if (c >= '1'&&c <= '6')
			if (availslot[c - '1'])
				kidnapper = c - '1';
	} while (kidnapper < 0);
	vector<int> target;
	bool possibleMistakeToKidnap = false;
	for (int e = 0; e < ENCMAX; e++) {
		if (encounter[e].getNameAndAlignment().exists&&encounter[e].getCreatureHealth().alive&&encounter[e].getCreatureHealth().align == -1 &&
			(encounter[e].getCreatureHealth().animalgloss == ANIMALGLOSS_NONE || lawList[LAW_ANIMALRESEARCH] == 2) &&
			(!encounter[e].get_weapon().get_specific_bool(BOOL_PROTECTS_AGAINST_KIDNAPPING_) ||
				encounter[e].getCreatureHealth().blood <= 20) && encounter[e].getCreatureHealth().animalgloss != ANIMALGLOSS_TANK)
			target.push_back(e);

		if (encounter[e].get_weapon().get_specific_bool(BOOL_PROTECTS_AGAINST_KIDNAPPING_)) {
			possibleMistakeToKidnap = true;
		}
	}
	if (len(target))
	{
		int t = target[0];
		if (len(target) > 1)
		{
			clearcommandarea();
			clearmessagearea();
			clearmaparea();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(9, 1, CONST_KIDNAP_WHOM);
			int x = 1, y = 11;
			for (int t2 = 0; t2 < len(target); t2++)
			{
				mvaddcharAlt(y++, x, t2 + 'A');
				addstrAlt(spaceDashSpace);
				addstrAlt(encounter[target[t2]].getNameAndAlignment().name);
				if (y == 17) y = 11, x += 30;
			}
			do
			{
				int c = getkeyAlt();
				if (c >= 'a'&&c < ('a' + ENCMAX))
				{
					t = c - 'a';
					if (t >= len(target)) t = -1;
					else t = target[t];
				}
				if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) return;
			} while (t < 0);
		}
		else
			// Special case: More than one conservative, but only one can be kidnapped
			if (len(target) == 1 && possibleMistakeToKidnap) {
				if (reconsiderKidnapping(encounter[target[0]].getNameAndAlignment().name)) {
					return;
				}
			}



		bool crappy_weapon = !(activesquad->squad[kidnapper]->get_weapon().get_specific_bool(BOOL_CAN_TAKE_HOSTAGES_));

		if (

			attemptKidnap(*activesquad->squad[kidnapper], encounter[t], crappy_weapon)
			
			)
		{
			activesquad->squad[kidnapper]->make_new_prisoner(encounter[t]);
			delenc(t, 0);
			int time = 20 + LCSrandom(10);
			if (time < 1) time = 1;
			if (sitealarmtimer > time || sitealarmtimer == -1) sitealarmtimer = time;
		}
		else { 
			setSiteAlarmOne();
		}

		if (crappy_weapon)
		{
			bool present = 0;
			for (int e = 0; e < ENCMAX; e++) {
				if (encounter[e].getNameAndAlignment().exists&&encounter[e].getCreatureHealth().alive) {
					present = 1;
					break;
				}
			}
			if (present)
			{
				amateurKidnapping(kidnapper, t);
			}
		}

		if (isThereASiteAlarm()) enemyattack();
		creatureadvance();
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_ALL_OF_THE_TARGETS_ARE_TOO_DANGEROUS);
		mvaddstrAlt(17, 1, CONST_X_MUCH_WHITESPACE);
		pressAnyKey();
	}
}
/* prompt after you've said you want to release someone */
void releasehostage()
{
	short kidnapper = -1;
	party_status = -1;
	int available = 0;
	char availslot[6] = { 0,0,0,0,0,0 };
	for (int p = 0; p < 6; p++)
		if (activesquad->squad[p] != NULL)
			if (activesquad->squad[p]->getCreatureHealth().alive&&activesquad->squad[p]->is_holding_body() && activesquad->squad[p]->get_prisoner_align() != ALIGN_LIBERAL)
				available++, availslot[p] = 1;
	if (!available)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_NO_HOSTAGES_ARE_BEING_HELD);
		mvaddstrAlt(17, 1, CONST_X_SOME_WHITESPACE);
		pressAnyKey();
		return;
	}
	do
	{
		printparty();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 20, CHOOSE_A_LIBERAL_TO + CONST_RELEASE_THEIR_HOSTAGE);
		int c = getkeyAlt();
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) return;
		if (c >= '1'&&c <= '6')
			if (availslot[c - '1'])
				kidnapper = c - '1';
	} while (kidnapper < 0);
	activesquad->squad[kidnapper]->make_prisoner_cantbluff_two();
	freehostage(*(activesquad->squad[kidnapper]), 2);
	if (!isThereASiteAlarm())
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_THE_HOSTAGE_SHOUTS_FOR_HELP, gamelog);
		gamelog.nextMessage(); //Next message.
		mvaddstrAlt(17, 1, CONST_X_SOME_WHITESPACE);
		pressAnyKey();
		setSiteAlarmOne();
		alienationcheck(1);
	}
}
/* haul dead/paralyzed */
void squadgrab_immobile(char dead)
{
	int hostslots = 0; //DRAGGING PEOPLE OUT IF POSSIBLE
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->getCreatureHealth().alive &&
				(activesquad->squad[p]->canwalk() ||
				(activesquad->squad[p]->flag & CREATUREFLAG_WHEELCHAIR)) &&
				!activesquad->squad[p]->is_holding_body())
				hostslots++;
			else if ((!activesquad->squad[p]->getCreatureHealth().alive ||
				(!activesquad->squad[p]->canwalk() &&
					!(activesquad->squad[p]->flag & CREATUREFLAG_WHEELCHAIR))) &&
				activesquad->squad[p]->is_holding_body())
			{
				clearmessagearea();
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_CAN_NO_LONGER_HANDLE, gamelog);
				addstrAlt(activesquad->squad[p]->get_prisoner_name(), gamelog);
				addstrAlt(singleDot, gamelog);
				gamelog.newline(); //New line.
				pressAnyKey();
				activesquad->squad[p]->drop_prisoner();
			}
		}
	}
	for (int p = 5; p >= 0; p--)
	{
		if (activesquad->squad[p] != NULL)
		{
			if ((!activesquad->squad[p]->getCreatureHealth().alive&&dead) ||
				(activesquad->squad[p]->getCreatureHealth().alive &&
					!(activesquad->squad[p]->flag & CREATUREFLAG_WHEELCHAIR) &&
					!activesquad->squad[p]->canwalk() && !dead))
			{
				if (hostslots == 0)
				{
					if (!activesquad->squad[p]->getCreatureHealth().alive)
					{
						clearmessagearea();
						set_color_easy(YELLOW_ON_BLACK_BRIGHT);
						mvaddstrAlt(16, 1, CONST_NOBODY_CAN_CARRY_MARTYR, gamelog);
						addstrAlt(activesquad->squad[p]->getNameAndAlignment().name, gamelog);
						addstrAlt(singleDot, gamelog);
						gamelog.newline();
						//DROP LOOT
						makeloot(*activesquad->squad[p]);
						activesquad->squad[p]->die();
						activesquad->squad[p]->location = -1;
					}
					else
					{
						clearmessagearea();
						set_color_easy(YELLOW_ON_BLACK_BRIGHT);
						mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
						addstrAlt(CONST_IS_LEFT_TO_BE_CAPTURED, gamelog);
						gamelog.newline(); //New line.
						capturecreature(*activesquad->squad[p]);
					}
				}
				else
				{
					for (int p2 = 0; p2 < 6; p2++)
					{
						if (p2 == p) continue;
						if (activesquad->squad[p2] != NULL)
						{
							if (activesquad->squad[p2]->getCreatureHealth().alive &&
								(activesquad->squad[p2]->canwalk() ||
								(activesquad->squad[p2]->flag & CREATUREFLAG_WHEELCHAIR)) &&
								!activesquad->squad[p2]->is_holding_body())
							{
								activesquad->squad[p2]->make_prisoner( activesquad->squad[p]);
								clearmessagearea();
								set_color_easy(YELLOW_ON_BLACK_BRIGHT);
								mvaddstrAlt(16, 1, activesquad->squad[p2]->getNameAndAlignment().name, gamelog);
								addstrAlt(CONST_HAULS, gamelog);
								addstrAlt(activesquad->squad[p]->getNameAndAlignment().name, gamelog);
								addstrAlt(singleDot, gamelog);
								gamelog.newline(); //New line.
								break;
							}
						}
					}
					hostslots--;
				}
				//SHUFFLE SQUAD
				bool flipstart = 0;
				for (int pt = 0; pt < 6; pt++)
				{
					if (pt == p - 1) continue;
					if (pt == p) flipstart = 1;
					if (flipstart&&pt < 5) activesquad->squad[pt] = activesquad->squad[pt + 1];
				}
				if (flipstart) activesquad->squad[5] = NULL;
				printparty();
				pressAnyKey();
			}
		}
	}
}