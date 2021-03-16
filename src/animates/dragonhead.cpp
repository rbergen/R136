#include "r136.h"
#include "animates.h"

DragonHead::DragonHead(RoomID room) : Animate(room) {}

bool DragonHead::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon_head].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een\n");
		console.main().print("geopende muil. Op de deur zit een zwaar slot.\n\n");

		break;

	case AnimateStatus::status_1:
		console.main().print("Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer\n");
		console.main().print("opengaat. Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te\n");
		console.main().print("gloeien.\n\n");

		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De ogen van de draak blijven licht gloeien.\n\n");

		break;

	case AnimateStatus::status_3:
		console.main().print("Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het\n");
		console.main().print("kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker.\n\n");

		core.animates[AnimateID::dragon_head].status++;
		break;

	case AnimateStatus::status_4:
		console.main().print("De ogen van de draak blijven gloeien.\n\n");

		break;

	case AnimateStatus::status_5:
		console.main().print("Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft\n");
		console.main().print("hij dicht. De ogen beginnen nu steeds feller te gloeien. Op een gegeven moment\n");
		console.main().print("concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet\n");
		console.main().print("en wordt weerkaatst in een spiegel vlak achter je. De spiegel reflecteert het\n");
		console.main().print("licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\n");
		console.main().print("Daarna zwaait de deur langzaam met veel gepiep open.\n\n");

		core.rooms[RoomID::small_cave].connections.set(Command::north, RoomID::main_cave);
		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_6:
		console.main().print("De zware deur is nu open en geeft toegang tot een ruimte.\n\n");

		break;
	}

	return true;
}