




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

// automatedDataTests.cpp
#include "cursesAlternative.h"

extern map<short, string>  conservativeLegalArgument;
extern map<short, string>  youAreStupidTalkAboutIssues;
extern map<short, string>  issueTooLiberal;
extern map<short, string>  issueEventString;
extern map<short, string>  conservatiseLaw;
extern map<short, string>  liberalizeLaw;
extern map<short, string>  discussIssues;
extern map<short, string>  discussesIssues;
extern map<short, vector<string> >  talkAboutTheIssues; 
extern map<short, vector<string> >  endgameLawStrings; 
extern bool multipleCityMode;
extern short lawList[LAWNUM];
void testCreature();

const string CONST_X_TEST = "TEST";
const string SUCCESS = "SUCCESS";

//#endif//AUTOMATEDDATATESTS_CPP
//#endif// INCLUDES_H_INCLUDED
