




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

//#include "includesDeprecatedB.h"
//#ifdef	LCSIO_CPP
// lcsio.cpp

#include <tinydir.h>
extern char homedir[MAX_PATH_SIZE];
extern char artdir[MAX_PATH_SIZE];
const string NEWSPIC_CPC = "newspic.cpc";
const string CONST_DAT = ".dat";
const string CONST_DOT = ".";
const string CONST_LCS = ".lcs/";
const string CONST_SLASH = "/";
const string DOT_SLASH = "./";
const string CONST_HOME = "HOME";
const string CONST_X_PARENT_ART_FOLDER = "../art/";
const string CONST_X_ART_FOLDER = "./art/";
const string CONST_USR_GAMES_LCS_ART = "/usr/games/lcs/art/";
const string CONST_USR_GAMES_SHARE_LCS_ART = "/usr/games/share/lcs/art/";
const string CONST_USR_SHARE_LCS_ART = "/usr/share/lcs/art/";
const string CONST_USR_LOCAL_SHARE_LCS_ART = "/usr/local/share/lcs/art/";
const string CONST_LCS_ART = "/lcs/art/";
const string CONST_SCORE = "score";

//#endif//LCSIO_CPP
//#endif// INCLUDES_H_INCLUDED
