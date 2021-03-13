#include "r136.h"

int main()
{
	Progdata progdata;

	InitializeConsole();

	RunIntro();

	SetupWindows();

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

	WaitForKey();

	ClearWindow();

	ReleaseConsole();

	return 0;
}

void ShowSplashScreen(void)
{
	ClearWindow();

	wattron(main_window, A_BOLD);
	WriteCentered(main_window, "*** R136 ***");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_UNDERLINE);
	WriteCentered(main_window, "Ontwerp"); waddch(main_window, '\n');
	wattroff(main_window, A_BOLD | A_UNDERLINE);
	
	WriteCentered(main_window, "Peter Wouda"); waddch(main_window, '\n');
	WriteCentered(main_window, "Rutger van Bergen");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_BOLD | A_UNDERLINE);
	WriteCentered(main_window, "Code"); waddch(main_window, '\n');
	wattroff(main_window, A_BOLD | A_UNDERLINE);
	
	WriteCentered(main_window, "Rutger van Bergen");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_BOLD | A_UNDERLINE);
	WriteCentered(main_window, "Testen"); waddch(main_window, '\n');
	wattroff(main_window, A_BOLD | A_UNDERLINE);
	
	WriteCentered(main_window, "Machiel Keizer"); waddch(main_window, '\n');
	WriteCentered(main_window, "Peter Wouda"); waddch(main_window, '\n');
	WriteCentered(main_window, "Rutger van Bergen");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_BOLD);
	WriteCentered(main_window, "Versie 3.2, (C) 1998, 2021 R.I.P.");
	wattroff(main_window, A_BOLD);
	
	waddstr(main_window, "\n\n");
}

void ShowStartMessage(void)
{
	ClearWindow();
	
	WriteToMainWindow(L"Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na\n");
	WriteToMainWindow(L"over waarom je hier, in deze verlaten, neertroostige omgeving staat.\n\n");
	WriteToMainWindow(L"Het verhaal begint op het moment dat je met drie andere wetenschappers een\n");
	WriteToMainWindow(L"project begon over straling. In een vergevorderd stadium van het onderzoek\n");
	WriteToMainWindow(L"werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er\n");
	WriteToMainWindow(L"andere, agressievere in de kernsplitser gebracht.\n");
	WriteToMainWindow(L"Het resultaat was even interessant als bedreigend: er ontstond een nieuwe\n");
	WriteToMainWindow(L"straling, de positronenstraling. Deze straling heft elektronen op waardoor\n");
	WriteToMainWindow(L"stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reactor\n");
	WriteToMainWindow(L"loste dan ook op in de lucht, en net op tijd kon een wereldramp voorkomen\n");
	WriteToMainWindow(L"worden door het heldhaftig optreden van één van je collega's.\n");
	WriteToMainWindow(L"De betreffende wetenschapper werd even blootgesteld aan de straling, en na\n");
	WriteToMainWindow(L"het gebeuren zonderde hij zich af.\n\n");
	WriteToMainWindow(L"Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en\n");
	WriteToMainWindow(L"het project te stoppen.\n");
	WriteToMainWindow(L"De wetenschapper die aan de straling was blootgesteld hield zich niet aan de\n");
	WriteToMainWindow(L"afspraak en stal wat van de agressieve stof. Hij bouwde een bom, de posi-\n");
	WriteToMainWindow(L"tronenbom genaamd.\n");
	
	WaitForKey();
	ClearWindow();
	
	WriteToMainWindow(L"Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de\n");
	WriteToMainWindow(L"wereld daarvoor laten boeten. Daarom verborg hij de bom, met een tijdmecha-\n");
	WriteToMainWindow(L"nisme op een plaats die niemand zou durven betreden; de vallei der verderf.\n\n");
	WriteToMainWindow(L"Eén van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\n");
	WriteToMainWindow(L"Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn\n");
	WriteToMainWindow(L"huis gevonden.\n");
	WriteToMainWindow(L"Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de\n");
	WriteToMainWindow(L"bom lag en licht radioactieve voetstappen.\n");
	WriteToMainWindow(L"Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er\n");
	WriteToMainWindow(L"moest worden ingegrepen. Aangezien je niet echt een held bent, werd er beslo-\n");
	WriteToMainWindow(L"ten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om\n");
	WriteToMainWindow(L"zijn reis te coördineren via een geheime radiofrequentie.\n");
	WriteToMainWindow(L"Je hebt nooit meer iets van hem gehoord.\n\n");
	WriteToMainWindow(L"Nu ben jij aan de beurt.\n\n");
	WriteToMainWindow(L"Je staat op de trap die naar de vallei leidt. Rechts van je staat een ver-\n");
	WriteToMainWindow(L"weerd bordje: \"Betreden op eigen risico\". Je kijkt nog één keer achterom,\n");
	WriteToMainWindow(L"en met trillende benen loop je naar beneden...\n");
	
	WaitForKey();
	ClearWindow();
	
	WriteToMainWindow(L"Type h voor help.\n\n");
}

void ForceExit(void)
{
	WaitForKey();

	remove(LOADSAVEDATAPATH);

	ClearWindow();

	ReleaseConsole();

	exit(0);
}

