




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
// commonactions.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
//#include "../pdcurses/curses.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for makedelimeter
#include "../title/highscore.h"       
//for void savehighscore(char endtype)
#include "../politics/politics.h"
//for int publicmood(int l)
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
//extern string singleSpace;
//extern string spaceDashSpace;
//extern string singleDot;

const string enterDash = "Enter - ";
const string selectA = "Press a Letter to select a ";
const string selectAn = "Press a Letter to select an ";

const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string HARMFUL_SPEECH = "harmful speech";
const string CONST_X_MONTH = "month";
const string CONST_X_MONTHS = "months";
const string FOR_SPACE = " for ";
const string WILL_BE_AT_SPACE = " will be at ";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string METHOD_OF_SORTING_TXT = "methodOfSorting.txt";
const string CHOOSE_HOW_TO_SORT_LIST = "Choose how to sort list of ";
const string DOLLARSIGN = "$";

short getCurrentSite();
extern short mode;
extern Deprecatedsquadst *activesquad;
extern vector<Deprecatedsquadst *> squad;
extern short activesortingchoice[SORTINGCHOICENUM];
extern class Ledger ledger;
extern Log gamelog;

//#endif//COMMONACTIONS_CPP
//#endif// INCLUDES_H_INCLUDED
