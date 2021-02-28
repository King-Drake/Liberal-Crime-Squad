


#include "includes39.h"
#include "constStringexternallyStoredData.h"

bool initialize_more_incomplete_txt() {
	// this is the string data for activities. they write up to three lines of text about the activity
	// the ones with a skill on the end (e.g. ACTIVITY_SELL_ART, ACTIVITY_SELL_MUSIC) pick one of the three lines of text based on the skill in question
	data_activities =
	{
		 map<Activity, Data_Activity>::value_type(ACTIVITY_COMMUNITYSERVICE, Data_Activity('a', true, CONST_HELP_THE_ELDERLY_LOCAL_LIBRARY_ANYTHING, CONST_THAT_IS_LIBERAL)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_TROUBLE, Data_Activity('a', true, CONST_CREATE_PUBLIC_DISTURBANCES)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_GRAFFITI, Data_Activity('a', true, CONST_SPRAY_POLITICAL_GRAFFITI_ART_AND_HEART_WILL, CONST_ENHANCE_THE_LIBERAL_EFFECT)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_POLLS, Data_Activity('a', true, CONST_SEARCH_THE_INTERNET_FOR_PUBLIC_OPINION_POLLS, CONST_POLLS_WILL_GIVE_AN_IDEA_ON_HOW_THE_LIBERAL_AGENDA_IS_GOING_COMPUTERS, CONST_AND_INTELLIGENCE_WILL_PROVIDE_BETTER_RESULTS)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_DOS_ATTACKS, Data_Activity('a', true, CONST_HARASS_CONSERVATIVE_WEBSITES_COMPUTER_SKILL, CONST_WILL_GIVE_GREATER_EFFECT)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_HACKING, Data_Activity('a', true, CONST_HARASS_WEBSITES_AND_HACK_PRIVATE_NETWORKS, CONST_COMPUTER_SKILL_AND_INTELLIGENCE_WILL_GIVE_MORE_FREQUENT_RESULTS, CONST_MULTIPLE_HACKERS_WILL_INCREASE_CHANCES_OF_BOTH_SUCCESS_AND_DETECTION)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_WRITE_LETTERS, Data_Activity('a', true, CONST_WRITE_LETTERS_TO_NEWSPAPERS_ABOUT_CURRENT_EVENTS)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_WRITE_GUARDIAN, Data_Activity('a', true, CONST_WRITE_ARTICLES_FOR_THE_LCS_S_NEWSPAPER)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_DONATIONS, Data_Activity('b', true, CONST_WALK_AROUND_AND_ASK_FOR_DONATIONS_TO_THE_LCS, CONST_BASED_ON_PERSUASION_PUBLIC_S_VIEW_ON_THE_CAUSE_AND_HOW_WELL_DRESSED_THE, CONST_ACTIVIST_IS)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_SELL_TSHIRTS, Data_Activity('b', true, CONST_TIE_DYE_T_SHIRTS_AND_SELL_THEM_ON_THE_STREET, CONST_WILL_EMBROIDER_SHIRTS_AND_SELL_THEM_ON_THE_STREET, CONST_WILL_PRINT_AND_DISTRIBUTE_SHIRTS_WITH_LIBERAL_SLOGANS, SKILL_TAILORING)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_SELL_ART, Data_Activity('b', true, CONST_SKETCH_PEOPLE_AND_SELL_PORTRAITS_BACK_TO_THEM, CONST_WILL_MAKE_PRETTY_PAINTINGS_AND_SELL_THEM_ON_THE_STREETS, CONST_WILL_CREATE_AND_SELL_PAINTINGS_EMBRACING_THE_LIBERAL_AGENDA, SKILL_ART)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_SELL_MUSIC, Data_Activity('b', true, CONST_GO_OUT_INTO_THE_STREETS_AND_DRUM_ON_BUCKETS, CONST_OR_PLAY_GUITAR_IF_ONE_IS_EQUIPPED)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_SELL_DRUGS, Data_Activity('c', true, CONST_BAKE_AND_SELL_SPECIAL_ADULT_BROWNIES_THAT_OPEN, CONST_MAGICAL_SHIMMERING_DOORWAYS_TO_THE_ADAMANTIUM_PITS)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_PROSTITUTION, Data_Activity('c', true, CONST_TRADE_SEX_FOR_MONEY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_CCFRAUD, Data_Activity('c', true, CONST_COMMIT_CREDIT_CARD_FRAUD_ONLINE)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_DOS_RACKET, Data_Activity('c', true, CONST_DEMAND_MONEY_IN_EXCHANGE_FOR_NOT_BRINGING_DOWN, CONST_MAJOR_WEBSITES)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_RECRUITING, Data_Activity('d', true, CONST_TRY_TO_FIND_SOMEONE_TO_JOIN_THE_LCS)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STEALCARS, Data_Activity('d', true, CONST_TRY_TO_FIND_AND_STEAL_A_CAR)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_MAKE_ARMOR, Data_Activity('d', true, CONST_MAKE_CLOTHING)), // did not have any strings listed
		 map<Activity, Data_Activity>::value_type(ACTIVITY_REPAIR_ARMOR, Data_Activity('d', true, CONST_REPAIR_CLOTHING)), // did not have any strings listed
		 map<Activity, Data_Activity>::value_type(ACTIVITY_WHEELCHAIR, Data_Activity('d', true, CONST_TRY_TO_FIND_A_WHEELCHAIR)), // did not have any strings listed
		 map<Activity, Data_Activity>::value_type(ACTIVITY_AUGMENT, Data_Activity('d', true, CONST_WILL_AUGMENT_ANOTHER_LIBERAL_TO_MAKE_THEM, CONST_PHYSICALLY_SUPERIOR)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_HEAL, Data_Activity('h', true, CONST_ATTEMPT_FIRST_AID)), // did not have any strings listed
		 map<Activity, Data_Activity>::value_type(ACTIVITY_HOSTAGETENDING, Data_Activity('i', true, CONST_TEND_TO_HOSTAGES)), // did not have any strings listed
		 map<Activity, Data_Activity>::value_type(ACTIVITY_CLINIC, Data_Activity('m', true, CONST_GO_TO_THE_CLINIC)), // did not have any strings listed
		 map<Activity, Data_Activity>::value_type(ACTIVITY_BURY, Data_Activity('z', true, CONST_BURY_DEAD_BODIES)), // did not have any strings listed
		 map<Activity, Data_Activity>::value_type(ACTIVITY_TEACH_POLITICS, Data_Activity('t', false, CONST_SKILLS_TRAINED_WRITING_PERSUASION_LAW_STREET_SENSE_SCIENCE, CONST_RELIGION_BUSINESS_MUSIC_ART, CONST_CLASSES_COST_UP_TO_20_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_TEACH_COVERT, Data_Activity('t', false, CONST_SKILLS_TRAINED_COMPUTERS_SECURITY_STEALTH_DISGUISE_TAILORING, CONST_SEDUCTION_PSYCHOLOGY_DRIVING, CONST_CLASSES_COST_UP_TO_60_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_TEACH_FIGHTING, Data_Activity('t', false, CONST_SKILLS_TRAINED_ALL_WEAPON_SKILLS_MARTIAL_ARTS_DODGE_FIRST_AID, "", CONST_CLASSES_COST_UP_TO_100_DAY_TO_CONDUCT_ALL_LIBERALS_ABLE_WILL_ATTEND)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_DEBATING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_MARTIAL_ARTS, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_DRIVING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_PSYCHOLOGY, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_FIRST_AID, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_LAW, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_DISGUISE, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_SCIENCE, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_BUSINESS, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_GYMNASTICS, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_WRITING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_ART, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_MUSIC, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_TEACHING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_LOCKSMITHING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_COMPUTERS, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		 //  map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_COOKING, Data_Activity'l', true,CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		  map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_FENCING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		  map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_WEAVING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		  map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_RELIGION, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		  //  map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_MAGIC, Data_Activity'l', true,CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		   map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_CLUB, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		   map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_STREETSENSE, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		   map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_THROWING, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		   map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_STEALTH, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		   map<Activity, Data_Activity>::value_type(ACTIVITY_STUDY_SEDUCTION, Data_Activity('l', true, CONST_ATTEND_CLASSES_IN_UNIVERSITY_DISTRICT, CONST_AT_A_COST_OF_60_A_DAY)),
		   map<Activity, Data_Activity>::value_type(ACTIVITY_NONE, Data_Activity('x', false, ""))
	};
	pollingData = {
		map< Views, stringConnectedToView >::value_type(VIEW_GAY,  stringConnectedToView(CONST_PROTECTING_GAY_RIGHTS, CONST_PROTECTING_THE_TRADITIONAL_FAMILY)),
		map< Views, stringConnectedToView >::value_type(VIEW_DEATHPENALTY, stringConnectedToView(CONST_THE_UNJUST_DEATH_PENALTY, CONST_PROTECTING_THE_DEATH_PENALTY, CONST_RESTORING_THE_DEATH_PENALTY)),
		map< Views, stringConnectedToView >::value_type(VIEW_TAXES, stringConnectedToView(CONST_THE_OPPRESSIVE_TAX_STRUCTURE, CONST_THE_EXCESSIVE_TAX_BURDEN)),
		map< Views, stringConnectedToView >::value_type(VIEW_NUCLEARPOWER, stringConnectedToView(CONST_THE_DANGERS_OF_NUCLEAR_POWER, CONST_THREATS_TO_NUCLEAR_POWER, CONST_LEGALIZING_NUCLEAR_POWER)),
		map< Views, stringConnectedToView >::value_type(VIEW_ANIMALRESEARCH, stringConnectedToView(CONST_BRUTAL_ANIMAL_RESEARCH_PRACTICES,CONST_EXCESSIVE_REGULATION_OF_ANIMAL_RESEARCH)),
		map< Views, stringConnectedToView >::value_type(VIEW_POLICEBEHAVIOR, stringConnectedToView(CONST_PREVENTING_POLICE_BRUTALITY,CONST_EXPANDING_POLICE_POWERS)),
		map< Views, stringConnectedToView >::value_type(VIEW_INTELLIGENCE, stringConnectedToView(CONST_CIVIL_LIBERTIES_AND_PERSONAL_PRIVACY,CONST_NATIONAL_SECURITY_AND_INTELLIGENCE)),
		map< Views, stringConnectedToView >::value_type(VIEW_FREESPEECH, stringConnectedToView(CONST_PROTECTING_FREE_SPEECH,CONST_ENDING_HATE_SPEECH)),
		map< Views, stringConnectedToView >::value_type(VIEW_GENETICS, stringConnectedToView(CONST_THE_DANGERS_OF_GENETIC_ENGINEERING,CONST_EXCESSIVE_REGULATION_OF_GENETIC_RESEARCH)),
		map< Views, stringConnectedToView >::value_type(VIEW_JUSTICES, stringConnectedToView(CONST_APPOINTING_PROPER_LIBERAL_JUSTICES,CONST_APPOINTING_PROPER_CONSERVATIVE_JUSTICES)),
		map< Views, stringConnectedToView >::value_type(VIEW_SWEATSHOPS, stringConnectedToView(CONST_THREATS_TO_LABOR_RIGHTS,CONST_CORRUPT_UNION_THUGS)),
		map< Views, stringConnectedToView >::value_type(VIEW_POLLUTION, stringConnectedToView(CONST_THREATS_TO_THE_ENVIRONMENT,CONST_EXCESSIVE_REGULATION_OF_INDUSTRY)),
		map< Views, stringConnectedToView >::value_type(VIEW_CORPORATECULTURE, stringConnectedToView(CONST_CORPORATE_CORRUPTION,CONST_EXCESSIVE_REGULATION_OF_CORPORATIONS)),
		map< Views, stringConnectedToView >::value_type(VIEW_CEOSALARY, stringConnectedToView(CONST_SEVERE_INCOME_INEQUALITY,CONST_RESISTING_COMMUNIST_WAGE_LIMITS)),
		map< Views, stringConnectedToView >::value_type(VIEW_PRISONS, stringConnectedToView(CONST_STOPPING_THE_PRISONERS_SUFFERING,CONST_PUTTING_THE_PRISONERS_IN_LINE)),
		map< Views, stringConnectedToView >::value_type(VIEW_IMMIGRATION, stringConnectedToView(CONST_IMMIGRANT_RIGHTS, CONST_ILLEGAL_IMMIGRATION, CONST_UNCONTROLLED_IMMIGRATION, CONST_UNCONTROLLED_IMMIGRATION)),
		map< Views, stringConnectedToView >::value_type(VIEW_DRUGS, stringConnectedToView(CONST_DRUG_RIGHTS,CONST_DRUG_ABUSE)),
		map< Views, stringConnectedToView >::value_type(VIEW_WOMEN, stringConnectedToView(CONST_WOMEN_S_EQUALITY,CONST_WOMEN)),
		map< Views, stringConnectedToView >::value_type(VIEW_CIVILRIGHTS, stringConnectedToView(CONST_CIVIL_RIGHTS,CONST_TROUBLEMAKING_MINORITIES)),
		map< Views, stringConnectedToView >::value_type(VIEW_GUNCONTROL, stringConnectedToView(CONST_GUN_VIOLENCE,CONST_PROTECTING_THE_SECOND_AMENDMENT)),
		map< Views, stringConnectedToView >::value_type(VIEW_MILITARY, stringConnectedToView(CONST_MILITARY_IMPERIALISM,CONST_DEFENDING_THE_NATION)),
		map< Views, stringConnectedToView >::value_type(VIEW_CONSERVATIVECRIMESQUAD, stringConnectedToView(CONST_THE_CONSERVATIVE_CRIME_SQUAD,CONST_THE_CCS_TERRORISTS)),
		map< Views, stringConnectedToView >::value_type(VIEW_TORTURE, stringConnectedToView(CONST_ENDING_THE_USE_OF_TORTURE,CONST_ENHANCING_INTERROGATIONS))
	};
	trainingActivity = {
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_DEBATING,SKILL_PERSUASION),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_MARTIAL_ARTS, SKILL_HANDTOHAND),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_DRIVING, SKILL_DRIVING),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_PSYCHOLOGY, SKILL_PSYCHOLOGY),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_FIRST_AID, SKILL_FIRSTAID),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_LAW, SKILL_LAW),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_DISGUISE, SKILL_DISGUISE),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_SCIENCE, SKILL_SCIENCE),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_BUSINESS, SKILL_BUSINESS),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_GYMNASTICS, SKILL_DODGE),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_LOCKSMITHING, SKILL_SECURITY),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_MUSIC, SKILL_MUSIC),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_ART, SKILL_ART),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_TEACHING, SKILL_TEACHING),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_WRITING, SKILL_WRITING),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_COMPUTERS, SKILL_COMPUTERS),
		//map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_COOKING,SKILL_COOKING),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_FENCING, SKILL_SWORD),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_WEAVING, SKILL_TAILORING),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_RELIGION, SKILL_RELIGION),
		//map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_MAGIC,SKILL_MAGIC),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_CLUB, SKILL_CLUB),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_STREETSENSE, SKILL_STREETSENSE),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_THROWING, SKILL_THROWING),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_STEALTH, SKILL_STEALTH),
		map< Activity, CreatureSkill>::value_type(ACTIVITY_STUDY_SEDUCTION, SKILL_SEDUCTION)
	};
	// This is the lesson data for the University.
	data_lessons = {
	   ActivityAndString(ACTIVITY_STUDY_DEBATING,	CONST_PUBLIC_POLICY),
	   ActivityAndString(ACTIVITY_STUDY_BUSINESS,	CONST_ECONOMICS),
	   ActivityAndString(ACTIVITY_STUDY_PSYCHOLOGY,	CONST_X_PSYCHOLOGY),
	   ActivityAndString(ACTIVITY_STUDY_LAW,	CONST_CRIMINAL_LAW),
	   ActivityAndString(ACTIVITY_STUDY_SCIENCE,	CONST_PHYSICS),
	   ActivityAndString(ACTIVITY_STUDY_DRIVING,	CONST_DRIVERS_ED),
	   ActivityAndString(ACTIVITY_STUDY_FIRST_AID,	CONST_X_FIRST_AID),
	   ActivityAndString(ACTIVITY_STUDY_ART,	CONST_PAINTING),
	   ActivityAndString(ACTIVITY_STUDY_DISGUISE,	CONST_THEATRE),
	   ActivityAndString(ACTIVITY_STUDY_MARTIAL_ARTS,CONST_KUNG_FU),
	   ActivityAndString(ACTIVITY_STUDY_GYMNASTICS,	CONST_GYMNASTICS),
	   ActivityAndString(ACTIVITY_STUDY_WRITING,	CONST_X_WRITING),
	   ActivityAndString(ACTIVITY_STUDY_TEACHING,	CONST_EDUCATION),
	   ActivityAndString(ACTIVITY_STUDY_MUSIC,	CONST_X_MUSIC),
	   ActivityAndString(ACTIVITY_STUDY_LOCKSMITHING,CONST_LOCKSMITHING),
	   // Terra Vitae
	   ActivityAndString(ACTIVITY_STUDY_COMPUTERS, CONST_COMPUTER_SCIENCE),
	   ActivityAndString(ACTIVITY_STUDY_FENCING, CONST_FENCING),
	   ActivityAndString(ACTIVITY_STUDY_WEAVING, CONST_WEAVING),
	   ActivityAndString(ACTIVITY_STUDY_RELIGION, CONST_X_RELIGION),
	   //, ActivityAndString(ACTIVITY_STUDY_MAGIC, CONST_MAGIC)
	   ActivityAndString(ACTIVITY_STUDY_CLUB,	CONST_BASEBALL),
	   ActivityAndString(ACTIVITY_STUDY_STREETSENSE,	CONST_POLICE_PROCEDURE),
	   ActivityAndString(ACTIVITY_STUDY_THROWING,	CONST_BASKETBALL),
	   ActivityAndString(ACTIVITY_STUDY_STEALTH,	CONST_X_STEALTH),
	   ActivityAndString(ACTIVITY_STUDY_SEDUCTION,CONST_BUYING_DRINKS)
	};
	hackingActivities = {
	   activityData(CONST_REVEALED_HUGE_POLITICAL_BIAS_IN_INS_PROCESSES.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({ ChangeOfOpinion(VIEW_IMMIGRATION,2,0,75), ChangeOfOpinion(VIEW_FREESPEECH,2,0,75) }), vector<string>({})),
	   //Scambaiting, except you're baiting a CEO
	   activityData(CONST_PUBLISHED_EMAILS_REVEALING_CEO_TAX_EVASION.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({ ChangeOfOpinion(VIEW_CEOSALARY,2,0,75),	ChangeOfOpinion(VIEW_TAXES,2,0,75) }), vector<string>({})),
	   activityData(CONST_SPREAD_VIDEOS_OF_RACIST_POLICE_BRUTALITY.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({ ChangeOfOpinion(VIEW_POLICEBEHAVIOR,2,0,75),	ChangeOfOpinion(VIEW_CIVILRIGHTS,2,0,75) }), vector<string>({})),
	   // *JDS* Penetrated government networks; don't get any loot, but do scare the info community
	   activityData(CONST_CAUSED_A_SCARE_BY_BREAKING_INTO_A_CIA_NETWORK.c_str(), DIFFICULTY_IMPOSSIBLE, 25, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({ ChangeOfOpinion(VIEW_INTELLIGENCE,10,0,75) }), vector<string>({})),
	   activityData(CONST_BROKE_INTO_MILITARY_NETWORKS_LEAVING_LCS_SLOGANS.c_str(), DIFFICULTY_IMPOSSIBLE, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({ ChangeOfOpinion(VIEW_LIBERALCRIMESQUAD,5,0,75) }), vector<string>({})),
	   activityData(CONST_SUBVERTED_A_CONSERVATIVE_FAMILY_FORUM.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({ ChangeOfOpinion(VIEW_GAY,2,0,75),	ChangeOfOpinion(VIEW_WOMEN,2,0,75) }), vector<string>({})),
	   activityData(CONST_SABOTAGED_A_GENETICS_RESEARCH_COMPANY_S_NETWORK.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({ ChangeOfOpinion(VIEW_GENETICS,2,0,75) }), vector<string>({})),
	   activityData(CONST_DISCOVERED_EVIDENCE_OF_JUDICIAL_CORRUPTION.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({}), vector<string>({ tag_LOOT_JUDGEFILES })),
	   activityData(CONST_UNCOVERED_INFORMATION_ON_DANGEROUS_RESEARCH.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({}), vector<string>({ tag_LOOT_RESEARCHFILES })),
	   activityData(CONST_PILFERED_FILES_FROM_A_CORPORATE_SERVER.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({}), vector<string>({ tag_LOOT_CORPFILES })),
	   activityData(CONST_INTERCEPTED_INTERNAL_MEDIA_EMAILS.c_str(), DIFFICULTY_SUPERHEROIC, 10, LAWFLAG_INFORMATION, vector<ChangeOfOpinion>({}), vector<string>({ tag_LOOT_CABLENEWSFILES,tag_LOOT_AMRADIOFILES }))
	};
	activate_menu_items =
	{
		map<char, vector<ActivityAndString> >::value_type('a',vector<ActivityAndString>({ ActivityAndString(1, ACTIVITY_COMMUNITYSERVICE, CONST_COMMUNITY_SERVICE),
		ActivityAndString(2, ACTIVITY_TROUBLE,	CONST_LIBERAL_DISOBEDIENCE),
			ActivityAndString(3, ACTIVITY_GRAFFITI,	CONST_X_GRAFFITI),
			ActivityAndString(4, ACTIVITY_POLLS,	CONST_SEARCH_OPINION_POLLS),
			//ActivityAndString(ACTIVITY_DOS_ATTACKS, CONST_HARASS_WEBSITES),
			ActivityAndString(5, ACTIVITY_HACKING,	CONST_HACKING),
			ActivityAndString(6, ACTIVITY_WRITE_LETTERS,	CONST_WRITE_TO_NEWSPAPERS),
			ActivityAndString(7, ACTIVITY_WRITE_GUARDIAN,	CONST_WRITE_FOR_THE_LIBERAL_GUARDIAN, ACTIVITIY_MENU_CHECK_PRESS) })), // 
		map<char, vector<ActivityAndString> >::value_type('b',vector<ActivityAndString>({ ActivityAndString(1, ACTIVITY_DONATIONS,	CONST_SOLICIT_DONATIONS),
			ActivityAndString(2, ACTIVITY_SELL_TSHIRTS,	CONST_SELL_TIE_DYED_T_SHIRTS, CONST_SELL_EMBROIDERED_SHIRTS, CONST_SELL_LIBERAL_T_SHIRTS, SKILL_TAILORING),
			ActivityAndString(3, ACTIVITY_SELL_ART,	CONST_SELL_PORTRAIT_SKETCHES, CONST_SELL_PAINTINGS, CONST_SELL_LIBERAL_ART, SKILL_ART),
			ActivityAndString(4, ACTIVITY_SELL_MUSIC,	CONST_PLAY_STREET_MUSIC, CONST_PLAY_STREET_MUSIC, CONST_PLAY_LIBERAL_MUSIC, SKILL_MUSIC) })),
		map<char, vector<ActivityAndString> >::value_type('c',vector<ActivityAndString>({ ActivityAndString(1, ACTIVITY_SELL_DRUGS,	CONST_SELL_BROWNIES),
			ActivityAndString(2, ACTIVITY_PROSTITUTION,	CONST_PROSTITUTION, ACTIVITIY_MENU_CHECK_AGE),
			//	ActivityAndString(ACTIVITY_DOS_RACKET, CONST_ELECTRONIC_PROTECTION_RACKET),
			ActivityAndString(3, ACTIVITY_CCFRAUD,	CONST_STEAL_CREDIT_CARD_NUMBERS) })),
		map<char, vector<ActivityAndString> >::value_type('d',vector<ActivityAndString>({ ActivityAndString(1, ACTIVITY_RECRUITING,	CONST_X_RECRUITING),
			ActivityAndString(2, ACTIVITY_MAKE_ARMOR,	CONST_X_MAKE_CLOTHING),
			ActivityAndString(3, ACTIVITY_REPAIR_ARMOR,	CONST_X_REPAIR_CLOTHING),
			ActivityAndString(4, ACTIVITY_STEALCARS,	CONST_STEAL_A_CAR, ACTIVITIY_MENU_CHECK_CAN_WALK),
			ActivityAndString(5, ACTIVITY_WHEELCHAIR,	CONST_PROCURE_A_WHEELCHAIR, ACTIVITIY_MENU_CHECK_WHEELCHAIR),
			ActivityAndString(6, ACTIVITY_AUGMENT, CONST_AUGMENT_A_LIBERAL, ACTIVITIY_MENU_CHECK_CAN_AUGMENT) })),
		map<char, vector<ActivityAndString> >::value_type('t',vector<ActivityAndString>({ ActivityAndString(0,  ACTIVITY_NONE,	CONST_TEACH_LIBERALS_ABOUT_WHAT),
			ActivityAndString(1, ACTIVITY_TEACH_POLITICS,	CONST_POLITICAL_ACTIVISM),
			ActivityAndString(2, ACTIVITY_TEACH_COVERT,	CONST_INFILTRATION),
			ActivityAndString(3, ACTIVITY_TEACH_FIGHTING,	CONST_URBAN_WARFARE) }))
	};
	recruitable_creatures = {
	   RecruitData(CREATURE_VETERAN, CONST_ARMY_VETERAN, 4),
	   RecruitData(CREATURE_ATHLETE, CONST_ATHLETE, 4),
	   RecruitData(CREATURE_COLLEGESTUDENT, CONST_COLLEGE_STUDENT, 1),
	   RecruitData(CREATURE_PROGRAMMER, CONST_COMPUTER_PROGRAMMER, 4),
	   RecruitData(CREATURE_DANCER, CONST_DANCER, 4),
	   RecruitData(CREATURE_DOCTOR, CONST_DOCTOR, 4),
	   RecruitData(CREATURE_FASHIONDESIGNER, CONST_FASHION_DESIGNER, 6),
	   RecruitData(CREATURE_GANGMEMBER, CONST_GANG_MEMBER, 2),
	   RecruitData(CREATURE_HIPPIE, CONST_HIPPIE, 1),
	   RecruitData(CREATURE_JOURNALIST, CONST_JOURNALIST, 4),
	   RecruitData(CREATURE_JUDGE_LIBERAL, CONST_JUDGE, 6),
	   RecruitData(CREATURE_LAWYER, CONST_LAWYER.c_str(), 4),
	   RecruitData(CREATURE_LOCKSMITH, CONST_LOCKSMITH.c_str(), 6),
	   RecruitData(CREATURE_MARTIALARTIST, CONST_MARTIAL_ARTIST.c_str(), 4),
	   RecruitData(CREATURE_MUSICIAN, CONST_MUSICIAN.c_str(), 4),
	   RecruitData(CREATURE_MUTANT, CONST_MUTANT.c_str(), 4),
	   RecruitData(CREATURE_PROSTITUTE, CONST_PROSTITUTE.c_str(), 2),
	   RecruitData(CREATURE_PSYCHOLOGIST, CONST_PSYCHOLOGIST.c_str(), 4),
	   RecruitData(CREATURE_TAXIDRIVER, CONST_TAXI_DRIVER.c_str(), 4),
	   RecruitData(CREATURE_TEACHER, CONST_TEACHER.c_str(), 4)
	};
	trainingActivitySorting = {
		map<short, string>::value_type(SORTINGCHOICE_LIBERALS, CONST_ACTIVE_LIBERALS),
		map<short, string>::value_type(SORTINGCHOICE_HOSTAGES, CONST_HOSTAGES),
		map<short, string>::value_type(SORTINGCHOICE_CLINIC, CONST_LIBERALS_IN_HOSPITAL),
		map<short, string>::value_type(SORTINGCHOICE_JUSTICE, CONST_OPPRESSED_LIBERALS),
		map<short, string>::value_type(SORTINGCHOICE_SLEEPERS, CONST_X_SLEEPERS_DOT),
		map<short, string>::value_type(SORTINGCHOICE_DEAD, CONST_DEAD_PEOPLE),
		map<short, string>::value_type(SORTINGCHOICE_AWAY, CONST_PEOPLE_AWAY),
		map<short, string>::value_type(SORTINGCHOICE_ACTIVATE, CONST_LIBERAL_ACTIVITY),
		map<short, string>::value_type(SORTINGCHOICE_ACTIVATESLEEPERS, CONST_SLEEPER_ACTIVITY),
		map<short, string>::value_type(SORTINGCHOICE_ASSEMBLESQUAD, CONST_AVAILABLE_LIBERALS),
		map<short, string>::value_type(SORTINGCHOICE_BASEASSIGN, CONST_SQUADLESS_MEMBERS),
		map<short, string>::value_type(SORTINGCHOICENUM,CONST_ERROR_INVALID_VALUE_FOR_SORTINGCHOICE)
	};
	incomeTypes = {
		map<short, string>::value_type(INCOME_BROWNIES,CONST_BROWNIES),
		map<short, string>::value_type(INCOME_CARS,CONST_CAR_SALES),
		map<short, string>::value_type(INCOME_CCFRAUD,CONST_CREDIT_CARD_FRAUD),
		map<short, string>::value_type(INCOME_DONATIONS,CONST_DONATIONS),
		map<short, string>::value_type(INCOME_SKETCHES,CONST_DRAWING_SALES),
		map<short, string>::value_type(INCOME_EMBEZZLEMENT,CONST_EMBEZZLEMENT),
		map<short, string>::value_type(INCOME_EXTORTION,CONST_EXTORTION),
		map<short, string>::value_type(INCOME_HUSTLING,CONST_HUSTLING),
		map<short, string>::value_type(INCOME_PAWN,CONST_PAWNING_GOODS),
		map<short, string>::value_type(INCOME_PROSTITUTION,CONST_PROSTITUTION),
		map<short, string>::value_type(INCOME_BUSKING,CONST_STREET_MUSIC),
		map<short, string>::value_type(INCOME_THIEVERY,CONST_THIEVERY),
		map<short, string>::value_type(INCOME_TSHIRTS,CONST_T_SHIRT_SALES),
		map<short, string>::value_type(INCOMETYPENUM,CONST_OTHER_INCOME)
	};
	expenseTypes = {
		map<short, string>::value_type(EXPENSE_TROUBLEMAKING, CONST_ACTIVISM),
		map<short, string>::value_type(EXPENSE_CONFISCATED, CONST_CONFISCATED),
		map<short, string>::value_type(EXPENSE_DATING, CONST_DATING),
		map<short, string>::value_type(EXPENSE_SKETCHES, CONST_DRAWING_MATERIALS),
		map<short, string>::value_type(EXPENSE_FOOD, CONST_GROCERIES),
		map<short, string>::value_type(EXPENSE_HOSTAGE, CONST_HOSTAGE_TENDING),
		map<short, string>::value_type(EXPENSE_LEGAL, CONST_LEGAL_FEES),
		map<short, string>::value_type(EXPENSE_MANUFACTURE, CONST_MANUFACTURING),
		map<short, string>::value_type(EXPENSE_CARS, CONST_NEW_CARS),
		map<short, string>::value_type(EXPENSE_SHOPPING, CONST_PURCHASING_GOODS),
		map<short, string>::value_type(EXPENSE_RECRUITMENT, CONST_RECRUITMENT),
		map<short, string>::value_type(EXPENSE_RENT, CONST_RENT),
		map<short, string>::value_type(EXPENSE_COMPOUND, CONST_SAFEHOUSE_INVESTMENTS),
		map<short, string>::value_type(EXPENSE_TRAINING, CONST_TRAINING),
		map<short, string>::value_type(EXPENSE_TRAVEL, tag_Travel),
		map<short, string>::value_type(EXPENSE_TSHIRTS, CONST_T_SHIRT_MATERIALS),
		map<short, string>::value_type(EXPENSETYPENUM, CONST_OTHER_EXPENSES)
	};
	siteReadMap = {
		map<short, string>::value_type(SITE_RESIDENTIAL_TENEMENT, CONST_APARTMENTINDUSTRIAL),
		map<short, string>::value_type(SITE_RESIDENTIAL_APARTMENT, CONST_APARTMENTUNIVERSITY),
		map<short, string>::value_type(SITE_RESIDENTIAL_APARTMENT_UPSCALE, CONST_APARTMENTDOWNTOWN),
		map<short, string>::value_type(SITE_INDUSTRY_WAREHOUSE, CONST_WAREHOUSE),
		map<short, string>::value_type(SITE_RESIDENTIAL_SHELTER, CONST_HOMELESSSHELTER),
		map<short, string>::value_type(SITE_BUSINESS_CRACKHOUSE, CONST_CRACKHOUSE),
		map<short, string>::value_type(SITE_BUSINESS_BARANDGRILL, CONST_BARANDGRILL),
		map<short, string>::value_type(SITE_RESIDENTIAL_BOMBSHELTER, CONST_BOMBSHELTER),
		map<short, string>::value_type(SITE_OUTDOOR_BUNKER, CONST_BUNKER),
		map<short, string>::value_type(SITE_LABORATORY_COSMETICS, CONST_COSMETICSLAB),
		map<short, string>::value_type(SITE_LABORATORY_GENETIC, CONST_GENETICSLAB),
		map<short, string>::value_type(SITE_GOVERNMENT_POLICESTATION, CONST_POLICESTATION),
		map<short, string>::value_type(SITE_GOVERNMENT_COURTHOUSE, CONST_COURTHOUSE),
		map<short, string>::value_type(SITE_GOVERNMENT_PRISON, CONST_PRISON),
		map<short, string>::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ, CONST_INTELLIGENCEHQ),
		map<short, string>::value_type(SITE_GOVERNMENT_ARMYBASE, CONST_ARMYBASE),
		map<short, string>::value_type(SITE_GOVERNMENT_FIRESTATION, CONST_FIRESTATION),
		map<short, string>::value_type(SITE_INDUSTRY_SWEATSHOP, CONST_SWEATSHOP),
		map<short, string>::value_type(SITE_INDUSTRY_POLLUTER, CONST_FACTORY),
		map<short, string>::value_type(SITE_CORPORATE_HEADQUARTERS, CONST_CORPORATEHQ),
		map<short, string>::value_type(SITE_CORPORATE_HOUSE, CONST_CEOHOUSE),
		map<short, string>::value_type(SITE_MEDIA_AMRADIO, CONST_RADIOSTATION),
		map<short, string>::value_type(SITE_MEDIA_CABLENEWS, CONST_CABLENEWS),
		map<short, string>::value_type(SITE_BUSINESS_JUICEBAR, CONST_JUICEBAR),
		map<short, string>::value_type(SITE_BUSINESS_INTERNETCAFE, CONST_INTERNETCAFE),
		map<short, string>::value_type(SITE_BUSINESS_CIGARBAR, CONST_CIGARBAR),
		map<short, string>::value_type(SITE_BUSINESS_LATTESTAND, CONST_LATTESTAND),
		map<short, string>::value_type(SITE_BUSINESS_VEGANCOOP, CONST_VEGANCOOP),
		map<short, string>::value_type(SITE_OUTDOOR_PUBLICPARK, CONST_PARK),
		map<short, string>::value_type(SITE_BUSINESS_BANK, CONST_BANK),
		map<short, string>::value_type(SITE_INDUSTRY_NUCLEAR, CONST_NUCLEARPLANT),
		map<short, string>::value_type(SITE_GOVERNMENT_WHITE_HOUSE, CONST_WHITEHOUSE)
	};
	buildThisSite = {
		map<short, string>::value_type(SITE_RESIDENTIAL_TENEMENT,CONST_RESIDENTIAL_APARTMENT),
		map<short, string>::value_type(SITE_RESIDENTIAL_APARTMENT,CONST_RESIDENTIAL_APARTMENT),
		map<short, string>::value_type(SITE_RESIDENTIAL_APARTMENT_UPSCALE,CONST_RESIDENTIAL_APARTMENT),
		map<short, string>::value_type(SITE_INDUSTRY_WAREHOUSE,CONST_GENERIC_UNSECURE),
		map<short, string>::value_type(SITE_RESIDENTIAL_SHELTER,CONST_GENERIC_UNSECURE),
		map<short, string>::value_type(SITE_BUSINESS_CRACKHOUSE,CONST_GENERIC_UNSECURE),
		map<short, string>::value_type(SITE_BUSINESS_BANK,CONST_GENERIC_LOBBY),
		map<short, string>::value_type(SITE_BUSINESS_BARANDGRILL,CONST_GENERIC_LOBBY),
		map<short, string>::value_type(SITE_RESIDENTIAL_BOMBSHELTER,CONST_GENERIC_LOBBY),
		map<short, string>::value_type(SITE_OUTDOOR_BUNKER,CONST_GENERIC_LOBBY),
		map<short, string>::value_type(SITE_GOVERNMENT_FIRESTATION,CONST_GENERIC_LOBBY),
		map<short, string>::value_type(SITE_LABORATORY_COSMETICS,CONST_LABORATORY_COSMETICS),
		map<short, string>::value_type(SITE_LABORATORY_GENETIC,CONST_LABORATORY_GENETICS),
		map<short, string>::value_type(SITE_GOVERNMENT_POLICESTATION,CONST_GOVERNMENT_POLICESTATION),
		map<short, string>::value_type(SITE_GOVERNMENT_COURTHOUSE,CONST_GOVERNMENT_COURTHOUSE),
		map<short, string>::value_type(SITE_GOVERNMENT_PRISON,CONST_GOVERNMENT_PRISON),
		map<short, string>::value_type(SITE_GOVERNMENT_INTELLIGENCEHQ,CONST_GOVERNMENT_INTELLIGENCEHQ),
		map<short, string>::value_type(SITE_GOVERNMENT_WHITE_HOUSE,CONST_GOVERNMENT_WHITE_HOUSE),
		map<short, string>::value_type(SITE_GOVERNMENT_ARMYBASE,CONST_GOVERNMENT_ARMYBASE),
		map<short, string>::value_type(SITE_INDUSTRY_SWEATSHOP,CONST_INDUSTRY_SWEATSHOP),
		map<short, string>::value_type(SITE_INDUSTRY_POLLUTER,CONST_INDUSTRY_POLLUTER),
		map<short, string>::value_type(SITE_INDUSTRY_NUCLEAR,CONST_INDUSTRY_NUCLEAR),
		map<short, string>::value_type(SITE_CORPORATE_HEADQUARTERS,CONST_CORPORATE_HEADQUARTERS),
		map<short, string>::value_type(SITE_CORPORATE_HOUSE,CONST_CORPORATE_HOUSE),
		map<short, string>::value_type(SITE_MEDIA_AMRADIO,CONST_MEDIA_AMRADIO),
		map<short, string>::value_type(SITE_MEDIA_CABLENEWS,CONST_MEDIA_CABLENEWS),
		map<short, string>::value_type(SITE_BUSINESS_JUICEBAR,CONST_BUSINESS_CAFE),
		map<short, string>::value_type(SITE_BUSINESS_INTERNETCAFE,CONST_BUSINESS_INTERNETCAFE),
		map<short, string>::value_type(SITE_BUSINESS_CIGARBAR,CONST_BUSINESS_RESTRICTEDCAFE),
		map<short, string>::value_type(SITE_BUSINESS_LATTESTAND,CONST_OUTDOOR_LATTESTAND),
		map<short, string>::value_type(SITE_BUSINESS_VEGANCOOP,CONST_GENERIC_ONEROOM),
		map<short, string>::value_type(SITE_OUTDOOR_PUBLICPARK,CONST_OUTDOOR_PUBLICPARK),
	};
	getSpecial = {
		map<string, short>::value_type(CONST_LAB_COSMETICS_CAGEDANIMALS, SPECIAL_LAB_COSMETICS_CAGEDANIMALS),
		map<string, short>::value_type(CONST_LAB_GENETIC_CAGEDANIMALS, SPECIAL_LAB_GENETIC_CAGEDANIMALS),
		map<string, short>::value_type(CONST_POLICESTATION_LOCKUP, SPECIAL_POLICESTATION_LOCKUP),
		map<string, short>::value_type(CONST_COURTHOUSE_LOCKUP, SPECIAL_COURTHOUSE_LOCKUP),
		map<string, short>::value_type(CONST_COURTHOUSE_JURYROOM, SPECIAL_COURTHOUSE_JURYROOM),
		map<string, short>::value_type(CONST_PRISON_CONTROL, SPECIAL_PRISON_CONTROL),
		map<string, short>::value_type(CONST_PRISON_CONTROL_LOW, SPECIAL_PRISON_CONTROL_LOW),
		map<string, short>::value_type(CONST_PRISON_CONTROL_MEDIUM, SPECIAL_PRISON_CONTROL_MEDIUM),
		map<string, short>::value_type(CONST_PRISON_CONTROL_HIGH, SPECIAL_PRISON_CONTROL_HIGH),
		map<string, short>::value_type(CONST_INTEL_SUPERCOMPUTER, SPECIAL_INTEL_SUPERCOMPUTER),
		map<string, short>::value_type(CONST_SWEATSHOP_EQUIPMENT, SPECIAL_SWEATSHOP_EQUIPMENT),
		map<string, short>::value_type(CONST_POLLUTER_EQUIPMENT, SPECIAL_POLLUTER_EQUIPMENT),
		map<string, short>::value_type(CONST_NUCLEAR_ONOFF, SPECIAL_NUCLEAR_ONOFF),
		map<string, short>::value_type(CONST_HOUSE_PHOTOS, SPECIAL_HOUSE_PHOTOS),
		map<string, short>::value_type(CONST_ARMYBASE_ARMORY, SPECIAL_ARMORY),
		map<string, short>::value_type(CONST_HOUSE_CEO, SPECIAL_HOUSE_CEO),
		map<string, short>::value_type(CONST_CORPORATE_FILES, SPECIAL_CORPORATE_FILES),
		map<string, short>::value_type(CONST_RADIO_BROADCASTSTUDIO, SPECIAL_RADIO_BROADCASTSTUDIO),
		map<string, short>::value_type(CONST_NEWS_BROADCASTSTUDIO, SPECIAL_NEWS_BROADCASTSTUDIO),
		map<string, short>::value_type(CONST_APARTMENT_LANDLORD, SPECIAL_APARTMENT_LANDLORD),
		map<string, short>::value_type(CONST_APARTMENT_SIGN, SPECIAL_SIGN_ONE),
		map<string, short>::value_type(CONST_RESTAURANT_TABLE, SPECIAL_RESTAURANT_TABLE),
		map<string, short>::value_type(CONST_CAFE_COMPUTER, SPECIAL_CAFE_COMPUTER),
		map<string, short>::value_type(CONST_PARK_BENCH, SPECIAL_PARK_BENCH),
		map<string, short>::value_type(CONST_STAIRS_UP, SPECIAL_STAIRS_UP),
		map<string, short>::value_type(CONST_STAIRS_DOWN, SPECIAL_STAIRS_DOWN),
		map<string, short>::value_type(CONST_CLUB_BOUNCER, SPECIAL_CLUB_BOUNCER),
		map<string, short>::value_type(CONST_CLUB_BOUNCER_SECONDVISIT, SPECIAL_CLUB_BOUNCER_SECONDVISIT)
	};
	getUnique = {
		map<string, short>::value_type(CONST_LAB_COSMETICS_CAGEDANIMALS, SPECIAL_LAB_COSMETICS_CAGEDANIMALS),
		map<string, short>::value_type(CONST_LAB_GENETIC_CAGEDANIMALS, SPECIAL_LAB_GENETIC_CAGEDANIMALS),
		map<string, short>::value_type(CONST_POLICESTATION_LOCKUP, SPECIAL_POLICESTATION_LOCKUP),
		map<string, short>::value_type(CONST_COURTHOUSE_LOCKUP, SPECIAL_COURTHOUSE_LOCKUP),
		map<string, short>::value_type(CONST_COURTHOUSE_JURYROOM, SPECIAL_COURTHOUSE_JURYROOM),
		map<string, short>::value_type(CONST_PRISON_CONTROL, SPECIAL_PRISON_CONTROL),
		map<string, short>::value_type(CONST_PRISON_CONTROL_LOW, SPECIAL_PRISON_CONTROL_LOW),
		map<string, short>::value_type(CONST_PRISON_CONTROL_MEDIUM, SPECIAL_PRISON_CONTROL_MEDIUM),
		map<string, short>::value_type(CONST_PRISON_CONTROL_HIGH, SPECIAL_PRISON_CONTROL_HIGH),
		map<string, short>::value_type(CONST_INTEL_SUPERCOMPUTER, SPECIAL_INTEL_SUPERCOMPUTER),
		map<string, short>::value_type(CONST_SWEATSHOP_EQUIPMENT, SPECIAL_SWEATSHOP_EQUIPMENT),
		map<string, short>::value_type(CONST_POLLUTER_EQUIPMENT, SPECIAL_POLLUTER_EQUIPMENT),
		map<string, short>::value_type(CONST_NUCLEAR_ONOFF, SPECIAL_NUCLEAR_ONOFF),
		map<string, short>::value_type(CONST_HOUSE_PHOTOS, SPECIAL_HOUSE_PHOTOS),
		map<string, short>::value_type(CONST_ARMYBASE_ARMORY, SPECIAL_ARMORY),
		map<string, short>::value_type(CONST_HOUSE_CEO, SPECIAL_HOUSE_CEO),
		map<string, short>::value_type(CONST_CORPORATE_FILES, SPECIAL_CORPORATE_FILES),
		map<string, short>::value_type(CONST_RADIO_BROADCASTSTUDIO, SPECIAL_RADIO_BROADCASTSTUDIO),
		map<string, short>::value_type(CONST_NEWS_BROADCASTSTUDIO, SPECIAL_NEWS_BROADCASTSTUDIO),
		map<string, short>::value_type(CONST_APARTMENT_LANDLORD, SPECIAL_APARTMENT_LANDLORD),
		map<string, short>::value_type(CONST_APARTMENT_SIGN, SPECIAL_SIGN_ONE),
		map<string, short>::value_type(CONST_RESTAURANT_TABLE, SPECIAL_RESTAURANT_TABLE),
		map<string, short>::value_type(CONST_CAFE_COMPUTER, SPECIAL_CAFE_COMPUTER),
		map<string, short>::value_type(CONST_PARK_BENCH, SPECIAL_PARK_BENCH),
		map<string, short>::value_type(CONST_STAIRS_UP, SPECIAL_STAIRS_UP),
		map<string, short>::value_type(CONST_STAIRS_DOWN, SPECIAL_STAIRS_DOWN),
		map<string, short>::value_type(CONST_CLUB_BOUNCER, SPECIAL_CLUB_BOUNCER),
		map<string, short>::value_type(CONST_CLUB_BOUNCER_SECONDVISIT, SPECIAL_CLUB_BOUNCER_SECONDVISIT)
	};
	getLootString = {
		map<string, string>::value_type(CONST_FINECLOTH,tag_LOOT_FINECLOTH),
		map<string, string>::value_type(CONST_CHEMICAL,tag_LOOT_CHEMICAL),
		map<string, string>::value_type(CONST_PDA,tag_LOOT_PDA),
		map<string, string>::value_type(CONST_LABEQUIPMENT,tag_LOOT_LABEQUIPMENT),
		map<string, string>::value_type(CONST_LAPTOP,tag_LOOT_COMPUTER),
		map<string, string>::value_type(CONST_CHEAPJEWELERY,tag_LOOT_CHEAPJEWELERY),
		map<string, string>::value_type(CONST_SECRETDOCUMENTS,tag_LOOT_SECRETDOCUMENTS),
		map<string, string>::value_type(CONST_CEOPHOTOS,tag_LOOT_CEOPHOTOS),
		map<string, string>::value_type(CONST_INTHQDISK,tag_LOOT_INTHQDISK),
		map<string, string>::value_type(CONST_CORPFILES,tag_LOOT_CORPFILES),
		map<string, string>::value_type(CONST_JUDGEFILES,tag_LOOT_JUDGEFILES),
		map<string, string>::value_type(CONST_RESEARCHFILES,tag_LOOT_RESEARCHFILES),
		map<string, string>::value_type(CONST_PRISONFILES,tag_LOOT_PRISONFILES),
		map<string, string>::value_type(CONST_CABLENEWSFILES,tag_LOOT_CABLENEWSFILES),
		map<string, string>::value_type(CONST_AMRADIOFILES,tag_LOOT_AMRADIOFILES),
		map<string, string>::value_type(CONST_POLICERECORDS,tag_LOOT_POLICERECORDS),
		map<string, string>::value_type(CONST_FINEJEWELERY,tag_LOOT_EXPENSIVEJEWELERY),
		map<string, string>::value_type(CONST_CELLPHONE,tag_LOOT_CELLPHONE),
		map<string, string>::value_type(CONST_MICROPHONE,tag_LOOT_MICROPHONE),
		map<string, string>::value_type(CONST_WATCH,tag_LOOT_WATCH),
		map<string, string>::value_type(CONST_SILVERWARE,tag_LOOT_SILVERWARE),
		map<string, string>::value_type(CONST_TRINKET,tag_LOOT_TRINKET)
	};
	reviewStrings = {
		map<short, string>::value_type(REVIEWMODE_LIBERALS, CONST_X_ACTIVE_LIBERALS),
		map<short, string>::value_type(REVIEWMODE_HOSTAGES,	CONST_CONSERVATIVE_AUTOMATONS_IN_CAPTIVITY),
		map<short, string>::value_type(REVIEWMODE_CLINIC,	CONST_LIBERALS_IN_CLINICS),
		map<short, string>::value_type(REVIEWMODE_JUSTICE,	CONST_LIBERALS_AND_THE_JUSTICE_SYSTEM),
		map<short, string>::value_type(REVIEWMODE_SLEEPERS,	CONST_X_SLEEPERS),
		map<short, string>::value_type(REVIEWMODE_DEAD,	CONST_LIBERAL_MARTYRS_AND_DEAD_BODIES),
		map<short, string>::value_type(REVIEWMODE_AWAY,	CONST_LIBERALS_THAT_ARE_AWAY)
	};
	reviewStringsSecondLine = {
		map<short, string>::value_type(REVIEWMODE_LIBERALS, CONST_SQUAD_ACTIVITY),
		map<short, string>::value_type(REVIEWMODE_HOSTAGES,	CONST_DAYS_IN_CAPTIVITY),
		map<short, string>::value_type(REVIEWMODE_CLINIC,	CONST_MONTHS_LEFT),
		map<short, string>::value_type(REVIEWMODE_JUSTICE,	CONST_PROGNOSIS),
		map<short, string>::value_type(REVIEWMODE_SLEEPERS,	CONST_PROFESSION),
		map<short, string>::value_type(REVIEWMODE_DEAD,	CONST_DAYS_SINCE_PASSING),
		map<short, string>::value_type(REVIEWMODE_AWAY,	CONST_DAYS_UNTIL_RETURN)
	};
	liberalListAndColor = {
	   stringAndColor(WHITE_ON_BLACK,	CONST_RECRUITED),
	   stringAndColor(MAGENTA_ON_BLACK,	CONST_SEDUCED),
	   stringAndColor(WHITE_ON_BLACK,	CONST_X_BACKSLASH),
	   stringAndColor(YELLOW_ON_BLACK,	CONST_ENLIGHTENED),
	   stringAndColor(YELLOW_ON_BLACK_BRIGHT,	TWO_SPACE_OPEN_BRACKET),
	   stringAndColor(WHITE_ON_BLACK,	CONST_ARRESTED),
	   stringAndColor(YELLOW_ON_BLACK_BRIGHT,	CONST_X_CLOSE_BRACKET),
	   stringAndColor(RED_ON_BLACK_BRIGHT,	SPACE_OPEN_BRACKET),
	   stringAndColor(WHITE_ON_BLACK,	CONST_IN_JAIL),
	   stringAndColor(RED_ON_BLACK_BRIGHT,	CONST_X_CLOSE_BRACKET),
	   stringAndColor(BLACK_ON_BLACK_BRIGHT,	SPACE_OPEN_BRACKET),
	   stringAndColor(WHITE_ON_BLACK,	CONST_IN_HIDING),
	   stringAndColor(BLACK_ON_BLACK_BRIGHT,	CONST_X_CLOSE_BRACKET),
	   stringAndColor(BLUE_ON_BLACK_BRIGHT,	SPACE_OPEN_BRACKET),
	   stringAndColor(WHITE_ON_BLACK,	CONST_SLEEPER),
	   stringAndColor(BLUE_ON_BLACK_BRIGHT,	CONST_X_CLOSE_BRACKET)
	};
	getCityDescription = {
		map<short, string>::value_type(SITE_CITY_SEATTLE, CONST_BIRTHPLACE_OF_THE_LCS),
		map<short, string>::value_type(SITE_CITY_LOS_ANGELES, CONST_HOLLYWOOD_AND_TRADE),
		map<short, string>::value_type(SITE_CITY_NEW_YORK, CONST_WALL_STREET_AND_BIG_MEDIA),
		map<short, string>::value_type(SITE_CITY_WASHINGTON_DC, CONST_THE_NATION_S_CAPITAL),
		map<short, string>::value_type(SITE_CITY_CHICAGO, CONST_MAFIA_HEADQUARTERS),
		map<short, string>::value_type(SITE_CITY_DETROIT, CONST_MURDER_CAPITAL_OF_AMERICA),
		map<short, string>::value_type(SITE_CITY_ATLANTA, CONST_THE_PRIDE_OF_THE_SOUTH),
		map<short, string>::value_type(SITE_CITY_MIAMI, CONST_A_TROPICAL_PARADISE)
	};
	getSiteName = {
		map<short, vector<string> >::value_type(SITE_CITY_SEATTLE,{ tag_Seattle, tag_SEA }),
		map<short, vector<string> >::value_type(SITE_CITY_LOS_ANGELES,{ CONST_LOS_ANGELES, tag_LA }),
		map<short, vector<string> >::value_type(SITE_CITY_NEW_YORK,{ CONST_NEW_YORK, tag_NYC }),
		map<short, vector<string> >::value_type(SITE_CITY_CHICAGO,{ tag_Chicago, tag_CHI }),
		map<short, vector<string> >::value_type(SITE_CITY_DETROIT,{ tag_Detroit, tag_DET }),
		map<short, vector<string> >::value_type(SITE_CITY_ATLANTA,{ tag_Atlanta, tag_ATL }),
		map<short, vector<string> >::value_type(SITE_CITY_MIAMI,{ tag_Miami, tag_MI }),
		map<short, vector<string> >::value_type(SITE_CITY_WASHINGTON_DC,{ CONST_WASHINGTON_DC, tag_DC }),
		map<short, vector<string> >::value_type(SITE_DOWNTOWN,{ tag_Downtown, tag_Downtown }),
		map<short, vector<string> >::value_type(SITE_UDISTRICT,{ tag_University_District, tag_u_District }),
		map<short, vector<string> >::value_type(SITE_COMMERCIAL,{ tag_Shopping, tag_Shopping }),
		map<short, vector<string> >::value_type(SITE_INDUSTRIAL,{ tag_Industrial_District, tag_i_District }),
		map<short, vector<string> >::value_type(SITE_OUTOFTOWN,{ tag_City_Outskirts, tag_Outskirts }),
		map<short, vector<string> >::value_type(SITE_TRAVEL,{ tag_Travel, tag_Travel }),
	};
	getActivityString = {
		map<short, string>::value_type(ACTIVITY_RECRUITING,	CONST_X_RECRUITING),
		map<short, string>::value_type(ACTIVITY_REPAIR_ARMOR,	CONST_REPAIRING_CLOTHING),
		map<short, string>::value_type(ACTIVITY_WHEELCHAIR,	CONST_PROCURING_A_WHEELCHAIR),
		map<short, string>::value_type(ACTIVITY_STEALCARS,	CONST_STEALING_A_CAR),
		map<short, string>::value_type(ACTIVITY_POLLS,	CONST_GATHERING_OPINION_INFO),
		map<short, string>::value_type(ACTIVITY_TROUBLE,	CONST_CAUSING_TROUBLE),
		map<short, string>::value_type(ACTIVITY_PROSTITUTION,	CONST_PROSTITUTING),
		map<short, string>::value_type(ACTIVITY_COMMUNITYSERVICE,	CONST_VOLUNTEERING),
		map<short, string>::value_type(ACTIVITY_GRAFFITI,	CONST_MAKING_GRAFFITI),
		map<short, string>::value_type(ACTIVITY_CCFRAUD,	CONST_CREDIT_CARD_FRAUD),
		map<short, string>::value_type(ACTIVITY_DOS_RACKET,	CONST_EXTORTING_WEBSITES),
		map<short, string>::value_type(ACTIVITY_DOS_ATTACKS,	CONST_ATTACKING_WEBSITES),
		map<short, string>::value_type(ACTIVITY_HACKING,	CONST_HACKING_NETWORKS),
		map<short, string>::value_type(ACTIVITY_SELL_TSHIRTS,	CONST_SELLING_T_SHIRTS),
		map<short, string>::value_type(ACTIVITY_SELL_ART,	CONST_SELLING_ART),
		map<short, string>::value_type(ACTIVITY_TEACH_POLITICS,	CONST_TEACHING_POLITICS),
		map<short, string>::value_type(ACTIVITY_TEACH_FIGHTING,	CONST_TEACHING_FIGHTING),
		map<short, string>::value_type(ACTIVITY_TEACH_COVERT,	CONST_TEACHING_COVERT_OPS),
		map<short, string>::value_type(ACTIVITY_SELL_MUSIC,	CONST_SELLING_MUSIC),
		map<short, string>::value_type(ACTIVITY_BURY,	CONST_DISPOSING_OF_BODIES),
		map<short, string>::value_type(ACTIVITY_DONATIONS,	CONST_SOLICITING_DONATIONS),
		map<short, string>::value_type(ACTIVITY_SELL_DRUGS,	CONST_SELLING_BROWNIES),
		map<short, string>::value_type(ACTIVITY_HEAL,	CONST_TENDING_TO_INJURIES),
		map<short, string>::value_type(ACTIVITY_NONE,	CONST_LAYING_LOW),
		map<short, string>::value_type(ACTIVITY_WRITE_LETTERS,	CONST_WRITING_LETTERS),
		map<short, string>::value_type(ACTIVITY_WRITE_GUARDIAN,	CONST_WRITING_NEWS),
		map<short, string>::value_type(ACTIVITY_CLINIC,	CONST_GOING_TO_FREE_CLINIC),
		map<short, string>::value_type(ACTIVITY_STUDY_DEBATING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_MARTIAL_ARTS,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_DRIVING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_PSYCHOLOGY,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_FIRST_AID,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_LAW,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_DISGUISE,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_SCIENCE,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_BUSINESS,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_GYMNASTICS,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_ART,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_MUSIC,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_TEACHING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_WRITING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_LOCKSMITHING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_COMPUTERS,	CONST_ATTENDING_CLASSES),
		//map<short, string>::value_type( ACTIVITY_STUDY_COOKING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_FENCING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_WEAVING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_RELIGION,	CONST_ATTENDING_CLASSES),
		//map<short, string>::value_type(ACTIVITY_STUDY_MAGIC,	CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_CLUB,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_STREETSENSE,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_THROWING,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_STEALTH,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_STUDY_SEDUCTION,CONST_ATTENDING_CLASSES),
		map<short, string>::value_type(ACTIVITY_SLEEPER_LIBERAL,	CONST_PROMOTING_LIBERALISM),
		map<short, string>::value_type(ACTIVITY_SLEEPER_CONSERVATIVE,	CONST_SPOUTING_CONSERVATISM),
		map<short, string>::value_type(ACTIVITY_SLEEPER_SPY,	CONST_SNOOPING_AROUND),
		map<short, string>::value_type(ACTIVITY_SLEEPER_RECRUIT,	CONST_RECRUITING_SLEEPERS),
		map<short, string>::value_type(ACTIVITY_SLEEPER_JOINLCS,	CONST_QUITTING_JOB),
		map<short, string>::value_type(ACTIVITY_SLEEPER_SCANDAL,	CONST_CREATING_A_SCANDAL),
		map<short, string>::value_type(ACTIVITY_SLEEPER_EMBEZZLE,	CONST_EMBEZZLING_FUNDS),
		map<short, string>::value_type(ACTIVITY_SLEEPER_STEAL,	CONST_STEALING_EQUIPMENT),
		map<short, string>::value_type(ACTIVITY_AUGMENT,	CONST_AUGMENTING_LIBERAL),
	};
	getViewString = {
		map<short, vector<string> >::value_type(VIEW_STALIN,{ CONST_STALINISM, CONST_STALINISM }) ,
		map<short, vector<string> >::value_type(VIEW_MOOD,{ CONST_PUBLIC_MOOD, CONST_X_PUBLIC_MOOD }) ,
		map<short, vector<string> >::value_type(VIEW_GAY,{ CONST_LGBTQ_RIGHTS, CONST_X_LGBTQ_RIGHTS }) ,
		map<short, vector<string> >::value_type(VIEW_DEATHPENALTY,{ CONST_THE_DEATH_PENALTY, CONST_BARBARIC_EXECUTIONS }) ,
		map<short, vector<string> >::value_type(VIEW_TAXES,{ CONST_TAXES, CONST_THE_TAX_STRUCTURE }) ,
		map<short, vector<string> >::value_type(VIEW_NUCLEARPOWER,{ CONST_NUCLEAR_POWER, CONST_NUCLEAR_MELTDOWNS }) ,
		map<short, vector<string> >::value_type(VIEW_ANIMALRESEARCH,{ CONST_ANIMAL_CRUELTY, CONST_X_ANIMAL_CRUELTY }) ,
		map<short, vector<string> >::value_type(VIEW_POLICEBEHAVIOR,{ CONST_COPS, CONST_POLICE_MISCONDUCT }) ,
		map<short, vector<string> >::value_type(VIEW_TORTURE,{ CONST_TORTURE, CONST_X_TORTURE }) ,
		map<short, vector<string> >::value_type(VIEW_PRISONS,{ CONST_THE_PRISON_SYSTEM, CONST_X_THE_PRISON_SYSTEM }) ,
		map<short, vector<string> >::value_type(VIEW_INTELLIGENCE,{ CONST_PRIVACY, CONST_PRIVACY_RIGHTS }) ,
		map<short, vector<string> >::value_type(VIEW_FREESPEECH,{ CONST_FREE_SPEECH, CONST_FREEDOM_OF_SPEECH }) ,
		map<short, vector<string> >::value_type(VIEW_GENETICS,{ CONST_GENETIC_RESEARCH, CONST_DANGEROUS_GMOS }) ,
		map<short, vector<string> >::value_type(VIEW_JUSTICES,{ CONST_JUDGES, CONST_THE_JUDICIARY }) ,
		map<short, vector<string> >::value_type(VIEW_GUNCONTROL,{ CONST_GUN_CONTROL, CONST_MASS_SHOOTINGS }) ,
		map<short, vector<string> >::value_type(VIEW_SWEATSHOPS,{ CONST_LABOR_UNIONS, CONST_WORKERS_RIGHTS }) ,
		map<short, vector<string> >::value_type(VIEW_POLLUTION,{ CONST_POLLUTION, CONST_X_POLLUTION }) ,
		map<short, vector<string> >::value_type(VIEW_CORPORATECULTURE,{ CONST_CORPORATIONS, CONST_X_CORPORATE_CORRUPTION }) ,
		map<short, vector<string> >::value_type(VIEW_CEOSALARY,{ CONST_CEO_COMPENSATION, CONST_X_CEO_COMPENSATION }) ,
		map<short, vector<string> >::value_type(VIEW_WOMEN,{ CONST_WOMEN_S_RIGHTS, CONST_GENDER_EQUALITY }) ,
		map<short, vector<string> >::value_type(VIEW_CIVILRIGHTS,{ CONST_X_CIVIL_RIGHTS, CONST_RACIAL_EQUALITY }) ,
		map<short, vector<string> >::value_type(VIEW_DRUGS,{ CONST_DRUGS, CONST_OPPRESSIVE_DRUG_LAWS }) ,
		map<short, vector<string> >::value_type(VIEW_IMMIGRATION,{ CONST_IMMIGRATION, CONST_X_IMMIGRANT_RIGHTS }) ,
		map<short, vector<string> >::value_type(VIEW_MILITARY,{ CONST_THE_MILITARY, CONST_MILITARY_SPENDING }) ,
		map<short, vector<string> >::value_type(VIEW_AMRADIO,{ CONST_AM_RADIO, CONST_AM_RADIO_PROPAGANDA }) ,
		map<short, vector<string> >::value_type(VIEW_CABLENEWS,{ CONST_CABLE_NEWS, CONST_CABLE_NEWS_LIES }) ,
		//map<short, vector<string> >::value_type( VIEW_POLITICALVIOLENCE, { CONST_POLITICAL_VIOLENCE, CONST_THE_NEED_FOR_ACTION } ) ,
		map<short, vector<string> >::value_type(VIEW_LIBERALCRIMESQUAD,{ CONST_THE_LCS, CONST_WHO_WE_ARE }) ,
		map<short, vector<string> >::value_type(VIEW_LIBERALCRIMESQUADPOS,{ CONST_THE_LCS, CONST_WHY_WE_ROCK }) ,
		map<short, vector<string> >::value_type(VIEW_CONSERVATIVECRIMESQUAD,{ CONST_THE_CCS, CONST_X_THE_CCS_TERRORISTS })
	};
	getLawString = {
		map<short, string>::value_type(LAW_ABORTION, CONST_ABORTION_RIGHTS),
		map<short, string>::value_type(LAW_ANIMALRESEARCH, CONST_ANIMAL_RIGHTS), // a.k.a. CONST_ANIMAL_RESEARCH
		map<short, string>::value_type(LAW_POLICEBEHAVIOR, CONST_POLICE_REGULATION), // a.k.a. CONST_POLICE_BEHAVIOR
		map<short, string>::value_type(LAW_PRIVACY, CONST_PRIVACY_RIGHTS), // a.k.a. CONST_X_PRIVACY
		map<short, string>::value_type(LAW_DEATHPENALTY, CONST_DEATH_PENALTY), // a.k.a. CONST_CAPITAL_PUNISHMENT
		map<short, string>::value_type(LAW_NUCLEARPOWER, CONST_X_NUCLEAR_POWER),
		map<short, string>::value_type(LAW_POLLUTION, CONST_X_POLLUTION),
		map<short, string>::value_type(LAW_LABOR, CONST_LABOR_LAWS), // a.k.a. CONST_WORKERS_RIGHTS
		map<short, string>::value_type(LAW_GAY, CONST_GAY_RIGHTS), // a.k.a. CONST_HOMOSEXUAL_RIGHTS
		map<short, string>::value_type(LAW_CORPORATE, CONST_CORPORATE_LAW), // a.k.a. CONST_CORPORATE_ETHICS
		map<short, string>::value_type(LAW_FREESPEECH, CONST_X_FREE_SPEECH), // a.k.a. CONST_FREEDOM_OF_SPEECH
		map<short, string>::value_type(LAW_FLAGBURNING, CONST_FLAG_BURNING),
		map<short, string>::value_type(LAW_GUNCONTROL, CONST_X_GUN_CONTROL),
		map<short, string>::value_type(LAW_TAX, CONST_TAX_STRUCTURE), // a.k.a. CONST_TAX_LAW
		map<short, string>::value_type(LAW_WOMEN, CONST_X_WOMENS_RIGHTS),
		map<short, string>::value_type(LAW_CIVILRIGHTS, CONST_CC_CIVIL_RIGHTS),
		map<short, string>::value_type(LAW_DRUGS, CONST_DRUG_LAWS), // a.k.a. CONST_DRUG_LAW
		map<short, string>::value_type(LAW_IMMIGRATION, CONST_X_IMMIGRATION),
		map<short, string>::value_type(LAW_ELECTIONS, CONST_ELECTION_REFORM),
		map<short, string>::value_type(LAW_MILITARY, CONST_MILITARY_SPENDING),
		map<short, string>::value_type(LAW_PRISONS, CONST_PRISON_REGULATION),
		map<short, string>::value_type(LAW_TORTURE, CONST_HUMAN_RIGHTS)
	};
	getLawFlagString = {
		map<short, string>::value_type(LAWFLAG_TREASON,  CONST_TREASON),
		map<short, string>::value_type(LAWFLAG_TERRORISM,  CONST_TERRORISM),
		map<short, string>::value_type(LAWFLAG_MURDER,  CONST_MURDER),
		map<short, string>::value_type(LAWFLAG_KIDNAPPING,  CONST_KIDNAPPING),
		map<short, string>::value_type(LAWFLAG_BANKROBBERY,  CONST_BANK_ROBBERY),
		map<short, string>::value_type(LAWFLAG_ARSON,  CONST_ARSON),
		map<short, string>::value_type(LAWFLAG_SPEECH,  CONST_HARMFUL_SPEECH),
		map<short, string>::value_type(LAWFLAG_BROWNIES,  CONST_DRUG_DEALING),
		map<short, string>::value_type(LAWFLAG_ESCAPED,  CONST_ESCAPING_PRISON),
		map<short, string>::value_type(LAWFLAG_HELPESCAPE,  CONST_RELEASING_PRISONERS),
		map<short, string>::value_type(LAWFLAG_JURY,  CONST_JURY_TAMPERING),
		map<short, string>::value_type(LAWFLAG_RACKETEERING,  CONST_RACKETEERING),
		map<short, string>::value_type(LAWFLAG_EXTORTION,  CONST_EXTORTION),
		map<short, string>::value_type(LAWFLAG_ARMEDASSAULT,  CONST_ARMED_ASSAULT),
		map<short, string>::value_type(LAWFLAG_ASSAULT,  CONST_ASSAULT),
		map<short, string>::value_type(LAWFLAG_CARTHEFT,  CONST_GRAND_THEFT_AUTO),
		map<short, string>::value_type(LAWFLAG_CCFRAUD,  CONST_X_CREDIT_CARD_FRAUD),
		map<short, string>::value_type(LAWFLAG_THEFT,  CONST_THEFT),
		map<short, string>::value_type(LAWFLAG_PROSTITUTION,  CONST_PROSTITUTION),
		//map<short, string>::value_type( LAWFLAG_GUNUSE,  CONST_FIRING_ILLEGAL_WEAPONS),
		//map<short, string>::value_type( LAWFLAG_GUNCARRY,  CONST_CARRYING_ILLEGAL_WEAPONS),
		map<short, string>::value_type(LAWFLAG_COMMERCE,  CONST_ELECTRONIC_SABOTAGE),
		map<short, string>::value_type(LAWFLAG_INFORMATION,  CONST_HACKING),
		map<short, string>::value_type(LAWFLAG_BURIAL,  CONST_UNLAWFUL_BURIAL),
		map<short, string>::value_type(LAWFLAG_BREAKING,  CONST_BREAKING_AND_ENTERING),
		map<short, string>::value_type(LAWFLAG_VANDALISM,  CONST_VANDALISM),
		map<short, string>::value_type(LAWFLAG_RESIST,  CONST_RESISTING_ARREST),
		map<short, string>::value_type(LAWFLAG_DISTURBANCE,  CONST_DISTURBING_THE_PEACE),
		map<short, string>::value_type(LAWFLAG_PUBLICNUDITY,  CONST_PUBLIC_NUDITY),
		map<short, string>::value_type(LAWFLAG_LOITERING,  CONST_LOITERING)
	};
	getLawFlagStringFull = {
		map<short, map<short, string> >::value_type(LAWFLAG_BURNFLAG,
		{
			map<short, string>::value_type(ALIGN_ARCHCONSERVATIVE ,	CONST_FLAG_MURDER),
			map<short, string>::value_type(ALIGN_CONSERVATIVE,CONST_X_FLAG_BURNING),
			map<short, string>::value_type(ALIGN_MODERATE,CONST_X_FLAG_BURNING),
			map<short, string>::value_type(ALIGN_LIBERAL,CONST_X_FLAG_BURNING),
			map<short, string>::value_type(ALIGN_ELITELIBERAL,CONST_X_FLAG_BURNING),
			map<short, string>::value_type(ALIGN_STALINIST ,CONST_X_FLAG_BURNING)
		}
			),
		map<short, map<short, string> >::value_type(LAWFLAG_HIREILLEGAL,{
			map<short, string>::value_type(ALIGN_ARCHCONSERVATIVE,CONST_HIRING_ILLEGAL_ALIENS),
			map<short, string>::value_type(ALIGN_CONSERVATIVE,CONST_HIRING_ILLEGAL_ALIENS),
			map<short, string>::value_type(ALIGN_MODERATE,CONST_HIRING_ILLEGAL_ALIENS),
			map<short, string>::value_type(ALIGN_LIBERAL,CONST_HIRING_UNDOCUMENTED_WORKERS),
			map<short, string>::value_type(ALIGN_ELITELIBERAL,CONST_HIRING_UNDOCUMENTED_WORKERS)
		}
			)
	};
	enumToCreature = {
		map<short, string>::value_type(CREATURE_BOUNCER,	CONST_CREATURE_BOUNCER),
		map<short, string>::value_type(CREATURE_SECURITYGUARD,	CONST_CREATURE_SECURITYGUARD),
		map<short, string>::value_type(CREATURE_SCIENTIST_LABTECH,	CONST_CREATURE_SCIENTIST_LABTECH),
		map<short, string>::value_type(CREATURE_SCIENTIST_EMINENT,	CONST_CREATURE_SCIENTIST_EMINENT),
		map<short, string>::value_type(CREATURE_CORPORATE_MANAGER,	CONST_CREATURE_CORPORATE_MANAGER),
		map<short, string>::value_type(CREATURE_CORPORATE_CEO,	CONST_CREATURE_CORPORATE_CEO),
		map<short, string>::value_type(CREATURE_WORKER_SERVANT,	CONST_CREATURE_WORKER_SERVANT),
		map<short, string>::value_type(CREATURE_WORKER_JANITOR,	CONST_CREATURE_WORKER_JANITOR),
		map<short, string>::value_type(CREATURE_WORKER_SWEATSHOP,	CONST_CREATURE_WORKER_SWEATSHOP),
		map<short, string>::value_type(CREATURE_WORKER_FACTORY_NONUNION,	CONST_CREATURE_WORKER_FACTORY_NONUNION),
		map<short, string>::value_type(CREATURE_WORKER_FACTORY_CHILD,	CONST_CREATURE_WORKER_FACTORY_CHILD),
		map<short, string>::value_type(CREATURE_WORKER_SECRETARY,	CONST_CREATURE_WORKER_SECRETARY),
		map<short, string>::value_type(CREATURE_WORKER_FACTORY_UNION,	CONST_CREATURE_WORKER_FACTORY_UNION),
		map<short, string>::value_type(CREATURE_LANDLORD,	CONST_CREATURE_LANDLORD),
		map<short, string>::value_type(CREATURE_TEENAGER,	CONST_CREATURE_TEENAGER),
		map<short, string>::value_type(CREATURE_COP,	CONST_CREATURE_COP),
		map<short, string>::value_type(CREATURE_SWAT,	CONST_CREATURE_SWAT),
		map<short, string>::value_type(CREATURE_DEATHSQUAD,	CONST_CREATURE_DEATHSQUAD),
		map<short, string>::value_type(CREATURE_FIREFIGHTER,	CONST_CREATURE_FIREFIGHTER),
		map<short, string>::value_type(CREATURE_EDUCATOR,	CONST_CREATURE_EDUCATOR),
		map<short, string>::value_type(CREATURE_GANGUNIT,	CONST_CREATURE_GANGUNIT),
		map<short, string>::value_type(CREATURE_JUDGE_LIBERAL,	CONST_CREATURE_JUDGE_LIBERAL),
		map<short, string>::value_type(CREATURE_JUDGE_CONSERVATIVE,	CONST_CREATURE_JUDGE_CONSERVATIVE),
		map<short, string>::value_type(CREATURE_AGENT,	CONST_CREATURE_AGENT),
		map<short, string>::value_type(CREATURE_RADIOPERSONALITY,	CONST_CREATURE_RADIOPERSONALITY),
		map<short, string>::value_type(CREATURE_NEWSANCHOR,	CONST_CREATURE_NEWSANCHOR),
		map<short, string>::value_type(CREATURE_GENETIC,	CONST_CREATURE_GENETIC),
		map<short, string>::value_type(CREATURE_GUARDDOG,	CONST_CREATURE_GUARDDOG),
		map<short, string>::value_type(CREATURE_PRISONER,	CONST_CREATURE_PRISONER),
		map<short, string>::value_type(CREATURE_JUROR,	CONST_CREATURE_JUROR),
		map<short, string>::value_type(CREATURE_LAWYER,	CONST_CREATURE_LAWYER),
		map<short, string>::value_type(CREATURE_SEWERWORKER,	CONST_CREATURE_SEWERWORKER),
		map<short, string>::value_type(CREATURE_COLLEGESTUDENT,	CONST_CREATURE_COLLEGESTUDENT),
		map<short, string>::value_type(CREATURE_MUSICIAN,	CONST_CREATURE_MUSICIAN),
		map<short, string>::value_type(CREATURE_MATHEMATICIAN,	CONST_CREATURE_MATHEMATICIAN),
		map<short, string>::value_type(CREATURE_TEACHER,	CONST_CREATURE_TEACHER),
		map<short, string>::value_type(CREATURE_HSDROPOUT,	CONST_CREATURE_HSDROPOUT),
		map<short, string>::value_type(CREATURE_BUM,	CONST_CREATURE_BUM),
		map<short, string>::value_type(CREATURE_GANGMEMBER,	CONST_CREATURE_GANGMEMBER),
		map<short, string>::value_type(CREATURE_CRACKHEAD,	CONST_CREATURE_CRACKHEAD),
		map<short, string>::value_type(CREATURE_PRIEST,	CONST_CREATURE_PRIEST),
		map<short, string>::value_type(CREATURE_ENGINEER,	CONST_CREATURE_ENGINEER),
		map<short, string>::value_type(CREATURE_FASTFOODWORKER,	CONST_CREATURE_FASTFOODWORKER),
		map<short, string>::value_type(CREATURE_BAKER,	CONST_CREATURE_BAKER),
		map<short, string>::value_type(CREATURE_BARISTA,	CONST_CREATURE_BARISTA),
		map<short, string>::value_type(CREATURE_BARTENDER,	CONST_CREATURE_BARTENDER),
		map<short, string>::value_type(CREATURE_TELEMARKETER,	CONST_CREATURE_TELEMARKETER),
		map<short, string>::value_type(CREATURE_CARSALESMAN,	CONST_CREATURE_CARSALESMAN),
		map<short, string>::value_type(CREATURE_OFFICEWORKER,	CONST_CREATURE_OFFICEWORKER),
		map<short, string>::value_type(CREATURE_FOOTBALLCOACH,	CONST_CREATURE_FOOTBALLCOACH),
		map<short, string>::value_type(CREATURE_PROSTITUTE,	CONST_CREATURE_PROSTITUTE),
		map<short, string>::value_type(CREATURE_MAILMAN,	CONST_CREATURE_MAILMAN),
		map<short, string>::value_type(CREATURE_GARBAGEMAN,	CONST_CREATURE_GARBAGEMAN),
		map<short, string>::value_type(CREATURE_PLUMBER,	CONST_CREATURE_PLUMBER),
		map<short, string>::value_type(CREATURE_CHEF,	CONST_CREATURE_CHEF),
		map<short, string>::value_type(CREATURE_CONSTRUCTIONWORKER,	CONST_CREATURE_CONSTRUCTIONWORKER),
		map<short, string>::value_type(CREATURE_AMATEURMAGICIAN,	CONST_CREATURE_AMATEURMAGICIAN),
		map<short, string>::value_type(CREATURE_TANK,	CONST_CREATURE_TANK),
		map<short, string>::value_type(CREATURE_MERC,	CONST_CREATURE_MERC),
		map<short, string>::value_type(CREATURE_HICK,	CONST_CREATURE_HICK),
		map<short, string>::value_type(CREATURE_SOLDIER,	CONST_CREATURE_SOLDIER),
		map<short, string>::value_type(CREATURE_VETERAN,	CONST_CREATURE_VETERAN),
		map<short, string>::value_type(CREATURE_HARDENED_VETERAN,	CONST_CREATURE_HARDENED_VETERAN),
		map<short, string>::value_type(CREATURE_PRISONGUARD,	CONST_CREATURE_PRISONGUARD),
		map<short, string>::value_type(CREATURE_HIPPIE,	CONST_CREATURE_HIPPIE),
		map<short, string>::value_type(CREATURE_CRITIC_ART,	CONST_CREATURE_CRITIC_ART),
		map<short, string>::value_type(CREATURE_CRITIC_MUSIC,	CONST_CREATURE_CRITIC_MUSIC),
		map<short, string>::value_type(CREATURE_SOCIALITE,	CONST_CREATURE_SOCIALITE),
		map<short, string>::value_type(CREATURE_PROGRAMMER,	CONST_CREATURE_PROGRAMMER),
		map<short, string>::value_type(CREATURE_RETIREE,	CONST_CREATURE_RETIREE),
		map<short, string>::value_type(CREATURE_PAINTER,	CONST_CREATURE_PAINTER),
		map<short, string>::value_type(CREATURE_SCULPTOR,	CONST_CREATURE_SCULPTOR),
		map<short, string>::value_type(CREATURE_AUTHOR,	CONST_CREATURE_AUTHOR),
		map<short, string>::value_type(CREATURE_JOURNALIST,	CONST_CREATURE_JOURNALIST),
		map<short, string>::value_type(CREATURE_DANCER,	CONST_CREATURE_DANCER),
		map<short, string>::value_type(CREATURE_PHOTOGRAPHER,	CONST_CREATURE_PHOTOGRAPHER),
		map<short, string>::value_type(CREATURE_CAMERAMAN,	CONST_CREATURE_CAMERAMAN),
		map<short, string>::value_type(CREATURE_HAIRSTYLIST,	CONST_CREATURE_HAIRSTYLIST),
		map<short, string>::value_type(CREATURE_FASHIONDESIGNER,	CONST_CREATURE_FASHIONDESIGNER),
		map<short, string>::value_type(CREATURE_CLERK,	CONST_CREATURE_CLERK),
		map<short, string>::value_type(CREATURE_THIEF,	CONST_CREATURE_THIEF),
		map<short, string>::value_type(CREATURE_ACTOR,	CONST_CREATURE_ACTOR),
		map<short, string>::value_type(CREATURE_YOGAINSTRUCTOR,	CONST_CREATURE_YOGAINSTRUCTOR),
		map<short, string>::value_type(CREATURE_MARTIALARTIST,	CONST_CREATURE_MARTIALARTIST),
		map<short, string>::value_type(CREATURE_ATHLETE,	CONST_CREATURE_ATHLETE),
		map<short, string>::value_type(CREATURE_BIKER,	CONST_CREATURE_BIKER),
		map<short, string>::value_type(CREATURE_TRUCKER,	CONST_CREATURE_TRUCKER),
		map<short, string>::value_type(CREATURE_TAXIDRIVER,	CONST_CREATURE_TAXIDRIVER),
		map<short, string>::value_type(CREATURE_NUN,	CONST_CREATURE_NUN),
		map<short, string>::value_type(CREATURE_MUTANT,	CONST_CREATURE_MUTANT),
		map<short, string>::value_type(CREATURE_DOCTOR,	CONST_CREATURE_DOCTOR),
		map<short, string>::value_type(CREATURE_NURSE,	CONST_CREATURE_NURSE),
		map<short, string>::value_type(CREATURE_CCS_VIGILANTE,	CONST_CREATURE_CCS_VIGILANTE),
		map<short, string>::value_type(CREATURE_CCS_ARCHCONSERVATIVE,	CONST_CREATURE_CCS_ARCHCONSERVATIVE),
		map<short, string>::value_type(CREATURE_POLITICALACTIVIST,	CONST_CREATURE_POLITICALACTIVIST),
		map<short, string>::value_type(CREATURE_CCS_MOLOTOV,	CONST_CREATURE_CCS_MOLOTOV),
		map<short, string>::value_type(CREATURE_CCS_SNIPER,	CONST_CREATURE_CCS_SNIPER),
		map<short, string>::value_type(CREATURE_PSYCHOLOGIST,	CONST_CREATURE_PSYCHOLOGIST),
		map<short, string>::value_type(CREATURE_LOCKSMITH,	CONST_CREATURE_LOCKSMITH),
		map<short, string>::value_type(CREATURE_MILITARYPOLICE,	CONST_CREATURE_MILITARYPOLICE),
		map<short, string>::value_type(CREATURE_SEAL,	CONST_CREATURE_SEAL),
		map<short, string>::value_type(CREATURE_MILITARYOFFICER,	CONST_CREATURE_MILITARYOFFICER),
		map<short, string>::value_type(CREATURE_BANK_TELLER,	CONST_CREATURE_BANK_TELLER),
		map<short, string>::value_type(CREATURE_BANK_MANAGER,	CONST_CREATURE_BANK_MANAGER),
		map<short, string>::value_type(CREATURE_SECRET_SERVICE,	CONST_CREATURE_SECRET_SERVICE),
		map<short, string>::value_type(CREATURE_POLITICIAN,	CONST_CREATURE_POLITICIAN)
	};
	getSkillEnumFromString = {
		map<string, short>::value_type(CONST_SKILL_ART, SKILL_ART),
		map<string, short>::value_type(CONST_SKILL_AXE, SKILL_AXE),
		map<string, short>::value_type(CONST_SKILL_BUSINESS, SKILL_BUSINESS),
		map<string, short>::value_type(CONST_SKILL_CLUB, SKILL_CLUB),
		map<string, short>::value_type(CONST_SKILL_COMPUTERS, SKILL_COMPUTERS),
		map<string, short>::value_type(CONST_SKILL_DISGUISE, SKILL_DISGUISE),
		map<string, short>::value_type(CONST_SKILL_DODGE, SKILL_DODGE),
		map<string, short>::value_type(CONST_SKILL_DRIVING, SKILL_DRIVING),
		map<string, short>::value_type(CONST_SKILL_FIRSTAID, SKILL_FIRSTAID),
		map<string, short>::value_type(CONST_SKILL_HEAVYWEAPONS, SKILL_HEAVYWEAPONS),
		map<string, short>::value_type(CONST_SKILL_KNIFE, SKILL_KNIFE),
		map<string, short>::value_type(CONST_SKILL_LAW, SKILL_LAW),
		map<string, short>::value_type(CONST_SKILL_HANDTOHAND, SKILL_HANDTOHAND),
		map<string, short>::value_type(CONST_SKILL_MUSIC, SKILL_MUSIC),
		map<string, short>::value_type(CONST_SKILL_PERSUASION, SKILL_PERSUASION),
		map<string, short>::value_type(CONST_SKILL_PISTOL, SKILL_PISTOL),
		map<string, short>::value_type(CONST_SKILL_PSYCHOLOGY, SKILL_PSYCHOLOGY),
		map<string, short>::value_type(CONST_SKILL_RELIGION, SKILL_RELIGION),
		map<string, short>::value_type(CONST_SKILL_RIFLE, SKILL_RIFLE),
		map<string, short>::value_type(CONST_SKILL_SCIENCE, SKILL_SCIENCE),
		map<string, short>::value_type(CONST_SKILL_SECURITY, SKILL_SECURITY),
		map<string, short>::value_type(CONST_SKILL_SEDUCTION, SKILL_SEDUCTION),
		map<string, short>::value_type(CONST_SKILL_SHOTGUN, SKILL_SHOTGUN),
		map<string, short>::value_type(CONST_SKILL_SMG, SKILL_SMG),
		map<string, short>::value_type(CONST_SKILL_STEALTH, SKILL_STEALTH),
		map<string, short>::value_type(CONST_SKILL_STREETSENSE, SKILL_STREETSENSE),
		map<string, short>::value_type(CONST_SKILL_SWORD, SKILL_SWORD),
		map<string, short>::value_type(CONST_SKILL_TAILORING, SKILL_TAILORING),
		map<string, short>::value_type(CONST_SKILL_TEACHING, SKILL_TEACHING),
		map<string, short>::value_type(CONST_SKILL_THROWING, SKILL_THROWING),
		map<string, short>::value_type(CONST_SKILL_WRITING, SKILL_WRITING)
	};
	getAttributeEnumFromString = {
		map<string, short>::value_type(CONST_ATTRIBUTE_HEART, ATTRIBUTE_HEART),
		map<string, short>::value_type(CONST_ATTRIBUTE_WISDOM, ATTRIBUTE_WISDOM),
		map<string, short>::value_type(CONST_ATTRIBUTE_INTELLIGENCE, ATTRIBUTE_INTELLIGENCE),
		map<string, short>::value_type(CONST_ATTRIBUTE_AGILITY, ATTRIBUTE_AGILITY),
		map<string, short>::value_type(CONST_ATTRIBUTE_STRENGTH, ATTRIBUTE_STRENGTH),
		map<string, short>::value_type(CONST_ATTRIBUTE_HEALTH, ATTRIBUTE_HEALTH),
		map<string, short>::value_type(CONST_ATTRIBUTE_CHARISMA, ATTRIBUTE_CHARISMA)
	};
	getCreatureEnumFromString = {
		map<string, short>::value_type(CONST_CREATURE_BOUNCER, CREATURE_BOUNCER),
		map<string, short>::value_type(CONST_CREATURE_SECURITYGUARD, CREATURE_SECURITYGUARD),
		map<string, short>::value_type(CONST_CREATURE_SCIENTIST_LABTECH, CREATURE_SCIENTIST_LABTECH),
		map<string, short>::value_type(CONST_CREATURE_SCIENTIST_EMINENT, CREATURE_SCIENTIST_EMINENT),
		map<string, short>::value_type(CONST_CREATURE_CORPORATE_MANAGER, CREATURE_CORPORATE_MANAGER),
		map<string, short>::value_type(CONST_CREATURE_CORPORATE_CEO, CREATURE_CORPORATE_CEO),
		map<string, short>::value_type(CONST_CREATURE_WORKER_SERVANT, CREATURE_WORKER_SERVANT),
		map<string, short>::value_type(CONST_CREATURE_WORKER_JANITOR, CREATURE_WORKER_JANITOR),
		map<string, short>::value_type(CONST_CREATURE_WORKER_SWEATSHOP, CREATURE_WORKER_SWEATSHOP),
		map<string, short>::value_type(CONST_CREATURE_WORKER_FACTORY_NONUNION, CREATURE_WORKER_FACTORY_NONUNION),
		map<string, short>::value_type(CONST_CREATURE_WORKER_FACTORY_CHILD, CREATURE_WORKER_FACTORY_CHILD),
		map<string, short>::value_type(CONST_CREATURE_WORKER_SECRETARY, CREATURE_WORKER_SECRETARY),
		map<string, short>::value_type(CONST_CREATURE_WORKER_FACTORY_UNION, CREATURE_WORKER_FACTORY_UNION),
		map<string, short>::value_type(CONST_CREATURE_LANDLORD, CREATURE_LANDLORD),
		map<string, short>::value_type(CONST_CREATURE_TEENAGER, CREATURE_TEENAGER),
		map<string, short>::value_type(CONST_CREATURE_COP, CREATURE_COP),
		map<string, short>::value_type(CONST_CREATURE_SWAT, CREATURE_SWAT),
		map<string, short>::value_type(CONST_CREATURE_DEATHSQUAD, CREATURE_DEATHSQUAD),
		map<string, short>::value_type(CONST_CREATURE_FIREFIGHTER, CREATURE_FIREFIGHTER),
		map<string, short>::value_type(CONST_CREATURE_EDUCATOR, CREATURE_EDUCATOR),
		map<string, short>::value_type(CONST_CREATURE_GANGUNIT, CREATURE_GANGUNIT),
		map<string, short>::value_type(CONST_CREATURE_JUDGE_LIBERAL, CREATURE_JUDGE_LIBERAL),
		map<string, short>::value_type(CONST_CREATURE_JUDGE_CONSERVATIVE, CREATURE_JUDGE_CONSERVATIVE),
		map<string, short>::value_type(CONST_CREATURE_AGENT, CREATURE_AGENT),
		map<string, short>::value_type(CONST_CREATURE_RADIOPERSONALITY, CREATURE_RADIOPERSONALITY),
		map<string, short>::value_type(CONST_CREATURE_NEWSANCHOR, CREATURE_NEWSANCHOR),
		map<string, short>::value_type(CONST_CREATURE_GENETIC, CREATURE_GENETIC),
		map<string, short>::value_type(CONST_CREATURE_GUARDDOG, CREATURE_GUARDDOG),
		map<string, short>::value_type(CONST_CREATURE_PRISONER, CREATURE_PRISONER),
		map<string, short>::value_type(CONST_CREATURE_JUROR, CREATURE_JUROR),
		map<string, short>::value_type(CONST_CREATURE_LAWYER, CREATURE_LAWYER),
		map<string, short>::value_type(CONST_CREATURE_SEWERWORKER, CREATURE_SEWERWORKER),
		map<string, short>::value_type(CONST_CREATURE_COLLEGESTUDENT, CREATURE_COLLEGESTUDENT),
		map<string, short>::value_type(CONST_CREATURE_MUSICIAN, CREATURE_MUSICIAN),
		map<string, short>::value_type(CONST_CREATURE_MATHEMATICIAN, CREATURE_MATHEMATICIAN),
		map<string, short>::value_type(CONST_CREATURE_TEACHER, CREATURE_TEACHER),
		map<string, short>::value_type(CONST_CREATURE_HSDROPOUT, CREATURE_HSDROPOUT),
		map<string, short>::value_type(CONST_CREATURE_BUM, CREATURE_BUM),
		map<string, short>::value_type(CONST_CREATURE_GANGMEMBER, CREATURE_GANGMEMBER),
		map<string, short>::value_type(CONST_CREATURE_CRACKHEAD, CREATURE_CRACKHEAD),
		map<string, short>::value_type(CONST_CREATURE_PRIEST, CREATURE_PRIEST),
		map<string, short>::value_type(CONST_CREATURE_ENGINEER, CREATURE_ENGINEER),
		map<string, short>::value_type(CONST_CREATURE_FASTFOODWORKER, CREATURE_FASTFOODWORKER),
		map<string, short>::value_type(CONST_CREATURE_BAKER, CREATURE_BAKER),
		map<string, short>::value_type(CONST_CREATURE_BARISTA, CREATURE_BARISTA),
		map<string, short>::value_type(CONST_CREATURE_BARTENDER, CREATURE_BARTENDER),
		map<string, short>::value_type(CONST_CREATURE_TELEMARKETER, CREATURE_TELEMARKETER),
		map<string, short>::value_type(CONST_CREATURE_CARSALESMAN, CREATURE_CARSALESMAN),
		map<string, short>::value_type(CONST_CREATURE_OFFICEWORKER, CREATURE_OFFICEWORKER),
		map<string, short>::value_type(CONST_CREATURE_FOOTBALLCOACH, CREATURE_FOOTBALLCOACH),
		map<string, short>::value_type(CONST_CREATURE_PROSTITUTE, CREATURE_PROSTITUTE),
		map<string, short>::value_type(CONST_CREATURE_MAILMAN, CREATURE_MAILMAN),
		map<string, short>::value_type(CONST_CREATURE_GARBAGEMAN, CREATURE_GARBAGEMAN),
		map<string, short>::value_type(CONST_CREATURE_PLUMBER, CREATURE_PLUMBER),
		map<string, short>::value_type(CONST_CREATURE_CHEF, CREATURE_CHEF),
		map<string, short>::value_type(CONST_CREATURE_CONSTRUCTIONWORKER, CREATURE_CONSTRUCTIONWORKER),
		map<string, short>::value_type(CONST_CREATURE_AMATEURMAGICIAN, CREATURE_AMATEURMAGICIAN),
		map<string, short>::value_type(CONST_CREATURE_TANK, CREATURE_TANK),
		map<string, short>::value_type(CONST_CREATURE_MERC, CREATURE_MERC),
		map<string, short>::value_type(CONST_CREATURE_HICK, CREATURE_HICK),
		map<string, short>::value_type(CONST_CREATURE_SOLDIER, CREATURE_SOLDIER),
		map<string, short>::value_type(CONST_CREATURE_VETERAN, CREATURE_VETERAN),
		map<string, short>::value_type(CONST_CREATURE_HARDENED_VETERAN, CREATURE_HARDENED_VETERAN),
		map<string, short>::value_type(CONST_CREATURE_PRISONGUARD, CREATURE_PRISONGUARD),
		map<string, short>::value_type(CONST_CREATURE_HIPPIE, CREATURE_HIPPIE),
		map<string, short>::value_type(CONST_CREATURE_CRITIC_ART, CREATURE_CRITIC_ART),
		map<string, short>::value_type(CONST_CREATURE_CRITIC_MUSIC, CREATURE_CRITIC_MUSIC),
		map<string, short>::value_type(CONST_CREATURE_SOCIALITE, CREATURE_SOCIALITE),
		map<string, short>::value_type(CONST_CREATURE_PROGRAMMER, CREATURE_PROGRAMMER),
		map<string, short>::value_type(CONST_CREATURE_RETIREE, CREATURE_RETIREE),
		map<string, short>::value_type(CONST_CREATURE_PAINTER, CREATURE_PAINTER),
		map<string, short>::value_type(CONST_CREATURE_SCULPTOR, CREATURE_SCULPTOR),
		map<string, short>::value_type(CONST_CREATURE_AUTHOR, CREATURE_AUTHOR),
		map<string, short>::value_type(CONST_CREATURE_JOURNALIST, CREATURE_JOURNALIST),
		map<string, short>::value_type(CONST_CREATURE_DANCER, CREATURE_DANCER),
		map<string, short>::value_type(CONST_CREATURE_PHOTOGRAPHER, CREATURE_PHOTOGRAPHER),
		map<string, short>::value_type(CONST_CREATURE_CAMERAMAN, CREATURE_CAMERAMAN),
		map<string, short>::value_type(CONST_CREATURE_HAIRSTYLIST, CREATURE_HAIRSTYLIST),
		map<string, short>::value_type(CONST_CREATURE_FASHIONDESIGNER, CREATURE_FASHIONDESIGNER),
		map<string, short>::value_type(CONST_CREATURE_CLERK, CREATURE_CLERK),
		map<string, short>::value_type(CONST_CREATURE_THIEF, CREATURE_THIEF),
		map<string, short>::value_type(CONST_CREATURE_ACTOR, CREATURE_ACTOR),
		map<string, short>::value_type(CONST_CREATURE_YOGAINSTRUCTOR, CREATURE_YOGAINSTRUCTOR),
		map<string, short>::value_type(CONST_CREATURE_MARTIALARTIST, CREATURE_MARTIALARTIST),
		map<string, short>::value_type(CONST_CREATURE_ATHLETE, CREATURE_ATHLETE),
		map<string, short>::value_type(CONST_CREATURE_BIKER, CREATURE_BIKER),
		map<string, short>::value_type(CONST_CREATURE_TRUCKER, CREATURE_TRUCKER),
		map<string, short>::value_type(CONST_CREATURE_TAXIDRIVER, CREATURE_TAXIDRIVER),
		map<string, short>::value_type(CONST_CREATURE_NUN, CREATURE_NUN),
		map<string, short>::value_type(CONST_CREATURE_MUTANT, CREATURE_MUTANT),
		map<string, short>::value_type(CONST_CREATURE_DOCTOR, CREATURE_DOCTOR),
		map<string, short>::value_type(CONST_CREATURE_NURSE, CREATURE_NURSE),
		map<string, short>::value_type(CONST_CREATURE_CCS_VIGILANTE, CREATURE_CCS_VIGILANTE),
		map<string, short>::value_type(CONST_CREATURE_CCS_ARCHCONSERVATIVE, CREATURE_CCS_ARCHCONSERVATIVE),
		map<string, short>::value_type(CONST_CREATURE_POLITICALACTIVIST, CREATURE_POLITICALACTIVIST),
		map<string, short>::value_type(CONST_CREATURE_CCS_MOLOTOV, CREATURE_CCS_MOLOTOV),
		map<string, short>::value_type(CONST_CREATURE_CCS_SNIPER, CREATURE_CCS_SNIPER),
		map<string, short>::value_type(CONST_CREATURE_PSYCHOLOGIST, CREATURE_PSYCHOLOGIST),
		map<string, short>::value_type(CONST_CREATURE_LOCKSMITH, CREATURE_LOCKSMITH),
		map<string, short>::value_type(CONST_CREATURE_MILITARYPOLICE, CREATURE_MILITARYPOLICE),
		map<string, short>::value_type(CONST_CREATURE_SEAL, CREATURE_SEAL),
		map<string, short>::value_type(CONST_CREATURE_MILITARYOFFICER, CREATURE_MILITARYOFFICER),
		map<string, short>::value_type(CONST_CREATURE_BANK_TELLER, CREATURE_BANK_TELLER),
		map<string, short>::value_type(CONST_CREATURE_BANK_MANAGER, CREATURE_BANK_MANAGER),
		map<string, short>::value_type(CONST_CREATURE_SECRET_SERVICE, CREATURE_SECRET_SERVICE),
		map<string, short>::value_type(CONST_CREATURE_POLITICIAN, CREATURE_POLITICIAN)
	};
	getBaseEnumFromString = {
		map<string, short>::value_type(CONST_SITE_RESIDENTIAL_SHELTER, SITE_RESIDENTIAL_SHELTER),
		map<string, short>::value_type(CONST_SITE_RESIDENTIAL_TENEMENT, SITE_RESIDENTIAL_TENEMENT),
		map<string, short>::value_type(CONST_SITE_RESIDENTIAL_APARTMENT, SITE_RESIDENTIAL_APARTMENT),
		map<string, short>::value_type(CONST_SITE_RESIDENTIAL_APARTMENT_UPSCALE, SITE_RESIDENTIAL_APARTMENT_UPSCALE),
		map<string, short>::value_type(CONST_SITE_RESIDENTIAL_BOMBSHELTER, SITE_RESIDENTIAL_BOMBSHELTER),
		map<string, short>::value_type(CONST_SITE_LABORATORY_COSMETICS, SITE_LABORATORY_COSMETICS),
		map<string, short>::value_type(CONST_SITE_LABORATORY_GENETIC, SITE_LABORATORY_GENETIC),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_POLICESTATION, SITE_GOVERNMENT_POLICESTATION),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_COURTHOUSE, SITE_GOVERNMENT_COURTHOUSE),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_PRISON, SITE_GOVERNMENT_PRISON),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_INTELLIGENCEHQ, SITE_GOVERNMENT_INTELLIGENCEHQ),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_FIRESTATION, SITE_GOVERNMENT_FIRESTATION),
		map<string, short>::value_type(CONST_SITE_INDUSTRY_SWEATSHOP, SITE_INDUSTRY_SWEATSHOP),
		map<string, short>::value_type(CONST_SITE_INDUSTRY_POLLUTER, SITE_INDUSTRY_POLLUTER),
		map<string, short>::value_type(CONST_SITE_INDUSTRY_NUCLEAR, SITE_INDUSTRY_NUCLEAR),
		map<string, short>::value_type(CONST_SITE_INDUSTRY_WAREHOUSE, SITE_INDUSTRY_WAREHOUSE),
		map<string, short>::value_type(CONST_SITE_CORPORATE_HEADQUARTERS, SITE_CORPORATE_HEADQUARTERS),
		map<string, short>::value_type(CONST_SITE_CORPORATE_HOUSE, SITE_CORPORATE_HOUSE),
		map<string, short>::value_type(CONST_SITE_MEDIA_AMRADIO, SITE_MEDIA_AMRADIO),
		map<string, short>::value_type(CONST_SITE_MEDIA_CABLENEWS, SITE_MEDIA_CABLENEWS),
		map<string, short>::value_type(CONST_SITE_BUSINESS_CRACKHOUSE, SITE_BUSINESS_CRACKHOUSE),
		map<string, short>::value_type(CONST_SITE_BUSINESS_JUICEBAR, SITE_BUSINESS_JUICEBAR),
		map<string, short>::value_type(CONST_SITE_BUSINESS_CIGARBAR, SITE_BUSINESS_CIGARBAR),
		map<string, short>::value_type(CONST_SITE_BUSINESS_LATTESTAND, SITE_BUSINESS_LATTESTAND),
		map<string, short>::value_type(CONST_SITE_BUSINESS_VEGANCOOP, SITE_BUSINESS_VEGANCOOP),
		map<string, short>::value_type(CONST_SITE_BUSINESS_INTERNETCAFE, SITE_BUSINESS_INTERNETCAFE),
		map<string, short>::value_type(CONST_SITE_BUSINESS_BARANDGRILL, SITE_BUSINESS_BARANDGRILL),
		map<string, short>::value_type(CONST_SITE_OUTDOOR_PUBLICPARK, SITE_OUTDOOR_PUBLICPARK),
		map<string, short>::value_type(CONST_SITE_OUTDOOR_BUNKER, SITE_OUTDOOR_BUNKER),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_ARMYBASE, SITE_GOVERNMENT_ARMYBASE),
		map<string, short>::value_type(CONST_SITE_BUSINESS_BANK, SITE_BUSINESS_BANK),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_LIBERAL_PARTY_HQ, SITE_GOVERNMENT_LIBERAL_PARTY_HQ),
		map<string, short>::value_type(CONST_SITE_GOVERNMENT_WHITE_HOUSE, SITE_GOVERNMENT_WHITE_HOUSE)
	};
	getSpecialWoundEnumFromString = {
		map<string, short>::value_type(CONST_SPECIALWOUND_TEETH, SPECIALWOUND_TEETH),
		map<string, short>::value_type(CONST_SPECIALWOUND_RIGHTEYE, SPECIALWOUND_RIGHTEYE),
		map<string, short>::value_type(CONST_SPECIALWOUND_LEFTEYE, SPECIALWOUND_LEFTEYE),
		map<string, short>::value_type(CONST_SPECIALWOUND_NOSE, SPECIALWOUND_NOSE),
		map<string, short>::value_type(CONST_SPECIALWOUND_TONGUE, SPECIALWOUND_TONGUE),
		map<string, short>::value_type(CONST_SPECIALWOUND_RIGHTLUNG, SPECIALWOUND_RIGHTLUNG),
		map<string, short>::value_type(CONST_SPECIALWOUND_LEFTLUNG, SPECIALWOUND_LEFTLUNG),
		map<string, short>::value_type(CONST_SPECIALWOUND_HEART, SPECIALWOUND_HEART),
		map<string, short>::value_type(CONST_SPECIALWOUND_LIVER, SPECIALWOUND_LIVER),
		map<string, short>::value_type(CONST_SPECIALWOUND_STOMACH, SPECIALWOUND_STOMACH),
		map<string, short>::value_type(CONST_SPECIALWOUND_RIGHTKIDNEY, SPECIALWOUND_RIGHTKIDNEY),
		map<string, short>::value_type(CONST_SPECIALWOUND_LEFTKIDNEY, SPECIALWOUND_LEFTKIDNEY),
		map<string, short>::value_type(CONST_SPECIALWOUND_SPLEEN, SPECIALWOUND_SPLEEN),
		map<string, short>::value_type(CONST_SPECIALWOUND_RIBS, SPECIALWOUND_RIBS),
		map<string, short>::value_type(CONST_SPECIALWOUND_NECK, SPECIALWOUND_NECK),
		map<string, short>::value_type(CONST_SPECIALWOUND_UPPERSPINE, SPECIALWOUND_UPPERSPINE),
		map<string, short>::value_type(CONST_SPECIALWOUND_LOWERSPINE, SPECIALWOUND_LOWERSPINE)
	};
	tankBodyParts = {
		map<short, string>::value_type(BODYPART_HEAD, CONST_TURRET),
		map<short, string>::value_type(BODYPART_BODY, CONST_FRONT),
		map<short, string>::value_type(BODYPART_ARM_RIGHT, CONST_RIGHT_SIDE),
		map<short, string>::value_type(BODYPART_ARM_LEFT, CONST_LEFT_SIDE),
		map<short, string>::value_type(BODYPART_LEG_RIGHT, CONST_RIGHT_TREAD),
		map<short, string>::value_type(BODYPART_LEG_LEFT, CONST_LEFT_TREAD)
	};
	animalBodyParts = {
		map<short, string>::value_type(BODYPART_HEAD, tag_head),
		map<short, string>::value_type(BODYPART_BODY, tag_body),
		map<short, string>::value_type(BODYPART_ARM_RIGHT, CONST_RIGHT_FRONT_LEG),
		map<short, string>::value_type(BODYPART_ARM_LEFT, CONST_LEFT_FRONT_LEG),
		map<short, string>::value_type(BODYPART_LEG_RIGHT, CONST_RIGHT_REAR_LEG),
		map<short, string>::value_type(BODYPART_LEG_LEFT, CONST_LEFT_REAR_LEG)
	};
	humanBodyParts = {
		map<short, string>::value_type(BODYPART_HEAD, tag_head),
		map<short, string>::value_type(BODYPART_BODY, tag_body),
		map<short, string>::value_type(BODYPART_ARM_RIGHT, CONST_RIGHT_ARM),
		map<short, string>::value_type(BODYPART_ARM_LEFT, CONST_LEFT_ARM),
		map<short, string>::value_type(BODYPART_LEG_RIGHT, CONST_RIGHT_LEG),
		map<short, string>::value_type(BODYPART_LEG_LEFT, CONST_LEFT_LEG)
	};
	supportsLiberalLaw = {
		map<short, string>::value_type(VIEW_GAY, CONST_WERE_IN_FAVOR_OF_EQUAL_RIGHTS_FOR_HOMOSEXUALS),
		map<short, string>::value_type(VIEW_DEATHPENALTY, CONST_OPPOSED_THE_DEATH_PENALTY),
		map<short, string>::value_type(VIEW_TAXES, CONST_WERE_AGAINST_CUTTING_TAXES),
		map<short, string>::value_type(VIEW_NUCLEARPOWER, CONST_WERE_TERRIFIED_OF_NUCLEAR_POWER),
		map<short, string>::value_type(VIEW_ANIMALRESEARCH, CONST_DEPLORED_ANIMAL_RESEARCH),
		map<short, string>::value_type(VIEW_POLICEBEHAVIOR, CONST_WERE_CRITICAL_OF_THE_POLICE),
		map<short, string>::value_type(VIEW_TORTURE, CONST_WANTED_STRONGER_MEASURES_TO_PREVENT_TORTURE),
		map<short, string>::value_type(VIEW_INTELLIGENCE, CONST_THOUGHT_THE_INTELLIGENCE_COMMUNITY_INVADES_PRIVACY),
		map<short, string>::value_type(VIEW_FREESPEECH, CONST_BELIEVED_IN_UNFETTERED_FREE_SPEECH),
		map<short, string>::value_type(VIEW_GENETICS, CONST_ABHORRED_GENETICALLY_ALTERED_FOOD_PRODUCTS),
		map<short, string>::value_type(VIEW_JUSTICES, CONST_WERE_FOR_THE_APPOINTMENT_OF_LIBERAL_JUSTICES),
		map<short, string>::value_type(VIEW_SWEATSHOPS, CONST_WOULD_BOYCOTT_COMPANIES_THAT_USED_SWEATSHOPS),
		map<short, string>::value_type(VIEW_POLLUTION, CONST_THOUGHT_INDUSTRY_SHOULD_LOWER_POLLUTION),
		map<short, string>::value_type(VIEW_CORPORATECULTURE, CONST_WERE_DISGUSTED_BY_CORPORATE_MALFEASANCE),
		map<short, string>::value_type(VIEW_CEOSALARY, CONST_BELIEVED_THAT_CEO_SALARIES_ARE_TOO_GREAT),
		map<short, string>::value_type(VIEW_WOMEN, CONST_FAVORED_DOING_MORE_FOR_GENDER_EQUALITY),
		map<short, string>::value_type(VIEW_CIVILRIGHTS, CONST_FELT_MORE_WORK_WAS_NEEDED_FOR_RACIAL_EQUALITY),
		map<short, string>::value_type(VIEW_GUNCONTROL, CONST_ARE_CONCERNED_ABOUT_GUN_VIOLENCE),
		map<short, string>::value_type(VIEW_MILITARY, CONST_OPPOSED_INCREASING_MILITARY_SPENDING),
		map<short, string>::value_type(VIEW_LIBERALCRIMESQUAD, CONST_RESPECTED_THE_POWER_OF_THE_LIBERAL_CRIME_SQUAD),
		map<short, string>::value_type(VIEW_LIBERALCRIMESQUADPOS, CONST_OF_THESE_HELD_THE_LIBERAL_CRIME_SQUAD_IN_HIGH_REGARD),
		map<short, string>::value_type(VIEW_CONSERVATIVECRIMESQUAD, CONST_HELD_THE_CONSERVATIVE_CRIME_SQUAD_IN_CONTEMPT),
		map<short, string>::value_type(VIEW_PRISONS, CONST_WANTED_TO_END_PRISONER_ABUSE_AND_TORTURE),
		map<short, string>::value_type(VIEW_AMRADIO, CONST_DO_NOT_LIKE_AM_RADIO),
		map<short, string>::value_type(VIEW_CABLENEWS, CONST_HAVE_A_NEGATIVE_OPINION_OF_CABLE_NEWS_PROGRAMS),
		//map<short, string>::value_type( VIEW_POLITICALVIOLENCE, CONST_THOUGHT_POLITICAL_VIOLENCE_WAS_JUSTIFIED)
	};
	winnerOfElection = {
		map<short, string>::value_type(ALIGN_ARCHCONSERVATIVE, CONST_THE_U_S_A_FLAG_EAGLE_CONSERVATIVE_TEA_PARTY_CLAIMS_VICTORY),
		map<short, string>::value_type(ALIGN_CONSERVATIVE, CONST_THE_CONSERVATIVE_PARTY_CLAIMS_VICTORY),
		map<short, string>::value_type(ALIGN_MODERATE, CONST_THE_NEXT_TWO_YEARS_PROMISE_TO_BE_MORE_OF_THE_SAME),
		map<short, string>::value_type(ALIGN_LIBERAL, CONST_THE_LIBERAL_PARTY_CLAIMS_VICTORY),
		map<short, string>::value_type(ALIGN_ELITELIBERAL, CONST_THE_PROGRESSIVE_ELITE_SOCIAL_LIBERAL_GREEN_PARTY_CLAIMS_VICTORY),
		map<short, string>::value_type(ALIGN_STALINIST, CONST_THE_STALINIST_PARTY_CLAIMS_VICTORY)
	};
	newsStories = {
		map<short, vector<string> >::value_type(NEWSSTORY_SQUAD_ESCAPED,
		{ CONST_ESCAPED_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING }),
		map<short, vector<string> >::value_type(NEWSSTORY_SQUAD_FLEDATTACK,
		{ CONST_ESCAPED_FROM_POLICE_OFFICERS_DURING_A_RAID_YESTERDAY_ACCORDING }),
		map<short, vector<string> >::value_type(NEWSSTORY_SQUAD_DEFENDED,
		{ CONST_FOUGHT_OFF_A_POLICE_RAID_YESTERDAY_ACCORDING }),
		map<short, vector<string> >::value_type(NEWSSTORY_SQUAD_BROKESIEGE,
		{ CONST_VIOLENTLY_BROKE_A_POLICE_SIEGE_YESTERDAY_ACCORDING }),
		map<short, vector<string> >::value_type(NEWSSTORY_SQUAD_KILLED_SIEGEATTACK,
		{ CONST_WERE_SLAIN_DURING_A_POLICE_RAID_YESTERDAY_ACCORDING,
			CONST_WERE_MURDERED_DURING_A_POLICE_RAID_YESTERDAY_ACCORDING }),
		map<short, vector<string> >::value_type(NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE,
		{ CONST_WERE_SLAIN_TRYING_TO_ESCAPE_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING,
			CONST_WERE_MURDERED_TRYING_TO_ESCAPE_FROM_A_POLICE_SIEGE_YESTERDAY_ACCORDING })
	};
	cityNames = {
		map<short, string>::value_type(SITE_CITY_SEATTLE,  CONST_SEATTLE_WA),
		map<short, string>::value_type(SITE_CITY_NEW_YORK,  CONST_NEW_YORK_NY),
		map<short, string>::value_type(SITE_CITY_LOS_ANGELES,  CONST_LOS_ANGELES_CA),
		map<short, string>::value_type(SITE_CITY_CHICAGO,  CONST_CHICAGO_IL),
		map<short, string>::value_type(SITE_CITY_DETROIT,  CONST_DETROIT_MI),
		map<short, string>::value_type(SITE_CITY_ATLANTA,  CONST_ATLANTA_GA),
		map<short, string>::value_type(SITE_CITY_MIAMI,  CONST_MIAMI_FL),
		map<short, string>::value_type(SITE_CITY_WASHINGTON_DC,  CONST_WASHINGTON_DC),
	};
	carchaseObstacles = {
		map<short, vector<string> >::value_type(CARCHASE_OBSTACLE_FRUITSTAND,
		//LIMIT :------------------------------------:
		{ CONST_YOU_ARE_SPEEDING_TOWARD_A_FLIMSY_FRUIT_STAND,
			CONST_D_SWERVE_TO_AVOID_HITTING_ANYONE,
			CONST_F_PLAY_IT_SAFE_AND_PLOW_THROUGH_IT }),
		map<short, vector<string> >::value_type(CARCHASE_OBSTACLE_TRUCKPULLSOUT,
		//LIMIT :------------------------------------:
	{ CONST_A_TRUCK_PULLS_OUT_IN_YOUR_PATH,
		CONST_D_SPEED_AROUND_IT,
		CONST_F_SLOW_DOWN }),
	map<short, vector<string> >::value_type(CARCHASE_OBSTACLE_CROSSTRAFFIC,
	//LIMIT :------------------------------------:
{ CONST_THERE_S_A_RED_LIGHT_WITH_CROSS_TRAFFIC_AHEAD,
	CONST_D_RUN_THE_LIGHT_ANYWAY,
	CONST_F_SLOW_DOWN_AND_TURN }),
map<short, vector<string> >::value_type(CARCHASE_OBSTACLE_CHILD,
//LIMIT :------------------------------------:
{ CONST_A_KID_RUNS_INTO_THE_STREET_FOR_HIS_BALL,
	CONST_D_SWERVE_AROUND_HIM,
	CONST_F_SLAM_THE_BRAKES })
	};
	skillEnumToString = {
		map<short, string>::value_type(SKILL_HANDTOHAND,      CONST_MARTIAL_ARTS),
		map<short, string>::value_type(SKILL_KNIFE,           CONST_KNIFE),
		map<short, string>::value_type(SKILL_SWORD,           CONST_SWORD),
		map<short, string>::value_type(SKILL_THROWING,        CONST_THROWING),
		map<short, string>::value_type(SKILL_CLUB,            CONST_CLUB),
		map<short, string>::value_type(SKILL_AXE,             CONST_X_AXE),
		map<short, string>::value_type(SKILL_PISTOL,          CONST_X_PISTOL),
		map<short, string>::value_type(SKILL_RIFLE,           CONST_X_RIFLE),
		map<short, string>::value_type(SKILL_HEAVYWEAPONS,    CONST_X_HEAVY_WEAPONS),
		map<short, string>::value_type(SKILL_SHOTGUN,         CONST_X_SHOTGUN),
		map<short, string>::value_type(SKILL_SMG,             CONST_X_SMG),
		map<short, string>::value_type(SKILL_PERSUASION,      CONST_X_PERSUASION),
		map<short, string>::value_type(SKILL_PSYCHOLOGY,      CONST_X_PSYCHOLOGY),
		map<short, string>::value_type(SKILL_SECURITY,        CONST_X_SECURITY),
		map<short, string>::value_type(SKILL_DISGUISE,        CONST_X_DISGUISE),
		map<short, string>::value_type(SKILL_COMPUTERS,       CONST_X_COMPUTERS),
		map<short, string>::value_type(SKILL_LAW,             CONST_X_LAW),
		map<short, string>::value_type(SKILL_TAILORING,       CONST_X_TAILORING),
		map<short, string>::value_type(SKILL_DRIVING,         CONST_X_DRIVING),
		map<short, string>::value_type(SKILL_WRITING,         CONST_X_WRITING),
		map<short, string>::value_type(SKILL_MUSIC,           CONST_X_MUSIC),
		map<short, string>::value_type(SKILL_ART,             CONST_X_ART),
		map<short, string>::value_type(SKILL_RELIGION,        CONST_X_RELIGION),
		map<short, string>::value_type(SKILL_SCIENCE,         CONST_X_SCIENCE),
		map<short, string>::value_type(SKILL_BUSINESS,        CONST_X_BUSINESS),
		map<short, string>::value_type(SKILL_STEALTH,         CONST_X_STEALTH),
		map<short, string>::value_type(SKILL_TEACHING,        CONST_X_TEACHING),
		map<short, string>::value_type(SKILL_STREETSENSE,     CONST_X_STREET_SENSE),
		map<short, string>::value_type(SKILL_SEDUCTION,       CONST_X_SEDUCTION),
		map<short, string>::value_type(SKILL_FIRSTAID,        CONST_X_FIRST_AID),
		map<short, string>::value_type(SKILL_DODGE,           CONST_X_DODGE)
	};
	attEnumToString = {
		map<short, string>::value_type(ATTRIBUTE_STRENGTH,       CONST_X_STR),
		map<short, string>::value_type(ATTRIBUTE_AGILITY,        CONST_X_AGI),
		map<short, string>::value_type(ATTRIBUTE_WISDOM,         CONST_X_WIS),
		map<short, string>::value_type(ATTRIBUTE_INTELLIGENCE,   CONST_X_INT),
		map<short, string>::value_type(ATTRIBUTE_HEART,          CONST_X_HRT),
		map<short, string>::value_type(ATTRIBUTE_HEALTH,         CONST_X_HLTH),
		map<short, string>::value_type(ATTRIBUTE_CHARISMA,       CONST_X_CHA)
	};
	getAlignString = {
		map<short, string>::value_type(ALIGN_ARCHCONSERVATIVE,  CONST_X_ARCHCONSERVATIVE),
		map<short, string>::value_type(ALIGN_CONSERVATIVE,  CONST_X_CONSERVATIVE),
		map<short, string>::value_type(ALIGN_MODERATE,  CONST_ACTIVITY_SLEEPER_SPY5),
		map<short, string>::value_type(ALIGN_LIBERAL,  CONST_X_LIBERAL),
		map<short, string>::value_type(ALIGN_ELITELIBERAL,  CONST_X_ELITE_LIBERAL),
		map<short, string>::value_type(ALIGN_STALINIST,  CONST_X_STALINIST)
	};
	musicList = {
		// titlemode.ogg or .mid - Also sprach Zarathustra, introduction by Richard Strauss
		map<short, string>::value_type(MUSIC_TITLEMODE, CONST_X_TITLEMODE), // load title mode music
																  // newgame.ogg or .mid- The Liberty Bell March by John Philip Sousa
		map<short, string>::value_type(MUSIC_NEWGAME, CONST_X_NEWGAME), // load new game music
															  // basemode.ogg or .mid - The Stars and Stripes Forever by John Philip Sousa
		map<short, string>::value_type(MUSIC_BASEMODE, CONST_X_BASEMODE), // load regular base mode music
																// siege.ogg or .mid- The Planets, 1st Movement CONST_X_MARS by Gustav Holst
		map<short, string>::value_type(MUSIC_SIEGE, CONST_X_SIEGE), // load base mode while under siege music
														  // activate.ogg or .mid - Piano Sonata #11, 3rd Movement "Rondo Alla Turca" by Wolfgang Amadeus Mozart
		map<short, string>::value_type(MUSIC_ACTIVATE, CONST_X_ACTIVATE), // load activate Liberals music
																// sleepers.ogg or .mid - Toccata and Fugue in D Minor, BWV 565 by Johann Sebastian Bach
		map<short, string>::value_type(MUSIC_SLEEPERS, CONST_X_SLEEPERS_LOWERCASE), // load activate Sleepers music
																// stopevil.ogg or .mid - Hungarian Dance #5 by Johannes Brahms (based on the csardas "Bartfai emlek" by Bela Keler)
		map<short, string>::value_type(MUSIC_STOPEVIL, CONST_X_STOPEVIL), // load go forth to stop evil music
																// reviewmode.ogg or .mid - Symphony #94, 2nd Movement "Surprise Symphony" by Joseph Haydn
		map<short, string>::value_type(MUSIC_REVIEWMODE, CONST_X_REVIEWMODE), // load review mode music
																	// liberalagenda.ogg or .mid - Beautiful Dreamer by Stephen Foster
		map<short, string>::value_type(MUSIC_LIBERALAGENDA, CONST_X_LIBERALAGENDA), // load status of the Liberal agenda music
																		  // disbanded.ogg or .mid - La Cucaracha, a traditional Mexican folk song originally from Spain
		map<short, string>::value_type(MUSIC_DISBANDED, CONST_X_DISBANDED), // load disbanded music
																  // finances.ogg or .mid - Minuet in G Major by Christian Petzold (falsely attributed to Johann Sebastian Bach until 1970)
		map<short, string>::value_type(MUSIC_FINANCES, CONST_X_FINANCES), // load finance report music
																// cartheft.ogg or .mid - The Ride of the Valkyries by Richard Wanger
		map<short, string>::value_type(MUSIC_CARTHEFT, CONST_X_CARTHEFT), // load car theft music
																// elections.ogg or .mid - Habanera from Carmen by Georges Bizet
		map<short, string>::value_type(MUSIC_ELECTIONS, CONST_X_ELECTIONS), // load elections music
																  // shopping.ogg or .mid - The Entertainer by Scott Joplin
		map<short, string>::value_type(MUSIC_SHOPPING, CONST_X_SHOPPING), // load shopping music
																// sitemode.ogg or .mid - Dance of the Sugar Plum Fairy by Pyotr Ilyich Tchaikovsky
		map<short, string>::value_type(MUSIC_SITEMODE, CONST_X_SITEMODE), // load site mode music
																// suspicious.ogg or .mid - Hall of the Mountain King by Edvard Grieg
		map<short, string>::value_type(MUSIC_SUSPICIOUS, tag_suspicious), // load suspicious music
																	// alarmed.ogg or .mid - 5th Symphony, 1st Movement by Ludwig van Beethoven
		map<short, string>::value_type(MUSIC_ALARMED, CONST_X_ALARMED), // load alarmed music
															  // heavycombat.ogg or .mid - 6th Symphony CONST_X_PASTORALE, 4th Movement by Ludwig van Beethoven
		map<short, string>::value_type(MUSIC_HEAVYCOMBAT, CONST_X_HEAVYCOMBAT), // load massive Conservative response music
																	  // defense.ogg or .mid - Danse Macabre by Camille Saint-Saens
		map<short, string>::value_type(MUSIC_DEFENSE, CONST_X_DEFENSE_LOWERCASE), // load escaping/engaging a siege music
															  // conquer.ogg or .mid - Infernal Galop / Can-Can from Orpheus in the Underworld by Jacques Offenbach
		map<short, string>::value_type(MUSIC_CONQUER, CONST_X_CONQUER), // load success in conquering a siege or safehouse or the CCS music
															  // carchase.ogg or .mid - The William Tell Overture by Gioacchino Antonio Rossini
		map<short, string>::value_type(MUSIC_CARCHASE, CONST_X_CARCHASE), // load car chase music
																// footchase.ogg or .mid - The Maple Leaf Rag by Scott Joplin
		map<short, string>::value_type(MUSIC_FOOTCHASE, CONST_X_FOOTCHASE), // load foot chase music
																  // InterrogationST.ogg or .mid - Night on Bald Mountain by Modest Mussorgsky
		map<short, string>::value_type(MUSIC_INTERROGATION, tag_interrogation), // load InterrogationST music
																		  // trial.ogg or .mid - Hungarian Rhapsody #2 by Franz Liszt
		map<short, string>::value_type(MUSIC_TRIAL, CONST_X_TRIAL), // load trial music
														  // recruiting.ogg or .mid - Dance of the Hours by Amilcare Ponchielli
		map<short, string>::value_type(MUSIC_RECRUITING, CONST_X_RECRUITING_LOWERCASE), // load recruiting music
																	// dating.ogg or .mid - The Blue Danube Waltz by Johann Strauss Jr.
		map<short, string>::value_type(MUSIC_DATING, tag_dating), // load dating music
															// newspaper.ogg or .mid - Eine Kleine Nachtmusik, 1st Movement by Wolfgang Amadeus Mozart
		map<short, string>::value_type(MUSIC_NEWSPAPER, CONST_X_NEWSPAPER), // load newspaper music
																  // lacops.ogg or .mid - The Flight of the Bumblebee by Nikolai Rimsky-Korsakov
		map<short, string>::value_type(MUSIC_LACOPS, CONST_X_LACOPS), // load LA cops beating black man and getting caught on video music
															// newscast.ogg or .mid - La Marseillaise, The French National Anthem by Claude Joseph Rouget de Lisle
		map<short, string>::value_type(MUSIC_NEWSCAST, CONST_X_NEWSCAST), // load newscast where smart liberal guest gets some words in edgewise music
																// glamshow.ogg or .mid - Das Deutschlandlied, The German National Anthem by Joseph Haydn
		map<short, string>::value_type(MUSIC_GLAMSHOW, CONST_X_GLAMSHOW), // load glamorous TV show about lifestyles of the rich and famous music
																// anchor.ogg or .mid - I Am the Very Model of a Modern Major-General by Sir Arthur Seymour Sullivan
		map<short, string>::value_type(MUSIC_ANCHOR, CONST_X_ANCHOR), // load handsome charismatic new Conservative cable news anchor music
															// abort.ogg or .mid - Tarantella Napoletana, a traditional Italian folk song from Naples
		map<short, string>::value_type(MUSIC_ABORT, CONST_X_ABORT), // load failed partial birth abortion on trashy daytime talk show music
														  // victory.ogg or .mid - The Star-Spangled Banner, The U.S. National Anthem by John Stafford Smith
		map<short, string>::value_type(MUSIC_VICTORY, CONST_X_VICTORY), // load victory music
															  // defeat.ogg or .mid - Piano Sonata #2, 3rd Movement "Funeral March" by Frederic Francois Chopin
		map<short, string>::value_type(MUSIC_DEFEAT, CONST_X_DEFEAT), // load defeat music
															// reagainified.ogg or .mid - Dixie, The Confederate National Anthem by Daniel Decatur Emmett
		map<short, string>::value_type(MUSIC_REAGANIFIED, CONST_X_REAGANIFIED), // load Reaganified music
																	  // stalinized.ogg or .mid - The Soviet (and now Russian) National Anthem by Alexander Vasilyevich Alexandrov
		map<short, string>::value_type(MUSIC_STALINIZED, CONST_X_STALINIZED) // load Stalinized music
	};
	ACTIVITY_TEACH_FIGHTING_DEFAULT =
		// this first block are creatures with All Weapon Skills, Martial Arts, Dodge, and First Aid
	{ CREATURE_ATHLETE,
		CREATURE_BOUNCER,
		CREATURE_COP,
		CREATURE_CCS_ARCHCONSERVATIVE,
		CREATURE_CCS_MOLOTOV,
		CREATURE_CCS_SNIPER,
		CREATURE_CCS_VIGILANTE,
		CREATURE_DEATHSQUAD,
		CREATURE_DOCTOR,
		CREATURE_FIREFIGHTER,
		CREATURE_GANGMEMBER,
		CREATURE_GANGUNIT,
		CREATURE_GUARDDOG,
		CREATURE_GENETIC,
		CREATURE_HARDENED_VETERAN,
		CREATURE_HICK,
		CREATURE_MARTIALARTIST,
		CREATURE_MERC,
		CREATURE_MILITARYOFFICER,
		CREATURE_MILITARYPOLICE,
		CREATURE_MUTANT,
		CREATURE_NURSE,
		CREATURE_PRISONGUARD,
		CREATURE_SEAL,
		CREATURE_SECURITYGUARD,
		CREATURE_SOLDIER,
		CREATURE_SWAT,
		CREATURE_TANK,
		CREATURE_VETERAN };
	ACTIVITY_TEACH_COVERT_DEFAULT =
		// this second block are creatures with Computers, Security, Stealth, Disguise, Tailoring, Seduction, Psychology, & Driving
	{ CREATURE_ACTOR,
		CREATURE_AGENT,
		CREATURE_AMATEURMAGICIAN,
		CREATURE_BIKER,
		CREATURE_BUM,
		CREATURE_CONSTRUCTIONWORKER,
		CREATURE_CRACKHEAD,
		CREATURE_EDUCATOR,
		CREATURE_FASHIONDESIGNER,
		CREATURE_GARBAGEMAN,
		CREATURE_HSDROPOUT,
		CREATURE_LOCKSMITH,
		CREATURE_MAILMAN,
		CREATURE_PLUMBER,
		CREATURE_PRISONER,
		CREATURE_PROGRAMMER,
		CREATURE_PROSTITUTE,
		CREATURE_PSYCHOLOGIST,
		CREATURE_SECRET_SERVICE,
		CREATURE_SEWERWORKER,
		CREATURE_TAXIDRIVER,
		CREATURE_THIEF,
		CREATURE_TRUCKER,
		CREATURE_WORKER_FACTORY_CHILD,
		CREATURE_WORKER_SERVANT,
		CREATURE_WORKER_SWEATSHOP };
	ACTIVITY_TEACH_POLITICS_DEFAULT =
		// this third block are creatures with Writing, Persuasion, Law, Street Sense, Science, Religion, Business, Music, & Art
	{ CREATURE_AUTHOR,
		CREATURE_BANK_MANAGER,
		CREATURE_BANK_TELLER,
		CREATURE_CAMERAMAN,
		CREATURE_CARSALESMAN,
		CREATURE_CHEF,
		CREATURE_CLERK,
		CREATURE_COLLEGESTUDENT,
		CREATURE_CORPORATE_CEO,
		CREATURE_CORPORATE_MANAGER,
		CREATURE_CRITIC_ART,
		CREATURE_CRITIC_MUSIC,
		CREATURE_DANCER,
		CREATURE_ENGINEER,
		CREATURE_FASTFOODWORKER,
		CREATURE_BAKER,
		CREATURE_BARISTA,
		CREATURE_BARTENDER,
		CREATURE_FOOTBALLCOACH,
		CREATURE_HAIRSTYLIST,
		CREATURE_HIPPIE,
		CREATURE_JOURNALIST,
		CREATURE_JUDGE_CONSERVATIVE,
		CREATURE_JUDGE_LIBERAL,
		CREATURE_JUROR,
		CREATURE_LANDLORD,
		CREATURE_LAWYER,
		CREATURE_MATHEMATICIAN,
		CREATURE_MUSICIAN,
		CREATURE_NEWSANCHOR,
		CREATURE_NUN,
		CREATURE_OFFICEWORKER,
		CREATURE_PAINTER,
		CREATURE_PHOTOGRAPHER,
		CREATURE_POLITICALACTIVIST,
		CREATURE_POLITICIAN,
		CREATURE_PRIEST,
		CREATURE_RADIOPERSONALITY,
		CREATURE_RETIREE,
		CREATURE_SCIENTIST_EMINENT,
		CREATURE_SCIENTIST_LABTECH,
		CREATURE_SCULPTOR,
		CREATURE_SOCIALITE,
		CREATURE_TEACHER,
		CREATURE_TEENAGER,
		CREATURE_TELEMARKETER,
		CREATURE_WORKER_FACTORY_NONUNION,
		CREATURE_WORKER_FACTORY_UNION,
		CREATURE_WORKER_JANITOR,
		CREATURE_WORKER_SECRETARY,
		CREATURE_YOGAINSTRUCTOR };
	processTheUnprocessed(helpTopicUnprocessed, helpTopics, string_to_activity);
	processTheUnprocessed(conservativeLegalArgumentUnprocessed, conservativeLegalArgument, string_to_law);
	processTheUnprocessed(youAreStupidTalkAboutIssuesUnprocessed, youAreStupidTalkAboutIssues, string_to_law);
	processTheUnprocessed(issueTooLiberalUnprocessed, issueTooLiberal, string_to_law);
	processTheUnprocessed(issueEventStringUnprocessed, issueEventString, string_to_view);
	processTheUnprocessed(conservatiseLawUnprocessed, conservatiseLaw, string_to_law);
	processTheUnprocessed(liberalizeLawUnprocessed, liberalizeLaw, string_to_law);
	processTheUnprocessed(discussIssuesUnprocessed, discussIssues, string_to_view);
	processTheUnprocessed(discussesIssuesUnprocessed, discussesIssues, string_to_view);
	processTheUnprocessed(talkAboutTheIssuesUnprocessed, talkAboutTheIssues, string_to_law);
	processTheUnprocessed(endgameLawStringsUnprocessed, endgameLawStrings, string_to_law);
	for (string str : state_biases_Unprocessed) {
		state_biases.push_back(atoi(str.data()));
	}
	site_tile_list = {
		map<string, short>::value_type(CONST_X_EXIT, SITEBLOCK_EXIT),
		map<string, short>::value_type(CONST_X_BLOCK, SITEBLOCK_BLOCK),
		map<string, short>::value_type(CONST_X_DOOR, SITEBLOCK_DOOR),
		map<string, short>::value_type(CONST_X_KNOWN, SITEBLOCK_KNOWN),
		map<string, short>::value_type(tag_LOOT, SITEBLOCK_LOOT),
		map<string, short>::value_type(CONST_X_LOCKED, SITEBLOCK_LOCKED),
		map<string, short>::value_type(CONST_X_KLOCK, SITEBLOCK_KLOCK),
		map<string, short>::value_type(CONST_X_CLOCK, SITEBLOCK_CLOCK),
		map<string, short>::value_type(CONST_X_RESTRICTED, SITEBLOCK_RESTRICTED),
		map<string, short>::value_type(CONST_X_BLOODY, SITEBLOCK_BLOODY),
		map<string, short>::value_type(CONST_BLOODY_2, SITEBLOCK_BLOODY2),
		map<string, short>::value_type(CONST_X_GRASSY, SITEBLOCK_GRASSY),
		map<string, short>::value_type(CONST_X_OUTDOOR, SITEBLOCK_OUTDOOR),
		map<string, short>::value_type(CONST_X_DEBRIS, SITEBLOCK_DEBRIS),
		map<string, short>::value_type(CONST_X_GRAFFITI_ALLCAPS, SITEBLOCK_GRAFFITI),
		map<string, short>::value_type(CONST_X_GRAFFITI_CCS, SITEBLOCK_GRAFFITI_CCS),
		map<string, short>::value_type(CONST_X_GRAFFITI_OTHER, SITEBLOCK_GRAFFITI_OTHER),
		map<string, short>::value_type(CONST_X_FIRE_START, SITEBLOCK_FIRE_START),
		map<string, short>::value_type(CONST_X_FIRE_PEAK, SITEBLOCK_FIRE_PEAK),
		map<string, short>::value_type(CONST_X_FIRE_END, SITEBLOCK_FIRE_END),
		map<string, short>::value_type(CONST_X_OPEN, 0),
	};
	rejectionReasons = {
		map<int, vector<string> >::value_type(REJECTED_CCS, rejectedByCCS),
	   map<int, vector<string> >::value_type(REJECTED_NUDE, rejectedBecauseNude),
	   map<int, vector<string> >::value_type(REJECTED_UNDERAGE, rejectedBecauseUnderage),
	   map<int, vector<string> >::value_type(REJECTED_FEMALE, rejectedBecauseFemale),
	   map<int, vector<string> >::value_type(REJECTED_FEMALEISH, rejectedBecauseFemaleish),
	   map<int, vector<string> >::value_type(REJECTED_DRESSCODE, rejectedBecauseDresscode),
	   map<int, vector<string> >::value_type(REJECTED_BLOODYCLOTHES, rejectedBecauseBloodyClothes),
	   map<int, vector<string> >::value_type(REJECTED_DAMAGEDCLOTHES, rejectedBecauseDamagedClothes),
	   map<int, vector<string> >::value_type(REJECTED_SECONDRATECLOTHES, rejectedBecauseSecondRateClothes),
	   map<int, vector<string> >::value_type(REJECTED_WEAPONS, rejectedBecauseWeapons),
	   map<int, vector<string> >::value_type(REJECTED_GUESTLIST, rejectedBecauseGuestList),
	};
	caseRejectionReasons = {
		map<int, vector<string> >::value_type(REJECTED_UNDERAGE, caseREJECTED_UNDERAGE),
	   map<int, vector<string> >::value_type(REJECTED_DRESSCODE, caseREJECTED_DRESSCODE),
	   map<int, vector<string> >::value_type(REJECTED_SMELLFUNNY, caseREJECTED_SMELLFUNNY),
	   map<int, vector<string> >::value_type(REJECTED_BLOODYCLOTHES, caseREJECTED_BLOODYCLOTHES),
	   map<int, vector<string> >::value_type(REJECTED_DAMAGEDCLOTHES, caseREJECTED_DAMAGEDCLOTHES),
	   map<int, vector<string> >::value_type(REJECTED_SECONDRATECLOTHES, caseREJECTED_SECONDRATECLOTHES),
	};
	return true;
}


void processTheUnprocessed(vector<string> &unprocessed, map<short, vector<string> > &processed, map<string, short> string_to_short) {
	int nextHelp = -2;
	vector<string> nextHelpStrings;
	for (string str : unprocessed) {
		if (string_to_short.count(str)) {
			if (nextHelp != -2) {
				processed.insert_or_assign(nextHelp, nextHelpStrings);
			}
			nextHelp = string_to_short[str];
			nextHelpStrings.clear();
		}
		else {
			nextHelpStrings.push_back(str);
		}
	}
	processed.insert_or_assign(nextHelp, nextHelpStrings);
}
void processTheUnprocessed(vector<string> &unprocessed, map<short, string> &processed, map<string, short> string_to_short) {
	int nextHelp = -2;
	string nextHelpString;
	for (string str : unprocessed) {
		if (string_to_short.count(str)) {
			if (nextHelp != -2) {
				processed.insert_or_assign(nextHelp, nextHelpString);
			}
			nextHelp = string_to_short[str];
			//nextHelpStrings.clear();
		}
		else {
			nextHelpString = str;
		}
	}
	processed.insert_or_assign(nextHelp, nextHelpString);
}