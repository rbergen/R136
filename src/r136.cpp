#include "r136.h"
#include "status.h"

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

	auto existing_target = connections.find(direction);
	return existing_target == connections.end() ? RoomID::undefined : existing_target->second;
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

void Animate::load(Animate& animate)
{
	room = animate.room;
	strikes_left = animate.strikes_left;
	status = animate.status;
}

void Item::inspect(CoreData& core)
{
	if (!status::is_room_lit(core))
	{
		console.main().print("Het is veel te donker om wat dan ook te bekijken.\n");
		return;
	}

	console.main().print(core.items[id].description);
	console.main().print("\n");
}
