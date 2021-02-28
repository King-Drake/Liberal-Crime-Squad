


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
#include "../includes59.h"
#include "../constStringOEMcommondisplay.h"
map<int, string> prisoner_description = {
	map<int, string>::value_type(CREATURE_POLITICIAN, A_CURSING_POLITICIAN),
	map<int, string>::value_type(CREATURE_CORPORATE_CEO, A_SQUIRMING_CEO),
	map<int, string>::value_type(CREATURE_RADIOPERSONALITY, A_CRYING_RADIO_PERSON),
	map<int, string>::value_type(CREATURE_NEWSANCHOR, A_SMARMY_NEWS_ANCHOR),
	map<int, string>::value_type(CREATURE_SCIENTIST_EMINENT, A_FRIGHTENED_EMINENT_SCIENTIST),
	map<int, string>::value_type(CREATURE_JUDGE_CONSERVATIVE, AN_ANGRY_HANGIN_JUDGE),
};
// Sets the text color to the thematic color for the given alignment
// extended_range forces colors to be set on a 5 point scale instead
// of just basic liberal-moderate-conservative
void set_alignment_color(short alignment, bool extended_range)
{
	if (alignmentColors.count(alignment)) {
		if (alignmentColors[alignment].count(extended_range)) {
			set_color_easy(alignmentColors[alignment][extended_range]);
		}
		else {
			set_color_easy(alignmentColors[alignment][true]);
		}
	}
	else {
		// This should not happen! Set a strange color to indicate an error!
		set_color_easy(YELLOW_ON_RED_BRIGHT_BLINK);
	}
}
// Sets the text color per activity type
void set_activity_color(long activity_type)
{
	if (activityColors.count(activity_type)) {
		set_color_easy(activityColors[activity_type]);
	}
	else {
		// This should not happen! Set a strange color to indicate an error!
		set_color_easy(YELLOW_ON_RED_BRIGHT);

	}
}
/* draws a horizontal line across the screen */
//void makedelimiter(int y = 8, int x = 0);
/* draws a horizontal line across the screen */
void makedelimiter(int y, int x)
{
	set_color_easy(WHITE_ON_BLACK);
	if (mode == GAMEMODE_SITE && y == 8 && x == 0 && mapshowing) // special case: there is a map on the right in site mode
		mvaddstrAlt(y, x, SEVENTY_NINE_LINE); // 80 characters
	else // normal delimiter
		mvaddstrAlt(y, x, CONST_X_LONG_LINE); // 80 characters
}
string perfectlyHealthy(const int align, const int animalgloss, const char smll) {


	if (align == -1)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		if (smll)return (CONSRVTV);
		else return (CONST_X_CONSERVATIVE);
	}
	else if (align == 0)
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		return (CONST_X_MODERATE);
	}
	else
	{
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		if (animalgloss == ANIMALGLOSS_ANIMAL)
			return (CONST_X_ANIMAL);
		else return (CONST_X_LIBERAL);
	}
}
string bleedingOut(const int alive, const int blood, const char smll) {


	if (!alive)
	{
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
		return (DECEASED);
	}
	else if (blood <= 20)
	{
		if (smll)return (NEAR_DETH);
		else return (NEAR_DEATH);
	}
	else if (blood <= 50)
	{
		if (smll)return (BADWOUND);
		else return (BADLY_WOUNDED);
	}
	else if (blood <= 75)
	{
		return (WOUNDED);
	}
	else// if (blood < 100)
	{
		if (smll)return (LTWOUND);
		else return (LIGHTLY_WOUNDED);
	}
}
string missingArmAndOrLeg(const int armok, const int legok, const char smll, const bool bleeding) {

	if (legok == 0 && armok == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (NOLIMBS);
	}
	else if ((legok == 1 && armok == 0) || (armok == 1 && legok == 0))
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (ONELIMB);
	}
	else if (legok == 2 && armok == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (CONST_X_NO_ARMS);
	}
	else if (legok == 0 && armok == 2)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (CONST_X_NO_LEGS);
	}
	else if (legok == 1 && armok == 1)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (ONEARMONELEG);
		else return (ONE_ARM_ONE_LEG);
	}
	else if (armok == 1)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (ONE_ARM);
	}
	else// if (legok == 1)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (ONE_LEG);
	}
}
string missingPartOfFace(const char lefteye, const char righteye, const char nose, const bool bleeding, const char smll) {

	if (righteye == 0 &&
		lefteye == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (CONST_X_BLIND);
	}
	else if ((righteye == 0 ||
		lefteye == 0) &&
		nose == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (FACEMUTL);
		else return (FACE_MUTILATED);
	}
	else if (nose == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (NOSEGONE);
		else return (MISSING_NOSE);
	}
	else //if (g.special[SPECIALWOUND_RIGHTEYE] == 0 ||
		 //g.special[SPECIALWOUND_LEFTEYE] == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (ONE_EYE);
		else return (MISSING_EYE);
	}
}
string getHealthStat(CreatureHealth g, const char smll) {

	bool bleeding = false;

	for (int w = 0; w < BODYPARTNUM; w++)
	{
		if (g.wound[w] & WOUND_BLEEDING)bleeding = true;
	}

	int armok = 2, legok = 2;
	if (g.wound[BODYPART_ARM_RIGHT] & (WOUND_NASTYOFF | WOUND_CLEANOFF)) { armok--; }
	if (g.wound[BODYPART_ARM_LEFT] & (WOUND_NASTYOFF | WOUND_CLEANOFF)) { armok--; }
	if (g.wound[BODYPART_LEG_RIGHT] & (WOUND_NASTYOFF | WOUND_CLEANOFF)) { legok--; }
	if (g.wound[BODYPART_LEG_LEFT] & (WOUND_NASTYOFF | WOUND_CLEANOFF)) { legok--; }


	if (bleeding)set_color_easy(RED_ON_BLACK_BRIGHT);
	else set_color_easy(WHITE_ON_BLACK_BRIGHT);

	if (!g.alive || g.blood < 100) {
		return bleedingOut(g.alive, g.blood, smll);
	}
	else if (g.special[SPECIALWOUND_NECK] == 2)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (NCKBROKE);
		else return (NECK_BROKEN);
	}
	else if (g.special[SPECIALWOUND_UPPERSPINE] == 2)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (QUADPLEG);
		else return (QUADRAPLEGIC);
	}
	else if (g.special[SPECIALWOUND_LOWERSPINE] == 2)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (PARAPLEG);
		else return (PARAPLEGIC);
	}
	else if (g.special[SPECIALWOUND_RIGHTEYE] == 0 &&
		g.special[SPECIALWOUND_LEFTEYE] == 0 &&
		g.special[SPECIALWOUND_NOSE] == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (FACEGONE);
		else return (FACE_GONE);
	}
	else if (armok != 2 || legok != 2) {
		return missingArmAndOrLeg(armok, legok, smll, bleeding);
	}
	else if (g.special[SPECIALWOUND_RIGHTEYE] == 0 ||
		g.special[SPECIALWOUND_LEFTEYE] == 0 ||
		g.special[SPECIALWOUND_NOSE] == 0) {
		return missingPartOfFace(g.special[SPECIALWOUND_LEFTEYE], g.special[SPECIALWOUND_RIGHTEYE], g.special[SPECIALWOUND_NOSE], bleeding, smll);
	}
	else if (g.special[SPECIALWOUND_TONGUE] == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (NOTONGUE);
		else return (NO_TONGUE);
	}
	else if (g.special[SPECIALWOUND_TEETH] == 0)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		return (NO_TEETH);
	}
	else if (g.special[SPECIALWOUND_TEETH] < TOOTHNUM)
	{
		if (!bleeding)set_color_easy(GREEN_ON_BLACK);
		if (smll)return (MISTEETH);
		else return (MISSING_TEETH);
	}
	else
	{
		return perfectlyHealthy(g.align, g.animalgloss, smll);
	}
}
/* prints a character's health description (One Leg, Liberal, NearDETH...) */
void printhealthstat(CreatureHealth g, int y, int x, char smll)
{
	// TODO remove direct usage of this function outside cursesAlternative.cpp
	string wound = getHealthStat(g, smll);
	mvaddstrAlt(y, x, wound);
}
void printAttributesAsKnowledgePermits(CreatureAttributeList cr, unsigned char knowledge) {
	mvaddstrAlt(2, 0, HRT_COLON + ((knowledge > 0) ? tostring(cr.get_attribute(ATTRIBUTE_HEART)) : QUESTION_MARK));
	mvaddstrAlt(3, 0, INT_COLON + ((knowledge > 0) ? tostring(cr.get_attribute(ATTRIBUTE_INTELLIGENCE)) : QUESTION_MARK));
	mvaddstrAlt(4, 0, WIS_COLON + ((knowledge > 0) ? tostring(cr.get_attribute(ATTRIBUTE_WISDOM)) : QUESTION_MARK));
	mvaddstrAlt(5, 0, HLTH_COLON + ((knowledge > 1) ? tostring(cr.get_attribute(ATTRIBUTE_HEALTH)) : QUESTION_MARK));
	mvaddstrAlt(2, 11, AGI_COLON + ((knowledge > 1) ? tostring(cr.get_attribute(ATTRIBUTE_AGILITY)) : QUESTION_MARK));
	mvaddstrAlt(3, 11, STR_COLON + ((knowledge > 1) ? tostring(cr.get_attribute(ATTRIBUTE_STRENGTH)) : QUESTION_MARK));
	mvaddstrAlt(4, 11, CHAR_COLON + ((knowledge > 0) ? tostring(cr.get_attribute(ATTRIBUTE_CHARISMA)) : QUESTION_MARK));
}
void set_color_for_disguise(DeprecatedCreature* cr) {

	switch (hasdisguise(*cr))
	{
	case 1:set_color_easy(GREEN_ON_BLACK_BRIGHT); break;
	case 2:set_color_easy(YELLOW_ON_BLACK_BRIGHT); break;
	default:
		if (cr->get_armor().get_stealth_value() > 1)
			set_color_easy(BLACK_ON_BLACK_BRIGHT);
		else set_color_easy(RED_ON_BLACK_BRIGHT);
	}
	if (sitealarmtimer >= 0 || isThereASiteAlarm())
		if (cr->get_armor().get_stealth_value() > 1)
			set_color_easy(BLACK_ON_BLACK_BRIGHT);

}
void printWounds(DeprecatedCreature *cr) {

	for (int w = 0; w < BODYPARTNUM; w++)
	{
		if (cr->getCreatureHealth().wound[w] & WOUND_BLEEDING)set_color_easy(RED_ON_BLACK_BRIGHT);
		else set_color_easy(WHITE_ON_BLACK);
		moveAlt(2 + w, 49);
		switch (w)
		{
		case BODYPART_HEAD:addstrAlt(HEAD_COLON); break;
		case BODYPART_BODY:addstrAlt(BODY_COLON); break;
		case BODYPART_ARM_RIGHT:addstrAlt(RIGHT_ARM_COLON); break;
		case BODYPART_ARM_LEFT:addstrAlt(LEFT_ARM_COLON); break;
		case BODYPART_LEG_RIGHT:addstrAlt(RIGHT_LEG_COLON); break;
		case BODYPART_LEG_LEFT:addstrAlt(LEFT_LEG_COLON); break;
		}
		moveAlt(2 + w, 61);
		if (cr->getCreatureHealth().wound[w] & WOUND_NASTYOFF)addstrAlt(RIPPED_OFF);
		else if (cr->getCreatureHealth().wound[w] & WOUND_CLEANOFF)addstrAlt(CLEAN_SEVER);
		else
		{
			int sum = 0;
			if (cr->getCreatureHealth().wound[w] & WOUND_SHOT)sum++;
			if (cr->getCreatureHealth().wound[w] & WOUND_CUT)sum++;
			if (cr->getCreatureHealth().wound[w] & WOUND_BRUISED)sum++;
			if (cr->getCreatureHealth().wound[w] & WOUND_BURNED)sum++;
			if (cr->getCreatureHealth().wound[w] & WOUND_TORN)sum++;
			if (sum == 0)
			{
				set_color_easy(GREEN_ON_BLACK_BRIGHT);
				if (cr->getCreatureHealth().animalgloss == ANIMALGLOSS_ANIMAL)
					addstrAlt(CONST_X_ANIMAL);
				else addstrAlt(CONST_X_LIBERAL);
			}
			if (cr->getCreatureHealth().wound[w] & WOUND_SHOT) { addstrAlt(CONST_X_SHT); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr->getCreatureHealth().wound[w] & WOUND_BRUISED) { addstrAlt(CONST_X_BRS); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr->getCreatureHealth().wound[w] & WOUND_CUT) { addstrAlt(CONST_X_CUT); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr->getCreatureHealth().wound[w] & WOUND_TORN) { addstrAlt(CONST_X_TRN); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr->getCreatureHealth().wound[w] & WOUND_BURNED) { addstrAlt(CONST_X_BRN); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
		}
	}
}
/* character info at top of screen */
void printcreatureinfo(DeprecatedCreature *cr, unsigned char knowledge)
{


	makedelimiter(1);
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(1, 2, cr->getNameAndAlignment().name);
	addstrAlt(COMMA_SPACE);
	addstrAlt(gettitle(cr->getCreatureHealth().align, cr->juice));
	if (cr->is_holding_body())
	{
		string prisoner_info = COMMA_HOLDING;
		if (prisoner_description.count(cr->get_prisoner_type()) >= 1) {
			prisoner_info += prisoner_description[cr->get_prisoner_type()];
		}
		else {
			prisoner_info += cr->get_prisoner_name();
		}
		addstrAlt(prisoner_info);
	}
	printAttributesAsKnowledgePermits(cr->getCreatureAttributeList(), knowledge);
	mvaddstrAlt(5, 11, TRANS_COLON);
	long v = -1;
	if (showcarprefs == 1)v = id_getcar(cr->pref_carid);
	else v = id_getcar(cr->carid);
	string str;
	if (v != -1 && showcarprefs != -1)
	{
		(str = getVehicleShortname(v));
		char d;
		if (showcarprefs == 1)d = cr->pref_is_driver;
		else d = cr->is_driver;
		if (d)(str += CONST_X_DASH_D);
	}
	else
	{
		int legok = 2;
		if ((cr->getCreatureHealth().wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF) ||
			(cr->getCreatureHealth().wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF))legok--;
		if ((cr->getCreatureHealth().wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF) ||
			(cr->getCreatureHealth().wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF))legok--;
		if (cr->flag & CREATUREFLAG_WHEELCHAIR) { (str = WHEEL_CHAIR); }
		else if (legok >= 1) { (str = CONST_X_ON_FOOT); }
		else { (str = ON_FOOT); }
	}
	addstrAlt(str);
	if (mode != GAMEMODE_SITE) { 
		set_color_easy(WHITE_ON_BLACK); 
	}
	else {
		switch (weaponcheck(*cr))
		{
		case -1:
		case 0:set_color_easy(GREEN_ON_BLACK_BRIGHT); break;
		case 1:set_color_easy(YELLOW_ON_BLACK_BRIGHT); break;
		case 2:set_color_easy(RED_ON_BLACK_BRIGHT); break;
		}
	}
	mvaddstrAlt(6, 0, WEAPON_COLON);
	addstrAlt(cr->get_weapon_string(1));
	if (mode != GAMEMODE_SITE)
	{
		set_color_for_armor(cr->get_armor());
	}
	else
	{
		set_color_for_disguise(cr);
	}
	mvaddstrAlt(7, 0, CLOTHES_COLON);
	addstrAlt(cr->get_armor_string(false));
	set_color_easy(WHITE_ON_BLACK);
	char used[SKILLNUM];
	memset(used, 0, sizeof(char)*SKILLNUM);
	int snum = 5;
	char printed = 1;
	while (snum > 0 && printed)
	{
		printed = 0;
		int max = 0;
		long maxs = -1;
		for (int s = 0; s < SKILLNUM; s++)
		{
			if ((cr->get_skill(s) * 10000 + cr->get_skill_ip(s)) > max && !used[s])
			{
				max = (cr->get_skill(s) * 10000 + cr->get_skill_ip(s));
				maxs = s;
			}
		}
		if (maxs != -1)
		{
			used[maxs] = 1;
			printed = 1;
			// Maxed skills are cyan
			if (cr->skill_cap(maxs) != 0 && cr->get_skill(maxs) >= cr->skill_cap(maxs))set_color_easy(CYAN_ON_BLACK_BRIGHT);
			// About to level up skills are white
			else if (cr->get_skill_ip(maxs) >= 100 + (10 * cr->get_skill(maxs)) &&
				cr->get_skill(maxs) < cr->skill_cap(maxs))set_color_easy(WHITE_ON_BLACK_BRIGHT);
			// <1 skills are dark gray
			else if (cr->get_skill(maxs) < 1)set_color_easy(BLACK_ON_BLACK_BRIGHT);
			// >=1 skills are light gray
			else set_color_easy(WHITE_ON_BLACK);
			moveAlt(3 + 5 - snum, 31);
			if (knowledge > 5 - snum)
				addstrAlt(skill_enum_to_string(maxs));
			else addstrAlt(SEVEN_QUESTION_MARKS);
			addstrAlt(CONST_X_COLON_SPACE);
			if (knowledge > 7 - snum)
				addstrAlt(cr->get_skill(maxs));
			else addcharAlt('?');
			if (snum == 5 && printed)
			{
				set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(2, 31, TOP_SKILLS_COLON);
			}
		}
		snum--;
	}
	int woundsum = 0;
	for (int w = 0; w < BODYPARTNUM; w++)
		if (cr->getCreatureHealth().wound[w] != 0)woundsum++;
	printhealthstat(cr->getCreatureHealth(), 1, 49, FALSE);
	if (woundsum > 0)
	{
		printWounds(cr);
		set_color_easy(WHITE_ON_BLACK);
	}
}

void clearRowsTwoThroughSeven() {
	for (int i = 2; i < 8; i++)
	{
		mvaddstrAlt(i, 0, FIFTY_OR_SO_SPACES); // 80 spaces
	}
}

/* party info at top of screen */
void printparty()
{
	DeprecatedCreature *party[6] = { NULL,NULL,NULL,NULL,NULL,NULL };
	if (activesquad != NULL)
		for (int p = 0; p < 6; p++)party[p] = activesquad->squad[p];
	set_color_easy(WHITE_ON_BLACK);
	clearRowsTwoThroughSeven();
	if (party_status != -1 && party[party_status] == NULL)party_status = -1;
	if (party_status != -1)
	{
		printcreatureinfo(party[party_status]);
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		mvaddstrAlt(1, 0, party_status + 1);
	}
	else
	{
		char str[200];
		mvaddstrAlt(1, 0, CODENAME_SKILL_WEAPON_ARMOR_HEALTH_HEADER); // 80 characters
		for (int p = 0; p < 6; p++)
		{
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(p + 2, 0, FIFTY_OR_SO_SPACES); // 80 spaces
			mvaddcharAlt(p + 2, 0, '1' + p);
			if (party[p] != NULL)
			{
				if (party[p]->is_holding_body())set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
				else set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(p + 2, 2, party[p]->getNameAndAlignment().name);
				if (party[p]->is_holding_body())addstrAlt(CONST_X_H);
				int skill = 0;
				char bright = 0;
				for (int sk = 0; sk < SKILLNUM; sk++)
				{
					skill += (int)party[p]->get_skill(sk);
					if (party[p]->get_skill_ip(sk) >= 100 + (10 * party[p]->get_skill(sk)) &&
						party[p]->get_skill(sk) < party[p]->skill_cap(sk))bright = 1;
				}
				set_color_easy(bright ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
				mvaddstrAlt(p + 2, 23, skill);
				addstrAlt(CONST_X_SLASH);
				addstrAlt(party[p]->get_weapon_skill());
				moveAlt(p + 2, 31);
				if (mode != GAMEMODE_SITE) { set_color_easy(WHITE_ON_BLACK); }
				// TODO This is key to the weapon display being red when back at base bug
				// Figure out how
				else {
					switch (weaponcheck(*party[p]))
					{
					case -1:
					case 0:set_color_easy(GREEN_ON_BLACK_BRIGHT); break;
					case 1:set_color_easy(YELLOW_ON_BLACK_BRIGHT); break;
					case 2:set_color_easy(RED_ON_BLACK_BRIGHT); break;
					}
				}
				if (party[p]->has_thrown_weapon && party[p]->has_extra_throwing_weapons())
					addstrAlt(party[p]->get_name_next_throwing_weapon());
				else addstrAlt(party[p]->get_weapon().get_shortname(0));
				//set_color_easy(WHITE_ON_BLACK);
				if (party[p]->get_weapon().get_ammoamount() > 0)
				{
					//set_color_easy(WHITE_ON_BLACK);
					addstrAlt(CONST_SpaceOpenParenthesis);
					addstrAlt(party[p]->get_weapon().get_ammoamount());
					addstrAlt(CLOSE_PARENTHESIS);
				}
				else if (party[p]->get_weapon().uses_ammo())
				{
					set_color_easy(BLACK_ON_BLACK_BRIGHT);
					if (party[p]->has_clips())
					{
						addstrAlt(CONST_SpaceOpenParenthesis);
						addstrAlt(party[p]->count_clips());
						addstrAlt(CLOSE_PARENTHESIS);
					}
					else
						addstrAlt(X_X_PARENTHESIS);
				}
				else if (party[p]->get_weapon().is_throwable() && !party[p]->has_thrown_weapon)
					addstrAlt(ONE_PARENTHESIS);
				else if (party[p]->has_thrown_weapon && party[p]->has_extra_throwing_weapons())
				{
					set_color_easy(BLACK_ON_BLACK_BRIGHT);
					addstrAlt(CONST_SpaceOpenParenthesis);
					addstrAlt(party[p]->count_weapons() - party[p]->is_armed());
					addstrAlt(CLOSE_PARENTHESIS);
				}
				if (mode != GAMEMODE_SITE)
				{
					setColorForArmor(party[p]->get_armor());
				}
				else
				{
					switch (hasdisguise(*party[p]))
					{
					case 1:set_color_easy(GREEN_ON_BLACK_BRIGHT); break;
					case 2:set_color_easy(YELLOW_ON_BLACK_BRIGHT); break;
					default:
						if (party[p]->get_armor().get_stealth_value() > 1)
							set_color_easy(BLACK_ON_BLACK_BRIGHT);
						else set_color_easy(RED_ON_BLACK_BRIGHT);
						break;
					}
					if (sitealarmtimer >= 0 || isThereASiteAlarm())
						if (party[p]->get_armor().get_stealth_value() > 1)
							set_color_easy(BLACK_ON_BLACK_BRIGHT);
				}
				mvaddstrAlt(p + 2, 46, party[p]->get_armor().get_shortname());
				printhealthstat(party[p]->getCreatureHealth(), p + 2, 61, TRUE);
				set_color_easy(WHITE_ON_BLACK);
				moveAlt(p + 2, 70);
				long v = -1;
				if (showcarprefs == 1)v = id_getcar(party[p]->pref_carid);
				else v = id_getcar(party[p]->carid);
				if (v != -1 && showcarprefs != -1)
				{
					strcpy(str, getVehicleShortname(v).c_str());
					if (showcarprefs == 1 ? party[p]->pref_is_driver : party[p]->is_driver)strcat(str, CONST_X_DASH_D.c_str());
				}
				else
				{
					int legok = 2;
					if ((party[p]->getCreatureHealth().wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF) ||
						(party[p]->getCreatureHealth().wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF))legok--;
					if ((party[p]->getCreatureHealth().wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF) ||
						(party[p]->getCreatureHealth().wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF))legok--;
					if (party[p]->flag & CREATUREFLAG_WHEELCHAIR)strcpy(str, WHEEL_CHAIR.c_str());
					else if (legok >= 1)strcpy(str, CONST_X_ON_FOOT.c_str());
					else strcpy(str, ON_FOOT.c_str());
				}
				addstrAlt(str);
			}
		}
	}
	makedelimiter();
}
void printwoundstat(CreatureHealth cr, int y, int x)
{
	// Add wound status
	for (int w = 0; w < BODYPARTNUM; w++)
	{
		if (cr.wound[w] & WOUND_BLEEDING)set_color_easy(RED_ON_BLACK_BRIGHT);
		else set_color_easy(WHITE_ON_BLACK);
		moveAlt(y + w, x);
		switch (w)
		{
		case BODYPART_HEAD:addstrAlt(HEAD_COLON); break;
		case BODYPART_BODY:addstrAlt(BODY_COLON); break;
		case BODYPART_ARM_RIGHT:addstrAlt(RIGHT_ARM_COLON); break;
		case BODYPART_ARM_LEFT:addstrAlt(LEFT_ARM_COLON); break;
		case BODYPART_LEG_RIGHT:addstrAlt(RIGHT_LEG_COLON); break;
		case BODYPART_LEG_LEFT:addstrAlt(LEFT_LEG_COLON); break;
		}
		moveAlt(y + w, x + 11);
		if (cr.wound[w] & WOUND_NASTYOFF)addstrAlt(RIPPED_OFF);
		else if (cr.wound[w] & WOUND_CLEANOFF)addstrAlt(SEVERED);
		else
		{
			int sum = 0;
			if (cr.wound[w] & WOUND_SHOT)sum++;
			if (cr.wound[w] & WOUND_CUT)sum++;
			if (cr.wound[w] & WOUND_BRUISED)sum++;
			if (cr.wound[w] & WOUND_BURNED)sum++;
			if (cr.wound[w] & WOUND_TORN)sum++;
			if (sum == 0)
			{
				set_color_easy(GREEN_ON_BLACK_BRIGHT);
				if (cr.animalgloss == ANIMALGLOSS_ANIMAL)
					addstrAlt(CONST_X_ANIMAL);
				else addstrAlt(CONST_X_LIBERAL);
			}
			if (cr.wound[w] & WOUND_SHOT) { addstrAlt(CONST_X_SHOT); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr.wound[w] & WOUND_BRUISED) { addstrAlt(BRUISED); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr.wound[w] & WOUND_CUT) { addstrAlt(CONST_X_CUT); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr.wound[w] & WOUND_TORN) { addstrAlt(CONST_X_TORN); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
			if (cr.wound[w] & WOUND_BURNED) { addstrAlt(CONST_X_BURNED); sum--; if (sum > 0)addstrAlt(CONST_X_SINGLE_COMMA); }
		}
	}
}
string juiceUntilLevelUp(const int juice) {

	string howMuchJuice;
	if (juice < 1000)
	{
		howMuchJuice = NEXT_COLON;
		if (juice < 0) howMuchJuice += tag_0;
		else if (juice < 10) howMuchJuice += CONST_X_NUM_10;
		else if (juice < 50) howMuchJuice += CONST_X_NUM_50;
		else if (juice < 100) howMuchJuice += ONE_HUNDRED;
		else if (juice < 200) howMuchJuice += TWO_HUNDRED;
		else if (juice < 500) howMuchJuice += FIVE_HUNDRED;
		else  howMuchJuice += ONE_THOUSAND;
	}
	return howMuchJuice;
}

string twoDigits(const int x) {
	return x < 10 ? tostring(0) + tostring(x) : tostring(x);
}
void printCreatureAttributes(DeprecatedCreature &cr) {

	mvaddstrAlt(5, 0, HEART_COLON);
	addstrAlt(cr.get_attribute(ATTRIBUTE_HEART, true));
	mvaddstrAlt(6, 0, INTELLIGENCE_COLON);
	addstrAlt(cr.get_attribute(ATTRIBUTE_INTELLIGENCE, true));
	mvaddstrAlt(7, 0, WISDOM_COLON);
	addstrAlt(cr.get_attribute(ATTRIBUTE_WISDOM, true));
	mvaddstrAlt(8, 0, HEALTH_COLON);
	addstrAlt(cr.get_attribute(ATTRIBUTE_HEALTH, true));
	mvaddstrAlt(9, 0, AGILITY_COLON);
	addstrAlt(cr.get_attribute(ATTRIBUTE_AGILITY, true));
	mvaddstrAlt(10, 0, STRENGTH_COLON);
	addstrAlt(cr.get_attribute(ATTRIBUTE_STRENGTH, true));
	mvaddstrAlt(11, 0, CHARISMA_COLON);
	addstrAlt(cr.get_attribute(ATTRIBUTE_CHARISMA, true));
}
void printCreatureSkills(DeprecatedCreature &cr) {
	char used[SKILLNUM];
	memset(used, 0, sizeof(char)*SKILLNUM);
	int skills_max = 16;
	char printed = 1;
	for (int skills_shown = 0; skills_shown < skills_max&&printed; skills_shown++)
	{
		printed = 0;
		int max = 0;
		long maxs = -1;
		for (int s = 0; s < SKILLNUM; s++)
		{
			if ((cr.get_skill(s) * 10000 + cr.get_skill_ip(s)) > max && !used[s])
			{
				max = (cr.get_skill(s) * 10000 + cr.get_skill_ip(s));
				maxs = s;
			}
		}
		if (maxs != -1)
		{
			used[maxs] = 1;
			printed = 1;
			// Maxed skills are cyan
			if (cr.skill_cap(maxs) != 0 && cr.get_skill(maxs) >= cr.skill_cap(maxs))set_color_easy(CYAN_ON_BLACK_BRIGHT);
			// About to level up skills are white
			else if (cr.get_skill_ip(maxs) >= 100 + (10 * cr.get_skill(maxs)) &&
				cr.get_skill(maxs) < cr.skill_cap(maxs))set_color_easy(WHITE_ON_BLACK_BRIGHT);
			// <1 skills are dark gray
			else if (cr.get_skill(maxs) < 1)set_color_easy(BLACK_ON_BLACK_BRIGHT);
			// >=1 skills are light gray
			else set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(6 + skills_shown, 28, skill_enum_to_string(maxs));
			addstrAlt(CONST_X_COLON_SPACE);
			moveAlt(6 + skills_shown, 42);
			addstrAlt(twoDigits(cr.get_skill(maxs)) + CONST_X_DOT);
			if (cr.get_skill_ip(maxs) < 100 + (10 * cr.get_skill(maxs)))
			{
				if ((cr.get_skill_ip(maxs) * 100) / (100 + (10 * cr.get_skill(maxs))) != 0)
				{
					if ((cr.get_skill_ip(maxs) * 100) / (100 + (10 * cr.get_skill(maxs))) < 10)
						addcharAlt('0');
					addstrAlt((cr.get_skill_ip(maxs) * 100) / (100 + (10 * cr.get_skill(maxs))));
				}
				else addstrAlt(DOUBLE_ZERO);
			}
			else addstrAlt(NINETY_NINE_PLUS);
			if (cr.skill_cap(maxs) == 0 || cr.get_skill(maxs) < cr.skill_cap(maxs))
				set_color_easy(BLACK_ON_BLACK_BRIGHT);
			moveAlt(6 + skills_shown, 48);
			addstrAlt(twoDigits(cr.skill_cap(maxs)) + POINT_DOUBLE_ZERO);
		}
	}
}
void printliberalstats_a(const CreatureBio cr, const CreatureJustice cr_2, const int flag) {


	set_color_easy(WHITE_ON_BLACK);
	// Add name
	mvaddstrAlt(2, 0, NAME_COLON);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(cr_2.name);
	set_color_easy(WHITE_ON_BLACK);
	if (strcmp(cr_2.propername.data(), cr_2.name.data()) != 0)
	{
		//The names do not match, print real name as well
		addstrAlt(CONST_SpaceOpenParenthesis);
		addstrAlt(cr_2.propername);
		addstrAlt(CLOSE_PARENTHESIS);
	}
	addstrAlt(COMMA_SPACE);
	addstrAlt(gettitle(cr_2.align, cr_2.juice));
	addstrAlt(CONST_SpaceOpenParenthesis);
	addstrAlt(cr_2.get_type_name);
	addstrAlt(CLOSE_PARENTHESIS);
	moveAlt(3, 0);
	// Add birthdate
	addstrAlt(BORN_SPACE);
	addstrAlt(getmonth(cr.birthday_month));
	addstrAlt(singleSpace);
	addstrAlt(cr.birthday_day);
	addstrAlt(COMMA_SPACE);
	if (cr.birthday_month < month ||
		(cr.birthday_month == month && cr.birthday_day <= day))
		addstrAlt(tostring(year - cr.age));
	else addstrAlt(tostring(year - 1 - cr.age));
	// Add age
	addstrAlt(AGE_SPACE);
	addstrAlt(tostring(cr.age));
	// Assess their gender in an Elite Liberal way
	if (cr.gender_liberal == GENDER_MALE)
		addstrAlt(COMMA_MALE);
	else if (cr.gender_liberal == GENDER_FEMALE)
		addstrAlt(COMMA_FEMALE);
	else addstrAlt(COMMA_GENDERQUEER);
	// DON'T Note if there's some conflict with Conservative society's perceptions
	//if(cr.gender_liberal != cr.gender_conservative && cr.gender_liberal != GENDER_NEUTRAL)
	//   addstrAlt(ASTERISK);
	addstrAlt(CLOSE_PARENTHESIS);
	moveAlt(3, 46);
	statebrokenlaws(cr_2, flag);
	set_color_easy(WHITE_ON_BLACK);
	// Add juice
	mvaddstrAlt(10, 16, JUICE_COLON);
	addstrAlt(cr_2.juice);
	mvaddstrAlt(11, 16, juiceUntilLevelUp(cr_2.juice));

}

void printliberalstats_c(const CreatureCar cr, const CreatureInventory cr_2, const CreatureHealth cr_3, const int flag) {


	set_color_easy(WHITE_ON_BLACK);
	// Add weapon
	mvaddstrAlt(13, 0, WEAPON_COLON);
	addstrAlt(cr_2.get_weapon_string);
	// Add clothing
	mvaddstrAlt(14, 0, CLOTHES_COLON);
	addstrAlt(cr_2.get_armor_string);
	// Add vehicle
	mvaddstrAlt(15, 0, CAR_COLON);
	long v = -1;
	if (showcarprefs == 1)v = id_getcar(cr.pref_carid);
	else v = id_getcar(cr.carid);
	if (v != -1 && showcarprefs != -1)
	{
		addstrAlt(getVehicleShortname(v));
		char d;
		if (showcarprefs == 1)d = cr.pref_is_driver;
		else d = cr.is_driver;
		if (d)addstrAlt(CONST_X_DASH_D);
	}
	else
	{
		int legok = 2;
		if ((cr_3.wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF) ||
			(cr_3.wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF))legok--;
		if ((cr_3.wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF) ||
			(cr_3.wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF))legok--;
		if (flag & CREATUREFLAG_WHEELCHAIR)addstrAlt(WHEEL_CHAIR);
		else if (legok >= 1)addstrAlt(CONST_X_ON_FOOT);
		else addstrAlt(ON_FOOT);
	}

}
void printliberalstats_d(DeprecatedCreature &cr) {

	// Add recruit stats
	if (cr.flag != CREATUREFLAG_BRAINWASHED)
	{
		mvaddstrAlt(18, 55, maxsubordinates(cr) - subordinatesleft(cr));
		addstrAlt(RECRUITS_SLASH);
		addstrAlt(maxsubordinates(cr));
		addstrAlt(SPACE_MAX);
	}
	else
	{
		mvaddstrAlt(18, 55, ENLIGHTENED);
		addstrAlt(CANT_RECRUIT);
	}
	// Any meetings with potential recruits scheduled?
	if (scheduledmeetings(cr))
	{
		mvaddstrAlt(20, 55, SCHEDULED_MEETINGS);
		addstrAlt(scheduledmeetings(cr));
	}
	// Add seduction stats
	moveAlt(19, 55);
	int lovers = loveslaves(cr);
	if (cr.flag & CREATUREFLAG_LOVESLAVE)
		lovers++;
	if (lovers)
	{
		addstrAlt(lovers);
		addstrAlt(ROMANTIC_INTEREST);
		if (lovers > 1)addstrAlt(LETTER_S);
	}
	// Any dates with potential love interests scheduled?
	if (scheduleddates(cr))
	{
		mvaddstrAlt(21, 55, SCHEDULED_DATES);
		addstrAlt(scheduleddates(cr));
	}


}
void printliberalstats_e(const CreatureHealth getCreatureHealth) {


	printwoundstat(getCreatureHealth, 5, 55);
	//SPECIAL WOUNDS
	{
		set_color_easy(RED_ON_BLACK);
		int y = 17;
		for (string str : printSpecialWounds(getCreatureHealth.special)) {

			mvaddstrAlt(y++, 0, str);
		}
	}


}
void printliberalstats_f(DeprecatedCreature &cr) {


	set_color_easy(WHITE_ON_BLACK);
	for (int i = 0, y = 12; i < AUGMENTATIONNUM; i++, y++)
	{
		if (cr.get_augmentation(i).type == -1) continue;
		mvaddstrAlt(y, 55, Augmentation::get_name(i));
		addstrAlt(CONST_X_COLON_SPACE);
		addstrAlt(cr.get_augmentation(i).name);
	}

}

void printliberalstats(DeprecatedCreature &cr)
{
	printliberalstats_a(cr.getCreatureBio(), cr.getCreatureJustice(), cr.flag);

	// Add attributes
	printCreatureAttributes(cr);
	// Add highest skills
	mvaddstrAlt(5, 28, CONST_X_SKILL);
	mvaddstrAlt(5, 43, NOW_MAX);
	printCreatureSkills(cr);

	printliberalstats_c(cr.getCreatureCar(), cr.getCreatureInventory(), cr.getCreatureHealth(), cr.flag);
	printliberalstats_d(cr);
	printliberalstats_e(cr.getCreatureHealth());
	printliberalstats_f(cr);
}
/* Full screen character sheet, skills only edition */
void printliberalskills(CreatureJustice cr, ListOfCreatureSkills cr_2) {

	// Add name
	set_color_easy(WHITE_ON_BLACK);
	moveAlt(2, 0);
	if (strcmp(cr.propername.data(), cr.name.data()) != 0)
		addstrAlt(CODE_NAME_COLON);
	else addstrAlt(NAME_COLON);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(cr.name);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(COMMA_SPACE);
	addstrAlt(gettitle(cr.align, cr.juice));
	addstrAlt(CONST_SpaceOpenParenthesis);
	addstrAlt(cr.get_type_name);
	addstrAlt(CLOSE_PARENTHESIS);
	// Add all skills
	for (int s = 0; s < SKILLNUM; s++)
	{
		if (s % 3 == 0 && s < 9)
		{
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(4, 27 * (s / 3));
			addstrAlt(CONST_X_SKILL);
			moveAlt(4, 15 + 27 * (s / 3));
			addstrAlt(NOW_MAX);
		}
		// Maxed skills are cyan
		if (cr_2.skill_cap(s) != 0 && cr_2.get_skill(s) >= cr_2.skill_cap(s))set_color_easy(CYAN_ON_BLACK_BRIGHT);
		// About to level up skills are white
		else if (cr_2.get_skill_ip(s) >= 100 + (10 * cr_2.get_skill(s)) &&
			cr_2.get_skill(s) < cr_2.skill_cap(s))set_color_easy(WHITE_ON_BLACK_BRIGHT);
		// <1 skills are dark gray
		else if (cr_2.get_skill(s) < 1)set_color_easy(BLACK_ON_BLACK_BRIGHT);
		// >=1 skills are light gray
		else set_color_easy(WHITE_ON_BLACK);
		moveAlt(5 + s / 3, 27 * (s % 3));
		addstrAlt(skill_enum_to_string(s));
		addstrAlt(CONST_X_COLON_SPACE);
		moveAlt(5 + s / 3, 14 + 27 * (s % 3));
		addstrAlt(twoDigits(cr_2.get_skill(s)) + CONST_X_DOT);
		if (cr_2.get_skill_ip(s) < 100 + (10 * cr_2.get_skill(s)))
		{
			if ((cr_2.get_skill_ip(s) * 100) / (100 + (10 * cr_2.get_skill(s))) != 0)
			{
				if ((cr_2.get_skill_ip(s) * 100) / (100 + (10 * cr_2.get_skill(s))) < 10)
					addstrAlt(tag_0);
				addstrAlt((cr_2.get_skill_ip(s) * 100) / (100 + (10 * cr_2.get_skill(s))));
			}
			else addstrAlt(DOUBLE_ZERO);
		}
		else addstrAlt(NINETY_NINE_PLUS);
		if (cr_2.skill_cap(s) == 0 || cr_2.get_skill(s) < cr_2.skill_cap(s))
			set_color_easy(BLACK_ON_BLACK_BRIGHT);
		moveAlt(5 + s / 3, 20 + 27 * (s % 3));
		addstrAlt(twoDigits(cr_2.skill_cap(s)) + POINT_DOUBLE_ZERO.c_str());
	}
	set_color_easy(WHITE_ON_BLACK);
}

/* Full screen character sheet, crime sheet */
void printliberalcrimes(CreatureJustice cr)
{
	// Add name
	set_color_easy(WHITE_ON_BLACK);
	if (strcmp(cr.propername.data(), cr.name.data()) != 0)
		mvaddstrAlt(2, 0, CODE_NAME_COLON);
	else mvaddstrAlt(2, 0, NAME_COLON);
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	addstrAlt(cr.name);
	set_color_easy(WHITE_ON_BLACK);
	addstrAlt(COMMA_SPACE);
	addstrAlt(gettitle(cr.align, cr.juice));
	addstrAlt(CONST_SpaceOpenParenthesis);
	addstrAlt(cr.get_type_name);
	addstrAlt(CLOSE_PARENTHESIS);
	// Show outstanding convictions in addition to untried crimes
	if (cr.deathpenalty)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		if (LocationsPool::getInstance().getLocationType(cr.location) == SITE_GOVERNMENT_PRISON)
			mvaddstrAlt(3, 0, ON_DEATH_ROW);
		else mvaddstrAlt(3, 0, SENTENCED_TO_DEATH);
	}
	else if (cr.sentence < 0)
	{
		set_color_easy(RED_ON_BLACK_BRIGHT);
		if (LocationsPool::getInstance().getLocationType(cr.location) == SITE_GOVERNMENT_PRISON)
			mvaddstrAlt(3, 0, SERVING_LIFE_IN_PRISON);
		else mvaddstrAlt(3, 0, SENTENCED_TO_LIFE_IN_PRISON);
	}
	else if (cr.sentence > 0)
	{
		set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		if (LocationsPool::getInstance().getLocationType(cr.location) == SITE_GOVERNMENT_PRISON)
			mvaddstrAlt(3, 0, SERVING_SPACE);
		else mvaddstrAlt(3, 0, SENTENCED_TO_SPACE);
		addstrAlt(cr.sentence);
		addstrAlt(MONTHS_IN_PRISON);
	}
	// Add all crimes
	for (int i = 0; i < LAWFLAGNUM; i++)
	{
		if (i % 2 == 0 && i < 4)
		{
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(4, 40 * (i / 2), CONST_X_CRIME);
			mvaddstrAlt(4, 30 + 40 * (i / 2), CONST_X_NUM);
		}
		// Commited crimes are yellow
		if (cr.crimes_suspected[i] > 0)
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		else set_color_easy(BLACK_ON_BLACK_BRIGHT);
		mvaddstrAlt(5 + i / 2, 40 * (i % 2), getlawflag(i) + CONST_X_COLON_SPACE);
		mvaddstrAlt(5 + i / 2, 30 + 40 * (i % 2), twoDigits(cr.crimes_suspected[i]));
	}
	set_color_easy(WHITE_ON_BLACK);
}
/* full character sheet (with surrounding interface) */
void fullstatus(const int _p)
{
	int p = _p;
	if (isThereNoActivesquad())return;
	const int pagenum = 3;
	int page = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(GREEN_ON_BLACK_BRIGHT);
		mvaddstrAlt(0, 0, PROFILE_OF_A_LIBERAL);
		if (page == 0) { 
			printliberalstats(*activesquad->squad[p]);
		}
		else if (page == 1) printliberalskills(activesquad->squad[p]->getCreatureJustice(), activesquad->squad[p]->getListOfCreatureSkills());
		else if (page == 2) printliberalcrimes(activesquad->squad[p]->getCreatureJustice());
		mvaddstrAlt(23, 0, N_CHANGE_CODENAME_G_FIX_GENDER_LABEL);
		if (activesquad->squad[1] != NULL)
			addstrAlt(LEFT_RIGHT_OTHER_LIBERALS);
		mvaddstrAlt(24, 0, PRESS_KEY_TO_CONTINUE_STRUGGLE);
		addstrAlt(UP_DOWN_MORE_INFO);
		int c = getkeyAlt();
		if (activesquad->squad[1] != NULL && ((c == KEY_LEFT) || (c == KEY_RIGHT)))
		{
			int sx = (c == KEY_LEFT) ? -1 : 1;
			do p = (p + 6 + sx) % 6; while (activesquad->squad[p] == NULL);
		}
		else if (c == KEY_DOWN)
		{
			page++;
			page %= pagenum;
		}
		else if (c == KEY_UP)
		{
			page--;
			if (page < 0) page = pagenum - 1;
			page %= pagenum;
		}
		else if (c == 'n')
		{
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(23, 0, WHAT_IS_NEW_CODENAME); // 80 characters
			mvaddstrAlt(24, 0, FIFTY_OR_SO_SPACES); // 80 spaces
			activesquad->squad[p]->new_name();
		}
		else if (c == 'g')
		{
			activesquad->squad[p]->gender_liberal++;
			if (activesquad->squad[p]->gender_liberal > 2)
				activesquad->squad[p]->gender_liberal = 0;
		}
		else break;
	}
}