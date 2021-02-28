




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

#include "bigListEnumTags.h"
// augmenttype.cpp

#include "augmentation.h"
#include "augmenttype.h"
//own header
#include "../log/log.h"
// for log
#include "../common/stringconversion.h"

const string LACKS_IDNAME_LOWERCASE = " lacks idname.";
const string AUGMENT_TYPE_SPACE = "Augment type ";
const string LACKS_IDNAME = "LACKS IDNAME ";

const string tag_difficulty = "difficulty";
const string tag_cost = "cost";
const string tag_min_age = "min_age";
const string tag_max_age = "max_age";
const string tag_description = "description";
const string tag_effect = "effect";
const string tag_attribute = "attribute";
const string tag_type = "type";
const string tag_name = "name";
const string tag_idname = "idname";
const string tag_id = "id";


map<string, int> augmentTags = {
	map<string, int>::value_type(tag_name, ENUM_tag_name),
	map<string, int>::value_type(tag_type, ENUM_tag_type),
	map<string, int>::value_type(tag_attribute, ENUM_tag_attribute),
	map<string, int>::value_type(tag_effect, ENUM_tag_effect),
	map<string, int>::value_type(tag_description, ENUM_tag_description),
	map<string, int>::value_type(tag_max_age, ENUM_tag_max_age),
	map<string, int>::value_type(tag_min_age, ENUM_tag_min_age),
	map<string, int>::value_type(tag_cost, ENUM_tag_cost),
	map<string, int>::value_type(tag_difficulty, ENUM_tag_difficulty),
};
extern Log xmllog;
//#endif//AUGMENTTYPE_CPP
//#endif// INCLUDES_H_INCLUDED
