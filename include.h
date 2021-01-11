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
	const char *name;
	const char *descript;
	char connect[6];
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
	Room *rooms;
	Living *living;
	Item items[25];
	char owneditems[10];
	char *paperroute;
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
#define CURSOR_NORMAL		0
#define CURSOR_FULL			1
#define CURSOR_UNDEFINED	-1

#define DO_EAST			0
#define DO_WEST			1
#define DO_NORTH		2
#define DO_SOUTH		3
#define DO_UP			4
#define DO_DOWN			5
#define DO_GEBRUIK		6
#define DO_COMBINEER	7
#define DO_PAK			8
#define DO_LEG			9
#define DO_BEKIJK		10
#define DO_AFWACHTEN	11
#define DO_EINDE		12
#define DO_STATUS		13
#define DO_HELP			14

#define LIVING_COUNT		21
#define LIVING_HELLEHOND	0
#define LIVING_RODETROL		1
#define LIVING_PLANT		2
#define LIVING_GNOE			3
#define LIVING_DRAAK		4
#define LIVING_GEZWEL		5
#define LIVING_DEUR			6
#define LIVING_STEMMEN		7
#define LIVING_BARBECUE		8
#define LIVING_BOOM			9
#define LIVING_DIAMANT		10
#define LIVING_COMPUTER		11
#define LIVING_DRAKEKOP		12
#define LIVING_LAVA			13
#define LIVING_VACUUM		14
#define LIVING_PAPIER		15
#define LIVING_NOORDMOERAS	16
#define LIVING_MIDDENMOERAS	17
#define LIVING_ZUIDMOERAS	18
#define LIVING_MISTGROT		19
#define LIVING_TELEPORT		20

#define ITEM_COUNT			25
#define ITEM_HONDVLEES		0
#define ITEM_HITTEPAK		1
#define ITEM_GROENKRISTAL	2
#define ITEM_ZWAARD			3
#define ITEM_BOT			4
#define ITEM_DISKETTE		5
#define ITEM_HASJ			6
#define ITEM_ROODKRISTAL	7
#define ITEM_SLAAPMUTS		8
#define ITEM_BOM			9
#define ITEM_ZAKLAMP		10
#define ITEM_VERBAND		11
#define ITEM_VLAMMENWERPER	12
#define ITEM_KOOKBOEK		13
#define ITEM_TNT			14
#define ITEM_GASPATROON		15
#define ITEM_GIFTIGVLEES	16
#define ITEM_ONTSTEKING		17
#define ITEM_BATTERIJEN		18
#define ITEM_GASMASKER		19
#define ITEM_PAPIERITEM		20
#define ITEM_BOEKJE			21
#define ITEM_BLAUWKRISTAL	22
#define ITEM_KOEKJE			23
#define ITEM_GASGRANAAT		24

#define ROOM_COUNT			80

int random(int max);

void clrscr();
int wherex();
int wherey();
void gotoxy(int x, int y);
void setcursor(int mode);
int agetchar(const char *allowed);
int ascanf(int chckinp, int length, const char *allowed, const char *frmstr, ...);
int strinp (const char *allowed, char *input, int inpx, int inpy, int caps, int esc, int curm);

void SaveStatus(Progdata &progdata);
bool LoadStatus(Progdata &progdata);

bool Initialize(Progdata &progdata);
bool SetRoomConnections(Room *rooms);
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
bool LivingStatus(Progdata &progdata);
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

