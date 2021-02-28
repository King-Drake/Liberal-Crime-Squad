




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
//#ifdef	INTERROGATION_CPP
// interrogation.cpp

const string feels_sick_and = " feels sick to the stomach afterward and ";
const string interrogate = "interrogation\\";
const string QUOTATION_MARK = "\"";
const string CONST_HUGS = "hugs ";
const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THIS = "Press any key to reflect on this.";
const string CONST_S_DISAPPEARANCE_HAS_NOT_YET_BEEN_REPORTED = "'s disappearance has not yet been reported.";
const string WAS_ABLE_TO_CREATE_MAP = " was able to create a map of the site with this information.";
const string CONST_UNFORTUNATELY_NONE_OF_IT_IS_USEFUL_TO_THE_LCS = "Unfortunately, none of it is useful to the LCS.";
const string CONST_REVEALS_DETAILS_ABOUT_THE = " reveals details about the ";
const string CONST_THE_CONVERSION_IS_CONVINCING_ENOUGH_THAT_THE_POLICE_NO_LONGER_CONSIDER_IT_A_KIDNAPPING = "The conversion is convincing enough that the police no longer consider it a kidnapping.";
const string CONST_THE_AUTOMATON_HAS_BEEN_ENLIGHTENED_YOUR_LIBERAL_RANKS_ARE_SWELLING = "The Automaton has been Enlightened!   Your Liberal ranks are swelling!";
const string CONST_GROWS_COLDER = " grows colder.";
const string CONST_S_INTERROGATION = "'s interrogation.";
const string CONST_UNDER = " under ";
const string CONST_IS_DEAD = " is dead";
const string CONST_HAS_COMMITTED_SUICIDE = " has committed suicide.";
const string CONST_HAS_BEEN_TAINTED_WITH_WISDOM = " has been tainted with wisdom!";
//const string CONST_EXCLAMATION_POINT = "!";
const string CONST_TURNS_THE_TABLES_ON = " turns the tables on ";
const string CONST_HOLDS_FIRM = " holds firm.";
const string CONST_BEGS_FOR_THE_NIGHTMARE_TO_END = " begs for the nightmare to end.";
const string CONST_CURLS_UP_AND = " curls up and";
const string CONST_TO_STOP_LOOKING_LIKE_HITLER = " to stop looking like Hitler.";
const string CONST_SCREAMS_FOR = " screams for ";
const string CONST_BEGS_HITLER_TO_STAY_AND_KILL = " begs Hitler to stay and kill ";
const string CONST_TALKS_ABOUT_HUGGING = "talks about hugging ";
const string CONST_STAMMERS_AND = " stammers and ";
const string CONST_TAKES_IT_WELL = " takes it well.";
const string CONST_S_WEAKENED_BODY_CRUMBLES_UNDER_THE_BRUTAL_ASSAULT = "'s weakened body crumbles under the brutal assault.";
const string CONST_IS_BADLY_HURT = " is badly hurt.";
const string CONST_SEEMS_TO_BE_GETTING_THE_MESSAGE = " seems to be getting the message.";
const string CONST_A_DETAILED_MAP_HAS_BEEN_CREATED_OF = "A detailed map has been created of ";
const string CONST_BEATS_INFORMATION_OUT_OF_THE_PATHETIC_THING = " beats information out of the pathetic thing.";
const string CONST_WONDERS_ABOUT_DEATH = " wonders about death.";
const string CONST_WONDERS_ABOUT_APPLES = " wonders about apples.";
const string CONST_CRIES_HELPLESSLY = " cries helplessly.";
const string CONST_BARKS_HELPLESSLY = " barks helplessly.";
const string CONST_CURLS_UP_IN_THE_CORNER_AND_DOESN_T_MOVE = " curls up in the corner and doesn't move.";
const string CONST_GOES_LIMP_IN_THE_RESTRAINTS = " goes limp in the restraints.";
const string CONST_MOMMY = "mommy.";
const string CONST_GOD_S_MERCY = "God's mercy.";
const string CONST_JOHN_LENNON_S_MERCY = "John Lennon's mercy.";
const string CONST_SCREAMS_HELPLESSLY_FOR = " screams helplessly for ";
const string CONST_IN_ITS_FACE = "!\" in its face.";
const string EXCLAMATION_POINT_SPACE = "! ";
const string CONST_X_THE_AUTOMATON = " the Automaton";
const string CONST_S_GUARDS_BEAT = "'s guards beat";
const string CONST_BEAT = " beat";
const string CONST_BEATS = " beats";
const string CONST_SCREAMING = "screaming \"";
const string CONST_HAD_A_NEAR_DEATH_EXPERIENCE_AND_MET_JOHN_LENNON = " had a near-death experience and met John Lennon.";
const string CONST_HAD_A_NEAR_DEATH_EXPERIENCE_AND_MET_GOD_IN_HEAVEN = " had a near-death experience and met God in heaven.";
const string CONST_CLUMSILY_RESCUES_IT_FROM_CARDIAC_ARREST_WITH_A_DEFIBRILLATOR = " clumsily rescues it from cardiac arrest with a defibrillator.";
const string CONST_FROM_ANY_HEALTH_DAMAGE = " from any health damage.";
const string CONST_SKILLFULLY_SAVES = " skillfully saves ";
const string CONST_DEFTLY_RESCUES_IT_FROM_CARDIAC_ARREST_WITH_A_DEFIBRILLATOR = " deftly rescues it from cardiac arrest with a defibrillator.";
const string CONST_S_INCOMPETENCE_AT_FIRST_AID = "'s incompetence at first aid.";
const string CONST_DIES_DUE_TO = " dies due to ";
const string CONST_S_WEAKENED_STATE = "'s weakened state.";
const string CONST_IT_IS_A_LETHAL_OVERDOSE_IN = "It is a lethal overdose in ";
const string CONST_PANTS = " pants.";
const string CONST_HAS_A_PANIC_ATTACK_AND_SHITS = " has a panic attack and shits ";
const string CONST_HAS_A_PANIC_ATTACK_AND_MAKES_A_STINKY = " has a panic attack and [makes a stinky].";
const string CONST_FLATLINES = " flatlines.";
const string CONST_USES_A_DEFIBRILLATOR_REPEATEDLY_BUT = " uses a defibrillator repeatedly but ";
const string CONST_FOAMS_AT_THE_MOUTH_AND_ITS_EYES_ROLL_BACK_IN_ITS_SKULL = " foams at the mouth and its eyes roll back in its skull.";
const string CONST_IT_IS_SUBJECTED_TO_DANGEROUS_HALLUCINOGENS = "It is subjected to dangerous hallucinogens.";
const string CONST_CONVERTED_INTO_A_MAKESHIFT_CELL = "converted into a makeshift cell.";
const string CONST_IS_LOCKED_IN_A_BACK_ROOM = " is locked in a back room ";
const string CONST_IN_THE_MIDDLE_OF_A_BACK_ROOM = "in the middle of a back room.";
const string CONST_IS_TIED_HANDS_AND_FEET_TO_A_METAL_CHAIR = " is tied hands and feet to a metal chair";
const string CONST_THE_AUTOMATON = "The Automaton";
const string CONST_DAY = ": Day ";
const string CONST_X_THE_EDUCATION_OF_ = "The Education of ";
const string CONST_IN_COLD_BLOOD = " in cold blood.";
const string CONST_EXECUTE = "execute ";
const string CONST_THERE_IS_NO_ONE_ABLE_TO_GET_UP_THE_NERVE_TO = "There is no one able to get up the nerve to ";
const string CONST_BY = " by ";
const string CONST_EXECUTES = " executes ";
const string CONST_THE_FINAL_EDUCATION_OF = "The Final Education of ";
const string CONST_PRESS_ENTER_TO_CONFIRM_THE_PLAN = "Press Enter to Confirm the Plan";
const string CONST_K_KILL_THE_HOSTAGE = "K - Kill the Hostage";
const string CONST_50 = "($50)";
const string CONST_HALLUCINOGENIC_DRUGS = "Hallucinogenic Drugs    ";
const string CONST_NO = "No ";
const string CONST_E = "E - ";
const string CONST_250 = "($250)";
const string CONST_EXPENSIVE_PROPS = "Expensive Props     ";
const string CONST_D = "D - ";
const string CONST_VIOLENTLY_BEATEN = "Violently Beaten    ";
const string CONST_NOT = "Not ";
const string CONST_C = "C - ";
const string CONST_PHYSICAL_RESTRAINTS = "Physical Restraints   ";
const string CONST_B = "B - ";
const string CONST_ATTEMPT_TO_CONVERT = "Attempt to Convert";
const string CONST_NO_VERBAL_CONTACT = "No Verbal Contact     ";
const string CONST_A = "A - ";
const string CONST_SELECTING_A_LIBERAL_INTERROGATION_PLAN = "Selecting a Liberal Interrogation Plan";
const string CONST_THE_EXECUTION_OF_AN_AUTOMATON = "The Execution of an Automaton         ";
const string CONST_X_MURDER_SPACE = "murder ";
const string CONST_THE_CONSERVATIVE_WOULD_LIKE_TO = "The Conservative would like to ";
const string CONST_THE_CONSERVATIVE_HATES = "The Conservative hates ";
const string CONST_TOWARD = "toward ";
const string CONST_THE_CONSERVATIVE_IS_UNCOOPERATIVE = "The Conservative is uncooperative ";
const string CONST_THE_CONSERVATIVE_LIKES = "The Conservative likes ";
const string CONST_AS_ITS_ONLY_FRIEND = " as its only friend.";
const string CONST_TO = "to ";
const string CONST_THE_CONSERVATIVE_CLINGS_HELPLESSLY = "The Conservative clings helplessly ";
const string CONST_OUTFIT = "Outfit: ";
const string CONST_WISDOM = "Wisdom: ";
const string HEART_COLON = "Heart: ";
const string CONST_PSYCHOLOGY_SKILL = "Psychology Skill: ";
const string CONST_HEALTH = "Health: ";
const string CONST_LEAD_INTERROGATOR = "Lead Interrogator: ";
const string CONST_PRISONER = "Prisoner: ";
const string CONST_34_SPACES = "                                  ";
const string CONST_CLING_TO_SCIENCE_TXT = "cling_to_science.txt";
const string CONST_CLING_TO_BUSINESS_TXT = "cling_to_business.txt";
const string CONST_CLING_TO_SCIENCE_ONE_LINE_TXT = "cling_to_science_one_line.txt";
const string CONST_CLING_TO_BUSINESS_ONE_LINE_TXT = "cling_to_business_one_line.txt";
const string CONST_VANILLA_RECRUIT_TXT = "vanilla_recruit.txt";
const string CONST_DISCUSS_TXT = "discuss.txt";
const string CONST_CLING_TO_RELIGION_ONE_LINE_TXT = "cling_to_religion_one_line.txt";
const string CONST_CLING_TO_RELIGION_TXT = "cling_to_religion.txt";
const string CONST_CLINGING_ONE_LINE_TXT = "clinging_one_line.txt";
const string CONST_CLING_TO_INTERROGATER_TXT = "cling_to_interrogater.txt";
const string CONST_INTERROGATER_SHOWS_COMPASSION_TXT = "interrogater_shows_compassion.txt";
const string CONST_INTERROGATER_SHOWS_COMPASSION_ONE_LINE_TXT = "interrogater_shows_compassion_one_line.txt";
const string CONST_DEVELOPS_HATRED_TXT = "develops_hatred.txt";
const string CONST_DEVELOPS_HATRED_ONE_LINE_TXT = "develops_hatred_one_line.txt";
const string CONST_SMARTER_THAN_YOU_TXT = "smarter_than_you.txt";
const string CONST_SMARTER_THAN_YOU_ONE_LINE_TXT = "smarter_than_you_one_line.txt";
const string CONST_GOOD_TRIP_COMPANION_TXT = "good_trip_companion.txt";
const string CONST_BAD_TRIP_TXT = "bad_trip.txt";
const string CONST_FALL_IN_LOVE_TXT = "fall_in_love.txt";
const string CONST_GOOD_TRIP_TXT = "good_trip.txt";
const string CONST_SELF_WOUNDING_TXT = "self_wounding.txt";
const string CONST_BROODS_OVER_DEATH_TXT = "broods_over_death.txt";
const string CONST_PARTIAL_CONVERSION_TXT = "partial_conversion.txt";
const string CONST_RESIST_DRUGS_TXT = "resist_drugs.txt";
const string CONST_USE_PROPS_TXT = "use_props.txt";
const string CONST_PRAYS_ON_DRUGS_TXT = "prays_on_drugs.txt";
const string CONST_PRAYS_TXT = "prays.txt";
const string CONST_WORDS_TO_SCREAM_TXT = "words_to_scream.txt";
const string CONST_WORDS_MEANING_SCREAMING_TXT = "words_meaning_screaming.txt";
const string CONST_BEAT_WITH_PROPS_TXT = "beat_with_props.txt";
const string CONST_SCREAMING_TXT = "screaming.txt";
const string CONST_LOW_HEART_TORTURE_PROPS_TXT = "low_heart_torture_props.txt";
const string CONST_FEELS_SICK_TXT = "feels_sick.txt";
const string CONST_EXECUTION_TXT = "execution.txt";

const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

#include "../creature/creature.h"
#include "../locations/locationsEnums.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../log/log.h"
#include "../common/commondisplayCreature.h"
// for void printhealthstat(Creature &,int,int,char);
#include "../common/getnames.h"
// for std::string getview(short ,bool );
#include "../common/commonactionsCreature.h"
// for  void sleeperize_prompt(Creature &,Creature &,int);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/creaturePoolCreature.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"

extern Log gamelog;
// Interrogation always enlightens
extern bool AUTOENLIGHTEN;
extern MusicClass music;
extern int stat_recruits;
extern int stat_kills;
extern class Ledger ledger;
extern short lawList[LAWNUM];

vector<string> execution;
vector<string> feels_sick;
vector<string> low_heart_torture_props;
vector<string> screaming;
vector<string> beat_with_props;
vector<string> words_meaning_screaming;
vector<string> words_to_scream;
vector<string> prays;
vector<string> prays_on_drugs;
vector<string> use_props;
vector<string> resist_drugs;
vector<string> partial_conversion;
vector<string> broods_over_death;
vector<string> self_wounding;
vector<string> good_trip;
vector<vector<string> > fall_in_love;
vector<vector<string> > bad_trip;
vector<vector<string> > good_trip_companion;
vector<string> smarter_than_you_one_line;
vector<vector<string> > smarter_than_you;
vector<string> develops_hatred_one_line;
vector<vector<string> > develops_hatred;
vector<string> interrogater_shows_compassion_one_line;
vector<vector<string> > interrogater_shows_compassion;
vector<vector<string> > cling_to_interrogater;
vector<string> clinging_one_line;
vector<vector<string> > cling_to_religion;
vector<string> cling_to_religion_one_line;
vector<vector<string> > discuss;
vector<string> vanilla_recruit;
vector<vector<string> > cling_to_business;
vector<vector<string> > cling_to_science;
vector<string> cling_to_business_one_line;
vector<string> cling_to_science_one_line;
const int DOUBLE_LINE = 2;
vector<file_and_text_collection> interrogate_text_file_collection = {
	/*InterrogationST.cpp*/
	customText(&execution, interrogate + CONST_EXECUTION_TXT),
	customText(&feels_sick, interrogate + CONST_FEELS_SICK_TXT),
	customText(&low_heart_torture_props, interrogate + CONST_LOW_HEART_TORTURE_PROPS_TXT),
	customText(&screaming, interrogate + CONST_SCREAMING_TXT),
	customText(&beat_with_props, interrogate + CONST_BEAT_WITH_PROPS_TXT),
	customText(&words_meaning_screaming, interrogate + CONST_WORDS_MEANING_SCREAMING_TXT),
	customText(&words_to_scream, interrogate + CONST_WORDS_TO_SCREAM_TXT),
	customText(&prays, interrogate + CONST_PRAYS_TXT),
	customText(&prays_on_drugs, interrogate + CONST_PRAYS_ON_DRUGS_TXT),
	customText(&use_props, interrogate + CONST_USE_PROPS_TXT),
	customText(&resist_drugs, interrogate + CONST_RESIST_DRUGS_TXT),
	customText(&partial_conversion, interrogate + CONST_PARTIAL_CONVERSION_TXT),
	customText(&broods_over_death, interrogate + CONST_BROODS_OVER_DEATH_TXT),
	customText(&self_wounding, interrogate + CONST_SELF_WOUNDING_TXT),
	customText(&good_trip, interrogate + CONST_GOOD_TRIP_TXT),
	customText(&fall_in_love, interrogate + CONST_FALL_IN_LOVE_TXT, DOUBLE_LINE),
	customText(&bad_trip, interrogate + CONST_BAD_TRIP_TXT, DOUBLE_LINE),
	customText(&good_trip_companion, interrogate + CONST_GOOD_TRIP_COMPANION_TXT, DOUBLE_LINE),
	customText(&smarter_than_you_one_line, interrogate + CONST_SMARTER_THAN_YOU_ONE_LINE_TXT),
	customText(&smarter_than_you, interrogate + CONST_SMARTER_THAN_YOU_TXT, DOUBLE_LINE),
	customText(&develops_hatred_one_line, interrogate + CONST_DEVELOPS_HATRED_ONE_LINE_TXT),
	customText(&develops_hatred, interrogate + CONST_DEVELOPS_HATRED_TXT, DOUBLE_LINE),
	customText(&interrogater_shows_compassion_one_line, interrogate + CONST_INTERROGATER_SHOWS_COMPASSION_ONE_LINE_TXT),
	customText(&interrogater_shows_compassion, interrogate + CONST_INTERROGATER_SHOWS_COMPASSION_TXT, DOUBLE_LINE),
	customText(&cling_to_interrogater, interrogate + CONST_CLING_TO_INTERROGATER_TXT, DOUBLE_LINE),
	customText(&clinging_one_line, interrogate + CONST_CLINGING_ONE_LINE_TXT),
	customText(&cling_to_religion, interrogate + CONST_CLING_TO_RELIGION_TXT, DOUBLE_LINE),
	customText(&cling_to_religion_one_line, interrogate + CONST_CLING_TO_RELIGION_ONE_LINE_TXT),
	customText(&discuss, interrogate + CONST_DISCUSS_TXT, DOUBLE_LINE),
	customText(&vanilla_recruit, interrogate + CONST_VANILLA_RECRUIT_TXT),
	customText(&cling_to_business_one_line, interrogate + CONST_CLING_TO_BUSINESS_ONE_LINE_TXT),
	customText(&cling_to_science_one_line, interrogate + CONST_CLING_TO_SCIENCE_ONE_LINE_TXT),
	customText(&cling_to_business, interrogate + CONST_CLING_TO_BUSINESS_TXT, DOUBLE_LINE),
	customText(&cling_to_science, interrogate + CONST_CLING_TO_SCIENCE_TXT, DOUBLE_LINE),
};

enum InterrogationTechnqiues
{
	TECHNIQUE_TALK,
	TECHNIQUE_RESTRAIN,
	TECHNIQUE_BEAT,
	TECHNIQUE_PROPS,
	TECHNIQUE_DRUGS,
	TECHNIQUE_KILL
};
string getDespairString(const bool drugs, const bool restrain, const bool religion);
string victimPrays(const bool onDrugs);
string getFallsInLove(const string name, const bool restrain);
string getBadTrip(const string name, const bool restrain, const bool rapport);
string outPsychologyCaptor(const string name);
string triedConvertingTheAbused(const string name);
string feelsBadForAbused(const string name);
string stockholmSyndrome(const string name);
string failToBreakReligion(const string a, const string cr);
string failedToBreakBusiness(const string a, const string cr);
string failedToBreakScience(const string a, const string cr);
//#endif//INTERROGATION_CPP
//#endif// INCLUDES_H_INCLUDED
