#pragma once

// inlines/items.h

#include "../base.h"
#include "types/items.h"

inline void Bone::use_if_target_present(CoreData& core)
{
	target_status(core) = AnimateStatus::door_open;
}

inline void Ingredient::use_if_target_present(CoreData& core)
{
	use_to_status(core, target_status(core) == AnimateStatus::initial_burn ? sets_target_to_status : AnimateStatus::cookie_is_baking);
}

inline void Crystal::use_if_target_present(CoreData& core)
{
	use_to_status(core, next_status(target_status(core)));
}

inline void Nightcap::use_if_target_present(CoreData& core)
{
	if (target_status(core) == AnimateStatus::sleeping_lightly)
		use_to_status(core);
	else
		report_pointless_use();
}

inline void Gasmask::use(CoreData& core)
{
	console.main().print("Je hebt het gasmasker al op.\n");
}

inline void HeatSuit::use(CoreData& core)
{
	console.main().print("Je hebt het hittepak al aan.\n");
}

inline Flashlight::Flashlight(string name, const wstring description, RoomID room) : Item(name, description, room)
{
	is_on = false;
	has_bunny_batteries = false;
	battery_level = constants::max_lamp_points;
}
