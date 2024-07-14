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
		console.main().print(select(
			L"Je hebt de rust van de rode trol verstoord. Hij kijkt zwaar geërgerd."
		,
			L"You've disturbed the peace of the red troll. He looks deeply annoyed."
		));

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print(select(
			"Nu is de trol pas echt goed wakker. Hij pakt zijn zweep en komt dreigend op je af."
		,
			"Now the troll is properly awake. He grabs his whip and appraches you threateningly."
		));

		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print(select(
			"De trol deelt je een harde klap uit met z'n zweep. Je voelt de brandende pijn tot je botten doordringen."
		,
			"The troll hits you hard whit his whip. You feel the burning pain down to your bones."
		));

		core.status.life_points--; //   Wond
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_3:
		console.main().print(select(
			"Het schuim loopt uit de trol z'n bek. Hij heft opnieuw zijn zweep."
		,
			"Foam runs from the troll's mouth. He rises his sword again."
		));

		core.animates[AnimateID::red_troll].status = randomizer::get_status(AnimateStatus::status_2, AnimateStatus::status_3);

		break;

	case AnimateStatus::booklet_thrown:
		console.main().print(select(
			"Opgewonden grijpt de trol het boekje. Hij bladert het door, en wordt roder en roder. Op een gegeven moment klinkt een geborrel op "
			"uit het wezen, en met een klap springt hij uit elkaar. Van de rotswanden druipen de resten van de trol langzaam naar beneden.\n"
			"Opeens zie je iets glinsteren."
		,
			"Excitedly, the troll snatches the booklet. He flips through it and turns more and more red. At some point a gurgling noise emerges "
			"from the creature, and he blows up with a bang. The remains of the troll slowly drip down from the cave walls.\n"
			"Suddenly, you see something glimmer."
		));

		core.items[ItemID::red_crystal].room = core.status.current_room;
		core.animates[AnimateID::red_troll].status++;

		break;

	case AnimateStatus::status_5:
		console.main().print(select(
			"Overal in de grot liggen stukken van de verscheurde trol verspreid. Het slijm zuigt aan je schoenen, en een vieze stank dringt in je neus."
		,
			"Pieces of the torn-up troll are spread throughout the cave. Slime pulls at your shoes, and a filthy stench creeps up your nose."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}
