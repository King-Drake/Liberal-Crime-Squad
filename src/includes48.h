




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

//#include "includesDeprecatedB.h"

#include "bigListEnumTags.h"
// creaturetype.cpp

const string NONE = "NONE";
const string CONST_COLON = ": ";
const string CONST_X_LACKS_IDNAME = " lacks idname.";
const string CONST_X_COMMA_SPACE = ", ";
const string CONST_X_IN_ = " in ";
const string FIREMAN = "Fireman";
const string CAR_SALESMAN = "Car Salesman";
const string MIGRANT_WORKER = "Migrant Worker";
const string CUSTODIAN = "Custodian";
const string CONST_X_SLAVE = "Slave";
const string TYPE_NAME_NOT_DEFINED = "type_name not defined for ";
const string UNKNOWN_ELEMENT = "Unknown element for ";
const string INVALID_ARMORTYPE = "Invalid armor type for ";
const string UNKNOWN_SKILL = "Unknown skill for ";
const string INVALID_GENDER = "Invalid gender for ";
const string UNKNOWN_ATTRIBUTE = "Unknown attribute in ";
const string INVALID_ALIGNMENT = "Invalid alignment for ";
const string CREATURE_TYPE = "Creature type ";
const string CONST_X_LACKS_IDNAME__ALLCAPS = "LACKS IDNAME ";
const string INVALID_CLIP_TYPE = "Invalid clip type for ";
const string CAN_NOT_BE_USED_BY = "can not be used by ";
const string IN_SPACE = "In ";
const string INVALID_WEAPON_TYPE = "Invalid weapon type for ";
const string UNKNOWN_ELEMENT_FOR_WEAPON = "Unknown element for weapon in ";
const string INVALID_INTERVAL = "Invalid interval for ";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_NONE = "ARMOR_NONE";
const string tag_CLIP_45 = "CLIP_45";
const string tag_CLIP = "CLIP";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_SEMIPISTOL_45 = "WEAPON_SEMIPISTOL_45";
const string tag_CLIP_9 = "CLIP_9";
const string tag_WEAPON_SEMIPISTOL_9MM = "WEAPON_SEMIPISTOL_9MM";
const string tag_CLIP_38 = "CLIP_38";
const string tag_WEAPON_REVOLVER_38 = "WEAPON_REVOLVER_38";
const string tag_WEAPON_NONE = "WEAPON_NONE";
const string tag_CIVILIAN = "CIVILIAN";
const string tag_type = "type";
const string tag_type_name = "type_name";
const string tag_encounter_name = "encounter_name";
const string tag_creature = "creature";
const string tag_weapon = "weapon";
const string tag_armor = "armor";
const string tag_skills = "skills";
const string tag_skill = "skill";
const string tag_money = "money";
const string tag_infiltration = "infiltration";
const string tag_gender = "gender";
const string tag_juice = "juice";
const string tag_attributes = "attributes";
const string tag_attribute = "attribute";
const string tag_attribute_points = "attribute_points";
const string tag_SENIOR = "SENIOR";
const string tag_MI = "MI";
const string tag_MIDDLEAGED = "MIDDLEAGED";
const string tag_GRADUATE = "GRADUATE";
const string tag_MATURE = "MATURE";
const string tag_YOUNGADULT = "YOUNGADULT";
const string tag_TEENAGER = "TEENAGER";
const string tag_CHILD = "CHILD";
const string tag_CHI = "CHI";
const string tag_D = "D";
const string tag_DOGYEARS = "DOGYEARS";
const string tag_age = "age";
const string tag_CONSERVATIVE = "CONSERVATIVE";
const string tag_MODERATE = "MODERATE";
const string tag_LIBERAL = "LIBERAL";
const string tag_PUBLIC_MOOD = "PUBLIC MOOD";
const string tag_align = "align";
const string tag_alignment = "alignment";
const string tag_idname = "idname";
const string tag_id = "id";
const string tag_APPROPRIATE = "APPROPRIATE";
const string tag_number_clips = "number_clips";
const string tag_clip = "clip";
const string tag_cliptype = "cliptype";
const string tag_number_weapons = "number_weapons";
const string tag_value = "value";
const string tag_CLIP_BUCKSHOT = "CLIP_BUCKSHOT";
const string tag_CLIP_SMG = "CLIP_SMG";
const string tag_CLIP_ASSAULT = "CLIP_ASSAULT";
const string tag_WEAPON_AUTORIFLE_AK47 = "WEAPON_AUTORIFLE_AK47";
const string tag_CLIP_44 = "CLIP_44";
const string tag_WEAPON_AXE = "WEAPON_AXE";
const string tag_CLIP_GASOLINE = "CLIP_GASOLINE";
const string tag_WEAPON_TORCH = "WEAPON_TORCH";
const string tag_WEAPON_PITCHFORK = "WEAPON_PITCHFORK";
const string tag_WEAPON_GAVEL = "WEAPON_GAVEL";

const string GIANT_MOSQUITO = "Giant Mosquito";
const string FLAMING_RABBIT = "Flaming Rabbit";
const string PET_SPACE = "Pet ";
const string CCS_TEAM_LEADER = "CCS Team Leader";
const string FIREFIGHTER = "Firefighter";
const string CONST_X_FIREMAN = "Fireman";
const string POLICE_NEGOTIATOR = "Police Negotiator";
const string CEO_SPACE = "CEO ";
const string ENFORCER = "Enforcer";
const string GENETIC_MONSTER_TXT = "genetic_monster.txt";
const string WORDS_MEANING_HICK_TXT = "words_meaning_hick.txt";
const string CCS_LIEUTENANT = "CCS Lieutenant";
const string CCS_FOUNDER = "CCS Founder";

const string tag_WEAPON_FLAMETHROWER = "WEAPON_FLAMETHROWER";
const string tag_LOOT_COMPUTER = "LOOT_COMPUTER";
const string tag_LOOT_CHEAPJEWELERY = "LOOT_CHEAPJEWELERY";
const string tag_LOOT_TRINKET = "LOOT_TRINKET";
const string tag_LOOT_SILVERWARE = "LOOT_SILVERWARE";
const string tag_LOOT_CELLPHONE = "LOOT_CELLPHONE";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_ARMOR_SECURITYUNIFORM = "ARMOR_SECURITYUNIFORM";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_ARMOR_HEAVYARMOR = "ARMOR_HEAVYARMOR";
const string tag_ARMOR_CHEAPSUIT = "ARMOR_CHEAPSUIT";
const string tag_ARMOR_WORKCLOTHES = "ARMOR_WORKCLOTHES";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_ARMOR_TRENCHCOAT = "ARMOR_TRENCHCOAT";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_WEAPON_SMG_MP5 = "WEAPON_SMG_MP5";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_REVOLVER_44 = "WEAPON_REVOLVER_44";
const string tag_LOOT_PDA = "LOOT_PDA";
const string tag_LOOT_MICROPHONE = "LOOT_MICROPHONE";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT_FAMILYPHOTO = "LOOT_FAMILYPHOTO";
const string tag_LOOT_WATCH = "LOOT_WATCH";
const string tag_ARMOR_BONDAGEGEAR = "ARMOR_BONDAGEGEAR";
const string tag_ARMOR_EXPENSIVESUIT = "ARMOR_EXPENSIVESUIT";
const string tag_ARMOR_EXPENSIVEDRESS = "ARMOR_EXPENSIVEDRESS";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_CHEMICAL = "LOOT_CHEMICAL";
const string tag_LOOT_FINECLOTH = "LOOT_FINECLOTH";
const string tag_ARMOR_BUNKERGEAR = "ARMOR_BUNKERGEAR";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_WEAPON_SHANK = "WEAPON_SHANK";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_ARMOR_POLICEARMOR = "ARMOR_POLICEARMOR";
const string tag_ARMOR_SWATARMOR = "ARMOR_SWATARMOR";
const string tag_ARMOR_POLICEUNIFORM = "ARMOR_POLICEUNIFORM";
const string tag_ARMOR_DEATHSQUADUNIFORM = "ARMOR_DEATHSQUADUNIFORM";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_WEAPON_NIGHTSTICK = "WEAPON_NIGHTSTICK";
const string tag_LOOT_LABEQUIPMENT = "LOOT_LABEQUIPMENT";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_ARMOR_BLACKROBE = "ARMOR_BLACKROBE";
const string tag_ARMOR_LABCOAT = "ARMOR_LABCOAT";
const string tag_ARMOR_BLACKDRESS = "ARMOR_BLACKDRESS";
const string tag_ARMOR_BLACKSUIT = "ARMOR_BLACKSUIT";
const string tag_WEAPON_SEMIRIFLE_AR15 = "WEAPON_SEMIRIFLE_AR15";
const string tag_WEAPON_COMBATKNIFE = "WEAPON_COMBATKNIFE";
const string tag_WEAPON_BASEBALLBAT = "WEAPON_BASEBALLBAT";
const string tag_WEAPON_DAISHO = "WEAPON_DAISHO";
const string tag_ARMOR_CLOWNSUIT = "ARMOR_CLOWNSUIT";
const string tag_ARMOR_DONKEYSUIT = "ARMOR_DONKEYSUIT";
const string tag_ARMOR_ELEPHANTSUIT = "ARMOR_ELEPHANTSUIT";
const string tag_ARMOR_CHEAPDRESS = "ARMOR_CHEAPDRESS";
const string tag_WEAPON_GUITAR = "WEAPON_GUITAR";
const string tag_LOOT_DIRTYSOCK = "LOOT_DIRTYSOCK";
const string tag_LOOT_KIDART = "LOOT_KIDART";
const string tag_ARMOR_TOGA = "ARMOR_TOGA";
const string tag_WEAPON_SYRINGE = "WEAPON_SYRINGE";
const string tag_WEAPON_CHAIN = "WEAPON_CHAIN";
const string tag_WEAPON_CROWBAR = "WEAPON_CROWBAR";
const string creature = "creature\\";

#include "../creature/creature.h"
#include "../locations/locationsEnums.h"
#include "../common/interval.h"
#include "creaturetype.h"
//own header
#include "../log/log.h"
// for LOG
#include "../common/translateid.h"
// for  int getweapontype(int)
#include "../common/stringconversion.h"
//for creaturetype_string_to_enum
#include "../politics/politics.h"
//for int publicmood(int l);

map<string, int> creatureTypeTags = {
	map<string, int>::value_type(tag_alignment, ENUM_tag_alignment),
	map<string, int>::value_type(tag_PUBLIC_MOOD, ENUM_tag_PUBLIC_MOOD),
	map<string, int>::value_type(tag_LIBERAL, ENUM_tag_LIBERAL),
	map<string, int>::value_type(tag_MODERATE, ENUM_tag_MODERATE),
	map<string, int>::value_type(tag_CONSERVATIVE, ENUM_tag_CONSERVATIVE),
	map<string, int>::value_type(tag_age, ENUM_tag_age),
	map<string, int>::value_type(tag_DOGYEARS, ENUM_tag_DOGYEARS),
	map<string, int>::value_type(tag_CHILD, ENUM_tag_CHILD),
	map<string, int>::value_type(tag_TEENAGER, ENUM_tag_TEENAGER),
	map<string, int>::value_type(tag_YOUNGADULT, ENUM_tag_YOUNGADULT),
	map<string, int>::value_type(tag_MATURE, ENUM_tag_MATURE),
	map<string, int>::value_type(tag_GRADUATE, ENUM_tag_GRADUATE),
	map<string, int>::value_type(tag_MIDDLEAGED, ENUM_tag_MIDDLEAGED),
	map<string, int>::value_type(tag_SENIOR, ENUM_tag_SENIOR),
	map<string, int>::value_type(tag_attribute_points, ENUM_tag_attribute_points),
	map<string, int>::value_type(tag_attributes, ENUM_tag_attributes),
	map<string, int>::value_type(tag_juice, ENUM_tag_juice),
	map<string, int>::value_type(tag_gender, ENUM_tag_gender),
	map<string, int>::value_type(tag_infiltration, ENUM_tag_infiltration),
	map<string, int>::value_type(tag_money, ENUM_tag_money),
	map<string, int>::value_type(tag_skills, ENUM_tag_skills),
	map<string, int>::value_type(tag_armor, ENUM_tag_armor),
	map<string, int>::value_type(tag_weapon, ENUM_tag_weapon),
	map<string, int>::value_type(tag_encounter_name, ENUM_tag_encounter_name),
	map<string, int>::value_type(tag_type_name, ENUM_tag_type_name),

};

vector<CreatureTypes> armAsCivilian = {
	// Curiously, CREATURE_CRACKHEAD has a chance to be armed with a shank, regardless of whether they are granted a civilian weapon
	CREATURE_CRACKHEAD, CREATURE_MUTANT, CREATURE_BUM, CREATURE_WORKER_FACTORY_UNION, CREATURE_WORKER_FACTORY_NONUNION, CREATURE_SCIENTIST_EMINENT, CREATURE_SCIENTIST_LABTECH
};

map<short, vector<CreatureTypes> > replaceTheseCreatures = {
	// The original code has a 1/10 chance to replace with CREATURE_THIEF
	// Otherwise, random selection between the other five.
	// This code changes this to a 1/11 chance to replace with CREATURE_THIEF
	// Which is close enough.
	map<CreatureTypes, vector<CreatureTypes> >::value_type(CREATURE_PRISONER,{ CREATURE_THIEF, CREATURE_GANGMEMBER, CREATURE_PROSTITUTE, CREATURE_CRACKHEAD, CREATURE_TEENAGER, CREATURE_HSDROPOUT, CREATURE_GANGMEMBER, CREATURE_PROSTITUTE, CREATURE_CRACKHEAD, CREATURE_TEENAGER, CREATURE_HSDROPOUT })

};
vector<CreatureTypes> doNotArmInThisFunction = {
	CREATURE_JUDGE_LIBERAL,
	CREATURE_POLITICIAN,
	CREATURE_CORPORATE_MANAGER,
	CREATURE_WORKER_SERVANT,
	CREATURE_WORKER_JANITOR,
	CREATURE_WORKER_SECRETARY,
	CREATURE_LANDLORD,
	CREATURE_BANK_TELLER,
	CREATURE_BANK_MANAGER,
	CREATURE_TEENAGER,
	CREATURE_SOLDIER,
	CREATURE_VETERAN,
	CREATURE_HARDENED_VETERAN,
	CREATURE_SWAT,
	CREATURE_DEATHSQUAD,
	CREATURE_GANGUNIT,
	CREATURE_AGENT,
	CREATURE_SECRET_SERVICE,
	CREATURE_RADIOPERSONALITY,
	CREATURE_NEWSANCHOR,
	CREATURE_JUROR,
	CREATURE_WORKER_FACTORY_CHILD,
	CREATURE_SEWERWORKER,
	CREATURE_COLLEGESTUDENT,
	CREATURE_MUSICIAN,
	CREATURE_MATHEMATICIAN,
	CREATURE_TEACHER,
	CREATURE_HSDROPOUT,
	CREATURE_PRIEST,
	CREATURE_ENGINEER,
	CREATURE_TELEMARKETER,
	CREATURE_CARSALESMAN,
	CREATURE_OFFICEWORKER,
	CREATURE_MAILMAN,
	CREATURE_GARBAGEMAN,
	CREATURE_PLUMBER,
	CREATURE_CHEF,
	CREATURE_CONSTRUCTIONWORKER,
	CREATURE_AMATEURMAGICIAN,
	CREATURE_AUTHOR,
	CREATURE_JOURNALIST,
	CREATURE_CRITIC_ART,
	CREATURE_CRITIC_MUSIC,
	CREATURE_BIKER,
	CREATURE_TRUCKER,
	CREATURE_TAXIDRIVER,
	CREATURE_PROGRAMMER,
	CREATURE_NUN,
	CREATURE_RETIREE,
	CREATURE_PAINTER,
	CREATURE_SCULPTOR,
	CREATURE_DANCER,
	CREATURE_PHOTOGRAPHER,
	CREATURE_CAMERAMAN,
	CREATURE_HAIRSTYLIST,
	CREATURE_FASHIONDESIGNER,
	CREATURE_CLERK,
	CREATURE_ACTOR,
	CREATURE_YOGAINSTRUCTOR,
	CREATURE_MARTIALARTIST,
	CREATURE_ATHLETE,
	CREATURE_LOCKSMITH,
	CREATURE_MILITARYPOLICE,
	CREATURE_SEAL,
	// These are not used in the switch statement anymore, but appear in the defaultWeapons collection
	//CREATURE_SECURITY_GUARD
	//CRREATURE_MERC
};
struct weaponLayout {
	string weaponTag;
	string clipTag;
	int ammunition;
	weaponLayout(string whichSkill_, string experience_, int maxLevel_) :weaponTag(whichSkill_), clipTag(experience_), ammunition(maxLevel_) {}
	weaponLayout(string whichSkill_) :weaponTag(whichSkill_), clipTag(""), ammunition(0) {}
	weaponLayout() : weaponLayout(tag_WEAPON_NONE) {}
};
struct fullWeaponLayout {
	weaponLayout cplus;
	weaponLayout c;
	weaponLayout moderate;
	weaponLayout l;
	weaponLayout lplus;
	fullWeaponLayout() : cplus(weaponLayout()), c(weaponLayout()), moderate(weaponLayout()), l(weaponLayout()), lplus(weaponLayout()) {}
	fullWeaponLayout(weaponLayout cplus_, weaponLayout c_, weaponLayout moderate_, weaponLayout l_, weaponLayout lplus_) : cplus(cplus_), c(c_), moderate(moderate_), l(l_), lplus(lplus_) {}

};


map<const short, const fullWeaponLayout> defaultWeapons = {
	map<const short, const fullWeaponLayout>::value_type(CREATURE_BOUNCER, fullWeaponLayout(weaponLayout(tag_WEAPON_SMG_MP5, tag_CLIP_SMG, 4), weaponLayout(tag_WEAPON_REVOLVER_44, tag_CLIP_44, 4), weaponLayout(tag_WEAPON_REVOLVER_38, tag_CLIP_38, 4), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_NIGHTSTICK))),
	map<const short, const fullWeaponLayout>::value_type(CREATURE_SECURITYGUARD, fullWeaponLayout(weaponLayout(tag_WEAPON_SMG_MP5, tag_CLIP_SMG, 4), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_NIGHTSTICK), weaponLayout(tag_WEAPON_REVOLVER_38, tag_CLIP_38, 4))),
	map<const short, const fullWeaponLayout>::value_type(CREATURE_MERC, fullWeaponLayout(weaponLayout(tag_WEAPON_AUTORIFLE_M16, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_AUTORIFLE_M16, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_AUTORIFLE_M16, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_SEMIRIFLE_AR15, tag_CLIP_ASSAULT, 7), weaponLayout(tag_WEAPON_SEMIRIFLE_AR15, tag_CLIP_ASSAULT, 7))),

};

#define AGE_TEENAGER    14+LCSrandom(4)  /* HS dropout, teenager, some fast food workers */
#define AGE_YOUNGADULT  18+LCSrandom(18) /* young lads and ladies */
#include "locations/locationsPool.h"
#include "sitemode/stealth.h"
short getCurrentSite();
struct fullName {
	string first;
	string middle;
	string last;

};
fullName generate_long_name(char gender = GENDER_NEUTRAL);
#include "customMaps.h"
vector<string> words_meaning_hick;
vector<string> genetic_monster;
vector<file_and_text_collection> creaturetypes_text_file_collection = {
	/*creaturetypes.cpp*/
	customText(&words_meaning_hick, creature + WORDS_MEANING_HICK_TXT),
	customText(&genetic_monster, creature + GENETIC_MONSTER_TXT),
};
bool isThereASiteAlarm();
extern char ccs_kills;
extern char endgamestate;
extern Log xmllog;
extern short lawList[LAWNUM];
extern short mode;
extern short sitealienate;
extern short sitetype;
extern vector<ClipType *> cliptype;
extern vector<WeaponType *> weapontype;

//#endif//CREATURETYPE_CPP
//#endif// INCLUDES_H_INCLUDED
