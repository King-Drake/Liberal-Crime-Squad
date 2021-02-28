#pragma once

struct Deprecateddatest
{
	long mac_id;
	vector<DeprecatedCreature *> date;
	short timeleft;
	int city;
	Deprecateddatest() : timeleft(0) { }
	~Deprecateddatest() { delete_and_clear(date); }
};
