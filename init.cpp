#include "include.h"
#include <time.h>

const char *roomnames[80] = {"in het bos", "in het bos", "in het bos", "in het moeras", "in het bos",
							  "in het bos", "op de begraafplaats", "in het bos", "in het moeras", "op de open plek",
							  "in het bos", "in het bos", "op de open plek", "op het moeraspad", "op de open plek",
							  "in het bos", "in het bos", "op de open plek", "in het moeras", "in de ru‹ne",

							  "in de slijmgrot", "in de zwarte grot", "in de drugsgrot", "in de geile grot", "in de jostiegrot",
							  "in de verwaarloosde grot", "in de lege grot", "in de hoofdgrot", "in de hierogliefengrot", "in de stankgrot",
							  "in de troosteloze grot", "in de TL-grot", "in de kleine grot", "in de ijsgrot", "in de kaktusgrot",
							  "in de stalagmietengrot", "in de stormgrot", "in de mistgrot", "in de wenteltrapgrot", "in de tentakelgrot",

							  "in de vuilnisgrot", "in de echogrot", "in de geheime grot", "in de voedselgrot", "in de grot van de gnoe",
							  "in een lege grot", "in de ogengrot", "in de rotsgrot", "in de leegte", "op de zandbank",
							  "in de martelgrot", "in een lege grot", "in de veilige grot", "in de nauwe rotsspleet", "in de oliegrot",
							  "in een lege grot", "in een wenteltrapgrot", "in de spinnengrot", "in de pratende grot", "op de lavaput",

							  "in de skoebiegrot", "in de radioactieve grot", "in de i-grot", "in de p-grot", "in de a-grot",
							  "in de dodengrot", "in de r-grot", "in de e-grot", "in een wenteltrapgrot", "in de P-grot",
							  "in de grot der verdoemenis", "in de vacuumgrot", "in de rode grot", "in de neongrot", "in de bloedgrot",
							  "in de vleermuisgrot", "in de slangengrot", "in de kwabbengrot", "in de glibbergrot", "in de teleportgrot"};

const char *roomdesc[80] = { "Je bevindt je in een uithoek van een donker bos. Overal hoor je enge geluiden.",
							  "Aan de zuidkant zie je een hek dat toegang geeft tot een donkere plaats.",
							  "Er komt een modderige geur uit het oosten.",
							  "Er hangt een griezelige nevel over het stinkende oppervlak.",
							  "Er komt een modderige geur uit het westen.",
							  "Pas op voor de laaghangende takken!",
							  "Een lucht van rottend vlees dringt in je neus. Je denkt dat je een grafsteen\r\nziet bewegen.",
							  NULL,
							  "Er hangt een griezelige nevel over het stinkende oppervlak.",
							  "Er komt een modderige geur uit het westen.",
							  NULL,
							  "Je trapt bijna in een bereklem.",
							  "Door de mist zie je nog net de omtrekken van het donkere bos.",
							  "Er ligt hier een skelet, waarschijnlijk een van je voorgangers.",
							  "Bij het licht van een halve maan onderscheid je nog net de vorm van een galg.",
							  "In de verte hoor je het trieste gehuil van een weerwolf.",
							  NULL,
							  "Er ligt hier een dood konijn dat wordt belaagd door vliegen.",
							  "Er hangt een griezelige nevel over het stinkende oppervlak.",
							  "Je bevindt je in een spookachtige ru‹ne. Er is hier een wankele trap die naar\r\nbeneden leidt.",

							  "De wanden van deze grot zijn bekleed met een snotachtig slijm.",
							  "Je ziet geen hand voor ogen.",
							  NULL,
							  "Aan de muren hangen gelige, gescheurde Playboy-posters.",
							  "Er hangt hier een dwangbuis, met het lijk van een verminkte jostie.",
							  NULL,
							  NULL,
							  "Er staat hier een batterij aan mysterieuze apparatuur.",
							  "Op de wanden staan hierogliefen waar je geen wijs uit wordt.",
							  "Er hangt hier een smerige lucht die je herinnert aan de zware lucht van een\r\nbeerput.",
							  NULL,
							  "De grot wordt zwak verlicht door een lichtbron die hoog aan het plafond hangt.",
							  NULL,
							  "In deze grot lijkt het net of alles van ijs is, en je krijgt rillingen.",
							  "Je bent omringd door giftige kaktussen die in deze grot staan.",
							  "Hier zie je een traliewerk van stalagmieten.",
							  "Door deze grot loeit een harde wind, waardoor je je vast moet grijpen aan een\r\nvan de wanden.",
							  "Een dichte mist belemmert je zicht, en je verliest je or‹entatiegevoel.",
							  "In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\r\nandere niveaus leidt.",
							  "Van alle kanten komen grote tentakels die je aftasten en groene sporen op je\r\nhuid achterlaten.",

							  "In deze grot ligt een grote stapel rottende etensresten. De stank is bijna on-\r\ndraaglijk.",
							  "Hier worden alle geluiden die je maakt tegen de wanden geëcho'd.",
							  "Op de grond van deze grot liggen allerlei onbekende en geheimzinnige voorwer-\r\npen.",
							  "Zo te ruiken is dit waarschijnlijk eens een keuken geweest...",
							  "Hier liggen de geraamtes van wezens die eerder ten prooi zijn gevallen aan de\r\ngnoe.",
							  NULL,
							  "Van alle kanten wordt je bespied door rode, bloeddoorlopen ogen die precies\r\nvolgen wat je doet.",
							  "Overal zie je hier scherpe rotspunten. Aan een aantal ervan zitten bruine kors-\r\nten.",
							  NULL,
							  "Op de vloer liggen vreemde patronen, gevormd uit verschillende soorten zand.",
							  "Onder de vage schemering van de martelvuren zie je nog net een duimschroef en\r\nwat stekelige voorwerpen waar nog wat bloed aan zit.",
							  NULL,
							  "Dit is de enige grot waar je je een beetje veilig voelt.",
							  "Aan alle kanten wordt je omringd door hoge rotsmuren. Alleen in het westen zie\r\nje een opening.",
							  "Vanuit het zuiden verspreidt zich een enorme hitte, die in deze grot nog net\r\ndraaglijk is.",
							  NULL,
							  "In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\r\nandere niveaus leidt.",
							  "Het wemelt hier van de tarantula's. Bij elke stap die je zet hoor je het onder\r\nje voeten kraken, en ze kruipen langs je benen omhoog.",
							  NULL,
							  NULL,

							  "Uit alle richtingen komen rare geluiden, als in een gesticht.",
							  "Door de hoge radioactiviteit is deze grot zwak verlicht.",
							  NULL,
							  NULL,
							  "In deze grot bevindt zich het stenen beeld van een oud, jou onbekend wezen.",
							  "De naam van deze grot spreekt voor zich...",
							  NULL,
							  NULL,
							  "In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar\r\nandere niveaus leidt.",
							  NULL,
							  "In deze grot heerst een haast verstikkende sfeer, en je voelt je niet prettig.",
							  NULL,
							  NULL,
							  "Deze grot is fel gekleurd. Er staan patronen die je doen denken aan zwarte ma-\r\ngie.",
							  "Het geraamte van een groot beest ligt hier op de grond en een aantal ingewanden\r\nliggen er naast.",
							  "In deze grot fladderen overal vleermuizen, op zoek naar hun prooi.",
							  "Je hoort het geluid van een ratelslang. Bij de weg naar het noorden staat een\r\ndoodskop getekend, die een gevaar aanduidt.",
							  NULL,
							  "Je glijdt bijna uit over de zeepachtige prut die overal in de grot ligt. Tus-\r\nsen de glibberige massa steekt een paal omhoog met daarop een pijl die naar\r\nhet oosten wijst.",
							  NULL};

char levelcon[11][3] = {{6, DO_DOWN, 34},
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

char blocked[83][2] = {{3, DO_WEST}, {3, DO_EAST}, {3, DO_SOUTH}, {8, DO_WEST},
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

char beginroom[21] = {2, 23, 25, 44, 50, 75, 45, 58, 17, 10, 4, 41, 32, 59, 71, 66, 3, 8, 18, 37, 79};
char killhits[21] = {4, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

const char *itemname[25] = {"het hellehondvlees", "het hittepak", "het groen kristal",
							 "het zwaard", "het bot", "de diskette", "de hasj", "het rood kristal",
							 "de slaapmuts", "de noekietronenbom", "de zaklamp", "het verband",
							 "de vlammenwerper", "het kookboek", "de tnt", "het mosterdgaspatroon",
							 "het giftige vlees", "de ontsteking", "het pakje batterijen", "het gasmasker",
							 "het papier", "het boekje", "het blauw kristal", "het koekje",
							 "de mosterdgasgranaat"};

const char *itemdesc[25] = {"Het is een goor stuk vlees dat naar kots ruikt.",
							 "Dit aluminiumkleurig pak beschermt je tegen grote hitte of kou.",
							 "Het is een helder, groengekleurd kristal. Even zie je een mysterieuze twinke-\r\nling",
							 "Het is een magisch zwaard dat er niet al te sterk uit ziet, maar veel kracht\r\nuitstraalt. In het heft zit een paarse robijn.",
							 "Het is een menselijk, verbleekt dijbeen, dat er sterk uit ziet. Je kunt er veel\r\nkracht mee zetten.",
							 "Het is een grijze 3,5 inch diskette van het merk 'Spirits' met daarop waar-\r\nschijnlijk belangrijke data.",
							 "Het is een zakje met spul dat lijkt op tabak.",
							 "Het is een helder, roodgekleurd kristal. Even zie je een mysterieuze twinke-\r\nling.",
							 "Het is een Mickey Mouse-slaapmuts met vrolijke kleuren.",
							 "De bom bestaat uit een aantal dunne buizen in een cilinder. Daaromheen zitten\r\neen aantal slangetjes. Er klinkt een vreemd gebrom dat uit een rooster komt. Er\r\nzit een bordje op: -5 - 105ø, Codenaam: R136.",
							 "Het is een zwarte, aluminium zaklamp met een halogeenlampje erin.",
							 "Het is een witte doos met een rood kruis waarin wat verband en een paar pleis-\r\nters zitten.",
							 "De vlammenwerper bestaat uit een pijp, een zuur- en een brandstoffles en een\r\naktivatieknop. Uit de pijp komt een klein waakvlammetje.",
							 "Het is een oud, vergeeld kookboek met daarin een koekjesrecept. Er staat:\r\n'Pak wat hellehond en wat hasj, en gooi het in de barbecue'.\r\nDat is alles.",
							 "De T.N.T. is een bosje rode staven met een velletje waarop staat: 'Pas op!\r\nSchokgevoelig!'",
							 "Het is een patroon dat mosterdgas onder druk bevat. Er zitten draadjes aan, en\r\nje kunt niets vinden om hem te aktiveren.",
							 "Het is een stuk vlees dat er op zich lekker uit ziet, maar een paar groene\r\nvlekken heeft. Er zit een dode mier op.",
							 "De ontsteking is een kastje met een T-vormige hendel erop.",
							 "Het is een pakketje met penlights. Konijntjes kunnen er uren mee trommelen.",
							 "Het is een groen masker met een rond filter en 2 plastic ooggaten.",
							 "Het is een geel vel papier met gekrulde hoeken. Het handschrift is bijna on-\r\nleesbaar, en met moeite ontcijfer je: 'Voed de drakekop met de 3 gekleurde\r\nkristallen'.",
							 "Het is een vies, kleverig boekje met op de voorkant een ontklede trol. Je\r\nkrijgt kotsneigingen.",
							 "Het is een helder, blauwgekleurd kristal. Even zie je een mysterieuze twinke-\r\nling.",
							 "Het is een rond koekje dat naar ammoniak stinkt.",
							 "Door het indrukken van de hendel kan het mosterdgas ontstnappen."};

char itemroom[25] = {-1, 4, -1, 5, 13, 20, 22, -1, 24, 27, 31, 39, 40, 43, 51, -1, 52, 60, 61, 62, -1, 70, 72, -1, -1};

char workon[25] = {LIVING_BARBECUE, -1, LIVING_DRAKEKOP, -1, LIVING_DEUR, LIVING_COMPUTER, LIVING_BARBECUE,
							 LIVING_DRAKEKOP, LIVING_DRAAK, LIVING_LAVA, -20, -1, LIVING_BOOM, -1, -1, -19, LIVING_GNOE, -17,
							 -12, -1, -1, LIVING_RODETROL, LIVING_DRAKEKOP, LIVING_DRAAK, LIVING_GEZWEL};

bool Initialize(Progdata &progdata)
{
	int i;

	progdata.paperroute[0] = 69;
	progdata.paperroute[1] = 64;
	progdata.paperroute[2] = 63;
	progdata.paperroute[3] = 62;
	progdata.paperroute[4] = 67;
	progdata.paperroute[5] = 66;

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

	return (SetRooms(progdata.rooms)
		&&	SetLivings(progdata.living)
		&&	SetItems(progdata.items));
}

bool SetRooms(Room *rooms)
{
	int i;
	int j;

	for (i = 0; i < 80; i++)
	{
		rooms[i].name = roomnames[i];
		rooms[i].descript = roomdesc[i];
		rooms[i].connect[DO_EAST] = i + 1;
		rooms[i].connect[DO_WEST] = i - 1;
		rooms[i].connect[DO_NORTH] = i - 5;
		rooms[i].connect[DO_SOUTH] = i + 5;
		rooms[i].connect[DO_UP] = rooms[i].connect[DO_DOWN] = -1;
	}

	// Seperate layers
	for (i = 0; i < 80; i += 20)
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
	for (i = 0; i < 11; i++)
		rooms[levelcon[i][0]].connect[levelcon[i][1]] = levelcon[i][2];
	// Blocked routes
	for (i = 0; i < 83; i++)
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

