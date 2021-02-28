#pragma once
class LootType : public ItemType
{
public:
	virtual thisItemIs whatIsThis() const { return THIS_IS_LOOT; }
	explicit LootType(MCD_STR xmlstring);
	// Returns if the loot type should be stacked or not.
	bool is_stackable() const { return stackable_; }
	// Returns if the loot should be skipped when quick fencing all loot.
	bool no_quick_fencing() const { return no_quick_fencing_; }
	// Returns if the loot is usable as cloth when making clothing.
	bool is_cloth() const { return cloth_; }
private:
	bool stackable_;
	bool no_quick_fencing_;
	bool cloth_;
};
