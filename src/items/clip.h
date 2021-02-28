#pragma once
class Clip : public Item
{
public:
	virtual thisItemIs whatIsThis() const { return THIS_IS_CLIP; }
	explicit Clip(const ClipType& seed, int number = 1);
	virtual Clip* clone() const { return new Clip(*this); }
	explicit Clip(const std::string& inputXml);
	string showXml() const;
	virtual Clip* split(int number);
	virtual bool merge(Item& i);
	virtual bool sort_compare_special(Item* other) const;
	virtual string equip_title() const;
	virtual const string& get_name() const;
	virtual long get_fencevalue() const;
	int get_ammoamount() const;
private:
};
