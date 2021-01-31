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
		printmw("Badend in je eigen bloed bezwijk je aan je verwondingen. Terwijl je liggend op\n");
		printmw("de grond met moeite naar adem snakt, hoor je in de verte een luid gelach.\n");
		printmw("Dan zakken je ogen dicht en stopt je hart met kloppen.\n");
		printmw("Op hetzelfde moment ontploft de bom en sterft de aarde met jou.\n\n");
		ForceExit();
	}

	if (progdata.status.lamppoints > 0 && progdata.status.lamp)
	{
		switch(--progdata.status.lamppoints)
		{
		case 10:
			printmw("De zaklamp gaat zwakker branden.\n\n");
			break;
		case 0:
			printmw("De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij.\n\n");
			progdata.status.lamp = false;
			break;
		}
	}

	do
	{
		char inpstr[65];

		do 
		{
			getcmdstr(inpstr, 64);
			ParseInput(progdata, inpstr, parsedata);
		} 
		while (parsedata.parseerror);

		printcentered(MAINWINDOW, "---***---");
		printmw("\n\n");

		switch(parsedata.selected)
		{
		case DO_EAST:
		case DO_WEST:
		case DO_NORTH:
		case DO_SOUTH:
		case DO_UP:
		case DO_DOWN:
			if (progdata.rooms[progdata.status.curroom].connect[parsedata.selected] >= 0)
			{
				if (progdata.living[LIVING_GNOE].room == progdata.status.curroom && progdata.living[LIVING_GNOE].status != STATUS_LIVING_DEAD)
				{
					switch (random(5))
					{
					case 0:
						progdata.living[LIVING_GNOE].room = ROOM_GNOEGROT;
						break;
					case 1:
						progdata.living[LIVING_GNOE].room = ROOM_ROTSGROT;
						break;
					case 2:
						progdata.living[LIVING_GNOE].room = ROOM_LEEGTE;
						break;
					case 3:
						progdata.living[LIVING_GNOE].room = ROOM_ZANDBANK;
						break;
					case 4:
						progdata.living[LIVING_GNOE].room = ROOM_OLIEGROT;
						break;
					}
				}
				
				progdata.status.curroom = progdata.rooms[progdata.status.curroom].connect[parsedata.selected];
				
				if (progdata.status.paperpos != PAPERROUTE_LENGTH)
				{
					if (progdata.status.curroom == progdata.paperroute[progdata.status.paperpos])
						progdata.status.paperpos++;
					else
						progdata.status.paperpos = 0;

					if (progdata.status.paperpos == PAPERROUTE_LENGTH)
						progdata.living[LIVING_PAPIER].status = STATUS_PAPIER_OPENING;
				}
				return true;
			}
			else
				printmw("Daar kun je niet heen.\n");
			break;
		case DO_GEBRUIK:
			DoGebruik(progdata, parsedata);
			break;
		case DO_COMBINEER:
			DoCombineer(progdata, parsedata);
			break;
		case DO_PAK:
			DoPak(progdata, parsedata);
			break;
		case DO_LEG:
			DoLeg(progdata, parsedata);
			break;
		case DO_BEKIJK:
			DoBekijk(progdata, parsedata);
			break;
		case DO_AFWACHTEN:
			DoAfwachten();
			break;
		case DO_EINDE:
			printmw("Weet je zeker dat je de aarde laat vergaan? ");
			if (tolower(agetchar("jJnN")) == 'j')
				return false;
			printmw("\nMooi zo!\n");
			break;
		case DO_STATUS:
			DoStatus(progdata);
			break;
		case DO_HELP:
			DoHelp();
			break;
		}

		printmw("\n");
	}
	while (parsedata.selected == DO_STATUS || parsedata.selected == DO_HELP || parsedata.selected == DO_EINDE);

	return true;
}

void DoGebruik(Progdata &progdata, Parsedata &parsedata)
{
	switch (progdata.owneditems[parsedata.object1])
	{
	case ITEM_ZWAARD:
		int monster;
		if (progdata.living[LIVING_HELLEHOND].room == progdata.status.curroom && progdata.living[LIVING_HELLEHOND].strike)
			monster = LIVING_HELLEHOND;
		else if (progdata.living[LIVING_PLANT].room == progdata.status.curroom && progdata.living[LIVING_PLANT].strike)
			monster = LIVING_PLANT;
		else
		{
			printmw("Dat heeft geen zin.\n\n");
			return;
		}

		while (true)
		{
			printmw("Je haalt uit met je zwaard");
			if (random(100) > 70)
				printmw(", maar het monster ontwijkt.\n");
			else
			{
				printmw(" en je raakt het monster hard.\n");
				progdata.living[monster].strike--;
			}
			if (progdata.living[monster].strike == 1)
				printmw("\nHet monster is zwaar gewond en je baadt in zijn bloed.\n");
			if (!progdata.living[monster].strike || random(100) > 30)
				break;
			printmw("\nJe kunt nog een slag uitdelen. Wil je dat? ");
			if (tolower(agetchar("jJnN")) != 'j')
			{
				printmw("\n");
				break;
			}
			printmw("\n");
		}
		printmw("\n");
		if (!progdata.living[monster].strike)
		{
			progdata.living[monster].status = STATUS_LIVING_DEAD;
			LivingStatus(progdata);
		}
		waitforkey();
		break;
	case ITEM_ZAKLAMP:
		if (progdata.status.lamp)
		{
			progdata.status.lamp = !progdata.status.lamp;
			printmw("Je zet de zaklamp uit.%s", IsRoomLit(progdata.status) ? "\n" : " Je ziet niets meer.\n");
			break;
		}
		if (progdata.status.lamppoints)
		{
			progdata.status.lamp = !progdata.status.lamp;
			printmw("Je zet de zaklamp aan. De straal verlicht de omtrek.\n");
		}
		else
			printmw("Zonder nieuwe batterijen doet'ie het niet...\n");
		break;
	case ITEM_VERBAND:
		if (progdata.status.lifepoints == MAX_LIFEPOINTS)
		{
			printmw("Je bent nog helemaal heel!\n");
			break;
		}
		printmw("Je pakt het verband en de pleisters en plaatst ze over je wonden. Je bijt even\n"
				 "op je lippen van de pijn als het verband je nog bloedende wonden raakt.\n\n"
				 "Je bent weer zo goed als nieuw.\n");
		progdata.status.lifepoints = MAX_LIFEPOINTS;
		progdata.items[ITEM_VERBAND].room = UNDEFINED;
		progdata.owneditems[parsedata.object1] = UNDEFINED;
		waitforkey();
		break;
	case ITEM_TNT:
		printmw("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samen-\n"
				 "gaat met een harde knal. Je wordt even verblind door de flits van de ontplof-\n"
				 "fing. Door de klap val je even flauw.\n");
		progdata.status.lifepoints--;
		waitforkey();
		break;
	case ITEM_HITTEPAK:
		printmw("Je hebt het pak al aan.\n");
		break;
	case ITEM_GASMASKER:
		printmw("Je hebt het gasmasker al op.\n");
		break;
	default:
		if (progdata.items[progdata.owneditems[parsedata.object1]].useableon < 0
			 || progdata.living[progdata.items[progdata.owneditems[parsedata.object1]].useableon].room != progdata.status.curroom)
		{
			printmw("Dat heeft geen zin.\n\n");
			break;
		}
		switch (progdata.owneditems[parsedata.object1])
		{
		case ITEM_BOT:
			progdata.living[LIVING_DEUR].status = STATUS_DEUR_OPEN;
			break;
		case ITEM_DISKETTE:
			UseItemToStatus(progdata, parsedata.object1, LIVING_COMPUTER, STATUS_COMPUTER_READING);
			break;
		case ITEM_HASJ:
			UseItemToStatus(progdata, parsedata.object1, LIVING_BARBECUE, progdata.living[LIVING_BARBECUE].status == STATUS_BARBECUE_INITIALBURN
				? STATUS_BARBECUE_HASJONFIRE : STATUS_BARBECUE_KOEKJEBAKING);
			break;
		case ITEM_HONDVLEES:
			UseItemToStatus(progdata, parsedata.object1, LIVING_BARBECUE, progdata.living[LIVING_BARBECUE].status == STATUS_BARBECUE_INITIALBURN
				? STATUS_BARBECUE_VLEESONFIRE : STATUS_BARBECUE_KOEKJEBAKING);
			break;
		case ITEM_ROODKRISTAL:
		case ITEM_GROENKRISTAL:
		case ITEM_BLAUWKRISTAL:
			UseItemToStatus(progdata, parsedata.object1, LIVING_DRAKEKOP, progdata.living[LIVING_DRAKEKOP].status + 1);
			break;
		case ITEM_KOEKJE:
			UseItemToStatus(progdata, parsedata.object1, LIVING_DRAAK, STATUS_DRAAK_KOEKJETHROWN);
			break;
		case ITEM_SLAAPMUTS:
			if (progdata.living[LIVING_DRAAK].status != STATUS_DRAAK_LIGHTSLEEPING)
			{
				printmw("Dat heeft geen zin.\n\n");
				return;
			}
			UseItemToStatus(progdata, parsedata.object1, LIVING_DRAAK, STATUS_DRAAK_SLAAPMUTSONHEAD);
			break;
		case ITEM_BOM:
			UseItemToStatus(progdata, parsedata.object1, LIVING_LAVA, STATUS_LAVA_BOMDROPPED);
			break;
		case ITEM_VLAMMENWERPER:
			UseItemToStatus(progdata, parsedata.object1, LIVING_BOOM, STATUS_BOOM_SETONFIRE);
			break;
		case ITEM_GIFTIGVLEES:
			UseItemToStatus(progdata, parsedata.object1, LIVING_GNOE, STATUS_GNOE_GIFTIGVLEESFED);
			break;
		case ITEM_BOEKJE:
			UseItemToStatus(progdata, parsedata.object1, LIVING_RODETROL, STATUS_RODETROL_BOEKJETHROWN);
			break;
		case ITEM_GASGRANAAT:
			UseItemToStatus(progdata, parsedata.object1, LIVING_GEZWEL, STATUS_GEZWEL_GASSED);
			break;
		}
		LivingStatus(progdata);
		waitforkey();
		break;
	}
}

void UseItemToStatus(Progdata &progdata, int ownedindex, int beast, int status)
{
	progdata.items[progdata.owneditems[ownedindex]].room = UNDEFINED;
	progdata.owneditems[ownedindex] = UNDEFINED;
	progdata.living[beast].status = status;
}

void DoCombineer(Progdata &progdata, Parsedata &parsedata)
{
	if (progdata.items[progdata.owneditems[parsedata.object1]].useableon > -2
		 || connectToItem(progdata.items[progdata.owneditems[parsedata.object1]].useableon) != progdata.owneditems[parsedata.object2])
	{
		printmw("Dat levert niets bruikbaars op.\n");
		return;
	}

	switch(progdata.owneditems[parsedata.object1])
	{
	case ITEM_ZAKLAMP:
	case ITEM_BATTERIJEN:
		printmw("Je schroeft de zaklamp open en schudt totdat de oude batterijen er uit komen\n"
				 "vallen. Daarna steek je de \"trommelbatterijen\" erin en schroeft de lamp weer\n"
				 "dicht. Nadat je een paar keer op de zaklantaarn hebt geslagen zie je dat hij\n"
				 "het doet.\n");
		progdata.status.lamppoints = UNDEFINED;
		progdata.items[ITEM_BATTERIJEN].room = UNDEFINED;
		if (progdata.owneditems[parsedata.object1] == ITEM_BATTERIJEN)
			progdata.owneditems[parsedata.object1] = UNDEFINED;
		else
			progdata.owneditems[parsedata.object2] = UNDEFINED;
		break;
	case ITEM_GASPATROON:
	case ITEM_ONTSTEKING:
		printmw("Je plaatst de ontsteker op het mosterdgaspatroon. Na enig friemelen is het\n"
				 "resultaat een werkende mosterdgasgranaat.\n");
		progdata.items[ITEM_GASPATROON].room = UNDEFINED;
		progdata.items[ITEM_ONTSTEKING].room = UNDEFINED;
		progdata.items[ITEM_GASGRANAAT].room = STATUS_ITEM_OWNED;
		progdata.owneditems[parsedata.object1] = ITEM_GASGRANAAT;
		progdata.owneditems[parsedata.object2] = UNDEFINED;
		break;
	}
}

void DoLeg(Progdata &progdata, Parsedata &parsedata)
{
	if (progdata.owneditems[parsedata.object1] == ITEM_ZAKLAMP)
	{
		printmw("Je bent inmiddels zo aan je zaklamp gehecht geraakt dat je hem niet meer kunt\n"
				 "missen.\n");
		return;
	}
	if (progdata.owneditems[parsedata.object1] == ITEM_BATTERIJEN)
	{
		printmw("Je bent inmiddels zo aan je batterijen gehecht geraakt dat je ze niet meer kunt\n"
				 "missen.\n");
		return;
	}
	printmw("Je legt %s neer.\n", progdata.items[progdata.owneditems[parsedata.object1]].name);
	progdata.items[progdata.owneditems[parsedata.object1]].room = progdata.status.curroom;
	progdata.owneditems[parsedata.object1] = UNDEFINED;
}

void DoPak(Progdata &progdata, Parsedata &parsedata)
{
	int i;

	for (i = 0; i < 10; i++)
		if (progdata.owneditems[i] == UNDEFINED)
			break;

	if (i == 10)
	{
		printmw("Je zakken zitten tsjokvol, en je krijgt %s er niet in.\n", progdata.items[parsedata.object1].name);
		return;
	}

	printmw("Je pakt %s op en steekt deze in een van je zakken.\n", progdata.items[parsedata.object1].name);

	progdata.items[parsedata.object1].room = STATUS_ITEM_OWNED;
	progdata.owneditems[i] = parsedata.object1;
}

void DoBekijk(Progdata &progdata, Parsedata &parsedata)
{
	if (!IsRoomLit(progdata.status))
	{
		printmw("Het is veel te donker om wat dan ook te bekijken.\n");
		return;
	}

	printmw("%s\n", progdata.items[progdata.owneditems[parsedata.object1]].descript);
}

void DoAfwachten(void)
{
	switch(random(5))
	{
	case 0:
		printmw("Je pulkt wat in je neus.\n");
		break;
	case 1:
		printmw("Je krabt wat achter je oren.\n");
		break;
	case 2:
		printmw("Je gaapt even uitgebreid.\n");
		break;
	case 3:
		printmw("Je trekt je broek even op.\n");
		break;
	case 4:
		printmw("Je pulkt wat smeer uit je oren.\n");
		break;
	}
}

void DoStatus(Progdata &progdata)
{
	int i;
	int count = 0;

	printmw("--- STATUSRAPPORT ---\n\n");
	printmw("Je hebt nog %d levenspunten.\n", progdata.status.lifepoints);
	if (progdata.items[ITEM_ZAKLAMP].room == STATUS_ITEM_OWNED)
		printmw("Je zaklamp staat %s.\n", progdata.status.lamp ? "aan" : "uit");

	for (i = 0; i < 10; i++)
		if (progdata.owneditems[i] != UNDEFINED)
			count++;

	if (!count)
		printmw("Je draagt niets.\n");
	else
	{
		printmw("Je hebt in je bezit:\n");
		for (i = 0; i < 10; i++)
			if (progdata.owneditems[i] != UNDEFINED)
				printmw("    %s\n", progdata.items[progdata.owneditems[i]].name);
	}
}

void DoHelp(void)
{
	printmw("--- HELP ---\n\n");
	printmw("Commando's:\n");
	printmw("   oost\n");
	printmw("   west\n");
	printmw("   noord\n");
	printmw("   zuid\n");
	printmw("   klim\n");
	printmw("   daal\n");
	printmw("   gebruik <voorwerp>\n");
	printmw("   combineer <voorwerp> en/met <voorwerp>\n");
	printmw("   pak <voorwerp>\n");
	printmw("   leg <voorwerp>\n");
	printmw("   bekijk <voorwerp>\n");
	printmw("   afwachten\n");
	printmw("   einde\n");
	printmw("   status\n");
	printmw("   help\n");
}

void ParseInput(Progdata &progdata, char *inpstr, Parsedata &parsedata)
{
	char *eoword;
	char *curp;
	char workstr[65];
	int i;

	parsedata.parseerror = false;

	strcpy_s(workstr, inpstr);

	for (i = (int)strlen(workstr) - 1; i >= 0 && workstr[i] == ' '; i--);
	workstr[i + 1] = 0;
	for (curp = workstr; curp < (workstr + strlen(workstr)) && *curp == ' '; curp++);

	eoword = strchr(curp, ' ');
	if (eoword == NULL)
		eoword = curp + strlen(curp);

	if (eoword == curp || eoword > curp + 9)
	{
		parsedata.parseerror = true;

		if (eoword == curp)
			printcmdstr("< geen commando gegeven");
		else
			printcmdstr("< ongeldig commando gegeven");
		return;
	}

	parsedata.selected = UNDEFINED;

	for (i = 0; parsedata.selected == UNDEFINED && i < COMMAND_COUNT; i++)
	{
		if (!strncmp(cmds[i], curp, int(eoword - curp)))
			parsedata.selected = i;
	}

	switch (parsedata.selected)
	{
	case UNDEFINED:
		printcmdstr("< ongeldig commando gegeven");
		parsedata.parseerror = true;
		return;

	case DO_GEBRUIK:
	case DO_LEG:
	case DO_BEKIJK:
		ParseSingleOwnedItemCommandParam(progdata, parsedata, cmds[parsedata.selected], eoword);	
		break;

	case DO_COMBINEER:
		ParseCombineItemsParameters(progdata, parsedata, eoword);
		break;

	case DO_PAK:
		if (*eoword != ' ')
		{
			printcmdstr("< syntax: pak <voorwerp>");
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
		printcmdstr("< syntax: combineer <voorwerp> en/met <voorwerp>");
		parsedata.parseerror = true;
		return;
	}

	previousMatch = currentMatch + 1;
	if (!(currentMatch = strstr(previousMatch, " en ")))
		currentMatch = strstr(previousMatch, " met ");

	int itemLength = (int)(currentMatch - previousMatch);
	if (itemLength >= 25)
		itemLength = 24;

	strncpy_s(itemname, previousMatch, itemLength);
	itemname[itemLength] = 0;

	parsedata.object1 = FindOwnedItemNum(progdata, itemname);
	if (!CheckFoundObject(parsedata, parsedata.object1, itemname, dontOwnItemFormatString))
		return;

	previousMatch = currentMatch + ((strstr(currentMatch, " en ") == currentMatch) ? 4 : 5);

	itemLength = (int)strlen(previousMatch);
	if (itemLength >= 25)
		itemLength = 24;

	strncpy_s(itemname, previousMatch, itemLength);
	itemname[itemLength] = 0;

	parsedata.object2 = FindOwnedItemNum(progdata, itemname);
	if (!CheckFoundObject(parsedata, parsedata.object2, itemname, dontOwnItemFormatString))
		return;
	
	if (parsedata.object1 == parsedata.object2)
	{
		printcmdstr("< je kunt een voorwerp niet met zichzelf combineren");
		parsedata.parseerror = true;
	}
}

bool ParseSingleOwnedItemCommandParam(Progdata &progdata, Parsedata& parsedata, const char* command, const char* parseString)
{
	if (*parseString != ' ')
	{
		printcmdstr("< syntax: %s <voorwerp>", command);
		parsedata.parseerror = true;
		return false;
	}
	parsedata.object1 = FindOwnedItemNum(progdata, parseString + 1);

	return CheckFoundObject(parsedata, parsedata.object1, parseString + 1, dontOwnItemFormatString);
}

bool CheckFoundObject(Parsedata& parsedata, char itemNum, const char* itemname, const char* undefinedItemFormatString)
{
	switch (parsedata.object1)
	{
	case UNDEFINED:
		printcmdstr(undefinedItemFormatString, itemname);
		parsedata.parseerror = true;
		return false;
	case AMBIGUOUS:
		printcmdstr("< de afkorting \"%s\" is dubbelzinnig", itemname);
		parsedata.parseerror = true;
		return false;
	}

	return true;
}

int FindOwnedItemNum(Progdata &progdata, const char *itemname)
{
	int item = UNDEFINED;
	int i;

	for (i = 0; i < 10 && item != AMBIGUOUS; i++)
		if (progdata.owneditems[i] != UNDEFINED)
			if (strstr(progdata.items[progdata.owneditems[i]].name, itemname))
				item = ((item == UNDEFINED) ? i : AMBIGUOUS);

	return item;
}

bool IsRoomLit(Status& status) 
{
	return status.curroom < ROOM_SLIJMGROT || status.lamp
		|| status.curroom == ROOM_RADIOACTIEVEGROT || status.curroom == ROOM_TLGROT;
}

int FindLayingItemNum(Progdata &progdata, const char *itemname)
{
	int item = UNDEFINED;
	int i;

	if (!IsRoomLit(progdata.status))
		return UNDEFINED;

	for (i = 0; i < ITEM_COUNT && item != AMBIGUOUS; i++)
		if (progdata.status.curroom == progdata.items[i].room && strstr(progdata.items[i].name, itemname))
			item = ((item == UNDEFINED) ? i : AMBIGUOUS);

	return item;
}


