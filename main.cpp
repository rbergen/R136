#include "r136.h"

int main()
{
	Progdata progdata;

	initconsole();

	RunIntro();

	setupwindows();

	Initialize(progdata);

	ShowSplashScreen();

	if (!LoadStatus(progdata))
		ShowStartMessage();

	while (true)
	{
		RoomStatus(progdata);
		if (LivingStatus(progdata))
			if (!DoAction(progdata))
				break;
	}

	SaveStatus(progdata);

	waitforkey();

	clrscr();

	releaseconsole();

	return 0;
}

void ShowSplashScreen(void)
{
	clrscr();
	wattron(MAINWINDOW, A_BOLD);
	printcentered(MAINWINDOW, "*** R136 ***");
	waddstr(MAINWINDOW, "\n\n");
	wattron(MAINWINDOW, A_UNDERLINE);
	printcentered(MAINWINDOW, "Ontwerp"); waddch(MAINWINDOW, '\n');
	wattroff(MAINWINDOW, A_BOLD | A_UNDERLINE);
	printcentered(MAINWINDOW, "Peter Wouda"); waddch(MAINWINDOW, '\n');
	printcentered(MAINWINDOW, "Rutger van Bergen");
	waddstr(MAINWINDOW, "\n\n");
	wattron(MAINWINDOW, A_BOLD | A_UNDERLINE);
	printcentered(MAINWINDOW, "Code"); waddch(MAINWINDOW, '\n');
	wattroff(MAINWINDOW, A_BOLD | A_UNDERLINE);
	printcentered(MAINWINDOW, "Rutger van Bergen");
	waddstr(MAINWINDOW, "\n\n");
	wattron(MAINWINDOW, A_BOLD | A_UNDERLINE);
	printcentered(MAINWINDOW, "Testen"); waddch(MAINWINDOW, '\n');
	wattroff(MAINWINDOW, A_BOLD | A_UNDERLINE);
	printcentered(MAINWINDOW, "Machiel Keizer"); waddch(MAINWINDOW, '\n');
	printcentered(MAINWINDOW, "Peter Wouda"); waddch(MAINWINDOW, '\n');
	printcentered(MAINWINDOW, "Rutger van Bergen");
	waddstr(MAINWINDOW, "\n\n");
	wattron(MAINWINDOW, A_BOLD);
	printcentered(MAINWINDOW, "Versie 3.2, (C) 1998, 2021 R.I.P.");
	wattroff(MAINWINDOW, A_BOLD);
	waddstr(MAINWINDOW, "\n\n");
}

void ShowStartMessage(void)
{
	clrscr();
	printmw("Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na\n");
	printmw("over waarom je hier, in deze verlaten, neertroostige omgeving staat.\n\n");
	printmw("Het verhaal begint op het moment dat je met 3 andere wetenschappers een\n");
	printmw("project begon over straling. In een vergevorderd stadium van het onderzoek\n");
	printmw("werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er\n");
	printmw("andere, agressievere in de kernsplitser gebracht.\n");
	printmw("Het resultaat was even interessant als bedreigend: er ontstond een nieuwe\n");
	printmw("straling, de positronenstraling. Deze straling heft elektronen op waardoor\n");
	printmw("stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reaktor\n");
	printmw("loste dan ook op in de lucht, en net op tijd kon een wereldramp voorkomen\n");
	printmw("worden door het heldhaftig optreden van een van je collega's.\n");
	printmw("De betreffende wetenschapper werd even blootgesteld aan de straling, en na\n");
	printmw("het gebeuren zonderde hij zich af.\n\n");
	printmw("Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en\n");
	printmw("het project te stoppen.\n");
	printmw("De wetenschapper die aan de straling was blootgesteld hield zich niet aan de\n");
	printmw("afspraak en stal wat van de agressieve stof. Hij bouwde een bom, de posi-\n");
	printmw("tronenbom genaamd.\n");
	waitforkey();
	clrscr();
	printmw("Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de\n");
	printmw("wereld daarvoor laten boeten. Daarom verborg hij de bom, met een tijdmecha-\n");
	printmw("nisme op een plaats die niemand zou durven betreden; de vallei der verderf.\n\n");
	printmw("Een van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\n");
	printmw("Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn\n");
	printmw("huis gevonden.\n");
	printmw("Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de\n");
	printmw("bom lag en licht radioactieve voetstappen.\n");
	printmw("Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er\n");
	printmw("moest worden ingegrepen. Aangezien je niet echt een held bent, werd er beslo-\n");
	printmw("ten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om\n");
	printmw("zijn reis te coordineren via een geheime radiofrequentie.\n");
	printmw("Je hebt nooit meer iets van hem gehoord.\n\n");
	printmw("Nu ben jij aan de beurt.\n\n");
	printmw("Je staat op de trap die naar de vallei leidt. Rechts van je staat een ver-\n");
	printmw("weerd bordje: \"Betreden op eigen risico\". Je kijkt nog een keer achterom,\n");
	printmw("en met trillende benen loop je naar beneden...\n");
	waitforkey();
	clrscr();
	printmw("Type h voor help.\n\n");
}

void ForceExit(void)
{
	waitforkey();

	remove(LOADSAVEDATAPATH);

	clrscr();

	releaseconsole();

	exit(0);
}

