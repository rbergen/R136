#include "base.h"
#include "console.h"
#include "animates.h"
#include "items.h"
#include "constants.h"
#include "startup.h"
#include "general.h"
#include <algorithm>
#include <ctime>
#include <functional>
#include <memory>
#include <iostream>

namespace startup
{
	namespace 
	{
		#define in_the_forest std::vector<wstring>{ L"in het bos", L"in the forest" }
		#define in_the_swamp std::vector<wstring>{ L"in het moeras", L"in the swamp" }
		#define at_an_open_space std::vector<wstring>{ L"op een open plek", L"at an open space" }
		#define	in_an_empty_cave std::vector<wstring>{ L"in een lege grot", L"in an empty cave" }
		#define	in_a_stairwell_cave std::vector<wstring>{ L"in een wenteltrapgrot", L"in a stairwell cave" }

		#define smelly_surface std::vector<wstring>{ \
			L"Er hangt een griezelige nevel over het stinkende oppervlak." \
		, \
			L"A creepy mist hangs over the smelly surface." \
		}
		
		#define	other_levels std::vector<wstring>{ \
			L"In deze grot bevindt zich een grote, stenen wenteltrap die waarschijnlijk naar andere niveaus leidt." \
		, \
			L"There is a large, circular stairwell that is made out of stone. It looks like it leads to other levels." \
		}

		std::unique_ptr<Room> rooms[] { // { names, descriptions }
			std::make_unique<Forest>(
				in_the_forest,
				std::vector<wstring>{
					L"Je bevindt je in een uithoek van een donker bos. Overal hoor je enge geluiden.", 
					L"This is the far corner of a dark forest. Scary sounds come from every direction." 
				}
			),
			std::make_unique<Forest>(
				in_the_forest,
				std::vector<wstring>{
					L"Aan de zuidkant zie je een hek dat toegang geeft tot een donkere plaats.",
					L"Towards the south, you see a gate that gives access to a dark place."
				}
			),
			std::make_unique<Forest>(
				in_the_forest,
				std::vector<wstring>{
					L"Er komt een modderige geur uit het oosten.",
					L"There is a muddy smell coming from the east."
				}
			),
			std::make_unique<Outdoor>(in_the_swamp, smelly_surface),
			std::make_unique<Forest>(
				in_the_forest,
				std::vector<wstring>{
					L"Er komt een modderige geur uit het westen."
					L"There is a muddy smell coming from the west."
				}
			),
			std::make_unique<Forest>(
				in_the_forest,
				std::vector<wstring>{
					L"Pas op voor de laaghangende takken!",
					L"Mind the low-hanging branches!"
				}
			),
			std::make_unique<Outdoor>(
				std::vector <wstring>{ L"op de begraafplaats", L"at the cemetery" },
				std::vector <wstring>{
					L"Een lucht van rottend vlees dringt in je neus. Je denkt dat je een grafsteen ziet bewegen.",
					L"The smell of rotting flesh creeps up your nose. You think you see a tombstone move."
				}
			),
			std::make_unique<Forest>(in_the_forest),
			std::make_unique<Outdoor>(in_the_swamp,	smelly_surface),
			std::make_unique<Outdoor>(
				at_an_open_space,
				std::vector<wstring>{
					L"Er komt een modderige geur uit het westen.",
					L"There is a muddy smell coming from the west."
				}
			),
			std::make_unique<Forest>(in_the_forest),
			std::make_unique<Forest>(
				in_the_forest,
				std::vector<wstring>{
					L"Je trapt bijna in een berenklem.",
					L"You almost step into a bear trap."
				}
			),
			std::make_unique<Outdoor>(
				at_an_open_space,
				std::vector<wstring>{
					L"Door de mist zie je nog net de omtrekken van het donkere bos.",
					L"Through the mist you can just make out the outline of the dark forest."
				}
			),
			std::make_unique<Outdoor>(
				std::vector<wstring>{ L"op het moeraspad", L"on the swamp path" },
				std::vector<wstring>{
					L"Er ligt hier een skelet, waarschijnlijk een van je voorgangers.",
					L"There's a skeleton here, probably one of your predecessors."
				}
			),
			std::make_unique<Outdoor>(
				at_an_open_space,
				std::vector<wstring>{
					L"Bij het licht van een halve maan onderscheid je nog net de vorm van een galg.",
					L"In the light of a half moon you can just make out the shape of a gallow."
				}
			),
			std::make_unique<Forest>(
				in_the_forest,
				std::vector<wstring>{
					L"In de verte hoor je het trieste gehuil van een weerwolf.",
					L"In the distance you hear the sad howl of a werewolf."
				}
			),
			std::make_unique<Forest>(in_the_forest),
			std::make_unique<Outdoor>(
				at_an_open_space,
				std::vector<wstring>{
					L"Er ligt hier een dood konijn dat wordt belaagd door vliegen.",
					L"There's a dead rabbit on the ground that's being attacked by flies."
				}
			),
			std::make_unique<Outdoor>(in_the_swamp,	smelly_surface),
			std::make_unique<Indoor>(
				std::vector<wstring>{ L"in de ruïne", L"in the ruins" },
				std::vector<wstring>{
					L"De ruïne is een spookachtige bouwval. Er is hier een wankele trap die naar beneden leidt.",
					L"The ruins are a spooky rubble. There is a shaky staircase that leads downwards."
				}
			),

			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de slijmgrot", L"in the slime cave" },
				std::vector<wstring>{
					L"De wanden van deze grot zijn bekleed met een snotachtig slijm.",
					L"The walls of the cave are covered in a snotty slime."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de zwarte grot", L"in the black cave" },
				std::vector<wstring>{
					L"Je ziet geen hand voor ogen.",
					L"You can't see your hand in front of your face."
				}
			),
			std::make_unique<Cave>(std::vector <wstring>{ L"in de drugsgrot", L"in the drugs cave" }),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de geile grot", L"in the horny cave", },
				std::vector<wstring>{
					L"Aan de muren hangen gelige, gescheurde Playboy-posters.",
					L"Affixed to the wall are yellow, torn Playboy posters."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de dwangbuisgrot", L"in the straitjacket cave" },
				std::vector<wstring>{
					L"Er hangt hier een dwangbuis, met daarin een verminkt lijk.",
					L"There's a straitjacket hanging from the ceiling, with a mutilated body in it."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in een verwaarloosde grot", L"in a neglected cave" }),
			std::make_unique<Cave>(in_an_empty_cave),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de hoofdgrot", L"in the main cave" },
				std::vector<wstring>{
					L"Er staat hier een batterij aan mysterieuze apparatuur.",
					L"There is a battery of mysterious equipment, here."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de hiërogliefengrot", L"in the hieroglyphs cave" },
				std::vector<wstring>{
					L"Op de wanden staan hiërogliefen waar je geen wijs uit wordt.",
					L"There are symbols on the walls that you can not make sense of."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de stankgrot", L"in the stench cave" },
				std::vector<wstring>{
					L"Er hangt hier een smerige lucht die je herinnert aan de zware lucht van een beerput.",
					L"The filthy stench that lingers here reminds you of the heavy smell of a cesspool."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in een troosteloze grot", L"in a disconsolate cave" }),
			std::make_unique<Indoor>(
				std::vector<wstring>{ L"in de TL-grot", L"in the fluorescent cave" },
				std::vector<wstring>{
					L"De grot wordt zwak verlicht door een lichtbron die hoog aan het plafond hangt.",
					L"The cave is weakly lit by a light source that hangs high at the ceiling."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in een kleine grot", L"in a small cave" }),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de ijsgrot", L"in the ice cave" },
				std::vector<wstring>{
					L"In deze grot lijkt het net of alles van ijs is, en je krijgt rillingen.",
					L"In this cave everything looks like it is made out of ice. It gives you the shivers."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de kaktusgrot", L"in the cactus cave", },
				std::vector<wstring>{
					L"Je bent omringd door giftige kaktussen die in deze grot staan.",
					L"You're surrounded by poisonous cactuses that are present in this cave."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de stalagmietengrot", L"in the stalagmite cave" },
				std::vector<wstring>{
					L"Hier zie je een traliewerk van stalagmieten.",
					L"You see a railing of stalagmites."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de stormgrot", L"in the storm cave" },
				std::vector<wstring>{
					L"Door deze grot loeit een harde wind, waardoor je je vast moet grijpen aan een van de wanden.",
					L"A hard wind blows through this cave that makes you hold on to one of the walls."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de mistgrot", L"in the mist cave" }),
			std::make_unique<Cave>(in_a_stairwell_cave, other_levels),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de tentakelgrot", L"in the tentacle cave" },
				std::vector<wstring>{
					L"Van alle kanten komen grote tentakels die je aftasten en groene sporen op je huid achterlaten.",
					L"Large tentacles come from all directions. They scan your body and leave green traces on your skin."
				}
			),

			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de vuilnisgrot", L"in the garbage cave" },
				std::vector<wstring>{
					L"In deze grot ligt een grote stapel rottende etensresten. De stank is bijna ondraaglijk.",
					L"There is large pile of rotting food remains in this cave. The stench is almost unbearable."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de echogrot", L"in the echo cave" },
				std::vector<wstring>{
					L"Hier worden alle geluiden die je maakt tegen de wanden geëcho'd.",
					L"All sounds you make echo back from the walls."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de geheime grot", L"in the secret cave" },
				std::vector<wstring>{
					L"Op de grond van deze grot liggen allerlei onbekende en geheimzinnige voorwerpen.",
					L"On the floor of the cave there's a wide range of unfamiliar and mysterious objects."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de voedselgrot", L"in the food cave" },
				std::vector<wstring>{
					L"Zo te ruiken is dit waarschijnlijk eens een keuken geweest...",
					L"It smells like this probably was a kitchen at some point..."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de grot van de gnoe", L"in the cave of the gnu" },
				std::vector<wstring>{
					L"Hier liggen de geraamtes van wezens die eerder ten prooi zijn gevallen aan de gnoe.",
					L"Scattered around are skeletons of creatures that fell prey to the gnu before."
				}
			),
			std::make_unique<Cave>(in_an_empty_cave),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de ogengrot", L"in the eye cave" },
				std::vector<wstring>{
					L"Van alle kanten wordt je bespied door rode, bloeddoorlopen ogen die precies volgen wat je doet.",
					L"From all angles you are looked at by red, blood-shot eyes that precisely follow your actions."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de rotsgrot", L"in the rock cave" },
				std::vector<wstring>{
					L"Overal zie je hier scherpe rotspunten. Aan een aantal ervan zitten bruine korsten.",
					L"You see sharp rock edges everywhere. Brown crusts are attached to some of them."
				}
			),
			std::make_unique<Outdoor>(std::vector<wstring>{ L"in de leegte", L"in the emptiness" }),
			std::make_unique<Outdoor>(
				std::vector<wstring>{ L"op de zandbank", L"at the sandbank" },
				std::vector<wstring>{
					L"Op de vloer liggen vreemde patronen, gevormd uit verschillende soorten zand.",
					L"On the ground you see strange patterns, made out of different types of sand."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de martelgrot", L"in the torture cave" },
				std::vector<wstring>{
					L"Onder de vage schemering van de martelvuren zie je nog net een duimschroef en wat stekelige voorwerpen waar nog wat bloed aan zit.",
					L"Under the vague shimmer of the torture fires, you can just see a thumbscrew and some pointy objects that still have some blood attached to them."
				}
			),
			std::make_unique<Cave>(in_an_empty_cave),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de veilige grot", L"in the safe cave" },
				std::vector<wstring>{
					L"Dit is de enige grot waar je je een beetje veilig voelt.",
					L"This is the only cave in which you feel some safety."
				}
			),
			std::make_unique<Outdoor>(
				std::vector<wstring>{ L"in de nauwe rotsspleet", L"in the narrow cleft" },
				std::vector<wstring>{
					L"Aan alle kanten wordt je omringd door hoge rotsmuren. Alleen in het westen zie je een opening.",
					L"You're surrounded by high rock walls at all sides. You only see an opening at the western side."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de oliegrot", L"in the oil cave" },
				std::vector<wstring>{
					L"Vanuit het zuiden verspreidt zich een enorme hitte, die in deze grot nog net draaglijk is.",
					L"An enormous heat spreads from the south that is only just bearable in this cave."
				}
			),
			std::make_unique<Cave>(in_an_empty_cave),
			std::make_unique<Cave>(in_a_stairwell_cave, other_levels),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de spinnengrot", L"in the spider cave" },
				std::vector<wstring>{
					L"Het wemelt hier van de tarantula's. Bij elke stap die je zet hoor je het onder je voeten kraken, en ze kruipen langs je benen omhoog.",
					L"It's teeming with tarantulas, here. You hear crunching with every step you take, and you feel them crawling up your legs."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de pratende grot", L"in the talking cave" }),
			std::make_unique<Cave>(std::vector<wstring>{ L"op de lavaput", L"at the lava pit" }),

			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de skoebiegrot", L"in the scooby cave" },
				std::vector<wstring>{
					L"Uit alle richtingen komen rare geluiden, als in een gesticht.",
					L"Weird noises come from all directions, as if in a mental institution."
				}
			),
			std::make_unique<Indoor>(
				std::vector<wstring>{ L"in de radioactieve grot", L"in the radioactive cave" },
				std::vector<wstring>{
					L"Door de hoge radioactiviteit is deze grot zwak verlicht.",
					L"Due to the high level of radioactivity, this cave is dimly lit."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de i-grot", L"in the second t cave" }),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de p-grot", L"in the first t cave" }),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de a-grot", L"in the first e cave" },
				std::vector<wstring>{
					L"In deze grot bevindt zich het stenen beeld van een oud, jou onbekend wezen.",
					L"This caves houses the stone statue of an old creature that is unfamiliar to you."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de dodengrot", L"in the cave of death" },
				std::vector<wstring>{
					L"De naam van deze grot spreekt voor zich...",
					L"The name of this cave speaks for itself..."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de r-grot", L"in the r cave" }),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de e-grot", L"in the second e cave" }),
			std::make_unique<Cave>(in_a_stairwell_cave, other_levels),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de P-grot", L"in the L cave" }),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de grot der verdoemenis", L"in the damnation cave" },
				std::vector<wstring>{
					L"In deze grot heerst een haast verstikkende sfeer, en je voelt je niet prettig.",
					L"An almost suffocating atmosphere dominates this cave. You don't feel comfortable here."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de vacuumgrot", L"in the vacuum cave" }),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de rode grot", L"in the red cave" }),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de neongrot", L"in the neon cave" },
				std::vector<wstring>{
					L"Deze grot is fel gekleurd. Er staan patronen die je doen denken aan zwarte magie.",
					L"This cave is brightly coloured. There are patterns that remind you of black magic."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de bloedgrot", L"in the blood cave" },
				std::vector<wstring>{
					L"Het geraamte van een groot beest ligt hier op de grond en een aantal ingewanden liggen er naast.",
					L"There's a skeleton of a large beast on the ground, and some of its guts are next to it."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de vleermuisgrot", L"in the bat cave" },
				std::vector<wstring>{
					L"In deze grot fladderen overal vleermuizen, op zoek naar hun prooi.",
					L"Bats are fluttering everywhere in this cave, looking for their prey."
				}
			),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de slangengrot", L"in the snake cave" },
				std::vector<wstring>{
					L"Je hoort het geluid van een ratelslang. Bij de weg naar het noorden staat een doodskop getekend, die een gevaar aanduidt.",
					L"You hear the sound of a rattle-snake. At the northern end there's a drawing of a skull, signifying danger."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de kwabbengrot", L"in the lobe cave" }),
			std::make_unique<Cave>(
				std::vector<wstring>{ L"in de glibbergrot", L"in the slippery cave" },
				std::vector<wstring>{
					L"Je glijdt bijna uit over de zeepachtige prut die overal in de grot ligt. Tussen de glibberige massa steekt een paal omhoog met daarop een pijl die naar het oosten wijst.",
					L"You nearly slip over the soap-like goo that is everywhere in this cave. Somewhere in the slippery mass, a pole sticks up that has an arrow attached to it, which points east."
				}
			),
			std::make_unique<Cave>(std::vector<wstring>{ L"in de teleportgrot", L"in the teleport cave" })
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

		std::unique_ptr<Animate> animates[] { // { room, strike }
			std::make_unique<HellHound>(RoomID::forest2, 4),
			std::make_unique<RedTroll>(RoomID::horny_cave),
			std::make_unique<Plant>(RoomID::neglected_cave, 6),
			std::make_unique<Gnu>(RoomID::gnu_cave),
			std::make_unique<Dragon>(RoomID::torture_cave),
			std::make_unique<Swelling>(RoomID::bat_cave),
			std::make_unique<Door>(RoomID::empty_cave45),
			std::make_unique<Voices>(RoomID::talking_cave),
			std::make_unique<Barbecue>(RoomID::open_space17),
			std::make_unique<Tree>(RoomID::forest10),
			std::make_unique<GreenCrystal>(RoomID::forest4),
			std::make_unique<Computer>(RoomID::echo_cave),
			std::make_unique<DragonHead>(RoomID::small_cave),
			std::make_unique<Lava>(RoomID::lava_pit),
			std::make_unique<Vacuum>(RoomID::vacuum_cave),
			std::make_unique<Hatch>(RoomID::r_cave),
			std::make_unique<Swamp>(RoomID::north_swamp),
			std::make_unique<Swamp>(RoomID::middle_swamp),
			std::make_unique<Swamp>(RoomID::south_swamp),
			std::make_unique<Mist>(RoomID::mist_cave),
			std::make_unique<Teleporter>(RoomID::teleport_cave)
		};

		std::unique_ptr<Item> items[] { // { name, description, room, useable_on }
			std::make_unique<HoundMeat>(
				std::vector<string>{ "het hellehondvlees", "the hell hound meat" },
				std::vector<wstring>{
					L"Het is een goor stuk vlees dat naar kots ruikt.",
					L"It's a filthy piece of meat that smells of vomit."
				}
			),
			std::make_unique<ThermalSuit>(
				std::vector<string>{ "het hittepak", "the thermal suit" },
				std::vector<wstring>{
					L"Dit aluminiumkleurig pak beschermt je tegen grote hitte of kou.",
					L"This aluminium-coloured suit protects you against great heat or cold."
				},
				RoomID::forest4
			),
			std::make_unique<Crystal>(
				std::vector<string>{ "het groen kristal", "the green crystal" },
				std::vector<wstring>{
					L"Het is een helder, groengekleurd kristal. Even zie je een mysterieuze twinkeling",
					L"It is a clear, green crystal. For a moment, you see a mysterious twinkle."
				}
			),
			std::make_unique<Sword>(
				std::vector<string>{ "het zwaard", "the sword" },
				std::vector<wstring>{
					L"Het is een magisch zwaard dat er niet al te sterk uit ziet, maar veel kracht uitstraalt. In het heft zit een paarse robijn.",
					L"It's a magical sword that doesn't look too strong, but radiates great force. There's a purple ruby in the handle."
				},
				RoomID::forest5
			),
			std::make_unique<Bone>(
				std::vector<string>{ "het bot", "the bone" },
				std::vector<wstring>{
					L"Het is een menselijk, verbleekt dijbeen, dat er sterk uit ziet. Je kunt er veel kracht mee zetten.",
					L"It's a bleak, human thigh bone, that looks strong. You can apply a lot of force with it."
				},
				RoomID::swamp_path
			),
			std::make_unique<Diskette>(
				std::vector<string>{ "de diskette", "the diskette" },
				std::vector<wstring>{
					L"Het is een grijze 3,5 inch diskette van het merk 'Spirits' met daarop waarschijnlijk belangrijke data.",
					L"It's a grey 3.5\" diskette of the brand 'Spirits' that is likely to contain important data."
				},
				RoomID::slime_cave
			),
			std::make_unique<Hashis>(
				std::vector<string>{ "de hasj", "the hashis" },
				std::vector<wstring>{
					L"Het is een zakje met spul dat lijkt op tabak.",
					L"It's a bag with stuff that looks like tobacco."
				},
				RoomID::drugs_cave
			),
			std::make_unique<Crystal>(
				std::vector<string>{ "het rood kristal", "the red crystal" },
				std::vector<wstring>{
					L"Het is een helder, roodgekleurd kristal. Even zie je een mysterieuze twinkeling.",
					L"It is a clear, red crystal. For a moment, you see a mysterious twinkle."
				}
			),
			std::make_unique<Nightcap>(
				std::vector<string>{ "de slaapmuts", "the nightcap" },
				std::vector<wstring>{
					L"Het is een Mickey Mouse-slaapmuts met vrolijke kleuren.",
					L"It's a Mickey Mouse nightcap full of happy colours."
				},
				RoomID::straitjacket_cave
			),
			std::make_unique<Bomb>(
				std::vector<string>{ "de noekietronenbom", "the nookytron bomb" },
				std::vector<wstring>{
					L"De bom bestaat uit een aantal dunne buizen in een cilinder. Daaromheen zitten een aantal slangetjes. Er klinkt een vreemd gebrom dat uit een rooster komt. Er zit een bordje op: -5° - 105°, Codenaam: R136.",
					L"The bomb consists of a number of thin tubes in a cilinder. Around it, there are some tubes. A strange hum emerges from a grate. There's a sign on it that says: -5° - 105°, Code name: R136."
				},
				RoomID::main_cave
			),
			std::make_unique<Flashlight>(
				std::vector<string>{ "de zaklamp", "the flashlight" },
				std::vector<wstring>{
					L"Het is een zwarte, aluminium zaklamp met een halogeenlampje erin.",
					L"It's a black, aluminium flashlight with a halogen lamp in it."
				},
				RoomID::fluorescent_cave
			),
			std::make_unique<Bandage>(
				std::vector<string>{ "het verband", "the bandage kit" },
				std::vector<wstring>{
					L"Het is een witte doos met een rood kruis waarin wat verband en een paar pleisters zitten.",
					L"It's a white box with a red cross. It contains some bandages and a few band-aids."
				}, RoomID::tentacle_cave
			),
			std::make_unique<Flamethrower>(
				std::vector<string>{ "de vlammenwerper", "the flamethrower" },
				std::vector<wstring>{
					L"De vlammenwerper bestaat uit een pijp, een zuur- en een brandstoffles en een activatieknop. Uit de pijp komt een klein waakvlammetje.",
					L"The flamethrower consists of a pipe, oxigen and fuel containers and an activation button. A small pilot light comes out of the end of the pipe."
				},
				RoomID::garbage_cave
			),
			std::make_unique<Item>(
				std::vector<string>{ "het kookboek", "the cookbook" },
				std::vector<wstring>{
					L"Het is een oud, vergeeld kookboek met daarin een koekjesrecept. Er staat: 'Pak wat hellehond en wat hasj, en gooi het in de barbecue'. Dat is alles.",
					L"It's an old, yellowed cookbook that has a cookie recepy in it. It says: 'Take some hell hound and some hashis and throw them in the barbecue.' That is all."
				},
				RoomID::food_cave
			),
			std::make_unique<TNT>(
				std::vector<string>{ "de tnt", "the tnt" },
				std::vector<wstring>{
					L"De T.N.T. is een bosje rode staven met een velletje waarop staat: 'Pas op! Schokgevoelig!'",
					L"The TNT is a bundle of red sticks with a note that says: 'Warning! Sensitive to shock!'"
				}, 
				RoomID::empty_cave51
			),
			std::make_unique<CombinableItem>(
				std::vector<string>{ "het mosterdgaspatroon", "the mustard gas cartrtridge" },
				std::vector<wstring>{
					L"Het is een patroon dat mosterdgas onder druk bevat. Er zitten draadjes aan, en je kunt niets vinden om hem te activeren.",
					L"It's a cartridge that contains mustard gas under pressure. There are wires attached to it and you can't find any way to activate it."
				}, 
				ItemID::ignition
			),
			std::make_unique<PoisonedMeat>(
				std::vector<string>{ "het giftige vlees", "the poisonous meat" },
				std::vector<wstring>{
					L"Het is een stuk vlees dat er op zich lekker uit ziet, maar een paar groene vlekken heeft. Er zit een dode mier op.",
					L"It's a piece of meat that looks delicious in itself, but has a few green spots. There's a dead ant on top of it."
				}, 
				RoomID::safe_cave
			),
			std::make_unique<CombinableItem>(
				std::vector<string>{ "de ontsteking", "the ignition" },
				std::vector<wstring>{
					L"De ontsteking is een kastje met een T-vormige hendel erop.",
					L"The ignition is a small box with T-shaped handle on it."
				}, 
				RoomID::scooby_cave, ItemID::gas_capsule
			),
			std::make_unique<CombinableItem>(
				std::vector<string>{ "het pakje batterijen", "the pack of batteries" },
				std::vector<wstring>{
					L"Het is een pakketje met penlights. Konijntjes kunnen er uren mee trommelen.",
					L"It's a packet of penlight batteries. Bunnies can drum for hours on them."
				}, 
				RoomID::radioactive_cave, ItemID::flashlight
			),
			std::make_unique<Gasmask>(
				std::vector<string>{ "het gasmasker", "the gasmask" },
				std::vector<wstring>{
					L"Het is een groen masker met een rond filter en 2 plastic ooggaten.",
					L"It's a green mask with a round filter and 2 plastic eyeholes."
				}, 
				RoomID::i_cave
			),
			std::make_unique<Item>(
				std::vector<string>{ "het papier", "the letter" },
				std::vector<wstring>{
					L"Het is een geel vel papier met gekrulde hoeken. Het handschrift is bijna onleesbaar, en met moeite ontcijfer je: 'Voed de drakekop met de 3 gekleurde kristallen'.",
					L"It's a yellow pieace of paper with curled corners. The writing is almost illegible, and with some difficulty you decipher: 'Feed the dragon's head with the three coloured crystals'."
				}
			),
			std::make_unique<Booklet>(
				std::vector<string>{ "het boekje", "the booklet" },
				std::vector<wstring>{
					L"Het is een vies, kleverig boekje met op de voorkant een ontklede trol. Je krijgt kotsneigingen.",
					L"It's a dirty, sticky booklet with a naked troll on the front page. You feel like throwing up."
				},
				RoomID::damnation_cave
			),
			std::make_unique<Crystal>(
				std::vector<string>{ "het blauw kristal", "the blue crystal" },
				std::vector<wstring>{
					L"Het is een helder, blauwgekleurd kristal. Even zie je een mysterieuze twinkeling.",
					L"It is a clear, blue crystal. For a moment, you see a mysterious twinkle."
				}, 
				RoomID::red_cave
			),
			std::make_unique<Cookie>(
				std::vector<string>{ "het koekje", "the cookie" },
				std::vector<wstring>{
					L"Het is een rond koekje dat naar ammoniak stinkt.",
					L"It's a round cookie that smells like ammonia."
				}
			),
			std::make_unique<GasGrenade>(
				std::vector<string>{ "de mosterdgasgranaat", "the mustard gas grenade" },
				std::vector<wstring>{
					L"Door het indrukken van de hendel kan het mosterdgas ontstnappen.",
					L"By pressing the handle down, the mustard gas can esacpe."
				}
			)
		};

		template <typename TKey, class TValue>
		void fill_map(EntityMap<TKey, TValue>& map, std::unique_ptr<TValue> values[], int count)
		{
			static_assert(std::is_base_of<Entity<TKey>, TValue>::value, "TValue must inherit from Entity<TKey>");

			map.clear();

			for (int i = 0; i < count; i++)
			{
				values[i]->id = static_cast<TKey>(i);
				map.add_or_set(std::move(values[i]));
			}
		}

		bool set_room_connections(std::unique_ptr<Room> rooms[], int count)
		{
			// Interconnect rooms with neighbours
			for (int i = 0; i < count; i++)
			{
				Room& room = *rooms[i];
				room.connections.clear();
				room.connections.set(Command::east, static_cast<RoomID>(i + 1));
				room.connections.set(Command::west, static_cast<RoomID>(i - 1));
				room.connections.set(Command::north, static_cast<RoomID>(i - 5));
				room.connections.set(Command::south, static_cast<RoomID>(i + 5));
			}

			// Seperate layers
			for (int i = 0; i < count; i += 20)
			{
				for (int j = 0; j < 16; j += 5)
				{
					rooms[i + j + 4]->connections.erase(Command::east);
					rooms[i + j]->connections.erase(Command::west);
				}

				for (int j = 0; j < 5; j++)
				{
					rooms[i + j]->connections.erase(Command::north);
					rooms[i + j + 15]->connections.erase(Command::south);
				}
			}

			// Connect layers
			for (auto& connection : level_connections)
				rooms[to_value(connection.from)]->connections.set(connection.direction, connection.to);

			// Blocked routes
			for (auto& block : blocked_connections)
				rooms[to_value(block.room)]->connections.erase(block.direction);

			return true;
		}
	}

	void initialize(CoreData& core)
	{
		core.paperroute = { RoomID::capital_p_cave, RoomID::a_cave, RoomID::p_cave, RoomID::i_cave, RoomID::e_cave, RoomID::r_cave };

		core.status.current_room = RoomID::forest0;
		core.status.paper_route_pos = 0;
		core.status.life_points = constants::max_life_points;
		core.status.has_tree_burned = false;

		srand(abs((int)time(NULL)));

		set_room_connections(rooms, to_value(RoomID::COUNT));

		fill_map(core.rooms, rooms, to_value(RoomID::COUNT));
		fill_map(core.animates, animates, to_value(AnimateID::COUNT));
		fill_map(core.items, items, to_value(ItemID::COUNT));

		core.set_flashlight(dynamic_cast<Flashlight*>(&core.items[ItemID::flashlight]));
	}

	void parse_arguments(CoreData& core, int argc, char* argv[])
	{
		core.language = Language::Dutch;

		if (argc < 2)
			return;

		for (int i = 1; i < argc; i++) 
		{
			string arg = argv[i];
			std::transform(arg.begin(), arg.end(), arg.begin(),
				[](unsigned char c) { return std::tolower(c); });
			
			if (!arg.compare("-h") || !arg.compare("--help"))
				general::show_arguments();

			else if (!arg.compare("-d") || !arg.compare("--dutch") || !arg.compare("-n") || !arg.compare("--nederlands"))
				core.language = Language::Dutch;

			else if (!arg.compare("-e") || !arg.compare("--english") || !arg.compare("--engels"))
				core.language = Language::English;
	
			else
			{
				std::cerr << "Ongeldige optie/invalid argument: " << arg << "\n\n";
				general::show_arguments();
			}
		}
	}
}

