#pragma once

/*
 politics.cpp
*/
/* politics - calculate presidential approval */
int presidentapproval();
/* politics -- gets the leaning of an issue voter for an election */
int getswingvoter(bool stalin);
/* politics -- gets the leaning of a partyline voter for an election */
int getsimplevoter(int leaning);

/* politics -- appoints a figure to an executive office, based on the President's alignment */
void fillCabinetPost(int position);
/* politics - causes the people to vote (presidential, congressional, propositions) */
void elections(char clearformess, char canseethings);
void elections_senate(int senmod, char canseethings);
void elections_house(char canseethings);
/* politics - causes the supreme court to hand down decisions */
void supremecourt(char clearformess, char canseethings);
/* politics - causes congress to act on legislation */
void congress(char clearformess, char canseethings);
// letter of amnesty to the LCS from the President (you win)
void amnesty();
/* politics - checks if the game is won */
char wincheck();
/* politics - checks the prevailing attitude on a specific law, or overall */
int publicmood(int l);
/* politics - checks the public's interest in a specific law, or overall*/
int publicinterest(int i);

/* returns true if Stalinists agree with Elite Liberals on a view/law, false if they strongly disagree with libs  *
 * the input bool islaw, if true, returns Stalinist opinion on laws, if false, returns Stalinist opinion on views */
bool stalinview(short view, bool islaw);

