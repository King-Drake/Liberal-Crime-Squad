




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
const int RNG_SIZE = 4;  // needed for locations.h
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

#include "includesDeprecatedB.h"
//#ifdef	EXTERNALLYSTOREDDATA_CPP
// externallyStoredData.cpp

const string talky = "talk\\";
const string MOSTLY_ENDINGS_FOLDER = "mostlyendings\\";

const string CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT = "attend classes in the University District";
const string CONST_AT_A_COST_OF_60_A_DAY = "at a cost of $60 a day.";


const string CONST_SELL_LIBERAL_ART = "Sell Liberal Art";
const string CONST_SELL_LIBERAL_T_SHIRTS = "Sell Liberal T-Shirts";
const string CONST_UNCONTROLLED_IMMIGRATION = "uncontrolled immigration.";
const string CONST_LEGALIZING_NUCLEAR_POWER = "legalizing nuclear power.";
const string CONST_RESTORING_THE_DEATH_PENALTY = "restoring the death penalty.";
const string CONST_CLASSES_COST_UP_TO_60_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND = "Classes cost up to $60/day to conduct. All Liberals able will attend.";
const string CONST_CLASSES_COST_UP_TO_20_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND = "Classes cost up to $20/day to conduct. All Liberals able will attend.";
const string CONST_WILL_CREATE_AND_SELL_PAINTINGS_EMBRACING_THE_LIBERAL_AGENDA = "will create and sell paintings embracing the Liberal agenda.";
const string CONST_WILL_PRINT_AND_DISTRIBUTE_SHIRTS_WITH_LIBERAL_SLOGANS = "will print and distribute shirts with Liberal slogans.";
const string CONST_ACTIVIST_IS = "activist is.";
const string CONST_MULTIPLE_HACKERS_WILL_INCREASE_CHANCES_OF_BOTH_SUCCESS_AND_DETECTION = "Multiple hackers will increase chances of both success and detection.";
const string CONST_AND_INTELLIGENCE_WILL_PROVIDE_BETTER_RESULTS = "and intelligence will provide better results.";

const string CONST_DRUG_LAW = "Drug Law";
const string CONST_TAX_LAW = "Tax Law";
const string CONST_FREEDOM_OF_SPEECH = "Freedom of Speech";
const string CONST_CORPORATE_ETHICS = "Corporate Ethics";
const string CONST_HOMOSEXUAL_RIGHTS = "Homosexual Rights";
const string CONST_WORKERS_RIGHTS = "Workers' Rights";
const string CONST_CAPITAL_PUNISHMENT = "Capital Punishment";
const string CONST_X_PRIVACY = "Privacy";
const string CONST_POLICE_BEHAVIOR = "Police Behavior";
const string CONST_ANIMAL_RESEARCH = "Animal Research";
const string CONST_X_THE_CCS_TERRORISTS = "The CCS Terrorists";
const string CONST_WHY_WE_ROCK = "Why We Rock";
const string CONST_WHO_WE_ARE = "Who We Are";
const string CONST_THE_NEED_FOR_ACTION = "The Need For Action";
const string CONST_CABLE_NEWS_LIES = "Cable \"News\" Lies";
const string CONST_AM_RADIO_PROPAGANDA = "AM Radio Propaganda";
const string CONST_X_IMMIGRANT_RIGHTS = "Immigrant Rights";
const string CONST_OPPRESSIVE_DRUG_LAWS = "Oppressive Drug Laws";
const string CONST_RACIAL_EQUALITY = "Racial Equality";
const string CONST_GENDER_EQUALITY = "Gender Equality";
const string CONST_X_CEO_COMPENSATION = "CEO Compensation";
const string CONST_X_CORPORATE_CORRUPTION = "Corporate Corruption";
const string CONST_MASS_SHOOTINGS = "Mass Shootings";
const string CONST_THE_JUDICIARY = "The Judiciary";
const string CONST_DANGEROUS_GMOS = "Dangerous GMOs";
const string CONST_X_THE_PRISON_SYSTEM = "The Prison System";
const string CONST_X_TORTURE = "Torture";
const string CONST_POLICE_MISCONDUCT = "Police Misconduct";
const string CONST_X_ANIMAL_CRUELTY = "Animal Cruelty";
const string CONST_NUCLEAR_MELTDOWNS = "Nuclear Meltdowns";
const string CONST_THE_TAX_STRUCTURE = "The Tax Structure";
const string CONST_BARBARIC_EXECUTIONS = "Barbaric Executions";
const string CONST_X_LGBTQ_RIGHTS = "LGBTQ Rights";
const string CONST_X_PUBLIC_MOOD = "Public Mood";
const string CONST_PLAY_LIBERAL_MUSIC = "Play Liberal Music";
const string CONST_SELL_PAINTINGS = "Sell Paintings";
const string CONST_SELL_EMBROIDERED_SHIRTS = "Sell Embroidered Shirts";
const string CONST_ENHANCING_INTERROGATIONS = "enhancing interrogations.";
const string CONST_THE_CCS_TERRORISTS = "the CCS terrorists.";
const string CONST_DEFENDING_THE_NATION = "defending the nation.";
const string CONST_PROTECTING_THE_SECOND_AMENDMENT = "protecting the Second Amendment.";
const string CONST_TROUBLEMAKING_MINORITIES = "troublemaking minorities.";
const string CONST_WOMEN = "women.";
const string CONST_DRUG_ABUSE = "drug abuse.";
const string CONST_ILLEGAL_IMMIGRATION = "illegal immigration.";
const string CONST_PUTTING_THE_PRISONERS_IN_LINE = "putting the prisoners in line.";
const string CONST_RESISTING_COMMUNIST_WAGE_LIMITS = "resisting communist wage limits.";
const string CONST_EXCESSIVE_REGULATION_OF_CORPORATIONS = "excessive regulation of corporations.";
const string CONST_EXCESSIVE_REGULATION_OF_INDUSTRY = "excessive regulation of industry.";
const string CONST_CORRUPT_UNION_THUGS = "corrupt union thugs.";
const string CONST_APPOINTING_PROPER_CONSERVATIVE_JUSTICES = "appointing proper Conservative justices.";
const string CONST_EXCESSIVE_REGULATION_OF_GENETIC_RESEARCH = "excessive regulation of genetic research.";
const string CONST_ENDING_HATE_SPEECH = "ending hate speech.";
const string CONST_NATIONAL_SECURITY_AND_INTELLIGENCE = "national security and intelligence.";
const string CONST_EXPANDING_POLICE_POWERS = "expanding police powers.";
const string CONST_EXCESSIVE_REGULATION_OF_ANIMAL_RESEARCH = "excessive regulation of animal research.";
const string CONST_THREATS_TO_NUCLEAR_POWER = "threats to nuclear power.";
const string CONST_THE_EXCESSIVE_TAX_BURDEN = "the excessive tax burden.";
const string CONST_PROTECTING_THE_DEATH_PENALTY = "protecting the death penalty.";
const string CONST_PROTECTING_THE_TRADITIONAL_FAMILY = "protecting the traditional family.";
const string CONST_CLASSES_COST_UP_TO_100_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND = "Classes cost up to $100/day to conduct. All Liberals able will attend.";
const string CONST_SEDUCTION_PSYCHOLOGY_DRIVING = "Seduction, Psychology, Driving";
const string CONST_RELIGION_BUSINESS_MUSIC_ART = "Religion, Business, Music, Art";
const string CONST_PHYSICALLY_SUPERIOR = "physically superior.";
const string CONST_MAJOR_WEBSITES = "major websites.";
const string CONST_MAGICAL_SHIMMERING_DOORWAYS_TO_THE_ADAMANTIUM_PITS = "magical shimmering doorways to the adamantium pits.";
const string CONST_OR_PLAY_GUITAR_IF_ONE_IS_EQUIPPED = "or play guitar if one is equipped.";
const string CONST_WILL_MAKE_PRETTY_PAINTINGS_AND_SELL_THEM_ON_THE_STREETS = "will make pretty paintings and sell them on the streets.";
const string CONST_WILL_EMBROIDER_SHIRTS_AND_SELL_THEM_ON_THE_STREET = "will embroider shirts and sell them on the street.";
const string CONST_BASED_ON_PERSUASION_PUBLIC_S_VIEW_ON_THE_CAUSE_AND_HOW_WELL_DRESSED_THE = "Based on persuasion, public's view on the cause, and how well dressed the";
const string CONST_COMPUTER_SKILL_AND_INTELLIGENCE_WILL_GIVE_MORE_FREQUENT_RESULTS = "Computer skill and intelligence will give more frequent results.";
const string CONST_WILL_GIVE_GREATER_EFFECT = "will give greater effect.";
const string CONST_POLLS_WILL_GIVE_AN_IDEA_ON_HOW_THE_LIBERAL_AGENDA_IS_GOING_COMPUTERS = "Polls will give an idea on how the liberal agenda is going. Computers";
const string CONST_ENHANCE_THE_LIBERAL_EFFECT = "enhance the liberal effect.";
const string CONST_THAT_IS_LIBERAL = "that is Liberal.";

const string CONST_HIRING_UNDOCUMENTED_WORKERS = "Hiring undocumented workers";
const string CONST_HIRING_ILLEGAL_ALIENS = "Hiring illegal aliens";
const string CONST_X_FLAG_BURNING = "Flag burning";
const string CONST_FLAG_MURDER = "Flag Murder";
const string CONST_LOITERING = "Loitering";
const string CONST_PUBLIC_NUDITY = "Public nudity";
const string CONST_DISTURBING_THE_PEACE = "Disturbing the peace";
const string CONST_RESISTING_ARREST = "Resisting arrest";
const string CONST_VANDALISM = "Vandalism";
const string CONST_BREAKING_AND_ENTERING = "Breaking and entering";
const string CONST_UNLAWFUL_BURIAL = "Unlawful burial";
const string CONST_HACKING = "Hacking";
const string CONST_ELECTRONIC_SABOTAGE = "Electronic sabotage";
const string CONST_CARRYING_ILLEGAL_WEAPONS = "Carrying illegal weapons";
const string CONST_FIRING_ILLEGAL_WEAPONS = "Firing illegal weapons";
const string CONST_PROSTITUTION = "Prostitution";
const string CONST_THEFT = "Theft";
const string CONST_X_CREDIT_CARD_FRAUD = "Credit card fraud";
const string CONST_GRAND_THEFT_AUTO = "Grand theft auto";
const string CONST_ASSAULT = "Assault";
const string CONST_ARMED_ASSAULT = "Armed assault";
const string CONST_EXTORTION = "Extortion";
const string CONST_RACKETEERING = "Racketeering";
const string CONST_JURY_TAMPERING = "Jury tampering";
const string CONST_RELEASING_PRISONERS = "Releasing prisoners";
const string CONST_ESCAPING_PRISON = "Escaping prison";
const string CONST_DRUG_DEALING = "Drug dealing";
const string CONST_HARMFUL_SPEECH = "Harmful speech";
const string CONST_ARSON = "Arson";
const string CONST_BANK_ROBBERY = "Bank robbery";
const string CONST_KIDNAPPING = "Kidnapping";
const string CONST_MURDER = "Murder";
const string CONST_TERRORISM = "Terrorism";
const string CONST_TREASON = "Treason";
const string CONST_HUMAN_RIGHTS = "Human Rights";
const string CONST_PRISON_REGULATION = "Prison Regulation";
const string CONST_MILITARY_SPENDING = "Military Spending";
const string CONST_ELECTION_REFORM = "Election Reform";
const string CONST_X_IMMIGRATION = "Immigration";
const string CONST_DRUG_LAWS = "Drug Laws";
const string CONST_CC_CIVIL_RIGHTS = "Civil Rights";
const string CONST_X_WOMENS_RIGHTS = "Women's Rights";
const string CONST_TAX_STRUCTURE = "Tax Structure";
const string CONST_X_GUN_CONTROL = "Gun Control";
const string CONST_FLAG_BURNING = "Flag Burning";
const string CONST_X_FREE_SPEECH = "Free Speech";
const string CONST_CORPORATE_LAW = "Corporate Law";
const string CONST_GAY_RIGHTS = "Gay Rights";
const string CONST_LABOR_LAWS = "Labor Laws";
const string CONST_X_POLLUTION = "Pollution";
const string CONST_X_NUCLEAR_POWER = "Nuclear Power";
const string CONST_DEATH_PENALTY = "Death Penalty";
const string CONST_PRIVACY_RIGHTS = "Privacy Rights";
const string CONST_POLICE_REGULATION = "Police Regulation";
const string CONST_ANIMAL_RIGHTS = "Animal Rights";
const string CONST_ABORTION_RIGHTS = "Abortion Rights";
const string CONST_THE_CCS = "the CCS";
const string CONST_THE_LCS = "the LCS";
const string CONST_POLITICAL_VIOLENCE = "political violence";
const string CONST_CABLE_NEWS = "cable news";
const string CONST_AM_RADIO = "AM radio";
const string CONST_THE_MILITARY = "the military";
const string CONST_IMMIGRATION = "immigration";
const string CONST_DRUGS = "drugs";
const string CONST_X_CIVIL_RIGHTS = "civil rights";
const string CONST_WOMEN_S_RIGHTS = "women's rights";
const string CONST_CEO_COMPENSATION = "CEO compensation";
const string CONST_CORPORATIONS = "corporations";
const string CONST_POLLUTION = "pollution";
const string CONST_LABOR_UNIONS = "labor unions";
const string CONST_GUN_CONTROL = "gun control";
const string CONST_JUDGES = "judges";
const string CONST_GENETIC_RESEARCH = "genetic research";
const string CONST_FREE_SPEECH = "free speech";
const string CONST_PRIVACY = "privacy";
const string CONST_THE_PRISON_SYSTEM = "the prison system";
const string CONST_TORTURE = "torture";
const string CONST_COPS = "cops";
const string CONST_ANIMAL_CRUELTY = "animal cruelty";
const string CONST_NUCLEAR_POWER = "nuclear power";
const string CONST_TAXES = "taxes";
const string CONST_THE_DEATH_PENALTY = "the death penalty";
const string CONST_LGBTQ_RIGHTS = "LGBTQ rights";
const string CONST_PUBLIC_MOOD = "public mood";
const string CONST_STALINISM = "Stalinism";
const string CONST_AUGMENTING_LIBERAL = "Augmenting Liberal";
const string CONST_STEALING_EQUIPMENT = "Stealing Equipment";
const string CONST_EMBEZZLING_FUNDS = "Embezzling Funds";
const string CONST_CREATING_A_SCANDAL = "Creating a Scandal";
const string CONST_QUITTING_JOB = "Quitting Job";
const string CONST_RECRUITING_SLEEPERS = "Recruiting Sleepers";
const string CONST_SNOOPING_AROUND = "Snooping Around";
const string CONST_SPOUTING_CONSERVATISM = "Spouting Conservatism";
const string CONST_PROMOTING_LIBERALISM = "Promoting Liberalism";
const string CONST_ATTENDING_CLASSES = "Attending Classes";
const string CONST_GOING_TO_FREE_CLINIC = "Going to Free CLINIC";
const string CONST_WRITING_NEWS = "Writing news";
const string CONST_WRITING_LETTERS = "Writing letters";
const string CONST_LAYING_LOW = "Laying Low";
const string CONST_TENDING_TO_INJURIES = "Tending to Injuries";
const string CONST_SELLING_BROWNIES = "Selling Brownies";
const string CONST_SOLICITING_DONATIONS = "Soliciting Donations";
const string CONST_DISPOSING_OF_BODIES = "Disposing of Bodies";
const string CONST_SELLING_MUSIC = "Selling Music";
const string CONST_TEACHING_COVERT_OPS = "Teaching Covert Ops";
const string CONST_TEACHING_FIGHTING = "Teaching Fighting";
const string CONST_TEACHING_POLITICS = "Teaching Politics";
const string CONST_SELLING_ART = "Selling Art";
const string CONST_SELLING_T_SHIRTS = "Selling T-Shirts";
const string CONST_HACKING_NETWORKS = "Hacking Networks";
const string CONST_ATTACKING_WEBSITES = "Attacking Websites";
const string CONST_EXTORTING_WEBSITES = "Extorting Websites";
const string CONST_CREDIT_CARD_FRAUD = "Credit Card Fraud";
const string CONST_MAKING_GRAFFITI = "Making Graffiti";
const string CONST_VOLUNTEERING = "Volunteering";
const string CONST_PROSTITUTING = "Prostituting";
const string CONST_CAUSING_TROUBLE = "Causing Trouble";
const string CONST_GATHERING_OPINION_INFO = "Gathering Opinion Info";
const string CONST_STEALING_A_CAR = "Stealing a Car";
const string CONST_PROCURING_A_WHEELCHAIR = "Procuring a Wheelchair";
const string CONST_REPAIRING_CLOTHING = "Repairing Clothing";
const string CONST_X_RECRUITING = "Recruiting";
const string CONST_NEW_YORK = "New York";
const string CONST_LOS_ANGELES = "Los Angeles";
const string CONST_A_TROPICAL_PARADISE = "A Tropical Paradise.";
const string CONST_THE_PRIDE_OF_THE_SOUTH = "The Pride of the South.";
const string CONST_MURDER_CAPITAL_OF_AMERICA = "Murder Capital of America.";
const string CONST_MAFIA_HEADQUARTERS = "Mafia Headquarters.";
const string CONST_THE_NATION_S_CAPITAL = "The Nation's Capital.";
const string CONST_WALL_STREET_AND_BIG_MEDIA = "Wall Street and Big Media.";
const string CONST_HOLLYWOOD_AND_TRADE = "Hollywood and Trade.";
const string CONST_BIRTHPLACE_OF_THE_LCS = "Birthplace of the LCS.";
const string CONST_X_CLOSE_BRACKET = "]";
const string CONST_SLEEPER = "Sleeper";
const string SPACE_OPEN_BRACKET = " [";
const string CONST_IN_HIDING = "In Hiding";
const string CONST_IN_JAIL = "In Jail";
const string CONST_ARRESTED = "Arrested";
const string TWO_SPACE_OPEN_BRACKET = "   [";
const string CONST_ENLIGHTENED = "Enlightened";
const string CONST_X_BACKSLASH = "/";
const string CONST_SEDUCED = "Seduced";
const string CONST_RECRUITED = "Recruited/";
const string CONST_DAYS_UNTIL_RETURN = "DAYS UNTIL RETURN";
const string CONST_DAYS_SINCE_PASSING = "DAYS SINCE PASSING";
const string CONST_PROFESSION = "PROFESSION";
const string CONST_PROGNOSIS = "PROGNOSIS";
const string CONST_MONTHS_LEFT = "MONTHS LEFT";
const string CONST_DAYS_IN_CAPTIVITY = "DAYS IN CAPTIVITY";
const string CONST_SQUAD_ACTIVITY = "SQUAD / ACTIVITY";
const string CONST_LIBERALS_THAT_ARE_AWAY = "Liberals that are Away";
const string CONST_LIBERAL_MARTYRS_AND_DEAD_BODIES = "Liberal Martyrs and Dead Bodies";
const string CONST_X_SLEEPERS = "Sleepers";
const string CONST_LIBERALS_AND_THE_JUSTICE_SYSTEM = "Liberals and the Justice System";
const string CONST_LIBERALS_IN_CLINICS = "Liberals in CLINICS";
const string CONST_CONSERVATIVE_AUTOMATONS_IN_CAPTIVITY = "Conservative Automatons in Captivity";
const string CONST_X_ACTIVE_LIBERALS = "Active Liberals";

const string CONST_WHITEHOUSE = "WhiteHouse";
const string CONST_NUCLEARPLANT = "NuclearPlant";
const string CONST_BANK = "Bank";
const string CONST_PARK = "Park";
const string CONST_VEGANCOOP = "VeganCoOp";
const string CONST_LATTESTAND = "LatteStand";
const string CONST_CIGARBAR = "CigarBar";
const string CONST_INTERNETCAFE = "InternetCafe";
const string CONST_JUICEBAR = "JuiceBar";
const string CONST_CABLENEWS = "CableNews";
const string CONST_RADIOSTATION = "RadioStation";
const string CONST_CEOHOUSE = "CEOHouse";
const string CONST_CORPORATEHQ = "CorporateHQ";
const string CONST_FACTORY = "Factory";
const string CONST_SWEATSHOP = "Sweatshop";
const string CONST_FIRESTATION = "FireStation";
const string CONST_ARMYBASE = "ArmyBase";
const string CONST_INTELLIGENCEHQ = "IntelligenceHQ";
const string CONST_PRISON = "Prison";
const string CONST_COURTHOUSE = "Courthouse";
const string CONST_POLICESTATION = "PoliceStation";
const string CONST_GENETICSLAB = "GeneticsLab";
const string CONST_COSMETICSLAB = "CosmeticsLab";
const string CONST_BUNKER = "Bunker";
const string CONST_BOMBSHELTER = "BombShelter";
const string CONST_BARANDGRILL = "BarAndGrill";
const string CONST_CRACKHOUSE = "CrackHouse";
const string CONST_HOMELESSSHELTER = "HomelessShelter";
const string CONST_WAREHOUSE = "Warehouse";
const string CONST_APARTMENTDOWNTOWN = "ApartmentDowntown";
const string CONST_APARTMENTUNIVERSITY = "ApartmentUniversity";
const string CONST_APARTMENTINDUSTRIAL = "ApartmentIndustrial";
const string CONST_OTHER_EXPENSES = "Other Expenses";
const string CONST_T_SHIRT_MATERIALS = "T-Shirt Materials";
const string CONST_TRAINING = "Training";
const string CONST_SAFEHOUSE_INVESTMENTS = "Safehouse Investments";
const string CONST_RENT = "Rent";
const string CONST_RECRUITMENT = "Recruitment";
const string CONST_PURCHASING_GOODS = "Purchasing Goods";
const string CONST_NEW_CARS = "New Cars";
const string CONST_MANUFACTURING = "Manufacturing";
const string CONST_LEGAL_FEES = "Legal Fees";
const string CONST_HOSTAGE_TENDING = "Hostage Tending";
const string CONST_GROCERIES = "Groceries";
const string CONST_DRAWING_MATERIALS = "Drawing Materials";
const string CONST_DATING = "Dating";
const string CONST_CONFISCATED = "Confiscated";
const string CONST_ACTIVISM = "Activism";
const string CONST_OTHER_INCOME = "Other Income";
const string CONST_T_SHIRT_SALES = "T-Shirt Sales";
const string CONST_THIEVERY = "Thievery";
const string CONST_STREET_MUSIC = "Street Music";
const string CONST_PAWNING_GOODS = "Pawning Goods";
const string CONST_HUSTLING = "Hustling";
const string CONST_EMBEZZLEMENT = "Embezzlement";
const string CONST_DRAWING_SALES = "Drawing Sales";
const string CONST_DONATIONS = "Donations";
const string CONST_CAR_SALES = "Car Sales";
const string CONST_BROWNIES = "Brownies";
const string CONST_ERROR_INVALID_VALUE_FOR_SORTINGCHOICE = "ERROR: INVALID VALUE FOR SORTINGCHOICE!";
const string CONST_SQUADLESS_MEMBERS = "squadless members.";
const string CONST_AVAILABLE_LIBERALS = "available Liberals.";
const string CONST_SLEEPER_ACTIVITY = "sleeper activity.";
const string CONST_LIBERAL_ACTIVITY = "Liberal activity.";
const string CONST_PEOPLE_AWAY = "people away.";
const string CONST_DEAD_PEOPLE = "dead people.";
const string CONST_X_SLEEPERS_DOT = "sleepers.";
const string CONST_OPPRESSED_LIBERALS = "oppressed Liberals.";
const string CONST_LIBERALS_IN_HOSPITAL = "Liberals in hospital.";
const string CONST_HOSTAGES = "hostages.";
const string CONST_ACTIVE_LIBERALS = "active Liberals.";
const string CONST_TEACHER = "Teacher";
const string CONST_TAXI_DRIVER = "Taxi Driver";
const string CONST_PSYCHOLOGIST = "Psychologist";
const string CONST_PROSTITUTE = "Prostitute";
const string CONST_MUTANT = "Mutant";
const string CONST_MUSICIAN = "Musician";
const string CONST_MARTIAL_ARTIST = "Martial Artist";
const string CONST_LOCKSMITH = "Locksmith";
const string CONST_LAWYER = "Lawyer";
const string CONST_JUDGE = "Judge";
const string CONST_JOURNALIST = "Journalist";
const string CONST_HIPPIE = "Hippie";
const string CONST_GANG_MEMBER = "Gang Member";
const string CONST_FASHION_DESIGNER = "Fashion Designer";
const string CONST_DOCTOR = "Doctor";
const string CONST_DANCER = "Dancer";
const string CONST_COMPUTER_PROGRAMMER = "Computer Programmer";
const string CONST_COLLEGE_STUDENT = "College Student";
const string CONST_ATHLETE = "Athlete";
const string CONST_ARMY_VETERAN = "Army Veteran";
const string CONST_URBAN_WARFARE = "Urban Warfare";
const string CONST_INFILTRATION = "Infiltration";
const string CONST_POLITICAL_ACTIVISM = "Political Activism";
const string CONST_TEACH_LIBERALS_ABOUT_WHAT = "Teach Liberals About What?";
const string CONST_AUGMENT_A_LIBERAL = "Augment a Liberal";
const string CONST_PROCURE_A_WHEELCHAIR = "Procure a Wheelchair";
const string CONST_STEAL_A_CAR = "Steal a Car";
const string CONST_X_REPAIR_CLOTHING = "Repair Clothing";
const string CONST_X_MAKE_CLOTHING = "Make Clothing";
const string CONST_STEAL_CREDIT_CARD_NUMBERS = "Steal Credit Card Numbers";
const string CONST_ELECTRONIC_PROTECTION_RACKET = "Electronic Protection Racket";
const string CONST_SELL_BROWNIES = "Sell Brownies";
const string CONST_PLAY_STREET_MUSIC = "Play Street Music";
const string CONST_SELL_PORTRAIT_SKETCHES = "Sell Portrait Sketches";
const string CONST_SELL_TIE_DYED_T_SHIRTS = "Sell Tie-Dyed T-Shirts";
const string CONST_SOLICIT_DONATIONS = "Solicit Donations";
const string CONST_WRITE_FOR_THE_LIBERAL_GUARDIAN = "Write for The Liberal Guardian";
const string CONST_WRITE_TO_NEWSPAPERS = "Write to Newspapers";
const string CONST_HARASS_WEBSITES = "Harass Websites";
const string CONST_SEARCH_OPINION_POLLS = "Search Opinion Polls";
const string CONST_X_GRAFFITI = "Graffiti";
const string CONST_LIBERAL_DISOBEDIENCE = "Liberal Disobedience";
const string CONST_COMMUNITY_SERVICE = "Community Service";
const string CONST_INTERCEPTED_INTERNAL_MEDIA_EMAILS = "intercepted internal media emails.";
const string CONST_PILFERED_FILES_FROM_A_CORPORATE_SERVER = "pilfered files from a Corporate server.";
const string CONST_UNCOVERED_INFORMATION_ON_DANGEROUS_RESEARCH = "uncovered information on dangerous research.";
const string CONST_DISCOVERED_EVIDENCE_OF_JUDICIAL_CORRUPTION = "discovered evidence of judicial corruption.";
const string CONST_SABOTAGED_A_GENETICS_RESEARCH_COMPANY_S_NETWORK = "sabotaged a genetics research company's network.";
const string CONST_SUBVERTED_A_CONSERVATIVE_FAMILY_FORUM = "subverted a Conservative family forum.";
const string CONST_BROKE_INTO_MILITARY_NETWORKS_LEAVING_LCS_SLOGANS = "broke into military networks leaving LCS slogans.";
const string CONST_CAUSED_A_SCARE_BY_BREAKING_INTO_A_CIA_NETWORK = "caused a scare by breaking into a CIA network.";
const string CONST_SPREAD_VIDEOS_OF_RACIST_POLICE_BRUTALITY = "spread videos of racist police brutality.";
const string CONST_PUBLISHED_EMAILS_REVEALING_CEO_TAX_EVASION = "published emails revealing CEO tax evasion.";
const string CONST_REVEALED_HUGE_POLITICAL_BIAS_IN_INS_PROCESSES = "revealed huge political bias in INS processes.";
const string CONST_BUYING_DRINKS = "Buying Drinks";
const string CONST_BASKETBALL = "Basketball";
const string CONST_POLICE_PROCEDURE = "Police Procedure";
const string CONST_BASEBALL = "Baseball";
const string CONST_MAGIC = "Magic";
const string CONST_WEAVING = "Weaving";
const string CONST_FENCING = "Fencing";
const string CONST_COMPUTER_SCIENCE = "Computer Science";
const string CONST_LOCKSMITHING = "Locksmithing";
const string CONST_EDUCATION = "Education";
const string CONST_GYMNASTICS = "Gymnastics";
const string CONST_KUNG_FU = "Kung Fu";
const string CONST_THEATRE = "Theatre";
const string CONST_PAINTING = "Painting";
const string CONST_DRIVERS_ED = "Drivers Ed";
const string CONST_PHYSICS = "Physics";
const string CONST_CRIMINAL_LAW = "Criminal Law";
const string CONST_ECONOMICS = "Economics";
const string CONST_PUBLIC_POLICY = "Public Policy";
const string CONST_ENDING_THE_USE_OF_TORTURE = "ending the use of torture.";
const string CONST_THE_CONSERVATIVE_CRIME_SQUAD = "the Conservative Crime Squad.";
const string CONST_MILITARY_IMPERIALISM = "military imperialism.";
const string CONST_GUN_VIOLENCE = "gun violence.";
const string CONST_CIVIL_RIGHTS = "civil rights.";
const string CONST_WOMEN_S_EQUALITY = "women's equality.";
const string CONST_DRUG_RIGHTS = "drug rights.";
const string CONST_IMMIGRANT_RIGHTS = "immigrant rights.";
const string CONST_STOPPING_THE_PRISONERS_SUFFERING = "stopping the prisoners' suffering.";
const string CONST_SEVERE_INCOME_INEQUALITY = "severe income inequality.";
const string CONST_CORPORATE_CORRUPTION = "corporate corruption.";
const string CONST_THREATS_TO_THE_ENVIRONMENT = "threats to the environment.";
const string CONST_THREATS_TO_LABOR_RIGHTS = "threats to labor rights.";
const string CONST_APPOINTING_PROPER_LIBERAL_JUSTICES = "appointing proper Liberal justices.";
const string CONST_THE_DANGERS_OF_GENETIC_ENGINEERING = "the dangers of genetic engineering.";
const string CONST_PROTECTING_FREE_SPEECH = "protecting free speech.";
const string CONST_CIVIL_LIBERTIES_AND_PERSONAL_PRIVACY = "civil liberties and personal privacy.";
const string CONST_PREVENTING_POLICE_BRUTALITY = "preventing police brutality.";
const string CONST_BRUTAL_ANIMAL_RESEARCH_PRACTICES = "brutal animal research practices.";
const string CONST_THE_DANGERS_OF_NUCLEAR_POWER = "the dangers of nuclear power.";
const string CONST_THE_OPPRESSIVE_TAX_STRUCTURE = "the oppressive tax structure.";
const string CONST_THE_UNJUST_DEATH_PENALTY = "the unjust death penalty.";
const string CONST_PROTECTING_GAY_RIGHTS = "protecting gay rights.";
const string CONST_SKILLS_TRAINED_ALL_WEAPON_SKILLS_MARTIAL_ARTS_DODGE_FIRST_AID = "Skills Trained: All Weapon Skills, Martial Arts, Dodge, First Aid";
const string CONST_SKILLS_TRAINED_COMPUTERS_SECURITY_STEALTH_DISGUISE_TAILORING = "Skills Trained: Computers, Security, Stealth, Disguise, Tailoring,";
const string CONST_SKILLS_TRAINED_WRITING_PERSUASION_LAW_STREET_SENSE_SCIENCE = "Skills Trained: Writing, Persuasion, Law, Street Sense, Science,";
const string CONST_BURY_DEAD_BODIES = "bury dead bodies.";
const string CONST_GO_TO_THE_CLINIC = "go to the clinic.";
const string CONST_TEND_TO_HOSTAGES = "tend to hostages.";
const string CONST_ATTEMPT_FIRST_AID = "attempt first aid.";
const string CONST_WILL_AUGMENT_ANOTHER_LIBERAL_TO_MAKE_THEM = "will augment another Liberal to make them";
const string CONST_TRY_TO_FIND_A_WHEELCHAIR = "try to find a wheelchair.";
const string CONST_REPAIR_CLOTHING = "repair clothing.";
const string CONST_MAKE_CLOTHING = "make clothing.";
const string CONST_TRY_TO_FIND_AND_STEAL_A_CAR = "try to find and steal a car.";
const string CONST_TRY_TO_FIND_SOMEONE_TO_JOIN_THE_LCS = "try to find someone to join the LCS.";
const string CONST_DEMAND_MONEY_IN_EXCHANGE_FOR_NOT_BRINGING_DOWN = "demand money in exchange for not bringing down";
const string CONST_COMMIT_CREDIT_CARD_FRAUD_ONLINE = "commit credit card fraud online.";
const string CONST_TRADE_SEX_FOR_MONEY = "trade sex for money.";
const string CONST_BAKE_AND_SELL_SPECIAL_ADULT_BROWNIES_THAT_OPEN = "bake and sell special adult brownies that open";
const string CONST_GO_OUT_INTO_THE_STREETS_AND_DRUM_ON_BUCKETS = "go out into the streets and drum on buckets,";
const string CONST_SKETCH_PEOPLE_AND_SELL_PORTRAITS_BACK_TO_THEM = "sketch people and sell portraits back to them.";
const string CONST_TIE_DYE_T_SHIRTS_AND_SELL_THEM_ON_THE_STREET = "tie-dye T-shirts and sell them on the street.";
const string CONST_WALK_AROUND_AND_ASK_FOR_DONATIONS_TO_THE_LCS = "walk around and ask for donations to the LCS.";
const string CONST_WRITE_ARTICLES_FOR_THE_LCS_S_NEWSPAPER = "write articles for the LCS's newspaper.";
const string CONST_WRITE_LETTERS_TO_NEWSPAPERS_ABOUT_CURRENT_EVENTS = "write letters to newspapers about current events.";
const string CONST_HARASS_WEBSITES_AND_HACK_PRIVATE_NETWORKS = "harass websites and hack private networks.";
const string CONST_HARASS_CONSERVATIVE_WEBSITES_COMPUTER_SKILL = "harass Conservative websites. Computer skill";
const string CONST_SEARCH_THE_INTERNET_FOR_PUBLIC_OPINION_POLLS = "search the internet for public opinion polls.";
const string CONST_SPRAY_POLITICAL_GRAFFITI_ART_AND_HEART_WILL = "spray political graffiti. Art and Heart will";
const string CONST_CREATE_PUBLIC_DISTURBANCES = "create public disturbances. ";
const string CONST_HELP_THE_ELDERLY_LOCAL_LIBRARY_ANYTHING = "help the elderly, local library, anything";
const string CONST_X_STALINIZED = "stalinized";
const string CONST_X_REAGANIFIED = "reaganified";
const string CONST_X_DEFEAT = "defeat";
const string CONST_X_VICTORY = "victory";
const string CONST_X_ABORT = "abort";
const string CONST_X_ANCHOR = "anchor";
const string CONST_X_GLAMSHOW = "glamshow";
const string CONST_X_NEWSCAST = "newscast";
const string CONST_X_LACOPS = "lacops";
const string CONST_X_NEWSPAPER = "newspaper";
const string CONST_X_RECRUITING_LOWERCASE = "recruiting";
const string CONST_X_TRIAL = "trial";
const string CONST_X_FOOTCHASE = "footchase";
const string CONST_X_CARCHASE = "carchase";
const string CONST_X_CONQUER = "conquer";
const string CONST_X_DEFENSE_LOWERCASE = "defense";
const string CONST_X_HEAVYCOMBAT = "heavycombat";
const string CONST_X_PASTORALE = "Pastorale";
const string CONST_X_ALARMED = "alarmed";
const string CONST_X_SITEMODE = "sitemode";
const string CONST_X_SHOPPING = "shopping";
const string CONST_X_ELECTIONS = "elections";
const string CONST_X_CARTHEFT = "cartheft";
const string CONST_X_FINANCES = "finances";
const string CONST_X_DISBANDED = "disbanded";
const string CONST_X_LIBERALAGENDA = "liberalagenda";
const string CONST_X_REVIEWMODE = "reviewmode";
const string CONST_X_STOPEVIL = "stopevil";
const string CONST_X_SLEEPERS_LOWERCASE = "sleepers";
const string CONST_X_ACTIVATE = "activate";
const string CONST_X_SIEGE = "siege";
const string CONST_X_MARS = "Mars";
const string CONST_X_BASEMODE = "basemode";
const string CONST_X_NEWGAME = "newgame";
const string CONST_X_TITLEMODE = "titlemode";
const string CONST_X_STALINIST = "Stalinist";
const string CONST_X_ELITE_LIBERAL = "Elite Liberal";
const string CONST_X_LIBERAL = "Liberal";
const string CONST_ACTIVITY_SLEEPER_SPY5 = "Moderate";
const string CONST_X_CONSERVATIVE = "Conservative";
const string CONST_X_ARCHCONSERVATIVE = "Arch-Conservative";
const string CONST_X_CHA = "CHA";
const string CONST_X_HLTH = "HLTH";
const string CONST_X_HRT = "HRT";
const string CONST_X_INT = "INT";
const string CONST_X_WIS = "WIS";
const string CONST_X_AGI = "AGI";
const string CONST_X_STR = "STR";
const string CONST_X_DODGE = "Dodge";
const string CONST_X_FIRST_AID = "First Aid";
const string CONST_X_SEDUCTION = "Seduction";
const string CONST_X_STREET_SENSE = "Street Sense";
const string CONST_X_TEACHING = "Teaching";
const string CONST_X_STEALTH = "Stealth";
const string CONST_X_BUSINESS = "Business";
const string CONST_X_SCIENCE = "Science";
const string CONST_X_RELIGION = "Religion";
const string CONST_X_ART = "Art";
const string CONST_X_MUSIC = "Music";
const string CONST_X_WRITING = "Writing";
const string CONST_X_DRIVING = "Driving";
const string CONST_X_TAILORING = "Tailoring";
const string CONST_X_LAW = "Law";
const string CONST_X_COMPUTERS = "Computers";
const string CONST_X_DISGUISE = "Disguise";
const string CONST_X_SECURITY = "Security";
const string CONST_X_PSYCHOLOGY = "Psychology";
const string CONST_X_PERSUASION = "Persuasion";
const string CONST_X_SMG = "SMG";
const string CONST_X_SHOTGUN = "Shotgun";
const string CONST_X_HEAVY_WEAPONS = "Heavy Weapons";
const string CONST_X_RIFLE = "Rifle";
const string CONST_X_PISTOL = "Pistol";
const string CONST_X_AXE = "Axe";
const string CONST_CLUB = "Club";
const string CONST_THROWING = "Throwing";
const string CONST_SWORD = "Sword";
const string CONST_KNIFE = "Knife";
const string CONST_MARTIAL_ARTS = "Martial Arts";
const string CONST_F_SLAM_THE_BRAKES = "F - Slam the brakes!";
const string CONST_D_SWERVE_AROUND_HIM = "D - Swerve around him!";
const string CONST_A_KID_RUNS_INTO_THE_STREET_FOR_HIS_BALL = "A kid runs into the street for his ball!";
const string CONST_F_SLOW_DOWN_AND_TURN = "F - Slow down and turn!";
const string CONST_D_RUN_THE_LIGHT_ANYWAY = "D - Run the light anyway!";
const string CONST_THERE_S_A_RED_LIGHT_WITH_CROSS_TRAFFIC_AHEAD = "There's a red light with cross traffic ahead!";
const string CONST_F_SLOW_DOWN = "F - Slow down!";
const string CONST_D_SPEED_AROUND_IT = "D - Speed around it!";
const string CONST_A_TRUCK_PULLS_OUT_IN_YOUR_PATH = "A truck pulls out in your path!";
const string CONST_F_PLAY_IT_SAFE_AND_PLOW_THROUGH_IT = "F - Play it safe and plow through it!";
const string CONST_D_SWERVE_TO_AVOID_HITTING_ANYONE = "D - Swerve to avoid hitting anyone!";
const string CONST_YOU_ARE_SPEEDING_TOWARD_A_FLIMSY_FRUIT_STAND = "You are speeding toward a flimsy fruit stand!";
const string CONST_WASHINGTON_DC = "Washington, DC";
const string CONST_MIAMI_FL = "Miami, FL";
const string CONST_ATLANTA_GA = "Atlanta, GA";
const string CONST_DETROIT_MI = "Detroit, MI";
const string CONST_CHICAGO_IL = "Chicago, IL";
const string CONST_LOS_ANGELES_CA = "Los Angeles, CA";
const string CONST_NEW_YORK_NY = "New York, NY";
const string CONST_SEATTLE_WA = "Seattle, WA";
const string CONST_WERE_MURDERED_TRYING_TO_ESCAPE_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "were murdered trying to escape from a police siege yesterday, according ";
const string CONST_WERE_SLAIN_TRYING_TO_ESCAPE_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "were slain trying to escape from a police siege yesterday, according ";
const string CONST_WERE_MURDERED_DURING_A_POLICE_RAID_YESTERDAY_ACCORDING = "were murdered during a police raid yesterday, according ";
const string CONST_WERE_SLAIN_DURING_A_POLICE_RAID_YESTERDAY_ACCORDING = "were slain during a police raid yesterday, according ";
const string CONST_VIOLENTLY_BROKE_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "violently broke a police siege yesterday, according ";
const string CONST_FOUGHT_OFF_A_POLICE_RAID_YESTERDAY_ACCORDING = "fought off a police raid yesterday, according ";
const string CONST_ESCAPED_FROM_POLICE_OFFICERS_DURING_A_RAID_YESTERDAY_ACCORDING = "escaped from police officers during a raid yesterday, according ";
const string CONST_ESCAPED_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING = "escaped from a police siege yesterday, according ";
const string CONST_THE_STALINIST_PARTY_CLAIMS_VICTORY = "The Stalinist Party claims victory!";
const string CONST_THE_PROGRESSIVE_ELITE_SOCIAL_LIBERAL_GREEN_PARTY_CLAIMS_VICTORY = "The Progressive Elite Social Liberal Green Party claims victory!";
const string CONST_THE_LIBERAL_PARTY_CLAIMS_VICTORY = "The Liberal Party claims victory!";
const string CONST_THE_NEXT_TWO_YEARS_PROMISE_TO_BE_MORE_OF_THE_SAME = "The next two years promise to be more of the same.";
const string CONST_THE_CONSERVATIVE_PARTY_CLAIMS_VICTORY = "The Conservative Party claims victory!";
const string CONST_THE_U_S_A_FLAG_EAGLE_CONSERVATIVE_TEA_PARTY_CLAIMS_VICTORY = "The $$ U.S.A. Flag Eagle $$ Conservative Tea Party claims victory!";
const string CONST_THOUGHT_POLITICAL_VIOLENCE_WAS_JUSTIFIED = "thought political violence was justified";
const string CONST_HAVE_A_NEGATIVE_OPINION_OF_CABLE_NEWS_PROGRAMS = "have a negative opinion of cable news programs";
const string CONST_DO_NOT_LIKE_AM_RADIO = "do not like AM radio";
const string CONST_WANTED_TO_END_PRISONER_ABUSE_AND_TORTURE = "wanted to end prisoner abuse and torture";
const string CONST_HELD_THE_CONSERVATIVE_CRIME_SQUAD_IN_CONTEMPT = "held the Conservative Crime Squad in contempt";
const string CONST_OF_THESE_HELD_THE_LIBERAL_CRIME_SQUAD_IN_HIGH_REGARD = "of these held the Liberal Crime Squad in high regard";
const string CONST_RESPECTED_THE_POWER_OF_THE_LIBERAL_CRIME_SQUAD = "respected the power of the Liberal Crime Squad";
const string CONST_OPPOSED_INCREASING_MILITARY_SPENDING = "opposed increasing military spending";
const string CONST_ARE_CONCERNED_ABOUT_GUN_VIOLENCE = "are concerned about gun violence";
const string CONST_FELT_MORE_WORK_WAS_NEEDED_FOR_RACIAL_EQUALITY = "felt more work was needed for racial equality";
const string CONST_FAVORED_DOING_MORE_FOR_GENDER_EQUALITY = "favored doing more for gender equality";
const string CONST_BELIEVED_THAT_CEO_SALARIES_ARE_TOO_GREAT = "believed that CEO salaries are too great";
const string CONST_WERE_DISGUSTED_BY_CORPORATE_MALFEASANCE = "were disgusted by corporate malfeasance";
const string CONST_THOUGHT_INDUSTRY_SHOULD_LOWER_POLLUTION = "thought industry should lower pollution";
const string CONST_WOULD_BOYCOTT_COMPANIES_THAT_USED_SWEATSHOPS = "would boycott companies that used sweatshops";
const string CONST_WERE_FOR_THE_APPOINTMENT_OF_LIBERAL_JUSTICES = "were for the appointment of Liberal justices";
const string CONST_ABHORRED_GENETICALLY_ALTERED_FOOD_PRODUCTS = "abhorred genetically altered food products";
const string CONST_BELIEVED_IN_UNFETTERED_FREE_SPEECH = "believed in unfettered free speech";
const string CONST_THOUGHT_THE_INTELLIGENCE_COMMUNITY_INVADES_PRIVACY = "thought the intelligence community invades privacy";
const string CONST_WANTED_STRONGER_MEASURES_TO_PREVENT_TORTURE = "wanted stronger measures to prevent torture";
const string CONST_WERE_CRITICAL_OF_THE_POLICE = "were critical of the police";
const string CONST_DEPLORED_ANIMAL_RESEARCH = "deplored animal research";
const string CONST_WERE_TERRIFIED_OF_NUCLEAR_POWER = "were terrified of nuclear power";
const string CONST_WERE_AGAINST_CUTTING_TAXES = "were against cutting taxes";
const string CONST_OPPOSED_THE_DEATH_PENALTY = "opposed the death penalty";
const string CONST_WERE_IN_FAVOR_OF_EQUAL_RIGHTS_FOR_HOMOSEXUALS = "were in favor of equal rights for homosexuals";
const string CONST_LEFT_LEG = "left leg";
const string CONST_RIGHT_LEG = "right leg";
const string CONST_LEFT_ARM = "left arm";
const string CONST_RIGHT_ARM = "right arm";
const string CONST_LEFT_REAR_LEG = "left rear leg";
const string CONST_RIGHT_REAR_LEG = "right rear leg";
const string CONST_LEFT_FRONT_LEG = "left front leg";
const string CONST_RIGHT_FRONT_LEG = "right front leg";
const string CONST_LEFT_TREAD = "left tread";
const string CONST_RIGHT_TREAD = "right tread";
const string CONST_LEFT_SIDE = "left side";
const string CONST_RIGHT_SIDE = "right side";
const string CONST_FRONT = "front";
const string CONST_TURRET = "turret";

// These are filenames, which the variable names should reflect
const string CONST_HELPTOPICS_TXT = "helpTopics.txt";
const string CONST_STATE_BIASES_TXT = "state_biases.txt";
const string CONST_ENDGAMELAWSTRINGS_TXT = "endgameLawStrings.txt";
const string CONST_TALKABOUTTHEISSUES_TXT = "talkAboutTheIssues.txt";
const string CONST_DISCUSSESISSUES_TXT = "discussesIssues.txt";
const string CONST_DISCUSSISSUES_TXT = "discussIssues.txt";
const string CONST_LIBERALIZELAW_TXT = "liberalizeLaw.txt";
const string CONST_CONSERVATISELAW_TXT = "conservatiseLaw.txt";
const string CONST_ISSUEEVENTSTRING_TXT = "issueEventString.txt";
const string CONST_ISSUETOOLIBERAL_TXT = "issueTooLiberal.txt";
const string CONST_YOUARESTUPIDTALKABOUTISSUES_TXT = "youAreStupidTalkAboutIssues.txt";
const string CONST_CONSERVATIVELEGALARGUMENT_TXT = "conservativeLegalArgument.txt";
const string CONST_CASEREJECTED_SECONDRATECLOTHES_TXT = "caseREJECTED_SECONDRATECLOTHES.txt";
const string CONST_CASEREJECTED_DAMAGEDCLOTHES_TXT = "caseREJECTED_DAMAGEDCLOTHES.txt";
const string CONST_CASEREJECTED_BLOODYCLOTHES_TXT = "caseREJECTED_BLOODYCLOTHES.txt";
const string CONST_CASEREJECTED_SMELLFUNNY_TXT = "caseREJECTED_SMELLFUNNY.txt";
const string CONST_CASEREJECTED_DRESSCODE_TXT = "caseREJECTED_DRESSCODE.txt";
const string CONST_CASEREJECTED_UNDERAGE_TXT = "caseREJECTED_UNDERAGE.txt";
const string CONST_REJECTEDBECAUSEGUESTLIST_TXT = "rejectedBecauseGuestList.txt";
const string CONST_REJECTEDBECAUSEWEAPONS_TXT = "rejectedBecauseWeapons.txt";
const string CONST_REJECTEDBECAUSESECONDRATECLOTHES_TXT = "rejectedBecauseSecondRateClothes.txt";
const string CONST_REJECTEDBECAUSEDAMAGEDCLOTHES_TXT = "rejectedBecauseDamagedClothes.txt";
const string CONST_REJECTEDBECAUSEBLOODYCLOTHES_TXT = "rejectedBecauseBloodyClothes.txt";
const string CONST_REJECTEDBECAUSEDRESSCODE_TXT = "rejectedBecauseDresscode.txt";
const string CONST_REJECTEDBECAUSEFEMALEISH_TXT = "rejectedBecauseFemaleish.txt";
const string CONST_REJECTEDBECAUSEFEMALE_TXT = "rejectedBecauseFemale.txt";
const string CONST_REJECTEDBECAUSEUNDERAGE_TXT = "rejectedBecauseUnderage.txt";
const string CONST_REJECTEDBECAUSENUDE_TXT = "rejectedBecauseNude.txt";
const string CONST_REJECTEDBYCCS_TXT = "rejectedByCCS.txt";

// Most of these are tags, and should only be defined a single time, rather than both here and elsewhere
const string CONST_SITE_OUTDOOR_BUNKER = "SITE_OUTDOOR_BUNKER";
const string CONST_SITE_OUTDOOR_PUBLICPARK = "SITE_OUTDOOR_PUBLICPARK";
const string CONST_SITE_BUSINESS_BARANDGRILL = "SITE_BUSINESS_BARANDGRILL";
const string CONST_SITE_BUSINESS_INTERNETCAFE = "SITE_BUSINESS_INTERNETCAFE";
const string CONST_SITE_BUSINESS_VEGANCOOP = "SITE_BUSINESS_VEGANCOOP";
const string CONST_SITE_BUSINESS_LATTESTAND = "SITE_BUSINESS_LATTESTAND";
const string CONST_SITE_BUSINESS_CIGARBAR = "SITE_BUSINESS_CIGARBAR";
const string CONST_SITE_BUSINESS_JUICEBAR = "SITE_BUSINESS_JUICEBAR";
const string CONST_SITE_BUSINESS_CRACKHOUSE = "SITE_BUSINESS_CRACKHOUSE";
const string CONST_SITE_MEDIA_CABLENEWS = "SITE_MEDIA_CABLENEWS";
const string CONST_SITE_MEDIA_AMRADIO = "SITE_MEDIA_AMRADIO";
const string CONST_SITE_CORPORATE_HOUSE = "SITE_CORPORATE_HOUSE";
const string CONST_SITE_CORPORATE_HEADQUARTERS = "SITE_CORPORATE_HEADQUARTERS";
const string CONST_SITE_INDUSTRY_WAREHOUSE = "SITE_INDUSTRY_WAREHOUSE";
const string CONST_SITE_INDUSTRY_NUCLEAR = "SITE_INDUSTRY_NUCLEAR";
const string CONST_SITE_INDUSTRY_POLLUTER = "SITE_INDUSTRY_POLLUTER";
const string CONST_SITE_INDUSTRY_SWEATSHOP = "SITE_INDUSTRY_SWEATSHOP";
const string CONST_SITE_GOVERNMENT_FIRESTATION = "SITE_GOVERNMENT_FIRESTATION";
const string CONST_SITE_GOVERNMENT_INTELLIGENCEHQ = "SITE_GOVERNMENT_INTELLIGENCEHQ";
const string CONST_SITE_GOVERNMENT_PRISON = "SITE_GOVERNMENT_PRISON";
const string CONST_SITE_GOVERNMENT_COURTHOUSE = "SITE_GOVERNMENT_COURTHOUSE";
const string CONST_SITE_GOVERNMENT_POLICESTATION = "SITE_GOVERNMENT_POLICESTATION";
const string CONST_SITE_LABORATORY_GENETIC = "SITE_LABORATORY_GENETIC";
const string CONST_SITE_LABORATORY_COSMETICS = "SITE_LABORATORY_COSMETICS";
const string CONST_SITE_RESIDENTIAL_BOMBSHELTER = "SITE_RESIDENTIAL_BOMBSHELTER";
const string CONST_SITE_RESIDENTIAL_APARTMENT_UPSCALE = "SITE_RESIDENTIAL_APARTMENT_UPSCALE";
const string CONST_SITE_RESIDENTIAL_APARTMENT = "SITE_RESIDENTIAL_APARTMENT";
const string CONST_SITE_RESIDENTIAL_TENEMENT = "SITE_RESIDENTIAL_TENEMENT";
const string CONST_SITE_RESIDENTIAL_SHELTER = "SITE_RESIDENTIAL_SHELTER";
const string CONST_CREATURE_POLITICIAN = "CREATURE_POLITICIAN";
const string CONST_CREATURE_SECRET_SERVICE = "CREATURE_SECRET_SERVICE";
const string CONST_CREATURE_BANK_MANAGER = "CREATURE_BANK_MANAGER";
const string CONST_CREATURE_BANK_TELLER = "CREATURE_BANK_TELLER";
const string CONST_CREATURE_MILITARYOFFICER = "CREATURE_MILITARYOFFICER";
const string CONST_CREATURE_SEAL = "CREATURE_SEAL";
const string CONST_CREATURE_MILITARYPOLICE = "CREATURE_MILITARYPOLICE";
const string CONST_CREATURE_LOCKSMITH = "CREATURE_LOCKSMITH";
const string CONST_CREATURE_PSYCHOLOGIST = "CREATURE_PSYCHOLOGIST";
const string CONST_CREATURE_CCS_SNIPER = "CREATURE_CCS_SNIPER";
const string CONST_CREATURE_CCS_MOLOTOV = "CREATURE_CCS_MOLOTOV";
const string CONST_CREATURE_POLITICALACTIVIST = "CREATURE_POLITICALACTIVIST";
const string CONST_CREATURE_CCS_ARCHCONSERVATIVE = "CREATURE_CCS_ARCHCONSERVATIVE";
const string CONST_CREATURE_CCS_VIGILANTE = "CREATURE_CCS_VIGILANTE";
const string CONST_CREATURE_NURSE = "CREATURE_NURSE";
const string CONST_CREATURE_DOCTOR = "CREATURE_DOCTOR";
const string CONST_CREATURE_MUTANT = "CREATURE_MUTANT";
const string CONST_CREATURE_NUN = "CREATURE_NUN";
const string CONST_CREATURE_TAXIDRIVER = "CREATURE_TAXIDRIVER";
const string CONST_CREATURE_TRUCKER = "CREATURE_TRUCKER";
const string CONST_CREATURE_BIKER = "CREATURE_BIKER";
const string CONST_CREATURE_ATHLETE = "CREATURE_ATHLETE";
const string CONST_CREATURE_MARTIALARTIST = "CREATURE_MARTIALARTIST";
const string CONST_CREATURE_YOGAINSTRUCTOR = "CREATURE_YOGAINSTRUCTOR";
const string CONST_CREATURE_ACTOR = "CREATURE_ACTOR";
const string CONST_CREATURE_THIEF = "CREATURE_THIEF";
const string CONST_CREATURE_CLERK = "CREATURE_CLERK";
const string CONST_CREATURE_FASHIONDESIGNER = "CREATURE_FASHIONDESIGNER";
const string CONST_CREATURE_HAIRSTYLIST = "CREATURE_HAIRSTYLIST";
const string CONST_CREATURE_CAMERAMAN = "CREATURE_CAMERAMAN";
const string CONST_CREATURE_PHOTOGRAPHER = "CREATURE_PHOTOGRAPHER";
const string CONST_CREATURE_DANCER = "CREATURE_DANCER";
const string CONST_CREATURE_JOURNALIST = "CREATURE_JOURNALIST";
const string CONST_CREATURE_AUTHOR = "CREATURE_AUTHOR";
const string CONST_CREATURE_SCULPTOR = "CREATURE_SCULPTOR";
const string CONST_CREATURE_PAINTER = "CREATURE_PAINTER";
const string CONST_CREATURE_RETIREE = "CREATURE_RETIREE";
const string CONST_CREATURE_PROGRAMMER = "CREATURE_PROGRAMMER";
const string CONST_CREATURE_SOCIALITE = "CREATURE_SOCIALITE";
const string CONST_CREATURE_CRITIC_MUSIC = "CREATURE_CRITIC_MUSIC";
const string CONST_CREATURE_CRITIC_ART = "CREATURE_CRITIC_ART";
const string CONST_CREATURE_HIPPIE = "CREATURE_HIPPIE";
const string CONST_CREATURE_PRISONGUARD = "CREATURE_PRISONGUARD";
const string CONST_CREATURE_HARDENED_VETERAN = "CREATURE_HARDENED_VETERAN";
const string CONST_CREATURE_VETERAN = "CREATURE_VETERAN";
const string CONST_CREATURE_SOLDIER = "CREATURE_SOLDIER";
const string CONST_CREATURE_HICK = "CREATURE_HICK";
const string CONST_CREATURE_MERC = "CREATURE_MERC";
const string CONST_CREATURE_TANK = "CREATURE_TANK";
const string CONST_CREATURE_AMATEURMAGICIAN = "CREATURE_AMATEURMAGICIAN";
const string CONST_CREATURE_CONSTRUCTIONWORKER = "CREATURE_CONSTRUCTIONWORKER";
const string CONST_CREATURE_CHEF = "CREATURE_CHEF";
const string CONST_CREATURE_PLUMBER = "CREATURE_PLUMBER";
const string CONST_CREATURE_GARBAGEMAN = "CREATURE_GARBAGEMAN";
const string CONST_CREATURE_MAILMAN = "CREATURE_MAILMAN";
const string CONST_CREATURE_PROSTITUTE = "CREATURE_PROSTITUTE";
const string CONST_CREATURE_FOOTBALLCOACH = "CREATURE_FOOTBALLCOACH";
const string CONST_CREATURE_OFFICEWORKER = "CREATURE_OFFICEWORKER";
const string CONST_CREATURE_CARSALESMAN = "CREATURE_CARSALESMAN";
const string CONST_CREATURE_TELEMARKETER = "CREATURE_TELEMARKETER";
const string CONST_CREATURE_BARTENDER = "CREATURE_BARTENDER";
const string CONST_CREATURE_BARISTA = "CREATURE_BARISTA";
const string CONST_CREATURE_BAKER = "CREATURE_BAKER";
const string CONST_CREATURE_FASTFOODWORKER = "CREATURE_FASTFOODWORKER";
const string CONST_CREATURE_ENGINEER = "CREATURE_ENGINEER";
const string CONST_CREATURE_PRIEST = "CREATURE_PRIEST";
const string CONST_CREATURE_CRACKHEAD = "CREATURE_CRACKHEAD";
const string CONST_CREATURE_GANGMEMBER = "CREATURE_GANGMEMBER";
const string CONST_CREATURE_BUM = "CREATURE_BUM";
const string CONST_CREATURE_HSDROPOUT = "CREATURE_HSDROPOUT";
const string CONST_CREATURE_TEACHER = "CREATURE_TEACHER";
const string CONST_CREATURE_MATHEMATICIAN = "CREATURE_MATHEMATICIAN";
const string CONST_CREATURE_MUSICIAN = "CREATURE_MUSICIAN";
const string CONST_CREATURE_COLLEGESTUDENT = "CREATURE_COLLEGESTUDENT";
const string CONST_CREATURE_SEWERWORKER = "CREATURE_SEWERWORKER";
const string CONST_CREATURE_LAWYER = "CREATURE_LAWYER";
const string CONST_CREATURE_JUROR = "CREATURE_JUROR";
const string CONST_CREATURE_PRISONER = "CREATURE_PRISONER";
const string CONST_CREATURE_GUARDDOG = "CREATURE_GUARDDOG";
const string CONST_CREATURE_GENETIC = "CREATURE_GENETIC";
const string CONST_CREATURE_NEWSANCHOR = "CREATURE_NEWSANCHOR";
const string CONST_CREATURE_RADIOPERSONALITY = "CREATURE_RADIOPERSONALITY";
const string CONST_CREATURE_AGENT = "CREATURE_AGENT";
const string CONST_CREATURE_JUDGE_CONSERVATIVE = "CREATURE_JUDGE_CONSERVATIVE";
const string CONST_CREATURE_JUDGE_LIBERAL = "CREATURE_JUDGE_LIBERAL";
const string CONST_CREATURE_GANGUNIT = "CREATURE_GANGUNIT";
const string CONST_CREATURE_EDUCATOR = "CREATURE_EDUCATOR";
const string CONST_CREATURE_FIREFIGHTER = "CREATURE_FIREFIGHTER";
const string CONST_CREATURE_DEATHSQUAD = "CREATURE_DEATHSQUAD";
const string CONST_CREATURE_SWAT = "CREATURE_SWAT";
const string CONST_CREATURE_COP = "CREATURE_COP";
const string CONST_CREATURE_TEENAGER = "CREATURE_TEENAGER";
const string CONST_CREATURE_LANDLORD = "CREATURE_LANDLORD";
const string CONST_CREATURE_WORKER_FACTORY_UNION = "CREATURE_WORKER_FACTORY_UNION";
const string CONST_CREATURE_WORKER_SECRETARY = "CREATURE_WORKER_SECRETARY";
const string CONST_CREATURE_WORKER_FACTORY_CHILD = "CREATURE_WORKER_FACTORY_CHILD";
const string CONST_CREATURE_WORKER_FACTORY_NONUNION = "CREATURE_WORKER_FACTORY_NONUNION";
const string CONST_CREATURE_WORKER_SWEATSHOP = "CREATURE_WORKER_SWEATSHOP";
const string CONST_CREATURE_WORKER_JANITOR = "CREATURE_WORKER_JANITOR";
const string CONST_CREATURE_WORKER_SERVANT = "CREATURE_WORKER_SERVANT";
const string CONST_CREATURE_CORPORATE_CEO = "CREATURE_CORPORATE_CEO";
const string CONST_CREATURE_CORPORATE_MANAGER = "CREATURE_CORPORATE_MANAGER";
const string CONST_CREATURE_SCIENTIST_EMINENT = "CREATURE_SCIENTIST_EMINENT";
const string CONST_CREATURE_SCIENTIST_LABTECH = "CREATURE_SCIENTIST_LABTECH";
const string CONST_CREATURE_SECURITYGUARD = "CREATURE_SECURITYGUARD";
const string CONST_CREATURE_BOUNCER = "CREATURE_BOUNCER";
const string CONST_ATTRIBUTE_CHARISMA = "ATTRIBUTE_CHARISMA";
const string CONST_ATTRIBUTE_HEALTH = "ATTRIBUTE_HEALTH";
const string CONST_ATTRIBUTE_STRENGTH = "ATTRIBUTE_STRENGTH";
const string CONST_ATTRIBUTE_AGILITY = "ATTRIBUTE_AGILITY";
const string CONST_ATTRIBUTE_INTELLIGENCE = "ATTRIBUTE_INTELLIGENCE";
const string CONST_ATTRIBUTE_WISDOM = "ATTRIBUTE_WISDOM";
const string CONST_ATTRIBUTE_HEART = "ATTRIBUTE_HEART";
const string CONST_SKILL_WRITING = "SKILL_WRITING";
const string CONST_SKILL_THROWING = "SKILL_THROWING";
const string CONST_SKILL_TEACHING = "SKILL_TEACHING";
const string CONST_SKILL_TAILORING = "SKILL_TAILORING";
const string CONST_SKILL_SWORD = "SKILL_SWORD";
const string CONST_SKILL_STREETSENSE = "SKILL_STREETSENSE";
const string CONST_SKILL_STEALTH = "SKILL_STEALTH";
const string CONST_SKILL_SMG = "SKILL_SMG";
const string CONST_SKILL_SHOTGUN = "SKILL_SHOTGUN";
const string CONST_SKILL_SEDUCTION = "SKILL_SEDUCTION";
const string CONST_SKILL_SECURITY = "SKILL_SECURITY";
const string CONST_SKILL_SCIENCE = "SKILL_SCIENCE";
const string CONST_SKILL_RIFLE = "SKILL_RIFLE";
const string CONST_SKILL_RELIGION = "SKILL_RELIGION";
const string CONST_SKILL_PSYCHOLOGY = "SKILL_PSYCHOLOGY";
const string CONST_SKILL_PISTOL = "SKILL_PISTOL";
const string CONST_SKILL_PERSUASION = "SKILL_PERSUASION";
const string CONST_SKILL_MUSIC = "SKILL_MUSIC";
const string CONST_SKILL_HANDTOHAND = "SKILL_HANDTOHAND";
const string CONST_SKILL_LAW = "SKILL_LAW";
const string CONST_SKILL_KNIFE = "SKILL_KNIFE";
const string CONST_SKILL_HEAVYWEAPONS = "SKILL_HEAVYWEAPONS";
const string CONST_SKILL_FIRSTAID = "SKILL_FIRSTAID";
const string CONST_SKILL_DRIVING = "SKILL_DRIVING";
const string CONST_SKILL_DODGE = "SKILL_DODGE";
const string CONST_SKILL_DISGUISE = "SKILL_DISGUISE";
const string CONST_SKILL_COMPUTERS = "SKILL_COMPUTERS";
const string CONST_SKILL_CLUB = "SKILL_CLUB";
const string CONST_SKILL_BUSINESS = "SKILL_BUSINESS";
const string CONST_SKILL_AXE = "SKILL_AXE";
const string CONST_SKILL_ART = "SKILL_ART";
const string CONST_TRINKET = "TRINKET";
const string CONST_SILVERWARE = "SILVERWARE";
const string CONST_WATCH = "WATCH";
const string CONST_MICROPHONE = "MICROPHONE";
const string CONST_CELLPHONE = "CELLPHONE";
const string CONST_FINEJEWELERY = "FINEJEWELERY";
const string CONST_POLICERECORDS = "POLICERECORDS";
const string CONST_AMRADIOFILES = "AMRADIOFILES";
const string CONST_CABLENEWSFILES = "CABLENEWSFILES";
const string CONST_PRISONFILES = "PRISONFILES";
const string CONST_RESEARCHFILES = "RESEARCHFILES";
const string CONST_JUDGEFILES = "JUDGEFILES";
const string CONST_CORPFILES = "CORPFILES";
const string CONST_INTHQDISK = "INTHQDISK";
const string CONST_CEOPHOTOS = "CEOPHOTOS";
const string CONST_SECRETDOCUMENTS = "SECRETDOCUMENTS";
const string CONST_CHEAPJEWELERY = "CHEAPJEWELERY";
const string CONST_LAPTOP = "LAPTOP";
const string CONST_LABEQUIPMENT = "LABEQUIPMENT";
const string CONST_PDA = "PDA";
const string CONST_CHEMICAL = "CHEMICAL";
const string CONST_FINECLOTH = "FINECLOTH";
const string CONST_CLUB_BOUNCER_SECONDVISIT = "CLUB_BOUNCER_SECONDVISIT";
const string CONST_CLUB_BOUNCER = "CLUB_BOUNCER";
const string CONST_STAIRS_DOWN = "STAIRS_DOWN";
const string CONST_STAIRS_UP = "STAIRS_UP";
const string CONST_PARK_BENCH = "PARK_BENCH";
const string CONST_CAFE_COMPUTER = "CAFE_COMPUTER";
const string CONST_RESTAURANT_TABLE = "RESTAURANT_TABLE";
const string CONST_APARTMENT_SIGN = "APARTMENT_SIGN";
const string CONST_APARTMENT_LANDLORD = "APARTMENT_LANDLORD";
const string CONST_NEWS_BROADCASTSTUDIO = "NEWS_BROADCASTSTUDIO";
const string CONST_RADIO_BROADCASTSTUDIO = "RADIO_BROADCASTSTUDIO";
const string CONST_CORPORATE_FILES = "CORPORATE_FILES";
const string CONST_HOUSE_CEO = "HOUSE_CEO";
const string CONST_ARMYBASE_ARMORY = "ARMYBASE_ARMORY";
const string CONST_HOUSE_PHOTOS = "HOUSE_PHOTOS";
const string CONST_NUCLEAR_ONOFF = "NUCLEAR_ONOFF";
const string CONST_POLLUTER_EQUIPMENT = "POLLUTER_EQUIPMENT";
const string CONST_SWEATSHOP_EQUIPMENT = "SWEATSHOP_EQUIPMENT";
const string CONST_INTEL_SUPERCOMPUTER = "INTEL_SUPERCOMPUTER";
const string CONST_PRISON_CONTROL_HIGH = "PRISON_CONTROL_HIGH";
const string CONST_PRISON_CONTROL_MEDIUM = "PRISON_CONTROL_MEDIUM";
const string CONST_PRISON_CONTROL_LOW = "PRISON_CONTROL_LOW";
const string CONST_PRISON_CONTROL = "PRISON_CONTROL";
const string CONST_COURTHOUSE_JURYROOM = "COURTHOUSE_JURYROOM";
const string CONST_COURTHOUSE_LOCKUP = "COURTHOUSE_LOCKUP";
const string CONST_POLICESTATION_LOCKUP = "POLICESTATION_LOCKUP";
const string CONST_LAB_GENETIC_CAGEDANIMALS = "LAB_GENETIC_CAGEDANIMALS";
const string CONST_LAB_COSMETICS_CAGEDANIMALS = "LAB_COSMETICS_CAGEDANIMALS";
const string CONST_OUTDOOR_PUBLICPARK = "OUTDOOR_PUBLICPARK";
const string CONST_GENERIC_ONEROOM = "GENERIC_ONEROOM";
const string CONST_OUTDOOR_LATTESTAND = "OUTDOOR_LATTESTAND";
const string CONST_BUSINESS_RESTRICTEDCAFE = "BUSINESS_RESTRICTEDCAFE";
const string CONST_BUSINESS_INTERNETCAFE = "BUSINESS_INTERNETCAFE";
const string CONST_BUSINESS_CAFE = "BUSINESS_CAFE";
const string CONST_MEDIA_CABLENEWS = "MEDIA_CABLENEWS";
const string CONST_MEDIA_AMRADIO = "MEDIA_AMRADIO";
const string CONST_CORPORATE_HOUSE = "CORPORATE_HOUSE";
const string CONST_CORPORATE_HEADQUARTERS = "CORPORATE_HEADQUARTERS";
const string CONST_INDUSTRY_NUCLEAR = "INDUSTRY_NUCLEAR";
const string CONST_INDUSTRY_POLLUTER = "INDUSTRY_POLLUTER";
const string CONST_INDUSTRY_SWEATSHOP = "INDUSTRY_SWEATSHOP";
const string CONST_GOVERNMENT_ARMYBASE = "GOVERNMENT_ARMYBASE";
const string CONST_GOVERNMENT_WHITE_HOUSE = "GOVERNMENT_WHITE_HOUSE";
const string CONST_GOVERNMENT_INTELLIGENCEHQ = "GOVERNMENT_INTELLIGENCEHQ";
const string CONST_GOVERNMENT_PRISON = "GOVERNMENT_PRISON";
const string CONST_GOVERNMENT_COURTHOUSE = "GOVERNMENT_COURTHOUSE";
const string CONST_GOVERNMENT_POLICESTATION = "GOVERNMENT_POLICESTATION";
const string CONST_LABORATORY_GENETICS = "LABORATORY_GENETICS";
const string CONST_LABORATORY_COSMETICS = "LABORATORY_COSMETICS";
const string CONST_GENERIC_LOBBY = "GENERIC_LOBBY";
const string CONST_GENERIC_UNSECURE = "GENERIC_UNSECURE";
const string CONST_RESIDENTIAL_APARTMENT = "RESIDENTIAL_APARTMENT";
const string CONST_VIEWNUM = "VIEWNUM";
const string CONST_VIEW_CONSERVATIVECRIMESQUAD = "VIEW_CONSERVATIVECRIMESQUAD";
const string CONST_VIEW_LIBERALCRIMESQUADPOS = "VIEW_LIBERALCRIMESQUADPOS";
const string CONST_VIEW_LIBERALCRIMESQUAD = "VIEW_LIBERALCRIMESQUAD";
const string CONST_VIEW_CABLENEWS = "VIEW_CABLENEWS";
const string CONST_VIEW_AMRADIO = "VIEW_AMRADIO";
const string CONST_VIEW_PRISONS = "VIEW_PRISONS";
const string CONST_VIEW_MILITARY = "VIEW_MILITARY";
const string CONST_VIEW_IMMIGRATION = "VIEW_IMMIGRATION";
const string CONST_VIEW_DRUGS = "VIEW_DRUGS";
const string CONST_VIEW_CIVILRIGHTS = "VIEW_CIVILRIGHTS";
const string CONST_VIEW_WOMEN = "VIEW_WOMEN";
const string CONST_VIEW_CEOSALARY = "VIEW_CEOSALARY";
const string CONST_VIEW_CORPORATECULTURE = "VIEW_CORPORATECULTURE";
const string CONST_VIEW_POLLUTION = "VIEW_POLLUTION";
const string CONST_VIEW_SWEATSHOPS = "VIEW_SWEATSHOPS";
const string CONST_VIEW_GUNCONTROL = "VIEW_GUNCONTROL";
const string CONST_VIEW_JUSTICES = "VIEW_JUSTICES";
const string CONST_VIEW_GENETICS = "VIEW_GENETICS";
const string CONST_VIEW_FREESPEECH = "VIEW_FREESPEECH";
const string CONST_VIEW_INTELLIGENCE = "VIEW_INTELLIGENCE";
const string CONST_VIEW_TORTURE = "VIEW_TORTURE";
const string CONST_VIEW_POLICEBEHAVIOR = "VIEW_POLICEBEHAVIOR";
const string CONST_VIEW_ANIMALRESEARCH = "VIEW_ANIMALRESEARCH";
const string CONST_VIEW_NUCLEARPOWER = "VIEW_NUCLEARPOWER";
const string CONST_VIEW_TAXES = "VIEW_TAXES";
const string CONST_VIEW_DEATHPENALTY = "VIEW_DEATHPENALTY";
const string CONST_VIEW_GAY = "VIEW_GAY";
const string CONST_VIEW_MOOD = "VIEW_MOOD";
const string CONST_VIEW_STALIN = "VIEW_STALIN";
const string CONST_LAWNUM = "LAWNUM";
const string CONST_LAW_TORTURE = "LAW_TORTURE";
const string CONST_LAW_PRISONS = "LAW_PRISONS";
const string CONST_LAW_MILITARY = "LAW_MILITARY";
const string CONST_LAW_ELECTIONS = "LAW_ELECTIONS";
const string CONST_LAW_IMMIGRATION = "LAW_IMMIGRATION";
const string CONST_LAW_DRUGS = "LAW_DRUGS";
const string CONST_LAW_CIVILRIGHTS = "LAW_CIVILRIGHTS";
const string CONST_LAW_WOMEN = "LAW_WOMEN";
const string CONST_LAW_TAX = "LAW_TAX";
const string CONST_LAW_GUNCONTROL = "LAW_GUNCONTROL";
const string CONST_LAW_FLAGBURNING = "LAW_FLAGBURNING";
const string CONST_LAW_FREESPEECH = "LAW_FREESPEECH";
const string CONST_LAW_CORPORATE = "LAW_CORPORATE";
const string CONST_LAW_GAY = "LAW_GAY";
const string CONST_LAW_LABOR = "LAW_LABOR";
const string CONST_LAW_POLLUTION = "LAW_POLLUTION";
const string CONST_LAW_NUCLEARPOWER = "LAW_NUCLEARPOWER";
const string CONST_LAW_DEATHPENALTY = "LAW_DEATHPENALTY";
const string CONST_LAW_PRIVACY = "LAW_PRIVACY";
const string CONST_LAW_POLICEBEHAVIOR = "LAW_POLICEBEHAVIOR";
const string CONST_LAW_ANIMALRESEARCH = "LAW_ANIMALRESEARCH";
const string CONST_LAW_ABORTION = "LAW_ABORTION";
const string CONST_LAW_MOOD = "LAW_MOOD";
const string CONST_LAW_STALIN = "LAW_STALIN";
const string CONST_THEGREATUNKNOWN = "theGreatUnknown";
const string CONST_ACTIVITYNUM = "ACTIVITYNUM";
const string CONST_ACTIVITY_AUGMENT = "ACTIVITY_AUGMENT";
const string CONST_X_OPEN = "OPEN";
const string CONST_X_FIRE_END = "FIRE_END";
const string CONST_X_FIRE_PEAK = "FIRE_PEAK";
const string CONST_X_FIRE_START = "FIRE_START";
const string CONST_ACTIVITY_RECRUITING = "ACTIVITY_RECRUITING";
const string CONST_X_GRAFFITI_OTHER = "GRAFFITI_OTHER";
const string CONST_X_GRAFFITI_CCS = "GRAFFITI_CCS";
const string CONST_X_GRAFFITI_ALLCAPS = "GRAFFITI";
const string CONST_X_DEBRIS = "DEBRIS";
const string CONST_X_OUTDOOR = "OUTDOOR";
const string CONST_X_GRASSY = "GRASSY";
const string CONST_BLOODY_2 = "BLOODY2";
const string CONST_X_BLOODY = "BLOODY";
const string CONST_X_RESTRICTED = "RESTRICTED";
const string CONST_X_CLOCK = "CLOCK";
const string CONST_ACTIVITY_SLEEPER_JOINLCS = "ACTIVITY_SLEEPER_JOINLCS";
const string CONST_X_KLOCK = "KLOCK";
const string CONST_X_LOCKED = "LOCKED";
const string CONST_X_KNOWN = "KNOWN";
const string CONST_X_DOOR = "DOOR";
const string CONST_X_BLOCK = "BLOCK";
const string CONST_X_EXIT = "EXIT";
const string CONST_ACTIVITY_STUDY_RELIGION = "ACTIVITY_STUDY_RELIGION";
const string CONST_ACTIVITY_STUDY_CLUB = "ACTIVITY_STUDY_CLUB";
const string CONST_ACTIVITY_STUDY_STREETSENSE = "ACTIVITY_STUDY_STREETSENSE";
const string CONST_ACTIVITY_STUDY_THROWING = "ACTIVITY_STUDY_THROWING";
const string CONST_ACTIVITY_STUDY_STEALTH = "ACTIVITY_STUDY_STEALTH";
const string CONST_ACTIVITY_STUDY_SEDUCTION = "ACTIVITY_STUDY_SEDUCTION";
const string CONST_ACTIVITY_CLINIC = "ACTIVITY_CLINIC";
const string CONST_ACTIVITY_HEAL = "ACTIVITY_HEAL";
const string CONST_ACTIVITY_SLEEPER_LIBERAL = "ACTIVITY_SLEEPER_LIBERAL";
const string CONST_ACTIVITY_SLEEPER_CONSERVATIVE = "ACTIVITY_SLEEPER_CONSERVATIVE";
const string CONST_ACTIVITY_SLEEPER_SPY = "ACTIVITY_SLEEPER_SPY";
const string CONST_ACTIVITY_SLEEPER_RECRUIT = "ACTIVITY_SLEEPER_RECRUIT";
const string CONST_ACTIVITY_SLEEPER_EMBEZZLE = "ACTIVITY_SLEEPER_EMBEZZLE";
const string CONST_ACTIVITY_SLEEPER_STEAL = "ACTIVITY_SLEEPER_STEAL";
const string CONST_ACTIVITY_SLEEPER_SCANDAL = "ACTIVITY_SLEEPER_SCANDAL";
const string CONST_SPECIALWOUND_LOWERSPINE = "SPECIALWOUND_LOWERSPINE";
const string CONST_ACTIVITY_STUDY_WEAVING = "ACTIVITY_STUDY_WEAVING";
const string CONST_SPECIALWOUND_UPPERSPINE = "SPECIALWOUND_UPPERSPINE";
const string CONST_SPECIALWOUND_NECK = "SPECIALWOUND_NECK";
const string CONST_SPECIALWOUND_RIBS = "SPECIALWOUND_RIBS";
const string CONST_SPECIALWOUND_SPLEEN = "SPECIALWOUND_SPLEEN";
const string CONST_SPECIALWOUND_LEFTKIDNEY = "SPECIALWOUND_LEFTKIDNEY";
const string CONST_SPECIALWOUND_RIGHTKIDNEY = "SPECIALWOUND_RIGHTKIDNEY";
const string CONST_SPECIALWOUND_STOMACH = "SPECIALWOUND_STOMACH";
const string CONST_SPECIALWOUND_LIVER = "SPECIALWOUND_LIVER";
const string CONST_SPECIALWOUND_HEART = "SPECIALWOUND_HEART";
const string CONST_SPECIALWOUND_LEFTLUNG = "SPECIALWOUND_LEFTLUNG";
const string CONST_ACTIVITY_STUDY_FENCING = "ACTIVITY_STUDY_FENCING";
const string CONST_SPECIALWOUND_RIGHTLUNG = "SPECIALWOUND_RIGHTLUNG";
const string CONST_SPECIALWOUND_TONGUE = "SPECIALWOUND_TONGUE";
const string CONST_SPECIALWOUND_NOSE = "SPECIALWOUND_NOSE";
const string CONST_SPECIALWOUND_LEFTEYE = "SPECIALWOUND_LEFTEYE";
const string CONST_SPECIALWOUND_RIGHTEYE = "SPECIALWOUND_RIGHTEYE";
const string CONST_SPECIALWOUND_TEETH = "SPECIALWOUND_TEETH";
const string CONST_SITE_GOVERNMENT_WHITE_HOUSE = "SITE_GOVERNMENT_WHITE_HOUSE";
const string CONST_SITE_GOVERNMENT_LIBERAL_PARTY_HQ = "SITE_GOVERNMENT_LIBERAL_PARTY_HQ";
const string CONST_SITE_BUSINESS_BANK = "SITE_BUSINESS_BANK";
const string CONST_SITE_GOVERNMENT_ARMYBASE = "SITE_GOVERNMENT_ARMYBASE";
const string CONST_ACTIVITY_STUDY_COMPUTERS = "ACTIVITY_STUDY_COMPUTERS";
const string CONST_ACTIVITY_STUDY_LOCKSMITHING = "ACTIVITY_STUDY_LOCKSMITHING";
const string CONST_ACTIVITY_STUDY_WRITING = "ACTIVITY_STUDY_WRITING";
const string CONST_ACTIVITY_STUDY_TEACHING = "ACTIVITY_STUDY_TEACHING";
const string CONST_ACTIVITY_STUDY_ART = "ACTIVITY_STUDY_ART";
const string CONST_ACTIVITY_STUDY_MUSIC = "ACTIVITY_STUDY_MUSIC";
const string CONST_ACTIVITY_STUDY_GYMNASTICS = "ACTIVITY_STUDY_GYMNASTICS";
const string CONST_ACTIVITY_STUDY_BUSINESS = "ACTIVITY_STUDY_BUSINESS";
const string CONST_ACTIVITY_STUDY_SCIENCE = "ACTIVITY_STUDY_SCIENCE";
const string CONST_ACTIVITY_STUDY_DISGUISE = "ACTIVITY_STUDY_DISGUISE";
const string CONST_ACTIVITY_STUDY_LAW = "ACTIVITY_STUDY_LAW";
const string CONST_ACTIVITY_STUDY_FIRST_AID = "ACTIVITY_STUDY_FIRST_AID";
const string CONST_ACTIVITY_STUDY_PSYCHOLOGY = "ACTIVITY_STUDY_PSYCHOLOGY";
const string CONST_ACTIVITY_STUDY_DRIVING = "ACTIVITY_STUDY_DRIVING";
const string CONST_ACTIVITY_STUDY_MARTIAL_ARTS = "ACTIVITY_STUDY_MARTIAL_ARTS";
const string CONST_ACTIVITY_STUDY_DEBATING = "ACTIVITY_STUDY_DEBATING";
const string CONST_ACTIVITY_TEACH_COVERT = "ACTIVITY_TEACH_COVERT";
const string CONST_ACTIVITY_TEACH_FIGHTING = "ACTIVITY_TEACH_FIGHTING";
const string CONST_ACTIVITY_TEACH_POLITICS = "ACTIVITY_TEACH_POLITICS";
const string CONST_ACTIVITY_WRITE_GUARDIAN = "ACTIVITY_WRITE_GUARDIAN";
const string CONST_ACTIVITY_WRITE_LETTERS = "ACTIVITY_WRITE_LETTERS";
const string CONST_ACTIVITY_WRITE_BLOG = "ACTIVITY_WRITE_BLOG";
const string CONST_ACTIVITY_BURY = "ACTIVITY_BURY";
const string CONST_ACTIVITY_WHEELCHAIR = "ACTIVITY_WHEELCHAIR";
const string CONST_ACTIVITY_STEALCARS = "ACTIVITY_STEALCARS";
const string CONST_ACTIVITY_MAKE_ARMOR = "ACTIVITY_MAKE_ARMOR";
const string CONST_ACTIVITY_REPAIR_ARMOR = "ACTIVITY_REPAIR_ARMOR";
const string CONST_ACTIVITY_HACKING = "ACTIVITY_HACKING";
const string CONST_ACTIVITY_DOS_ATTACKS = "ACTIVITY_DOS_ATTACKS";
const string CONST_ACTIVITY_DOS_RACKET = "ACTIVITY_DOS_RACKET";
const string CONST_ACTIVITY_CCFRAUD = "ACTIVITY_CCFRAUD";
const string CONST_ACTIVITY_POLLS = "ACTIVITY_POLLS";
const string CONST_ACTIVITY_PROSTITUTION = "ACTIVITY_PROSTITUTION";
const string CONST_ACTIVITY_SELL_DRUGS = "ACTIVITY_SELL_DRUGS";
const string CONST_ACTIVITY_DONATIONS = "ACTIVITY_DONATIONS";
const string CONST_ACTIVITY_SELL_TSHIRTS = "ACTIVITY_SELL_TSHIRTS";
const string CONST_ACTIVITY_SELL_MUSIC = "ACTIVITY_SELL_MUSIC";
const string CONST_ACTIVITY_SELL_ART = "ACTIVITY_SELL_ART";
const string CONST_ACTIVITY_COMMUNITYSERVICE = "ACTIVITY_COMMUNITYSERVICE";
const string CONST_ACTIVITY_GRAFFITI = "ACTIVITY_GRAFFITI";
const string CONST_ACTIVITY_TROUBLE = "ACTIVITY_TROUBLE";
const string CONST_ACTIVITY_HOSTAGETENDING = "ACTIVITY_HOSTAGETENDING";
const string CONST_ACTIVITY_VISIT = "ACTIVITY_VISIT";
const string CONST_ACTIVITY_NONE = "ACTIVITY_NONE";
const string SINGLE_SPACE = " ";

const string tag_LOOT = "LOOT";
const string tag_dating = "dating";
const string tag_interrogation = "interrogation";
const string tag_suspicious = "suspicious";
const string tag_body = "body";
const string tag_head = "head";
const string tag_Travel = "Travel";
const string tag_City_Outskirts = "City Outskirts";
const string tag_Outskirts = "Outskirts";
const string tag_i_District = "I-District";
const string tag_Industrial_District = "Industrial District";
const string tag_Shopping = "Shopping";
const string tag_University_District = "University District";
const string tag_u_District = "U-District";
const string tag_D = "D";
const string tag_Downtown = "Downtown";
const string tag_DC = "DC";
const string tag_Miami = "Miami";
const string tag_MI = "MI";
const string tag_ATL = "ATL";
const string tag_Atlanta = "Atlanta";
const string tag_DET = "DET";
const string tag_Detroit = "Detroit";
const string tag_Chicago = "Chicago";
const string tag_CHI = "CHI";
const string tag_NYC = "NYC";
const string tag_LA = "LA";
const string tag_SEA = "SEA";
const string tag_Seattle = "Seattle";
const string tag_LOOT_TRINKET = "LOOT_TRINKET";
const string tag_LOOT_SILVERWARE = "LOOT_SILVERWARE";
const string tag_LOOT_WATCH = "LOOT_WATCH";
const string tag_LOOT_MICROPHONE = "LOOT_MICROPHONE";
const string tag_LOOT_CELLPHONE = "LOOT_CELLPHONE";
const string tag_LOOT_EXPENSIVEJEWELERY = "LOOT_EXPENSIVEJEWELERY";
const string tag_LOOT_POLICERECORDS = "LOOT_POLICERECORDS";
const string tag_LOOT_AMRADIOFILES = "LOOT_AMRADIOFILES";
const string tag_LOOT_CABLENEWSFILES = "LOOT_CABLENEWSFILES";
const string tag_LOOT_PRISONFILES = "LOOT_PRISONFILES";
const string tag_LOOT_RESEARCHFILES = "LOOT_RESEARCHFILES";
const string tag_LOOT_JUDGEFILES = "LOOT_JUDGEFILES";
const string tag_LOOT_CORPFILES = "LOOT_CORPFILES";
const string tag_LOOT_INTHQDISK = "LOOT_INTHQDISK";
const string tag_LOOT_CEOPHOTOS = "LOOT_CEOPHOTOS";
const string tag_LOOT_SECRETDOCUMENTS = "LOOT_SECRETDOCUMENTS";
const string tag_LOOT_CHEAPJEWELERY = "LOOT_CHEAPJEWELERY";
const string tag_LOOT_COMPUTER = "LOOT_COMPUTER";
const string tag_LOOT_LABEQUIPMENT = "LOOT_LABEQUIPMENT";
const string tag_LOOT_PDA = "LOOT_PDA";
const string tag_LOOT_CHEMICAL = "LOOT_CHEMICAL";
const string tag_LOOT_FINECLOTH = "LOOT_FINECLOTH";
const string tag_value = "value";
const string tag_attribute = "attribute";
const string tag_skill = "skill";


#include "../creature/creature.h"
#include "../locations/locations.h"
#include "../common/ledgerEnums.h"
#include "../customMaps.h"
#include "../set_color_support.h"
file_and_text_collection customText(vector<string>  *collection_, string fileName_) {
	file_and_text_collection newWound;
	newWound.collection = collection_;
	newWound.fileName = fileName_;
	newWound.superCollection = false;
	return newWound;
}
file_and_text_collection customText(string fileName_) {
	file_and_text_collection newWound;
	vector<string> vsr;
	vsr.push_back(SINGLE_SPACE);
	newWound.collection = &vsr;
	newWound.fileName = fileName_;
	newWound.superCollection = false;
	return newWound;
}
file_and_text_collection customText(vector<vector<string> >  *collection_, string fileName_, int dimensions_) {
	file_and_text_collection newWound;
	newWound.super_collection = collection_;
	newWound.fileName = fileName_;
	newWound.dimensions = dimensions_;
	newWound.superCollection = true;
	return newWound;
}
file_and_text_collection customText(string fileName_, int dimensions_) {
	file_and_text_collection newWound;
	newWound.fileName = fileName_;
	newWound.dimensions = dimensions_;
	newWound.superCollection = true;
	return newWound;
}
struct stringAndColor
{
	string str;
	ColorSetup type;
	stringAndColor(string str_, ColorSetup type_) : str(str_), type(type_) { }
	stringAndColor(ColorSetup type_, string str_) : str(str_), type(type_) { }
};
int getLawFromFlag(int type);

extern  map<Activity, Data_Activity> data_activities;
extern map< Activity, CreatureSkill> trainingActivity;
extern map< Views, stringConnectedToView > pollingData;
extern map<char, vector<ActivityAndString> > activate_menu_items;
extern map<int, vector<string> > caseRejectionReasons;
extern map<int, vector<string> > rejectionReasons;
extern map<short, map<short, string> > getLawFlagStringFull;
extern map<short, string> animalBodyParts;
extern map<short, string> attEnumToString;
extern map<short, string> buildThisSite;
extern map<short, string> cityNames;
extern map<short, string> conservatiseLaw;
extern map<short, string> conservativeLegalArgument;
extern map<short, string> discussesIssues;
extern map<short, string> discussIssues;
extern map<short, string> enumToCreature;
extern map<short, string> expenseTypes;
extern map<short, string> getActivityString;
extern map<short, string> getAlignString;
extern map<short, string> getCityDescription;
extern map<short, string> getLawFlagString;
extern map<short, string> getLawString;
extern map<short, string> humanBodyParts;
extern map<short, string> incomeTypes;
extern map<short, string> issueEventString;
extern map<short, string> issueTooLiberal;
extern map<short, string> liberalizeLaw;
extern map<short, string> musicList;
extern map<short, string> reviewStrings;
extern map<short, string> reviewStringsSecondLine;
extern map<short, string> siteReadMap;
extern map<short, string> skillEnumToString;
extern map<short, string> supportsLiberalLaw;
extern map<short, string> tankBodyParts;
extern map<short, string> trainingActivitySorting;
extern map<short, string> winnerOfElection;
extern map<short, string> youAreStupidTalkAboutIssues;
extern map<short, vector<string> > carchaseObstacles;
extern map<short, vector<string> > endgameLawStrings;
extern map<short, vector<string> > getSiteName;
extern map<short, vector<string> > getViewString;
extern map<short, vector<string> > helpTopics;
extern map<short, vector<string> > newsStories;
extern map<short, vector<string> > talkAboutTheIssues;
extern map<string, short> getAttributeEnumFromString;
extern map<string, short> getBaseEnumFromString;
extern map<string, short> getCreatureEnumFromString;
extern map<string, short> getSkillEnumFromString;
extern map<string, short> getSpecial;
extern map<string, short> getSpecialWoundEnumFromString;
extern map<string, short> getUnique;
extern map<string, short> site_tile_list;
extern map<string, string> getLootString;
extern vector<ActivityAndString> data_lessons;
extern vector<activityData> hackingActivities;
extern vector<CreatureTypes> ACTIVITY_TEACH_COVERT_DEFAULT;
extern vector<CreatureTypes> ACTIVITY_TEACH_FIGHTING_DEFAULT;
extern vector<CreatureTypes> ACTIVITY_TEACH_POLITICS_DEFAULT;
extern vector<int> state_biases;
extern vector<RecruitData> recruitable_creatures;
extern vector<string> theGreatUnknown;
extern vector<stringAndColor> liberalListAndColor;

vector<string> conservativeLegalArgumentUnprocessed;
vector<string> youAreStupidTalkAboutIssuesUnprocessed;
vector<string> issueTooLiberalUnprocessed;
vector<string> issueEventStringUnprocessed;
vector<string> conservatiseLawUnprocessed;
vector<string> liberalizeLawUnprocessed;
vector<string> discussIssuesUnprocessed;
vector<string> discussesIssuesUnprocessed;
vector<string> talkAboutTheIssuesUnprocessed;
vector<string> endgameLawStringsUnprocessed;
vector<string> helpTopicUnprocessed;
vector<string> state_biases_Unprocessed;
map<string, short> string_to_activity = {
	map<string, short>::value_type(CONST_ACTIVITY_NONE, ACTIVITY_NONE),
	map<string, short>::value_type(CONST_ACTIVITY_VISIT, ACTIVITY_VISIT),
	map<string, short>::value_type(CONST_ACTIVITY_HOSTAGETENDING, ACTIVITY_HOSTAGETENDING),
	map<string, short>::value_type(CONST_ACTIVITY_TROUBLE, ACTIVITY_TROUBLE),
	map<string, short>::value_type(CONST_ACTIVITY_GRAFFITI, ACTIVITY_GRAFFITI),
	map<string, short>::value_type(CONST_ACTIVITY_COMMUNITYSERVICE, ACTIVITY_COMMUNITYSERVICE),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_ART, ACTIVITY_SELL_ART),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_MUSIC, ACTIVITY_SELL_MUSIC),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_TSHIRTS, ACTIVITY_SELL_TSHIRTS),
	map<string, short>::value_type(CONST_ACTIVITY_DONATIONS, ACTIVITY_DONATIONS),
	map<string, short>::value_type(CONST_ACTIVITY_SELL_DRUGS, ACTIVITY_SELL_DRUGS),
	map<string, short>::value_type(CONST_ACTIVITY_PROSTITUTION, ACTIVITY_PROSTITUTION),
	map<string, short>::value_type(CONST_ACTIVITY_POLLS, ACTIVITY_POLLS),
	map<string, short>::value_type(CONST_ACTIVITY_CCFRAUD, ACTIVITY_CCFRAUD),
	map<string, short>::value_type(CONST_ACTIVITY_DOS_RACKET, ACTIVITY_DOS_RACKET),
	map<string, short>::value_type(CONST_ACTIVITY_DOS_ATTACKS, ACTIVITY_DOS_ATTACKS),
	map<string, short>::value_type(CONST_ACTIVITY_HACKING, ACTIVITY_HACKING),
	map<string, short>::value_type(CONST_ACTIVITY_REPAIR_ARMOR, ACTIVITY_REPAIR_ARMOR),
	map<string, short>::value_type(CONST_ACTIVITY_MAKE_ARMOR, ACTIVITY_MAKE_ARMOR),
	map<string, short>::value_type(CONST_ACTIVITY_STEALCARS, ACTIVITY_STEALCARS),
	map<string, short>::value_type(CONST_ACTIVITY_WHEELCHAIR, ACTIVITY_WHEELCHAIR),
	map<string, short>::value_type(CONST_ACTIVITY_BURY, ACTIVITY_BURY),
	map<string, short>::value_type(CONST_ACTIVITY_WRITE_BLOG, ACTIVITY_WRITE_BLOG),
	map<string, short>::value_type(CONST_ACTIVITY_WRITE_LETTERS, ACTIVITY_WRITE_LETTERS),
	map<string, short>::value_type(CONST_ACTIVITY_WRITE_GUARDIAN, ACTIVITY_WRITE_GUARDIAN),
	map<string, short>::value_type(CONST_ACTIVITY_TEACH_POLITICS, ACTIVITY_TEACH_POLITICS),
	map<string, short>::value_type(CONST_ACTIVITY_TEACH_FIGHTING, ACTIVITY_TEACH_FIGHTING),
	map<string, short>::value_type(CONST_ACTIVITY_TEACH_COVERT, ACTIVITY_TEACH_COVERT),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_DEBATING, ACTIVITY_STUDY_DEBATING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_MARTIAL_ARTS, ACTIVITY_STUDY_MARTIAL_ARTS),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_DRIVING, ACTIVITY_STUDY_DRIVING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_PSYCHOLOGY, ACTIVITY_STUDY_PSYCHOLOGY),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_FIRST_AID, ACTIVITY_STUDY_FIRST_AID),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_LAW, ACTIVITY_STUDY_LAW),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_DISGUISE, ACTIVITY_STUDY_DISGUISE),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_SCIENCE, ACTIVITY_STUDY_SCIENCE),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_BUSINESS, ACTIVITY_STUDY_BUSINESS),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_GYMNASTICS, ACTIVITY_STUDY_GYMNASTICS),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_MUSIC, ACTIVITY_STUDY_MUSIC),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_ART, ACTIVITY_STUDY_ART),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_TEACHING, ACTIVITY_STUDY_TEACHING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_WRITING, ACTIVITY_STUDY_WRITING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_LOCKSMITHING, ACTIVITY_STUDY_LOCKSMITHING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_COMPUTERS, ACTIVITY_STUDY_COMPUTERS),
	//ACTIVITY_STUDY_COOKING
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_FENCING, ACTIVITY_STUDY_FENCING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_WEAVING, ACTIVITY_STUDY_WEAVING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_RELIGION, ACTIVITY_STUDY_RELIGION),
	//ACTIVITY_STUDY_MAGIC
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_CLUB, ACTIVITY_STUDY_CLUB),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_STREETSENSE, ACTIVITY_STUDY_STREETSENSE),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_THROWING, ACTIVITY_STUDY_THROWING),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_STEALTH, ACTIVITY_STUDY_STEALTH),
	map<string, short>::value_type(CONST_ACTIVITY_STUDY_SEDUCTION, ACTIVITY_STUDY_SEDUCTION),
	map<string, short>::value_type(CONST_ACTIVITY_CLINIC, ACTIVITY_CLINIC),
	map<string, short>::value_type(CONST_ACTIVITY_HEAL, ACTIVITY_HEAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_LIBERAL, ACTIVITY_SLEEPER_LIBERAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_CONSERVATIVE, ACTIVITY_SLEEPER_CONSERVATIVE),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_SPY, ACTIVITY_SLEEPER_SPY),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_RECRUIT, ACTIVITY_SLEEPER_RECRUIT),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_SCANDAL, ACTIVITY_SLEEPER_SCANDAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_EMBEZZLE, ACTIVITY_SLEEPER_EMBEZZLE),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_STEAL, ACTIVITY_SLEEPER_STEAL),
	map<string, short>::value_type(CONST_ACTIVITY_SLEEPER_JOINLCS, ACTIVITY_SLEEPER_JOINLCS),
	map<string, short>::value_type(CONST_ACTIVITY_RECRUITING, ACTIVITY_RECRUITING),
	map<string, short>::value_type(CONST_ACTIVITY_AUGMENT, ACTIVITY_AUGMENT),
	map<string, short>::value_type(CONST_ACTIVITYNUM, ACTIVITYNUM),
	map<string, short>::value_type(CONST_THEGREATUNKNOWN, -1),
};
map<string, short> string_to_law = {
	map<string, short>::value_type(CONST_LAW_STALIN, LAW_STALIN),
	map<string, short>::value_type(CONST_LAW_MOOD, LAW_MOOD),
	map<string, short>::value_type(CONST_LAW_ABORTION, LAW_ABORTION),
	map<string, short>::value_type(CONST_LAW_ANIMALRESEARCH, LAW_ANIMALRESEARCH),
	map<string, short>::value_type(CONST_LAW_POLICEBEHAVIOR, LAW_POLICEBEHAVIOR),
	map<string, short>::value_type(CONST_LAW_PRIVACY, LAW_PRIVACY),
	map<string, short>::value_type(CONST_LAW_DEATHPENALTY, LAW_DEATHPENALTY),
	map<string, short>::value_type(CONST_LAW_NUCLEARPOWER, LAW_NUCLEARPOWER),
	map<string, short>::value_type(CONST_LAW_POLLUTION, LAW_POLLUTION),
	map<string, short>::value_type(CONST_LAW_LABOR, LAW_LABOR),
	map<string, short>::value_type(CONST_LAW_GAY, LAW_GAY),
	map<string, short>::value_type(CONST_LAW_CORPORATE, LAW_CORPORATE),
	map<string, short>::value_type(CONST_LAW_FREESPEECH, LAW_FREESPEECH),
	map<string, short>::value_type(CONST_LAW_FLAGBURNING, LAW_FLAGBURNING),
	map<string, short>::value_type(CONST_LAW_GUNCONTROL, LAW_GUNCONTROL),
	map<string, short>::value_type(CONST_LAW_TAX, LAW_TAX),
	map<string, short>::value_type(CONST_LAW_WOMEN, LAW_WOMEN),
	map<string, short>::value_type(CONST_LAW_CIVILRIGHTS, LAW_CIVILRIGHTS),
	map<string, short>::value_type(CONST_LAW_DRUGS, LAW_DRUGS),
	map<string, short>::value_type(CONST_LAW_IMMIGRATION, LAW_IMMIGRATION),
	map<string, short>::value_type(CONST_LAW_ELECTIONS, LAW_ELECTIONS),
	map<string, short>::value_type(CONST_LAW_MILITARY, LAW_MILITARY),
	map<string, short>::value_type(CONST_LAW_PRISONS, LAW_PRISONS),
	map<string, short>::value_type(CONST_LAW_TORTURE, LAW_TORTURE),
	map<string, short>::value_type(CONST_LAWNUM, LAWNUM),
};
map<string, short> string_to_view = {
	map<string, short>::value_type(CONST_VIEW_STALIN, VIEW_STALIN),
	map<string, short>::value_type(CONST_VIEW_MOOD, VIEW_MOOD),
	map<string, short>::value_type(CONST_VIEW_GAY, VIEW_GAY),
	map<string, short>::value_type(CONST_VIEW_DEATHPENALTY, VIEW_DEATHPENALTY),
	map<string, short>::value_type(CONST_VIEW_TAXES, VIEW_TAXES),
	map<string, short>::value_type(CONST_VIEW_NUCLEARPOWER, VIEW_NUCLEARPOWER),
	map<string, short>::value_type(CONST_VIEW_ANIMALRESEARCH, VIEW_ANIMALRESEARCH),
	map<string, short>::value_type(CONST_VIEW_POLICEBEHAVIOR, VIEW_POLICEBEHAVIOR),
	map<string, short>::value_type(CONST_VIEW_TORTURE, VIEW_TORTURE),
	map<string, short>::value_type(CONST_VIEW_INTELLIGENCE, VIEW_INTELLIGENCE),
	map<string, short>::value_type(CONST_VIEW_FREESPEECH, VIEW_FREESPEECH),
	map<string, short>::value_type(CONST_VIEW_GENETICS, VIEW_GENETICS),
	map<string, short>::value_type(CONST_VIEW_JUSTICES, VIEW_JUSTICES),
	map<string, short>::value_type(CONST_VIEW_GUNCONTROL, VIEW_GUNCONTROL),
	map<string, short>::value_type(CONST_VIEW_SWEATSHOPS, VIEW_SWEATSHOPS),
	map<string, short>::value_type(CONST_VIEW_POLLUTION, VIEW_POLLUTION),
	map<string, short>::value_type(CONST_VIEW_CORPORATECULTURE, VIEW_CORPORATECULTURE),
	map<string, short>::value_type(CONST_VIEW_CEOSALARY, VIEW_CEOSALARY),
	map<string, short>::value_type(CONST_VIEW_WOMEN, VIEW_WOMEN),
	map<string, short>::value_type(CONST_VIEW_CIVILRIGHTS, VIEW_CIVILRIGHTS),
	map<string, short>::value_type(CONST_VIEW_DRUGS, VIEW_DRUGS),
	map<string, short>::value_type(CONST_VIEW_IMMIGRATION, VIEW_IMMIGRATION),
	map<string, short>::value_type(CONST_VIEW_MILITARY, VIEW_MILITARY),
	map<string, short>::value_type(CONST_VIEW_PRISONS, VIEW_PRISONS),
	map<string, short>::value_type(CONST_VIEW_AMRADIO, VIEW_AMRADIO),
	map<string, short>::value_type(CONST_VIEW_CABLENEWS, VIEW_CABLENEWS),
	map<string, short>::value_type(CONST_VIEW_LIBERALCRIMESQUAD, VIEW_LIBERALCRIMESQUAD),
	map<string, short>::value_type(CONST_VIEW_LIBERALCRIMESQUADPOS, VIEW_LIBERALCRIMESQUADPOS),
	map<string, short>::value_type(CONST_VIEW_CONSERVATIVECRIMESQUAD, VIEW_CONSERVATIVECRIMESQUAD),
	map<string, short>::value_type(CONST_VIEWNUM, VIEWNUM),
};
// TODO these should have error detection, but that is kinda low priority
void processTheUnprocessed(vector<string> &unprocessed, map<short, string> &processed, map<string, short> string_to_short);
void processTheUnprocessed(vector<string> &unprocessed, map<short, vector<string> > &processed, map<string, short> string_to_short);

vector<string> rejectedByCCS;
vector<string> rejectedBecauseNude;
vector<string> rejectedBecauseUnderage;
vector<string> rejectedBecauseFemale;
vector<string> rejectedBecauseFemaleish;
vector<string> rejectedBecauseDresscode;
vector<string> rejectedBecauseBloodyClothes;
vector<string> rejectedBecauseDamagedClothes;
vector<string> rejectedBecauseSecondRateClothes;
vector<string> rejectedBecauseWeapons;
vector<string> rejectedBecauseGuestList;
// the vector<string> 'caseREJECTED' and 'rejected' are similar but not identicle.
// TODO the precise differences should be made more apparant
vector<string> caseREJECTED_UNDERAGE;
vector<string> caseREJECTED_DRESSCODE;
vector<string> caseREJECTED_SMELLFUNNY;
vector<string> caseREJECTED_BLOODYCLOTHES;
vector<string> caseREJECTED_DAMAGEDCLOTHES;
vector<string> caseREJECTED_SECONDRATECLOTHES;
vector<file_and_text_collection> externally_stored_data_text_file_collection = {
	customText(&rejectedByCCS, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBYCCS_TXT),
	customText(&rejectedBecauseNude, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSENUDE_TXT),
	customText(&rejectedBecauseUnderage, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEUNDERAGE_TXT),
	customText(&rejectedBecauseFemale, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEFEMALE_TXT),
	customText(&rejectedBecauseFemaleish, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEFEMALEISH_TXT),
	customText(&rejectedBecauseDresscode, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEDRESSCODE_TXT),
	customText(&rejectedBecauseBloodyClothes, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEBLOODYCLOTHES_TXT),
	customText(&rejectedBecauseDamagedClothes, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEDAMAGEDCLOTHES_TXT),
	customText(&rejectedBecauseSecondRateClothes, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSESECONDRATECLOTHES_TXT),
	customText(&rejectedBecauseWeapons, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEWEAPONS_TXT),
	customText(&rejectedBecauseGuestList, MOSTLY_ENDINGS_FOLDER + CONST_REJECTEDBECAUSEGUESTLIST_TXT),
	customText(&caseREJECTED_UNDERAGE, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_UNDERAGE_TXT),
	customText(&caseREJECTED_DRESSCODE, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_DRESSCODE_TXT),
	customText(&caseREJECTED_SMELLFUNNY, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_SMELLFUNNY_TXT),
	customText(&caseREJECTED_BLOODYCLOTHES, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_BLOODYCLOTHES_TXT),
	customText(&caseREJECTED_DAMAGEDCLOTHES, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_DAMAGEDCLOTHES_TXT),
	customText(&caseREJECTED_SECONDRATECLOTHES, MOSTLY_ENDINGS_FOLDER + CONST_CASEREJECTED_SECONDRATECLOTHES_TXT),
	customText(&conservativeLegalArgumentUnprocessed, talky + CONST_CONSERVATIVELEGALARGUMENT_TXT),
	customText(&youAreStupidTalkAboutIssuesUnprocessed, talky + CONST_YOUARESTUPIDTALKABOUTISSUES_TXT),
	customText(&issueTooLiberalUnprocessed, talky + CONST_ISSUETOOLIBERAL_TXT),
	customText(&issueEventStringUnprocessed, talky + CONST_ISSUEEVENTSTRING_TXT),
	customText(&conservatiseLawUnprocessed, talky + CONST_CONSERVATISELAW_TXT),
	customText(&liberalizeLawUnprocessed, talky + CONST_LIBERALIZELAW_TXT),
	customText(&discussIssuesUnprocessed, talky + CONST_DISCUSSISSUES_TXT),
	customText(&discussesIssuesUnprocessed, talky + CONST_DISCUSSESISSUES_TXT),
	customText(&talkAboutTheIssuesUnprocessed, talky + CONST_TALKABOUTTHEISSUES_TXT),
	customText(&endgameLawStringsUnprocessed, talky + CONST_ENDGAMELAWSTRINGS_TXT),
	customText(&state_biases_Unprocessed, MOSTLY_ENDINGS_FOLDER + CONST_STATE_BIASES_TXT),
	customText(&helpTopicUnprocessed, CONST_HELPTOPICS_TXT),
};
bool initialize_more_incomplete_txt();
//#endif//EXTERNALLYSTOREDDATA_CPP
//#endif// INCLUDES_H_INCLUDED
