#include "base.h"
#include "console.h"
#include "animates.h"

Hatch::Hatch(RoomID room) : Animate(room) {}

bool Hatch::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::hatch].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"Er zit een dicht, houten luik in het plafond. Je kunt er niet bij."
		,
			"There's a closed, wooden hatch in the ceiling. You can't reach it."
		));

		break;

	case AnimateStatus::hatch_opening:
		console.main().print(select(
			"Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden."
		,
			"The hatch in the ceiling opens, and a sheet of paper whirls downward."
		));

		core.items[ItemID::paper].room = RoomID::r_cave;
		core.animates[AnimateID::hatch].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print(select(
			"Het luik aan het plafond hangt nu open. Er zit een leeg gat."
		,
			"The hatch in the ceiling hangs open. There's an empty hole."
		));

		break;

	default:
		break;
	}

	return true;
}