
/*
Copyright (c) 2002,2003,2004 by Tarn Adams                                          //
                                                                                    //
This file is part of Liberal Crime Squad.                                           //
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

#include "../includes22.h"
#include "../constStringendgame.h"
void printRatifyHeader() {
	mvaddstrAlt(0, 62, CONST_HOUSE);
	mvaddstrAlt(0, 70, CONST_SENATE);
	mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_CONGRESSIONAL_VOTES_UNFOLD);
	pressAnyKey();
}
void printHouseRatification(const int l, const bool yeswin_h, const int yesvotes_h) {

	if (l == HOUSENUM - 1 && yeswin_h) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(2, 62, yesvotes_h);
	addstrAlt(CONST_YEA);
	if (l == HOUSENUM - 1 && !yeswin_h) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(3, 62, l + 1 - yesvotes_h);
	addstrAlt(CONST_NAY);
}
void printHouseRatificationS(const int l, const bool yeswin_s, const int yesvotes_s, const int s) {

	if (l == HOUSENUM - 1 && yeswin_s) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(2, 70, yesvotes_s);
	addstrAlt(CONST_YEA);
	if (l == HOUSENUM - 1 && !yeswin_s) set_color_easy(WHITE_ON_BLACK_BRIGHT);
	else if (l == HOUSENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(3, 70, s - yesvotes_s);
	addstrAlt(CONST_NAY);
	if (l % 5 == 0) pause_ms(10);
}
/* EndGameStatus - checks if a constitutional amendment is ratified */
char ratify(int level, int lawview, int view, char congress, char canseethings)
{
	if (canseethings)
	{
		music.play(MUSIC_ELECTIONS);
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, CONST_THE_RATIFICATION_PROCESS);
	}
	//THE STATE VOTE WILL BE BASED ON VIEW OF LAW
	int mood = publicmood(lawview);
	//OR OF A PARTICULAR ISSUE
	if (view >= 0) mood = attitude[view];
	//CONGRESS
	bool ratified = false;
	if (congress)
	{
		ratified = true;
		if (canseethings)
		{
			printRatifyHeader();
		}
		bool yeswin_h = false, yeswin_s = false;
		int yesvotes_h = 0, yesvotes_s = 0, s = 0;
		for (int l = 0; l < HOUSENUM; l++)
		{
			int vote = house[l];
			if (vote >= -1 && vote <= 1) vote += LCSrandom(3) - 1;
			if (level == vote) yesvotes_h++;
			if (l == HOUSENUM - 1) if (yesvotes_h >= HOUSESUPERMAJORITY) yeswin_h = true;
			if (canseethings)
			{
				printHouseRatification(l, yeswin_h, yesvotes_h);
			}
			if (l % 4 == 0 && s < SENATENUM)
			{
				vote = senate[s++];
				if (vote >= -1 && vote <= 1) vote += LCSrandom(3) - 1;
				if (level == vote) yesvotes_s++;
			}
			if (l == HOUSENUM - 1 && yesvotes_s >= SENATESUPERMAJORITY) yeswin_s = true;
			if (canseethings)
			{
				printHouseRatificationS(l, yeswin_s, yesvotes_s, s);
			}
		}
		if (!yeswin_h || !yeswin_s) ratified = false;
	}
	else ratified = true;
	if (level == 3) level = -2; // special case for Stalinists: do this after Congress but before the states
								//STATES
	if (ratified)
	{
		ratified = false;
		int yesstate = 0;
		if (canseethings)
		{
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			for (int s = 0; s < 50; s++)
			{
				if (s < 17) { moveAlt(5 + s, 0); }
				else if (s < 34) { moveAlt(5 + s - 17, 27); }
				else { moveAlt(5 + s - 34, 54); }

				addstrAlt(statename(s));
			}
			mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_WATCH_THE_STATE_VOTES_UNFOLD);
			pressAnyKey();
		}
		for (int s = 0; s < STATENUM; s++)
		{
			int smood = mood;
			// State biases.
			int multiplier = 5 + LCSrandom(3);
			smood += state_biases[s] * multiplier;
			int vote = -2;
			if (LCSrandom(100) < smood)vote++;
			if (LCSrandom(100) < smood)vote++;
			if (LCSrandom(100) < smood)vote++;
			if (LCSrandom(100) < smood)vote++;
			if (vote == 1 && !LCSrandom(2)) vote = 2;
			if (vote == -1 && !LCSrandom(2)) vote = -2;
			if (vote == level)
			{
				yesstate++;
			}
			if (canseethings) {
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				if (s < 17) moveAlt(5 + s, 22);
				else if (s < 34) moveAlt(5 + s - 17, 49);
				else moveAlt(5 + s - 34, 76);

				if (vote == level) {
					addstrAlt(CONST_YEA);
				}
				else {
					addstrAlt(CONST_NAY);
				}

				if (s == STATENUM - 1 && yesstate >= STATESUPERMAJORITY) set_color_easy(WHITE_ON_BLACK_BRIGHT);
				else if (s == STATENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
				else set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(23, 50, yesstate);
				addstrAlt(CONST_YEA);
				if (s == STATENUM - 1 && yesstate < STATESUPERMAJORITY) set_color_easy(WHITE_ON_BLACK_BRIGHT);
				else if (s == STATENUM - 1) set_color_easy(BLACK_ON_BLACK_BRIGHT);
				else set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(23, 60, s + 1 - yesstate);
				addstrAlt(CONST_NAY);
				pause_ms(50);
			}
		}
		if (yesstate >= STATESUPERMAJORITY) ratified = true;
	}
	if (canseethings)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		moveAlt(23, 0);
		if (ratified) addstrAlt(CONST_AMENDMENT_ADOPTED);
		else addstrAlt(CONST_AMENDMENT_REJECTED);
	}
	return ratified;
}
/* EndGameStatus - header for announcing constitutional amendments */
void amendmentheading()
{
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_PROPOSED_AMENDMENT);
	addstrAlt(romannumeral(amendnum));
	addstrAlt(CONST_TO_THE_UNITED_STATES_CONSTITUTION);
}
/*
TODO: I'm not sure if anything in here should be logged. Perhaps only the notification
that the country has become arch-conservative... --Addictgamer
*/
/* EndGameStatus - attempts to pass a constitutional amendment to help win the game */
void tossjustices(char canseethings)
{
	if (canseethings)
	{
		music.play(MUSIC_ELECTIONS);
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(12, 6, CONST_THE_ELITE_LIBERAL_CONGRESS_IS_PROPOSING_AN_ELITE_LIBERAL_AMENDMENT);
		pressAnyKey();
	}
	//STATE THE AMENDMENT
	if (canseethings)
	{
		int tossnum = 0;
		for (int j = 0; j < COURTNUM; j++) if (court[j] != ALIGN_ELITELIBERAL) tossnum++;
		amendmentheading();
		mvaddstrAlt(2, 5, CONST_THE_FOLLOWING_FORMER_CITIZEN);
		if (tossnum != 1)addstrAlt(CONST_S_ARE);
		else addstrAlt(CONST_IS);
		addstrAlt(CONST_BRANDED_ARCH_CONSERVATIVE);
		int y = 4;
		for (int j = 0; j < COURTNUM; j++) if (court[j] != ALIGN_ELITELIBERAL)
		{
			mvaddstrAlt(y++, 0, courtname[j]);
		}
		mvaddstrAlt(y + 1, 5, CONST_IN_PARTICULAR_THE_AFOREMENTIONED_FORMER_CITIZEN);
		if (tossnum != 1)addstrAlt(CONST_S);
		addstrAlt(CONST_MAY);
		mvaddstrAlt(y + 2, 0, CONST_NOT_SERVE_ON_THE_SUPREME_COURT_SAID_FORMER_CITIZEN);
		if (tossnum != 1)addstrAlt(CONST_S);
		addstrAlt(CONST_WILL);
		mvaddstrAlt(y + 3, 0, CONST_BE_DEPORTED_TO);
		if (tossnum != 1)addstrAlt(CONST_CONSERVATIVE_COUNTRIES);
		else addstrAlt(CONST_A_CONSERVATIVE_COUNTRY);
		addstrAlt(CONST_OF_THE_PRESIDENT_S);
		mvaddstrAlt(y + 4, 0, CONST_CHOOSING_TO_BE_REPLACED_BY);
		if (tossnum != 1)addstrAlt(CONST_PROPER_JUSTICES);
		else addstrAlt(CONST_A_PROPER_JUSTICE);
		addstrAlt(CONST_ALSO_OF);
		mvaddstrAlt(y + 5, 0, CONST_THE_PRESIDENT_S_CHOOSING_WITH_THE_ADVICE_AND_CONSENT_OF);
		mvaddstrAlt(y + 6, 0, CONST_THE_SENATE);
		mvaddstrAlt(24, 0, CONST_PRESS_C_TO_WATCH_THE_RATIFICATION_PROCESS_UNFOLD);
		while (getkeyAlt() != 'c');
	}
	if (ratify(2, -1, -1, 1, canseethings))
	{
		//BLAST JUSTICES
		for (int j = 0; j < COURTNUM; j++) if (court[j] != ALIGN_ELITELIBERAL)
		{
			do {
				fullName fn = generate_long_name();
				strcpy(courtname[j], (fn.first + " " + fn.last).data());
			} while (len(courtname[j]) > 20);
			court[j] = ALIGN_ELITELIBERAL;
		}
		amendnum++;
	}
	if (canseethings)
	{
		mvaddstrAlt(24, 0, pressKeyToReflect);
		pressAnyKey();
	}
}
/* EndGameStatus - attempts to pass a constitutional amendment to help win the game */
void amendment_termlimits(char canseethings)
{
	if (termlimits)return; // Durr~! Don't pass this amendment if it's already passed!
	if (canseethings)
	{
		music.play(MUSIC_ELECTIONS);
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(12, 6, CONST_A_NATIONAL_CONVENTION_HAS_PROPOSED_AN_ELITE_LIBERAL_AMENDMENT);
		pressAnyKey();
	}
	//STATE THE AMENDMENT
	if (canseethings)
	{
		amendmentheading();
		{
			int i = 2;
			for (string s : amendmentPass) {
				mvaddstrAlt(i, 0, s);
				i++;
			}
		}
		mvaddstrAlt(24, 0, CONST_PRESS_C_TO_WATCH_THE_RATIFICATION_PROCESS_UNFOLD);
		while (getkeyAlt() != 'c');
	}
	if (ratify(2, -1, -1, 0, canseethings))
	{
		termlimits = true;
		if (canseethings)
		{
			mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_HOLD_NEW_ELECTIONS);
			pressAnyKey();
		}
		elections_senate(0, canseethings);
		elections_senate(1, canseethings);
		elections_senate(2, canseethings);
		elections_house(canseethings);
		amendnum++;
	}
	else if (canseethings)
	{
		mvaddstrAlt(24, 0, pressKeyToReflect);
		pressAnyKey();
	}
}
void badEndRemakeWorld(const string& str, const string& str2, const string& str3, EndTypes end) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	eraseAlt();
	mvaddstrAlt(12, 10, str);
	pressAnyKey();
	set_color_easy(WHITE_ON_BLACK);
	eraseAlt();
	mvaddstrAlt(12, 12, str2);
	pressAnyKey();
	set_color_easy(BLACK_ON_BLACK_BRIGHT);
	eraseAlt();
	mvaddstrAlt(12, 14, str3);
	pressAnyKey();
	savehighscore(end);
}
/* EndGameStatus - attempts to pass a constitutional amendment to lose the game */
void attemptAmendmentEnding(char canseethings, Alignment enforcedAlignment)
{
	vector<string> output;
	MusicModes endMusic;
	vector<string> finalCabinet;
	vector<int> ratificationNumbers;
	string proposedAmendment;
	if (enforcedAlignment == ALIGN_ARCHCONSERVATIVE) {
		proposedAmendment = proposeConservative;
		output = archConservativeAmendment;
		endMusic = MUSIC_REAGANIFIED;
		finalCabinet = reaganifiedCabinet;
		ratificationNumbers = {
			-2,-1,-1,1
		};
	}
	else if (enforcedAlignment == ALIGN_STALINIST) {
		proposedAmendment = proposeStalinist;
		output = stalinAmendment;
		endMusic = MUSIC_STALINIZED;
		finalCabinet = stalinizedCabinet;
		ratificationNumbers = {
			3,-2,-2,1
		};
	}
	else {
		addstrAlt(CONST_INVALID_ALIGNMENT_FOR_AMENDMENT);
		return;
	}
	move_center_string(12, proposedAmendment.data());
	if (canseethings)
	{
		music.play(MUSIC_ELECTIONS);
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		eraseAlt();
		pressAnyKey();
		//STATE THE AMENDMENT
		amendmentheading();
		{
			int i = 2;
			for (string s : output) {
				mvaddstrAlt(i, 0, s);
				i++;
			}
		}
		mvaddstrAlt(24, 0, CONST_PRESS_C_TO_WATCH_THE_RATIFICATION_PROCESS_UNFOLD);
		while (getkeyAlt() != 'c');
	}
	if (ratify(ratificationNumbers[0], ratificationNumbers[1], ratificationNumbers[2], ratificationNumbers[3], canseethings))
	{
		music.play(endMusic);
		if (canseethings)
		{
			mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_REFLECT_ON_WHAT_HAS_HAPPENED_ONE_LAST_TIME);
			pressAnyKey();
		}
		amendnum = 1; // Constitution repealed...
		if (canseethings)
		{
			strcpy(execname[EXEC_PRESIDENT], finalCabinet[0].data());
			strcpy(execname[EXEC_VP], finalCabinet[1].data());
			strcpy(execname[EXEC_STATE], finalCabinet[2].data());
			strcpy(execname[EXEC_ATTORNEY], finalCabinet[3].data());
			for (int e = 0; e < EXECNUM; e++) exec[e] = enforcedAlignment;
			if (enforcedAlignment == ALIGN_ARCHCONSERVATIVE) {
				for (int l = 0; l < LAWNUM; l++) lawList[l] = enforcedAlignment;
				liberalagenda(-1);
				savehighscore(END_REAGAN);
			}
			else if (enforcedAlignment == ALIGN_STALINIST) {
				for (int l = 0; l < LAWNUM; l++) lawList[l] = stalinview(l, true) ? ALIGN_ELITELIBERAL : ALIGN_ARCHCONSERVATIVE;
				liberalagenda(-2);
				savehighscore(END_STALIN);
			}
		}
		else
		{
			string endingOne;
			string endingTwo;
			string endingThree;
			EndTypes ending;
			vector<string> inPrison;
			switch (cantseereason)
			{
			case 1:
				//DATING AND 
				endingOne = youWentOnVacation;
				if (enforcedAlignment == ALIGN_ARCHCONSERVATIVE) {
					endingTwo = CONSERVATIVES_HAVE_REMADE_THE_WORLD;
				}
				else if (enforcedAlignment == ALIGN_STALINIST) {
					endingTwo = stalinistsRemakeWorld;
				}
				endingThree = they_ll_round_you_up;
				ending = END_DATING;
				break;
			case 2:
				//HIDING AND 
				endingOne = youWentIntoHiding;
				if (enforcedAlignment == ALIGN_ARCHCONSERVATIVE) {
					endingTwo = CONSERVATIVES_HAVE_REMADE_THE_WORLD;
				}
				else if (enforcedAlignment == ALIGN_STALINIST) {
					endingTwo = stalinistsRemakeWorld;
				}
				endingThree = they_ll_round_you_up;
				ending = END_HIDING;
				break;
			case 3:
				//IF YOU ARE ALL IN PRISON, 
				endingOne = whileYouWereInPrison;
				if (enforcedAlignment == ALIGN_ARCHCONSERVATIVE) {
					vector<string> inPrison = conservativePrison;
				}
				else if (enforcedAlignment == ALIGN_STALINIST) {
					vector<string> inPrison = stalinistPrison;
				}
				endingTwo = inPrison[0];
				endingThree = inPrison[1];
				ending = END_PRISON;
				break;
			case 4:
				//DISBANDED AND 
				endingOne = youDisappearedSafely;
				if (enforcedAlignment == ALIGN_ARCHCONSERVATIVE) {
					endingTwo = CONSERVATIVES_HAVE_REMADE_THE_WORLD;
				}
				else if (enforcedAlignment == ALIGN_STALINIST) {
					endingTwo = stalinistsRemakeWorld;
				}
				endingThree = they_ll_round_you_up;
				ending = END_DISBANDLOSS;
				break;
			}
			badEndRemakeWorld(endingOne, endingTwo, endingThree, ending);
		}
		viewhighscores(endMusic);
		end_game();
	}
	else
	{
		if (canseethings)
		{
			mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_BREATHE_A_SIGH_OF_RELIEF);
			pressAnyKey();
		}
	}
}