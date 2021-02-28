
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
#include "../includes15.h"
#include "../constStringadvance.h"
#include <algorithm>



/* handles end of round stuff for one creature */
void advancecreature(DeprecatedCreature &cr)
{
	if (!cr.getNameAndAlignment().alive) return;
	char incaprint;
	if (incapacitated(cr, 1, incaprint))
	{
		if (incaprint)
		{
			printparty();
			if (mode == GAMEMODE_CHASECAR ||
				mode == GAMEMODE_CHASEFOOT) printchaseencounter();
			else printencounter();
			pressAnyKey();
		}
	}
	int bleed = 0, topmedicalskill = 0;
	DeprecatedCreature* topmedical = NULL;
	for (int i = 0; i < 6; i++) if (activesquad->squad[i] &&
		activesquad->squad[i]->getNameAndAlignment().alive&&
		!activesquad->squad[i]->is_stunned() &&
		activesquad->squad[i]->blood > 40 &&
		activesquad->squad[i]->id != cr.id&&
		activesquad->squad[i]->get_skill(SKILL_FIRSTAID) > topmedicalskill)
		topmedicalskill = (topmedical = activesquad->squad[i])->get_skill(SKILL_FIRSTAID);
	for (int w = 0; w < BODYPARTNUM; w++)
	{
		if (cr.wound[w] & WOUND_BLEEDING)
		{
			if (LCSrandom(500) < cr.get_attribute(ATTRIBUTE_HEALTH, true))
				cr.wound[w] ^= WOUND_BLEEDING;
			else if (cr.squadid != -1 && topmedical&&topmedical->skill_check(SKILL_FIRSTAID, DIFFICULTY_FORMIDABLE))
			{
				clearmessagearea();
				set_color_easy(GREEN_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 1, topmedical->getNameAndAlignment().name, gamelog);
				addstrAlt(ABLE_TO_SLOW_BLEEDING, gamelog);
				mvaddstrAlt(17, 1, cr.getNameAndAlignment().name, gamelog);
				addstrAlt(sWounds, gamelog);
				gamelog.newline();
				topmedical->train(SKILL_FIRSTAID, max(int(50 - topmedicalskill * 2), 0));
				cr.wound[w] ^= WOUND_BLEEDING;
				pressAnyKey();
			}
			else bleed++;
		}
	}
	if (mode == GAMEMODE_SITE && LCSrandom(3) &&
		((levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_PEAK) ||
		(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_END)))
	{
		int burndamage = (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_FIRE_PEAK) ? LCSrandom(40) : LCSrandom(20);
		clearmessagearea();
		// Firefighter's bunker gear reduces burn damage
		if (cr.get_armor().has_fireprotection())
		{
			// Base effect is 3/4 damage reduction, the denominator
			// increases with low quality or damaged gear
			int denom = 4;
			// Damaged gear
			if (cr.get_armor().is_damaged()) denom += 2;
			// Shoddy quality gear
			denom += cr.get_armor().get_quality() - 1;
			// Apply damage reduction
			burndamage = static_cast<int>(burndamage * (1 - (3.0 / denom)));
		}
		cr.blood -= burndamage;
		if (cr.blood <= 0)
		{
			cr.die();
			if (cr.squadid != -1)
			{
				if (cr.align == 1) stat_dead++;
			}
			else if (cr.align == -1 && (cr.animalgloss != ANIMALGLOSS_ANIMAL || lawList[LAW_ANIMALRESEARCH] == 2))
			{
				stat_kills++;
				if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite())) LocationsPool::getInstance().addSiegeKill(getCurrentSite());
				if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) && cr.animalgloss == ANIMALGLOSS_TANK) LocationsPool::getInstance().removeTank(getCurrentSite());
				if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
				{
					if (cr.type == CREATURE_CCS_ARCHCONSERVATIVE) ccs_boss_kills++;
					ccs_siege_kills++;
				}
			}
			if (cr.squadid == -1)
			{
				sitecrime += 10;
				sitestory->crime.push_back(CRIME_KILLEDSOMEBODY);
				criminalizeparty(LAWFLAG_MURDER);
				//<-- people dying in fire? probably your fault for starting it
			}
			adddeathmessage(cr);
			pressAnyKey();
			if (cr.is_holding_body()) freehostage(cr, 1);
		}
		else
		{
			set_color_easy(RED_ON_BLACK);
			mvaddstrAlt(16, 1, cr.getNameAndAlignment().name, gamelog);
			addstrAlt(isBurned, gamelog);
			gamelog.newline(); //Next message?
			pressAnyKey();
		}
	}
	if (bleed > 0)
	{
		clearmessagearea();
		cr.blood -= bleed;
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_BLOODY;
		cr.get_armor().set_bloody(true);
		if (cr.blood <= 0)
		{
			cr.die();
			if (cr.squadid != -1)
			{
				if (cr.align == 1) stat_dead++;
			}
			else if (cr.align == -1 && (cr.animalgloss != ANIMALGLOSS_ANIMAL || lawList[LAW_ANIMALRESEARCH] == 2))
			{
				stat_kills++;
				if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))LocationsPool::getInstance().addSiegeKill(getCurrentSite());
				if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) && cr.animalgloss == ANIMALGLOSS_TANK)LocationsPool::getInstance().removeTank(getCurrentSite());
				if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
				{
					if (cr.type == CREATURE_CCS_ARCHCONSERVATIVE) ccs_boss_kills++;
					ccs_siege_kills++;
				}
			}
			if (cr.squadid == -1)
			{
				sitecrime += 10;
				sitestory->crime.push_back(CRIME_KILLEDSOMEBODY);
				//criminalizeparty(LAWFLAG_MURDER);
				//^-- might not die from squad attacking
			}
			adddeathmessage(cr);
			pressAnyKey();
			if (cr.is_holding_body()) freehostage(cr, 1);
		}
	}
}
void sitemodeCreatureAdvance() {


	if (isThereASiteAlarm() && sitecrime > 10) postalarmtimer++;
	if (sitealarmtimer > 0 && !isThereASiteAlarm() && sitecrime > 5)
	{
		sitealarmtimer--;
		if (sitealarmtimer <= 0)
		{
			sitealarmtimer = 0;
			clearmessagearea();
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(16, 1, smellsPanic, gamelog);
			gamelog.newline();
			printencounter();
			pressAnyKey();
		}
	}
	for (int z = 0; z < MAPZ; z++)
	{
		bool stairs = 0; // Will check if higher levels are accessible
		for (int y = 0; y < MAPY; y++)
		{
			for (int x = 0; x < MAPX; x++)
			{
				if (levelmap[x][y][z].flag & SITEBLOCK_EXIT) continue;
				if (levelmap[x][y][z].special != -1)
					if (levelmap[x][y][z].special & SPECIAL_STAIRS_UP) stairs = 1;
				// Extinguish ending fires
				if (levelmap[x][y][z].flag & SITEBLOCK_FIRE_END)
				{
					if (!LCSrandom(15))
					{
						levelmap[x][y][z].flag &= ~SITEBLOCK_FIRE_END;
						levelmap[x][y][z].flag |= SITEBLOCK_DEBRIS;
					}
				}
				// Cool/spread peak fires
				if (levelmap[x][y][z].flag & SITEBLOCK_FIRE_PEAK)
				{
					siteonfire = 1;
					if (!LCSrandom(10))
					{
						levelmap[x][y][z].flag &= ~SITEBLOCK_FIRE_PEAK;
						levelmap[x][y][z].flag |= SITEBLOCK_FIRE_END;
					}
					else if (!LCSrandom(4)) // Spread fire
					{
						int dir = LCSrandom(4); // Random initial direction
						int tries = 0; // Will try all four directions before giving up
						while (tries < 4)
						{
							int xmod = 0, ymod = 0;
							switch (dir)
							{
							case 0:xmod = -1; break;
							case 1:xmod = 1; break;
							case 2:ymod = -1; break;
							case 3:ymod = 1; break;
							}
							// Check if the tile is a valid place to spread fire to
							if (x + xmod < MAPX&&x + xmod >= 0 && y + ymod < MAPY&&y + ymod >= 0 &&
								!(levelmap[x + xmod][y + ymod][z].flag & SITEBLOCK_FIRE_START) &&
								!(levelmap[x + xmod][y + ymod][z].flag & SITEBLOCK_DEBRIS) &&
								!(levelmap[x + xmod][y + ymod][z].flag & SITEBLOCK_FIRE_PEAK) &&
								!(levelmap[x + xmod][y + ymod][z].flag & SITEBLOCK_FIRE_END) &&
								!(levelmap[x + xmod][y + ymod][z].flag & SITEBLOCK_EXIT) &&
								!(levelmap[x + xmod][y + ymod][z].flag & SITEBLOCK_METAL))
							{
								// Spread it
								levelmap[x + xmod][y + ymod][z].flag |= SITEBLOCK_FIRE_START;
								break;
							}
							// Else try another direction
							tries++;
							dir++; dir %= 4;
						}
						if (tries == 5) // If all four directions unacceptable, spread upward
						{
							// Check if up is valid
							if (z < MAPZ &&
								!(levelmap[x][y][z + 1].flag & SITEBLOCK_FIRE_START) &&
								!(levelmap[x][y][z + 1].flag & SITEBLOCK_DEBRIS) &&
								!(levelmap[x][y][z + 1].flag & SITEBLOCK_FIRE_PEAK) &&
								!(levelmap[x][y][z + 1].flag & SITEBLOCK_FIRE_END) &&
								!(levelmap[x][y][z + 1].flag & SITEBLOCK_METAL))
							{
								// Spread it
								levelmap[x][y][z + 1].flag |= SITEBLOCK_FIRE_START;
							}
							// Else give up
						}
					}
				}
				// Aggrivate starting fires
				if (levelmap[x][y][z].flag & SITEBLOCK_FIRE_START)
				{
					if (!LCSrandom(5))
					{
						sitechangest change(x, y, z, SITEBLOCK_DEBRIS);
						addLocationChange(getCurrentSite(), change);
						levelmap[x][y][z].flag &= ~SITEBLOCK_BLOCK;
						levelmap[x][y][z].flag &= ~SITEBLOCK_DOOR;
						levelmap[x][y][z].flag &= ~SITEBLOCK_FIRE_START;
						levelmap[x][y][z].flag |= SITEBLOCK_FIRE_PEAK;
						sitecrime += 5;
					}
				}
			}
		}
		// If no stairs to the next level were found, don't continue to that level
		if (!stairs) break;
	}
}
/* handles end of round stuff for everyone */
void creatureadvance()
{

	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL) continue;
		if (!activesquad->squad[p]->getNameAndAlignment().alive) continue;
		advancecreature(*activesquad->squad[p]);
		if (activesquad->squad[p]->is_holding_body())
		{
			activesquad->squad[p]->advance_prisoner();
			if (!activesquad->squad[p]->is_prisoner_alive())
			{
				if (activesquad->squad[p]->is_prisoner_non_LCS())
				{
					clearmessagearea();
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(16, 1, activesquad->squad[p]->getNameAndAlignment().name, gamelog);
					addstrAlt(drops, gamelog);
					addstrAlt(activesquad->squad[p]->get_prisoner_name(), gamelog);
					addstrAlt(sBody, gamelog);
					gamelog.newline();
					activesquad->squad[p]->make_prisoner_ground_loot();
					pressAnyKey();
					sitecrime += 10;
					sitestory->crime.push_back(CRIME_KILLEDSOMEBODY);
					//criminalizeparty(LAWFLAG_MURDER);
					//<-- might not die from squad's attacks
					if (activesquad->squad[p]->get_prisoner_type() == CREATURE_CORPORATE_CEO ||
						activesquad->squad[p]->get_prisoner_type() == CREATURE_RADIOPERSONALITY ||
						activesquad->squad[p]->get_prisoner_type() == CREATURE_NEWSANCHOR ||
						activesquad->squad[p]->get_prisoner_type() == CREATURE_SCIENTIST_EMINENT ||
						activesquad->squad[p]->get_prisoner_type() == CREATURE_JUDGE_CONSERVATIVE)
					{
						sitecrime += 30;
					}

					activesquad->squad[p]->delete_and_nullify_prisoner();
				}
			}
		}
	}
	if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		CreaturePool::getInstance().advanceCreaturesAtLocation(getCurrentSite());
		autopromote(getCurrentSite());
	}
	for (int e = 0; e < ENCMAX; e++)
	{
		if (!encounter[e].exists) continue;
		if (!encounter[e].alive) continue;
		advancecreature(e);
	}
	if (mode != GAMEMODE_CHASECAR)
	{
		//TAKE THE INJURED WITH YOU
		squadgrab_immobile(0);
		//TAKE THE DEAD WITH YOU
		squadgrab_immobile(1);
	}
	for (int e = ENCMAX - 1; e >= 0; e--)
	{
		if (!encounter[e].exists) continue;
		if (!encounter[e].alive) delenc(e, 1);
	}
	if (mode == GAMEMODE_SITE)
	{
		sitemodeCreatureAdvance();
	}
	//I'll do this here so that everything that happened in the round is grouped together.
	//Note the check is to make sure that no excessive blank lines appear between encounters
	//in the gamelog due to something not happening for a round or two (like the squad
	//moving around with no mishaps). In other words, it only does nexMessage if
	//something was logged this round.
	if (gamelog.hasMessage()) gamelog.nextMessage();
}