#pragma once
class Money : public Item
{
public:
	explicit Money(long amount) : amount_(amount) { }
	virtual thisItemIs whatIsThis() const { return THIS_IS_MONEY; }
	virtual Money* clone() const { return new Money(*this); }
	explicit Money(const std::string& inputXml);
	string showXml() const;
	virtual string equip_title() const;
	virtual const string& get_name() const { return get_itemtypename(); }
	virtual long get_fencevalue() const { return amount_ * number_; }
	virtual Money* split(int number);
	virtual bool merge(Item& i);
	virtual bool sort_compare_special(Item* other) const;
	long get_amount() const { return amount_; }
	void set_amount(long amount) { amount_ = amount; }
	void add_amount(long amount) { amount_ += amount; }
	void take_all_from(Money& more) { amount_ += more.amount_; more.amount_ = 0; }
	void flatten() { amount_ = amount_ * number_; number_ = 1; }
private:
	long amount_;
};
