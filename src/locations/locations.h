#pragma once
//#include "common.h"
#include "locationsEnums.h"


const int SITEBLOCK_EXIT = BIT1;
const int SITEBLOCK_BLOCK = BIT2;
const int SITEBLOCK_DOOR = BIT3;
const int SITEBLOCK_KNOWN = BIT4;
const int SITEBLOCK_LOOT = BIT5;
const int SITEBLOCK_LOCKED = BIT6;
const int SITEBLOCK_KLOCK = BIT7;
const int SITEBLOCK_CLOCK = BIT8;
const int SITEBLOCK_RESTRICTED = BIT9;
const int SITEBLOCK_BLOODY = BIT10;
const int SITEBLOCK_BLOODY2 = BIT11;
const int SITEBLOCK_GRASSY = BIT12;
const int SITEBLOCK_OUTDOOR = BIT13;
const int SITEBLOCK_DEBRIS = BIT14;
const int SITEBLOCK_GRAFFITI = BIT15;
const int SITEBLOCK_GRAFFITI_CCS = BIT16;
const int SITEBLOCK_GRAFFITI_OTHER = BIT17;
const int SITEBLOCK_FIRE_START = BIT18;
const int SITEBLOCK_FIRE_PEAK = BIT19;
const int SITEBLOCK_FIRE_END = BIT20;
const int SITEBLOCK_CHAINLINK = BIT21;
const int SITEBLOCK_ALARMED = BIT22;
const int SITEBLOCK_METAL = BIT23;

const int SIEGEFLAG_UNIT = BIT1;
const int SIEGEFLAG_TRAP = BIT2;
const int SIEGEFLAG_HEAVYUNIT = BIT3;
const int SIEGEFLAG_UNIT_DAMAGED = BIT4;
struct siegest
{
	char siege;
	//Puzz:  Temporary siege thing for organizations
	int orgID;
	short siegetype;
	char underattack;
	int attacktime;
	short kills;
	short tanks;
	short escalationstate;
	char lights_off;
	char cameras_off;
	short timeuntillocated;
	short timeuntilcorps;
	short timeuntilcia;
	short timeuntilccs;
	short timeuntilfiremen;
	siegest() : siege(0), siegetype(-1), underattack(0), escalationstate(0), timeuntillocated(-1), timeuntilcorps(-1), timeuntilcia(-1), timeuntilccs(-1), timeuntilfiremen(-1) { }
};
struct coordinatest
{
	int locx;
	int locy;
	int locz;
};
struct siteblockst
{
	short special;
	int flag;
	char siegeflag;
};
struct sitechangest
{
	char x, y, z;
	int flag;
	sitechangest() { }
	sitechangest(char x_, char y_, char z_, int flag_) : x(x_), y(y_), z(z_), flag(flag_) { }
};
const int MAPX = 70;
const int MAPY = 23;
const int MAPZ = 10;
const int COMPOUND_BASIC = BIT1;
const int COMPOUND_CAMERAS = BIT2;
const int COMPOUND_TANKTRAPS = BIT3;
const int COMPOUND_TRAPS = BIT4;
const int COMPOUND_GENERATOR = BIT5;
const int COMPOUND_PRINTINGPRESS = BIT6;
const int COMPOUND_AAGUN = BIT7;
const int CITY_NAMELEN = 80;
const int LOCATION_NAMELEN = 40;
const int LOCATION_SHORTNAMELEN = 20;
class Location
{
public:
	char name[LOCATION_NAMELEN];
	char shortname[LOCATION_SHORTNAMELEN];
	char type;
	int city;
	int area; // two locations share an area if a squad located within one can reach the other without transportation
	int parent; // the index of parent in vector<Locations> locations
	//int id = 0; // NOT USED, kept for backwards compatibility
	vector<Item *> loot;
	vector<sitechangest> changes;
	int renting;
	char newrental;
	char needcar;
	int closed;
	bool hidden;
	bool mapped;
	bool upgradable;
	int highsecurity;
	siegest siege;
	int heat;
	int heat_protection;
	int compound_walls;
	int compound_stores;
	char front_business;
	char front_name[LOCATION_NAMELEN];
	char front_shortname[LOCATION_SHORTNAMELEN];
	bool haveflag;
	unsigned long mapseed[RNG_SIZE];
	Location(const char type_, const int parent_ = -1);
	Location() { }
	Location* addchild(const char type_);
	~Location() { delete_and_clear(loot); }
	void init();
	void update_heat_protection();
	bool duplicatelocation();
	bool can_be_upgraded() { return upgradable; }
	bool can_be_fortified();
	bool fortified();
	bool can_be_trapped();
	bool trapped() { return compound_walls & COMPOUND_TRAPS; }
	bool can_install_tanktraps();
	bool tank_traps();
	bool can_have_businessfront();
	bool has_business_front();
	bool bomb_resistant();
	bool part_of_justice_system();
	bool is_lcs_safehouse() { return renting >= 0; }
	bool is_ccs_safehouse() { return renting == RENTING_CCS; }
	bool is_city() { return type == city; }
	string getname(const signed char shortname_ = false, const bool include_city = false);
	void rename(const string name_, const string shortname_);
	string city_description();
	void getloot(vector<Item *>& loot);
};
/*******************************************************************************
*
*                        Location Data
*                        Folder: "locations"
*
*******************************************************************************/
/*
 world.cpp
*/
Location* find_site_in_city(const int site_type, const int city);
int find_site_index_in_city(const int site_type, const int city);
/* find local versions of these locations */
int find_site_index_in_same_city(const int site_type, const int site_index);
/*
inline int find_site_index_in_same_city(int site_type, const DeprecatedCreature& cr) { return find_site_index_in_same_city(site_type,cr.location); }
inline int find_police_station(int site_index) { return find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION,site_index); }
inline int find_police_station(const DeprecatedCreature& cr) { return find_police_station(cr.location); }
inline int find_clinic(int site_index) { return find_site_index_in_same_city(SITE_HOSPITAL_CLINIC,site_index); }
inline int find_clinic(const DeprecatedCreature& cr) { return find_clinic(cr.location); }
inline int find_homeless_shelter(int site_index) { return find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER,site_index); }
inline int find_homeless_shelter(const DeprecatedCreature& cr) { return find_homeless_shelter(cr.location); }
inline int find_courthouse(int site_index) { return find_site_index_in_same_city(SITE_GOVERNMENT_COURTHOUSE,site_index); }
inline int find_courthouse(const DeprecatedCreature& cr) { return find_courthouse(cr.location); }
inline int find_hospital(int site_index) { return find_site_index_in_same_city(SITE_HOSPITAL_UNIVERSITY,site_index); }
inline int find_hospital(const DeprecatedCreature& cr) { return find_hospital(cr.location); }
/* sets up the list of locations */
void make_world(const bool hasmaps);

