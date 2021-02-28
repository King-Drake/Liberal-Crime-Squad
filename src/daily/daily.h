
void advanceday(char &clearformess, char canseethings);

/* daily - manages too hot timer and when a site map should be re-seeded and renamed */
void advancelocations();
/* daily - returns true if the site type supports high security */
char securityable(int type);

/* daily - returns the number of days in the current month */
int monthday();