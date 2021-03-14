#include "r136.h"

const char* saved_status_path = "r136data.rip";

bool HandleFailedWrite(FILE* fp)
{
	print_to_main_window("Fout bij wegschrijven status.\n\nStatus niet opgeslagen!\n");

	fclose(fp);
	remove(saved_status_path);

	return false;
}

bool save_status(CoreData& core)
{
	FILE* fp;

	print_to_main_window("\n\nWil je je huidige status opslaan? ");

	if (tolower(advanced_getchar("jJnN")) != 'j')
	{
		print_to_main_window("\n");

		return true;
	}

	while (!(fp = fopen(saved_status_path, "wb")))
	{
		print_to_main_window("\n\nKon het save-bestand niet openen voor schrijven. Nogmaals proberen? ");

		if (tolower(advanced_getchar("jJnN")) != 'j')
		{
			print_to_main_window("\n\nStatus niet opgeslagen!\n");

			remove(saved_status_path);

			return false;
		}
	}

	print_to_main_window("\n");

	for (int i = 0; i < to_value(ItemID::COUNT); i++)
		if (fp != 0 && fwrite(&core.items[static_cast<ItemID>(i)].room, sizeof(RoomID), 1, fp) < 1)
			return HandleFailedWrite(fp);

	for (int i = 0; i < to_value(RoomID::COUNT); i++)
		for (int j = 0; j < 6; j++) 
		{
			RoomID connected_room = core.rooms[static_cast<RoomID>(i)].connections[static_cast<Command>(j)];
			if (fp != 0 && fwrite(&connected_room, sizeof(RoomID), 1, fp) < 1)
				return HandleFailedWrite(fp);
		}

	for (int i = 0; i < to_value(AnimateID::COUNT); i++)
		if (fp != 0 && fwrite(&core.animates[static_cast<AnimateID>(i)], sizeof(Animate), 1, fp) < 1)
			return HandleFailedWrite(fp);

	size_t inventory_size = core.inventory.count();
	if (fp != 0 && fwrite(&inventory_size, sizeof(size_t), 1, fp) < 1)
		return HandleFailedWrite(fp);

	for (ItemID item : core.inventory)
		if (fp != 0 && fwrite(&item, sizeof(ItemID), 1, fp) < 1)
			return HandleFailedWrite(fp);

	if (fp != 0 && fwrite(&core.status, sizeof(Status), 1, fp) < 1)
		return HandleFailedWrite(fp);

	if (fp != 0)
		fclose(fp);

	return true;
}

bool HandleFailedRead(CoreData& core, FILE* fp)
{
	print_to_main_window("Fout bij lezen status.\n\nJe start een nieuw spel.\n\n");

	fclose(fp);
	remove(saved_status_path);

	wait_for_key();

	initialize(core);

	return false;
}

bool load_status(CoreData& core)
{
	FILE* fp;
	int i;

	if (!(fp = fopen(saved_status_path, "rb")))
	{
		write_centered(main_window, "Druk op een toets om te beginnen");

		wait_for_key();
		return false;
	}

	write_centered(main_window, "Toets 1 voor een nieuw spel, 2 voor een gesaved spel: ");

	if (tolower(advanced_getchar("12")) != '2')
	{
		if (fp != 0) 
			fclose(fp);

		remove(saved_status_path);

		return false;
	}

	print_to_main_window("\n");

	RoomID room_id = RoomID();
	for (int i = 0; i < to_value(ItemID::COUNT); i++) 
	{
		if (fp != 0 && fread(&room_id, sizeof(RoomID), 1, fp) < 1)
			return HandleFailedRead(core, fp);

		ore.items[static_cast<ItemID>(i)].room = room_id;
	}

	for (int i = 0; i < to_value(RoomID::COUNT); i++)
		for (int j = 0; j < 6; j++)
		{
			if (fp != 0 && fread(&room_id, sizeof(RoomID), 1, fp) < 1)
				return HandleFailedRead(core, fp);

			core.rooms[static_cast<RoomID>(i)].connections.set(static_cast<Command>(j), room_id);
		}

	Animate animate{};
	for (int i = 0; i < to_value(AnimateID::COUNT); i++)
	{
		if (fp != 0 && fread(&animate, sizeof(Animate), 1, fp) < 1)
			return HandleFailedRead(core, fp);

		core.animates[static_cast<AnimateID>(i)] = animate;
	}

	size_t inventory_size;
	if (fp != 0 && fread(&inventory_size, sizeof(size_t), 1, fp) < 1)
		return HandleFailedRead(core, fp);

	ItemID item;
	while (inventory_size--) 
	{
		if (fp != 0 && fread(&item, sizeof(ItemID), 1, fp) < 1)
			return HandleFailedRead(core, fp);
		else
			core.inventory.add(item);
	}

	if (fp != 0 && fread(&core.status, sizeof(Status), 1, fp) < 1)
		return HandleFailedRead(core, fp);

	print_to_main_window("\n");
	
	if (fp != 0)
		fclose(fp);
	
	return true;
}

