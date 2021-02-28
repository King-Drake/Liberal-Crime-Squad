




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
/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);
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
//#ifdef	WEAPON_CPP
// weapon.cpp

#include "../creature/creatureEnums.h"
#include "../items/itemtype.h"
#include "../items/item.h"
#include "../items/cliptype.h"
#include "../items/clip.h"
#include "../items/weapontype.h"
#include "../items/weapon.h"

#include "../common/translateid.h"
// for getweapontype

extern vector<WeaponType *> weapontype;

const string CONST_CLOSE_PARENTHESIS = ")";
const string CONST_SPACE_OPEN_PARENTHESIS = " (";

const string tag_ammo = "ammo";
const string tag_loaded_cliptype = "loaded_cliptype";
const string tag_weapon = "weapon";

//#endif//WEAPON_CPP
//#endif// INCLUDES_H_INCLUDED
