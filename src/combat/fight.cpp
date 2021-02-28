


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
#include "../includes62.h"
#include "../constStringfight.h"
bool goodguyattack = false;
 /* generates the loot dropped by a creature when it dies */
 void makeloot(DeprecatedCreature &cr)
 {
	 cr.makeloot(groundloot);
 }
 bool isThereGroundLoot() {
	 return len(groundloot) > 0;
 }
 void delete_and_clear_groundloot() {
	 delete_and_clear(groundloot);
 }

 bool incapacitatedTank(DeprecatedCreature &a, const char noncombat, char &printed) {

	 if (a.getCreatureHealth().blood <= 20 || (a.getCreatureHealth().blood <= 50 && (LCSrandom(2) || a.forceinc)))
	 {
		 a.forceinc = 0;
		 if (noncombat)
		 {
			 clearmessagearea();
			 set_color_easy(WHITE_ON_BLACK_BRIGHT);
			 mvaddstrAlt(16, 1, tag_The, gamelog);
			 addstrAlt(a.getNameAndAlignment().name, gamelog);
			 addstrAlt(singleSpace + pickrandom(paralyzed_tank));
			 gamelog.newline();
			 printed = 1;
		 }
		 return 1;
	 }
	 return 0;

 }

 bool incapacitatedAnimal(DeprecatedCreature &a, const char noncombat, char &printed) {

	 if (a.getCreatureHealth().blood <= 20 || (a.getCreatureHealth().blood <= 50 && (LCSrandom(2) || a.forceinc)))
	 {
		 a.forceinc = 0;
		 if (noncombat)
		 {
			 clearmessagearea();
			 set_color_easy(WHITE_ON_BLACK_BRIGHT);
			 mvaddstrAlt(16, 1, tag_The, gamelog);
			 addstrAlt(a.getNameAndAlignment().name);
			 switch (LCSrandom(3))
			 {
			 case 0: if (lawList[LAW_FREESPEECH] == -2) addstrAlt(CONST_MAKES_A_STINKY, gamelog);
					 else addstrAlt(CONST_SOILS_THE_FLOOR, gamelog); break;
			 default:
				 addstrAlt(singleSpace + pickrandom(bleeding_animal), gamelog); break;
			 }
			 gamelog.newline();
			 printed = 1;
		 }
		 return 1;
	 }
	 return 0;

 }
 bool incapacitatedPerson(DeprecatedCreature &a, const char noncombat, char &printed) {
	 if (a.getCreatureHealth().blood <= 20 || (a.getCreatureHealth().blood <= 50 && (LCSrandom(2) || a.forceinc)))
	 {
		 a.forceinc = 0;
		 if (noncombat)
		 {
			 clearmessagearea();
			 set_color_easy(WHITE_ON_BLACK_BRIGHT);
			 mvaddstrAlt(16, 1, a.getNameAndAlignment().name);
			 switch (LCSrandom(54))
			 {
				 //TODO IsaacG Complete Migration of Strings
			 case 0: if (lawList[LAW_FREESPEECH] == -2) addstrAlt(CONST_MAKES_A_STINKY);
					 else addstrAlt(CONST_SOILS_THE_FLOOR); break;
			 case 1: if (mode != GAMEMODE_CHASECAR) addstrAlt(CONST_STUMBLES_AGAINST_A_WALL);
					 else addstrAlt(CONST_LEANS_AGAINST_THE_DOOR); break;
			 case 2: if (a.getCreatureHealth().special[SPECIALWOUND_RIGHTEYE] && a.getCreatureHealth().special[SPECIALWOUND_LEFTEYE])
				 addstrAlt(CONST_STARES_OFF_INTO_SPACE);
					 else if (a.getCreatureHealth().special[SPECIALWOUND_RIGHTEYE] || a.getCreatureHealth().special[SPECIALWOUND_LEFTEYE])
						 addstrAlt(CONST_STARES_INTO_SPACE_WITH_ONE_EMPTY_EYE);
					 else addstrAlt(CONST_STARES_OUT_WITH_HOLLOW_SOCKETS); break;
			 case 3: if (lawList[LAW_FREESPEECH] == -2) addstrAlt(CONST_MAKES_A_MESS_MOANING);
					 else addstrAlt(CONST_PISSES_ON_THE_FLOOR_MOANING); break;
			 case 4: if (a.getCreatureHealth().special[SPECIALWOUND_TEETH] > 1) addstrAlt(CONST_S_TEETH_START_CHATTERING);
					 else if (a.getCreatureHealth().special[SPECIALWOUND_TEETH] == 1) addstrAlt(CONST_S_TOOTH_STARTS_CHATTERING);
					 else addstrAlt(CONST_S_GUMS_START_CHATTERING); break;
			 case 5: if (a.getCreatureBio().age < 20 && !a.getCreatureHealth().animalgloss) addstrAlt(CONST_CRIES_MOMMY);
					 else switch (a.type) {
					 case CREATURE_GENETIC:
						 addstrAlt(CONST_MURMURS_WHAT_ABOUT_MY_OFFSPRING); break;
					 case CREATURE_GUARDDOG:
						 addstrAlt(CONST_MURMURS_WHAT_ABOUT_MY_PUPPIES); break;
					 default:
						 addstrAlt(CONST_MURMURS_WHAT_ABOUT_MY_CHILDREN); break;
					 } break;
			 case 6: if (lawList[LAW_FREESPEECH] == -2)addstrAlt(CONST_MAKES_A_MESS);
					 else addstrAlt(CONST_VOMITS_UP_A_CLOT_OF_BLOOD); break;
			 case 7: if (lawList[LAW_FREESPEECH] == -2)addstrAlt(CONST_MAKES_A_MESS);
					 else addstrAlt(CONST_SPITS_UP_A_CLUSTER_OF_BLOODY_BUBBLES); break;
			 default: addstrAlt(pickrandom(bleeding_to_death));
			 }
			 printed = 1;
		 }
		 return 1;
	 }
	 if (a.is_stunned())
	 {
		 if (noncombat)
		 {
			 a.decrement_stunned();
			 clearmessagearea();
			 set_color_easy(WHITE_ON_BLACK_BRIGHT);
			 mvaddstrAlt(16, 1, a.getNameAndAlignment().name, gamelog);
			 addstrAlt(singleSpace + pickrandom(stunned_text));
			 gamelog.newline();
			 printed = 1;
		 }
		 return 1;
	 }
	 if (a.getCreatureHealth().special[SPECIALWOUND_NECK] == 2 || a.getCreatureHealth().special[SPECIALWOUND_UPPERSPINE] == 2)
	 {
		 if (!noncombat)
		 {
			 clearmessagearea();
			 set_color_easy(WHITE_ON_BLACK_BRIGHT);
			 mvaddstrAlt(16, 1, a.getNameAndAlignment().name, gamelog);
			 addstrAlt(singleSpace + pickrandom(paralyzed_text));
			 gamelog.newline();
			 printed = 1;
		 }
		 return 1;
	 }
	 return 0;
 }
 /* checks if the creature can fight and prints flavor text if they can't */
 char incapacitated(DeprecatedCreature &a, const char noncombat, char &printed)
 {
	 printed = 0;
	 switch (a.getCreatureHealth().animalgloss) {
	 case ANIMALGLOSS_TANK:
		 return incapacitatedTank(a, noncombat, printed);
	 case ANIMALGLOSS_ANIMAL:
		 return incapacitatedAnimal(a, noncombat, printed);
	 default:
		 return incapacitatedPerson(a, noncombat, printed);
	 }
 }
 string getSpecialAttackString(DeprecatedCreature &a, DeprecatedCreature &t, int &resist, int &attack) {

	 char str[200];
	 strcpy(str, a.getNameAndAlignment().name.data());
	 strcat(str, singleSpace.c_str());

	 switch (a.type)
	 {
	 case CREATURE_JUDGE_CONSERVATIVE:
	 case CREATURE_JUDGE_LIBERAL:
		 strcat(str, pickrandom(judge_debate).c_str());
		 strcat(str, singleSpace.c_str());
		 strcat(str, t.getNameAndAlignment().name.data());
		 strcat(str, CONST_EXCLAMATION_POINT.c_str());
		 if (t.getCreatureHealth().align == 1)
			 resist = t.skill_roll(SKILL_LAW) +
			 t.attribute_roll(ATTRIBUTE_HEART);
		 else
			 resist = t.skill_roll(SKILL_LAW) +
			 t.attribute_roll(ATTRIBUTE_WISDOM);
		 attack += a.skill_roll(SKILL_LAW);
		 break;
	 case CREATURE_SCIENTIST_EMINENT:
		 switch (LCSrandom(scientist_debate.size() + 1))
		 {
		 case 0:if (a.getCreatureHealth().align == ALIGN_CONSERVATIVE)strcat(str, CONST_EXPLAINS_THE_BENEFITS_OF_RESEARCH_TO.c_str());
				else strcat(str, CONST_EXPLAINS_ETHICAL_RESEARCH_TO.c_str()); break;
		 default:
			 strcat(str, pickrandom(scientist_debate).c_str()); break;
		 }
		 strcat(str, singleSpace.c_str());
		 strcat(str, t.getNameAndAlignment().name.data());
		 strcat(str, CONST_EXCLAMATION_POINT.c_str());
		 if (t.getCreatureHealth().align == 1)
			 resist = t.skill_roll(SKILL_SCIENCE) +
			 t.attribute_roll(ATTRIBUTE_HEART);
		 else
			 resist = t.skill_roll(SKILL_SCIENCE) +
			 t.attribute_roll(ATTRIBUTE_WISDOM);
		 attack += a.skill_roll(SKILL_SCIENCE);
		 break;
	 case CREATURE_POLITICIAN:
		 if (a.getCreatureHealth().align == -1)
			 strcat(str, pickrandom(conservative_politician_debate).c_str());
		 else
			 strcat(str, pickrandom(other_politician_debate).c_str());
		 strcat(str, singleSpace.c_str());
		 strcat(str, t.getNameAndAlignment().name.data());
		 strcat(str, CONST_EXCLAMATION_POINT.c_str());
		 if (t.getCreatureHealth().align == 1)
			 resist = t.skill_roll(SKILL_LAW) +
			 t.attribute_roll(ATTRIBUTE_HEART);
		 else
			 resist = t.skill_roll(SKILL_LAW) +
			 t.attribute_roll(ATTRIBUTE_WISDOM);
		 attack += a.skill_roll(SKILL_LAW);
		 break;
	 case CREATURE_CORPORATE_CEO:
		 if (a.getCreatureHealth().align == -1)
			 strcat(str, pickrandom(conservative_ceo_debate).c_str());
		 else
			 strcat(str, pickrandom(other_ceo_debate).c_str());
		 strcat(str, singleSpace.c_str());
		 strcat(str, t.getNameAndAlignment().name.data());
		 strcat(str, CONST_EXCLAMATION_POINT.c_str());
		 if (t.getCreatureHealth().align == 1)
			 resist = t.skill_roll(SKILL_BUSINESS) +
			 t.attribute_roll(ATTRIBUTE_HEART);
		 else
			 resist = t.skill_roll(SKILL_BUSINESS) +
			 t.attribute_roll(ATTRIBUTE_WISDOM);
		 attack += a.skill_roll(SKILL_BUSINESS);
		 break;
	 case CREATURE_RADIOPERSONALITY:
	 case CREATURE_NEWSANCHOR:
		 strcat(str, pickrandom(media_debate).c_str());
		 strcat(str, singleSpace.c_str());
		 strcat(str, t.getNameAndAlignment().name.data());
		 strcat(str, CONST_EXCLAMATION_POINT.c_str());
		 if (t.getCreatureHealth().align == 1)
			 resist = t.attribute_roll(ATTRIBUTE_HEART);
		 else
			 resist = t.attribute_roll(ATTRIBUTE_WISDOM);
		 attack += a.attribute_roll(ATTRIBUTE_CHARISMA);
		 break;
	 case CREATURE_MILITARYOFFICER:
		 strcat(str, pickrandom(military_debate).c_str());
		 strcat(str, singleSpace.c_str());
		 strcat(str, t.getNameAndAlignment().name.data());
		 strcat(str, CONST_EXCLAMATION_POINT.c_str());
		 if (t.getCreatureHealth().align == 1)
			 resist = t.attribute_roll(ATTRIBUTE_HEART);
		 else
			 resist = t.attribute_roll(ATTRIBUTE_WISDOM);
		 attack += a.attribute_roll(ATTRIBUTE_CHARISMA);
		 break;
	 case CREATURE_COP:
		 if (a.enemy())
		 {
			 strcat(str, pickrandom(police_debate).c_str());
			 strcat(str, singleSpace.c_str());
			 strcat(str, t.getNameAndAlignment().name.data());
			 strcat(str, CONST_EXCLAMATION_POINT.c_str());
			 resist = t.attribute_roll(ATTRIBUTE_HEART);
			 attack += a.skill_roll(SKILL_PERSUASION);
			 break;
		 }
		 //No break. If the cop is a liberal it will do a musical attack instead.
	 default:
		 if (a.get_weapon().get_specific_bool(BOOL_MUSICAL_ATTACK_) || a.type == CREATURE_COP)
		 {
			 switch (LCSrandom(5))
			 {
				 //TODO IsaacG Migrate Strings
			 case 0:strcat(str, CONST_PLAYS_A_SONG_FOR.c_str()); break;
			 case 1:strcat(str, CONST_SINGS_TO.c_str()); break;
			 case 2:if (a.get_weapon().get_specific_bool(BOOL_MUSICAL_ATTACK_))
			 {
				 strcat(str, CONST_STRUMS_THE.c_str());
				 strcat(str, a.get_weapon().get_name().c_str());
			 }
					else // let's use a small enough instrument for anyone to carry in their pocket
						strcat(str, CONST_BLOWS_A_HARMONICA.c_str());
				 strcat(str, CONST_AT.c_str()); break;
			 case 3:if (a.getCreatureHealth().align == 1)strcat(str, CONST_PLAYS_PROTEST_SONGS_AT.c_str());
					else strcat(str, CONST_PLAYS_COUNTRY_SONGS_AT.c_str());
					break;
			 case 4:strcat(str, CONST_ROCKS_OUT_AT.c_str()); break;
			 }
			 strcat(str, singleSpace.c_str());
			 strcat(str, t.getNameAndAlignment().name.data());
			 strcat(str, CONST_EXCLAMATION_POINT.c_str());
			 attack = a.skill_roll(SKILL_MUSIC);
			 if (t.getCreatureHealth().align == 1)
				 resist = t.attribute_roll(ATTRIBUTE_HEART);
			 else resist = t.attribute_roll(ATTRIBUTE_WISDOM);
			 if (resist > 0)
				 a.train(SKILL_MUSIC, LCSrandom(resist) + 1);
			 else a.train(SKILL_MUSIC, 1);
		 }
		 break;
	 }
	 return str;
 }
 void specialattack(DeprecatedCreature &a, DeprecatedCreature &t)
 {
	 int resist = 0;
	 clearmessagearea();
	 set_color_easy(WHITE_ON_BLACK_BRIGHT);
	 int attack = 0;
	 if (a.getCreatureHealth().align != 1)
		 attack = a.attribute_roll(ATTRIBUTE_WISDOM) + t.get_attribute(ATTRIBUTE_WISDOM, false);
	 else //if (a.align == 1)
		 attack = a.attribute_roll(ATTRIBUTE_HEART) + t.get_attribute(ATTRIBUTE_HEART, false);

	 mvaddstrAlt(16, 1, getSpecialAttackString(a, t, resist, attack), gamelog);

	 gamelog.newline();
	 if ((t.getCreatureHealth().animalgloss == ANIMALGLOSS_TANK || (t.getCreatureHealth().animalgloss == ANIMALGLOSS_ANIMAL && lawList[LAW_ANIMALRESEARCH] != 2))
		 || (a.enemy() && t.flag & CREATUREFLAG_BRAINWASHED))
	 {
		 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_IS_IMMUNE_TO_THE_ATTACK, gamelog);
	 }
	 else if (a.getCreatureHealth().align == t.getCreatureHealth().align)
	 {
		 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_ALREADY_AGREES_WITH + a.getNameAndAlignment().name + singleDot);
	 }
	 else if (attack > resist)
	 {
		 t.increase_stunned((attack - resist) / 4);
		 if (a.enemy())
		 {
			 if (t.juice > 100)
			 {
				 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_LOSES_JUICE, gamelog);
				 addjuice(t, -50, 100);
			 }
			 else if (LCSrandom(15) > t.get_attribute(ATTRIBUTE_WISDOM, true) || t.get_attribute(ATTRIBUTE_WISDOM, true) < t.get_attribute(ATTRIBUTE_HEART, true))
			 {
				 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_IS_TAINTED_WITH_WISDOM, gamelog);
				 t.adjust_attribute(ATTRIBUTE_WISDOM, +1);
			 }
			 else if (t.getCreatureHealth().align == ALIGN_LIBERAL && t.flag & CREATUREFLAG_LOVESLAVE)
			 {
				 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_CAN_T_BEAR_TO_LEAVE, gamelog);
			 }
			 else
			 {
				 if (a.getCreatureHealth().align == -1)
				 {
					 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_IS_TURNED_CONSERVATIVE, gamelog);
					 t.stop_being_stunned();
					 if (t.is_holding_body())
						 freehostage(t, 0);
					 addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
				 }
				 else
				 {
					 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_DOESN_T_WANT_TO_FIGHT_ANYMORE, gamelog);
					 t.stop_being_stunned();
					 if (t.is_holding_body())
						 freehostage(t, 0);
					 addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
				 }
				 for (int e = 0; e < ENCMAX; e++)
				 {
					 if (encounter[e].getNameAndAlignment().exists == 0)
					 {
						 encounter[e] = t;
						 encounter[e].make_existing();
						 if (a.getCreatureHealth().align == -1)conservatise(encounter[e]);
						 encounter[e].make_cantbluff_two();
						 encounter[e].squadid = -1;
						 break;
					 }
				 }
				 bool flipstart = 0;
				 for (int p = 0; p < 6; p++)
				 {
					 if (activesquad->squad[p] == &t)
					 {
						 activesquad->squad[p]->die();
						 activesquad->squad[p]->location = -1;
						 activesquad->squad[p] = NULL;
						 flipstart = 1;
					 }
					 if (flipstart&&p < 5) activesquad->squad[p] = activesquad->squad[p + 1];
				 }
				 if (flipstart) activesquad->squad[5] = NULL;
			 }
		 }
		 else
		 {
			 if (t.juice >= 100)
			 {
				 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_SEEMS_LESS_BADASS, gamelog);
				 addjuice(t, -50, 99);
			 }
			 else if (!t.attribute_check(ATTRIBUTE_HEART, DIFFICULTY_AVERAGE) ||
				 t.get_attribute(ATTRIBUTE_HEART, true) < t.get_attribute(ATTRIBUTE_WISDOM, true))
			 {
				 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_S_HEART_SWELLS, gamelog);
				 t.adjust_attribute(ATTRIBUTE_HEART, +1);
			 }
			 else
			 {
				 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_HAS_TURNED_LIBERAL, gamelog);
				 t.stop_being_stunned();
				 liberalize(t);
				 t.infiltration /= 2;
				 t.flag |= CREATUREFLAG_CONVERTED;
				 t.make_cantbluff_zero();
			 }
		 }
	 }
	 else
	 {
		 mvaddstrAlt(17, 1, t.getNameAndAlignment().name + (string)CONST_REMAINS_STRONG, gamelog);
	 }
	 gamelog.newline();
	 printparty();
	 if (mode == GAMEMODE_CHASECAR ||
		 mode == GAMEMODE_CHASEFOOT) printchaseencounter();
	 else printencounter();
	 pressAnyKey();
	 return;
 }
 /* modifies a combat roll based on the creature's critical injuries */
 void healthmodroll(int &aroll, DeprecatedCreature &a)
 {
	 if (a.getCreatureHealth().special[SPECIALWOUND_RIGHTEYE] != 1) aroll -= LCSrandom(2);
	 if (a.getCreatureHealth().special[SPECIALWOUND_LEFTEYE] != 1) aroll -= LCSrandom(2);
	 if (a.getCreatureHealth().special[SPECIALWOUND_RIGHTEYE] != 1 &&
		 a.getCreatureHealth().special[SPECIALWOUND_LEFTEYE] != 1) aroll -= LCSrandom(20);
	 if (a.getCreatureHealth().special[SPECIALWOUND_RIGHTLUNG] != 1) aroll -= LCSrandom(8);
	 if (a.getCreatureHealth().special[SPECIALWOUND_LEFTLUNG] != 1) aroll -= LCSrandom(8);
	 if (a.getCreatureHealth().special[SPECIALWOUND_HEART] != 1) aroll -= LCSrandom(10);
	 if (a.getCreatureHealth().special[SPECIALWOUND_LIVER] != 1) aroll -= LCSrandom(5);
	 if (a.getCreatureHealth().special[SPECIALWOUND_STOMACH] != 1) aroll -= LCSrandom(5);
	 if (a.getCreatureHealth().special[SPECIALWOUND_RIGHTKIDNEY] != 1) aroll -= LCSrandom(5);
	 if (a.getCreatureHealth().special[SPECIALWOUND_LEFTKIDNEY] != 1) aroll -= LCSrandom(5);
	 if (a.getCreatureHealth().special[SPECIALWOUND_SPLEEN] != 1) aroll -= LCSrandom(4);
	 if (a.getCreatureHealth().special[SPECIALWOUND_LOWERSPINE] != 1) aroll -= LCSrandom(100);
	 if (a.getCreatureHealth().special[SPECIALWOUND_UPPERSPINE] != 1) aroll -= LCSrandom(200);
	 if (a.getCreatureHealth().special[SPECIALWOUND_NECK] != 1) aroll -= LCSrandom(300);
	 if (a.getCreatureHealth().special[SPECIALWOUND_RIBS] < RIBNUM) aroll -= LCSrandom(5);
	 if (a.getCreatureHealth().special[SPECIALWOUND_RIBS] < RIBNUM / 2) aroll -= LCSrandom(5);
	 if (a.getCreatureHealth().special[SPECIALWOUND_RIBS] == 0) aroll -= LCSrandom(5);
 }
 /* adjusts attack damage based on armor, other factors */
 void damagemod(const DeprecatedCreature t, const char &damtype, int &damamount, int mod)
 {

	 if (mod > 10) mod = 10; // Cap damage multiplier (every 5 points adds 1x damage)
	 if (mod <= -20) damamount >>= 8;  //Cars plus heavy armor can be really tough.
	 else if (mod <= -14) damamount >>= 7;
	 else if (mod <= -8) damamount >>= 6;
	 else if (mod <= -6) damamount >>= 5;
	 else if (mod <= -4) damamount >>= 4;
	 else if (mod <= -3) damamount >>= 3;
	 else if (mod <= -2) damamount >>= 2;
	 else if (mod <= -1) damamount >>= 1;
	 else if (mod >= 0) damamount = (int)((float)damamount * (1.0f + 0.2f*mod));
	 // Firefighter's bunker gear reduces fire damage by 3/4
	 if ((damtype & WOUND_BURNED) && t.get_armor().has_fireprotection())
	 {
		 // Damaged gear isn't as effective as undamaged gear
		 if (t.get_armor().is_damaged())
			 damamount >>= 1; // Only half as much damage reduction
		 else
			 damamount >>= 2; // Full damage reduction
	 }
	 if (damamount < 0)damamount = 0;
 }
 std::string bodypartName(Bodyparts w, AnimalGlosses t) {
	 if (t == ANIMALGLOSS_TANK) {
		 if (tankBodyParts.count(w) > 0)
			 return tankBodyParts[w];
	 }
	 else if (t == ANIMALGLOSS_ANIMAL) {// FIXME: What about Six-legged Pigs?
		 if (animalBodyParts.count(w) > 0)
			 return animalBodyParts[w];
	 }
	 else {
		 if (humanBodyParts.count(w) > 0)
			 return humanBodyParts[w];
	 }
	 return CONST_NULL_BODYPART;
 }
 /* damages the selected armor if it covers the body part specified */
 void armordamage(Armor &armor, const int bp, const int damamount)
 {
	 if (armor.covers(bp) && LCSrandom(armor.get_durability()) < damamount)
	 {
		 if (armor.is_damaged())
		 {
			 armor.decrease_quality(LCSrandom(armor.get_durability()) < LCSrandom(damamount) / armor.get_quality() ? 1 : 0);
		 }
		 else
		 {
			 armor.set_damaged(true);
		 }
	 }
 }
 /* blood explosions */
 void bloodblast(Armor* armor)
 {
	 //GENERAL
	 if (armor != NULL)
		 armor->set_bloody(true);
	 if (mode != GAMEMODE_SITE)
		 return;
	 levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_BLOODY2;
	 //HIT EVERYTHING
	 for (int p = 0; p < 6; p++)
	 {
		 if (activesquad->squad[p] == NULL) continue;
		 if (!LCSrandom(2))
			 activesquad->squad[p]->get_armor().set_bloody(true);
	 }
	 bloodyUpEncounterArmor();
	 //REFRESH THE SCREEN
	 printsitemap(loc_coord.locx, loc_coord.locy, loc_coord.locz);
	 refreshAlt();
 }
 /* destroys armor, masks, drops weapons based on severe damage */
 void severloot(DeprecatedCreature &cr)
 {
	 int armok = 2;
	 if ((cr.getCreatureHealth().wound[BODYPART_ARM_RIGHT] & WOUND_NASTYOFF) ||
		 (cr.getCreatureHealth().wound[BODYPART_ARM_RIGHT] & WOUND_CLEANOFF)) armok--;
	 if ((cr.getCreatureHealth().wound[BODYPART_ARM_LEFT] & WOUND_NASTYOFF) ||
		 (cr.getCreatureHealth().wound[BODYPART_ARM_LEFT] & WOUND_CLEANOFF)) armok--;
	 if (cr.getCreatureHealth().special[SPECIALWOUND_NECK] != 1) armok = 0;
	 if (cr.getCreatureHealth().special[SPECIALWOUND_UPPERSPINE] != 1) armok = 0;
	 if (cr.is_armed() && armok == 0)
	 {
		 clearmessagearea();
		 set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		 mvaddstrAlt(16, 1, tag_The, gamelog);
		 addstrAlt(cr.get_weapon().get_name(1), gamelog);
		 addstrAlt(CONST_SLIPS_FROM, gamelog);
		 mvaddstrAlt(17, 1, cr.getNameAndAlignment().name, gamelog);
		 addstrAlt(CONST_S_GRASP, gamelog);
		 gamelog.newline();
		 pressAnyKey();
		 if (mode == GAMEMODE_SITE) cr.drop_weapons_and_clips(&groundloot);
		 else cr.drop_weapons_and_clips(NULL);
	 }
	 if ((((cr.getCreatureHealth().wound[BODYPART_BODY] & WOUND_CLEANOFF) ||
		 (cr.getCreatureHealth().wound[BODYPART_BODY] & WOUND_NASTYOFF)) &&
		 cr.get_armor().covers(BODYPART_BODY)) ||
		 ((cr.getCreatureHealth().wound[BODYPART_HEAD] & WOUND_NASTYOFF) &&
			 cr.get_armor().is_mask()))
	 {
		 clearmessagearea();
		 set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		 mvaddstrAlt(16, 1, cr.getNameAndAlignment().name, gamelog);
		 addstrAlt(CONST_X_S_SPACE, gamelog);
		 addstrAlt(cr.get_armor().get_name(), gamelog);
		 addstrAlt(CONST_HAS_BEEN_DESTROYED, gamelog);
		 gamelog.newline();
		 pressAnyKey();
		 cr.strip(NULL);
	 }
 }
 /* describes a character's death */
 void adddeathmessage(DeprecatedCreature &cr)
 {
	 set_color_easy(YELLOW_ON_BLACK_BRIGHT);
	 char str[200];
	 char secondLine[200];
	 bool hasSecondLine = false;
	 strcpy(str, cr.getNameAndAlignment().name.data());
	 if ((cr.getCreatureHealth().wound[BODYPART_HEAD] & WOUND_CLEANOFF) ||
		 (cr.getCreatureHealth().wound[BODYPART_HEAD] & WOUND_NASTYOFF))
	 {
		 hasSecondLine = true;
		 switch (LCSrandom(4))
		 {
			 //TODO IsaacG Complete Migration of Strings
		 case 0:
			 strcat(str, CONST_REACHES_ONCE_WHERE_THERE.c_str());
			 if (mode != GAMEMODE_CHASECAR)
				 strcpy(secondLine, CONST_IS_NO_HEAD_AND_FALLS.c_str());
			 else strcpy(secondLine, CONST_IS_NO_HEAD_AND_SLUMPS_OVER.c_str());
			 break;
		 case 1:
			 if (mode != GAMEMODE_CHASECAR)
				 strcat(str, CONST_STANDS_HEADLESS_FOR_A.c_str());
			 else strcat(str, CONST_SITS_HEADLESS_FOR_A.c_str());
			 strcpy(secondLine, CONST_MOMENT_THEN_CRUMPLES_OVER.c_str());
			 break;
		 case 2:
			 strcat(str, CONST_SQUIRTS.c_str());
			 if (lawList[LAW_FREESPEECH] == -2)strcat(str, CONST_RED_WATER.c_str());
			 else strcat(str, tag_blood.c_str());
			 strcat(str, CONST_OUT_OF_THE.c_str());
			 if (mode != GAMEMODE_CHASECAR)
				 strcpy(secondLine, CONST_NECK_AND_RUNS_DOWN_THE_HALL.c_str());
			 else strcpy(secondLine, CONST_NECK_AND_FALLS_TO_THE_SIDE.c_str());
			 break;
		 case 3:
			 strcat(str, CONST_SUCKS_A_LAST_BREATH_THROUGH.c_str());
			 strcpy(secondLine, CONST_THE_NECK_HOLE_THEN_IS_QUIET.c_str());
			 break;
		 }
	 }
	 else if ((cr.getCreatureHealth().wound[BODYPART_BODY] & WOUND_CLEANOFF) ||
		 (cr.getCreatureHealth().wound[BODYPART_BODY] & WOUND_NASTYOFF))
	 {
		 strcat(str, (singleSpace + pickrandom(body_falls_apart)).c_str());
	 }
	 else
	 {
		 hasSecondLine = true;
		 switch (LCSrandom(11))
		 {
		 case 0:
			 strcat(str, CONST_SWEATS_PROFUSELY_MURMURS.c_str());
			 if (lawList[LAW_FREESPEECH] == -2)strcpy(secondLine, CONST_SOMETHING_GOOD_ABOUT_JESUS_AND_DIES.c_str());
			 else strcpy(secondLine, CONST_SOMETHING_ABOUT_JESUS_AND_DIES.c_str());
			 break;
		 case 1:
			 strcat(str, CONST_GASPS_A_LAST_BREATH_AND.c_str());
			 if (lawList[LAW_FREESPEECH] == -2) strcpy(secondLine, CONST_X_MAKES_A_MESS.c_str());
			 else strcpy(secondLine, CONST_X_SOILS_THE_FLOOR.c_str());
			 break;
		 case 2:
			 strcat(str, CONST_SPEAKS_THESE_FINAL_WORDS.c_str());
			 switch (cr.getCreatureHealth().align)
			 {
			 case ALIGN_LIBERAL:
			 case ALIGN_ELITELIBERAL:
				 strcpy(secondLine, slogan_str.c_str()); break;
			 case ALIGN_MODERATE:
				 strcpy(secondLine, CONST_A_PLAGUE_ON_BOTH_YOUR_HOUSES.c_str()); break;
			 default:
				 strcpy(secondLine, CONST_BETTER_DEAD_THAN_LIBERAL.c_str()); break;
			 }
			 break;
		 default:
			 vector<string> death = pickrandom(double_line_death);
			 strcat(str, (singleSpace + death[0]).c_str());
			 strcpy(secondLine, death[1].c_str());
			 break;
		 }
	 }
	 mvaddstrAlt(16, 1, str, gamelog);
	 if (hasSecondLine) {
		 mvaddstrAlt(17, 1, secondLine, gamelog);
	 }
	 gamelog.newline();
 }
 bool attemptSpecialAttack(DeprecatedCreature &a, DeprecatedCreature &t, const bool force_melee) {
	 vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	 //SPECIAL ATTACK!
	 int encnum = 0;
	 for (int e = 0; e < ENCMAX; e++) if (encounter[e].exists) encnum++;
	 bool specialAttackIsPossible = (!force_melee &&
		 (((a.type == CREATURE_COP && a.getCreatureHealth().align == ALIGN_MODERATE && a.enemy()) ||
			 a.type == CREATURE_SCIENTIST_EMINENT ||
			 a.type == CREATURE_JUDGE_LIBERAL ||
			 a.type == CREATURE_JUDGE_CONSERVATIVE ||
			 (a.type == CREATURE_CORPORATE_CEO && LCSrandom(2)) ||
			 a.type == CREATURE_POLITICIAN ||
			 a.type == CREATURE_RADIOPERSONALITY ||
			 a.type == CREATURE_NEWSANCHOR ||
			 a.type == CREATURE_MILITARYOFFICER ||
			 a.get_weapon().get_specific_bool(BOOL_MUSICAL_ATTACK_)) &&
			 (a.get_weapon().get_specific_bool(BOOL_MUSICAL_ATTACK_) || !a.is_armed() || a.getCreatureHealth().align != 1)));
	 if (specialAttackIsPossible)
	 {
		 if (a.getCreatureHealth().align == 1 || encnum < ENCMAX)
		 {
			 specialattack(a, t);
			 return true;
		 }
	 }
	 return false;
 }
 bool attemptReload(DeprecatedCreature &a, const bool force_melee) {
	 //RELOAD
	 if ((a.will_reload(mode == GAMEMODE_CHASECAR, force_melee)
		 || (a.has_thrown_weapon && a.has_extra_throwing_weapons()))
		 && !force_melee)
	 {
		 char str[200];
		 if (a.will_reload(mode == GAMEMODE_CHASECAR, force_melee))
		 {
			 a.reload(false);
			 strcpy(str, a.getNameAndAlignment().name.data());
			 strcat(str, CONST_RELOADS.c_str());
		 }
		 else if (a.has_thrown_weapon && a.has_extra_throwing_weapons())
		 {
			 a.ready_another_throwing_weapon();
			 strcpy(str, a.getNameAndAlignment().name.data());
			 strcat(str, CONST_READIES_ANOTHER.c_str());
			 strcat(str, a.get_weapon().get_name().c_str());
			 strcat(str, singleDot.c_str());
		 }
		 mvaddstrAlt(16, 1, str, gamelog);
		 gamelog.newline();
		 printparty();
		 if (mode == GAMEMODE_CHASECAR
			 || mode == GAMEMODE_CHASEFOOT) printchaseencounter();
		 else printencounter();
		 pressAnyKey();
		 return true;
	 }
	 else if (a.has_thrown_weapon) a.has_thrown_weapon = false;
	 return false;
 }
 bool attemptIncapacitated(DeprecatedCreature &a) {
	 //INCAPACITATED
	 char incaprint;
	 a.forceinc = 0;
	 if (incapacitated(a, 0, incaprint))
	 {
		 if (incaprint)
		 {
			 printparty();
			 if (mode == GAMEMODE_CHASECAR ||
				 mode == GAMEMODE_CHASEFOOT) printchaseencounter();
			 else printencounter();
			 pressAnyKey();
		 }
		 a.forceinc = 1;
		 return true;
	 }
	 return false;
 }

 string showMultipleHits(DeprecatedCreature &a, const int bursthits, const attackst attack_used) {
	 string str;
	 // show multiple hits
	 if (bursthits > 1 && a.is_armed()) // Only show if not melee
	 {
		 str = COMMA_SPACE;
		 if (!a.is_armed()) //Move into WEAPON_NONE? -XML
		 {
			 str += CONST_STRIKING;
		 }
		 else {
			 str += attack_used.hit_description;
		 }
		 str += burstHitString(bursthits);
	 }
	 else if (attack_used.always_describe_hit)
	 {
		 str += COMMA_SPACE;
		 str += attack_used.hit_description;
	 }
	 return str;
 }
 DeprecatedCreature* takeBulletForLeader(DeprecatedCreature &t, const int damamount, const int w) {
	 DeprecatedCreature* target = 0;
	 if (t.squadid != -1 && t.hireid == -1 && //if the founder is hit...
		 (damamount > t.getCreatureHealth().blood || damamount >= 10) && //and lethal or potentially crippling damage is done...
		 (w == BODYPART_HEAD || w == BODYPART_BODY)) //to a critical bodypart...
	 {
		 //Oh Noes!!!! Find a liberal to jump in front of the bullet!!!
		 for (int i = 0; i < 6; i++)
		 {
			 if (activesquad->squad[i] == NULL) break;
			 if (activesquad->squad[i] == &t) break;
			 if (activesquad->squad[i]->get_attribute(ATTRIBUTE_HEART, true) > 8 &&
				 activesquad->squad[i]->get_attribute(ATTRIBUTE_AGILITY, true) > 4)
			 {
				 target = activesquad->squad[i];
				 clearmessagearea();
				 set_color_easy(GREEN_ON_BLACK_BRIGHT);
				 mvaddstrAlt(16, 1, target->getNameAndAlignment().name, gamelog);
				 if (!t.getCreatureHealth().alive) addstrAlt(CONST_MISGUIDEDLY, gamelog);
				 else addstrAlt(CONST_HEROICALLY, gamelog);
				 addstrAlt(CONST_SHIELDS, gamelog);
				 addstrAlt(t.getNameAndAlignment().name, gamelog);
				 if (!t.getCreatureHealth().alive) addstrAlt(CONST_S_CORPSE, gamelog);
				 addstrAlt(CONST_EXCLAMATION_POINT, gamelog);
				 gamelog.newline();
				 addjuice(*target, 10, 1000);//Instant juice!! Way to take the bullet!!
				 pressAnyKey();
				 break;
			 }
		 }
	 }
	 return target;
 }

 int determineBodypartHit(DeprecatedCreature &t, const int aroll, const int droll, const bool sneak_attack) {

	 bool canhit = false;
	 for (int w = 0; w < BODYPARTNUM && !canhit; w++)
	 {
		 if (!(t.getCreatureHealth().wound[w] & WOUND_CLEANOFF) && !(t.getCreatureHealth().wound[w] & WOUND_NASTYOFF))
		 {
			 canhit = true;
		 }
	 }
	 int w;
	 do
	 {
		 int offset = 0;
		 if (aroll > droll + 5)
			 offset = 4;  // NICE SHOT; MORE LIKELY TO HIT BODY/HEAD
		 if (aroll > droll + 10 &&
			 (!(t.getCreatureHealth().wound[BODYPART_HEAD] & (WOUND_CLEANOFF | WOUND_NASTYOFF)) ||
				 !(t.getCreatureHealth().wound[BODYPART_BODY] & (WOUND_CLEANOFF | WOUND_NASTYOFF))))
			 offset = 8;  // NO LIMB HITS HERE YOU AWESOME PERSON
		 if (sneak_attack)
			 offset = 10; // Backstab! 2/3 body, 1/3 head
		 if (aroll > droll + 15 &&
			 !(t.getCreatureHealth().wound[BODYPART_HEAD] & (WOUND_CLEANOFF | WOUND_NASTYOFF)))
			 offset = 12; // BOOM AUTOMATIC HEADSHOT MOTHA******
						  //Weighted location roll:
						  //200% chance to hit body
						  //50% chance to hit head
		 w = offset + LCSrandom(13 - offset);
		 switch (w)
		 {
		 case 12:w = BODYPART_HEAD; break;
		 case 11:
		 case 10:
		 case 9:
		 case 8:w = BODYPART_BODY; break;
		 case 7:
		 case 3:w = BODYPART_ARM_RIGHT; break;
		 case 6:
		 case 2:w = BODYPART_ARM_LEFT; break;
		 case 5:
		 case 1:w = BODYPART_LEG_RIGHT; break;
		 case 4:
		 case 0:w = BODYPART_LEG_LEFT; break;
		 }
	 } while (((t.getCreatureHealth().wound[w] & WOUND_CLEANOFF) || (t.getCreatureHealth().wound[w] & WOUND_NASTYOFF)) && canhit == true);
	 return w;
 }
 string printSpecialWounds(DeprecatedCreature* target, const int w, const int damamount, const int damtype) {

	 char heavydam = 0, breakdam = 0, pokedam = 0;
	 if (damamount >= 12) //JDS -- 2x damage needed
	 {
		 if (damtype & WOUND_SHOT || damtype & WOUND_BURNED || damtype & WOUND_TORN || damtype & WOUND_CUT) heavydam = 1;
	 }
	 if (damamount >= 10) //JDS -- 2x damage needed
	 {
		 if (damtype & WOUND_SHOT || damtype & WOUND_TORN || damtype & WOUND_CUT) pokedam = 1;
	 }
	 if ((damtype & WOUND_BRUISED || damtype & WOUND_SHOT || damtype & WOUND_TORN || damtype & WOUND_CUT) && damamount >= 50) {
		 breakdam = 1;
	 }
	 string damageDescription;
	 switch (w) {
	 case BODYPART_HEAD:
		 damageDescription = specialWoundPossibilityHead(
			 *target,
			 breakdam,
			 heavydam,
			 damtype
		 );
		 break;
	 case BODYPART_BODY:
		 string damageDescription = specialWoundPossibilityBody(
			 *target,
			 breakdam,
			 pokedam,
			 damtype
		 );
		 break;
	 }
	 return damageDescription;

 }


 char consolidateDamageTypesNotCutOrBruised(const attackst attack_used) {
	 char damtype = 0;
	 if (attack_used.burns) damtype |= WOUND_BURNED;
	 if (attack_used.tears) damtype |= WOUND_TORN;
	 if (attack_used.shoots) damtype |= WOUND_SHOT;
	 if (attack_used.bleeding) damtype |= WOUND_BLEEDING;
	 return damtype;
 }

 char consolidateDamageTypes(const attackst attack_used) {
	 char damtype = 0;
	 if (attack_used.bruises) damtype |= WOUND_BRUISED;
	 if (attack_used.cuts) damtype |= WOUND_CUT;
	 damtype |= consolidateDamageTypesNotCutOrBruised(attack_used);
	 return damtype;
 }

 string initiateCombat(const DeprecatedCreature a, const bool sneak_attack, const attackst attack_used) {


	 string str;

	 if (!a.is_armed())
	 {
		 if (!a.getCreatureHealth().animalgloss) //Move into WEAPON_NONE -XML
		 {
			 str += howGracefulAttack(a.get_skill(SKILL_HANDTOHAND));
		 }
		 else
		 {
			 if (a.specialattack == ATTACK_CANNON)
			 {
				 str += CONST_FIRES_A_120MM_SHELL_AT;
			 }
			 else if (a.specialattack == ATTACK_FLAME) str += CONST_BREATHES_FIRE_AT;
			 else if (a.specialattack == ATTACK_SUCK) str += CONST_STABS;
			 else str += CONST_BITES;
		 }
	 }
	 else
	 {

		 if (sneak_attack)
		 {
			 str += CONST_SNEAKS_UP_ON;
		 }
		 else {
			 str += attack_used.attack_description;
			 setSiteAlarmOne();
		 }
	 }
	 return str;
 }

 string unsuccessfulHit(DeprecatedCreature &a, DeprecatedCreature &t, const int droll) {


	 string str;

	 if (mode == GAMEMODE_CHASECAR)
	 {
		 DeprecatedCreature* driver = getChaseDriver(t);
		 str = driver->getNameAndAlignment().name;
		 if (droll == 1) {
			 str = a.getNameAndAlignment().name;
			 str += CONST_MISSED;
		 }
		 else if (droll == 2) {
			 str = a.getNameAndAlignment().name;
			 str += CONST_JUST_BARELY_MISSED;
		 }
		 else if (droll > 18 || droll < 1) {
			 str = a.getNameAndAlignment().name;
			 str += CONST_MISSES_COMPLETELY;  // You failed to hit someone who probably rolled a zero.  You should feel bad.
		 }
		 else {
			 str += evasionStringsAlt[droll - 3];
		 }
	 }
	 else {
		 str = t.getNameAndAlignment().name;
		 if (droll == 1) {
			 str = a.getNameAndAlignment().name;
			 str += CONST_MISSED;
		 }
		 else if (droll == 2) {
			 str = a.getNameAndAlignment().name;
			 str += CONST_JUST_BARELY_MISSED;
		 }
		 else if (droll > 18 || droll < 1) {
			 str = a.getNameAndAlignment().name;
			 str += CONST_MISSES_COMPLETELY;  // You failed to hit someone who probably rolled a zero.  You should feel bad.
		 }
		 else {
			 str += evasionStrings[droll - 3];
		 }
	 }
	 return str;

 }
 void inflictNonZeroDamage(AttackInfliction attackI,
	 DeprecatedCreature &a,
	 const string inputStr,
	 const AttackSeverity attackS,
	 const int damtype,
	 DeprecatedCreature &t)
 {
	 // These two variables are used and changed within this function, but are never used again by the function that calls this one
	 string str = inputStr;
	 int damamount = attackS.damamount;

	 DeprecatedCreature *target = takeBulletForLeader(t, damamount, attackS.hit_location);
	 if (!target) target = &t;//If nobody jumps in front of the attack,
	 target->apply_wound(attackS.hit_location, damtype);
	 int severamount = bodypartSeverAmount(attackS.hit_location);
	 if (attackS.severtype != -1 && damamount >= severamount)
		 target->apply_wound(attackS.hit_location, (char)attackS.severtype);
	 if (attackS.hit_location != BODYPART_HEAD && attackS.hit_location != BODYPART_BODY && target->getCreatureHealth().blood - damamount <= 0 &&
		 target->getCreatureHealth().blood > 0)
	 {
		 do
		 {
			 if (LCSrandom(100) < attackI.attack_used.no_damage_reduction_for_limbs_chance)
				 break;
			 else damamount >>= 1;
		 } while (target->getCreatureHealth().blood - damamount <= 0);
	 }
	 if (attackS.damagearmor) armordamage(target->get_armor(), attackS.hit_location, damamount); {
		 target->lose_blood(damamount);
	 }
	 levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_BLOODY;

	 string hit_punctuation = attackI.attack_used.hit_punctuation;
	 string dismembered = dismemberingWound(attackS.hit_location, target->getCreatureHealth().wound[attackS.hit_location]);
	 if (len(dismembered)) {
		 hit_punctuation = dismembered;
	 }
	 str += hit_punctuation;

	 if ((target->getCreatureHealth().wound[BODYPART_HEAD] & (WOUND_CLEANOFF | WOUND_NASTYOFF)) ||
		 (target->getCreatureHealth().wound[BODYPART_BODY] & (WOUND_CLEANOFF | WOUND_NASTYOFF)) ||
		 target->getCreatureHealth().blood <= 0)
	 {
		 if ((attackS.hit_location == BODYPART_HEAD && target->getCreatureHealth().wound[BODYPART_HEAD] & WOUND_NASTYOFF) ||
			 (attackS.hit_location == BODYPART_BODY && target->getCreatureHealth().wound[BODYPART_BODY] & WOUND_NASTYOFF)) {
			 bloodblast(&target->get_armor());
		 }
		 const char alreadydead = !target->getCreatureHealth().alive; // This tests whether the person being fatally wounded was a corpse
		 if (!alreadydead)
		 {
			 target->die();
			 if (t.getCreatureHealth().align == -a.getCreatureHealth().align)
				 addjuice(a, 5 + t.juice / 20, 1000); // Instant juice
			 else addjuice(a, -(5 + t.juice / 20), -50);
			 if (target->squadid != -1)
			 {
				 if (target->getCreatureHealth().align == 1) stat_dead++;
			 }
			 else if (target->enemy() && (t.getCreatureHealth().animalgloss != ANIMALGLOSS_ANIMAL || lawList[LAW_ANIMALRESEARCH] == 2))
			 {
				 stat_kills++;
				 if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite())) LocationsPool::getInstance().addSiegeKill(getCurrentSite());
				 if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()) && t.getCreatureHealth().animalgloss == ANIMALGLOSS_TANK) LocationsPool::getInstance().removeTank(getCurrentSite());
				 if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, getCurrentSite()) == RENTING_CCS)
				 {
					 if (target->type == CREATURE_CCS_ARCHCONSERVATIVE) ccs_boss_kills++;
					 ccs_siege_kills++;
				 }
			 }
			 if (target->squadid == -1 &&
				 (target->getCreatureHealth().animalgloss != ANIMALGLOSS_ANIMAL || lawList[LAW_ANIMALRESEARCH] == 2) &&
				 !attackI.sneak_attack)
			 {
				 sitecrime += 10;
				 sitestory->crime.push_back(CRIME_KILLEDSOMEBODY);
				 if (a.squadid != -1) criminalizeparty(LAWFLAG_MURDER);
			 }
		 }
		 //set_color_easy(WHITE_ON_BLACK_BRIGHT);
		 if (goodguyattack) { set_color_easy(GREEN_ON_BLACK_BRIGHT); }
		 else { set_color_easy(RED_ON_BLACK_BRIGHT); }

		 mvaddstrAlt(17, 1, str, gamelog);
		 gamelog.newline();
		 pressAnyKey();
		 if (!alreadydead)
		 {
			 severloot(t);
			 clearmessagearea();
			 adddeathmessage(*target);
			 pressAnyKey();
			 if (target->is_holding_body()) freehostage(t, 1);
		 }
	 }
	 else
	 {
		 if (target->getCreatureHealth().wound[attackS.hit_location] & WOUND_NASTYOFF) bloodblast(&target->get_armor());
		 if (goodguyattack) set_color_easy(GREEN_ON_BLACK_BRIGHT);
		 else set_color_easy(RED_ON_BLACK_BRIGHT);
		 //set_color_easy(WHITE_ON_BLACK_BRIGHT);
		 mvaddstrAlt(17, 1, str, gamelog);
		 gamelog.newline();
		 printparty();
		 if (mode == GAMEMODE_CHASECAR ||
			 mode == GAMEMODE_CHASEFOOT) printchaseencounter();
		 else printencounter();
		 pressAnyKey();
		 //SPECIAL WOUNDS
		 string damageDescription;
		 if (!(target->getCreatureHealth().wound[attackS.hit_location] & (WOUND_CLEANOFF | WOUND_NASTYOFF)) &&
			 !target->getCreatureHealth().animalgloss)
		 {
			 damageDescription = printSpecialWounds(target, attackS.hit_location, damamount, damtype);
			 severloot(*target);
		 }
		 if (len(damageDescription) > 0) {
			 clearmessagearea();
			 if (goodguyattack) set_color_easy(GREEN_ON_BLACK_BRIGHT);
			 else set_color_easy(RED_ON_BLACK_BRIGHT);
			 mvaddstrAlt(16, 1, damageDescription, gamelog);
			 gamelog.newline();
			 pressAnyKey();
		 }
		 //set_color_easy(WHITE_ON_BLACK_BRIGHT);
	 }
 }

 int couldVehicleHaveBlockedAttack(const int mod, const  int armor, const char damtype,
	 const int armorpiercing, const int car_dmg) {
	 // Could the vehicle have bounced that round on its own?
	 int cardmg = car_dmg;

	 DeprecatedCreature testDummy; // Spawn nude test dummy to see if body armor was needed to prevent damage
	 int mod3 = mod;

	 const int mod2 = armor + LCSrandom(armor + 1) - armorpiercing;
	 if (mod2 > 0) mod3 -= mod2 * 2;
	 damagemod(testDummy, damtype, cardmg, mod3);

	 return cardmg;
 }
 int couldTankHaveBlockedAttack(const int mod, const char damtype,
	 const int armorpiercing, const int car_dmg) {
	 int armor;
	 if (damtype != WOUND_BURNED) armor = 15;
	 else armor = 10;
	 // Could the vehicle have bounced that round on its own?
	 int cardmg = car_dmg;
	 DeprecatedCreature testDummy; // Spawn nude test dummy to see if body armor was needed to prevent damage
	 int mod3 = mod;

	 const int mod2 = armor + LCSrandom(armor + 1) - armorpiercing;
	 if (mod2 > 0) mod3 -= mod2 * 2;
	 damagemod(testDummy, damtype, cardmg, mod3);

	 return cardmg;
 }
 void defineIfDefined(const attackst attack_used, int &random, int &fixed, int &severtype) {
	 if (attack_used.critical.random_damage_defined)
		 random = attack_used.critical.random_damage;
	 if (attack_used.critical.fixed_damage_defined)
		 fixed = attack_used.critical.fixed_damage;
	 if (attack_used.critical.severtype_defined)
		 severtype = attack_used.critical.severtype;
 }
 string bouncesOffCar(const Vehicle* vehicle, const int vehicleHitLocation) {
	 string str = CONST_THE_ATTACK_BOUNCES_OFF;

	 str += (CONST_THE + vehicle->shortname() + CONST_X_S_SPACE);
	 str += vehicle->getpartname(vehicleHitLocation);

	 return str;
 }
 void updateDamageExcludingCar(const DeprecatedCreature t, char &damtype, int &damamount, const damageDetails ddetails) {

	 int mod3 = ddetails.mod;
	 int armor = t.get_armor().get_armor(ddetails.hit_location);
	 if (t.getCreatureHealth().animalgloss == ANIMALGLOSS_TANK)
	 {
		 if (damtype != WOUND_BURNED) armor = 15;
		 else armor = 10;
	 }
	 //if(t.get_armor().get_quality()>1)
	 armor -= t.get_armor().get_quality() - 1;
	 if (t.get_armor().is_damaged())
		 armor -= 1;
	 if (armor < 0) armor = 0; // Possible from second-rate clothes
	 armor += ddetails.extraarmor; // Add vehicle armor 
	 const int mod2 = armor + LCSrandom(armor + 1) - ddetails.armorpiercing;
	 if (mod2 > 0) mod3 -= mod2 * 2;
	 damagemod(t, damtype, damamount, mod3);
 }
 void inflictDamage(const int numhits, DeprecatedCreature &a, DeprecatedCreature &t, const AttackInfliction attackI) {


	 int hit_location = determineBodypartHit(t, attackI.aroll, attackI.droll, attackI.sneak_attack);


	 char damtype = 0;
	 int damamount = 0;
	 char strengthmin = 1;
	 char strengthmax = 1;
	 int severtype = -1;
	 char damagearmor = 0;
	 char armorpiercing = 0;
	 int extraarmor = 0;
	 if (!a.is_armed())
	 {
		 strengthmin = 5;
		 strengthmax = 10;
		 for (int i = numhits; i > 0; i--) //Put into WEAPON_NONE -XML
		 {
			 damamount += LCSrandom(5 + a.get_skill(SKILL_HANDTOHAND)) + 1 + a.get_skill(SKILL_HANDTOHAND);
		 }
		 if (!a.getCreatureHealth().animalgloss) damtype |= WOUND_BRUISED;
		 else
		 {
			 switch (a.specialattack) {
			 case ATTACK_CANNON:
				 damamount = LCSrandom(5000) + 5000;
				 armorpiercing = 20;

				 damtype |= consolidateDamageTypesNotCutOrBruised(attackI.attack_used);

				 strengthmin = 0;
				 strengthmax = 0;
				 break;

			 case ATTACK_FLAME:
				 damtype |= WOUND_BURNED;
				 break;

			 case ATTACK_SUCK:
				 damtype |= WOUND_CUT;
				 break;

			 default:
				 damtype |= WOUND_TORN;
				 break;
			 }
			 severtype = WOUND_NASTYOFF;
		 }
	 }
	 else
	 {
		 damtype |= consolidateDamageTypes(attackI.attack_used);
		 strengthmin = attackI.attack_used.strength_min;
		 strengthmax = attackI.attack_used.strength_max;
		 severtype = attackI.attack_used.severtype;
		 int random = attackI.attack_used.random_damage;
		 int fixed = attackI.attack_used.fixed_damage;
		 if (attackI.sneak_attack) fixed += 100;
		 if (numhits >= attackI.attack_used.critical.hits_required
			 && LCSrandom(100) < attackI.attack_used.critical.chance)
		 {
			 defineIfDefined(attackI.attack_used, random, fixed, severtype);
		 }
		 for (int i = numhits; i > 0; i--)
		 {
			 damamount += LCSrandom(random) + fixed;
		 }
		 damagearmor = attackI.attack_used.damages_armor;
		 armorpiercing = attackI.attack_used.armorpiercing;
	 }
	 // Coarse combat lethality reduction.
	 //damamount/=2;
	 if (t.squadid != -1 && t.hireid == -1) // Plot Armor: if the founder is hit, inflict
		 damamount /= 2;                // 1/2 damage, because founders are cool
	 int mod = 0;
	 if (strengthmax > strengthmin)
	 {
		 // Melee attacks: Maximum strength bonus, minimum
		 // strength to deliver full damage
		 int strength = a.attribute_roll(ATTRIBUTE_STRENGTH);
		 if (strength > strengthmax) strength = (strengthmax + strength) / 2;
		 mod += strength - strengthmin;
		 armorpiercing += (strength - strengthmin) / 4;
	 }
	 //SKILL BONUS FOR GOOD ROLL
	 mod += attackI.aroll - attackI.droll;
	 //DO THE HEALTH MOD ON THE WOUND
	 mod -= t.attribute_roll(ATTRIBUTE_HEALTH);
	 //Health and poor accuracy will only avoid critical hits, not stop low-damage attacks
	 if (mod < 0) mod = 0;
	 // In a car chase, the vehicle itself provides bonus armor
	 int vehicleHitLocation = 0;
	 Vehicle* vehicle = getChaseVehicle(t);
	 if (mode == GAMEMODE_CHASECAR && vehicle != NULL)
	 {
		 vehicleHitLocation = vehicle->gethitlocation(hit_location);
		 extraarmor = vehicle->armorbonus(vehicleHitLocation);
		 // TODO damage vehicle itself
	 }
	 int cardmg = damamount;
	 {
		 updateDamageExcludingCar(t, damtype, damamount, damageDetails(mod, hit_location, extraarmor, armorpiercing));
	 }

	 string str;
	 if ((damamount == 0) && (mode == GAMEMODE_CHASECAR && vehicle != NULL && extraarmor > 0))
	 {

		 if ((t.getCreatureHealth().animalgloss == ANIMALGLOSS_TANK)) {
			 cardmg = couldTankHaveBlockedAttack(mod, damtype,
				 armorpiercing, cardmg);
		 }
		 else {
			 int armor = t.get_armor().get_armor(hit_location);
			 //if(t.get_armor().get_quality()>1)
			 armor -= t.get_armor().get_quality() - 1;
			 if (t.get_armor().is_damaged())
				 armor -= 1;
			 if (armor < 0) armor = 0; // Possible from second-rate clothes
			 armor += extraarmor; // Add vehicle armor 

			 cardmg = couldVehicleHaveBlockedAttack(mod, armor, damtype,
				 armorpiercing, cardmg);
		 }
		 if (cardmg < 2) //fudge factor of 1 armor level due to randomness
		 {
			 str = bouncesOffCar(vehicle, vehicleHitLocation);
		 }
	 }

	 if (len(str) < 1) {
		 str = a.heshe(true); // capitalize=true. Shorten the string so it doesn't spill over as much; we already said attacker's name on the previous line anyways.
		 if (attackI.sneak_attack) str += CONST_X_STABS_;
		 else str += CONST_HITS;
		 str += t.getNameAndAlignment().name;
		 str += CONST_X_S_SPACE;
		 str += bodypartName((Bodyparts)hit_location, (AnimalGlosses)t.getCreatureHealth().animalgloss);
		 str += showMultipleHits(a, numhits, attackI.attack_used);
		 // Report vehicle protection effect
		 if (mode == GAMEMODE_CHASECAR && vehicle != NULL && extraarmor > 0)
		 {
			 str += CONST_THROUGH;

			 str += (CONST_THE + vehicle->shortname() + CONST_X_S_SPACE);
			 str += vehicle->getpartname(vehicleHitLocation);
		 }
	 }

	 // Bullets caught by armor should bruise instead of poke holes.
	 if (damamount < 4 && damtype & WOUND_SHOT)
	 {
		 damtype &= ~(WOUND_SHOT | WOUND_BLEEDING);
		 damtype |= WOUND_BRUISED;
	 }
	 if (damamount > 0)
	 {
		 inflictNonZeroDamage(attackI,
			 a,
			 str,
			 AttackSeverity(damamount, damagearmor, severtype, hit_location),
			 damtype,
			 t);

	 }
	 else
	 {
		 set_color_easy(YELLOW_ON_BLACK_BRIGHT);
		 str += CONST_TO_NO_EFFECT;
		 mvaddstrAlt(17, 1, str, gamelog);
		 gamelog.newline();
		 printparty();
		 if (mode == GAMEMODE_CHASECAR ||
			 mode == GAMEMODE_CHASEFOOT) printchaseencounter();
		 else printencounter();
		 pressAnyKey();
	 }
 }
 void directlyUseWeapon(DeprecatedCreature &a, int &num_attacks, int &thrownweapons, int &bursthits, const attackst attack_used) {


	 if (mode == GAMEMODE_SITE && LCSrandom(100) < attack_used.fire.chance_causes_debris)
	 {// TODO - In a car chase, debris should make driving harder for one round, or require a drive skill check to avoid damage
		 sitechangest change(loc_coord.locx, loc_coord.locy, loc_coord.locz, SITEBLOCK_DEBRIS);
		 addLocationChange(getCurrentSite(), change);//  location[cursite]->changes.push_back(change);
	 }
	 if (mode == GAMEMODE_SITE && LCSrandom(100) < attack_used.fire.chance)
	 {// TODO - In a car chase, apply vehicle damage, with drive skill check to partially mitigate
	  // Fire!
		 if (!(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_END) ||
			 !(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_PEAK) ||
			 !(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_START) ||
			 !(levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_DEBRIS))
		 {
			 levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag |= SITEBLOCK_FIRE_START;
			 sitecrime += 3;
			 addjuice(a, 5, 500);
			 criminalizeparty(LAWFLAG_ARSON);
			 sitestory->crime.push_back(CRIME_ARSON);
		 }
	 }

	 if (attack_used.thrown)
	 {
		 thrownweapons = num_attacks;
		 if (thrownweapons > a.count_weapons()) {
			 thrownweapons = a.count_weapons();
			 num_attacks = thrownweapons;
		 }
	 }
	 else
		 if (attack_used.uses_ammo) {
			 if (a.get_weapon().get_ammoamount() < num_attacks) {
				 num_attacks = a.get_weapon().get_ammoamount();
			 }
			 a.get_weapon().decrease_ammo(num_attacks);
		 }

 }
 string firstStrike(const DeprecatedCreature a, const DeprecatedCreature t, const char mistake, const bool sneak_attack, const attackst attack_used) {
	 string str = a.getNameAndAlignment().name;

	 str += singleSpace;
	 if (mistake) { str += CONST_MISTAKENLY; }
	 str += initiateCombat(a, sneak_attack, attack_used);
	 str += singleSpace;
	 str += t.getNameAndAlignment().name;

	 if (a.is_armed() && !attack_used.thrown)
	 {
		 str += CONST_WITH_A;
		 str += a.get_weapon().get_name(1);
	 }

	 str += CONST_EXCLAMATION_POINT;
	 return str;
 }
 int driverAttackBonus(const DeprecatedCreature a) {

	 DeprecatedCreature* adriver = getChaseDriver(a);
	 Vehicle* avehicle = getChaseVehicle(a);

	 if (adriver != NULL && avehicle != NULL)
	 {
		 return avehicle->attackbonus(adriver->id == a.id);  // Attack bonus depends on attacker's car and whether attacker is distracted by driving.
	 }
	 else // shouldn't happen
	 {
		 return -10; // You're on the wrong side of a drive-by shooting?!
	 }

 }

 bool attackPoolEncounter(const int p, const int t, const char mistake, const bool force_melee) {
	 return attack(*pool[p], encounter[t], mistake, force_melee);
 }

/* attack handling for an individual creature and its target */
bool attack(DeprecatedCreature &a, DeprecatedCreature &t, const char mistake, const bool force_melee)
{

	clearmessagearea(true);  // erase the whole length and redraw map if applicable, since previous combat messages can be wider than 53 chars.
	if (goodguyattack) set_color_easy(GREEN_ON_BLACK_BRIGHT);
	else set_color_easy(RED_ON_BLACK_BRIGHT);

	const attackst* attack_used = a.get_weapon().get_attack(mode == GAMEMODE_CHASECAR,          //Force ranged if in a car.
		force_melee,
		(force_melee || !a.can_reload())); //No reload if force melee or unable to reload.
	if (attemptIncapacitated(a) || attemptSpecialAttack(a, t, force_melee) || attemptReload(a, force_melee) || attack_used == NULL) {
		// All exit points consolidated here, except the final one.
		// These four conditions, in order, determine the attacker is not capable of attacking using the standard attack()
		// It relies on lazy conditional OR, since each condition has side effects.
		return false;
	}

	// for tanks, attack_used->ranged returns false, so we need to check if it's a tank
	bool melee = !attack_used->ranged && !(!a.is_armed() && a.getCreatureHealth().animalgloss && a.specialattack == ATTACK_CANNON);

	bool sneak_attack = a.is_armed() && (attack_used->can_backstab && a.getCreatureHealth().align == ALIGN_LIBERAL && !mistake) && (t.is_cantbluff_zero() && !isThereASiteAlarm());

	if (sneak_attack)
	{
		if (sitealarmtimer > 10 || sitealarmtimer < 0) {
			sitealarmtimer = 10;
		}
		t.make_cantbluff_two();
	}

	mvaddstrAlt(16, 1, firstStrike(a, t, mistake, sneak_attack, *attack_used), gamelog);

	gamelog.newline();
	pressAnyKey();
	if (goodguyattack) set_color_easy(GREEN_ON_BLACK_BRIGHT);
	else set_color_easy(RED_ON_BLACK_BRIGHT);

	int bonus = 0; // Accuracy bonus or penalty that does NOT affect damage or counterattack chance
				   //SKILL EFFECTS
	const int wsk = attack_used->skill;

	// Basic roll
	int aroll = a.skill_roll(wsk);
	// In a car chase, the driver provides the defence roll instead of the victim.
	int droll;
	if (mode != GAMEMODE_CHASECAR)
	{
		droll = t.skill_roll(SKILL_DODGE) / 2;
	}
	else
	{

		DeprecatedCreature* driver = getChaseDriver(t);
		Vehicle* vehicle = getChaseVehicle(t);

		if (driver != NULL && vehicle != NULL)
		{  // without a vehicle or driver, you get a zero roll.
			droll = driver->skill_roll(PSEUDOSKILL_DODGEDRIVE);
		}
		else {
			droll = 0;
		}

		DeprecatedCreature* adriver = getChaseDriver(a);
		Vehicle* avehicle = getChaseVehicle(a);

		if (adriver != NULL && avehicle != NULL)
		{
			bonus += avehicle->attackbonus(adriver->id == a.id);  // Attack bonus depends on attacker's car and whether attacker is distracted by driving.
		}
		else // shouldn't happen
		{
			bonus += -10; // You're on the wrong side of a drive-by shooting?!
		}
	}
	if (sneak_attack)
	{
		droll = t.attribute_roll(ATTRIBUTE_WISDOM) / 2;
		aroll += a.skill_roll(SKILL_STEALTH);
		a.train(wsk, 10);
	}
	else
	{
		DeprecatedCreature* driver = getChaseDriver(t);

		if (driver != NULL)
			driver->train(SKILL_DRIVING, aroll / 2);
		else
			t.train(SKILL_DODGE, aroll * 2);
		a.train(wsk, droll * 2 + 5);
	}
	// Hostages interfere with attack
	if (t.is_holding_body()) bonus -= LCSrandom(10);
	if (a.is_holding_body()) aroll -= LCSrandom(10);
	//Injured people suck at attacking, are like fish in a barrel to attackers
	if (mode == GAMEMODE_CHASEFOOT)
	{
		// If in a foot chase, double the debilitating effect of injuries
		healthmodroll(aroll, a);
		healthmodroll(droll, t);
		healthmodroll(droll, t);
	}
	else if (mode == GAMEMODE_CHASECAR)
	{
		// In a car chase, the driver is applying dodge rolls even for crippled people.
		healthmodroll(aroll, a);
		DeprecatedCreature* driver = getChaseDriver(t);

		if (driver != NULL)
		{// if there is no driver, we already rolled a zero, so don't worry about further penalties.
			healthmodroll(droll, *driver);
		}
	}
	else
	{
		// Any other case (site fight) normal penalties.
		healthmodroll(aroll, a);
		healthmodroll(droll, t);
	}
	AttackInfliction attackI(sneak_attack, aroll, droll, *attack_used);
	// Weapon accuracy bonuses and penalties
	bonus += attack_used->accuracy_bonus;
	//USE BULLETS
	int bursthits = 0; // Tracks number of hits.
	int thrownweapons = 0; // Used by thrown weapons to remove the weapons at the end of the turn if needed
	if (!a.is_armed()) //Move into WEAPON_NONE -XML
	{
		// Martial arts multi-strikes
		bursthits = 1 + LCSrandom(a.get_skill(SKILL_HANDTOHAND) / 3 + 1);
		if (bursthits > 5) bursthits = 5;
		if (a.getCreatureHealth().animalgloss) bursthits = 1; // Whoops, must be human to use martial arts fanciness
	}
	else
	{
		int num_attacks = attack_used->number_attacks;
		if (sneak_attack) {
			num_attacks = 1;
			bursthits = 1;
		}
		directlyUseWeapon(a, num_attacks, thrownweapons, bursthits, *attack_used);
		if (!sneak_attack) {
			for (int i = 0; i < num_attacks; i++)
			{
				// Each shot in a burst is increasingly less likely to hit
				if (aroll + bonus - i * attack_used->successive_attacks_difficulty > droll)
					bursthits++;
			}
		}
	}
	//HIT!
	if (aroll + bonus > droll)
	{
		inflictDamage(bursthits, a, t, attackI);
	}
	else
	{
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		if (melee && aroll < droll - 10 && t.getCreatureHealth().blood>70 && t.getCreatureHealth().animalgloss == ANIMALGLOSS_NONE
			&& t.is_armed() && t.get_weapon().get_attack(false, true, true) != NULL)
		{
			string str2 = t.getNameAndAlignment().name;
			str2 += CONST_KNOCKS_THE_BLOW_ASIDE_AND_COUNTERS;
			mvaddstrAlt(17, 1, str2, gamelog);
			gamelog.newline();
			pressAnyKey();
			goodguyattack = !goodguyattack;
			attack(t, a, 0, true);
			goodguyattack = !goodguyattack;
		}//TODO if missed person, but vehicle is large, it might damage the car. 
		else {
			string str2;
			if (sneak_attack)
			{
				str2 = t.getNameAndAlignment().name;
				str2 += singleSpace + pickrandom(cry_alarm);
				setSiteAlarmOne();
			}
			else {
				str2 += unsuccessfulHit(a, t, droll);

			}
			mvaddstrAlt(17, 1, str2, gamelog);

			gamelog.newline();
			printparty();
			if (mode == GAMEMODE_CHASECAR ||
				mode == GAMEMODE_CHASEFOOT) printchaseencounter();
			else printencounter();
			pressAnyKey();



		}
	}
	for (; thrownweapons > 0; thrownweapons--)
	{
		if (a.has_thrown_weapon)
			a.ready_another_throwing_weapon();
		a.drop_weapon(NULL);
	}
	// This is the only point in the function that returns true
	return true;
}
void singleSquadMemberAttack(const int p, const bool wasalarm) {
	vector<int> super_enemies;
	vector<int> dangerous_enemies;
	vector<int> enemies;
	vector<int> non_enemies;
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].getCreatureHealth().alive&&encounter[e].getNameAndAlignment().exists)
		{
			if (encounter[e].enemy())
			{
				if (encounter[e].getCreatureHealth().animalgloss == ANIMALGLOSS_TANK &&
					!encounter[e].is_stunned())
					super_enemies.push_back(e);
				else if ((encounter[e].is_armed() ||
					(encounter[e].type == CREATURE_COP && encounter[e].getCreatureHealth().align == ALIGN_MODERATE) ||
					encounter[e].type == CREATURE_SCIENTIST_EMINENT ||
					encounter[e].type == CREATURE_JUDGE_LIBERAL ||
					encounter[e].type == CREATURE_JUDGE_CONSERVATIVE ||
					encounter[e].type == CREATURE_CORPORATE_CEO ||
					encounter[e].type == CREATURE_POLITICIAN ||
					encounter[e].type == CREATURE_RADIOPERSONALITY ||
					encounter[e].type == CREATURE_NEWSANCHOR ||
					encounter[e].type == CREATURE_MILITARYOFFICER ||
					encounter[e].specialattack != -1) &&
					encounter[e].getCreatureHealth().blood >= 40 &&
					!encounter[e].is_stunned())
					dangerous_enemies.push_back(e);
				else enemies.push_back(e);
			}
			else non_enemies.push_back(e);
		}
	}
	if (!(len(super_enemies) + len(dangerous_enemies) + len(enemies))) return;
	int target;
	// If there are super enemies, shoot at one of them unless we're using a persuasion-based attack
	if (len(super_enemies) &&
		((activesquad->squad[p]->type != CREATURE_SCIENTIST_EMINENT &&
			activesquad->squad[p]->type != CREATURE_JUDGE_LIBERAL &&
			activesquad->squad[p]->type != CREATURE_JUDGE_CONSERVATIVE &&
			activesquad->squad[p]->type != CREATURE_CORPORATE_CEO &&
			activesquad->squad[p]->type != CREATURE_POLITICIAN &&
			activesquad->squad[p]->type != CREATURE_RADIOPERSONALITY &&
			activesquad->squad[p]->type != CREATURE_NEWSANCHOR &&
			activesquad->squad[p]->type != CREATURE_MILITARYOFFICER &&
			!activesquad->squad[p]->get_weapon().get_specific_bool(BOOL_MUSICAL_ATTACK_)) ||
			(!activesquad->squad[p]->get_weapon().get_specific_bool(BOOL_MUSICAL_ATTACK_) &&
				activesquad->squad[p]->is_armed())))
		target = pickrandom(super_enemies);
	// Else, if there are dangerous enemies, shoot at one of them
	else if (len(dangerous_enemies))
		target = pickrandom(dangerous_enemies);
	// Else, if there are regular enemies, shoot at one of them
	else if (len(enemies)) target = pickrandom(enemies);
	// Else, we skipped a super enemy because it we're using a persuasion-based attack but it's the only enemy left so we have to pick it
	else target = pickrandom(super_enemies);
	char mistake = 0;
	// Mistaken attack
	/*
	Mistakenly attacking innocents: if skill is 8 or higher, there is no chance of mistakenly hitting innocents (except when used as a human shield).
	If skill is 7 or lower, the odds are based on skill, with a maximum of 10% chance at skill = 0;
	Melee weapons only require a skill of 4.
	If skill is 3 or lower, the odds are based on skill, with a maximum of 5% chance at skill = 0;
	*/
	if (len(non_enemies) && activesquad->squad[p]->get_weapon_skill() < (4 + (activesquad->squad[p]->get_weapon().is_ranged() * 4)) &&
		!LCSrandom(10 + 2 * (5 + 5 * activesquad->squad[p]->get_weapon().is_ranged()) * activesquad->squad[p]->get_weapon_skill()))
		// Mistaken attack
	{
		target = pickrandom(non_enemies);
		mistake = 1;
	}
	bool actual;
	const short beforeblood = encounter[target].getCreatureHealth().blood;
	if (encounter[target].getCreatureHealth().align == 1) mistake = 1;
	actual = attack(*activesquad->squad[p], encounter[target], mistake);
	if (actual)
	{
		if (mistake)
		{
			alienationcheck(mistake);
			sitestory->crime.push_back(CRIME_ATTACKED_MISTAKE);
			sitecrime += 10;
		}
		else
		{
			sitecrime += 3;
			addjuice(*(activesquad->squad[p]), 1, 200);
		}
		sitestory->crime.push_back(CRIME_ATTACKED);
		// Charge with assault if first strike
		if (isThereASiteAlarm() && (!wasalarm || (beforeblood > encounter[target].getCreatureHealth().blood && beforeblood == 100)))
		{
			if (!activesquad->squad[p]->is_armed())
				criminalize(*activesquad->squad[p], LAWFLAG_ASSAULT);
			else criminalize(*activesquad->squad[p], LAWFLAG_ARMEDASSAULT);
		}
	}
	if (!encounter[target].getCreatureHealth().alive)
	{
		delenc(target, 1);
		if (!mistake)
		{
			for (int p = 0; p < 6; p++)
			{
				if (activesquad->squad[p] == NULL) continue;
				if (!activesquad->squad[p]->getCreatureHealth().alive) continue;
				addjuice(*(activesquad->squad[p]), 5, 500);
			}
		}
	}
}

void yourinitialattack() {
	const bool wasalarm = isThereASiteAlarm();
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL) continue;
		if (!activesquad->squad[p]->getCreatureHealth().alive) continue;
		singleSquadMemberAttack(p, wasalarm);
	}
}

/* attack handling for each side as a whole */
void youattack()
{
	foughtthisround = 1;
	goodguyattack = true;
	yourinitialattack();
	vector<NameAndAlignment> encounter = getEncounterNameAndAlignment();
	for (int e = 0; e < ENCMAX; e++)
	{
		if (encounter[e].exists && encounter[e].alive && encounter[e].enemy)
		{
			setSiteAlarmOne();
			break;
		}
	}
	//COVER FIRE
	if (LocationsPool::getInstance().isThereASiegeHere(getCurrentSite()))
	{
		for (int p = 0; p < CreaturePool::getInstance().lenpool(); p++)
		{
			if (!pool[p]->getCreatureHealth().alive) continue;
			if (pool[p]->getCreatureHealth().align != 1) continue;
			if (pool[p]->squadid != -1) continue;
			if (pool[p]->location != getCurrentSite()) continue;
			// Juice check to engage in cover fire
			// 10% chance for every 10 juice, starting at
			// 10% chance for 0 juice -- caps out at 100%
			// chance to fire at 90 juice
			//if(LCSrandom(10)-pool[p]->juice/10>0)continue;
			if (pool[p]->get_weapon().get_attack(true, false, false))
			{
				char conf = 0;
				if (pool[p]->get_weapon().get_ammoamount() > 0) conf = 1;
				if (pool[p]->get_weapon().get_attack(true, false, false)->uses_ammo)
					if (pool[p]->can_reload()) conf = 1;
				if (conf)
				{
					vector<int> goodtarg, badtarg;
					for (int e = 0; e < ENCMAX; e++)
					{
						if (encounter[e].alive&&encounter[e].exists)
						{
							if (encounter[e].enemy)goodtarg.push_back(e);
							else badtarg.push_back(e);
						}
					}
					if (!len(goodtarg)) return;
					int target = pickrandom(goodtarg);
					char mistake = 0;
					// Mistaken attack
					/*
					Mistakenly attacking innocents: if skill is 8 or higher, there is no chance of mistakenly hitting innocents (except when used as a human shield).
					If skill is 7 or lower, the odds are based on skill, with a maximum of 10% chance at skill = 0;
					Melee weapons only require a skill of 4.
					If skill is 3 or lower, the odds are based on skill, with a maximum of 5% chance at skill = 0;
					*/
					if (len(badtarg) && pool[p]->get_weapon_skill() < (4 + (pool[p]->get_weapon().is_ranged() * 4)) &&
						!LCSrandom(10 + 2 * (5 + 5 * pool[p]->get_weapon().is_ranged()) * pool[p]->get_weapon_skill()))
					{
						target = pickrandom(badtarg);
						mistake = 1;
					}
					bool actual;
					actual = attackPoolEncounter(p, target, mistake);
					if (actual)
					{
						if (mistake)
						{
							alienationcheck(mistake);
							sitestory->crime.push_back(CRIME_ATTACKED_MISTAKE);
							sitecrime += 10;
						}
						if (!pool[p]->is_armed())
							criminalize(*pool[p], LAWFLAG_ASSAULT);
						else criminalize(*pool[p], LAWFLAG_ARMEDASSAULT);
					}
					if (!encounter[target].alive) delenc(target, 1);
				}
			}
		}
	}
}
// RETURN_ONE - special meaning, additional conditionals
// RETURN_ZERO - break surrounding loop
LOOP_CONTINUATION singleEnemyAttack(const int e, const bool armed) {


	if (!encounter[e].getNameAndAlignment().exists) return REPEAT;
	if (!encounter[e].getCreatureHealth().alive) return REPEAT;
	if (isThereASiteAlarm() && encounter[e].type == CREATURE_BOUNCER && encounter[e].getCreatureHealth().align != ALIGN_LIBERAL)
		conservatise(e);
	if (encounter[e].enemy()) encounter[e].make_cantbluff_two();

	if (mode != GAMEMODE_CHASECAR)
	{
		// Encountered creature will flee if:
		// (a) Non-Conservative, and not recently converted via music or some other mechanism
		// (b) Conservative, no juice, unarmed, non-tank/animal, enemy is armed, and fails a morale check based in part on injury level
		// (c) Conservative, and lost more than 55% blood
		// (d) There's a fire, they are not firefighters, and they fail a random check
		// Encountered creatures will never flee if they are tanks, animals, or so hurt they can't move
		char fire = 0;
		if (mode == GAMEMODE_SITE)
		{
			if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_START ||
				levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_END)
				fire = 1;
			else if (levelmap[loc_coord.locx][loc_coord.locy][loc_coord.locz].flag & SITEBLOCK_FIRE_PEAK)
				fire = 2;
		}
		if (((!encounter[e].enemy() ||
			(encounter[e].juice == 0 && !encounter[e].is_armed() && armed&&encounter[e].getCreatureHealth().blood<signed(70 + LCSrandom(61))))
			&& !(encounter[e].flag & CREATUREFLAG_CONVERTED)) || (encounter[e].getCreatureHealth().blood < 45 && encounter[e].juice < 200)
			|| ((fire*LCSrandom(5) >= 3) && !(encounter[e].type == CREATURE_FIREFIGHTER)))
		{
			if (encounter[e].getCreatureHealth().animalgloss == ANIMALGLOSS_NONE)
			{

				return RETURN_ONE;
			}
		}
	}

	vector<int> goodtarg, badtarg;
	if (encounter[e].enemy())
	{
		for (int p = 0; p < 6; p++) {
			if (activesquad->squad[p] != NULL) {
				if (activesquad->squad[p]->getCreatureHealth().alive) { goodtarg.push_back(p); }
			}
		}
	}
	else
	{
		for (int e2 = 0; e2 < ENCMAX; e2++)
		{
			if (!encounter[e2].getNameAndAlignment().exists) continue;
			if (!encounter[e2].getCreatureHealth().alive) continue;
			if (encounter[e2].getCreatureHealth().align != -1) continue;
			goodtarg.push_back(e2);
		}
	}
	for (int e2 = 0; e2 < ENCMAX; e2++)
	{
		if (!encounter[e2].getNameAndAlignment().exists) continue;
		if (!encounter[e2].getCreatureHealth().alive) continue;
		if (encounter[e2].enemy()) continue;
		badtarg.push_back(e2);
	}
	if (!len(goodtarg)) return RETURN_ZERO;
	int target = pickrandom(goodtarg);
	char canmistake = 1;
	int encnum = 0;
	for (int e2 = 0; e2 < ENCMAX; e2++) if (encounter[e2].getNameAndAlignment().exists) encnum++;
	if ((encounter[e].type == CREATURE_SCIENTIST_EMINENT ||
		encounter[e].type == CREATURE_JUDGE_LIBERAL ||
		encounter[e].type == CREATURE_JUDGE_CONSERVATIVE ||
		encounter[e].type == CREATURE_CORPORATE_CEO ||
		encounter[e].type == CREATURE_POLITICIAN ||
		encounter[e].type == CREATURE_RADIOPERSONALITY ||
		encounter[e].type == CREATURE_NEWSANCHOR ||
		encounter[e].type == CREATURE_MILITARYOFFICER) && encnum < ENCMAX) canmistake = 0;
	bool actual;
	if (canmistake)
	{
		if (encounter[e].enemy())
		{
			if (activesquad->squad[target]->is_holding_body() && !LCSrandom(2))
			{
				// Mistaken attack
				actual = activesquad->squad[target]->human_shield_attacked(encounter[e]);
				if (!activesquad->squad[target]->is_prisoner_alive())
				{
					if (activesquad->squad[target]->is_prisoner_non_LCS())
					{
						clearmessagearea();
						set_color_easy(WHITE_ON_BLACK_BRIGHT);
						mvaddstrAlt(16, 1, activesquad->squad[target]->getNameAndAlignment().name, gamelog);
						addstrAlt(CONST_DROPS, gamelog);
						addstrAlt(activesquad->squad[target]->get_prisoner_name(), gamelog);
						addstrAlt(CONST_S_BODY, gamelog);
						gamelog.newline();
						const int prisonerType = activesquad->squad[target]->get_prisoner_type();
						if (prisonerType == CREATURE_CORPORATE_CEO ||
							prisonerType == CREATURE_POLITICIAN ||
							prisonerType == CREATURE_RADIOPERSONALITY ||
							prisonerType == CREATURE_NEWSANCHOR ||
							prisonerType == CREATURE_SCIENTIST_EMINENT ||
							prisonerType == CREATURE_JUDGE_CONSERVATIVE ||
							prisonerType == CREATURE_MILITARYOFFICER) 
						{
							sitecrime += 30;
						}
						activesquad->squad[target]->make_prisoner_ground_loot();
						pressAnyKey();
						activesquad->squad[target]->delete_and_nullify_prisoner();
					}
				}
				return REPEAT;
			}
		}
		// Mistaken attack
		/*
		Mistakenly attacking innocents: if skill is 8 or higher, there is no chance of mistakenly hitting innocents (except when used as a human shield).
		If skill is 7 or lower, the odds are based on skill, with a maximum of 20% chance at skill = 0;
		Melee weapons only require a skill of 4.
		If skill is 3 or lower, the odds are based on skill, with a maximum of 10% chance at skill = 0;
		*/
		if (len(badtarg) && encounter[e].get_weapon_skill() < (4 + (encounter[e].get_weapon().is_ranged() * 4)) &&
			!LCSrandom(10 + 2 * (5 + 5 * encounter[e].get_weapon().is_ranged()) * encounter[e].get_weapon_skill()))
		{
			target = pickrandom(badtarg);
			if (encounter[target].flag & CREATUREFLAG_CONVERTED)
				actual = attack(encounter[e], encounter[target], 0);
			// Mistaken Attack
			else actual = attack(encounter[e], encounter[target], 1);
			if (!encounter[target].getCreatureHealth().alive) delenc(target, 1);
			return REPEAT;
		}
	}
	if (encounter[e].enemy())
		actual = attack(encounter[e], *activesquad->squad[target], 0);
	else actual = attack(encounter[e], encounter[target], 0);
	return REPEAT;
}
void enemyattack()
{

	foughtthisround = 1;
	goodguyattack = false;
	bool armed = false;
	for (int i = 0; i < 6; i++)
	{
		if (activesquad->squad[i] == NULL) break;
		if (activesquad->squad[i]->is_armed()) armed = true;
	}
	if (NOENEMYATTACK) {
		return;
	}
	char printed;
	for (int e = 0; e < ENCMAX; e++)
	{
		switch (singleEnemyAttack(e, armed)) {
		case RETURN_ONE:
			if (!incapacitated(encounter[e], 0, printed))
			{
				if (printed)
				{
					printparty();
					if (mode == GAMEMODE_CHASECAR ||
						mode == GAMEMODE_CHASEFOOT) printchaseencounter();
					else printencounter();
					pressAnyKey();
				}
				clearmessagearea();
				mvaddstrAlt(16, 1, encounter[e].getNameAndAlignment().name, gamelog);
				if ((encounter[e].getCreatureHealth().wound[BODYPART_LEG_RIGHT] & WOUND_NASTYOFF) ||
					(encounter[e].getCreatureHealth().wound[BODYPART_LEG_RIGHT] & WOUND_CLEANOFF) ||
					(encounter[e].getCreatureHealth().wound[BODYPART_LEG_LEFT] & WOUND_NASTYOFF) ||
					(encounter[e].getCreatureHealth().wound[BODYPART_LEG_LEFT] & WOUND_CLEANOFF) ||
					(encounter[e].getCreatureHealth().blood < 45))
					addstrAlt(pickrandom(escape_crawling), gamelog);
				else addstrAlt(pickrandom(escape_running), gamelog);
				gamelog.newline();
				delenc(e, 0);
				e--;
				printparty();
				if (mode == GAMEMODE_CHASECAR ||
					mode == GAMEMODE_CHASEFOOT) printchaseencounter();
				else printencounter();
				pressAnyKey();
			}
			break;
		case RETURN_ZERO:
			return;
		}
	}
}
string damtypeToUpperSpineString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT) damageDescription += (CONST_S_UPPER_SPINE_IS_SHATTERED);
	else (damageDescription += CONST_S_UPPER_SPINE_IS_BROKEN);

	return damageDescription;
}
string damtypeToLowerSpineString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += CONST_S_LOWER_SPINE_IS_SHATTERED;
	else damageDescription += (CONST_S_LOWER_SPINE_IS_BROKEN);

	return damageDescription;
}
string damtypeToRightLungString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_RIGHT_LUNG_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_RIGHT_LUNG_IS_TORN);
	else damageDescription += (CONST_S_RIGHT_LUNG_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToLeftLungString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_LEFT_LUNG_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_LEFT_LUNG_IS_TORN);
	else damageDescription += (CONST_S_LEFT_LUNG_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToHeartString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_HEART_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_HEART_IS_TORN);
	else damageDescription += (CONST_S_HEART_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToLiverString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_LIVER_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_LIVER_IS_TORN);
	else damageDescription += (CONST_S_LIVER_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToStomachString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_STOMACH_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_STOMACH_IS_TORN);
	else damageDescription += (CONST_S_STOMACH_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToRightKidneyString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_RIGHT_KIDNEY_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_RIGHT_KIDNEY_IS_TORN);
	else damageDescription += (CONST_S_RIGHT_KIDNEY_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToLeftKidneyString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_LEFT_KIDNEY_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_LEFT_KIDNEY_IS_TORN);
	else damageDescription += (CONST_S_LEFT_KIDNEY_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToSpleenString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_SPLEEN_IS_BLASTED);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_SPLEEN_IS_TORN);
	else damageDescription += (CONST_S_SPLEEN_IS_PUNCTURED);

	return damageDescription;
}
string damtypeToRibsString(const char damtype, const char ribminus, const int ribsleft, const string name) {
	string damageDescription;
	if (ribminus > 1)
	{
		if (ribminus == ribsleft)
			damageDescription += (CONST_ALL);
		damageDescription += (name);
		damageDescription += (CONST_OF);
		damageDescription += (name);
		damageDescription += (CONST_S_RIBS_ARE);
	}
	else if (ribsleft > 1)
	{
		damageDescription += (CONST_ONE_OF);
		damageDescription += (name);
		damageDescription += (CONST_S_RIB_IS);
	}
	else
	{
		damageDescription += (name);
		damageDescription += (CONST_S_LAST_UNBROKEN_RIB_IS);
	}
	if (damtype & WOUND_SHOT)damageDescription += (CONST_SHOT_APART);
	else damageDescription += (CONST_BROKEN);
	return damageDescription;
}
//std::string bodypartName(Bodyparts w, AnimalGlosses t);
string specialWoundPossibilityBody(
	DeprecatedCreature &t,
	const char breakdam,
	const char pokedam,
	const char damtype)
{
	DeprecatedCreature* target = &t;
	string damageDescription = "";
	switch (LCSrandom(11))
	{
	case 0:
		if (target->getCreatureHealth().special[SPECIALWOUND_UPPERSPINE] && breakdam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToUpperSpineString(damtype);
			target->set_special_wound(SPECIALWOUND_UPPERSPINE, 0);
			if (target->getCreatureHealth().blood > 20) target->set_blood(20);
		}
		break;
	case 1:
		if (target->getCreatureHealth().special[SPECIALWOUND_LOWERSPINE] && breakdam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToLowerSpineString(damtype);
			target->set_special_wound(SPECIALWOUND_LOWERSPINE, 0);
			if (target->getCreatureHealth().blood > 20) target->set_blood(20);
		}
		break;
	case 2:
		if (target->getCreatureHealth().special[SPECIALWOUND_RIGHTLUNG] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToRightLungString(damtype);
			target->set_special_wound(SPECIALWOUND_RIGHTLUNG, 0);
			if (target->getCreatureHealth().blood > 20) target->set_blood(20);
		}
		break;
	case 3:
		if (target->getCreatureHealth().special[SPECIALWOUND_LEFTLUNG] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToLeftLungString(damtype);
			target->set_special_wound(SPECIALWOUND_LEFTLUNG, 0);
			if (target->getCreatureHealth().blood > 20) target->set_blood(20);
		}
		break;
	case 4:
		if (target->getCreatureHealth().special[SPECIALWOUND_HEART] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToHeartString(damtype);
			target->set_special_wound(SPECIALWOUND_HEART, 0);
			if (target->getCreatureHealth().blood > 3) target->set_blood(3);
		}
		break;
	case 5:
		if (target->getCreatureHealth().special[SPECIALWOUND_LIVER] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToLiverString(damtype);
			target->set_special_wound(SPECIALWOUND_LIVER, 0);
			if (target->getCreatureHealth().blood > 50) target->set_blood(50);
		}
		break;
	case 6:
		if (target->getCreatureHealth().special[SPECIALWOUND_STOMACH] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToStomachString(damtype);
			target->set_special_wound(SPECIALWOUND_STOMACH, 0);
			if (target->getCreatureHealth().blood > 50) target->set_blood(50);
		}
		break;
	case 7:
		if (target->getCreatureHealth().special[SPECIALWOUND_RIGHTKIDNEY] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToRightKidneyString(damtype);
			target->set_special_wound(SPECIALWOUND_RIGHTKIDNEY, 0);
			if (target->getCreatureHealth().blood > 50) target->set_blood(50);
		}
		break;
	case 8:
		if (target->getCreatureHealth().special[SPECIALWOUND_LEFTKIDNEY] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToLeftKidneyString(damtype);
			target->set_special_wound(SPECIALWOUND_LEFTKIDNEY, 0);
			if (target->getCreatureHealth().blood > 50) target->set_blood(50);
		}
		break;
	case 9:
		if (target->getCreatureHealth().special[SPECIALWOUND_SPLEEN] && pokedam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToSpleenString(damtype);
			target->set_special_wound(SPECIALWOUND_SPLEEN, 0);
			if (target->getCreatureHealth().blood > 50) target->set_blood(50);
		}
		break;
	case 10:
		if (target->getCreatureHealth().special[SPECIALWOUND_RIBS] > 0 && breakdam)
		{
			int ribminus = LCSrandom(RIBNUM) + 1;
			if (ribminus > target->getCreatureHealth().special[SPECIALWOUND_RIBS]) ribminus = target->getCreatureHealth().special[SPECIALWOUND_RIBS];

			damageDescription += damtypeToRibsString(damtype, ribminus, target->getCreatureHealth().special[SPECIALWOUND_RIBS], target->getNameAndAlignment().name);

			target->set_special_wound(SPECIALWOUND_RIBS, target->getCreatureHealth().special[SPECIALWOUND_RIBS] - ribminus);
		}
		break;
	}
	return damageDescription;
}
string damtypeToTeethString(const char damtype, const int woundTeeth, const string name, const int teethminus) {
	string damageDescription;
	if (teethminus > 1)
	{
		if (teethminus == woundTeeth)
		{
			damageDescription += (CONST_ALL);
		}
		damageDescription += tostring(teethminus);
		damageDescription += CONST_OF;
		damageDescription += name;
		damageDescription += CONST_S_TEETH_ARE;
	}
	else if (woundTeeth > 1)
	{
		damageDescription += (CONST_ONE_OF);
		damageDescription += (name);
		damageDescription += (CONST_S_TEETH_IS);
	}
	else
	{
		damageDescription += (name);
		damageDescription += (CONST_S_LAST_TOOTH_IS);
	}
	if (damtype & WOUND_SHOT)damageDescription += (CONST_SHOT_OUT);
	else if (damtype & WOUND_BURNED)damageDescription += (CONST_BURNED_AWAY);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_GOUGED_OUT);
	else if (damtype & WOUND_CUT)damageDescription += (CONST_CUT_OUT);
	else damageDescription += (CONST_KNOCKED_OUT);
	return damageDescription;
}
string damtypeToFaceString(const char damtype) {
	string damageDescription;
	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_FACE_IS_BLASTED_OFF);
	else if (damtype & WOUND_BURNED)damageDescription += (CONST_S_FACE_IS_BURNED_AWAY);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_FACE_IS_TORN_OFF);
	else if (damtype & WOUND_CUT)damageDescription += (CONST_S_FACE_IS_CUT_AWAY);
	else damageDescription += (CONST_S_FACE_IS_REMOVED);
	return damageDescription;
}
string damtypeToRightEyeString(const char damtype) {
	string damageDescription;
	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_RIGHT_EYE_IS_BLASTED_OUT);
	else if (damtype & WOUND_BURNED)damageDescription += (CONST_S_RIGHT_EYE_IS_BURNED_AWAY);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_RIGHT_EYE_IS_TORN_OUT);
	else if (damtype & WOUND_CUT)damageDescription += (CONST_S_RIGHT_EYE_IS_POKED_OUT);
	else damageDescription += (CONST_S_RIGHT_EYE_IS_REMOVED);
	return damageDescription;
}
string damtypeToLeftEyeString(const char damtype) {
	string damageDescription;
	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_LEFT_EYE_IS_BLASTED_OUT);
	else if (damtype & WOUND_BURNED)damageDescription += (CONST_S_LEFT_EYE_IS_BURNED_AWAY);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_LEFT_EYE_IS_TORN_OUT);
	else if (damtype & WOUND_CUT)damageDescription += (CONST_S_LEFT_EYE_IS_POKED_OUT);
	else damageDescription += (CONST_S_LEFT_EYE_IS_REMOVED);
	return damageDescription;
}
string damtypeToTongueString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_TONGUE_IS_BLASTED_OFF);
	else if (damtype & WOUND_BURNED)damageDescription += (CONST_S_TONGUE_IS_BURNED_AWAY);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_TONGUE_IS_TORN_OUT);
	else if (damtype & WOUND_CUT)damageDescription += (CONST_S_TONGUE_IS_CUT_OFF);
	else damageDescription += (CONST_S_TONGUE_IS_REMOVED);

	return damageDescription;
}
string damtypeToNoseString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_NOSE_IS_BLASTED_OFF);
	else if (damtype & WOUND_BURNED)damageDescription += (CONST_S_NOSE_IS_BURNED_AWAY);
	else if (damtype & WOUND_TORN)damageDescription += (CONST_S_NOSE_IS_TORN_OFF);
	else if (damtype & WOUND_CUT)damageDescription += (CONST_S_NOSE_IS_CUT_OFF);
	else damageDescription += (CONST_S_NOSE_IS_REMOVED);

	return damageDescription;
}
string damtypeToNeckString(const char damtype) {
	string damageDescription;

	if (damtype & WOUND_SHOT)damageDescription += (CONST_S_NECK_BONES_ARE_SHATTERED);
	else damageDescription += (CONST_S_NECK_IS_BROKEN);

	return damageDescription;
}

string specialWoundPossibilityHead(
	DeprecatedCreature &t,
	const char breakdam,
	//char pokedam,
	const char heavydam,
	const char damtype
) {
	DeprecatedCreature* target = &t;
	string damageDescription = "";
	switch (LCSrandom(7))
	{

	case 0:
		if ((target->getCreatureHealth().special[SPECIALWOUND_RIGHTEYE] ||
			target->getCreatureHealth().special[SPECIALWOUND_LEFTEYE] ||
			target->getCreatureHealth().special[SPECIALWOUND_NOSE]) && heavydam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToFaceString(damtype);
			target->set_special_wound(SPECIALWOUND_RIGHTEYE, 0);
			target->set_special_wound(SPECIALWOUND_LEFTEYE, 0);
			target->set_special_wound(SPECIALWOUND_NOSE, 0);
			if (target->getCreatureHealth().blood > 20)target->set_blood(20);
		}
		break;
	case 1:
		if (target->getCreatureHealth().special[SPECIALWOUND_TEETH] > 0)
		{
			int teethminus = LCSrandom(TOOTHNUM) + 1;
			if (teethminus > target->getCreatureHealth().special[SPECIALWOUND_TEETH])
				teethminus = target->getCreatureHealth().special[SPECIALWOUND_TEETH];
			damageDescription += damtypeToTeethString(damtype, target->getCreatureHealth().special[SPECIALWOUND_TEETH], target->getNameAndAlignment().name, teethminus);
			target->set_special_wound(SPECIALWOUND_TEETH, target->getCreatureHealth().special[SPECIALWOUND_TEETH] - teethminus);
		}
		break;
	case 2:
		if (target->getCreatureHealth().special[SPECIALWOUND_RIGHTEYE] && heavydam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToRightEyeString(damtype);
			target->set_special_wound(SPECIALWOUND_RIGHTEYE, 0);
			if (target->getCreatureHealth().blood > 50)target->set_blood(50);
		}
		break;
	case 3:
		if (target->getCreatureHealth().special[SPECIALWOUND_LEFTEYE] && heavydam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToLeftEyeString(damtype);
			target->set_special_wound(SPECIALWOUND_LEFTEYE, 0);
			if (target->getCreatureHealth().blood > 50)target->set_blood(50);
		}
		break;
	case 4:
		if (target->getCreatureHealth().special[SPECIALWOUND_TONGUE] && heavydam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToTongueString(damtype);
			target->set_special_wound(SPECIALWOUND_TONGUE, 0);
			if (target->getCreatureHealth().blood > 50)target->set_blood(50);
		}
		break;
	case 5:
		if (target->getCreatureHealth().special[SPECIALWOUND_NOSE] && heavydam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToNoseString(damtype);
			target->set_special_wound(SPECIALWOUND_NOSE, 0);
			if (target->getCreatureHealth().blood > 50)target->set_blood(50);
		}
		break;
	case 6:
		if (target->getCreatureHealth().special[SPECIALWOUND_NECK] && breakdam)
		{
			damageDescription += (target->getNameAndAlignment().name);
			damageDescription += damtypeToNeckString(damtype);
			target->set_special_wound(SPECIALWOUND_NECK, 0);
			if (target->getCreatureHealth().blood > 20)target->set_blood(20);
		}
		break;
	}
	return damageDescription;
}
/* abandoned liberal is captured by conservatives */
void capturecreature(DeprecatedCreature &t)
{
	t.set_activity_type(ACTIVITY_NONE);
	t.drop_weapons_and_clips(NULL);
	Armor clothes = Armor(getarmortype(tag_ARMOR_CLOTHES));
	t.give_armor(clothes, NULL);
	freehostage(t, 2); // situation 2 = no message; this may want to be changed to 0 or 1
	if (t.is_holding_body())
	{
		if (t.is_prisoner_non_LCS())
			t.delete_prisoner();
		t.discard_body(); // Stop hauling people
	}
	if (t.flag & CREATUREFLAG_JUSTESCAPED)
	{
		t.location = getCurrentSite();
		if (sitetype == SITE_GOVERNMENT_PRISON ||
			sitetype == SITE_GOVERNMENT_COURTHOUSE)
		{
			Armor prisoner = Armor(getarmortype(tag_ARMOR_PRISONER));
			t.give_armor(prisoner, NULL);
		}
		if (sitetype == SITE_GOVERNMENT_PRISON)
		{
			t.clear_criminal_record();
		}
	}
	else
		t.location = find_site_index_in_same_city(SITE_GOVERNMENT_POLICESTATION, getCurrentSite());
	t.squadid = -1;
}
/* pushes people into the current squad (used in a siege) */
void autopromote(const int loc)
{
	if (!activesquad) return;
	const int partysize = activesquadSize(), partyalive = activesquadAlive();
	int libnum = 0;
	if (partyalive == 6) return;
	for (int pl = 0; pl < CreaturePool::getInstance().lenpool(); pl++)
	{
		if (pool[pl]->location != loc) continue;
		if (pool[pl]->getCreatureHealth().alive&&pool[pl]->getCreatureHealth().align == 1) libnum++;
	}
	if (partysize == libnum) return;
	for (int p = 0; p < 6; p++)
	{
		if (activesquad->squad[p] == NULL || !activesquad->squad[p]->getCreatureHealth().alive)
		{
			for (int pl = 0; pl < CreaturePool::getInstance().lenpool(); pl++)
			{
				if (pool[pl]->location != loc) continue;
				if (pool[pl]->getCreatureHealth().alive&&pool[pl]->squadid == -1 &&
					pool[pl]->getCreatureHealth().align == 1)
				{
					if (activesquad->squad[p] != NULL) activesquad->squad[p]->squadid = -1;
					activesquad->squad[p] = pool[pl];
					activesquad->squad[p]->squadid = activesquad->id;
					break;
				}
			}
		}
	}
}