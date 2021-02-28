




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
/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);
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
const string CHOOSE_A_LIBERAL_TO = "Choose a Liberal squad member to ";
//#ifdef	DAILY_CPP
// daily.cpp


const string notEnoughMoney = "You don't have enough money!";
const string CHOOSE_A_COLOR = "Choose a color";
const string theseColorsAreCon = "These colors are Conservative";
const string thisColor = "Color";
const string CHOOSE_A_VEHICLE = "Choose a vehicle";
const string thisVehicle = "Vehicle";
const string weDontNeedCar = "We don't need a Conservative car";
const string B_CHOOSE_BUYER = "B - Choose a buyer";
const string s_sellCar = "S - Sell a car";
const string s_sellThe = "S - Sell the ";
const string g_getCar = "G - Get a Liberal car";
const string toSpend = "SPEND.";
const string enterLeave = "Enter - Leave";
const string f_fixWounds = "F - Go in and fix up Conservative wounds";
const string WAS_TOO_HOT_TO_RISK = " was too hot to risk.";
const string DECIDED = " decided ";
const string REGAINS_CONTACT = " regains contact with the LCS.";
const string CONST_CREATURE_POLITICALACTIVIST = "CREATURE_POLITICALACTIVIST";
const string CONST_CREATURE_TEENAGER = "CREATURE_TEENAGER";
const string THE_LIBERAL_WILL_BE_MISSED = ". The Liberal will be missed.";
const string HAS_PASSED_AWAY = " has passed away at the age of ";
const string SURFS_THE_NET = " surfs the Net for recent opinion polls.";
const string WHY_IS_THE_SQUAD_HERE = "Why is the squad here?   (S)afe House, to cause (T)rouble, or (B)oth?";
const string HAS_ARRIVED_AT = " has arrived at ";
const string LOOKS_AROUND = " looks around ";
const string ARRIVES_IN = " arrives in ";
const string SPENT_ON_TICKETS = "%s spent $%d on tickets to go to %s.";
const string COULDNT_AFFORD_TICKETS = "%s couldn't afford tickets to go to %s.";
const string TRAVEL_LOCATION = "travel location";
const string DIDNT_HAVE_A_CAR = " didn't have a car to get to ";
const string COULDNT_USE_THE = " couldn't use the ";
const string INSTEAD_OF = " instead of ";
const string ACTED_WITH = " acted with ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string CONST_OUBLIETTE_XML = "oubliette.xml";
const string CONST_DEPTSTORE_XML = "deptstore.xml";
const string CONST_P_REPAINT_CAR_REPLACE_PLATES_AND_TAGS_500 = "P - Repaint car, replace plates and tags ($500)";
const string CONST_PAWNSHOP_XML = "pawnshop.xml";
const string CONST_ARMSDEALER_XML = "armsdealer.xml";
const string SPENT_DOLLARS = " spent $";
const string ON_TICKETS = " on tickets to go to ";
const string SINGLE_DOT = ".";
const string COULDNT_AFFORD_TICKETSA = " couldn't afford tickets to go to %";
const string COULDNT_AFFORD_TICKETSB = ".";

#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureA.h"

#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "../news/news.h"
void majornewspaper(char &clearformess, char canseethings);
//#include "../sitemode/sitemode.h"
void mode_site(const short loc);
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for makedelimeter
#include "../common/getnames.h"
// for std::string getactivity(ActivityST)
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
/* tells how many total members a squad has (including dead members) */
// for void basesquad(squadst *,long)
#include "../daily/daily.h"
/* squad members with no chain of command lose contact */
void dispersalcheck(char &clearformess);

#include "../daily/activities.h"
//for void repairarmor(Creature &cr,char &clearformess); and stealcar
#include "../daily/siege.h"        
//for sigeturn and siegecheck
//#include "../daily/recruit.h"
void recruitment_activity(DeprecatedCreature &cr);
char completerecruitmeeting(Deprecatedrecruitst &d, const int p);
//#include "../daily/date.h"
char completevacation(Deprecateddatest &d, int p);
char completedate(Deprecateddatest &d, int p);
#include "../combat/chaseCreature.h"
//for int driveskill(Creature &cr,Vehicle &v);
//hmm --Schmel924
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../title/titlescreen.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"


#include "../sitemode/shop.h"
#include "../common/musicClass.h"


bool carselect(DeprecatedCreature &cr, short &cartype);
bool stealcar(DeprecatedCreature &cr, char &clearformess);
bool vehicletypeavailableatshop(const int i);
DeprecatedCreature* findSleeperCarSalesman(int loc);
extern char artdir[MAX_PATH_SIZE];
extern char disbanding;
extern char showcarprefs;
extern class Ledger ledger;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int month;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short fieldskillrate;
extern short party_status;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatednewsstoryst *> newsstory;
extern vector<Deprecatedrecruitst *> recruit;
extern vector<Deprecatedsquadst *> squad;
extern vector<Vehicle *> vehicle;
int driveskill(DeprecatedCreature &cr, int v);
int getVehicleTypePrice(const int carchoice);
int getVehicleTypeSleeperPrice(const int carchoice);
int lenVehicleType();
string getVehicleFullname(int i);
string vehicleTypelongname(const int p);
vector<string> getVehicleTypeColor(const int carchoice);
Vehicle* getVehicleFromTypeYear(const int carchoice, const int colorchoice, const int year);
void basesquad(Deprecatedsquadst *st, long loc);
void clearCarStates();
void determineMedicalSupportAtEachLocation(bool clearformess);
void doDates(char &clearformess);
void getwheelchair(DeprecatedCreature &cr, char &clearformess);
void locateActiveSquad(const int loc);
void locatesquad(Deprecatedsquadst *st, long loc);
void makearmor(DeprecatedCreature &cr, char &clearformess);
void repairarmor(DeprecatedCreature &cr, char &clearformess);
void survey(DeprecatedCreature *cr);
void tendhostage(DeprecatedCreature *cr, char &clearformess);
//#endif//DAILY_CPP
//#endif// INCLUDES_H_INCLUDED
