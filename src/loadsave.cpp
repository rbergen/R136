#include "r136.h"

const char* LOADSAVEDATAPATH = "r136data.rip";

void HandleFailedWrite(FILE *fp)
{
	print_to_main_window("Fout bij wegschrijven status.\n\nStatus niet opgeslagen!\n");

	fclose(fp);
	remove(LOADSAVEDATAPATH);
}

void SaveStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	print_to_main_window("\n\nWil je je huidige status opslaan? ");

	if (tolower(advanced_getchar("jJnN")) != 'j')
	{
		print_to_main_window("\n");

		return;
	}

	while (!(fp = fopen(LOADSAVEDATAPATH, "wb")))
	{
		print_to_main_window("\n\nKon het save-bestand niet openen voor schrijven. Nogmaals proberen? ");

		if (tolower(advanced_getchar("jJnN")) != 'j')
		{
			print_to_main_window("\n\nStatus niet opgeslagen!\n");

			remove(LOADSAVEDATAPATH);

			return;
		}
	}

	print_to_main_window("\n");

	for (i = 0; i < 25; i++)
	{
		if (fp != 0 && fwrite(&progdata.items[i].room, sizeof(char), 1, fp) < 1)
		{
			HandleFailedWrite(fp);
			return;
		}
	}

	for (i = 0; i < 80; i++)
	{
		if (fp != 0 && fwrite(progdata.rooms[i].connect, sizeof(char) * 6, 1, fp) < 1)
		{
			HandleFailedWrite(fp);
			return;
		}
	}

	for (i = 0; i < 21; i++)
	{
		if (fp != 0 && fwrite(&progdata.animates[i], sizeof(Animate), 1, fp) < 1)
		{
			HandleFailedWrite(fp);
			return;
		}
	}

	if (fp != 0 && fwrite(progdata.owneditems, sizeof(char), 10, fp) < 10)
	{
		HandleFailedWrite(fp);
		return;
	}

	if (fp != 0 && fwrite(&progdata.status, sizeof(Status), 1, fp) < 1)
	{
		HandleFailedWrite(fp);
		return;
	}

	if (fp != 0)
		fclose(fp);
}

void HandleFailedRead(Progdata &progdata, FILE *fp)
{
	print_to_main_window("Fout bij lezen status.\n\nJe start een nieuw spel.\n\n");

	fclose(fp);
	remove(LOADSAVEDATAPATH);

	wait_for_key();

	Initialize(progdata);
}

bool LoadStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	if (!(fp = fopen(LOADSAVEDATAPATH, "rb")))
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

		remove(LOADSAVEDATAPATH);

		return false;
	}

	print_to_main_window("\n");

	for (i = 0; i < 25; i++)
	{
		if (fp != 0 && fread(&progdata.items[i].room, sizeof(char), 1, fp) < 1)
		{
			HandleFailedRead(progdata, fp);
			return false;
		}
	}

	for (i = 0; i < 80; i++)
	{
		if (fp != 0 && fread(progdata.rooms[i].connect, sizeof(char) * 6, 1, fp) < 1)
		{
			HandleFailedRead(progdata, fp);
			return false;
		}
	}

	for (i = 0; i < 21; i++)
	{
		if (fp != 0 && fread(&progdata.animates[i], sizeof(Animate), 1, fp) < 1)
		{
			HandleFailedRead(progdata, fp);
			return false;
		}
	}

	if (fp != 0 && fread(progdata.owneditems, sizeof(char), 10, fp) < 10)
	{
		HandleFailedRead(progdata, fp);
		return false;
	}

	if (fp != 0 && fread(&progdata.status, sizeof(Status), 1, fp) < 1)
	{
		HandleFailedRead(progdata, fp);
		return false;
	}

	print_to_main_window("\n");
	
	if (fp != 0)
		fclose(fp);
	
	return true;
}

