#include "base.h"
#include "console.h"
#include "items.h"
#include "status.h"

bool Flashlight::use(CoreData& core)
{
	if (is_on)
	{
		is_on = false;
		console.main().print(
			select("Je zet de zaklamp uit.{0}", "You turn off the flashlight.{0}"), 
			status::is_room_lit(core) ? "" : select(" Je ziet niets meer.", "You don't see a thing anymore.")
		);
		console.main().empty_line();
		return false;
	}

	if (has_bunny_batteries || battery_level)
	{
		is_on = true;
		console.main().print(select(
			"Je zet de zaklamp aan. De straal verlicht de omtrek."
		,
			"You turn on the flashlight. The beam lights up your surroundings."
		));
		console.main().empty_line();
		return false;
	}

	console.main().print(select(
		"Zonder nieuwe batterijen doet-ie het niet..."
	,
		"It won't work without new batteries..."
	));
	console.main().empty_line();
	return true;
}

void Flashlight::decrease_battery_level(CoreData& core)
{
	if (has_bunny_batteries || battery_level <= 0 || !is_on)
		return;

	switch (--battery_level)
	{
	case 10:
		console.main().print(select("De zaklamp gaat zwakker branden.", "The light of the flashlight starts to dim."));
		break;
	case 0:
		console.main().print(select(
			"De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij."
		,
			"The batteries in the flaslight are depleted. Slowly, it goes out."
		));
		is_on = false;
		break;
	}
	console.main().empty_line();

}
