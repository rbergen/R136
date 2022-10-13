#include "base.h"
#include "console.h"
#include "animates.h"
#include "items.h"
#include "constants.h"
#include "startup.h"
#include "general.h"
#include <algorithm>
#include <ctime>
#include <functional>
#include <memory>
#include <iostream>

namespace startup
{
	namespace 
	{
		#include "data/rooms.h"
		#include "data/connections.h"
		#include "data/animates.h"
		#include "data/items.h"

		template <typename TKey, class TValue>
		void fill_map(EntityMap<TKey, TValue>& map, std::unique_ptr<TValue> values[], int count)
		{
			static_assert(std::is_base_of<Entity<TKey>, TValue>::value, "TValue must inherit from Entity<TKey>");

			map.clear();

			for (int i = 0; i < count; i++)
			{
				values[i]->id = static_cast<TKey>(i);
				map.add_or_set(std::move(values[i]));
			}
		}

		bool set_room_connections(std::unique_ptr<Room> rooms[], int count)
		{
			// Interconnect rooms with neighbours
			for (int i = 0; i < count; i++)
			{
				Room& room = *rooms[i];
				room.connections.clear();
				room.connections.set(Command::east, static_cast<RoomID>(i + 1));
				room.connections.set(Command::west, static_cast<RoomID>(i - 1));
				room.connections.set(Command::north, static_cast<RoomID>(i - 5));
				room.connections.set(Command::south, static_cast<RoomID>(i + 5));
			}

			// Seperate layers
			for (int i = 0; i < count; i += 20)
			{
				for (int j = 0; j < 16; j += 5)
				{
					rooms[i + j + 4]->connections.erase(Command::east);
					rooms[i + j]->connections.erase(Command::west);
				}

				for (int j = 0; j < 5; j++)
				{
					rooms[i + j]->connections.erase(Command::north);
					rooms[i + j + 15]->connections.erase(Command::south);
				}
			}

			// Connect layers
			for (auto& connection : level_connections)
				rooms[to_value(connection.from)]->connections.set(connection.direction, connection.to);

			// Blocked routes
			for (auto& block : blocked_connections)
				rooms[to_value(block.room)]->connections.erase(block.direction);

			return true;
		}
	}

	void initialize(CoreData& core)
	{
		core.paperroute = { RoomID::capital_p_cave, RoomID::a_cave, RoomID::p_cave, RoomID::i_cave, RoomID::e_cave, RoomID::r_cave };

		core.status.current_room = RoomID::forest0;
		core.status.paper_route_pos = 0;
		core.status.life_points = constants::max_life_points;
		core.status.has_tree_burned = false;

		srand(abs((int)time(NULL)));

		set_room_connections(rooms, to_value(RoomID::COUNT));

		fill_map(core.rooms, rooms, to_value(RoomID::COUNT));
		fill_map(core.animates, animates, to_value(AnimateID::COUNT));
		fill_map(core.items, items, to_value(ItemID::COUNT));

		core.set_flashlight(dynamic_cast<Flashlight*>(&core.items[ItemID::flashlight]));
	}

	void parse_arguments(CoreData& core, int argc, char* argv[])
	{
		core.language = Language::Dutch;

		if (argc < 2)
			return;

		for (int i = 1; i < argc; i++) 
		{
			string arg = argv[i];
			std::transform(arg.begin(), arg.end(), arg.begin(),
				[](unsigned char c) { return std::tolower(c); });
			
			if (!arg.compare("-h") || !arg.compare("--help"))
				general::show_arguments();

			else if (!arg.compare("-d") || !arg.compare("--dutch") || !arg.compare("-n") || !arg.compare("--nederlands"))
				core.language = Language::Dutch;

			else if (!arg.compare("-e") || !arg.compare("--english") || !arg.compare("--engels"))
				core.language = Language::English;
	
			else
			{
				std::cerr << "Ongeldige optie/invalid argument: " << arg << "\n\n";
				general::show_arguments();
			}
		}
	}
}

