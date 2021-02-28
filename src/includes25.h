




/*
	File created by Chris Johnson.
	These were previously all in game.cpp.

	This file includes all the the enums, defines, and included headers required globally by all components.

	All code released under GNU GPL.
*/
#include <windows.h>
#include <vector>
#include <map>
#include <deque>
#include "cmarkup/Markup.h"
using namespace std;

#include "includesDeprecated.h"
#include "includesRandom.h"
//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
//#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
//#include "activityST.h"

//int get_associated_attribute(int skill_type);
#include "includesSDS.h"
//#include "includesDeprecatedB.h"
//#ifdef	LOCATIONS_CPP
// locations.cpp

#include "../creature/newcreature.h"
#include "../locations/locations.h"
#include "../common/creaturePool.h"
#include "../customMaps.h"
void strcpy(char* c, string str);
void strcat(char* c, string str);
extern short lawList[LAWNUM];
const string CONST_X_BUNKER = "Bunker";
const string CONST_BAR_GRILL = "Bar & Grill";
const string CONST_BOMB_SHELTER = "Bomb Shelter";
const string CONST_OUBLIETTE = "Oubliette";
const string CONST_CLINIC = "Clinic";
const string CONST_U_HOSPITAL = "U Hospital";
const string CONST_RADIO_STATION = "Radio Station";
const string CONST_NEWS_STATION = "News Station";
const string CONST_CHEM_FACT = "Chem Fact";
const string CONST_REFINERY = "Refinery";
const string CONST_PLAST_FACT = "Plast Fact";
const string CONST_ALUM_FACT = "Alum Fact";
const string CONST_SHELTER = "Shelter";
const string CONST_CEO_HOUSE = "CEO House";
const string CONST_X_BANK = "Bank";
const string CONST_CORP_HQ = "Corp. HQ";
const string CONST_MINIPAX = "Minipax";
const string CONST_INT_HQ = "Int. HQ";
const string CONST_MINILUV = "Miniluv";
const string CONST_NPOWER_PLANT = "NPower Plant";
const string CONST_NWASTE_CENTER = "NWaste Center";
const string CONST_JUDGE_HALL = "Judge Hall";
const string CONST_BLACK_MARKET = "Black Market";
const string CONST_ROBERT_E_LEE_BUNKER = "Robert E. Lee Bunker";
const string CONST_DESERT_EAGLE_BAR_GRILL = "Desert Eagle Bar & Grill";
const string CONST_FALLOUT_SHELTER = "Fallout Shelter";
const string CONST_X_PARK = "Park";
const string CONST_X_SPACE_PARK = " Park";
const string CONST_X_LATTE_STAND = "Latte Stand";
const string CONST_LATTE_STAND = " Latte Stand";
const string CONST_CIGAR_BAR = "Cigar Bar";
const string CONST_GENTLEMEN_S_CLUB = " Gentlemen's Club";
const string CONST_NET_CAFE = "Net Cafe";
const string CONST_INTERNET_CAFE = " Internet Cafe";
const string CONST_X_VEGAN_COOP = "Vegan Co-op";
const string CONST_VEGAN_CO_OP = " Vegan Co-op";
const string CONST_X_JUICE_BAR = "Juice Bar";
const string CONST_JUICE_BAR = " Juice Bar";
const string CONST_CRACK_HOUSE = "Crack House";
const string CONST_DISPENSARY = "Dispensary";
const string CONST_MARIJUANA_DISPENSARY = "Marijuana Dispensary";
const string CONST_CANNABIS_LOUNGE = "Cannabis Lounge";
const string CONST_COFFEE_HOUSE = "Coffee House";
const string CONST_DRUGS_CENTER = "Drugs Center";
const string CONST_RECREATIONAL_DRUGS_CENTER = "Recreational Drugs Center";
const string CONST_ST = " St. ";
const string CONST_X_SWEATSHOP = "Sweatshop";
const string CONST_GARMENT_MAKERS = " Garment Makers";
const string CONST_THE_OUBLIETTE = "The Oubliette";
const string CONST_DEPT_STORE = "Dept. Store";
const string CONST_S_DEPARTMENT_STORE = "'s Department Store";
const string CONST_USED_CARS = "Used Cars";
const string CONST_S_USED_CARS = "'s Used Cars";
const string CONST_COSMETICS_LAB = "Cosmetics Lab";
const string CONST_COSMETICS = " Cosmetics";
const string CONST_GENETICS_LAB = "Genetics Lab";
const string CONST_GENETICS = " Genetics";
const string CONST_THE_FREE_CLINIC = "The Free Clinic";
const string CONST_THE_UNIVERSITY_HOSPITAL = "The University Hospital";
const string CONST_PROJECTS = "Projects";
const string CONST_ST_HOUSING_PROJECTS = " St. Housing Projects";
const string CONST_APTS = " Apts";
const string CONST_APARTMENTS = " Apartments";
const string CONST_CONDOS = " Condos";
const string CONST_CONDOMINIUMS = " Condominiums";
const string CONST_AM_RADIO_STATION = "AM Radio Station";
const string CONST_CABLE_NEWS_STATION = "Cable News Station";
const string CONST_CHEMICAL_FACTORY = "Chemical Factory";
const string CONST_AUTO_PLANT = "Auto Plant";
const string CONST_OIL_REFINERY = "Oil Refinery";
const string CONST_PLASTIC_FACTORY = "Plastic Factory";
const string CONST_ALUMINUM_FACTORY = "Aluminum Factory";
const string CONST_BUILDING = "Building";
const string CONST_BUILDING_SITE = "Building Site";
const string CONST_TOY = "Toy";
const string CONST_TOY_FACTORY = "Toy Factory";
const string CONST_PACKING = "Packing";
const string CONST_PACKING_PLANT = "Packing Plant";
const string CONST_STEEL = "Steel";
const string CONST_STEEL_PLANT = "Steel Plant";
const string CONST_DRILL = "Drill";
const string CONST_DRILL_FACTORY = "Drill Factory";
const string CONST_FERTILIZER = "Fertilizer";
const string CONST_FERTILIZER_PLANT = "Fertilizer Plant";
const string CONST_CEMENT = "Cement";
const string CONST_CEMENT_FACTORY = "Cement Factory";
const string CONST_PAPER_MILL = "Paper Mill";
const string CONST_X_WAREHOUSE = "Warehouse";
const string CONST_MEAT_PLANT = "Meat Plant";
const string CONST_ABANDONED = "Abandoned ";
const string CONST_HOMELESS_SHELTER = "Homeless Shelter";
const string CONST_CEO_RESIDENCE = "CEO Residence";
const string CONST_CEO_CASTLE = "CEO Castle";
const string CONST_PAWNSHOP = "Pawnshop";
const string CONST_PAWN_GUN = " Pawn & Gun";
const string CONST_S_PAWNSHOP = "'s Pawnshop";
const string CONST_AMERICAN_BANK_CORP = "American Bank Corp";
const string CONST_CORPORATE_HQ = "Corporate HQ";
const string CONST_WHITE_HOUSE = "White House";
const string CONST_X_ARMY_BASE = "Army Base";
const string CONST_ARMY_BASE = " Army Base";
const string CONST_MINISTRY_OF_PEACE = "Ministry of Peace";
const string CONST_INTELLIGENCE_HQ = "Intelligence HQ";
const string CONST_MINISTRY_OF_LOVE = "Ministry of Love";
const string CONST_NUCLEAR_POWER_PLANT = "Nuclear Power Plant";
const string CONST_NUCLEAR_WASTE_CENTER = "Nuclear Waste Center";
const string CONST_X_PRISON = "Prison";
const string CONST_X_SPACE_PRISON = " Prison";
const string CONST_JOYCAMP = "Joycamp";
const string CONST_FORCED_LABOR_CAMP = " Forced Labor Camp";
const string CONST_FIRE_STATION = "Fire Station";
const string CONST_FIREMAN_HQ = "Fireman HQ";
const string CONST_X_COURTHOUSE = "Courthouse";
const string CONST_HALLS_OF_ULTIMATE_JUDGMENT = "Halls of Ultimate Judgment";
const string CONST_POLICE_STATION = "Police Station";
const string CONST_DEATH_SQUAD_HQ = "Death Squad HQ";
const string CONST_LATTE_NAME_2_TXT = "latte_name_2.txt";
const string CONST_LATTE_NAME_TXT = "latte_name.txt";
const string CONST_CAFE_NAME_2_TXT = "cafe_name_2.txt";
const string CONST_CAFE_NAME_TXT = "cafe_name.txt";
const string CONST_VEGAN_NAME_2_TXT = "vegan_name_2.txt";
const string CONST_VEGAN_NAME_TXT = "vegan_name.txt";
const string CONST_JUICE_NAME_2_TXT = "juice_name_2.txt";
const string CONST_JUICE_NAME_TXT = "juice_name.txt";
const string CONST_LABOR_CAMP_NAME_2_TXT = "labor_camp_name_2.txt";
const string CONST_LABOR_CAMP_NAME_TXT = "labor_camp_name.txt";

const string tag_The = "The ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string locations = "locations\\";

// Finds a location with the corresponding type and returns
// its index in the location array
vector<string> labor_camp_name;
vector<string> labor_camp_name_2;
vector<string> juice_name;
vector<string> juice_name_2;
vector<string> vegan_name;
vector<string> vegan_name_2;
vector<string> cafe_name;
vector<string> cafe_name_2;
vector<string> latte_name;
vector<string> latte_name_2;
vector<file_and_text_collection> locations_text_file_collection = {
	/*locations.cpp*/
	customText(&labor_camp_name, locations + CONST_LABOR_CAMP_NAME_TXT),
	customText(&labor_camp_name_2, locations + CONST_LABOR_CAMP_NAME_2_TXT),
	customText(&juice_name, locations + CONST_JUICE_NAME_TXT),
	customText(&juice_name_2, locations + CONST_JUICE_NAME_2_TXT),
	customText(&vegan_name, locations + CONST_VEGAN_NAME_TXT),
	customText(&vegan_name_2, locations + CONST_VEGAN_NAME_2_TXT),
	customText(&cafe_name, locations + CONST_CAFE_NAME_TXT),
	customText(&cafe_name_2, locations + CONST_CAFE_NAME_2_TXT),
	customText(&latte_name, locations + CONST_LATTE_NAME_TXT),
	customText(&latte_name_2, locations + CONST_LATTE_NAME_2_TXT),
};
//#endif//LOCATIONS_CPP
//#endif// INCLUDES_H_INCLUDED
