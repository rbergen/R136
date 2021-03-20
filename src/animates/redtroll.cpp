#include "base.h"
#include "console.h"
#include "animates.h"
#include "random.h"

RedTroll::RedTroll(RoomID room) : Animate(room) {}

bool RedTroll::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::red_troll].status)
	{
	case AnimateStatus::initial:
		console.main().print(L"Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar geërgerd.");

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je af.");

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn tot je botten doordringen.");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_3:
		console.main().print("Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep.");

		core.animates[AnimateID::red_troll].status = randomizer::get_status(AnimateStatus::status_2, AnimateStatus::status_3);

		break;

	case AnimateStatus::booklet_thrown:
		console.main().print("Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en roder. Op een gegeven moment klinkt een geborrel op "
			"uit het wezen, en met een klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol langzaam naar beneden.\n"
			"Opeens zie je iets glinsteren.");

		core.items[ItemID::red_crystal].room = core.status.current_room;
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_5:
		console.main().print("Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm zuigt aan je schoenen, en een vieze stank dringt in je neus.");

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}