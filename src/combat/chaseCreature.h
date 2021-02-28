
int driveskill(DeprecatedCreature &cr, Vehicle &v);
Vehicle* getChaseVehicle(const DeprecatedCreature &c);
DeprecatedCreature* getChaseDriver(const DeprecatedCreature &c);
/* the next two functions force a chase sequence with a specific liberal */
bool footchase(DeprecatedCreature &cr);
bool chasesequence(DeprecatedCreature &cr, Vehicle &v);