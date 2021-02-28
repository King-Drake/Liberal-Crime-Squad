

#include "../includes24.h"
#include "../constStringOEMlocationsPool.h"

map <string, int> cityLocationTags = {
map<string, int>::value_type(tag_Downtown, ENUM_tag_Downtown),
map<string, int>::value_type(tag_University_District, ENUM_tag_University_District),
map<string, int>::value_type(tag_u_District, ENUM_tag_u_District),
map<string, int>::value_type(tag_Industrial_District, ENUM_tag_Industrial_District),
map<string, int>::value_type(tag_i_District, ENUM_tag_i_District),
map<string, int>::value_type(tag_Shopping, ENUM_tag_Shopping),
map<string, int>::value_type(tag_Outskirts, ENUM_tag_Outskirts),
map<string, int>::value_type(tag_Seaport_Area, ENUM_tag_Seaport_Area),
map<string, int>::value_type(tag_Seaport, ENUM_tag_Seaport),
map<string, int>::value_type(tag_Outskirts_amp_Orange_County, ENUM_tag_Outskirts_amp_Orange_County),
map<string, int>::value_type(tag_City_Outskirts, ENUM_tag_City_Outskirts),
map<string, int>::value_type(tag_Arlington, ENUM_tag_Arlington),
map<string, int>::value_type(tag_Hollywood, ENUM_tag_Hollywood),
map<string, int>::value_type(tag_Greater_Hollywood, ENUM_tag_Greater_Hollywood),
map<string, int>::value_type(tag_Manhattan, ENUM_tag_Manhattan),
map<string, int>::value_type(tag_Manhattan_Island, ENUM_tag_Manhattan_Island),
map<string, int>::value_type(tag_Brooklyn_ampersand_Queens, ENUM_tag_Brooklyn_ampersand_Queens),
map<string, int>::value_type(tag_Long_Island, ENUM_tag_Long_Island),
map<string, int>::value_type(tag_The_Bronx, ENUM_tag_The_Bronx)
};

#include <algorithm>

/* rolls up a creature's stats and equipment */
void makecreature(DeprecatedCreature &cr, short type);
vector<Location *> location;
void initiateNewgameLocations(DeprecatedCreature* newcr, const newGameArguments ngm) {
	Deprecatedsquadst *newsq = new Deprecatedsquadst;
	newsq->id = 0; cursquadid++;
	newsq->squad[0] = newcr;
	newcr->squadid = 0;
	strcpy(newsq->name, theLCS);
	// This is not a proper for loop, it only iterates to find a single instance of a valid location
	// then executes its code once, and then break;
	for (int l = 0; l < len(location); l++)
	{
		if (location[l]->type == ngm.base)
		{
			newcr->base = l;
			newcr->location = l;
			if (ngm.sports_car) {

				Vehicle * startcar = newSportsCar();
				startcar->add_heat(10);
				newVehicle(startcar);
				newcr->pref_carid = startcar->id();
				
				startcar->set_location(l);
				
			}
			switch (ngm.base)
			{
			case SITE_RESIDENTIAL_APARTMENT_UPSCALE:location[l]->renting = 500; break;
			case SITE_RESIDENTIAL_APARTMENT:location[l]->renting = 200; break;
			case SITE_RESIDENTIAL_TENEMENT:location[l]->renting = 100; break;
			case SITE_BUSINESS_CRACKHOUSE:
				location[l]->renting = RENTING_PERMANENT;
				location[l]->compound_stores += 100;
				break;
			}
			location[l]->newrental = 1;
			switch (ngm.recruits)
			{
			case RECRUITS_GANG:
				for (int i = 0; i < 4; i++)
				{
					DeprecatedCreature* recruit = new DeprecatedCreature;
					makecreature(*recruit, CREATURE_GANGMEMBER);
					if (recruit->get_weapon().get_itemtypename() == tag_WEAPON_AUTORIFLE_AK47 ||
						recruit->get_weapon().get_itemtypename() == tag_WEAPON_SMG_MP5 ||
						!recruit->is_armed())
					{
						Weapon w(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_9MM)]);
						recruit->give_weapon(w, NULL);
						Clip c(*cliptype[getcliptype(tag_CLIP_9)], 4);
						recruit->take_clips(c, 4);
						recruit->reload(false);
					}
					recruit->align = ALIGN_LIBERAL;
					recruit->set_attribute(ATTRIBUTE_HEART,
						recruit->get_attribute(ATTRIBUTE_HEART, false) +
						recruit->get_attribute(ATTRIBUTE_WISDOM, false) / 2);
					recruit->set_attribute(ATTRIBUTE_WISDOM,
						recruit->get_attribute(ATTRIBUTE_WISDOM, false) / 2);
					recruit->namecreature();
					recruit->rename(recruit->propername);
					recruit->location = l;
					recruit->base = l;
					recruit->hireid = newcr->id;
					newsq->squad[i + 1] = recruit;
					recruit->squadid = newsq->id;
					addCreature(recruit);
				}
				break;
			}
			if (GIVEBLOODYARMOR) {
				Armor *newa = new Armor(getarmortype(tag_ARMOR_CLOTHES));
				newa->set_bloody(true);
				location[l]->loot.push_back(newa);
			}
			if (HIGHFUNDS) {
				ledger.force_funds(100000);
			}
			break;
		}
	}
	//newcr->juice=0;
	squad.push_back(newsq);
	activesquad = newsq;
	if (ngm.makelawyer)
	{
		DeprecatedCreature* lawyer = new DeprecatedCreature;
		makecreature(*lawyer, CREATURE_LAWYER);
		// Make sure lawyer is of the appropriate gender for dating the main character;
		// opposite sex by default, same sex if the option was chosen that mentions
		// homosexuality
		if (ngm.gaylawyer)
		{
			lawyer->gender_conservative = lawyer->gender_liberal = newcr->gender_conservative;
			// neutral founder gets neutral partner
		}
		else
		{
			if (newcr->gender_conservative == GENDER_MALE)
				lawyer->gender_liberal = lawyer->gender_conservative = GENDER_FEMALE;
			if (newcr->gender_conservative == GENDER_FEMALE)
				lawyer->gender_liberal = lawyer->gender_conservative = GENDER_MALE;
			// neutral founder gets random partner
		}
		// Ensure the lawyer has good heart/wisdom stats
		if (lawyer->get_attribute(ATTRIBUTE_HEART, false) < newcr->get_attribute(ATTRIBUTE_HEART, false) - 2)
			lawyer->adjust_attribute(ATTRIBUTE_HEART, -2);
		lawyer->set_attribute(ATTRIBUTE_WISDOM, 1);
		lawyer->namecreature();
		lawyer->flag |= CREATUREFLAG_SLEEPER;
		lawyer->flag |= CREATUREFLAG_LOVESLAVE;
		lawyer->align = ALIGN_LIBERAL;
		lawyer->infiltration = 0.3f;
		lawyer->set_age(28);
		location[lawyer->worklocation]->mapped = 1;
		lawyer->hireid = newcr->id;
		addCreature(lawyer);
		lawyer->location = lawyer->base = lawyer->worklocation;
	}
}
bool LocationsPool::locationPoolInitiated = false;
LocationsPool lPool;
LocationsPool LocationsPool::getInstance()
{
	if (!locationPoolInitiated) {
		lPool = LocationsPool();
		locationPoolInitiated = true;
	}
	return lPool;
}
const int LocationsPool::lenpool() const
{
	return len(location);
}
const int LocationsPool::getLocationCity(int cursite)const {
	return location[cursite]->city;
}
void LocationsPool::hideCCSSafehouses()
{
	// hide ccs safehouses
	for (int l = 0; l < lenpool(); l++)
	{
		if (getRentingType(l) == RENTING_CCS)
		{
			location[l]->renting = RENTING_NOCONTROL;
			location[l]->hidden = true;
		}
	}
}
void LocationsPool::addHeat(int cursite, int heat)
{
	location[cursite]->heat += heat;
}
const void LocationsPool::findAllLootTypes(vector<bool>& havetype, vector<int>& loottypeindex, const vector<string>& dox)const
{
	//FIND ALL LOOT TYPES
	for (int loc = 0; loc < LocationsPool::getInstance().lenpool(); loc++)
	{
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,loc) == RENTING_NOCONTROL) continue;
		consolidateloot(location[loc]->loot);
		for (int l = 0; l < len(location[loc]->loot); l++)
		{
			if (!(location[loc]->loot[l]->whatIsThis() == THIS_IS_LOOT)) continue;
			if (!binary_search(dox.begin(), dox.end(), location[loc]->loot[l]->get_itemtypename())) continue;
			if (!havetype[getloottype(location[loc]->loot[l]->get_itemtypename())])
			{
				loottypeindex.push_back(getloottype(location[loc]->loot[l]->get_itemtypename()));
				havetype[getloottype(location[loc]->loot[l]->get_itemtypename())] = true;
			}
		}
	}
}
const bool LocationsPool::isLocationMapped(int cursite)const
{
	return location[cursite]->mapped;
}
const bool LocationsPool::isLocationHidden(int cursite)const
{
	return location[cursite]->hidden;
}
void LocationsPool::setLocationMappedAndUnhidden(int cursite)
{
	location[cursite]->mapped = 1;
	location[cursite]->hidden = 0;
}
const string LocationsPool::getLocationNameWithGetnameMethod(int cursite, signed char a)const {
	return getLocationNameWithGetnameMethod(cursite, a, false);
}

const string CONST_AWAY = "Away";
const string LocationsPool::getLocationNameWithGetnameMethod(int cursite, signed char a, bool b)const
{
	if (cursite == -1) {
		return CONST_AWAY;
	}
	return location[cursite]->getname(a, b);
}
const int LocationsPool::getCompoundWalls(int cursite)const
{
	return location[cursite]->compound_walls;
}
// Redundant, carelessly, worry later TODO
void LocationsPool::setTimeUntilSiege(int cursite, int time)
{
	LocationsPool::getInstance().setSiegetimeuntillocated(cursite, time);
}
const bool LocationsPool::isNewRental(int cursite)const
{
	return location[cursite]->newrental;
}
void LocationsPool::evictLCSFrom(int l)
{

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 1, CONST_EVICTION_NOTICE);
	addstrAlt(LocationsPool::getInstance().getLocationName(l));
	addstrAlt(CONST_POSSESSIONS_GO_TO_THE_SHELTER);
	pressAnyKey();
	location[l]->renting = RENTING_NOCONTROL;
	CreaturePool::getInstance().moveAllSquadMembers(l);
	int hs = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, l);
	location[hs]->getloot(location[l]->loot);
	location[l]->compound_walls = 0;
	location[l]->compound_stores = 0;
	location[l]->front_business = -1;
}
const int LocationsPool::isThisSiteClosed(int cursite)const
{
	return location[cursite]->closed;
}
const char LocationsPool::doesThisPlaceNeedACar(int cursite)const
{
	return location[cursite]->needcar;
}
const int LocationsPool::findTravelLocation()const
{
	int travelLocation = -1;
	for (int i = 0; i < len(location); i++) {
		if (location[i]->type == SITE_TRAVEL)
		{
			travelLocation = i;
			break;
		}
	}
	return travelLocation;
}
const int LocationsPool::getLocationParent(int cursite)const
{
	return location[cursite]->parent;
}
int LocationsPool::deleteSpecialItem(int slot, vector<int> loottypeindex)
{
	//DELETE THE ITEM
	for (int loc = 0; loc < LocationsPool::getInstance().lenpool(); loc++)
	{
		if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,loc) == RENTING_NOCONTROL) continue;
		for (int l = 0; l < len(location[loc]->loot); l++)
		{
			if (!(location[loc]->loot[l]->whatIsThis() == THIS_IS_LOOT)) continue;
			if (getloottype(location[loc]->loot[l]->get_itemtypename()) == loottypeindex[slot])
			{
				location[loc]->loot[l]->decrease_number(1);
				if (location[loc]->loot[l]->empty())
					delete_and_remove(location[loc]->loot, l);
				return loottypeindex[slot];
			}
		}
	}
	return -1;
}
void LocationsPool::getAssetValues(long & weaponValue, long & armorValue, long & clipValue, long & lootValue)const
{
	for (int j = 0; j < LocationsPool::getInstance().lenpool(); j++)
		for (int i = 0; i < len(location[j]->loot); i++)
		{
			Item* item = location[j]->loot[i];
			if (item->whatIsThis() == THIS_IS_WEAPON) weaponValue += item->get_fencevalue()*item->get_number();
			if (item->whatIsThis() == THIS_IS_ARMOR) armorValue += item->get_fencevalue()*item->get_number();
			if (item->whatIsThis() == THIS_IS_CLIP) clipValue += item->get_fencevalue()*item->get_number();
			if (item->whatIsThis() == THIS_IS_LOOT) lootValue += item->get_fencevalue()*item->get_number();
		}
}
const bool LocationsPool::canBeFortified(int cursite)const
{
	return location[cursite]->can_be_fortified();
}
/* daily - seeds and names a site (will re-seed and rename if used after start) */
void LocationsPool::initLocation(int cursite)
{
	initlocation(*location[cursite]);
}
void LocationsPool::stashThisLootHere(const string& tag, int homes) {
	location[homes]->loot.push_back(getNewLoot(tag));
}
void LocationsPool::stashThisWeaponHere(int itemindex, int shelter) {
	location[shelter]->loot.push_back(new Weapon(*weapontype[itemindex]));
}
void LocationsPool::stashThisArmorHere(int itemindex, int shelter) {
	location[shelter]->loot.push_back(new Armor(itemindex));
}
void LocationsPool::equipLoc(int loc, int y)
{
	equip(location[loc]->loot, y);
}
void LocationsPool::delete_and_clear_pool()
{
	delete_and_clear(location);
}
const char LocationsPool::isThereASiegeHere(int cursite)const
{
	return location[cursite]->siege.siege;
}
const int LocationsPool::isThisPlaceHighSecurity(int cursite)const
{
	return location[cursite]->highsecurity;
}
void LocationsPool::isThereASiegeHere(int cursite, char newCondition)const
{
	location[cursite]->siege.siege = newCondition;
}
void LocationsPool::isThisPlaceHighSecurity(int cursite, int newCondition)const
{
	location[cursite]->highsecurity = newCondition;
}
const char LocationsPool::getLocationType(int cursite)const
{
	return location[cursite]->type;
}
const short LocationsPool::getSiegeType(int cursite)const
{
	return location[cursite]->siege.siegetype;
}
const short LocationsPool::getSiegeEscalationState(int cursite)const
{
	return location[cursite]->siege.escalationstate;
}
const int LocationsPool::getRentingType(int cursite)const
{
	return location[cursite]->renting;
}
void LocationsPool::initSite(int loc)
{
	initsite(*location[loc]);
}
// TODO Understand this
void LocationsPool::eraseAndReplaceGraffiti(int cursite, int locx, int locy, int locz)
{
	// Erase any previous semi-permanent graffiti here
	for (int i = 0; i < len(location[cursite]->changes); i++)
	{
		if ((location[cursite]->changes[i].x == locx) &&
			(location[cursite]->changes[i].y == locy) &&
			(location[cursite]->changes[i].z == locz) &&
			((location[cursite]->changes[i].flag == SITEBLOCK_GRAFFITI) ||
			(location[cursite]->changes[i].flag == SITEBLOCK_GRAFFITI_CCS) ||
				(location[cursite]->changes[i].flag == SITEBLOCK_GRAFFITI_OTHER)))
		{
			location[cursite]->changes.erase(location[cursite]->changes.begin() + i);
			break;
		}
	}
	// Add new semi-permanent graffiti
	struct sitechangest change(locx, locy, locz, SITEBLOCK_GRAFFITI);
	location[cursite]->changes.push_back(change);
}

const string LocationsPool::getLocationName(int cursite)const
{
	return location[cursite]->getname();
}
/* common - purges empty squads from existence */
void cleangonesquads()
{
	for (int sq = len(squad) - 1; sq >= 0; sq--)
	{  //NUKE SQUAD IF IT IS GONE
		bool hasmembers = false;
		for (int p = 0; p < 6; p++)
			if (squad[sq]->squad[p] != NULL)
			{  // Let's do a bit of housekeeping here
			   // And see if we can't gracefully eliminate that
			   // pesky dead liberal in my squad bug
				if (squad[sq]->squad[p]->getNameAndAlignment().alive == false)
				{
					removesquadinfo(*squad[sq]->squad[p]);
					p = -1; // restart this for loop
				}
				else hasmembers = true;
			}
		if (!hasmembers)
		{  //SQUAD LOOT WILL BE DESTROYED
			if (activesquad == squad[sq]) activesquad = NULL;
			delete_and_remove(squad, sq);
		}
		//OTHERWISE YOU CAN TAKE ITS MONEY (and other gear)
		else location[squad[sq]->squad[0]->base]->getloot(squad[sq]->loot);
	}
}
// Prompt to turn new recruit into a sleeper
void sleeperize_prompt(DeprecatedCreature &converted, DeprecatedCreature &recruiter, int y)
{

	bool selection = false;
	while (true)
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(y, 0, CONST_IN_WHAT_CAPACITY_WILL);
		addstrAlt(converted.getNameAndAlignment().name);
		addstrAlt(CONST_BEST_SERVE_THE_LIBERAL_CAUSE);
		set_color_easy(selection ? WHITE_ON_BLACK : WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(y + 2, 0, selection ? TWO_SPACES : ARROW_RIGHT);
		addstrAlt(CONST_COME_TO);
		addstrAlt(location[recruiter.location]->getname(-1, true));
		addstrAlt(CONST_AS_A);
		set_color_easy(selection ? GREEN_ON_BLACK : GREEN_ON_BLACK_BRIGHT);
		addstrAlt(CONST_REGULAR_MEMBER);
		set_color_easy(selection ? WHITE_ON_BLACK : WHITE_ON_BLACK_BRIGHT);
		addstrAlt(singleDot);
		set_color_easy(selection ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
		mvaddstrAlt(y + 3, 0, selection ? ARROW_RIGHT : TWO_SPACES);
		addstrAlt(CONST_STAY_AT);
		addstrAlt(location[converted.worklocation]->getname(-1, true));
		addstrAlt(CONST_AS_A);
		set_color_easy(selection ? CYAN_ON_BLACK_BRIGHT : CYAN_ON_BLACK);
		addstrAlt(CONST_SLEEPER_AGENT);
		set_color_easy(selection ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
		addstrAlt(singleDot);
		int c = getkeyAlt();
		if ((c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) && selection)
		{
			converted.flag |= CREATUREFLAG_SLEEPER;
			converted.location = converted.worklocation;
			location[converted.worklocation]->mapped = 1;
			location[converted.worklocation]->hidden = 0;
			converted.base = converted.worklocation;
			liberalize(converted, false);
			break;
		}
		else if ((c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) && !selection)
		{
			converted.location = recruiter.location;
			converted.base = recruiter.base;
			liberalize(converted, false);
			break;
		}
		else if (is_page_up(c) || is_page_down(c)) selection = !selection;
	}
}
Location* find_site_in_city(const int site_type, const int city)
{
	int i = find_site_index_in_city(site_type, city);
	if (i != -1) return location[i];
	else return NULL;
}
int find_site_index_in_city(const int site_type, const int city)
{
	for (int i = 0; i < len(location); i++)
		if (location[i]->type == site_type && (!multipleCityMode || city == -1 || location[i]->city == city))
			return i;
	return -1;
}
int find_site_index_in_same_city(const int site_type, const int site_index)
{
	int city = -1;
	if (site_index >= 0) city = location[site_index]->city;
	return find_site_index_in_city(site_type, city);
}
void addChildren(Location* district, const vector<SiteTypes> subdistricts) {
	for (SiteTypes st : subdistricts) {
		district->addchild(st);
	}
}
void addChildren(Location* district, const vector<SiteTypes> subdistricts, const bool hasmaps) {
	for (SiteTypes st : subdistricts) {
		district->addchild(st)->mapped = hasmaps;
	}
}

void make_classic_world(bool hasmaps)
{
	Location* district = NULL;
	location.push_back(district = new Location(SITE_DOWNTOWN));
	district->area = 0;
	district->mapped = hasmaps; // for some reason this property isn't inherited by downtown locations so it's manually added for each one, need to debug why this happens
	addChildren(district, classicDowntown, hasmaps);
	{
		Location* site = district->addchild(SITE_BUSINESS_BARANDGRILL);
		site->renting = RENTING_CCS;
		site->hidden = true;
		site->mapped = false;
	}
	location.push_back(district = new Location(SITE_COMMERCIAL));
	district->area = 0;
	addChildren(district, classicCommercial);

	location.push_back(district = new Location(SITE_UDISTRICT));
	district->area = 0;
	addChildren(district, classicUptown);

	location.push_back(district = new Location(SITE_INDUSTRIAL));
	district->area = 0;
	district->addchild(SITE_RESIDENTIAL_SHELTER)->renting = RENTING_PERMANENT;
	{
		Location* site = district->addchild(SITE_INDUSTRY_WAREHOUSE);
		site->renting = RENTING_PERMANENT;
		site->upgradable = true;
	}
	district->addchild(SITE_RESIDENTIAL_TENEMENT);
	district->addchild(SITE_INDUSTRY_POLLUTER);
	district->addchild(SITE_INDUSTRY_SWEATSHOP);
	district->addchild(SITE_BUSINESS_CRACKHOUSE)->upgradable = true;
	{
		Location* site = district->addchild(SITE_RESIDENTIAL_BOMBSHELTER);
		site->renting = RENTING_CCS;
		site->hidden = true;
	}
	location.push_back(district = new Location(SITE_OUTOFTOWN));
	district->area = 1;
	addChildren(district, classicOutOfTown);
	{
		Location* site = district->addchild(SITE_OUTDOOR_BUNKER);
		site->renting = RENTING_CCS;
		site->hidden = true;
	}
	location.push_back(district = new Location(SITE_TRAVEL));
	district->area = 1;
	district->addchild(SITE_GOVERNMENT_WHITE_HOUSE);
}

void make_world(const bool hasmaps)
{
	if (!multipleCityMode)
	{
		make_classic_world(hasmaps);
		return;
	}
	//MAKE LOCATIONS
	Location* city = NULL;
	Location* district = NULL;
	//Location* site = NULL;
	location.push_back(city = new Location(SITE_CITY_SEATTLE));
	district = city->addchild(SITE_DOWNTOWN);
	district->area = 0;
	district->mapped = hasmaps; // for some reason this property isn't inherited by downtown locations so it's manually added for each one, need to debug why this happens
	addChildren(district, seattleDowntown, hasmaps);
	{
		Location* site = district->addchild(SITE_BUSINESS_BARANDGRILL);
		site->renting = RENTING_CCS;
		site->hidden = true;
		site->mapped = false;
	}
	district = city->addchild(SITE_UDISTRICT);
	district->area = 0;
	addChildren(district, seattleUptown);
	district = city->addchild(SITE_INDUSTRIAL);
	district->area = 0;
	district->addchild(SITE_RESIDENTIAL_SHELTER)->renting = RENTING_PERMANENT;
	{
		Location* site = district->addchild(SITE_INDUSTRY_WAREHOUSE);
		site->renting = RENTING_PERMANENT;
		site->upgradable = true;
	}
	district->addchild(SITE_RESIDENTIAL_TENEMENT);
	district->addchild(SITE_INDUSTRY_POLLUTER);
	district->addchild(SITE_INDUSTRY_SWEATSHOP);
	district->addchild(SITE_BUSINESS_CRACKHOUSE)->upgradable = true;
	district->addchild(SITE_BUSINESS_PAWNSHOP);
	district->addchild(SITE_BUSINESS_CARDEALERSHIP);
	district = city->addchild(SITE_OUTOFTOWN);
	district->area = 1;
	addChildren(district, seattleOutOfTown);
	location.push_back(city = new Location(SITE_CITY_NEW_YORK));
	district = city->addchild(SITE_DOWNTOWN);
	district->area = 0;
	strcpy(district->name, tag_Manhattan_Island);
	strcpy(district->shortname, tag_Manhattan);

	addChildren(district, newYorkManhattan);
	district = city->addchild(SITE_UDISTRICT);
	district->area = 0;
	strcpy(district->name, tag_Brooklyn_ampersand_Queens);
	strcpy(district->shortname, tag_Long_Island);
	{
		Location* site = district->addchild(SITE_INDUSTRY_WAREHOUSE);
		site->renting = RENTING_PERMANENT;
		site->upgradable = true;
	}
	addChildren(district, newYorkLongIsland);
	{
		Location* site = district->addchild(SITE_RESIDENTIAL_BOMBSHELTER);
		site->renting = RENTING_CCS;
		site->hidden = true;
	}
	district = city->addchild(SITE_INDUSTRIAL);
	district->area = 0;
	strcpy(district->name, tag_The_Bronx);
	strcpy(district->shortname, tag_The_Bronx);
	district->addchild(SITE_RESIDENTIAL_SHELTER)->renting = RENTING_PERMANENT;
	district->addchild(SITE_RESIDENTIAL_TENEMENT);
	district->addchild(SITE_INDUSTRY_POLLUTER);
	district->addchild(SITE_INDUSTRY_SWEATSHOP);
	district->addchild(SITE_LABORATORY_COSMETICS);
	district->addchild(SITE_BUSINESS_VEGANCOOP);
	district->addchild(SITE_BUSINESS_PAWNSHOP);
	district->addchild(SITE_BUSINESS_CARDEALERSHIP);
	district->addchild(SITE_BUSINESS_CRACKHOUSE)->upgradable = true;
	district->addchild(SITE_OUTDOOR_PUBLICPARK);
	district = city->addchild(SITE_OUTOFTOWN);
	district->area = 1;
	district->addchild(SITE_INDUSTRY_NUCLEAR);
	location.push_back(city = new Location(SITE_CITY_LOS_ANGELES));
	district = city->addchild(SITE_DOWNTOWN);
	district->area = 0;
	district->addchild(SITE_RESIDENTIAL_SHELTER)->renting = RENTING_PERMANENT;

	addChildren(district, losAngelesDowntown);

	district = city->addchild(SITE_UDISTRICT);
	district->area = 0;
	strcpy(district->name, tag_Greater_Hollywood);
	strcpy(district->shortname, tag_Hollywood);

	addChildren(district, hollyWoodUptown);

	district = city->addchild(SITE_INDUSTRIAL);
	district->area = 0;
	strcpy(district->name, tag_Seaport_Area);
	strcpy(district->shortname, tag_Seaport);
	{
		Location* site = district->addchild(SITE_INDUSTRY_WAREHOUSE);
		site->renting = RENTING_PERMANENT;
		site->upgradable = true;
	}
	addChildren(district, seaportArea);
	district->addchild(SITE_BUSINESS_CRACKHOUSE)->upgradable = true;
	district = city->addchild(SITE_OUTOFTOWN);
	district->area = 1;
	strcpy(district->name, tag_Outskirts_amp_Orange_County);
	district->addchild(SITE_GOVERNMENT_PRISON);
	district->addchild(SITE_INDUSTRY_NUCLEAR);
	district->addchild(SITE_GOVERNMENT_ARMYBASE);
	{
		Location* site = district->addchild(SITE_OUTDOOR_BUNKER);
		site->renting = RENTING_CCS;
		site->hidden = true;
	}
	location.push_back(city = new Location(SITE_CITY_WASHINGTON_DC));
	district = city->addchild(SITE_DOWNTOWN);
	district->area = 0;
	strcpy(district->name, tag_Downtown);
	addChildren(district, washingtonDCDowntown);
	district->addchild(SITE_RESIDENTIAL_SHELTER)->renting = RENTING_PERMANENT;
	district = city->addchild(SITE_UDISTRICT);
	district->area = 0;
	strcpy(district->name, tag_National_Mall);
	strcpy(district->shortname, CONST_MALL);
	district->addchild(SITE_OUTDOOR_PUBLICPARK);
	district->addchild(SITE_GOVERNMENT_WHITE_HOUSE);
	district = city->addchild(SITE_OUTOFTOWN);
	district->area = 1;
	strcpy(district->name, tag_Arlington);
	district->addchild(SITE_GOVERNMENT_PRISON);
	district->addchild(SITE_GOVERNMENT_INTELLIGENCEHQ);
	district->addchild(SITE_GOVERNMENT_ARMYBASE);
}
// Finds a location with the corresponding type and returns
// its index in the location array
int findlocation(int type, int city = -1)
{
	if (!multipleCityMode) city = -1;
	for (int i = 0; i < len(location); i++)
		if (location[i]->type == type && (location[i]->city == city || city == -1)) return i;
	return -1;
}
// Locations - Construct a new location with the specified parameters
Location::Location(const char type_, const int parent_)
	: type(type_), city(-1), parent(parent_), renting(RENTING_NOCONTROL), needcar(false), hidden(false), upgradable(false)
{
	if (this->parent != -1)
	{
		this->needcar = location[this->parent]->needcar;
		this->mapped = location[this->parent]->mapped;
		this->area = location[this->parent]->area;
		this->city = location[this->parent]->city;
	}
	if (this->city < 0 && multipleCityMode)
		this->city = this->type;
	initlocation(*this);
}
Location* Location::addchild(const char type_)
{
	Location *newloc = new Location(type_, findlocation(this->type, this->city));
	location.push_back(newloc);
	return newloc;
}
/* Settings for shortname_ (true is 1 and false is 0, by the way):
* -1: entire name is long, no matter what
*  0: first part of place name is long, and if there's a city at the end it's short
*  1: first part of the name is short unless the place itself is a city in which case it's long, and if there's a city at the end it's short
*  2: entire name is short, no matter what */
string defaultName(const signed char shortname_, Location* thisLocation) {
	string str;
	if ((shortname_ >= 1 && thisLocation->type != thisLocation->city) || shortname_ >= 2) {
		if (thisLocation->front_business != -1)
			str = thisLocation->front_shortname;
		else
			str = thisLocation->shortname;
	}
	else {
		if (thisLocation->front_business != -1)
			str = thisLocation->front_name;
		else
			str = thisLocation->name;
	}
	return str;
}
string Location::getname(const signed char shortname_, const bool include_city)
{
	string str = defaultName(shortname_, this);
	if (multipleCityMode&&include_city&&type != city) {
		string cityname = location[findlocation(city, city)]->getname(shortname_ + 2);
			switch (cityLocationTags[str]) {
			case ENUM_tag_Downtown:
				str += singleSpace + cityname;
				break;
			case ENUM_tag_University_District:
			case ENUM_tag_u_District:
			case ENUM_tag_Industrial_District:
			case ENUM_tag_i_District:
			case ENUM_tag_Shopping:
			case ENUM_tag_Outskirts:
			case ENUM_tag_Seaport_Area:
			case ENUM_tag_Seaport:
			case ENUM_tag_Outskirts_amp_Orange_County:
				str = cityname + singleSpace + str;
				break;
			case ENUM_tag_City_Outskirts:
				str = cityname + CONST_OUTSKIRTS;
				break;
			case ENUM_tag_Arlington:
				str += (shortname_ < 0 ? CONST_VIRGINIA : CONST_VA);
				break;
			case ENUM_tag_Hollywood:
			case ENUM_tag_Greater_Hollywood:
				str += (shortname_ < 0 ? CONST_CALIFORNIA : CONST_CA);
				break;
			case ENUM_tag_Manhattan:
			case ENUM_tag_Manhattan_Island:
			case ENUM_tag_Brooklyn_ampersand_Queens:
			case ENUM_tag_Long_Island:
			case ENUM_tag_The_Bronx:
				str += (shortname_ < 0 ? CONST_X_NEW_YORK : CONST_NY);
				break;
			default:
				str += COMMA_SPACE + cityname;
				break;
			}
		
	}
	return str;
}
bool Location::duplicatelocation()
{
	for (int l = 0; l < len(location); l++)
	{
		if (location[l] == this)
			continue;
		if (type != SITE_RESIDENTIAL_SHELTER && !strcmp(location[l]->name, this->name))
			return true;
		if (location[l]->front_business != -1 && this->front_business != -1 &&
			!strcmp(location[l]->front_shortname, this->front_shortname))
			return true;
	}
	return 0;
}
void Location::update_heat_protection()
{
	int l;
	for (l = 0; l < len(location); l++)
	{
		if (location[l] == this)
			break;
	}
	if (l == len(location))
	{
		heat_protection = 0;
		return;
	}
	int numpres = CreaturePool::getInstance().howManyLivingPeopleAreHere(l);
	heat_protection = 0;
	// Determine how effective your current safehouse
	// is at keeping the police confused
	switch (location[l]->type)
	{
	case SITE_INDUSTRY_WAREHOUSE:
		if (location[l]->front_business != -1)
			heat_protection += 12; // Business front -- high protection
		else
			heat_protection += 0; // Abandoned warehouse -- no protection
		break;
	case SITE_BUSINESS_CRACKHOUSE:
		if (location[l]->front_business != -1)
			heat_protection += 10; // Business front -- high medium protection (Cops still find it a bit shady)
		else
			heat_protection += 0; // Regular Crackhouse -- no protection
		break;
	case SITE_RESIDENTIAL_SHELTER:
		heat_protection += 0; // Homeless shelter -- no protection
		break;
	case SITE_RESIDENTIAL_TENEMENT:
		heat_protection += 4; // Lower class housing -- low protection
		break;
	case SITE_RESIDENTIAL_APARTMENT:
		heat_protection += 8; // Middle class housing -- medium protection
		break;
	case SITE_RESIDENTIAL_BOMBSHELTER:
	case SITE_OUTDOOR_BUNKER:
	case SITE_BUSINESS_BARANDGRILL:
	case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
		heat_protection += 12; // Upper class housing -- high protection
		break;
	}
	if (lawList[LAW_FLAGBURNING] == -2 && location[l]->haveflag) heat_protection += 6; // More protection if the flag is sacred
	else if (lawList[LAW_FLAGBURNING] != -2 && location[l]->haveflag) heat_protection += 2; // Some if the flag isn't
	else if (lawList[LAW_FLAGBURNING] == -2 && !(location[l]->haveflag)) heat_protection -= 2; // Lose some if it is and you have no flag
	else {} // None if it isn't and you have no flag
	if (heat_protection < 0) heat_protection = 0;
	heat_protection *= 5;
	if (heat_protection > 95) heat_protection = 95;
}
std::string getactivity(ActivityST &act)
{
	if (getActivityString.count(act.type)) {
		return getActivityString[act.type];
	}
	else
		switch (act.type)
		{
		case ACTIVITY_HOSTAGETENDING:
		{
			std::string str = CONST_TENDING_TO;
			int pl = getpoolcreature(act.arg);
			if (pl != -1) return str + CreaturePool::getInstance().getName(pl);
			else return str + CONST_A_BUG;
		}
		case ACTIVITY_MAKE_ARMOR:
			return CONST_MAKING + armortype[act.arg]->get_shortname();
		case ACTIVITY_VISIT:
			return CONST_GOING_TO + location[act.arg]->getname(!location[act.arg]->is_city());
		default:
			return CONST_REPORTING_BUGS_TO_THE_DEV_TEAM;
		}
}
/* daily - manages too hot timer and when a site map should be re-seeded and renamed */
void advancelocations()
{
	//ADVANCE LOCATIONS
	for (int l = 0; l < len(location); l++)
	{
		if (location[l]->closed > 0)
		{
			location[l]->closed--;
			if (location[l]->closed == 0)
			{  //Clean up graffiti, patch up walls, restore fire damage
				location[l]->changes.clear();
				//If high security is supported, chance to throw guards everywhere
				if (securityable(location[l]->type) && LCSrandom(2))
					location[l]->highsecurity = 60;
				//Else remodel the location, invalidate maps
				else initlocation(*location[l]);
			}
		}
		else if (location[l]->highsecurity > 0)
		{  // Bank will remain on high security much longer
			if (location[l]->type != SITE_BUSINESS_BANK)
				location[l]->highsecurity--;
			else if (!LCSrandom(5))
				location[l]->highsecurity--;
		}
	}
}
bool DeprecatedCreature::is_imprisoned() const
{
	return(alive && clinic == 0 && dating == 0 && hiding == 0 &&
		!(flag & CREATUREFLAG_SLEEPER) &&
		::location[this->location]->part_of_justice_system());
}
bool DeprecatedCreature::is_active_liberal() const
{
	return(alive && align == ALIGN_LIBERAL && clinic == 0 && dating == 0 &&
		hiding == 0 && !(flag & CREATUREFLAG_SLEEPER) &&
		!::location[this->location]->part_of_justice_system());
}
/* prompt user to enter an amount of items to equip, move, or sell */
long prompt_amount(long min, long max)
{
	printparty();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(8, 15, CONST_HOW_MANY);
	char str[100];
	enter_name(8, 30, str, 100, toCstring(max));
	int amount = atoi(str);
	amount = std::max((long)amount, min);
	amount = std::min((long)amount, max);
	return amount;
}


void printEquipMenu(const int loc, const int page, const string errmsg, const vector<Item *> loot) {
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(0, 0, CONST_EQUIP_THE_SQUAD);
	printparty();
	if (!errmsg.empty()) {
		set_color_easy(CYAN_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 20, errmsg);
		set_color_easy(WHITE_ON_BLACK);
	}
	int x = 1, y = 10;
	char str[200];
	//char str2[200];
	for (int l = page * 18; l < len(loot) && l < page * 18 + 18; l++)
	{
		string s = loot[l]->equip_title();
		if (loot[l]->get_number() > 1)
			s += CONST_X + tostring(loot[l]->get_number());
		str[0] = l - page * 18 + 'A';
		str[1] = '\x0';
		strcat(str, spaceDashSpace);
		strcat(str, s);
		mvaddstrAlt(y, x, str);
		x += 26;
		if (x > 53) x = 1, y++;
	}
	//PAGE UP
	if (page > 0)
	{
		mvaddstrAlt(17, 1, addprevpagestr());
	}
	//PAGE DOWN
	if ((page + 1) * 18 < len(loot))
	{
		mvaddstrAlt(17, 53, addnextpagestr());
	}
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(19, 1, CONST_PRESS_A_LETTER_TO_EQUIP_A_LIBERAL_ITEM);
	mvaddstrAlt(20, 1, CONST_PRESS_A_NUMBER_TO_DROP_THAT_SQUAD_MEMBER_S_CONSERVATIVE_WEAPON);
	mvaddstrAlt(21, 1, CONST_S_LIBERALLY_STRIP_A_SQUAD_MEMBER);
	mvaddstrAlt(22, 1, CONST_CURSORS_INCREASE_OR_DECREASE_AMMO_ALLOCATION);
	if (loc != -1)
	{
		if (len(location[loc]->loot)) set_color_easy(WHITE_ON_BLACK);
		else set_color_easy(BLACK_ON_BLACK_BRIGHT);
		mvaddstrAlt(23, 1, CONST_Y_GET_THINGS_FROM);
		addstrAlt(location[loc]->getname(true));
		if (len(loot)) set_color_easy(WHITE_ON_BLACK);
		else set_color_easy(BLACK_ON_BLACK_BRIGHT);
		mvaddstrAlt(23, 40, CONST_Z_STASH_THINGS_AT);
		addstrAlt(location[loc]->getname(true));
	}
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(24, 1, enter_done);
}
int makeChoice(const int increaseammo, const int decreaseammo) {


	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	moveAlt(8, 20);
	if (increaseammo)
		addstrAlt(CHOOSE_A_LIBERAL_TO + CONST_RECEIVE_A_CLIP);
	else if (decreaseammo)
		addstrAlt(CHOOSE_A_LIBERAL_TO + CONST_DROP_A_CLIP);
	else addstrAlt(CHOOSE_A_LIBERAL_TO + CONST_RECEIVE_IT);
	return getkeyAlt();

}

// TODO Relocate these to a new file
// to allow removal of creature.h
string transferClipBaseSquad(const bool decreaseammo, const bool increaseammo, int& slot, int& page, const int e, vector<Item *> &loot) {

	DeprecatedCreature *squaddie = activesquad->squad[e - '1'];
	if (squaddie)
	{
		if (decreaseammo)
		{
			if (squaddie->has_clips())
			{
				loot.push_back(squaddie->take_one_clip());
				consolidateloot(loot);
				return NOT_ERROR_BUT_CONTINUE;
			}
			else if (!squaddie->get_weapon().uses_ammo())
			{
				return CONST_NO_AMMO_TO_DROP;
			}
			else
			{
				return CONST_NO_SPARE_CLIPS;
			}
		}
		if (increaseammo)
		{
			if (!squaddie->get_weapon().uses_ammo())
			{
				return CONST_NO_AMMO_REQUIRED;
			}
			slot = -1;
			for (int sl = 0; sl < len(loot); sl++)
			{
				if (loot[sl]->whatIsThis() == THIS_IS_CLIP && squaddie->get_weapon().acceptable_ammo(*loot[sl]))
				{
					slot = sl;
					break;
				}
				else if (loot[sl]->whatIsThis() == THIS_IS_WEAPON && loot[sl]->is_same_type(squaddie->get_weapon())) //For throwing weapons. -XML
				{
					Weapon* w = static_cast<Weapon*>(loot[sl]); //cast -XML
					if (w->is_throwable())
					{
						slot = sl;
						break;
					}
				}
			}
			if (slot == -1)
			{
				return CONST_NO_AMMO_AVAILABLE;
			}
		}
		int armok = 2;
		if ((squaddie->wound[BODYPART_ARM_RIGHT] & WOUND_NASTYOFF) ||
			(squaddie->wound[BODYPART_ARM_RIGHT] & WOUND_CLEANOFF)) armok--;
		if ((squaddie->wound[BODYPART_ARM_LEFT] & WOUND_NASTYOFF) ||
			(squaddie->wound[BODYPART_ARM_LEFT] & WOUND_CLEANOFF)) armok--;
		if (squaddie->special[SPECIALWOUND_NECK] != 1) armok = 0;
		if (squaddie->special[SPECIALWOUND_UPPERSPINE] != 1) armok = 0;
		if (loot[slot]->whatIsThis() == THIS_IS_WEAPON && armok)
		{
			Weapon* w = static_cast<Weapon*>(loot[slot]); //cast -XML
			squaddie->give_weapon(*w, &loot);
			if (loot[slot]->empty()) delete_and_remove(loot, slot);
			if (page * 18 >= len(loot) && page != 0) page--;
		}
		else if (loot[slot]->whatIsThis() == THIS_IS_ARMOR)
		{
			Armor* a = static_cast<Armor*>(loot[slot]); //cast -XML
			squaddie->give_armor(*a, &loot);
			if (loot[slot]->empty()) delete_and_remove(loot, slot);
			if (page * 18 >= len(loot) && page != 0) page--;
		}
		else if (loot[slot]->whatIsThis() == THIS_IS_CLIP && armok)
		{
			int space = 9 - squaddie->count_clips();
			if (!squaddie->get_weapon().uses_ammo())
			{
				return CONST_CAN_T_CARRY_AMMO_WITHOUT_A_GUN;
			}
			else if (!squaddie->get_weapon().acceptable_ammo(*loot[slot]))
			{
				return CONST_THAT_AMMO_DOESN_T_FIT;
			}
			else if (space < 1)
			{
				return CONST_CAN_T_CARRY_ANY_MORE_AMMO;
			}
			else
			{
				int amount = 1;
				if (loot[slot]->get_number() > 1 && !increaseammo)
					amount = prompt_amount(0, min((int)loot[slot]->get_number(), space));
				squaddie->take_clips(*loot[slot], amount);
				if (loot[slot]->empty()) delete_and_remove(loot, slot);
				if (page * 18 >= len(loot) && page != 0) page--;
			}
		}
		consolidateloot(loot);
	}
	return "";
}
bool isThereNoActivesquad() {
	return activesquad == NULL;
}
// This function is used only once, but it allows another function not to import *activesquad (though, like much of the code, its purpose is unclear)
void clearActiveSquadForceInc() {
	for (int p = 0; p < 6; p++)
		if (activesquad->squad[p] != NULL)
			activesquad->squad[p]->forceinc = 0;
}
void disarmSquadmember(vector<Item *> &loot, const int p) {

	if (activesquad->squad[p] != NULL)
	{
		activesquad->squad[p]->drop_weapons_and_clips(&loot);
		consolidateloot(loot);
	}
}

bool notDoesActiveSquadHaveExactlyOneMember() {
	bool choice = true;
	if (activesquad->squad[0])
	{
		choice = false;
		for (int i = 1; i < 6; i++)
			if (activesquad->squad[i])
			{
				choice = true; break;
			}
	}
	return choice;
}
void completelyStripSquadMember(vector<Item *> &loot, int d) {
	if (activesquad->squad[d])
	{
		activesquad->squad[d]->strip(&loot);
		consolidateloot(loot);
	}
}
/* review squad equipment */
void equip(vector<Item *> &loot, int loc)
{

	if (isThereNoActivesquad()) return;
	consolidateloot(loot);
	if (loc != -1) consolidateloot(location[loc]->loot);
	int page = 0;
	string errmsg = "";
	while (true)
	{
		printEquipMenu(loc, page, errmsg, loot);
		errmsg = "";

		int c = getkeyAlt();
		bool increaseammo = (c == KEY_UP);
		bool decreaseammo = (c == KEY_DOWN);
		if ((c >= 'a'&&c <= 'r') || increaseammo || decreaseammo)
		{
			int slot = c - 'a' + page * 18;
			if (increaseammo || decreaseammo) slot = -999;
			else
			{
				if (slot < 0 || slot >= len(loot)) continue; // Out of range.
				else if (!(loot[slot]->whatIsThis() == THIS_IS_WEAPON)
					&& !(loot[slot]->whatIsThis() == THIS_IS_ARMOR)
					&& !(loot[slot]->whatIsThis() == THIS_IS_CLIP))
				{
					errmsg = CONST_YOU_CAN_T_EQUIP_THAT;
					continue;
				}
			}
			bool choice = notDoesActiveSquadHaveExactlyOneMember();
			int e = '1';
			if (choice)
			{
				e = makeChoice(increaseammo, decreaseammo);
			}
			if (e >= '1'&&e <= '6')
			{
				errmsg = transferClipBaseSquad(decreaseammo, increaseammo, slot, page, e, loot);
				if (!errmsg.empty()) {
					if (errmsg == NOT_ERROR_BUT_CONTINUE) {
						errmsg = "";
					}
					continue;
				}
			}
		}
		else
			if (c == 's')
			{
				bool choice = notDoesActiveSquadHaveExactlyOneMember();

				int d = '1';
				if (choice)
				{
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(8, 20, CHOOSE_A_LIBERAL_TO + CONST_STRIP_DOWN);
					d = getkeyAlt();
				}
				if (d >= '1'&& d <= '6')
				{
					completelyStripSquadMember(loot, d - '1');
				}

			}
			else
				if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) { break; }
		if (loc != -1)
		{
			if (c == 'y'&&len(location[loc]->loot)) moveloot(loot, location[loc]->loot);
			if (c == 'z'&&len(loot)) moveloot(location[loc]->loot, loot);
		}
		if (c >= '1'&&c <= '6')
		{
			int p = c - '1';
			disarmSquadmember(loot, p);
		}
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 18 < len(loot)) page++;
	}
}
/* lets you pick stuff to stash/retrieve from one location to another */
void moveloot(vector<Item *> &dest, vector<Item *> &source)
{
	int page = 0;
	vector<int> selected(len(source), 0);
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(0, 0, CONST_SELECT_OBJECTS);
		printparty();
		int x = 1, y = 10;
		char str[200];
		for (int l = page * 18; l < len(source) && l < page * 18 + 18; l++)
		{
			if (selected[l]) set_color_easy(GREEN_ON_BLACK_BRIGHT);
			else set_color_easy(WHITE_ON_BLACK);
			string s = source[l]->equip_title();
			if (source[l]->get_number() > 1)
			{
				s += singleSpace;
				if (selected[l] > 0) s += tostring(selected[l]) + CONST_SLASH;
				else s += CONST_X_X;
				s += tostring(source[l]->get_number());
			}
			str[0] = l - page * 18 + 'A';
			str[1] = '\x0';
			strcat(str, spaceDashSpace);
			strcat(str, s);
			mvaddstrAlt(y, x, str);
			x += 26;
			if (x > 53) x = 1, y++;
		}
		//PAGE UP
		set_color_easy(WHITE_ON_BLACK);
		if (page > 0)
		{
			mvaddstrAlt(17, 1, addprevpagestr());
		}
		//PAGE DOWN
		if ((page + 1) * 18 < len(source))
		{
			mvaddstrAlt(17, 53, addnextpagestr());
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(23, 1, CONST_PRESS_A_LETTER_TO_SELECT_AN_ITEM);
		mvaddstrAlt(24, 1, enter_done);
		int c = getkeyAlt();
		if (c >= 'a'&&c <= 'r')
		{
			int slot = c - 'a' + page * 18;
			if (slot >= 0 && slot < len(source))
			{
				if (selected[slot]) selected[slot] = 0;
				else if (source[slot]->get_number() > 1)
					selected[slot] = prompt_amount(0, source[slot]->get_number());
				else selected[slot] = 1;
			}
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 18 < len(source)) page++;
	}
	for (int l = len(source) - 1; l >= 0; l--) if (selected[l] > 0)
	{
		if (source[l]->get_number() <= selected[l])
		{
			dest.push_back(source[l]);
			source.erase(source.begin() + l);
		}
		else
		{
			Item* newit = source[l]->split(selected[l]);
			dest.push_back(newit);
		}
	}
	// Avoid stuff jumping around the next time you equip.
	consolidateloot(dest);
}
/* equipment - assign new bases to the equipment */
void equipmentbaseassign()
{
	int page_loot = 0, page_loc = 0, selectedbase = 0;
	bool sortbytype = false;
	vector<Item *> temploot;
	map<Item *, Location *> temploot2;
	for (int l = 0; l < len(location); l++) for (int l2 = 0; l2 < len(location[l]->loot); l2++)
		if (!location[l]->siege.siege)
		{
			temploot.push_back(location[l]->loot[l2]);
			temploot2[location[l]->loot[l2]] = location[l];
		}
	if (!len(temploot)) return;
	vector<int> temploc;
	for (int l = 0; l < len(location); l++) if (location[l]->renting >= 0 && !location[l]->siege.siege)
		temploc.push_back(l);
	if (!len(temploc)) return;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		printfunds();
		mvaddstrAlt(0, 0, CONST_MOVING_EQUIPMENT);
		mvaddstrAlt(1, 0, CONST_ITEM_CURRENT_LOCATION);
		mvaddstrAlt(1, 51, CONST_NEW_LOCATION);
		for (int p = page_loot * 19, y = 2; p < len(temploot) && p < page_loot * 19 + 19; p++, y++)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 0);
			addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(temploot[p]->equip_title());
			mvaddstrAlt(y, 25, temploot2[temploot[p]]->getname(true, true));
		}
		for (int p = page_loc * 9, y = 2; p < len(temploc) && p < page_loc * 9 + 9; p++, y++)
		{
			if (p == selectedbase)set_color_easy(WHITE_ON_BLACK_BRIGHT);
			else set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 51);
			addcharAlt(y + '1' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(location[temploc[p]]->getname(true, true));
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, CONST_PRESS_A_LETTER_TO_ASSIGN_A_BASE_PRESS_A_NUMBER_TO_SELECT_A_BASE);
		moveAlt(23, 0);
		if (sortbytype) addstrAlt(CONST_T_TO_SORT_BY_LOCATION);
		else addstrAlt(CONST_T_TO_SORT_BY_TYPE);
		addstrAlt(CONST_SHIFT_AND_A_NUMBER_WILL_MOVE_ALL_ITEMS);
		moveAlt(24, 0); // location for either viewing other base pages or loot pages
		if (len(temploc) > 9)
		{
			addstrAlt(CONST_TO_VIEW_OTHER_BASE_PAGES);
			moveAlt(24, 34); // we have base pages, so different location for viewing other loot pages
		}
		if (len(temploot) > 19)
			addstrAlt(addpagestr());
		int c = getkeyAlt();
		//PAGE UP (items)
		if (is_page_up(c) && page_loot > 0) page_loot--;
		//PAGE DOWN (items)
		if (is_page_down(c) && (page_loot + 1) * 19 < len(temploot)) page_loot++;
		//PAGE UP (locations)
		if (c == ','&&page_loc > 0) page_loc--;
		//PAGE DOWN (locations)
		if (c == '.' && (page_loc + 1) * 9 < len(temploc)) page_loc++;
		//Toggle sorting method
		if (c == 't')
		{
			sortbytype = !sortbytype;
			if (sortbytype) sort(temploot.begin(), temploot.end(), Item::sort_compare);
			else
			{  //Sort by location
				temploot.clear();
				for (int l = 0; l < len(location); l++) for (int l2 = 0; l2 < len(location[l]->loot); l2++)
					if (!location[l]->siege.siege) temploot.push_back(location[l]->loot[l2]);
			}
		}
		if (c >= 'a'&&c <= 's')
		{
			int p = page_loot * 19 + c - 'a';
			if (p < len(temploot))
				// Search through the old base's stuff for this item
				for (int l2 = 0; l2 < len(temploot2[temploot[p]]->loot); l2++)
					// Remove it from that inventory and move it to the new one
					if (temploot2[temploot[p]]->loot[l2] == temploot[p])
					{
						temploot2[temploot[p]]->loot.erase(temploot2[temploot[p]]->loot.begin() + l2);
						location[temploc[selectedbase]]->loot.push_back(temploot[p]);
						temploot2[temploot[p]] = location[temploc[selectedbase]];
					}
		}
		if (c >= '1'&&c <= '9')
		{
			int p = page_loc * 9 + c - '1';
			if (p < len(temploc)) selectedbase = p;
		}
		for (int upnumi = 0; upnumi < len(upnums); upnumi++)
		{
			if (c == upnums[upnumi])
			{
				// Set base location
				int basechoice = page_loc * 9 + upnumi;
				if (basechoice < len(temploc))
				{
					selectedbase = basechoice;
					// Search through the old base's stuff for this item
					for (int p = 0; p < len(temploot); p++)
						// Search through the old base's stuff for this item
						for (int l2 = 0; l2 < len(temploot2[temploot[p]]->loot); l2++)
							// Remove it from that inventory and move it to the new one
							if (temploot2[temploot[p]]->loot[l2] == temploot[p])
							{
								temploot2[temploot[p]]->loot.erase(temploot2[temploot[p]]->loot.begin() + l2);
								location[temploc[selectedbase]]->loot.push_back(temploot[p]);
								temploot2[temploot[p]] = location[temploc[selectedbase]];
							}
				}
			}
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}
/* combines multiple items of the same type into stacks */
void consolidateloot(vector<Item *> &loot)
{
	//PUT THINGS TOGETHER
	for (int l = len(loot) - 1; l >= 1; l--) for (int l2 = l - 1; l2 >= 0; l2--)
	{
		loot[l2]->merge(*loot[l]);
		if (loot[l]->empty())
		{
			delete_and_remove(loot, l); break;
		}
	}
	sort(loot.begin(), loot.end(), Item::sort_compare);
}
/* check if the squad has a certain weapon */
char squadhasitem(Deprecatedsquadst &sq, const string& type)
{
	if (getweapontype(type) == -1) return 0;
	for (int p = 0; p < 6; p++) if (sq.squad[p])
		if (sq.squad[p]->get_weapon().get_itemtypename() == type) return 1;
	for (int l = 0; l < len(sq.loot); l++)
	{
		if (sq.loot[l]->get_itemtypename() != type) continue;
		if (sq.loot[l]->whatIsThis() == THIS_IS_WEAPON && sq.loot[l]->get_itemtypename() == type) return 1;
	}
	return 0;
}
/* location info at top of screen */
void printlocation(long loc)
{

	if (location[loc]->siege.siege)
	{
		if (!location[loc]->siege.underattack)
		{
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(2, 1, CONST_THE_POLICE_HAVE_SURROUNDED_THIS_LOCATION);
		}
		else
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			switch (location[loc]->siege.siegetype)
			{
			case SIEGE_POLICE:
				mvaddstrAlt(2, 1, CONST_THE_POLICE_ARE_RAIDING_THIS_LOCATION); break;
			case SIEGE_CIA:
				mvaddstrAlt(2, 1, CONST_THE_CIA_IS_RAIDING_THIS_LOCATION); break;
			case SIEGE_HICKS:
				mvaddstrAlt(2, 1, CONST_THE_MASSES_ARE_STORMING_THIS_LOCATION); break;
			case SIEGE_CORPORATE:
				mvaddstrAlt(2, 1, CONST_THE_CORPORATIONS_ARE_RAIDING_THIS_LOCATION); break;
			case SIEGE_CCS:
				mvaddstrAlt(2, 1, CONST_THE_CCS_IS_RAIDING_THIS_LOCATION); break;
			case SIEGE_FIREMEN:
				mvaddstrAlt(2, 1, CONST_FIREMEN_ARE_RAIDING_THIS_LOCATION); break;
			}
		}
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(2, 1, CONST_YOU_ARE_NOT_UNDER_SIEGE_YET);
	}
	if (location[loc]->can_be_upgraded())
	{
		if (numbereating(loc) > 0)
		{
			if (fooddaysleft(loc))
			{
				if (fooddaysleft(loc) < 4)
				{
					if (!location[loc]->siege.siege)set_color_easy(WHITE_ON_BLACK);
					else set_color_easy(YELLOW_ON_BLACK_BRIGHT);
					mvaddstrAlt(3, 1, CONST_THIS_LOCATION_HAS_FOOD_FOR_ONLY_A_FEW_DAYS);
				}
			}
			else
			{
				if (!location[loc]->siege.siege)set_color_easy(WHITE_ON_BLACK);
				else set_color_easy(RED_ON_BLACK_BRIGHT);
				mvaddstrAlt(3, 1, CONST_THIS_LOCATION_HAS_INSUFFICIENT_FOOD_STORES);
			}
		}
		if (location[loc]->compound_walls & COMPOUND_BASIC)
		{
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(4, 1, CONST_FORTIFIED_COMPOUND);
		}
		if (location[loc]->compound_walls & COMPOUND_PRINTINGPRESS)
		{
			set_color_easy(BLUE_ON_BLACK_BRIGHT);
			mvaddstrAlt(4, 31, CONST_PRINTING_PRESS);
		}
		if (location[loc]->front_business != -1)
		{
			set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
			mvaddstrAlt(4, 54, CONST_BUSINESS_FRONT);
		}
		if (location[loc]->compound_walls & COMPOUND_CAMERAS)
		{
			if (location[loc]->siege.siege&&location[loc]->siege.cameras_off)
			{
				set_color_easy(RED_ON_BLACK);
				mvaddstrAlt(5, 1, CONST_CAMERAS_OFF);
			}
			else
			{
				set_color_easy(GREEN_ON_BLACK_BRIGHT);
				mvaddstrAlt(5, 1, CONST_CAMERAS_ON);
			}
		}
		if (location[loc]->compound_walls & COMPOUND_TRAPS)
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(5, 16, CONST_BOOBY_TRAPS);
		}
		if (location[loc]->compound_walls & COMPOUND_AAGUN)
		{
			set_color_easy(CYAN_ON_BLACK_BRIGHT);
			mvaddstrAlt(5, 33, CONST_AA_GUN);
		}
		if (location[loc]->compound_walls & COMPOUND_TANKTRAPS)
		{
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(5, 46, CONST_TANK_TRAPS);
		}
		if (location[loc]->siege.siege&&location[loc]->siege.lights_off)
		{
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(5, 60, CONST_LIGHTS_OUT);
		}
		else if (location[loc]->compound_walls & COMPOUND_GENERATOR)
		{
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(5, 61, CONST_GENERATOR);
		}
		int eaters = numbereating(loc), days = fooddaysleft(loc);
		if (eaters > 0)
		{
			if (days >= 1)
			{
				set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(6, 50, days);
				addstrAlt(CONST_X_SPACE_DAY);
				if (days != 1)addcharAlt('s');
				addstrAlt(CONST_OF_FOOD_LEFT);
			}
			else if (days == 0)
			{
				set_color_easy(RED_ON_BLACK);
				mvaddstrAlt(6, 50, CONST_NOT_ENOUGH_FOOD);
			}
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(6, 1, location[loc]->compound_stores);
		addstrAlt(CONST_DAILY_RATION);
		if (location[loc]->compound_stores != 1)addstrAlt(CONST_S);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(6, 30, eaters);
		addstrAlt(CONST_EATING);
	}
}
/* location and squad header */
void locheader()
{

	if (activesquad != NULL && activesquad->squad[0]->location != -1)
	{
		if (location[activesquad->squad[0]->location]->siege.siege)
		{
			if (location[activesquad->squad[0]->location]->siege.underattack)set_color_easy(RED_ON_BLACK_BRIGHT);
			else set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		}
		else set_color_easy(WHITE_ON_BLACK);
	}
	else if (selectedsiege != -1)
	{
		if (location[selectedsiege]->siege.siege)
		{
			if (location[selectedsiege]->siege.underattack)set_color_easy(RED_ON_BLACK_BRIGHT);
			else set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		}
		else set_color_easy(WHITE_ON_BLACK);
	}
	else set_color_easy(WHITE_ON_BLACK);
	moveAlt(0, 0);
	if (activesquad != NULL && activesquad->squad[0]->location != -1)
	{
		addstrAlt(location[activesquad->squad[0]->location]->getname(false, true));
		addstrAlt(COMMA_SPACE);
	}
	else
	{
		if (selectedsiege == -1)
		{
			addstrAlt(CONST_NO_SQUAD_SELECTED);
			addstrAlt(COMMA_SPACE);
		}
		else
		{
			addstrAlt(location[selectedsiege]->getname(false, true));
			addstrAlt(COMMA_SPACE);
		}
	}
	addstrAlt(getmonth(month, true));
	addstrAlt(singleSpace);
	addstrAlt(day);
	addstrAlt(COMMA_SPACE);
	addStringYear();
	if (activesquad == NULL && selectedsiege == -1)
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		mvaddstrAlt(3, 6, CONST_TO_FORM_A_NEW_SQUAD);
		mvaddstrAlt(4, 6, CONST_1_R_REVIEW_ASSETS_AND_FORM_SQUADS);
		mvaddstrAlt(5, 6, CONST_2_PRESS_Z_TO_ASSEMBLE_A_NEW_SQUAD);
		set_color_easy(WHITE_ON_BLACK);
	}
	printfunds();
	if (activesquad != NULL)
	{
		string str = getactivity(activesquad->activity);
		set_activity_color(activesquad->activity.type);
		if (activesquad->activity.type == ACTIVITY_NONE)
		{
			bool haveact = false, multipleact = false;
			for (int p = 0; p < 6; p++)
			{
				if (activesquad->squad[p] == NULL) continue;
				const string str2 = activesquad->squad[p]->getActivityString();
				set_activity_color(activesquad->squad[p]->activity.type);
				if (haveact&&str != str2) multipleact = true;
				str = str2, haveact = true;
			}
			if (multipleact)
			{
				str = CONST_ACTING_INDIVIDUALLY;
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
			}
		}
		mvaddstrAlt(0, 41, str);
	}
}

bool showSafehouseInfo(Location* this_location, Location* squad_location, const bool havecar, const int ticketprice) {

	bool show_safehouse_info = false;
	if (this_location == squad_location) {
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		addstrAlt(currentLocation);
		show_safehouse_info = true;
	}
	else if (this_location->renting >= 0) {
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		addstrAlt(safeHouse);
		show_safehouse_info = true;
	}
	else if (this_location->renting == RENTING_CCS) {
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(enemySafeHouse);
	}
	else if (this_location->closed) {
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(PARENTHESIS_CLOSED_DOWN);
	}
	else if (this_location->highsecurity) {
		set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
		addstrAlt(highSecurity);
	}
	else if (multipleCityMode && this_location->type == squad_location->city) {
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		addstrAlt(currentLocation);
	}
	else if (this_location->area != squad_location->area && !havecar) {
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		addstrAlt(needCar);
	}
	else if (this_location->type == SITE_TRAVEL) {
		if (ledger.get_funds() < ticketprice)
			set_color_easy(RED_ON_BLACK_BRIGHT);
		else
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
		addstrAlt(spaceParanthesisDollar + tostring(ticketprice) + CLOSE_PARENTHESIS);
	}
	return show_safehouse_info;
}
/* base - go forth to stop evil */
void stopevil()
{
	//int l = 0, p = 0;
	if (!activesquad) return;
	bool havecar = false;
	for (int p = 0; p < 6; p++) if (activesquad->squad[p]) if (activesquad->squad[p]->pref_carid != -1)
	{
		havecar = true;
		break;
	}
	Location* squad_location = location[activesquad->squad[0]->location];
	int page = 0, loc = -1;
	// Start at the city level, rather than the absolute top
	if (multipleCityMode) {
		for (int l = 0; l < len(location); l++) {
			if (location[l]->type == squad_location->city) {
				loc = l;
				break;
			}
		}
	}
	vector<long> temploc;
	// 1. LCS safe houses
	for (int l = 0; l < len(location); l++)
		if (location[l]->parent == loc && location[l]->renting >= 0 && !location[l]->hidden)
			temploc.push_back(l);
	// 2. CCS safe houses
	for (int l = 0; l < len(location); l++)
		if (location[l]->parent == loc && location[l]->renting == RENTING_CCS && !location[l]->hidden)
			temploc.push_back(l);
	// 3. Other sites
	for (int l = 0; l < len(location); l++)
		if (location[l]->parent == loc && location[l]->renting == RENTING_NOCONTROL && !location[l]->hidden)
			temploc.push_back(l);
	// Determine cost of tickets for travel
	int ticketprice = 100 * activesquadSize();
	while (true)
	{
		music.play(MUSIC_STOPEVIL);
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(0, 0, CONST_WHERE_WILL_THE_SQUAD_GO);
		printparty();
		if (loc != -1)
		{
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(8, 0, location[loc]->getname(-1, true));
		}
		temploc.clear();
		for (int l = 0; l < len(location); l++)
			if (location[l]->parent == loc && location[l]->renting >= 0 && !location[l]->hidden)temploc.push_back(l);
		for (int l = 0; l < len(location); l++)
			if (location[l]->parent == loc && location[l]->renting == RENTING_CCS && !location[l]->hidden)temploc.push_back(l);
		for (int l = 0; l < len(location); l++)
			if (location[l]->parent == loc && location[l]->renting == RENTING_NOCONTROL && !location[l]->hidden)temploc.push_back(l);
		int y = 10;
		for (int p = page * 11; p != -1 && p < len(temploc) && p < page * 11 + 11; p++)
		{
			Location* this_location = location[temploc[p]];
			set_color_easy(WHITE_ON_BLACK);
			mvaddcharAlt(y, 0, y - 10 + 'A');
			addstrAlt(spaceDashSpace);
			addstrAlt(location[temploc[p]]->getname());

			bool show_safehouse_info = showSafehouseInfo(this_location, squad_location, havecar, ticketprice);

			if (this_location->siege.siege > 0) {
				set_color_easy(RED_ON_BLACK);
				addstrAlt(underSiege);
			}
			if (show_safehouse_info)
			{
				this_location->update_heat_protection();
				set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(y, 54, heatLevel);
				if (this_location->heat > this_location->heat_protection)
					set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				else set_color_easy(BLACK_ON_BLACK_BRIGHT);
				addstrAlt(this_location->heat);
				addstrAlt(percentSign);
				set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(y, 66, secrecyLevel);
				if (this_location->heat > this_location->heat_protection)
					set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				else set_color_easy(BLACK_ON_BLACK_BRIGHT);
				addstrAlt(this_location->heat_protection);
				addstrAlt(percentSign);
			}
			if (multipleCityMode && this_location->city == this_location->type)
			{
				set_color_easy(BLACK_ON_BLACK_BRIGHT);
				mvaddstrAlt(y, 50, this_location->city_description());
			}
			y++;
		}
		if (multipleCityMode && loc != -1 && LocationsPool::getInstance().getLocationType(loc) == location[loc]->city)
		{
			set_color_easy(WHITE_ON_BLACK);
			mvaddcharAlt(y + 1, 0, y - 10 + 'A');
			addstrAlt(travelDifCity);
			if (!havecar) {
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				addstrAlt(needCar);
			}
			else {
				if (ledger.get_funds() < ticketprice)
					set_color_easy(RED_ON_BLACK_BRIGHT);
				else set_color_easy(GREEN_ON_BLACK_BRIGHT);
				addstrAlt(spaceParanthesisDollar + tostring(ticketprice) + CLOSE_PARENTHESIS);
			}
			temploc.push_back(-1);
		}
		set_color_easy(WHITE_ON_BLACK);
		//PAGE UP
		if (page > 0)
		{
			mvaddstrAlt(10, 60, addprevpagestr());
		}
		//PAGE DOWN
		if ((page + 1) * 11 < len(temploc))
		{
			mvaddstrAlt(20, 60, addnextpagestr());
		}
		set_color_easy(WHITE_ON_BLACK);
		if ((loc == -1) || (multipleCityMode && LocationsPool::getInstance().getLocationType(loc) == squad_location->city)) mvaddstrAlt(24, 1, CONST_ENTER_THE_SQUAD_IS_NOT_YET_LIBERAL_ENOUGH);
		else mvaddstrAlt(24, 1, CONST_ENTER_BACK_ONE_STEP);
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 11 < len(temploc)) page++;
		if (c >= 'a'&&c <= 'k')
		{
			int sq = page * 11 + c - 'a';
			if (sq < len(temploc) && sq >= 0)
			{
				int oldloc = loc;
				loc = temploc[sq];
				if ((loc == -1 || (multipleCityMode && location[loc]->city != squad_location->city)) && !havecar)
					loc = oldloc;
				int subcount = 0;
				for (int l = 0; l < len(location); l++)
					if (location[l]->parent == loc)
						subcount++;
				if (subcount == 0 || (multipleCityMode && loc >= 0 && location[loc]->city != squad_location->city))
				{
					if (!location[loc]->closed &&
						((location[loc]->area == squad_location->area&&location[loc]->city == squad_location->city) || havecar))
					{
						activesquad->activity.type = ACTIVITY_VISIT;
						activesquad->activity.arg = loc;
						return;
					}
					else loc = oldloc;
				}
			}
		}
		/*if(c=='z')
		{
		activesquad->stance++;
		if(activesquad->stance>SQUADSTANCE_STANDARD)
		activesquad->stance=0;
		}*/
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR)
		{
			if (loc != -1 && (location[loc]->city != LocationsPool::getInstance().getLocationType(loc) || location[loc]->city != squad_location->city))
				loc = location[loc]->parent;
			else
			{
				activesquad->activity.type = ACTIVITY_NONE; // Clear squad activity
				break;
			}
		}
	}
}
vector<string> caseBUSINESSFRONT_INSURANCE;
vector<string> caseBUSINESSFRONT_TEMPAGENCY;
vector<string> caseBUSINESSFRONT_RESTAURANT;
vector<string> caseBUSINESSFRONT_MISCELLANEOUS;
vector<file_and_text_collection> locationspool_text_file_collection = {
	customText(&caseBUSINESSFRONT_INSURANCE, MOSTLY_ENDINGS_FOLDER + CONST_CASEBUSINESSFRONT_INSURANCE_TXT),
	customText(&caseBUSINESSFRONT_TEMPAGENCY, MOSTLY_ENDINGS_FOLDER + CONST_CASEBUSINESSFRONT_TEMPAGENCY_TXT),
	customText(&caseBUSINESSFRONT_RESTAURANT, MOSTLY_ENDINGS_FOLDER + CONST_CASEBUSINESSFRONT_RESTAURANT_TXT),
	customText(&caseBUSINESSFRONT_MISCELLANEOUS, MOSTLY_ENDINGS_FOLDER + CONST_CASEBUSINESSFRONT_MISCELLANEOUS_TXT),
};
/* base - invest in this location */
void investlocation()
{
	int loc = selectedsiege;
	while (true)
	{
		eraseAlt();
		locheader();
		printlocation(loc);
		if (LocationsPool::getInstance().canBeFortified(loc))
		{
			if (ledger.get_funds() >= 2000) set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(BLACK_ON_BLACK_BRIGHT);
			if (LocationsPool::getInstance().getLocationType(loc) == SITE_OUTDOOR_BUNKER)
				mvaddstrAlt(8, 1, CONST_W_REPAIR_THE_BUNKER_FORTIFICATIONS_2000);
			else if (LocationsPool::getInstance().getLocationType(loc) == SITE_RESIDENTIAL_BOMBSHELTER)
				mvaddstrAlt(8, 1, CONST_W_FORTIFY_THE_BOMB_SHELTER_ENTRANCES_2000);
			else
				mvaddstrAlt(8, 1, CONST_W_FORTIFY_THE_COMPOUND_FOR_A_SIEGE_2000);
		}
		if (!(LocationsPool::getInstance().get_specific_integer(INT_GETCOMPOUNDWALLS,loc) & COMPOUND_CAMERAS))
		{
			if (ledger.get_funds() >= 2000) set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(BLACK_ON_BLACK_BRIGHT);
			mvaddstrAlt(9, 1, CONST_C_PLACE_SECURITY_CAMERAS_AROUND_THE_COMPOUND_2000);
		}
		if (location[loc]->can_be_trapped())
		{
			if (ledger.get_funds() >= 3000) set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(BLACK_ON_BLACK_BRIGHT);
			mvaddstrAlt(10, 1, CONST_B_PLACE_BOOBY_TRAPS_THROUGHOUT_THE_COMPOUND_3000);
		}
		if (location[loc]->can_install_tanktraps())
		{
			if (ledger.get_funds() >= 3000) set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(BLACK_ON_BLACK_BRIGHT);
			mvaddstrAlt(11, 1, CONST_T_RING_THE_COMPOUND_WITH_TANK_TRAPS_3000);
		}
		if (!(location[loc]->compound_walls & COMPOUND_GENERATOR))
		{
			if (ledger.get_funds() >= 3000) set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(BLACK_ON_BLACK_BRIGHT);
			mvaddstrAlt(12, 1, CONST_G_BUY_A_GENERATOR_FOR_EMERGENCY_ELECTRICITY_3000);
		}
		if (!(location[loc]->compound_walls & COMPOUND_AAGUN))
		{
			if (lawList[LAW_GUNCONTROL] == ALIGN_ARCHCONSERVATIVE)
			{
				if (ledger.get_funds() >= 35000) set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(13, 1, CONST_A_INSTALL_A_PERFECTLY_LEGAL_ANTI_AIRCRAFT_GUN_ON_THE_ROOF_35_000);
			}
			else
			{
				if (ledger.get_funds() >= 200000) set_color_easy(WHITE_ON_BLACK);
				else set_color_easy(BLACK_ON_BLACK_BRIGHT);
				mvaddstrAlt(13, 1, CONST_A_INSTALL_AND_CONCEAL_AN_ILLEGAL_ANTI_AIRCRAFT_GUN_ON_THE_ROOF_200_000);
			}
		}
		if (!(location[loc]->compound_walls & COMPOUND_PRINTINGPRESS))
		{
			if (ledger.get_funds() >= 3000) set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(BLACK_ON_BLACK_BRIGHT);
			mvaddstrAlt(14, 1, CONST_P_BUY_A_PRINTING_PRESS_TO_START_YOUR_OWN_NEWSPAPER_3000);
		}
		if (location[loc]->can_have_businessfront())
		{
			if (ledger.get_funds() >= 3000) set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(BLACK_ON_BLACK_BRIGHT);
			mvaddstrAlt(15, 1, CONST_F_SETUP_A_BUSINESS_FRONT_TO_WARD_OFF_SUSPICION_3000);
		}
		if (ledger.get_funds() >= 150) set_color_easy(WHITE_ON_BLACK);
		else set_color_easy(BLACK_ON_BLACK_BRIGHT);
		mvaddstrAlt(16, 1, CONST_R_STOCKPILE_20_DAILY_RATIONS_OF_FOOD_150);
		mvaddstrAlt(17, 1, enter_done);
		int c = getkeyAlt();
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
		if (c == 'w')
		{
			if (location[loc]->can_be_fortified() && ledger.get_funds() >= 2000)
			{
				ledger.subtract_funds(2000, EXPENSE_COMPOUND);
				location[loc]->compound_walls |= COMPOUND_BASIC;
			}
		}
		if (c == 'c')
		{
			if (!(LocationsPool::getInstance().get_specific_integer(INT_GETCOMPOUNDWALLS,loc) & COMPOUND_CAMERAS) && ledger.get_funds() >= 2000)
			{
				ledger.subtract_funds(2000, EXPENSE_COMPOUND);
				location[loc]->compound_walls |= COMPOUND_CAMERAS;
			}
		}
		if (c == 'b')
		{
			if (location[loc]->can_be_trapped() && ledger.get_funds() >= 3000)
			{
				ledger.subtract_funds(3000, EXPENSE_COMPOUND);
				location[loc]->compound_walls |= COMPOUND_TRAPS;
			}
		}
		if (c == 't')
		{
			if (location[loc]->can_install_tanktraps() && ledger.get_funds() >= 3000)
			{
				ledger.subtract_funds(3000, EXPENSE_COMPOUND);
				location[loc]->compound_walls |= COMPOUND_TANKTRAPS;
			}
		}
		if (c == 'g')
		{
			if (!(LocationsPool::getInstance().get_specific_integer(INT_GETCOMPOUNDWALLS,loc) & COMPOUND_GENERATOR) && ledger.get_funds() >= 3000)
			{
				ledger.subtract_funds(3000, EXPENSE_COMPOUND);
				location[loc]->compound_walls |= COMPOUND_GENERATOR;
			}
		}
		if (c == 'a')
		{
			int aagunPrice = 200000;
			if (lawList[LAW_GUNCONTROL] == ALIGN_ARCHCONSERVATIVE)
				aagunPrice = 35000;
			if (!(location[loc]->compound_walls & COMPOUND_AAGUN) && ledger.get_funds() >= aagunPrice)
			{
				ledger.subtract_funds(aagunPrice, EXPENSE_COMPOUND);
				location[loc]->compound_walls |= COMPOUND_AAGUN;
			}
		}
		if (c == 'p')
		{
			if (!(LocationsPool::getInstance().get_specific_integer(INT_GETCOMPOUNDWALLS,loc) & COMPOUND_PRINTINGPRESS) && ledger.get_funds() >= 3000)
			{
				ledger.subtract_funds(3000, EXPENSE_COMPOUND);
				location[loc]->compound_walls |= COMPOUND_PRINTINGPRESS;
			}
		}
		if (c == 'r')
		{
			if (ledger.get_funds() >= 150)
			{
				ledger.subtract_funds(150, EXPENSE_COMPOUND);
				location[loc]->compound_stores += 20;
			}
		}
		if (c == 'f')
		{
			if (location[loc]->can_have_businessfront() && ledger.get_funds() >= 3000)
			{
				ledger.subtract_funds(3000, EXPENSE_COMPOUND);
				do
				{
					location[loc]->front_business = LCSrandom(BUSINESSFRONTNUM);
					strcpy(location[loc]->front_name, lastname(true));
					strcat(location[loc]->front_name, singleSpace);
					int selection;
					switch (location[loc]->front_business)
					{
					case BUSINESSFRONT_INSURANCE:
						selection = LCSrandom(len(caseBUSINESSFRONT_INSURANCE) / 2);
						strcat(location[loc]->front_name, caseBUSINESSFRONT_INSURANCE[selection * 2]);
						strcpy(location[loc]->front_shortname, caseBUSINESSFRONT_INSURANCE[selection * 2 + 1]);
						break;
					case BUSINESSFRONT_TEMPAGENCY:
						selection = LCSrandom(len(caseBUSINESSFRONT_TEMPAGENCY) / 2);
						strcat(location[loc]->front_name, caseBUSINESSFRONT_TEMPAGENCY[selection * 2]);
						strcpy(location[loc]->front_shortname, caseBUSINESSFRONT_TEMPAGENCY[selection * 2 + 1]);
						break;
					case BUSINESSFRONT_RESTAURANT:
						selection = LCSrandom(len(caseBUSINESSFRONT_RESTAURANT) / 2);
						strcat(location[loc]->front_name, caseBUSINESSFRONT_RESTAURANT[selection * 2]);
						strcpy(location[loc]->front_shortname, caseBUSINESSFRONT_RESTAURANT[selection * 2 + 1]);
						break;
					case BUSINESSFRONT_MISCELLANEOUS:
						selection = LCSrandom(len(caseBUSINESSFRONT_MISCELLANEOUS) / 2);
						strcat(location[loc]->front_name, caseBUSINESSFRONT_MISCELLANEOUS[selection * 2]);
						strcpy(location[loc]->front_shortname, caseBUSINESSFRONT_MISCELLANEOUS[selection * 2 + 1]);
						break;
					}
				} while (location[loc]->duplicatelocation());
			}
		}
	}
}
void makeIntoHostage(DeprecatedCreature* newcr) {
	newcr->namecreature();
	newcr->location = activesquad->squad[0]->base;
	newcr->base = activesquad->squad[0]->base;
	newcr->flag |= CREATUREFLAG_MISSING;
	//disarm them and stash their weapon back at the base
	newcr->drop_weapons_and_clips(&(location[newcr->location]->loot));
	//Create InterrogationST data
	newcr->activity.intr() = new InterrogationST;
}
/* names the new hostage and stashes them in your base */
void kidnaptransfer(DeprecatedCreature &cr)
{
	DeprecatedCreature* newcr = new DeprecatedCreature;
	*newcr = cr;
	makeIntoHostage(newcr);
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_THE_EDUCATION_OF);
	addstrAlt(newcr->propername);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(2, 0, CONST_X_WHAT_NAME_WILL_YOU_USE_FOR_THIS_);
	addstrAlt(newcr->get_type_name());
	addstrAlt(CONST_X_IN_ITS_PRESENCE);
	mvaddstrAlt(3, 0, CONST_X_IF_YOU_DO_NOT_ENTER_ANYTHING_THEIR_REAL_NAME_WILL_BE_USED);
	newcr->new_name_four();
	addCreature(newcr);
	stat_kidnappings++;
}
/* transfer all loot from some source (such as a squad or another location) to a location, and deal with money properly */
void Location::getloot(vector<Item *>& loot)
{
	for (int l = len(loot) - 1; l >= 0; l--)
		if (loot[l]->whatIsThis() == THIS_IS_MONEY)
		{
			Money* m = static_cast<Money*>(loot[l]); //cast -XML
			ledger.add_funds(m->get_amount(), INCOME_THIEVERY);
			delete loot[l];
		}
		else
		{  // Empty squad inventory into base inventory
			this->loot.push_back(loot[l]);
		}
	loot.clear();
}
void clearRentExemptions() {
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++) location[l]->newrental = 0;
}
void publishSpecialEditions(char &clearformess) {
	//YOUR PAPER AND PUBLIC OPINION AND STUFF
	vector<int> nploc;
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++)
	{
		if ((location[l]->compound_walls & COMPOUND_PRINTINGPRESS) &&
			!location[l]->siege.siege&&
			location[l]->renting != RENTING_CCS) nploc.push_back(l);
	}
	if (len(nploc))
	{
		//DO SPECIAL EDITIONS
		int loottypeindex = choosespecialedition(clearformess);
		if (loottypeindex != -1)
		{
			printnews(loottypeindex, len(nploc));
			if (LootTypePool::getInstance().getIdName(loottypeindex) == tag_LOOT_INTHQDISK || //For special edition xml file? -XML
				LootTypePool::getInstance().getIdName(loottypeindex) == tag_LOOT_SECRETDOCUMENTS)
			{
				for (int l = 0; l < len(nploc); l++)
					criminalizepool(LAWFLAG_TREASON, -1, nploc[l]);
			}
		}
	}
}
void manageGrafiti() {
	//Manage graffiti
	for (int l = 0; l < LocationsPool::getInstance().lenpool(); l++) // Check each location
	{
		for (int c = len(location[l]->changes) - 1; c >= 0; c--) // Each change to the map
		{
			if (location[l]->changes[c].flag == SITEBLOCK_GRAFFITI ||
				location[l]->changes[c].flag == SITEBLOCK_GRAFFITI_CCS ||
				location[l]->changes[c].flag == SITEBLOCK_GRAFFITI_OTHER) // Find changes that refer specifically to graffiti
			{
				int power = 0, align = 0;
				if (location[l]->changes[c].flag == SITEBLOCK_GRAFFITI) align = 1;
				if (location[l]->changes[c].flag == SITEBLOCK_GRAFFITI_CCS) align = -1;
				//Purge graffiti from more secure sites (or from non-secure
				//sites about once every five years), but these will
				//influence people more for the current month
				if (securityable(LocationsPool::getInstance().getLocationType(l)))
				{
					location[l]->changes.erase(location[l]->changes.begin() + c);
					power = 5;
				}
				else
				{
					if (location[l]->renting == RENTING_CCS)
						location[l]->changes[c].flag = SITEBLOCK_GRAFFITI_CCS; // Convert to CCS tags
					else if (location[l]->renting == RENTING_PERMANENT)
						location[l]->changes[c].flag = SITEBLOCK_GRAFFITI; // Convert to LCS tags
					else
					{
						power = 1;
						if (!LCSrandom(10))
							location[l]->changes[c].flag = SITEBLOCK_GRAFFITI_OTHER; // Convert to other tags
						if (!LCSrandom(10) && endgamestate < ENDGAME_CCS_DEFEATED&&endgamestate>0)
							location[l]->changes[c].flag = SITEBLOCK_GRAFFITI_CCS; // Convert to CCS tags
						if (!LCSrandom(30))
							location[l]->changes.erase(location[l]->changes.begin() + c); // Clean up
					}
				}
				if (align == 1)
				{
					background_liberal_influence[VIEW_LIBERALCRIMESQUAD] += power;
					background_liberal_influence[VIEW_CONSERVATIVECRIMESQUAD] += power;
				}
				else if (align == -1)
				{
					background_liberal_influence[VIEW_LIBERALCRIMESQUAD] -= power;
					background_liberal_influence[VIEW_CONSERVATIVECRIMESQUAD] -= power;
				}
			}
		}
	}
}
char getseigedFromLocation(int secondaryLocation) {
	siegest* siege = NULL;
	int primaryLocation = activesquad ? activesquad->squad[0]->location : -1;
	if (primaryLocation != -1) {
		siege = &location[primaryLocation]->siege;
	}
	else if (secondaryLocation != -1) {
		siege = &location[secondaryLocation]->siege;
	}
	if (siege == NULL) {
		return 0;
	}
	else {
	return siege->siege;
	}
}

void createTempSquadWithJustThisLiberal(DeprecatedCreature *cr, int cursquadid) {
	//create a temp squad containing just this liberal
	int oldsquadid = cr->squadid;
	Deprecatedsquadst *oldactivesquad = activesquad;
	activesquad = new Deprecatedsquadst;
	strcpy(activesquad->name, CONST_TEMPORARY_SQUAD);
	activesquad->id = cursquadid;
	activesquad->squad[0] = cr;
	cr->squadid = activesquad->id;
	//go to equipment screen
	equip(location[activesquad->squad[0]->location]->loot, -1);
	//once you're done, restore original squad status.
	delete activesquad;
	activesquad = oldactivesquad;
	cr->squadid = oldsquadid;
}

void moveEverythingAwayFromSite(int cursite) {
	location[cursite]->renting = RENTING_NOCONTROL;
	//MOVE ALL ITEMS AND SQUAD MEMBERS
	const int hs = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, cursite);
	CreaturePool::getInstance().moveEverythingFrom(cursite, hs);
	location[hs]->getloot(location[cursite]->loot);
	location[cursite]->compound_walls = 0;
	location[cursite]->compound_stores = 0;
	location[cursite]->front_business = -1;
}
void LocationsPool::addSiegeKill(int cursite) {
	location[cursite]->siege.kills++;
}
void LocationsPool::removeTank(int cursite) {
	location[cursite]->siege.tanks--;
}
void addLocationChange(int cursite, sitechangest change) {
	location[cursite]->changes.push_back(change);
}
const int LocationsPool::getHeat(int cursite) const {
	return location[cursite]->heat;
}
void LocationsPool::setSiegetimeuntillocated(int cursite, int timer) {
	location[cursite]->siege.timeuntillocated = timer;
}

void LocationsPool::clearHeat(int cursite) {
	location[cursite]->heat = 0;
}
void setColorBasedOnSiege(const int cursite, const int y, const bool p) {
	Location *loc = location[cursite];
	siegest *siege = &loc->siege;
	if (siege ? siege->siege : false) set_color_easy(siege->underattack ? p ? RED_ON_BLACK_BRIGHT : RED_ON_BLACK : p ? YELLOW_ON_BLACK_BRIGHT : YELLOW_ON_BLACK);
	mvaddstrAlt(y, 31, location[cursite]->getname(true, true));
}

int consolidateSiegeLoot() {
	int k = 0;
	for (int l = 0; l < len(location); l++)
	{
		consolidateloot(location[l]->loot);
		if (!location[l]->siege.siege)
			k += len(location[l]->loot); // Review and Move Equipment
	}
	return k;
}

void nukeAllEmptySquads(const vector<int> squadloc, const int mode) {
	//NUKE ALL EMPTY SQUADS
	for (int sq = len(squad) - 1; sq >= 0; sq--)
	{
		bool hasmembers = false;
		for (int p = 0; p < 6; p++)
			if (squad[sq]->squad[p] != NULL)
			{
				hasmembers = true; break;
			}
		// in the event a new squad is created squadloc[] will be one shorter than squad[]
		// But since a new squad cannot be created without members, this should
		// not ever break
		if (!hasmembers && mode == GAMEMODE_BASE)
		{
			if (squadloc[sq] != -1)
				location[squadloc[sq]]->getloot(squad[sq]->loot);
			if (activesquad == squad[sq])activesquad = NULL;
			delete_and_remove(squad, sq);
		}
	}
}

void consolidateLoot(const int l) {
	consolidateloot(location[l]->loot);
}
int LocationsPool::lenloot(const int l)const {
	return len(location[l]->loot);
}
string getLootTitle(const int base, const int l) {
	return location[base]->loot[l]->equip_title();
}

int getLootNumber(const int base, const int l) {
	return location[base]->loot[l]->get_number();
}

void LocationsPool::captureSite(int cursite) {
	location[cursite]->renting = RENTING_PERMANENT; // Capture safehouse for the glory of the LCS!
	location[cursite]->closed = 0;
	location[cursite]->heat = 100;
}

void LocationsPool::closeSite(int cursite, int sitecrime) {
	location[cursite]->closed = sitecrime / 10; // Close down site
}
bool LocationsPool::siteHasCameras(int cursite)const {
	return (location[cursite]->compound_walls & COMPOUND_CAMERAS) && !location[cursite]->siege.cameras_off;
}
void getRandomLoot(int cursite) {
	int b = LCSrandom(len(location[cursite]->loot));
	Item *it = location[cursite]->loot[b];
	giveActiveSquadThisLoot(it);
	location[cursite]->loot.erase(location[cursite]->loot.begin() + b);
}

char LocationsPool::isThisUnderAttack(int cursite)const {
	return location[cursite]->siege.underattack;
}

void LocationsPool::setRenting(int cursite, int renting) {
	location[cursite]->renting = renting;
}

char LocationsPool::isThisAFront(int cursite)const {
	return location[cursite]->front_business;
}
string LocationsPool::getFrontName(int cursite)const {
	return location[cursite]->front_name;
}

void LocationsPool::tickAttackTime(int cursite) {
	location[cursite]->siege.attacktime++;
}
int LocationsPool::getAttackTime(int cursite)const {
	return location[cursite]->siege.attacktime;
}
void LocationsPool::resetAttackTime(int cursite) {
	location[cursite]->siege.attacktime = 0;
}
int LocationsPool::doWeHaveTankTraps(int cursite)const {
	return (location[cursite]->compound_walls&COMPOUND_TANKTRAPS);
}
void LocationsPool::deleteTankTraps(int l) {
	location[l]->compound_walls &= ~COMPOUND_TANKTRAPS;
}
void LocationsPool::spawnATank(int cursite) {
	location[cursite]->siege.tanks++;
}

void LocationsPool::spawnATank(int cursite, int num) {
	location[cursite]->siege.tanks = num;
}

int LocationsPool::getSiegeKills(int cursite)const {
	return location[cursite]->siege.kills;
}
int LocationsPool::getSiegeTanks(int cursite)const {
	return location[cursite]->siege.tanks;
}

void LocationsPool::turnOffSiege(int loc) {
	location[loc]->siege.attacktime = 0;
	location[loc]->siege.kills = 0;
	location[loc]->siege.tanks = 0;
}

bool LocationsPool::hasTraps(int loc)const {
	return location[loc]->compound_walls&COMPOUND_TRAPS;
}

bool LocationsPool::lightsOff(int loc) const {
	return location[loc]->siege.lights_off;
}
int armor_makedifficulty(Armor& type, DeprecatedCreature *cr);
/* armor repair */
#include "log/log.h"
extern Log gamelog;
void repairarmor(DeprecatedCreature &cr, char &clearformess)
{
	Armor *armor = NULL;
	Item *pile = NULL;
	vector<Item *> *pilelist = NULL;
	int pileindex = 0;

	// Clean yourself up first
	if (cr.get_armor().is_bloody() || cr.get_armor().is_damaged())
		armor = &cr.get_armor();
	else if (cr.squadid != -1)
	{
		int sq = getsquad(cr.squadid);
		for (int l = 0; l < len(squad[sq]->loot); l++)
			if (squad[sq]->loot[l]->whatIsThis() == THIS_IS_ARMOR)
			{
				Armor* a = static_cast<Armor*>(squad[sq]->loot[l]); //cast -XML
				if (a->is_bloody() || a->is_damaged())
				{
					armor = a;
					pile = squad[sq]->loot[l];
					pileindex = l;
					pilelist = &squad[sq]->loot;
					break;
				}
			}
	}
	// Multiple passes, to find the best item to work on
	bool dothis = false;
	for (int passnum = 0; passnum < 3 && !dothis; passnum++)
		if (armor == NULL && cr.location != -1)
			for (int l = 0; l < len(location[cr.location]->loot); l++)
				if (location[cr.location]->loot[l]->whatIsThis() == THIS_IS_ARMOR)
				{
					Armor* a = static_cast<Armor*>(location[cr.location]->loot[l]);//cast -XML
					switch (passnum)
					{
					case 0: // Guaranteed to accomplish something
						dothis = (a->is_bloody() && a->is_damaged());
						break;
					case 1: // Find something to clean if low skill, repair if high
						dothis = (a->is_bloody() && armor_makedifficulty(*a, &cr) > 4)
							|| (a->is_damaged() && armor_makedifficulty(*a, &cr) <= 4);
						break;
					case 2: // Anything that needs work
						dothis = (a->is_bloody() || a->is_damaged());
						break;
					}
					if (dothis)
					{
						armor = a;
						pile = location[cr.location]->loot[l];
						pileindex = l;
						pilelist = &location[cr.location]->loot;
						break;
					}
				}

	if (clearformess) eraseAlt();
	else makedelimiter();

	if (armor == NULL)
	{
		moveAlt(8, 1);
		addstrAlt(cr.name, gamelog);
		switch (LCSrandom(4))
		{
		case 0: addstrAlt(" tidies up the safehouse.", gamelog); break;
		case 1: addstrAlt(" reorganizes the armor closet.", gamelog); break;
		case 2: addstrAlt(" cleans the kitchen.", gamelog); break;
		case 3:
			addstrAlt(" peruses some sewing magazines.", gamelog);
			cr.train(SKILL_TAILORING, 1);
			break;
		}
		gamelog.nextMessage();
		pressAnyKey();
	}
	else
	{
		string armorname = armor->get_name();// Get name before we maybe destroy it
		bool repairfailed = false;
		bool qualityReduction = !LCSrandom(10);
		bool armorDestroyed = !armor->decrease_quality(0);

		if (armor->is_damaged())
		{
			long dif = armor_makedifficulty(*armor, &cr);
			dif >>= (armor->get_quality() - 1);  // it is easy to patch up rags
			cr.train(SKILL_TAILORING, dif / 2 + 1);

			if (LCSrandom(1 + dif / 2)) repairfailed = true;
		}
		else {
			repairfailed = true;
		}
		if (armorDestroyed)
			repairfailed = false;  // Its dead, Jim; stop trying to fix it
		if (repairfailed)
			qualityReduction = false; // Low skill repairers shredding your shirts seem too harsh

		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		moveAlt(8, 1);

		std::string result = "";
		result += cr.name;

		if (armorDestroyed)
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			result += " disposes of ";
		}
		else if (repairfailed && armor->is_bloody())
		{
			set_color_easy(CYAN_ON_BLACK_BRIGHT);
			result += " cleans ";
		}
		else if (repairfailed)
		{
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			result += " is working to repair ";
		}
		else
		{
			if (!qualityReduction)
			{
				set_color_easy(GREEN_ON_BLACK_BRIGHT);
				result += " repairs ";
			}
			else
			{
				armorDestroyed = !armor->decrease_quality(1);
				if (armorDestroyed)
				{
					set_color_easy(RED_ON_BLACK_BRIGHT);
					result += " finds there is no hope of repairing ";
				}
				else
				{
					set_color_easy(YELLOW_ON_BLACK_BRIGHT);
					result += " repairs what little can be fixed of ";
				}
			}
		}

		if (pile)
		{
			result += armor->aan();
		}
		else
			result += cr.hisher();

		if (armorDestroyed)
			result += " ruined";

		result += " " + armorname + ".";

		addstrAlt(result, gamelog);
		gamelog.nextMessage();

		if (pile)
		{
			if (pile->get_number() > 1)
			{
				Item *newpile = pile->split(pile->get_number() - 1);
				pilelist->push_back(newpile);
			}
		}

		armor->set_bloody(false);
		if (!repairfailed)
		{
			armor->set_damaged(false);
		}
		if (armorDestroyed)
		{
			if (!pile) // repairer was wearing it
			{
				cr.strip(NULL);
			}
			else // scrap from stockpile
			{
				delete_and_remove(*pilelist, pileindex);
			}
		}

		pressAnyKey();
	}
}
char tryFindCloth(int cursite) {
	for (int l = 0; l < len(location[cursite]->loot); l++) {
		if (location[cursite]->loot[l]->whatIsThis() == THIS_IS_LOOT &&
			(location[cursite]->loot[l])->is_cloth()) //cast -XML
		{
			if (location[cursite]->loot[l]->get_number() == 1)
				delete_and_remove(location[cursite]->loot, l);
			else location[cursite]->loot[l]->decrease_number(1);
			return 1;
		}
	}
	return 0;
}
void addLootToLoc(int loc, Item* it) {
	location[loc]->loot.push_back(it);
}
string gimmeASprayCan(DeprecatedCreature* graffiti) {
	for (int i = 0; i < LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, graffiti->base); i++)
	{
		if (location[graffiti->base]->loot[i]->whatIsThis() == THIS_IS_WEAPON)
		{
			Weapon *w = static_cast<Weapon*>(location[graffiti->base]->loot[i]); //cast -XML
			if (w->get_specific_bool(BOOL_CAN_GRAFFITI_))
			{
				string spray_name = w->get_name();
				graffiti->give_weapon(*w, &(location[graffiti->base]->loot));
				if (location[graffiti->base]->loot[i]->empty())
					delete_and_remove(location[graffiti->base]->loot, i);
				return spray_name;
			}
		}
	}
	return "";
}
void buyMeASprayCan(DeprecatedCreature* graffiti) {

	Weapon spray(*weapontype[getweapontype(tag_WEAPON_SPRAYCAN)]);
	graffiti->give_weapon(spray, &location[graffiti->base]->loot);
}
void lootTheBody(DeprecatedCreature &cr, int base) {
	//MAKE BASE LOOT
	cr.makeloot(location[base]->loot);
}

void DeprecatedCreature::makeloot(const int base) {
	lootTheBody(*this, base);
}
int countSafeHouses() {
	int safenumber = 0;
	for (int l = 0; l < len(location); l++) if (location[l]->is_lcs_safehouse()) safenumber++;
	return safenumber;
}
Location* getLocation() {
	Location* loc = NULL;
	if (selectedsiege != -1) loc = location[selectedsiege];
	if (activesquad) if (activesquad->squad[0]->location != -1)
		loc = location[activesquad->squad[0]->location];
	return loc;
}

bool isPartOfJusticeSystem(int cursite) {
	return location[cursite]->part_of_justice_system();
}
bool LocationsPool::canBeUpgraded(int cursite)const {
	return location[cursite]->can_be_upgraded();
}

void LocationsPool::clearunderattack(int cursite) {
	location[cursite]->siege.underattack = 0;
}
bool isThisSafehouse(int loc) {
	return location[loc]->is_lcs_safehouse();
}
void equipLoot(int l, int loc) {
	equip(location[l]->loot, loc);
}
void burnFlagAtLocation(int l) {
	location[l]->haveflag = 0;
}
void locationIsNowRented(int l, int rent) {
	location[l]->renting = rent;
	location[l]->newrental = 1;
}

int getCity(int l) {
	return location[l]->city;
}

int getFenceValueLocation(int l, int slot) {
	return location[l]->loot[slot]->get_fencevalue();
}

bool getCanBeSoldLocation(int l, int slot) {
	return location[l]->loot[slot]->is_good_for_sale();
}

int getLocationLootNumber(int l, int slot) {
	return location[l]->loot[slot]->get_number();
}

void decreateLocationLoot(int loc, int loot, int num) {
	location[loc]->loot[loot]->decrease_number(num);
	if (location[loc]->loot[loot]->empty())
		delete_and_remove(location[loc]->loot, loot);
}

int whatIsThisItemInLocation(int loc, int l) {
	return location[loc]->loot[l]->whatIsThis();
}

void deleteLocationLoot(int loc, int loot) {
	delete_and_remove(location[loc]->loot, loot);
}
void deleteLocationLoot(int loc) {
	delete_and_clear(location[loc]->loot);
}

bool noQuickFenceLocation(int loc, int l) {
	return location[loc]->loot[l]->no_quick_fencing();
}

void CCSCapturesSite(int loc) {
	location[loc]->renting = RENTING_CCS;
}

int LocationsPool::getStoresAmount(int l)const {
	return location[l]->compound_stores;
}

void endLocationSiege(int l) {
	location[l]->siege.siege = 0;
}

void reduceCompoundStores(int loc, int amount) {
	location[loc]->compound_stores -= amount;
}
void emptyCompoundStores(int l) {
	location[l]->compound_stores = 0;
}

bool hasPrintingPress(int l) {
	return location[l]->compound_walls&COMPOUND_PRINTINGPRESS;
}

void deletePrintingPress(int loc) {

	location[loc]->compound_walls &= ~COMPOUND_PRINTINGPRESS;
}

siegest getWholeSiege(int l) {
	return location[l]->siege;
}

void deleteBusinessFront(int l) {

	location[l]->front_business = -1;
}

void deleteCompoundWalls(int loc) {

	location[loc]->compound_walls = 0;
}

void dropHeatByFivePercent(int l) {
	location[l]->heat = static_cast<int>(location[l]->heat * 0.95);
}

int getTimeUntilSiege(int l) {
	return location[l]->siege.timeuntillocated;
}

void huntFasterIfSiteIncrediblyHot(int l) {
	if (location[l]->heat > 100)
	{
		int hunt_speed;
		hunt_speed = location[l]->heat / 50;
		while (hunt_speed&&location[l]->siege.timeuntillocated > 1)
		{
			location[l]->siege.timeuntillocated--;
			hunt_speed--;
		}
	}
}

void updateLocationHeatProtection(int l) {
	location[l]->update_heat_protection();
}

void letPlaceCoolOffUnlessCrime(int crimes, int l) {
	if (crimes < location[l]->heat)
	{
		location[l]->heat -= 1;
		if (location[l]->heat < 0)
			location[l]->heat = 0;
	}
	else
	{
		// Update location heat
		if (crimes > location[l]->heat) location[l]->heat += (crimes - location[l]->heat) / 10 + 1;
		// Begin planning siege if high heat on location
		if (location[l]->heat > location[l]->heat_protection &&
			LCSrandom(500) < location[l]->heat &&
			!(location[l]->siege.timeuntillocated >= 0)) //Do not re-plan siege.
		{
			// Set time until siege is carried out
			location[l]->siege.timeuntillocated += 2 + LCSrandom(6);
		}
	}
}

void policeSiege(int l) {

	location[l]->siege.siege = 1;
	location[l]->siege.siegetype = SIEGE_POLICE;
	location[l]->siege.lights_off = 0;
	location[l]->siege.cameras_off = 0;
}
void corporateSiege(int l) {
	location[l]->siege.siege = 1;
	location[l]->siege.siegetype = SIEGE_CORPORATE;
	location[l]->siege.underattack = 1;
	location[l]->siege.lights_off = 0;
	location[l]->siege.cameras_off = 0;
}

void CCSSiege(int l) {
	location[l]->siege.siege = 1;
	location[l]->siege.siegetype = SIEGE_CCS;
	location[l]->siege.underattack = 1;
	location[l]->siege.lights_off = 0;
	location[l]->siege.cameras_off = 0;
}

void CIASiege(int l) {
	location[l]->siege.siege = 1;
	location[l]->siege.siegetype = SIEGE_CIA;
	location[l]->siege.underattack = 1;
	location[l]->siege.lights_off = 1;
	location[l]->siege.cameras_off = 1;
}

void hicksSiege(int l) {
	location[l]->siege.siege = 1;
	location[l]->siege.siegetype = SIEGE_HICKS;
	location[l]->siege.underattack = 1;
	location[l]->siege.lights_off = 0;
	location[l]->siege.cameras_off = 0;
}

void firemanSiege(int l) {
	location[l]->siege.siege = 1;
	location[l]->siege.siegetype = SIEGE_FIREMEN;
	location[l]->siege.underattack = 1;
	location[l]->siege.lights_off = 0;
	location[l]->siege.cameras_off = 0;

}

void escalateSite(int l) {
	location[l]->siege.timeuntillocated = LCSrandom(4) + 4;
	location[l]->siege.escalationstate++;
}

void dumpLootAtLocation(int homes, vector<Item *>& loot) {
	location[homes]->getloot(loot);
}

void deleteGeneratorLightsOff(int l) {

	location[l]->compound_walls &= ~COMPOUND_GENERATOR;
	location[l]->siege.lights_off = 1;
}

int LocationsPool::getTimeUntilSiege(int loc, int type)const {
	switch (type) {
	case SIEGE_POLICE:
	//case INT_GETTIMEUNTILSIEGE_POLICE:
		return location[loc]->siege.timeuntillocated;
		break;
	case SIEGE_CIA:
	//case INT_GETTIMEUNTILSIEGE_CIA:
		return location[loc]->siege.timeuntilcia;
		break;
	case SIEGE_CORPORATE:
	//case INT_GETTIMEUNTILSIEGE_CORPORATE:
		return location[loc]->siege.timeuntilcorps;
		break;
	case SIEGE_CCS:
	//case INT_GETTIMEUNTILSIEGE_CCS:
		return location[loc]->siege.timeuntilccs;
		break;
	case SIEGE_FIREMEN:
	//case INT_GETTIMEUNTILSIEGE_FIREMEN:
		return location[loc]->siege.timeuntilfiremen;
		break;
	default:
	case SIEGE_ORG:
	//case INT_GETTIMEUNTILSIEGE_ORG:
	case SIEGE_HICKS:
	//case INT_GETTIMEUNTILSIEGE_HICKS:
	case SIEGENUM:
		return 0;
		break;

	}
}

void LocationsPool::setTimeUntilSiege(int loc, int type, int time) {
	switch (type) {
	case SIEGE_POLICE:
		location[loc]->siege.timeuntillocated = time;
		break;
	case SIEGE_CIA:
		location[loc]->siege.timeuntilcia = time;
		break;
	case SIEGE_CORPORATE:
		location[loc]->siege.timeuntilcorps = time;
		break;
	case SIEGE_CCS:
		location[loc]->siege.timeuntilccs = time;
		break;
	case SIEGE_FIREMEN:
		location[loc]->siege.timeuntilfiremen = time;
		break;
	default:
	case SIEGE_ORG:
	case SIEGE_HICKS:
	case SIEGENUM:
		;
		break;
	}
}

bool hasBusinessFront(int l) {
	return location[l]->front_business != -1;
}

bool hasAGenerator(int l) {
	return location[l]->compound_walls & COMPOUND_GENERATOR;
}

bool hasCameras(int l) {
	return location[l]->compound_walls & COMPOUND_CAMERAS;
}

void deleteAAGun(int l) {
	location[l]->compound_walls &= ~COMPOUND_AAGUN;
}

bool siteHasAAGun(int l) {
	return location[l]->compound_walls & COMPOUND_AAGUN;
}

void setUnderAttack(int l) {

	location[l]->siege.underattack = 1;
}

bool getLightsOff(int l) {
	return location[l]->siege.lights_off;
}

void setLightsOff(int l) {

	location[l]->siege.lights_off = 1;
}

bool hasBasicCompoundWalls(int l) {
	return location[l]->compound_walls & COMPOUND_BASIC;
}

const int LocationsPool::get_specific_integer(const locationsPoolIntegers lPI, const int cursite) const {
	switch (lPI) {
	case INT_GETSTORESAMOUNT: return getStoresAmount(cursite); break;
	case INT_GETRENTINGTYPE: return getRentingType(cursite); break;
	case INT_ISTHISPLACEHIGHSECURITY: return isThisPlaceHighSecurity(cursite); break;
	case INT_GETLOCATIONCITY: return getLocationCity(cursite); break;

	//case INT_GETTIMEUNTILSIEGE_POLICE: 
	//case INT_GETTIMEUNTILSIEGE_CIA: 
	//case INT_GETTIMEUNTILSIEGE_CORPORATE: 
	//case INT_GETTIMEUNTILSIEGE_CCS: 
	//case INT_GETTIMEUNTILSIEGE_FIREMEN: 
	//case INT_GETTIMEUNTILSIEGE_ORG: 
	//case INT_GETTIMEUNTILSIEGE_HICKS: 
	//	return getTimeUntilSiege(cursite, lPI); break;

	case INT_GETCOMPOUNDWALLS: return getCompoundWalls(cursite); break;
	case INT_ISTHISSITECLOSED: return isThisSiteClosed(cursite); break;
	case INT_GETLOCATIONPARENT: return getLocationParent(cursite); break;
	case INT_GETATTACKTIME: return getAttackTime(cursite); break;
	case INT_DOWEHAVETANKTRAPS: return doWeHaveTankTraps(cursite); break;
	case INT_GETSIEGEKILLS: return getSiegeKills(cursite); break;
	case INT_GETSIEGETANKS: return getSiegeTanks(cursite); break;
	case INT_GETHEAT: return getHeat(cursite); break;
	case INT_LENLOOT: return lenloot(cursite); break;

	default: //ERROR
		return -1;
	}
}