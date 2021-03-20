#include "base.h"
#include "console.h"
#include "items.h"

bool TNT::use(CoreData& core)
{
	console.main().print("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samengaat met een harde knal. "
		"Je wordt even verblind door de flits van de ontploffing. Door de klap val je even flauw.");
	console.main().empty_line();

	core.status.life_points--;

	return true;
}