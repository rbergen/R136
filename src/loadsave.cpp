#include "r136.h"

const char* LOADSAVEDATAPATH = "r136data.rip";

void HandleFailedWrite(FILE *fp)
{
	printmw("Fout bij wegschrijven status.\n\nStatus niet opgeslagen!\n");

	fclose(fp);
	remove(LOADSAVEDATAPATH);
}

void SaveStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	printmw("\n\nWil je je huidige status opslaan? ");

	if (tolower(agetchar("jJnN")) != 'j')
	{
		printmw("\n");

		return;
	}

	while (!(fp = fopen(LOADSAVEDATAPATH, "wb")))
	{
		printmw("\n\nKon het save-bestand niet openen voor schrijven. Nogmaals proberen? ");

		if (tolower(agetchar("jJnN")) != 'j')
		{
			printmw("\n\nStatus niet opgeslagen!\n");

			remove(LOADSAVEDATAPATH);

			return;
		}
	}

	printmw("\n");

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
	printmw("Fout bij lezen status.\n\nJe start een nieuw spel.\n\n");

	fclose(fp);
	remove(LOADSAVEDATAPATH);

	waitforkey();

	Initialize(progdata);
}

bool LoadStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	if (!(fp = fopen(LOADSAVEDATAPATH, "rb")))
	{
		printcentered(MAINWINDOW, "Druk op een toets om te beginnen");

		waitforkey();
		return false;
	}

	printcentered(MAINWINDOW, "Toets 1 voor een nieuw spel, 2 voor een gesaved spel: ");

	if (tolower(agetchar("12")) != '2')
	{
		if (fp != 0) 
			fclose(fp);

		remove(LOADSAVEDATAPATH);

		return false;
	}

	printmw("\n");

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

	printmw("\n");
	
	if (fp != 0)
		fclose(fp);
	
	return true;
}

