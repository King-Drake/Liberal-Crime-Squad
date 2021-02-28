#include "../items/itemPool.h"
class CreaturePool : ItemTypePool {
private:
	static bool creaturePoolInitiated;
	//CreaturePool();
public:
	void moveEverythingFrom(int cursite, int hs);
	void stop_riding_me(int id_);
	void stopAllBleeding();
	const bool doesAnyoneLiveHere(int loc);
	void stop_preferring_me(int id_);
	void clearAllBleedingAndEscapeFlags();
	void outSleepers(int cursite, int base);
	void advanceCreaturesAtLocation(int cursite);
	void arrestOrKillCCSSleepers();
	const int countLiberals(int cursite);
	static CreaturePool getInstance();
	const int liberal_guardian_writing_power();
	const int howManyLivingPeopleAreHere(int l);
	const int lenpool() const;
	void delete_and_clear_pool();
	void setupDisband();
	const bool isThisCarWantedByAnotherSquad(long vehicleID, int squadID);
	const string getName(int p);
	void moveAllSquadMembers(int l);
};