#include "base.h"
#include "console.h"
#include "animates.h"

Computer::Computer(RoomID room) : Animate(room) {}

bool Computer::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::computer].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat een computer van het merk Beull die bestaat bestaat uit een kast met\n");
		console.main().print("een 3.5-inch drive en een monitor. Op de monitor staat: \"Datadisk invoeren\n");
		console.main().print("a.u.b.\".\n\n");

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De computer wacht nog steeds.\n\n");

		break;

	case AnimateStatus::computer_is_reading:
		console.main().print("De drive begint te lezen en na korte tijd verschijnt er informatie op het\n");
		console.main().print("scherm. Er staat: \"In het onderste grottenstelsel moet men een letter-\n");
		console.main().print("route volgen die resulteert in de naam van het te vinden voorwerp.\".\n");
		console.main().print("Na even wordt het scherm zwart.\n\n");

		core.animates[AnimateID::computer].status++;

		break;

	case AnimateStatus::status_3:
		console.main().print("Er valt niets te zien op de monitor en de computer is stil.\n\n");

		break;
	}

	return true;
}