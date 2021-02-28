




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
/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);
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


// liberalagenda.cpp

#include "../creature/creatureEnums.h"
//#include "../common/commondisplay.h"
void set_alignment_color(short alignment, bool extended_range = false);
//#include "../common/getnames.h"
string getlaw(int l);
//#include "../common/commonactions.h"
void cleangonesquads();
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../common/musicClass.h"
vector<string> supremeChars;
vector<string> courtChars;
map<short, vector<string> > endgameLawStrings;
#include "../common/creaturePool.h"
enum Pages
{
	PAGE_LEADERS,
	PAGE_ISSUES_A,
	PAGE_ISSUES_B,
	PAGENUM
};
vector<string> disbandingMessage;
vector<string> issue_phrases;

extern bool stalinmode;
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern int disbandtime;
extern int year;
extern MusicClass music;
extern short court[COURTNUM];
extern short exec[EXECNUM];
extern short execterm;
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short senate[SENATENUM];
extern short wincondition;

const string pressLToViewHighScores = "Press 'L' to view the high score list.";

const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

const string CONST_COURTCHARS_TXT = "courtChars.txt";
const string CONST_SUPREMECHARS_TXT = "supremeChars.txt";
const string CONST_ISSUE_PHRASES_TXT = "issue_phrases.txt";
const string CONST_DISBANDINGMESSAGE_TXT = "disbandingMessage.txt";
vector<file_and_text_collection> liberl_agenda_text_file_collection = {
customText(&disbandingMessage, MOSTLY_ENDINGS_FOLDER + CONST_DISBANDINGMESSAGE_TXT),
customText(&issue_phrases, MOSTLY_ENDINGS_FOLDER + CONST_ISSUE_PHRASES_TXT),
customText(&supremeChars, MOSTLY_ENDINGS_FOLDER + CONST_SUPREMECHARS_TXT),
customText(&courtChars, MOSTLY_ENDINGS_FOLDER + CONST_COURTCHARS_TXT),
};
const string CONST_TYPE_THIS_LIBERAL_PHRASE_TO_CONFIRM_PRESS_A_WRONG_LETTER_TO_RETHINK_IT = "Type this Liberal phrase to confirm (press a wrong letter to rethink it):";
const string CONST_ARE_YOU_SURE_YOU_WANT_TO_DISBAND = "Are you sure you want to disband?";
const string CONST_PRESS_D_TO_DISBAND_AND_WAIT_USE_CURSORS_FOR_OTHER_PAGES_ANY_OTHER_KEY_TO_EXIT = "Press D to disband and wait. Use cursors for other pages. Any other key to exit.";
const string CONST_ARCH_CONSERVATIVE = "Arch-Conservative";
const string DASH_SPACE = "-  ";
const string CONST_X_CONSERVATIVE_SPACE = "Conservative  ";
const string CONST_X_MODERATE_SPACE = "moderate  ";
const string CONST_X_LIBERAL_SPACE = "Liberal  ";
const string CONST_X_ELITE_LIBERAL_SPACE = "Elite Liberal  ";
const string CONST_X_STALINIST_SPACE = "Stalinist  ";
const string CONST_TRIAL_JUDGES = "Trial Judges";
const string CONST_STALINIST_SHOW = "Stalinist Show";
const string CONST_REPLACED_BY = "Replaced By";
const string CONST_ETHICS_OFFICERS = "Ethics Officers";
const string CONST_BY_CORPORATE = "By Corporate";
const string CONST_REPLACED = "Replaced";
const string CONST_X_SENATE_COLON = "Senate: ";
const string CONST_X_HOUSE_COLON = "House: ";
const string CONST_ATTORNEY_GENERAL = "Attorney General: ";
const string CONST_INTERNAL_AFFAIRS_COMMISSAR = "Internal Affairs Commissar: ";
const string CONST_MINISTER_OF_TRUTH = "Minister of Truth: ";
const string CONST_SECRETARY_OF_STATE = "Secretary of State: ";
const string CONST_FOREIGN_AFFAIRS_COMMISSAR = "Foreign Affairs Commissar: ";
const string CONST_MINISTER_OF_PEACE = "Minister of Peace: ";
const string CONST_VICE_PRESIDENT = "Vice President: ";
const string CONST_PREMIER = "Premier: ";
const string CONST_MINISTER_OF_LOVE = "Minister of Love: ";
const string CONST_2ND_TERM = "(2nd Term):";
const string CONST_1ST_TERM = "(1st Term):";
const string CONST_PRESIDENT = "President ";
const string CONST_GENERAL_SECRETARY = "General Secretary: ";
const string CONST_KING = "King: ";
const string CONST_THE_CONGRESS_CONSISTS_OF_STALINIST_PARTY_LOYALISTS = "The Congress consists of Stalinist Party loyalists.";
const string CONST_THE_CONGRESS_CONSISTS_OF_CEOS_AND_TELEVANGELISTS = "The Congress consists of CEOs and televangelists.";

const string CONST_X_GEN_SUM_FOOTER = "ผ                 ศออออออออออฯออออออออออฯอออออออออออออออออออออออออออออออออออออออ";
const string GENERAL_SUMMARY_ISSUES_HEADER = "บ GENERAL SUMMARY บ ISSUES A ณ ISSUES B ณ";
const string FORMATTED_LINE = "ษอออออออออออออออออปฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤฟ";
const string CONST_X_GEN_SUM_FOOTER_3 = "ฯอออออออออออออออออฯออออออออออผ          ศอออออออออออออออออออออออออออออออออออออออ";
const string CONST_X_GENERAL_SUMMARY_ISSUES_A_ISSUES_B_3 = "ณ GENERAL SUMMARY ณ ISSUES A บ ISSUES B บ";
const string CONST_X_GEN_SUM_HEADER_3 = "ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤยฤฤฤฤฤฤฤฤฤฤษออออออออออป";
const string CONST_X_GEN_SUM_FOOTER_2 = "ฯอออออออออออออออออผ          ศออออออออออฯอออออออออออออออออออออออออออออออออออออออ";
const string CONST_X_GENERAL_SUMMARY_ISSUES_A_ISSUES_B_2 = "ณ GENERAL SUMMARY บ ISSUES A บ ISSUES B ณ";
const string CONST_X_GEN_SUM_HEADER_2 = "ฺฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤษออออออออออปฤฤฤฤฤฤฤฤฤฤฟ";
const string CONST_THE_COUNTRY_HAS_BEEN_STALINIZED = "The country has been Stalinized.";
const string CONST_THE_COUNTRY_HAS_BEEN_REAGANIFIED = "The country has been Reaganified.";
const string CONST_THE_COUNTRY_HAS_ACHIEVED_ELITE_LIBERAL_STATUS = "The country has achieved Elite Liberal status!";
const string CONST_THE_COUNTRY_HAS_ACHIEVED_LIBERAL_STATUS = "The country has achieved Liberal status!";

const string CONST_THE_STATUS_OF_THE_LIBERAL_AGENDA = "The Status of the Liberal Agenda";
const string CONST_THE_ABJECT_FAILURE_OF_THE_LIBERAL_AGENDA = "The Abject Failure of the Liberal Agenda";
const string CONST_THE_TRIUMPH_OF_THE_LIBERAL_AGENDA = "The Triumph of the Liberal Agenda";
const string tag_Sta = "Sta, ";
const string tag_Libp = "Lib+, ";
const string tag_Lib = "Lib, ";
const string tag_Mod = "Mod, ";
const string tag_Cons = "Cons, ";
const string tag_Consp = "Cons+";
//#endif//LIBERALAGENDA_CPP
//#endif// INCLUDES_H_INCLUDED
