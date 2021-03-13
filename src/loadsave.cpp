#include "r136.h"

const char* LOADSAVEDATAPATH = "r136data.rip";

void HandleFailedWrite(FILE *fp)
{
	PrintToMainWindow("Fout bij wegschrijven status.\n\nStatus niet opgeslagen!\n");

	fclose(fp);
	remove(LOADSAVEDATAPATH);
}

void SaveStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	PrintToMainWindow("\n\nWil je je huidige status opslaan? ");

	if (tolower(AdvancedGetChar("jJnN")) != 'j')
	{
		PrintToMainWindow("\n");

		return;
	}

	while (!(fp = fopen(LOADSAVEDATAPATH, "wb")))
	{
		PrintToMainWindow("\n\nKon het save-bestand niet openen voor schrijven. Nogmaals proberen? ");

		if (tolower(AdvancedGetChar("jJnN")) != 'j')
		{
			PrintToMainWindow("\n\nStatus niet opgeslagen!\n");

			remove(LOADSAVEDATAPATH);

			return;
		}
	}

	PrintToMainWindow("\n");

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
		if (fp != 0 && fwrite(&progdata.living[i], sizeof(Living), 1, fp) < 1)
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
	PrintToMainWindow("Fout bij lezen status.\n\nJe start een nieuw spel.\n\n");

	fclose(fp);
	remove(LOADSAVEDATAPATH);

	WaitForKey();

	Initialize(progdata);
}

bool LoadStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	if (!(fp = fopen(LOADSAVEDATAPATH, "rb")))
	{
		WriteCentered(main_window, "Druk op een toets om te beginnen");

		WaitForKey();
		return false;
	}

	WriteCentered(main_window, "Toets 1 voor een nieuw spel, 2 voor een gesaved spel: ");

	if (tolower(AdvancedGetChar("12")) != '2')
	{
		if (fp != 0) 
			fclose(fp);

		remove(LOADSAVEDATAPATH);

		return false;
	}

	PrintToMainWindow("\n");

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
		if (fp != 0 && fread(&progdata.living[i], sizeof(Living), 1, fp) < 1)
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

	PrintToMainWindow("\n");
	
	if (fp != 0)
		fclose(fp);
	
	return true;
}

