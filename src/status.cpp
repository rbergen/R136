#include "base.h"
#include "console.h"
#include "status.h"

namespace status
{
	namespace
	{
		void show_items(CoreData& core)
		{
			int count = 0;
			constexpr auto item_count = to_value(ItemID::COUNT);

			for (auto& element : core.items)
				if (element.second->room == core.status.current_room)
					count++;

			if (!count)
				return;

			console.main().print(select((count > 1 ? "Hier liggen " : "Hier ligt "), "You see "));

			for (auto& element : core.items)
			{
				auto& item = *element.second;

				if (item.room != core.status.current_room)
					continue;

				console.main().print(select(item.names));

				switch (--count)
				{
				case 0:
					break;
				case 1:
					console.main().print(select(" en ", " and "));
					break;
				default:
					console.main().print(", ");
					break;
				}
			}

			console.main().print(".");
		}

		void show_open_directions(CoreData& core, RoomConnections& connections)
		{
			size_t count = connections.count();

			if (!count)
				return;

			console.main().print(select("Je kunt naar ", "You can go "));

			for (auto& element : connections)
			{
				switch (element.first)
				{
				case Command::east:
					console.main().print(select("het oosten", "east"));
					break;
				case Command::west:
					console.main().print(select("het westen", "west"));
					break;
				case Command::north:
					console.main().print(select("het noorden", "north"));
					break;
				case Command::south:
					console.main().print(select("het zuiden", "south"));
					break;
				case Command::up:
					console.main().print(select("boven", "up"));
					break;
				case Command::down:
					console.main().print(select("beneden", "down"));
					break;

				default:
					break;
				}

				switch (--count)
				{
				case 0:
					break;
				case 1:
					console.main().print(select(" en ", " and "));
					break;
				default:
					console.main().print(", ");
					break;
				}
			}

			console.main().print(".");
		}
	}

	bool is_room_lit(CoreData& core)
	{
		auto& status = core.status;

		return core.rooms[status.current_room].type != RoomType::cave || core.flashlight().is_on;
	}

	void show_room_status(CoreData& core)
	{
		static const wstring smoldering_forest_description = select(
			L"Om je heen zie je de smeulende resten van wat eens bos was."
		,
			L"Around you, you see the smoldering remains of what used to be a forest."
		);

		auto current_room_id = core.status.current_room;
		auto& current_room = core.rooms[current_room_id];

		console.main().print(select(L"Je bevindt je {0}.\n", L"You are {0}.\n"), select(current_room.names));
		console.main().end_line();

		if (!is_room_lit(core))
		{
			console.main().print(select(
				"Het is stekedonker en je ziet geen hand voor ogen."
			,
				"It's pitch black and you can't see your hand in front of your face."
			));
			console.main().end_line();
		}
		else
		{
			const wstring& description = core.status.has_tree_burned && current_room.type == RoomType::forest
				? smoldering_forest_description
				: select(current_room.descriptions);

			if (!description.empty())
			{
				console.main().print(description);
				console.main().end_line();
			}

			show_items(core);
			console.main().end_line();
		}

		show_open_directions(core, current_room.connections);
		console.main().empty_line();
	}
}
