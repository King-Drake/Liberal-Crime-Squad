




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
//#include "vehicle/vehicletype.h"
//#include "vehicle/vehicle.h"


//just a float that is initialized to 0
#include "floatZero.h"
//Interrogation information for the InterrogationST system, to be
//dynamically created on capture and deleted when InterrogationST ends,
//referenced using a pointer typecast into one of the arguments
//of the target's current action.
#include "activityST.h"

//int get_associated_attribute(int skill_type);
#include "includesSDS.h"
#include "includesSDS2.h"
//#include "includesDeprecatedB.h"
//#ifdef	JUSTICE_CPP
// justice.cpp

const string counts_of = " counts of ";
const string execution_in_three_months = "The execution is scheduled to occur three months from now.";
const string justice = "justice\\";
const string CONST_HIRING_AN_UNDOCUMENTED_WORKER = "hiring an undocumented worker";
const string CONST_X_HIRING_UNDOCUMENTED_WORKERS = "hiring undocumented workers";
const string CONST_MONTHS = " months.";
const string CONST_IS_DUE_TO_BE_EXECUTED_IN = " is due to be executed in ";
const string CONST_IS_DUE_TO_BE_RELEASED_NEXT_MONTH = " is due to be released next month.";
const string CONST_IS_DUE_TO_BE_EXECUTED_NEXT_MONTH = " is due to be executed next month.";
const string CONST_NO_DOUBT_THERE_ARE_SOME_MENTAL_SCARS_BUT_THE_LIBERAL_IS_BACK = "No doubt there are some mental scars, but the Liberal is back.";
const string CONST_HAS_BEEN_RELEASED_FROM_PRISON = " has been released from prison.";
const string CONST_IF_YOU_CAN_T_PROTECT_YOUR_OWN_PEOPLE_WHO_CAN_YOU_PROTECT = "If you can't protect your own people, who can you protect?";
const string CONST_HAS_FAILED_THE_LIBERAL_CRIME_SQUAD = " has failed the Liberal Crime Squad.";
const string CONST_X_BY_SPACE = "by ";
const string CONST_TODAY_THE_CONSERVATIVE_MACHINE_EXECUTED = "Today, the Conservative Machine executed ";
const string CONST_FOR_SHAME = "FOR SHAME:";
const string CONST_DUE_TO_THE_ABOLITION_OF_THE_DEATH_PENALTY = "due to the abolition of the death penalty.";
const string CONST_S_DEATH_SENTENCE_HAS_BEEN_COMMUTED_TO_LIFE = "'s death sentence has been commuted to life, ";
const string CONST_SEEMS_TO_BE_MOSTLY_FINE_THOUGH = " seems to be mostly fine, though.";
const string CONST_IS_KINDA_LOSING_IT_IN_HERE_JUICE_THAT_IS = " is kinda losing it in here. Juice, that is.";
const string CONST_HAS_BECOME_A_MORE_HARDENED_JUICIER_CRIMINAL = " has become a more hardened, Juicier criminal.";
const string CONST_THE_LCS_WILL_RISE_AGAIN_MULTIPLE_LCS_MEMBERS_ESCAPE = "The LCS will rise again! Multiple LCS members escape!";
const string CONST_ANOTHER_IMPRISONED_LCS_MEMBER_ALSO_GETS_OUT = "Another imprisoned LCS member also gets out!";
const string CONST_ESCAPED_FROM_PRISON = " escaped from prison!";
const string CONST_INTENTIONALLY_ODS_ON_SMUGGLED_DRUGS_THEN_BREAKS_OUT_OF_THE_MEDICAL_WARD = " intentionally ODs on smuggled drugs, then breaks out of the medical ward!";
const string CONST_JIMMIES_THE_CELL_DOOR_AND_CUTS_THE_OUTER_FENCE_IN_THE_DEAD_OF_NIGHT = " jimmies the cell door and cuts the outer fence in the dead of night!";
const string CONST_PUTS_ON_SMUGGLED_STREET_CLOTHES_AND_CALMLY_WALKS_OUT_OF_PRISON = " puts on smuggled street clothes and calmly walks out of prison.";
const string CONST_CODES_A_VIRUS_ON_A_SMUGGLED_PHONE_THAT_OPENS_ALL_THE_PRISON_DOORS = " codes a virus on a smuggled phone that opens all the prison doors!";
const string CONST_LEADS_A_RIOT_WITH_DOZENS_OF_PRISONERS_CHANTING_THE_LCS_SLOGAN = " leads a riot with dozens of prisoners chanting the LCS slogan!";
const string CONST_MANAGED_TO_AVOID_LASTING_INJURY = " managed to avoid lasting injury.";
const string CONST_IS_FOUND_DEAD = " is found dead.";
const string CONST_IS_BADLY_HURT_IN_THE_PROCESS = " is badly hurt in the process.";
const string CONST_CONSUMES_DRUGS_THAT_SIMULATE_DEATH_AND_IS_THROWN_OUT_WITH_THE_TRASH = " consumes drugs that simulate death, and is thrown out with the trash!";
const string CONST_PICKS_THE_LOCK_ON_THEIR_LEG_CHAINS_AND_THEN_SNEAKS_AWAY = " picks the lock on their leg chains and then sneaks away!";
const string CONST_WEARS_AN_ELECTRICIAN_S_OUTFIT_AND_RIDES_AWAY_WITH_SOME_CONTRACTORS = " wears an electrician's outfit and rides away with some contractors.";
const string CONST_LEADS_THE_OPPRESSED_PRISONERS_AND_OVERWHELMS_THE_PRISON_GUARDS = " leads the oppressed prisoners and overwhelms the prison guards!";
const string CONST_X_REMAINS_STRONG = " remains strong.";
const string CONST_ABANDONS_THE_LIBERAL_CRIME_SQUAD = " abandons the Liberal Crime Squad!";
const string CONST_ONLY_STAYS_LOYAL_TO_THE_LCS_FOR = " only stays loyal to the LCS for ";
const string CONST_SILENTLY_GROWS_WISER = " silently grows Wiser...";
const string CONST_FEELS_BAD_ABOUT_LCS_ACTIONS_AND_LOSES_JUICE = " feels bad about LCS actions, and loses juice!";
const string CONST_THE_COURT_ACCEPTS_THE_PLEA = "The court accepts the plea.";
const string CONST_NOLO = "nolo";
const string CONST_LESS_A_MONTH_FOR_TIME_ALREADY_SERVED = ", less a month for time already served.";
const string CONST_WILL_BE_RETURNED_TO_PRISON_TO_RESUME_AN_EARLIER_SENTENCE = " will be returned to prison to resume an earlier sentence";
const string CONST_IS_FREE = " is free!";
const string CONST_NOT_GUILTY = "NOT GUILTY!";
const string CONST_THE_PROSECUTION_DECLINES_TO_RE_TRY_THE_CASE = "The prosecution declines to re-try the case.";
const string CONST_THE_CASE_WILL_BE_RE_TRIED_NEXT_MONTH = "The case will be re-tried next month.";
const string CONST_BUT_THEY_CAN_T_REACH_A_VERDICT = "But they can't reach a verdict!";
const string CONST_THE_JURY_HAS_RETURNED_FROM_DELIBERATIONS = "The jury has returned from deliberations.";
const string CONST_THE_JURY_LEAVES_TO_CONSIDER_THE_CASE = "The jury leaves to consider the case.";
const string CONST_TO_ACQUIT = " to acquit)";
const string CONST_NEED = ", need ";
const string CONST_X_SPACE_PARENTHESIS = " (";
const string CONST_HAD_THE_JURY_JUDGE_AND_PROSECUTION_CRYING_FOR_FREEDOM = " had the jury, judge, and prosecution crying for freedom.";
const string CONST_MADE_A_VERY_POWERFUL_CASE = " made a very powerful case.";
const string CONST_WORKED_THE_JURY_VERY_WELL = " worked the jury very well.";
const string CONST_S_ARGUMENTS_WERE_PRETTY_GOOD = "'s arguments were pretty good.";
const string CONST_DID_ALL_RIGHT_BUT_MADE_SOME_MISTAKES = " did all right, but made some mistakes.";
const string CONST_S_CASE_REALLY_SUCKED = "'s case really sucked.";
const string CONST_MAKES_ONE_HORRIBLE_MISTAKE_AFTER_ANOTHER = " makes one horrible mistake after another.";
const string CONST_CONDUCTS_AN_INCREDIBLE_DEFENSE = " conducts an incredible defense.";
const string CONST_AND_SHOUT_NOT_GUILTY_BEFORE_DELIBERATIONS_EVEN_BEGAN = "and shout \"NOT GUILTY!\" before deliberations even began.";
const string CONST_S_ARGUMENTS_MADE_SEVERAL_OF_THE_JURORS_STAND_UP = "'s arguments made several of the jurors stand up ";
const string CONST_THE_DEFENSE_IS_EXTREMELY_COMPELLING = "The defense is extremely compelling.";
const string CONST_THE_DEFENSE_MAKES_THE_PROSECUTION_LOOK_LIKE_AMATEURS = "The defense makes the prosecution look like amateurs.";
const string CONST_THE_DEFENSE_WAS_REALLY_SLICK = "The defense was really slick.";
const string CONST_DEFENSE_ARGUMENTS_WERE_PRETTY_GOOD = "Defense arguments were pretty good.";
const string CONST_THE_DEFENSE_WAS_LACKLUSTER = "The defense was lackluster.";
const string CONST_THE_DEFENSE_IS_TOTALLY_LAME = "The defense is totally lame.";
const string CONST_THE_DEFENSE_ATTORNEY_ACCIDENTALLY_SAID_MY_CLIENT_IS_GUILTY_DURING_CLOSING = "The defense attorney accidentally said \"My client is GUILTY!\" during closing.";
const string CONST_THE_DEFENSE_ATTORNEY_RARELY_SHOWED_UP = "The defense attorney rarely showed up.";
const string CONST_TO_CONVICT = " to convict)";
const string CONST_X_TO_PLUS = " to +";
const string PARENTHESIS_PLUS = " (+";
const string CONST_THE_PROSECUTION_IS_INCREDIBLY_STRONG = "The prosecution is incredibly strong.";
const string CONST_THE_PROSECUTION_MAKES_AN_AIRTIGHT_CASE = "The prosecution makes an airtight case.";
const string CONST_THE_PROSECUTION_S_CASE_IS_SOLID = "The prosecution's case is solid.";
const string CONST_THE_PROSECUTION_GIVES_A_STANDARD_PRESENTATION = "The prosecution gives a standard presentation.";
const string CONST_THE_PROSECUTION_S_PRESENTATION_IS_TERRIBLE = "The prosecution's presentation is terrible.";
const string CONST_THE_JURY_IS_A_BIT_CONSERVATIVE = "The jury is a bit Conservative.";
const string CONST_THE_JURY_IS_QUITE_MODERATE = "The jury is quite moderate.";
const string CONST_THE_JURY_IS_FAIRLY_LIBERAL = "The jury is fairly Liberal.";
const string CONST_S_BEST_FRIEND_FROM_CHILDHOOD_IS_A_JUROR = "'s best friend from childhood is a juror.";
const string CONST_S_CONSERVATIVE_ARCH_NEMESIS_WILL_REPRESENT_THE_PROSECUTION = "'s CONSERVATIVE ARCH-NEMESIS will represent the prosecution!!!";
const string CONST_S_FAVOR = "'s favor!";
const string CONST_ENSURES_THE_JURY_IS_STACKED_IN = " ensures the jury is stacked in ";
const string CONST_THE_TRIAL_PROCEEDS_JURY_SELECTION_IS_FIRST = "The trial proceeds.  Jury selection is first.";
const string CONST_IS_STANDING_TRIAL = " is standing trial.";
const string CONST_INTELLIGENCE = "Intelligence: ";
const string CONST_X_LAW_COLON = "Law: ";
const string CONST_CHARISMA = "Charisma: ";
const string CONST_X_PERSUASION_COLON = "Persuasion: ";
const string HEART_COLON = "Heart: ";
const string CONST_S_OFFER_TO_ASSIST_PRO_BONO = "'s offer to assist pro bono.";
const string CONST_E_ACCEPT_SLEEPER = "E - Accept sleeper ";
const string CONST_D_PAY_5000_TO_HIRE_ACE_LIBERAL_ATTORNEY = "D - Pay $5000 to hire ace Liberal attorney ";
const string CONST_C_PLEAD_GUILTY = "C - Plead guilty.";
const string CONST_B_DEFEND_SELF = "B - Defend self!";
const string CONST_A_USE_A_COURT_APPOINTED_ATTORNEY = "A - Use a court-appointed attorney.";
const string CONST_HOW_WILL_YOU_CONDUCT_THE_DEFENSE = "How will you conduct the defense?";
const string CONST_A_FORMER_LCS_MEMBER_WILL_TESTIFY_AGAINST = "A former LCS member will testify against ";
const string CONST_FORMER_LCS_MEMBERS_WILL_TESTIFY_AGAINST = " former LCS members will testify against ";
const string CONST_X_LOITERING = "loitering";
const string CONST_INDECENT_EXPOSURE = "indecent exposure";
const string CONST_X_DISTURBING_THE_PEACE = "disturbing the peace";
const string CONST_X_RESISTING_ARREST = "resisting arrest";
const string CONST_X_VANDALISM = "vandalism";
const string CONST_X_BREAKING_AND_ENTERING = "breaking and entering";
const string CONST_X_UNLAWFUL_BURIAL = "unlawful burial";
const string CONST_UNLAWFUL_ACCESS_OF_AN_INFORMATION_SYSTEM = "unlawful access of an information system";
const string CONST_INTERFERENCE_WITH_INTERSTATE_COMMERCE = "interference with interstate commerce";
const string CONST_POSSESSION_OF_AN_ILLEGAL_WEAPON = "possession of an illegal weapon";
const string CONST_FIRING_AN_ILLEGAL_WEAPON = "firing an illegal weapon";
const string CONST_HIRING_AN_ILLEGAL_ALIEN = "hiring an illegal alien";
const string CONST_X_HIRING_ILLEGAL_ALIENS = "hiring illegal aliens";
const string CONST_X_PROSTITUTION = "prostitution";
const string CONST_PETTY_LARCENY = "petty larceny";
const string CONST_X_CREDIT_CARD_FRAUD_LOWERCASE = "credit card fraud";
const string CONST_X_GRAND_THEFT_AUTO = "grand theft auto";
const string CONST_MISDEMEANOR_ASSAULT = "misdemeanor assault";
const string CONST_FELONY_ASSAULT = "felony assault";
const string CONST_X_EXTORTION = "extortion";
const string CONST_X_RACKETEERING = "racketeering";
const string CONST_X_JURY_TAMPERING = "jury tampering";
const string CONST_AIDING_A_PRISON_ESCAPE = "aiding a prison escape";
const string CONST_X_ESCAPING_PRISON = "escaping prison";
const string CONST_X_DRUG_DEALING = "drug dealing";
const string CONST_SEDITION = "sedition";
const string CONST_X_FLAG_BURNING_LOWERCASE = "flag burning";
const string CONST_FELONY_FLAG_BURNING = "felony flag burning";
const string CONST_X_FLAG_MURDER = "Flag Murder";
const string CONST_X_ARSON = "arson";
const string CONST_X_BANK_ROBBERY = "bank robbery";
const string CONST_X_KIDNAPPING = "kidnapping";
const string CONST_X_MURDER = "murder";
const string CONST_X_TERRORISM = "terrorism";
const string CONST_X_TREASON = "treason";
const string CONST_IS_CHARGED_WITH = ", is charged with ";
const string CONST_THE_DEFENDANT = "The defendant, ";
const string CONST_THE_JUDGE_READS_THE_CHARGES = "The judge reads the charges:";
const string CONST_READS_THE_CHARGES_TRYING_TO_HIDE_A_SMILE = " reads the charges, trying to hide a smile:";
const string CONST_TO_BE_SERVED_CONSECUTIVELY = "to be served consecutively";
const string CONST_TO_BE_SERVED_CONCURRENTLY = "to be served concurrently";
const string CONST_X_SINGLE_COMMA = ",";
const string CONST_IN_PRISON = " in prison";
const string CONST_LETTER_S = "s";
const string CONST_MONTH = " month";
const string CONST_YEARS_IN_PRISON = " years in prison";
const string CONST_LIFE_IN_PRISON = "life in prison";
const string CONST_HAVE_A_NICE_DAY = "Have a nice day, ";
const string CONST_CONSECUTIVE_LIFE_TERMS_IN_PRISON = " consecutive life terms in prison";
const string CONST_YOU_ARE_SENTENCED_TO = ", you are sentenced to ";
const string CONST_CONSIDER_THIS_A_WARNING_YOU_ARE_FREE_TO_GO = ", consider this a warning.  You are free to go.";
const string CONST_YOU_WILL_BE_RETURNED_TO_PRISON_TO_RESUME_IT = "You will be returned to prison to resume it";
const string CONST_THE_COURT_SEES_NO_NEED_TO_ADD_TO_YOUR_EXISTING_SENTENCE = ", the court sees no need to add to your existing sentence.";
const string CONST_YOU_ARE_SENTENCED_TO_DEATH = ", you are sentenced to DEATH!";
const string CONST_YOU_WILL_BE_RETURNED_TO_PRISON_TO_CARRY_OUT_YOUR_DEATH_SENTENCE = ", you will be returned to prison to carry out your death sentence.";
const string CONST_DURING_SENTENCING_THE_JUDGE_GRANTS_SOME_LENIENCY = "During sentencing, the judge grants some leniency.";
const string CONST_GUILTY = "GUILTY!";
const string CONST_GENERAL_EXPERIENCES_TXT = "general_experiences.txt";
const string CONST_BAD_EXPERIENCES_TXT = "bad_experiences.txt";
const string CONST_GOOD_EXPERIENCES_TXT = "good_experiences.txt";
const string CONST_LABOR_CAMP_EXPERIENCES_TXT = "labor_camp_experiences.txt";
const string CONST_REEDUCATION_EXPERIENCES_TXT = "reeducation_experiences.txt";
const string CONST_SUPPOSEDLY_PAINLESS_EXECUTION_METHOD_TXT = "supposedly_painless_execution_method.txt";
const string CONST_STANDARD_EXECUTION_METHODS_TXT = "standard_execution_methods.txt";
const string CONST_CRUEL_AND_UNUSUAL_EXECUTION_METHODS_TXT = "cruel_and_unusual_execution_methods.txt";
const string CONST_CONSERVATIVE_JURY_TXT = "conservative_jury.txt";
const string CONST_LIBERAL_JURY_TXT = "liberal_jury.txt";

const string tag_ARMOR = "ARMOR";
const string tag_ARMOR_CLOTHES = "ARMOR_CLOTHES";
const string tag_ARMOR_WORKCLOTHES = "ARMOR_WORKCLOTHES";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";

const string SINGLE_DOT = ".";
const string CONST_X_COMMA_SPACE = ", ";
const string CONST_SPACE_AND_SPACE = " and ";
const string LETTER_S = "s";

#include "../creature/creature.h"
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../log/log.h"
//#include "../common/commonactions.h"
int scare_factor(int lawflag, int crimenumber);
#include "../common/commonactionsCreature.h"
// for  bool iscriminal(Creature &)
#include "../common/translateid.h"
// for  int getarmortype
#include "../politics/politics.h"
//for publicmood
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../common/creaturePoolCreature.h"
vector<string> liberal_jury;
vector<string> conservative_jury;
vector<string> cruel_and_unusual_execution_methods;
vector<string> standard_execution_methods;
vector<string> supposedly_painless_execution_method;
vector<string> reeducation_experiences;
vector<string> labor_camp_experiences;
vector<string> good_experiences;
vector<string> bad_experiences;
vector<string> general_experiences;
#include "../customMaps.h"
vector<file_and_text_collection> justice_text_file_collection = {
	/*justice.cpp*/
	customText(&liberal_jury, justice + CONST_LIBERAL_JURY_TXT),
	customText(&conservative_jury, justice + CONST_CONSERVATIVE_JURY_TXT),
	customText(&cruel_and_unusual_execution_methods, justice + CONST_CRUEL_AND_UNUSUAL_EXECUTION_METHODS_TXT),
	customText(&standard_execution_methods, justice + CONST_STANDARD_EXECUTION_METHODS_TXT),
	customText(&supposedly_painless_execution_method, justice + CONST_SUPPOSEDLY_PAINLESS_EXECUTION_METHOD_TXT),
	customText(&reeducation_experiences, justice + CONST_REEDUCATION_EXPERIENCES_TXT),
	customText(&labor_camp_experiences, justice + CONST_LABOR_CAMP_EXPERIENCES_TXT),
	customText(&good_experiences, justice + CONST_GOOD_EXPERIENCES_TXT),
	customText(&bad_experiences, justice + CONST_BAD_EXPERIENCES_TXT),
	customText(&general_experiences, justice + CONST_GENERAL_EXPERIENCES_TXT),
};
#include "../common/musicClass.h"

extern bool SHOWMECHANICS;
extern MusicClass music;
extern class Ledger ledger;
extern unsigned long attorneyseed[RNG_SIZE];
extern unsigned long seed[RNG_SIZE];
extern Log gamelog;
extern int stat_dead;
extern short lawList[LAWNUM];
extern vector<DeprecatedCreature *> pool;

#include "../common/creaturePool.h"
#include "../locations/locationsPool.h"
//void printSingleCrime(const CreatureJustice g, const Lawflags law_flag, const int typenum, const string crime_string, const bool mention_multiple_counts = false);
map<Lawflags, string> crimeBlockOne = {
	map<Lawflags, string>::value_type(LAWFLAG_TREASON, CONST_X_TREASON),
	map<Lawflags, string>::value_type(LAWFLAG_TERRORISM, CONST_X_TERRORISM),
	map<Lawflags, string>::value_type(LAWFLAG_MURDER, CONST_X_MURDER),
	map<Lawflags, string>::value_type(LAWFLAG_KIDNAPPING, CONST_X_KIDNAPPING),
	map<Lawflags, string>::value_type(LAWFLAG_BANKROBBERY, CONST_X_BANK_ROBBERY),
	map<Lawflags, string>::value_type(LAWFLAG_ARSON, CONST_X_ARSON),
};
map<Lawflags, string> crimeBlockTwo = {
	map<Lawflags, string>::value_type(LAWFLAG_SPEECH, CONST_SEDITION),
	map<Lawflags, string>::value_type(LAWFLAG_BROWNIES, CONST_X_DRUG_DEALING),
	map<Lawflags, string>::value_type(LAWFLAG_ESCAPED, CONST_X_ESCAPING_PRISON),
	map<Lawflags, string>::value_type(LAWFLAG_HELPESCAPE, CONST_AIDING_A_PRISON_ESCAPE),
	map<Lawflags, string>::value_type(LAWFLAG_JURY, CONST_X_JURY_TAMPERING),
	map<Lawflags, string>::value_type(LAWFLAG_RACKETEERING, CONST_X_RACKETEERING),
	map<Lawflags, string>::value_type(LAWFLAG_EXTORTION, CONST_X_EXTORTION),
	map<Lawflags, string>::value_type(LAWFLAG_ARMEDASSAULT, CONST_FELONY_ASSAULT),
	map<Lawflags, string>::value_type(LAWFLAG_ASSAULT, CONST_MISDEMEANOR_ASSAULT),
	map<Lawflags, string>::value_type(LAWFLAG_CARTHEFT, CONST_X_GRAND_THEFT_AUTO),
	map<Lawflags, string>::value_type(LAWFLAG_CCFRAUD, CONST_X_CREDIT_CARD_FRAUD_LOWERCASE),
	map<Lawflags, string>::value_type(LAWFLAG_THEFT, CONST_PETTY_LARCENY),
	map<Lawflags, string>::value_type(LAWFLAG_PROSTITUTION, CONST_X_PROSTITUTION),
};
map<Lawflags, string> crimeBlockThree = {
	map<Lawflags, string>::value_type(LAWFLAG_COMMERCE, CONST_INTERFERENCE_WITH_INTERSTATE_COMMERCE),
	map<Lawflags, string>::value_type(LAWFLAG_INFORMATION, CONST_UNLAWFUL_ACCESS_OF_AN_INFORMATION_SYSTEM),
	map<Lawflags, string>::value_type(LAWFLAG_BURIAL, CONST_X_UNLAWFUL_BURIAL),
	map<Lawflags, string>::value_type(LAWFLAG_BREAKING, CONST_X_BREAKING_AND_ENTERING),
	map<Lawflags, string>::value_type(LAWFLAG_VANDALISM, CONST_X_VANDALISM),
	map<Lawflags, string>::value_type(LAWFLAG_RESIST, CONST_X_RESISTING_ARREST),
	map<Lawflags, string>::value_type(LAWFLAG_DISTURBANCE, CONST_X_DISTURBING_THE_PEACE),
	map<Lawflags, string>::value_type(LAWFLAG_PUBLICNUDITY, CONST_INDECENT_EXPOSURE),
	map<Lawflags, string>::value_type(LAWFLAG_LOITERING, CONST_X_LOITERING),
};
map<Lawflags, bool> crimeMultipleCounts = {
	map<Lawflags, bool>::value_type(LAWFLAG_TREASON,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_TERRORISM,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_MURDER,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_KIDNAPPING,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BANKROBBERY,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ARSON,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_SPEECH,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BROWNIES,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ESCAPED,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_HELPESCAPE,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_JURY,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_RACKETEERING, false),
	map<Lawflags, bool>::value_type(LAWFLAG_EXTORTION,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ARMEDASSAULT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_ASSAULT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_CARTHEFT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_CCFRAUD,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_THEFT,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_PROSTITUTION,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_COMMERCE,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_INFORMATION,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BURIAL,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_BREAKING,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_VANDALISM,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_RESIST, false),
	map<Lawflags, bool>::value_type(LAWFLAG_DISTURBANCE,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_PUBLICNUDITY,  true),
	map<Lawflags, bool>::value_type(LAWFLAG_LOITERING, false),
};
enum LegalDefense {
	UNDECIDED = -1,
	COURT_ATTORNEY = 0,
	SELF_REPRESENT = 1,
	PLEAD_GUILTY = 2,
	ACE_ATTORNEY = 3,
	SLEEPER_ATTORNEY = 4
};

//#endif//JUSTICE_CPP
//#endif// INCLUDES_H_INCLUDED
