




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
//#ifdef	RECRUIT_CPP
// recruit.cpp
#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"

#include "../creature/deprecatedCreatureB.h"
//#include "../creature/deprecatedCreatureC.h"
//#include "../creature/deprecatedCreatureD.h"

////
#include "../items/armortype.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../basemode/activate.h"
// for recruitFindDifficulty and recruitName
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
// for void printcreatureinfo(Creature *,unsigned char=255)
#include "../common/getnames.h"
// for getview
//#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
// for subordinatesleft
#include "../combat/fight.h"

#include "../common/musicClass.h"

/* recruit struct constructor */

#include "../combat/fight.h"

int getkeyAlt();

void pressAnyKey();

void talk(DeprecatedCreature &a, const int t);

void make_creature_without_encounter_array(const int x, const short type);
short getCurrentSite();
void setCurrentSite(const short i);
extern MusicClass music;
extern short attitude[VIEWNUM];
extern DeprecatedCreature encounter[ENCMAX];

const string MISSING_NO = "missingno";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
void printFoundMultipleRecruits(const string crname);
void printPressEnterToCallItADay(const int recruitCount);
void printAdventuresInRecruitment();
void printSingleRecruit(const int i, const int align, const string name, const string age_string);
void printAskAroundForARecruit(const string recruiter, const string recruit_type);
void printSetupAMeeting(const string crname, const int align, const string rname, const string age_string);
void printWasUnableToTrackDown(const string crname, const string type);
//#endif//RECRUIT_CPP
//#endif// INCLUDES_H_INCLUDED
