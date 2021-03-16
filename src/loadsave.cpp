#include "r136.h"

const char* saved_status_path = "r136data.rip";

bool HandleFailedWrite(FILE* fp)
{
	console.main().print("Fout bij wegschrijven status.\n\nStatus niet opgeslagen!\n");

	fclose(fp);
	remove(saved_status_path);

	return false;
}

bool save_status(CoreData& core)
{
	FILE* fp;

	console.main().print("\n\nWil je je huidige status opslaan? ");

	if (tolower(console.main().get_char_input("jJnN")) != 'j')
	{
		console.main().print("\n");

		return true;
	}

	while (!(fp = fopen(saved_status_path, "wb")))
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
	console.main().print("Fout bij lezen status.\n\nJe start een nieuw spel.\n\n");

	fclose(fp);
	remove(saved_status_path);

	console.main().wait_for_key();

	initialize(core);

	return false;
}

bool load_status(CoreData& core)
{
	FILE* fp;

	if (!(fp = fopen(saved_status_path, "rb")))
	{
		console.main().print_centered("Druk op een toets om te beginnen");

		console.main().wait_for_key();
		return false;
	}

	console.main().print_centered("Toets 1 voor een nieuw spel, 2 voor een gesaved spel: ");

	if (tolower(console.main().get_char_input("12")) != '2')
	{
		if (fp != 0) 
			fclose(fp);

		remove(saved_status_path);

		return false;
	}

	console.main().print("\n");

	RoomID room_id = RoomID();
	for (int i = 0; i < to_value(ItemID::COUNT); i++) 
	{
		if (fp != 0 && fread(&room_id, sizeof(RoomID), 1, fp) < 1)
			return HandleFailedRead(core, fp);

		core.items[static_cast<ItemID>(i)].room = room_id;
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

	console.main().print("\n");
	
	if (fp != 0)
		fclose(fp);
	
	return true;
}

