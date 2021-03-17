#include "r136.h"
#include <iostream>
#include <fstream>

const char* saved_status_path = "r136data.rip";

bool load_animate(std::ifstream& file, Animate& animate)
{
	std::underlying_type_t<RoomID> room;
	std::underlying_type_t<AnimateStatus> status;

	file
		>> room
		>> status
		>> animate.strikes_left;

	if (!file.good())
		return false;

	animate.room = static_cast<RoomID>(room);
	animate.status = static_cast<AnimateStatus>(status);

	return true;
}

bool save_animate(std::ofstream& file, Animate& animate)
{
	file
		<< to_value(animate.room)
		<< to_value(animate.status)
		<< animate.strikes_left;

	return file.good();
}

bool load_status(std::ifstream& file, Status& status)
{
	std::underlying_type_t<RoomID> current_room;

	file
		>> current_room
		>> status.has_tree_burned
		>> status.is_lamp_on
		>> status.lamp_points
		>> status.life_points
		>> status.paper_route_pos;

	if (!file.good())
		return false;

	status.current_room = static_cast<RoomID>(current_room);

	return true;
}

bool save_status(std::ofstream& file, Status& status)
{
	file
		<< to_value(status.current_room)
		<< status.has_tree_burned
		<< status.is_lamp_on
		<< status.lamp_points
		<< status.life_points
		<< status.paper_route_pos;

	return file.good();
}

bool handle_load_fail(CoreData& core, std::ifstream& file)
{
	console.main().print("Fout bij lezen status.\n\nJe start een nieuw spel.\n\n");

	file.close();
	remove(saved_status_path);

	console.main().wait_for_key();

	initialize(core);

	return false;
}

bool handle_save_fail(std::ofstream& file)
{
	console.main().print("Fout bij wegschrijven status.\n\nStatus niet opgeslagen!\n");

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

	if (tolower(console.main().get_char_input("12")) != '2')
	{
		file.close();
		remove(saved_status_path);

		return false;
	}

	console.main().print("\n");

	std::underlying_type_t<RoomID> room;
	ItemID item_id;
	RoomID room_id;

	for (int i = 0; i < to_value(ItemID::COUNT); i++) 
	{
		if (file >> room, !file.good())
			return handle_load_fail(core, file);
		
		item_id = static_cast<ItemID>(i);
		room_id = static_cast<RoomID>(room);

		core.items[static_cast<ItemID>(i)].room = room_id;
		if (room_id == RoomID::owned)
			core.inventory.add(item_id);
	}

	for (int i = 0; i < to_value(RoomID::COUNT); i++)
		for (int j = 0; j < 6; j++)
		{
			if (file >> room, !file.good())
				return handle_load_fail(core, file);

			core.rooms[static_cast<RoomID>(i)].connections.set(static_cast<Command>(j), static_cast<RoomID>(room));
		}

	Animate animate{};
	for (int i = 0; i < to_value(AnimateID::COUNT); i++)
	{
		if (!load_animate(file, animate))
			return handle_load_fail(core, file);

		core.animates[static_cast<AnimateID>(i)].load(animate);
	}

	if (!load_status(file, core.status))
		return handle_load_fail(core, file);

	console.main().print("\n");
	
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
		if (file << to_value(core.items[static_cast<ItemID>(i)].room), !file.good())
			return handle_save_fail(file);

	for (int i = 0; i < to_value(RoomID::COUNT); i++)
		for (int j = 0; j < 6; j++)
			if (file << to_value(core.rooms[static_cast<RoomID>(i)].connections[static_cast<Command>(j)]), !file.good())
				return handle_save_fail(file);

	for (int i = 0; i < to_value(AnimateID::COUNT); i++)
		if (!save_animate(file, core.animates[static_cast<AnimateID>(i)]))
			return handle_save_fail(file);

	for (ItemID item : core.inventory)
		if (file << to_value(item), !file.good())
			return handle_save_fail(file);

	if (!save_status(file, core.status))
		return handle_save_fail(file);

	file.close();

	return true;
}

