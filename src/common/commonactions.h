

/* common - test for possible game over */
char endcheck(char cause = END_OTHER);
/* common - applies a crime to everyone in the active party */
void criminalizeparty(short crime);
/* common - applies a crime to everyone in a location, or the entire LCS */
void criminalizepool(short crime, long exclude = -1, short loc = -1);
/* common - gives juice to everyone in the active party */
void juiceparty(long juice, long cap);
/* common - purges empty squads from existance */
void cleangonesquads();
/* common - shifts public opinion on an issue */
void change_public_opinion(int v, int power, char affect = 1, char cap = 100);
/* common - random issue by public interest */
int randomissue(bool core_only = 0);
// Picks a random option, based on the weights provided
int choose_one(const int * weight_list, int number_of_options, int default_value);
/* common - Prompt to decide how to sort liberals.*/
void sorting_prompt(short listforsorting);
/* common - Returns appropriate sortingchoice enum value for a reviewmode enum value.
(Is currently unnecessary unless the enums are changed.)*/
short reviewmodeenum_to_sortingchoiceenum(short reviewmode);
/* common - Display a list of options and return choice. */
int choiceprompt(const string &firstline, const string &secondline,
	const vector<string> &option, const string &optiontypename,
	bool allowexitwochoice, const string &exitstring = "");
/* common - Displays a list of things to buy and returns an int corresponding
to the index of the chosen thing in the nameprice vector. */
int buyprompt(const string &firstline, const string &secondline,
	const vector< pair<string, int> > &nameprice, int namepaddedlength,
	const string &producttype, const string &exitstring);