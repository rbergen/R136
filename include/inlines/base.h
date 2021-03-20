#pragma once

// inlines/base.h

#include "types/base.h"
#include "types/console.h"
#include "constants.h"
#include "templates/base.h"

inline Flashlight& CoreData::flashlight()
{
	return *flashlight_ptr;
}

inline CoreData::CoreData() :
	inventory(Inventory(constants::max_owned_items))

{}

inline void CoreData::set_flashlight(Flashlight * flashlight_ptr)
{
	this->flashlight_ptr = flashlight_ptr;
}

inline size_t RoomConnections::count() const
{
	return connections.size();
}

inline bool RoomConnections::erase(Command direction)
{
	return connections.erase(direction) != 0;
}

inline void RoomConnections::clear()
{
	connections.clear();
}

inline std::map<Command, RoomID>::iterator RoomConnections::begin()
{
	return connections.begin();
}

inline std::map<Command, RoomID>::iterator RoomConnections::end()
{
	return connections.end();
}

inline bool RoomConnections::is_open(Command direction) const
{
	return (*this)[direction] != RoomID::undefined;
}

inline Item::Item(const string name, const wstring description, RoomID room, AnimateID usable_on, AnimateStatus sets_target_to_status) :
	name(name),
	description(description),
	room(room),
	usable_on(usable_on),
	sets_target_to_status(sets_target_to_status)
{}

inline bool Item::use_with_target_present(CoreData& core)
{
	return use_to_status(core);
}

inline bool Item::is_target_present(CoreData& core)
{
	return core.animates.contains(usable_on) && core.animates[usable_on].room == core.status.current_room;
}

inline AnimateStatus& Item::target_status(CoreData& core)
{
	return core.animates[usable_on].status;
}

inline void Item::report_pointless_use()
{
	console.main().print("Dat heeft geen zin.\n");
}

inline bool Item::use_to_status(CoreData& core, AnimateStatus to_status)
{
	if (to_status == AnimateStatus::undefined)
		to_status = sets_target_to_status;

	if (to_status == AnimateStatus::undefined || to_value(usable_on) < 0)
		return false;

	core.inventory.remove(*this);
	core.animates[usable_on].status = to_status;

	return true;
}

inline bool Item::use(CoreData& core)
{
	if (is_target_present(core))
		return use_with_target_present(core);

	report_pointless_use();
	return true;
}

inline bool Item::is_in_posession()
{
	return room == RoomID::in_posession;
}

inline Inventory::Inventory(int capacity) : BoundedCollection<ItemID>(capacity) {}

inline bool Inventory::add(ItemID item)
{
	return BoundedCollection<ItemID>::add(item);
}

inline bool Inventory::add(Item& item)
{
	if (!BoundedCollection<ItemID>::add(item.id))
		return false;

	item.room = RoomID::in_posession;
	return true;
}

inline bool Inventory::remove(Item& item)
{
	if (!BoundedCollection<ItemID>::remove(item.id))
		return false;

	item.room = RoomID::undefined;
	return true;
}

inline AnimateStatus next_status(AnimateStatus status)
{
	return static_cast<AnimateStatus>(to_value(status) + 1);
}

inline AnimateStatus operator++(AnimateStatus& status, int)
{
	AnimateStatus temp = status;
	status = next_status(status);
	return temp;
}

inline AnimateStatus& operator++(AnimateStatus& status)
{
	status = next_status(status);
	return status;
}