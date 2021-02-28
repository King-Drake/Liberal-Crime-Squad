#pragma once

struct Deprecatednewsstoryst
{
	short type, view;
	char claimed;
	short politics_level, violence_level;
	DeprecatedCreature *cr;
	vector<int> crime;
	long loc, priority, page, guardianpage;
	char positive;
	short siegetype;
	Deprecatednewsstoryst() : claimed(1), politics_level(0), violence_level(0), cr(NULL), loc(-1) { }
};

