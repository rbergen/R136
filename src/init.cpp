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
	{ ROOM_BEGRAAFPLAATS, Command::kDown, ROOM_KAKTUSGROT },
	{ ROOM_RUINE, Command::kDown, ROOM_ZWARTEGROT },
	{ ROOM_ZWARTEGROT, Command::kUp, ROOM_RUINE },
	{ ROOM_HIEROGLIEFENGROT, Command::kDown, ROOM_PRATENDEGROT },
	{ ROOM_STORMGROT, Command::kDown, ROOM_OGENGROT },
	{ ROOM_WENTELTRAPGROT1, Command::kDown, ROOM_WENTELTRAPGROT2 },
	{ ROOM_OGENGROT, Command::kUp, ROOM_STORMGROT },
	{ ROOM_WENTELTRAPGROT2, Command::kUp, ROOM_WENTELTRAPGROT1 },
	{ ROOM_WENTELTRAPGROT2, Command::kDown, ROOM_WENTELTRAPGROT3 },
	{ ROOM_PRATENDEGROT, Command::kUp, ROOM_HIEROGLIEFENGROT },
	{ ROOM_WENTELTRAPGROT3, Command::kUp, ROOM_WENTELTRAPGROT2 }
};

#define BLOCKED_COUNT		83
#define BLOCKED_ROOM		0
#define BLOCKED_DIRECTION	1

BlockedConnection blocked[BLOCKED_COUNT] = { // { room, direction }
	{ROOM_NOORDMOERAS, Command::kWest}, {ROOM_NOORDMOERAS, Command::kEast}, {ROOM_NOORDMOERAS, Command::kSouth}, 
	{ROOM_MIDDENMOERAS, Command::kWest}, {ROOM_MIDDENMOERAS, Command::kEast}, {ROOM_MIDDENMOERAS, Command::kNorth}, {ROOM_MIDDENMOERAS, Command::kSouth}, 
	{ROOM_BOS5, Command::kEast},							  
	{ROOM_BEGRAAFPLAATS, Command::kWest}, 
	{ROOM_BOS11, Command::kEast}, 
	{ROOM_OPENPLEK12, Command::kWest}, 
	{ROOM_ZUIDMOERAS, Command::kWest}, {ROOM_ZUIDMOERAS, Command::kEast}, {ROOM_ZUIDMOERAS, Command::kNorth}, 
	{ROOM_RUINE, Command::kWest}, 
	{ROOM_SLIJMGROT, Command::kEast},
	{ROOM_ZWARTEGROT, Command::kWest}, 
	{ROOM_DRUGSGROT, Command::kEast}, {ROOM_DRUGSGROT, Command::kSouth}, 
	{ROOM_GEILEGROT, Command::kWest}, {ROOM_GEILEGROT, Command::kEast}, 
	{ROOM_DWANGBUISGROT, Command::kWest}, 
	{ROOM_VERWAARLOOSDEGROT, Command::kEast}, {ROOM_VERWAARLOOSDEGROT, Command::kNorth}, 
	{ROOM_LEGEGROT26, Command::kWest}, {ROOM_LEGEGROT26, Command::kEast}, 
	{ROOM_HOOFDGROT, Command::kEast}, {ROOM_HOOFDGROT, Command::kWest}, {ROOM_HOOFDGROT, Command::kNorth}, 
	{ROOM_HIEROGLIEFENGROT, Command::kWest}, 
	{ROOM_TLGROT, Command::kSouth},
	{ROOM_KLEINEGROT, Command::kNorth}, 
	{ROOM_IJSGROT, Command::kEast},
	{ROOM_KAKTUSGROT, Command::kWest}, {ROOM_KAKTUSGROT, Command::kSouth},
	{ROOM_STORMGROT, Command::kNorth}, 							  
	{ROOM_MISTGROT, Command::kWest}, {ROOM_MISTGROT, Command::kNorth}, {ROOM_MISTGROT, Command::kEast},
	{ROOM_TENTAKELGROT, Command::kNorth},
	{ROOM_VUILNISGROT, Command::kEast}, 
	{ROOM_ECHOGROT, Command::kWest}, {ROOM_ECHOGROT, Command::kEast},
	{ROOM_GEHEIMEGROT, Command::kWest}, {ROOM_GEHEIMEGROT, Command::kEast},
	{ROOM_VOEDSELGROT, Command::kWest}, {ROOM_VOEDSELGROT, Command::kEast},
	{ROOM_GNOEGROT, Command::kWest},
	{ROOM_LEGEGROT45, Command::kNorth}, 
	{ROOM_OGENGROT, Command::kEast}, 
	{ROOM_ROTSGROT, Command::kWest}, 
	{ROOM_LEEGTE, Command::kSouth}, 
	{ROOM_VEILIGEGROT, Command::kEast}, {ROOM_VEILIGEGROT, Command::kSouth},
	{ROOM_NAUWEROTSSPLEET, Command::kNorth}, {ROOM_NAUWEROTSSPLEET, Command::kEast}, {ROOM_NAUWEROTSSPLEET, Command::kSouth},
	{ROOM_OLIEGROT, Command::kWest},
	{ROOM_LEGEGROT55, Command::kEast}, 
	{ROOM_WENTELTRAPGROT2, Command::kWest}, 
	{ROOM_SPINNENGROT, Command::kNorth},
	{ROOM_PRATENDEGROT, Command::kEast}, 
	{ROOM_LAVAPUT, Command::kWest}, 
	{ROOM_SKOEBIEGROT, Command::kEast},
	{ROOM_RADIOACTIEVEGROT, Command::kWest}, {ROOM_RADIOACTIEVEGROT, Command::kSouth},
	{ROOM_DODENGROT, Command::kSouth},
	{ROOM_RGROT, Command::kNorth},	{ROOM_RGROT, Command::kSouth},
	{ROOM_EGROT, Command::kSouth},
	{ROOM_VERDOEMENISGROT, Command::kNorth}, {ROOM_VERDOEMENISGROT, Command::kEast},
	{ROOM_VACUUMGROT, Command::kWest}, {ROOM_VACUUMGROT, Command::kNorth}, {ROOM_VACUUMGROT, Command::kEast},
	{ROOM_RODEGROT, Command::kWest}, {ROOM_RODEGROT, Command::kNorth}, {ROOM_RODEGROT, Command::kEast},
	{ROOM_NEONGROT, Command::kWest}, 
	{ROOM_BLOEDGROT, Command::kSouth}, 
	{ROOM_VLEERMUISGROT, Command::kNorth}, 
	{ROOM_TELEPORTGROT, Command::kWest}, {ROOM_TELEPORTGROT, Command::kNorth}
};

Living living[to_underlying(AnimateID::COUNT)] = { // { room, strike }
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

Item items[ITEM_COUNT] = { // { name, descript, room, useableon }
	{ "het hellehondvlees", L"Het is een goor stuk vlees dat naar kots ruikt.", kUndefined, AnimateID::kBarbecue },
	{ "het hittepak", L"Dit aluminiumkleurig pak beschermt je tegen grote hitte of kou.", ROOM_BOS4, AnimateID::kUndefined },
	{ "het groen kristal", L"Het is een helder, groengekleurd kristal. Even zie je een mysterieuze twinke-\nling", kUndefined, AnimateID::kDragonHead },
	{ "het zwaard", L"Het is een magisch zwaard dat er niet al te sterk uit ziet, maar veel kracht\nuitstraalt. In het heft zit een paarse robijn.", ROOM_BOS5, AnimateID::kUndefined },
	{ "het bot", L"Het is een menselijk, verbleekt dijbeen, dat er sterk uit ziet. Je kunt er veel\nkracht mee zetten.", ROOM_MOERASPAD, AnimateID::kDoor },
	{ "de diskette", L"Het is een grijze 3,5 inch diskette van het merk 'Spirits' met daarop waar-\nschijnlijk belangrijke data.", ROOM_SLIJMGROT, AnimateID::kComputer },
	{ "de hasj", L"Het is een zakje met spul dat lijkt op tabak.", ROOM_DRUGSGROT, AnimateID::kBarbecue },
	{ "het rood kristal", L"Het is een helder, roodgekleurd kristal. Even zie je een mysterieuze twinke-\nling.", kUndefined, AnimateID::kDragonHead },
	{ "de slaapmuts", L"Het is een Mickey Mouse-slaapmuts met vrolijke kleuren.", ROOM_DWANGBUISGROT, AnimateID::kDragon },
	{ "de noekietronenbom", L"De bom bestaat uit een aantal dunne buizen in een cilinder. Daaromheen zitten\neen aantal slangetjes. Er klinkt een vreemd gebrom dat uit een rooster komt. Er\nzit een bordje op: -5° - 105°, Codenaam: R136.", ROOM_HOOFDGROT, AnimateID::kLava },
	{ "de zaklamp", L"Het is een zwarte, aluminium zaklamp met een halogeenlampje erin.", ROOM_TLGROT, connectToItem(ITEM_BATTERIJEN) },
	{ "het verband", L"Het is een witte doos met een rood kruis waarin wat verband en een paar pleis-\nters zitten.", ROOM_TENTAKELGROT, AnimateID::kUndefined },
	{ "de vlammenwerper", L"De vlammenwerper bestaat uit een pijp, een zuur- en een brandstoffles en een\nactivatieknop. Uit de pijp komt een klein waakvlammetje.", ROOM_VUILNISGROT, AnimateID::kTree },
	{ "het kookboek", L"Het is een oud, vergeeld kookboek met daarin een koekjesrecept. Er staat:\n'Pak wat hellehond en wat hasj, en gooi het in de barbecue'.\nDat is alles.", ROOM_VOEDSELGROT, AnimateID::kUndefined },
	{ "de tnt", L"De T.N.T. is een bosje rode staven met een velletje waarop staat: 'Pas op!\nSchokgevoelig!'", ROOM_LEGEGROT51, AnimateID::kUndefined },
	{ "het mosterdgaspatroon", L"Het is een patroon dat mosterdgas onder druk bevat. Er zitten draadjes aan, en\nje kunt niets vinden om hem te activeren.", kUndefined, connectToItem(ITEM_ONTSTEKING) },
	{ "het giftige vlees", L"Het is een stuk vlees dat er op zich lekker uit ziet, maar een paar groene\nvlekken heeft. Er zit een dode mier op.", ROOM_VEILIGEGROT, AnimateID::kGnu },
	{ "de ontsteking", L"De ontsteking is een kastje met een T-vormige hendel erop.", ROOM_SKOEBIEGROT, connectToItem(ITEM_GASPATROON) },
	{ "het pakje batterijen", L"Het is een pakketje met penlights. Konijntjes kunnen er uren mee trommelen.", ROOM_RADIOACTIEVEGROT, connectToItem(ITEM_ZAKLAMP) },
	{ "het gasmasker", L"Het is een groen masker met een rond filter en 2 plastic ooggaten.", ROOM_IGROT, AnimateID::kUndefined },
	{ "het papier", L"Het is een geel vel papier met gekrulde hoeken. Het handschrift is bijna on-\nleesbaar, en met moeite ontcijfer je: 'Voed de drakekop met de 3 gekleurde\nkristallen'.", kUndefined, AnimateID::kUndefined },
	{ "het boekje", L"Het is een vies, kleverig boekje met op de voorkant een ontklede trol. Je\nkrijgt kotsneigingen.", ROOM_VERDOEMENISGROT, AnimateID::kRedTroll },
	{ "het blauw kristal", L"Het is een helder, blauwgekleurd kristal. Even zie je een mysterieuze twinke-\nling.", ROOM_RODEGROT, AnimateID::kDragonHead },
	{ "het koekje", L"Het is een rond koekje dat naar ammoniak stinkt.", kUndefined, AnimateID::kDragon },
	{ "de mosterdgasgranaat", L"Door het indrukken van de hendel kan het mosterdgas ontstnappen.", kUndefined, AnimateID::kSwelling }
};

char paperroute[PAPERROUTE_LENGTH] = { ROOM_HOOFDLETTERPGROT, ROOM_AGROT, ROOM_PGROT, ROOM_IGROT, ROOM_EGROT, ROOM_RGROT };

bool Initialize(Progdata& progdata)
{
	int i;

	progdata.paperroute = paperroute;

	progdata.status.curroom = ROOM_BOS0;
	progdata.status.paperpos = 0;
	progdata.status.lifepoints = MAX_LIFEPOINTS;
	progdata.status.lamp = false;
	progdata.status.lamppoints = 60;

	ClearWindow();

	srand((int)time(NULL));

	for (i = 0; i < 10; i++)
		progdata.owneditems[i] = -1;

	progdata.rooms = rooms;
	progdata.living = living;
	progdata.items = items;

	return SetRoomConnections(progdata.rooms);
}

bool SetRoomConnections(Room *rooms)
{
	int i;
	int j;

	// Interconnect rooms with neighbours
	for (i = 0; i < ROOM_COUNT; i++)
	{
		rooms[i].connect[kEast] = i + 1;
		rooms[i].connect[kWest] = i - 1;
		rooms[i].connect[kNorth] = i - 5;
		rooms[i].connect[kSouth] = i + 5;
		rooms[i].connect[kUp] = rooms[i].connect[kDown] = kUndefined;
	}

	// Seperate layers
	for (i = 0; i < ROOM_COUNT; i += 20)
	{
		for (j = 0; j < 16; j += 5)
		{
			rooms[i + j + 4].connect[to_underlying(Command::kEast)] = kUndefined;
			rooms[i + j].connect[to_underlying(Command::kWest)] = kUndefined;
		}

		for (j = 0; j < 5; j++)
		{
			rooms[i + j].connect[to_underlying(Command::kNorth)] = kUndefined;
			rooms[i + j + 15].connect[to_underlying(Command::kSouth)] = kUndefined;
		}
	}

	// Connect layers
	for (i = 0; i < LEVELCON_COUNT; i++)
		rooms[level_connections[i][LEVELCON_FROMROOM]].connect[level_connections[i][LEVELCON_DIRECTION]] = level_connections[i][LEVELCON_TOROOM];
	
	// Blocked routes
	for (i = 0; i < BLOCKED_COUNT; i++)
		rooms[blocked[i][BLOCKED_ROOM]].connect[blocked[i][BLOCKED_DIRECTION]] = kUndefined;

	return true;
}


