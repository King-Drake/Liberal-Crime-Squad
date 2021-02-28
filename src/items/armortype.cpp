

#include "../includes35.h"
#include "../constStringarmortype.h"
#include <algorithm>


ArmorType::ArmorType(MCD_STR xmlstring)
	: ItemType(xmlstring),
	make_difficulty_(0), make_price_(0), deathsquad_legality_(false),
	can_get_bloody_(true), can_get_damaged_(true),
	stealth_value_(0), armor_body_(0), armor_head_(0), armor_limbs_(0), fireprotection_(false),
	cover_head_(false), cover_body_(true), cover_arms_(true), cover_legs_(true), conceal_face_(false),
	shortname_(CONST_armortypeUNDEF), shortname_future_(CONST_armortypeUNDEF), shortname_defined_(false), shortname_future_defined_(false),
	interrogation_basepower_(0), interrogation_assaultbonus_(0), interrogation_drugbonus_(0),
	professionalism_(2), conceal_weaponsize_(5),
	mask_(false), surprise_mask_(false), description_(CONST_armortypeUNDEF),
	quality_levels_(4), durability_(10)
{
	init(xmlstring);
}
ArmorType::ArmorType(const ArmorType& base, MCD_STR xmlstring)
	: ItemType(base, xmlstring),
	make_difficulty_(base.make_difficulty_), make_price_(base.make_price_), deathsquad_legality_(base.deathsquad_legality_),
	can_get_bloody_(base.can_get_bloody_), can_get_damaged_(base.can_get_damaged_),
	stealth_value_(base.stealth_value_), armor_body_(base.armor_body_), armor_head_(base.armor_head_), armor_limbs_(base.armor_limbs_), fireprotection_(base.fireprotection_),
	cover_head_(base.cover_head_), cover_body_(base.cover_body_), cover_arms_(base.cover_arms_), cover_legs_(base.cover_legs_), conceal_face_(base.conceal_face_),
	shortname_(base.shortname_), shortname_future_(base.shortname_future_), shortname_defined_(base.shortname_defined_), shortname_future_defined_(base.shortname_future_defined_),
	interrogation_basepower_(base.interrogation_basepower_), interrogation_assaultbonus_(base.interrogation_assaultbonus_), interrogation_drugbonus_(base.interrogation_drugbonus_),
	professionalism_(base.professionalism_), conceal_weaponsize_(base.conceal_weaponsize_),
	mask_(base.mask_), surprise_mask_(base.surprise_mask_), description_(base.description_),
	quality_levels_(base.quality_levels_), durability_(base.durability_)
{
	init(xmlstring);
}



void ArmorType::init(const MCD_STR& xmlstring)
{
	CMarkup xml;
	xml.SetDoc(xmlstring);
	xml.FindElem();
	xml.IntoElem();
	while (xml.FindElem()) //Loop over all the elements inside the armortype element.
	{
		std::string element = xml.GetTagName();
		int b;
		if (armorTypeInitTags.count(element)) {
			switch (armorTypeInitTags[element]) {
			case ENUM_tag_make_difficulty:
				make_difficulty_ = atoi(xml.GetData());
				break;
			case ENUM_tag_make_price:
				make_price_ = atoi(xml.GetData());
				break;
			case ENUM_tag_deathsquad_legality:
				b = stringtobool(xml.GetData());
				if (b == 1)
					deathsquad_legality_ = true;
				else if (b == 0)
					deathsquad_legality_ = false;
				/*else
				errorlog << INVALID_BOOLEAN_FOR_ARMOR << idname()
				<< COLON_DEATHSQUAD_LEGALITY << xml.GetData() << std::endl;*/
				break;
			case ENUM_tag_can_get_bloody:
				b = stringtobool(xml.GetData());
				if (b == 1)
					can_get_bloody_ = true;
				else if (b == 0)
					can_get_bloody_ = false;
				break;
			case ENUM_tag_can_get_damaged:
				b = stringtobool(xml.GetData());
				if (b == 1)
					can_get_damaged_ = true;
				else if (b == 0)
					can_get_damaged_ = false;
				break;
			case ENUM_tag_armor:
				xml.IntoElem();
				while (xml.FindElem())
				{
					element = xml.GetTagName();
					if (element == tag_body)
						armor_body_ = atoi(xml.GetData());
					else if (element == tag_head)
						armor_head_ = atoi(xml.GetData());
					else if (element == tag_limbs)
						armor_limbs_ = atoi(xml.GetData());
					else if (element == tag_fireprotection)
					{
						b = stringtobool(xml.GetData());
						if (b == 1)
							fireprotection_ = true;
						else if (b == 0)
							fireprotection_ = false;
						/*else
						errorlog << INVALID_BOOLEAN_FOR_ARMOR << idname()
						<< COLON_FIREPROTECTION << xml.GetData() << std::endl;*/
					}
					/*else
					errorlog << UNKNOWN_ELEMENT_FOR_ARMOR_TYPE << idname()
					<< COLON_ARMOR << element << endl;*/
				}
				xml.OutOfElem();
				break;
			case ENUM_tag_body_covering:
				xml.IntoElem();
				while (xml.FindElem())
				{
					element = xml.GetTagName();
					if (element == tag_body)
					{
						b = stringtobool(xml.GetData());
						if (b == 1)
							cover_body_ = true;
						else if (b == 0)
							cover_body_ = false;
						/*else
						errorlog << INVALID_BOOLEAN_FOR_ARMOR << idname()
						<< COLON_BODY_COVERING << xml.GetData() << std::endl;*/
					}
					else if (element == tag_head)
					{
						b = stringtobool(xml.GetData());
						if (b == 1)
							cover_head_ = true;
						else if (b == 0)
							cover_head_ = false;
						/*else
						errorlog << INVALID_BOOLEAN_FOR_ARMOR << idname()
						<< COLON_HEAD_COVERING << xml.GetData() << std::endl;*/
					}
					else if (element == tag_arms)
					{
						b = stringtobool(xml.GetData());
						if (b == 1)
							cover_arms_ = true;
						else if (b == 0)
							cover_arms_ = false;
						/*else
						errorlog << INVALID_BOOLEAN_FOR_ARMOR << idname()
						<< COLON_ARM_COVERING << xml.GetData() << std::endl;*/
					}
					else if (element == tag_legs)
					{
						b = stringtobool(xml.GetData());
						if (b == 1)
							cover_legs_ = true;
						else if (b == 0)
							cover_legs_ = false;
						/*else
						errorlog << INVALID_BOOLEAN_FOR_ARMOR << idname()
						<< COLON_LEG_COVERING << xml.GetData() << std::endl;*/
					}
					else if (element == tag_conceals_face)
					{
						b = stringtobool(xml.GetData());
						if (b == 1)
							conceal_face_ = true;
						else if (b == 0)
							conceal_face_ = false;
						/*else
						errorlog << INVALID_BOOLEAN_FOR_ARMOR << idname()
						<< COLON_CONCEAL_FACE << xml.GetData() << std::endl;*/
					}
					/*else
					errorlog << UNKNOWN_ELEMENT_FOR_ARMOR_TYPE << idname()
					<< COLON_ARMOR << element << endl;*/
				}
				xml.OutOfElem();
				break;
			case ENUM_tag_shortname:
				shortname_ = xml.GetData();
				shortname_defined_ = true;
				if (len(shortname_) > 14)
					shortname_.resize(14);
				break;
			case ENUM_tag_interrogation:
				xml.IntoElem();
				while (xml.FindElem())
				{
					if (element == tag_basepower)
						interrogation_basepower_ = atoi(xml.GetData());
					else if (element == tag_assaultbonus)
						interrogation_assaultbonus_ = atoi(xml.GetData());
					else if (element == tag_drugbonus)
						interrogation_drugbonus_ = atoi(xml.GetData());
					/*else
					errorlog << UNKNOWN_ELEMENT_FOR_ARMOR_TYPE << idname()
					<< COLON_INTERROGATION_ST << element << endl;*/
				}
				xml.OutOfElem();
				break;
			case ENUM_tag_professionalism:
				professionalism_ = atoi(xml.GetData());
				break;
			case ENUM_tag_conceal_weapon_size:
				conceal_weaponsize_ = atoi(xml.GetData());
				break;
			case ENUM_tag_stealth_value:
				stealth_value_ = atoi(xml.GetData());
				break;
			case ENUM_tag_mask:
				b = stringtobool(xml.GetData());
				if (b == 1)
					mask_ = true;
				else if (b == 0)
					mask_ = false;
				break;
			case ENUM_tag_surprise:
				b = stringtobool(xml.GetData());
				if (b == 1)
					surprise_mask_ = true;
				else if (b == 0)
					surprise_mask_ = false;
				break;
			case ENUM_tag_description:
				description_ = xml.GetData();
				break;
			case ENUM_tag_qualitylevels:
				quality_levels_ = max(1, atoi(xml.GetData()));
				break;
			case ENUM_tag_durability:
				durability_ = max(0, atoi(xml.GetData()));
				break;
			}
		}

	}
	if (!shortname_defined_ && len(name_) <= 14)
		shortname_ = name_;
}
int ArmorType::get_armor(int bodypart) const
{
	if (covers(bodypart))
	{
		switch (bodypart)
		{
		case BODYPART_HEAD:
			return armor_head_;
		case BODYPART_BODY:
			return armor_body_;
		case BODYPART_ARM_RIGHT:
		case BODYPART_ARM_LEFT:
			return armor_limbs_;
		case BODYPART_LEG_RIGHT:
		case BODYPART_LEG_LEFT:
			return armor_limbs_;
		}
	}
	return 0;
}
bool ArmorType::covers(int bodypart) const
{
	switch (bodypart)
	{
	case BODYPART_HEAD: return cover_head_;
	case BODYPART_BODY: return cover_body_;
	case BODYPART_ARM_RIGHT:
	case BODYPART_ARM_LEFT: return cover_arms_;
	case BODYPART_LEG_RIGHT:
	case BODYPART_LEG_LEFT: return cover_legs_;
	}
	return false;
}
const string& ArmorType::get_shortname() const
{
	if (shortname_future_defined_ && year >= 2100)
		return shortname_future_;
	else if (year >= 2100 && name_future_defined_ && len(name_future_) <= 14)
		return name_future_;
	else //if (shortname_defined_)
		return shortname_;
}
bool ArmorType::conceals_weaponsize(int weaponsize) const
{
	return (conceal_weaponsize_ >= weaponsize);
}