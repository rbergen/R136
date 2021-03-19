#include "base.h"
#include "console.h"
#include "animates.h"

Tree::Tree(RoomID room) : Animate(room) {}

bool Tree::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::tree].status)
	{
	case AnimateStatus::initial:
		console.main().print("In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit\n");
		console.main().print("een bordje met daarop de tekst \"Roken en open vuur verboden\".\n\n");

		break;

	case AnimateStatus::tree_on_fire:
		console.main().print("Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam\n");
		console.main().print("te branden, en weldra staat hij in lichterlaaie. De vlammen slaan om zich heen,\n");
		console.main().print("en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee,\n");
		console.main().print("en de hitte is enorm.");

		if (core.items[ItemID::thermal_suit].room != RoomID::owned)
		{
			console.main().empty_line();
			console.main().print("Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwon-\n");
			console.main().print("den op.");

			core.status.life_points -= 4; //   Levenswond
		}

		core.status.has_tree_burned = true;
		core.items[ItemID::green_crystal].room = RoomID::forest4;
		core.animates[AnimateID::green_crystal].status = AnimateStatus::visible;
		core.animates[AnimateID::tree].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk\n");
		console.main().print("bord met daarop \"R   n e  op n v u  ver  d n\".");

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}