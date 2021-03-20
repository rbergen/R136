#include "base.h"
#include "console.h"
#include "animates.h"

Tree::Tree(RoomID room) : Animate(room) {}

bool Tree::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::tree].status)
	{
	case AnimateStatus::initial:
		console.main().print("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit een bordje met daarop de tekst \"Roken en open vuur verboden\".");

		break;

	case AnimateStatus::tree_on_fire:
		console.main().print("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam te branden, en weldra staat hij in lichterlaaie. "
			"De vlammen slaan om zich heen, en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee, en de hitte is enorm.");

		if (!core.inventory.contains(ItemID::thermal_suit))
		{
			console.main().empty_line();
			console.main().print("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwonden op.");

			core.status.life_points -= 4; //   Levenswond
		}

		core.status.has_tree_burned = true;
		core.items[ItemID::green_crystal].room = RoomID::forest4;
		core.animates[AnimateID::green_crystal].status = AnimateStatus::visible;
		core.animates[AnimateID::tree].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk bord met daarop \"R   n e  op n v u  ver  d n\".");

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}