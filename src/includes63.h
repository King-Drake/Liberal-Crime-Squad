




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


//#include "includesDeprecatedB.h"
#include "includesSDS.h"
#include "includesSDS2.h"

// chase.cpp

#include "../creature/creature.h"
////


#include "../creature/deprecatedCreatureC.h"

#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../vehicle/vehicletype.h"
#include "../vehicle/vehicle.h"
//#include "basemode/baseactions.h"
void orderparty();
//#include "sitemode/advance.h"
void creatureadvance();
#include "../sitemode/sitedisplay.h"
//#include "sitemode/miscactions.h"
void reloadparty(bool wasteful = false);
#include "../log/log.h"
// for gamelog
#include "../common/translateid.h"
// for  int id_getcar(int)
#include "../common/commondisplay.h"
// for addstr (with log)
#include "../common/commonactions.h"
#include "../common/commonactionsCreature.h"
//#include "common/equipment.h"
void equip(vector<Item *> &loot, int loc);
#include "fight.h"
#include "fightCreature.h"  
// for void youattack();
#include "haulkidnapCreature.h"
// for  void kidnaptransfer(Creature &cr);
#include "../cursesAlternative.h"
#include "../customMaps.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
#include "../common/creaturePool.h"
enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};
vector<NameAndAlignment> getEncounterNameAndAlignment();
void make_creature_without_encounter_array(const int x, const short type);
const string hereTheyCome = "Here they come!";
const string BEING_FOLLOWED = "being followed by Conservative swine!";
const string lostThem = "It looks like you've lost them!";
const string isSeized = " is seized, ";

const string CARCHASE_OBSTACLE_CHILD_TXT = "carchase_obstacle_child.txt";
const string CARCHASE_OBSTACLE_CROSS_TRAFFIC_TXT = "carchase_obstacle_cross_traffic.txt";
const string CARCHASE_OBSTACLE_TRUCK_PULLS_OUT_TXT = "carchase_obstacle_truck_pulls_out.txt";
const string CARCHASE_OBSTACLE_FRUIT_STAND_TXT = "carchase_obstacle_fruit_stand.txt";
const string CARCHASE_OBSTACLE_NONE_TXT = "carchase_obstacle_none.txt";
const string DIE_IN_CAR_TXT = "die_in_car.txt";
const string CAR_CRASH_FATALITIES_TXT = "car_crash_fatalities.txt";
const string CAR_CRASH_MODES_TXT = "car_crash_modes.txt";
const string CAR_PLOWS_THROUGH_TXT = "car_plows_through.txt";
const string CAR_SPEED_TXT = "car_speed.txt";

const string IS_STILL_ON_YOUR_TAIL = " is still on your tail!";
const string C_REFLECT_ON_YOUR_LACK_OF_SKILL = "C - Reflect on your lack of skill.";
const string F_FIGHT = "F - Fight!";
const string E_EQUIP = "E - Equip";
const string D_TRY_TO_LOSE_THEM = "D - Try to lose them!";

const string tag_POLICECAR = "POLICECAR";
const string tag_The = "The ";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string chase = "chase\\";
const string IS_FREE = " is free.";
const string S_ARE_FREE = "s are free.";
const string YOUR_HOSTAGE = "Your hostage";
const string YOU_PULL_OVER_AND_ARRESTED = "You pull over and are arrested.";
const string YOU_STOP_AND_ARE_ARRESTED = "You stop and are arrested.";
const string YOU_SCALE_A_SMALL_BUILDING = "You scale a small building and leap between rooftops!";
const string YOU_CLIMB_A_FENCE = "You climb a fence in record time!";
const string YOU_RUN_AS_FAST_AS_YOU_CAN = "You run as fast as you can!";
const string YOU_SUDDENLY_DART_INTO_ALLEY = "You suddenly dart into an alley!";
const string THROWN_TO_GROUND_AND_TAZED = "thrown to the ground, and tazed repeatedly!";
const string THROWN_TO_GROUND_TAZED_TO_DEATH = "thrown to the ground, and tazed to death!";
const string PUSHED_TO_GROUND_HANDCUFFED = "pushed to the ground, and handcuffed!";
const string THROWN_TO_GROUND_AND_SHOT = "thrown to the ground, and shot in the head!";
const string CRUSHED_BENEATH_TANK = " crushed beneath the tank's treads!";
const string THROWN_TO_GROUND_AND_BEATEN_SENSELESS = "thrown to the ground, and beaten senseless!";
const string THROWN_TO_GROUND_AND_BEATEN_DEAD = "thrown to the ground, and beaten to death!";
const string BREAKS_AWAY = " breaks away!";
const string CANT_KEEP_UP = " can't keep up!";
const string TIPS_INTO_A_POOL_TANK_IS_TRAPPED = " tips into a pool. The tank is trapped!";
const string CONST_X_G_GIVE_UP = "G - Give Up";
const string AS_YOU_EXIT_YOU_NOTICE = "As you exit the site, you notice that you are ";
const string BRAKES_HARD = " brakes hard and nearly crashes!";
const string BACKS_OFF = " backs off for safety.";
const string SKIDS_OUT = " skids out!";
const string FALLS_BEHIND = " falls behind!";
const string YOU_MAKE_OBSCENE_GESTURES = "You make obscene gestures at the pursuers!";
const string YOU_BOLDLY_WEAVE_THROUGH_TRAFFIC = "You boldly weave through oncoming traffic!";
const string CRAWLS_FREE_OF_CAR = " crawls free of the car, shivering with pain.";
const string GASPS_IN_PAIN_BUT_LIVES = " gasps in pain, but lives, for now.";
const string FEET_PERIOD = " feet.";
const string WHEELCHAIR_PERIOD = " wheelchair.";
const string AND_STRUGGLES_TO = " and struggles to ";
const string CAR_FRAME = "car frame";
const string GRIPS_THE_SPACE = " grips the ";
const string SEAT_OUT_COLD_AND_DIES = " seat, out cold, and dies.";
const string SLUMPS_IN = " slumps in ";
const string YOUR_SPACE = "Your ";
const string TAKES_OVER_THE_WHEEL = " takes over the wheel.";
const string YOU_SWERVE_TO_AVOID = "You swerve to avoid the obstacle!";
const string P_PULL_OVER = "P - Pull over";
const string B_BAIL_OUT = "B - Bail out and run!";
const string AS_YOU_PULL_AWAY_YOU_NOTICE = "As you pull away from the site, you notice that you are ";
const string STATIONWAGON = "STATIONWAGON";
const string CONST_X_PICKUP = "PICKUP";
const string CONST_X_JEEP = "JEEP";
const string CONST_X_SUV = "SUV";
const string AGENTCAR = "AGENTCAR";
const string CONST_X_HMMWV = "HMMWV";
//crashenemycar

const string HITS_A_PARKED_CAR = " hits a parked car and flips over.";
const string PERSON_INSIDE_IS_SQUASHED_INTO_CUBE = "The person inside is squashed into a cube.";
const string EVERYONE_INSIDE_PEELED_OFF_AGAINST_PAVEMENT = "Everyone inside is peeled off against the pavement.";
const string SPINS_OUT_AND_CRASHES = " spins out and crashes.";
const string SLAMS_INTO_BUILDING = " slams into a building.";
// obstacledrive

const string BOTH_SIDES_AVOID_ENDANGERING_CHILD = "Both sides refrain from endangering the child...";
const string CONSERVATIVES_UNLEASH_GUNFIRE = "The Conservative bastards unleash a hail of gunfire!";
const string YOU_SLOW_DOWN_AND_AVOID_KID = "You slow down and carefully avoid the kid.";
const string FRUIT_SELLER_IS_SQUASHED = "The fruit seller is squashed!";
const string FRUIT_SMASHES_ALL_OVER_WINDSHIELD = "Fruit smashes all over the windshield!";
const string YOU_SLOW_DOWN_AND_EVADE = "You slow down, and carefully evade the truck.";
const string YOU_SLOW_DOWN = "You slow down, and turn the corner.";

const int DRIVING_RANDOMNESS = 13;
extern char endgamestate;
extern char foughtthisround;
extern chaseseqst chaseseq;
extern DeprecatedCreature encounter[ENCMAX];
extern Deprecatednewsstoryst *sitestory;
extern Deprecatedsquadst *activesquad;
extern int stat_dead;
extern Log gamelog;
extern long cursquadid;
extern MusicClass music;
extern short fieldskillrate;
extern short lawList[LAWNUM];
extern short mode;
extern short party_status;
int baddieCount();
int baddieCount(const bool in_car);
int driveskill(DeprecatedCreature &cr, int v);
int encounterSize();
int getEncounterCarID(const int p);
Vehicle* getVehicleOfThisType(int cartype);
void addCreatueVehiclesToCollection(DeprecatedCreature *cr[6], vector<Vehicle *> &veh);
void conservatise(const int e);
void deleteVehicles(vector<Vehicle *>& carid);
void removeCreatureFromSquad(DeprecatedCreature &cr, int oldsqid);


void emptyEncounter();

vector<string> car_speed;
vector<string> car_plows_through;
vector<string> car_crash_modes;
vector<string> car_crash_fatalities;
vector<string> die_in_car;
vector<string> carchase_obstacle_none;
vector<string> carchase_obstacle_fruit_stand;
vector<string> carchase_obstacle_truck_pulls_out;
vector<string> carchase_obstacle_cross_traffic;
vector<string> carchase_obstacle_child;
vector<file_and_text_collection> chase_text_file_collection = {
	/*chase.cpp*/
	customText(&car_speed, chase + CAR_SPEED_TXT),
	customText(&car_plows_through, chase + CAR_PLOWS_THROUGH_TXT),
	customText(&car_crash_modes, chase + CAR_CRASH_MODES_TXT),
	customText(&car_crash_fatalities, chase + CAR_CRASH_FATALITIES_TXT),
	customText(&die_in_car, chase + DIE_IN_CAR_TXT),
	customText(&carchase_obstacle_none, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_NONE_TXT),
	customText(&carchase_obstacle_fruit_stand, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_FRUIT_STAND_TXT),
	customText(&carchase_obstacle_truck_pulls_out, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_TRUCK_PULLS_OUT_TXT),
	customText(&carchase_obstacle_cross_traffic, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_CROSS_TRAFFIC_TXT),
	customText(&carchase_obstacle_child, MOSTLY_ENDINGS_FOLDER + CARCHASE_OBSTACLE_CHILD_TXT),
};
map<short, vector<string> > carchaseObstacles;


//#endif//CHASE_CPP
//#endif// INCLUDES_H_INCLUDED
