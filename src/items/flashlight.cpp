#include "r136.h"
#include "items.h"

void Flashlight::use(CoreData& core)
{

	if (status.is_lamp_on)
	{
		status.is_lamp_on = !status.is_lamp_on;
		console.main().print("Je zet de zaklamp uit.{0}", is_room_lit(core) ? "\n" : " Je ziet niets meer.\n");
		break;
	}

	if (status.lamp_points)
	{
		status.is_lamp_on = !status.is_lamp_on;
		console.main().print("Je zet de zaklamp aan. De straal verlicht de omtrek.\n");
	}
	else
		console.main().print("Zonder nieuwe batterijen doet'ie het niet...\n");
}