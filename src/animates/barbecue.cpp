#include "base.h"
#include "console.h"
#include "animates.h"

Barbecue::Barbecue(RoomID room) : Animate(room) {}

bool Barbecue::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::barbecue].status)
	{
	case AnimateStatus::initial_burn:
		console.main().print(select(
			"Op deze open plek staat een barbecue gezellig te branden."
		,
			"In this open space, a barbecue is burning nicely."
		));

		break;

	case AnimateStatus::hashis_on_fire:
		console.main().print(select(
			"Als je de hasj op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt er niets."
		,
			"When you throw the hashis on the barbecue, the flame changes colour. Beyond that, nothing happens."
		));

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::meat_on_fire:
		console.main().print(select(
			"Als je het vlees op de barbecue gooit verschiet de vlam van kleur. Verder gebeurt er niets."
		,
			"When you throw the meat on the barbecue, the flame changes colour. Beyond that, nothing happens."
		));

		core.animates[AnimateID::barbecue].status = AnimateStatus::ingredient_burning;

		break;

	case AnimateStatus::ingredient_burning:
		console.main().print(select(
			"De barbecue brandt nog steeds, alleen iets onrustiger dan eerst."
		,
			"The barbecue is still burning, just a little more flickery than before."
		));

		break;

	case AnimateStatus::cookie_is_baking:
		console.main().print(select(
			L"Een grote rookontwikkeling treedt op wanneer het tweede ingrediënt in de barbecue belandt.\n"
			 "Knetterend smelten de 2 ingrediënten om tot een koekje."
		,
			L"A lot of smoke develops when the second ingredient lands on the barbecue."
			 "With crackling noises, the two ingredients blend together into a cookie."
		));

		core.items[ItemID::cookie].room = core.status.current_room;
		core.animates[AnimateID::barbecue].status = AnimateStatus::initial_burn;

		break;

	default:
		break;
	}

	console.main().empty_line();
	return true;
}