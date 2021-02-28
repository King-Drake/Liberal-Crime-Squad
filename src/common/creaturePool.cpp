


#include "../includes58.h"
#include "../constStringOEMcreaturePool.h"
#include <algorithm>

vector<DeprecatedCreature *> pool;
CreaturePool singletonPool;
void addCreature(DeprecatedCreature* cr)
{
	pool.push_back(cr);
}
void CreaturePool::moveEverythingFrom(int cursite, int hs)
{
	for (int p = 0; p < lenpool(); p++)
	{
		if (pool[p]->location == cursite)pool[p]->location = hs;
		if (pool[p]->base == cursite)pool[p]->base = hs;
	}
}
void CreaturePool::stop_riding_me(int id_)
{
	for (int p = 0; p < lenpool(); p++)
		if (pool[p]->carid == id_)
			pool[p]->carid = -1;
}
void CreaturePool::stopAllBleeding()
{
	for (int p = 0; p < lenpool(); p++)
		for (int w = 0; w < BODYPARTNUM; w++)
			pool[p]->wound[w] &= ~WOUND_BLEEDING;
}
const bool CreaturePool::doesAnyoneLiveHere(int loc)
{
	for (int p = 0; p < lenpool(); p++) {
		if (pool[p]->base == loc) {
			return true;
		}
	}
	return false;
}
void CreaturePool::stop_preferring_me(int id_)
{
	for (int p = 0; p < lenpool(); p++)
		if (pool[p]->pref_carid == id_)
			pool[p]->pref_carid = -1;
}
void CreaturePool::clearAllBleedingAndEscapeFlags()
{
	for (int p = 0; p < lenpool(); p++)
	{
		pool[p]->flag &= ~CREATUREFLAG_JUSTESCAPED;
		for (int w = 0; w < BODYPARTNUM; w++)
		{
			pool[p]->wound[w] &= ~WOUND_BLEEDING;
		}
	}
}
void CreaturePool::outSleepers(int cursite, int base)
{
	for (int p = 0; p < lenpool(); p++)
	{
		if (pool[p]->flag&CREATUREFLAG_SLEEPER &&
			pool[p]->location == cursite)
		{
			pool[p]->flag &= ~CREATUREFLAG_SLEEPER;
			eraseAlt();
			mvaddstrAlt(8, 1, string_sleeper, gamelog);
			addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
			addstrAlt(HAS_BEEN_OUTED_BY_YOUR_ATTACK, gamelog);
			gamelog.newline();
			mvaddstrAlt(10, 1, THE_LIBERAL_IS_NOW_A_NORMAL_SQUAD_MEMBER, gamelog);
			gamelog.newline();
			pool[p]->base = base;
			pool[p]->location = pool[p]->base;
			pressAnyKey();
		}
	}
}
void CreaturePool::advanceCreaturesAtLocation(int cursite)
{
	for (int p = 0; p < lenpool(); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive) continue;
		if (pool[p]->squadid != -1) continue;
		if (pool[p]->location != cursite) continue;
		advancecreature(*pool[p]);
	}
}
void CreaturePool::arrestOrKillCCSSleepers()
{
	for (int p = 0; p < lenpool(); p++)
	{
		if (pool[p]->flag&CREATUREFLAG_SLEEPER)
		{
			if (pool[p]->type == CREATURE_CCS_VIGILANTE || pool[p]->type == CREATURE_CCS_ARCHCONSERVATIVE ||
				pool[p]->type == CREATURE_CCS_MOLOTOV || pool[p]->type == CREATURE_CCS_SNIPER)
			{
				pool[p]->flag &= ~CREATUREFLAG_SLEEPER;
				criminalize(*pool[p], LAWFLAG_RACKETEERING);
				capturecreature(*pool[p]);
			}
		}
	}
}
const int CreaturePool::liberal_guardian_writing_power()
{
	int power = 0;
	for (int i = 0; i < lenpool(); i++)
	{
		if (pool[i]->getNameAndAlignment().alive&&pool[i]->activity_type() == ACTIVITY_WRITE_GUARDIAN)
		{
			if (pool[i]->location != -1 &&
				LocationsPool::getInstance().get_specific_integer(INT_GETCOMPOUNDWALLS,pool[i]->location) & COMPOUND_PRINTINGPRESS)
			{
				pool[i]->train(SKILL_WRITING, LCSrandom(3)); // Experience gain
				power += pool[i]->skill_roll(SKILL_WRITING); // Record the writer on this topic
				criminalize(*pool[i], LAWFLAG_SPEECH); // Record possibly illegal speech activity
			}
			else pool[i]->set_activity_type(ACTIVITY_NONE);
		}
	}
	return power;
}
const int CreaturePool::howManyLivingPeopleAreHere(int l)
{
	int numpres = 0;
	for (int p = 0; p < lenpool(); p++)
	{
		if (pool[p]->location != l) continue; // People not at this base don't count
		if (!pool[p]->getNameAndAlignment().alive) continue; // Dead people don't count
		numpres++;
	}
	return numpres;
}
const int CreaturePool::countLiberals(int cursite)
{
	int libnum = 0;
	for (int p = 0; p < lenpool(); p++) {
		if (pool[p]->align == 1 &&
			pool[p]->getNameAndAlignment().alive&&
			pool[p]->location == cursite &&
			!(pool[p]->flag&CREATUREFLAG_SLEEPER)) {
			libnum++;
		}
	}
	return libnum;
}
bool CreaturePool::creaturePoolInitiated = false;
CreaturePool CreaturePool::getInstance() {
	if (!creaturePoolInitiated) {
		creaturePoolInitiated = true;
		singletonPool = CreaturePool();
	}
	return singletonPool;
}
void CreaturePool::delete_and_clear_pool() {
	delete_and_clear(pool);
}
void CreaturePool::setupDisband()
{
	for (int p = lenpool() - 1; p >= 0; p--)
	{
		if (!pool[p]->getNameAndAlignment().alive || pool[p]->flag&CREATUREFLAG_KIDNAPPED || pool[p]->flag&CREATUREFLAG_MISSING) delete_and_remove(pool, p);
		else if (!(pool[p]->flag&CREATUREFLAG_SLEEPER))
		{
			removesquadinfo(*pool[p]);
			pool[p]->hiding = -1;
		}
	}
}
const bool CreaturePool::isThisCarWantedByAnotherSquad(long vehicleID, int squadID)
{
	for (int p = 0; p < lenpool(); p++)
	{
		if (pool[p]->squadid != -1 && pool[p]->getNameAndAlignment().alive&&
			pool[p]->pref_carid == vehicleID && pool[p]->squadid != squadID)
		{
			return true;
		}
	}
	return false;
}
const string CreaturePool::getName(int p)
{
	return pool[p]->getNameAndAlignment().name;
}
void CreaturePool::moveAllSquadMembers(int l)
{
	int hs = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, l);
	//MOVE ALL ITEMS AND SQUAD MEMBERS
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->location == l) pool[p]->location = hs;
		if (pool[p]->base == l) pool[p]->base = hs;
	}
}
const int CreaturePool::lenpool() const {
	return len(pool);
}
void whoAreWaitingForRescue(vector<DeprecatedCreature *>& waiting_for_rescue, int cursite, short special) {
	for (int pl = 0; pl < len(pool); pl++)
	{
		if (pool[pl]->location == cursite &&
			!(pool[pl]->flag & CREATUREFLAG_SLEEPER) &&
			!(special == SPECIAL_PRISON_CONTROL_LOW && !(pool[pl]->getCreatureJustice().sentence > 0 && !pool[pl]->getCreatureJustice().deathpenalty)) && //Low is for normal time-limited sentences.
			!(special == SPECIAL_PRISON_CONTROL_MEDIUM && !(pool[pl]->getCreatureJustice().sentence < 0 && !pool[pl]->getCreatureJustice().deathpenalty)) && //Medium is for life sentences.
			!(special == SPECIAL_PRISON_CONTROL_HIGH && !pool[pl]->getCreatureJustice().deathpenalty)) //High is for death sentences.
			waiting_for_rescue.push_back(pool[pl]);
	}
}
DeprecatedCreature* findSleeperCarSalesman(int loc) {
	for (int p = 0; p < len(pool); p++)
		if (pool[p]->getNameAndAlignment().alive && (pool[p]->flag & CREATUREFLAG_SLEEPER) &&
			pool[p]->type == CREATURE_CARSALESMAN && LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,pool[p]->location) == LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,loc))
			return pool[p];
	return NULL;
}
map<short, string> issueEventString;
static void getissueeventstring(char* str)
{
	strcat(str, issueEventString[LCSrandom(VIEWNUM - 3)].data());
}

LOOP_CONTINUATION increment_completerecruitmeeting(const int p, Deprecatedrecruitst &r, int &y) {
	int c = getkeyAlt();
	if (c == 'c' && subordinatesleft(*pool[p]) && r.eagerness() >= 4)
	{
		mvaddstrAlt(y, 0, pool[p]->getNameAndAlignment().name, gamelog);
		addstrAlt(OFFERS_TO_LET, gamelog);
		addstrAlt(r.recruit->getNameAndAlignment().name, gamelog);
		addstrAlt(JOIN_THE_LIBERAL_CRIME_SQUAD, gamelog);
		gamelog.newline();
		pressAnyKey();
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		moveAlt(y += 2, 0);
		addstrAlt(r.recruit->getNameAndAlignment().name, gamelog);
		addstrAlt(ACCEPTS_AND_IS_EAGER, gamelog);
		gamelog.nextMessage();
		liberalize(*r.recruit, false);
		pressAnyKey();
		eraseAlt();
		sleeperize_prompt(*r.recruit, *pool[p], 6);
		r.recruit->hireid = pool[p]->id;
		pool[p]->train(SKILL_PERSUASION, 25);
		addCreature(r.recruit);
		r.recruit = NULL;
		stat_recruits++;
		return RETURN_ONE;
	}
	if (c == 'b' || (c == 'a' && ledger.get_funds() >= 50))
	{
		if (c == 'a')
			ledger.subtract_funds(50, EXPENSE_RECRUITMENT);
		pool[p]->train(SKILL_PERSUASION,
			max(12 - pool[p]->get_skill(SKILL_PERSUASION), 5));
		pool[p]->train(SKILL_SCIENCE,
			max(r.recruit->get_skill(SKILL_SCIENCE) - pool[p]->get_skill(SKILL_SCIENCE), 0));
		pool[p]->train(SKILL_RELIGION,
			max(r.recruit->get_skill(SKILL_RELIGION) - pool[p]->get_skill(SKILL_RELIGION), 0));
		pool[p]->train(SKILL_LAW,
			max(r.recruit->get_skill(SKILL_LAW) - pool[p]->get_skill(SKILL_LAW), 0));
		pool[p]->train(SKILL_BUSINESS,
			max(r.recruit->get_skill(SKILL_BUSINESS) - pool[p]->get_skill(SKILL_BUSINESS), 0));
		int lib_persuasiveness = pool[p]->get_skill(SKILL_BUSINESS) +
			pool[p]->get_skill(SKILL_SCIENCE) +
			pool[p]->get_skill(SKILL_RELIGION) +
			pool[p]->get_skill(SKILL_LAW) +
			pool[p]->get_attribute(ATTRIBUTE_INTELLIGENCE, true);
		int recruit_reluctance = 5 +
			r.recruit->get_skill(SKILL_BUSINESS) +
			r.recruit->get_skill(SKILL_SCIENCE) +
			r.recruit->get_skill(SKILL_RELIGION) +
			r.recruit->get_skill(SKILL_LAW) +
			r.recruit->get_attribute(ATTRIBUTE_WISDOM, true) +
			r.recruit->get_attribute(ATTRIBUTE_INTELLIGENCE, true);
		if (lib_persuasiveness > recruit_reluctance) recruit_reluctance = 0;
		else recruit_reluctance -= lib_persuasiveness;
		int difficulty = recruit_reluctance;
		char str[75];
		strcpy(str, "");
		if (c == 'a')
		{
			difficulty -= 5;
			mvaddstrAlt(y++, 0, pool[p]->getNameAndAlignment().name, gamelog);
			addstrAlt(SHARES_SPACE, gamelog);
			getissueeventstring(str);
			addstrAlt(str, gamelog);
			addstrAlt(singleDot, gamelog);
			gamelog.newline();
			pressAnyKey();
		}
		else
		{
			mvaddstrAlt(y++, 0, pool[p]->getNameAndAlignment().name, gamelog);
			addstrAlt(EXPLAINS_SPACE, gamelog);
			addstrAlt(pool[p]->hisher(), gamelog);
			addstrAlt(VIEWS_ON, gamelog);
			addstrAlt(getview(LCSrandom(VIEWNUM - 3), true), gamelog);
			addstrAlt(singleDot, gamelog);
			gamelog.newline();
			pressAnyKey();
		}
		// Liberals with juice increase difficulty as if their Wisdom were increased by said juice
		if (r.recruit->juice >= 10)
		{
			if (r.recruit->juice < 50) //Activist
				difficulty += 1;
			else if (r.recruit->juice < 100) //Socialist Threat
				difficulty += static_cast<int>(2 + 0.1*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
			else if (r.recruit->juice < 200) //Revolutionary
				difficulty += static_cast<int>(3 + 0.2*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
			else if (r.recruit->juice < 500) //Urban Commando
				difficulty += static_cast<int>(4 + 0.3*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
			else if (r.recruit->juice < 1000) //Liberal Guardian
				difficulty += static_cast<int>(5 + 0.4*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
			else //Elite Liberal
				difficulty += static_cast<int>(6 + 0.5*r.recruit->get_attribute(ATTRIBUTE_WISDOM, false));
		}
		if (difficulty > 18) difficulty = 18; // difficulty above 18 is impossible, we don't want that
		if (pool[p]->skill_check(SKILL_PERSUASION, difficulty))
		{
			set_color_easy(CYAN_ON_BLACK_BRIGHT);
			//if (r.level < 127) r.level++;
			if (r.eagerness1 < 127) r.eagerness1++;
			mvaddstrAlt(y++, 0, r.recruit->getNameAndAlignment().name, gamelog);
			addstrAlt(FOUND_SPACE, gamelog);
			addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
			addstrAlt(S_VIEWS_INSIGHTFUL, gamelog);
			gamelog.newline();
			mvaddstrAlt(y++, 0, THEYLL_MEET_AGAIN, gamelog);
			gamelog.nextMessage();
		}
		else if (pool[p]->skill_check(SKILL_PERSUASION, difficulty)) // Second chance to not fail horribly
		{
			//if (r.level < 127) r.level++;
			if (r.eagerness1 > -128) r.eagerness1--;
			mvaddstrAlt(y++, 0, r.recruit->getNameAndAlignment().name, gamelog);
			addstrAlt(IS_SKEPTICAL_ABOUT, gamelog);
			addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
			addstrAlt(S_ARGUMENTS, gamelog);
			gamelog.newline();
			mvaddstrAlt(y++, 0, THEYLL_MEET_AGAIN_TOMORROW, gamelog);
			gamelog.nextMessage();
		}
		else
		{
			set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
			moveAlt(y++, 0);
			if (r.recruit->talkreceptive() && r.recruit->align == ALIGN_LIBERAL)
			{
				addstrAlt(r.recruit->getNameAndAlignment().name, gamelog);
				addstrAlt(ISNT_CONVINCED, gamelog);
				addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(REALLY_UNDERSTANDS_PROBLEM, gamelog);
				gamelog.newline();
				mvaddstrAlt(y++, 0, CONST_X_MAYBE_, gamelog);
				addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(NEEDS_MORE_EXPERIENCE, gamelog);
				gamelog.nextMessage();
			}
			else
			{
				addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(COMESOFF_AS_INSANE, gamelog);
				gamelog.newline();
				mvaddstrAlt(y++, 0, THIS_WHOLE_THING_WAS_A_MISTAKE, gamelog);
				gamelog.nextMessage();
			}
			pressAnyKey();
			return RETURN_ONE;
		}
		pressAnyKey();
		return RETURN_ZERO;
	}
	if (c == 'd') return RETURN_ONE;
	return REPEAT;
}
void printrecruitmeeting(Deprecatedrecruitst &r, const int p) {

	addstrAlt(MEETING_WITH_SPACE, gamelog);
	addstrAlt(r.recruit->getNameAndAlignment().name, gamelog);
	addstrAlt(COMMA_SPACE, gamelog);
	addstrAlt(r.recruit->get_type_name(), gamelog);
	addstrAlt(COMMA_SPACE, gamelog);
	addstrAlt(LocationsPool::getInstance().getLocationName(r.recruit->location), gamelog);
	gamelog.newline();
	set_color_easy(WHITE_ON_BLACK);
	printfunds();
	printcreatureinfo(r.recruit);
	makedelimiter();
	mvaddstrAlt(10, 0, r.recruit->getNameAndAlignment().name);
	switch (r.eagerness())
	{
	case 1: addstrAlt(WILL_TAKE_A_LOT_OF_PERSUADING); break;
	case 2: addstrAlt(IS_INTERESTED_IN_LEARNING_MORE); break;
	case 3: addstrAlt(FEELS_SOMETHING_MUST_BE_DONE); break;
	default: if (r.eagerness() >= 4) addstrAlt(IS_READY_TO_FIGHT);
			 else addstrAlt(KIND_OF_REGRETS_AGREEING); break;
	}
	mvaddstrAlt(11, 0, HOW_SHOULD_SPACE);
	addstrAlt(pool[p]->getNameAndAlignment().name);
	addstrAlt(APPROACH_THE_SITUATION);
	moveAlt(13, 0);
	if (ledger.get_funds() < 50) set_color_easy(BLACK_ON_BLACK_BRIGHT);
	addstrAlt(A_SPEND_FIFTY_DOLLARS);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(14, 0, B_CASUALLY_CHAT);
	moveAlt(15, 0);
	if (subordinatesleft(*pool[p]) && r.eagerness() >= 4)
	{
		addstrAlt(C_OFFER_TO_LET);
		addstrAlt(r.recruit->getNameAndAlignment().name);
		addstrAlt(JOIN_THE_LCS);
	}
	else if (!subordinatesleft(*pool[p]))
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		addstrAlt(CONST_X_C_DASH);
		addstrAlt(pool[p]->getNameAndAlignment().name);
		addstrAlt(NEEDS_MORE_JUICE_TO_RECRUIT);
		set_color_easy(WHITE_ON_BLACK);
	}
	else
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		addstrAlt(CONST_X_C_DASH);
		addstrAlt(r.recruit->getNameAndAlignment().name);
		addstrAlt(ISNT_READY_TO_JOIN);
		set_color_easy(WHITE_ON_BLACK);
	}
	mvaddstrAlt(16, 0, D_BREAK_OFF_MEETINGS);
}
/* daily - recruit - recruit meeting */
char completerecruitmeeting(Deprecatedrecruitst &r, const int p)
{
	music.play(MUSIC_RECRUITING);
	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	moveAlt(0, 0);
	if (pool[p]->meetings++ > 5 && LCSrandom(pool[p]->meetings - 5))
	{
		addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
		addstrAlt(ACCIDENTALLY_MISSED_THE_MEETING_WITH, gamelog);
		addstrAlt(r.recruit->getNameAndAlignment().name, gamelog);
		mvaddstrAlt(1, 0, DUE_TO_MULTIPLE_BOOKING_OR_RECRUITMENT, gamelog);
		gamelog.newline();
		mvaddstrAlt(3, 0, GET_IT_TOGETHER_COMMA, gamelog);
		addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
		addstrAlt(EXCLAMATION_POINT, gamelog);
		gamelog.nextMessage();
		pressAnyKey();
		return 1;
	}
	printrecruitmeeting(r, p);
	int y = 18;
	while (true)
	{
		LOOP_CONTINUATION next_loop = increment_completerecruitmeeting(p, r, y);
		if (next_loop != REPEAT) {
			if (next_loop == RETURN_ONE) {
				return 1;
			}
			else if (next_loop == RETURN_ZERO) {
				return 0;
			}
		}
	}
}
void findAllTendersToThisHostage(DeprecatedCreature* cr, vector<DeprecatedCreature *>& temppool) {
	//Find all tenders who are set to this hostage
	for (int p = 0; p < len(pool); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive) continue;
		if (pool[p]->activity_type() == ACTIVITY_HOSTAGETENDING && pool[p]->activity_arg() == cr->id)
		{
			//If they're in the same location as the hostage,
			//include them in the InterrogationST
			if (pool[p]->location == cr->location&&pool[p]->location != -1)
				temppool.push_back(pool[p]);
			//If they're someplace else, take them off the job
			else pool[p]->set_activity_type(ACTIVITY_NONE);
		}
	}
}
void hostageEscapes(DeprecatedCreature* cr, char clearformess) {
	for (int p = 0; p < len(pool); p++)
	{
		if (pool[p] == cr)
		{
			if (clearformess) eraseAlt();
			else makedelimiter();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(8, 1, cr->getNameAndAlignment().name, gamelog);
			addstrAlt(HAS_ESCAPED, gamelog);
			gamelog.nextMessage();
			LocationsPool::getInstance().setTimeUntilSiege(cr->location, 3);
			pressAnyKey();
			//clear activities for tenders
			for (int i = 0; i < len(pool); i++)
			{
				if (!pool[i]->getNameAndAlignment().alive) continue;
				if (pool[i]->activity_type() == ACTIVITY_HOSTAGETENDING && pool[i]->activity_arg() == cr->id)
					pool[i]->set_activity_type(ACTIVITY_NONE);
			}
			delete_and_remove(pool, p);
			break;
		}
	}
}
void setAllCreatureActivities(Activity cr, vector<DeprecatedCreature *>& temppool) {
	for (int p = 0; p < len(temppool); p++) {
		temppool[p]->set_activity_type(cr);
	}
}
DeprecatedCreature::~DeprecatedCreature()
{
	delete weapon;
	delete armor;
	delete_and_clear(clips);
	delete_and_clear(extra_throwing_weapons);
	if (prisoner)
	{
		for (int p = 0; p < len(pool); p++)
			if (prisoner == pool[p]) { delete_and_remove(pool, p); break; }
	}
	// Clean up hostage situation
	stop_hauling_me();
}
void DeprecatedCreature::stop_hauling_me()
{
	for (int p = 0; p < len(pool); p++) if (pool[p]->prisoner == this) pool[p]->prisoner = NULL;
}
bool DeprecatedCreature::enemy() const
{
	if (align == ALIGN_CONSERVATIVE)
		return true;
	else if (type == CREATURE_COP && align == ALIGN_MODERATE)
	{
		for (int i = 0; i < len(pool); i++)
			if (pool[i] == this)
				return false;
		return true;
	}
	else return false;
}
vector<DeprecatedCreature *> selectOnlySleepersThatCanWork() {
	vector<DeprecatedCreature *> temppool;
	// Comb the pool of Liberals for sleeper agents
	for (int p = 0; p < len(pool); p++)
	{
		// Select only sleepers that can work
		if (pool[p]->getNameAndAlignment().alive == true &&
			pool[p]->flag & CREATUREFLAG_SLEEPER&&
			pool[p]->align == ALIGN_LIBERAL &&
			pool[p]->hiding == false &&
			pool[p]->clinic == false &&
			pool[p]->dating == false)
		{
			temppool.push_back(pool[p]);
		}
	}
	return temppool;
}
void determineMedicalSupportAtEachLocation(bool clearformess) {
	// Healing - determine medical support at each location
	int *healing = new int[LocationsPool::getInstance().lenpool()];
	int *healing2 = new int[LocationsPool::getInstance().lenpool()];
	for (int p = 0; p < LocationsPool::getInstance().lenpool(); p++)
	{
		// Clinic is equal to a skill 6 liberal
		if (LocationsPool::getInstance().getLocationType(p) == SITE_HOSPITAL_CLINIC) healing[p] = 6;
		// Hospital is equal to a skill 12 liberal
		else if (LocationsPool::getInstance().getLocationType(p) == SITE_HOSPITAL_UNIVERSITY) healing[p] = 12;
		else healing[p] = 0;
		healing2[p] = 0;
	}
	if (!disbanding) for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive) continue;
		if (pool[p]->hiding) continue;
		if (pool[p]->flag&CREATUREFLAG_SLEEPER) continue;
		// People will help heal even if they aren't specifically assigned to do so
		// Having a specific healing activity helps bookkeeping for the player, though
		// Only the highest medical skill is considered
		if (pool[p]->activity_type() == ACTIVITY_HEAL || pool[p]->activity_type() == ACTIVITY_NONE)
			if (pool[p]->location > -1 &&
				healing[pool[p]->location] < pool[p]->get_skill(SKILL_FIRSTAID))
			{
				healing[pool[p]->location] = pool[p]->get_skill(SKILL_FIRSTAID);
				pool[p]->set_activity_type(ACTIVITY_HEAL);
			}
	}
	// Don't let starving locations heal
	for (int p = 0; p < LocationsPool::getInstance().lenpool(); p++)
		if (LocationsPool::getInstance().getLocationType(p) != SITE_HOSPITAL_CLINIC && LocationsPool::getInstance().getLocationType(p) != SITE_HOSPITAL_UNIVERSITY)
			if (!fooddaysleft(p))
				if (LocationsPool::getInstance().isThereASiegeHere(p))
					healing[p] = 0;
	//HEAL NON-CLINIC PEOPLE AND TRAIN
	if (!disbanding) for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!(pool[p]->getNameAndAlignment().alive)) continue;
		if (clinictime(*pool[p]))
		{
			// For people in LCS home treatment
			if (pool[p]->clinic == false)
			{
				int damage = 0; // Amount health degrades
								//int release=1;
				int transfer = 0;
				// Give experience to caretakers
				if (pool[p]->location > -1) healing2[pool[p]->location] += 100 - pool[p]->blood;
				// Cap blood at 100-injurylevel*20
				if (pool[p]->blood < 100 - (clinictime(*pool[p]) - 1) * 20)
				{
					// Add health
					if (pool[p]->location > -1)pool[p]->blood += 1 + healing[pool[p]->location] / 3;
					if (pool[p]->blood > 100 - (clinictime(*pool[p]) - 1) * 20)
						pool[p]->blood = 100 - (clinictime(*pool[p]) - 1) * 20;
					if (pool[p]->blood > 100)
						pool[p]->blood = 100;
				}
				if (pool[p]->getNameAndAlignment().alive&&pool[p]->blood < 0)
				{
					if (clearformess) eraseAlt();
					else makedelimiter();
					pool[p]->die();
					mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
					addstrAlt(HAS_DIED_OF_INJURIES, gamelog);
					gamelog.nextMessage();
				}
				for (int w = 0; w < BODYPARTNUM; w++)
				{
					// Limbs blown off
					if (pool[p]->wound[w] & WOUND_NASTYOFF)
					{
						// Chance to stabilize/amputate wound
						// Difficulty 12 (Will die if not treated)
						if (pool[p]->location > -1 && healing[pool[p]->location] + LCSrandom(10) > 12)
							pool[p]->wound[w] = WOUND_CLEANOFF;
						// Else take bleed damage (4)
						else
						{
							damage += 4;
							//release=0;
							if (pool[p]->location > -1 && healing[pool[p]->location] + 9 <= 12)
								transfer = 1;
						}
					}
					// Bleeding wounds
					else if (pool[p]->wound[w] & WOUND_BLEEDING)
					{
						// Chance to stabilize wound
						// Difficulty 8 (1 in 10 of happening naturally)
						if (pool[p]->location > -1 && healing[pool[p]->location] + LCSrandom(10) > 8)
							// Toggle bleeding off
							pool[p]->wound[w] &= ~WOUND_BLEEDING;
						// Else take bleed damage (1)
						else
						{
							damage += 1;
							//release=0;
						}
					}
					// Non-bleeding wounds
					else
					{  // Erase wound if almost fully healed, but preserve loss of limbs.
						if (pool[p]->blood >= 95)
							pool[p]->wound[w] &= WOUND_CLEANOFF;
					}
				}
				// Critical hit wounds
				for (int i = SPECIALWOUND_RIGHTLUNG; i < SPECIALWOUNDNUM; ++i)
				{
					int healdiff = 14, permdamage = 0, bleed = 0, healed = 0;
					// Specific treatment information on wounds
					switch (i)
					{
					case SPECIALWOUND_HEART:
						healdiff = 16;
						bleed = 8;
					case SPECIALWOUND_RIGHTLUNG:
					case SPECIALWOUND_LEFTLUNG:
						permdamage = 1;
					case SPECIALWOUND_LIVER:
					case SPECIALWOUND_STOMACH:
					case SPECIALWOUND_RIGHTKIDNEY:
					case SPECIALWOUND_LEFTKIDNEY:
					case SPECIALWOUND_SPLEEN:
						healed = 1;
						bleed++;
						break;
					case SPECIALWOUND_RIBS:
						healed = RIBNUM;
						break;
					case SPECIALWOUND_NECK:
					case SPECIALWOUND_UPPERSPINE:
					case SPECIALWOUND_LOWERSPINE:
						healed = 2;
						break;
					}
					// If wounded
					if (pool[p]->special[i] != healed && (i == SPECIALWOUND_RIBS || pool[p]->special[i] != 1))
					{
						// Chance to stabilize wound
						if (pool[p]->location > -1 && healing[pool[p]->location] + LCSrandom(10) > healdiff)
						{
							// Remove wound
							pool[p]->special[i] = healed;
							if (permdamage)
							{
								// May take permanent health damage depending on
								// quality of care
								if (LCSrandom(20) > healing[pool[p]->location])
								{
									pool[p]->adjust_attribute(ATTRIBUTE_HEALTH, -1);
									if (pool[p]->get_attribute(ATTRIBUTE_HEALTH, false) <= 0)
									{
										pool[p]->set_attribute(ATTRIBUTE_HEALTH, 1);
									}
								}
							}
						}
						// Else take bleed damage
						else
						{
							damage += bleed;
							//release=0;
							if (healing[pool[p]->location] + 9 <= healdiff)
								transfer = 1;
						}
					}
				}
				// Apply damage
				pool[p]->blood -= damage;
				if (transfer&&pool[p]->location > -1 &&
					pool[p]->getNameAndAlignment().alive == 1 &&
					pool[p]->align == 1 &&
					LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,pool[p]->location) != RENTING_NOCONTROL &&
					LocationsPool::getInstance().getLocationType(pool[p]->location) != SITE_HOSPITAL_UNIVERSITY)
				{
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
					addstrAlt(S_INJURIES_REQUIRE_PROFESSIONAL, gamelog);
					gamelog.nextMessage();
					pool[p]->set_activity_type(ACTIVITY_CLINIC);
					pressAnyKey();
				}
			}
		}
	}
	//Give experience to medics
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		//If present, qualified to heal, and doing so
		if (pool[p]->location >= 0 && pool[p]->activity_type() == ACTIVITY_HEAL)
		{
			//Clear activity if their location doesn't have healing work to do
			if (healing2[pool[p]->location] == 0)
				pool[p]->set_activity_type(ACTIVITY_NONE);
			//Give experience based on work done and current skill
			else
				pool[p]->train(SKILL_FIRSTAID, max(0, healing2[pool[p]->location] / 5 - pool[p]->get_skill(SKILL_FIRSTAID) * 2));
		}
	}
	delete[] healing;
	delete[] healing2;
}
/* promote a subordinate to maintain chain of command when boss is lost */
bool promotesubordinates(DeprecatedCreature &cr, char &clearformess)
{
	int newboss = -1;
	int bigboss = -2;
	if (cr.hireid == -1)bigboss = -1;//Special: Founder
	int maxjuice = 0; //Need more than 0 juice to get promoted
	int subordinates = 0;
	//Need REVOLUTIONARY (100+) juice to take over founder role
	if (cr.hireid == -1)maxjuice = 99;
	//Identify big boss and top subordinate
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->id == cr.id)continue;
		if (pool[p]->id == cr.hireid)bigboss = p;
		if (pool[p]->hireid == cr.id && pool[p]->getNameAndAlignment().alive && pool[p]->align == 1)
		{
			subordinates++;
			//Brainwashed people inelligible for promotion to founder
			if (bigboss == -1 && pool[p]->flag & CREATUREFLAG_BRAINWASHED)continue;
			//Loveslaves inelligible for promotion to anything unless juice is high
			//in which case they get over it and continue to serve as a normal member
			if (pool[p]->flag & CREATUREFLAG_LOVESLAVE)
			{
				if (pool[p]->juice < 100)continue;
				else pool[p]->flag &= ~CREATUREFLAG_LOVESLAVE;
			}
			// Highest juice liberal not a sleeper or subject to a life sentence gets promoted
			if (pool[p]->juice > maxjuice &&
				!(pool[p]->flag & CREATUREFLAG_SLEEPER) &&
				(pool[p]->location == -1 ||
				(LocationsPool::getInstance().getLocationType(pool[p]->location) != SITE_GOVERNMENT_PRISON || pool[p]->getCreatureJustice().sentence >= 0)))
			{
				maxjuice = pool[p]->juice;
				newboss = p;
			}
		}
	}
	//No subordinates or none with sufficient juice to carry on
	if (subordinates == 0 || newboss == -1)
	{
		if (cr.hireid != -1)return 0;
		if (subordinates > 0) // Disintegration of the LCS
		{
			if (clearformess) eraseAlt();
			else makedelimiter();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(8, 1, cr.getNameAndAlignment().name, gamelog);
			addstrAlt(HAS_DIED, gamelog);
			gamelog.newline();
			pressAnyKey();
			mvaddstrAlt(10, 1, THERE_ARE_NONE_WHO_CAN_LEAD, gamelog);
			gamelog.nextMessage();
			pressAnyKey();
		}
		return 0;
	}
	//Chain of command totally destroyed if dead person's boss also dead
	if (bigboss == -2 || (cr.hireid != -1 && bigboss != -1 && !pool[bigboss]->getNameAndAlignment().alive))return 0;
	//Promote the new boss
	pool[newboss]->hireid = cr.hireid;
	//Order secondary subordinates to follow the new boss
	if (subordinates > 1)
	{
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (pool[p]->hireid == cr.id && // recruited by old boss that died
				p != newboss &&             // not the new boss
				!(pool[p]->flag & CREATUREFLAG_LOVESLAVE)) // is not a love slave
			{
				pool[p]->hireid = pool[newboss]->id; // promote
			}
		}
	}
	if (clearformess) eraseAlt();
	else makedelimiter();
	if (bigboss != -1) // Normal promotion
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 1, pool[bigboss]->getNameAndAlignment().name, gamelog);
		addstrAlt(HAS_PROMOTED, gamelog);
		addstrAlt(pool[newboss]->getNameAndAlignment().name, gamelog);
		mvaddstrAlt(9, 1, DUE_TO_THE_DEATH_OF, gamelog);
		addstrAlt(cr.getNameAndAlignment().name, gamelog);
		addstrAlt(singleDot, gamelog);
		if (subordinates > 1)
		{
			gamelog.newline();
			mvaddstrAlt(11, 1, pool[newboss]->getNameAndAlignment().name, gamelog);
			addstrAlt(WILL_TAKE_OVER_FOR, gamelog);
			addstrAlt(cr.getNameAndAlignment().name, gamelog);
			addstrAlt(IN_THE_COMMAND_CHAIN, gamelog);
		}
		gamelog.nextMessage();
		pressAnyKey();
	}
	else // Founder level promotion
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 1, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(HAS_DIED, gamelog);
		gamelog.newline();
		pressAnyKey();
		mvaddstrAlt(10, 1, pool[newboss]->getNameAndAlignment().name, gamelog);
		addstrAlt(IS_THE_NEW_LEADER_OF_LCS, gamelog);
		gamelog.nextMessage();
		pressAnyKey();
		cr.hireid = -2; // Make dead founder not founder.
	}
	return 1;
}
/* squad members with no chain of command lose contact */
void dispersalcheck(char &clearformess)
{

	//NUKE DISPERSED SQUAD MEMBERS WHOSE MASTERS ARE NOT AVAILABLE
	if (CreaturePool::getInstance().lenpool())
	{
		// *JDS* I'm documenting this algorithm carefully because it
		// took me awhile to figure out what exactly was going on here.
		//
		// dispersal_status tracks whether each person has a secure chain of command.
		//
		// if dispersal_status == NOCONTACT, no confirmation of contact has been made
		// if dispersal_status == BOSSSAFE, confirmation that THEY are safe is given,
		//    but it is still needed to check whether their subordinates
		//    can reach them.
		// if dispersal_status == SAFE, confirmation has been made that this squad
		//    member is safe, and their immediate subordinates have also
		//    checked.
		//
		// The way the algorithm works, everyone starts at dispersal_status = NOCONTACT.
		// Then we start at the top of the chain of command and walk
		// down it slowly, marking people BOSSSAFE and then SAFE as we sweep
		// down the chain. If someone is dead or in an unreachable state,
		// they block progression down the chain to their subordinates,
		// preventing everyone who requires contact with that person
		// from being marked safe. After everyone reachable has been
		// reached and marked safe, all remaining squad members are nuked.
		vector<int> dispersal_status;
		dispersal_status.resize(CreaturePool::getInstance().lenpool());
		bool promotion;
		do
		{
			promotion = 0;
			for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
			{
				// Default: members are marked dispersal_status = NOCONTACT
				//(no contact verified)
				dispersal_status[p] = DISPERSAL_NOCONTACT;
				// If member has no boss (founder level), mark
				// them dispersal_status = BOSSSAFE, using them as a starting point
				// at the top of the chain.
				if (pool[p]->hireid == -1)
				{
					if (!disbanding)
					{
						dispersal_status[p] = DISPERSAL_BOSSSAFE;
						if (pool[p]->hiding == -1)
							pool[p]->hiding = LCSrandom(10) + 5;
					}
					else dispersal_status[p] = DISPERSAL_BOSSINHIDING;
				}
				// If they're dead, mark them dispersal_status = SAFE, so they
				// don't ever have their subordinates checked
				// and aren't lost themselves (they're a corpse,
				// corpses don't lose contact)
				if (!pool[p]->getNameAndAlignment().alive && !disbanding)
				{
					dispersal_status[p] = DISPERSAL_SAFE;
					//Attempt to promote their subordinates
					if (promotesubordinates(*pool[p], clearformess)) promotion = 1;
					if (pool[p]->location == -1 || LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,pool[p]->location) == RENTING_NOCONTROL)
						delete_and_remove(pool, p--);
				}
			}
		} while (promotion);
		char changed;
		do // while(changed)
		{
			changed = 0;
			char inprison;
			// Go through the entire pool to locate people at dispersal_status = BOSSSAFE,
			// so we can verify that their subordinates can reach them.
			for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
			{
				if (!pool[p]->getNameAndAlignment().alive) continue;
				if (pool[p]->location != -1 &&
					LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_GOVERNMENT_PRISON &&
					!(pool[p]->flag & CREATUREFLAG_SLEEPER))
				{
					inprison = 1;
				}
				else inprison = 0;
				// If your boss is in hiding
				if (dispersal_status[p] == DISPERSAL_BOSSINHIDING)
				{
					dispersal_status[p] = DISPERSAL_HIDING;
					for (int p2 = CreaturePool::getInstance().lenpool() - 1; p2 >= 0; p2--)
					{
						if (pool[p2]->hireid == pool[p]->id && pool[p2]->getNameAndAlignment().alive)
						{
							dispersal_status[p2] = DISPERSAL_BOSSINHIDING; // Mark them as unreachable
							changed = 1; // Need another iteration
						}
					}
				}
				// If in prison or unreachable due to a member of the command structure
				// above being in prison
				else if ((dispersal_status[p] == DISPERSAL_BOSSSAFE && inprison) || dispersal_status[p] == DISPERSAL_BOSSINPRISON)
				{
					int dispersalval = DISPERSAL_SAFE;
					if (pool[p]->flag&CREATUREFLAG_LOVESLAVE)
					{
						if ((dispersal_status[p] == DISPERSAL_BOSSINPRISON && !inprison) ||
							(dispersal_status[p] == DISPERSAL_BOSSSAFE && inprison))
						{
							pool[p]->juice--; // Love slaves bleed juice when not in prison with their lover
							if (pool[p]->juice < -50) dispersalval = DISPERSAL_ABANDONLCS;
						}
					}
					dispersal_status[p] = dispersalval; // Guaranteed contactable in prison
														// Find all subordinates
					for (int p2 = CreaturePool::getInstance().lenpool() - 1; p2 >= 0; p2--)
					{
						if (pool[p2]->hireid == pool[p]->id && pool[p2]->getNameAndAlignment().alive)
						{
							if (inprison) dispersal_status[p2] = DISPERSAL_BOSSINPRISON;
							else dispersal_status[p2] = DISPERSAL_BOSSSAFE;
							changed = 1; // Need another iteration
						}
					}
				}
				// Otherwise, if they're reachable
				else if (dispersal_status[p] == DISPERSAL_BOSSSAFE && !inprison)
				{
					// Start looking through the pool again.
					for (int p2 = CreaturePool::getInstance().lenpool() - 1; p2 >= 0; p2--)
					{
						// Locate each of this person's subordinates.
						if (pool[p2]->hireid == pool[p]->id)
						{
							// Protect them from being dispersed -- their boss is
							// safe. Their own subordinates will then be considered
							// in the next loop iteration.
							dispersal_status[p2] = DISPERSAL_BOSSSAFE;
							// If they're hiding indefinitely and their boss isn't
							// hiding at all, then have them discreetly return in a
							// couple of weeks
							if (pool[p2]->hiding == -1 && !pool[p]->hiding)
								pool[p2]->hiding = LCSrandom(10) + 3;
							changed = 1; // Take note that another iteration is needed.
						}
					}
					// Now that we've dealt with this person's subordinates, mark
					// them so that we don't look at them again in this loop.
					dispersal_status[p] = DISPERSAL_SAFE;
				}
			}
		} while (changed); // If another iteration is needed, continue the loop.
						   // After checking through the entire command structure, proceed
						   // to nuke all squad members who are unable to make contact with
						   // the LCS.
		for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
		{
			if (dispersal_status[p] == DISPERSAL_NOCONTACT || dispersal_status[p] == DISPERSAL_HIDING || dispersal_status[p] == DISPERSAL_ABANDONLCS)
			{
				if (clearformess) eraseAlt();
				else makedelimiter();
				if (!disbanding)
				{
					if (!pool[p]->hiding&&dispersal_status[p] == DISPERSAL_HIDING)
					{
						set_color_easy(WHITE_ON_BLACK_BRIGHT);
						mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
						addstrAlt(HAS_LOST_TOUCH_WITH_LCS, gamelog);
						gamelog.nextMessage();
						pressAnyKey();
						set_color_easy(GREEN_ON_BLACK_BRIGHT);
						mvaddstrAlt(9, 1, THE_LIBERAL_HAS_GONE_INTO_HIDING, gamelog);
						gamelog.nextMessage();
						pressAnyKey();
					}
					else if (dispersal_status[p] == DISPERSAL_ABANDONLCS)
					{
						set_color_easy(WHITE_ON_BLACK_BRIGHT);
						mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
						addstrAlt(HAS_ABANDONED_THE_LCS, gamelog);
						gamelog.nextMessage();
						pressAnyKey();
					}
					else if (dispersal_status[p] == DISPERSAL_NOCONTACT)
					{
						set_color_easy(WHITE_ON_BLACK_BRIGHT);
						mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
						addstrAlt(HAS_LOST_TOUCH_WITH_LCS, gamelog);
						gamelog.nextMessage();
						pressAnyKey();
					}
				}
				removesquadinfo(*pool[p]);
				if (dispersal_status[p] == DISPERSAL_NOCONTACT || dispersal_status[p] == DISPERSAL_ABANDONLCS)
					delete_and_remove(pool, p);
				else
				{
					pool[p]->location = -1;
					if (!(pool[p]->flag & CREATUREFLAG_SLEEPER)) //Sleepers end up in shelter otherwise.
						pool[p]->base = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, pool[p]->location);
					pool[p]->set_activity_type(ACTIVITY_NONE);
					pool[p]->hiding = -1; // Hide indefinitely
				}
			}
		}
	}
	//MUST DO AN END OF GAME CHECK HERE BECAUSE OF DISPERSAL
	endcheck(END_DISPERSED);
	cleangonesquads();
}
vector<DeprecatedCreature *> activatable_liberals()
{
	vector<DeprecatedCreature *> temppool;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->is_active_liberal())
		{
			if (pool[p]->squadid != -1)
			{
				int sq = getsquad(pool[p]->squadid);
				if (sq != -1) if (squad[sq]->activity.type != ACTIVITY_NONE) continue;
			}
			temppool.push_back(pool[p]);
		}
	}
	return temppool;
}
vector<DeprecatedCreature *> getLiberalsSharingLocation(DeprecatedCreature * cr) {
	vector<DeprecatedCreature *> temppool;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++) {
		if (pool[p] == cr) continue;
		if (pool[p]->is_active_liberal() && (pool[p]->location == cr->location))
		{
			temppool.push_back(pool[p]);
		}
	}
	return temppool;
}
vector<DeprecatedCreature *> getHostagesSharingLocation(DeprecatedCreature *cr) {
	vector<DeprecatedCreature *> temppool;
	for (int p = 0; p < len(pool); p++)
	{
		if (pool[p]->align != 1 &&
			pool[p]->getNameAndAlignment().alive&&
			pool[p]->location == cr->location)
		{
			temppool.push_back(pool[p]);
		}
	}
	return temppool;
}
int countHostagesSharingLocation(DeprecatedCreature *cr) {
	int hostagecount = 0;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->getNameAndAlignment().alive&&pool[p]->align != 1 && pool[p]->location == cr->location) hostagecount++;
	}
	return hostagecount;
}
int countDeadSharingLocation(DeprecatedCreature *cr) {
	int havedead = 0;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive) havedead = 1;
	}
	return havedead;
}
string getSleeperBouncerName(short cursite) {
	string output = "";
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->base == cursite && pool[p]->type == CREATURE_BOUNCER)
		{
			output = pool[p]->getNameAndAlignment().name;
			break;
		}
	}
	return output;
}
string getSleeperSecurityName(short cursite, int type) {
	string name = "";
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->base == cursite)
		{
			if (pool[p]->type == type)
			{
				name = pool[p]->getNameAndAlignment().name;
				break;
			}
		}
	}
	return name;
}
char doWeHaveASleeperHere(short cursite) {
	char autoadmit = 0;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->base == cursite)
		{
			autoadmit = 1;
		}
	}
	return autoadmit;
}
string getSleeperBankerName(short cursite) {
	string output = "";
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->type == CREATURE_BANK_MANAGER &&
			pool[p]->flag & CREATUREFLAG_SLEEPER &&
			pool[p]->base == cursite)
		{
			output = pool[p]->getNameAndAlignment().name;
			break;
		}
	}
	return output;
}
string haveSleeperBankerCrackSafe(short cursite, int base) {
	string output = "";
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->base == cursite && pool[p]->type == CREATURE_BANK_MANAGER)
		{
			output = pool[p]->getNameAndAlignment().name;
			pool[p]->location = pool[p]->base = base;
			pool[p]->flag &= ~CREATUREFLAG_SLEEPER;
			pool[p]->set_activity_type(ACTIVITY_NONE);
			pool[p]->criminalize_me(LAWFLAG_BANKROBBERY, false);
			break;
		}
	}
	return output;
}
void monthlyRunTheSystem(char &clearformess) {
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (!pool[p]->getNameAndAlignment().alive) continue;
		if (pool[p]->flag & CREATUREFLAG_SLEEPER) continue;
		if (pool[p]->location == -1) continue;
		if (LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_GOVERNMENT_POLICESTATION)
		{
			if (clearformess) eraseAlt();
			else makedelimiter();
			if (pool[p]->flag & CREATUREFLAG_MISSING)
			{
				set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, COPS_RE_POLLUTED, gamelog);
				addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(S_MIND_WITH_CONSERVATISM, gamelog);
				gamelog.nextMessage();
				pressAnyKey();
				removesquadinfo(*pool[p]);
				delete_and_remove(pool, p);
				continue;
			}
			else if (pool[p]->flag & CREATUREFLAG_ILLEGALALIEN && lawList[LAW_IMMIGRATION] != 2)
			{
				set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(HAS_BEEN_SHIPPED_OUT_TO_THE_INS, gamelog);
				if (lawList[LAW_IMMIGRATION] == -2 && lawList[LAW_DEATHPENALTY] == -2)
					addstrAlt(EXECUTION, gamelog);
				else addstrAlt(DEPORTATION, gamelog);
				gamelog.newline();
				pressAnyKey();
				removesquadinfo(*pool[p]);
				delete_and_remove(pool, p);
				continue;
			}
			else
			{
				//TRY TO GET RACKETEERING CHARGE
				int copstrength = 100;
				if (lawList[LAW_POLICEBEHAVIOR] == -2) copstrength = 200;
				if (lawList[LAW_POLICEBEHAVIOR] == -1) copstrength = 150;
				if (lawList[LAW_POLICEBEHAVIOR] == 1) copstrength = 75;
				if (lawList[LAW_POLICEBEHAVIOR] == 2) copstrength = 50;
				copstrength = (copstrength*pool[p]->heat) / 4;
				if (copstrength > 200)copstrength = 200;
				//Confession check
				if (LCSrandom(copstrength) > pool[p]->juice + pool[p]->get_attribute(ATTRIBUTE_HEART, true) * 5 -
					pool[p]->get_attribute(ATTRIBUTE_WISDOM, true) * 5 + pool[p]->get_skill(SKILL_PSYCHOLOGY) * 5
					/*+ pool[p]->get_skill(SKILL_SURVIVAL)*5*/ && pool[p]->hireid != -1)
				{
					int p2 = getpoolcreature(pool[p]->hireid);
					if (pool[p2]->getNameAndAlignment().alive && (pool[p2]->location == -1 || LocationsPool::getInstance().getLocationType(pool[p2]->location) != SITE_GOVERNMENT_PRISON))
					{  //Charge the boss with racketeering!
						criminalize(*pool[p2], LAWFLAG_RACKETEERING);
						//Rack up testimonies against the boss in court!
						pool[p2]->another_confession();
					}
					//Issue a raid on this guy's base!
					if (pool[p]->base >= 0)LocationsPool::getInstance().addHeat(pool[p]->base, 300);
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
					addstrAlt(HAS_BROKEN_AND_RATTED_YOU_OUT, gamelog);
					gamelog.newline();
					pressAnyKey();
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(9, 1, THE_TRAITOR_WILL_TESTIFY, gamelog);
					gamelog.nextMessage();
					pressAnyKey();
					removesquadinfo(*pool[p]);
					delete_and_remove(pool, p);
					continue; //no trial for this person; skip to next person

				}
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(IS_MOVED_TO_THE_COURTHOUSE, gamelog);
				gamelog.nextMessage();
				pressAnyKey();
				pool[p]->location = find_site_index_in_same_city(SITE_GOVERNMENT_COURTHOUSE, pool[p]->location);
				Armor prisoner(getarmortype(tag_ARMOR_PRISONER));
				pool[p]->give_armor(prisoner, NULL);
			}
		}
		else if (LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_GOVERNMENT_COURTHOUSE)
		{
			trial(*pool[p]); clearformess = 1;
		}
		else if (LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_GOVERNMENT_PRISON)
			if (prison(*pool[p])) clearformess = 1;
	}
}
void monthlyRunExecutions() {
	for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
	{
		if (pool[p]->location == -1) continue;
		if (LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_GOVERNMENT_PRISON && !pool[p]->getNameAndAlignment().alive)
		{
			removesquadinfo(*pool[p]);
			pool[p]->die();
			pool[p]->location = -1;
		}
	}
}
void monthlyRunHealClinicPeople(char &clearformess) {
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!(pool[p]->getNameAndAlignment().alive)) continue;
		if (pool[p]->clinic > 0)
		{
			pool[p]->clinic--;
			for (int w = 0; w < BODYPARTNUM; w++)
			{
				if ((pool[p]->wound[w] & WOUND_NASTYOFF) || (pool[p]->wound[w] & WOUND_CLEANOFF))
					pool[p]->wound[w] = (char)WOUND_CLEANOFF;
				else pool[p]->wound[w] = 0;
			}
			int healthdamage = 0;
			if (pool[p]->special[SPECIALWOUND_RIGHTLUNG] != 1)
			{
				pool[p]->special[SPECIALWOUND_RIGHTLUNG] = 1;
				if (LCSrandom(2)) healthdamage++;
			}
			if (pool[p]->special[SPECIALWOUND_LEFTLUNG] != 1)
			{
				pool[p]->special[SPECIALWOUND_LEFTLUNG] = 1;
				if (LCSrandom(2)) healthdamage++;
			}
			if (pool[p]->special[SPECIALWOUND_HEART] != 1)
			{
				pool[p]->special[SPECIALWOUND_HEART] = 1;
				if (LCSrandom(3)) healthdamage++;
			}
			pool[p]->special[SPECIALWOUND_LIVER] = 1;
			pool[p]->special[SPECIALWOUND_STOMACH] = 1;
			pool[p]->special[SPECIALWOUND_RIGHTKIDNEY] = 1;
			pool[p]->special[SPECIALWOUND_LEFTKIDNEY] = 1;
			pool[p]->special[SPECIALWOUND_SPLEEN] = 1;
			pool[p]->special[SPECIALWOUND_RIBS] = RIBNUM;
			if (!pool[p]->special[SPECIALWOUND_NECK])
				pool[p]->special[SPECIALWOUND_NECK] = 2;
			if (!pool[p]->special[SPECIALWOUND_UPPERSPINE])
				pool[p]->special[SPECIALWOUND_UPPERSPINE] = 2;
			if (!pool[p]->special[SPECIALWOUND_LOWERSPINE])
				pool[p]->special[SPECIALWOUND_LOWERSPINE] = 2;
			// Inflict permanent health damage
			pool[p]->set_attribute(ATTRIBUTE_HEALTH, pool[p]->get_attribute(ATTRIBUTE_HEALTH, 0) - healthdamage);
			if (pool[p]->get_attribute(ATTRIBUTE_HEALTH, 0) <= 0)
				pool[p]->set_attribute(ATTRIBUTE_HEALTH, 1);
			if (pool[p]->blood <= 20 && pool[p]->clinic <= 2)pool[p]->blood = 50;
			if (pool[p]->blood <= 50 && pool[p]->clinic <= 1)pool[p]->blood = 75;
			// If at clinic and in critical condition, transfer to university hospital
			if (pool[p]->clinic > 2 &&
				pool[p]->location > -1 &&
				LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_HOSPITAL_CLINIC)
			{
				int hospital = find_site_index_in_same_city(SITE_HOSPITAL_UNIVERSITY, pool[p]->location);
				if (hospital != -1)
				{
					pool[p]->location = hospital;
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
					addstrAlt(HAS_BEEN_TRANSFERRED_TO, gamelog);
					addstrAlt(LocationsPool::getInstance().getLocationName(hospital), gamelog);
					addstrAlt(singleDot, gamelog);
					gamelog.nextMessage();
					pressAnyKey();
				}
			}
			// End treatment
			if (pool[p]->clinic == 0)
			{
				pool[p]->blood = 100;
				if (clearformess) eraseAlt();
				else makedelimiter();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, pool[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(HAS_LEFT, gamelog);
				addstrAlt(LocationsPool::getInstance().getLocationName(pool[p]->location), gamelog);
				addstrAlt(singleDot, gamelog);
				gamelog.nextMessage();
				int hs = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, pool[p]->location);
				if (hs == -1) hs = 0; //TODO: Error unable to find location
				if (LocationsPool::getInstance().isThereASiegeHere(pool[p]->base) ||
					LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,pool[p]->base) == RENTING_NOCONTROL)
					pool[p]->base = hs;
				pool[p]->location = pool[p]->base;
				pressAnyKey();
			}
		}
	}
}
void havingSleepers(char &clearformess, char canseethings, int(&libpower)[VIEWNUM]) {
	for (int pl = CreaturePool::getInstance().lenpool() - 1; pl > 0; pl--) {
		if (pool[pl]->getNameAndAlignment().alive && (pool[pl]->flag & CREATUREFLAG_SLEEPER)) {
			sleepereffect(*pool[pl], clearformess, canseethings, libpower);
		}
	}
}
void giveSeductionExperienceToLoveSlaves() {
	for (int s = 0; s < CreaturePool::getInstance().lenpool(); s++)
	{
		pool[s]->train(SKILL_SEDUCTION, loveslaves(*pool[s]) * 5);
		if (pool[s]->flag & CREATUREFLAG_LOVESLAVE)
			pool[s]->train(SKILL_SEDUCTION, 5);
	}
}
void dejuiceBoss(DeprecatedCreature &g) {
	int boss = getpoolcreature(g.hireid);
	if (boss != -1 && pool[boss]->juice > 50)
	{
		int juice = g.juice / 10;
		if (juice < 5) juice = 5;
		addjuice(*pool[boss], -juice, 0);
	}
}
DeprecatedCreature * getSleeperJudge(DeprecatedCreature g) {
	DeprecatedCreature * sleeperjudge = NULL;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		if (pool[p]->getNameAndAlignment().alive && (pool[p]->flag&CREATUREFLAG_SLEEPER) && LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,pool[p]->location) == LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,g.location))
		{
			if (pool[p]->type == CREATURE_JUDGE_CONSERVATIVE || pool[p]->type == CREATURE_JUDGE_LIBERAL)
				if (pool[p]->infiltration * 100 >= LCSrandom(100)) sleeperjudge = pool[p];
		}
	return sleeperjudge;
}
DeprecatedCreature * getSleeperLawyer(DeprecatedCreature g) {
	int maxsleeperskill = 0;
	DeprecatedCreature * sleeperlawyer = NULL;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		if (pool[p]->getNameAndAlignment().alive && (pool[p]->flag&CREATUREFLAG_SLEEPER) && LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,pool[p]->location) == LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,g.location))
		{
			if (pool[p]->type == CREATURE_LAWYER)
				if (pool[p]->get_skill(SKILL_LAW) + pool[p]->get_skill(SKILL_PERSUASION) >= maxsleeperskill)
				{
					sleeperlawyer = pool[p];
					maxsleeperskill = pool[p]->get_skill(SKILL_LAW) + sleeperlawyer->get_skill(SKILL_PERSUASION);
				}
		}
	return sleeperlawyer;
}

/*

	1 - Not apart of the LCS / Laying Low

	2 - Advocating Liberalism

	3 - Absent

*/
int getSleeperPresidentStatus()
{
	for (int p = 0; p < len(pool); p++)
	{
		if (pool[p]->getNameAndAlignment().alive)
		{
			//this could have issues if we later use the President's type for other creatures (or we alllow them to be comman types)
			if (pool[p]->id == uniqueCreatures.President().id)
			{
				if ((pool[p]->flag & CREATUREFLAG_SLEEPER))
				{
					//if President is advocating for elite lib they vote like it
					if (pool[p]->activity_type() == ACTIVITY_SLEEPER_LIBERAL)
						return 1;
					else
						return 0;
				}
				//if the President is absent let the VP vote
				else
					return 2;
			}

		}
	}
	//President is not LCS and votes as normal.
	return 0;
}


//Name is a bit misleading as this currently only clears their name (which is broken as of now)
void clearSleeperPresident()
{
	for (int p = 0; p < len(pool); p++)
	{
		if (pool[p]->getNameAndAlignment().alive)
		{
			if (pool[p]->id == uniqueCreatures.President().id)
			{
				pool[p]->propername[CREATURE_NAMELEN] = pool[p]->name[CREATURE_NAMELEN];
			}
		}
	}
	//clear recruit pool as well (might need to do dating)
	for (int r = 0; r < len(recruit); r++)
	{
		if (recruit[r]->recruit->getNameAndAlignment().alive)
		{
			if (recruit[r]->recruit->id == uniqueCreatures.President().id)
			{
				recruit[r]->recruit->name[CREATURE_NAMELEN] = recruit[r]->recruit->propername[CREATURE_NAMELEN];
			}

		}
	}
}

/*

	0 - Not apart of the LCS

	1 - Apart of the LCS and a sleeper

	2 - Active memeber of the LCS / Away


*/
int IsPresidentLCS()
{
	DeprecatedCreature* president = NULL;

	//recruits need to be checked first.
	for (int r = 0; r < len(recruit); r++)
	{
		if (recruit[r]->recruit->getNameAndAlignment().alive)
		{
			if (recruit[r]->recruit->id == uniqueCreatures.President().id)
			{
				return 2;
			}
		}
	}

	for (int p = 0; p < len(pool); p++)
	{
		if (pool[p]->getNameAndAlignment().alive)
		{
			//checking by type is not the best. However it allows us to clear sleeper ex-presidents easier
			if (pool[p]->id == uniqueCreatures.President().id)
			{
				if ((pool[p]->flag & CREATUREFLAG_SLEEPER))
				{
					return 1;
				}
				return 2;
			}

		}
	}
	
	return 0;
}

int otherPrisonersEscapeWithMe(DeprecatedCreature g, int prison) {
	int num_escaped = 0;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (pool[p]->location == prison && !(pool[p]->flag & CREATUREFLAG_SLEEPER))
		{
			criminalize(*pool[p], LAWFLAG_ESCAPED);
			pool[p]->location = g.location;
			num_escaped++;
		}
	}
	return num_escaped;
}

/* transforms a creature id number into the index of that person in the pool */
int getpoolcreature(int id)
{
	for (int i = 0; i < CreaturePool::getInstance().lenpool(); i++) if (pool[i]->id == id) return i;
	return -1;
}

/* common - test for possible game over */
char endcheck(char cause)
{
	bool dead = true;
	for (int p = 0; p < CreaturePool::getInstance().lenpool() && dead; p++)
		if (pool[p]->getNameAndAlignment().alive&&pool[p]->align == 1 &&
			!(pool[p]->flag&CREATUREFLAG_SLEEPER&&pool[p]->hireid != -1)) // Allow sleepers to lead LCS without losing
			dead = false;
	if (dead) // Did we just lose the game?
	{  // Game Over
		if (cause == END_BUT_NOT_END)
		{  // just checking for game over ahead of time but going back to the code for more stuff
			music.play(MUSIC_DEFEAT); // we were defeated, so play the right music
			return true; // go back to code, it has more text to display before we REALLY end the game
		}
		// OK if we didn't return yet it's REALLY Game Over, right now, but we need to find out why
		if (cause == END_OTHER)
		{  // got killed, possibly in a siege but maybe not, find out the reason we lost
			if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
			{
				switch (LocationsPool::getInstance().getSiegeType(getCurrentSite()))
				{
				case SIEGE_POLICE: savehighscore(END_POLICE); break;
				case SIEGE_CIA: savehighscore(END_CIA); break;
				case SIEGE_HICKS: savehighscore(END_HICKS); break;
				case SIEGE_CORPORATE: savehighscore(END_CORP); break;
				case SIEGE_CCS: savehighscore(END_CCS); break;
				case SIEGE_FIREMEN: savehighscore(END_FIREMEN); break;
				}
			}
			else savehighscore(END_DEAD);
		}
		else savehighscore(cause); // the reason we lost was specified in the function call
								   // You just lost the game!
		viewhighscores();
		end_game();
		return true;
	}
	return false; // Hey, we're still alive! We get to keep playing!
}
/* common - applies a crime to everyone in a location, or the entire LCS */
void criminalizepool(short crime, long exclude, short loc)
{
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (p == exclude) continue;
		if (loc != -1 && pool[p]->location != loc) continue;
		criminalize(*pool[p], crime);
	}
}
/* common - gives juice to a given creature */
void addjuice(DeprecatedCreature &cr, long juice, long cap)
{
	// Ignore zero changes
	if (juice == 0) return;
	// Check against cap
	if ((juice > 0 && cr.juice >= cap) ||
		(juice < 0 && cr.juice <= cap))
		return;
	// Apply juice gain
	cr.juice += juice;
	// Pyramid scheme of juice trickling up the chain
	if (cr.hireid != -1)
		for (int i = 0; i < CreaturePool::getInstance().lenpool(); i++)
			if (pool[i]->id == cr.hireid)
			{
				addjuice(*pool[i], juice / 5, cr.juice);
				break;
			}
	// Bounds check
	if (cr.juice > 1000)cr.juice = 1000;
	if (cr.juice < -50)cr.juice = -50;
}
// Determines the number of subordinates a creature may recruit,
// based on their max and the number they already command
int subordinatesleft(const DeprecatedCreature& cr)
{
	int recruitcap = maxsubordinates(cr);
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		// ignore seduced and brainwashed characters
		if (pool[p]->hireid == cr.id&&pool[p]->getNameAndAlignment().alive && !(pool[p]->flag&(CREATUREFLAG_LOVESLAVE | CREATUREFLAG_BRAINWASHED)))
			recruitcap--;
	if (recruitcap > 0) return recruitcap;
	else return 0;
}
// Determines the number of love slaves a creature has
int loveslaves(const DeprecatedCreature& cr)
{
	int loveslaves = 0;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		// If subordinate and a love slave
		if (pool[p]->hireid == cr.id && pool[p]->getNameAndAlignment().alive && pool[p]->flag & CREATUREFLAG_LOVESLAVE)
			loveslaves++;
	return loveslaves;
}
/* The following boolean functions will return true if first is supposed to be
before second in the list. */
bool sort_none(const DeprecatedCreature* first, const DeprecatedCreature* second) //This will sort sorted back to unsorted.
{
	for (int j = 0; j < CreaturePool::getInstance().lenpool(); j++)
		if (pool[j] == first) return true;
		else if (pool[j] == second) return false;
		return false;
}