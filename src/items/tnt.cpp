#include "base.h"
#include "console.h"
#include "items.h"

bool TNT::use(CoreData& core)
{
	console.main().print(select(
		"Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samengaat met een harde knal. "
		"Je wordt even verblind door de flits van de ontploffing. Door de klap val je even flauw."
	,
		"You take a stick and throw it on the ground. An explosion follows, accompanied by a loud bang. "
		"You're temporarily blinded by the explosion's flash. Due to the hit you shortly loose conscience."
	));
	console.main().empty_line();

	core.status.life_points--;

	return true;
}