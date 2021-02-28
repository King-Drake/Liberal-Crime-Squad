




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
//#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
//#include "activityST.h"

//int get_associated_attribute(int skill_type);

//#include "includesDeprecatedB.h"
//#ifdef	ENDGAME_CPP
// endgame.cpp

const string CONSERVATIVES_HAVE_REMADE_THE_WORLD = "The Conservatives have made the world in their image.";
const string stalinistsRemakeWorld = "The Stalinists have made the world in their image.";
const string youWentOnVacation = "You went on vacation when the country was on the verge of collapse.";
const string youWentIntoHiding = "You went into hiding when the country was on the verge of collapse.";
const string whileYouWereInPrison = "While you were on the inside, the country degenerated...";
const string youDisappearedSafely = "You disappeared safely, but you hadn't done enough.";
const string proposeConservative = "The Arch-Conservative Congress is proposing an ARCH-CONSERVATIVE AMENDMENT!";
const string proposeStalinist = "The Stalinist Congress is proposing a STALINIST AMENDMENT!";
const string they_ll_round_you_up = "They'll round up the last of you up eventually.  All is lost.";
const string pressKeyToReflect = "Press any key to reflect on what has happened.";
const string CONST_YEA = " Yea";
const string CONST_NAY = " Nay";
const string CONST_PRESS_ANY_KEY_TO_BREATHE_A_SIGH_OF_RELIEF = "Press any key to breathe a sigh of relief.                   ";
const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_WHAT_HAS_HAPPENED_ONE_LAST_TIME = "Press any key to reflect on what has happened ONE LAST TIME.";
const string CONST_PRESS_C_TO_WATCH_THE_RATIFICATION_PROCESS_UNFOLD = "Press 'C' to watch the ratification process unfold.";
const string CONST_INVALID_ALIGNMENT_FOR_AMENDMENT = "INVALID ALIGNMENT FOR AMENDMENT";
const string CONST_PRESS_ANY_KEY_TO_HOLD_NEW_ELECTIONS = "Press any key to hold new elections!                           ";
const string CONST_A_NATIONAL_CONVENTION_HAS_PROPOSED_AN_ELITE_LIBERAL_AMENDMENT = "A National Convention has proposed an ELITE LIBERAL AMENDMENT!";
const string CONST_THE_SENATE = "the Senate.";
const string CONST_THE_PRESIDENT_S_CHOOSING_WITH_THE_ADVICE_AND_CONSENT_OF = "the President's choosing with the advice and consent of";
const string CONST_ALSO_OF = ", also of";
const string CONST_A_PROPER_JUSTICE = "a Proper Justice";
const string CONST_PROPER_JUSTICES = "Proper Justices";
const string CONST_CHOOSING_TO_BE_REPLACED_BY = "choosing to be replaced by ";
const string CONST_OF_THE_PRESIDENT_S = " of the President's";
const string CONST_A_CONSERVATIVE_COUNTRY = "a Conservative country";
const string CONST_CONSERVATIVE_COUNTRIES = "Conservative countries";
const string CONST_BE_DEPORTED_TO = "be deported to ";
const string CONST_WILL = " will";
const string CONST_S = "s";
const string CONST_NOT_SERVE_ON_THE_SUPREME_COURT_SAID_FORMER_CITIZEN = "not serve on the Supreme Court.  Said former citizen";
const string CONST_MAY = " may";
const string CONST_IN_PARTICULAR_THE_AFOREMENTIONED_FORMER_CITIZEN = "In particular, the aforementioned former citizen";
const string CONST_BRANDED_ARCH_CONSERVATIVE = " branded Arch-Conservative:";
const string CONST_IS = " is";
const string CONST_S_ARE = "s are";
const string CONST_THE_FOLLOWING_FORMER_CITIZEN = "The following former citizen";
const string CONST_THE_ELITE_LIBERAL_CONGRESS_IS_PROPOSING_AN_ELITE_LIBERAL_AMENDMENT = "The Elite Liberal Congress is proposing an ELITE LIBERAL AMENDMENT!";
const string CONST_TO_THE_UNITED_STATES_CONSTITUTION = " to the United States Constitution:";
const string CONST_PROPOSED_AMENDMENT = "Proposed Amendment ";
const string CONST_AMENDMENT_REJECTED = "AMENDMENT REJECTED.";
const string CONST_AMENDMENT_ADOPTED = "AMENDMENT ADOPTED.";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_STATE_VOTES_UNFOLD = "Press any key to watch the State votes unfold.              ";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_CONGRESSIONAL_VOTES_UNFOLD = "Press any key to watch the Congressional votes unfold.     ";
const string CONST_SENATE = "Senate";
const string CONST_HOUSE = "House";
const string CONST_THE_RATIFICATION_PROCESS = "The Ratification Process:";
const string CONST_STALINIZEDCABINET_TXT = "stalinizedCabinet.txt";
const string CONST_REAGANIFIEDCABINET_TXT = "reaganifiedCabinet.txt";
const string CONST_STALINISTPRISON_TXT = "stalinistPrison.txt";
const string CONST_CONSERVATIVEPRISON_TXT = "conservativePrison.txt";
const string CONST_AMENDMENTPASS_TXT = "amendmentPass.txt";
const string CONST_ARCHCONSERVATIVEAMENDMENT_TXT = "archConservativeAmendment.txt";
const string CONST_STALINAMENDMENT_TXT = "stalinAmendment.txt";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

#include "../creature/creatureEnums.h"
/* fills a string with a proper name */
void generate_name(char *str, char gender = GENDER_NEUTRAL);
#include "../basemode/liberalagenda.h"
// for liberalagenda
//#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for void printfunds(int,int,char*)
#include "../common/misc.h"
// for char* statename(int)
		 //shouldn't be in getnames? --Schmel924
// for romannumeral (int)
		 //only usage here --Schmel924
#include "../title/titlescreen.h"
// for void reset;
#include "../title/highscore.h"
// for void savehighscore(char endtype);
//#include "../monthly/EndGameStatus.h"
//own header
		//does not compile without --Schmel924
#include "../politics/politics.h"
//for publicmood
#include "../cursesAlternative.h"
#include <gui_constants.h>
#include "../set_color_support.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
#include "../common/musicClass.h"
vector<int> state_biases;
vector<string> reaganifiedCabinet;
vector<string> stalinizedCabinet;
vector<string> archConservativeAmendment;
vector<string> stalinAmendment;

vector<string> conservativePrison;
vector<string> stalinistPrison;
vector<string> amendmentPass;
#include "../customMaps.h"
vector<file_and_text_collection> endgame_text_file_collection = {
	customText(&stalinAmendment, MOSTLY_ENDINGS_FOLDER + CONST_STALINAMENDMENT_TXT),
	customText(&archConservativeAmendment, MOSTLY_ENDINGS_FOLDER + CONST_ARCHCONSERVATIVEAMENDMENT_TXT),
	customText(&amendmentPass, MOSTLY_ENDINGS_FOLDER + CONST_AMENDMENTPASS_TXT),
	customText(&conservativePrison, MOSTLY_ENDINGS_FOLDER + CONST_CONSERVATIVEPRISON_TXT),
	customText(&stalinistPrison, MOSTLY_ENDINGS_FOLDER + CONST_STALINISTPRISON_TXT),
	customText(&reaganifiedCabinet, MOSTLY_ENDINGS_FOLDER + CONST_REAGANIFIEDCABINET_TXT),
	customText(&stalinizedCabinet, MOSTLY_ENDINGS_FOLDER + CONST_STALINIZEDCABINET_TXT),
};
struct fullName {
	string first;
	string middle;
	string last;

};
extern bool termlimits;
extern char cantseereason;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern int amendnum;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short senate[SENATENUM];

fullName generate_long_name(char gender = GENDER_NEUTRAL);
//#endif//ENDGAME_CPP
//#endif// INCLUDES_H_INCLUDED
