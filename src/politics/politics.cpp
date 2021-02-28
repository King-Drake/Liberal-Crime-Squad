

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

#include "../includes16.h"
#include "../constStringpolitics.h"
#include <algorithm>
vector<string> corporateSuffix;
 map<short, string> winnerOfElection;
 vector<file_and_text_collection> politics_text_file_collection = {
	 customText(&corporateSuffix, MOSTLY_ENDINGS_FOLDER + corporateSuffixtxt),
 };
 
 /* returns true if Stalinists agree with Elite Liberals on a view/law, false if they strongly disagree with libs  *
 * the input bool islaw, if true, returns Stalinist opinion on laws, if false, returns Stalinist opinion on views */
 bool stalinview(short view, bool islaw)
 {
	 if (islaw)
	 {
		 if (stalinLaw.count(view)) {
			 return stalinLaw[view];
		 }
		 else
			 return false; // if the law doesn't exist, assume false
	 }
	 else
	 {
		 if (stalinView.count(view)) {
			 return stalinView[view];
		 }
		 else
			 return false; // if the view doesn't exist, assume false
	 }
 }

 // a function to transform a view into a law
 int viewToLaw(const short arr[VIEWNUM], const int old_l) {
	 int l = old_l;
	 if (lawReturnAttitude.count(l)) {
		 return arr[lawReturnAttitude[l]];
	 } else {
		 switch (l) {  // All laws should be affected by exactly one issue if there is a direct
			// correlation between that law and an issue. For example, police behavior
			// as a law should depend only upon police behavior as an issue. This keeps
			// the game logical to the player and ensures that the public opinion polls
			// displayed in-game accurately predict how people will vote in specific
			// issues. For a handful of laws, we might not have a directly correlating
			// issue; for example, as of this writing, there is no issue asking people's
			// opinions on torture. In this case, we can use the nearest issue, or we
			// can mix two closely related ones. As a general principle, try to avoid
			// getting too complicated here; this is under-the-hood stuff the player
			// will never appreciate, so it should be kept as simple and transparent as
			// possible so as to avoid creating unexpected results that will only confuse
			// players, like people refusing to further regulate nuclear power because
			// one of the other issues besides nuclear power is conservative, even when
			// the nuclear power issue is 100% Liberal. - Jonathan S. Fox
			 case LAW_CORPORATE: return (arr[VIEW_CORPORATECULTURE] + arr[VIEW_CEOSALARY]) / 2; // <-- We'll be merging these two views here because there is no CEO salary law.
																										  // The issue is there for flavor, and falls under the same umbrella of
																										  // corporate regulation. - Jonathan S. Fox
			 case LAW_STALIN:
				 l = 0;
				 for (int v = 0; v < VIEWNUM - 3; v++)
					 if (stalinview(v, false)) l += 100 - arr[v];
					 else l += arr[v];
				 return l / (VIEWNUM - 3);
			 case LAW_ELECTIONS:
			 case LAW_MOOD:
			 default: //eg. -1
				 l = 0;
				 for (int v = 0; v < VIEWNUM - 3; v++) l += arr[v];
				 return l / (VIEWNUM - 3);
		 }
	 }
 }
 
 /* politics - checks the prevailing attitude on a specific law, or overall */
 int publicmood(const int old_l){
	 return viewToLaw(attitude, old_l);
 }

 /* politics - checks the public's interest in a specific law, or overall*/
 int publicinterest(const int old_l) {
	 return viewToLaw(public_interest, old_l);
 }

 /* common - shifts public opinion on an issue */
 void change_public_opinion(int v, int power, char affect, char cap)
 {
	 // First note this in the liberal influence -- mostly for the
	 // sake of the nice visual intelligence report entry
	 if (v < VIEWNUM - 5)
	 {
		 background_liberal_influence[v] += power * 10;
	 }
	 if (v == VIEW_LIBERALCRIMESQUAD)affect = 0;
	 if (v == VIEW_LIBERALCRIMESQUADPOS)affect = 0;
	 if (v == VIEW_LIBERALCRIMESQUADPOS)
	 {
		 int mood = publicmood(-1);
		 if (cap > mood + 40)cap = mood + 40;
	 }
	 int effpower = power;
	 // Affect is whether the LCS is publicly known to be behind
	 // the circumstances creating the public opinion change
	 if (affect == 1)
	 {
		 // Aff is the % of people who know/care about the LCS
		 int aff = attitude[VIEW_LIBERALCRIMESQUAD];
		 // Rawpower is the amount of the action proportional
		 // to the people who, not having heard of the LCS,
		 // do not allow the LCS' reputation to affect their
		 // opinions
		 int rawpower = (int)((float)power * (float)(100 - aff) / 100.0f);
		 // Affected power is the remainder of the action besides
		 // rawpower, the amount of the people who know of the LCS
		 // and have it alter their opinion
		 int affectedpower = power - rawpower;
		 if (affectedpower > 0)
		 {
			 // Dist is a combination of the relative popularity of the LCS
			 // to the issue and the absolute popularity of the LCS. Very
			 // popular LCS on a very unpopular issue is very influential.
			 // Very unpopular LCS on a very popular issue has the ability
			 // to actually have a reverse effect.
			 int dist = attitude[VIEW_LIBERALCRIMESQUADPOS] - attitude[v] +
				 attitude[VIEW_LIBERALCRIMESQUADPOS] - 50;
			 // Affected power is then scaled by dist -- if the LCS is
			 // equally popular as the issue, it's equally powerful as
			 // the rawpower. For every 10% up or down past there, it's
			 // 10% more or less powerful.
			 affectedpower = (int)(((float)affectedpower*(100.0 + (float)dist)) / 100.0f);
		 }
		 // Effpower is then the sum of the rawpower (people who don't know
		 // about the LCS) and the affectedpower (people who do know
		 // about the LCS and had their judgment swayed by their opinion
		 // of it).
		 effpower = rawpower + affectedpower;
	 }
	 else if (affect == -1)
	 {
		 // Simplifed algorithm for affect by CCS respect
		 effpower = power * (100 - attitude[VIEW_CONSERVATIVECRIMESQUAD]) / 100;
	 }
	 if (v == VIEW_LIBERALCRIMESQUAD)
	 {
		 //Only half the country will ever hear about the LCS at one time,
		 //and people will only grudgingly lose fear of it
		 if (effpower < -5)effpower = -5;
		 if (effpower > 50)effpower = 50;
	 }
	 else if (v == VIEW_LIBERALCRIMESQUADPOS)
	 {
		 //Only 50% of the country can be swayed at once in their views
		 //of the LCS negatively, 5% positively
		 if (effpower < -50)effpower = -50;
		 if (effpower > 5)effpower = 5;
	 }
	 //Scale the magnitude of the effect based on how much
	 //people are paying attention to the issue
	 effpower = (int)(effpower*(1 + (float)public_interest[v] / 50));
	 //Then affect public interest
	 if (public_interest[v] < cap || (v == VIEW_LIBERALCRIMESQUADPOS && public_interest[v] < 100))
		 public_interest[v] += abs(effpower);
	 if (effpower > 0)
	 {
		 //Some things will never persuade the last x% of the population.
		 //If there's a cap on how many people will be impressed, this
		 //is where that's handled.
		 if (attitude[v] + effpower > cap)
		 {
			 if (attitude[v] > cap)effpower = 0;
			 else effpower = cap - attitude[v];
		 }
	 }
	 //Finally, apply the effect.
	 attitude[v] += effpower;
	 if (attitude[v] < 0)attitude[v] = 0;
	 if (attitude[v] > 100)attitude[v] = 100;
 }

 /* politics -- gets the leaning of an issue voter for an election */
 int getswingvoter(bool stalin)
 {
	 // Take a random voter, calculate how liberal or conservative they are
	 // If stalin parameter is true, it calculates how libertarian or Stalinist they are instead
	 int bias = publicmood(-1 - stalin) - LCSrandom(100), vote = -2;
	 if (bias > 25)bias = 25;
	 if (bias < -25)bias = -25;
	 // Each issue they roll for their opinion on a 50-point subset of the
	 // spectrum, determined by bias -- high liberal/libertarian bias only rolls on the
	 // liberal/libertarian end of the spectrum, high conservative/Stalinist bias only rolls on
	 // the conservative/Stalinist end of the spectrum
	 for (int i = 0; i < 4; i++)
	 {
		 int issue = randomissue(true);
		 if (25 + LCSrandom(50) - bias < ((stalin&&stalinview(issue, false)) ? 100 - attitude[issue] : attitude[issue])) vote++;
	 }
	 return vote;
 }
 /* politics - calculate presidential approval */
 int presidentapproval()
 {
	 //Calculate Presidential approval rating
	 int approval = 0;
	 for (int i = 0; i < 1000; i++)
	 {
		 if (i % 2 == 0 && LCSrandom(2)) approval++;    // Partyline supporter (~25%)
		 else if (i % 2 == 1 && LCSrandom(2)) continue; // Partyline opponent  (~25%)
		 else                                    // Swing issue voter   (~50%) (should be more than in the real election)
		 {
			 // Get their leanings as an issue voter
			 int vote = getswingvoter(exec[EXEC_PRESIDENT] == ALIGN_STALINIST);
			 // If their views are close to the President's views, they should
			 // approve, but might not if their party leaning conflicts with
			 // the president's
			 // Moderate president from the Conservative party is only supported
			 // by moderates and Conservatives
			 // Moderate president from the Liberal party is only supported
			 // by moderates and Liberals
			 int presalign = exec[EXEC_PRESIDENT] == ALIGN_STALINIST ? ALIGN_ARCHCONSERVATIVE : exec[EXEC_PRESIDENT];
			 if (abs(presalign - vote) <= 1 && (presparty != LIBERAL_PARTY ? vote <= 0 : vote >= 0)) approval++;
		 }
	 }
	 return approval;
 }
 /* politics -- gets the leaning of a partyline voter for an election */
 int getsimplevoter(int leaning)
 {
	 // no need for this to deal with Stalinism, this function deliberately only deals with the liberal vs. conservative spectrum
	 int vote = leaning - 1;
	 for (int i = 0; i < 2; i++) if (LCSrandom(100) < attitude[randomissue(true)]) vote++;
	 return vote;
 }

 /* politics -- appoints a figure to an executive office, based on the President's alignment*/
 void fillCabinetPost(int position)
 {
	 int pres_status = getSleeperPresidentStatus();
		// Check if the President is a sleeper and set alignment based on the response (or VP votes like the President)
	 if (pres_status == 1)
		 exec[position] = ALIGN_ELITELIBERAL;
	 else
	 {
		 if (exec[EXEC_PRESIDENT] == ALIGN_ARCHCONSERVATIVE) exec[position] = ALIGN_ARCHCONSERVATIVE;
		 else if (exec[EXEC_PRESIDENT] == ALIGN_ELITELIBERAL) exec[position] = ALIGN_ELITELIBERAL;
		 else if (exec[EXEC_PRESIDENT] == ALIGN_STALINIST) exec[position] = ALIGN_STALINIST;
		 else exec[position] = exec[EXEC_PRESIDENT] + LCSrandom(3) - 1;
	 }

	 // Set name
	 if (exec[position] == ALIGN_ARCHCONSERVATIVE) generate_name(execname[position], GENDER_WHITEMALEPATRIARCH);
	 else if (exec[position] == ALIGN_CONSERVATIVE) generate_name(execname[position], GENDER_MALE);
	 else generate_name(execname[position]);
 }
 /* politics -- promotes the Vice President to President, and replaces VP*/
 void promoteVP()
 {
	 //revoke sleeper Presidents position.
	 clearSleeperPresident();
	 exec[EXEC_PRESIDENT] = exec[EXEC_VP]; // VP takes over as President
	 strcpy(execname[EXEC_PRESIDENT], execname[EXEC_VP]);
	 switch (exec[EXEC_PRESIDENT])
	 { // make sure presparty is set correctly (if old President was moderate they could've been in Liberal OR Conservative Party,
	 case ALIGN_ARCHCONSERVATIVE: // and new President might have a political alignment incompatible with that party)
	 case ALIGN_CONSERVATIVE:
		 presparty = CONSERVATIVE_PARTY; break; // Conservatives and Arch-Conservatives align with the Conservative Party
	 case ALIGN_MODERATE:
		 break; // same party as previous President (either Liberal Party or Conservative Party)
	 case ALIGN_LIBERAL:
	 case ALIGN_ELITELIBERAL:
		 presparty = LIBERAL_PARTY; break; // Liberals and Elite Liberals align with the Liberal Party
	 case ALIGN_STALINIST:
		 presparty = STALINIST_PARTY; break; // Stalinists align with the Stalinist Party
	 }
	 fillCabinetPost(EXEC_VP); // the vacant VP slot needs to be filled
	 if (abs(exec[EXEC_PRESIDENT]) > 1)
	 {  // new President has extreme views... make sure all cabinet members agree with new President
		 if (exec[EXEC_PRESIDENT] != exec[EXEC_STATE]) fillCabinetPost(EXEC_STATE);
		 if (exec[EXEC_PRESIDENT] != exec[EXEC_ATTORNEY]) fillCabinetPost(EXEC_ATTORNEY);
	 }
	 else
	 {  // new President has fairly moderate views, but anyone who differs too much from them must be replaced
		 if (abs(exec[EXEC_PRESIDENT] - exec[EXEC_STATE]) > 1) fillCabinetPost(EXEC_STATE);
		 if (abs(exec[EXEC_PRESIDENT] - exec[EXEC_ATTORNEY]) > 1) fillCabinetPost(EXEC_ATTORNEY);
	 }
 }


 void printSenateWinner(const int change[]) {
	 const int mood = publicmood(LAW_MOOD);
	 signed char winner;
	 if (change[5] > 0 && change[5] > change[0] + change[1] && change[5] > change[3] + change[4]) // Stalinist increased and Stalinist gain is more than C or L side gain/loss
		 winner = ALIGN_STALINIST;
	 else if (change[0] + change[1] > change[3] + change[4]) // C side gain/loss is more than L side gain/loss
	 {
		 if (change[1] < 0 && mood < 25) winner = ALIGN_ARCHCONSERVATIVE;
		 else winner = ALIGN_CONSERVATIVE;
	 }
	 else if (change[3] + change[4] > change[0] + change[1]) // L side gain/loss is more than C side gain/loss
	 {
		 if (change[3] < 0 && mood>75) winner = ALIGN_ELITELIBERAL;
		 else winner = ALIGN_LIBERAL;
	 }
	 else if (change[0] > 0 && change[4] <= 0 && change[5] <= 0) // C+ increased and L+ and Stalinist both same or decreased
	 {
		 if (mood < 25) winner = ALIGN_ARCHCONSERVATIVE;
		 else winner = ALIGN_CONSERVATIVE;
	 }
	 else if (change[4] > 0 && change[0] <= 0 && change[5] <= 0) // L+ increased and C+ and Stalinist both same or decreased
	 {
		 if (mood > 75) winner = ALIGN_ELITELIBERAL;
		 else winner = ALIGN_LIBERAL;
	 }
	 else if (change[5] > 0 && change[0] <= 0 && change[4] <= 0) // Stalinist increased and C+ and L+ both same or decreased
		 winner = ALIGN_STALINIST;
	 else winner = ALIGN_MODERATE; // nobody won

	 actuallyPrintSenateWinner(winnerOfElection[winner]);
	 pressAnyKey();
 }

 void elections_senate(int senmod, char canseethings)
 {
	 const int mood = publicmood(LAW_MOOD);
	 const int stalinmood = publicmood(LAW_STALIN);
	 if (canseethings)
	 {
		 music.play(MUSIC_ELECTIONS);
		 printSenateElectionsHeader();
	 }
	 {
		 int x = 0;
		 int y = 2;
		 for (int s = 0; s < SENATENUM; s++)
		 {
			 if (senmod != -1 && s % 3 != senmod)continue;
			 if (canseethings)
			 {
				 printSingleSenatorSymbol(y, x, senate[s]);
			 }
			 x += 20;
			 if (x > 70) x = 0, y++;
		 }
	 }
	 if (canseethings)
	 {
		 printPressAnyKeyElections();
		 pressAnyKey();
	 }
	 int vote, change[6] = { 0,0,0,0,0,0 };
	 {
		 int x = 0;
		 int y = 2;
		 for (int s = 0; s < SENATENUM; s++)
		 {
			 if (senmod != -1 && s % 3 != senmod) continue;
			 vote = -2;
			 for (int i = 0; i < 4; i++) if (mood > LCSrandom(100)) vote++;
			 if (stalinmode&&stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100)) vote = 3;
			 change[senate[s] + 2]--;
			 if (termlimits) senate[s] = vote;
			 else
			 {
				 int vote2;
				 bool first = true;
				 do {
					 vote2 = -2;
					 for (int i = 0; i < 4; i++) if (mood > LCSrandom(100)) vote2++;
					 if (stalinmode&&stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100)) vote2 = 3;
					 if (first) switch (lawList[LAW_ELECTIONS])
					 {
					 case -2: 
						switch (senate[s]) { // Nested switch statement is because liberal members are less corrupt by nature, which puts them at a disadvantage - Noop
							case  3: 
							case -2: if (LCSrandom(3)) vote2 = senate[s]; break; // 2/3 chance of incumbent winning no matter what (huge   advantage)
							case -1: if (LCSrandom(2)) vote2 = senate[s]; break; // 1/2 chance of incumbent winning no matter what (big   advantage)
							case  0: if (!LCSrandom(3)) vote2 = senate[s]; break; // 1/3 chance of incumbent winning no matter what (medium   advantage)
							case  1: if (!LCSrandom(5)) vote2 = senate[s]; break; // 1/5 chance of incumbent winning no matter what (small   advantage)
							case  2: if (!LCSrandom(8)) vote2 = senate[s]; break; // 1/8 chance of incumbent winning no matter what (tiny   advantage)
							default: if (LCSrandom(3)) vote2 = senate[s]; break;
						 }
						 break;
					 case -1:
						 switch (senate[s]) {
						 case  3:
						 case -2: 
						 case -1: if (LCSrandom(2)) vote2 = senate[s]; break;
						 case  0: if (!LCSrandom(3)) vote2 = senate[s]; break;
						 case  1: if (!LCSrandom(5)) vote2 = senate[s]; break;
						 case  2: if (!LCSrandom(8)) vote2 = senate[s]; break;
						 default: if (LCSrandom(3)) vote2 = senate[s]; break;
						 }
						 break;
					 case 0:
						 switch (senate[s]) {
						 case  3:
						 case -2:
						 case -1: 
						 case  0: if (!LCSrandom(3)) vote2 = senate[s]; break;
						 case  1: if (!LCSrandom(5)) vote2 = senate[s]; break;
						 case  2: if (!LCSrandom(8)) vote2 = senate[s]; break;
						 default: if (!LCSrandom(3)) vote2 = senate[s]; break;
						 }
						 break;
					 case 1:
						 switch (senate[s]) {
						 case  3:
						 case -2:
						 case -1:
						 case  0:
						 case  1: if (!LCSrandom(5)) vote2 = senate[s]; break;
						 case  2: if (!LCSrandom(8)) vote2 = senate[s]; break;
						 default: if (!LCSrandom(5)) vote2 = senate[s]; break;
						 }
						 break;
					 case 2: 
						 if (!LCSrandom(8)) vote2 = senate[s]; break;
					 // Legacy (Deprecated by Noop) 
					 /*
					 case -2: if (LCSrandom(3)) vote2 = senate[s]; break; // 2/3 chance of incumbent winning no matter what (huge   advantage)
					 case -1: if (LCSrandom(2)) vote2 = senate[s]; break; // 1/2 chance of incumbent winning no matter what (big    advantage)
					 case  0: if (!LCSrandom(3)) vote2 = senate[s]; break; // 1/3 chance of incumbent winning no matter what (medium advantage)
					 case  1: if (!LCSrandom(5)) vote2 = senate[s]; break; // 1/5 chance of incumbent winning no matter what (small  advantage)
					 case  2: if (!LCSrandom(8)) vote2 = senate[s]; break; // 1/8 chance of incumbent winning no matter what (tiny   advantage)
					 */
					 }
					 first = false;
				 } while (vote2 != senate[s] && vote2 != vote);
				 senate[s] = vote2;
			 }
			 change[senate[s] + 2]++;
			 if (canseethings)
			 {
				 printSingleSenator(senate[s], x, y);
			 }
			 x += 20;
			 if (x > 70) x = 0, y++;
			 if (canseethings)
			 {
				 printSenateStatus(change);
				 if (!disbanding) pause_ms(30);
			 }
		 }
	 }
	 if (canseethings)
	 {
		 printSenateWinner(change);
	 }
 }


 void printWinnerOfElection(const int change[]) {
	 const int mood = publicmood(LAW_MOOD);
	 signed char winner;
	 if (change[5] > 0 && change[5] > change[0] + change[1] && change[5] > change[3] + change[4]) // Stalinist increased and Stalinist gain is more than C or L side gain/loss
		 winner = ALIGN_STALINIST;
	 else if (change[0] + change[1] > change[3] + change[4]) // C side gain/loss is more than L side gain/loss
	 {
		 if (change[1] < 0 && mood < 25) winner = ALIGN_ARCHCONSERVATIVE;
		 else winner = ALIGN_CONSERVATIVE;
	 }
	 else if (change[3] + change[4] > change[0] + change[1]) // L side gain/loss is more than C side gain/loss
	 {
		 if (change[3] < 0 && mood>75) winner = ALIGN_ELITELIBERAL;
		 else winner = ALIGN_LIBERAL;
	 }
	 else if (change[0] > 0 && change[4] <= 0 && change[5] <= 0) // C+ increased and L+ and Stalinist both same or decreased
	 {
		 if (mood < 25) winner = ALIGN_ARCHCONSERVATIVE;
		 else winner = ALIGN_CONSERVATIVE;
	 }
	 else if (change[4] > 0 && change[0] <= 0 && change[5] <= 0) // L+ increased and C+ and Stalinist both same or decreased
	 {
		 if (mood > 75) winner = ALIGN_ELITELIBERAL;
		 else winner = ALIGN_LIBERAL;
	 }
	 else if (change[5] > 0 && change[0] <= 0 && change[4] <= 0) // Stalinist increased and C+ and L+ both same or decreased
		 winner = ALIGN_STALINIST;
	 else winner = ALIGN_MODERATE; // nobody won

	 printSingleWinnerOfElection(winnerOfElection[winner]);
	 if (!disbanding)
	 {
		 printCONST_PRESS_ANY_KEY_TO_CONTINUE_THE_ELECTIONS();
		 pressAnyKey();
	 }
	 else pause_ms(800);
 }

 void elections_house(const char canseethings)
 {
	 const int mood = publicmood(LAW_MOOD);
	 const int stalinmood = publicmood(LAW_STALIN);
	 if (canseethings)
	 {
		 music.play(MUSIC_ELECTIONS);
		 printHouseElectionsHeader();
		 pressAnyKey();
	 }
	 int change[6] = { 0,0,0,0,0,0 };
	 {
		 int x = 0;
		 int y = 2;
		 for (int h = 0; h < HOUSENUM; h++)
		 {
			 int vote = -2;
			 for (int i = 0; i < 4; i++) if (mood > LCSrandom(100)) vote++;
			 if (stalinmode&&stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100)) vote = 3;
			 change[house[h] + 2]--;
			 if (termlimits) house[h] = vote;
			 else
			 {
				 int vote2;
				 bool first = true;
				 do {
					 vote2 = -2;
					 for (int i = 0; i < 4; i++) if (mood > LCSrandom(100)) vote2++;
					 if (stalinmode&&stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100) && stalinmood < LCSrandom(100)) vote2 = 3;
					 if (first) switch (lawList[LAW_ELECTIONS])
					 {
					 case -2:
						 switch (house[h]) { // Nested switch statement is because liberal members are less corrupt by nature, which puts them at a disadvantage - Noop
						 case  3:
						 case -2: if (LCSrandom(3)) vote2 = house[h]; break; // 2/3 chance of incumbent winning no matter what (huge   advantage)
						 case -1: if (LCSrandom(2)) vote2 = house[h]; break; // 1/2 chance of incumbent winning no matter what (big   advantage)
						 case  0: if (!LCSrandom(3)) vote2 = house[h]; break; // 1/3 chance of incumbent winning no matter what (medium   advantage)
						 case  1: if (!LCSrandom(5)) vote2 = house[h]; break; // 1/5 chance of incumbent winning no matter what (small   advantage)
						 case  2: if (!LCSrandom(8)) vote2 = house[h]; break; // 1/8 chance of incumbent winning no matter what (tiny   advantage)
						 default: if (LCSrandom(3)) vote2 = house[h]; break;
						 }
						 break;
					 case -1:
						 switch (house[h]) {
						 case  3:
						 case -2:
						 case -1: if (LCSrandom(2)) vote2 = house[h]; break;
						 case  0: if (!LCSrandom(3)) vote2 = house[h]; break;
						 case  1: if (!LCSrandom(5)) vote2 = house[h]; break;
						 case  2: if (!LCSrandom(8)) vote2 = house[h]; break;
						 default: if (LCSrandom(3)) vote2 = house[h]; break;
						 }
						 break;
					 case 0:
						 switch (house[h]) {
						 case  3:
						 case -2:
						 case -1:
						 case  0: if (!LCSrandom(3)) vote2 = house[h]; break;
						 case  1: if (!LCSrandom(5)) vote2 = house[h]; break;
						 case  2: if (!LCSrandom(8)) vote2 = house[h]; break;
						 default: if (!LCSrandom(3)) vote2 = house[h]; break;
						 }
						 break;
					 case 1:
						 switch (house[h]) {
						 case  3:
						 case -2:
						 case -1:
						 case  0:
						 case  1: if (!LCSrandom(5)) vote2 = house[h]; break;
						 case  2: if (!LCSrandom(8)) vote2 = house[h]; break;
						 default: if (!LCSrandom(5)) vote2 = house[h]; break;
						 }
						 break;
					 case 2:
						 if (!LCSrandom(8)) vote2 = house[h]; break;
					 // Legacy (Deprecated by Noop)
					 /*
					 case -2: if (LCSrandom(3)) vote2 = house[h]; break; // 2/3 chance of incumbent winning no matter what (huge   advantage)
					 case -1: if (LCSrandom(2)) vote2 = house[h]; break; // 1/2 chance of incumbent winning no matter what (big    advantage)
					 case  0: if (!LCSrandom(3)) vote2 = house[h]; break; // 1/3 chance of incumbent winning no matter what (medium advantage)
					 case  1: if (!LCSrandom(5)) vote2 = house[h]; break; // 1/5 chance of incumbent winning no matter what (small  advantage)
					 case  2: if (!LCSrandom(8)) vote2 = house[h]; break; // 1/8 chance of incumbent winning no matter what (tiny   advantage)
					 */
					 }
					 first = false;
				 } while (vote2 != house[h] && vote2 != vote);
				 house[h] = vote2;
			 }
			 change[house[h] + 2]++;
			 if (canseethings)
			 {
				 printHouseChanges(x, y, house[h], change);
				 if (!disbanding) pause_ms(5);
			 }

			 x += 3;
			 if (x > 78) x = 0, y++;
		 }
	 }
	 if (canseethings)
	 {
		 printWinnerOfElection(change);
	 }
 }
 bool voteOnBill(const char canseethings, const int mood, const int propdir, const int p) {
	 bool yeswin = false;
	 bool recount = false;
	 for (int l = 0, yesvotes = 0; l < 1000; l++)
	 {
		 if (LCSrandom(100) < mood ? propdir == 1 : propdir == -1) yesvotes++;
		 if (l == 999)
		 {
			 if (yesvotes > 500) yeswin = true;
			 else if (yesvotes == 500) yeswin = (LCSrandom(100) < mood ? propdir == 1 : propdir == -1), recount = true;
		 }
		 if (canseethings && (l % 10 == 9))
		 {
			 printSingleVoteOnBill(l, yesvotes, yeswin, p);
			 pause_ms(10);
		 }
	 }
	 if (canseethings&&recount)
	 {
		 printCONST_A_RECOUNT_WAS_NECESSARY(p);
	 }
	 return yeswin;
 }
 void printCandidates(const char candidate[3][POLITICIAN_NAMELEN + 1]) {
	 for (int c = 0; c < 2 + stalinmode; c++)
	 {
		 printSingleCandidateTitle(candidate[c] + 1, candidate[c][0], c);
	 }
	 if (!disbanding)
	 {
		 printWatchElectionUnfold();
		 pressAnyKey();
	 }
	 else pause_ms(200);
 }

 int singleVote(const int l, const char liberalCandiadate, const char conservativeCandiadate) {
	 int partyVote;
	 if (l % 2 == 0 && LCSrandom(5))
	 {  // Partyline Liberals (~40%) - except when stalin mode is enabled they can go Stalinist sometimes
		 if (!stalinmode || getswingvoter(true) != -2 || getswingvoter(false) == 2) // if we aren't in stalin mode or they don't agree with Stalinism or they are an Elite Liberal
			 partyVote = LIBERAL_PARTY;                                        // go with Liberal Party affiliation (Good Loyal Liberal!)
		 else partyVote = STALINIST_PARTY;                                    // otherwise, this Liberal's gone Stalinist and betrayed Liberalism (TRAITOR!)
	 }
	 else if (l % 2 == 1 && LCSrandom(5))
	 {  // Partyline Conservatives (~40%) - except when stalin mode is enabled they can go Stalinist sometimes
		 if (!stalinmode || getswingvoter(true) != -2 || getswingvoter(false) == -2) // if we aren't in stalin mode or they don't agree with Stalinism or they are an Arch-Conservative
			 partyVote = CONSERVATIVE_PARTY;                                    // go with Conservative Party affiliation (Good Loyal Conservative!)
		 else partyVote = STALINIST_PARTY;                                     // otherwise, this Conservative's gone Stalinist and betrayed Conservatism (TRAITOR!)
	 }
	 else // Swing Issue Voters (~20%)
	 {
		 // Get the leanings of an issue voter
		 int vote = getswingvoter(false);
		 // If they agree with the Stalinist candidate and Stalinist mode is enabled,
		 // cast a vote for the Stalinist candidate
		 if (stalinmode&&getswingvoter(true) == -2)
			 partyVote = STALINIST_PARTY;
		 // If they are to the left or equal to the liberal candidate,
		 // and they disagree with the other candidate(s), cast a
		 // vote for the liberal candidate.
		 else if (vote >= liberalCandiadate && vote != conservativeCandiadate)
			 partyVote = LIBERAL_PARTY;
		 // If they are to the right or equal to the conservative candidate,
		 // and they disagree with the other candidate(s), cast a vote
		 // for the conservative candidate.
		 else if (vote <= conservativeCandiadate && vote != liberalCandiadate)
			 partyVote = CONSERVATIVE_PARTY;
		 // If they disagree with all the candidates, vote randomly.
		 else partyVote = LCSrandom(2 + stalinmode);
	 }
	 return partyVote;
 }
 void presidentialElection(const char canseethings) {

	 // IsaacG This is goddamn disgusting.  a candiadate is a single char representing alignment followed by a char* of their name
	 char candidate[3][POLITICIAN_NAMELEN + 1];
	 int votes[3] = { 0,0,0 };
	 //Primaries
	 int approvepres = 0, approveveep = 0;              // presidential & vice-presidential approval within own party
	 int libvotes[3] = { 0,0,0 }, consvotes[3] = { 0,0,0 }; // liberal & conservative parties' candidates votes received
															// run primaries for 100 voters
	 for (int i = 0; i < 100; i++)
	 {
		 int voters[2] = { getsimplevoter(1),getsimplevoter(1) }; // liberal & conservative party voter both decide
		 if (presparty != STALINIST_PARTY) // Stalinist Party doesn't do primaries
		 {
			 // Incumbent can win primary automatically if their approval in their party is over 50%,
			 // so we need to know what their inter-party approval rating is.
			 // check if this voter supports the president (1/2 chance if closely aligned)
			 if (voters[presparty] == exec[EXEC_PRESIDENT] + presparty * 2 || (abs(exec[EXEC_PRESIDENT] + presparty * 2 - voters[presparty]) == 1 && !LCSrandom(2))) approvepres++;
			 // check if this voter supports the vice-president (1/3 chance if closely aligned)
			 if (voters[presparty] == exec[EXEC_VP] + presparty * 2 || (abs(exec[EXEC_VP] + presparty * 2 - voters[presparty]) == 1 && !LCSrandom(3))) approveveep++;
		 }
		 consvotes[voters[CONSERVATIVE_PARTY]]++, libvotes[voters[LIBERAL_PARTY]]++; // count ballots
	 }
	 // determine conservative winner
	 if (consvotes[0] > consvotes[1] && consvotes[0] > consvotes[2]) candidate[CONSERVATIVE_PARTY][0] = ALIGN_ARCHCONSERVATIVE;
	 else if (consvotes[1] > consvotes[2]) candidate[CONSERVATIVE_PARTY][0] = ALIGN_CONSERVATIVE;
	 else candidate[CONSERVATIVE_PARTY][0] = ALIGN_MODERATE;
	 // determine liberal winner
	 if (libvotes[0] > libvotes[1] && libvotes[0] > libvotes[2]) candidate[LIBERAL_PARTY][0] = ALIGN_MODERATE;
	 else if (libvotes[1] > libvotes[2]) candidate[LIBERAL_PARTY][0] = ALIGN_LIBERAL;
	 else candidate[LIBERAL_PARTY][0] = ALIGN_ELITELIBERAL;
	 // Stalinist winner is always Stalinist
	 candidate[STALINIST_PARTY][0] = ALIGN_STALINIST;
	 // approval within own party of Stalinist pres and VP is 100%, since all Stalinist party members have the same political views
	 if (presparty == STALINIST_PARTY) approvepres = 100, approveveep = 100;
	 // name the candidates
	 if (candidate[CONSERVATIVE_PARTY][0] == -2) generate_name(candidate[CONSERVATIVE_PARTY] + 1, GENDER_WHITEMALEPATRIARCH);
	 else if (candidate[CONSERVATIVE_PARTY][0] == -1) generate_name(candidate[CONSERVATIVE_PARTY] + 1, GENDER_MALE);
	 else generate_name(candidate[CONSERVATIVE_PARTY] + 1);
	 generate_name(candidate[LIBERAL_PARTY] + 1);
	 generate_name(candidate[STALINIST_PARTY] + 1);
	 // Special Incumbency Rules: If the incumbent president or vice president
	 // has approval of over 50% in their party, they win their primary
	 // automatically. Even if they don't have over 50%, if their alignment wins
	 // using the normal primary process, they are the chosen candidate for
	 // that alignment (this last bit only applies to President; unpopular VP
	 // candidates just don't run, and if their alignment wins it will be
	 // someone else).
	 if (execterm == 1) // President running for re-election
	 {
		 if (approvepres >= 50) candidate[presparty][0] = exec[EXEC_PRESIDENT];
		 if (candidate[presparty][0] == exec[EXEC_PRESIDENT]) strcpy(candidate[presparty] + 1, execname[EXEC_PRESIDENT]);
		 else execterm = 2; // Boom! Incumbent president was defeated in their
	 }                   // own party. New candidate works with a clean slate.
	 else if (approveveep >= 50 &&                                              // Vice-President running for President
		 (presparty != LIBERAL_PARTY || exec[EXEC_VP] != ALIGN_CONSERVATIVE) && // We don't want conservative liberals
		 (presparty != CONSERVATIVE_PARTY || exec[EXEC_VP] != ALIGN_LIBERAL))   // or liberal conservatives.
	 {
		 if (approvepres >= 50)
		 {
			 candidate[presparty][0] = exec[EXEC_VP];
			 strcpy(candidate[presparty] + 1, execname[EXEC_VP]);
		 }
	 }
	 //Print candidates
	 if (canseethings)
	 {
		 printCandidates(candidate);
	 }
	 int winner = -1;
	 bool recount = false;
	 for (int l = 0; l < 1000; l++) // 1000 Voters!
	 {
		 votes[singleVote(l, candidate[LIBERAL_PARTY][0], candidate[CONSERVATIVE_PARTY][0])]++;
		 if (l % 5 == 4)
		 {
			 int maxvote = 0;
			 for (int c = 0; c < 2 + stalinmode; c++) if (votes[c] > maxvote) maxvote = votes[c];
			 vector<int> eligible;
			 for (int c = 0; c < 2 + stalinmode; c++) if (votes[c] == maxvote) eligible.push_back(c);
			 recount = len(eligible) > 1;
			 winner = pickrandom(eligible);
			 if (canseethings)
			 {
				 for (int c = 0; c < 2 + stalinmode; c++)
				 {
					 printOneSingleVote(votes[c], c, winner, c == winner && recount&&l == 999);
				 }
				 if (!disbanding) pause_ms(40);
				 else pause_ms(20);
			 }
		 }
	 }
	 if (canseethings)
	 {
		 printPressKeyToContinueElections();
		 pressAnyKey();
	 }
	 //else if(disbanding) pause_ms(800);
	 //CONSTRUCT EXECUTIVE BRANCH
	 if (winner == presparty && execterm == 1) execterm = 2;
	 else
	 {
		 clearSleeperPresident();
		 presparty = winner, execterm = 1, exec[EXEC_PRESIDENT] = candidate[winner][0];
		 strcpy(execname[EXEC_PRESIDENT], candidate[winner] + 1);
		 for (int e = EXEC_PRESIDENT + 1; e < EXECNUM; e++) fillCabinetPost(e);
	 }
 }
 bool isPresidentElectionYear() {
	 return year % 4 == 0;
 }
 bool isAnyElectionYear() {
	 return year % 2 == 0;

 }
 int senMod() {
	 return (year % 6) / 2;
 }

 /* politics - causes the people to vote (presidential, congressional, propositions) */
 void elections(char clearformess, char canseethings)
 {
	 if (canseethings)
	 {
		 music.play(MUSIC_ELECTIONS);
		 if (clearformess) eraseAlt();
		 else makedelimiter();
		 printTheElectionsAreHeld();
		 pressAnyKey();
	 }
	 //PRESIDENTIAL
	 if (isPresidentElectionYear())
	 {
		 if (canseethings)
		 {
			 printElectionYearHeader();
		 }
		 presidentialElection(canseethings);
	 }
	 if (isAnyElectionYear())
	 {
		 elections_senate(senMod(), canseethings); //SENATE
		 elections_house(canseethings); //HOUSE
	 }
	 //PROPOSITIONS
	 if (canseethings)
	 {
		 printImportantProps();
		 addStringYear();
	 }
	 vector<int> prop, propdir, canlaw;
	 int pnum = LCSrandom(4) + 4; // this expression for pnum has a maximum value of 7, important later on
	 char lawtaken[LAWNUM];
	 memset(lawtaken, 0, LAWNUM * sizeof(char));
	 int lawpriority[LAWNUM];
	 memset(lawpriority, 0, LAWNUM * sizeof(int));
	 char lawdir[LAWNUM];
	 memset(lawdir, 0, LAWNUM * sizeof(char));
	 //DETERMINE PROPS
	 for (int l = 0; l < LAWNUM; l++)
	 {
		 int pmood = publicmood(l);
		 int pvote = -2;
		 for (int i = 0; i < 4; i++) if (LCSrandom(100) < pmood) pvote++;
		 if (lawList[l] < pvote) lawdir[l] = 1;
		 if (lawList[l] >= pvote) lawdir[l] = -1;
		 if (lawList[l] == -2) lawdir[l] = 1;
		 if (lawList[l] == 2) lawdir[l] = -1;
		 pvote = (lawList[l] + 2) * 25; //CALC PRIORITY
		 lawpriority[l] = abs(pvote - pmood) + LCSrandom(10) + publicinterest(l);
	 }
	 prop.resize(pnum);
	 propdir.resize(pnum);
	 int propnums[7] = { 0,0,0,0,0,0,0 }; // 7 is maximum value for pnum
	 if (canseethings)
	 {
		 for (int p = 0; p < pnum; p++)
		 {
			 int propnum = 0;
			 do
			 {  // this loop prevents duplicate proposition numbers from occurring
				 switch (p)
				 { // 7 entries, as 7 is maximum value for pnum
				 case 0: propnum = 2 * (17 - LCSrandom(2) * 6)*(19 - LCSrandom(2) * 6); break;
				 case 1: propnum = 7 * (17 - LCSrandom(2) * 6)*(19 - LCSrandom(2) * 6); break;
				 case 2: propnum = 3 * (17 - LCSrandom(2) * 6)*(19 - LCSrandom(2) * 6); break;
				 case 3: propnum = 5 * (17 - LCSrandom(2) * 6)*(2 - LCSrandom(2) * 1); break;
				 case 4: propnum = 11 * (17 - LCSrandom(2) * 6)*(2 - LCSrandom(2) * 1); break;
				 case 5: propnum = 13 * (17 - LCSrandom(2) * 6)*(2 - LCSrandom(2) * 1); break;
				 case 6: propnum = 17 * (17 - LCSrandom(2) * 6)*(2 - LCSrandom(2) * 1); break;
				 }
			 } while (std::find(propnums, propnums + p, propnum) != propnums + p); // redo loop if we already used this proposition number, end loop if it's unused
			 propnums[p] = propnum; // put the proposition number we chose into the array, so we don't choose it again for a later proposition
		 }
		 std::sort(propnums, propnums + pnum);
	 }
	 for (int p = 0; p < pnum; p++)
	 {
		 int maxprior = 0;
		 for (int l = 0; l < LAWNUM; l++) if (lawpriority[l] > maxprior && !lawtaken[l]) maxprior = lawpriority[l];
		 canlaw.clear();
		 for (int l = 0; l < LAWNUM; l++) if (lawpriority[l] == maxprior && !lawtaken[l]) canlaw.push_back(l);
		 prop[p] = pickrandom(canlaw);
		 lawtaken[prop[p]] = 1;
		 propdir[p] = lawdir[prop[p]];
		 if (canseethings)
		 {
			 printCurrentProp(p, propnums[p], propdir[p], prop[p]);
		 }
	 }
	 if (canseethings)
	 {
		 printCONST_PRESS_ANY_KEY_TO_WATCH_THE_ELECTIONS_UNFOLD();
		 pressAnyKey();
	 }
	 for (int p = 0; p < pnum; p++)
	 {		 
		 if (voteOnBill(canseethings, publicmood(prop[p]), propdir[p], p)) {
			 lawList[prop[p]] += propdir[p];
		 }
	 }
	 if (canseethings)
	 {
		 printPressKeyToReflect();
		 pressAnyKey();
	 }
 }

 /* politics - causes the supreme court to hand down decisions */
 void supremecourt(char clearformess, char canseethings)
 {
	 if (canseethings)
	 {
		 music.play(MUSIC_ELECTIONS);
		 if (clearformess) eraseAlt();
		 else makedelimiter();
		 printSupremeCourtDecides();
		 pressAnyKey();
	 }
	 //CHANGE THINGS AND REPORT
	 if (canseethings)
	 {
		 printSupremeCourtWatch();
	 }
	 vector<int> scase, scasedir;
	 int cnum = LCSrandom(5) + 2, bias = 0;
	 char lawtaken[LAWNUM];
	 memset(lawtaken, 0, LAWNUM * sizeof(char));
	 scase.resize(cnum);
	 scasedir.resize(cnum);
	 for (int c = 0; c < cnum; c++)
	 {
		 do
		 {
			 scase[c] = LCSrandom(LAWNUM);
		 } while (lawtaken[scase[c]]);
		 lawtaken[scase[c]] = 1;
		 //Constitutional bias -- free speech, flag burning issues, supreme court
		 //is extra liberal, gun control, supreme court is extra conservative
		 if (scase[c] == LAW_FREESPEECH || scase[c] == LAW_FLAGBURNING)bias = 1;
		 else if (scase[c] == LAW_GUNCONTROL)bias = -1;
		 else bias = 0;
		 if (lawList[scase[c]] == 2)scasedir[c] = -1;
		 else if (lawList[scase[c]] == -2)scasedir[c] = 1;
		 else
		 {
			 if (bias)scasedir[c] = bias;
			 else if (!LCSrandom(2))scasedir[c] = 1;
			 else scasedir[c] = -1;
		 }
		 if (canseethings)
		 {

			 string name1, name2;
			 if (!LCSrandom(5)) (name1 = CONST_UNITED_STATES);
			 else name1 = lastname();
			 if ((scase[c] == LAW_LABOR || scase[c] == LAW_CORPORATE ||
				 scase[c] == LAW_ANIMALRESEARCH || scase[c] == LAW_POLLUTION) &&
				 !LCSrandom(5))
			 {
				 name2 = lastname(true) + pickrandom(corporateSuffix);
			 }
			 else {
				 name2 = lastname();
			 }
			 printSupremeCourtRuling(c, name1, name2, scasedir[c], scase[c]);
		 }
	 }
	 if (canseethings)
	 {
		 printPressKeyToWatch();
		 pressAnyKey();
	 }
	 for (int c = 0; c < cnum; c++)
	 {
		 char yeswin = 0;
		 int yesvotes = 0;
		 //Constitutional bias -- free speech, flag burning issues, supreme court
		 //is extra liberal, gun control, supreme court is extra conservative
		 //"All court justices will vote according to alignment and bias and do not consult
		 //popular opinion...---Servant Corps"
		 if (scase[c] == LAW_FREESPEECH || scase[c] == LAW_FLAGBURNING) bias = 1;
		 else if (scase[c] == LAW_GUNCONTROL) bias = -1;
		 else bias = 0;
		 for (int l = 0; l < COURTNUM; l++)
		 {
			 int vote = court[l];
			 if (vote == ALIGN_STALINIST)
			 {
				 if (stalinview(scase[c], true)) vote = ALIGN_ELITELIBERAL;
				 else vote = ALIGN_ARCHCONSERVATIVE;
			 }
			 if (vote >= -1 && vote <= 1) vote += bias;
			 if (lawList[scase[c]] > vote && scasedir[c] == -1) yesvotes++;
			 if (lawList[scase[c]] < vote && scasedir[c] == 1) yesvotes++;
			 if (l == COURTNUM - 1 && yesvotes >= COURTMAJORITY) yeswin = 1;
			 if (canseethings)
			 {
				 printStatusQuoOrChange(l,   c,   yeswin,   yesvotes);
				 pause_ms(60);
			 }
		 }
		 if (yeswin) lawList[scase[c]] += scasedir[c];
	 }
	 if (canseethings)
	 {
		 printPressKeyToReflect();
		 pressAnyKey();
	 }
	 //CHANGE A JUSTICE 40% OF THE TIME
	 if (LCSrandom(10) >= 6)
	 {
		 if (canseethings)
		 {
			 printChangingOfTheGuard();
		 }
		 int j = LCSrandom(COURTNUM);
		 if (canseethings)
		 {
			 printCanSeeCourtB(court[j], courtname[j]);
			 pressAnyKey();
		 }
		 float president = (exec[EXEC_PRESIDENT] == ALIGN_STALINIST ? (float)-3 : (float)exec[EXEC_PRESIDENT]);
		 float sen = 0;
		 for (int s = 0; s < 100; s++) sen += (senate[s] == ALIGN_STALINIST ? (float)-3 : (float)senate[s]);
		 sen /= 100.0f;
		 float consensus = (president + sen)*.5f;
		 if (consensus < -2.1f) court[j] = ALIGN_STALINIST;
		 else if (consensus < -1.5f) court[j] = ALIGN_ARCHCONSERVATIVE;
		 else if (consensus < -.5f) court[j] = ALIGN_CONSERVATIVE;
		 else if (consensus < .5f) court[j] = ALIGN_MODERATE;
		 else if (consensus < 1.5f) court[j] = ALIGN_LIBERAL;
		 else court[j] = ALIGN_ELITELIBERAL;
		 do
		 {
			 if (court[j] == ALIGN_ARCHCONSERVATIVE)
				 generate_name(courtname[j], GENDER_WHITEMALEPATRIARCH);
			 else generate_name(courtname[j]);
		 } while (len(courtname[j]) > 20);
		 if (canseethings)
		 {
			 printCanSeeCourt(court[j], courtname[j]);
			 pressAnyKey();
		 }
	 }
 }
 
 //Some politicians listen to public opinion, but no politician will radically deviate from their alignment.
 //More extreme politicians are less likely to deviate from their views. Moderates always consult public opinion.
 char determine_politician_vote(char alignment, int law)
 {
	 char vote = alignment; // politicians will never sway more than 1 step from this
	 int mood = publicmood(law);
	 int interest = publicinterest(law) / 10;
	 if (vote == ALIGN_STALINIST)
	 {
		 // Stalinist -- Will not accept public opinion
		 if (stalinview(law, true)) vote = ALIGN_ELITELIBERAL;
		 else vote = ALIGN_ARCHCONSERVATIVE;
	 }
	 else if (vote == -2 || vote == 2)
	 {
		 // Extremist -- Highly resistant to public opinion
		 interest -= 10 + LCSrandom(15); 
		 if (interest > 0) {
			 // The masses are scary! Could be swayed, but only one step towards moderation
			 vote = -2;
			 for (int i = 0; i < 4; i++)if (LCSrandom(100) < mood) vote++;
			 if (abs(vote - alignment) > 1) vote = alignment / 2;
		 }
	 }
	 else if (vote == -1 || vote == 1)
	 {
		 // Partisan -- Tends to listen to public opinion only if they're watching
		 interest -= LCSrandom(10);
		 vote = -2;
		 for (int i = 0; i < 4; i++)if (LCSrandom(100) < mood)vote++;
		 if (interest > 0) {
			 if (abs(vote - alignment) > 1) vote = 0;
		 } else if (abs(vote + alignment) < 2){
			 // will compromise with the elites, but not with the moderates
			 vote = alignment;
		 }
	 }
	 else if (vote == 0)
	 {
		 // Moderate -- Listens to public opinion, but won't accept either extreme
		 vote = -2;
		 for (int i = 0; i < 4; i++)if (LCSrandom(100) < mood)vote++;
		 if (abs(vote) > 1)vote = vote / 2;
	 }
	 return vote;
 }
 void determineBills(const char canseethings, vector<int> &bill, vector<int> &billdir) {

	 char lawtaken[LAWNUM];
	 memset(lawtaken, 0, LAWNUM * sizeof(char));
	 int lawpriority[LAWNUM];
	 memset(lawpriority, 0, LAWNUM * sizeof(int));
	 char lawdir[LAWNUM];
	 memset(lawdir, 0, LAWNUM * sizeof(char));

	 for (int l = 0; l < LAWNUM; l++)
	 {
		 int pup = 0;
		 int pdown = 0;
		 int pprior = 0;
		 // Consult House
		 for (int cl = 0; cl < HOUSENUM; cl++)
		 {
			 short housealign = house[cl];
			 if (housealign == ALIGN_STALINIST)
			 {
				 if (stalinview(l, true)) housealign = ALIGN_ELITELIBERAL;
				 else housealign = ALIGN_ARCHCONSERVATIVE;
			 }
			 if (lawList[l] < housealign)pup++;
			 else if (lawList[l] > housealign)pdown++;
			 pprior += abs(housealign - lawList[l]);
		 }
		 // Consult Senate
		 for (int sl = 0; sl < SENATENUM; sl++)
		 {
			 short senatealign = senate[sl];
			 if (senatealign == ALIGN_STALINIST)
			 {
				 if (stalinview(l, true)) senatealign = ALIGN_ELITELIBERAL;
				 else senatealign = ALIGN_ARCHCONSERVATIVE;
			 }
			 if (lawList[l] < senatealign)pup += 4;
			 else if (lawList[l] > senatealign)pdown += 4;
			 pprior += abs(senatealign - lawList[l]) * 4;
		 }
		 // Consult Public Opinion
		 int mood = publicmood(l);
		 int public_position = (mood / 20) - 2;
		 int gravitas = publicinterest(l) * 10;
		 if (lawList[l] < public_position)pup += gravitas;
		 if (lawList[l] > public_position)pdown += gravitas;
		 pprior += abs(public_position - lawList[l]) * ((gravitas + 600) / 2);
		 if (pup > pdown) lawdir[l] = 1;
		 else if (pup == pdown) lawdir[l] = LCSrandom(2) * 2 - 1;
		 else lawdir[l] = -1;
		 if (lawList[l] == -2) lawdir[l] = 1;
		 if (lawList[l] == 2) lawdir[l] = -1;
		 //CALC PRIORITY
		 lawpriority[l] = pprior;
	 }
	 vector<int> canlaw;
	 for (int c = 0; c < bill.size(); c++)
	 {
		 int maxprior = 0;
		 for (int l = 0; l < LAWNUM; l++)
			 if (lawpriority[l] > maxprior && !lawtaken[l])maxprior = lawpriority[l];
		 canlaw.clear();
		 for (int l = 0; l < LAWNUM; l++)
			 if (lawpriority[l] == maxprior && !lawtaken[l])
				 canlaw.push_back(l);
		 bill[c] = pickrandom(canlaw);
		 lawtaken[bill[c]] = 1;
		 billdir[c] = lawdir[bill[c]];
		 if (canseethings)
		 {
			 printDetermineBill(c, billdir[c], bill[c]);
		 }
	 }
 }

 
 BillStatus determineBillStatus(const int billc, const int billdirc, const int c, const char canseethings) {

	 BillStatus killbillc = BILL_PASSED_CONGRESS;

	 char yeswin_h = 0;
	 char yeswin_s = 0;
	 int yesvotes_h = 0;
	 int yesvotes_s = 0;
	 int s = 0;
	 for (int l = 0; l < HOUSENUM; l++)
	 {

		 int vote = determine_politician_vote(house[l], billc);
		 if (lawList[billc] > vote&&billdirc == -1) yesvotes_h++;
		 if (lawList[billc] < vote&&billdirc == 1) yesvotes_h++;
		 if (l == HOUSENUM - 1)
		 {
			 if (yesvotes_h >= HOUSEMAJORITY) yeswin_h = 1;
			 if (yesvotes_h >= HOUSESUPERMAJORITY) killbillc = BILL_OVERRIDE_VETO;
		 }
		 if (canseethings)
		 {
			 displayHouseVotes(l, yesvotes_h, yeswin_h, c);
		 }
		 if (l % 4 == 0 && s < SENATENUM)
		 {
			 vote = determine_politician_vote(senate[s++], billc);
			 if (lawList[billc] > vote&&billdirc == -1) yesvotes_s++;
			 if (lawList[billc] < vote&&billdirc == 1) yesvotes_s++;
		 }
		 if (l == HOUSENUM - 1)
		 {
			 if (yesvotes_s >= SENATEMAJORITY) yeswin_s = 1;
			 if (yesvotes_s < SENATESUPERMAJORITY&&killbillc == BILL_OVERRIDE_VETO) killbillc = BILL_PASSED_CONGRESS;
			 if (yesvotes_s == SENATEMAJORITY - 1)
			 {  //TIE BREAKER
				 int vote;
				 if ((exec[EXEC_VP] >= -1 && exec[EXEC_VP] <= 1) ||
					 (exec[EXEC_PRESIDENT] >= -1 && exec[EXEC_PRESIDENT] <= 1))
					 vote = (exec[EXEC_PRESIDENT] + // only consult Cabinet and random number generator if alignment between -1 and 1
						 exec[EXEC_VP] +        // for President and/or Vice President
						 exec[EXEC_STATE] +
						 exec[EXEC_ATTORNEY] + LCSrandom(9) - 4) / 4;
				 else
				 {
					 vote = exec[EXEC_VP];
					 if (vote == ALIGN_STALINIST)
					 {
						 if (stalinview(billc, true)) vote = ALIGN_ELITELIBERAL;
						 else vote = ALIGN_ARCHCONSERVATIVE;
					 }
				 }
				 if (lawList[billc] > vote&&billdirc == -1) yeswin_s = 1;
				 if (lawList[billc] < vote&&billdirc == 1) yeswin_s = 1;
				 //ASSURED SIGNING BY PRESIDENT IF VP VOTED YES
				 if (yeswin_s) killbillc = BILL_SIGNED;
			 }
		 }
		 if (canseethings)
		 {
			 displaySenateVotes(l, yesvotes_s, yeswin_s, c, s);
		 }
	 }
	 if (!yeswin_h || !yeswin_s) killbillc = BILL_FAILED;
	 return killbillc;
 }
vector<int> getHouseMake() {

	 vector<int> housemake = { 0,0,0,0,0,0 };
	 for (int h = 0; h < HOUSENUM; h++) housemake[house[h] + 2]++;
	 return housemake;
 }
vector<int> getSenateMake() {

	 vector<int> senatemake = { 0,0,0,0,0,0 };
	 for (int s = 0; s < SENATENUM; s++) senatemake[senate[s] + 2]++;
	 return senatemake;
 }
 /* politics - causes congress to act on legislation */
 void congress(char clearformess, char canseethings)
 {
	 if (canseethings)
	 {
		 music.play(MUSIC_ELECTIONS);
		 displayCongressHeader(clearformess);
		 pressAnyKey();
		 displayCongressHeaderPartOne();
	 }
	 vector<int> bill, billdir;
	 vector<BillStatus> killbill;
	 int cnum = LCSrandom(3) + 1;
	 bill.resize(cnum);
	 billdir.resize(cnum);
	 killbill.resize(cnum);

	 //DETERMINE BILLS
	 determineBills(canseethings, bill, billdir);

	 if (canseethings)
	 {
		 displayCongressHeaderPartTwo();
	 }
	 for (int c = 0; c < cnum; c++)
	 {
		 killbill[c] = determineBillStatus(bill[c], billdir[c], c, canseethings);
	 }
	 int havebill = 0;
	 for (int c = 0; c < cnum; c++) if (killbill[c] != BILL_FAILED) havebill++;
	 if (havebill)
	 {
		 if (canseethings)
		 {
			 printWatchPresident();
			 pressAnyKey();
			 printWatchPresidentB();
			 pause_ms(500);
		 }
		 for (int c = 0; c < len(bill); c++)
		 {
			 if (killbill[c] != BILL_FAILED)
			 {
				 int vote;
				 if (exec[EXEC_PRESIDENT] >= -1 && exec[EXEC_PRESIDENT] <= 1)
					 vote = (exec[EXEC_PRESIDENT] + // only consult Cabinet and random number generator if alignment between -1 and 1
						 exec[EXEC_VP] +        // for President
						 exec[EXEC_STATE] +
						 exec[EXEC_ATTORNEY] + LCSrandom(9) - 4) / 4;
				 else
				 {
					 vote = exec[EXEC_PRESIDENT];
					 if (vote == ALIGN_STALINIST)
					 {
						 if (stalinview(bill[c], true)) vote = ALIGN_ELITELIBERAL;
						 else vote = ALIGN_ARCHCONSERVATIVE;
					 }
				 }
				 //todo make this check sleeper state.
				 int pres_status = getSleeperPresidentStatus();
				 if (pres_status > 0)
				 {
					 if (pres_status == 1)
					 {
						 //temp to test id refactor
						 
						 vote = ALIGN_ELITELIBERAL;
					 }
					 else if (pres_status == 2)
					 {
						 //VP rushes because waiting on the President until last minute and does not consult Cabinet
						 vote = exec[EXEC_VP];
						 monthsPresidentMissing++;
						 //(right now the handling of the missing president is not realistic or interesting. However I feel it's better than nothing
						 //President has been missing for too long. Promote VP and just remove them.
						 //if (monthsPresidentMissing > (monthsPresidentMissing + LCSrandom(7 - 1)))
						 if (monthsPresidentMissing > (monthsPresidentMissing + LCSrandom(7 - 1)))
						 {
							 promoteVP();
							 monthsPresidentMissing = 0;

						 }
					 }
				 }
				 //President has reappeared.
				 if (pres_status != 2)
					 monthsPresidentMissing = 0;
					 
				 if ((lawList[bill[c]] > vote&&billdir[c] == -1) || (lawList[bill[c]] < vote&&billdir[c] == 1)) killbill[c] = BILL_SIGNED;
			 }
			 if (canseethings)
			 {
				 printBillResults(static_cast<BillStatus> (killbill[c]), c);
				 pause_ms(500);
			 }
			 if (killbill[c] == BILL_SIGNED || killbill[c] == BILL_OVERRIDE_VETO) lawList[bill[c]] += billdir[c];
		 }
		 if (canseethings)
		 {
			 printReflectOnBill();
			 pressAnyKey();
		 }
	 }
	 else if (canseethings)
	 {
		 printDeadInCongress();
		 pressAnyKey();
	 }
	 //CONGRESS CONSTITUTION CHANGES
	 vector<int> housemake = getHouseMake();
	 vector<int> senatemake = getSenateMake();
	 // Throw out non-L+ Justices?
	 bool tossj = false;
	 for (int j = 0; j < COURTNUM; j++) if (court[j] != ALIGN_ELITELIBERAL) tossj = true;
	 if (housemake[4] + housemake[3] / 2 >= HOUSESUPERMAJORITY && senatemake[4] + senatemake[3] / 2 >= SENATESUPERMAJORITY && tossj && !nocourtpurge)
		 tossjustices(canseethings);
	 // Purge Congress, implement term limits, and hold new elections?
	 if ((housemake[4] + housemake[3] / 2 < HOUSESUPERMAJORITY || senatemake[4] + senatemake[3] / 2 < SENATESUPERMAJORITY) && publicmood(-1) > 80 && !notermlimit)
		 amendment_termlimits(canseethings);
	 // LET ARCH-CONSERVATIVES REPEAL THE CONSTITUTION AND LOSE THE GAME?
	 if (housemake[0] >= HOUSESUPERMAJORITY && senatemake[0] >= SENATESUPERMAJORITY)
		 attemptAmendmentEnding(canseethings, ALIGN_ARCHCONSERVATIVE);
	 // LET STALINISTS REPEAL THE CONSTITUTION AND LOSE THE GAME?
	 if (housemake[5] >= HOUSESUPERMAJORITY && senatemake[5] >= SENATESUPERMAJORITY)
		 attemptAmendmentEnding(canseethings, ALIGN_STALINIST);
 }
 /* politics - checks if the game is won */
 char wincheck()
 {
	 for (int e = 0; e < EXECNUM; e++) if (exec[e] < ALIGN_ELITELIBERAL) return 0;
	 if (wincondition == WINCONDITION_ELITE) for (int l = 0; l < LAWNUM; l++) if (lawList[l] < ALIGN_ELITELIBERAL) return 0;
	 else
	 {
		 int liberalLaws = 0, eliteLaws = 0;
		 for (int l = 0; l < LAWNUM; l++)
		 {
			 if (lawList[l] < ALIGN_LIBERAL) return 0;
			 if (lawList[l] == ALIGN_LIBERAL) liberalLaws++;
			 else eliteLaws++;
		 }
		 if (eliteLaws < liberalLaws) return 0;
	 }
	 int housemake[6] = { 0,0,0,0,0,0 };
	 for (int h = 0; h < HOUSENUM; h++) housemake[house[h] + 2]++;
	 if (housemake[4] + housemake[3] / 2 < ((wincondition == WINCONDITION_ELITE) ? HOUSESUPERMAJORITY : HOUSECOMFYMAJORITY)) return 0; // Elite Libs plus half of Libs >= 3/5 for easy, 2/3 for elite
	 if (housemake[4] < ((wincondition == WINCONDITION_ELITE) ? HOUSECOMFYMAJORITY : HOUSEMAJORITY)) return 0; // Elite Libs themselves >= 1/2 for easy, 3/5 for elite
	 int senatemake[6] = { 0,0,0,0,0,0 };
	 for (int s = 0; s < SENATENUM; s++) senatemake[senate[s] + 2]++;
	 if (senatemake[4] + senatemake[3] / 2 < ((wincondition == WINCONDITION_ELITE) ? SENATESUPERMAJORITY : SENATECOMFYMAJORITY)) return 0; // Elite Libs plus half of Libs >= 3/5 for easy, 2/3 for elite
	 if (wincondition != WINCONDITION_ELITE) senatemake[exec[EXEC_VP] + 2]++; // VP counts as Senator only for breaking ties (so counts for 1/2 fraction but not higher fractions)
	 if (senatemake[4] < ((wincondition == WINCONDITION_ELITE) ? SENATECOMFYMAJORITY : SENATEMAJORITY)) return 0; // Elite Libs themselves >= 1/2 for easy, 3/5 for elite
	 int elibjudge = 0, libjudge = 0;
	 for (int c = 0; c < COURTNUM; c++)
	 {
		 if (court[c] == ALIGN_ELITELIBERAL) elibjudge++;
		 if (court[c] == ALIGN_LIBERAL) libjudge++;
	 }
	 if (elibjudge < COURTMAJORITY && (wincondition == WINCONDITION_ELITE || elibjudge + libjudge / 2 < COURTSUPERMAJORITY)) return 0;
	 return 1;
 }
