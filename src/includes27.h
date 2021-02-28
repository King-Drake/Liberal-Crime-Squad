




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
#include "includesSDS.h"
//#include "includesDeprecatedB.h"
//#ifdef	WEAPONTYPE_CPP

#include "bigListEnumTags.h"
// weapontype.cpp
#include "../creature/creatureEnums.h"
#include "../items/itemtype.h"
#include "../items/cliptype.h"
#include "../items/weapontype.h"

#include "../common/stringconversion.h"

extern int year;
extern short lawList[LAWNUM];

const string CONST_tag_striking = "striking";
const string CONST_UNDEF = "UNDEF";
const string CONST_ASSAULTS = "assaults";

const string tag_chance_causes_debris = "chance_causes_debris";
const string tag_chance = "chance";
const string tag_fire = "fire";
const string tag_severtype = "severtype";
const string tag_fixed_damage = "fixed_damage";
const string tag_random_damage = "random_damage";
const string tag_hits_required = "hits_required";
const string tag_critical = "critical";
const string tag_no = "no";
const string tag_no_DR_for_limbs_chance = "no_damage_reduction_for_limbs_chance";
const string tag_armor = "armor";
const string tag_armorpiercing = "armorpiercing";
const string tag_damages_armor = "damages_armor";
const string tag_bleeding = "bleeding";
const string tag_shoots = "shoots";
const string tag_burns = "burns";
const string tag_cuts = "cuts";
const string tag_tears = "tears";
const string tag_bruises = "bruises";
const string tag_strength = "strength";
const string tag_strength_max = "strength_max";
const string tag_strength_min = "strength_min";
const string tag_successive_attacks_difficulty = "successive_attacks_difficulty";
const string tag_number_attacks = "number_attacks";
const string tag_accuracy_bonus = "accuracy_bonus";
const string tag_skill = "skill";
const string tag_hit_punctuation = "hit_punctuation";
const string tag_always_describe_hit = "always_describe_hit";
const string tag_hit_description = "hit_description";
const string tag_attack = "attack";
const string tag_attack_description = "attack_description";
const string tag_ammotype = "ammotype";
const string tag_ammo = "ammo";
const string tag_can_backstab = "can_backstab";
const string tag_thrown = "thrown";
const string tag_ranged = "ranged";
const string tag_priority = "priority";
const string tag_size = "size";
const string tag_suspicious = "suspicious";
const string tag_auto_break_locks = "auto_break_locks";
const string tag_bashstrengthmod = "bashstrengthmod";
const string tag_legality = "legality";
const string tag_graffiti = "graffiti";
const string tag_instrument = "instrument";
const string tag_music = "music";
const string tag_musical_attack = "musical_attack";
const string tag_protects_against_kidnapping = "protects_against_kidnapping";
const string tag_can_threaten_hostages = "can_threaten_hostages";
const string tag_threatening = "threatening";
const string tag_can_take_hostages = "can_take_hostages";
const string tag_shortname_future = "shortname_future";
const string tag_shortname = "shortname";
const string tag_shortname_future_sub_2 = "shortname_future_sub_2";
const string tag_shortname_future_sub_1 = "shortname_future_sub_1";
const string tag_shortname_sub_2 = "shortname_sub_2";
const string tag_shortname_sub_1 = "shortname_sub_1";
const string tag_name_future = "name_future";
const string tag_name = "name";
const string tag_name_future_sub_2 = "name_future_sub_2";
const string tag_name_future_sub_1 = "name_future_sub_1";
const string tag_name_sub_2 = "name_sub_2";
const string tag_name_sub_1 = "name_sub_1";
//#endif//WEAPONTYPE_CPP
//#endif// INCLUDES_H_INCLUDED
