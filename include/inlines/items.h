#pragma once

// inlines/items.h

#include "types/base.h"
#include "templates/items.h"

inline bool Bone::use_with_target_present(CoreData& core)
{
	target_status(core) = AnimateStatus::door_open;
	
	return true;
}

inline bool Ingredient::use_with_target_present(CoreData& core)
{
	use_to_status(core, target_status(core) == AnimateStatus::initial_burn ? sets_target_to_status : AnimateStatus::cookie_is_baking);

	return true;
}

inline bool Crystal::use_with_target_present(CoreData& core)
{
	use_to_status(core, next_status(target_status(core)));

	return true;
}

inline bool Nightcap::use_with_target_present(CoreData& core)
{
	if (target_status(core) == AnimateStatus::sleeping_lightly)
		return use_to_status(core);

	report_pointless_use(core);
	return false;
}

inline bool Gasmask::use(CoreData& core)
{
	console.main().print(select("Je hebt het gasmasker al op.", "You're already wearing the gas mask."));
	console.main().empty_line();
	return false;
}

inline bool ThermalSuit::use(CoreData& core)
{
	console.main().print(select("Je hebt het hittepak al aan.", "You're already wearing the thermal suit."));
	console.main().empty_line();
	return false;
}

inline CombinableItem::CombinableItem(const std::vector<string> names, const std::vector<wstring> descriptions, RoomID room, ItemID combines_with)
	: Item(names, descriptions, room, item::combines_with(combines_with)) {}

inline bool CombinableItem::combines_with(ItemID item)
{
	return item::combines_with(usable_on) == item;
}

inline Flashlight::Flashlight(const std::vector<string> names, const std::vector <wstring> descriptions, RoomID room) : CombinableItem(names, descriptions, room, ItemID::batteries)
{
	is_on = false;
	has_bunny_batteries = false;
	battery_level = constants::max_lamp_points;
}
