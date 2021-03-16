#include "status.h"

void show_room_status(CoreData& core)
{
	static const wchar_t* youre_at_format = L"Je bevindt je %ls.\n";
	static const wchar_t* smoldering_forest_description = L"Om je heen zie je de smeulende resten van wat eens bos was.";

	auto current_room_id = core.status.current_room;
	auto& current_room = core.rooms[current_room_id];
	const wchar_t* current_room_name = current_room.name;

	size_t youre_at_buffer_length = wcslen(youre_at_format) + wcslen(current_room_name);
	wchar_t* youre_at_buffer = new wchar_t[youre_at_buffer_length];
	swprintf(youre_at_buffer, youre_at_buffer_length, youre_at_format, current_room_name);
	
	console.main().write(youre_at_buffer);

	delete[] youre_at_buffer;

	if (current_room_id != RoomID::radioactive_cave && current_room_id != RoomID::fluorescent_cave
		&& to_value(current_room_id) >= 20 && !core.status.is_lamp_on)
	{
		console.main().print("Het is stekedonker en je ziet geen hand voor ogen.\n");
	}
	else
	{
		const wchar_t* description = core.status.has_tree_burned && current_room.is_forest 
			? smoldering_forest_description
			: current_room.description;

		if (description)
			console.main().write(description);
		
		console.main().print("\n");
		show_items(core);
	}

	show_open_directions(current_room.connections);
	console.main().print("\n");
}

void show_open_directions(RoomConnections& connections)
{
	size_t count = connections.count();

	if (!count)
		return;

	console.main().print("Je kunt naar ");

	for (auto& element : connections)
	{
		switch (element.first)
		{
		case Command::east:
			console.main().print("het oosten");
			break;
		case Command::west:
			console.main().print("het westen");
			break;
		case Command::north:
			console.main().print("het noorden");
			break;
		case Command::south:
			console.main().print("het zuiden");
			break;
		case Command::up:
			console.main().print("boven");
			break;
		case Command::down:
			console.main().print("beneden");
			break;
		}

		switch (--count)
		{
		case 0:
			break;
		case 1:
			console.main().print(" en ");
			break;
		default:
			console.main().print(", ");
			break;
		}
	}

	console.main().print(".\n");
}

void show_items(CoreData& core)
{
	int count = 0;
	constexpr auto item_count = to_value(ItemID::COUNT);

	for (auto& element : core.items) 
		if (element.second->room == core.status.current_room)
			count++;

	if (!count)
		return;

	console.main().print("Hier lig%s ", count > 1 ? "gen" : "t");

	for (auto& element : core.items) 
	{
		auto& item = *element.second;

		if (item.room != core.status.current_room)
			continue;

		if (getcurx(stdscr) > 54)
			console.main().print("\n");

		console.main().print(item.name);

		switch (--count)
		{
		case 0:
			break;
		case 1:
			console.main().print(" en ");
			break;
		default:
			console.main().print(", ");
			break;
		}
	}

	console.main().print(".\n");
}


bool progress_animate_status(CoreData& core)
{
	AnimateID present_animate = AnimateID::undefined;

	for (auto& element : core.animates)
	{
		if (element.second->room == core.status.current_room)
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
		console.main().print("Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een\n");
		console.main().print("verschrikkelijke pijn kraakt als een bliksem door je lijf. Je valt naar achte-\n");
		console.main().print("ren de grot uit, en daar val je even flauw.\n\n");

		core.status.life_points -= 4; //   Levenswond
		core.status.current_room = RoomID::snake_cave; //   Grot terug
	
		return false;
	
	case AnimateID::hatch:
		progress_hatch_status(core);
		break;
	
	case AnimateID::north_swamp:
	case AnimateID::middle_swamp:
	case AnimateID::south_swamp:
		console.main().print("Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond\n");
		console.main().print("onder de voeten hebt. Ondanks je wilde pogingen boven te blijven zak je\n");
		console.main().print("langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa\n");
		console.main().print("zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie,\n");
		console.main().print("en na enige tijd verlies je je bewustzijn.\n");
		console.main().print("Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot.\n\n");

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
		console.main().print("In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen\n");
		console.main().write(L"ziet. Je verliest je orïentatiegevoel en stommelt paniekerig door de grot, op\n");
		console.main().print("zoek naar een uitgang.\n");
		console.main().print("Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden,\n");
		console.main().print("struikel je voorover een andere grot in.\n\n");

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
		console.main().print("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het\n");
		console.main().print("plafond en tegen een van de wanden een enorm apparaat met een aantal\n");
		console.main().print("bedieningspanelen en beeldschermen.\n");
		console.main().print("Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal\n");
		console.main().print("in de grond, waarna een sirene begint te loeien. Van de schrik blijf je liggen,\n");
		console.main().print("en je ziet dat de lampen aan het plafond feller gaan branden en er grote\n");
		console.main().print("hoeveelheden data over de beeldschermen flitsen. Even later zie je een\n");
		console.main().print("oogverblindende flits en voel je je even gewichtloos.\n");
		console.main().print("Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\n");
		console.main().print("Sterker nog, je ligt buiten...\n\n");

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
		console.main().print("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe\n");
		console.main().print("tanden steken duidelijk af, en het rode kwijl druipt langzaam uit zijn bek.\n");
		console.main().print("Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel\n");
		console.main().print("klinkt een diep gegrom.\n\n");

		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn\n");
		console.main().print("nagels boren zich in je vlees, en op een gegeven moment bijt hij je hard in je\n");
		console.main().print("schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. De\n");
		console.main().print("hond laat je los, en hij kijkt je grommend aan.\n\n");

		core.status.life_points--; //  Wond
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn\n");
		console.main().print("keel, en hij staat klaar om opnieuw aan te vallen.\n\n");

		core.animates[AnimateID::hellhound].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_3:
		console.main().print("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je\n");
		console.main().print("deelt nog een slag uit, en een stuk vlees van de hond laat los.\n\n");

		core.items[ItemID::hound_meat].room = core.status.current_room;
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_4:
		console.main().print("De dode hellehond ligt in een bad van dampend bloed.\n\n");
		break;
	}
}

void progress_red_troll_status(CoreData& core)
{
	switch (core.animates[AnimateID::red_troll].status)
	{
	case AnimateStatus::initial:
    	console.main().write(L"Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar geërgerd.\n\n");

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je\n");
		console.main().print("af.\n\n");

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn\n");
		console.main().print("tot je botten doordringen.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_3:
		console.main().print("Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep.\n\n");

		core.animates[AnimateID::red_troll].status = get_random_status(AnimateStatus::status_2, AnimateStatus::status_3);

		break;

	case AnimateStatus::booklet_thrown:
		console.main().print("Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en\n");
		console.main().print("roder. Op een gegeven moment klinkt een geborrel op uit het wezen, en met een\n");
		console.main().print("klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol\n");
		console.main().print("langzaam naar beneden.\n");
		console.main().print("Opeens zie je iets glinsteren.\n\n");

		core.items[ItemID::red_crystal].room = core.status.current_room;
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_5:
		console.main().print("Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm\n");
		console.main().print("zuigt aan je schoenen, en een vieze stank dringt in je neus.\n\n");

		break;
	}
}

void progress_plant_status(CoreData& core)
{
	switch (core.animates[AnimateID::plant].status)
	{
	case AnimateStatus::initial:
		console.main().print("In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit\n");
		console.main().print("in een afschrikwekkende kop, met afzichtelijke tanden. Hij heeft je gezien en\n");
		console.main().print("beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen\n");
		console.main().print("zetten zit je verstrengd in het monster, en zet de plant zijn tanden in je\n");
		console.main().print("nek.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::plant].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_1:
		console.main().print("De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek.\n");
		console.main().print("Met zijn groene oogjes kijkt hij je weer aan, en hij maakt aanstalten zijn\n");
		console.main().print("tanden opnieuw in je nek te zetten.\n\n");

		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via\n");
		console.main().print("je rug naar beneden, en de pijn is nu ondraaglijk. Na een tijdje laat de plant\n");
		console.main().print("je weer los.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::plant].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::dead:
		console.main().print("De resten van wat eerst een vleesetende plant was liggen nu op de grond van\n");
		console.main().print("de grot. Zijn bek ligt opengesperd, en zijn ogen rollen bijna uit zijn oogkas-\n");
		console.main().print("sen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\n");
		console.main().print("Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening.\n\n");

		core.rooms[RoomID::neglected_cave].connections.set(Command::north, RoomID::slime_cave); //	Maak verbinding met slijmgrot
		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_4:
		console.main().print("De vleesetende plant is niet veel meer dan een berg stinkend tuinafval.\n\n");

		break;
	}
}

void progress_gnu_status(CoreData& core)
{
	switch (core.animates[AnimateID::gnu].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aan-\n");
		console.main().print("kijkt. Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende\n");
		console.main().print("beestjes, die je nog nooit eerder gezien hebt. Het beest verspreidt een\n");
		console.main().print("afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe.\n\n");

		core.animates[AnimateID::gnu].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je\n");
		console.main().print("hebt het gevoel alsof je longen uit je lijf worden geperst. Versuft sta je\n");
		console.main().print("weer op.\n\n");

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::poisonous_meat_fed:
		console.main().write(L"De gnoe ziet het vlees, snuffelt er aan, en slokt het in één hap naar binnen.\n");
		console.main().print("Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar\n");
		console.main().print("buiten. Hij zakt in elkaar en blijft roerloos liggen.\n\n");

		core.animates[AnimateID::gnu].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print("Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er\n");
		console.main().print("als een papje naast.\n\n");

		break;
	}
}

void progress_dragon_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon].status)
	{
	case AnimateStatus::initial:
		console.main().print("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je\n");
		console.main().print("allemaal bespieden met gele oogjes. Zijn hele huid is bedekt met schimmel, en\n");
		console.main().print("uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af drup-\n");
		console.main().print("pelt. Opeens komt uit een van de bekken een rommelend geluid. Met moeite\n");
		console.main().print("versta je \"Ben jij een koekie?\".\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig\n");
		console.main().print("te snuiven.\n");
		console.main().print("De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van\n");
		console.main().print("walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt\n");
		console.main().print("\"BEN JIJ EEN KOEKIE?!?\".\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzet-\n");
		console.main().print("tende harde klap. Er kraakt iets in je hoofd, en een duizeling maakt zich van\n");
		console.main().print("je meester. Hij maakt aanstalten je nog een klap te verkopen.\n\n");

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::cookie_is_thrown:
		console.main().print("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\n");
		console.main().print("Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\n");
		console.main().print("Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak\n");
		console.main().print("slaapt.\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::sleeping_lightly:
		console.main().print("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn\n");
		console.main().print("lijf klinkt een diep gegrom.\n\n");

		break;

	case AnimateStatus::nightcap_on_head:
		console.main().print("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts\n");
		console.main().print("steken af tegen de beschimmelde huid, en de muts zakt iets scheef. Op een ge-\n");
		console.main().print("geven moment valt er iets, en het klettert tegen de harde rotsvloer.\n\n");

		core.items[ItemID::gas_capsule].room = core.status.current_room;
		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_6:

		console.main().print("De draak slaapt rustig.\n\n");

		break;
	}
}

void progress_swelling_status(CoreData& core)
{
	switch (core.animates[AnimateID::swelling].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je\n");
		console.main().print("aan met 2 gluiperige ogen, op zijn huid zitten schurftvlekken, en op zijn\n");
		console.main().print("mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich\n");
		console.main().print("vast aan alle wanden van de grot en verspert zo je weg.\n\n");

		core.animates[AnimateID::swelling].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.\n\n");

		break;

	case AnimateStatus::swelling_gassed:
		if (core.items[ItemID::gasmask].room == RoomID::owned)
		// gasmasker op
		{
			console.main().print("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n");
			console.main().print("Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen\n");
			console.main().print("overal scheuren in zijn schurfterige huid. Zijn tentakels komen langzaam met\n");
			console.main().print("een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in el-\n");
			console.main().print("kaar.\n\n");
		}
		else
		// geen masker... oeps!
		{
			console.main().print("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen,\n");
			console.main().print("voordat je zelf een kloppende hoofdpijn krijgt en onderuit gaat. Je hebt niets\n");
			console.main().print("om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer\n");
			console.main().print("bij.\n\n");

			core.status.life_points -= 4; //    Grote wond
		}

		core.rooms[RoomID::bat_cave].connections.set(Command::north, RoomID::damnation_cave);
		core.animates[AnimateID::swelling].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn\n");
		console.main().print("maag kruipen pissebedden en oorkruipers. Er verspreidt zich een sterke rot-\n");
		console.main().print("lucht, en er ontstaat langzaam een klein slijmplasje.\n\n");

		break;
	}
}

void progress_door_status(CoreData& core)
{
	switch (core.animates[AnimateID::door].status)
	{
	case AnimateStatus::initial:
		console.main().print("In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet\n");
		console.main().print("meer open te krijgen.\n\n");

		break;

	case AnimateStatus::door_open:
		console.main().write(L"Je zet één eind van het bot onder de deur, en op het andere begin je te duwen.\n");
		console.main().print("Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een\n");
		console.main().print("kier. Je geeft nog een duw, en langzaam draait de deur open.\n\n");

		core.rooms[RoomID::empty_cave45].connections.set(Command::north, RoomID::garbage_cave);
		core.animates[AnimateID::door].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De deur is nu open, en geeft toegang tot een grot.\n\n");

		break;
	}
}

void progress_voices_status(CoreData& core)
{
	switch (core.animates[AnimateID::voices].status)
	{
	case AnimateStatus::initial:
		console.main().print("Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan:\n");
		console.main().print("\"Wat schreeuwt is in z'n hart nog een kind\".\n");
		console.main().print("Dan is het weer stil.\n\n");

		core.animates[AnimateID::voices].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("Vanuit de verte hoor je zachte, lachende stemmetjes.\n\n");

		break;
	}
}

void progress_barbecue_status(CoreData& core)
{
	switch (core.animates[AnimateID::barbecue].status)
	{
	case AnimateStatus::initial_burn:
		console.main().print("Op deze open plek staat een barbecue gezellig te branden.\n\n");

		break;

	case AnimateStatus::hashis_on_fire:
		console.main().print("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt\n");
		console.main().print("er niets.\n\n");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::meat_on_fire:
		console.main().print("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder\n");
		console.main().print("gebeurt er niets.\n\n");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::ingredient_burning:
		console.main().print("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.\n\n");

		break;

	case AnimateStatus::cookie_is_baking:
		console.main().write(L"Een grote rookontwikkeling treedt op wanneer het tweede ingrediënt in de\n");
		console.main().print("barbecue belandt.\n");
		console.main().write(L"Knetterend smelten de 2 ingrediënten om tot een koekje.\n\n");

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
		console.main().print("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit\n");
		console.main().print("een bordje met daarop de tekst \"Roken en open vuur verboden\".\n\n");

		break;

	case AnimateStatus::tree_on_fire:
		console.main().print("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam\n");
		console.main().print("te branden, en weldra staat hij in lichterlaaie. De vlammen slaan om zich heen,\n");
		console.main().print("en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee,\n");
		console.main().print("en de hitte is enorm.\n\n");

		if (core.items[ItemID::thermal_suit].room != RoomID::owned)
		{
			console.main().print("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwon-\n");
			console.main().print("den op.\n\n");

			core.status.life_points -= 4; //   Levenswond
		}

		core.status.has_tree_burned = true;
		core.items[ItemID::green_crystal].room = RoomID::forest4;
		core.animates[AnimateID::green_crystal].status = AnimateStatus::visible;
		core.animates[AnimateID::tree].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk\n");
		console.main().print("bord met daarop \"R   n e  op n v u  ver  d n\".\n\n");

		break;
	}
}

void progress_green_crystal_status(CoreData& core)
{
	switch (core.animates[AnimateID::green_crystal].status)
	{
	case AnimateStatus::initial:
		console.main().write(L"Je struikelt over iets. Door de begroeïing zie je niet wat het is.\n\n");

		break;
	}
}

void progress_computer_status(CoreData& core)
{
	switch (core.animates[AnimateID::computer].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat een computer van het merk Beull die bestaat bestaat uit een kast met\n");
		console.main().print("een 3.5-inch drive en een monitor. Op de monitor staat: \"Datadisk invoeren\n");
		console.main().print("a.u.b.\".\n\n");

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De computer wacht nog steeds.\n\n");

		break;

	case AnimateStatus::computer_is_reading:
		console.main().print("De drive begint te lezen en na korte tijd verschijnt er informatie op het\n");
		console.main().print("scherm. Er staat: \"In het onderste grottenstelsel moet men een letter-\n");
		console.main().print("route volgen die resulteert in de naam van het te vinden voorwerp.\".\n");
		console.main().print("Na even wordt het scherm zwart.\n\n");

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_3:
		console.main().print("Er valt niets te zien op de monitor en de computer is stil.\n\n");

		break;
	}
}

void progress_dragon_head_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon_head].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een\n");
		console.main().print("geopende muil. Op de deur zit een zwaar slot.\n\n");

		break;

	case AnimateStatus::status_1:
		console.main().print("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer\n");
		console.main().print("opengaat. Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te\n");
		console.main().print("gloeien.\n\n");

		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De ogen van de draak blijven licht gloeien.\n\n");

		break;

	case AnimateStatus::status_3:
		console.main().print("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het\n");
		console.main().print("kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.\n\n");

		core.animates[AnimateID::dragon_head].status++;
		break;

	case AnimateStatus::status_4:
		console.main().print("De ogen van de draak blijven gloeien.\n\n");

		break;

	case AnimateStatus::status_5:
		console.main().print("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft\n");
		console.main().print("hij dicht. De ogen beginnen nu steeds feller te gloeien. Op een gegeven moment\n");
		console.main().print("concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet\n");
		console.main().print("en wordt weerkaatst in een spiegel vlak achter je. De spiegel reflecteert het\n");
		console.main().print("licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\n");
		console.main().print("Daarna zwaait de deur langzaam met veel gepiep open.\n\n");

		core.rooms[RoomID::small_cave].connections.set(Command::north, RoomID::main_cave);
		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_6:
		console.main().print("De zware deur is nu open en geeft toegang tot een ruimte.\n\n");

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
			console.main().print("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke\n");
			console.main().print("damp, en een rode gloed verlicht de omtrek. De hitte is enorm, maar het hitte-\n");
			console.main().print("pak beschermt je tegen verbranding.\n\n");
		}
		else
		{
			console.main().print("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je\n");
			console.main().print("een aantal brandwonden oploopt en naar achteren wordt geblazen.\n\n");

			core.status.current_room = RoomID::oil_cave; //   Grot terug
			core.status.life_points -= 4; //   Levenswond

			return false;
		}

		return true;

	case AnimateStatus::bomb_dropped:
		console.main().print("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt\n");
		console.main().print("de bom langzaam weg naar beneden. De lava begint op een gegeven moment vreemd\n");
		console.main().print("te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver-\n");
		console.main().print("blindende flits vanuit het lava. Daarna wordt het weer rustiger.\n\n");
		console.main().print("Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door\n");
		console.main().print("dit positronenwapen, waarvan de beginselen mede van jouw handen komen. Je mis-\n");
		console.main().print("sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het\n");
		console.main().print("grottenstelsel.\n\n");

		force_exit();
	}

	return true;
}

void progress_hatch_status(CoreData& core)
{
	switch (core.animates[AnimateID::hatch].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er zit een dicht, houten luik in het plafond. Je kunt er niet bij.\n\n");

		break;

	case AnimateStatus::hatch_opening:
		console.main().print("Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden.\n\n");

		core.items[ItemID::paper].room = RoomID::r_cave;
		core.animates[AnimateID::hatch].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("Het luik aan het plafond hangt nu open. Er zit een leeg gat.\n\n");

		break;
	}
}


