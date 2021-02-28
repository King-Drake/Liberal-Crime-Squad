




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

//#include "includesSDS.h"
const string spaceDashSpace = " - ";
const string CHOOSE_A_LIBERAL_TO = "Choose a Liberal squad member to ";
//#include "includesDeprecatedB.h"
// baseactions.cpp


#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
//#include "../cursesgraphics.h"

#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "../common/getnames.h"
void enter_name(int, int, char*, int, const char*);
#include "../common/commondisplay.h"
// for void printparty(void)
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"

int getkey_cap_alt();
int lenVehiclePool();
int getCarID(const int l);
string getCarFullname(const int l);

extern char slogan[SLOGAN_LEN];
extern Deprecatedsquadst *activesquad;
extern string slogan_str;
extern vector<string> default_slogans;
extern short party_status;

const string VEHICLE_PARAGRAPH_TXT = "vehicleParagraph.txt";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string BE_A_PASSENGER = "be a passenger.";
const string DRIVE_IT = "drive it.";
const string CHOOSING_THE_RIGHT_LIBERAL_VEHICLE = "Choosing the Right Liberal Vehicle";
const string IN_SPOT_SPACE = " in Spot ";
const string CHOSE_SQUAD_MEMBER_TO_REPLACE = "Choose squad member to replace ";
const string CHOOSE_SQUAD_MEMBER_TO_MOVE = "Choose squad member to move";
const string MANY_SPACES_SOMETHING = "                                                                                          ";
const string WHAT_IS_YOUR_NEW_SLOGAN = "What is your new slogan?";

//#endif//BASEACTIONS_CPP
//#endif// INCLUDES_H_INCLUDED
