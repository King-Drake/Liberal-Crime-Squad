




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
//#ifdef	SIEGE_CPP
// siege.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
#include "../basemode/baseactions.h"
// for orderparty
#include "../sitemode/sitedisplay.h"
//#include "../sitemode/advance.h"
void creatureadvance();
//#include "../sitemode/miscactions.h"
void reloadparty(bool wasteful = false);
//#include "../sitemode/sitemode.h"
void mode_site(const short loc);
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for void cleangonesquads();
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for void printfunds(int,int,char*)
#include "../common/translateid.h"
// for  int getsquad(int)
#include "../politics/politics.h"
//for  int publicmood(int l);
#include "../combat/fight.h"   
//for void autopromote(int loc);
#include "../combat/chase.h"
//for void evasiverun();
#include "../customMaps.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"

int getkeyAlt();
int eraseAlt(void);
void pressAnyKey();
int pressSpecificKey(const int x, const int y);

void emptyEncounter();
void fillEncounter(CreatureTypes c, int numleft);
#include "../common/creaturePool.h"
bool hasPrintingPress(int l);
void deletePrintingPress(int loc);
void deleteCompoundWalls(int loc);
void deleteBusinessFront(int loc);
void CCSCapturesSite(int loc);
void endLocationSiege(int l);
void deleteLocationLoot(int l);
void deleteLocationVehicles(int loc);

int baddieCount();
int encounterSize();
vector<NameAndAlignment> getEncounterNameAndAlignment();
short getCurrentSite();
void setCurrentSite(const short i);
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

void printEscapeEngageInfo();
void printEscapeEngageInfoFooter(const bool cameras, const bool traps);
void logDefeat();
void printConquerTextCCS(const int ccs_siege_kills, const int ccs_kills);
void printConquerText(const bool police);

void dropHeatByFivePercent(int l);
int getTimeUntilSiege(int l);
void huntFasterIfSiteIncrediblyHot(int l);
void updateLocationHeatProtection(int l);
void letPlaceCoolOffUnlessCrime(int crimes, int l);
void policeSiege(int l);
void corporateSiege(int l);
void CCSSiege(int l);
void CIASiege(int l);
void hicksSiege(int l);
void firemanSiege(int l);
bool hasCameras(int l);
bool hasAGenerator(int l);
bool hasBusinessFront(int l);
bool siteHasAAGun(int l);
void deleteAAGun(int l);

void deleteGeneratorLightsOff(int l);


int printBestLCSMemberForNews(const string repname, const int l);

bool getLightsOff(int l);
void setLightsOff(int l);
bool hasBasicCompoundWalls(int l);


void reduceCompoundStores(int loc, int amount);
void emptyCompoundStores(int l);
void setUnderAttack(int l);

void baseEveryoneLeftAtHomelessShelter(const int homes);
void escalateSite(int l);
void dumpLootAtLocation(int homes, vector<Item *>& loot);
siegest getWholeSiege(int l);
void cancelOutBleeding();
int print_character_info(const int c, const int party_status);
void countHeroes(int &partysize, int &partyalive);
int print_character_info(const int c, const int party_status);
int getEscapeEngageLocation();
void deleteAllSquadsInActiveAreaExceptActive(const int loc);
void formANewSquadIfThereAreNone();


void juiceEntireCreaturePool(const long juice, const long cap);
void printBrokenLawsFooter(const bool kidnapped, const int typenum);
void printHarboringFugitive();
void printBrokenLawsHeader(const char underAttack, const short escalation);
void printBurnedFlag(const int flagLaw);
void printHireIllegal(const bool lawStatus);
void printReleaseKidnapped(const string kname, const int kidnapped);
void printCCSRaidSafehouse();
void printCorpSiegeWarning(const int sleeper, const string locationName);
void corporateSiegePrint(const string lname);
void printCCSCarbomb();
void printCCSRaid(const string lname);
void printEveryoneInjuredHeader();
void printInjuredList(const vector<pair<string, int> > injuredList);
void printKillList(const vector<pair<string, int> > killList);
void printCCSSleeperWarning(const string lname);
void printJetBombers();
void printTankArrival(const bool tank_traps);
void printSWATArrival();
void printPoliceSiegeHeader(const string lname);
void printPoliceSleeperWarning(const string locationName, const int siegeEscalationState);
void printPoliceSiegeEmptyHeader(const string lname);
void printCorpseRecoveredByPolice(const string corpse, const int y);
void printKidnapRecoveredByPolice(const string kidnap, const int y);
void printSpecificCrime(const Lawflags crime);
void printMostSeriousCrime(const bool breakercount[LAWFLAGNUM]);
void printWantedFor();
void printRehab();
void printEveryoneHereIsDead(const string lname);
void printBusinessFrontTaken();
void printCompoundDismantled();
void printPrintingpressDismantled();
void printMoneyConfiscated(const int confiscated);
void printFundsIntact();
void printLiberalsTakenToPolice(const int pcount);
void printSingleLiberalTaken(const string pname, const string pcname);
void printKidnapFreed();
void printSingleKidnapFreed(const string kname);
void printTheyConfiscateEverything(const int siege, const int escalationState);
void printConquerTextCCS(const int ccs_siege_kills, const int ccs_kills);
void printCorpseRecovery(const int y, const string name);
void printKidnapRescue(const int y, const string name);
void printFiremenSiegeEmpty(const string locationName);
void printFiremenRaid2();
void printFiremenRaid(const string loc);
void printFiremenSiegeEmpty(const bool printingPress, const bool businessFront);
void printCIASiegeWarning(const string locationName);
void printCIASiege(const string locationName, const bool hasCameras, const bool hasAGenerator);
void printRadioHicksSiege(const int l);
void printCableHicksSiege(const int l);
void printFiremenSiege(const bool sleeper, const int l);
void printReporterEnteredCompound(const string repname);
void printThePoliceCutLights(const bool clearformess);
void printReporterDuringSiege(const string repname, const string name, const int segmentpower);
void printShotBySniper(const string targname);
void printMissedBySniper(const string targname);
void printWasKilledInBombing(const string targname);
void printNarrowlyAvoidsDeath(const string targname);
void printNoOneIsHurt(const bool clearformess);
void printCONST_THE_LIGHTS_FADE_AND_ALL_IS_DARK(const bool clearformess);
void printCONST_THE_GENERATOR_HAS_BEEN_DESTROYED(const bool clearformess);
void printCONST_THERE_S_NOTHING_LEFT_BUT_SMOKING_WRECKAGE(const bool clearformess);
void printCONST_THE_ANTI_AIRCRAFT_GUN_TAKES_A_DIRECT_HIT(const bool clearformess);
void printCONST_EXPLOSIONS_ROCK_THE_COMPOUND(const bool clearformess);
void printCONST_A_SKILLED_PILOT_GETS_THROUGH(const bool clearformess);
void printCONST_IT_S_ALL_OVER_THE_TV_EVERYONE_IN_THE_LIBERAL_CRIME_SQUAD_GAINS_20_JUICE(const bool clearformess);
void printCONST_HIT_ONE_OF_THE_BOMBERS_SLAMS_INTO_TO_THE_GROUND(const bool clearformess);
void printCONST_YOU_DIDN_T_SHOOT_ANY_DOWN_BUT_YOU_VE_MADE_THEM_THINK_TWICE(const bool clearformess);
void printCONST_THE_THUNDER_OF_THE_ANTI_AIRCRAFT_GUN_SHAKES_THE_COMPOUND(const bool clearformess);
void printCONST_YOU_HEAR_PLANES_STREAK_OVERHEAD(const bool clearformess);
void printConservativesRaidedUnoccupiedSafehouse(const string locname);
void printCorpseRecovered(const string pname, const int y);
void printLiberalRescued(const string pname, const int y);
void printReflectOnYourConJudgement();
void printSallyForthSiege();
void printSallyForthFooter();
void printYoureFree();
void printSiegeIsBroken();
void printSiegeOptions(const int partysize, const short party_status);
void printLocationName(const string loc);
void printTanksMoveToEntrance(const bool clearformess);
void printEngineersRemoveTankTrap(const bool clearformess);
void logADayPasses();
void printYourLiberalsAreStarving(const bool clearformess);
void printHasStarvedToDeath(const string pname, const bool clearformess);
void printTheCopsAreComing(const bool clearformess);
void printYouHaveEscaped();
void printEscapeEngageInfo();
void printEscapeEngageInfoFooter(const bool cameras, const bool traps);
void logDefeat();
void printConquerText(const bool police);

extern char ccs_kills;
extern char disbanding;
extern char endgamestate;
extern char foughtthisround;
extern class Ledger ledger;
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int ccs_siege_kills;
extern int police_heat;
extern int selectedsiege;
extern int stat_dead;
extern Log gamelog;
extern long cursquadid;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short lawList[LAWNUM];
extern short mode;
extern short offended_amradio;
extern short offended_cablenews;
extern short offended_cia;
extern short offended_corps;
extern short offended_firemen;
extern short party_status;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatednewsstoryst *> newsstory;
extern vector<Deprecatedsquadst *> squad;

//#endif//SIEGE_CPP
//#endif// INCLUDES_H_INCLUDED
