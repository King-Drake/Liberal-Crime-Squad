

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

#include "../includes17.h"
#include "../constStringnews.h"
//TODO: Add logging for this file? --Addictgamer
void printRandomCableNewsName() {

	eraseAlt();
	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	string str = CONST_TONIGHT_ON_A_CABLE_NEWS_CHANNEL + pickrandom(cable_name) + singleSpace + pickrandom(cable_name_2) + CONST_SPACE_WITH_SPACE;
	string bname;
	bname = generate_name(GENDER_WHITEMALEPATRIARCH);
	str += bname;
	mvaddstrCenter(0, str);
	mvaddstrAlt(16, 20, bname);
	mvaddstrAlt(17, 20, pickrandom(cable_city).data());
	moveAlt(16, 41);
	addstrAlt(generate_name());
	mvaddstrAlt(17, 41, pickrandom(cable_city_2).data());
}
void printMultilineNewsStory(const vector<string> x) {

	set_color_easy(WHITE_ON_BLACK_BRIGHT);
	for (int i = 0; i < len(x); i++) {
		mvaddstrAlt(19 + i, 13, x[i]);
	}
}


Deprecatednewsstoryst* ccs_strikes_story()
{
	Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
	// Chance of CCS squad wipe
	if (LCSrandom(10))ns->type = NEWSSTORY_CCS_SITE;
	else ns->type = NEWSSTORY_CCS_KILLED_SITE;
	// Chance of positive CCS story
	ns->positive = true;
	do {
		ns->loc = LCSrandom(LocationsPool::getInstance().lenpool());
	} while (LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, ns->loc) != -1);
	return ns;
}
Deprecatednewsstoryst* ccs_fbi_raid_story()
{
	Deprecatednewsstoryst* ns = new Deprecatednewsstoryst;
	ns->type = NEWSSTORY_CCS_DEFEATED;
	ns->priority = 8000;
	endgamestate = ENDGAME_CCS_DEFEATED;
	// arrest or kill ccs sleepers
	CreaturePool::getInstance().arrestOrKillCCSSleepers();
	LocationsPool::getInstance().hideCCSSafehouses();
	// go militarized police
	change_public_opinion(VIEW_POLICEBEHAVIOR, -20);
	return ns;
}
Deprecatednewsstoryst* ccs_exposure_story()
{
	Deprecatednewsstoryst* ns = new Deprecatednewsstoryst;
	ns->type = NEWSSTORY_CCS_NOBACKERS;
	ns->priority = 8000;
	ccsexposure = CCSEXPOSURE_NOBACKERS;
	// arrest seventeen representatives and eight senators
	int arrestsleft = 8;
	for (int i = 0; i < SENATENUM; i++)
	{
		if ((senate[i] == -2 || senate[i] == -1) && !LCSrandom(4))
		{
			senate[i] = ALIGN_ELITELIBERAL;
			arrestsleft--;
			if (arrestsleft <= 0) break;
		}
	}
	arrestsleft = 17;
	for (int i = 0; i < HOUSENUM; i++)
	{
		if ((house[i] == -2 || house[i] == -1) && !LCSrandom(4))
		{
			house[i] = ALIGN_ELITELIBERAL;
			arrestsleft--;
			if (arrestsleft <= 0) break;
		}
	}
	// change police regulation issue to be more liberal
	lawList[LAW_POLICEBEHAVIOR] += 2;
	if (lawList[LAW_POLICEBEHAVIOR] > ALIGN_ELITELIBERAL)
		lawList[LAW_POLICEBEHAVIOR] = ALIGN_ELITELIBERAL;
	change_public_opinion(VIEW_POLICEBEHAVIOR, 50);
	change_public_opinion(VIEW_CONSERVATIVECRIMESQUAD, 50);
	return ns;
}
void advance_ccs_defeat_storyline()
{
	switch (ccsexposure)
	{
	default:
	case CCSEXPOSURE_NONE:
	case CCSEXPOSURE_LCSGOTDATA:
		break;
	case CCSEXPOSURE_EXPOSED:
		newsstory.push_back(ccs_exposure_story());
		break;
	case CCSEXPOSURE_NOBACKERS:
		newsstory.push_back(ccs_fbi_raid_story());
		break;
	}
}
Deprecatednewsstoryst* new_major_event()
{
	Deprecatednewsstoryst *ns = new Deprecatednewsstoryst;
	ns->type = NEWSSTORY_MAJOREVENT;
	while (true)
	{
		ns->view = LCSrandom(VIEWNUM - 3);
		ns->positive = LCSrandom(2);
		// Skip issues that we have no news stories for
		if (ns->view == VIEW_IMMIGRATION)continue;
		if (ns->view == VIEW_DRUGS)continue;
		if (ns->view == VIEW_MILITARY)continue;
		if (ns->view == VIEW_CIVILRIGHTS)continue;
		if (ns->view == VIEW_TORTURE)continue;
		//if(ns->view==VIEW_POLITICALVIOLENCE)continue;
		// News stories that don't apply when the law is extreme -- covering
		// nuclear power when it's banned, police corruption when it doesn't
		// exist, out of control pollution when it's under control, etc.
		if (ns->positive) {
			if (ns->view == VIEW_WOMEN && lawList[LAW_ABORTION] == -2)continue; // Abortion banned
			if (ns->view == VIEW_DEATHPENALTY && lawList[LAW_DEATHPENALTY] == 2)continue; // Death penalty banned
			if (ns->view == VIEW_NUCLEARPOWER && lawList[LAW_NUCLEARPOWER] == 2)continue; // Nuclear power banned
			if (ns->view == VIEW_ANIMALRESEARCH && lawList[LAW_ANIMALRESEARCH] == 2)continue; // Animal research banned
			if (ns->view == VIEW_POLICEBEHAVIOR && lawList[LAW_POLICEBEHAVIOR] == 2)continue; // Police corruption eliminated
			if (ns->view == VIEW_INTELLIGENCE && lawList[LAW_PRIVACY] == 2)continue; // Privacy rights respected
			if (ns->view == VIEW_SWEATSHOPS && lawList[LAW_LABOR] == 2)continue; // Sweatshops nonexistant
			if (ns->view == VIEW_POLLUTION && lawList[LAW_POLLUTION] >= 1)continue; // Pollution under control
			if (ns->view == VIEW_CORPORATECULTURE && lawList[LAW_CORPORATE] == 2)continue; // Regulation controls corporate corruption
			if (ns->view == VIEW_CEOSALARY && lawList[LAW_CORPORATE] == 2)continue; // CEOs aren't rich
		}
		else {
			if (ns->view == VIEW_WOMEN && lawList[LAW_ABORTION] < 2)continue; // Partial birth abortion banned
			if (ns->view == VIEW_AMRADIO && lawList[LAW_FREESPEECH] == -2)continue; // AM Radio is censored to oblivion
			if (ns->view == VIEW_ANIMALRESEARCH && lawList[LAW_ANIMALRESEARCH] == 2)continue; // Animal research banned
		}
		break;
	}
	if (ns->positive) change_public_opinion(ns->view, 20, 0);
	else change_public_opinion(ns->view, -20, 0);
	public_interest[ns->view] += 50;
	return ns;
}
const int MAJOR_NEWS_RATE = 60;
void generate_random_event_news_stories()
{
	//Conservative Crime Squad Strikes!
	if (endgamestate < ENDGAME_CCS_DEFEATED &&
		LCSrandom(30) < endgamestate)
	{
		newsstory.push_back(ccs_strikes_story());
	}
	// The slow defeat of the conservative crime squad...
	if (endgamestate < ENDGAME_CCS_DEFEATED &&
		ccsexposure >= CCSEXPOSURE_EXPOSED &&
		!LCSrandom(60))
	{
		advance_ccs_defeat_storyline();
	}
	// Random major event news stories
	if (!LCSrandom(MAJOR_NEWS_RATE)) {
		newsstory.push_back(new_major_event());
	}
}
void clean_up_empty_news_stories()
{
	// Delete stories that have no content or shouldn't be reported on
	for (int n = len(newsstory) - 1; n >= 0; n--)
	{
		// Squad site action stories without crimes
		if (newsstory[n]->type == NEWSSTORY_SQUAD_SITE &&
			!len(newsstory[n]->crime))
		{
			delete_and_remove(newsstory, n);
			continue;
		}
		// Police killed stories without police being killed
		if (newsstory[n]->type == NEWSSTORY_CARTHEFT ||
			newsstory[n]->type == NEWSSTORY_NUDITYARREST ||
			newsstory[n]->type == NEWSSTORY_WANTEDARREST ||
			newsstory[n]->type == NEWSSTORY_DRUGARREST ||
			newsstory[n]->type == NEWSSTORY_GRAFFITIARREST ||
			newsstory[n]->type == NEWSSTORY_BURIALARREST)
		{
			char conf = 0;
			for (int c = 0; c < len(newsstory[n]->crime); c++)
			{
				if (newsstory[n]->crime[c] == CRIME_KILLEDSOMEBODY)
				{
					conf = 1;
					break;
				}
			}
			if (!conf)
			{
				delete_and_remove(newsstory, n);
				continue;
			}
		}
		// Sieges that aren't police actions
		if ((newsstory[n]->type == NEWSSTORY_SQUAD_ESCAPED ||
			newsstory[n]->type == NEWSSTORY_SQUAD_FLEDATTACK ||
			newsstory[n]->type == NEWSSTORY_SQUAD_DEFENDED ||
			newsstory[n]->type == NEWSSTORY_SQUAD_BROKESIEGE ||
			newsstory[n]->type == NEWSSTORY_SQUAD_KILLED_SIEGEATTACK ||
			newsstory[n]->type == NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE) &&
			newsstory[n]->siegetype != SIEGE_POLICE)
		{
			delete_and_remove(newsstory, n);
			continue;
		}
	}
}
int bonusPriority(const short type, const long loc, long priority) {
	switch (type)
	{
	case NEWSSTORY_SQUAD_KILLED_SITE:
	case NEWSSTORY_SQUAD_KILLED_SIEGEATTACK:
	case NEWSSTORY_SQUAD_ESCAPED:
		priority += 10 + attitude[VIEW_LIBERALCRIMESQUAD] / 3;
		break;
	case NEWSSTORY_SQUAD_FLEDATTACK:
	case NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE:
		priority += 15 + attitude[VIEW_LIBERALCRIMESQUAD] / 3;
		break;
	case NEWSSTORY_SQUAD_DEFENDED:
		priority += 30 + attitude[VIEW_LIBERALCRIMESQUAD] / 3;
		break;
	case NEWSSTORY_SQUAD_BROKESIEGE:
		priority += 45 + attitude[VIEW_LIBERALCRIMESQUAD] / 3;
		break;
	default:
		// Suppress actions at CCS safehouses
		if (loc != -1 &&
			LocationsPool::getInstance().get_specific_integer(INT_GETRENTINGTYPE, loc) == RENTING_CCS)
		{
			priority = 0;
		}
		break;
	}
	return priority;
}
int moreBonusPriority(const short type, const long loc, long priority) {

	switch (LocationsPool::getInstance().getLocationType(loc))
	{
		// Not even reported
	case SITE_BUSINESS_CRACKHOUSE:
		if (type == NEWSSTORY_SQUAD_KILLED_SITE ||
			type == NEWSSTORY_SQUAD_SITE)
		{
			priority = 0;
			break;
		}
		// Nobody cares
	case SITE_RESIDENTIAL_TENEMENT:
		priority /= 8;
		break;
		// Normal priority
	case SITE_RESIDENTIAL_SHELTER:
	case SITE_INDUSTRY_WAREHOUSE:
	case SITE_RESIDENTIAL_BOMBSHELTER:
	case SITE_DOWNTOWN:
	case SITE_COMMERCIAL:
	case SITE_UDISTRICT:
	case SITE_OUTOFTOWN:
	case SITE_INDUSTRIAL:
	case SITE_RESIDENTIAL_APARTMENT:
	case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
	case SITE_LABORATORY_COSMETICS:
	case SITE_LABORATORY_GENETIC:
	case SITE_HOSPITAL_CLINIC:
	case SITE_HOSPITAL_UNIVERSITY:
	case SITE_INDUSTRY_SWEATSHOP:
	case SITE_INDUSTRY_POLLUTER:
	case SITE_BUSINESS_PAWNSHOP:
	case SITE_BUSINESS_JUICEBAR:
	case SITE_BUSINESS_CIGARBAR:
	case SITE_BUSINESS_LATTESTAND:
	case SITE_BUSINESS_VEGANCOOP:
	case SITE_BUSINESS_INTERNETCAFE:
	case SITE_BUSINESS_DEPTSTORE:
	case SITE_BUSINESS_HALLOWEEN:
	case SITE_BUSINESS_BARANDGRILL:
	case SITE_BUSINESS_ARMSDEALER:
	case SITE_BUSINESS_CARDEALERSHIP:
	case SITE_OUTDOOR_PUBLICPARK:
	case SITE_OUTDOOR_BUNKER:
	default:
		break;
		// WOAH OMG
	case SITE_INDUSTRY_NUCLEAR:
	case SITE_GOVERNMENT_POLICESTATION:
	case SITE_GOVERNMENT_COURTHOUSE:
	case SITE_GOVERNMENT_PRISON:
	case SITE_GOVERNMENT_INTELLIGENCEHQ:
	case SITE_GOVERNMENT_ARMYBASE:
	case SITE_GOVERNMENT_FIRESTATION:
	case SITE_CORPORATE_HEADQUARTERS:
	case SITE_CORPORATE_HOUSE:
	case SITE_MEDIA_AMRADIO:
	case SITE_MEDIA_CABLENEWS:
	case SITE_BUSINESS_BANK:
	case SITE_GOVERNMENT_WHITE_HOUSE:
		priority *= 2;
		break;
	}
	return priority;
}
/* news - determines the priority of a news story */
void setpriority(Deprecatednewsstoryst &ns)
{
	// Priority is set differently based on the type of the news story
	switch (ns.type)
	{
		// Major events always muscle to the front page by having a very high priority
	case NEWSSTORY_MAJOREVENT:
		ns.priority = 30000;
		break;
		// LCS-related news stories are more important if they involve lots of headline-grabbing
		// crimes
	case NEWSSTORY_SQUAD_SITE:
	case NEWSSTORY_SQUAD_ESCAPED:
	case NEWSSTORY_SQUAD_FLEDATTACK:
	case NEWSSTORY_SQUAD_DEFENDED:
	case NEWSSTORY_SQUAD_BROKESIEGE:
	case NEWSSTORY_SQUAD_KILLED_SIEGEATTACK:
	case NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE:
	case NEWSSTORY_SQUAD_KILLED_SITE:
	case NEWSSTORY_CARTHEFT:
	case NEWSSTORY_NUDITYARREST:
	case NEWSSTORY_WANTEDARREST:
	case NEWSSTORY_DRUGARREST:
	case NEWSSTORY_GRAFFITIARREST:
	case NEWSSTORY_BURIALARREST:
	{
		ns.priority = 0;
		int crime[CRIMENUM];
		memset(crime, 0, CRIMENUM * sizeof(int));
		// Record all the crimes in this story
		for (int c = 0; c < len(ns.crime); c++)
			crime[ns.crime[c]]++;
		// Cap publicity for more than ten repeats of an action of some type
		if (crime[CRIME_STOLEGROUND] > 10) crime[CRIME_STOLEGROUND] = 10;
		if (crime[CRIME_BROKEDOWNDOOR] > 10) crime[CRIME_BROKEDOWNDOOR] = 10;
		if (crime[CRIME_ATTACKED_MISTAKE] > 10) crime[CRIME_ATTACKED_MISTAKE] = 10;
		if (crime[CRIME_ATTACKED] > 10) crime[CRIME_ATTACKED] = 10;
		if (crime[CRIME_BREAK_SWEATSHOP] > 10) crime[CRIME_BREAK_SWEATSHOP] = 10;
		if (crime[CRIME_BREAK_FACTORY] > 10) crime[CRIME_BREAK_FACTORY] = 10;
		if (crime[CRIME_FREE_RABBITS] > 10) crime[CRIME_FREE_RABBITS] = 10;
		if (crime[CRIME_FREE_BEASTS] > 10) crime[CRIME_FREE_BEASTS] = 10;
		if (crime[CRIME_TAGGING] > 10) crime[CRIME_TAGGING] = 10;
		// Increase news story priority based on the number of instances of
		// various crimes, scaled by a factor dependant on the crime
		// Unique site crimes
		ns.priority += crime[CRIME_BANKVAULTROBBERY] * 100;
		ns.priority += crime[CRIME_BANKSTICKUP] * 100;
		ns.priority += crime[CRIME_SHUTDOWNREACTOR] * 100;
		ns.priority += crime[CRIME_HACK_INTEL] * 100;
		ns.priority += crime[CRIME_ARMORY] * 100;
		ns.priority += crime[CRIME_HOUSE_PHOTOS] * 100;
		ns.priority += crime[CRIME_CORP_FILES] * 100;
		ns.priority += crime[CRIME_PRISON_RELEASE] * 50;
		ns.priority += crime[CRIME_JURYTAMPERING] * 30;
		ns.priority += crime[CRIME_POLICE_LOCKUP] * 30;
		ns.priority += crime[CRIME_COURTHOUSE_LOCKUP] * 30;
		ns.priority += crime[CRIME_BANKTELLERROBBERY] * 30;
		// Common site crimes
		ns.priority += crime[CRIME_KILLEDSOMEBODY] * 30;
		ns.priority += crime[CRIME_FREE_BEASTS] * 12;
		ns.priority += crime[CRIME_BREAK_SWEATSHOP] * 8;
		ns.priority += crime[CRIME_BREAK_FACTORY] * 8;
		ns.priority += crime[CRIME_FREE_RABBITS] * 8;
		ns.priority += crime[CRIME_ATTACKED_MISTAKE] * 7;
		ns.priority += crime[CRIME_ATTACKED] * 4;
		ns.priority += crime[CRIME_TAGGING] * 2;
		ns.priority += crime[CRIME_VANDALISM] * 2;
		//ns.priority+=crime[CRIME_STOLEGROUND ];
		//ns.priority+=crime[CRIME_BROKEDOWNDOOR ];
		// Set story's political and violence levels for determining whether
		// a story becomes positive or negative
		if (ns.claimed) ns.politics_level = 5;
		else ns.politics_level = 0;
		ns.politics_level += crime[CRIME_SHUTDOWNREACTOR] * 100;
		ns.politics_level += crime[CRIME_HACK_INTEL] * 100;
		ns.politics_level += crime[CRIME_HOUSE_PHOTOS] * 100;
		ns.politics_level += crime[CRIME_CORP_FILES] * 100;
		ns.politics_level += crime[CRIME_PRISON_RELEASE] * 50;
		ns.politics_level += crime[CRIME_POLICE_LOCKUP] * 30;
		ns.politics_level += crime[CRIME_COURTHOUSE_LOCKUP] * 30;
		ns.politics_level += crime[CRIME_FREE_BEASTS] * 10;
		ns.politics_level += crime[CRIME_BREAK_SWEATSHOP] * 10;
		ns.politics_level += crime[CRIME_BREAK_FACTORY] * 10;
		ns.politics_level += crime[CRIME_FREE_RABBITS] * 10;
		ns.politics_level += crime[CRIME_VANDALISM] * 5;
		ns.politics_level += crime[CRIME_TAGGING] * 3;
		ns.violence_level = 0;
		ns.violence_level += crime[CRIME_ARMORY] * 100;
		ns.violence_level += crime[CRIME_KILLEDSOMEBODY] * 20;
		ns.violence_level += crime[CRIME_ATTACKED_MISTAKE] * 12;
		ns.violence_level += crime[CRIME_ATTACKED] * 4;
		// Add additional priority based on the type of news story
		// and how high profile the LCS is
		ns.priority = bonusPriority(ns.type, ns.loc, ns.priority);

		// Double profile if the squad moved out in full battle colors
		if (ns.claimed == 2) ns.priority *= 2;
		// Modify notability by location
		if (ns.loc != -1)
		{
			ns.priority = moreBonusPriority(ns.type, ns.loc, ns.priority);
		}
		// Cap news priority, in part so it can't displace major news stories
		if (ns.priority > 20000) ns.priority = 20000;
		break;
	}
	case NEWSSTORY_KIDNAPREPORT:
		// Kidnappings are higher priority if they're an archconservative
		ns.priority = 20;
		if (ns.cr->type == CREATURE_CORPORATE_CEO ||
			ns.cr->type == CREATURE_RADIOPERSONALITY ||
			ns.cr->type == CREATURE_NEWSANCHOR ||
			ns.cr->type == CREATURE_SCIENTIST_EMINENT ||
			ns.cr->type == CREATURE_JUDGE_CONSERVATIVE) ns.priority = 40;
		break;
	case NEWSSTORY_MASSACRE:
		// More people massacred, higher priority (I think; not verified ns.crime[1] is people present)
		ns.priority = 10 + ns.crime[1] * 5;
		break;
	case NEWSSTORY_CCS_SITE:
	case NEWSSTORY_CCS_KILLED_SITE:
		// CCS actions loosely simulate LCS actions; here it adds some
		// random site crimes to the story and increases the
		// priority accordingly
		ns.crime.push_back(CRIME_BROKEDOWNDOOR);
		ns.priority = 1;
		ns.politics_level += 20;
		if (ns.positive == 0)
		{
			ns.crime.push_back(CRIME_ATTACKED_MISTAKE);
			ns.priority += 7;
			ns.violence_level += 12;
		}
		ns.crime.push_back(CRIME_ATTACKED);
		ns.priority += 4 * (LCSrandom(10) + 1);
		ns.violence_level += LCSrandom(10) * 4;
		if (LCSrandom(endgamestate + 1))
		{
			ns.crime.push_back(CRIME_KILLEDSOMEBODY);
			ns.priority += LCSrandom(10) * 30;
			ns.violence_level += LCSrandom(10) * 20;
		}
		if (LCSrandom(endgamestate + 1))
		{
			ns.crime.push_back(CRIME_STOLEGROUND);
			ns.priority += LCSrandom(10);
		}
		if (!LCSrandom(endgamestate + 4))
		{
			ns.crime.push_back(CRIME_BREAK_FACTORY);
			ns.priority += LCSrandom(10) * 2;
			ns.politics_level += LCSrandom(10) * 10;
		}
		if (LCSrandom(2))
		{
			ns.crime.push_back(CRIME_CARCHASE);
		}
		break;
	case NEWSSTORY_CCS_DEFENDED:
	case NEWSSTORY_CCS_KILLED_SIEGEATTACK:
		ns.priority = 40 + attitude[VIEW_LIBERALCRIMESQUAD] / 3;
		break;
	}
}
void assign_page_numbers_to_newspaper_stories()
{
	for (int n = len(newsstory) - 1; n >= 0; n--)
	{
		setpriority(*newsstory[n]);
		// Suppress squad actions that aren't worth a story
		if (newsstory[n]->type == NEWSSTORY_SQUAD_SITE &&
			((newsstory[n]->priority < 50 &&
				newsstory[n]->claimed == 0) ||
				newsstory[n]->priority < 4))
		{
			delete_and_remove(newsstory, n);
			continue;
		}
		newsstory[n]->page = -1;
	}
	char acted;
	int curpage = 1, curguardianpage = 1;
	do
	{
		acted = 0;
		// Sort the major newspapers
		int maxn = -1, maxp = -1;
		for (int n = 0; n < len(newsstory); n++)
		{
			if (newsstory[n]->priority > maxp&&
				newsstory[n]->page == -1)
			{
				maxn = n;
				maxp = newsstory[n]->priority;
			}
		}
		if (maxn != -1)
		{
			if (newsstory[maxn]->priority < 30 && curpage == 1) curpage = 2;
			if (newsstory[maxn]->priority < 25 && curpage < 3) curpage = 3 + LCSrandom(2);
			if (newsstory[maxn]->priority < 20 && curpage < 5) curpage = 5 + LCSrandom(5);
			if (newsstory[maxn]->priority < 15 && curpage < 10) curpage = 10 + LCSrandom(10);
			if (newsstory[maxn]->priority < 10 && curpage < 20) curpage = 20 + LCSrandom(10);
			if (newsstory[maxn]->priority < 5 && curpage < 30) curpage = 30 + LCSrandom(20);
			newsstory[maxn]->page = curpage;
			newsstory[maxn]->guardianpage = curguardianpage;
			curpage++;
			curguardianpage++;
			acted = 1;
		}
	} while (acted);
}
/* news - draws the specified block of text to the screen */
void displaynewsstory(const string story, const short *storyx_s, const short *storyx_e, int y) {
	vector<char *> text;
	vector<char> centered;
	int curpos = 0;
	char addstring[500];
	int cury = y;
	char endparagraph = 0;
	char iscentered = 0;
	int i = 0;
	while (curpos < len(story) && cury < 25)
	{
		char content = 0;
		int totalwidth = 0;
		int addstrcur = 0;
		int length = storyx_e[cury] - storyx_s[cury] + 1;
		if (length == 0) { cury++; if (endparagraph > 0)endparagraph--; continue; }
		for (i = curpos; i < len(story); i++)
		{
			if (story[i] == '&'&&story[i + 1] != '&')
			{
				i++;
				if (story[i] == 'c')iscentered = 1;
				if (story[i] == 'r')
				{
					content = 1;
					i++;
					addstrcur += 1;
					addstring[addstrcur - 1] = ' ';
					addstring[addstrcur] = '\x0';
					endparagraph = 1;
					break;
				}
			}
			else
			{
				content = 1;
				if (story[i] == '&')i++;
				addstring[addstrcur] = story[i];
				addstring[addstrcur + 1] = '\x0';
				totalwidth++;
				if (totalwidth > length)
				{
					while (story[i] != ' ') i--, addstrcur--;
					while (story[i] == ' ') i++;
					addstring[addstrcur] = '\x0';
					break;
				}
				addstrcur++;
			}
		}
		if (i == len(story)) addstring[addstrcur] = '\x0';
		if (len(addstring) && content)
		{
			int words = 0;
			char silent = 1;
			vector<int> spacex;
			for (int s2 = 0; s2 < len(addstring); s2++)
			{
				if (addstring[s2] == ' ')
				{
					if (!silent)
					{
						silent = 1;
						words++;
						spacex.push_back(s2);
					}
				}
				else
				{
					if (silent)
					{
						words++;
						silent = 0;
					}
				}
			}
			while (!endparagraph&&words > 1 && len(addstring) < length && !iscentered)
			{
				int csp = pickrandom(spacex);
				for (int x = 0; x < len(spacex); x++)
					if (spacex[x] > csp) spacex[x]++;
				int l = len(addstring);
				for (int s = l + 1; s > csp; s--)
					addstring[s] = addstring[s - 1];
			}
			char *news = new char[len(addstring) + 1];
			strcpy(news, addstring);
			text.push_back(news);
			centered.push_back(iscentered);
			cury++;
			if (endparagraph > 0)
				endparagraph--, iscentered = 0;
		}
		curpos = i;
	}
	set_color_easy(BLACK_ON_WHITE);
	for (int t = 0; t < len(text); t++)
	{
		if (y + t >= 25) break;
		if (text[t][len(text[t]) - 1] == ' ') // remove trailing space
			text[t][len(text[t]) - 1] = '\x0'; // (necessary for proper centering and to not overwrite borders around an ad)
		if (centered[t])
			moveAlt(y + t, ((storyx_s[y + t] + storyx_e[y + t] - len(text[t]) + 1) >> 1));
		else moveAlt(y + t, storyx_s[y + t]);
		addstrAlt(text[t]);
		delete[] text[t];
	}
	text.clear();
}
int randomBox() {
	return pickrandom(randombox);
}
string defaultAdFour() {
	string ad;

	ad = ampersandC + CONST_QUALITY_PRE_OWNED + ampersandR;
	ad += ampersandC + CONST_VEHICLES_R;
	ad += ampersandC;
	ad += tostring(year - LCSrandom(15));
	ad += singleSpace;
	// strcat(ad,cartype);
	//TODO: leading zeros, etc.
	ad += CONST_X_LEXUS_GS_ + ampersandR;
	ad += ampersandC + CONST_SEDAN_4D + ampersandR;
	ad += ampersandC + CONST_ONLY;
	ad += tostring(LCSrandom(16) + 15);
	ad += ampersandR;

	return ad;

}
string defaultAdTwo() {
	string ad;
	ad = ampersandC + CONST_FINE_LEATHER_CHAIRS + ampersandR + ampersandR;
	ad += ampersandC + CONST_SPECIAL_PURCHASE + ampersandR;
	ad += ampersandC + CONST_NOW;
	ad += LCSrandom(201) + 400;
	ad += ampersandR;
	return ad;
}
string defaultAdSix() {
	string ad;

	ad = ampersandC;
	ad += pickrandom(personalAds);
	ad += ampersandR + ampersandR;
	ad += ampersandC;
	ad += sexdesc();
	ad += singleSpace;
	ad += sexwho();
	ad += singleSpace;
	ad += sexseek();
	ad += ampersandR;
	ad += ampersandC;
	ad += sextype();
	ad += CONST_W;
	ad += sexwho();
	ad += ampersandR;

	return ad;

}
string defaultAdLGTwo() {
	string ad;

	ad = ampersandC + CONST_LIBERAL_DEFENSE_LAWYER + ampersandR;
	ad += ampersandC;
	ad += tostring(LCSrandom(11) + 20);
	ad += CONST_YEARS_EXPERIENCE + ampersandR + ampersandR;
	ad += ampersandC + CONST_CALL_TODAY + ampersandR;

	return ad;
}
string defaultAdLGSix() {
	string ad;

	ad = ampersandC;
	ad += pickrandom(personalAdsLG);
	ad += ampersandR + ampersandR;
	ad += ampersandC;
	ad += sexdesc();
	ad += singleSpace;
	ad += sexwho();
	ad += singleSpace;
	ad += sexseek();
	ad += ampersandR;
	ad += ampersandC;
	ad += sextype();
	ad += CONST_W;
	ad += sexwho();
	ad += ampersandR;

	return ad;

}
void displaysinglead(const bool liberalguardian, char addplace[2][3], short* storyx_s, short* storyx_e)
{
	int x, y;
	do x = LCSrandom(2), y = LCSrandom(3); while (addplace[x][y]);
	char choice = LCSrandom(6) + 1; // choose an ad from 1 to 6 that isn't already taken
	for (int x2 = 0; x2 < 2; x2++) for (int y2 = 0; y2 < 3; y2++) // loop thru ad places to see ads already up
		if (addplace[x2][y2] == choice) choice = LCSrandom(6) + 1, x2 = 0, y2 = -1; // choose again and restart loop if already taken
	addplace[x][y] = choice; // we got an ad chosen that isn't a duplicate
	int sx = 0, ex = 0, sy = 0, ey = 0;
	if (x == 0) sx = 0, ex = 23 + LCSrandom(4);
	if (x == 1) sx = 57 - LCSrandom(4), ex = 79;
	if (y == 0) sy = 2, ey = 9;
	if (y == 1) sy = 10, ey = 17;
	if (y == 2) sy = 18, ey = 24;
	int ch = randomBox();
	for (y = sy; y <= ey; y++)
	{
		if (storyx_s[y] < ex&&ex < 43) storyx_s[y] = ex + 2;
		if (storyx_e[y] > sx&&sx > 43) storyx_e[y] = sx - 2;
		if (ey == 9 && y == 9) continue;
		if (ey == 17 && y == 17) continue;
		for (x = sx; x <= ex; x++)
			if (y == sy || y == 8 || y == 16 || y == 24 || x == sx || x == ex)
				mvaddchAlt(y, x, ch);
	}
	//AD CONTENT
	{
		short storyx_s[25], storyx_e[25];
		for (int it2 = 0; it2 < 25; it2++) storyx_s[it2] = 40, storyx_e[it2] = 40;
		for (int it2 = sy + 1; it2 <= ey - 1; it2++) storyx_s[it2] = sx + 1, storyx_e[it2] = ex - 1;
		string ad;
		if (!liberalguardian)
		{ // regular newspaper (not Liberal Guardian)
			switch (choice) // should be 6 choices from 1 to 6
			{ // location[]->name?
			case 1:
			case 3:
			case 5:
			default:
				ad = "";
				for (string str : pickrandom(adList)) {
					ad += str;
				}
				break;
			case 2:
				ad = defaultAdTwo();
				break;
			case 4:
				ad = defaultAdFour();
				break;
			case 6:
				ad = defaultAdSix();

				break;

			}
		}
		else
		{ // Liberal Guardian Ads
			switch (choice) // should be 6 choices from 1 to 6
			{
			case 1:
			case 3:
			case 4:
			case 5:
			default:
				ad = "";
				for (string str : pickrandom(adListB)) {
					ad += str;
				}
				break;

			case 2:
				ad = defaultAdLGTwo();
				break;
			case 6:
				ad = defaultAdLGSix();
				break;
			}
		}
		displaynewsstory(ad, storyx_s, storyx_e, sy + 1);
	}
}
void displayads(const Deprecatednewsstoryst ns, const bool liberalguardian, short* storyx_s, short* storyx_e)
{
	int adnumber = 0;
	if (!liberalguardian)
	{
		if (ns.page >= 10)adnumber++;
		if (ns.page >= 20)adnumber += LCSrandom(2) + 1;
		if (ns.page >= 30)adnumber += LCSrandom(2) + 1;
		if (ns.page >= 40)adnumber += LCSrandom(2) + 1;
		if (ns.page >= 50)adnumber += LCSrandom(2) + 1;
	}
	else
	{
		if (ns.guardianpage >= 2)adnumber++;
		if (ns.guardianpage >= 3)adnumber += LCSrandom(2) + 1;
		if (ns.guardianpage >= 4)adnumber += LCSrandom(2) + 1;
		if (ns.guardianpage >= 5)adnumber += LCSrandom(2) + 1;
		if (ns.guardianpage >= 6)adnumber += LCSrandom(2) + 1;
	}
	char addplace[2][3] = { { 0,0,0 },{ 0,0,0 } };
	for (adnumber = (adnumber > 6 ? 6 : adnumber); adnumber > 0; adnumber--)
		displaysinglead(liberalguardian, addplace, storyx_s, storyx_e);
}
string storyPlaceName(string &placename, const char location_type, const bool liberalguardian, const bool ccs) {
	string story;
	switch (location_type)
	{
	case SITE_CITY_SEATTLE:
	case SITE_CITY_LOS_ANGELES:
	case SITE_CITY_NEW_YORK:
	case SITE_CITY_CHICAGO:
	case SITE_CITY_DETROIT:
	case SITE_CITY_ATLANTA:
	case SITE_CITY_MIAMI:
	case SITE_CITY_WASHINGTON_DC:
		story += CONST_IN;
		break;
	case SITE_DOWNTOWN:
	case SITE_COMMERCIAL:
	case SITE_UDISTRICT:
	case SITE_OUTOFTOWN:
	case SITE_INDUSTRIAL:
	case SITE_TRAVEL:
		if (placename == tag_Shopping)
		{
			placename = CONST_SHOPPING_MALL;
			story += CONST_AT_THE;
		}
		else if (placename == tag_Travel)
		{
			placename = CONST_TRAVEL_AGENCY;
			story += CONST_AT_THE;
		}
		else if (placename == tag_Outskirts_and_Orange_County)
		{
			placename = CONST_ORANGE_COUNTY;
			story += CONST_IN;
		}
		else if (placename == tag_Brooklyn_and_Queens)
		{
			placename = tag_Long_Island;
			story += CONST_ON;
		}
		else if (placename == tag_Greater_Hollywood)
		{
			placename = tag_Hollywood;
			story += CONST_IN;
		}
		else if (placename == tag_Manhattan_Island)
		{
			placename = tag_Manhattan;
			story += CONST_IN;
		}
		else if (placename == tag_Arlington)
			story += CONST_IN;
		else if (placename == tag_National_Mall)
			story += CONST_ON_THE;
		else if (placename != tag_Downtown)
			story += CONST_IN_THE;
		break;
	case SITE_BUSINESS_PAWNSHOP:
		if (placename.find(CONST_APOSTROPHE_S) != string::npos)
		{
			story += CONST_AT_SPACE;
			if (liberalguardian && !ccs)story += CONST_THE_NOTORIOUS;
		}
		else
		{
			story += CONST_AT_THE;
			if (liberalguardian && !ccs)story += CONST_NOTORIOUS;
		}
		break;
	case SITE_RESIDENTIAL_APARTMENT:
	case SITE_BUSINESS_CARDEALERSHIP:
	case SITE_BUSINESS_DEPTSTORE:
	case SITE_OUTDOOR_PUBLICPARK:
		story += CONST_AT_SPACE;
		if (liberalguardian && !ccs)story += CONST_THE_NOTORIOUS;
		break;
	default:
		story += CONST_AT_THE;
		if (liberalguardian && !ccs)story += CONST_NOTORIOUS;
		break;
	}
	return story;
}
string squadstory_text_location(const Deprecatednewsstoryst ns, const bool liberalguardian, const bool ccs)
{
	string story;
	story += CONST_THE_EVENTS_TOOK_PLACE;
	string placename = LocationsPool::getInstance().getLocationName(ns.loc);
	if (placename.substr(0, 4) == tag_The)
		placename = placename.substr(4);
	int posand = placename.find('&');
	if (posand != (int)string::npos)
		placename = placename.substr(0, posand) + CONST_AND + placename.substr(posand + 1);
	story += storyPlaceName(placename, LocationsPool::getInstance().getLocationType(ns.loc), liberalguardian, ccs);
	if (ccs)
	{
		switch (LocationsPool::getInstance().getLocationType(ns.loc))
		{
		case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
			story += CONST_UNIVERSITY_DORMITORY; break;
		case SITE_BUSINESS_CIGARBAR:
			story += CONST_LADY_LUCK_STRIP_CLUB; break;
		case SITE_LABORATORY_COSMETICS:
			story += CONST_ANIMAL_SHELTER; break;
		case SITE_LABORATORY_GENETIC:
			story += CONST_RESEARCH_ETHICS_COMMISSION_HQ; break;
		case SITE_GOVERNMENT_POLICESTATION:
			story += CONST_SEEDY_BACK_ALLEY_TM; break;
		case SITE_GOVERNMENT_COURTHOUSE:
			story += CONST_ABORTION_CLINIC; break;
		case SITE_GOVERNMENT_PRISON:
			story += CONST_REHABILITATION_CENTER; break;
		case SITE_GOVERNMENT_INTELLIGENCEHQ:
			story += CONST_WIKILEAKS_HQ; break;
		case SITE_INDUSTRY_SWEATSHOP:
			story += CONST_LABOR_UNION_HQ; break;
		case SITE_INDUSTRY_POLLUTER:
			story += CONST_GREENPEACE_OFFICES; break;
		case SITE_INDUSTRY_NUCLEAR:
			story += CONST_WHIRLED_PEAS_MUSEUM; break;
		case SITE_CORPORATE_HEADQUARTERS:
			story += CONST_WELFARE_ASSISTANCE_AGENCY; break;
		case SITE_CORPORATE_HOUSE:
			story += CONST_TAX_COLLECTION_AGENCY; break;
		case SITE_MEDIA_AMRADIO:
			story += CONST_PUBLIC_RADIO_STATION; break;
		case SITE_MEDIA_CABLENEWS:
			story += CONST_NETWORK_NEWS_STATION; break;
		case SITE_GOVERNMENT_ARMYBASE:
			story += CONST_GREENPEACE_OFFICES; break;
		case SITE_GOVERNMENT_FIRESTATION:
			story += CONST_ACLU_BRANCH_OFFICE; break;
		case SITE_BUSINESS_BANK:
			story += CONST_RICHARD_DAWKINS_FOOD_BANK; break;
		default:
			story += placename;
			story += CONST_DOT_SPACE; break;
		}
	}
	else story += placename;
	if (liberalguardian && !ccs)
	{
		switch (LocationsPool::getInstance().getLocationType(ns.loc))
		{
		case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
			story += CONST_KNOWN_FOR_ITS_RICH_AND_SNOOTY_RESIDENTS; break;
		case SITE_BUSINESS_CIGARBAR:
			story += CONST_A_SPAWNING_GROUND_OF_WRONG_CONSERVATIVE_IDEAS; break;
		case SITE_LABORATORY_COSMETICS:
			story += CONST_A_CONSERVATIVE_ANIMAL_RIGHTS_ABUSER; break;
		case SITE_LABORATORY_GENETIC:
			story += CONST_A_DANGEROUS_CONSERVATIVE_GENETIC_RESEARCH_LAB; break;
		case SITE_GOVERNMENT_POLICESTATION:
			story += CONST_HEADQUARTERS_OF_ONE_OF_THE_MOST_OPPRESSIVE_AND_CONSERVATIVE_POLICE_FORCES_IN_THE_COUNTRY; break;
		case SITE_GOVERNMENT_COURTHOUSE:
			story += CONST_SITE_OF_NUMEROUS_CONSERVATIVE_INJUSTICES; break;
		case SITE_GOVERNMENT_PRISON:
			story += CONST_WHERE_INNOCENT_PEOPLE_ARE_REGULARLY_BEATEN_BY_CONSERVATIVE_GUARDS; break;
		case SITE_GOVERNMENT_INTELLIGENCEHQ:
			story += CONST_THE_CONSERVATIVE_HEADQUARTERS_OF_ONE_OF_THE_BIGGEST_PRIVACY_VIOLATORS_IN_THE_WORLD; break;
		case SITE_GOVERNMENT_ARMYBASE:
			story += CONST_PRIDE_OF_CONSERVATIVE_TORTURERS_AND_WARMONGERS_EVERYWHERE; break;
		case SITE_INDUSTRY_SWEATSHOP:
			story += CONST_A_CONSERVATIVE_SWEATSHOP_AND_HUMAN_RIGHTS_ABUSER; break;
		case SITE_INDUSTRY_POLLUTER:
			story += CONST_A_FACTORY_WHOSE_CONSERVATIVE_SMOKESTACKS_CHOKE_THE_CITY_WITH_DEADLY_POLLUTANTS; break;
		case SITE_INDUSTRY_NUCLEAR:
			story += CONST_ALSO_KNOWN_TO_BE_A_CONSERVATIVE_STORAGE_FACILITY_FOR_RADIOACTIVE_WASTE; break;
		case SITE_CORPORATE_HEADQUARTERS:
			story += CONST_WHERE_EVIL_AND_CONSERVATISM_COAGULATE_IN_THE_HALLWAYS; break;
		case SITE_CORPORATE_HOUSE:
			story += CONST_A_BUILDING_WITH_ENOUGH_SQUARE_FOOTAGE_ENOUGH_TO_HOUSE_A_HUNDRED_PEOPLE_IF_IT_WEREN_T_IN_CONSERVATIVE_HANDS; break;
		case SITE_MEDIA_AMRADIO:
		case SITE_MEDIA_CABLENEWS:
			story += CONST_KNOWN_FOR_ITS_EXTREME_CONSERVATIVE_BIAS; break;
		case SITE_BUSINESS_BANK:
			story += CONST_THE_VERY_SYMBOL_OF_ECONOMIC_INEQUALITY; break;
		default:
			story += CONST_DOT_SPACE; break;
		}
	}
	else if (!ccs)
		story += CONST_DOT_SPACE;

	return story;
}
string squadstory_text_opening(const Deprecatednewsstoryst ns, bool liberalguardian, bool ccs)
{
	string story;
	if (ns.type == NEWSSTORY_SQUAD_SITE)
	{
		if (!newscherrybusted && !liberalguardian)
		{
			if (ns.positive)
			{
				story += CONST_A_GROUP_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD;
				story += CONST_BURST_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING;
				story += CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT;
				story += AMPERSAND_R;
			}
			else
			{
				story += CONST_A_GROUP_OF_THUGS_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD;
				story += CONST_WENT_ON_A_RAMPAGE_YESTERDAY_ACCORDING;
				story += CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT;
			}
		}
		else
		{
			if (ns.positive)
			{
				story += CONST_THE_LIBERAL_CRIME_SQUAD_HAS_STRUCK_AGAIN;
				story += AMPERSAND_R;
			}
			else
			{
				if (!liberalguardian)
					story += CONST_THE_LIBERAL_CRIME_SQUAD_HAS_GONE_ON_A_RAMPAGE;
				else
					story += CONST_A_LIBERAL_CRIME_SQUAD_OPERATION_WENT_HORRIBLY_WRONG;
				story += AMPERSAND_R;
			}
		}
	}
	else if (ns.type == NEWSSTORY_CCS_SITE)
	{
		if (newscherrybusted < 2)
		{
			if (ns.positive && !liberalguardian)
			{
				story += CONST_A_GROUP_OF_M16_WIELDING_VIGILANTES_CALLING_ITSELF_THE_CONSERVATIVE_CRIME_SQUAD;
				story += CONST_BURST_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING;
				story += CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT;
				story += AMPERSAND_R;
			}
			else
			{
				story += CONST_A_GROUP_OF_WORTHLESS_M16_TOTING_HICKS_CALLING_ITSELF_THE_CONSERVATIVE_CRIME_SQUAD;
				story += CONST_WENT_ON_A_RAMPAGE_YESTERDAY_ACCORDING;
				story += CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT;
			}
		}
		else
		{
			if (ns.positive && !liberalguardian)
			{
				story += CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_STRUCK_AGAIN;
				story += AMPERSAND_R;
			}
			else
			{
				story += CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_GONE_ON_ANOTHER_RAMPAGE;
				story += AMPERSAND_R;
			}
		}
	}
	else if (ns.type == NEWSSTORY_CCS_KILLED_SITE)
	{
		if (newscherrybusted < 2)
		{
			if (ns.positive && !liberalguardian)
			{
				story += CONST_A_GROUP_OF_M16_WIELDING_VIGILANTES_CALLING_THEMSELVES_THE_CONSERVATIVE_CRIME_SQUAD;
				story += CONST_BURST_BRIEFLY_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING;
				story += CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT_SPACE;
				story += AMPERSAND_R;
			}
			else
			{
				story += CONST_A_GROUP_OF;
				story += pickrandom(ccs_adjective);
				story += pickrandom(ccs_adjective_2);
				story += CONST_M16_TOTING;
				story += pickrandom(ccs_noun);
				story += CONST_CALLING_THEMSELVES_THE_CONSERVATIVE_CRIME_SQUAD_WENT_ON_A;
				story += pickrandom(ccs_adjective_3);
				story += CONST_RAMPAGE_YESTERDAY_ACCORDING_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT;
				story += AMPERSAND_R;
			}
		}
		else
		{
			if (ns.positive && !liberalguardian)
			{
				story += CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_STRUCK_AGAIN_ALBEIT_WITH_A_TRAGIC_END;
				story += AMPERSAND_R;
			}
			else
			{
				story += CONST_THE_CONSERVATIVE_CRIME_SQUAD_HAS_GONE_ON_ANOTHER_RAMPAGE_AND_THEY_GOT_WHAT_THEY_DESERVED;
				story += AMPERSAND_R;
			}
		}
	}
	else
	{
		if (!newscherrybusted && !liberalguardian)
		{
			if (ns.positive)
			{
				story += CONST_A_GROUP_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD;
				story += CONST_BURST_BRIEFLY_ONTO_THE_SCENE_OF_POLITICAL_ACTIVISM_YESTERDAY_ACCORDING;
				story += CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT_SPACE;
				story += AMPERSAND_R;
			}
			else
			{
				story += CONST_A_GROUP_OF_THUGS_CALLING_ITSELF_THE_LIBERAL_CRIME_SQUAD;
				story += CONST_WENT_ON_A_SUICIDAL_RAMPAGE_YESTERDAY_ACCORDING;
				story += CONST_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT_SPACE;
				story += AMPERSAND_R;
			}
		}
		else
		{
			if (ns.positive)
			{
				story += CONST_THE_LIBERAL_CRIME_SQUAD_HAS_STRUCK_AGAIN_ALBEIT_WITH_A_TRAGIC_END;
				story += AMPERSAND_R;
			}
			else
			{
				if (!liberalguardian)
					story += CONST_THE_LIBERAL_CRIME_SQUAD_HAS_GONE_ON_A_RAMPAGE_AND_THEY_GOT_WHAT_THEY_DESERVED;
				else
					story += CONST_A_LIBERAL_CRIME_SQUAD_OPERATION_WENT_HORRIBLY_WRONG_AND_CAME_TO_A_TRAGIC_END;//XXX: Rewrite me -- LK
				story += AMPERSAND_R;
			}
		}
	}
	story += squadstory_text_location(ns, liberalguardian, ccs);
	if (ns.type == NEWSSTORY_SQUAD_KILLED_SITE)
	{
		if (liberalguardian)story += CONST_UNFORTUNATELY_THE_LCS_GROUP_WAS_DEFEATED_BY_THE_FORCES_OF_EVIL;
		else if (ns.positive)story += CONST_EVERYONE_IN_THE_LCS_GROUP_WAS_ARRESTED_OR_KILLED;
		else story += CONST_FORTUNATELY_THE_LCS_THUGS_WERE_STOPPED_BY_BRAVE_CITIZENS;
	}
	if (ns.type == NEWSSTORY_CCS_KILLED_SITE)
	{
		if (ns.positive && !liberalguardian)story += CONST_EVERYONE_IN_THE_CCS_GROUP_WAS_ARRESTED_OR_KILLED;
		else story += CONST_FORTUNATELY_THE_CCS_THUGS_WERE_STOPPED_BY_BRAVE_CITIZENS;
	}
	story += AMPERSAND_R;
	return story;
}

void run_television_news_stories()
{
	for (int n = len(newsstory) - 1; n >= 0; n--)
	{
		char del = 0;
		if (newsstory[n]->type == NEWSSTORY_MAJOREVENT)
		{
			if (newsstory[n]->positive)
			{
				switch (newsstory[n]->view)
				{
				case VIEW_POLICEBEHAVIOR:
					music.play(MUSIC_LACOPS);
					movie.loadmovie(CONST_LACOPS_CMV.c_str());
					movie.playmovie(0, 0);

					printMultilineNewsStory(CONST_Police_744);
					pressAnyKey();
					del = 1;
					break;
				case VIEW_CABLENEWS:
				{
					music.play(MUSIC_NEWSCAST);
					printRandomCableNewsName();

					movie.loadmovie(CONST_NEWSCAST_CMV.c_str());
					movie.playmovie(1, 1);

					printMultilineNewsStory(CONST_Cable_744POS);
					pressAnyKey();
					del = 1;
					break;
				}
				}
			}
			else
			{
				switch (newsstory[n]->view)
				{
				case VIEW_CEOSALARY:
					music.play(MUSIC_GLAMSHOW);
					movie.loadmovie(CONST_GLAMSHOW_CMV.c_str());
					movie.playmovie(0, 0);
					printMultilineNewsStory(CONST_CEO_744);
					pressAnyKey();
					del = 1;
					break;
				case VIEW_CABLENEWS:
					music.play(MUSIC_ANCHOR);
					movie.loadmovie(CONST_ANCHOR_CMV.c_str());
					movie.playmovie(0, 0);

					printMultilineNewsStory(CONST_Cable_744);
					pressAnyKey();
					del = 1;
					break;
				case VIEW_WOMEN:
					music.play(MUSIC_ABORT);
					eraseAlt();
					movie.loadmovie(CONST_ABORT_CMV.c_str());
					movie.playmovie(0, 0);
					printMultilineNewsStory(CONST_Woman_744);
					pressAnyKey();
					del = 1;
					break;
				}
			}
		}
		if (del) delete_and_remove(newsstory, n);
	}
}

string getLastNameForHeadline(char* fullName)
{
	int j = -1;
	char lastName[20];
	// Parse through full name to get the last name
	for (int i = 0; fullName[i] != 0; i++)
	{
		// Start recording last name at the space between first and last
		if (fullName[i] == ' ')
		{
			j = 0;
		}
		// When recording last name, transcribe in uppercase
		else if (j >= 0)
		{
			lastName[j++] = toupper(fullName[i]);
		}
	}
	lastName[j] = 0; // To finish, NULL terminate the transcribed string
					 // Write to string
	string ret = lastName;
	return ret;
}
void displayOtherStoryHeader(const Deprecatednewsstoryst ns, const bool liberalguardian, const int header, string& single_line_news, string& double_line_news) {
	if (ns.positive)
	{
		if (newscherrybusted || liberalguardian)
		{
			if (!liberalguardian)
			{
				if (ns.priority > 250)
				{
					single_line_news = CONST_UNSTOPPABLE;
				}
				else
				{
					single_line_news = CONST_LCS_STRIKES;
				}
			}
			else
			{
				if (ns.priority > 150)
				{
					change_public_opinion(header, 5, 1); // Bonus for big story
					switch (header)
					{
					case VIEW_TAXES:
					case VIEW_SWEATSHOPS:
					case VIEW_CEOSALARY:
					case VIEW_NUCLEARPOWER:
					case VIEW_POLICEBEHAVIOR:
					case VIEW_DEATHPENALTY:
					case VIEW_INTELLIGENCE:
					case VIEW_ANIMALRESEARCH:
					case VIEW_GENETICS:
					case VIEW_FREESPEECH:
					case VIEW_GAY:
					case VIEW_JUSTICES:
					case VIEW_POLLUTION:
					case VIEW_CORPORATECULTURE:
					case VIEW_AMRADIO:
					case VIEW_CABLENEWS:
						single_line_news = newsStoryHeadlines[header];
						break;
					default:
						single_line_news = CONST_HEROIC_STRIKE;
						break;
					}
				}
				else
				{
					single_line_news = CONST_LCS_STRIKES;
				}
			}

		}
		else
		{
			single_line_news = CONST_LIBERAL_CRIME;
			double_line_news = CONST_SQUAD_STRIKES;
		}
	}
	else
	{
		if (newscherrybusted || liberalguardian)
		{
			if (!liberalguardian)
				single_line_news = CONST_LCS_RAMPAGE;
			else
				single_line_news = CONST_LCS_SORRY;
		}
		else
		{
			single_line_news = CONST_LIBERAL_CRIME;
			double_line_news = CONST_SQUAD_RAMPAGE;
		}
	}
}

int displaystoryheader(const Deprecatednewsstoryst ns, const bool liberalguardian, const int header)
{
	string single_line_news = "";
	string double_line_news = "";
	switch (ns.type)
	{
	case NEWSSTORY_PRESIDENT_IMPEACHED:
	case NEWSSTORY_PRESIDENT_BELIEVED_DEAD:
	case NEWSSTORY_PRESIDENT_FOUND_DEAD:
	case NEWSSTORY_PRESIDENT_FOUND:
	case NEWSSTORY_PRESIDENT_KIDNAPPED:
	case NEWSSTORY_PRESIDENT_MISSING:
	case NEWSSTORY_PRESIDENT_ASSASSINATED:
		single_line_news = getLastNameForHeadline(oldPresidentName);
		double_line_news = presidentStories[ns.type];
		break;
	case NEWSSTORY_CCS_NOBACKERS:
		single_line_news = CONST_FBI_HUNTS_CCS;
		break;
	case NEWSSTORY_CCS_DEFEATED:
		single_line_news = CONST_RAIDS_END_CCS;
		break;
	case NEWSSTORY_NUDITYARREST:
	case NEWSSTORY_CARTHEFT:
	case NEWSSTORY_WANTEDARREST:
	case NEWSSTORY_DRUGARREST:
	case NEWSSTORY_GRAFFITIARREST:
	case NEWSSTORY_BURIALARREST:
		single_line_news = CONST_POLICE_KILLED;
		break;
	case NEWSSTORY_SQUAD_ESCAPED:
	case NEWSSTORY_SQUAD_FLEDATTACK:
		single_line_news = CONST_LCS_ESCAPES;
		double_line_news = CONST_POLICE_SIEGE;
		break;
	case NEWSSTORY_SQUAD_DEFENDED:
	case NEWSSTORY_SQUAD_BROKESIEGE:
		single_line_news = CONST_LCS_FIGHTS;
		double_line_news = CONST_OFF_COPS;
		break;
	case NEWSSTORY_SQUAD_KILLED_SIEGEATTACK:
	case NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE:
		if (!liberalguardian)
		{
			single_line_news = CONST_LCS_SIEGE;
			double_line_news = CONST_TRAGIC_END;
		}
		else
		{
			single_line_news = CONST_POLICE_KILL;
			double_line_news = CONST_LCS_MARTYRS;
		}
		break;
	case NEWSSTORY_CCS_SITE:
	case NEWSSTORY_CCS_KILLED_SITE:
		if (newscherrybusted < 2)
		{
			single_line_news = tag_CONSERVATIVE;
			double_line_news = CONST_CRIME_SQUAD;
		}
		else
		{
			if (ns.positive)
				single_line_news = CONST_CCS_STRIKES;//AGAIN?
			else
				single_line_news = CONST_CCS_RAMPAGE;
		}
		break;
	default:
		displayOtherStoryHeader(ns, liberalguardian, header, single_line_news, double_line_news);
		break;
	}

	displaycenterednewsfont(single_line_news, 5);
	if (double_line_news.size() > 0) {
		displaycenterednewsfont(double_line_news, 13);
		return 21;
	}
	else {
		return 13;
	}
}
void handle_public_opinion_impact(const Deprecatednewsstoryst &ns)
{
	// Check if this function is meant to handle public opinion impact
	// for this type of news story (primarily deals with squad/site actions)
	bool validType = false;
	for (int i = 0; i < len(okay_types) && !validType; i++)
	{
		if (okay_types[i] == ns.type)
			validType = false;
	}
	if (validType) {

		int impact = ns.priority;
		// Magnitude of impact will be affected by which page of the newspaper the story appears on
		if (ns.page == 1) impact *= 5;
		else if (ns.page == 2) impact *= 3;
		else if (ns.page == 3) impact *= 2;
		int maxpower = 1;
		if (ns.page == 1) maxpower = 100;
		else if (ns.page < 5) maxpower = 100 - 10 * ns.page;
		else if (ns.page < 10) maxpower = 40;
		else if (ns.page < 20) maxpower = 20;
		else if (ns.page < 30) maxpower = 10;
		else if (ns.page < 40) maxpower = 5;
		else maxpower = 1;
		// Five times effectiveness with the Liberal Guardian
		if (ns.positive == 2)
			impact *= 5;
		// Cap power
		if (impact > maxpower)
			impact = maxpower;
		impact /= 10;
		impact++;
		// Account for squad responsible, rampages, and Liberal Guardian bias
		int impact_direction = ALIGN_LIBERAL;
		if (ns.type == NEWSSTORY_CCS_SITE || ns.type == NEWSSTORY_CCS_KILLED_SITE)
		{
			impact_direction = ALIGN_CONSERVATIVE;
			if (ns.positive)
				change_public_opinion(VIEW_CONSERVATIVECRIMESQUAD, impact, 0);
			else
				change_public_opinion(VIEW_CONSERVATIVECRIMESQUAD, -impact, 0);
		}
		else
		{
			change_public_opinion(VIEW_LIBERALCRIMESQUAD, 2 + impact);
			impact_direction = ALIGN_LIBERAL;
			if (ns.positive)
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, impact);
			else
				change_public_opinion(VIEW_LIBERALCRIMESQUADPOS, -impact);
		}
		impact *= impact_direction;
		int squad_responsible = impact_direction;
		if (!ns.positive) impact /= 4;
		// Impact gun control issue
		change_public_opinion(VIEW_GUNCONTROL, abs(impact) / 10, 0, abs(impact) * 10);
		if (ns.loc == -1) return;
		// Location-specific issue impact
		std::vector<int> issues;

		if (siteViews.count(LocationsPool::getInstance().getLocationType(ns.loc))) {
			for (Views v : siteViews[LocationsPool::getInstance().getLocationType(ns.loc)]) {
				issues.push_back(v);
			}
		}

		for (int i = 0; i < len(issues); i++)
			change_public_opinion(issues[i], impact, squad_responsible, impact * 10);

	}
}
/* news - graphics */
void loadgraphics()
{
	int picnum, dimx, dimy;
	FILE *h;
	if ((h = LCSOpenFile(CONST_LARGECAP_CPC.c_str(), CONST_CPP_IO_RB.c_str(), LCSIO_PRE_ART)) != NULL)
	{
		fread(&picnum, sizeof(int), 1, h);
		fread(&dimx, sizeof(int), 1, h);
		fread(&dimy, sizeof(int), 1, h);
		for (int p = 0; p < picnum; p++)
			for (int x = 0; x < dimx; x++)
				for (int y = 0; y < dimy; y++)
					fread(&bigletters[p][x][y][0], sizeof(char), 4, h);
		LCSCloseFile(h);
	}
	if ((h = LCSOpenFile(CONST_NEWSTOPS_CPC.c_str(), CONST_CPP_IO_RB.c_str(), LCSIO_PRE_ART)) != NULL)
	{
		fread(&picnum, sizeof(int), 1, h);
		fread(&dimx, sizeof(int), 1, h);
		fread(&dimy, sizeof(int), 1, h);
		for (int p = 0; p < picnum; p++)
			for (int x = 0; x < dimx; x++)
				for (int y = 0; y < dimy; y++)
					fread(&newstops[p][x][y][0], sizeof(char), 4, h);
		LCSCloseFile(h);
	}
	if ((h = LCSOpenFile(CONST_NEWSPIC_CPC.c_str(), CONST_CPP_IO_RB.c_str(), LCSIO_PRE_ART)) != NULL)
	{
		fread(&picnum, sizeof(int), 1, h);
		fread(&dimx, sizeof(int), 1, h);
		fread(&dimy, sizeof(int), 1, h);
		for (int p = 0; p < picnum; p++)
			for (int x = 0; x < dimx; x++)
				for (int y = 0; y < dimy; y++)
					fread(&newspic[p][x][y][0], sizeof(char), 4, h);
		LCSCloseFile(h);
	}
}
void displaycenteredsmallnews(const std::string& str, int y)
{
	set_color_easy(BLACK_ON_WHITE);
	mvaddstrCenter(y, str);
}
void displaynewsstoryPositiveX(const short view, const string next, const short* storyx_s, const short* storyx_e) {
	displaycenterednewsfont(next, 5);
	displaynewsstory(constructeventstory(view, true), storyx_s, storyx_e, 13);

}
void displaynewsstoryNegativeX(const short view, const string next, const short* storyx_s, const short* storyx_e) {
	displaycenterednewsfont(next, 5);
	displaynewsstory(constructeventstory(view, false), storyx_s, storyx_e, 13);

}
void displaynewsstoryNegativeX(const short view, const string next, const string second, const short* storyx_s, const short* storyx_e) {
	displaycenterednewsfont(next, 5);
	displaycenterednewsfont(second, 13);
	displaynewsstory(constructeventstory(view, false), storyx_s, storyx_e, 21);

}
void displaynewsandpicture(const string news1, const string news2, const int picture) {
	displaycenterednewsfont(news1, 5);
	displaycenteredsmallnews(news2, 12);
	displaynewspicture(picture, 13);
}

void displaypositivemajoreventstory(const Deprecatednewsstoryst ns, const short* storyx_s, const short* storyx_e) {


	switch (ns.view)
	{
	case VIEW_WOMEN:
	case VIEW_GAY:
	case VIEW_DEATHPENALTY:
	case VIEW_GUNCONTROL:
	case VIEW_PRISONS:
	case VIEW_INTELLIGENCE:
	case VIEW_FREESPEECH:
	case VIEW_JUSTICES:
	case VIEW_AMRADIO:
		displaynewsstoryPositiveX(ns.view, positiveMajorEvents[ns.view], storyx_s, storyx_e);
		break;


	case VIEW_TAXES:
	{
		string str = pickrandom(reagan_bad) + singleSpace + pickrandom(reagan_bad_2) + CONST_A_NEW_BOOK_FURTHER_DOCUMENTING_THE_OTHER_SIDE_OF_REAGAN;
		displaynewsandpicture(CONST_REAGAN_FLAWED, str, PICTURE_BOOK);
		break;
	}

	case VIEW_NUCLEARPOWER:
	case VIEW_ANIMALRESEARCH:
	case VIEW_GENETICS:
	case VIEW_SWEATSHOPS:
	case VIEW_POLLUTION:
	case VIEW_CORPORATECULTURE:
		displaynewsandpicture(positiveMajorPictures[ns.view].first, positiveMajorPictures[ns.view].second, positiveMajorPictures[ns.view].third);
		break;
	case VIEW_CEOSALARY:
	{

		string str = CONST_THIS_MAJOR_CEO;
		switch (LCSrandom(ceo_behaving_badly.size()))
		{
		case 0:
			if (lawList[LAW_FREESPEECH] == -2 && lawList[LAW_WOMEN] != -2)str += CONST_REGULARLY_VISITS_WORKING_WOMEN;
			else if (lawList[LAW_FREESPEECH] == -2 && lawList[LAW_WOMEN] == -2)str += CONST_REGULARLY_DONATES_TO_SPERM_BANKS;
			else str += CONST_REGULARLY_VISITS_PROSTITUTES;
			break;
		default:
			str += pickrandom(ceo_behaving_badly);
		}
		displaynewsandpicture(CONST_THIS_MAJOR_CEO, str, PICTURE_CEO);
		break;
	}

	}
}

void displaynegativemajoreventstory(const Deprecatednewsstoryst ns, const short* storyx_s, const short* storyx_e) {

	switch (ns.view)
	{
	case VIEW_DEATHPENALTY:
	case VIEW_ANIMALRESEARCH:
	case VIEW_PRISONS:
	case VIEW_INTELLIGENCE:
	case VIEW_GENETICS:
	case VIEW_JUSTICES:
	case VIEW_POLLUTION:
	case VIEW_CORPORATECULTURE:
		displaynewsstoryNegativeX(ns.view, negativeMajorEvents[ns.view], storyx_s, storyx_e);
		break;

	case VIEW_GUNCONTROL:
		displaynewsstoryNegativeX(ns.view, CONST_ARMED_CITIZEN, CONST_SAVES_LIVES, storyx_s, storyx_e);
		break;
	case VIEW_AMRADIO:
		displaynewsstoryNegativeX(ns.view, CONST_THE_DEATH, CONST_OF_CULTURE, storyx_s, storyx_e);
		break;


	case VIEW_TAXES:
	{
		string str = pickrandom(reagan_good) + singleSpace + pickrandom(reagan_good_2) + CONST_A_NEW_BOOK_LAUDING_REAGAN_AND_THE_GREATEST_GENERATION;
		displaynewsandpicture(CONST_REAGAN_THE_MAN, str, PICTURE_BOOK);
		break;
	}

	case VIEW_GAY:
	case VIEW_NUCLEARPOWER:
	case VIEW_FREESPEECH:
		displaynewsandpicture(negativeMajorPictures[ns.view].first, negativeMajorPictures[ns.view].second, negativeMajorPictures[ns.view].third);
		break;

	case VIEW_SWEATSHOPS:
		displaynewsandpicture(CONST_THEY_ARE_HERE, month >= 8 && month <= 11 ? CONST_FALL_FASHIONS_HIT_THE_STORES_ACROSS_THE_COUNTRY : CONST_FALL_FASHIONS_ARE_PREVIEWED_IN_STORES_ACROSS_THE_COUNTRY, PICTURE_TSHIRT);
		break;


	case VIEW_POLICEBEHAVIOR:
		if (lawList[LAW_FREESPEECH] == -2)displaycenterednewsfont(CONST_JERKS, 5);
		else displaycenterednewsfont(CONST_BASTARDS, 5);
		displaynewspicture(PICTURE_TERRORISTS, 13);
		break;
	}
}
void displaymajoreventstory(const Deprecatednewsstoryst ns, const short* storyx_s, const short* storyx_e)
{

	if (ns.positive)
	{
		displaypositivemajoreventstory(ns, storyx_s, storyx_e);
	}
	else
	{
		displaynegativemajoreventstory(ns, storyx_s, storyx_e);
	}
}
string wantedOrGraffitiArrest(const Deprecatednewsstoryst ns) {



	string story;
	int crime[CRIMENUM];
	std::memset(crime, 0, sizeof(int)*CRIMENUM);
	for (int c = 0; c < len(ns.crime); c++)
		crime[ns.crime[c]]++;
	if (crime[CRIME_KILLEDSOMEBODY] > 1)
	{
		if (crime[CRIME_KILLEDSOMEBODY] == 2)
			story += CONST_TWO_UPPERCASE;
		else
			story += CONST_SEVERAL;
		story += CONST_POLICE_OFFICERS_WERE;
	}
	else story += CONST_A_POLICE_OFFICER_WAS;
	story += CONST_KILLED_IN_THE_LINE_OF_DUTY_YESTERDAY;
	story += CONST_ACCORDING_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT;
	story += ampersandR;
	story += CONST_A_SUSPECT_IDENTIFIED_ONLY_AS_A_MEMBER_OF_THE;
	story += CONST_RADICAL_POLITICAL_GROUP_KNOWN_AS_THE_LIBERAL_CRIME_SQUAD_IS_BELIEVED_TO_HAVE_KILLED;
	if (crime[CRIME_KILLEDSOMEBODY] > 1)
	{
		story += tostring(crime[CRIME_KILLEDSOMEBODY]);
		story += CONST_OFFICERS;
	}
	else story += CONST_THE_POLICE_OFFICER;
	story += CONST_WHILE_THEY_WERE_ATTEMPTING_TO_PERFORM_AN_ARREST;
	story += CONST_THE_NAMES_OF_THE_OFFICERS_HAVE_NOT_BEEN_RELEASED_PENDING_NOTIFICATION_OF_THEIR_FAMILIES;
	story += ampersandR;
	return story;
}
string nudityCarDrugOrBurialArrest(const Deprecatednewsstoryst ns) {
	string story;
	int crime[CRIMENUM];
	std::memset(crime, 0, sizeof(int)*CRIMENUM);
	for (int c = 0; c < len(ns.crime); c++)
		crime[ns.crime[c]]++;
	story += CONST_A_ROUTINE_ARREST_WENT_HORRIBLY_WRONG_YESTERDAY;
	story += CONST_ACCORDING_TO_A_SPOKESPERSON_FROM_THE_POLICE_DEPARTMENT;
	story += ampersandR;
	story += CONST_A_SUSPECT_WHOSE_IDENTITY_IS_UNCLEAR;
	story += CONST_KILLED;
	if (crime[CRIME_KILLEDSOMEBODY] > 1)
	{
		story += tostring(crime[CRIME_KILLEDSOMEBODY]);
		story += CONST_POLICE_OFFICERS_THAT_WERE;
	}
	else story += CONST_A_POLICE_OFFICER_THAT_WAS;
	story += CONST_ATTEMPTING_TO_PERFORM_AN_ARREST;
	if (ns.type == NEWSSTORY_NUDITYARREST)
		story += CONST_THE_INCIDENT_APPARENTLY_OCCURRED_AS_A_RESPONSE_TO_A_PUBLIC_NUDITY_COMPLAINT;
	else if (ns.type == NEWSSTORY_DRUGARREST)
		story += CONST_THE_SUSPECT_WAS_ALLEGEDLY_SELLING_POT_BROWNIES;
	else if (ns.type == NEWSSTORY_BURIALARREST)
	{
		story += CONST_A_PASSERBY_ALLEGEDLY_CALLED_THE_AUTHORITIES_AFTER_SEEING_THE_SUSPECT_DRAGGING_WHAT;
		story += CONST_APPEARED_TO_BE_A_CORPSE_THROUGH_AN_EMPTY_LOT;
	}
	else
		story += CONST_A_PASSERBY_HAD_ALLEGEDLY_SPOTTED_THE_SUSPECT_COMMITTING_A_CAR_THEFT;
	if (crime[CRIME_KILLEDSOMEBODY] > 1)
		story += CONST_THE_NAMES_OF_THE_OFFICERS_HAVE_NOT_BEEN_RELEASED_PENDING_NOTIFICATION_OF_THEIR_FAMILIES;
	else story += CONST_THE_NAME_OF_THE_OFFICER_HAS_NOT_BEEN_RELEASED_PENDING_NOTIFICATION_OF_THE_OFFICER_S_FAMILY;
	story += ampersandR;
	return story;

}
bool specialCrimes(const int c) {
	bool special = false;
	switch (c) {
	case CRIME_HOUSE_PHOTOS:
	case CRIME_CORP_FILES:
	case CRIME_SHUTDOWNREACTOR:
	case CRIME_BANKVAULTROBBERY:
	case CRIME_BANKSTICKUP:
	case CRIME_POLICE_LOCKUP:
	case CRIME_COURTHOUSE_LOCKUP:
	case CRIME_PRISON_RELEASE:
	case CRIME_JURYTAMPERING:
	case CRIME_HACK_INTEL:
	case CRIME_ARMORY:
	case CRIME_CARCHASE:
	case CRIME_CARCRASH:
	case CRIME_FOOTCHASE:
		special = true;
		break;
		// case CRIME_TAGGING:
	}
	return special;
}

string accordingToCrimeString(const int c, const bool liberalguardian) {
	string story;

	switch (c) {
	case CRIME_POLICE_LOCKUP:
	case CRIME_BANKVAULTROBBERY:
	case CRIME_BANKSTICKUP:
	case CRIME_COURTHOUSE_LOCKUP:
	case CRIME_PRISON_RELEASE:
	case CRIME_JURYTAMPERING:
	case CRIME_HACK_INTEL:
	case CRIME_ARMORY:
	case CRIME_HOUSE_PHOTOS:
	case CRIME_CORP_FILES:
		story += accordingToLiberalGuardian[c][!liberalguardian];
		story += ampersandR;
		break;
	}
	return story;
}
string extraCrimes(const bool liberalguardian, const bool ccs, const int type_sum, const int crime[CRIMENUM]) {
	int typesum = type_sum;
	if (typesum <= 0) {
		return "";
	}
	string story = "";
	if (!ccs)
	{
		story += liberalguardian ? CONST_THE_LIBERAL_CRIME_SQUAD : CONST_FURTHER_DETAILS_ARE_SKETCHY_BUT_POLICE_SOURCES_SUGGEST_THAT_THE_LCS + CONST_ENGAGED_IN;
	}
	else
	{
		story += CONST_FURTHER_DETAILS_ARE_SKETCHY_BUT_POLICE_SOURCES_SUGGEST_THAT_THE_CCS;
		story += CONST_ENGAGED_IN;
	}
	if (crime[CRIME_ARSON])
	{
		story += liberalguardian || !ccs ? CONST_SET_FIRE_TO_CONSERVATIVE_PROPERTY : CONST_ARSON_LOWERCASE;

		if (typesum >= 3)story += COMMA_SPACE;
		else if (typesum == 2)story += AND;
		typesum--;
	}
	if (!liberalguardian || ccs)
	{
		if (crime[CRIME_KILLEDSOMEBODY])
		{
			story += CONST_MURDER_LOWERCASE;
			if (typesum >= 3)story += COMMA_SPACE;
			else if (typesum == 2)story += AND;
			typesum--;
		}
		if (crime[CRIME_ATTACKED_MISTAKE])
		{
			story += CONST_VIOLENCE;
			if (typesum >= 3)story += COMMA_SPACE;
			else if (typesum == 2)story += AND;
			typesum--;
		}
		if (crime[CRIME_ATTACKED])
		{
			if (crime[CRIME_ATTACKED_MISTAKE])story += CONST_MORE_VIOLENCE;
			else story += CONST_VIOLENCE;
			if (typesum >= 3)story += COMMA_SPACE;
			else if (typesum == 2)story += AND;
			typesum--;
		}
	}
	else
	{
		if (crime[CRIME_ATTACKED])
		{
			story += CONST_ENGAGED_IN_COMBAT_WITH_CONSERVATIVE_FORCES;
			if (typesum >= 3)story += COMMA_SPACE;
			else if (typesum == 2)story += AND;
			typesum--;
		}
	}
	if (crime[CRIME_STOLEGROUND] || crime[CRIME_BANKTELLERROBBERY])
	{
		story += liberalguardian || !ccs ? CONST_LIBERATED_ENEMY_RESOURCES : CONST_THEFT_LOWERCASE;

		if (typesum >= 3)story += COMMA_SPACE;
		else if (typesum == 2)story += AND;
		typesum--;
	}
	if (crime[CRIME_FREE_RABBITS] || crime[CRIME_FREE_BEASTS])
	{
		story += liberalguardian ? CONST_LIBERATED_ABUSED_ANIMALS : CONST_TAMPERING_WITH_LAB_ANIMALS;

		if (typesum >= 3)story += COMMA_SPACE;
		else if (typesum == 2)story += AND;
		typesum--;
	}
	if (crime[CRIME_BREAK_SWEATSHOP] || crime[CRIME_BREAK_FACTORY] || crime[CRIME_VANDALISM])
	{
		story += liberalguardian || !ccs ? CONST_DAMAGED_ENEMY_INFRASTRUCTURE : CONST_DESTRUCTION_OF_PRIVATE_PROPERTY;

		if (typesum >= 3)story += COMMA_SPACE;
		else if (typesum == 2)story += AND;
		typesum--;
	}
	if (crime[CRIME_TAGGING])
	{
		story += liberalguardian || !ccs ? CONST_MARKED_THE_SITE_FOR_LIBERATION : CONST_VANDALISM_LOWERCASE;

		if (typesum >= 3)story += COMMA_SPACE;
		else if (typesum == 2)story += AND;
		typesum--;
	}
	if (crime[CRIME_BROKEDOWNDOOR])
	{
		story += liberalguardian || !ccs ? CONST_BROKE_DOWN_DOORS : CONST_BREAKING_AND_ENTERING_LOWERCASE;

		if (typesum >= 3)story += COMMA_SPACE;
		else if (typesum == 2)story += AND;
		typesum--;
	}
	if (crime[CRIME_UNLOCKEDDOOR])
	{
		story += liberalguardian || !ccs ? CONST_PICKED_LOCKS : CONST_UNLAWFUL_ENTRY;

		if (typesum >= 3)story += COMMA_SPACE;
		else if (typesum == 2)story += AND;
		typesum--;
	}
	story += singleDot;

	story += ampersandR;
	return story;
}
string otherCrime(const Deprecatednewsstoryst ns, const bool liberalguardian, const bool ccs) {
	string story;
	int crime[CRIMENUM];
	memset(crime, 0, sizeof(int)*CRIMENUM);
	int typesum = 0;
	for (int c = 0; c < len(ns.crime); c++)
	{
		// Count crimes of each type
		crime[ns.crime[c]]++;
		// Special crimes are described at the start or end of the article;
		// others should be recorded in the body
		if (specialCrimes(ns.crime[c])) {
			continue;
		}
		if (crime[ns.crime[c]] == 1) typesum++;
	}
	if (crime[CRIME_SHUTDOWNREACTOR])
	{
		if (lawList[LAW_NUCLEARPOWER] == 2)
		{
			story += liberalguardian ? CONST_THE_LIBERAL_CRIME_SQUAD_TAMPERED_WITH_THE_STATE_S_WATER_SUPPLY_YESTERDAY + CONST_DEMONSTRATING_THE_EXTREME_DANGERS_OF_NUCLEAR_WASTE : ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_CONTAMINATED_THE_STATE_S_WATER_SUPPLY + CONST_YESTERDAY_BY_TAMPERING_WITH_EQUIPMENT_ON_THE_SITE;
			story += ampersandR;
		}
		else
		{
			story += liberalguardian ? CONST_THE_LIBERAL_CRIME_SQUAD_BROUGHT_THE_REACTOR_TO_THE_VERGE_OF_A_NUCLEAR_MELTDOWN + CONST_DEMONSTRATING_THE_EXTREME_VULNERABILITY_AND_DANGER_OF_NUCLEAR_POWER_PLANTS : ACCORDING_TO_SOURCES + CONST_THE_LIBERAL_CRIME_SQUAD_NEARLY_CAUSED_A_CATASTROPHIC_MELTDOWN_OF_THE_NUCLEAR + CONST_REACTOR;

			story += ampersandR;
		}
	}
	if (crime[CRIME_POLICE_LOCKUP])
	{
		story += accordingToCrimeString(CRIME_POLICE_LOCKUP, liberalguardian);
	}
	if (crime[CRIME_BANKVAULTROBBERY])
	{
		story += accordingToCrimeString(CRIME_BANKVAULTROBBERY, liberalguardian);
	}
	else if (crime[CRIME_BANKSTICKUP])
	{
		story += accordingToCrimeString(CRIME_BANKSTICKUP, liberalguardian);
	}
	for (Crimes c : noteworthyCrimes) {
		if (crime[c]) {
			story += accordingToCrimeString(c, liberalguardian);
		}
	}
	if (liberalguardian && !ccs)
	{
		if (crime[CRIME_ATTACKED_MISTAKE]) typesum--;
		if (crime[CRIME_KILLEDSOMEBODY]) typesum--;
	}

	story += extraCrimes(liberalguardian, ccs, typesum, crime);

	if (crime[CRIME_CARCHASE])
	{
		story += liberalguardian && !ccs ? CONST_CONSERVATIVE_OPERATIVES_ENGAGED_IN_A_RECKLESS + CONST_PURSUIT_OF_THE_LCS : CONST_IT_IS_KNOWN_THAT_THERE_WAS_A_HIGH_SPEED_CHASE + CONST_FOLLOWING_THE_INCIDENT;

		if (crime[CRIME_CARCRASH])
		{
			if (crime[CRIME_CARCRASH] > 1)
			{
				story += tostring(crime[CRIME_CARCRASH]);
				story += CONST_VEHICLES_CRASHED;
			}
			else story += CONST_ONE_VEHICLE_CRASHED;
			if (!liberalguardian || ccs)
				story += CONST_DETAILS_ABOUT_INJURIES_WERE_NOT_RELEASED;//XXX: Why not turn them into martyrs?
		}
		if (crime[CRIME_FOOTCHASE])
		{
			story += liberalguardian || !ccs ? CONST_THE_LIBERAL_CRIME_SQUAD_ENDED_THE_DANGEROUS_HIGH_SPEED_CHASE_IN_ORDER_TO_PROTECT_THE_PUBLIC_AND_ATTEMPTED_TO_ESCAPE_ON_FOOT : CONST_THERE_WAS_ALSO_A_FOOT_CHASE_WHEN_THE_SUSPECT_OR_SUSPECTS_BAILED_OUT_AFTER_THE_HIGH_SPEED_PURSUIT;

		}
		story += ampersandR;
	}
	if (!ccs && !LCSrandom(8))
	{
		if (crime[CRIME_TAGGING])
		{
			story += CONST_THE_SLOGAN;
			story += slogan_str;
			story += CONST_WAS_FOUND_PAINTED_ON_THE_WALLS;
		}
		else
		{
			switch (LCSrandom(3))
			{
			case 0:
				if (ns.type == NEWSSTORY_SQUAD_KILLED_SITE)
				{
					story += CONST_ONE_UTTERED_THE_WORDS;
					story += slogan_str;
					story += CONST_BEFORE_PASSING_OUT;

					return story;
				}
				else
				{
					story += CONST_AS_THEY_LEFT_THEY_SHOUTED;
				}
				break;
			case 1:
				story += CONST_ONE_OF_THEM_WAS_RUMORED_TO_HAVE_CRIED_OUT;
				break;
			case 2:
				story += CONST_WITNESSES_REPORTED_HEARING_THE_PHRASE;
				break;
			}
			story += slogan_str;
			story += QUOTATION_MARK;
			return story;
		}
		story += ampersandR;

	}
	return story;

}

string displayMinorStory(const bool liberalguardian, Deprecatednewsstoryst ns) {
	string story;
	{

		switch (ns.type)
		{
		case NEWSSTORY_CCS_NOBACKERS:
			for (string s : caseNEWSSTORY_CCS_NOBACKERS) {
				story += s;
			}
			break;
		case NEWSSTORY_CCS_DEFEATED:
			for (string s : caseNEWSSTORY_CCS_DEFEATED) {
				story += s;
			}
			break;
		case NEWSSTORY_WANTEDARREST:
		case NEWSSTORY_GRAFFITIARREST:
		{
			story += wantedOrGraffitiArrest(ns);
			break;
		}
		case NEWSSTORY_NUDITYARREST:
		case NEWSSTORY_CARTHEFT:
		case NEWSSTORY_DRUGARREST:
		case NEWSSTORY_BURIALARREST:
		{
			story += nudityCarDrugOrBurialArrest(ns);
			break;
		}
		case NEWSSTORY_SQUAD_ESCAPED:
		case NEWSSTORY_SQUAD_FLEDATTACK:
		case NEWSSTORY_SQUAD_DEFENDED:
		case NEWSSTORY_SQUAD_BROKESIEGE:
		case NEWSSTORY_SQUAD_KILLED_SIEGEATTACK:
		case NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE:
			story += membersOfLCS;
			if (!liberalguardian) {
				story += newsStories[ns.type][0];
				story += policeSpokesperson;
			}
			else
			{
				story += newsStories[ns.type][len(newsStories[ns.type]) - 1];
				story += lcsSpokeseperson;
			}
			story += ampersandR;
			break;
		default:
			bool ccs = 0;
			if (ns.type == NEWSSTORY_CCS_KILLED_SITE || ns.type == NEWSSTORY_CCS_SITE)ccs = 1;
			story += squadstory_text_opening(ns, liberalguardian, ccs);
			story += otherCrime(ns, liberalguardian, ccs);
			break;
		}
	}
	return story;
}
/* news - make some filler junk */
string generatefiller(int amount) {
	string story;
	//TODO: Use text from filler.cpp
	story += ampersandR + cityname() + spaceDashSpace;
	for (int par = 0; amount > 0; amount--)
	{
		par++;
		for (int i = 0; i < LCSrandom(10) + 3; i++)story += CONST_TILDA;
		if (amount > 1)story += singleSpace;
		if (par >= 50 && !LCSrandom(5) && amount > 20)
		{
			par = 0;
			story += ampersandR + singleSpace;
		}
	}
	story += ampersandR;
	return story;

}

string displayMassacreStory(const Deprecatednewsstoryst ns, const bool liberalguardian, int &y) {
	if (ns.page == 1)
	{
		y = 21;
		if (ns.crime[0] == SIEGE_CCS)
		{
			displaycenterednewsfont(CONST_CCS_MASSACRE, 5);
		}
		else if (!liberalguardian)
		{
			displaycenterednewsfont(CONST_MYSTERIOUS, 5);
			displaycenterednewsfont(CONST_MASSACRE, 13);
		}
		else
		{
			displaycenterednewsfont(tag_CONSERVATIVE, 5);
			displaycenterednewsfont(CONST_MASSACRE, 13);
		}
	}
	string story;
	(story = city);
	(story += spaceDashSpace);
	if (ns.crime[1] > 2)
	{
		(story += tostring(ns.crime[1]));
		(story += CONST_BODIES_WERE); //Gruesome pile, large pile.
	}
	else if (ns.crime[1] > 1) { (story += CONST_TWO_BODIES_WERE); }
	else { (story += CONST_A_BODY_WAS); }
	story += CONST_FOUND_IN_THE;
	story += LocationsPool::getInstance().getLocationName(ns.loc);
	story += CONST_YESTERDAY;
	if (!liberalguardian)
	{
		story += CONST_ACCORDING_TO_A_SPOKESPERSON_FOR;
		story += CONST_THE_POLICE_DEPARTMENT_THE_MATTER_IS_UNDER_INVESTIGATION_AS_A_HOMICIDE;
		story += ampersandR;
		story += CONST_PRIVATELY_SOURCES_IN_THE_DEPARTMENT_CONFIDE_THAT_THERE_AREN_T_ANY_LEADS;
		story += CONST_ACCORDING_TO_ONE_PERSON_FAMILIAR_WITH_THE_CASE;
	}
	else
	{
		story += CONST_THE_POLICE_HAVE_OPENED_AN_INVESTIGATION_INTO_THE_MASSACRE_BUT_SEEM;
		story += CONST_UNWILLING_TO_PURSUE_THE_CASE_WITH_ANY_SERIOUS_EFFORT;
		story += ampersandR;
		story += CONST_THE_LIBERAL_CRIME_SQUAD_HAS_CLAIMED_THAT_THE;
		if (ns.crime[1] > 1) {
			story += CONST_VICTIMS_WERE_MEMBERS;
		}
		else {
			story += CONST_VICTIM_WAS_A_MEMBER;
		}
		story += CONST_OF_THE_LCS_TARGETED_SIMPLY_DUE_TO_THEIR_POLITICAL_BELIEFS;
		story += CONST_ACCORDING_TO_AN_LCS_SPOKESPERSON;
	}
	switch (ns.crime[0])
	{
	case SIEGE_CIA:
		if (!liberalguardian)
		{
			if (ns.crime[1] > 1)(story += CONST_THE_BODIES_HAD_NO_FACES_OR);
			else (story += CONST_THE_BODY_HAD_NO_FACE_OR);
			(story += CONST_FINGERPRINTS_LIKE_IT_WAS_ALL_SMOOTH);
			if (lawList[LAW_FREESPEECH] == -2)(story += CONST_CRAZIEST_THING_I_VE_EVER_SEEN);
			else if (lawList[LAW_FREESPEECH] == 2)(story += CONST_DAMNEDEST_THING_I_VE_EVER_SEEN);
			else (story += CONST_D_MND_ST_THING_I_VE_EVER_SEEN);
		}
		else
		{
			story += CONST_WE_HAVE_STRONG_EVIDENCE_THAT_THIS_WAS_AN_EXTRA_JUDICIAL_SLAUGHTER;
			story += CONST_CARRIED_OUT_BY_THE_CENTRAL_INTELLIGENCE_AGENCY_IN_RETALIATION_FOR_OUR;
			story += CONST_PREVIOUS_ACTIONS_TO_UNCOVER_HUMAN_RIGHTS_ABUSES_AND_CORRUPTION_IN_THE;
			story += CONST_INTELLIGENCE_COMMUNITY;
		}
		break;
		// SIEGE_FIREMEN gets a conditional opening
		// The rest is included in siegeMassacreStory;
	case SIEGE_FIREMEN:
		if (!liberalguardian)
		{
			if (ns.crime[1] > 1)(story += CONST_THE_RECOVERED_BODIES_WERE);
			else (story += CONST_THE_RECOVERED_BODY_WAS);
		}
		else
		{
			if (ns.crime[1] > 1)(story += CONST_THE_MURDERED_WERE_REPORTERS);
			else (story += CONST_THE_MURDERED_WAS_A_REPORTER);
		}
	case SIEGE_POLICE:
	case SIEGE_HICKS:
	case SIEGE_CORPORATE:
	case SIEGE_CCS:
		story += siegeMassacreStory[ns.crime[0]][liberalguardian];
		break;
	}
	story += CONST_DOT_QUOTATION_MARK;
	story += ampersandR;
	story += generatefiller(200);
	return story;
}
string getNewsStoryKidnapping(const Deprecatednewsstoryst ns) {
	string story = CONST_THE_DISAPPEARANCE_OF;
	story += ns.cr->propername;
	story += CONST_IS_NOW_CONSIDERED_A_KIDNAPPING;
	story += CONST_ACCORDING_TO_A_POLICE_SPOKESPERSON;
	story += ampersandR;
	char dstr[200], dstr2[200];
	story += singleSpace;
	generate_name(dstr, dstr2);
	story += dstr;
	story += singleSpace;
	story += dstr2;
	story += CONST_SPEAKING_ON_BEHALF_OF_THE_POLICE_DEPARTMENT_STATED;
	story += CONST_WE_NOW_BELIEVE_THAT;
	story += ns.cr->propername;
	story += CONST_WAS_TAKEN;
	story += tostring(ns.cr->joindays - 1);
	story += CONST_DAYS_AGO_BY_A_PERSON_OR_PERSONS_AS_YET_UNDETERMINED;
	story += CONST_WE_HAVE_SEVERAL_LEADS_AND_ARE_CONFIDENT_THAT_WE_WILL;
	story += CONST_BRING;
	story += ns.cr->propername;
	story += CONST_BACK_HOME_AND_BRING_THE_KIDNAPPERS_TO_JUSTICE;
	story += CONST_AS_THE_INVESTIGATION_IS_ONGOING_I_CANNOT_BE_MORE_SPECIFIC_AT_THIS_TIME;
	story += CONST_TO_THE_CITIZENS_PLEASE_CONTACT_THE_DEPARTMENT_IF_YOU_HAVE_ANY_ADDITIONAL_INFORMATION;
	story += QUOTATION_MARK;
	story += ampersandR;
	story += CONST_ACCORDING_TO_SOURCES;
	story += ns.cr->propername;
	story += CONST_S_LAST_KNOWN_LOCATION_WAS_THE;
	story += LocationsPool::getInstance().getLocationName(ns.cr->worklocation);
	story += CONST_POLICE_WERE_SEEN_SEARCHING_THE_SURROUNDING_AREA_YESTERDAY;
	story += ampersandR;
	story += generatefiller(200);
	return story;
}
void displaystory(const Deprecatednewsstoryst ns, const bool liberalguardian, int header)
{
	music.play(MUSIC_NEWSPAPER);
	preparepage(ns, liberalguardian);
	short storyx_s[25];
	short storyx_e[25];
	for (int it2 = 0; it2 < 25; it2++) storyx_s[it2] = 1;
	for (int it2 = 0; it2 < 25; it2++) storyx_e[it2] = 78;
	displayads(ns, liberalguardian, storyx_s, storyx_e);
	string city;
	if (multipleCityMode && ns.loc != -1)
	{
		Location * ns_site = find_site_in_city(LocationsPool::getInstance().get_specific_integer(INT_GETLOCATIONCITY, ns.loc), -1);
		if (cityNames.count(ns_site->type) > 0) {
			city = cityNames[ns_site->type].data();
		}
		else {
			city = lcityname;
		}
	}
	else city = lcityname;
	switch (ns.type)
	{
	case NEWSSTORY_MAJOREVENT:
		displaymajoreventstory(ns, storyx_s, storyx_e);
		break;
	case NEWSSTORY_CCS_NOBACKERS:
	case NEWSSTORY_CCS_DEFEATED:
	case NEWSSTORY_SQUAD_SITE:
	case NEWSSTORY_SQUAD_ESCAPED:
	case NEWSSTORY_SQUAD_FLEDATTACK:
	case NEWSSTORY_SQUAD_DEFENDED:
	case NEWSSTORY_SQUAD_BROKESIEGE:
	case NEWSSTORY_SQUAD_KILLED_SIEGEATTACK:
	case NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE:
	case NEWSSTORY_SQUAD_KILLED_SITE:
	case NEWSSTORY_CCS_SITE:
	case NEWSSTORY_CCS_KILLED_SITE:
	case NEWSSTORY_CARTHEFT:
	case NEWSSTORY_NUDITYARREST:
	case NEWSSTORY_WANTEDARREST:
	case NEWSSTORY_DRUGARREST:
	case NEWSSTORY_GRAFFITIARREST:
	case NEWSSTORY_BURIALARREST:
	{
		string story;
		int y = 2;
		if ((!liberalguardian&&ns.page == 1) || (liberalguardian&&ns.guardianpage == 1))
		{
			y = displaystoryheader(ns, liberalguardian, header);
			
		}
		(story = city);
		(story += spaceDashSpace);
		story += displayMinorStory(liberalguardian, ns);
		story += generatefiller(200);
		displaynewsstory(story, storyx_s, storyx_e, y);
		if (!newscherrybusted)newscherrybusted = 1;
		if (ns.type == NEWSSTORY_CCS_SITE ||
			ns.type == NEWSSTORY_CCS_KILLED_SITE)newscherrybusted = 2;

		break;
	}
	case NEWSSTORY_MASSACRE:
	{
		int y = 3;
		string story = displayMassacreStory(ns, liberalguardian, y);
		displaynewsstory(story, storyx_s, storyx_e, y);
		break;
	}
	case NEWSSTORY_KIDNAPREPORT:
	{
		int y = 2;
		if (ns.page == 1)
		{
			y = 21;
			if (liberalguardian)
			{
				displaycenterednewsfont(CONST_LCS_DENIES, 5);
				displaycenterednewsfont(CONST_ONLY9, 13); break;
			}
			else
			{
				switch (ns.cr->type)
				{
				case CREATURE_CORPORATE_CEO:
					displaycenterednewsfont(tag_CEO, 5); break;
				case CREATURE_RADIOPERSONALITY:
					displaycenterednewsfont(CONST_RADIO_HOST, 5); break;
				case CREATURE_NEWSANCHOR:
					displaycenterednewsfont(CONST_NEWS_ANCHOR, 5); break;
				case CREATURE_SCIENTIST_EMINENT:
					displaycenterednewsfont(CONST_SCIENTIST, 5); break;
				case CREATURE_JUDGE_CONSERVATIVE:
					displaycenterednewsfont(CONST_JUDGE_CAPS, 5); break;
				case CREATURE_COP:
				case CREATURE_GANGUNIT:
				case CREATURE_DEATHSQUAD:
					displaycenterednewsfont(CONST_COP, 5); break;
				default:
					displaycenterednewsfont(CONST_SOMEONE, 5); break;
				}
				displaycenterednewsfont(CONST_KIDNAPPED, 13);
			}
		}
		string story;
		story = city;
		story += getNewsStoryKidnapping(ns);
		displaynewsstory(story, storyx_s, storyx_e, y);
		break;
	}
	}

	pressSpecificKey('x', ESC, ENTER, SPACEBAR);
}
void display_newspaper()
{
	int writers = CreaturePool::getInstance().liberal_guardian_writing_power();
	for (int n = 0; n < len(newsstory); n++)
	{
		bool liberalguardian = 0;
		int header = -1;
		if (writers&&newsstory[n]->type != NEWSSTORY_MAJOREVENT)
			liberalguardian = 1;
		switch (newsstory[n]->type)
		{
		case NEWSSTORY_SQUAD_SITE:
		case NEWSSTORY_SQUAD_KILLED_SITE:
			switch (LocationsPool::getInstance().getLocationType(newsstory[n]->loc))
			{
			case SITE_LABORATORY_COSMETICS:
				header = VIEW_ANIMALRESEARCH;
				break;
			case SITE_LABORATORY_GENETIC:
				header = VIEW_GENETICS;
				break;
			case SITE_GOVERNMENT_POLICESTATION:
				header = VIEW_POLICEBEHAVIOR;
				break;
			case SITE_GOVERNMENT_COURTHOUSE:
				header = VIEW_JUSTICES;
				break;
			case SITE_GOVERNMENT_PRISON:
				header = VIEW_DEATHPENALTY;
				break;
			case SITE_GOVERNMENT_INTELLIGENCEHQ:
				header = VIEW_INTELLIGENCE;
				break;
			case SITE_INDUSTRY_SWEATSHOP:
				header = VIEW_SWEATSHOPS;
				break;
			case SITE_INDUSTRY_POLLUTER:
				header = VIEW_POLLUTION;
				break;
			case SITE_INDUSTRY_NUCLEAR:
				header = VIEW_NUCLEARPOWER;
				break;
			case SITE_CORPORATE_HEADQUARTERS:
				header = VIEW_CORPORATECULTURE;
				break;
			case SITE_CORPORATE_HOUSE:
				header = VIEW_CEOSALARY;
				break;
			case SITE_MEDIA_AMRADIO:
				header = VIEW_AMRADIO;
				break;
			case SITE_MEDIA_CABLENEWS:
				header = VIEW_CABLENEWS;
				break;
			case SITE_RESIDENTIAL_APARTMENT_UPSCALE:
			case SITE_BUSINESS_CIGARBAR:
			case SITE_BUSINESS_BANK:
				header = VIEW_TAXES;
				break;
			}
			break;
		case NEWSSTORY_SQUAD_ESCAPED:
		case NEWSSTORY_SQUAD_FLEDATTACK:
		case NEWSSTORY_SQUAD_DEFENDED:
		case NEWSSTORY_SQUAD_BROKESIEGE:
		case NEWSSTORY_SQUAD_KILLED_SIEGEATTACK:
		case NEWSSTORY_SQUAD_KILLED_SIEGEESCAPE:
			break;
		case NEWSSTORY_CCS_NOBACKERS:
		case NEWSSTORY_CCS_DEFEATED:
			break;
		}
		if (liberalguardian)
		{
			if (newsstory[n]->type == NEWSSTORY_CCS_SITE ||
				newsstory[n]->type == NEWSSTORY_CCS_KILLED_SITE)
			{
				newsstory[n]->positive = 0;
			}
			displaystory(*newsstory[n], liberalguardian, header);
			if (newsstory[n]->positive)newsstory[n]->positive += 1;
		}
		else displaystory(*newsstory[n], 0, -1);
	}
}
/* news - major newspaper reporting on lcs and other topics */
void majornewspaper(char &clearformess, char canseethings)
{
	clearformess = true;
	generate_random_event_news_stories();
	clean_up_empty_news_stories();
	if (canseethings) run_television_news_stories();
	assign_page_numbers_to_newspaper_stories();
	if (canseethings) display_newspaper();
	//DELETE STORIES
	for (int n = 0; n < len(newsstory); n++)
		handle_public_opinion_impact(*newsstory[n]);
	delete_and_clear(newsstory);
}