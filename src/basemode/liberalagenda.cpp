
// Note: this file is encoded in the PC-8 / Code Page 437 / OEM-US character set
// (The same character set used by Liberal Crime Squad when it is running)
// Certain special characters won't display correctly unless your text editor is
// set to use that character set, such as this e with an accent: Ã©
// In Windows Notepad with the Terminal font, OEM/DOS encoding it should work fine.
// You can set this in Notepad by going to Format->Font and choosing the Terminal font,
// then choosing OEM/DOS in the Script dropdown box.
// In Notepad++ go to the Encoding menu, Character sets, Western European, OEM-US... easy!
// In Code::Blocks's editor go to Settings->Editor->the Other Settings tab and
// then pick WINDOWS-437 from the dropdown box and then choose the radio button
// to make this the default encoding and disable auto-detection of the encoding.

#include "../includes65.h"
#include "../constStringliberalagenda.h"
#include <algorithm>
/* base - liberal agenda - disband */
bool confirmdisband()
{
	string word = pickrandom(issue_phrases);
	for (int pos = 0; pos < len(word);)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, CONST_ARE_YOU_SURE_YOU_WANT_TO_DISBAND);
		set_color_easy(WHITE_ON_BLACK);
		for (int i = 0; i < len(disbandingMessage); i++) {
			mvaddstrAlt(i + 2, 0, disbandingMessage[i]);
		}
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(13, 0, CONST_TYPE_THIS_LIBERAL_PHRASE_TO_CONFIRM_PRESS_A_WRONG_LETTER_TO_RETHINK_IT);
		for (int x = 0; x < len(word); x++)
		{
			if (x == pos) set_color_easy(GREEN_ON_BLACK);
			else if (x < pos) set_color_easy(GREEN_ON_BLACK_BRIGHT);
			else set_color_easy(WHITE_ON_BLACK);
			mvaddcharAlt(15, x, word[x]);
		}
		if (getkeyAlt() == ::tolower(word[pos]))
		{
			pos++;
			if (word[pos] == ' ' || word[pos] == '\'' || word[pos] == '-') pos++;
		}
		else return false;
	}
	//SET UP THE DISBAND
	CreaturePool::getInstance().setupDisband();
	cleangonesquads();
	disbandtime = year;
	return true;
}
void printDisbandOption() {

	moveAlt(23, 0);
	if (stalinmode)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(CONST_X_STALINIST_SPACE);
	}
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	addstrAlt(CONST_X_ELITE_LIBERAL_SPACE);
	if (!stalinmode)
	{
		set_color_easy(WHITE_ON_BLACK);
		addstrAlt(DASH_SPACE);
	}
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	addstrAlt(CONST_X_LIBERAL_SPACE);
	if (!stalinmode)
	{
		set_color_easy(WHITE_ON_BLACK);
		addstrAlt(DASH_SPACE);
	}
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	addstrAlt(CONST_X_MODERATE_SPACE);
	if (!stalinmode)
	{
		set_color_easy(WHITE_ON_BLACK);
		addstrAlt(DASH_SPACE);
	}
	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	addstrAlt(CONST_X_CONSERVATIVE_SPACE);
	if (!stalinmode)
	{
		set_color_easy(WHITE_ON_BLACK);
		addstrAlt(DASH_SPACE);
	}
	set_color_easy(RED_ON_BLACK_BRIGHT);
	addstrAlt(CONST_ARCH_CONSERVATIVE);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(24, 0, CONST_PRESS_D_TO_DISBAND_AND_WAIT_USE_CURSORS_FOR_OTHER_PAGES_ANY_OTHER_KEY_TO_EXIT);
}
void printLaws(const int startinglaw, const signed char won) {
	for (int l = startinglaw, y = 4; l < startinglaw + 18 && l < LAWNUM; l++, y++)
	{
		if (won == -1 || won == -2)
			set_alignment_color(ALIGN_ARCHCONSERVATIVE, true);
		else set_alignment_color(lawList[l], true);
		moveAlt(y, 0);
		if (won == -2)addstrAlt(endgameLawStrings[l][0]);
		else if (won == -1)addstrAlt(endgameLawStrings[l][1]);
		else if (lawList[l] == ALIGN_ARCHCONSERVATIVE)
			addstrAlt(endgameLawStrings[l][2]);
		else if (lawList[l] == -1)addstrAlt(endgameLawStrings[l][3]);
		else if (lawList[l] == 0)addstrAlt(endgameLawStrings[l][4]);
		else if (lawList[l] == 1)addstrAlt(endgameLawStrings[l][5]);
		else if (won != 1 || wincondition != WINCONDITION_ELITE)addstrAlt(endgameLawStrings[l][6]);
		else addstrAlt(endgameLawStrings[l][7]);
	}
}
void printReplacements(const signed char won) {
	if (won == -1)
	{
		mvaddstrAlt(7, 65, CONST_REPLACED);
		mvaddstrAlt(8, 63, CONST_BY_CORPORATE);
		mvaddstrAlt(9, 62, CONST_ETHICS_OFFICERS);
	}
	else if (won == -2)
	{
		mvaddstrAlt(7, 63, CONST_REPLACED_BY);
		mvaddstrAlt(8, 62, CONST_STALINIST_SHOW);
		mvaddstrAlt(9, 63, CONST_TRIAL_JUDGES);
	}
	else
	{
		for (int c = 0, y = 4; c < COURTNUM; c++, y++)
		{
			set_alignment_color(court[c], true);
			mvaddstrAlt(y, 60, courtname[c]);
		}
	}
}
void printLeadersWithoutVictor() {

	signed char align;

	int housemake[6] = { 0,0,0,0,0,0 };
	for (int h = 0; h < HOUSENUM; h++) housemake[house[h] + 2]++;
	if (housemake[5] + min(housemake[0], housemake[4]) >= HOUSEMAJORITY) align = ALIGN_STALINIST; // Stalinists have a majority (perhaps with help from extremists on both sides)
	else if (housemake[0] >= HOUSEMAJORITY) align = ALIGN_ARCHCONSERVATIVE; // Arch-Conservatives have a majority
	else if (housemake[4] >= HOUSEMAJORITY) align = ALIGN_ELITELIBERAL; // Elite Liberals have a majority
	else if (housemake[0] + housemake[1] >= HOUSEMAJORITY) align = ALIGN_CONSERVATIVE; // Conservatives plus Arch-Conservatives have a majority
	else if (housemake[3] + housemake[4] >= HOUSEMAJORITY) align = ALIGN_LIBERAL; // Liberals plus Elite Liberals have a majority
	else align = ALIGN_MODERATE; // nobody has a majority
	set_alignment_color(align, true);
	mvaddstrAlt(10, 0, CONST_X_HOUSE_COLON);
	if (stalinmode) addstrAlt(tostring(housemake[5]) + tag_Sta);
	addstrAlt(tostring(housemake[4]) + tag_Libp);
	addstrAlt(tostring(housemake[3]) + tag_Lib);
	addstrAlt(tostring(housemake[2]) + tag_Mod);
	addstrAlt(tostring(housemake[1]) + tag_Cons);
	addstrAlt(tostring(housemake[0]) + tag_Consp);
	int senatemake[6] = { 0,0,0,0,0,0 };
	for (int s = 0; s < SENATENUM; s++) senatemake[senate[s] + 2]++;
	senatemake[exec[EXEC_VP] + 2]++; // Vice President is tie-breaking vote in the Senate
	if (senatemake[5] + min(senatemake[0], senatemake[4]) >= SENATEMAJORITY) align = ALIGN_STALINIST; // Stalinists have a majority (perhaps with help from extremists on both sides)
	else if (senatemake[0] >= SENATEMAJORITY) align = ALIGN_ARCHCONSERVATIVE; // Arch-Conservatives have a majority
	else if (senatemake[4] >= SENATEMAJORITY) align = ALIGN_ELITELIBERAL; // Elite Liberals have a majority
	else if (senatemake[0] + senatemake[1] >= SENATEMAJORITY) align = ALIGN_CONSERVATIVE; // Conservatives plus Arch-Conservatives have a majority
	else if (senatemake[3] + senatemake[4] >= SENATEMAJORITY) align = ALIGN_LIBERAL; // Liberals plus Elite Liberals have a majority
	else align = ALIGN_MODERATE; // nobody has a majority
	set_alignment_color(align, true);
	senatemake[exec[EXEC_VP] + 2]--; // Vice President isn't actually a Senator though
	mvaddstrAlt(11, 0, CONST_X_SENATE_COLON);
	if (stalinmode) addstrAlt(tostring(senatemake[5]) + tag_Sta);
	addstrAlt(tostring(senatemake[4]) + tag_Libp);
	addstrAlt(tostring(senatemake[3]) + tag_Lib);
	addstrAlt(tostring(senatemake[2]) + tag_Mod);
	addstrAlt(tostring(senatemake[1]) + tag_Cons);
	addstrAlt(tostring(senatemake[0]) + tag_Consp);

}
void printLeadersFirstPage(const signed char won) {


	signed char align;

	moveAlt(5, 0);
	if (won == -1) addstrAlt(CONST_KING);
	else if (won == -2) addstrAlt(CONST_GENERAL_SECRETARY);
	else
	{
		addstrAlt(CONST_PRESIDENT);
		if (execterm == 1)addstrAlt(CONST_1ST_TERM);
		else addstrAlt(CONST_2ND_TERM);
	}
	if (won == -2) moveAlt(5, 30);
	else mvaddstrAlt(5, 25, execname[EXEC_PRESIDENT]);
	align = exec[EXEC_VP];
	set_alignment_color(align, true);
	moveAlt(6, 0);
	if (won == -1) addstrAlt(CONST_MINISTER_OF_LOVE);
	else if (won == -2) addstrAlt(CONST_PREMIER);
	else addstrAlt(CONST_VICE_PRESIDENT);
	if (won == -2) moveAlt(6, 30);
	else mvaddstrAlt(6, 25, execname[EXEC_VP]);
	align = exec[EXEC_STATE];
	set_alignment_color(align, true);
	moveAlt(7, 0);
	if (won == -1) addstrAlt(CONST_MINISTER_OF_PEACE);
	else if (won == -2) addstrAlt(CONST_FOREIGN_AFFAIRS_COMMISSAR);
	else addstrAlt(CONST_SECRETARY_OF_STATE);
	if (won == -2) moveAlt(7, 30);
	else mvaddstrAlt(7, 25, execname[EXEC_STATE]);
	align = exec[EXEC_ATTORNEY];
	set_alignment_color(align, true);
	moveAlt(8, 0);
	if (won == -1) addstrAlt(CONST_MINISTER_OF_TRUTH);
	else if (won == -2) addstrAlt(CONST_INTERNAL_AFFAIRS_COMMISSAR);
	else addstrAlt(CONST_ATTORNEY_GENERAL);

}
void printCourtWithoutVictory() {

	signed char align;

	int courtmake[6] = { 0,0,0,0,0,0 };
	for (int s = 0; s < COURTNUM; s++) courtmake[court[s] + 2]++;
	if (courtmake[5] + min(courtmake[0], courtmake[4]) >= COURTMAJORITY) align = ALIGN_STALINIST; // Stalinists have a majority (perhaps with help from extremists on both sides)
	else if (courtmake[0] >= COURTMAJORITY) align = ALIGN_ARCHCONSERVATIVE; // Arch-Conservatives have a majority
	else if (courtmake[4] >= COURTMAJORITY) align = ALIGN_ELITELIBERAL; // Elite Liberals have a majority
	else if (courtmake[0] + courtmake[1] >= COURTMAJORITY) align = ALIGN_CONSERVATIVE; // Conservatives plus Arch-Conservatives have a majority
	else if (courtmake[3] + courtmake[4] >= COURTMAJORITY) align = ALIGN_LIBERAL; // Liberals plus Elite Liberals have a majority
	else align = ALIGN_MODERATE; // nobody has a majority
	set_alignment_color(align, true);
}
void printSingleLaw(const signed char won, const int l) {
	if (won == -1 || won == -2)
		set_alignment_color(ALIGN_ARCHCONSERVATIVE, true);
	else if (won == 1 && wincondition == WINCONDITION_ELITE)
		set_alignment_color(ALIGN_ELITELIBERAL, true);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(14 + l / 3, l % 3 * 26, "\x11ÄÄÄÄÄ\x10");
	if (won == -1 || won == -2)
		set_alignment_color(ALIGN_ARCHCONSERVATIVE, true);
	else set_alignment_color(lawList[l], true);
	addstrAlt(getlaw(l));
	mvaddcharAlt(14 + l / 3, l % 3 * 26 + 3 - lawList[l], 'O');
}
void printPageLeaders(const signed char won) {



	mvaddstrAlt(1, 0, FORMATTED_LINE);
	mvaddstrAlt(2, 0, GENERAL_SUMMARY_ISSUES_HEADER);
	mvaddstrAlt(3, 0, CONST_X_GEN_SUM_FOOTER);
	set_alignment_color(exec[EXEC_PRESIDENT], true);
	printLeadersFirstPage(won);
	if (won == -2) moveAlt(8, 30);
	else mvaddstrAlt(8, 25, execname[EXEC_ATTORNEY]);
	if (won == -1)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		mvaddstrAlt(10, 0, CONST_THE_CONGRESS_CONSISTS_OF_CEOS_AND_TELEVANGELISTS);
	}
	else if (won == -2)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		mvaddstrAlt(10, 0, CONST_THE_CONGRESS_CONSISTS_OF_STALINIST_PARTY_LOYALISTS);
	}
	else
	{
		printLeadersWithoutVictor();
	}
	if (won == -1 || won == -2) set_color_easy(RED_ON_BLACK_BRIGHT);
	else if (won == 1) set_color_easy(GREEN_ON_BLACK_BRIGHT);
	else
	{
		printCourtWithoutVictory();
	}
	for (int i = 0; i < len(supremeChars); i++) {
		mvaddstrAlt(5 + i, 56, supremeChars[i]);
	}
	for (int i = 0; i < len(courtChars); i++) {
		mvaddstrAlt(6 + i, 58, courtChars[i]);
	}
	printReplacements(won);
	for (int l = 0; l < LAWNUM; l++)
	{
		printSingleLaw(won, l);
	}
}
void printPage(const int page, const signed char won) {

	switch (page)
	{
	case PAGE_LEADERS:
	{
		printPageLeaders(won);
		break;
	}
	case PAGE_ISSUES_A:
		mvaddstrAlt(1, 0, CONST_X_GEN_SUM_HEADER_2);
		mvaddstrAlt(2, 0, CONST_X_GENERAL_SUMMARY_ISSUES_A_ISSUES_B_2);
		mvaddstrAlt(3, 0, CONST_X_GEN_SUM_FOOTER_2);


		printLaws(0, won);
		break;
	case PAGE_ISSUES_B:

		mvaddstrAlt(1, 0, CONST_X_GEN_SUM_HEADER_3);
		mvaddstrAlt(2, 0, CONST_X_GENERAL_SUMMARY_ISSUES_A_ISSUES_B_3);
		mvaddstrAlt(3, 0, CONST_X_GEN_SUM_FOOTER_3);

		printLaws(18, won);
		break;

	}
}

/* base - liberal agenda */
bool liberalagenda(signed char won)
{

	int page = 0;
	while (true)
	{
		eraseAlt();
		if (won == 1)
		{
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
			mvaddstrAlt(0, 0, CONST_THE_TRIUMPH_OF_THE_LIBERAL_AGENDA);
			music.play(MUSIC_VICTORY);
		}
		else if (won == -1 || won == -2)
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(0, 0, CONST_THE_ABJECT_FAILURE_OF_THE_LIBERAL_AGENDA);
			if (won == -1) music.play(MUSIC_REAGANIFIED);
			if (won == -2) music.play(MUSIC_STALINIZED);
		}
		else
		{
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(0, 0, CONST_THE_STATUS_OF_THE_LIBERAL_AGENDA);
			music.play(MUSIC_LIBERALAGENDA);
		}
		if (page < 0) page = PAGENUM - 1;
		if (page >= PAGENUM) page = 0;
		printPage(page, won);
		if (won == 1)
		{
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
			if (wincondition == WINCONDITION_EASY)
				mvaddstrAlt(23, 0, CONST_THE_COUNTRY_HAS_ACHIEVED_LIBERAL_STATUS);
			else mvaddstrAlt(23, 0, CONST_THE_COUNTRY_HAS_ACHIEVED_ELITE_LIBERAL_STATUS);
			mvaddstrAlt(24, 0, pressLToViewHighScores);
			int c = getkeyAlt();
			if (is_page_down(c)) page++;
			else if (is_page_up(c)) page--;
			else if (c == 'l') break;
		}
		else if (won == -1)
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(23, 0, CONST_THE_COUNTRY_HAS_BEEN_REAGANIFIED);
			mvaddstrAlt(24, 0, pressLToViewHighScores);
			int c = getkeyAlt();
			if (is_page_down(c)) page++;
			else if (is_page_up(c)) page--;
			else if (c == 'l') break;
		}
		else if (won == -2)
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(23, 0, CONST_THE_COUNTRY_HAS_BEEN_STALINIZED);
			mvaddstrAlt(24, 0, pressLToViewHighScores);
			int c = getkeyAlt();
			if (is_page_down(c)) page++;
			else if (is_page_up(c)) page--;
			else if (c == 'l') break;
		}
		else
		{
			printDisbandOption();
			int c = getkeyAlt();
			if (is_page_down(c)) page++;
			else if (is_page_up(c)) page--;
			else if (c == 'd') return confirmdisband();
			else break;
		}
	}
	return false;
}