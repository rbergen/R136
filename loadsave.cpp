#include "include.h"

const char* LOADSAVEDATAPATH = "r136data.rip";

void SaveStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	_cprintf("\r\n\r\nWil je je huidige status opslaan? ");
	if (tolower(agetchar("jJnN")) != 'j')
	{
		_cprintf("\r\n");
		return;
	}

	while (fopen_s(&fp, LOADSAVEDATAPATH, "wb"))
	{
		_cprintf("\r\n\r\nKon het save-bestand niet openen voor schrijven. Nogmaals proberen? ");
		if (tolower(agetchar("jJnN")) != 'j')
		{
			_cprintf("\r\n\r\nStatus niet opgeslagen!\r\n");
			remove(LOADSAVEDATAPATH);
			return;
		}
	}

	_cprintf("\r\n");

	for (i = 0; i < 25; i++)
	{
		if (fp != 0 && fwrite(&progdata.items[i].room, sizeof(char), 1, fp) < 1)
		{
			_cprintf("Fout bij wegschrijven status.\r\n\r\nStatus niet opgeslagen!\r\n");
			fclose(fp);
			remove(LOADSAVEDATAPATH);
			return;
		}
	}

	for (i = 0; i < 80; i++)
	{
		if (fp != 0 && fwrite(progdata.rooms[i].connect, sizeof(char) * 6, 1, fp) < 1)
		{
			_cprintf("Fout bij wegschrijven status.\r\n\r\nStatus niet opgeslagen!\r\n");
			fclose(fp);
			remove(LOADSAVEDATAPATH);
			return;
		}
	}
	for (i = 0; i < 21; i++)
	{
		if (fp != 0 && fwrite(&progdata.living[i], sizeof(Living), 1, fp) < 1)
		{
			_cprintf("Fout bij wegschrijven status.\r\n\r\nStatus niet opgeslagen!\r\n");
			fclose(fp);
			remove(LOADSAVEDATAPATH);
			return;
		}
	}
	if (fp != 0 && fwrite(progdata.owneditems, sizeof(char), 10, fp) < 10)
	{
		_cprintf("Fout bij wegschrijven status.\r\n\r\nStatus niet opgeslagen!\r\n");
		fclose(fp);
		remove(LOADSAVEDATAPATH);
		return;
	}
	if (fp != 0 && fwrite(&progdata.status, sizeof(Status), 1, fp) < 1)
	{
		_cprintf("Fout bij wegschrijven status.\r\n\r\nStatus niet opgeslagen!\r\n");
		fclose(fp);
		remove(LOADSAVEDATAPATH);
		return;
	}
	if (fp != 0)
	{
		fclose(fp);
	}
}

bool LoadStatus(Progdata &progdata)
{
	FILE *fp;
	int i;

	if (fopen_s(&fp, LOADSAVEDATAPATH, "rb"))
	{
		printf("                      Druk op een toets om te beginnen");
		(void)_getch();
		return false;
	}

	_cprintf("            Toets 1 voor een nieuw spel, 2 voor een gesaved spel: ");
	if (tolower(agetchar("12")) != '2')
	{
		if (fp != 0) 
			fclose(fp);
		remove(LOADSAVEDATAPATH);
		return false;
	}
	_cprintf("\r\n");

	for (i = 0; i < 25; i++)
	{
		if (fp != 0 && fread(&progdata.items[i].room, sizeof(char), 1, fp) < 1)
		{
			_cprintf("Fout bij lezen status.\r\n\r\nJe start een nieuw spel.\r\n\r\n");
			fclose(fp);
			remove(LOADSAVEDATAPATH);
			(void)_getch();
			Initialize(progdata);
			return false;
		}
	}
	for (i = 0; i < 80; i++)
	{
		if (fp != 0 && fread(progdata.rooms[i].connect, sizeof(char) * 6, 1, fp) < 1)
		{
			_cprintf("Fout bij lezen status.\r\n\r\nJe start een nieuw spel.\r\n\r\n");
			fclose(fp);
			remove(LOADSAVEDATAPATH);
			(void)_getch();
			Initialize(progdata);
			return false;
		}
	}
	for (i = 0; i < 21; i++)
	{
		if (fp != 0 && fread(&progdata.living[i], sizeof(Living), 1, fp) < 1)
		{
			_cprintf("Fout bij lezen status.\r\n\r\nJe start een nieuw spel.\r\n\r\n");
			fclose(fp);
			remove(LOADSAVEDATAPATH);
			(void)_getch();
			Initialize(progdata);
			return false;
		}
	}
	if (fp != 0 && fread(progdata.owneditems, sizeof(char), 10, fp) < 10)
	{
		_cprintf("Fout bij lezen status.\r\n\r\nJe start een nieuw spel.\r\n\r\n");
		fclose(fp);
		remove(LOADSAVEDATAPATH);
		(void)_getch();
		Initialize(progdata);
		return false;
	}
	if (fp != 0 && fread(&progdata.status, sizeof(Status), 1, fp) < 1)
	{
		_cprintf("Fout bij lezen status.\r\n\r\nJe start een nieuw spel.\r\n\r\n");
		fclose(fp);
		remove(LOADSAVEDATAPATH);
		(void)_getch();
		Initialize(progdata);
		return false;
	}
	_cprintf("\r\n");
	
	if (fp != 0)
		fclose(fp);
	
	return true;
}

