



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
/*
        This file was created by Chris Johnson (grundee@users.sourceforge.net)
        by copying code from game.cpp.
        To see descriptions of files and functions, see the list at
        the bottom of includes.h in the top src folder.
*/

#include "../includes45.h"
#include "../constStringactivities.h"
#include <algorithm>
vector<string> quality_0;
vector<string> quality_20;
vector<string> quality_35;
vector<string> quality_50;
vector<string> words_meaning_hacked;
vector<string> enemy_website;
vector<string> win_hand_to_hand;
vector<string> lose_hand_to_hand;
vector<string> car_wont_start;
vector<string> gets_nervous;
vector<string> cant_hotwire_car;
vector<string> almost_hotwire_car;
vector<string> cant_find_keys;
vector<string> cant_find_keys_no_free_speech;
map< Views, stringConnectedToView > pollingData;
map< Activity, CreatureSkill> trainingActivity;

vector<file_and_text_collection> activities_text_file_collection = {
	/*activities.cpp*/
	customText(&quality_0, ACTIVITIES_FOLDER + CONST_X_QUALITY_0_TXT),
	customText(&quality_20, ACTIVITIES_FOLDER + CONST_X_QUALITY_20_TXT),
	customText(&quality_35, ACTIVITIES_FOLDER + CONST_X_QUALITY_35_TXT),
	customText(&quality_50, ACTIVITIES_FOLDER + CONST_X_QUALITY_50_TXT),
	customText(&words_meaning_hacked, ACTIVITIES_FOLDER + CONST_X_WORDS_MEANING_HACKED_TXT),
	customText(&enemy_website, ACTIVITIES_FOLDER + CONST_X_ENEMY_WEBSITE_TXT),
	customText(&win_hand_to_hand, ACTIVITIES_FOLDER + CONST_X_WIN_HAND_TO_HAND_TXT),
	customText(&lose_hand_to_hand, ACTIVITIES_FOLDER + CONST_X_LOST_HAND_TO_HAND_TXT),
	customText(&car_wont_start, ACTIVITIES_FOLDER + CONST_X_CAR_WONT_START_TXT),
	customText(&gets_nervous, ACTIVITIES_FOLDER + CONST_X_GETS_NERVOUS_TXT),
	customText(&cant_hotwire_car, ACTIVITIES_FOLDER + CONST_X_CANT_HOTWIRE_TXT),
	customText(&almost_hotwire_car, ACTIVITIES_FOLDER + CONST_X_ALMOST_HOTWIRE_TXT),
	customText(&cant_find_keys, ACTIVITIES_FOLDER + CONST_X_CANT_FIND_KEYS_TXT),
	customText(&cant_find_keys_no_free_speech, ACTIVITIES_FOLDER + CONST_X_CANT_FIND_KEYS_NFS_TXT),
};
void adjustblogpower(int &power)
{
	if (power < 20)
	{
		addstrAlt(pickrandom(quality_0));
		power = -signed(LCSrandom(2));
	}
	else if (power < 35)
	{
		addstrAlt(pickrandom(quality_20));
		power = 1;
	}
	else if (power < 50)
	{
		addstrAlt(pickrandom(quality_35));
		power = 2;
	}
	else
	{
		addstrAlt(pickrandom(quality_50));
		power = 3;
	}
}
struct trainItem {
	CreatureSkill whichSkill;
	int experience;
	int maxLevel;
	trainItem(CreatureSkill whichSkill_, int experience_, int maxLevel_) :whichSkill(whichSkill_), experience(experience_), maxLevel(maxLevel_) {}
};
struct stringAndMaybeTrain {
	string str;
	vector<trainItem> trainingItem;
	stringAndMaybeTrain(const string& str_, const vector<trainItem>& trainingItem_) : str(str_), trainingItem(trainingItem_) {}
};
vector<stringAndMaybeTrain> cleanSafeHouse = {
	stringAndMaybeTrain(CONST_X_TIDIES_SAFEHOUSE, vector<trainItem>({})),
	stringAndMaybeTrain(CONST_X_REORGANIZES_CLOSET, vector<trainItem>({})),
	stringAndMaybeTrain(CONST_X_CLEANS_KITCHEN, vector<trainItem>({})),
	stringAndMaybeTrain(CONST_X_PERUSES_MAGAZINES, vector<trainItem>({ trainItem(SKILL_TAILORING, 1,MAXATTRIBUTE) }))
};

int armor_makedifficulty(Armor& type, DeprecatedCreature *cr); //Replace with Armor class method? -XML
int armor_makedifficulty(ArmorType& type, DeprecatedCreature *cr); //Replace with Armor class method? -XML

/* armor manufacture */
void makearmor(DeprecatedCreature &cr, char &clearformess)
{
	int at = cr.activity_arg();
	int cost = armortype[at]->get_make_price();
	int hcost = (cost >> 1) + 1;
	int dif = armor_makedifficulty(*armortype[at], &cr);
	if (ledger.get_funds() < hcost)
	{
		if (clearformess) eraseAlt();
		else makedelimiter();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 1, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_CANNOT_AFFORD_MATERIAL, gamelog);
		gamelog.nextMessage();
		pressAnyKey();
		return;
	}
	else
	{
		char foundcloth = 0;
		if (cr.squadid != -1)
		{
			int sq = getsquad(cr.squadid);
			for (int l = 0; l < len(squad[sq]->loot); l++)
				if (squad[sq]->loot[l]->whatIsThis() == THIS_IS_LOOT &&
					(squad[sq]->loot[l])->is_cloth()) //cast -XML
				{
					if (squad[sq]->loot[l]->get_number() == 1)
						delete_and_remove(squad[sq]->loot, l);
					else squad[sq]->loot[l]->decrease_number(1);
					foundcloth = 1;
					break;
				}
		}
		if (!foundcloth) foundcloth = tryFindCloth(cr.location);
		if (!foundcloth&&ledger.get_funds() < cost)
		{
			if (clearformess) eraseAlt();
			else makedelimiter();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(8, 1, cr.getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_X_CANNOT_FIND_CLOTH, gamelog);
			gamelog.nextMessage();
			pressAnyKey();
		}
		else
		{
			if (foundcloth) ledger.subtract_funds(hcost, EXPENSE_MANUFACTURE);
			else ledger.subtract_funds(cost, EXPENSE_MANUFACTURE);
			cr.train(SKILL_TAILORING, dif * 2 + 1);
			int quality = 1;
			while (LCSrandom(10) < dif && quality <= armortype[at]->get_quality_levels())
				quality++;
			if (clearformess) eraseAlt();
			else makedelimiter();
			Item *it = new Armor(at, quality);
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(8, 1, cr.getNameAndAlignment().name, gamelog);
			if (quality <= ((Armor*)it)->get_quality_levels())
			{
				addstrAlt(CONST_X_HAS_MADE_A, gamelog);
				switch (quality)
				{
				case 1:addstrAlt(CONST_X_FIRST_RATE, gamelog); break;
				case 2:addstrAlt(CONST_X_SECOND_RATE, gamelog); break;
				case 3:addstrAlt(CONST_X_THIRD_RATE, gamelog); break;
				case 4:addstrAlt(CONST_X_FOURTH_RATE, gamelog); break;
				default:addstrAlt(quality, gamelog); addstrAlt(CONST_X_TH_RATE, gamelog); break;
				}
				addLootToLoc(cr.location, it);
			}
			else
			{
				addstrAlt(CONST_X_WASTED_MATERIALS, gamelog);
			}
			addstrAlt(singleSpace, gamelog);
			addstrAlt(armortype[at]->get_name(), gamelog);
			addstrAlt(singleDot, gamelog);
			gamelog.nextMessage();
			pressAnyKey();
		}
	}
}
/* search for polls */
map<short, string> supportsLiberalLaw;
int get_noise_based_on_skill(const int creatureskill) {
	int noise;

	if (creatureskill < 1) noise = 18 + LCSrandom(3); // 18 to 20
	else if (creatureskill < 2) noise = 16 + LCSrandom(2); // 16 or 17
	else if (creatureskill < 3) noise = 14 + LCSrandom(2); // 14 or 15
	else if (creatureskill < 4) noise = 12 + LCSrandom(2); // 12 or 13
	else if (creatureskill < 5) noise = 10 + LCSrandom(2); // 10 or 11
	else if (creatureskill < 6) noise = 8 + LCSrandom(2); // 8 or 9
	else if (creatureskill < 7) noise = 7;
	else if (creatureskill < 9) noise = 6;
	else if (creatureskill < 11) noise = 5;
	else if (creatureskill < 14) noise = 4;
	else if (creatureskill < 18) noise = 3;
	else noise = 2;

	return noise;
}
void print_issue_box(const int noise) {
	//Header for issue box
	mvaddstrAlt(6, 0, CONST_X_ADDITIONAL_FINDINGS);
	mvaddstrAlt(7, 0, CONST_X_ISSUE_PUBLIC_INTEREST_HEADER);
	//Footer
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 0, CONST_X_RESULTS_ARE_PLUS_MINUS);
	addstrAlt(noise);
	addstrAlt(CONST_X_LIBERAL_PERCENTAGE_POINTS);
	mvaddstrAlt(24, 0, CONST_X_ENTER_DONE);
	mvaddstrAlt(24, 40, addprevpagestr() + CONST_X_LITTLE_WHITESPACE + addnextpagestr());
}
void draw_issue_page(const int page, const int noise, const int survey[], const char SURVEY_PAGE_SIZE) {


	int y = 8;
	//Draw each line
	for (int v = page * SURVEY_PAGE_SIZE; v < (page + 1)*SURVEY_PAGE_SIZE; v++, y++)
	{
		if (v >= VIEWNUM || (v == VIEW_CONSERVATIVECRIMESQUAD && (endgamestate >= ENDGAME_CCS_DEFEATED || newscherrybusted < 2)))
		{
			mvaddstrAlt(y, 0, CONST_X_LOTS_OF_WHITESPACE);
			continue;
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(y, 4, CONST_X_MANY_DOTS);
		if (noise >= 7 || survey[v] == -1) addstrAlt(CONST_X_UNKNOWN);
		else if (noise >= 4)
		{
			if (public_interest[v] > 50) addstrAlt(CONST_X_HIGH);
			else addstrAlt(CONST_X_LOW);
		}
		else
		{
			if (public_interest[v] > 100) addstrAlt(CONST_X_VERY_HIGH);
			else if (public_interest[v] > 50) addstrAlt(CONST_X_HIGH);
			else if (public_interest[v] > 10) addstrAlt(CONST_X_MODERATE);
			else if (public_interest[v]) addstrAlt(CONST_X_LOW);
			else addstrAlt(CONST_X_NONE_SPACE);
		}
		if (survey[v] == -1)set_color_easy(BLACK_ON_BLACK_BRIGHT);
		else if (survey[v] < 10)set_color_easy(RED_ON_BLACK_BRIGHT);
		else if (survey[v] < 30)set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
		else if (survey[v] < 50)set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		else if (survey[v] < 70)set_color_easy(BLUE_ON_BLACK_BRIGHT);
		else if (survey[v] < 90)set_color_easy(CYAN_ON_BLACK_BRIGHT);
		else set_color_easy(GREEN_ON_BLACK_BRIGHT);
		moveAlt(y, 0);
		if (survey[v] == -1) addstrAlt(CONST_X_TWO_QUESTION_MARKS);
		else
		{
			if (survey[v] < 10)addcharAlt('0');
			addstrAlt(survey[v]);
		}
		addstrAlt(CONST_X_PERCENT_SIGN);
		if (v == VIEW_DRUGS) {
			if (lawList[LAW_DRUGS] >= 1) addstrAlt(CONST_X_SUPPORTED_MARIJUANA_LEGAL);
			else addstrAlt(CONST_X_BELIEVE_IN_LEGAL_MARIJUANA);
		}
		else if (v == VIEW_IMMIGRATION) {
			if (lawList[LAW_IMMIGRATION] >= 1) addstrAlt(CONST_X_CONDEMN_IMMIGRATION_REGULATIONS);
			else addstrAlt(CONST_X_AMNESTY_FOR_IMMIGRANTS);
		}
		else {
			addstrAlt(supportsLiberalLaw[v]);
		}
	}
}
void printMostConcernedAbout(const int maxview) {

	switch (maxview)
	{
		//case VIEW_POLITICALVIOLENCE:
		//   if(attitude[VIEW_POLITICALVIOLENCE]>50) addstrAlt(CONST_X_TAKING_STRONG_ACTION);
		//   else addstrAlt(...);
		//   break;
	case VIEW_LIBERALCRIMESQUAD:
	case VIEW_LIBERALCRIMESQUADPOS:
		if (attitude[VIEW_LIBERALCRIMESQUAD] < 50) addstrAlt(CONST_X_ACTIVIST_POLITICAL_GROUPS);
		else
		{
			if (attitude[VIEW_LIBERALCRIMESQUADPOS] > 50) addstrAlt(CONST_X_THE_LIBERAL_CRIME_SQUAD);
			else addstrAlt(CONST_X_THE_LCS_TERRORISTS);
		}
		break;
	case VIEW_AMRADIO:
	case VIEW_CABLENEWS:
		if (attitude[VIEW_AMRADIO] + attitude[VIEW_CABLENEWS] > 100) addstrAlt(CONST_X_CONSERVATIVE_MEDIA_BIAS);
		else addstrAlt(CONST_X_LIBERAL_MEDIA_BIAS);
		break;
	default:
		stringConnectedToView currentView = pollingData[(Views)maxview];
		if (attitude[maxview] > 50) {
			addstrAlt(pollingData[(Views)maxview].aboveFifty);
		}
		else {
			if (lawList[maxview] == 2) {
				addstrAlt(pollingData[(Views)maxview].belowFiftyEliteLiberalLaw);
			}
			else if (lawList[maxview] >= 1) {
				addstrAlt(pollingData[(Views)maxview].belowFiftyLiberalLaw);
			}
			else {
				addstrAlt(currentView.belowFifty);
			}
		}
		break;
	}
}
int surveyValue(const int v, const int noise, const int misschance) {
	int survey;
	survey = attitude[v];
	//MAKE SURVEY ACCURATE IF DEBUGGING
	if (!SHOWMECHANICS) {
		do { survey += LCSrandom(noise * 2 + 1) - noise; } while (!LCSrandom(20));
	}
	if (survey < 0) survey = 0;
	if (survey > 100) survey = 100;
	if (!SHOWMECHANICS) {
		if (LCSrandom(public_interest[v] + 100) < int(misschance)) survey = -1;
	}
	if (v == VIEW_LIBERALCRIMESQUAD && attitude[v] == 0) survey = -1;
	return survey;
}
int findmaxview(const int _maxview, const int v) {
	int maxview = _maxview;
	if (v != VIEW_LIBERALCRIMESQUAD && v != VIEW_LIBERALCRIMESQUADPOS/*&&v!=VIEW_POLITICALVIOLENCE*/)
	{
		if (_maxview != -1) { if (public_interest[v] > public_interest[_maxview]) maxview = v; }
		else { if (public_interest[v] > 0) maxview = v; }
	}
	return maxview;

}
void survey(DeprecatedCreature *cr)
{
	music.play(MUSIC_ELECTIONS);
	const int creatureskill = cr->skill_roll(SKILL_COMPUTERS);
	const int misschance = max(30 - creatureskill, 5);
	const int noise = get_noise_based_on_skill(creatureskill);
	int survey[VIEWNUM];
	int maxview = -1;
	for (int v = 0; v < VIEWNUM; v++)
	{
		survey[v] = surveyValue(v, noise, misschance);
		maxview = findmaxview(maxview, v);
	}
	if (survey[VIEW_LIBERALCRIMESQUAD] <= 0) survey[VIEW_LIBERALCRIMESQUADPOS] = -1;
	eraseAlt();
	//TODO: Sort out the gamelog for this.
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(0, 0, CONST_X_SURVEY_OF_PUBLIC_OPINION);
	int approval = presidentapproval();
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(2, 0, approval / 10 + (LCSrandom(noise * 2 + 1) - noise), gamelog);
	addstrAlt(CONST_X_HAD_FAVORABLE_OPINION);
	set_alignment_color(exec[EXEC_PRESIDENT], true);
	addstrAlt(CONST_X_PRESIDENT);
	addstrAlt(execname[EXEC_PRESIDENT]);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(singleDot);
	//Top excitement issue
	if (maxview != -1)
	{
		mvaddstrAlt(4, 0, CONST_X_THE_PEOPLE_ARE_MOST_CONCERNED);
		printMostConcernedAbout(maxview);
	}
	else
	{
		mvaddstrAlt(4, 0, CONST_X_THE_PUBLIC_IS_UNCONCERNED);
	}
	print_issue_box(noise);
	int page = 0;
	const int maxpage = VIEWNUM / SURVEY_PAGE_SIZE;
	int c = '0';
	while (c != 'x' && c != ENTER && c != ESC && c != SPACEBAR)
	{
		//Keep pages within bounds
		if (page < 0) page = maxpage;
		if (page > maxpage) page = 0;
		//Start from the top
		draw_issue_page(page, noise, survey, SURVEY_PAGE_SIZE);
		do {
			c = getkeyAlt();
			if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) {}
			else if (is_page_up(c)) { page--; }
			else if (is_page_down(c)) { page++; }
		} while (c != 'x' && c != ENTER && c != ESC && c != SPACEBAR && c != interface_pgup && c != KEY_UP && c != KEY_LEFT && c != interface_pgdn && c != KEY_DOWN && c != KEY_RIGHT);

	}
}
// Police accost your liberal!
void attemptarrest(DeprecatedCreature & liberal, const char* str, int clearformess)
{


	if (str)
	{
		if (clearformess) eraseAlt();
		else makedelimiter();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 1, liberal.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_IS_ACCOSTED_BY_POLICE, gamelog);
		addstrAlt(str, gamelog);
		addstrAlt(CONST_X_EXCLAMATION_POINT, gamelog);
		gamelog.nextMessage();
		pressAnyKey();
	}
	// Chase sequence! Wee!
	makechasers(-1, 5);
	if (!sitestory)
	{
		Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
		ns->type = NEWSSTORY_WANTEDARREST; // TODO: Make a more generic catch-all arrest story
		ns->loc = -1;
		newsstory.push_back(ns);
		sitestory = ns;
	}
	chaseseq.clean();
	chaseseq.location = LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONPARENT,liberal.location);
	footchase(liberal);
}
// While galavanting in public, your liberals may be ambushed by police
int checkforarrest(DeprecatedCreature & liberal, const char* string, int clearformess)
{
	bool arrest = false;
	if (!liberal.animalgloss && liberal.is_naked() && LCSrandom(2))
	{
		criminalize(liberal, LAWFLAG_DISTURBANCE);
		Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
		ns->type = NEWSSTORY_NUDITYARREST;
		ns->loc = -1;
		newsstory.push_back(ns);
		sitestory = ns;
		arrest = true;
	}
	else if (liberal.heat > liberal.get_skill(SKILL_STREETSENSE) * 10)
	{
		if (!LCSrandom(50))
		{
			Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
			ns->type = NEWSSTORY_WANTEDARREST;
			ns->loc = -1;
			newsstory.push_back(ns);
			sitestory = ns;
			arrest = true;
		}
	}
	if (arrest) attemptarrest(liberal, string, clearformess);
	return arrest;
}
/* misc activation related things */
// *JDSRETURN*
void funds_and_trouble(char &clearformess)
{
	vector<DeprecatedCreature *> trouble, hack, bury, solicit, tshirts, art, music, graffiti, brownies, prostitutes, teachers, students;
	for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
	{
		if (!pool[p]->getNameAndAlignment().alive) continue;
		if (pool[p]->location == -1)
		{
			pool[p]->set_activity_type(ACTIVITY_NONE);
			continue;
		}
		switch (pool[p]->activity_type())
		{
		case ACTIVITY_TEACH_FIGHTING:
		case ACTIVITY_TEACH_POLITICS:
		case ACTIVITY_TEACH_COVERT:
			teachers.push_back(pool[p]);
			break;
		case ACTIVITY_CCFRAUD:
		case ACTIVITY_DOS_RACKET:
		case ACTIVITY_DOS_ATTACKS:
		case ACTIVITY_HACKING:
			hack.push_back(pool[p]);
			break;
		case ACTIVITY_GRAFFITI:
			graffiti.push_back(pool[p]);
			break;
		case ACTIVITY_TROUBLE:
			trouble.push_back(pool[p]);
			break;
		case ACTIVITY_COMMUNITYSERVICE:
			addjuice(*pool[p], 1, 10);
			change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 1, 0, 80);
			break;
		case ACTIVITY_SELL_TSHIRTS:
			tshirts.push_back(pool[p]);
			break;
		case ACTIVITY_SELL_ART:
			art.push_back(pool[p]);
			break;
		case ACTIVITY_SELL_MUSIC:
			music.push_back(pool[p]);
			break;
		case ACTIVITY_DONATIONS:
			solicit.push_back(pool[p]);
			break;
		case ACTIVITY_SELL_DRUGS:
			brownies.push_back(pool[p]);
			break;
		case ACTIVITY_PROSTITUTION:
			prostitutes.push_back(pool[p]);
			break;
		case ACTIVITY_BURY:
			bury.push_back(pool[p]);
			pool[p]->set_activity_type(ACTIVITY_NONE);
			break;
		case ACTIVITY_CLINIC:
			hospitalize(find_site_index_in_same_city(SITE_HOSPITAL_CLINIC, pool[p]->location), *pool[p]);
			pool[p]->set_activity_type(ACTIVITY_NONE);
			break;
		case ACTIVITY_STUDY_DEBATING:
		case ACTIVITY_STUDY_MARTIAL_ARTS:
		case ACTIVITY_STUDY_DRIVING:
		case ACTIVITY_STUDY_PSYCHOLOGY:
		case ACTIVITY_STUDY_FIRST_AID:
		case ACTIVITY_STUDY_LAW:
		case ACTIVITY_STUDY_DISGUISE:
		case ACTIVITY_STUDY_SCIENCE:
		case ACTIVITY_STUDY_BUSINESS:
			//case ACTIVITY_STUDY_COOKING:
		case ACTIVITY_STUDY_GYMNASTICS:
		case ACTIVITY_STUDY_ART:
		case ACTIVITY_STUDY_TEACHING:
		case ACTIVITY_STUDY_MUSIC:
		case ACTIVITY_STUDY_WRITING:
		case ACTIVITY_STUDY_LOCKSMITHING:
		case ACTIVITY_STUDY_COMPUTERS:
		case ACTIVITY_STUDY_FENCING:
		case ACTIVITY_STUDY_WEAVING:
		case ACTIVITY_STUDY_RELIGION:
			//case ACTIVITY_STUDY_MAGIC:
		case ACTIVITY_STUDY_CLUB:
		case ACTIVITY_STUDY_STREETSENSE:
		case ACTIVITY_STUDY_THROWING:
		case ACTIVITY_STUDY_STEALTH:
		case ACTIVITY_STUDY_SEDUCTION:
			students.push_back(pool[p]);
			break;
		case ACTIVITY_SLEEPER_JOINLCS:
			if (!LocationsPool::getInstance().isThereASiegeHere(find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, pool[p]->location)))
			{
				pool[p]->set_activity_type(ACTIVITY_NONE);
				pool[p]->flag &= ~CREATUREFLAG_SLEEPER;
				pool[p]->location = pool[p]->base = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, pool[p]->location);
			}
			//Letters to the editor
		case ACTIVITY_WRITE_LETTERS:
			if (pool[p]->skill_check(SKILL_WRITING, DIFFICULTY_EASY))
				background_liberal_influence[randomissue()] += 5;
			pool[p]->train(SKILL_WRITING, LCSrandom(5) + 1);
			break;
			//Guardian Essays
			//Basically letters to the editor, but thrice as potent, and can backfire
		case ACTIVITY_WRITE_GUARDIAN:
			if (pool[p]->skill_check(SKILL_WRITING, DIFFICULTY_EASY))
				background_liberal_influence[randomissue()] += 15;
			else
				background_liberal_influence[randomissue()] -= 15;
			pool[p]->train(SKILL_WRITING, LCSrandom(5) + 1);
			break;
		}
	}
	doActivitySolicitDonations(solicit, clearformess);
	doActivitySellTshirts(tshirts, clearformess);
	doActivitySellArt(art, clearformess);
	doActivitySellMusic(music, clearformess);
	doActivitySellBrownies(brownies, clearformess);
	doActivityHacking(hack, clearformess);
	doActivityGraffiti(graffiti, clearformess);
	doActivityProstitution(prostitutes, clearformess);
	doActivityLearn(students, clearformess);
	doActivityTrouble(trouble, clearformess);
	doActivityTeach(teachers, clearformess);
	doActivityBury(bury, clearformess);
}
void doActivitySolicitDonations(vector<DeprecatedCreature *> &solicit, char &clearformess)
{  //SOLICITORS
	long total_income = 0;
	for (int s = 0; s < len(solicit); s++)
	{
		if (!checkforarrest(*solicit[s], CONST_X_SOLICITING_DONATIONS.c_str(), clearformess))
		{
			int income = solicit[s]->skill_roll(SKILL_PERSUASION) *
				solicit[s]->get_armor().get_professionalism() + 1;
			// Country's alignment dramatically affects effectiveness
			// The more conservative the country, the more effective
			if (publicmood(-1) > 90) income /= 2;
			if (publicmood(-1) > 65) income /= 2;
			if (publicmood(-1) > 35) income /= 2;
			if (publicmood(-1) > 10) income /= 2;
			solicit[s]->income = income;
			total_income += income;
			solicit[s]->train(SKILL_PERSUASION, max(5 - solicit[s]->get_skill(SKILL_PERSUASION), 2));
		}
	}
	ledger.add_funds(total_income, INCOME_DONATIONS);
}
void doActivitySellTshirts(vector<DeprecatedCreature *> &tshirts, char &clearformess)
{
	for (int s = 0; s < len(tshirts); s++)
	{
		if (!checkforarrest(*tshirts[s], CONST_X_SELLING_SHIRTS.c_str(), clearformess))
		{
			long money = (tshirts[s]->skill_roll(SKILL_TAILORING) +
				tshirts[s]->skill_roll(SKILL_BUSINESS)) / 2;
			// Country's alignment affects effectiveness
			// In a Liberal country, there are many competing vendors
			if (publicmood(-1) > 65) money /= 2;
			if (publicmood(-1) > 35) money /= 2;
			//If you're selling epic shirts enough they'll have some political impact
			if (tshirts[s]->skill_check(SKILL_TAILORING, DIFFICULTY_FORMIDABLE))
				background_liberal_influence[randomissue()] += 5;
			tshirts[s]->income = money;
			ledger.add_funds(money, INCOME_TSHIRTS);
			tshirts[s]->train(SKILL_TAILORING, max(7 - tshirts[s]->get_skill(SKILL_TAILORING), 2));
			tshirts[s]->train(SKILL_BUSINESS, max(7 - tshirts[s]->get_skill(SKILL_BUSINESS), 2));
		}
	}
}
void doActivitySellArt(vector<DeprecatedCreature *> &art, char &clearformess)
{
	for (int s = 0; s < len(art); s++)
	{
		if (!checkforarrest(*art[s], CONST_X_SKETCHING_PORTRAITS.c_str(), clearformess))
		{
			long money = art[s]->skill_roll(SKILL_ART);
			// Country's alignment affects effectiveness
			// In a Liberal country, there are many competing vendors
			if (publicmood(-1) > 65) money /= 2;
			if (publicmood(-1) > 35) money /= 2;
			//Epic Liberal art may have positive political effect
			if (art[s]->skill_check(SKILL_ART, DIFFICULTY_FORMIDABLE))
				background_liberal_influence[randomissue()] += 5;
			art[s]->income = money;
			ledger.add_funds(money, INCOME_SKETCHES);
			art[s]->train(SKILL_ART, max(7 - art[s]->get_skill(SKILL_ART), 4));
		}
	}
}
void doActivitySellMusic(vector<DeprecatedCreature *> &music, char &clearformess)
{
	for (int s = 0; s < len(music); s++)
	{
		if (!checkforarrest(*music[s], CONST_X_PLAYING_MUSIC.c_str(), clearformess))
		{
			long money = music[s]->skill_roll(SKILL_MUSIC) / 2;
			bool has_instrument = music[s]->get_weapon().get_specific_bool(BOOL_INSTRUMENT_);
			if (has_instrument) money *= 4;
			// Country's alignment affects effectiveness
			// In a Liberal country, there are many competing vendors
			if (publicmood(-1) > 65) money /= 2;
			if (publicmood(-1) > 35) money /= 2;
			//Epic Liberal protest songs
			if (music[s]->skill_check(SKILL_MUSIC, DIFFICULTY_FORMIDABLE))
				background_liberal_influence[randomissue()] += has_instrument ? 10 : 5;
			ledger.add_funds(money, INCOME_BUSKING);
			music[s]->income = money;
			if (has_instrument) music[s]->train(SKILL_MUSIC, max(7 - music[s]->get_skill(SKILL_MUSIC), 4));
			else music[s]->train(SKILL_MUSIC, max(5 - music[s]->get_skill(SKILL_MUSIC), 2));
		}
	}
}
void doActivitySellBrownies(vector<DeprecatedCreature *> &brownies, char &clearformess)
{
	for (int s = 0; s < len(brownies); s++)
	{
		//Check for police search
		int dodgelawroll = LCSrandom(1 + 30 * lawList[LAW_DRUGS] + 3);
		//Saved by street sense?
		if (dodgelawroll == 0)
			dodgelawroll = brownies[s]->skill_check(SKILL_STREETSENSE, DIFFICULTY_AVERAGE);
		if (dodgelawroll == 0 && lawList[LAW_DRUGS] <= 0) // Busted!
		{
			Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
			ns->type = NEWSSTORY_DRUGARREST;
			ns->loc = -1;
			newsstory.push_back(ns);
			sitestory = ns;
			criminalize(*brownies[s], LAWFLAG_BROWNIES);
			attemptarrest(*brownies[s], CONST_X_SELLING_BROWNIES.c_str(), clearformess);
		}
		long money = brownies[s]->skill_roll(SKILL_PERSUASION) +
			brownies[s]->skill_roll(SKILL_BUSINESS) +
			brownies[s]->skill_roll(SKILL_STREETSENSE);
		// more money when more illegal
		if (lawList[LAW_DRUGS] == -2) money *= 4;
		if (lawList[LAW_DRUGS] == -1) money *= 2;
		if (lawList[LAW_DRUGS] == 1) money /= 4;
		if (lawList[LAW_DRUGS] == 2) money /= 8;
		brownies[s]->income = money;
		ledger.add_funds(money, INCOME_BROWNIES);
		// Make the sale
		brownies[s]->train(SKILL_PERSUASION, max(4 - brownies[s]->get_skill(SKILL_PERSUASION), 1));
		// Know the streets
		brownies[s]->train(SKILL_STREETSENSE, max(7 - brownies[s]->get_skill(SKILL_STREETSENSE), 3));
		// Manage your money
		brownies[s]->train(SKILL_BUSINESS, max(10 - brownies[s]->get_skill(SKILL_BUSINESS), 3));
	}
}
vector<activityData> hackingActivities;
void doActivityHacking(vector<DeprecatedCreature *> &hack, char &clearformess)
{
	if (len(hack))
	{
		vector<DeprecatedCreature *> cc,/*web,ddos,*/truehack;
		//First, do accounting to figure out who's doing what
		for (int h = 0; h < len(hack); h++)
		{
			switch (hack[h]->activity_type())
			{
			case ACTIVITY_CCFRAUD:
				hack[h]->train(SKILL_COMPUTERS, 2);
				cc.push_back(hack[h]);
				break;
			case ACTIVITY_DOS_ATTACKS:
				hack[h]->train(SKILL_COMPUTERS, 2);
				//web.push_back(hack[h]);
				break;
			case ACTIVITY_DOS_RACKET:
				hack[h]->train(SKILL_COMPUTERS, 4);
				// ddos.push_back(hack[h]);
				break;
			case ACTIVITY_HACKING:
				hack[h]->train(SKILL_COMPUTERS, 4);
				truehack.push_back(hack[h]);
				break;
			}
		}
		char msg[200] = { 0 };
		//MAJOR HACKING
		int hack_skill = 0;
		for (int h = 0; h < len(truehack); h++)
			hack_skill = max(hack_skill, truehack[h]->skill_roll(SKILL_COMPUTERS));
		if (DIFFICULTY_HEROIC <= hack_skill + len(truehack) - 1)
		{
			if (len(truehack) > 1) strcpy(msg, CONST_X_YOUR_HACKERS_HAVE_.c_str());
			else { strcpy(msg, truehack[0]->getNameAndAlignment().name.data()); strcat(msg, CONST_X_HAS_.c_str()); }
			int trackdif = 0, juiceval = 0;
			int short crime = 0;
			activityData currentActivity = pickrandom(hackingActivities);
			strcat(msg, currentActivity.msgString);
			trackdif = currentActivity.difficulty;
			crime = currentActivity.crime;
			juiceval = currentActivity.juiceval;
			if (len(currentActivity.lootType) > 0) {
				addLootToLoc(hack[0]->location, getNewLoot(pickrandom(currentActivity.lootType)));
			}
			for (ChangeOfOpinion o : currentActivity.opinion) {
				change_public_opinion(o.view, o.x, o.y, o.z);
			}
			if (trackdif > hack_skill + LCSrandom(5) - 2)
				for (int h = 0; h < len(truehack); h++)
					criminalize(*hack[h], crime);
			// Award juice to the hacking team for a job well done
			for (int h = 0; h < len(truehack); h++)
				addjuice(*truehack[h], juiceval, 200);
		}
		else if (DIFFICULTY_FORMIDABLE <= hack_skill + len(truehack) - 1)
		{
			int issue = LCSrandom(VIEWNUM - 5), crime = LAWFLAG_INFORMATION;
			if (len(truehack) > 1) strcpy(msg, CONST_X_YOUR_HACKERS_HAVE_LOWERCASE.c_str());
			else { strcpy(msg, truehack[0]->getNameAndAlignment().name.data()); strcat(msg, CONST_X_HAS_.c_str()); }
			strcat(msg, pickrandom(words_meaning_hacked).data());
			strcat(msg, CONST_X_A_SPACE.c_str());
			strcat(msg, pickrandom(enemy_website).data());
			strcat(msg, singleDot.data());
			change_public_opinion(issue, 1);
			if (DIFFICULTY_HEROIC > hack_skill + LCSrandom(5) - 2)
				for (int h = 0; h < len(truehack); h++)
					criminalize(*truehack[h], crime);
			// Award juice to the hacking team for a job well done
			for (int h = 0; h < len(truehack); h++)
				addjuice(*truehack[h], 5, 100);
		}
		if (msg[0])
		{
			if (clearformess) eraseAlt();
			else makedelimiter();
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(8, 1, msg, gamelog);
			gamelog.nextMessage();
			msg[0] = 0;
			pressAnyKey();
		}
		//CREDIT CARD FRAUD
		for (int h = 0; h < len(cc); h++)
		{
			hack_skill = cc[h]->skill_roll(SKILL_COMPUTERS);
			int difficulty = DIFFICULTY_CHALLENGING;
			if (difficulty <= hack_skill)
			{
				// *JDS* You get between $1 and $100, plus an extra $1-50 every
				// time you pass a check against your hacking skill, where chance of
				// failure is one over the adjusted hackers' skill divided by four. Once
				// a check fails, no more money is gained. This check will be made
				// up to 20 times, at which point the loop breaks. The skill check
				// here doesn't take into account funding.
				int fundgain = LCSrandom(101);
				while (difficulty < hack_skill)
				{
					fundgain += LCSrandom(51);
					difficulty += 2;
				}
				ledger.add_funds(fundgain, INCOME_CCFRAUD);
				cc[h]->income = fundgain / len(cc);
				if (fundgain / 25 > LCSrandom(hack_skill + 1))
					criminalize(*cc[h], LAWFLAG_CCFRAUD);
			}
			if (msg[0])
			{
				if (clearformess) eraseAlt();
				else makedelimiter();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, msg, gamelog); //TODO: Log this?
				gamelog.nextMessage();
				msg[0] = 0;
				pressAnyKey();
			}
		}
	}
}
void doActivityGraffiti(vector<DeprecatedCreature *> &graffiti, char &clearformess)
{
	if (len(graffiti))
	{
		for (int s = 0; s < len(graffiti); s++)
		{
			if (!graffiti[s]->get_weapon().get_specific_bool(BOOL_CAN_GRAFFITI_))
			{
				if (clearformess) eraseAlt();
				else makedelimiter();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, graffiti[s]->getNameAndAlignment().name, gamelog);
				//Check base inventory for a spraycan
				bool foundone = false;
				string gottaCan = gimmeASprayCan(graffiti[s]);
				if (len(gottaCan)) {
					foundone = true;
					addstrAlt(CONST_X_GRABBED_A_, gamelog);
					addstrAlt(gottaCan, gamelog);
					addstrAlt(CONST_X_FROM_, gamelog);
					addstrAlt(LocationsPool::getInstance().getLocationName(graffiti[s]->base)); //TODO: Explicitly log it, or will the game log it?
					addstrAlt(singleDot, gamelog);
					pressAnyKey();
				}

				if (!foundone && ledger.get_funds() >= 20)
				{
					ledger.subtract_funds(20, EXPENSE_SHOPPING);
					addstrAlt(CONST_X_BOUGHT_SPRAYPAINT_FOR_GRAFFITI, gamelog);
					pressAnyKey();
					buyMeASprayCan(graffiti[s]);
				}
				else if (!foundone)
				{
					addstrAlt(CONST_X_NEEDS_A_SPRAYCAN_EQUIPPED_TO_DO_GRAFFITI, gamelog);
					graffiti[s]->set_activity_type(ACTIVITY_NONE);
					pressAnyKey();
				}
				gamelog.nextMessage(); //Next message now so that we don't have to type it for every case.
			}
			int issue = VIEW_LIBERALCRIMESQUAD, power = 1;
			if (clearformess) eraseAlt();
			else makedelimiter();
			if (!LCSrandom(10) &&
				!(graffiti[s]->skill_check(SKILL_STREETSENSE, DIFFICULTY_AVERAGE)))
			{
				if (clearformess) eraseAlt();
				else makedelimiter();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, graffiti[s]->getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_WAS_SPOTTED_BY_THE_POLICE, gamelog);
				criminalize(*graffiti[s], LAWFLAG_VANDALISM);
				graffiti[s]->train(SKILL_STREETSENSE, 20);
				if (graffiti[s]->activity_arg() != -1)
				{
					addstrAlt(CONST_X_WHILE_WORKING_ON_THE_MURAL, gamelog);
					graffiti[s]->setactivityargNegativeOne();
				}
				else addstrAlt(CONST_X_WHILE_SPRAYING_AN_LCS_TAG, gamelog);
				gamelog.nextMessage();
				Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
				ns->type = NEWSSTORY_GRAFFITIARREST;
				ns->loc = -1;
				ns->positive = 0;
				newsstory.push_back(ns);
				sitestory = ns;
				pressAnyKey();
				attemptarrest(*graffiti[s], NULL, clearformess);
			}
			else if (graffiti[s]->activity_arg() != -1)
			{
				power = 0;
				if (!LCSrandom(3))
				{
					issue = graffiti[s]->activity_arg();
					power = graffiti[s]->skill_roll(SKILL_ART) / 3;
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(8, 1, graffiti[s]->getNameAndAlignment().name, gamelog);
					addstrAlt(CONST_X_HAS_COMPLETED_A, gamelog);
					if (power > 3)addstrAlt(CONST_X_BEAUTIFUL, gamelog);
					addstrAlt(CONST_X_MURAL_ABOUT_, gamelog);
					addstrAlt(getview(issue, false), gamelog);
					addstrAlt(singleDot, gamelog);
					gamelog.nextMessage();
					graffiti[s]->setactivityargNegativeOne();
					addjuice(*graffiti[s], power, power * 20);
					change_public_opinion(issue, power);
					graffiti[s]->train(SKILL_ART, max(10 - graffiti[s]->get_skill(SKILL_ART) / 2, 1));
					pressAnyKey();
				}
				else
				{
					power = 0;
					set_color_easy(WHITE_ON_BLACK_BRIGHT);
					mvaddstrAlt(8, 1, graffiti[s]->getNameAndAlignment().name, gamelog);
					addstrAlt(CONST_X_WORKS_THROUGH_THE_NIGHT_ON_A_LARGE_MURAL, gamelog);
					gamelog.nextMessage();
					graffiti[s]->train(SKILL_ART, max(10 - graffiti[s]->get_skill(SKILL_ART) / 2, 1));
					pressAnyKey();
				}
			}
			else if (!LCSrandom(max(30 - graffiti[s]->get_skill(SKILL_ART) * 2, 5)))
			{
				issue = randomissue();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, graffiti[s]->getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_HAS_BEGUN_WORK_ON_A_LARGE_MURAL_ABOUT_, gamelog);
				addstrAlt(getview(issue, false), gamelog);
				addstrAlt(singleDot, gamelog);
				gamelog.nextMessage();
				graffiti[s]->setactivityarg(issue);
				power = 0;
				graffiti[s]->train(SKILL_ART, max(10 - graffiti[s]->get_skill(SKILL_ART) / 2, 1));
				pressAnyKey();
			}
			graffiti[s]->train(SKILL_ART, max(4 - graffiti[s]->get_skill(SKILL_ART), 0));
			if (issue == VIEW_LIBERALCRIMESQUAD)
			{
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, LCSrandom(2), 0, 65);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, !LCSrandom(8), 0, 65);
				public_interest[issue] += power;
			}
			else
			{
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, LCSrandom(2) + 1, 0, 85);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, !LCSrandom(4), 0, 65);
				public_interest[issue] += power;
				background_liberal_influence[issue] += power;
			}
		}
	}
}
void doActivityProstitution(vector<DeprecatedCreature *> &prostitutes, char &clearformess)
{
	for (int p = len(prostitutes) - 1; p >= 0; p--)
	{
		// Business once every three days or so
		if (LCSrandom(3)) continue;
		//char num[20];
		long fundgain = 0;
		char caught = 0;
		// Skill determies how much money you get
		int performance = prostitutes[p]->skill_roll(SKILL_SEDUCTION);
		if (performance > DIFFICULTY_HEROIC)
			fundgain = LCSrandom(201) + 200;
		else
			fundgain = LCSrandom(10 * performance) + 10 * performance;
		// Street sense check or deal with slimy people that reduce dignity and juice
		if (!LCSrandom(3) &&
			!(prostitutes[p]->skill_check(SKILL_STREETSENSE, DIFFICULTY_AVERAGE)))
		{
			addjuice(*prostitutes[p], -!LCSrandom(3), -20);
		}
		// Gain seduction and street sense
		prostitutes[p]->train(SKILL_SEDUCTION, max(10 - prostitutes[p]->get_skill(SKILL_SEDUCTION), 0));
		prostitutes[p]->train(SKILL_STREETSENSE, max(10 - prostitutes[p]->get_skill(SKILL_STREETSENSE), 0));
		if (!LCSrandom(50)) // Police sting?
		{
			if (!(prostitutes[p]->skill_check(SKILL_STREETSENSE, DIFFICULTY_AVERAGE))) // Street sense to avoid
			{
				if (clearformess) eraseAlt();
				else makedelimiter();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, prostitutes[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_HAS_BEEN_ARRESTED_IN_A_PROSTITUTION_STING, gamelog);
				gamelog.nextMessage();
				addjuice(*prostitutes[p], -7, -30);
				pressAnyKey();
				caught = 1;
				removesquadinfo(*prostitutes[p]);
				prostitutes[p]->carid = -1;
				prostitutes[p]->location = find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION, prostitutes[p]->location);
				prostitutes[p]->drop_weapons_and_clips(NULL);
				prostitutes[p]->set_activity_type(ACTIVITY_NONE);
				criminalize(*prostitutes[p], LAWFLAG_PROSTITUTION);
			}
			else
			{
				if (clearformess) eraseAlt();
				else makedelimiter();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(8, 1, prostitutes[p]->getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_WAS_NEARLY_CAUGHT_IN_A_PROSTITUTION_STING, gamelog);
				gamelog.nextMessage();
				addjuice(*prostitutes[p], 5, 0);
				pressAnyKey();
			}
		}
		if (!caught)
		{
			prostitutes[p]->train(SKILL_STREETSENSE, max(5 - prostitutes[p]->get_skill(SKILL_STREETSENSE), 0));
			ledger.add_funds(fundgain, INCOME_PROSTITUTION);
			prostitutes[p]->income = fundgain;
		}
	}
}
void doActivityLearn(vector<DeprecatedCreature *> &students, char &clearformess)
{
	for (int s = len(students) - 1; s >= 0; s--)
	{
		if (ledger.get_funds() < 60) break;
		ledger.subtract_funds(60, EXPENSE_TRAINING);
		int skill[2] = { -1, -1 };
		int effectiveness[2] = { 20, 20 };
		skill[0] = trainingActivity[(Activity)(students[s]->activity_type())];
		bool worthcontinuing = false;
		for (int i = 0; i < 2; i++)
			if (skill[i] != -1)
			{  // rapid decrease in effectiveness as your skill gets higher.
				effectiveness[i] /= (students[s]->get_skill(skill[i]) + 1);
				if (effectiveness[i] < 1)
					effectiveness[i] = 1;
				students[s]->train(skill[i], effectiveness[i]);
				if (students[s]->get_skill(skill[i]) < students[s]->skill_cap(skill[i]))
					worthcontinuing = true;
			}
		if (!worthcontinuing)
		{
			students[s]->set_activity_type(ACTIVITY_NONE);
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(8, 1, students[s]->getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_X_HAS_LEARNED_AS_MUCH_AS_, gamelog);
			addstrAlt(students[s]->heshe(), gamelog);
			addstrAlt(CONST_X_CAN, gamelog);
			gamelog.nextMessage();
			pressAnyKey();
		}
	}
}
void finishTrouble(short &crime, long &juiceval, const int mod, const vector<DeprecatedCreature *> trouble) {
	char done = 0;
	do
	{
		switch (LCSrandom(10))
		{
		case 0:
			addstrAlt(CONST_X_RUN_AROUND_UPTOWN_SPLASHING_PAINT_ON_FUR_COATS, gamelog);
			juiceval = 2;
			crime = LAWFLAG_ASSAULT;
			change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
			change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod >> 1, 0, 70);
			public_interest[VIEW_ANIMALRESEARCH] += mod;
			background_liberal_influence[VIEW_ANIMALRESEARCH] += mod;
			done = 1;
			break;
		case 1:
		{
			if (lawList[LAW_GAY] < 2)
			{
				addstrAlt(CONST_X_DISRUPTED_A_TRADITIONAL_WEDDING_AT_A_CHURCH, gamelog);
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
				public_interest[VIEW_GAY] += mod;
				background_liberal_influence[VIEW_GAY] += mod;
				juiceval = 2;
				crime = LAWFLAG_DISTURBANCE;
				done = 1;
			}
			break;
		}
		case 2:
		{
			if (lawList[LAW_ABORTION] < 2)
			{
				addstrAlt(CONST_X_POSTED_HORRIFYING_DEAD_ABORTION_DOCTOR_PICTURES_DOWNTOWN, gamelog);
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
				public_interest[VIEW_WOMEN] += mod;
				background_liberal_influence[VIEW_WOMEN] += mod;
				juiceval = 1;
				done = 1;
			}
			break;
		}
		case 3:
		{
			if (lawList[LAW_POLICEBEHAVIOR] < 2)
			{
				addstrAlt(CONST_X_GONE_DOWNTOWN_AND_REENACTED_A_POLICE_BEATING, gamelog);
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
				public_interest[VIEW_POLICEBEHAVIOR] += mod;
				background_liberal_influence[VIEW_POLICEBEHAVIOR] += mod;
				juiceval = 2;
				crime = LAWFLAG_DISTURBANCE;
				done = 1;
			}
			break;
		}
		case 4:
		{
			if (lawList[LAW_NUCLEARPOWER] < 2)
			{
				if (len(trouble) > 1)addstrAlt(CONST_X_DRESSED_UP_AND_PRETENDED_TO_BE_RADIOACTIVE_MUTANTS, gamelog);
				else addstrAlt(CONST_X_DRESSED_UP_AND_PRETENDED_TO_BE_A_RADIOACTIVE_MUTANT, gamelog);
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
				public_interest[VIEW_NUCLEARPOWER] += mod;
				background_liberal_influence[VIEW_NUCLEARPOWER] += mod;
				juiceval = 2;
				crime = LAWFLAG_DISTURBANCE;
				done = 1;
			}
			break;
		}
		case 5:
		{
			if (lawList[LAW_POLLUTION] < 2)
			{
				addstrAlt(CONST_X_SQUIRTED_BUSINESS_PEOPLE_WITH_FAKE_POLLUTED_WATER, gamelog);
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
				public_interest[VIEW_POLLUTION] += mod;
				background_liberal_influence[VIEW_POLLUTION] += mod;
				juiceval = 2;
				crime = LAWFLAG_DISTURBANCE;
				done = 1;
			}
			break;
		}
		case 6:
		{
			if (lawList[LAW_DEATHPENALTY] < 2)
			{
				addstrAlt(CONST_X_DISTRIBUTED_FLIERS_GRAPHICALLY_ILLUSTRATING_EXECUTIONS, gamelog);
				change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
				public_interest[VIEW_DEATHPENALTY] += mod;
				background_liberal_influence[VIEW_DEATHPENALTY] += mod;
				juiceval = 1;
				done = 1;
			}
			break;
		}
		case 7:
		{
			addstrAlt(CONST_X_DISTRIBUTED_FLIERS_GRAPHICALLY_ILLUSTRATING_CIA_TORTURE, gamelog);
			change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
			change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
			public_interest[VIEW_TORTURE] += mod;
			background_liberal_influence[VIEW_TORTURE] += mod;
			juiceval = 1;
			done = 1;
			break;
		}
		case 8:
		{
			addstrAlt(CONST_X_BURNED_A_CORPORATE_SYMBOL_AND_DENOUNCED_CAPITALISM, gamelog);
			change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
			change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
			public_interest[VIEW_CORPORATECULTURE] += mod;
			background_liberal_influence[VIEW_CORPORATECULTURE] += mod;
			if (lawList[LAW_CORPORATE] == -2)
			{               // In extreme corporate culture cases this should give a flag burning charge! -- kviiri
				juiceval = 2;  // Done -- SlatersQuest
				crime = LAWFLAG_BURNFLAG;
			}
			else juiceval = 1;
			done = 1;
			break;
		}
		case 9:
		{
			addstrAlt(CONST_X_SET_UP_A_MOCK_SWEATSHOP_IN_THE_MIDDLE_OF_THE_MALL, gamelog);
			change_public_opinion(VIEW_LIBERALCRIMESQUAD, mod);
			change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, mod, 0, 70);
			public_interest[VIEW_SWEATSHOPS] += mod;
			background_liberal_influence[VIEW_SWEATSHOPS] += mod;
			juiceval += 1;
			done = 1;
			break;
		}
		}
	} while (!done);
}
void doActivityTrouble(vector<DeprecatedCreature *> &trouble, char &clearformess)
{
	if (len(trouble))
	{
		long juiceval = 0;
		short crime = 0;
		if (clearformess) eraseAlt();
		else makedelimiter();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		moveAlt(8, 1);
		if (len(trouble) > 1) addstrAlt(CONST_X_YOUR_ACTIVISTS_HAVE_, gamelog);
		else { addstrAlt(trouble[0]->getNameAndAlignment().name, gamelog); addstrAlt(CONST_X_HAS_, gamelog); }
		int power = 0;
		for (int t = 0; t < len(trouble); t++)
			power += trouble[t]->skill_roll(SKILL_PERSUASION) +
			trouble[t]->skill_roll(SKILL_STREETSENSE);
		int mod = 1;
		if (LCSrandom(10) < power) mod++;
		if (LCSrandom(20) < power) mod++;
		if (LCSrandom(40) < power) mod++;
		if (LCSrandom(60) < power) mod++;
		if (LCSrandom(80) < power) mod++;
		if (LCSrandom(100) < power) mod++;

		finishTrouble(crime, juiceval, mod, trouble);

		gamelog.nextMessage(); //Do this now so that it doesn't have to be done in every case up there.
		pressAnyKey();
		if (crime != 0)
		{
			for (int t = 0; t < len(trouble); t++)
			{
				if (!LCSrandom(30) &&
					!(trouble[t]->skill_check(SKILL_STREETSENSE, DIFFICULTY_AVERAGE)))
				{
					if (clearformess) eraseAlt();
					else makedelimiter();
					if (!LCSrandom(4))
					{
						Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
						ns->type = NEWSSTORY_WANTEDARREST; // should probably create a NEWSSTORY_TROUBLEARREST and implement it fully
						ns->loc = -1;                      // but this will have to do for now
						ns->positive = 0;
						newsstory.push_back(ns);
						sitestory = ns;
						attemptarrest(*trouble[t], CONST_X_CAUSING_TROUBLE.c_str(), clearformess);
					}
					else
					{
						set_color_easy(WHITE_ON_BLACK_BRIGHT);
						mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
						addstrAlt(CONST_X_IS_CORNERED_BY_A_MOB_OF_ANGRY_REDNECKS, gamelog);
						gamelog.nextMessage();
						pressAnyKey();
						bool wonfight = false;
						if (trouble[t]->get_weapon().get_specific_bool(BOOL_THREATENING_))
						{
							if (clearformess) eraseAlt();
							else makedelimiter();
							set_color_easy(WHITE_ON_BLACK_BRIGHT);
							mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
							addstrAlt(CONST_X_BRANDISHES_THE_, gamelog);
							addstrAlt(trouble[t]->get_weapon().get_name(), gamelog);
							addstrAlt(CONST_X_EXCLAMATION_POINT, gamelog);
							gamelog.nextMessage();
							pressAnyKey();
							if (clearformess) eraseAlt();
							else makedelimiter();
							set_color_easy(WHITE_ON_BLACK_BRIGHT);
							mvaddstrAlt(8, 1, CONST_X_THE_MOB_SCATTERS, gamelog);
							gamelog.nextMessage();
							pressAnyKey();
							addjuice(*trouble[t], 5, 20);
							wonfight = true;
						}
						else
						{
							for (int count = 0; count <= LCSrandom(5) + 2; count++)
							{
								if (clearformess) eraseAlt();
								else makedelimiter();
								if (trouble[t]->skill_roll(SKILL_HANDTOHAND) > LCSrandom(6) + count)
								{
									set_color_easy(CYAN_ON_BLACK_BRIGHT);
									mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
									addstrAlt(singleSpace, gamelog);
									addstrAlt(pickrandom(win_hand_to_hand), gamelog);
									gamelog.nextMessage();
									pressAnyKey();
									wonfight = true;
								}
								else
								{
									set_color_easy(YELLOW_ON_BLACK_BRIGHT);
									mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
									addstrAlt(singleSpace, gamelog);
									addstrAlt(pickrandom(lose_hand_to_hand), gamelog);
									gamelog.nextMessage();
									pressAnyKey();
									count++; // fight goes faster when you're losing
									wonfight = false;
								}
							}
							if (wonfight)
							{
								if (clearformess) eraseAlt();
								else makedelimiter();
								set_color_easy(GREEN_ON_BLACK_BRIGHT);
								mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
								addstrAlt(CONST_X_BEAT_THE, gamelog);
								if (lawList[LAW_FREESPEECH] == -2)
									addstrAlt(CONST_X_TAR, gamelog);
								else addstrAlt(CONST_X_SHIT, gamelog);
								addstrAlt(CONST_X_OUT_OF_EVERYONE_WHO_GOT_CLOSE, gamelog);
								gamelog.nextMessage();
								pressAnyKey();
								addjuice(*trouble[t], 30, 300);
								if (trouble[t]->blood > 70)trouble[t]->blood = 70;
							}
						}
						if (!wonfight)
						{
							if (clearformess) eraseAlt();
							else makedelimiter();
							set_color_easy(RED_ON_BLACK_BRIGHT);
							mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
							addstrAlt(CONST_X_IS_SEVERELY_BEATEN_BEFORE_THE_MOB_IS_BROKEN_UP, gamelog);
							gamelog.nextMessage();
							trouble[t]->set_activity_type(ACTIVITY_CLINIC);
							pressAnyKey();
							addjuice(*trouble[t], -10, -50);
							if (trouble[t]->blood > 10)trouble[t]->blood = 10;
							if (!LCSrandom(5))
							{
								if (clearformess) eraseAlt();
								else makedelimiter();
								switch (LCSrandom(10))
								{
								case 0:
									if (trouble[t]->special[SPECIALWOUND_LOWERSPINE] == 1)
									{
										mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
										addstrAlt(CONST_X_S_LOWER_SPINE_HAS_BEEN_BROKEN, gamelog);
										gamelog.nextMessage();
										trouble[t]->special[SPECIALWOUND_LOWERSPINE] = 0;
										pressAnyKey();
									}
									break;
								case 1:
									if (trouble[t]->special[SPECIALWOUND_UPPERSPINE] == 1)
									{
										mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
										addstrAlt(CONST_X_S_UPPER_SPINE_HAS_BEEN_BROKEN, gamelog);
										gamelog.nextMessage();
										trouble[t]->special[SPECIALWOUND_UPPERSPINE] = 0;
										pressAnyKey();
									}
									break;
								case 2:
									if (trouble[t]->special[SPECIALWOUND_NECK] == 1)
									{
										mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name, gamelog);
										addstrAlt(CONST_X_S_NECK_HAS_BEEN_BROKEN, gamelog);
										gamelog.nextMessage();
										trouble[t]->special[SPECIALWOUND_NECK] = 0;
										pressAnyKey();
									}
									break;
								case 3:
									if (trouble[t]->special[SPECIALWOUND_TEETH] > 0)
									{
										mvaddstrAlt(8, 1, trouble[t]->getNameAndAlignment().name);
										if (trouble[t]->special[SPECIALWOUND_TEETH] > 1)addstrAlt(CONST_X_S_TEETH_HAVE_BEEN_SMASHED_OUT_ON_THE_CURB, gamelog);
										else addstrAlt(CONST_X_S_TOOTH_HAS_BEEN_PULLED_OUT_WITH_PLIERS, gamelog);
										gamelog.nextMessage();
										trouble[t]->special[SPECIALWOUND_TEETH] = 0;
										pressAnyKey();
									}
									break;
								default:
								{
									if (trouble[t]->special[SPECIALWOUND_RIBS] > 0)
									{
										int ribminus = LCSrandom(RIBNUM) + 1;
										if (ribminus > trouble[t]->special[SPECIALWOUND_RIBS])ribminus = trouble[t]->special[SPECIALWOUND_RIBS];
										moveAlt(8, 1);
										if (ribminus > 1)
										{
											if (ribminus == trouble[t]->special[SPECIALWOUND_RIBS])
												addstrAlt(CONST_X_ALL_SPACE, gamelog);
											addstrAlt(ribminus, gamelog);
											addstrAlt(CONST_X_OF_, gamelog);
											addstrAlt(trouble[t]->getNameAndAlignment().name, gamelog);
											addstrAlt(CONST_X_S_RIBS_ARE_, gamelog);
										}
										else if (trouble[t]->special[SPECIALWOUND_RIBS] > 1)
										{
											addstrAlt(CONST_X_ONE_OF_, gamelog);
											addstrAlt(trouble[t]->getNameAndAlignment().name, gamelog);
											addstrAlt(CONST_X_S_RIB_IS_, gamelog);
										}
										else
										{
											addstrAlt(trouble[t]->getNameAndAlignment().name);
											addstrAlt(CONST_X_S_LAST_UNBROKEN_RIB_IS_, gamelog);
										}
										addstrAlt(CONST_X_BROKEN, gamelog);
										gamelog.nextMessage();
										pressAnyKey();
										trouble[t]->special[SPECIALWOUND_RIBS] -= ribminus;
									}
									break;
								}
								}
							}
						}
					}
				}
			}
		}
		for (int h = 0; h < len(trouble); h++)
			addjuice(*trouble[h], juiceval, 40);
	}
}
void doActivityTeach(vector<DeprecatedCreature *> &teachers, char &clearformess)
{
	for (int t = 0; t < len(teachers); t++)
	{
		int skillarray[14];
		int cost = 0, students = 0;
		//Build a list of skills to train and determine the cost for running
		//a class depending on what the teacher is teaching
		switch (teachers[t]->activity_type())
		{
		case ACTIVITY_TEACH_POLITICS:
			cost = 2;
			skillarray[0] = SKILL_LAW;
			skillarray[1] = SKILL_PERSUASION;
			skillarray[2] = SKILL_WRITING;
			skillarray[3] = SKILL_RELIGION;
			skillarray[4] = SKILL_BUSINESS;
			skillarray[5] = SKILL_SCIENCE;
			skillarray[6] = SKILL_STREETSENSE;
			skillarray[7] = SKILL_MUSIC;
			skillarray[8] = SKILL_ART;
			skillarray[9] = -1;
			break;
		case ACTIVITY_TEACH_COVERT:
			cost = 6;
			skillarray[0] = SKILL_SECURITY;
			skillarray[1] = SKILL_COMPUTERS;
			skillarray[2] = SKILL_DISGUISE;
			skillarray[3] = SKILL_TAILORING;
			skillarray[4] = SKILL_STEALTH;
			skillarray[5] = SKILL_SEDUCTION;
			skillarray[6] = SKILL_PSYCHOLOGY;
			skillarray[7] = SKILL_DRIVING;
			skillarray[8] = -1;
			break;
		case ACTIVITY_TEACH_FIGHTING:
			cost = 10;
			skillarray[0] = SKILL_KNIFE;
			skillarray[1] = SKILL_SWORD;
			skillarray[2] = SKILL_CLUB;
			skillarray[3] = SKILL_PISTOL;
			skillarray[4] = SKILL_RIFLE;
			skillarray[5] = SKILL_SHOTGUN;
			skillarray[6] = SKILL_HEAVYWEAPONS;
			skillarray[7] = SKILL_AXE;
			skillarray[8] = SKILL_SMG;
			skillarray[9] = SKILL_THROWING;
			skillarray[10] = SKILL_HANDTOHAND;
			skillarray[11] = SKILL_DODGE;
			skillarray[12] = SKILL_FIRSTAID;
			skillarray[13] = -1;
			break;
		}
		//Count potential students for this teacher to get an idea of efficiency
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			//If they're at the location
			if (pool[p]->location == teachers[t]->location &&
				pool[p]->align == ALIGN_LIBERAL &&
				pool[p]->getNameAndAlignment().alive)
			{
				//Step through the array of skills to train
				for (int i = 0; i < 13; i++)           //Any reason why we aren't using a while(true) loop or something even more dynamic? --kviiri
				{
					//If no more skills to train, stop
					if (skillarray[i] == -1) break;
					//Otherwise, if the student has less skill than the teacher, train the student
					//proportional to the difference in skill between teacher and student times the
					//teacher's ability at teaching
					if (pool[p]->get_skill(skillarray[i]) < teachers[t]->get_skill(skillarray[i]) - 1 &&
						pool[p]->get_skill(skillarray[i]) < teachers[t]->get_skill(SKILL_TEACHING) + 2 &&
						pool[p]->get_skill(skillarray[i]) < pool[p]->skill_cap(skillarray[i]))
					{
						students++;
					}
				}
			}
		}
		//Check funds.
		if (ledger.get_funds() < min(students, 10)*cost)
			continue; //Can't afford to teach them. Continue with next teacher.
					  //Walk through and train people
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			//If they're at the location
			if (pool[p]->location == teachers[t]->location &&
				pool[p]->align == ALIGN_LIBERAL &&
				pool[p]->getNameAndAlignment().alive)
			{
				//Step through the array of skills to train
				for (int i = 0; i < 13; i++)
				{
					//If no more skills to train, stop
					if (skillarray[i] == -1)break;
					//Otherwise, if the student has less skill than the teacher, train the student
					//proportional to the difference in skill between teacher and student times the
					//teacher's ability at teaching
					if (pool[p]->get_skill(skillarray[i]) < teachers[t]->get_skill(skillarray[i]) - 1 &&
						pool[p]->get_skill(skillarray[i]) < teachers[t]->get_skill(SKILL_TEACHING) + 2 &&
						pool[p]->get_skill(skillarray[i]) < pool[p]->skill_cap(skillarray[i]))
					{
						// Teach based on teacher's skill in the topic plus skill in teaching, minus
						// student's skill in the topic
						int teach = teachers[t]->get_skill(skillarray[i]) +
							teachers[t]->get_skill(SKILL_TEACHING) -
							pool[p]->get_skill(skillarray[i]);
						//at ten students, cost no longer goes up, but effectiveness goes down.
						if (students > 10)
						{
							//teach = (teach * 10) / students; //teach at 50% speed with twice as many students.
							teach = ((teach * 30 / students) + teach) / 4; //62.5% speed with twice as many students.
						}
						if (teach < 1)
							teach = 1;
						// Cap at 10 points per day
						if (teach > 10)
							teach = 10;
						pool[p]->train(skillarray[i], teach);
						/*if(students<10)
						{
						students++;
						ledger.subtract_funds(cost,EXPENSE_TRAINING);
						if(students==10)cost=0;
						}*/
					}
				}
			}
		}
		ledger.subtract_funds(cost*min(students, 10), EXPENSE_TRAINING);
		teachers[t]->train(SKILL_TEACHING, min(students, 10));
	}
}
void doActivityBury(vector<DeprecatedCreature *> &bury, char &clearformess)
{
	if (len(bury))
	{
		for (int p = CreaturePool::getInstance().lenpool() - 1; p >= 0; p--)
		{
			if (pool[p]->getNameAndAlignment().alive) continue;
			bool arrest_attempted = false;
			// strip corpse's inventory
			pool[p]->makeloot(bury[0]->base);

			for (int b = 0; b < len(bury); b++)
			{
				if (!arrest_attempted && !(bury[b]->skill_check(SKILL_STREETSENSE, DIFFICULTY_EASY)))
				{
					arrest_attempted = true; // Only attempt one burial arrest per body
					Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
					ns->type = NEWSSTORY_BURIALARREST;
					ns->loc = -1;
					newsstory.push_back(ns);
					sitestory = ns;
					criminalize(*bury[b], LAWFLAG_BURIAL);
					char str[100];
					strcpy(str, CONST_X_BURYING_.c_str());
					strcat(str, pool[p]->getNameAndAlignment().name.data());
					strcat(str, CONST_X_S_BODY.c_str());
					attemptarrest(*bury[b], str, clearformess);
					// If a liberal is spotted they should not do more burials.
					bury.erase(bury.begin() + b--);
					break;
				}
			}
			//BURY (even if interrupted)
			delete_and_remove(pool, p);
			if (!len(bury)) break; //Stop burials if none are left doing them.
		}
	}
}
int lenVehicleType();
int steal_difficultytofind(const int v);
string vehicleTypelongname(const int p);
bool carselect(DeprecatedCreature &cr, short &cartype)
{
	cartype = -1;
	vector<int> cart;
	for (int a = 0; a < lenVehicleType(); a++)
		if (steal_difficultytofind(a) < 10) cart.push_back(a);
	int page = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, CONST_X_WHAT_TYPE_OF_CAR_WILL_);
		addstrAlt(cr.getNameAndAlignment().name);
		addstrAlt(CONST_X_TRY_TO_FIND_AND_STEAL_TODAY);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(1, 0, CONST_X_TYPEDIFFICULTY_TO_FIND_UNATTENDED);
		int y = 2;
		for (int p = page * 19; p < len(cart) && p < page * 19 + 19; p++)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 0);
			addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(vehicleTypelongname(cart[p]));
			moveAlt(y++, 49);
			displayDifficulty(steal_difficultytofind(cart[p]));
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, CONST_X_PRESS_A_LETTER_TO_SELECT_A_TYPE_OF_CAR);
		mvaddstrAlt(23, 0, addpagestr());
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(cart)) page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + c - 'a';
			if (p < len(cart))
			{
				cartype = cart[p];
				return true;
			}
		}
		// Too easy to accidentally back out
		// Not a big problem if this page isn't skippable
		// (There's no immediate risk in picking a car)
		// - JDS
		//if(c=='x'||c==ENTER||c==ESC||c==SPACEBAR)break;
	}
	return false;
}

void observeAlarm(const bool sensealarm, const bool alarmon, const string name, const string carname) {
	if (alarmon)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		moveAlt(10, 0);
		if (sensealarm)addstrAlt(CONST_X_THE_VIPER);
		else addstrAlt(carname);
		addstrAlt(CONST_X_COLON_SPACE_SPACE);
		set_color_easy(RED_ON_BLACK_BRIGHT);
		if (sensealarm)addstrAlt(CONST_X_STAND_AWAY_FROM_THE_VEHICLE_BEEP_BEEP);
		else addstrAlt(CONST_X_BEEP_BEEP_BEEP_BEEP);
	}
	else if (sensealarm)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(10, 0, CONST_X_THE_VIPER_COLON);
		set_color_easy(RED_ON_BLACK_BRIGHT);
		addstrAlt(CONST_X_THIS_IS_THE_VIPER_STAND_AWAY, gamelog);
		gamelog.nextMessage();
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(10, 0, name, gamelog);
		addstrAlt(CONST_X_STANDS_BY_THE_, gamelog);
		addstrAlt(carname, gamelog);
		addstrAlt(singleDot, gamelog);
		gamelog.nextMessage();
	}
}
bool enterCar(DeprecatedCreature &cr, const bool sensealarm, bool &alarmon, string carname, const bool touchalarm, char &windowdamage) {
	for (bool entered = false; !entered;)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, CONST_X_ADVENTURES_IN_LIBERAL_CAR_THEFT);
		printcreatureinfo(&cr);
		makedelimiter();

		observeAlarm(sensealarm != 0, alarmon, cr.getNameAndAlignment().name, carname);

		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(12, 0, CONST_X_A_PICK_THE_LOCK);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(13, 0, CONST_X_B_BREAK_THE_WINDOW);
		moveAlt(14, 0);

		addstrAlt(considerLeaving(sensealarm, alarmon, cr.getNameAndAlignment().name));

		char method = -1;
		while (method == -1)
		{
			int c = getkeyAlt();
			if (c == 'a')method = 0;
			if (c == 'b')method = 1;
			if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) { return false; } /* try again tomorrow */
		}
		//PICK LOCK
		if (method == 0)
		{
			if (cr.skill_check(SKILL_SECURITY, DIFFICULTY_AVERAGE))
			{
				switch (fieldskillrate)
				{
				case FIELDSKILLRATE_FAST:
					cr.train(SKILL_SECURITY, 25); break;
				case FIELDSKILLRATE_CLASSIC:
					cr.train(SKILL_SECURITY, max(5 - cr.get_skill(SKILL_SECURITY), 0)); break;
				case FIELDSKILLRATE_HARD:
					cr.train(SKILL_SECURITY, 0); break;
				}
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 0, cr.getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_JIMMIES_THE_CAR_DOOR_OPEN, gamelog);
				gamelog.nextMessage();
				pressAnyKey();
				entered = true;
			}
			else
			{
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 0, cr.getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_FIDDLES_WITH_THE_LOCK_WITH_NO_LUCK, gamelog);
				gamelog.nextMessage();
				pressAnyKey();
			}
		}
		//BREAK WINDOW
		if (method == 1)
		{
			int difficulty = static_cast<int>(DIFFICULTY_EASY / cr.get_weapon().get_bashstrengthmod()) - windowdamage;
			if (cr.attribute_check(ATTRIBUTE_STRENGTH, difficulty))
			{
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 0, cr.getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_SMASHES_THE_WINDOW, gamelog);
				if (cr.get_weapon().get_bashstrengthmod() > 1)
				{
					addstrAlt(CONST_X_WITH_A_, gamelog);
					addstrAlt(cr.get_weapon().get_name(2), gamelog);
				}
				addstrAlt(singleDot, gamelog);
				gamelog.nextMessage();
				windowdamage = 10;
				pressAnyKey();
				entered = true;
			}
			else
			{
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(16, 0, cr.getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_CRACKS_THE_WINDOW, gamelog);
				if (cr.get_weapon().get_bashstrengthmod() > 1)
				{
					addstrAlt(CONST_X_WITH_A_, gamelog);
					addstrAlt(cr.get_weapon().get_name(2), gamelog);
				}
				addstrAlt(CONST_X_BUT_IT_IS_STILL_SOMEWHAT_INTACT, gamelog);
				gamelog.nextMessage();
				windowdamage++;
				pressAnyKey();
			}
		}
		//ALARM CHECK
		int y = 17;
		if (touchalarm || sensealarm)
		{
			if (!alarmon)
			{
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				mvaddstrAlt(y++, 0, CONST_X_AN_ALARM_SUDDENLY_STARTS_BLARING, gamelog);
				gamelog.nextMessage();
				pressAnyKey();
				alarmon = true;
			}
		}
		//NOTICE CHECK
		if (!LCSrandom(50) || (!LCSrandom(5) && alarmon))
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			mvaddstrAlt(y++, 0, cr.getNameAndAlignment().name, gamelog);
			addstrAlt(CONST_X_HAS_BEEN_SPOTTED_BY_A_PASSERBY, gamelog);
			gamelog.nextMessage();
			pressAnyKey();
			//FOOT CHASE
			chaseseq.clean();
			chaseseq.location = LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONPARENT,cr.location);
			Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
			ns->type = NEWSSTORY_CARTHEFT;
			newsstory.push_back(ns);
			sitestory = ns;
			makechasers(-1, 5);
			if (footchase(cr)) {
				mode = GAMEMODE_BASE;
				return false;
			} // Switched to return false; this will cause you to try again tomorrow
			else {
				mode = GAMEMODE_BASE;
				return false;
			}
		}
	}
	return true;
}

bool attempt_find_keys(const bool keys_in_car, const int key_location, const int key_search_total, int& y, DeprecatedCreature &cr) {
	bool started = false;
	int difficulty;
	string location;
	if (!keys_in_car)
	{
		difficulty = DIFFICULTY_IMPOSSIBLE;
		location = CONST_X_IN_SPACE_WITH_ALIENS_SERIOUSLY;
	}
	else switch (key_location)
	{
	case 0:
	default:
		difficulty = DIFFICULTY_AUTOMATIC;
		location = CONST_X_IN_THE_IGNITION_DAMN;
		break;
	case 1:
		difficulty = DIFFICULTY_EASY;
		location = CONST_X_ABOVE_THE_PULLDOWN_SUNBLOCK_THINGY;
		break;
	case 2:
		difficulty = DIFFICULTY_EASY;
		location = CONST_X_IN_THE_GLOVE_COMPARTMENT;
		break;
	case 3:
		difficulty = DIFFICULTY_AVERAGE;
		location = CONST_X_UNDER_THE_FRONT_SEAT;
		break;
	case 4:
		difficulty = DIFFICULTY_HARD;
		location = CONST_X_UNDER_THE_BACK_SEAT;
		break;
	}
	if (cr.attribute_check(ATTRIBUTE_INTELLIGENCE, difficulty))
	{
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		moveAlt(y++, 0);
		if (lawList[LAW_FREESPEECH] == -2)addstrAlt(CONST_X_HOLY_CAR_KEYS_, gamelog); // Holy car keys Batman!
		else addstrAlt(CONST_X_HOLY_SHIT_, gamelog);
		addstrAlt(cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_FOUND_THE_KEYS, gamelog);
		addstrAlt(location, gamelog);
		started = true;
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(y++, 0, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_RUMMAGING_, gamelog);
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		if (key_search_total == 5)
			addstrAlt(CONST_X_ARE_THEY_EVEN_IN_HERE, gamelog);
		else if (key_search_total == 10)
			addstrAlt(CONST_X_I_DONT_THINK_THEYRE_IN_HERE, gamelog);
		else if (key_search_total == 15)
			addstrAlt(CONST_X_IF_THEY_WERE_HERE_ID_HAVE_FOUND_THEM_BY_NOW, gamelog);
		else if (key_search_total > 15)
		{
			addstrAlt(pickrandom(car_wont_start), gamelog);
		}
		else
		{
			if (lawList[LAW_FREESPEECH] == -2) {
				addstrAlt(pickrandom(cant_find_keys_no_free_speech));
			}
			else {
				addstrAlt(pickrandom(cant_find_keys));
			}
		}
	}
	return started;
}
bool startCar(DeprecatedCreature &cr, const string carname, const bool alarmon, const bool sensealarm) {
	char keys_in_car = LCSrandom(5) > 0, key_search_total = 0;
	int key_location = LCSrandom(5), nervous_counter = 0;





	bool started = false;
	while (!started)
	{
		nervous_counter++;
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, CONST_X_ADVENTURES_IN_LIBERAL_CAR_THEFT);
		printcreatureinfo(&cr);
		makedelimiter();
		int y = 10;
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(y++, 0, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_IS_BEHIND_THE_WHEEL_OF_A_, gamelog);
		addstrAlt(carname, gamelog);
		addstrAlt(singleDot, gamelog);
		gamelog.nextMessage();
		if (alarmon)
		{
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			moveAlt(y++, 0);
			if (sensealarm)addstrAlt(CONST_X_THE_VIPER);
			else addstrAlt(carname);
			addstrAlt(CONST_X_COLON_SPACE_SPACE);
			set_color_easy(RED_ON_BLACK_BRIGHT);
			if (sensealarm)addstrAlt(CONST_X_REMOVE_YOURSELF_FROM_THE_VEHICLE_BEEP_BEEP);
			else addstrAlt(CONST_X_BEEP_BEEP_BEEP_BEEP);
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt((++y)++, 0, CONST_X_A_HOTWIRE_THE_CAR);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(y++, 0, CONST_X_B_DESPERATELY_SEARCH_FOR_KEYS);
		moveAlt(y++, 0);
		if (!sensealarm)addstrAlt(CONST_CALL_IT_A_DAY_PRESS_ENTER);
		else { addstrAlt(CONST_X_ENTER_THE_VIPER_HAS_FINALLY_DETERRED_); addstrAlt(cr.getNameAndAlignment().name); addstrAlt(singleDot); }
		y++;
		CarHotwireMethod method = UNDETERMINED;
		while (method == UNDETERMINED)
		{
			int c = getkeyAlt();
			if (c == 'a') method = ATTEMPT_HOTWIRE;
			if (c == 'b') method = USE_KEYS;
			if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) { return false; } // Call it a day and try again tomorrow
		}
		//HOTWIRE CAR
		if (method == ATTEMPT_HOTWIRE)
		{
			if (cr.skill_check(SKILL_SECURITY, DIFFICULTY_CHALLENGING))
			{
				switch (fieldskillrate)
				{
				case FIELDSKILLRATE_FAST:
					cr.train(SKILL_SECURITY, 50); break;
				case FIELDSKILLRATE_CLASSIC:
					cr.train(SKILL_SECURITY, max(10 - cr.get_skill(SKILL_SECURITY), 0)); break;
				case FIELDSKILLRATE_HARD:
					cr.train(SKILL_SECURITY, 0); break;
				}
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(y++, 0, cr.getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_HOTWIRES_THE_CAR, gamelog);
				gamelog.nextMessage();
				pressAnyKey();
				started = true;
			}
			else
			{
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				mvaddstrAlt(y++, 0, cr.getNameAndAlignment().name, gamelog);
				int flavor_text;
				if (cr.get_skill(SKILL_SECURITY) < 4)
					addstrAlt(pickrandom(cant_hotwire_car));
				else {
					if (LCSrandom(cant_hotwire_car.size() + almost_hotwire_car.size()) >= cant_hotwire_car.size()) {
						addstrAlt(pickrandom(almost_hotwire_car));
					}
					else {
						addstrAlt(pickrandom(cant_hotwire_car));
					}
				}
				gamelog.nextMessage();
				pressAnyKey();
			}
		}
		else
			//KEYS
			if (method == USE_KEYS)
			{
				started = attempt_find_keys(keys_in_car, key_location, key_search_total, y, cr);
				if (!started) {
					key_search_total++;
				}
				gamelog.nextMessage();
				pressAnyKey();
			}
			else {
				// ERROR
				// currently no other method
			}
			//NOTICE CHECK
			if (!started && (!LCSrandom(50) || (!LCSrandom(5) && alarmon)))
			{
				set_color_easy(RED_ON_BLACK_BRIGHT);
				mvaddstrAlt(y++, 0, cr.getNameAndAlignment().name, gamelog);
				addstrAlt(CONST_X_HAS_BEEN_SPOTTED_BY_A_PASSERBY, gamelog);
				gamelog.nextMessage();
				pressAnyKey();
				//FOOT CHASE
				chaseseq.clean();
				chaseseq.location = LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONPARENT,cr.location);
				Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
				ns->type = NEWSSTORY_CARTHEFT;
				newsstory.push_back(ns);
				sitestory = ns;
				makechasers(-1, 5);
				if (footchase(cr)) {
					mode = GAMEMODE_BASE;
					return false;
				}
				else {
					mode = GAMEMODE_BASE;
					return false;
				}
			}
			// Nervous message check
			else if (!started && (LCSrandom(7) + 5) < nervous_counter)
			{
				nervous_counter = 0;
				moveAlt(++y, 0); y++;
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				addstrAlt(cr.getNameAndAlignment().name, gamelog);
				addstrAlt(singleSpace, gamelog);
				addstrAlt(pickrandom(gets_nervous), gamelog);
				gamelog.nextMessage();
				pressAnyKey();
			}
	}
	return true;
}

/* steal a car */
bool stealcar(DeprecatedCreature &cr, char &clearformess)
{

	music.play(MUSIC_CARTHEFT);
	clearformess = 1;
	short cartype;
	if (carselect(cr, cartype))
	{
		int diff = steal_difficultytofind(cartype) * 2;
		Vehicle *v = NULL;
		int old = cartype;
		cr.train(SKILL_STREETSENSE, 5);
		//THEFT SEQUENCE
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, CONST_X_ADVENTURES_IN_LIBERAL_CAR_THEFT, gamelog);
		gamelog.nextMessage();
		printcreatureinfo(&cr);
		makedelimiter();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(10, 0, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_LOOKS_AROUND_FOR_AN_ACCESSIBLE_VEHICLE, gamelog);
		pressAnyKey();
		//ROUGH DAY
		if (!cr.skill_check(SKILL_STREETSENSE, diff))
			do cartype = LCSrandom(lenVehicleType());
		while (cartype == old || LCSrandom(10) < steal_difficultytofind(cartype));
		v = getVehicleOfThisType(cartype);
		string carname = v->fullname();
		mvaddstrAlt(11, 0, cr.getNameAndAlignment().name, gamelog);
		if (old != cartype)
		{
			addstrAlt(wasUnableToFind(vehicleTypelongname(old)), gamelog);
		}
		else addstrAlt(CONST_X_FOUND_A, gamelog);
		addstrAlt(v->longname(), gamelog);
		addstrAlt(singleDot, gamelog);
		gamelog.nextMessage();
		pressAnyKey();
		//APPROACH?
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, CONST_X_ADVENTURES_IN_LIBERAL_CAR_THEFT);
		printcreatureinfo(&cr);
		makedelimiter();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(10, 0, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_LOOKS_FROM_A_DISTANCE_AT_AN_EMPTY_, gamelog);
		addstrAlt(carname, gamelog);
		addstrAlt(singleDot, gamelog);
		gamelog.nextMessage();
		mvaddstrAlt(12, 0, CONST_X_A_APPROACH_THE_DRIVERS_SIDE_DOOR);
		mvaddstrAlt(13, 0, CONST_CALL_IT_A_DAY_PRESS_ENTER);
		while (true)
		{
			int c = getkeyAlt();
			if (c == 'a')break;
			if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) { delete v; return false; }
		}
		//SECURITY?
		bool alarmon = false, sensealarm = LCSrandom(100) < v->sensealarmchance(),
			touchalarm = LCSrandom(100) < v->touchalarmchance();
		char windowdamage = 0;
		if (!enterCar(cr, sensealarm, alarmon, carname, touchalarm, windowdamage)) {
			delete v;
			return false;
		}
		//START CAR
		//char ignition_progress=0;
		if (!startCar(cr, carname, alarmon, sensealarm)) {
			delete v;
			return false;
		}
		//CHASE SEQUENCE
		//CAR IS OFFICIAL, THOUGH CAN BE DELETE BY chasesequence()
		addjuice(cr, v->steal_juice(), 100);
		newVehicle(v);
		v->add_heat(14 + v->steal_extraheat());
		v->set_location(cr.base);
		// Automatically assign this car to this driver, if no other one is present
		if (cr.pref_carid == -1)
		{
			cr.pref_carid = v->id();
			cr.pref_is_driver = true;
		}
		chaseseq.clean();
		chaseseq.location = LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONPARENT,cr.location);
		int chaselev = !LCSrandom(13 - windowdamage);
		if (chaselev > 0 || (v->vtypeidname() == tag_POLICECAR && LCSrandom(2))) //Identify police cruiser. Temporary solution? -XML
		{
			v->add_heat(10);
			chaselev = 1;
			Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
			ns->type = NEWSSTORY_CARTHEFT;
			newsstory.push_back(ns);
			sitestory = ns;
			makechasers(-1, chaselev);
			if (!chasesequence(cr, *v)) // Caught or killed in the chase. Do not need to delete vehicle.
				return 0;
		}
		return 1;
	}
	return 0;
}
/* get a wheelchair */
void getwheelchair(DeprecatedCreature &cr, char &clearformess)
{
	if (clearformess) eraseAlt();
	else makedelimiter();
	if (LCSrandom(2))
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 1, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_HAS_PROCURED_A_WHEELCHAIR, gamelog);
		cr.flag |= CREATUREFLAG_WHEELCHAIR;
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(8, 1, cr.getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_X_WAS_UNABLE_TO_GET_A_WHEELCHAIR_MAYBE_TOMORROW, gamelog);
	}
	gamelog.nextMessage();
	pressAnyKey();
}