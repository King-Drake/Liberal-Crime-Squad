




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
//

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

//#include "includesDeprecatedB.h"
//#ifdef	MONTHLY_CPP
// monthly.cpp

#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../basemode/liberalagenda.h"
// for liberalagenda
//#include "../items/itemPool.h"
//#include "../items/lootTypePool.h"
//#include "../common/commonactions.h"
char endcheck(char cause);
void change_public_opinion(int v, int power, char affect = 1, char cap = 100);
#include "../log/log.h"
#include "../common/commondisplay.h"
// for set_alignment_color and delimiter
#include "../common/translateid.h"
// for  int getpoolcreature(int id);
#include "../title/titlescreen.h"
// for void reset;
#include "../title/highscore.h"
// for viewhighscores, in event of EndGameStatus
#include "../politics/politics.h"
//for publicmood
//#include "../monthly/lcsmonthly.h"
void fundreport(char &clearformess);
//#include "../daily/daily.h"
//for dispersalcheck and securitytable
void dispersalcheck(char &clearformess);
#include "../cursesAlternative.h"
#include "../set_color_support.h"
//#include <common\\getnames.h>
std::string getview(short view, bool shortname);
#include "../locations/locationsPool.h"
#include "../locations/locationsEnums.h"
#include "../common/creaturePool.h"
#include "../common/creaturePoolHeader.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
void clearRentExemptions();
void publishSpecialEditions(char &clearformess);
void manageGrafiti();


#include "../common/musicClass.h"
extern bool SHOWMECHANICS;
extern bool SHOWWAIT;
extern bool stalinmode;
extern char disbanding;
extern char endgamestate;
extern char newscherrybusted;
extern class Ledger ledger;
extern int day;
extern int disbandtime;
extern int month;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short lawList[LAWNUM];
extern short public_interest[VIEWNUM];

const string CONST_THEY_WILL_NEVER_SEE_THE_UTOPIA_THEY_DREAMED_OF = "They will never see the utopia they dreamed of...";
const string CONST_THE_LAST_LCS_MEMBERS_HAVE_ALL_BEEN_HUNTED_DOWN = "The last LCS members have all been hunted down.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_IS_NOW_JUST_A_MEMORY = "The Liberal Crime Squad is now just a memory.";

const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THESE_POLL_NUMBERS = "Press any key to reflect on these poll numbers.";
const string CONST_ARCH_CONSERVATIVE_UPPERCASE = "Arch-Conservative";
const string CONST_DASH_SPACE_SPACE = "-  ";
const string CONST_CONSERVATIVE_UPPERCASE_SPACE = "Conservative  ";
const string CONST_MODERATE_SPACE = "moderate  ";
const string CONST_LIBERAL_UPPERCASE_SPACE = "Liberal  ";
const string CONST_ELITE_LIBERAL_UPPERCASE_SPACE = "Elite Liberal ";
const string CONST_THREE_CHARACTER_LINE = "ÄÄÄ";
const string CONST_CURRENT_POLITICAL_TRENDS = "CURRENT POLITICAL TRENDS";
const string CONST_LCS_MONTHLY_INTELLIGENCE_REPORT = "LCS MONTHLY INTELLIGENCE REPORT";
//#endif//MONTHLY_CPP
//#endif// INCLUDES_H_INCLUDED
