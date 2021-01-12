#include "include.h"

#define COMMAND_COUNT	15
#define AMBIGUOUS		-2

const char* dontOwnItemFormatString = "%s< je hebt geen \"%s\"";

const char *cmds[COMMAND_COUNT] = {"oost", "west", "noord", "zuid", "klim", "daal", "gebruik",
							"combineer", "pak", "leg", "bekijk", "afwachten", "einde",
							"status", "help"};

bool DoAction(Progdata &progdata)
{
	char inpstr[65];
	Parsedata parsedata{};
	int cury;

	if (progdata.status.lifepoints <= 0)
	{
		_cprintf("Badend in je eigen bloed bezwijk je aan je verwondingen. Terwijl je liggend op\r\n"
				  "de grond met moeite naar adem snakt, hoor je in de verte een luid gelach.\r\n"
				  "Dan zakken je ogen dicht en stopt je hart met kloppen.\r\n"
				  "Op hetzelfde moment ontploft de bom en sterft de aarde met jou.\r\n\r\n");
		ForceExit();
	}

	if (progdata.status.lamppoints > 0 && progdata.status.lamp)
	{
		switch(--progdata.status.lamppoints)
		{
		case 10:
			_cprintf("De zaklamp gaat zwakker branden.\r\n\r\n");
			break;
		case 0:
			_cprintf("De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij.\r\n\r\n");
			progdata.status.lamp = false;
			break;
		}
	}

	do
	{
		cury = wherey();
		memset(inpstr, ' ', 64);
		inpstr[64] = 0;

		do
		{
			gotoxy(1, cury);
			_cprintf("> ");
			strinp(" abcdefghijklmnopqrstuvwxyz", inpstr, wherex(), wherey(), -1, 0, 0);
			gotoxy(1, cury);
			ParseInput(progdata, inpstr, parsedata);
		}
		while (parsedata.parseerror);

		_cprintf("\r\n\r\n");

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
				_cprintf("Daar kun je niet heen.\r\n");
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
			_cprintf("Weet je zeker dat je de aarde laat vergaan? ");
			if (tolower(agetchar("jJnN")) == 'j')
				return false;
			_cprintf("\r\nMooi zo!\r\n");
			break;
		case DO_STATUS:
			DoStatus(progdata);
			break;
		case DO_HELP:
			DoHelp();
			break;
		}

		_cprintf("\r\n");
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
			_cprintf("Dat heeft geen zin.\r\n\r\n");
			return;
		}

		while (true)
		{
			_cprintf("Je haalt uit met je zwaard");
			if (random(100) > 70)
				_cprintf(", maar het monster ontwijkt.\r\n");
			else
			{
				_cprintf(" en je raakt het monster hard.\r\n");
				progdata.living[monster].strike--;
			}
			if (progdata.living[monster].strike == 1)
				_cprintf("\r\nHet monster is zwaar gewond en je baadt in zijn bloed.\r\n");
			if (!progdata.living[monster].strike || random(100) > 30)
				break;
			_cprintf("\r\nJe kunt nog een slag uitdelen. Wil je dat? ");
			if (tolower(agetchar("jJnN")) != 'j')
			{
				_cprintf("\r\n");
				break;
			}
			_cprintf("\r\n");
		}
		_cprintf("\r\n");
		if (!progdata.living[monster].strike)
		{
			progdata.living[monster].status = STATUS_LIVING_DEAD;
			LivingStatus(progdata);
		}
		(void)_getch();
		break;
	case ITEM_ZAKLAMP:
		if (progdata.status.lamp)
		{
			progdata.status.lamp = !progdata.status.lamp;
			_cprintf("Je zet de zaklamp uit.%s", IsRoomLit(progdata.status) ? "\r\n" : " Je ziet niets meer.\r\n");
			break;
		}
		if (progdata.status.lamppoints)
		{
			progdata.status.lamp = !progdata.status.lamp;
			_cprintf("Je zet de zaklamp aan. De straal verlicht de omtrek.\r\n");
		}
		else
			_cprintf("Zonder nieuwe batterijen doet'ie het niet...\r\n");
		break;
	case ITEM_VERBAND:
		if (progdata.status.lifepoints == MAX_LIFEPOINTS)
		{
			_cprintf("Je bent nog helemaal heel!\r\n");
			break;
		}
		_cprintf("Je pakt het verband en de pleisters en plaatst ze over je wonden. Je bijt even\r\n"
				 "op je lippen van de pijn als het verband je nog bloedende wonden raakt.\r\n\r\n"
				 "Je bent weer zo goed als nieuw.\r\n");
		progdata.status.lifepoints = MAX_LIFEPOINTS;
		progdata.items[ITEM_VERBAND].room = UNDEFINED;
		progdata.owneditems[parsedata.object1] = UNDEFINED;
		(void)_getch();
		break;
	case ITEM_TNT:
		_cprintf("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samen-\r\n"
				 "gaat met een harde knal. Je wordt even verblind door de flits van de ontplof-\r\n"
				 "fing. Door de klap val je even flauw.\r\n");
		progdata.status.lifepoints--;
		(void)_getch();
		break;
	case ITEM_HITTEPAK:
		_cprintf("Je hebt het pak al aan.\r\n");
		break;
	case ITEM_GASMASKER:
		_cprintf("Je hebt het gasmasker al op.\r\n");
		break;
	default:
		if (progdata.items[progdata.owneditems[parsedata.object1]].useableon < 0
			 || progdata.living[progdata.items[progdata.owneditems[parsedata.object1]].useableon].room != progdata.status.curroom)
		{
			_cprintf("Dat heeft geen zin.\r\n\r\n");
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
				_cprintf("Dat heeft geen zin.\r\n\r\n");
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
		(void)_getch();
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
		_cprintf("Dat levert niets bruikbaars op.\r\n");
		return;
	}

	switch(progdata.owneditems[parsedata.object1])
	{
	case ITEM_ZAKLAMP:
	case ITEM_BATTERIJEN:
		_cprintf("Je schroeft de zaklamp open en schudt totdat de oude batterijen er uit komen\r\n"
				 "vallen. Daarna steek je de \"trommelbatterijen\" erin en schroeft de lamp weer\r\n"
				 "dicht. Nadat je een paar keer op de zaklantaarn hebt geslagen zie je dat hij\r\n"
				 "het doet.\r\n");
		progdata.status.lamppoints = UNDEFINED;
		progdata.items[ITEM_BATTERIJEN].room = UNDEFINED;
		if (progdata.owneditems[parsedata.object1] == ITEM_BATTERIJEN)
			progdata.owneditems[parsedata.object1] = UNDEFINED;
		else
			progdata.owneditems[parsedata.object2] = UNDEFINED;
		break;
	case ITEM_GASPATROON:
	case ITEM_ONTSTEKING:
		_cprintf("Je plaatst de ontsteker op het mosterdgaspatroon. Na enig friemelen is het\r\n"
				 "resultaat een werkende mosterdgasgranaat.\r\n");
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
		_cprintf("Je bent inmiddels zo aan je zaklamp gehecht geraakt dat je hem niet meer kunt\r\n"
				 "missen.\r\n");
		return;
	}
	if (progdata.owneditems[parsedata.object1] == ITEM_BATTERIJEN)
	{
		_cprintf("Je bent inmiddels zo aan je batterijen gehecht geraakt dat je ze niet meer kunt\r\n"
				 "missen.\r\n");
		return;
	}
	_cprintf("Je legt %s neer.\r\n", progdata.items[progdata.owneditems[parsedata.object1]].name);
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
		_cprintf("Je zakken zitten tsjokvol, en je krijgt %s er niet in.\r\n", progdata.items[parsedata.object1].name);
		return;
	}

	_cprintf("Je pakt %s op en steekt deze in een van je zakken.\r\n", progdata.items[parsedata.object1].name);

	progdata.items[parsedata.object1].room = STATUS_ITEM_OWNED;
	progdata.owneditems[i] = parsedata.object1;
}

void DoBekijk(Progdata &progdata, Parsedata &parsedata)
{
	if (!IsRoomLit(progdata.status))
	{
		_cprintf("Het is veel te donker om wat dan ook te bekijken.\r\n");
		return;
	}

	_cprintf("%s\r\n", progdata.items[progdata.owneditems[parsedata.object1]].descript);
}

void DoAfwachten(void)
{
	switch(random(5))
	{
	case 0:
		_cprintf("Je pulkt wat in je neus.\r\n");
		break;
	case 1:
		_cprintf("Je krabt wat achter je oren.\r\n");
		break;
	case 2:
		_cprintf("Je gaapt even uitgebreid.\r\n");
		break;
	case 3:
		_cprintf("Je trekt je broek even op.\r\n");
		break;
	case 4:
		_cprintf("Je pulkt wat smeer uit je oren.\r\n");
		break;
	}
}

void DoStatus(Progdata &progdata)
{
	int i;
	int count = 0;

	_cprintf("--- STATUSRAPPORT ---\r\n\r\n");
	_cprintf("Je hebt nog %d levenspunten.\r\n", progdata.status.lifepoints);
	if (progdata.items[ITEM_ZAKLAMP].room == STATUS_ITEM_OWNED)
		_cprintf("Je zaklamp staat %s.\r\n", progdata.status.lamp ? "aan" : "uit");

	for (i = 0; i < 10; i++)
		if (progdata.owneditems[i] != UNDEFINED)
			count++;

	if (!count)
		_cprintf("Je draagt niets.\r\n");
	else
	{
		_cprintf("Je hebt in je bezit:\r\n");
		for (i = 0; i < 10; i++)
			if (progdata.owneditems[i] != UNDEFINED)
				_cprintf("    %s\r\n", progdata.items[progdata.owneditems[i]].name);
	}
}

void DoHelp(void)
{
	_cprintf("--- HELP ---\r\n\r\n");
	_cprintf("Commando's:\r\n");
	_cprintf("   oost\r\n");
	_cprintf("   west\r\n");
	_cprintf("   noord\r\n");
	_cprintf("   zuid\r\n");
	_cprintf("   klim\r\n");
	_cprintf("   daal\r\n");
	_cprintf("   gebruik <voorwerp>\r\n");
	_cprintf("   combineer <voorwerp> en/met <voorwerp>\r\n");
	_cprintf("   pak <voorwerp>\r\n");
	_cprintf("   leg <voorwerp>\r\n");
	_cprintf("   bekijk <voorwerp>\r\n");
	_cprintf("   afwachten\r\n");
	_cprintf("   einde\r\n");
	_cprintf("   status\r\n");
	_cprintf("   help\r\n");
}

void ParseInput(Progdata &progdata, char *inpstr, Parsedata &parsedata)
{
	char *eoword;
	char *curp;
	char clearString[81];
	char workstr[65];
	int i;

	parsedata.parseerror = false;
	memset(clearString, ' ', 79);
	clearString[79] = '\r';
	clearString[80] = 0;

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
			_cprintf("%s< geen commando gegeven", clearString);
		else
			_cprintf("%s< ongeldig commando gegeven", clearString);
		(void)_getch();
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
		_cprintf("%s< ongeldig commando gegeven", clearString);
		parsedata.parseerror = true;
		(void)_getch();
		return;

	case DO_GEBRUIK:
	case DO_LEG:
	case DO_BEKIJK:
		ParseSingleOwnedItemCommandParam(progdata, parsedata, cmds[parsedata.selected], eoword, clearString);	
		break;

	case DO_COMBINEER:
		ParseCombineItemsParameters(progdata, parsedata, eoword, clearString);
		break;

	case DO_PAK:
		if (*eoword != ' ')
		{
			_cprintf("%s< syntax: pak <voorwerp>", clearString);
			parsedata.parseerror = true;
			(void)_getch();
			return;
		}
		parsedata.object1 = FindLayingItemNum(progdata, eoword + 1);
		CheckFoundObject(parsedata, parsedata.object1, eoword + 1, "%s< je ziet hier geen \"%s\" die je kunt meenemen", clearString);;
		break;
	}
}

void ParseCombineItemsParameters(Progdata &progdata, Parsedata& parsedata, const char* currentMatch, const char* clearString)
{
	const char* previousMatch;
	char itemname[25];

	if (*currentMatch != ' ' || (!strstr(currentMatch + 1, " en ") && !strstr(currentMatch + 1, " met ")))
	{
		_cprintf("%s< syntax: combineer <voorwerp> en/met <voorwerp>", clearString);
		parsedata.parseerror = true;
		(void)_getch();
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
	if (!CheckFoundObject(parsedata, parsedata.object1, itemname, dontOwnItemFormatString, clearString))
		return;

	previousMatch = currentMatch + ((strstr(currentMatch, " en ") == currentMatch) ? 4 : 5);

	itemLength = (int)strlen(previousMatch);
	if (itemLength >= 25)
		itemLength = 24;

	strncpy_s(itemname, previousMatch, itemLength);
	itemname[itemLength] = 0;

	parsedata.object2 = FindOwnedItemNum(progdata, itemname);
	if (!CheckFoundObject(parsedata, parsedata.object2, itemname, dontOwnItemFormatString, clearString))
		return;
	
	if (parsedata.object1 == parsedata.object2)
	{
		_cprintf("%s\r< je kunt een voorwerp niet met zichzelf combineren", clearString);
		parsedata.parseerror = true;
		(void)_getch();
	}
}

bool ParseSingleOwnedItemCommandParam(Progdata &progdata, Parsedata& parsedata, const char* command, const char* parseString, const char *clearString)
{
	if (*parseString != ' ')
	{
		_cprintf("%s< syntax: %s <voorwerp>", clearString, command);
		parsedata.parseerror = true;
		(void)_getch();
		return false;
	}
	parsedata.object1 = FindOwnedItemNum(progdata, parseString + 1);

	return CheckFoundObject(parsedata, parsedata.object1, parseString + 1, dontOwnItemFormatString, clearString);
}

bool CheckFoundObject(Parsedata& parsedata, char itemNum, const char* itemname, const char* undefinedItemFormatString, const char* clearString)
{
	switch (parsedata.object1)
	{
	case UNDEFINED:
		_cprintf(undefinedItemFormatString, clearString, itemname);
		parsedata.parseerror = true;
		(void)_getch();
		return false;
	case AMBIGUOUS:
		_cprintf("%s< de afkorting \"%s\" is dubbelzinnig", clearString, itemname);
		parsedata.parseerror = true;
		(void)_getch();
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


