
#include "../includes56.h"
#include "../constStringhelp.h"

#include "../cursesAlternative.h"
#include "../set_color_support.h"
// {{{ Various voids
// Help pages are drawn here.
// NOTE: This will probably need updating if there are any fundamental code
// changes that will change gameplay.
map<short, vector<string> > helpTopics;
//string liberalHelpOn;
//string pressAnyKeyToReturn;
void help(const char* string)
{
	eraseAlt();
}
// Generates help page on activities.
// Just supply Activity type.
void HelpActivities(int activityType)
{
	//
	if (activityType == ACTIVITY_NONE)
	{
		return;
	}
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, liberalHelpOn);
	vector<string> helpTopic;
	if (helpTopics.count(activityType)) {
		helpTopic = helpTopics[activityType];
	}
	else {
		helpTopic = helpTopics[-1];
	}
	mvaddstrAlt(2, 0, helpTopic[0]);
	for (int i = 0; i < len(helpTopic) - 1; i++) {
		mvaddstrAlt(4 + i, 0, helpTopic[i + 1]);
	}
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, pressAnyKeyToReturn);
	pressAnyKey();
}
