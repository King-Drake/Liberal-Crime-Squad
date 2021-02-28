




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
// augmentation.cpp
#include "augmentation.h"

const string CONSERVATIVE_BUG = "Conservative Swine! (Bug)";
const string CONST_X_SKIN = "Skin";
const string CONST_X_LEGS = "Legs";
const string CONST_X_ARMS = "Arms";
const string CONST_X_BODY = "Body";
const string CONST_X_HEAD = "Head";
const string tag_skin = "skin";
const string tag_effect = "effect";
const string tag_type = "type";
const string tag_name = "name";
const string tag_augmentation = "augmentation";

const string tag_value = "value";
const string tag_attribute = "attribute";

const string tag_legs = "legs";
const string tag_arms = "arms";
const string tag_body = "body";
const string tag_head = "head";

//#endif//AUGMENTATION_CPP
//#endif// INCLUDES_H_INCLUDED
