#include "r136.h"
#include "animates.h"

Door::Door(RoomID room) : Animate(room) {}

bool Door::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::door].status)
	{
	case AnimateStatus::initial:
		console.main().print("In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet\n");
		console.main().print("meer open te krijgen.\n\n");

		break;

	case AnimateStatus::door_open:
		console.main().print(L"Je zet één eind van het bot onder de deur, en op het andere begin je te duwen.\n");
		console.main().print("Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een\n");
		console.main().print("kier. Je geeft nog een duw, en langzaam draait de deur open.\n\n");

		core.rooms[RoomID::empty_cave45].connections.set(Command::north, RoomID::garbage_cave);
		core.animates[AnimateID::door].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De deur is nu open, en geeft toegang tot een grot.\n\n");

		break;
	}

	return true;
}