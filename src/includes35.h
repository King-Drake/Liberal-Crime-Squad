




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
//#ifdef	ARMORTYPE_CPP

#include "bigListEnumTags.h"
// armortype.cpp

enum Bodyparts
{
	BODYPART_HEAD,
	BODYPART_BODY,
	BODYPART_ARM_RIGHT,
	BODYPART_ARM_LEFT,
	BODYPART_LEG_RIGHT,
	BODYPART_LEG_LEFT,
	BODYPARTNUM
};

#include "../creature/creatureEnums.h"
//#include "../items/item.h"
#include "../items/itemtype.h"
//#include "../items/armor.h"
#include "../items/armortype.h"
//own header
#include "../common/stringconversion.h"
//for stringtobool

const string CONST_armortypeUNDEF = "UNDEF";
const string UNKNOWN_ELEMENT_FOR_ARMOR_TYPE = "Unknown element for armor type ";
const string COLON_INTERROGATION_ST = "::InterrogationST: ";
const string COLON_ARMOR = "::armor: ";
const string COLON_CONCEAL_FACE = "::body_covering::conceal_face: ";
const string INVALID_BOOLEAN_FOR_ARMOR = "Invalid boolean value for armor type ";
const string COLON_LEG_COVERING = "::body_covering::legs: ";
const string COLON_ARM_COVERING = "::body_covering::arms: ";
const string COLON_HEAD_COVERING = "::body_covering::head: ";
const string COLON_BODY_COVERING = "::body_covering::body: ";
const string COLON_FIREPROTECTION = "::armor::fireprotection: ";
const string COLON_DEATHSQUAD_LEGALITY = "::deathsquad_legality: ";

const string tag_durability = "durability";
const string tag_qualitylevels = "qualitylevels";
const string tag_quality = "quality";
const string tag_description = "description";
const string tag_surprise = "surprise";
const string tag_mask = "mask";
const string tag_stealth = "stealth";
const string tag_stealth_value = "stealth_value";
const string tag_conceal_weapon_size = "conceal_weapon_size";
const string tag_professionalism = "professionalism";
const string tag_drugbonus = "drugbonus";
const string tag_assaultbonus = "assaultbonus";
const string tag_basepower = "basepower";
const string tag_base = "base";
const string tag_interrogation = "interrogation";
const string tag_shortname = "shortname";
const string tag_conceals_face = "conceals_face";
const string tag_legs = "legs";
const string tag_arms = "arms";
const string tag_head = "head";
const string tag_body = "body";
const string tag_body_covering = "body_covering";
const string tag_fire = "fire";
const string tag_fireprotection = "fireprotection";
const string tag_limbs = "limbs";
const string tag_armor = "armor";
const string tag_can_get_damaged = "can_get_damaged";
const string tag_can_get_bloody = "can_get_bloody";
const string tag_deathsquad_legality = "deathsquad_legality";
const string tag_make_price = "make_price";
const string tag_make_difficulty = "make_difficulty";

map<string, int> armorTypeInitTags = {
	map<string, int>::value_type(tag_make_difficulty, ENUM_tag_make_difficulty),
	map<string, int>::value_type(tag_make_price, ENUM_tag_make_price),
	map<string, int>::value_type(tag_deathsquad_legality, ENUM_tag_deathsquad_legality),
	map<string, int>::value_type(tag_can_get_bloody, ENUM_tag_can_get_bloody),
	map<string, int>::value_type(tag_can_get_damaged, ENUM_tag_can_get_damaged),
	map<string, int>::value_type(tag_armor, ENUM_tag_armor),
	map<string, int>::value_type(tag_body_covering, ENUM_tag_body_covering),
	map<string, int>::value_type(tag_shortname, ENUM_tag_shortname),
	map<string, int>::value_type(tag_interrogation, ENUM_tag_interrogation),
	map<string, int>::value_type(tag_professionalism, ENUM_tag_professionalism),
	map<string, int>::value_type(tag_conceal_weapon_size, ENUM_tag_conceal_weapon_size),
	map<string, int>::value_type(tag_stealth_value, ENUM_tag_stealth_value),
	map<string, int>::value_type(tag_mask, ENUM_tag_mask),
	map<string, int>::value_type(tag_surprise, ENUM_tag_surprise),
	map<string, int>::value_type(tag_description, ENUM_tag_description),
	map<string, int>::value_type(tag_qualitylevels, ENUM_tag_qualitylevels),
	map<string, int>::value_type(tag_durability, ENUM_tag_durability),
};
extern int year;
//#endif//ARMORTYPE_CPP
//#endif// INCLUDES_H_INCLUDED
