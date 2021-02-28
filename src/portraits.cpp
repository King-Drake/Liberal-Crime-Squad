#include <cstdio>
#include <string>

//#include <QString>
//#include <QDataStream>

enum GuiState { GAME_MODE, PORTRAIT_GENERATOR, LOOKS_CALIBRATION, TOTAL_GUI };


enum Culture { TANK, AFRICAN, WEST_AFRICAN, INDIAN, BYZANTINE, GERMAN, TOTAL_CULT };
enum Gender { MALE, FEMALE, TOTAL_GEN };
enum Age { SMALL, YOUNG, MATURE, OLD, TOTAL_AGE };
enum Looks { UGLY, MODEST, AVERAGE, NICE, BEST, TOTAL_LOOKS };



enum Parts { BASE, NECK, CHIN, CHEEKS, MOUTH, EYES, NOSE, EYES2, EAR, EARS, TOTAL_PARTS };
enum HairParts { HAIR, HAIR_BEHIND, BEARD, BEARD_BEHIND, TOTAL_HAIR_PARTS };


// Understood by dataBases

enum FaceScore { BAD, NORMAL, GOOD, TOTAL_FACESCORE };
//enum ClothesStyle   {MILITARY, CIVILIAN, STREETSLUM, TOTAL_CLOTHES_DEX};
enum HairStyle { MILITARY_HAIR, CIVILIAN_HAIR, STREETSLUM_HAIR, TOTAL_HAIR_DEX };

// WHEN ADDING NEW VALUE, ENUM-STRINGS-FILE MUST MATCH
// ALSO - AS THINGS STAND, WHEN PROGRAM IS LAUNCHED, IT FIRST POPULATES assetStorage ACORDING TO THIS SOURCE FILE
//          BUT
// AFTER THIS, IT LOADS assetStorage FROM DISK WITH WHATEVER STRUCTURE IT HAD BEFORE, SO SOURCE FILE INITIALIZATION IS CIRCUMVATED


enum Location
{
	SITE_CITY_SEATTLE, // first are the cities
	SITE_CITY_LOS_ANGELES,
	SITE_CITY_NEW_YORK,
	SITE_CITY_CHICAGO,
	SITE_CITY_DETROIT,
	SITE_CITY_ATLANTA,
	SITE_CITY_MIAMI,
	SITE_CITY_WASHINGTON_DC,
	SITE_DOWNTOWN, // then are the districts
	SITE_COMMERCIAL,
	SITE_UDISTRICT,
	SITE_OUTOFTOWN,
	SITE_INDUSTRIAL,
	SITE_TRAVEL,
	SITE_HOSPITAL_CLINIC, // then come sites which cannot be mapped
	SITE_HOSPITAL_UNIVERSITY,
	SITE_BUSINESS_PAWNSHOP,
	SITE_BUSINESS_DEPTSTORE,
	SITE_BUSINESS_HALLOWEEN,
	SITE_BUSINESS_ARMSDEALER,
	SITE_BUSINESS_CARDEALERSHIP,
	SITE_RESIDENTIAL_SHELTER, // this has to be in this spot - sites before this cannot be mapped and sites after this can be mapped
	SITE_RESIDENTIAL_TENEMENT, // sites starting at this point CAN be mapped
	SITE_RESIDENTIAL_APARTMENT,
	SITE_RESIDENTIAL_APARTMENT_UPSCALE,
	SITE_RESIDENTIAL_BOMBSHELTER,
	SITE_LABORATORY_COSMETICS,
	SITE_LABORATORY_GENETIC,
	SITE_GOVERNMENT_POLICESTATION,
	SITE_GOVERNMENT_COURTHOUSE,
	SITE_GOVERNMENT_PRISON,
	SITE_GOVERNMENT_INTELLIGENCEHQ,
	SITE_GOVERNMENT_FIRESTATION,
	SITE_INDUSTRY_SWEATSHOP,
	SITE_INDUSTRY_POLLUTER,
	SITE_INDUSTRY_NUCLEAR,
	SITE_INDUSTRY_WAREHOUSE,
	SITE_CORPORATE_HEADQUARTERS,
	SITE_CORPORATE_HOUSE,
	SITE_MEDIA_AMRADIO,
	SITE_MEDIA_CABLENEWS,
	SITE_BUSINESS_CRACKHOUSE,
	SITE_BUSINESS_JUICEBAR,
	SITE_BUSINESS_CIGARBAR,
	SITE_BUSINESS_LATTESTAND,
	SITE_BUSINESS_VEGANCOOP,
	SITE_BUSINESS_INTERNETCAFE,
	SITE_BUSINESS_BARANDGRILL,
	SITE_OUTDOOR_PUBLICPARK,
	SITE_OUTDOOR_BUNKER,
	SITE_GOVERNMENT_ARMYBASE,
	SITE_BUSINESS_BANK,
	SITE_GOVERNMENT_LIBERAL_PARTY_HQ,
	SITE_GOVERNMENT_WHITE_HOUSE,
	SITENUM // this comes last
};
enum Allignment {
	ARCH_CONSERVATIVE,
	CONSERVATIVE,
	MODERATE,
	LIBERAL,
	ELITE_LIBERAL
};

enum Occupation
{
	CREATURE_BOUNCER,
	CREATURE_SECURITYGUARD,
	CREATURE_SCIENTIST_LABTECH,
	CREATURE_SCIENTIST_EMINENT,
	CREATURE_CORPORATE_MANAGER,
	CREATURE_CORPORATE_CEO,
	CREATURE_WORKER_SERVANT,
	CREATURE_WORKER_JANITOR,
	CREATURE_WORKER_SWEATSHOP,
	CREATURE_WORKER_FACTORY_NONUNION,
	CREATURE_WORKER_FACTORY_CHILD,
	CREATURE_WORKER_SECRETARY,
	CREATURE_WORKER_FACTORY_UNION,
	CREATURE_LANDLORD,
	CREATURE_TEENAGER,
	CREATURE_COP,
	CREATURE_SWAT,
	CREATURE_DEATHSQUAD,
	CREATURE_FIREFIGHTER,
	CREATURE_EDUCATOR,
	CREATURE_GANGUNIT,
	CREATURE_JUDGE_LIBERAL,
	CREATURE_JUDGE_CONSERVATIVE,
	CREATURE_AGENT,
	CREATURE_RADIOPERSONALITY,
	CREATURE_NEWSANCHOR,
	CREATURE_GENETIC,
	CREATURE_GUARDDOG,
	CREATURE_PRISONER,
	CREATURE_JUROR,
	CREATURE_LAWYER,
	CREATURE_SEWERWORKER,
	CREATURE_COLLEGESTUDENT,
	CREATURE_MUSICIAN,
	CREATURE_MATHEMATICIAN,
	CREATURE_TEACHER,
	CREATURE_HSDROPOUT,
	CREATURE_BUM,
	CREATURE_GANGMEMBER,
	CREATURE_CRACKHEAD,
	CREATURE_PRIEST,
	CREATURE_ENGINEER,
	CREATURE_FASTFOODWORKER,
	CREATURE_BAKER,
	CREATURE_BARISTA,
	CREATURE_BARTENDER,
	CREATURE_TELEMARKETER,
	CREATURE_CARSALESMAN,
	CREATURE_OFFICEWORKER,
	CREATURE_FOOTBALLCOACH,
	CREATURE_PROSTITUTE,
	CREATURE_MAILMAN,
	CREATURE_GARBAGEMAN,
	CREATURE_PLUMBER,
	CREATURE_CHEF,
	CREATURE_CONSTRUCTIONWORKER,
	CREATURE_AMATEURMAGICIAN,
	CREATURE_TANK,
	CREATURE_MERC,
	CREATURE_HICK,
	CREATURE_SOLDIER,
	CREATURE_VETERAN,
	CREATURE_HARDENED_VETERAN,
	CREATURE_PRISONGUARD,
	CREATURE_HIPPIE,
	CREATURE_CRITIC_ART,
	CREATURE_CRITIC_MUSIC,
	CREATURE_SOCIALITE,
	CREATURE_PROGRAMMER,
	CREATURE_RETIREE,
	CREATURE_PAINTER,
	CREATURE_SCULPTOR,
	CREATURE_AUTHOR,
	CREATURE_JOURNALIST,
	CREATURE_DANCER,
	CREATURE_PHOTOGRAPHER,
	CREATURE_CAMERAMAN,
	CREATURE_HAIRSTYLIST,
	CREATURE_FASHIONDESIGNER,
	CREATURE_CLERK,
	CREATURE_THIEF,
	CREATURE_ACTOR,
	CREATURE_YOGAINSTRUCTOR,
	CREATURE_MARTIALARTIST,
	CREATURE_ATHLETE,
	CREATURE_BIKER,
	CREATURE_TRUCKER,
	CREATURE_TAXIDRIVER,
	CREATURE_NUN,
	CREATURE_MUTANT,
	CREATURE_DOCTOR,
	CREATURE_NURSE,
	CREATURE_CCS_VIGILANTE,
	CREATURE_CCS_ARCHCONSERVATIVE,
	CREATURE_POLITICALACTIVIST,
	CREATURE_CCS_MOLOTOV,
	CREATURE_CCS_SNIPER,
	CREATURE_PSYCHOLOGIST,
	CREATURE_LOCKSMITH,
	CREATURE_MILITARYPOLICE,
	CREATURE_SEAL,
	CREATURE_MILITARYOFFICER,
	CREATURE_BANK_TELLER,
	CREATURE_BANK_MANAGER,
	CREATURE_SECRET_SERVICE,
	CREATURE_POLITICIAN,
	CREATURENUM
};

struct Package {

	// All enumus switches should have a reasonable default CASE
		// EX: for cases where a new area is added to the game, but program isn't aware of it

	// Are police officers that go on a date in civilian clothes ?

	/*

	friend QDataStream& operator << (QDataStream& out, const Package& entry) {

		out << entry.age;
		out << entry.isFemale;
		out << entry.occupation;
		out << entry.laws;
		out << entry.charisma;
		out << entry.identityHash;
		out << entry.isHostile;
		out << entry.isNPC;
		out << entry.isGeneric;
		out << entry.allignment;
		out << entry.name;
		out << entry.selector;
		out << entry.isAlive;
		out << entry.isSleeper;

		return out;
	}


	friend QDataStream& operator >> (QDataStream& in, Package& entry) {

		in >> entry.age;
		in >> entry.isFemale;
		in >> entry.occupation;
		in >> entry.laws;
		in >> entry.charisma;
		in >> entry.identityHash;
		in >> entry.isHostile;
		in >> entry.isNPC;
		in >> entry.isGeneric;
		in >> entry.allignment;
		in >> entry.name;
		in >> entry.selector;
		in >> entry.isAlive;
		in >> entry.isSleeper;

		return in;
	}

	*/
	// SessionSwitch

	bool isFemale;//                [bool]      0
	Occupation occupation;//        [enum]      police officer
	//Clothing clothes;//           [enum]      police uniform
	int age;//                      [int]       28
	int charisma;//                 [int]       13
	Allignment allignment;//        [enum]      conservative
	std::string name;
	//QString name;//                 [String]    noName      if ScruffyJanitor, use occupation instead


	int selector;//                 [int]       2            (for proper display of portrait on GUI -and- interaction with creature ease)
	int identityHash;//             [string?]   dk3rcS       (what will be stored in the DB)
	bool isGeneric;//               [bool]      true         (is worth storing, otherwise discard after scene) check scruffyName - if yes, toggle this as well
	bool isNPC;//                   [bool]      false


	Allignment laws;//              [enum]      liberal      (game will need to make a mean of all laws and determine if [conservative] (all sharp), [>modarate] (75 %
	Location location;//            [enum]      streets      (must additionally take care of cases like recruiting/dating scene)
	bool isHostile;//               [bool]      true
	bool isAlive;//                 [bool]      true
	bool isSleeper;//               [bool]      false

	// special (?)                  [bool]      false       Used for either CCS boss, or player Leader, or president, VIPs etc.



};
enum LCSIO_FLAGS
{
	LCSIO_PRE_ART = 1, /// Append the given file name to the art directory path.
	LCSIO_PRE_HOME = 2 /// Append the given file name to the home directory path.
};
struct CreatureBools
{
	const bool exists;
	const bool alive;
	const bool enemy;
	CreatureBools(bool _exists, bool _alive, bool _enemy) :
		exists(_exists),
		alive(_alive),
		enemy(_enemy)
	{};
};
struct CreatureInts
{
	const int align;
	const int type;
	const int blood;
	CreatureInts(int _align, int _type, int _blood) :
		align(_align),
		type(_type),
		blood(_blood)
	{};
};
struct PartialCreatureJustice {
	const int juice;
	const int align;
	const char deathpenalty;
	const int location;
	const int sentence;
	PartialCreatureJustice(const char _deathpenalty, const int _location, const int _sentence, const int _juice, const  int _align) :
		deathpenalty(_deathpenalty),
		location(_location),
		sentence(_sentence),
		juice(_juice),
		align(_align)
	{}
};
struct CreatureJustice {
	const std::string propername;
	const std::string name;
	const std::string get_type_name;
	const int juice;
	const int align;
	const char deathpenalty;
	const int location;
	const int sentence;
	const int crimes_suspected[30];
	CreatureJustice(PartialCreatureJustice na, const char _propername[], const  char _name[], const std::string _get_type_name, const int _crimes_suspected[30]) :
		propername(_propername),
		name(_name),
		get_type_name(_get_type_name),
		deathpenalty(na.deathpenalty),
		location(na.location),
		sentence(na.sentence),
		// Fragile af, but C++ doesn't make const arrays easy to implement, and documentation is unclear
		crimes_suspected{
		_crimes_suspected[0],
		_crimes_suspected[1],
		_crimes_suspected[2],
		_crimes_suspected[3],
		_crimes_suspected[4],
		_crimes_suspected[5],
		_crimes_suspected[6],
		_crimes_suspected[7],
		_crimes_suspected[8],
		_crimes_suspected[9],
		_crimes_suspected[10],
		_crimes_suspected[11],
		_crimes_suspected[12],
		_crimes_suspected[13],
		_crimes_suspected[14],
		_crimes_suspected[15],
		_crimes_suspected[16],
		_crimes_suspected[17],
		_crimes_suspected[18],
		_crimes_suspected[19],
		_crimes_suspected[20],
		_crimes_suspected[21],
		_crimes_suspected[22],
		_crimes_suspected[23],
		_crimes_suspected[24],
		_crimes_suspected[25],
		_crimes_suspected[26],
		_crimes_suspected[27],
		_crimes_suspected[28],
		_crimes_suspected[29],
	},
	juice(na.juice),
	align(na.align)
	{}
};
struct NameAndAlignment
{
	const bool exists;
	const bool alive;
	const bool enemy;
	const int align;
	const int type;
	const int blood;
	const std::string name;
	NameAndAlignment(CreatureBools creatureBools, CreatureInts creatureInts, std::string _name) :
		exists(creatureBools.exists),
		alive(creatureBools.alive),
		enemy(creatureBools.enemy),
		type(creatureInts.type),
		blood(creatureInts.blood),
		align(creatureInts.align),
		name(_name)
	{};
};
struct CreatureBio {

	const int birthday_month;
	const int birthday_day;
	const int age;

	const char gender_conservative;
	const char gender_liberal;
	CreatureBio(const int _birthday_month, const int _birthday_day, const int _age, const  char _gender_conservative, const char _gender_liberal) : birthday_month(_birthday_month), birthday_day(_birthday_day), age(_age), gender_conservative(_gender_conservative), gender_liberal(_gender_liberal) {};
};

#include <vector>
#include <common\stringconversion.h>

template <class Container> inline long len(const Container& x)
{
	return x.size();
}
std::vector<int> PCreatureCharisma();
std::vector<NameAndAlignment> PNameAndAlignment();
std::vector<CreatureJustice> PCreatureJustice();
std::vector<CreatureBio> PCreatureBio();

std::vector<int> ActiveSquadPCreatureCharisma();
std::vector<NameAndAlignment> ActiveSquadPNameAndAlignment();
std::vector<CreatureJustice> ActiveSquadPCreatureJustice();
std::vector<CreatureBio> ActiveSquadPCreatureBio();

const std::string CONST_CPP_IO_WB = "wb";
FILE* LCSOpenFile(const char* filename, const char* mode, int flags);
std::vector<int> ActiveSquadID();
std::vector<int> PCreatureID();
enum CreatureGender
{
	GENDER_NEUTRAL,
	GENDER_MALE,
	GENDER_FEMALE,
	// Used to get some more specific names.
	GENDER_WHITEMALEPATRIARCH,
	// Used in creature creation.
	GENDER_MALE_BIAS,
	GENDER_FEMALE_BIAS,
	GENDER_RANDOM
};
bool nullActive();
void LCSCloseFile(FILE* handle);
void printStuff(std::string str);
int getAverageLawLevel();
class title_screen {

private:
	static title_screen s_title_singleton;
	static std::vector<std::string> s_savefiles;
	static std::string savefile_name;
	bool static autosave;
	static bool titleInitiated;
	void choose_savefile_name();
	void selectAndLoadSaveFile();
public:
	static title_screen getInstance();
	void mode_title();
	std::string getFileName();
	void reset();
	static void setautosaveoption(bool shouldautosave);
	void autosavegame();
};
std::vector<std::string> PAllClothes();
std::vector<std::string> SquadAllClothes();
void outputPortraitFile() {


	std::vector<NameAndAlignment> nAA = PNameAndAlignment();
	std::vector < CreatureJustice> jAA = PCreatureJustice();
	std::vector < CreatureBio> bAA = PCreatureBio();
	std::vector<std::string> allClothes = PAllClothes();
	std::vector <int> cAA = PCreatureCharisma();
	std::vector<std::string> squadClothes = SquadAllClothes();
	std::vector<int> pAAID = PCreatureID();

	std::string fileName = "message.raw"; 
	int averageLaw = getAverageLawLevel();

	FILE* h;
	h = LCSOpenFile(fileName.c_str(), CONST_CPP_IO_WB.c_str(), LCSIO_PRE_HOME);
	if (h != NULL)
	{
		
		// TODO selector number does not account for entities leaving, or prisoners
		// start with the number of entries
		int lengthOf = len(nAA);
		fwrite(&lengthOf, sizeof(int), 1, h);

		for (int i = 0; i < len(nAA); i++) {

			Package entry;
			entry.age = bAA[i].age;
			entry.isFemale = bAA[i].gender_liberal == GENDER_FEMALE;
			entry.occupation = (Occupation)nAA[i].type;
			entry.laws = (Allignment) averageLaw;
			entry.charisma = cAA[i];
			entry.identityHash = pAAID[i];
			entry.isHostile = nAA[i].enemy;
			entry.isNPC = 1;
			entry.isGeneric = true;
			entry.allignment = (Allignment) (nAA[i].align + 2);
			entry.name = nAA[i].name;
			entry.selector = i;
			entry.isAlive = nAA[i].alive;
			entry.isSleeper = 0;
			char outputName[32]{ "" };
			strcpy(outputName, nAA[i].name.c_str());
			char outputClothes[32]{ "" };
			strcpy(outputClothes, allClothes[i].c_str());

		fwrite(&entry.age, sizeof(int), 1, h);
		fwrite(&entry.isFemale, sizeof(bool), 1, h);
		fwrite(&entry.occupation, sizeof(int), 1, h);
		fwrite(&entry.laws, sizeof(int), 1, h);
		fwrite(&entry.charisma, sizeof(int), 1, h);
		fwrite(&entry.identityHash, sizeof(int), 1, h);
		fwrite(&entry.isHostile, sizeof(bool), 1, h);
		fwrite(&entry.isNPC, sizeof(bool), 1, h);
		fwrite(&entry.isGeneric, sizeof(bool), 1, h);
		fwrite(&entry.allignment, sizeof(int), 1, h);
		fwrite(&outputName, sizeof(char), 32, h);
		fwrite(&entry.selector, sizeof(int), 1, h);
		fwrite(&entry.isAlive, sizeof(bool), 1, h);
		fwrite(&entry.isSleeper, sizeof(bool), 1, h);
		fwrite(&outputClothes, sizeof(char), 32, h);
		}
		
		if (!nullActive()) {
	std::vector<int> AScAA = ActiveSquadPCreatureCharisma();
	std::vector<NameAndAlignment> ASnAA = ActiveSquadPNameAndAlignment();
	std::vector<CreatureJustice> ASjAA = ActiveSquadPCreatureJustice();
	std::vector<CreatureBio> ASbAA = ActiveSquadPCreatureBio();
	std::vector<int> pAAID = ActiveSquadID();
			// start with the number of active squad members
			lengthOf = len(ASnAA);
			fwrite(&lengthOf, sizeof(int), 1, h);

			for (int i = 0; i < len(ASnAA); i++) {

				Package entry;
				entry.age = ASbAA[i].age;
				entry.isFemale = ASbAA[i].gender_liberal == GENDER_FEMALE;
				entry.occupation = (Occupation)ASnAA[i].type;
				entry.laws = (Allignment)averageLaw;
				entry.charisma = AScAA[i];
				entry.identityHash = pAAID[i];
				entry.isHostile = ASnAA[i].enemy;
				entry.isNPC = 1;
				entry.isGeneric = true;
				entry.allignment = (Allignment)(ASnAA[i].align + 2);
				entry.name = ASnAA[i].name;
				entry.selector = i;
				entry.isAlive = ASnAA[i].alive;
				entry.isSleeper = 0;
				char outputName[32]{ "" };
				strcpy(outputName, ASnAA[i].name.c_str());
				char outputClothes[32]{ "" };
				strcpy(outputClothes, squadClothes[i].c_str());

				fwrite(&entry.age, sizeof(int), 1, h);
				fwrite(&entry.isFemale, sizeof(bool), 1, h);
				fwrite(&entry.occupation, sizeof(int), 1, h);
				fwrite(&entry.laws, sizeof(int), 1, h);
				fwrite(&entry.charisma, sizeof(int), 1, h);
				fwrite(&entry.identityHash, sizeof(int), 1, h);
				fwrite(&entry.isHostile, sizeof(bool), 1, h);
				fwrite(&entry.isNPC, sizeof(bool), 1, h);
				fwrite(&entry.isGeneric, sizeof(bool), 1, h);
				fwrite(&entry.allignment, sizeof(int), 1, h);
				fwrite(&outputName, sizeof(char), 32, h);
				fwrite(&entry.selector, sizeof(int), 1, h);
				fwrite(&entry.isAlive, sizeof(bool), 1, h);
				fwrite(&entry.isSleeper, sizeof(bool), 1, h);
				fwrite(&outputClothes, sizeof(char), 32, h);
			}
		}
		else {
			int i = 0;
			fwrite(&i, sizeof(int), 1, h);
		}

		char outputFilename[32]{ "" };
		strcpy(outputFilename, title_screen::getInstance().getFileName());
		fwrite(&outputFilename, sizeof(char), 32, h);
		
		LCSCloseFile(h);
	}
}