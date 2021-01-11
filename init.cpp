#include "include.h"
#include <time.h>

Room rooms[ROOM_COUNT] = { // { name, descript }
	{ "in het bos",				"Je bevindt je in een uithoek van een donker bos. Overal hoor je enge geluiden." },
	{ "in het bos",				"Aan de zuidkant zie je een hek dat toegang geeft tot een donkere plaats." },
	{ "in het bos", 			"Er komt een modderige geur uit het oosten." },
	{ "in het moeras",			"Er hangt een griezelige nevel over het stinkende oppervlak."},
	{ "in het bos",				"Er komt een modderige geur uit het westen." },
	{ "in het bos",				"Pas op voor de laaghangende takken!" },
	{ "op de begraafplaats",	"Een lucht van rottend vlees dringt in je neus. Je denkt dat je een grafsteen\r\nziet bewegen." },
	{ "in het bos" },
	{ "in het moeras",			"Er hangt een griezelige nevel over het stinkende oppervlak." },
	{ "op de open plek",		"Er komt een modderige geur uit het westen." },
	{ "in het bos" },
	{ "in het bos",				"Je trapt bijna in een bereklem." },
	{ "op de open plek",		"Door de mist zie je nog net de omtrekken van het donkere bos." },
	{ "op het moeraspad",		"Er ligt hier een skelet, waarschijnlijk een van je voorgangers." },
	{ "op de open plek",		"Bij het licht van een halve maan onderscheid je nog net de vorm van een galg." },
	{ "in het bos",				"In de verte hoor je het trieste gehuil van een weerwolf." },
	{ "in het bos" },
	{ "op de open plek",		"Er ligt hier een dood konijn dat wordt belaagd door vliegen." },
	{ "in het moeras",			"Er hangt een griezelige nevel over het stinkende oppervlak." },
	{ "in de ruïne",			"Je bevindt je in een spookachtige ruïne. Er is hier een wankele trap die naar\r\nbeneden leidt." },

	{ "in de slijmgrot",		"De wanden van deze grot zijn bekleed met een snotachtig slijm." },
	{ "in de zwarte grot",		"Je ziet geen hand voor ogen." },
	{ "in de drugsgrot" },
	{ "in de geile grot",		"Aan de muren hangen gelige, gescheurde Playboy-posters." },
	{ "in de dwangbuisgrot",	"Er hangt hier een dwangbuis, met daarin een verminkt lijk." },
	{ "in de verwaarloosde grot" },
	{ "in de lege grot" },
	{ "in de hoofdgrot",		"Er staat hier een batterij aan mysterieuze apparatuur." },
	{ "in de hiërogliefengrot", "Op de wanden staan hiërogliefen waar je geen wijs uit wordt." },
	{ "in de stankgrot",		"Er hangt hier een smerige lucht die je herinnert aan de zware lucht van een\r\nbeerput." },
	{ "in de troosteloze grot" },
	{ "in de TL-grot",			"De grot wordt zwak verlicht door een lichtbron die hoog aan het plafond hangt." },
	{ "in de kleine grot" },
	{ "in de ijsgrot",			"In deze grot lijkt het net of alles van ijs is, en je krijgt rillingen." },
	{ "in de kaktusgrot",		"Je bent omringd door giftige kaktussen die in deze grot staan." },
	{ "in de stalagmietengrot",	"Hier zie je een traliewerk van stalagmieten." },
	{ "in de stormgrot",		"Door deze grot loeit een harde wind, waardoor je je vast moet grijpen aan een\r\nvan de wanden." },
	{ "in de mistgrot",			"Een dichte mist belemmert je zicht, en je verliest je or‹entatiegevoel." },
	{ "in de wenteltrapgrot",	"In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\r\nandere niveaus leidt." },
	{ "in de tentakelgrot",		"Van alle kanten komen grote tentakels die je aftasten en groene sporen op je\r\nhuid achterlaten." },

	{ "in de vuilnisgrot",		"In deze grot ligt een grote stapel rottende etensresten. De stank is bijna on-\r\ndraaglijk." },
	{ "in de echogrot",			"Hier worden alle geluiden die je maakt tegen de wanden geëcho'd." },
	{ "in de geheime grot",		"Op de grond van deze grot liggen allerlei onbekende en geheimzinnige voorwer-\r\npen." },
	{ "in de voedselgrot",		"Zo te ruiken is dit waarschijnlijk eens een keuken geweest..." },
	{ "in de grot van de gnoe", "Hier liggen de geraamtes van wezens die eerder ten prooi zijn gevallen aan de\r\ngnoe." },
	{ "in een lege grot" },
	{ "in de ogengrot",			"Van alle kanten wordt je bespied door rode, bloeddoorlopen ogen die precies\r\nvolgen wat je doet."},
	{ "in de rotsgrot",			"Overal zie je hier scherpe rotspunten. Aan een aantal ervan zitten bruine kors-\r\nten."},
	{ "in de leegte" },
	{ "op de zandbank",			"Op de vloer liggen vreemde patronen, gevormd uit verschillende soorten zand."},
	{ "in de martelgrot",		"Onder de vage schemering van de martelvuren zie je nog net een duimschroef en\r\nwat stekelige voorwerpen waar nog wat bloed aan zit."},
	{ "in een lege grot" },
	{ "in de veilige grot",		"Dit is de enige grot waar je je een beetje veilig voelt."},
	{ "in de nauwe rotsspleet", "Aan alle kanten wordt je omringd door hoge rotsmuren. Alleen in het westen zie\r\nje een opening."},
	{ "in de oliegrot",			"Vanuit het zuiden verspreidt zich een enorme hitte, die in deze grot nog net\r\ndraaglijk is."},
	{ "in een lege grot" },
	{ "in een wenteltrapgrot",	"In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\r\nandere niveaus leidt."},
	{ "in de spinnengrot",		"Het wemelt hier van de tarantula's. Bij elke stap die je zet hoor je het onder\r\nje voeten kraken, en ze kruipen langs je benen omhoog."},
	{ "in de pratende grot" },
	{ "op de lavaput" },

	{ "in de skoebiegrot",			"Uit alle richtingen komen rare geluiden, als in een gesticht."},
	{ "in de radioactieve grot",	"Door de hoge radioactiviteit is deze grot zwak verlicht." },
	{ "in de i-grot" },
	{ "in de p-grot" },
	{ "in de a-grot",				"In deze grot bevindt zich het stenen beeld van een oud, jou onbekend wezen." },
	{ "in de dodengrot",			"De naam van deze grot spreekt voor zich..." },
	{ "in de r-grot" },
	{ "in de e-grot" },
	{ "in een wenteltrapgrot",		"In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\r\nandere niveaus leidt." },
	{ "in de P-grot" },
	{ "in de grot der verdoemenis", "In deze grot heerst een haast verstikkende sfeer, en je voelt je niet prettig." },
	{ "in de vacuumgrot" },
	{ "in de rode grot" },
	{ "in de neongrot",				"Deze grot is fel gekleurd. Er staan patronen die je doen denken aan zwarte ma-\r\ngie." },
	{ "in de bloedgrot",			"Het geraamte van een groot beest ligt hier op de grond en een aantal ingewanden\r\nliggen er naast." },
	{ "in de vleermuisgrot",		"In deze grot fladderen overal vleermuizen, op zoek naar hun prooi."},
	{ "in de slangengrot",			"Je hoort het geluid van een ratelslang. Bij de weg naar het noorden staat een\r\ndoodskop getekend, die een gevaar aanduidt." },
	{ "in de kwabbengrot" },
	{ "in de glibbergrot",			"Je glijdt bijna uit over de zeepachtige prut die overal in de grot ligt. Tus-\r\nsen de glibberige massa steekt een paal omhoog met daarop een pijl die naar\r\nhet oosten wijst." },
	{ "in de teleportgrot" }
};

#define LEVELCON_COUNT 11

char levelcon[LEVELCON_COUNT][3] = {{6, DO_DOWN, 34},
								{19, DO_DOWN, 21},
								{21, DO_UP, 19},
								{28, DO_DOWN, 58},
								{36, DO_DOWN, 46},
								{38, DO_DOWN, 56},
								{46, DO_UP, 36},
								{56, DO_UP, 38},
								{56, DO_DOWN, 68},
								{58, DO_UP, 28},
								{68, DO_UP, 56}};

#define BLOCKED_COUNT 83

char blocked[BLOCKED_COUNT][2] = {{3, DO_WEST}, {3, DO_EAST}, {3, DO_SOUTH}, {8, DO_WEST},
							  {8, DO_EAST}, {8, DO_NORTH}, {8, DO_SOUTH}, {5, DO_EAST},
							  {6, DO_WEST}, {11, DO_EAST}, {12, DO_WEST}, {18, DO_WEST},
							  {18, DO_EAST}, {18, DO_NORTH}, {19, DO_WEST}, {20, DO_EAST},
							  {21, DO_WEST}, {22, DO_EAST}, {22, DO_SOUTH}, {27, DO_NORTH},
							  {23, DO_WEST}, {23, DO_EAST}, {24, DO_WEST}, {25, DO_EAST},
							  {25, DO_NORTH}, {26, DO_WEST}, {26, DO_EAST}, {27, DO_EAST},
							  {27, DO_WEST}, {28, DO_WEST}, {32, DO_NORTH}, {33, DO_EAST},
							  {34, DO_WEST}, {31, DO_SOUTH}, {36, DO_NORTH}, {34, DO_SOUTH},
							  {37, DO_WEST}, {37, DO_NORTH}, {37, DO_EAST}, {39, DO_NORTH},
							  {40, DO_EAST}, {41, DO_WEST}, {41, DO_EAST}, {42, DO_WEST},
							  {42, DO_EAST}, {43, DO_WEST},  {43, DO_EAST}, {44, DO_WEST},
							  {45, DO_NORTH}, {46, DO_EAST}, {47, DO_WEST}, {52, DO_EAST},
							  {48, DO_SOUTH}, {53, DO_NORTH}, {53, DO_EAST}, {54, DO_WEST},
							  {55, DO_EAST}, {56, DO_WEST}, {52, DO_SOUTH}, {57, DO_NORTH},
							  {53, DO_SOUTH}, {58, DO_EAST}, {59, DO_WEST}, {60, DO_EAST},
							  {61, DO_WEST}, {61, DO_SOUTH}, {66, DO_NORTH}, {65, DO_SOUTH},
							  {70, DO_NORTH}, {70, DO_EAST}, {71, DO_WEST}, {66, DO_SOUTH},
							  {71, DO_NORTH}, {71, DO_EAST}, {72, DO_WEST}, {67, DO_SOUTH},
							  {72, DO_NORTH}, {72, DO_EAST}, {73, DO_WEST}, {79, DO_WEST},
							  {74, DO_SOUTH}, {75, DO_NORTH}, {79, DO_NORTH}};

Living livings[LIVING_COUNT] = { // { room, strike }
	{2, 4}, {23}, {25, 6}, {44}, {50}, {75}, {45}, {58}, {17}, {10}, {4}, {41}, {32}, {59}, {71}, {66}, {3}, {8}, {18}, {37}, {79} 
};

Item items[ITEM_COUNT] = { // { name, descript, room, useableon }
	{ "het hellehondvlees", "Het is een goor stuk vlees dat naar kots ruikt.", -1 },
	{ "het hittepak", "Dit aluminiumkleurig pak beschermt je tegen grote hitte of kou.", 4 },
	{ "het groen kristal", "Het is een helder, groengekleurd kristal. Even zie je een mysterieuze twinke-\r\nling", -1 },
	{ "het zwaard", "Het is een magisch zwaard dat er niet al te sterk uit ziet, maar veel kracht\r\nuitstraalt. In het heft zit een paarse robijn.", 5 },
	{ "het bot", "Het is een menselijk, verbleekt dijbeen, dat er sterk uit ziet. Je kunt er veel\r\nkracht mee zetten.", 13 },
	{ "de diskette", "Het is een grijze 3,5 inch diskette van het merk 'Spirits' met daarop waar-\r\nschijnlijk belangrijke data.", 20 },
	{ "de hasj", "Het is een zakje met spul dat lijkt op tabak.", 22 },
	{ "het rood kristal", "Het is een helder, roodgekleurd kristal. Even zie je een mysterieuze twinke-\r\nling.", -1 },
	{ "de slaapmuts", "Het is een Mickey Mouse-slaapmuts met vrolijke kleuren.", 24 },
	{ "de noekietronenbom", "De bom bestaat uit een aantal dunne buizen in een cilinder. Daaromheen zitten\r\neen aantal slangetjes. Er klinkt een vreemd gebrom dat uit een rooster komt. Er\r\nzit een bordje op: -5 - 105ø, Codenaam: R136.", 27 },
	{ "de zaklamp", "Het is een zwarte, aluminium zaklamp met een halogeenlampje erin.", 31 },
	{ "het verband", "Het is een witte doos met een rood kruis waarin wat verband en een paar pleis-\r\nters zitten.", 39 },
	{ "de vlammenwerper", "De vlammenwerper bestaat uit een pijp, een zuur- en een brandstoffles en een\r\naktivatieknop. Uit de pijp komt een klein waakvlammetje.", 40 },
	{ "het kookboek", "Het is een oud, vergeeld kookboek met daarin een koekjesrecept. Er staat:\r\n'Pak wat hellehond en wat hasj, en gooi het in de barbecue'.\r\nDat is alles.", 43 },
	{ "de tnt", "De T.N.T. is een bosje rode staven met een velletje waarop staat: 'Pas op!\r\nSchokgevoelig!'", 51 },
	{ "het mosterdgaspatroon", "Het is een patroon dat mosterdgas onder druk bevat. Er zitten draadjes aan, en\r\nje kunt niets vinden om hem te aktiveren.", -1},
	{ "het giftige vlees", "Het is een stuk vlees dat er op zich lekker uit ziet, maar een paar groene\r\nvlekken heeft. Er zit een dode mier op.", 52 },
	{ "de ontsteking", "De ontsteking is een kastje met een T-vormige hendel erop.", 60 },
	{ "het pakje batterijen", "Het is een pakketje met penlights. Konijntjes kunnen er uren mee trommelen.", 61 },
	{ "het gasmasker", "Het is een groen masker met een rond filter en 2 plastic ooggaten.", 62 },
	{ "het papier", "Het is een geel vel papier met gekrulde hoeken. Het handschrift is bijna on-\r\nleesbaar, en met moeite ontcijfer je: 'Voed de drakekop met de 3 gekleurde\r\nkristallen'.", -1 },
	{ "het boekje", "Het is een vies, kleverig boekje met op de voorkant een ontklede trol. Je\r\nkrijgt kotsneigingen.", 70 },
	{ "het blauw kristal", "Het is een helder, blauwgekleurd kristal. Even zie je een mysterieuze twinke-\r\nling.", 72 },
	{ "het koekje", "Het is een rond koekje dat naar ammoniak stinkt.", -1 },
	{ "de mosterdgasgranaat", "Door het indrukken van de hendel kan het mosterdgas ontstnappen.", -1 }
};

char workon[25] = {LIVING_BARBECUE, -1, LIVING_DRAKEKOP, -1, LIVING_DEUR, LIVING_COMPUTER, LIVING_BARBECUE,
							 LIVING_DRAKEKOP, LIVING_DRAAK, LIVING_LAVA, -20, -1, LIVING_BOOM, -1, -1, -19, LIVING_GNOE, -17,
							 -12, -1, -1, LIVING_RODETROL, LIVING_DRAKEKOP, LIVING_DRAAK, LIVING_GEZWEL};

bool Initialize(Progdata& progdata)
{
	int i;

	progdata.paperroute = new char[] { 69, 64, 63, 62, 67, 66 };

	progdata.status.curroom = 0;
	progdata.status.paperpos = 0;
	progdata.status.lifepoints = 20;
	progdata.status.lamp = false;
	progdata.status.lamppoints = 60;

//	window(1, 1, 80, 25);
	clrscr();
	printf("**** Missiecode: _R136_ ****");
//	window(1, 3, 80, 25);

	srand((int)time(NULL));

	for (i = 0; i < 10; i++)
		progdata.owneditems[i] = -1;

	progdata.rooms = rooms;

	return (SetRoomConnections(progdata.rooms)
		&&	SetLivings(progdata.living)
		&&	SetItems(progdata.items));
}

bool SetRoomConnections(Room *rooms)
{
	int i;
	int j;

	for (i = 0; i < ROOM_COUNT; i++)
	{
		rooms[i].connect[DO_EAST] = i + 1;
		rooms[i].connect[DO_WEST] = i - 1;
		rooms[i].connect[DO_NORTH] = i - 5;
		rooms[i].connect[DO_SOUTH] = i + 5;
		rooms[i].connect[DO_UP] = rooms[i].connect[DO_DOWN] = -1;
	}

	// Seperate layers
	for (i = 0; i < ROOM_COUNT; i += 20)
	{
		for (j = 0; j < 16; j += 5)
		{
			rooms[i + j + 4].connect[DO_EAST] = -1;
			rooms[i + j].connect[DO_WEST] = -1;
		}
		for (j = 0; j < 5; j++)
		{
			rooms[i + j].connect[DO_NORTH] = -1;
			rooms[i + j + 15].connect[DO_SOUTH] = -1;
		}
	}
	// Connect layers
	for (i = 0; i < LEVELCON_COUNT; i++)
		rooms[levelcon[i][0]].connect[levelcon[i][1]] = levelcon[i][2];
	// Blocked routes
	for (i = 0; i < BLOCKED_COUNT; i++)
		rooms[blocked[i][0]].connect[blocked[i][1]] = -1;

	return true;
}

bool SetLivings(Living *living)
{
	int i;

	for (i = 0; i < 21; i++)
	{
		living[i].room = beginroom[i];
		living[i].strike = killhits[i];
		living[i].status = 0;
	}

	return true;
}

bool SetItems(Item *items)
{
	int i;

	for (i = 0; i < 25; i++)
	{
		items[i].name = itemname[i];
		items[i].descript = itemdesc[i];
		items[i].room = itemroom[i];
		items[i].useableon = workon[i];
	}

	return true;
}

