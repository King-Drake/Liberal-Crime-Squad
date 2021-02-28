
#pragma once

struct Deprecatedsquadst
{
	char name[SQUAD_NAMELEN];
	DeprecatedCreature *squad[6];
	ActivityST activity;
	int id;
	vector<Item *> loot;

	char stance; // Squad's site action stance: high profile, low profile, etc.

	Deprecatedsquadst()
	{
		for (int p = 0; p < 6; p++) squad[p] = NULL;
		strcpy(name, "");
		activity.type = ACTIVITY_NONE, id = -1, stance = SQUADSTANCE_STANDARD;
	}
	~Deprecatedsquadst() { delete_and_clear(loot); }
	/* tells how many total members a squad has (including dead members) */
	int squadsize() {
		int squadsize(const Deprecatedsquadst *st);
		return squadsize(this);
	}
	/* tells how many members a squad has who are alive */
	int squadalive() {
		int squadalive(const Deprecatedsquadst *st);
		return squadalive(this);
	}
};

int activesquadSize();
int activesquadAlive();