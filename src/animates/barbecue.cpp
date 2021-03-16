#include "r136.h"
#include "animates.h"

Barbecue::Barbecue(RoomID room) : Animate(room) {}

bool Barbecue::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::barbecue].status)
	{
	case AnimateStatus::initial_burn:
		console.main().print("Op deze open plek staat een barbecue gezellig te branden.\n\n");

		break;

	case AnimateStatus::hashis_on_fire:
		console.main().print("Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt\n");
		console.main().print("er niets.\n\n");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::meat_on_fire:
		console.main().print("Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder\n");
		console.main().print("gebeurt er niets.\n\n");

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::ingredient_burning:
		console.main().print("De barbecue brandt nog steeds, alleen iets onrustiger dan eerst.\n\n");

		break;

	case AnimateStatus::cookie_is_baking:
		console.main().write(L"Een grote rookontwikkeling treedt op wanneer het tweede ingrediënt in de\n");
		console.main().print("barbecue belandt.\n");
		console.main().write(L"Knetterend smelten de 2 ingrediënten om tot een koekje.\n\n");

		core.items[ItemID::cookie].room = core.status.current_room;
		core.animates[AnimateID::barbecue].status = AnimateStatus::initial_burn;

		break;
	}

	return true;
}