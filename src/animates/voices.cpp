#include "base.h"
#include "console.h"
#include "animates.h"

Voices::Voices(RoomID room) : Animate(room) {}

bool Voices::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::voices].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"Uit het niets hoor je opeens een paar stemmen. Met moeite kun je ze verstaan: \"Wat schreeuwt is in z'n hart nog een kind\".\n"
			"Dan is het weer stil."
		,
			"Out of nothing you suddenly hear a few voices. With difficulty you can understand them: \"What shouts is still a child in its heart\".\n"
			"Then it goes quiet again."
		));

		core.animates[AnimateID::voices].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print(select(
			"Vanuit de verte hoor je zachte, lachende stemmetjes."
		, 
			"From the distance you hear soft, laughing voices."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}