
#include "../includes27.h"
#include "../constStringweapontype.h"
map<string, int> weaponTypeTags = {
	map<string, int>::value_type(tag_shortname, ENUM_tag_shortname),
	map<string, int>::value_type(tag_shortname_future, ENUM_tag_shortname_future),
	map<string, int>::value_type(tag_name_sub_1, ENUM_tag_name_sub_1),
	map<string, int>::value_type(tag_name_sub_2, ENUM_tag_name_sub_2),
	map<string, int>::value_type(tag_name_future_sub_1, ENUM_tag_name_future_sub_1),
	map<string, int>::value_type(tag_name_future_sub_2, ENUM_tag_name_future_sub_2),
	map<string, int>::value_type(tag_shortname_sub_1, ENUM_tag_shortname_sub_1),
	map<string, int>::value_type(tag_shortname_sub_2, ENUM_tag_shortname_sub_2),
	map<string, int>::value_type(tag_shortname_future_sub_1, ENUM_tag_shortname_future_sub_1),
	map<string, int>::value_type(tag_shortname_future_sub_2, ENUM_tag_shortname_future_sub_2),
	map<string, int>::value_type(tag_can_take_hostages, ENUM_tag_can_take_hostages),
	map<string, int>::value_type(tag_threatening, ENUM_tag_threatening),
	map<string, int>::value_type(tag_can_threaten_hostages, ENUM_tag_can_threaten_hostages),
	map<string, int>::value_type(tag_protects_against_kidnapping, ENUM_tag_protects_against_kidnapping),
	map<string, int>::value_type(tag_musical_attack, ENUM_tag_musical_attack),
	map<string, int>::value_type(tag_instrument, ENUM_tag_instrument),
	map<string, int>::value_type(tag_graffiti, ENUM_tag_graffiti),
	map<string, int>::value_type(tag_legality, ENUM_tag_legality),
	map<string, int>::value_type(tag_bashstrengthmod, ENUM_tag_bashstrengthmod),
	map<string, int>::value_type(tag_auto_break_locks, ENUM_tag_auto_break_locks),
	map<string, int>::value_type(tag_suspicious, ENUM_tag_suspicious),
	map<string, int>::value_type(tag_size, ENUM_tag_size),
	map<string, int>::value_type(tag_attack, ENUM_tag_attack),
};

WeaponType::WeaponType(MCD_STR xmlstring)
	: ItemType(xmlstring), name_sub_1_defined_(false), name_sub_2_defined_(false),
	name_future_sub_1_defined_(false), name_future_sub_2_defined_(false),
	shortname_(CONST_UNDEF), shortname_defined_(false), shortname_future_defined_(false),
	shortname_sub_1_defined_(false), shortname_sub_2_defined_(false),
	shortname_future_sub_1_defined_(false), shortname_future_sub_2_defined_(false),
	can_take_hostages_(false), threatening_(false), can_threaten_hostages_(true),
	protects_against_kidnapping_(true),
	musical_attack_(false), instrument_(false), legality_(2), bashstrengthmod_(1),
	suspicious_(true), size_(15), can_graffiti_(false), auto_break_lock_(false)
{
	CMarkup xml;
	xml.SetDoc(xmlstring);
	xml.FindElem();
	xml.IntoElem();
	attackst * attack;
	while (xml.FindElem()) //Loop over all the elements inside the weapontype element.
	{
		std::string element = xml.GetTagName();
		if (weaponTypeTags.count(element)) {
			int b;
			switch (weaponTypeTags[element]) {
			case ENUM_tag_shortname:

				shortname_ = xml.GetData();
				shortname_defined_ = true;
				break;
			case ENUM_tag_shortname_future:

				shortname_future_ = xml.GetData();
				shortname_future_defined_ = true;
				break;
			case ENUM_tag_name_sub_1:

				name_sub_1_ = xml.GetData();
				name_sub_1_defined_ = true;
				break;
			case ENUM_tag_name_sub_2:

				name_sub_2_ = xml.GetData();
				name_sub_2_defined_ = true;
				break;
			case ENUM_tag_name_future_sub_1:

				name_future_sub_1_ = xml.GetData();
				name_future_sub_1_defined_ = true;
				break;
			case ENUM_tag_name_future_sub_2:

				name_future_sub_2_ = xml.GetData();
				name_future_sub_2_defined_ = true;
				break;
			case ENUM_tag_shortname_sub_1:

				shortname_sub_1_ = xml.GetData();
				shortname_sub_1_defined_ = true;
				break;
			case ENUM_tag_shortname_sub_2:

				shortname_sub_2_ = xml.GetData();
				shortname_sub_2_defined_ = true;
				break;
			case ENUM_tag_shortname_future_sub_1:

				shortname_future_sub_1_ = xml.GetData();
				shortname_future_sub_1_defined_ = true;
				break;
			case ENUM_tag_shortname_future_sub_2:

				shortname_future_sub_2_ = xml.GetData();
				shortname_future_sub_2_defined_ = true;
				break;
			case ENUM_tag_can_take_hostages:
				b = stringtobool(xml.GetData());
				if (b == 1)
					can_take_hostages_ = true;
				else if (b == 0)
					can_take_hostages_ = false;
				break;
			case ENUM_tag_threatening:
				b = stringtobool(xml.GetData());
				if (b == 1)
					threatening_ = true;
				else if (b == 0)
					threatening_ = false;
				break;
			case ENUM_tag_can_threaten_hostages:
				b = stringtobool(xml.GetData());
				if (b == 1)
					can_threaten_hostages_ = true;
				else if (b == 0)
					can_threaten_hostages_ = false;
				break;
			case ENUM_tag_protects_against_kidnapping:
				b = stringtobool(xml.GetData());
				if (b == 1)
					protects_against_kidnapping_ = true;
				else if (b == 0)
					protects_against_kidnapping_ = false;
				break;
			case ENUM_tag_musical_attack:
				b = stringtobool(xml.GetData());
				if (b == 1)
					musical_attack_ = true;
				else if (b == 0)
					musical_attack_ = false;
				break;
			case ENUM_tag_instrument:
				b = stringtobool(xml.GetData());
				if (b == 1)
					instrument_ = true;
				else if (b == 0)
					instrument_ = false;
				break;
			case ENUM_tag_graffiti:
				b = stringtobool(xml.GetData());
				if (b == 1)
					can_graffiti_ = true;
				else if (b == 0)
					can_graffiti_ = false;
				break;
			case ENUM_tag_legality:
				legality_ = atoi(xml.GetData());
				break;
			case ENUM_tag_bashstrengthmod:
				bashstrengthmod_ = atoi(xml.GetData()) / 100.0;
				break;
			case ENUM_tag_auto_break_locks:
				b = stringtobool(xml.GetData());
				if (b == 1)
					auto_break_lock_ = true;
				else if (b == 0)
					auto_break_lock_ = false;
				break;
			case ENUM_tag_suspicious:
				b = stringtobool(xml.GetData());
				if (b == 1)
					suspicious_ = true;
				else if (b == 0)
					suspicious_ = false;
				break;
			case ENUM_tag_size:
				size_ = atoi(xml.GetData());
				break;
			case ENUM_tag_attack:
				attack = new attackst(xml.GetSubDoc());
				for (b = 0; b < len(attacks_) && attack->priority >= attacks_[b]->priority; b++);
				attacks_.insert(attacks_.begin() + b, attack);
				break;
			}
		}
		if (!shortname_defined_)
		{
			if ((uses_ammo() && len(name_) <= 9)
				|| len(name_) <= 14)
				shortname_ = name_;
		}
		else
		{
			if (len(shortname_) > 9 && uses_ammo())
				shortname_.resize(9);
			else if (len(shortname_) > 14)
				shortname_.resize(14);
		}
	}
}
map<string, int> attackstTags = {
	map<string, int>::value_type(tag_priority, ENUM_tag_priority),
	map<string, int>::value_type(tag_ranged, ENUM_tag_ranged),
	map<string, int>::value_type(tag_thrown, ENUM_tag_thrown),
	map<string, int>::value_type(tag_can_backstab, ENUM_tag_can_backstab),
	map<string, int>::value_type(tag_ammotype, ENUM_tag_ammotype),
	map<string, int>::value_type(tag_attack_description, ENUM_tag_attack_description),
	map<string, int>::value_type(tag_hit_description, ENUM_tag_hit_description),
	map<string, int>::value_type(tag_always_describe_hit, ENUM_tag_always_describe_hit),
	map<string, int>::value_type(tag_hit_punctuation, ENUM_tag_hit_punctuation),
	map<string, int>::value_type(tag_skill, ENUM_tag_skill),
	map<string, int>::value_type(tag_accuracy_bonus, ENUM_tag_accuracy_bonus),
	map<string, int>::value_type(tag_number_attacks, ENUM_tag_number_attacks),
	map<string, int>::value_type(tag_successive_attacks_difficulty, ENUM_tag_successive_attacks_difficulty),
	map<string, int>::value_type(tag_strength_min, ENUM_tag_strength_min),
	map<string, int>::value_type(tag_strength_max, ENUM_tag_strength_max),
	map<string, int>::value_type(tag_random_damage, ENUM_tag_random_damage),
	map<string, int>::value_type(tag_fixed_damage, ENUM_tag_fixed_damage),
	map<string, int>::value_type(tag_bruises, ENUM_tag_bruises),
	map<string, int>::value_type(tag_tears, ENUM_tag_tears),
	map<string, int>::value_type(tag_cuts, ENUM_tag_cuts),
	map<string, int>::value_type(tag_burns, ENUM_tag_burns),
	map<string, int>::value_type(tag_shoots, ENUM_tag_shoots),
	map<string, int>::value_type(tag_bleeding, ENUM_tag_bleeding),
	map<string, int>::value_type(tag_severtype, ENUM_tag_severtype),
	map<string, int>::value_type(tag_damages_armor, ENUM_tag_damages_armor),
	map<string, int>::value_type(tag_armorpiercing, ENUM_tag_armorpiercing),
	map<string, int>::value_type(tag_no_DR_for_limbs_chance, ENUM_tag_no_DR_for_limbs_chance),
	map<string, int>::value_type(tag_critical, ENUM_tag_critical),
	map<string, int>::value_type(tag_fire, ENUM_tag_fire),
};

attackst::attackst(MCD_STR xmlstring)
	: priority(1), ranged(false), thrown(false), ammotype(CONST_UNDEF), uses_ammo(false),
	attack_description(CONST_ASSAULTS), hit_description(CONST_tag_striking),
	always_describe_hit(false), can_backstab(false), hit_punctuation(singleDot),
	skill(SKILL_CLUB), accuracy_bonus(0), number_attacks(1),
	successive_attacks_difficulty(0), strength_min(5), strength_max(10),
	random_damage(1), fixed_damage(1), bruises(false), tears(false), cuts(false),
	burns(false), shoots(false), bleeding(false), severtype(0), damages_armor(false),
	armorpiercing(0), no_damage_reduction_for_limbs_chance(0)
{
	CMarkup xml;
	xml.SetDoc(xmlstring);
	xml.FindElem();
	xml.IntoElem();
	while (xml.FindElem()) //Loop over all the elements inside the vehicletype element.
	{
		std::string element = xml.GetTagName();
		if (attackstTags.count(element)) {
			int b;
			switch (attackstTags[element]) {

			case ENUM_tag_priority:
				priority = atoi(xml.GetData());
				break;

			case ENUM_tag_ranged:
				b = stringtobool(xml.GetData());
				if (b == 1)
					ranged = true;
				else if (b == 0)
					ranged = false;
				break;

			case ENUM_tag_thrown:
				b = stringtobool(xml.GetData());
				if (b == 1)
					thrown = true;
				else if (b == 0)
					thrown = false;
				break;

			case ENUM_tag_can_backstab:
				b = stringtobool(xml.GetData());
				if (b == 1)
					can_backstab = true;
				else if (b == 0)
					can_backstab = false;
				break;

			case ENUM_tag_ammotype:
				ammotype = xml.GetData();
				uses_ammo = true;
				break;

			case ENUM_tag_attack_description:
				attack_description = xml.GetData();
				break;

			case ENUM_tag_hit_description:
				hit_description = xml.GetData();
				break;

			case ENUM_tag_always_describe_hit:
				b = stringtobool(xml.GetData());
				if (b == 1)
					always_describe_hit = true;
				else if (b == 0)
					always_describe_hit = false;
				break;

			case ENUM_tag_hit_punctuation:
				hit_punctuation = xml.GetData();
				break;

			case ENUM_tag_skill:
				b = skill_string_to_enum(xml.GetData());
				if (b != -1)
					skill = b;
				break;

			case ENUM_tag_accuracy_bonus:
				accuracy_bonus = atoi(xml.GetData());
				break;

			case ENUM_tag_number_attacks:
				number_attacks = atoi(xml.GetData());
				break;

			case ENUM_tag_successive_attacks_difficulty:
				successive_attacks_difficulty = atoi(xml.GetData());
				break;

			case ENUM_tag_strength_min:
				strength_min = atoi(xml.GetData());
				break;

			case ENUM_tag_strength_max:
				strength_max = atoi(xml.GetData());
				break;

			case ENUM_tag_random_damage:
				random_damage = atoi(xml.GetData());
				break;

			case ENUM_tag_fixed_damage:
				fixed_damage = atoi(xml.GetData());
				break;

			case ENUM_tag_bruises:
				b = stringtobool(xml.GetData());
				if (b == 1)
					bruises = true;
				else if (b == 0)
					bruises = false;
				break;

			case ENUM_tag_tears:
				b = stringtobool(xml.GetData());
				if (b == 1)
					tears = true;
				else if (b == 0)
					tears = false;
				break;

			case ENUM_tag_cuts:
				b = stringtobool(xml.GetData());
				if (b == 1)
					cuts = true;
				else if (b == 0)
					cuts = false;
				break;

			case ENUM_tag_burns:
				b = stringtobool(xml.GetData());
				if (b == 1)
					burns = true;
				else if (b == 0)
					burns = false;
				break;

			case ENUM_tag_shoots:
				b = stringtobool(xml.GetData());
				if (b == 1)
					shoots = true;
				else if (b == 0)
					shoots = false;
				break;

			case ENUM_tag_bleeding:
				b = stringtobool(xml.GetData());
				if (b == 1)
					bleeding = true;
				else if (b == 0)
					bleeding = false;
				break;

			case ENUM_tag_severtype:
				b = severtype_string_to_enum(xml.GetData());
				if (b != -1)
					severtype = b;
				break;

			case ENUM_tag_damages_armor:
				b = stringtobool(xml.GetData());
				if (b == 1)
					damages_armor = true;
				else if (b == 0)
					damages_armor = false;
				break;

			case ENUM_tag_armorpiercing:
				armorpiercing = atoi(xml.GetData());
				break;

			case ENUM_tag_no_DR_for_limbs_chance:
				no_damage_reduction_for_limbs_chance = atoi(xml.GetData());
				break;

			case ENUM_tag_critical:
				xml.IntoElem();
				while (xml.FindElem())
				{
					element = xml.GetTagName();
					if (element == tag_chance)
						critical.chance = atoi(xml.GetData());
					else if (element == tag_hits_required)
						critical.hits_required = atoi(xml.GetData());
					else if (element == tag_random_damage)
					{
						critical.random_damage = atoi(xml.GetData());
						critical.random_damage_defined = true;
					}
					else if (element == tag_fixed_damage)
					{
						critical.fixed_damage = atoi(xml.GetData());
						critical.fixed_damage_defined = true;
					}
					else if (element == tag_severtype)
					{
						b = severtype_string_to_enum(xml.GetData());
						if (b != -1)
						{
							critical.severtype = b;
							critical.severtype_defined = true;
						}
					}
				}
				xml.OutOfElem();
				break;
			case ENUM_tag_fire:
				xml.IntoElem();
				while (xml.FindElem())
				{
					element = xml.GetTagName();
					if (element == tag_chance)
						fire.chance = atoi(xml.GetData());
					else if (element == tag_chance_causes_debris)
						fire.chance_causes_debris = atoi(xml.GetData());
				}
				xml.OutOfElem();
				break;

			default:
				break;
			}
		}

	}
	if (!bruises && !tears && !cuts && !burns && !shoots)
		bruises = true; //If no type specified, then bruise.
}
attackst::criticalst::criticalst()
	: chance(0), hits_required(1), random_damage(1), random_damage_defined(false),
	fixed_damage(1), fixed_damage_defined(false), severtype(0), severtype_defined(false)
{
}
attackst::firest::firest()
	: chance(0), chance_causes_debris(0)
{
}
WeaponType::~WeaponType()
{
	delete_and_clear(attacks_);
}
const string& WeaponType::get_name(unsigned subtype) const
{
	if (subtype == 0)
		return get_name();
	else if (subtype == 1)
	{
		if (name_future_sub_1_defined_ && year >= 2100)
			return name_future_sub_1_;
		else if (name_sub_1_defined_)
			return name_sub_1_;
		else
			return get_name();
	}
	else if (subtype == 2)
	{
		if (name_future_sub_2_defined_ && year >= 2100)
			return name_future_sub_2_;
		else if (name_sub_2_defined_)
			return name_sub_2_;
		else
			return get_name();
	}
	else
		return get_name(); //Reference to temporary. -XML
}
const string& WeaponType::get_shortname(unsigned subtype) const
{
	if (subtype > 2)
		return shortname_; //Reference to temporary. -XML
	else if (subtype == 1)
	{
		if (shortname_future_sub_1_defined_ && year >= 2100)
			return shortname_future_sub_1_;
		else if (year >= 2100 && name_future_sub_1_defined_ && len(name_future_sub_1_) <= 14) //Too long for ammo using weapons. -XML
			return name_future_sub_1_;
		else if (shortname_sub_1_defined_)
			return shortname_sub_1_;
		else if (name_sub_1_defined_ && len(name_sub_1_) <= 14) //Too long for ammo using weapons. -XML
			return name_sub_1_;
	}
	else if (subtype == 2)
	{
		if (shortname_future_sub_2_defined_ && year >= 2100)
			return shortname_future_sub_2_;
		else if (year >= 2100 && name_future_sub_2_defined_ && len(name_future_sub_2_) <= 14) //Too long for ammo using weapons. -XML
			return name_future_sub_2_;
		else if (shortname_sub_2_defined_)
			return shortname_sub_2_;
		else if (name_sub_2_defined_ && len(name_sub_2_) <= 14) //Too long for ammo using weapons. -XML
			return name_sub_2_;
	}
	if (shortname_future_defined_ && year >= 2100)
		return shortname_future_;
	else if (year >= 2100 && name_future_defined_ && len(name_future_) <= 14) //Too long for ammo using weapons. -XML
		return name_future_;
	else //if (shortname_defined_)
		return shortname_;
}
bool WeaponType::uses_ammo() const
{
	for (int i = 0; i < len(attacks_); i++)
		if (attacks_[i]->uses_ammo)
			return true;
	return false;
}
bool WeaponType::acceptable_ammo(const string& clipname) const
{
	for (int i = 0; i < len(attacks_); i++)
		if (attacks_[i]->ammotype == clipname)
			return true;
	return false;
}
bool WeaponType::is_ranged() const
{
	for (int i = 0; i < len(attacks_); i++)
		if (attacks_[i]->ranged)
			return true;
	return false;
}
bool WeaponType::is_throwable() const
{
	for (int i = 0; i < len(attacks_); i++)
		if (attacks_[i]->thrown)
			return true;
	return false;
}
bool WeaponType::is_legal() const
{
	return legality_ >= lawList[LAW_GUNCONTROL];
}
