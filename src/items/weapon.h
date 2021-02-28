#pragma once
class Weapon : public Item
{
public:
	bool Weapon::get_specific_bool(const WeaponTypeBool b) const;
	explicit Weapon(const WeaponType& seed, int number = 1);
	virtual thisItemIs whatIsThis() const { return THIS_IS_WEAPON; }
	virtual Weapon* clone() const { return new Weapon(*this); }
	explicit Weapon(const std::string& inputXml);
	string showXml() const;
	virtual string equip_title() const;
	virtual Weapon* split(int number);
	virtual bool merge(Item& i);
	virtual bool sort_compare_special(Item* other) const;
	const string& get_name() const;
	const string& get_name(unsigned subtype) const;
	const string& get_shortname(unsigned subtype = 0) const;
	long get_fencevalue() const;
	int get_legality() const;
	float get_bashstrengthmod() const;
	int get_size() const;
	// Tries to reload the weapon with clip. If the weapon is reloaded, clip's
	// number is reduced by one.
	bool reload(Clip& clip);
	int get_ammoamount() const { return ammo_; }
	void decrease_ammo(int d) { ammo_ -= d; }
	const string& get_loaded_cliptypename() const { return loaded_cliptype_; }
	const attackst* get_attack(bool force_ranged, bool force_melee, bool force_no_reload) const;
	bool acceptable_ammo(const Item& c) const;
	bool acceptable_ammo(const Clip& c) const;
	bool acceptable_ammo(const ClipType& c) const;
	bool uses_ammo() const;
	bool is_ranged() const;
	bool is_throwable() const;
	bool is_legal() const;
private:
	string loaded_cliptype_;
	int ammo_;
};
