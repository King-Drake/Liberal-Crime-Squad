

#include "../includes20.h"
#include "../constStringlcsmonthly.h"

const vector<int> viewAnimals = { VIEW_ANIMALRESEARCH, 15 };
const vector<int> viewJustice = { VIEW_JUSTICES, 15 };
const vector<int> viewGay = { VIEW_GAY, 15 };
const vector<int> emptyVector = {};
const vector<int> viewSweatshop = { VIEW_SWEATSHOPS, 10 };
const vector<int> viewGeneticAndPollution = { VIEW_GENETICS, 10, VIEW_POLLUTION, 10 };
const vector< pair<string, vector<int> > > CEOLoveLettersInfluence = {
	std::make_pair(CONST_ADDRESSED_TO_HIS_PET_DOG_YIKES, viewAnimals),
	std::make_pair(CONST_TO_THE_JUDGE_THAT_ACQUIT_HIM_IN_A_CORRUPTION_TRIAL, viewJustice),
	std::make_pair(CONST_TO_AN_ILLICIT_GAY_LOVER, viewGay),
	std::make_pair(CONST_TO_HIMSELF_THEY_RE_VERY_STEAMY, emptyVector),
	std::make_pair(CONST_IMPLYING_THAT_HE_HAS_ENSLAVED_HIS_HOUSESERVANTS, viewSweatshop),
	std::make_pair(CONST_TO_THE_FDA_OFFICIAL_OVERSEEING_THE_CEO_S_PRODUCTS, viewGeneticAndPollution),
	std::make_pair(CONST_THAT_SEEM_TO_TOUCH_ON_EVERY_FETISH_KNOWN_TO_MAN, emptyVector),
	std::make_pair(CONST_PROMISING_SOMEONE_COMPANY_PROFITS_IN_EXCHANGE_FOR_SEXUAL_FAVORS, emptyVector),
};

const vector<int> viewPoliceAndJustice = { VIEW_POLICEBEHAVIOR, 15, VIEW_JUSTICES, 10 };
 const vector< pair<string, vector<int> > > CEOPhotosInfluence  = {
	std::make_pair(CONST_ENGAGING_IN_LEWD_BEHAVIOR_WITH_ANIMALS, viewAnimals),
	std::make_pair(CONST_DIGGING_UP_GRAVES_AND_SLEEPING_WITH_THE_DEAD, emptyVector),
	std::make_pair(CONST_PARTICIPATING_IN_A_MURDER, viewPoliceAndJustice),
	std::make_pair(CONST_ENGAGING_IN_HEAVY_BONDAGE_A_CUCUMBER_WAS_INVOLVED_IN_SOME_WAY, emptyVector),
	std::make_pair(CONST_TONGUE_KISSING_AN_INFAMOUS_DICTATOR, emptyVector),
	std::make_pair(CONST_MAKING_OUT_WITH_AN_FDA_OFFICIAL_OVERSEEING_THE_CEO_S_PRODUCTS, viewGeneticAndPollution),
	std::make_pair(CONST_CASTRATING_HIMSELF, emptyVector),
	std::make_pair(CONST_WAVING_A_NAZI_FLAG_AT_A_SUPREMACIST_RALLY, emptyVector),
	std::make_pair(CONST_TORTURING_AN_EMPLOYEE_WITH_A_HOT_IRON, viewSweatshop),
	std::make_pair(CONST_PLAYING_WITH_FECES_AND_URINE, emptyVector),
};
const vector<int> viewTaxesStrong = { VIEW_TAXES, 25 };
const vector< pair<string, vector<int> > > CEOTaxesInfluence = {
	std::make_pair(CONST_SHOWING_THAT_HE_HAS_ENGAGED_IN_CONSISTENT_TAX_EVASION, viewTaxesStrong),

};

const vector<int> strongGenetics = { VIEW_GENETICS, 50 };
const vector<int> strongGay = { VIEW_GAY, 50 };
const vector<int> strongWomen = { VIEW_WOMEN, 50 };
const vector<int> strongSweat = { VIEW_SWEATSHOPS, 50 };
const vector<int> strongTaxes = { VIEW_TAXES, 50 };
 const vector< pair<string, vector<int> > > CorpFilesInfluence = {
	std::make_pair(CONST_DESCRIBING_A_GENETIC_MONSTER_CREATED_IN_A_LAB, strongGenetics),
	std::make_pair(CONST_WITH_A_LIST_OF_GAY_EMPLOYEES_ENTITLED_HOMO_WORKERS, strongGay),
	std::make_pair(CONST_CONTAINING_A_MEMO_TERMINATE_THE_PREGNANCY_I_TERMINATE_YOU, strongWomen),
	std::make_pair(CONST_CHEERFULLY_DESCRIBING_FOREIGN_CORPORATE_SWEATSHOPS, strongSweat),
	std::make_pair(CONST_DESCRIBING_AN_INTRICATE_TAX_SCHEME, strongTaxes),
};

const vector<int> strongJustice = { VIEW_JUSTICES, 50 };
const vector<int> strongFreeSpeech = { VIEW_FREESPEECH, 50 };
const vector< pair<string, vector<int> > > CIAPapersInfluence = {
	std::make_pair(CONST_DOCUMENTING_THE_OVERTHROW_OF_A_GOVERNMENT, emptyVector),
	std::make_pair(CONST_DOCUMENTING_THE_PLANNED_ASSASSINATION_OF_A_LIBERAL_FEDERAL_JUDGE, strongJustice),
	std::make_pair(CONST_CONTAINING_PRIVATE_INFORMATION_ON_INNOCENT_CITIZENS, emptyVector),
	std::make_pair(CONST_DOCUMENTING_HARMFUL_SPEECH_MADE_BY_INNOCENT_CITIZENS, strongFreeSpeech),
	std::make_pair(CONST_USED_TO_KEEP_TABS_ON_GAY_CITIZENS, strongGay),
	std::make_pair(CONST_DOCUMENTING_THE_INFILTRATION_OF_A_PRO_CHOICE_GROUP, strongWomen),

};


const vector<int> viewTorture = { VIEW_TORTURE , 15 };
const vector<int> strongTorture = { VIEW_TORTURE , 50 };
const vector<int> viewIntelligence = { VIEW_INTELLIGENCE , 15 };
const vector<int> viewDeathPrisons = { VIEW_DEATHPENALTY , 50, VIEW_PRISONS , 20 };
  const vector< pair<string, vector<int> > > PolicePapersInfluence =
{
	std::make_pair(CONST_DOCUMENTING_HUMAN_RIGHTS_ABUSES_BY_THE_FORCE, viewTorture),
	std::make_pair(CONST_DOCUMENTING_A_POLICE_TORTURE_CASE, strongTorture),

	std::make_pair(CONST_DOCUMENTING_A_SYSTEMATIC_INVASION_OF_PRIVACY_BY_THE_FORCE, viewIntelligence),

	std::make_pair(CONST_DOCUMENTING_A_FORCED_CONFESSION, emptyVector),
	std::make_pair(CONST_DOCUMENTING_WIDESPREAD_CORRUPTION_IN_THE_FORCE, emptyVector),

	std::make_pair(CONST_DOCUMENTING_GLADIATORIAL_MATCHES_HELD_BETWEEN_PRISONERS_BY_GUARDS, viewDeathPrisons),

};

const vector< pair<string, vector<int> > > JudgePapersInfluence =
{
	std::make_pair(CONST_TAKING_BRIBES_TO_ACQUIT_MURDERERS, emptyVector),
	std::make_pair(CONST_PROMISING_CONSERVATIVE_RULINGS_IN_EXCHANGE_FOR_APPOINTMENTS, emptyVector),
};


const vector<int> strongAnimals = { VIEW_ANIMALRESEARCH, 50 };

const vector< pair<string, vector<int> > > ResearchPapersInfluence = {
	std::make_pair(CONST_DOCUMENTING_HORRIFIC_ANIMAL_RIGHTS_ABUSES, strongAnimals),
	std::make_pair(CONST_STUDYING_THE_EFFECTS_OF_TORTURE_ON_CATS, strongAnimals),
	std::make_pair(CONST_COVERING_UP_THE_ACCIDENTAL_CREATION_OF_A_GENETIC_MONSTER, strongGenetics),
	std::make_pair(CONST_SHOWING_HUMAN_TEST_SUBJECTS_DYING_UNDER_GENETIC_RESEARCH, strongGenetics),
};

const vector< pair<string, vector<int> > > PrisonPapersInfluence =
{
	std::make_pair(CONST_DOCUMENTING_HUMAN_RIGHTS_ABUSES_BY_PRISON_GUARDS, emptyVector),
	std::make_pair(CONST_DOCUMENTING_A_PRISON_TORTURE_CASE, strongTorture),

	std::make_pair(CONST_DOCUMENTING_WIDESPREAD_CORRUPTION_AMONG_PRISON_EMPLOYEES, emptyVector),
	std::make_pair(CONST_DOCUMENTING_GLADIATORIAL_MATCHES_HELD_BETWEEN_PRISONERS_BY_GUARDS, emptyVector),
};

const vector< pair<string, vector<int> > > CablePapersInfluence  = {
	std::make_pair(CONST_CALLING_THEIR_NEWS_THE_VANGUARD_OF_CONSERVATIVE_THOUGHT, emptyVector),
	std::make_pair(CONST_MANDATING_NEGATIVE_COVERAGE_OF_LIBERAL_POLITICIANS, emptyVector),
	std::make_pair(CONST_PLANNING_TO_DRUM_UP_A_FALSE_SCANDAL_ABOUT_A_LIBERAL_FIGURE, emptyVector),
	std::make_pair(CONST_INSTRUCTING_A_FEMALE_ANCHOR_TO_GET_SEXIER_OR_GET_A_NEW_JOB, emptyVector),

};

const vector< pair<string, vector<int> > > RadioPapersInfluence  =
{
	std::make_pair(CONST_CALLING_LISTENERS_SHEEP_TO_BE_TOLD_WHAT_TO_THINK, emptyVector),
	std::make_pair(CONST_SAYING_IT_S_OKAY_TO_LIE_THEY_DON_T_NEED_THE_TRUTH, emptyVector),
	std::make_pair(CONST_PLANNING_TO_DRUM_UP_A_FALSE_SCANDAL_ABOUT_A_LIBERAL_FIGURE, emptyVector),
};


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
//TODO: Log the monthly report? --Addictgamer
/* monthly - reports the guardian's power to the player */
  void guardianupdate(char size, int power)
  {
	  music.play(MUSIC_NEWSPAPER);
	  eraseAlt();
	  set_color_easy(WHITE_ON_BLACK);
	  moveAlt(5, 2);
	  if (size)
	  {
		  addstrAlt(CONST_THE_MONTHLY_LIBERAL_GUARDIAN_NEWSPAPER, gamelog);
	  }
	  else
	  {
		  addstrAlt(CONST_THE_MONTHLY_LIBERAL_GUARDIAN_ONLINE_NEWSLETTER, gamelog);
	  }
	  addstrAlt(CONST_IS_PUBLISHED, gamelog);
	  gamelog.newline();
	  moveAlt(7, 2);
	  if (power < 0)
	  {
		  addstrAlt(CONST_THE_ONLY_READERS_ARE_CONSERVATIVES_WHO_SEEM_TO_THINK_IT_S_FUNNY, gamelog);
	  }
	  else if (power == 0)
	  {
		  addstrAlt(CONST_UNFORTUNATELY_NOBODY_SEEMS_INTERESTED, gamelog);
	  }
	  else if (power < 5)
	  {
		  addstrAlt(CONST_VERY_FEW_PEOPLE_SEEM_TO_BE_INTERESTED, gamelog);
	  }
	  else if (power < 50)
	  {
		  addstrAlt(CONST_A_FAIR_NUMBER_OF_PEOPLE_ARE_READING_IT, gamelog);
	  }
	  else if (power < 100)
	  {
		  addstrAlt(CONST_MANY_PEOPLE_ARE_READING_IT, gamelog);
	  }
	  else if (power < 250)
	  {
		  addstrAlt(CONST_THE_RESPONSE_IS_VERY_STRONG_PEOPLE_ARE_CHANGING_THEIR_MINDS, gamelog);
	  }
	  else
	  {
		  addstrAlt(CONST_THE_RESPONSE_IS_ELECTRIC_EVERYONE_IS_TALKING_ABOUT_THIS_MONTH_S, gamelog);
		  mvaddstrAlt(8, 2, CONST_X_LIBERAL_GUARDIAN, gamelog);
	  }
	  gamelog.nextMessage();
	  pressAnyKey();
	  return;
  }
  /* monthly - lets the player choose a special edition for the guardian */
  int choosespecialedition(char &clearformess)
  {
	  static const vector<string> dox(document_types, document_types + len(document_types));
	  int page = 0;
	  //char havetype[LOOTNUM];
	  //for(int l=0;l<LOOTNUM;l++)havetype[l]=0;
	  vector<bool> havetype(LootTypePool::getInstance().lenpool(), false);
	  vector<int> loottypeindex;
	  LocationsPool::getInstance().findAllLootTypes(havetype, loottypeindex, dox);
	  constructLootIndices(havetype, loottypeindex, dox);
	  if (!len(loottypeindex)) return -1;
	  clearformess = 1;
	  //PICK ONE
	  while (true)
	  {
		  music.play(MUSIC_NEWSPAPER);
		  eraseAlt();
		  set_color_easy(WHITE_ON_BLACK);
		  mvaddstrAlt(0, 0, CONST_DO_YOU_WANT_TO_RUN_A_SPECIAL_EDITION);
		  int x = 1, y = 10;
		  char str[200];
		  for (int l = page * 18; l < len(loottypeindex) && l < page * 18 + 18; l++)
		  {
			  str[0] = l - page * 18 + 'A';
			  str[1] = '\x0';
			  strcat(str, spaceDashSpace.c_str());
			  strcat(str, LootTypePool::getInstance().getName(LootTypePool::getInstance().getIdName(loottypeindex[l])).c_str());
			  mvaddstrAlt(y, x, str);
			  x += 26;
			  if (x > 53) x = 1, y++;
		  }
		  //PAGE UP
		  if (page > 0)
		  {
			  mvaddstrAlt(17, 1, addprevpagestr());
		  }
		  //PAGE DOWN
		  if ((page + 1) * 18 < LootTypePool::getInstance().lenpool())
		  {
			  mvaddstrAlt(17, 53, addnextpagestr());
		  }
		  mvaddstrAlt(24, 1, CONST_ENTER_NOT_IN_THIS_MONTH_S_LIBERAL_GUARDIAN);
		  int c = getkeyAlt();
		  if (c >= 'a'&&c <= 'r')
		  {
			  int slot = c - 'a' + page * 18;
			  if (slot >= 0 && slot < len(loottypeindex))
			  {
				  // remove item from location
				  int output = LocationsPool::getInstance().deleteSpecialItem(slot, loottypeindex);
				  if (output != -1) {
					  return output;
				  }
				  // if not in location, remove item from squad
				  removeItemFromSquad(loottypeindex[slot]);
				  //WHOOPS!
				  return loottypeindex[slot];
			  }
		  }
		  if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) return -1;
		  //PAGE UP
		  if (is_page_up(c) && page > 0) page--;
		  //PAGE DOWN
		  if (is_page_down(c) && (page + 1) * 18 < LootTypePool::getInstance().lenpool()) page++;
	  }
	  return -1;
  }
  void change_opinion_from_Influence(vector< pair<string, vector<int> > > Influence) {


	  vector<int>::iterator it;
	  int influence = LCSrandom(Influence.size());
	  addstrAlt(Influence[influence].first, gamelog);
	  for (it = Influence[influence].second.begin(); it != Influence[influence].second.end(); it += 2) {
		  change_public_opinion(*it, *(it + 1));
	  }

  }

  void printLootCCSBackers() {

	  mvaddstrAlt(5, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_MORE_THAN_ONE_THOUSAND_PAGES_OF_DOCUMENTS_ABOUT, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(6, 1, CONST_THE_CCS_ORGANIZATION_ALSO_REVEALING_IN_EXTREME_DETAIL_THE_NAMES_AND, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(7, 1, CONST_RESPONSIBILITIES_OF_CONSERVATIVE_CRIME_SQUAD_SYMPATHIZERS_AND_SUPPORTERS, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(8, 1, CONST_IN_THE_STATE_AND_FEDERAL_GOVERNMENTS_SECTIONS_PRECISELY_DOCUMENT_THE, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(9, 1, CONST_EXTENSIVE_PLANNING_TO_CREATE_AN_EXTRA_JUDICIAL_DEATH_SQUAD_THAT_WOULD_BE, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, CONST_ABOVE_PROSECUTION_AND_COULD_HUNT_DOWN_LAW_ABIDING_LIBERALS_AND_ACT, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(11, 1, CONST_AS_A_FOIL_WHEN_NO_OTHER_ENEMIES_WERE_PRESENT_TO_DIRECT_PUBLIC_ENERGY, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(12, 1, CONST_AGAINST, gamelog);
	  mvaddstrAlt(14, 1, CONST_THE_SCANDAL_REACHES_INTO_THE_HEART_OF_THE_CONSERVATIVE_LEADERSHIP_IN_THE, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(15, 1, CONST_COUNTRY_AND_THE_FULL_RAMIFICATIONS_OF_THIS_REVELATION_MAY_NOT_BE_FELT, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(16, 1, CONST_FOR_MONTHS_ONE_THING_IS_CLEAR_HOWEVER_FROM_THE_IMMEDIATE_PUBLIC_REACTION, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(17, 1, CONST_TOWARD_THE_REVELATIONS_AND_THE_SPEED_WITH_WHICH_EVEN_AM_RADIO_AND_CABLE, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(18, 1, CONST_NEWS_DENOUNCE_THE_CCS, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(20, 1, CONST_THIS_IS_THE_BEGINNING_OF_THE_END_FOR_THE_CONSERVATIVE_CRIME_SQUAD, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_INTELLIGENCE, 50);
	  change_public_opinion(VIEW_CONSERVATIVECRIMESQUAD, 100);
	  ccsexposure = CCSEXPOSURE_EXPOSED;
  }

  void printLootCEOPhotos() {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_PHOTOS_OF_A_MAJOR_CEO, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);

	  change_opinion_from_Influence(CEOPhotosInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, THIS_IS_BOUND_TO_RILE_UP_CORPS, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_CEOSALARY, 50);
	  change_public_opinion(VIEW_CORPORATECULTURE, 50);
	  offended_corps = 1;
  }
  void printLootCEOLoveLetters() {
	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_LOVE_LETTERS_FROM_A_MAJOR_CEO, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);


	  change_opinion_from_Influence(CEOLoveLettersInfluence);


	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, THIS_IS_BOUND_TO_RILE_UP_CORPS, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_CEOSALARY, 50);
	  change_public_opinion(VIEW_CORPORATECULTURE, 50);
	  offended_corps = 1;
  }
  void printLootCEOTaxes() {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_A_MAJOR_CEO_S_TAX_PAPERS, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);

	  change_opinion_from_Influence(CEOTaxesInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, THIS_IS_BOUND_TO_RILE_UP_CORPS, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_CEOSALARY, 50);
	  change_public_opinion(VIEW_CORPORATECULTURE, 50);
	  offended_corps = 1;
  }

  void printLootCorpFiles(const short newspaper) {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CORPORATE_FILES, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, newspaper * 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, newspaper * 10);


	  change_opinion_from_Influence(CEOPhotosInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, THIS_IS_BOUND_TO_RILE_UP_CORPS, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_CEOSALARY, 50);
	  change_public_opinion(VIEW_CORPORATECULTURE, 50);
	  offended_corps = 1;
  }
  void printLootCIAPapers() {
	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CIA_AND_OTHER_INTELLIGENCE_FILES, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);


	  change_opinion_from_Influence(CIAPapersInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, CONST_THIS_IS_BOUND_TO_GET_THE_GOVERNMENT_A_LITTLE_RILED_UP, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_INTELLIGENCE, 50);
	  offended_cia = 1;
  }

  void printLootPolicePapers() {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_POLICE_RECORDS, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);


	  change_opinion_from_Influence(PolicePapersInfluence);

	  moveAlt(9, 1);
	  gamelog.newline();
	  addstrAlt(major_news_take_it_up, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_POLICEBEHAVIOR, 50);
  }
  void printLootJudgePapers() {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_WITH_EVIDENCE_OF_A_CONSERVATIVE_JUDGE, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);


	  change_opinion_from_Influence(JudgePapersInfluence);

	  gamelog.newline();
	  mvaddstrAlt(8, 1, major_news_take_it_up, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_JUSTICES, 50);
  }

  void printLootResearchPapers() {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_RESEARCH_PAPERS, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);


	  change_opinion_from_Influence(ResearchPapersInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.nextMessage();
  }

  void printLootPrisonPapers() {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_PRISON_DOCUMENTS, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);
	  change_public_opinion(VIEW_PRISONS, 50);


	  change_opinion_from_Influence(PrisonPapersInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_DEATHPENALTY, 50);
  }

  void printLootCablePapers() {

	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CABLE_NEWS_MEMOS, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);


	  change_opinion_from_Influence(CablePapersInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, CONST_THIS_IS_BOUND_TO_GET_THE_CONSERVATIVE_MASSES_A_LITTLE_RILED_UP, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_CABLENEWS, 50);
	  offended_cablenews = 1;
  }

//  vector< pair<string, vector<int> > > RadioPapersInfluence;
  void printLootRadioPapers() {


	  mvaddstrAlt(6, 1, CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_AM_RADIO_PLANS, gamelog);
	  moveAlt(7, 1);
	  change_public_opinion(VIEW_LIBERALCRIMESQUAD, 10);
	  change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, 10);


	  change_opinion_from_Influence(RadioPapersInfluence);

	  gamelog.newline();
	  mvaddstrAlt(9, 1, major_news_take_it_up, gamelog);
	  gamelog.newline();
	  mvaddstrAlt(10, 1, CONST_THIS_IS_BOUND_TO_GET_THE_CONSERVATIVE_MASSES_A_LITTLE_RILED_UP, gamelog);
	  gamelog.nextMessage();
	  change_public_opinion(VIEW_AMRADIO, 50);
	  offended_amradio = 1;
  }
  /* monthly - guardian - prints liberal guardian special editions */
  void printnews(short li, short newspaper)
  {
	  //// TODO Move to XML
	  music.play(MUSIC_NEWSPAPER);
	  if (lawList[LAW_FREESPEECH] == -2)offended_firemen = 1;
	  eraseAlt();
	  set_color_easy(WHITE_ON_BLACK_BRIGHT);

	  switch (lootTypeIDEnum[LootTypePool::getInstance().getIdName(li)]) {
	  case ENUM_tag_LOOT_CEOPHOTOS:

		  printLootCEOPhotos();
		  break;

	  case ENUM_tag_LOOT_CEOLOVELETTERS:


		  printLootCEOLoveLetters();
		  break;

	  case ENUM_tag_LOOT_CEOTAXPAPERS:


		  printLootCEOTaxes();
		  break;

	  case ENUM_tag_LOOT_CORPFILES:


		  printLootCorpFiles(newspaper);
		  break;

	  case ENUM_tag_LOOT_CCS_BACKERLIST:


		  printLootCCSBackers();
		  break;

	  case ENUM_tag_LOOT_INTHQDISK:
	  case ENUM_tag_LOOT_SECRETDOCUMENTS:


		  printLootCIAPapers();
		  break;

	  case ENUM_tag_LOOT_POLICERECORDS:


		  printLootPolicePapers();
		  break;

	  case ENUM_tag_LOOT_JUDGEFILES:


		  printLootJudgePapers();
		  break;

	  case ENUM_tag_LOOT_RESEARCHFILES:


		  printLootResearchPapers();
		  break;

	  case ENUM_tag_LOOT_PRISONFILES:


		  printLootPrisonPapers();
		  break;

	  case ENUM_tag_LOOT_CABLENEWSFILES:


		  printLootCablePapers();
		  break;

	  case ENUM_tag_LOOT_AMRADIOFILES:


		  printLootRadioPapers();
		  break;

	  }

	  pressAnyKey();
  }
  void printIncomeTypes(const int y, const int i) {
	  set_color_easy(WHITE_ON_BLACK);
	  mvaddstrAlt(y, 0, dotdotdot);
	  set_color_easy(GREEN_ON_BLACK);
	  string num = PLUS_DOLLAR + tostring(ledger.income[i]);
	  mvaddstrAlt(y, 60 - len(num), num);
	  if (ledger.dailyIncome[i])
		  num = PAREN_PLUS_DOLLAR + tostring(ledger.dailyIncome[i]) + CLOSE_PARENTHESIS;
	  else
	  {
		  set_color_easy(WHITE_ON_BLACK);
		  num = DOLLAR_ZERO;
	  }
	  mvaddstrAlt(y, 73 - len(num), num);
	  set_color_easy(WHITE_ON_BLACK);
	  if (incomeTypes.count(i)) {
		  mvaddstrAlt(y, 0, incomeTypes[i]);
	  }
	  else {
		  mvaddstrAlt(y, 0, incomeTypes[INCOMETYPENUM]);
	  }
  }
  void printLedgerAmount(const int y, const int i) {
	  set_color_easy(WHITE_ON_BLACK);
	  mvaddstrAlt(y, 0, dotdotdot);
	  set_color_easy(RED_ON_BLACK);
	  string num = MINUS_DOLLAR + tostring(ledger.expense[i]);
	  mvaddstrAlt(y, 60 - len(num), num);
	  if (ledger.dailyExpense[i])
		  num = PAREN_MINUS_DOLLAR + tostring(ledger.dailyExpense[i]) + CLOSE_PARENTHESIS;
	  else
	  {
		  set_color_easy(WHITE_ON_BLACK);
		  num = DOLLAR_ZERO;
	  }
	  mvaddstrAlt(y, 73 - len(num), num);
	  set_color_easy(WHITE_ON_BLACK);
	  if (expenseTypes.count(i)) {
		  mvaddstrAlt(y, 0, expenseTypes[i]);
	  }
	  else {
		  mvaddstrAlt(y, 0, expenseTypes[EXPENSETYPENUM]);
	  }
  }
  void printDailyMoney(const int y, const int dailymoney, const int totalmoney) {
	  string num;
	  set_color_easy(WHITE_ON_BLACK_BRIGHT);
	  mvaddstrAlt(y, 0, CONST_NET_CHANGE_THIS_MONTH_DAY);
	  if (totalmoney > 0) { set_color_easy(GREEN_ON_BLACK_BRIGHT); num = CONST_X_PLUS_SIGN; }
	  else if (totalmoney < 0) { set_color_easy(RED_ON_BLACK_BRIGHT); num = CONST_X_MINUS_SIGN; }
	  else { set_color_easy(WHITE_ON_BLACK_BRIGHT); num = ""; }
	  num += DOLLAR_SIGN + tostring(abs(totalmoney));
	  mvaddstrAlt(y, 60 - len(num), num);
	  if (dailymoney > 0)
	  {
		  set_color_easy(GREEN_ON_BLACK_BRIGHT);
		  num = PAREN_PLUS_DOLLAR + tostring(abs(dailymoney)) + CLOSE_PARENTHESIS;
	  }
	  else if (dailymoney < 0)
	  {
		  set_color_easy(RED_ON_BLACK_BRIGHT);
		  num = PAREN_MINUS_DOLLAR + tostring(abs(dailymoney)) + CLOSE_PARENTHESIS;
	  }
	  else
	  {
		  set_color_easy(WHITE_ON_BLACK_BRIGHT);
		  num = DOLLAR_ZERO;
	  }
	  mvaddstrAlt(y, 73 - len(num), num);
  }
  void printLedgerPage(const int y, const string lcsmonthly, const long get_funds) {
	  string num = DOLLAR_SIGN + tostring(get_funds);
	  set_color_easy(WHITE_ON_BLACK);
	  mvaddstrAlt(y, 0, dotdotdot);
	  mvaddstrAlt(y, 0, lcsmonthly);
	  set_color_easy(get_funds ? GREEN_ON_BLACK : WHITE_ON_BLACK);
	  mvaddstrAlt(y, 60 - len(num), num);
  }
  /* monthly - LCS finances report */
  void fundreport(char &clearformess)
  {
	  if (disbanding) return;
	  music.play(MUSIC_FINANCES);
	  clearformess = true;
	  int page = 0;
	  bool showledger = false;
	  int expenselines = 0;
	  for (int i = 0; i < EXPENSETYPENUM; i++)
		  if (ledger.expense[i])
			  expenselines++;
	  while (true)
	  {
		  eraseAlt();
		  int y = 2, totalmoney = 0, dailymoney = 0, numpages = 1;
		  set_color_easy(WHITE_ON_BLACK_BRIGHT);
		  mvaddstrAlt(0, 0, CONST_LIBERAL_CRIME_SQUAD_FUNDING_REPORT);
		  for (int i = 0; i < INCOMETYPENUM; i++)
		  {
			  if (ledger.income[i])
			  {
				  showledger = true;
				  if (page == numpages - 1)
				  {
					  printIncomeTypes(y, i);
				  }
				  totalmoney += ledger.income[i];
				  dailymoney += ledger.dailyIncome[i];
				  if (++y >= 23) y = 2, numpages++;
			  }
		  }
		  // If expenses are too long to fit on this page, start them on the next page so it isn't broken in half unnecessarily
		  if (y + expenselines >= 23 && y > 2) y = 2, numpages++;
		  for (int i = 0; i < EXPENSETYPENUM; i++)
		  {
			  if (ledger.expense[i])
			  {
				  showledger = true;
				  if (page == numpages - 1)
				  {
					  printLedgerAmount(y, i);
				  }
				  totalmoney -= ledger.expense[i];
				  dailymoney -= ledger.dailyExpense[i];
				  if (++y >= 23) y = 2, numpages++;
			  }
		  }
		  if (showledger)
		  {
			  if (page == numpages - 1) makedelimiter(y);
			  if (++y >= 23) y = 2, numpages++;
			  if (page == numpages - 1)
			  {
				  printDailyMoney(y, dailymoney, totalmoney);
			  }
			  if (++y >= 23) y = 2, numpages++;
		  }
		  if (y > 2) y++; // Blank line between income/expenses and assets if not starting a new page
		  if (y + 7 >= 23) y = 2, numpages++; //Start a new page if the liquid assets won't fit on the rest of the current page.
											  // tally up liquid assets
		  long weaponValue = 0, armorValue = 0, clipValue = 0, lootValue = 0;
		  LocationsPool::getInstance().getAssetValues(weaponValue, armorValue, clipValue, lootValue);

		  if (page == numpages - 1)
		  {
			  printLedgerPage(y, CONST_CASH, ledger.get_funds());
		  }
		  if (++y >= 23) y = 2, numpages++;
		  if (page == numpages - 1)
		  {
			  printLedgerPage(y, CONST_TOOLS_AND_WEAPONS, weaponValue);
		  }
		  if (++y >= 23) y = 2, numpages++;
		  if (page == numpages - 1)
		  {
			  printLedgerPage(y, CONST_CLOTHING_AND_ARMOR, armorValue);
		  }
		  if (++y >= 23) y = 2, numpages++;
		  if (page == numpages - 1)
		  {
			  printLedgerPage(y, CONST_AMMUNITION, clipValue);
		  }
		  if (++y >= 23) y = 2, numpages++;
		  if (page == numpages - 1)
		  {
			  printLedgerPage(y, CONST_MISCELLANEOUS_LOOT, lootValue);
		  }
		  if (++y >= 23) y = 2, numpages++;
		  if (page == numpages - 1) makedelimiter(y);
		  if (++y >= 23) y = 2, numpages++;
		  if (page == numpages - 1)
		  {
			  set_color_easy(WHITE_ON_BLACK_BRIGHT);
			  mvaddstrAlt(y, 0, CONST_TOTAL_LIQUID_ASSETS);
			  long netWorth = ledger.get_funds() + weaponValue + armorValue + clipValue + lootValue;
			  set_color_easy(netWorth ? GREEN_ON_BLACK_BRIGHT : WHITE_ON_BLACK_BRIGHT);
			  string num = DOLLAR_SIGN + tostring(netWorth);
			  mvaddstrAlt(y, 60 - len(num), num);
		  }
		  set_color_easy(WHITE_ON_BLACK);
		  if (numpages > 1)
		  {
			  mvaddstrAlt(24, 0, CONST_PRESS_ENTER_TO_REFLECT_ON_THE_REPORT + addpagestr());
			  while (true)
			  {
				  int c = getkeyAlt();
				  if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR)
				  {
					  music.play(MUSIC_PREVIOUS);
					  return;
				  }
				  //PAGE UP
				  if (is_page_up(c)) { page--; if (page < 0) page = numpages - 1; break; }
				  //PAGE DOWN
				  if (is_page_down(c)) { page++; if (page >= numpages) page = 0; break; }
			  }
		  }
		  else
		  {
			  mvaddstrAlt(24, 0, CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THE_REPORT);
			  pressAnyKey();
			  music.play(MUSIC_PREVIOUS);
			  return;
		  }
	  }
  }