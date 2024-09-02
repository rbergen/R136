#include "base.h"
#include "console.h"
#include "animates.h"
#include "random.h"

Plant::Plant(RoomID room, int strikes_to_kill) : Animate(room, strikes_to_kill) {}

bool Plant::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::plant].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit in een afschrikwekkende kop, met afzichtelijke tanden. "
			"Hij heeft je gezien en beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen zetten zit je verstrengd in het monster, "
			"en zet de plant zijn tanden in je nek."
		,
			"This cave houses a flesh-eating plant. Its thick green stem runs up to a horrifying head, with gruesome teeth. "
			"It noticed you and it moves its wide-open mouth in your direction. Before you've been able to make a move, you're tangled up in the monster. "
			"The plant puts its teeth in your neck."
		));

		core.status.life_points--; //   Wound
		core.animates[AnimateID::plant].status = randomizer::get_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_1:
		console.main().print(select(
			"De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek. Met zijn groene oogjes kijkt hij je weer aan, "
			"en hij maakt aanstalten zijn tanden opnieuw in je nek te zetten."
		,
			"With its little scavy tongue, the plant licks your blood of its mouth. It looks at you again with its geen eyes, "
			"and prepares to sink its teeth in your neck again."
		));

		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print(select(
			"Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via je rug naar beneden, en de pijn is nu ondraaglijk. "
			"Na een tijdje laat de plant je weer los."
		,
			"Once more, the plant's mouth encloses your neck. A warm stream of blood runs down over your back, and now the pain is unbearable. "
			"After a while, the plant lets go of you again."
		));

		core.status.life_points--; //   Wond
		core.animates[AnimateID::plant].status = randomizer::get_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::dead:
		console.main().print(select(
			"De resten van wat eerst een vleesetende plant was liggen nu op de grond van de grot. Zijn bek ligt opengesperd, "
			"en zijn ogen rollen bijna uit zijn oogkassen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\n"
			"Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening."
		,
			"The remains of what used to be a flesh-eating plant are now on the floor of the cave. It's mouth is wide open, "
			"and its eyes almost roll out of their sockets. The blood of its victims slowly drips out of its stem.\n"
			"At the spot where his molded roots used to be, an opening has appeared."
		));

		core.rooms[RoomID::neglected_cave].connections.set(Command::north, RoomID::slime_cave); //	Maak verbinding met slijmgrot
		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_4:
		console.main().print(select(
			"De vleesetende plant is niet veel meer dan een berg stinkend tuinafval."
		,
			"The flesh-eating plant is little more than a mound of stinking garden waste."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}