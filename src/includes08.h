




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

long LCSrandom(long max);
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


enum GameModes
{
	GAMEMODE_TITLE,
	GAMEMODE_BASE,
	GAMEMODE_SITE,
	GAMEMODE_CHASECAR,
	GAMEMODE_CHASEFOOT
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

const int SQUAD_NAMELEN = 40;




//just a float that is initialized to 0
#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
#include "activityST.h"

//int get_associated_attribute(int skill_type);

//#ifdef	STEALTH_CPP
// stealth.cpp

#include "../creature/creature.h"
////

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../sitemode/sitedisplay.h"
#include "../common/commonactionsCreature.h"
#include "../locations/locationsPool.h"
#include "../customMaps.h"

short getCurrentSite();
extern short fieldskillrate;

/* checks if your liberal activity is noticed */
char disguisesite(long type);

vector<NameAndAlignment> getEncounterNameAndAlignment();
bool isThereASiteAlarm();
void setSiteAlarmOne();
void conservatise(const int e);

int get_stealth_difficulty(const int n);
int get_disguise_difficulty(const int n);
int get_encounter_time(const int n);
vector<int> potentialEncounterNoticers();

extern coordinatest loc_coord;
extern Deprecatedsquadst *activesquad;
extern short fieldskillrate;
extern short lawList[LAWNUM];
extern short mode;
extern short sitealarmtimer;
extern short sitealienate;
extern short sitetype;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_BUNKERGEAR = "ARMOR_BUNKERGEAR";
const string tag_ARMOR_SWATARMOR = "ARMOR_SWATARMOR";
const string tag_ARMOR_DEATHSQUADUNIFORM = "ARMOR_DEATHSQUADUNIFORM";
const string tag_ARMOR_POLICEARMOR = "ARMOR_POLICEARMOR";
const string tag_ARMOR_POLICEUNIFORM = "ARMOR_POLICEUNIFORM";
const string tag_ARMOR_EXPENSIVEDRESS = "ARMOR_EXPENSIVEDRESS";
const string tag_ARMOR_EXPENSIVESUIT = "ARMOR_EXPENSIVESUIT";
const string tag_ARMOR_SECURITYUNIFORM = "ARMOR_SECURITYUNIFORM";
const string tag_ARMOR_CHEAPDRESS = "ARMOR_CHEAPDRESS";
const string tag_ARMOR_CHEAPSUIT = "ARMOR_CHEAPSUIT";
const string tag_ARMOR_SEALSUIT = "ARMOR_SEALSUIT";
const string tag_ARMOR_ARMYARMOR = "ARMOR_ARMYARMOR";
const string tag_ARMOR_MILITARY = "ARMOR_MILITARY";
const string tag_ARMOR_SERVANTUNIFORM = "ARMOR_SERVANTUNIFORM";
const string tag_ARMOR_HARDHAT = "ARMOR_HARDHAT";
const string tag_ARMOR_CIVILLIANARMOR = "ARMOR_CIVILLIANARMOR";
const string tag_ARMOR_LABCOAT = "ARMOR_LABCOAT";
const string tag_ARMOR_WORKCLOTHES = "ARMOR_WORKCLOTHES";
const string tag_ARMOR_BLACKDRESS = "ARMOR_BLACKDRESS";
const string tag_ARMOR_BLACKSUIT = "ARMOR_BLACKSUIT";
const string tag_ARMOR_OVERALLS = "ARMOR_OVERALLS";
const string tag_ARMOR_PRISONER = "ARMOR_PRISONER";
const string tag_ARMOR_PRISONGUARD = "ARMOR_PRISONGUARD";
const string tag_ARMOR_BLACKROBE = "ARMOR_BLACKROBE";
const string tag_ARMOR_HEAVYARMOR = "ARMOR_HEAVYARMOR";
const string tag_ARMOR_WIFEBEATER = "ARMOR_WIFEBEATER";
const string tag_WEAPON = "WEAPON";
const string tag_WEAPON_CARBINE_M4 = "WEAPON_CARBINE_M4";
const string tag_WEAPON_CHAIN = "WEAPON_CHAIN";
const string tag_WEAPON_SHANK = "WEAPON_SHANK";
const string tag_WEAPON_SHOTGUN_PUMP = "WEAPON_SHOTGUN_PUMP";
const string tag_WEAPON_TORCH = "WEAPON_TORCH";
const string tag_WEAPON_PITCHFORK = "WEAPON_PITCHFORK";
const string tag_WEAPON_NIGHTSTICK = "WEAPON_NIGHTSTICK";
const string tag_WEAPON_SMG_MP5 = "WEAPON_SMG_MP5";
const string tag_WEAPON_FLAMETHROWER = "WEAPON_FLAMETHROWER";
const string tag_WEAPON_AXE = "WEAPON_AXE";
const string tag_WEAPON_SEMIRIFLE_AR15 = "WEAPON_SEMIRIFLE_AR15";
const string tag_WEAPON_AUTORIFLE_M16 = "WEAPON_AUTORIFLE_M16";
const string tag_WEAPON_SEMIPISTOL_45 = "WEAPON_SEMIPISTOL_45";
const string tag_WEAPON_DESERT_EAGLE = "WEAPON_DESERT_EAGLE";
const string tag_WEAPON_SEMIPISTOL_9MM = "WEAPON_SEMIPISTOL_9MM";
const string tag_WEAPON_REVOLVER_38 = "WEAPON_REVOLVER_38";
const string tag_WEAPON_REVOLVER_44 = "WEAPON_REVOLVER_44";
const string tag_WEAPON_GAVEL = "WEAPON_GAVEL";
const string tag_WEAPON_SYRINGE = "WEAPON_SYRINGE";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_WEAPON_MP5_SMG = "WEAPON_MP5_SMG";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

map<short, map<string, int> > siegeDisguises = {
	map<SiegeTypes, map<string, int> >::value_type(SIEGE_CIA,
		{
			map<string, int>::value_type(tag_ARMOR_BLACKSUIT, 1),
			map<string, int>::value_type(tag_ARMOR_BLACKDRESS, 1)
		}
	),

	map<SiegeTypes, map<string, int> >::value_type(SIEGE_CORPORATE,
		{
			map<string, int>::value_type(tag_ARMOR_MILITARY,  1),
			map<string, int>::value_type(tag_ARMOR_ARMYARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_SEALSUIT,  1),
		}
	),
	map<SiegeTypes, map<string, int> >::value_type(SIEGE_HICKS,
		{
			map<string, int>::value_type(tag_ARMOR_CLOTHES,  2),
			map<string, int>::value_type(tag_ARMOR_OVERALLS,  1),
			map<string, int>::value_type(tag_ARMOR_WIFEBEATER, 1),
		}
	),
	map<SiegeTypes, map<string, int> >::value_type(SIEGE_FIREMEN,
		{
			map<string, int>::value_type(tag_ARMOR_BUNKERGEAR, 1),
		}
   ),
};

map<short, map<string, int> > siteDisguises = {

	map<SiteTypes, map<string, int> >::value_type(SITE_BUSINESS_CIGARBAR,{
	map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
	map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),
	map<string, int>::value_type(tag_ARMOR_BLACKSUIT,  1),
	map<string, int>::value_type(tag_ARMOR_BLACKDRESS,  1),
}
),
map<SiteTypes, map<string, int> >::value_type(SITE_CORPORATE_HEADQUARTERS,{
	map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
	map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
	map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
	map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),
}
	),
};
map<short, map<string, int> > siteDisguisesRestricted = {

	map<SiteTypes, map<string, int> >::value_type(SITE_INDUSTRY_NUCLEAR,{
	map<string, int>::value_type(tag_ARMOR_LABCOAT,  1),
			map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
			map<string, int>::value_type(tag_ARMOR_CIVILLIANARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_HARDHAT,  1),

}
),
map<SiteTypes, map<string, int> >::value_type(SITE_MEDIA_AMRADIO,{
	map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),

}
	),
map<SiteTypes, map<string, int> >::value_type(SITE_MEDIA_CABLENEWS,{
	map<string, int>::value_type(tag_ARMOR_SECURITYUNIFORM,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),

}
),

map<SiteTypes, map<string, int> >::value_type(SITE_GOVERNMENT_WHITE_HOUSE,{
	map<string, int>::value_type(tag_ARMOR_BLACKSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_BLACKDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_CHEAPDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVESUIT,  1),
			map<string, int>::value_type(tag_ARMOR_EXPENSIVEDRESS,  1),
			map<string, int>::value_type(tag_ARMOR_MILITARY,  1),
			map<string, int>::value_type(tag_ARMOR_ARMYARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_SEALSUIT,  1),

}
),
map<SiteTypes, map<string, int> >::value_type(SITE_GOVERNMENT_ARMYBASE,{
	map<string, int>::value_type(tag_ARMOR_MILITARY,  1),
			map<string, int>::value_type(tag_ARMOR_ARMYARMOR,  1),
			map<string, int>::value_type(tag_ARMOR_SEALSUIT,  1),

}
),
map<SiteTypes, map<string, int> >::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ,{
	map<string, int>::value_type(tag_ARMOR_BLACKSUIT,  1),
			map<string, int>::value_type(tag_ARMOR_BLACKDRESS,  1),

}
),

};

void printShoutsForHelp(const string ename, const int ealign);
bool isPrisoner(const string tkname);
void printAlienation(const short sitealienate);
void printFadesAway(const string aname, const int partysize);
void printBlewStealthCheck(const string aname);
void printActsNatural(const string aname, const int partysize);
void printEnemyNameInAlarm(const string nname);
void printLooksAtSquadSuspiciously();
void printShoutsInAlarm();
void printConservativeRaisesAlarm(const bool weapon, const int ntype, const int nalign);
void pressAnyKey();
//#endif//STEALTH_CPP
//#endif// INCLUDES_H_INCLUDED
