




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

//

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
//#ifdef	NEWS_CPP
// news.cpp

#include "../creature/creature.h"
////

//#include "../creature/deprecatedCreatureA.h"
//#include "../creature/deprecatedCreatureB.h"

#include "../creature/deprecatedCreatureC.h"
//#include "../creature/deprecatedCreatureD.h"

////
#include "../locations/locations.h"
#include "../common/commonactions.h"
//#include "../common/stringconversion.h"
inline char* strcpy(char* dest, const std::string& src) { return strcpy(dest, src.c_str()); }
inline char* strcat(char* dest, const std::string& src) { return strcat(dest, src.c_str()); }
inline char* strcat(char* dest, long src) { return strcat(dest, tostring(src)); }
#include "../common/getnames.h"
#include "../common/misc.h"
// from cursesgraphics.h
#define CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZONTAL 0xc5
#define CH_FULL_BLOCK 0xdb
#define CH_LIGHT_SHADE 0xb0
#define CH_MEDIUM_SHADE 0xb1
#define CH_DARK_SHADE 0xb2
// from daily.h
int monthday();
#include "../cursesAlternative.h"
#include "../set_color_support.h"
#include "../common/creaturePool.h"
#include "../locations/locationsPool.h"
#include "../cursesmovie.h"
vector<Deprecatednewsstoryst *> newsstory;
Deprecatednewsstoryst* lastNewsStory() {
	return newsstory[len(newsstory) - 1];
}
#include "../common/musicClass.h"

extern bool multipleCityMode;
extern CCSexposure ccsexposure;
extern char endgamestate;
extern char lcityname[CITY_NAMELEN];
extern char newscherrybusted;
extern char oldPresidentName[POLITICIAN_NAMELEN];
extern CursesMoviest movie;
extern int month;
extern int year;
extern MusicClass music;
extern short attitude[VIEWNUM];
extern short house[HOUSENUM];
extern short lawList[LAWNUM];
extern short public_interest[VIEWNUM];
extern short senate[SENATENUM];
extern string slogan_str;
extern unsigned char bigletters[27][5][7][4];
extern unsigned char newspic[20][78][18][4];
extern unsigned char newstops[6][80][5][4];


map<short, vector<string> > newsStories;
map<short, string> cityNames;
vector<string> liberalCrime;
vector<string> AMorPM;
vector<string> book_title;
vector<string> book_title_2;
vector<string> random_nationality;
vector<string> conservative_oppose_book;
vector<string> radio_name;
vector<string> radio_name_2;
vector<string> vigilante_murder;
vector<string> why_chase_ended;
vector<string> crazy_conservative_act;
vector<string> bribe_officers;
vector<string> my_idol;
vector<string> prison_book_title;
vector<string> prison_book_title_2;
vector<string> mutilated_corpse;
vector<string> evidence_of_child_murder;
vector<string> break_in_murder_case;
vector<string> animal_research_country;
vector<string> drug_name;
vector<string> drug_name_2;
vector<string> chimp_drug_impact;
vector<string> chimp_drug_horror;
vector<string> terrorist_group;
vector<string> terrorist_plot;
vector<string> terrorist_plot_no_free_speech;
vector<string> gene_corp_name;
vector<string> gene_corp_name_2;
vector<string> gene_product_name;
vector<string> gene_product_name_2;
vector<string> gene_product_benefit;
vector<string> gene_product_cost;
vector<string> bullshit_no_free_speech;
vector<string> bullshit;
vector<string> petty_violence;
vector<string> his_her;
vector<string> older_younger;
vector<string> brother_sister;
vector<string> judge_with_prostitute;
vector<string> judge_with_prostitute_no_free_speech;
vector<string> judge_with_prostitute_full_free_speech;
vector<string> radio_host_crazy_quote;
vector<string> radio_host_lost_mind;
vector<string> family_values_company_name;
vector<string> family_values_company_name_2;
vector<string> family_values_company_name_3;
vector<string> pollution_consumption;
vector<string> pollution_consumption_2;
vector<string> i_like_polution;
vector<string> distrust_liberals;
vector<string> tech_giant_name;
vector<string> tech_giant_name_2;
vector<string> fm_radio_name;
vector<string> fm_radio_name_2;
vector<string> public_place;
vector<string> reagan_bad;
vector<string> reagan_bad_2;
vector<string> ceo_behaving_badly;
vector<string> reagan_good;
vector<string> reagan_good_2;
vector<string> cable_name;
vector<string> cable_name_2;
vector<string> cable_city;
vector<string> cable_city_2;
vector<string> ccs_adjective;
vector<string> ccs_adjective_2;
vector<string> ccs_adjective_3;
vector<string> ccs_noun;
vector<string> personalAds;
vector<string> personalAdsLG;
vector<string> caseNEWSSTORY_CCS_DEFEATED;
vector<string> caseNEWSSTORY_CCS_NOBACKERS;
vector<vector<string> > adListB;
vector<vector<string> > adList;
const int AD_LENGTH = 4;
#include "../customMaps.h"

void displaynewspicture(int p, int y);
void displaycenterednewsfont(const std::string& str, int y);
void preparepage(const Deprecatednewsstoryst ns, const bool liberalguardian);

const vector<int> randombox = {
	CH_LIGHT_SHADE,
	CH_MEDIUM_SHADE,
	CH_DARK_SHADE,
	CH_FULL_BLOCK,
	CH_BOX_DRAWINGS_LIGHT_VERTICAL_AND_HORIZONTAL,
	'*'
};
string sexdesc();
string sexwho();
string sexseek();
string sextype();

string constructeventstory(const short view, const char positive);

const int PICTURE_MUTANT_BEAST = 0;
const int PICTURE_CEO = 1;
const int PICTURE_BOOK = 2;
const int PICTURE_MELTDOWN = 3;
const int PICTURE_GENETICS = 4;
const int PICTURE_RIVERFIRE = 5;
const int PICTURE_DOLLARS = 6;
const int PICTURE_TINKYWINKY = 7;
const int PICTURE_OIL = 8;
const int PICTURE_TERRORISTS = 9;
const int PICTURE_KKK = 10;
const int PICTURE_TSHIRT = 11;

const string membersOfLCS = "Members of the Liberal Crime Squad ";
const string lcsSpokeseperson = "to a Liberal Crime Squad spokesperson.";
const string policeSpokesperson = "to a spokesperson from the police department.";
const string ACCORDING_TO_SOURCES = "  According to sources that were at the scene, ";
const string ACCORDING_TO_POLICE = "  According to police sources that were at the scene, ";
const string CONST_A_SPOKESPERSON_STATED_COMMA_QUOTE = "a spokesperson stated, \"";
const string CONST_HEARD_SAYING_COMMA_QUOTE = "heard saying, \"";
const string CONST_TWO_NIGHTS_AGO_DURING_RADIO = "two nights ago during the syndicated radio program \"";
const string CONST_HAD_COME_TO_EXPECT_WITH_ATTACKS_ON_LIBERAL_MEDIA = "had come to expect, with attacks on the \"liberal media establishment\"";
const string CONST_DOT_BUT_WHEN_THE_RADIO_ICON_SAID = "the \"elite liberal agenda\".  But when the radio icon said, \"";
const string CONST_COMMA_KNEW_THAT_QUOTE = ", knew that \"";
const string CONST_DOT_AFTER_THAT_IT_GOT_WORSE = ". After that, it just got worse and worse.\"";
const string CONST_SPACE_THE_SPOKESMAN_FURTHER_STATED = "  The spokesperson further stated, \"";
const string CONST_SCREAMED_FUCK_POLICE_AND_MORE = "screamed \"fuck the police those goddamn motherfuckers.  I got a fucking ticket this morning and I'm fucking pissed as shit.\"";
const string CONST_THE_SLOGAN = "  The slogan, \"";
const string CONST_ONE_UTTERED_THE_WORDS = "  One uttered the words, \"";
const string CONST_AS_THEY_LEFT_THEY_SHOUTED = "  As they left, they shouted, \"";
const string CONST_ONE_OF_THEM_WAS_RUMORED_TO_HAVE_CRIED_OUT = "  One of them was rumored to have cried out, \"";
const string CONST_WITNESSES_REPORTED_HEARING_THE_PHRASE = "  Witnesses reported hearing the phrase, \"";
const string CONST_ACCORDING_TO_ONE_PERSON_FAMILIAR_WITH_THE_CASE = "According to one person familiar with the case, \"";

const string CONST_REAGAN_WAS_WRONG = "Reagan was wrong";
const string CONST_CPP_IO_RB = "rb";
const string CONST_NEO_PAGAN_LOWERCASE = "neo-pagan";
const string CONST_HIM_LOWERCASE = "him";
const string CONST_BLOODS_CAPITALIZED = "Bloods";
const string CONST_HIMSELF_LOWERCASE = "himself";
const string CONST_HE_LOWERCASE_SPACE = "he ";
const string CONST_MISS_SPACE = "Miss ";
const string CONST_I_WOULD_KILL_AGAIN = "If I were to be released, I would surely kill again.\"";
const string CONST_HE_LOWERCASE = "he";
const string CONST_MAKE_THINGS_RIGHT_WITH_THE_ALMIGHTY_FATHER = "\"Make things right with the Almighty Father.\"";
const string CONST_HUSBAND_LOWERCASE = "husband";

const string CONST_BURNED_UNRECOGNIZABLE = "burned unrecognizable.  ";
const string CONST_THE_RECOVERED_BODY_WAS = "The recovered body was ";
const string CONST_THE_RECOVERED_BODIES_WERE = "The recovered bodies were ";
const string CONST_THEY_HAVE_TO_BE_STOPPED_BEFORE_THEY_KILL_AGAIN = "They have to be stopped before they kill again";
const string CONST_THIS_IS_THE_DOING_OF_THE_CONSERVATIVE_CRIME_SQUAD_BUTCHERS = "This is the doing of the Conservative Crime Squad butchers.  ";
const string CONST_NO_NAMES_NO_FACES_NOT_EVEN_WHERE_IT_HAPPENED_REALLY = "no names, no faces, not even where it happened really";
const string CONST_LOOK_IT_WAS_A_CONSERVATIVE_CRIME_SQUAD_HIT_THAT_S_ALL_WE_KNOW = "Look, it was a Conservative Crime Squad hit, that's all we know, ";
const string CONST_JUST_COVERING_IT_UP = "just covering it up";
const string CONST_WITH_IN_THE_PAST_WHEN_THE_POLICE_CAN_T_FIGURE_THIS_ONE_OUT_THEY_RE = "with in the past.  *When* the police can't figure this one out, they're ";
const string CONST_KNOWN_TO_WORK_WITH_SEVERAL_CORPORATIONS_WE_VE_HAD_CONFRONTATIONS = "known to work with several corporations we've had confrontations ";
const string CONST_THIS_MASSACRE_HAS_THE_SIGNATURE_MARK_OF_A_GROUP_OF_MERCENARIES = "This massacre has the signature mark of a group of mercenaries ";
const string CONST_IT_WAS_EXECUTION_STYLE_PROFESSIONAL_WE_VE_GOT_NOTHING = "It was execution style.  Professional.  We've got nothing";
const string CONST_INSPIRED_BY_THE_CONSERVATIVE_MEDIA_S_BRAINWASHING_PROPAGANDA = "inspired by the Conservative media's brainwashing propaganda";
const string CONST_WE_HAVE_REASON_TO_BELIEVE_THAT_THIS_BRUTAL_MASSACRE_WAS = "We have reason to believe that this brutal massacre was ";
const string CONST_BEEN_BITE_MARKS_NOTHING_RECOGNIZABLE_LEFT_COMPLETE_CARNAGE = "been bite marks.  Nothing recognizable left.  Complete carnage.";
const string CONST_BURNED_STABBED_WITH_MAYBE_PITCHFORKS_THERE_MAY_HAVE = "Burned...  stabbed with, maybe, pitchforks.  There may have ";
const string CONST_INTELLIGENCE_COMMUNITY = "intelligence community";
const string CONST_PREVIOUS_ACTIONS_TO_UNCOVER_HUMAN_RIGHTS_ABUSES_AND_CORRUPTION_IN_THE = "previous actions to uncover human rights abuses and corruption in the ";
const string CONST_CARRIED_OUT_BY_THE_CENTRAL_INTELLIGENCE_AGENCY_IN_RETALIATION_FOR_OUR = "carried out by the Central Intelligence Agency in retaliation for our ";
const string CONST_WE_HAVE_STRONG_EVIDENCE_THAT_THIS_WAS_AN_EXTRA_JUDICIAL_SLAUGHTER = "We have strong evidence that this was an extra-judicial slaughter ";
const string CONST_D_MND_ST_THING_I_VE_EVER_SEEN = "D*mnd*st thing I've ever seen";
const string CONST_DAMNEDEST_THING_I_VE_EVER_SEEN = "Damnedest thing I've ever seen";
const string CONST_CRAZIEST_THING_I_VE_EVER_SEEN = "[Craziest] thing I've ever seen";
const string CONST_FINGERPRINTS_LIKE_IT_WAS_ALL_SMOOTH = "fingerprints.  Like, it was all smooth.  ";
const string CONST_THE_BODY_HAD_NO_FACE_OR = "The body had no face or ";
const string CONST_THE_BODIES_HAD_NO_FACES_OR = "The bodies had no faces or ";
const string CONST_ACCORDING_TO_AN_LCS_SPOKESPERSON = "According to an LCS spokesperson, \"";
const string CONST_OF_THE_LCS_TARGETED_SIMPLY_DUE_TO_THEIR_POLITICAL_BELIEFS = "of the LCS targeted simply due to their political beliefs.  ";
const string CONST_VICTIM_WAS_A_MEMBER = "victim was a member ";
const string CONST_VICTIMS_WERE_MEMBERS = "victims were members ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_CLAIMED_THAT_THE = "  The Liberal Crime Squad has claimed that the ";
const string CONST_UNWILLING_TO_PURSUE_THE_CASE_WITH_ANY_SERIOUS_EFFORT = "unwilling to pursue the case with any serious effort.";
const string CONST_THE_POLICE_HAVE_OPENED_AN_INVESTIGATION_INTO_THE_MASSACRE_BUT_SEEM = "  The police have opened an investigation into the massacre, but seem ";
const string CONST_PRIVATELY_SOURCES_IN_THE_DEPARTMENT_CONFIDE_THAT_THERE_AREN_T_ANY_LEADS = "  Privately, sources in the department confide that there aren't any leads.  ";
const string CONST_THE_POLICE_DEPARTMENT_THE_MATTER_IS_UNDER_INVESTIGATION_AS_A_HOMICIDE = "the police department, the matter is under investigation as a homicide.";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR = "  According to a spokesperson for ";
const string CONST_YESTERDAY = " yesterday.";
const string CONST_FOUND_IN_THE = " found in the ";
const string CONST_A_BODY_WAS = " A body was ";
const string CONST_TWO_BODIES_WERE = " Two bodies were ";
const string CONST_BODIES_WERE = " bodies were ";
const string CONST_MASSACRE = "MASSACRE";
const string CONST_MYSTERIOUS = "MYSTERIOUS";
const string CONST_CCS_MASSACRE = "CCS MASSACRE";
const string CONST_BEFORE_PASSING_OUT = "\" before passing out.";
const string CONST_WAS_FOUND_PAINTED_ON_THE_WALLS = "\" was found painted on the walls.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ENDED_THE_DANGEROUS_HIGH_SPEED_CHASE_IN_ORDER_TO_PROTECT_THE_PUBLIC_AND_ATTEMPTED_TO_ESCAPE_ON_FOOT = "The Liberal Crime Squad ended the dangerous high-speed chase in order to protect the public, and attempted to escape on foot.  ";
const string CONST_THERE_WAS_ALSO_A_FOOT_CHASE_WHEN_THE_SUSPECT_OR_SUSPECTS_BAILED_OUT_AFTER_THE_HIGH_SPEED_PURSUIT = "There was also a foot chase when the suspect or suspects bailed out after the high-speed pursuit.  ";
const string CONST_DETAILS_ABOUT_INJURIES_WERE_NOT_RELEASED = "Details about injuries were not released.  ";
const string CONST_ONE_VEHICLE_CRASHED = "One vehicle crashed.  ";
const string CONST_VEHICLES_CRASHED = " vehicles crashed.  ";
const string CONST_PURSUIT_OF_THE_LCS = "pursuit of the LCS.  ";
const string CONST_CONSERVATIVE_OPERATIVES_ENGAGED_IN_A_RECKLESS = "  Conservative operatives engaged in a reckless ";
const string CONST_FOLLOWING_THE_INCIDENT = "following the incident.  ";
const string CONST_IT_IS_KNOWN_THAT_THERE_WAS_A_HIGH_SPEED_CHASE = "  It is known that there was a high-speed chase ";
const string CONST_PICKED_LOCKS = "picked locks";
const string CONST_UNLAWFUL_ENTRY = "unlawful entry";
const string CONST_BROKE_DOWN_DOORS = "broke down doors";
const string CONST_BREAKING_AND_ENTERING_LOWERCASE = "breaking and entering";
const string CONST_MARKED_THE_SITE_FOR_LIBERATION = "marked the site for Liberation";
const string CONST_VANDALISM_LOWERCASE = "vandalism";
const string CONST_DAMAGED_ENEMY_INFRASTRUCTURE = "damaged enemy infrastructure";
const string CONST_DESTRUCTION_OF_PRIVATE_PROPERTY = "destruction of private property";
const string CONST_LIBERATED_ABUSED_ANIMALS = "liberated abused animals";
const string CONST_TAMPERING_WITH_LAB_ANIMALS = "tampering with lab animals";
const string CONST_LIBERATED_ENEMY_RESOURCES = "liberated enemy resources";
const string CONST_THEFT_LOWERCASE = "theft";
const string CONST_ENGAGED_IN_COMBAT_WITH_CONSERVATIVE_FORCES = "engaged in combat with Conservative forces";
const string CONST_VIOLENCE = "violence";
const string CONST_MORE_VIOLENCE = "more violence";
const string CONST_MURDER_LOWERCASE = "murder";
const string CONST_SET_FIRE_TO_CONSERVATIVE_PROPERTY = "set fire to Conservative property";
const string CONST_ARSON_LOWERCASE = "arson";
const string CONST_ENGAGED_IN = "engaged in ";
const string CONST_FURTHER_DETAILS_ARE_SKETCHY_BUT_POLICE_SOURCES_SUGGEST_THAT_THE_CCS = "  Further details are sketchy, but police sources suggest that the CCS ";
const string CONST_THE_LIBERAL_CRIME_SQUAD = "  The Liberal Crime Squad ";
const string CONST_FURTHER_DETAILS_ARE_SKETCHY_BUT_POLICE_SOURCES_SUGGEST_THAT_THE_LCS = "  Further details are sketchy, but police sources suggest that the LCS ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_COMPANY_S_CONSERVATIVE_CORRUPTION = "  The Liberal Crime Squad was attempting to uncover the company's Conservative corruption.";
const string CONST_EXECUTIVES_ON_THE_SCENE_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING = "executives on the scene seemed very nervous about something.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_CEO_S_CONSERVATIVE_CORRUPTION = "  The Liberal Crime Squad was attempting to uncover the CEO's Conservative corruption.";
const string CONST_THE_OWNER_OF_THE_HOUSE_SEEMED_VERY_FRANTIC_ABOUT_SOME_MISSING_PROPERTY = "the owner of the house seemed very frantic about some missing property.";
const string CONST_LIBERAL_CRIME_SQUAD_INFILTRATION_SPECIALISTS_WORKED_TO_LIBERATE_WEAPONS_FROM_THE_OPPRESSORS = "  Liberal Crime Squad infiltration specialists worked to liberate weapons from the oppressors.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_BREAK_INTO_THE_ARMORY = "the Liberal Crime Squad attempted to break into the armory.";
const string CONST_LIBERAL_CRIME_SQUAD_COMPUTER_SPECIALISTS_WORKED_TO_LIBERATE_INFORMATION_FROM_CIA_COMPUTERS = "  Liberal Crime Squad computer specialists worked to liberate information from CIA computers.";
const string CONST_INTELLIGENCE_OFFICIALS_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING = "intelligence officials seemed very nervous about something.";
const string CONST_MAY_HAVE_INTERFERED_WITH_JURY_DELIBERATIONS = "may have interfered with jury deliberations.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_APOLOGIZED_OVER_REPORTS_THAT_THE_OPERATION = "  The Liberal Crime Squad has apologized over reports that the operation ";
const string CONST_TRUST_AND_ATTEMPTED_TO_INFLUENCE_A_JURY = "trust and attempted to influence a jury.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_VIOLATED_THE_SACRED = "the Liberal Crime Squad allegedly violated the sacred ";
const string CONST_AT_THE_PRISON = "at the prison.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_ABUSIVE_CONSERVATIVE_CONDITIONS = "  The Liberal Crime Squad attempted to rescue innocent people from the abusive Conservative conditions ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_PRISONERS_WHILE_IN_THE_FACILITY = "the Liberal Crime Squad allegedly freed prisoners while in the facility.";
const string CONST_SAVING_THEM_FROM_THE_HIGHLY_CORRUPT_CONSERVATIVE_JUSTICE_SYSTEM = "saving them from the highly corrupt Conservative justice system.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_COURTHOUSE_LOCKUP = "  The Liberal Crime Squad attempted to rescue innocent people from the courthouse lockup, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_COURTHOUSE_LOCKUP = "the Liberal Crime Squad allegedly freed or attempted to free prisoners from the courthouse lockup.";
const string CONST_HOPING_TO_ACQUIRE_THE_RESOURCES_TO_OVERCOME_EVIL = "hoping to acquire the resources to overcome evil.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_DEMANDED_ACCESS_TO_THE_BANK_VAULT = "  The Liberal Crime Squad demanded access to the bank vault, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_THREATENED_INNOCENT_BYSTANDERS_IN_ORDER_TO_ROB_THE_BANK_VAULT = "the Liberal Crime Squad threatened innocent bystanders in order to rob the bank vault.";
const string CONST_SHOWING_THE_TRIUMPH_OF_LIBERAL_IDEALS_OVER_CONSERVATIVE_ECONOMICS = "showing the triumph of Liberal ideals over Conservative economics.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT = "  The Liberal Crime Squad opened the bank vault, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT_WHICH_HELD_MORE_THAN_100_000_AT_THE_TIME = "the Liberal Crime Squad opened the bank vault, which held more than $100,000 at the time.";
const string CONST_SAVING_THEM_FROM_TORTURE_AND_BRUTALITY_AT_THE_HANDS_OF_CONSERVATIVE_POLICE_INTERROGATORS = "saving them from torture and brutality at the hands of Conservative police interrogators.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_POLICE_LOCKUP = "  The Liberal Crime Squad attempted to rescue innocent people from the police lockup, ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_POLICE_LOCKUP = "the Liberal Crime Squad allegedly freed or attempted to free prisoners from the police lockup.";
const string CONST_DEMONSTRATING_THE_EXTREME_VULNERABILITY_AND_DANGER_OF_NUCLEAR_POWER_PLANTS = "demonstrating the extreme vulnerability and danger of Nuclear Power Plants. ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_BROUGHT_THE_REACTOR_TO_THE_VERGE_OF_A_NUCLEAR_MELTDOWN = "  The Liberal Crime Squad brought the reactor to the verge of a nuclear meltdown, ";
const string CONST_REACTOR = "reactor.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_NEARLY_CAUSED_A_CATASTROPHIC_MELTDOWN_OF_THE_NUCLEAR = "the Liberal Crime Squad nearly caused a catastrophic meltdown of the nuclear ";
const string CONST_DEMONSTRATING_THE_EXTREME_DANGERS_OF_NUCLEAR_WASTE = "demonstrating the extreme dangers of Nuclear Waste. ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_TAMPERED_WITH_THE_STATE_S_WATER_SUPPLY_YESTERDAY = "  The Liberal Crime Squad tampered with the state's water supply yesterday, ";
const string CONST_YESTERDAY_BY_TAMPERING_WITH_EQUIPMENT_ON_THE_SITE = "yesterday by tampering with equipment on the site.";
const string CONST_THE_LIBERAL_CRIME_SQUAD_CONTAMINATED_THE_STATE_S_WATER_SUPPLY = "the Liberal Crime Squad contaminated the state's water supply";
const string CONST_THE_NAME_OF_THE_OFFICER_HAS_NOT_BEEN_RELEASED_PENDING_NOTIFICATION_OF_THE_OFFICER_S_FAMILY = "The name of the officer has not been released pending notification of the officer's family.";
const string CONST_THE_NAMES_OF_THE_OFFICERS_HAVE_NOT_BEEN_RELEASED_PENDING_NOTIFICATION_OF_THEIR_FAMILIES = "The names of the officers have not been released pending notification of their families.";
const string CONST_A_PASSERBY_HAD_ALLEGEDLY_SPOTTED_THE_SUSPECT_COMMITTING_A_CAR_THEFT = "A passerby had allegedly spotted the suspect committing a car theft.  ";
const string CONST_APPEARED_TO_BE_A_CORPSE_THROUGH_AN_EMPTY_LOT = "appeared to be a corpse through an empty lot.  ";
const string CONST_A_PASSERBY_ALLEGEDLY_CALLED_THE_AUTHORITIES_AFTER_SEEING_THE_SUSPECT_DRAGGING_WHAT = "A passerby allegedly called the authorities after seeing the suspect dragging what ";
const string CONST_THE_SUSPECT_WAS_ALLEGEDLY_SELLING_POT_BROWNIES = "The suspect was allegedly selling \"pot brownies\".  ";
const string CONST_THE_INCIDENT_APPARENTLY_OCCURRED_AS_A_RESPONSE_TO_A_PUBLIC_NUDITY_COMPLAINT = "The incident apparently occurred as a response to a public nudity complaint.  ";
const string CONST_ATTEMPTING_TO_PERFORM_AN_ARREST = " attempting to perform an arrest.  ";
const string CONST_A_POLICE_OFFICER_THAT_WAS = "a police officer that was";
const string CONST_POLICE_OFFICERS_THAT_WERE = " police officers that were";
const string CONST_KILLED = "killed ";
const string CONST_A_SUSPECT_WHOSE_IDENTITY_IS_UNCLEAR = "  A suspect, whose identity is unclear, ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT = "according to a spokesperson from the police department.";
const string CONST_A_ROUTINE_ARREST_WENT_HORRIBLY_WRONG_YESTERDAY = "A routine arrest went horribly wrong yesterday, ";
const string CONST_WHILE_THEY_WERE_ATTEMPTING_TO_PERFORM_AN_ARREST = " while they were attempting to perform an arrest.  ";
const string CONST_THE_POLICE_OFFICER = "the police officer ";
const string CONST_OFFICERS = " officers ";
const string CONST_RADICAL_POLITICAL_GROUP_KNOWN_AS_THE_LIBERAL_CRIME_SQUAD_IS_BELIEVED_TO_HAVE_KILLED = "radical political group known as the Liberal Crime Squad, is believed to have killed ";
const string CONST_A_SUSPECT_IDENTIFIED_ONLY_AS_A_MEMBER_OF_THE = "  A suspect, identified only as a member of the ";
const string CONST_KILLED_IN_THE_LINE_OF_DUTY_YESTERDAY = " killed in the line of duty yesterday, ";
const string CONST_A_POLICE_OFFICER_WAS = "A police officer was";
const string CONST_POLICE_OFFICERS_WERE = " police officers were";
const string CONST_SEVERAL = "Several";
const string CONST_TWO_UPPERCASE = "Two";
const string CONST_OF_CULTURE = "OF CULTURE";
const string CONST_THE_DEATH = "THE DEATH";
const string CONST_NEW_JOBS = "NEW JOBS";
const string CONST_LOOKING_UP = "LOOKING UP";
const string CONST_FALL_FASHIONS_ARE_PREVIEWED_IN_STORES_ACROSS_THE_COUNTRY = "Fall fashions are previewed in stores across the country.";
const string CONST_FALL_FASHIONS_HIT_THE_STORES_ACROSS_THE_COUNTRY = "Fall fashions hit the stores across the country.";
const string CONST_THEY_ARE_HERE = "THEY ARE HERE";
const string CONST_JUSTICE_AMOK = "JUSTICE AMOK";
const string CONST_GM_FOOD_FAIRE = "GM FOOD FAIRE";
const string CONST_FREE_SPEECH_ADVOCATES_FIGHT_HARD_TO_LET_A_WHITE_SUPREMACIST_RALLY_TAKE_PLACE = "Free speech advocates fight hard to let a white supremacist rally take place.";
const string CONST_HATE_RALLY = "HATE RALLY";
const string CONST_DODGED_BULLET = "DODGED BULLET";
const string CONST_HOSTAGE_SLAIN = "HOSTAGE SLAIN";
const string CONST_BASTARDS = "BASTARDS";
const string CONST_JERKS = "[JERKS]";
const string CONST_APE_EXPLORERS = "APE EXPLORERS";
const string CONST_OPEC_CUTS_OIL_PRODUCTION_SHARPLY_IN_RESPONSE_TO_A_US_FOREIGN_POLICY_DECISION = "OPEC cuts oil production sharply in response to a US foreign policy decision.";
const string CONST_OIL_CRUNCH = "OIL CRUNCH";
const string CONST_A_NEW_BOOK_LAUDING_REAGAN_AND_THE_GREATEST_GENERATION = ": A new book lauding Reagan and the greatest generation.";
const string CONST_REAGAN_THE_MAN = "REAGAN THE MAN";
const string CONST_SAVES_LIVES = "SAVES LIVES";
const string CONST_ARMED_CITIZEN = "ARMED CITIZEN";
const string CONST_END_IN_TEARS = "END IN TEARS";
const string CONST_OUR_BOYS_DEFEND_FREEDOM_ONCE_AGAIN_DEFEATING_AN_EVIL_DICTATOR = "Our boys defend freedom once again, defeating an evil dictator.";
const string CONST_BIG_VICTORY = "BIG VICTORY";
const string CONST_LET_S_FRY_EM = "LET'S FRY 'EM";
const string CONST_JERRY_FALWELL_EXPLAINS_THE_TRUTH_ABOUT_TINKY_WINKY_AGAIN = "Jerry Falwell explains the truth about Tinky Winky.  Again.";
const string CONST_KINKY_WINKY = "KINKY WINKY";
const string CONST_AM_IMPLOSION = "AM IMPLOSION";
const string CONST_REGULARLY_VISITS_PROSTITUTES = "regularly visits prostitutes.";
const string CONST_REGULARLY_DONATES_TO_SPERM_BANKS = "regularly [donates to sperm banks].";
const string CONST_REGULARLY_VISITS_WORKING_WOMEN = "regularly visits [working women].";
const string CONST_THIS_MAJOR_CEO = "This major CEO ";
const string CONST_AMERICAN_CEO = "AMERICAN CEO";
const string CONST_AN_ENORMOUS_COMPANY_FILES_FOR_BANKRUPTCY_SHATTERING_THE_PREVIOUS_RECORD = "An enormous company files for bankruptcy, shattering the previous record.";
const string CONST_BELLY_UP = "BELLY UP";
const string CONST_THE_OHIO_RIVER_CAUGHT_ON_FIRE_AGAIN = "The Ohio River caught on fire again.";
const string CONST_RING_OF_FIRE = "RING OF FIRE";
const string CONST_A_T_SHIRT_IN_A_STORE_IS_FOUND_SCRAWLED_WITH_A_MESSAGE_FROM_A_SWEATSHOP_WORKER = "A T-shirt in a store is found scrawled with a message from a sweatshop worker.";
const string CONST_CHILD_S_PLEA = "CHILD'S PLEA";
const string CONST_IN_CONTEMPT = "IN CONTEMPT";
const string CONST_OVER_A_HUNDRED_PEOPLE_BECOME_SICK_FROM_GENETICALLY_MODIFIED_FOOD = "Over a hundred people become sick from genetically modified food.";
const string CONST_KILLER_FOOD = "KILLER FOOD";
const string CONST_BOOK_BANNED = "BOOK BANNED";
const string CONST_THE_FBI_FILES = "THE FBI FILES";
const string CONST_ON_THE_INSIDE = "ON THE INSIDE";
const string CONST_A_MUTANT_ANIMAL_HAS_ESCAPED_FROM_A_LAB_AND_KILLED_THIRTY_PEOPLE = "A mutant animal has escaped from a lab and killed thirty people.";
const string CONST_HELL_ON_EARTH = "HELL ON EARTH";
const string CONST_A_NUCLEAR_POWER_PLANT_SUFFERS_A_CATASTROPHIC_MELTDOWN = "A nuclear power plant suffers a catastrophic meltdown.";
const string CONST_MELTDOWN = "MELTDOWN";
const string CONST_A_NEW_BOOK_FURTHER_DOCUMENTING_THE_OTHER_SIDE_OF_REAGAN = ": A new book further documenting the other side of Reagan.";
const string CONST_REAGAN_FLAWED = "REAGAN FLAWED";
const string CONST_MASS_SHOOTING_ALLCAPS = "MASS SHOOTING";
const string CONST_NIGHTMARE = "NIGHTMARE";
const string CONST_IS_THE_LATEST_MILITARY_INVASION_YET_ANOTHER_QUAGMIRE = "Is the latest military invasion yet another quagmire?";
const string CONST_CASUALTIES_MOUNT = "CASUALTIES MOUNT";
const string CONST_JUSTICE_DEAD = "JUSTICE DEAD";
const string CONST_CRIME_OF_HATE = "CRIME OF HATE";
const string CONST_CLINIC_MURDER = "CLINIC MURDER";
const string CONST_NEWSPIC_CPC = "newspic.cpc";
const string CONST_NEWSTOPS_CPC = "newstops.cpc";
const string CONST_LARGECAP_CPC = "largecap.cpc";
const string CONST_SQUAD_RAMPAGE = "SQUAD RAMPAGE";
const string CONST_LIBERAL_CRIME = "LIBERAL CRIME";
const string CONST_LCS_SORRY = "LCS SORRY";
const string CONST_LCS_RAMPAGE = "LCS RAMPAGE";
const string CONST_SQUAD_STRIKES = "SQUAD STRIKES";
const string CONST_LCS_STRIKES = "LCS STRIKES";
const string CONST_HEROIC_STRIKE = "HEROIC STRIKE";
const string CONST_LCS_HITS_TV = "LCS HITS TV";
const string CONST_LCS_HITS_AM = "LCS HITS AM";
const string CONST_LCS_HITS_CORP = "LCS HITS CORP";
const string CONST_POLLUTER_HIT = "POLLUTER HIT";
const string CONST_NO_JUSTICE = "NO JUSTICE";
const string CONST_EVIL_RESEARCH = "EVIL RESEARCH";
const string CONST_LCS_VS_CIA = "LCS VS CIA";
const string CONST_PRISON_WAR = "PRISON WAR";
const string CONST_LCS_VS_COPS = "LCS VS COPS";
const string CONST_MELTDOWN_RISK = "MELTDOWN RISK";
const string CONST_CLASS_WAR = "CLASS WAR";
const string CONST_UNSTOPPABLE = "UNSTOPPABLE";
const string CONST_CCS_RAMPAGE = "CCS RAMPAGE";
const string CONST_CCS_STRIKES = "CCS STRIKES";
const string CONST_CRIME_SQUAD = "CRIME SQUAD";
const string CONST_LCS_MARTYRS = "LCS MARTYRS";
const string CONST_POLICE_KILL = "POLICE KILL";
const string CONST_TRAGIC_END = "TRAGIC END";
const string CONST_LCS_SIEGE = "LCS SIEGE";
const string CONST_OFF_COPS = "OFF COPS";
const string CONST_LCS_FIGHTS = "LCS FIGHTS";
const string CONST_POLICE_SIEGE = "POLICE SIEGE";
const string CONST_LCS_ESCAPES = "LCS ESCAPES";
const string CONST_POLICE_KILLED = "POLICE KILLED";
const string CONST_RAIDS_END_CCS = "RAIDS END CCS";
const string CONST_FBI_HUNTS_CCS = "FBI HUNTS CCS";
const string CONST_ASSASSINATED = "ASSASSINATED";
const string CONST_MISSING = "MISSING";
const string CONST_RESCUED = "RESCUED";
const string CONST_FOUND_DEAD = "FOUND DEAD";
const string CONST_BELIEVED_DEAD = "BELIEVED DEAD";
const string CONST_IMPEACHED = "IMPEACHED";
const string CONST_LOWER_BORDER_WITH_CORNERS = "ศออออออออออออออออออออออออออออออออออออออออออออออออออออผ";
const string CONST_AUDIENCE_AND_VIEWERS_NATIONWIDE_FEEL_ITS_PAIN = "บ   audience and viewers nationwide feel its pain.   บ";
const string CONST_POPULAR_AFTERNOON_TALK_SHOW_THE_STUDIO = "บ   popular  afternoon  talk  show.    The  studio   บ";
const string CONST_A_FAILED_PARTIAL_BIRTH_ABORTION_GOES_ON_A = "บ     A  failed partial  birth abortion  goes on a   บ";
const string CONST_UPPER_BORDER_WITH_CORNERS = "ษออออออออออออออออออออออออออออออออออออออออออออออออออออป";
const string CONST_ABORT_CMV = "abort.cmv";
const string CONST_BY_IMPRESSIVE_ADVERTISING_AMERICA_TUNES_IN = "บ   by impressive  advertising, America  tunes in.   บ";
const string CONST_NEW_ANCHOR_FOR_ONE_OF_ITS_NEWS_SHOWS_GUIDED = "บ   new anchor for  one of its news shows.  Guided   บ";
const string CONST_A_MAJOR_CABLE_NEWS_CHANNEL_HAS_HIRED_A_SLICK = "บ     A major Cable News channel has hired a slick   บ";
const string CONST_ANCHOR_CMV = "anchor.cmv";
const string CONST_ADVERTISING_BLITZ_IT_S_BOUND_TO_BE_POPULAR = "บ   advertising  blitz, it's bound  to be popular.   บ";
const string CONST_BEGINS_AIRING_THIS_WEEK_WITH_THE_NATIONWIDE = "บ   begins airing  this week.  With the nationwide   บ";
const string CONST_A_NEW_SHOW_GLAMORIZING_THE_LIVES_OF_THE_RICH = "บ     A new show glamorizing the lives of the rich   บ";
const string CONST_GLAMSHOW_CMV = "glamshow.cmv";
const string CONST_VIEWERS_ACROSS_THE_NATION_WERE_LISTENING = "บ   viewers  across  the  nation  were  listening.   บ";
const string CONST_BRIGHT_LIBERAL_GUEST_FINISH_A_SENTENCE_MANY = "บ   bright Liberal guest  finish a sentence.  Many   บ";
const string CONST_A_CABLE_NEWS_ANCHOR_ACCIDENTALLY_LET_A = "บ     A  Cable  News  anchor  accidentally  let  a   บ";
const string CONST_NEWSCAST_CMV = "newscast.cmv";
const string CONST_SPACE_WITH_SPACE = " with ";
const string CONST_TONIGHT_ON_A_CABLE_NEWS_CHANNEL = "Tonight on a Cable News channel: ";
const string CONST_TAPED_BY_A_PASSERBY_AND_SATURATES_THE_NEWS = "บ   taped by  a passerby  and saturates  the news.   บ";
const string CONST_LOS_ANGELES_AGAIN_THIS_TIME_THE_INCIDENT = "บ   Los Angeles again.  This time, the incident is   บ";
const string CONST_THE_POLICE_HAVE_BEATEN_A_BLACK_MAN_IN = "บ     The  police  have  beaten  a  black  man  in   บ";
const string CONST_LACOPS_CMV = "lacops.cmv";
const string CONST_WHILE_RESISTING_CAPTURE_ACCORDING_TO_A_PRISON_SPOKESPERSON = " while \"resisting capture\", according to a prison spokesperson.";
const string CONST_BEATEN_TO_DEATH = "beaten to death";
const string CONST_ALSO_HARMED = "[also harmed]";
const string CONST_THE_PRISONER_WAS = ".  The prisoner was ";
const string CONST_ALTAR = " altar";
const string CONST_SATANIC = "Satanic";
const string CONST_SACRIFICED_THE_GUARD_ON_A_MAKESHIFT = "sacrificed the guard on a makeshift ";
const string CONST_PERFORMED_DEADLY_EXPERIMENTS_ON_THE_GUARD_UNHEARD_OF_SINCE_DR_MENGELE = "performed deadly experiments on the guard unheard of since Dr. Mengele";
const string CONST_EATEN_THE_GUARD_S_LIVER_WITH_SOME_FAVA_BEANS_AND_A_NICE_CHIANTI = "eaten the guard's liver with some fava beans and a nice chianti";
const string CONST_BURNT_THE_GUARD_TO_A_CRISP_USING_A_LIGHTER_AND_SOME_GASOLINE = "burnt the guard to a crisp using a lighter and some gasoline";
const string CONST_TRICKED_ANOTHER_GUARD_INTO_SHOOTING_THE_GUARD_DEAD = "tricked another guard into shooting the guard dead";
const string CONST_OFF = " off";
const string CONST_HER = "her";
const string CONST_TAKEN_THE_GUARD_TO_THE_EXECUTION_CHAMBER_AND_FINISHED = "taken the guard to the execution chamber and finished ";
const string CONST_THROWN_THE_GUARD_OUT_THE_TOP_STOREY_WINDOW = "thrown the guard out the top-storey window";
const string CONST_ELECTROCUTED_THE_GUARD_WITH_HIGH_VOLTAGE_WIRES = "electrocuted the guard with high-voltage wires";
const string CONST_HIT_ALL_36_PRESSURE_POINTS_OF_DEATH_ON_THE_GUARD = "hit all 36 pressure points of death on the guard";
const string CONST_CRIPS = "Crips";
const string CONST_POISONED_THE_GUARD_WITH_DRUGS_SMUGGLED_INTO_THE_PRISON_BY_THE = "poisoned the guard with drugs smuggled into the prison by the ";
const string CONST_OWN_GUN = " own gun";
const string CONST_SHOT_THE_GUARD_WITH = "shot the guard with ";
const string CONST_CELL = " cell";
const string CONST_SMASHED_THE_GUARD_S_SKULL_WITH_THE_TOILET_SEAT_FROM = "smashed the guard's skull with the toilet seat from ";
const string CONST_CHEWED_OUT_THE_GUARD_S_THROAT = "chewed out the guard's throat";
const string CONST_STRANGLED_THE_GUARD_TO_DEATH_WITH_A_KNOTTED_BED_SHEET = "strangled the guard to death with a knotted bed sheet";
const string CONST_SLIT_THE_GUARD_S_THROAT_WITH_A_SHANK = "slit the guard's throat with a shank";
const string CONST_KILLED_THE_GUARD = "killed the guard";
const string CONST_HARMED_THE_GUARD = "[harmed] the guard";
const string CONST_HAD_ALREADY = " had already ";
const string CONST_THE_HOSTAGE_BUT = "the hostage, but ";
const string CONST_THE_TOWER_WAS_BREACHED_IN_AN_ATTEMPT_TO_REACH = "  The tower was breached in an attempt to reach ";
const string CONST_IMMA_KILL_ALL_YOU_B_TCHES_STARTIN_WITH_THIS_M_TH_F_CK_R_HERE = "Imma kill all you b*tches, startin' with this m*th*f*ck*r here.";
const string CONST_I_WILL_HARM_ALL_POLICE_OFFICERS_STARTIN_WITH_THIS_ONE_HERE = "[I will harm all police officers], startin' with this [one] here.";
const string CONST_IMMA_KILL_ALL_YOU_BITCHES_STARTIN_WITH_THIS_MOTHAFUCKER_HERE = "Imma kill all you bitches, startin' with this mothafucker here.";
const string CONST_WHY_THE_F_CK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the f*ck am I talkin' to you?  I'd rather kill this pig.";
const string CONST_WHY_AM_I_TALKIN_TO_YOU_I_D_RATHER_HARM_THIS_POLICE_OFFICER = "Why [am I] talkin' to you?  I'd rather [harm this police officer.]";
const string CONST_WHY_THE_FUCK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the fuck am I talkin' to you?  I'd rather kill this pig.";
const string CONST_F_CK_A_M_TH_F_CK_N_BULL_I_M_KILLIN_THIS_PIG_SH_T = "F*ck a m*th*f*ck*n' bull.  I'm killin' this pig sh*t.";
const string CONST_TOO_LATE_I_AM_GOING_TO_HARM_THIS_POLICE_OFFICER = "[Too late.]  [I am going to harm this police officer.]";
const string CONST_FUCK_A_MUTHAFUCKIN_BULL_I_M_KILLIN_THIS_PIG_SHIT = "Fuck a muthafuckin' bull.  I'm killin' this pig shit.";
const string CONST_AH_F_CK_THIS_SH_T_THIS_PUNK_B_TCH_IS_F_CKIN_DEAD = "Ah, f*ck this sh*t.  This punk b*tch is f*ckin' dead!";
const string CONST_AH_NO_WAY_THIS_POLICE_OFFICER_WILL_BE_HARMED = "Ah, [no way.]  This [police officer will be harmed!]";
const string CONST_AH_FUCK_THIS_SHIT_THIS_PUNK_BITCH_IS_FUCKIN_DEAD = "Ah, fuck this shit.  This punk bitch is fuckin' dead!";
const string CONST_REPORTEDLY_SCREAMED_INTO_THE_RECEIVER = " reportedly screamed into the receiver \"";
const string CONST_DAYS_BUT_TALKS_WERE_CUT_SHORT_WHEN = " days, but talks were cut short when ";
const string CONST_ATTEMPTED_TO_NEGOTIATE_BY_PHONE_FOR = "attempted to negotiate by phone for ";
const string CONST_AUTHORITIES_LOCKED_DOWN_THE_PRISON_AND = "Authorities locked down the prison and ";
const string CONST_WITH_THE_GUARD_IN_A_PRISON_TOWER = " with the guard in a prison tower.  ";
const string CONST_HERSELF = "herself";
const string CONST_AND_BARRICADED = " and barricaded ";
const string CONST_OVERPOWERED = ", overpowered ";
const string CONST_AN_INMATE_AT = ", an inmate at ";
const string CONST_TWO_WEEKS_AGO_CONVICTED_RAPIST = "   Two weeks ago, convicted rapist ";
const string CONST_TWO_WEEKS_AGO_CONVICTED_REPRODUCTION_FIEND = "   Two weeks ago, convicted [reproduction fiend] ";
const string CONST_CAPTOR = " captor.";
const string CONST_DEATH_OF_BOTH_THE_PRISON_GUARD_BEING_HELD_HOSTAGE_AND = "death of both the prison guard being held hostage and ";
const string CONST_CORRECTIONAL_FACILITY_ENDED_TRAGICALLY_YESTERDAY_WITH_THE = " Correctional Facility ended tragically yesterday with the ";
const string CONST_THE_HOSTAGE_CRISIS_AT_THE = " - The hostage crisis at the ";
const string CONST_S_HEROIC_ACTIONS = "'s heroic actions.\"";
const string CONST_IF_NOT_FOR = " if not for ";
const string CONST_MASS_SHOOTING = "mass shooting";
const string CONST_HURTING_SPREE = "[hurting spree]";
const string CONST_THE_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_SAID_WE_D_HAVE_A_YET_ANOTHER = "  The spokesperson for the police department said, \"We'd have a yet another ";
const string CONST_COULD_HURT_ANYONE_ELSE_R = "could hurt anyone else.&r";
const string CONST_SHE_LOWERCASE_SPACE = "she ";
const string CONST_BEFORE = "before ";
const string CONST_FIREFIGHT_KILLING_THE_ATTACKER = "firefight, killing the attacker ";
const string CONST_FIREFIGHT_PUTTING_THE_ATTACKER_TO_SLEEP = "firefight, [putting the attacker to sleep] ";
const string CONST_BECAME_MORE_AGITATED_THE_HEROIC_CITIZEN_WAS_FORCED_TO_ENGAGE_THE_SHOOTER_IN_A = " became more agitated, the heroic citizen was forced to engage the shooter in a ";
const string CONST_ATTEMPTED_TO_TALK_DOWN_THE_SHOOTER_BUT_AS = " attempted to talk down the shooter, but as ";
const string CONST_MR = "Mr. ";
const string CONST_MRS = "Mrs. ";
const string CONST_MS = "Ms. ";
const string CONST_INITIALLY = "  Initially, ";
const string CONST_TO_TAKE_COVER_WHILE_OTHERS_CALLED_THE_POLICE_R = " to take cover while others called the police.&r";
const string CONST_FORCING = "forcing ";
const string CONST_THE_CITIZEN_PULLED_A_CONCEALED_HANDGUN_AND_FIRED_ONCE_AT_THE_SHOOTER = "The citizen pulled a concealed handgun and fired once at the shooter, ";
const string CONST_SPRUNG_INTO_ACTION = " sprung into action. ";
const string CONST_OPENED_FIRE_AT_THE = " opened fire at the ";
const string CONST_AFTER = " After ";
const string CONST_WAS_PREVENTED_BY_A_BYSTANDER_WITH_A_GUN = " was prevented by a bystander with a gun.";
const string CONST_IN_A_SURPRISING_TURN_A = " - In a surprising turn, a ";
const string CONST_STATED_THAT_THE_INCIDENT_IS_UNDER_INVESTIGATION = "stated that the incident is under investigation.";
const string CONST_A_SPOKESPERSON_FOR_THE_FCC = " A spokesperson for the FCC ";
const string CONST_WITHIN_THE_TOWN = "within the town. ";
const string CONST_IN_NEIGHBORING_TOWNS = "in neighboring towns. ";
const string CONST_WITHIN_THE_COUNTY = "within the county. ";
const string CONST_FROM_ALL_OVER_THE_STATE = "from all over the state. ";
const string CONST_ACROSS_THE_NATION = "across the nation. ";
const string CONST_FROM_IRATE_LISTENERS = "from irate listeners ";
const string CONST_COMPLAINTS = " complaints ";
const string CONST_SOME = "some";
const string CONST_DOZENS_OF = "dozens of";
const string CONST_HUNDREDS_OF = "hundreds of";
const string CONST_SEVERAL_HUNDRED = "several hundred";
const string CONST_THOUSANDS_OF = "thousands of";
const string CONST_THE_FCC_RECEIVED = "the FCC received ";
const string CONST_LATER_APOLOGIZED = " later apologized, ";
const string CONST_ON_THE_AIR_ALTHOUGH = " on the air.  Although ";
const string CONST_MASTURBATED = "masturbated";
const string CONST_HAD_FUN = "[had fun]";
const string CONST_BREASTFED_FROM_A_LACTATING_WOMAN = "breastfed from a lactating woman";
const string CONST_FED_FROM_A_WOMAN = "[fed] from a [woman]";
const string CONST_BREASTFED_FROM_AN_EXPOSED_WOMAN = "breastfed from an exposed woman";
const string CONST_FED_FROM_AN_INDECENT_WOMAN = "[fed] from [an indecent] woman";
const string CONST_SCREAMED_F_CK_THE_POLICE_THOSE_G_DD_MN_M_TH_F_CK_RS_I_GOT_A_F_CKING_TICKET_THIS_MORNING_AND_I_M_F_CKING_P_SS_D_AS_SH_T = "screamed \"f*ck the police those g*dd*mn m*th*f*ck*rs.  I got a f*cking ticket this morning and I'm f*cking p*ss*d as sh*t.\"";
const string CONST_SCREAMED_DARN_THE_POLICE_THOSE_BIG_DUMB_JERKS_I_GOT_A_STUPID_TICKET_THIS_MORNING_AND_I_M_SO_ANGRY = "screamed \"[darn] the police those [big dumb jerks]. I got a [stupid] ticket this morning and I'm [so angry].\"";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_RELIEVE_THEMSELVES = "encouraged listeners to call in and relieve themselves";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_TAKE_A_PISS = "encouraged listeners to call in and take a piss";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_URINATE = "encouraged listeners to call in and [urinate]";
const string CONST_HAD_INTERCOURSE = "had intercourse";
const string CONST_FUCKED = "fucked";
const string CONST_HAD_CONSENSUAL_INTERCOURSE_IN_THE_MISSIONARY_POSITION = "[had consensual intercourse in the missionary position]";
const string CONST_REPORTEDLY = " reportedly ";
const string CONST_QUOTATION_COMMA_SPACE = "\", ";
const string CONST_APOS_S_SPACE = "'s ";
const string CONST_BROADCAST_OF_THE_PROGRAM = "broadcast of the program \"";
const string CONST_HAS_BROUGHT_RADIO_ENTERTAINMENT_TO_A_NEW_LOW_DURING_YESTERDAY_S = " has brought radio entertainment to a new low.  During yesterday's ";
const string CONST_INFAMOUS_FM_RADIO_SHOCK_JOCK = " - Infamous FM radio shock jock ";
const string CONST_OF_THE_TECH_INDUSTRY_BUT_IS_ALSO_INDICATIVE_OF_A_FULL_ECONOMIC_RECOVER_R = "of the tech industry but is also indicative of a full economic recover.&r";
const string CONST_ANALYSTS_SUGGEST_THAT_NOT_ONLY_DOES_THE_EXPANSION_SPEAK_TO_THE_HEALTH = "analysts suggest that not only does the expansion speak to the health ";
const string CONST_FUTURES_OF_SOME_OF_THE_COMPANIES_IN_THE_TECH_SECTOR_ON_THE_WHOLE_HOWEVER = "futures of some of the companies in the tech sector.  On the whole, however, ";
const string CONST_ALTHOUGH_THE_DAMPENED_MOVEMENT_MIGHT_BE_EXPECTED_DUE_TO_THE_UNCERTAIN = "although the dampened movement might be expected due to the uncertain ";
const string CONST_THE_MARKETS_REPORTEDLY_RESPONDED_TO_THE_ANNOUNCEMENT_WITH_MILD_INTEREST = "The markets reportedly responded to the announcement with mild interest, ";
const string CONST_THIS_WELCOME_NEWS_IS_BOUND_TO_BE_A_PLEASANT_SURPRISE_TO_THOSE_IN_THE_UNEMPLOYMENT_LINES = "this welcome news is bound to be a pleasant surprise to those in the unemployment lines.  ";
const string CONST_OF_LARGE_CORPORATIONS_TO_EXPORT_JOBS_OVERSEAS_THESE_DAYS = "of large corporations to export jobs overseas these days, ";
const string CONST_LIGHT_OF_THE_TENDENCY = "light of the tendency ";
const string CONST_GIVEN_THE_STATE_OF_THE_ECONOMY_RECENTLY_AND_IN = "Given the state of the economy recently and in ";
const string CONST_INCREASING_ITS_PAYROLLS_BY_OVER_TEN_THOUSAND_WORKERS_ALONE = " increasing its payrolls by over ten thousand workers alone.  ";
const string CONST_TECH_GIANT = "tech giant ";
const string CONST_ARE_EXPECTED_IN_THE_FIRST_MONTH_WITH = "are expected in the first month, with ";
const string CONST_DURING_THE_NEXT_QUARTER_OVER_THIRTY_THOUSAND_JOBS = "during the next quarter.  Over thirty thousand jobs ";
const string CONST_WILL_BE_EXPANDING_THEIR_WORK_FORCES_CONSIDERABLY = "will be expanding their work forces considerably ";
const string CONST_AT_A_JOINT_NEWS_CONFERENCE_HERE_THAT_THEY = "at a joint news conference here that they ";
const string CONST_SEVERAL_MAJOR_COMPANIES_HAVE_ANNOUNCED = " - Several major companies have announced ";
const string CONST_NEEDS_TO_TAKE_A_BREATHER_ON_THIS_ONE_WE_DON_T_SEE_WHY_THERE_S_SUCH_A_RUSH_TO_JUDGMENT_HERE = "needs to take a breather on this one.  We don't see why there's such a rush to judgment here.  ";
const string CONST_BEFORE_WE_URGE_ANY_ACTION_SOCIETY_REALLY_JUST = "before we urge any action.  Society really just ";
const string CONST_THERE_S_WORK_LEFT_TO_BE_DONE_WE_SHOULD_STUDY_MUCH_MORE = "there's work left to be done.  We should study much more ";
const string CONST_WHY_IS_THERE_CONTENTION_ON_THE_POLLUTION_QUESTION_IT_S_BECAUSE = "Why is there contention on the pollution question?  It's because ";
const string CONST_ALL_WE_VE_DONE_IS_INTRODUCED_A_LITTLE_CLARITY_INTO_THE_ONGOING_DEBATE = "All we've done is introduced a little clarity into the ongoing debate.  ";
const string CONST_THESE_ISSUES_TO_THEIR_OWN_ADVANTAGE = " these issues to their own advantage.  ";
const string CONST_YOU_HAVE_TO_REALIZE_THAT = ".  You have to realize that ";
const string CONST_A_SPOKESPERSON_STATED_THAT = "a spokesperson stated that, \"";
const string CONST_WHEN_QUESTIONED_ABOUT_THE_SCIENCE_BEHIND_THESE_RESULTS = "   When questioned about the science behind these results, ";
const string CONST_MIGHT_ACTUALLY = " might actually ";
const string CONST_AMONG_THE_MOST_STARTLING_OF_THE_THINK_TANK_S_FINDINGS_IS_THAT = "Among the most startling of the think tank's findings is that ";
const string CONST_AND_THE_LATEST_SCIENCE_ON_THE_ISSUE = "and the latest science on the issue.  ";
const string CONST_RECENTLY_RELEASED_A_WIDE_RANGING_REPORT_DETAILING_RECENT_TRENDS = " recently released a wide-ranging report detailing recent trends ";
const string CONST_POLLUTION_MIGHT_NOT_BE_SO_BAD_AFTER_ALL_THE = " - Pollution might not be so bad after all.  The ";
const string CONST_COMPLETELY_STRAPPED_FOR_CASH_R = "completely strapped for cash.&r";
const string CONST_TO_THE_CURRENT_ECONOMIC_DOLDRUMS_THAT_HAVE_LEFT_THE_STATE = "to the current economic doldrums that have left the state ";
const string CONST_HAS_STATED_THAT_THE_CASE_WILL_NOT_BE_RETRIED_DUE = "has stated that the case will not be retried, due ";
const string CONST_A_SPOKESPERSON_FOR_THE_DISTRICT_ATTORNEY = "   A spokesperson for the district attorney ";
const string CONST_THANK_YOU_FOR_SAVING_ME_FROM_MYSELF = "Thank you for saving me from myself.  ";
const string CONST_CONFESSED_AND_WAS_SENTENCED_TO_LIFE_SAYING = " confessed and was sentenced to life, saying \"";
const string CONST_COVERED_IN_THE_VICTIMS_BLOOD = "covered in the victims' blood.  ";
const string CONST_WAS_FOUND_WITH_THE_MURDER_WEAPON = " was found with the murder weapon, ";
const string CONST_AFTER_AN_INTENSIVE_MANHUNT = "After an intensive manhunt, ";
const string CONST_SLAYINGS = " slayings.  ";
const string CONST_WAS_CONVICTED_OF_THE_NOW_INFAMOUS = " was convicted of the now-infamous ";
const string CONST_TEN_YEARS_AGO = "   Ten years ago, ";
const string CONST_GRANTS_WAS_NOT_COERCED_IN_ANY_WAY_R = " grants was not coerced in any way.&r";
const string CONST_WHICH_EVEN_JUSTICE = ", which even Justice ";
const string CONST_DESPITE_THE_CONFESSION_OF = ", despite the confession of ";
const string CONST_CONSULTATIONS_WITH_A_MAGIC_8_BALL = " consultations with a Magic 8-Ball";
const string CONST_FAMILY = " family";
const string CONST_CLOSE_PERSONAL_FRIENDSHIP_WITH_THE = " close personal friendship with the ";
const string CONST_PERSONAL_PHILOSOPHY_OF_LIBERTY = " personal philosophy of liberty";
const string CONST_DESERVED_ANOTHER_CHANCE = " deserved another chance";
const string CONST_BELIEF_THAT = " belief that ";
const string CONST_BELIEF_THAT_THE_CRIMES_WERE_A_VAST_RIGHT_WING_CONSPIRACY = " belief that the crimes were a vast right-wing conspiracy";
const string CONST_GENERAL_FEELING_ABOUT_POLICE_CORRUPTION = " general feeling about police corruption";
const string CONST_TEN_YEAR_OLD_EYEWITNESS_TESTIMONY = "ten-year-old eyewitness testimony";
const string CONST_MADE_THE_DECISION_BASED_ON = "made the decision based on ";
const string CONST_OF_THE_NOTORIOUSLY_LIBERAL_CIRCUIT_OF_APPEALS_HERE = " of the notoriously liberal circuit of appeals here ";
const string CONST_JUSTICE = "Justice ";
const string CONST_WAS_OVERTURNED_BY_A_FEDERAL_JUDGE_YESTERDAY = " was overturned by a federal judge yesterday.  ";
const string CONST_THE_CONVICTION_OF_CONFESSED_SERIAL_KILLER = " - The conviction of confessed serial killer ";
const string CONST_BUT_THE_GM_INDUSTRY_OPERATES_AT_A_HIGHER_ETHICAL_STANDARD_THAT_GOES_WITHOUT_SAYING = "but the GM industry operates at a higher ethical standard.  That goes without saying.";
const string CONST_NO_THAT_S_JUST_RIDICULOUS_I_MEAN_SURE_COMPANIES_HAVE_PUT_UNSAFE_PRODUCTS_OUT = "No.  That's just ridiculous.  I mean, sure companies have put unsafe products out, ";
const string CONST_WOULD_WE_STAKE_THE_REPUTATION_OF_OUR_COMPANY_ON_UNSAFE_PRODUCTS = ".  Would we stake the reputation of our company on unsafe products?  ";
const string CONST_IS_JUST_A_LOAD_OF = " is just a load of ";
const string CONST_LOOK_THESE_PRODUCTS_ARE_SAFE_THAT_THING_ABOUT_THE = "Look, these products are safe.  That thing about the ";
const string CONST_ONE_IN_PARTICULAR_SAID = "One in particular said, \"";
const string CONST_IN_THEIR_DISMISSAL_OF_THE_CRITICISM_WHICH_OFTEN_FOLLOWS_THE_INDUSTRY = "in their dismissal of the criticism which often follows the industry.  ";
const string CONST_SPOKESPEOPLE_FOR_THE_GM_CORPORATIONS_WERE_UNIVERSAL = "   Spokespeople for the GM corporations were universal ";
const string CONST_THIS_AMAZING_NEW_PRODUCT_ACTUALLY = "this amazing new product actually ";
const string CONST_ACCORDING_TO_THE_PUBLIC_RELATIONS_REPRESENTATIVE_SPEAKING = "According to the public relations representative speaking, ";
const string CONST_DURING_AN_AFTERNOON_POWERPOINT_PRESENTATION = "\", during an afternoon PowerPoint presentation.  ";
const string CONST_PRESENTED_THEIR_PRODUCT = ", presented their product, \"";
const string CONST_ONE_SUCH_CORPORATION = "   One such corporation, ";
const string CONST_BOOTHS_AND_GAVE_TALKS_TO_WIDE_EYED_ONLOOKERS = "booths and gave talks to wide-eyed onlookers.";
const string CONST_TO_SHOWCASE_ITS_UPCOMING_PRODUCTS_OVER_THIRTY_COMPANIES_SET_UP = "to showcase its upcoming products.  Over thirty companies set up ";
const string CONST_THE_GENETIC_FOODS_INDUSTRY_STAGED_A_MAJOR_EVENT_HERE_YESTERDAY = " - The genetic foods industry staged a major event here yesterday ";
const string CONST_THIS_NEW_AGE = "this new age.";
const string CONST_FOR_WHAT_WE_FEEL_ARE_THE_ESSENTIAL_TOOLS_FOR_COMBATING_TERRORISM_IN = "for what we feel are the essential tools for combating terrorism in ";
const string CONST_THE_HEAD_OF_THE_AGENCY_WILL_BE_SENDING_A_REQUEST_TO_CONGRESS = "The Head of the Agency will be sending a request to Congress ";
const string CONST_HOWEVER_LET_ME_ALSO_SAY_THAT_THERE_S_MORE_THAT_NEEDS_TO_BE_DONE = "However, let me also say that there's more that needs to be done.  ";
const string CONST_CIVILIZATION_BEFORE_THEY_CAN_DESTROY_AMERICAN_FAMILIES = "civilization before they can destroy American families.  ";
const string CONST_PROVIDING_US_WITH_THE_TOOLS_WE_NEED_TO_NEUTRALIZE_THESE_ENEMIES_OF = "providing us with the tools we need to neutralize these enemies of ";
const string CONST_THAT_WE_ARE_GRATEFUL_TO_THE_CONGRESS_AND_THIS_ADMINISTRATION_FOR = "that we are grateful to the Congress and this Administration for ";
const string CONST_I_WON_T_COMPROMISE_OUR_SOURCES_AND_METHODS_BUT_LET_ME_JUST_SAY = "I won't compromise our sources and methods, but let me just say ";
const string CONST_WAS_TO_OCCUR = "was to occur.";
const string CONST_TERRORIST_ORGANIZATION_ALLOWED_THE_PLOT_TO_BE_FOILED_JUST_DAYS_BEFORE_IT = "terrorist organization allowed the plot to be foiled just days before it ";
const string CONST_HOWEVER_INTELLIGENCE_GARNERED_FROM_DEEP_WITHIN_THE_MYSTERIOUS = ".  However, intelligence garnered from deep within the mysterious ";
const string CONST_PLANNED_TO = " planned to ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_AGENCY = "   According to a spokesperson for the agency, ";
const string CONST_WOULD_HAVE_OCCURRED_ON_AMERICAN_SOIL = "would have occurred on American soil.";
const string CONST_WASHINGTON_DC_THE_CIA_ANNOUNCED_YESTERDAY_THAT_IT_HAS_AVERTED_A_TERROR_ATTACK_THAT = "Washington, DC - The CIA announced yesterday that it has averted a terror attack that ";
const string CONST_THE_FIRST_PHASE_OF_HUMAN_TRIALS_IS_SLATED_TO_BEGIN_IN_A_FEW_MONTHS = "   The first phase of human trials is slated to begin in a few months.";
const string CONST_I_THINK_THE_MEDIA_SHOULD_BE_FOCUSING_ON_THE_ENORMOUS_BENEFITS_OF_THIS_DRUG = "I think the media should be focusing on the enormous benefits of this drug.";
const string CONST_WHILE_WE_UNDERSTAND_YOUR_CONCERNS_ANY_WORRIES_ARE_ENTIRELY_UNFOUNDED = "While we understand your concerns, any worries are entirely unfounded.  ";
const string CONST_WE_HAVE_A_VERY_EXPERIENCED_RESEARCH_TEAM = ".  We have a very experienced research team.  ";
const string CONST_A_SPOKESPERSON_FOR_THE_RESEARCH_TEAM_STATED_THAT_IT_REALLY_ISN_T_SO_BAD_AS_ALL_THAT_CHIMPANZEES_ARE_VERY_RESILIENT_CREATURES = "a spokesperson for the research team stated that, \"It really isn't so bad as all that.  Chimpanzees are very resilient creatures.  ";
const string CONST_FIELDING_QUESTIONS_ABOUT_THE_ETHICS_OF_THEIR_EXPERIMENTS_FROM_REPORTERS_DURING_A_PRESS_CONFERENCE_YESTERDAY = "Fielding questions about the ethics of their experiments from reporters during a press conference yesterday, ";
const string CONST_DOT_SPACE = ". ";
const string CONST_ALONG_WITH_BONOBOS_CHIMPANZEES_ARE_OUR_CLOSEST_COUSINS = "   Along with bonobos, chimpanzees are our closest cousins";
const string CONST_CORRECTS_ERECTILE_DYSFUNCTION_IN_CHIMPANZEES = "corrects erectile dysfunction in chimpanzees";
const string CONST_HELPS_CHIMPANZEES_REPRODUCE = "[helps chimpanzees reproduce]";
const string CONST_THE_DRUG_APPARENTLY = ", the drug apparently ";
const string CONST_ANAL = "Anal";
const string CONST_BUM_BUM = "Bum-Bum";
const string CONST_CALLED = "Called ";
const string CONST_HERE_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = "here report that they have discovered an amazing new wonder drug.  ";
const string CONST_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = " report that they have discovered an amazing new wonder drug. ";
const string CONST_FROM = "from ";
const string CONST_RESEARCHERS = " - Researchers ";
const string CONST_THE_DEATH_PENALTY_IN_THIS_CASE = "the death penalty in this case.";
const string CONST_LIFE_IMPRISONMENT_IN_THIS_CASE = "life imprisonment in this case.";
const string CONST_SEEKING = "seeking ";
const string CONST_THE_DISTRICT_ATTORNEY_S_OFFICE_HAS_ALREADY_REPEATEDLY_SAID_IT_WILL_BE = "   The district attorney's office has already repeatedly said it will be ";
const string CONST_SOURCES_SAY_THAT_THE_POLICE_GOT_A_BREAK_IN_THE_CASE_WHEN = ".  Sources say that the police got a break in the case when ";
const string CONST_DEAD_AND = " dead and ";
const string CONST_IN_A_BETTER_PLACE = " [in a better place]";
const string CONST_ONLY_TO_TURN_UP_LATER = "only to turn up later";
const string CONST_OVER_TWENTY_CHILDREN_IN_THE_PAST_TWO_YEARS_HAVE_GONE_MISSING = ".  Over twenty children in the past two years have gone missing, ";
const string CONST_WAS_DETAINED_YESTERDAY_AFTERNOON_REPORTEDLY_IN_POSSESSION_OF = " was detained yesterday afternoon, reportedly in possession of ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_HERE = "according to a spokesperson for the police department here.  ";
const string CONST_STRING_OF_BRUTAL_CHILD_KILLINGS_THAT_HAS_KEPT_EVERYONE_IN_THE_AREA_ON_EDGE = "string of brutal child killings that has kept everyone in the area on edge, ";
const string CONST_THE_AUTHORITIES_HAVE_APPREHENDED_THEIR_PRIMARY_SUSPECT_IN_THE = "The authorities have apprehended their primary suspect in the ";
const string CONST_PERHAPS_PARENTS_CAN_REST_EASIER_TONIGHT = " - Perhaps parents can rest easier tonight.  ";
const string CONST_DOT_QUOTATION_MARK = ".\"";
const string CONST_CHOICE_AND_I_WOULD_ONLY_HAVE_A_FEW_SECONDS_BEFORE_THEY_MADE_IT_FOR_ME = " choice, and I would only have a few seconds before they made it for me";
const string CONST_HELLUVA = "helluva";
const string CONST_DIFFICULT = "[difficult]";
const string CONST_THE_OTHER_A = " the other.  A ";
const string CONST_AIDS = "AIDS";
const string CONST_GRIDS = "GRIDS";
const string CONST_MAYBE_LOSE_AN_EYE_THE_ONE_WAY_MAYBE_CATCH = "Maybe lose an eye the one way, maybe catch ";
const string CONST_MY_SHANK_S_UNDER_THE_MATTRESS_BETTER_TO_BE_BRAVE_AND_FIGHT_OR_CHICKEN_OUT_AND_LET_THEM_TAKE_IT = "My shank's under the mattress.  Better to be brave and fight or chicken out and let them take it?  ";
const string CONST_WITH_DARK_GLARES_OF_BARE_LUST_AS_FOOTBALL_PLAYERS_MIGHT_STARE_AT_A_STUPEFIED_DRUNKEN_HELPLESS_TEENAGER = "with dark glares of bare lust, as football players might stare at a stupefied, drunken, helpless teenager.  ";
const string CONST_I_WAS_TRAPPED_WITH_THEM_NOW_THERE_WERE_THREE_LOOKING_ME_OVER = "I was trapped with them now.  There were three, looking me over ";
const string CONST_COMING_TO_A_HALT_WITH_A_DEAFENING_CLANG_THAT_SAID_IT_ALL = "coming to a halt with a deafening clang that said it all ฤฤ ";
const string CONST_THE_STEEL_BARS_GRATED_FORWARD_IN_THEIR_RAILS = "The steel bars grated forward in their rails, ";
const string CONST_TAKE_THIS_EXCERPT = "   Take this excerpt, \"";
const string CONST_UNDERSCORE_DOT_AMPERSAND_R = "_.&r";
const string CONST_BUTTLORD = "Buttlord";
const string CONST_BUMLORD = "[Bum]lord";
const string CONST_UNDERSCORE = "_";
const string CONST_S_NEW_TOUR_DE_FORCE = "'s new tour-de-force, _";
const string CONST_ORANGE_IS_THE_NEW_BLACK = "Orange is the New Black";
const string CONST_HAVE_THESE_WORKS_BEEN_AS_POIGNANT_AS = "have these works been as poignant as ";
const string CONST_PRISON_THEME_LATELY_IN_ITS_OFFERINGS_FOR_MASS_CONSUMPTION_RARELY = "prison theme lately in its offerings for mass consumption, rarely ";
const string CONST_ALTHOUGH_POPULAR_CULTURE_HAS_USED_OR_PERHAPS_OVERUSED_THE = "Although popular culture has used, or perhaps overused, the ";
const string CONST_DETAIL_WHAT_GOES_ON_BEHIND_BARS = "detail what goes on behind bars.  ";
const string CONST_A_FORMER_PRISONER_HAS_WRITTEN_A_BOOK_DESCRIBING_IN_HORRIFYING = " - A former prisoner has written a book describing in horrifying ";
const string CONST_WAS_DISTURBINGLY_OBSESSED_WITH_GUNS_AND_DEATH_R = " was disturbingly obsessed with guns and death.&r";
const string CONST_SHE = "she";
const string CONST_REPORTS_INDICATE_THAT_THE_STUDENT_KEPT_A_JOURNAL_THAT_SHOWED = "reports indicate that the student kept a journal that showed ";
const string CONST_INVESTIGATORS_ARE_CURRENTLY_SEARCHING_THE_STUDENT_S_BELONGINGS_AND_INITIAL = "  Investigators are currently searching the student's belongings, and initial ";
const string CONST_SHORTLY_AFTERWARDS_R = " shortly afterwards.&r";
const string CONST_COMMITTED_SUICIDE = " committed suicide";
const string CONST_FEEL_DEEPLY_ASLEEP = " [feel deeply asleep]";
const string CONST_AND_WOUNDED_DOZENS_MORE = " and wounded dozens more.  ";
const string CONST_HURT_SOME_PEOPLE = "[hurt some people].  ";
const string CONST_WHEN_THE_POLICE_ARRIVED_THE_STUDENT_HAD_ALREADY = "  When the police arrived, the student had already ";
const string CONST_AS_WELL_R = " as well.&r";
const string CONST_SHOT = "shot";
const string CONST_UNFORTUNATELY_HARMED = "[unfortunately harmed]";
const string CONST_THEY_WERE = ", they were ";
const string CONST_WHEN_OTHER_STUDENTS_TRIED_TO_WRESTLE_THE_WEAPONS_AWAY_FROM = "When other students tried to wrestle the weapons away from ";
const string CONST_STUDENTS_AND_TEACHERS_INSIDE = " students and teachers inside.  ";
const string CONST_SPRAYING_BULLETS_AT = "spraying bullets at";
const string CONST_SCARING = "[scaring]";
const string CONST_CLASSROOMS = "classrooms, ";
const string CONST_WHILE_CLASSES_WERE_IN_SESSION_THEN_SYSTEMATICALLY_STARTED_BREAKING_INTO = " while classes were in session, then systematically started breaking into ";
const string CONST_UNIVERSITY_LOWERCASE = "university ";
const string CONST_SCHOOL = "school ";
const string CONST_ENTERED_THE = " entered the ";
const string CONST_UNIVERSITY_UPPER_CASE = " University";
const string CONST_HIGH_SCHOOL_UPPER_CASE = " High School";
const string CONST_MIDDLE_SCHOOL_UPPER_CASE = " Middle School";
const string CONST_ELEMENTARY_SCHOOL_UPPER_CASE = " Elementary School";
const string CONST_MORE_THAN_A_DOZEN_CLASSMATES_AND_TWO_TEACHERS_AT = " more than a dozen classmates and two teachers at ";
const string CONST_MOW_DOWN = "mow down";
const string CONST_SCARE = "[scare]";
const string CONST_USED_A_VARIETY_OF_GUNS_TO = ", used a variety of guns to ";
const string CONST_UNIVERSITY = "university";
const string CONST_HIGH_SCHOOL = "high school";
const string CONST_MIDDLE_SCHOOL = "middle school";
const string CONST_ELEMENTARY_SCHOOL = "elementary school";
const string CONST_AT_A_LOCAL = " at a local ";
const string CONST_SHOOTING_RAMPAGE = "shooting rampage";
const string CONST_A_STUDENT_HAS_GONE_ON_A = "A student has gone on a ";
const string CONST_TO_THE_FM_BAND = "to the FM band.";
const string CONST_PASTURES_OF_THESE_MANY_SAID_THAT_THEY_WOULD_BE_SWITCHING_OVER = "pastures.  Of these, many said that they would be switching over ";
const string CONST_HAVE_DECIDED_TO_LEAVE_THE_PROGRAM_FOR_SANER = "have decided to leave the program for saner ";
const string CONST_FULLY_HALF_OF_THE_HOST_S_MOST_LOYAL_SUPPORTERS = "fully half of the host's most loyal supporters ";
const string CONST_ACCORDING_TO_A_POLL_COMPLETED_YESTERDAY = "According to a poll completed yesterday, ";
const string CONST_THE_DAMAGE_MIGHT_ALREADY_BE_DONE = "the damage might already be done.  ";
const string CONST_ISSUED_AN_APOLOGY_LATER_IN_THE_PROGRAM_BUT = " issued an apology later in the program, but ";
const string CONST_G_DD_MN_MIND = " g*dd*mn mind";
const string CONST_GOSH_DARN_MIND = " [gosh darn] mind";
const string CONST_GODDAMN_MIND = " goddamn mind";
const string CONST_HIS = "his";
const string CONST_LOST = "lost ";
const string CONST_HAD = " had ";
const string CONST_A_FORMER_FAN_OF_THE_SHOW = "\", a former fan of the show, ";
const string CONST_LIBERAL_MEDIA_ESTABLISHMENT = "liberal media establishment!";
const string CONST_CURRENT_PRESIDENT = "current president!";
const string CONST_AND_THE_GREATEST_LIVING_EXAMPLE_OF_A_REVERSE_RACIST_IS_THE = "and the greatest living example of a reverse racist is the ";
const string CONST_S_MONOLOGUE_FOR_THE_EVENING_BEGAN_THE_WAY_THAT_FANS = "'s monologue for the evening began the way that fans ";
const string CONST_QUOTATION_PERIOD = "\".";
const string CONST_WENT_OFF_FOR_FIFTEEN_MINUTES_IN_AN_INEXPLICABLE_RANT = " went off for fifteen minutes in an inexplicable rant ";
const string CONST_WELL_KNOWN_AM_RADIO_PERSONALITY = " - Well-known AM radio personality ";
const string CONST_THE_JUDGE_WOULD_BE_GOING_ON_A_BIBLE_RETREAT_FOR_A_FEW_WEEKS_TO = "the judge would be going on a Bible retreat for a few weeks to ";
const string CONST_COULD_NOT_BE_REACHED_FOR_COMMENT_ALTHOUGH_AN_AID_STATED_THAT = " could not be reached for comment, although an aid stated that ";
const string CONST_IN_EXCHANGE_FOR_THEIR_SILENCE = " in exchange for their silence.";
const string CONST_REPORTEDLY_OFFERED = " reportedly offered ";
const string CONST_WHEN_POLICE_BROKE_INTO_THE_HOTEL_ROOM_THEY_SAW = "when police broke into the hotel room they saw ";
const string CONST_ACCORDING_TO_SOURCES_FAMILIAR_WITH_THE_PARTICULARS = "According to sources familiar with the particulars, ";
const string CONST_LAST_WEEK_IN_A_HOTEL_DURING_A_POLICE_STING_OPERATION = " last week in a hotel during a police sting operation.  ";
const string CONST_WAS_FOUND_WITH = ", was found with ";
const string CONST_WHO_ONCE = ", who once ";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_PROSTITUTE = " has resigned in disgrace after being caught with a prostitute.";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_CIVIL_SERVANT = " has resigned in disgrace after being caught with a [civil servant].";
const string CONST_CONSERVATIVE_FEDERAL_JUDGE = " - Conservative federal judge ";
const string CONST_QUESTION_MARK = "?";
const string CONST_MAMMA_WHY_DID_THEY_KILL = "Mamma, why did they kill ";
const string CONST_DEAD = " dead?";
const string CONST_MAMMA_IS = "Mamma, is ";
const string CONST_MANY_AREA_CHILDREN_SPONTANEOUSLY_BROKE_INTO_TEARS_ONE_CHILD_WAS = "many area children spontaneously broke into tears.  One child was ";
const string CONST_WHEN_THE_DECISION_TO_BAN_THE_BOOK_WAS_ANNOUNCED_YESTERDAY = "   When the decision to ban the book was announced yesterday, ";
const string CONST_AS_KEY_EVIDENCE_OF_THE_DARK_NATURE_OF_THE_BOOK = " as key evidence of the dark nature of the book.";
const string CONST_A_CHILD_THAT = "a child that ";
const string CONST_A_CHILD_THAT_SAID_A_MAGIC_SPELL_AT_HER_PARENTS = "a child that said a magic spell at her parents";
const string CONST_A_CHILD_THAT_SWORE_IN_CLASS = "a child that swore in class";
const string CONST_IN_THEIR_COMPLAINT_THE_GROUPS_CITED_AN_INCIDENT_INVOLVING = "In their complaint, the groups cited an incident involving ";
const string CONST_SOME_CONSERVATIVES_FEEL_THAT_THE_BOOKS = "some conservatives feel that the books ";
const string CONST_ALTHOUGH_THE_SERIES_IS_ADORED_BY_CHILDREN_WORLDWIDE = "Although the series is adored by children worldwide, ";
const string CONST_PERIOD_SPACE = ". ";
const string CONST_AUTHOR = " author ";
const string CONST_IS_THE_THIRD_IN_AN_IMMENSELY_POPULAR_SERIES_BY = "_, is the third in an immensely popular series by ";
const string CONST_AND_THE = "_and_the_";
const string CONST_THE_BOOK = "   The book, ";
const string CONST_THE_CITY_BOWED_TO_PRESSURE_FROM_RELIGIOUS_GROUPS = "the city bowed to pressure from religious groups.";
const string CONST_A_CHILDREN_S_STORY_HAS_BEEN_REMOVED_FROM_LIBRARIES_HERE_AFTER = " - A children's story has been removed from libraries here after ";
const string CONST_YOU_THINK_ABOUT_THAT_BEFORE_YOU_CONTINUE_SLANGING_ACCUSATIONS = "You think about that before you continue slanging accusations";
const string CONST_THESE_FILES_DEAL_WITH_THE_ONE_AND_NOT_THE_OTHER = "these files deal with the one and not the other.  ";
const string CONST_IT_MIGHT_BE_A_BIT_PRESUMPTIVE_TO_ASSUME_THAT = "It might be a bit presumptive to assume that ";
const string CONST_WELL_YOU_KNOW_THERE_S_PRIVACY_AND_THERE_S_PRIVACY = "Well, you know, there's privacy, and there's privacy.  ";
const string CONST_THE_FBI_REFUSED_TO_COMMENT_INITIALLY_BUT_WHEN_CONFRONTED_WITH_THE_INFORMATION = "  The FBI refused to comment initially, but when confronted with the information, ";
const string CONST_DEAL_WITH_THE_UNDESIRABLES_ALTHOUGH_THIS_PHRASE_IS_NOT_CLARIFIED = "\"deal with the undesirables\", although this phrase is not clarified.  ";
const string CONST_MORE_DISTURBINGLY_THE_FILES_MAKE_REFERENCE_TO_A_PLAN_TO = "  More disturbingly, the files make reference to a plan to ";
const string CONST_UNIONS_WORKING_FOR_LIBERAL_ORGANIZATIONS_EVEN = "unions, working for liberal organizations ฤฤ even ";
const string CONST_THE_FILES_CONTAIN_INFORMATION_ON_WHICH_PEOPLE_HAVE_BEEN_ATTENDING_DEMONSTRATIONS_ORGANIZING = "The files contain information on which people have been attending demonstrations, organizing ";
const string CONST_THIS_NEWSPAPER_YESTERDAY_RECEIVED_A_COLLECTION_OF_FILES_FROM_A_SOURCE_IN_THE_FEDERAL_BUREAU_OF_INVESTIGATIONS = "This newspaper yesterday received a collection of files from a source in the Federal Bureau of Investigations.  ";
const string CONST_WASHINGTON_DC_THE_FBI_MIGHT_BE_KEEPING_TABS_ON_YOU = "Washington, DC - The FBI might be keeping tabs on you.  ";
const string CONST_CAN_BE_PUT_TO_DEATH_IN_THIS_COUNTRY = "can be put to death in this country.";
const string CONST_TRAGEDY_IT_WILL_BE_THAT_OUR_NATION_IS_NOW_EVALUATING_THE_EASE_WITH_WHICH_PEOPLE = "tragedy, it will be that our nation is now evaluating the ease with which people ";
const string CONST_AND_MORE_EVENTS_ARE_EXPECTED_THIS_EVENING_IF_THERE_IS_A_BRIGHT_SIDE_TO_BE_FOUND_FROM_THIS = "and more events are expected this evening.  If there is a bright side to be found from this ";
const string CONST_CANDLELIGHT_VIGILS_WERE_HELD_THROUGHOUT_THE_COUNTRY_LAST_NIGHT_DURING_THE_EXECUTION = "  Candlelight vigils were held throughout the country last night during the execution, ";
const string CONST_THE_FAMILY_WANTS_CLOSURE_WE_DON_T_HAVE_TIME_FOR_ANOTHER_TRIAL = "The family wants closure.  We don't have time for another trial";
const string CONST_END_OF_STORY = "End of story";
const string CONST_ASSASSIN_SERIAL_KILLER_EITHER_WAY_GUILTY = "Assassin, serial killer, either way ฤฤ guilty.  ";
const string CONST_THE_CONVICT_IS_ALWAYS_REFERRED_TO_BY_THREE_NAMES = "The convict is always referred to by three names.  ";
const string CONST_LET_S_NOT_FORGET_THE_CONVICT_IS_COLORED_YOU_KNOW_HOW_THEIR_KIND_ARE = "Let's not forget the convict is colored.  You know how their kind are";
const string CONST_SPOKESPERSON_FOR_THE_GOVERNOR_SAYING = "spokesperson for the governor saying, ";
const string CONST_THE_STATE_STILL_WENT_THROUGH_WITH_THE_EXECUTION_WITH_A = "The state still went through with the execution, with a ";
const string CONST_WAS_FRAMED = " was framed.  ";
const string CONST_AN_ADMISSION_FROM_A_FORMER_PROSECUTOR_THAT = "an admission from a former prosecutor that ";
const string CONST_A_BATTERY_OF_NEGATIVE_DNA_TESTS = "a battery of negative DNA tests.  ";
const string CONST_A_CONFESSION_FROM_ANOTHER_CONVICT = "a confession from another convict.  ";
const string CONST_HAVE_BEEN_PRODUCED_INCLUDING = "have been produced, including ";
const string CONST_SINCE_THEN_NUMEROUS_PIECES_OF_EXCULPATORY_EVIDENCE = "Since then, numerous pieces of exculpatory evidence ";
const string CONST_OF_13_SERIAL_MURDERS = " of 13 serial murders.  ";
const string CONST_WAS_CONVICTED_IN = " was convicted in ";
const string CONST_CORRECTIONAL_FACILITY_R = " Correctional Facility.&r";
const string CONST_YESTERDAY_AT_THE = " yesterday at the ";
const string CONST_SINGLE_COLON = ":";
const string CONST_WAS_PRONOUNCED_DEAD_AT = " was pronounced dead at ";
const string CONST_AN_INNOCENT_CITIZEN_HAS_BEEN_PUT_TO_DEATH_IN_THE_ELECTRIC_CHAIR = " - An innocent citizen has been put to death in the electric chair.  ";
const string CONST_EVEN_THOUGH_BEING_GAY_IS_DEVIANT_AS_WE_ALL_KNOW = ", even though being gay is deviant, as we all know.";
const string CONST_IS_A_KNOWN_FAGGOT = " is a known faggot";
const string CONST_DESPITE_THE_FACT_THAT = ", despite the fact that ";
const string CONST_AGGRAVATED_NATURE_OF_THE_OFFENSE = "aggravated nature of the offense";
const string CONST_PROSECUTE_THIS_CASE_AS_A_HATE_CRIME_DUE_TO_THE = "prosecute this case as a hate crime, due to the ";
const string CONST_AUTHORITIES_HAVE_STATED_THAT_THEY_WILL_VIGOROUSLY = "  Authorities have stated that they will vigorously ";
const string CONST_AT_WHICH_POINT_THEY_WERE_TAKEN_INTO_CUSTODY_NOBODY_WAS_SERIOUSLY_INJURED_DURING_THE_INCIDENT = "at which point they were taken into custody.  Nobody was seriously injured during the incident.";
const string CONST_THE_CHASE_ENDED_WHEN = "The chase ended when ";
const string CONST_AT_THE_PURSUING_POLICE_CRUISERS = " at the pursuing police cruisers.  ";
const string CONST_TAKING_SWIPES = "taking swipes";
const string CONST_URINATING_OUT_THE_WINDOW = "urinating out the window";
const string CONST_PISSING_OUT_THE_WINDOW = "pissing out the window";
const string CONST_RELIEVING_THEMSELVES_OUT_THE_WINDOW = "[relieving themselves] out the window";
const string CONST_THROWING_BEER_BOTTLES = "throwing beer bottles";
const string CONST_THROWING_JUICE_BOXES = "throwing [juice boxes]";
const string CONST_MURDERERS_SWERVING_WILDLY = "murderers swerving wildly, ";
const string CONST_WITNESSES_OF_THE_FREEWAY_CHASE_DESCRIBED_THE_PICKUP_OF_THE_ALLEGED = "  Witnesses of the freeway chase described the pickup of the alleged ";
const string CONST_HAVE_NOT_YET_BEEN_RELEASED = "have not yet been released.";
const string CONST_WERE_APPREHENDED_AFTER_A_HIGH_SPEED_CHASE_THEIR_NAMES = "were apprehended after a high speed chase.  Their names ";
const string CONST_A_POLICE_SPOKESPERSON_REPORTED_THAT_FOUR_SUSPECTS = "A police spokesperson reported that four suspects ";
const string CONST_HERE_YESTERDAY = " here yesterday.  ";
const string CONST_A_HOMOSEXUAL_WAS = "a homosexual, was ";
const string CONST_A_KNOWN_HOMOSEXUAL_WAS = "a known homosexual, was ";
const string CONST_A_KNOWN_SEXUAL_DEVIANT_WAS = "a known sexual deviant, was ";
const string CONST_CHILDREN_R = " children.&r";
const string CONST_FIVE = "five";
const string CONST_FOUR = "four";
const string CONST_THREE = "three";
const string CONST_TWO = "two";
const string CONST_SPACE_AND_SPACE = " and ";
const string CONST_WIFE = "wife";
const string CONST_IS_SURVIVED_BY = " is survived by ";
const string CONST_HAD_BEEN_COMPLETED_R = "had been completed.&r";
const string CONST_SURRENDERED_WITHOUT_A_STRUGGLE_REPORTEDLY_SAYING_THAT_GOD_S_WORK = " surrendered without a struggle, reportedly saying that God's work ";
const string CONST_ABORTION_DOCTORS_AS_OPPOSED_TO_ARRESTING_THEM_R = " abortion doctors as opposed to arresting them.&r";
const string CONST_LATER_ADMITTED_TO_BEING_A_ROGUE_FBI_VIGILANTE_HUNTING_DOWN = " later admitted to being a rogue FBI vigilante, hunting down ";
const string CONST_CALLED_THE_POLICE_ON_A_CELLPHONE_AND_THEY_ARRIVED_SHORTLY_THEREAFTER = "called the police on a cellphone and they arrived shortly thereafter.  ";
const string CONST_VERSES_OF_THE_BIBLE_AT_THE_STUNNED_ONLOOKERS_SOMEONE = "verses of the Bible at the stunned onlookers.  Someone ";
const string CONST_REMAINED_AT_THE_SCENE_AFTER_THE_SHOOTING_SCREAMING = " remained at the scene after the shooting, screaming ";
const string CONST_WITNESSES_REPORT_THAT = "  Witnesses report that ";
const string CONST_IS_IN_CUSTODY_R = ", is in custody.&r";
const string CONST_THE_SUSPECTED_SHOOTER = "The suspected shooter, ";
const string CONST_TIMES_AND_DIED_IMMEDIATELY_IN_THE_PARKING_LOT = " times and died immediately in the parking lot.  ";
const string CONST_WAS_HIT = " was hit ";
const string CONST_SHOTS_WERE_FIRED_FROM_A_NEARBY_VEHICLE = "shots were fired from a nearby vehicle.  ";
const string CONST_CAR_WHEN_ACCORDING_TO_POLICE_REPORTS = " car when, according to police reports, ";
const string CONST_WAS_WALKING_TO = " was walking to ";
const string CONST_DR = "Dr. ";
const string CONST_CLINIC_YESTERDAY = " Clinic yesterday.  ";
const string CONST_GUNNED_DOWN_OUTSIDE_OF_THE = "gunned down outside of the ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_SEMI_LEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed semi-legal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTION_MURDERS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortion-murders was ruthlessly ";
const string CONST_TILDA = "~";
const string AMPERSAND_R = "&r";
const string CONST_FORTUNATELY_THE_CCS_THUGS_WERE_STOPPED_BY_BRAVE_CITIZENS = "Fortunately, the CCS thugs were stopped by brave citizens.  ";
const string CONST_EVERYONE_IN_THE_CCS_GROUP_WAS_ARRESTED_OR_KILLED = "Everyone in the CCS group was arrested or killed.  ";
const string CONST_FORTUNATELY_THE_LCS_THUGS_WERE_STOPPED_BY_BRAVE_CITIZENS = "Fortunately, the LCS thugs were stopped by brave citizens.  ";
const string CONST_EVERYONE_IN_THE_LCS_GROUP_WAS_ARRESTED_OR_KILLED = "Everyone in the LCS group was arrested or killed.  ";
const string CONST_UNFORTUNATELY_THE_LCS_GROUP_WAS_DEFEATED_BY_THE_FORCES_OF_EVIL = "Unfortunately, the LCS group was defeated by the forces of evil.  ";
const string CONST_A_LIBERAL_CRIME_SQUAD_OPERATION_WENT_HORRIBLY_WRONG_AND_CAME_TO_A_TRAGIC_END = "A Liberal Crime Squad operation went horribly wrong, and came to a tragic end.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_GONE_ON_A_RAMPAGE_AND_THEY_GOT_WHAT_THEY_DESERVED = "The Liberal Crime Squad has gone on a rampage, and they got what they deserved.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_STRUCK_AGAIN_ALBEIT_WITH_A_TRAGIC_END = "The Liberal Crime Squad has struck again, albeit with a tragic end.  ";
const string CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT_SPACE = "to a spokesperson from the police department.  ";
const string CONST_WENT_ON_A_SUICIDAL_RAMPAGE_YESTERDAY_ACCORDING = "went on a suicidal rampage yesterday, according ";
const string CONST_A_GROUP_OF_THUGS_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD = "A group of thugs calling itself the Liberal Crime Squad ";
const string CONST_BURST_BRIEFLY_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING = "burst briefly onto the scene of political activism yesterday, according ";
const string CONST_A_GROUP_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD = "A group calling itself the Liberal Crime Squad ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_GONE_ON_ANOTHER_RAMPAGE_AND_THEY_GOT_WHAT_THEY_DESERVED = "The Conservative Crime Squad has gone on another rampage, and they got what they deserved.  ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_STRUCK_AGAIN_ALBEIT_WITH_A_TRAGIC_END = "The Conservative Crime Squad has struck again, albeit with a tragic end.  ";
const string CONST_RAMPAGE_YESTERDAY_ACCORDING_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT = "rampage yesterday, according to a spokesperson from the police department.  ";
const string CONST_CALLING_THEMSELVES_THE_CONSERVATIVE_CRIME_SQUAD_WENT_ON_A = "calling themselves the Conservative Crime Squad went on a ";
const string CONST_M16_TOTING = "M16-toting ";
const string CONST_A_GROUP_OF = "A group of ";
const string CONST_A_GROUP_OF_M16_WIELDING_VIGILANTES_CALLING_THEMSELVES_THE_CONSERVATIVE_CRIME_SQUAD = "A group of M16-wielding vigilantes calling themselves the Conservative Crime Squad ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_GONE_ON_ANOTHER_RAMPAGE = "The Conservative Crime Squad has gone on another rampage.  ";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_STRUCK_AGAIN = "The Conservative Crime Squad has struck again.  ";
const string CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT = "to a spokesperson from the police department.";
const string CONST_WENT_ON_A_RAMPAGE_YESTERDAY_ACCORDING = "went on a rampage yesterday, according ";
const string CONST_A_GROUP_OF_WORTHLESS_M16_TOTING_HICKS_CALLING_ITSELF_THE_CONSERVATIVE_CRIME_SQUAD = "A group of worthless M16-toting hicks calling itself the Conservative Crime Squad ";
const string CONST_BURST_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING = "burst onto the scene of political activism yesterday, according ";
const string CONST_A_GROUP_OF_M16_WIELDING_VIGILANTES_CALLING_ITSELF_THE_CONSERVATIVE_CRIME_SQUAD = "A group of M16-wielding vigilantes calling itself the Conservative Crime Squad ";
const string CONST_A_LIBERAL_CRIME_SQUAD_OPERATION_WENT_HORRIBLY_WRONG = "A Liberal Crime Squad operation went horribly wrong.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_GONE_ON_A_RAMPAGE = "The Liberal Crime Squad has gone on a rampage.  ";
const string CONST_THE_LIBERAL_CRIME_SQUAD_HAS_STRUCK_AGAIN = "The Liberal Crime Squad has struck again.  ";
const string CONST_THE_VERY_SYMBOL_OF_ECONOMIC_INEQUALITY = ", the very symbol of economic inequality.  ";
const string CONST_KNOWN_FOR_ITS_EXTREME_CONSERVATIVE_BIAS = ", known for its Extreme Conservative Bias.  ";
const string CONST_A_BUILDING_WITH_ENOUGH_SQUARE_FOOTAGE_ENOUGH_TO_HOUSE_A_HUNDRED_PEOPLE_IF_IT_WEREN_T_IN_CONSERVATIVE_HANDS = ", a building with enough square footage enough to house a hundred people if it weren't in Conservative Hands.  ";
const string CONST_WHERE_EVIL_AND_CONSERVATISM_COAGULATE_IN_THE_HALLWAYS = ", where evil and Conservatism coagulate in the hallways.  ";
const string CONST_ALSO_KNOWN_TO_BE_A_CONSERVATIVE_STORAGE_FACILITY_FOR_RADIOACTIVE_WASTE = ", also known to be a Conservative storage facility for radioactive waste.  ";
const string CONST_A_FACTORY_WHOSE_CONSERVATIVE_SMOKESTACKS_CHOKE_THE_CITY_WITH_DEADLY_POLLUTANTS = ", a factory whose Conservative smokestacks choke the city with deadly pollutants.  ";
const string CONST_A_CONSERVATIVE_SWEATSHOP_AND_HUMAN_RIGHTS_ABUSER = ", a Conservative sweatshop and human rights abuser.  ";
const string CONST_PRIDE_OF_CONSERVATIVE_TORTURERS_AND_WARMONGERS_EVERYWHERE = ", pride of Conservative torturers and warmongers everywhere.  ";
const string CONST_THE_CONSERVATIVE_HEADQUARTERS_OF_ONE_OF_THE_BIGGEST_PRIVACY_VIOLATORS_IN_THE_WORLD = ", the Conservative headquarters of one of the biggest privacy violators in the world.  ";
const string CONST_WHERE_INNOCENT_PEOPLE_ARE_REGULARLY_BEATEN_BY_CONSERVATIVE_GUARDS = ", where innocent people are regularly beaten by Conservative guards.  ";
const string CONST_SITE_OF_NUMEROUS_CONSERVATIVE_INJUSTICES = ", site of numerous Conservative Injustices.  ";
const string CONST_HEADQUARTERS_OF_ONE_OF_THE_MOST_OPPRESSIVE_AND_CONSERVATIVE_POLICE_FORCES_IN_THE_COUNTRY = ", headquarters of one of the most oppressive and Conservative police forces in the country.  ";
const string CONST_A_DANGEROUS_CONSERVATIVE_GENETIC_RESEARCH_LAB = ", a dangerous Conservative genetic research lab.  ";
const string CONST_A_CONSERVATIVE_ANIMAL_RIGHTS_ABUSER = ", a Conservative animal rights abuser.  ";
const string CONST_A_SPAWNING_GROUND_OF_WRONG_CONSERVATIVE_IDEAS = ", a spawning ground of Wrong Conservative Ideas.  ";
const string CONST_KNOWN_FOR_ITS_RICH_AND_SNOOTY_RESIDENTS = ", known for its rich and snooty residents.  ";
const string CONST_RICHARD_DAWKINS_FOOD_BANK = "Richard Dawkins Food Bank.  ";
const string CONST_ACLU_BRANCH_OFFICE = "ACLU Branch Office.  ";
const string CONST_GREENPEACE_OFFICES = "Greenpeace Offices.  ";
const string CONST_NETWORK_NEWS_STATION = "Network News Station.  ";
const string CONST_PUBLIC_RADIO_STATION = "Public Radio Station.  ";
const string CONST_TAX_COLLECTION_AGENCY = "Tax Collection Agency.  ";
const string CONST_WELFARE_ASSISTANCE_AGENCY = "Welfare Assistance Agency.  ";
const string CONST_WHIRLED_PEAS_MUSEUM = "Whirled Peas Museum.  ";
const string CONST_LABOR_UNION_HQ = "Labor Union HQ.  ";
const string CONST_WIKILEAKS_HQ = "WikiLeaks HQ.  ";
const string CONST_REHABILITATION_CENTER = "Rehabilitation Center.  ";
const string CONST_ABORTION_CLINIC = "Abortion Clinic.  ";
const string CONST_SEEDY_BACK_ALLEY_TM = "Seedy Back Alley(tm).  ";
const string CONST_RESEARCH_ETHICS_COMMISSION_HQ = "Research Ethics Commission HQ.  ";
const string CONST_ANIMAL_SHELTER = "Animal Shelter.  ";
const string CONST_LADY_LUCK_STRIP_CLUB = "Lady Luck Strip Club.  ";
const string CONST_UNIVERSITY_DORMITORY = "University Dormitory.  ";
const string CONST_NOTORIOUS = "notorious ";
const string CONST_AT_THE = "at the ";
const string CONST_THE_NOTORIOUS = "the notorious ";
const string CONST_AT_SPACE = "at ";
const string CONST_APOSTROPHE_S = "'s";
const string CONST_IN_THE = "in the ";
const string CONST_ON_THE = "on the ";
const string CONST_IN = "in ";
const string CONST_ON = "on ";
const string CONST_ORANGE_COUNTY = "Orange County";
const string CONST_TRAVEL_AGENCY = "Travel Agency";
const string CONST_SHOPPING_MALL = "Shopping Mall";
const string CONST_AND = "and";
const string CONST_THE_EVENTS_TOOK_PLACE = "  The events took place ";
const string CONST_W = " w/ ";
const string CONST_CALL_TODAY = "Call Today";
const string CONST_POLICE_WERE_SEEN_SEARCHING_THE_SURROUNDING_AREA_YESTERDAY = ".  Police were seen searching the surrounding area yesterday.";
const string CONST_S_LAST_KNOWN_LOCATION_WAS_THE = "'s last known location was the ";
const string CONST_ACCORDING_TO_SOURCES = "  According to sources, ";
const string QUOTATION_MARK = "\"";
const string CONST_YEARS_EXPERIENCE = " Years Experience";
const string CONST_TO_THE_CITIZENS_PLEASE_CONTACT_THE_DEPARTMENT_IF_YOU_HAVE_ANY_ADDITIONAL_INFORMATION = "To the citizens, please contact the department if you have any additional information.";
const string CONST_AS_THE_INVESTIGATION_IS_ONGOING_I_CANNOT_BE_MORE_SPECIFIC_AT_THIS_TIME = "As the investigation is ongoing, I cannot be more specific at this time.  ";
const string CONST_BACK_HOME_AND_BRING_THE_KIDNAPPERS_TO_JUSTICE = " back home and bring the kidnappers to justice.  ";
const string CONST_BRING = "bring ";
const string CONST_WE_HAVE_SEVERAL_LEADS_AND_ARE_CONFIDENT_THAT_WE_WILL = "We have several leads and are confident that we will ";
const string CONST_DAYS_AGO_BY_A_PERSON_OR_PERSONS_AS_YET_UNDETERMINED = " days ago, by a person or persons as yet undetermined.  ";
const string CONST_WAS_TAKEN = " was taken ";
const string CONST_WE_NOW_BELIEVE_THAT = "\"We now believe that ";
const string CONST_SPEAKING_ON_BEHALF_OF_THE_POLICE_DEPARTMENT_STATED = ", speaking on behalf of the police department, stated ";
const string CONST_LIBERAL_DEFENSE_LAWYER = "Liberal Defense Lawyer";
const string CONST_ACCORDING_TO_A_POLICE_SPOKESPERSON = "according to a police spokesperson.";
const string CONST_IS_NOW_CONSIDERED_A_KIDNAPPING = " is now considered a kidnapping, ";
const string CONST_THE_DISAPPEARANCE_OF = " - The disappearance of ";
const string CONST_KIDNAPPED = "KIDNAPPED";
const string CONST_SOMEONE = "SOMEONE";
const string CONST_COP = "COP";
const string CONST_JUDGE_CAPS = "JUDGE";
const string CONST_SCIENTIST = "SCIENTIST";
const string CONST_NEWS_ANCHOR = "NEWS ANCHOR";
const string CONST_RADIO_HOST = "RADIO HOST";
const string CONST_ONLY9 = "KIDNAPPING";
const string CONST_LCS_DENIES = "LCS DENIES";
const string CONST_THIS_IS_CLEARLY_THE_WORK_OF_CONSERVATIVE_BUTCHERS_ENFORCING_THE_PROHIBITION_ON_A_FREE_PRESS = "This is clearly the work of conservative butchers enforcing the prohibition on a free press";
const string CONST_WORKING_FOR_THIS_VERY_PAPER = "working for this very paper. ";
const string CONST_THE_MURDERED_WAS_A_REPORTER = "The murdered was a reporter ";
const string CONST_THE_MURDERED_WERE_REPORTERS = "The murdered were reporters ";
const string CONST_FORTUNATELY_FIREMEN_WERE_ABLE_TO_RESPOND_BEFORE_THE_FIRE_COULD_SPREAD_TO_OTHER_BUILDINGS = "Fortunately, firemen were able to respond before the fire could spread to other buildings";
const string CONST_WE_ARE_WORKING_CLOSELY_WITH_THE_FIRE_DEPARTMENT_TO_TRACK_DOWN_THE_ARSONIST = "we are working closely with the Fire Department to track down the arsonist.  ";
const string CONST_SCORCH_MARKS_THROUGHOUT_THE_SITE_INDICATE_THAT_THIS_WAS_NO_ACCIDENT = "Scorch marks throughout the site indicate that this was no accident; ";
const string CONST_ONLY = "Only $";
const string CONST_SEDAN_4D = "Sedan 4D";
const string CONST_X_LEXUS_GS_ = "Lexus GS 300";
const string CONST_VEHICLES_R = "Vehicles&r";
const string CONST_QUALITY_PRE_OWNED = "Quality Pre-Owned";
const string CONST_NOW = "Now $";
const string CONST_SPECIAL_PURCHASE = "Special Purchase";
const string CONST_FINE_LEATHER_CHAIRS = "Fine Leather Chairs";
const string CONST_CASENEWSSTORY_CCS_NOBACKERS_TXT = "caseNEWSSTORY_CCS_NOBACKERS.txt";
const string CONST_CASENEWSSTORY_CCS_DEFEATED_TXT = "caseNEWSSTORY_CCS_DEFEATED.txt";
const string CONST_ADLISTB_TXT = "adListB.txt";
const string CONST_ADLIST_TXT = "adList.txt";
const string CONST_PERSONALADSLG_TXT = "personalAdsLG.txt";
const string CONST_PERSONALADS_TXT = "personalAds.txt";
const string CONST_CCS_NOUN_TXT = "ccs_noun.txt";
const string CONST_CCS_ADJECTIVE_3_TXT = "ccs_adjective_3.txt";
const string CONST_CCS_ADJECTIVE_2_TXT = "ccs_adjective_2.txt";
const string CONST_CCS_ADJECTIVE_TXT = "ccs_adjective.txt";
const string CONST_CABLE_CITY_2_TXT = "cable_city_2.txt";
const string CONST_CABLE_CITY_TXT = "cable_city.txt";
const string CONST_CABLE_NAME_2_TXT = "cable_name_2.txt";
const string CONST_CABLE_NAME_TXT = "cable_name.txt";
const string CONST_REAGAN_GOOD_2_TXT = "reagan_good_2.txt";
const string CONST_REAGAN_GOOD_TXT = "reagan_good.txt";
const string CONST_CEO_BEHAVING_BADLY_TXT = "ceo_behaving_badly.txt";
const string CONST_REAGAN_BAD_2_TXT = "reagan_bad_2.txt";
const string CONST_REAGAN_BAD_TXT = "reagan_bad.txt";
const string CONST_PUBLIC_PLACE_TXT = "public_place.txt";
const string CONST_FM_RADIO_NAME_2_TXT = "fm_radio_name_2.txt";
const string CONST_FM_RADIO_NAME_TXT = "fm_radio_name.txt";
const string CONST_TECH_GIANT_NAME_2_TXT = "tech_giant_name_2.txt";
const string CONST_TECH_GIANT_NAME_TXT = "tech_giant_name.txt";
const string CONST_DISTRUST_LIBERALS_TXT = "distrust_liberals.txt";
const string CONST_I_LIKE_POLUTION_TXT = "i_like_polution.txt";
const string CONST_POLLUTION_CONSUMPTION_2_TXT = "pollution_consumption_2.txt";
const string CONST_POLLUTION_CONSUMPTION_TXT = "pollution_consumption.txt";
const string CONST_FAMILY_VALUES_COMPANY_NAME_3_TXT = "family_values_company_name_3.txt";
const string CONST_FAMILY_VALUES_COMPANY_NAME_2_TXT = "family_values_company_name_2.txt";
const string CONST_FAMILY_VALUES_COMPANY_NAME_TXT = "family_values_company_name.txt";
const string CONST_RADIO_HOST_LOST_MIND_TXT = "radio_host_lost_mind.txt";
const string CONST_RADIO_HOST_CRAZY_QUOTE_TXT = "radio_host_crazy_quote.txt";
const string CONST_JUDGE_WITH_PROSTITUTE_FULL_FREE_SPEECH_TXT = "judge_with_prostitute_full_free_speech.txt";
const string CONST_JUDGE_WITH_PROSTITUTE_NO_FREE_SPEECH_TXT = "judge_with_prostitute_no_free_speech.txt";
const string CONST_JUDGE_WITH_PROSTITUTE_TXT = "judge_with_prostitute.txt";
const string CONST_BROTHER_SISTER_TXT = "brother_sister.txt";
const string CONST_OLDER_YOUNGER_TXT = "older_younger.txt";
const string CONST_HIS_HER_TXT = "his_her.txt";
const string CONST_PETTY_VIOLENCE_TXT = "petty_violence.txt";
const string CONST_BULLSHIT_TXT = "bullshit.txt";
const string CONST_BULLSHIT_NO_FREE_SPEECH_TXT = "bullshit_no_free_speech.txt";
const string CONST_GENE_PRODUCT_COST_TXT = "gene_product_cost.txt";
const string CONST_GENE_PRODUCT_BENEFIT_TXT = "gene_product_benefit.txt";
const string CONST_GENE_PRODUCT_NAME_2_TXT = "gene_product_name_2.txt";
const string CONST_GENE_PRODUCT_NAME_TXT = "gene_product_name.txt";
const string CONST_GENE_CORP_NAME_2_TXT = "gene_corp_name_2.txt";
const string CONST_GENE_CORP_NAME_TXT = "gene_corp_name.txt";
const string CONST_TERRORIST_PLOT_NO_FREE_SPEECH_TXT = "terrorist_plot_no_free_speech.txt";
const string CONST_TERRORIST_PLOT_TXT = "terrorist_plot.txt";
const string CONST_TERRORIST_GROUP_TXT = "terrorist_group.txt";
const string CONST_CHIMP_DRUG_HORROR_TXT = "chimp_drug_horror.txt";
const string CONST_CHIMP_DRUG_IMPACT_TXT = "chimp_drug_impact.txt";
const string CONST_DRUG_NAME_2_TXT = "drug_name_2.txt";
const string CONST_DRUG_NAME_TXT = "drug_name.txt";
const string CONST_ANIMAL_RESEARCH_COUNTRY_TXT = "animal_research_country.txt";
const string CONST_BREAK_IN_MURDER_CASE_TXT = "break_in_murder_case.txt";
const string CONST_EVIDENCE_OF_CHILD_MURDER_TXT = "evidence_of_child_murder.txt";
const string CONST_MUTILATED_CORPSE_TXT = "mutilated_corpse.txt";
const string CONST_PRISON_BOOK_TITLE_2_TXT = "prison_book_title_2.txt";
const string CONST_PRISON_BOOK_TITLE_TXT = "prison_book_title.txt";
const string CONST_MY_IDOL_TXT = "my_idol.txt";
const string CONST_BRIBE_OFFICERS_TXT = "bribe_officers.txt";
const string CONST_CRAZY_CONSERVATIVE_ACT_TXT = "crazy_conservative_act.txt";
const string CONST_WHY_CHASE_ENDED_TXT = "why_chase_ended.txt";
const string CONST_VIGILANTE_MURDER_TXT = "vigilante_murder.txt";
const string CONST_RADIO_NAME_2_TXT = "radio_name_2.txt";
const string CONST_RADIO_NAME_TXT = "radio_name.txt";
const string CONST_CONSERVATIVE_OPPOSE_BOOK_TXT = "conservative_oppose_book.txt";
const string CONST_RANDOM_NATIONALITY_TXT = "random_nationality.txt";
const string CONST_BOOK_TITLE_2_TXT = "book_title_2.txt";
const string CONST_BOOK_TITLE_TXT = "book_title.txt";
const string CONST_AMORPM_TXT = "AMorPM.txt";
const string CONST_LIBERALCRIME_TXT = "liberalCrime.txt";

const string tag_CEO = "CEO";
const string tag_CONSERVATIVE = "CONSERVATIVE";
const string tag_D = "D";
const string tag_Downtown = "Downtown";
const string tag_National_Mall = "National Mall";
const string tag_Arlington = "Arlington";
const string tag_Manhattan = "Manhattan";
const string tag_Manhattan_Island = "Manhattan Island";
const string tag_Hollywood = "Hollywood";
const string tag_Greater_Hollywood = "Greater Hollywood";
const string tag_Long_Island = "Long Island";
const string tag_B = "B";
const string tag_Brooklyn_and_Queens = "Brooklyn and Queens";
const string tag_Outskirts_and_Orange_County = "Outskirts and Orange County";
const string tag_Outskirts = "Outskirts";
const string tag_Travel = "Travel";
const string tag_Shopping = "Shopping";
const string tag_The = "The ";

const string majorevent = "majorevent\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

vector<string> CONST_Woman_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_FAILED_PARTIAL_BIRTH_ABORTION_GOES_ON_A, CONST_POPULAR_AFTERNOON_TALK_SHOW_THE_STUDIO, CONST_AUDIENCE_AND_VIEWERS_NATIONWIDE_FEEL_ITS_PAIN, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_Cable_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_MAJOR_CABLE_NEWS_CHANNEL_HAS_HIRED_A_SLICK, CONST_NEW_ANCHOR_FOR_ONE_OF_ITS_NEWS_SHOWS_GUIDED, CONST_BY_IMPRESSIVE_ADVERTISING_AMERICA_TUNES_IN, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_CEO_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_NEW_SHOW_GLAMORIZING_THE_LIVES_OF_THE_RICH, CONST_BEGINS_AIRING_THIS_WEEK_WITH_THE_NATIONWIDE, CONST_ADVERTISING_BLITZ_IT_S_BOUND_TO_BE_POPULAR, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_Cable_744POS = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_A_CABLE_NEWS_ANCHOR_ACCIDENTALLY_LET_A, CONST_BRIGHT_LIBERAL_GUEST_FINISH_A_SENTENCE_MANY, CONST_VIEWERS_ACROSS_THE_NATION_WERE_LISTENING, CONST_LOWER_BORDER_WITH_CORNERS
};
vector<string> CONST_Police_744 = {
	CONST_UPPER_BORDER_WITH_CORNERS, CONST_THE_POLICE_HAVE_BEATEN_A_BLACK_MAN_IN, CONST_LOS_ANGELES_AGAIN_THIS_TIME_THE_INCIDENT, CONST_TAPED_BY_A_PASSERBY_AND_SATURATES_THE_NEWS, CONST_LOWER_BORDER_WITH_CORNERS
};

map<int, string> newsStoryHeadlines = {
	map<int, string>::value_type(VIEW_TAXES,	CONST_CLASS_WAR),
	map<int, string>::value_type(VIEW_SWEATSHOPS,	CONST_CLASS_WAR),
	map<int, string>::value_type(VIEW_CEOSALARY,	CONST_CLASS_WAR),
	map<int, string>::value_type(VIEW_NUCLEARPOWER,	CONST_MELTDOWN_RISK),
	map<int, string>::value_type(VIEW_POLICEBEHAVIOR,	CONST_LCS_VS_COPS),
	map<int, string>::value_type(VIEW_DEATHPENALTY,	CONST_PRISON_WAR),
	map<int, string>::value_type(VIEW_INTELLIGENCE,	CONST_LCS_VS_CIA),
	map<int, string>::value_type(VIEW_ANIMALRESEARCH,	CONST_EVIL_RESEARCH),
	map<int, string>::value_type(VIEW_GENETICS,	CONST_EVIL_RESEARCH),
	map<int, string>::value_type(VIEW_FREESPEECH,	CONST_NO_JUSTICE),
	map<int, string>::value_type(VIEW_GAY,	CONST_NO_JUSTICE),
	map<int, string>::value_type(VIEW_JUSTICES,	CONST_NO_JUSTICE),
	map<int, string>::value_type(VIEW_POLLUTION,	CONST_POLLUTER_HIT),
	map<int, string>::value_type(VIEW_CORPORATECULTURE,	CONST_LCS_HITS_CORP),
	map<int, string>::value_type(VIEW_AMRADIO,	CONST_LCS_HITS_AM),
	map<int, string>::value_type(VIEW_CABLENEWS,	CONST_LCS_HITS_TV)
};
map<int, string> presidentStories = {
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_IMPEACHED,  CONST_IMPEACHED),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_BELIEVED_DEAD,  CONST_BELIEVED_DEAD),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_FOUND_DEAD, CONST_FOUND_DEAD),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_FOUND,  CONST_RESCUED),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_KIDNAPPED,  CONST_KIDNAPPED),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_MISSING,  CONST_MISSING),
	map<int, string>::value_type(NEWSSTORY_PRESIDENT_ASSASSINATED,  CONST_ASSASSINATED)
};
map<char, vector<Views> > siteViews = {
	map<SiteTypes, vector<Views> >::value_type(SITE_LABORATORY_COSMETICS,
		{
			VIEW_ANIMALRESEARCH,
			VIEW_WOMEN,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_LABORATORY_GENETIC,
		{
			VIEW_ANIMALRESEARCH,
			VIEW_GENETICS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_POLICESTATION,
		{
			VIEW_POLICEBEHAVIOR,
			VIEW_PRISONS,
			VIEW_DRUGS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_COURTHOUSE,
		{
			VIEW_DEATHPENALTY,
			VIEW_JUSTICES,
			VIEW_FREESPEECH,
			VIEW_GAY,
			VIEW_WOMEN,
			VIEW_CIVILRIGHTS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_PRISON,
		{
			VIEW_DEATHPENALTY,
			VIEW_DRUGS,
			VIEW_TORTURE,
			VIEW_PRISONS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_ARMYBASE,
		{
			VIEW_TORTURE,
			VIEW_MILITARY,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_WHITE_HOUSE,
		{
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ,
		{
			VIEW_INTELLIGENCE,
			VIEW_TORTURE,
			VIEW_PRISONS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_INDUSTRY_SWEATSHOP,
		{
			VIEW_SWEATSHOPS,
			VIEW_IMMIGRATION,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_INDUSTRY_POLLUTER,
		{
			VIEW_SWEATSHOPS,
			VIEW_POLLUTION,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_INDUSTRY_NUCLEAR,
		{
			VIEW_NUCLEARPOWER,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_CORPORATE_HEADQUARTERS,
		{
			VIEW_TAXES,
			VIEW_CORPORATECULTURE,
			VIEW_WOMEN,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_CORPORATE_HOUSE,
		{
			VIEW_TAXES,
			VIEW_CEOSALARY,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_MEDIA_AMRADIO,
		{
			VIEW_AMRADIO,
			VIEW_FREESPEECH,
			VIEW_GAY,
			VIEW_WOMEN,
			VIEW_CIVILRIGHTS,
		}
		),
	map<SiteTypes, vector<Views> >::value_type(SITE_MEDIA_CABLENEWS,
		{
			VIEW_CABLENEWS,
			VIEW_FREESPEECH,
			VIEW_GAY,
			VIEW_WOMEN,
			VIEW_CIVILRIGHTS,
		}
		),
			map<SiteTypes, vector<Views> >::value_type(SITE_RESIDENTIAL_APARTMENT_UPSCALE,
				{
					VIEW_TAXES,
					VIEW_CEOSALARY,
					VIEW_GUNCONTROL,
				}
				),
			map<SiteTypes, vector<Views> >::value_type(SITE_BUSINESS_CIGARBAR,
				{
					VIEW_TAXES,
					VIEW_CEOSALARY,
					VIEW_WOMEN,
				}
				),
			map<SiteTypes, vector<Views> >::value_type(SITE_BUSINESS_BANK,
				{
					VIEW_TAXES,
					VIEW_CEOSALARY,
					VIEW_CORPORATECULTURE,
				}
				),
};
int okay_types[] = { NEWSSTORY_SQUAD_SITE, NEWSSTORY_SQUAD_ESCAPED, NEWSSTORY_SQUAD_FLEDATTACK,
	NEWSSTORY_SQUAD_DEFENDED, NEWSSTORY_SQUAD_BROKESIEGE, NEWSSTORY_SQUAD_KILLED_SIEGEATTACK,
	NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE, NEWSSTORY_SQUAD_KILLED_SITE, NEWSSTORY_WANTEDARREST,
	NEWSSTORY_GRAFFITIARREST, NEWSSTORY_CCS_SITE, NEWSSTORY_CCS_KILLED_SITE };
map<short, string> positiveMajorEvents = {
	map<short, string>::value_type(VIEW_WOMEN,
	CONST_CLINIC_MURDER),

	map<short, string>::value_type(VIEW_GAY,
	CONST_CRIME_OF_HATE),

	map<short, string>::value_type(VIEW_DEATHPENALTY,
	CONST_JUSTICE_DEAD),

	map<short, string>::value_type(VIEW_GUNCONTROL,
	CONST_MASS_SHOOTING_ALLCAPS),

	map<short, string>::value_type(VIEW_PRISONS,
	CONST_ON_THE_INSIDE),

	map<short, string>::value_type(VIEW_INTELLIGENCE,
	CONST_THE_FBI_FILES),

	map<short, string>::value_type(VIEW_FREESPEECH,
	CONST_BOOK_BANNED),

	map<short, string>::value_type(VIEW_JUSTICES,
	CONST_IN_CONTEMPT),

	map<short, string>::value_type(VIEW_AMRADIO,
	CONST_AM_IMPLOSION),
};
struct TwoStringsAndAnInt {
	const string first;
	const string second;
	const int third;
	TwoStringsAndAnInt(string _first, string _second, int _third) : first(_first), second(_second), third(_third) {}
	TwoStringsAndAnInt() : first(""), second(""), third(-1) {}
};
map<short, TwoStringsAndAnInt> positiveMajorPictures = {
	map<short, TwoStringsAndAnInt>::value_type(VIEW_NUCLEARPOWER,
	TwoStringsAndAnInt(CONST_MELTDOWN, CONST_A_NUCLEAR_POWER_PLANT_SUFFERS_A_CATASTROPHIC_MELTDOWN, PICTURE_MELTDOWN)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_ANIMALRESEARCH,
	TwoStringsAndAnInt(CONST_HELL_ON_EARTH, CONST_A_MUTANT_ANIMAL_HAS_ESCAPED_FROM_A_LAB_AND_KILLED_THIRTY_PEOPLE, PICTURE_MUTANT_BEAST)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_GENETICS,
	TwoStringsAndAnInt(CONST_KILLER_FOOD, CONST_OVER_A_HUNDRED_PEOPLE_BECOME_SICK_FROM_GENETICALLY_MODIFIED_FOOD, PICTURE_GENETICS)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_SWEATSHOPS,
	TwoStringsAndAnInt(CONST_CHILD_S_PLEA, CONST_A_T_SHIRT_IN_A_STORE_IS_FOUND_SCRAWLED_WITH_A_MESSAGE_FROM_A_SWEATSHOP_WORKER, PICTURE_TSHIRT)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_POLLUTION,
	TwoStringsAndAnInt(CONST_RING_OF_FIRE, CONST_THE_OHIO_RIVER_CAUGHT_ON_FIRE_AGAIN, PICTURE_RIVERFIRE)),

	map<short, TwoStringsAndAnInt>::value_type(VIEW_CORPORATECULTURE,
	TwoStringsAndAnInt(CONST_BELLY_UP, CONST_AN_ENORMOUS_COMPANY_FILES_FOR_BANKRUPTCY_SHATTERING_THE_PREVIOUS_RECORD, PICTURE_DOLLARS)),



};
map<short, string> negativeMajorEvents = {

	map<short, string>::value_type(VIEW_DEATHPENALTY,
		CONST_LET_S_FRY_EM),

	map<short, string>::value_type(VIEW_ANIMALRESEARCH,
		CONST_APE_EXPLORERS),

	map<short, string>::value_type(VIEW_PRISONS,
		CONST_HOSTAGE_SLAIN),

	map<short, string>::value_type(VIEW_INTELLIGENCE,
		CONST_DODGED_BULLET),

	map<short, string>::value_type(VIEW_GENETICS,
		CONST_GM_FOOD_FAIRE),

	map<short, string>::value_type(VIEW_JUSTICES,
		CONST_JUSTICE_AMOK),

	map<short, string>::value_type(VIEW_POLLUTION,
		CONST_LOOKING_UP),

	map<short, string>::value_type(VIEW_CORPORATECULTURE,
		CONST_NEW_JOBS),
};
map<short, TwoStringsAndAnInt> negativeMajorPictures = {

	map<short, TwoStringsAndAnInt>::value_type(VIEW_GAY,
		TwoStringsAndAnInt(CONST_KINKY_WINKY, CONST_JERRY_FALWELL_EXPLAINS_THE_TRUTH_ABOUT_TINKY_WINKY_AGAIN, PICTURE_TINKYWINKY)
	),
	map<short, TwoStringsAndAnInt>::value_type(VIEW_NUCLEARPOWER,
		TwoStringsAndAnInt(CONST_OIL_CRUNCH, CONST_OPEC_CUTS_OIL_PRODUCTION_SHARPLY_IN_RESPONSE_TO_A_US_FOREIGN_POLICY_DECISION, PICTURE_OIL)
	),
	map<short, TwoStringsAndAnInt>::value_type(VIEW_FREESPEECH,
		TwoStringsAndAnInt(CONST_HATE_RALLY, CONST_FREE_SPEECH_ADVOCATES_FIGHT_HARD_TO_LET_A_WHITE_SUPREMACIST_RALLY_TAKE_PLACE, PICTURE_KKK)
	),



};

map<int, vector<string> >accordingToLiberalGuardian = {

	map<Crimes, vector<string> >::value_type(CRIME_POLICE_LOCKUP,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_POLICE_LOCKUP + CONST_SAVING_THEM_FROM_TORTURE_AND_BRUTALITY_AT_THE_HANDS_OF_CONSERVATIVE_POLICE_INTERROGATORS , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_POLICE_LOCKUP }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_BANKVAULTROBBERY,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT + CONST_SHOWING_THE_TRIUMPH_OF_LIBERAL_IDEALS_OVER_CONSERVATIVE_ECONOMICS , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_OPENED_THE_BANK_VAULT_WHICH_HELD_MORE_THAN_100_000_AT_THE_TIME }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_BANKSTICKUP,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_DEMANDED_ACCESS_TO_THE_BANK_VAULT + CONST_HOPING_TO_ACQUIRE_THE_RESOURCES_TO_OVERCOME_EVIL , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_THREATENED_INNOCENT_BYSTANDERS_IN_ORDER_TO_ROB_THE_BANK_VAULT }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_COURTHOUSE_LOCKUP,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_COURTHOUSE_LOCKUP + CONST_SAVING_THEM_FROM_THE_HIGHLY_CORRUPT_CONSERVATIVE_JUSTICE_SYSTEM , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_OR_ATTEMPTED_TO_FREE_PRISONERS_FROM_THE_COURTHOUSE_LOCKUP }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_PRISON_RELEASE,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_RESCUE_INNOCENT_PEOPLE_FROM_THE_ABUSIVE_CONSERVATIVE_CONDITIONS + CONST_AT_THE_PRISON , ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_FREED_PRISONERS_WHILE_IN_THE_FACILITY }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_JURYTAMPERING,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_HAS_APOLOGIZED_OVER_REPORTS_THAT_THE_OPERATION + CONST_MAY_HAVE_INTERFERED_WITH_JURY_DELIBERATIONS , ACCORDING_TO_POLICE + CONST_THE_LIBERAL_CRIME_SQUAD_ALLEGEDLY_VIOLATED_THE_SACRED + CONST_TRUST_AND_ATTEMPTED_TO_INFLUENCE_A_JURY }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_HACK_INTEL,
		{ CONST_LIBERAL_CRIME_SQUAD_COMPUTER_SPECIALISTS_WORKED_TO_LIBERATE_INFORMATION_FROM_CIA_COMPUTERS , ACCORDING_TO_POLICE + CONST_INTELLIGENCE_OFFICIALS_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_ARMORY,
		{ CONST_LIBERAL_CRIME_SQUAD_INFILTRATION_SPECIALISTS_WORKED_TO_LIBERATE_WEAPONS_FROM_THE_OPPRESSORS , CONST_ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_ATTEMPTED_TO_BREAK_INTO_THE_ARMORY }
	),
	map<Crimes,  vector<string> >::value_type(CRIME_HOUSE_PHOTOS,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_CEO_S_CONSERVATIVE_CORRUPTION , ACCORDING_TO_POLICE + CONST_THE_OWNER_OF_THE_HOUSE_SEEMED_VERY_FRANTIC_ABOUT_SOME_MISSING_PROPERTY }
	),
	map<Crimes, vector<string> >::value_type(CRIME_CORP_FILES,
		{ CONST_THE_LIBERAL_CRIME_SQUAD_WAS_ATTEMPTING_TO_UNCOVER_THE_COMPANY_S_CONSERVATIVE_CORRUPTION , ACCORDING_TO_POLICE + CONST_EXECUTIVES_ON_THE_SCENE_SEEMED_VERY_NERVOUS_ABOUT_SOMETHING }
	),
};
const vector<Crimes> noteworthyCrimes = {
	CRIME_COURTHOUSE_LOCKUP,
	CRIME_PRISON_RELEASE,
	CRIME_JURYTAMPERING,
	CRIME_HACK_INTEL,
	CRIME_ARMORY,
	CRIME_HOUSE_PHOTOS,
	CRIME_CORP_FILES
};
map<int, vector<string> >siegeMassacreStory = {

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_POLICE,

		{
			(CONST_BURNED_STABBED_WITH_MAYBE_PITCHFORKS_THERE_MAY_HAVE)+(CONST_BEEN_BITE_MARKS_NOTHING_RECOGNIZABLE_LEFT_COMPLETE_CARNAGE),
			(CONST_WE_HAVE_REASON_TO_BELIEVE_THAT_THIS_BRUTAL_MASSACRE_WAS)+(CONST_INSPIRED_BY_THE_CONSERVATIVE_MEDIA_S_BRAINWASHING_PROPAGANDA)
		}
	),
	map<SiegeTypes,  vector<string> >::value_type(SIEGE_HICKS,

		{
			(CONST_BURNED_STABBED_WITH_MAYBE_PITCHFORKS_THERE_MAY_HAVE)+
			(CONST_BEEN_BITE_MARKS_NOTHING_RECOGNIZABLE_LEFT_COMPLETE_CARNAGE)

		,

		(CONST_WE_HAVE_REASON_TO_BELIEVE_THAT_THIS_BRUTAL_MASSACRE_WAS)+
		(CONST_INSPIRED_BY_THE_CONSERVATIVE_MEDIA_S_BRAINWASHING_PROPAGANDA)
		}),

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_CORPORATE,

		{
			(CONST_IT_WAS_EXECUTION_STYLE_PROFESSIONAL_WE_VE_GOT_NOTHING)

			,

		(CONST_THIS_MASSACRE_HAS_THE_SIGNATURE_MARK_OF_A_GROUP_OF_MERCENARIES)+
		(CONST_KNOWN_TO_WORK_WITH_SEVERAL_CORPORATIONS_WE_VE_HAD_CONFRONTATIONS)+
		(CONST_WITH_IN_THE_PAST_WHEN_THE_POLICE_CAN_T_FIGURE_THIS_ONE_OUT_THEY_RE)+
		(CONST_JUST_COVERING_IT_UP)
		}),

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_CCS,

		{
			(CONST_LOOK_IT_WAS_A_CONSERVATIVE_CRIME_SQUAD_HIT_THAT_S_ALL_WE_KNOW)+
			(CONST_NO_NAMES_NO_FACES_NOT_EVEN_WHERE_IT_HAPPENED_REALLY)

		,

		(CONST_THIS_IS_THE_DOING_OF_THE_CONSERVATIVE_CRIME_SQUAD_BUTCHERS)+
		(CONST_THEY_HAVE_TO_BE_STOPPED_BEFORE_THEY_KILL_AGAIN)
		}),

	map<SiegeTypes,  vector<string> >::value_type(SIEGE_FIREMEN,
		{
			(CONST_BURNED_UNRECOGNIZABLE)+
			(CONST_SCORCH_MARKS_THROUGHOUT_THE_SITE_INDICATE_THAT_THIS_WAS_NO_ACCIDENT)+
		(CONST_WE_ARE_WORKING_CLOSELY_WITH_THE_FIRE_DEPARTMENT_TO_TRACK_DOWN_THE_ARSONIST)+
		(CONST_FORTUNATELY_FIREMEN_WERE_ABLE_TO_RESPOND_BEFORE_THE_FIRE_COULD_SPREAD_TO_OTHER_BUILDINGS)

		,

		(CONST_WORKING_FOR_THIS_VERY_PAPER)+
		(CONST_THIS_IS_CLEARLY_THE_WORK_OF_CONSERVATIVE_BUTCHERS_ENFORCING_THE_PROHIBITION_ON_A_FREE_PRESS)
		}),


};
vector<file_and_text_collection> majorevent_text_file_collection = {
	/*majorevent.cpp*/
	customText(&liberalCrime, majorevent + CONST_LIBERALCRIME_TXT),
	customText(&AMorPM, majorevent + CONST_AMORPM_TXT),
	customText(&book_title, majorevent + CONST_BOOK_TITLE_TXT),
	customText(&book_title_2, majorevent + CONST_BOOK_TITLE_2_TXT),
	customText(&random_nationality, majorevent + CONST_RANDOM_NATIONALITY_TXT),
	customText(&conservative_oppose_book, majorevent + CONST_CONSERVATIVE_OPPOSE_BOOK_TXT),
	customText(&radio_name, majorevent + CONST_RADIO_NAME_TXT),
	customText(&radio_name_2, majorevent + CONST_RADIO_NAME_2_TXT),
	customText(&vigilante_murder, majorevent + CONST_VIGILANTE_MURDER_TXT),
	customText(&why_chase_ended, majorevent + CONST_WHY_CHASE_ENDED_TXT),
	customText(&crazy_conservative_act, majorevent + CONST_CRAZY_CONSERVATIVE_ACT_TXT),
	customText(&bribe_officers, majorevent + CONST_BRIBE_OFFICERS_TXT),
	customText(&my_idol, majorevent + CONST_MY_IDOL_TXT),
	customText(&prison_book_title, majorevent + CONST_PRISON_BOOK_TITLE_TXT),
	customText(&prison_book_title_2, majorevent + CONST_PRISON_BOOK_TITLE_2_TXT),
	customText(&mutilated_corpse, majorevent + CONST_MUTILATED_CORPSE_TXT),
	customText(&evidence_of_child_murder, majorevent + CONST_EVIDENCE_OF_CHILD_MURDER_TXT),
	customText(&break_in_murder_case, majorevent + CONST_BREAK_IN_MURDER_CASE_TXT),
	customText(&animal_research_country, majorevent + CONST_ANIMAL_RESEARCH_COUNTRY_TXT),
	customText(&drug_name, majorevent + CONST_DRUG_NAME_TXT),
	customText(&drug_name_2, majorevent + CONST_DRUG_NAME_2_TXT),
	customText(&chimp_drug_impact, majorevent + CONST_CHIMP_DRUG_IMPACT_TXT),
	customText(&chimp_drug_horror, majorevent + CONST_CHIMP_DRUG_HORROR_TXT),
	customText(&terrorist_group, majorevent + CONST_TERRORIST_GROUP_TXT),
	customText(&terrorist_plot, majorevent + CONST_TERRORIST_PLOT_TXT),
	customText(&terrorist_plot_no_free_speech, majorevent + CONST_TERRORIST_PLOT_NO_FREE_SPEECH_TXT),
	customText(&gene_corp_name, majorevent + CONST_GENE_CORP_NAME_TXT),
	customText(&gene_corp_name_2, majorevent + CONST_GENE_CORP_NAME_2_TXT),
	customText(&gene_product_name, majorevent + CONST_GENE_PRODUCT_NAME_TXT),
	customText(&gene_product_name_2, majorevent + CONST_GENE_PRODUCT_NAME_2_TXT),
	customText(&gene_product_benefit, majorevent + CONST_GENE_PRODUCT_BENEFIT_TXT),
	customText(&gene_product_cost, majorevent + CONST_GENE_PRODUCT_COST_TXT),
	customText(&bullshit_no_free_speech, majorevent + CONST_BULLSHIT_NO_FREE_SPEECH_TXT),
	customText(&bullshit, majorevent + CONST_BULLSHIT_TXT),
	customText(&petty_violence, majorevent + CONST_PETTY_VIOLENCE_TXT),
	customText(&his_her, majorevent + CONST_HIS_HER_TXT),
	customText(&older_younger, majorevent + CONST_OLDER_YOUNGER_TXT),
	customText(&brother_sister, majorevent + CONST_BROTHER_SISTER_TXT),
	customText(&judge_with_prostitute, majorevent + CONST_JUDGE_WITH_PROSTITUTE_TXT),
	customText(&judge_with_prostitute_no_free_speech, majorevent + CONST_JUDGE_WITH_PROSTITUTE_NO_FREE_SPEECH_TXT),
	customText(&judge_with_prostitute_full_free_speech, majorevent + CONST_JUDGE_WITH_PROSTITUTE_FULL_FREE_SPEECH_TXT),
	customText(&radio_host_crazy_quote, majorevent + CONST_RADIO_HOST_CRAZY_QUOTE_TXT),
	customText(&radio_host_lost_mind, majorevent + CONST_RADIO_HOST_LOST_MIND_TXT),
	customText(&family_values_company_name, majorevent + CONST_FAMILY_VALUES_COMPANY_NAME_TXT),
	customText(&family_values_company_name_2, majorevent + CONST_FAMILY_VALUES_COMPANY_NAME_2_TXT),
	customText(&family_values_company_name_3, majorevent + CONST_FAMILY_VALUES_COMPANY_NAME_3_TXT),
	customText(&pollution_consumption, majorevent + CONST_POLLUTION_CONSUMPTION_TXT),
	customText(&pollution_consumption_2, majorevent + CONST_POLLUTION_CONSUMPTION_2_TXT),
	customText(&i_like_polution, majorevent + CONST_I_LIKE_POLUTION_TXT),
	customText(&distrust_liberals, majorevent + CONST_DISTRUST_LIBERALS_TXT),
	customText(&tech_giant_name, majorevent + CONST_TECH_GIANT_NAME_TXT),
	customText(&tech_giant_name_2, majorevent + CONST_TECH_GIANT_NAME_2_TXT),
	customText(&fm_radio_name, majorevent + CONST_FM_RADIO_NAME_TXT),
	customText(&fm_radio_name_2, majorevent + CONST_FM_RADIO_NAME_2_TXT),
	customText(&public_place, majorevent + CONST_PUBLIC_PLACE_TXT),
	customText(&reagan_bad, majorevent + CONST_REAGAN_BAD_TXT),
	customText(&reagan_bad_2, majorevent + CONST_REAGAN_BAD_2_TXT),
	customText(&ceo_behaving_badly, majorevent + CONST_CEO_BEHAVING_BADLY_TXT),
	customText(&reagan_good, majorevent + CONST_REAGAN_GOOD_TXT),
	customText(&reagan_good_2, majorevent + CONST_REAGAN_GOOD_2_TXT),
	customText(&cable_name, majorevent + CONST_CABLE_NAME_TXT),
	customText(&cable_name_2, majorevent + CONST_CABLE_NAME_2_TXT),
	customText(&cable_city, majorevent + CONST_CABLE_CITY_TXT),
	customText(&cable_city_2, majorevent + CONST_CABLE_CITY_2_TXT),
	/*squadstory_text.cpp*/
	customText(&ccs_adjective, majorevent + CONST_CCS_ADJECTIVE_TXT),
	customText(&ccs_adjective_2, majorevent + CONST_CCS_ADJECTIVE_2_TXT),
	customText(&ccs_adjective_3, majorevent + CONST_CCS_ADJECTIVE_3_TXT),
	customText(&ccs_noun, majorevent + CONST_CCS_NOUN_TXT),
	customText(&personalAds, MOSTLY_ENDINGS_FOLDER + CONST_PERSONALADS_TXT),
	customText(&personalAdsLG, MOSTLY_ENDINGS_FOLDER + CONST_PERSONALADSLG_TXT),
	customText(&adList, MOSTLY_ENDINGS_FOLDER + CONST_ADLIST_TXT, AD_LENGTH),
	customText(&adListB, MOSTLY_ENDINGS_FOLDER + CONST_ADLISTB_TXT, AD_LENGTH),
	customText(&caseNEWSSTORY_CCS_DEFEATED, MOSTLY_ENDINGS_FOLDER + CONST_CASENEWSSTORY_CCS_DEFEATED_TXT),
	customText(&caseNEWSSTORY_CCS_NOBACKERS, MOSTLY_ENDINGS_FOLDER + CONST_CASENEWSSTORY_CCS_NOBACKERS_TXT),
};
//#endif//NEWS_CPP
//#endif// INCLUDES_H_INCLUDED
