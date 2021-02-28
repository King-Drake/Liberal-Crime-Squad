
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

#include "../includes25.h"
#include "../constStringlocations.h"
 void Location::init()
 {
	 haveflag = 0;
	 newrental = 0;
	 heat = 0;
	 heat_protection = 0;
	 closed = 0;
	 mapped = 0;
	 highsecurity = 0;
	 initOtherRNG(mapseed);
	 changes.clear();
	 compound_walls = 0;
	 compound_stores = 0;
	 front_business = -1;
 }
 map<short, string> getCityDescription;
 string Location::city_description()
 {
	 if (getCityDescription.count(type)) {
		 return getCityDescription[type];
	 }
	 else {
		 return "";
	 }
 }
 bool Location::can_be_fortified()
 {
	 if (!upgradable) return false;
	 switch (type)
	 {
	 default:
		 return !fortified();
	 case SITE_OUTDOOR_BUNKER:
	 case SITE_BUSINESS_BARANDGRILL:
		 return false;
	 }
 }
 bool Location::fortified()
 {
	 switch (type)
	 {
	 default:
		 return compound_walls & COMPOUND_BASIC;
	 case SITE_OUTDOOR_BUNKER:
		 return true;
	 }
 }
 bool Location::can_be_trapped()
 {
	 if (!upgradable) return false;
	 return !trapped();
 }
 bool Location::can_install_tanktraps()
 {
	 if (!upgradable) return false;
	 switch (type)
	 {
	 default:
		 return !tank_traps();
	 case SITE_BUSINESS_BARANDGRILL:
	 case SITE_OUTDOOR_BUNKER:
	 case SITE_RESIDENTIAL_BOMBSHELTER:
		 return false;
	 }
 }
 bool Location::tank_traps()
 {
	 switch (type)
	 {
	 default:
		 return compound_walls & COMPOUND_TANKTRAPS;
	 case SITE_OUTDOOR_BUNKER:
	 case SITE_RESIDENTIAL_BOMBSHELTER:
		 return true;
	 }
 }
 bool Location::can_have_businessfront()
 {
	 if (!upgradable) return false;
	 switch (type)
	 {
	 default:
		 return !has_business_front();
	 case SITE_BUSINESS_BARANDGRILL:
	 case SITE_OUTDOOR_BUNKER:
	 case SITE_RESIDENTIAL_BOMBSHELTER:
		 return false;
	 }
 }
 bool Location::has_business_front()
 {
	 return front_business != -1 ||
		 type == SITE_BUSINESS_BARANDGRILL;
 }
 bool Location::bomb_resistant()
 {
	 return type == SITE_RESIDENTIAL_BOMBSHELTER;
 }
 bool Location::part_of_justice_system()
 {
	 return type == SITE_GOVERNMENT_POLICESTATION ||
		 type == SITE_GOVERNMENT_COURTHOUSE ||
		 type == SITE_GOVERNMENT_PRISON;
 }
 void Location::rename(const string name_, const string shortname_)
 {
	 strcpy(this->name, name_.data());
	 strcpy(this->shortname, shortname_.data());
 }
 void renameWarehouse(Location &loc) {
	 do {
		 strcpy(loc.name, CONST_ABANDONED);
		 /*lastname(loc.name,true);
		 strcat(loc.name,singleSpace);*/
		 switch (LCSrandom(10))
		 {
		 case 0:
			 strcat(loc.name, CONST_MEAT_PLANT);
			 strcpy(loc.shortname, CONST_MEAT_PLANT);
			 break;
		 case 1:
			 strcat(loc.name, CONST_X_WAREHOUSE);
			 strcpy(loc.shortname, CONST_X_WAREHOUSE);
			 break;
		 case 2:
			 strcat(loc.name, CONST_PAPER_MILL);
			 strcpy(loc.shortname, CONST_PAPER_MILL);
			 break;
		 case 3:
			 strcat(loc.name, CONST_CEMENT_FACTORY);
			 strcpy(loc.shortname, CONST_CEMENT);
			 break;
		 case 4:
			 strcat(loc.name, CONST_FERTILIZER_PLANT);
			 strcpy(loc.shortname, CONST_FERTILIZER);
			 break;
		 case 5:
			 strcat(loc.name, CONST_DRILL_FACTORY);
			 strcpy(loc.shortname, CONST_DRILL);
			 break;
		 case 6:
			 strcat(loc.name, CONST_STEEL_PLANT);
			 strcpy(loc.shortname, CONST_STEEL);
			 break;
		 case 7:
			 strcat(loc.name, CONST_PACKING_PLANT);
			 strcpy(loc.shortname, CONST_PACKING);
			 break;
		 case 8:
			 strcat(loc.name, CONST_TOY_FACTORY);
			 strcpy(loc.shortname, CONST_TOY);
			 break;
		 case 9:
			 strcat(loc.name, CONST_BUILDING_SITE);
			 strcpy(loc.shortname, CONST_BUILDING);
			 break;
		 }
	 } while (loc.duplicatelocation());
 }
 void renamePrison(Location &loc) {
	 if (lawList[LAW_PRISONS] == -2)
	 {
		 strcpy(loc.name, pickrandom(labor_camp_name));
		 strcat(loc.name, singleSpace);
		 strcat(loc.name, pickrandom(labor_camp_name_2));
		 strcat(loc.name, CONST_FORCED_LABOR_CAMP);
		 strcpy(loc.shortname, CONST_JOYCAMP);
	 }
	 else
	 {
		 strcpy(loc.name, lastname(true));
		 strcat(loc.name, CONST_X_SPACE_PRISON);
		 strcpy(loc.shortname, CONST_X_PRISON);
	 }
 }
 void renamePoluter(Location &loc) {
	 switch (LCSrandom(5))
	 {
	 case 0:
		 loc.rename(CONST_ALUMINUM_FACTORY, CONST_ALUM_FACT);
		 break;
	 case 1:
		 loc.rename(CONST_PLASTIC_FACTORY, CONST_PLAST_FACT);
		 break;
	 case 2:
		 loc.rename(CONST_OIL_REFINERY, CONST_REFINERY);
		 break;
	 case 3:
		 loc.rename(CONST_AUTO_PLANT, CONST_AUTO_PLANT);
		 break;
	 case 4:
		 loc.rename(CONST_CHEMICAL_FACTORY, CONST_CHEM_FACT);
		 break;
	 }
 }
 void renamePoliceStation(Location &loc) {
	 if (lawList[LAW_POLICEBEHAVIOR] == -2 && lawList[LAW_DEATHPENALTY] == -2) {
		 loc.rename(CONST_DEATH_SQUAD_HQ, CONST_DEATH_SQUAD_HQ);
	 }
	 else {
		 loc.rename(CONST_POLICE_STATION, CONST_POLICE_STATION);
	 }
 }
 void renameCourthouse(Location &loc) {
	 if (lawList[LAW_DEATHPENALTY] == -2) {
		 loc.rename(CONST_HALLS_OF_ULTIMATE_JUDGMENT, CONST_JUDGE_HALL);
	 }
	 else {
		 loc.rename(CONST_X_COURTHOUSE, CONST_X_COURTHOUSE);
	 }
 }
 void renameFireStation(Location &loc) {

	 if (lawList[LAW_FREESPEECH] == -2) {
		 loc.rename(CONST_FIREMAN_HQ, CONST_FIREMAN_HQ);
		 loc.hidden = false;
	 }
	 else {
		 loc.rename(CONST_FIRE_STATION, CONST_FIRE_STATION);
		 loc.hidden = true;
	 }
 }
 void renameNuclear(Location &loc) {
	 if (lawList[LAW_NUCLEARPOWER] == 2) {
		 loc.rename(CONST_NUCLEAR_WASTE_CENTER, CONST_NWASTE_CENTER);
	 }
	 else {
		 loc.rename(CONST_NUCLEAR_POWER_PLANT, CONST_NPOWER_PLANT);
	 }
 }
 void renameIntelligenceHQ(Location &loc) {

	 if (lawList[LAW_PRIVACY] == -2 && lawList[LAW_POLICEBEHAVIOR] == -2) {
		 loc.rename(CONST_MINISTRY_OF_LOVE, CONST_MINILUV);
	 }
	 else {
		 loc.rename(CONST_INTELLIGENCE_HQ, CONST_INT_HQ);
	 }
 }
 void renameArmyBase(Location &loc) {
	 if (lawList[LAW_MILITARY] == -2) {
		 loc.rename(CONST_MINISTRY_OF_PEACE, CONST_MINIPAX);
	 }
	 else {
		 strcpy(loc.name, lastname(true));
		 strcat(loc.name, CONST_ARMY_BASE);
		 strcpy(loc.shortname, CONST_X_ARMY_BASE);
	 }
 }
 void renamePawnShop(Location &loc) {

	 strcpy(loc.name, lastname(true));
	 if (lawList[LAW_GUNCONTROL] == ALIGN_ELITELIBERAL)
		 strcat(loc.name, CONST_S_PAWNSHOP);
	 else
		 strcat(loc.name, CONST_PAWN_GUN);
	 strcpy(loc.shortname, CONST_PAWNSHOP);
 }
 void renameCorporateHouse(Location &loc) {

	 if (lawList[LAW_CORPORATE] == -2 && lawList[LAW_TAX] == -2)
		 loc.rename(CONST_CEO_CASTLE, CONST_CEO_CASTLE);
	 else
		 loc.rename(CONST_CEO_RESIDENCE, CONST_CEO_HOUSE);
 }

 void renameCrackhouse(Location &loc) {
	 do {
		 strcpy(loc.name, lastname(true));
		 strcat(loc.name, CONST_ST);
		 if (lawList[LAW_DRUGS] == 2)
		 {
			 switch (LCSrandom(4))
			 {
				 //TODO IsaacG Migrate Strings
			 case 0:
				 strcat(loc.name, CONST_RECREATIONAL_DRUGS_CENTER);
				 strcpy(loc.shortname, CONST_DRUGS_CENTER);
				 break;
			 case 1:
				 strcat(loc.name, CONST_COFFEE_HOUSE);
				 strcpy(loc.shortname, CONST_COFFEE_HOUSE);
				 break;
			 case 2:
				 strcat(loc.name, CONST_CANNABIS_LOUNGE);
				 strcpy(loc.shortname, CONST_CANNABIS_LOUNGE);
				 break;
			 case 3:
				 strcat(loc.name, CONST_MARIJUANA_DISPENSARY);
				 strcpy(loc.shortname, CONST_DISPENSARY);
				 break;
			 }
		 }
		 else
		 {
			 strcat(loc.name, CONST_CRACK_HOUSE);
			 strcpy(loc.shortname, CONST_CRACK_HOUSE);
		 }
	 } while (loc.duplicatelocation());
 }

 void renameApartment(Location &loc) {

	 do {
		 strcpy(loc.name, lastname(true));
		 strcpy(loc.shortname, loc.name);
		 strcat(loc.name, CONST_APARTMENTS);
		 strcat(loc.shortname, CONST_APTS);
	 } while (loc.duplicatelocation());

 }

 void renameUpscaleApt(Location &loc) {

	 do {
		 strcpy(loc.name, lastname(true));
		 strcpy(loc.shortname, loc.name);
		 strcat(loc.name, CONST_CONDOMINIUMS);
		 strcat(loc.shortname, CONST_CONDOS);
	 } while (loc.duplicatelocation());

 }

 void renameTenet(Location &loc) {

	 do {
		 do {
			 strcpy(loc.name, lastname(true));
		 } while (len(loc.name) > 7);
		 strcat(loc.name, CONST_ST_HOUSING_PROJECTS);
		 strcpy(loc.shortname, CONST_PROJECTS);
	 } while (loc.duplicatelocation());

 }
 void returnToDefaultName(Location &loc) {
	 switch (loc.type)
	 {
	 case SITE_GOVERNMENT_WHITE_HOUSE:
		 loc.rename(CONST_WHITE_HOUSE, CONST_WHITE_HOUSE);
		 break;
	 case SITE_CORPORATE_HEADQUARTERS:
		 loc.rename(CONST_CORPORATE_HQ, CONST_CORP_HQ);
		 break;
	 case SITE_BUSINESS_BANK:
		 loc.rename(CONST_AMERICAN_BANK_CORP, CONST_X_BANK);
		 break;
	 case SITE_RESIDENTIAL_SHELTER:
		 loc.rename(CONST_HOMELESS_SHELTER, CONST_SHELTER);
		 break;
	 case SITE_MEDIA_CABLENEWS:
		 loc.rename(CONST_CABLE_NEWS_STATION, CONST_NEWS_STATION);
		 break;
	 case SITE_MEDIA_AMRADIO:
		 loc.rename(CONST_AM_RADIO_STATION, CONST_RADIO_STATION);
		 break;
	 case SITE_HOSPITAL_UNIVERSITY:
		 loc.rename(CONST_THE_UNIVERSITY_HOSPITAL, CONST_U_HOSPITAL);
		 break;
	 case SITE_HOSPITAL_CLINIC:
		 loc.rename(CONST_THE_FREE_CLINIC, CONST_CLINIC);
		 break;
	 case SITE_RESIDENTIAL_BOMBSHELTER:
		 loc.rename(CONST_FALLOUT_SHELTER, CONST_BOMB_SHELTER);
		 break;
	 case SITE_BUSINESS_BARANDGRILL:
		 loc.rename(CONST_DESERT_EAGLE_BAR_GRILL, CONST_BAR_GRILL);
		 break;
	 case SITE_OUTDOOR_BUNKER:
		 loc.rename(CONST_ROBERT_E_LEE_BUNKER, CONST_X_BUNKER);
		 break;
	 case SITE_BUSINESS_ARMSDEALER:
		 loc.rename(CONST_BLACK_MARKET, CONST_BLACK_MARKET);
		 break;
	 case SITE_BUSINESS_HALLOWEEN:
		 loc.rename(CONST_THE_OUBLIETTE, CONST_OUBLIETTE);
		 break;
	 }
 }
 void renameSITE_LABORATORY_GENETIC(char* name, char* shortname) {

	 strcpy(name, lastname(true));
	 strcat(name, CONST_GENETICS);
	 strcpy(shortname, CONST_GENETICS_LAB);
 }
 void renameSITE_LABORATORY_COSMETICS(char* name, char* shortname) {

	 strcpy(name, lastname(true));
	 strcat(name, CONST_COSMETICS);
	 strcpy(shortname, CONST_COSMETICS_LAB);
 }
 void renameSITE_BUSINESS_CARDEALERSHIP(char* name, char* shortname) {

	 generate_name(name, GENDER_WHITEMALEPATRIARCH);
	 strcat(name, CONST_S_USED_CARS);
	 strcpy(shortname, CONST_USED_CARS);
 }
 void renameSITE_BUSINESS_DEPTSTORE(char* name, char* shortname) {

	 strcpy(name, lastname(true));
	 strcat(name, CONST_S_DEPARTMENT_STORE);
	 strcpy(shortname, CONST_DEPT_STORE);
 }
 void renameSITE_INDUSTRY_SWEATSHOP(char* name, char* shortname) {

	 strcpy(name, lastname(true));
	 strcat(name, CONST_GARMENT_MAKERS);
	 strcpy(shortname, CONST_X_SWEATSHOP);
 }
 void renameSITE_BUSINESS_JUICEBAR(char* name, char* shortname) {

	 strcpy(name, "");
	 strcat(name, pickrandom(juice_name));
	 strcat(name, singleSpace);
	 strcat(name, pickrandom(juice_name_2));
	 strcat(name, CONST_JUICE_BAR);
	 strcpy(shortname, CONST_X_JUICE_BAR);
 }
 void renameSITE_BUSINESS_VEGANCOOP(char* name, char* shortname) {

	 strcpy(name, "");
	 strcat(name, pickrandom(vegan_name));
	 strcat(name, singleSpace);
	 strcat(name, pickrandom(vegan_name_2));
	 strcat(name, CONST_VEGAN_CO_OP);
	 strcpy(shortname, CONST_X_VEGAN_COOP);
 }
 void renameSITE_BUSINESS_INTERNETCAFE(char* name, char* shortname) {

	 strcpy(name, "");
	 strcat(name, pickrandom(cafe_name));
	 strcat(name, singleSpace);
	 strcat(name, pickrandom(cafe_name_2));
	 strcat(name, CONST_INTERNET_CAFE);
	 strcpy(shortname, CONST_NET_CAFE);
 }
 void rename(char* name, char* shortname) {

 }
 void renameSITE_BUSINESS_CIGARBAR(char* name, char* shortname) {

	 strcpy(name, tag_The);
	 strcat(name, lastname(true));
	 strcat(name, CONST_GENTLEMEN_S_CLUB);
	 strcpy(shortname, CONST_CIGAR_BAR);
 }
 void renameSITE_BUSINESS_LATTESTAND(char* name, char* shortname) {

	 strcpy(name, "");
	 strcat(name, pickrandom(latte_name));
	 strcat(name, singleSpace);
	 strcat(name, pickrandom(latte_name_2));
	 strcat(name, CONST_LATTE_STAND);
	 strcpy(shortname, CONST_X_LATTE_STAND);
 }
 void renameSITE_OUTDOOR_PUBLICPARK(char* name, char* shortname) {

	 strcpy(name, lastname(true));
	 strcat(name, CONST_X_SPACE_PARK);
	 strcpy(shortname, CONST_X_PARK);
 }
 map<short, vector<string> > getSiteName;
 /* daily - seeds and names a site (will re-seed and rename if used after start) */
 void initlocation(Location &loc)
 {  // NOTE: make sure to keep code here matching code in updateworld_laws() in monthly.cpp for when names are changed
	 loc.init();
	 switch (loc.type)
	 {
	 case SITE_CITY_SEATTLE:
	 case SITE_CITY_LOS_ANGELES:
	 case SITE_CITY_NEW_YORK:
	 case SITE_CITY_CHICAGO:
	 case SITE_CITY_DETROIT:
	 case SITE_CITY_ATLANTA:
	 case SITE_CITY_MIAMI:
	 case SITE_CITY_WASHINGTON_DC:
	 case SITE_DOWNTOWN:
	 case SITE_UDISTRICT:
	 case SITE_COMMERCIAL:
	 case SITE_INDUSTRIAL:
	 case SITE_OUTOFTOWN:
	 case SITE_TRAVEL:
		 loc.rename(getSiteName[loc.type][0], getSiteName[loc.type][1]);
		 break;
	 case SITE_GOVERNMENT_WHITE_HOUSE:
	 case SITE_CORPORATE_HEADQUARTERS:
	 case SITE_BUSINESS_BANK:
	 case SITE_RESIDENTIAL_SHELTER:
	 case SITE_MEDIA_CABLENEWS:
	 case SITE_MEDIA_AMRADIO:
	 case SITE_HOSPITAL_UNIVERSITY:
	 case SITE_HOSPITAL_CLINIC:
	 case SITE_RESIDENTIAL_BOMBSHELTER:
	 case SITE_BUSINESS_BARANDGRILL:
	 case SITE_OUTDOOR_BUNKER:
	 case SITE_BUSINESS_ARMSDEALER:
	 case SITE_BUSINESS_HALLOWEEN:
		 returnToDefaultName(loc);
		 break;
	 case SITE_GOVERNMENT_POLICESTATION:
		 renamePoliceStation(loc);
		 break;
	 case SITE_GOVERNMENT_COURTHOUSE:
		 renameCourthouse(loc);
		 break;
	 case SITE_GOVERNMENT_FIRESTATION:
		 renameFireStation(loc);
		 break;
	 case SITE_GOVERNMENT_PRISON:
		 renamePrison(loc);
		 break;
	 case SITE_INDUSTRY_NUCLEAR:
		 renameNuclear(loc);
		 break;
	 case SITE_GOVERNMENT_INTELLIGENCEHQ:
		 renameIntelligenceHQ(loc);
		 break;
	 case SITE_GOVERNMENT_ARMYBASE:
		 renameArmyBase(loc);
		 break;
	 case SITE_BUSINESS_PAWNSHOP:
		 renamePawnShop(loc);
		 break;
	 case SITE_CORPORATE_HOUSE:
		 renameCorporateHouse(loc);
		 break;
	 case SITE_INDUSTRY_WAREHOUSE:
		 renameWarehouse(loc);
		 break;
	 case SITE_INDUSTRY_POLLUTER:
		 renamePoluter(loc);
		 break;
	 case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
		 renameUpscaleApt(loc);
		 break;
	 case SITE_RESIDENTIAL_APARTMENT:
		 renameApartment(loc);
		 break;
	 case SITE_RESIDENTIAL_TENEMENT:
		 renameTenet(loc);
		 break;
	 case SITE_BUSINESS_CRACKHOUSE:
		 renameCrackhouse(loc);
		 break;
	 case SITE_LABORATORY_GENETIC:
		 renameSITE_LABORATORY_GENETIC(loc.name, loc.shortname);
		 break;
	 case SITE_LABORATORY_COSMETICS:
		 renameSITE_LABORATORY_COSMETICS(loc.name, loc.shortname);
		 break;
	 case SITE_BUSINESS_CARDEALERSHIP:
		 renameSITE_BUSINESS_CARDEALERSHIP(loc.name, loc.shortname);
		 break;
	 case SITE_BUSINESS_DEPTSTORE:
		 renameSITE_BUSINESS_DEPTSTORE(loc.name, loc.shortname);
		 break;
	 case SITE_INDUSTRY_SWEATSHOP:
		 renameSITE_INDUSTRY_SWEATSHOP(loc.name, loc.shortname);
		 break;
	 case SITE_BUSINESS_JUICEBAR:
		 renameSITE_BUSINESS_JUICEBAR(loc.name, loc.shortname);
		 break;
	 case SITE_BUSINESS_VEGANCOOP:
		 renameSITE_BUSINESS_VEGANCOOP(loc.name, loc.shortname);
		 break;
	 case SITE_BUSINESS_INTERNETCAFE:
		 renameSITE_BUSINESS_INTERNETCAFE(loc.name, loc.shortname);
		 break;
	 case SITE_BUSINESS_CIGARBAR:
		 renameSITE_BUSINESS_CIGARBAR(loc.name, loc.shortname);
		 break;
	 case SITE_BUSINESS_LATTESTAND:
		 renameSITE_BUSINESS_LATTESTAND(loc.name, loc.shortname);
		 break;
	 case SITE_OUTDOOR_PUBLICPARK:
		 renameSITE_OUTDOOR_PUBLICPARK(loc.name, loc.shortname);
		 break;
	 }
 }
 