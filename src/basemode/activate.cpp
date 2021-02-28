

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
// Note: this file is encoded in the PC-8 / Code Page 437 / OEM-US character set
// (The same character set used by Liberal Crime Squad when it is running)
// Certain special characters won't display correctly unless your text editor is
// set to use that character set, such as this e with an accent: ├⌐
// In Windows Notepad with the Terminal font, OEM/DOS encoding it should work fine.
// You can set this in Notepad by going to Format->Font and choosing the Terminal font,
// then choosing OEM/DOS in the Script dropdown box.
// In Notepad++ go to the Encoding menu, Character sets, Western European, OEM-US... easy!
// In Code::Blocks's editor go to Settings->Editor->the Other Settings tab and
// then pick WINDOWS-437 from the dropdown box and then choose the radio button
// to make this the default encoding and disable auto-detection of the encoding.
// Then close the file and reopen it (since Code::Blocks detects the encoding
// when it opens the file and it can't be changed after that; what we changed was
// how it detects encoding for files it opens in the future, not files already open).
// In Microsoft Visual C++, right-click the file in the Solution Explorer,
// select Open With..., choose C++ Source Code Editor (with encoding),
// then choose OEM United States - Codepage 437.
// In MS-DOS Editor (included with Windows as EDIT.COM in your system32 directory),
// the codepage will be correct already since it's running in a console window just
// like Liberal Crime Squad. Well OK, the encoding might be wrong, but then it's wrong
// in Liberal Crime Squad TOO, and to fix it, go to Control Panel, Regional and Language Settings,
// Advanced tab, and choose English (United States) from the dropdown box as the encoding
// for non-Unicode applications, then press OK.
// If you have a Linux or other UNIX-based system you are obviously smart enough
// to figure out for yourself how to open a file in OEM-US PC-8 codepage 437 in
// your favorite text editor. If you're on Mac OS X, well that's UNIX-based, figure
// it out for yourself.



#include "../includes69.h"
#include "../constStringOEMactivate.h"
#include <algorithm>

Activity getDefaultActivityTeaching(DeprecatedCreature *cr) {
	for (CreatureTypes type : ACTIVITY_TEACH_FIGHTING_DEFAULT) {
		if (cr->type == type) {
			return ACTIVITY_TEACH_FIGHTING;
		}
	}
	for (CreatureTypes type : ACTIVITY_TEACH_COVERT_DEFAULT) {
		if (cr->type == type) {
			return ACTIVITY_TEACH_COVERT;
		}
	}
	for (CreatureTypes type : ACTIVITY_TEACH_POLITICS_DEFAULT) {
		if (cr->type == type) {
			return ACTIVITY_TEACH_POLITICS;
		}
	}
	return ACTIVITY_TEACH_POLITICS;

}

// These two functions handle listing and updating class choices
int classlist = 0;
void listclasses(DeprecatedCreature *cr)
{

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(10, 40, CLASSES_COST_SIXTY);
	for (int i = 0; i < 5; ++i)
	{
		if (i + classlist < len(data_lessons))
		{
			set_color_easy(cr->activity_type() == data_lessons[i + classlist].activity ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(12 + i, 40, to_string(i + 1) + spaceDashSpace + data_lessons[i + classlist].str);
		}
	}
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(17, 40, to_string(6) + spaceDashSpace + OTHER_CLASSES);
}
void updateclasschoice(DeprecatedCreature *cr, char choice)
{
	if (choice >= '1' && choice <= '5')
	{
		if (choice - '1' + classlist < len(data_lessons))
			cr->set_activity_type(data_lessons[choice - '1' + classlist].activity);
		listclasses(cr);
	}
	else if (choice == '6')
	{
		classlist += 5;
		if (classlist >= len(data_lessons))
			classlist = 0;
		listclasses(cr);
	}
}
char incrementChar(char c, int i) {
	return c + i;
}
void recruitSelect(DeprecatedCreature &cr)
{
	// Number of recruitable creatures
	int options = len(recruitable_creatures);
	for (int i = 0; i < options; i++)
	{
		// Dynamic difficulty for certain creatures, recalculated each time the function is called
		if (recruitable_creatures[i].type == CREATURE_MUTANT)
		{
			if (lawList[LAW_NUCLEARPOWER] == -2 && lawList[LAW_POLLUTION] == -2)
				recruitable_creatures[i].difficulty = 2;
			else if (lawList[LAW_NUCLEARPOWER] == -2 || lawList[LAW_POLLUTION] == -2)
				recruitable_creatures[i].difficulty = 6;
			else
				recruitable_creatures[i].difficulty = 9;
		}
	}
	int page = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, WHAT_TYPE_OF_PERSON_WILL);
		addstrAlt(cr.getNameAndAlignment().name);
		addstrAlt(TRY_TO_MEET_AND_RECRUIT);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(1, 0, TYPE_DIFFICULTY_HEADER);
		for (int p = page * 19, y = 2; p < options&&p < page * 19 + 19; p++, y++)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 0);
			addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(recruitable_creatures[p].name);
			moveAlt(y, 49);
			displayDifficulty(recruitable_creatures[p].difficulty);
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, PRESS_A_LETTER_TO_SELECT_PROFESSION);
		mvaddstrAlt(23, 0, addpagestr());
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0)page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < options)page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + (int)(c - 'a');
			if (p < options)
			{
				cr.set_activity_type(ACTIVITY_RECRUITING, recruitable_creatures[p].type);
				break;
			}
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
	return;
}
void show_victim_status(CreatureHealth victim, const int age, const int HEART)
{

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(2, 55, STATUS_COLON);
	printhealthstat(victim, 2, 66, true);
	printwoundstat(victim, 4, 55);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(11, 55, HEART_COLON); mvaddstrAlt(11, 66, tostring(HEART));
	mvaddstrAlt(12, 55, AGE_COLON); mvaddstrAlt(12, 66, tostring(age));
}
#include <sstream>
vector<string>& split_string(const string &s, char delim, vector<string> &elems) {
	ostringstream oss;
	for (char c : s) {
		if (c == ' ')
		{
			elems.push_back(oss.str());
			oss.str(string());
		}
		else if (c == '\n')
		{
			elems.push_back(oss.str());
			elems.push_back("");
			oss.str(string());
		}
		else oss << c;
	}
	elems.push_back(oss.str());
	return elems;
}
void apply_augmentation(DeprecatedCreature *victim, DeprecatedCreature *cr, AugmentType *selected_aug) {

	int skills = cr->get_skill(SKILL_SCIENCE) + (cr->get_skill(SKILL_FIRSTAID) / 2);
	int difficulty = selected_aug->get_difficulty();

	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(23, 1, PRESS_ANY_KEY);
	moveAlt(21, 1);
	int blood_saved = 10 * cr->get_skill(SKILL_SCIENCE) + 15 * cr->get_skill(SKILL_FIRSTAID);
	if (blood_saved > 100) blood_saved = 100;
	victim->lose_blood(100 - blood_saved);
	if (skills < difficulty &&
		LCSrandom((100 * difficulty) / skills) < 100)
	{
		unsigned char* wound = nullptr;
		switch (selected_aug->get_type())
		{
		case AUGMENTATION_HEAD:
			victim->apply_special_wound(BODYPART_HEAD, WOUND_NASTYOFF);
			victim->lose_blood( 100);
			break;
		case AUGMENTATION_BODY:
			victim->apply_special_wound(BODYPART_BODY, WOUND_NASTYOFF);
			victim->lose_blood( 100);
			break;
		case AUGMENTATION_ARMS:
			if (LCSrandom(2))
				victim->apply_special_wound(BODYPART_ARM_LEFT, WOUND_NASTYOFF);
			else
				victim->apply_special_wound(BODYPART_ARM_RIGHT, WOUND_NASTYOFF);
			victim->lose_blood( 25);
			break;
		case AUGMENTATION_LEGS:
			if (LCSrandom(2))
				victim->apply_special_wound(BODYPART_LEG_LEFT, WOUND_NASTYOFF);
			else
				victim->apply_special_wound(BODYPART_LEG_RIGHT, WOUND_NASTYOFF);
			victim->lose_blood( 25);
			break;
		case AUGMENTATION_SKIN:
			if (LCSrandom(2))
				victim->apply_special_wound(BODYPART_HEAD, WOUND_NASTYOFF);
			else
				victim->apply_special_wound(BODYPART_BODY, WOUND_NASTYOFF);
			victim->lose_blood( 50);
			break;
		}
		if (victim->getCreatureHealth().blood > 0)
		{
			set_color_easy(RED_ON_BLACK_BRIGHT);
			addstrAlt(string(victim->getNameAndAlignment().name) + HAS_BEEN_HORRIBLY_DISFIGURED, gamelog);
		}
	}
	else //It was successful... but not without some injuries
	{
		switch (selected_aug->get_type())
		{
		case AUGMENTATION_HEAD:
			victim->apply_special_wound(BODYPART_HEAD, WOUND_BLEEDING | WOUND_BRUISED);
			break;
		case AUGMENTATION_BODY:
			victim->apply_special_wound(BODYPART_BODY, WOUND_BLEEDING | WOUND_BRUISED);
			break;
		case AUGMENTATION_ARMS:
			if (LCSrandom(2))
				victim->apply_special_wound(BODYPART_ARM_RIGHT, WOUND_BLEEDING | WOUND_BRUISED);
			else
				victim->apply_special_wound(BODYPART_ARM_LEFT, WOUND_BLEEDING | WOUND_BRUISED);
			break;
		case AUGMENTATION_LEGS:
			if (LCSrandom(2))
				victim->apply_special_wound(BODYPART_LEG_RIGHT, WOUND_BLEEDING | WOUND_BRUISED);
			else
				victim->apply_special_wound(BODYPART_LEG_LEFT, WOUND_BLEEDING | WOUND_BRUISED);
			break;
		case AUGMENTATION_SKIN:
			victim->apply_special_wound(BODYPART_HEAD, WOUND_BLEEDING | WOUND_BRUISED);
			break;
		}
		selected_aug->make_augment(victim->get_augmentation(selected_aug->get_type()));
		victim->adjust_attribute(selected_aug->get_attribute(), selected_aug->get_effect());
		cr->train(SKILL_SCIENCE, 15);
		addjuice(*cr, 10, 1000);
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		addstrAlt(string(victim->getNameAndAlignment().name) + HAS_BEEN_AUGMENTED_WITH + selected_aug->get_name(), gamelog);
	}
	if (victim->getCreatureHealth().blood <= 0) //Lost too much blood, you killed 'em
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		victim->die();
		addstrAlt(string(victim->getNameAndAlignment().name) + HAS_BEEN_BRUTALLY_MURDERED_BY + cr->getNameAndAlignment().name, gamelog);
	}
}
void selectAugmentType(vector<AugmentType *> &aug_type, char aug_c, int age);	

void select_augmentation(DeprecatedCreature *cr) //TODO: Finish and general cleanup
{
	DeprecatedCreature *victim = 0;
	vector<DeprecatedCreature *> temppool = getLiberalsSharingLocation(cr);
	int cur_step = 0;
	int page = 0;
	int c = 0;
	int aug_c = 0;
	vector<AugmentType *> aug_type;
	AugmentType *selected_aug;
	while (true)
	{
		eraseAlt();

		switch (cur_step) {
		case 0: //PAGE 0, selecting a liberal
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(0, 0, SELECT_LIBERAL_TO_PERFORM_EXPERIMENTS_UPON);
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(1, 0, NAME_HEALTH_HEART_HEADER);
			for (int p = page * 19, y = 2; p < len(temppool) && p < page * 19 + 19; p++, y++)
			{
				set_color_easy(WHITE_ON_BLACK); //c==y+'a'-2);
				moveAlt(y, 0);
				addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
				addstrAlt(temppool[p]->getNameAndAlignment().name);
				mvaddstrAlt(y, 49, tostring(temppool[p]->get_attribute(ATTRIBUTE_HEART, true)));
				mvaddstrAlt(y, 62, tostring(temppool[p]->getCreatureBio().age));
				printhealthstat(temppool[p]->getCreatureHealth(), y, 31, TRUE);
			}
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(22, 0, PRESS_A_LETTER_TO_SELECT_LIBERAL);
			mvaddstrAlt(23, 0, addpagestr());
			c = getkeyAlt();
			//PAGE UP
			if (is_page_up(c) && page > 0)page--;
			//PAGE DOWN
			if (is_page_down(c) && (page + 1) * 19 < len(temppool))page++;
			if (c >= 'a'&&c <= 's')
			{
				int p = page * 19 + c - 'a';
				if (p < len(temppool))
				{
					victim = temppool[p];
					cur_step = 1;
				}
				else
					victim = 0;
			}
			if (c == 'x' || c == ESC || c == SPACEBAR || c == ENTER) return;
			break;
		case 1: //PAGE 1, selecting an augmentation
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(0, 0, SUBJECT_COLON);
			set_color_easy(WHITE_ON_BLACK);
			addstrAlt(victim->getNameAndAlignment().name); addstrAlt(COMMA_SPACE); addstrAlt(gettitle(victim->getCreatureHealth().align, victim->juice));
			//mvaddstrAlt(1,0,EIGHTY_LINE);
			show_victim_status(victim->getCreatureHealth(), victim->getCreatureBio().age, victim->get_attribute(ATTRIBUTE_HEART, true));
			mvaddstrAlt(2, 1, SELECT_AUGMENTATION);
			for (int p = page * 19, y = 4; p < AUGMENTATIONNUM&&p < page * 19 + 19; p++, y++)
			{
				bool already_augmented = victim->get_augmentation(y - 4).type != -1;
				if (already_augmented) set_color_easy(BLACK_ON_BLACK_BRIGHT);
				else set_color_easy(aug_c == y + 'a' - 4 ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
				moveAlt(y, 1);
				addcharAlt(y + 'A' - 4); addstrAlt(spaceDashSpace);
				addstrAlt(Augmentation::get_name(y - 4));
			}
			if (aug_c >= 'a'&&aug_c <= 'e'&&c >= 'a'&&c <= 'e')
			{
				aug_type.clear();
				if (victim->get_augmentation(aug_c - 'a').type == -1) //False if already augmented on that bodypart.
				{
					selectAugmentType(aug_type, aug_c, victim->getCreatureBio().age);
				}
			}
			set_color_easy(WHITE_ON_BLACK);
			for (int x = 0, y = 4; x < aug_type.size(); x++, y++)
			{
				mvaddcharAlt(y, 26, y + '1' - 4); addstrAlt(spaceDashSpace);
				addstrAlt(aug_type[x]->get_name());
			}
			//Checks to see if valid input, and moves to next screen
			if (aug_c >= 'a'&&aug_c <= 'e'&&c >= '1'&&c <= '0' + aug_type.size())
			{
				cur_step = 2;
				selected_aug = aug_type[c - '1'];
				break;
			}
			c = getkeyAlt();
			if (c >= 'a'&&c <= 'e') aug_c = c;
			else if (c == ESC)return;
			else if (c == 'x' || c == SPACEBAR || c == ENTER) { cur_step = 0; aug_type.clear(); aug_c = 0; }
			break;
		case 2: //PAGE 2, confirm your choices
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(0, 0, SUBJECT_COLON);
			set_color_easy(WHITE_ON_BLACK);
			addstrAlt(victim->getNameAndAlignment().name); addstrAlt(COMMA_SPACE); addstrAlt(gettitle(victim->getCreatureHealth().align, victim->juice));
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(2, 0, AUGMENTATION_COLON);
			set_color_easy(WHITE_ON_BLACK);
			addstrAlt(selected_aug->get_name());
			show_victim_status(victim->getCreatureHealth(), victim->getCreatureBio().age, victim->get_attribute(ATTRIBUTE_HEART, true));
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(4, 0, EFFECT_COLON);
			set_color_easy(WHITE_ON_BLACK);
			string selected_attribute = attribute_enum_to_string(selected_aug->get_attribute());
			addstrAlt((char)(toupper(selected_attribute.at(0))) +
				selected_attribute.substr(1) +
				(selected_aug->get_effect() >= 0 ? SPACE_PLUS : singleSpace) +
				tostring(selected_aug->get_effect()));
			set_color_easy(WHITE_ON_BLACK_BRIGHT);
			mvaddstrAlt(5, 0, CHANCE_AT_SUCCESS_COLON);
			int skills = cr->get_skill(SKILL_SCIENCE) + (cr->get_skill(SKILL_FIRSTAID) / 2);
			int difficulty = selected_aug->get_difficulty();
			set_color_easy(WHITE_ON_BLACK);
			addstrAlt(to_string(100 * skills / difficulty));
			mvaddstrAlt(7, 0, DESCRIPTION);
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(8, 0, LONG_LINE_BUT_NOT_EIGHTY);
			vector<string> desc;
			split_string(selected_aug->get_description(), ' ', desc);
			int chars_left = 50;
			int line = 9;
			for (int i = 0; i < desc.size(); i++)
			{
				if (desc[i].length() > 50) continue;
				else if (desc[i].empty())
				{
					line++;
					chars_left = 50;
					continue;
				}
				else if (chars_left<0 || desc[i].length()>chars_left)
				{
					line++;
					chars_left = 50;
					i--;
					continue;
				}
				else if (desc[i].length() <= chars_left)
				{
					mvaddstrAlt(line, 50 - chars_left, desc[i]);
					chars_left -= (desc[i].length() + 1);
				}
			}
			mvaddstrAlt(23, 1, ARE_YOU_SURE_Y_N);
			c = getkeyAlt();
			if (c == 'y')
			{
				apply_augmentation(victim, cr, selected_aug);
				show_victim_status(victim->getCreatureHealth(), victim->getCreatureBio().age, victim->get_attribute(ATTRIBUTE_HEART, true));
				pressAnyKey();
				return;
			}
			else if (c == ESC)return;
			else if (c == 'x' || c == SPACEBAR || c == ENTER || c == 'n') { cur_step = 1; selected_aug = nullptr; }
			break;
		}
	}
}
int armor_makedifficulty(ArmorType& type, DeprecatedCreature *cr) //Make class method? -XML
{
	int basedif = type.get_make_difficulty() - cr->get_skill(SKILL_TAILORING) + 3;
	return max(basedif, 0);
}
int armor_makedifficulty(Armor& type, DeprecatedCreature *cr)
{
	return armor_makedifficulty(*armortype[getarmortype(type.get_itemtypename())], cr);
}
// Macro definition 
#ifndef MAX
// maximum of 2 numbers
#define MAX(a,b) (((a)<(b))?(b):(a))
#endif

/* base - activate - make clothing */
void select_makeclothing(DeprecatedCreature *cr)
{
	vector<int> armortypei;
	for (int a = 0; a < len(armortype); a++)
	{
		if (armortype[a]->get_make_difficulty() == 0)
			continue;
		if (armortype[a]->deathsquad_legality()
			&& (lawList[LAW_POLICEBEHAVIOR] != -2 || lawList[LAW_DEATHPENALTY] != -2))
			continue;
		armortypei.push_back(a);
	}
	int page = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, WHICH_WILL);
		addstrAlt(cr->getNameAndAlignment().name);
		addstrAlt(TRY_TO_MAKE_NOTE_HALF_COST_WITH_CLOTH);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(1, 0, NAME_DIFFICULTY_COST_HEADER);
		int y = 2;
		for (int p = page * 19; p < len(armortypei) && p < page * 19 + 19; p++, y++)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 0);
			addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(armortype[armortypei[p]]->get_name());
			moveAlt(y, 37);
			displayDifficulty(MAX(armor_makedifficulty(*armortype[armortypei[p]], cr), 0));
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
			string price = '$' + tostring(armortype[armortypei[p]]->get_make_price());
			mvaddstrAlt(y, 64 - len(price), price);
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, PRESS_A_LETTER_TO_SELECT_CLOTHING_TYPE);
		mvaddstrAlt(23, 0, addpagestr());
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0)page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(armortypei))page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + c - 'a';
			if (p < len(armortypei))
			{
				cr->set_activity_type(ACTIVITY_MAKE_ARMOR, armortypei[p]); //Use id name of armor type instead? -XML
				return;
			}
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}

/* base - activate - hostages */
void select_tendhostage(DeprecatedCreature* cr)
{
	vector<DeprecatedCreature*> temppool = getHostagesSharingLocation(cr);
	if (!len(temppool))return;
	if (len(temppool) == 1)
	{
		cr->set_activity_type(ACTIVITY_HOSTAGETENDING, temppool[0]->id);
		return;
	}
	int page = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(0, 0, WHICH_HOSTAGE_WILL);
		addstrAlt(cr->getNameAndAlignment().name);
		addstrAlt(BE_WATCHING_OVER);
		mvaddstrAlt(1, 0, CODENAME_SKILL_HEALTH_LOCATION_HEADER);
		mvaddstrAlt(1, 57, DAYS_IN_CAPTIVITY);
		for (int y = 2, p = page * 19; p < len(temppool) && p < page * 19 + 19; p++, y++)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 0);
			addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(temppool[p]->getNameAndAlignment().name);
			bool bright = false;
			int skill = 0;
			for (int sk = 0; sk < SKILLNUM; sk++)
			{
				skill += temppool[p]->get_skill(sk);
				if (temppool[p]->get_skill_ip(sk) >= 100 + (10 * temppool[p]->get_skill(sk)) &&
					temppool[p]->get_skill(sk) < temppool[p]->skill_cap(sk))bright = true;
			}
			set_color_easy(bright ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(y, 25, skill);
			printhealthstat(temppool[p]->getCreatureHealth(), y, 33, TRUE);
			if (mode == REVIEWMODE_JUSTICE)set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			else set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(y, 42, LocationsPool::getInstance().getLocationNameWithGetnameMethod(temppool[p]->location, true, true));
			set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
			mvaddstrAlt(y, 57, temppool[p]->joindays);
			addstrAlt(singleSpace);
			if (temppool[p]->joindays > 1)addstrAlt(CONST_X_DAYS);
			else addstrAlt(CONST_X_DAY);
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, PRESS_A_LETTER_TO_SELECT_CONSERVATIVE);
		mvaddstrAlt(23, 0, addpagestr());
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(temppool)) page++;
		if (c >= 'a' && c <= 's')
		{
			int p = page * 19 + (int)(c - 'a');
			if (p < len(temppool))
			{
				cr->set_activity_type(ACTIVITY_HOSTAGETENDING, temppool[p]->id);
				return;
			}
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}
bool attempt_set_activity(DeprecatedCreature* cr, const int nact) {
	ActivityST oact = cr->activity;
	cr->set_activity_type(ACTIVITY_NONE);
	switch (nact) {
	case ACTIVITY_RECRUITING:
		recruitSelect(*cr);
		break;
	case ACTIVITY_MAKE_ARMOR:
		select_makeclothing(cr);
		break;

	case ACTIVITY_AUGMENT:
		select_augmentation(cr);
		break;

	case ACTIVITY_HOSTAGETENDING:
		select_tendhostage(cr);
		break;
	}
	if (cr->activity_type() == nact) ;
	else cr->activity = oact;
	return cr->activity_type() == nact;
}
vector<string> standard_activities_and_data;
void selectOneOfStandardActivities(char c, char choiceChar, DeprecatedCreature *cr) {
	int choice = choiceChar - '1';
	switch (c) {
	case 'a':
		switch (choiceChar)
		{
		case '1':
		case '2':
		case '4':
			//case '5':cr->activity.type=ACTIVITY_DOS_ATTACKS;
		case '5':
		case '6':
			cr->set_activity_type(activate_menu_items[c][choice].activity);
			break;
		case '3':
			cr->set_activity_type(ACTIVITY_GRAFFITI, -1);
			break;
		case '7':
			if (cr->location != -1 &&
				LocationsPool::getInstance().get_specific_integer(INT_GETCOMPOUNDWALLS,cr->location) & COMPOUND_PRINTINGPRESS)
			{
				cr->set_activity_type(ACTIVITY_WRITE_GUARDIAN); break;
			}
		default:
			if (cr->get_attribute(ATTRIBUTE_WISDOM, true) > 7 || cr->juice < 0)
				cr->set_activity_type(ACTIVITY_COMMUNITYSERVICE);
			else if (cr->get_attribute(ATTRIBUTE_WISDOM, true) > 4)
				cr->set_activity_type(ACTIVITY_TROUBLE);
			else
			{
				if (cr->get_skill(SKILL_COMPUTERS) > 2)
					cr->set_activity_type(ACTIVITY_HACKING);
				else if (cr->get_skill(SKILL_ART) > 1)
				{
					cr->set_activity_type(ACTIVITY_GRAFFITI, -1);
				}
				else
					cr->set_activity_type(ACTIVITY_TROUBLE);
			}
		}
		break;
	case 'b':
		switch (choiceChar)
		{
		case '1':
		case '2':
		case '3':
		case '4':
			cr->set_activity_type(activate_menu_items[c][choice].activity);
			break;
		default:
			if (cr->get_weapon().get_specific_bool(BOOL_INSTRUMENT_))
				cr->set_activity_type(ACTIVITY_SELL_MUSIC);
			else if (cr->get_skill(SKILL_ART) > 1)
				cr->set_activity_type(ACTIVITY_SELL_ART);
			else if (cr->get_skill(SKILL_TAILORING) > 1)
				cr->set_activity_type(ACTIVITY_SELL_TSHIRTS);
			else if (cr->get_skill(SKILL_MUSIC) > 1)
				cr->set_activity_type(ACTIVITY_SELL_MUSIC);
			else cr->set_activity_type(ACTIVITY_DONATIONS);
		}
		break;
	case 'c':
		switch (choiceChar)
		{
		case '1':
		case '3':
			//case '4':cr->activity.type=ACTIVITY_DOS_RACKET;break;
			cr->set_activity_type(activate_menu_items[c][choice].activity);
			break;
		case '2':
			if (ZEROMORAL || cr->getCreatureBio().age >= 18)
				cr->set_activity_type(ACTIVITY_PROSTITUTION); break;
		default:
			if (cr->get_skill(SKILL_COMPUTERS) > 1)
				cr->set_activity_type(ACTIVITY_CCFRAUD);
			else if (cr->get_skill(SKILL_SEDUCTION) > 1 && (ZEROMORAL || cr->getCreatureBio().age >= 18))
				cr->set_activity_type(ACTIVITY_PROSTITUTION);
			else cr->set_activity_type(ACTIVITY_SELL_DRUGS);
		}
		break;
	case 'd':
		switch (choiceChar)
		{
		case '1': { // Pick type to recruit
			attempt_set_activity(cr, ACTIVITY_RECRUITING);
			break; }
		case '2': { // Pick clothing to make
			attempt_set_activity(cr, ACTIVITY_MAKE_ARMOR);
			break; }
		case '3':
			cr->set_activity_type(activate_menu_items[c][choice].activity);
			break;
		case '4':
			cr->set_activity_type(ACTIVITY_STEALCARS);
			break;
		case '5':
			if (!cr->canwalk() && !(cr->flag & CREATUREFLAG_WHEELCHAIR))
				cr->set_activity_type(ACTIVITY_WHEELCHAIR);
			break;
		case '6': {
			attempt_set_activity(cr, ACTIVITY_AUGMENT);
			break; }
		}
		break;
	}
}

enum LOOP_CONTINUATION {
	RETURN_ZERO,
	RETURN_ONE,
	REPEAT
};
LOOP_CONTINUATION iterateActivate(DeprecatedCreature *cr, const int hostagecount, int &state, const char havedead) {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK);
	printfunds();
	moveAlt(0, 0);
	if (cr->income)
	{
		addstrAlt(cr->getNameAndAlignment().name);
		addstrAlt(MADE_DOLLARS);
		addstrAlt(cr->income);
		addstrAlt(YESTERDAY_WHAT_NOW);
	}
	else
	{
		addstrAlt(TAKING_ACTION_COLON_WHAT_WILL);
		addstrAlt(cr->getNameAndAlignment().name);
		addstrAlt(BE_DOING_TODAY);
	}
	printcreatureinfo(cr);
	makedelimiter();
	Data_Activity activity = data_activities[(Activity)cr->activity_type()];
	if (!state)
	{
		if (activity.key != 'x')
			state = activity.key;
	}
	int oldstate = state;
	for (int i = 0; i < len(standard_activities_and_data); i++) {
		set_color_easy(state == 'a' + i ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
		mvaddstrAlt(10 + i, 1, incrementChar('A', i) + spaceDashSpace + standard_activities_and_data[i]);
	}
	set_color_easy(state == 't' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	mvaddstrAlt(14, 1, T_TEACHING_OTHER_LIBERALS);
	if (hostagecount > 0)set_color_easy(state == 'i' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(15, 1, I_TEND_TO_HOSTAGE);
	set_color_easy(state == 'l' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	mvaddstrAlt(16, 1, L_LEARN_IN_UNIVERSITY);
	if (clinictime(*cr))set_color_easy(state == 'm' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(17, 1, M_MOVE_TO_CLINIC);
	if (cr->get_skill(SKILL_FIRSTAID) != 0)
		set_color_easy(state == 'h' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	else
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(18, 1, H_HEAL_LIBERALS);
	if (havedead)set_color_easy(state == 'z' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	else set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(19, 1, Z_DIZPOSE_OF_BODIES);

	char sieged =  getseigedFromLocation(selectedsiege);
	
	/*char underattack=0;
	if(siege&&sieged) underattack=siege->underattack;*/
	if (!sieged)
		set_color_easy(WHITE_ON_BLACK);
	else
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
	mvaddstrAlt(20, 1, E_EQUIP_THIS_LIBERAL);
	// standard activities are coded as 'a' to 'd'
	// All other activities use ordinal letters, rather than consecutive
	if (state >= 'a' && state < 'e' )
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(19, 40, QUESTION_HELP);
	}
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(20, 40, CONST_X_ENTER_CONFIRM);
	set_color_easy(state == 'x' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
	mvaddstrAlt(21, 1, X_NOTHING);
	if (state == 'l')
	{
		listclasses(cr);
	}
	else
	{
		int ypos = 10;
		for (ActivityAndString current_item : activate_menu_items[state]) {
			set_color_easy(cr->activity_type() == current_item.activity ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			moveAlt(ypos, 40);
			if (current_item.i > 0)
			{
				addstrAlt(current_item.i);
				addstrAlt(spaceDashSpace);
			}
			ypos++;
			string outputString;
			if (current_item.skill == SKILLNUM) { outputString = current_item.str; }
			else {
				if (cr->get_skill(current_item.skill) >= 8) { outputString = current_item.str3; }
				else
					if (cr->get_skill(current_item.skill) >= 4) { outputString = current_item.str2; }
					else {
						outputString = current_item.str;
					}
			}
			addstrAlt(outputString);
		}
	}
	set_color_easy(WHITE_ON_BLACK);
	moveAlt(22, 3);
	if (activity.show_name)
	{
		addstrAlt(cr->getNameAndAlignment().name);
		addstrAlt(SPACE_WILL_SPACE);
	}
	addstrAlt(activity.lineAttempt(0, cr));
	mvaddstrAlt(23, 3, activity.lineAttempt(1, cr));
	mvaddstrAlt(24, 3, activity.lineAttempt(2, cr));
	int c = getkeyAlt();
	if (c >= 'a'&&c <= 'z') state = c;
	if ((c >= 'a'&&c <= 'z') || (c >= '0'&&c <= '9'))
	{
		int choice = c;
		switch (state)
		{
		case 'a':
		case 'b':
		case 'c':
		case 'd':
			selectOneOfStandardActivities(state, choice, cr);
			break;
		case 't':
			switch (choice)
			{
			case '1':
			case '2':
			case '3':
				// activate_menu_items['t'] starts its index at 0 with ACTIVITY_NONE, instead of starting at 1 the way the other maps do
				// This is a temporary fix as part of a move to basically remove switch(state) as well as switch(choice)
				cr->set_activity_type(activate_menu_items['t'][(choice - '1') + 1].activity);
				break;
			default:
				cr->set_activity_type(getDefaultActivityTeaching(cr));
				break;
			}
			break;
		case 'i':
			if (hostagecount > 0)
			{
				if (attempt_set_activity(cr, ACTIVITY_HOSTAGETENDING)) {

				}
				else {
					state = oldstate;
				}
			}
			break;
		case 'l':
			updateclasschoice(cr, choice);
			break;
		case 'm':
			if (clinictime(*cr)) cr->set_activity_type(ACTIVITY_CLINIC);
			else state = oldstate;
			break;
		case 'h':
			if (cr->get_skill(SKILL_FIRSTAID)) cr->set_activity_type(ACTIVITY_HEAL);
			else state = oldstate;
			break;
		case 'z':
			if (havedead) cr->set_activity_type(ACTIVITY_BURY);
			else state = oldstate;
			break;
		case 'e':
			if (!sieged)
			{
				createTempSquadWithJustThisLiberal(cr, cursquadid);
			}
			state = oldstate;
			break;
		case 'x':
			cr->set_activity_type(ACTIVITY_NONE);
			break;
		default:
			state = oldstate;
			break;
		}
	}
	// Enter pressed
	if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) return RETURN_ZERO;
	// ? Pressed
	if (c == '?')
		if (state == 'a' || state == 'b' || state == 'c' || state == 'd')
			HelpActivities(cr->activity.type); // Call activity help pages
	return REPEAT;
}
void activate(DeprecatedCreature *cr)
{
	int hostagecount = countHostagesSharingLocation(cr);
	int state = 0;
	char havedead = countDeadSharingLocation(cr);
	while (iterateActivate(cr, hostagecount, state, havedead) == REPEAT)
	{
		;
	}
}
//Activism
Activity getDefaultActivityActivism(DeprecatedCreature *cr) {
	if (cr->get_attribute(ATTRIBUTE_WISDOM, true) > 7 || cr->juice < 0)
		return ACTIVITY_COMMUNITYSERVICE;
	else if (cr->get_attribute(ATTRIBUTE_WISDOM, true) > 4)
		return ACTIVITY_TROUBLE;
	else
	{
		if (cr->get_skill(SKILL_COMPUTERS) > 2)
			return ACTIVITY_HACKING;
		else if (cr->get_skill(SKILL_ART) > 1)
		{
			cr->setactivityargNegativeOne();
			return ACTIVITY_GRAFFITI;
		}
		else return ACTIVITY_TROUBLE;
	}
}
//Fundraising
Activity getDefaultActivityFundraising(DeprecatedCreature *cr) {
	if (cr->get_weapon().get_specific_bool(BOOL_INSTRUMENT_))
		return ACTIVITY_SELL_MUSIC;
	else if (cr->get_skill(SKILL_ART) > 1)
		return ACTIVITY_SELL_ART;
	else if (cr->get_skill(SKILL_TAILORING) > 1)
		return ACTIVITY_SELL_TSHIRTS;
	else if (cr->get_skill(SKILL_MUSIC) > 1)
		return ACTIVITY_SELL_MUSIC;
	else return ACTIVITY_DONATIONS;
}
//Illegal Fundraising
Activity getDefaultActivityIllegalFundraising(DeprecatedCreature *cr) {
	if (cr->get_skill(SKILL_COMPUTERS) > 1)
		return ACTIVITY_CCFRAUD;
	else if (cr->get_skill(SKILL_SEDUCTION) > 1 && (ZEROMORAL || cr->getCreatureBio().age >= 18))
		return ACTIVITY_PROSTITUTION;
	else
		return ACTIVITY_SELL_DRUGS;
}
vector<string> bulkActivityString;

vector<file_and_text_collection> activate_text_file_collection = {
	customText(&bulkActivityString, MOSTLY_ENDINGS_FOLDER + BULK_ACTIVITY_STRING_TXT),
	// standard_activities_and_data is capped at four (4) elements
	customText(&standard_activities_and_data, MOSTLY_ENDINGS_FOLDER + STANDARD_ACTIVITIES_AND_DATA_TXT),
};
void activatebulk()
{

	vector<DeprecatedCreature *> temppool = activatable_liberals();
	if (!len(temppool)) return;
	int page = 0, selectedactivity = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		printfunds();
		mvaddstrAlt(0, 0, ACTIVATE_UNINVOLVED_LIBERALS);
		mvaddstrAlt(1, 0, CODE_NAME_CURRENT_ACTIVITY_HEADER);
		mvaddstrAlt(1, 51, BULK_ACTIVITY_HEADER);

		for (int i = 0; i < len(bulkActivityString); i++) {
			set_color_easy(selectedactivity == i ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(2 + i, 51, incrementChar('1', i) + spaceDashSpace + bulkActivityString[i]);
		}

		for (int y = 2, p = page * 19; p < len(temppool) && p < page * 19 + 19; p++, y++)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 0);
			addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(temppool[p]->getNameAndAlignment().name);
			moveAlt(y, 25);
			set_activity_color(temppool[p]->activity_type());
			addstrAlt(temppool[p]->getActivityString());
			/*if(temppool[p]->activity.type==ACTIVITY_TROUBLE)
			{
			addstrAlt(spaceParanthesisDollar);
			addstrAlt(temppool[p]->activity.arg);
			addstrAlt(CLOSE_PARENTHESIS);
			}*/
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, PRESS_A_LETTER_TO_ASSIGN_ACTIVITY_OR_NUMBER);
		mvaddstrAlt(23, 0, addpagestr());
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(temppool)) page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + c - 'a';
			if (p < len(temppool))
			{
				switch (selectedactivity)
				{
				case 0: //Activism
					temppool[p]->set_activity_type(getDefaultActivityActivism(temppool[p]));
					break;
				case 1: //Fundraising
					temppool[p]->set_activity_type(getDefaultActivityFundraising(temppool[p]));
					break;
				case 2: //Illegal Fundraising
					temppool[p]->set_activity_type(getDefaultActivityIllegalFundraising(temppool[p]));
					break;
				case 3: //Check polls
					temppool[p]->set_activity_type(ACTIVITY_POLLS);
					break;
				case 4: //Steal cars
					temppool[p]->set_activity_type(ACTIVITY_STEALCARS);
					break;
				case 5: //Volunteer
					temppool[p]->set_activity_type(ACTIVITY_COMMUNITYSERVICE);
					break;
				case 6: //Repair Clothing
					temppool[p]->set_activity_type(ACTIVITY_REPAIR_ARMOR);
					break;
				}
			}
		}
		if (c >= '1'&&c <= '7')
			selectedactivity = c - '1';
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}
/* base - activate the uninvolved */

void activate()
{
	vector<DeprecatedCreature *> temppool = activatable_liberals();
	if (!len(temppool)) return;
	sortliberals(temppool, activesortingchoice[SORTINGCHOICE_ACTIVATE]);
	int page = 0;
	while (true)
	{
		music.play(MUSIC_ACTIVATE);
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		printfunds();
		mvaddstrAlt(0, 0, ACTIVATE_UNINVOLVED_LIBERALS);
		mvaddstrAlt(1, 0, CODENAME_SKILL_HEALTH_LOCATION_HEADER);
		mvaddstrAlt(1, 57, CONST_X_TITLE_ACTIVITY);
		int y = 2;
		for (int p = page * 19; p < len(temppool) && p < page * 19 + 19; p++, y++)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(y, 0);
			addcharAlt(y + 'A' - 2); addstrAlt(spaceDashSpace);
			addstrAlt(temppool[p]->getNameAndAlignment().name);
			char bright = 0;
			int skill = 0;
			for (int sk = 0; sk < SKILLNUM; sk++)
			{
				skill += temppool[p]->get_skill(sk);
				if (temppool[p]->get_skill_ip(sk) >= 100 + (10 * temppool[p]->get_skill(sk)) &&
					temppool[p]->get_skill(sk) < temppool[p]->skill_cap(sk))bright = 1;
			}
			set_color_easy(bright ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(y, 25, skill);
			printhealthstat(temppool[p]->getCreatureHealth(), y, 33, TRUE);
			if (mode == REVIEWMODE_JUSTICE)set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			else set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(y, 42, LocationsPool::getInstance().getLocationNameWithGetnameMethod(temppool[p]->location, true, true));
			moveAlt(y, 57);
			// Let's add some color here...
			set_activity_color(temppool[p]->activity_type());
			addstrAlt(temppool[p]->getActivityString());
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, PRESS_A_LETTER_TO_ASSIGN_ACTIVITY);
		mvaddstrAlt(23, 0, addpagestr());
		addstrAlt(CONST_X_T_TO_SORT);
		mvaddstrAlt(24, 0, Z_TO_ASSIGN_SIMPLE_TASKS);
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 19 < len(temppool)) page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 19 + c - 'a';
			if (p < len(temppool)) activate(temppool[p]);
		}
		if (c == 't')
		{
			sorting_prompt(SORTINGCHOICE_ACTIVATE);
			sortliberals(temppool, activesortingchoice[SORTINGCHOICE_ACTIVATE], true);
		}
		if (c == 'z') activatebulk();
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}