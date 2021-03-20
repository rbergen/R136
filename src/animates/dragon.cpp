#include "base.h"
#include "console.h"
#include "animates.h"

Dragon::Dragon(RoomID room) : Animate(room) {}

bool Dragon::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon].status)
	{
	case AnimateStatus::initial:
		console.main().print("In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je allemaal bespieden met gele oogjes. "
			"Zijn hele huid is bedekt met schimmel, en uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af druppelt. "
			"Opeens komt uit een van de bekken een rommelend geluid. Met moeite versta je \"Ben jij een koekie?\".");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig te snuiven.\n"
		"De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt "
		"\"BEN JIJ EEN KOEKIE?!?\".");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzettende harde klap. Er kraakt iets in je hoofd, "
			"en een duizeling maakt zich van je meester. Hij maakt aanstalten je nog een klap te verkopen.");

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::cookie_is_thrown:
		console.main().print("De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\n"
			"Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\n"
			"Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak slaapt.");

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::sleeping_lightly:
		console.main().print("De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn lijf klinkt een diep gegrom.");

		break;

	case AnimateStatus::nightcap_on_head:
		console.main().print("Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts steken af tegen de beschimmelde huid, "
			"en de muts zakt iets scheef. Op een ge geven moment valt er iets, en het klettert tegen de harde rotsvloer.");

		core.items[ItemID::gas_capsule].room = core.status.current_room;
		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_6:

		console.main().print("De draak slaapt rustig.");

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}