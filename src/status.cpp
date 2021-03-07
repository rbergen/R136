#include "r136.h"

void RoomStatus(Progdata &progdata)
{
	static const wchar_t *youreatFormat = L"Je bevindt je %ls.\n";
	const wchar_t *roomName;
	wchar_t *youreatBuffer;
	size_t youreatBufferLength;

	roomName = progdata.rooms[progdata.status.curroom].name;

	youreatBufferLength = wcslen(youreatFormat) + wcslen(roomName);
	youreatBuffer = (wchar_t *)calloc(youreatBufferLength, sizeof(wchar_t));
	swprintf(youreatBuffer, youreatBufferLength, youreatFormat, roomName);
	
	writemw(youreatBuffer);

	free(youreatBuffer);

	if (progdata.status.curroom != ROOM_RADIOACTIEVEGROT && progdata.status.curroom != ROOM_TLGROT && progdata.status.curroom >= 20 && !progdata.status.lamp)
		printmw("Het is stekedonker en je ziet geen hand voor ogen.\n");
	else
	{
		if (progdata.rooms[progdata.status.curroom].descript)
			writemw(progdata.rooms[progdata.status.curroom].descript);
			printmw("\n");
		ShowItems(progdata);
	}

	ShowDirString(progdata.rooms[progdata.status.curroom].connect);
	printmw("\n");
}

void ShowDirString(char *connect)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		if (connect[i] != UNDEFINED)
			count++;

	if (!count)
		return;

	printmw("Je kunt naar ");

	for (i = 0; i < 6; i++)
		if (connect[i] != UNDEFINED)
		{
			switch(i)
			{
			case DO_EAST:
				printmw("het oosten");
				break;
			case DO_WEST:
				printmw("het westen");
				break;
			case DO_NORTH:
				printmw("het noorden");
				break;
			case DO_SOUTH:
				printmw("het zuiden");
				break;
			case DO_UP:
				printmw("boven");
				break;
			case DO_DOWN:
				printmw("beneden");
				break;
			}
			switch(--count)
			{
			case 0:
				break;
			case 1:
				printmw(" en ");
				break;
			default:
				printmw(", ");
				break;
			}
		}

	printmw(".\n");
}

void ShowItems(Progdata &progdata)
{
	int count = 0;
	int i;

	for (i = 0; i < ITEM_COUNT; i++)
		if (progdata.items[i].room == progdata.status.curroom)
			count++;

	if (count)
	{
		printmw("Hier lig%s ", count > 1 ? "gen" : "t");

		for (i = 0; i < ITEM_COUNT; i++)
			if (progdata.items[i].room == progdata.status.curroom)
			{
				if (getcurx(stdscr) > 54)
					printmw("\n");
				printmw(progdata.items[i].name);

				switch(--count)
				{
				case 0:
					break;
				case 1:
					printmw(" en ");
					break;
				default:
					printmw(", ");
					break;
				}
			}

		printmw(".\n");
	}
}


bool LivingStatus(Progdata &progdata)
{
	int livingfound = UNDEFINED;
	int i;

	for (i = 0; i < LIVING_COUNT && livingfound == UNDEFINED; i++)
		if (progdata.living[i].room == progdata.status.curroom)
			livingfound = i;

	switch (livingfound)
	{
	case LIVING_HELLEHOND:

		HellehondStatus(progdata);
		break;
	
	case LIVING_RODETROL:
	
		RodeTrolStatus(progdata);
		break;
	
	case LIVING_PLANT:
	
		PlantStatus(progdata);
		break;
	
	case LIVING_GNOE:
	
		GnoeStatus(progdata);
		break;
	
	case LIVING_DRAAK:
		DraakStatus(progdata);
		break;
	
	case LIVING_GEZWEL:
	
		GezwelStatus(progdata);
		break;
	
	case LIVING_DEUR:
	
		DeurStatus(progdata);
		break;
	
	case LIVING_STEMMEN:
	
		StemmenStatus(progdata);
		break;
	
	case LIVING_BARBECUE:
	
		BarbecueStatus(progdata);
		break;
	
	case LIVING_BOOM:
	
		BoomStatus(progdata);
		break;
	
	case LIVING_GROENKRISTAL:
	
		GroenKristalStatus(progdata);
		break;
	
	case LIVING_COMPUTER:
	
		ComputerStatus(progdata);
		break;
	
	case LIVING_DRAKEKOP:
	
		DrakeKopStatus(progdata);
		break;
	
	case LIVING_LAVA:
	
		return LavaStatus(progdata);
	
	case LIVING_VACUUM:
	
		printmw("Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een\n");
		printmw("verschrikkelijke pijn kraakt als een bliksem door je lijf. Je valt naar achte-\n");
		printmw("ren de grot uit, en daar val je even flauw.\n\n");

		progdata.status.lifepoints -= 4; //   Levenswond
		progdata.status.curroom = ROOM_SLANGENGROT; //   Grot terug
	
		return false;
	
	case LIVING_PAPIER:
	
		PapierStatus(progdata);
		break;
	
	case LIVING_NOORDMOERAS:
	case LIVING_MIDDENMOERAS:
	case LIVING_ZUIDMOERAS:
	
		printmw("Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond\n");
		printmw("onder de voeten hebt. Ondanks je wilde pogingen boven te blijven zak je\n");
		printmw("langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa\n");
		printmw("zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie,\n");
		printmw("en na enige tijd verlies je je bewustzijn.\n");
		printmw("Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot.\n\n");

		switch (progdata.status.curroom)
		{
	
		case ROOM_NOORDMOERAS:
	
			progdata.status.curroom = ROOM_LEGEGROT51;
			break;
	
		case ROOM_MIDDENMOERAS:
	
			progdata.status.curroom = ROOM_TROOSTELOZEGROT;
			break;
	
		case ROOM_ZUIDMOERAS:
	
			progdata.status.curroom = ROOM_ROTSGROT;
			break;
		}
	
		return false;
	
	case LIVING_MISTGROT:
	
		printmw("In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen\n");
		writemw(L"ziet. Je verliest je orïentatiegevoel en stommelt paniekerig door de grot, op\n");
		printmw("zoek naar een uitgang.\n");
		printmw("Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden,\n");
		printmw("struikel je voorover een andere grot in.\n\n");

		switch(random(3))
		{
		case 0:
	
			progdata.status.curroom = ROOM_STORMGROT;
			break;
	
		case 1:
	
			progdata.status.curroom = ROOM_KLEINEGROT;
			break;
	
		case 2:
	
			progdata.status.curroom = ROOM_WENTELTRAPGROT1;
			break;
		}
	
		return false;
	
	case LIVING_TELEPORT:
	
		printmw("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het\n");
		printmw("plafond en tegen een van de wanden een enorm apparaat met een aantal\n");
		printmw("bedieningspanelen en beeldschermen.\n");
		printmw("Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal\n");
		printmw("in de grond, waarna een sirene begint te loeien. Van de schrik blijf je liggen,\n");
		printmw("en je ziet dat de lampen aan het plafond feller gaan branden en er grote\n");
		printmw("hoeveelheden data over de beeldschermen flitsen. Even later zie je een\n");
		printmw("oogverblindende flits en voel je je even gewichtloos.\n");
		printmw("Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\n");
		printmw("Sterker nog, je ligt buiten...\n\n");

		progdata.status.curroom = ROOM_BOS1;

		return false;
	}

	return true;
}

void HellehondStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_HELLEHOND].status)
	{
	case 0:

		printmw("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe\n");
		printmw("tanden steken duidelijk af, en het rode kwijl druipt langzaam uit zijn bek.\n");
		printmw("Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel\n");
		printmw("klinkt een diep gegrom.\n\n");

		progdata.living[LIVING_HELLEHOND].status++;

		break;

	case 1:

		printmw("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn\n");
		printmw("nagels boren zich in je vlees, en op een gegeven moment bijt hij je hard in je\n");
		printmw("schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. De\n");
		printmw("hond laat je los, en hij kijkt je grommend aan.\n\n");

		progdata.status.lifepoints--; //  Wond
		progdata.living[LIVING_HELLEHOND].status++;

		break;

	case 2:

		printmw("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn\n");
		printmw("keel, en hij staat klaar om opnieuw aan te vallen.\n\n");

		progdata.living[LIVING_HELLEHOND].status = random(2) + 1;

		break;

	case 3:

		printmw("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je\n");
		printmw("deelt nog een slag uit, en een stuk vlees van de hond laat los.\n\n");

		progdata.items[ITEM_HONDVLEES].room = progdata.status.curroom;
		progdata.living[LIVING_HELLEHOND].status++;

		break;

	case 4:

		printmw("De dode hellehond ligt in een bad van dampend bloed.\n\n");
		break;
	}
}

void RodeTrolStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_RODETROL].status)
	{
	case 0:

    	writemw(L"Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar geërgerd.\n\n");

		progdata.living[LIVING_RODETROL].status++;

		break;

	case 1:

		printmw("Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je\n");
		printmw("af.\n\n");

		progdata.living[LIVING_RODETROL].status++;

		break;

	case 2:

		printmw("De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn\n");
		printmw("tot je botten doordringen.\n\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[LIVING_RODETROL].status++;

		break;

	case 3:

		printmw("Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep.\n\n");

		progdata.living[LIVING_RODETROL].status = random(2) + 2;

		break;

	case STATUS_RODETROL_BOEKJETHROWN:

		printmw("Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en\n");
		printmw("roder. Op een gegeven moment klinkt een geborrel op uit het wezen, en met een\n");
		printmw("klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol\n");
		printmw("langzaam naar beneden.\n");
		printmw("Opeens zie je iets glinsteren.\n\n");

		progdata.items[ITEM_ROODKRISTAL].room = progdata.status.curroom;
		progdata.living[LIVING_RODETROL].status++;

		break;

	case 5:

		printmw("Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm\n");
		printmw("zuigt aan je schoenen, en een vieze stank dringt in je neus.\n\n");

		break;
	}
}

void PlantStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_PLANT].status)
	{
	case 0:

		printmw("In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit\n");
		printmw("in een afschrikwekkende kop, met afzichtelijke tanden. Hij heeft je gezien en\n");
		printmw("beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen\n");
		printmw("zetten zit je verstrengd in het monster, en zet de plant zijn tanden in je\n");
		printmw("nek.\n\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[LIVING_PLANT].status = random(2) + 1;

		break;

	case 1:

		printmw("De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek.\n");
		printmw("Met zijn groene oogjes kijkt hij je weer aan, en hij maakt aanstalten zijn\n");
		printmw("tanden opnieuw in je nek te zetten.\n\n");

		progdata.living[LIVING_PLANT].status++;

		break;

	case 2:

		printmw("Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via\n");
		printmw("je rug naar beneden, en de pijn is nu ondraaglijk. Na een tijdje laat de plant\n");
		printmw("je weer los.\n\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[LIVING_PLANT].status = random(2) + 1;

		break;

	case STATUS_LIVING_DEAD:

		printmw("De resten van wat eerst een vleesetende plant was liggen nu op de grond van\n");
		printmw("de grot. Zijn bek ligt opengesperd, en zijn ogen rollen bijna uit zijn oogkas-\n");
		printmw("sen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\n");
		printmw("Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening.\n\n");

		progdata.rooms[ROOM_VERWAARLOOSDEGROT].connect[DO_NORTH] = ROOM_SLIJMGROT; //	Maak verbinding met slijmgrot
		progdata.living[LIVING_PLANT].status++;

		break;

	case 4:
		printmw("De vleesetende plant is niet veel meer dan een berg stinkend tuinafval.\n\n");

		break;
	}
}

void GnoeStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_GNOE].status)
	{
	case 0:

		printmw("Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aan-\n");
		printmw("kijkt. Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende\n");
		printmw("beestjes, die je nog nooit eerder gezien hebt. Het beest verspreidt een\n");
		printmw("afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe.\n\n");

		progdata.living[LIVING_GNOE].status++;

		break;

	case 1:

		printmw("De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je\n");
		printmw("hebt het gevoel alsof je longen uit je lijf worden geperst. Versuft sta je\n");
		printmw("weer op.\n\n");

		progdata.status.lifepoints--; //   Wond

		break;

	case STATUS_GNOE_GIFTIGVLEESFED:

		writemw(L"De gnoe ziet het vlees, snuffelt er aan, en slokt het in één hap naar binnen.\n");
		printmw("Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar\n");
		printmw("buiten. Hij zakt in elkaar en blijft roerloos liggen.\n\n");

		progdata.living[LIVING_GNOE].status = STATUS_LIVING_DEAD;

		break;

	case STATUS_LIVING_DEAD:

		printmw("Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er\n");
		printmw("als een papje naast.\n\n");

		break;
	}
}

void DraakStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_DRAAK].status)
	{

	case 0:

		printmw("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je\n");
		printmw("allemaal bespieden met gele oogjes. Zijn hele huid is bedekt met schimmel, en\n");
		printmw("uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af drup-\n");
		printmw("pelt. Opeens komt uit een van de bekken een rommelend geluid. Met moeite\n");
		printmw("versta je \"Ben jij een koekie?\".\n\n");

		progdata.living[LIVING_DRAAK].status++;

		break;

	case 1:

		printmw("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig\n");
		printmw("te snuiven.\n");
		printmw("De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van\n");
		printmw("walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt\n");
		printmw("\"BEN JIJ EEN KOEKIE?!?\".\n\n");

		progdata.living[LIVING_DRAAK].status++;

		break;

	case 2:

		printmw("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzet-\n");
		printmw("tende harde klap. Er kraakt iets in je hoofd, en een duizeling maakt zich van\n");
		printmw("je meester. Hij maakt aanstalten je nog een klap te verkopen.\n\n");

		progdata.status.lifepoints--; //   Wond

		break;

	case STATUS_DRAAK_KOEKJETHROWN:

		printmw("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\n");
		printmw("Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\n");
		printmw("Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak\n");
		printmw("slaapt.\n\n");

		progdata.living[LIVING_DRAAK].status++;

		break;

	case STATUS_DRAAK_LIGHTSLEEPING:

		printmw("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn\n");
		printmw("lijf klinkt een diep gegrom.\n\n");

		break;

	case STATUS_DRAAK_SLAAPMUTSONHEAD:

		printmw("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts\n");
		printmw("steken af tegen de beschimmelde huid, en de muts zakt iets scheef. Op een ge-\n");
		printmw("geven moment valt er iets, en het klettert tegen de harde rotsvloer.\n\n");

		progdata.items[ITEM_GASPATROON].room = progdata.status.curroom;
		progdata.living[LIVING_DRAAK].status++;

		break;

	case 6:

		printmw("De draak slaapt rustig.\n\n");

		break;
	}
}

void GezwelStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_GEZWEL].status)
	{
	case 0:

		printmw("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je\n");
		printmw("aan met 2 gluiperige ogen, op zijn huid zitten schurftvlekken, en op zijn\n");
		printmw("mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich\n");
		printmw("vast aan alle wanden van de grot en verspert zo je weg.\n\n");

		progdata.living[LIVING_GEZWEL].status++;

		break;

	case 1:

		printmw("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.\n\n");

		break;

	case STATUS_GEZWEL_GASSED:
		if (progdata.items[ITEM_GASMASKER].room == STATUS_ITEM_OWNED)
		// gasmasker op
		{
			printmw("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n");
			printmw("Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen\n");
			printmw("overal scheuren in zijn schurfterige huid. Zijn tentakels komen langzaam met\n");
			printmw("een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in el-\n");
			printmw("kaar.\n\n");
		}
		else
		// geen masker... oeps!
		{
			printmw("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen,\n");
			printmw("voordat je zelf een kloppende hoofdpijn krijgt en onderuit gaat. Je hebt niets\n");
			printmw("om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer\n");
			printmw("bij.\n\n");

			progdata.status.lifepoints -= 4; //    Grote wond
		}

		progdata.rooms[ROOM_VLEERMUISGROT].connect[DO_NORTH] = ROOM_VERDOEMENISGROT;
		progdata.living[LIVING_GEZWEL].status = STATUS_LIVING_DEAD;

		break;

	case STATUS_LIVING_DEAD:

		printmw("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn\n");
		printmw("maag kruipen pissebedden en oorkruipers. Er verspreidt zich een sterke rot-\n");
		printmw("lucht, en er ontstaat langzaam een klein slijmplasje.\n\n");

		break;
	}
}

void DeurStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_DEUR].status)
	{
	case 0:

		printmw("In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet\n");
		printmw("meer open te krijgen.\n\n");

		break;

	case STATUS_DEUR_OPEN:

		writemw(L"Je zet één eind van het bot onder de deur, en op het andere begin je te duwen.\n");
		printmw("Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een\n");
		printmw("kier. Je geeft nog een duw, en langzaam draait de deur open.\n\n");

		progdata.rooms[ROOM_LEGEGROT45].connect[DO_NORTH] = ROOM_VUILNISGROT;
		progdata.living[LIVING_DEUR].status++;

		break;

	case 2:
		printmw("De deur is nu open, en geeft toegang tot een grot.\n\n");

		break;
	}
}

void StemmenStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_STEMMEN].status)
	{
	case 0:

		printmw("Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan:\n");
		printmw("\"Wat schreeuwt is in z'n hart nog een kind\".\n");
		printmw("Dan is het weer stil.\n\n");

		progdata.living[LIVING_STEMMEN].status++;

		break;

	case 1:

		printmw("Vanuit de verte hoor je zachte, lachende stemmetjes.\n\n");

		break;
	}
}

void BarbecueStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_BARBECUE].status)
	{
	case STATUS_BARBECUE_INITIALBURN:

		printmw("Op deze open plek staat een barbecue gezellig te branden.\n\n");

		break;

	case STATUS_BARBECUE_HASJONFIRE:

		printmw("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt\n");
		printmw("er niets.\n\n");

		progdata.living[LIVING_BARBECUE].status = STATUS_BARBECUE_INGREDIENTBURN;

		break;

	case STATUS_BARBECUE_VLEESONFIRE:

		printmw("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder\n");
		printmw("gebeurt er niets.\n\n");

		progdata.living[LIVING_BARBECUE].status = STATUS_BARBECUE_INGREDIENTBURN;

		break;

	case STATUS_BARBECUE_INGREDIENTBURN:

		printmw("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.\n\n");

		break;

	case STATUS_BARBECUE_KOEKJEBAKING:

		writemw(L"Een grote rookontwikkeling treedt op wanneer het tweede ingrediënt in de\n");
		printmw("barbecue belandt.\n");
		writemw(L"Knetterend smelten de 2 ingrediënten om tot een koekje.\n\n");

		progdata.items[ITEM_KOEKJE].room = progdata.status.curroom;
		progdata.living[LIVING_BARBECUE].status = STATUS_BARBECUE_INITIALBURN;

		break;
	}
}

void BoomStatus(Progdata &progdata)
{
	static const wchar_t *smeulendbos = L"Om je heen zie je de smeulende resten van wat eens bos was.";

	int i, j;

	switch (progdata.living[LIVING_BOOM].status)
	{
	case 0:

		printmw("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit\n");
		printmw("een bordje met daarop de tekst \"Roken en open vuur verboden\".\n\n");

		break;

	case STATUS_BOOM_SETONFIRE:

		printmw("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam\n");
		printmw("te branden, en weldra staat hij in lichterlaaie. De vlammen slaan om zich heen,\n");
		printmw("en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee,\n");
		printmw("en de hitte is enorm.\n\n");

		if (progdata.items[ITEM_HITTEPAK].room != STATUS_ITEM_OWNED)
		{
			printmw("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwon-\n");
			printmw("den op.\n\n");

			progdata.status.lifepoints -= 4; //   Levenswond
		}

		for (i = 0; i < 20; i += 5)
			for (j = 0; j < 2; j++)
				if (i + j != 6)
					progdata.rooms[i + j].descript = smeulendbos;

		progdata.rooms[ROOM_BOS2].descript = smeulendbos;
		progdata.rooms[ROOM_BOS4].descript = smeulendbos;
		progdata.rooms[ROOM_BOS7].descript = smeulendbos;

		progdata.items[ITEM_GROENKRISTAL].room = ROOM_BOS4;
		progdata.living[LIVING_GROENKRISTAL].status = 1;
		progdata.living[LIVING_BOOM].status++;

		break;

	case 2:

		printmw("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk\n");
		printmw("bord met daarop \"R   n e  op n v u  ver  d n\".\n\n");

		break;
	}
}

void GroenKristalStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_GROENKRISTAL].status)
	{
	case 0:

		writemw(L"Je struikelt over iets. Door de begroeïing zie je niet wat het is.\n\n");

		break;
	}
}

void ComputerStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_COMPUTER].status)
	{
	case 0:

		printmw("Er staat een computer van het merk Beull die bestaat bestaat uit een kast met\n");
		printmw("een 3.5-inch drive en een monitor. Op de monitor staat: \"Datadisk invoeren\n");
		printmw("a.u.b.\".\n\n");

		progdata.living[LIVING_COMPUTER].status++;

		break;

	case 1:

		printmw("De computer wacht nog steeds.\n\n");

		break;

	case STATUS_COMPUTER_READING:

		printmw("De drive begint te lezen en na korte tijd verschijnt er informatie op het\n");
		printmw("scherm. Er staat: \"In het onderste grottenstelsel moet men een letter-\n");
		printmw("route volgen die resulteert in de naam van het te vinden voorwerp.\".\n");
		printmw("Na even wordt het scherm zwart.\n\n");

		progdata.living[LIVING_COMPUTER].status++;

		break;

	case 3:

		printmw("Er valt niets te zien op de monitor en de computer is stil.\n\n");

		break;
	}
}

void DrakeKopStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_DRAKEKOP].status)
	{
	case 0:

		printmw("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een\n");
		printmw("geopende muil. Op de deur zit een zwaar slot.\n\n");

		break;

	case 1:

		printmw("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer\n");
		printmw("opengaat. Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te\n");
		printmw("gloeien.\n\n");

		progdata.living[LIVING_DRAKEKOP].status++;

		break;

	case 2:

		printmw("De ogen van de draak blijven licht gloeien.\n\n");

		break;

	case 3:

		printmw("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het\n");
		printmw("kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.\n\n");

		progdata.living[LIVING_DRAKEKOP].status++;
		break;

	case 4:

		printmw("De ogen van de draak blijven gloeien.\n\n");

		break;

	case 5:

		printmw("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft\n");
		printmw("hij dicht. De ogen beginnen nu steeds feller te gloeien. Op een gegeven moment\n");
		printmw("concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet\n");
		printmw("en wordt weerkaatst in een spiegel vlak achter je. De spiegel reflecteert het\n");
		printmw("licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\n");
		printmw("Daarna zwaait de deur langzaam met veel gepiep open.\n\n");

		progdata.rooms[ROOM_KLEINEGROT].connect[DO_NORTH] = ROOM_HOOFDGROT;
		progdata.living[LIVING_DRAKEKOP].status++;

		break;

	case 6:

		printmw("De zware deur is nu open en geeft toegang tot een ruimte.\n\n");

		break;
	}
}

bool LavaStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_LAVA].status)
	{
	case 0:

		if (progdata.items[ITEM_HITTEPAK].room == STATUS_ITEM_OWNED)
		{
			printmw("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke\n");
			printmw("damp, en een rode gloed verlicht de omtrek. De hitte is enorm, maar het hitte-\n");
			printmw("pak beschermt je tegen verbranding.\n\n");
		}
		else
		{
			printmw("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je\n");
			printmw("een aantal brandwonden oploopt en naar achteren wordt geblazen.\n\n");

			progdata.status.curroom = ROOM_OLIEGROT; //   Grot terug
			progdata.status.lifepoints -= 4; //   Levenswond

			return false;
		}

		return true;

	case STATUS_LAVA_BOMDROPPED:

		printmw("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt\n");
		printmw("de bom langzaam weg naar beneden. De lava begint op een gegeven moment vreemd\n");
		printmw("te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver-\n");
		printmw("blindende flits vanuit het lava. Daarna wordt het weer rustiger.\n\n");
		printmw("Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door\n");
		printmw("dit positronenwapen, waarvan de beginselen mede van jouw handen komen. Je mis-\n");
		printmw("sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het\n");
		printmw("grottenstelsel.\n\n");

		ForceExit();
	}

	return true;
}

void PapierStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_PAPIER].status)
	{
	case 0:

		printmw("Er zit een dicht, houten luik in het plafond. Je kunt er niet bij.\n\n");

		break;

	case STATUS_PAPIER_OPENING:

		printmw("Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden.\n\n");

		progdata.items[ITEM_PAPIERITEM].room = ROOM_RGROT;
		progdata.living[LIVING_PAPIER].status++;

		break;

	case 2:

		printmw("Het luik aan het plafond hangt nu open. Er zit een leeg gat.\n\n");

		break;
	}
}


