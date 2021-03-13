#include "r136.h"
#include <time.h>



Room rooms[ROOM_COUNT] = { // { name, descript }
	{ L"in het bos",					L"Je bevindt je in een uithoek van een donker bos. Overal hoor je enge geluiden." },
	{ L"in het bos",					L"Aan de zuidkant zie je een hek dat toegang geeft tot een donkere plaats." },
	{ L"in het bos", 					L"Er komt een modderige geur uit het oosten." },
	{ L"in het moeras",					L"Er hangt een griezelige nevel over het stinkende oppervlak."},
	{ L"in het bos",					L"Er komt een modderige geur uit het westen." },
	{ L"in het bos",					L"Pas op voor de laaghangende takken!" },
	{ L"op de begraafplaats",			L"Een lucht van rottend vlees dringt in je neus. Je denkt dat je een grafsteen\nziet bewegen." },
	{ L"in het bos" },
	{ L"in het moeras",					L"Er hangt een griezelige nevel over het stinkende oppervlak." },
	{ L"op een open plek",				L"Er komt een modderige geur uit het westen." },
	{ L"in het bos" },
	{ L"in het bos",					L"Je trapt bijna in een bereklem." },
	{ L"op een open plek",				L"Door de mist zie je nog net de omtrekken van het donkere bos." },
	{ L"op het moeraspad",				L"Er ligt hier een skelet, waarschijnlijk een van je voorgangers." },
	{ L"op een open plek",				L"Bij het licht van een halve maan onderscheid je nog net de vorm van een galg." },
	{ L"in het bos",					L"In de verte hoor je het trieste gehuil van een weerwolf." },
	{ L"in het bos" },
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

#define LEVELCON_COUNT		11
#define LEVELCON_FROMROOM	0
#define LEVELCON_DIRECTION	1
#define LEVELCON_TOROOM		2

LevelConnection level_connections[LEVELCON_COUNT] = { // { fromroom, direction, toroom }
	{ ROOM_BEGRAAFPLAATS, Command::down, ROOM_KAKTUSGROT },
	{ ROOM_RUINE, Command::down, ROOM_ZWARTEGROT },
	{ ROOM_ZWARTEGROT, Command::up, ROOM_RUINE },
	{ ROOM_HIEROGLIEFENGROT, Command::down, ROOM_PRATENDEGROT },
	{ ROOM_STORMGROT, Command::down, ROOM_OGENGROT },
	{ ROOM_WENTELTRAPGROT1, Command::down, ROOM_WENTELTRAPGROT2 },
	{ ROOM_OGENGROT, Command::up, ROOM_STORMGROT },
	{ ROOM_WENTELTRAPGROT2, Command::up, ROOM_WENTELTRAPGROT1 },
	{ ROOM_WENTELTRAPGROT2, Command::down, ROOM_WENTELTRAPGROT3 },
	{ ROOM_PRATENDEGROT, Command::up, ROOM_HIEROGLIEFENGROT },
	{ ROOM_WENTELTRAPGROT3, Command::up, ROOM_WENTELTRAPGROT2 }
};

#define BLOCKED_COUNT		83
#define BLOCKED_ROOM		0
#define BLOCKED_DIRECTION	1

BlockedConnection blocked[BLOCKED_COUNT] = { // { room, direction }
	{ROOM_NOORDMOERAS, Command::west}, {ROOM_NOORDMOERAS, Command::east}, {ROOM_NOORDMOERAS, Command::south}, 
	{ROOM_MIDDENMOERAS, Command::west}, {ROOM_MIDDENMOERAS, Command::east}, {ROOM_MIDDENMOERAS, Command::north}, {ROOM_MIDDENMOERAS, Command::south}, 
	{ROOM_BOS5, Command::east},							  
	{ROOM_BEGRAAFPLAATS, Command::west}, 
	{ROOM_BOS11, Command::east}, 
	{ROOM_OPENPLEK12, Command::west}, 
	{ROOM_ZUIDMOERAS, Command::west}, {ROOM_ZUIDMOERAS, Command::east}, {ROOM_ZUIDMOERAS, Command::north}, 
	{ROOM_RUINE, Command::west}, 
	{ROOM_SLIJMGROT, Command::east},
	{ROOM_ZWARTEGROT, Command::west}, 
	{ROOM_DRUGSGROT, Command::east}, {ROOM_DRUGSGROT, Command::south}, 
	{ROOM_GEILEGROT, Command::west}, {ROOM_GEILEGROT, Command::east}, 
	{ROOM_DWANGBUISGROT, Command::west}, 
	{ROOM_VERWAARLOOSDEGROT, Command::east}, {ROOM_VERWAARLOOSDEGROT, Command::north}, 
	{ROOM_LEGEGROT26, Command::west}, {ROOM_LEGEGROT26, Command::east}, 
	{ROOM_HOOFDGROT, Command::east}, {ROOM_HOOFDGROT, Command::west}, {ROOM_HOOFDGROT, Command::north}, 
	{ROOM_HIEROGLIEFENGROT, Command::west}, 
	{ROOM_TLGROT, Command::south},
	{ROOM_KLEINEGROT, Command::north}, 
	{ROOM_IJSGROT, Command::east},
	{ROOM_KAKTUSGROT, Command::west}, {ROOM_KAKTUSGROT, Command::south},
	{ROOM_STORMGROT, Command::north}, 							  
	{ROOM_MISTGROT, Command::west}, {ROOM_MISTGROT, Command::north}, {ROOM_MISTGROT, Command::east},
	{ROOM_TENTAKELGROT, Command::north},
	{ROOM_VUILNISGROT, Command::east}, 
	{ROOM_ECHOGROT, Command::west}, {ROOM_ECHOGROT, Command::east},
	{ROOM_GEHEIMEGROT, Command::west}, {ROOM_GEHEIMEGROT, Command::east},
	{ROOM_VOEDSELGROT, Command::west}, {ROOM_VOEDSELGROT, Command::east},
	{ROOM_GNOEGROT, Command::west},
	{ROOM_LEGEGROT45, Command::north}, 
	{ROOM_OGENGROT, Command::east}, 
	{ROOM_ROTSGROT, Command::west}, 
	{ROOM_LEEGTE, Command::south}, 
	{ROOM_VEILIGEGROT, Command::east}, {ROOM_VEILIGEGROT, Command::south},
	{ROOM_NAUWEROTSSPLEET, Command::north}, {ROOM_NAUWEROTSSPLEET, Command::east}, {ROOM_NAUWEROTSSPLEET, Command::south},
	{ROOM_OLIEGROT, Command::west},
	{ROOM_LEGEGROT55, Command::east}, 
	{ROOM_WENTELTRAPGROT2, Command::west}, 
	{ROOM_SPINNENGROT, Command::north},
	{ROOM_PRATENDEGROT, Command::east}, 
	{ROOM_LAVAPUT, Command::west}, 
	{ROOM_SKOEBIEGROT, Command::east},
	{ROOM_RADIOACTIEVEGROT, Command::west}, {ROOM_RADIOACTIEVEGROT, Command::south},
	{ROOM_DODENGROT, Command::south},
	{ROOM_RGROT, Command::north},	{ROOM_RGROT, Command::south},
	{ROOM_EGROT, Command::south},
	{ROOM_VERDOEMENISGROT, Command::north}, {ROOM_VERDOEMENISGROT, Command::east},
	{ROOM_VACUUMGROT, Command::west}, {ROOM_VACUUMGROT, Command::north}, {ROOM_VACUUMGROT, Command::east},
	{ROOM_RODEGROT, Command::west}, {ROOM_RODEGROT, Command::north}, {ROOM_RODEGROT, Command::east},
	{ROOM_NEONGROT, Command::west}, 
	{ROOM_BLOEDGROT, Command::south}, 
	{ROOM_VLEERMUISGROT, Command::north}, 
	{ROOM_TELEPORTGROT, Command::west}, {ROOM_TELEPORTGROT, Command::north}
};

Animate animates[to_value(AnimateID::COUNT)] = { // { room, strike }
	{ROOM_BOS2, 4}, 
	{ROOM_GEILEGROT}, 
	{ROOM_VERWAARLOOSDEGROT, 6}, 
	{ROOM_GNOEGROT}, 
	{ROOM_MARTELGROT}, 
	{ROOM_VLEERMUISGROT}, 
	{ROOM_LEGEGROT45}, 
	{ROOM_PRATENDEGROT}, 
	{ROOM_OPENPLEK17}, 
	{ROOM_BOS10}, 
	{ROOM_BOS4}, 
	{ROOM_ECHOGROT}, 
	{ROOM_KLEINEGROT}, 
	{ROOM_LAVAPUT}, 
	{ROOM_VACUUMGROT}, 
	{ROOM_RGROT}, 
	{ROOM_NOORDMOERAS}, 
	{ROOM_MIDDENMOERAS}, 
	{ROOM_ZUIDMOERAS}, 
	{ROOM_MISTGROT}, 
	{ROOM_TELEPORTGROT} 
};

Item items[to_value(ItemID::COUNT)] = { // { name, descript, room, useableon }
	{ "het hellehondvlees", L"Het is een goor stuk vlees dat naar kots ruikt.", undefined, AnimateID::barbecue },
	{ "het hittepak", L"Dit aluminiumkleurig pak beschermt je tegen grote hitte of kou.", ROOM_BOS4, AnimateID::undefined },
	{ "het groen kristal", L"Het is een helder, groengekleurd kristal. Even zie je een mysterieuze twinke-\nling", undefined, AnimateID::dragon_head },
	{ "het zwaard", L"Het is een magisch zwaard dat er niet al te sterk uit ziet, maar veel kracht\nuitstraalt. In het heft zit een paarse robijn.", ROOM_BOS5, AnimateID::undefined },
	{ "het bot", L"Het is een menselijk, verbleekt dijbeen, dat er sterk uit ziet. Je kunt er veel\nkracht mee zetten.", ROOM_MOERASPAD, AnimateID::door },
	{ "de diskette", L"Het is een grijze 3,5 inch diskette van het merk 'Spirits' met daarop waar-\nschijnlijk belangrijke data.", ROOM_SLIJMGROT, AnimateID::computer },
	{ "de hasj", L"Het is een zakje met spul dat lijkt op tabak.", ROOM_DRUGSGROT, AnimateID::barbecue },
	{ "het rood kristal", L"Het is een helder, roodgekleurd kristal. Even zie je een mysterieuze twinke-\nling.", undefined, AnimateID::dragon_head },
	{ "de slaapmuts", L"Het is een Mickey Mouse-slaapmuts met vrolijke kleuren.", ROOM_DWANGBUISGROT, AnimateID::dragon },
	{ "de noekietronenbom", L"De bom bestaat uit een aantal dunne buizen in een cilinder. Daaromheen zitten\neen aantal slangetjes. Er klinkt een vreemd gebrom dat uit een rooster komt. Er\nzit een bordje op: -5° - 105°, Codenaam: R136.", ROOM_HOOFDGROT, AnimateID::lava },
	{ "de zaklamp", L"Het is een zwarte, aluminium zaklamp met een halogeenlampje erin.", ROOM_TLGROT, connectToItem(ItemID::batteries) },
	{ "het verband", L"Het is een witte doos met een rood kruis waarin wat verband en een paar pleis-\nters zitten.", ROOM_TENTAKELGROT, AnimateID::undefined },
	{ "de vlammenwerper", L"De vlammenwerper bestaat uit een pijp, een zuur- en een brandstoffles en een\nactivatieknop. Uit de pijp komt een klein waakvlammetje.", ROOM_VUILNISGROT, AnimateID::tree },
	{ "het kookboek", L"Het is een oud, vergeeld kookboek met daarin een koekjesrecept. Er staat:\n'Pak wat hellehond en wat hasj, en gooi het in de barbecue'.\nDat is alles.", ROOM_VOEDSELGROT, AnimateID::undefined },
	{ "de tnt", L"De T.N.T. is een bosje rode staven met een velletje waarop staat: 'Pas op!\nSchokgevoelig!'", ROOM_LEGEGROT51, AnimateID::undefined },
	{ "het mosterdgaspatroon", L"Het is een patroon dat mosterdgas onder druk bevat. Er zitten draadjes aan, en\nje kunt niets vinden om hem te activeren.", undefined, connectToItem(ItemID::ignition) },
	{ "het giftige vlees", L"Het is een stuk vlees dat er op zich lekker uit ziet, maar een paar groene\nvlekken heeft. Er zit een dode mier op.", ROOM_VEILIGEGROT, AnimateID::gnu },
	{ "de ontsteking", L"De ontsteking is een kastje met een T-vormige hendel erop.", ROOM_SKOEBIEGROT, connectToItem(ItemID::gas_capsule) },
	{ "het pakje batterijen", L"Het is een pakketje met penlights. Konijntjes kunnen er uren mee trommelen.", ROOM_RADIOACTIEVEGROT, connectToItem(ItemID::flashlight) },
	{ "het gasmasker", L"Het is een groen masker met een rond filter en 2 plastic ooggaten.", ROOM_IGROT, AnimateID::undefined },
	{ "het papier", L"Het is een geel vel papier met gekrulde hoeken. Het handschrift is bijna on-\nleesbaar, en met moeite ontcijfer je: 'Voed de drakekop met de 3 gekleurde\nkristallen'.", undefined, AnimateID::undefined },
	{ "het boekje", L"Het is een vies, kleverig boekje met op de voorkant een ontklede trol. Je\nkrijgt kotsneigingen.", ROOM_VERDOEMENISGROT, AnimateID::red_troll },
	{ "het blauw kristal", L"Het is een helder, blauwgekleurd kristal. Even zie je een mysterieuze twinke-\nling.", ROOM_RODEGROT, AnimateID::dragon_head },
	{ "het koekje", L"Het is een rond koekje dat naar ammoniak stinkt.", undefined, AnimateID::dragon },
	{ "de mosterdgasgranaat", L"Door het indrukken van de hendel kan het mosterdgas ontstnappen.", undefined, AnimateID::swelling }
};

char paperroute[paper_route_length] = { ROOM_HOOFDLETTERPGROT, ROOM_AGROT, ROOM_PGROT, ROOM_IGROT, ROOM_EGROT, ROOM_RGROT };

template <typename TKey, typename TValue>
void fill_map(std::map<TKey, TValue> map, TValue values[], int value_count)
{
	for (int i = 0; i < value_count; i++)
		map[static_cast<TKey>(i)] = values[i];
}

bool Initialize(Progdata& progdata)
{
	int i;

	progdata.paperroute = paperroute;

	progdata.status.curroom = ROOM_BOS0;
	progdata.status.paperpos = 0;
	progdata.status.lifepoints = max_life_points;
	progdata.status.lamp = false;
	progdata.status.lamppoints = 60;

	clear_window();

	srand((int)time(NULL));

	for (i = 0; i < 10; i++)
		progdata.owneditems[i] = -1;

	progdata.rooms = rooms;
	fill_map(progdata.animates, animates, to_value(AnimateID::COUNT));
	fill_map(progdata.items, items, to_value(ItemID::COUNT));

	return SetRoomConnections(progdata.rooms);
}

bool SetRoomConnections(Room *rooms)
{
	int i;
	int j;

	// Interconnect rooms with neighbours
	for (i = 0; i < ROOM_COUNT; i++)
	{
		rooms[i].connect[to_value(Command::east)] = i + 1;
		rooms[i].connect[to_value(Command::west)] = i - 1;
		rooms[i].connect[to_value(Command::north)] = i - 5;
		rooms[i].connect[to_value(Command::south)] = i + 5;
		rooms[i].connect[to_value(Command::up)] = rooms[i].connect[to_value(Command::down)] = undefined;
	}

	// Seperate layers
	for (i = 0; i < ROOM_COUNT; i += 20)
	{
		for (j = 0; j < 16; j += 5)
		{
			rooms[i + j + 4].connect[to_value(Command::east)] = undefined;
			rooms[i + j].connect[to_value(Command::west)] = undefined;
		}

		for (j = 0; j < 5; j++)
		{
			rooms[i + j].connect[to_value(Command::north)] = undefined;
			rooms[i + j + 15].connect[to_value(Command::south)] = undefined;
		}
	}

	// Connect layers
	for (i = 0; i < LEVELCON_COUNT; i++)
		rooms[level_connections[i].from].connect[to_value(level_connections[i].direction)] = level_connections[i].to;
	
	// Blocked routes
	for (i = 0; i < BLOCKED_COUNT; i++)
		rooms[blocked[i].room].connect[to_value(blocked[i])] = undefined;

	return true;
}


