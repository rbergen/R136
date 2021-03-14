#include "r136.h"
#include <time.h>
#include "init.h"

Room rooms[to_value(RoomID::COUNT)] = { // { name, description, is_forest }
	{ L"in het bos",					L"Je bevindt je in een uithoek van een donker bos. Overal hoor je enge geluiden.", true },
	{ L"in het bos",					L"Aan de zuidkant zie je een hek dat toegang geeft tot een donkere plaats.", true },
	{ L"in het bos", 					L"Er komt een modderige geur uit het oosten.", true },
	{ L"in het moeras",					L"Er hangt een griezelige nevel over het stinkende oppervlak."},
	{ L"in het bos",					L"Er komt een modderige geur uit het westen.", true },
	{ L"in het bos",					L"Pas op voor de laaghangende takken!", true },
	{ L"op de begraafplaats",			L"Een lucht van rottend vlees dringt in je neus. Je denkt dat je een grafsteen\nziet bewegen." },
	{ L"in het bos", nullptr, true },
	{ L"in het moeras",					L"Er hangt een griezelige nevel over het stinkende oppervlak." },
	{ L"op een open plek",				L"Er komt een modderige geur uit het westen." },
	{ L"in het bos", nullptr, true },
	{ L"in het bos",					L"Je trapt bijna in een bereklem.", true },
	{ L"op een open plek",				L"Door de mist zie je nog net de omtrekken van het donkere bos." },
	{ L"op het moeraspad",				L"Er ligt hier een skelet, waarschijnlijk een van je voorgangers." },
	{ L"op een open plek",				L"Bij het licht van een halve maan onderscheid je nog net de vorm van een galg." },
	{ L"in het bos",					L"In de verte hoor je het trieste gehuil van een weerwolf.", true },
	{ L"in het bos", nullptr, true },
	{ L"op een open plek",				L"Er ligt hier een dood konijn dat wordt belaagd door vliegen." },
	{ L"in het moeras",					L"Er hangt een griezelige nevel over het stinkende oppervlak." },
	{ L"in de ruïne",					L"De ruïne is een spookachtige bouwval. Er is hier een wankele trap die naar\nbeneden leidt." },

	{ L"in de slijmgrot",				L"De wanden van deze grot zijn bekleed met een snotachtig slijm." },
	{ L"in de zwarte grot",				L"Je ziet geen hand voor ogen." },
	{ L"in de drugsgrot" },
	{ L"in de geile grot",				L"Aan de muren hangen gelige, gescheurde Playboy-posters." },
	{ L"in de dwangbuisgrot",			L"Er hangt hier een dwangbuis, met daarin een verminkt lijk." },
	{ L"in een verwaarloosde grot" },
	{ L"in een lege grot" },
	{ L"in de hoofdgrot",				L"Er staat hier een batterij aan mysterieuze apparatuur." },
	{ L"in de hiërogliefengrot",		L"Op de wanden staan hiërogliefen waar je geen wijs uit wordt." },
	{ L"in de stankgrot",				L"Er hangt hier een smerige lucht die je herinnert aan de zware lucht van een\nbeerput." },
	{ L"in een troosteloze grot" },
	{ L"in de TL-grot",					L"De grot wordt zwak verlicht door een lichtbron die hoog aan het plafond hangt." },
	{ L"in een kleine grot" },
	{ L"in de ijsgrot",					L"In deze grot lijkt het net of alles van ijs is, en je krijgt rillingen." },
	{ L"in de kaktusgrot",				L"Je bent omringd door giftige kaktussen die in deze grot staan." },
	{ L"in de stalagmietengrot",		L"Hier zie je een traliewerk van stalagmieten." },
	{ L"in de stormgrot",				L"Door deze grot loeit een harde wind, waardoor je je vast moet grijpen aan een\nvan de wanden." },
	{ L"in de mistgrot",				L"Een dichte mist belemmert je zicht, en je verliest je orïentatiegevoel." },
	{ L"in de wenteltrapgrot",			L"In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\nandere niveaus leidt." },
	{ L"in de tentakelgrot",			L"Van alle kanten komen grote tentakels die je aftasten en groene sporen op je\nhuid achterlaten." },

	{ L"in de vuilnisgrot",				L"In deze grot ligt een grote stapel rottende etensresten. De stank is bijna on-\ndraaglijk." },
	{ L"in de echogrot",				L"Hier worden alle geluiden die je maakt tegen de wanden geëcho'd." },
	{ L"in de geheime grot",			L"Op de grond van deze grot liggen allerlei onbekende en geheimzinnige voorwer-\npen." },
	{ L"in de voedselgrot",				L"Zo te ruiken is dit waarschijnlijk eens een keuken geweest..." },
	{ L"in de grot van de gnoe",		L"Hier liggen de geraamtes van wezens die eerder ten prooi zijn gevallen aan de\ngnoe." },
	{ L"in een lege grot" },
	{ L"in de ogengrot",				L"Van alle kanten wordt je bespied door rode, bloeddoorlopen ogen die precies\nvolgen wat je doet."},
	{ L"in de rotsgrot",				L"Overal zie je hier scherpe rotspunten. Aan een aantal ervan zitten bruine kors-\nten."},
	{ L"in de leegte" },
	{ L"op de zandbank",				L"Op de vloer liggen vreemde patronen, gevormd uit verschillende soorten zand."},
	{ L"in de martelgrot",				L"Onder de vage schemering van de martelvuren zie je nog net een duimschroef en\nwat stekelige voorwerpen waar nog wat bloed aan zit."},
	{ L"in een lege grot" },
	{ L"in de veilige grot",			L"Dit is de enige grot waar je je een beetje veilig voelt."},
	{ L"in de nauwe rotsspleet",		L"Aan alle kanten wordt je omringd door hoge rotsmuren. Alleen in het westen zie\nje een opening."},
	{ L"in de oliegrot",				L"Vanuit het zuiden verspreidt zich een enorme hitte, die in deze grot nog net\ndraaglijk is."},
	{ L"in een lege grot" },
	{ L"in een wenteltrapgrot",			L"In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\nandere niveaus leidt."},
	{ L"in de spinnengrot",				L"Het wemelt hier van de tarantula's. Bij elke stap die je zet hoor je het onder\nje voeten kraken, en ze kruipen langs je benen omhoog."},
	{ L"in de pratende grot" },
	{ L"op de lavaput" },

	{ L"in de skoebiegrot",				L"Uit alle richtingen komen rare geluiden, als in een gesticht."},
	{ L"in de radioactieve grot",		L"Door de hoge radioactiviteit is deze grot zwak verlicht." },
	{ L"in de i-grot" },
	{ L"in de p-grot" },
	{ L"in de a-grot",					L"In deze grot bevindt zich het stenen beeld van een oud, jou onbekend wezen." },
	{ L"in de dodengrot",				L"De naam van deze grot spreekt voor zich..." },
	{ L"in de r-grot" },
	{ L"in de e-grot" },
	{ L"in de wenteltrapgrot",			L"In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\nandere niveaus leidt." },
	{ L"in de P-grot" },
	{ L"in de grot der verdoemenis",	L"In deze grot heerst een haast verstikkende sfeer, en je voelt je niet prettig." },
	{ L"in de vacuumgrot" },
	{ L"in de rode grot" },
	{ L"in de neongrot",				L"Deze grot is fel gekleurd. Er staan patronen die je doen denken aan zwarte ma-\ngie." },
	{ L"in de bloedgrot",				L"Het geraamte van een groot beest ligt hier op de grond en een aantal ingewanden\nliggen er naast." },
	{ L"in de vleermuisgrot",			L"In deze grot fladderen overal vleermuizen, op zoek naar hun prooi."},
	{ L"in de slangengrot",				L"Je hoort het geluid van een ratelslang. Bij de weg naar het noorden staat een\ndoodskop getekend, die een gevaar aanduidt." },
	{ L"in de kwabbengrot" },
	{ L"in de glibbergrot",				L"Je glijdt bijna uit over de zeepachtige prut die overal in de grot ligt. Tus-\nsen de glibberige massa steekt een paal omhoog met daarop een pijl die naar\nhet oosten wijst." },
	{ L"in de teleportgrot" }
};

struct LevelConnection
{
	RoomID from;
	Command direction;
	RoomID to;
};

struct BlockedConnection
{
	RoomID room;
	Command direction;
};

std::vector<LevelConnection> level_connections = { // { from, direction, to }
	{ RoomID::cemetery, Command::down, RoomID::cactus_cave },
	{ RoomID::ruin, Command::down, RoomID::black_cave },
	{ RoomID::black_cave, Command::up, RoomID::ruin },
	{ RoomID::hieroglyphs_cave, Command::down, RoomID::talking_cave },
	{ RoomID::storm_cave, Command::down, RoomID::eyes_cave },
	{ RoomID::stairwell_cave1, Command::down, RoomID::stairwell_cave2 },
	{ RoomID::eyes_cave, Command::up, RoomID::storm_cave },
	{ RoomID::stairwell_cave2, Command::up, RoomID::stairwell_cave1 },
	{ RoomID::stairwell_cave2, Command::down, RoomID::stairwell_cave3 },
	{ RoomID::talking_cave, Command::up, RoomID::hieroglyphs_cave },
	{ RoomID::stairwell_cave3, Command::up, RoomID::stairwell_cave2 }
};

std::vector<BlockedConnection> blocked_connections = { // { room, direction }
	{RoomID::north_swamp, Command::west}, {RoomID::north_swamp, Command::east}, {RoomID::north_swamp, Command::south},
	{RoomID::middle_swamp, Command::west}, {RoomID::middle_swamp, Command::east}, {RoomID::middle_swamp, Command::north}, {RoomID::middle_swamp, Command::south},
	{RoomID::forest5, Command::east},
	{RoomID::cemetery, Command::west},
	{RoomID::forest11, Command::east},
	{RoomID::open_space12, Command::west},
	{RoomID::south_swamp, Command::west}, {RoomID::south_swamp, Command::east}, {RoomID::south_swamp, Command::north},
	{RoomID::ruin, Command::west},
	{RoomID::slime_cave, Command::east},
	{RoomID::black_cave, Command::west},
	{RoomID::drugs_cave, Command::east}, {RoomID::drugs_cave, Command::south},
	{RoomID::horny_cave, Command::west}, {RoomID::horny_cave, Command::east},
	{RoomID::straitjacket_cave, Command::west},
	{RoomID::neglected_cave, Command::east}, {RoomID::neglected_cave, Command::north},
	{RoomID::empty_cave26, Command::west}, {RoomID::empty_cave26, Command::east},
	{RoomID::main_cave, Command::east}, {RoomID::main_cave, Command::west}, {RoomID::main_cave, Command::north},
	{RoomID::hieroglyphs_cave, Command::west},
	{RoomID::fluorescent_cave, Command::south},
	{RoomID::small_cave, Command::north},
	{RoomID::ice_cave, Command::east},
	{RoomID::cactus_cave, Command::west}, {RoomID::cactus_cave, Command::south},
	{RoomID::storm_cave, Command::north},
	{RoomID::mist_cave, Command::west}, {RoomID::mist_cave, Command::north}, {RoomID::mist_cave, Command::east},
	{RoomID::tentacle_cave, Command::north},
	{RoomID::garbage_cave, Command::east},
	{RoomID::echo_cave, Command::west}, {RoomID::echo_cave, Command::east},
	{RoomID::secret_cave, Command::west}, {RoomID::secret_cave, Command::east},
	{RoomID::food_cave, Command::west}, {RoomID::food_cave, Command::east},
	{RoomID::gnu_cave, Command::west},
	{RoomID::empty_cave45, Command::north},
	{RoomID::eyes_cave, Command::east},
	{RoomID::rock_cave, Command::west},
	{RoomID::emptiness, Command::south},
	{RoomID::safe_cave, Command::east}, {RoomID::safe_cave, Command::south},
	{RoomID::narrow_cleft, Command::north}, {RoomID::narrow_cleft, Command::east}, {RoomID::narrow_cleft, Command::south},
	{RoomID::oil_cave, Command::west},
	{RoomID::empty_cave55, Command::east},
	{RoomID::stairwell_cave2, Command::west},
	{RoomID::spider_cave, Command::north},
	{RoomID::talking_cave, Command::east},
	{RoomID::lava_pit, Command::west},
	{RoomID::scooby_cave, Command::east},
	{RoomID::radioactive_cave, Command::west}, {RoomID::radioactive_cave, Command::south},
	{RoomID::death_cave, Command::south},
	{RoomID::r_cave, Command::north}, {RoomID::r_cave, Command::south},
	{RoomID::e_cave, Command::south},
	{RoomID::damnation_cave, Command::north}, {RoomID::damnation_cave, Command::east},
	{RoomID::vacuum_cave, Command::west}, {RoomID::vacuum_cave, Command::north}, {RoomID::vacuum_cave, Command::east},
	{RoomID::red_cave, Command::west}, {RoomID::red_cave, Command::north}, {RoomID::red_cave, Command::east},
	{RoomID::neon_cave, Command::west},
	{RoomID::blood_cave, Command::south},
	{RoomID::bat_cave, Command::north},
	{RoomID::teleport_cave, Command::west}, {RoomID::teleport_cave, Command::north}
};

Animate animates[to_value(AnimateID::COUNT)] = { // { room, strike }
	{RoomID::forest2, 4},
	{RoomID::horny_cave},
	{RoomID::neglected_cave, 6},
	{RoomID::gnu_cave},
	{RoomID::torture_cave},
	{RoomID::bat_cave},
	{RoomID::empty_cave45},
	{RoomID::talking_cave},
	{RoomID::open_space17},
	{RoomID::forest10},
	{RoomID::forest4},
	{RoomID::echo_cave},
	{RoomID::small_cave},
	{RoomID::lava_pit},
	{RoomID::vacuum_cave},
	{RoomID::r_cave},
	{RoomID::north_swamp},
	{RoomID::middle_swamp},
	{RoomID::south_swamp},
	{RoomID::mist_cave},
	{RoomID::teleport_cave}
};

Item items[to_value(ItemID::COUNT)] = { // { name, description, room, useable_on }
	{ "het hellehondvlees", L"Het is een goor stuk vlees dat naar kots ruikt.", AnimateID::barbecue },
	{ "het hittepak", L"Dit aluminiumkleurig pak beschermt je tegen grote hitte of kou.", RoomID::forest4 },
	{ "het groen kristal", L"Het is een helder, groengekleurd kristal. Even zie je een mysterieuze twinke-\nling", AnimateID::dragon_head },
	{ "het zwaard", L"Het is een magisch zwaard dat er niet al te sterk uit ziet, maar veel kracht\nuitstraalt. In het heft zit een paarse robijn.", RoomID::forest5 },
	{ "het bot", L"Het is een menselijk, verbleekt dijbeen, dat er sterk uit ziet. Je kunt er veel\nkracht mee zetten.", RoomID::swamp_path, AnimateID::door },
	{ "de diskette", L"Het is een grijze 3,5 inch diskette van het merk 'Spirits' met daarop waar-\nschijnlijk belangrijke data.", RoomID::slime_cave, AnimateID::computer },
	{ "de hasj", L"Het is een zakje met spul dat lijkt op tabak.", RoomID::drugs_cave, AnimateID::barbecue },
	{ "het rood kristal", L"Het is een helder, roodgekleurd kristal. Even zie je een mysterieuze twinke-\nling.", AnimateID::dragon_head },
	{ "de slaapmuts", L"Het is een Mickey Mouse-slaapmuts met vrolijke kleuren.", RoomID::straitjacket_cave, AnimateID::dragon },
	{ "de noekietronenbom", L"De bom bestaat uit een aantal dunne buizen in een cilinder. Daaromheen zitten\neen aantal slangetjes. Er klinkt een vreemd gebrom dat uit een rooster komt. Er\nzit een bordje op: -5° - 105°, Codenaam: R136.", RoomID::main_cave, AnimateID::lava },
	{ "de zaklamp", L"Het is een zwarte, aluminium zaklamp met een halogeenlampje erin.", RoomID::fluorescent_cave, combines_with(ItemID::batteries) },
	{ "het verband", L"Het is een witte doos met een rood kruis waarin wat verband en een paar pleis-\nters zitten.", RoomID::tentacle_cave },
	{ "de vlammenwerper", L"De vlammenwerper bestaat uit een pijp, een zuur- en een brandstoffles en een\nactivatieknop. Uit de pijp komt een klein waakvlammetje.", RoomID::garbage_cave, AnimateID::tree },
	{ "het kookboek", L"Het is een oud, vergeeld kookboek met daarin een koekjesrecept. Er staat:\n'Pak wat hellehond en wat hasj, en gooi het in de barbecue'.\nDat is alles.", RoomID::food_cave },
	{ "de tnt", L"De T.N.T. is een bosje rode staven met een velletje waarop staat: 'Pas op!\nSchokgevoelig!'", RoomID::empty_cave51 },
	{ "het mosterdgaspatroon", L"Het is een patroon dat mosterdgas onder druk bevat. Er zitten draadjes aan, en\nje kunt niets vinden om hem te activeren.", combines_with(ItemID::ignition) },
	{ "het giftige vlees", L"Het is een stuk vlees dat er op zich lekker uit ziet, maar een paar groene\nvlekken heeft. Er zit een dode mier op.", RoomID::safe_cave, AnimateID::gnu },
	{ "de ontsteking", L"De ontsteking is een kastje met een T-vormige hendel erop.", RoomID::scooby_cave, combines_with(ItemID::gas_capsule) },
	{ "het pakje batterijen", L"Het is een pakketje met penlights. Konijntjes kunnen er uren mee trommelen.", RoomID::radioactive_cave, combines_with(ItemID::flashlight) },
	{ "het gasmasker", L"Het is een groen masker met een rond filter en 2 plastic ooggaten.", RoomID::i_cave },
	{ "het papier", L"Het is een geel vel papier met gekrulde hoeken. Het handschrift is bijna on-\nleesbaar, en met moeite ontcijfer je: 'Voed de drakekop met de 3 gekleurde\nkristallen'." },
	{ "het boekje", L"Het is een vies, kleverig boekje met op de voorkant een ontklede trol. Je\nkrijgt kotsneigingen.", RoomID::damnation_cave, AnimateID::red_troll },
	{ "het blauw kristal", L"Het is een helder, blauwgekleurd kristal. Even zie je een mysterieuze twinke-\nling.", RoomID::red_cave, AnimateID::dragon_head },
	{ "het koekje", L"Het is een rond koekje dat naar ammoniak stinkt.", AnimateID::dragon },
	{ "de mosterdgasgranaat", L"Door het indrukken van de hendel kan het mosterdgas ontstnappen.", AnimateID::swelling }
};

template <typename TKey, class TValue>
void fill_map(std::map<TKey, TValue> map, TValue values[], int value_count)
{
	bool is_entity = std::is_base_of<Entity<TKey>, TValue>::value;

	for (int i = 0; i < value_count; i++) 
	{
		TKey id = static_cast<TKey>(i);

		if (is_entity) 
		{
			((TEntity<TKey>)values[i]).id = id;
		}

		map.emplace( = values[i];
	}

}

bool initialize(CoreData& core)
{
	core.paperroute = { RoomID::capital_p_cave, RoomID::a_cave, RoomID::p_cave, RoomID::i_cave, RoomID::e_cave, RoomID::r_cave };

	core.status.current_room = RoomID::forest0;
	core.status.paper_route_pos = 0;
	core.status.life_points = max_life_points;
	core.status.is_lamp_on = false;
	core.status.lamp_points = max_lamp_points;
	core.status.has_tree_burned = false;

	clear_window();

	srand((int)time(NULL));

	return set_room_connections(rooms);

	fill_map(core.animates, animates, to_value(AnimateID::COUNT));
	fill_map(core.items, items, to_value(ItemID::COUNT));
	fill_map(core.rooms, rooms, to_value(RoomID::COUNT));
}

bool set_room_connections(Room* rooms)
{
	// Interconnect rooms with neighbours
	for (int i = 0; i < to_value(RoomID::COUNT); i++)
	{
		Room& room = rooms[i];
		room.connections.set(Command::east, static_cast<RoomID>(i + 1));
		room.connections.set(Command::west, static_cast<RoomID>(i - 1));
		room.connections.set(Command::north, static_cast<RoomID>(i - 5));
		room.connections.set(Command::south, static_cast<RoomID>(i + 5));
	}

	// Seperate layers
	for (int i = 0; i < to_value(RoomID::COUNT); i += 20)
	{
		for (int j = 0; j < 16; j += 5)
		{
			rooms[i + j + 4].connections.erase(Command::east);
			rooms[i + j].connections.erase(Command::west);
		}

		for (int j = 0; j < 5; j++)
		{
			rooms[i + j].connections.erase(Command::north);
			rooms[i + j + 15].connections.erase(Command::south);
		}
	}

	// Connect layers
	for (auto &connection : level_connections)
		rooms[to_value(connection.from)].connections.set(connection.direction, connection.to);
	
	// Blocked routes
	for (auto &block : blocked_connections)
		rooms[to_value(block.room)].connections.erase(block.direction);

	return true;
}


