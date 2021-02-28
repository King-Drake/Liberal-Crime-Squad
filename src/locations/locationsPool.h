#include "../items/itemPool.h"
enum locationsPoolBooleans {
	BOOL_CANBEUPGRADED,
	BOOL_ISNEWRENTAL,
	BOOL_CANBEFORTIFIED,
	BOOL_SITEHASCAMERAS,
	BOOL_HASTRAPS,
	BOOL_LIGHTSOFF,
	BOOL_ISLOCATIONMAPPED,
	BOOL_ISLOCATIONHIDDEN,
};
enum locationsPoolIntegers {
	INT_GETSTORESAMOUNT,
	INT_GETRENTINGTYPE,
	INT_ISTHISPLACEHIGHSECURITY,
	INT_GETLOCATIONCITY,
	

	INT_GETCOMPOUNDWALLS,
	INT_ISTHISSITECLOSED,
	INT_GETLOCATIONPARENT,
	INT_GETATTACKTIME,
	INT_DOWEHAVETANKTRAPS,
	INT_GETSIEGEKILLS,
	INT_GETSIEGETANKS,
	INT_GETHEAT,
	INT_LENLOOT,

	//INT_GETTIMEUNTILSIEGE_POLICE,
	//INT_GETTIMEUNTILSIEGE_CIA,
	//INT_GETTIMEUNTILSIEGE_CORPORATE,
	//INT_GETTIMEUNTILSIEGE_CCS,
	//INT_GETTIMEUNTILSIEGE_FIREMEN,
	//INT_GETTIMEUNTILSIEGE_ORG,
	//INT_GETTIMEUNTILSIEGE_HICKS,
};

/*
enum locationsPoolCharacters {

	CHAR_ISTHEREASIEGEHERE,
	CHAR_GETLOCATIONTYPE,
	CHAR_DOESTHISPLACENEEDACAR,
	CHAR_ISTHISUNDERATTACK,
	CHAR_ISTHISAFRONT,
};
enum locationsPoolShorts {

	SHORT_GETSIEGETYPE,
	SHORT_GETSIEGEESCALATIONSTATE,
};
enum locationsPoolStrings {

	STRING_GETLOCATIONNAME,
	STRING_GETLOCATIONNAMEWITHGETNAMEMETHOD,
	STRING_GETLOCATIONNAMEWITHGETNAMEMETHOD,
	STRING_GETFRONTNAME,
};*/
class LocationsPool : ItemTypePool {
public:
	static LocationsPool getInstance();
	void delete_and_clear_pool();
	void spawnATank(int cursite, int num);
	void initSite(int loc);
	void eraseAndReplaceGraffiti(int cursite, int locx, int locy, int locz);
	void hideCCSSafehouses();
	void addHeat(int cursite, int heat);
	void clearHeat(int cursite);
	void clearunderattack(int cursite);
	void deleteTankTraps(int l);
	void setTimeUntilSiege(int loc, int type, int time);
	void setLocationMappedAndUnhidden(int cursite);
	void removeTank(int cursite);
	void addSiegeKill(int cursite);
	void setTimeUntilSiege(int cursite, int time);
	void evictLCSFrom(int l);
	int deleteSpecialItem(int slot, vector<int> loottypeindex);
	void initLocation(int cursite);
	void equipLoc(int, int);
	void stashThisLootHere(const string&, int);
	void stashThisWeaponHere(int itemindex, int shelter);
	void setSiegetimeuntillocated(int cursite, int timer);
	void stashThisArmorHere(int itemindex, int shelter);
	void captureSite(int cursite);
	void closeSite(int cursite, int sitecrime);
	void setRenting(int cursite, int renting);
	void tickAttackTime(int cursite);
	void resetAttackTime(int cursite);
	void spawnATank(int cursite);
	void turnOffSiege(int cursite);

	const int lenpool() const;
	const int findTravelLocation() const;

	const int get_specific_integer(const locationsPoolIntegers lPI, const int cursite) const;

	void isThereASiegeHere(int cursite, char newCondition) const;
	void isThisPlaceHighSecurity(int cursite, int newCondition) const;
	void getAssetValues(long & weaponValue, long & armorValue, long & clipValue, long & lootValue) const;
	const void findAllLootTypes(vector<bool>& havetype, vector<int>& loottypeindex, const vector<string>& dox) const;



	bool canBeUpgraded(int cursite) const ;
	const bool isNewRental(int cursite) const;
	const bool canBeFortified(int cursite) const;
	bool siteHasCameras(int cursite) const;
	bool hasTraps(int loc) const;
	bool lightsOff(int loc) const;
	const bool isLocationMapped(int cursite) const;
	const bool isLocationHidden(int cursite) const;

	const char isThereASiegeHere(int cursite) const ;
	const char getLocationType(int cursite) const;
	const char doesThisPlaceNeedACar(int cursite) const;
	char isThisUnderAttack(int cursite) const;
	char isThisAFront(int cursite) const;

	const short getSiegeType(int cursite) const;
	const short getSiegeEscalationState(int cursite) const;

	const string getLocationName(int cursite) const;
	const string getLocationNameWithGetnameMethod(int cursite, signed char a, bool b) const;
	const string getLocationNameWithGetnameMethod(int cursite, signed char a) const;
	string getFrontName(int cursite) const;


	int getTimeUntilSiege(int loc, int type) const;

private:

	int getStoresAmount(int l) const;
	const int getRentingType(int cursite) const;
	const int isThisPlaceHighSecurity(int cursite) const;
	const int getLocationCity(int cursite) const;
	const int getCompoundWalls(int cursite) const;
	const int isThisSiteClosed(int cursite) const;
	const int getLocationParent(int cursite) const;
	int getAttackTime(int cursite) const;
	int doWeHaveTankTraps(int cursite) const;
	int getSiegeKills(int cursite) const;
	int getSiegeTanks(int cursite) const;
	const int getHeat(int cursite) const;
	int lenloot(int cursite) const;


	static bool locationPoolInitiated;
};
