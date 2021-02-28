#pragma once
enum thisItemIs {
	THIS_IS_WEAPON,
	THIS_IS_ARMOR,
	THIS_IS_CLIP,
	THIS_IS_LOOT,
	THIS_IS_MONEY
};
class ItemType
{
public:
	//ItemType() { }
	// (Sub-?)Constructor for creating an item type from xml.
	explicit ItemType(MCD_STR xmlstring);
	// (Sub-?)Constructor for creating an item type from xml using another
	// item type for default values.
	ItemType(const ItemType& base, MCD_STR xmlstring);
	virtual ~ItemType() { }
	// Returns the unique (unless someone messed up an xml-file) identifying
	// name of the item type.
	const string& get_idname() const { return idname_; }
	// Return the id number. Id number may not be consistent between a
	// save'n'load if an xml-file has been changed.
	long get_id() const { return id_; }
	// Functions to identify the derived classes.
	virtual thisItemIs whatIsThis() const = 0;
	// Returns the name of item type, dependent on the year.
	virtual const string& get_name() const;
	// Returns the fencevalue.
	virtual long get_fencevalue() const { return fencevalue_; }
	// Keeps count of the number of item types. Used for assigning id number.
	static int number_of_itemtypes;
protected:
	string name_;
	string name_future_;
	bool name_future_defined_;
	//string& idname() { return idname_; }
	//const string& idname() const { return idname_; }
	//long& id() { return id_; }
	//const long& id() const { return id_; }
	//string& name() { return name_; }
	//const string& name() const { return name_; }
	//string& name_future() { return name_future_; }
	//const string& name_future() const { return name_future_; }
	//bool& name_future_defined() { return name_future_defined_; }
	//const bool& name_future_defined() const { return name_future_defined_; }
	//long& fencevalue() { return fencevalue_; }
	//const long& fencevalue() const { return fencevalue_; }
private:
	// Used by constructors to initialize values from xml.
	void init(const MCD_STR& xmlstring);
	//short type;
	string idname_;
	long id_;
	long fencevalue_;
};
