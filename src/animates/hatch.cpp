#include "base.h"
#include "console.h"
#include "animates.h"

Hatch::Hatch(RoomID room) : Animate(room) {}

bool Hatch::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::hatch].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er zit een dicht, houten luik in het plafond. Je kunt er niet bij.");

		break;

	case AnimateStatus::hatch_opening:
		console.main().print("Het luik in het plafond gaat open en er dwarrelt een vel papier naar beneden.");

		core.items[ItemID::paper].room = RoomID::r_cave;
		core.animates[AnimateID::hatch].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("Het luik aan het plafond hangt nu open. Er zit een leeg gat.");

		break;

	default:
		break;
	}

	return true;
}