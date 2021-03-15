#include "r136.h"

bool RoomConnections::is_direction_command(Command command) const
{
	for (auto direction : { Command::east, Command::west, Command::north, Command::south, Command::up, Command::down })
		if (direction == command)
			return true;

	return false;
}

size_t RoomConnections::count() const
{
	return connections.size();
}

RoomID RoomConnections::operator[](Command direction) const
{
	if (!is_direction_command(direction))
		return RoomID::undefined;

	for (auto& element : connections)
		if (element.first == direction)
			return element.second;

	return RoomID::undefined;
}

bool RoomConnections::erase(Command direction)
{
	return connections.erase(direction) != 0;
}

std::map<Command, RoomID>::iterator RoomConnections::begin()
{
	return connections.begin();
}

std::map<Command, RoomID>::iterator RoomConnections::end()
{
	return connections.end();
}

bool RoomConnections::is_open(Command direction) const
{
	return (*this)[direction] != RoomID::undefined;
}

bool RoomConnections::set(Command direction, RoomID room)
{
	if (!is_direction_command(direction))
		return false;

	if (room == RoomID::undefined)
	{
		auto existing_target = connections.find(direction);
		if (existing_target == connections.end())
			return true;

		connections.erase(existing_target);
	}

	connections[direction] = room;
	return true;
}

Inventory::Inventory(int capacity) : BoundedCollection<ItemID>(capacity) {}

bool Inventory::add(ItemID item)
{
	return BoundedCollection<ItemID>::add(item);
}

bool Inventory::add(Item item)
{
	if (!BoundedCollection<ItemID>::add(item.id))
		return false;

	item.room = RoomID::owned;
	return true;
}

bool Inventory::remove(Item item)
{
	if (!BoundedCollection<ItemID>::remove(item.id))
		return false;

	item.room = RoomID::undefined;
	return true;
}

AnimateStatus next_status(AnimateStatus status)
{
	return static_cast<AnimateStatus>(to_value(status) + 1);
}

AnimateStatus operator++(AnimateStatus& status, int)
{
	AnimateStatus temp = status;
	status = next_status(status);
	return temp;
}

AnimateStatus& operator++(AnimateStatus& status)
{
	status = next_status(status);
	return status;
}

// This following section is a little bit of nastiness due to major OS platforms not agreeing in 2021, on one approach to idle-wait for a number of milliseconds
#ifdef _WIN32
#include <windows.h>
void sleep_ms(int n)
{
	Sleep(n);
}
#else
#include <unistd.h>
#include <map>
void sleep_ms(int n)
{
	usleep(n * 1000, );
}

#endif
