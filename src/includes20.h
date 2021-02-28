




/*
	File created by Chris Johnson.
	These were previously all in game.cpp.

	This file includes all the the enums, defines, and included headers required globally by all components.

	All code released under GNU GPL.
*/
#include <windows.h>
#include <vector>
#include <map>
#include <deque>
#include "cmarkup/Markup.h"
using namespace std;

#include "includesDeprecated.h"
#include "includesRandom.h"
/* This is declared again lower down, just needed here for this header. */
std::string tostring(long i);
//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
//#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
//#include "activityST.h"

//int get_associated_attribute(int skill_type);
#include "includesSDS.h"
//#include "includesDeprecatedB.h"
//#ifdef	LCSMONTHLY_CPP
// lcsmonthly.cpp

#include "../creature/newcreature.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../items/itemPool.h"
#include "../items/lootTypePool.h"
#include "../log/log.h"
// for commondisplay.h
#include "../common/commondisplay.h"
// for addpage and delimiter
//#include "../common/equipment.h"
void consolidateloot(vector<Item *> &loot);
//#include "../common/translateid.h"
int getloottype(const string &idname);
void removeItemFromSquad(const int loottypeindex);
#include "../common/commonactions.h"
// for void change_public_opinion(int,int,char =1,char=100);
#include "../cursesAlternative.h"
#include "../cursesAlternativeConstants.h"
#include "../set_color_support.h"
#include "../locations/locationsPool.h"
#include "../common/musicClass.h"
map<short, string> expenseTypes;
map<short, string> incomeTypes;
void constructLootIndices(vector<bool> &havetype, vector<int> &loottypeindex, const vector<string> dox);

extern CCSexposure ccsexposure;
extern char disbanding;
extern class Ledger ledger;
extern Log gamelog;
extern MusicClass music;
extern short lawList[LAWNUM];
extern short offended_amradio;
extern short offended_cablenews;
extern short offended_cia;
extern short offended_corps;
extern short offended_firemen;

const string THIS_IS_BOUND_TO_RILE_UP_CORPS = "This is bound to get the Corporations a little riled up.";
const string major_news_take_it_up = "The major networks and publications take it up and run it for weeks.";

const string CONST_PROMISING_SOMEONE_COMPANY_PROFITS_IN_EXCHANGE_FOR_SEXUAL_FAVORS = "promising someone company profits in exchange for sexual favors.";
const string CONST_THAT_SEEM_TO_TOUCH_ON_EVERY_FETISH_KNOWN_TO_MAN = "that seem to touch on every fetish known to man.";
const string CONST_TO_THE_FDA_OFFICIAL_OVERSEEING_THE_CEO_S_PRODUCTS = "to the FDA official overseeing the CEO's products.";
const string CONST_IMPLYING_THAT_HE_HAS_ENSLAVED_HIS_HOUSESERVANTS = "implying that he has enslaved his houseservants.";
const string CONST_TO_HIMSELF_THEY_RE_VERY_STEAMY = "to himself.  They're very steamy.";
const string CONST_TO_AN_ILLICIT_GAY_LOVER = "to an illicit gay lover.";
const string CONST_TO_THE_JUDGE_THAT_ACQUIT_HIM_IN_A_CORRUPTION_TRIAL = "to the judge that acquit him in a corruption trial.";
const string CONST_ADDRESSED_TO_HIS_PET_DOG_YIKES = "addressed to his pet dog.  Yikes.";

const string CONST_PLAYING_WITH_FECES_AND_URINE = "playing with feces and urine.";
const string CONST_TORTURING_AN_EMPLOYEE_WITH_A_HOT_IRON = "torturing an employee with a hot iron.";
const string CONST_WAVING_A_NAZI_FLAG_AT_A_SUPREMACIST_RALLY = "waving a Nazi flag at a supremacist rally.";
const string CONST_CASTRATING_HIMSELF = "castrating himself.";
const string CONST_MAKING_OUT_WITH_AN_FDA_OFFICIAL_OVERSEEING_THE_CEO_S_PRODUCTS = "making out with an FDA official overseeing the CEO's products.";
const string CONST_TONGUE_KISSING_AN_INFAMOUS_DICTATOR = "tongue-kissing an infamous dictator.";
const string CONST_ENGAGING_IN_HEAVY_BONDAGE_A_CUCUMBER_WAS_INVOLVED_IN_SOME_WAY = "engaging in heavy bondage.  A cucumber was involved in some way.";
const string CONST_PARTICIPATING_IN_A_MURDER = "participating in a murder.";
const string CONST_DIGGING_UP_GRAVES_AND_SLEEPING_WITH_THE_DEAD = "digging up graves and sleeping with the dead.";
const string CONST_ENGAGING_IN_LEWD_BEHAVIOR_WITH_ANIMALS = "engaging in lewd behavior with animals.";
const string CONST_SHOWING_THAT_HE_HAS_ENGAGED_IN_CONSISTENT_TAX_EVASION = "showing that he has engaged in consistent tax evasion.";
const string CONST_DESCRIBING_AN_INTRICATE_TAX_SCHEME = "describing an intricate tax scheme.";
const string CONST_CHEERFULLY_DESCRIBING_FOREIGN_CORPORATE_SWEATSHOPS = "cheerfully describing foreign corporate sweatshops.";
const string CONST_CONTAINING_A_MEMO_TERMINATE_THE_PREGNANCY_I_TERMINATE_YOU = "containing a memo: \"Terminate the pregnancy, I terminate you.\"";
const string CONST_WITH_A_LIST_OF_GAY_EMPLOYEES_ENTITLED_HOMO_WORKERS = "with a list of gay employees entitled \"Homo-workers\".";
const string CONST_DESCRIBING_A_GENETIC_MONSTER_CREATED_IN_A_LAB = "describing a genetic monster created in a lab.";
const string CONST_DOCUMENTING_THE_INFILTRATION_OF_A_PRO_CHOICE_GROUP = "documenting the infiltration of a pro-choice group.";
const string CONST_USED_TO_KEEP_TABS_ON_GAY_CITIZENS = "used to keep tabs on gay citizens.";
const string CONST_DOCUMENTING_HARMFUL_SPEECH_MADE_BY_INNOCENT_CITIZENS = "documenting \"harmful speech\" made by innocent citizens.";
const string CONST_CONTAINING_PRIVATE_INFORMATION_ON_INNOCENT_CITIZENS = "containing private information on innocent citizens.";
const string CONST_DOCUMENTING_THE_PLANNED_ASSASSINATION_OF_A_LIBERAL_FEDERAL_JUDGE = "documenting the planned assassination of a Liberal federal judge.";
const string CONST_DOCUMENTING_THE_OVERTHROW_OF_A_GOVERNMENT = "documenting the overthrow of a government.";

const string CONST_DOCUMENTING_WIDESPREAD_CORRUPTION_IN_THE_FORCE = "documenting widespread corruption in the force.";
const string CONST_DOCUMENTING_A_FORCED_CONFESSION = "documenting a forced confession.";
const string CONST_DOCUMENTING_A_SYSTEMATIC_INVASION_OF_PRIVACY_BY_THE_FORCE = "documenting a systematic invasion of privacy by the force.";
const string CONST_DOCUMENTING_A_POLICE_TORTURE_CASE = "documenting a police torture case.";
const string CONST_DOCUMENTING_HUMAN_RIGHTS_ABUSES_BY_THE_FORCE = "documenting human rights abuses by the force.";

const string CONST_DOCUMENTING_GLADIATORIAL_MATCHES_HELD_BETWEEN_PRISONERS_BY_GUARDS = "documenting gladiatorial matches held between prisoners by guards.";
const string CONST_PROMISING_CONSERVATIVE_RULINGS_IN_EXCHANGE_FOR_APPOINTMENTS = "promising Conservative rulings in exchange for appointments.";
const string CONST_TAKING_BRIBES_TO_ACQUIT_MURDERERS = "taking bribes to acquit murderers.";

const string CONST_SHOWING_HUMAN_TEST_SUBJECTS_DYING_UNDER_GENETIC_RESEARCH = "showing human test subjects dying under genetic research.";
const string CONST_COVERING_UP_THE_ACCIDENTAL_CREATION_OF_A_GENETIC_MONSTER = "covering up the accidental creation of a genetic monster.";
const string CONST_STUDYING_THE_EFFECTS_OF_TORTURE_ON_CATS = "studying the effects of torture on cats.";
const string CONST_DOCUMENTING_HORRIFIC_ANIMAL_RIGHTS_ABUSES = "documenting horrific animal rights abuses.";


const string CONST_DOCUMENTING_WIDESPREAD_CORRUPTION_AMONG_PRISON_EMPLOYEES = "documenting widespread corruption among prison employees.";
const string CONST_DOCUMENTING_A_PRISON_TORTURE_CASE = "documenting a prison torture case.";
const string CONST_DOCUMENTING_HUMAN_RIGHTS_ABUSES_BY_PRISON_GUARDS = "documenting human rights abuses by prison guards.";


const string CONST_PLANNING_TO_DRUM_UP_A_FALSE_SCANDAL_ABOUT_A_LIBERAL_FIGURE = "planning to drum up a false scandal about a Liberal figure.";
const string CONST_INSTRUCTING_A_FEMALE_ANCHOR_TO_GET_SEXIER_OR_GET_A_NEW_JOB = "instructing a female anchor to 'get sexier or get a new job'.";
const string CONST_MANDATING_NEGATIVE_COVERAGE_OF_LIBERAL_POLITICIANS = "mandating negative coverage of Liberal politicians.";
const string CONST_CALLING_THEIR_NEWS_THE_VANGUARD_OF_CONSERVATIVE_THOUGHT = "calling their news 'the vanguard of Conservative thought'.";

const string CONST_SAYING_IT_S_OKAY_TO_LIE_THEY_DON_T_NEED_THE_TRUTH = "saying 'it's okay to lie, they don't need the truth'.";
const string CONST_CALLING_LISTENERS_SHEEP_TO_BE_TOLD_WHAT_TO_THINK = "calling listeners 'sheep to be told what to think'.";


const string CONST_PRESS_ANY_KEY_TO_REFLECT_ON_THE_REPORT = "Press any key to reflect on the report.";
const string CONST_PRESS_ENTER_TO_REFLECT_ON_THE_REPORT = "Press Enter to reflect on the report.  ";
const string DOLLAR_SIGN = "$";
const string CONST_TOTAL_LIQUID_ASSETS = "Total Liquid Assets:";
const string CONST_MISCELLANEOUS_LOOT = "Miscellaneous Loot";
const string CONST_AMMUNITION = "Ammunition";
const string CONST_CLOTHING_AND_ARMOR = "Clothing and Armor";
const string CONST_TOOLS_AND_WEAPONS = "Tools and Weapons";
const string CONST_CASH = "Cash";
const string DOLLAR_ZERO = " ($0)";
const string PAREN_MINUS_DOLLAR = " (-$";
const string PAREN_PLUS_DOLLAR = " (+$";
const string CONST_X_MINUS_SIGN = "-";
const string CONST_X_PLUS_SIGN = "+";
const string CONST_NET_CHANGE_THIS_MONTH_DAY = "Net Change This Month (Day):";
const string MINUS_DOLLAR = "-$";
const string PLUS_DOLLAR = "+$";
const string CONST_LIBERAL_CRIME_SQUAD_FUNDING_REPORT = "Liberal Crime Squad: Funding Report";
const string CONST_THIS_IS_BOUND_TO_GET_THE_CONSERVATIVE_MASSES_A_LITTLE_RILED_UP = "This is bound to get the Conservative masses a little riled up.";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_AM_RADIO_PLANS = "The Liberal Guardian runs a story featuring AM radio plans ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CABLE_NEWS_MEMOS = "The Liberal Guardian runs a story featuring cable news memos ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_PRISON_DOCUMENTS = "The Liberal Guardian runs a story featuring prison documents ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_RESEARCH_PAPERS = "The Liberal Guardian runs a story featuring research papers ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_WITH_EVIDENCE_OF_A_CONSERVATIVE_JUDGE = "The Liberal Guardian runs a story with evidence of a Conservative judge ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_POLICE_RECORDS = "The Liberal Guardian runs a story featuring police records ";
const string CONST_THIS_IS_BOUND_TO_GET_THE_GOVERNMENT_A_LITTLE_RILED_UP = "This is bound to get the Government a little riled up.";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CIA_AND_OTHER_INTELLIGENCE_FILES = "The Liberal Guardian runs a story featuring CIA and other intelligence files ";
const string CONST_THIS_IS_THE_BEGINNING_OF_THE_END_FOR_THE_CONSERVATIVE_CRIME_SQUAD = "This is the beginning of the end for the Conservative Crime Squad.";
const string CONST_NEWS_DENOUNCE_THE_CCS = "News denounce the CCS.";
const string CONST_TOWARD_THE_REVELATIONS_AND_THE_SPEED_WITH_WHICH_EVEN_AM_RADIO_AND_CABLE = "toward the revelations, and the speed with which even AM Radio and Cable";
const string CONST_FOR_MONTHS_ONE_THING_IS_CLEAR_HOWEVER_FROM_THE_IMMEDIATE_PUBLIC_REACTION = "for months. One thing is clear, however, from the immediate public reaction";
const string CONST_COUNTRY_AND_THE_FULL_RAMIFICATIONS_OF_THIS_REVELATION_MAY_NOT_BE_FELT = "country, and the full ramifications of this revelation may not be felt";
const string CONST_THE_SCANDAL_REACHES_INTO_THE_HEART_OF_THE_CONSERVATIVE_LEADERSHIP_IN_THE = "The scandal reaches into the heart of the Conservative leadership in the";
const string CONST_AGAINST = "against.";
const string CONST_AS_A_FOIL_WHEN_NO_OTHER_ENEMIES_WERE_PRESENT_TO_DIRECT_PUBLIC_ENERGY = "as a foil when no other enemies were present to direct public energy";
const string CONST_ABOVE_PROSECUTION_AND_COULD_HUNT_DOWN_LAW_ABIDING_LIBERALS_AND_ACT = "above prosecution, and could hunt down law-abiding Liberals and act";
const string CONST_EXTENSIVE_PLANNING_TO_CREATE_AN_EXTRA_JUDICIAL_DEATH_SQUAD_THAT_WOULD_BE = "extensive planning to create an extra-judicial death squad that would be";
const string CONST_IN_THE_STATE_AND_FEDERAL_GOVERNMENTS_SECTIONS_PRECISELY_DOCUMENT_THE = "in the state and federal governments. Sections precisely document the";
const string CONST_RESPONSIBILITIES_OF_CONSERVATIVE_CRIME_SQUAD_SYMPATHIZERS_AND_SUPPORTERS = "responsibilities of Conservative Crime Squad sympathizers and supporters";
const string CONST_THE_CCS_ORGANIZATION_ALSO_REVEALING_IN_EXTREME_DETAIL_THE_NAMES_AND = "the CCS organization, also revealing in extreme detail the names and ";
const string CONST_THE_LIBERAL_GUARDIAN_RUNS_MORE_THAN_ONE_THOUSAND_PAGES_OF_DOCUMENTS_ABOUT = "The Liberal Guardian runs more than one thousand pages of documents about ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_CORPORATE_FILES = "The Liberal Guardian runs a story featuring Corporate files ";
const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_A_MAJOR_CEO_S_TAX_PAPERS = "The Liberal Guardian runs a story featuring a major CEO's tax papers ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_LOVE_LETTERS_FROM_A_MAJOR_CEO = "The Liberal Guardian runs a story featuring love letters from a major CEO ";

const string CONST_THE_LIBERAL_GUARDIAN_RUNS_A_STORY_FEATURING_PHOTOS_OF_A_MAJOR_CEO = "The Liberal Guardian runs a story featuring photos of a major CEO ";
const string CONST_ENTER_NOT_IN_THIS_MONTH_S_LIBERAL_GUARDIAN = "Enter - Not in this month's Liberal Guardian";
const string CONST_DO_YOU_WANT_TO_RUN_A_SPECIAL_EDITION = "Do you want to run a special edition?";
const string CONST_X_LIBERAL_GUARDIAN = "Liberal Guardian.";
const string CONST_THE_RESPONSE_IS_ELECTRIC_EVERYONE_IS_TALKING_ABOUT_THIS_MONTH_S = "The response is electric. Everyone is talking about this month's ";
const string CONST_THE_RESPONSE_IS_VERY_STRONG_PEOPLE_ARE_CHANGING_THEIR_MINDS = "The response is very strong. People are changing their minds.";
const string CONST_MANY_PEOPLE_ARE_READING_IT = "Many people are reading it.";
const string CONST_A_FAIR_NUMBER_OF_PEOPLE_ARE_READING_IT = "A fair number of people are reading it.";
const string CONST_VERY_FEW_PEOPLE_SEEM_TO_BE_INTERESTED = "Very few people seem to be interested.";
const string CONST_UNFORTUNATELY_NOBODY_SEEMS_INTERESTED = "Unfortunately, nobody seems interested.";
const string CONST_THE_ONLY_READERS_ARE_CONSERVATIVES_WHO_SEEM_TO_THINK_IT_S_FUNNY = "The only readers are Conservatives, who seem to think it's funny.";
const string CONST_IS_PUBLISHED = " is published.";
const string CONST_THE_MONTHLY_LIBERAL_GUARDIAN_ONLINE_NEWSLETTER = "The monthly Liberal Guardian online newsletter";
const string CONST_THE_MONTHLY_LIBERAL_GUARDIAN_NEWSPAPER = "The monthly Liberal Guardian newspaper";

const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT = "LOOT";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_PRISONFILES = "LOOT_PRISONFILES";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_LOOT_INTHQDISK = "LOOT_INTHQDISK";
const string tag_LOOT_CCS_BACKERLIST = "LOOT_CCS_BACKERLIST";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_CEOTAXPAPERS = "LOOT_CEOTAXPAPERS";
const string tag_LOOT_CEOLOVELETTERS = "LOOT_CEOLOVELETTERS";
const string tag_LOOT_CEOPHOTOS = "LOOT_CEOPHOTOS";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

enum lootTypeTags {
	ENUM_tag_LOOT_CEOPHOTOS,
	ENUM_tag_LOOT_CEOLOVELETTERS,
	ENUM_tag_LOOT_CEOTAXPAPERS,
	ENUM_tag_LOOT_CORPFILES,
	ENUM_tag_LOOT_CCS_BACKERLIST,
	ENUM_tag_LOOT_INTHQDISK,
	ENUM_tag_LOOT_SECRETDOCUMENTS,
	ENUM_tag_LOOT_POLICERECORDS,
	ENUM_tag_LOOT_JUDGEFILES,
	ENUM_tag_LOOT_RESEARCHFILES,
	ENUM_tag_LOOT_PRISONFILES,
	ENUM_tag_LOOT_CABLENEWSFILES,
	ENUM_tag_LOOT_AMRADIOFILES,
};
map<string, int> lootTypeIDEnum = {
	map<string, int> ::value_type(tag_LOOT_CEOPHOTOS, ENUM_tag_LOOT_CEOPHOTOS),
	map<string, int> ::value_type(tag_LOOT_CEOLOVELETTERS, ENUM_tag_LOOT_CEOLOVELETTERS),
	map<string, int> ::value_type(tag_LOOT_CEOTAXPAPERS, ENUM_tag_LOOT_CEOTAXPAPERS),
	map<string, int> ::value_type(tag_LOOT_CORPFILES, ENUM_tag_LOOT_CORPFILES),
	map<string, int> ::value_type(tag_LOOT_CCS_BACKERLIST, ENUM_tag_LOOT_CCS_BACKERLIST),
	map<string, int> ::value_type(tag_LOOT_INTHQDISK, ENUM_tag_LOOT_INTHQDISK),
	map<string, int> ::value_type(tag_LOOT_SECRETDOCUMENTS, ENUM_tag_LOOT_SECRETDOCUMENTS),
	map<string, int> ::value_type(tag_LOOT_POLICERECORDS, ENUM_tag_LOOT_POLICERECORDS),
	map<string, int> ::value_type(tag_LOOT_JUDGEFILES, ENUM_tag_LOOT_JUDGEFILES),
	map<string, int> ::value_type(tag_LOOT_RESEARCHFILES, ENUM_tag_LOOT_RESEARCHFILES),
	map<string, int> ::value_type(tag_LOOT_PRISONFILES, ENUM_tag_LOOT_PRISONFILES),
	map<string, int> ::value_type(tag_LOOT_CABLENEWSFILES, ENUM_tag_LOOT_CABLENEWSFILES),
	map<string, int> ::value_type(tag_LOOT_AMRADIOFILES, ENUM_tag_LOOT_AMRADIOFILES),
};
static const char dotdotdot[] = ". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . ";
//Temporary, maybe put special edition definition into an xml file. -XML
static const string document_types[] =
{  // This list MUST be in alphabetical order for binary_search() to work right
	tag_LOOT_AMRADIOFILES,
	tag_LOOT_CABLENEWSFILES,
	tag_LOOT_CCS_BACKERLIST,
	tag_LOOT_CEOLOVELETTERS,
	tag_LOOT_CEOPHOTOS,
	tag_LOOT_CEOTAXPAPERS,
	tag_LOOT_CORPFILES,
	tag_LOOT_INTHQDISK,
	tag_LOOT_JUDGEFILES,
	tag_LOOT_POLICERECORDS,
	tag_LOOT_PRISONFILES,
	tag_LOOT_RESEARCHFILES,
	tag_LOOT_SECRETDOCUMENTS
};
//#endif//LCSMONTHLY_CPP
//#endif// INCLUDES_H_INCLUDED
