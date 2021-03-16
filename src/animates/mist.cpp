#include "r136.h"
#include "animates.h"

Mist::Mist(RoomID room) : Animate(room) {}

bool Mist::progress_status(CoreData& core)
{
	console.main().print("In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen\n");
	console.main().write(L"ziet. Je verliest je orïentatiegevoel en stommelt paniekerig door de grot, op\n");
	console.main().print("zoek naar een uitgang.\n");
	console.main().print("Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden,\n");
	console.main().print("struikel je voorover een andere grot in.\n\n");

	switch (get_random_number(3))
	{
	case 0:
		core.status.current_room = RoomID::storm_cave;
		break;

	case 1:
		core.status.current_room = RoomID::small_cave;
		break;

	case 2:
		core.status.current_room = RoomID::stairwell_cave1;
		break;
	}

	return false;
}