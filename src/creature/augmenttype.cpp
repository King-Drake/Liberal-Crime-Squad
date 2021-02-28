

#include "../includes50.h"
#include "../constStringaugmenttype.h"

int AugmentType::number_of_augmenttypes = 0;


AugmentType::AugmentType(const std::string& xmlstring) : max_age_(-1), min_age_(-1), cost_(0), difficulty_(5)
{
	id_ = number_of_augmenttypes++;
	CMarkup xml;
	xml.SetDoc(xmlstring);
	xml.FindElem();
	idname_ = xml.GetAttrib(tag_idname);
	if (!len(idname_))
	{
		idname_ = LACKS_IDNAME + tostring(id_);
		xmllog.log(AUGMENT_TYPE_SPACE + tostring(id_) + LACKS_IDNAME_LOWERCASE);
	}
	xml.IntoElem();
	while (xml.FindElem())
	{
		std::string element = xml.GetTagName();
		if (augmentTags.count(element)) {
			switch (augmentTags[element]) {
			case ENUM_tag_name:
				name_ = xml.GetData();
				break;
			case ENUM_tag_type:
				type_ = augment_string_to_enum(xml.GetData());
				break;
			case ENUM_tag_attribute:
				attribute_ = attribute_string_to_enum(xml.GetData());
				break;
			case ENUM_tag_effect:
				effect_ = atoi(xml.GetData().c_str());
				break;
			case ENUM_tag_description:
				description_ = xml.GetData();
				break;
			case ENUM_tag_max_age:
				max_age_ = atoi(xml.GetData().c_str());
				break;
			case ENUM_tag_min_age:
				min_age_ = atoi(xml.GetData().c_str());
				break;
			case ENUM_tag_cost:
				cost_ = atoi(xml.GetData().c_str());
				break;
			case ENUM_tag_difficulty:
				difficulty_ = atoi(xml.GetData().c_str());
				break;
			}
		}
	}
}
void AugmentType::make_augment(Augmentation& au)
{
	au.name = get_name();
	au.type = get_type();
	au.attribute = get_attribute();
	au.effect = get_effect();
}