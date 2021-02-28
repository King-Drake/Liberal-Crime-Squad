


#include "../includes51.h"
#include "../constStringaugmentation.h"

std::string Augmentation::get_name(int au)
{
	switch (au)
	{
	case AUGMENTATION_HEAD: return CONST_X_HEAD;
	case AUGMENTATION_BODY: return CONST_X_BODY;
	case AUGMENTATION_ARMS: return CONST_X_ARMS;
	case AUGMENTATION_LEGS: return CONST_X_LEGS;
	case AUGMENTATION_SKIN: return CONST_X_SKIN;
	default: return CONSERVATIVE_BUG;
	}
}
std::string Augmentation::showXml() const
{
	CMarkup xml;
	xml.AddElem(tag_augmentation);
	xml.IntoElem();
	xml.AddElem(tag_name, name);
	xml.AddElem(tag_type, type);
	xml.AddElem(tag_attribute, attribute);
	xml.AddElem(tag_effect, effect);
	xml.AddElem(tag_value, value);
	return xml.GetDoc();
}
Augmentation::Augmentation(const std::string& inputXml)
{
	CMarkup xml;
	xml.SetDoc(inputXml);
	xml.FindElem();
	xml.IntoElem();
	while (xml.FindElem())
	{
		std::string tag = xml.GetTagName();
		if (tag == tag_name)
			name = xml.GetData();
		else if (tag == tag_type)
			type = atoi(xml.GetData().c_str());
		else if (tag == tag_attribute)
			attribute = atoi(xml.GetData().c_str());
		else if (tag == tag_effect)
			effect = atoi(xml.GetData().c_str());
		else if (tag == tag_value)
			value = atoi(xml.GetData().c_str());
	}
}

int augment_string_to_enum(const string& augmentname)
{
	if (augmentname == tag_head)
		return AUGMENTATION_HEAD;
	else if (augmentname == tag_body)
		return AUGMENTATION_BODY;
	else if (augmentname == tag_arms)
		return AUGMENTATION_ARMS;
	else if (augmentname == tag_legs)
		return AUGMENTATION_LEGS;
	else if (augmentname == tag_skin)
		return AUGMENTATION_SKIN;
	else
		return -1;
}