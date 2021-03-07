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
	
	writemw(L"Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na\n");
	writemw(L"over waarom je hier, in deze verlaten, neertroostige omgeving staat.\n\n");
	writemw(L"Het verhaal begint op het moment dat je met drie andere wetenschappers een\n");
	writemw(L"project begon over straling. In een vergevorderd stadium van het onderzoek\n");
	writemw(L"werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er\n");
	writemw(L"andere, agressievere in de kernsplitser gebracht.\n");
	writemw(L"Het resultaat was even interessant als bedreigend: er ontstond een nieuwe\n");
	writemw(L"straling, de positronenstraling. Deze straling heft elektronen op waardoor\n");
	writemw(L"stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reactor\n");
	writemw(L"loste dan ook op in de lucht, en net op tijd kon een wereldramp voorkomen\n");
	writemw(L"worden door het heldhaftig optreden van één van je collega's.\n");
	writemw(L"De betreffende wetenschapper werd even blootgesteld aan de straling, en na\n");
	writemw(L"het gebeuren zonderde hij zich af.\n\n");
	writemw(L"Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en\n");
	writemw(L"het project te stoppen.\n");
	writemw(L"De wetenschapper die aan de straling was blootgesteld hield zich niet aan de\n");
	writemw(L"afspraak en stal wat van de agressieve stof. Hij bouwde een bom, de posi-\n");
	writemw(L"tronenbom genaamd.\n");
	
	waitforkey();
	clrscr();
	
	writemw(L"Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de\n");
	writemw(L"wereld daarvoor laten boeten. Daarom verborg hij de bom, met een tijdmecha-\n");
	writemw(L"nisme op een plaats die niemand zou durven betreden; de vallei der verderf.\n\n");
	writemw(L"Eén van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\n");
	writemw(L"Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn\n");
	writemw(L"huis gevonden.\n");
	writemw(L"Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de\n");
	writemw(L"bom lag en licht radioactieve voetstappen.\n");
	writemw(L"Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er\n");
	writemw(L"moest worden ingegrepen. Aangezien je niet echt een held bent, werd er beslo-\n");
	writemw(L"ten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om\n");
	writemw(L"zijn reis te coördineren via een geheime radiofrequentie.\n");
	writemw(L"Je hebt nooit meer iets van hem gehoord.\n\n");
	writemw(L"Nu ben jij aan de beurt.\n\n");
	writemw(L"Je staat op de trap die naar de vallei leidt. Rechts van je staat een ver-\n");
	writemw(L"weerd bordje: \"Betreden op eigen risico\". Je kijkt nog één keer achterom,\n");
	writemw(L"en met trillende benen loop je naar beneden...\n");
	
	waitforkey();
	clrscr();
	
	writemw(L"Type h voor help.\n\n");
}

void ForceExit(void)
{
	waitforkey();

	remove(LOADSAVEDATAPATH);

	clrscr();

	releaseconsole();

	exit(0);
}

