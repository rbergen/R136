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
		PrintToMainWindow("Badend in je eigen bloed bezwijk je aan je verwondingen. Terwijl je liggend op\n");
		PrintToMainWindow("de grond met moeite naar adem snakt, hoor je in de verte een luid gelach.\n");
		PrintToMainWindow("Dan zakken je ogen dicht en stopt je hart met kloppen.\n");
		PrintToMainWindow("Op hetzelfde moment ontploft de bom en sterft de aarde met jou.\n\n");
		ForceExit();
	}

	if (progdata.status.lamppoints > 0 && progdata.status.lamp)
	{
		switch(--progdata.status.lamppoints)
		{
		case 10:
			PrintToMainWindow("De zaklamp gaat zwakker branden.\n\n");
			break;
		case 0:
			PrintToMainWindow("De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij.\n\n");
			progdata.status.lamp = false;
			break;
		}
	}

	do
	{
		char inpstr[65];

		do 
		{
			GetCommandString(inpstr, 64);
			ParseInput(progdata, inpstr, parsedata);
		} 
		while (parsedata.parseerror);

		WriteCentered(main_window, "---***---");
		PrintToMainWindow("\n\n");

		switch(parsedata.selected)
		{
		case kEast:
		case kWest:
		case kNorth:
		case kSouth:
		case kUp:
		case kDown:
			if (progdata.rooms[progdata.status.curroom].connect[parsedata.selected] >= 0)
			{
				if (progdata.living[kGnu].room == progdata.status.curroom && progdata.living[kGnu].status != STATUS_LIVING_DEAD)
				{
					switch (GetRandomNumber(5))
					{
					case 0:
						progdata.living[kGnu].room = ROOM_GNOEGROT;
						break;
					case 1:
						progdata.living[kGnu].room = ROOM_ROTSGROT;
						break;
					case 2:
						progdata.living[kGnu].room = ROOM_LEEGTE;
						break;
					case 3:
						progdata.living[kGnu].room = ROOM_ZANDBANK;
						break;
					case 4:
						progdata.living[kGnu].room = ROOM_OLIEGROT;
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
						progdata.living[kPaper].status = STATUS_PAPIER_OPENING;
				}
				return true;
			}
			else
				PrintToMainWindow("Daar kun je niet heen.\n");
			break;
		case kUse:
			DoGebruik(progdata, parsedata);
			break;
		case kCombine:
			DoCombineer(progdata, parsedata);
			break;
		case kPickup:
			DoPak(progdata, parsedata);
			break;
		case kLayDown:
			DoLeg(progdata, parsedata);
			break;
		case kInspect:
			DoBekijk(progdata, parsedata);
			break;
		case kWait:
			DoAfwachten();
			break;
		case kFinish:
			PrintToMainWindow("Weet je zeker dat je de aarde laat vergaan? ");
			if (tolower(AdvancedGetChar("jJnN")) == 'j')
				return false;
			PrintToMainWindow("\nMooi zo!\n");
			break;
		case kStatus:
			DoStatus(progdata);
			break;
		case kHelp:
			DoHelp();
			break;
		}

		PrintToMainWindow("\n");
	}
	while (parsedata.selected == kStatus || parsedata.selected == kHelp || parsedata.selected == kFinish);

	return true;
}

void DoGebruik(Progdata &progdata, Parsedata &parsedata)
{
	switch (progdata.owneditems[parsedata.object1])
	{
	case ITEM_ZWAARD:

		int monster;

		if (progdata.living[kHellHound].room == progdata.status.curroom && progdata.living[kHellHound].strike)
			monster = kHellHound;
		else if (progdata.living[kPlant].room == progdata.status.curroom && progdata.living[kPlant].strike)
			monster = kPlant;
		else
		{
			PrintToMainWindow("Dat heeft geen zin.\n\n");
			return;
		}

		while (true)
		{
			PrintToMainWindow("Je haalt uit met je zwaard");

			if (GetRandomNumber(100) > 70)
				PrintToMainWindow(", maar het monster ontwijkt.\n");
			else
			{
				PrintToMainWindow(" en je raakt het monster hard.\n");
				progdata.living[monster].strike--;
			}

			if (progdata.living[monster].strike == 1)
				PrintToMainWindow("\nHet monster is zwaar gewond en je baadt in zijn bloed.\n");

			if (!progdata.living[monster].strike || GetRandomNumber(100) > 30)
				break;

			PrintToMainWindow("\nJe kunt nog een slag uitdelen. Wil je dat? ");

			if (tolower(AdvancedGetChar("jJnN")) != 'j')
			{
				PrintToMainWindow("\n");
				break;
			}

			PrintToMainWindow("\n");
		}
		PrintToMainWindow("\n");

		if (!progdata.living[monster].strike)
		{
			progdata.living[monster].status = STATUS_LIVING_DEAD;
			LivingStatus(progdata);
		}

		WaitForKey();
		break;

	case ITEM_ZAKLAMP:

		if (progdata.status.lamp)
		{
			progdata.status.lamp = !progdata.status.lamp;
			PrintToMainWindow("Je zet de zaklamp uit.%s", IsRoomLit(progdata.status) ? "\n" : " Je ziet niets meer.\n");
			break;
		}

		if (progdata.status.lamppoints)
		{
			progdata.status.lamp = !progdata.status.lamp;
			PrintToMainWindow("Je zet de zaklamp aan. De straal verlicht de omtrek.\n");
		}
		else
			PrintToMainWindow("Zonder nieuwe batterijen doet'ie het niet...\n");

		break;

	case ITEM_VERBAND:

		if (progdata.status.lifepoints == MAX_LIFEPOINTS)
		{
			PrintToMainWindow("Je bent nog helemaal heel!\n");
			break;
		}

		PrintToMainWindow("Je pakt het verband en de pleisters en plaatst ze over je wonden. Je bijt even\n"
				 "op je lippen van de pijn als het verband je nog bloedende wonden raakt.\n\n"
				 "Je bent weer zo goed als nieuw.\n");

		progdata.status.lifepoints = MAX_LIFEPOINTS;
		progdata.items[ITEM_VERBAND].room = kUndefined;
		progdata.owneditems[parsedata.object1] = kUndefined;

		WaitForKey();
		break;

	case ITEM_TNT:

		PrintToMainWindow("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samen-\n"
				 "gaat met een harde knal. Je wordt even verblind door de flits van de ontplof-\n"
				 "fing. Door de klap val je even flauw.\n");

		progdata.status.lifepoints--;

		WaitForKey();
		break;

	case ITEM_HITTEPAK:

		PrintToMainWindow("Je hebt het pak al aan.\n");

		break;

	case ITEM_GASMASKER:

		PrintToMainWindow("Je hebt het gasmasker al op.\n");

		break;

	default:

		if (progdata.items[progdata.owneditems[parsedata.object1]].useableon < 0
			 || progdata.living[progdata.items[progdata.owneditems[parsedata.object1]].useableon].room != progdata.status.curroom)
		{
			PrintToMainWindow("Dat heeft geen zin.\n\n");
			break;
		}

		switch (progdata.owneditems[parsedata.object1])
		{

		case ITEM_BOT:

			progdata.living[kDoor].status = STATUS_DEUR_OPEN;

			break;

		case ITEM_DISKETTE:

			UseItemToStatus(progdata, parsedata.object1, kComputer, STATUS_COMPUTER_READING);

			break;

		case ITEM_HASJ:

			UseItemToStatus(progdata, parsedata.object1, kBarbecue, progdata.living[kBarbecue].status == STATUS_BARBECUE_INITIALBURN
				? STATUS_BARBECUE_HASJONFIRE : STATUS_BARBECUE_KOEKJEBAKING);

			break;

		case ITEM_HONDVLEES:

			UseItemToStatus(progdata, parsedata.object1, kBarbecue, progdata.living[kBarbecue].status == STATUS_BARBECUE_INITIALBURN
				? STATUS_BARBECUE_VLEESONFIRE : STATUS_BARBECUE_KOEKJEBAKING);

			break;

		case ITEM_ROODKRISTAL:
		case ITEM_GROENKRISTAL:
		case ITEM_BLAUWKRISTAL:

			UseItemToStatus(progdata, parsedata.object1, kDragonHead, progdata.living[kDragonHead].status + 1);

			break;

		case ITEM_KOEKJE:

			UseItemToStatus(progdata, parsedata.object1, kDragon, STATUS_DRAAK_KOEKJETHROWN);

			break;

		case ITEM_SLAAPMUTS:

			if (progdata.living[kDragon].status != STATUS_DRAAK_LIGHTSLEEPING)
			{
				PrintToMainWindow("Dat heeft geen zin.\n\n");
				return;
			}

			UseItemToStatus(progdata, parsedata.object1, kDragon, STATUS_DRAAK_SLAAPMUTSONHEAD);

			break;

		case ITEM_BOM:

			UseItemToStatus(progdata, parsedata.object1, kLava, STATUS_LAVA_BOMDROPPED);

			break;

		case ITEM_VLAMMENWERPER:

			UseItemToStatus(progdata, parsedata.object1, kTree, STATUS_BOOM_SETONFIRE);

			break;

		case ITEM_GIFTIGVLEES:

			UseItemToStatus(progdata, parsedata.object1, kGnu, STATUS_GNOE_GIFTIGVLEESFED);

			break;

		case ITEM_BOEKJE:

			UseItemToStatus(progdata, parsedata.object1, kRedTroll, STATUS_RODETROL_BOEKJETHROWN);

			break;

		case ITEM_GASGRANAAT:

			UseItemToStatus(progdata, parsedata.object1, kSwelling, STATUS_GEZWEL_GASSED);

			break;
		}

		LivingStatus(progdata);

		WaitForKey();
		break;
	}
}

void UseItemToStatus(Progdata &progdata, int ownedindex, int beast, int status)
{
	progdata.items[progdata.owneditems[ownedindex]].room = kUndefined;
	progdata.owneditems[ownedindex] = kUndefined;
	progdata.living[beast].status = status;
}

void DoCombineer(Progdata &progdata, Parsedata &parsedata)
{
	if (progdata.items[progdata.owneditems[parsedata.object1]].useableon > -2
		 || connectToItem(progdata.items[progdata.owneditems[parsedata.object1]].useableon) != progdata.owneditems[parsedata.object2])
	{
		PrintToMainWindow("Dat levert niets bruikbaars op.\n");
		return;
	}

	switch(progdata.owneditems[parsedata.object1])
	{
	case ITEM_ZAKLAMP:
	case ITEM_BATTERIJEN:

		PrintToMainWindow("Je schroeft de zaklamp open en schudt totdat de oude batterijen er uit komen\n"
				 "vallen. Daarna steek je de \"trommelbatterijen\" erin en schroeft de lamp weer\n"
				 "dicht. Nadat je een paar keer op de zaklantaarn hebt geslagen zie je dat hij\n"
				 "het doet.\n");

		progdata.status.lamppoints = kUndefined;
		progdata.items[ITEM_BATTERIJEN].room = kUndefined;

		if (progdata.owneditems[parsedata.object1] == ITEM_BATTERIJEN)
			progdata.owneditems[parsedata.object1] = kUndefined;
		else
			progdata.owneditems[parsedata.object2] = kUndefined;

		break;

	case ITEM_GASPATROON:
	case ITEM_ONTSTEKING:

		PrintToMainWindow("Je plaatst de ontsteker op het mosterdgaspatroon. Na enig friemelen is het\n"
				 "resultaat een werkende mosterdgasgranaat.\n");

		progdata.items[ITEM_GASPATROON].room = kUndefined;
		progdata.items[ITEM_ONTSTEKING].room = kUndefined;
		progdata.items[ITEM_GASGRANAAT].room = STATUS_ITEM_OWNED;

		progdata.owneditems[parsedata.object1] = ITEM_GASGRANAAT;
		progdata.owneditems[parsedata.object2] = kUndefined;

		break;
	}
}

void DoLeg(Progdata &progdata, Parsedata &parsedata)
{
	if (progdata.owneditems[parsedata.object1] == ITEM_ZAKLAMP)
	{
		PrintToMainWindow("Je bent inmiddels zo aan je zaklamp gehecht geraakt dat je hem niet meer kunt\n"
				 "missen.\n");

		return;
	}

	if (progdata.owneditems[parsedata.object1] == ITEM_BATTERIJEN)
	{
		PrintToMainWindow("Je bent inmiddels zo aan je batterijen gehecht geraakt dat je ze niet meer kunt\n"
				 "missen.\n");

		return;
	}

	PrintToMainWindow("Je legt %s neer.\n", progdata.items[progdata.owneditems[parsedata.object1]].name);

	progdata.items[progdata.owneditems[parsedata.object1]].room = progdata.status.curroom;
	progdata.owneditems[parsedata.object1] = kUndefined;
}

void DoPak(Progdata &progdata, Parsedata &parsedata)
{
	int i;

	for (i = 0; i < 10; i++)
		if (progdata.owneditems[i] == kUndefined)
			break;

	if (i == 10)
	{
		PrintToMainWindow("Je zakken zitten tjokvol, en je krijgt %s er niet in.\n", progdata.items[parsedata.object1].name);
		return;
	}

	PrintToMainWindow("Je pakt %s op en steekt deze in een van je zakken.\n", progdata.items[parsedata.object1].name);

	progdata.items[parsedata.object1].room = STATUS_ITEM_OWNED;
	progdata.owneditems[i] = parsedata.object1;
}

void DoBekijk(Progdata &progdata, Parsedata &parsedata)
{
	if (!IsRoomLit(progdata.status))
	{
		PrintToMainWindow("Het is veel te donker om wat dan ook te bekijken.\n");
		return;
	}

	WriteToMainWindow(progdata.items[progdata.owneditems[parsedata.object1]].descript);
	PrintToMainWindow("\n");
}

void DoAfwachten(void)
{
	switch(GetRandomNumber(5))
	{
	case 0:

		PrintToMainWindow("Je pulkt wat in je neus.\n");
		break;

	case 1:

		PrintToMainWindow("Je krabt wat achter je oren.\n");
		break;

	case 2:

		PrintToMainWindow("Je gaapt even uitgebreid.\n");
		break;

	case 3:

		PrintToMainWindow("Je trekt je broek even op.\n");
		break;

	case 4:

		PrintToMainWindow("Je pulkt wat smeer uit je oren.\n");
		break;

	}
}

void DoStatus(Progdata &progdata)
{
	int i;
	int count = 0;

	PrintToMainWindow("--- STATUSRAPPORT ---\n\n");
	PrintToMainWindow("Je hebt nog %d levenspunten.\n", progdata.status.lifepoints);

	if (progdata.items[ITEM_ZAKLAMP].room == STATUS_ITEM_OWNED)
		PrintToMainWindow("Je zaklamp staat %s.\n", progdata.status.lamp ? "aan" : "uit");

	for (i = 0; i < 10; i++)
		if (progdata.owneditems[i] != kUndefined)
			count++;

	if (!count)
		PrintToMainWindow("Je draagt niets.\n");
	else
	{
		PrintToMainWindow("Je hebt in je bezit:\n");
		for (i = 0; i < 10; i++)
			if (progdata.owneditems[i] != kUndefined)
				PrintToMainWindow("    %s\n", progdata.items[progdata.owneditems[i]].name);
	}
}

void DoHelp(void)
{
	PrintToMainWindow("--- HELP ---\n\n");
	PrintToMainWindow("Commando's:\n");
	PrintToMainWindow("   oost\n");
	PrintToMainWindow("   west\n");
	PrintToMainWindow("   noord\n");
	PrintToMainWindow("   zuid\n");
	PrintToMainWindow("   klim\n");
	PrintToMainWindow("   daal\n");
	PrintToMainWindow("   gebruik <voorwerp>\n");
	PrintToMainWindow("   combineer <voorwerp> en/met <voorwerp>\n");
	PrintToMainWindow("   pak <voorwerp>\n");
	PrintToMainWindow("   leg <voorwerp>\n");
	PrintToMainWindow("   bekijk <voorwerp>\n");
	PrintToMainWindow("   afwachten\n");
	PrintToMainWindow("   einde\n");
	PrintToMainWindow("   status\n");
	PrintToMainWindow("   help\n");
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
			PrintCommandString("< geen commando gegeven");
		else
			PrintCommandString("< ongeldig commando gegeven");

		return;
	}

	parsedata.selected = kUndefined;

	for (i = 0; parsedata.selected == kUndefined && i < COMMAND_COUNT; i++)
	{
		// this search assumes that the commands each start with a different letter
		// it finds the first command that starts with whatever is the command (abbreviation) entered by the user 
		if (!strncmp(cmds[i], curp, int(eoword - curp)))
			parsedata.selected = i;
	}

	switch (parsedata.selected)
	{
	case kUndefined:

		PrintCommandString("< ongeldig commando gegeven");
		parsedata.parseerror = true;
		return;

	case kUse:
	case kLayDown:
	case kInspect:

		ParseSingleOwnedItemCommandParam(progdata, parsedata, cmds[parsedata.selected], eoword);	
		break;

	case kCombine:

		ParseCombineItemsParameters(progdata, parsedata, eoword);
		break;

	case kPickup:

		if (*eoword != ' ')
		{
			PrintCommandString("< syntax: pak <voorwerp>");
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
		PrintCommandString("< syntax: combineer <voorwerp> en/met <voorwerp>");
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
		PrintCommandString("< je kunt een voorwerp niet met zichzelf combineren");
		parsedata.parseerror = true;
	}
}

bool ParseSingleOwnedItemCommandParam(Progdata &progdata, Parsedata& parsedata, const char* command, const char* parseString)
{
	if (*parseString != ' ')
	{
		PrintCommandString("< syntax: %s <voorwerp>", command);
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
	case kUndefined:

		PrintCommandString(undefinedItemFormatString, itemname);
		parsedata.parseerror = true;

		return false;

	case AMBIGUOUS:

		PrintCommandString("< de afkorting \"%s\" is dubbelzinnig", itemname);
		parsedata.parseerror = true;

		return false;
	}

	return true;
}

int FindOwnedItemNum(Progdata &progdata, const char *itemname)
{
	int item = kUndefined;
	int i;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (i = 0; i < 10 && item != AMBIGUOUS; i++)
		if (progdata.owneditems[i] != kUndefined && strstr(progdata.items[progdata.owneditems[i]].name, itemname))
			item = ((item == kUndefined) ? i : AMBIGUOUS);

	return item;
}

bool IsRoomLit(Status& status) 
{
	return status.curroom < ROOM_SLIJMGROT || status.lamp
		|| status.curroom == ROOM_RADIOACTIEVEGROT || status.curroom == ROOM_TLGROT;
}

int FindLayingItemNum(Progdata &progdata, const char *itemname)
{
	int item = kUndefined;
	int i;

	if (!IsRoomLit(progdata.status))
		return kUndefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (i = 0; i < ITEM_COUNT && item != AMBIGUOUS; i++)
		if (progdata.status.curroom == progdata.items[i].room && strstr(progdata.items[i].name, itemname))
			item = ((item == kUndefined) ? i : AMBIGUOUS);

	return item;
}


