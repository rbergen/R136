#include "r136.h"
#include "animates.h"

Dragon::Dragon(RoomID room) : Animate(room) {}

bool Dragon::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon].status)
	{
	case AnimateStatus::initial:
		console.main().print("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je\n");
		console.main().print("allemaal bespieden met gele oogjes. Zijn hele huid is bedekt met schimmel, en\n");
		console.main().print("uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af drup-\n");
		console.main().print("pelt. Opeens komt uit een van de bekken een rommelend geluid. Met moeite\n");
		console.main().print("versta je \"Ben jij een koekie?\".\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig\n");
		console.main().print("te snuiven.\n");
		console.main().print("De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van\n");
		console.main().print("walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt\n");
		console.main().print("\"BEN JIJ EEN KOEKIE?!?\".\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzet-\n");
		console.main().print("tende harde klap. Er kraakt iets in je hoofd, en een duizeling maakt zich van\n");
		console.main().print("je meester. Hij maakt aanstalten je nog een klap te verkopen.\n\n");

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::cookie_is_thrown:
		console.main().print("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\n");
		console.main().print("Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\n");
		console.main().print("Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak\n");
		console.main().print("slaapt.\n\n");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::sleeping_lightly:
		console.main().print("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn\n");
		console.main().print("lijf klinkt een diep gegrom.\n\n");

		break;

	case AnimateStatus::nightcap_on_head:
		console.main().print("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts\n");
		console.main().print("steken af tegen de beschimmelde huid, en de muts zakt iets scheef. Op een ge-\n");
		console.main().print("geven moment valt er iets, en het klettert tegen de harde rotsvloer.\n\n");

		core.items[ItemID::gas_capsule].room = core.status.current_room;
		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_6:

		console.main().print("De draak slaapt rustig.\n\n");

		break;
	}

	return true;
}