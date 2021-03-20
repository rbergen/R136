#include "base.h"
#include "console.h"
#include "animates.h"

DragonHead::DragonHead(RoomID room) : Animate(room) {}

bool DragonHead::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon_head].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een geopende muil. Op de deur zit een zwaar slot.");

		break;

	case AnimateStatus::status_1:
		console.main().print("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer opengaat. "
			"Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te gloeien.");

		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De ogen van de draak blijven licht gloeien.");

		break;

	case AnimateStatus::status_3:
		console.main().print("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.");

		core.animates[AnimateID::dragon_head].status++;
		break;

	case AnimateStatus::status_4:
		console.main().print("De ogen van de draak blijven gloeien.");

		break;

	case AnimateStatus::status_5:
		console.main().print("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft hij dicht. De ogen beginnen nu steeds feller te gloeien. "
			"Op een gegeven moment concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet en wordt weerkaatst in een spiegel vlak achter je. "
			"De spiegel reflecteert het licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\n"
			"Daarna zwaait de deur langzaam met veel gepiep open.");

		core.rooms[RoomID::small_cave].connections.set(Command::north, RoomID::main_cave);
		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_6:
		console.main().print("De zware deur is nu open en geeft toegang tot een ruimte.");

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}