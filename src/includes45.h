




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

#include "includesSDS.h"
//#include "includesDeprecatedB.h"
//#ifdef	ACTIVITIES_CPP
// activities.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../basemode/activate.h"
// for armor_makedifficulty
#include "../items/loottype.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for addstr
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void criminalize(Creature &,short);
#include "../common/getnames.h"
// for std::string getview(short, bool)
#include "../politics/politics.h"
//for int publicmood(int l);
#include "../combat/chase.h"
#include "../combat/chaseCreature.h"
//for void makechasers(long sitetype,long sitecrime);
#include "../combat/fightCreature.h"  

#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../items/lootTypePoolItem.h"
#include "../common/creaturePool.h"


void doActivitySolicitDonations(vector<DeprecatedCreature *> &solicit, char &clearformess);
void doActivitySellTshirts(vector<DeprecatedCreature *> &tshirts, char &clearformess);
void doActivitySellArt(vector<DeprecatedCreature *> &art, char &clearformess);
void doActivitySellMusic(vector<DeprecatedCreature *> &music, char &clearformess);
void doActivitySellBrownies(vector<DeprecatedCreature *> &brownies, char &clearformess);
void doActivityHacking(vector<DeprecatedCreature *> &hack, char &clearformess);
void doActivityGraffiti(vector<DeprecatedCreature *> &graffiti, char &clearformess);
void doActivityProstitution(vector<DeprecatedCreature *> &prostitutes, char &clearformess);
void doActivityLearn(vector<DeprecatedCreature *> &students, char &clearformess);
void doActivityTrouble(vector<DeprecatedCreature *> &trouble, char &clearformess);
void doActivityTeach(vector<DeprecatedCreature *> &teachers, char &clearformess);
void doActivityBury(vector<DeprecatedCreature *> &bury, char &clearformess);

void addLootToLoc(int loc, Item* it);
char tryFindCloth(int cursite);
string wasUnableToFind(const string old);
string considerLeaving(const bool sensealarm, const bool alarmon, const string name);
extern bool SHOWMECHANICS;
extern char endgamestate;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char newscherrybusted;
extern chaseseqst chaseseq;
extern class Ledger ledger;
extern Deprecatednewsstoryst *sitestory;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short exec[EXECNUM];
extern short fieldskillrate;
extern short interface_pgdn;
extern short interface_pgup;
extern short lawList[LAWNUM];
extern short mode;
extern short public_interest[VIEWNUM];
extern vector<ArmorType *> armortype;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatednewsstoryst *> newsstory;
extern vector<Deprecatedsquadst *> squad;
static const char SURVEY_PAGE_SIZE = 14;
string gimmeASprayCan(DeprecatedCreature* graffiti);
Vehicle* getVehicleOfThisType(int cartype);
void buyMeASprayCan(DeprecatedCreature* graffiti);
void newVehicle(Vehicle *startcar);

enum CarHotwireMethod {
	UNDETERMINED,
	ATTEMPT_HOTWIRE,
	USE_KEYS
};


const string CONST_X_CAN = " can.";
const string CONST_X_HAS_LEARNED_AS_MUCH_AS_ = " has learned as much as ";

const string tag_POLICECAR = "POLICECAR";
const string tag_WEAPON_SPRAYCAN = "WEAPON_SPRAYCAN";
const string tag_WEAPON = "WEAPON";
const string CONST_X_HAS_ = " has ";
const string CONST_X_EXCLAMATION_POINT = "!";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string CONST_X_PERUSES_MAGAZINES = " peruses some sewing magazines.";
const string CONST_X_CLEANS_KITCHEN = " cleans the kitchen.";
const string CONST_X_REORGANIZES_CLOSET = " reorganizes the armor closet.";
const string CONST_X_TIDIES_SAFEHOUSE = " tidies up the safehouse.";
const string CONST_X_RUINED = " ruined";
const string CONST_X_REPAIRS_SOMEWHAT = " repairs what little can be fixed of ";
const string CONST_X_NO_HOPE_TO_REPAIR = " finds there is no hope of repairing ";
const string CONST_X_REPAIRS = " repairs ";
const string CONST_X_IS_WORKING_TO_REPAIR = " is working to repair ";
const string CONST_X_CLEANS = " cleans ";
const string CONST_X_DISPOSES_OF = " disposes of ";
const string CONST_X_WASTED_MATERIALS = " wasted the materials for a";
const string CONST_X_TH_RATE = "th-rate";
const string CONST_X_FOURTH_RATE = "fourth-rate";
const string CONST_X_THIRD_RATE = "third-rate";
const string CONST_X_SECOND_RATE = "second-rate";
const string CONST_X_FIRST_RATE = "first-rate";
const string CONST_X_HAS_MADE_A = " has made a ";
const string CONST_X_CANNOT_FIND_CLOTH = " cannot find enough cloth to reduce clothing costs.";
const string CONST_X_CANNOT_AFFORD_MATERIAL = " cannot afford material for clothing.";
const string CONST_X_LITTLE_WHITESPACE = "    ";
const string CONST_X_ENTER_DONE = "Enter - Done";
const string CONST_X_LIBERAL_PERCENTAGE_POINTS = " Liberal percentage points.";
const string CONST_X_RESULTS_ARE_PLUS_MINUS = "Results are +/- ";
const string CONST_X_ISSUE_PUBLIC_INTEREST_HEADER = "XX% Issue 컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴?ublic Interest";
const string CONST_X_ADDITIONAL_FINDINGS = "Additional notable findings:";
const string CONST_X_AMNESTY_FOR_IMMIGRANTS = "wanted amnesty for illegal immigrants";
const string CONST_X_CONDEMN_IMMIGRATION_REGULATIONS = "condemned unnecessary immigration regulations";
const string CONST_X_BELIEVE_IN_LEGAL_MARIJUANA = "believed in legalizing marijuana";
const string CONST_X_SUPPORTED_MARIJUANA_LEGAL = "supported keeping marijuana legal";
const string CONST_X_PERCENT_SIGN = "% ";
const string CONST_X_TWO_QUESTION_MARKS = "??";
const string CONST_X_NONE_SPACE = "None     ";
const string CONST_X_LOW = "Low      ";
const string CONST_X_MODERATE = "Moderate ";
const string CONST_X_HIGH = "High     ";
const string CONST_X_VERY_HIGH = "Very High";
const string CONST_X_UNKNOWN = "Unknown  ";
const string CONST_X_MANY_DOTS = "........................................................";
const string CONST_X_LOTS_OF_WHITESPACE = "                                                                                ";
const string CONST_X_LIBERAL_MEDIA_BIAS = "Liberal Media Bias.";
const string CONST_X_CONSERVATIVE_MEDIA_BIAS = "Conservative Media Bias.";
const string CONST_X_THE_LCS_TERRORISTS = "the LCS terrorists.";
const string CONST_X_THE_LIBERAL_CRIME_SQUAD = "the Liberal Crime Squad.";
const string CONST_X_ACTIVIST_POLITICAL_GROUPS = "activist political groups.";
const string CONST_X_THE_PUBLIC_IS_UNCONCERNED = "The public is not concerned with politics right now.";

const string CONST_X_TAKING_STRONG_ACTION = "taking strong action.";
const string CONST_X_THE_PEOPLE_ARE_MOST_CONCERNED = "The people are most concerned about ";
const string CONST_X_PRESIDENT = "President ";
const string CONST_X_HAD_FAVORABLE_OPINION = "% had a favorable opinion of ";
const string CONST_X_SURVEY_OF_PUBLIC_OPINION = "Survey of Public Opinion, According to Recent Polls";
const string CONST_X_IS_ACCOSTED_BY_POLICE = " is accosted by police while ";
const string CONST_X_SOLICITING_DONATIONS = "soliciting donations";
const string CONST_X_SELLING_SHIRTS = "selling shirts";
const string CONST_X_SKETCHING_PORTRAITS = "sketching portraits";

const string CONST_X_PLAYING_MUSIC = "playing music";
const string CONST_X_SELLING_BROWNIES = "selling brownies";
const string CONST_X_A_SPACE = " a ";
const string CONST_X_YOUR_HACKERS_HAVE_LOWERCASE = "Your hackers have ";
const string CONST_X_YOUR_HACKERS_HAVE_ = "Your Hackers have ";
const string CONST_X_HAS_BEGUN_WORK_ON_A_LARGE_MURAL_ABOUT_ = " has begun work on a large mural about ";
const string CONST_X_WORKS_THROUGH_THE_NIGHT_ON_A_LARGE_MURAL = " works through the night on a large mural.";
const string CONST_X_MURAL_ABOUT_ = " mural about ";
const string CONST_X_BEAUTIFUL = " beautiful";
const string CONST_X_HAS_COMPLETED_A = " has completed a";
const string CONST_X_WHILE_SPRAYING_AN_LCS_TAG = " while spraying an LCS tag!";
const string CONST_X_WHILE_WORKING_ON_THE_MURAL = " while working on the mural!";
const string CONST_X_WAS_SPOTTED_BY_THE_POLICE = " was spotted by the police";
const string CONST_X_NEEDS_A_SPRAYCAN_EQUIPPED_TO_DO_GRAFFITI = " needs a spraycan equipped to do graffiti.";
const string CONST_X_BOUGHT_SPRAYPAINT_FOR_GRAFFITI = " bought spraypaint for graffiti.";
const string CONST_X_FROM_ = " from ";
const string CONST_X_GRABBED_A_ = " grabbed a ";
const string CONST_X_WAS_NEARLY_CAUGHT_IN_A_PROSTITUTION_STING = " was nearly caught in a prostitution sting.";
const string CONST_X_HAS_BEEN_ARRESTED_IN_A_PROSTITUTION_STING = " has been arrested in a prostitution sting.";
const string CONST_X_SET_UP_A_MOCK_SWEATSHOP_IN_THE_MIDDLE_OF_THE_MALL = "set up a mock sweatshop in the middle of the mall!";
const string CONST_X_BURNED_A_CORPORATE_SYMBOL_AND_DENOUNCED_CAPITALISM = "burned a corporate symbol and denounced capitalism!";
const string CONST_X_DISTRIBUTED_FLIERS_GRAPHICALLY_ILLUSTRATING_CIA_TORTURE = "distributed fliers graphically illustrating CIA torture!";
const string CONST_X_DISTRIBUTED_FLIERS_GRAPHICALLY_ILLUSTRATING_EXECUTIONS = "distributed fliers graphically illustrating executions!";
const string CONST_X_SQUIRTED_BUSINESS_PEOPLE_WITH_FAKE_POLLUTED_WATER = "squirted business people with fake polluted water!";
const string CONST_X_DRESSED_UP_AND_PRETENDED_TO_BE_A_RADIOACTIVE_MUTANT = "dressed up and pretended to be a radioactive mutant!";
const string CONST_X_DRESSED_UP_AND_PRETENDED_TO_BE_RADIOACTIVE_MUTANTS = "dressed up and pretended to be radioactive mutants!";
const string CONST_X_GONE_DOWNTOWN_AND_REENACTED_A_POLICE_BEATING = "gone downtown and reenacted a police beating!";
const string CONST_X_POSTED_HORRIFYING_DEAD_ABORTION_DOCTOR_PICTURES_DOWNTOWN = "posted horrifying dead abortion doctor pictures downtown!";
const string CONST_X_DISRUPTED_A_TRADITIONAL_WEDDING_AT_A_CHURCH = "disrupted a traditional wedding at a church!";
const string CONST_X_RUN_AROUND_UPTOWN_SPLASHING_PAINT_ON_FUR_COATS = "run around uptown splashing paint on fur coats!";
const string CONST_X_BROKEN = "broken!";
const string CONST_X_S_LAST_UNBROKEN_RIB_IS_ = "'s last unbroken rib is ";
const string CONST_X_S_RIB_IS_ = "'s rib is ";
const string CONST_X_ONE_OF_ = "One of ";
const string CONST_X_S_RIBS_ARE_ = "'s ribs are ";
const string CONST_X_OF_ = " of ";
const string CONST_X_ALL_SPACE = "All ";
const string CONST_X_S_TOOTH_HAS_BEEN_PULLED_OUT_WITH_PLIERS = "'s tooth has been pulled out with pliers!";
const string CONST_X_S_TEETH_HAVE_BEEN_SMASHED_OUT_ON_THE_CURB = "'s teeth have been smashed out on the curb.";
const string CONST_X_S_NECK_HAS_BEEN_BROKEN = "'s neck has been broken!";
const string CONST_X_S_UPPER_SPINE_HAS_BEEN_BROKEN = "'s upper spine has been broken!";
const string CONST_X_S_LOWER_SPINE_HAS_BEEN_BROKEN = "'s lower spine has been broken!";
const string CONST_X_IS_SEVERELY_BEATEN_BEFORE_THE_MOB_IS_BROKEN_UP = " is severely beaten before the mob is broken up.";
const string CONST_X_OUT_OF_EVERYONE_WHO_GOT_CLOSE = " out of everyone who got close!";
const string CONST_X_SHIT = "shit";
const string CONST_X_TAR = "[tar]";
const string CONST_X_BEAT_THE = " beat the ";
const string CONST_X_THE_MOB_SCATTERS = "The mob scatters!";
const string CONST_X_BRANDISHES_THE_ = " brandishes the ";
const string CONST_X_IS_CORNERED_BY_A_MOB_OF_ANGRY_REDNECKS = " is cornered by a mob of angry rednecks.";
const string CONST_X_CAUSING_TROUBLE = "causing trouble";
const string CONST_X_YOUR_ACTIVISTS_HAVE_ = "Your Activists have ";
const string CONST_X_PRESS_A_LETTER_TO_SELECT_A_TYPE_OF_CAR = "Press a Letter to select a Type of Car";
const string CONST_X_TYPEDIFFICULTY_TO_FIND_UNATTENDED = "컴컴TYPE컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴DIFFICULTY TO FIND UNATTENDED컴";
const string CONST_X_TRY_TO_FIND_AND_STEAL_TODAY = " try to find and steal today?";
const string CONST_X_WHAT_TYPE_OF_CAR_WILL_ = "What type of car will ";
const string CONST_X_STANDS_BY_THE_ = " stands by the ";
const string CONST_X_THIS_IS_THE_VIPER_STAND_AWAY = "THIS IS THE VIPER!   STAND AWAY!";
const string CONST_X_THE_VIPER_COLON = "THE VIPER:   ";
const string CONST_X_STAND_AWAY_FROM_THE_VEHICLE_BEEP_BEEP = "STAND AWAY FROM THE VEHICLE!   <BEEP!!> <BEEP!!>";
const string CONST_X_BEEP_BEEP_BEEP_BEEP = "<BEEP!!> <BEEP!!> <BEEP!!> <BEEP!!>";
const string CONST_X_COLON_SPACE_SPACE = ":   ";
const string CONST_X_THE_VIPER = "THE VIPER";
const string CONST_X_B_BREAK_THE_WINDOW = "B - Break the window.";
const string CONST_X_A_PICK_THE_LOCK = "A - Pick the lock.";
const string CONST_X_BUT_IT_IS_STILL_SOMEWHAT_INTACT = " but it is still somewhat intact.";
const string CONST_X_WITH_A_ = " with a ";
const string CONST_X_CRACKS_THE_WINDOW = " cracks the window";
const string CONST_X_SMASHES_THE_WINDOW = " smashes the window";
const string CONST_X_FIDDLES_WITH_THE_LOCK_WITH_NO_LUCK = " fiddles with the lock with no luck.";
const string CONST_X_AN_ALARM_SUDDENLY_STARTS_BLARING = "An alarm suddenly starts blaring!";
const string CONST_X_JIMMIES_THE_CAR_DOOR_OPEN = " jimmies the car door open.";
const string CONST_X_HAS_BEEN_SPOTTED_BY_A_PASSERBY = " has been spotted by a passerby!";

const string CONST_X_ADVENTURES_IN_LIBERAL_CAR_THEFT = "Adventures in Liberal Car Theft";

const string CONST_X_IF_THEY_WERE_HERE_ID_HAVE_FOUND_THEM_BY_NOW = "If they were here, I'd have found them by now.";
const string CONST_X_I_DONT_THINK_THEYRE_IN_HERE = "I don't think they're in here...";
const string CONST_X_ARE_THEY_EVEN_IN_HERE = "Are they even in here?";
const string CONST_X_RUMMAGING_ = ": <rummaging> ";
const string CONST_X_FOUND_THE_KEYS = " found the keys ";
const string CONST_X_HOLY_SHIT_ = "Holy shit!  ";
const string CONST_X_HOLY_CAR_KEYS_ = "Holy [Car Keys]!  ";
const string CONST_X_UNDER_THE_BACK_SEAT = "under the back seat!";
const string CONST_X_UNDER_THE_FRONT_SEAT = "under the front seat!";
const string CONST_X_IN_THE_GLOVE_COMPARTMENT = "in the glove compartment!";
const string CONST_X_ABOVE_THE_PULLDOWN_SUNBLOCK_THINGY = "above the pull-down sunblock thingy!";
const string CONST_X_IN_THE_IGNITION_DAMN = "in the ignition.  Damn.";
const string CONST_X_IN_SPACE_WITH_ALIENS_SERIOUSLY = "in SPACE. With ALIENS. Seriously.";

const string CONST_X_HOTWIRES_THE_CAR = " hotwires the car!";
const string CONST_X_ENTER_THE_VIPER_HAS_FINALLY_DETERRED_ = "Enter - The Viper has finally deterred ";
const string CONST_CALL_IT_A_DAY_PRESS_ENTER = "Enter - Call it a day.";
const string CONST_X_B_DESPERATELY_SEARCH_FOR_KEYS = "B - Desperately search for keys.";
const string CONST_X_A_HOTWIRE_THE_CAR = "A - Hotwire the car.";


const string CONST_X_REMOVE_YOURSELF_FROM_THE_VEHICLE_BEEP_BEEP = "REMOVE YOURSELF FROM THE VEHICLE!   <BEEP!!> <BEEP!!>";


const string CONST_X_IS_BEHIND_THE_WHEEL_OF_A_ = " is behind the wheel of a ";
const string CONST_X_A_APPROACH_THE_DRIVERS_SIDE_DOOR = "A - Approach the driver's side door.";
const string CONST_X_LOOKS_FROM_A_DISTANCE_AT_AN_EMPTY_ = " looks from a distance at an empty ";
const string CONST_X_FOUND_A = " found a ";
const string CONST_X_LOOKS_AROUND_FOR_AN_ACCESSIBLE_VEHICLE = " looks around for an accessible vehicle...";
const string CONST_X_WAS_UNABLE_TO_GET_A_WHEELCHAIR_MAYBE_TOMORROW = " was unable to get a wheelchair.  Maybe tomorrow...";
const string CONST_X_HAS_PROCURED_A_WHEELCHAIR = " has procured a wheelchair.";
const string ACTIVITIES_FOLDER = "activities\\";

const string CONST_X_CANT_FIND_KEYS_NFS_TXT = "cant_find_keys_no_free_speech.txt";
const string CONST_X_CANT_FIND_KEYS_TXT = "cant_find_keys.txt";
const string CONST_X_ALMOST_HOTWIRE_TXT = "almost_hotwire_car.txt";
const string CONST_X_CANT_HOTWIRE_TXT = "cant_hotwire_car.txt";
const string CONST_X_GETS_NERVOUS_TXT = "gets_nervous.txt";
const string CONST_X_CAR_WONT_START_TXT = "car_wont_start.txt";
const string CONST_X_LOST_HAND_TO_HAND_TXT = "lose_hand_to_hand.txt";
const string CONST_X_WIN_HAND_TO_HAND_TXT = "win_hand_to_hand.txt";
const string CONST_X_ENEMY_WEBSITE_TXT = "enemy_website.txt";
const string CONST_X_WORDS_MEANING_HACKED_TXT = "words_meaning_hacked.txt";
const string CONST_X_QUALITY_50_TXT = "quality_50.txt";
const string CONST_X_QUALITY_35_TXT = "quality_35.txt";
const string CONST_X_QUALITY_20_TXT = "quality_20.txt";
const string CONST_X_QUALITY_0_TXT = "quality_0.txt";
const string CONST_X_S_BODY = "'s body";
const string CONST_X_BURYING_ = "burying ";

//#endif//ACTIVITIES_CPP
//#endif// INCLUDES_H_INCLUDED
