#include "base.h"

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

std::unique_ptr<Room> rooms[]{ // { names, descriptions }
	std::make_unique<Forest>(
		in_the_forest,
		std::vector<wstring>{
			L"Je bevindt je in een uithoek van een donker bos. Overal hoor je enge geluiden."
		,
			L"This is the far corner of a dark forest. Scary sounds come from every direction."
		}
	),
	std::make_unique<Forest>(
		in_the_forest,
		std::vector<wstring>{
			L"Aan de zuidkant zie je een hek dat toegang geeft tot een donkere plaats."
		,
			L"Towards the south, you see a gate that gives access to a dark place."
		}
	),
	std::make_unique<Forest>(
		in_the_forest,
		std::vector<wstring>{
			L"Er komt een modderige geur uit het oosten."
		,
			L"There is a muddy smell coming from the east."
		}
	),
	std::make_unique<Outdoor>(in_the_swamp, smelly_surface),
	std::make_unique<Forest>(
		in_the_forest,
		std::vector<wstring>{
			L"Er komt een modderige geur uit het westen."
		,
			L"There is a muddy smell coming from the west."
		}
	),
	std::make_unique<Forest>(
		in_the_forest,
		std::vector<wstring>{
			L"Pas op voor de laaghangende takken!"
		,
			L"Mind the low-hanging branches!"
		}
	),
	std::make_unique<Outdoor>(
		std::vector <wstring>{ L"op de begraafplaats", L"at the cemetery" },
		std::vector <wstring>{
			L"Een lucht van rottend vlees dringt in je neus. Je denkt dat je een grafsteen ziet bewegen."
		,
			L"The smell of rotting flesh creeps up your nose. You think you see a tombstone move."
		}
	),
	std::make_unique<Forest>(in_the_forest),
	std::make_unique<Outdoor>(in_the_swamp,	smelly_surface),
	std::make_unique<Outdoor>(
		at_an_open_space,
		std::vector<wstring>{
			L"Er komt een modderige geur uit het westen."
		,
			L"There is a muddy smell coming from the west."
		}
	),
	std::make_unique<Forest>(in_the_forest),
	std::make_unique<Forest>(
		in_the_forest,
		std::vector<wstring>{
			L"Je trapt bijna in een berenklem."
		,
			L"You almost step into a bear trap."
		}
	),
	std::make_unique<Outdoor>(
		at_an_open_space,
		std::vector<wstring>{
			L"Door de mist zie je nog net de omtrekken van het donkere bos."
		,
			L"Through the mist you can just make out the outline of the dark forest."
		}
	),
	std::make_unique<Outdoor>(
		std::vector<wstring>{ L"op het moeraspad", L"on the swamp path" },
		std::vector<wstring>{
			L"Er ligt hier een skelet, waarschijnlijk een van je voorgangers."
		,
			L"There's a skeleton here, probably one of your predecessors."
		}
	),
	std::make_unique<Outdoor>(
		at_an_open_space,
		std::vector<wstring>{
			L"Bij het licht van een halve maan onderscheid je nog net de vorm van een galg."
		,
			L"In the light of a half moon you can just make out the shape of a gallow."
		}
	),
	std::make_unique<Forest>(
		in_the_forest,
		std::vector<wstring>{
			L"In de verte hoor je het trieste gehuil van een weerwolf."
		,
			L"In the distance you hear the sad howl of a werewolf."
		}
	),
	std::make_unique<Forest>(in_the_forest),
	std::make_unique<Outdoor>(
		at_an_open_space,
		std::vector<wstring>{
			L"Er ligt hier een dood konijn dat wordt belaagd door vliegen."
		,
			L"There's a dead rabbit on the ground that's being attacked by flies."
		}
	),
	std::make_unique<Outdoor>(in_the_swamp,	smelly_surface),
	std::make_unique<Indoor>(
		std::vector<wstring>{ L"in de ruïne", L"in the ruins" },
		std::vector<wstring>{
			L"De ruïne is een spookachtige bouwval. Er is hier een wankele trap die naar beneden leidt."
		,
			L"The ruins are a spooky rubble. There is a shaky staircase that leads downwards."
		}
	),

	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de slijmgrot", L"in the slime cave" },
		std::vector<wstring>{
			L"De wanden van deze grot zijn bekleed met een snotachtig slijm."
		,
			L"The walls of the cave are covered in a snotty slime."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de zwarte grot", L"in the black cave" },
		std::vector<wstring>{
			L"Je ziet geen hand voor ogen."
		,
			L"You can't see your hand in front of your face."
		}
	),
	std::make_unique<Cave>(std::vector <wstring>{ L"in de drugsgrot", L"in the drugs cave" }),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de geile grot", L"in the horny cave", },
		std::vector<wstring>{
			L"Aan de muren hangen gelige, gescheurde Playboy-posters."
		,
			L"Affixed to the wall are yellow, torn Playboy posters."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de dwangbuisgrot", L"in the straitjacket cave" },
		std::vector<wstring>{
			L"Er hangt hier een dwangbuis, met daarin een verminkt lijk."
		,
			L"There's a straitjacket hanging from the ceiling, with a mutilated body in it."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in een verwaarloosde grot", L"in a neglected cave" }),
	std::make_unique<Cave>(in_an_empty_cave),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de hoofdgrot", L"in the main cave" },
		std::vector<wstring>{
			L"Er staat hier een batterij aan mysterieuze apparatuur."
		,
			L"There is a battery of mysterious equipment, here."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de hiërogliefengrot", L"in the hieroglyphs cave" },
		std::vector<wstring>{
			L"Op de wanden staan hiërogliefen waar je geen wijs uit wordt."
		,
			L"There are symbols on the walls that you can not make sense of."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de stankgrot", L"in the stench cave" },
		std::vector<wstring>{
			L"Er hangt hier een smerige lucht die je herinnert aan de zware lucht van een beerput."
		,
			L"The filthy stench that lingers here reminds you of the heavy smell of a cesspool."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in een troosteloze grot", L"in a disconsolate cave" }),
	std::make_unique<Indoor>(
		std::vector<wstring>{ L"in de TL-grot", L"in the fluorescent cave" },
		std::vector<wstring>{
			L"De grot wordt zwak verlicht door een lichtbron die hoog aan het plafond hangt."
		,
			L"The cave is weakly lit by a light source that hangs high at the ceiling."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in een kleine grot", L"in a small cave" }),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de ijsgrot", L"in the ice cave" },
		std::vector<wstring>{
			L"In deze grot lijkt het net of alles van ijs is, en je krijgt rillingen."
		,
			L"In this cave everything looks like it is made out of ice. It gives you the shivers."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de kaktusgrot", L"in the cactus cave", },
		std::vector<wstring>{
			L"Je bent omringd door giftige kaktussen die in deze grot staan."
		,
			L"You're surrounded by poisonous cactuses that are present in this cave."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de stalagmietengrot", L"in the stalagmite cave" },
		std::vector<wstring>{
			L"Hier zie je een traliewerk van stalagmieten."
		,
			L"You see a railing of stalagmites."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de stormgrot", L"in the storm cave" },
		std::vector<wstring>{
			L"Door deze grot loeit een harde wind, waardoor je je vast moet grijpen aan een van de wanden."
		,
			L"A hard wind blows through this cave that makes you hold on to one of the walls."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de mistgrot", L"in the mist cave" }),
	std::make_unique<Cave>(in_a_stairwell_cave, other_levels),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de tentakelgrot", L"in the tentacle cave" },
		std::vector<wstring>{
			L"Van alle kanten komen grote tentakels die je aftasten en groene sporen op je huid achterlaten."
		,
			L"Large tentacles come from all directions. They scan your body and leave green traces on your skin."
		}
	),

	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de vuilnisgrot", L"in the garbage cave" },
		std::vector<wstring>{
			L"In deze grot ligt een grote stapel rottende etensresten. De stank is bijna ondraaglijk."
		,
			L"There is large pile of rotting food remains in this cave. The stench is almost unbearable."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de echogrot", L"in the echo cave" },
		std::vector<wstring>{
			L"Hier worden alle geluiden die je maakt tegen de wanden geëcho'd."
		,
			L"All sounds you make echo back from the walls."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de geheime grot", L"in the secret cave" },
		std::vector<wstring>{
			L"Op de grond van deze grot liggen allerlei onbekende en geheimzinnige voorwerpen."
		,
			L"On the floor of the cave there's a wide range of unfamiliar and mysterious objects."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de voedselgrot", L"in the food cave" },
		std::vector<wstring>{
			L"Zo te ruiken is dit waarschijnlijk eens een keuken geweest..."
		,
			L"It smells like this probably was a kitchen at some point..."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de grot van de gnoe", L"in the cave of the gnu" },
		std::vector<wstring>{
			L"Hier liggen de geraamtes van wezens die eerder ten prooi zijn gevallen aan de gnoe."
		,
			L"Scattered around are skeletons of creatures that fell prey to the gnu before."
		}
	),
	std::make_unique<Cave>(in_an_empty_cave),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de ogengrot", L"in the eye cave" },
		std::vector<wstring>{
			L"Van alle kanten wordt je bespied door rode, bloeddoorlopen ogen die precies volgen wat je doet."
		,
			L"From all angles you are looked at by red, blood-shot eyes that precisely follow your actions."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de rotsgrot", L"in the rock cave" },
		std::vector<wstring>{
			L"Overal zie je hier scherpe rotspunten. Aan een aantal ervan zitten bruine korsten."
		,
			L"You see sharp rock edges everywhere. Brown crusts are attached to some of them."
		}
	),
	std::make_unique<Outdoor>(std::vector<wstring>{ L"in de leegte", L"in the emptiness" }),
	std::make_unique<Outdoor>(
		std::vector<wstring>{ L"op de zandbank", L"at the sandbank" },
		std::vector<wstring>{
			L"Op de vloer liggen vreemde patronen, gevormd uit verschillende soorten zand."
		,
			L"On the ground you see strange patterns, made out of different types of sand."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de martelgrot", L"in the torture cave" },
		std::vector<wstring>{
			L"Onder de vage schemering van de martelvuren zie je nog net een duimschroef en wat stekelige voorwerpen waar nog wat bloed aan zit."
		,
			L"Under the vague shimmer of the torture fires, you can just see a thumbscrew and some pointy objects that still have some blood attached to them."
		}
	),
	std::make_unique<Cave>(in_an_empty_cave),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de veilige grot", L"in the safe cave" },
		std::vector<wstring>{
			L"Dit is de enige grot waar je je een beetje veilig voelt."
		,
			L"This is the only cave in which you feel some safety."
		}
	),
	std::make_unique<Outdoor>(
		std::vector<wstring>{ L"in de nauwe rotsspleet", L"in the narrow cleft" },
		std::vector<wstring>{
			L"Aan alle kanten wordt je omringd door hoge rotsmuren. Alleen in het westen zie je een opening."
		,
			L"You're surrounded by high rock walls at all sides. You only see an opening at the western side."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de oliegrot", L"in the oil cave" },
		std::vector<wstring>{
			L"Vanuit het zuiden verspreidt zich een enorme hitte, die in deze grot nog net draaglijk is."
		,
			L"An enormous heat spreads from the south that is only just bearable in this cave."
		}
	),
	std::make_unique<Cave>(in_an_empty_cave),
	std::make_unique<Cave>(in_a_stairwell_cave, other_levels),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de spinnengrot", L"in the spider cave" },
		std::vector<wstring>{
			L"Het wemelt hier van de tarantula's. Bij elke stap die je zet hoor je het onder je voeten kraken, en ze kruipen langs je benen omhoog."
		,
			L"It's teeming with tarantulas, here. You hear crunching with every step you take, and you feel them crawling up your legs."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de pratende grot", L"in the talking cave" }),
	std::make_unique<Cave>(std::vector<wstring>{ L"op de lavaput", L"at the lava pit" }),

	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de skoebiegrot", L"in the scooby cave" },
		std::vector<wstring>{
			L"Uit alle richtingen komen rare geluiden, als in een gesticht."
		,
			L"Weird noises come from all directions, as if in a mental institution."
		}
	),
	std::make_unique<Indoor>(
		std::vector<wstring>{ L"in de radioactieve grot", L"in the radioactive cave" },
		std::vector<wstring>{
			L"Door de hoge radioactiviteit is deze grot zwak verlicht."
		,
			L"Due to the high level of radioactivity, this cave is dimly lit."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de i-grot", L"in the second t cave" }),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de p-grot", L"in the first t cave" }),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de a-grot", L"in the first e cave" },
		std::vector<wstring>{
			L"In deze grot bevindt zich het stenen beeld van een oud, jou onbekend wezen."
		,
			L"This caves houses the stone statue of an old creature that is unfamiliar to you."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de dodengrot", L"in the cave of death" },
		std::vector<wstring>{
			L"De naam van deze grot spreekt voor zich..."
		,
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
			L"In deze grot heerst een haast verstikkende sfeer, en je voelt je niet prettig."
		,
			L"An almost suffocating atmosphere dominates this cave. You don't feel comfortable here."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de vacuumgrot", L"in the vacuum cave" }),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de rode grot", L"in the red cave" }),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de neongrot", L"in the neon cave" },
		std::vector<wstring>{
			L"Deze grot is fel gekleurd. Er staan patronen die je doen denken aan zwarte magie."
		,
			L"This cave is brightly coloured. There are patterns that remind you of black magic."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de bloedgrot", L"in the blood cave" },
		std::vector<wstring>{
			L"Het geraamte van een groot beest ligt hier op de grond en een aantal ingewanden liggen er naast."
		,
			L"There's a skeleton of a large beast on the ground, and some of its guts are next to it."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de vleermuisgrot", L"in the bat cave" },
		std::vector<wstring>{
			L"In deze grot fladderen overal vleermuizen, op zoek naar hun prooi."
		,
			L"Bats are fluttering everywhere in this cave, looking for their prey."
		}
	),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de slangengrot", L"in the snake cave" },
		std::vector<wstring>{
			L"Je hoort het geluid van een ratelslang. Bij de weg naar het noorden staat een doodskop getekend, die een gevaar aanduidt."
		,
			L"You hear the sound of a rattle-snake. At the northern end there's a drawing of a skull, signifying danger."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de kwabbengrot", L"in the lobe cave" }),
	std::make_unique<Cave>(
		std::vector<wstring>{ L"in de glibbergrot", L"in the slippery cave" },
		std::vector<wstring>{
			L"Je glijdt bijna uit over de zeepachtige prut die overal in de grot ligt. Tussen de glibberige massa steekt een paal omhoog met daarop een pijl die naar het oosten wijst."
		,
			L"You nearly slip over the soap-like goo that is everywhere in this cave. Somewhere in the slippery mass, a pole sticks up that has an arrow attached to it, which points east."
		}
	),
	std::make_unique<Cave>(std::vector<wstring>{ L"in de teleportgrot", L"in the teleport cave" })
};
