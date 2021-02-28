
#include "../includes11.h"
#include "../constStringshop.h"
#include <algorithm>

 ShopOption::ShopOption() : description_(undefined), letter_(0), letter_defined_(false)
 { }
 Shop::Shop(MCD_STR xmlstring)
	 : allow_selling_(false), only_sell_legal_(true), increase_prices_with_illegality_(false),
	 fullscreen_(false), sell_masks_(false)
 {
	 init(xmlstring);
 }
 Shop::Shop(MCD_STR xmlstring, bool fullscreen, bool only_sell_legal,
	 bool increase_prices_with_illegality)
	 : allow_selling_(false), only_sell_legal_(only_sell_legal),
	 increase_prices_with_illegality_(increase_prices_with_illegality),
	 fullscreen_(fullscreen), sell_masks_(false)
 {
	 init(xmlstring);
 }

 void Shop::init(const MCD_STR &xmlstring)
 {
	 CMarkup xml;
	 xml.SetDoc(xmlstring);
	 xml.FindElem();
	 xml.IntoElem();
	 while (xml.FindElem())
	 {
		 std::string tag = xml.GetTagName();
		 if (shopInitTags.count(tag)) {
			 switch (shopInitTags[tag]) {
				 int b;
			 case ENUM_tag_only_sell_legal_items:

				 b = stringtobool(xml.GetData());
				 if (b == 1 || b == 0) only_sell_legal_ = b;
				 break;
			 case ENUM_tag_fullscreen:

				 b = stringtobool(xml.GetData());
				 if (b == 1 || b == 0) fullscreen_ = b;
				 break;
			 case ENUM_tag_allow_selling:

				 b = stringtobool(xml.GetData());
				 if (b == 1 || b == 0) allow_selling_ = b;
				 break;
			 case ENUM_tag_increase_prices_with_illegality:

				 b = stringtobool(xml.GetData());
				 if (b == 1 || b == 0) increase_prices_with_illegality_ = b;
				 break;
			 case ENUM_tag_department:

				 options_.push_back(new Shop(xml.GetSubDoc(), fullscreen_, only_sell_legal_,
					 increase_prices_with_illegality_));
				 break;
			 case ENUM_tag_entry:
				 description_ = xml.GetData();
				 break;
			 case ENUM_tag_exit:
				 exit_ = xml.GetData();
				 break;
			 case ENUM_tag_sell_masks:

				 b = stringtobool(xml.GetData());
				 if (b == 1 || b == 0) sell_masks_ = b;
				 break;
			 case ENUM_tag_letter:
				 letter_ = xml.GetData()[0];
				 if (97 <= letter_ && letter_ <= 122) //Check it is a letter.
					 letter_defined_ = true;
				 else if (65 <= letter_ && letter_ <= 90)
				 {
					 letter_ += 32;
					 letter_defined_ = true;
				 }
				 else if (letter_ == '!') //Allow special character.
					 letter_defined_ = true;
				 break;
			 case ENUM_tag_item:

				 options_.push_back(new ShopItem(xml.GetSubDoc(), only_sell_legal_,
					 increase_prices_with_illegality_));
				 break;

			 }
		 }
	 }
 }
 Shop::~Shop()
 {
	 delete_and_clear(options_);
 }
 void Shop::enter(Deprecatedsquadst& customers) const
 {
	 music.play(MUSIC_SHOPPING);
	 int buyer = 0;
	 choose(customers, buyer);
 }
 void Shop::choose(Deprecatedsquadst& customers, int& buyer) const
 {
	 if (fullscreen_) browse_fullscreen(customers, buyer);
	 else browse_halfscreen(customers, buyer);
 }
 void Shop::browse_fullscreen(Deprecatedsquadst& customers, int& buyer) const
 {
	 int page = 0;
	 std::vector<ShopOption*> available_options = options_;
	 available_options.erase(remove_if(available_options.begin(),
		 available_options.end(),
		 std::not1(std::mem_fun(&ShopOption::display))),
		 available_options.end());
	 int c;
	 do
	 {
		 printFullscreenHeader(customers.squad[buyer]->getNameAndAlignment().name);
		 //Write wares and prices
		 for (int p = page * 19; p < len(available_options) && p < page * 19 + 19; p++)
		 {
			 if (available_options[p]->is_available()) {
				 printFullscreenOption(p, available_options[p]->get_description_fullscreen());
			 }
		 }
		 printFullscreenFooter(std::string(customers.squad[buyer]->getNameAndAlignment().name), exit_);
		 
		 c = getkeyAlt();

		 //PAGE UP
		 if (is_page_up(c) && page > 0) page--;
		 //PAGE DOWN
		 if (is_page_down(c) && (page + 1) * 19 < len(available_options)) page++;
		 if (c >= 'a'&&c <= 's')
		 {
			 int p = page * 19 + c - 'a';
			 if (p < len(available_options) && available_options[p]->is_available())
				 available_options[p]->choose(customers, buyer);
			 break;
		 }
	 } while (!(c == 'x' || c == ENTER || c == ESC || c == SPACEBAR));
 }
 int fenceselect(Deprecatedsquadst& customers)
 {
	 int ret = 0, page = 0;
	 consolidateLoot(customers.squad[0]->base);

	 vector<int> selected(LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base), 0);
	 while (true)
	 {
		 printFenceHeader(ret);
		 printparty();
		 for (int l = page * 18, i = 0; l < LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base) && l < page * 18 + 18; l++, i++)
		 {
			 printLootForSale(i, selected[l], getLootNumber(customers.squad[0]->base, l), getLootTitle(customers.squad[0]->base, l));


		 }
		 //PAGE UP
		 printPageOptions(page > 0, (page + 1) * 18 < LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base));
		 printSellingFooter();
		 int c = getkeyAlt();
		 if (c >= 'a' && c <= 'r')
		 {
			 int slot = c - 'a' + page * 18;
			 if (slot >= 0 && slot < LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base))
			 {
				 if (selected[slot])
				 {
					 ret -= getFenceValueLocation(customers.squad[0]->base, slot) * selected[slot];
					 selected[slot] = 0;
				 }
				 else
				 {
					 if (!getCanBeSoldLocation(customers.squad[0]->base, slot))
					 {
						 printparty();
						 printCantSellDamage();
						 pressAnyKey();
					 }
					 else
					 {
						 if (getLocationLootNumber(customers.squad[0]->base, slot) > 1)
							 selected[slot] = prompt_amount(0, getLocationLootNumber(customers.squad[0]->base, slot));
						 else selected[slot] = 1;
						 ret += getFenceValueLocation(customers.squad[0]->base, slot) * selected[slot];
					 }
				 }
			 }
		 }
		 if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
		 //PAGE UP
		 if (is_page_up(c) && page > 0)
			 page--;
		 //PAGE DOWN
		 if (is_page_down(c) &&
			 (page + 1) * 18 < LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base))
			 page++;
	 }
	 for (int l = LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base) - 1; l >= 0; l--)
	 {
		 if (selected[l])
		 {
			 decreateLocationLoot(customers.squad[0]->base, l, selected[l]);

		 }
	 }
	 return ret;
 }
 void sell_loot(Deprecatedsquadst& customers)
 {
	 int partysize = customers.squadsize();
	 while (true)
	 {
		 printSellLootHeader(LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base), partysize, party_status);
		 locheader();
		 printparty();

		 int c = getkeyAlt();
		 if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
		 if (c == 'e'&&customers.squad[0]->base != -1)
			 equipLoot(customers.squad[0]->base, -1);
		 if (c == 'w' || c == 'a' || c == 'c')
		 {
			 printReallySellAllThese(c);
			 if (getkeyAlt() != 'y') c = 0; //no sale
		 }
		 if ((c == 'w' || c == 'c' || c == 'l' || c == 'a' || c == 'f') &&
			 LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base))
		 {
			 int fenceamount = 0;
			 if (c == 'f') fenceamount = fenceselect(customers);
			 else
			 {
				 for (int l = LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base) - 1; l >= 0; l--)
				 {
					 if (c == 'w' && whatIsThisItemInLocation(customers.squad[0]->base, l) == THIS_IS_WEAPON
						 && getCanBeSoldLocation(customers.squad[0]->base, l))
					 {
						 fenceamount += getFenceValueLocation(customers.squad[0]->base, l)
							 * getLocationLootNumber(customers.squad[0]->base, l);
						 deleteLocationLoot(customers.squad[0]->base, l);
					 }
					 else if (c == 'c' && whatIsThisItemInLocation(customers.squad[0]->base, l) == THIS_IS_ARMOR
						 && getCanBeSoldLocation(customers.squad[0]->base, l))
					 {
						 fenceamount += getFenceValueLocation(customers.squad[0]->base, l)
							 * getLocationLootNumber(customers.squad[0]->base, l);
						 deleteLocationLoot(customers.squad[0]->base, l);
					 }
					 else if (c == 'a' && whatIsThisItemInLocation(customers.squad[0]->base, l) == THIS_IS_CLIP
						 && getCanBeSoldLocation(customers.squad[0]->base, l))
					 {
						 fenceamount += getFenceValueLocation(customers.squad[0]->base, l)
							 * getLocationLootNumber(customers.squad[0]->base, l);
						 deleteLocationLoot(customers.squad[0]->base, l);
					 }
					 else if (c == 'l' && whatIsThisItemInLocation(customers.squad[0]->base, l) == THIS_IS_LOOT
						 && getCanBeSoldLocation(customers.squad[0]->base, l))
					 {
						 if (!noQuickFenceLocation(customers.squad[0]->base, l))
						 {
							 fenceamount += getFenceValueLocation(customers.squad[0]->base, l)
								 * getLocationLootNumber(customers.squad[0]->base, l);
							 deleteLocationLoot(customers.squad[0]->base, l);
						 }
					 }
				 }
			 }
			 if (fenceamount)
			 {
				 printFenceAmount(fenceamount);
				 pressAnyKey();
				 ledger.add_funds(fenceamount, INCOME_PAWN);
			 }
		 }
	 }
 }

 void choose_buyer(Deprecatedsquadst& customers, int& buyer)
 {
	 party_status = -1;
	 int partysize = customers.squadsize();
	 if (partysize <= 1) return;
	 while (true)
	 {
		 printparty();
		 printChooseALiberalTo();
		 int c = getkeyAlt();
		 if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) return;
		 if (c >= '1'&&c <= partysize + '1' - 1)
		 {
			 buyer = c - '1';
			 return;
		 }
	 }
 }
 
 // Removing the subsequent references to location will be difficult.
 void maskselect(DeprecatedCreature &buyer)
 {
	 short maskindex = -1;
	 std::vector<int> masktype;
	 std::vector<string> masknames;
	 std::vector<string> maskdescriptions;
	 for (int a = 0; a < len(armortype); a++)
	 {
		 if (armortype[a]->is_mask() && !armortype[a]->is_surprise_mask()) {
			 masktype.push_back(a);
			 masknames.push_back(armortype[a]->get_name());
			 maskdescriptions.push_back(armortype[a]->get_description());
		 }
	 }
	 int page = 0;
	 int c;
	 do
	 {
	//	 for (int p = page * 19, y = 2; p < len(masktype) && p < page * 19 + 19; p++, y++) {

	//	 }
		 printMaskOptions(page, buyer.getNameAndAlignment().name, masktype, masknames, maskdescriptions);


		 c = getkeyAlt();

		 //PAGE UP
		 if (is_page_up(c) && page > 0) {
			 page--;
		 }else
		 //PAGE DOWN
		 if (is_page_down(c) && (page + 1) * 19 < len(masktype)) { 
			 page++; 
		 }else
		 if (c >= 'a'&&c <= 's')
		 {
			 int p = page * 19 + c - 'a';
			 if (p < len(masktype))
			 {
				 maskindex = masktype[p];
			 }
		 }else
		 if (c == 'z')
		 {
			 for (int i = 0; i < len(armortype); i++) {
				 if (armortype[i]->is_mask() && armortype[i]->is_surprise_mask())
				 {
					 masktype.push_back(i);
				 }
			 }
			 maskindex = pickrandom(masktype);
		 }
	 } while (maskindex == -1 && !(c == 'z' || c == 'x' || c == ENTER || c == ESC || c == SPACEBAR));
	 if (maskindex != -1 && ledger.get_funds() >= 15)
	 {
		 Armor a = Armor(maskindex);
		 buyer.give_armor(a, &location[buyer.base]->loot);
		 ledger.subtract_funds(15, EXPENSE_SHOPPING);
	 }
 }
 
 void Shop::browse_halfscreen(Deprecatedsquadst& customers, int& buyer) const
 {
	 int page = 0, partysize = customers.squadsize();
	 std::vector<ShopOption*> available_options = options_;
	 available_options.erase(remove_if(available_options.begin(),
		 available_options.end(),
		 std::not1(std::mem_fun(&ShopOption::display))),
		 available_options.end());
	 int c;
	 vector<char> unusable_letters;
	 unusable_letters.push_back('b');
	 unusable_letters.push_back('e');
	 if (allow_selling_) { unusable_letters.push_back('s'); }
	 if (sell_masks_) { unusable_letters.push_back('m'); }
	 for (int i = 0; i < len(available_options); i++) {
		 if (available_options[i]->letter_defined_) {
			 unusable_letters.push_back(available_options[i]->showletter());
		 }
	 }
	 do
	 {
		 printBrowseHalfscreenHeader(customers.squad[buyer]->getNameAndAlignment().name);
		 locheader();
		 printparty();
		 //Write wares and prices
		 int y = 0;
		 bool left_side = true;
		 int taken_letters = 0;
		 for (int p = page * 19; p < len(available_options) && p < page * 19 + 20; p++)
		 {



			 if (!available_options[p]->letter_defined_)
			 {
				 // Find an available letter to use for this ware.
				 bool done = false;
				 while (taken_letters < 27 && !done)
				 {
					 done = true;
					 for (char k : unusable_letters) {
						 if ('a' + taken_letters == k) {
							 taken_letters++;
							 done = false;
						 }
					 }
				 }
				 available_options[p]->letter_ = 'a' + taken_letters;
				 taken_letters++;
			 }
			 if (available_options[p]->is_available())
			 {
				 printShopOptions(y, left_side, available_options[p]->showletter(), available_options[p]->get_description_halfscreen());
			 }


			 if (!left_side) {
				 y++;
			 }
			 left_side = !left_side;
		 }

		 LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base);
		 printOptionsMiddle(y, sell_masks_ && ledger.get_funds() >= 15, left_side, allow_selling_, LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base));

		 y += 2 + (left_side ? 0 : 1);

		 printShopFooter(y, party_status, partysize, exit_);

		 c = getkeyAlt();

		 for (int i = 0; i < len(available_options); i++) {
			 if (c == available_options[i]->letter_)
			 {
				 available_options[i]->choose(customers, buyer); break;
			 }
		 }
		 if (c == 'e' && customers.squad[0]->base != -1)
		 {
			 equipLoot(customers.squad[0]->base, -1);
		 }
		 else if (c == 's'&&allow_selling_&&LocationsPool::getInstance().get_specific_integer(INT_LENLOOT, customers.squad[0]->base))
		 {
			 sell_loot(customers);
		 }
		 else if (c == 'm'&&sell_masks_&&ledger.get_funds() >= 15)
		 {
			 maskselect(*customers.squad[buyer]);
		 }
		 else if (c == 'b') {
			 choose_buyer(customers, buyer);
		 }
		 else if (c == '0') {
			 party_status = -1;
		 }
		 else if (c >= '1'&&c <= '6')
		 {
			 if (customers.squad[c - '1'] != NULL)
			 {
				 if (party_status == c - '1')
					 fullstatus(party_status);
				 else party_status = c - '1';
			 }
		 }
	 }
	 while (!(c == 'x' || c == ENTER || c == ESC || c == SPACEBAR));
 }
 bool Shop::is_available() const
 {  //Disable shop (department) if it has nothing to sell.
	 bool r = false;
	 for (int i = 0; i < len(options_) && !(r = options_[i]->display()); i++);
	 return r;
 }

 Shop::ShopItem::ShopItem(MCD_STR xmlstring, bool only_sell_legal,
	 bool increase_price_with_illegality)
	 : price_(0), only_sell_legal_(only_sell_legal),
	 increase_price_with_illegality_(increase_price_with_illegality),
	 description_defined_(false)
 {
	 CMarkup xml;
	 xml.SetDoc(xmlstring);
	 xml.FindElem();
	 xml.IntoElem();
	 while (xml.FindElem())
	 {
		 std::string tag = xml.GetTagName();
		 if (shopItemTags.count(tag)) {
			 switch (shopItemTags[tag]) {

			 case ENUM_tag_class:
				 if (xml.GetData() == tag_WEAPON)
					 itemclass_ = WEAPON;
				 else if (xml.GetData() == tag_CLIP)
					 itemclass_ = CLIP;
				 else if (xml.GetData() == tag_ARMOR)
					 itemclass_ = ARMOR;
				 else if (xml.GetData() == tag_LOOT)
					 itemclass_ = LOOT;
				 break;
			 case ENUM_tag_type:
				 itemtypename_ = xml.GetData();
				 break;
			 case ENUM_tag_description:
				 description_ = xml.GetData();
				 description_defined_ = true;
				 break;
			 case ENUM_tag_price:
				 price_ = atoi(xml.GetData());
				 break;
			 case ENUM_tag_sleeperprice:
				 sleeperprice_ = atoi(xml.GetData());
				 break;
			 case ENUM_tag_letter:
				 letter_ = xml.GetData()[0];
				 if (97 <= letter_ && letter_ <= 122) //Check it is a letter.
					 letter_defined_ = true;
				 else if (65 <= letter_ && letter_ <= 90)
				 {
					 letter_ += 32;
					 letter_defined_ = true;
				 }
				 else if (letter_ == '!') //Allow special character.
					 letter_defined_ = true;
				 break;


			 }
		 }
	 }
 }

 bool Shop::ShopItem::is_available() const
 {
	 return valid_item() && (!only_sell_legal_ || legal()) && can_afford();
 }
 const std::string Shop::ShopItem::get_description_halfscreen() const
 {
	 std::string r = get_description();
	 r.resize(26, ' ');
	 r += paranthesisDollar + tostring(adjusted_price()) + CLOSE_PARENTHESIS;
	 return r;
 }
 const std::string Shop::ShopItem::get_description_fullscreen() const
 {
	 std::string r = get_description();
	 r.resize(35, ' ');
	 r += asMoney(adjusted_price());
	 return r;
 }
 bool Shop::ShopItem::display() const
 {
	 return(valid_item() && (!only_sell_legal_ || legal()));
 }
 bool Shop::ShopItem::can_afford() const
 {
	 return(adjusted_price() <= ledger.get_funds());
 }
 bool Shop::ShopItem::legal() const
 {
	 bool r = true;
	 switch (itemclass_)
	 {
	 case WEAPON: r = weapontype[getweapontype(itemtypename_)]->is_legal(); break;
	 case CLIP:
		 // Decide if clip is legal by looping through all weapons and
		 // testing if there exists a weapon such that it is legal and
		 // it can take this clip. If no legal weapon can take this type
		 // of clip, the clip is implicitly illegal as well.
		 r = false;
		 for (int i = 0; i < len(weapontype) && !r; i++)
			 if (weapontype[i]->acceptable_ammo(itemtypename_) && weapontype[i]->is_legal())
				 r = true;
		 break;
	 case ARMOR:       //Can't be illegal.
	 case LOOT: break; //Can't be illegal.
	 }
	 return r;
 }
 bool Shop::ShopItem::valid_item() const
 {
	 int i = -1;
	 switch (itemclass_)
	 {
	 case WEAPON: i = getweapontype(itemtypename_); break;
	 case CLIP:   i = getcliptype(itemtypename_); break;
	 case ARMOR:  i = getarmortype(itemtypename_); break;
	 case LOOT:   i = getloottype(itemtypename_); break;
	 }
	 return(i != -1);
 }
 int Shop::ShopItem::adjusted_price() const
 {
	 int p = price_;
	 if (increase_price_with_illegality_&&itemclass_ == WEAPON && valid_item())
		 for (int i = weapontype[getweapontype(itemtypename_)]->get_legality(); i < lawList[LAW_GUNCONTROL]; i++)
			 p *= 2;
	 return p;
 }
 const std::string Shop::ShopItem::get_description() const
 {
	 if (description_defined_) return description_;
	 else switch (itemclass_)
	 {
	 case WEAPON: return weapontype[getweapontype(itemtypename_)]->get_name();
	 case CLIP:   return cliptype[getcliptype(itemtypename_)]->get_name();
	 case ARMOR:  return armortype[getarmortype(itemtypename_)]->get_name();
	 case LOOT:   return LootTypePool::getInstance().getName(itemtypename_); // loottype[getloottype(itemtypename_)]->get_name();
	 default:     return description_; // Will be undefined
	 }
 }

 void Shop::ShopItem::choose(Deprecatedsquadst& customers, int& buyer) const
 {
	 if (!is_available()) return;
	 ledger.subtract_funds(adjusted_price(), EXPENSE_SHOPPING);
	 switch (itemclass_)
	 {
	 case WEAPON: {
		 Weapon* i = new Weapon(*weapontype[getweapontype(itemtypename_)]);
		 customers.squad[buyer]->give_weapon(*i, &location[customers.squad[0]->base]->loot);
		 if (i->empty()) delete i;
		 else location[customers.squad[0]->base]->loot.push_back(i);
		 break; }
	 case CLIP: {
		 Clip* i = new Clip(*cliptype[getcliptype(itemtypename_)]);
		 customers.squad[buyer]->take_clips(*i, 1);
		 if (i->empty()) delete i;
		 else location[customers.squad[0]->base]->loot.push_back(i);
		 break; }
	 case ARMOR: {
		 Armor* i = new Armor(getarmortype(itemtypename_));
		 customers.squad[buyer]->give_armor(*i, &location[customers.squad[0]->base]->loot);
		 if (i->empty()) delete i;
		 else location[customers.squad[0]->base]->loot.push_back(i);
		 break; }
	 case LOOT: {
		 location[customers.squad[0]->base]->loot.push_back(getNewLoot(itemtypename_));
		 break; }
	 }
 }