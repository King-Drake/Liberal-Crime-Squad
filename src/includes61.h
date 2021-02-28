




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
const string CHOOSE_A_LIBERAL_TO = "Choose a Liberal squad member to ";
// haulkidnap.cpp

const string CONST_IS_THE_ONLY_VIABLE_TARGET = " Is The Only Viable Target";
const string CONST_STILL_KIDNAP_Y_N = "Still Kidnap? [Y/N]";
const string CONST_HAULS = " hauls ";
const string CONST_IS_LEFT_TO_BE_CAPTURED = " is left to be captured.";
const string CONST_NOBODY_CAN_CARRY_MARTYR = "Nobody can carry Martyr ";
const string CONST_CAN_NO_LONGER_HANDLE = " can no longer handle ";
const string CONST_X_SOME_WHITESPACE = "                                  ";
const string CONST_THE_HOSTAGE_SHOUTS_FOR_HELP = "The hostage shouts for help!      ";
const string CONST_RELEASE_THEIR_HOSTAGE = "release their hostage.";
const string CONST_NO_HOSTAGES_ARE_BEING_HELD = "No hostages are being held.       ";
const string CONST_X_MUCH_WHITESPACE = "                                                     ";
const string CONST_ALL_OF_THE_TARGETS_ARE_TOO_DANGEROUS = "All of the targets are too dangerous.                ";
const string CONST_KIDNAP_WHOM = "Kidnap whom?";
const string CONST_DO_THE_JOB = "do the job.";
const string CONST_NO_ONE_CAN_DO_THE_JOB = "No one can do the job.            ";
const string CONST_X_IS_CAPTURED = " is captured.";
const string CONST_X_IS_RECAPTURED = " is recaptured.";
const string CONST_A_HOSTAGE_ESCAPES = "A hostage escapes!";
const string CONST_IS_CAPTURED = " is captured";
const string CONST_IS_RECAPTURED = " is recaptured";
const string CONST_AND_A_HOSTAGE_IS_FREED = " and a hostage is freed";
const string CONST_AND_SAYS = "and says, ";
const string CONST_X_THE_ = " the ";
const string CONST_SHOWS = " shows ";
const string CONST_WRITHES_AWAY = " writhes away!";
const string CONST_BUT = "but ";
const string CONST_GRABS_AT = " grabs at ";
const string CONST_IS_STRUGGLING_AND_SCREAMING = " is struggling and screaming!";
//const string CONST_EXCLAMATION_POINT = "!";
const string CONST_SNATCHES = " snatches ";
const string CONST_PLEASE_BE_COOL = "\"[Please], be cool.\"";
const string CONST_BITCH_BE_COOL = "\"Bitch, be cool.\"";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../sitemode/advance.h"
// for creatureadvance
#include "../sitemode/stealth.h"
#include "../sitemode/sitedisplay.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for printparty
//// #include "../common/commonactions.h"
void criminalizeparty(short crime);
//// #include "../common/commonactionsCreature.h"
void removesquadinfo(DeprecatedCreature &cr);
/* roll on the kidnap attempt and show the results */
#include "set_color_support.h"
#include "cursesAlternative.h"

void conservatise(const int cr);

void capturecreature(DeprecatedCreature &t);
vector<NameAndAlignment> getEncounterNameAndAlignment();

bool isThereASiteAlarm();
void setSiteAlarmOne();

extern short offended_amradio;
extern short offended_cablenews;
extern int sitecrime;
extern short party_status;

extern short sitealarmtimer;
extern Deprecatedsquadst *activesquad;
extern DeprecatedCreature encounter[ENCMAX];
extern short lawList[LAWNUM];

extern short mode;
extern Log gamelog;

void enemyattack();
void delenc(const short e, const char loot);
void makeloot(DeprecatedCreature &cr);
//#endif//HAULKIDNAP_CPP
//#endif// INCLUDES_H_INCLUDED
