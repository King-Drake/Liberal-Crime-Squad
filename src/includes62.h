




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

// fight.cpp

const string fighty = "fight\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_S_NECK_IS_BROKEN = "'s neck is broken!";
const string CONST_S_NECK_BONES_ARE_SHATTERED = "'s neck bones are shattered!";
const string CONST_S_NOSE_IS_REMOVED = "'s nose is removed!";
const string CONST_S_NOSE_IS_CUT_OFF = "'s nose is cut off!";
const string CONST_S_NOSE_IS_TORN_OFF = "'s nose is torn off!";
const string CONST_S_NOSE_IS_BURNED_AWAY = "'s nose is burned away!";
const string CONST_S_NOSE_IS_BLASTED_OFF = "'s nose is blasted off!";
const string CONST_S_TONGUE_IS_REMOVED = "'s tongue is removed!";
const string CONST_S_TONGUE_IS_CUT_OFF = "'s tongue is cut off!";
const string CONST_S_TONGUE_IS_TORN_OUT = "'s tongue is torn out!";
const string CONST_S_TONGUE_IS_BURNED_AWAY = "'s tongue is burned away!";
const string CONST_S_TONGUE_IS_BLASTED_OFF = "'s tongue is blasted off!";
const string CONST_S_LEFT_EYE_IS_REMOVED = "'s left eye is removed!";
const string CONST_S_LEFT_EYE_IS_POKED_OUT = "'s left eye is poked out!";
const string CONST_S_LEFT_EYE_IS_TORN_OUT = "'s left eye is torn out!";
const string CONST_S_LEFT_EYE_IS_BURNED_AWAY = "'s left eye is burned away!";
const string CONST_S_LEFT_EYE_IS_BLASTED_OUT = "'s left eye is blasted out!";
const string CONST_S_RIGHT_EYE_IS_REMOVED = "'s right eye is removed!";
const string CONST_S_RIGHT_EYE_IS_POKED_OUT = "'s right eye is poked out!";
const string CONST_S_RIGHT_EYE_IS_TORN_OUT = "'s right eye is torn out!";
const string CONST_S_RIGHT_EYE_IS_BURNED_AWAY = "'s right eye is burned away!";
const string CONST_S_RIGHT_EYE_IS_BLASTED_OUT = "'s right eye is blasted out!";
const string CONST_KNOCKED_OUT = "knocked out!";
const string CONST_CUT_OUT = "cut out!";
const string CONST_GOUGED_OUT = "gouged out!";
const string CONST_BURNED_AWAY = "burned away!";
const string CONST_SHOT_OUT = "shot out!";
const string CONST_S_LAST_TOOTH_IS = "'s last tooth is ";
const string CONST_S_TEETH_IS = "'s teeth is ";
const string CONST_ONE_OF = "One of ";
const string CONST_S_TEETH_ARE = "'s teeth are ";
const string CONST_OF = " of ";
const string CONST_ALL = "All ";
const string CONST_S_FACE_IS_REMOVED = "'s face is removed!";
const string CONST_S_FACE_IS_CUT_AWAY = "'s face is cut away!";
const string CONST_S_FACE_IS_TORN_OFF = "'s face is torn off!";
const string CONST_S_FACE_IS_BURNED_AWAY = "'s face is burned away!";
const string CONST_S_FACE_IS_BLASTED_OFF = "'s face is blasted off!";
const string CONST_BROKEN = "broken!";
const string CONST_SHOT_APART = "shot apart!";
const string CONST_S_LAST_UNBROKEN_RIB_IS = "'s last unbroken rib is ";
const string CONST_S_RIB_IS = "'s rib is ";
const string CONST_S_RIBS_ARE = "'s ribs are ";
const string CONST_S_SPLEEN_IS_PUNCTURED = "'s spleen is punctured!";
const string CONST_S_SPLEEN_IS_TORN = "'s spleen is torn!";
const string CONST_S_SPLEEN_IS_BLASTED = "'s spleen is blasted!";
const string CONST_S_LEFT_KIDNEY_IS_PUNCTURED = "'s left kidney is punctured!";
const string CONST_S_LEFT_KIDNEY_IS_TORN = "'s left kidney is torn!";
const string CONST_S_LEFT_KIDNEY_IS_BLASTED = "'s left kidney is blasted!";
const string CONST_S_RIGHT_KIDNEY_IS_PUNCTURED = "'s right kidney is punctured!";
const string CONST_S_RIGHT_KIDNEY_IS_TORN = "'s right kidney is torn!";
const string CONST_S_RIGHT_KIDNEY_IS_BLASTED = "'s right kidney is blasted!";
const string CONST_S_STOMACH_IS_PUNCTURED = "'s stomach is punctured!";
const string CONST_S_STOMACH_IS_TORN = "'s stomach is torn!";
const string CONST_S_STOMACH_IS_BLASTED = "'s stomach is blasted!";
const string CONST_S_LIVER_IS_PUNCTURED = "'s liver is punctured!";
const string CONST_S_LIVER_IS_TORN = "'s liver is torn!";
const string CONST_S_LIVER_IS_BLASTED = "'s liver is blasted!";
const string CONST_S_HEART_IS_PUNCTURED = "'s heart is punctured!";
const string CONST_S_HEART_IS_TORN = "'s heart is torn!";
const string CONST_S_HEART_IS_BLASTED = "'s heart is blasted!";
const string CONST_S_LEFT_LUNG_IS_PUNCTURED = "'s left lung is punctured!";
const string CONST_S_LEFT_LUNG_IS_TORN = "'s left lung is torn!";
const string CONST_S_LEFT_LUNG_IS_BLASTED = "'s left lung is blasted!";
const string CONST_S_RIGHT_LUNG_IS_PUNCTURED = "'s right lung is punctured!";
const string CONST_S_RIGHT_LUNG_IS_TORN = "'s right lung is torn!";
const string CONST_S_RIGHT_LUNG_IS_BLASTED = "'s right lung is blasted!";
const string CONST_S_LOWER_SPINE_IS_BROKEN = "'s lower spine is broken!";
const string CONST_S_LOWER_SPINE_IS_SHATTERED = "'s lower spine is shattered!";
const string CONST_S_UPPER_SPINE_IS_BROKEN = "'s upper spine is broken!";
const string CONST_S_UPPER_SPINE_IS_SHATTERED = "'s upper spine is shattered!";
const string CONST_S_BODY = "'s body.";
const string CONST_DROPS = " drops ";
const string CONST_MISSES_COMPLETELY = " misses completely!";
const string CONST_JUST_BARELY_MISSED = " just barely missed!";
const string CONST_MISSED = " missed!";
const string CONST_KNOCKS_THE_BLOW_ASIDE_AND_COUNTERS = " knocks the blow aside and counters!";
const string CONST_TO_NO_EFFECT = " to no effect.";
const string CONST_EXCLAMATION_POINT = "!";
const string CONST_S_CORPSE = "'s corpse";
const string CONST_SHIELDS = " shields ";
const string CONST_HEROICALLY = " heroically";
const string CONST_MISGUIDEDLY = " misguidedly";
const string CONST_THE = "the ";
const string CONST_THE_ATTACK_BOUNCES_OFF = "The attack bounces off ";
const string CONST_THROUGH = " through ";
const string CONST_STRIKING = "striking";
const string CONST_X_S_SPACE = "'s ";
const string CONST_HITS = " hits ";
const string CONST_X_STABS_ = " stabs ";
const string CONST_WITH_A = " with a ";
const string CONST_SNEAKS_UP_ON = "sneaks up on";
const string CONST_BITES = "bites";
const string CONST_STABS = "stabs";
const string CONST_BREATHES_FIRE_AT = "breathes fire at";
const string CONST_FIRES_A_120MM_SHELL_AT = "fires a 120mm shell at";
const string CONST_MISTAKENLY = "MISTAKENLY ";
const string CONST_READIES_ANOTHER = " readies another ";
const string CONST_RELOADS = " reloads.";
const string CONST_ACTUAL = "actual";
const string CONST_A_PLAGUE_ON_BOTH_YOUR_HOUSES = "\"A plague on both your houses...\"";
const string CONST_SPEAKS_THESE_FINAL_WORDS = " speaks these final words: ";
const string CONST_X_SOILS_THE_FLOOR = "soils the floor.";
const string CONST_X_MAKES_A_MESS = "[makes a mess].";
const string CONST_GASPS_A_LAST_BREATH_AND = " gasps a last breath and ";
const string CONST_SOMETHING_ABOUT_JESUS_AND_DIES = "something about Jesus, and dies.";
const string CONST_SOMETHING_GOOD_ABOUT_JESUS_AND_DIES = "something [good] about Jesus, and dies.";
const string CONST_SWEATS_PROFUSELY_MURMURS = " sweats profusely, murmurs ";
const string CONST_THE_NECK_HOLE_THEN_IS_QUIET = "the neck hole, then is quiet.";
const string CONST_SUCKS_A_LAST_BREATH_THROUGH = " sucks a last breath through ";
const string CONST_NECK_AND_FALLS_TO_THE_SIDE = "neck and falls to the side.";
const string CONST_NECK_AND_RUNS_DOWN_THE_HALL = "neck and runs down the hall.";
const string CONST_OUT_OF_THE = " out of the ";
const string CONST_RED_WATER = "[red water]";
const string CONST_SQUIRTS = " squirts ";
const string CONST_MOMENT_THEN_CRUMPLES_OVER = "moment then crumples over.";
const string CONST_SITS_HEADLESS_FOR_A = " sits headless for a ";
const string CONST_STANDS_HEADLESS_FOR_A = " stands headless for a ";
const string CONST_IS_NO_HEAD_AND_SLUMPS_OVER = "is no head, and slumps over.";
const string CONST_IS_NO_HEAD_AND_FALLS = "is no head, and falls.";
const string CONST_REACHES_ONCE_WHERE_THERE = " reaches once where there ";
const string CONST_HAS_BEEN_DESTROYED = " has been destroyed.";
const string CONST_S_GRASP = "'s grasp.";
const string CONST_SLIPS_FROM = " slips from";
const string CONST_NULL_BODYPART = "NULL BODYPART";
const string CONST_REMAINS_STRONG = " remains strong.";
const string CONST_HAS_TURNED_LIBERAL = " has turned Liberal!";
const string CONST_S_HEART_SWELLS = "'s Heart swells!";
const string CONST_SEEMS_LESS_BADASS = " seems less badass!";
const string CONST_DOESN_T_WANT_TO_FIGHT_ANYMORE = " doesn't want to fight anymore";
const string CONST_IS_TURNED_CONSERVATIVE = " is turned Conservative";
const string CONST_CAN_T_BEAR_TO_LEAVE = " can't bear to leave!";
const string CONST_IS_TAINTED_WITH_WISDOM = " is tainted with Wisdom!";
const string CONST_LOSES_JUICE = " loses juice!";
const string CONST_ALREADY_AGREES_WITH = " already agrees with ";
const string CONST_IS_IMMUNE_TO_THE_ATTACK = " is immune to the attack!";
const string CONST_ROCKS_OUT_AT = "rocks out at";
const string CONST_PLAYS_COUNTRY_SONGS_AT = "plays country songs at";
const string CONST_PLAYS_PROTEST_SONGS_AT = "plays protest songs at";
const string CONST_AT = " at";
const string CONST_BLOWS_A_HARMONICA = "blows a harmonica";
const string CONST_STRUMS_THE = "strums the ";
const string CONST_SINGS_TO = "sings to";
const string CONST_PLAYS_A_SONG_FOR = "plays a song for";
const string CONST_EXPLAINS_ETHICAL_RESEARCH_TO = "explains ethical research to";
const string CONST_EXPLAINS_THE_BENEFITS_OF_RESEARCH_TO = "explains the benefits of research to";
const string CONST_SPITS_UP_A_CLUSTER_OF_BLOODY_BUBBLES = " spits up a cluster of bloody bubbles.";
const string CONST_MAKES_A_MESS = " [makes a mess].";
const string CONST_VOMITS_UP_A_CLOT_OF_BLOOD = " vomits up a clot of blood.";
const string CONST_S_GUMS_START_CHATTERING = "'s gums start chattering.";
const string CONST_S_TOOTH_STARTS_CHATTERING = "'s tooth starts chattering.";
const string CONST_S_TEETH_START_CHATTERING = "'s teeth start chattering.";
const string CONST_PISSES_ON_THE_FLOOR_MOANING = " pisses on the floor, moaning.";
const string CONST_MAKES_A_MESS_MOANING = " [makes a mess], moaning.";
const string CONST_STARES_OUT_WITH_HOLLOW_SOCKETS = " stares out with hollow sockets.";
const string CONST_STARES_INTO_SPACE_WITH_ONE_EMPTY_EYE = " stares into space with one empty eye.";
const string CONST_STARES_OFF_INTO_SPACE = " stares off into space.";
const string CONST_LEANS_AGAINST_THE_DOOR = " leans against the door.";
const string CONST_STUMBLES_AGAINST_A_WALL = " stumbles against a wall.";
const string CONST_SOILS_THE_FLOOR = " soils the floor.";
const string CONST_MAKES_A_STINKY = " [makes a stinky].";
//const string CONST_TIMES = " times";
const string CONST_FIVE_TIMES = " five times";
const string CONST_FOUR_TIMES = " four times";
const string CONST_THREE_TIMES = " three times";
const string CONST_TWICE = " twice";
const string CONST_EVASIONSTRINGSALT_TXT = "evasionStringsAlt.txt";
const string CONST_EVASIONSTRINGS_TXT = "evasionStrings.txt";
const string CONST_BODY_FALLS_APART_TXT = "body_falls_apart.txt";
const string CONST_DOUBLE_LINE_DEATH_TXT = "double_line_death.txt";
const string CONST_BLEEDING_ANIMAL_TXT = "bleeding_animal.txt";
const string CONST_PARALYZED_TANK_TXT = "paralyzed_tank.txt";
const string CONST_PARALYZED_TEXT_TXT = "paralyzed_text.txt";
const string CONST_STUNNED_TEXT_TXT = "stunned_text.txt";
const string CONST_BLEEDING_TO_DEATH_TXT = "bleeding_to_death.txt";
const string CONST_CRY_ALARM_TXT = "cry_alarm.txt";
const string CONST_SCIENTIST_DEBATE_TXT = "scientist_debate.txt";
const string CONST_POLICE_DEBATE_TXT = "police_debate.txt";
const string CONST_MILITARY_DEBATE_TXT = "military_debate.txt";
const string CONST_MEDIA_DEBATE_TXT = "media_debate.txt";
const string CONST_OTHER_POLITICIAN_DEBATE_TXT = "other_politician_debate.txt";
const string CONST_CONSERVATIVE_POLITICIAN_DEBATE_TXT = "conservative_politician_debate.txt";
const string CONST_OTHER_CEO_DEBATE_TXT = "other_ceo_debate.txt";
const string CONST_CONSERVATIVE_CEO_DEBATE_TXT = "conservative_ceo_debate.txt";
const string CONST_JUDGE_DEBATE_TXT = "judge_debate.txt";
const string CONST_ESCAPE_CRAWLING_TXT = "escape_crawling.txt";
const string CONST_ESCAPE_RUNNING_TXT = "escape_running.txt";
const string CONST_CRIES_MOMMY = " cries \"Mommy!\"";
const string CONST_MURMURS_WHAT_ABOUT_MY_OFFSPRING = " murmurs \"What about my offspring?\"";
const string CONST_MURMURS_WHAT_ABOUT_MY_PUPPIES = " murmurs \"What about my puppies?\"";
const string CONST_MURMURS_WHAT_ABOUT_MY_CHILDREN = " murmurs \"What about my children?\"";
const string CONST_BETTER_DEAD_THAN_LIBERAL = "\"Better dead than liberal...\"";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_false = "false";
const string tag_blood = "blood";
const string tag_The = "The ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../sitemode/stealth.h"
#include "../sitemode/sitedisplay.h"
#include "../items/money.h"
#include "../log/log.h"
// for gamelog
//#include "../common/translateid.h"
int getarmortype(const string &idname);
//#include "../common/commondisplay.h"
void printparty();
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
//#include "../combat/chaseCreature.h"
Vehicle* getChaseVehicle(const DeprecatedCreature &c);
DeprecatedCreature* getChaseDriver(const DeprecatedCreature &c);
//#include "../combat/haulkidnapCreature.h"
void freehostage(DeprecatedCreature &cr, char situation);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/creaturePool.h"
vector<string> escape_running;
vector<string> escape_crawling;
vector<string> judge_debate;
vector<string> conservative_ceo_debate;
vector<string> other_ceo_debate;
vector<string> conservative_politician_debate;
vector<string> other_politician_debate;
vector<string> media_debate;
vector<string> military_debate;
vector<string> police_debate;
vector<string> scientist_debate;
vector<string> cry_alarm;
vector<string> bleeding_to_death;
vector<string> stunned_text;
vector<string> paralyzed_text;
vector<string> paralyzed_tank;
vector<string> bleeding_animal;
vector<vector<string> > double_line_death;
vector<string> body_falls_apart;
vector<string> evasionStringsAlt;
vector<string> evasionStrings;
const int DOUBLE_LINE = 2;
vector<file_and_text_collection> fighty_text_file_collection = {
	/*fight.cpp*/
	customText(&escape_running, fighty + CONST_ESCAPE_RUNNING_TXT),
	customText(&escape_crawling, fighty + CONST_ESCAPE_CRAWLING_TXT),
	customText(&judge_debate, fighty + CONST_JUDGE_DEBATE_TXT),
	customText(&conservative_ceo_debate, fighty + CONST_CONSERVATIVE_CEO_DEBATE_TXT),
	customText(&other_ceo_debate, fighty + CONST_OTHER_CEO_DEBATE_TXT),
	customText(&conservative_politician_debate, fighty + CONST_CONSERVATIVE_POLITICIAN_DEBATE_TXT),
	customText(&other_politician_debate, fighty + CONST_OTHER_POLITICIAN_DEBATE_TXT),
	customText(&media_debate, fighty + CONST_MEDIA_DEBATE_TXT),
	customText(&military_debate, fighty + CONST_MILITARY_DEBATE_TXT),
	customText(&police_debate, fighty + CONST_POLICE_DEBATE_TXT),
	customText(&scientist_debate, fighty + CONST_SCIENTIST_DEBATE_TXT),
	customText(&cry_alarm, fighty + CONST_CRY_ALARM_TXT),
	customText(&bleeding_to_death, fighty + CONST_BLEEDING_TO_DEATH_TXT),
	customText(&stunned_text, fighty + CONST_STUNNED_TEXT_TXT),
	customText(&paralyzed_text, fighty + CONST_PARALYZED_TEXT_TXT),
	customText(&paralyzed_tank, fighty + CONST_PARALYZED_TANK_TXT),
	customText(&bleeding_animal, fighty + CONST_BLEEDING_ANIMAL_TXT),
	customText(&double_line_death, fighty + CONST_DOUBLE_LINE_DEATH_TXT, DOUBLE_LINE),
	customText(&body_falls_apart, fighty + CONST_BODY_FALLS_APART_TXT),
	customText(&evasionStrings, MOSTLY_ENDINGS_FOLDER + CONST_EVASIONSTRINGS_TXT),
	customText(&evasionStringsAlt, MOSTLY_ENDINGS_FOLDER + CONST_EVASIONSTRINGSALT_TXT),
};

extern bool NOENEMYATTACK;
extern char foughtthisround;
extern coordinatest loc_coord;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int ccs_boss_kills;
extern int ccs_siege_kills;
extern int sitecrime;
extern int stat_dead;
extern int stat_kills;
extern Log gamelog;
extern short lawList[LAWNUM];
extern short mode;
extern short sitealarmtimer;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern string slogan_str;
extern vector<DeprecatedCreature *> pool;

short  getCurrentSite();
void addLocationChange(int cursite, sitechangest change);



vector<Item *> groundloot;


vector<NameAndAlignment> getEncounterNameAndAlignment();
void delenc(const short e, const char loot);
string specialWoundPossibilityBody(
	DeprecatedCreature &target,
	const char breakdam,
	const char pokedam,
	const char damtype
);
string specialWoundPossibilityHead(
	DeprecatedCreature &target,
	const char breakdam,
	const char heavydam,
	const char damtype
);
map<short, string> tankBodyParts;
map<short, string> animalBodyParts;
map<short, string> humanBodyParts;
std::string burstHitString(int bursthits);
void bloodyUpEncounterArmor();
/* attack handling for an individual creature and its target */
// returns a boolean representing whether it was the intended target or CONST_ACTUAL
// so bool actual does not need to be passed by reference
bool attack(DeprecatedCreature &a, DeprecatedCreature &t, const char mistake, const bool force_melee = false);

void setSiteAlarmOne();
string howGracefulAttack(int handToHand);
string dismemberingWound(const int w, const int wound);
int bodypartSeverAmount(const int w);

class AttackInfliction {
public:
	AttackInfliction(const bool, const int, const int, const attackst);
	const bool sneak_attack;
	const int aroll;
	const int droll;
	const attackst attack_used;
};
AttackInfliction::AttackInfliction(const bool _sneak_attack, const int _aroll, const int _droll, const attackst _attack_used) : sneak_attack(_sneak_attack), aroll(_aroll < 0 ? 0 : _aroll),
	droll(_droll < 0 ? 0 : _droll),
	attack_used(_attack_used) {


}
class AttackSeverity {
public:
	AttackSeverity::AttackSeverity(const int, const int, const int, const int);
	const int damamount;
	const int damagearmor;
	const int severtype;
	const int hit_location;

};
AttackSeverity::AttackSeverity(const int _damamount, const int _damagearmor, const int _severtype, const int w) : damamount(_damamount),
damagearmor(_damagearmor),
severtype(_severtype),
hit_location(w)
{


}

struct damageDetails {
	const int mod;
	const int hit_location;
	const int extraarmor;
	const char armorpiercing;
	damageDetails(int _mod, int _hit_location, int _extraarmor, char _armorpiercing) : mod(_mod), hit_location(_hit_location), extraarmor(_extraarmor), armorpiercing(_armorpiercing) {};
};
bool attackPoolEncounter(const int p, const int t, const char mistake, const bool force_melee = false);
void addLocationChange(int cursite, sitechangest change);
bool isThereASiteAlarm();
vector<NameAndAlignment> getEncounterNameAndAlignment();
enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};
void conservatise(const int e);
//#endif//FIGHT_CPP
//#endif// INCLUDES_H_INCLUDED
