

#include "../includes54.h"
#include "../constStringstringconversion.h"
#include <sstream>
#include <algorithm>


std::string tostring(long i)
{
	std::ostringstream os;
	os << i;
	return os.str();
}
using std::transform;
int stringtobool(string boolstr)
{
	transform(boolstr.begin(), boolstr.end(), boolstr.begin(), ::tolower);
	if (boolstr == tag_true || boolstr == tag_1 || boolstr == tag_on || boolstr == tag_yes) return 1;
	else if (boolstr == tag_false || boolstr == tag_0 || boolstr == tag_off || boolstr == tag_no) return 0;
	else return -1;
}
short creaturetype_string_to_enum(const string& ctname)
{
	if (getCreatureEnumFromString.count(ctname) > 0) {
		return getCreatureEnumFromString[ctname];
	}
	else
		return -1;
}
string showXmlSkill(int skill_, int value_) {

	CMarkup xml;
	xml.AddElem(tag_skill);
	xml.IntoElem();
	xml.AddElem(tag_value, min(value_, MAXATTRIBUTE));
	return xml.GetDoc();
}
string showXmlAttribute(int attribute_, int value_) {

	CMarkup xml;
	xml.AddElem(tag_attribute);
	xml.IntoElem();
	xml.AddElem(tag_value, min(value_, MAXATTRIBUTE));
	return xml.GetDoc();
}
map<short, string> skillEnumToString;
map<short, string> attEnumToString;
string skill_enum_to_string(int skill_type) {

	if (skillEnumToString.count(skill_type)) {
		return skillEnumToString[skill_type];
	}
	else
		return "";
}
string attribute_enum_to_string(int attribute)
{
	if (attEnumToString.count(attribute)) {
		return attEnumToString[attribute];
	}
	else
		return "";
	/*
	if (attribute == ATTRIBUTE_STRENGTH)
		return tag_strength;
	else if (attribute == ATTRIBUTE_INTELLIGENCE)
		return tag_intelligence;
	else if (attribute == ATTRIBUTE_WISDOM)
		return tag_wisdom;
	else if (attribute == ATTRIBUTE_AGILITY)
		return tag_agility;
	else if (attribute == ATTRIBUTE_HEALTH)
		return tag_health;
	else if (attribute == ATTRIBUTE_CHARISMA)
		return tag_charisma;
	else if (attribute == ATTRIBUTE_HEART)
		return tag_heart;
	else
		return "";*/
}
int attribute_string_to_enum(const string& attribute)
{
	if (attribute == tag_strength)
		return ATTRIBUTE_STRENGTH;
	else if (attribute == tag_intelligence)
		return ATTRIBUTE_INTELLIGENCE;
	else if (attribute == tag_wisdom)
		return ATTRIBUTE_WISDOM;
	else if (attribute == tag_agility)
		return ATTRIBUTE_AGILITY;
	else if (attribute == tag_health)
		return ATTRIBUTE_HEALTH;
	else if (attribute == tag_charisma)
		return ATTRIBUTE_CHARISMA;
	else if (attribute == tag_heart)
		return ATTRIBUTE_HEART;
	else
		return -1;
}

int gender_string_to_enum(const string& gender)
{
	if (gender == tag_NEUTRAL)
		return GENDER_NEUTRAL;
	else if (gender == tag_MALE)
		return GENDER_MALE;
	else if (gender == tag_FEMALE)
		return GENDER_FEMALE;
	else if (gender == tag_GENDER_WHITEMALEPATRIARCH)
		return GENDER_WHITEMALEPATRIARCH;
	else if (gender == tag_MALE_BIAS)
		return GENDER_MALE_BIAS;
	else if (gender == tag_FEMALE_BIAS)
		return GENDER_FEMALE_BIAS;
	else if (gender == tag_RANDOM)
		return GENDER_RANDOM;
	else
		return -1;
}
//string NONE;
int severtype_string_to_enum(const string& severtype)
{
	if (severtype == tag_NASTY)
		return WOUND_NASTYOFF;
	else if (severtype == tag_CLEAN)
		return WOUND_CLEANOFF;
	else if (severtype == NONE)
		return 0;
	else
		return -1;
}
int skill_string_to_enum(string skillname)
{
	transform(skillname.begin(), skillname.end(), skillname.begin(), ::tolower);
	if (skillname == tag_handtohand)
		return SKILL_HANDTOHAND;
	else if (skillname == tag_knife)
		return SKILL_KNIFE;
	else if (skillname == tag_sword)
		return SKILL_SWORD;
	else if (skillname == tag_club)
		return SKILL_CLUB;
	else if (skillname == tag_axe)
		return SKILL_AXE;
	else if (skillname == tag_throwing)
		return SKILL_THROWING;
	else if (skillname == tag_pistol)
		return SKILL_PISTOL;
	else if (skillname == tag_rifle)
		return SKILL_RIFLE;
	else if (skillname == tag_smg)
		return SKILL_SMG;
	else if (skillname == tag_shotgun)
		return SKILL_SHOTGUN;
	else if (skillname == tag_persuasion)
		return SKILL_PERSUASION;
	else if (skillname == tag_psychology)
		return SKILL_PSYCHOLOGY;
	else if (skillname == tag_law)
		return SKILL_LAW;
	else if (skillname == tag_security)
		return SKILL_SECURITY;
	else if (skillname == tag_disguise)
		return SKILL_DISGUISE;
	else if (skillname == tag_computers)
		return SKILL_COMPUTERS;
	else if (skillname == tag_tailoring)
		return SKILL_TAILORING;
	else if (skillname == tag_driving)
		return SKILL_DRIVING;
	else if (skillname == tag_writing)
		return SKILL_WRITING;
	else if (skillname == tag_music)
		return SKILL_MUSIC;
	else if (skillname == tag_art)
		return SKILL_ART;
	else if (skillname == tag_religion)
		return SKILL_RELIGION;
	else if (skillname == tag_science)
		return SKILL_SCIENCE;
	else if (skillname == tag_business)
		return SKILL_BUSINESS;
	else if (skillname == tag_stealth)
		return SKILL_STEALTH;
	else if (skillname == tag_teaching)
		return SKILL_TEACHING;
	else if (skillname == tag_streetsense)
		return SKILL_STREETSENSE;
	else if (skillname == tag_seduction)
		return SKILL_SEDUCTION;
	else if (skillname == tag_firstaid)
		return SKILL_FIRSTAID;
	else if (skillname == tag_dodge)
		return SKILL_DODGE;
	else if (skillname == tag_heavyweapons)
		return SKILL_HEAVYWEAPONS;
	else
		return -1;
}

int get_associated_attribute(int skill_type)
{
	// Initialize associated attribute
	switch (skill_type)
	{
	case SKILL_CLUB:
	case SKILL_AXE:
	case SKILL_HEAVYWEAPONS:
		return ATTRIBUTE_STRENGTH;
	case SKILL_HANDTOHAND:
	case SKILL_KNIFE:
	case SKILL_SWORD:
	case SKILL_PISTOL:
	case SKILL_RIFLE:
	case SKILL_SMG:
	case SKILL_SHOTGUN:
	case SKILL_DRIVING:
	case SKILL_STEALTH:
	case SKILL_THROWING:
	case SKILL_DODGE:
		return ATTRIBUTE_AGILITY;
	case SKILL_DISGUISE:
	case SKILL_SEDUCTION:
	case SKILL_PERSUASION:
		return ATTRIBUTE_CHARISMA;
	case SKILL_ART:
	case SKILL_MUSIC:
		return ATTRIBUTE_HEART;
	case SKILL_RELIGION:
	case SKILL_BUSINESS:
	case SKILL_WRITING:
	case SKILL_PSYCHOLOGY:
	case SKILL_SECURITY:
	case SKILL_TAILORING:
	case SKILL_TEACHING:
	case SKILL_FIRSTAID:
	case SKILL_SCIENCE:
	case SKILL_LAW:
	case SKILL_COMPUTERS:
	case SKILL_STREETSENSE:
	default:
		return ATTRIBUTE_INTELLIGENCE;
	}
}