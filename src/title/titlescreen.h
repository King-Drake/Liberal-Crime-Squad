#pragma once
class title_screen {

private:
	static title_screen s_title_singleton;
	static vector<string> s_savefiles;
	static string savefile_name;
	bool static autosave;
	static bool titleInitiated;
	void choose_savefile_name();
	void selectAndLoadSaveFile();
public:
	static title_screen getInstance();
	void mode_title();
	string getFileName();
	void reset();
	static void setautosaveoption(bool shouldautosave);
	void autosavegame();
};
/*
 titlescreen.cpp
*/
//void mode_title();
