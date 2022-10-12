#include "base.h"
#include "console.h"
#include "animates.h"

Door::Door(RoomID room) : Animate(room) {}

bool Door::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::door].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"In het noorden zit een grote, vastgeroeste deur. Hij is met blote handen niet meer open te krijgen."
		,
			"A large door that is rusted shut is at the northern side. It can no longer be opened with bare hands."
		));

		break;

	case AnimateStatus::door_open:
		console.main().print(select(
			L"Je zet één eind van het bot onder de deur, en op het andere begin je te duwen.\n"
			 "Na lang wrikken begint de deur hevig te kraken en te piepen, en vormt zich een kier. Je geeft nog een duw, en langzaam draait de deur open."
		,
			L"You put one end of the bone under the door, and you start pushing down on the other.\n"
			 "After extensive wiggling, the door starts to creak and squeak, and a crack appears. You push down once more, and slowly the door swings open."
		));

		core.rooms[RoomID::empty_cave45].connections.set(Command::north, RoomID::garbage_cave);
		core.animates[AnimateID::door].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print(select(
			"De deur is nu open, en geeft toegang tot een grot."
		,
			"The door is now open and provides access to a cave."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}