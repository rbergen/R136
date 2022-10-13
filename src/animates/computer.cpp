#include "base.h"
#include "console.h"
#include "animates.h"

Computer::Computer(RoomID room) : Animate(room) {}

bool Computer::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::computer].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"Er staat een computer van het merk Beull die bestaat bestaat uit een kast met een 3.5-inch drive en een monitor. "
			"Op de monitor staat: \"Datadisk invoeren a.u.b.\"."
		,
			"There's a Beull-branded computer that consists of a cabinet with a 3.5\" drive and a monitor. The monitor displays: "
			"\"Please enter data disk\"."
		));

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print(select("De computer wacht nog steeds.", "The computer's still waiting."));

		break;

	case AnimateStatus::computer_is_reading:
		console.main().print(select( 
			"De drive begint te lezen en na korte tijd verschijnt er informatie op het scherm. "
			"Er staat: \"In het onderste grottenstelsel moet men een letter route volgen die resulteert in de naam van het te vinden voorwerp.\"\n"
			"Na even wordt het scherm zwart."
		,
			"The drive starts to read and after a short time information appears on the screen. "
			"It reads: \"In the lowest cave system, one must follow a letter route that results in the name of the object that is to be found.\"\n"
			"After a little while, the screen goes black."
		));

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_3:
		console.main().print(select( 
			"Er valt niets te zien op de monitor en de computer is stil."
		, 
			"There's nothing to see on the monitor and the computer is silent."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}