




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

// getnames.cpp

#include "../creature/newcreature.h"
#include "../cursesAlternative.h"
#include "../customMaps.h"
extern short lawList[LAWNUM];

const string moderateLC = "moderate";
const string BUGGY_STRING = "Buggy";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string names = "names\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_GETMONTH_TXT = "getMonth.txt";
const string CONST_CITY_NAMES_TXT = "city_names.txt";
//const string CONST_SOFTWARE_BUGS = "Software Bugs";
const string CONST_BUGGY_SOFTWARE = "Buggy Software";
const string CONST_BUGS = "bugs";
const string CONST_X_ELITE_LIBERAL = "Elite Liberal";
const string CONST_LIBERAL_GUARDIAN = "Liberal Guardian";
const string CONST_URBAN_COMMANDO = "Urban Commando";
const string CONST_REVOLUTIONARY = "Revolutionary";
const string CONST_SOCIALIST_THREAT = "Socialist Threat";
const string CONST_ACTIVIST = "Activist";
const string CONST_CIVILIAN = "Civilian";
const string CONST_PUNK = "Punk";
const string CONST_SOCIETY_S_DREGS = "Society's Dregs";
const string CONST_DAMN_WORTHLESS = "Damn Worthless";
const string CONST_DARN_WORTHLESS = "[Darn] Worthless";
const string CONST_PEACE_PRIZE_WINNER = "Peace Prize Winner";
const string CONST_PEACEMAKER = "Peacemaker";
const string CONST_GREAT_PERSON = "Great Person";
const string CONST_UPSTANDING_CITIZEN = "Upstanding Citizen";
const string CONST_RESPECTED = "Respected";
const string CONST_HARD_WORKING = "Hard Working";
const string CONST_NON_LIBERAL = "Non-Liberal";
const string CONST_NON_LIBERAL_PUNK = "Non-Liberal Punk";
const string CONST_EVIL_INCARNATE = "Evil Incarnate";
const string CONST_ARCH_CONSERVATIVE = "Arch-Conservative";
const string CONST_INSANE_VIGILANTE = "Insane Vigilante";
const string CONST_HEARTLESS_BASTARD = "Heartless Bastard";
const string CONST_HEARTLESS_JERK = "Heartless [Jerk]";
const string CONST_STUBBORN_AS_HELL = "Stubborn as Hell";
const string CONST_STUBBORN_AS_HECK = "Stubborn as [Heck]";
const string CONST_WRONG_THINKER = "Wrong-Thinker";
const string CONST_MINDLESS_CONSERVATIVE = "Mindless Conservative";
const string CONST_CONSERVATIVE_PUNK = "Conservative Punk";
const string CONST_CONSERVATIVE_DREGS = "Conservative Dregs";
//#endif//GETNAMES_CPP
//#endif// INCLUDES_H_INCLUDED
