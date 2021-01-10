#include "include.h"

void RoomStatus(Progdata &progdata)
{
	_cprintf("Je bevindt je %s.\r\n", progdata.rooms[progdata.status.curroom].name);

	if (progdata.status.curroom != 61 && progdata.status.curroom != 31 && progdata.status.curroom >= 20 && !progdata.status.lamp)
		_cprintf("Het is stekedonker en je ziet geen hand voor ogen.\r\n");
	else
	{
		if (progdata.rooms[progdata.status.curroom].descript)
			_cprintf("%s\r\n", progdata.rooms[progdata.status.curroom].descript);
		ShowItems(progdata);
	}

	ShowDirString(progdata.rooms[progdata.status.curroom].connect);
	_cprintf("\r\n");
}

void ShowDirString(char *connect)
{
	int count = 0;
	int i;

	for (i = 0; i < 6; i++)
		if (connect[i] > -1)
			count++;

	if (!count)
		return;

	_cprintf("Je kunt naar ");

	for (i = 0; i < 6; i++)
		if (connect[i] > -1)
		{
			switch(i)
			{
			case DO_EAST:
				_cprintf("het oosten");
				break;
			case DO_WEST:
				_cprintf("het westen");
				break;
			case DO_NORTH:
				_cprintf("het noorden");
				break;
			case DO_SOUTH:
				_cprintf("het zuiden");
				break;
			case DO_UP:
				_cprintf("boven");
				break;
			case DO_DOWN:
				_cprintf("beneden");
				break;
			}
			switch(--count)
			{
			case 0:
				break;
			case 1:
				_cprintf(" en ");
				break;
			default:
				_cprintf(", ");
				break;
			}
		}

	_cprintf(".\r\n");
}

void ShowItems(Progdata &progdata)
{
	int count = 0;
	int i;

	for (i = 0; i < 25; i++)
		if (progdata.items[i].room == progdata.status.curroom)
			count++;

	if (count)
	{
		_cprintf("Hier lig%s ", count > 1 ? "gen" : "t");

		for (i = 0; i < 25; i++)
			if (progdata.items[i].room == progdata.status.curroom)
			{
				if (wherex() > 55)
					_cprintf("\r\n");
				_cprintf(progdata.items[i].name);

				switch(--count)
				{
				case 0:
					break;
				case 1:
					_cprintf(" en ");
					break;
				default:
					_cprintf(", ");
					break;
				}
			}

		_cprintf(".\r\n");
	}
}


bool LivingStatus(Progdata &progdata)
{
	int livingfound = -1;
	int i;

	for (i = 0; i < 21 && livingfound == -1; i++)
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
	case LIVING_DIAMANT:
		DiamantStatus(progdata);
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
		_cprintf("Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een\r\n"
				 "verschrikkelijke pijn kraakt als een bliksem door je lijf. Je valt naar achte-\r\n"
				 "ren de grot uit, en daar val je even flauw.\r\n\r\n");

		progdata.status.lifepoints -= 4; //   Levenswond
		progdata.status.curroom = 76; //   Grot terug
		return false;
	case LIVING_PAPIER:
		PapierStatus(progdata);
		break;
	case LIVING_NOORDMOERAS:
	case LIVING_MIDDENMOERAS:
	case LIVING_ZUIDMOERAS:
		_cprintf("Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond\r\n"
				  "onder de voeten hebt. Ondanks je wilde pogingen boven te blijven zak je\r\n"
				  "langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa\r\n"
				  "zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie,\r\n"
				  "en na enige tijd verlies je je bewustzijn.\r\n"
				  "Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot.\r\n\r\n");

		switch (progdata.status.curroom)
		{
		case 3:
			progdata.status.curroom = 51;
			break;
		case 8:
			progdata.status.curroom = 30;
			break;
		case 18:
			progdata.status.curroom = 47;
			break;
		}
		return false;
	case LIVING_MISTGROT:
		_cprintf("In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen\r\n"
              "ziet. Je verliest je or‹entatiegevoel en stommelt paniekerig door de grot, op\r\n"
				  "zoek naar een uitgang.\r\n"
				  "Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden,\r\n"
				  "struikel je voorover een andere grot in.\r\n\r\n");

		switch(random(3))
		{
		case 0:
			progdata.status.curroom = 36;
			break;
		case 1:
			progdata.status.curroom = 32;
			break;
		case 2:
			progdata.status.curroom = 38;
			break;
		}
		return false;
	case LIVING_TELEPORT:
		_cprintf("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het\r\n"
				  "plafond en tegen een van de wanden een enorm apparaat met een aantal\r\n"
				  "bedieningspanelen en beeldschermen.\r\n"
				  "Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal\r\n"
				  "in de grond, waarna een sirene begint te loeien. Van de schrik blijf je liggen,\r\n"
				  "en je ziet dat de lampen aan het plafond feller gaan branden en er grote\r\n"
				  "hoeveelheden data over de beeldschermen flitsen. Even later zie je een\r\n"
				  "oogverblindende flits en voel je je even gewichtloos.\r\n"
				  "Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\r\n"
				  "Sterker nog, je ligt buiten...\r\n\r\n");

		progdata.status.curroom = 1;
		return false;
	}
	return true;
}

void HellehondStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_HELLEHOND].status)
	{
	case 0:
		_cprintf("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe\r\n"
				 "tanden steken duidelijk af, en het rode kwijl druipt langzaam uit zijn bek.\r\n"
				 "Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel\r\n"
				 "klinkt een diep gegrom.\r\n\r\n");

		progdata.living[LIVING_HELLEHOND].status = 1;
		break;
	case 1:
		_cprintf("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn\r\n"
				 "nagels boren zich in je vlees, en op een gegeven moment bijt hij je hard in je\r\n"
				 "schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. De\r\n"
				 "hond laat je los, en hij kijkt je grommend aan.\r\n\r\n");

		progdata.status.lifepoints--; //  Wond
		progdata.living[LIVING_HELLEHOND].status = 2;
		break;
	case 2:
		_cprintf("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn\r\n"
				 "keel, en hij staat klaar om opnieuw aan te vallen.\r\n\r\n");

		progdata.living[LIVING_HELLEHOND].status = random(2) + 1;
		break;
	case 3:
		_cprintf("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je\r\n"
				 "deelt nog een slag uit, en een stuk vlees van de hond laat los.\r\n\r\n");

		progdata.items[ITEM_HONDVLEES].room = progdata.status.curroom;
		progdata.living[LIVING_HELLEHOND].status = 4;
		break;
	case 4:
		_cprintf("De dode hellehond ligt in een bad van dampend bloed.\r\n\r\n");
		break;
	}
}

void RodeTrolStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_RODETROL].status)
	{
	case 0:
      _cprintf("Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar ge‰rgerd.\r\n\r\n");

		progdata.living[LIVING_RODETROL].status = 1;
		break;
	case 1:
		_cprintf("Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je\r\n"
				 "af.\r\n\r\n");

		progdata.living[LIVING_RODETROL].status = 2;
		break;
	case 2:
		_cprintf("De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn\r\n"
				 "tot je botten doordringen.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[LIVING_RODETROL].status = 3;
		break;
	case 3:
		_cprintf("Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep.\r\n\r\n");

		progdata.living[LIVING_RODETROL].status = random(2) + 2;
		break;
	case 4:
		_cprintf("Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en\r\n"
				 "roder. Op een gegeven moment klinkt een geborrel op uit het wezen, en met een\r\n"
				 "klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol\r\n"
				 "langzaam naar beneden.\r\n"
				 "Opeens zie je iets glinsteren.\r\n\r\n");

		progdata.items[ITEM_ROODKRISTAL].room = progdata.status.curroom;
		progdata.living[LIVING_RODETROL].status = 5;
		break;
	case 5:
		_cprintf("Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm\r\n"
				 "zuigt aan je schoenen, en een vieze stank dringt in je neus.\r\n\r\n");

		break;
	}
}

void PlantStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_PLANT].status)
	{
	case 0:
		_cprintf("In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit\r\n"
				 "in een afschrikwekkende kop, met afzichtelijke tanden. Hij heeft je gezien en\r\n"
				 "beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen\r\n"
				 "zetten zit je verstrengd in het monster, en zet de plant zijn tanden in je\r\n"
				 "nek.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[LIVING_PLANT].status = random(2) + 1;
		break;
	case 1:
		_cprintf("De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek.\r\n"
				 "Met zijn groene oogjes kijkt hij je weer aan, en hij maakt aanstalten zijn\r\n"
				 "tanden opnieuw in je nek te zetten.\r\n\r\n");

		progdata.living[LIVING_PLANT].status = 2;
		break;
	case 2:
		_cprintf("Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via\r\n"
				 "je rug naar beneden, en de pijn is nu ondraaglijk. Na een tijdje laat de plant\r\n"
				 "je weer los.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		progdata.living[LIVING_PLANT].status = random(2) + 1;
		break;
	case 3:
		_cprintf("De resten van wat eerst een vleesetende plant was liggen nu op de grond van\r\n"
				 "de grot. Zijn bek ligt opengesperd, en zijn ogen rollen bijna uit zijn oogkas-\r\n"
				 "sen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\r\n"
				 "Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening.\r\n\r\n");

		progdata.rooms[25].connect[DO_NORTH] = 20; //	Maak verbinding met slijmgrot
		progdata.living[LIVING_PLANT].status = 4;
		break;
	case 4:
		_cprintf("De vleesetende plant is niet veel meer dan een berg stinkend tuinafval.\r\n\r\n");

		break;
	}
}

void GnoeStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_GNOE].status)
	{
	case 0:
		_cprintf("Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aan-\r\n"
				 "kijkt. Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende\r\n"
				 "beestjes, die je nog nooit eerder gezien hebt. Het beest verspreidt een\r\n"
				 "afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe.\r\n\r\n");

		progdata.living[LIVING_GNOE].status = 1;
		break;
	case 1:
		_cprintf("De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je\r\n"
				 "hebt het gevoel alsof je longen uit je lijf worden geperst. Versuft sta je\r\n"
				 "weer op.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		break;
	case 2:
      _cprintf("De gnoe ziet het vlees, snuffelt er aan, en slokt het in ‚‚n hap naar binnen.\r\n"
				 "Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar\r\n"
				 "buiten. Hij zakt in elkaar en blijft roerloos liggen.\r\n\r\n");

		progdata.living[LIVING_GNOE].status = 3;
		break;
	case 3:
		_cprintf("Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er\r\n"
				 "als een papje naast.\r\n\r\n");

		break;
	}
}

void DraakStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_DRAAK].status)
	{
	case 0:
		_cprintf("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je\r\n"
				 "allemaal bespieden met gele oogjes. Zijn hele huid is bedekt met schimmel, en\r\n"
				 "uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af drup-\r\n"
				 "pelt. Opeens komt uit een van de bekken een rommelend geluid. Met moeite\r\n"
				 "versta je \"Ben jij een koekie?\".\r\n\r\n");

		progdata.living[LIVING_DRAAK].status = 1;
		break;
	case 1:
		_cprintf("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig\r\n"
				 "te snuiven.\r\n"
				 "De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van\r\n"
				 "walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt\r\n"
				 "\"BEN JIJ EEN KOEKIE?!?\".\r\n\r\n");

		progdata.living[LIVING_DRAAK].status = 2;
		break;
	case 2:
		_cprintf("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzet-\r\n"
				 "tende harde klap. Er kraakt iets in je hoofd, en een duizeling maakt zich van\r\n"
				 "je meester. Hij maakt aanstalten je nog een klap te verkopen.\r\n\r\n");

		progdata.status.lifepoints--; //   Wond
		break;
	case 3:
		_cprintf("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\r\n"
				 "Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\r\n"
				 "Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak\r\n"
				 "slaapt.\r\n\r\n");

		progdata.living[LIVING_DRAAK].status = 4;
		break;
	case 4:
		_cprintf("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn\r\n"
				 "lijf klinkt een diep gegrom.\r\n\r\n");

		break;
	case 5:
		_cprintf("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts\r\n"
				 "steken af tegen de beschimmelde huid, en de muts zakt iets scheef. Op een ge-\r\n"
				 "geven moment valt er iets, en het klettert tegen de harde rotsvloer.\r\n\r\n");

		progdata.items[ITEM_GASPATROON].room = progdata.status.curroom;
		progdata.living[LIVING_DRAAK].status = 6;
		break;
	case 6:
		_cprintf("De draak slaapt rustig.\r\n\r\n");

		break;
	}
}

void GezwelStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_GEZWEL].status)
	{
	case 0:
		_cprintf("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je\r\n"
				 "aan met 2 gluiperige ogen, op zijn huid zitten schurftvlekken, en op zijn\r\n"
				 "mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich\r\n"
				 "vast aan alle wanden van de grot en verspert zo je weg.\r\n\r\n");

		progdata.living[LIVING_GEZWEL].status = 1;
		break;
	case 1:
		_cprintf("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.\r\n\r\n");

		break;
	case 2:
		if (progdata.items[ITEM_GASMASKER].room == -2)
		// gasmasker op
		{
			_cprintf("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\r\n"
					 "Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen\r\n"
					 "overal scheuren in zijn schurfterige huid. Zijn tentakels komen langzaam met\r\n"
					 "een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in el-\r\n"
					 "kaar.\r\n\r\n");
		}
		else
		// geen masker... oeps!
		{
			_cprintf("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen,\r\n"
					 "voordat je zelf een kloppende hoofdpijn krijgt en onderuit gaat. Je hebt niets\r\n"
					 "om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer\r\n"
					 "bij.\r\n\r\n");

			progdata.status.lifepoints -= 4; //    Grote wond
		}
		progdata.rooms[75].connect[DO_NORTH] = 70;
		progdata.living[LIVING_GEZWEL].status = 4;
		break;
	case 4:
		_cprintf("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn\r\n"
				 "maag kruipen pissebedden en oorkruipers. Er verspreidt zich een sterke rot-\r\n"
				 "lucht, en er ontstaat langzaam een klein slijmplasje.\r\n\r\n");

		break;
	}
}

void DeurStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_DEUR].status)
	{
	case 0:
		_cprintf("In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet\r\n"
				 "meer open te krijgen.\r\n\r\n");

		break;
	case 1:
		_cprintf("Je zet 1 eind van het bot onder de deur, en op het andere begin je te duwen.\r\n"
				 "Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een\r\n"
				 "kier. Je geeft nog een duw, en langzaam draait de deur open.\r\n\r\n");

		progdata.rooms[45].connect[DO_NORTH] = 40;
		progdata.living[LIVING_DEUR].status = 2;
		break;
	case 2:
		_cprintf("De deur is nu open, en geeft toegang tot een grot.\r\n\r\n");

		break;
	}
}

void StemmenStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_STEMMEN].status)
	{
	case 0:
		_cprintf("Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan:\r\n"
				 "\"Wat schreeuwt is in z'n hart nog een kind\".\r\n"
				 "Dan is het weer stil.\r\n\r\n");

		progdata.living[LIVING_STEMMEN].status = 1;
		break;
	case 1:
		_cprintf("Vanuit de verte hoor je zachte, lachende stemmetjes.\r\n\r\n");

		break;
	}
}

void BarbecueStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_BARBECUE].status)
	{
	case 0:
		_cprintf("Op deze open plek staat een barbecue gezellig te branden.\r\n\r\n");

		break;
	case 1:
		_cprintf("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt\r\n"
				  "er niets.\r\n\r\n");

		progdata.living[LIVING_BARBECUE].status = 3;
		break;
	case 2:
		_cprintf("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder\r\n"
				  "gebeurt er niets.\r\n\r\n");

		progdata.living[LIVING_BARBECUE].status = 3;
		break;
	case 3:
		_cprintf("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.\r\n\r\n");

		break;
	case 4:
      _cprintf("Een grote rookontwikkeling treedt op wanneer het tweede ingredi‰nt in de\r\n"
				  "barbecue belandt.\r\n"
             "Knetterend smelten de 2 ingredi‰nten om tot een koekje.\r\n\r\n");

		progdata.items[ITEM_KOEKJE].room = progdata.status.curroom;
		progdata.living[LIVING_BARBECUE].status = 0;
		break;
	}
}

void BoomStatus(Progdata &progdata)
{
	static const char *smeulendbos = "Om je heen zie je de smeulende resten van wat eens bos was.";
	int i, j;

	switch (progdata.living[LIVING_BOOM].status)
	{
	case 0:
		_cprintf("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit\r\n"
				 "een bordje met daarop de tekst \"Roken en open vuur verboden\".\r\n\r\n");

		break;
	case 1:
		_cprintf("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam\r\n"
				 "te branden, en weldra staat hij in lichterlaaie. De vlammen slaan om zich heen,\r\n"
				 "en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee,\r\n"
				 "en de hitte is enorm.\r\n\r\n");

		if (progdata.items[ITEM_HITTEPAK].room != -2)
		{
			_cprintf("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwon-\r\n"
					 "den op.\r\n\r\n");

			progdata.status.lifepoints -= 4; //   Levenswond
		}

		for (i = 0; i < 20; i += 5)
			for (j = 0; j < 2; j++)
				if (i + j != 6)
					progdata.rooms[i + j].descript = smeulendbos;
		progdata.rooms[2].descript = smeulendbos;
		progdata.rooms[4].descript = smeulendbos;
		progdata.rooms[7].descript = smeulendbos;

		progdata.items[ITEM_GROENKRISTAL].room = 4;
		progdata.living[LIVING_DIAMANT].status = 1;
		progdata.living[LIVING_BOOM].status = 2;
		break;
	case 2:
		_cprintf("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk\r\n"
				 "bord met daarop \"R   n e  op n v u  ver  d n\".\r\n\r\n");

		break;
	}
}

void DiamantStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_DIAMANT].status)
	{
	case 0:
      _cprintf("Je struikelt over iets. Door de begroe‹ing zie je niet wat het is.\r\n\r\n");

		break;
	}
}

void ComputerStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_COMPUTER].status)
	{
	case 0:
		_cprintf("Er staat een computer van het merk Beull die bestaat bestaat uit een kast met\r\n"
				 "een 3.5-inch drive en een monitor. Op de monitor staat: \"Datadisk invoeren\r\n"
				 "a.u.b.\".\r\n\r\n");

		progdata.living[LIVING_COMPUTER].status = 1;
		break;
	case 1:
		_cprintf("De computer wacht nog steeds.\r\n\r\n");

		break;
	case 2:
		_cprintf("De drive begint te lezen en na korte tijd verschijnt er informatie op het\r\n"
				 "scherm. Er staat: \"In het onderste grottenstelsel moet men een letter-\r\n"
				 "route volgen die resulteert in de naam van het te vinden voorwerp.\".\r\n"
				 "Na even wordt het scherm zwart.\r\n\r\n");

		progdata.living[LIVING_COMPUTER].status = 3;
		break;
	case 3:
		_cprintf("Er valt niets te zien op de monitor en de computer is stil.\r\n\r\n");

		break;
	}
}

void DrakeKopStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_DRAKEKOP].status)
	{
	case 0:
		_cprintf("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een\r\n"
				 "geopende muil. Op de deur zit een zwaar slot.\r\n\r\n");

		break;
	case 1:
		_cprintf("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer\r\n"
				 "opengaat. Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te\r\n"
				 "gloeien.\r\n\r\n");

		progdata.living[LIVING_DRAKEKOP].status = 2;
		break;
	case 2:
		_cprintf("De ogen van de draak blijven licht gloeien.\r\n\r\n");

		break;
	case 3:
		_cprintf("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het\r\n"
				 "kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.\r\n\r\n");

		progdata.living[LIVING_DRAKEKOP].status = 4;
		break;
	case 4:
		_cprintf("De ogen van de draak blijven gloeien.\r\n\r\n");

		break;
	case 5:
		_cprintf("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft\r\n"
				 "hij dicht. De ogen beginnen nu steeds feller te gloeien. Op een gegeven moment\r\n"
				 "concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet\r\n"
				 "en wordt weerkaatst in een spiegel vlak achter je. De spiegel reflecteert het\r\n"
				 "licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\r\n"
				 "Daarna zwaait de deur langzaam met veel gepiep open.\r\n\r\n");

		progdata.rooms[32].connect[DO_NORTH] = 27;
		progdata.living[LIVING_DRAKEKOP].status = 6;
		break;
	case 6:
		_cprintf("De zware deur is nu open en geeft toegang tot een ruimte.\r\n\r\n");

		break;
	}
}

bool LavaStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_LAVA].status)
	{
	case 0:
		if (progdata.items[ITEM_HITTEPAK].room == -2)
			_cprintf("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke\r\n"
					 "damp, en een rode gloed verlicht de omtrek. De hitte is enorm, maar het hitte-\r\n"
					 "pak beschermt je tegen verbranding.\r\n\r\n");
		else
		{
			_cprintf("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je\r\n"
					 "een aantal brandwonden oploopt en naar achteren wordt geblazen.\r\n\r\n");

			progdata.status.curroom = 54; //   Grot terug
			progdata.status.lifepoints -= 4; //   Levenswond
			return false;
		}
		return true;
	case 1:
		_cprintf("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt\r\n"
				 "de bom langzaam weg naar beneden. De lava begint op een gegeven moment vreemd\r\n"
				 "te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver-\r\n"
				 "blindende flits vanuit het lava. Daarna wordt het weer rustiger.\r\n\r\n"
				 "Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door\r\n"
				 "dit positronenwapen, waarvan de beginselen mede van jouw handen komen. Je mis-\r\n"
				 "sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het\r\n"
				 "grottenstelsel.\r\n\r\n");

		ForceExit();
	}
	return true;
}

void PapierStatus(Progdata &progdata)
{
	switch (progdata.living[LIVING_PAPIER].status)
	{
	case 0:
		_cprintf("Er zit een dicht, houten luik in het plafond. Je kunt er niet bij.\r\n\r\n");

		break;
	case 1:
		_cprintf("Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden.\r\n\r\n");

		progdata.items[ITEM_PAPIERITEM].room = 66;
		progdata.living[LIVING_PAPIER].status = 2;
		break;
	case 2:
		_cprintf("Het luik aan het plafond hangt nu open. Er zit een leeg gat.\r\n\r\n");

		break;
	}
}


