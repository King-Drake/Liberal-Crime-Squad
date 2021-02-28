
#include "../includes55.h"
#include "../constStringmisc.h"
void sexdesc(char *str)
{
	strcpy(str, pickrandom(sexdescAcronym).c_str());
}
void sexwho(char *str)
{
	strcpy(str, pickrandom(sexwhoAcronym).c_str());
}
void sexseek(char *str)
{
	strcpy(str, pickrandom(sexseekAcronym).c_str());
}
void sextype(char *str)
{
	strcpy(str, pickrandom(sextypeAcronym).c_str());
}
string sexdesc()
{
	return pickrandom(sexdescAcronym);
}
string sexwho()
{
	return pickrandom(sexwhoAcronym);
}
string sexseek()
{
	return pickrandom(sexseekAcronym);
}
string sextype()
{
	return pickrandom(sextypeAcronym);
}
const char* statename(int i)
{
	if (i < 0 || i >= len(listOfStates)) i = LCSrandom(len(listOfStates));
	return listOfStates[i].data();
}
/* EndGameStatus - converts an integer into a roman numeral for amendments */
string romannumeral(int amendnum)
{
	string roman = "";
	while (amendnum >= 1000)
	{
		amendnum -= 1000;
		(roman += 'M');
	}
	if (amendnum >= 900)
	{
		amendnum -= 900;
		(roman += 'C');
		(roman += 'M');
	}
	if (amendnum >= 500)
	{
		amendnum -= 500;
		(roman += 'D');
	}
	if (amendnum >= 400)
	{
		amendnum -= 400;
		(roman += 'C');
		(roman += 'D');
	}
	while (amendnum >= 100)
	{
		amendnum -= 100;
		(roman += 'C');
	}
	if (amendnum >= 90)
	{
		amendnum -= 90;
		(roman += 'X');
		(roman += 'C');
	}
	if (amendnum >= 50)
	{
		amendnum -= 50;
		(roman += 'L');
	}
	if (amendnum >= 40)
	{
		amendnum -= 40;
		(roman += 'X');
		(roman += 'L');
	}
	while (amendnum >= 10)
	{
		amendnum -= 10;
		(roman += 'X');
	}
	if (amendnum >= 9)
	{
		amendnum -= 9;
		(roman += 'I');
		(roman += 'X');
	}
	if (amendnum >= 5)
	{
		amendnum -= 5;
		(roman += 'V');
	}
	if (amendnum >= 4)
	{
		amendnum -= 4;
		(roman += 'I');
		(roman += 'V');
	}
	while (amendnum >= 1)
	{
		amendnum -= 1;
		(roman += 'I');
	}
	return roman;
}
#ifndef DONT_INCLUDE_SDL
bool oggsupport = true;
Mix_Music* songs[MUSIC_OFF];
bool songsinitialized = false;
int musicmode = MUSIC_OFF;
int previous = MUSIC_OFF;
/* helper function for initsongs() */
void loadsong(int i, const char* filename)
{
	// the reason it prints progress on the screen is because it might be a little slow sometimes so this reassures the user progress is being made
	eraseAlt();
	if (oggsupport)
	{
		mvaddstrAlt(12, 0, CONST_LOADING_OGG_VORBIS_MUSIC + tostring(i + 1) + CONST_SLASH + tostring(MUSIC_OFF) + PARENTHESIS_COLON + artdir + CONST_OGG + filename + CONST_X_OGG);
		mvaddstrAlt(13, 0, string(CONST_WITH) + artdir + CONST_MIDI + filename + CONST_MID_AS_MIDI_FALLBACK);
	}
	else mvaddstrAlt(12, 0, CONST_LOADING_MIDI_MUSIC + tostring(i + 1) + CONST_SLASH + tostring(MUSIC_OFF) + PARENTHESIS_COLON + artdir + CONST_MIDI + filename + CONST_MID);
	refreshAlt();
	if (oggsupport) songs[i] = Mix_LoadMUS((string(artdir) + CONST_OGG + filename + CONST_X_OGG).c_str()); // only attempt loading Ogg if we have Ogg support
	if (!songs[i] || !oggsupport) // it failed to load Ogg Vorbis music or Ogg support doesn't exist, let's try MIDI instead
	{
		if (oggsupport) gamelog.log(string(CONST_SDL_MIXER_FUNCTION_MIX_LOADMUS_FAILED_TO_LOAD) + artdir + CONST_OGG + filename + CONST_X_OGG_COLON + Mix_GetError()); // Ogg Vorbis music failed to load
		songs[i] = Mix_LoadMUS((string(artdir) + CONST_MIDI + filename + CONST_MID).c_str());
	}
	if (!songs[i]) // there was an error with Mix_LoadMUS() when called on the MIDI file
		gamelog.log(string(CONST_SDL_MIXER_FUNCTION_MIX_LOADMUS_FAILED_TO_LOAD) + artdir + CONST_MIDI + filename + CONST_X_MID_ + Mix_GetError()); // MIDI music failed to load
}
#endif // DONT_INCLUDE_SDL
/* initialize SDL, SDL_mixer, and songs */
void MusicClass::init()
{
#ifndef DONT_INCLUDE_SDL
	if (songsinitialized) return; // only initialize once
	if (SDL_Init(SDL_INIT_AUDIO) != 0) // initialize what we need from SDL for audio
	{  // SDL failed to initialize, so log it and exit
		addstrAlt(string(CONST_UNABLE_TO_INITIALIZE_SDL) + SDL_GetError(), gamelog);
		gamelog.nextMessage();
 	pressAnyKey();
		endwinAlt();
		exit(EXIT_FAILURE);
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) != 0) // initialize the audio mixer at 44.1 kHz with a large buffer size, since we're just playing music not sound effects
	{  // SDL_mixer failed to initialize, so log it and exit
		addstrAlt(string(CONST_UNABLE_TO_INITIALIZE_SDL_MIXER) + Mix_GetError(), gamelog);
		gamelog.nextMessage();
 	pressAnyKey();
		SDL_Quit();
		endwinAlt();
		exit(EXIT_FAILURE);
	}
	if ((Mix_Init(MIX_INIT_OGG | MIX_INIT_FLUIDSYNTH)&MIX_INIT_OGG) != MIX_INIT_OGG) // initialize Ogg Vorbis support (and FluidSynth if it's there for better MIDI quality)
	{  // Ogg Vorbis support failed to load, we'll use MIDI instead
		gamelog.log(CONST_OGG_VORBIS_SUPPORT_FAILED_TO_LOAD_MIDI_MUSIC_WILL_BE_USED_INSTEAD_IF_POSSIBLE);
		gamelog.nextMessage();
		oggsupport = false;
	}
	else oggsupport = true; // we have Ogg Vorbis support!
		
	// titlemode.ogg or .mid - Also sprach Zarathustra, introduction by Richard Strauss
	loadsong(MUSIC_TITLEMODE, musicList[MUSIC_TITLEMODE].data()), // load title mode music
																  // newgame.ogg or .mid- The Liberty Bell March by John Philip Sousa
		loadsong(MUSIC_NEWGAME, musicList[MUSIC_NEWGAME].data()), // load new game music
																  // basemode.ogg or .mid - The Stars and Stripes Forever by John Philip Sousa
		loadsong(MUSIC_BASEMODE, musicList[MUSIC_BASEMODE].data()), // load regular base mode music
																	// siege.ogg or .mid- The Planets, 1st Movement Mars by Gustav Holst
		loadsong(MUSIC_SIEGE, musicList[MUSIC_SIEGE].data()), // load base mode while under siege music
															  // activate.ogg or .mid - Piano Sonata #11, 3rd Movement "Rondo Alla Turca" by Wolfgang Amadeus Mozart
		loadsong(MUSIC_ACTIVATE, musicList[MUSIC_ACTIVATE].data()), // load activate Liberals music
																	// sleepers.ogg or .mid - Toccata and Fugue in D Minor, BWV 565 by Johann Sebastian Bach
		loadsong(MUSIC_SLEEPERS, musicList[MUSIC_SLEEPERS].data()), // load activate Sleepers music
																	// stopevil.ogg or .mid - Hungarian Dance #5 by Johannes Brahms (based on the csardas "Bartfai emlek" by Bela Keler)
		loadsong(MUSIC_STOPEVIL, musicList[MUSIC_STOPEVIL].data()), // load go forth to stop evil music
																	// reviewmode.ogg or .mid - Symphony #94, 2nd Movement "Surprise Symphony" by Joseph Haydn
		loadsong(MUSIC_REVIEWMODE, musicList[MUSIC_REVIEWMODE].data()), // load review mode music
																		// liberalagenda.ogg or .mid - Beautiful Dreamer by Stephen Foster
		loadsong(MUSIC_LIBERALAGENDA, musicList[MUSIC_LIBERALAGENDA].data()), // load status of the Liberal agenda music
																			  // disbanded.ogg or .mid - La Cucaracha, a traditional Mexican folk song originally from Spain
		loadsong(MUSIC_DISBANDED, musicList[MUSIC_DISBANDED].data()), // load disbanded music
																	  // finances.ogg or .mid - Minuet in G Major by Christian Petzold (falsely attributed to Johann Sebastian Bach until 1970)
		loadsong(MUSIC_FINANCES, musicList[MUSIC_FINANCES].data()), // load finance report music
																	// cartheft.ogg or .mid - The Ride of the Valkyries by Richard Wanger
		loadsong(MUSIC_CARTHEFT, musicList[MUSIC_CARTHEFT].data()), // load car theft music
																	// elections.ogg or .mid - Habanera from Carmen by Georges Bizet
		loadsong(MUSIC_ELECTIONS, musicList[MUSIC_ELECTIONS].data()), // load elections music
																	  // shopping.ogg or .mid - The Entertainer by Scott Joplin
		loadsong(MUSIC_SHOPPING, musicList[MUSIC_SHOPPING].data()), // load shopping music
																	// sitemode.ogg or .mid - Dance of the Sugar Plum Fairy by Pyotr Ilyich Tchaikovsky
		loadsong(MUSIC_SITEMODE, musicList[MUSIC_SITEMODE].data()), // load site mode music
																	// suspicious.ogg or .mid - Hall of the Mountain King by Edvard Grieg
		loadsong(MUSIC_SUSPICIOUS, musicList[MUSIC_SUSPICIOUS].data()), // load suspicious music
																		// alarmed.ogg or .mid - 5th Symphony, 1st Movement by Ludwig van Beethoven
		loadsong(MUSIC_ALARMED, musicList[MUSIC_ALARMED].data()), // load alarmed music
																  // heavycombat.ogg or .mid - 6th Symphony Pastorale, 4th Movement by Ludwig van Beethoven
		loadsong(MUSIC_HEAVYCOMBAT, musicList[MUSIC_HEAVYCOMBAT].data()), // load massive Conservative response music
																		  // defense.ogg or .mid - Danse Macabre by Camille Saint-Saens
		loadsong(MUSIC_DEFENSE, musicList[MUSIC_DEFENSE].data()), // load escaping/engaging a siege music
																  // conquer.ogg or .mid - Infernal Galop / Can-Can from Orpheus in the Underworld by Jacques Offenbach
		loadsong(MUSIC_CONQUER, musicList[MUSIC_CONQUER].data()), // load success in conquering a siege or safehouse or the CCS music
																  // carchase.ogg or .mid - The William Tell Overture by Gioacchino Antonio Rossini
		loadsong(MUSIC_CARCHASE, musicList[MUSIC_CARCHASE].data()), // load car chase music
																	// footchase.ogg or .mid - The Maple Leaf Rag by Scott Joplin
		loadsong(MUSIC_FOOTCHASE, musicList[MUSIC_FOOTCHASE].data()), // load foot chase music
																	  // InterrogationST.ogg or .mid - Night on Bald Mountain by Modest Mussorgsky
		loadsong(MUSIC_INTERROGATION, musicList[MUSIC_INTERROGATION].data()), // load InterrogationST music
																			  // trial.ogg or .mid - Hungarian Rhapsody #2 by Franz Liszt
		loadsong(MUSIC_TRIAL, musicList[MUSIC_TRIAL].data()), // load trial music
															  // recruiting.ogg or .mid - Dance of the Hours by Amilcare Ponchielli
		loadsong(MUSIC_RECRUITING, musicList[MUSIC_RECRUITING].data()), // load recruiting music
																		// dating.ogg or .mid - The Blue Danube Waltz by Johann Strauss Jr.
		loadsong(MUSIC_DATING, musicList[MUSIC_DATING].data()), // load dating music
																// newspaper.ogg or .mid - Eine Kleine Nachtmusik, 1st Movement by Wolfgang Amadeus Mozart
		loadsong(MUSIC_NEWSPAPER, musicList[MUSIC_NEWSPAPER].data()), // load newspaper music
																	  // lacops.ogg or .mid - The Flight of the Bumblebee by Nikolai Rimsky-Korsakov
		loadsong(MUSIC_LACOPS, musicList[MUSIC_LACOPS].data()), // load LA cops beating black man and getting caught on video music
																// newscast.ogg or .mid - La Marseillaise, The French National Anthem by Claude Joseph Rouget de Lisle
		loadsong(MUSIC_NEWSCAST, musicList[MUSIC_NEWSCAST].data()), // load newscast where smart liberal guest gets some words in edgewise music
																	// glamshow.ogg or .mid - Das Deutschlandlied, The German National Anthem by Joseph Haydn
		loadsong(MUSIC_GLAMSHOW, musicList[MUSIC_GLAMSHOW].data()), // load glamorous TV show about lifestyles of the rich and famous music
																	// anchor.ogg or .mid - I Am the Very Model of a Modern Major-General by Sir Arthur Seymour Sullivan
		loadsong(MUSIC_ANCHOR, musicList[MUSIC_ANCHOR].data()), // load handsome charismatic new Conservative cable news anchor music
																// abort.ogg or .mid - Tarantella Napoletana, a traditional Italian folk song from Naples
		loadsong(MUSIC_ABORT, musicList[MUSIC_ABORT].data()), // load failed partial birth abortion on trashy daytime talk show music
															  // victory.ogg or .mid - The Star-Spangled Banner, The U.S. National Anthem by John Stafford Smith
		loadsong(MUSIC_VICTORY, musicList[MUSIC_VICTORY].data()), // load victory music
																  // defeat.ogg or .mid - Piano Sonata #2, 3rd Movement "Funeral March" by Frederic Francois Chopin
		loadsong(MUSIC_DEFEAT, musicList[MUSIC_DEFEAT].data()), // load defeat music
																// reagainified.ogg or .mid - Dixie, The Confederate National Anthem by Daniel Decatur Emmett
		loadsong(MUSIC_REAGANIFIED, musicList[MUSIC_REAGANIFIED].data()), // load Reaganified music
																		  // stalinized.ogg or .mid - The Soviet (and now Russian) National Anthem by Alexander Vasilyevich Alexandrov
		loadsong(MUSIC_STALINIZED, musicList[MUSIC_STALINIZED].data()), // load Stalinized music
		eraseAlt();
	refreshAlt();
	songsinitialized = true;
#endif // DONT_INCLUDE_SDL
}
/* shut down SDL, SDL_mixer, and songs */
void MusicClass::quit()
{
#ifndef DONT_INCLUDE_SDL
	if (!songsinitialized) return; // only shut down once
	music.play(MUSIC_OFF);
	for (int c = 0; c < MUSIC_OFF; c++) if (songs[c]) Mix_FreeMusic(songs[c]);
	while (Mix_Init(0)) Mix_Quit();
	Mix_CloseAudio();
	SDL_Quit();
	songsinitialized = false;
#endif // DONT_INCLUDE_SDL
}
/* play music specified by a MusicMode */
void MusicClass::play(int _musicmode)
{
#ifndef DONT_INCLUDE_SDL
	if (!songsinitialized) init(); // if it hasn't been initialized already, do it now
	if (_musicmode == MUSIC_CURRENT) return; // keep playing current music if that's what's requested
	if (_musicmode == MUSIC_RANDOM) _musicmode = LCSrandom(MUSIC_OFF); // play a random song if that's what's requested
	if (_musicmode == MUSIC_PREVIOUS) _musicmode = previous; // restore previous setting if that's what's requested
	if (musicmode == _musicmode) return; // already playing the right music
	previous = musicmode; // store previous setting
	musicmode = _musicmode; // set musicmode to input
	Mix_HaltMusic(); // stop any music that we're playing
	if (musicmode < 0 || musicmode >= MUSIC_OFF)
	{
		musicmode = MUSIC_OFF; // just in case we had odd input, make sure we keep track that music is off
		return; // return without playing music
	}
	if (!songs[musicmode]) // there was an error with Mix_LoadMUS() back when it was called on this song
		return; // we can't play music if it isn't loaded, might as well return
	if (Mix_PlayMusic(songs[musicmode], -1) != 0) // start playing the music, and have it loop indefinitely
		gamelog.log(string(CONST_SDL_MIXER_FUNCTION_MIX_PLAYMUSIC_FAILED) + Mix_GetError()); // Music failed to play
	enableIf(isEnabled());
#endif // DONT_INCLUDE_SDL
}
	Interval::Interval() : min(0), max(0) { }
	Interval::Interval(int value) : min(value), max(value) { }
	Interval::Interval(int low, int high) : min(low), max(high) { }
	void Interval::set_interval(int low, int high) { min = low, max = high; }
	// Sets the interval according to a string that is either a number or two
	// number separated by a dash. Returns false and does not change the
	// interval if the given string is not a valid interval.
	// Sets the interval according to a string that is either a number or two
	// number separated by a dash. Returns false and does not change the
	// interval if the given string is not a valid interval.
	bool valid(const string& v);
	bool Interval::set_interval(const string& interval)
	{
		if (!len(interval) ||
			interval.find_first_not_of(CONST_1234567890) != string::npos)
			return false;
		size_t dashpos = interval.find('-', 1);
		if (dashpos == string::npos) // Just a constant.
		{
			if (!valid(interval)) return false;
			max = min = atoi(interval.c_str());
		}
		else
		{
			string smin = interval.substr(0, dashpos), smax = interval.substr(dashpos + 1);
			if (!valid(smin) || !valid(smax)) return false;
			int tmin = atoi(smin.c_str()), tmax = atoi(smax.c_str());
			if (tmin > tmax) return false;
			min = tmin, max = tmax;
		}
		return true;
	}
	int Interval::roll() const { return LCSrandom(max - min + 1) + min; }
	bool valid(const string& v)
	{
		return len(v) &&                       // Blank string is invalid.
			(len(v) != 1 || v[0] != '-') &&        // Just a dash is invalid.
			v.find('-', 1) == string::npos;
	} 
	Ledger::Ledger() : funds(7), total_income(0), total_expense(0)
	{
		for (int i = 0; i<INCOMETYPENUM; i++) income[i] = 0, dailyIncome[i] = 0;
		for (int e = 0; e<EXPENSETYPENUM; e++) expense[e] = 0, dailyExpense[e] = 0;
	}
	class Ledger ledger;
	int Ledger::get_funds() { return funds; }
	void Ledger::force_funds(int amount) { funds = amount; }
	void Ledger::add_funds(int amount, int incometype)
	{
		funds += amount,
			income[incometype] += amount,
			dailyIncome[incometype] += amount,
			total_income += amount;
	}
	void Ledger::subtract_funds(int amount, int expensetype)
	{
		funds -= amount,
			expense[expensetype] += amount,
			dailyExpense[expensetype] += amount,
			total_expense += amount;
	}
	void Ledger::resetMonthlyAmounts()
	{
		for (int i = 0; i<INCOMETYPENUM; i++) income[i] = 0;
		for (int e = 0; e<EXPENSETYPENUM; e++) expense[e] = 0;
	}
	void Ledger::resetDailyAmounts()
	{
		for (int i = 0; i<INCOMETYPENUM; i++) dailyIncome[i] = 0;
		for (int e = 0; e<EXPENSETYPENUM; e++) dailyExpense[e] = 0;
	}
	MusicClass::MusicClass() : enabled(true) { }
	bool MusicClass::isEnabled() { return enabled; }
	void MusicClass::enableIf(bool e)
	{
		enabled = e;
#ifndef DONT_INCLUDE_SDL
		Mix_VolumeMusic(enabled*(MIX_MAX_VOLUME / 2)); // half volume if music enabled, muted if music disabled
#endif // DONT_INCLUDE_SDL
	}




	// Functions removed from elsewhere that require no #include
	// except for enumerators and standard libraries
	// Most of these can be simplified through use of maps and other data structured
	// Which will assist in future additions or changes



	bool sitealarm;
	bool isThereASiteAlarm() {
		return sitealarm;
	}
	void setSiteAlarmOne() {
		sitealarm = true;
	}
	void resetSiteAlarm() {
		sitealarm = false;
	}

	void addCrackhouse(int creaturearray[CREATURENUM]) {
		if (lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2 &&
			lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 50;
		if (endgamestate<ENDGAME_CCS_DEFEATED && endgamestate>ENDGAME_NONE)
			creaturearray[CREATURE_CCS_VIGILANTE] += 5;
	}
	void addJuiceBar(int creaturearray[CREATURENUM]) {
		creaturearray[CREATURE_TEENAGER] += 10;
		creaturearray[CREATURE_JUDGE_LIBERAL] += 1;
		creaturearray[CREATURE_COLLEGESTUDENT] += 10;
		creaturearray[CREATURE_MUSICIAN] += 2;
		creaturearray[CREATURE_MATHEMATICIAN] += 1;
		creaturearray[CREATURE_TEACHER] += 1;
		creaturearray[CREATURE_HSDROPOUT] += 1;
		creaturearray[CREATURE_ENGINEER] += 1;
		creaturearray[CREATURE_FASTFOODWORKER] += 1;
		creaturearray[CREATURE_BAKER] += 1;
		creaturearray[CREATURE_BARISTA] += 1;
		creaturearray[CREATURE_BARTENDER] += 1;
		creaturearray[CREATURE_TELEMARKETER] += 1;
		creaturearray[CREATURE_CARSALESMAN] += 1;
		creaturearray[CREATURE_OFFICEWORKER] += 1;
		creaturearray[CREATURE_MAILMAN] += 1;
		creaturearray[CREATURE_CHEF] += 1;
		creaturearray[CREATURE_NURSE] += 1;
		creaturearray[CREATURE_AMATEURMAGICIAN] += 1;
		creaturearray[CREATURE_HIPPIE] += 6;
		creaturearray[CREATURE_CRITIC_ART] += 1;
		creaturearray[CREATURE_CRITIC_MUSIC] += 1;
		creaturearray[CREATURE_AUTHOR] += 1;
		creaturearray[CREATURE_JOURNALIST] += 1;
		creaturearray[CREATURE_SOCIALITE] += 2;
		creaturearray[CREATURE_PROGRAMMER] += 1;
		creaturearray[CREATURE_RETIREE] += 1;
		creaturearray[CREATURE_PAINTER] += 1;
		creaturearray[CREATURE_SCULPTOR] += 1;
		creaturearray[CREATURE_DANCER] += 1;
		creaturearray[CREATURE_PHOTOGRAPHER] += 1;
		creaturearray[CREATURE_CAMERAMAN] += 1;
		creaturearray[CREATURE_HAIRSTYLIST] += 1;
		creaturearray[CREATURE_FASHIONDESIGNER] += 1;
		creaturearray[CREATURE_CLERK] += 1;
		creaturearray[CREATURE_THIEF] += 1;
		creaturearray[CREATURE_ACTOR] += 1;
		creaturearray[CREATURE_YOGAINSTRUCTOR] += 1;
		creaturearray[CREATURE_MARTIALARTIST] += 1;
		creaturearray[CREATURE_ATHLETE] += 1;
		creaturearray[CREATURE_LOCKSMITH] += 1;
	}
	void addCigarbar(int creaturearray[CREATURENUM], const char sec) {
		if (sec || isThereASiteAlarm())creaturearray[CREATURE_BOUNCER] += 100;
		else creaturearray[CREATURE_BOUNCER] += 10;
		if (sec)creaturearray[CREATURE_GUARDDOG] += 25;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] += 2;
		if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] += 2;
		if (endgamestate<ENDGAME_CCS_DEFEATED && endgamestate>ENDGAME_NONE)
			creaturearray[CREATURE_CCS_VIGILANTE] += 5;

	}
	void addWhitehouse(int creaturearray[CREATURENUM], const char sec) {


		if (sec)creaturearray[CREATURE_SECRET_SERVICE] += 100;
		else creaturearray[CREATURE_SECRET_SERVICE] += 5;
		if (endgamestate<ENDGAME_CCS_DEFEATED && endgamestate>ENDGAME_NONE && exec[EXEC_PRESIDENT] < ALIGN_CONSERVATIVE)
			creaturearray[CREATURE_CCS_ARCHCONSERVATIVE] += 1;
	}
	void addLatteStandOrPark(int creaturearray[CREATURENUM]) {


		if (lawList[LAW_LABOR] < 2)creaturearray[CREATURE_WORKER_FACTORY_NONUNION] += 5;
		if (lawList[LAW_LABOR] >= 0)creaturearray[CREATURE_WORKER_FACTORY_UNION] += 5;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] += 2;
		if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] += 2;
		if (endgamestate<ENDGAME_CCS_DEFEATED && endgamestate>ENDGAME_NONE)
			creaturearray[CREATURE_CCS_VIGILANTE] += endgamestate * 4;
		if (lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 1;
		if (lawList[LAW_POLLUTION] == -2)creaturearray[CREATURE_MUTANT] += 1;
		if (lawList[LAW_POLLUTION] == -2 &&
			lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] += 1;
		else creaturearray[CREATURE_PRISONGUARD] += 1;
	}
	void addVeganCoop(int creaturearray[CREATURENUM]) {


		if (lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 1;
		if (lawList[LAW_POLLUTION] == -2)creaturearray[CREATURE_MUTANT] += 1;
		if (lawList[LAW_POLLUTION] == -2 &&
			lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 2;
	}
	void addInternetCafe(int creaturearray[CREATURENUM]) {

		creaturearray[CREATURE_SCIENTIST_LABTECH] += 5;
		creaturearray[CREATURE_CORPORATE_MANAGER] += 3;
		creaturearray[CREATURE_TEENAGER] += 15;
		creaturearray[CREATURE_LAWYER] += 3;
		creaturearray[CREATURE_COLLEGESTUDENT] += 25;
		creaturearray[CREATURE_MUSICIAN] += 2;
		creaturearray[CREATURE_MATHEMATICIAN] += 1;
		creaturearray[CREATURE_TEACHER] += 5;
		creaturearray[CREATURE_ENGINEER] += 15;
		creaturearray[CREATURE_DOCTOR] += 1;
		creaturearray[CREATURE_BARISTA] += 10;
		creaturearray[CREATURE_CARSALESMAN] += 3;
		creaturearray[CREATURE_OFFICEWORKER] += 15;
		creaturearray[CREATURE_WORKER_SECRETARY] += 5;
		creaturearray[CREATURE_HIPPIE] += 1;
		creaturearray[CREATURE_PROGRAMMER] += 15;
		creaturearray[CREATURE_RETIREE] += 5;
		creaturearray[CREATURE_PAINTER] += 1;
		creaturearray[CREATURE_SCULPTOR] += 1;
		creaturearray[CREATURE_DANCER] += 1;
		creaturearray[CREATURE_PHOTOGRAPHER] += 1;
		creaturearray[CREATURE_CAMERAMAN] += 1;
		creaturearray[CREATURE_CLERK] += 1;
		creaturearray[CREATURE_LOCKSMITH] += 1;

	}
	void addShelter(int creaturearray[CREATURENUM]) {

		if (lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2 &&
			lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 50;
	}
	void addTenement(int creaturearray[CREATURENUM]) {


		if (lawList[LAW_LABOR] < 2)creaturearray[CREATURE_WORKER_FACTORY_NONUNION] += 1;
		if (lawList[LAW_LABOR] >= 0)creaturearray[CREATURE_WORKER_FACTORY_UNION] += 1;
		if (lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2 &&
			lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 5;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] += 1;
		else creaturearray[CREATURE_PRISONGUARD] += 1;
	}
	void addApartment(int creaturearray[CREATURENUM]) {


		if (lawList[LAW_LABOR] < 2)creaturearray[CREATURE_WORKER_FACTORY_NONUNION] = 1;
		if (lawList[LAW_LABOR] >= 0)creaturearray[CREATURE_WORKER_FACTORY_UNION] = 1;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] += 1;
		if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] += 1;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] += 1;
		else creaturearray[CREATURE_PRISONGUARD] += 1;
	}

	void addIntelligence(int creaturearray[CREATURENUM], const char sec) {


		if (sec)creaturearray[CREATURE_AGENT] += 1000;
		else creaturearray[CREATURE_AGENT] += 100;
		if (sec)creaturearray[CREATURE_GUARDDOG] += 450;

	}
	void addArmyBase(int creaturearray[CREATURENUM], const char sec) {

		if (sec)creaturearray[CREATURE_GUARDDOG] += 230;
		if (sec)creaturearray[CREATURE_MILITARYPOLICE] += 100;
	}
	void addSweatShop(int creaturearray[CREATURENUM], const char sec) {


		if (sec)creaturearray[CREATURE_SECURITYGUARD] += 1000;
		else creaturearray[CREATURE_SECURITYGUARD] += 100;
	}
	void addIndustryPolluter(int creaturearray[CREATURENUM], const char sec) {
		if (sec)creaturearray[CREATURE_SECURITYGUARD] += 100;

		if (lawList[LAW_LABOR] == -2)
		{
			creaturearray[CREATURE_WORKER_FACTORY_NONUNION] += 20;
			creaturearray[CREATURE_WORKER_FACTORY_CHILD] += 140;
		}
		else if (lawList[LAW_LABOR] == -1)
		{
			creaturearray[CREATURE_WORKER_FACTORY_NONUNION] += 160;
			creaturearray[CREATURE_WORKER_FACTORY_CHILD] += 1;
		}
		else if (lawList[LAW_LABOR] == 0)
		{
			creaturearray[CREATURE_WORKER_FACTORY_NONUNION] += 80;
			creaturearray[CREATURE_WORKER_FACTORY_UNION] += 80;
		}
		else if (lawList[LAW_LABOR] == 1)
		{
			creaturearray[CREATURE_WORKER_FACTORY_NONUNION] = 50;
			creaturearray[CREATURE_WORKER_FACTORY_UNION] = 110;
		}
		else creaturearray[CREATURE_WORKER_FACTORY_UNION] = 160;
	}
	void addCorpHQ(int creaturearray[CREATURENUM], const char sec) {

		if (sec)creaturearray[CREATURE_GUARDDOG] += 100;
		if (sec)creaturearray[CREATURE_SECURITYGUARD] = 400;
		else creaturearray[CREATURE_SECURITYGUARD] = 40;
	}
	void addCorpHouse(int creaturearray[CREATURENUM], const char sec) {



		if (sec)creaturearray[CREATURE_MERC] = 100;
		if (sec)creaturearray[CREATURE_GUARDDOG] = 50;
		else creaturearray[CREATURE_GUARDDOG] = 5;
	}
	void addMediaAMRadio(int creaturearray[CREATURENUM], const char sec) {


		if (sec)creaturearray[CREATURE_SECURITYGUARD] = 100;
		else creaturearray[CREATURE_SECURITYGUARD] = 10;
	}
	void addMediaCablenews(int creaturearray[CREATURENUM], const char sec) {

		if (sec)creaturearray[CREATURE_SECURITYGUARD] = 100;
		else creaturearray[CREATURE_SECURITYGUARD] = 10;

	}

	void addLaboratoryCosmetics(int creaturearray[CREATURENUM], const char sec) {


		if (sec)creaturearray[CREATURE_SECURITYGUARD] += 100;
		else creaturearray[CREATURE_SECURITYGUARD] += 3;
	}
	void addIndustryNuclear(int creaturearray[CREATURENUM], const char sec) {


		if (sec)creaturearray[CREATURE_SECURITYGUARD] += 100;
		else creaturearray[CREATURE_SECURITYGUARD] += 10;
	}
	void addLaboratoryGenetic(int creaturearray[CREATURENUM], const char sec) {



		if (sec)creaturearray[CREATURE_GUARDDOG] += 25;
		if (sec)creaturearray[CREATURE_SECURITYGUARD] += 100;
		else creaturearray[CREATURE_SECURITYGUARD] += 3;
	}
	void addPoliceStation(int creaturearray[CREATURENUM], const char sec) {



		if (lawList[LAW_LABOR] < 2)creaturearray[CREATURE_WORKER_FACTORY_NONUNION] = 1;
		if (lawList[LAW_LABOR] >= 0)creaturearray[CREATURE_WORKER_FACTORY_UNION] = 1;
		if (sec)creaturearray[CREATURE_COP] += 1000;
		else creaturearray[CREATURE_COP] += 500;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] += 400;
		if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] += 400;
		if (lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_POLLUTION] == -2 &&
			lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 5;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] = 1;
		else creaturearray[CREATURE_PRISONGUARD] = 1;
	}
	void addCourthouse(int creaturearray[CREATURENUM], const char sec) {



		if (sec)creaturearray[CREATURE_COP] = 2000;
		else creaturearray[CREATURE_COP] = 200;
		if (lawList[LAW_LABOR] < 2)creaturearray[CREATURE_WORKER_FACTORY_NONUNION] = 1;
		if (lawList[LAW_LABOR] >= 0)creaturearray[CREATURE_WORKER_FACTORY_UNION] = 1;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] = 80;
		if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] = 80;
		if (lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 1;
		if (lawList[LAW_POLLUTION] == -2)creaturearray[CREATURE_MUTANT] += 1;
		if (lawList[LAW_POLLUTION] == -2 &&
			lawList[LAW_NUCLEARPOWER] == -2)creaturearray[CREATURE_MUTANT] += 2;
		if (lawList[LAW_DEATHPENALTY] == -2 &&
			lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_EDUCATOR] = 1;
		else creaturearray[CREATURE_PRISONGUARD] = 1;
	}
	void addFirestation(int creaturearray[CREATURENUM], const char sec) {


		if (sec)
		{
			if (lawList[LAW_DEATHPENALTY] == -2 &&
				lawList[LAW_POLICEBEHAVIOR] == -2)creaturearray[CREATURE_DEATHSQUAD] += 50;
			else if (lawList[LAW_POLICEBEHAVIOR] <= -1)creaturearray[CREATURE_GANGUNIT] += 50;
			else creaturearray[CREATURE_COP] += 50;
		}
	}

	/* prints a short blurb showing how to page forward */
	string addnextpagestr()
	{
		string output;
		if (interface_pgup == '[')
			output = CLOSING_BRACKET;
		else if (interface_pgup == '.')
			output = CONST_X_SINGLE_COLON;
		else output = CONST_X_PGDN;
		return output + DASH_NEXT;
	}
	/* prints a short blurb showing how to page back */
	string addprevpagestr()
	{
		string output;
		if (interface_pgup == '[')
			output = CONST_X_OPEN_BRACKET;
		else if (interface_pgup == '.')
			output = SEMI_COLON;
		else output = CONST_X_PGUP;
		return output + DASH_PREVIOUS;
	}
	/* prints a long blurb showing how to page forward and back */
	string addpagestr()
	{
		string output;
		if (interface_pgup == '[')
			output = OPEN_CLOSE_BRACKET;
		else if (interface_pgup == '.')
			output = SEMI_COLON_AND_COLON;
		else output = PGUP_PGDN;
		return output + TO_VIEW_OTHER_LIBERAL_PAGES;
	}

	/* daily - returns the number of days in the current month */
	int monthday()
	{
		switch (month)
		{
		case 2: return 28 + (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)); // February
		case 4: // April
		case 6: // June
		case 9: // September
		case 11: return 30; // November
		default: return 31; // January, March, May, July, August, October, & December
		}
	}

	bool populateEncounter(const int type, int creaturearray[CREATURENUM], const char sec) {
		switch (type)
		{
		case SITE_BUSINESS_CRACKHOUSE:
		{
			addCrackhouse(creaturearray);
			break;
		}
		case SITE_BUSINESS_JUICEBAR:
		{
			addJuiceBar(creaturearray);
			break;
		}
		case SITE_BUSINESS_CIGARBAR:
		{
			addCigarbar(creaturearray, sec);
			break;
		}
		case SITE_GOVERNMENT_WHITE_HOUSE:
		{
			addWhitehouse(creaturearray, sec);
			break;
		}
		case SITE_OUTDOOR_PUBLICPARK:
		case SITE_BUSINESS_LATTESTAND:
		{
			addLatteStandOrPark(creaturearray);
			break;
		}
		case SITE_BUSINESS_VEGANCOOP:
		{
			addVeganCoop(creaturearray);
			break;
		}
		case SITE_BUSINESS_INTERNETCAFE:
		{
			addInternetCafe(creaturearray);
			break;
		}
		default:
		case SITE_RESIDENTIAL_SHELTER:
		{
			addShelter(creaturearray);
			break;
		}
		case SITE_RESIDENTIAL_TENEMENT:
		{
			addTenement(creaturearray);
			return true;
		}
		case SITE_RESIDENTIAL_APARTMENT:
		{
			addApartment(creaturearray);
			return true;
		}

		case SITE_LABORATORY_COSMETICS:
		{
			addLaboratoryCosmetics(creaturearray, sec);
			break;
		}
		case SITE_INDUSTRY_NUCLEAR:
		{
			addIndustryNuclear(creaturearray, sec);
			break;
		}
		case SITE_LABORATORY_GENETIC:
		{
			addLaboratoryGenetic(creaturearray, sec);
			break;
		}
		case SITE_GOVERNMENT_POLICESTATION:
		{
			addPoliceStation(creaturearray, sec);
			break;
		}
		case SITE_GOVERNMENT_COURTHOUSE:
		{
			addCourthouse(creaturearray, sec);
			break;
		}
		case SITE_GOVERNMENT_FIRESTATION:
		{
			addFirestation(creaturearray, sec);
			break;
		}

		case SITE_GOVERNMENT_INTELLIGENCEHQ:
		{
			addIntelligence(creaturearray, sec);
			break;
		}
		case SITE_GOVERNMENT_ARMYBASE:
		{
			addArmyBase(creaturearray, sec);
			break;
		}
		case SITE_INDUSTRY_SWEATSHOP:
		{
			addSweatShop(creaturearray, sec);
			break;
		}
		case SITE_INDUSTRY_POLLUTER:
		{
			addIndustryPolluter(creaturearray, sec);
			break;
		}
		case SITE_CORPORATE_HEADQUARTERS:
		{
			addCorpHQ(creaturearray, sec);
			break;
		}
		case SITE_CORPORATE_HOUSE:
		{
			addCorpHouse(creaturearray, sec);
			break;
		}
		case SITE_MEDIA_AMRADIO:
		{
			addMediaAMRadio(creaturearray, sec);
			break;
		}
		case SITE_MEDIA_CABLENEWS:
		{
			addMediaCablenews(creaturearray, sec);
			break;
		}
		}
		return false;

	}

	int bodypartSeverAmount(const int w) {
		int severamount = 100;
		switch (w)
		{
		case BODYPART_HEAD:severamount = 100; break;
		case BODYPART_BODY:severamount = 1000; break;
		case BODYPART_ARM_RIGHT:severamount = 200; break;
		case BODYPART_ARM_LEFT:severamount = 200; break;
		case BODYPART_LEG_RIGHT:severamount = 400; break;
		case BODYPART_LEG_LEFT:severamount = 400; break;
		}
		return severamount;
	}
	std::string burstHitString(int bursthits) {
		if (bursthits < 1) {
			bursthits = 1;
		}
		string output;
		if (bursthits > 5) {
			output += singleSpace + tostring(bursthits);
		}
		else {
			output += numberTimesHit[bursthits - 1];
		}
		if (bursthits > 2) {
			output += CONST_TIMES;
		}
		return output;
	}
	std::string getlaw(int l)
	{
		if (getLawString.count(l)) {
			return getLawString[l];
		}
		else {
			return CONST_SOFTWARE_BUGS;
		}
	}
	std::string cityname()
	{
		return pickrandom(city_names);
	}

	int getLawFromFlag(int type) {
		if (type == LAWFLAG_BURNFLAG) {
			return LAW_FLAGBURNING;
		}
		else if (type == LAWFLAG_HIREILLEGAL) {
			return LAW_IMMIGRATION;
		}
		return 0;
	}
	std::string getlawflag(int type)
	{
		if (getLawFlagStringFull.count(type)) {
			return getLawFlagStringFull[type][lawList[getLawFromFlag(type)]];
		}
		else
			if (getLawFlagString.count(type)) {
				return getLawFlagString[type];
			}
			else {
				return findingBugs;
			}
	}

	/* returns true if the entire site is not open to public */
	char disguisesite(long type)
	{
		switch (type)
		{
		case SITE_LABORATORY_COSMETICS:
		case SITE_LABORATORY_GENETIC:
		case SITE_GOVERNMENT_PRISON:
		case SITE_GOVERNMENT_INTELLIGENCEHQ:
		case SITE_INDUSTRY_SWEATSHOP:
		case SITE_INDUSTRY_POLLUTER:
		case SITE_CORPORATE_HEADQUARTERS:
		case SITE_CORPORATE_HOUSE:
		case SITE_BUSINESS_CIGARBAR:
			return 1;
		}
		return 0;
	}

	/* common - random issue by public interest */
	int randomissue(bool core_only)
	{
		int interest_array[VIEWNUM], total_interest = 0;
		int numviews = core_only ? VIEWNUM - 5 : ((endgamestate >= ENDGAME_CCS_DEFEATED || newscherrybusted < 2) ? VIEWNUM - 1 : VIEWNUM);
		for (int i = 0; i < numviews; i++)
		{
			interest_array[i] = public_interest[i] + total_interest + 25;
			total_interest += public_interest[i] + 25;
		}
		int roll = LCSrandom(total_interest);
		for (int i = 0; i < numviews; i++) if (roll < interest_array[i]) return i;
		return VIEW_MOOD;
	}

	/* fills a string with a proper name */
	void generate_name(char *str, char gender)
	{
		char first[80];
		char last[80];
		generate_name(first, last, gender);
		strcpy(str, first);
		strcat(str, singleSpace.data());
		strcat(str, last);
	}
	string generate_name(char gender) {
		char str[200];
		generate_name(str, gender);
		return str;
	}
	/* get a first and last name for the same person */
	void generate_name(char *first, char *last, char gender)
	{
		do {
			firstname(first, gender);
			strcpy(last, lastname(gender == GENDER_WHITEMALEPATRIARCH).data());
		} while (strcmp(first, last) == 0);
	}
	/* get a first, middle, and last name for the same person */
	void generate_long_name(char *first, char *middle, char *last, char gender)
	{
		// pick either male or female so we can have 75% chance of first and middle names having matching genders
		if (gender == GENDER_NEUTRAL)
			gender = (LCSrandom(2) ? GENDER_MALE : GENDER_FEMALE);
		do {
			firstname(first, gender);
			if (LCSrandom(2)) // middle name is a first name
				firstname(middle, (gender == GENDER_WHITEMALEPATRIARCH || LCSrandom(2) ? gender : GENDER_NEUTRAL)); // 25% chance for middle name of other gender unless white male patriarch
			else // middle name is a last name
				strcpy(middle, lastname(gender == GENDER_WHITEMALEPATRIARCH).data());
			strcpy(last, lastname(gender == GENDER_WHITEMALEPATRIARCH).data());
		} while (strcmp(first, middle) == 0 && strcmp(first, last) == 0 && strcmp(middle, last) == 0);
	}
	string firstname(const char default_gender) {
		string str;
		int roll, nametable;
		// If we don't care if the name is male or female, pick one randomly
		// This ensures gender balance in the names chosen
		char gender;
		if (default_gender == GENDER_NEUTRAL) {
			gender = (LCSrandom(2) ? GENDER_MALE : GENDER_FEMALE);
		}
		else {
			gender = default_gender;
		}
		switch (gender) {
		case GENDER_MALE:
			roll = LCSrandom(len(male_first_names) +
				len(gender_neutral_first_names));

			if (roll >= len(gender_neutral_first_names))
				nametable = GENDER_MALE;
			else
				nametable = GENDER_NEUTRAL;
			break;
		case GENDER_FEMALE:
			roll = LCSrandom(len(female_first_names) +
				len(gender_neutral_first_names));
			if (roll >= len(gender_neutral_first_names))
				nametable = GENDER_FEMALE;
			else
				nametable = GENDER_NEUTRAL;
			break;
		case GENDER_WHITEMALEPATRIARCH:
			nametable = GENDER_WHITEMALEPATRIARCH;
			break;

		}
		switch (nametable) {
		case GENDER_MALE:
			str = pickrandom(male_first_names);
			break;
		case GENDER_FEMALE:
			str = pickrandom(female_first_names);
			break;
		case GENDER_NEUTRAL:
			str = pickrandom(gender_neutral_first_names);
			break;
		case GENDER_WHITEMALEPATRIARCH:
			str = pickrandom(great_white_male_patriarch_first_names);
			break;
		default:
			str = ERROL_DEFAULT_NAME;
			break;
		}
		return str;
	}
	/* gets a random first name */
	void firstname(char *str, char gender)
	{
		strcpy(str, firstname(gender).c_str());
	}
	string lastname(bool archconservative)
		//{{{ Last Name
	{
		string str;
		// For non-Arch-Conservatives, pick from ALL last names
		if (!archconservative)
		{
			// Roll on the number of non-Arch-Conservative last names,
			// plus the number of regular last names
			int roll = LCSrandom(len(regular_last_names) +
				len(archconservative_last_names));
			// Decide whether to use an Arch-Conservative last name
			// or a regular last name
			archconservative = (roll >= len(regular_last_names));
		}
		// Now the archconservative variable might be true even if the function wasn't called that way,
		// but if it WAS called that way it's definitely true... this way non-Arch-Conservatives get
		// random last names out of all the last names, while Arch-Conservatives are limited to their own
		// last names
		if (archconservative)
			str = pickrandom(archconservative_last_names);
		else
			str = pickrandom(regular_last_names);
		return str;
	}


	string isInCustody() {
		char str[200];
		char str2[200];
		generate_name(str, str2);

		string output = str \
			+ singleSpace \
			+ str2 \
			+ CONST_IS_IN_CUSTODY_R \
			+ CONST_WITNESSES_REPORT_THAT \
			+ str2 \
			+ CONST_REMAINED_AT_THE_SCENE_AFTER_THE_SHOOTING_SCREAMING \
			+ CONST_VERSES_OF_THE_BIBLE_AT_THE_STUNNED_ONLOOKERS_SOMEONE \
			+ CONST_CALLED_THE_POLICE_ON_A_CELLPHONE_AND_THEY_ARRIVED_SHORTLY_THEREAFTER \
			+ str2;
		return output;
	}
	string atTheAbortionClinic() {
		string story;
		story += lastname(true) \
			+ CONST_CLINIC_YESTERDAY \
			+ CONST_DR;
		return story;
	}
	string abortionDoctorShot() {

		string story;
		if (lawList[LAW_ABORTION] == -2) story += CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTION_MURDERS_WAS_RUTHLESSLY;
		else if (lawList[LAW_ABORTION] == -1) story += CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ILLEGAL_ABORTIONS_WAS_RUTHLESSLY;
		else if (lawList[LAW_ABORTION] == 0) story += CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_SEMI_LEGAL_ABORTIONS_WAS_RUTHLESSLY;
		else story += CONST_A_DOCTOR_THAT_ROUTINELY_PERFORMED_ABORTIONS_WAS_RUTHLESSLY;

		story += CONST_GUNNED_DOWN_OUTSIDE_OF_THE;

		return story;
	}

	string howCrazyIsKiller() {
		string story;

		if (lawList[LAW_WOMEN] == -2)
		{
			story += CONST_LATER_ADMITTED_TO_BEING_A_ROGUE_FBI_VIGILANTE_HUNTING_DOWN \
				+ CONST_ABORTION_DOCTORS_AS_OPPOSED_TO_ARRESTING_THEM_R;
		}
		else
		{
			story += CONST_SURRENDERED_WITHOUT_A_STRUGGLE_REPORTEDLY_SAYING_THAT_GOD_S_WORK \
				+ CONST_HAD_BEEN_COMPLETED_R;
		}


		return story;
	}

	string newsOnKiller() {
		string story;


		const char gn = pickrandom(maleOrFemale);

		char dstr[200], dstr2[200];
		generate_name(dstr, dstr2, gn);

		story += dstr \
			+ singleSpace \
			+ dstr2;
		char gen[200];
		strcpy(gen, (gn == GENDER_FEMALE ? CONST_HER : CONST_HIS).data());

		story += CONST_WAS_WALKING_TO \
			+ gen;//TODO() Add more variety, not just in the parking lot.
		story += CONST_CAR_WHEN_ACCORDING_TO_POLICE_REPORTS \
			+ CONST_SHOTS_WERE_FIRED_FROM_A_NEARBY_VEHICLE \
			+ dstr2 \
			+ CONST_WAS_HIT \
			+ tostring(LCSrandom(15) + 3) \
			+ CONST_TIMES_AND_DIED_IMMEDIATELY_IN_THE_PARKING_LOT \
			+ CONST_THE_SUSPECTED_SHOOTER;


		story += isInCustody();
		story += howCrazyIsKiller();
		story += singleSpace \
			+ dstr2 \
			+ CONST_IS_SURVIVED_BY \
			+ gen \
			+ singleSpace;

		char spouse = pickrandom(maleOrFemale);
		if (lawList[LAW_GAY] <= 1)
			spouse = (gn == GENDER_FEMALE ? GENDER_MALE : GENDER_FEMALE);

		story += (spouse == GENDER_FEMALE ? CONST_WIFE : CONST_HUSBAND_LOWERCASE) \
			+ CONST_SPACE_AND_SPACE;

		return story;
	}
	string constructVIEW_WOMEN()
	{
		string story;

		story = cityname();
		story += spaceDashSpace;

		story += abortionDoctorShot();

		story += atTheAbortionClinic();
		story += newsOnKiller();

		story += pickrandom(two_to_five) \
			+ CONST_CHILDREN_R;

		return story;
	}

	string getPhraseDrunkDriving() {

		string story;

		switch (LCSrandom(3))
		{
		case 0:
			if (lawList[LAW_FREESPEECH] == -2) story += CONST_THROWING_JUICE_BOXES;
			else story += CONST_THROWING_BEER_BOTTLES;
			break;
		case 1:
			if (lawList[LAW_FREESPEECH] == -2) story += CONST_RELIEVING_THEMSELVES_OUT_THE_WINDOW;
			else if (lawList[LAW_FREESPEECH] == 2) story += CONST_PISSING_OUT_THE_WINDOW;
			else story += CONST_URINATING_OUT_THE_WINDOW;
			break;
		case 2: story += CONST_TAKING_SWIPES; break;
		}

		return story;
	}

	string getPhraseKnownHomosexual() {

		string story;


		if (lawList[LAW_GAY] == -2) story += CONST_A_KNOWN_SEXUAL_DEVIANT_WAS;
		else if (lawList[LAW_GAY] == -1) story += CONST_A_KNOWN_HOMOSEXUAL_WAS;
		else story += CONST_A_HOMOSEXUAL_WAS;


		return story;
	}

	string getPhraseNoEmpathyForHomosexual(const string dstr, const string dstr2) {

		string story;


		if (lawList[LAW_GAY] == -2 && lawList[LAW_FREESPEECH] != -2)
		{
			story += CONST_DESPITE_THE_FACT_THAT \
				+ dstr \
				+ singleSpace \
				+ dstr2 \
				+ CONST_IS_A_KNOWN_FAGGOT;
		}
		else if (lawList[LAW_GAY] == -2)story += CONST_EVEN_THOUGH_BEING_GAY_IS_DEVIANT_AS_WE_ALL_KNOW;
		else story += singleDot;

		return story;
	}
	string constructVIEW_GAY()
	{


		string story;
		story = cityname();
		story += spaceDashSpace;

		char dstr[200], dstr2[200];
		generate_name(dstr, dstr2);

		story += dstr \
			+ singleSpace \
			+ dstr2 \
			+ COMMA_SPACE;


		story += getPhraseKnownHomosexual();

		story += pickrandom(vigilante_murder) \
			+ CONST_HERE_YESTERDAY \
			+ CONST_A_POLICE_SPOKESPERSON_REPORTED_THAT_FOUR_SUSPECTS \
			+ CONST_WERE_APPREHENDED_AFTER_A_HIGH_SPEED_CHASE_THEIR_NAMES \
			+ CONST_HAVE_NOT_YET_BEEN_RELEASED \
			+ ampersandR \
			+ CONST_WITNESSES_OF_THE_FREEWAY_CHASE_DESCRIBED_THE_PICKUP_OF_THE_ALLEGED \
			+ CONST_MURDERERS_SWERVING_WILDLY;

		story += getPhraseDrunkDriving();

		story += CONST_AT_THE_PURSUING_POLICE_CRUISERS \
			+ CONST_THE_CHASE_ENDED_WHEN \
			+ pickrandom(why_chase_ended) \
			+ " " \
			+ CONST_AT_WHICH_POINT_THEY_WERE_TAKEN_INTO_CUSTODY_NOBODY_WAS_SERIOUSLY_INJURED_DURING_THE_INCIDENT \
			+ ampersandR \
			+ CONST_AUTHORITIES_HAVE_STATED_THAT_THEY_WILL_VIGOROUSLY \
			+ CONST_PROSECUTE_THIS_CASE_AS_A_HATE_CRIME_DUE_TO_THE \
			+ CONST_AGGRAVATED_NATURE_OF_THE_OFFENSE;

		story += getPhraseNoEmpathyForHomosexual(dstr, dstr2);

		story += ampersandR;

		return story;
	}
	string constructVIEW_FREESPEECH()
	{

		string story;
		story = cityname();
		story += CONST_A_CHILDREN_S_STORY_HAS_BEEN_REMOVED_FROM_LIBRARIES_HERE_AFTER \
			+ CONST_THE_CITY_BOWED_TO_PRESSURE_FROM_RELIGIOUS_GROUPS \
			+ ampersandR \
			+ CONST_THE_BOOK \
			+ CONST_UNDERSCORE;

		char dstr[200], nstr[200];

		generate_name(nstr, dstr);

		story += nstr \
			+ CONST_UNDERSCORE \
			+ dstr \
			+ CONST_AND_THE \
			+ pickrandom(book_title) \
			+ CONST_UNDERSCORE \
			+ pickrandom(book_title_2) \
			+ CONST_IS_THE_THIRD_IN_AN_IMMENSELY_POPULAR_SERIES_BY \
			+ pickrandom(random_nationality) \
			+ CONST_AUTHOR;

		char c[2] = { 0,0 };

		c[0] = 'A' + LCSrandom(26);

		story += c \
			+ singleDot;

		c[0] = 'A' + LCSrandom(26);

		story += c \
			+ CONST_PERIOD_SPACE;

		strcpy(dstr, lastname().data());

		story += dstr \
			+ CONST_DOT_SPACE \
			+ CONST_ALTHOUGH_THE_SERIES_IS_ADORED_BY_CHILDREN_WORLDWIDE \
			+ CONST_SOME_CONSERVATIVES_FEEL_THAT_THE_BOOKS \
			+ pickrandom(conservative_oppose_book) \
			+ singleSpace \
			+ CONST_IN_THEIR_COMPLAINT_THE_GROUPS_CITED_AN_INCIDENT_INVOLVING;

		switch (LCSrandom(3))
		{
		case 0: story += CONST_A_CHILD_THAT_SWORE_IN_CLASS; break;
		case 1: story += CONST_A_CHILD_THAT_SAID_A_MAGIC_SPELL_AT_HER_PARENTS; break;
		case 2: story += CONST_A_CHILD_THAT \
			+ pickrandom(petty_violence) \
			+ singleSpace \
			+ pickrandom(his_her) \
			+ singleSpace \
			+ pickrandom(older_younger) \
			+ singleSpace \
			+ pickrandom(brother_sister);
			break;
		}

		story += CONST_AS_KEY_EVIDENCE_OF_THE_DARK_NATURE_OF_THE_BOOK \
			+ ampersandR \
			+ CONST_WHEN_THE_DECISION_TO_BAN_THE_BOOK_WAS_ANNOUNCED_YESTERDAY \
			+ CONST_MANY_AREA_CHILDREN_SPONTANEOUSLY_BROKE_INTO_TEARS_ONE_CHILD_WAS \
			+ CONST_HEARD_SAYING_COMMA_QUOTE;

		switch (LCSrandom(2))
		{
		case 0:
			story += CONST_MAMMA_IS \
				+ nstr \
				+ CONST_DEAD;
			break;
		case 1:
			story += CONST_MAMMA_WHY_DID_THEY_KILL \
				+ nstr \
				+ CONST_QUESTION_MARK;
			break;
		}

		story += QUOTATION_MARK \
			+ ampersandR;

		return story;
	}
	string constructVIEW_DEATHPENALTY()
	{

		string story;

		story += statename() \
			+ CONST_AN_INNOCENT_CITIZEN_HAS_BEEN_PUT_TO_DEATH_IN_THE_ELECTRIC_CHAIR;

		char dstr[200], dstr2[200], dstr3[200];

		generate_long_name(dstr, dstr2, dstr3);

		story += dstr \
			+ singleSpace \
			+ dstr2 \
			+ singleSpace \
			+ dstr3 \
			+ CONST_WAS_PRONOUNCED_DEAD_AT \
			+ tostring(LCSrandom(12) + 1) \
			+ CONST_SINGLE_COLON \
			+ tostring(LCSrandom(60)) \
			+ pickrandom(AMorPM) \
			+ CONST_YESTERDAY_AT_THE;

		char jstr[200];

		strcpy(jstr, lastname(true).data());

		story += jstr \
			+ CONST_CORRECTIONAL_FACILITY_R \
			+ singleSpace \
			+ dstr3 \
			+ CONST_WAS_CONVICTED_IN \
			+ tostring(year - LCSrandom(11) - 10) \
			+ CONST_OF_13_SERIAL_MURDERS \
			+ CONST_SINCE_THEN_NUMEROUS_PIECES_OF_EXCULPATORY_EVIDENCE \
			+ CONST_HAVE_BEEN_PRODUCED_INCLUDING;

		switch (LCSrandom(3))
		{
		case 0: story += CONST_A_CONFESSION_FROM_ANOTHER_CONVICT;
			break;
		case 1: story += CONST_A_BATTERY_OF_NEGATIVE_DNA_TESTS;
			break;
		case 2:
			story += CONST_AN_ADMISSION_FROM_A_FORMER_PROSECUTOR_THAT \
				+ dstr3 \
				+ CONST_WAS_FRAMED;
			break;
		}

		story += CONST_THE_STATE_STILL_WENT_THROUGH_WITH_THE_EXECUTION_WITH_A \
			+ CONST_SPOKESPERSON_FOR_THE_GOVERNOR_SAYING \
			+ QUOTATION_MARK;

		switch (LCSrandom(3))
		{
		case 0: story += CONST_LET_S_NOT_FORGET_THE_CONVICT_IS_COLORED_YOU_KNOW_HOW_THEIR_KIND_ARE;
			break;
		case 1:
			story += CONST_THE_CONVICT_IS_ALWAYS_REFERRED_TO_BY_THREE_NAMES \
				+ CONST_ASSASSIN_SERIAL_KILLER_EITHER_WAY_GUILTY \
				+ CONST_END_OF_STORY;
			break;
		case 2: story += CONST_THE_FAMILY_WANTS_CLOSURE_WE_DON_T_HAVE_TIME_FOR_ANOTHER_TRIAL;
			break;
		}

		story += CONST_DOT_QUOTATION_MARK \
			+ ampersandR \
			+ CONST_CANDLELIGHT_VIGILS_WERE_HELD_THROUGHOUT_THE_COUNTRY_LAST_NIGHT_DURING_THE_EXECUTION \
			+ CONST_AND_MORE_EVENTS_ARE_EXPECTED_THIS_EVENING_IF_THERE_IS_A_BRIGHT_SIDE_TO_BE_FOUND_FROM_THIS \
			+ CONST_TRAGEDY_IT_WILL_BE_THAT_OUR_NATION_IS_NOW_EVALUATING_THE_EASE_WITH_WHICH_PEOPLE \
			+ CONST_CAN_BE_PUT_TO_DEATH_IN_THIS_COUNTRY \
			+ ampersandR;

		return story;
	}
	string constructVIEW_INTELLIGENCE()
	{

		string story;
		story += CONST_WASHINGTON_DC_THE_FBI_MIGHT_BE_KEEPING_TABS_ON_YOU \
			+ CONST_THIS_NEWSPAPER_YESTERDAY_RECEIVED_A_COLLECTION_OF_FILES_FROM_A_SOURCE_IN_THE_FEDERAL_BUREAU_OF_INVESTIGATIONS \
			+ CONST_THE_FILES_CONTAIN_INFORMATION_ON_WHICH_PEOPLE_HAVE_BEEN_ATTENDING_DEMONSTRATIONS_ORGANIZING \
			+ CONST_UNIONS_WORKING_FOR_LIBERAL_ORGANIZATIONS_EVEN \
			+ pickrandom(liberalCrime) \
			+ ampersandR \
			+ CONST_MORE_DISTURBINGLY_THE_FILES_MAKE_REFERENCE_TO_A_PLAN_TO \
			+ CONST_DEAL_WITH_THE_UNDESIRABLES_ALTHOUGH_THIS_PHRASE_IS_NOT_CLARIFIED \
			+ ampersandR \
			+ CONST_THE_FBI_REFUSED_TO_COMMENT_INITIALLY_BUT_WHEN_CONFRONTED_WITH_THE_INFORMATION \
			+ CONST_A_SPOKESPERSON_STATED_COMMA_QUOTE \
			+ CONST_WELL_YOU_KNOW_THERE_S_PRIVACY_AND_THERE_S_PRIVACY \
			+ CONST_IT_MIGHT_BE_A_BIT_PRESUMPTIVE_TO_ASSUME_THAT \
			+ CONST_THESE_FILES_DEAL_WITH_THE_ONE_AND_NOT_THE_OTHER \
			+ CONST_YOU_THINK_ABOUT_THAT_BEFORE_YOU_CONTINUE_SLANGING_ACCUSATIONS \
			+ CONST_DOT_QUOTATION_MARK \
			+ ampersandR;
		return story;
	}
	string getPhraseJudgeWithProstitute() {

		string story;
		if (lawList[LAW_FREESPEECH] == -2) {
			story += pickrandom(judge_with_prostitute_no_free_speech);
		}
		else if (lawList[LAW_FREESPEECH] == 2) {
			story += pickrandom(judge_with_prostitute_full_free_speech);
		}
		else {
			story += pickrandom(judge_with_prostitute);
		}


		return story;
	}

	string getPhraseJudgeResigned() {

		string story;


		if (lawList[LAW_FREESPEECH] == -2) story += CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_CIVIL_SERVANT;
		else story += CONST_HAS_RESIGNED_IN_DISGRACE_AFTER_BEING_CAUGHT_WITH_A_PROSTITUTE;

		return story;
	}
	string constructVIEW_JUSTICES()
	{
		string story;
		story = cityname();
		story += CONST_CONSERVATIVE_FEDERAL_JUDGE;

		char dstr[200], dstr2[200];

		generate_name(dstr, dstr2, GENDER_WHITEMALEPATRIARCH);

		story += dstr \
			+ singleSpace \
			+ dstr2;

		story += getPhraseJudgeResigned();

		story += ampersandR \
			+ singleSpace \
			+ dstr2 \
			+ CONST_WHO_ONCE \
			+ pickrandom(crazy_conservative_act) \
			+ CONST_WAS_FOUND_WITH;

		char pstr[200], pstr2[200];
		generate_name(pstr, pstr2);

		story += pstr \
			+ singleSpace \
			+ pstr2 \
			+ CONST_LAST_WEEK_IN_A_HOTEL_DURING_A_POLICE_STING_OPERATION \
			+ CONST_ACCORDING_TO_SOURCES_FAMILIAR_WITH_THE_PARTICULARS \
			+ CONST_WHEN_POLICE_BROKE_INTO_THE_HOTEL_ROOM_THEY_SAW;


		story += getPhraseJudgeWithProstitute();

		story += singleSpace \
			+ pstr2 \
			+ CONST_REPORTEDLY_OFFERED \
			+ pickrandom(bribe_officers) \
			+ CONST_IN_EXCHANGE_FOR_THEIR_SILENCE \
			+ ampersandR \
			+ singleSpace \
			+ dstr2 \
			+ CONST_COULD_NOT_BE_REACHED_FOR_COMMENT_ALTHOUGH_AN_AID_STATED_THAT \
			+ CONST_THE_JUDGE_WOULD_BE_GOING_ON_A_BIBLE_RETREAT_FOR_A_FEW_WEEKS_TO \
			+ CONST_MAKE_THINGS_RIGHT_WITH_THE_ALMIGHTY_FATHER \
			+ ampersandR;

		return story;
	}

	string getPhraseRadioHostLostMind() {

		string story;

		switch (LCSrandom(radio_host_lost_mind.size()))
		{
		case 0:
			story += CONST_LOST \
				+ CONST_HIS; // the AM personality's a white male patriarch
			if (lawList[LAW_FREESPEECH] == 2)story += CONST_GODDAMN_MIND;
			else if (lawList[LAW_FREESPEECH] == -2)story += CONST_GOSH_DARN_MIND;
			else story += CONST_G_DD_MN_MIND;
			break;
		default:
			story += pickrandom(radio_host_lost_mind);
		}

		return story;
	}
	string constructVIEW_AMRADIO()
	{

		string story;
		story = cityname();
		story += CONST_WELL_KNOWN_AM_RADIO_PERSONALITY;

		char dstr[200], dstr2[200];
		generate_name(dstr, dstr2, GENDER_WHITEMALEPATRIARCH);

		story += dstr \
			+ singleSpace \
			+ dstr2 \
			+ CONST_WENT_OFF_FOR_FIFTEEN_MINUTES_IN_AN_INEXPLICABLE_RANT \
			+ CONST_TWO_NIGHTS_AGO_DURING_RADIO \
			+ pickrandom(radio_name) \
			+ singleSpace \
			+ pickrandom(radio_name_2) \
			+ CONST_QUOTATION_PERIOD \
			+ ampersandR \
			+ singleSpace \
			+ dstr2 \
			+ CONST_S_MONOLOGUE_FOR_THE_EVENING_BEGAN_THE_WAY_THAT_FANS \
			+ CONST_HAD_COME_TO_EXPECT_WITH_ATTACKS_ON_LIBERAL_MEDIA \
			+ CONST_DOT_BUT_WHEN_THE_RADIO_ICON_SAID;

		switch (LCSrandom(radio_host_crazy_quote.size()))
		{
		case 0:
			story += CONST_AND_THE_GREATEST_LIVING_EXAMPLE_OF_A_REVERSE_RACIST_IS_THE;
			if (presparty != CONSERVATIVE_PARTY) story += CONST_CURRENT_PRESIDENT; // Limbaugh
			else story += CONST_LIBERAL_MEDIA_ESTABLISHMENT;
			break;
		default:
			story += pickrandom(radio_host_crazy_quote);
			break;
		}

		story += CONST_A_FORMER_FAN_OF_THE_SHOW;

		char nstr[200], nstr2[200];
		generate_name(nstr, nstr2);

		story += nstr \
			+ singleSpace \
			+ nstr2 \
			+ CONST_COMMA_KNEW_THAT_QUOTE \
			+ pickrandom(my_idol) \
			+ CONST_HAD;


		story += getPhraseRadioHostLostMind();

		story += CONST_DOT_AFTER_THAT_IT_GOT_WORSE \
			+ ampersandR \
			+ singleSpace \
			+ dstr2 \
			+ CONST_ISSUED_AN_APOLOGY_LATER_IN_THE_PROGRAM_BUT \
			+ CONST_THE_DAMAGE_MIGHT_ALREADY_BE_DONE \
			+ CONST_ACCORDING_TO_A_POLL_COMPLETED_YESTERDAY \
			+ CONST_FULLY_HALF_OF_THE_HOST_S_MOST_LOYAL_SUPPORTERS; // XXX How many of them switch should
		story += CONST_HAVE_DECIDED_TO_LEAVE_THE_PROGRAM_FOR_SANER; // depend on [LAW_FREESPEECH]
		story += CONST_PASTURES_OF_THESE_MANY_SAID_THAT_THEY_WOULD_BE_SWITCHING_OVER \
			+ CONST_TO_THE_FM_BAND \
			+ ampersandR;

		return story;
	}
	string getSchool(const int schtype, const bool capitalized) {
		return SchoolTypes[schtype][capitalized];
	}

	string getAgeForSchoolStudent(const int schtype) {
		//6->11,10->15,14->19,18->23
		return tostring(6 + (schtype * 4) + LCSrandom(6)); //generate an age that would roughly correspond to the schtype
	}

	string getPhraseKillingSpree() {
		string story;

		if (lawList[LAW_FREESPEECH] == -2) story += CONST_HURTING_SPREE;
		else story += CONST_SHOOTING_RAMPAGE;

		return story;
	}

	string getPhraseKilledSelf() {
		string story;
		if (lawList[LAW_FREESPEECH] == -2)story += CONST_FEEL_DEEPLY_ASLEEP;
		else story += CONST_COMMITTED_SUICIDE;

		return story;
	}

	string getPhraseMowedDown() {
		string story;


		if (lawList[LAW_FREESPEECH] == -2)story += CONST_SCARE;
		else story += CONST_MOW_DOWN;

		return story;
	}

	string getGraphicShootingDetails(const int dg) {

		string story;

		if (lawList[LAW_FREESPEECH] == -2) story += CONST_SCARING;
		else story += CONST_SPRAYING_BULLETS_AT;
		story += CONST_STUDENTS_AND_TEACHERS_INSIDE \
			+ CONST_WHEN_OTHER_STUDENTS_TRIED_TO_WRESTLE_THE_WEAPONS_AWAY_FROM \
			+ (dg == GENDER_FEMALE ? CONST_HER : CONST_HIM_LOWERCASE) \
			+ CONST_THEY_WERE;

		if (lawList[LAW_FREESPEECH] == -2) story += CONST_UNFORTUNATELY_HARMED;
		else story += CONST_SHOT;
		story += CONST_AS_WELL_R \
			+ CONST_WHEN_THE_POLICE_ARRIVED_THE_STUDENT_HAD_ALREADY;

		if (lawList[LAW_FREESPEECH] == -2) story += CONST_HURT_SOME_PEOPLE;
		else
		{
			story += CONST_KILLED \
				+ tostring(2 + LCSrandom(30)) \
				+ CONST_AND_WOUNDED_DOZENS_MORE;
		}


		return story;
	}
	string constructVIEW_GUNCONTROL()
	{

		string story;
		const int schtype = LCSrandom(4);

		story = cityname();

		story += spaceDashSpace \
			+ CONST_A_STUDENT_HAS_GONE_ON_A;

		story += getPhraseKillingSpree();

		story += CONST_AT_A_LOCAL;

		story += getSchool(schtype, false);

		story += CONST_DOT_SPACE;

		char dstr[200], dstr2[200];
		const char dg = pickrandom(maleOrFemale);
		generate_name(dstr, dstr2, dg);

		story += dstr \
			+ singleSpace \
			+ dstr2 \
			+ COMMA_SPACE;

		story += getAgeForSchoolStudent(schtype);
		story += CONST_USED_A_VARIETY_OF_GUNS_TO;
		story += getPhraseMowedDown();
		story += CONST_MORE_THAN_A_DOZEN_CLASSMATES_AND_TWO_TEACHERS_AT;


		story += lastname(true);

		story += singleSpace;

		story += getSchool(schtype, true);

		story += CONST_DOT_SPACE \
			+ dstr2 \
			+ CONST_ENTERED_THE;

		if (schtype != 3) story += CONST_SCHOOL;
		else story += CONST_UNIVERSITY_LOWERCASE;
		story += CONST_WHILE_CLASSES_WERE_IN_SESSION_THEN_SYSTEMATICALLY_STARTED_BREAKING_INTO \
			+ CONST_CLASSROOMS;

		story += getGraphicShootingDetails(dg);

		story += dstr;

		story += getPhraseKilledSelf();

		story += CONST_SHORTLY_AFTERWARDS_R \
			+ CONST_INVESTIGATORS_ARE_CURRENTLY_SEARCHING_THE_STUDENT_S_BELONGINGS_AND_INITIAL \
			+ CONST_REPORTS_INDICATE_THAT_THE_STUDENT_KEPT_A_JOURNAL_THAT_SHOWED \
			+ (dg == GENDER_FEMALE ? CONST_SHE : CONST_HE_LOWERCASE) \
			+ CONST_WAS_DISTURBINGLY_OBSESSED_WITH_GUNS_AND_DEATH_R;

		return story;
	}
	string getPhrasePrisonBook() {
		string story;

		if (!LCSrandom(prison_book_title_2.size())) {
			story;
			if (lawList[LAW_FREESPEECH] == -2) story += CONST_BUMLORD;
			else story += CONST_BUTTLORD;
		}
		else {
			story;
			story += pickrandom(prison_book_title_2);
		}

		return story;
	}
	string getPhraseAIDS() {
		string story;
		if (lawList[LAW_GAY] == -2)story += CONST_GRIDS;// Gay Related Immunodeficiency Syndrome, an obsoleted/politically incorrect name for AIDS.
		else story += CONST_AIDS;

		return story;

	}
	string getPhraseDifficult() {
		string story;


		if (lawList[LAW_FREESPEECH] == -2)story += CONST_DIFFICULT;
		else story += CONST_HELLUVA;

		return story;

	}

	string constructVIEW_PRISONS()
	{

		string story;
		story = cityname();
		story += CONST_A_FORMER_PRISONER_HAS_WRITTEN_A_BOOK_DESCRIBING_IN_HORRIFYING \
			+ CONST_DETAIL_WHAT_GOES_ON_BEHIND_BARS \
			+ CONST_ALTHOUGH_POPULAR_CULTURE_HAS_USED_OR_PERHAPS_OVERUSED_THE \
			+ CONST_PRISON_THEME_LATELY_IN_ITS_OFFERINGS_FOR_MASS_CONSUMPTION_RARELY \
			+ CONST_HAVE_THESE_WORKS_BEEN_AS_POIGNANT_AS;
		char dstr[200], dstr2[200];
		generate_name(dstr, dstr2); // allow either gender (look up 'Orange is the New Black' online to see why)
		story += dstr \
			+ singleSpace \
			+ dstr2 \
			+ CONST_S_NEW_TOUR_DE_FORCE \
			+ pickrandom(prison_book_title) \
			+ CONST_UNDERSCORE;
		story += getPhrasePrisonBook();


		story += CONST_UNDERSCORE_DOT_AMPERSAND_R \
			+ CONST_TAKE_THIS_EXCERPT;//TODO() Add more excerpts, more variety.
		story += CONST_THE_STEEL_BARS_GRATED_FORWARD_IN_THEIR_RAILS \
			+ CONST_COMING_TO_A_HALT_WITH_A_DEAFENING_CLANG_THAT_SAID_IT_ALL \
			+ CONST_I_WAS_TRAPPED_WITH_THEM_NOW_THERE_WERE_THREE_LOOKING_ME_OVER \
			+ CONST_WITH_DARK_GLARES_OF_BARE_LUST_AS_FOOTBALL_PLAYERS_MIGHT_STARE_AT_A_STUPEFIED_DRUNKEN_HELPLESS_TEENAGER \
			+ CONST_MY_SHANK_S_UNDER_THE_MATTRESS_BETTER_TO_BE_BRAVE_AND_FIGHT_OR_CHICKEN_OUT_AND_LET_THEM_TAKE_IT \
			+ CONST_MAYBE_LOSE_AN_EYE_THE_ONE_WAY_MAYBE_CATCH;


		story += getPhraseAIDS();

		story += CONST_THE_OTHER_A;

		story += getPhraseDifficult();

		story += CONST_CHOICE_AND_I_WOULD_ONLY_HAVE_A_FEW_SECONDS_BEFORE_THEY_MADE_IT_FOR_ME \
			+ CONST_DOT_QUOTATION_MARK \
			+ ampersandR;
		return story;
	}

	string constructPositiveEventStory(const short view) {

		string story = "";

		switch (view)
		{
		case VIEW_WOMEN:
		{
			story += constructVIEW_WOMEN();
			break;
		}
		case VIEW_GAY:
		{
			story += constructVIEW_GAY();
			break;
		}
		case VIEW_FREESPEECH:
		{
			story += constructVIEW_FREESPEECH();
			break;
		}
		case VIEW_DEATHPENALTY:
		{
			story += constructVIEW_DEATHPENALTY();

			break;
		}
		case VIEW_INTELLIGENCE:
		{
			story += constructVIEW_INTELLIGENCE();
			break;
		}

		case VIEW_JUSTICES:
		{
			story += constructVIEW_JUSTICES();
			break;
		}
		case VIEW_AMRADIO:
		{
			story += constructVIEW_AMRADIO();
			break;
		}
		case VIEW_GUNCONTROL:
		{
			story += constructVIEW_GUNCONTROL();
			break;
		}
		case VIEW_PRISONS:
		{
			story += constructVIEW_PRISONS();
			break;
		}
		}
		return story;
	}
	string getAnimalTestNation() {
		string story;

		if (lawList[LAW_ANIMALRESEARCH] == 2)
		{
			story += CONST_FROM;
			story += pickrandom(animal_research_country);
			story += CONST_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG;
		}
		else {
			story += CONST_HERE_REPORT_THAT_THEY_HAVE_DISCOVERED_AN_AMAZING_NEW_WONDER_DRUG;
		}


		return story;
	}

	string getPhraseDrugName() {

		string story;
		if (LCSrandom(drug_name.size())) {
			story += pickrandom(drug_name);
		}
		else {
			if (lawList[LAW_FREESPEECH] == -2)story += CONST_BUM_BUM;
			else story += CONST_ANAL;
		}

		return story;
	}

	string getPhraseViagra() {
		string story;
		if (LCSrandom(chimp_drug_impact.size())) {
			story += pickrandom(chimp_drug_impact);
		}
		else {
			if (lawList[LAW_FREESPEECH] == -2)story += CONST_HELPS_CHIMPANZEES_REPRODUCE;
			else story += CONST_CORRECTS_ERECTILE_DYSFUNCTION_IN_CHIMPANZEES;
		}


		return story;
	}
	string constructNegativeVIEW_ANIMALRESEARCH()
	{

		string story = cityname()\
			+ CONST_RESEARCHERS;

		story += getAnimalTestNation();

		story += CONST_CALLED;

		story += getPhraseDrugName();


		story += pickrandom(drug_name_2)\
			+ CONST_THE_DRUG_APPARENTLY;

		story += getPhraseViagra();

		story += CONST_DOT_SPACE \
			+ ampersandR \
			+ CONST_ALONG_WITH_BONOBOS_CHIMPANZEES_ARE_OUR_CLOSEST_COUSINS \
			+ CONST_DOT_SPACE \
			+ CONST_FIELDING_QUESTIONS_ABOUT_THE_ETHICS_OF_THEIR_EXPERIMENTS_FROM_REPORTERS_DURING_A_PRESS_CONFERENCE_YESTERDAY \
			+ CONST_A_SPOKESPERSON_FOR_THE_RESEARCH_TEAM_STATED_THAT_IT_REALLY_ISN_T_SO_BAD_AS_ALL_THAT_CHIMPANZEES_ARE_VERY_RESILIENT_CREATURES\
			+ pickrandom(chimp_drug_horror)\
			+ CONST_WE_HAVE_A_VERY_EXPERIENCED_RESEARCH_TEAM\
			+ CONST_WHILE_WE_UNDERSTAND_YOUR_CONCERNS_ANY_WORRIES_ARE_ENTIRELY_UNFOUNDED\
			+ CONST_I_THINK_THE_MEDIA_SHOULD_BE_FOCUSING_ON_THE_ENORMOUS_BENEFITS_OF_THIS_DRUG\
			+ QUOTATION_MARK\
			+ ampersandR\
			+ CONST_THE_FIRST_PHASE_OF_HUMAN_TRIALS_IS_SLATED_TO_BEGIN_IN_A_FEW_MONTHS\
			+ ampersandR;
		return story;
	}

	string constructNegativeVIEW_POLLUTION() {

		string story = cityname()\
			+ CONST_POLLUTION_MIGHT_NOT_BE_SO_BAD_AFTER_ALL_THE\
			+ pickrandom(family_values_company_name)\
			+ singleSpace\
			+ pickrandom(family_values_company_name_2)\
			+ singleSpace\
			+ pickrandom(family_values_company_name_3)\
			+ CONST_RECENTLY_RELEASED_A_WIDE_RANGING_REPORT_DETAILING_RECENT_TRENDS\
			+ CONST_AND_THE_LATEST_SCIENCE_ON_THE_ISSUE\
			+ CONST_AMONG_THE_MOST_STARTLING_OF_THE_THINK_TANK_S_FINDINGS_IS_THAT\
			+ pickrandom(pollution_consumption)\
			+ CONST_MIGHT_ACTUALLY\
			+ pickrandom(pollution_consumption_2)\
			+ singleDot\
			+ ampersandR\
			+ CONST_WHEN_QUESTIONED_ABOUT_THE_SCIENCE_BEHIND_THESE_RESULTS\
			+ CONST_A_SPOKESPERSON_STATED_THAT\
			+ pickrandom(i_like_polution)\
			+ CONST_YOU_HAVE_TO_REALIZE_THAT\
			+ pickrandom(distrust_liberals)\
			+ CONST_THESE_ISSUES_TO_THEIR_OWN_ADVANTAGE\
			+ CONST_ALL_WE_VE_DONE_IS_INTRODUCED_A_LITTLE_CLARITY_INTO_THE_ONGOING_DEBATE\
			+ CONST_WHY_IS_THERE_CONTENTION_ON_THE_POLLUTION_QUESTION_IT_S_BECAUSE\
			+ CONST_THERE_S_WORK_LEFT_TO_BE_DONE_WE_SHOULD_STUDY_MUCH_MORE\
			+ CONST_BEFORE_WE_URGE_ANY_ACTION_SOCIETY_REALLY_JUST\
			+ CONST_NEEDS_TO_TAKE_A_BREATHER_ON_THIS_ONE_WE_DON_T_SEE_WHY_THERE_S_SUCH_A_RUSH_TO_JUDGMENT_HERE\
			+ ampersandR;
		return story;
	}
	string constructNegativeVIEW_CORPORATECULTURE() {



		string story = cityname()\
			+ CONST_SEVERAL_MAJOR_COMPANIES_HAVE_ANNOUNCED\
			+ CONST_AT_A_JOINT_NEWS_CONFERENCE_HERE_THAT_THEY\
			+ CONST_WILL_BE_EXPANDING_THEIR_WORK_FORCES_CONSIDERABLY\
			+ CONST_DURING_THE_NEXT_QUARTER_OVER_THIRTY_THOUSAND_JOBS\
			+ CONST_ARE_EXPECTED_IN_THE_FIRST_MONTH_WITH\
			+ CONST_TECH_GIANT\
			+ pickrandom(tech_giant_name)\
			+ pickrandom(tech_giant_name_2)\
			+ CONST_INCREASING_ITS_PAYROLLS_BY_OVER_TEN_THOUSAND_WORKERS_ALONE\
			+ CONST_GIVEN_THE_STATE_OF_THE_ECONOMY_RECENTLY_AND_IN\
			+ CONST_LIGHT_OF_THE_TENDENCY\
			+ CONST_OF_LARGE_CORPORATIONS_TO_EXPORT_JOBS_OVERSEAS_THESE_DAYS\
			+ CONST_THIS_WELCOME_NEWS_IS_BOUND_TO_BE_A_PLEASANT_SURPRISE_TO_THOSE_IN_THE_UNEMPLOYMENT_LINES\
			+ CONST_THE_MARKETS_REPORTEDLY_RESPONDED_TO_THE_ANNOUNCEMENT_WITH_MILD_INTEREST\
			+ CONST_ALTHOUGH_THE_DAMPENED_MOVEMENT_MIGHT_BE_EXPECTED_DUE_TO_THE_UNCERTAIN\
			+ CONST_FUTURES_OF_SOME_OF_THE_COMPANIES_IN_THE_TECH_SECTOR_ON_THE_WHOLE_HOWEVER\
			+ CONST_ANALYSTS_SUGGEST_THAT_NOT_ONLY_DOES_THE_EXPANSION_SPEAK_TO_THE_HEALTH\
			+ CONST_OF_THE_TECH_INDUSTRY_BUT_IS_ALSO_INDICATIVE_OF_A_FULL_ECONOMIC_RECOVER_R;
		return story;
	}
	string getPhraseBullshit() {

		string story;
		if (lawList[LAW_FREESPEECH] == -2) {
			story += pickrandom(bullshit_no_free_speech);
		}
		else {
			story += pickrandom(bullshit);
		}


		return story;
	}
	string getCorporationNameAndProduct() {
		string story = pickrandom(gene_corp_name)\
			+ singleSpace\
			+ pickrandom(gene_corp_name_2)\
			+ CONST_PRESENTED_THEIR_PRODUCT\
			+ pickrandom(gene_product_name)\
			+ singleSpace\
			+ pickrandom(gene_product_name_2)\
			+ CONST_DURING_AN_AFTERNOON_POWERPOINT_PRESENTATION\
			+ CONST_ACCORDING_TO_THE_PUBLIC_RELATIONS_REPRESENTATIVE_SPEAKING\
			+ CONST_THIS_AMAZING_NEW_PRODUCT_ACTUALLY\
			+ pickrandom(gene_product_benefit)\
			+ singleDot;

		return story;
	}
	string constructNegativeVIEW_GENETICS()
	{

		string story = cityname()\
			+ CONST_THE_GENETIC_FOODS_INDUSTRY_STAGED_A_MAJOR_EVENT_HERE_YESTERDAY\
			+ CONST_TO_SHOWCASE_ITS_UPCOMING_PRODUCTS_OVER_THIRTY_COMPANIES_SET_UP\
			+ CONST_BOOTHS_AND_GAVE_TALKS_TO_WIDE_EYED_ONLOOKERS\
			+ ampersandR\
			+ CONST_ONE_SUCH_CORPORATION;

		story += getCorporationNameAndProduct();

		story += ampersandR\
			+ CONST_SPOKESPEOPLE_FOR_THE_GM_CORPORATIONS_WERE_UNIVERSAL\
			+ CONST_IN_THEIR_DISMISSAL_OF_THE_CRITICISM_WHICH_OFTEN_FOLLOWS_THE_INDUSTRY\
			+ CONST_ONE_IN_PARTICULAR_SAID\
			+ CONST_LOOK_THESE_PRODUCTS_ARE_SAFE_THAT_THING_ABOUT_THE\
			+ pickrandom(gene_product_cost)\
			+ CONST_IS_JUST_A_LOAD_OF;

		story += getPhraseBullshit();

		story += CONST_WOULD_WE_STAKE_THE_REPUTATION_OF_OUR_COMPANY_ON_UNSAFE_PRODUCTS\
			+ CONST_NO_THAT_S_JUST_RIDICULOUS_I_MEAN_SURE_COMPANIES_HAVE_PUT_UNSAFE_PRODUCTS_OUT\
			+ CONST_BUT_THE_GM_INDUSTRY_OPERATES_AT_A_HIGHER_ETHICAL_STANDARD_THAT_GOES_WITHOUT_SAYING\
			+ QUOTATION_MARK\
			+ ampersandR;
		return story;
	}
	string getPhraseMutilatedCorpse() {
		string story;

		if (lawList[LAW_FREESPEECH] == -2)
			story += CONST_IN_A_BETTER_PLACE;
		else
		{
			story += CONST_DEAD_AND;
			story += pickrandom(mutilated_corpse);
		}

		return story;
	}
	string getPhraseDeathPenalty() {
		string story;

		
		if (lawList[LAW_DEATHPENALTY] == 2)
			story += CONST_LIFE_IMPRISONMENT_IN_THIS_CASE;
		else
			story += CONST_THE_DEATH_PENALTY_IN_THIS_CASE;


		return story;
	}
	string constructNegativeVIEW_DEATHPENALTY()
	{

		char dstr[200], dstr2[200], dstr3[200];
		generate_long_name(dstr, dstr2, dstr3);
		string story = cityname()\
			+ CONST_PERHAPS_PARENTS_CAN_REST_EASIER_TONIGHT\
			+ CONST_THE_AUTHORITIES_HAVE_APPREHENDED_THEIR_PRIMARY_SUSPECT_IN_THE\
			+ CONST_STRING_OF_BRUTAL_CHILD_KILLINGS_THAT_HAS_KEPT_EVERYONE_IN_THE_AREA_ON_EDGE\
			+ CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_HERE\
			+ dstr\
			+ singleSpace\
			+ dstr2\
			+ singleSpace\
			+ dstr3\
			+ CONST_WAS_DETAINED_YESTERDAY_AFTERNOON_REPORTEDLY_IN_POSSESSION_OF\
			+ pickrandom(evidence_of_child_murder)\
			+ CONST_OVER_TWENTY_CHILDREN_IN_THE_PAST_TWO_YEARS_HAVE_GONE_MISSING\
			+ CONST_ONLY_TO_TURN_UP_LATER;

		story += getPhraseMutilatedCorpse();

		story += CONST_SOURCES_SAY_THAT_THE_POLICE_GOT_A_BREAK_IN_THE_CASE_WHEN\
			+ pickrandom(break_in_murder_case)\
			+ singleDot\
			+ ampersandR\
			+ CONST_THE_DISTRICT_ATTORNEY_S_OFFICE_HAS_ALREADY_REPEATEDLY_SAID_IT_WILL_BE\
			+ CONST_SEEKING;
		story += getPhraseDeathPenalty();
		story += ampersandR;
		return story;
	}
	string getPhraseTerroristPlot() {
		string story;


		if (lawList[LAW_FREESPEECH] == -2)story += pickrandom(terrorist_plot_no_free_speech);
		else story += pickrandom(terrorist_plot);

		return story;
	}
	string constructNegativeVIEW_INTELLIGENCE()
	{

		string story;
		story += CONST_WASHINGTON_DC_THE_CIA_ANNOUNCED_YESTERDAY_THAT_IT_HAS_AVERTED_A_TERROR_ATTACK_THAT\
			+ CONST_WOULD_HAVE_OCCURRED_ON_AMERICAN_SOIL\
			+ ampersandR\
			+ CONST_ACCORDING_TO_A_SPOKESPERSON_FOR_THE_AGENCY\
			+ pickrandom(terrorist_group)\
			+ CONST_PLANNED_TO;

		story += getPhraseTerroristPlot();

		story += CONST_HOWEVER_INTELLIGENCE_GARNERED_FROM_DEEP_WITHIN_THE_MYSTERIOUS\
			+ CONST_TERRORIST_ORGANIZATION_ALLOWED_THE_PLOT_TO_BE_FOILED_JUST_DAYS_BEFORE_IT\
			+ CONST_WAS_TO_OCCUR\
			+ ampersandR\
			+ CONST_SPACE_THE_SPOKESMAN_FURTHER_STATED\
			+ CONST_I_WON_T_COMPROMISE_OUR_SOURCES_AND_METHODS_BUT_LET_ME_JUST_SAY\
			+ CONST_THAT_WE_ARE_GRATEFUL_TO_THE_CONGRESS_AND_THIS_ADMINISTRATION_FOR\
			+ CONST_PROVIDING_US_WITH_THE_TOOLS_WE_NEED_TO_NEUTRALIZE_THESE_ENEMIES_OF\
			+ CONST_CIVILIZATION_BEFORE_THEY_CAN_DESTROY_AMERICAN_FAMILIES\
			+ CONST_HOWEVER_LET_ME_ALSO_SAY_THAT_THERE_S_MORE_THAT_NEEDS_TO_BE_DONE\
			+ CONST_THE_HEAD_OF_THE_AGENCY_WILL_BE_SENDING_A_REQUEST_TO_CONGRESS\
			+ CONST_FOR_WHAT_WE_FEEL_ARE_THE_ESSENTIAL_TOOLS_FOR_COMBATING_TERRORISM_IN\
			+ CONST_THIS_NEW_AGE\
			+ QUOTATION_MARK\
			+ ampersandR;
		return story;
	}
	string unreliableTestimony(const char gn, const string dstr3) {

		string gen = (gn == GENDER_FEMALE ? CONST_HER : CONST_HIS);
		string story;
		switch (LCSrandom(7))
		{
		case 0:story = CONST_TEN_YEAR_OLD_EYEWITNESS_TESTIMONY; break;
		case 1:story = gen; story += CONST_GENERAL_FEELING_ABOUT_POLICE_CORRUPTION; break;
		case 2:story = gen; story += CONST_BELIEF_THAT_THE_CRIMES_WERE_A_VAST_RIGHT_WING_CONSPIRACY; break; // Clinton
		case 3:
			story = gen;
			story += CONST_BELIEF_THAT;
			story += dstr3;
			story += CONST_DESERVED_ANOTHER_CHANCE;
			break;
		case 4:
			story = gen;
			story += CONST_PERSONAL_PHILOSOPHY_OF_LIBERTY; break;
		case 5:
			story = gen;
			story += CONST_CLOSE_PERSONAL_FRIENDSHIP_WITH_THE;
			story += dstr3; // I know Charles Manson.
			story += CONST_FAMILY; // Charles Manson was a friend of mine.
			break; // And you, sir, are no Charles Manson!
		case 6:story = gen; story += CONST_CONSULTATIONS_WITH_A_MAGIC_8_BALL; break;
		}
		return story;
	}
	string constructNegativeVIEW_JUSTICES()
	{

		char dstr[200], dstr2[200], dstr3[200];
		generate_long_name(dstr, dstr2, dstr3);
		char jstr[200], jstr2[200];
		const char gn = pickrandom(maleOrFemale);
		generate_name(jstr, jstr2, gn);
		string story = cityname()\
			+ CONST_THE_CONVICTION_OF_CONFESSED_SERIAL_KILLER\
			+ dstr\
			+ singleSpace\
			+ dstr2\
			+ singleSpace\
			+ dstr3\
			+ CONST_WAS_OVERTURNED_BY_A_FEDERAL_JUDGE_YESTERDAY\
			+ CONST_JUSTICE\
			+ jstr\
			+ singleSpace\
			+ jstr2\
			+ CONST_OF_THE_NOTORIOUSLY_LIBERAL_CIRCUIT_OF_APPEALS_HERE\
			+ CONST_MADE_THE_DECISION_BASED_ON;
		story += unreliableTestimony(gn, dstr3);
		char sstr[200];
		strcpy(sstr, lastname().data());
		story += CONST_DESPITE_THE_CONFESSION_OF\
			+ dstr3\
			+ CONST_WHICH_EVEN_JUSTICE\
			+ jstr2\
			+ CONST_GRANTS_WAS_NOT_COERCED_IN_ANY_WAY_R\
			+ CONST_TEN_YEARS_AGO\
			+ dstr3\
			+ CONST_WAS_CONVICTED_OF_THE_NOW_INFAMOUS\
			+ sstr\
			+ CONST_SLAYINGS\
			+ CONST_AFTER_AN_INTENSIVE_MANHUNT\
			+ dstr3\
			+ CONST_WAS_FOUND_WITH_THE_MURDER_WEAPON\
			+ CONST_COVERED_IN_THE_VICTIMS_BLOOD\
			+ dstr3\
			+ CONST_CONFESSED_AND_WAS_SENTENCED_TO_LIFE_SAYING\
			+ CONST_THANK_YOU_FOR_SAVING_ME_FROM_MYSELF\
			+ CONST_I_WOULD_KILL_AGAIN\
			+ CONST_A_SPOKESPERSON_FOR_THE_DISTRICT_ATTORNEY\
			+ CONST_HAS_STATED_THAT_THE_CASE_WILL_NOT_BE_RETRIED_DUE\
			+ CONST_TO_THE_CURRENT_ECONOMIC_DOLDRUMS_THAT_HAVE_LEFT_THE_STATE\
			+ CONST_COMPLETELY_STRAPPED_FOR_CASH_R;
		return story;
	}
	string obsceneAct() {
		string story;

		switch (LCSrandom(5))
		{
		case 0:
			if (lawList[LAW_FREESPEECH] == -2)story += CONST_HAD_CONSENSUAL_INTERCOURSE_IN_THE_MISSIONARY_POSITION;
			else if (lawList[LAW_FREESPEECH] == 2)story += CONST_FUCKED;
			else story += CONST_HAD_INTERCOURSE; break;
		case 1:
			if (lawList[LAW_FREESPEECH] == -2)story += CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_URINATE;
			else if (lawList[LAW_FREESPEECH] == 2)story += CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_TAKE_A_PISS;
			else story += CONST_ENCOURAGED_LISTENERS_TO_CALL_IN_AND_RELIEVE_THEMSELVES; break;
		case 2:
			if (lawList[LAW_FREESPEECH] == 2)story += CONST_SCREAMED_FUCK_POLICE_AND_MORE;
			else if (lawList[LAW_FREESPEECH] == -2)story += CONST_SCREAMED_DARN_THE_POLICE_THOSE_BIG_DUMB_JERKS_I_GOT_A_STUPID_TICKET_THIS_MORNING_AND_I_M_SO_ANGRY;
			else story += CONST_SCREAMED_F_CK_THE_POLICE_THOSE_G_DD_MN_M_TH_F_CK_RS_I_GOT_A_F_CKING_TICKET_THIS_MORNING_AND_I_M_F_CKING_P_SS_D_AS_SH_T; break;
		case 3:
			if (lawList[LAW_FREESPEECH] == -2 && lawList[LAW_WOMEN] == -2)story += CONST_FED_FROM_AN_INDECENT_WOMAN;
			else if (lawList[LAW_FREESPEECH] != -2 && lawList[LAW_WOMEN] == -2)story += CONST_BREASTFED_FROM_AN_EXPOSED_WOMAN;
			else if (lawList[LAW_FREESPEECH] == -2 && lawList[LAW_WOMEN] != -2)story += CONST_FED_FROM_A_WOMAN;
			else story += CONST_BREASTFED_FROM_A_LACTATING_WOMAN; break;
		case 4:
			if (lawList[LAW_FREESPEECH] == -2)story += CONST_HAD_FUN;
			else story += CONST_MASTURBATED; break;
		}

		return story;
	}

	string howManyListeners() {
		string story;


		if (lawList[LAW_FREESPEECH] == -2) story += CONST_THOUSANDS_OF;
		else if (lawList[LAW_FREESPEECH] == -1) story += CONST_SEVERAL_HUNDRED;
		else if (lawList[LAW_FREESPEECH] == 0) story += CONST_HUNDREDS_OF;
		else if (lawList[LAW_FREESPEECH] == 1) story += CONST_DOZENS_OF;
		else story += CONST_SOME;


		return story;
	}

	string listenersFromWhere() {
		string story;

		if (lawList[LAW_FREESPEECH] == -2) story += CONST_ACROSS_THE_NATION;
		else if (lawList[LAW_FREESPEECH] == -1) story += CONST_FROM_ALL_OVER_THE_STATE;
		else if (lawList[LAW_FREESPEECH] == 0) story += CONST_WITHIN_THE_COUNTY;
		else if (lawList[LAW_FREESPEECH] == 1) story += CONST_IN_NEIGHBORING_TOWNS;
		else story += CONST_WITHIN_THE_TOWN;


		return story;

	}
	string constructNegativeVIEW_AMRADIO()
	{ //THIS ONE IS SHORTER BECAUSE OF DOUBLE HEADLINE


		char dstr[200], dstr2[200];
		generate_name(dstr, dstr2, GENDER_WHITEMALEPATRIARCH);


		string story = cityname();

		story += CONST_INFAMOUS_FM_RADIO_SHOCK_JOCK\
			+ dstr\
			+ singleSpace\
			+ dstr2\
			+ CONST_HAS_BROUGHT_RADIO_ENTERTAINMENT_TO_A_NEW_LOW_DURING_YESTERDAY_S\
			+ CONST_BROADCAST_OF_THE_PROGRAM\
			+ dstr\
			+ CONST_APOS_S_SPACE\
			+ pickrandom(fm_radio_name)\
			+ singleSpace\
			+ pickrandom(fm_radio_name_2)\
			+ CONST_QUOTATION_COMMA_SPACE\
			+ dstr2\
			+ CONST_REPORTEDLY;

		story += obsceneAct();

		story += CONST_ON_THE_AIR_ALTHOUGH\
			+ dstr2\
			+ CONST_LATER_APOLOGIZED\
			+ CONST_THE_FCC_RECEIVED;

		story += howManyListeners();

		story += CONST_COMPLAINTS;
		story += CONST_FROM_IRATE_LISTENERS;

		story += listenersFromWhere();

		story += CONST_A_SPOKESPERSON_FOR_THE_FCC;
		story += CONST_STATED_THAT_THE_INCIDENT_IS_UNDER_INVESTIGATION;
		story += ampersandR;
		return story;
	}

	string misterMissMrsOrMs(const int jg2) {
		string tg2;

		if (jg2 == GENDER_FEMALE)
		{
			if (LCSrandom(4) < lawList[LAW_WOMEN] + 2) // 0% chance at lawList[LAW_WOMEN]==-2, 100% chance at lawList[LAW_WOMEN]==2
				(tg2 = CONST_MS);
			else
				(tg2 = (LCSrandom(2) ? CONST_MRS : CONST_MISS_SPACE));
		}
		else (tg2 = CONST_MR);

		return tg2;
	}
	string getPhraseMassShooting() {
		string story;

		if (lawList[LAW_FREESPEECH] == -2) story += CONST_HURTING_SPREE;
		else story += CONST_MASS_SHOOTING;


		return story;
	}
	string getPhraseKillingAttacker() {

		string story;


		if (lawList[LAW_FREESPEECH] == -2) story += CONST_FIREFIGHT_PUTTING_THE_ATTACKER_TO_SLEEP;
		else story += CONST_FIREFIGHT_KILLING_THE_ATTACKER;

		return story;

	}
	string constructNegativeVIEW_GUNCONTROL()
	{
		string story = cityname();
		char jstr[200], jstr2[200], jstr3[200], jstr4[200], jstr5[200];
		const char jg1 = pickrandom(maleOrFemale);
		const char jg2 = pickrandom(maleOrFemale);
		generate_long_name(jstr, jstr2, jstr3, jg1);
		generate_name(jstr4, jstr5, jg2);
		story += CONST_IN_A_SURPRISING_TURN_A;

		story += getPhraseMassShooting();

		story += CONST_WAS_PREVENTED_BY_A_BYSTANDER_WITH_A_GUN\
			+ CONST_AFTER\
			+ jstr\
			+ singleSpace\
			+ jstr2\
			+ CONST_OPENED_FIRE_AT_THE\
			+ jstr3\
			+ singleSpace\
			+ pickrandom(public_place)\
			+ COMMA_SPACE\
			+ jstr4\
			+ singleSpace\
			+ jstr5\
			+ CONST_SPRUNG_INTO_ACTION\
			+ CONST_THE_CITIZEN_PULLED_A_CONCEALED_HANDGUN_AND_FIRED_ONCE_AT_THE_SHOOTER\
			+ CONST_FORCING\
			+ jstr2\
			+ CONST_TO_TAKE_COVER_WHILE_OTHERS_CALLED_THE_POLICE_R\
			+ CONST_INITIALLY;

		string tg2 = misterMissMrsOrMs(jg2);

		story += tg2;
		story += jstr5;
		story += CONST_ATTEMPTED_TO_TALK_DOWN_THE_SHOOTER_BUT_AS;
		story += jstr2;
		story += CONST_BECAME_MORE_AGITATED_THE_HEROIC_CITIZEN_WAS_FORCED_TO_ENGAGE_THE_SHOOTER_IN_A;

		story += getPhraseKillingAttacker();

		story += CONST_BEFORE;
		story += (jg1 == GENDER_FEMALE ? CONST_SHE_LOWERCASE_SPACE : CONST_HE_LOWERCASE_SPACE);
		story += CONST_COULD_HURT_ANYONE_ELSE_R;
		story += CONST_THE_SPOKESPERSON_FOR_THE_POLICE_DEPARTMENT_SAID_WE_D_HAVE_A_YET_ANOTHER;

		story += getPhraseMassShooting();

		story += CONST_IF_NOT_FOR;
		story += tg2;
		story += jstr5;
		story += CONST_S_HEROIC_ACTIONS;
		return story;
	}
	string threatenToKillPolice() {
		string story;
		switch (LCSrandom(4))
		{
		case 0:
			if (lawList[LAW_FREESPEECH] == 2)story += CONST_AH_FUCK_THIS_SHIT_THIS_PUNK_BITCH_IS_FUCKIN_DEAD;
			else if (lawList[LAW_FREESPEECH] == -2)story += CONST_AH_NO_WAY_THIS_POLICE_OFFICER_WILL_BE_HARMED;
			else story += CONST_AH_F_CK_THIS_SH_T_THIS_PUNK_B_TCH_IS_F_CKIN_DEAD;
			break;
		case 1:
			if (lawList[LAW_FREESPEECH] == 2)story += CONST_FUCK_A_MUTHAFUCKIN_BULL_I_M_KILLIN_THIS_PIG_SHIT;
			else if (lawList[LAW_FREESPEECH] == -2)story += CONST_TOO_LATE_I_AM_GOING_TO_HARM_THIS_POLICE_OFFICER;
			else story += CONST_F_CK_A_M_TH_F_CK_N_BULL_I_M_KILLIN_THIS_PIG_SH_T;
			break;
		case 2:
			if (lawList[LAW_FREESPEECH] == 2)story += CONST_WHY_THE_FUCK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG;
			else if (lawList[LAW_FREESPEECH] == -2)story += CONST_WHY_AM_I_TALKIN_TO_YOU_I_D_RATHER_HARM_THIS_POLICE_OFFICER;
			else story += CONST_WHY_THE_F_CK_AM_I_TALKIN_TO_YOU_I_D_RATHER_KILL_THIS_PIG;
			break;
		case 3:
			if (lawList[LAW_FREESPEECH] == 2)story += CONST_IMMA_KILL_ALL_YOU_BITCHES_STARTIN_WITH_THIS_MOTHAFUCKER_HERE;
			else if (lawList[LAW_FREESPEECH] == -2)story += CONST_I_WILL_HARM_ALL_POLICE_OFFICERS_STARTIN_WITH_THIS_ONE_HERE;
			else story += CONST_IMMA_KILL_ALL_YOU_B_TCHES_STARTIN_WITH_THIS_M_TH_F_CK_R_HERE;
			break;
		}
		return story;
	}
	string viciousGuardKilling(const char ggn, const char dgn) {
		string story;

		if (lawList[LAW_FREESPEECH] == -2) story += CONST_HARMED_THE_GUARD;
		else if (lawList[LAW_FREESPEECH] == -1) story += CONST_KILLED_THE_GUARD;
		else switch (LCSrandom(15))
		{
		default:
			story += pickrandom(vicious_killing_of_guard);
			break;
		case 10: story += CONST_SMASHED_THE_GUARD_S_SKULL_WITH_THE_TOILET_SEAT_FROM;
			story += (dgn == GENDER_FEMALE ? CONST_HER : CONST_HIS);
			story += CONST_CELL; break;
		case 11: story += CONST_SHOT_THE_GUARD_WITH;
			story += (ggn == GENDER_FEMALE ? CONST_HER : CONST_HIS);
			story += CONST_OWN_GUN; break;
		case 12: story += CONST_POISONED_THE_GUARD_WITH_DRUGS_SMUGGLED_INTO_THE_PRISON_BY_THE;
			story += (LCSrandom(2) ? CONST_CRIPS : CONST_BLOODS_CAPITALIZED); break;
		case 13: story += CONST_TAKEN_THE_GUARD_TO_THE_EXECUTION_CHAMBER_AND_FINISHED;
			story += (ggn == GENDER_FEMALE ? CONST_HER : CONST_HIM_LOWERCASE);
			story += CONST_OFF; break;
		case 14: story += CONST_SACRIFICED_THE_GUARD_ON_A_MAKESHIFT;
			story += (LCSrandom(2) ? CONST_SATANIC : CONST_NEO_PAGAN_LOWERCASE);
			story += CONST_ALTAR; break;
		}
		return story;
	}

	string getPhraseBeatenToDeath() {

		string story;



		if (lawList[LAW_FREESPEECH] == -2) story += CONST_ALSO_HARMED;
		else  story += CONST_BEATEN_TO_DEATH;

		return story;
	}

	string getPhraseRapist() {
		string story;

		if (lawList[LAW_FREESPEECH] == -2)story += CONST_TWO_WEEKS_AGO_CONVICTED_REPRODUCTION_FIEND;
		else story += CONST_TWO_WEEKS_AGO_CONVICTED_RAPIST;

		return story;
	}
	string constructNegativeVIEW_PRISONS()
	{

		string story = cityname();
		story += CONST_THE_HOSTAGE_CRISIS_AT_THE;
		char jstr[200];
		strcpy(jstr, lastname(true).data());
		story += jstr;
		story += CONST_CORRECTIONAL_FACILITY_ENDED_TRAGICALLY_YESTERDAY_WITH_THE;
		story += CONST_DEATH_OF_BOTH_THE_PRISON_GUARD_BEING_HELD_HOSTAGE_AND;
		const char ggn = pickrandom(maleOrFemale);
		story += (ggn == GENDER_FEMALE ? CONST_HER : CONST_HIS);
		story += CONST_CAPTOR;
		story += ampersandR;

		story += getPhraseRapist();

		char dstr[200], dstr2[200];
		const char dgn = pickrandom(maleOrFemale);
		generate_name(dstr, dstr2, dgn);
		char gstr[200], gstr2[200];
		generate_name(gstr, gstr2, ggn);
		story += dstr\
			+ singleSpace\
			+ dstr2\
			+ CONST_AN_INMATE_AT\
			+ jstr\
			+ CONST_OVERPOWERED\
			+ gstr\
			+ singleSpace\
			+ gstr2\
			+ CONST_AND_BARRICADED\
			+ (dgn == GENDER_FEMALE ? CONST_HERSELF : CONST_HIMSELF_LOWERCASE)\
			+ CONST_WITH_THE_GUARD_IN_A_PRISON_TOWER\
			+ CONST_AUTHORITIES_LOCKED_DOWN_THE_PRISON_AND\
			+ CONST_ATTEMPTED_TO_NEGOTIATE_BY_PHONE_FOR\
			+ tostring(LCSrandom(18) + 5)\
			+ CONST_DAYS_BUT_TALKS_WERE_CUT_SHORT_WHEN\
			+ dstr2\
			+ CONST_REPORTEDLY_SCREAMED_INTO_THE_RECEIVER\
			+ threatenToKillPolice()\
			+ QUOTATION_MARK\
			+ CONST_THE_TOWER_WAS_BREACHED_IN_AN_ATTEMPT_TO_REACH\
			+ CONST_THE_HOSTAGE_BUT\
			+ dstr2\
			+ CONST_HAD_ALREADY\
			+ viciousGuardKilling(ggn, dgn)\
			+ CONST_THE_PRISONER_WAS;

		story += getPhraseBeatenToDeath();

		story += CONST_WHILE_RESISTING_CAPTURE_ACCORDING_TO_A_PRISON_SPOKESPERSON;
		story += ampersandR;
		return story;
	}


	string constructNegativeEventStory(const short view) {
		string story = "";
		switch (view)
		{
		case VIEW_ANIMALRESEARCH:
		{
			story = constructNegativeVIEW_ANIMALRESEARCH();
			break;
		}
		case VIEW_POLLUTION: {
			story = constructNegativeVIEW_POLLUTION();
			break;
		}
		case VIEW_CORPORATECULTURE: {
			story = constructNegativeVIEW_CORPORATECULTURE();
			break;
		}
		case VIEW_GENETICS:
		{
			story = constructNegativeVIEW_GENETICS();
			break;
		}

		case VIEW_DEATHPENALTY:
		{
			story = constructNegativeVIEW_DEATHPENALTY();
			break;
		}

		case VIEW_INTELLIGENCE:
		{
			story = constructNegativeVIEW_INTELLIGENCE();
			break;
		}

		case VIEW_JUSTICES:
		{
			story = constructNegativeVIEW_JUSTICES();
			break;
		}

		case VIEW_AMRADIO:
		{
			story = constructNegativeVIEW_AMRADIO();
			break;
		}
		case VIEW_GUNCONTROL:
		{
			story = constructNegativeVIEW_GUNCONTROL();
			break;
		}
		case VIEW_PRISONS:
		{
			story = constructNegativeVIEW_PRISONS();
			break;
		}
		}
		return story;
	}

	/* news - constructs non-LCS related event stories */
	string constructeventstory(const short view, const char positive)
	{
		if (positive) {
			return constructPositiveEventStory(view);
		}
		else
		{
			return constructNegativeEventStory(view);
		}
	}



	string wasUnableToFind(const string old) {
		return CONST_X_WAS_UNABLE_TO_FIND_A_ + old + CONST_X_BUT_DID_FIND_A_;
	}

	string considerLeaving(const bool sensealarm, const bool alarmon, const string name) {

		if (!sensealarm) return CONST_CALL_IT_A_DAY_PRESS_ENTER;
		else
		{
			if (!alarmon)
			{
				return (CONST_X_ENTER_THE_VIPER_)+(name)+(CONST_X_IS_DETERRED);
			}
			else
			{
				return (CONST_X_ENTER_YES_THE_VIPER_HAS_DETERRED_)+(name)+(singleDot);
			}
		}
	}

	string getDespairString(const bool drugs, const bool restrain, const bool religion) {


		string output;
		switch (LCSrandom(4))
		{
		case 0: output = CONST_SCREAMS_HELPLESSLY_FOR;
			if (drugs) output = CONST_JOHN_LENNON_S_MERCY;
			else if (religion) output = CONST_GOD_S_MERCY;
			else  output = CONST_MOMMY;
			break;
		case 1:
			if (restrain)  output = CONST_GOES_LIMP_IN_THE_RESTRAINTS;
			else  output = CONST_CURLS_UP_IN_THE_CORNER_AND_DOESN_T_MOVE; break;
		case 2:
			if (drugs && !LCSrandom(5))  output = CONST_BARKS_HELPLESSLY;
			else  output = CONST_CRIES_HELPLESSLY; break;
		case 3:
			if (drugs && !LCSrandom(3))  output = CONST_WONDERS_ABOUT_APPLES;
			else  output = CONST_WONDERS_ABOUT_DEATH;
			break;
		}
		return output;
	}

	string victimPrays(const bool onDrugs) {
		if (!onDrugs)
		{
			return pickrandom(prays);
		}
		else
		{
			return pickrandom(prays_on_drugs);
		}
	}

	string getFallsInLove(const string name, const bool restrain) {
		string output;

		switch (LCSrandom(fall_in_love.size() + 1))
		{
		case 0:
			output = CONST_STAMMERS_AND;
			output += restrain ? CONST_TALKS_ABOUT_HUGGING : CONST_HUGS;
			output += name;
			output += singleDot;
			break;
		default:
			int which_love = LCSrandom(fall_in_love.size());
			output = fall_in_love[which_love][0];
			output += name;
			output += fall_in_love[which_love][1];
			break;
		}
		return output;
	}

	string getBadTrip(const string name, const bool restrain, const bool rapport) {

		string output;
		switch (LCSrandom(bad_trip.size() + 2))
		{
		case 0:
			if (rapport)
			{
				output = CONST_BEGS_HITLER_TO_STAY_AND_KILL;
				output += name;
				output += singleDot;
			}
			else
			{
				output = CONST_SCREAMS_FOR;
				output += name;
				output += CONST_TO_STOP_LOOKING_LIKE_HITLER;
			}
			break;
		case 1:
			if (!restrain) output = CONST_CURLS_UP_AND;
			output = CONST_BEGS_FOR_THE_NIGHTMARE_TO_END;
			break;
		default:
			int which_trip = LCSrandom(bad_trip.size());
			output = (bad_trip[which_trip][0]);
			output += name;
			output += (bad_trip[which_trip][1]);
			break;
		}
		return output;
	}
	string outPsychologyCaptor(const string name) {
		string output;
		int which_smarter = LCSrandom(smarter_than_you.size() + smarter_than_you_one_line.size());
		if (which_smarter < smarter_than_you.size()) {
			output = smarter_than_you[which_smarter][0];
			output += name;
			output += smarter_than_you[which_smarter][1];
		}
		else {
			output = pickrandom(smarter_than_you_one_line);
		}
		return output;

	}

	string triedConvertingTheAbused(const string name) {
		string output;
		int which_hatred = LCSrandom(develops_hatred.size() + develops_hatred_one_line.size());
		if (which_hatred < develops_hatred.size())
		{
			output = develops_hatred[which_hatred][0];
			output += name;
			output += develops_hatred[which_hatred][1];
		}
		else {
			output = pickrandom(develops_hatred_one_line);
		}

		return output;
	}

	string feelsBadForAbused(const string name) {

		string output;
		int which_compassion = LCSrandom(interrogater_shows_compassion.size() + interrogater_shows_compassion_one_line.size());
		if (which_compassion < interrogater_shows_compassion.size()) {
			output = interrogater_shows_compassion[which_compassion][0];
			output += name;
			output += interrogater_shows_compassion[which_compassion][1];
		}
		else {
			output = pickrandom(interrogater_shows_compassion_one_line);
		}
		return output;
	}

	string stockholmSyndrome(const string name) {

		string output;
		int which_cling = LCSrandom(cling_to_interrogater.size() + clinging_one_line.size());
		if (which_cling < cling_to_interrogater.size()) {
			output = cling_to_interrogater[which_cling][0];
			output += name;
			output += cling_to_interrogater[which_cling][1];
		}
		else {
			output = pickrandom(clinging_one_line);
		}
		return output;
	}

	string failToBreakReligion(const string a, const string cr) {

		string output;
		int which_cling = LCSrandom(cling_to_religion.size() + cling_to_religion_one_line.size());
		if (which_cling < cling_to_religion.size()) {
			output = a;
			output += cling_to_religion[which_cling][0];
			output += cr;
			output += cling_to_religion[which_cling][1];
		}
		else {
			output = cr;
			output += pickrandom(cling_to_religion_one_line);
		}
		return output;
	}

	string failedToBreakBusiness(const string a, const string cr) {

		string output = cr;
		int which_cling = LCSrandom(cling_to_business.size() + cling_to_business_one_line.size());
		if (which_cling < cling_to_business.size()) {
			output += cling_to_business[which_cling][0];
			output += a;
			output += cling_to_business[which_cling][1];
		}
		else {
			output += pickrandom(cling_to_business_one_line);
		}
		return output;
	}

	string failedToBreakScience(const string a, const string cr) {
		string output = cr;
		int which_cling = LCSrandom(cling_to_science.size() + cling_to_science_one_line.size());
		if (which_cling < cling_to_science.size()) {
			output += cling_to_science[which_cling][0];
			output += a;
			output += cling_to_science[which_cling][1];
		}
		else {
			output += pickrandom(cling_to_science_one_line);
		}
		return output;
	}


	string howGracefulAttack(int handToHand) {


		if (!LCSrandom(handToHand + 1))
			return CONST_PUNCHES;
		else if (!LCSrandom(handToHand))
			return CONST_SWINGS_AT;
		else if (!LCSrandom(handToHand - 1))
			return CONST_GRAPPLES_WITH;
		else if (!LCSrandom(handToHand - 2))
			return CONST_KICKS;
		else if (!LCSrandom(handToHand - 3))
			return CONST_STRIKES_AT;
		else if (!LCSrandom(handToHand - 4))
			return CONST_JUMP_KICKS;
		else return CONST_GRACEFULLY_STRIKES_AT;
	}

	string dismemberingWound(const int w, const int wound) {


		string output = "";

		if (w == BODYPART_HEAD && wound & WOUND_CLEANOFF) {
			output = CONST_CUTTING_IT_OFF;
		}
		else if (w == BODYPART_BODY && wound & WOUND_CLEANOFF) {
			output = CONST_CUTTING_IN_HALF;
		}
		else if (w == BODYPART_HEAD && wound & WOUND_NASTYOFF) {
			output = CONST_BLOWING_IT_APART;
		}
		else if (w == BODYPART_BODY && wound & WOUND_NASTYOFF) {
			output = CONST_BLOWING_IT_IN_HALF;
		}
		else if (wound & WOUND_CLEANOFF) {
			output = CONST_CUTTING_IT_OFF;
		}
		else if (wound & WOUND_NASTYOFF) {
			output = CONST_BLOWING_IT_OFF;
		}

		return output;
	}


	vector<string> printSpecialWounds(const char special[SPECIALWOUNDNUM]) {
		vector<string> woundList;

		if (special[SPECIALWOUND_HEART] != 1)
		{
			woundList.push_back(HEART_PUNCTURED);
		}
		if (special[SPECIALWOUND_RIGHTLUNG] != 1)
		{
			woundList.push_back(R_LUNG_COLLAPSED);
		}
		if (special[SPECIALWOUND_LEFTLUNG] != 1)
		{
			woundList.push_back(L_LUNG_COLLAPSED);
		}
		if (special[SPECIALWOUND_NECK] != 1)
		{
			woundList.push_back(BROKEN_NECK);
		}
		if (special[SPECIALWOUND_UPPERSPINE] != 1)
		{
			woundList.push_back(BROKEN_UP_SPINE);
		}
		if (special[SPECIALWOUND_LOWERSPINE] != 1)
		{
			woundList.push_back(BROKEN_LW_SPINE);
		}
		if (special[SPECIALWOUND_RIGHTEYE] != 1)
		{
			woundList.push_back(NO_RIGHT_EYE);
		}
		if (special[SPECIALWOUND_LEFTEYE] != 1)
		{
			woundList.push_back(NO_LEFT_EYE);
		}
		if (special[SPECIALWOUND_NOSE] != 1)
		{
			woundList.push_back(NO_NOSE);
		}
		if (special[SPECIALWOUND_TONGUE] != 1)
		{
			woundList.push_back(NO_TONGUE);
		}
		if (special[SPECIALWOUND_TEETH] != TOOTHNUM)
		{
			if (special[SPECIALWOUND_TEETH] == 0)woundList.push_back(NO_TEETH);
			else if (special[SPECIALWOUND_TEETH] == TOOTHNUM - 1)woundList.push_back(MISSING_TOOTH);
			else if (special[SPECIALWOUND_TEETH] < TOOTHNUM)woundList.push_back(MISSING_TEETH);
		}
		if (special[SPECIALWOUND_LIVER] != 1)
		{
			woundList.push_back(LIVER_DAMAGED);
		}
		if (special[SPECIALWOUND_RIGHTKIDNEY] != 1)
		{
			woundList.push_back(R_KIDNEY_DAMAGED);
		}
		if (special[SPECIALWOUND_LEFTKIDNEY] != 1)
		{
			woundList.push_back(L_KIDNEY_DAMAGED);
		}
		if (special[SPECIALWOUND_STOMACH] != 1)
		{
			woundList.push_back(STOMACH_INJURED);
		}
		if (special[SPECIALWOUND_SPLEEN] != 1)
		{
			woundList.push_back(BUSTED_SPLEEN);
		}
		if (special[SPECIALWOUND_RIBS] != RIBNUM)
		{
			if (special[SPECIALWOUND_RIBS] == 0)woundList.push_back(ALL_RIBS_BROKEN);
			else if (special[SPECIALWOUND_RIBS] == RIBNUM - 1)woundList.push_back(BROKEN_RIB);
			else if (special[SPECIALWOUND_RIBS] < RIBNUM)woundList.push_back(BROKEN_RIBS);
		}
		return woundList;
	}