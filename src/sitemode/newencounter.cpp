
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

#include "../includes12.h"
#include "../constStringnewencounter.h"


/* rolls up a random creature type according to the passed weighting array */
int getrandomcreaturetype(int cr[CREATURENUM])
{
	int sum = 0;
	for (int c = 0; c < CREATURENUM; c++)sum += cr[c];
	if (sum > 0)
	{
		int roll = LCSrandom(sum);
		int sel = 0;
		while (roll >= 0) { roll -= cr[sel]; sel++; }
		return sel - 1;
	}
	else return -1;
}


void addBank(int creaturearray[CREATURENUM], const char sec) {
	if (mode == GAMEMODE_SITE && !(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED))
	{
		creaturearray[CREATURE_BANK_MANAGER] = 20;
		creaturearray[CREATURE_SCIENTIST_LABTECH] = 1;
		creaturearray[CREATURE_WORKER_JANITOR] = 1;
		creaturearray[CREATURE_WORKER_SECRETARY] = 1;
		creaturearray[CREATURE_TEENAGER] = 3;
		creaturearray[CREATURE_COP] += 1;
		creaturearray[CREATURE_LAWYER] = 1;
		creaturearray[CREATURE_SEWERWORKER] = 1;
		creaturearray[CREATURE_COLLEGESTUDENT] = 1;
		creaturearray[CREATURE_MUSICIAN] = 1;
		creaturearray[CREATURE_MATHEMATICIAN] = 1;
		creaturearray[CREATURE_TEACHER] = 1;
		creaturearray[CREATURE_PRIEST] = 1;
		creaturearray[CREATURE_ENGINEER] = 1;
		creaturearray[CREATURE_FASTFOODWORKER] = 1;
		creaturearray[CREATURE_BAKER] = 1;
		creaturearray[CREATURE_BARISTA] = 1;
		creaturearray[CREATURE_BARTENDER] = 1;
		creaturearray[CREATURE_TELEMARKETER] = 1;
		creaturearray[CREATURE_CARSALESMAN] = 1;
		creaturearray[CREATURE_OFFICEWORKER] = 1;
		creaturearray[CREATURE_FOOTBALLCOACH] = 1;
		creaturearray[CREATURE_MAILMAN] = 1;
		creaturearray[CREATURE_DOCTOR] = 1;
		creaturearray[CREATURE_PSYCHOLOGIST] += 1;
		creaturearray[CREATURE_NURSE] = 1;
		creaturearray[CREATURE_GARBAGEMAN] = 1;
		creaturearray[CREATURE_PLUMBER] = 1;
		creaturearray[CREATURE_CHEF] = 1;
		creaturearray[CREATURE_CONSTRUCTIONWORKER] = 1;
		creaturearray[CREATURE_AMATEURMAGICIAN] = 1;
		creaturearray[CREATURE_SOLDIER] = 1;
		creaturearray[CREATURE_VETERAN] = 2;
		creaturearray[CREATURE_HIPPIE] = 1;
		creaturearray[CREATURE_CRITIC_ART] = 1;
		creaturearray[CREATURE_CRITIC_MUSIC] = 1;
		creaturearray[CREATURE_AUTHOR] = 1;
		creaturearray[CREATURE_JOURNALIST] = 1;
		creaturearray[CREATURE_TAXIDRIVER] = 1;
		creaturearray[CREATURE_PROGRAMMER] = 1;
		creaturearray[CREATURE_RETIREE] = 1;
		creaturearray[CREATURE_PAINTER] = 1;
		creaturearray[CREATURE_SCULPTOR] = 1;
		creaturearray[CREATURE_DANCER] = 1;
		creaturearray[CREATURE_PHOTOGRAPHER] = 1;
		creaturearray[CREATURE_CAMERAMAN] = 1;
		creaturearray[CREATURE_HAIRSTYLIST] = 1;
		creaturearray[CREATURE_CLERK] = 1;
		creaturearray[CREATURE_THIEF] = 1;
		creaturearray[CREATURE_ACTOR] = 1;
		creaturearray[CREATURE_YOGAINSTRUCTOR] = 1;
		creaturearray[CREATURE_MARTIALARTIST] += 1;
		creaturearray[CREATURE_ATHLETE] = 1;
		creaturearray[CREATURE_FIREFIGHTER] += 1;
		creaturearray[CREATURE_LOCKSMITH] += 1;


		if (sec) creaturearray[CREATURE_MERC] = 100;
		else creaturearray[CREATURE_SECURITYGUARD] = 50;
		if (lawList[LAW_LABOR] < 2)creaturearray[CREATURE_WORKER_FACTORY_NONUNION] = 1;
		if (lawList[LAW_LABOR] >= 0)creaturearray[CREATURE_WORKER_FACTORY_UNION] = 1;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] += 1;
		if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] += 1;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] += 1;
		else creaturearray[CREATURE_PRISONGUARD] += 1;
	}
	else
	{
		creaturearray[CREATURE_BANK_MANAGER] = 200;
		creaturearray[CREATURE_THIEF] = 1;


		if (sec) creaturearray[CREATURE_MERC] = 2000;
		else creaturearray[CREATURE_SECURITYGUARD] = 1000;
	}
}
void addUpscaleApartment(int creaturearray[CREATURENUM], const char sec) {



	if (mode == GAMEMODE_SITE && !(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED))
	{
		if (sec)creaturearray[CREATURE_SECURITYGUARD] += 100;
		else creaturearray[CREATURE_SECURITYGUARD] += 10;
		if (sec)creaturearray[CREATURE_GUARDDOG] += 50;
	}
	else if (mode == GAMEMODE_SITE && sec)
	{
		//inside someone's room when security is high. Might meet a policeman.
		if (lawList[LAW_DEATHPENALTY] == -2 && lawList[LAW_POLICEBEHAVIOR] == -2)
			creaturearray[CREATURE_DEATHSQUAD] += 5;
		if (lawList[LAW_POLICEBEHAVIOR] <= -1)
			creaturearray[CREATURE_GANGUNIT] += 10;
		creaturearray[CREATURE_COP] += 15;
	}
}

void addPrison(int creaturearray[CREATURENUM], const char sec) {

	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
		creaturearray[CREATURE_PRISONER] = 8; // prisoners only in restricted areas
	if (sec)
	{
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] += 3;
		else creaturearray[CREATURE_PRISONGUARD] += 3;
	}
	else
	{
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] += 2;
		else creaturearray[CREATURE_PRISONGUARD] += 2;
	}
}

void addPoliceOrMilitary(int creaturearray[CREATURENUM]) {
	switch (sitetype)
	{
	case SITE_GOVERNMENT_ARMYBASE:
		creaturearray[CREATURE_SOLDIER] = 1000;
		creaturearray[CREATURE_MILITARYPOLICE] = 300;
		creaturearray[CREATURE_MILITARYOFFICER] = 150;
		creaturearray[CREATURE_SEAL] = 150;
		creaturearray[CREATURE_GUARDDOG] = 100;
		creaturearray[CREATURE_TANK] = 100;
		break;
	case SITE_GOVERNMENT_WHITE_HOUSE:
		creaturearray[CREATURE_SECRET_SERVICE] = 1000;
		creaturearray[CREATURE_MILITARYOFFICER] = 100;
		break;
	case SITE_GOVERNMENT_INTELLIGENCEHQ:
		creaturearray[CREATURE_AGENT] = 1000;
		creaturearray[CREATURE_MILITARYOFFICER] = 100;
		creaturearray[CREATURE_GUARDDOG] = 50;
		break;
	case SITE_CORPORATE_HEADQUARTERS:
	case SITE_CORPORATE_HOUSE:
		creaturearray[CREATURE_MERC] = 1000;
		break;
	case SITE_MEDIA_AMRADIO:
	case SITE_MEDIA_CABLENEWS:
		creaturearray[CREATURE_HICK] = 1000;
		break;
	case SITE_GOVERNMENT_POLICESTATION:
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] = 1000;
		else creaturearray[CREATURE_SWAT] = 1000;
		break;
	default:
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] = 1000;
		else if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] = 1000;
		else creaturearray[CREATURE_COP] = 1000;
		break;
	}
	if (siteonfire && lawList[LAW_FREESPEECH] != -2)creaturearray[CREATURE_FIREFIGHTER] = 1000;
}
void addCCS(int creaturearray[CREATURENUM]) {
	creaturearray[CREATURE_CCS_VIGILANTE] += 50;
	//creaturearray[CREATURE_CCS_ARCHCONSERVATIVE]+=endgamestate;
	creaturearray[CREATURE_PROSTITUTE] += 5;
	creaturearray[CREATURE_CRACKHEAD] += 5;
	creaturearray[CREATURE_PRIEST] += 5;
	creaturearray[CREATURE_RADIOPERSONALITY] += 1;

}
/* generates a new random encounter */
void prepareencounter(short type, char sec)
{
	int encslot = 0;
	emptyEncounter();
	int creaturearray[CREATURENUM];
	memset(creaturearray, 0, CREATURENUM * sizeof(int));
	if (postalarmtimer > 80)
	{
		addPoliceOrMilitary(creaturearray);
	}
	if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
	{
		addCCS(creaturearray);
		for (int n = 0; n < LCSrandom(6) + 1; n++)
		{
			make_creature_without_encounter_array(encslot, getrandomcreaturetype(creaturearray));
			conservatiseEncslot(encslot);
			encslot++;
		}
	}
	else
	{
		if (type != SITE_BUSINESS_BANK && type != SITE_GOVERNMENT_PRISON) {
			for (int i = 0; i < len(locationsSpawners[type]); i += 2) {
				creaturearray[locationsSpawners[type][i]] += locationsSpawners[type][i + 1];
			}
		}
		int encnum = 6;
		const int variableEncnum = mode == GAMEMODE_SITE && !(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED) ? 4 : 1;
		bool variableEncounter = false;
		switch (type) {
		case SITE_GOVERNMENT_PRISON:
		{
			addPrison(creaturearray, sec);
			break;
		}
		case SITE_BUSINESS_BANK:
		{
			addBank(creaturearray, sec);
			variableEncounter = true;
			break;
		}
		case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
		{
			addUpscaleApartment(creaturearray, sec);
			variableEncounter = true;
			break;
		}
		default:
			variableEncounter = populateEncounter(type, creaturearray, sec);
			break;
		}
		if (variableEncounter) {
			encnum = variableEncnum;

		}
		for (int n = 0; n < LCSrandom(encnum) + 1; n++)
		{
			make_creature_without_encounter_array(encslot, getrandomcreaturetype(creaturearray));
			encslot++;
		}
	}
}
/* generates a new siege encounter */
char addsiegeencounter(char type)
{
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int num;
	int freeslots = 0;
	for (int e = 0; e < ENCMAX; e++)
	{
		if (!encounter[e].exists)freeslots++;
	}
	switch (type)
	{
	case SIEGEFLAG_UNIT:
	case SIEGEFLAG_UNIT_DAMAGED:
	{
		if (freeslots < 6)return 0;
		num = LCSrandom(3) + 4;
		if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
		{
			switch (LocationsPool::getInstance().getSiegeType(getCurrentSite()))
			{
			case SIEGE_POLICE:
				if (LocationsPool::getInstance().getSiegeEscalationState(getCurrentSite()) == 0)
					fillEncounter(CREATURE_SWAT, num);
				else
				{
					if (LocationsPool::getInstance().getSiegeEscalationState(getCurrentSite()) < 3) fillEncounter(CREATURE_SOLDIER, num);
					else fillEncounter(CREATURE_SEAL, num);
				}
				break;
			case SIEGE_CIA:
				fillEncounter(CREATURE_AGENT, num);
				break;
			case SIEGE_HICKS:
				fillEncounter(CREATURE_HICK, num);
				break;
			case SIEGE_CORPORATE:
				fillEncounter(CREATURE_MERC, num);
				break;
			case SIEGE_CCS:
				for (int e = 0; e < ENCMAX && num > 0; e++) {
					if (!encounter[e].exists) {
						if (!LCSrandom(12))
							make_creature_without_encounter_array(e, CREATURE_CCS_ARCHCONSERVATIVE);
						else if (!LCSrandom(11))
							make_creature_without_encounter_array(e, CREATURE_CCS_MOLOTOV);
						else if (!LCSrandom(10))
							make_creature_without_encounter_array(e, CREATURE_CCS_SNIPER);
						else make_creature_without_encounter_array(e, CREATURE_CCS_VIGILANTE);
						num--;
					}
				}
				break;
			case SIEGE_FIREMEN:
				fillEncounter(CREATURE_FIREFIGHTER, num);
				break;
			}
		}
		else
		{
			switch (sitetype)
			{
			case SITE_GOVERNMENT_ARMYBASE:
				if (!encounter[0].exists && !LCSrandom(2)) {
					make_creature_without_encounter_array(0, CREATURE_TANK);
					num--;
				}
				fillEncounter(CREATURE_SOLDIER, num);
				break;
			case SITE_GOVERNMENT_INTELLIGENCEHQ:
				fillEncounter(CREATURE_AGENT, num);
				break;
			case SITE_CORPORATE_HEADQUARTERS:
			case SITE_CORPORATE_HOUSE:
				fillEncounter(CREATURE_MERC, num);
				break;
			case SITE_MEDIA_AMRADIO:
			case SITE_MEDIA_CABLENEWS:
				fillEncounter(CREATURE_HICK, num);
				break;
			case SITE_GOVERNMENT_POLICESTATION:
				if (lawList[LAW_DEATHPENALTY] == -2 &&
					lawList[LAW_POLICEBEHAVIOR] == -2)fillEncounter(CREATURE_DEATHSQUAD, num);
				else fillEncounter(CREATURE_SWAT, num);
				break;
			case SITE_BUSINESS_CRACKHOUSE:
				// TODO this causes all encountered creatures to become conservative, not just the gangmembers
				fillEncounter(CREATURE_GANGMEMBER, num);
				for (int e = 0; e < ENCMAX; e++) {
					if (encounter[e].exists)
						conservatise(e);
				}
				break;
			default:
				if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
				{
					for (int e = 0; e < ENCMAX && num > 0; e++) {
						if (!LCSrandom(11))
							make_creature_without_encounter_array(e, CREATURE_CCS_MOLOTOV);
						else if (!LCSrandom(10))
							make_creature_without_encounter_array(e, CREATURE_CCS_SNIPER);
						else make_creature_without_encounter_array(e, CREATURE_CCS_VIGILANTE);
						num--;
					}
				}
				else if (lawList[LAW_DEATHPENALTY] == -2 &&
					lawList[LAW_POLICEBEHAVIOR] == -2)fillEncounter(CREATURE_DEATHSQUAD, num);
				else fillEncounter(CREATURE_SWAT, num);
				break;
			}
		}
		// TODO this causes all encountered creatures to be damaged, not just the newly generated ones
		if (type == SIEGEFLAG_UNIT_DAMAGED)
			for (int e = 0; e < ENCMAX; e++) {
				if (encounter[e].exists)
					damage_creature(e);
			}
		break;
	}
	case SIEGEFLAG_HEAVYUNIT:
	{
		if (freeslots < 1)return 0;
		num = 1;
		fillEncounter(CREATURE_TANK, num);
		break;
	}
	}
	return 1;
}
