
#include "../includes30.h"
#include "../constStringlootTypePool.h"

#include "../items/itemPool.h"
#include "../items/lootTypePool.h"
#include "../items/itemtype.h"
#include "../items/loottype.h"
vector<LootType *> loottype;
bool LootTypePool::lootTypePoolInitiated = false;

const int LootTypePool::lenpool() const
{
	return len(loottype);
}
LootTypePool lPool;
LootTypePool LootTypePool::getInstance()
{
	if (!lootTypePoolInitiated) {
		lPool = LootTypePool();
		lootTypePoolInitiated = true;
	}
	return lPool;
}
const string LootTypePool::getIdName(int i)
{
	return loottype[i]->get_idname();
}
void LootTypePool::delete_and_clear_pool()
{
	delete_and_clear(loottype);
}
#include "../items/item.h"
#include "../items/loot.h"
#include "../common/translateid.h"
const string LootTypePool::getName(const string& itemtypename_) {
	return loottype[getloottype(itemtypename_)]->get_name();
}
/* transforms a loot type id into the index of that loot type in the global vector */
int getloottype(int id)
{
	for (int i = 0; i < len(loottype); i++) if (loottype[i]->get_id() == id) return i;
	return -1;
}
/* transforms a loot type name into the index of that loot type in the global vector */
int getloottype(const string &idname)
{
	for (int i = 0; i < len(loottype); i++) if (loottype[i]->get_idname() == idname) return i;
	return -1;
}
#include "../items/lootTypePoolItem.h"
Item* getNewLoot(const string& newLootType, int num) {
	return new Loot(*loottype[getloottype(newLootType)], num);
}
string Loot::equip_title() const
{
	return loottype[getloottype(get_itemtypename())]->get_name();
}
const string& Loot::get_name() const
{
	return loottype[getloottype(get_itemtypename())]->get_name();
}
long Loot::get_fencevalue() const
{
	return loottype[getloottype(get_itemtypename())]->get_fencevalue();
}
bool Loot::is_stackable() const
{
	return loottype[getloottype(get_itemtypename())]->is_stackable();
}
bool Loot::no_quick_fencing() const
{
	return loottype[getloottype(get_itemtypename())]->no_quick_fencing();
}
bool Loot::is_cloth() const
{
	return loottype[getloottype(get_itemtypename())]->is_cloth();
}
Loot::Loot(const LootType& seed, int number) : Item(seed, number)
{ }
Loot::Loot(const std::string& inputXml) : Item(inputXml)
{
	/*CMarkup xml;
	xml.SetDoc(inputXml);
	xml.FindElem();
	xml.IntoElem();
	while(xml.FindElem())
	{
	std::string tag=xml.GetTagName();
	}*/
}
string Loot::showXml() const
{
	CMarkup xml;
	xml.AddElem(CONST_LOOT);
	xml.IntoElem();
	addBaseValues(xml);
	return xml.GetDoc();
}
Loot* Loot::split(int number)
{
	if (number > number_) number = number_;
	Loot* newi = clone();
	newi->number_ = number;
	number_ -= number;
	return newi;
}
bool Loot::merge(Item& i)
{
	if (is_stackable() && i.whatIsThis() == THIS_IS_LOOT && is_same_type(i))
	{
		increase_number(i.get_number());
		i.set_number(0);
		return true;
	}
	return false;
}
bool Loot::sort_compare_special(Item* other) const
{
	if (other)
	{
		int thisi = getloottype(get_itemtypename());
		int otheri = getloottype(other->get_itemtypename());
		if (thisi < otheri || otheri == -1) return false;
		else if (thisi > otheri&&otheri != -1) return true;
		else return false;
	}
	else return false;
}