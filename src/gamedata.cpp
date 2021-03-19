#include "base.h"
#include "console.h"
#include "startup.h"
#include "gamedata.h"
#include <iostream>
#include <fstream>

namespace game_data
{
	namespace
	{
		const char* saved_status_path = "r136data.rip";

		template<class T>
		bool load(std::ifstream& file, T& value)
		{
			file.read((char*)&value, sizeof(T));
			return file.good();
		}

		template<class T>
		bool save(std::ofstream& file, T& value)
		{
			file.write((char*)&value, sizeof(T));
			return file.good();
		}

		template<>
		bool load(std::ifstream& file, Animate& animate)
		{
			return load(file, animate.room)
				&& load(file, animate.status)
				&& load(file, animate.strikes_left);
		}

		template<>
		bool save(std::ofstream& file, Animate& animate)
		{
			return save(file, animate.room)
				&& save(file, animate.status)
				&& save(file, animate.strikes_left);
		}

		template<>
		bool load(std::ifstream& file, Status& status)
		{
			return load(file, status.current_room)
				&& load(file, status.has_tree_burned)
				&& load(file, status.life_points)
				&& load(file, status.paper_route_pos);
		}

		template<>
		bool save(std::ofstream& file, Status& status)
		{
			return save(file, status.current_room) 
				&& save(file, status.has_tree_burned)
				&& save(file, status.life_points)
				&& save(file, status.paper_route_pos);
		}

		template<>
		bool load(std::ifstream& file, Flashlight& flashlight)
		{
			return load(file, flashlight.is_on) 
				&& load(file, flashlight.battery_level) 
				&& load(file, flashlight.has_bunny_batteries);
		}

		template<>
		bool save(std::ofstream& file, Flashlight& flashlight)
		{
			return save(file, flashlight.is_on)
				&& save(file, flashlight.battery_level)
				&& save(file, flashlight.has_bunny_batteries);
		}

		bool handle_load_fail(CoreData& core, std::ifstream& file)
		{
			console.main().print_centered("Fout bij lezen status.");
			console.main().print("\n\n");
			console.main().print_centered("Je start een nieuw spel.");
			console.main().print("\n\n");

			file.close();
			game_data::remove();

			console.main().wait_for_key();

			startup::initialize(core);

			return false;
		}

		bool handle_save_fail(std::ofstream& file)
		{
			console.main().print_centered("Fout bij wegschrijven status.");
			console.main().print("\n\n");
			console.main().print_centered("Status niet opgeslagen!");
			console.main().print("\n\n");

			file.close();
			game_data::remove();

			return false;
		}
	}

	bool load(CoreData& core)
	{
		std::ifstream file;

		file.open(saved_status_path, std::ios::in | std::ios::binary);

		if (!file.good())
		{
			console.main().print_centered("Druk op een toets om te beginnen");

			console.main().wait_for_key();
			return false;
		}

		console.main().print_centered("Toets 1 voor een nieuw spel, 2 voor een gesaved spel: ");

		if (console.main().get_char_input("12") != '2')
		{
			file.close();
			game_data::remove();

			return false;
		}

		console.main().print("\n");

		ItemID item_id;
		RoomID room_id;

		for (int i = 0; i < to_value(ItemID::COUNT); i++)
		{
			if (!load(file, room_id))
				return handle_load_fail(core, file);

			item_id = static_cast<ItemID>(i);

			core.items[static_cast<ItemID>(i)].room = room_id;
			if (room_id == RoomID::owned)
				core.inventory.add(item_id);
		}

		for (int i = 0; i < to_value(RoomID::COUNT); i++)
			for (int j = 0; j < 6; j++)
			{
				if (!load(file, room_id))
					return handle_load_fail(core, file);

				core.rooms[static_cast<RoomID>(i)].connections.set(static_cast<Command>(j), room_id);
			}

		Animate animate{};

		for (int i = 0; i < to_value(AnimateID::COUNT); i++)
		{
			if (!load(file, animate))
				return handle_load_fail(core, file);

			core.animates[static_cast<AnimateID>(i)].load(animate);
		}

		if (!load(file, core.status))
			return handle_load_fail(core, file);

		if (!load(file, core.flashlight()))
			return handle_load_fail(core, file);

		file.close();
		console.main().clear();
		return true;
	}

	bool save(CoreData& core)
	{
		std::ofstream file;

		console.main().print("\n\nWil je je huidige status opslaan? ");

		if (tolower(console.main().get_char_input("jJnN")) != 'j')
		{
			console.main().print("\n");
			return true;
		}

		while (file.open(saved_status_path, std::ios::out | std::ios::binary | std::ios::trunc), !file.good())
		{
			console.main().print("\n\nKon het save-bestand niet openen voor schrijven. Nogmaals proberen? ");

			if (tolower(console.main().get_char_input("jJnN")) != 'j')
			{
				console.main().print("\n\nStatus niet opgeslagen!\n");

				return false;
			}
		}

		console.main().print("\n");

		for (int i = 0; i < to_value(ItemID::COUNT); i++)
			if (!save(file, core.items[static_cast<ItemID>(i)].room))
				return handle_save_fail(file);

		RoomID room;

		for (int i = 0; i < to_value(RoomID::COUNT); i++)
			for (int j = 0; j < 6; j++)
			{
				room = core.rooms[static_cast<RoomID>(i)].connections[static_cast<Command>(j)];
				if (!save(file, room))
					return handle_save_fail(file);
			}

		for (int i = 0; i < to_value(AnimateID::COUNT); i++)
			if (!save(file, core.animates[static_cast<AnimateID>(i)]))
				return handle_save_fail(file);

		if (!save(file, core.status))
			return handle_save_fail(file);

		if (!save(file, core.flashlight()))
			return handle_save_fail(file);

		file.close();

		return true;
	}

	void remove() 
	{
		::remove(saved_status_path);
	}
}
