




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
#include "includesSDS2.h"
string showXmlSkill(int skill_, int value_);
string showXmlAttribute(int attribute_, int value_);
//#include "includesDeprecatedB.h"
string skill_enum_to_string(int skill_type);
// creature.cpp

#include "../creature/creature.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../sitemode/stealth.h"
// for hasdisguise
//#include "../common/stringconversion.h"
string attribute_enum_to_string(int attribute);
#include "../common/translateid.h"
// for  int getweapontype(int )
//#include "../politics/politics.h"
/* politics -- promotes the Vice President to President, and replaces VP */
void promoteVP();
//only use here. --Schmel924
#include "../combat/chaseCreature.h"
//for Vehicle* getChaseVehicle(const Creature &c);
		//hmm --Schmel924
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"

const string LETTER_Z = "z";

const string LETTER_X = "x";

const string SLASH_MARK = "/";
const string CONST_X_SELVES = "selves";
const string THEM_LOWERCASE = "them";
const string HER_LOWERCASE = "her";
const string THEMSELF_LOWERCASE = "themself";
const string HERS_LOWERCASE = "hers";
const string HE_AND_SHE = "heANDshe";
const string CONST_X_QUESTION_MARK = "?";
const string COMMA_AMBIGUOUS = ", Ambiguous";
const string CONST_X_FEMALE = ", Female";
const string CONST_X_MALE = ", Male";
const string VERY_OLD = "Very Old";
const string EIGHTIES = "80s";
const string SEVENTIES = "70s";
const string SIXTIES = "60s";
const string FIFTIES = "50s";
const string FORTIES = "40s";
const string THIRTIES = "30s";
const string TWENTIES = "20s";
const string SPACE_PARENTHESIS = " (";
const string PARENTHESIS_QUESTION = " (?)";
const string CONST_X_NONE = "None";
const string ZERO_OVER = " (0/";
const string ONE_OVER = " (1/";
const string CONST_X_SELF = "self";
const string XEMSELF_LOWERCASE = "xemself";
const string CONST_X_XEM = "Xem";
const string CONST_X_HER = "Her";
const string CONST_X_HIM = "Him";
const string CONST_X_S = "s";
const string CONST_X_XYRS = "xyrs";
const string CONST_X_XYR = "Xyr";
const string CONST_X_HIS = "His";
const string XE_LOWERCASE = "xe";
const string XE_SPACE = "Xe";
const string SHE_SPACE = "She";
const string HE_SPACE = "He";
const string CONST_X_PRESIDENT_ = "President ";
const string CCS_HEAVY = "CCS Heavy";
const string SOLDIER = "Soldier";
const string ELITE_SECURITY = "Elite Security";
const string ENLIGHTENED_JUDGE = "Enlightened Judge";
const string NEW_UNION_WORKER = "New Union Worker";
const string JADED_LIBERAL_JUDGE = "Jaded Liberal Judge";
const string EX_UNION_WORKER = "Ex-Union Worker";
const string IMPOSSIBLE = ", IMPOSSIBLE";
const string DIFFICULTY = ", Difficulty ";
const string SKILL_CHECK = " SkillCheck(";
const string OUTCOME_OF_SPACE = ", Outcome of ";
const string ADJUSTED_ATTRIBUTE_VALUE = "Adjusted Attribute Value ";
const string AUTOMATIC_FAILURE = "automatic failure";
const string SKILL_VALUE = ", Skill Value ";
const string SKILL_ROLL = " SkillRoll(";
const string ILLEGAL_SKILL_ROLL = "-=ILLEGAL SKILL ROLL=-";
const string ATTRIBUTE_CHECK = " AttributeCheck(";
const string ATTRIBUTE_LEVEL = ", Attribute Level ";
const string ATTRIBUTE_ROLL = " AttributeRoll(";
const string PERCENT_F = "%f";
const string SCRUFFY_UNNAMED_JANITOR = "ScruffyUnnamedJanitor";
const string CONST_CREATURE_WORKER_JANITOR = "CREATURE_WORKER_JANITOR";
const string CCS_COVERNAME_OTHER_TXT = "ccs_covername_other.txt";
const string CCS_COVERNAME_SHOTGUN_TXT = "ccs_covername_shotgun.txt";
const string HE_LOWERCASE = "he";
const string SHE_LOWERCASE = "she";
const string HIS_LOWERCASE = "his";
const string CONST_X_HER_LOWERCASE = "her";
const string CONST_X_XYR_LOWERCASE = "xyr";
const string HIM_LOWERCASE = "him";
const string CONST_X_XEM_LOWERCASE = "xem";

const string tag_value = "value";
const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_NONE = "ARMOR_NONE";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_NONE = "WEAPON_NONE";
const string tag_Pres = "Pres";
const string tag_Pres_state = "Pres_state";
const string tag_Pres_ID = "Pres_ID";
const string tag_CEO = "CEO";
const string tag_CEO_state = "CEO_state";
const string tag_CEO_ID = "CEO_ID";
const string tag_uniquecreatures = "uniquecreatures";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_ARMOR_HEAVYARMOR = "ARMOR_HEAVYARMOR";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_reports_to_police = "reports_to_police";
const string tag_kidnap_resistant = "kidnap_resistant";
const string tag_talkreceptive = "talkreceptive";
const string tag_seethroughstealth = "seethroughstealth";
const string tag_seethroughdisguise = "seethroughdisguise";
const string tag_dontname = "dontname";
const string tag_flag = "flag";
const string tag_pref_is_driver = "pref_is_driver";
const string tag_pref_carid = "pref_carid";
const string tag_is_driver = "is_driver";
const string tag_carid = "carid";
const string tag_arg = "arg";
const string tag_arg2 = "arg2";
const string tag_type = "type";
const string tag_activity = "activity";
const string tag_base = "base";
const string tag_cantbluff = "cantbluff";
const string tag_worklocation = "worklocation";
const string tag_location = "location";
const string tag_crimes_suspected = "crimes_suspected";
const string tag_special = "special";
const string tag_blood = "blood";
const string tag_wound = "wound";
const string tag_income = "income";
const string tag_juice = "juice";
const string tag_money = "money";
const string tag_has_thrown_weapon = "has_thrown_weapon";
const string tag_stunned = "stunned";
const string tag_forceinc = "forceinc";
const string tag_meetings = "meetings";
const string tag_hireid = "hireid";
const string tag_id = "id";
const string tag_deathdays = "deathdays";
const string tag_joindays = "joindays";
const string tag_deathpenalty = "deathpenalty";
const string tag_confessions = "confessions";
const string tag_sentence = "sentence";
const string tag_prisoner = "prisoner";
const string tag_trainingsubject = "trainingsubject";
const string tag_trainingtime = "trainingtime";
const string tag_hiding = "hiding";
const string tag_dating = "dating";
const string tag_clinic = "clinic";
const string tag_specialattack = "specialattack";
const string tag_animalgloss = "animalgloss";
const string tag_infiltration = "infiltration";
const string tag_type_idname = "type_idname";
const string tag_alive = "alive";
const string tag_align = "align";
const string tag_exists = "exists";
const string tag_birthday_day = "birthday_day";
const string tag_birthday_month = "birthday_month";
const string tag_age = "age";
const string tag_squadid = "squadid";
const string tag_gender = "gender";
const string tag_gender_liberal = "gender_liberal";
const string tag_gender_conservative = "gender_conservative";
const string tag_propername = "propername";
const string tag_name = "name";
const string tag_skill_experience = "skill_experience";
const string tag_skill = "skill";
const string tag_creature = "creature";
const string tag_clip = "clip";
const string tag_augmentation = "augmentation";
const string tag_armor = "armor";
const string tag_weapon = "weapon";
const string tag_attribute = "attribute";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string creature = "creature\\";

vector<string> ccs_covername_shotgun;
vector<string> ccs_covername_other;
vector<file_and_text_collection> creature_text_file_collection = {
	/*creature.cpp*/
	customText(&ccs_covername_shotgun, creature + CCS_COVERNAME_SHOTGUN_TXT),
	customText(&ccs_covername_other, creature + CCS_COVERNAME_OTHER_TXT),
};

char hasdisguise(const DeprecatedCreature &cr);

extern Log gamelog;
extern bool SHOWMECHANICS;
extern bool ZEROMORAL;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char oldPresidentName[POLITICIAN_NAMELEN];
extern short exec[EXECNUM];
extern long curcreatureid;
extern UniqueCreatures uniqueCreatures;

//#endif//CREATURE_CPP
//#endif// INCLUDES_H_INCLUDED
