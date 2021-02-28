int pressSpecificKey(const int x, const int y);
int pressSpecificKey(const int x, const int y, const int z);
void pressSpecificKey(const int x, const int y, const int z, const int w);
int pressSpecificKey(const int x, const int y, const int z, const int w, const int u);
int clearAlt(void);
int refreshAlt(void);
// These are the functions we seek to remove from as much as possible
int moveAlt(const int, const int);
int	mvaddstrAlt(const int, const int, const std::string);
int	mvaddstrAlt(const int, const int, const std::string, Log &a);
int	mvaddstrAlt(const int, const int, const char*, Log &a);
int	mvaddstrAlt(const int, const int, const int, Log &a);
int	mvaddstrAlt(const int, const int, const char*);
int	mvaddstrAlt(const int, const int, const int);
int	mvaddstrAlt(const int x, const int y, const  char *z);
int addstrAlt(const char *text);
int addstrAlt(const std::string&);
int addstrAlt(const std::string&, Log &log);
int addstrAlt(const char *text, Log &log);
int addstrAlt(const long num);
int addstrAlt(const long num, Log &log);
int addcharAlt(const char ch);
int addcharAlt(const char ch, Log &log);
int mvaddcharAlt(int y, int x, char ch);
int mvaddcharAlt(int y, int x, char ch, Log &log);
//
// These are less critical to the goal
int eraseAlt(void);
int mvaddchAlt(int, int, const int);
int mvgetnstrAlt(int, int, char *, int);
int addchAlt(const int);
void PDC_set_titleAlt(const char *);
int endwinAlt();
int mvaddstrCenter(int i, string str);
int mvaddstrCenter(int i, string str, Log &log);
void pressAnyKey();
//
void noechoAlt();
void start_colorAlt();
void curs_setAlt(int i);
void keypadAlt(bool i);
void raw_outputAlt(bool i);
void init_pairAlt(short x, short y, short z);
void initscrAlt();
void set_colorAlt(short f, short b, bool bright, bool blink = false);
int checkkeyAlt();
void echoAlt();

int getkeyAlt();

bool is_page_up(const int c);
bool is_page_down(const int c);

//needed to display who signed bill.
extern int getSleeperPresidentStatus();