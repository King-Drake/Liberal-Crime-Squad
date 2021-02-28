#pragma once
class ClipType : public ItemType
{
public:
	explicit ClipType(MCD_STR xmlstring);
	thisItemIs whatIsThis() const { return THIS_IS_CLIP; }
	int get_ammoamount() const { return ammo_; }
private:
	int ammo_;
};
