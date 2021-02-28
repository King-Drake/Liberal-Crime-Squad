


/*
This file is part of Liberal Crime Squad.                                           //
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

#include "../includes68.h"
#include "../constStringactivate_sleepers.h"
void activate_sleeper(DeprecatedCreature *cr)
{
	int state = 0;
	int choice = 0;
	while (true)
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		printfunds();
		mvaddstrAlt(0, 0, TAKING_UNDERCOVER_ACTION_WHAT_WILL);
		addstrAlt(cr->getNameAndAlignment().name);
		addstrAlt(FOCUS_ON);
		printcreatureinfo(cr);
		makedelimiter();
		set_color_easy(state == 'a' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
		mvaddstrAlt(10, 1, A_COMMUNICATION);
		set_color_easy(state == 'b' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
		mvaddstrAlt(11, 1, B_ESPIONAGE);
		set_color_easy(state == 'c' ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
		mvaddstrAlt(12, 1, C_JOIN_ACTIVE_LCS);
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(20, 40, ENTER_CONFIRM_SELECTION);
		switch (state)
		{
		case 'a':
			set_color_easy(cr->activity_type() == ACTIVITY_NONE ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(10, 40, ONE_LAY_LOW);
			set_color_easy(cr->activity_type() == ACTIVITY_SLEEPER_LIBERAL ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(11, 40, TWO_ADVOCATE_LIBERALISM);
			if (subordinatesleft(*cr))
			{
				set_color_easy(cr->activity_type() == ACTIVITY_SLEEPER_RECRUIT ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
				mvaddstrAlt(12, 40, THREE_EXPAND_SLEEPER_NETWORK);
			}
			else
			{
				set_color_easy(BLACK_ON_BLACK_BRIGHT);
				if (cr->flag & CREATUREFLAG_BRAINWASHED)
					mvaddstrAlt(12, 40, THREE_ENLIGHTENED_CANNOT_RECRUIT);
				else mvaddstrAlt(12, 40, THREE_NEED_MORE_JUICE_TO_RECRUIT);
			}
			break;
		case 'b':
			set_color_easy(cr->activity_type() == ACTIVITY_SLEEPER_SPY ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(10, 40, ONE_UNCOVER_SECRETS);
			set_color_easy(cr->activity_type() == ACTIVITY_SLEEPER_EMBEZZLE ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(11, 40, TWO_EMBEZZLE);
			set_color_easy(cr->activity_type() == ACTIVITY_SLEEPER_STEAL ? WHITE_ON_BLACK_BRIGHT : WHITE_ON_BLACK);
			mvaddstrAlt(12, 40, THREE_STEAL);
			break;
		}
		set_color_easy(WHITE_ON_BLACK);
		switch (cr->activity_type())
		{
		case ACTIVITY_NONE:
			mvaddstrAlt(22, 3, cr->getNameAndAlignment().name);
			addstrAlt(WILL_STAY_OUT_OF_TROUBLE);
			break;
		case ACTIVITY_SLEEPER_LIBERAL:
			mvaddstrAlt(22, 3, cr->getNameAndAlignment().name);
			addstrAlt(WILL_BUILD_SUPPORT);
			break;
		case ACTIVITY_SLEEPER_RECRUIT:
			if (subordinatesleft(*cr))
			{
				mvaddstrAlt(22, 3, cr->getNameAndAlignment().name);
				addstrAlt(WILL_TRY_TO_RECRUIT);
			}
			break;
		case ACTIVITY_SLEEPER_SPY:
			mvaddstrAlt(22, 3, cr->getNameAndAlignment().name);
			addstrAlt(WILL_SNOOP);
			break;
		case ACTIVITY_SLEEPER_EMBEZZLE:
			mvaddstrAlt(22, 3, cr->getNameAndAlignment().name);
			addstrAlt(WILL_EMBEZZLE);
			break;
		case ACTIVITY_SLEEPER_STEAL:
			mvaddstrAlt(22, 3, cr->getNameAndAlignment().name);
			addstrAlt(WILL_STEAL);
			break;
		}
		int c = getkeyAlt();
		if (c >= 'a'&&c <= 'z') state = c;
		if ((c >= 'a'&&c <= 'z') || (c >= '1'&&c <= '9'))
		{
			choice = c;
			switch (state)
			{
			case 'a':
				switch (choice)
				{
				default:
				case '1':cr->set_activity_type(ACTIVITY_NONE); break;
				case '2':cr->set_activity_type(ACTIVITY_SLEEPER_LIBERAL); break;
				case '3':
					if (subordinatesleft(*cr))
						cr->set_activity_type(ACTIVITY_SLEEPER_RECRUIT); break;
				}
				break;
			case 'b':
				switch (choice)
				{
				default:
				case '1':cr->set_activity_type(ACTIVITY_SLEEPER_SPY); break;
				case '2':cr->set_activity_type(ACTIVITY_SLEEPER_EMBEZZLE); break;
				case '3':cr->set_activity_type(ACTIVITY_SLEEPER_STEAL); break;
				}
				break;
			}
		}
		if (state == 'c')
		{
			//ActivityST oact=cr->activity;
			cr->set_activity_type(ACTIVITY_SLEEPER_JOINLCS);
		}
		if (c == 'x')
		{
			cr->set_activity_type(ACTIVITY_NONE);
			break;
		}
		else
			if (c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}
/* base - activate sleepers */
void activate_sleepers()
{
	vector<DeprecatedCreature *> temppool = selectOnlySleepersThatCanWork();
	if (!len(temppool)) return;
	sortliberals(temppool, activesortingchoice[SORTINGCHOICE_ACTIVATESLEEPERS]);
	int page = 0;
	while (true)
	{
		music.play(MUSIC_SLEEPERS);
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		printfunds();
		mvaddstrAlt(0, 0, ACTIVATE_SLEEPER);
		makedelimiter(1);
		mvaddstrAlt(1, 4, CODE_NAME_HEADER);
		mvaddstrAlt(1, 25, JOB_HEADER);
		mvaddstrAlt(1, 42, SITE_HEADER);
		mvaddstrAlt(1, 57, ACTIVITY_HEADER);
		int y = 2;
		for (int p = page * 9; p < len(temppool) && p < page * 9 + 9; p++, y += 2)
		{
			set_color_easy(WHITE_ON_BLACK);
			mvaddcharAlt(y, 0, (y - 2) / 2 + 'A'); addstrAlt(spaceDashSpace);
			addstrAlt(temppool[p]->getNameAndAlignment().name);
			mvaddstrAlt(y, 25, temppool[p]->get_type_name());
			mvaddstrAlt(y + 1, 6, EFFECTIVENESS_COLON);
			if (temppool[p]->infiltration > 0.8f)
				set_color_easy(RED_ON_BLACK_BRIGHT);
			else if (temppool[p]->infiltration > 0.6f)
				set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
			else if (temppool[p]->infiltration > 0.4f)
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			else if (temppool[p]->infiltration > 0.2f)
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
			else if (temppool[p]->infiltration > 0.1f)
				set_color_easy(WHITE_ON_BLACK);
			else set_color_easy(GREEN_ON_BLACK);
			addstrAlt(static_cast<long>(temppool[p]->infiltration * 100 + 0.5)); // gets rounded to nearest integer
			addstrAlt(percentSign);
			set_color_easy(WHITE_ON_BLACK);
			mvaddstrAlt(y, 42, LocationsPool::getInstance().getLocationNameWithGetnameMethod(temppool[p]->worklocation, true, true));
			// Let's add some color here...
			set_activity_color(temppool[p]->activity_type());
			mvaddstrAlt(y, 57, temppool[p]->getActivityString());
		}
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(22, 0, PRESS_A_LETTER_TO_ASSIGN);
		mvaddstrAlt(23, 0, addpagestr() + T_TO_SORT_PEOPLE);
		set_color_easy(WHITE_ON_BLACK);
		int c = getkeyAlt();
		//PAGE UP
		if (is_page_up(c) && page > 0) page--;
		//PAGE DOWN
		if (is_page_down(c) && (page + 1) * 9 < len(temppool)) page++;
		if (c >= 'a'&&c <= 's')
		{
			int p = page * 9 + (int)(c - 'a');
			if (p < len(temppool))
				activate_sleeper(temppool[p]);
		}
		if (c == 't')
		{
			sorting_prompt(SORTINGCHOICE_ACTIVATESLEEPERS);
			sortliberals(temppool, activesortingchoice[SORTINGCHOICE_ACTIVATESLEEPERS], true);
		}
		if (c == 'x' || c == ENTER || c == ESC || c == SPACEBAR) break;
	}
}