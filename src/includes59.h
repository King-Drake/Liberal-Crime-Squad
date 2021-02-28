




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
string skill_enum_to_string(int skill_type);
// commondisplay.cpp
#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../sitemode/stealth.h"
#include "../common/getnames.h"
// for getmonth
#include "../common/translateid.h"
// for  int getcar(int)
#include "../common/commonactionsCreature.h"
// for void sortliberals(std::vector<Creature *>&,short,bool)
#include "../daily/siege.h"
// for statebrokenlaws(cr);
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"

std::string gettitle(const int align, const int juice);
bool isThereNoActivesquad();
bool isThereASiteAlarm();
void makedelimiter(int y = 8, int x = 0);
void printcreatureinfo(DeprecatedCreature *cr, unsigned char knowledge = 255);
void set_color_for_armor(const Armor armor);
void setColorForArmor(const Armor ar);
void statebrokenlaws(CreatureJustice cr, const int flag);

extern bool mapshowing;
extern char showcarprefs;
extern Deprecatedsquadst *activesquad;
extern int day;
extern int month;
extern int year;
extern short mode;
extern short party_status;
extern short sitealarmtimer;



map<int, map<bool, ColorSetup> > alignmentColors = {
	// Liberal activism
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_ARCHCONSERVATIVE,{ map<bool, ColorSetup>::value_type(true, RED_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_CONSERVATIVE,{ map<bool, ColorSetup>::value_type(true, MAGENTA_ON_BLACK_BRIGHT), map<bool, ColorSetup>::value_type(false, RED_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_MODERATE,{ map<bool, ColorSetup>::value_type(true, YELLOW_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_LIBERAL,{ map<bool, ColorSetup>::value_type(true, CYAN_ON_BLACK_BRIGHT), map<bool, ColorSetup>::value_type(false, GREEN_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_ELITELIBERAL,{ map<bool, ColorSetup>::value_type(true, GREEN_ON_BLACK_BRIGHT) }),
	map<int,  map<bool, ColorSetup> >::value_type(ALIGN_STALINIST,{ map<bool, ColorSetup>::value_type(true, RED_ON_BLACK_BRIGHT) }),
};
map<int, ColorSetup> activityColors = {
	// Liberal activism
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_LIBERAL, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_TROUBLE, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_GRAFFITI, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_DOS_ATTACKS, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_HACKING, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_WRITE_LETTERS, GREEN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_WRITE_GUARDIAN, GREEN_ON_BLACK_BRIGHT),
	// Recruitment
	map<int, ColorSetup>::value_type(ACTIVITY_RECRUITING, GREEN_ON_BLACK),
	// Less exciting liberal activities
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_SPY, BLUE_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_COMMUNITYSERVICE, BLUE_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_POLLS, BLUE_ON_BLACK_BRIGHT),
	// Stealing things
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_STEAL, CYAN_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITY_WHEELCHAIR, CYAN_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITY_STEALCARS, CYAN_ON_BLACK),
	// Illegal fundraising
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_EMBEZZLE, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_DRUGS, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_PROSTITUTION, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_CCFRAUD, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_DOS_RACKET, RED_ON_BLACK_BRIGHT),
	// Legal fundraising
	map<int, ColorSetup>::value_type(ACTIVITY_DONATIONS, CYAN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_TSHIRTS, CYAN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_ART, CYAN_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_SELL_MUSIC, CYAN_ON_BLACK_BRIGHT),
	// Clothing/garment stuff
	map<int, ColorSetup>::value_type(ACTIVITY_REPAIR_ARMOR, CYAN_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITY_MAKE_ARMOR, CYAN_ON_BLACK),
	// Teaching
	map<int, ColorSetup>::value_type(ACTIVITY_TEACH_POLITICS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_TEACH_FIGHTING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_TEACH_COVERT, MAGENTA_ON_BLACK_BRIGHT),
	//and studying
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_DEBATING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_MARTIAL_ARTS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_DRIVING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_PSYCHOLOGY, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_FIRST_AID, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_LAW, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_DISGUISE, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_SCIENCE, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_BUSINESS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_GYMNASTICS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_ART, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_MUSIC, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_TEACHING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_WRITING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_LOCKSMITHING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_COMPUTERS, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_FENCING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_WEAVING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_RELIGION, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_CLUB, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_STREETSENSE, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_THROWING, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_STEALTH, MAGENTA_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_STUDY_SEDUCTION, MAGENTA_ON_BLACK_BRIGHT),
	// Interrogating
	map<int, ColorSetup>::value_type(ACTIVITY_HOSTAGETENDING, YELLOW_ON_BLACK_BRIGHT),
	// Dealing with your injuries
	map<int, ColorSetup>::value_type(ACTIVITY_CLINIC, RED_ON_BLACK),
	// Doing something Conservative
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_CONSERVATIVE, RED_ON_BLACK_BRIGHT),
	// Dealing with the dead
	map<int, ColorSetup>::value_type(ACTIVITY_BURY, BLACK_ON_BLACK_BRIGHT),
	// Nothing terribly important
	map<int, ColorSetup>::value_type(ACTIVITY_HEAL, WHITE_ON_BLACK),// Identical to none in practice
	map<int, ColorSetup>::value_type(ACTIVITY_NONE, WHITE_ON_BLACK),
	map<int, ColorSetup>::value_type(ACTIVITYNUM, WHITE_ON_BLACK),
	// Going somewhere
	map<int, ColorSetup>::value_type(ACTIVITY_VISIT, YELLOW_ON_BLACK_BRIGHT),
	// Quitting being a sleeper to join the LCS
	map<int, ColorSetup>::value_type(ACTIVITY_SLEEPER_JOINLCS, RED_ON_BLACK_BRIGHT),
	map<int, ColorSetup>::value_type(ACTIVITY_AUGMENT, BLUE_ON_BLACK_BRIGHT),
};
/* checks if a creature's weapon is suspicious or illegal */
char weaponcheck(const DeprecatedCreature &cr, bool metaldetect = false);
/* checks if a creature's uniform is appropriate to the location */
char hasdisguise(const DeprecatedCreature &cr);
string getVehicleShortname(int i);

vector<string> printSpecialWounds(const char special[SPECIALWOUNDNUM]);
