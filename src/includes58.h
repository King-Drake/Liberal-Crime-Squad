




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
#include "cmarkup/Markup.h" //For XML.
using namespace std;

#include "includesDeprecated.h"
#include "includesRandom.h"
//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
#include "activityST.h"

//int get_associated_attribute(int skill_type);

#include "includesSDS.h"
#include "includesSDS2.h"
// creaturePool.cpp


#include "../creature/creature.h"

#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/creaturePool.h"
#include "../common/creaturePoolCreature.h"
#include "../cursesAlternative.h"
#include "../log/log.h"
#include "../sitemode/advance.h"
/* handles end of round stuff for one creature */
void advancecreature(DeprecatedCreature &cr);
#include "../common/commonactionsCreature.h"
#include "../combat/fightCreature.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../set_color_support.h"
#include "../common/commondisplay.h"
#include "../common/commondisplayCreature.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../common/getnames.h"
#include "../common/translateid.h"
// for  int getpoolcreature(int)
#include "../daily/siege.h"
#include "../common/commonactions.h"

enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};



enum DispersalTypes
{
	DISPERSAL_SAFE = -1,
	DISPERSAL_BOSSSAFE,
	DISPERSAL_NOCONTACT,
	DISPERSAL_BOSSINPRISON,
	DISPERSAL_HIDING,
	DISPERSAL_BOSSINHIDING,
	DISPERSAL_ABANDONLCS
};
extern Log gamelog;
extern char disbanding;
extern int stat_recruits;
extern class Ledger ledger;
extern vector<Deprecatedsquadst *> squad;
extern MusicClass music;
extern short lawList[LAWNUM];

//#include "../monthly/justice.h"
void trial(DeprecatedCreature &g);
char prison(DeprecatedCreature &g);
//#include "../monthly/sleeper_update.h"
void sleepereffect(DeprecatedCreature &cr, char &clearformess, char canseethings, int(&libpower)[VIEWNUM]);
void savehighscore(char endtype);
void viewhighscores(int musicoverride = MUSIC_OFF);
void end_game(int err = EXIT_SUCCESS);
short getCurrentSite();
extern UniqueCreatures uniqueCreatures;
extern long curcreatureid;
extern vector<Deprecatedrecruitst*> recruit;
