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
	
	WriteToMainWindow(youreatBuffer);

	free(youreatBuffer);

	if (progdata.status.curroom != ROOM_RADIOACTIEVEGROT && progdata.status.curroom != ROOM_TLGROT && progdata.status.curroom >= 20 && !progdata.status.lamp)
		PrintToMainWindow("Het is stekedonker en je ziet geen hand voor ogen.\n");
	else
	{
		if (progdata.rooms[progdata.status.curroom].descript)
			WriteToMainWindow(progdata.rooms[progdata.status.curroom].descript);
			PrintToMainWindow("\n");
		ShowItems(progdata);
	}

	ShowDirString(progdata.rooms[progdata.status.curroom].connect);
	PrintToMainWindow("\n");
}

void ShowDirString(char *connect)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		if (connect[i] != kUndefined)
			count++;

	if (!count)
		return;

	PrintToMainWindow("Je kunt naar ");

	for (i = 0; i < 6; i++)
		if (connect[i] != kUndefined)
		{
			switch(static_cast<Command>(i))
			{
			case Command::kEast:
				PrintToMainWindow("het oosten");
				break;
			case Command::kWest:
				PrintToMainWindow("het westen");
				break;
			case Command::kNorth:
				PrintToMainWindow("het noorden");
				break;
			case Command::kSouth:
				PrintToMainWindow("het zuiden");
				break;
			case Command::kUp:
				PrintToMainWindow("boven");
				break;
			case Command::kDown:
				PrintToMainWindow("beneden");
				break;
			}
			switch(--count)
			{
			case 0:
				break;
			case 1:
				PrintToMainWindow(" en ");
				break;
			default:
				PrintToMainWindow(", ");
				break;
			}
		}

	PrintToMainWindow(".\n");
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
		PrintToMainWindow("Hier lig%s ", count > 1 ? "gen" : "t");

		for (i = 0; i < ITEM_COUNT; i++)
			if (progdata.items[i].room == progdata.status.curroom)
			{
				if (getcurx(stdscr) > 54)
					PrintToMainWindow("\n");
				PrintToMainWindow(progdata.items[i].name);

				switch(--count)
				{
				case 0:
					break;
				case 1:
					PrintToMainWindow(" en ");
					break;
				default:
					PrintToMainWindow(", ");
					break;
				}
			}

		PrintToMainWindow(".\n");
	}
}


bool LivingStatus(Progdata &progdata)
{
	AnimateID livingfound = AnimateID::kUndefined;
	int i;

	for (i = 0; i < AnimateID::COUNT && livingfound == kUndefined; i++)
		if (progdata.living[i].room == progdata.status.curroom)
			livingfound = i;

	switch (livingfound)
	{
	case AnimateID::kHellHound:

		HellehondStatus(progdata);
		break;
	
	case AnimateID::kRedTroll:
	
		RodeTrolStatus(progdata);
		break;
	
	case AnimateID::kPlant:
	
		PlantStatus(progdata);
		break;
	
	case AnimateID::kGnu:
	
		GnoeStatus(progdata);
		break;
	
	case AnimateID::kDragon:
		DraakStatus(progdata);
		break;
	
	case AnimateID::kSwelling:
	
		GezwelStatus(progdata);
		break;
	
	case AnimateID::kDoor:
	
		DeurStatus(progdata);
		break;
	
	case AnimateID::kVoices:
	
		StemmenStatus(progdata);
		break;
	
	case AnimateID::kBarbecue:
	
		BarbecueStatus(progdata);
		break;
	
	case AnimateID::kTree:
	
		BoomStatus(progdata);
		break;
	
	case AnimateID::kGreenCrystal:
	
		GroenKristalStatus(progdata);
		break;
	
	case AnimateID::kComputer:
	
		ComputerStatus(progdata);
		break;
	
	case AnimateID::kDragonHead:
	
		DrakeKopStatus(progdata);
		break;
	
	case AnimateID::kLava:
	
		return LavaStatus(progdata);
	
	case AnimateID::kVacuum:
	
		PrintToMainWindow("Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een\n");
		PrintToMainWindow("verschrikkelijke pijn kraakt als een bliksem door je lijf. Je valt naar achte-\n");
		PrintToMainWindow("ren de grot uit, en daar val je even flauw.\n\n");

		progdata.status.lifepoints -= 4; //   Levenswond
		progdata.status.curroom = ROOM_SLANGENGROT; //   Grot terug
	
		return false;
	
	case AnimateID::kPaper:
	
		PapierStatus(progdata);
		break;
	
	case AnimateID::kNorthSwamp:
	case AnimateID::kMiddleSwamp:
	case AnimateID::kSouthSwamp:
	
		PrintToMainWindow("Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond\n");
		PrintToMainWindow("onder de voeten hebt. Ondanks je wilde pogingen boven te blijven zak je\n");
		PrintToMainWindow("langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa\n");
		PrintToMainWindow("zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie,\n");
		PrintToMainWindow("en na enige tijd verlies je je bewustzijn.\n");
		PrintToMainWindow("Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot.\n\n");

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
	
	case AnimateID::kMist:
	
		PrintToMainWindow("In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen\n");
		WriteToMainWindow(L"ziet. Je verliest je orïentatiegevoel en stommelt paniekerig door de grot, op\n");
		PrintToMainWindow("zoek naar een uitgang.\n");
		PrintToMainWindow("Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden,\n");
		PrintToMainWindow("struikel je voorover een andere grot in.\n\n");

		switch(GetRandomNumber(3))
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
	
	case AnimateID::kTeleporter:
	
		PrintToMainWindow("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het\n");
		PrintToMainWindow("plafond en tegen een van de wanden een enorm apparaat met een aantal\n");
		PrintToMainWindow("bedieningspanelen en beeldschermen.\n");
		PrintToMainWindow("Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal\n");
		PrintToMainWindow("in de grond, waarna een sirene begint te loeien. Van de schrik blijf je liggen,\n");
		PrintToMainWindow("en je ziet dat de lampen aan het plafond feller gaan branden en er grote\n");
		PrintToMainWindow("hoeveelheden data over de beeldschermen flitsen. Even later zie je een\n");
		PrintToMainWindow("oogverblindende flits en voel je je even gewichtloos.\n");
		PrintToMainWindow("Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\n");
		PrintToMainWindow("Sterker nog, je ligt buiten...\n\n");

		progdata.status.curroom = ROOM_BOS1;

		return false;
	}

	return true;
}

void HellehondStatus(Progdata &progdata)
{
	switch (progdata.living[kHellHound].status)
	{
	case 0:

		PrintToMainWindow("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe\n");
		PrintToMainWindow("tanden steken duidelijk af, en het rode kwijl druipt langzaam uit zijn bek.\n");
		PrintToMainWindow("Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel\n");
		PrintToMainWindow("klinkt een diep gegrom.\n\n");

		progdata.living[kHellHound].status++;

		break;

	case 1:

		PrintToMainWindow("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn\n");
		PrintToMainWindow("nagels boren zich in je vlees, en op een gegeven moment bijt hij je hard in je\n");
		PrintToMainWindow("schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. De\n");
		PrintToMainWindow("hond laat je los, en hij kijkt je grommend aan.\n\n");

		progdata.status.lifepoints--; //  Wond
		progdata.living[kHellHound].status++;

		break;

	case 2:

		PrintToMainWindow("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn\n");
		PrintToMainWindow("keel, en hij staat klaar om opnieuw aan te vallen.\n\n");

		progdata.living[kHellHound].status = GetRandomNumber(2) + 1;

		break;

	case 3:

		PrintToMainWindow("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je\n");
		PrintToMainWindow("deelt nog een slag uit, en een stuk vlees van de hond laat los.\n\n");

		progdata.items[ITEM_HONDVLEES].room = progdata.status.curroom;
		progdata.living[kHellHound].status++;

		break;

	case 4:

		PrintToMainWindow("De dode hellehond ligt in een bad van dampend bloed.\n\n");
		break;
	}
}

void RodeTrolStatus(Progdata &progdata)
{
	switch (progdata.living[kRedTroll].status)
	{
	case 0:

    	WriteToMainWindow(L"Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar geërgerd.\n\n");

		progdata.living[kRedTroll].status++;

		break;

	case 1:

		PrintToMainWindow("Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je\n");
		PrintToMainWindow("af.\n\n");

		progdata.living[kRedTroll].status++;

		break;

	case 2:

		PrintToMainWindow("De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn\n");
		PrintToMainWindow("tot je botten doordringen.\n\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[kRedTroll].status++;

		break;

	case 3:

		PrintToMainWindow("Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep.\n\n");

		progdata.living[kRedTroll].status = GetRandomNumber(2) + 2;

		break;

	case STATUS_RODETROL_BOEKJETHROWN:

		PrintToMainWindow("Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en\n");
		PrintToMainWindow("roder. Op een gegeven moment klinkt een geborrel op uit het wezen, en met een\n");
		PrintToMainWindow("klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol\n");
		PrintToMainWindow("langzaam naar beneden.\n");
		PrintToMainWindow("Opeens zie je iets glinsteren.\n\n");

		progdata.items[ITEM_ROODKRISTAL].room = progdata.status.curroom;
		progdata.living[kRedTroll].status++;

		break;

	case 5:

		PrintToMainWindow("Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm\n");
		PrintToMainWindow("zuigt aan je schoenen, en een vieze stank dringt in je neus.\n\n");

		break;
	}
}

void PlantStatus(Progdata &progdata)
{
	switch (progdata.living[kPlant].status)
	{
	case 0:

		PrintToMainWindow("In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit\n");
		PrintToMainWindow("in een afschrikwekkende kop, met afzichtelijke tanden. Hij heeft je gezien en\n");
		PrintToMainWindow("beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen\n");
		PrintToMainWindow("zetten zit je verstrengd in het monster, en zet de plant zijn tanden in je\n");
		PrintToMainWindow("nek.\n\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[kPlant].status = GetRandomNumber(2) + 1;

		break;

	case 1:

		PrintToMainWindow("De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek.\n");
		PrintToMainWindow("Met zijn groene oogjes kijkt hij je weer aan, en hij maakt aanstalten zijn\n");
		PrintToMainWindow("tanden opnieuw in je nek te zetten.\n\n");

		progdata.living[kPlant].status++;

		break;

	case 2:

		PrintToMainWindow("Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via\n");
		PrintToMainWindow("je rug naar beneden, en de pijn is nu ondraaglijk. Na een tijdje laat de plant\n");
		PrintToMainWindow("je weer los.\n\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[kPlant].status = GetRandomNumber(2) + 1;

		break;

	case STATUS_LIVING_DEAD:

		PrintToMainWindow("De resten van wat eerst een vleesetende plant was liggen nu op de grond van\n");
		PrintToMainWindow("de grot. Zijn bek ligt opengesperd, en zijn ogen rollen bijna uit zijn oogkas-\n");
		PrintToMainWindow("sen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\n");
		PrintToMainWindow("Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening.\n\n");

		progdata.rooms[ROOM_VERWAARLOOSDEGROT].connect[kNorth] = ROOM_SLIJMGROT; //	Maak verbinding met slijmgrot
		progdata.living[kPlant].status++;

		break;

	case 4:
		PrintToMainWindow("De vleesetende plant is niet veel meer dan een berg stinkend tuinafval.\n\n");

		break;
	}
}

void GnoeStatus(Progdata &progdata)
{
	switch (progdata.living[kGnu].status)
	{
	case 0:

		PrintToMainWindow("Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aan-\n");
		PrintToMainWindow("kijkt. Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende\n");
		PrintToMainWindow("beestjes, die je nog nooit eerder gezien hebt. Het beest verspreidt een\n");
		PrintToMainWindow("afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe.\n\n");

		progdata.living[kGnu].status++;

		break;

	case 1:

		PrintToMainWindow("De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je\n");
		PrintToMainWindow("hebt het gevoel alsof je longen uit je lijf worden geperst. Versuft sta je\n");
		PrintToMainWindow("weer op.\n\n");

		progdata.status.lifepoints--; //   Wond

		break;

	case STATUS_GNOE_GIFTIGVLEESFED:

		WriteToMainWindow(L"De gnoe ziet het vlees, snuffelt er aan, en slokt het in één hap naar binnen.\n");
		PrintToMainWindow("Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar\n");
		PrintToMainWindow("buiten. Hij zakt in elkaar en blijft roerloos liggen.\n\n");

		progdata.living[kGnu].status = STATUS_LIVING_DEAD;

		break;

	case STATUS_LIVING_DEAD:

		PrintToMainWindow("Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er\n");
		PrintToMainWindow("als een papje naast.\n\n");

		break;
	}
}

void DraakStatus(Progdata &progdata)
{
	switch (progdata.living[kDragon].status)
	{

	case 0:

		PrintToMainWindow("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je\n");
		PrintToMainWindow("allemaal bespieden met gele oogjes. Zijn hele huid is bedekt met schimmel, en\n");
		PrintToMainWindow("uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af drup-\n");
		PrintToMainWindow("pelt. Opeens komt uit een van de bekken een rommelend geluid. Met moeite\n");
		PrintToMainWindow("versta je \"Ben jij een koekie?\".\n\n");

		progdata.living[kDragon].status++;

		break;

	case 1:

		PrintToMainWindow("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig\n");
		PrintToMainWindow("te snuiven.\n");
		PrintToMainWindow("De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van\n");
		PrintToMainWindow("walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt\n");
		PrintToMainWindow("\"BEN JIJ EEN KOEKIE?!?\".\n\n");

		progdata.living[kDragon].status++;

		break;

	case 2:

		PrintToMainWindow("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzet-\n");
		PrintToMainWindow("tende harde klap. Er kraakt iets in je hoofd, en een duizeling maakt zich van\n");
		PrintToMainWindow("je meester. Hij maakt aanstalten je nog een klap te verkopen.\n\n");

		progdata.status.lifepoints--; //   Wond

		break;

	case STATUS_DRAAK_KOEKJETHROWN:

		PrintToMainWindow("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\n");
		PrintToMainWindow("Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\n");
		PrintToMainWindow("Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak\n");
		PrintToMainWindow("slaapt.\n\n");

		progdata.living[kDragon].status++;

		break;

	case STATUS_DRAAK_LIGHTSLEEPING:

		PrintToMainWindow("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn\n");
		PrintToMainWindow("lijf klinkt een diep gegrom.\n\n");

		break;

	case STATUS_DRAAK_SLAAPMUTSONHEAD:

		PrintToMainWindow("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts\n");
		PrintToMainWindow("steken af tegen de beschimmelde huid, en de muts zakt iets scheef. Op een ge-\n");
		PrintToMainWindow("geven moment valt er iets, en het klettert tegen de harde rotsvloer.\n\n");

		progdata.items[ITEM_GASPATROON].room = progdata.status.curroom;
		progdata.living[kDragon].status++;

		break;

	case 6:

		PrintToMainWindow("De draak slaapt rustig.\n\n");

		break;
	}
}

void GezwelStatus(Progdata &progdata)
{
	switch (progdata.living[kSwelling].status)
	{
	case 0:

		PrintToMainWindow("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je\n");
		PrintToMainWindow("aan met 2 gluiperige ogen, op zijn huid zitten schurftvlekken, en op zijn\n");
		PrintToMainWindow("mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich\n");
		PrintToMainWindow("vast aan alle wanden van de grot en verspert zo je weg.\n\n");

		progdata.living[kSwelling].status++;

		break;

	case 1:

		PrintToMainWindow("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.\n\n");

		break;

	case STATUS_GEZWEL_GASSED:
		if (progdata.items[ITEM_GASMASKER].room == STATUS_ITEM_OWNED)
		// gasmasker op
		{
			PrintToMainWindow("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n");
			PrintToMainWindow("Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen\n");
			PrintToMainWindow("overal scheuren in zijn schurfterige huid. Zijn tentakels komen langzaam met\n");
			PrintToMainWindow("een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in el-\n");
			PrintToMainWindow("kaar.\n\n");
		}
		else
		// geen masker... oeps!
		{
			PrintToMainWindow("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen,\n");
			PrintToMainWindow("voordat je zelf een kloppende hoofdpijn krijgt en onderuit gaat. Je hebt niets\n");
			PrintToMainWindow("om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer\n");
			PrintToMainWindow("bij.\n\n");

			progdata.status.lifepoints -= 4; //    Grote wond
		}

		progdata.rooms[ROOM_VLEERMUISGROT].connect[kNorth] = ROOM_VERDOEMENISGROT;
		progdata.living[kSwelling].status = STATUS_LIVING_DEAD;

		break;

	case STATUS_LIVING_DEAD:

		PrintToMainWindow("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn\n");
		PrintToMainWindow("maag kruipen pissebedden en oorkruipers. Er verspreidt zich een sterke rot-\n");
		PrintToMainWindow("lucht, en er ontstaat langzaam een klein slijmplasje.\n\n");

		break;
	}
}

void DeurStatus(Progdata &progdata)
{
	switch (progdata.living[kDoor].status)
	{
	case 0:

		PrintToMainWindow("In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet\n");
		PrintToMainWindow("meer open te krijgen.\n\n");

		break;

	case STATUS_DEUR_OPEN:

		WriteToMainWindow(L"Je zet één eind van het bot onder de deur, en op het andere begin je te duwen.\n");
		PrintToMainWindow("Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een\n");
		PrintToMainWindow("kier. Je geeft nog een duw, en langzaam draait de deur open.\n\n");

		progdata.rooms[ROOM_LEGEGROT45].connect[kNorth] = ROOM_VUILNISGROT;
		progdata.living[kDoor].status++;

		break;

	case 2:
		PrintToMainWindow("De deur is nu open, en geeft toegang tot een grot.\n\n");

		break;
	}
}

void StemmenStatus(Progdata &progdata)
{
	switch (progdata.living[kVoices].status)
	{
	case 0:

		PrintToMainWindow("Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan:\n");
		PrintToMainWindow("\"Wat schreeuwt is in z'n hart nog een kind\".\n");
		PrintToMainWindow("Dan is het weer stil.\n\n");

		progdata.living[kVoices].status++;

		break;

	case 1:

		PrintToMainWindow("Vanuit de verte hoor je zachte, lachende stemmetjes.\n\n");

		break;
	}
}

void BarbecueStatus(Progdata &progdata)
{
	switch (progdata.living[kBarbecue].status)
	{
	case STATUS_BARBECUE_INITIALBURN:

		PrintToMainWindow("Op deze open plek staat een barbecue gezellig te branden.\n\n");

		break;

	case STATUS_BARBECUE_HASJONFIRE:

		PrintToMainWindow("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt\n");
		PrintToMainWindow("er niets.\n\n");

		progdata.living[kBarbecue].status = STATUS_BARBECUE_INGREDIENTBURN;

		break;

	case STATUS_BARBECUE_VLEESONFIRE:

		PrintToMainWindow("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder\n");
		PrintToMainWindow("gebeurt er niets.\n\n");

		progdata.living[kBarbecue].status = STATUS_BARBECUE_INGREDIENTBURN;

		break;

	case STATUS_BARBECUE_INGREDIENTBURN:

		PrintToMainWindow("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.\n\n");

		break;

	case STATUS_BARBECUE_KOEKJEBAKING:

		WriteToMainWindow(L"Een grote rookontwikkeling treedt op wanneer het tweede ingrediënt in de\n");
		PrintToMainWindow("barbecue belandt.\n");
		WriteToMainWindow(L"Knetterend smelten de 2 ingrediënten om tot een koekje.\n\n");

		progdata.items[ITEM_KOEKJE].room = progdata.status.curroom;
		progdata.living[kBarbecue].status = STATUS_BARBECUE_INITIALBURN;

		break;
	}
}

void BoomStatus(Progdata &progdata)
{
	static const wchar_t *smeulendbos = L"Om je heen zie je de smeulende resten van wat eens bos was.";

	int i, j;

	switch (progdata.living[kTree].status)
	{
	case 0:

		PrintToMainWindow("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit\n");
		PrintToMainWindow("een bordje met daarop de tekst \"Roken en open vuur verboden\".\n\n");

		break;

	case STATUS_BOOM_SETONFIRE:

		PrintToMainWindow("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam\n");
		PrintToMainWindow("te branden, en weldra staat hij in lichterlaaie. De vlammen slaan om zich heen,\n");
		PrintToMainWindow("en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee,\n");
		PrintToMainWindow("en de hitte is enorm.\n\n");

		if (progdata.items[ITEM_HITTEPAK].room != STATUS_ITEM_OWNED)
		{
			PrintToMainWindow("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwon-\n");
			PrintToMainWindow("den op.\n\n");

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
		progdata.living[kGreenCrystal].status = 1;
		progdata.living[kTree].status++;

		break;

	case 2:

		PrintToMainWindow("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk\n");
		PrintToMainWindow("bord met daarop \"R   n e  op n v u  ver  d n\".\n\n");

		break;
	}
}

void GroenKristalStatus(Progdata &progdata)
{
	switch (progdata.living[kGreenCrystal].status)
	{
	case 0:

		WriteToMainWindow(L"Je struikelt over iets. Door de begroeïing zie je niet wat het is.\n\n");

		break;
	}
}

void ComputerStatus(Progdata &progdata)
{
	switch (progdata.living[kComputer].status)
	{
	case 0:

		PrintToMainWindow("Er staat een computer van het merk Beull die bestaat bestaat uit een kast met\n");
		PrintToMainWindow("een 3.5-inch drive en een monitor. Op de monitor staat: \"Datadisk invoeren\n");
		PrintToMainWindow("a.u.b.\".\n\n");

		progdata.living[kComputer].status++;

		break;

	case 1:

		PrintToMainWindow("De computer wacht nog steeds.\n\n");

		break;

	case STATUS_COMPUTER_READING:

		PrintToMainWindow("De drive begint te lezen en na korte tijd verschijnt er informatie op het\n");
		PrintToMainWindow("scherm. Er staat: \"In het onderste grottenstelsel moet men een letter-\n");
		PrintToMainWindow("route volgen die resulteert in de naam van het te vinden voorwerp.\".\n");
		PrintToMainWindow("Na even wordt het scherm zwart.\n\n");

		progdata.living[kComputer].status++;

		break;

	case 3:

		PrintToMainWindow("Er valt niets te zien op de monitor en de computer is stil.\n\n");

		break;
	}
}

void DrakeKopStatus(Progdata &progdata)
{
	switch (progdata.living[kDragonHead].status)
	{
	case 0:

		PrintToMainWindow("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een\n");
		PrintToMainWindow("geopende muil. Op de deur zit een zwaar slot.\n\n");

		break;

	case 1:

		PrintToMainWindow("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer\n");
		PrintToMainWindow("opengaat. Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te\n");
		PrintToMainWindow("gloeien.\n\n");

		progdata.living[kDragonHead].status++;

		break;

	case 2:

		PrintToMainWindow("De ogen van de draak blijven licht gloeien.\n\n");

		break;

	case 3:

		PrintToMainWindow("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het\n");
		PrintToMainWindow("kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.\n\n");

		progdata.living[kDragonHead].status++;
		break;

	case 4:

		PrintToMainWindow("De ogen van de draak blijven gloeien.\n\n");

		break;

	case 5:

		PrintToMainWindow("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft\n");
		PrintToMainWindow("hij dicht. De ogen beginnen nu steeds feller te gloeien. Op een gegeven moment\n");
		PrintToMainWindow("concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet\n");
		PrintToMainWindow("en wordt weerkaatst in een spiegel vlak achter je. De spiegel reflecteert het\n");
		PrintToMainWindow("licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\n");
		PrintToMainWindow("Daarna zwaait de deur langzaam met veel gepiep open.\n\n");

		progdata.rooms[ROOM_KLEINEGROT].connect[kNorth] = ROOM_HOOFDGROT;
		progdata.living[kDragonHead].status++;

		break;

	case 6:

		PrintToMainWindow("De zware deur is nu open en geeft toegang tot een ruimte.\n\n");

		break;
	}
}

bool LavaStatus(Progdata &progdata)
{
	switch (progdata.living[kLava].status)
	{
	case 0:

		if (progdata.items[ITEM_HITTEPAK].room == STATUS_ITEM_OWNED)
		{
			PrintToMainWindow("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke\n");
			PrintToMainWindow("damp, en een rode gloed verlicht de omtrek. De hitte is enorm, maar het hitte-\n");
			PrintToMainWindow("pak beschermt je tegen verbranding.\n\n");
		}
		else
		{
			PrintToMainWindow("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je\n");
			PrintToMainWindow("een aantal brandwonden oploopt en naar achteren wordt geblazen.\n\n");

			progdata.status.curroom = ROOM_OLIEGROT; //   Grot terug
			progdata.status.lifepoints -= 4; //   Levenswond

			return false;
		}

		return true;

	case STATUS_LAVA_BOMDROPPED:

		PrintToMainWindow("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt\n");
		PrintToMainWindow("de bom langzaam weg naar beneden. De lava begint op een gegeven moment vreemd\n");
		PrintToMainWindow("te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver-\n");
		PrintToMainWindow("blindende flits vanuit het lava. Daarna wordt het weer rustiger.\n\n");
		PrintToMainWindow("Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door\n");
		PrintToMainWindow("dit positronenwapen, waarvan de beginselen mede van jouw handen komen. Je mis-\n");
		PrintToMainWindow("sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het\n");
		PrintToMainWindow("grottenstelsel.\n\n");

		ForceExit();
	}

	return true;
}

void PapierStatus(Progdata &progdata)
{
	switch (progdata.living[kPaper].status)
	{
	case 0:

		PrintToMainWindow("Er zit een dicht, houten luik in het plafond. Je kunt er niet bij.\n\n");

		break;

	case STATUS_PAPIER_OPENING:

		PrintToMainWindow("Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden.\n\n");

		progdata.items[ITEM_PAPIERITEM].room = ROOM_RGROT;
		progdata.living[kPaper].status++;

		break;

	case 2:

		PrintToMainWindow("Het luik aan het plafond hangt nu open. Er zit een leeg gat.\n\n");

		break;
	}
}


