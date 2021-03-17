#include "r136.h"
#include "main.h"

int main()
{
	CoreData core;

	console.initialize();

	run_intro();

	initialize(core);

	show_splashscreen();

	if (!load_game(core))
		show_start_message();

	while (true)
	{
		show_room_status(core);
		if (progress_animate_status(core))
			if (!perform_command(core))
				break;
	}

	save_game(core);

	console.main().wait_for_key(true);
	console.main().clear();

	console.release();

	return 0;
}

void show_splashscreen(void)
{
	console.main().clear();

	console.main().set_attribute(A_BOLD);
	console.main().print_centered("*** R136 ***");
	console.main().print("\n\n");
	
	console.main().set_attribute(A_UNDERLINE);
	console.main().print_centered("Ontwerp\n"); 
	console.main().unset_attribute(A_BOLD | A_UNDERLINE);
	
	console.main().print_centered("Peter Wouda\n"); 
	console.main().print_centered("Rutger van Bergen");
	console.main().print("\n\n");
	
	console.main().set_attribute(A_BOLD | A_UNDERLINE);
	console.main().print_centered("Code\n"); 
	console.main().unset_attribute(A_BOLD | A_UNDERLINE);
	
	console.main().print_centered("Rutger van Bergen");
	console.main().print("\n\n");
	
	console.main().set_attribute(A_BOLD | A_UNDERLINE);
	console.main().print_centered("Testen\n"); 
	console.main().unset_attribute(A_BOLD | A_UNDERLINE);
	
	console.main().print_centered("Machiel Keizer\n"); 
	console.main().print_centered("Peter Wouda\n"); 
	console.main().print_centered("Rutger van Bergen\n");
	console.main().print("\n\n");
	
	console.main().set_attribute(A_BOLD);
	console.main().print_centered("Versie 3.3.1, (C) 1998, 2021 R.I.P.");
	console.main().unset_attribute(A_BOLD);
	console.main().print("\n\n");
}

void show_start_message(void)
{
	console.main().clear();
	
	console.main().print(L"Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na\n");
	console.main().print(L"over waarom je hier, in deze verlaten, neertroostige omgeving staat.\n\n");
	console.main().print(L"Het verhaal begint op het moment dat je met drie andere wetenschappers een\n");
	console.main().print(L"project begon over straling. In een vergevorderd stadium van het onderzoek\n");
	console.main().print(L"werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er\n");
	console.main().print(L"andere, agressievere in de kernsplitser gebracht.\n");
	console.main().print(L"Het resultaat was even interessant als bedreigend: er ontstond een nieuwe\n");
	console.main().print(L"straling, de positronenstraling. Deze straling heft elektronen op waardoor\n");
	console.main().print(L"stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reactor\n");
	console.main().print(L"loste dan ook op in de lucht, en net op tijd kon een wereldramp voorkomen\n");
	console.main().print(L"worden door het heldhaftig optreden van één van je collega's.\n");
	console.main().print(L"De betreffende wetenschapper werd even blootgesteld aan de straling, en na\n");
	console.main().print(L"het gebeuren zonderde hij zich af.\n\n");
	console.main().print(L"Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en\n");
	console.main().print(L"het project te stoppen.\n");
	console.main().print(L"De wetenschapper die aan de straling was blootgesteld hield zich niet aan de\n");
	console.main().print(L"afspraak en stal wat van de agressieve stof. Hij bouwde een bom, de posi-\n");
	console.main().print(L"tronenbom genaamd.\n\n");
	
	console.main().wait_for_key(true);
	console.main().clear();
	
	console.main().print(L"Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de\n");
	console.main().print(L"wereld daarvoor laten boeten. Daarom verborg hij de bom, met een tijdmecha-\n");
	console.main().print(L"nisme op een plaats die niemand zou durven betreden; de vallei der verderf.\n\n");
	console.main().print(L"Eén van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\n");
	console.main().print(L"Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn\n");
	console.main().print(L"huis gevonden.\n");
	console.main().print(L"Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de\n");
	console.main().print(L"bom lag en licht radioactieve voetstappen.\n");
	console.main().print(L"Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er\n");
	console.main().print(L"moest worden ingegrepen. Aangezien je niet echt een held bent, werd er beslo-\n");
	console.main().print(L"ten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om\n");
	console.main().print(L"zijn reis te coördineren via een geheime radiofrequentie.\n");
	console.main().print(L"Je hebt nooit meer iets van hem gehoord.\n\n");
	console.main().print(L"Nu ben jij aan de beurt.\n\n");
	console.main().print(L"Je staat op de trap die naar de vallei leidt. Rechts van je staat een ver-\n");
	console.main().print(L"weerd bordje: \"Betreden op eigen risico\". Je kijkt nog één keer achterom,\n");
	console.main().print(L"en met trillende benen loop je naar beneden...\n\n");
	
	console.main().wait_for_key(true);
	console.main().clear();

	
	console.main().print(L"Type h voor help.\n\n");
}

void force_exit(void)
{
	console.main().wait_for_key(true);

	remove(saved_status_path);

	console.main().clear();

	console.release();

	exit(0);
}

