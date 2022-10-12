#include "base.h"
#include "console.h"
#include "animates.h"

Swamp::Swamp(RoomID room) : Animate(room) {}

bool Swamp::progress_status(CoreData& core)
{
	console.main().print(select(
		"Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond onder de voeten hebt. "
		"Ondanks je wilde pogingen boven te blijven zak je langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa "
		"zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie, en na enige tijd verlies je je bewustzijn.\n"
		"Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot."
	,
		"With the first step you take into the swamp, you feel that you no longer have solid footing. "
		"Despite trying desparately to stay above, you slowly sink into the swamp. When you're neck-deep in the bubbling, muddy mass "
		"you hold your breath and close your eyes. You keep sinking down the goo, and after some time you lose consciousness.\n"
		"When you come to, you notice that you are on solid ground... in a cave."
	));
	console.main().empty_line();

	switch (core.status.current_room)
	{
	case RoomID::north_swamp:
		core.status.current_room = RoomID::empty_cave51;
		break;

	case RoomID::middle_swamp:
		core.status.current_room = RoomID::gloomy_cave;
		break;

	case RoomID::south_swamp:
		core.status.current_room = RoomID::rock_cave;
		break;

	default:
		core.status.current_room = RoomID::swamp_path;
		break;
	}

	return false;
}