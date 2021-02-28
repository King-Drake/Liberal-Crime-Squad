#include "includes47.h"
#include "constStringOEMcursesAlternative.h"
#include <mbctype.h>
#include <gui_constants.h>

Log gamelog; //The gamelog.
Log xmllog; // Log for xml errors or bad values.

void setColorBasedOnSiege(const int cursite, const int y, const bool p);

void translategetch(int &c);
void translategetch_cap(int &c);
/* Refreshes the screen, empties the keyboard buffer, waits for a new key to be pressed, and returns the key pressed */
int getkey();
/* Variant of getkey() that doesn't make all letters lowercase */
int getkey_cap();
/* Empties the keyboard buffer, and returns most recent key pressed, if any */
int checkkey();
/* Variant of checkkey() that doesn't make all letters lowercase */
// UNUSED
int checkkey_cap();
void set_title(char *c);
void init_console();
#include <common\\consolesupport.h>

void set_color(short f, short b, bool bright, bool blink = false);
#include "../set_color_support.h"
const ColorSetup RED_ON_WHITE = { COLOR_RED, COLOR_WHITE, 1 };
const ColorSetup BLUE_ON_WHITE = { COLOR_BLUE, COLOR_WHITE, 1 };
const ColorSetup WHITE_ON_BLUE = { COLOR_WHITE, COLOR_BLUE, 1 };
const ColorSetup BLACK_ON_BLACK = { COLOR_BLACK, COLOR_BLACK };
const ColorSetup BLACK_ON_BLACK_BRIGHT = { COLOR_BLACK, COLOR_BLACK, 1 };
const ColorSetup BLACK_ON_WHITE = { COLOR_BLACK, COLOR_WHITE };
const ColorSetup BLUE_ON_BLACK_BRIGHT = { COLOR_BLUE, COLOR_BLACK, 1 };
const ColorSetup CYAN_ON_BLACK = { COLOR_CYAN, COLOR_BLACK };
const ColorSetup CYAN_ON_BLACK_BRIGHT = { COLOR_CYAN, COLOR_BLACK, 1 };
const ColorSetup GREEN_ON_BLACK = { COLOR_GREEN, COLOR_BLACK };
const ColorSetup GREEN_ON_BLACK_BRIGHT = { COLOR_GREEN, COLOR_BLACK, 1 };
const ColorSetup MAGENTA_ON_BLACK = { COLOR_MAGENTA, COLOR_BLACK };
const ColorSetup MAGENTA_ON_BLACK_BRIGHT = { COLOR_MAGENTA, COLOR_BLACK, 1 };
const ColorSetup RED_ON_BLACK = { COLOR_RED, COLOR_BLACK };
const ColorSetup RED_ON_BLACK_BRIGHT = { COLOR_RED, COLOR_BLACK, 1 };
const ColorSetup RED_ON_BLUE_BRIGHT = { COLOR_RED, COLOR_BLUE, 1 };
const ColorSetup RED_ON_GREEN_BRIGHT = { COLOR_RED, COLOR_GREEN, 1 };
const ColorSetup RED_ON_RED = { COLOR_RED, COLOR_RED };
const ColorSetup RED_ON_RED_BRIGHT = { COLOR_RED, COLOR_RED, 1 };
const ColorSetup RED_ON_WHITE_BRIGHT = { COLOR_RED, COLOR_WHITE, 1 };
const ColorSetup BLUE_ON_WHITE_BRIGHT = { COLOR_BLUE, COLOR_WHITE, 1 };
const ColorSetup WHITE_ON_BLACK = { COLOR_WHITE, COLOR_BLACK };
const ColorSetup WHITE_ON_BLACK_BRIGHT = { COLOR_WHITE, COLOR_BLACK, 1 };
const ColorSetup WHITE_ON_RED_BRIGHT = { COLOR_WHITE, COLOR_RED, 1 };
const ColorSetup WHITE_ON_BLUE_BRIGHT = { COLOR_WHITE, COLOR_BLUE, 1 };
const ColorSetup WHITE_ON_WHITE = { COLOR_WHITE, COLOR_WHITE };
const ColorSetup WHITE_ON_WHITE_BRIGHT = { COLOR_WHITE, COLOR_WHITE, 1 };
const ColorSetup YELLOW_ON_BLACK = { COLOR_YELLOW, COLOR_BLACK };
const ColorSetup YELLOW_ON_BLACK_BRIGHT = { COLOR_YELLOW, COLOR_BLACK, 1 };
const ColorSetup YELLOW_ON_RED = { COLOR_YELLOW, COLOR_RED };
const ColorSetup YELLOW_ON_RED_BRIGHT = { COLOR_YELLOW, COLOR_RED, 1 };
const ColorSetup YELLOW_ON_RED_BRIGHT_BLINK = { COLOR_YELLOW, COLOR_RED, 1, 1 };
void printfunds(int y, int offsetx, const char* prefix, long funds);
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../locations/locationsPool.h"
// BASEMODE

const string PLANNING_HEADER = "컴� PLANNING 컴�";
const string ACTIVISM_HEADER = "컴� ACTIVISM 컴�";
const string COLONS_NO_DOTS = ":::::::::";
const string COLONS_AND_DOTS = ":.:.:.:.:";
const string NO_FOOD = " (No Food)";
const string UNDER_SIEGE = "Under Siege";
const string UNDER_ATTACK = "Under Attack";
const string I_INVEST_IN_LOCATION = "I - Invest in this location";

const string tag_Sta = "Sta, ";
const string tag_Libp = "Lib+, ";
const string tag_Lib = "Lib, ";
const string tag_Mod = "Mod, ";
const string tag_Cons = "Cons, ";
const string tag_Consp = "Cons+";
//const string tag_value = "value";
//const string tag_attribute = "attribute";
//const string tag_skill = "skill";
const string HOUSE_COLON = "House: ";
const string SENATE_COLON = "Senate: ";
const string SUPREME_COURT_COLON = "Supreme Court: ";
const string MID_LENGTH_LINE = "컴컴컴컴컴컴컴컴";
const string PUBLIC_MOOD = "Public Mood";
const string LIBERTARIAN = "Libertarian";
const string STALINIST = "Stalinist";
const string CONSERVATIVE = "Conservative";
const string LIBERAL = "Liberal";

bool stalinview(short view, bool islaw);

void printStalinMood() {
	extern short attitude[VIEWNUM];

	signed char align;
	int stalin = 0; // the Stalinist mood position from 1 to 78 (left=Stalinist, right=Libertarian)
	for (int v = 0; v < VIEWNUM - 3; v++)
	{
		stalin += stalinview(v, false) ? attitude[v] : 100 - attitude[v];
	}
	stalin = 78 - (stalin * 77) / ((VIEWNUM - 3) * 100); // very accurate Stalinist mood positioning!
	if (stalin >= 64) align = ALIGN_ELITELIBERAL;
	else if (stalin >= 48) align = ALIGN_LIBERAL;
	else if (stalin >= 32) align = ALIGN_MODERATE;
	else if (stalin >= 16) align = ALIGN_CONSERVATIVE;
	else align = ALIGN_ARCHCONSERVATIVE;
	set_alignment_color(align, true);
	mvaddstrAlt(17, 33, PUBLIC_MOOD);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, STALINIST);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 68, LIBERTARIAN);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(18, 0, "\x11컴컴컴컴컴컴컴�");
	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	mvaddstrAlt(18, 16, MID_LENGTH_LINE);
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(18, 32, MID_LENGTH_LINE);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(18, 48, MID_LENGTH_LINE);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(18, 64, "컴컴컴컴컴컴컴�\x10");
	set_alignment_color(align, true);
	mvaddcharAlt(18, stalin, 'O');
}
void printMood() {
	extern short attitude[VIEWNUM];
	extern bool stalinmode;
	if (stalinmode)
	{
		printStalinMood();
	}


	int mood = 0; // the mood position from 1 to 78 (left=left-wing, right=right-wing)
	for (int v = 0; v < VIEWNUM - 3; v++) { mood += attitude[v]; }
	mood = 78 - (mood * 77) / ((VIEWNUM - 3) * 100); // very accurate mood positioning!
	signed char align;
	if (mood >= 64) align = ALIGN_ARCHCONSERVATIVE;
	else if (mood >= 48) align = ALIGN_CONSERVATIVE;
	else if (mood >= 32) align = ALIGN_MODERATE;
	else if (mood >= 16) align = ALIGN_LIBERAL;
	else align = ALIGN_ELITELIBERAL;
	set_alignment_color(align, true);

	mvaddstrAlt(stalinmode ? 21 : 20, 33, PUBLIC_MOOD);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(21, 1, LIBERAL);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(21, 67, CONSERVATIVE);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 0, "\x11컴컴컴컴컴컴컴�");
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 16, MID_LENGTH_LINE);
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 32, MID_LENGTH_LINE);
	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 48, MID_LENGTH_LINE);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 64, "컴컴컴컴컴컴컴�\x10");
	set_alignment_color(align, true);

	mvaddcharAlt(22, mood, 'O');
}








//
// NEWGAME
const string error = "ERROR";
const string whatIsYourName = "What is your name to the People?";
const string pressEnterToBeRealName = "Press enter to be known by your real name instead.";
void printErrorTypeOther(int ip) {
	clearAlt();
	mvaddstrAlt(0, 0, error);
	mvaddstrAlt(1, 0, ip);

}
void printWhatIsYourName() {
	eraseAlt();

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, whatIsYourName);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(1, 0, pressEnterToBeRealName);
}


// POLITICS

map<short, string> conservatiseLaw;
map<short, string> liberalizeLaw;

const string pressKeyToReflect = "Press any key to reflect on what has happened.";
const string CONST_YEA = " Yea";
const string CONST_NAY = " Nay";
const string establishPrisonReform = "Establish Prison Rehabilitation";
const string improvePrisonConditions = "Improve Prison Conditions";
const string CONST_PRO_HUMAN_RIGHTS = "pro-Human Rights";
const string CONST_FOUR_SPACES = "    ";
const string CONST_NONE_OF_THE_ITEMS_MADE_IT_TO_THE_PRESIDENT_S_DESK = "None of the items made it to the President's desk.";
const string CONST_VETO = "*** VETO ***";
const string CONST_FORCED_BY_CONGRESS = "FORCED BY CONGRESS";
const string CONST_DEAD_IN_CONGRESS = "Dead in Congress";
const string CONST_CC_PRESIDENT = "President";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_PRESIDENT = "Press any key to watch the President.                   ";
const string CONST_VP = "VP";
const string CONST_CC_SENATE = "Senate";
const string CONST_CC_HOUSE = "House";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_VOTES_UNFOLD = "Press any key to watch the votes unfold.";
const string CONST_EXPAND_PRISONERS_RIGHTS = "Expand Prisoners' Rights";
const string CONST_MANDATE_PRISON_REHABILITATION = "Mandate Prison Rehabilitation";
const string CONST_CC_TO_S = "To ";
const string CONST_JOINT_RESOLUTION = "Joint Resolution ";
const string CONST_LEGISLATIVE_AGENDA = "Legislative Agenda ";
const string CONST_CONGRESS_IS_ACTING_ON_LEGISLATION = "Congress is acting on legislation!";
const string CONST_IS_APPOINTED_TO_THE_BENCH = ", is appointed to the bench.";
const string CONST_THE_HONORABLE = "the Honorable ";
const string CONST_COMRADE = "Comrade ";
const string CONST_AFTER_MUCH_DEBATE_AND_TELEVISED_TESTIMONY_A_NEW_JUSTICE = "After much debate and televised testimony, a new justice,";
const string CONST_PRESS_ANY_KEY_TO_SEE_WHAT_HAPPENS = "Press any key to see what happens.";
const string CONST_IS_STEPPING_DOWN = ", is stepping down.";
const string CONST_CC_JUSTICE_S = "Justice ";
const string CONST_CHANGING_THE_GUARD = "Changing the Guard!";
const string CONST_FOR_STATUS_QUO = " for Status Quo";
const string CONST_FOR_CHANGE = " for Change";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_DECISIONS_UNFOLD = "Press any key to watch the decisions unfold.";
const string CONST_A_DECISION_COULD = "A Decision could ";
const string CONST_VS = " vs. ";
const string CONST_SUPREME_COURT_WATCH = "Supreme Court Watch ";
const string CONST_THE_SUPREME_COURT_IS_HANDING_DOWN_DECISIONS = "The Supreme court is handing down decisions!";
const string CONST_A_RECOUNT_WAS_NECESSARY = "A Recount was Necessary";
const string CONST_PERCENT_S_NO = "% No";
const string CONST_PERCENT_S_YES = "% Yes";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD = "Press any key to watch the elections unfold.";
const string CONST_PROPOSITION = "Proposition ";
const string CONST_IMPORTANT_PROPOSITIONS = "Important Propositions ";
const string CONST_PRESS_ANY_KEY_TO_CONTINUE_ELECTIONS_DOT_S_S = "Press any key to continue the elections.   ";
const string CONST_AFTER_RECOUNT = " (After Recount)";
const string CONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTION_UNFOLD = "Press any key to watch the election unfold.";
const string CONST_CC_MRS_DOT = "Mrs. ";
const string CONST_CC_MR_DOT = "Mr. ";
const string CONST_REPRESENTATIVE = "Representative ";
const string CONST_RET_GENERAL = "Ret. General ";
const string CONST_SENATOR = "Senator ";
const string CONST_GOVERNOR = "Governor ";
const string CONST_CC_VICE_PRESIDENT_S = "Vice President ";
const string CONST_CC_PRESIDENT_S = "President ";
const string CONST_AFTER_A_LONG_PRIMARY_CAMPAIGN_THE_PEOPLE_HAVE_RALLIED_AROUND_TWO_LEADERS = "After a long primary campaign, the people have rallied around two leaders...";
const string CONST_AFTER_A_LONG_PRIMARY_CAMPAIGN_THE_PEOPLE_HAVE_RALLIED_AROUND_THREE_LEADERS = "After a long primary campaign, the people have rallied around three leaders...";
const string CONST_PRESIDENTIAL_GENERAL_ELECTION = "Presidential General Election ";
const string CONST_THE_ELECTIONS_ARE_BEING_HELD_TODAY = "The Elections are being held today!";
const string CONST_PRESS_ANY_KEY_TO_CONTINUE_THE_ELECTIONS = "Press any key to continue the elections.    ";
const string CONST_8_SPACES = "        ";
const string CONST_PLUS_SIGN = "+";
const string CONST_UC_SSS_CPLUSCOLON_S = "   C+: ";
const string CONST_UC_SSS_CCOLON_S = "   C: ";
const string CONST_CONST_LC_SSS_MCOLON_S = "   m: ";
const string CONST_UC_SSS_LCOLON_S = "   L: ";
const string CONST_UC_SSS_LPLUSCOLON_S = "   L+: ";
const string CONST_UC_SSS_SCOLON_S = "   S: ";
const string CONST_NET_CHANGE = "Net change:";
const string CONST_UC_S = "S ";
const string CONST_UC_L_PLUS = "L+";
const string CONST_L = "L ";
const string CONST_M = "m ";
const string CONST_UC_C_S = "C ";
const string CONST_UC_C_PLUS = "C+";
const string CONST_HOUSE_ELECTIONS = "House Elections ";
const string CONST_20_SPACES = "                    ";
const string CONST_SENATE_ELECTIONS = "Senate Elections ";
void printSingleSenatorSymbol(const int y, const int x, const short senates) {
	set_alignment_color(senates, true);
	mvaddstrAlt(y, x, getalign(senates, false));

}
void printSingleVoteOnBill(const int l, const int yesvotes, const bool yeswin, const int p) {

	if ((l != 999 && yesvotes > l / 2) || (l == 999 && yeswin)) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (yesvotes < l / 2 || l == 999) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(p * 3 + 2, 70, yesvotes / 10);
	addcharAlt('.');
	addstrAlt(yesvotes % 10);
	addstrAlt(CONST_PERCENT_S_YES);
	if ((l != 999 && yesvotes < l / 2) || (l == 999 && !yeswin)) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (yesvotes > l / 2 || l == 999) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(p * 3 + 3, 70, (l + 1 - yesvotes) / 10);
	addcharAlt('.');
	addstrAlt((l + 1 - yesvotes) % 10);
	addstrAlt(CONST_PERCENT_S_NO);
}
void printCONST_A_RECOUNT_WAS_NECESSARY(const int p) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(p * 3 + 3, 0, CONST_A_RECOUNT_WAS_NECESSARY);

}
void printSingleWinnerOfElection(const string winner) {

	moveAlt(21, 0);
	addstrAlt(winner);
}
void printCONST_PRESS_ANY_KEY_TO_CONTINUE_THE_ELECTIONS() {

	mvaddstrAlt(22, 0, CONST_PRESS_ANY_KEY_TO_CONTINUE_THE_ELECTIONS);
}
void printReflectOnBill() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, pressKeyToReflect + CONST_FOUR_SPACES);
}
void printDeadInCongress() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_NONE_OF_THE_ITEMS_MADE_IT_TO_THE_PRESIDENT_S_DESK);
	mvaddstrAlt(24, 0, pressKeyToReflect + CONST_FOUR_SPACES);
}
void printWatchPresidentB() {

	mvaddstrAlt(0, 35, CONST_CC_PRESIDENT);
}
void printWatchPresident() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_PRESIDENT);
}
void printBillResults(const BillStatus bill, const int c) {
	extern char execname[EXECNUM][POLITICIAN_NAMELEN];
	moveAlt(c * 3 + 2, 35);
	if (bill == BILL_SIGNED)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		if (getSleeperPresidentStatus() != 2)
			addstrAlt(execname[EXEC_PRESIDENT]);
		else
			addstrAlt(execname[EXEC_VP]);
	}
	else if (bill == BILL_FAILED)
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		addstrAlt(CONST_DEAD_IN_CONGRESS);
	}
	else if (bill == BILL_OVERRIDE_VETO)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		addstrAlt(CONST_FORCED_BY_CONGRESS);
	}
	else
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(CONST_VETO);
	}
}
void displayCongressHeader(const char clearformess) {
	if (clearformess) eraseAlt();
	else makedelimiter();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_CONGRESS_IS_ACTING_ON_LEGISLATION);
}
void addStringYear() {
	extern int year;
	addstrAlt(year);
}
void displayCongressHeaderPartOne() {
	//CHANGE THINGS AND REPORT
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_LEGISLATIVE_AGENDA);
	addStringYear();
}
void displayCongressHeaderPartTwo() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_VOTES_UNFOLD);
	pressAnyKey();
	mvaddstrAlt(0, 62, CONST_CC_HOUSE);
	mvaddstrAlt(0, 70, CONST_CC_SENATE);
}
void displayHouseVotes(const int l, const int yesvotes_h, const char yeswin_h, const int c) {
	if (l == HOUSENUM - 1 && yeswin_h) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(c * 3 + 2, 62, yesvotes_h);
	addstrAlt(CONST_YEA);
	if (l == HOUSENUM - 1 && !yeswin_h) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(c * 3 + 3, 62, l + 1 - yesvotes_h);
	addstrAlt(CONST_NAY);
}
void displaySenateVotes(const int l, const int yesvotes_s, const char yeswin_s, const int c, const int s) {

	if (l == HOUSENUM - 1 && yeswin_s) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(c * 3 + 2, 70, yesvotes_s);
	addstrAlt(CONST_YEA);
	if (l == HOUSENUM - 1 && yesvotes_s == SENATEMAJORITY - 1 && yeswin_s)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(c * 3 + 2, 78, CONST_VP);
	}
	if (l == HOUSENUM - 1 && !yeswin_s) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(c * 3 + 3, 70, (s - yesvotes_s));
	addstrAlt(CONST_NAY);
	if (l == HOUSENUM - 1 && yesvotes_s == SENATEMAJORITY - 1 && !yeswin_s)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(c * 3 + 3, 78, CONST_VP);
	}
	if (l % 5 == 0) pause_ms(5);
}
void printSingleHouseMember(const short h, const int y, const int x) {
	moveAlt(y, x);
	switch (h) {
	case -2:
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(CONST_UC_C_PLUS);
		break;

	case -1:
		set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
		addstrAlt(CONST_UC_C_S);
		break;

	case 0:
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		addstrAlt(CONST_M);
		break;

	case 1:
		set_color_easy(CYAN_ON_BLACK_BRIGHT);
		addstrAlt(CONST_L);
		break;

	case 2:
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		addstrAlt(CONST_UC_L_PLUS);
		break;

	default:
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(CONST_UC_S);
		break;
	}
}

void printHouseChanges(const int x, const int y, const short h, const int change[]) {
	extern bool stalinmode;
	printSingleHouseMember(h, y, x);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(20, 0, CONST_NET_CHANGE);
	if (stalinmode)
	{
		addstrAlt(CONST_UC_SSS_SCOLON_S);
		if (change[5] > 0) addstrAlt(CONST_PLUS_SIGN);
		addstrAlt(change[5]);
	}
	addstrAlt(CONST_UC_SSS_LPLUSCOLON_S);
	if (change[4] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[4]);
	addstrAlt(CONST_UC_SSS_LCOLON_S);
	if (change[3] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[3]);
	addstrAlt(CONST_CONST_LC_SSS_MCOLON_S);
	if (change[2] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[2]);
	addstrAlt(CONST_UC_SSS_CCOLON_S);
	if (change[1] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[1]);
	addstrAlt(CONST_UC_SSS_CPLUSCOLON_S);
	if (change[0] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[0]);
	addstrAlt(CONST_8_SPACES);
}
void printHouseMembership() {
	extern short house[HOUSENUM];
	int x = 0;
	int y = 2;
	for (int h = 0; h < HOUSENUM; h++)
	{

		printSingleHouseMember(house[h], y, x);

		x += 3;
		if (x > 78) x = 0, y++;
	}
}
void printHouseElectionsHeader() {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_HOUSE_ELECTIONS);
	addStringYear();
	printHouseMembership();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD);
}
void printSingleSenator(const short s, const int x, const int y) {
	set_alignment_color(s, true);
	mvaddstrAlt(y, x, CONST_20_SPACES);
	mvaddstrAlt(y, x, getalign(s, false));
}
void printSenateElectionsHeader() {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_SENATE_ELECTIONS);
	addStringYear();
}
void printPressAnyKeyElections() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD);
}

void printDetermineBill(const int c, const int billdirc, const int billc) {
	extern short lawList[LAWNUM];

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(c * 3 + 2, 0, CONST_JOINT_RESOLUTION);
	addStringYear();
	addcharAlt('-');
	addstrAlt(c + 1);
	mvaddstrAlt(c * 3 + 3, 0, CONST_CC_TO_S);
	if (billdirc == 1)set_color_easy(GREEN_ON_BLACK_BRIGHT);
	else set_color_easy(RED_ON_BLACK_BRIGHT);
	set_alignment_color(billdirc);
	if (billdirc == 1) {
		if (billc == LAW_PRISONS) {
			if (lawList[LAW_PRISONS] == 1) addstrAlt(establishPrisonReform);
			else addstrAlt(improvePrisonConditions);
		}
		else {
			addstrAlt(liberalizeLaw[billc]);
		}
	}
	else {
		addstrAlt(conservatiseLaw[billc]);
	}
	set_color_easy(WHITE_ON_BLACK);
	refreshAlt();
}
void printCanSeeCourt(const short courtj, const string courtnamej) {
	mvaddstrAlt(4, 0, CONST_AFTER_MUCH_DEBATE_AND_TELEVISED_TESTIMONY_A_NEW_JUSTICE);
	moveAlt(5, 0);
	if (courtj == ALIGN_STALINIST) addstrAlt(CONST_COMRADE);
	else addstrAlt(CONST_THE_HONORABLE);
	addstrAlt(courtnamej);
	addstrAlt(COMMA_SPACE);
	addstrAlt(getalign(courtj, false));
	addstrAlt(CONST_IS_APPOINTED_TO_THE_BENCH);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(7, 0, pressKeyToReflect);
}
void printCanSeeCourtB(const short courtj, const string courtnamej) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(2, 0, CONST_CC_JUSTICE_S);
	addstrAlt(courtnamej);
	addstrAlt(COMMA_SPACE);
	addstrAlt(getalign(courtj, false));
	addstrAlt(CONST_IS_STEPPING_DOWN);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(7, 0, CONST_PRESS_ANY_KEY_TO_SEE_WHAT_HAPPENS);
}
void printChangingOfTheGuard() {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_CHANGING_THE_GUARD);
}
void printPressKeyToReflect() {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, pressKeyToReflect);
}
void printStatusQuoOrChange(const int l, const int c, const char yeswin, const int yesvotes) {
	if (l == COURTNUM - 1 && yeswin)set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == COURTNUM - 1)set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(c * 3 + 2, 63, yesvotes);
	addstrAlt(CONST_FOR_CHANGE);
	if (l == COURTNUM - 1 && !yeswin)set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == COURTNUM - 1)set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(c * 3 + 3, 63, l + 1 - yesvotes);
	addstrAlt(CONST_FOR_STATUS_QUO);
}
void printPressKeyToWatch() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_DECISIONS_UNFOLD);

}
void printSupremeCourtRuling(const int c, const string name1, const string name2, const int scasedirc, const int scasec) {
	extern short lawList[LAWNUM];
	mvaddstrAlt(c * 3 + 2, 0, name1 + CONST_VS + name2);
	mvaddstrAlt(c * 3 + 3, 0, CONST_A_DECISION_COULD);
	set_alignment_color(scasedirc);
	if (scasedirc == 1) {
		if (scasec == LAW_PRISONS) {
			if (lawList[LAW_PRISONS] == 1) addstrAlt(establishPrisonReform);
			else addstrAlt(improvePrisonConditions);
		}
		else {
			addstrAlt(liberalizeLaw[scasec]);
		}
	}
	else {
		addstrAlt(conservatiseLaw[scasec]);
	}
	set_color_easy(WHITE_ON_BLACK);
	refreshAlt();
}
void actuallyPrintSenateWinner(const string winner) {
	moveAlt(21, 0);
	addstrAlt(winner);
	mvaddstrAlt(22, 0, CONST_PRESS_ANY_KEY_TO_CONTINUE_THE_ELECTIONS);

}
void printCONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD() {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD);
}
void printSenateStatus(const int change[]) {
	extern bool stalinmode;

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(20, 0, CONST_NET_CHANGE);
	if (stalinmode)
	{
		addstrAlt(CONST_UC_SSS_SCOLON_S);
		if (change[5] > 0) addstrAlt(CONST_PLUS_SIGN);
		addstrAlt(change[5]);
	}
	addstrAlt(CONST_UC_SSS_LPLUSCOLON_S);
	if (change[4] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[4]);
	addstrAlt(CONST_UC_SSS_LCOLON_S);
	if (change[3] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[3]);
	addstrAlt(CONST_CONST_LC_SSS_MCOLON_S);
	if (change[2] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[2]);
	addstrAlt(CONST_UC_SSS_CCOLON_S);
	if (change[1] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[1]);
	addstrAlt(CONST_UC_SSS_CPLUSCOLON_S);
	if (change[0] > 0) addstrAlt(CONST_PLUS_SIGN);
	addstrAlt(change[0]);
	addstrAlt(CONST_8_SPACES);
}
void printSingleCandidateTitle(const string candidatec1, const char candidatec0, const int c) {
	extern short presparty;
	extern short execterm;
	extern char execname[EXECNUM][POLITICIAN_NAMELEN];
	// Pick color by political orientation
	set_alignment_color(candidatec0, true);
	moveAlt(8 - ((c + 1) % 3) * 2, 0);
	// Choose title -- president or vice president special titles, otherwise
	// pick based on historically likely titles (eg, governor most likely...)
	if (c == presparty && execterm == 1) addstrAlt(CONST_CC_PRESIDENT_S);
	// IsaacG: strcmp() Are you fucking kidding me?
	else if (c == presparty && !strcmp(candidatec1.data(), execname[EXEC_VP])) addstrAlt(CONST_CC_VICE_PRESIDENT_S);
	else if (LCSrandom(2)) addstrAlt(CONST_GOVERNOR);
	else if (LCSrandom(2)) addstrAlt(CONST_SENATOR);
	else if (LCSrandom(2)) addstrAlt(CONST_RET_GENERAL);
	else if (LCSrandom(2)) addstrAlt(CONST_REPRESENTATIVE);
	else if (LCSrandom(2)) addstrAlt(CONST_CC_MR_DOT);
	else addstrAlt(CONST_CC_MRS_DOT);
	addstrAlt(candidatec1);
	addstrAlt(COMMA_SPACE + getalign(candidatec0, false));
}
void printWatchElectionUnfold() {
	extern bool stalinmode;
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(8 + stalinmode * 2, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTION_UNFOLD);
}
void printOneSingleVote(const int votesc, const int c, const int winner, const bool lastVote) {
	if (c == winner) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	moveAlt(8 - ((c + 1) % 3) * 2, 45);
	addstrAlt(votesc / 10);
	addcharAlt('.');
	addstrAlt(votesc % 10);
	addcharAlt('%');
	if (lastVote) addstrAlt(CONST_AFTER_RECOUNT);

}
void printPressKeyToContinueElections() {
	extern bool stalinmode;

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(8 + stalinmode * 2, 0, CONST_PRESS_ANY_KEY_TO_CONTINUE_ELECTIONS_DOT_S_S);
}
void printSupremeCourtDecides() {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_SUPREME_COURT_IS_HANDING_DOWN_DECISIONS);
}
void printSupremeCourtWatch() {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_SUPREME_COURT_WATCH);
	addStringYear();
	set_color_easy(WHITE_ON_BLACK);
}
void printTheElectionsAreHeld() {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_ELECTIONS_ARE_BEING_HELD_TODAY);
}
void printElectionYearHeader() {
	extern bool stalinmode;
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_PRESIDENTIAL_GENERAL_ELECTION);
	addStringYear();
	set_color_easy(WHITE_ON_BLACK);
	moveAlt(2, 0);
	if (stalinmode) addstrAlt(CONST_AFTER_A_LONG_PRIMARY_CAMPAIGN_THE_PEOPLE_HAVE_RALLIED_AROUND_THREE_LEADERS);
	else addstrAlt(CONST_AFTER_A_LONG_PRIMARY_CAMPAIGN_THE_PEOPLE_HAVE_RALLIED_AROUND_TWO_LEADERS);
}
void printImportantProps() {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_IMPORTANT_PROPOSITIONS);
}
void printCurrentProp(const int p, const int propnumsp, const int propdirp, const int propp) {
	extern short lawList[LAWNUM];

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(p * 3 + 2, 0, CONST_PROPOSITION + tostring(propnumsp) + ':');
	mvaddstrAlt(p * 3 + 2, 18, CONST_CC_TO_S);
	set_alignment_color(propdirp);
	if (propdirp == 1) {
		if (propp == LAW_PRISONS) {
			if (lawList[LAW_PRISONS] == 1) addstrAlt(establishPrisonReform);
			else addstrAlt(improvePrisonConditions);
		}
		else {
			addstrAlt(liberalizeLaw[propp]);
		}
	}
	else {
		addstrAlt(conservatiseLaw[propp]);
	}
	set_color_easy(WHITE_ON_BLACK);
}
// POLITICS
///// RECRUIT

const string CONST_ADVENTURES_IN_LIBERAL_RECRUITMENT = "Adventures in Liberal Recruitment";
const string CONST_PRESS_ENTER_OR_ESCAPE_TO_CALL_IT_A_DAY = "Press enter or escape to call it a day.";
const string CONST_SPACE_DASH_SPACE = " - ";
const string CONST_WAS_ABLE_TO_GET_INFORMATION_ON_MULTIPLE_PEOPLE = " was able to get information on multiple people.";
const string CONST_MANAGED_TO_SET_UP_A_MEETING_WITH = " managed to set up a meeting with ";
const string CONST_WAS_UNABLE_TO_TRACK_DOWN_A = " was unable to track down a ";
const string CONST_DOT = ".";
const string CONST_ASKS_AROUND_FOR_A = " asks around for a ";
const string CONST_DOT_DOT_DOT = "...";

void printPressEnterToCallItADay(const int recruitCount) {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(12 + recruitCount + 1, 0, CONST_PRESS_ENTER_OR_ESCAPE_TO_CALL_IT_A_DAY);

}
void printAdventuresInRecruitment() {
	// Used four times!  Excellent.
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_ADVENTURES_IN_LIBERAL_RECRUITMENT);
}
void printSingleRecruit(const int i, const int align, const string name, const string age_string) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(12 + i, 0, char('a' + i) + CONST_SPACE_DASH_SPACE);
	set_alignment_color(align);
	addstrAlt(name);
	addstrAlt(age_string);
}
void printAskAroundForARecruit(const string recruiter, const string recruit_type) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(10, 0, recruiter + CONST_ASKS_AROUND_FOR_A + recruit_type + CONST_DOT_DOT_DOT);
}
void printSetupAMeeting(const string crname, const int align, const string rname, const string age_string) {

	mvaddstrAlt(11, 0, crname + CONST_MANAGED_TO_SET_UP_A_MEETING_WITH);
	set_alignment_color(align);
	addstrAlt(rname);
	addstrAlt(age_string);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(singleDot);
}
void printWasUnableToTrackDown(const string crname, const string type) {

	mvaddstrAlt(11, 0, crname + CONST_WAS_UNABLE_TO_TRACK_DOWN_A + type + CONST_DOT);
}
void printFoundMultipleRecruits(const string crname) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(10, 0, crname + CONST_WAS_ABLE_TO_GET_INFORMATION_ON_MULTIPLE_PEOPLE);
}
///// RECRUIT
// REVIEWMODE

const string CONST_ENLIGHTENED_LIBERALS_FOLLOW_ANYONE_SEDUCED_LIBERALS_FOLLOW_ONLY_THEIR_LOVER = "Enlightened Liberals follow anyone. Seduced Liberals follow only their lover.";
const string CONST_PRESS_A_LETTER_TO_PROMOTE_A_LIBERAL_YOU_CANNOT_PROMOTE_LIBERALS_IN_HIDING = "Press a letter to promote a Liberal. You cannot promote Liberals in hiding.";
const string CONST_LCS_LEADER = "<LCS Leader>";
const string CONST_CAN_T_LEAD_MORE = "<Can't Lead More>";
const string CONST_REFUSES_PROMOTION = "<Refuses Promotion>";
const string CONST_CONTACT_AFTER_PROMOTION = "CONTACT AFTER PROMOTION";
const string CONST_CODE_NAME_HEADER = "컴컴CODE NAME컴컴컴컴컴컴컴CURRENT CONTACT컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string CONST_PROMOTE_THE_ELITE_LIBERALS = "Promote the Elite Liberals";
const string CONST_T_TO_SORT_PEOPLE = "T to sort people.";
const string CONST_COMMA_DOT_TO_VIEW_OTHER_BASE_PAGES = ",. to view other Base pages.";
const string CONST_LIBERALS_MUST_BE_MOVED_IN_SQUADS_TO_TRANSFER_BETWEEN_CITIES = "Liberals must be moved in squads to transfer between cities.";
const string CONST_PRESS_LETTER_TO_ASSIGN_BASE_PRESS_NUMBER_TO_SELECT_BASE = "Press a Letter to assign a Base.  Press a Number to select a Base.";
const string CONST_UNDER_SIEGE = " <Under Siege>";
const string CONST_NEW_BASE = "NEW BASE";
const string CONST_CODE_NAME_CURRENT_BASE_HEADER = "컴컴CODE NAME컴컴컴컴컴컴CURRENT BASE컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�";
const string CONST_NEW_BASES_FOR_SQUADLESS_LIBERALS = "New Bases for Squadless Liberals";
const string CONST_LC_S_WITH = " with";
const string CONST_CHOOSE_SQUAD_MEMBER_TO_REPLACE = "Choose squad member to replace ";
const string CONST_HAS_GAINED_WISDOM = " has gained wisdom.                                                             ";
const string CONST_LC_S_GROWS_COLDER = " grows colder.                                                                  ";
const string CONST_HAS_LOST_HEART = " has lost heart.                                                                ";
const string CONST_FEELS_SICK_TO_THE_STOMACH_AFTERWARD_AND = " feels sick to the stomach afterward and                                        ";
const string CONST_LC_S_BY_S = " by ";
const string CONST_LC_S_EXECUTES_S = " executes ";
const string CONST_C_CONFIRM_ANY_OTHER_KEY_TO_CONTINUE = "  C - Confirm       Any other key to continue                                   ";
const string CONST_KILLING_YOUR_SQUAD_MEMBERS_IS_NOT_A_LIBERAL_ACT = "Killing your squad members is Not a Liberal Act.                                ";
const string CONST_KILL_THIS_SQUAD_MEMBER = " kill this squad member?                               ";
const string CONST_CONFIRM_YOU_WANT_TO_HAVE = "Confirm you want to have ";
const string CONST_IN_COURT = " in court.";
const string CONST_TO_TESTIFY_AGAINST = "to testify against ";
const string CONST_THE_CONSERVATIVE_TRAITOR_HAS_RATTED_YOU_OUT_TO_THE_POLICE_AND_SWORN = "The Conservative traitor has ratted you out to the police, and sworn";
const string CONST_S_WHEREABOUTS = "'s whereabouts.";
const string CONST_A_LIBERAL_FRIEND_TIPS_YOU_OFF_ON = "A Liberal friend tips you off on ";
const string CONST_HAS_BEEN_RELEASED = " has been released.                                                             ";
const string CONST_IF_THE_MEMBER_HAS_LOW_HEART_THEY_MAY_GO_TO_THE_POLICE = "If the member has low heart they may go to the police.                          ";
const string CONST_DO_YOU_WANT_TO_PERMANENTLY_RELEASE_THIS_SQUAD_MEMBER_FROM_THE_LCS = "Do you want to permanently release this squad member from the LCS?              ";
const string CONST_WHAT_IS_THE_NEW_CODE_NAME = "What is the new code name?                                                      ";
const string CONST_UP_DOWN_MORE_INFO = "    UP/DOWN  - More Info";
const string CONST_PRESS_ANY_OTHER_KEY_TO_CONTINUE_THE_STRUGGLE = "Press any other key to continue the Struggle";
const string CONST_LEFT_RIGHT_VIEW_OTHERS = "    LEFT/RIGHT - View Others";
const string CONST_N_CHANGE_CODE_NAME_G_FIX_GENDER_LABEL = "N - Change Code Name      G - Fix Gender Label";
const string CONST_PRESS_N_TO_CHANGE_THIS_AUTOMATON_S_CODE_NAME = "Press N to change this Automaton's Code Name";
const string CONST_K_KILL_MEMBER = "         K - Kill member";
const string CONST_R_REMOVE_MEMBER = "R - Remove member";
const string CONST_PROFILE_OF_A_LIBERAL = "Profile of a Liberal";
const string CONST_PROFILE_OF_AN_AUTOMATON = "Profile of an Automaton";
const string CONST_S_T_TO_SORT_PEOPLE = " T to sort people.";
const string CONST_REORDER_LIBERALS = "Reorder Liberals";
const string CONST_PLACE = "Place ";
const string CONST_PRESS_A_LETTER_TO_VIEW_STATUS_Z = "Press a Letter to View Status.        Z - ";
const string CONST_NO_CONTACT = "<No Contact>";
const string CONST_reviewmode058 = "Day";
const string CONST_DAYS = "Days";
const string CONST_CC_MONTH = "Month";
const string CONST_CC_MONTHS = "Months";
const string CONST_OUT_IN = "Out in ";
const string CONST_7_LINES = "컴컴컴�";
const string CONST_LIFE_SENTENCE = "Life Sentence";
const string CONST_LIFE_SENTENCES = " Life Sentences";
const string CONST_DEATH_ROW = "DEATH ROW: ";
const string CONST_UC_SQUAD = "SQUAD";
const string CONST_SKILL_HEALTH_LOCATION_HEADER = "컴컴CODE NAME컴컴컴컴컴컴SKILL컴횴EALTH컴횸OCATION컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string CONST_SQUAD_DEFAULT_NAME = "The Liberal Crime Squad";
const string CONST_WHAT_SHALL_WE_DESIGNATE_THIS_LIBERAL_SQUAD = "What shall we designate this Liberal squad?                                     ";
const string CONST_YOU_CANNOT_FORM_A_SQUAD_WITH_ONLY_CONSERVATIVES = "You cannot form a Squad with only Conservatives!                                ";
const string CONST_PRESS_A_LETTER_TO_VIEW_LIBERAL_DETAILS = "Press a Letter to view Liberal details.                                         ";
const string CONST_SQUAD_LIBERALS_MUST_BE_ABLE_TO_MOVE_AROUND = "                Squad Liberals must be able to move around.                     ";
const string CONST_LIBERALS_MUST_BE_IN_THE_SAME_LOCATION_TO_FORM_A_SQUAD = "           Liberals must be in the same location to form a Squad.               ";
const string CONST_9_DISSOLVE_THE_SQUAD = "9 - Dissolve the squad.";
const string CONST_ENTER_I_NEED_NO_SQUAD = "Enter - I need no squad!";
const string CONST_ENTER_THE_SQUAD_IS_READY = "Enter - The squad is ready.";
const string CONST_V_VIEW_A_LIBERAL = "V - View a Liberal";
const string CONST_PRESS_A_LETTER_TO_ADD_OR_REMOVE_A_LIBERAL_FROM_THE_SQUAD = "Press a Letter to add or remove a Liberal from the squad.";
const string CONST_AWAY = "AWAY";
const string CONST_CODE_NAME_PROFESSION_HEADER = "컴컴CODE NAME컴컴컴컴컴컴SKILL컴횴EALTH컴컴컴컴컴횾ROFESSION컴컴컴컴컴컴컴컴컴컴";
const string CONST_SQUAD = "Squad: ";
const string CONST_NEW_SQUAD = "New Squad";
const string CONST_THE_SQUAD_IS_FULL = "The squad is full.";
const string CONST_ASSEMBLE_THE_SQUAD = "Assemble the squad!";
const string CONST_GETSSICK_TXT = "getsSick.txt";
const string CONST_METHODOFEXECUTION_TXT = "methodOfExecution.txt";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
vector<string> methodOfExecution;
vector<string> getsSick;
vector<file_and_text_collection> reviewmode_text_file_collection = {
	/*transferred via algorithm*/
	customText(&methodOfExecution, MOSTLY_ENDINGS_FOLDER + CONST_METHODOFEXECUTION_TXT),
	customText(&getsSick, MOSTLY_ENDINGS_FOLDER + CONST_GETSSICK_TXT),
};
map<short, string> reviewStrings;
map<short, string> reviewStringsSecondLine;
struct stringAndColor
{
	string str;
	ColorSetup type;
	stringAndColor(const string& str_, const ColorSetup type_) : str(str_), type(type_) { }
	stringAndColor(const ColorSetup type_, const string& str_) : str(str_), type(type_) { }
};
vector<stringAndColor> liberalListAndColor;
void printJustThis(const string name) {
	// TODO remove this function
	addstrAlt(name);
}
void printPromotionFooter(const bool addPage) {

	moveAlt(21, 0);
	for (stringAndColor s : liberalListAndColor) {
		set_color_easy(s.type);
		addstrAlt(s.str);
	}
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_PROMOTE_A_LIBERAL_YOU_CANNOT_PROMOTE_LIBERALS_IN_HIDING);
	mvaddstrAlt(23, 0, CONST_ENLIGHTENED_LIBERALS_FOLLOW_ANYONE_SEDUCED_LIBERALS_FOLLOW_ONLY_THEIR_LOVER);
	if (addPage)
	{
		mvaddstrAlt(24, 0, addpagestr());
	}
}
void printPromotionHeader() {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, CONST_PROMOTE_THE_ELITE_LIBERALS);
	mvaddstrAlt(1, 0, CONST_CODE_NAME_HEADER); // 80 characters
	mvaddstrAlt(1, 54, CONST_CONTACT_AFTER_PROMOTION);
}
void printIAmLeader() {

	addstrAlt(CONST_LCS_LEADER);
}
void printPromotionScreenSetup(const int iteration) {
	set_color_easy(WHITE_ON_BLACK);
	mvaddcharAlt(iteration + 2, 0, iteration + 'A');
	addstrAlt(spaceDashSpace);
	moveAlt(iteration + 2, 27);
}

void printPromotionScreenSetupB(const int iteration) {
	moveAlt(iteration + 2, 54);
}

void printPromotionScreenSetupD(const int iteration, const int level) {

	moveAlt(iteration + 2, 4 + level);
}
void printIsLoveSlave() {
	addstrAlt(CONST_REFUSES_PROMOTION);

}
void printIsBrainWashed() {
	addstrAlt(CONST_CAN_T_LEAD_MORE);

}

void printBaseAssignmentFooter(const bool longPool, const bool manyLocations) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(21, 0, CONST_PRESS_LETTER_TO_ASSIGN_BASE_PRESS_NUMBER_TO_SELECT_BASE);
	mvaddstrAlt(22, 0, CONST_LIBERALS_MUST_BE_MOVED_IN_SQUADS_TO_TRANSFER_BETWEEN_CITIES);
	if (longPool)
	{
		mvaddstrAlt(23, 0, addpagestr());
	}
	if (manyLocations)
	{
		mvaddstrAlt(24, 0, CONST_COMMA_DOT_TO_VIEW_OTHER_BASE_PAGES);
	}
	mvaddstrAlt(23, 35, CONST_T_TO_SORT_PEOPLE);
}

void printBaseName(const bool selectedbase, const int iteration, const string locname) {

	if (selectedbase)set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddcharAlt(iteration + 2, 51, iteration + '1'); addstrAlt(spaceDashSpace);
	addstrAlt(locname);
}
void printLiberalNameInLocation(const bool currentLocation, const bool underSiege, const bool excludeMention, const int iteration, const string tname, const string lname) {

	if (currentLocation && underSiege)
		set_color_easy(RED_ON_BLACK_BRIGHT);
	else if (excludeMention)
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddcharAlt(iteration + 2, 0, iteration + 'A'); addstrAlt(spaceDashSpace);
	addstrAlt(tname);
	mvaddstrAlt(iteration + 2, 25, lname);
	if (underSiege)
	{
		addstrAlt(CONST_UNDER_SIEGE);
	}
}
void printBaseAssignmentHeader() {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, CONST_NEW_BASES_FOR_SQUADLESS_LIBERALS);
	mvaddstrAlt(1, 0, CONST_CODE_NAME_CURRENT_BASE_HEADER); // 80 characters
	mvaddstrAlt(1, 51, CONST_NEW_BASE);
}

void printLosesHeart(const string name) {

	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	gamelog.newline(); //New line.
	mvaddstrAlt(22, 0, name, gamelog);
	addstrAlt(CONST_FEELS_SICK_TO_THE_STOMACH_AFTERWARD_AND, gamelog); // 80 characters
	// this sentence probably takes more than 80 characters so use 2 lines and break it here
	gamelog.newline(); //New line.
	mvaddstrAlt(23, 0, pickrandom(getsSick), gamelog);
	gamelog.newline(); //New line.
	mvaddstrAlt(24, 0, name, gamelog);
	addstrAlt(CONST_HAS_LOST_HEART, gamelog); // 80 characters
	gamelog.nextMessage(); //Write buffer out to prepare for next message.
}
void printGainsWisdom(const string name) {

	gamelog.newline(); //New line here too.
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 0, name, gamelog);
	addstrAlt(CONST_LC_S_GROWS_COLDER, gamelog); // 80 characters
	gamelog.newline(); //New line.
	mvaddstrAlt(24, 0, name, gamelog);
	addstrAlt(CONST_HAS_GAINED_WISDOM, gamelog); // 80 characters
	gamelog.nextMessage(); //Write buffer out to prepare for next message.
}
void printSwapSquadMember() {
	mvaddstrAlt(22, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(23, 0, CONST_80_SPACES); // 80 spaces
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 8, CONST_CHOOSE_SQUAD_MEMBER_TO_REPLACE);
}
void printNameWith(const string name) {

	addstrAlt(name);
	addstrAlt(CONST_LC_S_WITH);
}
void printPerformsExecution(const string executor, const string victim) {

	mvaddstrAlt(22, 0, executor, gamelog);
	addstrAlt(CONST_LC_S_EXECUTES_S, gamelog); // 10 characters (10+4+66=80)
	addstrAlt(victim, gamelog);
	addstrAlt(CONST_LC_S_BY_S, gamelog); // 4 characters (10+4+66=80)
	addstrAlt(pickrandom(methodOfExecution), gamelog);
	mvaddstrAlt(23, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces
}
void printKillAllyPrompt(const string executor) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(22, 0, CONST_CONFIRM_YOU_WANT_TO_HAVE); // 25 characters (25+55=80)
	addstrAlt(executor);
	addstrAlt(CONST_KILL_THIS_SQUAD_MEMBER); // 55 characters (25+55=80)
	mvaddstrAlt(23, 0, CONST_KILLING_YOUR_SQUAD_MEMBERS_IS_NOT_A_LIBERAL_ACT); // 80 characters
	mvaddstrAlt(24, 0, CONST_C_CONFIRM_ANY_OTHER_KEY_TO_CONTINUE); // 80 characters
}
void printTestifiesAgainstBoss(const string tname, const string bname) {
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 0, CONST_A_LIBERAL_FRIEND_TIPS_YOU_OFF_ON, gamelog);
	addstrAlt(tname, gamelog);
	addstrAlt(CONST_S_WHEREABOUTS, gamelog);
	gamelog.newline(); //New line.
	mvaddstrAlt(24, 0, CONST_THE_CONSERVATIVE_TRAITOR_HAS_RATTED_YOU_OUT_TO_THE_POLICE_AND_SWORN, gamelog);
	gamelog.newline(); //New line.
	mvaddstrAlt(25, 0, CONST_TO_TESTIFY_AGAINST, gamelog);
	addstrAlt(bname, gamelog);
	addstrAlt(CONST_IN_COURT, gamelog);
	gamelog.nextMessage(); //Write out buffer to prepare for next message.
}
void printHasBeenReleased(const string name) {
	mvaddstrAlt(22, 0, name, gamelog);
	addstrAlt(CONST_HAS_BEEN_RELEASED, gamelog); // 80 characters
	gamelog.newline(); //New line.
	mvaddstrAlt(23, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces
	gamelog.nextMessage(); //Write out buffer to prepare for next message.
}
void printReleaseLiberalPrompt() {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(22, 0, CONST_DO_YOU_WANT_TO_PERMANENTLY_RELEASE_THIS_SQUAD_MEMBER_FROM_THE_LCS); // 80 characters
	mvaddstrAlt(23, 0, CONST_IF_THE_MEMBER_HAS_LOW_HEART_THEY_MAY_GO_TO_THE_POLICE); // 80 characters
	mvaddstrAlt(24, 0, CONST_C_CONFIRM_ANY_OTHER_KEY_TO_CONTINUE); // 80 characters
}
void printWhatIsNewName() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_WHAT_IS_THE_NEW_CODE_NAME); // 80 characters
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces
}
void printReviewModeNameFooter(const bool conservative, const bool morePages) {

	moveAlt(23, 0);
	if (conservative) addstrAlt(CONST_PRESS_N_TO_CHANGE_THIS_AUTOMATON_S_CODE_NAME);
	else addstrAlt(CONST_N_CHANGE_CODE_NAME_G_FIX_GENDER_LABEL);
	if (morePages) addstrAlt(CONST_LEFT_RIGHT_VIEW_OTHERS);
	mvaddstrAlt(24, 0, CONST_PRESS_ANY_OTHER_KEY_TO_CONTINUE_THE_STRUGGLE);
	addstrAlt(CONST_UP_DOWN_MORE_INFO);
}
void printRemoveLiberal() {
	moveAlt(22, 0);
	addstrAlt(CONST_R_REMOVE_MEMBER);

}
void printKillLiberal() {

	addstrAlt(CONST_K_KILL_MEMBER);
}
void printProfileHeader(const bool conservative) {

	eraseAlt();
	moveAlt(0, 0);
	if (conservative)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(CONST_PROFILE_OF_AN_AUTOMATON);
	}
	else
	{
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		addstrAlt(CONST_PROFILE_OF_A_LIBERAL);
	}
}

void printSortPeople() {

	mvaddstrAlt(23, 0, addpagestr() + CONST_S_T_TO_SORT_PEOPLE);
}
void printSwapMe(const string name) {
	addstrAlt(CONST_PLACE);
	addstrAlt(name);

}
void printReorderLiberals() {
	addstrAlt(CONST_REORDER_LIBERALS);
}
void printPressLetterToViewStats() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_VIEW_STATUS_Z);
}
void printReviewStringsHeader(const short mode) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, reviewStrings[mode]);
	mvaddstrAlt(1, 0, CONST_SKILL_HEALTH_LOCATION_HEADER); // 80 characters
	mvaddstrAlt(1, 57, reviewStringsSecondLine[mode]);
}

void printREVIEWMODE_CLINIC(const int clinic) {

	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	addstrAlt(CONST_OUT_IN);
	addstrAlt(clinic);
	addstrAlt(singleSpace);
	if (clinic > 1) {
		addstrAlt(CONST_CC_MONTHS);
	}
	else {
		addstrAlt(CONST_CC_MONTH);
	}
}
void printREVIEWMODE_SLEEPERS(const int align, const string tname) {

	if (align == -1)set_color_easy(RED_ON_BLACK_BRIGHT);
	else if (align == 0)set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else set_color_easy(GREEN_ON_BLACK_BRIGHT);
	addstrAlt(tname);
}
void printREVIEWMODE_DEAD(const int deathdays) {

	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	addstrAlt(deathdays);
	addstrAlt(singleSpace);
	if (deathdays > 1) {
		addstrAlt(CONST_DAYS);
	}
	else {
		addstrAlt(CONST_reviewmode058);
	}
}
void printREVIEWMODE_AWAY(const int hiding, const int dating) {

	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	if (hiding != -1)
	{
		addstrAlt(dating + hiding);
		addstrAlt(singleSpace);
		if (dating + hiding > 1)
			addstrAlt(CONST_DAYS);
		else addstrAlt(CONST_reviewmode058);
	}
	else addstrAlt(CONST_NO_CONTACT);
}

void printREVIEWMODE_JUSTICE(const bool deathpenalty, const int sentence, const int location) {
	if (deathpenalty&&sentence != 0 &&
		location == SITE_GOVERNMENT_PRISON)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(CONST_DEATH_ROW);
		addstrAlt(sentence);
		addstrAlt(singleSpace);
		if (sentence > 1)addstrAlt(CONST_CC_MONTHS);
		else addstrAlt(CONST_CC_MONTH);
	}
	else if (sentence <= -1 &&
		location == SITE_GOVERNMENT_PRISON)
	{
		set_color_easy(WHITE_ON_BLACK);
		if (sentence < -1)
		{
			addstrAlt(-sentence);
			addstrAlt(CONST_LIFE_SENTENCES);
		}
		else
			addstrAlt(CONST_LIFE_SENTENCE);
	}
	else if (sentence != 0 &&
		location == SITE_GOVERNMENT_PRISON)
	{
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		addstrAlt(sentence);
		addstrAlt(singleSpace);
		if (sentence > 1)addstrAlt(CONST_CC_MONTHS);
		else addstrAlt(CONST_CC_MONTH);
	}
	else
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		addstrAlt(CONST_7_LINES); // 7 characters
	}
}
void printREVIEWMODE_HOSTAGES(const int joindays) {

	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	addstrAlt(joindays);
	addstrAlt(singleSpace);
	if (joindays > 1)addstrAlt(CONST_DAYS);
	else addstrAlt(CONST_reviewmode058);
}

void printEvaluateLiberalsHeader(const int iteration, const string tname) {

	set_color_easy(WHITE_ON_BLACK);

	mvaddcharAlt(iteration + 2, 0, iteration + 'A');
	addstrAlt(spaceDashSpace);
	addstrAlt(tname);
}
void printLiberalHealthStat(const bool bright, const int iteration, const int skill, const string hstat) {

	set_color_easy(bright ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	mvaddstrAlt(iteration + 2, 25, skill);
	mvaddstrAlt(iteration + 2, 33, hstat);

}
void printREVIEWMODE_LIBERALS() {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	addstrAlt(CONST_UC_SQUAD);

}
void printREVIEWMODE_LIBERALS(const int type, const string activity) {

	set_activity_color(type);
	addstrAlt(activity);
}
void setColorAndPositionForReviewmode(const short mode, const int iteration, const string locationname) {

	if (mode == REVIEWMODE_JUSTICE) {
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	}
	else {
		set_color_easy(WHITE_ON_BLACK);
	}

	moveAlt(iteration + 2, 42);

	addstrAlt(locationname);

	moveAlt(iteration + 2, 57);
}
void printGiveThisSquadAName(char *name) {
	mvaddstrAlt(22, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(23, 0, CONST_WHAT_SHALL_WE_DESIGNATE_THIS_LIBERAL_SQUAD); // 80 characters
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces
	enter_name(24, 0, name, SQUAD_NAMELEN, CONST_SQUAD_DEFAULT_NAME.c_str());

}
void printSquadCannotBeOnlyConservative() {
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(23, 0, CONST_YOU_CANNOT_FORM_A_SQUAD_WITH_ONLY_CONSERVATIVES); // 80 characters
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces
}
void printPressLetterToViewLiberalDetails()
{
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_VIEW_LIBERAL_DETAILS); // 80 characters
	mvaddstrAlt(23, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces
}
void printSquadMustBeAbleToMove() {
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(23, 0, CONST_SQUAD_LIBERALS_MUST_BE_ABLE_TO_MOVE_AROUND); // 80 characters
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces

}
void printSquadMustBeInSameLocation() {

	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(22, 0, CONST_80_SPACES); // 80 spaces
	mvaddstrAlt(23, 0, CONST_LIBERALS_MUST_BE_IN_THE_SAME_LOCATION_TO_FORM_A_SQUAD); // 80 characters
	mvaddstrAlt(24, 0, CONST_80_SPACES); // 80 spaces
}
void printAddOrRemoveFromSquad(const int partysize) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_ADD_OR_REMOVE_A_LIBERAL_FROM_THE_SQUAD);
	mvaddstrAlt(23, 0, addpagestr() + CONST_S_T_TO_SORT_PEOPLE);
	mvaddstrAlt(23, 50, CONST_V_VIEW_A_LIBERAL);
	moveAlt(24, 0);
	if (partysize > 0) addstrAlt(CONST_ENTER_THE_SQUAD_IS_READY);
	else addstrAlt(CONST_ENTER_I_NEED_NO_SQUAD);
	if (partysize > 0) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(24, 40, CONST_9_DISSOLVE_THE_SQUAD);
}
void printSquadGreen(const int iteration) {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(iteration + 2, 75, CONST_UC_SQUAD);

}
void printSquadYellow(const int iteration) {
	set_color_easy(YELLOW_ON_BLACK);
	mvaddstrAlt(iteration + 2, 75, CONST_UC_SQUAD);

}
void printSquadAway(const int iteration) {
	set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(iteration + 2, 75, CONST_AWAY);

}
void printCreatureTypename(const int iteration, const int align, const string type) {

	if (align == -1) set_color_easy(RED_ON_BLACK_BRIGHT);
	else if (align == 0) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(iteration + 2, 50, type);
}
void printTotalSkill(const int iteration, const int skill, const bool bright) {

	set_color_easy(bright ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	mvaddstrAlt(iteration + 2, 25, skill);
}
void printCreatureNameForSquad(const int iteration, const string name) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddcharAlt(iteration + 2, 0, iteration + 'A');
	addstrAlt(spaceDashSpace);
	addstrAlt(name);
}
void printAssembleSquadHeader(const int partysize, const char newsquad, const string name) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	moveAlt(0, 0);
	if (partysize < 6)addstrAlt(CONST_ASSEMBLE_THE_SQUAD);
	else addstrAlt(CONST_THE_SQUAD_IS_FULL);
	if (newsquad)
	{
		mvaddstrAlt(0, 71, CONST_NEW_SQUAD);
	}
	else
	{
		mvaddstrAlt(0, 73 - len(name), CONST_SQUAD);
		addstrAlt(name);
	}
	mvaddstrAlt(1, 0, CONST_CODE_NAME_PROFESSION_HEADER); // 80 characters
}

const string CONST_PRESS_Z_TO_ASSEMBLE_A_NEW_SQUAD_PRESS_T_TO_ASSIGN_NEW_BASES_TO_THE_SQUADLESS = "Press Z to Assemble a New Squad.  Press T to Assign New Bases to the Squadless.";
const string CONST_PRESS_U_TO_PROMOTE_LIBERALS = "  Press U to Promote Liberals.";
const string CONST_PRESS_A_LETTER_TO_SELECT_A_SQUAD_1_7_TO_VIEW_LIBERAL_GROUPS = "Press a Letter to select a squad.  1-7 to view Liberal groups.";
const string CONST_PRESS_Y_TO_TURN_ON_SOME_MUSIC = "Press Y to turn on some Music.";
const string CONST_PRESS_Y_TO_TURN_OFF_THE_MUSIC = "Press Y to turn off the Music.";
const string CONST_PRESS_V_TO_INSPECT_LIBERAL_FINANCES = "Press V to Inspect Liberal finances.";

const string CONST_8_REVIEW_AND_MOVE_EQUIPMENT = "8 - Review and Move Equipment (";
const string CONST_7_AWAY = "7 - Away (";
const string CONST_6_THE_DEAD = "6 - The Dead (";
const string CONST_5_SLEEPERS = "5 - Sleepers (";
const string CONST_4_JUSTICE_SYSTEM = "4 - Justice System (";
const string CONST_3_HOSPITAL = "3 - Hospital (";
const string CONST_2_HOSTAGES = "2 - Hostages (";
const string CONST_1_ACTIVE_LIBERALS = "1 - Active Liberals (";
const string CONST_SQUAD_NAME_LOCATION_ACTIVITY_HEADER = "컴컴SQUAD NAME컴컴컴컴컴컴컴컴횸OCATION컴컴컴컴컴컴ACTIVITY컴컴컴컴컴컴컴컴컴컴�";
const string CONST_REVIEW_YOUR_LIBERALS_AND_ASSEMBLE_SQUADS = "Review your Liberals and Assemble Squads";
void printReviewHeader() {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, CONST_REVIEW_YOUR_LIBERALS_AND_ASSEMBLE_SQUADS);
	mvaddstrAlt(1, 0, CONST_SQUAD_NAME_LOCATION_ACTIVITY_HEADER); // 80 characters
}
void printReviewActivity(const int activityTypeID, const int iteration, const string str) {

	set_activity_color(activityTypeID);

	mvaddstrAlt(iteration + 2, 51, str);
}
void printSquadLocationAndSiegeStatus(const int cursite, const int iteration, const bool activesquad) {
	setColorBasedOnSiege(cursite, iteration + 2, activesquad);

}
void printSquadName(const string sname, const bool active, const int iteration) {
	set_color_easy(active ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	mvaddcharAlt(iteration + 2, 0, iteration + 'A');
	addstrAlt(spaceDashSpace);
	addstrAlt(sname);
}
void printReviewModeOptions(const int activity, const int iteration, const int numMembers) {

	bool invalid = false;
	ColorSetup const_color;
	string active_string;
	switch (activity) {
	case REVIEWMODE_LIBERALS: //0
		const_color = GREEN_ON_BLACK_BRIGHT;
		active_string = CONST_1_ACTIVE_LIBERALS;
		break;

	case REVIEWMODE_HOSTAGES: //1
		const_color = RED_ON_BLACK_BRIGHT;
		active_string = CONST_2_HOSTAGES;
		break;
	case REVIEWMODE_CLINIC: // 2
		const_color = WHITE_ON_BLACK_BRIGHT;
		active_string = CONST_3_HOSPITAL;
		break;
	case REVIEWMODE_JUSTICE: // 3
		const_color = YELLOW_ON_BLACK_BRIGHT;
		active_string = CONST_4_JUSTICE_SYSTEM;
		break;
	case REVIEWMODE_SLEEPERS: // 4
		const_color = MAGENTA_ON_BLACK_BRIGHT;
		active_string = CONST_5_SLEEPERS;
		break;
	case REVIEWMODE_DEAD: // 5
		const_color = BLACK_ON_BLACK_BRIGHT;
		active_string = CONST_6_THE_DEAD;
		break;
	case REVIEWMODE_AWAY: // 6
		const_color = BLUE_ON_BLACK_BRIGHT;
		active_string = CONST_7_AWAY;
		break;
	case REVIEWMODENUM: // 7 review and move equipment
		const_color = CYAN_ON_BLACK_BRIGHT;
		active_string = CONST_8_REVIEW_AND_MOVE_EQUIPMENT;
		break;
	default: // should never happen, would throw an exception before reaching this point, as numMembers is taken from an array whose maximum index is REVIEWMODENUM
		invalid = true;
		break;
	}
	if (!invalid) {
		set_color_easy(const_color);
		mvaddstrAlt(iteration + 2, 0, active_string + tostring(numMembers) + ')');
	}
}
void printReviewModeFooter(const bool musicIsEnabled) {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(21, 0, CONST_PRESS_V_TO_INSPECT_LIBERAL_FINANCES);
	if (musicIsEnabled)
		mvaddstrAlt(21, 38, CONST_PRESS_Y_TO_TURN_OFF_THE_MUSIC);
	else mvaddstrAlt(21, 38, CONST_PRESS_Y_TO_TURN_ON_SOME_MUSIC);
	mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_SELECT_A_SQUAD_1_7_TO_VIEW_LIBERAL_GROUPS);
	mvaddstrAlt(23, 0, addpagestr() + CONST_PRESS_U_TO_PROMOTE_LIBERALS);
	mvaddstrAlt(24, 0, CONST_PRESS_Z_TO_ASSEMBLE_A_NEW_SQUAD_PRESS_T_TO_ASSIGN_NEW_BASES_TO_THE_SQUADLESS);
}
// end REVIEWMODE

// SAVELOAD

const string itemType = "Item type ";
const string doesNotExistItem = " does not exist. Deleting item.";
const string vehicleType = "Vehicle type ";
const string doesNotExistVehicle = " does not exist. Deleting vehicle.";
void printInvalidVehicle(const string typeidname) {

	addstrAlt(vehicleType + typeidname + doesNotExistVehicle);
}
void printInvalidItem(const string typeidname) {

	addstrAlt(itemType);
	addstrAlt(typeidname);
	addstrAlt(doesNotExistItem);
}

// end SAVELOAD


// SHOP



const string CONST_DOLLAR_SIGN = "$";

string asMoney(const int c) {
	return CONST_DOLLAR_SIGN + tostring(c);
}
const string CONST_ENTER = "Enter - ";
const string CONST_B_CHOOSE_A_BUYER = "B - Choose a buyer";
const string CONST_S_SELL_SOMETHING = "S - Sell something";
const string CONST_E_LOOK_OVER_EQUIPMENT = "E - Look over Equipment";
const string CONST_M_BUY_A_MASK_15 = "M - Buy a Mask                ($15)";
const string CONST_BUYER = "Buyer: ";
const string CONST_WITH_A_RANDOM_MASK = " With a Random Mask";
const string CONST_Z_SURPRISE = "Z - Surprise ";
const string CONST_PRESS_A_LETTER_TO_SELECT_A_MASK = "Press a Letter to select a Mask";
const string CONST_PRODUCT_NAME_HEADER = "컴컴PRODUCT NAME컴컴컴컴컴컴컴컴컴컴컴DESCRIPTION컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string CONST_BUY = " buy?";
const string CONST_WHICH_MASK_WILL = "Which mask will ";
const string CONST_SPEND = "SPEND.";
const string CONST_TO_LIBERAL_FUNDS = " to Liberal Funds.";
const string CONST_YOU_ADD = "You add $";
const string CONST_REALLY_SELL_ALL_CLOTHES_Y_ES_TO_CONFIRM = "Really sell all clothes? (Y)es to confirm.           ";
const string CONST_REALLY_SELL_ALL_AMMO_Y_ES_TO_CONFIRM = "Really sell all ammo? (Y)es to confirm.              ";
const string CONST_REALLY_SELL_ALL_WEAPONS_Y_ES_TO_CONFIRM = "Really sell all weapons? (Y)es to confirm.           ";
const string CONST_ENTER_DONE_PAWNING = "Enter - Done pawning";
const string CONST_L_PAWN_ALL_LOOT = "L - Pawn all Loot";
const string CONST_C_PAWN_ALL_CLOTHES = "C - Pawn all Clothes";
const string CONST_A_PAWN_ALL_AMMUNITION = "A - Pawn all Ammunition";
const string CONST_W_PAWN_ALL_WEAPONS = "W - Pawn all Weapons";
const string CONST_F_PAWN_SELECTIVELY = "F - Pawn Selectively";
const string CONST_YOU_CAN_T_SELL_DAMAGED_GOODS = " You can't sell damaged goods.";
const string CONST_PRESS_A_LETTER_TO_SELECT_AN_ITEM_TO_SELL = "Press a letter to select an item to sell.";
const string CONST_LC_X = " x";
const string CONST_SLASH = "/";
const string CONST_ESTIMATED_LIBERAL_AMOUNT = "Estimated Liberal Amount: $";
const string CONST_WHAT_WILL_YOU_SELL = "What will you sell?";
const string CONST_PRESS_A_LETTER_TO_SELECT_AN_OPTION = "Press a Letter to select an option";
const string CONST_PRODUCT_NAME_PRICE_HEADER = "컴컴PRODUCT NAME컴컴컴컴컴컴컴컴컴컴컴PRICE컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴";
const string CONST_WHAT_WILL = "What will ";


void printBrowseHalfscreenHeader(const string cname) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(8, 45, CONST_BUYER);
	addstrAlt(cname);
}

void printShopOptions(const int y, const bool x, const char letter, const string description) {

	set_color_easy(WHITE_ON_BLACK);
	int xNew = x ? 1 : 40;
	mvaddstrAlt(y + 10, xNew, letter + spaceDashSpace + description);
}
void printShopFooter(const int _y, const short party_status, const int partysize, const string exit_) {
	int y = _y + 10;
	if (party_status != -1) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(++y, 1, show_squad_liberal_status);
	if (partysize > 0 && (party_status == -1 || partysize > 1))
		set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(y++, 40, HASH_CHECK_STATUS_OF_LIBERAL);
	if (partysize >= 2) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(y, 1, CONST_B_CHOOSE_A_BUYER);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(y, 40, CONST_ENTER);
	addstrAlt(exit_);
}
void printOptionsMiddle(const int _y, const bool sell_masks_, const bool left_side, const bool allow_selling_, const int loot) {
	int y = 10 + _y;
	if (sell_masks_)
	{
		mvaddstrAlt(y, left_side ? 1 : 40, CONST_M_BUY_A_MASK_15);
	}
	if (!left_side) y++;
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(y++, 1, CONST_E_LOOK_OVER_EQUIPMENT);
	if (allow_selling_)
	{
		if (loot >= 1) {
			set_color_easy(WHITE_ON_BLACK);
		}
		else { set_color_easy(BLACK_ON_BLACK_BRIGHT); }
		mvaddstrAlt(y++, 1, CONST_S_SELL_SOMETHING);
	}
}

void printMaskOptions(const int page, const string bname, const vector<int> masktype, const vector<string> mname, const vector<string> mdescription) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_WHICH_MASK_WILL);
	addstrAlt(bname);
	addstrAlt(CONST_BUY);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(1, 0, CONST_PRODUCT_NAME_HEADER);
	for (int p = page * 19, y = 2; p < len(masktype) && p < page * 19 + 19; p++, y++)
	{
		set_color_easy(WHITE_ON_BLACK);

		mvaddcharAlt(y, 0, y + 'A' - 2);
		addstrAlt(spaceDashSpace);
		addstrAlt(mname[p]);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(y, 39, mdescription[p]);
	}
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_SELECT_A_MASK);
	mvaddstrAlt(23, 0, addpagestr());
	mvaddstrAlt(24, 0, CONST_Z_SURPRISE);
	addstrAlt(bname);
	addstrAlt(CONST_WITH_A_RANDOM_MASK);

}
void printFenceAmount(const int fenceamount) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_YOU_ADD);
	addstrAlt(fenceamount);
	addstrAlt(CONST_TO_LIBERAL_FUNDS);
}
void printChooseALiberalTo() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 20, CHOOSE_A_LIBERAL_TO + CONST_SPEND);
}

void printReallySellAllThese(const char c) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	switch (c)
	{
	case 'w': mvaddstrAlt(18, 1, CONST_REALLY_SELL_ALL_WEAPONS_Y_ES_TO_CONFIRM); break;
	case 'a': mvaddstrAlt(18, 1, CONST_REALLY_SELL_ALL_AMMO_Y_ES_TO_CONFIRM); break;
	case 'c': mvaddstrAlt(18, 1, CONST_REALLY_SELL_ALL_CLOTHES_Y_ES_TO_CONFIRM); break;
	}
}
void printSellLootHeader(const int loot, const int partysize, const short party_status) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(10, 1, CONST_E_LOOK_OVER_EQUIPMENT);
	mvaddstrAlt(10, 1, CONST_E_LOOK_OVER_EQUIPMENT);
	if (loot > 0) {
		set_color_easy(WHITE_ON_BLACK);
	}
	else { set_color_easy(BLACK_ON_BLACK_BRIGHT); }
	mvaddstrAlt(10, 40, CONST_F_PAWN_SELECTIVELY);
	mvaddstrAlt(11, 1, CONST_W_PAWN_ALL_WEAPONS);
	mvaddstrAlt(11, 40, CONST_A_PAWN_ALL_AMMUNITION);
	mvaddstrAlt(12, 1, CONST_C_PAWN_ALL_CLOTHES);
	mvaddstrAlt(12, 40, CONST_L_PAWN_ALL_LOOT);
	if (party_status != -1)
		set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(15, 1, show_squad_liberal_status);
	if (partysize && (party_status == -1 || partysize > 1))
		set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(15, 40, HASH_CHECK_STATUS_OF_LIBERAL);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(16, 40, CONST_ENTER_DONE_PAWNING);
}
void printCantSellDamage() {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 15, CONST_YOU_CAN_T_SELL_DAMAGED_GOODS);
}
void printSellingFooter() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 1, CONST_PRESS_A_LETTER_TO_SELECT_AN_ITEM_TO_SELL);
	mvaddstrAlt(24, 1, enter_done);
}
void printPageOptions(const bool prev, const bool next) {

	set_color_easy(WHITE_ON_BLACK);
	if (prev)
	{
		mvaddstrAlt(17, 1, addprevpagestr());
	}
	//PAGE DOWN
	if (next)
	{
		mvaddstrAlt(17, 53, addnextpagestr());
	}
}

void printLootForSale(const int i, const int selectedl, const int lootNumber, const string lootTitle) {

	int x = 1 + (i % 3) * 26;
	int y = 10 + i / 3;

	if (selectedl)
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	string itemstr = lootTitle;
	if (lootNumber > 1)
	{
		if (selectedl)
			itemstr += singleSpace + tostring(selectedl) + CONST_SLASH;
		else itemstr += CONST_LC_X;
		itemstr += tostring(lootNumber);
	}
	string outstr;
	outstr = static_cast<char>(i + 'A');
	outstr += spaceDashSpace + itemstr;
	mvaddstrAlt(y, x, outstr);
}
void printFenceHeader(const int ret) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, CONST_WHAT_WILL_YOU_SELL);
	if (ret)
	{
		mvaddstrAlt(0, 30, CONST_ESTIMATED_LIBERAL_AMOUNT);
		addstrAlt(ret);
	}
}
void printFullscreenFooter(const string bname, const string exit_) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_SELECT_AN_OPTION); //allow customize option? -XML
	mvaddstrAlt(23, 0, addpagestr());
	mvaddstrAlt(24, 0, CONST_ENTER + bname + singleSpace + exit_);
}
void printFullscreenHeader(const string bname) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, CONST_WHAT_WILL);
	addstrAlt(bname);
	addstrAlt(CONST_BUY);
	mvaddstrAlt(1, 0, CONST_PRODUCT_NAME_PRICE_HEADER);
}
void printFullscreenOption(const int p, const string dname) {

	mvaddcharAlt(p + 2, 0, 'A' + p);
	addstrAlt(spaceDashSpace);
	addstrAlt(dname);
}





// END SHOP


void printchaseencounter();
bool isThereGroundLoot();
extern coordinatest loc_coord;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
vector<NameAndAlignment> getEncounterNameAndAlignment();
enum wallDirection {
	WALL_UP = 0,
	WALL_DOWN = 1,
	WALL_LEFT = 2,
	WALL_RIGHT = 3,
	CORNER_UL = 4,
	CORNER_UR = 5,
	CORNER_DL = 6,
	CORNER_DR = 7
};
extern coordinatest loc_coord;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];

extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
map<SpecialBlocks, string> specialString = {
	map<SpecialBlocks, string>::value_type(SPECIAL_LAB_COSMETICS_CAGEDANIMALS, CONST_CAGED_ANIMALS),
	map<SpecialBlocks, string>::value_type(SPECIAL_NUCLEAR_ONOFF, CONST_REACTOR_CONTROL_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_LAB_GENETIC_CAGEDANIMALS, CONST_CAGED_QUOTE_ANIMALS_ENDQUOTE),
	map<SpecialBlocks, string>::value_type(SPECIAL_POLICESTATION_LOCKUP, CONST_POLICE_DETENTION_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_COURTHOUSE_LOCKUP, CONST_COURTHOUSE_JAIL),
	map<SpecialBlocks, string>::value_type(SPECIAL_COURTHOUSE_JURYROOM, CONST_JURY_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_PRISON_CONTROL, CONST_CC_PRISON_CONTROL_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_PRISON_CONTROL_LOW, CONST_CC_PRISON_CONTROL_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_PRISON_CONTROL_MEDIUM, CONST_CC_PRISON_CONTROL_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_PRISON_CONTROL_HIGH, CONST_CC_PRISON_CONTROL_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_INTEL_SUPERCOMPUTER, CONST_SUPERCOMPUTER),
	map<SpecialBlocks, string>::value_type(SPECIAL_SWEATSHOP_EQUIPMENT, CONST_TEXTILE_EQUIPMENT),
	map<SpecialBlocks, string>::value_type(SPECIAL_POLLUTER_EQUIPMENT, CONST_FACTORY_EQUIPMENT),
	map<SpecialBlocks, string>::value_type(SPECIAL_ARMORY, CONST_ARMORY),
	map<SpecialBlocks, string>::value_type(SPECIAL_HOUSE_CEO, CONST_CEO_S_STUDY),
	map<SpecialBlocks, string>::value_type(SPECIAL_HOUSE_PHOTOS, CONST_SAFE),
	map<SpecialBlocks, string>::value_type(SPECIAL_CORPORATE_FILES, CONST_SAFE),
	map<SpecialBlocks, string>::value_type(SPECIAL_RADIO_BROADCASTSTUDIO, CONST_RADIO_BROADCAST_ROOM),
	map<SpecialBlocks, string>::value_type(SPECIAL_NEWS_BROADCASTSTUDIO, CONST_NEWS_BROADCAST_STUDIO),
	map<SpecialBlocks, string>::value_type(SPECIAL_APARTMENT_LANDLORD, CONST_LANDLORD_S_OFFICE),
	map<SpecialBlocks, string>::value_type(SPECIAL_SIGN_ONE, CONST_SIGN),
	map<SpecialBlocks, string>::value_type(SPECIAL_SIGN_TWO, CONST_SIGN),
	map<SpecialBlocks, string>::value_type(SPECIAL_SIGN_THREE, CONST_SIGN),
	map<SpecialBlocks, string>::value_type(SPECIAL_DISPLAY_CASE, CONST_DISPLAY_CASE),
	map<SpecialBlocks, string>::value_type(SPECIAL_STAIRS_UP, CONST_STAIRS_UP),
	map<SpecialBlocks, string>::value_type(SPECIAL_STAIRS_DOWN, CONST_STAIRS_DOWN),
	map<SpecialBlocks, string>::value_type(SPECIAL_RESTAURANT_TABLE, CONST_TABLE),
	map<SpecialBlocks, string>::value_type(SPECIAL_CAFE_COMPUTER, CONST_COMPUTER),
	map<SpecialBlocks, string>::value_type(SPECIAL_PARK_BENCH, CONST_BENCH),
	map<SpecialBlocks, string>::value_type(SPECIAL_BANK_VAULT, CONST_BANK_VAULT),
	map<SpecialBlocks, string>::value_type(SPECIAL_BANK_TELLER, CONST_BANK_TELLER),
	map<SpecialBlocks, string>::value_type(SPECIAL_BANK_MONEY, CONST_OH_WOW_SO_MUCH_MONEY),
	map<SpecialBlocks, string>::value_type(SPECIAL_CCS_BOSS, CONST_CCS_BOSS),
	map<SpecialBlocks, string>::value_type(SPECIAL_OVAL_OFFICE_NW, CONST_THE_OFFICE_OF_THE_PRESIDENT),
	map<SpecialBlocks, string>::value_type(SPECIAL_OVAL_OFFICE_NE, CONST_THE_OFFICE_OF_THE_PRESIDENT),
	map<SpecialBlocks, string>::value_type(SPECIAL_OVAL_OFFICE_SW, CONST_THE_OFFICE_OF_THE_PRESIDENT),
	map<SpecialBlocks, string>::value_type(SPECIAL_OVAL_OFFICE_SE, CONST_THE_OFFICE_OF_THE_PRESIDENT),
};
int encounterSize();
int squadAlive();
extern bool mapshowing;
extern coordinatest loc_coord;
extern siteblockst levelmap[MAPX][MAPY][MAPZ];
extern bool mapshowing;
extern short mode;
extern coordinatest loc_coord;
int monthday();
const char *_difficulty[] = { "Simple", "Very Easy", "Easy", "Below Average", "Average", "Above Average", "Hard", "Very Hard", "Extremely Difficult", "Nearly Impossible", "Impossible" };
//	extern string COMMA_SPACE;
extern int day;
extern int month;
extern int year;
extern unsigned char newstops[6][80][5][4];
extern unsigned char bigletters[27][5][7][4];
extern unsigned char newspic[20][78][18][4];
#define CH_BOX_DRAWINGS_LIGHT_VERTICAL 0xb3
#define CH_UPPER_HALF_BLOCK 0xdf
#define CH_LOWER_HALF_BLOCK 0xdc
#define CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZONTAL 0xc5
#define CH_FULL_BLOCK 0xdb
#define CH_LIGHT_SHADE 0xb0
#define CH_MEDIUM_SHADE 0xb1
#define CH_DARK_SHADE 0xb2

std::pair<ColorSetup, int> ConfederateFlag[7][17] = {
{
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK)
},
{
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1de),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1dd),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK)
},
{
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1de),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1dd),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK)
},
{
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1de),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x1dd),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x1de),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1dd),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK)
},
{
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1de),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1dd),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK)
},
{
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1de),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, 0x1dd),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK)
},
{
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(RED_ON_RED, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_UPPER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_WHITE_BRIGHT, CH_FULL_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, 0x12a),
std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_UPPER_HALF_BLOCK)
}
};

std::pair<ColorSetup, int> AmericanFlag[7][18] = {
	{
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, '.'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, '.'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, '.'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, '.'),
		std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
		std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	},
{
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
},
{
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, ':'),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
},
{
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_BLUE_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
},
{
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
},
{
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
	std::pair<ColorSetup, int>(WHITE_ON_RED_BRIGHT, CH_LOWER_HALF_BLOCK),
},
{
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
	std::pair<ColorSetup, int>(RED_ON_BLACK, CH_UPPER_HALF_BLOCK),
},
};
extern bool fixcleartype;
extern class Ledger ledger;
//
// SIEGE

const string siege = "siege\\";

const string CONST_ENGAGECONSERVATIVESESCAPE_TXT = "engageConservativesEscape.txt";
const string CONST_ENGAGECONSERVATIVES_TXT = "engageConservatives.txt";
const string CONST_NEXTSIEGEAGAIN_TXT = "nextSiegeAgain.txt";
const string CONST_NEXTSIEGE_TXT = "nextSiege.txt";
const string CONST_WORD_REPLACING_LIBERAL_TXT = "word_replacing_liberal.txt";
const string CONST_INSULT_FOR_LIBERAL_TXT = "insult_for_liberal.txt";
const string CONST_NEWSPAPER_LAST_NAME_TXT = "newspaper_last_name.txt";
const string CONST_NEWSPAPER_FIRST_NAME_TXT = "newspaper_first_name.txt";
const string CONST_WORDS_MEANING_NEWS_TXT = "words_meaning_news.txt";
const string CONST_THE_PRINTING_PRESS_IS_DISMANTLED_AND_BURNED = "The printing press is dismantled and burned.";
//const string CONST_EXCLAMATION_POINT = "!";
const string CONST_AN_UNOCCUPIED_SAFEHOUSE = ", an unoccupied safehouse.";
const string CONST_HAS_BEEN_RESCUED = " has been rescued.";
const string CONST_S_CORPSE_HAS_BEEN_RECOVERED = "'s corpse has been recovered.";
const string CONST_SURRENDER_YOURSELVES = "Surrender yourselves!";
const string CONST_MATERIALS_RELATING_TO_THE_BUSINESS_FRONT_HAVE_BEEN_TAKEN = "Materials relating to the business front have been taken.";
const string CONST_THE_COMPOUND_IS_DISMANTLED = "The compound is dismantled.";
const string CONST_LAW_ENFORCEMENT_HAS_CONFISCATED = "Law enforcement has confiscated $";
const string CONST_IN_LCS_FUNDS = " in LCS funds.";
const string CONST_FORTUNATELY_YOUR_FUNDS_REMAIN_INTACT = "Fortunately, your funds remain intact.";
const string CONST_LIBERALS_ARE_TAKEN_TO_THE_POLICE_STATION = " Liberals are taken to the police station.";
const string CONST_IS_TAKEN_TO_THE_POLICE_STATION = "is taken to the police station.";
const string CONST_X_SINGLE_COMMA = ",";
const string CONST_AKA = ", aka ";
const string CONST_THE_KIDNAP_VICTIMS_ARE_REHABILITATED_AND_FREED = "The kidnap victims are rehabilitated and freed.";
const string CONST_IS_REHABILITATED_AND_FREED = " is rehabilitated and freed.";
const string CONST_CONFISCATE_EVERYTHING_INCLUDING_SQUAD_WEAPONS = " confiscate everything, including Squad weapons.";
const string CONST_THE_FIREMEN = "The firemen";
const string CONST_THE_SOLDIERS = "The soldiers";
const string CONST_THE_POLICE = "The police";
const string CONST_IS_SLAIN = " is slain.";
const string CONST_EVERYONE_IN_THE = "Everyone in the ";
const string CONST_YOU_ARE_WANTED_FOR_HARBORING_A_FUGITIVE_FROM_JUSTICE = "You are wanted for harboring a fugitive from justice";
const string CONST_YOU_ARE_WANTED_FOR_LOITERING = "You are wanted for loitering";
const string CONST_YOU_ARE_WANTED_FOR_INDECENT_EXPOSURE = "You are wanted for indecent exposure";
const string CONST_YOU_ARE_WANTED_FOR_DISTURBING_THE_PEACE = "You are wanted for disturbing the peace";
const string CONST_YOU_ARE_WANTED_FOR_RESISTING_ARREST = "You are wanted for resisting arrest";
const string CONST_YOU_ARE_WANTED_FOR_VANDALISM = "You are wanted for vandalism";
const string CONST_YOU_ARE_WANTED_FOR_BREAKING_AND_ENTERING = "You are wanted for breaking and entering";
const string CONST_YOU_ARE_WANTED_FOR_UNLAWFUL_BURIAL = "You are wanted for unlawful burial";
const string CONST_YOU_ARE_WANTED_FOR_UNLAWFUL_ACCESS_OF_AN_INFORMATION_SYSTEM = "You are wanted for unlawful access of an information system";
const string CONST_YOU_ARE_WANTED_FOR_INTERFERENCE_WITH_INTERSTATE_COMMERCE = "You are wanted for interference with interstate commerce";
const string CONST_YOU_ARE_WANTED_FOR_PROSTITUTION = "You are wanted for prostitution";
const string CONST_YOU_ARE_WANTED_FOR_PETTY_LARCENY = "You are wanted for petty larceny";
const string CONST_YOU_ARE_WANTED_FOR_CREDIT_CARD_FRAUD = "You are wanted for credit card fraud";
const string CONST_YOU_ARE_WANTED_FOR_GRAND_THEFT_AUTO = "You are wanted for grand theft auto";
const string CONST_YOU_ARE_WANTED_FOR_MISDEMEANOR_ASSAULT = "You are wanted for misdemeanor assault";
const string CONST_YOU_ARE_WANTED_FOR_ASSAULT_WITH_A_DEADLY_WEAPON = "You are wanted for assault with a deadly weapon";
const string CONST_YOU_ARE_WANTED_FOR_EXTORTION = "You are wanted for extortion";
const string CONST_YOU_ARE_WANTED_FOR_RACKETEERING = "You are wanted for racketeering";
const string CONST_YOU_ARE_WANTED_FOR_JURY_TAMPERING = "You are wanted for jury tampering";
const string CONST_YOU_ARE_WANTED_FOR_AIDING_A_PRISON_ESCAPE = "You are wanted for aiding a prison escape";
const string CONST_YOU_ARE_WANTED_FOR_ESCAPING_PRISON = "You are wanted for escaping prison";
const string CONST_YOU_ARE_WANTED_FOR_SALE_AND_DISTRIBUTION_OF_A_CONTROLLED_SUBSTANCE = "You are wanted for sale and distribution of a controlled substance";
const string CONST_YOU_ARE_WANTED_FOR_SEDITION = "You are wanted for sedition";
const string CONST_YOU_ARE_WANTED_FOR_ARSON = "You are wanted for arson";
const string CONST_YOU_ARE_WANTED_FOR_BANK_ROBBERY = "You are wanted for bank robbery";
const string CONST_YOU_ARE_WANTED_FOR_KIDNAPPING = "You are wanted for kidnapping";
const string CONST_YOU_ARE_WANTED_FOR_FIRST_DEGREE_MURDER = "You are wanted for first degree murder";
const string CONST_YOU_ARE_WANTED_FOR_TERRORISM = "You are wanted for terrorism";
const string CONST_YOU_ARE_WANTED_FOR_TREASON = "You are wanted for treason";
const string CONST_AND_OTHER_CRIMES = " and other crimes";
const string CONST_YOU_ARE_WANTED_FOR_HIRING_AN_ILLEGAL_ALIEN = "You are wanted for hiring an illegal alien";
const string CONST_YOU_ARE_WANTED_FOR_FLAG_BURNING = "You are wanted for flag burning";
const string CONST_YOU_ARE_WANTED_FOR_FELONY_FLAG_BURNING = "You are wanted for felony flag burning";
const string CONST_YOU_ARE_WANTED_FOR_FLAG_MURDER = "You are wanted for Flag Murder";
const string CONST_UNHARMED = " unharmed!";
const string CONST_AND_THE_OTHERS = " and the others";
const string CONST_RELEASE = "Release ";
const string CONST_IN_THE_NAME_OF_GOD_YOUR_CAMPAIGN_OF_TERROR_ENDS_HERE = "In the name of God, your campaign of terror ends here!";
const string CONST_YOU_HEAR_A_BLARING_VOICE_ON_A_LOUDSPEAKER = "You hear a blaring voice on a loudspeaker:";
const string CONST_YOU_HEAR_SHOUTS = "You hear shouts:";
const string CONST_YOU_ARE_WANTED_FOR_HIRING_AN_UNDOCUMENTED_WORKER = "You are wanted for hiring an undocumented worker";
const string CONST_UC_HIRING_UNDOCUMENTED_WORKERS = "HIRING UNDOCUMENTED WORKERS";
const string CONST_UC_FLAG_BURNING = "FLAG BURNING";
const string CONST_UC_LOITERING = "LOITERING";
const string CONST_UC_PUBLIC_NUDITY = "PUBLIC NUDITY";
const string CONST_UC_DISTURBING_THE_PEACE = "DISTURBING THE PEACE";
const string CONST_UC_RESISTING_ARREST = "RESISTING ARREST";
const string CONST_UC_VANDALISM = "VANDALISM";
const string CONST_UC_BREAKING_AND_ENTERING = "BREAKING AND ENTERING";
const string CONST_UC_UNLAWFUL_BURIAL = "UNLAWFUL BURIAL";
const string CONST_UC_HACKING = "HACKING";
const string CONST_UC_ELECTRONIC_SABOTAGE = "ELECTRONIC SABOTAGE";
const string CONST_UC_HIRING_ILLEGAL_ALIENS = "HIRING ILLEGAL ALIENS";
const string CONST_UC_PROSTITUTION = "PROSTITUTION";
const string CONST_UC_THEFT = "THEFT";
const string CONST_UC_CREDIT_CARD_FRAUD = "CREDIT CARD FRAUD";
const string CONST_UC_GRAND_THEFT_AUTO = "GRAND THEFT AUTO";
const string CONST_UC_ASSAULT = "ASSAULT";
const string CONST_UC_ARMED_ASSAULT = "ARMED ASSAULT";
const string CONST_UC_EXTORTION = "EXTORTION";
const string CONST_UC_RACKETEERING = "RACKETEERING";
const string CONST_UC_JURY_TAMPERING = "JURY TAMPERING";
const string CONST_UC_RELEASING_PRISONERS = "RELEASING PRISONERS";
const string CONST_UC_ESCAPING_PRISON = "ESCAPING PRISON";
const string CONST_UC_DRUG_DEALING = "DRUG DEALING";
const string CONST_UC_HARMFUL_SPEECH = "HARMFUL SPEECH";
const string CONST_UC_FLAG_MURDER = "FLAG MURDER";
const string CONST_UC_ARSON = "ARSON";
const string CONST_UC_BANK_ROBBERY = "BANK ROBBERY";
const string CONST_UC_KIDNAPPING = "KIDNAPPING";
const string CONST_UC_MURDER = "MURDER";
const string CONST_UC_TERRORISM = "TERRORISM";
const string CONST_UC_TREASON = "TREASON";
const string CONST_REHABILITATION = "REHABILITATION";
const string CONST_WANTED_FOR = "WANTED FOR ";
const string CONST_PRESS_ESC_TO_PONDER_THE_SITUATION = "Press Esc to ponder the situation...";
const string CONST_ATTACK_WILL_BE_CARRIED_OUT_BY_SEAL_TEAM_6 = "attack will be carried out by SEAL Team 6.";
const string CONST_PLANES_WILL_BOMB_THE_COMPOUND_DURING_THE_SIEGE_AND_THE_FINAL = "Planes will bomb the compound during the siege, and the final ";
const string CONST_A_TANK_WILL_COVER_THE_ENTRANCE_TO_THE_COMPOUND = "A tank will cover the entrance to the compound.";
const string CONST_THE_FIGHTING_FORCE_WILL_BE_COMPOSED_OF_NATIONAL_GUARD_TROOPS = "The fighting force will be composed of national guard troops.";
const string CONST_AN_IMMINENT_POLICE_RAID_ON = "an imminent police raid on ";
const string CONST_YOU_HAVE_RECEIVED_ADVANCE_WARNING_FROM_YOUR_SLEEPERS_REGARDING = "You have received advance warning from your sleepers regarding ";

const string CONST_THE_COPS_HAVE_RAIDED_THE = "The cops have raided the ";
const string CONST_YOU_HEAR_JET_BOMBERS_STREAK_OVERHEAD = "You hear jet bombers streak overhead.";
const string CONST_AN_M1_ABRAMS_TANK_TAKES_UP_POSITION_OUTSIDE_THE_COMPOUND = "An M1 Abrams Tank takes up position outside the compound.";
const string CONST_AN_M1_ABRAMS_TANK_IS_STOPPED_BY_THE_TANK_TRAPS = "An M1 Abrams Tank is stopped by the tank traps.";
const string CONST_NATIONAL_GUARD_TROOPS_ARE_REPLACING_NORMAL_SWAT_UNITS = "National Guard troops are replacing normal SWAT units.";
const string CONST_THE_POLICE_HAVE_SURROUNDED_THE = "The police have surrounded the ";
const string CONST_LC_THE_LCS = "the LCS";
const string CONST_ARE_HIRING_MERCENARIES_TO_ATTACK = "are hiring mercenaries to attack ";
const string CONST_THAT_THE_CORPORATIONS = " that the Corporations ";
const string CONST_AN_ANONYMOUS_TIP = "an anonymous tip";
const string CONST_YOUR_SLEEPER_CEO_S_WARNING = "your sleeper CEO's warning";
const string CONST_YOU_HAVE_RECEIVED = "You have received ";
const string CONST_CORPORATE_MERCENARIES_ARE_RAIDING_THE = "Corporate mercenaries are raiding the ";
const string CONST_CCS_MEMBERS_POUR_OUT_OF_THE_TRUCK_AND_SHOOT_IN_THE_FRONT_DOORS = "CCS members pour out of the truck and shoot in the front doors!";
const string CONST_INJURED = "INJURED: ";
const string CONST_UC_KILLED = "KILLED: ";
const string CONST_CCS_CAR_BOMBING_CASUALTY_REPORT = "CCS CAR BOMBING CASUALTY REPORT";
const string CONST_THE_TRUCK_PLOWS_INTO_THE_BUILDING_AND_EXPLODES = "The truck plows into the building and explodes!";
const string CONST_A_SCREECHING_TRUCK_PULLS_UP_TO = "A screeching truck pulls up to ";
const string CONST_IS_GEARING_UP_TO_ATTACK = " is gearing up to attack ";
const string CONST_YOU_HAVE_RECEIVED_A_SLEEPER_WARNING_THAT_THE_CCS = "You have received a sleeper warning that the CCS ";
const string CONST_COME_QUIETLY_AND_YOU_WILL_NOT_BE_HARMED = "Come quietly and you will not be harmed.";
const string CONST_UNACCEPTABLE_SPEECH_HAS_OCCURRED_AT_THIS_LOCATION = "Unacceptable Speech has occurred at this location.";
const string CONST_YOU_HEAR_A_SCREECHING_VOICE_OVER_THE_SOUND_OF_FIRE_ENGINE_SIRENS = "You hear a screeching voice over the sound of fire engine sirens:";
const string CONST_ARMORED_FIREMEN_SWARM_OUT_PILOT_LIGHTS_BURNING = "Armored firemen swarm out, pilot lights burning.";
const string CONST_SCREAMING_FIRE_ENGINES_PULL_UP_TO_THE = "Screaming fire engines pull up to the ";

const string CONST_MATERIALS_RELATING_TO_THE_BUSINESS_FRONT_HAVE_BEEN_DESTROYED = "Materials relating to the business front have been destroyed.";
const string CONST_THE_FIREMEN_HAVE_RAIDED_THE = "The Firemen have raided the ";
const string CONST_TO_LAUNCH_AN_ATTACK_ON = "to launch an attack on ";
const string CONST_A_SLEEPER_AGENT_HAS_REPORTED_THAT_THE_CIA_IS_PLANNING = "A sleeper agent has reported that the CIA is planning ";
const string CONST_THEY_VE_SHUT_OFF_THE_LIGHTS = "They've shut off the lights!";
const string CONST_TO_SHUT_OFF_THE_LIGHTS = "to shut off the lights!";
const string CONST_THROUGH_SOME_FORM_OF_HIGH_TECHNOLOGY_THEY_VE_MANAGED = "Through some form of high technology, they've managed ";
const string CONST_TO_SHUT_OFF_THE_LIGHTS_AND_THE_CAMERAS = "to shut off the lights and the cameras!";

const string CONST_UNMARKED_BLACK_VANS_ARE_SURROUNDING_THE = "Unmarked black vans are surrounding the ";
const string CONST_ARE_STORMING_THE = "are storming the ";
const string CONST_MASSES_DISSATISFIED_WITH_YOUR_LACK_OF_RESPECT_FOR_AM_RADIO = "Masses dissatisfied with your lack of respect for AM Radio ";
//	const string CONST_ARE_STORMING_THE = "are storming the ";
const string CONST_MASSES_DISSATISFIED_WITH_YOUR_LACK_OF_RESPECT_FOR_CABLE_NEWS = "Masses dissatisfied with your lack of respect for Cable News ";
const string CONST_THE_FIREMEN_ARE_PLANNING_TO_BURN = "the Firemen are planning to burn ";
const string CONST_WORD_IN_THE_UNDERGROUND_IS_THAT = "Word in the underground is that ";
const string CONST_A_SLEEPER_FIREMAN_HAS_INFORMED_YOU_THAT = "A sleeper Fireman has informed you that ";
const string CONST_CONSERVATIVES_HAVE_RAIDED_THE = "Conservatives have raided the ";
const string CONST_FORTUNATELY_NO_ONE_IS_HURT = "Fortunately, no one is hurt.";
const string CONST_NARROWLY_AVOIDED_DEATH = " narrowly avoided death!";
const string CONST_WAS_KILLED_IN_THE_BOMBING = " was killed in the bombing!";
const string CONST_THE_LIGHTS_FADE_AND_ALL_IS_DARK = "The lights fade and all is dark.";
const string CONST_THE_GENERATOR_HAS_BEEN_DESTROYED = "The generator has been destroyed!";
const string CONST_THERE_S_NOTHING_LEFT_BUT_SMOKING_WRECKAGE = "There's nothing left but smoking wreckage...";
const string CONST_THE_ANTI_AIRCRAFT_GUN_TAKES_A_DIRECT_HIT = "The anti-aircraft gun takes a direct hit!";
const string CONST_EXPLOSIONS_ROCK_THE_COMPOUND = "Explosions rock the compound!";
const string CONST_A_SKILLED_PILOT_GETS_THROUGH = "A skilled pilot gets through!";
const string CONST_IT_S_ALL_OVER_THE_TV_EVERYONE_IN_THE_LIBERAL_CRIME_SQUAD_GAINS_20_JUICE = "It's all over the TV. Everyone in the Liberal Crime Squad gains 20 juice!";
const string CONST_HIT_ONE_OF_THE_BOMBERS_SLAMS_INTO_TO_THE_GROUND = "Hit! One of the bombers slams into to the ground.";
const string CONST_YOU_DIDN_T_SHOOT_ANY_DOWN_BUT_YOU_VE_MADE_THEM_THINK_TWICE = "You didn't shoot any down, but you've made them think twice!";
const string CONST_THE_THUNDER_OF_THE_ANTI_AIRCRAFT_GUN_SHAKES_THE_COMPOUND = "The thunder of the anti-aircraft gun shakes the compound!";
const string CONST_YOU_HEAR_PLANES_STREAK_OVERHEAD = "You hear planes streak overhead!";
const string CONST_A_SNIPER_NEARLY_HITS = "A sniper nearly hits ";
const string CONST_A_SNIPER_TAKES_OUT = "A sniper takes out ";
const string CONST_S_WORDS = "'s words.";
const string CONST_VIRTUALLY_EVERYONE_IN_AMERICA_WAS_MOVED_BY = "Virtually everyone in America was moved by ";
const string CONST_LATER_WENT_ON_TO_WIN_A_PULITZER_FOR_IT = " later went on to win a Pulitzer for it.";
const string CONST_EVEN_THE_CABLE_NEWS_AND_AM_RADIO_SPEND_DAYS_TALKING_ABOUT_IT = "Even the Cable News and AM Radio spend days talking about it.";
const string CONST_THE_DISCUSSION_WAS_EXCITING_AND_DYNAMIC = "The discussion was exciting and dynamic.";
const string CONST_REPRESENTS_THE_LCS_WELL = " represents the LCS well.";
const string CONST_S_VERBAL_FINESSE_LEAVES_SOMETHING_TO_BE_DESIRED = "'s verbal finesse leaves something to be desired.";
const string CONST_STUTTERS_NERVOUSLY_THE_WHOLE_TIME = " stutters nervously the whole time.";
const string CONST_C_BUT_SPACE = "But ";
const string CONST_FALLS_ASLEEP = " falls asleep.";
const string CONST_BUT_THE_INTERVIEW_IS_SO_BORING_THAT = "But the interview is so boring that ";
const string CONST_RETARDED = "Retarded";
const string CONST_DUMB = "Dumb";
const string CONST_AND_LATER_USED_THE_MATERIAL_FOR_A_BROADWAY_PLAY_CALLED = "and later used the material for a Broadway play called";
const string CONST_CANCELED_THE_INTERVIEW_HALFWAY_THROUGH = " canceled the interview halfway through";
const string CONST_GOT_INTO_THE_COMPOUND_SOMEHOW = "got into the compound somehow!";
const string CONST_FROM_THE = " from the ";
const string CONST_ELITIST = "Elitist ";
const string CONST_THE_TANK_MOVES_FORWARD_TO_YOUR_COMPOUND_ENTRANCE = "The tank moves forward to your compound entrance.";
const string CONST_ARMY_ENGINEERS_HAVE_REMOVED_YOUR_TANK_TRAPS = "Army engineers have removed your tank traps.";
const string CONST_THE_POLICE_HAVE_CUT_THE_LIGHTS = "The police have cut the lights!";
const string CONST_THE_COPS_ARE_COMING = "The cops are coming!";
const string CONST_HAS_STARVED_TO_DEATH = " has starved to death.";
const string CONST_YOUR_LIBERALS_ARE_STARVING = "Your Liberals are starving!";
const string CONST_A_DAY_PASSES_WHILE_UNDER_SIEGE = "A day passes while under siege...";
const string CONST_YOUR_LIBERALS_SPLIT_UP_AND_LAY_LOW_FOR_A_FEW_DAYS = "Your Liberals split up and lay low for a few days.";
const string CONST_PRESS_ANY_KEY_TO_SPLIT_UP_AND_LAY_LOW_FOR_A_FEW_DAYS = "Press any key to split up and lay low for a few days";
const string CONST_YOU_HAVE_ESCAPED = "You have escaped!";
const string CONST_THE_SIEGE_IS_BROKEN = "The siege is broken!";
const string CONST_YOU_RE_FREE = "You're free!";
const string CONST_C_REFLECT_ON_YOUR_CONSERVATIVE_JUDGMENT = "C - Reflect on your Conservative judgment.";
const string CONST_G_SURRENDER = "G - Surrender";
const string CONST_F_FIGHT = "F - Fight!";
const string CONST_E_EQUIP = "E - Equip";
const string CONST_D_ESCAPE = "D - Escape";

const string CONST_PRESS_ANY_KEY_TO_CONFRONT_THE_CONSERVATIVE_AGGRESSORS = "Press any key to Confront the Conservative Aggressors";
const string CONST_YOUR_LIBERALS_SALLY_FORTH_TO_CONFRONT_THE_SIEGE = "Your Liberals sally forth to confront the siege.";
const string CONST_UNDER_SIEGE_ESCAPE_OR_ENGAGE = "UNDER SIEGE: ESCAPE OR ENGAGE";
vector<string> words_meaning_news;
vector<string> newspaper_first_name;
vector<string> newspaper_last_name;
vector<string> insult_for_liberal;
vector<string> word_replacing_liberal;
vector<string> engageConservativesEscape;
vector<string> engageConservatives;
vector<string> nextSiegeAgain;
vector<string> nextSiege;
vector<file_and_text_collection> siege_text_file_collection = {
	/*siege.cpp*/
	customText(&words_meaning_news, siege + CONST_WORDS_MEANING_NEWS_TXT),
	customText(&newspaper_first_name, siege + CONST_NEWSPAPER_FIRST_NAME_TXT),
	customText(&newspaper_last_name, siege + CONST_NEWSPAPER_LAST_NAME_TXT),
	customText(&insult_for_liberal, siege + CONST_INSULT_FOR_LIBERAL_TXT),
	customText(&word_replacing_liberal, siege + CONST_WORD_REPLACING_LIBERAL_TXT),
	customText(&nextSiege, MOSTLY_ENDINGS_FOLDER + CONST_NEXTSIEGE_TXT),
	customText(&nextSiegeAgain, MOSTLY_ENDINGS_FOLDER + CONST_NEXTSIEGEAGAIN_TXT),
	customText(&engageConservatives, MOSTLY_ENDINGS_FOLDER + CONST_ENGAGECONSERVATIVES_TXT),
	customText(&engageConservativesEscape, MOSTLY_ENDINGS_FOLDER + CONST_ENGAGECONSERVATIVESESCAPE_TXT),
};

map<Lawflags, string> youAreWantedForThis = {

	//TREASON
	map<Lawflags, string>::value_type(LAWFLAG_TREASON, CONST_YOU_ARE_WANTED_FOR_TREASON),
	//TERRORISM
	map<Lawflags, string>::value_type(LAWFLAG_TERRORISM, CONST_YOU_ARE_WANTED_FOR_TERRORISM),
	//MURDERER
	map<Lawflags, string>::value_type(LAWFLAG_MURDER, CONST_YOU_ARE_WANTED_FOR_FIRST_DEGREE_MURDER),
	//KIDNAPPER
	map<Lawflags, string>::value_type(LAWFLAG_KIDNAPPING, CONST_YOU_ARE_WANTED_FOR_KIDNAPPING),
	//BANK ROBBER
	map<Lawflags, string>::value_type(LAWFLAG_BANKROBBERY, CONST_YOU_ARE_WANTED_FOR_BANK_ROBBERY),
	//ARSONIST
	map<Lawflags, string>::value_type(LAWFLAG_ARSON, CONST_YOU_ARE_WANTED_FOR_ARSON),
	//SPEECH
	map<Lawflags, string>::value_type(LAWFLAG_SPEECH, CONST_YOU_ARE_WANTED_FOR_SEDITION),
	//BROWNIES
	map<Lawflags, string>::value_type(LAWFLAG_BROWNIES, CONST_YOU_ARE_WANTED_FOR_SALE_AND_DISTRIBUTION_OF_A_CONTROLLED_SUBSTANCE),
	//ESCAPED
	map<Lawflags, string>::value_type(LAWFLAG_ESCAPED, CONST_YOU_ARE_WANTED_FOR_ESCAPING_PRISON),
	//HELP ESCAPED
	map<Lawflags, string>::value_type(LAWFLAG_HELPESCAPE, CONST_YOU_ARE_WANTED_FOR_AIDING_A_PRISON_ESCAPE),
	//JURY
	map<Lawflags, string>::value_type(LAWFLAG_JURY, CONST_YOU_ARE_WANTED_FOR_JURY_TAMPERING),
	//RACKETEERING
	map<Lawflags, string>::value_type(LAWFLAG_RACKETEERING, CONST_YOU_ARE_WANTED_FOR_RACKETEERING),
	//EXTORTION
	map<Lawflags, string>::value_type(LAWFLAG_EXTORTION, CONST_YOU_ARE_WANTED_FOR_EXTORTION),
	//ASSAULT
	map<Lawflags, string>::value_type(LAWFLAG_ARMEDASSAULT, CONST_YOU_ARE_WANTED_FOR_ASSAULT_WITH_A_DEADLY_WEAPON),
	//ASSAULT
	map<Lawflags, string>::value_type(LAWFLAG_ASSAULT, CONST_YOU_ARE_WANTED_FOR_MISDEMEANOR_ASSAULT),
	//CAR THEFT
	map<Lawflags, string>::value_type(LAWFLAG_CARTHEFT, CONST_YOU_ARE_WANTED_FOR_GRAND_THEFT_AUTO),
	//CC FRAUD
	map<Lawflags, string>::value_type(LAWFLAG_CCFRAUD, CONST_YOU_ARE_WANTED_FOR_CREDIT_CARD_FRAUD),
	//THIEF
	map<Lawflags, string>::value_type(LAWFLAG_THEFT, CONST_YOU_ARE_WANTED_FOR_PETTY_LARCENY),
	//PROSTITUTION
	map<Lawflags, string>::value_type(LAWFLAG_PROSTITUTION, CONST_YOU_ARE_WANTED_FOR_PROSTITUTION),
	//COMMERCE
	map<Lawflags, string>::value_type(LAWFLAG_COMMERCE, CONST_YOU_ARE_WANTED_FOR_INTERFERENCE_WITH_INTERSTATE_COMMERCE),
	//INFORMATION
	map<Lawflags, string>::value_type(LAWFLAG_INFORMATION, CONST_YOU_ARE_WANTED_FOR_UNLAWFUL_ACCESS_OF_AN_INFORMATION_SYSTEM),
	//UNLAWFUL BURIAL
	map<Lawflags, string>::value_type(LAWFLAG_BURIAL, CONST_YOU_ARE_WANTED_FOR_UNLAWFUL_BURIAL),
	//BREAKING
	map<Lawflags, string>::value_type(LAWFLAG_BREAKING, CONST_YOU_ARE_WANTED_FOR_BREAKING_AND_ENTERING),
	//VANDALISM
	map<Lawflags, string>::value_type(LAWFLAG_VANDALISM, CONST_YOU_ARE_WANTED_FOR_VANDALISM),
	//RESIST
	map<Lawflags, string>::value_type(LAWFLAG_RESIST, CONST_YOU_ARE_WANTED_FOR_RESISTING_ARREST),
	//DISTURBANCE
	map<Lawflags, string>::value_type(LAWFLAG_DISTURBANCE, CONST_YOU_ARE_WANTED_FOR_DISTURBING_THE_PEACE),
	//PUBLIC NUDITY
	map<Lawflags, string>::value_type(LAWFLAG_PUBLICNUDITY, CONST_YOU_ARE_WANTED_FOR_INDECENT_EXPOSURE),
	//LOITERING
	map<Lawflags, string>::value_type(LAWFLAG_LOITERING, CONST_YOU_ARE_WANTED_FOR_LOITERING),
};
map<int, string> mostSeriousCrime = {

	map<int, string>::value_type(LAWFLAG_TREASON,
	CONST_UC_TREASON),
	//TERRORISM
	map<int, string>::value_type(LAWFLAG_TERRORISM,
	CONST_UC_TERRORISM),
	//MURDERER
	map<int, string>::value_type(LAWFLAG_MURDER,
	CONST_UC_MURDER),
	//KIDNAPPER
	map<int, string>::value_type(LAWFLAG_KIDNAPPING,
	CONST_UC_KIDNAPPING),
	//BANK ROBBER
	map<int, string>::value_type(LAWFLAG_BANKROBBERY,
	CONST_UC_BANK_ROBBERY),
	//ARSONIST
	map<int, string>::value_type(LAWFLAG_BANKROBBERY,
	CONST_UC_ARSON),
};
map<int, string> mostSeriousCrime2 = {
	//SPEECH
	map<int, string>::value_type(LAWFLAG_SPEECH,
	CONST_UC_HARMFUL_SPEECH),
	//BROWNIES
	map<int, string>::value_type(LAWFLAG_BROWNIES,
	CONST_UC_DRUG_DEALING),
	//ESCAPED
	map<int, string>::value_type(LAWFLAG_ESCAPED,
	CONST_UC_ESCAPING_PRISON),
	//HELP ESCAPED
	map<int, string>::value_type(LAWFLAG_HELPESCAPE,
	CONST_UC_RELEASING_PRISONERS),
	//JURY
	map<int, string>::value_type(LAWFLAG_JURY,
	CONST_UC_JURY_TAMPERING),
	//RACKETEERING
	map<int, string>::value_type(LAWFLAG_RACKETEERING,
	CONST_UC_RACKETEERING),
	//EXTORTION
	map<int, string>::value_type(LAWFLAG_EXTORTION,
	CONST_UC_EXTORTION),
	//ASSAULT
	map<int, string>::value_type(LAWFLAG_ARMEDASSAULT,
	CONST_UC_ARMED_ASSAULT),
	//ASSAULT
	map<int, string>::value_type(LAWFLAG_ASSAULT,
	CONST_UC_ASSAULT),
	//CAR THEFT
	map<int, string>::value_type(LAWFLAG_CARTHEFT,
	CONST_UC_GRAND_THEFT_AUTO),
	//CC FRAUD
	map<int, string>::value_type(LAWFLAG_CCFRAUD,
	CONST_UC_CREDIT_CARD_FRAUD),
	//THIEF
	map<int, string>::value_type(LAWFLAG_THEFT,
	CONST_UC_THEFT),
	//PROSTITUTION
	map<int, string>::value_type(LAWFLAG_PROSTITUTION,
	CONST_UC_PROSTITUTION)
};
map<int, string> mostSeriousCrime3 = {
	//COMMERCE
	map<int, string>::value_type(LAWFLAG_COMMERCE,
	CONST_UC_ELECTRONIC_SABOTAGE),
	//INFORMATION
	map<int, string>::value_type(LAWFLAG_INFORMATION,
	CONST_UC_HACKING),
	//UNLAWFUL BURIAL
	map<int, string>::value_type(LAWFLAG_BURIAL,
	CONST_UC_UNLAWFUL_BURIAL),
	//BREAKING
	map<int, string>::value_type(LAWFLAG_BREAKING,
	CONST_UC_BREAKING_AND_ENTERING),
	//VANDALISM
	map<int, string>::value_type(LAWFLAG_VANDALISM,
	CONST_UC_VANDALISM),
	//RESIST
	map<int, string>::value_type(LAWFLAG_RESIST,
	CONST_UC_RESISTING_ARREST),
	//DISTURBANCE
	map<int, string>::value_type(LAWFLAG_DISTURBANCE,
	CONST_UC_DISTURBING_THE_PEACE),
	//PUBLIC NUDITY
	map<int, string>::value_type(LAWFLAG_PUBLICNUDITY,
	CONST_UC_PUBLIC_NUDITY),
	//LOITERING
	map<int, string>::value_type(LAWFLAG_LOITERING,
	CONST_UC_LOITERING),
};

const string CONST_FIVE_STARS_VICTORY_FIVE_STARS = "* * * * *   VICTORY   * * * * *";
const string CONST_PRESS_C_TO_CONTINUE_LIBERALLY = "Press C to Continue Liberally.";
const string CONST_THIS_FILTH_UNTIL_THE_LIBERAL_AGENDA_IS_REALIZED = "this filth until the Liberal Agenda is realized.";
const string CONST_UNFORTUNATELY_YOU_WILL_NEVER_TRULY_BE_SAFE_FROM = "Unfortunately, you will never truly be safe from ";
const string CONST_THE_CONSERVATIVES_HAVE_BEEN_DRIVEN_BACK = "The Conservative automatons have been driven back.  ";
const string CONST_ABANDONING_THIS_SAFE_HOUSE_FOR_A_SAFER_LOCATION = "abandoning this safe house for a safer location.";
const string CONST_THE_TIME_BEING_WHILE_THEY_ARE_REGROUPING_YOU_MIGHT_CONSIDER = "the time being.  While they are regrouping, you might consider ";
const string CONST_THE_CONSERVATIVE_AUTOMATONS_HAVE_BEEN_DRIVEN_BACK = "The Conservative automatons have been driven back 컴 for ";
const string CONST_YOU_HAVE_BEEN_DEFEATED = "You have been defeated.";
const string CONST_YOUR_LIBERALS_CONFRONT_THE_CONSERVATIVES_WITHIN_THE_SAFEHOUSE = "Your Liberals confront the Conservatives within the safehouse.";
const string CONST_YOUR_TRAPS_WILL_HARASS_THE_ENEMY_BUT_NOT_THE_SQUAD = "Your traps will harass the enemy, but not the Squad.";
const string CONST_YOUR_SECURITY_CAMERAS_LET_YOU_SEE_UNITS_ON_THE_M_AP = "Your security cameras let you see units on the (M)ap.";
const string CONST_UNDER_ATTACK_ESCAPE_OR_ENGAGE = "UNDER ATTACK: ESCAPE OR ENGAGE";

void printReporterEnteredCompound(const string repname) {
	set_color_easy(WHITE_ON_BLACK);
	eraseAlt();
	mvaddstrAlt(1, 1, CONST_ELITIST, gamelog);
	addstrAlt(repname, gamelog);
	addstrAlt(CONST_FROM_THE, gamelog);
	addstrAlt(pickrandom(words_meaning_news), gamelog);
	addstrAlt(singleSpace);
	addstrAlt(pickrandom(newspaper_first_name), gamelog);
	addstrAlt(singleSpace, gamelog);
	addstrAlt(pickrandom(newspaper_last_name), gamelog);
	mvaddstrAlt(2, 1, CONST_GOT_INTO_THE_COMPOUND_SOMEHOW, gamelog);
	gamelog.newline();
}
void printThePoliceCutLights(const bool clearformess) {
	if (clearformess) eraseAlt();
	else makedelimiter();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_POLICE_HAVE_CUT_THE_LIGHTS, gamelog);
	gamelog.newline();
}

void printReporterDuringSiege(const string repname, const string name, const int segmentpower) {
	extern short lawList[LAWNUM];
	string line_one;
	string line_two = "";
	if (segmentpower < 15)
	{
		line_one = repname + CONST_CANCELED_THE_INTERVIEW_HALFWAY_THROUGH;
		line_two = CONST_AND_LATER_USED_THE_MATERIAL_FOR_A_BROADWAY_PLAY_CALLED;
		if (LCSrandom(insult_for_liberal.size() + 1)) {
			mvaddstrAlt(10, 1, pickrandom(insult_for_liberal));
		}
		else {
			if (lawList[LAW_FREESPEECH] == -2) mvaddstrAlt(10, 1, CONST_DUMB, gamelog);
			else mvaddstrAlt(10, 1, CONST_RETARDED, gamelog);
		}
		addstrAlt(singleSpace, gamelog);
		addstrAlt(pickrandom(word_replacing_liberal));
		addstrAlt(singleDot, gamelog);
	}
	else if (segmentpower < 20)
	{
		line_one = CONST_BUT_THE_INTERVIEW_IS_SO_BORING_THAT + name + CONST_FALLS_ASLEEP;
	}
	else if (segmentpower < 25)
	{
		line_one = CONST_C_BUT_SPACE + name + CONST_STUTTERS_NERVOUSLY_THE_WHOLE_TIME;
	}
	else if (segmentpower < 30)
	{
		line_one = name + CONST_S_VERBAL_FINESSE_LEAVES_SOMETHING_TO_BE_DESIRED;

	}
	else if (segmentpower < 45)
	{
		line_one = name + CONST_REPRESENTS_THE_LCS_WELL;
	}
	else if (segmentpower < 60)
	{
		line_one = CONST_THE_DISCUSSION_WAS_EXCITING_AND_DYNAMIC;
		line_two = CONST_EVEN_THE_CABLE_NEWS_AND_AM_RADIO_SPEND_DAYS_TALKING_ABOUT_IT;
	}
	else
	{
		line_one = repname + CONST_LATER_WENT_ON_TO_WIN_A_PULITZER_FOR_IT;
		line_two = CONST_VIRTUALLY_EVERYONE_IN_AMERICA_WAS_MOVED_BY + name + CONST_S_WORDS;
	}
	mvaddstrAlt(8, 1, line_one, gamelog);
	if (len(line_two) > 0) {
		mvaddstrAlt(9, 1, line_two, gamelog);
	}
	gamelog.newline();
}
void printShotBySniper(const string targname) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_A_SNIPER_TAKES_OUT, gamelog);
	addstrAlt(targname, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.newline();
}
void printMissedBySniper(const string targname) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_A_SNIPER_NEARLY_HITS, gamelog);
	addstrAlt(targname, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.newline();
}

void printWasKilledInBombing(const string targname) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, targname, gamelog);
	addstrAlt(CONST_WAS_KILLED_IN_THE_BOMBING, gamelog);
	gamelog.newline();
}
void printNarrowlyAvoidsDeath(const string targname) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, targname, gamelog);
	addstrAlt(CONST_NARROWLY_AVOIDED_DEATH, gamelog);
	gamelog.newline();
}
void printNoOneIsHurt(const bool clearformess) {
	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_FORTUNATELY_NO_ONE_IS_HURT, gamelog);
	gamelog.newline();
}

void printCONST_THE_LIGHTS_FADE_AND_ALL_IS_DARK(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_THE_LIGHTS_FADE_AND_ALL_IS_DARK, gamelog);
	gamelog.newline();
}
void printCONST_THE_GENERATOR_HAS_BEEN_DESTROYED(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_THE_GENERATOR_HAS_BEEN_DESTROYED, gamelog);
	gamelog.newline();
}
void printCONST_THERE_S_NOTHING_LEFT_BUT_SMOKING_WRECKAGE(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_THERE_S_NOTHING_LEFT_BUT_SMOKING_WRECKAGE, gamelog);
	gamelog.newline();
}
void printCONST_THE_ANTI_AIRCRAFT_GUN_TAKES_A_DIRECT_HIT(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_THE_ANTI_AIRCRAFT_GUN_TAKES_A_DIRECT_HIT, gamelog);
	gamelog.newline();
}
void printCONST_EXPLOSIONS_ROCK_THE_COMPOUND(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_EXPLOSIONS_ROCK_THE_COMPOUND, gamelog);
	gamelog.newline();
}
void printCONST_A_SKILLED_PILOT_GETS_THROUGH(const bool clearformess) {

	mvaddstrAlt(8, 1, CONST_A_SKILLED_PILOT_GETS_THROUGH, gamelog);
	gamelog.newline();
}
void printCONST_IT_S_ALL_OVER_THE_TV_EVERYONE_IN_THE_LIBERAL_CRIME_SQUAD_GAINS_20_JUICE(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_IT_S_ALL_OVER_THE_TV_EVERYONE_IN_THE_LIBERAL_CRIME_SQUAD_GAINS_20_JUICE, gamelog);
}
void printCONST_HIT_ONE_OF_THE_BOMBERS_SLAMS_INTO_TO_THE_GROUND(const bool clearformess) {

	mvaddstrAlt(8, 1, CONST_HIT_ONE_OF_THE_BOMBERS_SLAMS_INTO_TO_THE_GROUND, gamelog);
	gamelog.newline();
}
void printCONST_YOU_DIDN_T_SHOOT_ANY_DOWN_BUT_YOU_VE_MADE_THEM_THINK_TWICE(const bool clearformess) {

	mvaddstrAlt(8, 1, CONST_YOU_DIDN_T_SHOOT_ANY_DOWN_BUT_YOU_VE_MADE_THEM_THINK_TWICE, gamelog);
}
void printCONST_THE_THUNDER_OF_THE_ANTI_AIRCRAFT_GUN_SHAKES_THE_COMPOUND(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	mvaddstrAlt(8, 1, CONST_THE_THUNDER_OF_THE_ANTI_AIRCRAFT_GUN_SHAKES_THE_COMPOUND, gamelog);
	gamelog.newline();
}
void printCONST_YOU_HEAR_PLANES_STREAK_OVERHEAD(const bool clearformess) {

	if (clearformess) eraseAlt();
	else makedelimiter();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_YOU_HEAR_PLANES_STREAK_OVERHEAD, gamelog);
	gamelog.newline();
}
void printConservativesRaidedUnoccupiedSafehouse(const string locname) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_CONSERVATIVES_HAVE_RAIDED_THE, gamelog);
	addstrAlt(locname, gamelog);
	addstrAlt(CONST_AN_UNOCCUPIED_SAFEHOUSE, gamelog);
	gamelog.newline();

}
void printCorpseRecovered(const string pname, const int y) {
	mvaddstrAlt(y + 9, 1, pname);
	addstrAlt(CONST_S_CORPSE_HAS_BEEN_RECOVERED, gamelog);
	gamelog.newline();

}
void printLiberalRescued(const string pname, const int y) {
	mvaddstrAlt(y + 9, 1, pname);
	addstrAlt(CONST_HAS_BEEN_RESCUED, gamelog);
	gamelog.newline();

}
void printCCSRaidSafehouse() {
	eraseAlt();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_CCS_MEMBERS_POUR_OUT_OF_THE_TRUCK_AND_SHOOT_IN_THE_FRONT_DOORS, gamelog);
	gamelog.nextMessage();
}

void printCorpSiegeWarning(const int sleeper, const string locationName) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_YOU_HAVE_RECEIVED, gamelog);
	if (sleeper)addstrAlt(CONST_YOUR_SLEEPER_CEO_S_WARNING, gamelog);
	else addstrAlt(CONST_AN_ANONYMOUS_TIP, gamelog);
	addstrAlt(CONST_THAT_THE_CORPORATIONS, gamelog);
	mvaddstrAlt(9, 1, CONST_ARE_HIRING_MERCENARIES_TO_ATTACK, gamelog);
	if (sleeper)addstrAlt(locationName, gamelog);
	else addstrAlt(CONST_LC_THE_LCS, gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.nextMessage();
}
void corporateSiegePrint(const string lname) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_CORPORATE_MERCENARIES_ARE_RAIDING_THE, gamelog);
	addstrAlt(lname, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.nextMessage();
}
void printCCSCarbomb() {
	eraseAlt();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_TRUCK_PLOWS_INTO_THE_BUILDING_AND_EXPLODES, gamelog);
	gamelog.nextMessage();
}
void printCCSRaid(const string lname) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_A_SCREECHING_TRUCK_PULLS_UP_TO, gamelog);
	addstrAlt(lname, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.newline();
}
void printEveryoneInjuredHeader() {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 1, CONST_CCS_CAR_BOMBING_CASUALTY_REPORT);
	mvaddstrAlt(2, 1, CONST_UC_KILLED);
	mvaddstrAlt(6, 1, CONST_INJURED);
}

void printInjuredList(const vector<pair<string, int> > injuredList) {
	int injured_y = 6;
	int injured_x = 10;
	for (pair<string, int> injured : injuredList)
	{


		int namelength = len(injured.first);

		if (injured_x + namelength > 78)
		{
			injured_y++;
			injured_x = 1;
			//Add limit for killed_y.
		}
		set_alignment_color(injured.second, false);
		mvaddstrAlt(injured_y, injured_x, injured.first);
		addstrAlt(COMMA_SPACE);
		injured_x += namelength + 2;


		//set_alignment_color(pool[i]->align,false);
		//addstrAlt(pool[i]->name);


	}
}
void printKillList(const vector<pair<string, int> > killList) {
	int killed_y = 2;
	int killed_x = 9;
	for (pair<string, int> injured : killList)
	{


		int namelength = len(injured.first);

		if (killed_x + namelength > 78)
		{
			killed_y++;
			killed_x = 1;
			//Add limit for killed_y.
		}
		set_alignment_color(injured.second, false);
		mvaddstrAlt(killed_y, killed_x, injured.first);
		addstrAlt(COMMA_SPACE);
		killed_x += namelength + 2;

	}
}
void printCCSSleeperWarning(const string lname) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_YOU_HAVE_RECEIVED_A_SLEEPER_WARNING_THAT_THE_CCS, gamelog);
	mvaddstrAlt(9, 1, CONST_IS_GEARING_UP_TO_ATTACK, gamelog);
	addstrAlt(lname, gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.nextMessage();
}

void printJetBombers() {

	mvaddstrAlt(11, 1, CONST_YOU_HEAR_JET_BOMBERS_STREAK_OVERHEAD, gamelog);
	gamelog.nextMessage();
}
void printTankArrival(const bool tank_traps) {

	if (tank_traps)
		mvaddstrAlt(10, 1, CONST_AN_M1_ABRAMS_TANK_IS_STOPPED_BY_THE_TANK_TRAPS, gamelog);
	else mvaddstrAlt(10, 1, CONST_AN_M1_ABRAMS_TANK_TAKES_UP_POSITION_OUTSIDE_THE_COMPOUND, gamelog);
	gamelog.nextMessage();
}
void printSWATArrival() {
	mvaddstrAlt(9, 1, CONST_NATIONAL_GUARD_TROOPS_ARE_REPLACING_NORMAL_SWAT_UNITS, gamelog);
	gamelog.nextMessage();
}
void printPoliceSiegeHeader(const string lname) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_POLICE_HAVE_SURROUNDED_THE, gamelog);
	addstrAlt(lname, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.newline();
}
void printPoliceSleeperWarning(const string locationName, const int siegeEscalationState) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_YOU_HAVE_RECEIVED_ADVANCE_WARNING_FROM_YOUR_SLEEPERS_REGARDING, gamelog);
	mvaddstrAlt(9, 1, CONST_AN_IMMINENT_POLICE_RAID_ON, gamelog);
	addstrAlt(locationName);
	addstrAlt(singleDot, gamelog);
	gamelog.newline();
	if (siegeEscalationState >= 1)
	{
		mvaddstrAlt(11, 1, CONST_THE_FIGHTING_FORCE_WILL_BE_COMPOSED_OF_NATIONAL_GUARD_TROOPS, gamelog);
	}
	if (siegeEscalationState >= 2)
	{
		mvaddstrAlt(12, 1, CONST_A_TANK_WILL_COVER_THE_ENTRANCE_TO_THE_COMPOUND, gamelog);
	}
	if (siegeEscalationState >= 3)
	{
		mvaddstrAlt(13, 1, CONST_PLANES_WILL_BOMB_THE_COMPOUND_DURING_THE_SIEGE_AND_THE_FINAL, gamelog);
		mvaddstrAlt(14, 1, CONST_ATTACK_WILL_BE_CARRIED_OUT_BY_SEAL_TEAM_6, gamelog);
	}
	gamelog.nextMessage(); //Write out buffer to prepare for next message.
	mvaddstrAlt(15, 1, CONST_PRESS_ESC_TO_PONDER_THE_SITUATION);
}
void printPoliceSiegeEmptyHeader(const string lname) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_COPS_HAVE_RAIDED_THE, gamelog);
	addstrAlt(lname, gamelog);
	addstrAlt(CONST_AN_UNOCCUPIED_SAFEHOUSE, gamelog);
	gamelog.newline();
}

void printCorpseRecoveredByPolice(const string corpse, const int y) {
	mvaddstrAlt(y + 9, 1, corpse, gamelog);
	addstrAlt(CONST_S_CORPSE_HAS_BEEN_RECOVERED, gamelog);
	gamelog.newline();
}
void printKidnapRecoveredByPolice(const string kidnap, const int y) {
	mvaddstrAlt(y + 9, 1, kidnap, gamelog);
	addstrAlt(CONST_HAS_BEEN_RESCUED, gamelog);
	gamelog.newline();
}

void printSpecificCrime(const Lawflags crime) {
	mvaddstrAlt(4, 1, youAreWantedForThis[crime], gamelog);
}

void printBrokenLawsFooter(const bool kidnapped, const int typenum) {
	if (!kidnapped)
	{
		if (typenum > 1) addstrAlt(CONST_AND_OTHER_CRIMES, gamelog);
		addstrAlt(singleDot, gamelog);
	}
	gamelog.nextMessage();
}
void printHarboringFugitive() {
	mvaddstrAlt(4, 1, CONST_YOU_ARE_WANTED_FOR_HARBORING_A_FUGITIVE_FROM_JUSTICE, gamelog);
}
void printBrokenLawsHeader(const char underAttack, const short escalation) {
	int publicmood(const int old_l);
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (underAttack) mvaddstrAlt(1, 1, CONST_YOU_HEAR_SHOUTS, gamelog);
	else mvaddstrAlt(1, 1, CONST_YOU_HEAR_A_BLARING_VOICE_ON_A_LOUDSPEAKER, gamelog);
	gamelog.newline();
	if (escalation >= 2 && publicmood(-1) < 20)
		mvaddstrAlt(3, 1, CONST_IN_THE_NAME_OF_GOD_YOUR_CAMPAIGN_OF_TERROR_ENDS_HERE, gamelog);
	else mvaddstrAlt(3, 1, CONST_SURRENDER_YOURSELVES, gamelog);
	gamelog.newline();
}
void printBurnedFlag(const int flagLaw) {

	if (flagLaw == -2)mvaddstrAlt(4, 1, CONST_YOU_ARE_WANTED_FOR_FLAG_MURDER, gamelog);
	else if (flagLaw == -1)mvaddstrAlt(4, 1, CONST_YOU_ARE_WANTED_FOR_FELONY_FLAG_BURNING, gamelog);
	else mvaddstrAlt(4, 1, CONST_YOU_ARE_WANTED_FOR_FLAG_BURNING, gamelog);
}
void printHireIllegal(const bool lawStatus) {
	mvaddstrAlt(4, 1, (lawStatus ? CONST_YOU_ARE_WANTED_FOR_HIRING_AN_ILLEGAL_ALIEN : CONST_YOU_ARE_WANTED_FOR_HIRING_AN_UNDOCUMENTED_WORKER), gamelog);
}
void printReleaseKidnapped(const string kname, const int kidnapped) {
	mvaddstrAlt(4, 1, CONST_RELEASE, gamelog);
	addstrAlt(kname, gamelog);
	if (kidnapped > 1) addstrAlt(CONST_AND_THE_OTHERS, gamelog);
	addstrAlt(CONST_UNHARMED, gamelog);
}

void printMostSeriousCrime(const bool breakercount[LAWFLAGNUM]) {
	extern short lawList[LAWNUM];
	for (auto const& x : mostSeriousCrime)
	{
		if (breakercount[x.first]) {
			addstrAlt(x.second);
			return;
		}
	}

	if (breakercount[LAWFLAG_BURNFLAG]) {
		addstrAlt(lawList[LAW_FLAGBURNING] == -2 ? CONST_UC_FLAG_MURDER : CONST_UC_FLAG_BURNING);
		return;
	}

	for (auto const& x : mostSeriousCrime2)
	{
		if (breakercount[x.first]) {
			addstrAlt(x.second);
			return;
		}
	}

	if (breakercount[LAWFLAG_HIREILLEGAL]) {
		addstrAlt(lawList[LAW_IMMIGRATION] < 1 ? CONST_UC_HIRING_ILLEGAL_ALIENS : CONST_UC_HIRING_UNDOCUMENTED_WORKERS);
		return;
	}

	for (auto const& x : mostSeriousCrime3)
	{
		if (breakercount[x.first]) {
			addstrAlt(x.second);
			return;
		}
	}
}
void printWantedFor() {
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);

	addstrAlt(CONST_WANTED_FOR);
}
void printRehab() {

	addstrAlt(CONST_REHABILITATION);
}
void printEveryoneHereIsDead(const string lname) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 1, CONST_EVERYONE_IN_THE, gamelog);
	addstrAlt(lname, gamelog);
	addstrAlt(CONST_IS_SLAIN, gamelog);
	gamelog.newline();
}
void printBusinessFrontTaken() {
	mvaddstrAlt(12, 1, CONST_MATERIALS_RELATING_TO_THE_BUSINESS_FRONT_HAVE_BEEN_TAKEN, gamelog);
	gamelog.newline();
}
void printCompoundDismantled() {
	mvaddstrAlt(10, 1, CONST_THE_COMPOUND_IS_DISMANTLED, gamelog);
	gamelog.newline();
}
void printPrintingpressDismantled() {
	mvaddstrAlt(10, 1, CONST_THE_PRINTING_PRESS_IS_DISMANTLED_AND_BURNED, gamelog);
	gamelog.newline();
}
void printMoneyConfiscated(const int confiscated) {
	mvaddstrAlt(8, 1, CONST_LAW_ENFORCEMENT_HAS_CONFISCATED + tostring(confiscated) + CONST_IN_LCS_FUNDS, gamelog);
	gamelog.newline();
}
void printFundsIntact() {
	mvaddstrAlt(8, 1, CONST_FORTUNATELY_YOUR_FUNDS_REMAIN_INTACT, gamelog);
	gamelog.newline();
}
void printLiberalsTakenToPolice(const int pcount) {
	mvaddstrAlt(5, 1, pcount, gamelog);
	addstrAlt(CONST_LIBERALS_ARE_TAKEN_TO_THE_POLICE_STATION, gamelog);
	gamelog.newline();
}
void printSingleLiberalTaken(const string pname, const string pcname) {

	mvaddstrAlt(5, 1, pname, gamelog);
	if (pname == pcname)
	{
		addstrAlt(CONST_AKA, gamelog);
		addstrAlt(pcname, gamelog);
		addstrAlt(CONST_X_SINGLE_COMMA, gamelog);
	}
	mvaddstrAlt(6, 1, CONST_IS_TAKEN_TO_THE_POLICE_STATION, gamelog);
	gamelog.newline();
}
void printKidnapFreed() {
	mvaddstrAlt(3, 1, CONST_THE_KIDNAP_VICTIMS_ARE_REHABILITATED_AND_FREED, gamelog);
	gamelog.newline();
}
void printSingleKidnapFreed(const string kname) {

	mvaddstrAlt(3, 1, kname);
	addstrAlt(CONST_IS_REHABILITATED_AND_FREED, gamelog);
	gamelog.newline();
}
void printTheyConfiscateEverything(const int siege, const int escalationState) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (siege == SIEGE_POLICE && escalationState == 0)
		mvaddstrAlt(1, 1, CONST_THE_POLICE, gamelog);
	else if (siege == SIEGE_POLICE && escalationState >= 1)
		mvaddstrAlt(1, 1, CONST_THE_SOLDIERS, gamelog);
	else mvaddstrAlt(1, 1, CONST_THE_FIREMEN, gamelog);
	addstrAlt(CONST_CONFISCATE_EVERYTHING_INCLUDING_SQUAD_WEAPONS, gamelog);
	gamelog.newline();
}
void printCorpseRecovery(const int y, const string name) {
	mvaddstrAlt(y + 9, 1, name, gamelog);
	addstrAlt(CONST_S_CORPSE_HAS_BEEN_RECOVERED, gamelog);
	gamelog.newline();
}
void printKidnapRescue(const int y, const string name) {
	mvaddstrAlt(y + 9, 1, name, gamelog);
	addstrAlt(CONST_HAS_BEEN_RESCUED, gamelog);
	gamelog.newline();
}
void printFiremenSiegeEmpty(const string locationName) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_FIREMEN_HAVE_RAIDED_THE, gamelog);
	addstrAlt(locationName, gamelog);
	addstrAlt(CONST_AN_UNOCCUPIED_SAFEHOUSE, gamelog);
	gamelog.newline();
}
void printFiremenRaid2() {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 1, CONST_YOU_HEAR_A_SCREECHING_VOICE_OVER_THE_SOUND_OF_FIRE_ENGINE_SIRENS, gamelog);
	gamelog.newline();
	mvaddstrAlt(3, 1, CONST_SURRENDER_YOURSELVES, gamelog);
	gamelog.newline();
	mvaddstrAlt(4, 1, CONST_UNACCEPTABLE_SPEECH_HAS_OCCURRED_AT_THIS_LOCATION, gamelog);
	gamelog.newline();
	mvaddstrAlt(6, 1, CONST_COME_QUIETLY_AND_YOU_WILL_NOT_BE_HARMED, gamelog);
	gamelog.nextMessage();
}
void printFiremenRaid(const string loc) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_SCREAMING_FIRE_ENGINES_PULL_UP_TO_THE, gamelog);
	addstrAlt(loc, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.newline();
	mvaddstrAlt(9, 1, CONST_ARMORED_FIREMEN_SWARM_OUT_PILOT_LIGHTS_BURNING, gamelog);
	gamelog.newline();
}
void printFiremenSiegeEmpty(const bool printingPress, const bool businessFront) {
	if (printingPress)
	{
		mvaddstrAlt(10, 1, CONST_THE_PRINTING_PRESS_IS_DISMANTLED_AND_BURNED, gamelog);
		gamelog.newline();
	}
	if (businessFront)
	{
		mvaddstrAlt(12, 1, CONST_MATERIALS_RELATING_TO_THE_BUSINESS_FRONT_HAVE_BEEN_DESTROYED, gamelog);
		gamelog.newline();
	}
}
void printCIASiegeWarning(const string locationName) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_A_SLEEPER_AGENT_HAS_REPORTED_THAT_THE_CIA_IS_PLANNING, gamelog);
	mvaddstrAlt(9, 1, CONST_TO_LAUNCH_AN_ATTACK_ON, gamelog);
	addstrAlt(locationName, gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.nextMessage();
}
void printCIASiege(const string locationName, const bool hasCameras, const bool hasAGenerator) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_UNMARKED_BLACK_VANS_ARE_SURROUNDING_THE, gamelog);
	addstrAlt(locationName, gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.newline();
	if (hasCameras)
	{
		mvaddstrAlt(9, 1, CONST_THROUGH_SOME_FORM_OF_HIGH_TECHNOLOGY_THEY_VE_MANAGED, gamelog);
		mvaddstrAlt(10, 1, CONST_TO_SHUT_OFF_THE_LIGHTS_AND_THE_CAMERAS, gamelog);
		gamelog.nextMessage();
	}
	else if (hasAGenerator)
	{
		mvaddstrAlt(9, 1, CONST_THROUGH_SOME_FORM_OF_HIGH_TECHNOLOGY_THEY_VE_MANAGED, gamelog);
		mvaddstrAlt(10, 1, CONST_TO_SHUT_OFF_THE_LIGHTS, gamelog);
		gamelog.nextMessage();
	}
	else
	{
		mvaddstrAlt(9, 1, CONST_THEY_VE_SHUT_OFF_THE_LIGHTS, gamelog);
		gamelog.nextMessage();
	}
}
void printRadioHicksSiege(const int l) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_MASSES_DISSATISFIED_WITH_YOUR_LACK_OF_RESPECT_FOR_AM_RADIO, gamelog);
	mvaddstrAlt(9, 1, CONST_ARE_STORMING_THE, gamelog);
	addstrAlt(LocationsPool::getInstance().getLocationName(l), gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.nextMessage();
}
void printCableHicksSiege(const int l) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_MASSES_DISSATISFIED_WITH_YOUR_LACK_OF_RESPECT_FOR_CABLE_NEWS, gamelog);
	mvaddstrAlt(9, 1, CONST_ARE_STORMING_THE, gamelog);
	addstrAlt(LocationsPool::getInstance().getLocationName(l), gamelog);
	addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
	gamelog.nextMessage();
}
void printFiremenSiege(const bool sleeper, const int l) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (sleeper) mvaddstrAlt(8, 1, CONST_A_SLEEPER_FIREMAN_HAS_INFORMED_YOU_THAT, gamelog);
	else mvaddstrAlt(8, 1, CONST_WORD_IN_THE_UNDERGROUND_IS_THAT, gamelog);
	mvaddstrAlt(9, 1, CONST_THE_FIREMEN_ARE_PLANNING_TO_BURN, gamelog);
	addstrAlt(LocationsPool::getInstance().getLocationName(l), gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.nextMessage();
}



void printReflectOnYourConJudgement()
{
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 1, CONST_C_REFLECT_ON_YOUR_CONSERVATIVE_JUDGMENT);
}

void printSallyForthSiege() {
	eraseAlt();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 26, CONST_UNDER_SIEGE_ESCAPE_OR_ENGAGE);
	set_color_easy(WHITE_ON_BLACK);
	int yLevel = 3;
	for (int i = 0; i < len(nextSiege); i++) {
		mvaddstrAlt(yLevel + i, 11, nextSiege[i]);
	}
	yLevel++;
	yLevel += len(nextSiege);
	for (int i = 0; i < len(nextSiegeAgain); i++) {
		mvaddstrAlt(yLevel + i, 11, nextSiegeAgain[i]);
	}
}
void printSallyForthFooter() {
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(23, 11, CONST_PRESS_ANY_KEY_TO_CONFRONT_THE_CONSERVATIVE_AGGRESSORS);
	// Seperate logging text
	gamelog.log(CONST_YOUR_LIBERALS_SALLY_FORTH_TO_CONFRONT_THE_SIEGE);
}
void printYoureFree() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	clearmessagearea();
	mvaddstrAlt(16, 1, CONST_YOU_RE_FREE, gamelog);
	gamelog.nextMessage();
}
void printSiegeIsBroken() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	clearmessagearea();
	mvaddstrAlt(16, 1, CONST_THE_SIEGE_IS_BROKEN, gamelog);
	gamelog.nextMessage();
}
void printSiegeOptions(const int partysize, const short party_status) {
	if (partysize > 1)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 40, O_CHANGE_SQUAD_ORDER);
	if (partysize > 0 && (party_status == -1 || partysize > 1))set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 40, HASH_CHECK_STATUS_OF_LIBERAL);
	if (party_status != -1)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 40, show_squad_liberal_status);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 1, CONST_D_ESCAPE);
	mvaddstrAlt(10, 1, CONST_E_EQUIP);
	mvaddstrAlt(11, 1, CONST_F_FIGHT);
	mvaddstrAlt(12, 1, CONST_G_SURRENDER);
}
void printLocationName(const string loc) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, loc);
}


void printTanksMoveToEntrance(const bool clearformess) {
	if (!clearformess)
	{
		makedelimiter();
	}
	mvaddstrAlt(clearformess ? 9 : 8, 1, CONST_THE_TANK_MOVES_FORWARD_TO_YOUR_COMPOUND_ENTRANCE, gamelog);
	gamelog.newline();
}
void printEngineersRemoveTankTrap(const bool clearformess) {
	if (clearformess) eraseAlt();
	else makedelimiter();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_ARMY_ENGINEERS_HAVE_REMOVED_YOUR_TANK_TRAPS, gamelog);
	gamelog.newline();
}
void logADayPasses() {
	gamelog.record(CONST_A_DAY_PASSES_WHILE_UNDER_SIEGE);
	gamelog.newline();
}
void printYourLiberalsAreStarving(const bool clearformess) {
	if (clearformess) eraseAlt();
	else makedelimiter();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_YOUR_LIBERALS_ARE_STARVING, gamelog);
	gamelog.newline();
}
void printHasStarvedToDeath(const string pname, const bool clearformess) {
	if (clearformess) eraseAlt();
	else makedelimiter();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, pname, gamelog);
	addstrAlt(CONST_HAS_STARVED_TO_DEATH, gamelog);
	gamelog.newline();
}
void printTheCopsAreComing(const bool clearformess) {
	if (clearformess) eraseAlt();
	else makedelimiter();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_THE_COPS_ARE_COMING, gamelog);
	gamelog.newline();
}
void printYouHaveEscaped() {
	eraseAlt();
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 32, CONST_YOU_HAVE_ESCAPED, gamelog);
	gamelog.nextMessage();
	set_color_easy(WHITE_ON_BLACK);
	int yLevel = 3;
	for (int i = 0; i < len(engageConservativesEscape); i++) {
		mvaddstrAlt(yLevel + i, 11, engageConservativesEscape[i]);
	}
	yLevel += len(engageConservativesEscape);
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(yLevel + 1, 11, CONST_PRESS_ANY_KEY_TO_SPLIT_UP_AND_LAY_LOW_FOR_A_FEW_DAYS);
	// Seperate logging text
	gamelog.log(CONST_YOUR_LIBERALS_SPLIT_UP_AND_LAY_LOW_FOR_A_FEW_DAYS);
}
void printEscapeEngageInfo() {
	eraseAlt();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 26, CONST_UNDER_ATTACK_ESCAPE_OR_ENGAGE);
	set_color_easy(WHITE_ON_BLACK);
	for (int i = 0; i < len(engageConservatives); i++) {
		mvaddstrAlt(3 + i, 11, engageConservatives[i]);
	}

}
void printEscapeEngageInfoFooter(const bool cameras, const bool traps) {
	int yLevel = 3 + len(engageConservatives);
	if (cameras)
	{
		mvaddstrAlt(yLevel, 16, CONST_YOUR_SECURITY_CAMERAS_LET_YOU_SEE_UNITS_ON_THE_M_AP);
	}
	if (traps)
	{
		mvaddstrAlt(yLevel + 1, 16, CONST_YOUR_TRAPS_WILL_HARASS_THE_ENEMY_BUT_NOT_THE_SQUAD);
	}
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(23, 11, CONST_PRESS_ANY_KEY_TO_CONFRONT_THE_CONSERVATIVE_AGGRESSORS);
	// Seperate logging text
	gamelog.log(CONST_YOUR_LIBERALS_CONFRONT_THE_CONSERVATIVES_WITHIN_THE_SAFEHOUSE);

}
void logDefeat() {

	gamelog.log(CONST_YOU_HAVE_BEEN_DEFEATED);
}
void printConquerText(const bool police) {

	eraseAlt();
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 26, CONST_FIVE_STARS_VICTORY_FIVE_STARS, gamelog);
	gamelog.newline();
	if (police)
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(3, 16, CONST_THE_CONSERVATIVE_AUTOMATONS_HAVE_BEEN_DRIVEN_BACK, gamelog);
		mvaddstrAlt(4, 11, CONST_THE_TIME_BEING_WHILE_THEY_ARE_REGROUPING_YOU_MIGHT_CONSIDER, gamelog);
		mvaddstrAlt(5, 11, CONST_ABANDONING_THIS_SAFE_HOUSE_FOR_A_SAFER_LOCATION, gamelog);
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(3, 16, CONST_THE_CONSERVATIVES_HAVE_BEEN_DRIVEN_BACK, gamelog);
		mvaddstrAlt(4, 11, CONST_UNFORTUNATELY_YOU_WILL_NEVER_TRULY_BE_SAFE_FROM, gamelog);
		mvaddstrAlt(5, 11, CONST_THIS_FILTH_UNTIL_THE_LIBERAL_AGENDA_IS_REALIZED, gamelog);
	}
	gamelog.nextMessage();
	mvaddstrAlt(7, 19, CONST_PRESS_C_TO_CONTINUE_LIBERALLY);
}

const string CONST_200_JUICE_TO_EVERYONE_FOR_ERADICATING_THE_CONSERVATIVE_CRIME_SQUAD = "+200 JUICE TO EVERYONE FOR ERADICATING THE CONSERVATIVE CRIME SQUAD";
const string CONST_REVOLUTION_TO_ATTEND_TO = "revolution to attend to?";
const string CONST_THE_CCS_HAS_BEEN_COMPLETELY_DESTROYED_NOW_WASN_T_THERE_A = "The CCS has been completely destroyed.  Now wasn't there a ";
const string CONST_THE_LAST_OF_THE_ENEMY_S_MORALE_AND_CONFIDENCE_IS_SHATTERED = "the last of the enemy's morale and confidence is shattered.";
const string CONST_WITH_ITS_FOUNDER_KILLED_IN_THE_HEART_OF_THEIR_OWN_BASE = "With its Founder killed in the heart of their own base, ";
const string CONST_SLIPS_AWAY = "slips away.  ";
const string CONST_THE_CCS_FOUNDER_LYING_DEAD_AT_THEIR_FEET_THE_SQUAD = "The CCS Founder lying dead at their feet, the squad ";
const string CONST_IT_IS_INCREASINGLY_CLEAR_THAT_THIS_WAS_THE_CCS_S_LAST_SAFEHOUSE = "it is increasingly clear that this was the CCS's last safehouse.";
const string CONST_AS_YOUR_LIBERALS_PICK_THROUGH_THE_REMAINS_OF_THE_SAFEHOUSE = "As your Liberals pick through the remains of the safehouse, ";
const string CONST_THEIR_FINAL_VICTORY = "their final victory.  ";
const string CONST_GUNFIRE_STILL_RINGING_IN_THEIR_EARS_THE_SQUAD_REVELS_IN = "Gunfire still ringing in their ears, the squad revels in ";
const string CONST_THIS_WILL_MAKE_A_FINE_BASE_FOR_FUTURE_LIBERAL_OPERATIONS = "this will make a fine base for future Liberal operations.";
const string CONST_POWER_HAS_BEEN_SEVERELY_WEAKENED_ONCE_THE_SAFEHOUSE_COOLS_OFF = "power has been severely weakened.  Once the safehouse cools off, ";
const string CONST_THE_CCS_FOUNDER_WASN_T_HERE_BUT_FOR_NOW_THEIR = "The CCS Founder wasn't here, but for now, their ";
const string CONST_THE_CCS_LIEUTENANT_LYING_DEAD_AT_THEIR_FEET_THE_SQUAD = "The CCS Lieutenant lying dead at their feet, the squad ";
const string CONST_THEIR_VICTORY = "their victory.  ";
void printConquerTextCCS(const int ccs_siege_kills, const int ccs_kills) {

	eraseAlt();
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 26, CONST_FIVE_STARS_VICTORY_FIVE_STARS, gamelog);
	gamelog.newline();
	if (ccs_kills < 3)
	{
		set_color_easy(WHITE_ON_BLACK);
		if (ccs_siege_kills > 10)
		{
			mvaddstrAlt(3, 16, CONST_GUNFIRE_STILL_RINGING_IN_THEIR_EARS_THE_SQUAD_REVELS_IN, gamelog);
			mvaddstrAlt(4, 11, CONST_THEIR_VICTORY, gamelog);
		}
		else
		{
			mvaddstrAlt(3, 16, CONST_THE_CCS_LIEUTENANT_LYING_DEAD_AT_THEIR_FEET_THE_SQUAD, gamelog);
			mvaddstrAlt(4, 11, CONST_SLIPS_AWAY);
		}
		addstrAlt(CONST_THE_CCS_FOUNDER_WASN_T_HERE_BUT_FOR_NOW_THEIR, gamelog);
		mvaddstrAlt(5, 11, CONST_POWER_HAS_BEEN_SEVERELY_WEAKENED_ONCE_THE_SAFEHOUSE_COOLS_OFF, gamelog);
		mvaddstrAlt(6, 11, CONST_THIS_WILL_MAKE_A_FINE_BASE_FOR_FUTURE_LIBERAL_OPERATIONS, gamelog);
	}
	else
	{
		if (ccs_siege_kills > 10)
		{
			mvaddstrAlt(3, 16, CONST_GUNFIRE_STILL_RINGING_IN_THEIR_EARS_THE_SQUAD_REVELS_IN, gamelog);
			mvaddstrAlt(4, 11, CONST_THEIR_FINAL_VICTORY, gamelog);
			mvaddstrAlt(6, 16, CONST_AS_YOUR_LIBERALS_PICK_THROUGH_THE_REMAINS_OF_THE_SAFEHOUSE, gamelog);
			mvaddstrAlt(7, 11, CONST_IT_IS_INCREASINGLY_CLEAR_THAT_THIS_WAS_THE_CCS_S_LAST_SAFEHOUSE, gamelog);
		}
		else
		{
			mvaddstrAlt(3, 16, CONST_THE_CCS_FOUNDER_LYING_DEAD_AT_THEIR_FEET_THE_SQUAD, gamelog);
			mvaddstrAlt(4, 11, CONST_SLIPS_AWAY, gamelog);
			mvaddstrAlt(6, 16, CONST_WITH_ITS_FOUNDER_KILLED_IN_THE_HEART_OF_THEIR_OWN_BASE, gamelog);
			mvaddstrAlt(7, 11, CONST_THE_LAST_OF_THE_ENEMY_S_MORALE_AND_CONFIDENCE_IS_SHATTERED, gamelog);
		}
		gamelog.newline();
		mvaddstrAlt(9, 16, CONST_THE_CCS_HAS_BEEN_COMPLETELY_DESTROYED_NOW_WASN_T_THERE_A, gamelog);
		mvaddstrAlt(10, 16, CONST_REVOLUTION_TO_ATTEND_TO, gamelog);
		gamelog.newline();
		mvaddstrAlt(12, 5, CONST_200_JUICE_TO_EVERYONE_FOR_ERADICATING_THE_CONSERVATIVE_CRIME_SQUAD, gamelog);
	}
	gamelog.nextMessage();
	mvaddstrAlt(15, 19, CONST_PRESS_C_TO_CONTINUE_LIBERALLY);
}
// end SIEGE
//
// SITEMODE
extern short lawList[LAWNUM];

const string CONST_LINE_D = "-D";
const string CONST_C_REFLECT_ON_YOUR_CONSERVATIVE_INEPTITUDE = "C - Reflect on your Conservative ineptitude";
const string CONST_R_REORGANIZE = "R - Reorganize";
const string CONST_R_RELEASE_HOSTAGE = "R - Release hostage";
const string CONST_R_RELEASE_OPPRESSED = "R - Release oppressed";
const string CONST_V_EVADE = "V - Evade";
const string CONST_V_RUN = "V - Run";
const string CONST_V_SNEAK = "V - Sneak";
const string CONST_U_USE = "U - Use";
const string CONST_U_GRAFFITI = "U - Graffiti";
const string CONST_T_TALK = "T - Talk";
const string CONST_K_KIDNAP = "K - Kidnap";
const string CONST_L_RELOAD = "L - Reload";
const string CONST_S_WAIT = "S - Wait";
const string CONST_M_MAP = "M - Map";
const string CONST_N_OPTIONS = "N - Options";
const string CONST_G_GET_LOOT = "G - Get Loot";
const string CONST_J_RELOAD_EMPTY = "J - Reload Empty";
const string CONST_W_A_D_X_MOVE = "W,A,D,X - Move";
const string CONST_CONSERVATIVES_SUSPICIOUS = ": CONSERVATIVES SUSPICIOUS";
const string CONST_CONSERVATIVES_ALARMED = ": CONSERVATIVES ALARMED";
const string CONST_ALIENATED_EVERYONE = ": ALIENATED EVERYONE";
const string CONST_ALIENATED_MASSES = ": ALIENATED MASSES";
const string CONST_CONSERVATIVE_REINFORCEMENTS_INCOMING = ": CONSERVATIVE REINFORCEMENTS INCOMING";
const string CONST_POLICE_RESPONDING = ": POLICE RESPONDING";
const string CONST_DEATH_SQUADS_RESPONDING = ": DEATH SQUADS RESPONDING";
const string CONST_CCS_VIGILANTIES_RESPONDING = ": CCS VIGILANTIES RESPONDING";
const string CONST_GANG_MEMBERS_RESPONDING = ": GANG MEMBERS RESPONDING";
const string CONST_ANGRY_MOB_RESPONDING = ": ANGRY MOB RESPONDING";
const string CONST_MERCENARIES_RESPONDING = ": MERCENARIES RESPONDING";
const string CONST_AGENTS_RESPONDING = ": AGENTS RESPONDING";
const string CONST_SECRET_SERVICE_RESPONDING = ": SECRET SERVICE RESPONDING";
const string CONST_SOLDIERS_AND_TANKS_RESPONDING = ": SOLDIERS AND TANKS RESPONDING";
const string CONST_LEVEL = ", Level ";
const string CONST_ESCAPE_OR_ENGAGE = ": Escape or Engage";
const string CONST_THERE_IS_A_CROWD_OF_PEOPLE_PASSING_BY = "There is a crowd of people passing by.";
const string CONST_THERE_IS_A_CROWD_OF_PEOPLE_UP_AHEAD = "There is a crowd of people up ahead.";
const string CONST_THERE_IS_A_GROUP_OF_PEOPLE_PASSING_BY = "There is a group of people passing by.";
const string CONST_THERE_IS_A_GROUP_OF_PEOPLE_UP_AHEAD = "There is a group of people up ahead.";
const string CONST_THERE_ARE_A_FEW_PEOPLE_PASSING_BY = "There are a few people passing by.";
const string CONST_THERE_ARE_A_FEW_PEOPLE_UP_AHEAD = "There are a few people up ahead.";
const string CONST_THERE_IS_SOMEONE_PASSING_BY = "There is someone passing by.";
const string CONST_THERE_IS_SOMEONE_UP_AHEAD = "There is someone up ahead.";
const string CONST_THE_LANDLORD_IS_IN = "The landlord is in.";
const string CONST_THE_LANDLORD_IS_OUT_OF_THE_OFFICE = "The landlord is out of the office.";
const string CONST_THE_CEO_S_STUDY_LIES_EMPTY = "The CEO's study lies empty.";
const string CONST_THE_CEO_IS_IN_HIS_STUDY = "The CEO is in his study.";
const string CONST_THE_CEO_MUST_HAVE_FLED_TO_A_PANIC_ROOM = "The CEO must have fled to a panic room.";
const string CONST_RATS = "[Rats!] ";
const string CONST_DAMN = "Damn! ";
const string CONST_THERE_ARE_PEOPLE_SITTING_HERE = "There are people sitting here.";
const string CONST_THE_BENCH_IS_EMPTY = "The bench is empty.";
const string CONST_THE_TABLE_IS_OCCUPIED = "The table is occupied.";
const string CONST_SOME_PEOPLE_ARE_HIDING_UNDER_THE_TABLE = "Some people are hiding under the table.";
const string CONST_THE_COMPUTER_IS_OCCUPIED = "The computer is occupied.";
const string CONST_THE_COMPUTER_HAS_BEEN_UNPLUGGED = "The computer has been unplugged.";
const string CONST_THE_POWER_OF_YOUR_LIBERAL_CONVICTIONS = "the power of your Liberal Convictions!";
const string CONST_THE_CONSERVATIVES_HAVE_SHRUNK_BACK_UNDER = "The Conservatives have shrunk back under ";
const string CONST_THE_CCS_HAS_BEEN_BROKEN = "The CCS has been broken!";
const string CONST_HAS_LEFT = " has left ";
const string CONST_THE_SQUAD_SNEAKS_PAST_THE_CONSERVATIVES = "The squad sneaks past the conservatives!";
const string CONST_YOU_FIND = "You find: ";
const string CONST_YOU_FEELING_SAFER_GETTING_OUT_ALONE = " you, feeling safer getting out alone.";
const string CONST_ONE_LIBERAL_LEAVES = "One Liberal leaves";
const string CONST_THE_LIBERAL_LEAVES = "The Liberal leaves";
const string CONST_SOME_LEAVE = "Some leave";
const string CONST_THEY_ALL_LEAVE = "They all leave";
const string CONST_FROM_THE_CONSERVATIVES = " from the Conservatives.";
const string CONST_AN_OPPRESSED_LIBERAL = "an Oppressed Liberal";
const string CONST_SOME_OPPRESSED_LIBERALS = "some Oppressed Liberals";
const string CONST_YOU_FREE = "You free ";
const string CONST_YOU_HAVE_TO_DEAL_WITH_THE_ENEMIES_FIRST = "You have to deal with the enemies first.";
const string CONST_WON_T_TALK_TO_YOU = " won't talk to you.";
const string CONST_TO_WHOM = "To whom?";
const string CONST_BLUFF = "Bluff";
const string CONST_DATING = "Dating";
const string CONST_ISSUES = "Issues";
const string CONST_WHICH_LIBERAL_WILL_SPEAK = "Which Liberal will speak?";
const string CONST_M_MUSIC = "[ ] M - Music";
const string CONST_E_ENCOUNTER_WARNINGS = "[ ] E - Encounter warnings";
const string CONST_SITE_MODE_OPTIONS = "Site mode options";
const string CONST_WHICH_WAY_W_A_D_AND_X_TO_MOVE_ENTER_TO_ABORT = "Which way?  (W,A,D, and X to move, ENTER to abort)";
const string CONST_IT_OPENS_EASILY_THE_ALARM_GOES_OFF = "It opens easily. The alarm goes off!";
const string CONST_THE_ALARM_GOES_OFF = "The alarm goes off!";
const string CONST_FORCE_IT_OPEN_YES_OR_NO = "Force it open? (Yes or No)";
const string CONST_IT_S_LOCKED_FROM_THE_OTHER_SIDE = "It's locked from the other side.";
const string CONST_LC_LOCKED = "locked.";
const string CONST_STILL = "still ";
const string CONST_YOU_SHAKE_THE_HANDLE_BUT_IT_IS = "You shake the handle but it is ";
const string CONST_YOUR_TAMPERING_SETS_OFF_THE_ALARM = "Your tampering sets off the alarm!";
const string CONST_TRY_TO_PICK_THE_LOCK_YES_OR_NO = "Try to pick the lock? (Yes or No)";
const string CONST_YOU_TRY_THE_DOOR_BUT_IT_IS_LOCKED = "You try the door, but it is locked.";
const string CONST_TRY_THE_DOOR_ANYWAY_YES_OR_NO = "Try the door anyway? (Yes or No)";
const string CONST_EMERGENCY_EXIT_ONLY_ALARM_WILL_SOUND = "EMERGENCY EXIT ONLY. ALARM WILL SOUND.";
const string CONST_THIS_DOOR_APPEARS_TO_BE_WIRED_UP_TO_AN_ALARM = "This door appears to be wired up to an alarm.";
const string CONST_THE_VAULT_DOOR_IS_IMPENETRABLE = "The vault door is impenetrable.";
const string CONST_TOO_HOT = "too hot";
const string CONST_YOUR_HOSTAGE_IS_FREE = "Your hostage is free.";
const string CONST_YOUR_HOSTAGES_ARE_FREE = "Your hostages are free.";
const string CONST_THE_POLICE_SUBDUE_AND_ARREST_THE_SQUAD = "The police subdue and arrest the squad.";
const string tag_X = "X";
void printItOpensWithAlarm() {
	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_IT_OPENS_EASILY_THE_ALARM_GOES_OFF, gamelog);
	gamelog.newline();
}
void printVaultIsImpenetrable() {

	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_VAULT_DOOR_IS_IMPENETRABLE, gamelog);
	gamelog.newline();
}
void printUnlockedButAlarmed(const bool locked) {

	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, locked ? CONST_THIS_DOOR_APPEARS_TO_BE_WIRED_UP_TO_AN_ALARM : CONST_EMERGENCY_EXIT_ONLY_ALARM_WILL_SOUND, gamelog);
	gamelog.newline();
	mvaddstrAlt(17, 1, CONST_TRY_THE_DOOR_ANYWAY_YES_OR_NO);
}
void printSquadSubduedHostagesFreed(const int hostages) {
	clearmessagearea();
	clearcommandarea();
	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_POLICE_SUBDUE_AND_ARREST_THE_SQUAD, gamelog);
	gamelog.newline();
	if (hostages > 0)
	{
		if (hostages > 1) {
			mvaddstrAlt(17, 1, CONST_YOUR_HOSTAGES_ARE_FREE, gamelog);
		}
		else {
			mvaddstrAlt(17, 1, CONST_YOUR_HOSTAGE_IS_FREE, gamelog);
		}
	}
	gamelog.newline();
}
void printShakeHandle(const bool locked, const bool has_security) {
	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (locked)
	{

		mvaddstrAlt(16, 1, CONST_YOU_SHAKE_THE_HANDLE_BUT_IT_IS + (has_security ? CONST_STILL : "") + CONST_LC_LOCKED, gamelog);
	}
	else {
		mvaddstrAlt(16, 1, CONST_IT_S_LOCKED_FROM_THE_OTHER_SIDE, gamelog);
	}
	gamelog.newline();
	mvaddstrAlt(17, 1, CONST_FORCE_IT_OPEN_YES_OR_NO);
}
void printLockpickPrompt() {
	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_YOU_TRY_THE_DOOR_BUT_IT_IS_LOCKED, gamelog);
	gamelog.newline();
	mvaddstrAlt(17, 1, CONST_TRY_TO_PICK_THE_LOCK_YES_OR_NO);
}
void printLockSetOffAlarm() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, CONST_YOUR_TAMPERING_SETS_OFF_THE_ALARM, gamelog);
	gamelog.newline();
}
void printAlarmGoesOff() {
	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_ALARM_GOES_OFF, gamelog);
	gamelog.newline();
}
void printWhichWay() {
	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_WHICH_WAY_W_A_D_AND_X_TO_MOVE_ENTER_TO_ABORT);
}
void printSitemodeOptions() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(10, 1, CONST_E_ENCOUNTER_WARNINGS);
	mvaddstrAlt(11, 1, CONST_M_MUSIC);
	mvaddstrAlt(24, 1, enter_done);
}
void printSitemodeOptionsHeader() {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, CONST_SITE_MODE_OPTIONS);
}
void printMusicEnabled(const bool musice) {
	mvaddstrAlt(11, 2, musice ? tag_X : singleSpace);
}
void printEncounterWarnings(const bool ewarn) {
	mvaddstrAlt(10, 2, ewarn ? tag_X : singleSpace);
}
void printActiveSquadTalkOptionsHeader() {
	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, CONST_WHICH_LIBERAL_WILL_SPEAK);
	mvaddstrAlt(9, 50, CONST_ISSUES);
	mvaddstrAlt(9, 60, CONST_DATING);
	mvaddstrAlt(9, 70, CONST_BLUFF);
}
void printToWhom() {
	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, CONST_TO_WHOM);
}
void set_color_easy_alignment(const int align) {
	switch (align)
	{
	case ALIGN_CONSERVATIVE: set_color_easy(RED_ON_BLACK_BRIGHT); break;
	case ALIGN_LIBERAL: set_color_easy(GREEN_ON_BLACK_BRIGHT); break;
	case ALIGN_MODERATE: set_color_easy(WHITE_ON_BLACK_BRIGHT); break;
	}

}
void printCreatureEncounter(const int t, const int talign, const string tname, const string tage) {
	int y = 11 + (t % 6);
	int x = 1 + (30 * (t / 6));
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddcharAlt(y, x, t + 'A');
	addstrAlt(spaceDashSpace);
	set_color_easy_alignment(talign);
	addstrAlt(tname);
	addstrAlt(tage);
}
void printIWontTalkToYou(const string tkname) {
	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, tkname);
	addstrAlt(CONST_WON_T_TALK_TO_YOU);
}
void printYouHaveEnemiesFirst() {

	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, CONST_YOU_HAVE_TO_DEAL_WITH_THE_ENEMIES_FIRST);
}
void printFreeThem(const int followers) {
	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_YOU_FREE, gamelog);
	if (followers > 1)addstrAlt(CONST_SOME_OPPRESSED_LIBERALS, gamelog);
	else addstrAlt(CONST_AN_OPPRESSED_LIBERAL, gamelog);
	addstrAlt(CONST_FROM_THE_CONSERVATIVES, gamelog);
	gamelog.newline();
}
void printFreeThemWithoutYou(const int followers, const int actgot) {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (actgot == 0 && followers > 1)mvaddstrAlt(16, 1, CONST_THEY_ALL_LEAVE, gamelog);
	else if (followers - actgot > 1)mvaddstrAlt(16, 1, CONST_SOME_LEAVE, gamelog);
	else if (actgot == 0)mvaddstrAlt(16, 1, CONST_THE_LIBERAL_LEAVES, gamelog);
	else mvaddstrAlt(16, 1, CONST_ONE_LIBERAL_LEAVES, gamelog);
	addstrAlt(CONST_YOU_FEELING_SAFER_GETTING_OUT_ALONE, gamelog);
	gamelog.newline();
}
void printEnemyCar(const string cname, const int v) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(19, v * 20 + 1, cname);

}
void printClearChaseScreen() {
	for (int i = 19; i <= 24; i++) {
		mvaddstrAlt(i, 0, CONST_80_SPACES); // 80 spaces
	}
}
void printYouFind(const string that_thing) {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(16, 1, CONST_YOU_FIND, gamelog);
	mvaddstrAlt(17, 1, that_thing, gamelog);
	gamelog.newline();
}
void printSneakPast() {
	clearmessagearea();
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_SQUAD_SNEAKS_PAST_THE_CONSERVATIVES, gamelog);
	gamelog.newline();
}
void printEnemyCarPassenger(const string ename, const int vnum, const int pnum, const bool driver) {
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(pnum + 20, vnum * 20 + 1, ename);
	if (driver) {
		addstrAlt(CONST_LINE_D);
	}
}
void printReflectOnIneptitude() {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 1, CONST_C_REFLECT_ON_YOUR_CONSERVATIVE_INEPTITUDE);
}
void printSiegeName(const string sname, const int locz) {

	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, sname);
	addstrAlt(CONST_LEVEL);
	addstrAlt(locz + 1);
	addstrAlt(CONST_ESCAPE_OR_ENGAGE);
}
void printCONSERVATIVES_SUSPICIOUS() {
	addstrAlt(CONST_CONSERVATIVES_SUSPICIOUS);
}
void printCONSERVATIVES_ALARMED() {
	addstrAlt(CONST_CONSERVATIVES_ALARMED);
}
void printALIENATED_EVERYONE() {
	addstrAlt(CONST_ALIENATED_EVERYONE);
}
void printALIENATED_MASSES() {
	addstrAlt(CONST_ALIENATED_MASSES);
}
void printCONSERVATIVE_REINFORCEMENTS_INCOMING() {
	addstrAlt(CONST_CONSERVATIVE_REINFORCEMENTS_INCOMING);
}
void printLocationNameAndAlarm(const string lname, const int postalarmtimer, const int locz) {

	if (postalarmtimer > 80) set_color_easy(RED_ON_BLACK_BRIGHT);
	else if (postalarmtimer > 60) set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, lname);
	addstrAlt(CONST_LEVEL);
	addstrAlt(locz + 1);
}
void printLocationSpecificWarning(const int lsite, const bool ccsRent) {
	switch (lsite)
	{
	case SITE_GOVERNMENT_ARMYBASE:
		addstrAlt(CONST_SOLDIERS_AND_TANKS_RESPONDING);
		break;
	case SITE_GOVERNMENT_WHITE_HOUSE:
		addstrAlt(CONST_SECRET_SERVICE_RESPONDING);
		break;
	case SITE_GOVERNMENT_INTELLIGENCEHQ:
		addstrAlt(CONST_AGENTS_RESPONDING);
		break;
	case SITE_CORPORATE_HEADQUARTERS:
	case SITE_CORPORATE_HOUSE:
		addstrAlt(CONST_MERCENARIES_RESPONDING);
		break;
	case SITE_MEDIA_AMRADIO:
	case SITE_MEDIA_CABLENEWS:
		addstrAlt(CONST_ANGRY_MOB_RESPONDING);
		break;
	case SITE_BUSINESS_CRACKHOUSE:
		addstrAlt(CONST_GANG_MEMBERS_RESPONDING);
		break;
	case SITE_GOVERNMENT_POLICESTATION:
	default:
		if (ccsRent)
		{
			addstrAlt(CONST_CCS_VIGILANTIES_RESPONDING);
		}
		else if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)addstrAlt(CONST_DEATH_SQUADS_RESPONDING);
		else addstrAlt(CONST_POLICE_RESPONDING);
		break;
	}
}
void printFoughtOffConservatives() {
	clearmessagearea();
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_CONSERVATIVES_HAVE_SHRUNK_BACK_UNDER, gamelog);
	mvaddstrAlt(17, 1, CONST_THE_POWER_OF_YOUR_LIBERAL_CONVICTIONS, gamelog);
	gamelog.newline();
}
void logBailOnBase(const string aname, const string sitename) {

	gamelog.record(aname);
	gamelog.record(CONST_HAS_LEFT);
	gamelog.record(sitename);
	gamelog.record(singleDot);
	gamelog.nextMessage();
}
void printCafeComputerEmpty() {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_COMPUTER_HAS_BEEN_UNPLUGGED, gamelog);
	gamelog.newline();
}
void printCafeComputerFull() {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_COMPUTER_IS_OCCUPIED, gamelog);
	gamelog.newline();
}
void printTheCCSIsBroken() {
	clearmessagearea();
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_CCS_HAS_BEEN_BROKEN, gamelog);
	gamelog.newline();
}
void printEmptyBench() {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_BENCH_IS_EMPTY, gamelog);
	gamelog.newline();
}
void printFullBench() {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THERE_ARE_PEOPLE_SITTING_HERE, gamelog);
	gamelog.newline();

}
void printRestaurantTableFull() {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_TABLE_IS_OCCUPIED, gamelog);
	gamelog.newline();
}
void printRestaurantTableHiding() {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_SOME_PEOPLE_ARE_HIDING_UNDER_THE_TABLE, gamelog);
	gamelog.newline();
}
void printTheCEOHasFled() {
	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (lawList[LAW_FREESPEECH] != ALIGN_ARCHCONSERVATIVE)
		mvaddstrAlt(16, 1, CONST_DAMN, gamelog);
	else
		mvaddstrAlt(16, 1, CONST_RATS, gamelog);
	addstrAlt(CONST_THE_CEO_MUST_HAVE_FLED_TO_A_PANIC_ROOM, gamelog);
	gamelog.newline();
}
void printTheCEOIsIn() {

	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_CEO_IS_IN_HIS_STUDY, gamelog);
	gamelog.newline();
}
void printTheCEOIsOut() {

	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_CEO_S_STUDY_LIES_EMPTY, gamelog);
	gamelog.newline();
}
void printTheLandlordIsOut() {
	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_LANDLORD_IS_OUT_OF_THE_OFFICE, gamelog);
	gamelog.newline();
}
void printTheLandlordIsIn() {
	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_LANDLORD_IS_IN, gamelog);
	gamelog.newline();
}
void printShowEncounterWarning(const int numenc, const bool squadmoved) {

	clearmessagearea(false);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	string weMoved;
	string weDidntMove;
	if (numenc == 1)
	{
		weMoved = CONST_THERE_IS_SOMEONE_UP_AHEAD;
		weDidntMove = CONST_THERE_IS_SOMEONE_PASSING_BY;
	}
	else if (numenc <= 3)
	{
		weMoved = CONST_THERE_ARE_A_FEW_PEOPLE_UP_AHEAD;
		weDidntMove = CONST_THERE_ARE_A_FEW_PEOPLE_PASSING_BY;
	}
	else if (numenc <= 6)
	{
		weMoved = CONST_THERE_IS_A_GROUP_OF_PEOPLE_UP_AHEAD;
		weDidntMove = CONST_THERE_IS_A_GROUP_OF_PEOPLE_PASSING_BY;
	}
	else
	{
		weMoved = CONST_THERE_IS_A_CROWD_OF_PEOPLE_UP_AHEAD;
		weDidntMove = CONST_THERE_IS_A_CROWD_OF_PEOPLE_PASSING_BY;
	}
	if (squadmoved) {
		mvaddstrAlt(16, 1, weMoved, gamelog);
	}
	else {
		mvaddstrAlt(16, 1, weDidntMove, gamelog);
	}
	gamelog.newline();
}
void printPlayerSiteOptions(const bool isThereASiteAlarm, const bool enemy, const int partysize, const int party_status, const bool talkers) {

	if (!enemy || !isThereASiteAlarm)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, CONST_W_A_D_X_MOVE);
	if (partysize > 1)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 1, O_CHANGE_SQUAD_ORDER);
	if (partysize > 0 && (party_status == -1 || partysize > 1))set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(12, 1, HASH_CHECK_STATUS_OF_LIBERAL);
	if (party_status != -1)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, show_squad_liberal_status);
	if (isThereGroundLoot() || (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag&SITEBLOCK_LOOT))
		set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 17, CONST_G_GET_LOOT);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(10, 17, CONST_N_OPTIONS);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 32, CONST_M_MAP);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(10, 32, CONST_S_WAIT);
	if (!enemy || !isThereASiteAlarm) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 42, CONST_L_RELOAD);
	mvaddstrAlt(10, 1, CONST_J_RELOAD_EMPTY);
	if (enemy) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 42, CONST_K_KIDNAP);
	if (talkers) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(14, 17, CONST_T_TALK);
}
void printUseOrGraffiti(const bool graffiti, const bool print_me) {
	if (print_me) {
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
	}
	else {
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
	}
	if (graffiti)mvaddstrAlt(11, 42, CONST_U_GRAFFITI);
	else mvaddstrAlt(11, 42, CONST_U_USE);
}
void printEvade() {

	set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(12, 42, CONST_V_EVADE);
}
void printEquipAndFight(const bool enemy) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(9, 42, CONST_E_EQUIP);
	if (enemy)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(14, 1, CONST_F_FIGHT);
}
void printReleaseOppressed() {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(14, 32, CONST_R_RELEASE_OPPRESSED);
}
void printReleaseHostages(const bool hostages) {
	if (hostages) set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(14, 32, CONST_R_RELEASE_HOSTAGE);

}

#define CH_FULL_BLOCK 0xdb
#define CH_UPWARDS_ARROW 0x18
#define CH_DOWNWARDS_ARROW 0x19
#define CH_BLACK_SMILING_FACE 0x02
#define CH_YEN_SIGN 0x9d
#define CH_BOX_DRAWINGS_DOUBLE_VERTICAL 0xba
#define CH_BOX_DRAWINGS_DOUBLE_HORIZONTAL 0xcd
#define CH_WHITE_SMILING_FACE 0x01
void printMap(const bool has_cameras) {
	for (int x = 0; x < MAPX; x++)
	{
		for (int y = 0; y < MAPY; y++)
		{
			if (levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_KNOWN)
			{
				if (x == loc_coord.locx && y == loc_coord.locy)
				{
					set_color_easy(GREEN_ON_BLACK_BRIGHT);
					mvaddchAlt(y + 1, x + 5, CH_WHITE_SMILING_FACE);
				}
				else
				{
					set_color_easy(WHITE_ON_BLACK);
					if (levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_BLOCK)
					{
						set_color_easy(WHITE_ON_WHITE);
						mvaddchAlt(y + 1, x + 5, ' ');
					}
					else if (levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_DOOR)
					{  // Pick color
						if (levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_METAL)
							set_color_easy(WHITE_ON_WHITE_BRIGHT);
						else if (levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_CLOCK
							&& levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_LOCKED)
							set_color_easy(RED_ON_BLACK);
						else if (levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_KLOCK
							&& levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_LOCKED)
							set_color_easy(BLACK_ON_BLACK_BRIGHT);
						else set_color_easy(YELLOW_ON_BLACK);
						if ((levelmap[x + 1][y][loc_coord.locz].flag & SITEBLOCK_BLOCK) ||
							(levelmap[x - 1][y][loc_coord.locz].flag & SITEBLOCK_BLOCK))
							mvaddchAlt(y + 1, x + 5, CH_BOX_DRAWINGS_DOUBLE_HORIZONTAL);
						else mvaddchAlt(y + 1, x + 5, CH_BOX_DRAWINGS_DOUBLE_VERTICAL);
					}
					else if ((levelmap[x][y][loc_coord.locz].siegeflag & SIEGEFLAG_HEAVYUNIT) &&
						has_cameras)
					{
						set_color_easy(RED_ON_BLACK_BRIGHT);
						mvaddchAlt(y + 1, x + 5, CH_YEN_SIGN);
					}
					else if ((levelmap[x][y][loc_coord.locz].siegeflag & SIEGEFLAG_UNIT) &&
						has_cameras)
					{
						set_color_easy(RED_ON_BLACK_BRIGHT);
						mvaddchAlt(y + 1, x + 5, CH_BLACK_SMILING_FACE);
					}
					else if ((levelmap[x][y][loc_coord.locz].siegeflag & SIEGEFLAG_UNIT_DAMAGED) &&
						has_cameras)
					{
						set_color_easy(RED_ON_BLACK);
						mvaddchAlt(y + 1, x + 5, CH_BLACK_SMILING_FACE);
					}
					else if (levelmap[x][y][loc_coord.locz].special == SPECIAL_STAIRS_UP)
					{
						set_color_easy(YELLOW_ON_BLACK_BRIGHT);
						mvaddchAlt(y + 1, x + 5, CH_UPWARDS_ARROW);
					}
					else if (levelmap[x][y][loc_coord.locz].special == SPECIAL_STAIRS_DOWN)
					{
						set_color_easy(YELLOW_ON_BLACK_BRIGHT);
						mvaddchAlt(y + 1, x + 5, CH_DOWNWARDS_ARROW);
					}
					else if (levelmap[x][y][loc_coord.locz].special != -1)
					{
						set_color_easy(YELLOW_ON_BLACK_BRIGHT);
						mvaddchAlt(y + 1, x + 5, '!');
					}
					else if (levelmap[x][y][loc_coord.locz].siegeflag & SIEGEFLAG_TRAP)
					{
						set_color_easy(YELLOW_ON_BLACK_BRIGHT);
						mvaddchAlt(y + 1, x + 5, '!');
					}
					else if (levelmap[x][y][loc_coord.locz].flag & SITEBLOCK_LOOT)
					{
						set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
						mvaddchAlt(y + 1, x + 5, '$');
					}
					else mvaddchAlt(y + 1, x + 5, ' ');
				}
			}
			else
			{
				set_color_easy(BLACK_ON_BLACK_BRIGHT);
				mvaddchAlt(y + 1, x + 5, CH_FULL_BLOCK);
			}
		}
	}
}
void logNewLine() {
	gamelog.newline();
}
void printReorganize(const int libnum) {
	if (libnum > 6)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(14, 32, CONST_R_REORGANIZE);
}
void printSneakOrRun(const bool evade) {

	set_color_easy(WHITE_ON_BLACK);
	if (!evade)
		mvaddstrAlt(12, 42, CONST_V_SNEAK);
	else
		mvaddstrAlt(12, 42, CONST_V_RUN);
}
//
// STEALTH
const string stealth = "stealth\\";
vector<string> blew_stealth_check;
const string CONST_BLEW_STEALTH_CHECK_TXT = "blew_stealth_check.txt";
vector<file_and_text_collection> stealth_text_file_collection = {
	customText(&blew_stealth_check, stealth + CONST_BLEW_STEALTH_CHECK_TXT),
};
const string CONST_AND_SHOUTS_FOR_HELP = "and shouts for help!";
const string CONST_AND_LETS_FORTH_A_PIERCING_CONSERVATIVE_ALARM_CRY = "and lets forth a piercing Conservative alarm cry!";
const string CONST_AND_LAUNCHES_INTO_ANGRY_CONSERVATIVE_BARKING = "and launches into angry Conservative barking!";
const string CONST_LOOKS_AT_THE_SQUAD_WITH_INTOLERANCE = " looks at the Squad with Intolerance ";
const string CONST_SEES_THE_SQUAD_S_LIBERAL_WEAPONS = " sees the Squad's Liberal Weapons ";
const string CONST_LOOKS_AT_THE_SQUAD_SUSPICIOUSLY = " looks at the Squad suspiciously.";
const string CONST_SHOUTS_IN_ALARM_AT_THE_SQUAD_S_LIBERAL_TRESPASSING = " shouts in alarm at the squad's Liberal Trespassing!";
const string CONST_ACTS_NATURAL = " acts natural.";
const string CONST_THE_SQUAD = "The squad";
const string CONST_FADES_INTO_THE_SHADOWS = " fades into the shadows.";
const string CONST_HOLSTERED = "holstered";
const string CONST_56_SPACES = "                                                        ";
const string CONST_WE_VE_ALIENATED_ABSOLUTELY_EVERYONE_HERE = "We've alienated absolutely everyone here!               ";
const string CONST_WE_VE_ALIENATED_THE_MASSES_HERE = "We've alienated the masses here!              ";
const string CONST_OBSERVES_YOUR_LIBERAL_ACTIVITY = " observes your Liberal activity ";


// TITLESCREEN

const int REAL_QUOTE_SIZE = 4;
const string pressMtoTurnOffMusic = "Press M to turn off the Music. Press H to view your Liberal High Score.";
const string pressMtoTurnOnMusic = "Press M to turn on some Music. Press H to view your Liberal High Score.";
const string pressToSelectSave = "Press a Letter to Select a Save File";
const string pressToDeleteSave = "Press a Letter to Delete a Save File";
const string vToSwitchXToQuit = ", V to switch, or X to quit";
const string ARE_YOU_SURE_DELETE = "Are you sure you want to delete ";
const string questionYSlashN = "? (y/n)";
const string newGame = "NEW GAME";
const string dotDat = ".dat";
const string deleteSave = "Delete a Save File";
const string CHOOSE_A_SAVE_FILE = "Choose a Save File";
const string titleScreenLine = "컴컴Title컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�";
const string inWhatWorld = "In what world will you pursue your Liberal Agenda?";
const string enterNameForSave = "Enter a name for the save file.";
const string pleaseEnterName = "Please enter a name for the save file.";
const string prettyPlease = "Pretty please enter a name for the save file.";
const string justEnterName = "Just enter a [darn] name for the save file.";
const string inspiredByOubliette = "Inspired by the 1983 version of Oubliette";
const string copyrightTarn = "v3.9 Copyright (C) 2002-4, Tarn Adams";
const string A_BAY_12_GAMES_PRODUCTION = "A Bay 12 Games Production";
const string lcsHyperlink = "http://bay12games.com/lcs/";
const string vChar = "v";
const string maintainedByOpenSource = " Maintained by the Open Source Community";
const string kingDrakeHyperlink = "https://github.com/King-Drake/Liberal-Crime-Squad";
const string lcsForumHyperlink = "http://www.bay12forums.com/smf/index.php?board=3.0";
const string lcsWikiHyperlink = "http://lcs.wikidot.com/";
const string pressESCToQuit = "Press ESC now to quit. Quitting later causes your progress to be saved.";
const string pressAnyKeyToPursue = "Press any other key to pursue your Liberal Agenda!";
const string plusChar = "+";
const string liberalCrimeSquad = "Liberal Crime Squad";
const string titley = "titlescreen\\";

const string CONST_REAL_QUOTE_TXT = "real_quote.txt";
const int SAVE_FILE_NAMELEN = 21;
vector<vector<string> > real_quote;
vector<file_and_text_collection> title_screen_text_files = {
	customText(&real_quote, titley + CONST_REAL_QUOTE_TXT, REAL_QUOTE_SIZE),
};

// SLEEPER_UPDATE

const string they_are_stashed = "They are stashed at the homeless shelter.";
const string hasBeenCaughtSnooping = " has been caught snooping around.";
const string isNowHomeless = "The Liberal is now homeless and jobless...";
const string hasLeakedIntelligence = " has leaked secret intelligence files.";
const string hasLeakedPolice = " has leaked secret police records.";
const string hasLeakedCorporate = " has leaked secret corporate documents.";
const string hasLeakedPrison = " has leaked internal prison records.";
const string hasLeakedCableNews = " has leaked proof of systemic Cable News bias.";
const string hasLeakedAMRadio = " has leaked proof of systemic AM Radio bias.";
const string hasLeakedAnimalResearch = " has leaked internal animal research reports.";
const string hasLeakedJudiciary = " has leaked proof of corruption in the judiciary.";
const string papersAreStashed = "The papers are stashed at the homeless shelter.";
const string hasLeakedCCS = " has leaked a list of the CCS's government backers.";
const string diskIsStashed = "The disk is stashed at the homeless shelter.";
const string HAS_BEEN_ARRESTED_EMBEZZLING = " has been arrested while embezzling funds.";
const string HAS_BEEN_ARRESTED_STEALING = " has been arrested while stealing things.";
const string droppedOffPackage = " has dropped a package off at the homeless shelter.";
const string itemNotFound = "Items not found in XML files led to ";
const string lostStolenItem = " lost stolen items! ";
const string contactModAuthor = "Contact the mod author (or DevTeam if playing the vanilla game) at once!";
const string CONST_CANSEETHINGS = "canseethings";
const string CONST_ABSTRACTED_DEBATE = "abstracted debate";
const string CONST_LIBERAL_POWER = "liberal power";
void printxmlFail(const int numberofxmlfails) {
	set_color_easy(RED_ON_BLUE_BRIGHT);
	mvaddstrAlt(8, 1, itemNotFound, xmllog);
	mvaddstrAlt(9, 1, tostring(numberofxmlfails), xmllog);
	addstrAlt(lostStolenItem, xmllog);
	set_color_easy(RED_ON_GREEN_BRIGHT);
	mvaddstrAlt(11, 1, contactModAuthor, xmllog);
	xmllog.nextMessage();

}
void printSleeperDropOffPackage(const string crname) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(6, 1, string_sleeper, gamelog);
	addstrAlt(crname, gamelog);
	addstrAlt(droppedOffPackage, gamelog);
	gamelog.nextMessage();

}
void printArrestedWhileStealing(const string crname) {
	eraseAlt();
	mvaddstrAlt(6, 1, string_sleeper, gamelog);
	addstrAlt(crname, gamelog);
	addstrAlt(HAS_BEEN_ARRESTED_STEALING, gamelog);
	gamelog.nextMessage();
}
void printArrestedWhileEmbezzling(const string crname) {
	eraseAlt();
	mvaddstrAlt(6, 1, string_sleeper, gamelog);
	addstrAlt(crname, gamelog);
	addstrAlt(HAS_BEEN_ARRESTED_EMBEZZLING, gamelog);
	gamelog.nextMessage();

}
void printHasBeenCaughtSnooping(const string crname) {
	eraseAlt();
	mvaddstrAlt(6, 1, string_sleeper, gamelog);
	addstrAlt(crname, gamelog);
	addstrAlt(hasBeenCaughtSnooping, gamelog);
	gamelog.newline();
	mvaddstrAlt(8, 1, isNowHomeless, gamelog);
	gamelog.nextMessage();

}

void creatureLeaksIntel(const string crname, const string& leak, const string& stashed) {
	eraseAlt();
	mvaddstrAlt(6, 1, string_sleeper, gamelog);
	addstrAlt(crname, gamelog);
	addstrAlt(leak, gamelog);
	gamelog.newline();
	mvaddstrAlt(7, 1, stashed, gamelog);
	gamelog.nextMessage();
}

void printCreatureLeaksIntelligence(const string crname) {
	creatureLeaksIntel(crname, hasLeakedIntelligence, they_are_stashed);

}
void printCreatureLeaksPolice(const string crname) {
	creatureLeaksIntel(crname, hasLeakedPolice, they_are_stashed);

}
void printCreatureLeaksCorp(const string crname) {
	creatureLeaksIntel(crname, hasLeakedCorporate, they_are_stashed);

}
void printCreatureLeaksPrison(const string crname) {
	creatureLeaksIntel(crname, hasLeakedPrison, they_are_stashed);

}
void printCreatureLeaksCable(const string crname) {
	creatureLeaksIntel(crname, hasLeakedCableNews, papersAreStashed);

}
void printCreatureLeaksRadio(const string crname) {
	creatureLeaksIntel(crname, hasLeakedAMRadio, papersAreStashed);

}
void printCreatureLeaksAnimalResearch(const string crname) {
	creatureLeaksIntel(crname, hasLeakedAnimalResearch, they_are_stashed);

}
void printCreatureLeaksJudiciary(const string crname) {
	creatureLeaksIntel(crname, hasLeakedJudiciary, papersAreStashed);

}
void printCreatureLeaksCCS(const string crname) {
	creatureLeaksIntel(crname, hasLeakedCCS, diskIsStashed);

}

//TALK
// TALK

extern short exec[EXECNUM];
extern short siteonfire;
extern Deprecatednewsstoryst *sitestory;
extern string slogan_str;
const int PICKUP_LINE_SIZE = 5;
const int DOUBLE_LINE = 2;
extern Log gamelog;
extern short lawList[LAWNUM];
const string CONST_THE_SQUAD_RELEASES_THE_HOSTAGE_IN_THE_TRADE = "The squad releases the hostage in the trade.";
const string while_naked = " while naked";
const string CONST_A_QUIETLY_PASS_THE_TELLER_A_ROBBERY_NOTE = "A - Quietly pass the teller a robbery note";
const string CONST_B_THREATEN_BYSTANDERS_AND_DEMAND_ACCESS_TO_THE_VAULT = "B - Threaten bystanders and demand access to the vault";
const string CONST_C_ON_SECOND_THOUGHT_DON_T_ROB_THE_BANK = "C - On second thought, don't rob the bank";
const string CONST_SLIPS_THE_TELLER_A_NOTE = " slips the teller a note: ";
const string CONST_THE_BANK_TELLER_READS_THE_NOTE = "The bank teller reads the note, ";
const string CONST_AND_DIVES_FOR_COVER_AS_THE_GUARDS_MOVE_IN_ON_THE_SQUAD = "and dives for cover as the guards move in on the squad!";
const string unnamed_String_Talk_cpp_007 = "The bank teller reads the note, ";
const string CONST_AND_SLIPS_SEVERAL_BRICKS_OF_CASH_INTO_THE_SQUAD_S_BAG = "and slips several bricks of cash into the squad's bag.";
const string CONST_BRANDISHES_THE = " brandishes the ";
const string unnamed_String_Talk_cpp_010 = "\"";
const string CONST_OPEN_THE_VAULT_NOW = "OPEN THE VAULT, NOW!\"";
const string CONST_THE_BANK_TELLER_AND_DIVES_FOR_COVER_AS = "The bank teller and dives for cover as ";
const string CONST_GUARDS_MOVE_IN_ON_THE_SQUAD = "guards move in on the squad!";
const string CONST_THE_BANK_EMPLOYEES_HESITANTLY_COOPERATE = "The bank employees hesitantly cooperate!";
const string CONST_THE_VAULT_IS_OPEN = "The vault is open!";
const string CONST_TALKS_TO = " talks to ";
const string unnamed_String_Talk_cpp_017 = ":";
const string CONST_A_STRIKE_UP_A_CONVERSATION_ABOUT_POLITICS = "A - Strike up a conversation about politics";
const string CONST_B_DROP_A_PICKUP_LINE = "B - Drop a pickup line";
const string CONST_C_ON_SECOND_THOUGHT_DON_T_SAY_ANYTHING = "C - On second thought, don't say anything";
const string CONST_D_RENT_A_ROOM = "D - Rent a room";
const string CONST_D_STOP_RENTING_A_ROOM = "D - Stop renting a room";
const string CONST_D_BUY_WEAPONS = "D - Buy weapons";
const string CONST_D_ROB_THE_BANK = "D - Rob the bank";
const string CONST_I_D_LIKE_CANCEL_MY_ROOM = "\"I'd like cancel my room.\"";
const string CONST_ALRIGHT_PLEASE_CLEAR_OUT_YOUR_ROOM = "\"Alright.Please clear out your room.\"";
const string CONST_YOUR_POSSESSIONS_AT_THIS_LOCATION_HAVE_BEEN_MOVED_TO_THE_SHELTER = "<Your possessions at this location have been moved to the shelter.>";
const string CONST_I_D_LIKE_TO_RENT_A_ROOM = "\"I'd like to rent a room.\"";
const string CONST_PUT_SOME_CLOTHES_ON_BEFORE_I_CALL_THE_COPS = "\"Put some clothes on before I call the cops.\"";
const string CONST_IT_LL_BE = "\"It'll be $";
const string CONST_A_MONTH = " a month.";
const string CONST_I_LL_NEED = "I'll need $";
const string CONST_NOW_AS_A_SECURITY_DEPOSIT = " now as a security deposit.\"";
const string CONST_A_ACCEPT = "A - Accept.";
const string CONST_B_DECLINE = "B - Decline.";
const string CONST_C_THREATEN_THE_LANDLORD = "C - Threaten the landlord.";
const string CONST_I_LL_TAKE_IT = "\"I'll take it.\"";
const string CONST_RENT_IS_DUE_BY_THE_THIRD_OF_EVERY_MONTH = "\"Rent is due by the third of every month.";
const string CONST_WE_LL_START_NEXT_MONTH = "We'll start next month.\"";
const string CONST_TURNS_AWAY = " <turns away>";
const string CONST_WHOA_I_WAS_LOOKING_FOR_SOMETHING_CHEAPER = "\"Whoa, I was looking for something cheaper.\"";
const string CONST_NOT_MY_PROBLEM = "\"Not my problem...\"";
const string unnamed_String_Talk_cpp_044 = " <turns away>";
const string unnamed_String_Talk_cpp_045 = " brandishes the ";
const string CONST_WHAT_S_THE_PRICE_FOR_THE_LIBERAL_CRIME_SQUAD = "\"What's the price for the Liberal Crime Squad?\"";
const string CONST_I_THINK_YOU_D_BETTER_LEAVE = "\"I think you'd better leave.\"";
const string CONST_CROSSES_ARMS = " <crosses arms>";
const string CONST_JESUS_IT_S_YOURS = "\"Jesus... it's yours...\"";
const string CONST_HEY_I_NEED_A_GUN = "\"Hey, I need a gun.\"";
const string CONST_JESUS = "\"Jesus...\"";
const string CONST_I_DON_T_SELL_GUNS_OFFICER = "\"I don't sell guns, officer.\"";
const string CONST_WE_CAN_TALK_WHEN_THINGS_ARE_CALM = "\"We can talk when things are calm.\"";
const string CONST_WHAT_EXACTLY_DO_YOU_NEED = "\"What exactly do you need?\"";
const string CONST_UHHH_NOT_A_GOOD_PLACE_FOR_THIS = "\"Uhhh... not a good place for this.\"";
const string CONST_DO_YOU_WANT_TO_HEAR_SOMETHING_DISTURBING = "\"Do you want to hear something disturbing?\"";
const string CONST_RUMBLES_DISINTERESTEDLY = " rumbles disinterestedly.";
const string CONST_BARKS = " barks.";
const string CONST_DOESN_T_UNDERSTAND = " doesn't understand.";
const string CONST_WHAT = "\"What?\"";
const string CONST_NOW_S_NOT_THE_TIME = "\"Now's not the time!\"";
const string CONST_LEAVE_ME_ALONE = "\"Leave me alone.\"";
const string unnamed_String_Talk_cpp_064 = "\"No.\"";
const string unnamed_String_Talk_cpp_065 = " <turns away>";

const string CONST_SHAKES_ITS_TURRET_A_FIRM_NO = " shakes its turret a firm 'no'.";
const string CONST_DOESN_T_QUITE_PICK_UP_ON_THE_SUBTEXT = " doesn't quite pick up on the subtext.";
const string CONST_DIRTY_YOU_KNOW_THAT_S_ILLEGAL_OFFICER = "\"Dirty.You know that's illegal, officer.\"";
const string unnamed_String_Talk_cpp_069 = " and ";
const string CONST_MAKE_PLANS_FOR_TONIGHT = " make plans for tonight";
const string unnamed_String_Talk_cpp_071 = ", and ";
const string CONST_BREAKS_FOR_THE_EXIT = " breaks for the exit";
const string unnamed_String_Talk_cpp_073 = ". ";
// I'm unhappy with these. If you have a better ideas please submit them.
const string CONST_TOO_LIBERAL_FOR_DEBATE = "You sense that they are already enlightened to the Libreal Agenda. Debating them would just prove a waste of time. ";
const string CONST_TOO_MODERATE_FOR_DEBATE = "You sense that they are a professional fence sitter. Debating them would just prove to be a waste of time.";
const string CONST_TOO_CONSERVATIVE_FOR_DEBATE = "You sense that they are so Conservative they have forgotten that other forms of political thought even exist. Debating them would just prove to be a waste of time."; 
const string CONST_TOO_LIBERAL_FOR_DATE = "You sense that they are already in a wonderful realtionship with their Elite Liberal signifigant other. And you would hate to intrude on that.";
const string CONST_TOO_MODERATE_FOR_DATE = "You sense that it would take them hours to decide if they would like to date you or not. And you would hate to wait on that";
const string CONST_TOO_CONSERVATIVE_FOR_DATE = "You notice a wedding ring on their finger. And you would hate to deal with that.";
const string WONT_DATE_LIBERAL = "\"Sorry, I've already got plans to help out at the retirement home.\"";
const string WONT_DATE_MODERATE = "\"Sorry, I've already got plans to go vote for a third party.\"";
const string WONT_DATE_CONSERVATIVE = "\"Sorry, I've already got plans to help out at chruch.\"";
const string CONST_I_M_A_HAPPILY_MARRIED_MAN_SWEETIE = "\"I'm a happily married man, sweetie.\"";
const string CONST_THIS_AIN_T_BROKEBACK_MOUNTAIN_SON = "\"This ain't Brokeback Mountain, son.\"";
const string CONST_THE_POLICE_ARE_NOT_DOING_THEIR_JOB_VERY_WELL = "\"[The police are not doing their job very well!]\"";
const string CONST_THE_COPS_SUCK = "\"The cops suck!\"";
const string CONST_INDUSTRIES_THAT_STOP_AT_NOTHING_TO_BECOME_MORE_PROFITABLE_ARE_POLLUTING = "\"Industries that stop at nothing to become more profitable are polluting ";
const string CONST_THE_ENVIRONMENT_IN_WAYS_THAT_HURT_NOT_ONLY_HUMANS_BUT_ANIMALS_TOO = "the environment in ways that hurt not only humans, but animals too.";
const string CONST_THE_ENVIRONMENT_IN_WAYS_THAT_HURT_NOT_ONLY_ANIMALS_BUT_PEOPLE_TOO = "the environment in ways that hurt not only animals, but people too.";
const string CONST_AAAAHHH = "\"Aaaahhh...\"";
const string CONST_OH_REALLY = "\"Oh, really?\"";
const string CONST_YEAH_REALLY = "\"Yeah, really!\"";
const string CONST_YOU_GOT_ANYTHING_TO_SMOKE_ON_YOU = "\"You got anything to smoke on you?\"";
const string CONST_COUGH = "*cough*";
const string CONST_AFTER_MORE_DISCUSSION = "After more discussion, ";
const string CONST_AGREES_TO_COME_BY_LATER_TONIGHT = " agrees to come by later tonight.";
const string CONST_UGH_PFFT = "\"Ugh.Pfft.\"";
const string CONST_DO_YOU_WANT_ME_TO_ARREST_YOU = "\"Do you want me to arrest you?\"";
const string CONST_IF_YOU_DON_T_SHUT_UP_I_M_GOING_TO_SHOOT_YOU = "\"If you don't shut up, I'm going to shoot you.\"";
const string CONST_WHATEVER = "\"Whatever.\"";
const string unnamed_String_Talk_cpp_093 = " <turns away>";
const string CONST_BLAM = "BLAM!";
const string CONST_CRUNCH = "CRUNCH!";
const string unnamed_String_Talk_cpp_115 = " drops ";
const string unnamed_String_Talk_cpp_116 = "'s body.";
const string CONST_FUCK = "\"Fuck!";
const string unnamed_String_Talk_cpp_118 = "\"[No!] ";
const string CONST_BACK_OFF_AND_WE_LL_LET_THE_HOSTAGES_GO = "\"Back off and we'll let the hostages go.\"";
const string CONST_BACK_OFF_AND_THE_HOSTAGE_GOES_FREE = "\"Back off and the hostage goes free.\"";
const string CONST_THE_SQUAD_RELEASES_ALL_HOSTAGES_IN_THE_TRADE = "The squad releases all hostages in the trade.";
const string CONST_DON_T_PUSH_THE_LCS = "\"Don't push the LCS!\"";
const string CONST_DON_T_PLAY_WITH_ME = "\"Don't [play] with me!\"";
const string CONST_DON_T_FUCK_WITH_ME = "\"Don't fuck with me!\"";
const string CONST_RELEASE_YOUR_HOSTAGES_AND_NOBODY_GETS_HURT = "\"Release your hostages, and nobody gets hurt.\"";
const string CONST_LET_THE_HOSTAGE_GO_AND_NOBODY_GETS_HURT = "\"Let the hostage go, and nobody gets hurt.\"";
const string CONST_THE_PLOY_WORKS_THE_CONSERVATIVES_BACK_OFF = "The ploy works! The Conservatives back off.";
const string unnamed_String_Talk_cpp_106 = "How should ";
const string CONST_RESPOND = " respond?";
const string CONST_A_EXECUTE_A_HOSTAGE = "A - Execute a hostage";
const string CONST_A_EXECUTE_THE_HOSTAGE = "A - Execute the hostage";
const string CONST_B_OFFER_TO_TRADE_THE_HOSTAGES_FOR_FREEDOM = "B - Offer to trade the hostages for freedom";
const string CONST_B_OFFER_TO_TRADE_THE_HOSTAGE_FOR_FREEDOM = "B - Offer to trade the hostage for freedom";
const string CONST_C_NO_REPLY = "C - No reply";

const string CONST_ISN_T_INTERESTED_IN_YOUR_PATHETIC_THREATS = " isn't interested in your pathetic threats.";
const string CONST_PRETENDS_TO_BE_PART_OF_A_POLICE_RAID = "pretends to be part of a police raid.";
const string CONST_PRETENDS_TO_BE_A_SECRET_AGENT = "pretends to be a Secret Agent.";
const string CONST_PRETENDS_TO_BE_MOUNTAIN = "pretends to be Mountain ";
const string CONST_LIKE_PATRICK_SWAYZE_IN_NEXT_OF_KIN = "like Patrick Swayze in Next of Kin.";
const string CONST_SQUEALS_LIKE_NED_BEATTY = "squeals like Ned Beatty ";
const string CONST_IN_DELIVERANCE = "in Deliverance.";
const string CONST_PRETENDS_TO_BE_A_MERCENARY = "pretends to be a mercenary.";
const string CONST_LIGHTS_A_MATCH_AND_THROWS_IT_ON_THE_GROUND = "lights a match and throws it on the ground. ";
const string CONST_THE_CARPET_SMOLDERS_THEN_BURSTS_INTO_FLAME = "The carpet smolders, then bursts into flame.";
const string CONST_PERHAPS_THAT_WAS_A_BAD_IDEA = "Perhaps that was a bad idea...";
const string CONST_THE_SITUATION_IS_UNDER_CONTROL = "\"The situation is under control.\"";
const string CONST_FIRE_EVACUATE_IMMEDIATELY = "\"Fire!Evacuate immediately!\"";
const string CONST_EVERYTHING_S_IN_CHECK = "\"Everything's in check.\"";
const string CONST_MAKE_WAY_I_M_A_DOCTOR = "\"Make way, I'm a doctor!\"";
const string CONST_NON_TARGETS_PLEASE_LEAVE_THE_SITE = "\"Non - targets please leave the site.\"";
const string CONST_ENGRAVES = " engraves ";
const string CONST_ELBERETH = "Elbereth";
const string CONST_ON_THE_FLOOR = " on the floor.";
const string CONST_TALKS_LIKE_A_CONSERVATIVE = " talks like a Conservative ";
const string CONST_AND_PRETENDS_TO_BELONG_HERE = "and pretends to belong here.";
const string unnamed_String_Talk_cpp_144 = "But ";
const string CONST_WEREN_T_BORN_YESTERDAY = " weren't born yesterday.";
const string CONST_IS_NOT_FOOLED_BY_THAT_ACT = " is not fooled by that [act].";
const string CONST_IS_NOT_FOOLED_BY_THAT_CRAP = " is not fooled by that crap.";
const string CONST_THE_ENEMY_IS_FOOLED_AND_DEPARTS = "The Enemy is fooled and departs.";
const string CONST_THE_SQUAD_IS_ARRESTED = "The Squad is arrested.";
const string unnamed_String_Talk_cpp_094 = " talks to ";
const string unnamed_String_Talk_cpp_095 = ":";
const string CONST_A_INTIMIDATE = "A - Intimidate";
const string CONST_B_THREATEN_HOSTAGES = "B - Threaten hostages";
const string CONST_C_BLUFF = "C - Bluff";
const string CONST_D_SURRENDER_TO_AUTHORITIES = "D - Surrender to authorities";
const string respondsComma = " responds, ";
const string saysComma = " says, ";
const string CONST_AGREE_TO_RELEASE_HOSTAGES_TXT = "agree_to_release_hostages.txt";
const string CONST_GO_AHEAD_AND_DIE_TXT = "go_ahead_and_die.txt";
const string CONST_LET_HOSTAGES_GO_TXT = "let_hostages_go.txt";
const string CONST_PLEASE_NO_MORE_TXT = "please_no_more.txt";
const string CONST_HOSTAGE_NEGOTIATION_TXT = "hostage_negotiation.txt";
const string CONST_WHO_CARES_ABOUT_HOSTAGE_TXT = "who_cares_about_hostage.txt";
const string CONST_PLEASE_SPARE_HOSTAGE_TXT = "please_spare_hostage.txt";
const string CONST_THREATEN_HOSTAGE_TXT = "threaten_hostage.txt";
const string CONST_BACKS_OFF_TXT = "backs_off.txt";
const string CONST_COME_AT_ME_BRO_TXT = "come_at_me_bro.txt";
const string CONST_TELLER_COMPLIES_TXT = "teller_complies.txt";
const string CONST_TELLER_GESTURES_TXT = "teller_gestures.txt";
const string CONST_ROBBING_BANK_TXT = "robbing_bank.txt";
const string CONST_THAT_IS_NOT_DISTURBING_TXT = "that_is_not_disturbing.txt";
const string CONST_THAT_IS_DISTURBING_TXT = "that_is_disturbing.txt";
const string CONST_MUTANT_REJECTION_TXT = "mutant_rejection.txt";
const string CONST_DOG_REJECTION_TXT = "dog_rejection.txt";
const string CONST_NORMAL_TALK_TO_DOG_TXT = "normal_talk_to_dog.txt";
const string CONST_LOVINGLY_TALK_TO_DOG_TXT = "lovingly_talk_to_dog.txt";
const string CONST_NORMAL_TALK_TO_MUTANT_TXT = "normal_talk_to_mutant.txt";
const string CONST_LOVINGLY_TALK_TO_MUTANT_TXT = "lovingly_talk_to_mutant.txt";
const string CONST_PICKUPLINES_TXT = "pickupLines.txt";
const string CONST_NO_FREE_SPEECH_FLIRT_TXT = "no_free_speech_flirt.txt";

const string talky = "talk\\";
const string talk_combat = "talk_combat\\";
const string unnamed_String_Talk_cpp_081 = "Prisoner";
extern vector<vector<string> > no_free_speech_flirt;
extern vector<vector<string> > pickupLines;
extern vector<vector<string> > lovingly_talk_to_mutant;
extern vector<vector<string> > normal_talk_to_mutant;
extern vector<vector<string> > lovingly_talk_to_dog;
extern vector<vector<string> > normal_talk_to_dog;

vector<string> dog_rejection;
vector<string> mutant_rejection;
vector<string> that_is_disturbing;
vector<string> that_is_not_disturbing;
vector<string> robbing_bank;
vector<string> teller_gestures;
vector<string> teller_complies;
//const int DOUBLE_LINE = 2;
vector<string> come_at_me_bro;
vector<string> backs_off;
vector<string> threaten_hostage;
vector<string> please_spare_hostage;
vector<string> who_cares_about_hostage;
vector<string> hostage_negotiation;
vector<string> please_no_more;
vector<string> let_hostages_go;
vector<string> go_ahead_and_die;
vector<string> agree_to_release_hostages;
vector<file_and_text_collection> talk_file_collection = {
	/*talk.cpp*/
	customText(&no_free_speech_flirt, talky + CONST_NO_FREE_SPEECH_FLIRT_TXT, PICKUP_LINE_SIZE),
	customText(&pickupLines, talky + CONST_PICKUPLINES_TXT, PICKUP_LINE_SIZE),
	customText(&lovingly_talk_to_mutant, talky + CONST_LOVINGLY_TALK_TO_MUTANT_TXT, DOUBLE_LINE),
	customText(&normal_talk_to_mutant, talky + CONST_NORMAL_TALK_TO_MUTANT_TXT, DOUBLE_LINE),
	customText(&lovingly_talk_to_dog, talky + CONST_LOVINGLY_TALK_TO_DOG_TXT, DOUBLE_LINE),
	customText(&normal_talk_to_dog, talky + CONST_NORMAL_TALK_TO_DOG_TXT, DOUBLE_LINE),
	customText(&dog_rejection, talky + CONST_DOG_REJECTION_TXT),
	customText(&mutant_rejection, talky + CONST_MUTANT_REJECTION_TXT),
	customText(&that_is_disturbing, talky + CONST_THAT_IS_DISTURBING_TXT),
	customText(&that_is_not_disturbing, talky + CONST_THAT_IS_NOT_DISTURBING_TXT),
	customText(&robbing_bank, talky + CONST_ROBBING_BANK_TXT),
	customText(&teller_gestures, talky + CONST_TELLER_GESTURES_TXT),
	customText(&teller_complies, talky + CONST_TELLER_COMPLIES_TXT),
	//talk in combat
	customText(&come_at_me_bro, talk_combat + CONST_COME_AT_ME_BRO_TXT),
	customText(&backs_off, talk_combat + CONST_BACKS_OFF_TXT),
	customText(&threaten_hostage, talk_combat + CONST_THREATEN_HOSTAGE_TXT),
	customText(&please_spare_hostage, talk_combat + CONST_PLEASE_SPARE_HOSTAGE_TXT),
	customText(&who_cares_about_hostage, talk_combat + CONST_WHO_CARES_ABOUT_HOSTAGE_TXT),
	customText(&hostage_negotiation, talk_combat + CONST_HOSTAGE_NEGOTIATION_TXT),
	customText(&please_no_more, talk_combat + CONST_PLEASE_NO_MORE_TXT),
	customText(&let_hostages_go, talk_combat + CONST_LET_HOSTAGES_GO_TXT),
	customText(&go_ahead_and_die, talk_combat + CONST_GO_AHEAD_AND_DIE_TXT),
	customText(&agree_to_release_hostages, talk_combat + CONST_AGREE_TO_RELEASE_HOSTAGES_TXT),
};
//string while_naked;
map<short, string> conservativeLegalArgument;
map<short, vector<string> > talkAboutTheIssues;
map<short, string> youAreStupidTalkAboutIssues;
map<short, string> issueTooLiberal;


short interface_pgup = '[';
short interface_pgdn = ']';
bool is_page_up(const int c) {
	return c == interface_pgup || c == KEY_UP || c == KEY_LEFT;
}
bool is_page_down(const int c) {
	return c == interface_pgdn || c == KEY_DOWN || c == KEY_RIGHT;
}
inline int translateGraphicsChar(unsigned char c) { return c; }
inline short translateGraphicsColor(short c) { return c; }
/* Variants of addch and mvaddch that work on chars and use translateGraphicsChar(), fixing display of extended characters */
inline int addchar(char ch) { return addch(translateGraphicsChar(ch)); }
inline int mvaddchar(int y, int x, char ch) { return mvaddch(y, x, translateGraphicsChar(ch)); }
inline int addchar(char ch, Log &log) { log.record(ch); return addchar(ch); }
inline int mvaddchar(int y, int x, char ch, Log &log) { log.record(ch); return mvaddchar(y, x, ch); }
/* Redefining addstr() and mvaddstr() so they use addchar() and mvaddchar(), fixing display of extended characters */
#undef addstr
inline int addstr(const char* text) { int ret = ERR; for (int i = 0; i < len(text); i++) ret = addchar(text[i]); return ret; }
#undef mvaddstr
inline int mvaddstr(int y, int x, const char* text) { int ret = move(y, x); if (ret != ERR) ret = addstr(text); return ret; }
/* Various wrappers to addstr() and mvaddstr() which handle permutations of:
- Including or not including the gamelog for external message logging
- std::string or c-style char arrays */
inline int addstr(const char *text, Log &log) { log.record(text); return addstr(text); }
inline int mvaddstr(int y, int x, const char *text, Log &log) { log.record(text); return mvaddstr(y, x, text); }
inline int addstr(const std::string& text) { int ret = ERR; for (int i = 0; i < len(text); i++) ret = addchar(text[i]); return ret; }
inline int addstr(const std::string& text, Log &log) { log.record(text); return addstr(text); }
inline int mvaddstr(int y, int x, const std::string& text) { int ret = move(y, x); if (ret != ERR) ret = addstr(text); return ret; }
inline int mvaddstr(int y, int x, const std::string& text, Log &log) { log.record(text); return mvaddstr(y, x, text); }
/* These wrappers convert numbers to text */
inline int addstr(long num) { return addstr(tostring(num)); }
inline int addstr(long num, Log &log) { return addstr(tostring(num), log); }
inline int mvaddstr(int y, int x, long num) { return mvaddstr(y, x, tostring(num)); }
inline int mvaddstr(int y, int x, long num, Log &log) { return mvaddstr(y, x, tostring(num), log); }
void pressAnyKey() {
	getkeyAlt();
}
void    PDC_set_titleAlt(const char *ch) {
	PDC_set_title(ch);
}
int endwinAlt() {
	return endwin();
}
int     addchAlt(const int ch) {
	return addch(ch);
}
int addcharAlt(const char ch) {
	return addch(translateGraphicsChar(ch));
}
int addcharAlt(const char ch, Log &log) {
	log.record(ch); return addcharAlt(ch);
}
int mvaddcharAlt(int y, int x, char ch) { return mvaddch(y, x, translateGraphicsChar(ch)); }
int mvaddcharAlt(int y, int x, char ch, Log &log) { log.record(ch); return mvaddcharAlt(y, x, ch); }
int eraseAlt(void) {
	return erase();
}
void strcat(char* c, string s) {
	strcat(c, s.data());
}
void strcpy(char* c, string s) {
	strcpy(c, s.data());
}
int     mvaddchAlt(int x, int y, const int ch) {
	return mvaddch(x, y, ch);
}
int     mvgetnstrAlt(int x, int y, char *ch, int z) {
	return mvgetnstr(x, y, ch, z);
}
int moveAlt(const int x, const int y) { return move(x, y); }
int	mvaddstrAlt(const int x, const int y, const string z) { return mvaddstr(x, y, z.data()); }
int	mvaddstrAlt(const int x, const int y, const char* z) { return mvaddstr(x, y, z); }
//int		mvaddstrAlt(const int x, const int y, const char* z) { return mvaddstr(x, y, z); }
//int addstrAlt(const char* x, Log y) { return addstr(x,y); }
//int addstrAlt(const string x) { return addstr(x); }
int addstrAlt(const char *text) { return addstr(text); }
int addstrAlt(const char *text, Log &log) { log.record(text); return addstr(text); }
int addstrAlt(const string &text) { int ret = ERR; for (int i = 0; i < strlen(text.data()); i++) ret = addcharAlt(text[i]); return ret; }
int addstrAlt(const string &text, Log &log) { log.record(text); return addstr(text.data()); }
int addstrAlt(const long num) { return addstr(tostring(num).data()); }
int addstrAlt(const long num, Log &log) { return addstrAlt(tostring(num).data(), log); }
int	mvaddstrAlt(const int x, const  int y, const int z) { return mvaddstr(x, y, tostring(z).data()); }
int	mvaddstrAlt(const int x, const int y, const string z, Log &a) {
	a.record(z);
	return mvaddstr(x, y, z.data());
}
int		 mvaddstrAlt(const int x, const int y, const char* z, Log &a) {
	a.record(z);
	return mvaddstr(x, y, z);
}
int		 mvaddstrAlt(const int x, const int y, const  int z, Log &a) {
	a.record(tostring(z));
	return mvaddstr(x, y, tostring(z).data());
}
int		mvaddstr_const(const MOVE_CONSTANT movement, const char *string) {
	return mvaddstrAlt(movement.y, movement.x, string);
}
int move_const(const MOVE_CONSTANT movement) {
	return moveAlt(movement.y, movement.x);
}
int center_string(const char* str);
int center_string(const char* str) {
	return 39 - ((strlen(str) - 1) >> 1);
}
int move_center_string(const int x, const char* str) {
	str;
	return mvaddstrAlt(x, center_string(str), str);
}
void set_color_easy(const ColorSetup color) {
	set_color(color.letter, color.background, color.bright, color.blink);
}
string burstToString(const int bursthits) {
	switch (bursthits) {
	case 2: return CONST_TWICE;
	case 3: return CONST_THREE_TIMES;
	case 4: return CONST_FOUR_TIMES;
	case 5: return  CONST_FIVE_TIMES;
	default: return singleSpace + tostring(bursthits) + CONST_S_TIMES;
	}
}
string qualifiedFailure(const int droll, const string name, vector<string> stringCollection) {
	return name + qualifiedFailure(droll, stringCollection);
}
string qualifiedFailure(const int droll, vector<string> stringCollection) {
	if (stringCollection.size() == 0) {
		return "";
	}
	if (droll < stringCollection.size() && droll >= 0) {
		return stringCollection[droll];
	}
	else {
		return stringCollection[0];
	}
}
int     clearAlt(void) {
	return clear();
}
int     refreshAlt(void) {
	return refresh();
}
void displayDifficulty(int difficulty)
{
	switch (difficulty)
	{
	case 0:	set_color_easy(GREEN_ON_BLACK_BRIGHT); break;
	case 1: set_color_easy(CYAN_ON_BLACK_BRIGHT); break;
	case 2: set_color_easy(CYAN_ON_BLACK); break;
	case 3: set_color_easy(BLUE_ON_BLACK_BRIGHT); break;
	case 4: set_color_easy(WHITE_ON_BLACK_BRIGHT); break;
	case 5: set_color_easy(WHITE_ON_BLACK); break;
	case 6: set_color_easy(YELLOW_ON_BLACK_BRIGHT); break;
	case 7: set_color_easy(MAGENTA_ON_BLACK); break;
	case 8: set_color_easy(MAGENTA_ON_BLACK_BRIGHT); break;
	case 9: set_color_easy(RED_ON_BLACK);	break;
	default:set_color_easy(RED_ON_BLACK_BRIGHT);	break;
	}
	if (difficulty >= 0 && difficulty < 10) addstrAlt(_difficulty[difficulty]); else addstrAlt(_difficulty[10]);
}
// IsaacG Various functions that are the single time
// a given aspect of the curses library is used
/*
This function prints the cash the player has with optional prefix as
well as screen coordinates.
Please note that offsetx is the offset from the right of the screen, y is
the offset from the top as always.
*//*
This function prints the cash the player has with optional prefix as
well as screen coordinates.
Please note that offsetx is the offset from the right of the screen, y is
the offset from the top as always.
*/
void printfunds(int y, int offsetx, const char* prefix, long funds)
{
	char moneystr[50], prefixbuffer[50];
	if (prefix == NULL)
		strncpy(prefixbuffer, "", 50);
	else strncpy(prefixbuffer, prefix, 50);
	strcpy(moneystr, tostring(funds).data());
	//Save screen coordinates for later.
	int begy, begx;
	getyx(stdscr, begy, begx);
	//Save color and brightness information for later.
	short colorpair, front, back;
	attr_t attrs;
	attr_get(&attrs, &colorpair, NULL);
	bool dim = (attrs & WA_DIM) != 0;
	pair_content(colorpair, &front, &back);
	//Move, set color, and write.
	mvaddstrAlt(y, 80 - strlen(moneystr) - strlen(prefixbuffer) - offsetx, prefixbuffer);
	addstrAlt(moneystr);
	//Recover old settings
	set_color(front, back, dim);
	moveAlt(begy, begx);
}
int mvaddstrCenter(int i, string str) {
	int x = 39 - ((len(str) - 1) >> 1);
	if (x < 0) x = 0;
	return mvaddstrAlt(i, x, str);
}
int mvaddstrCenter(int i, string str, Log &log) {
	int x = 39 - ((len(str) - 1) >> 1);
	if (x < 0) x = 0;
	return mvaddstrAlt(i, x, str, log);
}
void noechoAlt() {
	noecho();
}
//initialize curses color
void start_colorAlt() {
	start_color();
}
void curs_setAlt(int i) {
	curs_set(i);
}
//begin the game loop
void keypadAlt(bool i) {
	keypad(stdscr, i);
}
void raw_outputAlt(bool i) {
	raw_output(i);
}
void init_pairAlt(short x, short y, short z) {
	init_pair(x, y, z);
}
void initscrAlt() {
	initscr();
}
void set_colorAlt(short f, short b, bool bright, bool blink) {
	set_color(f, b, bright, blink);
}
int checkkeyAlt() {
	return checkkey();
}
void echoAlt() {
	echo();
}

//void outputPortraitFile();
int getkeyAlt() {
	//outputPortraitFile();
	return getkey();
}
/* Allow the player to enter a name with an optional default */
void enter_name(int y, int x, char *name, int len, const char* defname)
{
	refreshAlt();
	keypadAlt(FALSE);
	raw_outputAlt(FALSE);
	echoAlt();
	curs_setAlt(1);
	mvgetnstrAlt(y, x, name, len - 1); //-1 because 'len' is normally the full space available and we need one for a terminator.
	curs_setAlt(0);
	noechoAlt();
	raw_outputAlt(TRUE);
	keypadAlt(TRUE);
	if ((defname != NULL) && (strncmp(name, "", len - 1) == 0)) strncpy(name, defname, len - 1);
	name[len - 1] = '\0';
}

// Removed from consolesupport.cpp
// These 4 variables to keep track of the current color are for
// this file only
short curForeground = COLOR_WHITE, curBackground = COLOR_BLACK;
bool isBright = false, isBlinking = false;
//sets current color to desired setting
void set_color(short f, short b, bool bright, bool blink)
{
	// keep track of current color
	curForeground = f, curBackground = b, isBright = bright, isBlinking = blink;
	//color swap required for PDcurses
	if (f == 7 && b == 0) f = 0, b = 0;
	else if (f == 0 && b == 0) f = 7, b = 0;
	chtype blinky = (blink ? A_BLINK : 0), brighty = (bright ? A_BOLD : 0);
	//pick color pair based on foreground and background
	attrset(brighty | blinky | COLOR_PAIR(f * 8 + b));
}
/* Refreshes the screen, empties the keyboard buffer, waits for a new key to be pressed, and returns the key pressed */
int getkey()
{
	refresh();
	nodelay(stdscr, TRUE);
	while (getch() != ERR);
	nodelay(stdscr, FALSE);
	int c = getch();
	translategetch(c);
	return c;
}

/* Variant of getkey() that doesn't make all letters lowercase */
int getkey_cap()
{
	refresh();
	nodelay(stdscr, TRUE);
	while (getch() != ERR);
	nodelay(stdscr, FALSE);
	int c = getch();
	translategetch_cap(c);
	return c;
}
int getkey_cap_alt() {
	return getkey_cap();
}
/* Empties the keyboard buffer, and returns most recent key pressed, if any */
int checkkey()
{
	int c = ERR, ret = ERR;
	nodelay(stdscr, TRUE);
	do
	{
		ret = c;
		c = getch();
		translategetch(c);
	} while (c != ERR);
	nodelay(stdscr, FALSE);
	return ret;
}
/* Variant of checkkey() that doesn't make all letters lowercase */
// UNUSED
int checkkey_cap()
{
	int c = ERR, ret = ERR;
	nodelay(stdscr, TRUE);
	do
	{
		ret = c;
		c = getch();
		translategetch_cap(c);
	} while (c != ERR);
	nodelay(stdscr, FALSE);
	return ret;
}
/*
This function prints the cash the player has with optional prefix as
well as screen coordinates.
Please note that offsetx is the offset from the right of the screen, y is
the offset from the top as always.
*/
void printfunds(int y, int offsetx, const char* prefix)
{
	printfunds(y, offsetx, prefix, ledger.get_funds());
}

int pressSpecificKey(const int x, const int y) {
	int c;
	do {
		c = getkeyAlt();

	} while (c != x && c != y);

	return c;
}
void pressSpecificKey(const int x, const int y, const int z, const int w) {
	int c;
	do {
		c = getkeyAlt();

	} while (c != x && c != y && c != z && c != w);
}
int pressSpecificKey(const int x, const int y, const int z, const int w, const int u) {
	int c;
	do {
		c = getkeyAlt();

	} while (c != x && c != y && c != z && c != w && c != u);
	return c;
}
int pressSpecificKey(const int x, const int y, const int z) {
	int c;
	do {
		c = getkeyAlt();

	} while (c != x && c != y && c != z);
	return c;
}
// prints a formatted name, used by promoteliberals
void printname(const int hiding, const int location, const int flag, const string name) {
	int bracketcolor = -1, namecolor, brightness;
	if (hiding)
		bracketcolor = COLOR_BLACK;
	// Determine bracket color, if any, based on location
	if (location != -1)
	{
		switch (LocationsPool::getInstance().getLocationType(location))
		{
		case SITE_GOVERNMENT_POLICESTATION:
		case SITE_GOVERNMENT_COURTHOUSE:
			if (!(flag & CREATUREFLAG_SLEEPER))
				bracketcolor = COLOR_YELLOW;
			break;
		case SITE_GOVERNMENT_PRISON:
			if (!(flag & CREATUREFLAG_SLEEPER))
				bracketcolor = COLOR_RED;
			break;
		default:
			break;
		}
	}
	// Determine name color, based on recruitment style
	if (flag & CREATUREFLAG_LOVESLAVE)
		namecolor = COLOR_MAGENTA;
	else if (flag & CREATUREFLAG_BRAINWASHED)
		namecolor = COLOR_YELLOW;
	else namecolor = COLOR_WHITE;
	// Determine name brightness, based on subordinates left
	/*if(subordinatesleft(cr))
	brightness=1;
	else*/
	brightness = 0;
	// add bracket (if used)
	if (bracketcolor != -1)
	{
		set_color(bracketcolor, COLOR_BLACK, 1);
		addstrAlt(CONST_OPEN_BRACKET);
	}
	if (flag & CREATUREFLAG_SLEEPER)
	{
		set_color_easy(BLUE_ON_BLACK_BRIGHT);
		addstrAlt(CONST_OPEN_BRACKET);
	}
	// add name
	set_color(namecolor, COLOR_BLACK, brightness);
	addstrAlt(name);
	// add close bracket (if used)
	if (flag & CREATUREFLAG_SLEEPER)
	{
		set_color_easy(BLUE_ON_BLACK_BRIGHT);
		addstrAlt(CONST_CLOSE_BRACKET);
	}
	if (bracketcolor != -1)
	{
		set_color(bracketcolor, COLOR_BLACK, 1);
		addstrAlt(CONST_CLOSE_BRACKET);
	}
	set_color_easy(WHITE_ON_BLACK);
}

#ifndef DIFF
// difference between 2 numbers (absolute value of subtracting one from the other)
#define DIFF(x,y) ((x)<(y)?((y)-(x)):((x)-(y)))
#endif
// Imperfect but quick and dirty line of sight check
// Only works if the target point is at most two spaces
// away in any direction
bool LineOfSight(int x, int y, int z)
{
	if (levelmap[x][y][z].flag&SITEBLOCK_KNOWN) return true; // already explored
	if (DIFF(x, loc_coord.locx) > 2 || DIFF(y, loc_coord.locy) > 2) return false; // too far away
	if (DIFF(x, loc_coord.locx) <= 1 && DIFF(y, loc_coord.locy) <= 1) return true; // right next to us or right where we're standing
	int x1, x2, y1, y2;
	if (DIFF(x, loc_coord.locx) == 1) x1 = loc_coord.locx, x2 = x;
	else x1 = x2 = (x + loc_coord.locx) / 2; // difference is either 0 or 2
	if (DIFF(y, loc_coord.locy) == 1) y1 = loc_coord.locy, y2 = y;
	else y1 = y2 = (y + loc_coord.locy) / 2; // difference is either 0 or 2
											 // Check for obstructions
	if ((levelmap[x1][y2][z].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT)) &&
		(levelmap[x2][y1][z].flag&(SITEBLOCK_BLOCK | SITEBLOCK_DOOR | SITEBLOCK_EXIT)))
		return false; // Blocked on some axis
	return true;
}
/* prints the names of creatures you see */
void printencounter()
{
	set_color_easy(WHITE_ON_BLACK);
	for (int i = 19; i <= 24; i++)
		mvaddstrAlt(i, 0, CONST_53_SPACES); // 53 spaces
	int px = 1, py = 19;
	for (NameAndAlignment n : getEncounterNameAndAlignment()) {

		if (n.exists)
		{
			if (!n.alive) set_color_easy(BLACK_ON_BLACK_BRIGHT);
			else if (n.align == 0) set_color_easy(WHITE_ON_BLACK_BRIGHT);
			else if (n.align == 1) set_color_easy(GREEN_ON_BLACK_BRIGHT);
			else set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(py, px, n.name);
		}
		px += 18;
		if (px > 37) px = 1, py++;
	}
}
void checkForDirectionalVisibility(bool(&visible)[8], const int x, const int y) {

	if (x > loc_coord.locx && x < MAPX) visible[WALL_LEFT] = true;
	if (x > 0 && x < loc_coord.locx) visible[WALL_RIGHT] = true;
	if (y > loc_coord.locy && y < MAPY) visible[WALL_UP] = true;
	if (y > 0 && y < loc_coord.locy) visible[WALL_DOWN] = true;
	if (y > loc_coord.locy && y<MAPY && x>loc_coord.locx && x < MAPX) visible[CORNER_UL] = true;
	if (y > loc_coord.locy && y < MAPY && x>0 && x < loc_coord.locx) visible[CORNER_UR] = true;
	if (y > 0 && y<loc_coord.locy && x>loc_coord.locx && x < MAPX) visible[CORNER_DL] = true;
	if (y > 0 && y < loc_coord.locy && x>0 && x < loc_coord.locx) visible[CORNER_DR] = true;
}
void checkForLOS(bool(&visible)[8], const int x, const int y, const int z) {


	if (!LineOfSight(x - 1, y, z)) visible[WALL_LEFT] = false;
	if (!LineOfSight(x + 1, y, z)) visible[WALL_RIGHT] = false;
	if (!LineOfSight(x, y - 1, z)) visible[WALL_UP] = false;
	if (!LineOfSight(x, y + 1, z)) visible[WALL_DOWN] = false;
	if (!LineOfSight(x - 1, y - 1, z)) visible[CORNER_UL] = false;
	if (!LineOfSight(x + 1, y - 1, z)) visible[CORNER_UR] = false;
	if (!LineOfSight(x - 1, y + 1, z)) visible[CORNER_DL] = false;
	if (!LineOfSight(x + 1, y + 1, z)) visible[CORNER_DR] = false;
}

int getSiteFlagForWall(const int x, const int y, const int z, const wallDirection wall) {


	switch (wall) {
	case WALL_UP:
		return levelmap[x][y - 1][z].flag;
		break;
	case WALL_DOWN:
		return levelmap[x][y + 1][z].flag;
		break;
	case WALL_LEFT:
		return levelmap[x - 1][y][z].flag;
		break;
	case WALL_RIGHT:
		return levelmap[x + 1][y][z].flag;
		break;
	case CORNER_UL:
		return levelmap[x - 1][y - 1][z].flag;
		break;
	case CORNER_UR:
		return levelmap[x + 1][y - 1][z].flag;
		break;
	case CORNER_DL:
		return levelmap[x - 1][y + 1][z].flag;
		break;
	case CORNER_DR:
		return levelmap[x + 1][y + 1][z].flag;
		break;
	}
	// ERROR
	return -1;
}
void checkForWallStatus(bool(&visible)[8], const int x, const int y, const int z, const int siteflag, const bool newstate) {
	for (int i = WALL_UP; i <= CORNER_DR; i++) {
		if (getSiteFlagForWall(x, y, z, (wallDirection)i) & siteflag) {
			visible[i] = newstate;
		}
	}
}

void checkForMemory(bool(&visible)[8], const int x, const int y, const int z) {
	checkForWallStatus(visible, x, y, z, (SITEBLOCK_KNOWN), true);
}
void checkForBlockage(bool(&visible)[8], const int x, const int y, const int z) {
	checkForWallStatus(visible, x, y, z, (SITEBLOCK_BLOCK | SITEBLOCK_DOOR), false);
}
void checkForBloodyWalls(bool(&bloody)[8], const int x, const int y, const int z) {
	checkForWallStatus(bloody, x, y, z, SITEBLOCK_BLOODY2, true);
}

void checkForOtherGraffiti(char(&graffiti)[4][4], char(&graffiticolor)[4], const int x, const int y, const int z) {
	for (int i = WALL_UP; i <= WALL_RIGHT; i++) {
		if (getSiteFlagForWall(x, y, z, (wallDirection)i) & SITEBLOCK_GRAFFITI_OTHER) {
			strcpy(graffiti[i], CONST_GNG.c_str());
			graffiticolor[i] = COLOR_BLACK;
		}
	}
}
void checkForCCSGraffiti(char(&graffiti)[4][4], char(&graffiticolor)[4], const int x, const int y, const int z) {
	for (int i = WALL_UP; i <= WALL_RIGHT; i++) {
		if (getSiteFlagForWall(x, y, z, (wallDirection)i) & SITEBLOCK_GRAFFITI_CCS) {
			strcpy(graffiti[i], CONST_CCS.c_str());
			graffiticolor[i] = COLOR_RED;
		}
	}

}
void checkForLCSGraffiti(char(&graffiti)[4][4], char(&graffiticolor)[4], const int x, const int y, const int z) {
	for (int i = WALL_UP; i <= WALL_RIGHT; i++) {
		if (getSiteFlagForWall(x, y, z, (wallDirection)i) & SITEBLOCK_GRAFFITI) {
			strcpy(graffiti[i], CONST_LCS.c_str());
			graffiticolor[i] = COLOR_GREEN;
		}
	}
}

void printwall(int x, int y, const int z, const int px, const int py)
{

	bool visible[8] = { false,false,false,false,false,false,false,false };
	bool bloody[8] = { false,false,false,false,false,false,false,false };
	char graffiti[4][4] = { "   ","   ","   ","   " };
	//	char graffiti[4][4] = { CONST_sitedisplay010.c_str(),CONST_sitedisplay010.c_str(),CONST_sitedisplay010.c_str(),CONST_sitedisplay010.c_str() };
	char graffiticolor[4] = { COLOR_BLACK,COLOR_BLACK,COLOR_BLACK,COLOR_BLACK };
	int type = levelmap[x][y][z].flag; // What are we drawing here? Wall/door? Locked/jammed? Metal/normal?
									   // Now follows a series of checks to determine the faces of the wall that should be
									   // displayed. Note the order of these checks is important:
									   //
									   // 1) You will see the wall if it's the upward face and you're above it (directional visibility)...
									   // 2) ...unless your line of sight is blocked (LOS)...
									   // 3) ...but line of sight and directional visibility is not important if you have already seen that
									   //          tile (memory)...
									   // 4) ...and regardless of any of the above, if there's a physical obstruction that would prevent you
									   //          from seeing it even if you were near it, like a wall, it should not be shown (blockages).
									   //
									   // The order of the remainder of the checks is not crucial.
									   // 1) Check for directional visibility
	checkForDirectionalVisibility(visible, x, y);
	// 2) Check LOS
	checkForLOS(visible, x, y, z);
	// 3) Check for memory
	checkForMemory(visible, x, y, z);
	// 4) Check for blockages
	checkForBlockage(visible, x, y, z);
	// Below not used for doors
	if (levelmap[x][y][z].flag & SITEBLOCK_BLOCK)
	{
		// Check for bloody walls
		checkForBloodyWalls(bloody, x, y, z);
		// Check for other graffiti
		checkForOtherGraffiti(graffiti, graffiticolor, x, y, z);
		// Check for CCS graffiti
		checkForCCSGraffiti(graffiti, graffiticolor, x, y, z);
		// Check for LCS graffiti
		checkForLCSGraffiti(graffiti, graffiticolor, x, y, z);
	}
	for (int dir = 4; dir < 8; dir++)
	{
		x = px, y = py;
		// Draw the corner
		if (visible[dir] && (type & SITEBLOCK_BLOCK))
		{
			bool blink = type & SITEBLOCK_METAL;
			// Position cursor in the correct corner
			//if(dir==CORNER_UL) // Nothing to do in this case
			if (dir == CORNER_UR) x += 4;
			if (dir == CORNER_DL) y += 2;
			if (dir == CORNER_DR) y += 2, x += 4;
			// Blood overrides gray base wall color
			if (bloody[dir]) set_color(COLOR_RED, COLOR_RED, 0);
			else set_color(COLOR_WHITE, COLOR_WHITE, 0, blink);
			// The corner's ready to draw now
			mvaddcharAlt(y, x, ' ');
		}
	}
	for (int dir = 0; dir < 4; dir++)
	{
		x = px, y = py;
		// Draw the wall/door
		if (visible[dir])
		{
			if (type & SITEBLOCK_BLOCK)
			{
				bool blink = type & SITEBLOCK_METAL;
				// Position cursor at the start of where the graffiti tag would go
				//if(dir==WALL_LEFT) // Nothing to do in this case
				if (dir == WALL_RIGHT) x += 4;
				if (dir == WALL_UP) x++;
				if (dir == WALL_DOWN) y += 2, x++;
				// Blood overrides graffiti overrides gray base wall color
				if (bloody[dir])
					set_color_easy(RED_ON_RED);
				else if (graffiti[dir][0] != ' ')
					set_color(graffiticolor[dir], COLOR_WHITE, 0, blink);
				else set_color(COLOR_WHITE, COLOR_WHITE, 0, blink);
				// Draw the chunk of wall where the graffiti would/will go
				for (int gchar = 0; gchar < 3; gchar++)
				{
					mvaddcharAlt(y, x, graffiti[dir][gchar]);
					if (dir == WALL_RIGHT || dir == WALL_LEFT) y++;
					else x++;
				}
				// For the long faces (top and bottom) of the wall, there is
				// additional space to either side of the 'tag' (or lack of tag)
				// that needs to be filled in with wall or blood color
				if (dir == WALL_UP || dir == WALL_DOWN)
				{
					if (bloody[dir]) set_color_easy(RED_ON_RED);
					else set_color(COLOR_WHITE, COLOR_WHITE, 0, blink);
					if (!visible[WALL_LEFT]) mvaddcharAlt(y, px, ' ');
					if (!visible[WALL_RIGHT]) mvaddcharAlt(y, px + 4, ' ');
				}
			}
			else if (type & SITEBLOCK_DOOR)
			{
				// Doors are, thankfully, much simpler, as they do not
				// support blood or graffiti
				// Position cursor at the start of face
				if (dir == WALL_DOWN) y += 2;
				if (dir == WALL_RIGHT) x += 4;
				// Pick color
				if (type & SITEBLOCK_METAL)
					set_color_easy(WHITE_ON_WHITE_BRIGHT);
				else if (type & SITEBLOCK_CLOCK && type & SITEBLOCK_LOCKED)
					set_color_easy(RED_ON_BLACK);
				else if (type & SITEBLOCK_KLOCK && type & SITEBLOCK_LOCKED)
					set_color_easy(BLACK_ON_BLACK_BRIGHT);
				else set_color_easy(YELLOW_ON_BLACK);
				// Draw face
				if (dir == WALL_RIGHT || dir == WALL_LEFT)
					for (int i = 0; i < 3; i++) mvaddstrAlt(y++, x, CONST_V_DOUBLE_LINE.c_str());
				else for (int i = 0; i < 5; i++) mvaddstrAlt(y, x++, CONST_H_DOUBLE_LINE.c_str());
				// Corners are possible if walls nearby are blown away, although this is rare
				if ((dir == WALL_LEFT && visible[WALL_UP]) || (dir == WALL_UP && visible[WALL_LEFT])) mvaddstrAlt(py, px, CONST_UL_CORNER.c_str());
				if ((dir == WALL_RIGHT && visible[WALL_UP]) || (dir == WALL_UP && visible[WALL_RIGHT])) mvaddstrAlt(py, px + 4, CONST_UR_CORNER.c_str());
				if ((dir == WALL_LEFT && visible[WALL_DOWN]) || (dir == WALL_DOWN && visible[WALL_LEFT])) mvaddstrAlt(py + 2, px, CONST_LL_CORNER.c_str());
				if ((dir == WALL_RIGHT && visible[WALL_DOWN]) || (dir == WALL_DOWN && visible[WALL_RIGHT])) mvaddstrAlt(py + 2, px + 4, CONST_LR_CORNER.c_str());
			}
		}
	}
}

void printdebris(const int px, const int py) {
	const int backcolor = COLOR_BLACK;
	const char blink = 0;

	set_color(COLOR_WHITE, backcolor, 1, blink);
	mvaddcharAlt(py + 0, px + 1, '.');
	mvaddcharAlt(py + 0, px + 4, '^');
	mvaddcharAlt(py + 1, px + 0, '=');
	mvaddcharAlt(py + 1, px + 3, '.');
	mvaddcharAlt(py + 1, px + 4, '|');
	mvaddcharAlt(py + 2, px + 1, '.');
	mvaddcharAlt(py + 2, px + 4, '\\');
}
void printfirepeak(const int px, const int py) {
	const int backcolor = COLOR_BLACK;
	const char blink = 0;

	set_color(COLOR_RED, backcolor, 1, blink);
	mvaddcharAlt(py + 0, px + 1, ':');
	mvaddcharAlt(py + 1, px + 0, '*');
	set_color(COLOR_YELLOW, backcolor, 1, blink);
	mvaddcharAlt(py + 0, px + 4, '$');
	mvaddcharAlt(py + 1, px + 3, ':');
	mvaddcharAlt(py + 1, px + 4, '%');
	mvaddcharAlt(py + 2, px + 1, ':');
	mvaddcharAlt(py + 2, px + 4, '*');
}
void printfirestart(const int px, const int py) {
	const int backcolor = COLOR_BLACK;
	const char blink = 0;

	set_color(COLOR_RED, backcolor, 1, blink);
	mvaddcharAlt(py + 0, px + 1, '.');
	set_color(COLOR_YELLOW, backcolor, 1, blink);
	mvaddcharAlt(py + 1, px + 3, '.');
	mvaddcharAlt(py + 2, px + 1, '.');
}
void printfireend(const int px, const int py) {
	const int backcolor = COLOR_BLACK;
	const char blink = 0;

	set_color(COLOR_RED, backcolor, 1, blink);
	mvaddcharAlt(py + 1, px + 0, '*');
	set_color(COLOR_YELLOW, backcolor, 1, blink);
	mvaddcharAlt(py + 0, px + 4, '~');
	mvaddcharAlt(py + 2, px + 4, '#');
	set_color(COLOR_WHITE, backcolor, 1, blink);
	mvaddcharAlt(py + 0, px + 1, '.');
	mvaddcharAlt(py + 1, px + 3, '.');
	mvaddcharAlt(py + 1, px + 4, '|');
	mvaddcharAlt(py + 2, px + 1, '.');
}

void printbloodyone(const int px, const int py) {
	const int backcolor = COLOR_BLACK;
	const char blink = 0;

	set_color(COLOR_RED, backcolor, 0, blink);
	mvaddcharAlt(py + 2, px + 1, '.');
	mvaddcharAlt(py + 1, px + 2, '.');
}
void printbloodytwo(const int px, const int py) {
	const int backcolor = COLOR_BLACK;
	const char blink = 0;

	set_color(COLOR_RED, backcolor, 0, blink);
	mvaddcharAlt(py + 1, px + 1, '%');
	mvaddcharAlt(py + 2, px + 1, '.');
	mvaddcharAlt(py + 1, px + 2, '.');
}
void printspecialtile(const short special, const int px, const int py) {
	const int backcolor = COLOR_BLACK;
	const char blink = 0;
	set_color(COLOR_YELLOW, backcolor, 1, blink);
	switch (special)
	{
	case SPECIAL_NUCLEAR_ONOFF:mvaddstrAlt(py, px, CONST_POWER); break;
	case SPECIAL_LAB_COSMETICS_CAGEDANIMALS:
	case SPECIAL_LAB_GENETIC_CAGEDANIMALS:mvaddstrAlt(py, px, CONST_CAGES); break;
	case SPECIAL_POLICESTATION_LOCKUP:
	case SPECIAL_COURTHOUSE_LOCKUP:mvaddstrAlt(py, px, CONST_CELLS); break;
	case SPECIAL_COURTHOUSE_JURYROOM:mvaddstrAlt(py, px, CONST_JURY); break;
	case SPECIAL_PRISON_CONTROL:
	case SPECIAL_PRISON_CONTROL_LOW:
	case SPECIAL_PRISON_CONTROL_MEDIUM:
	case SPECIAL_PRISON_CONTROL_HIGH:mvaddstrAlt(py, px, CONST_CTROL); break;
	case SPECIAL_INTEL_SUPERCOMPUTER:mvaddstrAlt(py, px, CONST_INTEL); break;
	case SPECIAL_SWEATSHOP_EQUIPMENT:
	case SPECIAL_POLLUTER_EQUIPMENT:mvaddstrAlt(py, px, CONST_EQUIP); break;
	case SPECIAL_ARMORY:mvaddstrAlt(py, px, CONST_ARMRY); break;
	case SPECIAL_HOUSE_CEO:mvaddstrAlt(py, px + 1, tag_CEO); break;
	case SPECIAL_HOUSE_PHOTOS:
	case SPECIAL_CORPORATE_FILES:mvaddstrAlt(py, px, CONST_SAFE_EXCLAIM); break;
	case SPECIAL_RADIO_BROADCASTSTUDIO:mvaddstrAlt(py, px + 1, CONST_MIC); break;
	case SPECIAL_NEWS_BROADCASTSTUDIO:mvaddstrAlt(py, px, CONST_STAGE); break;
	case SPECIAL_APARTMENT_LANDLORD:mvaddstrAlt(py, px, CONST_RENT_QUESTION); break;
	case SPECIAL_SIGN_ONE:
	case SPECIAL_SIGN_TWO:
	case SPECIAL_SIGN_THREE:mvaddstrAlt(py, px, CONST_SIGN_EXCLAIM); break;
	case SPECIAL_STAIRS_UP:mvaddstrAlt(py, px + 1, "UP\x18"); break;
	case SPECIAL_STAIRS_DOWN:mvaddstrAlt(py, px + 1, "DN\x19"); break;
	case SPECIAL_RESTAURANT_TABLE:mvaddstrAlt(py, px, CONST_UC_TABLE); break;
	case SPECIAL_CAFE_COMPUTER:mvaddstrAlt(py, px + 1, CONST_CPU); break;
	case SPECIAL_PARK_BENCH:mvaddstrAlt(py, px, CONST_UC_BENCH); break;
	case SPECIAL_SECURITY_METALDETECTORS:mvaddstrAlt(py, px, CONST_METAL); break;
	case SPECIAL_SECURITY_CHECKPOINT:mvaddstrAlt(py, px, CONST_GUARD); break;
	case SPECIAL_DISPLAY_CASE:mvaddstrAlt(py, px, CONST_CASE); break;
	case SPECIAL_BANK_VAULT:mvaddstrAlt(py, px, CONST_VAULT); break;
	case SPECIAL_BANK_TELLER:mvaddstrAlt(py, px, CONST_TELER); break;
	case SPECIAL_BANK_MONEY:mvaddstrAlt(py, px, tag_MONEY); break;
	case SPECIAL_CCS_BOSS:mvaddstrAlt(py, px, CONST_BOSS); break;
	case SPECIAL_OVAL_OFFICE_NW:mvaddstrAlt(py, px + 3, CONST_OV); break;
	case SPECIAL_OVAL_OFFICE_NE:mvaddstrAlt(py, px, CONST_AL); break;
	case SPECIAL_OVAL_OFFICE_SW:mvaddstrAlt(py, px + 2, CONST_UC_OFF); break;
	case SPECIAL_OVAL_OFFICE_SE:mvaddstrAlt(py, px, CONST_ICE); break;
	}
}
void printemptysquare(const int flag, const int px, const int py) {
	char ch;
	if (flag & SITEBLOCK_RESTRICTED)
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		ch = '+';
	}
	else if (flag & SITEBLOCK_GRASSY)
	{
		set_color_easy(GREEN_ON_BLACK);
		ch = '.';
	}
	else if (flag & SITEBLOCK_OUTDOOR)
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		ch = ' ';
	}
	else
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		ch = ' ';
	}
	for (int px2 = px; px2 < px + 5; px2++)
		for (int py2 = py; py2 < py + 3; py2++)
			mvaddcharAlt(py2, px2, ch);
}
void printsiteexit(const int px, const int py) {

	const int backcolor = COLOR_BLACK;
	const char blink = 0;
	set_color(COLOR_WHITE, backcolor, 0, blink);
	mvaddstrAlt(py + 1, px + 1, CONST_EXT);
}
void printsiteloot(const int px, const int py) {

	const int backcolor = COLOR_BLACK;
	const char blink = 0;
	set_color(COLOR_MAGENTA, backcolor, 1, blink);
	mvaddstrAlt(py, px + 1, CONST_MONEY_ON_GROUND);
}
void printstatusofsquare(const int flag, const int px, const int py) {
	// These functions mostly overwrite one another in the event multiple are true
	// The big exception is the last two, and later on the other instances
	// Of strings being printed, rather than char based
	if (flag & SITEBLOCK_DEBRIS)
	{
		printdebris(px, py);
	}
	if (flag & SITEBLOCK_FIRE_START)
	{
		printfirestart(px, py);
	}
	if (flag & SITEBLOCK_FIRE_PEAK)
	{
		printfirepeak(px, py);
	}
	if (flag & SITEBLOCK_FIRE_END)
	{
		printfireend(px, py);
	}
	if (flag & SITEBLOCK_BLOODY)
	{
		printbloodyone(px, py);
	}
	if (flag & SITEBLOCK_BLOODY2)
	{
		printbloodytwo(px, py);
	}
	if (flag & SITEBLOCK_EXIT)
	{
		printsiteexit(px, py);
	}
	else if (flag & SITEBLOCK_LOOT)
	{
		printsiteloot(px, py);
	}
}
void printblock(int x, int y, int z, int px, int py)
{
	if (!LineOfSight(x, y, z))
	{
		set_color_easy(BLACK_ON_BLACK);
		for (x = px; x < px + 5; x++)
			for (y = py; y < py + 3; y++)
				mvaddcharAlt(y, x, ' ');
	}
	else {
		levelmap[x][y][z].flag |= SITEBLOCK_KNOWN;
		if (levelmap[x][y][z].flag & (SITEBLOCK_BLOCK | SITEBLOCK_DOOR))
		{
			printwall(x, y, z, px, py);
		}
		else {
			const int backcolor = COLOR_BLACK;
			const char blink = 0;
			printemptysquare(levelmap[x][y][z].flag, px, py);
			printstatusofsquare(levelmap[x][y][z].flag, px, py);

			if (levelmap[x][y][z].siegeflag & SIEGEFLAG_TRAP)
			{
				set_color(COLOR_YELLOW, backcolor, 1, blink);
				mvaddstrAlt(py + 1, px, CONST_TRAP);
			}
			else if (levelmap[x][y][z].siegeflag & SIEGEFLAG_UNIT_DAMAGED)
			{
				set_color(COLOR_RED, backcolor, 0, blink);
				mvaddstrAlt(py + 2, px, CONST_LC_ENEMY);
			}
			else if (levelmap[x][y][z].special != -1)
			{
				printspecialtile(levelmap[x][y][z].special, px, py);

			}
			if (levelmap[x][y][z].siegeflag & SIEGEFLAG_HEAVYUNIT)
			{
				set_color(COLOR_RED, backcolor, 1, blink);
				mvaddstrAlt(py + 2, px, tag_ARMOR);
			}
			else if (levelmap[x][y][z].siegeflag & SIEGEFLAG_UNIT)
			{
				set_color(COLOR_RED, backcolor, 1, blink);
				mvaddstrAlt(py + 2, px, CONST_ENEMY);
			}
		}
	}
}
// Prints the map graphics in the bottom right of the screen
void printsitemap(int x, int y, int z)
{
	mapshowing = true;
	// Build the frame
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(8, 53, CONST_UL_CORNER_26_SPACES_UR_CORNER.c_str()); // 27 characters - top of map
	mvaddstrAlt(24, 53, CONST_LL_CORNER_26_SPACES_LR_CORNER.c_str()); // 27 characters - bottom of map
	for (int yscreen = 9; yscreen < 24; yscreen++)
		mvaddstrAlt(yscreen, 53, CONST_V_LINE_26_SPACES_V_LINE.c_str()); // 27 characters - the map itself
																// Do a preliminary Line of Sight iteration for better Line of Sight detection
	for (int xsite = x - 2; xsite < x + 3; xsite++)
		for (int ysite = y - 2; ysite < y + 3; ysite++)
			if (LineOfSight(xsite, ysite, z))
				levelmap[xsite][ysite][z].flag |= SITEBLOCK_KNOWN;
	// Display the map
	for (int xsite = x - 2, xscreen = 79 - 5 * 5; xsite < x + 3; xscreen += 5, xsite++)
		for (int ysite = y - 2, yscreen = 24 - 3 * 5; ysite < y + 3; yscreen += 3, ysite++)
			printblock(xsite, ysite, z, xscreen, yscreen);
	//PRINT SPECIAL
	string str;
	if (specialString.count(static_cast<SpecialBlocks>(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special)) > 0) {
		str = specialString[static_cast<SpecialBlocks>(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special)];
	}
	else {
		str = "";
	}

	if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].special != -1)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(24, 67 - (len(str) >> 1), str);
	}
	//PRINT PARTY
	int partyalive = squadAlive();
	if (partyalive > 0) set_color_easy(GREEN_ON_BLACK_BRIGHT);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 64, CONST_ALLCAPS_SQUAD);
	int encsize = encounterSize();
	//PRINT ANY OPPOSING FORCE INFO
	if (encsize)
	{
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		if (levelmap[loc_coord.locx][loc_coord.locx][loc_coord.locz].siegeflag & SIEGEFLAG_HEAVYUNIT)
			mvaddstrAlt(17, 64, tag_ARMOR);
		else if (levelmap[loc_coord.locx][loc_coord.locx][loc_coord.locz].siegeflag & SIEGEFLAG_UNIT)
			mvaddstrAlt(17, 64, CONST_ENEMY);
		else if (levelmap[loc_coord.locx][loc_coord.locx][loc_coord.locz].siegeflag & SIEGEFLAG_UNIT_DAMAGED)
			mvaddstrAlt(17, 64, CONST_LC_ENEMY);
		else mvaddstrAlt(17, 64, CONST_ENCTR);
		printencounter();
	}
	if (isThereGroundLoot())
	{
		set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
		mvaddstrAlt(15, 64, CONST_LOOT_EXCLAMATION);
		printencounter();
	}
}
void clearmaparea(bool lower, bool upper)
{
	if (upper) mapshowing = false;
	set_color_easy(WHITE_ON_BLACK);
	for (int y = 8; y < 25; y++)
	{
		if (!upper&&y < 15)continue;
		if (!lower&&y >= 15)continue;
		if (y == 8) mvaddstrAlt(y, 53, CONST_H_27_LINE);  // 27 characters
		else mvaddstrAlt(y, 53, CONST_27_SPACES);  // 27 spaces
	}
}
/* blanks a part of the screen */
void clearcommandarea()
{
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	for (int y = 9; y < 16; y++)
		mvaddstrAlt(y, 0, CONST_53_SPACES); // 53 spaces
	if (mode != GAMEMODE_SITE) clearmaparea(false, true);
}
void refreshmaparea()
{
	if (mode == GAMEMODE_SITE) printsitemap(loc_coord.locx, loc_coord.locy, loc_coord.locz);
	else clearmaparea(true, false);
}
void clearmessagearea(bool redrawmaparea)
{
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	if (redrawmaparea)
	{
		mvaddstrAlt(16, 0, CONST_80_SPACES); // 80 spaces
		mvaddstrAlt(17, 0, CONST_80_SPACES); // 80 spaces
		refreshmaparea();
		// Must reprint chasers when no map to the right
		if (mode == GAMEMODE_CHASECAR || mode == GAMEMODE_CHASEFOOT) printchaseencounter();
	}
	else
	{
		mvaddstrAlt(16, 0, CONST_53_SPACES); // 53 spaces
		mvaddstrAlt(17, 0, CONST_53_SPACES); // 53 spaces
	}
}
/* news - show major news story */
void preparepage(const Deprecatednewsstoryst ns, const bool liberalguardian)
{
	set_color_easy(WHITE_ON_WHITE);
	for (int x = 0; x < 80; x++)
		for (int y = 0; y < 25; y++)
			mvaddcharAlt(y, x, ' ');
	set_color_easy(WHITE_ON_BLACK);
	if (ns.page == 1 || (liberalguardian&&ns.guardianpage == 1))
	{
		//TOP
		int pap = LCSrandom(5);
		for (int x = 0; x < 80; x++)
		{
			for (int y = 0; y < 5; y++)
			{
				if (liberalguardian)
				{
					set_color((newstops[5][x][y][1]),
						(newstops[5][x][y][2]),
						newstops[5][x][y][3]);
					mvaddcharAlt(y, x, newstops[5][x][y][0]);
				}
				else
				{
					set_color((newstops[pap][x][y][1]),
						(newstops[pap][x][y][2]),
						newstops[pap][x][y][3]);
					mvaddcharAlt(y, x, newstops[pap][x][y][0]);
				}
			}
		}
		if (!liberalguardian) // Liberal Guardian graphics don't support adding a date
		{
			//DATE
			set_color_easy(BLACK_ON_WHITE);
			int pday = day, pmonth = month, pyear = year;
			if (pday > monthday()) // Day counter has increased but end-of-month has not yet
			{ // been checked so it has to be accounted for here.
				pday = 1, pmonth++;
				if (pmonth > 12) pmonth = 1, pyear++;
			}
			mvaddstrAlt(3, 66 + (pday < 10), getmonth(pmonth, true));
			addstrAlt(singleSpace);
			addstrAlt(pday);
			addstrAlt(COMMA_SPACE);
			addstrAlt(pyear);
		}
	}
	else
	{
		//PAGE
		set_color_easy(BLACK_ON_WHITE);
		mvaddstrAlt(0, 76, liberalguardian ? ns.guardianpage : ns.page);
	}
}

void displaycenterednewsfont(const std::string& str, int y)
{
	int width = -1;
	for (int s = 0; s < len(str); s++)
	{
		if (str[s] >= 'A'&&str[s] <= 'Z')width += 6;
		else if (str[s] == '\'')width += 4;
		else width += 3;
	}
	int x = 39 - width / 2;
	for (int s = 0; s < len(str); s++)
	{
		if ((str[s] >= 'A'&&str[s] <= 'Z') || str[s] == '\'')
		{
			int p;
			if (str[s] >= 'A'&&str[s] <= 'Z') p = str[s] - 'A';
			else p = 26;
			int lim = 6;
			if (str[s] == '\'') lim = 4;
			if (s == len(str) - 1) lim--;
			for (int x2 = 0; x2 < lim; x2++) for (int y2 = 0; y2 < 7; y2++)
			{
				// Clean the square first.
				set_color_easy(BLACK_ON_BLACK);
				mvaddchAlt(y + y2, x + x2, ' ');
				if (x2 == 5)
				{
					set_color_easy(WHITE_ON_WHITE);
					mvaddchAlt(y + y2, x + x2, ' ');
				}
				else
				{
					set_color((bigletters[p][x2][y2][1]),
						(bigletters[p][x2][y2][2]),
						bigletters[p][x2][y2][3]);
					mvaddcharAlt(y + y2, x + x2, bigletters[p][x2][y2][0]);
				}
			}
			x += lim;
		}
		else
		{
			set_color_easy(WHITE_ON_WHITE);
			for (int x2 = 0; x2 < 3; x2++) for (int y2 = 0; y2 < 7; y2++)
			{
				mvaddcharAlt(y + y2, x + x2, ' ');
			}
			x += 3;
		}
	}
}

void displaynewspicture(int p, int y)
{
	for (int x2 = 0; x2 < 78; x2++)
		for (int y2 = 0; y2 < 15; y2++)
		{
			if (y + y2 > 24) break;
			set_color((newspic[p][x2][y2][1]),
				(newspic[p][x2][y2][2]),
				newspic[p][x2][y2][3]);
			moveAlt(y + y2, 1 + x2);
			addcharAlt(newspic[p][x2][y2][0]);
		}
}

void setColorForArmor(const Armor ar) {
	int fg = COLOR_WHITE;
	int bg = COLOR_BLACK;
	int in = 1;
	if (ar.is_bloody())
	{
		bg = COLOR_RED;  in = 1;
	}
	if (ar.get_quality() > ar.get_quality_levels())
	{
		fg = COLOR_BLACK;
	}
	else if (ar.is_damaged())
	{
		fg = COLOR_YELLOW; in = 1;
	}
	else if (ar.get_quality() > 1)
	{
		fg = COLOR_YELLOW; in = (bg == COLOR_RED);
	}
	if (fg == COLOR_WHITE && bg == COLOR_BLACK)
		in = 0;
	set_color(fg, bg, in);
}


void set_color_for_armor(const Armor armor) {
	int fg = COLOR_WHITE;
	int bg = COLOR_BLACK;
	int in = 1;
	if (armor.is_bloody())
	{
		bg = COLOR_RED;  in = 0;
	}
	if (armor.get_quality() > armor.get_quality_levels())
	{
		fg = COLOR_BLACK;
	}
	else if (armor.is_damaged())
	{
		fg = COLOR_YELLOW; in = 1;
	}
	else if (armor.get_quality() > 1)
	{
		fg = COLOR_YELLOW; in = (bg == COLOR_RED);
	}
	if (fg == COLOR_WHITE && bg == COLOR_BLACK)
		in = 0;
	set_color(fg, bg, in);
}


bool has_ignited(const int c) {

	// Ignition currently follows five steps
	//CH_BOX_DRAWINGS_LIGHT_VERTICAL
	//CH_DARK_SHADE
	//CH_MEDIUM_SHADE
	//CH_LIGHT_SHADE
	//' '
	// Any character other than these five indicate non-ignition
	// therfore, only these five should not be used in flag design
	return c == CH_BOX_DRAWINGS_LIGHT_VERTICAL ||
		c == CH_DARK_SHADE ||
		c == CH_MEDIUM_SHADE ||
		c == CH_LIGHT_SHADE ||
		c == ' ';
}

void printFlag() {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 18; j++) {
			set_color_easy(AmericanFlag[i][j].first);
			mvaddchAlt(i + 10, j + 31, AmericanFlag[i][j].second);
		}
	}
}
void printFlagB() {

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 17; j++) {
			set_color_easy(ConfederateFlag[i][j].first);
			mvaddchAlt(i + 10, j + 31, ConfederateFlag[i][j].second);
		}
	}
}
/* base - burn the flag */
void burnflag()
{
	const int FLAG_HEIGHT = 7;
	const int FLAG_WIDTH = 17;
	int flagparts = FLAG_HEIGHT * FLAG_WIDTH;
	std::pair<ColorSetup, int> flag[FLAG_WIDTH][FLAG_HEIGHT];
	for (int y = 0; y < FLAG_HEIGHT; y++) {
		for (int x = 0; x < FLAG_WIDTH; x++) {
			flag[x][y] = AmericanFlag[y][x];
		}
	}
	int x1 = LCSrandom(FLAG_WIDTH);
	int y1 = LCSrandom(FLAG_HEIGHT);
	flag[x1][y1] = std::pair<ColorSetup, int>(YELLOW_ON_BLACK_BRIGHT, CH_DARK_SHADE);
	bool first = true;
	while (flagparts > 0)
	{
		if (!first) for (int x = 0; x < FLAG_WIDTH; x++) for (int y = 0; y < FLAG_HEIGHT; y++)
		{
			if (flag[x][y].second == CH_BOX_DRAWINGS_LIGHT_VERTICAL) { flag[x][y] = std::pair<ColorSetup, int>(flag[x][y].first, CH_DARK_SHADE); }
			else if (flag[x][y].second == CH_DARK_SHADE)
			{
				flag[x][y] = std::pair<ColorSetup, int>(RED_ON_BLACK, CH_MEDIUM_SHADE);
			}
			else if (flag[x][y].second == CH_MEDIUM_SHADE)
			{
				flag[x][y] = std::pair<ColorSetup, int>(BLACK_ON_BLACK_BRIGHT, CH_LIGHT_SHADE);
			}
			else if (flag[x][y].second == CH_LIGHT_SHADE)
			{
				flagparts--;
				flag[x][y] = std::pair<ColorSetup, int>(BLACK_ON_BLACK, ' ');
			}
		}
		else first = false;
		for (int x = 0; x < FLAG_WIDTH; x++) for (int y = 0; y < FLAG_HEIGHT; y++)
		{
			set_color_easy(flag[x][y].first);
			mvaddchAlt(y + 10, x + 31, flag[x][y].second);
		}

		pause_ms(10);

		bool gotnew = false;
		while (!gotnew&&flagparts > 3)
		{
			int x = LCSrandom(FLAG_WIDTH);
			int y = LCSrandom(FLAG_HEIGHT);

			if (!has_ignited(flag[x][y].second))
			{
				bool conf = false;
				if (x > 0)
				{
					if (has_ignited(flag[x - 1][y].second)) conf = true;
				}
				if (x < 17)
				{
					if (has_ignited(flag[x + 1][y].second)) conf = true;
				}
				if (y > 0)
				{
					if (has_ignited(flag[x][y - 1].second)) conf = true;
				}
				if (y < 6)
				{
					if (has_ignited(flag[x][y + 1].second)) conf = true;
				}
				if (conf)
				{
					flag[x][y] = std::pair<ColorSetup, int>(YELLOW_ON_BLACK_BRIGHT, CH_BOX_DRAWINGS_LIGHT_VERTICAL);
					gotnew = true;
				}
			}
		}
	}
}

/*
Copyright (c) 2002,2003,2004 by Tarn Adams                                            //
//
This file is part of Liberal Crime Squad.                                             //
//
Liberal Crime Squad is free software; you can redistribute it and/or modify     //
it under the terms of the GNU General Public License as published by            //
the Free Software Foundation; either version 2 of the License, or               //
(at your option) any later version.                                             //
//
Liberal Crime Squad is distributed in the hope that it will be useful,          //
but WITHOUT ANY WARRANTY; without even the implied warranty of                  //
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the                  //
GNU General Public License for more details.                                    //
//
You should have received a copy of the GNU General Public License               //
along with Liberal Crime Squad; if not, write to the Free Software              //
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   02111-1307   USA     //
*/
/*
This file was created by Chris Johnson (grundee@users.sourceforge.net)
by copying code from game.cpp.
To see descriptions of files and functions, see the list at
the bottom of includes.h in the top src folder.
*/
//#define CONSOLE_SUPPORT // define this BEFORE including anything

void    PDC_set_titleAlt(const char *ch);
//IN CASE FUNKY ARROW KEYS ARE SENT IN, TRANSLATE THEM BACK
void translategetch(int &c)
{
	//if(c==-63)c='7';
	//if(c==-62)c='8';
	//if(c==-61)c='9';
	//if(c==-60)c='4';
	//if(c==-59)c='5';
	//if(c==-58)c='6';
	//if(c==-57)c='1';
	//if(c==-56)c='2';
	//if(c==-55)c='3';
	if (c == -6 || c == 0x1FA) c = '0';
	if (c == -50 || c == 0x1CE) c = '.';
	if (c == -53 || c == 0x1CB) c = ENTER;
	if (c == -47 || c == 0x1D1) c = '+';
	if (c == -48 || c == 0x1D0) c = '-';
	if (c == -49 || c == 0x1CF) c = '*';
	if (c == -54 || c == 0x1CA) c = '/';
	/*
	if(c==2)c='2';
	if(c==3)c='8';
	if(c==4)c='4';
	if(c==5)c='6';
	*/
	// SPECIAL TRANSLATION for AZERTY keyboard
	if (interface_pgup == '.')
	{
		if (c == ';')c = '.';
		if (c == ':')c = '/';
		if (c == '&')c = '1';
		if (c == 0x82)c = '2';
		if (c == '\"')c = '3';
		if (c == '\'')c = '4';
		if (c == '(')c = '5';
		if (c == '-')c = '6';
		if (c == 0x8A)c = '7';
		if (c == '_')c = '8';
		if (c == 0x87)c = '9';
		if (c == 0x85)c = '0';
	}
	if (c >= 'A'&&c <= 'Z') { c += 'a' - 'A'; }
	/* Support Cursor Keys...*/
	//if(c==KEY_LEFT)c='a';
	//if(c==KEY_RIGHT)c='d';
	//if(c==KEY_UP)c='w';
	//if(c==KEY_DOWN)c='x';
}
void translategetch_cap(int &c)
{
	//if(c==-63)c='7';
	//if(c==-62)c='8';
	//if(c==-61)c='9';
	//if(c==-60)c='4';
	//if(c==-59)c='5';
	//if(c==-58)c='6';
	//if(c==-57)c='1';
	//if(c==-56)c='2';
	//if(c==-55)c='3';
	if (c == -6 || c == 0x1FA) c = '0';
	if (c == -50 || c == 0x1CE) c = '.';
	if (c == -53 || c == 0x1CB) c = ENTER;
	if (c == -47 || c == 0x1D1) c = '+';
	if (c == -48 || c == 0x1D0) c = '-';
	if (c == -49 || c == 0x1CF) c = '*';
	if (c == -54 || c == 0x1CA) c = '/';
	/*
	if(c==2)c='2';
	if(c==3)c='8';
	if(c==4)c='4';
	if(c==5)c='6';
	*/
}
void set_title(char *s)
{
	PDC_set_titleAlt(s);
}
// Initialize the console, depending on the OS and language/code page settings
void init_console()
{
	// This has to be set to Code Page 437 in Windows regardless of Unicode, that's just how PDCurses works on Windows, even the UTF-8 version of PDCurses
	SetConsoleOutputCP(437); // use Code Page 437 (US English code page for DOS) for output, regardless of anything else
	SetConsoleCP(437); // use Code Page 437 (US English code page for DOS) for input, regardless of anything else
	setlocale(LC_ALL, ENGLISH_UNITED_437.c_str());
	_setmbcp(_MB_CP_LOCALE); // use same code page as multibyte code page

}
BOOL FontSmoothingEnabled;
UINT TypeOfFontSmoothing;
void begin_cleartype_fix() // execute this function after loading settings from init.txt, but before the user is actively playing the game
{
	if (fixcleartype) // only do anything if fixcleartype was set in init.txt and we're running Windows XP or later
	{
		// first we get the font smoothing parameters from Windows so that the old settings are backed up
		SystemParametersInfo(SPI_GETFONTSMOOTHING, 0, &FontSmoothingEnabled, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
		SystemParametersInfo(SPI_GETFONTSMOOTHINGTYPE, 0, &TypeOfFontSmoothing, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
		// now we see if the game crashed or exited prematurely the last time, and load the font smoothing parameters from the file if
		//     that is the case, to ensure that the user's original font smoothing settings will be restored when they exit the game
		FILE *h;
		h = LCSOpenFile(CLEARTYPE_DAT.c_str(), CONST_RB.c_str(), LCSIO_PRE_HOME);
		if (h != NULL)
		{
			fread(&FontSmoothingEnabled, sizeof(BOOL), 1, h);
			fread(&TypeOfFontSmoothing, sizeof(UINT), 1, h);
			LCSCloseFile(h);
		}
		// now that we know for sure what the original settings were, and both the variables FontSmoothingEnabled and
		// TypeOfFontSmoothing are guaranteed to be the original settings prior to any modifications by this game, we can
		// back the original settings up to disk, in case the game crashes or is exited prematurely
		h = LCSOpenFile(CLEARTYPE_DAT.c_str(), CONST_WB.c_str(), LCSIO_PRE_HOME);
		if (h != NULL)
		{
			fwrite(&FontSmoothingEnabled, sizeof(BOOL), 1, h);
			fwrite(&TypeOfFontSmoothing, sizeof(UINT), 1, h);
			LCSCloseFile(h);
			// now that everything is safely backed up, we set the font smoothing parameters to be optimal for Liberal Crime Squad
			// ClearType messes things up and causes visual artifacts in Win32 Console Apps like this game so it's going to be off
			// but we'll have standard font smoothing on because it looks really good with Lucida Console, and doesn't affect raster fonts at all
			SystemParametersInfo(SPI_SETFONTSMOOTHING, TRUE, 0, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
			SystemParametersInfo(SPI_SETFONTSMOOTHINGTYPE, 0, (void*)FE_FONTSMOOTHINGSTANDARD, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
		}
	}
}
void end_cleartype_fix() // execute this function after the user is done playing the game, but before the program closes
{
	if (fixcleartype) // only do anything if fixcleartype was set in init.txt and we're running Windows XP or later
	{
		// restore the original settings the user had for font smoothing
		SystemParametersInfo(SPI_SETFONTSMOOTHINGTYPE, 0, (void*)TypeOfFontSmoothing, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
		SystemParametersInfo(SPI_SETFONTSMOOTHING, FontSmoothingEnabled, 0, SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
		// now that the settings are safely restored, it's time to delete the temporary backup of the font smoothing settings
		LCSDeleteFile(CLEARTYPE_DAT.c_str(), LCSIO_PRE_HOME);
	}
}
// STEALTH_CPP
void printShoutsForHelp(const string ename, const int ealign) {
	clearmessagearea();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, ename, gamelog);
	addstrAlt(CONST_OBSERVES_YOUR_LIBERAL_ACTIVITY, gamelog);
	if (ealign == ALIGN_CONSERVATIVE)
		mvaddstrAlt(17, 1, CONST_AND_LETS_FORTH_A_PIERCING_CONSERVATIVE_ALARM_CRY, gamelog);
	else mvaddstrAlt(17, 1, CONST_AND_SHOUTS_FOR_HELP, gamelog);
	gamelog.newline();
}
void printAlienation(const short sitealienate) {

	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	if (sitealienate == 1)mvaddstrAlt(16, 1, CONST_WE_VE_ALIENATED_THE_MASSES_HERE, gamelog);
	else mvaddstrAlt(16, 1, CONST_WE_VE_ALIENATED_ABSOLUTELY_EVERYONE_HERE, gamelog);
	gamelog.newline();
	mvaddstrAlt(17, 1, CONST_56_SPACES);
}
void printFadesAway(const string aname, const int partysize) {

	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	if (partysize > 1)
		mvaddstrAlt(16, 1, CONST_THE_SQUAD, gamelog);
	else
		mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(CONST_FADES_INTO_THE_SHADOWS, gamelog);
	gamelog.newline();
}
void printBlewStealthCheck(const string aname) {

	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(pickrandom(blew_stealth_check), gamelog);
	gamelog.newline();
}
void printActsNatural(const string aname, const int partysize) {

	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	if (partysize > 1)
		mvaddstrAlt(16, 1, CONST_THE_SQUAD, gamelog);
	else
		mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(CONST_ACTS_NATURAL, gamelog);
	gamelog.newline();
}
void printEnemyNameInAlarm(const string nname) {
	clearmessagearea();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, nname, gamelog);

}
void printLooksAtSquadSuspiciously() {
	addstrAlt(CONST_LOOKS_AT_THE_SQUAD_SUSPICIOUSLY, gamelog);

}
void printShoutsInAlarm() {
	addstrAlt(CONST_SHOUTS_IN_ALARM_AT_THE_SQUAD_S_LIBERAL_TRESPASSING, gamelog);

}
void printConservativeRaisesAlarm(const bool weapon, const int ntype, const int nalign) {
	if (weapon&&ntype != CREATURE_GUARDDOG)
	{
		addstrAlt(CONST_SEES_THE_SQUAD_S_LIBERAL_WEAPONS, gamelog);
		if (nalign == ALIGN_CONSERVATIVE)
			mvaddstrAlt(17, 1, CONST_AND_LETS_FORTH_A_PIERCING_CONSERVATIVE_ALARM_CRY, gamelog);
		else
			mvaddstrAlt(17, 1, CONST_AND_SHOUTS_FOR_HELP, gamelog);

	}
	else
	{
		addstrAlt(CONST_LOOKS_AT_THE_SQUAD_WITH_INTOLERANCE, gamelog);
		if (nalign == ALIGN_CONSERVATIVE)
		{
			if (ntype == CREATURE_GUARDDOG)
				mvaddstrAlt(17, 1, CONST_AND_LAUNCHES_INTO_ANGRY_CONSERVATIVE_BARKING, gamelog);
			else
				mvaddstrAlt(17, 1, CONST_AND_LETS_FORTH_A_PIERCING_CONSERVATIVE_ALARM_CRY, gamelog);
		}
		else
			mvaddstrAlt(17, 1, CONST_AND_SHOUTS_FOR_HELP, gamelog);
	}
	gamelog.newline();
}
// STEALTH_CPP

// TALK_CPP
bool isPrisoner(const string tkname) {
	return strcmp(tkname.data(), unnamed_String_Talk_cpp_081.data()) == 0;
	//	const string unnamed_String_Talk_cpp_060 = "Prisoner";
}

void printTalkAboutIssuesHeader(const string aname) {
	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);

}
void printTalkAboutIssuesWhenStupid(const int lw) {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	if (lw == LAW_POLICEBEHAVIOR) {
		if (lawList[LAW_FREESPEECH] == ALIGN_ARCHCONSERVATIVE)
			mvaddstrAlt(10, 1, CONST_THE_POLICE_ARE_NOT_DOING_THEIR_JOB_VERY_WELL, gamelog);
		else
			mvaddstrAlt(10, 1, CONST_THE_COPS_SUCK, gamelog);
	}
	else {
		mvaddstrAlt(10, 1, youAreStupidTalkAboutIssues[lw]);
	}
	gamelog.newline();
}
void printTalkAboutIssuesTooLiberal(const int lw) {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	mvaddstrAlt(10, 1, issueTooLiberal[lw]);
	gamelog.newline();
}
void printTalkAboutIssuesNormal(const int lw, const int tkanimalgloss) {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	if (lw == LAW_POLLUTION) {
		mvaddstrAlt(10, 1, CONST_INDUSTRIES_THAT_STOP_AT_NOTHING_TO_BECOME_MORE_PROFITABLE_ARE_POLLUTING, gamelog);
		if (tkanimalgloss == ANIMALGLOSS_ANIMAL) { mvaddstrAlt(11, 1, CONST_THE_ENVIRONMENT_IN_WAYS_THAT_HURT_NOT_ONLY_HUMANS_BUT_ANIMALS_TOO, gamelog); }
		else { mvaddstrAlt(11, 1, CONST_THE_ENVIRONMENT_IN_WAYS_THAT_HURT_NOT_ONLY_ANIMALS_BUT_PEOPLE_TOO, gamelog); }
	}
	else {
		mvaddstrAlt(10, 1, talkAboutTheIssues[lw][0], gamelog);
		mvaddstrAlt(11, 1, talkAboutTheIssues[lw][1], gamelog);
	}
	gamelog.newline();
}
void printTurnsAway() {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(unnamed_String_Talk_cpp_093, gamelog);
	gamelog.newline();
}
void printRespondantName(const string tkname, const bool extraline = false) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(12 + (extraline ? 1 : 0), 1, tkname, gamelog);
	addstrAlt(respondsComma, gamelog);
}
void printConservativeRespondsToStupid(const string tkname, const int tktype, const bool extraline) {
	printRespondantName(tkname, extraline);
	int y = 13 + (extraline ? 1 : 0);

	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	if (tktype == CREATURE_GANGUNIT)
		mvaddstrAlt(y, 1, CONST_DO_YOU_WANT_ME_TO_ARREST_YOU, gamelog);
	else if (tktype == CREATURE_DEATHSQUAD)
		mvaddstrAlt(y, 1, CONST_IF_YOU_DON_T_SHUT_UP_I_M_GOING_TO_SHOOT_YOU, gamelog);
	else
	{
		mvaddstrAlt(y, 1, pickrandom(that_is_not_disturbing), gamelog);
	}
}

void printConservativeCounter(const string tkname, const bool extraline, const int lw) {
	printRespondantName(tkname, extraline);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13 + (extraline ? 1 : 0), 1, conservativeLegalArgument[lw], gamelog);

}
void printRejectTalk(const string tkname, const bool extraline) {
	printRespondantName(tkname, extraline);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13 + (extraline ? 1 : 0), 1, CONST_WHATEVER, gamelog);

}
void printMutantTalkAboutIssues(const string tkname, const int extraline) {
	printRespondantName(tkname, extraline);
	int y = 13 + (extraline ? 1 : 0);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(y, 1, CONST_UGH_PFFT, gamelog);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(unnamed_String_Talk_cpp_093, gamelog);
	gamelog.newline();
}

void printThatIsDisturbing(const string tkname, const bool extraline, const int special_case) {
	printRespondantName(tkname, extraline);
	int y = 13 + (extraline ? 1 : 0);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	switch (special_case)
	{
	case 0:
		mvaddstrAlt(y++, 1, CONST_OH_REALLY, gamelog);
		pressAnyKey();
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		mvaddstrAlt(y, 1, CONST_YEAH_REALLY, gamelog);
		break;
	case 1:
		mvaddstrAlt(y, 1, CONST_YOU_GOT_ANYTHING_TO_SMOKE_ON_YOU, gamelog);
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		addstrAlt(CONST_COUGH, gamelog);
		break;
	default:
		mvaddstrAlt(y, 1, pickrandom(that_is_disturbing), gamelog);
		break;
	}
	gamelog.newline();
}
void printUnableToSpeakAgree(const string tkname, const bool extraline) {

	printRespondantName(tkname, extraline);
	int y = 13 + (extraline ? 1 : 0);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(y, 1, CONST_AAAAHHH, gamelog);
	gamelog.newline();
}
void printAgreesToComeByLater(const string tkname, const bool extraline, const bool another_extraline) {

	int y = 14 + (extraline ? 1 : 0) + (another_extraline ? 1 : 0);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(y, 1, CONST_AFTER_MORE_DISCUSSION, gamelog);
	addstrAlt(tkname, gamelog);
	addstrAlt(CONST_AGREES_TO_COME_BY_LATER_TONIGHT, gamelog);
	gamelog.newline();
}


void printSpecialRecruitment(const string aname, const string tkname, const string pitch, const string response) {
	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 1, pitch, gamelog);
	gamelog.newline();
	pressAnyKey();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, tkname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	mvaddstrAlt(14, 1, response, gamelog);
	gamelog.newline();

}
void printTalkOptionsDuringCombat(const bool hostages, const bool is_cantbluff_two, const bool cop) {
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(11, 1, CONST_A_INTIMIDATE);
	if (!hostages)set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(12, 1, CONST_B_THREATEN_HOSTAGES);
	if (!is_cantbluff_two)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_C_BLUFF);
	if (cop)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(14, 1, CONST_D_SURRENDER_TO_AUTHORITIES);
	set_color_easy(WHITE_ON_BLACK);
	gamelog.newline();

}

void printTalksToThem(const string aname, const int tkalign, const string tkname) {

	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(unnamed_String_Talk_cpp_094, gamelog);
	set_color_easy_alignment(tkalign);
	addstrAlt(tkname, gamelog);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(unnamed_String_Talk_cpp_095, gamelog);
	gamelog.newline();
}
void printTheSquadIsArrested() {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(14, 1, CONST_THE_SQUAD_IS_ARRESTED, gamelog);
	gamelog.newline();
}

void printTheEnemyIsFooled() {

	clearmessagearea();
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_THE_ENEMY_IS_FOOLED_AND_DEPARTS, gamelog);
	gamelog.newline();
}
void printXeIsNotFooled(const string ename, const bool noFreeSpeech) {
	clearmessagearea();
	set_color_easy(RED_ON_BLACK_BRIGHT);

	mvaddstrAlt(16, 1, ename, gamelog);
	addstrAlt(noFreeSpeech ? CONST_IS_NOT_FOOLED_BY_THAT_ACT : CONST_IS_NOT_FOOLED_BY_THAT_CRAP, gamelog);
	gamelog.newline();
}
void printITalkLikeAConservative(const string aname) {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(CONST_TALKS_LIKE_A_CONSERVATIVE, gamelog);
	mvaddstrAlt(17, 1, CONST_AND_PRETENDS_TO_BELONG_HERE, gamelog);
	gamelog.newline();
}
void printEngraveElbereth(const string aname) {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(CONST_ENGRAVES, gamelog);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	addstrAlt(CONST_ELBERETH, gamelog);     //Fanciful multicolor message
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	addstrAlt(CONST_ON_THE_FLOOR, gamelog);
	gamelog.newline();
}
void printDeathSquadBluff() {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_NON_TARGETS_PLEASE_LEAVE_THE_SITE, gamelog);
	gamelog.newline();
}

void printLabCoatBluff() {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	mvaddstrAlt(16, 1, CONST_MAKE_WAY_I_M_A_DOCTOR, gamelog);
	gamelog.newline();
}
void printPoliceBluff() {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);

	mvaddstrAlt(16, 1, CONST_THE_SITUATION_IS_UNDER_CONTROL, gamelog);
	gamelog.newline();
}
void printBunkerGearBluff(const short onfire) {
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, onfire ? CONST_FIRE_EVACUATE_IMMEDIATELY : CONST_EVERYTHING_S_IN_CHECK, gamelog);
	gamelog.newline();
}
void printWeWerentBornYesterday(const string ename) {
	clearmessagearea();
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, unnamed_String_Talk_cpp_144, gamelog);
	addstrAlt(ename, gamelog);
	addstrAlt(CONST_WEREN_T_BORN_YESTERDAY, gamelog);
	gamelog.newline();
}
void printSiegeBluff(const string aname, const int siegeType) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(singleSpace, gamelog);
	switch (siegeType)
	{
	case SIEGE_POLICE:
		addstrAlt(CONST_PRETENDS_TO_BE_PART_OF_A_POLICE_RAID, gamelog);
		break;
	case SIEGE_CIA:
		addstrAlt(CONST_PRETENDS_TO_BE_A_SECRET_AGENT, gamelog);
		break;
	case SIEGE_CCS:
	case SIEGE_HICKS:
		switch (LCSrandom(2))
		{
		case 0:
			addstrAlt(CONST_PRETENDS_TO_BE_MOUNTAIN, gamelog);
			mvaddstrAlt(17, 1, CONST_LIKE_PATRICK_SWAYZE_IN_NEXT_OF_KIN, gamelog);
			break;
		case 1:
			addstrAlt(CONST_SQUEALS_LIKE_NED_BEATTY, gamelog);
			mvaddstrAlt(17, 1, CONST_IN_DELIVERANCE, gamelog);
			break;
		}
		break;
	case SIEGE_CORPORATE:
		addstrAlt(CONST_PRETENDS_TO_BE_A_MERCENARY, gamelog);
		break;
	case SIEGE_FIREMEN:
		addstrAlt(CONST_LIGHTS_A_MATCH_AND_THROWS_IT_ON_THE_GROUND, gamelog);
		if ((!(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_END) ||
			!(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_PEAK) ||
			!(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_START) ||
			!(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_DEBRIS)) && !LCSrandom(10))
		{
			levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_FIRE_START;
			mvaddstrAlt(17, 1, CONST_THE_CARPET_SMOLDERS_THEN_BURSTS_INTO_FLAME, gamelog);
			gamelog.newline();
			mvaddstrAlt(18, 1, CONST_PERHAPS_THAT_WAS_A_BAD_IDEA, gamelog);
		}
		break;
	}
}
void printEnemyIgnoresThreat(const string tkname) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	clearmessagearea();
	mvaddstrAlt(16, 1, tkname, gamelog);
	addstrAlt(CONST_ISN_T_INTERESTED_IN_YOUR_PATHETIC_THREATS, gamelog);
	gamelog.newline();

}
void printHowShouldWeRespond(const string aname, const int hostages) {

	set_color_easy(WHITE_ON_BLACK);
	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	mvaddstrAlt(9, 1, unnamed_String_Talk_cpp_106);
	addstrAlt(aname);
	addstrAlt(CONST_RESPOND);
	mvaddstrAlt(11, 1, hostages > 1 ? (CONST_A_EXECUTE_A_HOSTAGE) : (CONST_A_EXECUTE_THE_HOSTAGE));
	mvaddstrAlt(12, 1, hostages > 1 ? (CONST_B_OFFER_TO_TRADE_THE_HOSTAGES_FOR_FREEDOM) : (CONST_B_OFFER_TO_TRADE_THE_HOSTAGE_FOR_FREEDOM));
	mvaddstrAlt(13, 1, CONST_C_NO_REPLY);
}
void printPloyWorksEnemyBacksOff() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	clearmessagearea();
	mvaddstrAlt(16, 1, CONST_THE_PLOY_WORKS_THE_CONSERVATIVES_BACK_OFF, gamelog);
	gamelog.newline();
}
void printExecutionGunshot() {
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_BLAM, gamelog);
	gamelog.newline();

}
void printExecutionBareHands() {
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, CONST_CRUNCH, gamelog);
	gamelog.newline();

}
void printDiscardsBody(const string aname, const string pname) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, aname, gamelog);
	addstrAlt(unnamed_String_Talk_cpp_115, gamelog);
	addstrAlt(pname, gamelog);
	addstrAlt(unnamed_String_Talk_cpp_116, gamelog);
	gamelog.newline();
}
void printAnotherOneBacksOff(const string ename) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);

	clearmessagearea();
	mvaddstrAlt(16, 1, ename, gamelog);
	addstrAlt(singleSpace + pickrandom(backs_off), gamelog);
}
void printThreatenEnemy(const string aname) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(COLON_SPACE, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	switch (LCSrandom(4))
	{
	case 0:
	{   // Formatting the slogan so that it always has quotes around it and punctuation
		if (slogan_str[0] != '"') mvaddcharAlt(17, 1, '"');
		mvaddstrAlt(17, 1 + (slogan_str[0] != '"' ? 1 : 0), slogan_str, gamelog);
		const int last = len(slogan_str);
		if (last && slogan_str[last - 1] != '"' && slogan_str[last - 1] != '!' && slogan_str[last - 1] != '.' && slogan_str[last - 1] != '?')
			addcharAlt('!', gamelog);
		if (last && slogan_str[last - 1] != '"') addcharAlt('"', gamelog);
		if (!sitestory->claimed)
			sitestory->claimed = 1;
		break;
	}
	default:
		mvaddstrAlt(17, 1, pickrandom(come_at_me_bro), gamelog);
		break;
	}
}
void printHostageNegotiation(const string ename, const int etype, const int ealign, const int hostages) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	clearmessagearea();
	mvaddstrAlt(16, 1, ename, gamelog);
	addstrAlt(COLON_SPACE, gamelog);
	if (ealign != ALIGN_CONSERVATIVE ||
		(etype == CREATURE_SECRET_SERVICE && exec[EXEC_PRESIDENT] > ALIGN_CONSERVATIVE))
	{
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		mvaddstrAlt(17, 1, pickrandom(please_spare_hostage), gamelog);
	}
	else
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		if (((etype == CREATURE_DEATHSQUAD ||
			etype == CREATURE_AGENT ||
			etype == CREATURE_MERC ||
			etype == CREATURE_CCS_ARCHCONSERVATIVE ||
			etype == CREATURE_GANGUNIT))
			&& ealign == ALIGN_CONSERVATIVE)
		{
			mvaddstrAlt(17, 1, pickrandom(who_cares_about_hostage), gamelog);
		}
		else
		{
			string moreHostageQuestions;
			if (LCSrandom(5)) {
				moreHostageQuestions = (pickrandom(hostage_negotiation));
			}
			else {
				if (hostages > 1)
					moreHostageQuestions = (CONST_RELEASE_YOUR_HOSTAGES_AND_NOBODY_GETS_HURT);
				else moreHostageQuestions = (CONST_LET_THE_HOSTAGE_GO_AND_NOBODY_GETS_HURT);
			}
			mvaddstrAlt(17, 1, moreHostageQuestions, gamelog);
		}
	}
	gamelog.newline();
}
void printThreatenHostages(const string aname) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname + COLON_SPACE, gamelog);
	{
		string anotherHostageThing;
		switch (LCSrandom(6))
		{
		case 0:anotherHostageThing = (CONST_DON_T_PUSH_THE_LCS);
			if (!sitestory->claimed)sitestory->claimed = 1; break;
		case 1:
			if (lawList[LAW_FREESPEECH] == -2)anotherHostageThing = (CONST_DON_T_PLAY_WITH_ME);
			else anotherHostageThing = (CONST_DON_T_FUCK_WITH_ME);
			break;
		default:
			anotherHostageThing = (pickrandom(threaten_hostage));
			break;
		}
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		mvaddstrAlt(17, 1, anotherHostageThing, gamelog);
	}
	gamelog.newline();
}
void printReleaseHostagesHeader(const string ename) {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, ename, gamelog);
	addstrAlt(COLON_SPACE, gamelog);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, pickrandom(agree_to_release_hostages), gamelog);
	gamelog.newline();
}
void printReleaseHostagesFooter(const int hostages) {

	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, hostages > 1 ? CONST_THE_SQUAD_RELEASES_ALL_HOSTAGES_IN_THE_TRADE : CONST_THE_SQUAD_RELEASES_THE_HOSTAGE_IN_THE_TRADE, gamelog);
	gamelog.newline();
}
void printEnemyAllowsHostagesToDie(const string ename) {
	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, ename, gamelog);
	addstrAlt(COLON_SPACE, gamelog);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, pickrandom(go_ahead_and_die), gamelog);
	gamelog.newline();
}
void printLetUsGoAndTheyGoFree(const string aname, const int hostages) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, aname, gamelog);
	addstrAlt(COLON_SPACE, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	{
		string nameHostages;
		if (LCSrandom(5))
		{
			if (hostages > 1) nameHostages = (CONST_BACK_OFF_AND_WE_LL_LET_THE_HOSTAGES_GO);
			else nameHostages = (CONST_BACK_OFF_AND_THE_HOSTAGE_GOES_FREE);
		}
		else {
			nameHostages = (pickrandom(let_hostages_go));
		}
		mvaddstrAlt(17, 1, nameHostages, gamelog);
	}
	gamelog.newline();

}
void printEnemyWatchesHostageDeath(const string ename) {
	clearmessagearea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(16, 1, ename, gamelog);
	addstrAlt(COLON_SPACE, gamelog);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, lawList[LAW_FREESPEECH] > ALIGN_ARCHCONSERVATIVE ? CONST_FUCK : unnamed_String_Talk_cpp_118, gamelog);
	addstrAlt(pickrandom(please_no_more), gamelog);
	gamelog.newline();
}

void printAcceptsPickupLine(const string aname, const string tkname, const vector<string> selected_flirt) {
	const bool extraline = (selected_flirt[1].empty() ? 0 : 1);
	int y = 13 + (extraline ? 1 : 0); 
	printRespondantName(tkname, extraline);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(y++, 1, selected_flirt[2], gamelog);
	gamelog.newline();
	pressAnyKey();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	++y;
	mvaddstrAlt(y++, 1, aname, gamelog);
	addstrAlt(unnamed_String_Talk_cpp_069, gamelog);
	addstrAlt(tkname, gamelog);
	addstrAlt(CONST_MAKE_PLANS_FOR_TONIGHT, gamelog);

	if (isPrisoner(tkname))
	{
		addstrAlt(unnamed_String_Talk_cpp_071, gamelog);
		mvaddstrAlt(y++, 1, tkname, gamelog);
		addstrAlt(CONST_BREAKS_FOR_THE_EXIT, gamelog);
	}
	addstrAlt(unnamed_String_Talk_cpp_073, gamelog);
	gamelog.newline();
}
void printRejectsPickupLine(const string tkname, const int tktype, const int agender_liberal, const vector<string> selected_flirt) {

	const bool extraline = (selected_flirt[1].empty() ?  0 : 1);
	int y = 13 + (extraline ? 1 : 0);
	printRespondantName(tkname, extraline);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	if (tktype == CREATURE_CORPORATE_CEO)
	{
		if (agender_liberal != GENDER_MALE)
			mvaddstrAlt(y, 1, CONST_I_M_A_HAPPILY_MARRIED_MAN_SWEETIE, gamelog);
		else mvaddstrAlt(y, 1, CONST_THIS_AIN_T_BROKEBACK_MOUNTAIN_SON, gamelog);
	}
	else
	{
		mvaddstrAlt(y++, 1, selected_flirt[3], gamelog);
		if (! selected_flirt[4].empty()) {
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(y, 1, selected_flirt[4], gamelog);
		}
	}
	gamelog.newline();
}
void printSaysWhat(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_WHAT, gamelog);
	gamelog.newline();
}

//todo add the asker and the asked name?
void printWontTalk(const int tkalign) {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	if (tkalign == ALIGN_LIBERAL || tkalign == ALIGN_ELITELIBERAL)
	{
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		mvaddstrAlt(11, 1, CONST_TOO_LIBERAL_FOR_DEBATE, gamelog);
	}
	else if (tkalign == ALIGN_CONSERVATIVE || tkalign == ALIGN_ARCHCONSERVATIVE)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		mvaddstrAlt(11, 1, CONST_TOO_CONSERVATIVE_FOR_DEBATE, gamelog);
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(11, 1, CONST_TOO_MODERATE_FOR_DEBATE, gamelog);
	}
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
}

//todo add the asker and the asked name?
void printWontDate(const int tkalign) {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	if (tkalign == ALIGN_LIBERAL || tkalign == ALIGN_ELITELIBERAL)
	{
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		mvaddstrAlt(11, 1, CONST_TOO_LIBERAL_FOR_DATE, gamelog);
	}
	else if (tkalign == ALIGN_CONSERVATIVE || tkalign == ALIGN_ARCHCONSERVATIVE)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		mvaddstrAlt(11, 1, CONST_TOO_CONSERVATIVE_FOR_DATE, gamelog);
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(11, 1, CONST_TOO_MODERATE_FOR_DATE, gamelog);
	}
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
}

void printTurnsAway(const string tkname, const int tkalign) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	if (isPrisoner(tkname))
	{
		if (tkalign == ALIGN_LIBERAL)
			mvaddstrAlt(13, 1, CONST_NOW_S_NOT_THE_TIME, gamelog);
		else mvaddstrAlt(13, 1, CONST_LEAVE_ME_ALONE, gamelog);
	}
	else mvaddstrAlt(13, 1, unnamed_String_Talk_cpp_064, gamelog);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(unnamed_String_Talk_cpp_065, gamelog);
	gamelog.newline();
}
void printRejectPolicePickupLine(const string tkname, const bool extraline) {
	printRespondantName(tkname, extraline);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(13 + (extraline ? 1 : 0), 1, CONST_DIRTY_YOU_KNOW_THAT_S_ILLEGAL_OFFICER, gamelog);
	gamelog.newline();
}
void printPickupLine(const string aname, const vector<string> selected_flirt) {

	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog); addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, selected_flirt[0], gamelog);
	if (!selected_flirt[1].empty()) {
		mvaddstrAlt(11, 1, selected_flirt[1], gamelog);
	}
	gamelog.newline();
}
void printNonHumanRejection(const string tkname, const int tktype, const bool extraline) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(12 + (extraline ? 1 : 0), 1, tkname, gamelog);
	switch (tktype)
	{
	case CREATURE_TANK:
		addstrAlt(CONST_SHAKES_ITS_TURRET_A_FIRM_NO, gamelog);
		break;
	case CREATURE_GUARDDOG:
		addstrAlt(saysComma, gamelog);
		set_color_easy(RED_ON_BLACK_BRIGHT);
		mvaddstrAlt(13 + (extraline ? 1 : 0), 1, pickrandom(dog_rejection), gamelog);
		break;
	case CREATURE_GENETIC:
		addstrAlt(saysComma, gamelog);
		set_color_easy(RED_ON_BLACK_BRIGHT);
		mvaddstrAlt(13 + (extraline ? 1 : 0), 1, pickrandom(mutant_rejection), gamelog);
		break;
	default:
		addstrAlt(CONST_DOESN_T_QUITE_PICK_UP_ON_THE_SUBTEXT, gamelog);
	}
	gamelog.newline();
}
void printAnimalDoesntUnderstand(const string tkname, const int tktype) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(12, 1, tkname, gamelog);
	switch (tktype)
	{
	case CREATURE_TANK: addstrAlt(CONST_RUMBLES_DISINTERESTEDLY, gamelog); break;
	case CREATURE_GUARDDOG: addstrAlt(CONST_BARKS, gamelog); break;
	default: addstrAlt(CONST_DOESN_T_UNDERSTAND, gamelog); break;
	}
	gamelog.newline();
}
void printWannaHearSomething(const string aname) {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_DO_YOU_WANT_TO_HEAR_SOMETHING_DISTURBING, gamelog);
	gamelog.newline();
}
void printLetMeSellYouAGun(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_WHAT_EXACTLY_DO_YOU_NEED, gamelog);
	gamelog.newline();
}
void printNotHereDummy(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_UHHH_NOT_A_GOOD_PLACE_FOR_THIS, gamelog);
	gamelog.newline();

}
void printWaitUntilItCoolsDown(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_WE_CAN_TALK_WHEN_THINGS_ARE_CALM, gamelog);
	gamelog.newline();

}
void printIDontSellToCops(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_I_DON_T_SELL_GUNS_OFFICER, gamelog);
	gamelog.newline();
}
void printIDontSellToNaked(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_JESUS, gamelog);
	gamelog.newline();
}
void printINeedAGun(const string aname) {

	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog); addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_HEY_I_NEED_A_GUN, gamelog);
	gamelog.newline();
}
void printJesusItsYours(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_JESUS_IT_S_YOURS, gamelog);
	gamelog.newline();
}
void printIWantYouToLeave(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_I_THINK_YOU_D_BETTER_LEAVE, gamelog);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(CONST_CROSSES_ARMS, gamelog);
	gamelog.newline();
}
void printGiveMeTheLCSPrice(const string aname) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_WHAT_S_THE_PRICE_FOR_THE_LIBERAL_CRIME_SQUAD, gamelog);
	gamelog.newline();
}
void printThreatensWithAGun(const string aname, const string aweapon) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(unnamed_String_Talk_cpp_045, gamelog);
	addstrAlt(aweapon, gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.newline();

}
void printRefuseRentDeal(const string aname) {

	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_WHOA_I_WAS_LOOKING_FOR_SOMETHING_CHEAPER, gamelog);
	gamelog.newline();
}
void printNotMyProblem(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_NOT_MY_PROBLEM, gamelog);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(unnamed_String_Talk_cpp_044, gamelog);
	gamelog.newline();
}
void printAcceptRentHeader(const string aname) {

	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog); addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_I_LL_TAKE_IT, gamelog);
	gamelog.newline();
}
void printAcceptRentFooter(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_RENT_IS_DUE_BY_THE_THIRD_OF_EVERY_MONTH, gamelog);
	gamelog.newline();
	mvaddstrAlt(14, 1, CONST_WE_LL_START_NEXT_MONTH, gamelog);
	gamelog.newline();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(CONST_TURNS_AWAY);

}
void printRentingOptions(const bool cannotAfford) {

	if (cannotAfford) {
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
	}
	mvaddstrAlt(11, 1, CONST_A_ACCEPT);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(12, 1, CONST_B_DECLINE);
	mvaddstrAlt(13, 1, CONST_C_THREATEN_THE_LANDLORD);
}
void printINeedThisMuchRent(const string tkname, const int rent) {

	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_IT_LL_BE, gamelog);
	addstrAlt(rent, gamelog);
	addstrAlt(CONST_A_MONTH, gamelog);
	gamelog.newline();
	mvaddstrAlt(14, 1, CONST_I_LL_NEED, gamelog);
	addstrAlt(rent, gamelog);
	addstrAlt(CONST_NOW_AS_A_SECURITY_DEPOSIT, gamelog);
	gamelog.newline();
}
void printPutSomeDamnClothesOn(const string tkname) {
	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_PUT_SOME_CLOTHES_ON_BEFORE_I_CALL_THE_COPS, gamelog);
	gamelog.newline();
}
void printIWantToRent(const string aname) {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_I_D_LIKE_TO_RENT_A_ROOM, gamelog);
	gamelog.newline();
}
void printClearOutYourRoom(const string tkname) {

	printRespondantName(tkname);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	mvaddstrAlt(13, 1, CONST_ALRIGHT_PLEASE_CLEAR_OUT_YOUR_ROOM, gamelog);
	gamelog.newline();
}
void printYourPossessionsAreRelocated() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(15, 1, CONST_YOUR_POSSESSIONS_AT_THIS_LOCATION_HAVE_BEEN_MOVED_TO_THE_SHELTER, gamelog);
	gamelog.newline();
}
void printIWantToCancelRent(const string aname) {

	clearcommandarea();
	clearmessagearea();
	clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_I_D_LIKE_CANCEL_MY_ROOM, gamelog);
	gamelog.newline();
}
void printTalkToPotentialLandlord(const bool is_naked) {
	mvaddstrAlt(14, 1, CONST_D_RENT_A_ROOM);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
}
void printTalkToLandlord(const bool is_naked) {
	mvaddstrAlt(14, 1, CONST_D_STOP_RENTING_A_ROOM);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
}
void printTalkToGangMemberOrMerc(const bool is_naked) {
	mvaddstrAlt(14, 1, CONST_D_BUY_WEAPONS);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
}
void printTalkToBankTeller(const bool is_naked) {
	mvaddstrAlt(14, 1, CONST_D_ROB_THE_BANK);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
}
void printTalkToHeader(const string aname) {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname);
	addstrAlt(CONST_TALKS_TO);

}
void printTalkToMiddle(const int tkalign, const string tkname, const string tkbio) {
	set_color_easy_alignment(tkalign);
	addstrAlt(tkname);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(tkbio);
	addstrAlt(unnamed_String_Talk_cpp_017);
}
void printTalkToFooter(const bool is_naked, const bool can_date) {

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(11, 1, CONST_A_STRIKE_UP_A_CONVERSATION_ABOUT_POLITICS);

	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
	if (can_date)set_color_easy(WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(12, 1, CONST_B_DROP_A_PICKUP_LINE);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(13, 1, CONST_C_ON_SECOND_THOUGHT_DON_T_SAY_ANYTHING);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);

}
void printBankerCooperates() {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, CONST_THE_BANK_EMPLOYEES_HESITANTLY_COOPERATE, gamelog);
	gamelog.newline();
}
void printTheVaultIsOpen() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, CONST_THE_VAULT_IS_OPEN, gamelog);
	gamelog.newline();

}
void printGuardsCloseIn() {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, CONST_THE_BANK_TELLER_AND_DIVES_FOR_COVER_AS, gamelog);
	mvaddstrAlt(10, 1, CONST_GUARDS_MOVE_IN_ON_THE_SQUAD, gamelog);
	gamelog.newline();
}
void printDemandVaultBeOpened(const string aname) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, aname, gamelog);
	addstrAlt(saysComma, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 1, unnamed_String_Talk_cpp_010, gamelog);
	addstrAlt(slogan_str, gamelog);
	gamelog.record(singleSpace);
	mvaddstrAlt(12, 1, CONST_OPEN_THE_VAULT_NOW, gamelog);
	gamelog.newline();

}
void printBrandishWeapon(const string aname, const string aweapon) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);

	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(CONST_BRANDISHES_THE, gamelog);
	addstrAlt(aweapon, gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.newline();
}
void printTellerComplies() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 1, unnamed_String_Talk_cpp_007, gamelog);
	addstrAlt(pickrandom(teller_complies), gamelog);
	mvaddstrAlt(12, 1, CONST_AND_SLIPS_SEVERAL_BRICKS_OF_CASH_INTO_THE_SQUAD_S_BAG, gamelog);
	gamelog.newline();
}
void printTellerAlertsCops() {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(11, 1, CONST_THE_BANK_TELLER_READS_THE_NOTE, gamelog);
	addstrAlt(pickrandom(teller_gestures), gamelog);
	mvaddstrAlt(12, 1, CONST_AND_DIVES_FOR_COVER_AS_THE_GUARDS_MOVE_IN_ON_THE_SQUAD, gamelog);
	gamelog.newline();
}
void printIRobTheBank(const string aname) {
	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(9, 1, aname, gamelog);
	addstrAlt(CONST_SLIPS_THE_TELLER_A_NOTE, gamelog);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(10, 1, pickrandom(robbing_bank), gamelog);
	gamelog.newline();
}
void printOptionsWithinBank(const bool is_naked) {

	clearcommandarea(); clearmessagearea(); clearmaparea();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(11, 1, CONST_A_QUIETLY_PASS_THE_TELLER_A_ROBBERY_NOTE);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
	mvaddstrAlt(12, 1, CONST_B_THREATEN_BYSTANDERS_AND_DEMAND_ACCESS_TO_THE_VAULT);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
	mvaddstrAlt(13, 1, CONST_C_ON_SECOND_THOUGHT_DON_T_ROB_THE_BANK);
	if (is_naked)addstrAlt(while_naked);
	addstrAlt(singleDot);
}


// end TALK_CPP


// TITLESCREEN_CPP
void printSaveHeader(const bool to_delete) {
	eraseAlt();
	set_color_easy(to_delete ? YELLOW_ON_RED : WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, to_delete ? deleteSave : CHOOSE_A_SAVE_FILE);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(1, 0, titleScreenLine);
}
void printSaveList(const int page, const vector<string> s_savefiles) {
	int y = 2;
	for (int p = page * 19; p < s_savefiles.size() && p < page * 19 + 19; p++, y++)
	{
		mvaddchAlt(y, 0, y + 'A' - 2);
		addstrAlt(spaceDashSpace);
		const string &strtemp = s_savefiles[p];
		addstrAlt(strtemp.substr(0, strtemp.find(dotDat)));
	}
	mvaddstrAlt(y, 0, (char(y + 'A' - 2)) + spaceDashSpace + newGame);

}
void printSaveFooter(const bool to_delete) {
	mvaddstrAlt(22, 0, (to_delete ? pressToDeleteSave : pressToSelectSave) + vToSwitchXToQuit);
	mvaddstrAlt(23, 0, addpagestr());

}
void printAreYouSure(const string s_savefiles) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrCenter(10, ARE_YOU_SURE_DELETE + s_savefiles + questionYSlashN);
}
void printMusicFooter(const bool musicEnabled) {

	string str;
	if (musicEnabled) {
		(str = pressMtoTurnOffMusic);
	}
	else {
		(str = pressMtoTurnOnMusic);
	}
	mvaddstrCenter(22, str);
}
const string discordHyperlink = "https://discord.gg/CHNcaSn";
void printTitleScreen() {
	//title screen
	eraseAlt();
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrCenter(2, liberalCrimeSquad);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrCenter(4, inspiredByOubliette);
	vector<string> quote = pickrandom(real_quote);
	mvaddstrCenter(6, quote[0]);
	mvaddstrCenter(7, quote[1]);
	mvaddstrCenter(8, quote[2]);
	mvaddstrCenter(9, quote[3]);
	mvaddstrCenter(11, copyrightTarn);
	mvaddstrCenter(12, A_BAY_12_GAMES_PRODUCTION);
	mvaddstrCenter(13, lcsHyperlink);
	mvaddstrCenter(14, lcsForumHyperlink);
	mvaddstrCenter(16, vChar + PACKAGE_VERSION_STR + maintainedByOpenSource);
	mvaddstrCenter(17, discordHyperlink);
	mvaddstrCenter(18, lcsWikiHyperlink);
	mvaddstrCenter(20, pressESCToQuit);
	mvaddstrCenter(22, pressAnyKeyToPursue);
	mvaddstrAlt(24, 79, plusChar);
}

string printNewGameHeader() {
	char savefile_temp[SAVE_FILE_NAMELEN];
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, inWhatWorld);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(1, 0, enterNameForSave);

	enter_name(2, 0, savefile_temp, SAVE_FILE_NAMELEN, NULL);
	bool justEnter = false;
	bool enterDamn = false;
	do {
		if (strcmp(savefile_temp, "") == 0) {
			eraseAlt();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(0, 0, inWhatWorld);
			string enterTheName;
			if (enterDamn) {
				enterTheName = justEnterName;
			}
			else if (justEnter) {
				enterTheName = prettyPlease;
				enterDamn = true;
			}
			else {
				enterTheName = pleaseEnterName;
			}
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(1, 0, enterTheName);
			enter_name(2, 0, savefile_temp, SAVE_FILE_NAMELEN, "");
			justEnter = true;
		}
		else {
			justEnter = false;
		}
	} while (justEnter);
	return savefile_temp + dotDat;
}
// end TITLESCREEN_CPP

enum COMMON_PRINTABLE {

	eprintTurnsAway,
	eprintTheSquadIsArrested,
	eprintTheEnemyIsFooled,
	eprintDeathSquadBluff,
	eprintLabCoatBluff,
	eprintPoliceBluff,
	eprintPloyWorksEnemyBacksOff,
	eprintExecutionGunshot,
	eprintExecutionBareHands,
	eprintYourPossessionsAreRelocated,
	eprintBankerCooperates,
	eprintTheVaultIsOpen,
	eprintGuardsCloseIn,
	eprintTellerComplies,
	eprintTellerAlertsCops,

	eprintOptionsWithinBank,
	eprintTalkToPotentialLandlord,
	eprintTalkToLandlord,
	eprintTalkToGangMemberOrMerc,
	eprintTalkToBankTeller,

	eprintOptionsWithinBankWhileNaked,
	eprintTalkToPotentialLandlordWhileNaked,
	eprintTalkToLandlordWhileNaked,
	eprintTalkToGangMemberOrMercWhileNaked,
	eprintTalkToBankTellerWhileNaked,

	eprintRentingOptions,
	eprintRentingOptionsCannotAfford,
};
void printCommonStatement(const COMMON_PRINTABLE pr) {
	switch (pr) {
	case eprintTurnsAway:
		printTurnsAway();
	break; 
	case eprintTheSquadIsArrested:
		printTheSquadIsArrested();
	break; 
	case eprintTheEnemyIsFooled:
		printTheEnemyIsFooled();
	break; 
	case eprintDeathSquadBluff:
		printDeathSquadBluff();
	break; 
	case eprintLabCoatBluff:
		printLabCoatBluff();
	break; 
	case eprintPoliceBluff:
		printPoliceBluff();
	break; 
	case eprintPloyWorksEnemyBacksOff:
		printPloyWorksEnemyBacksOff();
	break;
	case eprintExecutionGunshot:
		printExecutionGunshot();
	break;
	case eprintExecutionBareHands:
		printExecutionBareHands();
	break; 
	case eprintYourPossessionsAreRelocated:
		printYourPossessionsAreRelocated();
	break; 
	case eprintBankerCooperates:
		printBankerCooperates();
	break;
	case eprintTheVaultIsOpen:
		printTheVaultIsOpen();
	break; 
	case eprintGuardsCloseIn:
		printGuardsCloseIn();
	break;
	case eprintTellerComplies:
		printTellerComplies();
	break;
	case eprintTellerAlertsCops:
		printTellerAlertsCops();
		break;
	case eprintOptionsWithinBank:
		printOptionsWithinBank(false);
		break;
	case eprintTalkToPotentialLandlord:
		printTalkToPotentialLandlord(false);
		break;
	case eprintTalkToLandlord:
		printTalkToLandlord(false);
		break;
	case eprintTalkToGangMemberOrMerc:
		printTalkToGangMemberOrMerc(false);
		break;
	case eprintTalkToBankTeller:
		printTalkToBankTeller(false);
		break;
	case eprintOptionsWithinBankWhileNaked:
		printOptionsWithinBank(true);
		break;
	case eprintTalkToPotentialLandlordWhileNaked:
		printTalkToPotentialLandlord(true);
		break;
	case eprintTalkToLandlordWhileNaked:
		printTalkToLandlord(true);
		break;
	case eprintTalkToGangMemberOrMercWhileNaked:
		printTalkToGangMemberOrMerc(true);
		break;
	case eprintTalkToBankTellerWhileNaked:
		printTalkToBankTeller(true);
		break;
	case eprintRentingOptions:
		printRentingOptions(false);
		break;
	case eprintRentingOptionsCannotAfford:
		printRentingOptions(true);
		break;
	}
}

enum COMMON_XE_DOES_PRINTABLE {

	eprintITalkLikeAConservative,
	eprintEngraveElbereth,
	eprintWeWerentBornYesterday,
	eprintWannaHearSomething,
	eprintLetMeSellYouAGun,
	eprintNotHereDummy,
	eprintWaitUntilItCoolsDown,
	eprintIDontSellToCops,
	eprintIDontSellToNaked,
	eprintINeedAGun,
	eprintJesusItsYours,
	eprintIWantYouToLeave,
	eprintGiveMeTheLCSPrice,
	eprintEnemyIgnoresThreat,
	eprintAnotherOneBacksOff,
	eprintThreatenEnemy,
	eprintThreatenHostages,
	eprintReleaseHostagesHeader,
	eprintRefuseRentDeal,
	eprintNotMyProblem,
	eprintAcceptRentHeader,
	eprintAcceptRentFooter,
	eprintDemandVaultBeOpened,
	eprintIRobTheBank,
	eprintEnemyWatchesHostageDeath,
	eprintSaysWhat,
	eprintPutSomeDamnClothesOn,
	eprintIWantToRent,
	eprintClearOutYourRoom,
	eprintIWantToCancelRent,
	eprintEnemyAllowsHostagesToDie,
	eprintTalkToHeader,

};

void printCommonXeDoesStatement(const COMMON_XE_DOES_PRINTABLE pr, const string aname) {
	switch (pr) {

	case eprintITalkLikeAConservative:
		printITalkLikeAConservative(aname);
		break;

	case eprintEngraveElbereth:
		printEngraveElbereth(aname);
		break;

	case eprintWeWerentBornYesterday:
		printWeWerentBornYesterday(aname);
		break;

	case eprintWannaHearSomething:
		printWannaHearSomething(aname);
		break;

	case eprintLetMeSellYouAGun:
		printLetMeSellYouAGun(aname);
		break;

	case eprintNotHereDummy:
		printNotHereDummy(aname);
		break;

	case eprintWaitUntilItCoolsDown:
		printWaitUntilItCoolsDown(aname);
		break;

	case eprintIDontSellToCops:
		printIDontSellToCops(aname);
		break;

	case eprintIDontSellToNaked:
		printIDontSellToNaked(aname);
		break;

	case eprintINeedAGun:
		printINeedAGun(aname);
		break;

	case eprintJesusItsYours:
		printJesusItsYours(aname);
		break;

	case eprintIWantYouToLeave:
		printIWantYouToLeave(aname);
		break;

	case eprintGiveMeTheLCSPrice:
		printGiveMeTheLCSPrice(aname);
		break;

	case eprintEnemyIgnoresThreat:
		printEnemyIgnoresThreat(aname);
		break;

	case eprintAnotherOneBacksOff:
		printAnotherOneBacksOff(aname);
		break;

	case eprintThreatenEnemy:
		printThreatenEnemy(aname);
		break;

	case eprintThreatenHostages:
		printThreatenHostages(aname);
		break;

	case eprintReleaseHostagesHeader:
		printReleaseHostagesHeader(aname);
		break;

	case eprintRefuseRentDeal:
		printRefuseRentDeal(aname);
		break;

	case eprintNotMyProblem:
		printNotMyProblem(aname);
		break;

	case eprintAcceptRentHeader:
		printAcceptRentHeader(aname);
		break;

	case eprintAcceptRentFooter:
		printAcceptRentFooter(aname);
		break;

	case eprintDemandVaultBeOpened:
		printDemandVaultBeOpened(aname);
		break;

	case eprintIRobTheBank:
		printIRobTheBank(aname);
		break;

	case eprintEnemyWatchesHostageDeath:
		printEnemyWatchesHostageDeath(aname);
		break;

	case eprintSaysWhat:
		printSaysWhat(aname);
		break;

	case eprintPutSomeDamnClothesOn:
		printPutSomeDamnClothesOn(aname);
		break;

	case eprintIWantToRent:
		printIWantToRent(aname);
		break;

	case eprintClearOutYourRoom:
		printClearOutYourRoom(aname);
		break;

	case eprintIWantToCancelRent:
		printIWantToCancelRent(aname);
		break;

	case eprintEnemyAllowsHostagesToDie:
		printEnemyAllowsHostagesToDie(aname);
		break;

	case eprintTalkToHeader:
		printTalkToHeader(aname);
		break;
	}
}

void printStuff(std::string str) {
	mvaddstrAlt(0, 0, str);
}