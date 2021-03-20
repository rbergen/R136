#include "base.h"
#include "console.h"
#include "animates.h"

Barbecue::Barbecue(RoomID room) : Animate(room) {}

bool Barbecue::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::barbecue].status)
	{
	case AnimateStatus::initial_burn:
		console.main().print("Op deze open plek staat een barbecue gezellig te branden.");

		break;

	case AnimateStatus::hashis_on_fire:
		console.main().print("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt er niets.");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::meat_on_fire:
		console.main().print("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt er niets.");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::ingredient_burning:
		console.main().print("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.");

		break;

	case AnimateStatus::cookie_is_baking:
		console.main().print(L"Een grote rookontwikkeling treedt op wanneer het tweede ingrediënt in de barbecue belandt.\n");
		console.main().print(L"Knetterend smelten de 2 ingrediënten om tot een koekje.");

		core.items[ItemID::cookie].room = core.status.current_room;
		core.animates[AnimateID::barbecue].status = AnimateStatus::initial_burn;

		break;
	}

	console.main().empty_line();
	return true;
}