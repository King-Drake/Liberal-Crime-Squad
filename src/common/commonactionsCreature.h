
/* common - tests if the person is a wanted criminal */
bool iscriminal(CreatureJustice cr);
/* common - sends somebody to the hospital */
void hospitalize(int loc, DeprecatedCreature &patient);
/* common - determines how long a creature's injuries will take to heal */
int clinictime(DeprecatedCreature &g);
/* common - applies a crime to a person */
void criminalize(DeprecatedCreature &cr, short crime);
/* common - gives juice to a given creature */
void addjuice(DeprecatedCreature &cr, long juice, long cap);
/* common - removes the liberal from all squads */
void removesquadinfo(DeprecatedCreature &cr);
/* Determines the number of subordinates a creature may command */
int maxsubordinates(const DeprecatedCreature& cr);
/* Determines the number of subordinates a creature may recruit,
based on their max and the number they already command */
int subordinatesleft(const DeprecatedCreature& cr);
// Determines the number of love slaves a creature has
int loveslaves(const DeprecatedCreature& cr);
/* Determines the number of loveslaves a creature may recruit,
based on their max and the number they already command */
int loveslavesleft(const DeprecatedCreature& cr);
// Determines the number of recruitment meetings a creature has scheduled
int scheduledmeetings(const DeprecatedCreature& cr);
// Determines the number of dates a creature has scheduled
int scheduleddates(const DeprecatedCreature& cr);
// Prompt to convert a new recruit into a sleeper
void sleeperize_prompt(DeprecatedCreature &converted, DeprecatedCreature &recruiter, int y);
/* common - Sort a list of creatures.*/
void sortliberals(std::vector<DeprecatedCreature *>& liberals, short sortingchoice, bool dosortnone = false);
/* common - Functions used when sorting vectors of creatures. */
bool sort_none(const DeprecatedCreature* first, const DeprecatedCreature* second);

bool sort_locationandname(const DeprecatedCreature* first, const DeprecatedCreature* second);
bool sort_squadorname(const DeprecatedCreature* first, const DeprecatedCreature* second);
