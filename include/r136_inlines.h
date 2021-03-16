#pragma once

#include "r136.h"

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

	item.room = RoomID::owned;
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

// This following section is a little bit of nastiness due to major OS platforms not agreeing in 2021, on one approach to idle-wait for a number of milliseconds
#ifdef _WIN32
#include <windows.h>
inline void sleep_ms(int n)
{
	Sleep(n);
}
#else
#include <unistd.h>
#include <map>
inline void sleep_ms(int n)
{
	usleep(n * 1000, );
}

#endif
