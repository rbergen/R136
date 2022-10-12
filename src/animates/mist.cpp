#include "base.h"
#include "console.h"
#include "random.h"
#include "animates.h"

Mist::Mist(RoomID room) : Animate(room) {}

bool Mist::progress_status(CoreData& core)
{
	console.main().print(select(
		L"In deze grot hangt een vreemde, dichte mist, waardoor je geen hand voor ogen ziet. "
		 "Je verliest je orïentatiegevoel en stommelt paniekerig door de grot, op zoek naar een uitgang.\n"
		 "Net als je begint te denken dat je nooit een uitgang uit deze grot zult vinden, struikel je voorover een andere grot in."
	,
		L"A strange, dense fog dominates this cave, because of which you can't see your hand in front of your eyes. "
		 "You lose orientation, and stumble around the cave in panic, looking for a way out.\n",
		 "Just when you start thinking that you'll never find a way out of this cave, you fall forward into another cave."
	));
	console.main().empty_line();

	switch (randomizer::get_number(3))
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