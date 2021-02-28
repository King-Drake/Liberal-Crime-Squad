
#include "../items/itemtype.h"
#include "../items/cliptype.h"
#include "../items/weapontype.h"
#include "../items/item.h"
#include "../items/clip.h"
#include "../items/weapon.h"
#include "../items/armor.h"
#include "augmentation.h"

#include "creatureEnums.h"

enum Bodyparts
{
	BODYPART_HEAD,
	BODYPART_BODY,
	BODYPART_ARM_RIGHT,
	BODYPART_ARM_LEFT,
	BODYPART_LEG_RIGHT,
	BODYPART_LEG_LEFT,
	BODYPARTNUM
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
struct NameAndAlignment
{
	const bool exists;
	const bool alive;
	const bool enemy;
	const int align;
	const int type;
	const int blood;
	const string name;
	NameAndAlignment(CreatureBools creatureBools, CreatureInts creatureInts, string _name) :
		exists(creatureBools.exists),
		alive(creatureBools.alive),
		enemy(creatureBools.enemy),
		type(creatureInts.type),
		blood(creatureInts.blood),
		align(creatureInts.align),
		name(_name)
	{};
};
int get_XML_value(const std::string& inputXml);

void make_creature_without_encounter_array(int cr, short type);
/* fills a string with a proper name */
void generate_name(char *str, char gender = GENDER_NEUTRAL);
/* get a first and last name for the same person */
void generate_name(char *first, char *last, char gender = GENDER_NEUTRAL);

/* fills a string with a proper name */
string generate_name(char gender = GENDER_NEUTRAL);
/* get a first and last name for the same person */
//string generate_name(char *first, char *last, char gender = GENDER_NEUTRAL);

/* get a first, middle, and last name for the same person */
void generate_long_name(char *first, char *middle, char *last, char gender = GENDER_NEUTRAL);
/* gets a random first name */
void firstname(char *str, char gender = GENDER_NEUTRAL);
/* gets a random last name */
string lastname(bool archconservative = false);

struct CreatureHealth {

	const unsigned char wound[BODYPARTNUM];
	const char special[SPECIALWOUNDNUM];

	const bool alive;

	const char animalgloss;

	const int blood;
	const int align;
	CreatureHealth(const NameAndAlignment na, const  char _animalgloss, const unsigned char _wound[BODYPARTNUM], const char _special[SPECIALWOUNDNUM]) :
		alive(na.alive), animalgloss(_animalgloss), blood(na.blood), align(na.align),
		// Fragile af, but C++ doesn't make const arrays easy to implement, and documentation is unclear
		wound{ _wound[0], _wound[1], _wound[2], _wound[3], _wound[4], _wound[5]},
		special{ _special[0], _special[1], _special[2], _special[3], _special[4], _special[5], _special[6], _special[7], _special[8], 
		_special[9], _special[10], _special[11], _special[12], _special[13], _special[14], _special[15], _special[16] }
	{};
};

struct ListOfCreatureSkills {
	int get_skill(int s) const { return skills[s]; }
	int get_skill_ip(int s) const { return skill_experience[s]; }
	int skill_cap(int s) const { return skill_attribute[s]; };

	ListOfCreatureSkills(const int _skills[SKILLNUM], const int _skill_experience[SKILLNUM], const int _skill_attribute[SKILLNUM]) {
		for (int i = 0; i < SKILLNUM; i++) {
			skills[i] = _skills[i];
			skill_experience[i] = _skill_experience[i];
			skill_attribute[i] = _skill_attribute[i];
		}
	}
private:
	// C++ makes const arrays difficult to implement
	// so these are private arrays with getters and no setters
	// nearly as good
	int skills[SKILLNUM];
	int skill_experience[SKILLNUM];
	int skill_attribute[SKILLNUM];

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
	const string propername;
	const string name;
	const string get_type_name;
	const int juice;
	const int align;
	const char deathpenalty;
	const int location;
	const int sentence;
	const int crimes_suspected[30];
	CreatureJustice(PartialCreatureJustice na, const char _propername[], const  char _name[], const string _get_type_name, const int _crimes_suspected[30]) : 
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
struct CreatureBio {

	const int birthday_month;
	const int birthday_day;
	const int age;

	const char gender_conservative;
	const char gender_liberal;
	CreatureBio(const int _birthday_month, const int _birthday_day, const int _age, const  char _gender_conservative, const char _gender_liberal) : birthday_month(_birthday_month), birthday_day(_birthday_day), age(_age), gender_conservative(_gender_conservative), gender_liberal(_gender_liberal) {};
};
struct CreatureInventory {

	const string get_weapon_string;
	const string get_armor_string;

	CreatureInventory(const string _get_weapon_string, const string _get_armor_string) : get_weapon_string(_get_weapon_string), get_armor_string(_get_armor_string) {}
};
struct CreatureCar {

	const int pref_carid;
	const int carid;
	const char pref_is_driver;
	const char is_driver;

	CreatureCar(const int _pref_carid, const int _carid, const char _pref_is_driver, const char _is_driver) : pref_carid(_pref_carid), carid(_carid), pref_is_driver(_pref_is_driver), is_driver(_is_driver) {}
};

struct CantBluffAnimal {
	const char cantbluff;
	const char animalgloss;
	CantBluffAnimal(const char _cantbluff, const char _animalgloss) : cantbluff(_cantbluff), animalgloss(_animalgloss) {}
};

struct CreatureAttributeList {
	const int get_attribute(const int x) {
			return attribute_juice_list.at(x);
	}
	CreatureAttributeList(const int _attribute_juice_list[ATTNUM]) : 
		attribute_juice_list{
		map<int, int>::value_type(ATTRIBUTE_STRENGTH, _attribute_juice_list[ATTRIBUTE_STRENGTH]),
		map<int, int>::value_type(ATTRIBUTE_INTELLIGENCE, _attribute_juice_list[ATTRIBUTE_INTELLIGENCE]),
		map<int, int>::value_type(ATTRIBUTE_WISDOM, _attribute_juice_list[ATTRIBUTE_WISDOM]),
		map<int, int>::value_type(ATTRIBUTE_AGILITY, _attribute_juice_list[ATTRIBUTE_AGILITY]),
		map<int, int>::value_type(ATTRIBUTE_HEALTH, _attribute_juice_list[ATTRIBUTE_HEALTH]),
		map<int, int>::value_type(ATTRIBUTE_CHARISMA, _attribute_juice_list[ATTRIBUTE_CHARISMA]),
		map<int, int>::value_type(ATTRIBUTE_HEART, _attribute_juice_list[ATTRIBUTE_HEART]),
	}
	{}
private:
	const map<int, int> attribute_juice_list;
};