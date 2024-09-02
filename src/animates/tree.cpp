#include "base.h"
#include "console.h"
#include "animates.h"

Tree::Tree(RoomID room) : Animate(room) {}

bool Tree::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::tree].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"In een kleine open plek staat een grote, kurkdroge, dode boom. Op de stam zit een bordje met daarop de tekst \"Roken en open vuur verboden\"."
		,
			"In a small, open area there is a large, bone-dry, dead tree. There's a sign on the stem that reads \"Smoking and naked flames prohibited\"."
		));

		break;

	case AnimateStatus::tree_on_fire:
		console.main().print(select(
			"Uit de pijp van de vlammenwerper spuit een enorme vlam. De boom begint langzaam te branden, en weldra staat hij in lichterlaaie. "
			"De vlammen slaan om zich heen, en het hele bos begint mee te branden. Je bent omringd door een enorme vuurzee, en de hitte is enorm."
		,
			"An enormous flame erupts from the flamethrower. Slowly, the tree starts to burn, and soon it's ablaze. "
			"The flames spread around, and the entire forest starts to burn. You're surrounded by an ocean of fire, and the heat is enormous."
		));

		if (!core.inventory.contains(ItemID::thermal_suit))
		{
			console.main().empty_line();
			console.main().print(select(
				"Je hebt niets om je te beschermen tegen de hitte, en je loopt flinke brandwonden op."
			,
				"You have nothing to protect you from the fire, and you suffer serious burns."
			));

			core.status.life_points -= 4; //   Serious injury
		}

		core.status.has_tree_burned = true;
		core.items[ItemID::green_crystal].room = RoomID::forest4;
		core.animates[AnimateID::green_crystal].status = AnimateStatus::visible;
		core.animates[AnimateID::tree].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print(select(
			"Uit de grond steken nog een paar wortels, en er naast ligt een verkoold stuk bord met daarop \"R   n e  op n v u  ver  d n\"."
		,
			"Some roots still stick from the ground. Next to them lies a charred part of a sign that reads \"Sm   ng a   na  d fl     pro    t d\"."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}