

//////////////////////////////////////////////////////////////////////////////////////////
//                                                                                      //
//Copyright (c) 2002,2003,2004 by Tarn Adams                                            //
//                                                                                      //
//////////////////////////////////////////////////////////////////////////////////////////
//This file is part of Liberal Crime Squad.                                             //
//                                                                                      //
//      Liberal Crime Squad is free software; you can redistribute it and/or modify     //
//      it under the terms of the GNU General Public License as published by            //
//      the Free Software Foundation; either version 2 of the License, or               //
//      (at your option) any later version.                                             //
//                                                                                      //
//      Liberal Crime Squad is distributed in the hope that it will be useful,          //
//      but WITHOUT ANY WARRANTY; without even the implied warranty of                  //
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the                  //
//      GNU General Public License for more details.                                    //
//                                                                                      //
//      You should have received a copy of the GNU General Public License               //
//      along with Liberal Crime Squad; if not, write to the Free Software              //
//      Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA   02111-1307   USA     //
//////////////////////////////////////////////////////////////////////////////////////////
#include "includes38.h"
#include "constStringgame.h"
#include <time.h>
void mainOne() {
	init_console(); // do this FIRST
					//start curses
	initscrAlt();
	gamelog.initialize(GAMELOG_FILEPATH, OVERWRITE_GAMELOG, NEWLINEMODE_GAMELOG); //Initialize the gamelog (and also initialize artdir and homedir)
	title_screen::getInstance();
	CreaturePool::getInstance();
	LocationsPool::getInstance();
}
void mainTwo() {
	time_t t = time(0);
	struct tm *now = localtime(&t); //Do not need to deallocate this. Statically allocated by system
	char datetime[41];
	sprintf(datetime, "ÄÄÄÄÄÄÄÄÄ%iÄ%02iÄ%02i %02i:%02i:%02iÄÄÄÄÄÄÄÄÄ\n\n\n",
		now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec); //YYYY-MM-DD HH:MM:SS format
	gamelog.log(string("\n\n\nÄÄÄÄÄÄÄÄÄÄ PROGRAM STARTED ÄÄÄÄÄÄÄÄÄÄ\n") + datetime);
}
void mainThree() {
	music.play(MUSIC_TITLEMODE); // initialize music and play title mode song (do this BEFORE displaying anything on the screen, but AFTER initializing artdir and homedir)
								 // set window title
	char wtitle[50];
	strcpy(wtitle, CONST_LIBERAL_CRIME_SQUAD);
	strcat(wtitle, PACKAGE_VERSION_STR.c_str());
	set_title(wtitle);
}

int oldMapMode = 0; // -1 if we're using the old map generation functions.
void mainFour() {
	noechoAlt();
	//initialize curses color
	start_colorAlt();
	initMainRNG();
	//initialize the array of color pairs
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 && j == 0)
			{
				init_pairAlt(7 * 8, 0, 0);
				continue;
			}
			if (i == 7 && j == 0) continue;
			init_pairAlt(i * 8 + j, i, j);
		}
	//turns off cursor
	curs_setAlt(0);
	//begin the game loop
	keypadAlt(TRUE);
	raw_outputAlt(TRUE);
	//Loading Graphics...
	loadgraphics();
	//Loading Init File Options...
	loadinitfile();
	//Loading sitemaps.txt...
	oldMapMode = !readConfigFile(CONST_SITEMAPS_TXT); // load site map data
	if (oldMapMode)
	{
		addstrAlt(failedToLoadSitemaps, gamelog);
		gamelog.nextMessage();
		pressAnyKey();
	}
	//Setting initial game data...
}
void mainFive() {
	//Initialize sorting choices.
	for (int s = 0; s < SORTINGCHOICENUM; s++)
		activesortingchoice[s] = SORTING_NONE;
	for (int v = 0; v < VIEWNUM; v++)
	{
		attitude[v] = 30 + LCSrandom(25);
		public_interest[v] = 0;
		background_liberal_influence[v] = 0;
	}
	attitude[VIEW_LIBERALCRIMESQUAD] = 0;
	attitude[VIEW_LIBERALCRIMESQUADPOS] = 5;
	//attitude[VIEW_POLITICALVIOLENCE]=5;
	if (REVOLUTIONNOW) {
		for (int v = 0; v < VIEWNUM; v++)
			attitude[v] = 100;
	}
	if (SHITLAWS) {
		for (int l = 0; l < LAWNUM; l++) { lawList[l] = -2; }
	}
	else
		if (PERFECTLAWS) {
			for (int l = 0; l < LAWNUM; l++) { lawList[l] = 2; }
		}
		else {
			lawList[LAW_ABORTION] = 1;
			lawList[LAW_ANIMALRESEARCH] = -1;
			lawList[LAW_POLICEBEHAVIOR] = -1;
			lawList[LAW_PRIVACY] = -1;
			lawList[LAW_DEATHPENALTY] = -1;
			lawList[LAW_NUCLEARPOWER] = -1;
			lawList[LAW_POLLUTION] = -1;
			lawList[LAW_LABOR] = 0;
			lawList[LAW_GAY] = 1;
			lawList[LAW_CORPORATE] = 0;
			lawList[LAW_FREESPEECH] = 0;
			lawList[LAW_FLAGBURNING] = 1;
			lawList[LAW_GUNCONTROL] = -1;
			lawList[LAW_TAX] = 0;
			lawList[LAW_WOMEN] = 1;
			lawList[LAW_CIVILRIGHTS] = 1;
			lawList[LAW_DRUGS] = -1;
			lawList[LAW_IMMIGRATION] = 0;
			lawList[LAW_ELECTIONS] = 0;
			lawList[LAW_MILITARY] = -1;
			lawList[LAW_PRISONS] = 0;
			lawList[LAW_TORTURE] = -1;
		}
}
const string blankString = "";
string fixLineSpecialCharacter(char * toFix) {
	string str = blankString;
	for (int i = 0; i < len(toFix); i++) {
		bool special = (static_cast<int> (toFix[i])) == -61;
		if (special) {
			i++;
			char c;
			switch (toFix[i]) {
			case -87: // 'é'
				c = (char)0x82;
				break;
			case -74: // 'ö'
				c = (char)0x94;
				break;
			case -95: // 'á'
				c = (char)0xa0;
				break;
			case -83: // 'í'
				c = (char)0xa1;
				break;
			case -77: // 'ó'
				c = (char)0xa2;
				break;
			case -70: // 'ú'
				c = (char)0xa3;
				break;
			case (int) '¼':
				// 'ü'
				c = (char)0x81;
				break;
			case (int) '«':
				// 'ë'
				c = (char)0x89;
				break;
			case (int) '²':
				// 'ò'
				c = (char)0x95;
				break;
			case (int) '¢':
				// 'â'
				c = (char)0x83;
				break;
			default:
				c = toFix[i];
				break;
			}
			str += c;
		}
		else if (toFix[i] == 'ô') {
			str += (char)0x93;
			//str += 'ô';
		}
		//else if (toFix[i] == 'Â') {
		//	oem 437 does not have this character
		//	str += 'Â';
		//}
		else if (toFix[i] == '¢') {
			str += (char)0x9b;
			//str += '¢';
		}
		else {
			str += toFix[i];
		}
	}
	return str;
}
bool isThisNotComment(char* currentLine) {
	return currentLine[0] != '#' && currentLine[1] != '#';
}
// populate_from_text extracts plaintext and puts it in a two dimensional vector of strings.
// returns true if file loads, false if not.
bool populate_from_txt(vector< vector<string> >& types, const string& fileName, const int dimension)
{
	types.clear();
	const int line_length = 2048;
	bool success = false;
	std::ifstream txtFile;
	txtFile.open(string(artdir) + fileName);
	if (txtFile.fail()) {
		std::cout << failedToLoad + fileName + CONST_EXCLAMATION_POINT << std::endl;
		pressAnyKey();
	}
	else {
		while (!txtFile.eof()) {
			char currentLine[line_length];
			txtFile.getline(currentLine, line_length);
			const bool notComment = isThisNotComment(currentLine);
			if (notComment) {
				vector<string> line;
				line.push_back(currentLine);
				for (int i = 0; i < dimension - 1 && !txtFile.eof(); i++) {
					// whether the line is not a comment, and is also the line whose contents are optional
					// Testing until obtain proper data from file
					txtFile.getline(currentLine, line_length);
					strcpy(currentLine, fixLineSpecialCharacter(currentLine));
					line.push_back(currentLine);
					if (!isThisNotComment(currentLine)) {
						std::cout << CONST_COMMENT_FOUND << std::endl << currentLine << std::endl;
						pressAnyKey();
					}
				}
				types.push_back(line);
			}
		}
	}
	success = types.size() > 0;
	if (!success) {
		addstrAlt(CONST_FILE_ERROR + fileName);
		pressAnyKey();
	}
	return success;
}
bool populate_from_txt(vector<string> & types, const string& fileName)
{
	types.clear();
	const int line_length = 2048;
	bool success = false;
	std::ifstream txtFile;
	txtFile.open(string(artdir) + fileName);
	if (txtFile.fail()) {
		std::cout << failedToLoad + fileName + CONST_EXCLAMATION_POINT << std::endl;
		pressAnyKey();
	}
	else {
		std::cout << std::endl;
		while (!txtFile.eof()) {
			char currentLine[line_length];
			txtFile.getline(currentLine, line_length);
			const bool notComment = (currentLine[0] && currentLine[0] != '#');
			if (notComment) {
				strcpy(currentLine, fixLineSpecialCharacter(currentLine));
				types.push_back(currentLine);
			}
		}
	}
	success = types.size() > 0;
	if (!success) {
		addstrAlt(CONST_FILE_ERROR + fileName);
		pressAnyKey();
	}
	return success;
}
bool initialize_more_incomplete_txt();
bool initialize_txt();
bool initialize_txt() {
	vector<vector<file_and_text_collection> > vast_text_collection = {
	activate_text_file_collection,
	activities_text_file_collection,
	baseactions_text_file_collection,
	chase_text_file_collection,
	common_text_file_collection,
	creature_text_file_collection,
	creaturetypes_text_file_collection,
	date_text_file_collection,
	endgame_text_file_collection,
	externally_stored_data_text_file_collection,
	fighty_text_file_collection,
	get_names_text_file_collection,
	globals_text_file_collection,
	interrogate_text_file_collection,
	justice_text_file_collection,
	liberl_agenda_text_file_collection,
	locations_text_file_collection,
	locationspool_text_file_collection,
	majorevent_text_file_collection,
	map_specials_text_file_collection,
	misc_activities_text_file_collection,
	misc_text_file_collection,
	names_text_file_collection,
	newgame_file_collection,
	politics_text_file_collection,
	talk_file_collection,
	//	text_file_collection,
		title_screen_text_files,
		reviewmode_text_file_collection,
		siege_text_file_collection,
		stealth_text_file_collection,
	};
	bool loaded = true;

	for (vector<file_and_text_collection> file : vast_text_collection) {
		for (file_and_text_collection f : file) {
			if (f.superCollection) {
				loaded &= populate_from_txt(*f.super_collection, f.fileName, f.dimensions);
				//loaded &= f.super_collection->size() > 0; this test is redundant, populate_from_txt already does it
				//the gamecrash from when namelists are empty was not detected.
			}
			else {
				loaded &= populate_from_txt(*f.collection, f.fileName);
				//loaded &= f.collection->size() > 0;
			}
		}
	}
	if (!loaded) {
		addstrAlt(CONST_FILE_ERROR_INITIATEINCOMPLETETEXT);
		pressAnyKey();
	}
	else {
		loaded &= initialize_more_incomplete_txt();
		if (!loaded) {
			addstrAlt(CONST_FILE_ERROR_INITIATEMOREINCOMPLETETEXT);
			pressAnyKey();
		}
		
	}
	return loaded;
}
void initialize_debug_defines() {
	string fileName = CONST_DEBUG_DEFINES_TXT;
	std::ifstream txtFile;
	txtFile.open(string(artdir) + fileName);
	//int debug_codes = 0;
	if (txtFile.fail()) {
		// debug file not found, don't do anything
	}
	else {
		clearAlt();
		int y = 0;
		while (!txtFile.eof()) {
			char currentLine[800];
			txtFile.getline(currentLine, 800);
			const bool notComment = isThisNotComment(currentLine);
			if (notComment) {
				for (pointerAndString p : debug_defines) {
					if (currentLine == p.fileName) {
						*(p.super_collection) = true;
						mvaddstrAlt(y++, 0, debugCode + p.fileName + ACTIVATED);
					}
				}
			}
		}
		if (DISPLAYDEBUG) {
			pressAnyKey();
		}
	}
}
void initiateSenate() {
	for (int s = 0; s < SENATENUM; s++)
	{
		if (s < 25) senate[s] = -2;
		else if (s < 60) senate[s] = -1;
		else if (s < 80) senate[s] = 0;
		else if (s < 95) senate[s] = 1;
		else senate[s] = 2;
	}
}
void initiateHouse() {
	for (int h = 0; h < HOUSENUM; h++)
	{
		if (h < 50) house[h] = -2;
		else if (h < 250) house[h] = -1;
		else if (h < 350) house[h] = 0;
		else if (h < 400) house[h] = 1;
		else house[h] = 2;
	}
}
void initiateCourt() {
	for (int c = 0; c < COURTNUM; c++)
	{
		if (c < 3) court[c] = -2;
		else if (c < 5) court[c] = -1;
		else if (c < 5) court[c] = 0;
		else if (c < 8) court[c] = 1;
		else court[c] = 2;
		do
		{
			fullName fn;
			if (court[c] == -2) {
				fn = generate_long_name(GENDER_WHITEMALEPATRIARCH);
			}
			else {
				fn = generate_long_name();
			}
			strcpy(courtname[c], (fn.first + " " + fn.last).data());
		} while (len(courtname[c]) > 20);
	}
}
void initiateExec() {
	for (int e = 0; e < EXECNUM; e++)
	{
		exec[e] = -2;
		fullName fn = generate_long_name(GENDER_WHITEMALEPATRIARCH);
		strcpy(execname[e], (fn.first + " " + fn.last).data());
	}
}
void mainSix() {
	initiateSenate();
	initiateHouse();
	initiateCourt();
	initiateExec();

	initOtherRNG(attorneyseed);
	strcpy(lcityname, cityname());
}
int main(int argc, char* argv[])
{
	mainOne();
	mainTwo();
	initialize_debug_defines();
	bool xml_loaded_ok = initialize_txt();
	if (!xml_loaded_ok) {
		mvaddstrAlt(0, 0, CONST_UNSPECIFIED_ERROR_WITH_CUSTOM_TEXT);
		pressAnyKey();
	}
	mainThree();
	mainFour();
	mainFive();
	mainSix();
	// Main Loop
	if (!mainSeven(xml_loaded_ok)) {
		// This function closes the entire program, and can be called anywhere
		end_game(EXIT_FAILURE);
	}
	else {
		clearAlt();
		title_screen::getInstance().mode_title();
	}
}
bool populate_masks_from_xml(vector<ArmorType*>& masks, const string& file, Log& log)
{
	CMarkup xml;
	if (!xml.Load(string(artdir) + file))
	{ //File is missing or not valid XML.
		addstrAlt(failedToLoad + file + CONST_EXCLAMATION_POINT, log);
		pressAnyKey();
		return false; //Abort.
	}
	xml.FindElem();
	xml.IntoElem();
	int defaultindex;
	if (xml.FindElem(CONST_DEFAULT)) defaultindex = getarmortype(xml.GetData());
	else
	{
		addstrAlt(defaultMissingForMask, log);
		pressAnyKey();
		return false; //Abort.
	}
	if (defaultindex == -1)
	{
		addstrAlt(defaultUnknownForMask, log);
		pressAnyKey();
		return false; //Abort.
	}
	xml.ResetMainPos();
	while (xml.FindElem(CONST_MASKTYPE)) masks.push_back(new ArmorType(*masks[defaultindex], xml.GetSubDoc()));
	return true;
}