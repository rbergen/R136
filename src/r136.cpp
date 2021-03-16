#include "r136.h"

bool RoomConnections::is_direction_command(Command command) const
{
	for (auto direction : { Command::east, Command::west, Command::north, Command::south, Command::up, Command::down })
		if (direction == command)
			return true;

	return false;
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

