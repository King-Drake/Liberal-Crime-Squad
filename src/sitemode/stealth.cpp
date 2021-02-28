
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

#include "../includes08.h"
#include "../constStringstealth.h"
 void noticecheck(int exclude, int difficulty)
 {

	 vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	 if (isThereASiteAlarm()) return;
	 char sneak = 0;
	 int topi = 0;
	 for (int i = 0; i < 6; ++i) if (activesquad->squad[i] && activesquad->squad[i]->get_skill(SKILL_STEALTH) > sneak)
		 sneak = activesquad->squad[i]->get_skill(SKILL_STEALTH), topi = i;
	 for (int e = 0; e < ENCMAX; e++)
	 {  //Prisoners shouldn't shout for help.
		 if (isPrisoner(encounter[e].name) || e == exclude || encounter[e].exists == false || activesquad->squad[topi]->skill_check(SKILL_STEALTH, difficulty)) { 
			 continue; 
		 }
		 else
		 {
			 printShoutsForHelp(encounter[e].name, encounter[e].align);
			 setSiteAlarmOne();
			 pressAnyKey();
			 break;
		 }
	 }
 }

 /* checks if your liberal behavior/attack alienates anyone */
 char alienationcheck(char mistake)
 {
	 vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	 if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))return 0;
	 char alienate = 0;

	 int oldsitealienate = sitealienate;
	 vector<int> noticer;
	 for (int e = 0; e < ENCMAX; e++)
	 {
		 // Prisoners should never be alienated by your crimes, as
		 // they're happy to have you attacking their place of holding
		 //if(encounter[e].type==CREATURE_PRISONER)continue;
		 // ...but Prisoners are now spawned with a variety of creature
		 // types, so we'll go by name instead
		 if (isPrisoner(encounter[e].name)) continue;
		 if (encounter[e].exists&&encounter[e].alive && (encounter[e].align == 0 || (encounter[e].align == 1 && mistake)))
			 noticer.push_back(e);
	 }
	 if (len(noticer))
	 {
		 char alienatebig = 0;
		 do
		 {
			 int an = LCSrandom(len(noticer));
			 int n = noticer[an];
			 noticer.erase(noticer.begin() + an);
			 if (encounter[n].align == 1) alienatebig = 1;
			 else alienate = 1;
		 } while (len(noticer));
		 if (alienatebig) sitealienate = 2;
		 if (alienate&&sitealienate != 2) sitealienate = 1;
		 if (oldsitealienate < sitealienate)
		 {
			 printAlienation(sitealienate);
			 setSiteAlarmOne();
			 for (int i = 0; i < ENCMAX; i++)
				 if (encounter[i].exists && encounter[i].align != ALIGN_CONSERVATIVE)
					 if (encounter[i].align == ALIGN_MODERATE || alienatebig)
						 conservatise(i);
			 if (mode == GAMEMODE_CHASECAR ||
				 mode == GAMEMODE_CHASEFOOT) printchaseencounter();
			 else printencounter();
			 pressAnyKey();
		 }
	 }
	 return alienate;
 }

 char weapon_in_character(const string wtype, const string atype)
 {
	 //// TODO Move to XML
	 if (atype == tag_ARMOR_LABCOAT && wtype == tag_WEAPON_SYRINGE)
		 return CREATURE_SCIENTIST_LABTECH;
	 if (atype == tag_ARMOR_BLACKROBE && wtype == tag_WEAPON_GAVEL)
		 return CREATURE_JUDGE_LIBERAL;
	 if (atype == tag_ARMOR_SECURITYUNIFORM && (wtype == tag_WEAPON_REVOLVER_38 ||
		 wtype == tag_WEAPON_REVOLVER_44 || wtype == tag_WEAPON_DESERT_EAGLE ||
		 wtype == tag_WEAPON_SEMIPISTOL_9MM || wtype == tag_WEAPON_SEMIPISTOL_45 ||
		 wtype == tag_WEAPON_NIGHTSTICK || wtype == tag_WEAPON_MP5_SMG))
		 return CREATURE_SECURITYGUARD;
	 if ((atype == tag_ARMOR_POLICEUNIFORM || atype == tag_ARMOR_POLICEARMOR) &&
		 (wtype == tag_WEAPON_REVOLVER_38 || wtype == tag_WEAPON_REVOLVER_44 ||
			 wtype == tag_WEAPON_DESERT_EAGLE || wtype == tag_WEAPON_SEMIPISTOL_9MM ||
			 wtype == tag_WEAPON_SEMIPISTOL_45 || wtype == tag_WEAPON_NIGHTSTICK ||
			 wtype == tag_WEAPON_SHOTGUN_PUMP))
		 return CREATURE_COP;
	 if (wtype == tag_WEAPON_SMG_MP5 || wtype == tag_WEAPON_CARBINE_M4)
	 {
		 if (atype == tag_ARMOR_SWATARMOR)
			 return CREATURE_SWAT;
		 else if (atype == tag_ARMOR_SECURITYUNIFORM && lawList[LAW_GUNCONTROL] == -2)
			 return CREATURE_SECURITYGUARD;
		 else if (atype == tag_ARMOR_MILITARY || atype == tag_ARMOR_ARMYARMOR)
			 return CREATURE_SOLDIER;
	 }
	 if (wtype == tag_WEAPON_AUTORIFLE_M16 || wtype == tag_WEAPON_SEMIRIFLE_AR15)
	 {
		 // Military
		 if (atype == tag_ARMOR_MILITARY || atype == tag_ARMOR_ARMYARMOR)
			 return CREATURE_SOLDIER;
		 if (atype == tag_ARMOR_DEATHSQUADUNIFORM)
			 return CREATURE_DEATHSQUAD;
	 }
	 if (wtype == tag_WEAPON_AXE && atype == tag_ARMOR_BUNKERGEAR)
		 return CREATURE_FIREFIGHTER;
	 if (wtype == tag_WEAPON_FLAMETHROWER && atype == tag_ARMOR_BUNKERGEAR && lawList[LAW_FREESPEECH] == -2)
		 return CREATURE_FIREFIGHTER;
	 if (atype == tag_ARMOR_PRISONGUARD && (wtype == tag_WEAPON_SMG_MP5 ||
		 wtype == tag_WEAPON_SHOTGUN_PUMP || wtype == tag_WEAPON_NIGHTSTICK))
		 return CREATURE_PRISONGUARD;
	 if ((atype == tag_ARMOR_OVERALLS || atype == tag_ARMOR_WIFEBEATER) &&
		 (wtype == tag_WEAPON_TORCH || wtype == tag_WEAPON_PITCHFORK ||
		 (lawList[LAW_GUNCONTROL] == -2 && wtype == tag_WEAPON_SHOTGUN_PUMP)))
		 return CREATURE_HICK;
	 if (wtype == tag_WEAPON_SHANK && atype == tag_ARMOR_PRISONER)
		 return CREATURE_PRISONER;
	 if (wtype == tag_WEAPON_CHAIN &&
		 (atype == tag_ARMOR_WORKCLOTHES || atype == tag_ARMOR_HARDHAT))
		 return CREATURE_WORKER_FACTORY_UNION;
	 if (wtype == tag_WEAPON_CARBINE_M4 && atype == tag_ARMOR_SEALSUIT)
		 return CREATURE_SEAL;
	 return -1;
 }
 
 /* checks if a creature's uniform is appropriate to the location */
 char hasdisguise(const DeprecatedCreature &cr)
 {
	 short type = -1;
	 if (getCurrentSite() >= 0)type = LocationsPool::getInstance().getLocationType(getCurrentSite());
	 char uniformed = 0;
	 // Never uniformed in battle colors
	 //if(activesquad->stance==SQUADSTANCE_BATTLECOLORS)
	 //   return 0;
	 if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	 {
		 switch (LocationsPool::getInstance().getSiegeType(getCurrentSite()))
		 {
		 case SIEGE_CCS:
		 {
			 // CCS has trained in anticipation of this tactic
			 // There is no fooling them
			 // (They pull this shit all the time in their own sieges)
			 uniformed = 0;
			 break;
		 }
		 case SIEGE_POLICE:
		 {
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR &&
				 LocationsPool::getInstance().getSiegeEscalationState(getCurrentSite()) == 0)uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_MILITARY &&
				 LocationsPool::getInstance().getSiegeEscalationState(getCurrentSite()) > 0)uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_ARMYARMOR &&
				 LocationsPool::getInstance().getSiegeEscalationState(getCurrentSite()) > 0)uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SEALSUIT &&
				 LocationsPool::getInstance().getSiegeEscalationState(getCurrentSite()) > 0)uniformed = 1;
			 break;
		 }
		 default:
			 if (siegeDisguises.count(LocationsPool::getInstance().getSiegeType(getCurrentSite())) > 0) {
				 if (siegeDisguises[LocationsPool::getInstance().getSiegeType(getCurrentSite())].count(cr.get_armor().get_itemtypename()) > 0) {
					 uniformed = siegeDisguises[LocationsPool::getInstance().getSiegeType(getCurrentSite())][cr.get_armor().get_itemtypename()];
				 }
			 }
			 break;
		 }
	 }
	 else
	 {
		 //// TODO Move to XML
		 if ((!cr.is_naked() || cr.animalgloss == ANIMALGLOSS_ANIMAL)
			 && cr.get_armor().get_itemtypename() != tag_ARMOR_HEAVYARMOR)uniformed = 1;

		 switch (type)
		 {
		 case SITE_INDUSTRY_WAREHOUSE:
		 case SITE_RESIDENTIAL_SHELTER:
			 uniformed = 1;
			 break;

		 case SITE_LABORATORY_COSMETICS:
		 case SITE_LABORATORY_GENETIC:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 uniformed = 0;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_LABCOAT)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SECURITYUNIFORM)uniformed = (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()) ? 1 : 2);
			 }
			 break;
		 case SITE_GOVERNMENT_POLICESTATION:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 uniformed = 0;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR)uniformed = 1;
				 if (lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2 &&
					 cr.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM)uniformed = 1;


				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR)uniformed = (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()) ? 1 : 2);
			 }
			 break;
		 case SITE_BUSINESS_BANK:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 uniformed = 0;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_CHEAPSUIT)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_EXPENSIVESUIT)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_CHEAPDRESS)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_EXPENSIVEDRESS)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SECURITYUNIFORM)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR)uniformed = 1;
				 if (lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2 &&
					 cr.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM)uniformed = 1;


				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR)uniformed = (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()) ? 1 : 2);
				 if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()))
				 {
					 if (cr.get_armor().get_itemtypename() == tag_ARMOR_CIVILLIANARMOR)uniformed = 1;
				 }
			 }
			 break;
		 case SITE_GOVERNMENT_COURTHOUSE:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 uniformed = 0;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_BLACKROBE)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_BLACKSUIT)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_BLACKDRESS)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_CHEAPSUIT)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_CHEAPDRESS)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_EXPENSIVESUIT)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_EXPENSIVEDRESS)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR)uniformed = 1;

				 if (lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2 &&
					 cr.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM)uniformed = 1;

				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR)uniformed = (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()) ? 1 : 2);
			 }
			 break;
		 case SITE_GOVERNMENT_FIRESTATION:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 uniformed = 0;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_BUNKERGEAR)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_WORKCLOTHES)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_OVERALLS)uniformed = 1;
				 if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()))
				 {
					 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM)uniformed = 1;
					 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR)uniformed = 1;
					 if (lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2 &&
						 cr.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM)uniformed = 1;
					 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR)uniformed = 1;
				 }
			 }
			 break;
		 case SITE_INDUSTRY_SWEATSHOP:
			 uniformed = 0;
			 if (cr.is_naked())uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SECURITYUNIFORM)uniformed = 1;
			 break;
		 case SITE_GOVERNMENT_PRISON:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 uniformed = 0;
				 if (lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2)
				 {
					 if (cr.get_armor().get_itemtypename() == tag_ARMOR_LABCOAT)uniformed = 1;
				 }
				 else if (cr.get_armor().get_itemtypename() == tag_ARMOR_PRISONGUARD)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_PRISONER)uniformed = 1;
			 }
			 break;
		 case SITE_INDUSTRY_POLLUTER:
			 uniformed = 0;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_WORKCLOTHES)uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_HARDHAT)uniformed = 1;
			 if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()))
			 {
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SECURITYUNIFORM)uniformed = 1;
			 }
			 break;
		 case SITE_CORPORATE_HOUSE:
			 uniformed = 0;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_EXPENSIVESUIT)uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_EXPENSIVEDRESS)uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SECURITYUNIFORM)uniformed = 1;
			 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SERVANTUNIFORM)uniformed = 1;
			 if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()))
			 {
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_MILITARY)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_ARMYARMOR)uniformed = 1;
				 if (cr.get_armor().get_itemtypename() == tag_ARMOR_SEALSUIT)uniformed = 1;
			 }
			 break;

		 case SITE_RESIDENTIAL_TENEMENT:
		 case SITE_RESIDENTIAL_APARTMENT:
		 case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)uniformed = 0;
			 break;
		 default:
			 if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 //if_count		
				 if (siteDisguisesRestricted.count(type) > 0) {
					 uniformed = 0;
					 if (siteDisguisesRestricted[type].count(cr.get_armor().get_itemtypename()) > 0) {
						 uniformed = siteDisguisesRestricted[type][cr.get_armor().get_itemtypename()];
					 }
				 }
			 }
			 else
			 {
				 if (siteDisguises.count(type) > 0) {
					 uniformed = 0;
					 if (siteDisguises[type].count(cr.get_armor().get_itemtypename()) > 0) {
						 uniformed = siteDisguises[type][cr.get_armor().get_itemtypename()];
					 }
				 }
			 }
			 break;
		 }
	 }
	 if (!uniformed)
	 {
		 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEUNIFORM)uniformed = 2;
		 if (cr.get_armor().get_itemtypename() == tag_ARMOR_POLICEARMOR)uniformed = 2;
		 if (lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2 &&
			 cr.get_armor().get_itemtypename() == tag_ARMOR_DEATHSQUADUNIFORM)uniformed = 2;
		 if (LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()) &&
			 cr.get_armor().get_itemtypename() == tag_ARMOR_SWATARMOR)uniformed = 2;
		 // Loop over adjacent locations to check if fire is anywhere in sight?
		 // Or perhaps have a site fire alarm? - Nick
		 if ((levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_START ||
			 levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_END ||
			 levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_PEAK) &&
			 cr.get_armor().get_itemtypename() == tag_ARMOR_BUNKERGEAR)uniformed = 1;
	 }
	 if (uniformed)
	 {
		 int qlmax = cr.get_armor().get_quality_levels();
		 int ql = cr.get_armor().get_quality() + cr.get_armor().is_damaged();
		 if (ql > qlmax)  // Shredded clothes are obvious
		 {
			 uniformed = 0;
		 }
		 else if ((ql - 1) * 2 > qlmax) // poor clothes make a poor disguise
		 {
			 uniformed++;
		 }
		 if (uniformed > 2)
			 uniformed = 0;
	 }
	 return uniformed;
 }

 /* checks if a creature's weapon is suspicious */
 char weaponcheck(const DeprecatedCreature &cr, bool metaldetect)
 {
	 bool suspicious = cr.get_weapon().get_specific_bool(BOOL_SUSPICIOUS_);
	 bool concealed = cr.weapon_is_concealed();
	 char incharacter = weapon_in_character(cr.get_weapon().get_itemtypename(), cr.get_armor().get_itemtypename());
	 // If your disguise is inappropriate to the current location,
	 // then being in character isn't sufficient
	 if (hasdisguise(cr) == false)
		 incharacter = -1;
	 if (suspicious)
	 {
		 if (concealed && !metaldetect)
			 return 0; // Hidden weapon, nothing to see
		 else if (incharacter >= 0)
			 return 1; // You look like you're supposed to have that weapon
		 else
			 return 2; // Looks like trouble
	 }
	 return 0; // Nothing to see here
 }
 /* checks if conservatives see through your disguise */
 void disguisecheck(int timer)
 {
	 int weapon = 0, partysize = activesquadSize();

	 bool forcecheck = false;

	 //int weaponar[6]={0};
	 // Only start to penalize the player's disguise/stealth checks after the first turn.
	 timer--;
	 for (int i = 0; i < 6; i++)
	 {
		 if (activesquad->squad[i] == NULL)break;
		 if (activesquad->squad[i]->is_naked() &&
			 activesquad->squad[i]->animalgloss != ANIMALGLOSS_ANIMAL)forcecheck = true;
		 int thisweapon = weaponcheck(*activesquad->squad[i], false);
		 if (thisweapon > weapon)weapon = thisweapon;
		 //if(thisweapon==2)weaponar[i]=1;
	 }
	 // TODO if a weapon is holstered
	 // meaning if it is within the squad inventory but not equipped by a squad member
	 // not even metal detectors can detect it
	 // This line checks all such weapons
	 // but does nothing with the information
	 // pending an overhaul of weapon concealment
	 /*for (Item *l : activesquad->loot) {
		 if (l->whatIsThis() == THIS_IS_WEAPON) {
			 int thisweapon = static_cast <Weapon*> (l)->is_suspicious();
			 //if (thisweapon > weapon)weapon = thisweapon;
		 }
	 }*/
	 // Nothing suspicious going on here
	 if (sitealarmtimer == -1 && weapon < 1 && !forcecheck)
	 {
		 if (!disguisesite(LocationsPool::getInstance().getLocationType(getCurrentSite())) &&
			 !(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED))return;
	 }
	 vector<int> noticer = potentialEncounterNoticers();
	 vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	 if (len(noticer))
	 {
		 int n;
		 int blew_it = -1;
		 bool spotted = false;
		 bool noticed = false;
		 for(int ji = len(noticer); !noticed && ji > 0; ji--)
		 {
			 int an = LCSrandom(len(noticer));
			 n = noticer[an];
			 noticer.erase(noticer.begin() + an);
			 int stealth_difficulty;
			 int disguise_difficulty;
			 //// TODO Move to XML
			 // Determine difficulty based on enemy type
			 stealth_difficulty = get_stealth_difficulty(n);
			 disguise_difficulty = get_disguise_difficulty(n);
			 // Increase difficulty if Conservatives suspicious...
			 if (sitealarmtimer == 1)
			 {
				 stealth_difficulty += 2;
				 disguise_difficulty += 4;
			 }
			 else if (sitealarmtimer > 1)
			 {
				 stealth_difficulty += 1;
				 disguise_difficulty += 2;
			 }
			 // Sneaking with a party is hard
			 stealth_difficulty += (partysize - 1);
			 if (stealth_difficulty > DIFFICULTY_SUPERHEROIC) {
				 stealth_difficulty = DIFFICULTY_SUPERHEROIC;
			 }
			 // Make the attempt!
			 for (int i = 0; i < 6 && !noticed && activesquad->squad[i] != NULL; i++)
			 {
				 // Try to sneak.
				 if (!spotted)
				 {
					 int result = activesquad->squad[i]->skill_roll(SKILL_STEALTH);
					 result -= timer;
					 if (fieldskillrate == FIELDSKILLRATE_HARD && result + 1 == stealth_difficulty)
					 {// Hard more = You only learn if you just missed, and realize what you did wrong.
						 activesquad->squad[i]->train(SKILL_STEALTH, 10);
					 }
					 if (result < stealth_difficulty)
						 spotted = true;
				 }
				 // Spotted! Act casual.
				 if (spotted)
				 {
					 // Scary weapons are not very casual.
					 if (weaponcheck(*activesquad->squad[i], false) == 2)
					 {
						 noticed = true;
					 }
					 else
					 {
						 int result = activesquad->squad[i]->skill_roll(SKILL_DISGUISE);
						 result -= timer;
						 if (fieldskillrate == FIELDSKILLRATE_HARD && result + 1 == disguise_difficulty)
						 {// Hard more = You only learn if you just missed, and realize what you did wrong.
							 activesquad->squad[i]->train(SKILL_DISGUISE, 10);
						 }
						 if (result < disguise_difficulty)
						 {
							 // That was not very casual, dude.
							 if (result < 0)blew_it = i;
							 noticed = true;
						 }
					 }
				 }
			 }
		 } 
		 // Give feedback on the Liberal Performance
		 if (!spotted)
		 {
			 for (int i = 0; i < 6; i++)
			 {
				 if (activesquad->squad[i] == NULL) break;
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
			 if (timer == 0)
			 {
				 printFadesAway(activesquad->squad[0]->getNameAndAlignment().name, partysize);
				 pressAnyKey();
			 }
		 }
		 else
		 {
			 if (blew_it == -1)
			 {
				 for (int i = 0; i < 6; i++)
				 {
					 if (activesquad->squad[i] == NULL) break;
					 if (hasdisguise(*(activesquad->squad[i])))
					 {
						 switch (fieldskillrate)
						 {
							 //// TODO Move to XML
						 case FIELDSKILLRATE_FAST:
							 activesquad->squad[i]->train(SKILL_DISGUISE, 50); break;
						 case FIELDSKILLRATE_CLASSIC:
							 activesquad->squad[i]->train(SKILL_DISGUISE, 10); break;
						 case FIELDSKILLRATE_HARD:
							 activesquad->squad[i]->train(SKILL_DISGUISE, 0); break;
						 }
					 }
				 }
			 }
			 if (blew_it != -1 && LCSrandom(2))
			 {
				 printBlewStealthCheck(activesquad->squad[blew_it]->getNameAndAlignment().name);
				 pressAnyKey();
			 }
			 else if (!noticed)
			 {
				 printActsNatural(activesquad->squad[0]->getNameAndAlignment().name, partysize);
				 pressAnyKey();
			 }
		 }
		 if (!noticed)return;
		 printEnemyNameInAlarm(encounter[n].name);
		 if (sitealarmtimer != 0 && weapon < 1 && encounter[n].type != CREATURE_GUARDDOG)
		 {
			 if ((sitetype == SITE_RESIDENTIAL_TENEMENT ||
				 sitetype == SITE_RESIDENTIAL_APARTMENT ||
				 sitetype == SITE_RESIDENTIAL_APARTMENT_UPSCALE) &&
				 levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_RESTRICTED)
			 {
				 printShoutsInAlarm();
				 setSiteAlarmOne();
			 }
			 else
			 {
				 printLooksAtSquadSuspiciously();
				 int time = get_encounter_time(n);
				 if (time < 1)time = 1;
				 if (sitealarmtimer > time || sitealarmtimer == -1)sitealarmtimer = time;
				 else
				 {
					 if (sitealarmtimer > 5) sitealarmtimer -= 5;
					 if (sitealarmtimer <= 5)sitealarmtimer = 0;
				 }
			 }
		 }
		 else
		 {
			 printConservativeRaisesAlarm(weapon, encounter[n].type, encounter[n].align);
			 setSiteAlarmOne();
		 }
		 pressAnyKey();
	 }
 }
 