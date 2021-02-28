




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
#include "sdl/SDL.h"
#include "sdl/SDL_mixer.h"

#include "includesDeprecated.h"
#include "creatureConstants.h"
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
#include "includesSDS2.h"
// misc.cpp

#include "../common/ledgerEnums.h"
#include "../common/ledger.h"
#include "../common/interval.h"
#include "../log/log.h"
#include "../cursesAlternative.h"

enum Bodyparts
{
	BODYPART_HEAD,
	BODYPART_BODY,
	BODYPART_ARM_RIGHT,
	BODYPART_ARM_LEFT,
	BODYPART_LEG_RIGHT,
	BODYPART_LEG_LEFT,
	BODYPARTNUM
};

#include "../creature/creatureEnums.h"
#include "../customMaps.h"
#include "../common/musicClass.h"

/* pick a descriptor acronym */
vector<string> sexdescAcronym;
/* what kind of person? */
vector<string> sexwhoAcronym;
/* seeking acronym */
vector<string> sexseekAcronym;
/* what type of sex? */
vector<string> sextypeAcronym;
map<short, string> musicList;
extern char artdir[MAX_PATH_SIZE];
extern char endgamestate;
extern char newscherrybusted;
extern int month;
extern int year;
extern Log gamelog;
extern map<short, map<short, string> > getLawFlagStringFull;
extern map<short, string> getLawFlagString;
extern map<short, string> getLawString;
extern MusicClass music;
extern short exec[EXECNUM];
extern short interface_pgup;
extern short lawList[LAWNUM];
extern short presparty;
extern short public_interest[VIEWNUM];
extern vector<string> AMorPM;
extern vector<string> animal_research_country;
extern vector<string> archconservative_last_names;
extern vector<string> book_title_2;
extern vector<string> book_title;
extern vector<string> break_in_murder_case;
extern vector<string> bribe_officers;
extern vector<string> brother_sister;
extern vector<string> bullshit_no_free_speech;
extern vector<string> bullshit;
extern vector<string> chimp_drug_horror;
extern vector<string> chimp_drug_impact;
extern vector<string> city_names;
extern vector<string> cling_to_business_one_line;
extern vector<string> cling_to_religion_one_line;
extern vector<string> cling_to_science_one_line;
extern vector<string> clinging_one_line;
extern vector<string> conservative_oppose_book;
extern vector<string> crazy_conservative_act;
extern vector<string> develops_hatred_one_line;
extern vector<string> distrust_liberals;
extern vector<string> drug_name_2;
extern vector<string> drug_name;
extern vector<string> evidence_of_child_murder;
extern vector<string> family_values_company_name_2;
extern vector<string> family_values_company_name_3;
extern vector<string> family_values_company_name;
extern vector<string> female_first_names;
extern vector<string> fm_radio_name_2;
extern vector<string> fm_radio_name;
extern vector<string> gender_neutral_first_names;
extern vector<string> gene_corp_name_2;
extern vector<string> gene_corp_name;
extern vector<string> gene_product_benefit;
extern vector<string> gene_product_cost;
extern vector<string> gene_product_name_2;
extern vector<string> gene_product_name;
extern vector<string> great_white_male_patriarch_first_names;
extern vector<string> his_her;
extern vector<string> i_like_polution;
extern vector<string> interrogater_shows_compassion_one_line;
extern vector<string> judge_with_prostitute_full_free_speech;
extern vector<string> judge_with_prostitute_no_free_speech;
extern vector<string> judge_with_prostitute;
extern vector<string> liberalCrime;
extern vector<string> male_first_names;
extern vector<string> mutilated_corpse;
extern vector<string> my_idol;
extern vector<string> older_younger;
extern vector<string> petty_violence;
extern vector<string> pollution_consumption_2;
extern vector<string> pollution_consumption;
extern vector<string> prays_on_drugs;
extern vector<string> prays;
extern vector<string> prison_book_title_2;
extern vector<string> prison_book_title;
extern vector<string> public_place;
extern vector<string> radio_host_crazy_quote;
extern vector<string> radio_host_lost_mind;
extern vector<string> radio_name_2;
extern vector<string> radio_name;
extern vector<string> random_nationality;
extern vector<string> regular_last_names;
extern vector<string> smarter_than_you_one_line;
extern vector<string> tech_giant_name_2;
extern vector<string> tech_giant_name;
extern vector<string> terrorist_group;
extern vector<string> terrorist_plot_no_free_speech;
extern vector<string> terrorist_plot;
extern vector<string> vigilante_murder;
extern vector<string> why_chase_ended;
extern vector<vector<string> > bad_trip;
extern vector<vector<string> > cling_to_business;
extern vector<vector<string> > cling_to_interrogater;
extern vector<vector<string> > cling_to_religion;
extern vector<vector<string> > cling_to_science;
extern vector<vector<string> > develops_hatred;
extern vector<vector<string> > fall_in_love;
extern vector<vector<string> > interrogater_shows_compassion;
extern vector<vector<string> > smarter_than_you;

#include "locations/locationsEnums.h"
const vector<string> numberTimesHit =
{
	"",
	" twice",
	" three",
	" four",
	" five",
};

void generate_name(char *first, char *last, char gender);
void firstname(char *str, char gender);
string lastname(bool archconservative);

vector<int> maleOrFemale = {
	GENDER_MALE,
	GENDER_FEMALE
};
/* fills a string with a proper name */
void generate_name(char *str, char gender = GENDER_NEUTRAL);
/* get a first and last name for the same person */
void generate_name(char *first, char *last, char gender = GENDER_NEUTRAL);

string lastname(bool archconservative = false);
const char* statename(int state = -1);
void generate_long_name(char *first, char *middle, char *last, char gender = GENDER_NEUTRAL);

vector<string> two_to_five = {
	"two",
	"three",
	"four",
	"five"
};

const vector<string> vicious_killing_of_guard = {
	"slit the guard's throat with a shank",
	"strangled the guard to death with a knotted bed sheet",
	"chewed out the guard's throat",
	"hit all 36 pressure points of death on the guard",
	"electrocuted the guard with high-voltage wires",
	"thrown the guard out the top-storey window",
	"tricked another guard into shooting the guard dead",
	"burnt the guard to a crisp using a lighter and some gasoline",
	"eaten the guard's liver with some fava beans and a nice chianti",
	"performed deadly experiments on the guard unheard of since Dr. Mengele"
};


const string findingBugs = "Finding bugs";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";
const string CONST_X_PGDN = "PGDN";
const string CONST_X_SINGLE_COLON = ":";
const string CLOSING_BRACKET = "]";
const string DASH_NEXT = " - Next";
const string CONST_X_PGUP = "PGUP";
const string SEMI_COLON = ";";
const string CONST_X_OPEN_BRACKET = "[";
const string DASH_PREVIOUS = " - Previous";
const string PGUP_PGDN = "PGUP/PGDN";
const string SEMI_COLON_AND_COLON = "; and :";
const string OPEN_CLOSE_BRACKET = "[]";
const string TO_VIEW_OTHER_LIBERAL_PAGES = " to view other Liberal pages.";
const string CONST_TIMES = " times";
const string CONST_SOFTWARE_BUGS = "Software Bugs";
const string ERROL_DEFAULT_NAME = "Errol";
const string CONST_HER = "her";
const string CONST_HIS = "his";
const string CONST_HURTING_SPREE = "[hurting spree]";
const string CONST_CALLED_THE_POLICE_ON_A_CELLPHONE_AND_THEY_ARRIVED_SHORTLY_THEREAFTER = "called the police on a cellphone and they arrived shortly thereafter. ";
const string CONST_VERSES_OF_THE_BIBLE_AT_THE_STUNNED_ONLOOKERS_SOMEONE = "verses of the Bible at the stunned onlookers. Someone ";
const string CONST_REMAINED_AT_THE_SCENE_AFTER_THE_SHOOTING_SCREAMING = " remained at the scene after the shooting, screaming ";
const string CONST_WITNESSES_REPORT_THAT = " Witnesses report that ";
const string CONST_IS_IN_CUSTODY_R = ", is in custody.&r";
const string CONST_DR = "Dr. ";
const string CONST_CLINIC_YESTERDAY = " Clinic yesterday. ";
const string CONST_GUNNED_DOWN_OUTSIDE_OF_THE = "gunned down outside of the ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_SEMI_LEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed semi-legal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTIONS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortions was ruthlessly ";
const string CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTION_MURDERS_WAS_RUTHLESSLY = "A doctor that routinely performed illegal abortion-murders was ruthlessly ";

const string CONST_HAD_BEEN_COMPLETED_R = "had been completed.&r";
const string CONST_SURRENDERED_WITHOUT_A_STRUGGLE_REPORTEDLY_SAYING_THAT_GOD_S_WORK = " surrendered without a struggle, reportedly saying that God's work ";
const string CONST_ABORTION_DOCTORS_AS_OPPOSED_TO_ARRESTING_THEM_R = " abortion doctors as opposed to arresting them.&r";
const string CONST_LATER_ADMITTED_TO_BEING_A_ROGUE_FBI_VIGILANTE_HUNTING_DOWN = " later admitted to being a rogue FBI vigilante, hunting down ";

const string CONST_SPACE_AND_SPACE = " and ";
const string CONST_WIFE = "wife";
const string CONST_IS_SURVIVED_BY = " is survived by ";

const string CONST_THE_SUSPECTED_SHOOTER = "The suspected shooter, ";
const string CONST_TIMES_AND_DIED_IMMEDIATELY_IN_THE_PARKING_LOT = " times and died immediately in the parking lot. ";
const string CONST_WAS_HIT = " was hit ";
const string CONST_SHOTS_WERE_FIRED_FROM_A_NEARBY_VEHICLE = "shots were fired from a nearby vehicle. ";
const string CONST_CAR_WHEN_ACCORDING_TO_POLICE_REPORTS = " car when, according to police reports, ";
const string CONST_WAS_WALKING_TO = " was walking to ";

const string CONST_HUSBAND_LOWERCASE = "husband";
const string CONST_CHILDREN_R = " children.&r";

const string CONST_TAKING_SWIPES = "taking swipes";
const string CONST_URINATING_OUT_THE_WINDOW = "urinating out the window";
const string CONST_PISSING_OUT_THE_WINDOW = "pissing out the window";
const string CONST_RELIEVING_THEMSELVES_OUT_THE_WINDOW = "[relieving themselves] out the window";
const string CONST_THROWING_BEER_BOTTLES = "throwing beer bottles";
const string CONST_THROWING_JUICE_BOXES = "throwing [juice boxes]";


const string CONST_A_HOMOSEXUAL_WAS = "a homosexual, was ";
const string CONST_A_KNOWN_HOMOSEXUAL_WAS = "a known homosexual, was ";
const string CONST_A_KNOWN_SEXUAL_DEVIANT_WAS = "a known sexual deviant, was ";

const string CONST_EVEN_THOUGH_BEING_GAY_IS_DEVIANT_AS_WE_ALL_KNOW = ", even though being gay is deviant, as we all know.";
const string CONST_IS_A_KNOWN_FAGGOT = " is a known faggot";
const string CONST_DESPITE_THE_FACT_THAT = ", despite the fact that ";
const string CONST_AGGRAVATED_NATURE_OF_THE_OFFENSE = "aggravated nature of the offense";
const string CONST_PROSECUTE_THIS_CASE_AS_A_HATE_CRIME_DUE_TO_THE = "prosecute this case as a hate crime, due to the ";
const string CONST_AUTHORITIES_HAVE_STATED_THAT_THEY_WILL_VIGOROUSLY = " Authorities have stated that they will vigorously ";
const string CONST_AT_WHICH_POINT_THEY_WERE_TAKEN_INTO_CUSTODY_NOBODY_WAS_SERIOUSLY_INJURED_DURING_THE_INCIDENT = "at which point they were taken into custody. Nobody was seriously injured during the incident.";
const string CONST_THE_CHASE_ENDED_WHEN = "The chase ended when ";
const string CONST_AT_THE_PURSUING_POLICE_CRUISERS = " at the pursuing police cruisers. ";

const string CONST_MURDERERS_SWERVING_WILDLY = "murderers swerving wildly, ";
const string CONST_WITNESSES_OF_THE_FREEWAY_CHASE_DESCRIBED_THE_PICKUP_OF_THE_ALLEGED = " Witnesses of the freeway chase described the pickup of the alleged ";
const string CONST_HAVE_NOT_YET_BEEN_RELEASED = "have not yet been released.";
const string CONST_WERE_APPREHENDED_AFTER_A_HIGH_SPEED_CHASE_THEIR_NAMES = "were apprehended after a high speed chase. Their names ";
const string CONST_A_POLICE_SPOKESPERSON_REPORTED_THAT_FOUR_SUSPECTS = "A police spokesperson reported that four suspects ";
const string CONST_HERE_YESTERDAY = " here yesterday. ";
const string CONST_UNDERSCORE = "_";

const string CONST_QUESTION_MARK = "?";
const string CONST_MAMMA_WHY_DID_THEY_KILL = "Mamma, why did they kill ";
const string CONST_DEAD = " dead?";
const string CONST_MAMMA_IS = "Mamma, is ";
const string CONST_MANY_AREA_CHILDREN_SPONTANEOUSLY_BROKE_INTO_TEARS_ONE_CHILD_WAS = "many area children spontaneously broke into tears. One child was ";
const string CONST_WHEN_THE_DECISION_TO_BAN_THE_BOOK_WAS_ANNOUNCED_YESTERDAY = " When the decision to ban the book was announced yesterday, ";
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
const string CONST_THE_BOOK = " The book, ";
const string CONST_THE_CITY_BOWED_TO_PRESSURE_FROM_RELIGIOUS_GROUPS = "the city bowed to pressure from religious groups.";
const string CONST_A_CHILDREN_S_STORY_HAS_BEEN_REMOVED_FROM_LIBRARIES_HERE_AFTER = " - A children's story has been removed from libraries here after ";

const string CONST_HEARD_SAYING_COMMA_QUOTE = "heard saying, \"";

const string QUOTATION_MARK = "\"";

const string CONST_DOT_SPACE = ". ";
const string CONST_DOT_QUOTATION_MARK = ".\"";

const string CONST_CAN_BE_PUT_TO_DEATH_IN_THIS_COUNTRY = "can be put to death in this country.";
const string CONST_TRAGEDY_IT_WILL_BE_THAT_OUR_NATION_IS_NOW_EVALUATING_THE_EASE_WITH_WHICH_PEOPLE = "tragedy, it will be that our nation is now evaluating the ease with which people ";
const string CONST_AND_MORE_EVENTS_ARE_EXPECTED_THIS_EVENING_IF_THERE_IS_A_BRIGHT_SIDE_TO_BE_FOUND_FROM_THIS = "and more events are expected this evening. If there is a bright side to be found from this ";
const string CONST_CANDLELIGHT_VIGILS_WERE_HELD_THROUGHOUT_THE_COUNTRY_LAST_NIGHT_DURING_THE_EXECUTION = " Candlelight vigils were held throughout the country last night during the execution, ";
const string CONST_THE_FAMILY_WANTS_CLOSURE_WE_DON_T_HAVE_TIME_FOR_ANOTHER_TRIAL = "The family wants closure. We don't have time for another trial";
const string CONST_END_OF_STORY = "End of story";
const string CONST_ASSASSIN_SERIAL_KILLER_EITHER_WAY_GUILTY = "Assassin, serial killer, either way ÄÄ guilty. ";
const string CONST_THE_CONVICT_IS_ALWAYS_REFERRED_TO_BY_THREE_NAMES = "The convict is always referred to by three names. ";
const string CONST_LET_S_NOT_FORGET_THE_CONVICT_IS_COLORED_YOU_KNOW_HOW_THEIR_KIND_ARE = "Let's not forget the convict is colored. You know how their kind are";
const string CONST_SPOKESPERSON_FOR_THE_GOVERNOR_SAYING = "spokesperson for the governor saying, ";
const string CONST_THE_STATE_STILL_WENT_THROUGH_WITH_THE_EXECUTION_WITH_A = "The state still went through with the execution, with a ";
const string CONST_WAS_FRAMED = " was framed. ";
const string CONST_AN_ADMISSION_FROM_A_FORMER_PROSECUTOR_THAT = "an admission from a former prosecutor that ";
const string CONST_A_BATTERY_OF_NEGATIVE_DNA_TESTS = "a battery of negative DNA tests. ";
const string CONST_A_CONFESSION_FROM_ANOTHER_CONVICT = "a confession from another convict. ";
const string CONST_HAVE_BEEN_PRODUCED_INCLUDING = "have been produced, including ";
const string CONST_SINCE_THEN_NUMEROUS_PIECES_OF_EXCULPATORY_EVIDENCE = "Since then, numerous pieces of exculpatory evidence ";
const string CONST_OF_13_SERIAL_MURDERS = " of 13 serial murders. ";
const string CONST_WAS_CONVICTED_IN = " was convicted in ";
const string CONST_CORRECTIONAL_FACILITY_R = " Correctional Facility.&r";
const string CONST_YESTERDAY_AT_THE = " yesterday at the ";
const string CONST_SINGLE_COLON = ":";
const string CONST_WAS_PRONOUNCED_DEAD_AT = " was pronounced dead at ";
const string CONST_AN_INNOCENT_CITIZEN_HAS_BEEN_PUT_TO_DEATH_IN_THE_ELECTRIC_CHAIR = " - An innocent citizen has been put to death in the electric chair. ";

const string CONST_YOU_THINK_ABOUT_THAT_BEFORE_YOU_CONTINUE_SLANGING_ACCUSATIONS = "You think about that before you continue slanging accusations";
const string CONST_THESE_FILES_DEAL_WITH_THE_ONE_AND_NOT_THE_OTHER = "these files deal with the one and not the other. ";
const string CONST_IT_MIGHT_BE_A_BIT_PRESUMPTIVE_TO_ASSUME_THAT = "It might be a bit presumptive to assume that ";
const string CONST_WELL_YOU_KNOW_THERE_S_PRIVACY_AND_THERE_S_PRIVACY = "Well, you know, there's privacy, and there's privacy. ";
const string CONST_THE_FBI_REFUSED_TO_COMMENT_INITIALLY_BUT_WHEN_CONFRONTED_WITH_THE_INFORMATION = " The FBI refused to comment initially, but when confronted with the information, ";
const string CONST_DEAL_WITH_THE_UNDESIRABLES_ALTHOUGH_THIS_PHRASE_IS_NOT_CLARIFIED = "\"deal with the undesirables\", although this phrase is not clarified. ";
const string CONST_MORE_DISTURBINGLY_THE_FILES_MAKE_REFERENCE_TO_A_PLAN_TO = " More disturbingly, the files make reference to a plan to ";
const string CONST_UNIONS_WORKING_FOR_LIBERAL_ORGANIZATIONS_EVEN = "unions, working for liberal organizations ÄÄ even ";
const string CONST_THE_FILES_CONTAIN_INFORMATION_ON_WHICH_PEOPLE_HAVE_BEEN_ATTENDING_DEMONSTRATIONS_ORGANIZING = "The files contain information on which people have been attending demonstrations, organizing ";
const string CONST_THIS_NEWSPAPER_YESTERDAY_RECEIVED_A_COLLECTION_OF_FILES_FROM_A_SOURCE_IN_THE_FEDERAL_BUREAU_OF_INVESTIGATIONS = "This newspaper yesterday received a collection of files from a source in the Federal Bureau of Investigations. ";
const string CONST_WASHINGTON_DC_THE_FBI_MIGHT_BE_KEEPING_TABS_ON_YOU = "Washington, DC - The FBI might be keeping tabs on you. ";

const string CONST_A_SPOKESPERSON_STATED_COMMA_QUOTE = "a spokesperson stated, \"";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_PROSTITUTE = " has resigned in disgrace after being caught with a prostitute.";
const string CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_CIVIL_SERVANT = " has resigned in disgrace after being caught with a [civil servant].";

const string CONST_THE_JUDGE_WOULD_BE_GOING_ON_A_BIBLE_RETREAT_FOR_A_FEW_WEEKS_TO = "the judge would be going on a Bible retreat for a few weeks to ";
const string CONST_COULD_NOT_BE_REACHED_FOR_COMMENT_ALTHOUGH_AN_AID_STATED_THAT = " could not be reached for comment, although an aid stated that ";
const string CONST_IN_EXCHANGE_FOR_THEIR_SILENCE = " in exchange for their silence.";
const string CONST_REPORTEDLY_OFFERED = " reportedly offered ";
const string CONST_WHEN_POLICE_BROKE_INTO_THE_HOTEL_ROOM_THEY_SAW = "when police broke into the hotel room they saw ";
const string CONST_ACCORDING_TO_SOURCES_FAMILIAR_WITH_THE_PARTICULARS = "According to sources familiar with the particulars, ";
const string CONST_LAST_WEEK_IN_A_HOTEL_DURING_A_POLICE_STING_OPERATION = " last week in a hotel during a police sting operation. ";
const string CONST_WAS_FOUND_WITH = ", was found with ";
const string CONST_WHO_ONCE = ", who once ";
const string CONST_CONSERVATIVE_FEDERAL_JUDGE = " - Conservative federal judge ";


const string CONST_MAKE_THINGS_RIGHT_WITH_THE_ALMIGHTY_FATHER = "\"Make things right with the Almighty Father.\"";
const string CONST_G_DD_MN_MIND = " g*dd*mn mind";
const string CONST_GOSH_DARN_MIND = " [gosh darn] mind";
const string CONST_GODDAMN_MIND = " goddamn mind";
const string CONST_LOST = "lost ";
const string CONST_TO_THE_FM_BAND = "to the FM band.";
const string CONST_PASTURES_OF_THESE_MANY_SAID_THAT_THEY_WOULD_BE_SWITCHING_OVER = "pastures. Of these, many said that they would be switching over ";
const string CONST_HAVE_DECIDED_TO_LEAVE_THE_PROGRAM_FOR_SANER = "have decided to leave the program for saner ";
const string CONST_FULLY_HALF_OF_THE_HOST_S_MOST_LOYAL_SUPPORTERS = "fully half of the host's most loyal supporters ";
const string CONST_ACCORDING_TO_A_POLL_COMPLETED_YESTERDAY = "According to a poll completed yesterday, ";
const string CONST_THE_DAMAGE_MIGHT_ALREADY_BE_DONE = "the damage might already be done. ";
const string CONST_ISSUED_AN_APOLOGY_LATER_IN_THE_PROGRAM_BUT = " issued an apology later in the program, but ";
const string CONST_HAD = " had ";
const string CONST_A_FORMER_FAN_OF_THE_SHOW = "\", a former fan of the show, ";
const string CONST_LIBERAL_MEDIA_ESTABLISHMENT = "liberal media establishment!";
const string CONST_CURRENT_PRESIDENT = "current president!";
const string CONST_AND_THE_GREATEST_LIVING_EXAMPLE_OF_A_REVERSE_RACIST_IS_THE = "and the greatest living example of a reverse racist is the ";
const string CONST_S_MONOLOGUE_FOR_THE_EVENING_BEGAN_THE_WAY_THAT_FANS = "'s monologue for the evening began the way that fans ";
const string CONST_QUOTATION_PERIOD = "\".";
const string CONST_WENT_OFF_FOR_FIFTEEN_MINUTES_IN_AN_INEXPLICABLE_RANT = " went off for fifteen minutes in an inexplicable rant ";
const string CONST_WELL_KNOWN_AM_RADIO_PERSONALITY = " - Well-known AM radio personality ";

const string CONST_TWO_NIGHTS_AGO_DURING_RADIO = "two nights ago during the syndicated radio program \"";
const string CONST_HAD_COME_TO_EXPECT_WITH_ATTACKS_ON_LIBERAL_MEDIA = "had come to expect, with attacks on the \"liberal media establishment\"";
const string CONST_DOT_BUT_WHEN_THE_RADIO_ICON_SAID = "the \"elite liberal agenda\". But when the radio icon said, \"";
const string CONST_COMMA_KNEW_THAT_QUOTE = ", knew that \"";
const string CONST_DOT_AFTER_THAT_IT_GOT_WORSE = ". After that, it just got worse and worse.\"";

const string CONST_UNIVERSITY = "university";
const string CONST_HIGH_SCHOOL = "high school";
const string CONST_MIDDLE_SCHOOL = "middle school";
const string CONST_ELEMENTARY_SCHOOL = "elementary school";
const string CONST_UNIVERSITY_UPPER_CASE = "University";
const string CONST_HIGH_SCHOOL_UPPER_CASE = "High School";
const string CONST_MIDDLE_SCHOOL_UPPER_CASE = "Middle School";
const string CONST_ELEMENTARY_SCHOOL_UPPER_CASE = "Elementary School";
const string CONST_SHOOTING_RAMPAGE = "shooting rampage";
const string CONST_COMMITTED_SUICIDE = " committed suicide";
const string CONST_FEEL_DEEPLY_ASLEEP = " [feel deeply asleep]";
const string CONST_MOW_DOWN = "mow down";
const string CONST_SCARE = "[scare]";

const string CONST_HIM_LOWERCASE = "him";
const string CONST_KILLED = "killed ";

const string CONST_AND_WOUNDED_DOZENS_MORE = " and wounded dozens more. ";
const string CONST_HURT_SOME_PEOPLE = "[hurt some people]. ";
const string CONST_WHEN_THE_POLICE_ARRIVED_THE_STUDENT_HAD_ALREADY = " When the police arrived, the student had already ";
const string CONST_AS_WELL_R = " as well.&r";
const string CONST_SHOT = "shot";
const string CONST_UNFORTUNATELY_HARMED = "[unfortunately harmed]";
const string CONST_THEY_WERE = ", they were ";
const string CONST_WHEN_OTHER_STUDENTS_TRIED_TO_WRESTLE_THE_WEAPONS_AWAY_FROM = "When other students tried to wrestle the weapons away from ";
const string CONST_STUDENTS_AND_TEACHERS_INSIDE = " students and teachers inside. ";
const string CONST_SPRAYING_BULLETS_AT = "spraying bullets at";
const string CONST_SCARING = "[scaring]";

const string CONST_WAS_DISTURBINGLY_OBSESSED_WITH_GUNS_AND_DEATH_R = " was disturbingly obsessed with guns and death.&r";
const string CONST_SHE = "she";
const string CONST_REPORTS_INDICATE_THAT_THE_STUDENT_KEPT_A_JOURNAL_THAT_SHOWED = "reports indicate that the student kept a journal that showed ";
const string CONST_INVESTIGATORS_ARE_CURRENTLY_SEARCHING_THE_STUDENT_S_BELONGINGS_AND_INITIAL = " Investigators are currently searching the student's belongings, and initial ";
const string CONST_SHORTLY_AFTERWARDS_R = " shortly afterwards.&r";
const string CONST_CLASSROOMS = "classrooms, ";
const string CONST_WHILE_CLASSES_WERE_IN_SESSION_THEN_SYSTEMATICALLY_STARTED_BREAKING_INTO = " while classes were in session, then systematically started breaking into ";
const string CONST_UNIVERSITY_LOWERCASE = "university ";
const string CONST_SCHOOL = "school ";
const string CONST_ENTERED_THE = " entered the ";
const string CONST_MORE_THAN_A_DOZEN_CLASSMATES_AND_TWO_TEACHERS_AT = " more than a dozen classmates and two teachers at ";
const string CONST_USED_A_VARIETY_OF_GUNS_TO = ", used a variety of guns to ";
const string CONST_AT_A_LOCAL = " at a local ";
const string CONST_A_STUDENT_HAS_GONE_ON_A = "A student has gone on a ";


const string CONST_HE_LOWERCASE = "he";
const string CONST_BUTTLORD = "Buttlord";
const string CONST_BUMLORD = "[Bum]lord";
const string CONST_AIDS = "AIDS";
const string CONST_GRIDS = "GRIDS";

const string CONST_HELLUVA = "helluva";
const string CONST_DIFFICULT = "[difficult]";
const string CONST_CHOICE_AND_I_WOULD_ONLY_HAVE_A_FEW_SECONDS_BEFORE_THEY_MADE_IT_FOR_ME = " choice, and I would only have a few seconds before they made it for me";
const string CONST_THE_OTHER_A = " the other. A ";
const string CONST_MAYBE_LOSE_AN_EYE_THE_ONE_WAY_MAYBE_CATCH = "Maybe lose an eye the one way, maybe catch ";
const string CONST_MY_SHANK_S_UNDER_THE_MATTRESS_BETTER_TO_BE_BRAVE_AND_FIGHT_OR_CHICKEN_OUT_AND_LET_THEM_TAKE_IT = "My shank's under the mattress. Better to be brave and fight or chicken out and let them take it? ";
const string CONST_WITH_DARK_GLARES_OF_BARE_LUST_AS_FOOTBALL_PLAYERS_MIGHT_STARE_AT_A_STUPEFIED_DRUNKEN_HELPLESS_TEENAGER = "with dark glares of bare lust, as football players might stare at a stupefied, drunken, helpless teenager. ";
const string CONST_I_WAS_TRAPPED_WITH_THEM_NOW_THERE_WERE_THREE_LOOKING_ME_OVER = "I was trapped with them now. There were three, looking me over ";
const string CONST_COMING_TO_A_HALT_WITH_A_DEAFENING_CLANG_THAT_SAID_IT_ALL = "coming to a halt with a deafening clang that said it all ÄÄ ";
const string CONST_THE_STEEL_BARS_GRATED_FORWARD_IN_THEIR_RAILS = "The steel bars grated forward in their rails, ";
const string CONST_TAKE_THIS_EXCERPT = " Take this excerpt, \"";
const string CONST_UNDERSCORE_DOT_AMPERSAND_R = "_.&r";
const string CONST_S_NEW_TOUR_DE_FORCE = "'s new tour-de-force, _";
const string CONST_HAVE_THESE_WORKS_BEEN_AS_POIGNANT_AS = "have these works been as poignant as ";
const string CONST_PRISON_THEME_LATELY_IN_ITS_OFFERINGS_FOR_MASS_CONSUMPTION_RARELY = "prison theme lately in its offerings for mass consumption, rarely ";
const string CONST_ALTHOUGH_POPULAR_CULTURE_HAS_USED_OR_PERHAPS_OVERUSED_THE = "Although popular culture has used, or perhaps overused, the ";
const string CONST_DETAIL_WHAT_GOES_ON_BEHIND_BARS = "detail what goes on behind bars. ";
const string CONST_A_FORMER_PRISONER_HAS_WRITTEN_A_BOOK_DESCRIBING_IN_HORRIFYING = " - A former prisoner has written a book describing in horrifying ";
const string CONST_HERE_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = "here report that they have discovered an amazing new wonder drug. ";
const string CONST_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG = " report that they have discovered an amazing new wonder drug. ";
const string CONST_FROM = "from ";
const string CONST_ANAL = "Anal";
const string CONST_BUM_BUM = "Bum-Bum";
const string CONST_CORRECTS_ERECTILE_DYSFUNCTION_IN_CHIMPANZEES = "corrects erectile dysfunction in chimpanzees";
const string CONST_HELPS_CHIMPANZEES_REPRODUCE = "[helps chimpanzees reproduce]";


const string CONST_THE_FIRST_PHASE_OF_HUMAN_TRIALS_IS_SLATED_TO_BEGIN_IN_A_FEW_MONTHS = " The first phase of human trials is slated to begin in a few months.";
const string CONST_I_THINK_THE_MEDIA_SHOULD_BE_FOCUSING_ON_THE_ENORMOUS_BENEFITS_OF_THIS_DRUG = "I think the media should be focusing on the enormous benefits of this drug.";
const string CONST_WHILE_WE_UNDERSTAND_YOUR_CONCERNS_ANY_WORRIES_ARE_ENTIRELY_UNFOUNDED = "While we understand your concerns, any worries are entirely unfounded. ";
const string CONST_WE_HAVE_A_VERY_EXPERIENCED_RESEARCH_TEAM = ". We have a very experienced research team. ";
const string CONST_A_SPOKESPERSON_FOR_THE_RESEARCH_TEAM_STATED_THAT_IT_REALLY_ISN_T_SO_BAD_AS_ALL_THAT_CHIMPANZEES_ARE_VERY_RESILIENT_CREATURES = "a spokesperson for the research team stated that, \"It really isn't so bad as all that. Chimpanzees are very resilient creatures. ";
const string CONST_FIELDING_QUESTIONS_ABOUT_THE_ETHICS_OF_THEIR_EXPERIMENTS_FROM_REPORTERS_DURING_A_PRESS_CONFERENCE_YESTERDAY = "Fielding questions about the ethics of their experiments from reporters during a press conference yesterday, ";
const string CONST_ALONG_WITH_BONOBOS_CHIMPANZEES_ARE_OUR_CLOSEST_COUSINS = " Along with bonobos, chimpanzees are our closest cousins";
const string CONST_THE_DRUG_APPARENTLY = ", the drug apparently ";
const string CONST_CALLED = "Called ";
const string CONST_RESEARCHERS = " - Researchers ";

const string CONST_NEEDS_TO_TAKE_A_BREATHER_ON_THIS_ONE_WE_DON_T_SEE_WHY_THERE_S_SUCH_A_RUSH_TO_JUDGMENT_HERE = "needs to take a breather on this one. We don't see why there's such a rush to judgment here. ";
const string CONST_BEFORE_WE_URGE_ANY_ACTION_SOCIETY_REALLY_JUST = "before we urge any action. Society really just ";
const string CONST_THERE_S_WORK_LEFT_TO_BE_DONE_WE_SHOULD_STUDY_MUCH_MORE = "there's work left to be done. We should study much more ";
const string CONST_WHY_IS_THERE_CONTENTION_ON_THE_POLLUTION_QUESTION_IT_S_BECAUSE = "Why is there contention on the pollution question? It's because ";
const string CONST_ALL_WE_VE_DONE_IS_INTRODUCED_A_LITTLE_CLARITY_INTO_THE_ONGOING_DEBATE = "All we've done is introduced a little clarity into the ongoing debate. ";
const string CONST_THESE_ISSUES_TO_THEIR_OWN_ADVANTAGE = " these issues to their own advantage. ";
const string CONST_YOU_HAVE_TO_REALIZE_THAT = ". You have to realize that ";
const string CONST_A_SPOKESPERSON_STATED_THAT = "a spokesperson stated that, \"";
const string CONST_WHEN_QUESTIONED_ABOUT_THE_SCIENCE_BEHIND_THESE_RESULTS = " When questioned about the science behind these results, ";
const string CONST_MIGHT_ACTUALLY = " might actually ";
const string CONST_AMONG_THE_MOST_STARTLING_OF_THE_THINK_TANK_S_FINDINGS_IS_THAT = "Among the most startling of the think tank's findings is that ";
const string CONST_AND_THE_LATEST_SCIENCE_ON_THE_ISSUE = "and the latest science on the issue. ";
const string CONST_RECENTLY_RELEASED_A_WIDE_RANGING_REPORT_DETAILING_RECENT_TRENDS = " recently released a wide-ranging report detailing recent trends ";
const string CONST_POLLUTION_MIGHT_NOT_BE_SO_BAD_AFTER_ALL_THE = " - Pollution might not be so bad after all. The ";

const string CONST_OF_THE_TECH_INDUSTRY_BUT_IS_ALSO_INDICATIVE_OF_A_FULL_ECONOMIC_RECOVER_R = "of the tech industry but is also indicative of a full economic recover.&r";
const string CONST_ANALYSTS_SUGGEST_THAT_NOT_ONLY_DOES_THE_EXPANSION_SPEAK_TO_THE_HEALTH = "analysts suggest that not only does the expansion speak to the health ";
const string CONST_FUTURES_OF_SOME_OF_THE_COMPANIES_IN_THE_TECH_SECTOR_ON_THE_WHOLE_HOWEVER = "futures of some of the companies in the tech sector. On the whole, however, ";
const string CONST_ALTHOUGH_THE_DAMPENED_MOVEMENT_MIGHT_BE_EXPECTED_DUE_TO_THE_UNCERTAIN = "although the dampened movement might be expected due to the uncertain ";
const string CONST_THE_MARKETS_REPORTEDLY_RESPONDED_TO_THE_ANNOUNCEMENT_WITH_MILD_INTEREST = "The markets reportedly responded to the announcement with mild interest, ";
const string CONST_THIS_WELCOME_NEWS_IS_BOUND_TO_BE_A_PLEASANT_SURPRISE_TO_THOSE_IN_THE_UNEMPLOYMENT_LINES = "this welcome news is bound to be a pleasant surprise to those in the unemployment lines. ";
const string CONST_OF_LARGE_CORPORATIONS_TO_EXPORT_JOBS_OVERSEAS_THESE_DAYS = "of large corporations to export jobs overseas these days, ";
const string CONST_LIGHT_OF_THE_TENDENCY = "light of the tendency ";
const string CONST_GIVEN_THE_STATE_OF_THE_ECONOMY_RECENTLY_AND_IN = "Given the state of the economy recently and in ";
const string CONST_INCREASING_ITS_PAYROLLS_BY_OVER_TEN_THOUSAND_WORKERS_ALONE = " increasing its payrolls by over ten thousand workers alone. ";
const string CONST_TECH_GIANT = "tech giant ";
const string CONST_ARE_EXPECTED_IN_THE_FIRST_MONTH_WITH = "are expected in the first month, with ";
const string CONST_DURING_THE_NEXT_QUARTER_OVER_THIRTY_THOUSAND_JOBS = "during the next quarter. Over thirty thousand jobs ";
const string CONST_WILL_BE_EXPANDING_THEIR_WORK_FORCES_CONSIDERABLY = "will be expanding their work forces considerably ";
const string CONST_AT_A_JOINT_NEWS_CONFERENCE_HERE_THAT_THEY = "at a joint news conference here that they ";
const string CONST_SEVERAL_MAJOR_COMPANIES_HAVE_ANNOUNCED = " - Several major companies have announced ";

const string CONST_THIS_AMAZING_NEW_PRODUCT_ACTUALLY = "this amazing new product actually ";
const string CONST_ACCORDING_TO_THE_PUBLIC_RELATIONS_REPRESENTATIVE_SPEAKING = "According to the public relations representative speaking, ";
const string CONST_DURING_AN_AFTERNOON_POWERPOINT_PRESENTATION = "\", during an afternoon PowerPoint presentation. ";
const string CONST_PRESENTED_THEIR_PRODUCT = ", presented their product, \"";

const string CONST_BUT_THE_GM_INDUSTRY_OPERATES_AT_A_HIGHER_ETHICAL_STANDARD_THAT_GOES_WITHOUT_SAYING = "but the GM industry operates at a higher ethical standard. That goes without saying.";
const string CONST_NO_THAT_S_JUST_RIDICULOUS_I_MEAN_SURE_COMPANIES_HAVE_PUT_UNSAFE_PRODUCTS_OUT = "No. That's just ridiculous. I mean, sure companies have put unsafe products out, ";
const string CONST_WOULD_WE_STAKE_THE_REPUTATION_OF_OUR_COMPANY_ON_UNSAFE_PRODUCTS = ". Would we stake the reputation of our company on unsafe products? ";
const string CONST_IS_JUST_A_LOAD_OF = " is just a load of ";
const string CONST_LOOK_THESE_PRODUCTS_ARE_SAFE_THAT_THING_ABOUT_THE = "Look, these products are safe. That thing about the ";
const string CONST_ONE_IN_PARTICULAR_SAID = "One in particular said, \"";
const string CONST_IN_THEIR_DISMISSAL_OF_THE_CRITICISM_WHICH_OFTEN_FOLLOWS_THE_INDUSTRY = "in their dismissal of the criticism which often follows the industry. ";
const string CONST_SPOKESPEOPLE_FOR_THE_GM_CORPORATIONS_WERE_UNIVERSAL = " Spokespeople for the GM corporations were universal ";
const string CONST_ONE_SUCH_CORPORATION = " One such corporation, ";
const string CONST_BOOTHS_AND_GAVE_TALKS_TO_WIDE_EYED_ONLOOKERS = "booths and gave talks to wide-eyed onlookers.";
const string CONST_TO_SHOWCASE_ITS_UPCOMING_PRODUCTS_OVER_THIRTY_COMPANIES_SET_UP = "to showcase its upcoming products. Over thirty companies set up ";
const string CONST_THE_GENETIC_FOODS_INDUSTRY_STAGED_A_MAJOR_EVENT_HERE_YESTERDAY = " - The genetic foods industry staged a major event here yesterday ";

const string CONST_DEAD_AND = " dead and ";
const string CONST_IN_A_BETTER_PLACE = " [in a better place]";
const string CONST_THE_DEATH_PENALTY_IN_THIS_CASE = "the death penalty in this case.";
const string CONST_LIFE_IMPRISONMENT_IN_THIS_CASE = "life imprisonment in this case.";
const string CONST_SEEKING = "seeking ";
const string CONST_THE_DISTRICT_ATTORNEY_S_OFFICE_HAS_ALREADY_REPEATEDLY_SAID_IT_WILL_BE = " The district attorney's office has already repeatedly said it will be ";
const string CONST_SOURCES_SAY_THAT_THE_POLICE_GOT_A_BREAK_IN_THE_CASE_WHEN = ". Sources say that the police got a break in the case when ";
const string CONST_ONLY_TO_TURN_UP_LATER = "only to turn up later";
const string CONST_OVER_TWENTY_CHILDREN_IN_THE_PAST_TWO_YEARS_HAVE_GONE_MISSING = ". Over twenty children in the past two years have gone missing, ";
const string CONST_WAS_DETAINED_YESTERDAY_AFTERNOON_REPORTEDLY_IN_POSSESSION_OF = " was detained yesterday afternoon, reportedly in possession of ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_HERE = "according to a spokesperson for the police department here. ";
const string CONST_STRING_OF_BRUTAL_CHILD_KILLINGS_THAT_HAS_KEPT_EVERYONE_IN_THE_AREA_ON_EDGE = "string of brutal child killings that has kept everyone in the area on edge, ";
const string CONST_THE_AUTHORITIES_HAVE_APPREHENDED_THEIR_PRIMARY_SUSPECT_IN_THE = "The authorities have apprehended their primary suspect in the ";
const string CONST_PERHAPS_PARENTS_CAN_REST_EASIER_TONIGHT = " - Perhaps parents can rest easier tonight. ";
const string CONST_SPACE_THE_SPOKESMAN_FURTHER_STATED = " The spokesperson further stated, \"";
const string CONST_THIS_NEW_AGE = "this new age.";
const string CONST_FOR_WHAT_WE_FEEL_ARE_THE_ESSENTIAL_TOOLS_FOR_COMBATING_TERRORISM_IN = "for what we feel are the essential tools for combating terrorism in ";
const string CONST_THE_HEAD_OF_THE_AGENCY_WILL_BE_SENDING_A_REQUEST_TO_CONGRESS = "The Head of the Agency will be sending a request to Congress ";
const string CONST_HOWEVER_LET_ME_ALSO_SAY_THAT_THERE_S_MORE_THAT_NEEDS_TO_BE_DONE = "However, let me also say that there's more that needs to be done. ";
const string CONST_CIVILIZATION_BEFORE_THEY_CAN_DESTROY_AMERICAN_FAMILIES = "civilization before they can destroy American families. ";
const string CONST_PROVIDING_US_WITH_THE_TOOLS_WE_NEED_TO_NEUTRALIZE_THESE_ENEMIES_OF = "providing us with the tools we need to neutralize these enemies of ";
const string CONST_THAT_WE_ARE_GRATEFUL_TO_THE_CONGRESS_AND_THIS_ADMINISTRATION_FOR = "that we are grateful to the Congress and this Administration for ";
const string CONST_I_WON_T_COMPROMISE_OUR_SOURCES_AND_METHODS_BUT_LET_ME_JUST_SAY = "I won't compromise our sources and methods, but let me just say ";
const string CONST_WAS_TO_OCCUR = "was to occur.";
const string CONST_TERRORIST_ORGANIZATION_ALLOWED_THE_PLOT_TO_BE_FOILED_JUST_DAYS_BEFORE_IT = "terrorist organization allowed the plot to be foiled just days before it ";
const string CONST_HOWEVER_INTELLIGENCE_GARNERED_FROM_DEEP_WITHIN_THE_MYSTERIOUS = ". However, intelligence garnered from deep within the mysterious ";
const string CONST_PLANNED_TO = " planned to ";
const string CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_AGENCY = " According to a spokesperson for the agency, ";
const string CONST_WOULD_HAVE_OCCURRED_ON_AMERICAN_SOIL = "would have occurred on American soil.";
const string CONST_WASHINGTON_DC_THE_CIA_ANNOUNCED_YESTERDAY_THAT_IT_HAS_AVERTED_A_TERROR_ATTACK_THAT = "Washington, DC - The CIA announced yesterday that it has averted a terror attack that ";

const string CONST_CONSULTATIONS_WITH_A_MAGIC_8_BALL = " consultations with a Magic 8-Ball";
const string CONST_FAMILY = " family";
const string CONST_CLOSE_PERSONAL_FRIENDSHIP_WITH_THE = " close personal friendship with the ";
const string CONST_PERSONAL_PHILOSOPHY_OF_LIBERTY = " personal philosophy of liberty";
const string CONST_DESERVED_ANOTHER_CHANCE = " deserved another chance";
const string CONST_BELIEF_THAT = " belief that ";
const string CONST_BELIEF_THAT_THE_CRIMES_WERE_A_VAST_RIGHT_WING_CONSPIRACY = " belief that the crimes were a vast right-wing conspiracy";
const string CONST_GENERAL_FEELING_ABOUT_POLICE_CORRUPTION = " general feeling about police corruption";
const string CONST_TEN_YEAR_OLD_EYEWITNESS_TESTIMONY = "ten-year-old eyewitness testimony";
const string CONST_I_WOULD_KILL_AGAIN = "If I were to be released, I would surely kill again.\"";

const string CONST_COMPLETELY_STRAPPED_FOR_CASH_R = "completely strapped for cash.&r";
const string CONST_TO_THE_CURRENT_ECONOMIC_DOLDRUMS_THAT_HAVE_LEFT_THE_STATE = "to the current economic doldrums that have left the state ";
const string CONST_HAS_STATED_THAT_THE_CASE_WILL_NOT_BE_RETRIED_DUE = "has stated that the case will not be retried, due ";
const string CONST_A_SPOKESPERSON_FOR_THE_DISTRICT_ATTORNEY = " A spokesperson for the district attorney ";
const string CONST_THANK_YOU_FOR_SAVING_ME_FROM_MYSELF = "Thank you for saving me from myself. ";
const string CONST_CONFESSED_AND_WAS_SENTENCED_TO_LIFE_SAYING = " confessed and was sentenced to life, saying \"";
const string CONST_COVERED_IN_THE_VICTIMS_BLOOD = "covered in the victims' blood. ";
const string CONST_WAS_FOUND_WITH_THE_MURDER_WEAPON = " was found with the murder weapon, ";
const string CONST_AFTER_AN_INTENSIVE_MANHUNT = "After an intensive manhunt, ";
const string CONST_SLAYINGS = " slayings. ";
const string CONST_WAS_CONVICTED_OF_THE_NOW_INFAMOUS = " was convicted of the now-infamous ";
const string CONST_TEN_YEARS_AGO = " Ten years ago, ";
const string CONST_GRANTS_WAS_NOT_COERCED_IN_ANY_WAY_R = " grants was not coerced in any way.&r";
const string CONST_WHICH_EVEN_JUSTICE = ", which even Justice ";
const string CONST_DESPITE_THE_CONFESSION_OF = ", despite the confession of ";

const string CONST_MADE_THE_DECISION_BASED_ON = "made the decision based on ";
const string CONST_OF_THE_NOTORIOUSLY_LIBERAL_CIRCUIT_OF_APPEALS_HERE = " of the notoriously liberal circuit of appeals here ";
const string CONST_JUSTICE = "Justice ";
const string CONST_WAS_OVERTURNED_BY_A_FEDERAL_JUDGE_YESTERDAY = " was overturned by a federal judge yesterday. ";
const string CONST_THE_CONVICTION_OF_CONFESSED_SERIAL_KILLER = " - The conviction of confessed serial killer ";
const string CONST_MASTURBATED = "masturbated";
const string CONST_HAD_FUN = "[had fun]";
const string CONST_BREASTFED_FROM_A_LACTATING_WOMAN = "breastfed from a lactating woman";
const string CONST_FED_FROM_A_WOMAN = "[fed] from a [woman]";
const string CONST_BREASTFED_FROM_AN_EXPOSED_WOMAN = "breastfed from an exposed woman";
const string CONST_FED_FROM_AN_INDECENT_WOMAN = "[fed] from [an indecent] woman";
const string CONST_SCREAMED_F_CK_THE_POLICE_THOSE_G_DD_MN_M_TH_F_CK_RS_I_GOT_A_F_CKING_TICKET_THIS_MORNING_AND_I_M_F_CKING_P_SS_D_AS_SH_T = "screamed \"f*ck the police those g*dd*mn m*th*f*ck*rs. I got a f*cking ticket this morning and I'm f*cking p*ss*d as sh*t.\"";
const string CONST_SCREAMED_DARN_THE_POLICE_THOSE_BIG_DUMB_JERKS_I_GOT_A_STUPID_TICKET_THIS_MORNING_AND_I_M_SO_ANGRY = "screamed \"[darn] the police those [big dumb jerks]. I got a [stupid] ticket this morning and I'm [so angry].\"";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_RELIEVE_THEMSELVES = "encouraged listeners to call in and relieve themselves";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_TAKE_A_PISS = "encouraged listeners to call in and take a piss";
const string CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_URINATE = "encouraged listeners to call in and [urinate]";
const string CONST_HAD_INTERCOURSE = "had intercourse";
const string CONST_FUCKED = "fucked";
const string CONST_HAD_CONSENSUAL_INTERCOURSE_IN_THE_MISSIONARY_POSITION = "[had consensual intercourse in the missionary position]";
const string CONST_SCREAMED_FUCK_POLICE_AND_MORE = "screamed \"fuck the police those goddamn motherfuckers. I got a fucking ticket this morning and I'm fucking pissed as shit.\"";

const string CONST_SOME = "some";
const string CONST_DOZENS_OF = "dozens of";
const string CONST_HUNDREDS_OF = "hundreds of";
const string CONST_SEVERAL_HUNDRED = "several hundred";
const string CONST_THOUSANDS_OF = "thousands of";
const string CONST_WITHIN_THE_TOWN = "within the town. ";
const string CONST_IN_NEIGHBORING_TOWNS = "in neighboring towns. ";
const string CONST_WITHIN_THE_COUNTY = "within the county. ";
const string CONST_FROM_ALL_OVER_THE_STATE = "from all over the state. ";
const string CONST_ACROSS_THE_NATION = "across the nation. ";
const string CONST_STATED_THAT_THE_INCIDENT_IS_UNDER_INVESTIGATION = "stated that the incident is under investigation.";
const string CONST_A_SPOKESPERSON_FOR_THE_FCC = " A spokesperson for the FCC ";
const string CONST_FROM_IRATE_LISTENERS = "from irate listeners ";
const string CONST_COMPLAINTS = " complaints ";
const string CONST_THE_FCC_RECEIVED = "the FCC received ";
const string CONST_LATER_APOLOGIZED = " later apologized, ";
const string CONST_ON_THE_AIR_ALTHOUGH = " on the air. Although ";

const string CONST_REPORTEDLY = " reportedly ";
const string CONST_QUOTATION_COMMA_SPACE = "\", ";
const string CONST_APOS_S_SPACE = "'s ";
const string CONST_BROADCAST_OF_THE_PROGRAM = "broadcast of the program \"";
const string CONST_HAS_BROUGHT_RADIO_ENTERTAINMENT_TO_A_NEW_LOW_DURING_YESTERDAY_S = " has brought radio entertainment to a new low. During yesterday's ";
const string CONST_INFAMOUS_FM_RADIO_SHOCK_JOCK = " - Infamous FM radio shock jock ";
const string CONST_MISS_SPACE = "Miss ";
const string CONST_MR = "Mr. ";
const string CONST_MRS = "Mrs. ";
const string CONST_MS = "Ms. ";
const string CONST_MASS_SHOOTING = "mass shooting";
const string CONST_FIREFIGHT_KILLING_THE_ATTACKER = "firefight, killing the attacker ";
const string CONST_FIREFIGHT_PUTTING_THE_ATTACKER_TO_SLEEP = "firefight, [putting the attacker to sleep] ";

const string CONST_HE_LOWERCASE_SPACE = "he ";

const string CONST_S_HEROIC_ACTIONS = "'s heroic actions.\"";
const string CONST_IF_NOT_FOR = " if not for ";
const string CONST_THE_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_SAID_WE_D_HAVE_A_YET_ANOTHER = " The spokesperson for the police department said, \"We'd have a yet another ";
const string CONST_COULD_HURT_ANYONE_ELSE_R = "could hurt anyone else.&r";
const string CONST_SHE_LOWERCASE_SPACE = "she ";
const string CONST_BEFORE = "before ";

const string CONST_BECAME_MORE_AGITATED_THE_HEROIC_CITIZEN_WAS_FORCED_TO_ENGAGE_THE_SHOOTER_IN_A = " became more agitated, the heroic citizen was forced to engage the shooter in a ";
const string CONST_ATTEMPTED_TO_TALK_DOWN_THE_SHOOTER_BUT_AS = " attempted to talk down the shooter, but as ";
const string CONST_INITIALLY = " Initially, ";
const string CONST_TO_TAKE_COVER_WHILE_OTHERS_CALLED_THE_POLICE_R = " to take cover while others called the police.&r";
const string CONST_FORCING = "forcing ";
const string CONST_THE_CITIZEN_PULLED_A_CONCEALED_HANDGUN_AND_FIRED_ONCE_AT_THE_SHOOTER = "The citizen pulled a concealed handgun and fired once at the shooter, ";
const string CONST_SPRUNG_INTO_ACTION = " sprung into action. ";
const string CONST_OPENED_FIRE_AT_THE = " opened fire at the ";
const string CONST_AFTER = " After ";
const string CONST_WAS_PREVENTED_BY_A_BYSTANDER_WITH_A_GUN = " was prevented by a bystander with a gun.";
const string CONST_IN_A_SURPRISING_TURN_A = " - In a surprising turn, a ";
const string CONST_IMMA_KILL_ALL_YOU_B_TCHES_STARTIN_WITH_THIS_M_TH_F_CK_R_HERE = "Imma kill all you b*tches, startin' with this m*th*f*ck*r here.";
const string CONST_I_WILL_HARM_ALL_POLICE_OFFICERS_STARTIN_WITH_THIS_ONE_HERE = "[I will harm all police officers], startin' with this [one] here.";
const string CONST_IMMA_KILL_ALL_YOU_BITCHES_STARTIN_WITH_THIS_MOTHAFUCKER_HERE = "Imma kill all you bitches, startin' with this mothafucker here.";
const string CONST_WHY_THE_F_CK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the f*ck am I talkin' to you? I'd rather kill this pig.";
const string CONST_WHY_AM_I_TALKIN_TO_YOU_I_D_RATHER_HARM_THIS_POLICE_OFFICER = "Why [am I] talkin' to you? I'd rather [harm this police officer.]";
const string CONST_WHY_THE_FUCK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG = "Why the fuck am I talkin' to you? I'd rather kill this pig.";
const string CONST_F_CK_A_M_TH_F_CK_N_BULL_I_M_KILLIN_THIS_PIG_SH_T = "F*ck a m*th*f*ck*n' bull. I'm killin' this pig sh*t.";
const string CONST_TOO_LATE_I_AM_GOING_TO_HARM_THIS_POLICE_OFFICER = "[Too late.] [I am going to harm this police officer.]";
const string CONST_FUCK_A_MUTHAFUCKIN_BULL_I_M_KILLIN_THIS_PIG_SHIT = "Fuck a muthafuckin' bull. I'm killin' this pig shit.";
const string CONST_AH_F_CK_THIS_SH_T_THIS_PUNK_B_TCH_IS_F_CKIN_DEAD = "Ah, f*ck this sh*t. This punk b*tch is f*ckin' dead!";
const string CONST_AH_NO_WAY_THIS_POLICE_OFFICER_WILL_BE_HARMED = "Ah, [no way.] This [police officer will be harmed!]";
const string CONST_AH_FUCK_THIS_SHIT_THIS_PUNK_BITCH_IS_FUCKIN_DEAD = "Ah, fuck this shit. This punk bitch is fuckin' dead!";
const string CONST_KILLED_THE_GUARD = "killed the guard";
const string CONST_HARMED_THE_GUARD = "[harmed] the guard";

const string CONST_NEO_PAGAN_LOWERCASE = "neo-pagan";
const string CONST_BLOODS_CAPITALIZED = "Bloods";

const string CONST_ALTAR = " altar";
const string CONST_SATANIC = "Satanic";
const string CONST_SACRIFICED_THE_GUARD_ON_A_MAKESHIFT = "sacrificed the guard on a makeshift ";

const string CONST_OFF = " off";
const string CONST_TAKEN_THE_GUARD_TO_THE_EXECUTION_CHAMBER_AND_FINISHED = "taken the guard to the execution chamber and finished ";
const string CONST_CRIPS = "Crips";
const string CONST_POISONED_THE_GUARD_WITH_DRUGS_SMUGGLED_INTO_THE_PRISON_BY_THE = "poisoned the guard with drugs smuggled into the prison by the ";
const string CONST_OWN_GUN = " own gun";
const string CONST_SHOT_THE_GUARD_WITH = "shot the guard with ";
const string CONST_CELL = " cell";
const string CONST_SMASHED_THE_GUARD_S_SKULL_WITH_THE_TOILET_SEAT_FROM = "smashed the guard's skull with the toilet seat from ";
const string CONST_BEATEN_TO_DEATH = "beaten to death";
const string CONST_ALSO_HARMED = "[also harmed]";

const string CONST_TWO_WEEKS_AGO_CONVICTED_RAPIST = " Two weeks ago, convicted rapist ";
const string CONST_TWO_WEEKS_AGO_CONVICTED_REPRODUCTION_FIEND = " Two weeks ago, convicted [reproduction fiend] ";

const string CONST_HIMSELF_LOWERCASE = "himself";

const string CONST_WHILE_RESISTING_CAPTURE_ACCORDING_TO_A_PRISON_SPOKESPERSON = " while \"resisting capture\", according to a prison spokesperson.";
const string CONST_THE_PRISONER_WAS = ". The prisoner was ";
const string CONST_HAD_ALREADY = " had already ";
const string CONST_THE_HOSTAGE_BUT = "the hostage, but ";
const string CONST_THE_TOWER_WAS_BREACHED_IN_AN_ATTEMPT_TO_REACH = " The tower was breached in an attempt to reach ";
const string CONST_REPORTEDLY_SCREAMED_INTO_THE_RECEIVER = " reportedly screamed into the receiver \"";
const string CONST_DAYS_BUT_TALKS_WERE_CUT_SHORT_WHEN = " days, but talks were cut short when ";
const string CONST_ATTEMPTED_TO_NEGOTIATE_BY_PHONE_FOR = "attempted to negotiate by phone for ";
const string CONST_AUTHORITIES_LOCKED_DOWN_THE_PRISON_AND = "Authorities locked down the prison and ";
const string CONST_WITH_THE_GUARD_IN_A_PRISON_TOWER = " with the guard in a prison tower. ";
const string CONST_HERSELF = "herself";
const string CONST_AND_BARRICADED = " and barricaded ";
const string CONST_OVERPOWERED = ", overpowered ";
const string CONST_AN_INMATE_AT = ", an inmate at ";
const string CONST_CAPTOR = " captor.";
const string CONST_DEATH_OF_BOTH_THE_PRISON_GUARD_BEING_HELD_HOSTAGE_AND = "death of both the prison guard being held hostage and ";
const string CONST_CORRECTIONAL_FACILITY_ENDED_TRAGICALLY_YESTERDAY_WITH_THE = " Correctional Facility ended tragically yesterday with the ";
const string CONST_THE_HOSTAGE_CRISIS_AT_THE = " - The hostage crisis at the ";
const string CONST_X_BUT_DID_FIND_A_ = " but did find a ";
const string CONST_X_WAS_UNABLE_TO_FIND_A_ = " was unable to find a ";
const string CONST_CALL_IT_A_DAY_PRESS_ENTER = "Enter - Call it a day.";

const string CONST_X_ENTER_YES_THE_VIPER_HAS_DETERRED_ = "Enter - Yes, the Viper has deterred ";
const string CONST_X_IS_DETERRED = " is deterred.";
const string CONST_X_ENTER_THE_VIPER_ = "Enter - The Viper?   ";
const string CONST_WONDERS_ABOUT_DEATH = " wonders about death.";
const string CONST_WONDERS_ABOUT_APPLES = " wonders about apples.";
const string CONST_CRIES_HELPLESSLY = " cries helplessly.";
const string CONST_BARKS_HELPLESSLY = " barks helplessly.";
const string CONST_CURLS_UP_IN_THE_CORNER_AND_DOESN_T_MOVE = " curls up in the corner and doesn't move.";
const string CONST_GOES_LIMP_IN_THE_RESTRAINTS = " goes limp in the restraints.";
const string CONST_MOMMY = "mommy.";
const string CONST_GOD_S_MERCY = "God's mercy.";
const string CONST_JOHN_LENNON_S_MERCY = "John Lennon's mercy.";
const string CONST_SCREAMS_HELPLESSLY_FOR = " screams helplessly for ";

const string CONST_TALKS_ABOUT_HUGGING = "talks about hugging ";
const string CONST_STAMMERS_AND = " stammers and ";

const string CONST_HUGS = "hugs ";

const string CONST_BEGS_FOR_THE_NIGHTMARE_TO_END = " begs for the nightmare to end.";
const string CONST_CURLS_UP_AND = " curls up and";
const string CONST_TO_STOP_LOOKING_LIKE_HITLER = " to stop looking like Hitler.";
const string CONST_SCREAMS_FOR = " screams for ";
const string CONST_BEGS_HITLER_TO_STAY_AND_KILL = " begs Hitler to stay and kill ";
const string CONST_GRACEFULLY_STRIKES_AT = "gracefully strikes at";
const string CONST_JUMP_KICKS = "jump kicks";
const string CONST_STRIKES_AT = "strikes at";
const string CONST_KICKS = "kicks";
const string CONST_GRAPPLES_WITH = "grapples with";
const string CONST_SWINGS_AT = "swings at";
const string CONST_PUNCHES = "punches";
const string CONST_BLOWING_IT_OFF = " BLOWING IT OFF!";
const string CONST_CUTTING_IT_OFF = " CUTTING IT OFF!";
const string CONST_BLOWING_IT_IN_HALF = " BLOWING IT IN HALF!";
const string CONST_BLOWING_IT_APART = " BLOWING IT APART!";
const string CONST_CUTTING_IN_HALF = " CUTTING IT IN HALF!";
const string MISSING_TEETH = "Missing Teeth";
const string NO_TEETH = "No Teeth";
const string NO_TONGUE = "No Tongue";

const string BROKEN_RIBS = "Broken Ribs";
const string BROKEN_RIB = "Broken Rib";
const string ALL_RIBS_BROKEN = "All Ribs Broken";
const string BUSTED_SPLEEN = "Busted Spleen";
const string STOMACH_INJURED = "Stomach Injured";
const string L_KIDNEY_DAMAGED = "L. Kidney Damaged";
const string R_KIDNEY_DAMAGED = "R. Kidney Damaged";
const string LIVER_DAMAGED = "Liver Damaged";
const string MISSING_TOOTH = "Missing a Tooth";
const string NO_NOSE = "No Nose";
const string NO_LEFT_EYE = "No Left Eye";
const string NO_RIGHT_EYE = "No Right Eye";
const string BROKEN_LW_SPINE = "Broken Lw Spine";
const string BROKEN_UP_SPINE = "Broken Up Spine";
const string BROKEN_NECK = "Broken Neck";
const string L_LUNG_COLLAPSED = "L. Lung Collapsed";
const string R_LUNG_COLLAPSED = "R. Lung Collapsed";
const string HEART_PUNCTURED = "Heart Punctured";
const string PARENTHESIS_COLON = "): ";

const string CONST_X_MID_ = ".mid:  ";
const string CONST_MID = ".mid";
const string CONST_X_OGG_COLON = ".ogg:  ";
const string CONST_X_OGG = ".ogg";
const string CONST_SLASH = "/";
const string CONST_MID_AS_MIDI_FALLBACK = ".mid as MIDI fallback)";
const string CONST_1234567890 = "1234567890-";
const string CONST_SDL_MIXER_FUNCTION_MIX_PLAYMUSIC_FAILED = "SDL_mixer function Mix_PlayMusic() failed:  ";
const string CONST_OGG_VORBIS_SUPPORT_FAILED_TO_LOAD_MIDI_MUSIC_WILL_BE_USED_INSTEAD_IF_POSSIBLE = "Ogg Vorbis support failed to load. MIDI music will be used instead if possible.";
const string CONST_UNABLE_TO_INITIALIZE_SDL_MIXER = "Unable to initialize SDL_mixer:  ";
const string CONST_UNABLE_TO_INITIALIZE_SDL = "Unable to initialize SDL:  ";
const string CONST_SDL_MIXER_FUNCTION_MIX_LOADMUS_FAILED_TO_LOAD = "SDL_mixer function Mix_LoadMUS() failed to load ";
const string CONST_MIDI = "midi/";
const string CONST_OGG = "ogg/";
const string CONST_LOADING_MIDI_MUSIC = "Loading MIDI music (";
const string CONST_WITH = "(with ";
const string CONST_LOADING_OGG_VORBIS_MUSIC = "Loading Ogg Vorbis music (";
const string CONST_LISTOFSTATES_TXT = "listOfStates.txt";
const string CONST_SEXTYPEACRONYM_TXT = "sextypeAcronym.txt";
const string CONST_SEXSEEKACRONYM_TXT = "sexseekAcronym.txt";
const string CONST_SEXWHOACRONYM_TXT = "sexwhoAcronym.txt";
const string CONST_SEXDESCACRONYM_TXT = "sexdescAcronym.txt";
vector<string> listOfStates;
vector<file_and_text_collection> misc_text_file_collection = {
customText(&sexdescAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXDESCACRONYM_TXT),
customText(&sexwhoAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXWHOACRONYM_TXT),
customText(&sexseekAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXSEEKACRONYM_TXT),
customText(&sextypeAcronym, MOSTLY_ENDINGS_FOLDER + CONST_SEXTYPEACRONYM_TXT),
customText(&listOfStates, MOSTLY_ENDINGS_FOLDER + CONST_LISTOFSTATES_TXT),
};
const vector<string> elementary = { CONST_ELEMENTARY_SCHOOL, CONST_ELEMENTARY_SCHOOL_UPPER_CASE };
const vector<string> middle = { CONST_MIDDLE_SCHOOL, CONST_MIDDLE_SCHOOL_UPPER_CASE };
const vector<string> high = { CONST_HIGH_SCHOOL, CONST_HIGH_SCHOOL_UPPER_CASE };
const vector<string> university = { CONST_UNIVERSITY, CONST_UNIVERSITY_UPPER_CASE };
map<int, vector<string> > SchoolTypes = {
	map<int, vector<string> >::value_type(0, elementary),
	map<int,  vector<string> >::value_type(1, middle),
	map<int,  vector<string> >::value_type(2, high),
	map<int,  vector<string> >::value_type(3, university),
};

