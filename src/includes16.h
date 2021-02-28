




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

//

//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
//#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.

//int get_associated_attribute(int skill_type);

enum BillStatus
{
	BILL_SIGNED = -2,
	BILL_OVERRIDE_VETO = -1,
	BILL_PASSED_CONGRESS = 0,
	BILL_FAILED = 1
};
//#include "includesDeprecatedB.h"
//#ifdef	POLITICS_CPP
// politics.cpp

#include "../creature/creatureEnums.h"
/* fills a string with a proper name */
void generate_name(char *str, char gender = GENDER_NEUTRAL);
string lastname(bool x = false);
//#include "../common/commonactions.h"
int randomissue(bool core_only = 0);
#include "../common/commondisplay.h"
// for  void makedelimiter(int y=8,int x=0);
//#include "../monthly/EndGameStatus.h"
/* EndGameStatus - attempts to pass a constitutional amendment to help win the game */
void tossjustices(char canseethings);
/* EndGameStatus - attempts to pass a constitutional amendment to help win the game */
void amendment_termlimits(char canseethings);
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include <common\\getnames.h>
#include "../common/musicClass.h"
#include "../customMaps.h"
map<int, bool> stalinView = {
	map<int, bool>::value_type(VIEW_STALIN,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(VIEW_MOOD,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(VIEW_GAY,  false), // Stalinists discriminate against gay people
	map<int, bool>::value_type(VIEW_DEATHPENALTY,  false), // Stalinists execute lots of people
	map<int, bool>::value_type(VIEW_TAXES,  true), // Stalinists support communist income redistribution
	map<int, bool>::value_type(VIEW_NUCLEARPOWER,  false), // Stalinists believe the more nuclear, the better
	map<int, bool>::value_type(VIEW_ANIMALRESEARCH,  false), // Stalinists are in favor of unethical research
	map<int, bool>::value_type(VIEW_POLICEBEHAVIOR,  false), // Stalinists use police for brutal repression
	map<int, bool>::value_type(VIEW_TORTURE,  false), // Stalinists torture their enemies
	map<int, bool>::value_type(VIEW_INTELLIGENCE,  false), // Stalinists don't believe in privacy
	map<int, bool>::value_type(VIEW_FREESPEECH,  false), // Stalinists don't allow any dissent
	map<int, bool>::value_type(VIEW_GENETICS,  false), // Stalinists are in favor of unethical research
	map<int, bool>::value_type(VIEW_JUSTICES,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(VIEW_GUNCONTROL,  true), // Stalinists don't want any armed resistance
	map<int, bool>::value_type(VIEW_SWEATSHOPS,  true), // Stalinists say, Workers of the world unite!
	map<int, bool>::value_type(VIEW_POLLUTION,  false), // Stalinists don't care about pollution
	map<int, bool>::value_type(VIEW_CORPORATECULTURE,  true), // Stalinists hate rich people and corporations
	map<int, bool>::value_type(VIEW_CEOSALARY,  true), // Stalinists hate rich people and corporations
	map<int, bool>::value_type(VIEW_WOMEN,  false), // Stalinists discriminate against women
	map<int, bool>::value_type(VIEW_CIVILRIGHTS,  false), // Stalinists discriminate against ethnic groups
	map<int, bool>::value_type(VIEW_DRUGS,  false), // Stalinists only allow vodka
	map<int, bool>::value_type(VIEW_IMMIGRATION,  false), // Stalinists maintained tight border security at the Iron Curtain
	map<int, bool>::value_type(VIEW_MILITARY,  false), // Stalinists use the military for brutal repression
	map<int, bool>::value_type(VIEW_PRISONS,  false), // Stalinists annex Canada to fill it with gulags
	map<int, bool>::value_type(VIEW_AMRADIO,  true), // Stalinists agree that Conservatives are bad
	map<int, bool>::value_type(VIEW_CABLENEWS,  true), // Stalinists agree that Conservatives are bad
													   //map<int, bool>::value_type( VIEW_POLITICALVIOLENCE,  true), // the LCS and Stalinists both like using political violence
   map<int, bool>::value_type(VIEW_LIBERALCRIMESQUAD,  false), // Liberals and Stalinists don't get along
   map<int, bool>::value_type(VIEW_LIBERALCRIMESQUADPOS,  false), // Liberals and Stalinists don't get along
   map<int, bool>::value_type(VIEW_CONSERVATIVECRIMESQUAD,  true), // Stalinists agree that Conservatives are bad
   map<int, bool>::value_type(VIEWNUM,  false), // Liberals and Stalinists don't get along
};
map<int, bool> stalinLaw = {
	map<int, bool>::value_type(LAW_STALIN,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(LAW_MOOD,  false), // Liberals and Stalinists don't get along
	map<int, bool>::value_type(LAW_ABORTION,  true), // Stalinists agree that abortion is good, although technically they don't let women choose
	map<int, bool>::value_type(LAW_ANIMALRESEARCH,  false), // Stalinists are in favor of unethical research
	map<int, bool>::value_type(LAW_POLICEBEHAVIOR,  false), // Stalinists use police for brutal repression
	map<int, bool>::value_type(LAW_PRIVACY,  false), // Stalinists don't believe in privacy
	map<int, bool>::value_type(LAW_DEATHPENALTY,  false), // Stalinists execute lots of people
	map<int, bool>::value_type(LAW_NUCLEARPOWER,  false), // Stalinists believe the more nuclear, the better
	map<int, bool>::value_type(LAW_POLLUTION,  false), // Stalinists don't care about pollution
	map<int, bool>::value_type(LAW_LABOR,  true), // Stalinists say, Workers of the world unite!
	map<int, bool>::value_type(LAW_GAY,  false), // Stalinists discriminate against gay people
	map<int, bool>::value_type(LAW_CORPORATE,  true), // Stalinists hate rich people and corporations
	map<int, bool>::value_type(LAW_FREESPEECH,  false), // Stalinists don't allow any dissent
	map<int, bool>::value_type(LAW_FLAGBURNING,  true), // Stalinists regularly burn flags
	map<int, bool>::value_type(LAW_GUNCONTROL,  true), // Stalinists don't want any armed resistance
	map<int, bool>::value_type(LAW_TAX,  true), // Stalinists support communist income redistribution
	map<int, bool>::value_type(LAW_WOMEN,  false), // Stalinists discriminate against women
	map<int, bool>::value_type(LAW_CIVILRIGHTS,  false), // Stalinists discriminate against ethnic groups
	map<int, bool>::value_type(LAW_DRUGS,  false), // Stalinists only allow vodka
	map<int, bool>::value_type(LAW_IMMIGRATION,  false), // Stalinists maintained tight border security at the Iron Curtain
	map<int, bool>::value_type(LAW_ELECTIONS,  false), // Stalinists don't even have elections
	map<int, bool>::value_type(LAW_MILITARY,  false), // Stalinists use the military for brutal repression
	map<int, bool>::value_type(LAW_PRISONS,  false), // Stalinists annex Canada to fill it with gulags
	map<int, bool>::value_type(LAW_TORTURE,  false), // Stalinists torture their enemies
	map<int, bool>::value_type(LAWNUM,  false), // Liberals and Stalinists don't get along
};
map<int, int> lawReturnAttitude = {
	map<int, int>::value_type(LAW_ABORTION, VIEW_WOMEN), //XXX, There is no ``VIEW_ABORTION''!
	map<int, int>::value_type(LAW_ANIMALRESEARCH, VIEW_ANIMALRESEARCH),
	map<int, int>::value_type(LAW_POLICEBEHAVIOR, VIEW_POLICEBEHAVIOR),
	map<int, int>::value_type(LAW_PRIVACY, VIEW_INTELLIGENCE),
	map<int, int>::value_type(LAW_DEATHPENALTY, VIEW_DEATHPENALTY),
	map<int, int>::value_type(LAW_NUCLEARPOWER, VIEW_NUCLEARPOWER),
	map<int, int>::value_type(LAW_POLLUTION, VIEW_POLLUTION),
	map<int, int>::value_type(LAW_LABOR, VIEW_SWEATSHOPS),
	map<int, int>::value_type(LAW_GAY, VIEW_GAY),
	map<int, int>::value_type(LAW_FREESPEECH, VIEW_FREESPEECH),
	map<int, int>::value_type(LAW_TAX, VIEW_TAXES),
	map<int, int>::value_type(LAW_FLAGBURNING, VIEW_FREESPEECH),  // <-- I'm keeping this pure free speech instead of free speech
	map<int, int>::value_type(LAW_WOMEN, VIEW_WOMEN),             // plus political violence. Ideologically, there's no association
	map<int, int>::value_type(LAW_CIVILRIGHTS, VIEW_CIVILRIGHTS), // between flag burning and violence. - Jonathan S. Fox
	map<int, int>::value_type(LAW_DRUGS, VIEW_DRUGS),
	map<int, int>::value_type(LAW_IMMIGRATION, VIEW_IMMIGRATION), //XXX, VIEW_DRUGS?
	map<int, int>::value_type(LAW_MILITARY, VIEW_MILITARY),
	map<int, int>::value_type(LAW_TORTURE, VIEW_TORTURE),
	map<int, int>::value_type(LAW_GUNCONTROL, VIEW_GUNCONTROL),
	map<int, int>::value_type(LAW_PRISONS, VIEW_PRISONS),
};

extern bool nocourtpurge;
extern bool notermlimit;           //These determine if ELAs can take place --kviiri
extern bool stalinmode;
extern bool termlimits;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char disbanding;
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern int year;
extern Log gamelog;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short execterm;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short presparty;
extern short public_interest[VIEWNUM];
extern short senate[SENATENUM];
extern short wincondition;
extern int getSleeperPresidentStatus();
extern void clearSleeperPresident();
extern int monthsPresidentMissing;

const string CONST_UNITED_STATES = "United States";
const string corporateSuffixtxt = "corporateSuffix.txt";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

void addStringYear();
void printCONST_PRESS_ANY_KEY_TO_CONTINUE_THE_ELECTIONS();
void printCONST_A_RECOUNT_WAS_NECESSARY(const int p);
void printSingleVoteOnBill(const int l, const int yesvotes, const bool yeswin, const int p);
void printSingleSenatorSymbol(const int y, const int x, const short senates);
void printSingleWinnerOfElection(const string winner);
void attemptAmendmentEnding(char canseethings, Alignment enforcedAlignment);
void printReflectOnBill();
void printDeadInCongress();
void printWatchPresidentB();
void printWatchPresident();
void printBillResults(const BillStatus bill, const int c);
void displayCongressHeader(const char clearformess);
void addStringYear();
void displayCongressHeaderPartOne();
void displayCongressHeaderPartTwo();
void displayHouseVotes(const int l, const int yesvotes_h, const char yeswin_h, const int c);
void displaySenateVotes(const int l, const int yesvotes_s, const char yeswin_s, const int c, const int s);
void printHouseElectionsHeader();
void printSingleSenator(const short s, const int x, const int y);
void printSenateElectionsHeader();
void printPressAnyKeyElections();
void printSingleHouseMember(const short h, const int y, const int x);
void printHouseChanges(const int x, const int y, const short h, const int change[]);
void printDetermineBill(const int c, const int billdirc, const int billc);
void printCanSeeCourt(const short courtj, const string courtnamej);
void printCanSeeCourtB(const short courtj, const string courtnamej);
void printChangingOfTheGuard();
void printPressKeyToReflect();
void printStatusQuoOrChange(const int l, const int c, const char yeswin, const int yesvotes);
void printPressKeyToWatch();
void printSenateStatus(const int change[]);
void printSupremeCourtRuling(const int c, const string name1, const string name2, const int scasedirc, const int scasec);
void actuallyPrintSenateWinner(const string winner);
void printCONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD();
void printCurrentProp(const int p, const int propnumsp, const int propdirp, const int propp);
void printImportantProps();
void printElectionYearHeader();
void printTheElectionsAreHeld();
void printSupremeCourtWatch();
void printSupremeCourtDecides();
void printPressKeyToContinueElections();
void printOneSingleVote(const int votesc, const int c, const int winner, const bool lastVote);
void printWatchElectionUnfold();
void printSingleCandidateTitle(const string candidatec1, const char candidatec0, const int c);
//#endif//POLITICS_CPP
//#endif// INCLUDES_H_INCLUDED
