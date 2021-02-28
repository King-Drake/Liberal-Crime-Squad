




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

enum LCSIO_FLAGS
{
	LCSIO_PRE_ART = 1, /// Append the given file name to the art directory path.
	LCSIO_PRE_HOME = 2 /// Append the given file name to the home directory path.
};
#include <iostream>
FILE* LCSOpenFile(const char* filename, const char* mode, int flags);
bool LCSOpenFileCPP(std::string filename, std::ios_base::openmode mode, int flags, std::fstream &file);
void LCSCloseFile(FILE* handle);
void LCSCloseFileCPP(std::fstream &file);
void LCSDeleteFile(const char* filename, int flags);
void LCSRenameFile(const char* old_filename, const char* new_filename, int flags);
//returns a list of all files in homedir with extension .dat
vector<string> LCSSaveFiles();

void pause_ms(int t);
void alarmset(int t);
void alarmwait();
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



enum SquadStances
{
	SQUADSTANCE_ANONYMOUS,
	SQUADSTANCE_STANDARD,
	SQUADSTANCE_BATTLECOLORS,
	SQUADSTANCE_MAX
};

const int ENCMAX = 18;
// ENCMAX _HAS_ to be 26 or less, or else there aren't enough letters

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

//just a float that is initialized to 0
#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
#include "activityST.h"

//int get_associated_attribute(int skill_type);

const string singleDot = ".";
const string singleSpace = " ";

//#ifdef	MISCACTIONS_CPP

// miscactions.cpp


#include "../creature/creature.h"
////


#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
//#include "../sitemode/sitedisplay.h"
void clearmessagearea(bool redrawmaparea = true);
#include "../log/log.h"
//#include "../common/commondisplay.h"
void printparty();
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void criminalizeparty
//#include "../daily/daily.h"
char securityable(int type);

#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../customMaps.h"
short getCurrentSite();
#include "miscactions.h"
vector<string> was_abused;
map<short, string> discussIssues;
map<short, string> discussesIssues;
const string ACTIVITIES_FOLDER = "activities\\";

void fillEncounter(CreatureTypes c, int numleft);
void whoAreWaitingForRescue(vector<DeprecatedCreature *>& waiting_for_rescue, int cursite, short special);

void fillEncounter(CreatureTypes c, int numleft);

map<int, CheckDifficulty> unlockDifficulty = {
	map<int, CheckDifficulty>::value_type(UNLOCK_CAGE,        DIFFICULTY_VERYEASY),
	map<int, CheckDifficulty>::value_type(UNLOCK_CAGE_HARD,   DIFFICULTY_AVERAGE),
	map<int, CheckDifficulty>::value_type(UNLOCK_CELL,        DIFFICULTY_FORMIDABLE),
	map<int, CheckDifficulty>::value_type(UNLOCK_ARMORY,      DIFFICULTY_HEROIC),
	map<int, CheckDifficulty>::value_type(UNLOCK_SAFE,        DIFFICULTY_HEROIC),
	map<int, CheckDifficulty>::value_type(UNLOCK_VAULT,       DIFFICULTY_HEROIC),
};
bool isThereASiteAlarm();
void setSiteAlarmOne();
vector<NameAndAlignment> getEncounterNameAndAlignment();

extern Deprecatedsquadst *activesquad;
extern Log gamelog;
extern short fieldskillrate;
extern short sitealarmtimer;
extern short sitealienate;

const string CONST_YOU_LL_HAVE_TO_COME_BACK_LATER = "You'll have to come back later.";
const string CONST_THERE_S_NOBODY_LEFT_TO_CARRY_THE_OTHERS = "There's nobody left to carry the others.";
const string CONST_THERE_S_NOBODY_LEFT_TO_CARRY = "There's nobody left to carry ";
const string CONST_WILL_HAVE_TO_HAUL_A_LIBERAL = " will have to haul a Liberal.";
const string CONST_SO = "so ";
const string CONST_FROM_THE_CONSERVATIVES = " from the Conservatives.";
const string CONST_YOU_VE_RESCUED = "You've rescued ";
const string CONST_AT_THEIR_DESKS_THE_SQUAD_MIGHT_YET_ESCAPE = "at their desks.  The Squad might yet escape.";
const string CONST_THE_SHOW_WAS_SO_GOOD_THAT_SECURITY_LISTENED_TO_IT = "The show was so good that security listened to it ";
const string CONST_THAT_SECURITY_WATCHED_IT = " that security watched it ";
const string CONST_ENTERTAINING = "entertaining";
const string CONST_HILARIOUS = "hilarious";
const string CONST_THE_SHOW_WAS_SO = "The show was so ";
const string CONST_AFTER_THE_SHOW = "after the show!";
const string CONST_SECURITY_IS_WAITING_FOR_THE_SQUAD = "Security is waiting for the Squad ";
const string CONST_THEY_NO_LONGER_FEEL_ALIENATED = "They no longer feel alienated.";
const string CONST_MODERATES_AT_THE_STATION_APPRECIATED_THE_SHOW = "Moderates at the station appreciated the show.";
const string CONST_THE_HOSTAGE_IS_KEPT_OFF_AIR = ", the hostage, is kept off-air.";
const string CONST_IS_FORCED_ON_TO = " is forced on to ";
const string CONST_THE_HOSTAGE = "The hostage ";
const string CONST_IT_WAS_THE_BEST_HOUR_OF_AM_RADIO_EVER = "It was the best hour of AM radio EVER.";
const string CONST_IT_WAS_THOUGHT_PROVOKING_EVEN_HUMOROUS = "It was thought-provoking, even humorous.";
const string CONST_THE_SQUAD_PUT_ON_A_GOOD_SHOW = "The Squad put on a good show.";
const string CONST_THE_SHOW_WAS_ALL_RIGHT = "The show was all right.";
const string CONST_IT_IS_MEDIOCRE_RADIO = "It is mediocre radio.";
const string CONST_IT_IS_A_VERY_BORING_HOUR = "It is a very boring hour.";
const string CONST_THE_SHOW_REALLY_SUCKS = "The show really sucks.";
const string CONST_THE_SQUAD_SOUNDS_WHOLLY_INSANE = "The Squad sounds wholly insane.";
const string CONST_IT_WAS_THE_BEST_HOUR_OF_CABLE_TV_EVER = "It was the best hour of Cable TV EVER.";
const string CONST_IT_IS_MEDIOCRE_TV = "It is mediocre TV.";
const string CONST_THE_SQUAD_LOOKS_COMPLETELY_INSANE = "The Squad looks completely insane.";
const string CONST_THE_SQUAD_TAKES_CONTROL_OF_THE_MICROPHONE_AND = "The Squad takes control of the microphone and ";
const string CONST_THE_SQUAD_STEPS_IN_FRONT_OF_THE_CAMERAS_AND = "The Squad steps in front of the cameras and ";
const string CONST_THE_BROADCAST_NEVER_HAPPENS = "the broadcast never happens.";
const string CONST_THE_CONSERVATIVES_IN_THE_ROOM_HURRY_THE_SQUAD_SO = "The Conservatives in the room hurry the Squad, so ";
const string CONST_INCLUDING_THE_BLIND_HACKER_YOU_BROUGHT = "Including the BLIND HACKER you brought.";
const string CONST_YOU_CAN_T_FIND_ANYONE_TO_DO_THE_JOB = "You can't find anyone to do the job.";
const string CONST_BYPASS_THE_VAULT_S_ELECTRONIC_LOCK = " bypass the vault's electronic lock.";
const string CONST_BYPASS_THE_SUPERCOMPUTER_SECURITY = " bypass the supercomputer security.";
const string CONST_SEE_HOW_TO = " see how to";
const string CONST_COULDN_T = " couldn't";
const string CONST_EXCLAMATION_POINT = "!";
const string CONST_DESPITE_BEING_BLIND = " despite being blind";
const string CONST_DISABLED_THE_SECOND_LAYER_OF_SECURITY = " disabled the second layer of security";
const string CONST_BURNED_A_DISK_OF_TOP_SECRET_FILES = " burned a disk of top secret files";
const string CONST_HAS = " has";
const string CONST_KICKS_THE_DOOR = " kicks the door";
const string CONST_RAMS_INTO_THE_DOOR = " rams into the door";
const string CONST_ALARMS_GO_OFF_EXCLAMATION = "Alarms go off!";
const string CONST_KICKS_IN_THE_DOOR = "kicks in the door";
const string CONST_RAMS_OPEN_THE_DOOR = "rams open the door";
const string CONST_SMASHES_IN_THE_DOOR = "smashes in the door";
const string CONST_USES_A_CROWBAR_ON_THE_DOOR = "uses a crowbar on the door";
const string CONST_CAN_T_FIGURE_THE_LOCK_OUT = " can't figure the lock out.";
const string CONST_IS_CLOSE_BUT_CAN_T_QUITE_GET_THE_LOCK_OPEN = " is close, but can't quite get the lock open.";
const string CONST_CRACKS_THE_COMBO_LOCKS = "cracks the combo locks";
const string CONST_UNLOCKS_THE_CELL = "unlocks the cell";
const string CONST_OPENS_THE_ARMORY = "opens the armory";
const string CONST_CRACKS_THE_SAFE = "cracks the safe";
const string CONST_UNLOCKS_THE_CAGE = "unlocks the cage";
const string CONST_UNLOCKS_THE_DOOR = "unlocks the door";
const string CONST_WAS_ABUSED_TXT = "was_abused.txt";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
vector<file_and_text_collection> misc_activities_text_file_collection = {
	/*miscactions.cpp*/
	customText(&was_abused, ACTIVITIES_FOLDER + CONST_WAS_ABUSED_TXT),
};
//#endif//MISCACTIONS_CPP
//#endif// INCLUDES_H_INCLUDED
