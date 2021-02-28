




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




enum Alignment
{
	ALIGN_ARCHCONSERVATIVE = -2,
	ALIGN_CONSERVATIVE,
	ALIGN_MODERATE,
	ALIGN_LIBERAL,
	ALIGN_ELITELIBERAL,
	ALIGN_STALINIST
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

enum Execs
{
	EXEC_PRESIDENT,
	EXEC_VP,
	EXEC_STATE,
	EXEC_ATTORNEY,
	EXECNUM
};


// full house (100%) - for looping thru full house
const int  HOUSENUM = 435;
// just over half of house (50%+1) - to pass bills
const int  HOUSEMAJORITY = 218;
// 3/5 of house - has no significance other than in seeing if you won game
const int  HOUSECOMFYMAJORITY = 261;
// 2/3 of house - to override veto or pass constitutional amendment
const int  HOUSESUPERMAJORITY = 290;
// full senate (100%) - for looping thru full senate
const int  SENATENUM = 100;
// just over half of senate(50%+1) - to bass bills
const int  SENATEMAJORITY = 51;
// 3/5 of senate - to break filibuster in real world, but in game, has no significance other than seeing if you won
const int  SENATECOMFYMAJORITY = 60;
// 2/3 of senate - to override veto or pass constitutional amendment
const int  SENATESUPERMAJORITY = 67;
// full court (100%) - for looping thru full court
const int  COURTNUM = 9;
// just over half of court (50%+1) - to make majority rulings
const int  COURTMAJORITY = 5;
// 2/3 of court - has no significance other than seeing if you won game
const int  COURTSUPERMAJORITY = 6;
// all states (100%) - for looping thru all states
const int  STATENUM = 50;
// 3/4 of states (75%) - needed to pass constitutional amendments
const int  STATESUPERMAJORITY = 38;

const int  POLITICIAN_NAMELEN = 80;


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
const string city = "CITY: ";
const string spaceDashSpace = " - ";
const string pressAnyKeyString = "Press any other key when ready to begin...";
const string pressAnyOtherKey = "Press any other key to continue...";

//#ifdef	NEWGAME_CPP
// newgame.cpp

#include "../creature/creature.h"
#include "../locations/locations.h"

#include "../common/ledgerEnums.h"
#include "../common/ledger.h"

#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"

//#include "../common/consolesupport.h"
// for getkey

#include "../log/log.h"

#include "../common/stringconversion.h"
//for string attribute_enum_to_string(int)

#include "../common/getnames.h"
// for cityname

#include "../common/translateid.h"
// for  getarmortype

#include "../cursesAlternative.h"
#include "../set_color_support.h"

#include "../common/creaturePoolCreature.h"

#include "../common/musicClass.h"



vector<string> founderQuestions;

#include "../customMaps.h"
vector<file_and_text_collection> newgame_file_collection = {
	/*newgame.cpp*/
	customText(&founderQuestions, "newgame\\founderQuestions.txt"),
};
map<string, short> getSkillEnumFromString;
map<short, string> enumToCreature;
map<string, short> getBaseEnumFromString;
map<string, short> getSpecialWoundEnumFromString;

extern bool ALLOWSTALIN;
extern bool BLIND;
extern bool INTERNAL;
extern bool multipleCityMode;
extern bool nocourtpurge;
extern bool NOFACE;
extern bool notermlimit;           //These determine if ELAs can take place --kviiri
extern bool NOWALK;
extern bool SPINE;
extern bool stalinmode;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char endgamestate;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char lcityname[CITY_NAMELEN];
extern class Ledger ledger;
extern int day;
extern int month;
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short court[COURTNUM];
extern short fieldskillrate;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short senate[SENATENUM];
extern short wincondition;
extern UniqueCreatures uniqueCreatures;
extern vector<ClipType *> cliptype;
extern vector<WeaponType *> weapontype;

Vehicle* newSportsCar();

enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};

void newVehicle(Vehicle *startcar);
enum Stat_Or_Attribute {
	SKILL,
	ATTRIBUTE,
	OTHER
};
enum Other_Influence {
	BIRTH_MONTH,
	BIRTH_DAY,
	BIRTH_YEAR,
	STARTING_MONTH,
	STARTING_DAY,
	STARTING_YEAR,
	GAY,
	DATING_LAWYER,
	DATING,
	HAS_MAPS,
	JUICE,
	SPORTS_CAR,
	ASSAULT_RIFLE,
	MONEY,
	BASE,
	CREATURE,
	ARMOR,
	RECRUITS
};
struct MutableImpact {
	Stat_Or_Attribute type;
	int item_to_influence;
	int magnitude;
	bool set_value;
};

struct Impact {
	const Stat_Or_Attribute type;
	const int item_to_influence;
	const int magnitude;
	const bool set_value;
	Impact(MutableImpact i) : type(i.type), item_to_influence(i.item_to_influence), magnitude(i.magnitude), set_value(i.set_value) {}
};
struct MutableChoice {
	string ANSWER;
	string ANSWER_2;
	vector<Impact> impact;
};
struct Choice {
	const string ANSWER;
	const string ANSWER_2;
	const vector<Impact> impact;
	Choice(MutableChoice c) : ANSWER(c.ANSWER), ANSWER_2(c.ANSWER_2), impact(c.impact) {}
};
struct MutableQuestion {
	string HEADER;
	string HEADER_2;
	string QUESTION;
	string QUESTION_2;
	vector<Choice> choices;
};
struct Question {

	const string HEADER;
	const string HEADER_2;
	const string QUESTION;
	const string QUESTION_2;
	const vector<Choice> choices;
	Question(MutableQuestion q) : HEADER(q.HEADER), HEADER_2(q.HEADER_2), QUESTION(q.QUESTION), QUESTION_2(q.QUESTION_2), choices(q.choices) {}
};
enum founderQuestionTagEnums {
	ENUM_tag_HEADER,
	ENUM_tag_ANSWER,
	ENUM_tag_QUESTION,
	ENUM_tag_SKILL_,
	ENUM_tag_ATTRIBUTE_,
	ENUM_tag_STARTING_,
	ENUM_tag_BIRTHDAY_,
	ENUM_tag_MONEY,
	ENUM_tag_DATING_LAWYER,
	ENUM_tag_GAY,
	ENUM_tag_HASMAPS,
	ENUM_tag_CREATURE,
	ENUM_tag_BASE,
	ENUM_tag_ARMOR,
	ENUM_tag_JUICE,
	ENUM_tag_RECRUITS_GANG,
	ENUM_tag_ASSAULT_RIFLE,
	ENUM_tag_SPORTS_CAR,
};

const int MAX_CHOICES = 10;

#include "../recruits.h"
/* creates your founder */
struct newGameArguments {
	const char recruits;
	const char base;
	const bool makelawyer;
	const bool gaylawyer;
	const bool sports_car;
	newGameArguments(char _recruits, char _base, bool _makelawyer, bool _gaylawyer, bool _sports_car) : recruits(_recruits), base(_base), makelawyer(_makelawyer), gaylawyer(_gaylawyer), sports_car(_sports_car) {}
};
const string ALL_OPTIONS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string pressBtoBeReborn = " (Press B to be born to a different family)";
const string pressCtoChangeSex = " (Press C to change your sex at birth)";
const string history = "HISTORY: ";
const string letMeChoose = "Let Me Choose";
const string letFateDecide = "Let Fate Decide";
const string pressDtoToggle = " (Press D to toggle childhood)";
const string pressEtoRelocate = " (Press E to relocate)";
const string sexIs = "SEX: ";
const string male = "Male";
const string female = "Female";
const string itsComplicated = "It's Complicated";
const string theFounder = "The Founder of the Liberal Crime Squad";
const string firstName = "FIRST NAME: ";
const string pressAtoReconsider = " (Press A to have your parents reconsider)";
const string lastName = "LAST NAME: ";
const string theDocSaid = "The doctor said I was ";
const string aBoy = "a boy";
const string aGirl = "a girl";
const string intersex = "an intersex baby";
const string myParents = "My parents ";
const string insistedOtherwise = "insisted otherwise.";
const string they = "They ";
const string namedMe = "named me ";
const string A_NEW_CON_ERA = "A NEW CONSERVATIVE ERA";
const string theYearIs = "The Year is ";
const string CONSERVATIVE_PRESIDENT = "Conservative President ";
const string endsSecondTerm = " ends his second term with approval";
const string highSeventiesApprovePres = "ratings in the high 70s, and is succeeded by hardcore Arch-Conservative";
const string WITH_CONSERVATIVES_SWEEPING_INTO_POWER = "With Conservatives sweeping into power in the House of Representatives";
const string senateConMajority = "and Senate, and a Conservative majority in the Supreme Court of the";
const string US_HAILING_BEGINNING_OF_A_NEW = "United States, commentators are hailing it as the beginning of a new";
const string conEra = "Conservative era.";
const string thePresident = "President ";
const string hasAskedCongressBeQuick = " has asked the new Congress to move quickly";
const string rubberStampArchCon = "to rubber stamp his radical Arch-Conservative agenda. ";
const string theLeftSeems = "The left seems";
const string powerlessToStop = "powerless to stop this imminent trampling of Liberal Sanity and Justice.";
const string inThisDarkTime = "In this dark time, the Liberal Crime Squad is born...";
const string unSelected = "[ ]";
const string isSelected = "[X]";
const string newGameAdvanced = "New Game of Liberal Crime Squad: Advanced Gameplay Options";
const string A_CLASSIC_MODE = " A - Classic Mode: No Conservative Crime Squad.";
const string B_CCS_STARTS_ACTIVE_AND_STRONG = " B - We Didn't Start The Fire: The CCS starts active and extremely strong.";
const string C_NIGHTMARE_MODE = " C - Nightmare Mode: Liberalism is forgotten. Is it too late to fight back?";
const string d_nationalLCS = " D - National LCS: Advanced play across multiple cities.";
const string e_marathonMode = " E - Marathon Mode: Prevent Liberals from amending the Constitution.";
const string f_stalinistMode = " F - Stalinist Mode: Enable Stalinist Comrade Squad (not fully implemented).";
const string newGameYourAgenda = "New Game of Liberal Crime Squad: Your Agenda";
const string A_NO_COMPROMISE = " A - No Compromise Classic - I will make all our laws Elite Liberal!";
const string B_DEMOCRAT_MODE = " B - Democrat Mode - Most laws must be Elite Liberal, some can be Liberal.";
const string newGameFieldLearn = "New Game of Liberal Crime Squad: Field Learning";
const string AFFECTS_THESE_SKILLS = "(affects Security, Stealth, Disguise, & Driving)";
const string A_FAST_SKILLS = " A - Fast skills - Grinding is Conservative!";
const string B_CLASSIC_EXCELLENCE_REQUIRES_PRACTICE = " B - Classic - Excellence requires practice.";
const string C_HARD_MODE = " C - Hard Mode - Learn from the best, or face arrest!";
const string notCreature = "Not a creature";
const string notValidMap = "Not a valid mappable site";
const string notSpecialWound = "Not a special wound";
const string notASkill = "Not a skill";
const string notAnAttribute = "Not an attribute";
const string tag_CLIP = "CLIP";
const string tag_CLIP_ASSAULT = "CLIP_ASSAULT";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_AUTORIFLE_AK47 = "WEAPON_AUTORIFLE_AK47";
const string tag_SPORTS_CAR = "SPORTS_CAR";
const string tag_ASSAULT_RIFLE = "ASSAULT_RIFLE";
const string tag_RECRUITS_GANG = "RECRUITS_GANG";
const string tag_JUICE = "JUICE";
const string tag_ARMOR = "ARMOR";
const string tag_B = "B";
const string tag_BASE = "BASE";
const string tag_CREATURE = "CREATURE";
const string tag_HASMAPS = "HASMAPS";
const string tag_GAY = "GAY";
const string tag_D = "D";
const string tag_DATING_LAWYER = "DATING_LAWYER";
const string tag_MONEY = "MONEY";
const string tag_YEAR = "YEAR";
const string tag_DAY = "DAY";
const string tag_MONTH = "MONTH";
const string tag_BIRTHDAY_ = "BIRTHDAY_";
const string tag_STARTING_ = "STARTING_";
const string tag_ATTRIBUTE_ = "ATTRIBUTE_";
const string tag_SKILL_ = "SKILL_";
const string tag__2 = "_2";
const string tag_QUESTION = "QUESTION";
const string tag_ANSWER = "ANSWER";
const string tag_HEADER = "HEADER";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
map<string, int> founderQuestionTags = {
	map<string, int>::value_type(tag_HEADER, ENUM_tag_HEADER),
	map<string, int>::value_type(tag_ANSWER, ENUM_tag_ANSWER),
	map<string, int>::value_type(tag_QUESTION, ENUM_tag_QUESTION),
	map<string, int>::value_type(tag_SKILL_, ENUM_tag_SKILL_),
	map<string, int>::value_type(tag_ATTRIBUTE_, ENUM_tag_ATTRIBUTE_),
	map<string, int>::value_type(tag_STARTING_, ENUM_tag_STARTING_),
	map<string, int>::value_type(tag_BIRTHDAY_, ENUM_tag_BIRTHDAY_),
	map<string, int>::value_type(tag_MONEY, ENUM_tag_MONEY),
	map<string, int>::value_type(tag_DATING_LAWYER, ENUM_tag_DATING_LAWYER),
	map<string, int>::value_type(tag_GAY, ENUM_tag_GAY),
	map<string, int>::value_type(tag_HASMAPS, ENUM_tag_HASMAPS),
	map<string, int>::value_type(tag_CREATURE, ENUM_tag_CREATURE),
	map<string, int>::value_type(tag_BASE, ENUM_tag_BASE),
	map<string, int>::value_type(tag_ARMOR, ENUM_tag_ARMOR),
	map<string, int>::value_type(tag_JUICE, ENUM_tag_JUICE),
	map<string, int>::value_type(tag_RECRUITS_GANG, ENUM_tag_RECRUITS_GANG),
	map<string, int>::value_type(tag_ASSAULT_RIFLE, ENUM_tag_ASSAULT_RIFLE),
	map<string, int>::value_type(tag_SPORTS_CAR, ENUM_tag_SPORTS_CAR),
};
void printErrorTypeOther(int ip);
void printWhatIsYourName();
//#endif//NEWGAME_CPP
//#endif// INCLUDES_H_INCLUDED
