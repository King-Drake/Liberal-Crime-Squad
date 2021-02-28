


#include "../includes48.h"
#include "../constStringcreaturetype.h"
#include <algorithm>

Weapon& DeprecatedCreature::weapon_none()
{
	static Weapon unarmed(*weapontype[getweapontype(tag_WEAPON_NONE)]);
	return unarmed;
}
// This would normally be inlined inside the DeprecatedCreature class in creature.h, but the DeprecatedCreature class
// has to be before creaturetype
std::string DeprecatedCreature::get_type_name() const { return getcreaturetype(type_idname)->get_type_name(); }
// Assign a value to an Interval from a string or log error.
void assign_interval(Interval& i, const std::string& value,
	const std::string& owner, const std::string& element)
{
	if (!i.set_interval(value))
		xmllog.log(INVALID_INTERVAL + element + CONST_X_IN_ + owner + CONST_COLON + value);
}
int CreatureType::s_number_of_creaturetypes = 0;
CreatureType::WeaponsAndClips::WeaponsAndClips(const std::string& weapon, int weapons, const std::string& clip, int clips)
	: weapon_type_str(weapon), number_weapons(weapons),
	cliptype(clip), number_clips(clips)
{
}

CreatureType::CreatureType(const std::string& xmlstring)
	: age_(18, 57), alignment_public_mood_(true),
	attribute_points_(40),
	gender_liberal_(GENDER_RANDOM), gender_conservative_(GENDER_RANDOM),
	infiltration_(0), juice_(0), money_(20, 40)
{
	for (int i = 0; i < ATTNUM; i++)
		attributes_[i].set_interval(1, 10);

	id_ = s_number_of_creaturetypes++;

	CMarkup xml;
	xml.SetDoc(xmlstring);
	xml.FindElem();

	idname_ = xml.GetAttrib("idname");
	if (!len(idname_))
	{
		idname_ = "LACKS IDNAME " + tostring(id_);
		xmllog.log("Creature type " + tostring(id_) + " lacks idname.");
	}
	type_ = creaturetype_string_to_enum(idname_);

	xml.IntoElem();
	// Loop over all the elements inside the creaturetype element.
	while (xml.FindElem())
	{
		std::string element = xml.GetTagName();

		if (element == "alignment")
		{
			std::string alignment = xml.GetData();
			if (alignment == "PUBLIC MOOD")
				alignment_public_mood_ = true;
			else if (alignment == "LIBERAL")
			{
				alignment_ = ALIGN_LIBERAL;
				alignment_public_mood_ = false;
			}
			else if (alignment == "MODERATE")
			{
				alignment_ = ALIGN_MODERATE;
				alignment_public_mood_ = false;
			}
			else if (alignment == "CONSERVATIVE")
			{
				alignment_ = ALIGN_CONSERVATIVE;
				alignment_public_mood_ = false;
			}
			else
				xmllog.log("Invalid alignment for " + idname_ + ": " + alignment);
		}
		else if (element == "age")
		{
			std::string age = xml.GetData();
			if (age == "DOGYEARS")
				age_.set_interval(2, 6);
			else if (age == "CHILD")
				age_.set_interval(7, 10);
			else if (age == "TEENAGER")
				age_.set_interval(14, 17);
			else if (age == "YOUNGADULT")
				age_.set_interval(18, 35);
			else if (age == "MATURE")
				age_.set_interval(20, 59);
			else if (age == "GRADUATE")
				age_.set_interval(26, 59);
			else if (age == "MIDDLEAGED")
				age_.set_interval(35, 59);
			else if (age == "SENIOR")
				age_.set_interval(65, 94);
			else
				assign_interval(age_, age, idname_, element);
		}
		else if (element == "attribute_points")
			assign_interval(attribute_points_, xml.GetData(), idname_, element);
		else if (element == "attributes")
		{
			while (xml.FindChildElem())
			{
				int attribute = attribute_string_to_enum(xml.GetChildTagName());
				if (attribute != -1)
					assign_interval(attributes_[attribute], xml.GetChildData(), idname_, element);
				else
					xmllog.log("Unknown attribute in " + idname_ + ": " + xml.GetTagName());
			}
		}
		else if (element == "juice")
			assign_interval(juice_, xml.GetData(), idname_, element);
		else if (element == "gender")
		{
			int gender = gender_string_to_enum(xml.GetData());
			if (gender != -1 && gender != GENDER_WHITEMALEPATRIARCH)
				gender_liberal_ = gender_conservative_ = gender;
			else
				xmllog.log("Invalid gender for " + idname_ + ": " + xml.GetData());
		}
		else if (element == "infiltration")
			assign_interval(infiltration_, xml.GetData(), idname_, element);
		else if (element == "money")
			assign_interval(money_, xml.GetData(), idname_, element);
		else if (element == "skills")
		{
			while (xml.FindChildElem())
			{
				int skill = skill_string_to_enum(xml.GetChildTagName());
				if (skill != -1)
					assign_interval(skills_[skill], xml.GetChildData(), idname_, element);
				else
					xmllog.log("Unknown skill for " + idname_ + ": " + xml.GetChildTagName());
			}
		}
		else if (element == "armor")
		{
			if (getarmortype(xml.GetData()) != -1)
				armortypes_.push_back(xml.GetData());
			else
				xmllog.log("Invalid armor type for " + idname_ + ": " + xml.GetData());;
		}
		else if (element == "weapon")
		{
			//xml.SavePos("creature");
			weapons_and_clips_.push_back(WeaponsAndClips(xml, idname_));
			//xml.RestorePos("creature");
		}
		else if (element == "encounter_name")
			encounter_name_ = xml.GetData();
		else if (element == "type_name")
			type_name_ = xml.GetData(); 
		else if (element == "talkreceptive")
			istalkreceptive_ = atoi(xml.GetData());
		else if (element == "seethroughstealth")
			seethroughstealth_ = atoi(xml.GetData());
		else if (element == "seethroughdisguise")
			seethroughdisguise_ = atoi(xml.GetData());
		else if (element == "reports_to_police")
			isreports_to_police_ = atoi(xml.GetData());
		else if (element == "kidnap_resistant")
			iskidnap_resistant_ = atoi(xml.GetData());
		else 
			xmllog.log("Unknown element for " + idname_ + ": " + element);
	}

	if (!len(type_name_))
	{
		xmllog.log("type_name not defined for " + idname_ + ".");
		type_name_ = "UNDEFINED";
	}
	// If no weapon type has been given then use WEAPON_NONE.
	if (!len(weapons_and_clips_))
		weapons_and_clips_.push_back(WeaponsAndClips("WEAPON_NONE", 1, "NONE", 0));
	// If no armor type has been given then use ARMOR_NONE.
	if (!len(armortypes_))
		armortypes_.push_back("ARMOR_NONE");
}


void CreatureType::make_creature(DeprecatedCreature& cr) const
{
	cr.type_idname = idname_;
	cr.align = get_alignment();
	cr.set_age(age_.roll());
	cr.juice = juice_.roll();
	cr.gender_liberal = cr.gender_conservative = roll_gender();
	cr.infiltration = roll_infiltration();
	cr.set_money(money_.roll());
	cr.rename(get_encounter_name());
	cr.settalkreceptive(istalkreceptive_);
	cr.setseethroughstealth(	seethroughstealth_);
	cr.setseethroughdisguise(	seethroughdisguise_);
	cr.setisreports_to_police(	isreports_to_police_);
	cr.setiskidnap_resistant(	iskidnap_resistant_);
	for (int i = 0; i < SKILLNUM; i++) cr.set_skill(i, skills_[i].roll());
	give_armor(cr);
	give_weapon(cr);
}
Alignment CreatureType::get_alignment() const
{
	if (alignment_public_mood_)
	{
		int mood = publicmood(-1);
		int a = ALIGN_CONSERVATIVE;
		if (LCSrandom(100) < mood) a++;
		if (LCSrandom(100) < mood) a++;
		return (Alignment)a;
	}
	else return alignment_;
}
int CreatureType::roll_gender() const
{
	switch (gender_liberal_)
	{
	case GENDER_NEUTRAL: return GENDER_NEUTRAL;
	case GENDER_MALE:    return GENDER_MALE;
	case GENDER_FEMALE:  return GENDER_FEMALE;
	case GENDER_MALE_BIAS:
		if (lawList[LAW_WOMEN] == -2 ||
			(lawList[LAW_WOMEN] == -1 && LCSrandom(25)) ||
			(lawList[LAW_WOMEN] == 0 && LCSrandom(10)) ||
			(lawList[LAW_WOMEN] == 1 && LCSrandom(4)))
			return GENDER_MALE;
	case GENDER_FEMALE_BIAS:
		if (lawList[LAW_WOMEN] == -2 ||
			(lawList[LAW_WOMEN] == -1 && LCSrandom(25)) ||
			(lawList[LAW_WOMEN] == 0 && LCSrandom(10)) ||
			(lawList[LAW_WOMEN] == 1 && LCSrandom(4)))
			return GENDER_FEMALE;
	}
	return LCSrandom(2) + 1; // Male or female.
}
float CreatureType::roll_infiltration() const
{
	return infiltration_.roll() / 100.0f;
}
std::string CreatureType::get_encounter_name() const
{
	if (len(encounter_name_))
		return encounter_name_;
	else return get_type_name();
}
std::string CreatureType::get_type_name() const
{
	switch (type_) // Hardcoded special cases.
	{
	case CREATURE_WORKER_SERVANT:
		if (lawList[LAW_LABOR] == -2 && lawList[LAW_CORPORATE] == -2) return CONST_X_SLAVE;
		break;
	case CREATURE_WORKER_JANITOR:
		if (lawList[LAW_LABOR] == 2) return CUSTODIAN;
		break;
	case CREATURE_WORKER_SWEATSHOP:
		if (lawList[LAW_LABOR] == 2 && lawList[LAW_IMMIGRATION] == 2) return MIGRANT_WORKER;
		break;
	case CREATURE_CARSALESMAN:
		if (lawList[LAW_WOMEN] == -2) return CAR_SALESMAN;
		break;
	case CREATURE_FIREFIGHTER:
		if (lawList[LAW_FREESPEECH] == -2) return FIREMAN;
		break;
	}
	return type_name_;
}
void CreatureType::give_weapon(DeprecatedCreature& cr) const
{
	const WeaponsAndClips& wc = pickrandom(weapons_and_clips_);
	if (wc.weapon_type_str == tag_CIVILIAN)
		give_weapon_civilian(cr);
	else if (wc.weapon_type_str != tag_WEAPON_NONE)
	{
		Weapon w(*weapontype[getweapontype(wc.weapon_type_str)], wc.number_weapons.roll());
		w.set_number(min(w.get_number(), 10L));
		while (!w.empty()) cr.give_weapon(w, NULL);
		if (wc.cliptype != NONE)
		{
			int n = wc.number_clips.roll();
			cr.take_clips(*cliptype[getcliptype(wc.cliptype)], n);
			cr.reload(false);
		}
	}
}
void CreatureType::give_weapon_civilian(DeprecatedCreature& cr) const
{
	if (lawList[LAW_GUNCONTROL] == -1 && !LCSrandom(30))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_38)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_38)], 4);
		cr.reload(false);
	}
	else if (lawList[LAW_GUNCONTROL] == -2)
	{
		if (!LCSrandom(10))
		{
			cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_9MM)], NULL);
			cr.take_clips(*cliptype[getcliptype(tag_CLIP_9)], 4);
			cr.reload(false);
		}
		else if (!LCSrandom(9))
		{
			cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_45)], NULL);
			cr.take_clips(*cliptype[getcliptype(tag_CLIP_45)], 4);
			cr.reload(false);
		}
	}
}
void CreatureType::give_armor(DeprecatedCreature& cr) const
{
	const std::string str = pickrandom(armortypes_);
	if (str != tag_ARMOR_NONE)
		cr.give_armor(getarmortype(str), NULL);
}


weaponLayout getWeaponLayout(const short type) {
	switch (lawList[LAW_GUNCONTROL]) {
	case -2:
		return defaultWeapons[type].cplus;
	case -1:
		return defaultWeapons[type].c;
	case 0:
		return defaultWeapons[type].moderate;
	case 1:
		return defaultWeapons[type].l;
	case 2:
		return defaultWeapons[type].lplus;
	}
	return weaponLayout(tag_WEAPON_NONE);
}

void giveDefaultWeapon(DeprecatedCreature &cr, const short type) {
	if (defaultWeapons.count(type) >= 1) {
		weaponLayout layout = getWeaponLayout(type);
		cr.give_weapon(*weapontype[getweapontype(layout.weaponTag)], NULL);
		if (layout.ammunition >= 1) {
			cr.take_clips(*cliptype[getcliptype(layout.clipTag)], layout.ammunition);
		}
		cr.reload(false);
	}
}
void armBouncer(DeprecatedCreature &cr) {
	if (mode == GAMEMODE_SITE && LocationsPool::getInstance().get_specific_integer(INT_ISTHISPLACEHIGHSECURITY, getCurrentSite()))
	{
		cr.rename(ENFORCER);
		cr.set_skill(SKILL_CLUB, LCSrandom(3) + 3);
	}
	if (disguisesite(sitetype))
	{
		cr.align = ALIGN_CONSERVATIVE;
		cr.infiltration = 0.1f*LCSrandom(4);
	}
	else cr.align = ALIGN_MODERATE;
}

void armCREATURE_SCIENTIST_LABTECH(DeprecatedCreature &cr) {
	if (!cr.is_armed() && !LCSrandom(2))
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SYRINGE)], NULL);
}
void armCREATURE_JUDGE_CONSERVATIVE(DeprecatedCreature &cr) {
	if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_44)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_44)], 4);
	}
	else if (!LCSrandom(2))
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_GAVEL)], NULL);
	cr.reload(false);
}
void armCREATURE_SCIENTIST_EMINENT(DeprecatedCreature &cr) {
	if (!cr.is_armed() && !LCSrandom(2))
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SYRINGE)], NULL);
}
void armCREATURE_CORPORATE_CEO(DeprecatedCreature &cr) {
	fullName fn = generate_long_name(GENDER_WHITEMALEPATRIARCH);
	strcpy(cr.propername, (fn.first + " " + fn.last).data());
	cr.rename(CEO_SPACE + cr.propername);
	cr.dontname = true;
}
void armCREATURE_WORKER_FACTORY_NONUNION(DeprecatedCreature &cr) {
	if (!cr.is_armed())
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_CHAIN)], NULL);
	if (cr.align == ALIGN_LIBERAL) cr.align = LCSrandom(2) - 1;
}
void armCREATURE_WORKER_SWEATSHOP(DeprecatedCreature &cr) {
	cr.flag |= CREATUREFLAG_ILLEGALALIEN;
}
void armCREATURE_LAWYER(DeprecatedCreature &cr) {
	if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_38)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_38)], 1);
		cr.reload(false);
	}
}
void armCREATURE_DOCTOR(DeprecatedCreature &cr) {
	if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_38)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_38)], 1);
		cr.reload(false);
	}
}
void armCREATURE_PSYCHOLOGIST(DeprecatedCreature &cr) {
	if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_38)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_38)], 1);
		cr.reload(false);
	}
	if (cr.gender_liberal == GENDER_MALE || LCSrandom(2))
		cr.give_armor(getarmortype(tag_ARMOR_CHEAPSUIT), NULL);
	else
		cr.give_armor(getarmortype(tag_ARMOR_CHEAPDRESS), NULL);
}
void armCREATURE_NURSE(DeprecatedCreature &cr) {
	if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_38)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_38)], 1);
		cr.reload(false);
	}
}
void armCREATURE_WORKER_FACTORY_UNION(DeprecatedCreature &cr) {
	if (!cr.is_armed())
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_CHAIN)], NULL);
}
void armCREATURE_TANK(DeprecatedCreature &cr) {
	cr.animalgloss = ANIMALGLOSS_TANK;
	cr.specialattack = ATTACK_CANNON;
}


void armCREATURE_HICK(DeprecatedCreature &cr) {
	cr.rename(pickrandom(words_meaning_hick));
	if ((lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(2)) || !LCSrandom(10))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHOTGUN_PUMP)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_BUCKSHOT)], 4);
	}
	else
		cr.give_weapon(*weapontype[getweapontype(LCSrandom(2) ? tag_WEAPON_TORCH : tag_WEAPON_PITCHFORK)], NULL);
	cr.reload(false);
}
void armCREATURE_COP(DeprecatedCreature &cr) {
	if (lawList[LAW_POLICEBEHAVIOR] == 2 && cr.align == ALIGN_LIBERAL && !LCSrandom(3)) // Peace Officer
	{
		cr.align = ALIGN_MODERATE;
		cr.rename(POLICE_NEGOTIATOR);
		cr.set_skill(SKILL_PERSUASION, LCSrandom(4) + 1);
		cr.set_skill(SKILL_PISTOL, LCSrandom(3) + 1);
		cr.set_attribute(ATTRIBUTE_HEART, 4);
	}
	else
	{
		if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
		{
			cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SMG_MP5)], NULL);
			cr.take_clips(*cliptype[getcliptype(tag_CLIP_SMG)], 4);
		}
		else if (!LCSrandom(3))
		{
			cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_9MM)], NULL);
			cr.take_clips(*cliptype[getcliptype(tag_CLIP_9)], 4);
		}
		else if (!LCSrandom(2))
		{
			cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHOTGUN_PUMP)], NULL);
			cr.take_clips(*cliptype[getcliptype(tag_CLIP_BUCKSHOT)], 4);
		}
		else
			cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_NIGHTSTICK)], NULL);
		cr.reload(false);
		cr.align = ALIGN_CONSERVATIVE;
		cr.set_skill(SKILL_PISTOL, LCSrandom(4) + 1);
		cr.set_skill(SKILL_SHOTGUN, LCSrandom(3) + 1);
		cr.set_skill(SKILL_CLUB, LCSrandom(2) + 1);
		cr.set_skill(SKILL_HANDTOHAND, LCSrandom(2) + 1);
		cr.set_attribute(ATTRIBUTE_WISDOM, 4);
	}
}
void armCREATURE_FIREFIGHTER(DeprecatedCreature &cr) {
	if (lawList[LAW_FREESPEECH] == -2)
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_FLAMETHROWER)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_GASOLINE)], 4);
		cr.reload(false);
		cr.set_skill(SKILL_HEAVYWEAPONS, LCSrandom(3) + 2);
		cr.rename(CONST_X_FIREMAN);
		cr.align = ALIGN_CONSERVATIVE;
	}
	else
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_AXE)], NULL);
		cr.set_skill(SKILL_AXE, LCSrandom(3) + 2);
		cr.rename(FIREFIGHTER);
	}
	if (isThereASiteAlarm()) // Respond to emergencies in bunker gear
		cr.give_armor(getarmortype(tag_ARMOR_BUNKERGEAR), NULL);
}
void armCREATURE_CCS_MOLOTOV(DeprecatedCreature &cr) {

	if (mode == GAMEMODE_SITE)
		nameCCSMember(cr);
}
void armCREATURE_CCS_SNIPER(DeprecatedCreature &cr) {

	if (mode == GAMEMODE_SITE)
		nameCCSMember(cr);
}
void armCREATURE_CCS_VIGILANTE(DeprecatedCreature &cr) {
	cr.give_armor(getarmortype(tag_ARMOR_CLOTHES), NULL);
	switch (LCSrandom(5) + endgamestate)
	{
	case 0:
	case 1:
		break;
	case 2:
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_9MM)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_9)], 7);
	}
	break;
	case 3:
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_44)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_44)], 7);
	}
	break;
	case 4:
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHOTGUN_PUMP)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_BUCKSHOT)], 7);
	}
	break;
	case 5:
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIRIFLE_AR15)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_ASSAULT)], 7);
		cr.give_armor(getarmortype(tag_ARMOR_CIVILLIANARMOR), NULL);
	}
	break;
	case 6:
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIRIFLE_AR15)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_ASSAULT)], 7);
		cr.give_armor(getarmortype(tag_ARMOR_ARMYARMOR), NULL);
	}
	break;
	default:
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_AUTORIFLE_M16)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_ASSAULT)], 7);
		cr.give_armor(getarmortype(tag_ARMOR_ARMYARMOR), NULL);
	}
	break;
	}
	cr.reload(false);
	if (mode == GAMEMODE_SITE)
		nameCCSMember(cr);
}
void armCREATURE_CCS_ARCHCONSERVATIVE(DeprecatedCreature &cr) {
	cr.rename((LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) ? CCS_TEAM_LEADER : (ccs_kills < 2 ? CCS_LIEUTENANT : CCS_FOUNDER)));
}
void armCREATURE_PRISONGUARD(DeprecatedCreature &cr) {
	if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SMG_MP5)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_SMG)], 4);
	}
	else if (!LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHOTGUN_PUMP)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_BUCKSHOT)], 4);
	}
	else
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_NIGHTSTICK)], NULL);
	cr.reload(false);
}
void armCREATURE_EDUCATOR(DeprecatedCreature &cr) {
	if (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SMG_MP5)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_SMG)], 4);
	}
	else if (!LCSrandom(3))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_9MM)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_9)], 4);
	}
	else
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SYRINGE)], NULL);
	cr.reload(false);
}
void armCREATURE_GENETIC(DeprecatedCreature &cr, int(&attcap)[ATTNUM]) {
	if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_CORPORATE_HOUSE)
	{
		cr.rename( PET_SPACE);
		attcap[ATTRIBUTE_CHARISMA] = 10;
	}
	else
		cr.rename( "");
	switch (LCSrandom(11))
	{
	case 0:
		cr.rename(cr.getNameAndAlignment().name + FLAMING_RABBIT);
		cr.specialattack = ATTACK_FLAME;
		break;
	case 1:
		cr.rename(cr.getNameAndAlignment().name + GIANT_MOSQUITO);
		cr.specialattack = ATTACK_SUCK;
		break;
	default:
		cr.rename(cr.getNameAndAlignment().name + pickrandom(genetic_monster));
		break;
	}
	cr.animalgloss = ANIMALGLOSS_ANIMAL;
	if (lawList[LAW_ANIMALRESEARCH] != 2)cr.no_money();
}
void armCREATURE_GUARDDOG(DeprecatedCreature &cr) {
	cr.animalgloss = ANIMALGLOSS_ANIMAL;
	if (lawList[LAW_ANIMALRESEARCH] != 2)cr.no_money();
}
void armCREATURE_PRISONER(DeprecatedCreature &cr, const CreatureType* crtype) {
	cr.drop_weapons_and_clips(NULL);
	crtype->give_weapon(cr);
	cr.strip(NULL);
	crtype->give_armor(cr);
	cr.set_money(crtype->money_.roll());
	cr.juice = crtype->juice_.roll();
	cr.gender_liberal = cr.gender_conservative = crtype->roll_gender();
	cr.rename(crtype->get_encounter_name());
	if (cr.align == ALIGN_CONSERVATIVE)
		cr.align = LCSrandom(2);
}
void armCREATURE_BUM(DeprecatedCreature &cr) {
	if (!cr.is_armed() && !LCSrandom(5))
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHANK)], NULL);
	if (cr.align == ALIGN_CONSERVATIVE)cr.align = LCSrandom(2);
}
void armCREATURE_MUTANT(DeprecatedCreature &cr) {
	if (!cr.is_armed() && !LCSrandom(5))
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHANK)], NULL);
}
void armCREATURE_GANGMEMBER(DeprecatedCreature &cr) {
	if (!LCSrandom(20) || (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(5)))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_AUTORIFLE_AK47)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_ASSAULT)], 3);
	}
	else if (!LCSrandom(16) || (lawList[LAW_GUNCONTROL] == -2 && !LCSrandom(5)))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SMG_MP5)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_SMG)], 4);
	}
	else if (!LCSrandom(15))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_45)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_45)], 4);
	}
	else if (!LCSrandom(10))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHOTGUN_PUMP)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_BUCKSHOT)], 4);
	}
	else if (!LCSrandom(4))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_9MM)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_9)], 4);
	}
	else if (!LCSrandom(2))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_REVOLVER_38)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_38)], 4);
	}
	else
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_COMBATKNIFE)], NULL);
	cr.reload(false);
	// We'll make the crack house a bit dicey
	if (LocationsPool::getInstance().getLocationType(getCurrentSite()) == SITE_BUSINESS_CRACKHOUSE)cr.align = ALIGN_CONSERVATIVE;
	if (!LCSrandom(2))switch (LCSrandom(3))
	{
	case 0://cr.crimes_committed[LAWFLAG_BROWNIES]++;
		cr.criminalize_me(LAWFLAG_BROWNIES, false);
		break;
	case 1://cr.crimes_committed[LAWFLAG_ASSAULT]++;
		cr.criminalize_me(LAWFLAG_ASSAULT, false);
		break;
	case 2://cr.crimes_committed[LAWFLAG_MURDER]++;
		cr.criminalize_me(LAWFLAG_MURDER, false);
		break;
	}
}
void armCREATURE_CRACKHEAD(DeprecatedCreature &cr, int(&attcap)[ATTNUM]) {
	if (!LCSrandom(5))
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SHANK)], NULL);
	if (cr.align == ALIGN_CONSERVATIVE)cr.align = LCSrandom(2);
	attcap[ATTRIBUTE_HEALTH] = 1 + LCSrandom(5);
}
void armCREATURE_FASTFOODWORKER(DeprecatedCreature &cr) {
	cr.set_age((LCSrandom(2) ? AGE_TEENAGER : AGE_YOUNGADULT));
}
void armCREATURE_FOOTBALLCOACH(DeprecatedCreature &cr) {
	if (LCSrandom(2))
	{
		cr.set_attribute(ATTRIBUTE_HEALTH, 5);
		cr.set_attribute(ATTRIBUTE_AGILITY, 5);
		cr.set_attribute(ATTRIBUTE_STRENGTH, 5);
	}
}
void armCREATURE_PROSTITUTE(DeprecatedCreature &cr) {
	if (LCSrandom(7))cr.gender_conservative = cr.gender_liberal = GENDER_FEMALE;
	else if (!LCSrandom(3))cr.gender_liberal = GENDER_FEMALE;
	if (cr.align == ALIGN_CONSERVATIVE)cr.align = LCSrandom(2);
	if (!LCSrandom(3)) { cr.criminalize_me(LAWFLAG_PROSTITUTION); }
}
void armCREATURE_HIPPIE(DeprecatedCreature &cr) {
	if (!LCSrandom(10)) {
		cr.criminalize_me(LAWFLAG_BROWNIES);
	}
}
void armCREATURE_SOCIALITE(DeprecatedCreature &cr) {
	cr.give_armor(getarmortype(cr.gender_liberal == GENDER_FEMALE ? tag_ARMOR_EXPENSIVEDRESS : tag_ARMOR_EXPENSIVESUIT), NULL);
}
void armCREATURE_THIEF(DeprecatedCreature &cr) {
	switch (LCSrandom(5))
	{
	case 0:
		cr.rename( getcreaturetype(CREATURE_SOCIALITE)->get_encounter_name());
		break;
	case 1:
		cr.rename( getcreaturetype(CREATURE_CLERK)->get_encounter_name());
		break;
	case 2:
		cr.rename( getcreaturetype(CREATURE_OFFICEWORKER)->get_encounter_name());
		break;
	case 3:
		cr.rename( getcreaturetype(CREATURE_CRITIC_ART)->get_encounter_name());
		break;
	case 4:
		cr.rename( getcreaturetype(CREATURE_CRITIC_MUSIC)->get_encounter_name());
		break;
	}
	if (!LCSrandom(10)) { cr.criminalize_me(LCSrandom(2) ? LAWFLAG_BREAKING : LAWFLAG_THEFT); }
}
void armCREATURE_MILITARYOFFICER(DeprecatedCreature &cr) {
	if (LCSrandom(4))
	{
		cr.give_weapon(*weapontype[getweapontype(tag_WEAPON_SEMIPISTOL_9MM)], NULL);
		cr.take_clips(*cliptype[getcliptype(tag_CLIP_9)], 4);
		cr.reload(false);
	}
}
// IsaacG Very few of the nested functions require anything other than &cr and type.  A rewrite that only uses those two parameters is desirable.
void armSpecificCreature(DeprecatedCreature &cr, const short type, const CreatureType* crtype, int(&attcap)[ATTNUM]) {
	switch (type)
	{
	case CREATURE_BOUNCER:
		armBouncer(cr);
		break;
	case CREATURE_SCIENTIST_LABTECH:
		armCREATURE_SCIENTIST_LABTECH(cr);
		break;
	case CREATURE_JUDGE_CONSERVATIVE:
		armCREATURE_JUDGE_CONSERVATIVE(cr);
		break;
	case CREATURE_SCIENTIST_EMINENT:
		armCREATURE_SCIENTIST_EMINENT(cr);
		break;
	case CREATURE_CORPORATE_CEO:
		armCREATURE_CORPORATE_CEO(cr);
		break;
	case CREATURE_WORKER_FACTORY_NONUNION:
		armCREATURE_WORKER_FACTORY_NONUNION(cr);
		break;
	case CREATURE_WORKER_SWEATSHOP:
		armCREATURE_WORKER_SWEATSHOP(cr);
		break;
	case CREATURE_LAWYER:
		armCREATURE_LAWYER(cr);
		break;
	case CREATURE_DOCTOR:
		armCREATURE_DOCTOR(cr);
		break;
	case CREATURE_PSYCHOLOGIST:
		armCREATURE_PSYCHOLOGIST(cr);
		break;
	case CREATURE_NURSE:
		armCREATURE_NURSE(cr);
		break;
	case CREATURE_WORKER_FACTORY_UNION:
		armCREATURE_WORKER_FACTORY_UNION(cr);
		break;
	case CREATURE_TANK:
		armCREATURE_TANK(cr);
		break;
	case CREATURE_HICK:
		armCREATURE_HICK(cr);
		break;
	case CREATURE_COP:
		armCREATURE_COP(cr);
		break;
	case CREATURE_FIREFIGHTER:
		armCREATURE_FIREFIGHTER(cr);
		break;
	case CREATURE_CCS_MOLOTOV:
		armCREATURE_CCS_MOLOTOV(cr);
		break;
	case CREATURE_CCS_SNIPER:
		armCREATURE_CCS_SNIPER(cr);
		break;
	case CREATURE_CCS_VIGILANTE:
		armCREATURE_CCS_VIGILANTE(cr);
		break;
	case CREATURE_CCS_ARCHCONSERVATIVE:
		armCREATURE_CCS_ARCHCONSERVATIVE(cr);
		break;
	case CREATURE_PRISONGUARD:
		armCREATURE_PRISONGUARD(cr);
		break;
	case CREATURE_EDUCATOR:
		armCREATURE_EDUCATOR(cr);
		break;
	case CREATURE_GENETIC:
		armCREATURE_GENETIC(cr, attcap);
		break;
	case CREATURE_GUARDDOG:
		armCREATURE_GUARDDOG(cr);
		break;
	case CREATURE_PRISONER:
		armCREATURE_PRISONER(cr, crtype);
		break;
	case CREATURE_BUM:
		armCREATURE_BUM(cr);
		break;
	case CREATURE_MUTANT:
		armCREATURE_MUTANT(cr);
		break;
	case CREATURE_GANGMEMBER:
		armCREATURE_GANGMEMBER(cr);
		break;
	case CREATURE_CRACKHEAD:
		armCREATURE_CRACKHEAD(cr, attcap);
		break;
	case CREATURE_FASTFOODWORKER:
		armCREATURE_FASTFOODWORKER(cr);
		break;
	case CREATURE_FOOTBALLCOACH:
		armCREATURE_FOOTBALLCOACH(cr);
		break;
	case CREATURE_PROSTITUTE:
		armCREATURE_PROSTITUTE(cr);
		break;
	case CREATURE_HIPPIE:
		armCREATURE_HIPPIE(cr);
		break;
	case CREATURE_SOCIALITE:
		armCREATURE_SOCIALITE(cr);
		break;
	case CREATURE_THIEF:
		armCREATURE_THIEF(cr);
		break;
	case CREATURE_MILITARYOFFICER:
		armCREATURE_MILITARYOFFICER(cr);
		break;
	}


}
void armCreature(DeprecatedCreature &cr, short type) {

	const CreatureType* crtype = getcreaturetype(type);
	crtype->make_creature(cr);
	int attnum = crtype->attribute_points_.roll();
	int attcap[ATTNUM];
	for (int i = 0; i < ATTNUM; i++)
	{
		cr.set_attribute(i, crtype->attributes_[i].min);
		attcap[i] = crtype->attributes_[i].max;
	}
	bool skipThisCreature = false;
	for (CreatureTypes crt : doNotArmInThisFunction) {
		if (crt == type) {
			skipThisCreature = true;
			break;
		}
	}
	for (CreatureTypes crt : armAsCivilian) {
		if (crt == type) {
			crtype->give_weapon_civilian(cr);
			break;
		}
	}
	if (replaceTheseCreatures.count(type) >= 1) {
		CreatureTypes replacement = pickrandom(replaceTheseCreatures[type]);
		makecreature(cr, replacement);
	}
	giveDefaultWeapon(cr, type);
	if (!skipThisCreature) {
		armSpecificCreature(cr, type, crtype, attcap);
	}

	vector<int> possible;
	for (int a = 0; a < ATTNUM; a++)
	{
		attnum -= min(4, cr.get_attribute(a, false));
		possible.push_back(a);
	}
	while (attnum > 0 && len(possible))
	{
		int i = LCSrandom(len(possible));
		int a = possible[i];
		if (a == ATTRIBUTE_WISDOM && cr.align == ALIGN_LIBERAL && LCSrandom(4)) a = ATTRIBUTE_HEART;
		if (a == ATTRIBUTE_HEART && cr.align == ALIGN_CONSERVATIVE && LCSrandom(4)) a = ATTRIBUTE_WISDOM;
		if (cr.get_attribute(a, false) < attcap[a])
		{
			cr.adjust_attribute(a, +1);
			attnum--;
		}
		else possible.erase(possible.begin() + i);
	}

	possible.clear();
}

/* rolls up a creature's stats and equipment */
void makecreature(DeprecatedCreature &cr, short type)
{
	if (type == -1) {
		return;
	}
	cr.drop_weapons_and_clips(NULL); // Get rid of any old equipment from old encounters.
	cr.strip(NULL);                  //
	cr.creatureinit();
	cr.make_existing();
	cr.squadid = -1;
	cr.type = type;
	cr.infiltration = 0;
	cr.location = getCurrentSite();
	cr.worklocation = verifyworklocation(type, cr.location);

	armCreature(cr, type);

	if (cr.align == ALIGN_LIBERAL) cr.infiltration = 0.15f + (LCSrandom(10) - 5)*0.01f;
	else if (cr.align == ALIGN_MODERATE) cr.infiltration = 0.25f + (LCSrandom(10) - 5)*0.01f;
	else cr.infiltration += 0.35f*(1 - cr.infiltration) + (LCSrandom(10) - 5)*0.01f;
	if (cr.infiltration < 0) cr.infiltration = 0;
	if (cr.infiltration > 1) cr.infiltration = 1;
	int randomskills = LCSrandom(4) + 4;
	if (cr.getCreatureBio().age > 20) randomskills += static_cast<int>(randomskills*((cr.getCreatureBio().age - 20.0) / 20.0));
	else randomskills -= (20 - cr.getCreatureBio().age) / 2;
	vector<int> possible;
	for (int s = 0; s < SKILLNUM; s++)possible.push_back(s);
	//RANDOM STARTING SKILLS
	while (randomskills > 0 && len(possible))
	{
		int i = LCSrandom(len(possible));
		int randomskill = possible[i];
		// 95% chance of not allowing some skills for anybody...
		if (LCSrandom(20))
		{
			if (randomskill == SKILL_HEAVYWEAPONS) continue;
			if (randomskill == SKILL_SMG) continue;
			if (randomskill == SKILL_SWORD) continue;
			if (randomskill == SKILL_RIFLE) continue;
			if (randomskill == SKILL_AXE) continue;
			if (randomskill == SKILL_CLUB) continue;
			if (randomskill == SKILL_PSYCHOLOGY) continue;
		}
		// 90% chance of not allowing some skills, other than
		//   for conservatives
		if (LCSrandom(10) && cr.align != ALIGN_CONSERVATIVE)
		{
			if (randomskill == SKILL_SHOTGUN) continue;
			if (randomskill == SKILL_PISTOL) continue;
		}
		if (cr.skill_cap(randomskill) > cr.get_skill(randomskill))
		{
			cr.set_skill(randomskill, cr.get_skill(randomskill) + 1);
			randomskills--;
			while (randomskills&&LCSrandom(2))
			{
				if (cr.skill_cap(randomskill) > cr.get_skill(randomskill) &&
					cr.get_skill(randomskill) < 4)
				{
					cr.set_skill(randomskill, cr.get_skill(randomskill) + 1);
					randomskills--;
				}
				else
				{
					possible.erase(possible.begin() + i);
					break;
				}
			}
		}
		else possible.erase(possible.begin() + i);
	}
	//ALIENATION
	if ((sitealienate >= 1 && cr.align == ALIGN_MODERATE) || (sitealienate == 2 && cr.align == ALIGN_LIBERAL))conservatise(cr);
}

CreatureType::WeaponsAndClips::WeaponsAndClips(CMarkup& xml, const string& owner)
	: number_weapons(1),
	cliptype("APPROPRIATE"), number_clips(4)
{ // The main position of the CMarkup object is expected not to be changed here.
	weapon_type_str = xml.GetData();

	// Read in values.
	if (!len(weapon_type_str))
	{
		while (xml.FindChildElem())
		{
			std::string element = xml.GetChildTagName();
			if (element == "type") weapon_type_str = xml.GetChildData();
			else if (element == "number_weapons")
				assign_interval(number_weapons, xml.GetChildData(), owner, element);
			else if (element == "cliptype") cliptype = xml.GetChildData();
			else if (element == "number_clips")
				assign_interval(number_clips, xml.GetChildData(), owner, element);
			else xmllog.log("Unknown element for weapon in " + owner + ": " + element);
		}
	}

	// Check values.
	if (weapon_type_str != "CIVILIAN")
	{
		if (getweapontype(weapon_type_str) == -1)
		{
			xmllog.log("Invalid weapon type for " + owner + ": " + weapon_type_str);
			weapon_type_str = "WEAPON_NONE";
			cliptype = "NONE";
		}
		else
		{
			const vector<attackst*>& attacks = ::weapontype[getweapontype(weapon_type_str)]->get_attacks();

			// Find a usable clip type for the weapon.
			if (cliptype == "APPROPRIATE")
			{
				cliptype = "NONE";
				for (int i = 0; i < len(attacks); i++)
				{
					if (attacks[i]->uses_ammo)
					{
						cliptype = attacks[i]->ammotype;
						break;
					}
				}
			}
			// Check clip is usable by the weapon.
			else if (getcliptype(cliptype) != -1) //Must be a clip type too.
			{
				int i;
				for (i = 0; i < len(attacks) && cliptype != attacks[i]->ammotype; i++);
				if (i == len(attacks))
				{
					xmllog.log("In " + owner + ", " + cliptype +
						"can not be used by " + weapon_type_str + ".");
					cliptype = "NONE";
				}
			}
			// Undefined clip type.
			else
			{
				xmllog.log("Invalid clip type for " + owner + ": " + cliptype);
				cliptype = "NONE";
			}
		}
	}
}

/*
CreatureType::WeaponsAndClips::WeaponsAndClips(CMarkup& xml, const string& owner)
	: number_weapons(1),
	cliptype(tag_APPROPRIATE), number_clips(4)
{
	weapon_type_str = xml.GetData();
	// Read in values.
	if (!len(weapontype))
	{
		while (xml.FindChildElem())
		{
			std::string element = xml.GetChildTagName();
			if (element == tag_type) weapon_type_str = xml.GetChildData();
			else if (element == tag_number_weapons)
				assign_interval(number_weapons, xml.GetChildData(), owner, element);
			else if (element == tag_cliptype) cliptype = xml.GetChildData();
			else if (element == tag_number_clips)
				assign_interval(number_clips, xml.GetChildData(), owner, element);
			else xmllog.log(UNKNOWN_ELEMENT_FOR_WEAPON + owner + CONST_creaturetypeB086 + element);
		}
	}
	// Check values.
	if (weapon_type_str != tag_CIVILIAN)
	{
		if (getweapontype(weapon_type_str) == -1)
		{
			xmllog.log(INVALID_WEAPON_TYPE + owner + CONST_creaturetypeB086 + weapon_type_str);
			weapon_type_str = tag_WEAPON_NONE;
			cliptype = NONE;
		}
		else
		{
			const vector<attackst*>& attacks = weapontype[getweapontype(weapon_type_str)]->get_attacks();
			// Find a usable clip type for the weapon.
			if (cliptype == tag_APPROPRIATE)
			{
				cliptype = NONE;
				for (int i = 0; i < len(attacks); i++)
				{
					if (attacks[i]->uses_ammo)
					{
						cliptype = attacks[i]->ammotype;
						break;
					}
				}
			}
			// Check clip is usable by the weapon.
			else if (getcliptype(cliptype) != -1) //Must be a clip type too.
			{
				int i;
				for (i = 0; i < len(attacks) && cliptype != attacks[i]->ammotype; i++);
				if (i == len(attacks))
				{
					xmllog.log(IN_SPACE + owner + CONST_X_COMMA_SPACE + cliptype +
						CAN_NOT_BE_USED_BY + weapon_type_str + singleDot);
					cliptype = NONE;
				}
			}
			// Undefined clip type.
			else
			{
				xmllog.log(INVALID_CLIP_TYPE + owner + CONST_creaturetypeB086 + cliptype);
				cliptype = NONE;
			}
		}
	}
}
*/