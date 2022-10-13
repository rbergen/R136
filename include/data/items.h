#include "base.h"

std::unique_ptr<Item> items[]{ // { name, description, room, useable_on }
	std::make_unique<HoundMeat>(
		std::vector<string>{ "het hellehondvlees", "the hell hound meat" },
		std::vector<wstring>{
			L"Het is een goor stuk vlees dat naar kots ruikt."
		,
			L"It's a filthy piece of meat that smells of vomit."
		}
	),
	std::make_unique<ThermalSuit>(
		std::vector<string>{ "het hittepak", "the thermal suit" },
		std::vector<wstring>{
			L"Dit aluminiumkleurig pak beschermt je tegen grote hitte of kou."
		,
			L"This aluminium-coloured suit protects you against great heat or cold."
		},
		RoomID::forest4
	),
	std::make_unique<Crystal>(
		std::vector<string>{ "het groen kristal", "the green crystal" },
		std::vector<wstring>{
			L"Het is een helder, groengekleurd kristal. Even zie je een mysterieuze twinkeling"
		,
			L"It is a clear, green crystal. For a moment, you see a mysterious twinkle."
		}
	),
	std::make_unique<Sword>(
		std::vector<string>{ "het zwaard", "the sword" },
		std::vector<wstring>{
			L"Het is een magisch zwaard dat er niet al te sterk uit ziet, maar veel kracht uitstraalt. In het heft zit een paarse robijn."
		,
			L"It's a magical sword that doesn't look too strong, but radiates great force. There's a purple ruby in the handle."
		},
		RoomID::forest5
	),
	std::make_unique<Bone>(
		std::vector<string>{ "het bot", "the bone" },
		std::vector<wstring>{
			L"Het is een menselijk, verbleekt dijbeen, dat er sterk uit ziet. Je kunt er veel kracht mee zetten."
		,
			L"It's a bleak, human thigh bone, that looks strong. You can apply a lot of force with it."
		},
		RoomID::swamp_path
	),
	std::make_unique<Diskette>(
		std::vector<string>{ "de diskette", "the diskette" },
		std::vector<wstring>{
			L"Het is een grijze 3,5 inch diskette van het merk 'Spirits' met daarop waarschijnlijk belangrijke data."
		,
			L"It's a grey 3.5\" diskette of the brand 'Spirits' that is likely to contain important data."
		},
		RoomID::slime_cave
	),
	std::make_unique<Hashis>(
		std::vector<string>{ "de hasj", "the hashis" },
		std::vector<wstring>{
			L"Het is een zakje met spul dat lijkt op tabak."
		,
			L"It's a bag with stuff that looks like tobacco."
		},
		RoomID::drugs_cave
	),
	std::make_unique<Crystal>(
		std::vector<string>{ "het rood kristal", "the red crystal" },
		std::vector<wstring>{
			L"Het is een helder, roodgekleurd kristal. Even zie je een mysterieuze twinkeling."
		,
			L"It is a clear, red crystal. For a moment, you see a mysterious twinkle."
		}
	),
	std::make_unique<Nightcap>(
		std::vector<string>{ "de slaapmuts", "the nightcap" },
		std::vector<wstring>{
			L"Het is een Mickey Mouse-slaapmuts met vrolijke kleuren."
		,
			L"It's a Mickey Mouse nightcap full of happy colours."
		},
		RoomID::straitjacket_cave
	),
	std::make_unique<Bomb>(
		std::vector<string>{ "de noekietronenbom", "the nookytron bomb" },
		std::vector<wstring>{
			L"De bom bestaat uit een aantal dunne buizen in een cilinder. Daaromheen zitten een aantal slangetjes. Er klinkt een vreemd gebrom dat uit een rooster komt. Er zit een bordje op: -5° - 105°, Codenaam: R136."
		,
			L"The bomb consists of a number of thin tubes in a cilinder. Around it, there are some tubes. A strange hum emerges from a grate. There's a sign on it that says: -5° - 105°, Code name: R136."
		},
		RoomID::main_cave
	),
	std::make_unique<Flashlight>(
		std::vector<string>{ "de zaklamp", "the flashlight" },
		std::vector<wstring>{
			L"Het is een zwarte, aluminium zaklamp met een halogeenlampje erin."
		,
			L"It's a black, aluminium flashlight with a halogen lamp in it."
		},
		RoomID::fluorescent_cave
	),
	std::make_unique<Bandage>(
		std::vector<string>{ "het verband", "the bandage kit" },
		std::vector<wstring>{
			L"Het is een witte doos met een rood kruis waarin wat verband en een paar pleisters zitten."
		,
			L"It's a white box with a red cross. It contains some bandages and a few band-aids."
		}, 
		RoomID::tentacle_cave
	),
	std::make_unique<Flamethrower>(
		std::vector<string>{ "de vlammenwerper", "the flamethrower" },
		std::vector<wstring>{
			L"De vlammenwerper bestaat uit een pijp, een zuur- en een brandstoffles en een activatieknop. Uit de pijp komt een klein waakvlammetje."
		,
			L"The flamethrower consists of a pipe, oxigen and fuel containers and an activation button. A small pilot light comes out of the end of the pipe."
		},
		RoomID::garbage_cave
	),
	std::make_unique<Item>(
		std::vector<string>{ "het kookboek", "the cookbook" },
		std::vector<wstring>{
			L"Het is een oud, vergeeld kookboek met daarin een koekjesrecept. Er staat: 'Pak wat hellehond en wat hasj, en gooi het in de barbecue'. Dat is alles."
		,
			L"It's an old, yellowed cookbook that has a cookie recepy in it. It says: 'Take some hell hound and some hashis and throw them in the barbecue.' That is all."
		},
		RoomID::food_cave
	),
	std::make_unique<TNT>(
		std::vector<string>{ "de tnt", "the tnt" },
		std::vector<wstring>{
			L"De T.N.T. is een bosje rode staven met een velletje waarop staat: 'Pas op! Schokgevoelig!'"
		,
			L"The TNT is a bundle of red sticks with a note that says: 'Warning! Sensitive to shock!'"
		},
		RoomID::empty_cave51
	),
	std::make_unique<CombinableItem>(
		std::vector<string>{ "het mosterdgaspatroon", "the mustard gas cartrtridge" },
		std::vector<wstring>{
			L"Het is een patroon dat mosterdgas onder druk bevat. Er zitten draadjes aan, en je kunt niets vinden om hem te activeren."
		,
			L"It's a cartridge that contains mustard gas under pressure. There are wires attached to it and you can't find any way to activate it."
		},
		ItemID::ignition
	),
	std::make_unique<PoisonedMeat>(
		std::vector<string>{ "het giftige vlees", "the poisonous meat" },
		std::vector<wstring>{
			L"Het is een stuk vlees dat er op zich lekker uit ziet, maar een paar groene vlekken heeft. Er zit een dode mier op."
		,
			L"It's a piece of meat that looks delicious in itself, but has a few green spots. There's a dead ant on top of it."
		},
		RoomID::safe_cave
	),
	std::make_unique<CombinableItem>(
		std::vector<string>{ "de ontsteking", "the ignition" },
		std::vector<wstring>{
			L"De ontsteking is een kastje met een T-vormige hendel erop."
		,
			L"The ignition is a small box with T-shaped handle on it."
		},
		RoomID::scooby_cave, ItemID::gas_capsule
	),
	std::make_unique<CombinableItem>(
		std::vector<string>{ "het pakje batterijen", "the pack of batteries" },
		std::vector<wstring>{
			L"Het is een pakketje met penlights. Konijntjes kunnen er uren mee trommelen."
		,
			L"It's a packet of penlight batteries. Bunnies can drum for hours on them."
		},
		RoomID::radioactive_cave, ItemID::flashlight
	),
	std::make_unique<Gasmask>(
		std::vector<string>{ "het gasmasker", "the gasmask" },
		std::vector<wstring>{
			L"Het is een groen masker met een rond filter en 2 plastic ooggaten."
		,
			L"It's a green mask with a round filter and 2 plastic eyeholes."
		},
		RoomID::i_cave
	),
	std::make_unique<Item>(
		std::vector<string>{ "het papier", "the letter" },
		std::vector<wstring>{
			L"Het is een geel vel papier met gekrulde hoeken. Het handschrift is bijna onleesbaar, en met moeite ontcijfer je: 'Voed de drakekop met de 3 gekleurde kristallen'."
		,
			L"It's a yellow pieace of paper with curled corners. The writing is almost illegible, and with some difficulty you decipher: 'Feed the dragon's head with the three coloured crystals'."
		}
	),
	std::make_unique<Booklet>(
		std::vector<string>{ "het boekje", "the booklet" },
		std::vector<wstring>{
			L"Het is een vies, kleverig boekje met op de voorkant een ontklede trol. Je krijgt kotsneigingen."
		,
			L"It's a dirty, sticky booklet with a naked troll on the front page. You feel like throwing up."
		},
		RoomID::damnation_cave
	),
	std::make_unique<Crystal>(
		std::vector<string>{ "het blauw kristal", "the blue crystal" },
		std::vector<wstring>{
			L"Het is een helder, blauwgekleurd kristal. Even zie je een mysterieuze twinkeling."
		,
			L"It is a clear, blue crystal. For a moment, you see a mysterious twinkle."
		},
		RoomID::red_cave
	),
	std::make_unique<Cookie>(
		std::vector<string>{ "het koekje", "the cookie" },
		std::vector<wstring>{
			L"Het is een rond koekje dat naar ammoniak stinkt."
		,
			L"It's a round cookie that smells like ammonia."
		}
	),
	std::make_unique<GasGrenade>(
		std::vector<string>{ "de mosterdgasgranaat", "the mustard gas grenade" },
		std::vector<wstring>{
			L"Door het indrukken van de hendel kan het mosterdgas ontstnappen."
		,
			L"By pressing the handle down, the mustard gas can esacpe."
		}
	)
};
