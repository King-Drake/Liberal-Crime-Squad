




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
#include "creatureConstants.h"
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

// stringconversion.cpp

#include "../creature/creatureEnums.h"

extern map<string, short> getCreatureEnumFromString;

const string NONE = "NONE";
const string tag_heavyweapons = "heavyweapons";
const string tag_dodge = "dodge";
const string tag_firstaid = "firstaid";
const string tag_seduction = "seduction";
const string tag_streetsense = "streetsense";
const string tag_teaching = "teaching";
const string tag_stealth = "stealth";
const string tag_business = "business";
const string tag_science = "science";
const string tag_religion = "religion";
const string tag_art = "art";
const string tag_music = "music";
const string tag_writing = "writing";
const string tag_driving = "driving";
const string tag_tailoring = "tailoring";
const string tag_computers = "computers";
const string tag_disguise = "disguise";
const string tag_security = "security";
const string tag_law = "law";
const string tag_psychology = "psychology";
const string tag_persuasion = "persuasion";
const string tag_shotgun = "shotgun";
const string tag_smg = "smg";
const string tag_rifle = "rifle";
const string tag_pistol = "pistol";
const string tag_throwing = "throwing";
const string tag_axe = "axe";
const string tag_club = "club";
const string tag_sword = "sword";
const string tag_knife = "knife";
const string tag_handtohand = "handtohand";
const string tag_CLEAN = "CLEAN";
const string tag_NASTY = "NASTY";
const string tag_RANDOM = "RANDOM";
const string tag_FEMALE_BIAS = "FEMALE BIAS";
const string tag_FEMALE = "FEMALE";
const string tag_MALE_BIAS = "MALE BIAS";
const string tag_MALE = "MALE";
const string tag_GENDER_WHITEMALEPATRIARCH = "GENDER_WHITEMALEPATRIARCH";
const string tag_NEUTRAL = "NEUTRAL";
const string tag_heart = "heart";
const string tag_charisma = "charisma";
const string tag_health = "health";
const string tag_agility = "agility";
const string tag_wisdom = "wisdom";
const string tag_intelligence = "intelligence";
const string tag_strength = "strength";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string tag_no = "no";
const string tag_false = "false";
const string tag_0 = "0";
const string tag_off = "off";
const string tag_on = "on";
const string tag_yes = "yes";
const string tag_1 = "1";
const string tag_true = "true";
//#endif//STRINGCONVERSION_CPP
//#endif// INCLUDES_H_INCLUDED
