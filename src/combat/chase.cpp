


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
#include "../includes63.h"
#include "../constStringchase.h"
#include <algorithm>
void fillEncounter(CreatureTypes c, int numleft) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	for (int e = 0; e < ENCMAX; e++)
	{
		if (!encounter[e].exists)
		{
			make_creature_without_encounter_array(e, c);
			numleft--;
		}
		if (numleft == 0)break;
	}
}
void chase_giveup()
{
	int ps = find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION, chaseseq.location);
	deleteVehicles(chaseseq.friendcar);
	int hostagefreed = 0;
	for (int p = 0; p < 6; p++)
	{
		if (!activesquad->squad[p]) continue;
		activesquad->squad[p]->squadid = -1;
		activesquad->squad[p]->carid = -1;
		activesquad->squad[p]->location = ps;
		activesquad->squad[p]->drop_weapons_and_clips(NULL);
		activesquad->squad[p]->set_activity_type(ACTIVITY_NONE);
		if (activesquad->squad[p]->is_holding_body())
		{
			if (activesquad->squad[p]->is_prisoner_non_LCS()) hostagefreed++;
			freehostage(*activesquad->squad[p], 2);
		}
		activesquad->squad[p] = NULL;
	}
	CreaturePool::getInstance().stopAllBleeding();
	clearmessagearea();
	clearcommandarea();
	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	moveAlt(16, 1);
	if (mode != GAMEMODE_CHASECAR)addstrAlt(YOU_STOP_AND_ARE_ARRESTED, gamelog);
	else addstrAlt(YOU_PULL_OVER_AND_ARRESTED, gamelog);
	gamelog.newline(); //New line.
	if (hostagefreed)
	{
		mvaddstrAlt(17, 1, YOUR_HOSTAGE, gamelog);
		if (hostagefreed > 1)
			addstrAlt(S_ARE_FREE, gamelog);
		else addstrAlt(IS_FREE, gamelog);
		gamelog.newline(); //New line.
	}
	pressAnyKey();
}
void printSemiRandomEscape(const int yourworst) {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	string output;
	switch (LCSrandom(yourworst / 5))
	{
	default:
		output = YOU_SUDDENLY_DART_INTO_ALLEY;
		break;
	case 1:
		output = YOU_RUN_AS_FAST_AS_YOU_CAN;
		break;
	case 2:
		output = YOU_CLIMB_A_FENCE;
		break;
	case 3:
		output = YOU_SCALE_A_SMALL_BUILDING;
		break;
	}
	mvaddstrAlt(16, 1, output, gamelog);
	gamelog.newline(); //New line.
	pressAnyKey();
}
void tankPlowsThrough(const int e) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	clearmessagearea();
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, encounter[e].name, gamelog);
	addstrAlt(singleSpace, gamelog);
	addstrAlt(pickrandom(car_plows_through), gamelog);
	pressAnyKey();
}
string isCapturedByCop(const int p) {

	string output = activesquad->squad[p]->getNameAndAlignment().name + isSeized;
	if (lawList[LAW_POLICEBEHAVIOR] >= ALIGN_LIBERAL)
	{
		output += PUSHED_TO_GROUND_HANDCUFFED;
	}
	else
	{
		if (activesquad->squad[p]->getCreatureHealth().blood <= 10)
		{
			output += THROWN_TO_GROUND_TAZED_TO_DEATH;
		}
		else
		{
			output += THROWN_TO_GROUND_AND_TAZED;
		}
		activesquad->squad[p]->lose_blood(10);
	}
	return output;
}
string isSummaryExecuted(const int p) {



	string output = activesquad->squad[p]->getNameAndAlignment().name + isSeized;

	output += isSeized;
	output += THROWN_TO_GROUND_AND_SHOT;
	activesquad->squad[p]->lose_all_blood();

	return output;
}
string isCrushedByTank(const int p) {



	string output = activesquad->squad[p]->getNameAndAlignment().name + CRUSHED_BENEATH_TANK;

	activesquad->squad[p]->lose_all_blood();

	return output;
}
string isCapturedByOther(const int p) {



	string output = activesquad->squad[p]->getNameAndAlignment().name + isSeized;

	output += isSeized;
	if (activesquad->squad[p]->getCreatureHealth().blood <= 60)
	{
		output += THROWN_TO_GROUND_AND_BEATEN_DEAD;
	}
	else
	{
		output += THROWN_TO_GROUND_AND_BEATEN_SENSELESS;
	}
	activesquad->squad[p]->lose_blood(60);

	return output;
}
void evasiverun()
{
	vector<int> yourspeed;
	yourspeed.resize(6);
	int yourworst = 10000, yourbest = 0, wheelchair = 0, notwheelchair = 0, theirbest = 0, theirworst = 10000;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL) continue;
		if (activesquad->squad[p]->getCreatureHealth().alive)
		{
			if (activesquad->squad[p]->flag & CREATUREFLAG_WHEELCHAIR)
			{
				yourspeed[p] = 0;
				wheelchair++;
			}
			else
			{
				yourspeed[p] = activesquad->squad[p]->attribute_roll(ATTRIBUTE_AGILITY) +
					activesquad->squad[p]->attribute_roll(ATTRIBUTE_HEALTH);
				//healthmodroll(yourspeed[p],*activesquad->squad[p]);
				notwheelchair++;
			}
			if (yourworst > yourspeed[p]) yourworst = yourspeed[p];
			if (yourbest < yourspeed[p]) yourbest = yourspeed[p];
		}
	}
	if (yourworst > 14)
	{
		yourworst += LCSrandom(5);
		printSemiRandomEscape(yourworst);
	}
	for (int e = 0; e < ENCMAX; e++)
	{
		if (!encounter[e].getNameAndAlignment().exists) continue;
		int chaser = encounter[e].attribute_roll(ATTRIBUTE_AGILITY) +
			encounter[e].attribute_roll(ATTRIBUTE_HEALTH);
		//healthmodroll(chaser,encounter[e]);
		if (theirbest < chaser) theirbest = chaser;
		if (theirworst > chaser) theirworst = chaser;
		if (encounter[e].type == CREATURE_TANK && LCSrandom(10))
		{
			tankPlowsThrough(e);
		}
		else if (chaser < yourworst)
		{
			clearmessagearea();
			set_color_easy(CYAN_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, encounter[e].getNameAndAlignment().name, gamelog);
			if (encounter[e].type == CREATURE_TANK)
			{
				addstrAlt(TIPS_INTO_A_POOL_TANK_IS_TRAPPED, gamelog);
				gamelog.newline(); //New line.
			}
			else
			{
				addstrAlt(CANT_KEEP_UP, gamelog);
				gamelog.newline(); //Another new line.
			}
			delenc(e--, 0);
			printchaseencounter();
			pressAnyKey();
		}
		else
		{
			clearmessagearea();
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, encounter[e].getNameAndAlignment().name, gamelog);
			addstrAlt(IS_STILL_ON_YOUR_TAIL, gamelog);
			gamelog.newline(); //New line.
			pressAnyKey();
		}
	}
	//This last loop can be used to have fast people in
	//your squad escape one by one just as the enemy
	//falls behind one by one
	int othersleft = 0;
	for (int p = 5; p >= 0; p--)
	{
		if (!encounter[0].getNameAndAlignment().exists) break;
		if (activesquad->squad[p] == NULL) continue;
		if (activesquad->squad[p]->getCreatureHealth().alive)
		{
			if (yourspeed[p] > theirbest)
			{
				if (p == 0 && othersleft == 0) break;
				clearmessagearea();
				set_color_easy(CYAN_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(BREAKS_AWAY, gamelog);
				gamelog.newline(); //New line.
				pressAnyKey();
				//Unload hauled hostage or body when they get back to the safehouse
				if (activesquad->squad[p]->is_holding_body())
				{
					activesquad->squad[p]->deal_with_prisoner();
				}
				removesquadinfo(*activesquad->squad[p]);
				printparty();
			}
			else if (yourspeed[p] < theirbest - 10)
			{
				clearmessagearea();
				set_color_easy(CYAN_ON_BLACK_BRIGHT);
				string squadmemberSubdued;
				switch (encounter[0].type)
				{
				case CREATURE_COP:
					squadmemberSubdued = isCapturedByCop(p);
					break;
				case CREATURE_DEATHSQUAD:
					squadmemberSubdued = isSummaryExecuted(p);
					break;
				case CREATURE_TANK:
					squadmemberSubdued = isCrushedByTank(p);
					break;
				default:
					squadmemberSubdued = isCapturedByOther(p);
					break;
				}
				mvaddstrAlt(16, 1, squadmemberSubdued, gamelog);
				gamelog.newline(); //New line.
				if (activesquad->squad[p]->getCreatureHealth().blood <= 0)
					activesquad->squad[p]->die();
				capturecreature(*activesquad->squad[p]);
				for (int i = p + 1, j = p; i < 6; i++, j++)
					activesquad->squad[j] = activesquad->squad[i];
				activesquad->squad[5] = NULL;
				// Death squads don't mess around, and don't fall behind when executing your people
				// Tanks don't stop either.
				if (encounter[0].type != CREATURE_DEATHSQUAD &&
					encounter[0].type != CREATURE_TANK)delenc(0, 0);
				printparty();
				printchaseencounter();
				pressAnyKey();
			}
			else othersleft++;
		}
	}
}
void printDrivingSituation(const int partysize) {

	//PRINT DRIVING SITUATION AND INSTRUCTIONS
	if (partysize > 1) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 40, O_CHANGE_SQUAD_ORDER);
	if (partysize > 0 && (party_status == -1 || partysize > 1))set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 40, HASH_CHECK_STATUS_OF_LIBERAL);
	if (party_status != -1)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 40, show_squad_liberal_status);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 1, D_TRY_TO_LOSE_THEM);
	mvaddstrAlt(10, 1, E_EQUIP);
	mvaddstrAlt(11, 1, F_FIGHT);
	if (chaseseq.canpullover)
	{
		mvaddstrAlt(12, 1, CONST_X_G_GIVE_UP);
	}
}
void destroyAllCarsOfParty() {

	//DESTROY ALL CARS BROUGHT ALONG WITH PARTY
	deleteVehicles(chaseseq.friendcar);
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL)continue;
		activesquad->squad[p]->die();
		activesquad->squad[p]->location = -1;
		activesquad->squad[p] = NULL;
	}
	endcheck(END_BUT_NOT_END); // play the right music in case we're dead
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 1, C_REFLECT_ON_YOUR_LACK_OF_SKILL);
}

void addNewLineIfFoughtThisRound();
LOOP_CONTINUATION increment_footchase() {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int partysize = activesquadSize(), partyalive = activesquadAlive();
	int encsize = encounterSize();
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, LocationsPool::getInstance().getLocationName(chaseseq.location));
	//PRINT PARTY
	if (partyalive == 0) party_status = -1;
	printparty();
	if (partyalive > 0)
	{
		printDrivingSituation(partysize);
	}
	else
	{
		destroyAllCarsOfParty();
	}
	//PRINT ENEMIES
	printchaseencounter();
	// check if we fought the previous loop; if so, add a blank gamelog line
	
	addNewLineIfFoughtThisRound();

	int c = getkeyAlt();
	if (partyalive == 0 && c == 'c')
	{
		if (!endcheck())
		{
			return RETURN_ZERO;
		}
	}
	if (partyalive > 0)
	{
		switch (c) {
		case 'g':
			if (chaseseq.canpullover)
			{
				chase_giveup();
				return RETURN_ZERO;
			}
			break;

		case 'd':
			if (encounter[0].exists&&
				encounter[0].type == CREATURE_COP)
			{
				sitestory->crime.push_back(CRIME_FOOTCHASE);
				criminalizeparty(LAWFLAG_RESIST);
			}
			evasiverun();
			enemyattack();
			creatureadvance();
			break;

		case 'o':
			if (partysize > 1) orderparty();
			break;

		case '0':
			party_status = -1;
			break;
		case 'f':
			if (encounter[0].exists&&
				encounter[0].type == CREATURE_COP)
			{
				sitestory->crime.push_back(CRIME_FOOTCHASE);
				criminalizeparty(LAWFLAG_RESIST);
			}
			youattack();
			enemyattack();
			creatureadvance();
			break;

		case 'e':

			equip(activesquad->loot, -1);
			break;
		default:
			if (c >= '1'&&c <= '6')
			{
				if (activesquad->squad[c - '1'] != NULL)
				{
					if (party_status == c - '1') fullstatus(party_status);
					else party_status = c - '1';
				}
			}
			break;

		}


		//HAVE YOU LOST ALL OF THEM?
		//THEN LEAVE
		partysize = activesquadSize(), partyalive = activesquadAlive();
		int baddiecount = baddieCount();
		if (partyalive > 0 && baddiecount == 0)
		{
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			clearmessagearea();
			mvaddstrAlt(16, 1, lostThem, gamelog);
			gamelog.newline(); //New line.
			pressAnyKey();
			CreaturePool::getInstance().stopAllBleeding();
			return RETURN_ONE;
		}
	}
	return REPEAT;
}
bool footchase()
{
	//NOTE: THIS FUNCTION RETURNS 1 IF ANYBODY ESCAPES
	//IT SHOULD NOT DELETE SQUADS OR CREATURES
	//SQUADS MAY BE FICTITIOUS AND BOTH WILL BE DELETED LATER ANYWAY
	reloadparty();
	//NUKE ALL CARS
	delete_and_clear(chaseseq.enemycar);
	//BAIL IF NO CHASERS
	int chasenum = 0;
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].getNameAndAlignment().exists) chasenum++;
		encounter[e].carid = -1;
	}
	if (chasenum == 0) return 1;
	mode = GAMEMODE_CHASEFOOT;
	music.play(MUSIC_FOOTCHASE);
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, AS_YOU_EXIT_YOU_NOTICE, gamelog);
	moveAlt(1, 0);
	gamelog.newline(); //New line.
	addstrAlt(BEING_FOLLOWED, gamelog);
	gamelog.newline(); //New line.
	pressAnyKey();
	while (true) {
		LOOP_CONTINUATION x = increment_footchase();
		if (x == RETURN_ZERO) {
			mode = GAMEMODE_BASE;
			//Make sure all possible exits of the chase have the nextMessage() call
			//to ensure that the gamelog is split properly into blocks.
			gamelog.nextMessage();
			return 0;
		}
		else if (x == RETURN_ONE) {
			mode = GAMEMODE_BASE;
			//Make sure all possible exits of the chase have the nextMessage() call
			//to ensure that the gamelog is split properly into blocks.
			gamelog.nextMessage();
			return 1;
		}
	}
}
int driveskill(DeprecatedCreature &cr, Vehicle &v)
{
	int driveskill = cr.skill_roll(PSEUDOSKILL_ESCAPEDRIVE);
	healthmodroll(driveskill, cr);
	if (driveskill < 0) driveskill = 0;
	driveskill *= static_cast<int>(cr.getCreatureHealth().blood / 50.0);
	return driveskill;
}
void evasivedrive()
{
	vector<long> yourrolls, theirrolls, theirrolls_id, theirrolls_drv;
	long yourworst = 10000;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL) continue;
		if (activesquad->squad[p]->getCreatureHealth().alive&&
			activesquad->squad[p]->is_driver)
		{
			int v = id_getcar(activesquad->squad[p]->carid);
			yourrolls.push_back(driveskill(*activesquad->squad[p], v) + LCSrandom(DRIVING_RANDOMNESS));
			switch (fieldskillrate)
			{
			case FIELDSKILLRATE_FAST:
				activesquad->squad[p]->train(SKILL_DRIVING, LCSrandom(20)); break;
			case FIELDSKILLRATE_CLASSIC:
				activesquad->squad[p]->train(SKILL_DRIVING, LCSrandom(20)); break;
			case FIELDSKILLRATE_HARD:
				activesquad->squad[p]->train(SKILL_DRIVING, LCSrandom(max(1, 20 - activesquad->squad[p]->get_skill(SKILL_DRIVING)))); break;
			}
			if (yourworst > yourrolls.back()) yourworst = yourrolls.back();
		}
	}
	if (!len(yourrolls)) yourrolls.push_back(0); //error -- and for this you get a 0
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].carid != -1 &&
			encounter[e].enemy() &&
			encounter[e].getCreatureHealth().alive&&
			encounter[e].getNameAndAlignment().exists&&
			encounter[e].is_driver)
		{
			for (int v = 0; v < len(chaseseq.enemycar); v++)
			{
				if (chaseseq.enemycar[v]->id() == encounter[e].carid)
				{
					theirrolls.push_back(driveskill(encounter[e], *chaseseq.enemycar[v]) + LCSrandom(DRIVING_RANDOMNESS));
					theirrolls_id.push_back(encounter[e].carid);
					theirrolls_drv.push_back(encounter[e].id);
				}
			}
		}
		else if (encounter[e].carid == -1) encounter[e].stop_existing();
	}
	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	moveAlt(16, 1);
	switch (LCSrandom(car_speed.size() + 1))
	{
	case 0:
		if (yourworst > 15)
			addstrAlt(YOU_BOLDLY_WEAVE_THROUGH_TRAFFIC, gamelog);
		else
			addstrAlt(YOU_MAKE_OBSCENE_GESTURES, gamelog);
		gamelog.newline(); //new line.
		break;
	default:
		addstrAlt(pickrandom(car_speed), gamelog);
		gamelog.newline(); //new line.
		break;
	}
	pressAnyKey();
	for (int i = 0; i < len(theirrolls); i++)
	{
		int cnt = pickrandom(yourrolls);
		if (theirrolls[i] < cnt)
		{
			clearmessagearea();
			set_color_easy(CYAN_ON_BLACK_BRIGHT);
			moveAlt(16, 1);
			for (int e = 0; e < ENCMAX; e++)
			{
				if (encounter[e].id == theirrolls_drv[i])
				{
					addstrAlt(encounter[e].getNameAndAlignment().name, gamelog);
					break;
				}
			}
			switch (LCSrandom(cnt / 5))
			{
			default:
				addstrAlt(FALLS_BEHIND, gamelog);
				gamelog.newline(); //New line.
				break;
			case 1:
				addstrAlt(SKIDS_OUT, gamelog);
				gamelog.newline(); //New line.
				break;
			case 2:
				addstrAlt(BACKS_OFF, gamelog);
				gamelog.newline(); //New line.
				break;
			case 3:
				addstrAlt(BRAKES_HARD, gamelog);
				gamelog.newline(); //New line.
				break;
			}
			for (int e = 0; e < ENCMAX; e++)
			{
				if (encounter[e].carid == theirrolls_id[i])
				{
					for (int e2 = e; e2 < ENCMAX - 1; e2++) encounter[e2] = encounter[e2 + 1];
					encounter[ENCMAX - 1].stop_existing();
					encounter[ENCMAX - 1].carid = -1;
					e--;
				}
			}
			for (int v = 0; v < len(chaseseq.enemycar); v++)
			{
				if (chaseseq.enemycar[v]->id() == theirrolls_id[i])
				{
					delete_and_remove(chaseseq.enemycar, v);
					break;
				}
			}
			printchaseencounter();
			pressAnyKey();
		}
		else
		{
			clearmessagearea();
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			moveAlt(16, 1);
			for (int e = 0; e < ENCMAX; e++)
			{
				if (encounter[e].id == theirrolls_drv[i])
				{
					addstrAlt(encounter[e].getNameAndAlignment().name, gamelog);
					break;
				}
			}
			addstrAlt(IS_STILL_ON_YOUR_TAIL, gamelog);
			gamelog.newline(); //Blarg. Newline.
			pressAnyKey();
		}
	}
}
void crashfriendlycar(int v)
{
	//CRASH CAR
	clearmessagearea();
	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, YOUR_SPACE, gamelog);
	addstrAlt(chaseseq.friendcar[v]->fullname(), gamelog);
	addstrAlt(pickrandom(car_crash_modes), gamelog);
	gamelog.newline(); //New line it.
	printparty();
	pressAnyKey();
	int victimsum = 0;
	for (int p = 0; p < 6; p++)
	{
		if (!activesquad->squad[p]) continue;
		if (activesquad->squad[p]->carid == chaseseq.friendcar[v]->id())
		{
			// Inflict injuries on Liberals
			for (int w = 0; w < BODYPARTNUM; w++)
				// If limb is intact
				if (!(activesquad->squad[p]->getCreatureHealth().wound[w] & (WOUND_CLEANOFF | WOUND_NASTYOFF)))
				{
					// Inflict injuries
					if (LCSrandom(2))
					{
						activesquad->squad[p]->apply_special_wound(w, (WOUND_TORN | WOUND_BLEEDING));
						activesquad->squad[p]->lose_blood(1 + LCSrandom(25));
					}
					if (!LCSrandom(3))
					{
						activesquad->squad[p]->apply_special_wound(w, (WOUND_CUT | WOUND_BLEEDING));
						activesquad->squad[p]->lose_blood(1 + LCSrandom(25));
					}
					if (LCSrandom(2) || activesquad->squad[p]->getCreatureHealth().wound[w] == 0)
					{
						activesquad->squad[p]->apply_special_wound(w, WOUND_BRUISED);
						activesquad->squad[p]->lose_blood(1 + LCSrandom(10));
					}
				}
			// Kill off hostages
			if (activesquad->squad[p]->is_holding_body())
			{
				// Instant death
				if (activesquad->squad[p]->is_prisoner_alive())
				{
					clearmessagearea();
					set_color_easy(RED_ON_BLACK_BRIGHT);
					mvaddstrAlt(16, 1, activesquad->squad[p]->get_prisoner_name(), gamelog);
					addstrAlt(pickrandom(car_crash_fatalities), gamelog);
					gamelog.newline(); //New line.
					printparty();
					pressAnyKey();
				}
				activesquad->squad[p]->prisoner_dies();
				victimsum++;
				// Record death if living Liberal is hauled
				if (!activesquad->squad[p]->is_prisoner_non_LCS())
				{
					if (activesquad->squad[p]->is_prisoner_alive()&&
						activesquad->squad[p]->get_prisoner_align() == 1)stat_dead++;

					activesquad->squad[p]->prisoner_dies();
				}
				// Otherwise just kill them off and be done with it
				else activesquad->squad[p]->delete_prisoner();
				activesquad->squad[p]->discard_body();
			}
			// Handle squad member death
			if (activesquad->squad[p]->getCreatureHealth().blood <= 0)
			{
				// Inform the player
				clearmessagearea();
				set_color_easy(RED_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
				switch (LCSrandom(die_in_car.size() + 1))
				{
					//TODO IsaacG Migrate Strings
				case 0:addstrAlt(SLUMPS_IN, gamelog);
					addstrAlt(activesquad->squad[p]->hisher(), gamelog);
					addstrAlt(SEAT_OUT_COLD_AND_DIES, gamelog); break;
				default:
					addstrAlt(pickrandom(die_in_car), gamelog);
					break;
				}
				gamelog.newline(); //New line.
				printparty();
				pressAnyKey();
				// Mark as dead
				activesquad->squad[p]->die();
				activesquad->squad[p]->location = -1;
				victimsum++;
				// Account for deaths for high score
				if (activesquad->squad[p]->getCreatureHealth().align == ALIGN_LIBERAL)stat_dead++;
				// Remove dead Liberal from squad
				activesquad->squad[p] = NULL;
			}
			else
			{
				// Inform the player of character survival
				clearmessagearea();
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
				switch (LCSrandom(3))
				{
				case 0:
					addstrAlt(GRIPS_THE_SPACE, gamelog);
					if (activesquad->squad[p]->is_armed())
						addstrAlt(activesquad->squad[p]->get_weapon().get_shortname(), gamelog);
					else addstrAlt(CAR_FRAME, gamelog);
					addstrAlt(AND_STRUGGLES_TO, gamelog);
					addstrAlt(activesquad->squad[p]->hisher(), gamelog);
					if (activesquad->squad[p]->flag & CREATUREFLAG_WHEELCHAIR)
						addstrAlt(WHEELCHAIR_PERIOD, gamelog);
					else addstrAlt(FEET_PERIOD, gamelog);
					break;
				case 1:
					addstrAlt(GASPS_IN_PAIN_BUT_LIVES, gamelog);
					break;
				case 2:addstrAlt(CRAWLS_FREE_OF_CAR, gamelog);
					activesquad->squad[p]->drop_weapon(NULL);
					break;
				}
				gamelog.newline(); //New line.
				printparty();
				pressAnyKey();
			}
		}
	}
	//CONSOLIDATE SQUAD
	for (int i = 0; i < 5; i++)
	{
		bool flipstart = 0;
		for (int pt = 0; pt < 6; pt++)
		{
			if (activesquad->squad[pt] == NULL && !flipstart)flipstart = 1;
			if (flipstart&&pt < 5)activesquad->squad[pt] = activesquad->squad[pt + 1];
		}
		if (flipstart)activesquad->squad[5] = NULL;
	}
	//GET RID OF CARS
	deleteVehicles(chaseseq.friendcar);
	for (int p = 0; p < 6; p++)
	{
		if (!activesquad->squad[p]) continue;
		activesquad->squad[p]->carid = -1;
	}
}
void crashenemycar(int v)
{
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int victimsum = 0;
	for (int p = ENCMAX - 1; p >= 0; p--)
	{
		if (!encounter[p].exists) continue;
		if (getEncounterCarID(p) == chaseseq.enemycar[v]->id())
		{
			victimsum++;
			delenc(p, 0);
		}
	}
	//CRASH CAR
	clearmessagearea();
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, tag_The, gamelog);
	addstrAlt(chaseseq.enemycar[v]->fullname(), gamelog);
	switch (LCSrandom(3))
	{
	case 0:addstrAlt(SLAMS_INTO_BUILDING, gamelog); break;
	case 1:
		addstrAlt(SPINS_OUT_AND_CRASHES, gamelog);
		moveAlt(17, 1);
		if (victimsum > 1)addstrAlt(EVERYONE_INSIDE_PEELED_OFF_AGAINST_PAVEMENT, gamelog);
		else if (victimsum == 1)addstrAlt(PERSON_INSIDE_IS_SQUASHED_INTO_CUBE, gamelog);
		break;
	case 2:addstrAlt(HITS_A_PARKED_CAR, gamelog); break;
	}
	gamelog.newline(); //New line.
	delete_and_remove(chaseseq.enemycar, v);
	printchaseencounter();
	pressAnyKey();
}
bool drivingupdate(short &obstacle)
{
	//CHECK TO SEE WHICH CARS ARE BEING DRIVEN
	vector<int> passenger;
	int driver;
	for (int v = len(chaseseq.friendcar) - 1; v >= 0; v--)
	{
		passenger.clear();
		driver = -1;
		for (int p = 0; p < 6; p++)
		{
			if (activesquad->squad[p] == NULL) continue;
			if (activesquad->squad[p]->carid == chaseseq.friendcar[v]->id())
			{
				if (activesquad->squad[p]->is_driver)
				{
					if (activesquad->squad[p]->canwalk()) driver = p;
					else activesquad->squad[p]->is_driver = 0;
				}
				passenger.push_back(p);
			}
		}
		if (len(passenger) && driver == -1)
		{
			//MAKE BEST DRIVING PASSENGER INTO A DRIVER
			vector<int> goodp;
			int max = 0;
			for (int p = 0; p < len(passenger); p++)
				if (driveskill(*activesquad->squad[passenger[p]], *chaseseq.friendcar[v]) > max&&activesquad->squad[passenger[p]]->canwalk())
					max = driveskill(*activesquad->squad[passenger[p]], *chaseseq.friendcar[v]);
			for (int p = 0; p < len(passenger); p++)
				if (driveskill(*activesquad->squad[passenger[p]], *chaseseq.friendcar[v]) == max && activesquad->squad[passenger[p]]->canwalk())
					goodp.push_back(passenger[p]);
			if (len(goodp))
			{
				int p = pickrandom(goodp);
				activesquad->squad[p]->is_driver = 1;
				driver = p;
				clearmessagearea();
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(TAKES_OVER_THE_WHEEL, gamelog);
				gamelog.newline(); //New line.
				printparty();
				pressAnyKey();
			}
		}
		if (driver == -1)
		{
			crashfriendlycar(v);
			sitestory->crime.push_back(CRIME_CARCHASE);
			return 1;
		}
	}
	for (int v = len(chaseseq.enemycar) - 1; v >= 0; v--)
	{
		passenger.clear();
		driver = -1;
		for (int p = 0; p < ENCMAX; p++)
		{
			if (!encounter[p].getNameAndAlignment().exists) continue;
			if (encounter[p].carid == chaseseq.enemycar[v]->id())
			{
				if (encounter[p].is_driver)
				{
					if (encounter[p].canwalk()) driver = p;
					else encounter[p].is_driver = 0;
				}
				passenger.push_back(p);
			}
		}
		// Enemies don't take over the wheel when driver incapacitated
		if (driver == -1)
		{
			crashenemycar(v);
			sitestory->crime.push_back(CRIME_CARCHASE);
		}
	}
	//SET UP NEXT OBSTACLE
	if (!LCSrandom(3)) obstacle = LCSrandom(CARCHASE_OBSTACLENUM);
	else obstacle = -1;
	return 0;
}
bool dodgedrive()
{
	clearmessagearea();
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, YOU_SWERVE_TO_AVOID, gamelog);
	gamelog.newline(); //New line.
	pressAnyKey();
	int driver;
	for (int v = len(chaseseq.friendcar) - 1; v >= 0; v--)
	{
		driver = -1;
		for (int p = 0; p < 6; p++)
		{
			if (!activesquad->squad[p]) continue;
			if (activesquad->squad[p]->carid == chaseseq.friendcar[v]->id())
			{
				if (activesquad->squad[p]->is_driver)
				{
					driver = p;
					break;
				}
			}
		}
		if (driver != -1)
		{
			if (!activesquad->squad[driver]->skill_check(PSEUDOSKILL_ESCAPEDRIVE, DIFFICULTY_EASY))
			{
				crashfriendlycar(v);
				sitestory->crime.push_back(CRIME_CARCHASE);
				return 1;
			}
		}
	}
	for (int v = len(chaseseq.enemycar) - 1; v >= 0; v--)
	{
		driver = -1;
		for (int p = 0; p < ENCMAX; p++)
		{
			if (!encounter[p].getNameAndAlignment().exists) continue;
			if (encounter[p].carid == chaseseq.enemycar[v]->id())
			{
				if (encounter[p].is_driver)
				{
					driver = p;
					break;
				}
			}
		}
		if (driver != -1)
			if (!encounter[driver].skill_check(PSEUDOSKILL_ESCAPEDRIVE, DIFFICULTY_EASY))
			{
				crashenemycar(v);
				sitestory->crime.push_back(CRIME_CARCHASE);
			}
	}
	return 0;
}
bool obstacledrive(short obstacle, char choice)
{
	switch (obstacle)
	{
	case CARCHASE_OBSTACLE_CROSSTRAFFIC:
		if (choice == 0)
		{
			if (dodgedrive()) return 1;
		}
		else if (choice == 1)
		{
			clearmessagearea();
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, YOU_SLOW_DOWN, gamelog);
			gamelog.newline(); //New line.
			pressAnyKey();
			if (!LCSrandom(3))
			{
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				mvaddstrAlt(17, 1, hereTheyCome, gamelog);
				gamelog.newline(); //New line.
				pressAnyKey();
				enemyattack();
				youattack();
			}
		}
		break;
	case CARCHASE_OBSTACLE_TRUCKPULLSOUT:
		if (choice == 0)
		{
			if (dodgedrive()) return 1;
		}
		else if (choice == 1)
		{
			clearmessagearea();
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, YOU_SLOW_DOWN_AND_EVADE, gamelog);
			gamelog.newline(); //New line.
			pressAnyKey();
			if (!LCSrandom(3))
			{
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				mvaddstrAlt(17, 1, hereTheyCome, gamelog);
				gamelog.newline(); //New line.
				pressAnyKey();
				enemyattack();
				youattack();
			}
		}
		break;
	case CARCHASE_OBSTACLE_FRUITSTAND:
		if (choice == 0)
		{
			if (dodgedrive()) return 1;
		}
		else if (choice == 1)
		{
			clearmessagearea();
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, FRUIT_SMASHES_ALL_OVER_WINDSHIELD, gamelog);
			gamelog.newline(); //New line.
			pressAnyKey();
			if (!LCSrandom(5))
			{
				set_color_easy(RED_ON_BLACK_BRIGHT);
				mvaddstrAlt(17, 1, FRUIT_SELLER_IS_SQUASHED, gamelog);
				gamelog.newline(); //All this logging and lining...
				pressAnyKey();
				criminalizeparty(LAWFLAG_MURDER);
			}
		}
		break;
	case CARCHASE_OBSTACLE_CHILD:
		if (choice == 0)
		{
			if (dodgedrive()) return 1;
		}
		else if (choice == 1)
		{
			clearmessagearea();
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, YOU_SLOW_DOWN_AND_AVOID_KID, gamelog);
			gamelog.newline(); //New line.
			pressAnyKey();
			if (!LCSrandom(3))
			{
				set_color_easy(RED_ON_BLACK_BRIGHT);
				mvaddstrAlt(17, 1, CONSERVATIVES_UNLEASH_GUNFIRE, gamelog);
				gamelog.newline(); //New line.
				pressAnyKey();
				enemyattack();
				youattack();
			}
			else
			{
				set_color_easy(GREEN_ON_BLACK_BRIGHT);
				mvaddstrAlt(17, 1, BOTH_SIDES_AVOID_ENDANGERING_CHILD, gamelog);
				gamelog.newline(); //New line.
				pressAnyKey();
			}
		}
		break;
	}
	return 0;
}
void printSituationAndInstructions(const short obstacle) {
	int partysize = activesquadSize();

	//PRINT DRIVING SITUATION AND INSTRUCTIONS
	if (partysize > 1)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 40, O_CHANGE_SQUAD_ORDER);
	if (partysize > 0 && (party_status == -1 || partysize > 1))set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 40, HASH_CHECK_STATUS_OF_LIBERAL);
	if (party_status != -1)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 40, show_squad_liberal_status);
	if (obstacle == -1)
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(9, 1, D_TRY_TO_LOSE_THEM);
		mvaddstrAlt(10, 1, E_EQUIP);
		mvaddstrAlt(11, 1, F_FIGHT);
	}
	else
	{
		set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
		mvaddstrAlt(9, 1, carchaseObstacles[obstacle][0]);
		gamelog.newline();
		mvaddstrAlt(10, 1, carchaseObstacles[obstacle][1]);
		mvaddstrAlt(11, 1, carchaseObstacles[obstacle][2]);
	}
	mvaddstrAlt(12, 1, B_BAIL_OUT);
	if (chaseseq.canpullover)
	{
		mvaddstrAlt(13, 1, P_PULL_OVER);
	}
}
void destroyAllCarsAndDetermineMusic() {
	//DESTROY ALL CARS BROUGHT ALONG WITH PARTY
	deleteVehicles(chaseseq.friendcar);
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL) continue;
		activesquad->squad[p]->die();
		activesquad->squad[p]->location = -1;
		activesquad->squad[p] = NULL;
	}
	endcheck(END_BUT_NOT_END); // play the right music in case we're dead
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 1, C_REFLECT_ON_YOUR_LACK_OF_SKILL);
}
LOOP_CONTINUATION chaseWithPartyAlive(const int c, short &obstacle) {

	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();


	int partysize = activesquadSize();
	int partyalive = activesquadAlive();

	if (c == 'o'&&partysize > 1)orderparty();
	if (c == '0')party_status = -1;
	if (c >= '1'&&c <= '6')
	{
		if (activesquad->squad[c - '1'] != NULL)
		{
			if (party_status == c - '1') fullstatus(party_status);
			else party_status = c - '1';
		}
	}
	if (c == 'b')
	{
		deleteVehicles(chaseseq.friendcar);
		for (int p = 0; p < 6; p++)
		{
			if (activesquad->squad[p] == NULL) continue;
			activesquad->squad[p]->carid = -1;
		}
		return footchase() ? RETURN_ONE : RETURN_ZERO;
	}
	else if (c == 'p')
	{
		if (chaseseq.canpullover)
		{
			chase_giveup();
			return RETURN_ZERO;
		}
	}
	else if (obstacle == -1)
	{
		if (c == 'd')
		{
			if (encounter[0].exists&&
				encounter[0].type == CREATURE_COP)
			{
				if (chaseseq.location) sitestory->crime.push_back(CRIME_CARCHASE);
				criminalizeparty(LAWFLAG_RESIST);
			}
			evasivedrive();
			enemyattack();
			youattack();
			creatureadvance();
			if (drivingupdate(obstacle))
			{
				partysize = activesquadSize(), partyalive = activesquadAlive();
				if (partyalive > 0) return footchase() ? RETURN_ONE : RETURN_ZERO;
			}
		}
		if (c == 'f')
		{
			if (encounter[0].exists&&
				encounter[0].type == CREATURE_COP)
			{
				if (chaseseq.location) sitestory->crime.push_back(CRIME_CARCHASE);
				criminalizeparty(LAWFLAG_RESIST);
			}
			youattack();
			enemyattack();
			creatureadvance();
			if (drivingupdate(obstacle))
			{
				partysize = activesquadSize(), partyalive = activesquadAlive();
				if (partyalive > 0) return footchase() ? RETURN_ONE : RETURN_ZERO;
			}
		}
		if (c == 'e') equip(activesquad->loot, -1);
	}
	else
	{
		switch (obstacle)
		{
		case CARCHASE_OBSTACLE_CHILD:
		case CARCHASE_OBSTACLE_CROSSTRAFFIC:
		case CARCHASE_OBSTACLE_TRUCKPULLSOUT:
		case CARCHASE_OBSTACLE_FRUITSTAND:
			if (c == 'd')
			{
				if (obstacledrive(obstacle, 0))
				{
					partysize = activesquadSize(), partyalive = activesquadAlive();
					if (partyalive > 0) return footchase() ? RETURN_ONE : RETURN_ZERO;
				}
				creatureadvance();
				drivingupdate(obstacle);
			}
			if (c == 'f')
			{
				if (obstacledrive(obstacle, 1))
				{
					partysize = activesquadSize(), partyalive = activesquadAlive();
					if (partyalive > 0) return footchase() ? RETURN_ONE : RETURN_ZERO;
				}
				creatureadvance();
				if (drivingupdate(obstacle))
				{
					partysize = activesquadSize(), partyalive = activesquadAlive();
					if (partyalive > 0) return footchase() ? RETURN_ONE : RETURN_ZERO;
				}
			}
			break;
		}
	}
	//HAVE YOU LOST ALL OF THEM?
	//THEN LEAVE
	partysize = activesquadSize(), partyalive = activesquadAlive();
	int baddiecount = baddieCount(true);
	if (partyalive > 0 && baddiecount == 0)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		clearmessagearea();
		mvaddstrAlt(16, 1, lostThem, gamelog);
		gamelog.newline(); //New line.
		pressAnyKey();
		CreaturePool::getInstance().stopAllBleeding();
		return RETURN_ONE;
	}
	return REPEAT;
}
LOOP_CONTINUATION increment_chasesequence(short& obstacle) {

	int partyalive = activesquadAlive();

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, LocationsPool::getInstance().getLocationName(chaseseq.location));
	//PRINT PARTY
	if (partyalive == 0) party_status = -1;
	printparty();
	if (partyalive > 0)
	{
		printSituationAndInstructions(obstacle);
	}
	else
	{
		destroyAllCarsAndDetermineMusic();
	}
	//PRINT ENEMIES
	printchaseencounter();
	int c = getkeyAlt();
	if (partyalive == 0 && c == 'c')
	{
		if (!endcheck())
		{
			return RETURN_ZERO;
		}
	}
	else if (partyalive > 0) {
		return chaseWithPartyAlive(c, obstacle);
	}

	return REPEAT;

}
bool chasesequence()
{
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int chasenum = 0;
	reloadparty();
	//NOTE: THIS FUNCTION RETURNS 1 IF ANYBODY ESCAPES
	//IT CAN DELETE CREATURES AND VEHICLES, BUT SHOULD NOT DELETE SQUADS
	//AS SQUADS MAY BE FICTITIOUS AND WILL BE DELETED LATER ANYWAY
	//BAIL IF NO CHASERS
	for (int e = 0; e < ENCMAX; e++) if (encounter[e].exists) chasenum++;
	if (!chasenum)
	{
		gamelog.newline();
		return 1;
	}
	chaseseq.friendcar.clear();
	addCreatueVehiclesToCollection(activesquad->squad, chaseseq.friendcar);
	mode = GAMEMODE_CHASECAR;
	music.play(MUSIC_CARCHASE);
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, AS_YOU_PULL_AWAY_YOU_NOTICE, gamelog);
	mvaddstrAlt(1, 0, BEING_FOLLOWED, gamelog);
	gamelog.newline(); //New line.
	pressAnyKey();
	if (LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONPARENT,chaseseq.location) != -1)
		chaseseq.location = LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONPARENT,chaseseq.location);
	short obstacle = -1;
	while (true) {
		LOOP_CONTINUATION x = increment_chasesequence(obstacle);
		if (x == RETURN_ZERO) {
			mode = GAMEMODE_BASE;
			//Make sure all possible exits of the chase have the nextMessage() call
			//to ensure that the gamelog is split properly into blocks.
			gamelog.nextMessage();
			return 0;
		}
		else if (x == RETURN_ONE) {
			mode = GAMEMODE_BASE;
			//Make sure all possible exits of the chase have the nextMessage() call
			//to ensure that the gamelog is split properly into blocks.
			gamelog.nextMessage();
			return 1;
		}
	}
}
Vehicle* getChaseVehicle(const DeprecatedCreature &c)
{
	Vehicle* found = NULL;
	if (mode == GAMEMODE_CHASECAR && c.carid != -1)
	{
		for (int v2 = 0; v2 < len(chaseseq.friendcar); v2++)
			if (chaseseq.friendcar[v2]->id() == c.carid)
			{
				found = chaseseq.friendcar[v2];
				break;
			}
		for (int v2 = 0; v2 < len(chaseseq.enemycar); v2++)
			if (chaseseq.enemycar[v2]->id() == c.carid)
			{
				found = chaseseq.enemycar[v2];
				break;
			}
	}
	return found;
}
DeprecatedCreature* getChaseDriver(const DeprecatedCreature &c)
{
	DeprecatedCreature* found = NULL;
	if (mode == GAMEMODE_CHASECAR && c.carid != -1)
	{
		int v = c.carid;
		// Check to see if the car we are in is being driven by an LCS member
		for (int p = 0; p < 6; p++)
		{
			if (activesquad->squad[p] == NULL) continue;
			if (activesquad->squad[p]->carid == v
				&& activesquad->squad[p]->is_driver)
			{
				found = activesquad->squad[p];
			}
		}
		// Check to see if the car we are in is being driven by an encounter creature.
		for (int p = 0; p < ENCMAX; p++)
		{
			if (!encounter[p].getNameAndAlignment().exists) continue;
			if (encounter[p].carid == v
				&& encounter[p].is_driver)
			{
				found = &encounter[p];
			}
		}
	}
	//gamelog.newline();
	return found;
}
void makechasers(long type, const long sitecriminality)
{
	// 
	long sitecrime_chasers;
	if (sitecriminality > 10) {
		sitecrime_chasers = 0;
		long sitecrime_log = sitecriminality;
		while (sitecrime_log > 10) {
			sitecrime_log /= 2;
			sitecrime_chasers += 10;
		}
		sitecrime_chasers += sitecrime_log;
	}
	else {
		sitecrime_chasers = sitecriminality;
	}
	emptyEncounter();
	if (!sitecrime_chasers) return;
	//short encslot = 0;
	string cartype; //Temporary (transitionally) solution. -XML
	long pnum;
	chaseseq.canpullover = 0;
	// 50% of CCS harassing your teams once they reach the
	// CONST_chase086 stage (but not for activities, which are
	// law enforcement response specific)
	int crime_ratio;
	CreatureTypes chasing_enemy;
	int min_enemies;
	int max_enemies;
	if (type != -1 && (endgamestate == ENDGAME_CCS_SIEGES || endgamestate == ENDGAME_CCS_ATTACKS) && LCSrandom(2))
	{
		cartype = CONST_X_SUV; //A CCS property, not a vehicle property. Temporary solution -XML
		crime_ratio = 5;
		min_enemies = 1;
		max_enemies = 12;
		chasing_enemy = CREATURE_CCS_VIGILANTE;
	}
	else
	{
		switch (type)
		{
		case SITE_GOVERNMENT_ARMYBASE:
			cartype = CONST_X_HMMWV; //Site property? Temporary solution. -XML
			crime_ratio = 5;
			min_enemies = 3;
			max_enemies = 6;
			chasing_enemy = CREATURE_SOLDIER;
			break;
		case SITE_GOVERNMENT_WHITE_HOUSE:
			cartype = AGENTCAR; //Site property? Temporary solution. -XML
			crime_ratio = 5;
			min_enemies = 1;
			max_enemies = 6;
			chasing_enemy = CREATURE_SECRET_SERVICE;
			break;
		case SITE_GOVERNMENT_INTELLIGENCEHQ:
			cartype = AGENTCAR; //Site property? Temporary solution. -XML
			crime_ratio = 5;
			min_enemies = 1;
			max_enemies = 6;
			chasing_enemy = CREATURE_AGENT;
			break;
		case SITE_CORPORATE_HEADQUARTERS:
		case SITE_CORPORATE_HOUSE:
			if (LCSrandom(2))cartype = CONST_X_SUV; //Site property? Temporary solution. -XML
			else cartype = CONST_X_JEEP; //Site property? Temporary solution. -XML
			crime_ratio = 5;
			min_enemies = 1;
			max_enemies = 6;
			chasing_enemy = CREATURE_MERC;
			break;
		case SITE_MEDIA_AMRADIO:
		case SITE_MEDIA_CABLENEWS:
			cartype = CONST_X_PICKUP; //Site property? Temporary solution. -XML
			crime_ratio = 3;
			min_enemies = 1;
			max_enemies = 18;
			chasing_enemy = CREATURE_HICK;
			break;
		case SITE_BUSINESS_CRACKHOUSE:
			cartype = STATIONWAGON; //Site property? Temporary solution. -XML
			crime_ratio = 3;
			min_enemies = 1;
			max_enemies = 18;
			chasing_enemy = CREATURE_GANGMEMBER;
			break;
		default:
			chaseseq.canpullover = 1;
			cartype = tag_POLICECAR; //Police property? Temporary solution. -XML
			crime_ratio = 5;
			min_enemies = 1;
			max_enemies = 6;
			if (lawList[LAW_DEATHPENALTY] == -2 &&
				lawList[LAW_POLICEBEHAVIOR] == -2) {
				chasing_enemy = CREATURE_DEATHSQUAD;
				chaseseq.canpullover = 0;
			}
			else if (lawList[LAW_POLICEBEHAVIOR] <= -1)
			{
				chasing_enemy = CREATURE_GANGUNIT;
			}
			else
			{
				chasing_enemy = CREATURE_COP;
			}
			break;
		}
	}
	pnum = LCSrandom((sitecrime_chasers / crime_ratio) + 1) + min_enemies;
	if (pnum > max_enemies) pnum = max_enemies;
	for (int n = 0; n < pnum; n++) {
		make_creature_without_encounter_array(n, chasing_enemy);
	}
	for (int n = 0; n < pnum; n++) conservatise(n);
	//ASSIGN CARS TO CREATURES
	int carnum;
	if (pnum <= 2) carnum = 1;
	else if (pnum <= 3) carnum = LCSrandom(2) + 1;
	else if (pnum <= 5) carnum = LCSrandom(2) + 2;
	else if (pnum <= 7) carnum = LCSrandom(2) + 3;
	else carnum = 4;
	for (int c = 0; c < carnum; c++)
	{
		Vehicle *v = getVehicleOfThisType(getvehicletype(cartype)); //If car type is unknown, due to change in xml file, the game will crash here. -XML
		chaseseq.enemycar.push_back(v);
		for (int n = 0; n < pnum; n++)
			if (encounter[n].carid == -1)
			{
				encounter[n].carid = v->id();
				encounter[n].is_driver = 1;
				break;
			}
	}
	long load[4] = { 0,0,0,0 };
	for (int n = 0; n < pnum; n++)
		if (encounter[n].carid == -1)
		{
			int v;
			do
			{
				v = LCSrandom(len(chaseseq.enemycar));
				encounter[n].carid = chaseseq.enemycar[v]->id();
				encounter[n].is_driver = 0;
			} while (load[v] >= 4);
			load[v]++;
		}
}

/* the next two functions force a chase sequence with a specific liberal */
bool footchase(DeprecatedCreature &cr)
{
	long oldsqid = cr.squadid;
	DeprecatedCreature *crp = &cr;
	Deprecatedsquadst *sq = new Deprecatedsquadst;
	sq->squad[0] = &cr;
	sq->squad[0]->squadid = cursquadid; cursquadid++;
	cr.squadid = sq->squad[0]->squadid;
	cr.carid = -1;
	Deprecatedsquadst *oact = activesquad;
	short ops = party_status;
	activesquad = sq;
	party_status = 0;
	bool escaped = footchase();
	party_status = ops;
	delete sq;
	if (escaped) cr.squadid = oldsqid;
	else if (oldsqid != -1)
	{
		removeCreatureFromSquad(*crp, oldsqid);
	}
	activesquad = oact;
	return escaped;
}
bool chasesequence(DeprecatedCreature &cr, Vehicle &v)
{
	long oldsqid = cr.squadid;
	Deprecatedsquadst *sq = new Deprecatedsquadst;
	sq->squad[0] = &cr;
	sq->squad[0]->squadid = cursquadid;
	sq->id = cursquadid; cursquadid++;
	cr.carid = v.id();
	cr.is_driver = 1;
	Deprecatedsquadst *oact = activesquad;
	short ops = party_status;
	activesquad = sq;
	party_status = 0;
	bool ret = chasesequence();
	party_status = ops;
	delete sq;
	if (ret)
	{
		cr.squadid = oldsqid;
		cr.carid = -1;
	}
	else if (oldsqid != -1)
	{
		removeCreatureFromSquad(cr, oldsqid);
	}
	activesquad = oact;
	gamelog.nextMessage(); //Next message.
	return ret;
}