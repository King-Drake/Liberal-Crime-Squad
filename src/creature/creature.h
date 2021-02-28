


#pragma once
#include "creatureConstants.h"
#include "newcreature.h"

#ifndef MIN
// minimum of 2 numbers
#define MIN(a,b) (((a)>(b))?(b):(a))
#endif
int get_associated_attribute(int skill_type);
class DeprecatedCreature
{
public:
	const NameAndAlignment getNameAndAlignment() const { return NameAndAlignment(CreatureBools(exists, alive, enemy()), CreatureInts(align, type, blood), name); }
	const CreatureHealth getCreatureHealth()  const { return CreatureHealth(getNameAndAlignment(), animalgloss, wound, special); }
	const CreatureJustice getCreatureJustice()  const { return CreatureJustice(PartialCreatureJustice(deathpenalty, location, sentence, juice, align), propername, name, get_type_name(), crimes_suspected); }
	const CreatureBio getCreatureBio() const { return CreatureBio(birthday_month, birthday_day, age, gender_conservative, gender_liberal); }
	const CreatureInventory getCreatureInventory() const { return CreatureInventory(get_weapon_string(0), get_armor_string(true));  }
	const CreatureCar getCreatureCar() const { return CreatureCar(pref_carid, carid, pref_is_driver, is_driver); }
	const CantBluffAnimal getCantBluffAnimal() const { return CantBluffAnimal(cantbluff, animalgloss); }
	const ListOfCreatureSkills getListOfCreatureSkills() const {
		int skill_attribute[SKILLNUM];
		for (int i = 0; i < SKILLNUM; i++) {
			skill_attribute[i] = skill_cap(i);
		}
		return ListOfCreatureSkills(skills, skill_experience, skill_attribute);
	};
	const CreatureAttributeList getCreatureAttributeList() const {
		int attribute_juice_list[ATTNUM];
		for (int i = 0; i < ATTNUM; i++) {
			attribute_juice_list[i] = get_attribute(i, true);
		}
		return CreatureAttributeList(attribute_juice_list);
	}

	DeprecatedCreature() { creatureinit(); }
	DeprecatedCreature(const DeprecatedCreature& org) { copy(org); }
	DeprecatedCreature& operator=(const DeprecatedCreature& rhs);
	~DeprecatedCreature();
	explicit DeprecatedCreature(const std::string& inputXml);

	/* are the characters close enough in age to date? */
	bool can_date(const int aage, const char aanimalgloss) const;

	bool enemy() const;



	int get_disguise_difficulty() const;
	int	get_stealth_difficulty() const;
	int get_true_attribute(int attribute) const;
	int get_attribute(int attribute, bool use_juice) const;
	int attribute_roll(int attribute) const;
	bool attribute_check(int attribute, int difficulty) const;
	int get_skill(int skill) const { return MIN(skills[skill], MAXATTRIBUTE); }
	int skill_roll(int skill) const;
	bool skill_check(int skill, int difficulty) const;
	int get_weapon_skill() const;
	int get_skill_ip(int skill) const { return skill_experience[skill]; }
	std::string get_type_name() const; // this function is implemented inline in creaturetype.h (can't do it here since CreatureType has to be defined after DeprecatedCreature)
	
	bool is_armed() const { return weapon; }
	bool is_naked() const { return !armor; }
	bool will_do_ranged_attack(bool force_ranged, bool force_melee) const; //force_melee is likely unnecessary. -XML
	bool can_reload() const;
	bool will_reload(bool force_ranged, bool force_melee) const;
	int count_clips() const;
	int count_weapons() const;
	bool weapon_is_concealed() const { return is_armed() && get_armor().conceals_weaponsize(weapon->get_size()); }
	string get_weapon_string(int subtype) const;
	string get_armor_string(bool fullname) const { return get_armor().equip_title(fullname); }
	string showXml() const;
	bool is_active_liberal() const;
	bool is_imprisoned() const;
	bool is_lcs_sleeper() const;
	bool canwalk() const;
	//int attval(int a,char usejuice=1);
	/* are they interested in talking about the issues? */
	bool talkreceptive() const;
	/* if this is true the creature will never accept dates or talk about the issues (note the bool is not used in xml as currently it is only
	applied post creature creation)*/
	bool wontdateortalk() const;
	/* rolls up a proper name for a creature */
	void namecreature();
	/* can turn the tables on datenapping */
	bool kidnap_resistant() const;
	bool reports_to_police() const;
	/* returns the creature's maximum level in the given skill */
	int skill_cap(int skill) const { return get_attribute(get_associated_attribute((CreatureSkill)skill), true); }
	const char* heshe(bool capitalize = false) const;
	const char* hisher(bool capitalize = false) const;
	const char* himher(bool capitalize = false) const;


	void set_attribute(int attribute, int amount) { attributes[attribute] = MIN(amount, MAXATTRIBUTE); }
	void adjust_attribute(int attribute, int amount) { set_attribute(attribute, attributes[attribute] + amount); }
	void set_skill(int skill, int amount) { skills[skill] = MIN(amount, MAXATTRIBUTE); }

	void die();
	void train(int trainedskill, int experience, int upto = MAXATTRIBUTE);
	void skill_up();

	bool reload(bool wasteful);
	bool ready_another_throwing_weapon();

	void stop_hauling_me();
	void creatureinit();

	void clear_criminal_record_but_not_heat() {

		for (int i = 0; i < LAWFLAGNUM; i++)
			crimes_suspected[i] = 0;
	}
	void clear_criminal_record() {

		// Clear criminal record?
		heat = 0;
		for (int i = 0; i < LAWFLAGNUM; i++)
			crimes_suspected[i] = 0;
	}
	void criminalize_me(const int crime, const bool grant_heat) {
		int lawflagheat(int lawflag);
		crimes_suspected[crime]++;
		if (grant_heat) {
			heat += lawflagheat(crime);

		}
	}
	void criminalize_me(const int crime) {
		criminalize_me(crime, false);
	}
	void clear_no_longer_crimes();
	void cap_crimes_at_ten();

	void apply_special_wound(const int wound, const int flag) {
		special[wound] |= flag;
	}

	void lose_blood(const int loss) {
		blood -= loss;
	}

	void lose_all_blood() {
		blood = 0;
	}

	void set_blood(const int _blood) {
		blood = _blood;
	}
	void set_special_wound(const int wound, const int value) {
		special[wound] = value;
	}
	void un_alive() {
		alive = 0; // Kill for the purposes of disbanding all contacts below
	}
	void apply_wound(const int _wound, const int flag) {
		wound[_wound] |= flag;
	}

	void another_confession() {
		confessions++;
	}
	char getCreatureConfessions() const {
		return confessions;
	}
	void rename(const string _name) {
		strcpy(name, _name.data());
	}
	void new_name() {
		void enter_name(int y, int x, char *name, int len, const char* defname);
		enter_name(24, 0, name, CREATURE_NAMELEN, propername);
	}
	void new_name_four() {
		void enter_name(int y, int x, char *name, int len, const char* defname);
		enter_name(4, 0, name, CREATURE_NAMELEN, propername);
	}
	void new_name_two() {
		void enter_name(int y, int x, char *name, int len, const char* defname);
		enter_name(2, 0, name, CREATURE_NAMELEN, propername);
	}
	void set_age(const int a) {
		age = a;
	}
	void age_up() {
		age++;
	}
	void set_date_of_birth(const int _birth_day, const int _birth_month, const int birth_year) {

		extern int year;
		extern int day;
		extern int month;

		birthday_day = _birth_day;
		birthday_month = _birth_month;
		age = year - birth_year;
		// Don't count this year in founder's age if starting before birthday
		if (month < getCreatureBio().birthday_month ||
			(month == getCreatureBio().birthday_month && day < getCreatureBio().birthday_day))
		{
			age--;
		}
	}

	Clip* take_one_clip() {

		Clip* new_clip = clips.back()->split(1);
		if (clips.back()->empty())
			clips.pop_back();
		return new_clip;
	}
	Augmentation & get_augmentation(int aug_num) { return augmentations[aug_num]; }
	Weapon& get_weapon() const { return is_armed() ? *weapon : weapon_none(); }
	Armor& get_armor() const { return is_naked() ? armor_none() : *armor; }
	bool take_clips(Item& clip, int number);
	bool take_clips(Clip& clip, int number);
	bool take_clips(const ClipType& ct, int number);
	void give_weapon(Weapon& w, vector<Item*>* lootpile);
	void give_weapon(const WeaponType& wt, vector<Item*>* lootpile);
	void drop_weapon(vector<Item*>* lootpile);
	void drop_weapons_and_clips(vector<Item*>* lootpile);
	void give_armor(Armor& a, vector<Item*>* lootpile);
	void give_armor(const int at, vector<Item*>* lootpile);
	void strip(vector<Item*>* lootpile);
	void makeloot(vector<Item *> &loot);

	void makeloot(const int base);
	void set_money(const int _money) {
		money = _money;
	}
	void no_money() {
		money = 0;
	}
	void make_cantbluff_two() {
		cantbluff = 2;
	}
	void make_cantbluff_zero() {
		cantbluff = 0;
	}
	void make_cantbluff_one() {
		cantbluff = 1;
	}
	bool is_cantbluff_two() const {
		return cantbluff == 2;
	}
	bool is_cantbluff_zero() const {
		return cantbluff == 0;
	}
	bool is_holding_body() const {
		if (prisoner) {
			return true;
		}
		else {
			return false;
		}
	}
	void discard_body() {
		prisoner = NULL;
	}
	bool is_stunned() const {
		return stunned;
	}
	void decrement_stunned() {
		stunned--;
	}
	void increase_stunned(const int e) {
		stunned += e;
	}
	void stop_being_stunned() {
		stunned = 0;
	}
	void stop_existing() {
		exists = false;
	}
	void make_existing() {
		exists = true;
	}

	// public
	string get_name_next_throwing_weapon() const {
		return extra_throwing_weapons[0]->get_shortname(0);
	}
	bool has_extra_throwing_weapons() const {
		return len(extra_throwing_weapons) > 0;
	}
	bool has_clips() const {
		return len(clips) > 0;
	}
	int activity_type() const {
		return activity.type;
	}
	void set_activity_type(const int c) {
		activity.type = c;
	}
	void set_activity_type(const int c, const int d) {
		activity.type = c;
		activity.arg = d;
	}
	int activity_arg() const {
		return activity.arg;
	}
	int get_prisoner_type()const {
		if (prisoner)
			return prisoner->type;
		else
			return -1;
	}
	string get_prisoner_name()const {
		if (prisoner)
			return prisoner->name;
		else
			return "";
	}
	int get_prisoner_align() const {
		//if (prisoner)
			return prisoner->align;
		//else
		//	return -3;
	}
	bool is_prisoner_alive() const {
		return prisoner->alive;
	}
	bool is_prisoner_enemy()const {
		return prisoner->enemy();
	}
	void delete_and_nullify_prisoner() {

		delete_and_nullify(prisoner);
	}
	void make_prisoner_ground_loot() {
		void makeloot(DeprecatedCreature &cr);
		makeloot(*prisoner);
	}
	void advance_prisoner() {
		void advancecreature(DeprecatedCreature &cr);
		advancecreature(*prisoner);
	}
	void mark_prisoner_as_kidnapped() {
		prisoner->flag |= CREATUREFLAG_KIDNAPPED;
	}
	bool is_prisoner_non_LCS() const {
		return prisoner->squadid == -1;
	}
	void deal_with_prisoner() {
		void removesquadinfo(DeprecatedCreature &cr);
		void kidnaptransfer(DeprecatedCreature &cr);
		//If this is an LCS member or corpse being hauled (marked as in the squad)
		if (prisoner->squadid != -1)
		{
			//Take them out of the squad  TODO: These two lines appear to be interchangeable, but it is unclear if they are
			removesquadinfo(*prisoner);
			//RESTORE POOL MEMBER
			//prisoner->squadid = -1;
			//Set base and current location to squad's safehouse
			//MUST LOCATE THE MEMBER
			prisoner->location = base;
			prisoner->base = base;
		}
		else //A kidnapped conservative
		{
			//Convert them into a prisoner
			//CONVERT KIDNAP VICTIM
			kidnaptransfer(*prisoner);
			delete prisoner;
		}
		discard_body();

	}
	void drop_prisoner() {
		void freehostage(DeprecatedCreature &cr, char situation);
		freehostage(*prisoner, 1);
	}
	void prisoner_dies() {

		void removesquadinfo(DeprecatedCreature &cr);
		removesquadinfo(*prisoner);
		prisoner->die();
		prisoner->location = -1;
	}
	int prisoner_usegment_power() const {
		int usegmentpower = 0;
		usegmentpower += prisoner->get_attribute(ATTRIBUTE_INTELLIGENCE, true);
		usegmentpower += prisoner->get_attribute(ATTRIBUTE_HEART, true);
		usegmentpower += prisoner->get_attribute(ATTRIBUTE_CHARISMA, true);
		usegmentpower += prisoner->get_skill(SKILL_PERSUASION);
		return usegmentpower;
	}
	void make_prisoner_cantbluff_two() {
		prisoner->make_cantbluff_two();
	}
	void make_prisoner(DeprecatedCreature *cr) {
		prisoner = cr;
	}
	void make_new_prisoner(DeprecatedCreature &cr) {

		prisoner = new DeprecatedCreature;
		*prisoner = cr;
	}
	void delete_prisoner() {
		delete prisoner;
	}
	char human_shield_attacked(DeprecatedCreature &cr) {
		bool attack(DeprecatedCreature &a, DeprecatedCreature &t, const char mistake, const bool force_melee = false);
		return attack(cr, *prisoner, 1);
	}
	int type;

	bool dontname;
	char propername[CREATURE_NAMELEN];
	char gender_conservative;
	char gender_liberal;

	std::string type_idname;
	float infiltration;
	char forceinc;
	bool has_thrown_weapon;

	int squadid;//REMEMBER, THIS IS ID NUMBER, NOT ARRAY INDEX
	int specialattack;
	int clinic;
	int dating;
	int hiding;
	int trainingtime;
	int trainingsubject;
	int joindays;
	int deathdays;
	int id;
	int hireid;

	int meetings;

	int income;

	int juice;
	int heat;
	int location;
	int worklocation;
	int base;
	int flag;

	int pref_carid;
	int carid;
	char is_driver;
	char pref_is_driver;

	// private, [in progress]
	ActivityST activity;


	int align;
	int blood;
	char animalgloss;

	unsigned char wound[BODYPARTNUM];
	char special[SPECIALWOUNDNUM];
	// private, except in haulkidnap.cpp
	DeprecatedCreature * prisoner;

	// private, except in justice.cpp
	int sentence;
	char confessions;
	char deathpenalty;

	// private, except in saveload.cpp
	char name[CREATURE_NAMELEN];
	int crimes_suspected[LAWFLAGNUM];

	int age;
	int birthday_month;
	int birthday_day;

	void settalkreceptive(const bool istalkreceptive_) {
		istalkreceptive = istalkreceptive_;
	}
	void setnevertalkordate(const bool nevertalkordate_) {
		nevertalkordate = nevertalkordate_;
	}
	void setseethroughstealth(const int seethroughstealth_) {
		seethroughstealth = seethroughstealth_;
	}
	void setseethroughdisguise(const int seethroughdisguise_) {
		seethroughdisguise = seethroughdisguise_;
	}
	void setisreports_to_police(const bool isreports_to_police_) {
		isreports_to_police = isreports_to_police_;
	}
	void setiskidnap_resistant(const bool iskidnap_resistant_) {
		iskidnap_resistant = iskidnap_resistant_;
	}
	void setactivityargNegativeOne() {
		setactivityarg(-1);
	}
	void setactivityarg(const int c) {
		activity.arg = c;
	}
	std::string getActivityString();

private:

	deque<Clip*> clips;
	deque<Weapon*> extra_throwing_weapons;

	bool alive;

	bool exists;
	int stunned;

	char cantbluff;

	int money;

	class Augmentation augmentations[AUGMENTATIONNUM];
	static Weapon& weapon_none();
	static Armor& armor_none();
	Weapon* weapon;
	Armor* armor;

	void copy(const DeprecatedCreature& org);
	int attributes[ATTNUM];
	int skills[SKILLNUM];
	int skill_experience[SKILLNUM];
	int seethroughdisguise;
	int seethroughstealth;
	bool istalkreceptive;
	bool nevertalkordate;
	bool iskidnap_resistant;
	bool isreports_to_police;

};

// this data struct is for activities, it relates to their info text and a couple of other things to avoid needing big switches in the code
struct Data_Activity
{
	bool show_name;
	char key;
	CreatureSkill skill;
	string line;
	string line2;
	string line3;
	Data_Activity(char _key, bool _show_name, string _line0, string _line1 = "", string _line2 = "", CreatureSkill _skill = SKILLNUM) : key(_key), show_name(_show_name), skill(_skill), line(_line0), line2(_line1), line3(_line2) {}
	Data_Activity() : Data_Activity('x', false, "") {}
	string lineAttempt(int row, DeprecatedCreature *cr)
	{
		if (skill == SKILLNUM) {
			string output = row == 0 ? line : row == 1 ? line2 : line3;
			return output;
		}
		else
		{
			if (row > 0) return "";
			if (cr->get_skill(skill) >= 8) return line3;
			if (cr->get_skill(skill) >= 4) return line2;
			return line;
		}
	}
};

enum UniqueCreatureData
{
	UNIQUECREATURE_ALIVE,
	UNIQUECREATURE_DEAD,
	UNIQUECREATURE_LIBERAL
};
class UniqueCreatures
{
private:
	DeprecatedCreature CEO_;
	int CEO_ID;
	DeprecatedCreature Pres_;
	int Pres_ID;
public:
	int CEO_state;
	int Pres_state;
	UniqueCreatures() : CEO_ID(-1), Pres_ID(-1) { }
	explicit UniqueCreatures(const std::string& inputXml);
	string showXml() const;
	void newCEO();
	void newPresident();
	DeprecatedCreature& CEO() { if (CEO_ID == -1) newCEO(); return CEO_; }
	DeprecatedCreature& President() { if (Pres_ID == -1) newPresident(); return Pres_; }
	void initialize() { newCEO(); newPresident(); }
};


// brutally ripped from includes.h --Schmel924
//From here up to void nameCCSMember(DeprecatedCreature &cr);
/*
implementations should be in creature.cpp
*/
// Add an age estimate to a person's name
string get_age_string(const CreatureBio bio, const char animalgloss);
/* ensures that the creature's work location is appropriate to its type */
int verifyworklocation(const int type, const int worklocation);
/* turns a creature into a conservative */
void conservatise(DeprecatedCreature &cr);
/* turns a creature into a liberal */
void liberalize(DeprecatedCreature &cr, bool rename = true);
/* gives a cover name to CCS members */
void nameCCSMember(DeprecatedCreature &cr);
//end of ripped part

