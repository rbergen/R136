#include "base.h"
#include "console.h"
#include "animates.h"
#include "random.h"

HellHound::HellHound(RoomID room, int strikes_to_kill) : Animate(room, strikes_to_kill) {}

bool HellHound::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::hellhound].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe tanden steken duidelijk af, "
			"en het rode kwijl druipt langzaam uit zijn bek. Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel "
			"klinkt een diep gegrom.");

		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn nagels boren zich in je vlees, "
			"en op een gegeven moment bijt hij je hard in je schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. "
			"De hond laat je los, en hij kijkt je grommend aan.");

		core.status.life_points--; //  Wond
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn keel, en hij staat klaar om opnieuw aan te vallen.");

		core.animates[AnimateID::hellhound].status = randomizer::get_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_3:
		console.main().print("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je deelt nog een slag uit, "
			"en een stuk vlees van de hond laat los.");

		core.items[ItemID::hound_meat].room = core.status.current_room;
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_4:
		console.main().print("De dode hellehond ligt in een bad van dampend bloed.");
		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}