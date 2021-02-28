



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
#include "../includes43.h"
#include "../constStringdate.h"
#include <algorithm>
 vector<Deprecateddatest *> date;
 // Handles the result of a date or vacation
 static int dateresult(int aroll, int troll, Deprecateddatest &d, int e, int p, int y)
 {
	 music.play(MUSIC_DATING);
	 std::string s = "";
	 if (aroll > troll)
	 {
		 set_color_easy(CYAN_ON_BLACK_BRIGHT);
		 moveAlt(y, 0); y++;
		 addstrAlt(d.date[e]->getNameAndAlignment().name, gamelog);
		 addstrAlt(IS_QUITE_TAKEN_WITH, gamelog);
		 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
		 addstrAlt(S_UNIQUE_PHILOSOPHY, gamelog);
		 gamelog.newline();
		 pressAnyKey();
		 if (loveslavesleft(*pool[p]) <= 0)
		 {
			 set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			 mvaddstrAlt(y++, 0, BUT_SPACE, gamelog);
			 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
			 addstrAlt(IS_ALREADY_DATING, gamelog);
			 int num_relationships = loveslaves(*pool[p]);
			 if (pool[p]->flag&CREATUREFLAG_LOVESLAVE) num_relationships++;
			 if (num_relationships == 1) addstrAlt(SOMEONE, gamelog);
			 else addstrAlt(tostring(num_relationships) + CONST_X_PEOPLE, gamelog);
			 gamelog.newline();
			 mvaddstrAlt(y++, 0, pool[p]->getNameAndAlignment().name, gamelog);
			 addstrAlt(ISNT_SEDUCTIVE_ENOUGH, gamelog);
			 if (num_relationships == 1) addstrAlt(ANOTHER, gamelog);
			 else addstrAlt(YET_ANOTHER, gamelog);
			 addstrAlt(RELATIONSHIP, gamelog);
			 gamelog.newline();
			 pressAnyKey();
			 set_color_easy(WHITE_ON_BLACK);
			 mvaddstrAlt(y++, 0, IT_WAS_FUN_PART_AMICABLY, gamelog);
			 gamelog.nextMessage();
			 pressAnyKey();
			 delete_and_remove(d.date, e);
			 return DATERESULT_BREAKUP;
		 }
		 if (LCSrandom((aroll - troll) / 2) > d.date[e]->get_attribute(ATTRIBUTE_WISDOM, true))
		 {
			 set_color_easy(GREEN_ON_BLACK_BRIGHT);
			 moveAlt(y, 0); y++;
			 addstrAlt(IN_FACT, gamelog);
			 addstrAlt(d.date[e]->getNameAndAlignment().name, gamelog);
			 addstrAlt(IS_SPACE, gamelog);
			 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
			 addstrAlt(S_TOTALLY_LOVE_SLAVE, gamelog);
			 gamelog.nextMessage();
			 //Get map of their workplace
			 LocationsPool::getInstance().setLocationMappedAndUnhidden(d.date[e]->worklocation);
			 pressAnyKey();
			 d.date[e]->flag |= CREATUREFLAG_LOVESLAVE;
			 d.date[e]->hireid = pool[p]->id;
			 eraseAlt();
			 set_color_easy(WHITE_ON_BLACK_BRIGHT);
			 mvaddstrAlt(0, 0, SELF_NULLIFYING_INFATUATION_OF);
			 addstrAlt(d.date[e]->propername);
			 set_color_easy(WHITE_ON_BLACK);
			 mvaddstrAlt(2, 0, CONST_WHAT_NAME_WILL_YOU_USE_FOR_THIS);
			 addstrAlt(d.date[e]->get_type_name());
			 addstrAlt(CONST_IN_ITS_PRESENCE);
			 mvaddstrAlt(3, 0, CONST_IF_YOU_DO_NOT_ENTER_ANYTHING_THEIR_REAL_NAME_WILL_BE_USED);
			 d.date[e]->new_name_four();
			 sleeperize_prompt(*d.date[e], *pool[p], 8);
			 addCreature(d.date[e]);
			 stat_recruits++;
			 d.date.erase(d.date.begin() + e);
			 return DATERESULT_JOINED;
		 }
		 else
		 {
			 if (d.date[e]->align == ALIGN_CONSERVATIVE && d.date[e]->get_attribute(ATTRIBUTE_WISDOM, false) > 3)
			 {
				 set_color_easy(GREEN_ON_BLACK_BRIGHT);
				 y++;
				 mvaddstrAlt(y++, 0, s + pool[p]->getNameAndAlignment().name + IS_SLOWLY_WARMING + d.date[e]->getNameAndAlignment().name + CONST_S_FROZEN_CONSERVATIVE_HEART, gamelog);
				 gamelog.newline();
				 moveAlt(y++, 0);
				 d.date[e]->adjust_attribute(ATTRIBUTE_WISDOM, -1);
				 d.date[e]->adjust_attribute(ATTRIBUTE_HEART, +1);
			 }
			 else if (d.date[e]->get_attribute(ATTRIBUTE_WISDOM, false) > 3)
			 {
				 d.date[e]->adjust_attribute(ATTRIBUTE_WISDOM, -1);
			 }
			 //Possibly date reveals map of location
			 else if (LocationsPool::getInstance().isLocationMapped(d.date[e]->worklocation) == 0 && !LCSrandom(d.date[e]->get_attribute(ATTRIBUTE_WISDOM, false)))
			 {
				 y++;
				 mvaddstrAlt(y++, 0, s + d.date[e]->getNameAndAlignment().name + TURNS_THE_TOPIC_OF_DISCUSSION
					 + LocationsPool::getInstance().getLocationName(d.date[e]->worklocation) + singleDot, gamelog);
				 gamelog.newline();
				 moveAlt(y++, 0);
				 if (!(LocationsPool::getInstance().getLocationType(d.date[e]->worklocation) <= SITE_RESIDENTIAL_SHELTER))
				 {
					 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
					 addstrAlt(WAS_ABLE_TO_CREATE_MAP, gamelog);
					 gamelog.newline();
					 y++;
				 }
				 else
				 {
					 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
					 addstrAlt(KNOWS_THIS_ALREADY, gamelog);
					 gamelog.newline();
					 y++;
				 }
				 LocationsPool::getInstance().setLocationMappedAndUnhidden(d.date[e]->worklocation);
			 }
			 set_color_easy(WHITE_ON_BLACK);
			 mvaddstrAlt(y++, 0, THEYLL_MEET_AGAIN_TOMORROW, gamelog);
			 gamelog.nextMessage();
			 pressAnyKey();
			 return DATERESULT_MEETTOMORROW;
		 }
	 }
	 else if (aroll == troll)
	 {
		 set_color_easy(WHITE_ON_BLACK);
		 mvaddstrAlt(y++, 0, d.date[e]->getNameAndAlignment().name, gamelog);
		 addstrAlt(SEEMED_TO_HAVE_FUN_BUT_LEFT_EARLY, gamelog);
		 moveAlt(y++, 0);
		 switch (LCSrandom(7))
		 {
		 case 0: addstrAlt(s + TO_WASH + d.date[e]->hisher() + CONST_HAIR, gamelog); break;
		 case 1: addstrAlt(DUE_TO_ALLERGY, gamelog); break;
		 case 2: addstrAlt(DUE_TO_EARLY_MEETING, gamelog); break;
		 case 3: addstrAlt(s + TO_CATCH + d.date[e]->hisher() + CONST_FAVOURITE_TV_SHOW, gamelog); break;
		 case 4:
			 addstrAlt(s + TO_TAKE_CARE_OF + d.date[e]->hisher() + CONST_PET, gamelog);
			 switch (LCSrandom(3 + (lawList[LAW_ANIMALRESEARCH] == -2)))
			 {
			 case 0: addstrAlt(CONST_X_CAT, gamelog); break;
			 case 1: addstrAlt(CONST_X_DOG, gamelog); break;
			 case 2: addstrAlt(CONST_X_FISH, gamelog); break;
			 case 3: addstrAlt(SIX_LEGGED_PIG, gamelog); break;
			 }
			 break;
		 case 5: addstrAlt(TO_GO_TO_BIRTHDAY, gamelog); break;
		 case 6: addstrAlt(s + TO_RECHARGE + d.date[e]->hisher() + CONST_CELL_PHONE, gamelog); break;
		 }
		 mvaddstrAlt(y++, 0, THEYLL_MEET_AGAIN_TOMORROW, gamelog);
		 gamelog.nextMessage();
		 pressAnyKey();
		 return DATERESULT_MEETTOMORROW;
	 }
	 else
	 {
		 //WISDOM POSSIBLE INCREASE
		 if (d.date[e]->align == -1 && aroll < troll / 2)
		 {
			 set_color_easy(RED_ON_BLACK_BRIGHT);
			 mvaddstrAlt(y++, 0, TALKING_WITH, gamelog);
			 addstrAlt(d.date[e]->getNameAndAlignment().name, gamelog);
			 addstrAlt(ACTUALLY_CURSES, gamelog);
			 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
			 addstrAlt(S_MIND_WITH_WISDOM, gamelog);
			 gamelog.newline();
			 pool[p]->adjust_attribute(ATTRIBUTE_WISDOM, +1);
			 if (d.date[e]->get_skill(SKILL_RELIGION) > pool[p]->get_skill(SKILL_RELIGION))
				 pool[p]->train(SKILL_RELIGION, 20 * (d.date[e]->get_skill(SKILL_RELIGION) - pool[p]->get_skill(SKILL_RELIGION)));
			 if (d.date[e]->get_skill(SKILL_SCIENCE) > pool[p]->get_skill(SKILL_SCIENCE))
				 pool[p]->train(SKILL_SCIENCE, 20 * (d.date[e]->get_skill(SKILL_SCIENCE) - pool[p]->get_skill(SKILL_SCIENCE)));
			 if (d.date[e]->get_skill(SKILL_BUSINESS) > pool[p]->get_skill(SKILL_BUSINESS))
				 pool[p]->train(SKILL_BUSINESS, 20 * (d.date[e]->get_skill(SKILL_BUSINESS) - pool[p]->get_skill(SKILL_BUSINESS)));
			 pressAnyKey();
		 }
		 //BREAK UP
		 // If your squad member is wanted by the police, a conservative who breaks up with
		 // them has a 1 in 50 chance of ratting them out, unless the person being dated is law
		 // enforcement, prison guard, or agent, in which case there is a 1 in 4 chance. -Fox
		 if ((iscriminal(pool[p]->getCreatureJustice())) &&
			 (!LCSrandom(50) || (LCSrandom(2) && (d.date[e]->kidnap_resistant()))))
		 {
			 set_color_easy(RED_ON_BLACK_BRIGHT);
			 mvaddstrAlt(y++, 0, d.date[e]->getNameAndAlignment().name, gamelog);
			 addstrAlt(WAS_LEAKING_INFORMATION_TO_POLICE, gamelog);
			 pressAnyKey();
			 moveAlt(y++, 0);
			 // 3/4 chance of being arrested if less than 50 juice,
			 // 1/2 chance of being arrested if more than 50 juice
			 if ((pool[p]->juice < 50 && LCSrandom(2)) || LCSrandom(2))
			 {
				 // Find the police station
				 long ps = find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION, pool[p]->location);
				 set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
				 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
				 addstrAlt(HAS_BEEN_ARRESTED, gamelog);
				 gamelog.nextMessage();
				 removesquadinfo(*pool[p]);
				 pool[p]->carid = -1;
				 pool[p]->location = ps;
				 pool[p]->drop_weapons_and_clips(NULL);
				 pool[p]->set_activity_type(ACTIVITY_NONE);
				 pressAnyKey();
				 delete_and_remove(d.date, e);
				 return DATERESULT_ARRESTED;
			 }
			 else
			 {
				 set_color_easy(GREEN_ON_BLACK_BRIGHT);
				 addstrAlt(BUT_SPACE, gamelog);
				 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
				 addstrAlt(ESCAPES_THE_POLICE_AMBUSH, gamelog);
				 gamelog.nextMessage();
			 }
		 }
		 else
		 {
			 int ls = loveslaves(*pool[p]);
			 if (ls > 0 && LCSrandom(2))
			 {
				 set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
				 mvaddstrAlt(y++, 0, s + THE_DATE_STARTS_WELL_UNTIL + d.date[e]->getNameAndAlignment().name, gamelog);
				 mvaddstrAlt(y++, 0, s + NOTICES + pool[p]->getNameAndAlignment().name + CONST_S, gamelog);
				 switch (ls)
				 {
				 case 5:
					 addstrAlt(AWE_INSPIRING, gamelog);
					 break;
				 case 4:
					 addstrAlt(INTRICATE, gamelog);
					 break;
				 case 3:
					 addstrAlt(COMPLICATED, gamelog);
					 break;
				 case 2:
					 addstrAlt(DETAILED, gamelog);
					 break;
				 case 1:
					 break;
				 default:
					 addstrAlt(MIND_BENDING, gamelog);
				 }
				 addstrAlt(s + SCHEDULE_FOR_KEEPING + d.date[e]->himher(), gamelog);
				 addstrAlt(s + FROM_MEETING_SPACE, gamelog);
				 moveAlt(y++, 0);
				 int lsfound = 0;
				 for (int q = 0; q < (int)pool.size(); q++)
				 {
					 if (pool[q]->hireid == pool[p]->id && pool[q]->getNameAndAlignment().alive && pool[q]->flag & CREATUREFLAG_LOVESLAVE)
					 {
						 lsfound++;
						 if (lsfound == 1)
						 {
							 addstrAlt(pool[q]->getNameAndAlignment().name, gamelog);
						 }
						 else if (lsfound < ls)
						 {
							 addstrAlt(s + COMMA_SPACE + pool[q]->getNameAndAlignment().name, gamelog);
						 }
						 else
						 {
							 addstrAlt(s + AND + pool[q]->getNameAndAlignment().name, gamelog);
						 }
					 }
				 }
				 addstrAlt(singleDot, gamelog);
				 gamelog.newline();
				 moveAlt(y++, 0);
			 }
			 else
			 {
				 set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
				 mvaddstrAlt(y++, 0, d.date[e]->getNameAndAlignment().name, gamelog);
				 addstrAlt(CAN_SENSE_THAT_THINGS_ARENT_WORKING, gamelog);
				 gamelog.newline();
				 moveAlt(y++, 0);
			 }
			 addstrAlt(THE_RELATIONSHIP_IS_OVER, gamelog);
			 gamelog.nextMessage();
		 }
		 pressAnyKey();
		 delete_and_remove(d.date, e);
		 return DATERESULT_BREAKUP;
	 }
 }
 /* daily - date - dater p gets back from vacation */
 char completevacation(Deprecateddatest &d, int p)
 {
	 music.play(MUSIC_DATING);
	 int e = 0;
	 eraseAlt();
	 set_color_easy(WHITE_ON_BLACK_BRIGHT);
	 mvaddstrAlt(0, 0, pool[p]->getNameAndAlignment().name, gamelog);
	 addstrAlt(IS_BACK_FROM_VACATION, gamelog);
	 gamelog.nextMessage();
	 // Temporarily make the date Conservative so that high-juice liberals aren't trivial to seduce
	 int datealignment = d.date[e]->align;
	 d.date[e]->align = -1;
	 short aroll = pool[p]->skill_roll(SKILL_SEDUCTION) * 2;
	 short troll = d.date[e]->attribute_roll(ATTRIBUTE_WISDOM);
	 // Attribute roll over; reset date's alignment to what it should be
	 d.date[e]->align = datealignment;
	 pool[p]->train(SKILL_SEDUCTION, LCSrandom(11) + 15);
	 int thingsincommon = 0;
	 for (int s = 0; s < SKILLNUM; s++)
		 if (d.date[e]->get_skill(s) >= 1 && pool[p]->get_skill(s) >= 1)
			 //Has a skill that is at least half the same skill of the other person on the date.
			 if (d.date[e]->get_skill(s) <= pool[p]->get_skill(s) * 2)
				 thingsincommon++;
	 aroll += thingsincommon * 3;
	 pool[p]->train(SKILL_SCIENCE,
		 max(d.date[e]->get_skill(SKILL_SCIENCE) - pool[p]->get_skill(SKILL_SCIENCE), 0));
	 pool[p]->train(SKILL_RELIGION,
		 max(d.date[e]->get_skill(SKILL_RELIGION) - pool[p]->get_skill(SKILL_RELIGION), 0));
	 pool[p]->train(SKILL_BUSINESS,
		 max(d.date[e]->get_skill(SKILL_BUSINESS) - pool[p]->get_skill(SKILL_BUSINESS), 0));
	 if (d.date[e]->skill_roll(SKILL_BUSINESS))
	 {
		 troll += d.date[e]->skill_roll(SKILL_BUSINESS);
		 aroll += pool[p]->skill_roll(SKILL_BUSINESS);
	 }
	 if (d.date[e]->skill_roll(SKILL_RELIGION))
	 {
		 troll += d.date[e]->skill_roll(SKILL_RELIGION);
		 aroll += pool[p]->skill_roll(SKILL_RELIGION);
	 }
	 if (d.date[e]->skill_roll(SKILL_SCIENCE))
	 {
		 troll += d.date[e]->skill_roll(SKILL_SCIENCE);
		 aroll += pool[p]->skill_roll(SKILL_SCIENCE);
	 }
	 switch (dateresult(aroll, troll, d, e, p, 2))
	 {
	 default:
	 case DATERESULT_MEETTOMORROW:return 0;
	 case DATERESULT_BREAKUP:     return 1;
	 case DATERESULT_JOINED:      return 1;
	 case DATERESULT_ARRESTED:    return 1;
	 }
 }
 /* daily - date - dater p goes on some dates */
 char completedate(Deprecateddatest &d, int p)
 {
	 music.play(MUSIC_DATING);
	 eraseAlt();
	 set_color_easy(WHITE_ON_BLACK_BRIGHT);
	 mvaddstrAlt(0, 0, pool[p]->getNameAndAlignment().name, gamelog);
	 addstrAlt(CONST_S_HAS_S, gamelog);
	 if (len(d.date) == 1)
	 {
		 if (pool[p]->clinic) addstrAlt(A_H_O_T_DATE, gamelog);
		 else addstrAlt(A_HOT_DATE, gamelog);
	 }
	 else addstrAlt(DATES_TO_MANAGE, gamelog);
	 for (int e = 0; e < len(d.date); e++)
	 {
		 addstrAlt(d.date[e]->getNameAndAlignment().name, gamelog);
		 if (e <= len(d.date) - 3) addstrAlt(COMMA_SPACE, gamelog);
		 else if (e == len(d.date) - 2) addstrAlt(AND, gamelog);
		 else
		 {
			 if (pool[p]->clinic > 0)
			 {
				 addstrAlt(AT_SPACE, gamelog);
				 addstrAlt(LocationsPool::getInstance().getLocationName(pool[p]->location), gamelog);
			 }
			 addstrAlt(singleDot, gamelog);
		 }
	 }
	 gamelog.newline();
	 pressAnyKey();
	 if (len(d.date) > 1 && !LCSrandom(len(d.date) > 2 ? 4 : 6))
	 {
		 switch (LCSrandom(3))
		 {
		 case 0:
			 moveAlt(2, 0);
			 if (len(d.date) > 2) addstrAlt(UNFORTUNATELY_THEY_ALL_KNOW_EACHOTHER, gamelog);
			 else addstrAlt(UNFORTUNATELY_THEY_KNOW_EACHOTHER, gamelog);
			 mvaddstrAlt(3, 0, pool[p]->getNameAndAlignment().name, gamelog);
			 addstrAlt(AN_AMBUSH_FOR_THE_DOG, gamelog);
			 gamelog.newline();
			 pressAnyKey();
			 break;
		 case 1:
			 moveAlt(2, 0);
			 if (len(d.date) > 2) addstrAlt(UNFORTUNATELY_THEY_ALL_TURN_UP_AT_ONCE, gamelog);
			 else addstrAlt(UNFORTUNATELY_THEY_TURN_UP_AT_ONCE, gamelog);
			 gamelog.newline();
			 mvaddstrAlt(3, 0, RUH_ROH, gamelog);
			 gamelog.newline();
			 pressAnyKey();
			 break;
		 default:
			 mvaddstrAlt(2, 0, pool[p]->getNameAndAlignment().name, gamelog);
			 if (len(d.date) > 2)
				 addstrAlt(REALIZES + pool[p]->heshe() + HAS_COMMITTED + tostring(len(d.date)) + MEALS_AT_ONCE, gamelog);
			 else
			 {
				 addstrAlt(CONST_MIXES_UP_THE_NAMES_OF, gamelog);
				 addstrAlt(d.date[0]->getNameAndAlignment().name, gamelog);
				 addstrAlt(AND, gamelog);
				 addstrAlt(d.date[1]->getNameAndAlignment().name, gamelog);
				 gamelog.newline();
			 }
			 mvaddstrAlt(3, 0, CONST_THINGS_GO_DOWNHILL_FAST, gamelog);
			 gamelog.newline();
			 pressAnyKey();
			 break;
		 }
		 mvaddstrAlt(5, 0, pool[p]->getNameAndAlignment().name, gamelog);
		 addstrAlt(singleSpace, gamelog);
		 addstrAlt(pickrandom(date_fail), gamelog);
		 addjuice(*pool[p], -5, -50);
		 gamelog.nextMessage();
		 pressAnyKey();
		 return 1;
	 }
	 for (int e = len(d.date) - 1; e >= 0; e--)
	 {
		 eraseAlt();
		 set_color_easy(WHITE_ON_BLACK_BRIGHT);
		 mvaddstrAlt(0, 0, CONST_SEEING);
		 addstrAlt(d.date[e]->getNameAndAlignment().name, gamelog);
		 addstrAlt(COMMA_SPACE, gamelog);
		 addstrAlt(d.date[e]->get_type_name(), gamelog);
		 addstrAlt(COMMA_SPACE, gamelog);
		 addstrAlt(LocationsPool::getInstance().getLocationNameWithGetnameMethod(d.date[e]->worklocation, false, true), gamelog);
		 gamelog.newline();
		 set_color_easy(WHITE_ON_BLACK);
		 printfunds();
		 //Others come to dates unarmed and wearing normal
		 //clothing
		 vector<Item*> temp;
		 d.date[e]->drop_weapons_and_clips(&temp);
		 Armor atmp(getarmortype(tag_ARMOR_CLOTHES));
		 d.date[e]->give_armor(atmp, &temp);
		 printcreatureinfo(d.date[e]);
		 makedelimiter();
		 while (len(temp))
		 {
			 if (temp.back()->whatIsThis() == THIS_IS_WEAPON)
				 d.date[e]->give_weapon(*(static_cast<Weapon*>(temp.back())), NULL); //casts -XML
			 else if (temp.back()->whatIsThis() == THIS_IS_ARMOR)
				 d.date[e]->give_armor(*(static_cast<Armor*>(temp.back())), NULL);
			 else if (temp.back()->whatIsThis() == THIS_IS_CLIP)
				 d.date[e]->take_clips(*(static_cast<Clip*>(temp.back())), temp.back()->get_number());
			 delete_and_remove(temp, len(temp) - 1);
		 }
		 mvaddstrAlt(10, 0, CONST_HOW_SHOULD);
		 addstrAlt(pool[p]->getNameAndAlignment().name);
		 addstrAlt(CONST_APPROACH_THE_SITUATION);
		 if (ledger.get_funds() >= 100 && !pool[p]->clinic)set_color_easy(WHITE_ON_BLACK);
		 else set_color_easy(BLACK_ON_BLACK_BRIGHT);
		 mvaddstrAlt(11, 0, CONST_A_SPEND_A_HUNDRED_BUCKS_TONIGHT_TO_GET_THE_BALL_ROLLING);
		 set_color_easy(WHITE_ON_BLACK);
		 mvaddstrAlt(12, 0, CONST_B_TRY_TO_GET_THROUGH_THE_EVENING_WITHOUT_SPENDING_A_PENNY);
		 if (!pool[p]->clinic&&pool[p]->blood == 100)set_color_easy(WHITE_ON_BLACK);
		 else set_color_easy(BLACK_ON_BLACK_BRIGHT);
		 moveAlt(13, 0);
		 if (pool[p]->blood == 100) addstrAlt(CONST_C_SPEND_A_WEEK_ON_A_CHEAP_VACATION_STANDS_UP_ANY_OTHER_DATES);
		 else addstrAlt(CONST_C_SPEND_A_WEEK_ON_A_CHEAP_VACATION_MUST_BE_UNINJURED);
		 set_color_easy(WHITE_ON_BLACK);
		 mvaddstrAlt(14, 0, CONST_D_BREAK_IT_OFF);
		 if (d.date[e]->align == -1 && !pool[p]->clinic)
		 {
			 set_color_easy(WHITE_ON_BLACK);
			 mvaddstrAlt(15, 0, CONST_E_JUST_KIDNAP_THE_CONSERVATIVE_BITCH);
		 }
		 int thingsincommon = 0;
		 for (int s = 0; s < SKILLNUM; s++)
			 if (d.date[e]->get_skill(s) >= 1 && pool[p]->get_skill(s) >= 1)
				 //Has a skill that is at least half the same skill of the other person on the date.
				 if (d.date[e]->get_skill(s) <= pool[p]->get_skill(s) * 2)
					 thingsincommon++;
		 while (true)
		 {
			 int c = getkeyAlt();
			 short aroll = pool[p]->skill_roll(SKILL_SEDUCTION);
			 short troll = d.date[e]->attribute_roll(ATTRIBUTE_WISDOM);
			 if (d.date[e]->align == ALIGN_CONSERVATIVE)
				 troll += troll * (d.date[e]->juice / 100);
			 // Even liberals and moderates shouldn't be TOO easy to seduce! -- SlatersQuest
			 else if (d.date[e]->align == ALIGN_MODERATE)
				 troll += troll * (d.date[e]->juice / 150);
			 else troll += troll * (d.date[e]->juice / 200);
			 char test = 0;
			 aroll += thingsincommon * 3;
			 if (c == 'a'&&ledger.get_funds() >= 100 && !pool[p]->clinic)
			 {
				 ledger.subtract_funds(100, EXPENSE_DATING);
				 aroll += LCSrandom(10);
				 test = true;
			 }
			 else if (c == 'b') test = true;
			 if (test)
			 {
				 pool[p]->train(SKILL_SEDUCTION, LCSrandom(4) + 5);
				 pool[p]->train(SKILL_SCIENCE,
					 max(d.date[e]->get_skill(SKILL_SCIENCE) - pool[p]->get_skill(SKILL_SCIENCE), 0));
				 pool[p]->train(SKILL_RELIGION,
					 max(d.date[e]->get_skill(SKILL_RELIGION) - pool[p]->get_skill(SKILL_RELIGION), 0));
				 pool[p]->train(SKILL_BUSINESS,
					 max(d.date[e]->get_skill(SKILL_BUSINESS) - pool[p]->get_skill(SKILL_BUSINESS), 0));
				 if (d.date[e]->get_skill(SKILL_BUSINESS))
				 {
					 troll += d.date[e]->skill_roll(SKILL_BUSINESS);
					 aroll += pool[p]->skill_roll(SKILL_BUSINESS);
				 }
				 if (d.date[e]->get_skill(SKILL_RELIGION))
				 {
					 troll += d.date[e]->skill_roll(SKILL_RELIGION);
					 aroll += pool[p]->skill_roll(SKILL_RELIGION);
				 }
				 if (d.date[e]->get_skill(SKILL_SCIENCE))
				 {
					 troll += d.date[e]->skill_roll(SKILL_SCIENCE);
					 aroll += pool[p]->skill_roll(SKILL_SCIENCE);
				 }
				 int y = 17;
				 if (dateresult(aroll, troll, d, e, p, y) == DATERESULT_ARRESTED) return 1;
				 break;
			 }
			 if (c == 'c' && !pool[p]->clinic&&pool[p]->blood == 100)
			 {
				 for (int e2 = len(d.date) - 1; e2 >= 0; e2--)
				 {
					 if (e2 == e) continue;
					 delete_and_remove(d.date, e2);
					 e = 0;
				 }
				 d.timeleft = 7;
				 pool[p]->train(SKILL_SEDUCTION, LCSrandom(40) + 15);
				 pool[p]->train(SKILL_SCIENCE,
					 max((d.date[e]->get_skill(SKILL_SCIENCE) - pool[p]->get_skill(SKILL_SCIENCE)) * 4, 0));
				 pool[p]->train(SKILL_RELIGION,
					 max((d.date[e]->get_skill(SKILL_RELIGION) - pool[p]->get_skill(SKILL_RELIGION)) * 4, 0));
				 pool[p]->train(SKILL_BUSINESS,
					 max((d.date[e]->get_skill(SKILL_BUSINESS) - pool[p]->get_skill(SKILL_BUSINESS)) * 4, 0));
				 return 0;
			 }
			 if (c == 'd')
			 {
				 delete_and_remove(d.date, e);
				 break;
			 }
			 if (c == 'e'&&d.date[e]->align == -1 && !pool[p]->clinic)
			 {
				 set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				 int bonus = 0;
				 mvaddstrAlt(17, 0, pool[p]->getNameAndAlignment().name, gamelog);
				 if (pool[p]->get_weapon().is_ranged())
				 {
					 addstrAlt(CONST_COMES_BACK_FROM_THE_BATHROOM_TOTING_THE, gamelog);
					 addstrAlt(pool[p]->get_weapon().get_name(1), gamelog);
					 mvaddstrAlt(18, 0, CONST_AND_THREATENS_TO_BLOW_THE_CONSERVATIVE_S_BRAINS_OUT, gamelog);
					 gamelog.newline();
					 bonus = 5;
				 }
				 else if (pool[p]->is_armed())
				 {
					 addstrAlt(CONST_GRABS_THE_CONSERVATIVE_FROM_BEHIND_HOLDING_THE, gamelog);
					 addstrAlt(pool[p]->get_weapon().get_name(1), gamelog);
					 mvaddstrAlt(18, 0, CONST_TO_THE_CORPORATE_SLAVE_S_THROAT, gamelog);
					 gamelog.newline();
					 if (pool[p]->get_weapon().get_specific_bool(BOOL_CAN_TAKE_HOSTAGES_))
						 bonus = 5;
					 else bonus = -1; // Conservative emboldened by the fact that you're trying
				 }                 // to kidnap them with a gavel or some shit like that
				 else
				 {
					 addstrAlt(CONST_SEIZES_THE_CONSERVATIVE_SWINE_FROM_BEHIND_AND_WARNS_IT, gamelog);
					 moveAlt(18, 0);
					 if (lawList[LAW_FREESPEECH] != -2)
						 addstrAlt(CONST_NOT_TO_FUCK_AROUND, gamelog);
					 else
						 addstrAlt(CONST_NOT_TO_RESIST, gamelog);
					 gamelog.newline();
					 bonus += pool[p]->get_skill(SKILL_HANDTOHAND) - 1;
				 }
				 pressAnyKey();
				 // Kidnap probably succeeds if the conservative isn't very dangerous,
				 // but fails 15 times as often if the conservative is tough stuff.
				 if ((!d.date[e]->kidnap_resistant() &&
					 LCSrandom(15)) ||
					 LCSrandom(2 + bonus))
				 {
					 set_color_easy(GREEN_ON_BLACK_BRIGHT);
					 mvaddstrAlt(20, 0, d.date[e]->getNameAndAlignment().name, gamelog);
					 if (bonus)
					 {
						 addstrAlt(CONST_DOESN_T_RESIST, gamelog);
						 gamelog.newline();
					 }
					 else
					 {
						 addstrAlt(CONST_STRUGGLES_AND_YELLS_FOR_HELP_BUT_NOBODY_COMES, gamelog);
						 gamelog.newline();
					 }
					 pressAnyKey();
					 mvaddstrAlt(22, 0, pool[p]->getNameAndAlignment().name, gamelog);
					 addstrAlt(CONST_KIDNAPS_THE_CONSERVATIVE, gamelog);
					 gamelog.nextMessage();
					 pressAnyKey();
					 d.date[e]->namecreature();
					 strcpy(d.date[e]->propername, d.date[e]->getNameAndAlignment().name.data());
					 d.date[e]->location = pool[p]->location;
					 d.date[e]->base = pool[p]->base;
					 d.date[e]->flag |= CREATUREFLAG_MISSING;
					 //Kidnapped wearing normal clothes and no weapon
					 d.date[e]->drop_weapons_and_clips(NULL);
					 Armor clothes(getarmortype(tag_ARMOR_CLOTHES));
					 d.date[e]->give_armor(clothes, NULL);
					 //Create InterrogationST data
					 d.date[e]->activity.intr() = new InterrogationST;
					 eraseAlt();
					 set_color_easy(WHITE_ON_BLACK_BRIGHT);
					 mvaddstrAlt(0, 0, CONST_THE_EDUCATION_OF);
					 addstrAlt(d.date[e]->propername);
					 set_color_easy(WHITE_ON_BLACK);
					 mvaddstrAlt(2, 0, CONST_WHAT_NAME_WILL_YOU_USE_FOR_THIS);
					 addstrAlt(d.date[e]->get_type_name());
					 addstrAlt(CONST_IN_ITS_PRESENCE);
					 mvaddstrAlt(3, 0, CONST_IF_YOU_DO_NOT_ENTER_ANYTHING_THEIR_REAL_NAME_WILL_BE_USED);
					 d.date[e]->new_name_four();
					 addCreature(d.date[e]);
					 stat_kidnappings++;
					 d.date.erase(d.date.begin() + e);
					 break;
				 }
				 else
				 {
					 int y = 20;
					 if (LCSrandom(2))
					 {
						 set_color_easy(MAGENTA_ON_BLACK_BRIGHT);
						 mvaddstrAlt(y++, 0, d.date[e]->getNameAndAlignment().name, gamelog);
						 addstrAlt(CONST_MANAGES_TO_GET_AWAY_ON_THE_WAY_BACK_TO_THE_SAFEHOUSE, gamelog);
						 gamelog.newline();
						 pressAnyKey();
						 mvaddstrAlt((++y)++, 0, pool[p]->getNameAndAlignment().name, gamelog);
						 addstrAlt(CONST_HAS_FAILED_TO_KIDNAP_THE_CONSERVATIVE, gamelog);
						 gamelog.nextMessage();
						 // Charge with kidnapping
						 criminalize(*pool[p], LAWFLAG_KIDNAPPING);
						 pressAnyKey();
						 delete_and_remove(d.date, e);
						 break;
					 }
					 else
					 {
						 set_color_easy(RED_ON_BLACK_BRIGHT);
						 mvaddstrAlt(y++, 0, d.date[e]->getNameAndAlignment().name, gamelog);
						 addstrAlt(CONST_S_FIST_IS_THE_LAST_THING, gamelog);
						 addstrAlt(pool[p]->getNameAndAlignment().name, gamelog);
						 addstrAlt(CONST_REMEMBERS_SEEING, gamelog);
						 gamelog.newline();
						 pressAnyKey();
						 mvaddstrAlt((++y)++, 0, CONST_THE_LIBERAL_WAKES_UP_IN_THE_POLICE_STATION, gamelog);
						 gamelog.nextMessage();
						 // Find the police station
						 int ps = find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION, pool[p]->location);
						 // Arrest the Liberal
						 removesquadinfo(*pool[p]);
						 pool[p]->carid = -1;
						 pool[p]->location = ps;
						 pool[p]->drop_weapons_and_clips(NULL);
						 pool[p]->set_activity_type(ACTIVITY_NONE);
						 // Charge with kidnapping
						 criminalize(*pool[p], LAWFLAG_KIDNAPPING);
						 pressAnyKey();
						 delete_and_remove(d.date, e);
						 return 1;
					 }
				 }
			 }
		 }
	 }
	 if (len(d.date))
	 {
		 d.timeleft = 0;
		 return 0;
	 }
	 else return 1;
 }


 // Determines the number of dates a creature has scheduled
 int scheduleddates(const DeprecatedCreature& cr)
 {
	 int dates = 0;
	 for (int p = len(date) - 1; p >= 0; p--)
		 // Does this creature have a list of dates scheduled?
		 if (date[p]->mac_id == cr.id)
		 {
			 dates = len(date[p]->date); break;
		 }
	 return dates;
 }
 void doDates(char &clearformess) {
	 for (int d = len(date) - 1; d >= 0; d--)
	 {
		 int p = getpoolcreature(date[d]->mac_id);
		 // Stand up dates if 1) dater does not exist, or 2) dater was not able to return to a safehouse today (and is not in the hospital)
		 if (p != -1 && ((pool[p]->location != -1 &&
			 (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE,pool[p]->location) != RENTING_NOCONTROL ||
				 LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_HOSPITAL_CLINIC ||
				 LocationsPool::getInstance().getLocationType(pool[p]->location) == SITE_HOSPITAL_UNIVERSITY) &&
			 LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY,pool[p]->location) == date[d]->city) ||
			 date[d]->timeleft))
		 {
			 //VACATION
			 if (date[d]->timeleft > 0)
			 {
				 pool[p]->dating = --date[d]->timeleft;
				 if (date[d]->timeleft == 0)
				 {
					 int hs = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, date[d]->city); //int hs = find_homeless_shelter(date[d]->city);
					 if (LocationsPool::getInstance().isThereASiegeHere(pool[p]->base))
						 pool[p]->base = hs;
					 pool[p]->location = pool[p]->base;
					 clearformess = 1;
					 if (completevacation(*date[d], p))
					 {
						 delete_and_remove(date, d);
						 continue;
					 }
				 }
			 }
			 //DO A DATE
			 else
			 {
				 //TERMINATE NULL DATES
				 if (LocationsPool::getInstance().isThereASiegeHere(pool[p]->location))
				 {
					 delete_and_remove(date, d);
					 continue;
				 }
				 //DO DATE
				 else {
					 clearformess = 1;
					 if (completedate(*date[d], p))
					 {
						 delete_and_remove(date, d);
						 continue;
					 }
					 else
					 {
						 pool[p]->dating = date[d]->timeleft;
						 if (pool[p]->dating > 0)
						 {
							 //NOW KICK THE DATER OUT OF THE SQUAD AND LOCATION
							 removesquadinfo(*pool[p]);
							 pool[p]->location = -1;
						 }
					 }
				 }

			 }
		 }
		 else
		 {
			 delete_and_remove(date, d);
			 continue;
		 }
	 }
 }
 void delenc(DeprecatedCreature &tk);
 int getCity(int l);
 void newDate(DeprecatedCreature &a, DeprecatedCreature &tk) {
	 Deprecateddatest *newd = NULL;
	 for (int d = 0; d < len(date); d++)
	 {
		 if (date[d]->mac_id == a.id)
		 {
			 newd = date[d];
			 break;
		 }
	 }
	 if (newd == NULL)
	 {
		 newd = new Deprecateddatest;
		 newd->mac_id = a.id;
		 newd->city = getCity(a.location);
		 date.push_back(newd);
	 }
	 DeprecatedCreature* newcr = new DeprecatedCreature;
	 *newcr = tk;
	 newcr->namecreature();
	 newcr->location = a.location;
	 newcr->base = a.base;
	 newd->date.push_back(newcr);
	 // TODO this is a pointer subtracting another pointer in order to calculate the index, change it
	 delenc(tk);
 }

 void delete_and_clear_date_pool() {
	 delete_and_clear(date);
 }