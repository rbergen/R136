#include "base.h"
#include "console.h"
#include "general.h"
#include "animates.h"

Lava::Lava(RoomID room) : Animate(room) {}

bool Lava::progress_status(CoreData& core)
{
	if (core.animates[AnimateID::lava].status == AnimateStatus::bomb_dropped)
	{
		console.main().print("Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt de bom langzaam weg naar beneden. "
			"De lava begint op een gegeven moment vreemd te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver blindende flits "
			"vanuit het lava. Daarna wordt het weer rustiger.");
		console.main().empty_line();
		console.main().print(
			"Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door dit positronenwapen, waarvan de beginselen mede van jouw handen komen. "
			"Je mis sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het grottenstelsel.");
		console.main().empty_line();

		general::force_exit();
	}

	if (!core.inventory.contains(ItemID::thermal_suit))
	{
		console.main().print("Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je een aantal brandwonden oploopt en naar achteren wordt geblazen.");

		core.status.current_room = RoomID::oil_cave; //   Grot terug
		core.status.life_points -= 4; //   Levenswond

		console.main().empty_line();
		return false;
	}

	console.main().print("Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke damp, en een rode gloed verlicht de omtrek. "
		"De hitte is enorm, maar het hitte pak beschermt je tegen verbranding.");
	console.main().empty_line();

	return true;

}