




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
//#ifdef	ARMOR_CPP
// armor.cpp

#include "../items/itemtype.h"
#include "../items/item.h"
#include "../items/armortype.h"
#include "../items/armor.h"
//own header
#include "../common/stringconversion.h"
//for int stringtobool(std::string)
#include "../common/translateid.h"
// for  int getarmortype


const string CLOSE_BRACKET = "]";
const string OPEN_BRACKET = "[";
const string tag_D = "D";
const string tag_B = "B";
const string tag_X = "X";
const string tag_quality = "quality";
const string tag_false = "false";
const string tag_damaged = "damaged";
const string tag_true = "true";
const string tag_bloody = "bloody";
const string tag_blood = "blood";
const string tag_armor = "armor";
const string ruinedName = "Tattered Rags";

extern vector<ArmorType *> armortype;
//#endif//ARMOR_CPP
//#endif// INCLUDES_H_INCLUDED
