




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


const int BIT1 = (1 << 0);
const int BIT2 = (1 << 1);
const int BIT3 = (1 << 2);
const int BIT4 = (1 << 3);
const int BIT5 = (1 << 4);
const int BIT6 = (1 << 5);
const int BIT7 = (1 << 6);
const int BIT8 = (1 << 7);
const int BIT9 = (1 << 8);
const int BIT10 = (1 << 9);
const int BIT11 = (1 << 10);
const int BIT12 = (1 << 11);
const int BIT13 = (1 << 12);
const int BIT14 = (1 << 13);
const int BIT15 = (1 << 14);
const int BIT16 = (1 << 15);
const int BIT17 = (1 << 16);
const int BIT18 = (1 << 17);
const int BIT19 = (1 << 18);
const int BIT20 = (1 << 19);
const int BIT21 = (1 << 20);
const int BIT22 = (1 << 21);
const int BIT23 = (1 << 22);
const int BIT24 = (1 << 23);
const int BIT25 = (1 << 24);
const int BIT26 = (1 << 25);
const int BIT27 = (1 << 26);
const int BIT28 = (1 << 27);
const int BIT29 = (1 << 28);
const int BIT30 = (1 << 29);
const int BIT31 = (1 << 30);
const int BIT32 = (1 << 31);
const int MAX_PATH_SIZE = 2048;
const int RNG_SIZE = 4;
/* These 6 random number generator functions are implemented in compat.cpp */
unsigned long getSeed();
unsigned long r_num();
long LCSrandom(long max);
void initMainRNG();
void copyRNG(unsigned long(&dest)[RNG_SIZE], unsigned long(&src)[RNG_SIZE]);
void initOtherRNG(unsigned long(&rng)[RNG_SIZE]);
/* Determine size of vectors and any other container that implements the size() function.
This basically includes all types of containers except for the C++11 std::forward_list. */
template <class Container> inline long len(const Container& x)
{
	return x.size();
}
/* Determine array size in pickrandom() and various functions throughout the code.
Only works on actual arrays, not on vectors or other containers. */
template <typename T, size_t N> inline long len(const T(&x)[N])
{
	return N;
}
/* Override of the prior function for null-terminated C-strings as char arrays.
This override allows pickrandom() to pick a random character from a C-string we have as a char array. */
template <size_t N> inline long len(const char(&x)[N])
{
	return strlen(x);
}
/* Override of the prior function for null-terminated C-strings as char pointers.
This override allows pickrandom() to pick a random character from a C-string we have as a char pointer. */
inline long len(const char* x)
{
	return strlen(x);
}
/* Override for when it doesn't work with const in front of the char*
(compilers are weird about template function overrides) */
inline long len(char* x)
{
	return strlen(x);
}
/* Pick a random element from a vector/deque/map/std::string/C++11 std::array/etc. (e.g. a random string from a vector of strings).
It works on any container class that implements the [] operator, size() function, and value_type typename.
This doesn't work if the vector/deque/map/std::string/C++11 std::array/etc. has zero elements. */
template <class Container> inline typename Container::value_type& pickrandom(const Container& x)
{
	return const_cast<typename Container::value_type&>(x[LCSrandom(len(x))]);
}
/* Pick a random element from an array (e.g. a random string from an array of strings).
This doesn't work if the array has zero elements. */
template <typename T, size_t N> inline T& pickrandom(const T(&x)[N])
{
	return const_cast<T&>(x[LCSrandom(len(x))]);
}
/* Pick a random element from a C-string.
Returns '\x0' (null character) for empty string. */
inline char& pickrandom(const char* x)
{
	return const_cast<char&>(x[LCSrandom(len(x))]);
}
/* Override for when it doesn't work with const in front of the char*
(compilers are weird about template function overrides) */
inline char& pickrandom(char* x)
{
	return x[LCSrandom(len(x))];
}
/* Deletes a specified pointer and sets it to NULL. */
template <typename T> inline void delete_and_nullify(T* &o)
{
	delete o;
	o = NULL;
}
/* Deletes and removes a specified pointer from a container. */
template <class Container> inline void delete_and_remove(Container& c, int i)
{
	if (i <= -1) return; // check for invalid index, and don't delete anything in this case
	delete c[i];
	c.erase(c.begin() + i);
}
/* Deletes and removes a specified pointer from 2 containers it's in.
c1 and c2 must not be the same container! */
template <class Container> inline void delete_and_remove(Container& c1, int i1, Container& c2, int i2)
{
	if (i1 <= -1 || i2 <= -1) return; // check for invalid index, and don't delete anything in this case
	if (c1[i1] == c2[i2])
	{ // it's the same pointer, so just delete it once, then remove it from both containers
		delete_and_remove(c1, i1);
		if (c1 != c2 || i1 != i2) c2.erase(c2.begin() + i2); // remove it from 2nd location, unless 2nd location is identical to 1st location
	}
	else
	{ // it's 2 different pointers, so delete them both and remove them from both containers
		delete_and_remove(c1, i1);
		delete_and_remove(c2, i2);
	}
}
/* Deletes and removes all pointers in a container. */
template <class Container> inline void delete_and_clear(Container& c)
{
	while (len(c))
	{
		delete c.back();
		c.pop_back();
	}
}
/* Deletes and removes all pointers that 2 containers have in common. */
template <class Container> inline void delete_and_clear(Container& c1, Container& c2)
{
	for (int i1 = len(c1) - 1; i1 >= 0; i1--)
		for (int i2 = len(c2) - 1; i2 >= 0; i2--)
			if (c1[i1] == c2[i2]) delete_and_remove(c1, i1, c2, i2);
}

#define CH_USE_CP437




const int TAB = 9;
const int ENTER = 10;
const int ESC = 27;
const int SPACEBAR = 32;

class Log;

enum Alignment
{
	ALIGN_ARCHCONSERVATIVE = -2,
	ALIGN_CONSERVATIVE,
	ALIGN_MODERATE,
	ALIGN_LIBERAL,
	ALIGN_ELITELIBERAL,
	ALIGN_STALINIST
};

enum UnlockTypes
{
	UNLOCK_DOOR,
	UNLOCK_CAGE,
	UNLOCK_CAGE_HARD,
	UNLOCK_CELL,
	UNLOCK_SAFE,
	UNLOCK_ARMORY,
	UNLOCK_VAULT,
	UNLOCKNUM
};

enum HackTypes
{
	HACK_SUPERCOMPUTER,
	HACK_VAULT,
	HACKNUM
};

enum SpecialAttacks
{
	ATTACK_CANNON,
	ATTACK_FLAME,
	ATTACK_SUCK,
	ATTACKNUM
};

enum EndGameStatus
{
	ENDGAME_NONE,
	ENDGAME_CCS_APPEARANCE,
	ENDGAME_CCS_ATTACKS,
	ENDGAME_CCS_SIEGES,
	ENDGAME_CCS_DEFEATED,
	ENDGAME_MARTIALLAW,
	ENDGAMENUM
};

enum CCSexposure
{
	CCSEXPOSURE_NONE,
	CCSEXPOSURE_LCSGOTDATA,
	CCSEXPOSURE_EXPOSED,
	CCSEXPOSURE_NOBACKERS,
	CCSEXPOSURENUM
};

const int ARMORFLAG_DAMAGED = BIT1;
const int ARMORFLAG_BLOODY = BIT2;


/* *JDS* I'm making laws an array instead of a bunch
 * of bits which are either on or off. Each charge can be
 * duplicated, for multiple counts, and intense focus
 * for wanted persons.
 */
enum Lawflags
{
	LAWFLAG_TREASON,      // "Treason"
	LAWFLAG_TERRORISM,    // "Terrorism"
	LAWFLAG_MURDER,       // "Murder"
	LAWFLAG_KIDNAPPING,   // "Kidnapping"
	LAWFLAG_BANKROBBERY,  // "Bank robbery"
	LAWFLAG_ARSON,        // "Arson"
	LAWFLAG_BURNFLAG,     // "Flag burning" / "Flag Murder"
	LAWFLAG_SPEECH,       // "Harmful speech"
	LAWFLAG_BROWNIES,     // "Drug dealing"
	LAWFLAG_ESCAPED,      // "Escaping prison"
	LAWFLAG_HELPESCAPE,   // "Releasing prisoners"
	LAWFLAG_JURY,         // "Jury tampering"
	LAWFLAG_RACKETEERING, // "Racketeering"
	LAWFLAG_EXTORTION,    // "Extortion"
	LAWFLAG_ARMEDASSAULT, // "Armed assault"
	LAWFLAG_ASSAULT,      // "Assault"
	LAWFLAG_CARTHEFT,     // "Grand theft auto"
	LAWFLAG_CCFRAUD,      // "Credit card fraud"
	LAWFLAG_THEFT,        // "Theft"
	LAWFLAG_PROSTITUTION, // "Prostitution"
	LAWFLAG_HIREILLEGAL,  // "Hiring illegal aliens" / "Hiring undocumented workers"
	LAWFLAG_COMMERCE,     // "Electronic sabotage"
	LAWFLAG_INFORMATION,  // "Hacking"
	LAWFLAG_BURIAL,       // "Unlawful burial"
	LAWFLAG_BREAKING,     // "Breaking and entering"
	LAWFLAG_VANDALISM,    // "Vandalism"
	LAWFLAG_RESIST,       // "Resisting arrest"
	LAWFLAG_DISTURBANCE,  // "Disturbing the peace"
	LAWFLAG_PUBLICNUDITY, // "Public nudity"
	LAWFLAG_LOITERING,    // "Loitering"
	LAWFLAGNUM
};

/* *JDS* In addition to laws being an array,
 * each law will be associated with a tag_heat value,
 * indicating how much that particular crime draws
 * police attention to the wanted person, and to the
 * LCS as a whole. This is a global array, available
 * at runtime and indexed to the lawflag enum, so that
 * code can dynamically look up these heat values as
 * needed at runtime.
 */


enum AnimalGlosses
{
	ANIMALGLOSS_NONE,//IMPORTANT THAT THIS BE HERE AT ZERO
	ANIMALGLOSS_TANK,
	ANIMALGLOSS_ANIMAL,
	ANIMALGLOSSNUM
};

enum Activity
{
	ACTIVITY_NONE,
	ACTIVITY_VISIT,
	ACTIVITY_HOSTAGETENDING,
	ACTIVITY_TROUBLE,
	ACTIVITY_GRAFFITI,
	ACTIVITY_COMMUNITYSERVICE,
	ACTIVITY_SELL_ART,
	ACTIVITY_SELL_MUSIC,
	ACTIVITY_SELL_TSHIRTS,
	ACTIVITY_DONATIONS,
	ACTIVITY_SELL_DRUGS,
	ACTIVITY_PROSTITUTION,
	ACTIVITY_POLLS,
	ACTIVITY_CCFRAUD,
	ACTIVITY_DOS_RACKET,
	ACTIVITY_DOS_ATTACKS,
	ACTIVITY_HACKING,
	ACTIVITY_REPAIR_ARMOR,
	ACTIVITY_MAKE_ARMOR,
	ACTIVITY_STEALCARS,
	ACTIVITY_WHEELCHAIR,
	ACTIVITY_BURY,
	ACTIVITY_WRITE_BLOG,
	ACTIVITY_WRITE_LETTERS,
	ACTIVITY_WRITE_GUARDIAN,
	ACTIVITY_TEACH_POLITICS,
	ACTIVITY_TEACH_FIGHTING,
	ACTIVITY_TEACH_COVERT,
	ACTIVITY_STUDY_DEBATING,
	ACTIVITY_STUDY_MARTIAL_ARTS,
	ACTIVITY_STUDY_DRIVING,
	ACTIVITY_STUDY_PSYCHOLOGY,
	ACTIVITY_STUDY_FIRST_AID,
	ACTIVITY_STUDY_LAW,
	ACTIVITY_STUDY_DISGUISE,
	ACTIVITY_STUDY_SCIENCE,
	ACTIVITY_STUDY_BUSINESS,
	ACTIVITY_STUDY_GYMNASTICS,
	ACTIVITY_STUDY_MUSIC,
	ACTIVITY_STUDY_ART,
	ACTIVITY_STUDY_TEACHING,
	ACTIVITY_STUDY_WRITING,
	ACTIVITY_STUDY_LOCKSMITHING,
	ACTIVITY_STUDY_COMPUTERS,
	ACTIVITY_STUDY_FENCING,
	ACTIVITY_STUDY_WEAVING,
	ACTIVITY_STUDY_RELIGION,
	ACTIVITY_STUDY_CLUB,
	ACTIVITY_STUDY_STREETSENSE,
	ACTIVITY_STUDY_THROWING,
	ACTIVITY_STUDY_STEALTH,
	ACTIVITY_STUDY_SEDUCTION,
	ACTIVITY_CLINIC,
	ACTIVITY_HEAL,
	ACTIVITY_SLEEPER_LIBERAL,
	ACTIVITY_SLEEPER_CONSERVATIVE,
	ACTIVITY_SLEEPER_SPY,
	ACTIVITY_SLEEPER_RECRUIT,
	ACTIVITY_SLEEPER_SCANDAL,
	ACTIVITY_SLEEPER_EMBEZZLE,
	ACTIVITY_SLEEPER_STEAL,
	ACTIVITY_SLEEPER_JOINLCS,
	ACTIVITY_RECRUITING,
	ACTIVITY_AUGMENT,
	ACTIVITYNUM
};



enum CarChaseObstacles
{
	CARCHASE_OBSTACLE_FRUITSTAND,
	CARCHASE_OBSTACLE_TRUCKPULLSOUT,
	CARCHASE_OBSTACLE_CROSSTRAFFIC,
	CARCHASE_OBSTACLE_CHILD,
	CARCHASE_OBSTACLENUM
};

enum SquadStances
{
	SQUADSTANCE_ANONYMOUS,
	SQUADSTANCE_STANDARD,
	SQUADSTANCE_BATTLECOLORS,
	SQUADSTANCE_MAX
};

const int ENCMAX = 18;
// ENCMAX _HAS_ to be 26 or less, or else there aren't enough letters


enum GameModes
{
	GAMEMODE_TITLE,
	GAMEMODE_BASE,
	GAMEMODE_SITE,
	GAMEMODE_CHASECAR,
	GAMEMODE_CHASEFOOT
};

enum MusicModes
{
	MUSIC_TITLEMODE,
	MUSIC_NEWGAME,
	MUSIC_BASEMODE,
	MUSIC_SIEGE,
	MUSIC_ACTIVATE,
	MUSIC_SLEEPERS,
	MUSIC_STOPEVIL,
	MUSIC_REVIEWMODE,
	MUSIC_LIBERALAGENDA,
	MUSIC_DISBANDED,
	MUSIC_FINANCES,
	MUSIC_CARTHEFT,
	MUSIC_ELECTIONS,
	MUSIC_SHOPPING,
	MUSIC_SITEMODE,
	MUSIC_SUSPICIOUS,
	MUSIC_ALARMED,
	MUSIC_HEAVYCOMBAT,
	MUSIC_DEFENSE,
	MUSIC_CONQUER,
	MUSIC_CARCHASE,
	MUSIC_FOOTCHASE,
	MUSIC_INTERROGATION,
	MUSIC_TRIAL,
	MUSIC_RECRUITING,
	MUSIC_DATING,
	MUSIC_NEWSPAPER,
	MUSIC_LACOPS,
	MUSIC_NEWSCAST,
	MUSIC_GLAMSHOW,
	MUSIC_ANCHOR,
	MUSIC_ABORT,
	MUSIC_VICTORY,
	MUSIC_DEFEAT,
	MUSIC_REAGANIFIED,
	MUSIC_STALINIZED,
	MUSIC_OFF, // this one must come immediately after the ones corresponding to music files (this one is to have silence)
	MUSIC_PREVIOUS, // this one must come after MUSIC_OFF (this one is to play the previous song)
	MUSIC_CURRENT, // this one must come after MUSIC_OFF (this one continues playing the current song)
	MUSIC_RANDOM // this one must come after MUSIC_OFF (this one plays a random song)
};

enum WinConditions
{
	WINCONDITION_ELITE,
	WINCONDITION_EASY
};
enum FieldSkillRates
{
	FIELDSKILLRATE_FAST,
	FIELDSKILLRATE_CLASSIC,
	FIELDSKILLRATE_HARD
};

enum Views
{
	VIEW_STALIN = -2, // this one is -2 and is actually calculated based on views >=0 and <VIEWNUM-3
	VIEW_MOOD, // this one is -1 and is likewise calculated based on views >=0 and <VIEWNUM-3
	VIEW_GAY, // view #0, the first one that is actually in the attitude[] array
	VIEW_DEATHPENALTY,
	VIEW_TAXES,
	VIEW_NUCLEARPOWER,
	VIEW_ANIMALRESEARCH,
	VIEW_POLICEBEHAVIOR,
	VIEW_TORTURE,
	VIEW_INTELLIGENCE,
	VIEW_FREESPEECH,
	VIEW_GENETICS,
	VIEW_JUSTICES,
	VIEW_GUNCONTROL,
	VIEW_SWEATSHOPS,
	VIEW_POLLUTION,
	VIEW_CORPORATECULTURE,
	VIEW_CEOSALARY,
	VIEW_WOMEN,//XXX: VIEW_ABORTION DOES NOT EXIST
	VIEW_CIVILRIGHTS,
	VIEW_DRUGS,
	VIEW_IMMIGRATION,
	VIEW_MILITARY,
	VIEW_PRISONS,
	//*JDS* I'm using VIEWNUM-5 in a random generator that rolls a
	//random issue, not including the media/politicalviolence ones, and this will
	//break if these stop being the last 4 issues; do a search
	//for VIEWNUM-5 to change it if it needs to be changed.
	VIEW_AMRADIO,
	VIEW_CABLENEWS,
	//THESE THREE MUST BE LAST FOR VIEWNUM-3 TO WORK IN PLACES
	VIEW_LIBERALCRIMESQUAD,
	VIEW_LIBERALCRIMESQUADPOS,
	//THIS ONE MUST BE LAST. randomissue RELIES ON IT BEING LAST TO IGNORE IT IF
	//CCS IS DEAD.
	VIEW_CONSERVATIVECRIMESQUAD,
	VIEWNUM
};

enum Laws
{
	LAW_STALIN = -2, // not a real law: this is -2 and is actually calculated based on views >=0 and <VIEWNUM-3
	LAW_MOOD, // not a real law: this is -1 and is likewise calculated based on views >=0 and <VIEWNUM-3
	LAW_ABORTION, // law #0, the first one that is actually in the law[] array
	LAW_ANIMALRESEARCH,
	LAW_POLICEBEHAVIOR,
	LAW_PRIVACY,
	LAW_DEATHPENALTY,
	LAW_NUCLEARPOWER,
	LAW_POLLUTION,
	LAW_LABOR,
	LAW_GAY,
	LAW_CORPORATE,
	LAW_FREESPEECH,
	LAW_FLAGBURNING,
	LAW_GUNCONTROL,
	LAW_TAX,
	LAW_WOMEN,
	LAW_CIVILRIGHTS,
	LAW_DRUGS,
	LAW_IMMIGRATION,
	LAW_ELECTIONS,
	LAW_MILITARY,
	LAW_PRISONS,
	LAW_TORTURE,
	LAWNUM
};

enum Crimes
{
	CRIME_STOLEGROUND,
	CRIME_UNLOCKEDDOOR,
	CRIME_BROKEDOWNDOOR,
	CRIME_ATTACKED_MISTAKE,
	CRIME_ATTACKED,
	CRIME_CARCHASE,
	CRIME_CARCRASH,
	CRIME_FOOTCHASE,
	CRIME_KILLEDSOMEBODY,
	CRIME_SHUTDOWNREACTOR,
	CRIME_POLICE_LOCKUP,
	CRIME_COURTHOUSE_LOCKUP,
	CRIME_PRISON_RELEASE,
	CRIME_JURYTAMPERING,
	CRIME_HACK_INTEL,
	CRIME_BREAK_SWEATSHOP,
	CRIME_BREAK_FACTORY,
	CRIME_HOUSE_PHOTOS,
	CRIME_CORP_FILES,
	CRIME_FREE_RABBITS,
	CRIME_FREE_BEASTS,
	CRIME_ARSON,
	CRIME_TAGGING,
	CRIME_ARMORY,
	CRIME_VANDALISM,
	CRIME_BANKVAULTROBBERY,
	CRIME_BANKTELLERROBBERY,
	CRIME_BANKSTICKUP,
	CRIMENUM
};

const int SQUAD_NAMELEN = 40;


enum EndTypes
{
	END_BUT_NOT_END = -2,
	END_OTHER = -1,
	END_WON,
	END_HICKS,
	END_CIA,
	END_POLICE,
	END_CORP,
	END_REAGAN,
	END_DEAD,
	END_PRISON,
	END_EXECUTED,
	END_DATING,
	END_HIDING,
	END_DISBANDLOSS,
	END_DISPERSED,
	END_CCS,
	END_FIREMEN,
	END_STALIN,
	ENDNUM
};

/*
   Declarations for every function grouped by folder and file.
   Created by jonathansfox.
*/

/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);


//

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


enum Bouncer_Reject_Reason
{
	REJECTED_CCS,
	REJECTED_NUDE,
	REJECTED_WEAPONS,
	REJECTED_UNDERAGE,
	REJECTED_FEMALEISH,
	REJECTED_FEMALE,
	REJECTED_BLOODYCLOTHES,
	REJECTED_DAMAGEDCLOTHES,
	REJECTED_CROSSDRESSING,
	REJECTED_GUESTLIST,
	REJECTED_DRESSCODE,
	REJECTED_SECONDRATECLOTHES,
	REJECTED_SMELLFUNNY,
	NOT_REJECTED
};



const string singleDot = ".";
const string string_sleeper = "Sleeper ";
//#ifdef	MAPSPECIALS_CPP
// mapspecials.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../sitemode/advance.h"
#include "../sitemode/miscactions.h"
#include "../sitemode/sitedisplay.h"
#include "../sitemode/stealth.h"
#include "../items/loottype.h"
#include "../items/loot.h"
#include "../items/money.h"
#include "../log/log.h"
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void addjuice(DeprecatedCreature &cr, long juice, long cap);
#include "../common/translateid.h"
// for  int getloottype(int id);
//#include "../combat/fight.h"
void enemyattack();
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
char run_broadcast(bool tv_broadcast);
#include "../common/creaturePool.h"
#include "../common/creaturePoolHeader.h"
void setEncounterZeroExistsFalse();
extern bool deagle;
extern bool m249;
extern CCSexposure ccsexposure;
extern char endgamestate;
extern coordinatest loc_coord;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int sitecrime;
extern Log gamelog;
extern short lawList[LAWNUM];
extern short mode;
extern short postalarmtimer;
extern short sitealarmtimer;
extern short sitealienate;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern vector<ClipType *> cliptype;
extern vector<WeaponType *> weapontype;
void giveActiveSquadMoney(const int money);
int spawnPresident();

/* Used by load() to create items of the correct class. */

bool isThereASiteAlarm();
void setSiteAlarmOne();

void addCrimeToSiteStory(const int crime);
void giveActiveSquadLoot(const string loot);
void claimSiteStory();
vector<NameAndAlignment> getEncounterNameAndAlignment();
void claimSiteStoryOne();
void juiceActiveSquad(const long juice, const long cap);
void giveActiveSquadThisLoot(Item* de);
/* checks if a creature's weapon is suspicious or illegal */
char weaponcheck(const DeprecatedCreature &cr, bool metaldetect = false);
/* checks if a creature's uniform is appropriate to the location */
char hasdisguise(const DeprecatedCreature &cr);
short getCurrentSite();
void make_creature_without_encounter_array(const int x, const short type);
void emptyEncounter();
void fillEncounter(CreatureTypes c, int numleft);
#include "../customMaps.h"
#include "../items/lootTypePoolItem.h"
const string itemClassClip = "clip";
const string itemClassWeapon = "weapon";
const string itemClassArmor = "armor";
const string itemClassLoot = "loot";
const string itemClassMoney = "money";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_GET_THE_FUCK_OUT_OF_HERE = "\"Get the fuck out of here.\"";
const string CONST_GET_THE_HELL_OUT_OF_HERE = "\"Get the hell out of here.\"";
const string CONST_THE_BEST_WAY_NOT_TO_FAIL_IS_TO_SUCCEED = "\"The best way not to fail is to succeed.\"";
const string CONST_GREAT_WORK_IS_DONE_BY_PEOPLE_WHO_DO_GREAT_WORK = "\"Great work is done by people who do great work.\"";

const string CONST_THE_CCS_LEADER_IS_HERE = "The CCS leader is here.";
const string CONST_THE_CCS_LEADER_IS_READY_FOR_YOU = "The CCS leader is ready for you!";
const string CONST_THE_PRESIDENT_IS_IN_THE_OVAL_OFFICE = "The President is in the Oval Office.";
const string CONST_SECRET_SERVICE_AGENTS_AMBUSH_THE_SQUAD = "Secret Service agents ambush the squad!";
const string CONST_THE_PRESIDENT_ISN_T_HERE = "The President isn't here... ";
const string CONST_A_SWAT_TEAM_STORMS_THE_VAULT = "A SWAT team storms the vault!!";
const string CONST_ANOTHER_SWAT_TEAM_MOVES_IN = "Another SWAT team moves in!!";
const string CONST_THE_SQUAD_LOADS_BRICKS_OF_CASH_INTO_A_DUFFEL_BAG = "The squad loads bricks of cash into a duffel bag.";
const string CONST_A_BANK_TELLER_IS_AVAILABLE = "A bank teller is available.";
const string CONST_THE_TELLER_WINDOW_IS_EMPTY = "The teller window is empty.";
const string CONST_THE_SQUAD_HAS_NOBODY_THAT_CAN_DO_THE_JOB = "The squad has nobody that can do the job.";
const string CONST_IS_NO_LONGER_RECOGNIZED = " is no longer recognized.";
const string CONST_AND_WILL_JOIN_THE_ACTIVE_LCS_TO_AVOID_ARREST = "and will join the active LCS to avoid arrest.";
const string CONST_X_OPENS_THE_VAULT_ = " opens the vault, ";
const string CONST_THE_HOSTAGE_IS_FORCED_TO_OPEN_THE_VAULT = "The hostage is forced to open the vault.";
const string CONST_OPENS_THE_VAULT = " opens the vault.";
const string CONST_TO_THE_BANK_S_MANAGERS = "to the bank's managers.";
const string CONST_LAST_IS_THE_BIOMETRIC_LOCK_THAT_KEYED_ONLY = "Last is the biometric lock that keyed only ";
const string CONST_THE_MONEY_WAS_SO_CLOSE_THE_SQUAD_COULD_TASTE_IT = "The money was so close the squad could taste it!";
const string CONST_BE_BYPASSED_BY_A_COMPUTER_EXPERT = "be bypassed by a computer expert.";
const string CONST_NEXT_IS_THE_ELECTRONIC_LOCK_THAT_WILL_HAVE = "Next is the electronic lock that will have ";
const string CONST_ON_THE_OTHER_SIDE_OF_THIS_DOOR = "on the other side of this door...";
const string CONST_THE_SQUAD_CAN_ONLY_DREAM_OF_THE_MONEY = "The squad can only dream of the money ";
const string CONST_BE_CRACKED_BY_A_SECURITY_EXPERT = "be cracked by a security expert.";
const string CONST_FIRST_IS_THE_COMBO_LOCK_THAT_WILL_HAVE = "First is the combo lock that will have ";
const string CONST_OPEN_THE_BANK_VAULT_YES_OR_NO = "Open the bank vault? (Yes or No)";
const string CONST_BUT_YOU_LL_STILL_HAVE_TO_CRACK_THE_OTHER_LOCKS = "but you'll still have to crack the other locks.";
const string CONST_CAN_HANDLE_THE_BIOMETRICS = " can handle the biometrics, ";
const string CONST_EXPERT_AND_ONE_OF_THE_BANK_MANAGERS = "expert, and one of the bank managers.";
const string CONST_YOU_WILL_NEED_A_SECURITY_EXPERT_A_COMPUTER = "You will need a security expert, a computer ";
const string CONST_AN_ELECTRONIC_LOCK_AND_A_BIOMETRIC_LOCK = "an electronic lock, and a biometric lock.";
const string CONST_THE_VAULT_DOOR_HAS_THREE_LAYERS_A_COMBO_LOCK = "The vault door has three layers: A combo lock, ";
const string CONST_BEEEP_BEEEP_BEEEP = "-BEEEP- -BEEEP- -BEEEP-";
const string CONST_JESUS_PUT_SOME_CLOTHES_ON = "\"Jesus! Put some clothes on!\"";
const string CONST_THIS_DOOR_IS_GUARDED = "This door is guarded.";
const string CONST_THE_SQUAD_STEPS_INTO_A_METAL_DETECTOR = "The squad steps into a metal detector.";
const string CONST_THE_SQUAD_FLASHES_ID_BADGES = "The squad flashes ID badges.";
const string CONST_THE_SECURITY_CHECKPOINT_IS_ABANDONED = "The security checkpoint is abandoned.";
const string CONST_SMASH_IT_YES_OR_NO = "Smash it? (Yes or No)";
const string CONST_YOU_SEE_A_DISPLAY_CASE = "You see a display case.";
const string CONST_START_AN_IMPROMPTU_NEWS_PROGRAM_YES_OR_NO = "Start an impromptu news program? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_CABLE_NEWS_BROADCASTING_STUDIO = "You've found a Cable News broadcasting studio.";
const string CONST_TAKE_OVER_THE_STUDIO_YES_OR_NO = " Take over the studio? (Yes or No)";
const string CONST_THEIR_RUSH_TO_GET_OUT = "their rush to get out.";
const string CONST_THE_CABLE_NEWS_BROADCASTERS_LEFT_THE_EQUIPMENT_ON_IN = "The Cable News broadcasters left the equipment on in";
const string CONST_INTERRUPT_THIS_EVENING_S_PROGRAMMING_YES_OR_NO = "Interrupt this evening's programming? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_RADIO_BROADCASTING_ROOM = "You've found a radio broadcasting room.";
const string CONST_THE_RADIO_BROADCASTERS_LEFT_THE_EQUIPMENT_ON_IN = "The radio broadcasters left the equipment on in ";
const string CONST_THE_SQUAD_HAS_FOUND_SOME_VERY_INTERESTING_FILES = "The Squad has found some very interesting files.";
const string CONST_OPEN_IT_YES_OR_NO = "Open it? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_SAFE = "You've found a safe.";
const string CONST_GUARDS_ARE_EVERYWHERE = "Guards are everywhere!";
const string CONST_IT_S_A_TRAP_THE_ARMORY_IS_EMPTY = "It's a trap!  The armory is empty.";
const string CONST_THE_SQUAD_FINDS_SOME_BODY_ARMOR = "The squad finds some body armor.";
const string CONST_THE_SQUAD_FINDS_SOME_M4_CARBINES = "The squad finds some M4 Carbines.";
const string CONST_THE_SQUAD_FINDS_SOME_M16_ASSAULT_RIFLES = "The squad finds some M16 Assault Rifles.";
const string CONST_JACKPOT_THE_SQUAD_FOUND_A_M249_MACHINE_GUN = "Jackpot! The squad found a M249 Machine Gun!";
const string CONST_ALARMS_GO_OFF_EXCLAMATION = "Alarms go off!";
const string CONST_BREAK_IN_YES_OR_NO = "Break in? (Yes or No)";
const string CONST_YOU_VE_FOUND_THE_ARMORY = "You've found the armory.";
const string CONST_WOW_IT_S_EMPTY_THAT_SUCKS = "Wow, it's empty.  That sucks.";
const string CONST_THESE_DOCUMENTS_SHOW_SERIOUS_TAX_EVASION = "These documents show serious tax evasion.";
const string CONST_THE_SQUAD_WILL_TAKE_THOSE = "The squad will take those.";
const string CONST_WOW_GET_A_LOAD_OF_THESE_LOVE_LETTERS = "Wow, get a load of these love letters. ";
const string CONST_THERE_ARE_SOME_DRUGS_HERE = "There are some drugs here.";
const string CONST_THERE_ARE_SOME_VERY_COMPROMISING_PHOTOS_HERE = "There are some... very compromising photos here.";
const string CONST_THE_SQUAD_LIBERATES_SOME_EXPENSIVE_JEWELERY = "The squad Liberates some expensive jewelery.";
const string CONST_THIS_GUY_SURE_HAD_A_LOT_OF_100_BILLS = "This guy sure had a lot of $100 bills.";
const string CONST_THE_SQUAD_HAS_FOUND_A_DESERT_EAGLE = "The squad has found a Desert Eagle.";
const string CONST_DESTROY_IT_YES_OR_NO = "Destroy it? (Yes or No)";
const string CONST_YOU_SEE_SOME_INDUSTRIAL_EQUIPMENT = "You see some industrial equipment.";
const string CONST_YOU_SEE_SOME_TEXTILE_EQUIPMENT = "You see some textile equipment.";
const string CONST_THE_SQUAD_SPRAYS_LIBERAL_GRAFFITI = "The squad sprays Liberal Graffiti!";
const string CONST_INCLUDING_A_LIST_OF_GOVERNMENT_BACKERS_OF_THE_CCS = "including a list of government backers of the CCS.";
const string CONST_X_SINGLE_COMMA = ",";
const string CONST_THE_SQUAD_OBTAINS_SENSITIVE_INFORMATION = "The Squad obtains sensitive information";
const string CONST_HACK_IT_YES_OR_NO = "Hack it? (Yes or No)";
const string CONST_YOU_VE_FOUND_THE_INTELLIGENCE_SUPERCOMPUTER = "You've found the Intelligence Supercomputer.";
const string CONST_COMPUTER_TO_SHUT_DOWN = "computer to shut down.";
const string CONST_THE_SECURITY_ALERT_HAS_CAUSED_THE = "The security alert has caused the ";
const string CONST_FREE_THE_PRISONERS_YES_OR_NO = "Free the prisoners? (Yes or No)";
const string CONST_PRISON_CONTROL_ROOM = "prison control room.";
const string CONST_HIGH_SECURITY = "high security ";
const string CONST_MEDIUM_SECURITY = "medium security ";
const string CONST_LOW_SECURITY = "low security ";
const string CONST_YOU_VE_FOUND_THE = "You've found the ";
const string CONST_WASN_T_QUITE_CONVINCING = " wasn't quite convincing...";
const string CONST_WASN_T_REALLY_WRONG_HERE = " wasn't really wrong here.";
const string CONST_CONCLUDES_THAT = "concludes that ";
const string CONST_WORKS_THE_ROOM_LIKE_IN_TWELVE_ANGRY_MEN_AND_THE_JURY = " works the room like in Twelve Angry Men, and the jury ";
const string CONST_ATTEMPT_TO_INFLUENCE_THEM_YES_OR_NO = "Attempt to influence them? (Yes or No)";
const string CONST_YOU_VE_FOUND_A_JURY_IN_DELIBERATIONS = "You've found a Jury in deliberations!";
const string CONST_VACATED_IN_A_HURRY = "vacated in a hurry.";
const string CONST_IT_APPEARS_AS_IF_THIS_ROOM_HAS_BEEN = "It appears as if this room has been ";
const string CONST_FREE_THEM_YES_OR_NO = "Free them? (Yes or No)";
const string CONST_YOU_SEE_PRISONERS_IN_THE_COURTHOUSE_JAIL = "You see prisoners in the Courthouse jail.";
const string CONST_YOU_SEE_PRISONERS_IN_THE_DETENTION_ROOM = "You see prisoners in the detention room.";
const string CONST_UH_MAYBE_THAT_IDEA_WAS_CONSERVATIVE_IN_RETROSPECT = "Uh, maybe that idea was Conservative in retrospect...";
const string CONST_YOU_SEE_HORRIBLE_MISSHAPEN_CREATURES_IN_A_SEALED_CAGE = "You see horrible misshapen creatures in a sealed cage.";
const string CONST_THE_SQUAD_RESIGNS_TO_JUST_LEAVING_A_THREATENING_NOTE = "the Squad resigns to just leaving a threatening note.";
const string CONST_AFTER_SOME_FAILED_ATTEMPTS_AND_A_VERY_LOUD_ALARM = "After some failed attempts, and a very loud alarm, ";
const string CONST_THE_REACTOR_IS_OVERHEATING = "The reactor is overheating!";
const string CONST_X_LITTLE_MORE_WHITESPACE = "                ";
const string CONST_A_DEAFENING_ALARM_SOUNDS = "A deafening alarm sounds!";
const string CONST_THE_NUCLEAR_WASTE_GETS_RELEASED_INTO_THE_STATE_S_WATER_SUPPLY = "The nuclear waste gets released into the state's water supply!";
const string CONST_PRESSES_THE_BIG_RED_BUTTON = " presses the big red button!";
const string CONST_MESS_WITH_THE_REACTOR_SETTINGS_YES_OR_NO = "Mess with the reactor settings? (Yes or No)";
const string CONST_YOU_SEE_THE_NUCLEAR_POWER_PLANT_CONTROL_ROOM = "You see the nuclear power plant control room.";
const string CONST_ATTEMPT_TO_RELEASE_NUCLEAR_WASTE_YES_OR_NO = "Attempt to release nuclear waste? (Yes or No)";
const string CONST_YOU_SEE_THE_NUCLEAR_WASTE_CENTER_CONTROL_ROOM = "You see the nuclear waste center control room.";
const string CONST_EMPLOYEES_ONLY = "Employees Only";
const string CONST_ON_THE_LEFT = "on the left.";
const string CONST_THE_LANDLORD_S_OFFICE_IS_THE_FIRST_DOOR = "The landlord's office is the first door";
const string CONST_THE_MUSEUM_DISPLAYS_IN_THE_GIFT_SHOP = "the museum displays in the gift shop.";
const string CONST_WELCOME_TO_THE_NPP_NUCLEAR_PLANT_PLEASE_ENJOY = "Welcome to the NPP Nuclear Plant. Please enjoy";
const string CONST_YOU_SEE_FLUFFY_WHITE_RABBITS_IN_A_LOCKED_CAGE = "You see fluffy white rabbits in a locked cage.";
const string CONST_GET_THE_HECK_OUT_OF_HERE = "\"Get the [heck] out of here.\"";
const string CONST_THE_BOUNCER_ASSESSES_YOUR_SQUAD = "The bouncer assesses your squad.";
const string CONST_THE_CONSERVATIVE_SCUM_BLOCK_THE_DOOR = "The Conservative scum block the door.";
const string CONST_SMIRKS_AND_LETS_THE_SQUAD_IN = " smirks and lets the squad in.";
const string CONST_CASENOT_REJECTED_TXT = "caseNOT_REJECTED.txt";
const string CONST_CASEREJECTED_WEAPONS_TXT = "caseREJECTED_WEAPONS.txt";
const string CONST_CASEREJECTED_NUDE_TXT = "caseREJECTED_NUDE.txt";
const string CONST_RANDOMCRIME_TXT = "randomCrime.txt";
const string CONST_NOTREJECTED_TXT = "notRejected.txt";
const string CONST_REJECTEDBECAUSESMELLFUNNY_TXT = "rejectedBecauseSmellFunny.txt";

const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT = "LOOT";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_CLIP = "CLIP";
const string tag_CLIP_ASSAULT = "CLIP_ASSAULT";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_CLIP_DRUM = "CLIP_DRUM";
const string tag_WEAPON_M249_MACHINEGUN = "WEAPON_M249_MACHINEGUN";
const string tag_LOOT_CEOTAXPAPERS = "LOOT_CEOTAXPAPERS";
const string tag_LOOT_CEOLOVELETTERS = "LOOT_CEOLOVELETTERS";
const string tag_LOOT_CEOPHOTOS = "LOOT_CEOPHOTOS";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_CLIP_50AE = "CLIP_50AE";
const string tag_WEAPON_DESERT_EAGLE = "WEAPON_DESERT_EAGLE";
const string tag_LOOT_INTHQDISK = "LOOT_INTHQDISK";
const string tag_LOOT_CCS_BACKERLIST = "LOOT_CCS_BACKERLIST";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
//#endif//MAPSPECIALS_CPP
//#endif// INCLUDES_H_INCLUDED
