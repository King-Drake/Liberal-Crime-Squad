



#include "includes37.h"
#include "constStringglobals.h"
#include <algorithm>

///
/*
DEBUG DEFINES
*/
// inform player of ACTIVATED debug codes
bool DISPLAYDEBUG = false;
// Don't save the game
bool NOSAVE = false;
// Enemies don't attack
bool NOENEMYATTACK = false;
// Laws start archconservative
bool SHITLAWS = false;
// Laws start elite liberal
bool PERFECTLAWS = false;
// Public opinion starts at 100% Liberal
bool REVOLUTIONNOW = false;
// Gives you bloody armor
bool GIVEBLOODYARMOR = false;
// Start with lots of money
bool HIGHFUNDS = false;
// Interrogation always enlightens
bool AUTOENLIGHTEN = false;
// Show polls when you can't see things
bool SHOWWAIT = false;
// Show die rolls, 100% accurate poll numbers
bool SHOWMECHANICS = false;
// Make the year 2100
bool THEFUTURE = false;
// Make the founder blind
bool BLIND = false;
// Make the founder unable to walk
bool NOWALK = false;
// Make the founder have no face
bool NOFACE = false;
// Make the founder have a severely injured spine
bool SPINE = false;
// Make the founder have severe internal damage
bool INTERNAL = false;
// Make age not matter for dating or prostitution
bool ZEROMORAL = false;
// Re-seed the Random Number Generator every time it's called
bool MORERANDOM = false;
// Allow experimental, incomplete Stalinist Comrade Squad mode to be chosen for new games
bool ALLOWSTALIN = false;
// Store savefiles in plaintext, making it human readable and editable
bool VERBOSESAVEFILE = false;
// NOVERBOSECOMMENTS only affect anything if VERBOSESAVEFILE is active
// Remove almost all automatically generated comments from verbose savefiles
vector<WeaponType *> weapontype;
bool NOVERBOSECOMMENTS = false;
unsigned char bigletters[27][5][7][4];
unsigned char newstops[6][80][5][4];
unsigned char newspic[20][78][18][4];
MusicClass music;
char homedir[MAX_PATH_SIZE];
char artdir[MAX_PATH_SIZE];
bool multipleCityMode;
unsigned long seed[RNG_SIZE];
vector<ClipType *> cliptype;
vector<ArmorType *> armortype;
vector<CreatureType *> creaturetype;
vector<AugmentType *> augmenttype;

long curcreatureid = 0;
vector<string> default_slogans;
#include "customMaps.h"
vector<file_and_text_collection> globals_text_file_collection = {
	customText(&default_slogans, CONST_DEFAULT_SLOGANS_TXT),
};
vector<Vehicle *> vehicle;
void newVehicle(Vehicle *startcar) {
	vehicle.push_back(startcar);
}
char showcarprefs = 1;
siteblockst levelmap[MAPX][MAPY][MAPZ];
chaseseqst chaseseq;
string slogan_str = CONST_WE_NEED_A_SLOGAN;
char slogan[SLOGAN_LEN] = "We need a slogan!";
vector<Deprecatedsquadst *> squad;
Deprecatedsquadst *activesquad = NULL;
long cursquadid = 0;
char disbanding = 0;
int disbandtime = 0;
char cantseereason;
short activesortingchoice[SORTINGCHOICENUM];
DeprecatedCreature encounter[ENCMAX];
short mode = GAMEMODE_TITLE;
short offended_corps = 0;
short offended_cia = 0;
short offended_amradio = 0;
short offended_cablenews = 0;
short offended_firemen = 0;
int police_heat = 0;
unsigned long attorneyseed[RNG_SIZE];
int selectedsiege = -1;
char lcityname[CITY_NAMELEN];
char newscherrybusted = 0;
int month = 1;
int year = THEFUTURE ? 2100 : 2009;
int amendnum = 28;
bool termlimits = false;
bool deagle = false;
bool m249 = false;
UniqueCreatures uniqueCreatures;
short attitude[VIEWNUM];
short public_interest[VIEWNUM];
short background_liberal_influence[VIEWNUM];
short lawList[LAWNUM];
short house[HOUSENUM];
short senate[SENATENUM];
short court[COURTNUM];
char courtname[COURTNUM][POLITICIAN_NAMELEN];
short exec[EXECNUM];
short execterm = 1;

char execname[EXECNUM][POLITICIAN_NAMELEN];
short presparty = CONSERVATIVE_PARTY;
char oldPresidentName[POLITICIAN_NAMELEN];
int stat_recruits = 0;
int stat_kidnappings = 0;
int stat_dead = 0;
int stat_kills = 0;
int stat_buys = 0;
int stat_burns = 0;
int ustat_recruits = 0;
int ustat_kidnappings = 0;
int ustat_dead = 0;
int ustat_kills = 0;
int ustat_funds = 0;
int ustat_spent = 0;
int ustat_buys = 0;
int ustat_burns = 0;
coordinatest loc_coord;
short sitetype;
short sitealienate;
short sitealarmtimer;
short postalarmtimer;
short siteonfire;
int sitecrime;
int monthsPresidentMissing; //TODO news events and searches for them. // should be in the Unique creatures class but that's causing issues with politics.cpp


bool mapshowing = false;
bool encounterwarnings = false;
char foughtthisround = 0;
int day = 1;
short party_status = -1;
short wincondition = WINCONDITION_ELITE;
short fieldskillrate = FIELDSKILLRATE_FAST;
bool notermlimit;           //These determine if ELAs can take place --kviiri
bool nocourtpurge;
bool stalinmode;
char endgamestate = ENDGAME_NONE;
CCSexposure ccsexposure = CCSEXPOSURE_NONE;
char ccs_kills = 0;
int ccs_siege_kills = 0;
int ccs_boss_kills = 0;
vector<Deprecatedrecruitst *> recruit;
Deprecatednewsstoryst *sitestory = NULL;
int yourscore = -1;
/* Free memory and exit the game */ // This function closes the entire program, and can be called anywhere
void end_game(int err)
{
	end_cleartype_fix(); // won't do anything unless fixcleartype is true
	// title_screen::getInstance().delete_screen();
	LocationsPool::getInstance().delete_and_clear_pool();
	delete_and_clear(squad);
	delete_and_clear_weapon_type();
	delete_and_clear(cliptype);
	delete_and_clear(armortype);
	LootTypePool::getInstance().delete_and_clear_pool();
	delete_and_clear(creaturetype);
	delete_and_clear(augmenttype);
	delete_and_clear_vehicle_types();
	delete_and_clear(vehicle);
	CreaturePool::getInstance().delete_and_clear_pool();
	delete_and_clear_sitemaps();
	delete_and_clear(recruit);
	delete_and_clear_date_pool();
	delete_and_clear_groundloot();
	music.quit(); // shut down music
	endwinAlt();
	exit(err);
}
template<class Type>
bool populate_from_xml(vector<Type*>& types, const string& file, Log& log)
{
	CMarkup xml;
	if (!xml.Load(string(artdir) + file))
	{ // File is missing or not valid XML.
		addstrAlt(failedToLoad + file + CONST_EXCLAMATION_POINT, log);
		pressAnyKey();
		// Will cause abort here or else if file is missing all unrecognized types
		// loaded from a saved game will be deleted. Also, you probably don't want
		// to play with a whole category of things missing anyway. If the file
		// does not have valid xml, then behaviour is kind of undefined so it's
		// best to abort then too.
		return false;
	}
	xml.FindElem();
	xml.IntoElem();
	while (xml.FindElem()) types.push_back(new Type(xml.GetSubDoc()));
	return true;
}
string getVehicleShortname(int i) {
	return vehicle[i]->shortname();
}
string getVehicleFullname(int i) {
	return vehicle[i]->fullname();
}
int driveskill(DeprecatedCreature &cr, int v) {
	return driveskill(cr, *vehicle[v]);
}

/* transforms a squad id number into the index of that squad in the global vector */
int getsquad(int id)
{
	for (int i = 0; i < len(squad); i++) if (squad[i]->id == id) return i;
	return -1;
}
/* transforms a car id number into the index of that car in the global vector */
int id_getcar(int id)
{
	for (int i = 0; i < len(vehicle); i++) if (vehicle[i]->id() == id) return i;
	return -1;
}

/* transforms a clip type id into the index of that clip type in the global vector */
int getcliptype(int id)
{
	for (int i = 0; i < len(cliptype); i++) if (cliptype[i]->get_id() == id) return i;
	return -1;
}
/* transforms a clip type name into the index of that clip type in the global vector */
int getcliptype(const string &idname)
{
	for (int i = 0; i < len(cliptype); i++) if (cliptype[i]->get_idname() == idname) return i;
	return -1;
}

/* transforms a armor type id into the index of that armor type in the global vector */
int getarmortype(int id)
{
	for (int i = 0; i < len(armortype); i++) if (armortype[i]->get_id() == id) return i;
	return -1;
}
/* transforms a armor type name into the index of that armor type in the global vector */
int getarmortype(const string &idname)
{
	for (int i = 0; i < len(armortype); i++) if (armortype[i]->get_idname() == idname) return i;
	return -1;
}
/* transforms a CreatureTypes value into a pointer to that creature type */
const CreatureType* getcreaturetype(short crtype)
{
	for (int i = 0; i < len(creaturetype); i++) if (crtype == creaturetype[i]->get_type()) return creaturetype[i];
	return NULL;
}
/* transforms a creature type name into a pointer to that creature type  */
const CreatureType* getcreaturetype(const std::string& crtype)
{
	for (int i = 0; i < len(creaturetype); i++) if (crtype == creaturetype[i]->get_idname()) return creaturetype[i];
	return NULL;
}

/* common - moves all squad members and their cars to a new location */
void locatesquad(Deprecatedsquadst *st, long loc)
{
	for (int p = 0; p < 6; p++) if (st->squad[p] != NULL)
	{
		st->squad[p]->location = loc;
		if (st->squad[p]->carid != -1)
		{
			long v = id_getcar(st->squad[p]->carid);
			if (v != -1) vehicle[v]->set_location(loc);
		}
	}
}

int lenVehiclePool() {
	return len(vehicle);
}

int getCarID(const int l) {
	return vehicle[l]->id();
}

string getCarFullname(const int l) {
	return vehicle[l]->fullname(true);
}

void deleteLocationVehicles(int loc) {
	for (int v = len(vehicle) - 1; v >= 0; v--)
		if (vehicle[v]->get_location() == loc)
			delete_and_remove(vehicle, v);
}

void deleteVehicle(int carid) {
	delete_and_remove(vehicle, carid);
}

void deleteVehicles(vector<Vehicle *>& carid) {
	delete_and_clear(carid, vehicle);
}

void addCreatueVehiclesToCollection(DeprecatedCreature *cr[6], vector<Vehicle *> &veh) {
	for (int p = 0; p < 6; p++)
	{
		if (cr[p] == NULL) continue;
		if (cr[p]->carid != -1)
		{
			int v = id_getcar(cr[p]->carid);
			if (v != -1)
			{
				int v2;
				for (v2 = 0; v2 < len(veh); v2++) {
					if (veh[v2]->id() == vehicle[v]->id()) {
						break;
					}
				}
				if (v2 == len(veh)) veh.push_back(vehicle[v]);
			}
		}
	}
}

bool mainSeven(bool xml_loaded_ok) {
	xmllog.initialize(CONST_XMLLOG, true, 1);
	xml_loaded_ok &= populate_from_xml(vehicletype, CONST_VEHICLES_XML, xmllog);
	xml_loaded_ok &= populate_from_xml(cliptype, CONST_CLIPS_XML, xmllog);
	xml_loaded_ok &= populate_from_xml(weapontype, CONST_WEAPONS_XML, xmllog);
	xml_loaded_ok &= populate_from_xml(armortype, CONST_ARMORS_XML, xmllog);
	xml_loaded_ok &= populate_masks_from_xml(armortype, CONST_MASKS_XML, xmllog);
	xml_loaded_ok &= populate_from_xml(loottype, CONST_LOOT_XML, xmllog);
	xml_loaded_ok &= populate_from_xml(creaturetype, CONST_CREATURES_XML, xmllog);
	xml_loaded_ok &= populate_from_xml(augmenttype, CONST_AUGMENTATIONS_XML, xmllog);
	return xml_loaded_ok;
}

void newRecruit(DeprecatedCreature *newcr, int a) {

	Deprecatedrecruitst *newrst = new Deprecatedrecruitst(newcr, a);
	recruit.push_back(newrst);
}

Weapon* spawnNewWeapon(string newWeaponType) {
	Weapon *w = new Weapon(*weapontype[getweapontype(newWeaponType)]);
	if (w->uses_ammo())
	{
		if (LCSrandom(2) || //50% chance of being loaded...
							//except for the most exotic weapons, which are always loaded.
			w->get_itemtypename() == tag_WEAPON_DESERT_EAGLE ||
			w->get_itemtypename() == tag_WEAPON_FLAMETHROWER) //Make weapon property? -XML
		{
			vector<int> cti;
			for (int ct = 0; ct < len(cliptype); ct++)
				if (w->acceptable_ammo(*cliptype[ct]))
					cti.push_back(ct);
			Clip c(*cliptype[pickrandom(cti)]);
			w->reload(c);
		}
	}
	return w;
}

Armor* spawnNewArmor(string newArmorType) {

	int quality = 1;
	if (!LCSrandom(3))
		quality = 2;
	Armor *a = new Armor(getarmortype(newArmorType), quality);
	if (!LCSrandom(3))
		a->set_damaged(true);

	return a;
}
void selectAugmentType(vector<AugmentType *> &aug_type, char aug_c, int age) {
	for (int x = 0; x < augmenttype.size(); x++)
	{
		if (augmenttype[x]->get_type() == aug_c - 'a' &&
			(augmenttype[x]->get_max_age() == -1 || age <= augmenttype[x]->get_max_age()) &&
			(augmenttype[x]->get_min_age() == -1 || age >= augmenttype[x]->get_min_age()) &&
			augmenttype[x]->get_cost() <= ledger.get_funds())
			//TODO: Make it so that if you don't have money, it just grays it out, not just not show it
			aug_type.push_back(augmenttype[x]);
	}
}

void removeCreatureFromSquad(DeprecatedCreature &cr, int oldsqid) {
	activesquad = squad[getsquad(oldsqid)];
	for (int i = 0; i < 6; i++)
	{
		if (activesquad->squad[i]) if (activesquad->squad[i] == &cr)
		{
			for (int j = i + 1; j < 6; j++, i++) activesquad->squad[i] = activesquad->squad[j];
			activesquad->squad[5] = NULL;
			break;
		}
	}
}
void setEncounterZeroExistsFalse() {
	encounter[0].stop_existing();
}
vector<NameAndAlignment> getEncounterNameAndAlignment() {
	vector<NameAndAlignment> nameList;
	for (int e = 0; e < ENCMAX; e++) {
		nameList.push_back(encounter[e].getNameAndAlignment());
	}
	return nameList;
}
void make_creature_without_encounter_array(const int x, const short type) {
	makecreature(encounter[x], type);
}
// TODO convert this to Linked List?
/* kills the specified creature from the encounter, dropping loot */
void delenc(const short e, const char loot)
{
	//MAKE GROUND LOOT
	if ((mode == GAMEMODE_SITE) && loot) makeloot(encounter[e]);
	//BURY IT
	for (int en = e; en < ENCMAX; en++)
	{
		if (!encounter[en].getNameAndAlignment().exists) break;
		if (en < ENCMAX - 1) encounter[en] = encounter[en + 1];
	}
	encounter[ENCMAX - 1].stop_existing();
}
void delenc(DeprecatedCreature &tk) {
	delenc(&tk - encounter, 0);
}
void bloodyUpEncounterArmor() {

	for (int e = 0; e < ENCMAX; e++)
	{
		if (!encounter[e].getNameAndAlignment().exists) continue;
		if (!LCSrandom(2))
			encounter[e].get_armor().set_bloody(true);
	}
}
int encounterSize() {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int encsize = 0;
	for (int e = 0; e < ENCMAX; e++) if (encounter[e].exists) encsize++;
	return encsize;
}
int baddieCount() {
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	int baddiecount = 0;
	for (int e = 0; e < ENCMAX; e++) if (encounter[e].enemy && encounter[e].alive&&encounter[e].exists) baddiecount++;
	return baddiecount;
}
int baddieCount(const bool in_car) {
	int baddiecount = 0;

	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].carid != -1 &&
			encounter[e].enemy() &&
			encounter[e].getNameAndAlignment().alive&&
			encounter[e].getNameAndAlignment().exists)baddiecount++;
	}
	return baddiecount;
}
void damage_creature(const int e) {

	encounter[e].blood = LCSrandom(75) + 1;
}
void conservatise(const int e) {
	conservatise(encounter[e]);
}

int spawnPresident() {
	DeprecatedCreature* LibPres = NULL;
	int pres_align = IsPresidentLCS();
	if (pres_align == 1)
	{
		DeprecatedCreature LibPres = uniqueCreatures.President();
		LibPres.align = ALIGN_ELITELIBERAL;
		LibPres.gender_liberal = uniqueCreatures.President().gender_conservative;
		LibPres.setnevertalkordate(1);
		encounter[0] = LibPres;
		return 1;
	}
	else if (pres_align == 2)
	{
		return 2;
	}
	else
	{
		int e = 0;
		for (; e < 2; e++)make_creature_without_encounter_array(e, CREATURE_SECRET_SERVICE);
		encounter[e] = uniqueCreatures.President();
		return 1;
	}
	//fallback
	return 2;
}
void liberalizeEncounterIfThisType(const int type) {

	for (int i = 0; i < ENCMAX; i++)
		if (encounter[i].type == type)
			encounter[i].align = ALIGN_LIBERAL;
}
int squadAlive() {
	int partyalive = 0;
	for (int p = 0; p < 6; p++)
		if (activesquad->squad[p]) if (activesquad->squad[p]->getNameAndAlignment().alive == 1) partyalive++;
	return partyalive;
}
void addCrimeToSiteStory(const int crime) {

	sitestory->crime.push_back(crime);
}
void DeprecatedCreature::makeloot(vector<Item *> &loot)
{
	drop_weapons_and_clips(&loot);
	strip(&loot);
	if (money > 0 && mode == GAMEMODE_SITE)
	{
		loot.push_back(new Money(money));
		money = 0;
	}
}
void giveActiveSquadThisLoot(Item* de) {
	activesquad->loot.push_back(de);
}

void giveActiveSquadMoney(const int money) {

	giveActiveSquadThisLoot(new Money(money));
}
void giveActiveSquadLoot(const string loot) {

	giveActiveSquadThisLoot(getNewLoot(loot));
}
void claimSiteStory() {
	sitestory->claimed = 2;
}
void claimSiteStoryOne() {
	if (!sitestory->claimed)
		sitestory->claimed = 1;
}
void juiceActiveSquad(const long juice, const long cap) {

	for (int i = 0; i < 6; i++)
	{
		if (activesquad->squad[i])
			addjuice(*(activesquad->squad[i]), juice, cap);
	}
}
void juiceEntireCreaturePool(const long juice, const long cap) {
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) addjuice(*pool[p], juice, cap);
}
int getEscapeEngageLocation() {
	int loc = -1;
	if (selectedsiege != -1) loc = selectedsiege;
	if (activesquad != NULL) loc = activesquad->squad[0]->location;
	return loc;
}
void deleteAllSquadsInActiveAreaExceptActive(const int loc) {
	for (int sq = len(squad) - 1; sq >= 0; sq--)
		if (squad[sq] != activesquad && squad[sq]->squad[0])
			if (squad[sq]->squad[0]->location == loc)
			{
				if (activesquad)
				{
					for (int p = 0; p < 6; p++)
					{
						if (!squad[sq]->squad[p]) continue;
						squad[sq]->squad[p]->squadid = -1;
					}
					delete_and_remove(squad, sq);
				}
				else activesquad = squad[sq];
			}
}
void formANewSquadIfThereAreNone() {
	if (!activesquad)
	{
		squad.push_back(new Deprecatedsquadst);
		squad.back()->id = cursquadid++;
		strcpy(squad.back()->name, LocationsPool::getInstance().getLocationNameWithGetnameMethod(selectedsiege, true).c_str());
		strcat(squad.back()->name, CONST_X_DEFENSE.c_str());
		int i = 0;
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) if (pool[p]->location == selectedsiege && pool[p]->getNameAndAlignment().alive&&pool[p]->align == 1)
		{
			squad.back()->squad[i] = pool[p];
			pool[p]->squadid = squad.back()->id;
			if (++i >= 6) break;
		}
		activesquad = squad.back();
	}
}

short cur_site;

short getCurrentSite() {
	return cur_site;
}
void setCurrentSite(const short i) {
	sitetype = LocationsPool::getInstance().getLocationType(i);
	cur_site = i;
}

void resetSiteGlobals() {
	sitealarmtimer = -1;
	postalarmtimer = 0;
	siteonfire = 0;
	sitealienate = 0;
	sitecrime = 0;

}

void resetCCSSiegeGlobals() {

	ccs_siege_kills = 0;
	ccs_boss_kills = 0;
}
void countHeroes(int &partysize, int &partyalive) {
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) if (pool[p]->align == 1 && pool[p]->location == getCurrentSite() && !(pool[p]->flag&CREATUREFLAG_SLEEPER))
	{
		partysize++;
		if (pool[p]->getNameAndAlignment().alive) partyalive++;
	}
}
void cancelOutBleeding() {
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) for (int w = 0; w < BODYPARTNUM; w++) pool[p]->wound[w] &= ~WOUND_BLEEDING;
}
int print_character_info(const int c, const int party_status) {
	if (c >= '1'&&c <= '6') if (activesquad->squad[c - '1'] != NULL)
	{
		if (party_status == c - '1')fullstatus(party_status);
		else return c - '1';
	}
	return party_status;
}
void baseEveryoneLeftAtHomelessShelter(const int homes) {
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location != getCurrentSite()) continue;
		if (!pool[p]->getNameAndAlignment().alive)
		{
			delete_and_remove(pool, p);
			continue;
		}
		//BASE EVERYONE LEFT AT HOMELESS SHELTER
		removesquadinfo(*pool[p]);
		pool[p]->hiding = LCSrandom(3) + 2;
		if (pool[p]->align == 1) // not a hostage
			pool[p]->location = -1;
		else // hostages don't go into hiding, just shove em into the homeless shelter
			pool[p]->location = homes;
		pool[p]->base = homes;
	}
}
int printBestLCSMemberForNews(const string repname, const int l) {
	int best = 0;
	for (int p = 0, bestvalue = -1000; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive || pool[p]->align != 1 || pool[p]->location != l) continue;
		int sum = pool[p]->get_attribute(ATTRIBUTE_INTELLIGENCE, true)
			+ pool[p]->get_attribute(ATTRIBUTE_HEART, true)
			+ pool[p]->get_skill(SKILL_PERSUASION)
			+ pool[p]->juice;
		if (sum > bestvalue) best = p, bestvalue = sum;
	}
	mvaddstrAlt(4, 1, pool[best]->getNameAndAlignment().name, gamelog);

	addstrAlt(CONST_DECIDES_TO_GIVE_AN_INTERVIEW, gamelog);
	gamelog.newline();
	pressAnyKey();
	mvaddstrAlt(6, 1, CONST_THE_INTERVIEW_IS_WIDE_RANGING_COVERING_A_VARIETY_OF_TOPICS, gamelog);
	gamelog.newline();
	pressAnyKey();
	int segmentpower = pool[best]->attribute_roll(ATTRIBUTE_INTELLIGENCE)
		+ pool[best]->attribute_roll(ATTRIBUTE_HEART)
		+ pool[best]->skill_roll(SKILL_PERSUASION)
		+ pool[best]->skill_roll(SKILL_PERSUASION)
		+ pool[best]->skill_roll(SKILL_PERSUASION);

	printReporterDuringSiege(repname, pool[best]->getNameAndAlignment().name, segmentpower);
	return segmentpower;
}
void set_site_story_as_last_news_story() {
	sitestory = lastNewsStory();

}
void setSiteStoryClaimedZero() {
	sitestory->claimed = 0;
}
bool isActiveSquadAnonymous() {
	return activesquad->stance == SQUADSTANCE_ANONYMOUS;
}
char shouldWeBailOnBase() {
	char bail_on_base = 1;
	if (getCurrentSite() == activesquad->squad[0]->base)bail_on_base = 0;
	return bail_on_base;
}
void set_sitestory_type() {
	void resolvesite();
	if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		if (LocationsPool::getInstance().isThisUnderAttack(getCurrentSite()))sitestory->type = NEWSSTORY_SQUAD_KILLED_SIEGEATTACK;
		else { sitestory->type = NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE; }
	}
	else
		if (!LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
		{
			sitestory->type = NEWSSTORY_SQUAD_KILLED_SITE;
			resolvesite();
		}
}
int activesquadSize() {
	return activesquad->squadsize();
}
int activesquadAlive() {
	return activesquad->squadalive();
}
void assembleActiveSquad() {
	assemblesquad(activesquad);
}
void locateActiveSquad(const int loc) {

	locatesquad(activesquad, loc);
}
int countactivesquadhostages() {
	int hostages = 0;

	for (int p = 0; p < 6; p++)
		if (activesquad->squad[p] != NULL)
			if (activesquad->squad[p]->is_holding_body() &&activesquad->squad[p]->get_prisoner_align() != ALIGN_LIBERAL)
				hostages++;
	return hostages;
}
int getactivesquadBase() {
	int cbase = -1;
	if (activesquad->squad[0] != NULL)
	{
		cbase = activesquad->squad[0]->base;
	}
	return cbase;
}
int getactivesquadCarID(const int p) {
	if (activesquad->squad[p]) {
		return activesquad->squad[p]->carid;
	}
	else {
		return -1;
	}
}
void killActiveSquad() {
	for (int p = 0; p < 6; p++)
	{
		if (!activesquad->squad[p]) continue;
		activesquad->squad[p]->die();
		activesquad->squad[p]->location = -1;
		activesquad->squad[p] = NULL;
	}
}
void conservatiseEncslot(const int encslot) {
	conservatise(encounter[encslot]);
}

vector<int> potentialEncounterNoticers() {
	vector<int> noticer;
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].type == CREATURE_PRISONER)continue;
		if (encounter[e].getNameAndAlignment().exists&&encounter[e].getNameAndAlignment().alive&&
			encounter[e].enemy())
		{
			noticer.push_back(e);
		}
	}
	return noticer;
}
int get_stealth_difficulty(const int n) {
	return encounter[n].get_stealth_difficulty();
}
int get_disguise_difficulty(const int n) {
	return encounter[n].get_disguise_difficulty();
}

int get_encounter_time(const int n) {
	int time;
	time = 20 + LCSrandom(10) - encounter[n].get_attribute(ATTRIBUTE_INTELLIGENCE, true)
		- encounter[n].get_attribute(ATTRIBUTE_WISDOM, true);
	return time;
}


void clearCarStates() {
	for (int p = 0; p < len(pool); p++) pool[p]->carid = -1;
}

void removeItemFromSquad(const int loottypeindex) {
	for (int sq = 0; sq < len(squad); sq++)
	{
		for (int l = 0; l < len(squad[sq]->loot); l++)
		{
			if (!(squad[sq]->loot[l]->whatIsThis() == THIS_IS_LOOT)) continue;
			if (getloottype(squad[sq]->loot[l]->get_itemtypename()) == loottypeindex)
			{
				squad[sq]->loot[l]->decrease_number(1);
				if (squad[sq]->loot[l]->empty())
					delete_and_remove(squad[sq]->loot, l);
				return;// loottypeindex;
			}
		}
	}
}

void constructLootIndices(vector<bool> &havetype, vector<int> &loottypeindex, const vector<string> dox) {
	for (int sq = 0; sq < len(squad); sq++)
	{
		consolidateloot(squad[sq]->loot);
		for (int l = 0; l < len(squad[sq]->loot); l++)
		{
			if (!(squad[sq]->loot[l]->whatIsThis() == THIS_IS_LOOT)) continue;
			if (!binary_search(dox.begin(), dox.end(), squad[sq]->loot[l]->get_itemtypename())) continue;
			if (!havetype[getloottype(squad[sq]->loot[l]->get_itemtypename())])
			{
				loottypeindex.push_back(getloottype(squad[sq]->loot[l]->get_itemtypename()));
				havetype[getloottype(squad[sq]->loot[l]->get_itemtypename())] = true;
			}
		}
	}
}

void printActiveSquadTalkOptions() {
	int y = 11;

	for (int p = 0; p < 6; p++)
	{

		if (activesquad->squad[p] != NULL)
		{
			if (activesquad->squad[p]->getNameAndAlignment().alive)
			{
				mvaddcharAlt(y, 1, p + '1');
				addstrAlt(spaceDashSpace);
				addstrAlt(activesquad->squad[p]->getNameAndAlignment().name);
				mvaddstrAlt(y, 50, activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA, true) / 2 +
					activesquad->squad[p]->get_skill(SKILL_PERSUASION));
				mvaddstrAlt(y, 60, activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA, true) / 2 +
					activesquad->squad[p]->get_skill(SKILL_SEDUCTION));
				mvaddstrAlt(y++, 70, activesquad->squad[p]->get_attribute(ATTRIBUTE_CHARISMA, true) / 2 +
					activesquad->squad[p]->get_skill(SKILL_DISGUISE));
			}
		}
	}
}
bool activeSquadMemberIsAliveAndExists(const int sp) {
	return activesquad->squad[sp] != NULL && activesquad->squad[sp]->getNameAndAlignment().alive;
}
void criminalizeEncounterPrisonerEscape(const int e) {
	criminalize(encounter[e], LAWFLAG_ESCAPED);

}
void duplicateEncounterMember(const int e) {
	encounter[e] = encounter[e + 1];
}
void unpersonLastEncounterMember() {
	encounter[ENCMAX - 1].stop_existing();
}
int checkForPeopleWhoCanRecruit() {
	// Check for people who can recruit followers
	for (int i = 0; i < 6; i++)
		if (activesquad->squad[i] != NULL)
			if (subordinatesleft(*activesquad->squad[i]))
				return i;
	return -1;
}
void addNewRecruit(int i, int e) {
	DeprecatedCreature* newcr = new DeprecatedCreature;
	*newcr = encounter[e];
	newcr->namecreature();
	newcr->location = activesquad->squad[i]->location;
	newcr->base = activesquad->squad[i]->base;
	newcr->hireid = activesquad->squad[i]->id;
	addCreature(newcr);
	stat_recruits++;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL)
		{
			activesquad->squad[p] = newcr;
			newcr->squadid = activesquad->id;
			break;
		}
	}
}
bool get_encounter_cantbluff_is_zero(const int e) {
	return encounter[e].is_cantbluff_zero();

}
bool get_encounter_cantbluff_is_two(const int e) {
	return encounter[e].is_cantbluff_two();

}
bool get_encounter_cantbluff_is_one(const int e) {
	return !(encounter[e].is_cantbluff_two() || encounter[e].is_cantbluff_zero());
}
void spawnCreatureCEO() {

	encounter[0] = uniqueCreatures.CEO();
	encounter[0].make_existing();
}
int getEncounterAnimalGloss(const int e) {
	return encounter[e].animalgloss;
}
CantBluffAnimal encounterGetCantBluffAnimal(const int t) {
	return encounter[t].getCantBluffAnimal();
}
CreatureBio encounterGetCreatureBio(const int t) {
	return encounter[t].getCreatureBio();
}

int getDifficultyBasedOnEncounterWisdom(const int e) {
	return encounter[e].get_attribute(ATTRIBUTE_WISDOM, true) > 10 ? DIFFICULTY_CHALLENGING : DIFFICULTY_AVERAGE;
}

int encounterWisdomRoll(const int e) {
	return encounter[e].attribute_roll(ATTRIBUTE_WISDOM);
}

int getEncounterCarID(const int e) {
	return encounter[e].carid;
}
int getEncounterIsDriver(const int e) {
	return encounter[e].is_driver;
}
int getEncounterWorkLocation(const int e) {
	return encounter[e].worklocation;
}
void sleeperSuccessfullyRecruits(const string name, const int id, const float infiltration, const int e) {

	DeprecatedCreature* recruit = new DeprecatedCreature(encounter[e]);
	liberalize(*recruit, 0);
	recruit->namecreature();
	recruit->hireid = id;
	if (recruit->infiltration > infiltration)
	{
		recruit->infiltration = infiltration;
	}
	recruit->flag |= CREATUREFLAG_SLEEPER;
	LocationsPool::getInstance().setLocationMappedAndUnhidden(recruit->worklocation);
	addCreature(recruit);
	eraseAlt();
	mvaddstrAlt(6, 1, string_sleeper, gamelog);
	addstrAlt(name, gamelog);
	addstrAlt(hasRecruited, gamelog);
	addstrAlt(recruit->get_type_name(), gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.newline();
	mvaddstrAlt(8, 1, recruit->getNameAndAlignment().name, gamelog);
	addstrAlt(looksForwardToServing, gamelog);
	gamelog.nextMessage();
}


void incrementStatRecruits() {
	stat_recruits++;
}

void putBackSpecials(const int olocx, const int olocy, const int olocz) {
	//PUT BACK SPECIALS
	for (int e = 0; e < ENCMAX; e++)
		if (encounter[e].getNameAndAlignment().exists)
		{
			if (encounter[e].is_cantbluff_zero()&&encounter[e].type == CREATURE_LANDLORD)
				levelmap[olocx][olocy][olocz].special = SPECIAL_APARTMENT_LANDLORD;
			if (encounter[e].is_cantbluff_zero()&&encounter[e].type == CREATURE_BANK_TELLER)
				levelmap[olocx][olocy][olocz].special = SPECIAL_BANK_TELLER;
			encounter[e].stop_existing();
		}
}

void emptyEncounter() {
	for (int e = 0; e < ENCMAX; e++)encounter[e].stop_existing();
}
void advancecreature(DeprecatedCreature &cr);
void advancecreature(const int e) {
	advancecreature(encounter[e]);
}

vector<string> male_first_names;
vector<string> female_first_names;
vector<string> gender_neutral_first_names;
vector<string> great_white_male_patriarch_first_names;
vector<string> regular_last_names;
vector<string> archconservative_last_names;
vector<file_and_text_collection> names_text_file_collection = {
	/*creaturenames.cpp*/
	customText(&male_first_names, names + MALE_FIRST_NAMES_TXT),
	customText(&female_first_names, names + FEMALE_FIRST_NAMES_TXT),
	customText(&gender_neutral_first_names, names + GENDER_NEUTRAL_FIRST_NAMES_TXT),
	customText(&great_white_male_patriarch_first_names, names + GWMP_FIRST_NAMES_TXT),
	customText(&regular_last_names, names + REGULAR_LAST_NAMES_TXT),
	customText(&archconservative_last_names, names + ARCHCONSERVATIVE_LAST_NAMES_TXT),
};


vector<NameAndAlignment> PNameAndAlignment() {
	vector<NameAndAlignment> out;
	for (DeprecatedCreature p : encounter) {
		if (p.getNameAndAlignment().exists) {
			out.push_back(p.getNameAndAlignment());
		}
	}
	return out;
}
vector<CreatureJustice> PCreatureJustice() {
	vector<CreatureJustice> out;
	for (DeprecatedCreature p : encounter) {
		if (p.getNameAndAlignment().exists) {
			out.push_back(p.getCreatureJustice());
		}
	}
	return out;

}
vector<std::string> PAllClothes() {
	vector<string> out;
	for (DeprecatedCreature p : encounter) {
		if (p.getNameAndAlignment().exists) {
			out.push_back(p.get_armor_string(true));
		}
	}
	return out;
}
vector<std::string> SquadAllClothes() {
	vector<string> out;
	for (int i = 0; i < activesquad->squadsize(); i++) {
			out.push_back(activesquad->squad[i]->get_armor_string(true));
		
	}
	return out;
}
vector<CreatureBio> PCreatureBio() {
	vector<CreatureBio> out;
	for (DeprecatedCreature p : encounter) {
		if (p.getNameAndAlignment().exists) {
			out.push_back(p.getCreatureBio());
		}
	}
	return out;

}
vector<int> PCreatureCharisma() {
	vector<int> out;
	for (DeprecatedCreature p : encounter) {
		if (p.getNameAndAlignment().exists) {
			int cha;
			CreatureAttributeList c = p.getCreatureAttributeList();
			cha = c.get_attribute(ATTRIBUTE_CHARISMA);
			out.push_back(cha);
		}
	}
	return out;
}

bool nullActive() {
	if (activesquad != NULL) {
		return activesquad->squadsize() <= 0;
	}
	else {
		return true;
	}
}

// return integer between 0 and 4
int getAverageLawLevel() {
	int average = 0;
	for (short i : lawList) {
		average += i + 2;
	}
	if (average % LAWNUM > LAWNUM / 2) {
		// hotfix to treat integer division as though it is real division
		average += average % LAWNUM;
	}
	average /= LAWNUM;
	return average;
}
vector<NameAndAlignment> ActiveSquadPNameAndAlignment() {
	vector<NameAndAlignment> out;
	for (int i = 0; i < activesquad->squadsize(); i++) {
		out.push_back(activesquad->squad[i]->getNameAndAlignment());
	}
	return out;
}
vector<CreatureJustice> ActiveSquadPCreatureJustice() {
	vector<CreatureJustice> out;
	for (int i = 0; i < activesquad->squadsize(); i++) {
		out.push_back(activesquad->squad[i]->getCreatureJustice());
	}
	return out;

}
vector<CreatureBio> ActiveSquadPCreatureBio() {
	vector<CreatureBio> out;
	for (int i = 0; i < activesquad->squadsize(); i++) {
		out.push_back(activesquad->squad[i]->getCreatureBio());
	}
	return out;

}
vector<int> ActiveSquadPCreatureCharisma() {
	vector<int> out;
	for (int i = 0; i < activesquad->squadsize(); i++) {
		int cha;
		CreatureAttributeList c = activesquad->squad[i]->getCreatureAttributeList();
		cha = c.get_attribute(ATTRIBUTE_CHARISMA);
		out.push_back(cha);
	}
	return out;
}

vector<int> ActiveSquadID() {
	vector<int> out;
	for (int i = 0; i < activesquad->squadsize(); i++) {
		int cha  = activesquad->squad[i]->id;
		out.push_back(cha);
	}
	return out;

}
vector<int> PCreatureID() {
	vector<int> out;
	for (DeprecatedCreature p : encounter) {
		if (p.getNameAndAlignment().exists) {
			int cha = p.id;
			out.push_back(cha);
		}
	}
	return out;

}