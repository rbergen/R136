#include "base.h"
#include "console.h"
#include "animates.h"

DragonHead::DragonHead(RoomID room) : Animate(room) {}

bool DragonHead::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon_head].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"Er zit in het noorden een zware, dichte deur met daarnaast een drakekop met een geopende muil. Op de deur zit een zwaar slot."
		,
			"There's a heavy, closed door in the north. Next to it is a dragon's head with an open mouth. There's a heavy lock on the door."
		));

		break;

	case AnimateStatus::status_1:
		console.main().print(select(
			"Je stopt het kristal in de muil van de drakekop, die daarop dicht- en weer opengaat. "
			"Het kristal is nu verdwenen, en de ogen van de kop beginnen licht te gloeien."
		,
			"You put the crystal in the mouth of the dragon's head, which subsequently closes and reopens. "
			"The crystal has disappeared, and the eyes in the head start to glow lightly."
		));

		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print(select("De ogen van de draak blijven licht gloeien.", "The eyes of the dragon keep glowling lightly."));

		break;

	case AnimateStatus::status_3:
		console.main().print(select(
			"Je stopt nog een kristal in de muil. Weer sluit en opent deze, en weer is het kristal verdwenen. Het schijnsel uit de ogen wordt nu sterker."
		,
			"You put another crystal in the mouth. Again, it closes and opens, and again, the crystal disappears. The shining from the eyes becomes stronger."
		));

		core.animates[AnimateID::dragon_head].status++;
		break;

	case AnimateStatus::status_4:
		console.main().print(select("De ogen van de draak blijven gloeien.", "The eyes of the dragon keep glowing."));

		break;

	case AnimateStatus::status_5:
		console.main().print(select(
			"Je legt het laatste kristal in de kop. De muil sluit zich weer, en nu blijft hij dicht. De ogen beginnen nu steeds feller te gloeien. "
			"Op een gegeven moment concentreert de gloed zich tot een erg felle lichtstraal, die langs je schiet en wordt weerkaatst in een spiegel vlak achter je. "
			"De spiegel reflecteert het licht met akelige precisie op het zware slot dat door de enorme hitte verdampt.\n"
			"Daarna zwaait de deur langzaam met veel gepiep open."
		,
			"You put the last crystal in the mouth. The mouth closes once more, and now it remains shut. The glow from the eyes keeps intensifying. "
			"At some point, the glow converges into a very bright beam of light that shoots past you and gets reflected by a mirror just begind you. "
			"With grisly precision, the mirror reflects the light onto the heavy lock, which evaporates due to the enormous heat.\n"
			"Then, the door slowly opens while squeaking loudly."
		));

		core.rooms[RoomID::small_cave].connections.set(Command::north, RoomID::main_cave);
		core.animates[AnimateID::dragon_head].status++;

		break;

	case AnimateStatus::status_6:
		console.main().print(select("De zware deur is nu open en geeft toegang tot een ruimte.", "The heavy door is now open and provides access to a room."));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}