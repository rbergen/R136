#include "base.h"
#include "console.h"
#include "items.h"

bool TNT::use(CoreData& core)
{
	console.main().print("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samen-\n"
		"gaat met een harde knal. Je wordt even verblind door de flits van de ontplof-\n"
		"fing. Door de klap val je even flauw.\n\n");

	core.status.life_points--;

	return true;
}