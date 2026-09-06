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