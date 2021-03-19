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
		console.main().print("Er staat hier een reusachtige hellehond die je de weg verspert. Zijn scherpe\n");
		console.main().print("tanden steken duidelijk af, en het rode kwijl druipt langzaam uit zijn bek.\n");
		console.main().print("Hij kijkt je dreigend aan met zijn bloeddoorlopen ogen, en uit zijn keel\n");
		console.main().print("klinkt een diep gegrom.\n\n");

		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De hellehond zet zich af tegen de grond, en hij spring boven op je lijf. Zijn\n");
		console.main().print("nagels boren zich in je vlees, en op een gegeven moment bijt hij je hard in je\n");
		console.main().print("schouder. Je botten kraken en een scheut van pijn trekt door je zenuwen. De\n");
		console.main().print("hond laat je los, en hij kijkt je grommend aan.\n\n");

		core.status.life_points--; //  Wond
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De honger van de hellehond is nog niet gestild. Een diep gegrom komt uit zijn\n");
		console.main().print("keel, en hij staat klaar om opnieuw aan te vallen.\n\n");

		core.animates[AnimateID::hellhound].status = random::get_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_3:
		console.main().print("Door de wonden aangericht met je zwaard sterft de hevig bloedende hellehond. Je\n");
		console.main().print("deelt nog een slag uit, en een stuk vlees van de hond laat los.\n\n");

		core.items[ItemID::hound_meat].room = core.status.current_room;
		core.animates[AnimateID::hellhound].status++;

		break;

	case AnimateStatus::status_4:
		console.main().print("De dode hellehond ligt in een bad van dampend bloed.\n\n");
		break;
	}

	return true;
}