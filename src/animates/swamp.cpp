#include "base.h"
#include "console.h"
#include "animates.h"

Swamp::Swamp(RoomID room) : Animate(room) {}

bool Swamp::progress_status(CoreData& core)
{
	console.main().print("Met de eerste stap die je in het moeras zet, voel je dat je geen vaste grond onder de voeten hebt. "
		"Ondanks je wilde pogingen boven te blijven zak je langzaam het moeras in. Als je tot je nek in de pruttelende, modderige massa "
		"zit houd je je adem in en doe je je ogen dicht. Je blijft zakken in de smurrie, en na enige tijd verlies je je bewustzijn.\n"
		"Als je weer bijkomt merk je dat je op een harde ondergrond ligt... in een grot.");
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