#include "r136.h"
#include "animates.h"

Lava::Lava(RoomID room) : Animate(room) {}

bool Lava::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::lava].status)
	{
	case AnimateStatus::initial:
		if (core.items[ItemID::thermal_suit].room == RoomID::owned)
		{
			console.main().print("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke\n");
			console.main().print("damp, en een rode gloed verlicht de omtrek. De hitte is enorm, maar het hitte-\n");
			console.main().print("pak beschermt je tegen verbranding.\n\n");
		}
		else
		{
			console.main().print("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je\n");
			console.main().print("een aantal brandwonden oploopt en naar achteren wordt geblazen.\n\n");

			core.status.current_room = RoomID::oil_cave; //   Grot terug
			core.status.life_points -= 4; //   Levenswond

			return false;
		}

		return true;

	case AnimateStatus::bomb_dropped:
		console.main().print("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt\n");
		console.main().print("de bom langzaam weg naar beneden. De lava begint op een gegeven moment vreemd\n");
		console.main().print("te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver-\n");
		console.main().print("blindende flits vanuit het lava. Daarna wordt het weer rustiger.\n\n");
		console.main().print("Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door\n");
		console.main().print("dit positronenwapen, waarvan de beginselen mede van jouw handen komen. Je mis-\n");
		console.main().print("sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het\n");
		console.main().print("grottenstelsel.\n\n");

		force_exit();
	}

	return true;
}