


#include "includes70.h"
#include "constStringautomatedDataTests.h"
// CREATURENUM = 106
void addCigarbar(int creaturearray[106]) {
	for (int i = 0; i < 106; i++) {
		creaturearray[i]++;
	}

}
void automatedDataTests() {
	int carray[106];
	carray[0]++;
	mvaddstrAlt(0, 0, carray[0]);
	addCigarbar(carray);
	mvaddstrAlt(1, 0, carray[0]);
	addCigarbar(carray);
	mvaddstrAlt(2, 0, carray[0]);
	addCigarbar(carray);
	mvaddstrAlt(3, 0, carray[0]);
	pressAnyKey();

	clearAlt();
	for (int i = 0, k = 0; i < LAWNUM; i++) {
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, i);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, conservativeLegalArgument[i]);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, youAreStupidTalkAboutIssues[i]);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, issueTooLiberal[i]);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, conservatiseLaw[i]);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, liberalizeLaw[i]);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		for (int j = 0; j < 2; j++) {
			mvaddstrAlt(k++, 0, talkAboutTheIssues[i][j]); // 0~1
		}
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		for (int j = 0; j < 8; j++) {
			mvaddstrAlt(k++, 0, endgameLawStrings[i][j]); // 0~7
		}
		mvaddstrAlt(k++, 0, SUCCESS);
	}
	pressAnyKey();
	clearAlt();
	for (int i = 0, k = 0; i < VIEWNUM - 3; i++) {
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, i);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, issueEventString[i]);
	}
	pressAnyKey();
	clearAlt();
	for (int i = 0, k = 0; i < VIEWNUM; i++) {
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, i);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, discussIssues[i]);
		mvaddstrAlt(k++, 0, CONST_X_TEST);
		mvaddstrAlt(k++, 0, discussesIssues[i]);
	}
	pressAnyKey();
	clearAlt();
	testCreature();

}


// This, this requires a lot of prepwork to test the makecreature(...) method
#include "creature/creature.h"
#include "vehicle/vehicleType.h"
#include "vehicle/vehicle.h"

struct newGameArguments {
	const char recruits;
	const char base;
	const bool makelawyer;
	const bool gaylawyer;
	const bool sports_car;
	newGameArguments(char _recruits, char _base, bool _makelawyer, bool _gaylawyer, bool _sports_car) : recruits(_recruits), base(_base), makelawyer(_makelawyer), gaylawyer(_gaylawyer), sports_car(_sports_car) {}
};
void initiateNewgameLocations(DeprecatedCreature* newcr, const newGameArguments ngm);
void makecreature(DeprecatedCreature &cr, short type);
void testCreature() {

	// This, this requires a lot of prepwork to test the makecreature(...) method
	multipleCityMode = false;
	void make_world(bool hasmaps);
	make_world(false);
	bool makelawyer = false;
	bool gaylawyer = false;
	bool sports_car = false;
	char recruits = 1;
	char base = 21;
	DeprecatedCreature *newcr = new DeprecatedCreature;
	void recruitment_activity(DeprecatedCreature &cr);
	initiateNewgameLocations(newcr, newGameArguments(recruits, base, makelawyer, gaylawyer, sports_car));
	recruitment_activity(*newcr);

	for (int i = 0; i < CREATURENUM; i++) {
		DeprecatedCreature cr;
		for (int j = -2; j < 3; j++) {
			lawList[LAW_GUNCONTROL] = j;
			makecreature(cr, i);
		}
		if (i % 20 == 0) {
			pressAnyKey();
			clearAlt();
		}
		mvaddstrAlt(i % 20, 0, cr.getNameAndAlignment().name);

	}
	mvaddstrAlt(21, 0, "TEST COMPLETE");

	mvaddstrAlt(22, 0, "Please Restart");
	// Player should restart at this point.
	pressAnyKey();
}