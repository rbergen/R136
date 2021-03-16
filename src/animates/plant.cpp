#include "r136.h"
#include "animates.h"

Plant::Plant(RoomID room, int strikes_to_kill) : Animate(room, strikes_to_kill) {}

bool Plant::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::plant].status)
	{
	case AnimateStatus::initial:
		console.main().print("In deze grot leeft een vleesetende plant. Zijn dikke groene stengel loopt uit\n");
		console.main().print("in een afschrikwekkende kop, met afzichtelijke tanden. Hij heeft je gezien en\n");
		console.main().print("beweegt zijn opengesperde bek in je richting. Voordat je een stap hebt kunnen\n");
		console.main().print("zetten zit je verstrengd in het monster, en zet de plant zijn tanden in je\n");
		console.main().print("nek.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::plant].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::status_1:
		console.main().print("De plant likt met zijn kleine schurfterige tongetje je bloed van zijn bek.\n");
		console.main().print("Met zijn groene oogjes kijkt hij je weer aan, en hij maakt aanstalten zijn\n");
		console.main().print("tanden opnieuw in je nek te zetten.\n\n");

		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print("Opnieuw omsluit de bek van de plant je hals. Een warme stroom bloed loopt via\n");
		console.main().print("je rug naar beneden, en de pijn is nu ondraaglijk. Na een tijdje laat de plant\n");
		console.main().print("je weer los.\n\n");

		core.status.life_points--; //   Wond
		core.animates[AnimateID::plant].status = get_random_status(AnimateStatus::status_1, AnimateStatus::status_2);

		break;

	case AnimateStatus::dead:
		console.main().print("De resten van wat eerst een vleesetende plant was liggen nu op de grond van\n");
		console.main().print("de grot. Zijn bek ligt opengesperd, en zijn ogen rollen bijna uit zijn oogkas-\n");
		console.main().print("sen. Uit zijn stengel druipt langzaam het bloed van zijn slachtoffers.\n");
		console.main().print("Op de plek waar vroeger zijn beschimmelde wortels waren zit nu een opening.\n\n");

		core.rooms[RoomID::neglected_cave].connections.set(Command::north, RoomID::slime_cave); //	Maak verbinding met slijmgrot
		core.animates[AnimateID::plant].status++;

		break;

	case AnimateStatus::status_4:
		console.main().print("De vleesetende plant is niet veel meer dan een berg stinkend tuinafval.\n\n");

		break;
	}

	return true;
}