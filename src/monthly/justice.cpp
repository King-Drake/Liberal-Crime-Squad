

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

#include "../includes21.h"
#include "../constStringjustice.h"

/* monthly - sentence a liberal */
void penalize(DeprecatedCreature &g, char lenient)
{
	set_color_easy(RED_ON_BLACK_BRIGHT);
	moveAlt(3, 1);
	addstrAlt(CONST_GUILTY, gamelog);
	gamelog.newline();

	pressAnyKey();

	short oldsentence = g.sentence;
	char olddeathpenalty = g.deathpenalty;
	g.sentence = 0, g.deathpenalty = 0;

	if (!lenient && ((g.crimes_suspected[LAWFLAG_MURDER]) || (g.crimes_suspected[LAWFLAG_TREASON]) ||
		((g.crimes_suspected[LAWFLAG_BURNFLAG]) && lawList[LAW_FLAGBURNING] == -2) ||
		lawList[LAW_DEATHPENALTY] == -2))
	{
		if (lawList[LAW_DEATHPENALTY] == -2) g.deathpenalty = 1;
		if (lawList[LAW_DEATHPENALTY] == -1) g.deathpenalty = LCSrandom(3);
		if (lawList[LAW_DEATHPENALTY] == 0) g.deathpenalty = LCSrandom(2);
		if (lawList[LAW_DEATHPENALTY] == 1) g.deathpenalty = !LCSrandom(5);
		if (lawList[LAW_DEATHPENALTY] == 2) g.deathpenalty = 0;
	}

	for (int l = 0; l < LAWFLAGNUM; l++) if (g.crimes_suspected[l] > 10) g.crimes_suspected[l] = 10;

	//CALC TIME
	if (!g.deathpenalty)
	{
		if (!(g.sentence < 0))
		{
			g.sentence += (36 + LCSrandom(18))*g.crimes_suspected[LAWFLAG_KIDNAPPING];
			g.sentence += (1 + LCSrandom(4))*g.crimes_suspected[LAWFLAG_THEFT];
			//g.sentence+=(4+LCSrandom(12))*(!!g.crimes_suspected[LAWFLAG_GUNUSE])+ // Extra for first incident only
			//            (2+LCSrandom(4)*g.crimes_suspected[LAWFLAG_GUNUSE]);      // Generally
			//g.sentence+=(1+LCSrandom(4))*(!!g.crimes_suspected[LAWFLAG_GUNCARRY]);
			g.sentence += (6 + LCSrandom(7))*g.crimes_suspected[LAWFLAG_CARTHEFT];
			g.sentence += (1 + LCSrandom(13))*g.crimes_suspected[LAWFLAG_INFORMATION];
			g.sentence += (1 + LCSrandom(13))*g.crimes_suspected[LAWFLAG_COMMERCE];
			g.sentence += (6 + LCSrandom(25))*g.crimes_suspected[LAWFLAG_CCFRAUD];
			g.sentence += (3 + LCSrandom(12))*g.crimes_suspected[LAWFLAG_BURIAL];
			g.sentence += (1 + LCSrandom(6))*g.crimes_suspected[LAWFLAG_PROSTITUTION];
			g.sentence += 1 * g.crimes_suspected[LAWFLAG_DISTURBANCE];
			g.sentence += 1 * g.crimes_suspected[LAWFLAG_PUBLICNUDITY];
			//g.sentence+=1*g.crimes_suspected[LAWFLAG_LOITERING];
			g.sentence += 1 * g.crimes_suspected[LAWFLAG_HIREILLEGAL];
			g.sentence += (12 + LCSrandom(100))*g.crimes_suspected[LAWFLAG_RACKETEERING];

			// How illegal is marijuana?
			if (lawList[LAW_DRUGS] == -2) g.sentence += (3 + LCSrandom(360))*g.crimes_suspected[LAWFLAG_BROWNIES]; //insanely illegal
			else if (lawList[LAW_DRUGS] == -1) g.sentence += (3 + LCSrandom(120))*g.crimes_suspected[LAWFLAG_BROWNIES]; //very illegal
			else if (lawList[LAW_DRUGS] == 0) g.sentence += (3 + LCSrandom(12))*g.crimes_suspected[LAWFLAG_BROWNIES]; //moderately illegal
			// else not illegal

			g.sentence += 1 * g.crimes_suspected[LAWFLAG_BREAKING];
			g.sentence += (60 + LCSrandom(181))*g.crimes_suspected[LAWFLAG_TERRORISM];
			g.sentence += (30 + LCSrandom(61))*g.crimes_suspected[LAWFLAG_BANKROBBERY];
			g.sentence += (30 + LCSrandom(61))*g.crimes_suspected[LAWFLAG_JURY];
			g.sentence += (30 + LCSrandom(61))*g.crimes_suspected[LAWFLAG_HELPESCAPE];
			g.sentence += (3 + LCSrandom(16))*g.crimes_suspected[LAWFLAG_ESCAPED];
			g.sentence += (1 + LCSrandom(1))*g.crimes_suspected[LAWFLAG_RESIST];
			g.sentence += (6 + LCSrandom(1))*g.crimes_suspected[LAWFLAG_EXTORTION];

			g.sentence += (4 + LCSrandom(3))*g.crimes_suspected[LAWFLAG_SPEECH];
			g.sentence += 1 * g.crimes_suspected[LAWFLAG_VANDALISM];
			g.sentence += (12 + LCSrandom(12))*g.crimes_suspected[LAWFLAG_ARSON];
			g.sentence += (12 + LCSrandom(1))*g.crimes_suspected[LAWFLAG_ARMEDASSAULT];
			g.sentence += (3 + LCSrandom(1))*g.crimes_suspected[LAWFLAG_ASSAULT];
		}
		if (lawList[LAW_FLAGBURNING] == -2)
		{
			if (!LCSrandom(2)) g.sentence += (120 + LCSrandom(241))*g.crimes_suspected[LAWFLAG_BURNFLAG];
			else if (g.crimes_suspected[LAWFLAG_BURNFLAG])g.sentence = -1 * g.crimes_suspected[LAWFLAG_BURNFLAG];
		}
		else if (lawList[LAW_FLAGBURNING] == -1) g.sentence += 36 * g.crimes_suspected[LAWFLAG_BURNFLAG];
		else if (lawList[LAW_FLAGBURNING] == 0) g.sentence += 1 * g.crimes_suspected[LAWFLAG_BURNFLAG];

		if ((LCSrandom(4) - g.crimes_suspected[LAWFLAG_MURDER]) > 0)
		{
			if (!(g.sentence < 0)) g.sentence += (120 + LCSrandom(241))*g.crimes_suspected[LAWFLAG_MURDER];
		}
		else
		{
			if (g.sentence < 0) g.sentence -= -1 * g.crimes_suspected[LAWFLAG_MURDER];
			else if (g.crimes_suspected[LAWFLAG_MURDER])
				g.sentence = -1 * g.crimes_suspected[LAWFLAG_MURDER];
		}
		if (g.sentence < 0) g.sentence -= 1 * g.crimes_suspected[LAWFLAG_TREASON];
		else if (g.crimes_suspected[LAWFLAG_TREASON]) g.sentence = -1 * g.crimes_suspected[LAWFLAG_TREASON];
		if (lenient&&g.sentence != -1) g.sentence /= 2;
		if (lenient&&g.sentence == -1) g.sentence = 240 + LCSrandom(120);
	}
	//LENIENCY AND CAPITAL PUNISHMENT DON'T MIX
	else if (g.deathpenalty&&lenient) g.deathpenalty = 0, g.sentence = -1;

	//MENTION LENIENCY
	if (lenient)
	{
		set_color_easy(WHITE_ON_BLACK);
		moveAlt(5, 1);
		addstrAlt(CONST_DURING_SENTENCING_THE_JUDGE_GRANTS_SOME_LENIENCY, gamelog);
		gamelog.newline();

		pressAnyKey();
	}

	//MENTION SENTENCE
	if (olddeathpenalty)
	{
		g.deathpenalty = 1;
		g.sentence = 3;
		set_color_easy(RED_ON_BLACK_BRIGHT);
		moveAlt(7, 1);
		addstrAlt(g.propername, gamelog);
		addstrAlt(CONST_YOU_WILL_BE_RETURNED_TO_PRISON_TO_CARRY_OUT_YOUR_DEATH_SENTENCE, gamelog);
		gamelog.newline();

		pressAnyKey();

		set_color_easy(WHITE_ON_BLACK);
		moveAlt(9, 1);
		addstrAlt(execution_in_three_months, gamelog);

		pressAnyKey();
	}
	else if (g.deathpenalty)
	{
		g.sentence = 3;
		set_color_easy(YELLOW_ON_RED_BRIGHT);
		moveAlt(7, 1);
		addstrAlt(g.propername, gamelog);
		addstrAlt(CONST_YOU_ARE_SENTENCED_TO_DEATH, gamelog);
		gamelog.newline();

		pressAnyKey();

		set_color_easy(WHITE_ON_BLACK);
		moveAlt(9, 1);
		addstrAlt(execution_in_three_months, gamelog);

		pressAnyKey();
	}
	// Don't give a time-limited sentence if they already have a life sentence.
	else if ((g.sentence >= 0 && oldsentence < 0) ||
		(g.sentence == 0 && oldsentence > 0))
	{
		g.sentence = oldsentence;
		set_color_easy(WHITE_ON_BLACK);
		moveAlt(7, 1);
		addstrAlt(g.propername, gamelog);
		addstrAlt(CONST_THE_COURT_SEES_NO_NEED_TO_ADD_TO_YOUR_EXISTING_SENTENCE, gamelog);
		moveAlt(8, 1);
		addstrAlt(CONST_YOU_WILL_BE_RETURNED_TO_PRISON_TO_RESUME_IT, gamelog);
		if (g.sentence > 1 && lenient)
		{
			g.sentence--;
			addstrAlt(CONST_LESS_A_MONTH_FOR_TIME_ALREADY_SERVED, gamelog);
		}
		else addstrAlt(SINGLE_DOT, gamelog);

		pressAnyKey();
	}
	else if (g.sentence == 0)
	{
		set_color_easy(WHITE_ON_BLACK);
		moveAlt(7, 1);
		addstrAlt(g.propername, gamelog);
		addstrAlt(CONST_CONSIDER_THIS_A_WARNING_YOU_ARE_FREE_TO_GO, gamelog);

		pressAnyKey();
	}
	else
	{
		if (g.sentence >= 36)g.sentence -= g.sentence % 12;

		set_color_easy(WHITE_ON_BLACK);
		moveAlt(7, 1);
		addstrAlt(g.propername, gamelog);
		addstrAlt(CONST_YOU_ARE_SENTENCED_TO, gamelog);
		if (g.sentence > 1200) g.sentence /= -1200;

		if (g.sentence <= -1)
		{
			if (g.sentence < -1)
			{
				addstrAlt(-(g.sentence), gamelog);
				addstrAlt(CONST_CONSECUTIVE_LIFE_TERMS_IN_PRISON, gamelog);
				gamelog.newline();

				// Don't bother saying this if the convicted already has one or
				// more life sentences. Makes the 'consecutively' and 'concurrently'
				// statements later easier to tack on.
				if (oldsentence >= 0)
				{
					addstrAlt(SINGLE_DOT, gamelog);

					pressAnyKey();

					moveAlt(9, 1);
					addstrAlt(CONST_HAVE_A_NICE_DAY, gamelog);
					addstrAlt(g.propername, gamelog);
				}
			}
			else addstrAlt(CONST_LIFE_IN_PRISON, gamelog);
		}
		else if (g.sentence >= 36)
		{
			addstrAlt(g.sentence / 12, gamelog);
			addstrAlt(CONST_YEARS_IN_PRISON, gamelog);
		}
		else
		{
			addstrAlt(g.sentence, gamelog);
			addstrAlt(CONST_MONTH, gamelog);
			if (g.sentence > 1)addstrAlt(LETTER_S, gamelog);
			addstrAlt(CONST_IN_PRISON, gamelog);
		}

		// Mash together compatible sentences.
		if ((g.sentence > 0 && oldsentence > 0) ||
			(g.sentence < 0 && oldsentence < 0))
		{
			addstrAlt(CONST_X_SINGLE_COMMA, gamelog);
			moveAlt(8, 1);
			if (lenient)
			{
				if (abs(oldsentence) > abs(g.sentence))
					g.sentence = oldsentence;
				addstrAlt(CONST_TO_BE_SERVED_CONCURRENTLY, gamelog);
			}
			else
			{
				g.sentence += oldsentence;
				addstrAlt(CONST_TO_BE_SERVED_CONSECUTIVELY, gamelog);
			}
		}

		addstrAlt(SINGLE_DOT, gamelog);

		//dejuice boss
		int boss = getpoolcreature(g.hireid);
		if (boss != -1 && pool[boss]->juice > 50)
		{
			int juice = g.juice / 10;
			if (juice < 5) juice = 5;
			addjuice(*pool[boss], -juice, 0);
		}

		pressAnyKey();
	}
	gamelog.nextMessage();
}



/* monthly - move a liberal to jail */
void imprison(DeprecatedCreature &g)
{
	g.location = find_site_index_in_city(SITE_GOVERNMENT_PRISON, LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, g.location));
}


void trial(DeprecatedCreature &g)
{

	music.play(MUSIC_TRIAL);
	// If their old base is no longer under LCS control, wander back to the
	// homeless shelter instead.
	if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, g.base) < 0) {
		g.base = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, g.location);
	}
	g.location = g.base;

	bool breaker[LAWFLAGNUM] = { 0 };

	eraseAlt();

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	mvaddstrAlt(1, 1, g.name, gamelog);
	addstrAlt(CONST_IS_STANDING_TRIAL, gamelog);

	gamelog.newline();
	pressAnyKey();

	set_color_easy(WHITE_ON_BLACK);

	if (!iscriminal(g.getCreatureJustice())) criminalize(g, LAWFLAG_LOITERING);

	int typenum = 0, scarefactor = 0;
	// *JDS* Scarefactor is the severity of the case against you; if you're a really
	// nasty person with a wide variety of major charges against you, then scarefactor
	// can get up there

	for (int i = 0; i < LAWFLAGNUM; i++) {
		if (g.crimes_suspected[i])
		{
			typenum++;
			scarefactor += scare_factor(i, g.crimes_suspected[i]);
			breaker[i] = 1;
		}
	}
	//CHECK FOR SLEEPERS
	DeprecatedCreature *sleeperjudge = NULL;
	DeprecatedCreature *sleeperlawyer = NULL;
	int maxsleeperskill = 0;
	for (int p = 0; p < len(pool); p++)
		if (pool[p]->getNameAndAlignment().alive && (pool[p]->flag&CREATUREFLAG_SLEEPER) && LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, pool[p]->location) == LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, g.location))
		{
			if (pool[p]->type == CREATURE_JUDGE_CONSERVATIVE || pool[p]->type == CREATURE_JUDGE_LIBERAL)
				if (pool[p]->infiltration * 100 >= LCSrandom(100)) sleeperjudge = pool[p];
			if (pool[p]->type == CREATURE_LAWYER)
				if (pool[p]->get_skill(SKILL_LAW) + pool[p]->get_skill(SKILL_PERSUASION) >= maxsleeperskill)
				{
					sleeperlawyer = pool[p];
					maxsleeperskill = pool[p]->get_skill(SKILL_LAW) + sleeperlawyer->get_skill(SKILL_PERSUASION);
				}
		}

	//STATE CHARGES
	set_color_easy(WHITE_ON_BLACK);

	if (sleeperjudge)
	{
		mvaddstrAlt(3, 1, string_sleeper, gamelog);
		addstrAlt(sleeperjudge->getNameAndAlignment().name, gamelog);
		addstrAlt(CONST_READS_THE_CHARGES_TRYING_TO_HIDE_A_SMILE, gamelog);
		g.confessions = 0; //Made sleeper judge prevent these lunatics from testifying
	}
	else mvaddstrAlt(3, 1, CONST_THE_JUDGE_READS_THE_CHARGES, gamelog);
	gamelog.newline();

	set_color_easy(RED_ON_BLACK_BRIGHT);
	mvaddstrAlt(5, 1, CONST_THE_DEFENDANT, gamelog);

	addstrAlt(g.propername, gamelog);
	addstrAlt(CONST_IS_CHARGED_WITH, gamelog);

	int x = 2, y = 5;
	while ((typenum--) > 0)
	{
		if ((x++) >= 2) { x = 0; moveAlt(++y, 1); }
		//////////////////////////////////////////////////////////////////////////
		//                                Treason                               //
		//////////////////////////////////////////////////////////////////////////
		// Technically, treason is exposing state secrets, or somesuch.         //
		// Illegal Immigrants cannot commit treason, because treason can only   //
		// be committed by `those owing allegiance to the United States`.       //
		//////////////////////////////////////////////////////////////////////////

		// The above is already respected by LCS; treason occurs from exposing
		// intelligence secrets, and illegal immigrants are not taken to trial.
		//    - Jonathan S. Fox

		// Oh, right. Forgot about that. Even if the law is L+?
		if (breaker[LAWFLAG_TREASON])
		{
			if (g.crimes_suspected[LAWFLAG_TREASON] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_TREASON], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_TREASON, gamelog);
			breaker[LAWFLAG_TREASON] = 0;
		}
		else if (breaker[LAWFLAG_TERRORISM])
		{
			if (g.crimes_suspected[LAWFLAG_TERRORISM] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_TERRORISM], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_TERRORISM, gamelog);
			breaker[LAWFLAG_TERRORISM] = 0;
		}
		else if (breaker[LAWFLAG_MURDER])//XXX: How about the addition of a `manslaughter` charge? -- LK
		{                               //     Manslaughter is murder without forethought or malice, IIRC. -- LK
										// Well, I can't think of an instance of this in LCS besides fruit stand employees. -Fox
										// Possibly people you accidentally kill when shooting at conservatives. -- LK
			if (g.crimes_suspected[LAWFLAG_MURDER] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_MURDER], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_MURDER, gamelog);
			breaker[LAWFLAG_MURDER] = 0;
		}
		else if (breaker[LAWFLAG_KIDNAPPING])
		{
			if (g.crimes_suspected[LAWFLAG_KIDNAPPING] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_KIDNAPPING], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_KIDNAPPING, gamelog);
			breaker[LAWFLAG_KIDNAPPING] = 0;
		}
		else if (breaker[LAWFLAG_BANKROBBERY])
		{
			if (g.crimes_suspected[LAWFLAG_BANKROBBERY] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_BANKROBBERY], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_BANK_ROBBERY, gamelog);
			breaker[LAWFLAG_BANKROBBERY] = 0;
		}
		else if (breaker[LAWFLAG_ARSON])
		{
			if (g.crimes_suspected[LAWFLAG_ARSON] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_ARSON], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_ARSON, gamelog);
			breaker[LAWFLAG_ARSON] = 0;
		}
		else if (breaker[LAWFLAG_BURNFLAG] && lawList[LAW_FLAGBURNING] <= 0)
		{
			if (g.crimes_suspected[LAWFLAG_BURNFLAG] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_BURNFLAG]);
				addstrAlt(counts_of, gamelog);
			}
			if (lawList[LAW_FLAGBURNING] == -2)
				addstrAlt(CONST_X_FLAG_MURDER, gamelog);
			else if (lawList[LAW_FLAGBURNING] == -1)
				addstrAlt(CONST_FELONY_FLAG_BURNING, gamelog);
			else if (lawList[LAW_FLAGBURNING] == 0)
				addstrAlt(CONST_X_FLAG_BURNING_LOWERCASE, gamelog);
			breaker[LAWFLAG_BURNFLAG] = 0;
		}
		else if (breaker[LAWFLAG_SPEECH])
		{
			if (g.crimes_suspected[LAWFLAG_SPEECH] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_SPEECH], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_SEDITION, gamelog);
			breaker[LAWFLAG_SPEECH] = 0;
		}
		else if (breaker[LAWFLAG_BROWNIES])
		{
			if (g.crimes_suspected[LAWFLAG_BROWNIES] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_BROWNIES], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_DRUG_DEALING, gamelog);
			breaker[LAWFLAG_BROWNIES] = 0;
			//x=2;
		}
		else if (breaker[LAWFLAG_ESCAPED])
		{
			if (g.crimes_suspected[LAWFLAG_ESCAPED] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_ESCAPED], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_ESCAPING_PRISON, gamelog);
			breaker[LAWFLAG_ESCAPED] = 0;
		}
		else if (breaker[LAWFLAG_HELPESCAPE])
		{
			if (g.crimes_suspected[LAWFLAG_HELPESCAPE] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_HELPESCAPE], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_AIDING_A_PRISON_ESCAPE, gamelog);
			breaker[LAWFLAG_HELPESCAPE] = 0;
			x = 2;
		}
		else if (breaker[LAWFLAG_JURY])
		{
			if (g.crimes_suspected[LAWFLAG_JURY] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_JURY], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_JURY_TAMPERING, gamelog);
			breaker[LAWFLAG_JURY] = 0;
		}
		else if (breaker[LAWFLAG_RACKETEERING])
		{
			addstrAlt(CONST_X_RACKETEERING, gamelog);
			breaker[LAWFLAG_RACKETEERING] = 0;
		}
		else if (breaker[LAWFLAG_EXTORTION])
		{
			if (g.crimes_suspected[LAWFLAG_EXTORTION] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_EXTORTION], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_EXTORTION, gamelog);
			breaker[LAWFLAG_EXTORTION] = 0;
		}
		else if (breaker[LAWFLAG_ARMEDASSAULT])
		{
			if (g.crimes_suspected[LAWFLAG_ARMEDASSAULT] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_ARMEDASSAULT], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_FELONY_ASSAULT, gamelog);
			breaker[LAWFLAG_ARMEDASSAULT] = 0;
		}
		else if (breaker[LAWFLAG_ASSAULT])
		{
			if (g.crimes_suspected[LAWFLAG_ASSAULT] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_ASSAULT], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_MISDEMEANOR_ASSAULT, gamelog);
			breaker[LAWFLAG_ASSAULT] = 0;
		}
		else if (breaker[LAWFLAG_CARTHEFT])
		{
			if (g.crimes_suspected[LAWFLAG_CARTHEFT] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_CARTHEFT], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_GRAND_THEFT_AUTO, gamelog);// If chase lasts more than 20 `turns` then
			breaker[LAWFLAG_CARTHEFT] = 0;// this should be `Grand Theft Auto` -- LK
		}                              // We'll just make it grand theft auto anyway :) -Fox
		else if (breaker[LAWFLAG_CCFRAUD])
		{
			if (g.crimes_suspected[LAWFLAG_CCFRAUD] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_CCFRAUD], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_CREDIT_CARD_FRAUD_LOWERCASE, gamelog);
			breaker[LAWFLAG_CCFRAUD] = 0;
		}
		else if (breaker[LAWFLAG_THEFT])
		{
			if (g.crimes_suspected[LAWFLAG_THEFT] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_THEFT], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_PETTY_LARCENY, gamelog);
			breaker[LAWFLAG_THEFT] = 0;
		}
		else if (breaker[LAWFLAG_PROSTITUTION])
		{
			if (g.crimes_suspected[LAWFLAG_PROSTITUTION] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_PROSTITUTION], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_PROSTITUTION, gamelog);
			breaker[LAWFLAG_PROSTITUTION] = 0;
		}
		else if (breaker[LAWFLAG_HIREILLEGAL])
		{
			if (g.crimes_suspected[LAWFLAG_HIREILLEGAL] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_HIREILLEGAL], gamelog);
				addstrAlt(counts_of, gamelog);
				addstrAlt((lawList[LAW_IMMIGRATION] < 1 ? CONST_X_HIRING_ILLEGAL_ALIENS : CONST_X_HIRING_UNDOCUMENTED_WORKERS), gamelog);
			}
			else addstrAlt((lawList[LAW_IMMIGRATION] < 1 ? CONST_HIRING_AN_ILLEGAL_ALIEN : CONST_HIRING_AN_UNDOCUMENTED_WORKER), gamelog);
			breaker[LAWFLAG_HIREILLEGAL] = 0;
			x = 2;
		}
		/*else if(breaker[LAWFLAG_GUNUSE])
		{
		   if(g.crimes_suspected[LAWFLAG_GUNUSE]>1)
		   {
			  addstrAlt(g.crimes_suspected[LAWFLAG_GUNUSE]);
			  addstrAlt(counts_of);
		   }
		   addstrAlt(CONST_FIRING_AN_ILLEGAL_WEAPON);
		   breaker[LAWFLAG_GUNUSE]=0;
		   x=2;
		}
		else if(breaker[LAWFLAG_GUNCARRY])
		{
		   if(g.crimes_suspected[LAWFLAG_GUNCARRY]>1)
		   {
			  addstrAlt(g.crimes_suspected[LAWFLAG_GUNCARRY]);
			  addstrAlt(counts_of);
		   }
		   addstrAlt(CONST_POSSESSION_OF_AN_ILLEGAL_WEAPON);
		   breaker[LAWFLAG_GUNCARRY]=0;
		   x=2;
		}*/
		else if (breaker[LAWFLAG_COMMERCE])
		{
			if (g.crimes_suspected[LAWFLAG_COMMERCE] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_COMMERCE], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_INTERFERENCE_WITH_INTERSTATE_COMMERCE, gamelog);
			breaker[LAWFLAG_COMMERCE] = 0;
			x = 2;
		}
		else if (breaker[LAWFLAG_INFORMATION])
		{
			if (g.crimes_suspected[LAWFLAG_INFORMATION] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_INFORMATION], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_UNLAWFUL_ACCESS_OF_AN_INFORMATION_SYSTEM, gamelog);
			breaker[LAWFLAG_INFORMATION] = 0;
			x = 2;
		}
		else if (breaker[LAWFLAG_BURIAL])
		{
			if (g.crimes_suspected[LAWFLAG_BURIAL] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_BURIAL], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_UNLAWFUL_BURIAL, gamelog);
			breaker[LAWFLAG_BURIAL] = 0;
		}
		else if (breaker[LAWFLAG_BREAKING])
		{
			if (g.crimes_suspected[LAWFLAG_BREAKING] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_BREAKING], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_BREAKING_AND_ENTERING, gamelog);
			breaker[LAWFLAG_BREAKING] = 0;
		}
		else if (breaker[LAWFLAG_VANDALISM])
		{
			if (g.crimes_suspected[LAWFLAG_VANDALISM] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_VANDALISM], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_VANDALISM, gamelog);
			breaker[LAWFLAG_VANDALISM] = 0;
		}
		else if (breaker[LAWFLAG_RESIST])
		{
			addstrAlt(CONST_X_RESISTING_ARREST, gamelog);
			breaker[LAWFLAG_RESIST] = 0;
		}
		else if (breaker[LAWFLAG_DISTURBANCE])
		{
			if (g.crimes_suspected[LAWFLAG_DISTURBANCE] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_DISTURBANCE], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_X_DISTURBING_THE_PEACE, gamelog);
			breaker[LAWFLAG_DISTURBANCE] = 0;
		}
		else if (breaker[LAWFLAG_PUBLICNUDITY])
		{
			if (g.crimes_suspected[LAWFLAG_PUBLICNUDITY] > 1)
			{
				addstrAlt(g.crimes_suspected[LAWFLAG_PUBLICNUDITY], gamelog);
				addstrAlt(counts_of, gamelog);
			}
			addstrAlt(CONST_INDECENT_EXPOSURE, gamelog);
			breaker[LAWFLAG_PUBLICNUDITY] = 0;
		}
		else if (breaker[LAWFLAG_LOITERING])
		{
			addstrAlt(CONST_X_LOITERING, gamelog);
			breaker[LAWFLAG_LOITERING] = 0;
		}

		if (typenum > 1) addstrAlt(CONST_X_COMMA_SPACE, gamelog);
		if (typenum == 1) addstrAlt(CONST_SPACE_AND_SPACE, gamelog);
		if (typenum == 0) addstrAlt(SINGLE_DOT, gamelog);

		pressAnyKey();
	}

	gamelog.newline();

	if (g.confessions)
	{
		moveAlt(y += 2, 1);

		if (g.confessions > 1)
		{
			addstrAlt(g.confessions, gamelog);
			addstrAlt(CONST_FORMER_LCS_MEMBERS_WILL_TESTIFY_AGAINST, gamelog);
		}
		else addstrAlt(CONST_A_FORMER_LCS_MEMBER_WILL_TESTIFY_AGAINST, gamelog);
		addstrAlt(g.name, gamelog);
		addstrAlt(SINGLE_DOT, gamelog);
		gamelog.newline();

		pressAnyKey();
	}

	//CHOOSE DEFENSE
	set_color_easy(WHITE_ON_BLACK);
	mvaddstrAlt(y + 2, 1, CONST_HOW_WILL_YOU_CONDUCT_THE_DEFENSE);

	char attorneyname[200];
	unsigned long oldseed[RNG_SIZE];
	copyRNG(oldseed, seed);
	copyRNG(seed, attorneyseed);
	generate_name(attorneyname);
	copyRNG(seed, oldseed);

	y += 4;
	mvaddstrAlt(y++, 1, CONST_A_USE_A_COURT_APPOINTED_ATTORNEY);
	mvaddstrAlt(y++, 1, CONST_B_DEFEND_SELF);
	mvaddstrAlt(y++, 1, CONST_C_PLEAD_GUILTY);



	if (ledger.get_funds() < 5000) {
		set_color_easy(BLACK_ON_BLACK_BRIGHT);
	}
	mvaddstrAlt(y++, 1, CONST_D_PAY_5000_TO_HIRE_ACE_LIBERAL_ATTORNEY);

	addstrAlt(attorneyname);
	addstrAlt(singleDot);
	if (sleeperlawyer)
	{
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(y++, 1, CONST_E_ACCEPT_SLEEPER);
		addstrAlt(sleeperlawyer->getNameAndAlignment().name);
		addstrAlt(CONST_S_OFFER_TO_ASSIST_PRO_BONO);

	}
	if (ledger.get_funds() < 5000) set_color_easy(WHITE_ON_BLACK);

	//SAV - added in display of skills and relevant attributes to help
	// decide when to defend self.
	mvaddstrAlt(++y, 5, HEART_COLON);
	addstrAlt(g.get_attribute(ATTRIBUTE_HEART, true));

	mvaddstrAlt(y, 25, CONST_X_PERSUASION_COLON);
	addstrAlt(g.get_skill(SKILL_PERSUASION));

	mvaddstrAlt(++y, 5, CONST_CHARISMA);
	addstrAlt(g.get_attribute(ATTRIBUTE_CHARISMA, true));

	mvaddstrAlt(y++, 25, CONST_X_LAW_COLON);
	addstrAlt(g.get_skill(SKILL_LAW));

	mvaddstrAlt(y++, 5, CONST_INTELLIGENCE);
	addstrAlt(g.get_attribute(ATTRIBUTE_INTELLIGENCE, true));

	// End SAV's adds




	LegalDefense defense;
	int c;
	while (true)
	{
		c = getkeyAlt();
		if (c == 'a') { defense = COURT_ATTORNEY; break; }

		if (c == 'b') { defense = SELF_REPRESENT; break; }

		if (c == 'c') { defense = PLEAD_GUILTY; break; }

		if (c == 'd'&&ledger.get_funds() >= 5000)
		{
			ledger.subtract_funds(5000, EXPENSE_LEGAL);
			defense = ACE_ATTORNEY;
			break;
		}
		if (c == 'e'&&sleeperlawyer)
		{
			defense = SLEEPER_ATTORNEY;
			strcpy(attorneyname, sleeperlawyer->name);
			break;
		}
	}

	//TRIAL
	if (defense != PLEAD_GUILTY)
	{
		int prosecution = 0;
		eraseAlt();

		set_color_easy(WHITE_ON_BLACK_BRIGHT);

		moveAlt(1, 1);
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_IS_STANDING_TRIAL);

		//TRIAL MESSAGE
		set_color_easy(WHITE_ON_BLACK);
		moveAlt(3, 1);
		addstrAlt(CONST_THE_TRIAL_PROCEEDS_JURY_SELECTION_IS_FIRST, gamelog);
		gamelog.newline();

		pressAnyKey();

		//JURY MAKEUP MESSAGE
		set_color_easy(WHITE_ON_BLACK_BRIGHT);
		moveAlt(5, 1);
		int jury = LCSrandom(61) - (60 * publicmood(-1)) / 100; // Political leanings of the population determine your jury
		if (sleeperjudge) jury -= 20;
		if (defense == ACE_ATTORNEY) // Hired $5000 ace attorney
		{
			if (LCSrandom(10))
			{
				addstrAlt(attorneyname, gamelog);
				addstrAlt(CONST_ENSURES_THE_JURY_IS_STACKED_IN, gamelog);
				addstrAlt(g.name, gamelog);
				addstrAlt(CONST_S_FAVOR, gamelog);
				gamelog.newline();
				if (jury > 0) jury = 0;
				jury -= 30;
			}
			else

			{
				set_color_easy(RED_ON_BLACK_BRIGHT);
				addstrAlt(attorneyname, gamelog);
				addstrAlt(CONST_S_CONSERVATIVE_ARCH_NEMESIS_WILL_REPRESENT_THE_PROSECUTION, gamelog);
				gamelog.newline();
				jury = 0;
				prosecution += 100; // DUN DUN DUN!!
			}
		}
		else if (jury <= -29)
		{
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
			switch (LCSrandom(liberal_jury.size() + 1))
			{
			case 0:addstrAlt(g.getNameAndAlignment().name); addstrAlt(CONST_S_BEST_FRIEND_FROM_CHILDHOOD_IS_A_JUROR, gamelog); break;
			default:addstrAlt(pickrandom(liberal_jury), gamelog); break;
			}
			gamelog.newline();
		}
		else if (jury <= -15) { addstrAlt(CONST_THE_JURY_IS_FAIRLY_LIBERAL, gamelog); }
		else if (jury < 15) { addstrAlt(CONST_THE_JURY_IS_QUITE_MODERATE, gamelog); }
		else if (jury < 29) { addstrAlt(CONST_THE_JURY_IS_A_BIT_CONSERVATIVE, gamelog); }
		else
		{
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			addstrAlt(pickrandom(conservative_jury), gamelog);
		}
		gamelog.newline();

		// Debug jury bias
		if (SHOWMECHANICS)
		{
			addstrAlt(CONST_X_SPACE_PARENTHESIS);
			if (jury >= 0) addcharAlt('+');
			addstrAlt(jury);
			addstrAlt(CONST_TO_CONVICT);
		}


		pressAnyKey();

		//PROSECUTION MESSAGE
		// *JDS* The bigger your record, the stronger the evidence
		prosecution += 40 + LCSrandom(101) + scarefactor + (20 * g.confessions);
		if (sleeperjudge) prosecution >>= 1;
		if (defense == ACE_ATTORNEY) prosecution -= 60;

		set_color_easy(WHITE_ON_BLACK);
		moveAlt(7, 1);

		if (prosecution <= 50) addstrAlt(CONST_THE_PROSECUTION_S_PRESENTATION_IS_TERRIBLE, gamelog);
		else if (prosecution <= 75) addstrAlt(CONST_THE_PROSECUTION_GIVES_A_STANDARD_PRESENTATION, gamelog);
		else if (prosecution <= 125) addstrAlt(CONST_THE_PROSECUTION_S_CASE_IS_SOLID, gamelog);
		else if (prosecution <= 175) addstrAlt(CONST_THE_PROSECUTION_MAKES_AN_AIRTIGHT_CASE, gamelog);
		else addstrAlt(CONST_THE_PROSECUTION_IS_INCREDIBLY_STRONG, gamelog);
		gamelog.newline();


		// Debug prosecution power
		if (SHOWMECHANICS)
		{
			addstrAlt(PARENTHESIS_PLUS);
			addstrAlt(prosecution / 2);
			addstrAlt(CONST_X_TO_PLUS);
			addstrAlt(prosecution);
			addstrAlt(CONST_TO_CONVICT);
		}



		getkeyAlt();

		jury += LCSrandom(prosecution / 2 + 1) + prosecution / 2;

		//DEFENSE MESSAGE
		set_color_easy(WHITE_ON_BLACK);
		moveAlt(9, 1);

		int defensepower = 0;
		if (defense == COURT_ATTORNEY || defense == ACE_ATTORNEY || defense == SLEEPER_ATTORNEY)
		{
			if (defense == COURT_ATTORNEY) defensepower = LCSrandom(71);    // Court-appointed attorney
			else if (defense == ACE_ATTORNEY) defensepower = LCSrandom(71) + 80; // Ace Liberal attorney
			else if (defense == SLEEPER_ATTORNEY)
			{
				// Sleeper attorney
				defensepower = LCSrandom(71) + sleeperlawyer->get_skill(SKILL_LAW) * 2
					+ sleeperlawyer->get_skill(SKILL_PERSUASION) * 2;
				sleeperlawyer->train(SKILL_LAW, prosecution / 4);
				sleeperlawyer->train(SKILL_PERSUASION, prosecution / 4);
			}
			if (defensepower <= 5) { addstrAlt(CONST_THE_DEFENSE_ATTORNEY_RARELY_SHOWED_UP, gamelog); }
			else if (defensepower <= 15) { addstrAlt(CONST_THE_DEFENSE_ATTORNEY_ACCIDENTALLY_SAID_MY_CLIENT_IS_GUILTY_DURING_CLOSING, gamelog); }
			else if (defensepower <= 25) { addstrAlt(CONST_THE_DEFENSE_IS_TOTALLY_LAME, gamelog); }
			else if (defensepower <= 50) { addstrAlt(CONST_THE_DEFENSE_WAS_LACKLUSTER, gamelog); }
			else if (defensepower <= 75) { addstrAlt(CONST_DEFENSE_ARGUMENTS_WERE_PRETTY_GOOD, gamelog); }
			else if (defensepower <= 100) { addstrAlt(CONST_THE_DEFENSE_WAS_REALLY_SLICK, gamelog); }
			else if (defensepower <= 145)
			{
				if (prosecution < 100) { addstrAlt(CONST_THE_DEFENSE_MAKES_THE_PROSECUTION_LOOK_LIKE_AMATEURS, gamelog); }
				else { addstrAlt(CONST_THE_DEFENSE_IS_EXTREMELY_COMPELLING, gamelog); }
			}
			else
			{
				if (prosecution < 100)
				{
					addstrAlt(attorneyname, gamelog);
					addstrAlt(CONST_S_ARGUMENTS_MADE_SEVERAL_OF_THE_JURORS_STAND_UP, gamelog);
					mvaddstrAlt(10, 1, CONST_AND_SHOUT_NOT_GUILTY_BEFORE_DELIBERATIONS_EVEN_BEGAN, gamelog);
					if (defense == SLEEPER_ATTORNEY) addjuice(*sleeperlawyer, 10, 500); // Bow please
				}
				else
				{
					addstrAlt(attorneyname, gamelog);
					addstrAlt(CONST_CONDUCTS_AN_INCREDIBLE_DEFENSE, gamelog);
				}

			}
			gamelog.newline();

		}
		if (defense == SELF_REPRESENT)
		{
			// *JDS* LEGAL SELF-REPRESENTATION: To succeed here, you really need to have two skills be
			// high: persuasion and law, with law being 1.5 times as influential. You can't have
			// just one or just the other. Even if you're a very persuasive person, the court will eat
			// you alive if you can't sound intelligent when talking about the relevant charges, and you
			// won't be able to fool the jury into letting you go if you aren't persuasive, as no
			// matter how encyclopedic your legal knowledge is, it's all in the pitch.
			//
			// If either your persuasion or your law roll is too low, you'll end up getting a negative
			// result that will drag down your defense. So try not to suck in either area.
			defensepower = 5 * (g.skill_roll(SKILL_PERSUASION) - 3) +
				10 * (g.skill_roll(SKILL_LAW) - 3);
			g.train(SKILL_PERSUASION, 50);
			g.train(SKILL_LAW, 50);

			addstrAlt(g.name, gamelog);
			if (defensepower <= 0)
			{
				addstrAlt(CONST_MAKES_ONE_HORRIBLE_MISTAKE_AFTER_ANOTHER, gamelog);
				gamelog.newline();
				addjuice(g, -10, -50); // You should be ashamed
			}
			else if (defensepower <= 25) addstrAlt(CONST_S_CASE_REALLY_SUCKED, gamelog);
			else if (defensepower <= 50) addstrAlt(CONST_DID_ALL_RIGHT_BUT_MADE_SOME_MISTAKES, gamelog);
			else if (defensepower <= 75) addstrAlt(CONST_S_ARGUMENTS_WERE_PRETTY_GOOD, gamelog);
			else if (defensepower <= 100) addstrAlt(CONST_WORKED_THE_JURY_VERY_WELL, gamelog);
			else if (defensepower <= 150) addstrAlt(CONST_MADE_A_VERY_POWERFUL_CASE, gamelog);
			else
			{
				addstrAlt(CONST_HAD_THE_JURY_JUDGE_AND_PROSECUTION_CRYING_FOR_FREEDOM, gamelog);
				addjuice(g, 50, 1000); // That shit is legend
			}
			gamelog.newline();
		}

		// Debug defense power
		if (SHOWMECHANICS)
		{
			addstrAlt(CONST_X_SPACE_PARENTHESIS);
			addstrAlt(defensepower);
			addstrAlt(CONST_NEED);
			addstrAlt(jury + 1);
			addstrAlt(CONST_TO_ACQUIT);
		}


		pressAnyKey();

		//DELIBERATION MESSAGE
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(12, 1, CONST_THE_JURY_LEAVES_TO_CONSIDER_THE_CASE, gamelog);

		gamelog.newline();
		pressAnyKey();


		//JURY RETURN MESSAGE
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(1, 1, CONST_THE_JURY_HAS_RETURNED_FROM_DELIBERATIONS, gamelog);

		gamelog.newline();
		pressAnyKey();


		bool keeplawflags = false;


		//HUNG JURY
		if (defensepower == jury)
		{
			set_color_easy(YELLOW_ON_BLACK_BRIGHT);
			mvaddstrAlt(3, 1, CONST_BUT_THEY_CAN_T_REACH_A_VERDICT, gamelog);
			gamelog.newline();
			pressAnyKey();
			//RE-TRY
			if (LCSrandom(2) || scarefactor >= 10 || g.getCreatureConfessions())
			{
				set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(5, 1, CONST_THE_CASE_WILL_BE_RE_TRIED_NEXT_MONTH, gamelog);
				gamelog.newline();
				pressAnyKey();
				g.location = find_site_index_in_same_city(SITE_GOVERNMENT_COURTHOUSE, g.location);
				keeplawflags = true;
			}
			//NO RE-TRY
			else
			{
				set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(5, 1, CONST_THE_PROSECUTION_DECLINES_TO_RE_TRY_THE_CASE, gamelog);
				gamelog.newline();
				if (g.getCreatureJustice().sentence == 0)
				{
					set_color_easy(GREEN_ON_BLACK_BRIGHT);
					mvaddstrAlt(7, 1, g.getNameAndAlignment().name, gamelog);
					addstrAlt(CONST_IS_FREE, gamelog);
				}
				else
				{
					set_color_easy(WHITE_ON_BLACK);
					mvaddstrAlt(7, 1, g.getNameAndAlignment().name, gamelog);
					addstrAlt(CONST_WILL_BE_RETURNED_TO_PRISON_TO_RESUME_AN_EARLIER_SENTENCE, gamelog);
					if (!g.getCreatureJustice().deathpenalty && g.getCreatureJustice().sentence > 1 && (LCSrandom(2) || sleeperjudge))
					{
						g.sentence--;
						addstrAlt(CONST_LESS_A_MONTH_FOR_TIME_ALREADY_SERVED, gamelog);
					}
					else addstrAlt(singleDot, gamelog);
					if (g.getCreatureJustice().deathpenalty)
					{
						g.sentence = 3;
						mvaddstrAlt(9, 1, execution_in_three_months, gamelog);
					}
				}
				gamelog.nextMessage();
				pressAnyKey();
			}

		}
		//ACQUITTAL!
		else if (defensepower > jury)
		{
			set_color_easy(GREEN_ON_BLACK_BRIGHT);
			mvaddstrAlt(3, 1, CONST_NOT_GUILTY, gamelog);
			gamelog.newline();

			pressAnyKey();

			if (g.sentence == 0)
			{
				set_color_easy(GREEN_ON_BLACK_BRIGHT);
				mvaddstrAlt(5, 1, g.name, gamelog);
				addstrAlt(CONST_IS_FREE, gamelog);
			}
			else
			{
				set_color_easy(WHITE_ON_BLACK);
				mvaddstrAlt(5, 1, g.name, gamelog);
				addstrAlt(CONST_WILL_BE_RETURNED_TO_PRISON_TO_RESUME_AN_EARLIER_SENTENCE, gamelog);
				if (!g.deathpenalty && g.sentence > 1 && (LCSrandom(2) || sleeperjudge))
				{
					g.sentence--;
					addstrAlt(CONST_LESS_A_MONTH_FOR_TIME_ALREADY_SERVED, gamelog);
				}
				else addstrAlt(singleDot, gamelog);
				if (g.deathpenalty)
				{
					g.sentence = 3;
					mvaddstrAlt(7, 1, execution_in_three_months, gamelog);
				}
			}

			gamelog.nextMessage();

			// Juice sleeper
			if (defense == SLEEPER_ATTORNEY) addjuice(*sleeperlawyer, 10, 100);
			// Juice for self-defense
			if (defense == SELF_REPRESENT) addjuice(g, 10, 100);

			pressAnyKey();
		}
		//LENIENCE
		else
		{
			// De-Juice sleeper
			if (defense == SLEEPER_ATTORNEY) addjuice(*sleeperlawyer, -5, 0);

			// Juice for getting convicted of something :)
			addjuice(g, 25, 200);

			// Check for lenience; sleeper judge will always be merciful
			if (defensepower / 3 >= jury / 4 || sleeperjudge) penalize(g, 1);
			else penalize(g, 0);
		}
		//CLEAN UP LAW FLAGS
		if (!keeplawflags) for (int i = 0; i < LAWFLAGNUM; i++) g.crimes_suspected[i] = 0;
		//Clean up heat, confessions
		g.heat = 0, g.confessions = 0;
		//PLACE PRISONER
		if (g.sentence != 0) imprison(g);
		else
		{

			g.give_armor(getarmortype(tag_ARMOR_CLOTHES), NULL);
		}
	}
	//GUILTY PLEA
	// How about CONST_NOLO (Nolo contendere) -- LK
	// I would imagine this would disregard the strength of the defense. -- LK
	else
	{
		eraseAlt();
		set_color_easy(WHITE_ON_BLACK);
		mvaddstrAlt(1, 1, CONST_THE_COURT_ACCEPTS_THE_PLEA, gamelog);

		gamelog.nextMessage();

		pressAnyKey();

		// Check for lenience; sleeper judge will always be merciful
		if (sleeperjudge || LCSrandom(2)) penalize(g, 1);
		else penalize(g, 0);
		//CLEAN UP LAW FLAGS
		for (int i = 0; i < LAWFLAGNUM; i++) g.crimes_suspected[i] = 0;
		//Clean up heat, confessions
		g.heat = 0, g.confessions = 0;
		//PLACE PRISONER
		if (g.sentence != 0) imprison(g);
		else
		{
			g.give_armor(getarmortype(tag_ARMOR_CLOTHES), NULL);
		}
	}
}


void reeducation(DeprecatedCreature &g)
{

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	moveAlt(8, 1);
	addstrAlt(g.name, gamelog);
	addstrAlt(pickrandom(reeducation_experiences), gamelog);
	gamelog.newline();

	pressAnyKey();

	moveAlt(10, 1);
	if (!g.attribute_check(ATTRIBUTE_HEART, DIFFICULTY_FORMIDABLE))
	{
		if (g.juice > 0 && LCSrandom(2))
		{
			addstrAlt(g.name, gamelog);
			addstrAlt(CONST_FEELS_BAD_ABOUT_LCS_ACTIONS_AND_LOSES_JUICE, gamelog);
			addjuice(g, -50, 0);
		}
		else if (LCSrandom(15) > g.get_attribute(ATTRIBUTE_WISDOM, true)
			|| g.get_attribute(ATTRIBUTE_WISDOM, true) < g.get_attribute(ATTRIBUTE_HEART, true))
		{
			addstrAlt(g.name, gamelog);
			addstrAlt(CONST_SILENTLY_GROWS_WISER, gamelog);
			g.adjust_attribute(ATTRIBUTE_WISDOM, +1);
		}
		else if (g.align == ALIGN_LIBERAL && g.flag & CREATUREFLAG_LOVESLAVE && LCSrandom(4))
		{
			addstrAlt(g.name, gamelog);
			addstrAlt(CONST_ONLY_STAYS_LOYAL_TO_THE_LCS_FOR, gamelog);
			addstrAlt(pool[g.hireid]->name, gamelog);
			addstrAlt(SINGLE_DOT, gamelog);
		}
		else
		{
			addstrAlt(g.name, gamelog);
			addstrAlt(CONST_ABANDONS_THE_LIBERAL_CRIME_SQUAD, gamelog);

			//Rat out contact
			int contact = getpoolcreature(g.hireid);
			if (contact >= 0)
			{
				criminalize(*pool[contact], LAWFLAG_RACKETEERING);
				pool[contact]->confessions++;
			}

			g.die();
			g.location = -1;
		}
	}
	else
	{
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_X_REMAINS_STRONG, gamelog);
	}
	gamelog.nextMessage();

	pressAnyKey();

	eraseAlt();

	return;
}

void laborcamp(DeprecatedCreature &g)
{
	int escaped = 0;
	string experience;
	// Escape attempt!
	if (g.hireid == -1 && !LCSrandom(3))
	{
		escaped = 2;
		experience = CONST_LEADS_THE_OPPRESSED_PRISONERS_AND_OVERWHELMS_THE_PRISON_GUARDS;
	}
	else if (g.skill_check(SKILL_DISGUISE, DIFFICULTY_HEROIC) && !LCSrandom(10))
	{
		escaped = 1;
		experience = CONST_WEARS_AN_ELECTRICIAN_S_OUTFIT_AND_RIDES_AWAY_WITH_SOME_CONTRACTORS;

		g.give_armor(getarmortype(tag_ARMOR_WORKCLOTHES), NULL);
	}
	else if (g.skill_check(SKILL_SECURITY, DIFFICULTY_CHALLENGING) && g.skill_check(SKILL_STEALTH, DIFFICULTY_HARD) && !LCSrandom(10))
	{
		escaped = 1;
		experience = CONST_PICKS_THE_LOCK_ON_THEIR_LEG_CHAINS_AND_THEN_SNEAKS_AWAY;
	}
	else if (g.skill_check(SKILL_SCIENCE, DIFFICULTY_HARD) && !LCSrandom(10))
	{
		escaped = 1;
		experience = CONST_CONSUMES_DRUGS_THAT_SIMULATE_DEATH_AND_IS_THROWN_OUT_WITH_THE_TRASH;
	}


	if (!escaped)experience = pickrandom(labor_camp_experiences);

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	moveAlt(8, 1);
	addstrAlt(g.name, gamelog);
	addstrAlt(experience, gamelog);
	gamelog.newline();

	pressAnyKey();

	moveAlt(10, 1);
	if (escaped)
	{
		int prison = g.location;
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_ESCAPED_FROM_PRISON, gamelog);
		addjuice(g, 50, 1000);
		criminalize(g, LAWFLAG_ESCAPED);
		g.location = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, g.location);

		if (escaped == 2)
		{
			int num_escaped = 0;
			for (int p = 0; p < len(pool); p++)
			{
				if (pool[p]->location == prison && !(pool[p]->flag & CREATUREFLAG_SLEEPER))
				{
					criminalize(*pool[p], LAWFLAG_ESCAPED);
					pool[p]->location = g.location;
					num_escaped++;
				}
			}
			if (num_escaped == 1)
			{
				gamelog.nextMessage();
				mvaddstrAlt(11, 1, CONST_ANOTHER_IMPRISONED_LCS_MEMBER_ALSO_GETS_OUT, gamelog);
			}
			else if (num_escaped > 1)
			{
				gamelog.nextMessage();
				mvaddstrAlt(11, 1, CONST_THE_LCS_WILL_RISE_AGAIN_MULTIPLE_LCS_MEMBERS_ESCAPE, gamelog);
			}
		}
	}
	else if (!LCSrandom(4))
	{
		if (g.get_attribute(ATTRIBUTE_HEALTH, true) > 1)
		{
			addstrAlt(g.name, gamelog);
			addstrAlt(CONST_IS_BADLY_HURT_IN_THE_PROCESS, gamelog);
			addjuice(g, -40, 0);
			addjuice(g, -10, -50);
		}
		else
		{
			addstrAlt(g.name, gamelog);
			addstrAlt(CONST_IS_FOUND_DEAD, gamelog);

			g.die();
			g.location = -1;
		}
	}
	else
	{
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_MANAGED_TO_AVOID_LASTING_INJURY, gamelog);
	}
	gamelog.nextMessage();

	pressAnyKey();

	eraseAlt();

	return;
}

void prisonscene(DeprecatedCreature &g)
{
	int escaped = 0;
	int effect = 0;
	string experience;
	if (g.juice + int(g.hireid == -1) * 300 > 500)
	{
		// Escape attempt!
		if (g.hireid == -1 && !LCSrandom(10))
		{
			escaped = 2;
			experience = CONST_LEADS_A_RIOT_WITH_DOZENS_OF_PRISONERS_CHANTING_THE_LCS_SLOGAN;
		}
		else if (g.skill_check(SKILL_COMPUTERS, DIFFICULTY_HARD) && !LCSrandom(5))
		{
			escaped = 2;
			experience = CONST_CODES_A_VIRUS_ON_A_SMUGGLED_PHONE_THAT_OPENS_ALL_THE_PRISON_DOORS;
		}
		else if (g.skill_check(SKILL_DISGUISE, DIFFICULTY_HARD) && !LCSrandom(5))
		{
			escaped = 1;
			experience = CONST_PUTS_ON_SMUGGLED_STREET_CLOTHES_AND_CALMLY_WALKS_OUT_OF_PRISON;
			g.give_armor(getarmortype(tag_ARMOR_CLOTHES), NULL);
		}
		else if (g.skill_check(SKILL_SECURITY, DIFFICULTY_CHALLENGING) && g.skill_check(SKILL_STEALTH, DIFFICULTY_CHALLENGING) && !LCSrandom(5))
		{
			escaped = 1;
			experience = CONST_JIMMIES_THE_CELL_DOOR_AND_CUTS_THE_OUTER_FENCE_IN_THE_DEAD_OF_NIGHT;
		}
		else if (g.skill_check(SKILL_SCIENCE, DIFFICULTY_AVERAGE) && g.skill_check(SKILL_HANDTOHAND, DIFFICULTY_EASY) && !LCSrandom(5))
		{
			escaped = 1;
			experience = CONST_INTENTIONALLY_ODS_ON_SMUGGLED_DRUGS_THEN_BREAKS_OUT_OF_THE_MEDICAL_WARD;
		}
	}


	if (escaped == 0)
	{
		if (g.attribute_check(ATTRIBUTE_HEART, DIFFICULTY_HARD)) {
			effect = 1;
			if (LCSrandom(2) > 0) experience = pickrandom(good_experiences);
			else experience = pickrandom(general_experiences);
		}
		else if (g.attribute_check(ATTRIBUTE_HEART, DIFFICULTY_CHALLENGING)) {
			effect = 0;
			experience = pickrandom(general_experiences);
		}
		else {
			effect = -1;
			if (LCSrandom(2) > 0) experience = pickrandom(bad_experiences);
			else experience = pickrandom(general_experiences);
		}
	}

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	moveAlt(8, 1);
	addstrAlt(g.name, gamelog);
	addstrAlt(experience, gamelog);
	gamelog.newline();

	pressAnyKey();

	moveAlt(10, 1);
	if (escaped)
	{
		int prison = g.location;
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_ESCAPED_FROM_PRISON, gamelog);
		addjuice(g, 50, 1000);
		criminalize(g, LAWFLAG_ESCAPED);
		g.location = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, g.location);

		if (escaped == 2)
		{
			int num_escaped = 0;
			for (int p = 0; p < len(pool); p++)
			{
				if (pool[p]->location == prison && !(pool[p]->flag & CREATUREFLAG_SLEEPER))
				{
					criminalize(*pool[p], LAWFLAG_ESCAPED);
					pool[p]->location = g.location;
					num_escaped++;
				}
			}
			if (num_escaped == 1)
			{
				gamelog.nextMessage();
				mvaddstrAlt(11, 1, CONST_ANOTHER_IMPRISONED_LCS_MEMBER_ALSO_GETS_OUT, gamelog);
			}
			else if (num_escaped > 1)
			{
				gamelog.nextMessage();
				mvaddstrAlt(11, 1, CONST_THE_LCS_WILL_RISE_AGAIN_MULTIPLE_LCS_MEMBERS_ESCAPE, gamelog);
			}
		}
	}
	else if (effect > 0)
	{
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_HAS_BECOME_A_MORE_HARDENED_JUICIER_CRIMINAL, gamelog);
		addjuice(g, 20, 1000);
	}
	else if (effect < 0)
	{
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_IS_KINDA_LOSING_IT_IN_HERE_JUICE_THAT_IS, gamelog);
		addjuice(g, -20, -30);
	}
	else
	{
		addstrAlt(g.name, gamelog);
		addstrAlt(CONST_SEEMS_TO_BE_MOSTLY_FINE_THOUGH, gamelog);
	}
	gamelog.nextMessage();

	pressAnyKey();

	eraseAlt();

	return;
}


/* monthly - advances a liberal's prison time or executes them */
//RETURNS IF SCREEN WAS ERASED
char prison(DeprecatedCreature &g)
{
	char showed = 0;

	// People not on death row or about to be released can have a scene in prison
	if (!g.deathpenalty && g.sentence != 1)
	{
		if (lawList[LAW_PRISONS] == 2)
		{
			//Liberal therapy.
			if (!LCSrandom(5)) reeducation(g);
		}
		else if (lawList[LAW_PRISONS] == -2)
		{
			//Labor camp.
			if (!LCSrandom(5)) laborcamp(g);
		}
		else
		{
			//Normal prison.
			if (!LCSrandom(5)) prisonscene(g);
		}
	}

	if (g.sentence > 0)
	{
		//COMMUTE DEATH IN RIGHT CLIMATE
		if (g.deathpenalty&&lawList[LAW_DEATHPENALTY] == 2)
		{
			eraseAlt();
			set_color_easy(WHITE_ON_BLACK);
			moveAlt(8, 1);
			addstrAlt(g.name, gamelog);
			addstrAlt(CONST_S_DEATH_SENTENCE_HAS_BEEN_COMMUTED_TO_LIFE, gamelog);
			moveAlt(9, 1);
			addstrAlt(CONST_DUE_TO_THE_ABOLITION_OF_THE_DEATH_PENALTY, gamelog);
			gamelog.nextMessage();

			pressAnyKey();

			g.sentence = -1;
			g.deathpenalty = 0;
			return 1;
		}

		//ADVANCE SENTENCE
		g.sentence--;
		if (g.sentence == 0)
		{
			//EXECUTE
			if (g.deathpenalty)
			{
				eraseAlt();
				set_color_easy(RED_ON_BLACK_BRIGHT);
				moveAlt(8, 1);
				addstrAlt(CONST_FOR_SHAME, gamelog);
				gamelog.newline();
				moveAlt(9, 1);
				addstrAlt(CONST_TODAY_THE_CONSERVATIVE_MACHINE_EXECUTED, gamelog);
				addstrAlt(g.name, gamelog);
				gamelog.record(singleSpace); //Log this for formatting purposes.
				moveAlt(10, 1);
				addstrAlt(CONST_X_BY_SPACE, gamelog);
				if (lawList[LAW_DEATHPENALTY] == -2)
					addstrAlt(pickrandom(cruel_and_unusual_execution_methods), gamelog);
				else if (lawList[LAW_DEATHPENALTY] == -1 || lawList[LAW_DEATHPENALTY] == 0)
					addstrAlt(pickrandom(standard_execution_methods), gamelog);
				else
					addstrAlt(pickrandom(supposedly_painless_execution_method), gamelog);
				addstrAlt(SINGLE_DOT, gamelog);

				pressAnyKey();

				//dejuice boss
				int boss = getpoolcreature(g.hireid);
				if (boss != -1)
				{
					gamelog.newline();
					set_color_easy(WHITE_ON_BLACK);
					moveAlt(12, 1);
					addstrAlt(pool[boss]->name, gamelog);
					addstrAlt(CONST_HAS_FAILED_THE_LIBERAL_CRIME_SQUAD, gamelog);
					gamelog.newline();
					moveAlt(14, 1);
					addstrAlt(CONST_IF_YOU_CAN_T_PROTECT_YOUR_OWN_PEOPLE_WHO_CAN_YOU_PROTECT, gamelog);

					pressAnyKey();

					addjuice(*pool[boss], -50, -50);
				}
				gamelog.nextMessage();

				g.die();
				stat_dead++;
				showed = 1;
			}
			//SET FREE
			else
			{
				eraseAlt();
				set_color_easy(WHITE_ON_BLACK);
				moveAlt(8, 1);
				addstrAlt(g.name, gamelog);
				addstrAlt(CONST_HAS_BEEN_RELEASED_FROM_PRISON, gamelog);
				gamelog.newline();
				moveAlt(9, 1);
				addstrAlt(CONST_NO_DOUBT_THERE_ARE_SOME_MENTAL_SCARS_BUT_THE_LIBERAL_IS_BACK, gamelog);
				gamelog.nextMessage();

				pressAnyKey();

				g.give_armor(getarmortype(tag_ARMOR_CLOTHES), NULL);
				// If their old base is no longer under LCS control, wander back to the
				// homeless shelter instead.
				if (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, g.base) < 0) {
					g.base = find_site_index_in_same_city(SITE_RESIDENTIAL_SHELTER, g.location);
				}
				g.location = g.base;
				showed = 1;
			}
		}
		//NOTIFY OF IMPENDING THINGS
		else if (g.sentence == 1)
		{
			if (g.deathpenalty)
			{
				eraseAlt();
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				moveAlt(8, 1);
				addstrAlt(g.name, gamelog);
				addstrAlt(CONST_IS_DUE_TO_BE_EXECUTED_NEXT_MONTH, gamelog);
				gamelog.nextMessage();

				pressAnyKey();

				showed = 1;
			}
			else
			{
				eraseAlt();
				set_color_easy(WHITE_ON_BLACK_BRIGHT);
				moveAlt(8, 1);
				addstrAlt(g.name, gamelog);
				addstrAlt(CONST_IS_DUE_TO_BE_RELEASED_NEXT_MONTH, gamelog);
				gamelog.nextMessage();

				pressAnyKey();

				showed = 1;
			}
		}
		else
		{
			if (g.deathpenalty)
			{
				eraseAlt();
				set_color_easy(YELLOW_ON_BLACK_BRIGHT);
				moveAlt(8, 1);
				addstrAlt(g.name, gamelog);
				addstrAlt(CONST_IS_DUE_TO_BE_EXECUTED_IN, gamelog);
				addstrAlt(g.sentence, gamelog);
				addstrAlt(CONST_MONTHS, gamelog);
				gamelog.nextMessage();

				pressAnyKey();

				showed = 1;
			}
		}
	}

	return showed;
}

  /* monthly - move a liberal to jail */
string commaAndPunctuation(const int typenum) {
	if (typenum > 1) return COMMA_SPACE;
	if (typenum == 1) return AND;
	if (typenum == 0) return singleDot;
	else return "";
}