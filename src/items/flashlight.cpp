#include "base.h"
#include "console.h"
#include "items.h"
#include "status.h"

void Flashlight::use(CoreData& core)
{
	if (is_on)
	{
		is_on = false;
		console.main().print("Je zet de zaklamp uit.{0}", status::is_room_lit(core) ? "\n" : " Je ziet niets meer.\n");
		return;
	}

	if (has_bunny_batteries || battery_level)
	{
		is_on = true;
		console.main().print("Je zet de zaklamp aan. De straal verlicht de omtrek.\n");
	}
	else
		console.main().print("Zonder nieuwe batterijen doet-ie het niet...\n");
}

void Flashlight::decrease_battery_level(CoreData& core)
{
	if (has_bunny_batteries || battery_level <= 0 || !is_on)
		return;

	switch (--battery_level)
	{
	case 10:
		console.main().print("De zaklamp gaat zwakker branden.\n\n");
		break;
	case 0:
		console.main().print("De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij.\n\n");
		is_on = false;
		break;
	}
}
