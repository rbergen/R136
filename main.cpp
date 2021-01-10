#include "include.h"

int main()
{
	Progdata progdata;

	Initialize(progdata);

	ShowSplashScreen();

	if (!LoadStatus(progdata))
		ShowStartMessage();

	while (true)
	{
		RoomStatus(progdata);
		if (BeastStatus(progdata))
			if (!DoAction(progdata))
				break;
	}

	SaveStatus(progdata);

	(void)_getch();

//	window(1, 1, 80, 25);
	clrscr();

	return 0;
}

void ShowSplashScreen(void)
{
	clrscr();
	_cprintf("                                *** R136 ***\r\n\r\n"
			  "                                  Ontwerp:\r\n"
			  "                                Peter Wouda\r\n"
			  "                             Rutger van Bergen\r\n\r\n"
			  "                                   Code:\r\n"
			  "                             Rutger van Bergen\r\n\r\n"
			  "                                  Testen:\r\n"
			  "                              Machiel Keizer\r\n"
			  "                                Peter Wouda\r\n"
			  "                             Rutger van Bergen\r\n\r\n"
			  "                        Versie 2.3, (C) 1998 R.I.P.\r\n\r\n");
}

void ShowStartMessage(void)
{
	clrscr();
	_cprintf("Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na\r\n"
			 "over waarom je hier, in deze verlaten, neertroostige omgeving staat.\r\n\r\n"
			 "Het verhaal begint op het moment dat je met 3 andere wetenschappers een\r\n"
			 "project begon over straling. In een vergevorderd stadium van het onderzoek\r\n"
			 "werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er\r\n"
			 "andere, agressievere in de kernsplitser gebracht.\r\n"
			 "Het resultaat was even interessant als bedreigend: er ontstond een nieuwe\r\n"
			 "straling, de positronenstraling. Deze straling heft elektronen op waardoor\r\n"
			 "stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reaktor\r\n"
			 "loste dan ook op in de lucht, en net op tijd kon een wereldramp voorkomen\r\n"
			 "worden door het heldhaftig optreden van een van je collega's.\r\n"
			 "De betreffende wetenschapper werd even blootgesteld aan de straling, en na\r\n"
			 "het gebeuren zonderde hij zich af.\r\n\r\n"
			 "Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en\r\n"
			 "het project te stoppen.\r\n"
			 "De wetenschapper die aan de straling was blootgesteld hield zich niet aan de\r\n"
			 "afspraak en stal wat van de agressieve stof. Hij bouwde een bom, de posi-\r\n"
			 "tronenbom genaamd.\r\n");
	(void)_getch();
	clrscr();
	_cprintf("Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de\r\n"
			 "wereld daarvoor laten boeten. Daarom verborg hij de bom, met een tijdmecha-\r\n"
			 "nisme op een plaats die niemand zou durven betreden; de vallei der verderf.\r\n\r\n"
			 "Een van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\r\n"
			 "Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn\r\n"
			 "huis gevonden.\r\n"
			 "Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de\r\n"
			 "bom lag en licht radioactieve voetstappen.\r\n"
			 "Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er\r\n"
			 "moest worden ingegrepen. Aangezien je niet echt een held bent, werd er beslo-\r\n"
			 "ten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om\r\n"
			 "zijn reis te coordineren via een geheime radiofrequentie.\r\n"
			 "Je hebt nooit meer iets van hem gehoord.\r\n\r\n"
			 "Nu ben jij aan de beurt.\r\n\r\n"
			 "Je staat op de trap die naar de vallei leidt. Rechts van je staat een ver-\r\n"
			 "weerd bordje: \"Betreden op eigen risico\". Je kijkt nog een keer achterom,\r\n"
			 "en met trillende benen loop je naar beneden...\r\n");
	(void)_getch();
	clrscr();
	_cprintf("Type h voor help.\r\n\r\n");
}

void ForceExit(void)
{

	(void)_getch();

	remove(LOADSAVEDATAPATH);

//	window(1, 1, 80, 25);
	clrscr();

	exit(0);
}

