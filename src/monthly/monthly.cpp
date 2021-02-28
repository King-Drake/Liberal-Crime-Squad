
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
// Note: this file is encoded in the PC-8 / Code Page 437 / OEM-US character set
// (The same character set used by Liberal Crime Squad when it is running)
// Certain special characters won't display correctly unless your text editor is
// set to use that character set, such as this e with an accent: é
// In Windows Notepad with the Terminal font, OEM/DOS encoding it should work fine.
// You can set this in Notepad by going to Format->Font and choosing the Terminal font,
// then choosing OEM/DOS in the Script dropdown box.
// In Notepad++ go to the Encoding menu, Character sets, Western European, OEM-US... easy!
// In Code::Blocks's editor go to Settings->Editor->the Other Settings tab and
// then pick WINDOWS-437 from the dropdown box and then choose the radio button
// to make this the default encoding and disable auto-detection of the encoding.
// Then close the file and reopen it (since Code::Blocks detects the encoding
// when it opens the file and it can't be changed after that; what we changed was
// how it detects encoding for files it opens in the future, not files already open).
// In Microsoft Visual C++, right-click the file in the Solution Explorer,
// select CONST_monthly000, choose CONST_monthlyB015,
// then choose CONST_monthly001.
// In MS-DOS Editor (included with Windows as EDIT.COM in your system32 directory),
// the codepage will be correct already since it's running in a console window just
// like Liberal Crime Squad. Well OK, the encoding might be wrong, but then it's wrong
// in Liberal Crime Squad TOO, and to fix it, go to Control Panel, Regional and Language Settings,
// Advanced tab, and choose English (United States) from the dropdown box as the encoding
// for non-Unicode applications, then press OK.
// If you have a Linux or other UNIX-based system you are obviously smart enough
// to figure out for yourself how to open a file in OEM-US PC-8 codepage 437 in
// your favorite text editor. If you're on Mac OS X, well that's UNIX-based, figure
// it out for yourself.

#include "../includes19.h"
#include "../constStringmonthly.h"
/* rename various buildings according to the new laws */

bool policeStationNeedsUpdate(short *law, short *oldlaw) {
	return ((law[LAW_POLICEBEHAVIOR] == -2 && law[LAW_DEATHPENALTY] == -2) ||
		(oldlaw[LAW_POLICEBEHAVIOR] == -2 && oldlaw[LAW_DEATHPENALTY] == -2)) &&
		(law[LAW_POLICEBEHAVIOR] != oldlaw[LAW_POLICEBEHAVIOR] ||
			law[LAW_DEATHPENALTY] != oldlaw[LAW_DEATHPENALTY]);
}
bool courthouseNeedsUpdate(short *law, short *oldlaw) {
	return (law[LAW_DEATHPENALTY] == -2 || oldlaw[LAW_DEATHPENALTY] == -2) &&
		law[LAW_DEATHPENALTY] != oldlaw[LAW_DEATHPENALTY];
}
bool fireStationNeedsUpdate(short *law, short *oldlaw) {
	return (law[LAW_FREESPEECH] == -2 || oldlaw[LAW_FREESPEECH] == -2) &&
		law[LAW_FREESPEECH] != oldlaw[LAW_FREESPEECH]
		;
}
bool prisonNeedsUpdate(short *law, short *oldlaw) {
	return (law[LAW_PRISONS] == -2 || oldlaw[LAW_PRISONS] == -2) &&
		law[LAW_PRISONS] != oldlaw[LAW_PRISONS]
		;
}
bool nuclearNeedsUpdate(short *law, short *oldlaw) {
	return (law[LAW_NUCLEARPOWER] == 2 || oldlaw[LAW_NUCLEARPOWER] == 2) &&
		law[LAW_NUCLEARPOWER] != oldlaw[LAW_NUCLEARPOWER]
		;
}
bool intelligenchqNeedsUpdate(short *law, short *oldlaw) {
	return ((law[LAW_PRIVACY] == -2 && law[LAW_POLICEBEHAVIOR] == -2) ||
		(oldlaw[LAW_PRIVACY] == -2 && oldlaw[LAW_POLICEBEHAVIOR] == -2)) &&
		(law[LAW_PRIVACY] != oldlaw[LAW_PRIVACY] ||
			law[LAW_POLICEBEHAVIOR] != oldlaw[LAW_POLICEBEHAVIOR])
		;
}
bool armyBaseNeedsUpdate(short *law, short *oldlaw) {
	return (law[LAW_MILITARY] == -2 || oldlaw[LAW_MILITARY] == -2) &&
		law[LAW_MILITARY] != oldlaw[LAW_MILITARY]
		;
}
bool pawnshopNeedsUpdate(short *law, short *oldlaw) {
	return (law[LAW_GUNCONTROL] == 2 || oldlaw[LAW_GUNCONTROL] == 2) &&
		law[LAW_GUNCONTROL] != oldlaw[LAW_GUNCONTROL]
		;
}
bool ceoHouseNeedsUpdate(short *law, short *oldlaw) {
	return ((law[LAW_CORPORATE] == -2 && law[LAW_TAX] == -2) ||
		(oldlaw[LAW_CORPORATE] == -2 && oldlaw[LAW_TAX] == -2)) &&
		(law[LAW_CORPORATE] != oldlaw[LAW_CORPORATE] ||
			law[LAW_TAX] != oldlaw[LAW_TAX])
		;
}
bool crackhouseNeedsUpdate(short *law, short *oldlaw) {
	return (law[LAW_DRUGS] == 2 || oldlaw[LAW_DRUGS] == 2) &&
		law[LAW_DRUGS] != oldlaw[LAW_DRUGS]
		;
}
void reinitializeSite(const int sitetype) {
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++)
		if (LocationsPool::getInstance().getLocationType(l) == sitetype)
			LocationsPool::getInstance().initLocation(l);
}
/* rename various buildings according to the new laws */

void updateworld_laws(short *law, short *oldlaw)
{  // NOTE: make sure to keep code here matching code in initlocation() in locations.cpp for when names are changed
	if (policeStationNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_GOVERNMENT_POLICESTATION); // Police Station or Death Squad HQ?
	if (courthouseNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_GOVERNMENT_COURTHOUSE); // Courthouse or judge hall?
	if (fireStationNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_GOVERNMENT_FIRESTATION); // Fire station or Fireman HQ?
	if (prisonNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_GOVERNMENT_PRISON); // Prison or re-ed camp?
	if (nuclearNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_INDUSTRY_NUCLEAR); // Nuclear Power Plant, or Nuclear Waste Center?
	if (intelligenchqNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_GOVERNMENT_INTELLIGENCEHQ); // Intelligence HQ or ministry of love?
	if (armyBaseNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_GOVERNMENT_ARMYBASE); // Army Base or Ministry of Peace?
	if (pawnshopNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_BUSINESS_PAWNSHOP); // Do they mention guns in the title?
	if (ceoHouseNeedsUpdate(law, oldlaw))
		reinitializeSite(SITE_CORPORATE_HOUSE); // CEO house or CEO Castle?
	if (crackhouseNeedsUpdate(law, oldlaw))
		for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++)
			if (LocationsPool::getInstance().getLocationType(l) == SITE_BUSINESS_CRACKHOUSE  // Crack House, or Recreational Drugs Center?
				&& LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,l) < 0) // Only rename locations not under LCS control, to avoid switching names around under the player
				LocationsPool::getInstance().initSite(l);
}
void publicOpinionNaturalMoves(int(&issuebalance)[VIEWNUM - 5],
	int(&libpower)[VIEWNUM],
	int &conspower,
	int &mediabalance) {

	for (int v = 0; v < VIEWNUM; v++)
	{
		// Liberal essays add their power to the effect of sleepers
		libpower[v] += background_liberal_influence[v];
		background_liberal_influence[v] = static_cast<short>(background_liberal_influence[v] * 0.66);
		if (v == VIEW_LIBERALCRIMESQUADPOS) continue;
		if (v == VIEW_LIBERALCRIMESQUAD) continue;
		//if(v==VIEW_POLITICALVIOLENCE)
		//{
		//   change_public_opinion(VIEW_POLITICALVIOLENCE,-1,0);
		//   continue;
		//}
		if (v == VIEW_CONSERVATIVECRIMESQUAD) continue;
		if (v != VIEW_AMRADIO && v != VIEW_CABLENEWS)
		{
			issuebalance[v] = libpower[v] - conspower;
			mediabalance += issuebalance[v];
			// Heavy randomization -- balance of power just biases the roll
			int roll = issuebalance[v] + LCSrandom(400) - 200;
			// If +/-50 to either side, that side wins the tug-of-war
			if (roll < -50)
				change_public_opinion(v, -1, 0);
			else if (roll > 50)
				change_public_opinion(v, 1, 0);
			else // Else random movement
				change_public_opinion(v, LCSrandom(2) * 2 - 1, 0);
		}
		// AM Radio and Cable News popularity slowly shift to reflect public
		// opinion over time -- if left unchecked, their subtle influence
		// on society will become a self-perpetuating Conservative nightmare!
		else if (v == VIEW_AMRADIO || v == VIEW_CABLENEWS)
		{
			if (publicmood(-1) < attitude[v])change_public_opinion(v, -1);
			else change_public_opinion(v, 1);
		}
	}
}

void print_labels_on_bottom_of_screen() {

	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	mvaddstrAlt(23, 0, CONST_ELITE_LIBERAL_UPPERCASE_SPACE);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(CONST_DASH_SPACE_SPACE);
	set_color_easy(CYAN_ON_BLACK_BRIGHT);
	addstrAlt(CONST_LIBERAL_UPPERCASE_SPACE);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(CONST_DASH_SPACE_SPACE);
	set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	addstrAlt(CONST_MODERATE_SPACE);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(CONST_DASH_SPACE_SPACE);
	set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
	addstrAlt(CONST_CONSERVATIVE_UPPERCASE_SPACE);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(CONST_DASH_SPACE_SPACE);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	addstrAlt(CONST_ARCH_CONSERVATIVE_UPPERCASE);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THESE_POLL_NUMBERS);
}
void printIntelligenceReport(char &clearformess) {
	/*******************************************************
	*                 INTELLIGENCE REPORT                  *
	*     ONLY IF SHOWMECHANICS OR SHOWWAIT IS DEFINED     *
	*        EYES ONLY - LCS PROPERTY - TOP SECRET         *
	*******************************************************/

	music.play(MUSIC_ELECTIONS);
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 23, CONST_LCS_MONTHLY_INTELLIGENCE_REPORT);
	mvaddstrAlt(2, 27, CONST_CURRENT_POLITICAL_TRENDS);
	int numviews = (endgamestate >= ENDGAME_CCS_DEFEATED || newscherrybusted < 2) ? VIEWNUM - 1 : VIEWNUM;
	for (int v = -1 - stalinmode, y = 4, x = 0, pip; v < numviews; v++)
	{
		if ((y - 4) * 2 >= numviews + 1 + stalinmode) y = 4, x = 40;
		for (pip = 2; pip >= -2; pip--)
		{
			set_alignment_color(pip, true);
			if (pip == 2) mvaddcharAlt(y, x + 22, '\x11');
			addstrAlt(CONST_THREE_CHARACTER_LINE);
			if (pip == -2) addcharAlt('\x10');
		}
		if (v >= 0) pip = 14 - (attitude[v] * 14) / 100;
		else pip = 14 - (publicmood(v) * 14) / 100;
		set_alignment_color((14 - pip) / 3 - 2, true);
		mvaddstrAlt(y, x, getview(v, false));
		mvaddcharAlt(y++, x + 23 + pip, 'O');
	}
	print_labels_on_bottom_of_screen();
	clearformess = 1;
	pressAnyKey();
}
void updateEndgamestate() {

	switch (endgamestate)
	{
	case ENDGAME_NONE:
		if (publicmood(-1) > 60)
		{
			endgamestate = ENDGAME_CCS_APPEARANCE;
			attitude[VIEW_CONSERVATIVECRIMESQUAD] = 0;
		}
		break;
	case ENDGAME_CCS_APPEARANCE:
		if (publicmood(-1) > 80)
			endgamestate = ENDGAME_CCS_ATTACKS;
		break;
	case ENDGAME_CCS_ATTACKS:
		if (publicmood(-1) > 90)
			endgamestate = ENDGAME_CCS_SIEGES;
		break;
	case ENDGAME_CCS_SIEGES:
	case ENDGAME_CCS_DEFEATED:
		//if(publicmood(-1)>85&&presparty!=LIBERAL_PARTY)
		//   endgamestate=ENDGAME_MARTIALLAW;
		break;
	}
}
void long_disband_loss() {


	music.play(MUSIC_DEFEAT);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	eraseAlt();
	mvaddstrAlt(12, 10, CONST_THE_LIBERAL_CRIME_SQUAD_IS_NOW_JUST_A_MEMORY, gamelog);
	gamelog.newline();
	pressAnyKey();
	set_color_easy(WHITE_ON_BLACK);
	eraseAlt();
	mvaddstrAlt(12, 12, CONST_THE_LAST_LCS_MEMBERS_HAVE_ALL_BEEN_HUNTED_DOWN, gamelog);
	gamelog.newline();
	pressAnyKey();
	set_color_easy(BLACK_ON_BLACK_BRIGHT);
	eraseAlt();
	mvaddstrAlt(12, 14, CONST_THEY_WILL_NEVER_SEE_THE_UTOPIA_THEY_DREAMED_OF, gamelog);
	gamelog.newline();
	gamelog.nextMessage();
	pressAnyKey();
	savehighscore(END_DISBANDLOSS);
	viewhighscores();
	end_game();
}
/* does end of month actions */
void passmonth(char &clearformess, char canseethings)
{
	short oldlaw[LAWNUM];
	for (int i = 0; i < LAWNUM; i++) {
		oldlaw[i] = lawList[i];
	}
	int l, p;
	//TIME ADVANCE
	day = 1;
	month++;
	if (month == 13)
	{
		month = 1;
		year++;
	}
	updateEndgamestate();
	//CLEAR RENT EXEMPTIONS
	clearRentExemptions();
	// Check for game over
	endcheck(END_DEAD);
	dispersalcheck(clearformess);
	if (!disbanding) {
		publishSpecialEditions(clearformess);
	}
	int libpower[VIEWNUM] = { 0 };
	//STORIES STALE EVEN IF NOT PRINTED
	for (int v = 0; v < VIEWNUM; v++)public_interest[v] /= 2;
	int conspower = 200 - attitude[VIEW_AMRADIO] - attitude[VIEW_CABLENEWS];
	//HAVING SLEEPERS
	havingSleepers(clearformess, canseethings, libpower);
	manageGrafiti();
	int mediabalance = 0;
	int issuebalance[VIEWNUM - 5];
	//int stimulus=0;
	//double cost=0;
	//double tax=0;
	//PUBLIC OPINION NATURAL MOVES
	publicOpinionNaturalMoves(issuebalance,
		libpower,
		conspower,
		mediabalance);
	// Temporary Stalinizing Code (TODO: Implement the Stalinist Comrade Squad for changing public opinion, then remove this)
	if (stalinmode) for (int v = 0; v < VIEWNUM - 3; v++)
	{
		if (stalinview(v, false)) { if ((attitude[v] += 3) > 100) attitude[v] = 100; }
		else { if (--attitude[v] < 0) attitude[v] = 0; }
	}
	// End Temporary Stalinizing Code (TODO: Implement the Stalinist Comrade Squad for changing public opinion, then remove this)
	// Seduction monthly experience stipends for those liberals
	// who have been getting it on with their love slaves/masters
	// in the background
	giveSeductionExperienceToLoveSlaves();
	/*******************************************************
	*                 INTELLIGENCE REPORT                  *
	*     ONLY IF SHOWMECHANICS OR SHOWWAIT IS DEFINED     *
	*        EYES ONLY - LCS PROPERTY - TOP SECRET         *
	*******************************************************/
	if ((SHOWMECHANICS || SHOWWAIT) && canseethings)
	{
		printIntelligenceReport(clearformess);
	}
	/*******************************************************
	*                                                      *
	*               END INTELLIGENCE REPORT                *
	*                                                      *
	*******************************************************/
	//ELECTIONS
	if (month == 11) {
		elections(clearformess, canseethings);
		clearformess = 1;
	}
	//SUPREME COURT
	if (month == 6) {
		supremecourt(clearformess, canseethings);
		clearformess = 1;
	}
	//CONGRESS
	congress(clearformess, canseethings);
	clearformess = 1;
	//DID YOU WIN?
	if (wincheck())
	{
		liberalagenda(1);
		savehighscore(END_WON);
		viewhighscores();
		end_game();
	}
	//CONTROL LONG DISBANDS
	if (disbanding&&year - disbandtime >= 50)
	{
		long_disband_loss();
	}
	//UPDATE THE WORLD IN CASE THE LAWS HAVE CHANGED
	updateworld_laws(lawList, oldlaw);
	//THE SYSTEM!
	if (!disbanding) {
		monthlyRunTheSystem(clearformess);
	}

	//NUKE EXECUTION VICTIMS
	monthlyRunExecutions();

	//MUST DO AN END OF GAME CHECK HERE BECAUSE OF EXECUTIONS
	endcheck(END_EXECUTED);
	//DISPERSAL CHECK
	dispersalcheck(clearformess);
	//FUND REPORTS
	if (canseethings)fundreport(clearformess);
	ledger.resetMonthlyAmounts();
	if (clearformess) eraseAlt();
	//HEAL CLINIC PEOPLE
	if (!disbanding) {
		monthlyRunHealClinicPeople(clearformess);
	}

}