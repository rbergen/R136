﻿#include "base.h"
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

			console.main().print("Hier lig{0} ", count > 1 ? "gen" : "t");

			for (auto& element : core.items)
			{
				auto& item = *element.second;

				if (item.room != core.status.current_room)
					continue;

				console.main().print(item.name);

				switch (--count)
				{
				case 0:
					break;
				case 1:
					console.main().print(" en ");
					break;
				default:
					console.main().print(", ");
					break;
				}
			}

			console.main().print(".");
		}

		void show_open_directions(RoomConnections& connections)
		{
			size_t count = connections.count();

			if (!count)
				return;

			console.main().print("Je kunt naar ");

			for (auto& element : connections)
			{
				switch (element.first)
				{
				case Command::east:
					console.main().print("het oosten");
					break;
				case Command::west:
					console.main().print("het westen");
					break;
				case Command::north:
					console.main().print("het noorden");
					break;
				case Command::south:
					console.main().print("het zuiden");
					break;
				case Command::up:
					console.main().print("boven");
					break;
				case Command::down:
					console.main().print("beneden");
					break;

				default:
					break;
				}

				switch (--count)
				{
				case 0:
					break;
				case 1:
					console.main().print(" en ");
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
		static const wstring smoldering_forest_description = L"Om je heen zie je de smeulende resten van wat eens bos was.";

		auto current_room_id = core.status.current_room;
		auto& current_room = core.rooms[current_room_id];

		console.main().print(L"Je bevindt je {0}.\n", current_room.name);
		console.main().end_line();

		if (!is_room_lit(core))
		{
			console.main().print("Het is stekedonker en je ziet geen hand voor ogen.");
			console.main().end_line();
		}
		else
		{
			const wstring& description = core.status.has_tree_burned && current_room.type == RoomType::forest
				? smoldering_forest_description
				: current_room.description;

			if (description.size() > 0)
			{
				console.main().print(description);
				console.main().end_line();
			}

			show_items(core);
			console.main().end_line();
		}

		show_open_directions(current_room.connections);
		console.main().empty_line();
	}
}
