#include "base.h"
#include "console.h"
#include "general.h"
#include "animates.h"

Lava::Lava(RoomID room) : Animate(room) {}

bool Lava::progress_status(CoreData& core)
{
	if (core.animates[AnimateID::lava].status == AnimateStatus::bomb_dropped)
	{
		console.main().print(select(
			"Je gooit de positronenbom met een pisboogje in de lava. Met luid gesis zakt de bom langzaam weg naar beneden. "
			"De lava begint op een gegeven moment vreemd te borrelen en verschiet ineens van rood naar groen. Dan zie je een oogver blindende flits "
			"vanuit het lava. Daarna wordt het weer rustiger."
		,
			"You throw the positron bomb into the lava with a lackluster curve. Sissing loudly, the bomb slowly sinks down. "
			"At some point, the lava starts bubbling weirdly and suddenly changes from red to green. Then you see a lightning flash from the lava. "
			"After that, it calms down again."
		));
		console.main().empty_line();
		console.main().print(select(
			"Het lijkt erop dat je de wereld hebt behoed voor de totaalvernietiging door dit positronenwapen, waarvan de beginselen mede van jouw handen komen. "
			"Je mis sie is voltooid, en vermoeid en vol van gemengde gevoelens verlaat je het grottenstelsel."
		,
			"It looks like you've saved the planet from total destruction by this positron weapon, the origins of which are partly your making. "
			"Your mission is complete, and tired and full of emotions you leave the cave system."
		));
		console.main().empty_line();

		general::force_exit(core.language);
	}

	if (!core.inventory.contains(ItemID::thermal_suit))
	{
		console.main().print(select(
			"Voor je zie je een krater waarin lava opborrelt. De hitte is zo intens, dat je een aantal brandwonden oploopt en naar achteren wordt geblazen."
		,
			"In front of you, there's a crater from which lava bubbles up. The heat is so intense that you suffer a number of burns and get blown backwards."
		));

		core.status.current_room = RoomID::oil_cave; //   Grot terug
		core.status.life_points -= 4; //   Levenswond

		console.main().empty_line();
		return false;
	}

	console.main().print(select(
		"Voor je zie je een krater waarin lava opborrelt. Van het lava komt een dikke damp, en een rode gloed verlicht de omtrek. "
		"De hitte is enorm, maar het hitte pak beschermt je tegen verbranding."
	,
		"In front of you, there's a crater from which lava bubbles up. A thick vapor emerges from the lava, and a red glow lights the surroundings. "
		"The heat is enormous, but the thermal suit protects you from burning."
	));
	console.main().empty_line();

	return true;

}