#pragma once
// Sets the text color to the thematic color for the given alignment
// extended_range forces colors to be set on a 5 point scale instead
// of just basic liberal-moderate-conservative
void set_alignment_color(short alignment, bool extended_range = false);
/* Sets the text color per activity type */
void set_activity_color(long activity_type);
/* location and squad header */
void locheader();
/* party info at top of screen */
void printparty();
/* location info at top of screen */
void printlocation(long loc);
/* full character sheet (with surrounding interface) */
void fullstatus(int p);
/* draws a horizontal line across the screen */
void makedelimiter(int y = 8, int x = 0);
/* prints amount of money the player has, with optional formatting */
void printfunds(int y = 0, int offset = 1, const char* prefix = "Money: ");
/* returns a short blurb showing how to page forward */
string addnextpagestr();
/* returns a short blurb showing how to page back */
string addprevpagestr();
/* returns a long blurb showing how to page forward and back */
string addpagestr();

/* addstr with formatted output */
int addstr_f(const char * format, ...);
/* mvaddstr with formatted output */
int mvaddstr_f(int y, int x, const char * format, ...);
