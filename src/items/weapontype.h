#pragma once
struct attackst
{
	attackst(MCD_STR xmlstring);
	int priority;
	bool ranged;
	bool thrown;
	string ammotype;
	bool uses_ammo;
	string attack_description;
	string hit_description;
	bool always_describe_hit;
	bool can_backstab;
	string hit_punctuation;
	int skill;
	int accuracy_bonus;
	int number_attacks;
	int successive_attacks_difficulty;
	int strength_min;
	int strength_max;
	int random_damage;
	int fixed_damage;
	bool bruises;
	bool tears;
	bool cuts;
	bool burns;
	bool shoots;
	bool bleeding;
	int severtype;
	bool damages_armor;
	int armorpiercing;
	int no_damage_reduction_for_limbs_chance;
	struct criticalst
	{
		criticalst();
		int chance;
		int hits_required;
		int random_damage;
		bool random_damage_defined;
		int fixed_damage;
		bool fixed_damage_defined;
		int severtype;
		bool severtype_defined;
	} critical;
	struct firest
	{
		firest();
		int chance;
		int chance_causes_debris;
	} fire;
};
enum WeaponTypeFloat {
	FLOAT_BASHSTRENGTHMOD_,
};
enum WeaponTypeInt {
	INT_LEGALITY_,
	INT_SIZE_,
};
enum WeaponTypeString {
	STRING_NAME_SUB_1_,
	STRING_NAME_SUB_2_,
	STRING_NAME_FUTURE_SUB_1_,
	STRING_NAME_FUTURE_SUB_2_,
	STRING_SHORTNAME_,
	STRING_SHORTNAME_FUTURE_,
	STRING_SHORTNAME_SUB_1_,
	STRING_SHORTNAME_SUB_2_,
	STRING_SHORTNAME_FUTURE_SUB_1_,
	STRING_SHORTNAME_FUTURE_SUB_2_,

};
enum WeaponTypeBool {
	BOOL_CAN_TAKE_HOSTAGES_,
	BOOL_THREATENING_,
	BOOL_CAN_THREATEN_HOSTAGES_,
	BOOL_PROTECTS_AGAINST_KIDNAPPING_,
	BOOL_MUSICAL_ATTACK_,
	BOOL_INSTRUMENT_,
	BOOL_SUSPICIOUS_,
	BOOL_CAN_GRAFFITI_,
	BOOL_AUTO_BREAK_LOCK_,

};
class WeaponType : public ItemType
{
public:
	const bool get_specific_bool(const WeaponTypeBool b) const {
		switch (b) {
		case BOOL_CAN_TAKE_HOSTAGES_: return can_take_hostages_; break;
		case BOOL_THREATENING_: return threatening_; break;
		case BOOL_CAN_THREATEN_HOSTAGES_: return can_threaten_hostages_; break;
		case BOOL_PROTECTS_AGAINST_KIDNAPPING_: return protects_against_kidnapping_; break;
		case BOOL_MUSICAL_ATTACK_: return musical_attack_; break;
		case BOOL_INSTRUMENT_: return instrument_; break;
		case BOOL_SUSPICIOUS_: return suspicious_; break;
		case BOOL_CAN_GRAFFITI_: return can_graffiti_; break;
		case BOOL_AUTO_BREAK_LOCK_: return auto_break_lock_; break;
		default:// ERROR
			return false;
		}
	}
	virtual thisItemIs whatIsThis() const { return THIS_IS_WEAPON; }
	// Constructor to create a weapon type from xml.
	explicit WeaponType(MCD_STR xmlstring);
	~WeaponType();
	using ItemType::get_name;
	// Returns the name of the weapon type of given subtype, dependent on year.
	// Subtype may be 0, 1 or 2. Any other values will be the same as 0. If
	// subtypes 1 or 2 are not defined, subtype 0 will be used instead.
	// Subtype 0 is equivalent to ItemType::get_name() (actually just calls that).
	const string& get_name(unsigned subtype) const;
	// Return the shorter name.
	const string& get_shortname(unsigned subtype = 0) const;
	// Returns if the weapon type can be used to take hostages without causing
	// alarm. 
	// Returns the most liberal gun control law for the weapon to be legal.
	// -2, -1, 0, 1 and 2 for C+, C, M, L and L+ respectively. -3 always illegal.
	int get_legality() const { return legality_; }
	// Checks if the weapon type is legal.
	bool is_legal() const;
	// Returns the bash bonus provided by the weapon type.
	float get_bashstrengthmod() const { return bashstrengthmod_; }
	// Returns the size of the weapon type. Used for concealment under clothes.
	int get_size() const { return size_; }
	// Gives a reference to the vector of all possible attacks made by the
	// weapon type.
	const vector<attackst*>& get_attacks() const { return attacks_; }
	// Checks if the weapon uses ammo in any of its attacks.
	bool uses_ammo() const;
	// Checks if the given clip type is used by any of the weapon's attacks.
	bool acceptable_ammo(const ClipType& c) const { return acceptable_ammo(c.get_idname()); }
	bool acceptable_ammo(const string& clipname) const;
	// Checks if any of the weapon's attacks are ranged.
	bool is_ranged() const;
	// Checks if any of the weapon's attacks involve throwing the weapon.
	bool is_throwable() const;
private:
	string name_sub_1_;
	string name_sub_2_;
	bool name_sub_1_defined_;
	bool name_sub_2_defined_;
	string name_future_sub_1_;
	string name_future_sub_2_;
	bool name_future_sub_1_defined_;
	bool name_future_sub_2_defined_;
	string shortname_;
	string shortname_future_;
	bool shortname_defined_;
	bool shortname_future_defined_;
	string shortname_sub_1_;
	string shortname_sub_2_;
	bool shortname_sub_1_defined_;
	bool shortname_sub_2_defined_;
	string shortname_future_sub_1_;
	string shortname_future_sub_2_;
	bool shortname_future_sub_1_defined_;
	bool shortname_future_sub_2_defined_;
	bool can_take_hostages_;
	bool threatening_;
	bool can_threaten_hostages_;
	bool protects_against_kidnapping_;
	bool musical_attack_;
	bool instrument_;
	int legality_;
	float bashstrengthmod_;
	bool suspicious_;
	int size_;
	bool can_graffiti_;
	bool auto_break_lock_;
	vector<attackst*> attacks_;
};
