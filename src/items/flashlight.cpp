#include "r136.h"
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

	if (has_batteries || battery_level)
	{
		is_on = true;
		console.main().print("Je zet de zaklamp aan. De straal verlicht de omtrek.\n");
	}
	else
		console.main().print("Zonder nieuwe batterijen doet-ie het niet...\n");
}