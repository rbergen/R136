#include "r136.h"
#include <iostream>
#include <fstream>

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
bool load<Animate>(std::ifstream& file, Animate& animate)
{
	if (!load(file, animate.room))
		return false;

	if (!load(file, animate.status))
		return false;

	return load(file, animate.strikes_left);
}

template<>
bool save<Animate>(std::ofstream& file, Animate& animate)
{
	if (!save(file, animate.room))
		return false;

	if (!save(file, animate.status))
		return false;

	return save(file, animate.strikes_left);
}

template<>
bool load<Status>(std::ifstream& file, Status& status)
{
	if (!load(file, status.current_room))
		return false;

	if (!load(file, status.has_tree_burned))
		return false;

	if (!load(file, status.is_lamp_on))
		return false;

	if (!load(file, status.lamp_points))
		return false;

	if (!load(file, status.life_points))
		return false;

	return load(file, status.paper_route_pos);
}

template<>
bool save<Status>(std::ofstream& file, Status& status)
{
	if (!save(file, status.current_room))
		return false;

	if (!save(file, status.has_tree_burned))
		return false;

	if (!save(file, status.is_lamp_on))
		return false;

	if (!save(file, status.lamp_points))
		return false;

	if (!save(file, status.life_points))
		return false;

	return save(file, status.paper_route_pos);
}

bool handle_load_fail(CoreData& core, std::ifstream& file)
{
	console.main().print_centered("Fout bij lezen status.");
	console.main().print("\n\n");
	console.main().print_centered("Je start een nieuw spel.");
	console.main().print("\n\n");

	file.close();
	remove(saved_status_path);

	console.main().wait_for_key();

	initialize(core);

	return false;
}

bool handle_save_fail(std::ofstream& file)
{
	console.main().print_centered("Fout bij wegschrijven status.");
	console.main().print("\n\n");
	console.main().print_centered("Status niet opgeslagen!");
	console.main().print("\n\n");

	file.close();
	remove(saved_status_path);

	return false;
}

bool load_game(CoreData& core)
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
		remove(saved_status_path);

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

	file.close();
	console.main().clear();
	return true;
}

bool save_game(CoreData& core)
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

			remove(saved_status_path);
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

	file.close();

	return true;
}

