#include "base.h"
#include "console.h"
#include "animates.h"

Voices::Voices(RoomID room) : Animate(room) {}

bool Voices::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::voices].status)
	{
	case AnimateStatus::initial:
		console.main().print("Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan:\n");
		console.main().print("\"Wat schreeuwt is in z'n hart nog een kind\".\n");
		console.main().print("Dan is het weer stil.");

		core.animates[AnimateID::voices].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("Vanuit de verte hoor je zachte, lachende stemmetjes.");

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}