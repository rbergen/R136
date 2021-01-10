#ifndef R136_INCLUDE

#define R136_INCLUDE

#include <conio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>

/*
  structures
*/

struct Room
{
	char connect[6];
	const char *name;
	const char *descript;
};

struct Living
{
	char room;
	char strike;
	char status;
};

struct Item
{
	const char *name;
	const char *descript;
	char room;
	char useableon;
};

struct Status
{
	char paperpos;
	char curroom;
	char lifepoints;
	bool lamp;
	char lamppoints;
};

struct Progdata
{
	Room rooms[80];
	Living living[21];
	Item items[25];
	char owneditems[10];
	char paperroute[6];
	Status status;
};

struct Parsedata
{
	char selected;
	char object1;
	char object2;
	bool parseerror;
};

/*
  defines
*/

#define EAST		0
#define WEST		1
#define NORTH		2
#define SOUTH		3
#define UP			4
#define DOWN		5
#define GEBRUIK	6
#define COMBINEER	7
#define PAK			8
#define LEG			9
#define BEKIJK		10
#define AFWACHTEN	11
#define EINDE		12
#define STATUS		13
#define HELP		14

#define HELLEHOND		0
#define RODETROL		1
#define PLANT			2
#define GNOE			3
#define DRAAK			4
#define GEZWEL			5
#define DEUR			6
#define STEMMEN		7
#define BARBECUE		8
#define BOOM			9
#define DIAMANT		10
#define COMPUTER		11
#define DRAKEKOP		12
#define LAVA			13
#define VACUUM			14
#define PAPIER			15
#define NOORDMOERAS	16
#define MIDDENMOERAS	17
#define ZUIDMOERAS	18
#define MISTGROT		19
#define TELEPORT		20

#define HONDVLEES			0
#define HITTEPAK			1
#define GROENKRISTAL		2
#define ZWAARD				3
#define BOT					4
#define DISKETTE			5
#define HASJ				6
#define ROODKRISTAL		7
#define SLAAPMUTS			8
#define BOM					9
#define ZAKLAMP			10
#define VERBAND			11
#define VLAMMENWERPER	12
#define KOOKBOEK			13
#define TNT					14
#define GASPATROON		15
#define GIFTIGVLEES		16
#define ONTSTEKING		17
#define BATTERIJEN		18
#define GASMASKER			19
#define PAPIERITEM		20
#define BOEKJE				21
#define BLAUWKRISTAL		22
#define KOEKJE				23
#define GASGRANAAT		24

int random(int max);

void clrscr();
int wherex();
int wherey();
void gotoxy(int x, int y);
int agetchar(const char *allowed);
int ascanf(int chckinp, int length, const char *allowed, const char *frmstr, ...);
int strinp (const char *allowed, char *input, int inpx, int inpy, int caps, int esc, int curm);

void SaveStatus(Progdata &progdata);
bool LoadStatus(Progdata &progdata);

bool Initialize(Progdata &progdata);
bool SetRooms(Room *rooms);
bool SetLivings(Living *living);
bool SetItems(Item *items);

bool DoAction(Progdata &progdata);
bool DoGebruik(Progdata &progdata, Parsedata &parsedata);
void UseItemToStatus(Progdata &progdata, int item, int ownedindex, int beast, int status);
void DoCombineer(Progdata &progdata, Parsedata &parsedata);
void DoLeg(Progdata &progdata, Parsedata &parsedata);
void DoPak(Progdata &progdata, Parsedata &parsedata);
void DoBekijk(Progdata &progdata, Parsedata &parsedata);
void DoAfwachten(void);
void DoStatus(Progdata &progdata);
void DoHelp(void);
void ParseInput(Progdata &progdata, char *inpstr, Parsedata &parsedata);
int FindOwnedItemNum(Progdata &progdata, char *itemname);
int FindLayingItemNum(Progdata &progdata, char *itemname);

void ShowSplashScreen(void);
void ShowStartMessage(void);
void ForceExit(void);

void RoomStatus(Progdata &progdata);
void ShowDirString(char *connect);
void ShowItems(Progdata &progdata);
bool BeastStatus(Progdata &progdata);
void HellehondStatus(Progdata &progdata);
void RodeTrolStatus(Progdata &progdata);
void PlantStatus(Progdata &progdata);
void GnoeStatus(Progdata &progdata);
void DraakStatus(Progdata &progdata);
void GezwelStatus(Progdata &progdata);
void DeurStatus(Progdata &progdata);
void StemmenStatus(Progdata &progdata);
void BarbecueStatus(Progdata &progdata);
void BoomStatus(Progdata &progdata);
void DiamantStatus(Progdata &progdata);
void ComputerStatus(Progdata &progdata);
void DrakeKopStatus(Progdata &progdata);
bool LavaStatus(Progdata &progdata);
void PapierStatus(Progdata &progdata);

extern const char* LOADSAVEDATAPATH;

#endif // !R136_INCLUDE

