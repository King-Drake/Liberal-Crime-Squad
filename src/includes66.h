




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


//#include "includesDeprecatedB.h"
#include "includesSDS.h"
// basemode.cpp
#include "../creature/creature.h"
////


#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
//#include "../pdcurses/curses.h"
#include "../cursesgraphics.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "../basemode/liberalagenda.h"
bool liberalagenda(signed char won);
#include "../basemode/baseactions.h"
//#include "../basemode/activate_sleepers.h"
void activate_sleepers();
//#include "../basemode/activate.h"
void activate();
//#include "../basemode/reviewmode.h"
void review();
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../common/getnames.h"
// for std::string getmonth(int)
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
//for int mvaddstr(int, int, const char*)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
//#include "../common/equipment.h"
void equip(vector<Item *> &loot, int loc);
//#include "../politics/politics.h"
bool stalinview(short view, bool islaw);
//#include "../monthly/monthly.h"
void passmonth(char &clearformess, char canseethings);
#include "../daily/daily.h"
//for int monthday();
#include "../daily/siege.h"
//for giveup()
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/musicClass.h"
#include "../common/creaturePool.h"
#include "../locations/locationsPool.h"
enum CantSeeReason
{
	CANTSEE_DATING = 1,
	CANTSEE_HIDING = 2,
	CANTSEE_OTHER = 3,
	CANTSEE_DISBANDING = 4
};
bool isPartOfJusticeSystem(int cursite);
bool isThisSafehouse(int loc);
extern bool stalinmode;
extern char cantseereason;
extern char disbanding;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern class Ledger ledger;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int disbandtime;
extern int month;
extern int selectedsiege;
extern int stat_burns;
extern int stat_buys;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short execterm;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short party_status;
extern short senate[SENATENUM];
extern string slogan_str;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatedsquadst *> squad;
int countSafeHouses();
int lenVehiclePool();
Location* getLocation();
void addStringYear();
void burnFlagAtLocation(int l);
void equipLoot(int l, int loc);
void printFlag();


const string P_PATRIOTISM = "P - PATRIOTISM: fly a flag here ($20)";
const string P_PROTEST = "P - PROTEST: burn the flag";
const string S_FREE_SPEECH_LIBERAL_SLOGAN = "S - FREE SPEECH: the Liberal Slogan";
const string NEXT_MONTH = " (next month)";
const string W_WAIT_A_DAY = "W - Wait a day";
const string W_WAIT_OUT_SIEGE = "W - Wait out the siege";
const string CANNOT_WAIT_UNTIL_RESOLVED = "Cannot Wait until Siege Resolved";
const string X_LIVE_TO_FIGHT_ANOTHER_DAY = "X - Live to fight EVIL another day";
const string F_GO_FORTH_TO_STOP_EVIL = "F - Go forth to stop EVIL";
const string G_GIVE_UP = "G - Give Up";
const string F_ESCAPE_ENGAGE = "F - Escape/Engage";
const string C_CANCEL_DEPARTURE = "C - Cancel this Squad's Departure";
const string B_SLEEPERS = "B - Sleepers";
const string A_ACTIVATE_LIBERALS = "A - Activate Liberals";
const string L_STATUS_OF_AGENDA = "L - The Status of the Liberal Agenda";
const string Z_NEXT_LOCATION = "Z - Next Location";
const string TAB_NEXT_SQUAD = "TAB - Next Squad";
const string O_REORDER = "O - Reorder";
const string R_REVIEW_ASSETS_AND_FORM_SQUAD = "R - Review Assets and Form Squads";
const string V_VEHICLES = "V - Vehicles";
const string E_EQUIP_SQUAD = "E - Equip Squad";
const string PLANNING_HEADER = "ÄÄÄ PLANNING ÄÄÄ";
const string ACTIVISM_HEADER = "ÄÄÄ ACTIVISM ÄÄÄ";
const string COLONS_NO_DOTS = ":::::::::";
const string COLONS_AND_DOTS = ":.:.:.:.:";
const string NO_FOOD = " (No Food)";
const string UNDER_SIEGE = "Under Siege";
const string UNDER_ATTACK = "Under Attack";
const string I_INVEST_IN_LOCATION = "I - Invest in this location";

const string tag_Sta = "Sta, ";
const string tag_Libp = "Lib+, ";
const string tag_Lib = "Lib, ";
const string tag_Mod = "Mod, ";
const string tag_Cons = "Cons, ";
const string tag_Consp = "Cons+";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string HOUSE_COLON = "House: ";
const string SENATE_COLON = "Senate: ";
const string SUPREME_COURT_COLON = "Supreme Court: ";
const string MID_LENGTH_LINE = "ÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ";
const string PUBLIC_MOOD = "Public Mood";
const string LIBERTARIAN = "Libertarian";
const string STALINIST = "Stalinist";
const string CONSERVATIVE = "Conservative";
const string LIBERAL = "Liberal";
const string SECOND_TERM = ", 2nd Term";
const string FIRST_TERM = ", 1st Term";
const string PRESIDENT_COLON = "President: ";
const string R_RECREATE_THE_LCS_OR_WAIT_NEXT_MONTH = "R - Recreate the Liberal Crime Squad                  Any Other Key - Next Month";
const string IT_HAS_BEEN_WHILE = "It sure has been a while.  Things might have changed a bit.";
const string IT_HAS_BEEN_LONG_LOT_CHANGED = "It has been a long time.  A lot must have changed...";
const string HOW_LONG_SINCE_TIMES_HAVE_CHANGED = "How long since you've heard these sounds...  times have changed.";
const string TIME_PASSES = "Time passes...";

//#endif//BASEMODE_CPP
//#endif// INCLUDES_H_INCLUDED
