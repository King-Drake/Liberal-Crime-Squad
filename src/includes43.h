




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
//#include "includesDeprecatedB.h"
//#ifdef	DATE_CPP
// date.cpp

const string CONST_S = "'s ";
const string CONST_CELL_PHONE = " cell phone.";
const string CONST_PET = " pet";
const string CONST_FAVOURITE_TV_SHOW = " favourite TV show.";
const string CONST_HAIR = " hair.";
const string CONST_S_FROZEN_CONSERVATIVE_HEART = "'s frozen Conservative heart.";
const string CONST_THE_LIBERAL_WAKES_UP_IN_THE_POLICE_STATION = "The Liberal wakes up in the police station...";
const string CONST_REMEMBERS_SEEING = " remembers seeing!";
const string CONST_S_FIST_IS_THE_LAST_THING = "'s fist is the last thing ";
const string CONST_HAS_FAILED_TO_KIDNAP_THE_CONSERVATIVE = " has failed to kidnap the Conservative.";
const string CONST_MANAGES_TO_GET_AWAY_ON_THE_WAY_BACK_TO_THE_SAFEHOUSE = " manages to get away on the way back to the safehouse!";
const string CONST_IF_YOU_DO_NOT_ENTER_ANYTHING_THEIR_REAL_NAME_WILL_BE_USED = "If you do not enter anything, their real name will be used.";
const string CONST_IN_ITS_PRESENCE = " in its presence?";
const string CONST_WHAT_NAME_WILL_YOU_USE_FOR_THIS = "What name will you use for this ";
const string CONST_THE_EDUCATION_OF = "The Education of ";
const string CONST_KIDNAPS_THE_CONSERVATIVE = " kidnaps the Conservative!";
const string CONST_STRUGGLES_AND_YELLS_FOR_HELP_BUT_NOBODY_COMES = " struggles and yells for help, but nobody comes.";
const string CONST_DOESN_T_RESIST = " doesn't resist.";
const string CONST_NOT_TO_RESIST = "not to [resist]!";
const string CONST_NOT_TO_FUCK_AROUND = "not to fuck around!";
const string CONST_SEIZES_THE_CONSERVATIVE_SWINE_FROM_BEHIND_AND_WARNS_IT = " seizes the Conservative swine from behind and warns it";
const string CONST_TO_THE_CORPORATE_SLAVE_S_THROAT = "to the corporate slave's throat!";
const string CONST_GRABS_THE_CONSERVATIVE_FROM_BEHIND_HOLDING_THE = " grabs the Conservative from behind, holding the ";
const string CONST_AND_THREATENS_TO_BLOW_THE_CONSERVATIVE_S_BRAINS_OUT = "and threatens to blow the Conservative's brains out!";
const string CONST_COMES_BACK_FROM_THE_BATHROOM_TOTING_THE = " comes back from the bathroom toting the ";
const string CONST_E_JUST_KIDNAP_THE_CONSERVATIVE_BITCH = "E - Just kidnap the Conservative bitch.";
const string CONST_D_BREAK_IT_OFF = "D - Break it off.";
const string CONST_C_SPEND_A_WEEK_ON_A_CHEAP_VACATION_MUST_BE_UNINJURED = "C - Spend a week on a cheap vacation (must be uninjured).";
const string CONST_C_SPEND_A_WEEK_ON_A_CHEAP_VACATION_STANDS_UP_ANY_OTHER_DATES = "C - Spend a week on a cheap vacation (stands up any other dates).";
const string CONST_B_TRY_TO_GET_THROUGH_THE_EVENING_WITHOUT_SPENDING_A_PENNY = "B - Try to get through the evening without spending a penny.";
const string CONST_A_SPEND_A_HUNDRED_BUCKS_TONIGHT_TO_GET_THE_BALL_ROLLING = "A - Spend a hundred bucks tonight to get the ball rolling.";
const string CONST_APPROACH_THE_SITUATION = " approach the situation?";
const string CONST_HOW_SHOULD = "How should ";
const string CONST_SEEING = "Seeing ";
const string CONST_THINGS_GO_DOWNHILL_FAST = "Things go downhill fast.";
const string CONST_MIXES_UP_THE_NAMES_OF = " mixes up the names of ";
const string REALIZES = " realizes ";
const string HAS_COMMITTED = " has committed to eating ";
const string MEALS_AT_ONCE = " meals at once.";
const string RUH_ROH = "Ruh roh...";
const string UNFORTUNATELY_THEY_TURN_UP_AT_ONCE = "Unfortunately, they turn up at the same time.";
const string UNFORTUNATELY_THEY_ALL_TURN_UP_AT_ONCE = "Unfortunately, they all turn up at the same time.";
const string AN_AMBUSH_FOR_THE_DOG = ".  An ambush was set for the lying dog...";
const string UNFORTUNATELY_THEY_KNOW_EACHOTHER = "Unfortunately, they know each other and had been discussing";
const string UNFORTUNATELY_THEY_ALL_KNOW_EACHOTHER = "Unfortunately, they all know each other and had been discussing";
const string AT_SPACE = " at ";
const string DATES_TO_MANAGE = "dates to manage with ";
const string A_HOT_DATE = "a hot date with ";
const string A_H_O_T_DATE = "a \"hot\" date with ";
const string CONST_S_HAS_S = " has ";
const string IS_BACK_FROM_VACATION = " is back from vacation.";
const string THE_RELATIONSHIP_IS_OVER = "This relationship is over.";
const string CAN_SENSE_THAT_THINGS_ARENT_WORKING = " can sense that things just aren't working out.";
const string FROM_MEETING_SPACE = " from meeting ";
const string SCHEDULE_FOR_KEEPING = "schedule for keeping ";
const string MIND_BENDING = "mind-bending ";
const string DETAILED = "detailed ";
const string COMPLICATED = "complicated ";
const string INTRICATE = "intricate ";
const string AWE_INSPIRING = "awe-inspiring ";
const string NOTICES = "notices ";
const string THE_DATE_STARTS_WELL_UNTIL = "The date starts well, but goes horribly wrong when ";
const string ESCAPES_THE_POLICE_AMBUSH = " escapes the police ambush!";
const string BUT_SPACE = "But ";
const string HAS_BEEN_ARRESTED = " has been arrested.";
const string WAS_LEAKING_INFORMATION_TO_POLICE = " was leaking information to the police the whole time!";
const string S_MIND_WITH_WISDOM = "'s mind with wisdom!!!";
const string ACTUALLY_CURSES = " actually curses ";
const string TALKING_WITH = "Talking with ";
const string THEYLL_MEET_AGAIN_TOMORROW = "They'll meet again tomorrow.";
const string TO_RECHARGE = " to recharge ";
const string TO_GO_TO_BIRTHDAY = " to go to a birthday party.";
const string SIX_LEGGED_PIG = " six-legged pig.";
const string CONST_X_FISH = " fish.";
const string CONST_X_DOG = " dog.";
const string CONST_X_CAT = " cat.";
const string TO_TAKE_CARE_OF = " to take care of ";
const string TO_CATCH = " to catch ";
const string DUE_TO_EARLY_MEETING = " due to an early meeting tomorrow.";
const string DUE_TO_ALLERGY = " due to an allergy attack.";
const string TO_WASH = " to wash ";
const string SEEMED_TO_HAVE_FUN_BUT_LEFT_EARLY = " seemed to have fun, but left early";
const string KNOWS_THIS_ALREADY = " knows all about that already.";
const string WAS_ABLE_TO_CREATE_MAP = " was able to create a map of the site with this information.";
const string TURNS_THE_TOPIC_OF_DISCUSSION = " turns the topic of discussion to the ";
const string IS_SLOWLY_WARMING = " is slowly warming ";
const string SELF_NULLIFYING_INFATUATION_OF = "The Self-Nullifying Infatuation of ";
const string S_TOTALLY_LOVE_SLAVE = "'s totally unconditional love-slave!";
const string IS_SPACE = " is ";
const string IN_FACT = "In fact, ";
const string IT_WAS_FUN_PART_AMICABLY = "It was fun though. They agree to part ways amicably.";
const string RELATIONSHIP = " relationship.";
const string YET_ANOTHER = "yet another";
const string ANOTHER = "another";
const string ISNT_SEDUCTIVE_ENOUGH = " isn't seductive enough to juggle ";
const string CONST_X_PEOPLE = " people!";
const string SOMEONE = "someone!";
const string IS_ALREADY_DATING = " is already dating ";
const string S_UNIQUE_PHILOSOPHY = "'s unique life philosophy...";
const string IS_QUITE_TAKEN_WITH = " is quite taken with ";
const string DATE_FAIL_TXT = "date_fail.txt";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string datey = "date\\";


#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"
//#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for  addstr
#include "../common/commonactionsCreature.h"
// for int loveslavesleft(const Creature&)
#include "../common/getnames.h"
// for void enter_name(int,int,char *,int,const char *=NULL)
//#include "../common/translateid.h"
int getarmortype(const string &idname);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/creaturePoolCreature.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"

extern class Ledger ledger;
extern int stat_kidnappings;
extern int stat_recruits;
extern Log gamelog;
extern MusicClass music;
extern short lawList[LAWNUM];
extern vector<DeprecatedCreature *> pool;

vector<string> date_fail;
vector<file_and_text_collection> date_text_file_collection = {
	/*date.cpp*/
	customText(&date_fail, datey + DATE_FAIL_TXT),
};
enum DateResults
{
	DATERESULT_MEETTOMORROW,
	DATERESULT_BREAKUP,
	DATERESULT_JOINED,
	DATERESULT_ARRESTED
};
int getpoolcreature(int id);
char completedate(Deprecateddatest &d, int p);
void removesquadinfo(DeprecatedCreature &cr);
char completevacation(Deprecateddatest &d, int p);
//#endif//DATE_CPP
//#endif// INCLUDES_H_INCLUDED
