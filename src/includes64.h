




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
std::string getactivity(ActivityST& act);
// reviewmode.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locationsEnums.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for void printfunds(int,int,char*)
#include "../common/getnames.h"
// for std::string getactivity(ActivityST)
//#include "../common/equipment.h"
void consolidateloot(vector<Item *>&);
void equipmentbaseassign();
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
/* tells how many total members a squad has (including dead members) */
// for short reviewmodeenum_to_sortingchoiceenum(short)
//#include "../common/translateid.h"
int getsquad(int);
int getpoolcreature(int);
//#include "../monthly/lcsmonthly.h"
void fundreport(char &clearformess);
void printname(const int hiding, const int location, const int flag, const string name);
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../common/creaturePool.h"

void nukeAllEmptySquads(const vector<int> squadloc, const int mode);

const int PAGELENGTH = 19;

extern short mode;
extern short activesortingchoice[SORTINGCHOICENUM];
extern Deprecatedsquadst *activesquad;
extern long cursquadid;
extern MusicClass music;
extern vector<DeprecatedCreature *> pool;
extern vector<Deprecatedsquadst *> squad;
extern int stat_kills;
extern bool multipleCityMode;
//	extern Log gamelog;

int consolidateSiegeLoot();

const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_TEMPORARY_SQUAD_CAMELCAPS = "Temporary Squad";
const string CONST_ACTING_INDIVIDUALLY_CAMELCAPS = "Acting Individually";

void printIAmLeader();
void printPromotionScreenSetup(const int iteration);
void printPromotionScreenSetupB(const int iteration);
void printPromotionScreenSetupD(const int iteration, const int level);
void printIsLoveSlave();
void printIsBrainWashed();
void printJustThis(const string name);
void printPromotionFooter(const bool addPage);
void printPromotionHeader();
void printBaseAssignmentFooter(const bool longPool, const bool manyLocations);
void printBaseName(const bool selectedbase, const int iteration, const string locname);
void printLiberalNameInLocation(const bool currentLocation, const bool underSiege, const bool excludeMention, const int iteration, const string tname, const string lname);
void printBaseAssignmentHeader();
void printLosesHeart(const string name);
void printGainsWisdom(const string name);
void printSwapSquadMember();
void printNameWith(const string name);
void printPerformsExecution(const string executor, const string victim);
void printKillAllyPrompt(const string executor);
void printTestifiesAgainstBoss(const string tname, const string bname);
void printHasBeenReleased(const string name);
void printReleaseLiberalPrompt();
void printWhatIsNewName();
void printReviewModeNameFooter(const bool conservative, const bool morePages);
void printRemoveLiberal();
void printKillLiberal();
void printProfileHeader(const bool conservative);
void printSortPeople();
void printSwapMe(const string name);
void printReorderLiberals();
void printPressLetterToViewStats();
void printReviewStringsHeader(const short mode);
void printREVIEWMODE_CLINIC(const int clinic);
void printREVIEWMODE_SLEEPERS(const int align, const string tname);
void printREVIEWMODE_DEAD(const int deathdays);
void printREVIEWMODE_AWAY(const int hiding, const int dating);
void printREVIEWMODE_JUSTICE(const bool deathpenalty, const int sentence, const int location);
void printREVIEWMODE_HOSTAGES(const int joindays);
void printEvaluateLiberalsHeader(const int iteration, const string tname);
void printLiberalHealthStat(const bool bright, const int iteration, const int skill, const string hstat);
void printREVIEWMODE_LIBERALS();
void printREVIEWMODE_LIBERALS(const int type, const string activity);
void setColorAndPositionForReviewmode(const short mode, const int iteration, const string locationname);
void printGiveThisSquadAName(char *name);
void printSquadCannotBeOnlyConservative();
void printPressLetterToViewLiberalDetails();
void printSquadMustBeAbleToMove();
void printSquadMustBeInSameLocation();
void printAddOrRemoveFromSquad(const int partysize);
void printSquadGreen(const int iteration);
void printSquadYellow(const int iteration);
void printSquadAway(const int iteration);
void printCreatureTypename(const int iteration, const int align, const string type);
void printTotalSkill(const int iteration, const int skill, const bool bright);
void printCreatureNameForSquad(const int iteration, const string name);
void printAssembleSquadHeader(const int partysize, const char newsquad, const string name);
void printReviewModeFooter(const bool musicIsEnabled);
void printReviewModeOptions(const int activity, const int iteration, const int numMembers);
void printReviewHeader();
void printReviewActivity(const int activityTypeID, const int iteration, const string str);
void printSquadLocationAndSiegeStatus(const int cursite, const int y, const bool p);
void printSquadName(const string sname, const bool active, const int iteration);
//#endif//REVIEWMODE_CPP
//#endif// INCLUDES_H_INCLUDED
