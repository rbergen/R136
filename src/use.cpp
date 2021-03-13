#include "r136.h"

#define COMMAND_COUNT	15
#define AMBIGUOUS		-2

const char* dontOwnItemFormatString = "< je hebt geen \"%s\"";

const char *cmds[COMMAND_COUNT] = {"oost", "west", "noord", "zuid", "klim", "daal", "gebruik",
							"combineer", "pak", "leg", "bekijk", "afwachten", "einde",
							"status", "help"};

bool DoAction(Progdata &progdata)
{
	Parsedata parsedata{};

	if (progdata.status.lifepoints <= 0)
	{
		print_to_main_window("Badend in je eigen bloed bezwijk je aan je verwondingen. Terwijl je liggend op\n");
		print_to_main_window("de grond met moeite naar adem snakt, hoor je in de verte een luid gelach.\n");
		print_to_main_window("Dan zakken je ogen dicht en stopt je hart met kloppen.\n");
		print_to_main_window("Op hetzelfde moment ontploft de bom en sterft de aarde met jou.\n\n");
		force_exit();
	}

	if (progdata.status.lamppoints > 0 && progdata.status.lamp)
	{
		switch(--progdata.status.lamppoints)
		{
		case 10:
			print_to_main_window("De zaklamp gaat zwakker branden.\n\n");
			break;
		case 0:
			print_to_main_window("De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij.\n\n");
			progdata.status.lamp = false;
			break;
		}
	}

	do
	{
		char inpstr[65];

		do 
		{
			get_command_string(inpstr, 64);
			ParseInput(progdata, inpstr, parsedata);
		} 
		while (parsedata.parseerror);

		write_centered(main_window, "---***---");
		print_to_main_window("\n\n");

		switch(parsedata.selected)
		{
		case east:
		case west:
		case north:
		case south:
		case up:
		case down:
			if (progdata.rooms[progdata.status.curroom].connect[parsedata.selected] >= 0)
			{
				if (progdata.animates[gnu].room == progdata.status.curroom && progdata.animates[gnu].status != dead)
				{
					switch (get_random_number(5))
					{
					case 0:
						progdata.animates[gnu].room = ROOM_GNOEGROT;
						break;
					case 1:
						progdata.animates[gnu].room = ROOM_ROTSGROT;
						break;
					case 2:
						progdata.animates[gnu].room = ROOM_LEEGTE;
						break;
					case 3:
						progdata.animates[gnu].room = ROOM_ZANDBANK;
						break;
					case 4:
						progdata.animates[gnu].room = ROOM_OLIEGROT;
						break;
					}
				}
				
				progdata.status.curroom = progdata.rooms[progdata.status.curroom].connect[parsedata.selected];
				
				if (progdata.status.paperpos != paper_route_length)
				{
					if (progdata.status.curroom == progdata.paperroute[progdata.status.paperpos])
						progdata.status.paperpos++;
					else
						progdata.status.paperpos = 0;

					if (progdata.status.paperpos == paper_route_length)
						progdata.animates[hatch].status = hatch_opening;
				}
				return true;
			}
			else
				print_to_main_window("Daar kun je niet heen.\n");
			break;
		case use:
			DoGebruik(progdata, parsedata);
			break;
		case combine:
			DoCombineer(progdata, parsedata);
			break;
		case pickup:
			DoPak(progdata, parsedata);
			break;
		case lay_down:
			DoLeg(progdata, parsedata);
			break;
		case inspect:
			DoBekijk(progdata, parsedata);
			break;
		case wait:
			DoAfwachten();
			break;
		case finish:
			print_to_main_window("Weet je zeker dat je de aarde laat vergaan? ");
			if (tolower(advanced_getchar("jJnN")) == 'j')
				return false;
			print_to_main_window("\nMooi zo!\n");
			break;
		case status:
			DoStatus(progdata);
			break;
		case help:
			DoHelp();
			break;
		}

		print_to_main_window("\n");
	}
	while (parsedata.selected == status || parsedata.selected == help || parsedata.selected == finish);

	return true;
}

void DoGebruik(Progdata &progdata, Parsedata &parsedata)
{
	switch (progdata.owneditems[parsedata.object1])
	{
	case sword:

		int monster;

		if (progdata.animates[hellhound].room == progdata.status.curroom && progdata.animates[hellhound].strike)
			monster = hellhound;
		else if (progdata.animates[plant].room == progdata.status.curroom && progdata.animates[plant].strike)
			monster = plant;
		else
		{
			print_to_main_window("Dat heeft geen zin.\n\n");
			return;
		}

		while (true)
		{
			print_to_main_window("Je haalt uit met je zwaard");

			if (get_random_number(100) > 70)
				print_to_main_window(", maar het monster ontwijkt.\n");
			else
			{
				print_to_main_window(" en je raakt het monster hard.\n");
				progdata.animates[monster].strike--;
			}

			if (progdata.animates[monster].strike == 1)
				print_to_main_window("\nHet monster is zwaar gewond en je baadt in zijn bloed.\n");

			if (!progdata.animates[monster].strike || get_random_number(100) > 30)
				break;

			print_to_main_window("\nJe kunt nog een slag uitdelen. Wil je dat? ");

			if (tolower(advanced_getchar("jJnN")) != 'j')
			{
				print_to_main_window("\n");
				break;
			}

			print_to_main_window("\n");
		}
		print_to_main_window("\n");

		if (!progdata.animates[monster].strike)
		{
			progdata.animates[monster].status = dead;
			progress_animate_status(progdata);
		}

		wait_for_key();
		break;

	case flashlight:

		if (progdata.status.lamp)
		{
			progdata.status.lamp = !progdata.status.lamp;
			print_to_main_window("Je zet de zaklamp uit.%s", IsRoomLit(progdata.status) ? "\n" : " Je ziet niets meer.\n");
			break;
		}

		if (progdata.status.lamppoints)
		{
			progdata.status.lamp = !progdata.status.lamp;
			print_to_main_window("Je zet de zaklamp aan. De straal verlicht de omtrek.\n");
		}
		else
			print_to_main_window("Zonder nieuwe batterijen doet'ie het niet...\n");

		break;

	case bandage:

		if (progdata.status.lifepoints == max_life_points)
		{
			print_to_main_window("Je bent nog helemaal heel!\n");
			break;
		}

		print_to_main_window("Je pakt het verband en de pleisters en plaatst ze over je wonden. Je bijt even\n"
				 "op je lippen van de pijn als het verband je nog bloedende wonden raakt.\n\n"
				 "Je bent weer zo goed als nieuw.\n");

		progdata.status.lifepoints = max_life_points;
		progdata.items[bandage].room = undefined;
		progdata.owneditems[parsedata.object1] = undefined;

		wait_for_key();
		break;

	case tnt:

		print_to_main_window("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samen-\n"
				 "gaat met een harde knal. Je wordt even verblind door de flits van de ontplof-\n"
				 "fing. Door de klap val je even flauw.\n");

		progdata.status.lifepoints--;

		wait_for_key();
		break;

	case thermal_suit:

		print_to_main_window("Je hebt het pak al aan.\n");

		break;

	case gasmask:

		print_to_main_window("Je hebt het gasmasker al op.\n");

		break;

	default:

		if (progdata.items[progdata.owneditems[parsedata.object1]].useableon < 0
			 || progdata.animates[progdata.items[progdata.owneditems[parsedata.object1]].useableon].room != progdata.status.curroom)
		{
			print_to_main_window("Dat heeft geen zin.\n\n");
			break;
		}

		switch (progdata.owneditems[parsedata.object1])
		{

		case bone:

			progdata.animates[door].status = door_open;

			break;

		case diskette:

			UseItemToStatus(progdata, parsedata.object1, computer, computer_is_reading);

			break;

		case hashis:

			UseItemToStatus(progdata, parsedata.object1, barbecue, progdata.animates[barbecue].status == initial_burn
				? hashis_on_fire : cookie_is_baking);

			break;

		case hound_meat:

			UseItemToStatus(progdata, parsedata.object1, barbecue, progdata.animates[barbecue].status == initial_burn
				? meat_on_fire : cookie_is_baking);

			break;

		case red_crystal:
		case green_crystal:
		case blue_crystal:

			UseItemToStatus(progdata, parsedata.object1, dragon_head, progdata.animates[dragon_head].status + 1);

			break;

		case cookie:

			UseItemToStatus(progdata, parsedata.object1, dragon, cookie_is_thrown);

			break;

		case nightcap:

			if (progdata.animates[dragon].status != sleeping_lightly)
			{
				print_to_main_window("Dat heeft geen zin.\n\n");
				return;
			}

			UseItemToStatus(progdata, parsedata.object1, dragon, nightcap_on_head);

			break;

		case bomb:

			UseItemToStatus(progdata, parsedata.object1, lava, bomb_dropped);

			break;

		case flamethrower:

			UseItemToStatus(progdata, parsedata.object1, tree, tree_on_fire);

			break;

		case poisined_meat:

			UseItemToStatus(progdata, parsedata.object1, gnu, poisonous_meat_fed);

			break;

		case booklet:

			UseItemToStatus(progdata, parsedata.object1, red_troll, booklet_thrown);

			break;

		case gas_grenade:

			UseItemToStatus(progdata, parsedata.object1, swelling, swelling_gassed);

			break;
		}

		progress_animate_status(progdata);

		wait_for_key();
		break;
	}
}

void UseItemToStatus(Progdata &progdata, int ownedindex, int beast, int status)
{
	progdata.items[progdata.owneditems[ownedindex]].room = undefined;
	progdata.owneditems[ownedindex] = undefined;
	progdata.animates[beast].status = status;
}

void DoCombineer(Progdata &progdata, Parsedata &parsedata)
{
	if (progdata.items[progdata.owneditems[parsedata.object1]].useableon > -2
		 || connectToItem(progdata.items[progdata.owneditems[parsedata.object1]].useableon) != progdata.owneditems[parsedata.object2])
	{
		print_to_main_window("Dat levert niets bruikbaars op.\n");
		return;
	}

	switch(progdata.owneditems[parsedata.object1])
	{
	case flashlight:
	case batteries:

		print_to_main_window("Je schroeft de zaklamp open en schudt totdat de oude batterijen er uit komen\n"
				 "vallen. Daarna steek je de \"trommelbatterijen\" erin en schroeft de lamp weer\n"
				 "dicht. Nadat je een paar keer op de zaklantaarn hebt geslagen zie je dat hij\n"
				 "het doet.\n");

		progdata.status.lamppoints = undefined;
		progdata.items[batteries].room = undefined;

		if (progdata.owneditems[parsedata.object1] == batteries)
			progdata.owneditems[parsedata.object1] = undefined;
		else
			progdata.owneditems[parsedata.object2] = undefined;

		break;

	case gas_capsule:
	case ignition:

		print_to_main_window("Je plaatst de ontsteker op het mosterdgaspatroon. Na enig friemelen is het\n"
				 "resultaat een werkende mosterdgasgranaat.\n");

		progdata.items[gas_capsule].room = undefined;
		progdata.items[ignition].room = undefined;
		progdata.items[gas_grenade].room = item_owned;

		progdata.owneditems[parsedata.object1] = gas_grenade;
		progdata.owneditems[parsedata.object2] = undefined;

		break;
	}
}

void DoLeg(Progdata &progdata, Parsedata &parsedata)
{
	if (progdata.owneditems[parsedata.object1] == flashlight)
	{
		print_to_main_window("Je bent inmiddels zo aan je zaklamp gehecht geraakt dat je hem niet meer kunt\n"
				 "missen.\n");

		return;
	}

	if (progdata.owneditems[parsedata.object1] == batteries)
	{
		print_to_main_window("Je bent inmiddels zo aan je batterijen gehecht geraakt dat je ze niet meer kunt\n"
				 "missen.\n");

		return;
	}

	print_to_main_window("Je legt %s neer.\n", progdata.items[progdata.owneditems[parsedata.object1]].name);

	progdata.items[progdata.owneditems[parsedata.object1]].room = progdata.status.curroom;
	progdata.owneditems[parsedata.object1] = undefined;
}

void DoPak(Progdata &progdata, Parsedata &parsedata)
{
	int i;

	for (i = 0; i < 10; i++)
		if (progdata.owneditems[i] == undefined)
			break;

	if (i == 10)
	{
		print_to_main_window("Je zakken zitten tjokvol, en je krijgt %s er niet in.\n", progdata.items[parsedata.object1].name);
		return;
	}

	print_to_main_window("Je pakt %s op en steekt deze in een van je zakken.\n", progdata.items[parsedata.object1].name);

	progdata.items[parsedata.object1].room = item_owned;
	progdata.owneditems[i] = parsedata.object1;
}

void DoBekijk(Progdata &progdata, Parsedata &parsedata)
{
	if (!IsRoomLit(progdata.status))
	{
		print_to_main_window("Het is veel te donker om wat dan ook te bekijken.\n");
		return;
	}

	write_to_main_window(progdata.items[progdata.owneditems[parsedata.object1]].descript);
	print_to_main_window("\n");
}

void DoAfwachten(void)
{
	switch(get_random_number(5))
	{
	case 0:

		print_to_main_window("Je pulkt wat in je neus.\n");
		break;

	case 1:

		print_to_main_window("Je krabt wat achter je oren.\n");
		break;

	case 2:

		print_to_main_window("Je gaapt even uitgebreid.\n");
		break;

	case 3:

		print_to_main_window("Je trekt je broek even op.\n");
		break;

	case 4:

		print_to_main_window("Je pulkt wat smeer uit je oren.\n");
		break;

	}
}

void DoStatus(Progdata &progdata)
{
	int i;
	int count = 0;

	print_to_main_window("--- STATUSRAPPORT ---\n\n");
	print_to_main_window("Je hebt nog %d levenspunten.\n", progdata.status.lifepoints);

	if (progdata.items[flashlight].room == item_owned)
		print_to_main_window("Je zaklamp staat %s.\n", progdata.status.lamp ? "aan" : "uit");

	for (i = 0; i < 10; i++)
		if (progdata.owneditems[i] != undefined)
			count++;

	if (!count)
		print_to_main_window("Je draagt niets.\n");
	else
	{
		print_to_main_window("Je hebt in je bezit:\n");
		for (i = 0; i < 10; i++)
			if (progdata.owneditems[i] != undefined)
				print_to_main_window("    %s\n", progdata.items[progdata.owneditems[i]].name);
	}
}

void DoHelp(void)
{
	print_to_main_window("--- HELP ---\n\n");
	print_to_main_window("Commando's:\n");
	print_to_main_window("   oost\n");
	print_to_main_window("   west\n");
	print_to_main_window("   noord\n");
	print_to_main_window("   zuid\n");
	print_to_main_window("   klim\n");
	print_to_main_window("   daal\n");
	print_to_main_window("   gebruik <voorwerp>\n");
	print_to_main_window("   combineer <voorwerp> en/met <voorwerp>\n");
	print_to_main_window("   pak <voorwerp>\n");
	print_to_main_window("   leg <voorwerp>\n");
	print_to_main_window("   bekijk <voorwerp>\n");
	print_to_main_window("   afwachten\n");
	print_to_main_window("   einde\n");
	print_to_main_window("   status\n");
	print_to_main_window("   help\n");
}

void ParseInput(Progdata &progdata, char *inpstr, Parsedata &parsedata)
{
	char *eoword;
	char *curp;
	char workstr[65];
	int i;

	parsedata.parseerror = false;

	strncpy(workstr, inpstr, 64);
	workstr[64] = 0;

	// trim input at both sides
	for (i = (int)strlen(workstr) - 1; i >= 0 && workstr[i] == ' '; i--);
	workstr[i + 1] = 0;
	for (curp = workstr; curp < (workstr + strlen(workstr)) && *curp == ' '; curp++);

	eoword = strchr(curp, ' ');
	if (eoword == NULL)
		eoword = curp + strlen(curp);

	// 9 is the length of the longest commands
	if (eoword == curp || eoword > curp + 9)
	{
		parsedata.parseerror = true;

		if (eoword == curp)
			print_command_string("< geen commando gegeven");
		else
			print_command_string("< ongeldig commando gegeven");

		return;
	}

	parsedata.selected = undefined;

	for (i = 0; parsedata.selected == undefined && i < COMMAND_COUNT; i++)
	{
		// this search assumes that the commands each start with a different letter
		// it finds the first command that starts with whatever is the command (abbreviation) entered by the user 
		if (!strncmp(cmds[i], curp, int(eoword - curp)))
			parsedata.selected = i;
	}

	switch (parsedata.selected)
	{
	case undefined:

		print_command_string("< ongeldig commando gegeven");
		parsedata.parseerror = true;
		return;

	case use:
	case lay_down:
	case inspect:

		ParseSingleOwnedItemCommandParam(progdata, parsedata, cmds[parsedata.selected], eoword);	
		break;

	case combine:

		ParseCombineItemsParameters(progdata, parsedata, eoword);
		break;

	case pickup:

		if (*eoword != ' ')
		{
			print_command_string("< syntax: pak <voorwerp>");
			parsedata.parseerror = true;

			return;
		}

		parsedata.object1 = FindLayingItemNum(progdata, eoword + 1);
		CheckFoundObject(parsedata, parsedata.object1, eoword + 1, "< je ziet hier geen \"%s\" die je kunt meenemen");

		break;
	}
}

void ParseCombineItemsParameters(Progdata &progdata, Parsedata& parsedata, const char* currentMatch)
{
	const char* previousMatch;
	char itemname[25];

	if (*currentMatch != ' ' || (!strstr(currentMatch + 1, " en ") && !strstr(currentMatch + 1, " met ")))
	{
		print_command_string("< syntax: combineer <voorwerp> en/met <voorwerp>");
		parsedata.parseerror = true;

		return;
	}

	previousMatch = currentMatch + 1;

	// first item ends with interjection word
	if (!(currentMatch = strstr(previousMatch, " en ")))
		currentMatch = strstr(previousMatch, " met ");

	int itemLength = (int)(currentMatch - previousMatch);

	if (itemLength > 24)
		itemLength = 24;

	strncpy(itemname, previousMatch, itemLength);
	itemname[itemLength] = 0;

	parsedata.object1 = FindOwnedItemNum(progdata, itemname);

	if (!CheckFoundObject(parsedata, parsedata.object1, itemname, dontOwnItemFormatString))
		return;

	// second item starts just after interjection word
	previousMatch = currentMatch + ((strstr(currentMatch, " en ") == currentMatch) ? 4 : 5);

	itemLength = (int)strlen(previousMatch);

	if (itemLength >= 25)
		itemLength = 24;

	strncpy(itemname, previousMatch, itemLength);
	itemname[itemLength] = 0;

	parsedata.object2 = FindOwnedItemNum(progdata, itemname);

	if (!CheckFoundObject(parsedata, parsedata.object2, itemname, dontOwnItemFormatString))
		return;
	
	if (parsedata.object1 == parsedata.object2)
	{
		print_command_string("< je kunt een voorwerp niet met zichzelf combineren");
		parsedata.parseerror = true;
	}
}

bool ParseSingleOwnedItemCommandParam(Progdata &progdata, Parsedata& parsedata, const char* command, const char* parseString)
{
	if (*parseString != ' ')
	{
		print_command_string("< syntax: %s <voorwerp>", command);
		parsedata.parseerror = true;

		return false;
	}

	parsedata.object1 = FindOwnedItemNum(progdata, parseString + 1);

	return CheckFoundObject(parsedata, parsedata.object1, parseString + 1, dontOwnItemFormatString);
}

bool CheckFoundObject(Parsedata& parsedata, char itemNum, const char* itemname, const char* undefinedItemFormatString)
{
	switch (itemNum)
	{
	case undefined:

		print_command_string(undefinedItemFormatString, itemname);
		parsedata.parseerror = true;

		return false;

	case AMBIGUOUS:

		print_command_string("< de afkorting \"%s\" is dubbelzinnig", itemname);
		parsedata.parseerror = true;

		return false;
	}

	return true;
}

int FindOwnedItemNum(Progdata &progdata, const char *itemname)
{
	int item = undefined;
	int i;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (i = 0; i < 10 && item != AMBIGUOUS; i++)
		if (progdata.owneditems[i] != undefined && strstr(progdata.items[progdata.owneditems[i]].name, itemname))
			item = ((item == undefined) ? i : AMBIGUOUS);

	return item;
}

bool IsRoomLit(Status& status) 
{
	return status.curroom < ROOM_SLIJMGROT || status.lamp
		|| status.curroom == ROOM_RADIOACTIEVEGROT || status.curroom == ROOM_TLGROT;
}

int FindLayingItemNum(Progdata &progdata, const char *itemname)
{
	int item = undefined;
	int i;

	if (!IsRoomLit(progdata.status))
		return undefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (i = 0; i < COUNT && item != AMBIGUOUS; i++)
		if (progdata.status.curroom == progdata.items[i].room && strstr(progdata.items[i].name, itemname))
			item = ((item == undefined) ? i : AMBIGUOUS);

	return item;
}


