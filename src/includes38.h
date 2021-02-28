




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
#include "cmarkup/Markup.h"
using namespace std;

#include "includesDeprecated.h"
#include "includesRandom.h"
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

#include "includesDeprecatedB.h"
//#ifdef	GAME_CPP
// game.cpp

#include "creature/newcreature.h"
#include "../items/armortype.h"
#include "common/interval.h"
#include "vehicle/vehicletype.h"
#include "vehicle/vehicle.h"
//#include "news/news.h"
void loadgraphics();
#include "items/loottype.h"
#include "creature/augmenttype.h"
//#include "configfile.h"
// Reads in an entire configuration file
// Returns 0 for read successful, returns -1 if failed read
int readConfigFile(const std::string& filename);
#include "log/log.h"
//for the gamelog
//#include "common/consolesupport.h"
// for getkey
#include "common/stringconversion.h"
//for string conversion
//#include "common/getnames.h"
std::string cityname();
#include "common/translateid.h"
// for  getarmortype 
#include "title/initfile.h"
//for void loadinitfile();
#include "title/titlescreen.h"
//for void mode_title();
#include "common/creaturePool.h"
#include "locations/locationsPool.h"
#include "cursesAlternative.h"
#include "customMaps.h"
/* end the game and clean up */
void end_game(int err = EXIT_SUCCESS);
bool fixcleartype = false;
struct pointerAndString {
	bool *super_collection;
	string fileName;
	pointerAndString(bool *super_, const string& file_) : fileName(file_), super_collection(super_) {}
};
struct fullName {
	string first;
	string middle;
	string last;

};
void init_console();
void initialize_debug_defines();
#include "common/musicClass.h"
const int CITY_NAMELEN = 80;


bool mainSeven(bool xml_loaded_ok);
extern bool DISPLAYDEBUG;
extern bool PERFECTLAWS;
extern bool REVOLUTIONNOW;
extern bool SHITLAWS;
extern char artdir[MAX_PATH_SIZE];
extern char courtname[COURTNUM][POLITICIAN_NAMELEN];
extern char execname[EXECNUM][POLITICIAN_NAMELEN];
extern char lcityname[CITY_NAMELEN];
extern Log gamelog; //The gamelog.
extern MusicClass music;
extern short  exec[EXECNUM];
extern short activesortingchoice[SORTINGCHOICENUM];
extern short attitude[VIEWNUM];
extern short background_liberal_influence[VIEWNUM];
extern short court[COURTNUM];
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short public_interest[VIEWNUM];
extern short senate[SENATENUM];
extern unsigned long attorneyseed[RNG_SIZE];
extern vector<file_and_text_collection> activate_text_file_collection;
extern vector<file_and_text_collection> activities_text_file_collection;
extern vector<file_and_text_collection> baseactions_text_file_collection;
extern vector<file_and_text_collection> chase_text_file_collection;
extern vector<file_and_text_collection> common_text_file_collection;
extern vector<file_and_text_collection> creature_text_file_collection;
extern vector<file_and_text_collection> creaturetypes_text_file_collection;
extern vector<file_and_text_collection> date_text_file_collection;
extern vector<file_and_text_collection> endgame_text_file_collection;
extern vector<file_and_text_collection> externally_stored_data_text_file_collection;
extern vector<file_and_text_collection> fighty_text_file_collection;
extern vector<file_and_text_collection> get_names_text_file_collection;
extern vector<file_and_text_collection> globals_text_file_collection;
extern vector<file_and_text_collection> interrogate_text_file_collection;
extern vector<file_and_text_collection> justice_text_file_collection;
extern vector<file_and_text_collection> liberl_agenda_text_file_collection;
extern vector<file_and_text_collection> locations_text_file_collection;
extern vector<file_and_text_collection> locationspool_text_file_collection;
extern vector<file_and_text_collection> majorevent_text_file_collection;
extern vector<file_and_text_collection> map_specials_text_file_collection;
extern vector<file_and_text_collection> misc_activities_text_file_collection;
extern vector<file_and_text_collection> misc_text_file_collection;
extern vector<file_and_text_collection> names_text_file_collection;
extern vector<file_and_text_collection> newgame_file_collection;
extern vector<file_and_text_collection> politics_text_file_collection;
extern vector<file_and_text_collection> reviewmode_text_file_collection;
extern vector<file_and_text_collection> siege_text_file_collection;
extern vector<file_and_text_collection> stealth_text_file_collection;
extern vector<file_and_text_collection> talk_file_collection;
extern vector<file_and_text_collection> title_screen_text_files;
extern vector<pointerAndString> debug_defines;
fullName generate_long_name(char gender = GENDER_NEUTRAL);

void set_title(char *s);
const string defaultMissingForMask = "Default missing for masks!";
const string defaultUnknownForMask = "Default for masks is not a known armor type!";
const string ACTIVATED = " ACTIVATED";
const string debugCode = "debug code ";
const string failedToLoadSitemaps = "Failed to load sitemaps.txt! Reverting to old map mode.";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string CONST_MASKTYPE = "masktype";
const string CONST_DEFAULT = "default";
const string CONST_UNSPECIFIED_ERROR_WITH_CUSTOM_TEXT = "Unspecified error with custom text";
//const string CONST_WE_NEED_A_SLOGAN = "We need a slogan!";
const string CONST_DEBUG_DEFINES_TXT = "debug_defines.txt";
const string CONST_FILE_ERROR_INITIATEMOREINCOMPLETETEXT = "File Error: InitiateMoreIncompleteText";
const string CONST_FILE_ERROR_INITIATEINCOMPLETETEXT = "File Error: InitiateIncompleteText";
const string CONST_FILE_ERROR = "File Error: ";
const string CONST_COMMENT_FOUND = "Comment Found";
const string CONST_SITEMAPS_TXT = "sitemaps.txt";
const string CONST_LIBERAL_CRIME_SQUAD = "Liberal Crime Squad ";

//#endif//GAME_CPP
//#endif// INCLUDES_H_INCLUDED
