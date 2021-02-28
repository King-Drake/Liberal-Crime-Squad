




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
#include "cmarkup/Markup.h" //For XML.
using namespace std;

#include "includesDeprecated.h"
#include "includesRandom.h"
//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
#include "activityST.h"

//int get_associated_attribute(int skill_type);
#include "includesSDS.h"
#include "includesSDS2.h"
//#include "includesDeprecatedB.h"
//#ifdef	LOCATIONSPOOL_CPP
// locationsPool.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../common/commondisplay.h"
// for void printfunds(int,int,char*)
#include "../common/stringconversion.h"
//for string attribute_enum_to_string(int)
#include "../common/getnames.h"
// for cityname
#include "../common/translateid.h"
// for  getarmortype
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../set_color_support.h"
#include "locationsPool.h"
#include "../common/creaturePoolCreature.h"
#include "../items/money.h"
#include "../recruits.h"
/* creates your founder */
struct newGameArguments {
	const char recruits;
	const char base;
	const bool makelawyer;
	const bool gaylawyer;
	const bool sports_car;
	newGameArguments(char _recruits, char _base, bool _makelawyer, bool _gaylawyer, bool _sports_car) : recruits(_recruits), base(_base), makelawyer(_makelawyer), gaylawyer(_gaylawyer), sports_car(_sports_car) {}
};
Vehicle* newSportsCar();
void newVehicle(Vehicle *startcar);
#include "../common/equipment.h"
#include "../common/creaturePool.h"
void initlocation(Location &loc);
//#include "sitemode/sitemode.h"
void initsite(Location &loc);
#include "../common/commonactionsCreature.h"

#include "../items/lootTypePoolItem.h"
map<short, string> getActivityString;

vector<SiteTypes> classicDowntown = {
	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_MEDIA_AMRADIO,
	SITE_MEDIA_CABLENEWS,
	SITE_BUSINESS_CIGARBAR,
	SITE_BUSINESS_LATTESTAND,
};
vector<SiteTypes> classicCommercial = {

	SITE_BUSINESS_DEPTSTORE,
	SITE_BUSINESS_PAWNSHOP,
	SITE_BUSINESS_HALLOWEEN,
	SITE_BUSINESS_CARDEALERSHIP,
};
vector<SiteTypes> classicUptown = {

	SITE_RESIDENTIAL_APARTMENT,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_HOSPITAL_CLINIC,
	SITE_LABORATORY_GENETIC,
	SITE_LABORATORY_COSMETICS,
	SITE_BUSINESS_VEGANCOOP,
	SITE_BUSINESS_JUICEBAR,
	SITE_BUSINESS_INTERNETCAFE,
	SITE_OUTDOOR_PUBLICPARK,
};
vector<SiteTypes> classicOutOfTown = {

	SITE_GOVERNMENT_PRISON,
	SITE_GOVERNMENT_INTELLIGENCEHQ,
	SITE_INDUSTRY_NUCLEAR,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_CORPORATE_HOUSE,
	SITE_GOVERNMENT_ARMYBASE,
};



vector<SiteTypes> seattleDowntown = {

	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_MEDIA_AMRADIO,
	SITE_BUSINESS_CIGARBAR,
	SITE_BUSINESS_LATTESTAND,
	SITE_BUSINESS_DEPTSTORE,
};

vector<SiteTypes> seattleUptown = {

	SITE_RESIDENTIAL_APARTMENT,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_HOSPITAL_CLINIC,
	SITE_LABORATORY_GENETIC,
	SITE_LABORATORY_COSMETICS,
	SITE_BUSINESS_VEGANCOOP,
	SITE_BUSINESS_JUICEBAR,
	SITE_BUSINESS_INTERNETCAFE,
	SITE_OUTDOOR_PUBLICPARK,
	SITE_BUSINESS_HALLOWEEN,
};
vector<SiteTypes> seattleOutOfTown = {

	SITE_GOVERNMENT_PRISON,
	SITE_GOVERNMENT_INTELLIGENCEHQ,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_GOVERNMENT_ARMYBASE,
};

vector<SiteTypes> newYorkManhattan = {

	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_MEDIA_AMRADIO,
	SITE_MEDIA_CABLENEWS,
	SITE_BUSINESS_CIGARBAR,
	SITE_OUTDOOR_PUBLICPARK,
	SITE_BUSINESS_DEPTSTORE,
	SITE_GOVERNMENT_PRISON,
};

vector<SiteTypes> newYorkLongIsland = {
	SITE_RESIDENTIAL_APARTMENT,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_HOSPITAL_CLINIC,
	SITE_BUSINESS_JUICEBAR,
	SITE_BUSINESS_INTERNETCAFE,
	SITE_INDUSTRY_POLLUTER,
	SITE_LABORATORY_GENETIC,
	SITE_GOVERNMENT_ARMYBASE,
};


vector<SiteTypes> losAngelesDowntown = {



	SITE_RESIDENTIAL_APARTMENT,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_BUSINESS_DEPTSTORE,

};


vector<SiteTypes> hollyWoodUptown = {


	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_BUSINESS_VEGANCOOP,
	SITE_BUSINESS_HALLOWEEN,
	SITE_BUSINESS_CIGARBAR,
	SITE_MEDIA_AMRADIO,
	SITE_OUTDOOR_PUBLICPARK,
	SITE_CORPORATE_HOUSE,


};


vector<SiteTypes> seaportArea = {


	SITE_RESIDENTIAL_TENEMENT,
	SITE_HOSPITAL_CLINIC,
	SITE_LABORATORY_GENETIC,
	SITE_LABORATORY_COSMETICS,
	SITE_INDUSTRY_POLLUTER,
	SITE_BUSINESS_PAWNSHOP,
	SITE_INDUSTRY_SWEATSHOP,
	SITE_BUSINESS_CARDEALERSHIP,


};

vector<SiteTypes> washingtonDCDowntown = {

	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_BUSINESS_BANK,
	SITE_BUSINESS_CARDEALERSHIP,
	SITE_HOSPITAL_CLINIC,
	SITE_HOSPITAL_UNIVERSITY,
	SITE_BUSINESS_DEPTSTORE,

};
#include "../daily/daily.h"
enum cityLocationTagEnums {
	ENUM_tag_Downtown,
	ENUM_tag_University_District,
	ENUM_tag_u_District,
	ENUM_tag_Industrial_District,
	ENUM_tag_i_District,
	ENUM_tag_Shopping,
	ENUM_tag_Outskirts,
	ENUM_tag_Seaport_Area,
	ENUM_tag_Seaport,
	ENUM_tag_Outskirts_amp_Orange_County,
	ENUM_tag_City_Outskirts,
	ENUM_tag_Arlington,
	ENUM_tag_Hollywood,
	ENUM_tag_Greater_Hollywood,
	ENUM_tag_Manhattan,
	ENUM_tag_Manhattan_Island,
	ENUM_tag_Brooklyn_ampersand_Queens,
	ENUM_tag_Long_Island,
	ENUM_tag_The_Bronx
};

// Check if the player wants to move all items to a new location,
// using Shift + a number key.
const char upnums[] = "!@#$%^&*(";
#include "../daily/siege.h"
void addStringYear();
#include "../common/commonactions.h"
#include "../common/musicClass.h"
#include "../customMaps.h"
enum BusinessFronts
{
	BUSINESSFRONT_INSURANCE,
	BUSINESSFRONT_TEMPAGENCY,
	BUSINESSFRONT_RESTAURANT,
	BUSINESSFRONT_MISCELLANEOUS,
	BUSINESSFRONTNUM
};
// Gives you bloody armor
extern bool GIVEBLOODYARMOR;
// Start with lots of money
extern bool HIGHFUNDS;

extern long cursquadid;
extern vector<ClipType *> cliptype;
extern vector<ArmorType *> armortype;

extern bool multipleCityMode;
extern char endgamestate;
extern class Ledger ledger;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int month;
extern int selectedsiege;
extern int stat_kidnappings;
extern int year;
extern MusicClass music;
extern short background_liberal_influence[VIEWNUM];
extern short lawList[LAWNUM];
extern vector<Deprecatedsquadst *> squad;
extern vector<WeaponType *> weapontype;

/* monthly - lets the player choose a special edition for the guardian */
int choosespecialedition(char &clearformess);
/* monthly - guardian - prints liberal guardian special editions */
void printnews(short l, short newspaper);
#include "../items/itemPool.h"
#include "../items/lootTypePool.h"
void giveActiveSquadThisLoot(Item* de);