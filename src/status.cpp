#include "r136.h"

void show_room_status(CoreData& core)
{
	static const wchar_t* youre_at_format = L"Je bevindt je %ls.\n";
	static const wchar_t* smoldering_forest_description = L"Om je heen zie je de smeulende resten van wat eens bos was.";

	auto current_room = core.status.current_room;
	const wchar_t* current_room_name = core.rooms[current_room].name;

	size_t youre_at_buffer_length = wcslen(youre_at_format) + wcslen(current_room_name);
	wchar_t* youre_at_buffer = new wchar_t[youre_at_buffer_length];
	swprintf(youre_at_buffer, youre_at_buffer_length, youre_at_format, current_room_name);
	
	write_to_main_window(youre_at_buffer);

	delete youre_at_buffer;

	if (current_room != RoomID::radioactive_cave && current_room != RoomID::fluorescent_cave
		&& to_value(current_room) >= 20 && !core.status.is_lamp_on)
	{
		print_to_main_window("Het is stekedonker en je ziet geen hand voor ogen.\n");
	}
	else
	{
		const wchar_t* description = core.status.has_tree_burned && core.rooms[current_room].is_forest 
			? smoldering_forest_description
			: core.rooms[current_room].description;

		if (description)
			write_to_main_window(description);
		
		print_to_main_window("\n");
		show_items(core);
	}

	show_open_directions(core.rooms[current_room].connections);
	print_to_main_window("\n");
}

void show_open_directions(RoomConnections connections)
{
	size_t count = connections.count();

	if (!count)
		return;

	print_to_main_window("Je kunt naar ");

	for (auto& element : connections)
	{
		switch (element.first)
		{
		case Command::east:
			print_to_main_window("het oosten");
			break;
		case Command::west:
			print_to_main_window("het westen");
			break;
		case Command::north:
			print_to_main_window("het noorden");
			break;
		case Command::south:
			print_to_main_window("het zuiden");
			break;
		case Command::up:
			print_to_main_window("boven");
			break;
		case Command::down:
			print_to_main_window("beneden");
			break;
		}

		switch (--count)
		{
		case 0:
			break;
		case 1:
			print_to_main_window(" en ");
			break;
		default:
			print_to_main_window(", ");
			break;
		}
	}

	print_to_main_window(".\n");
}

void show_items(CoreData& core)
{
	int count = 0;
	auto item_count = to_value(ItemID::COUNT);

	for (auto& element : core.items) 
		if (element.second.room == core.status.current_room)
			count++;

	if (!count)
		return;

	print_to_main_window("Hier lig%s ", count > 1 ? "gen" : "t");

	for (auto& element : core.items) 
	{
		auto& item = element.second;

		if (item.room != core.status.current_room)
			continue;

		if (getcurx(stdscr) > 54)
			print_to_main_window("\n");

		print_to_main_window(item.name);

		switch (--count)
		{
		case 0:
			break;
		case 1:
			print_to_main_window(" en ");
			break;
		default:
			print_to_main_window(", ");
			break;
		}
	}

	print_to_main_window(".\n");
}


bool progress_animate_status(CoreData& core)
{
	AnimateID present_animate = AnimateID::undefined;

	for (auto& element : core.animates)
	{
		if (element.second.room == core.status.current_room)
		{
			present_animate = element.first;
			break;
		}
	}

	switch (present_animate)
	{
	case AnimateID::hellhound:
		progress_hellhound_status(core);
		break;
	
	case AnimateID::red_troll:
		progress_red_troll_status(core);
		break;
	
	case AnimateID::plant:
		progress_plant_status(core);
		break;
	
	case AnimateID::gnu:
		progress_gnu_status(core);
		break;
	
	case AnimateID::dragon:
		progress_dragon_status(core);
		break;
	
	case AnimateID::swelling:
		progress_swelling_status(core);
		break;
	
	case AnimateID::door:
		progress_door_status(core);
		break;
	
	case AnimateID::voices:
		progress_voices_status(core);
		break;
	
	case AnimateID::barbecue:
		progress_barbecue_status(core);
		break;
	
	case AnimateID::tree:
		progress_tree_status(core);
		break;
	
	case AnimateID::green_crystal:
		progress_green_crystal_status(core);
		break;
	
	case AnimateID::computer:
		progress_computer_status(core);
		break;
	
	case AnimateID::dragon_head:
		progress_dragon_head_status(core);
		break;
	
	case AnimateID::lava:
		return progress_lava_status(core);
	
	case AnimateID::vacuum:
		print_to_main_window("Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een\n");
		print_to_main_window("verschrikkelijke pijn kraakt als een bliksem door je lijf. Je valt naar achte-\n");
		print_to_main_window("ren de grot uit, en daar val je even flauw.\n\n");

		core.status.life_points -= 4; //   Levenswond
		core.status.current_room = RoomID::snake_cave; //   Grot terug
	
		return false;
	
	case AnimateID::hatch:
		progress_hatch_status(core);
		break;
	
	case AnimateID::north_swamp:
	case AnimateID::middle_swamp:
	case AnimateID::south_swamp:
		print_to_main_window("Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond\n");
		print_to_main_window("onder de voeten hebt. Ondanks je wilde pogingen boven te blijven zak je\n");
		print_to_main_window("langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa\n");
		print_to_main_window("zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie,\n");
		print_to_main_window("en na enige tijd verlies je je bewustzijn.\n");
		print_to_main_window("Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot.\n\n");

		switch (core.status.current_room)
		{
		case RoomID::north_swamp:
			core.status.current_room = RoomID::empty_cave51;
			break;
	
		case RoomID::middle_swamp:
			core.status.current_room = RoomID::gloomy_cave;
			break;
	
		case RoomID::south_swamp:
			core.status.current_room = RoomID::rock_cave;
			break;
		}
	
		return false;
	
	case AnimateID::mist:
		print_to_main_window("In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen\n");
		write_to_main_window(L"ziet. Je verliest je orïentatiegevoel en stommelt paniekerig door de grot, op\n");
		print_to_main_window("zoek naar een uitgang.\n");
		print_to_main_window("Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden,\n");
		print_to_main_window("struikel je voorover een andere grot in.\n\n");

		switch(get_random_number(3))
		{
		case 0:
			core.status.current_room = RoomID::storm_cave;
			break;
	
		case 1:
			core.status.current_room = RoomID::small_cave;
			break;
	
		case 2:
			core.status.current_room = RoomID::stairwell_cave1;
			break;
		}
	
		return false;
	
	case AnimateID::teleporter:
		print_to_main_window("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het\n");
		print_to_main_window("plafond en tegen een van de wanden een enorm apparaat met een aantal\n");
		print_to_main_window("bedieningspanelen en beeldschermen.\n");
		print_to_main_window("Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal\n");
		print_to_main_window("in de grond, waarna een sirene begint te loeien. Van de schrik blijf je liggen,\n");
		print_to_main_window("en je ziet dat de lampen aan het plafond feller gaan branden en er grote\n");
		print_to_main_window("hoeveelheden data over de beeldschermen flitsen. Even later zie je een\n");
		print_to_main_window("oogverblindende flits en voel je je even gewichtloos.\n");
		print_to_main_window("Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\n");
		print_to_main_window("Sterker nog, je ligt buiten...\n\n");

		core.status.current_room = RoomID::forest1;

		return false;
	}

	return true;
}

void progress_hellhound_status(CoreData& core)
{
	switch (core.animates[AnimateID::hellhound].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe\n");
		print_to_main_window("tanden steken duidelijk af, en het rode kwijl druipt langzaam uit zijn bek.\n");
		print_to_main_window("Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel\n");
		print_to_main_window("klinkt een diep gegrom.\n\n");

		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_1:
		print_to_main_window("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn\n");
		print_to_main_window("nagels boren zich in je vlees, en op een gegeven moment bijt hij je hard in je\n");
		print_to_main_window("schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. De\n");
		print_to_main_window("hond laat je los, en hij kijkt je grommend aan.\n\n");

		core.status.life_points--; //  Wond
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn\n");
		print_to_main_window("keel, en hij staat klaar om opnieuw aan te vallen.\n\n");

		core.animates[AnimateID::hellhound].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_3:
		print_to_main_window("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je\n");
		print_to_main_window("deelt nog een slag uit, en een stuk vlees van de hond laat los.\n\n");

		core.items[ItemID::hound_meat].room = core.status.current_room;
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_4:
		print_to_main_window("De dode hellehond ligt in een bad van dampend bloed.\n\n");
		break;
	}
}

void progress_red_troll_status(CoreData& core)
{
	switch (core.animates[AnimateID::red_troll].status)
	{
	case AnimateStatus::initial:
    	write_to_main_window(L"Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar geërgerd.\n\n");

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_1:
		print_to_main_window("Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je\n");
		print_to_main_window("af.\n\n");

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn\n");
		print_to_main_window("tot je botten doordringen.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_3:
		print_to_main_window("Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep.\n\n");

		core.animates[AnimateID::red_troll].status = get_random_status(AnimateStatus::status_2, AnimateStatus::status_3);

		break;

	case AnimateStatus::booklet_thrown:
		print_to_main_window("Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en\n");
		print_to_main_window("roder. Op een gegeven moment klinkt een geborrel op uit het wezen, en met een\n");
		print_to_main_window("klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol\n");
		print_to_main_window("langzaam naar beneden.\n");
		print_to_main_window("Opeens zie je iets glinsteren.\n\n");

		core.items[ItemID::red_crystal].room = core.status.current_room;
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_5:
		print_to_main_window("Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm\n");
		print_to_main_window("zuigt aan je schoenen, en een vieze stank dringt in je neus.\n\n");

		break;
	}
}

void progress_plant_status(CoreData& core)
{
	switch (core.animates[AnimateID::plant].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit\n");
		print_to_main_window("in een afschrikwekkende kop, met afzichtelijke tanden. Hij heeft je gezien en\n");
		print_to_main_window("beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen\n");
		print_to_main_window("zetten zit je verstrengd in het monster, en zet de plant zijn tanden in je\n");
		print_to_main_window("nek.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::plant].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_1:
		print_to_main_window("De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek.\n");
		print_to_main_window("Met zijn groene oogjes kijkt hij je weer aan, en hij maakt aanstalten zijn\n");
		print_to_main_window("tanden opnieuw in je nek te zetten.\n\n");

		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via\n");
		print_to_main_window("je rug naar beneden, en de pijn is nu ondraaglijk. Na een tijdje laat de plant\n");
		print_to_main_window("je weer los.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::plant].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::dead:
		print_to_main_window("De resten van wat eerst een vleesetende plant was liggen nu op de grond van\n");
		print_to_main_window("de grot. Zijn bek ligt opengesperd, en zijn ogen rollen bijna uit zijn oogkas-\n");
		print_to_main_window("sen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\n");
		print_to_main_window("Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening.\n\n");

		core.rooms[RoomID::neglected_cave].connections.set(Command::north, RoomID::slime_cave); //	Maak verbinding met slijmgrot
		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_4:
		print_to_main_window("De vleesetende plant is niet veel meer dan een berg stinkend tuinafval.\n\n");

		break;
	}
}

void progress_gnu_status(CoreData& core)
{
	switch (core.animates[AnimateID::gnu].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aan-\n");
		print_to_main_window("kijkt. Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende\n");
		print_to_main_window("beestjes, die je nog nooit eerder gezien hebt. Het beest verspreidt een\n");
		print_to_main_window("afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe.\n\n");

		core.animates[AnimateID::gnu].status++;

		break;

	case AnimateStatus::status_1:
		print_to_main_window("De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je\n");
		print_to_main_window("hebt het gevoel alsof je longen uit je lijf worden geperst. Versuft sta je\n");
		print_to_main_window("weer op.\n\n");

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::poisonous_meat_fed:
		write_to_main_window(L"De gnoe ziet het vlees, snuffelt er aan, en slokt het in één hap naar binnen.\n");
		print_to_main_window("Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar\n");
		print_to_main_window("buiten. Hij zakt in elkaar en blijft roerloos liggen.\n\n");

		core.animates[AnimateID::gnu].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		print_to_main_window("Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er\n");
		print_to_main_window("als een papje naast.\n\n");

		break;
	}
}

void progress_dragon_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je\n");
		print_to_main_window("allemaal bespieden met gele oogjes. Zijn hele huid is bedekt met schimmel, en\n");
		print_to_main_window("uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af drup-\n");
		print_to_main_window("pelt. Opeens komt uit een van de bekken een rommelend geluid. Met moeite\n");
		print_to_main_window("versta je \"Ben jij een koekie?\".\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_1:
		print_to_main_window("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig\n");
		print_to_main_window("te snuiven.\n");
		print_to_main_window("De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van\n");
		print_to_main_window("walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt\n");
		print_to_main_window("\"BEN JIJ EEN KOEKIE?!?\".\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzet-\n");
		print_to_main_window("tende harde klap. Er kraakt iets in je hoofd, en een duizeling maakt zich van\n");
		print_to_main_window("je meester. Hij maakt aanstalten je nog een klap te verkopen.\n\n");

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::cookie_is_thrown:
		print_to_main_window("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\n");
		print_to_main_window("Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\n");
		print_to_main_window("Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak\n");
		print_to_main_window("slaapt.\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::sleeping_lightly:
		print_to_main_window("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn\n");
		print_to_main_window("lijf klinkt een diep gegrom.\n\n");

		break;

	case AnimateStatus::nightcap_on_head:
		print_to_main_window("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts\n");
		print_to_main_window("steken af tegen de beschimmelde huid, en de muts zakt iets scheef. Op een ge-\n");
		print_to_main_window("geven moment valt er iets, en het klettert tegen de harde rotsvloer.\n\n");

		core.items[ItemID::gas_capsule].room = core.status.current_room;
		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_6:

		print_to_main_window("De draak slaapt rustig.\n\n");

		break;
	}
}

void progress_swelling_status(CoreData& core)
{
	switch (core.animates[AnimateID::swelling].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je\n");
		print_to_main_window("aan met 2 gluiperige ogen, op zijn huid zitten schurftvlekken, en op zijn\n");
		print_to_main_window("mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich\n");
		print_to_main_window("vast aan alle wanden van de grot en verspert zo je weg.\n\n");

		core.animates[AnimateID::swelling].status++;

		break;

	case AnimateStatus::status_1:
		print_to_main_window("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.\n\n");

		break;

	case AnimateStatus::swelling_gassed:
		if (core.items[ItemID::gasmask].room == RoomID::owned)
		// gasmasker op
		{
			print_to_main_window("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n");
			print_to_main_window("Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen\n");
			print_to_main_window("overal scheuren in zijn schurfterige huid. Zijn tentakels komen langzaam met\n");
			print_to_main_window("een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in el-\n");
			print_to_main_window("kaar.\n\n");
		}
		else
		// geen masker... oeps!
		{
			print_to_main_window("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen,\n");
			print_to_main_window("voordat je zelf een kloppende hoofdpijn krijgt en onderuit gaat. Je hebt niets\n");
			print_to_main_window("om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer\n");
			print_to_main_window("bij.\n\n");

			core.status.life_points -= 4; //    Grote wond
		}

		core.rooms[RoomID::bat_cave].connections.set(Command::north, RoomID::damnation_cave);
		core.animates[AnimateID::swelling].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		print_to_main_window("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn\n");
		print_to_main_window("maag kruipen pissebedden en oorkruipers. Er verspreidt zich een sterke rot-\n");
		print_to_main_window("lucht, en er ontstaat langzaam een klein slijmplasje.\n\n");

		break;
	}
}

void progress_door_status(CoreData& core)
{
	switch (core.animates[AnimateID::door].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet\n");
		print_to_main_window("meer open te krijgen.\n\n");

		break;

	case AnimateStatus::door_open:
		write_to_main_window(L"Je zet één eind van het bot onder de deur, en op het andere begin je te duwen.\n");
		print_to_main_window("Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een\n");
		print_to_main_window("kier. Je geeft nog een duw, en langzaam draait de deur open.\n\n");

		core.rooms[RoomID::empty_cave45].connections.set(Command::north, RoomID::garbage_cave);
		core.animates[AnimateID::door].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("De deur is nu open, en geeft toegang tot een grot.\n\n");

		break;
	}
}

void progress_voices_status(CoreData& core)
{
	switch (core.animates[AnimateID::voices].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan:\n");
		print_to_main_window("\"Wat schreeuwt is in z'n hart nog een kind\".\n");
		print_to_main_window("Dan is het weer stil.\n\n");

		core.animates[AnimateID::voices].status++;

		break;

	case AnimateStatus::status_1:
		print_to_main_window("Vanuit de verte hoor je zachte, lachende stemmetjes.\n\n");

		break;
	}
}

void progress_barbecue_status(CoreData& core)
{
	switch (core.animates[AnimateID::barbecue].status)
	{
	case AnimateStatus::initial_burn:
		print_to_main_window("Op deze open plek staat een barbecue gezellig te branden.\n\n");

		break;

	case AnimateStatus::hashis_on_fire:
		print_to_main_window("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt\n");
		print_to_main_window("er niets.\n\n");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::meat_on_fire:
		print_to_main_window("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder\n");
		print_to_main_window("gebeurt er niets.\n\n");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::ingredient_burning:
		print_to_main_window("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.\n\n");

		break;

	case AnimateStatus::cookie_is_baking:
		write_to_main_window(L"Een grote rookontwikkeling treedt op wanneer het tweede ingrediënt in de\n");
		print_to_main_window("barbecue belandt.\n");
		write_to_main_window(L"Knetterend smelten de 2 ingrediënten om tot een koekje.\n\n");

		core.items[ItemID::cookie].room = core.status.current_room;
		core.animates[AnimateID::barbecue].status = AnimateStatus::initial_burn;

		break;
	}
}

void progress_tree_status(CoreData& core)
{
	switch (core.animates[AnimateID::tree].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit\n");
		print_to_main_window("een bordje met daarop de tekst \"Roken en open vuur verboden\".\n\n");

		break;

	case AnimateStatus::tree_on_fire:
		print_to_main_window("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam\n");
		print_to_main_window("te branden, en weldra staat hij in lichterlaaie. De vlammen slaan om zich heen,\n");
		print_to_main_window("en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee,\n");
		print_to_main_window("en de hitte is enorm.\n\n");

		if (core.items[ItemID::thermal_suit].room != RoomID::owned)
		{
			print_to_main_window("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwon-\n");
			print_to_main_window("den op.\n\n");

			core.status.life_points -= 4; //   Levenswond
		}

		core.status.has_tree_burned = true;
		core.items[ItemID::green_crystal].room = RoomID::forest4;
		core.animates[AnimateID::green_crystal].status = AnimateStatus::visible;
		core.animates[AnimateID::tree].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk\n");
		print_to_main_window("bord met daarop \"R   n e  op n v u  ver  d n\".\n\n");

		break;
	}
}

void progress_green_crystal_status(CoreData& core)
{
	switch (core.animates[AnimateID::green_crystal].status)
	{
	case AnimateStatus::initial:
		write_to_main_window(L"Je struikelt over iets. Door de begroeïing zie je niet wat het is.\n\n");

		break;
	}
}

void progress_computer_status(CoreData& core)
{
	switch (core.animates[AnimateID::computer].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("Er staat een computer van het merk Beull die bestaat bestaat uit een kast met\n");
		print_to_main_window("een 3.5-inch drive en een monitor. Op de monitor staat: \"Datadisk invoeren\n");
		print_to_main_window("a.u.b.\".\n\n");

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_1:
		print_to_main_window("De computer wacht nog steeds.\n\n");

		break;

	case AnimateStatus::computer_is_reading:
		print_to_main_window("De drive begint te lezen en na korte tijd verschijnt er informatie op het\n");
		print_to_main_window("scherm. Er staat: \"In het onderste grottenstelsel moet men een letter-\n");
		print_to_main_window("route volgen die resulteert in de naam van het te vinden voorwerp.\".\n");
		print_to_main_window("Na even wordt het scherm zwart.\n\n");

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_3:
		print_to_main_window("Er valt niets te zien op de monitor en de computer is stil.\n\n");

		break;
	}
}

void progress_dragon_head_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon_head].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een\n");
		print_to_main_window("geopende muil. Op de deur zit een zwaar slot.\n\n");

		break;

	case AnimateStatus::status_1:
		print_to_main_window("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer\n");
		print_to_main_window("opengaat. Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te\n");
		print_to_main_window("gloeien.\n\n");

		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("De ogen van de draak blijven licht gloeien.\n\n");

		break;

	case AnimateStatus::status_3:
		print_to_main_window("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het\n");
		print_to_main_window("kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.\n\n");

		core.animates[AnimateID::dragon_head].status++;
		break;

	case AnimateStatus::status_4:
		print_to_main_window("De ogen van de draak blijven gloeien.\n\n");

		break;

	case AnimateStatus::status_5:
		print_to_main_window("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft\n");
		print_to_main_window("hij dicht. De ogen beginnen nu steeds feller te gloeien. Op een gegeven moment\n");
		print_to_main_window("concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet\n");
		print_to_main_window("en wordt weerkaatst in een spiegel vlak achter je. De spiegel reflecteert het\n");
		print_to_main_window("licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\n");
		print_to_main_window("Daarna zwaait de deur langzaam met veel gepiep open.\n\n");

		core.rooms[RoomID::small_cave].connections.set(Command::north, RoomID::main_cave);
		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_6:
		print_to_main_window("De zware deur is nu open en geeft toegang tot een ruimte.\n\n");

		break;
	}
}

bool progress_lava_status(CoreData& core)
{
	switch (core.animates[AnimateID::lava].status)
	{
	case AnimateStatus::initial:
		if (core.items[ItemID::thermal_suit].room == RoomID::owned)
		{
			print_to_main_window("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke\n");
			print_to_main_window("damp, en een rode gloed verlicht de omtrek. De hitte is enorm, maar het hitte-\n");
			print_to_main_window("pak beschermt je tegen verbranding.\n\n");
		}
		else
		{
			print_to_main_window("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je\n");
			print_to_main_window("een aantal brandwonden oploopt en naar achteren wordt geblazen.\n\n");

			core.status.current_room = RoomID::oil_cave; //   Grot terug
			core.status.life_points -= 4; //   Levenswond

			return false;
		}

		return true;

	case AnimateStatus::bomb_dropped:
		print_to_main_window("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt\n");
		print_to_main_window("de bom langzaam weg naar beneden. De lava begint op een gegeven moment vreemd\n");
		print_to_main_window("te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver-\n");
		print_to_main_window("blindende flits vanuit het lava. Daarna wordt het weer rustiger.\n\n");
		print_to_main_window("Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door\n");
		print_to_main_window("dit positronenwapen, waarvan de beginselen mede van jouw handen komen. Je mis-\n");
		print_to_main_window("sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het\n");
		print_to_main_window("grottenstelsel.\n\n");

		force_exit();
	}

	return true;
}

void progress_hatch_status(CoreData& core)
{
	switch (core.animates[AnimateID::hatch].status)
	{
	case AnimateStatus::initial:
		print_to_main_window("Er zit een dicht, houten luik in het plafond. Je kunt er niet bij.\n\n");

		break;

	case AnimateStatus::hatch_opening:
		print_to_main_window("Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden.\n\n");

		core.items[ItemID::paper].room = RoomID::r_cave;
		core.animates[AnimateID::hatch].status++;

		break;

	case AnimateStatus::status_2:
		print_to_main_window("Het luik aan het plafond hangt nu open. Er zit een leeg gat.\n\n");

		break;
	}
}


