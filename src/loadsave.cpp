#include "r136.h"

const char* saved_status_path = "r136data.rip";

void HandleFailedWrite(FILE* fp)
{
	print_to_main_window("Fout bij wegschrijven status.\n\nStatus niet opgeslagen!\n");

	fclose(fp);
	remove(saved_status_path);
}

void save_status(CoreData& core)
{
	FILE* fp;

	print_to_main_window("\n\nWil je je huidige status opslaan? ");

	if (tolower(advanced_getchar("jJnN")) != 'j')
	{
		print_to_main_window("\n");

		return;
	}

	while (!(fp = fopen(saved_status_path, "wb")))
	{
		print_to_main_window("\n\nKon het save-bestand niet openen voor schrijven. Nogmaals proberen? ");

		if (tolower(advanced_getchar("jJnN")) != 'j')
		{
			print_to_main_window("\n\nStatus niet opgeslagen!\n");

			remove(saved_status_path);

			return;
		}
	}

	print_to_main_window("\n");

	for (int i = 0; i < to_value(ItemID::COUNT); i++)
	{
		if (fp != 0 && fwrite(&core.items[static_cast<ItemID>(i)].room, sizeof(RoomID), 1, fp) < 1)
		{
			HandleFailedWrite(fp);
			return;
		}
	}

	for (int i = 0; i < to_value(RoomID::COUNT); i++)
	{
		for (int j = 0; j < 6; j++) 
		{
			RoomID connected_room = core.rooms[static_cast<RoomID>(i)].connections[static_cast<Command>(j)];
			if (fp != 0 && fwrite(&connected_room, sizeof(RoomID), 1, fp) < 1)
			{
				HandleFailedWrite(fp);
				return;
			}
		}
	}

	for (int i = 0; i < to_value(AnimateID::COUNT); i++)
	{
		if (fp != 0 && fwrite(&core.animates[static_cast<AnimateID>(i)], sizeof(Animate), 1, fp) < 1)
		{
			HandleFailedWrite(fp);
			return;
		}
	}

	size_t inventory_size = core.inventory.count();
	if (fp != 0 && fwrite(&inventory_size, sizeof(size_t), 1, fp) < 1)
	{
		HandleFailedWrite(fp);
		return;
	}

	for ()
	if (fp != 0 && fwrite(core.inventory, sizeof(char), 10, fp) < 10)
	{
		HandleFailedWrite(fp);
		return;
	}

	if (fp != 0 && fwrite(&core.status, sizeof(Status), 1, fp) < 1)
	{
		HandleFailedWrite(fp);
		return;
	}

	if (fp != 0)
		fclose(fp);
}

void HandleFailedRead(CoreData& core, FILE* fp)
{
	print_to_main_window("Fout bij lezen status.\n\nJe start een nieuw spel.\n\n");

	fclose(fp);
	remove(saved_status_path);

	wait_for_key();

	initialize(core);
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

	for (i = 0; i < 25; i++)
	{
		if (fp != 0 && fread(&core.items[i].room, sizeof(char), 1, fp) < 1)
		{
			HandleFailedRead(core, fp);
			return false;
		}
	}

	for (i = 0; i < 80; i++)
	{
		if (fp != 0 && fread(core.rooms[i].connections, sizeof(char) * 6, 1, fp) < 1)
		{
			HandleFailedRead(core, fp);
			return false;
		}
	}

	for (i = 0; i < 21; i++)
	{
		if (fp != 0 && fread(&core.animates[i], sizeof(Animate), 1, fp) < 1)
		{
			HandleFailedRead(core, fp);
			return false;
		}
	}

	if (fp != 0 && fread(core.inventory, sizeof(char), 10, fp) < 10)
	{
		HandleFailedRead(core, fp);
		return false;
	}

	if (fp != 0 && fread(&core.status, sizeof(Status), 1, fp) < 1)
	{
		HandleFailedRead(core, fp);
		return false;
	}

	print_to_main_window("\n");
	
	if (fp != 0)
		fclose(fp);
	
	return true;
}

