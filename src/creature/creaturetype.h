#pragma once
class CreatureType
{
public:
	// Creates a creature type from xml.
	explicit CreatureType(const std::string& xmlstring);
	friend void makecreature(DeprecatedCreature &cr, short type);
	// Remakes the creature into the creature type. Depends on being called
	// from makecreature currently.
	void make_creature(DeprecatedCreature& cr) const;
	const std::string& get_idname() const { return idname_; }
	long get_id() const { return id_; }
	short get_type() const { return type_; }
	Alignment get_alignment() const;
	int roll_gender() const;
	float roll_infiltration() const;
	std::string get_encounter_name() const;
	std::string get_type_name() const;
	// Gives the creature one of the creature type's possible weapons,
	// with clips if so defined.
	void give_weapon(DeprecatedCreature& cr) const;
	// May give a 9mm, .45 or .38 depending on gun control law and chance.
	void give_weapon_civilian(DeprecatedCreature& cr) const;
	// Gives the creature one of the creature type's possible armors.
	void give_armor(DeprecatedCreature& cr) const;
	static int s_number_of_creaturetypes;


	Interval attribute_points_;
	Interval attributes_[ATTNUM];
	Interval juice_;
	Interval money_;


private:
	std::string idname_;
	long id_;
	short type_; // This is a CreatureTypes enum value.
	struct WeaponsAndClips
	{
		WeaponsAndClips(const std::string & weapon, int weapons, const std::string & clip, int clips);
		WeaponsAndClips(CMarkup& xml, const string& owner);
		// TODO this name conflicts with the vector<WeaponType *> weapontype, which is interfering with refactor efforts
		std::string weapon_type_str;
		Interval number_weapons;
		std::string cliptype;
		Interval number_clips;
	};
	std::vector<WeaponsAndClips> weapons_and_clips_;
	std::vector<std::string> armortypes_;
	std::string type_name_;
	std::string encounter_name_;
	Interval age_;
	bool alignment_public_mood_;
	Alignment alignment_;
	int gender_liberal_;      // Only gender_liberal_ is used now determining
	int gender_conservative_; // starting gender.
	Interval infiltration_;
	Interval skills_[SKILLNUM];

	int seethroughdisguise_;
	int seethroughstealth_;
	bool istalkreceptive_;
	bool iskidnap_resistant_;
	bool isreports_to_police_;
};
/* transforms a CreatureTypes value into a pointer to that creature type */
const CreatureType* getcreaturetype(short crtype);
// This declaration is necessary for the function DeprecatedCreature::get_type_name() to work.
// It isn't part of the CreatureType class or creaturetype.cpp file, it's implemented elsewhere.
/* transforms a creature type name into a pointer to that creature type */
const CreatureType* getcreaturetype(const std::string& crtype);

