

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
#include "../includes09.h"
#include "../constStringsitemode.h"
void pressAnyKey(); 
int getkeyAlt();
int refreshAlt(void);
int eraseAlt(void);
void logNewLine();
void fight_subdued()
{
	//int p;
	//int ps=find_police_station(chaseseq.location);
	deleteVehicles(chaseseq.friendcar);
	int hostages = 0;
	for (int p = 0; p < 6; p++)
		if (activesquad->squad[p] != NULL)
			if (activesquad->squad[p]->is_holding_body() &&activesquad->squad[p]->get_prisoner_align() != ALIGN_LIBERAL)
				hostages++;
	int stolen = 0;
	// Police assess stolen goods in inventory
	for (int l = 0; l < len(activesquad->loot); l++)
		if (activesquad->loot[l]->whatIsThis() == THIS_IS_LOOT)
			stolen++;
	for (int p = 0; p < 6; p++)
	{
		if (!activesquad->squad[p]) continue;
		for (int i = 0; i < stolen; i++) {
			activesquad->squad[p]->criminalize_me(LAWFLAG_THEFT);
		}
		capturecreature(*(activesquad->squad[p]));
		activesquad->squad[p] = NULL;
	}
	CreaturePool::getInstance().stopAllBleeding();
	printSquadSubduedHostagesFreed(hostages);
	pressAnyKey();
}

/* marks the area around the specified tile as explored */
void knowmap(const int locx, const int locy, const int locz)
{
	levelmap[locx][locy][locz].flag |= SITEBLOCK_KNOWN;
	if (locx > 0)levelmap[locx - 1][locy][locz].flag |= SITEBLOCK_KNOWN;
	if (locx < MAPX - 1)levelmap[locx + 1][locy][locz].flag |= SITEBLOCK_KNOWN;
	if (locy > 0)levelmap[locx][locy - 1][locz].flag |= SITEBLOCK_KNOWN;
	if (locy < MAPY - 1)levelmap[locx][locy + 1][locz].flag |= SITEBLOCK_KNOWN;
	if (locx > 0 && locy > 0)
		if (!(levelmap[locx - 1][locy][locz].flag & SITEBLOCK_BLOCK) ||
			!(levelmap[locx][locy - 1][locz].flag & SITEBLOCK_BLOCK))
			levelmap[locx - 1][locy - 1][locz].flag |= SITEBLOCK_KNOWN;
	if (locx < MAPX - 1 && locy>0)
		if (!(levelmap[locx + 1][locy][locz].flag & SITEBLOCK_BLOCK) ||
			!(levelmap[locx][locy - 1][locz].flag & SITEBLOCK_BLOCK))
			levelmap[locx + 1][locy - 1][locz].flag |= SITEBLOCK_KNOWN;
	if (locx > 0 && locy < MAPY - 1)
		if (!(levelmap[locx - 1][locy][locz].flag & SITEBLOCK_BLOCK) ||
			!(levelmap[locx][locy + 1][locz].flag & SITEBLOCK_BLOCK))
			levelmap[locx - 1][locy + 1][locz].flag |= SITEBLOCK_KNOWN;
	if (locx < MAPX - 1 && locy < MAPY - 1)
		if (!(levelmap[locx + 1][locy][locz].flag & SITEBLOCK_BLOCK) ||
			!(levelmap[locx][locy + 1][locz].flag & SITEBLOCK_BLOCK))
			levelmap[locx + 1][locy + 1][locz].flag |= SITEBLOCK_KNOWN;
}

void knowmap() {
	knowmap(loc_coord.locx, loc_coord.locy, loc_coord.locz);
}
short getCurrentSite();
/* site - determines spin on site news story, CONST_TOO_HOT timer */
void resolvesite()
{
	if (sitealienate) sitestory->positive = 0;
	//removed the 'alarmed' requirement for high security buildings, on the principle that even if they didn't see you, they will presumably
	//notice later on that all their stuff has been stolen or whatever.
	if (sitecrime > 5 + LCSrandom(95))//was 100 but that meant I could still steal everything from a building every day without anyone caring...
	{
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_NOCONTROL)
		{
			// Capture a warehouse or crack den?
			if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_INDUSTRY_WAREHOUSE ||
				LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_BUSINESS_CRACKHOUSE)
			{
				LocationsPool::getInstance().captureSite(getCurrentSite());
			}
			else LocationsPool::getInstance().closeSite(getCurrentSite(), sitecrime);
		}
		// Out sleepers
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
		{
			CreaturePool::getInstance().outSleepers(getCurrentSite(), activesquad->squad[0]->base);
		}
	}
	else if (sitecrime > 10 && (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_NOCONTROL || LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) > 500))
	{
		if (LocationsPool::getInstance().getLocationType(getCurrentSite()) != SITE_RESIDENTIAL_BOMBSHELTER &&
			LocationsPool::getInstance().getLocationType(getCurrentSite()) != SITE_BUSINESS_BARANDGRILL &&
			LocationsPool::getInstance().getLocationType(getCurrentSite()) != SITE_OUTDOOR_BUNKER &&
			LocationsPool::getInstance().getLocationType(getCurrentSite()) != SITE_INDUSTRY_WAREHOUSE &&
			LocationsPool::getInstance().getLocationType(getCurrentSite()) != SITE_BUSINESS_CRACKHOUSE)
		{
			if (securityable(LocationsPool::getInstance().getLocationType(getCurrentSite())))
				LocationsPool::getInstance().isThisPlaceHighSecurity(getCurrentSite(), sitecrime);
			else LocationsPool::getInstance().closeSite(getCurrentSite(), 70);
		}
	}
}
/* behavior when the player bumps into a door in sitemode */
void open_door(bool restricted)
{
	bool locked = levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_LOCKED,
		alarmed = levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_ALARMED,
		vault_door = levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_METAL,
		//   known_locked=levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_KLOCK,
		cant_unlock = levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_CLOCK;
	if (vault_door)
	{
		// Vault door, not usable by bumping
		printVaultIsImpenetrable();
		pressAnyKey();
		return;
	}
	bool has_security = false;
	for (int i = 0; i < 6; i++)
	{
		if (activesquad->squad[i] &&
			activesquad->squad[i]->get_skill(SKILL_SECURITY) != 0)
		{
			has_security = true;
			break;
		}
	}
	if (alarmed)
	{
		// Unlocked but alarmed door, clearly marked as such
		printUnlockedButAlarmed(locked);
		while (true)
		{
			int c = getkeyAlt();
			if (c == 'y') break;
			else if (c == 'n') return;
		}
	}
	if (locked && !cant_unlock && has_security)
	{
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_KLOCK;
		while (true)
		{
			printLockpickPrompt();
			int c = getkeyAlt();
			clearmessagearea(false);
			if (c == 'y')
			{
				UnlockAttempt actual = unlock(UNLOCK_DOOR); // 1 if an actual attempt was made, 0 otherwise
							 // If the unlock was successful
				if (actual == UNLOCKED)
				{
					// Unlock the door
					levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag &= ~(SITEBLOCK_LOCKED | SITEBLOCK_ALARMED);
					sitestory->crime.push_back(CRIME_UNLOCKEDDOOR);
					if (sitealarmtimer < 0 || sitealarmtimer>50) sitealarmtimer = 50;
					//criminalizeparty(LAWFLAG_BREAKING);
				}
				// Else perma-lock it if an attempt was made
				else if (actual == LOUD_FAILURE)
				{
					levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_CLOCK;
					if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_ALARMED)
					{
						printLockSetOffAlarm();
						setSiteAlarmOne();
						pressAnyKey();
					}
				}
				// Check for people noticing you fiddling with the lock
				if (actual != NEVERMIND)
				{
					alienationcheck(0);
					noticecheck(-1);
				}
				return;
			}
			else if (c == 'n') return;
		}
	}
	else if (locked || (!restricted && alarmed))
	{
		int c;
		do
		{
			printShakeHandle(locked, has_security);
			c = getkeyAlt();
			if (c == 'y')
			{
				UnlockAttempt actualy = bash();
				if (actualy == UNLOCKED)
				{
					levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag &= ~SITEBLOCK_DOOR;
					int time = 0;
					if (sitealarmtimer > time || sitealarmtimer == -1)sitealarmtimer = time;
					if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_ALARMED)
					{
						printAlarmGoesOff();
						setSiteAlarmOne();
						pressAnyKey();
					}
					sitecrime++;
					sitestory->crime.push_back(CRIME_BROKEDOWNDOOR);
					criminalizeparty(LAWFLAG_BREAKING);
				}
				alienationcheck(1);
				noticecheck(-1, DIFFICULTY_HEROIC);
			}
		} while (c != 'y' && c != 'n');
	}
	else
	{
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag &= ~SITEBLOCK_DOOR;
		if (alarmed)
		{
			// Opened an unlocked but clearly marked emergency exit door
			printItOpensWithAlarm();
			setSiteAlarmOne();
			pressAnyKey();
		}
	}
}

int whichWay() {
	int c = 0;
	printWhichWay();
	while (true)
	{
		int c2 = getkeyAlt();
		if (c2 == 'w' || c2 == 'a' || c2 == 'd' || c2 == 'x' ||
			c2 == KEY_LEFT || c2 == KEY_RIGHT || c2 == KEY_UP || c2 == KEY_DOWN)
		{
			c = c2;
			break;
		}
		if (c2 == ENTER || c2 == ESC || c2 == SPACEBAR)break;
	}
	return c;
}
void pressedKeyN() {
	mapshowing = false;
	printSitemodeOptionsHeader();
	printparty();
	printSitemodeOptions();
	int c = 0;
	while (true)
	{
		if (c == 'e') encounterwarnings = !encounterwarnings;
		if (c == 'm') music.enableIf(!music.isEnabled());
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR)break;
		printEncounterWarnings(encounterwarnings);
		printMusicEnabled(music.isEnabled());
		c = getkeyAlt();
	}
	mapshowing = true;

}


void pressedKeyU(const bool enemy) {
	
		if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special != -1)
		{
			switch (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special)
			{
			case SPECIAL_LAB_COSMETICS_CAGEDANIMALS:special_lab_cosmetics_cagedanimals(); break;
			case SPECIAL_NUCLEAR_ONOFF:special_nuclear_onoff(); break;
			case SPECIAL_LAB_GENETIC_CAGEDANIMALS:special_lab_genetic_cagedanimals(); break;
			case SPECIAL_POLICESTATION_LOCKUP:special_policestation_lockup(); break;
			case SPECIAL_COURTHOUSE_LOCKUP:special_courthouse_lockup(); break;
			case SPECIAL_COURTHOUSE_JURYROOM:special_courthouse_jury(); break;
			case SPECIAL_PRISON_CONTROL:
			case SPECIAL_PRISON_CONTROL_LOW:
			case SPECIAL_PRISON_CONTROL_MEDIUM:
			case SPECIAL_PRISON_CONTROL_HIGH:
				special_prison_control(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special); break;
			case SPECIAL_INTEL_SUPERCOMPUTER:special_intel_supercomputer(); break;
			case SPECIAL_SWEATSHOP_EQUIPMENT:special_sweatshop_equipment(); break;
			case SPECIAL_POLLUTER_EQUIPMENT:special_polluter_equipment(); break;
			case SPECIAL_HOUSE_PHOTOS:special_house_photos(); break;
			case SPECIAL_ARMORY:special_armory(); break;
			case SPECIAL_CORPORATE_FILES:special_corporate_files(); break;
			case SPECIAL_RADIO_BROADCASTSTUDIO:special_radio_broadcaststudio(); break;
			case SPECIAL_NEWS_BROADCASTSTUDIO:special_news_broadcaststudio(); break;
			case SPECIAL_SIGN_ONE:special_readsign(SPECIAL_SIGN_ONE); break;
			case SPECIAL_SIGN_TWO:special_readsign(SPECIAL_SIGN_TWO); break;
			case SPECIAL_SIGN_THREE:special_readsign(SPECIAL_SIGN_THREE); break;
			case SPECIAL_STAIRS_UP:loc_coord.locz++; break;
			case SPECIAL_STAIRS_DOWN:loc_coord.locz--; break;
			case SPECIAL_DISPLAY_CASE:special_display_case(); break;
			case SPECIAL_SECURITY_CHECKPOINT:special_security_checkpoint(); break;
			case SPECIAL_SECURITY_METALDETECTORS:special_security_metaldetectors(); break;
			case SPECIAL_SECURITY_SECONDVISIT:special_security_secondvisit(); break;
			case SPECIAL_BANK_VAULT:special_bank_vault(); break;
			case SPECIAL_BANK_TELLER:special_bank_teller(); break;
			case SPECIAL_BANK_MONEY:special_bank_money(); break;
			case SPECIAL_CCS_BOSS:special_ccs_boss(); break;
			case SPECIAL_OVAL_OFFICE_NW:
			case SPECIAL_OVAL_OFFICE_NE:
			case SPECIAL_OVAL_OFFICE_SW:
			case SPECIAL_OVAL_OFFICE_SE:special_oval_office(); break;
			}
		}
		else if (!(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & (SITEBLOCK_GRAFFITI | SITEBLOCK_BLOODY2)) &&
			((levelmap[loc_coord.locx + 1][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_BLOCK) ||
			(levelmap[loc_coord.locx - 1][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_BLOCK) ||
				(levelmap[loc_coord.locx][loc_coord.locy + 1][loc_coord.locz].flag & SITEBLOCK_BLOCK) ||
				(levelmap[loc_coord.locx][loc_coord.locy - 1][loc_coord.locz].flag & SITEBLOCK_BLOCK)))
		{
			int spray = 0;
			for (int i = 0; i < 6; i++)
			{
				if (!activesquad->squad[i])break;
				if (activesquad->squad[i]->get_weapon().get_specific_bool(BOOL_CAN_GRAFFITI_))
				{
					spray = 1;
					break;
				}
			}
			if (spray)
			{
				special_graffiti();
				if (enemy&&isThereASiteAlarm())
				{
					enemyattack();
				}
			}
		}
	
}
void pressedKeyL() {

	reloadparty(true);
	printparty();
	refreshAlt();
	creatureadvance();

}

int findLivingSquadMemberIndex() {
	int forcesp = NO_VALID_MEMBERS;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->getNameAndAlignment().alive)
			{
				if (forcesp == NO_VALID_MEMBERS)forcesp = p;
				else forcesp = MULTIPLE_LIVING_MEMBERS;
			}
		}
	}
	return forcesp;
}
int findEncounterCreatureWhoCanBeBluffed() {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	
	int forcetk = NO_VALID_MEMBERS;
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].exists&&encounter[e].alive &&
			!(encounter[e].type == CREATURE_WORKER_SERVANT ||
				encounter[e].type == CREATURE_WORKER_SWEATSHOP))
		{
			if (!get_encounter_cantbluff_is_one(e) || isThereASiteAlarm())
			{
				if (forcetk == NO_VALID_MEMBERS)forcetk = e;
				else forcetk = MULTIPLE_LIVING_MEMBERS;
			}
		}
	}
	return  forcetk;
}
int pressedKeyTWithMultipleLivingMembers() {
	int sp = NO_VALID_MEMBERS;
	printActiveSquadTalkOptionsHeader();
	printActiveSquadTalkOptions();

	while (true)
	{
		int c = getkeyAlt();
		if (c >= '1'&&c <= '6')
		{
			sp =  (c - '1');
			if (activeSquadMemberIsAliveAndExists(sp)) break;
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) { sp = NO_VALID_MEMBERS; break; }
	}
	return sp;
}
int pressedKeyTAndMeantIt(const bool enemy, const int forcetk, const int sp) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int tk = NO_VALID_MEMBERS;
	if (forcetk == MULTIPLE_LIVING_MEMBERS)
	{
		while (true)
		{
			printToWhom();
			for (int t = 0; t < ENCMAX; t++)
			{
				if (encounter[t].exists)
				{
					CantBluffAnimal encounterBA = encounterGetCantBluffAnimal(t);
					CreatureBio encounterBio = encounterGetCreatureBio(t);
					if (encounterBA.cantbluff != 1)
					{
						printCreatureEncounter(t, encounter[t].align, encounter[t].name, get_age_string(encounterBio, encounterBA.animalgloss));
						
					}	
				}
			}
			int c = getkeyAlt();
			if(c - 'a' >= 0 && c - 'a' < ENCMAX)
			{
				tk = (c - 'a');
				if (encounter[tk].exists)
				{
					if (encounter[tk].alive &&
						!(encounter[tk].type == CREATURE_WORKER_SERVANT ||
							encounter[tk].type == CREATURE_WORKER_SWEATSHOP))
					{
						CantBluffAnimal encounterBA = encounterGetCantBluffAnimal(tk);
						if (encounterBA.cantbluff == 1 &&
							(!isThereASiteAlarm() || encounterBA.animalgloss == ANIMALGLOSS_ANIMAL))
						{
							printIWontTalkToYou(encounter[tk].name);
							pressAnyKey();
						}
						else if (!encounter[tk].enemy && isThereASiteAlarm() && enemy)
						{
							printYouHaveEnemiesFirst();
							pressAnyKey();
						}
						else break;
					}
				}
				
			}
			if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) { tk = NO_VALID_MEMBERS; break; }
		}
	}
	else tk = forcetk;
	return tk;
}
void pressedKeyT(const bool enemy, int& encounter_timer) {
	// forcesp is the index of the only living activesquad member, or is -2 if more than one living activesquad members exist
	int forcesp = findLivingSquadMemberIndex();
	// forcetk is the index of the only encounter creature with cantbluff != 1 (or isThereASiteAlarm()), or is -2 if more than one such creature exists
	int forcetk = findEncounterCreatureWhoCanBeBluffed();

	// Together, this condition is asking whether the activesquad is willing and able to attempt a bluff
	if (forcetk != NO_VALID_MEMBERS && forcesp != NO_VALID_MEMBERS)
	{
		int sp = NO_VALID_MEMBERS;
		if (forcesp == MULTIPLE_LIVING_MEMBERS)
		{
			// since forcesp != -1, the only way for sp != -1 to be false is if this function either does not assign a value to sp or assigns the value -1
			// which only occurs if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR)
			sp = pressedKeyTWithMultipleLivingMembers();
		}
		else {
			sp = forcesp;
		}
		// if sp == -1 at this point, it means the player has opted to cancel the effects of pressing 't'
		if (sp != NO_VALID_MEMBERS)
		{
			int tk = pressedKeyTAndMeantIt(enemy, forcetk, sp);
			if (tk != NO_VALID_MEMBERS)
			{
				if (haveActiveSquadTalk(sp, tk))
				{
					if (enemy&&isThereASiteAlarm()) {
						enemyattack();
					}
					else if (enemy) { 
						disguisecheck(encounter_timer);
					}
					creatureadvance();
					encounter_timer++;
				}
			}
		}
	}

}
void pressedKeyM() {
	printMap(LocationsPool::getInstance().siteHasCameras(getCurrentSite()));
	pressAnyKey();

}
void pressedKeyF(int& encounter_timer) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	// Don't subdue squad if someone is still in good condition.
	bool cannotsubdue = false;
	for (int j = 0; j < 6 && !cannotsubdue; j++)
	{
		if (activesquad->squad[j] &&
			activesquad->squad[j]->getNameAndAlignment().alive &&
			activesquad->squad[j]->blood > 40)
		{
			cannotsubdue = true;
		}
	}
	// Cops can subdue and arrest the squad.
	bool subdue = false;
	for (int i = 0; i < ENCMAX && (!cannotsubdue && !subdue); i++)
	{
		if (encounter[i].exists&&
			encounter[i].blood > 60 &&
			(encounter[i].type == CREATURE_COP))
		{
			subdue = true;
		}
	}
	if (subdue)
		fight_subdued();
	else
	{
		youattack();
		enemyattack();
		creatureadvance();
		encounter_timer++;
	}

}
void pressedKeyR(const bool freeable, const bool enemy) {
	const int hostages = countactivesquadhostages();
	int partysize = activesquadSize();
	const int libnum = CreaturePool::getInstance().countLiberals(getCurrentSite());
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) && libnum > 6)
	{
		assembleActiveSquad();
		autopromote(getCurrentSite());
	}
	else if (freeable && (!enemy || !isThereASiteAlarm()) && !LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		short followers = 0, actgot = 0;
		if (enemy)setSiteAlarmOne();
		bool freed;
		//do
		//{
			bool flipstart = 0;
			freed = 0;
			for (int e = 0; e < ENCMAX; e++)
			{
				if (!encounter[e].exists)break;
				if ((encounter[e].type == CREATURE_WORKER_SERVANT ||
					encounter[e].type == CREATURE_WORKER_FACTORY_CHILD ||
					encounter[e].type == CREATURE_WORKER_SWEATSHOP ||
					(isPrisoner(encounter[e].name) && encounter[e].align == 1)) && !flipstart)
				{
					if (isPrisoner(encounter[e].name))
					{
						setSiteAlarmOne(); /* alarm for prisoner escape */
						criminalizeEncounterPrisonerEscape(e);
					}
					followers++, flipstart = 1, freed = 1;
					if (partysize < 6)
					{
						int i = checkForPeopleWhoCanRecruit();

						// If someone can, add this person as a newly recruited Liberal!
						if (i < 6 && i > -1)
						{
							addNewRecruit(i, e);
							actgot++;
							partysize++;
						}
					}
				}
				if (flipstart)
					if (e < ENCMAX - 1) {
						duplicateEncounterMember(e);
					}
			}
			if (flipstart) { unpersonLastEncounterMember(); }
			if (freed)
			{
				int time = 20 + LCSrandom(10);
				if (time < 1)time = 1;
				if (sitealarmtimer > time || sitealarmtimer == -1)sitealarmtimer = time;
			}
		//} while (freed);
		if (followers > 0)
		{
			printFreeThem(followers);

			if (actgot < followers)
			{
				pressAnyKey();
				printFreeThemWithoutYou(followers, actgot);
			}
			pressAnyKey();
		}
	}
	else if (hostages)
		releasehostage();
}

string getNewLootFromBank() {
	string newLootType;
	if (!LCSrandom(4))newLootType = tag_LOOT_WATCH;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(2))newLootType = tag_LOOT_PDA;
	else newLootType = tag_LOOT_COMPUTER;
	return newLootType;
}
string getNewLootFromApartment() {
	string newLootType;

	if (!LCSrandom(5))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(4))newLootType = tag_LOOT_SILVERWARE;
	else if (!LCSrandom(3))newLootType = tag_LOOT_TRINKET;
	else if (!LCSrandom(2))newLootType = tag_LOOT_CHEAPJEWELERY;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}
string getNewLootFromApartmentUpscale() {
	string newLootType;
	if (!LCSrandom(10))newLootType = tag_LOOT_EXPENSIVEJEWELERY;
	else if (!LCSrandom(5))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(4))newLootType = tag_LOOT_SILVERWARE;
	else if (!LCSrandom(3))newLootType = tag_LOOT_PDA;
	else if (!LCSrandom(2))newLootType = tag_LOOT_CHEAPJEWELERY;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}

string getNewLootFromLab() {
	string newLootType;


	if (!LCSrandom(20))newLootType = tag_LOOT_RESEARCHFILES;
	else if (!LCSrandom(2))newLootType = tag_LOOT_LABEQUIPMENT;
	else if (!LCSrandom(2))newLootType = tag_LOOT_COMPUTER;
	else if (!LCSrandom(5))newLootType = tag_LOOT_PDA;
	else if (!LCSrandom(5))newLootType = tag_LOOT_CHEMICAL;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}

string getNewLootFromPolice() {
	string newLootType;

	if (!LCSrandom(20))newLootType = tag_LOOT_POLICERECORDS;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(2))newLootType = tag_LOOT_PDA;
	else newLootType = tag_LOOT_COMPUTER;


	return newLootType;
}
string getNewLootFromCourt() {
	string newLootType;



	if (!LCSrandom(20))newLootType = tag_LOOT_JUDGEFILES;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(2))newLootType = tag_LOOT_PDA;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}

string getNewLootFromWhiteHouse() {
	string newLootType;



	if (!LCSrandom(20))newLootType = tag_LOOT_SECRETDOCUMENTS;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(2))newLootType = tag_LOOT_PDA;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}
string getNewLootFromArmy() {
	string newLootType;


	if (!LCSrandom(20))newLootType = tag_LOOT_SECRETDOCUMENTS;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(2))newLootType = tag_LOOT_WATCH;
	else newLootType = tag_LOOT_TRINKET;

	return newLootType;
}
string getNewLootFromIntelligence() {
	string newLootType;


	if (!LCSrandom(20))newLootType = tag_LOOT_SECRETDOCUMENTS;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(2))newLootType = tag_LOOT_PDA;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}
string getNewLootFromCorporate() {
	string newLootType;


	if (!LCSrandom(50))newLootType = tag_LOOT_CORPFILES;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(2))newLootType = tag_LOOT_PDA;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}

string getNewLootFromCorporateHouse() {
	string newLootType;

	if (!LCSrandom(8))newLootType = tag_LOOT_TRINKET;
	else if (!LCSrandom(7))newLootType = tag_LOOT_WATCH;
	else if (!LCSrandom(6))newLootType = tag_LOOT_PDA;
	else if (!LCSrandom(5))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(4))newLootType = tag_LOOT_SILVERWARE;
	else if (!LCSrandom(3))newLootType = tag_LOOT_CHEAPJEWELERY;
	else if (!LCSrandom(2))newLootType = tag_LOOT_FAMILYPHOTO;
	else newLootType = tag_LOOT_COMPUTER;


	return newLootType;
}

string getNewLootFromRadio() {
	string newLootType;


	if (!LCSrandom(20))newLootType = tag_LOOT_AMRADIOFILES;
	else if (!LCSrandom(4))newLootType = tag_LOOT_MICROPHONE;
	else if (!LCSrandom(3))newLootType = tag_LOOT_PDA;
	else if (!LCSrandom(2))newLootType = tag_LOOT_CELLPHONE;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}

string getNewLootFromCable() {
	string newLootType;


	if (!LCSrandom(20))newLootType = tag_LOOT_CABLENEWSFILES;
	else if (!LCSrandom(4))newLootType = tag_LOOT_MICROPHONE;
	else if (!LCSrandom(3))newLootType = tag_LOOT_PDA;
	else if (!LCSrandom(2))newLootType = tag_LOOT_CELLPHONE;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}

string getNewLootFromCCS() {
	string newLootType;


	if (!LCSrandom(5))newLootType = tag_LOOT_CELLPHONE;
	else if (!LCSrandom(4))newLootType = tag_LOOT_SILVERWARE;
	else if (!LCSrandom(3))newLootType = tag_LOOT_TRINKET;
	else if (!LCSrandom(2))newLootType = tag_LOOT_CHEAPJEWELERY;
	else newLootType = tag_LOOT_COMPUTER;

	return newLootType;
}

string getNewLootFromSITE_RESIDENTIAL_TENEMENT() {
	string newLootType;

	if (!LCSrandom(3))newLootType = tag_LOOT_KIDART;
	else if (!LCSrandom(2))newLootType = tag_LOOT_DIRTYSOCK;
	else newLootType = tag_LOOT_FAMILYPHOTO;

	return newLootType;
}
void getGroundLootFromTenement(string &newLootType, string &newWeaponType, string &newArmorType) {
	if (!LCSrandom(25))
	{
		string rndWeps[] = { tag_WEAPON_BASEBALLBAT, tag_WEAPON_CROWBAR, tag_WEAPON_SHANK,
			tag_WEAPON_SYRINGE, tag_WEAPON_CHAIN, tag_WEAPON_GUITAR,tag_WEAPON_SPRAYCAN };
		newWeaponType = pickrandom(rndWeps);
	}
	else if (!LCSrandom(20))
	{
		string rndArmors[] = { tag_ARMOR_CHEAPDRESS, tag_ARMOR_CHEAPSUIT, tag_ARMOR_CLOTHES, tag_ARMOR_TRENCHCOAT,
			tag_ARMOR_WORKCLOTHES, tag_ARMOR_TOGA, tag_ARMOR_PRISONER };
		newArmorType = pickrandom(rndArmors);
	}
	else newLootType = getNewLootFromSITE_RESIDENTIAL_TENEMENT();
}
void getGroundLootFromCCS(string &newLootType, string &newWeaponType, string &newArmorType) {
	//storming a CCS stronghold. Logically you ought to get all the leftover stuff if you win...
	switch (LCSrandom(3))
	{
	case 0:
		newWeaponType = pickrandom(rndWeps);
		break;
	case 1:
		newArmorType = pickrandom(rndArmors);
		break;
	default:
		newLootType = getNewLootFromCCS();
		break;
	}
}
void getGroundLootFromCEOHouse(string &newLootType, string &newWeaponType, string &newArmorType) {

	if (!LCSrandom(50))
	{
		string rndArmors[] = { tag_ARMOR_EXPENSIVEDRESS, tag_ARMOR_EXPENSIVESUIT, tag_ARMOR_EXPENSIVESUIT,
			tag_ARMOR_EXPENSIVESUIT, tag_ARMOR_BONDAGEGEAR };
		newArmorType = pickrandom(rndArmors);
	}
	else
		newLootType = getNewLootFromCorporateHouse();
}
void getGroundLootFromFirestation(string &newLootType, string &newWeaponType, string &newArmorType) {

	if (!LCSrandom(25)) newArmorType = tag_ARMOR_BUNKERGEAR;
	else if (LCSrandom(2))newLootType = tag_LOOT_TRINKET;
	else newLootType = tag_LOOT_COMPUTER;
}
void getGroundLootFromIntelligenceHQ(string &newLootType, string &newWeaponType, string &newArmorType) {

	if (!LCSrandom(24))
	{
		string rndWeps[] = { tag_WEAPON_FLAMETHROWER, tag_WEAPON_SEMIPISTOL_45,
			tag_WEAPON_SMG_MP5, tag_WEAPON_CARBINE_M4, tag_WEAPON_AUTORIFLE_M16 };
		newWeaponType = pickrandom(rndWeps);
	}
	else if (!LCSrandom(30))
	{
		string rndArmors[] = { tag_ARMOR_HEAVYARMOR };
		newArmorType = pickrandom(rndArmors);
	}
	else newLootType = getNewLootFromIntelligence();

}
void getGroundLootFromArmyBase(string &newLootType, string &newWeaponType, string &newArmorType) {

	if (!LCSrandom(3))
	{
		string rndWeps[] = { tag_WEAPON_SEMIPISTOL_9MM, tag_WEAPON_CARBINE_M4, tag_WEAPON_AUTORIFLE_M16 };
		newWeaponType = pickrandom(rndWeps);
	}
	else if (!LCSrandom(2))
	{
		string rndArmors[] = { tag_ARMOR_ARMYARMOR };
		newArmorType = pickrandom(rndArmors);
	}
	else newLootType = getNewLootFromArmy();
}
void getGroundLootFromPoliceStation(string &newLootType, string &newWeaponType, string &newArmorType) {

	if (!LCSrandom(25))
	{
		string rndWeps[] = { tag_WEAPON_NIGHTSTICK, tag_WEAPON_NIGHTSTICK, tag_WEAPON_SHOTGUN_PUMP, tag_WEAPON_SEMIPISTOL_9MM,
			tag_WEAPON_SMG_MP5, tag_WEAPON_CARBINE_M4, tag_WEAPON_AUTORIFLE_M16, tag_WEAPON_AUTORIFLE_M16 };
		//make sure the number of types matches the random range...
		newWeaponType = rndWeps[LCSrandom(4) + 2 - lawList[LAW_GUNCONTROL]];
	}
	else if (!LCSrandom(25))
	{
		string rndArmors[] = { tag_ARMOR_POLICEUNIFORM, tag_ARMOR_POLICEUNIFORM, tag_ARMOR_POLICEARMOR, tag_ARMOR_POLICEUNIFORM,
			tag_ARMOR_SWATARMOR, tag_ARMOR_POLICEUNIFORM, tag_ARMOR_POLICEARMOR, tag_ARMOR_DEATHSQUADUNIFORM };
		//make sure the number of types matches the random range...
		newArmorType = rndArmors[LCSrandom(4) + 2 - lawList[LAW_GUNCONTROL]];
	}
	else newLootType = getNewLootFromPolice();
}
void getGroundLootFromUpscaleApartment(string &newLootType, string &newWeaponType, string &newArmorType) {

	if (!LCSrandom(30))
	{
		string rndWeps[] = { tag_WEAPON_BASEBALLBAT, tag_WEAPON_COMBATKNIFE, tag_WEAPON_DAISHO, tag_WEAPON_SHOTGUN_PUMP,
			tag_WEAPON_REVOLVER_44, tag_WEAPON_SEMIPISTOL_45, tag_WEAPON_SEMIRIFLE_AR15, tag_WEAPON_AUTORIFLE_M16 };
		//make sure the number of types matches the random range...
		newWeaponType = rndWeps[LCSrandom(6 - lawList[LAW_GUNCONTROL])];
	}
	else if (!LCSrandom(20))
	{
		string rndArmors[] = { tag_ARMOR_EXPENSIVEDRESS, tag_ARMOR_BLACKDRESS, tag_ARMOR_EXPENSIVESUIT, tag_ARMOR_BLACKSUIT,
			tag_ARMOR_BONDAGEGEAR, tag_ARMOR_CIVILLIANARMOR, tag_ARMOR_BLACKROBE, tag_ARMOR_LABCOAT };
		newArmorType = pickrandom(rndArmors);
	}
	else newLootType = getNewLootFromApartmentUpscale();
}
void getGroundLootFromApartment(string &newLootType, string &newWeaponType, string &newArmorType) {

	if (!LCSrandom(25))
	{
		string rndWeps[] = { tag_WEAPON_BASEBALLBAT, tag_WEAPON_REVOLVER_38,
			tag_WEAPON_REVOLVER_44, tag_WEAPON_NIGHTSTICK, tag_WEAPON_GUITAR };
		newWeaponType = pickrandom(rndWeps);
	}
	else if (!LCSrandom(20))
	{
		string rndArmors[] = { tag_ARMOR_CHEAPDRESS, tag_ARMOR_CHEAPSUIT, tag_ARMOR_CLOTHES, tag_ARMOR_TRENCHCOAT,
			tag_ARMOR_WORKCLOTHES, tag_ARMOR_CLOWNSUIT, tag_ARMOR_ELEPHANTSUIT, tag_ARMOR_DONKEYSUIT };
		newArmorType = pickrandom(rndArmors);
	}
	else newLootType = getNewLootFromApartment();
}
void pickupAndPrintNewLoot(const string newLootType, const string newWeaponType, const string newArmorType) {

	Item *item;
	item = NULL;
	if (len(newLootType))
	{
		item = getNewLoot(newLootType);
		giveActiveSquadThisLoot(item);
	}
	if (len(newArmorType))
	{
		item = spawnNewArmor(newArmorType);
		giveActiveSquadThisLoot(item);
	}
	if (len(newWeaponType))
	{

		item = spawnNewWeapon(newWeaponType);
		giveActiveSquadThisLoot(item);
	}
	if (item)
	{
		printYouFind(item->equip_title());
		pressAnyKey(); //wait for key press before clearing.
	}
}
void getThatGroundLoot() {


	int time = 20 + LCSrandom(10);
	if (time < 1)time = 1;
	if (sitealarmtimer > time || sitealarmtimer == -1)sitealarmtimer = time;
	string newLootType, newWeaponType, newArmorType;
	switch (sitetype)
	{
	case SITE_RESIDENTIAL_TENEMENT:
		getGroundLootFromTenement(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_BUSINESS_BANK:
		newLootType = getNewLootFromBank();
		break;
	case SITE_RESIDENTIAL_APARTMENT:
		getGroundLootFromApartment(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
		getGroundLootFromUpscaleApartment(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_LABORATORY_COSMETICS:
	case SITE_INDUSTRY_NUCLEAR:
	case SITE_LABORATORY_GENETIC:
		newLootType = getNewLootFromLab();
		break;
	case SITE_GOVERNMENT_POLICESTATION:
		getGroundLootFromPoliceStation(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_GOVERNMENT_COURTHOUSE:
		newLootType = getNewLootFromCourt();
		break;
	case SITE_GOVERNMENT_PRISON:
		if (!LCSrandom(5))
			newArmorType = tag_ARMOR_PRISONER;
		else newWeaponType = tag_WEAPON_SHANK;
		break;
	case SITE_GOVERNMENT_WHITE_HOUSE:
		newLootType = getNewLootFromWhiteHouse();
		break;
	case SITE_GOVERNMENT_ARMYBASE:
		getGroundLootFromArmyBase(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_GOVERNMENT_INTELLIGENCEHQ:
		getGroundLootFromIntelligenceHQ(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_GOVERNMENT_FIRESTATION:
		getGroundLootFromFirestation(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_INDUSTRY_SWEATSHOP:
		newLootType = tag_LOOT_FINECLOTH;
		break;
	case SITE_INDUSTRY_POLLUTER:
		newLootType = tag_LOOT_CHEMICAL;
		break;
	case SITE_CORPORATE_HEADQUARTERS:
		newLootType = getNewLootFromCorporate();
		break;
	case SITE_CORPORATE_HOUSE:
		getGroundLootFromCEOHouse(newLootType, newWeaponType, newArmorType);
		break;
	case SITE_MEDIA_AMRADIO:
		newLootType = getNewLootFromRadio();
		break;
	case SITE_MEDIA_CABLENEWS:
		newLootType = getNewLootFromCable();
		break;
	case SITE_BUSINESS_BARANDGRILL:
	case SITE_OUTDOOR_BUNKER:
	case SITE_RESIDENTIAL_BOMBSHELTER:
		getGroundLootFromCCS(newLootType, newWeaponType, newArmorType);
		break;
	}
	pickupAndPrintNewLoot(newLootType, newWeaponType, newArmorType);
}
void pressedKeyG(const bool enemy, int& encounter_timer) {
	if ((isThereGroundLoot() || (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_LOOT)))
	{
		bool tookground = 0;
		if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_LOOT)
		{
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag &= ~SITEBLOCK_LOOT;
			if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
			{
				//GRAB SOME OF THE BASE LOOT
				int lcount = 1; //1 FROM THE ONE DELETED ABOVE
				for (int x = 0; x < MAPX; x++)
					for (int y = 0; y < MAPY; y++)
						for (int z = 0; z < MAPZ; z++)
							if (levelmap[x][y][z].flag&SITEBLOCK_LOOT)
								lcount++;
				int lplus = LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, getCurrentSite()) / lcount;
				if (lcount == 1) lplus = LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, getCurrentSite());
				for (; lplus > 0; lplus--)
				{
					getRandomLoot(getCurrentSite());
				}
			}
			else
			{
				getThatGroundLoot();
			}
			tookground = 1;
		}
		//MAKE GROUND LOOT INTO MISSION LOOT
		for (int l = 0; l < len(groundloot); l++)
			giveActiveSquadThisLoot(groundloot[l]);
		groundloot.clear();
		if (enemy&&isThereASiteAlarm())enemyattack();
		else if (enemy)disguisecheck(encounter_timer);
		if (tookground)
		{
			// If the party steals from the ground, party member 0 gets the blame
			juiceparty(1, 200);
			alienationcheck(0);
			noticecheck(-1);
			sitecrime++;
			sitestory->crime.push_back(CRIME_STOLEGROUND);
			if (enemy)
				criminalize(*(activesquad->squad[0]), LAWFLAG_THEFT);
		}
		creatureadvance();
		encounter_timer++;
	}
}
void enemyAttemptsFreeShots(int& encounter_timer) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();

	//ENEMIES SHOULD GET FREE SHOTS NOW
	if (isThereASiteAlarm())
	{
		bool snuck_away = true;
		// Try to sneak past
		for (int e = 0; e < ENCMAX && snuck_away; e++)
		{
			if (encounter[e].exists &&
				encounter[e].alive  &&
				get_encounter_cantbluff_is_two(e))
			{
				// You can't sneak past this person; they already know you're there
				snuck_away = false;
			}
		}
		// If you can sneak past all enemies
		if (snuck_away)
		{
			for (int e = 0; e < ENCMAX && snuck_away; e++)
			{
				if (!encounter[e].exists)continue;
				for (int i = 0; i < 6; i++)
				{
					if (activesquad->squad[i])
					{
						int roll = activesquad->squad[i]->skill_roll(SKILL_STEALTH);
						if (roll + 1 == DIFFICULTY_HARD && fieldskillrate == FIELDSKILLRATE_HARD)
							activesquad->squad[i]->train(SKILL_STEALTH, 10);
						if (roll < DIFFICULTY_HARD)
						{
							snuck_away = false;
							break;
						}
					}
				}
			}
		}
		// If snuck past everyone
		if (snuck_away)
		{
			for (int i = 0; i < 6; i++)
			{
				if (activesquad->squad[i] != NULL)
				{
					switch (fieldskillrate)
					{
					case FIELDSKILLRATE_FAST:
						activesquad->squad[i]->train(SKILL_STEALTH, 40); break;
					case FIELDSKILLRATE_CLASSIC:
						activesquad->squad[i]->train(SKILL_STEALTH, 10); break;
					case FIELDSKILLRATE_HARD:
						activesquad->squad[i]->train(SKILL_STEALTH, 0); break;
					}
				}
			}
			printSneakPast();
			pressAnyKey();
		}
		else
			enemyattack();
	}
	else disguisecheck(encounter_timer);
}
void bailUponVictory() {
	music.play(MUSIC_CONQUER);
	if (LocationsPool::getInstance().isThisUnderAttack(getCurrentSite()))sitestory->type = NEWSSTORY_SQUAD_DEFENDED;
	else sitestory->type = NEWSSTORY_SQUAD_BROKESIEGE;
	if (LocationsPool::getInstance().getSiegeType(getCurrentSite()) == SIEGE_CCS)
	{
		// CCS DOES NOT capture the warehouse -- reverse earlier assumption of your defeat!
		if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_INDUSTRY_WAREHOUSE || LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_BUSINESS_CRACKHOUSE)
			LocationsPool::getInstance().setRenting(getCurrentSite(), RENTING_PERMANENT);
		else if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_RESIDENTIAL_TENEMENT)
			LocationsPool::getInstance().setRenting(getCurrentSite(), 200);
		else if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_RESIDENTIAL_APARTMENT)
			LocationsPool::getInstance().setRenting(getCurrentSite(), 650);
		else if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_RESIDENTIAL_APARTMENT_UPSCALE)
			LocationsPool::getInstance().setRenting(getCurrentSite(), 1500);
	}
	//DEAL WITH PRISONERS AND STOP BLEEDING
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL)continue;
		if (activesquad->squad[p]->is_holding_body())
		{
			activesquad->squad[p]->deal_with_prisoner();
		}
	}
	//Clear all bleeding and prison escape flags
	CreaturePool::getInstance().clearAllBleedingAndEscapeFlags();
	//INFORM
	printFoughtOffConservatives();

	pressAnyKey();
	conquertext();
	escapesiege(1);
}
void bailOnBase() {
	// Seperate logging message.	
	logBailOnBase(activesquad->name, 
		LocationsPool::getInstance().isThisAFront(getCurrentSite()) != -1
		? LocationsPool::getInstance().getFrontName(getCurrentSite())
		: LocationsPool::getInstance().getLocationName(getCurrentSite()));

	//RESET MODE PRIOR TO CHASE
	showcarprefs = 0;
	//CHASE SEQUENCE OR FOOT CHASE
	chaseseq.clean();
	chaseseq.location = getCurrentSite();
	long level = sitecrime;
	if (!isThereASiteAlarm())level = 0;
	if (LCSrandom(3) && level < 4)level = 0;
	if (LCSrandom(2) && level < 8)level = 0;
	if (postalarmtimer < 10 + (int)LCSrandom(20))level = 0;
	else if (postalarmtimer < 20 + (int)LCSrandom(20) && LCSrandom(3))level = 0;
	else if (postalarmtimer < 40 + (int)LCSrandom(20) && !LCSrandom(3))level = 0;
	if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))level = 1000;
	//MAKE SURE YOU ARE GUILTY OF SOMETHING
	bool guilty = 0;
	for (int p = 0; p < 6; p++) {
		if (activesquad->squad[p] != NULL) {
			if (iscriminal(activesquad->squad[p]->getCreatureJustice())) {
				guilty = 1; 
			}
		}
	}
	if (!guilty)level = 0;
	makechasers(sitetype, level);
	bool havecar = 0;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->carid != -1)
			{
				havecar = 1;
				for (int i = 0; i < 6; i++)
				{
					if (activesquad->squad[i] != NULL &&
						activesquad->squad[i]->carid == -1)
					{
						activesquad->squad[i]->carid = activesquad->squad[p]->carid;
					}
				}
				break;
			}
		}
	}
	bool gotout;
	if (havecar)gotout = chasesequence();
	else gotout = footchase();
	//If you survived
	if (gotout)
	{
		//Check for hauled prisoners/corpses
		for (int p = 0; p < 6; p++)
		{
			if (activesquad->squad[p] == NULL)continue;
			if (activesquad->squad[p]->is_holding_body())
			{

				activesquad->squad[p]->deal_with_prisoner();
			}
		}
		//Clear all bleeding and prison escape flags
		CreaturePool::getInstance().clearAllBleedingAndEscapeFlags();
		//END SITE MODE
		if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
		{
			//Special handling for escaping siege
			escapesiege(0);
		}
		else
		{
			resolvesite();
		}
	}
	//You didn't survive -- handle squad death (unless that ended the game)
	else if (!endcheck())
	{
		if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
		{
			//Report on squad killed during siege
			if (LocationsPool::getInstance().isThisUnderAttack(getCurrentSite()))sitestory->type = NEWSSTORY_SQUAD_KILLED_SIEGEATTACK;
			else sitestory->type = NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE;
			LocationsPool::getInstance().isThereASiegeHere(getCurrentSite(), 0);
		}
		else
		{
			//Or report on your failed raid
			sitestory->type = NEWSSTORY_SQUAD_KILLED_SITE;
			//Would juice the party here, but you're all dead, so...
			resolvesite();
		}
	}
}
void bailUponDefeatCCS() {
	music.play(MUSIC_CONQUER);
	//DEAL WITH PRISONERS AND STOP BLEEDING
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL)continue;
		if (activesquad->squad[p]->is_holding_body())
		{
			activesquad->squad[p]->deal_with_prisoner();
		}
	}
	//Clear all bleeding and prison escape flags
	CreaturePool::getInstance().clearAllBleedingAndEscapeFlags();
	//INFORM
	printTheCCSIsBroken();
	pressAnyKey();
	LocationsPool::getInstance().captureSite(getCurrentSite());
	// CCS Safehouse killed?
	if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_RESIDENTIAL_BOMBSHELTER ||
		LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_BUSINESS_BARANDGRILL ||
		LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_OUTDOOR_BUNKER)
	{
		ccs_kills++;
		if (ccs_kills < 3) endgamestate--;
		else endgamestate = ENDGAME_CCS_DEFEATED;
	}
	conquertextccs();
}
int attemptResolveSiege(const int olocx, const int olocy, const int olocz) {

	if (loc_coord.locx != olocx || loc_coord.locy != olocy || loc_coord.locz != olocz)
		emptyEncounter();
	//MOVE SIEGE UNITS AROUND
	//MOVE UNITS
	vector<int> unitx, unity, unitz;
	for (int x = 0; x < MAPX; x++) for (int y = 0; y < MAPY; y++) for (int z = 0; z < MAPZ; z++)
		if (levelmap[x][y][z].siegeflag&SIEGEFLAG_UNIT)
			unitx.push_back(x), unity.push_back(y), unitz.push_back(z);
	int sx = 0, sy = 0, sz = 0;
	for (int u = 0; u < len(unitx); u++)
	{
		// don't leave tile if player is here
		if (unitx[u] == loc_coord.locx && unity[u] == loc_coord.locy && unitz[u] == loc_coord.locz) continue;
		// move into player's tile if possible
		if ((((unitx[u] == loc_coord.locx - 1 || unitx[u] == loc_coord.locx + 1) &&
			unity[u] == loc_coord.locy) ||
			((unity[u] == loc_coord.locy - 1 || unity[u] == loc_coord.locy + 1) &&
				unitx[u] == loc_coord.locx))
			&& unitz[u] == loc_coord.locz)
		{
			levelmap[unitx[u]][unity[u]][unitz[u]].siegeflag &= ~SIEGEFLAG_UNIT;
			//Get torched
			if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_PEAK)
				levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag |= SIEGEFLAG_UNIT_DAMAGED;
			//BLOW TRAPS
			if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag & SIEGEFLAG_TRAP)
			{
				levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag &= ~SIEGEFLAG_TRAP;
				levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag |= SIEGEFLAG_UNIT_DAMAGED;
			}
			else levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag |= SIEGEFLAG_UNIT;
			continue;
		}
		sz = 0;
		switch (LCSrandom(4))
		{
		case 0: sx = -1, sy = 0; break;
		case 1: sx = 1, sy = 0; break;
		case 2: sx = 0, sy = 1; break;
		case 3: sx = 0, sy = -1; break;
		}
		sx += unitx[u], sy += unity[u], sz += unitz[u];
		if (sx >= 0 && sx < MAPX&&sy >= 0 && sy < MAPY&&sz >= 0 && sz < MAPZ)
			if (!(levelmap[sx][sy][sz].flag&SITEBLOCK_BLOCK))
			{
				if ((levelmap[sx][sy][sz].flag&SITEBLOCK_DOOR))
					levelmap[sx][sy][sz].flag &= ~(SITEBLOCK_DOOR | SITEBLOCK_LOCKED | SITEBLOCK_KLOCK | SITEBLOCK_CLOCK);
				else
				{  //BLOCK PASSAGE
					if (!(levelmap[sx][sy][sz].siegeflag&(SIEGEFLAG_UNIT | SIEGEFLAG_HEAVYUNIT)))
					{
						levelmap[unitx[u]][unity[u]][unitz[u]].siegeflag &= ~SIEGEFLAG_UNIT;
						//BLOW TRAPS
						if (levelmap[sx][sy][sz].siegeflag&SIEGEFLAG_TRAP)
						{
							levelmap[sx][sy][sz].siegeflag &= ~SIEGEFLAG_TRAP;
							levelmap[sx][sy][sz].siegeflag |= SIEGEFLAG_UNIT_DAMAGED;
						}
						else levelmap[sx][sy][sz].siegeflag |= SIEGEFLAG_UNIT;
					}
				}
			}
	}
	unitx.clear(), unity.clear(), unitz.clear();
	for (int u = 0; u < len(unitx); u++)
	{
		sz = 0;
		switch (LCSrandom(4))
		{
		case 0: sx = -1, sy = 0; break;
		case 1: sx = 1, sy = 0; break;
		case 2: sx = 0, sy = 1; break;
		case 3: sx = 0, sy = -1; break;
		}
		sx += unitx[u], sy += unity[u], sz += unitz[u];
		if (sx >= 0 && sx < MAPX&&sy >= 0 && sy < MAPY&&sz >= 0 && sz < MAPZ)
			if (!(levelmap[sx][sy][sz].flag&SITEBLOCK_BLOCK) && (levelmap[sx][sy][sz].flag&SITEBLOCK_DOOR))
				levelmap[sx][sy][sz].flag &= ~(SITEBLOCK_DOOR | SITEBLOCK_LOCKED | SITEBLOCK_KLOCK | SITEBLOCK_CLOCK);
	}
	unitx.clear(), unity.clear(), unitz.clear();
	//NEW WAVES
	//IF THERE AREN'T ENOUGH UNITS AROUND
	//AND THEY HAVEN'T BEEN SCARED OFF
	//MORE WAVES WILL ATTACK
	//AND IT GETS WORSE AND WORSE
	//but not as bad as it used to get,
	//since the extra waves are small
	LocationsPool::getInstance().tickAttackTime(getCurrentSite());
	if ((LocationsPool::getInstance().get_specific_integer(INT_GETATTACKTIME, getCurrentSite()) >= 100 + LCSrandom(10) &&
		(loc_coord.locz != 0 || loc_coord.locx<(MAPX / 2 - 3) || loc_coord.locx>(MAPX / 2 + 3) ||
			loc_coord.locy > 5)))
	{
		LocationsPool::getInstance().resetAttackTime(getCurrentSite());
		int existingUnits = 0;
		for (int x = 0; x < MAPX; x++) for (int y = 0; y < MAPY; y++) for (int z = 0; z < MAPZ; z++)
			if (levelmap[x][y][z].siegeflag&(SIEGEFLAG_UNIT | SIEGEFLAG_HEAVYUNIT))
				existingUnits++;
		//PLACE UNITS
		int lx, ly, lz, unitnum = 7 - existingUnits, count = 10000;
		if (unitnum < 0)unitnum = 0;
		for (int t = 0; t < unitnum; t++)
		{
			count = 10000;
			do
			{
				lx = LCSrandom(7) + (MAPX / 2) - 3, ly = LCSrandom(5), lz = 0, count--;
				if (count == 0) break;
			} while ((levelmap[lx][ly][lz].flag & (SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT)) ||
				(levelmap[lx][ly][lz].siegeflag & (SIEGEFLAG_UNIT | SIEGEFLAG_HEAVYUNIT | SIEGEFLAG_TRAP)));
			levelmap[lx][ly][lz].siegeflag |= SIEGEFLAG_UNIT;
		}
		if (!LocationsPool::getInstance().get_specific_integer(INT_DOWEHAVETANKTRAPS, getCurrentSite()) &&
			LocationsPool::getInstance().getSiegeType(getCurrentSite()) == SIEGE_POLICE &&
			LocationsPool::getInstance().getSiegeEscalationState(getCurrentSite()) >= 2)
		{
			count = 10000;
			int hunitnum = 1;
			for (int t = 0; t < hunitnum; t++)
			{
				do
				{
					lx = LCSrandom(7) + (MAPX / 2) - 3, ly = LCSrandom(5), lz = 0, count--;
					if (count == 0) break;
				} while ((levelmap[lx][ly][lz].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT)) ||
					(levelmap[lx][ly][lz].siegeflag&(SIEGEFLAG_UNIT | SIEGEFLAG_HEAVYUNIT | SIEGEFLAG_TRAP)));
				levelmap[lx][ly][lz].siegeflag |= SIEGEFLAG_HEAVYUNIT;
				LocationsPool::getInstance().spawnATank(getCurrentSite());
			}
		}
	}
	//CHECK FOR SIEGE UNITS
	//INCLUDING DAMAGED ONES
	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag&SIEGEFLAG_UNIT)
	{
		if (addsiegeencounter(SIEGEFLAG_UNIT))
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag &= ~SIEGEFLAG_UNIT;
	}
	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag&SIEGEFLAG_HEAVYUNIT)
	{
		if (addsiegeencounter(SIEGEFLAG_HEAVYUNIT))
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag &= ~SIEGEFLAG_HEAVYUNIT;
	}
	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag&SIEGEFLAG_UNIT_DAMAGED)
	{
		if (addsiegeencounter(SIEGEFLAG_UNIT_DAMAGED))
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].siegeflag &= ~SIEGEFLAG_UNIT_DAMAGED;
	}
	//BAIL UPON VICTORY
	if (LocationsPool::getInstance().get_specific_integer(INT_GETSIEGEKILLS, getCurrentSite()) >= 10 &&
		LocationsPool::getInstance().get_specific_integer(INT_GETSIEGETANKS, getCurrentSite()) < 1 &&
		LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		bailUponVictory();
		return 1;
	}
	return 0;
}

void encounterCafeComputer() {

	if (isThereASiteAlarm() || sitealienate)
	{
		printCafeComputerEmpty();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
	}
	else
	{
		printCafeComputerFull();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
		prepareencounter(sitetype, 0);
	}
}
void encounterRestaurantTable() {
	if (isThereASiteAlarm() || sitealienate)
	{
		printRestaurantTableHiding();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
		prepareencounter(sitetype, 0);
	}
	else
	{
		printRestaurantTableFull();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
		prepareencounter(sitetype, 0);
	}
}

void encounterParkBench() {

	if (isThereASiteAlarm() || sitealienate)
	{
		printEmptyBench();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
	}
	else
	{
		printFullBench();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
		prepareencounter(sitetype, 0);
	}
}
void encounterSpecialHouseCEO() {

	if ((isThereASiteAlarm() || sitealienate || LocationsPool::getInstance().isThereASiegeHere(getCurrentSite())) &&
		uniqueCreatures.CEO_state == UNIQUECREATURE_ALIVE)
	{
		printTheCEOHasFled();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
	}
	else
	{
		switch (uniqueCreatures.CEO_state)
		{
		case UNIQUECREATURE_ALIVE:
			printTheCEOIsIn();
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
			pressAnyKey();
			emptyEncounter();
			spawnCreatureCEO();
			break;
		case UNIQUECREATURE_DEAD:
		case UNIQUECREATURE_LIBERAL:			
			void printTheCEOIsOut();
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
			pressAnyKey();
			break;
		}
	}
}

void encounterApartmentLandlord() {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();

	if (isThereASiteAlarm() || sitealienate ||
		LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		printTheLandlordIsOut();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
	}
	else
	{
		printTheLandlordIsIn();
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = -1;
		pressAnyKey();
		emptyEncounter();
		make_creature_without_encounter_array(0, CREATURE_LANDLORD);
	}
}
void encounterOtherSpecial(const int olocx, const int olocy, const int olocz) {

	bool squadmoved = (olocx != loc_coord.locx || olocy != loc_coord.locy || olocz != loc_coord.locz);
	if (squadmoved &&
		(LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_RESIDENTIAL_APARTMENT ||
			LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_RESIDENTIAL_TENEMENT ||
			LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_RESIDENTIAL_APARTMENT_UPSCALE))
	{
		if (LCSrandom(3))return; // Rarely encounter someone in apartments.
	}
	prepareencounter(sitetype, LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()));
	// Since vector<NameAndAlignment> encounter is read-only, this must be called AFTER the encounter has been prepared.
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int numenc = 0;
	// TODO This is bizarre
	// the for loop breaks if it finds an empty encounter
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].exists) numenc++;
		else break;
	}
	if (encounterwarnings&&numenc > 0)
	{  // show an encounter warning, based on whether the squad moved or not and the size of the encounter
		printShowEncounterWarning(numenc, squadmoved);
		pressAnyKey();
	}
}

void encounterSpecial(const int makespecial, const int olocx, const int olocy, const int olocz) {
	switch (makespecial)
	{
	case SPECIAL_CAFE_COMPUTER:
		encounterCafeComputer();
		break;
	case SPECIAL_RESTAURANT_TABLE:
		encounterRestaurantTable();
		break;
	case SPECIAL_PARK_BENCH:
		encounterParkBench();
		break;
	case SPECIAL_SECURITY_CHECKPOINT:
		special_security_checkpoint();
		break;
	case SPECIAL_SECURITY_METALDETECTORS:
		special_security_metaldetectors();
		break;
	case SPECIAL_SECURITY_SECONDVISIT:
		special_security_secondvisit();
		break;
	case SPECIAL_CLUB_BOUNCER:
		special_bouncer_assess_squad();
		break;
	case SPECIAL_CLUB_BOUNCER_SECONDVISIT:
		special_bouncer_greet_squad();
		break;
	case SPECIAL_HOUSE_CEO:
		encounterSpecialHouseCEO();
		break;
	case SPECIAL_APARTMENT_LANDLORD:
		encounterApartmentLandlord();
		break;
	case SPECIAL_BANK_TELLER:
		special_bank_teller();
		break;
	case SPECIAL_CCS_BOSS:
		special_ccs_boss();
		break;
	case SPECIAL_OVAL_OFFICE_NW:
	case SPECIAL_OVAL_OFFICE_NE:
	case SPECIAL_OVAL_OFFICE_SW:
	case SPECIAL_OVAL_OFFICE_SE:
		special_oval_office();
		break;
	default:
		encounterOtherSpecial(olocx, olocy, olocz);
		break;
	}
}
void pressedKeyShiftL() {

	reloadparty();
	printparty();
	refreshAlt();
	creatureadvance();

}
// return true if leaving site
int moveOrWaitThenCheckForExit(const int olocx, const int olocy, const int olocz, const char c, const int encsize, char& hostcheck) {

	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();



	//SEE IF THERE IS AN ENCOUNTER
	char newenc = 0;
	// 10% chance of encounter normally (100% if waiting)
	// 20% chance of encounter after massive response
	// 0% chance of encounter during sieges
	if (!LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		if (postalarmtimer > 80) { if (!LCSrandom(5)) newenc = 1; }
		else if (!LCSrandom(10) || c == 's') newenc = 1;
	}
	for (int e = 0; e < ENCMAX; e++) if (encounter[e].exists) newenc = 0;
	// Handle special tiles that activate when you step on them
	// (rather than those that must be manually ACTIVATED)
	long makespecial = -1;
	switch (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special)
	{
	case SPECIAL_SECURITY_CHECKPOINT:
	case SPECIAL_SECURITY_METALDETECTORS:
	case SPECIAL_SECURITY_SECONDVISIT:
	case SPECIAL_CLUB_BOUNCER:
	case SPECIAL_CLUB_BOUNCER_SECONDVISIT:
	case SPECIAL_APARTMENT_LANDLORD:
	case SPECIAL_HOUSE_CEO:
	case SPECIAL_RESTAURANT_TABLE:
	case SPECIAL_CAFE_COMPUTER:
	case SPECIAL_PARK_BENCH:
	case SPECIAL_BANK_TELLER:
	case SPECIAL_CCS_BOSS:
	case SPECIAL_OVAL_OFFICE_NW:
	case SPECIAL_OVAL_OFFICE_NE:
	case SPECIAL_OVAL_OFFICE_SW:
	case SPECIAL_OVAL_OFFICE_SE:
		makespecial = levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special;
		newenc = 1;
		break;
	}
	//DO DOORS
	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_DOOR)
	{
		open_door(levelmap[olocx][olocy][olocz].flag&SITEBLOCK_RESTRICTED);
		loc_coord.locx = olocx, loc_coord.locy = olocy, loc_coord.locz = olocz;
		if (encsize > 0) newenc = 0;
	}
	//BAIL UPON VICTORY (version 2 -- defeated CCS safehouse)
	if (ccs_boss_kills >= 1 &&
		!LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) &&
		LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
	{
		bailUponDefeatCCS();
		showcarprefs = 0;
		return 1;
	}
	if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite())) // *JDS* police response added
	{
		if (attemptResolveSiege(olocx, olocy, olocz)) {
			showcarprefs = 0;
			return 1;
		}
	}
	if (!LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) && newenc)
	{
		encounterSpecial(makespecial, olocx, olocy, olocz);
		hostcheck = 1;
	}
	if (!LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
		if ((loc_coord.locx != olocx || loc_coord.locy != olocy || loc_coord.locz != olocz) && !newenc)
			putBackSpecials(olocx, olocy, olocz);

	if (loc_coord.locx != olocx || loc_coord.locy != olocy || loc_coord.locz != olocz)
	{
		//NUKE GROUND LOOT
		delete_and_clear_groundloot();
		//MOVE BLOOD
		if (levelmap[olocx][olocy][olocz].flag&SITEBLOCK_BLOODY2)
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_BLOODY;
	}
	knowmap();


	return 0;
}
void partyIsAliveOnSite(const bool enemy,
	const int talkers,
	const bool freeable) {

	const int hostages = countactivesquadhostages();
	const int partysize = activesquadSize();
	const int libnum = CreaturePool::getInstance().countLiberals(getCurrentSite());
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();

	printPlayerSiteOptions(isThereASiteAlarm(), enemy, partysize, party_status, talkers);

	bool graffiti = false;
	bool print_me = false;
	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special != -1 &&
		levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special != SPECIAL_CLUB_BOUNCER_SECONDVISIT)print_me = true;
	else if (!(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & (SITEBLOCK_GRAFFITI | SITEBLOCK_BLOODY2)))
	{
		if ((levelmap[loc_coord.locx + 1][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_BLOCK) ||
			(levelmap[loc_coord.locx - 1][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_BLOCK) ||
			(levelmap[loc_coord.locx][loc_coord.locy + 1][loc_coord.locz].flag & SITEBLOCK_BLOCK) ||
			(levelmap[loc_coord.locx][loc_coord.locy - 1][loc_coord.locz].flag & SITEBLOCK_BLOCK))
		{
			bool can_graffiti = false;
			for (int i = 0; i < 6 && !can_graffiti; i++)
			{
				if (!activesquad->squad[i]) i = 6;
				else can_graffiti = activesquad->squad[i]->get_weapon().get_specific_bool(BOOL_CAN_GRAFFITI_);

			}
			if (can_graffiti) {

				print_me = true;
				graffiti = true;

			}
			else print_me = false;
		}
		else print_me = false;
	}
	else print_me = false;
	printUseOrGraffiti(graffiti, print_me);
	if (enemy&&isThereASiteAlarm())
	{
		bool evade = false;
		for (int e = 0; e < ENCMAX; e++)
		{
			if (encounter[e].exists &&
				encounter[e].alive  &&
				get_encounter_cantbluff_is_two(e))
			{
				// You can't sneak past this person; they already know you're there
				evade = true;
				break;
			}
		}
		printSneakOrRun(evade);
	}
	else
	{
		printEvade();
	}
	printEquipAndFight(enemy);
	if (!LocationsPool::getInstance().isThereASiegeHere(getCurrentSite())) {
		if (freeable && (!enemy || !isThereASiteAlarm()))
		{
			printReleaseOppressed();
		}
		else
		{
			printReleaseHostages(hostages);
		}
	}
	else
	{
		printReorganize(libnum);

	}
}

void onSiteButNoSiege() {
	printLocationNameAndAlarm(LocationsPool::getInstance().getLocationNameWithGetnameMethod(getCurrentSite(), -1, true), postalarmtimer, loc_coord.locz);
	if (postalarmtimer > 80)
	{
		printLocationSpecificWarning(LocationsPool::getInstance().getLocationType(getCurrentSite()), LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS);
		
		music.play(MUSIC_HEAVYCOMBAT);
	}
	else if (postalarmtimer > 60) { printCONSERVATIVE_REINFORCEMENTS_INCOMING(); music.play(MUSIC_ALARMED); }
	else if (sitealienate == 1) { printALIENATED_MASSES(); music.play(MUSIC_ALARMED); }
	else if (sitealienate == 2) { printALIENATED_EVERYONE(); music.play(MUSIC_ALARMED); }
	else if (isThereASiteAlarm()) { printCONSERVATIVES_ALARMED(); music.play(MUSIC_ALARMED); }
	else if (sitealarmtimer == 0) { printCONSERVATIVES_SUSPICIOUS(); music.play(MUSIC_SUSPICIOUS); }
	else music.play(MUSIC_SITEMODE);
}

void playSiegeMusic() {
	music.play(MUSIC_DEFENSE);
	printSiegeName(LocationsPool::getInstance().getLocationNameWithGetnameMethod(getCurrentSite(), -1, true), loc_coord.locz);
}

void partyPerformsAction(const int c, const bool canMove, const bool enemy, const int talkers, int &encounter_timer) {

	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();


	switch (c) {
	case 'w':
	case KEY_UP:
		if (canMove && loc_coord.locy > 0 && !(levelmap[loc_coord.locx][loc_coord.locy - 1][loc_coord.locz].flag & SITEBLOCK_BLOCK))loc_coord.locy--;
		break;
	case 'a':
	case KEY_LEFT:
		if (canMove && !(levelmap[loc_coord.locx - 1][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_BLOCK))loc_coord.locx--;
		break;
	case 'd':
	case KEY_RIGHT:
		if (canMove && !(levelmap[loc_coord.locx + 1][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_BLOCK))loc_coord.locx++;
		break;
	case 'x':
	case KEY_DOWN:
		if (canMove && !(levelmap[loc_coord.locx][loc_coord.locy + 1][loc_coord.locz].flag & SITEBLOCK_BLOCK))loc_coord.locy++;
		break;
	case 'u':
		pressedKeyU(enemy);
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
		if (activesquad->squad[c - '1'] != NULL)
		{
			if (party_status == c - '1')fullstatus(party_status);
			else party_status = c - '1';
		}
		break;
	case 'k':
		if (enemy) { kidnapattempt(); }
		break;
	case 'e':
		mapshowing = false;
		equip(activesquad->loot, -1);
		if (enemy&&isThereASiteAlarm())enemyattack();
		else if (enemy)disguisecheck(encounter_timer);
		creatureadvance();
		encounter_timer++;
		mapshowing = true;
		break;
	case 'n':
		pressedKeyN();
		break;
	case 'l':
		if ((!enemy || !isThereASiteAlarm())) {
			pressedKeyL();
			encounter_timer++;
		}
		break;
	case 'j':
		if ((!enemy || !isThereASiteAlarm())) {
			pressedKeyShiftL();
			encounter_timer++;
		}
		break;
	case 't':
		if (talkers) {
			pressedKeyT(enemy, encounter_timer);
		}
		break;
	case '0':
		party_status = -1;
		break;
	case 'm':
		pressedKeyM();
		break;
	case 'f':
		if (enemy) { pressedKeyF(encounter_timer); }
		break;
	case 'g':
		pressedKeyG(enemy, encounter_timer);
		break;
	}

}
void recounttalkers(int& talkers) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	talkers = 0;
	for (int e = 0; e < ENCMAX; e++)
		if (encounter[e].exists)
			if (encounter[e].enemy && (get_encounter_cantbluff_is_zero(e) || getEncounterAnimalGloss(e) == ANIMALGLOSS_ANIMAL)) talkers++;
}

bool canactivesquadmove(int& c, const bool enemy) {

	bool canMove = !enemy || !isThereASiteAlarm();
	{
		if (c == 'v'&&enemy&&isThereASiteAlarm())
		{
			char override = whichWay();
			if (override) {
				c = override;
				canMove = true;
			}

		}
	}
	return canMove;
}
void checkForHostageScream(char &hostcheck) {

	//PRINT SITE MAP
	printsitemap(loc_coord.locx, loc_coord.locy, loc_coord.locz);
	//CHECK IF YOU HAVE A SQUIRMING AMATEUR HOSTAGE
	//hostcheck SHOULD ONLY BE 1 WHEN A NEWENC IS CREATED
	if (hostcheck)
	{
		char havehostage = 0;
		//Check your whole squad
		for (int p = 0; p < 6; p++)
		{
			if (activesquad->squad[p] != NULL)
			{
				//If they're unarmed and dragging someone
				if (activesquad->squad[p]->is_holding_body() &&
					!activesquad->squad[p]->get_weapon().get_specific_bool(BOOL_CAN_THREATEN_HOSTAGES_))
				{
					//And that someone is not an LCS member
					if (activesquad->squad[p]->is_prisoner_non_LCS())
					{
						//They scream for help -- flag them kidnapped, cause alarm
						activesquad->squad[p]->mark_prisoner_as_kidnapped();
						if (activesquad->squad[p]->type == CREATURE_RADIOPERSONALITY)offended_amradio = 1;
						if (activesquad->squad[p]->type == CREATURE_NEWSANCHOR)offended_cablenews = 1;
						havehostage = 1;
					}
				}
			}
		}
		if (havehostage)
		{
			alienationcheck(1);
			sitecrime += 5;
			criminalizeparty(LAWFLAG_KIDNAPPING);
		}
		hostcheck = 0;
		clearmessagearea();
	}

}
void destroyActiveCars() {

	if (!LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		for (int p = 0; p < 6; p++)
		{
			const int id = getactivesquadCarID(p);
			if (id != -1)
				deleteVehicle(id_getcar(id));
		}
	}
}

void partyIsDeadOnSite() {
	//DESTROY ALL CARS BROUGHT ALONG WITH PARTY
	destroyActiveCars();
	killActiveSquad();
	endcheck(END_BUT_NOT_END); // play the right music in case we're dead
	printReflectOnIneptitude();
}
void addNewLineIfFoughtThisRound() {

	if (foughtthisround) { logNewLine(); }
	foughtthisround = 0;
}
// Return true if supposed to still be in mode_site(), false otherwise
bool increment_mode_site(char &bail_on_base, char &hostcheck, int &encounter_timer) {

	int encsize;
	bool freeable;
	bool enemy;
	int majorenemy;
	int talkers;
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();

	encsize = 0;
	freeable = false;
	enemy = false;
	majorenemy = 0;
	talkers = 0;

	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].exists)
		{
			encsize++;
			if (encounter[e].enemy) { 
				enemy = true;
			}
			if (encounter[e].type == CREATURE_WORKER_SERVANT ||
				encounter[e].type == CREATURE_WORKER_FACTORY_CHILD ||
				encounter[e].type == CREATURE_WORKER_SWEATSHOP ||
				(isPrisoner(encounter[e].name) != 0 && encounter[e].align == 1)
				){
				freeable = true;
			}
			else if ((!get_encounter_cantbluff_is_one(e) || isThereASiteAlarm()) && !(encounter[e].align == 1 && isThereASiteAlarm() && enemy)) { 
				talkers++; 
			}
			if (encounter[e].type == CREATURE_CORPORATE_CEO ||
				encounter[e].type == CREATURE_RADIOPERSONALITY ||
				encounter[e].type == CREATURE_NEWSANCHOR ||
				encounter[e].type == CREATURE_SCIENTIST_EMINENT ||
				encounter[e].type == CREATURE_JUDGE_CONSERVATIVE) {
				majorenemy++;
			}
		}
	}

	//If in combat, do a second check
	if (talkers&&isThereASiteAlarm() && enemy)
	{
		recounttalkers(talkers);
	}

	
	// Let the squad stop stressing out over the encounter if there are no enemies this round
	if (!enemy) encounter_timer = 0;
	eraseAlt();
	{
		if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
		{
			playSiegeMusic();
		}
		else
		{
			onSiteButNoSiege();
		}
	}
	//PRINT PARTY
	if (activesquadAlive() == 0)party_status = -1;
	printparty();
	//PRINT SITE INSTRUCTIONS
	if (activesquadAlive() > 0)
	{
		partyIsAliveOnSite(enemy,
			talkers,
			freeable);
	}
	else
	{
		partyIsDeadOnSite();
		int c = getkeyAlt();
		if (c == 'c' && !endcheck()) {
			set_sitestory_type();
			mode = GAMEMODE_BASE;
			showcarprefs = 0;
			return false;
		}
		else
		{
			return true;
		}
	}
	checkForHostageScream(hostcheck);
	// check if we fought the previous loop; if so, add a blank gamelog line
	addNewLineIfFoughtThisRound();

	int c;

	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special == SPECIAL_CLUB_BOUNCER)
	{
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_PERMANENT)
		{
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special = SPECIAL_NONE;
			c = getkeyAlt();
		}
		else {
			c = 's';
		}
	}
	else c = getkeyAlt();

	if (activesquadAlive() > 0) {
		int olocx = loc_coord.locx, olocy = loc_coord.locy, olocz = loc_coord.locz;
		bool canMove = canactivesquadmove(c, enemy);
		switch (c) {
		case 'r':
			pressedKeyR(freeable, enemy);
			break;
		case 'o':
			if (activesquadSize() > 1) {
				orderparty(); 
			}
			break;
		default:
			partyPerformsAction(c, canMove, enemy, talkers, encounter_timer);
			break;
		}

		if (loc_coord.locx != olocx || loc_coord.locy != olocy || loc_coord.locz != olocz || c == 's') {

			int cbase = getactivesquadBase();
			//NEED TO GO BACK TO OLD LOCATION IN CASE COMBAT
			//REFRESHES THE SCREEN
			long nlocx = loc_coord.locx, nlocy = loc_coord.locy, nlocz = loc_coord.locz;
			loc_coord.locx = olocx, loc_coord.locy = olocy, loc_coord.locz = olocz;
			if (enemy) {
				enemyAttemptsFreeShots(encounter_timer);
			}
			creatureadvance();
			encounter_timer++;
			if (activesquadAlive()) {
				//AFTER DEATH CHECK CAN MOVE BACK TO NEW LOCATION
				loc_coord.locx = nlocx, loc_coord.locy = nlocy, loc_coord.locz = nlocz;
				//CHECK FOR EXIT
				if ((levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_EXIT) ||
					(cbase == getCurrentSite() && !LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) &&
						bail_on_base))
				{
					bailOnBase();
					resetSiteAlarm();
					mode = GAMEMODE_BASE;
					return false;
				}
				if (moveOrWaitThenCheckForExit(olocx, olocy, olocz, c, encsize, hostcheck)) {
					//RESET MODE
					mode = GAMEMODE_BASE;
					return false;
				}
			}
		}
	}
	return true;
}
void mode_site() {

	if (isThereNoActivesquad())return;
	reloadparty();
	showcarprefs = -1;
	char bail_on_base = shouldWeBailOnBase();
	knowmap();
	char hostcheck = 0;
	int encounter_timer = 0;

	while (increment_mode_site(bail_on_base, hostcheck, encounter_timer))
	{
		;
	}
}
void placeLootForSiege(const int lootnum) {

	int lx, ly, lz;

	for (int l = 0; l < ((lootnum <= 10) ? lootnum : 10); l++)
	{
		do lx = LCSrandom(MAPX), ly = LCSrandom(MAPY), lz = 0;
		while (levelmap[lx][ly][lz].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT));
		levelmap[lx][ly][lz].flag |= SITEBLOCK_LOOT;
	}
}
void placeTrapsForSiege() {

	int lx, ly, lz;

	int trapnum = 30;
	for (int t = 0; t < trapnum; t++)
	{
		do lx = LCSrandom(MAPX), ly = LCSrandom(MAPY), lz = 0;
		while (levelmap[lx][ly][lz].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT | SITEBLOCK_LOOT));
		levelmap[lx][ly][lz].siegeflag |= SIEGEFLAG_TRAP;
	}
}
void placeUnitsForSiege() {

	int lx, ly, lz;

	int unitnum = 6;
	int count = 50000;
	for (int t = 0; t < unitnum; t++)
	{
		do
		{
			lx = LCSrandom(11) + (MAPX / 2) - 5;
			ly = LCSrandom(8);
			lz = 0;
			count--;
			if (count == 0) break;
		} while ((levelmap[lx][ly][lz].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT)) ||
			(levelmap[lx][ly][lz].siegeflag&(SIEGEFLAG_UNIT | SIEGEFLAG_HEAVYUNIT | SIEGEFLAG_TRAP)));
		levelmap[lx][ly][lz].siegeflag |= SIEGEFLAG_UNIT;
	}
}
void mode_site(const short loc)
{
	setCurrentSite(loc);

	resetSiteAlarm();
	resetSiteGlobals();
	LocationsPool::getInstance().initSite(loc);
	set_site_story_as_last_news_story();
	mode = GAMEMODE_SITE;
	if (!LocationsPool::getInstance().isThereASiegeHere(loc))
	{
		music.play(MUSIC_SITEMODE);
		resetCCSSiegeGlobals();
		//Low profile site action?
		if (isActiveSquadAnonymous())
			setSiteStoryClaimedZero();
		//Start at entrance to map
		loc_coord.locx = MAPX >> 1;
		loc_coord.locy = 1;
		loc_coord.locz = 0;
		// Second floor start of White House
		if (LocationsPool::getInstance().getLocationType(loc) == SITE_GOVERNMENT_WHITE_HOUSE && levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_BLOCK)
			loc_coord.locz++;
		//check for sleeper infiltration or map knowledge
		if (CreaturePool::getInstance().doesAnyoneLiveHere(loc) || LocationsPool::getInstance().isLocationMapped(loc))
		{
			//make entire site known
			for (int x = 0; x < MAPX; x++)
				for (int y = 0; y < MAPY; y++)
					for (int z = 0; z < MAPZ; z++)
						levelmap[x][y][z].flag |= SITEBLOCK_KNOWN;
		}
	}
	else
	{
		music.play(MUSIC_DEFENSE);
		setSiteAlarmOne();
		LocationsPool::getInstance().turnOffSiege(loc);
		//PLACE YOU
		//int maxy=0;
		for (int x = 0; x < MAPX; x++)
			for (int y = 0; y < MAPY; y++)
			{
				for (int z = 0; z < MAPZ; z++)
				{
					if (!(LocationsPool::getInstance().lightsOff(loc)))levelmap[x][y][z].flag |= SITEBLOCK_KNOWN;
					levelmap[x][y][z].flag &= ~SITEBLOCK_LOCKED;
					levelmap[x][y][z].flag &= ~SITEBLOCK_LOOT;
				}
				//if(!(levelmap[x][y][0].flag & (SITEBLOCK_BLOCK|SITEBLOCK_DOOR)))maxy=y;
			}
		//Cops have tanks; firemen have fire.
		if (LocationsPool::getInstance().getSiegeType(loc) == SIEGE_FIREMEN)
		{
			int firesstarted = 0, firex, firey;
			do
			{
				firex = LCSrandom(MAPX), firey = LCSrandom(MAPY);
				firesstarted++;
				levelmap[firex][firey][0].flag |= SITEBLOCK_FIRE_START;
			} while (!(levelmap[firex][firey][0].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT)) &&
				firesstarted < 4);
		}
		do
		{
			// Some bugs with degenerate spawn outside the map are occurring
			// Unknown why, but hard-coding limits to spawn location should help
			//loc_coord.locx=LCSrandom(MAPX);
			//loc_coord.locy=maxy-LCSrandom(3);
			loc_coord.locx = MAPX / 2 + LCSrandom(25) - 12;
			loc_coord.locy = 15 - LCSrandom(3);
			//if(loc_coord.locy<3) loc_coord.locy=3;
			loc_coord.locz = 0;
		} while (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR |
			SITEBLOCK_FIRE_START | SITEBLOCK_FIRE_PEAK | SITEBLOCK_FIRE_END));
		//PLACE LOOT
		placeLootForSiege(LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, loc));
		//PLACE TRAPS
		if (LocationsPool::getInstance().hasTraps(loc))
		{
			placeTrapsForSiege();
		}
		//PLACE UNITS
		placeUnitsForSiege();
		if (!(LocationsPool::getInstance().get_specific_integer(INT_DOWEHAVETANKTRAPS,loc)) &&
			LocationsPool::getInstance().getSiegeType(loc) == SIEGE_POLICE &&
			LocationsPool::getInstance().getSiegeEscalationState(loc) >= 2)
		{
			levelmap[MAPX / 2][1][0].siegeflag |= SIEGEFLAG_HEAVYUNIT;
			LocationsPool::getInstance().spawnATank(loc, 1);
		}
	}
	mode_site();
}
/* prints the names of creatures you see in car chases */
void printchaseencounter()
{
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	printClearChaseScreen();
	if (len(chaseseq.enemycar))
	{
		int passenger_number[4] = { 0,0,0,0 };
		for (int v = 0; v < len(chaseseq.enemycar); v++)
		{
			printEnemyCar(chaseseq.enemycar[v]->fullname(true), v);
		}
		for (int e = 0; e < ENCMAX; e++) {
			if (encounter[e].exists) {
				for (int v = 0; v < len(chaseseq.enemycar); v++) {
					if (chaseseq.enemycar[v]->id() == getEncounterCarID(e))
					{
						printEnemyCarPassenger(encounter[e].name, v, passenger_number[v], getEncounterIsDriver(e));
						passenger_number[v]++;
					}
				}
			}
		}
	}
	else { 
		printencounter();
	}
}