#include "base.h"
#include "console.h"
#include "items.h"
#include "status.h"

bool Flashlight::use(CoreData& core)
{
	if (is_on)
	{
		is_on = false;
		console.main().print("Je zet de zaklamp uit.{0}", status::is_room_lit(core) ? "" : " Je ziet niets meer.");
		console.main().empty_line();
		return false;
	}

	if (has_bunny_batteries || battery_level)
	{
		is_on = true;
		console.main().print("Je zet de zaklamp aan. De straal verlicht de omtrek.");
		console.main().empty_line();
		return false;
	}

	console.main().print("Zonder nieuwe batterijen doet-ie het niet...");
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
		console.main().print("De zaklamp gaat zwakker branden.");
		break;
	case 0:
		console.main().print("De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij.");
		is_on = false;
		break;
	}
	console.main().empty_line();

}
