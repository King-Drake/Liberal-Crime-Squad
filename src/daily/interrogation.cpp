



/*
Copyright (c) 2002,2003,2004 by Tarn Adams                                            //
                                                                                      //
This file is part of Liberal Crime Squad.                                             //
                                                                                    //
    Liberal Crime Squad is free software; you can redistribute it and/or modify     //
    it under the terms of the GNU General Public License as published by            //
    the Free Software Foundation; either version 2 of the License, or               //
    (at your option) any later version.                                             //
                                                                                    //
    Liberal Crime Squad is distributed in the hope that it will be useful,          //
    but WITHOUT ANY WARRANTY; without even the implied warranty of                  //
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the                  //
    GNU General Public License for more details.                                    //
                                                                                    //
    You should have received a copy of the GNU General Public License               //
    along with Liberal Crime Squad; if not, write to the Free Software              //
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   02111-1307   USA     //
*/
// Clear sidebar
#include "../includes42.h"
#include "../constStringinterrogation.h"
#include <algorithm>
void clear_interrogation_sidebar()
{
	for (int i = 4; i < 23; i++)
		mvaddstrAlt(i, 40, CONST_34_SPACES); // 34 spaces
}
// Shows the InterrogationST data at the right side of the screen
void show_interrogation_sidebar(DeprecatedCreature * cr, DeprecatedCreature * a)
{
	clear_interrogation_sidebar();
	map<long, struct Float_Zero>& rapport = cr->activity.intr()->rapport;
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(4, 40, CONST_PRISONER);
	set_color_easy(RED_ON_BLACK_BRIGHT);
	addstrAlt(cr->getNameAndAlignment().name);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(6, 40, CONST_HEALTH);
	printhealthstat(cr->getCreatureHealth(), 6, 48, 0);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(7, 40, HEART_COLON);
	addstrAlt(cr->get_attribute(ATTRIBUTE_HEART, true));
	mvaddstrAlt(8, 40, CONST_WISDOM);
	addstrAlt(cr->get_attribute(ATTRIBUTE_WISDOM, true));
	mvaddstrAlt(9, 40, CONST_HEALTH);
	addstrAlt(cr->get_attribute(ATTRIBUTE_HEALTH, true));
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(13, 40, CONST_LEAD_INTERROGATOR);
	set_color_easy(GREEN_ON_BLACK_BRIGHT);
	addstrAlt(a->getNameAndAlignment().name);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(15, 40, CONST_HEALTH);
	printhealthstat(a->getCreatureHealth(), 16, 48, 0);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(17, 40, CONST_PSYCHOLOGY_SKILL);
	addstrAlt(a->get_skill(SKILL_PSYCHOLOGY));
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(18, 40, HEART_COLON);
	addstrAlt(a->get_attribute(ATTRIBUTE_HEART, true));
	mvaddstrAlt(19, 40, CONST_WISDOM);
	addstrAlt(a->get_attribute(ATTRIBUTE_WISDOM, true));
	mvaddstrAlt(20, 40, CONST_OUTFIT);
	addstrAlt(a->get_armor().get_name());
	// What would 4, 2, 0, -2, -3, and/or -5 mean? (Some of these may not exist) -- LK
	// These are greater than and less than comparisons, so they are testing ranges -Fox
	string line_one;
	string line_two = "";
	if (rapport[a->id] > 3)
	{
		line_one = CONST_THE_CONSERVATIVE_CLINGS_HELPLESSLY;
		line_two = CONST_TO;
		line_two += string(a->getNameAndAlignment().name);
		line_two += CONST_AS_ITS_ONLY_FRIEND;
	}
	else if (rapport[a->id] > 1)
	{
		line_one = CONST_THE_CONSERVATIVE_LIKES;
		line_one += string(a->getNameAndAlignment().name);
		line_one += singleDot;
	}
	else if (rapport[a->id] > -1)
	{
		line_one = CONST_THE_CONSERVATIVE_IS_UNCOOPERATIVE;
		line_two = CONST_TOWARD;
		line_two += string(a->getNameAndAlignment().name);
		line_two += singleDot;
	}
	else if (rapport[a->id] > -4)
	{
		line_one = CONST_THE_CONSERVATIVE_HATES;
		line_one += string(a->getNameAndAlignment().name);
		line_one += singleDot;
	}
	else
	{
		line_one = CONST_THE_CONSERVATIVE_WOULD_LIKE_TO;
		line_two, CONST_X_MURDER_SPACE;
		line_two += string(a->getNameAndAlignment().name);
		line_two += singleDot;
	}
	mvaddstrAlt(22, 40, line_one);
	if (len(line_two)) {
		mvaddstrAlt(23, 40, line_two);
	}
}
void printInterrogationMenu(bool techniques[6], DeprecatedCreature * cr, DeprecatedCreature * a) {
	int c = -1;
	do
	{

		if (techniques[TECHNIQUE_KILL])
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(2, 0, CONST_THE_EXECUTION_OF_AN_AUTOMATON);
		}
		else
		{
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(2, 0, CONST_SELECTING_A_LIBERAL_INTERROGATION_PLAN);
		}
		if (techniques[TECHNIQUE_KILL])set_color_easy(BLACK_ON_BLACK_BRIGHT);
		else set_color_easy(techniques[TECHNIQUE_TALK] ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);

		mvaddstrAlt(4, 0, CONST_A);

		if (!techniques[TECHNIQUE_TALK]) addstrAlt(CONST_NO_VERBAL_CONTACT);
		else addstrAlt(CONST_ATTEMPT_TO_CONVERT);

		if (!techniques[TECHNIQUE_KILL])set_color_easy(techniques[TECHNIQUE_RESTRAIN] ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);

		mvaddstrAlt(5, 0, CONST_B);
		if (!techniques[TECHNIQUE_RESTRAIN]) addstrAlt(CONST_NO);

		addstrAlt(CONST_PHYSICAL_RESTRAINTS);
		if (!techniques[TECHNIQUE_KILL])set_color_easy(techniques[TECHNIQUE_BEAT] ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);

		mvaddstrAlt(6, 0, CONST_C);

		if (!techniques[TECHNIQUE_BEAT]) addstrAlt(CONST_NOT);

		addstrAlt(CONST_VIOLENTLY_BEATEN);

		if (!techniques[TECHNIQUE_KILL])set_color_easy(techniques[TECHNIQUE_PROPS] ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);

		mvaddstrAlt(7, 0, CONST_D);

		if (!techniques[TECHNIQUE_PROPS])addstrAlt(CONST_NO);

		addstrAlt(CONST_EXPENSIVE_PROPS);
		mvaddstrAlt(7, 27, CONST_250);

		if (!techniques[TECHNIQUE_KILL])set_color_easy(techniques[TECHNIQUE_DRUGS] ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);

		mvaddstrAlt(8, 0, CONST_E);

		if (!techniques[TECHNIQUE_DRUGS])addstrAlt(CONST_NO);

		addstrAlt(CONST_HALLUCINOGENIC_DRUGS);
		mvaddstrAlt(8, 28, CONST_50);

		if (techniques[TECHNIQUE_KILL])set_color_easy(RED_ON_BLACK_BRIGHT);
		else set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(10, 0, CONST_K_KILL_THE_HOSTAGE);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(12, 0, CONST_PRESS_ENTER_TO_CONFIRM_THE_PLAN);
		show_interrogation_sidebar(cr, a);
		c = getkeyAlt();
		if (c >= 'a'&&c <= 'e') { techniques[c - 'a'] = !techniques[c - 'a']; }
		if (c == 'k') { techniques[TECHNIQUE_KILL] = !techniques[TECHNIQUE_KILL]; }
	} while (c != 'x' && c != ENTER && c != ESC && c != SPACEBAR);
}
void attemptExecution(DeprecatedCreature * cr) {

	vector<DeprecatedCreature *> temppool;
	findAllTendersToThisHostage(cr, temppool);
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_THE_FINAL_EDUCATION_OF, gamelog);
	addstrAlt(cr->getNameAndAlignment().name, gamelog);
	addstrAlt(CONST_DAY, gamelog);
	addstrAlt(cr->joindays, gamelog);
	gamelog.newline();
	DeprecatedCreature *a = NULL;
	for (int i = 0; i < len(temppool); i++)
		if (LCSrandom(50) < temppool[i]->juice ||
			LCSrandom(9) + 1 >= temppool[i]->get_attribute(ATTRIBUTE_HEART, 0))
		{
			a = temppool[i]; break;
		}
	if (a)
	{
		set_color_easy(MAGENTA_ON_BLACK);
		cr->die();
		mvaddstrAlt(13, 0, a->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_EXECUTES, gamelog);
		addstrAlt(cr->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_BY, gamelog);
		addstrAlt(pickrandom(execution), gamelog);
		//show_interrogation_sidebar(cr,a);
		pressAnyKey();
		if (LCSrandom(a->get_attribute(ATTRIBUTE_HEART, false)) > LCSrandom(3))
		{
			gamelog.newline();
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
			mvaddstrAlt(14, 0, a->getNameAndAlignment().name, gamelog);
			addstrAlt(feels_sick_and, gamelog);
			a->adjust_attribute(ATTRIBUTE_HEART, -1);
			mvaddstrAlt(15, 0, pickrandom(feels_sick), gamelog);
		}
		else if (!LCSrandom(3))
		{
			gamelog.newline();
			set_color_easy(CYAN_ON_BLACK_BRIGHT);
			mvaddstrAlt(14, 0, a->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_GROWS_COLDER, gamelog);
			a->adjust_attribute(ATTRIBUTE_WISDOM, +1);
		}
		gamelog.nextMessage();
	}
	else
	{
		set_color_easy(YELLOW_ON_BLACK);
		mvaddstrAlt(13, 0, CONST_THERE_IS_NO_ONE_ABLE_TO_GET_UP_THE_NERVE_TO, gamelog);
		mvaddstrAlt(14, 0, CONST_EXECUTE, gamelog);
		addstrAlt(cr->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_IN_COLD_BLOOD, gamelog);
		gamelog.nextMessage();
	}
	pressAnyKey();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THIS);
	pressAnyKey();
}
char feelTheDrugUse(DeprecatedCreature *cr, DeprecatedCreature *doctor) {
	char emptyDrugs = 0;
	cr->adjust_attribute(ATTRIBUTE_HEALTH, -1);
	pressAnyKey();
	mvaddstrAlt(7, 0, cr->getNameAndAlignment().name, gamelog);
	addstrAlt(CONST_FOAMS_AT_THE_MOUTH_AND_ITS_EYES_ROLL_BACK_IN_ITS_SKULL, gamelog);
	gamelog.newline();
	pressAnyKey();
	mvaddstrAlt(8, 0, doctor->getNameAndAlignment().name, gamelog);
	int y = 8;
	if (cr->get_attribute(ATTRIBUTE_HEALTH, false) <= 0 || !doctor->get_skill(SKILL_FIRSTAID)) // he's dead, Jim
	{
		if (doctor->get_skill(SKILL_FIRSTAID))
		{ // we have a real doctor but the patient is still dead anyway
			addstrAlt(CONST_USES_A_DEFIBRILLATOR_REPEATEDLY_BUT, gamelog);
			addstrAlt(cr->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_FLATLINES, gamelog);
		}
		else
		{
			if (lawList[LAW_FREESPEECH] == -2)
				addstrAlt(CONST_HAS_A_PANIC_ATTACK_AND_MAKES_A_STINKY, gamelog);
			else
			{
				addstrAlt(CONST_HAS_A_PANIC_ATTACK_AND_SHITS, gamelog);
				addstrAlt(doctor->hisher(), gamelog);
				addstrAlt(CONST_PANTS, gamelog);
			}
		}
		gamelog.newline();
		pressAnyKey();
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		if (doctor->get_skill(SKILL_FIRSTAID))
		{
			mvaddstrAlt(9, 0, CONST_IT_IS_A_LETHAL_OVERDOSE_IN, gamelog);
			addstrAlt(cr->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_S_WEAKENED_STATE, gamelog);
		}
		else
		{
			mvaddstrAlt(9, 0, cr->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_DIES_DUE_TO, gamelog);
			addstrAlt(doctor->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_S_INCOMPETENCE_AT_FIRST_AID, gamelog);
		}
		gamelog.newline();
		cr->die();
	}
	else
	{
		if (doctor->skill_check(SKILL_FIRSTAID, DIFFICULTY_CHALLENGING)) // is the doctor AWESOME?
		{
			doctor->train(SKILL_FIRSTAID, 5 * max(10 - doctor->get_skill(SKILL_FIRSTAID), 0), 10); // can train up to 10
			addstrAlt(CONST_DEFTLY_RESCUES_IT_FROM_CARDIAC_ARREST_WITH_A_DEFIBRILLATOR, gamelog); // not long enough for near-death experience
			gamelog.newline();
			pressAnyKey();
			mvaddstrAlt(9, 0, doctor->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_SKILLFULLY_SAVES, gamelog);
			addstrAlt(cr->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_FROM_ANY_HEALTH_DAMAGE, gamelog);
			cr->adjust_attribute(ATTRIBUTE_HEALTH, +1); // no permanent health damage from a skilled doctor
			emptyDrugs = 1;
		}
		else
		{
			doctor->train(SKILL_FIRSTAID, 5 * max(5 - doctor->get_skill(SKILL_FIRSTAID), 0), 5); // can train up to 5
			addstrAlt(CONST_CLUMSILY_RESCUES_IT_FROM_CARDIAC_ARREST_WITH_A_DEFIBRILLATOR, gamelog);
			gamelog.newline();
			pressAnyKey();
			mvaddstrAlt(9, 0, cr->getNameAndAlignment().name, gamelog);
			if (cr->get_skill(SKILL_RELIGION)) // the patient was out long enough to have a near-death experience
				addstrAlt(CONST_HAD_A_NEAR_DEATH_EXPERIENCE_AND_MET_GOD_IN_HEAVEN, gamelog);
			else addstrAlt(CONST_HAD_A_NEAR_DEATH_EXPERIENCE_AND_MET_JOHN_LENNON, gamelog);
			emptyDrugs = 2;
		}
		gamelog.newline();
	}
	return emptyDrugs;
}

string acquireMapFromWork(const int worklocation) {

	if (LocationsPool::getInstance().getLocationType(worklocation) <= SITE_RESIDENTIAL_SHELTER)
		return CONST_UNFORTUNATELY_NONE_OF_IT_IS_USEFUL_TO_THE_LCS;
	else
	{
		return CONST_A_DETAILED_MAP_HAS_BEEN_CREATED_OF + LocationsPool::getInstance().getLocationName(worklocation) + singleDot;
	}
}


bool attemptToOutsmartCaptor(DeprecatedCreature *cr, DeprecatedCreature *a, const bool drugs, int& y) {
	//Failure to break religious convictions
	if (cr->get_skill(SKILL_RELIGION) > a->get_skill(SKILL_RELIGION) + a->get_skill(SKILL_PSYCHOLOGY) && !drugs)
	{
		moveAlt(y++, 0);
		addstrAlt(failToBreakReligion(a->getNameAndAlignment().name, cr->getNameAndAlignment().name), gamelog);
		gamelog.newline();
		a->train(SKILL_RELIGION, cr->get_skill(SKILL_RELIGION) * 4);
	}
	//Failure to persuade entrenched capitalists
	else if (cr->get_skill(SKILL_BUSINESS) > a->get_skill(SKILL_BUSINESS) + a->get_skill(SKILL_PSYCHOLOGY) && !drugs)
	{
		moveAlt(y++, 0);
		addstrAlt(failedToBreakBusiness(a->getNameAndAlignment().name, cr->getNameAndAlignment().name), gamelog);
		gamelog.newline();
		a->train(SKILL_BUSINESS, cr->get_skill(SKILL_BUSINESS) * 4);
	}
	//Failure to persuade scientific minds
	else if (cr->get_skill(SKILL_SCIENCE) > a->get_skill(SKILL_SCIENCE) + a->get_skill(SKILL_PSYCHOLOGY) && !drugs)
	{
		moveAlt(y++, 0);
		addstrAlt(failedToBreakScience(a->getNameAndAlignment().name, cr->getNameAndAlignment().name), gamelog);

		gamelog.newline();
		a->train(SKILL_SCIENCE, cr->get_skill(SKILL_SCIENCE) * 4);
	}
	else {
		return false;
	}
	return true;


}
void getCreatureWorkplaceMaps(DeprecatedCreature* cr, int &y, const string aname) {
	mvaddstrAlt(y, 0, cr->getNameAndAlignment().name, gamelog);
	addstrAlt(CONST_REVEALS_DETAILS_ABOUT_THE, gamelog);
	addstrAlt(LocationsPool::getInstance().getLocationName(cr->worklocation), gamelog);
	addstrAlt(singleDot, gamelog);
	gamelog.newline();
	if (LocationsPool::getInstance().getLocationType(cr->worklocation) <= SITE_RESIDENTIAL_SHELTER)
		mvaddstrAlt(++y, 0, CONST_UNFORTUNATELY_NONE_OF_IT_IS_USEFUL_TO_THE_LCS, gamelog);
	else
	{
		mvaddstrAlt(++y, 0, aname, gamelog);
		addstrAlt(WAS_ABLE_TO_CREATE_MAP, gamelog);
	}
	LocationsPool::getInstance().setLocationMappedAndUnhidden(cr->worklocation);

}

bool attemptSway(DeprecatedCreature *cr, DeprecatedCreature *a, const int attack, map<long, struct Float_Zero>(&rapport), char& turned, int& y) {

	//Target is swayed by Liberal Reason -- skilled interrogators, time held,
	//and rapport contribute to the likelihood of this
	if (!(cr->attribute_check(ATTRIBUTE_WISDOM, attack / 6)))
	{
		if (cr->juice > 0)
		{
			cr->juice -= attack;
			if (cr->juice < 0) cr->juice = 0;
		}
		if (cr->get_attribute(ATTRIBUTE_HEART, false) < 10)
			cr->adjust_attribute(ATTRIBUTE_HEART, +1);
		//Improve rapport with interrogator
		rapport[a->id] += 1.5;
		//Join LCS??
		//1) They were liberalized
		if (cr->get_attribute(ATTRIBUTE_HEART, true) > cr->get_attribute(ATTRIBUTE_WISDOM, true) + 4) turned = 1;
		//2) They were befriended
		if (rapport[a->id] > 4) turned = 1;
		mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
		addstrAlt(pickrandom(partial_conversion), gamelog);
		gamelog.newline();
		if (LocationsPool::getInstance().isLocationMapped(cr->worklocation) == 0 && !LCSrandom(5))
		{
			y++;
			getCreatureWorkplaceMaps(cr, y, a->getNameAndAlignment().name);
		}
	}
	else {
		return false;
	}
	return true;
}

void interrogaterNotOutsmarted(DeprecatedCreature *cr, DeprecatedCreature *a, const bool props, map<long, struct Float_Zero>(&rapport), int& y) {

	//Target is not sold on the LCS arguments and holds firm
	//This is the worst possible outcome if you use props
	if (!(cr->skill_check(SKILL_PERSUASION, a->get_attribute(ATTRIBUTE_HEART, true))) || props)
	{
		//Not completely unproductive; builds rapport
		rapport[a->id] += 0.2f;
		mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_HOLDS_FIRM, gamelog);
		gamelog.newline();
	}
	//Target actually wins the argument so successfully that the Liberal
	//interrogator's convictions are the ones that are shaken
	else
	{
		//Consolation prize is that they end up liking the
		//liberal more
		rapport[a->id] += 0.5f;
		a->adjust_attribute(ATTRIBUTE_WISDOM, +1);
		mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_TURNS_THE_TABLES_ON, gamelog);
		addstrAlt(a->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
		gamelog.newline();
		//show_interrogation_sidebar(cr,a);
		pressAnyKey();
		mvaddstrAlt(y++, 0, a->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_HAS_BEEN_TAINTED_WITH_WISDOM, gamelog);
		gamelog.newline();
	}
}

void creaturePossiblyLosesHeartOrGainsWisdom(DeprecatedCreature* a, int &y) {
	if (LCSrandom(a->get_attribute(ATTRIBUTE_HEART, false)) > LCSrandom(3))
	{
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		mvaddstrAlt(y++, 0, a->getNameAndAlignment().name, gamelog);
		addstrAlt(feels_sick_and, gamelog);
		a->adjust_attribute(ATTRIBUTE_HEART, -1);
		mvaddstrAlt(y++, 0, pickrandom(feels_sick), gamelog);
		gamelog.newline();
	}
	else if (!LCSrandom(3))
	{
		set_color_easy(CYAN_ON_BLACK_BRIGHT);
		mvaddstrAlt(y++, 0, a->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_GROWS_COLDER, gamelog);
		gamelog.newline();
		a->adjust_attribute(ATTRIBUTE_WISDOM, +1);
	}
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
}

string creatureIsHurtAndMightDie(DeprecatedCreature* cr) {
	string output;
	if (cr->get_attribute(ATTRIBUTE_HEALTH, false) > 1)
	{
		cr->adjust_attribute(ATTRIBUTE_HEALTH, -1);
		output = (cr->getNameAndAlignment().name);
		output += (CONST_IS_BADLY_HURT);
	}
	else
	{
		cr->set_attribute(ATTRIBUTE_HEALTH, 0);
		output = (cr->getNameAndAlignment().name);
		output += (CONST_S_WEAKENED_BODY_CRUMBLES_UNDER_THE_BRUTAL_ASSAULT);
		cr->die();
	}
	return output;
}

vector<string> printCreatureInterrogationStatus(DeprecatedCreature* cr, const bool restrain) {
	vector<string> output;

	output.push_back(CONST_X_THE_EDUCATION_OF_ + cr->getNameAndAlignment().name + CONST_DAY + tostring(cr->joindays));

	if (restrain)
	{
		output.push_back(CONST_THE_AUTOMATON + CONST_IS_TIED_HANDS_AND_FEET_TO_A_METAL_CHAIR);
		output.push_back(CONST_IN_THE_MIDDLE_OF_A_BACK_ROOM);
	}
	else
	{
		output.push_back(CONST_THE_AUTOMATON + CONST_IS_LOCKED_IN_A_BACK_ROOM);
		output.push_back(CONST_CONVERTED_INTO_A_MAKESHIFT_CELL);
	}

	return output;
}
void creatureConversion(DeprecatedCreature* cr, DeprecatedCreature* a, int &y) {
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(++y, 0, CONST_THE_AUTOMATON_HAS_BEEN_ENLIGHTENED_YOUR_LIBERAL_RANKS_ARE_SWELLING, gamelog);
	if (cr->get_attribute(ATTRIBUTE_HEART, true) > 7 &&
		cr->get_attribute(ATTRIBUTE_WISDOM, true) > 2 &&
		!LCSrandom(4) && (cr->flag & CREATUREFLAG_KIDNAPPED))
	{
		gamelog.newline();
		mvaddstrAlt(++y, 0, CONST_THE_CONVERSION_IS_CONVINCING_ENOUGH_THAT_THE_POLICE_NO_LONGER_CONSIDER_IT_A_KIDNAPPING, gamelog);
		//Actually liberalized -- they'll clean up the kidnapping story
		cr->flag &= ~CREATUREFLAG_MISSING;
		cr->flag &= ~CREATUREFLAG_KIDNAPPED;
	}
	cr->flag |= CREATUREFLAG_BRAINWASHED;
	y += 2;
	liberalize(*cr, false);
	cr->hireid = a->id;
	stat_recruits++;
	if (LocationsPool::getInstance().isLocationMapped(cr->worklocation) == 0 || LocationsPool::getInstance().isLocationHidden(cr->worklocation) == 1)
	{
		gamelog.newline();
		getCreatureWorkplaceMaps(cr, y, a->getNameAndAlignment().name);
	}
}
string tortureLineOne() {
	return singleSpace + pickrandom(low_heart_torture_props) + COMMA_SPACE;
}
string tortureLineTwo() {
	return  CONST_SCREAMING + pickrandom(screaming) + EXCLAMATION_POINT_SPACE + pickrandom(screaming) + CONST_IN_ITS_FACE;
}
void hostageDies(DeprecatedCreature *cr, DeprecatedCreature *a, int &y) {

	cr->die();
	stat_kills++;
	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(++y, 0, cr->getNameAndAlignment().name, gamelog);
	addstrAlt(CONST_IS_DEAD, gamelog);
	if (a)
	{
		addstrAlt(CONST_UNDER, gamelog);
		addstrAlt(a->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_S_INTERROGATION, gamelog);
	}
	else addstrAlt(singleDot, gamelog);
	set_color_easy(WHITE_ON_BLACK);
	y++;
	//show_interrogation_sidebar(cr,a);
	pressAnyKey();
	if (a)
	{
		if (LCSrandom(a->get_attribute(ATTRIBUTE_HEART, false)))
		{
			gamelog.newline();
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
			mvaddstrAlt(++y, 0, a->getNameAndAlignment().name, gamelog);
			addstrAlt(feels_sick_and, gamelog);
			a->adjust_attribute(ATTRIBUTE_HEART, -1);
			mvaddstrAlt(++y, 0, pickrandom(feels_sick), gamelog);
		}
		else if (!LCSrandom(3))
		{
			gamelog.newline();
			set_color_easy(CYAN_ON_BLACK_BRIGHT);
			mvaddstrAlt(++y, 0, a->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_GROWS_COLDER, gamelog);
			a->adjust_attribute(ATTRIBUTE_WISDOM, +1);
		}
	}
}
void attemptSuicide(DeprecatedCreature *cr, const bool restrain, int &y) {

	//can't commit suicide if restrained
	if (LCSrandom(6) || restrain)
	{
		set_color_easy(MAGENTA_ON_BLACK);
		mvaddstrAlt(++y, 0, cr->getNameAndAlignment().name, gamelog);
		//can't cut self if restrained
		if (!restrain && !LCSrandom(5)) {
			addstrAlt(singleSpace + pickrandom(self_wounding), gamelog);
			cr->blood -= LCSrandom(15) + 10;
		}
		else {
			addstrAlt(singleSpace + pickrandom(broods_over_death), gamelog);
		}
		gamelog.newline();
	}
	else
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		mvaddstrAlt(++y, 0, cr->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_HAS_COMMITTED_SUICIDE, gamelog);
		gamelog.newline(); //TODO: Next message?
		cr->die();
	}
	y++;
	//show_interrogation_sidebar(cr,a);
	pressAnyKey();
}
void illTellYouWhatIKnow(DeprecatedCreature *cr, DeprecatedCreature *a, const int forceroll, int &y) {

	gamelog.newline();
	if (cr->get_attribute(ATTRIBUTE_HEART, false) > 1) cr->adjust_attribute(ATTRIBUTE_HEART, -1);
	if (LCSrandom(2) && cr->juice > 0) { if ((cr->juice -= forceroll) < 0) cr->juice = 0; }
	else if (cr->get_attribute(ATTRIBUTE_WISDOM, false) > 1)
	{
		cr->set_attribute(ATTRIBUTE_WISDOM, cr->get_attribute(ATTRIBUTE_WISDOM, false) - (forceroll / 10));
		if (cr->get_attribute(ATTRIBUTE_WISDOM, false) < 1) cr->set_attribute(ATTRIBUTE_WISDOM, 1);
	}
	if (LocationsPool::getInstance().isLocationMapped(cr->worklocation) == 0 && !LCSrandom(5))
	{
		//show_interrogation_sidebar(cr,a);
		pressAnyKey();
		mvaddstrAlt(y++, 0, a->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_BEATS_INFORMATION_OUT_OF_THE_PATHETIC_THING, gamelog);
		gamelog.newline();
		pressAnyKey();
		mvaddstrAlt(y++, 0, acquireMapFromWork(cr->worklocation), gamelog);
		gamelog.newline();
		LocationsPool::getInstance().setLocationMappedAndUnhidden(cr->worklocation);
	}
}
DeprecatedCreature* getAttackAndLeadInterrogator(int &attack, const DeprecatedCreature* cr, const vector<DeprecatedCreature *> temppool) {
	int business = 0, religion = 0, science = 0;
	vector<int> _attack;
	for (DeprecatedCreature* temp : temppool)//int p = 0; p < len(temppool); p++)
	{
		int currentAttack = 0;
		if (temp) {
			if (temp->getNameAndAlignment().alive)
			{
				if (temp->get_skill(SKILL_BUSINESS) > business) {
					business = temp->get_skill(SKILL_BUSINESS);
				}
				if (temp->get_skill(SKILL_RELIGION) > religion) {
					religion = temp->get_skill(SKILL_RELIGION);
				}
				if (temp->get_skill(SKILL_SCIENCE) > science) {
					science = temp->get_skill(SKILL_SCIENCE);
				}
				currentAttack = (temp->get_attribute(ATTRIBUTE_HEART, true) -
					temp->get_attribute(ATTRIBUTE_WISDOM, true) +
					temp->get_skill(SKILL_PSYCHOLOGY) * 2);
				currentAttack += temp->get_armor().get_interrogation_basepower();
				if (currentAttack < 0) {
					currentAttack = 0;
				}
				if (currentAttack > attack) {
					attack = currentAttack;
				}
			}
		}
		_attack.push_back(currentAttack);
	}
	vector<int> goodp;
	for (int p = 0; p < len(temppool); p++) {
		if (temppool[p] && temppool[p]->getNameAndAlignment().alive&&_attack[p] == attack) {
			goodp.push_back(p);
		}
	}
	DeprecatedCreature* a = temppool[pickrandom(goodp)];
	attack += len(temppool);
	attack += cr->joindays;
	attack += business - cr->get_skill(SKILL_BUSINESS);
	attack += religion - cr->get_skill(SKILL_RELIGION);
	attack += science - cr->get_skill(SKILL_SCIENCE);
	attack += a->skill_roll(SKILL_PSYCHOLOGY) - cr->skill_roll(SKILL_PSYCHOLOGY);
	attack += cr->attribute_roll(ATTRIBUTE_HEART);
	attack -= cr->attribute_roll(ATTRIBUTE_WISDOM) * 2;
	return a;
}
void beatCaptive(DeprecatedCreature* a, DeprecatedCreature* cr, int &y, const vector<DeprecatedCreature *> temppool, const bool(&techniques)[6], map<long, struct Float_Zero>(&rapport)) {
	y++;
	int forceroll = 0;
	bool tortured = 0;
	for (int i = 0; i < len(temppool); i++)
	{
		//add interrogator's strength to beating strength
		forceroll += temppool[i]->attribute_roll(ATTRIBUTE_STRENGTH);
		//reduce rapport with each interrogator
		rapport[temppool[i]->id] -= 0.4f;
	}
	//Torture captive if lead interrogator has low heart
	//and you funded using extra supplies
	//
	//Yeah, you kinda don't want this to happen
	if (!(a->attribute_check(ATTRIBUTE_HEART, DIFFICULTY_EASY)) && techniques[TECHNIQUE_PROPS])
	{
		tortured = true;
		//Torture more devastating than normal beating
		forceroll *= 5;
		//Extremely bad for rapport with lead interrogator
		rapport[a->id] -= 3;
		mvaddstrAlt(y, 0, a->getNameAndAlignment().name + tortureLineOne(), gamelog);
		mvaddstrAlt(++y, 0, tortureLineTwo(), gamelog);
		gamelog.newline();
		if (cr->get_attribute(ATTRIBUTE_HEART, true) > 1) cr->adjust_attribute(ATTRIBUTE_HEART, -1);
		if (cr->get_attribute(ATTRIBUTE_WISDOM, true) > 1) cr->adjust_attribute(ATTRIBUTE_WISDOM, -1);
	}
	else
	{
		string guardsAdministerBeating;
		switch (len(temppool)) {
		case 1: // X beats the automaton
			guardsAdministerBeating = temppool[0]->getNameAndAlignment().name + CONST_BEATS;
			break;

		case 2: // X and Y beat the automaton
			guardsAdministerBeating = temppool[0]->getNameAndAlignment().name + AND + temppool[1]->getNameAndAlignment().name + CONST_BEAT;
			break;

		default: // cr->name's guards beat the automaton
			guardsAdministerBeating = cr->getNameAndAlignment().name + CONST_S_GUARDS_BEAT;
			break;
		}
		mvaddstrAlt(y, 0, guardsAdministerBeating + CONST_X_THE_AUTOMATON, gamelog);
		if (techniques[TECHNIQUE_PROPS])
		{
			addstrAlt(singleSpace, gamelog);
			addstrAlt(pickrandom(beat_with_props), gamelog);
		}
		addstrAlt(COMMA_SPACE, gamelog);
		mvaddstrAlt(++y, 0, pickrandom(words_meaning_screaming), gamelog);
		addstrAlt(QUOTATION_MARK);
		for (int i = 0; i < 3; i++)
		{
			addstrAlt(pickrandom(words_to_scream), gamelog);
			if (i < 2) addstrAlt(EXCLAMATION_POINT_SPACE, gamelog);
		}
		addstrAlt(CONST_IN_ITS_FACE, gamelog);
		gamelog.newline();
	}
	y++;
	cr->blood -= (5 + LCSrandom(5)) * (1 + techniques[TECHNIQUE_PROPS]);
	//show_interrogation_sidebar(cr,a);
	pressAnyKey();
	if (!(cr->attribute_check(ATTRIBUTE_HEALTH, forceroll)))
	{
		if (cr->skill_check(SKILL_RELIGION, forceroll))
		{
			mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
			addstrAlt(singleSpace + victimPrays(techniques[TECHNIQUE_DRUGS]), gamelog);
			gamelog.newline();

		}
		else if (forceroll >
			cr->get_attribute(ATTRIBUTE_WISDOM, true) * 3 +
			cr->get_attribute(ATTRIBUTE_HEART, true) * 3 +
			cr->get_attribute(ATTRIBUTE_HEALTH, true) * 3)
		{
			mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
			const string despair = getDespairString(techniques[TECHNIQUE_DRUGS], techniques[TECHNIQUE_RESTRAIN], cr->get_skill(SKILL_RELIGION));
			addstrAlt(despair, gamelog);

			illTellYouWhatIKnow(cr, a, forceroll, y);
		}
		else
		{
			mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_SEEMS_TO_BE_GETTING_THE_MESSAGE, gamelog);
			gamelog.newline();
			if (cr->juice > 0) if ((cr->juice -= forceroll) < 0) cr->juice = 0;
			if (cr->get_attribute(ATTRIBUTE_WISDOM, false) > 1)
			{
				cr->set_attribute(ATTRIBUTE_WISDOM, cr->get_attribute(ATTRIBUTE_WISDOM, false) - (forceroll / 10 + 1));
				if (cr->get_attribute(ATTRIBUTE_WISDOM, false) < 1) cr->set_attribute(ATTRIBUTE_WISDOM, 1);
			}
		}
		if (!(cr->attribute_check(ATTRIBUTE_HEALTH, forceroll / 3)))
		{
			//show_interrogation_sidebar(cr,a);
			pressAnyKey();
			string creatureInjury = creatureIsHurtAndMightDie(cr);
			mvaddstrAlt(y++, 0, creatureInjury, gamelog);
			gamelog.newline();
		}
	}
	else
	{
		mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_TAKES_IT_WELL, gamelog);
		gamelog.newline();
	}
	//show_interrogation_sidebar(cr,a);
	pressAnyKey();
	if (tortured && cr->getNameAndAlignment().alive)
	{
		creaturePossiblyLosesHeartOrGainsWisdom(a, y);
	}
}
/* hostage tending */
void tendhostage(DeprecatedCreature *cr, char &clearformess)
{
	if (cr->location == -1)
	{
		delete cr;
		return;
	}
	music.play(MUSIC_INTERROGATION);
	vector<DeprecatedCreature *> temppool;
	DeprecatedCreature *a = NULL;
	InterrogationST* &intr = cr->activity.intr();
	bool(&techniques)[6] = intr->techniques;
	map<long, struct Float_Zero>& rapport = intr->rapport;
	findAllTendersToThisHostage(cr, temppool);
	//possible hostage escape attempt if unattended or unrestrained
	if (!len(temppool) || !techniques[TECHNIQUE_RESTRAIN])
	{
		//CHECK FOR HOSTAGE ESCAPE
		if (LCSrandom(200) + 25 * len(temppool) <
			cr->get_attribute(ATTRIBUTE_INTELLIGENCE, true) +
			cr->get_attribute(ATTRIBUTE_AGILITY, true) +
			cr->get_attribute(ATTRIBUTE_STRENGTH, true) &&
			cr->joindays >= 5)
		{
			hostageEscapes(cr, clearformess);
			//delete InterrogationST data
			delete intr;
			return;
		}
	}
	if (!len(temppool)) return;
	clearformess = 1;
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_X_THE_EDUCATION_OF_);
	addstrAlt(cr->getNameAndAlignment().name);
	addstrAlt(CONST_DAY);
	addstrAlt(cr->joindays);
	pressAnyKey();
	set_color_easy(WHITE_ON_BLACK);

	{
		//each day, the attack roll is initialized to the number of days of the stay with
		//the LCS -- they will eventually break, but also eventually become too traumatized
		//to continue
		int attack = 0;
		a = getAttackAndLeadInterrogator(attack, cr, temppool);

		char turned = 0;
		{
			printInterrogationMenu(techniques, cr, a);
			if (techniques[TECHNIQUE_PROPS] && ledger.get_funds() >= 250)
				ledger.subtract_funds(250, EXPENSE_HOSTAGE);
			else techniques[TECHNIQUE_PROPS] = 0;
			if (techniques[TECHNIQUE_DRUGS] && ledger.get_funds() >= 50)
				ledger.subtract_funds(50, EXPENSE_HOSTAGE);

			else techniques[TECHNIQUE_DRUGS] = 0;

			if (techniques[TECHNIQUE_KILL]) // Kill the Hostage
			{
				attemptExecution(cr);
				if (cr->getNameAndAlignment().alive) {
					//Interrogation will continue as planned, with
					//these restrictions:
					techniques[TECHNIQUE_TALK] = 0; //don't talk to them today
					techniques[TECHNIQUE_BEAT] = 0; //don't beat them today
					techniques[TECHNIQUE_DRUGS] = 0; //don't administer drugs
													 //Food and restraint settings will be applied as normal
				}
				else {

					//delete InterrogationST information
					delete intr;
					stat_kills++;

					setAllCreatureActivities(ACTIVITY_NONE, temppool);

					return;
				}
			}
			eraseAlt();
		}

		attack += techniques[TECHNIQUE_RESTRAIN] ? 5 : 0;
		vector<string> status = printCreatureInterrogationStatus(cr, techniques[TECHNIQUE_RESTRAIN]);

		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, status[0], gamelog);
		gamelog.newline();

		mvaddstrAlt(2, 0, status[1], gamelog);
		mvaddstrAlt(3, 0, status[2], gamelog);

		gamelog.newline();
		//show_interrogation_sidebar(cr,a);
		pressAnyKey();
		int y = 4;
		if (techniques[TECHNIQUE_DRUGS]) // Hallucinogenic drugs
		{

			mvaddstrAlt(5, 0, CONST_IT_IS_SUBJECTED_TO_DANGEROUS_HALLUCINOGENS, gamelog);
			gamelog.newline();
			int drugbonus = 10 + a->get_armor().get_interrogation_drugbonus(); // we won't apply this JUST yet
																			   //Possible permanent health damage
			if (LCSrandom(50) < ++intr->druguse)
			{
				y = 9;

				DeprecatedCreature* doctor = a; // the lead interrogator is doctor by default
				int maxskill = doctor->get_skill(SKILL_FIRSTAID);
				for (int i = 0; i < len(temppool); i++) // search for the best doctor
					if (temppool[i]->get_skill(SKILL_FIRSTAID) > maxskill)
						maxskill = (doctor = temppool[i])->get_skill(SKILL_FIRSTAID); // we found a doctor


				int drugeffect = feelTheDrugUse(cr, doctor);
				if (drugeffect == 0) {

				}
				else if (drugeffect == 1) {

					techniques[TECHNIQUE_DRUGS] = (intr->druguse = drugbonus = 0); // drugs eliminated from the system (zeroing out 3 variables with 1 line of code)
					rapport[doctor->id] += 0.5f; // rapport bonus for having life saved by doctor
				}
				else if (drugeffect == 2) {

					drugbonus *= 2; // the near-death experience doubles the drug bonus, since the hostage is spaced out afterwards
					rapport[doctor->id] += 0.5f; // rapport bonus for having life saved by doctor
				}


			}
			attack += drugbonus; // now we finally apply the drug bonus
			moveAlt(++y, 0);
			//show_interrogation_sidebar(cr,a);
			pressAnyKey();
		}
		if (techniques[TECHNIQUE_BEAT] && !turned&&cr->getNameAndAlignment().alive) // Beating
		{
			beatCaptive(a, cr, y, temppool, techniques, rapport);
		}
		// Verbal Interrogation
		if (techniques[TECHNIQUE_TALK] && cr->getNameAndAlignment().alive)
		{
			float rapport_temp = rapport[a->id];
			if (!techniques[TECHNIQUE_RESTRAIN])attack += 5;
			attack += int(rapport[a->id] * 3);
			mvaddstrAlt((++y)++, 0, a->getNameAndAlignment().name, gamelog);
			if (techniques[TECHNIQUE_PROPS])//props
			{
				attack += 10;
				addstrAlt(singleSpace, gamelog);
				addstrAlt(pickrandom(use_props), gamelog);
				gamelog.newline();
			}
			else
			{
				int which_discuss = LCSrandom(discuss.size() + vanilla_recruit.size());
				if (which_discuss < discuss.size()) {
					addstrAlt(discuss[which_discuss][0], gamelog);
					addstrAlt(getview(LCSrandom(VIEWNUM - 3), true), gamelog);
					addstrAlt(discuss[which_discuss][1], gamelog);
				}
				else {
					addstrAlt(pickrandom(vanilla_recruit), gamelog);
				}
			}
			addstrAlt(cr->getNameAndAlignment().name, gamelog);
			addstrAlt(singleDot, gamelog);
			gamelog.newline();
			//Hallucinogenic drugs:
			//Re-interprets lead interrogator
			if (techniques[TECHNIQUE_DRUGS])
			{
				//show_interrogation_sidebar(cr,a);
				pressAnyKey();
				moveAlt(y++, 0);
				if (cr->skill_check(SKILL_PSYCHOLOGY, DIFFICULTY_CHALLENGING))
				{
					addstrAlt(cr->getNameAndAlignment().name);
					addstrAlt(singleSpace, gamelog);
					addstrAlt(pickrandom(resist_drugs), gamelog);
					gamelog.newline();
				}
				else if ((rapport[a->id] > 1 && !LCSrandom(3)) || !LCSrandom(10))
				{
					rapport_temp = 10;
					addstrAlt(cr->getNameAndAlignment().name + getFallsInLove(a->getNameAndAlignment().name, techniques[TECHNIQUE_RESTRAIN]), gamelog);
					gamelog.newline();
				}
				else if ((rapport[a->id] < -1 && LCSrandom(3)) || !LCSrandom(5))
				{
					attack = 0;
					addstrAlt(cr->getNameAndAlignment().name + getBadTrip(a->getNameAndAlignment().name, techniques[TECHNIQUE_RESTRAIN], rapport[a->id] < -3), gamelog);
					gamelog.newline();
				}
				else
				{
					int which_good_trip = LCSrandom(good_trip.size() + good_trip_companion.size());
					addstrAlt(cr->getNameAndAlignment().name, gamelog);
					if (which_good_trip < good_trip_companion.size()) {
						addstrAlt(good_trip_companion[which_good_trip][0], gamelog);
						addstrAlt(a->getNameAndAlignment().name, gamelog);
						addstrAlt(good_trip_companion[which_good_trip][1], gamelog);
					}
					else {
						addstrAlt(pickrandom(good_trip), gamelog);
					}
					gamelog.newline();
				}
			}
			//show_interrogation_sidebar(cr,a);
			pressAnyKey();
			if (cr->get_skill(SKILL_PSYCHOLOGY) > a->get_skill(SKILL_PSYCHOLOGY))
			{
				mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
				addstrAlt(outPsychologyCaptor(a->getNameAndAlignment().name), gamelog);

			}
			//Attempt to convert when the target is brutally treated will
			//just alienate them and make them cynical
			else if (techniques[TECHNIQUE_BEAT] || rapport_temp < -2)
			{
				mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
				addstrAlt(triedConvertingTheAbused(a->getNameAndAlignment().name), gamelog);

				gamelog.newline();
				if (a->skill_check(SKILL_SEDUCTION, DIFFICULTY_CHALLENGING))
				{
					//show_interrogation_sidebar(cr,a);
					pressAnyKey();
					mvaddstrAlt(y++, 0, a->getNameAndAlignment().name, gamelog);
					addstrAlt(feelsBadForAbused(cr->getNameAndAlignment().name), gamelog);
					gamelog.newline();
					rapport[a->id] += 0.7f;
					if (rapport[a->id] > 3)
					{
						//show_interrogation_sidebar(cr,a);
						pressAnyKey();
						mvaddstrAlt(y++, 0, cr->getNameAndAlignment().name, gamelog);
						addstrAlt(stockholmSyndrome(a->getNameAndAlignment().name), gamelog);
						gamelog.newline();
						if (rapport[a->id] > 5) turned = 1;
					}
				}
				if (cr->get_attribute(ATTRIBUTE_HEART, false) > 1) cr->adjust_attribute(ATTRIBUTE_HEART, -1);
			}
			else
				if (!attemptToOutsmartCaptor(cr, a, techniques[TECHNIQUE_DRUGS], y)) {
					if (!attemptSway(cr, a, attack, rapport, turned, y)) {
						interrogaterNotOutsmarted(cr, a, techniques[TECHNIQUE_PROPS], rapport, y);
					}
				}
			//show_interrogation_sidebar(cr,a);
			pressAnyKey();
		}
		//Lead interrogator gets bonus experience
		if (!techniques[TECHNIQUE_KILL])
		{
			a->train(SKILL_PSYCHOLOGY, attack / 2 + 1);
			//Others also get experience
			for (int i = 0; i < len(temppool); i++) temppool[i]->train(SKILL_PSYCHOLOGY, attack / 4 + 1);
		}
		//Possibly suicidal when heart is down to 1 and prisoner has already been
		//captive for a week without rescue
		if (!turned&&cr->getNameAndAlignment().alive&&cr->get_attribute(ATTRIBUTE_HEART, false) <= 1 && LCSrandom(3) && cr->joindays > 6)
		{
			attemptSuicide(cr, techniques[TECHNIQUE_RESTRAIN], y);
		}

		if (AUTOENLIGHTEN) {
			turned = 1;// Lucky!
		}
		//Death
		if (cr->getNameAndAlignment().alive == 0 || cr->blood < 1)
		{
			//delete InterrogationST information
			delete intr;
			hostageDies(cr, a, y);
			gamelog.nextMessage();
		}
		else if (turned)
		{
			//clear_interrogation_sidebar();
			//delete InterrogationST information
			delete intr;
			creatureConversion(cr, a, y);
			setAllCreatureActivities(ACTIVITY_NONE, temppool);
			if (cr->flag & CREATUREFLAG_MISSING && !(cr->flag & CREATUREFLAG_KIDNAPPED))
			{
				pressAnyKey();
				eraseAlt();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				gamelog.newline();
				mvaddstrAlt(1, 0, cr->getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_S_DISAPPEARANCE_HAS_NOT_YET_BEEN_REPORTED, gamelog);
				sleeperize_prompt(*cr, *a, 3);
				cr->flag &= ~CREATUREFLAG_MISSING;
				gamelog.nextMessage();
				return;
			}
		}
		if (cr->align == 1 || !cr->getNameAndAlignment().alive) {
			setAllCreatureActivities(ACTIVITY_NONE, temppool);
		}
	}
	gamelog.nextMessage();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THIS);
	pressAnyKey();
}