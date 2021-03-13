#include "r136.h"

int main()
{
	Progdata progdata;

	initialize_console();

	RunIntro();

	setup_windows();

	Initialize(progdata);

	show_splashscreen();

	if (!LoadStatus(progdata))
		show_start_message();

	while (true)
	{
		show_room_status(progdata);
		if (progress_animate_status(progdata))
			if (!DoAction(progdata))
				break;
	}

	SaveStatus(progdata);

	wait_for_key();

	clear_window();

	release_console();

	return 0;
}

void show_splashscreen(void)
{
	clear_window();

	wattron(main_window, A_BOLD);
	write_centered(main_window, "*** R136 ***");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_UNDERLINE);
	write_centered(main_window, "Ontwerp"); waddch(main_window, '\n');
	wattroff(main_window, A_BOLD | A_UNDERLINE);
	
	write_centered(main_window, "Peter Wouda"); waddch(main_window, '\n');
	write_centered(main_window, "Rutger van Bergen");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_BOLD | A_UNDERLINE);
	write_centered(main_window, "Code"); waddch(main_window, '\n');
	wattroff(main_window, A_BOLD | A_UNDERLINE);
	
	write_centered(main_window, "Rutger van Bergen");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_BOLD | A_UNDERLINE);
	write_centered(main_window, "Testen"); waddch(main_window, '\n');
	wattroff(main_window, A_BOLD | A_UNDERLINE);
	
	write_centered(main_window, "Machiel Keizer"); waddch(main_window, '\n');
	write_centered(main_window, "Peter Wouda"); waddch(main_window, '\n');
	write_centered(main_window, "Rutger van Bergen");
	
	waddstr(main_window, "\n\n");
	
	wattron(main_window, A_BOLD);
	write_centered(main_window, "Versie 3.2, (C) 1998, 2021 R.I.P.");
	wattroff(main_window, A_BOLD);
	
	waddstr(main_window, "\n\n");
}

void show_start_message(void)
{
	clear_window();
	
	write_to_main_window(L"Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na\n");
	write_to_main_window(L"over waarom je hier, in deze verlaten, neertroostige omgeving staat.\n\n");
	write_to_main_window(L"Het verhaal begint op het moment dat je met drie andere wetenschappers een\n");
	write_to_main_window(L"project begon over straling. In een vergevorderd stadium van het onderzoek\n");
	write_to_main_window(L"werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er\n");
	write_to_main_window(L"andere, agressievere in de kernsplitser gebracht.\n");
	write_to_main_window(L"Het resultaat was even interessant als bedreigend: er ontstond een nieuwe\n");
	write_to_main_window(L"straling, de positronenstraling. Deze straling heft elektronen op waardoor\n");
	write_to_main_window(L"stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reactor\n");
	write_to_main_window(L"loste dan ook op in de lucht, en net op tijd kon een wereldramp voorkomen\n");
	write_to_main_window(L"worden door het heldhaftig optreden van één van je collega's.\n");
	write_to_main_window(L"De betreffende wetenschapper werd even blootgesteld aan de straling, en na\n");
	write_to_main_window(L"het gebeuren zonderde hij zich af.\n\n");
	write_to_main_window(L"Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en\n");
	write_to_main_window(L"het project te stoppen.\n");
	write_to_main_window(L"De wetenschapper die aan de straling was blootgesteld hield zich niet aan de\n");
	write_to_main_window(L"afspraak en stal wat van de agressieve stof. Hij bouwde een bom, de posi-\n");
	write_to_main_window(L"tronenbom genaamd.\n");
	
	wait_for_key();
	clear_window();
	
	write_to_main_window(L"Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de\n");
	write_to_main_window(L"wereld daarvoor laten boeten. Daarom verborg hij de bom, met een tijdmecha-\n");
	write_to_main_window(L"nisme op een plaats die niemand zou durven betreden; de vallei der verderf.\n\n");
	write_to_main_window(L"Eén van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\n");
	write_to_main_window(L"Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn\n");
	write_to_main_window(L"huis gevonden.\n");
	write_to_main_window(L"Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de\n");
	write_to_main_window(L"bom lag en licht radioactieve voetstappen.\n");
	write_to_main_window(L"Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er\n");
	write_to_main_window(L"moest worden ingegrepen. Aangezien je niet echt een held bent, werd er beslo-\n");
	write_to_main_window(L"ten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om\n");
	write_to_main_window(L"zijn reis te coördineren via een geheime radiofrequentie.\n");
	write_to_main_window(L"Je hebt nooit meer iets van hem gehoord.\n\n");
	write_to_main_window(L"Nu ben jij aan de beurt.\n\n");
	write_to_main_window(L"Je staat op de trap die naar de vallei leidt. Rechts van je staat een ver-\n");
	write_to_main_window(L"weerd bordje: \"Betreden op eigen risico\". Je kijkt nog één keer achterom,\n");
	write_to_main_window(L"en met trillende benen loop je naar beneden...\n");
	
	wait_for_key();
	clear_window();
	
	write_to_main_window(L"Type h voor help.\n\n");
}

void force_exit(void)
{
	wait_for_key();

	remove(LOADSAVEDATAPATH);

	clear_window();

	release_console();

	exit(0);
}

