
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

#include "../includes07.h"
#include "../constStringtalk.h"
/* bluff, date, issues */
void talk(DeprecatedCreature &a, const int t)
{
	DeprecatedCreature &tk = encounter[t];
	// TALKING TO DOGS
	if (tk.type == CREATURE_GUARDDOG && tk.align != ALIGN_LIBERAL)
	{
		 heyMisterDog(tk);
	}else
	// TALKING TO MONSTERS
	if (tk.type == CREATURE_GENETIC && tk.align != ALIGN_LIBERAL)
	{
		 heyMisterMonster(tk);
	}else
	// BLUFFING
	if ((isThereASiteAlarm() || LocationsPool::getInstance().isThereASiegeHere(getCurrentSite())) && tk.enemy())
	{
		 talkInCombat(a, tk);
	}
	else {
		 talkToGeneric(a, tk);
	}
}
char talkToBankTeller(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	const bool is_naked = a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL;
	printCommonStatement(is_naked ? eprintOptionsWithinBankWhileNaked : eprintOptionsWithinBank);
	int c = pressSpecificKey('a', 'b', 'c');
	switch (c)
	{
	case 'a':
		printCommonXeDoesStatement(eprintIRobTheBank,a.getNameAndAlignment().name);
		pressAnyKey();
		if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()))
		{
			printCommonStatement(eprintTellerAlertsCops);

			pressAnyKey();
			setSiteAlarmOne();
			criminalize(a, LAWFLAG_BANKROBBERY);
			sitestory->crime.push_back(CRIME_BANKTELLERROBBERY);
			sitecrime += 30;
			make_creature_without_encounter_array(0, CREATURE_MERC);
			make_creature_without_encounter_array(1, CREATURE_MERC);
			make_creature_without_encounter_array(2, CREATURE_MERC);
			make_creature_without_encounter_array(3, CREATURE_MERC);
		}
		else
		{
			printCommonStatement(eprintTellerComplies);
			pressAnyKey();
			criminalize(a, LAWFLAG_BANKROBBERY);
			sitestory->crime.push_back(CRIME_BANKTELLERROBBERY);
			sitecrime += 30;
			sitealarmtimer = 0;
			giveActiveSquadThisLoot(new Money(5000));
		}
		tk.make_cantbluff_one();
		return 1;
	case 'b':
	{
		clearcommandarea(); clearmessagearea(); clearmaparea();
		DeprecatedCreature *armed_liberal = NULL;
		for (int i = 0; i < 6; i++)
		{
			if (activesquad->squad[i] &&
				activesquad->squad[i]->get_weapon().get_specific_bool(BOOL_THREATENING_))
			{
				armed_liberal = activesquad->squad[i];
				break;
			}
		}
		if (armed_liberal)
		{
			printBrandishWeapon(armed_liberal->getNameAndAlignment().name, armed_liberal->get_weapon().get_shortname(0));
			pressAnyKey();
			clearmessagearea();
		}

		printCommonXeDoesStatement(eprintDemandVaultBeOpened,a.getNameAndAlignment().name);

		pressAnyKey();
		const int roll = a.skill_roll(SKILL_PERSUASION);
		int difficulty = DIFFICULTY_VERYEASY;
		if (armed_liberal == NULL)
			difficulty += 12;
		if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()))
			difficulty += 12;
		if (roll < difficulty)
		{
			printCommonStatement(eprintGuardsCloseIn);

			pressAnyKey();
			setSiteAlarmOne();
			sitealienate = 2;
			criminalizeparty(LAWFLAG_BANKROBBERY);
			sitestory->crime.push_back(CRIME_BANKSTICKUP);
			sitecrime += 50;
			CreatureTypes guard = CREATURE_SECURITYGUARD;
			if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite())) guard = CREATURE_MERC;
			make_creature_without_encounter_array(0, guard);
			make_creature_without_encounter_array(1, guard);
			make_creature_without_encounter_array(2, guard);
			make_creature_without_encounter_array(3, guard);
			make_creature_without_encounter_array(4, guard);
			make_creature_without_encounter_array(5, guard);
		}
		else
		{
			printCommonStatement(eprintBankerCooperates);

			pressAnyKey();

			printCommonStatement(eprintTheVaultIsOpen);

			pressAnyKey();

			criminalizeparty(LAWFLAG_BANKROBBERY);
			sitestory->crime.push_back(CRIME_BANKSTICKUP);
			sitecrime += 50;
			setSiteAlarmOne();
			sitealienate = 2;
			for (int x = 0; x < MAPX; x++)
				for (int y = 0; y < MAPY; y++)
					for (int z = 0; z < MAPZ; z++)
					{
						levelmap[x][y][z].flag &= ~SITEBLOCK_LOCKED;
						if (levelmap[x][y][z].flag & SITEBLOCK_METAL)
							levelmap[x][y][z].flag &= ~SITEBLOCK_DOOR;
						if (levelmap[x][y][z].special == SPECIAL_BANK_VAULT)
							levelmap[x][y][z].special = SPECIAL_NONE;
					}
			setEncounterZeroExistsFalse();
		}
	}
	default:
	case 'c':
		return 0;
	}
}


char talkToGeneric(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	printCommonXeDoesStatement(eprintTalkToHeader,a.getNameAndAlignment().name);
	printTalkToMiddle(tk.align, tk.getNameAndAlignment().name, get_age_string(tk.getCreatureBio(), tk.animalgloss));


	const bool is_naked = a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL;

	printTalkToFooter(is_naked, tk.can_date(a.getCreatureBio().age, a.animalgloss));

	if (tk.type == CREATURE_LANDLORD && LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == -1)
	{
		printCommonStatement(is_naked ? eprintTalkToPotentialLandlordWhileNaked : eprintTalkToPotentialLandlord);
	}
	else if (tk.type == CREATURE_LANDLORD && LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) > 0)
	{
		printCommonStatement(is_naked ? eprintTalkToLandlordWhileNaked : eprintTalkToLandlord);

	}
	else if (tk.type == CREATURE_GANGMEMBER || tk.type == CREATURE_MERC)
	{
		printCommonStatement(is_naked ? eprintTalkToGangMemberOrMercWhileNaked : eprintTalkToGangMemberOrMerc);

	}
	else if (tk.type == CREATURE_BANK_TELLER)
	{
		printCommonStatement(is_naked ? eprintTalkToBankTellerWhileNaked : eprintTalkToBankTeller);

	}
	while (true)
	{
		const int c = getkeyAlt();
		switch (c)
		{
		case 'a':
			wannaHearSomethingDisturbing(a, tk);
			return 1;
		case 'b':
			if (!tk.can_date(a.getCreatureBio().age, a.animalgloss)) break;
			doYouComeHereOften(a, tk);
			return 1;
		case 'c':
			return 0;
		case 'd':
			if (tk.type == CREATURE_LANDLORD && LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == -1)
			{
				heyIWantToRentARoom(a, tk);
				return 1;
			}
			else if (tk.type == CREATURE_LANDLORD && LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) > 0)
			{
				heyIWantToCancelMyRoom(a, tk);
				return 1;
			}
			else if (tk.type == CREATURE_GANGMEMBER || tk.type == CREATURE_MERC)
			{
				heyINeedAGun(a, tk);
				return 1;
			}
			else if (tk.type == CREATURE_BANK_TELLER)
			{
				return talkToBankTeller(a, tk);
			}
			break;
		}
	}
}

void heyIWantToCancelMyRoom(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	printCommonXeDoesStatement(eprintIWantToCancelRent,a.getNameAndAlignment().name);

	pressAnyKey();
	const bool is_naked = a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL;
	if (is_naked)
	{
		printCommonXeDoesStatement(eprintPutSomeDamnClothesOn,tk.getNameAndAlignment().name);
		pressAnyKey();
	}else{
		printCommonXeDoesStatement(eprintClearOutYourRoom, tk.getNameAndAlignment().name);

		pressAnyKey();

		printCommonStatement(eprintYourPossessionsAreRelocated);

		pressAnyKey();

		moveEverythingAwayFromSite(getCurrentSite());
	}
}

/* common - assigns a new base to all members of a squad */
void heyIWantToRentARoom(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	printCommonXeDoesStatement(eprintIWantToRent,a.getNameAndAlignment().name);
	pressAnyKey();
	const bool is_naked = a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL;
	if (is_naked)
	{
		printCommonXeDoesStatement(eprintPutSomeDamnClothesOn,tk.getNameAndAlignment().name);
		pressAnyKey();
		return;
	}
	int rent;
	switch (LocationsPool::getInstance().getLocationType(getCurrentSite()))
	{
	default:rent = 200; break;
	case SITE_RESIDENTIAL_APARTMENT:rent = 650; break;
	case SITE_RESIDENTIAL_APARTMENT_UPSCALE:rent = 1500; break;
	}

	printINeedThisMuchRent(tk.getNameAndAlignment().name, rent);

	pressAnyKey();
	clearcommandarea(); clearmessagearea(); clearmaparea();

	while (true)
	{
		int c = 'a';
		printCommonStatement(ledger.get_funds() < rent ? eprintRentingOptionsCannotAfford : eprintRentingOptions);
		c = getkeyAlt();
		switch (c)
		{
		case 'a': // Accept rent deal
			if (ledger.get_funds() < rent) break;
			printCommonXeDoesStatement(eprintAcceptRentHeader,a.getNameAndAlignment().name);

			pressAnyKey();

			printCommonXeDoesStatement(eprintAcceptRentFooter,tk.getNameAndAlignment().name);

			pressAnyKey();

			ledger.subtract_funds(rent, EXPENSE_RENT);
			locationIsNowRented(getCurrentSite(), rent);
			basesquad(activesquad, getCurrentSite());
			return;
		case 'b': // Refuse rent deal
			printCommonXeDoesStatement(eprintRefuseRentDeal,a.getNameAndAlignment().name);
			pressAnyKey();
			printCommonXeDoesStatement(eprintNotMyProblem,tk.getNameAndAlignment().name);
			pressAnyKey();
			return;
		case 'c': // Threaten landlord
			clearcommandarea(); clearmessagearea(); clearmaparea();
			DeprecatedCreature *armed_liberal = NULL;
			for (int i = 0; i < 6; i++)
			{
				if (activesquad->squad[i] &&
					activesquad->squad[i]->get_weapon().get_specific_bool(BOOL_THREATENING_))
				{
					armed_liberal = activesquad->squad[i];
					break;
				}
			}
			if (armed_liberal)
			{

				printThreatensWithAGun(armed_liberal->getNameAndAlignment().name, armed_liberal->get_weapon().get_shortname(0));
				pressAnyKey();
				clearmessagearea();
			}
			printCommonXeDoesStatement(eprintGiveMeTheLCSPrice,a.getNameAndAlignment().name);
			pressAnyKey();
			const int roll = a.skill_roll(SKILL_PERSUASION);
			int difficulty = DIFFICULTY_FORMIDABLE;
			if (!newscherrybusted)
				difficulty += 6;
			if (armed_liberal == NULL)
				difficulty += 6;
			if (roll < difficulty - 1)
			{

				printCommonXeDoesStatement(eprintIWantYouToLeave,tk.getNameAndAlignment().name);
				pressAnyKey();
				tk.make_cantbluff_one();
				return;
			}
			else
			{
				printCommonXeDoesStatement(eprintJesusItsYours,tk.getNameAndAlignment().name);
				pressAnyKey();
				int rent;
				// Either he calls the cops...
				if (roll < difficulty)
				{
					for (int i = 0; i < 6; i++)
						if (activesquad->squad[i])
							criminalize(*(activesquad->squad[i]), LAWFLAG_EXTORTION);
					LocationsPool::getInstance().setSiegetimeuntillocated(getCurrentSite(), 2);
					rent = 10000000; // Yeah he's kicking you out next month
				}
				// ...or it's yours for free
				else rent = 0;
				locationIsNowRented(getCurrentSite(), rent);
				basesquad(activesquad, getCurrentSite());
				return;
			}
		}
	}
}

void heyINeedAGun(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	printCommonXeDoesStatement(eprintINeedAGun,a.getNameAndAlignment().name);
	pressAnyKey();
	const bool is_naked = a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL;
	if (is_naked)
	{
		printCommonXeDoesStatement(eprintIDontSellToNaked,tk.getNameAndAlignment().name);
		pressAnyKey();
		return;
	}
	// IsaacG Migrate Strings
	if (a.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM ||
		a.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR ||
		a.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR ||
		(lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2 &&
			a.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM))
	{
		printCommonXeDoesStatement(eprintIDontSellToCops,tk.getNameAndAlignment().name);
		pressAnyKey();
		return;
	}
	if (isThereASiteAlarm())
	{
		printCommonXeDoesStatement(eprintWaitUntilItCoolsDown,tk.getNameAndAlignment().name);
		pressAnyKey();
		return;
	}
	switch (LocationsPool::getInstance().getLocationType(getCurrentSite()))
	{
	case SITE_OUTDOOR_BUNKER:
	case SITE_BUSINESS_CRACKHOUSE:
	case SITE_BUSINESS_BARANDGRILL:
	case SITE_BUSINESS_ARMSDEALER:
	case SITE_RESIDENTIAL_TENEMENT:
	case SITE_RESIDENTIAL_BOMBSHELTER:
	case SITE_RESIDENTIAL_SHELTER:
		printCommonXeDoesStatement(eprintLetMeSellYouAGun,tk.getNameAndAlignment().name);
		pressAnyKey();
		armsdealer(getCurrentSite());
		return;
	default:
		printCommonXeDoesStatement(eprintNotHereDummy,tk.getNameAndAlignment().name);
		pressAnyKey();
		return;
	}
}

void wannaHearSomethingDisturbing(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	bool neverinterested = tk.wontdateortalk();
	if (neverinterested)
	{
		//todo print custom message based on alignment
		printWontTalk(tk.align);
		pressAnyKey();
		return;
	}
	printCommonXeDoesStatement(eprintWannaHearSomething,a.getNameAndAlignment().name);
	pressAnyKey();
	
	bool interested = tk.talkreceptive();
	if (!interested && a.skill_check(SKILL_PERSUASION, DIFFICULTY_AVERAGE) && !neverinterested)
	{
		interested = true;
	}
	if ((tk.animalgloss == ANIMALGLOSS_ANIMAL && tk.align != ALIGN_LIBERAL) ||
		tk.animalgloss == ANIMALGLOSS_TANK)
	{
		printAnimalDoesntUnderstand(tk.getNameAndAlignment().name, tk.type);
		pressAnyKey();
	}
	else if (!isPrisoner(tk.getNameAndAlignment().name) && interested)
	{
		printCommonXeDoesStatement(eprintSaysWhat,tk.getNameAndAlignment().name);
		pressAnyKey();
		talkAboutIssues(a, tk);
	}
	else
	{
		printTurnsAway(tk.getNameAndAlignment().name, tk.align);
		pressAnyKey();
	}
}

void doYouComeHereOften(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	vector<string> selected_flirt;
	bool neverinterested = tk.wontdateortalk();
	if (neverinterested)
	{
		//todo print message based on alignment
		printWontDate(tk.align);
		pressAnyKey();
		return;
	}
	if (lawList[LAW_FREESPEECH] == -2)
	{
		selected_flirt = pickrandom(no_free_speech_flirt);
	}
	else
	{
		selected_flirt = pickrandom(pickupLines);
	}
	printPickupLine(a.getNameAndAlignment().name, selected_flirt);
	const bool extraline = (selected_flirt[1] != "" ? 1 : 0);
	pressAnyKey();
	bool succeeded = false;
	int difficulty = DIFFICULTY_HARD;
	if (tk.type == CREATURE_CORPORATE_CEO)
		difficulty = DIFFICULTY_HEROIC;
	const bool is_naked = a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL;
	if (is_naked) difficulty -= 4;
	if (a.skill_check(SKILL_SEDUCTION, difficulty))
		succeeded = true;
	if ((tk.animalgloss == ANIMALGLOSS_ANIMAL && lawList[LAW_ANIMALRESEARCH] != 2 && a.animalgloss != ANIMALGLOSS_ANIMAL) ||
		tk.animalgloss == ANIMALGLOSS_TANK)
	{
		switch (tk.type)
		{
		case CREATURE_GUARDDOG:
			tk.align = ALIGN_CONSERVATIVE;
			tk.make_cantbluff_one();
			break;
		case CREATURE_GENETIC:
			tk.align = ALIGN_CONSERVATIVE;
			tk.make_cantbluff_one();
			break;
		}
		printNonHumanRejection(tk.getNameAndAlignment().name, tk.type, extraline);
		pressAnyKey();
		return;
	}
	a.train(SKILL_SEDUCTION, LCSrandom(5) + 2);
	if ((a.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM // Police property on armor? -XML
		|| a.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR
		|| a.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR
		|| (lawList[LAW_POLICEBEHAVIOR] == ALIGN_ARCHCONSERVATIVE && lawList[LAW_DEATHPENALTY] == ALIGN_ARCHCONSERVATIVE
			&& a.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM))
		&& tk.type == CREATURE_PROSTITUTE)
	{
		printRejectPolicePickupLine(tk.getNameAndAlignment().name, extraline);
		pressAnyKey();
		tk.make_cantbluff_one();
	}
	else if (succeeded)
	{
		printAcceptsPickupLine(a.getNameAndAlignment().name, tk.getNameAndAlignment().name, selected_flirt);
		if (isPrisoner(tk.getNameAndAlignment().name))
		{
			criminalize(tk, LAWFLAG_ESCAPED);
		}
		pressAnyKey();
		newDate(a, tk);
	}
	else
	{
		printRejectsPickupLine(tk.getNameAndAlignment().name, tk.type, a.gender_liberal, selected_flirt);
		pressAnyKey();
		tk.make_cantbluff_one();
	}
}

void talkAboutIssues(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	const int lw = LCSrandom(LAWNUM); // pick a random law to talk about
	bool succeeded = false;
	bool you_are_stupid = false;
	bool issue_too_liberal = false;
	if (!(a.attribute_check(ATTRIBUTE_INTELLIGENCE, DIFFICULTY_EASY)))
		you_are_stupid = true;
	else if (lawList[lw] == ALIGN_ELITELIBERAL && newscherrybusted)
		issue_too_liberal = true;

	printTalkAboutIssuesHeader(a.getNameAndAlignment().name);

	if (you_are_stupid)
	{
		printTalkAboutIssuesWhenStupid(lw);
	}
	else if (issue_too_liberal)
	{
		printTalkAboutIssuesTooLiberal(lw);
	}
	else
	{
		printTalkAboutIssuesNormal(lw, tk.animalgloss);
	}

	

	pressAnyKey();
	int difficulty = DIFFICULTY_VERYEASY;
	if (tk.align == ALIGN_CONSERVATIVE)
		difficulty += 7;
	if (!(tk.talkreceptive()))
		difficulty += 7;
	if (you_are_stupid)
		difficulty += 5;
	if (issue_too_liberal)
		difficulty += 5;
	const bool is_naked = a.is_naked() && a.animalgloss != ANIMALGLOSS_ANIMAL;
	if (is_naked)
		difficulty += 5;
	succeeded = a.skill_check(SKILL_PERSUASION, difficulty);
	const bool extraline = you_are_stupid || issue_too_liberal;
	const int special_case = LCSrandom(10);
	bool another_extraline = !special_case;
	// Prisoners never accept to join you, you must liberate them instead

	if (succeeded && !isPrisoner(tk.getNameAndAlignment().name))
	{
		bool unableToSpeak = tk.type == CREATURE_MUTANT && tk.get_attribute(ATTRIBUTE_INTELLIGENCE, true) < 3;
		if (unableToSpeak) {
			printUnableToSpeakAgree(tk.getNameAndAlignment().name, extraline);
		}
		else
		{
			printThatIsDisturbing(tk.getNameAndAlignment().name, extraline, special_case);
		}
		pressAnyKey();
		printAgreesToComeByLater(tk.getNameAndAlignment().name, extraline, another_extraline && !unableToSpeak);
		pressAnyKey();
		DeprecatedCreature* newcr = new DeprecatedCreature;
		*newcr = tk;
		newcr->namecreature();
		newRecruit(newcr, a.id);
		delenc(tk);
	}
	else
	{
		if (tk.type == CREATURE_MUTANT &&
			tk.get_attribute(ATTRIBUTE_INTELLIGENCE, true) < 3)
		{
			printMutantTalkAboutIssues(tk.getNameAndAlignment().name, extraline);
		}
		else
		{
			const bool tkConservativeCounter = tk.align != ALIGN_LIBERAL && tk.attribute_check(ATTRIBUTE_WISDOM, DIFFICULTY_AVERAGE);
			if (tk.align == ALIGN_CONSERVATIVE && you_are_stupid)
			{
				printConservativeRespondsToStupid(tk.getNameAndAlignment().name, tk.type, extraline);
			}
			else if (tkConservativeCounter)
			{
				printConservativeCounter(tk.getNameAndAlignment().name, extraline, lw);
			}
			else
			{
				printRejectTalk(tk.getNameAndAlignment().name, extraline);
			}
		}
		printCommonStatement(eprintTurnsAway);
		pressAnyKey();
		tk.make_cantbluff_one();
	}
}




void pressKeyAInCombat(DeprecatedCreature &a) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	printCommonXeDoesStatement(eprintThreatenEnemy,a.getNameAndAlignment().name);
	pressAnyKey();
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].exists&&encounter[e].alive&&encounter[e].enemy)
		{
			const int attack = a.juice / 50 + attitude[VIEW_LIBERALCRIMESQUAD] / 10;
			const int defense = encounterWisdomRoll(e);
			if (attack > defense)
			{
				if (encounter[e].type == CREATURE_COP ||
					encounter[e].type == CREATURE_GANGUNIT ||
					encounter[e].type == CREATURE_SWAT ||
					encounter[e].type == CREATURE_DEATHSQUAD ||
					encounter[e].type == CREATURE_SOLDIER ||
					encounter[e].type == CREATURE_HARDENED_VETERAN ||
					encounter[e].type == CREATURE_CCS_ARCHCONSERVATIVE ||
					encounter[e].type == CREATURE_AGENT ||
					encounter[e].type == CREATURE_SECRET_SERVICE)
				{
					if (LCSrandom(3)) continue;
				}
				printCommonXeDoesStatement(eprintAnotherOneBacksOff,encounter[e].name);
				delenc(e, 0);
				addjuice(a, 2, 200); // Instant juice!
				pressAnyKey();
			}
		}
	}
}


void pressedKeyAWithHostage(DeprecatedCreature &a, const int hostages, const int e) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	DeprecatedCreature* executer = 0;
	if (a.is_holding_body())
		executer = &a;
	else for (int i = 0; i < 6; i++)
	{
		if (activesquad->squad[i] &&
			activesquad->squad[i]->is_holding_body() &&
			activesquad->squad[i]->is_prisoner_alive() &&
			activesquad->squad[i]->is_prisoner_enemy())
		{
			executer = activesquad->squad[i];
			break;
		}
	}
	
	if (executer->get_weapon().is_ranged()
		&& executer->get_weapon().get_ammoamount() > 0)
	{
		printCommonStatement(eprintExecutionGunshot);
		executer->get_weapon().decrease_ammo(1); //What if it doesn't use ammo? -XML
	}
	else
	{
		printCommonStatement(eprintExecutionBareHands);
	}
	
	pressAnyKey();
	printDiscardsBody(executer->getNameAndAlignment().name, executer->get_prisoner_name());
	addjuice(*executer, -5, -50); // DE-juice for this shit
	sitecrime += 10;
	sitestory->crime.push_back(CRIME_KILLEDSOMEBODY);
	criminalize(*executer, LAWFLAG_MURDER);
	if (executer->get_prisoner_type() == CREATURE_CORPORATE_CEO ||
		executer->get_prisoner_type() == CREATURE_RADIOPERSONALITY ||
		executer->get_prisoner_type() == CREATURE_NEWSANCHOR ||
		executer->get_prisoner_type() == CREATURE_SCIENTIST_EMINENT ||
		executer->get_prisoner_type() == CREATURE_JUDGE_CONSERVATIVE)sitecrime += 30;
	executer->make_prisoner_ground_loot();
	pressAnyKey();
	executer->delete_and_nullify_prisoner();
	if (hostages > 1 && LCSrandom(2))
	{
		printCommonXeDoesStatement(eprintEnemyWatchesHostageDeath,encounter[e].name);
		for (int i = ENCMAX - 1; i >= 0; i--)
		{
			if (encounter[i].exists && encounter[i].enemy && encounter[i].alive)
			{
				delenc(i, 0);
			}
		}
		pressAnyKey();
	}
}
void pressedKeyBWithHostage(DeprecatedCreature &a, const int hostages, const int e) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	printLetUsGoAndTheyGoFree(a.getNameAndAlignment().name, hostages);
	pressAnyKey();
	if (((encounter[e].type == CREATURE_DEATHSQUAD ||
		encounter[e].type == CREATURE_AGENT ||
		encounter[e].type == CREATURE_MERC ||
		encounter[e].type == CREATURE_CCS_ARCHCONSERVATIVE ||
		encounter[e].type == CREATURE_GANGUNIT) &&
		LCSrandom(2)) && encounter[e].align == ALIGN_CONSERVATIVE)
	{
		printCommonXeDoesStatement(eprintEnemyAllowsHostagesToDie,encounter[e].name);
		pressAnyKey();
	}
	else
	{

		printCommonXeDoesStatement(eprintReleaseHostagesHeader,encounter[e].name);
		pressAnyKey();
		printReleaseHostagesFooter(hostages);
		juiceparty(15, 200); // Instant juice for successful hostage negotiation
		for (int i = ENCMAX - 1; i >= 0; i--) {
			if (encounter[i].exists&&encounter[i].enemy && encounter[i].alive)
			{
				delenc(i, 0);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			if (activesquad->squad[i] &&
				activesquad->squad[i]->is_holding_body() &&
				activesquad->squad[i]->is_prisoner_enemy())
			{
				activesquad->squad[i]->delete_and_nullify_prisoner();
			}
		}
		pressAnyKey();
	}
}

void pressKeyBInCombat(DeprecatedCreature &a, DeprecatedCreature &tk, const int hostages, const int weaponhostage) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	printCommonXeDoesStatement(eprintThreatenHostages,a.getNameAndAlignment().name);
	sitecrime += 5;
	criminalizeparty(LAWFLAG_KIDNAPPING);
	addjuice(a, -2, -10); // DE-juice for this shit
	pressAnyKey();
	if (weaponhostage)
	{
		bool noretreat = false;
		int e = 0;
		for (; e < ENCMAX; e++)
		{
			if (encounter[e].exists&&encounter[e].alive&&
				encounter[e].enemy && encounter[e].blood > 70)
			{
				if ((encounter[e].type == CREATURE_DEATHSQUAD ||
					encounter[e].type == CREATURE_SOLDIER ||
					encounter[e].type == CREATURE_HARDENED_VETERAN ||
					encounter[e].type == CREATURE_CCS_ARCHCONSERVATIVE ||
					encounter[e].type == CREATURE_AGENT ||
					encounter[e].type == CREATURE_MERC ||
					encounter[e].type == CREATURE_COP ||
					encounter[e].type == CREATURE_GANGUNIT ||
					encounter[e].type == CREATURE_SWAT ||
					encounter[e].type == CREATURE_SECRET_SERVICE) &&
					LCSrandom(5))
				{
					printHostageNegotiation(encounter[e].name, encounter[e].type, encounter[e].align, hostages);
					pressAnyKey();
					noretreat = true;
					break;
				}
			}
		}
		if (e == ENCMAX) { e--; }
		if (noretreat == false)
		{
			printCommonStatement(eprintPloyWorksEnemyBacksOff);
			for (int i = ENCMAX - 1; i >= 0; i--)
			{
				if (encounter[i].exists&&
					encounter[i].alive&&
					encounter[i].align <= -1)
				{
					delenc(i, 0);
				}
			}
			pressAnyKey();
		}
		else
		{
			printHowShouldWeRespond(a.getNameAndAlignment().name, hostages);
			char c = pressSpecificKey('a', 'b'); // TODO: something to happen if you press 'c'
			switch (c) {
			case 'a':
				pressedKeyAWithHostage(a, hostages, e);
				break;

			case 'b':
				pressedKeyBWithHostage(a, hostages, e);
				break;


			}
		}
	}
	else
	{
		printCommonXeDoesStatement(eprintEnemyIgnoresThreat,tk.getNameAndAlignment().name);
		pressAnyKey();
	}
}

void pressKeyCInCombat(DeprecatedCreature &a) {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();

	if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		printSiegeBluff(a.getNameAndAlignment().name, LocationsPool::getInstance().getSiegeType(getCurrentSite()));
		
	}
	else        //Special bluff messages for various uniforms
	{
		if (a.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM ||
			a.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR ||
			a.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR)
		{
			printCommonStatement(eprintPoliceBluff);
		}
		else if (a.get_armor().get_itemtypename() == tag_ARMOR_BUNKERGEAR)
		{
			printBunkerGearBluff(siteonfire);
		}
		else if (a.get_armor().get_itemtypename() == tag_ARMOR_LABCOAT)
			printCommonStatement(eprintLabCoatBluff);
		else if (a.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM)
			printCommonStatement(eprintDeathSquadBluff);
		else if (a.get_armor().get_itemtypename() == tag_ARMOR_MITHRIL)
		{
			printCommonXeDoesStatement(eprintEngraveElbereth,a.getNameAndAlignment().name);
		}
		else
		{
			printCommonXeDoesStatement(eprintITalkLikeAConservative,a.getNameAndAlignment().name);
		}

	}
	pressAnyKey();
	bool fooled = true;
	int e = 0;
	for (; e < ENCMAX; e++)
	{
		if (encounter[e].exists&&encounter[e].alive&&
			encounter[e].enemy)
		{
			const int roll = a.skill_roll(SKILL_DISGUISE);
			const int diff = getDifficultyBasedOnEncounterWisdom(e);
			fooled = roll >= diff;
			if (roll + 1 == diff && fieldskillrate == FIELDSKILLRATE_HARD)
				a.train(SKILL_DISGUISE, 20);
			if (!fooled) break;
		}
	}
	if (e == ENCMAX) { e--; }
	switch (fieldskillrate)
	{
	case FIELDSKILLRATE_FAST:
		a.train(SKILL_DISGUISE, 50); break;
	case FIELDSKILLRATE_CLASSIC:
		a.train(SKILL_DISGUISE, 20); break;
	case FIELDSKILLRATE_HARD:
		a.train(SKILL_DISGUISE, 0); break;
	}
	if (!fooled)
	{
		if (encounter[e].type == CREATURE_HICK)
		{
			printCommonXeDoesStatement(eprintWeWerentBornYesterday, encounter[e].name);
		}
		else
		{
			printXeIsNotFooled(encounter[e].name, lawList[LAW_FREESPEECH] == ALIGN_ARCHCONSERVATIVE);
		}
		pressAnyKey();
	}
	else
	{
		printCommonStatement(eprintTheEnemyIsFooled);
		pressAnyKey();
		for (int e = ENCMAX - 1; e >= 0; e--)
			if (encounter[e].exists&&encounter[e].alive&&encounter[e].enemy)
				delenc(e, 0);
	}
}
void pressKeyDInCombat() {
	printCommonStatement(eprintTheSquadIsArrested);
	pressAnyKey();
	int stolen = 0;
	// Police assess stolen goods in inventory
	for (int l = 0; l < len(activesquad->loot); l++)
		if (activesquad->loot[l]->whatIsThis() == THIS_IS_LOOT)
			stolen++;
	for (int i = 0; i < 6; i++)
	{
		if (activesquad->squad[i])
		{
			for (int j = 0; j < stolen; j++) {
				activesquad->squad[i]->criminalize_me(LAWFLAG_THEFT);
			}
			capturecreature(*activesquad->squad[i]);
		}
		activesquad->squad[i] = NULL;
	}
	LocationsPool::getInstance().isThereASiegeHere(getCurrentSite(), 0);
}
char haveActiveSquadTalk(const int sp, const int t) {
	DeprecatedCreature &tk = encounter[t];
	// TALKING TO DOGS
	if (tk.type == CREATURE_GUARDDOG && tk.align != ALIGN_LIBERAL)
	{
		heyMisterDog(tk);
		return 1;
	}
	else {
		// TALKING TO MONSTERS
		if (tk.type == CREATURE_GENETIC && tk.align != ALIGN_LIBERAL)
		{
			heyMisterMonster(tk);
			return 1;
		}
		else
			// BLUFFING
			if ((isThereASiteAlarm() || LocationsPool::getInstance().isThereASiegeHere(getCurrentSite())) && tk.enemy())
			{
				talkInCombat(*activesquad->squad[sp], tk);
				return 1;
			}
			else {
				return talkToGeneric(*activesquad->squad[sp], tk);
			}
	}

}
void talkInCombat(DeprecatedCreature &a, DeprecatedCreature &tk)
{
	printTalksToThem(a.name, tk.align, tk.getNameAndAlignment().name);
	int c = 0, hostages = 0, weaponhostage = 0;
	bool cop = 0;
	for (int i = 0; i < 6; i++)
	{
		if (activesquad->squad[i] &&
			activesquad->squad[i]->is_holding_body() &&
			activesquad->squad[i]->is_prisoner_alive() &&
			activesquad->squad[i]->is_prisoner_enemy())
		{
			hostages++;
			if (activesquad->squad[i]->get_weapon().get_specific_bool(BOOL_CAN_THREATEN_HOSTAGES_))
				weaponhostage++;
		}
	}
	if (tk.type == CREATURE_COP ||
		tk.type == CREATURE_GANGUNIT ||
		tk.type == CREATURE_DEATHSQUAD ||
		tk.type == CREATURE_SWAT ||
		tk.type == CREATURE_SECURITYGUARD ||
		tk.type == CREATURE_MERC ||
		tk.type == CREATURE_SOLDIER ||
		tk.type == CREATURE_MILITARYPOLICE ||
		tk.type == CREATURE_MILITARYOFFICER ||
		tk.type == CREATURE_SEAL)
	{
		cop = 1;
	}
	printTalkOptionsDuringCombat(hostages, tk.is_cantbluff_two(), cop);
	while (true)
	{
		c = getkeyAlt();
		if (c == 'a')break;
		if (c == 'b' && hostages)break;
		if (c == 'c' && !tk.is_cantbluff_two())break;
		if (c == 'd' && cop)break;
	}
	switch (c) {
	case 'a':
		// Intimidate
		pressKeyAInCombat(a);
		break;

	case 'b':
		// Threaten Hostages
		pressKeyBInCombat(a, tk, hostages, weaponhostage);
		break;

	case 'c':
		// Bluff
		pressKeyCInCombat(a);
		break;

	case 'd':
		// Surrender to authorities
		pressKeyDInCombat();
		break;

	}
}
int findMostHeartfulLiberal() {
	int bestp = 0;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] &&
			activesquad->squad[p]->get_attribute(ATTRIBUTE_HEART, true) >
			activesquad->squad[bestp]->get_attribute(ATTRIBUTE_HEART, true))
		{
			bestp = p;
		}
	}
	return bestp;
}

void heyMisterDog(DeprecatedCreature &tk)
{
	bool success = false;
	string pitch;
	string response;
	// Find most Heartful Liberal
	int bestp = findMostHeartfulLiberal();
	// Say something unbelievably hippie
	if (activesquad->squad[bestp]->get_attribute(ATTRIBUTE_HEART, true) >= 15)
	{
		success = true;
		vector<string> which_choice = pickrandom(lovingly_talk_to_dog);
		pitch = which_choice[0];
		response = which_choice[1];
	}
	else // or not
	{
		tk.make_cantbluff_one();
		vector<string> which_choice = pickrandom(normal_talk_to_dog);
		pitch = which_choice[0];
		response = which_choice[1];
	}

	printSpecialRecruitment(activesquad->squad[bestp]->getNameAndAlignment().name, tk.getNameAndAlignment().name, pitch, response);
	pressAnyKey();

	if (success) {
		liberalizeEncounterIfThisType(CREATURE_GUARDDOG);
	}
}
void heyMisterMonster(DeprecatedCreature &tk)
{
	bool success = false;
	string pitch;
	string response;
	// Find most Heartful Liberal
	int bestp = findMostHeartfulLiberal();
	// Say something diplomatic
	if (activesquad->squad[bestp]->get_attribute(ATTRIBUTE_HEART, true) >= 15)
	{
		success = true;
		vector<string> which_choice = pickrandom(lovingly_talk_to_mutant);
		pitch = which_choice[0];
		response = which_choice[1];
	}
	else // or not
	{
		tk.make_cantbluff_one();
		vector<string> which_choice = pickrandom(normal_talk_to_mutant);
		pitch = which_choice[0];
		response = which_choice[1];
	}

	printSpecialRecruitment(activesquad->squad[bestp]->getNameAndAlignment().name, tk.getNameAndAlignment().name, pitch, response);
	pressAnyKey();

	if (success) {
		liberalizeEncounterIfThisType(CREATURE_GENETIC);
	}
}

/* ensures that the creature's work location is appropriate to its type */
int verifyworklocation(const int type, const int worklocation)
{
	int okaysite[SITENUM];
	memset(okaysite, 0, SITENUM * sizeof(int));

	// TODO this can be extracted to a table
	if (type == CREATURE_CCS_ARCHCONSERVATIVE || type == CREATURE_CCS_MOLOTOV ||
		type == CREATURE_CCS_SNIPER || type == CREATURE_CCS_VIGILANTE) {

		if (ccs_kills == 2)okaysite[SITE_OUTDOOR_BUNKER] = 1;
		if (ccs_kills == 1)okaysite[SITE_RESIDENTIAL_BOMBSHELTER] = 1;
		if (ccs_kills == 0)okaysite[SITE_BUSINESS_BARANDGRILL] = 1;
	}
	else {
		if (okaySiteList.count(type)) {
			for (SiteTypes s : okaySiteList[type]) {
				okaysite[s] = 1;
			}
		}
		else {
			for (SiteTypes s : defaultSiteList) {
				okaysite[s] = 1;
			}
		}
	}
	int new_work_location = worklocation;
	char swap = 0;
	// TODO possible alwaysfalse conditional, investigate
	if (worklocation == -1) swap = 1;
	else if (!okaysite[(int)LocationsPool::getInstance().getLocationType((int)worklocation)]) swap = 1;
	if (swap)
	{
		//int city = location[location]->city;
		//PICK A TYPE OF WORK LOCATION
		//worklocation=choose_one(okaysite,SITENUM,0);
		//FIND ONE OF THESE
		vector<int> goodlist;
		//find_site_index_in_city(worklocation, location[location]->city);
		for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++)
			//if(location[l]->type==worklocation && (!multipleCityMode || location[l]->city == location))
			if (okaysite[(int)LocationsPool::getInstance().getLocationType(l)] &&
				(!multipleCityMode || LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,l)
					==
					LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,worklocation)))
				goodlist.push_back(l);
		// Sadler - This line sometimes causes a memory fault
		//               Only thing I can think of is if loop above didn't
		//               find any locations of type == to worklocation
		//               My hunch is that some locations, such as the 1st four
		//               are special and cannot be used here..
		//
		//   TODO There was a bug in the makecharacter() code where the
		//   SITE_OUTOFTOWN was not set properly. This was fixed but the bug here
		//   is still occurring, normally at the Latte Bar Downtown ;
		if (!len(goodlist)) new_work_location = 0;
		else new_work_location = pickrandom(goodlist);
	}
	return new_work_location;
}
