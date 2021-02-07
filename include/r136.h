#ifndef R136_INCLUDE

#define R136_INCLUDE

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

// This following section is a little bit of nastiness due to major OS platforms not agreeing in 2021 on one approach to idle-wait for a number of milliseconds
#ifdef _WIN32
#include <windows.h>
#define mssleep(n)	Sleep((n))	
#else
#include <unistd.h>
#define mssleep(n)	usleep((n) * 1000)
#endif

/*
	Defines
*/
#define COLORS_BOLD			1
#define COLORS_BANNER		2
#define COLORS_ERROR		3
#define COLORS_INVERSE		4
#define COLORS_INVERSERED	5
#define COLORS_NORMAL		6

#define CURSOR_NORMAL		0
#define CURSOR_FULL			1

#define UNDEFINED	-1

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
#define LIVING_GROENKRISTAL	10
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

#define connectToItem(n)	(-((n) + 2))

#define ROOM_COUNT				80
#define ROOM_BOS0				0
#define ROOM_BOS1				1
#define ROOM_BOS2				2
#define ROOM_NOORDMOERAS		3
#define ROOM_BOS4				4
#define ROOM_BOS5				5
#define ROOM_BEGRAAFPLAATS		6
#define ROOM_BOS7				7
#define ROOM_MIDDENMOERAS		8
#define ROOM_OPENPLEK9			9
#define ROOM_BOS10				10
#define ROOM_BOS11				11
#define ROOM_OPENPLEK12			12
#define ROOM_MOERASPAD			13
#define ROOM_OPENPLEK14			14
#define ROOM_BOS15				15
#define ROOM_BOS16				16
#define ROOM_OPENPLEK17			17
#define ROOM_ZUIDMOERAS			18
#define ROOM_RUINE				19
#define ROOM_SLIJMGROT			20
#define ROOM_ZWARTEGROT			21
#define ROOM_DRUGSGROT			22
#define ROOM_GEILEGROT			23
#define ROOM_DWANGBUISGROT		24
#define ROOM_VERWAARLOOSDEGROT	25
#define ROOM_LEGEGROT26			26
#define ROOM_HOOFDGROT			27
#define ROOM_HIEROGLIEFENGROT	28
#define ROOM_STANKGROT			29
#define ROOM_TROOSTELOZEGROT	30
#define ROOM_TLGROT				31
#define ROOM_KLEINEGROT			32
#define ROOM_IJSGROT			33
#define ROOM_KAKTUSGROT			34
#define ROOM_STALAGMIETENGROT	35
#define ROOM_STORMGROT			36
#define ROOM_MISTGROT			37
#define ROOM_WENTELTRAPGROT1	38
#define ROOM_TENTAKELGROT		39
#define ROOM_VUILNISGROT		40
#define ROOM_ECHOGROT			41
#define ROOM_GEHEIMEGROT		42
#define ROOM_VOEDSELGROT		43
#define ROOM_GNOEGROT			44
#define ROOM_LEGEGROT45			45
#define ROOM_OGENGROT			46
#define ROOM_ROTSGROT			47
#define ROOM_LEEGTE				48
#define ROOM_ZANDBANK			49
#define ROOM_MARTELGROT			50
#define ROOM_LEGEGROT51			51 
#define ROOM_VEILIGEGROT		52
#define ROOM_NAUWEROTSSPLEET	53
#define ROOM_OLIEGROT			54 
#define ROOM_LEGEGROT55			55 
#define ROOM_WENTELTRAPGROT2	56 
#define ROOM_SPINNENGROT		57 
#define ROOM_PRATENDEGROT		58
#define ROOM_LAVAPUT			59 
#define ROOM_SKOEBIEGROT		60
#define ROOM_RADIOACTIEVEGROT 	61 
#define ROOM_IGROT				62
#define ROOM_PGROT				63
#define ROOM_AGROT				64
#define ROOM_DODENGROT			65
#define ROOM_RGROT				66
#define ROOM_EGROT				67
#define ROOM_WENTELTRAPGROT3	68
#define ROOM_HOOFDLETTERPGROT	69
#define ROOM_VERDOEMENISGROT	70
#define ROOM_VACUUMGROT			71
#define ROOM_RODEGROT			72
#define ROOM_NEONGROT			73
#define ROOM_BLOEDGROT			74
#define ROOM_VLEERMUISGROT		75
#define ROOM_SLANGENGROT		76
#define ROOM_KWABBENGROT		77
#define ROOM_GLIBBERGROT		78
#define ROOM_TELEPORTGROT		79

#define PAPERROUTE_LENGTH		6
#define MAX_LIFEPOINTS			20
#define MAX_OWNEDITEMS			10

#define STATUS_LIVING_DEAD				3
#define STATUS_PAPIER_OPENING			1
#define STATUS_DEUR_OPEN				1
#define STATUS_BARBECUE_INITIALBURN		0
#define STATUS_BARBECUE_HASJONFIRE		1
#define STATUS_BARBECUE_VLEESONFIRE		2
#define STATUS_BARBECUE_INGREDIENTBURN	3
#define STATUS_BARBECUE_KOEKJEBAKING	4
#define STATUS_COMPUTER_READING			2
#define STATUS_DRAAK_KOEKJETHROWN		3
#define STATUS_DRAAK_LIGHTSLEEPING		4
#define STATUS_DRAAK_SLAAPMUTSONHEAD	5
#define STATUS_LAVA_BOMDROPPED			1
#define STATUS_BOOM_SETONFIRE			1
#define STATUS_GNOE_GIFTIGVLEESFED		2
#define STATUS_RODETROL_BOEKJETHROWN	4
#define STATUS_GEZWEL_GASSED			2
#define STATUS_ITEM_OWNED				-2

/*
	Structures
*/

struct Room
{
	const char* name;
	const char* descript;
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
	const char* name;
	const char* descript;
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
	Room* rooms;
	Living* living;
	Item* items;
	char owneditems[MAX_OWNEDITEMS];
	char* paperroute;
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
	Functions
*/

int random(int max);

void setupwindows();
int printmw(const char* fmt, ...);
void initconsole();
void printfsblockat(int y, int x, int colors, const wchar_t** block, int rowcount);
void printfsblocksectionat(int y, int x, int colors, const wchar_t** block, int uppery, int leftx, int lowery, int rightx);
void printfsat(int y, int x, int colors, const wchar_t* text);
void clrfs(int colors);
void getfssize(int& y, int& x);
void updatefs();
void clrscr();
void waitforkey();
void waitforfskey();
void printcentered(WINDOW* win, const char* str);
void clearline(WINDOW *win);
void getcmdstr(char* input, int maxlength);
void printcmdstr(const char* fmt, ...);
int agetchar(const char *allowed);
int ascanf(WINDOW *win, int chckinp, int length, const char *allowed, const char *frmstr, ...);
int strinp (WINDOW *win, const char *allowed, char *input, int inpx, int inpy, int caps, int esc, int curm);

void RunIntro();

void SaveStatus(Progdata &progdata);
bool LoadStatus(Progdata &progdata);

bool Initialize(Progdata &progdata);
bool SetRoomConnections(Room *rooms);

bool DoAction(Progdata &progdata);
void DoGebruik(Progdata &progdata, Parsedata &parsedata);
void UseItemToStatus(Progdata &progdata, int ownedindex, int beast, int status);
void DoCombineer(Progdata &progdata, Parsedata &parsedata);
void DoLeg(Progdata &progdata, Parsedata &parsedata);
void DoPak(Progdata &progdata, Parsedata &parsedata);
void DoBekijk(Progdata &progdata, Parsedata &parsedata);
void DoAfwachten(void);
void DoStatus(Progdata &progdata);
void DoHelp(void);
void ParseInput(Progdata &progdata, char *inpstr, Parsedata &parsedata);
void ParseCombineItemsParameters(Progdata& progdata, Parsedata& parsedata, const char* currentMatch);
bool CheckFoundObject(Parsedata& parsedata, char itemNum, const char* itemname, const char* undefinedItemFormatString);
bool ParseSingleOwnedItemCommandParam(Progdata& progdata, Parsedata& parsedata, const char* command, const char* parseString);
int FindOwnedItemNum(Progdata &progdata, const char *itemname);
bool IsRoomLit(Status& status);
int FindLayingItemNum(Progdata &progdata, const char *itemname);

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
void GroenKristalStatus(Progdata &progdata);
void ComputerStatus(Progdata &progdata);
void DrakeKopStatus(Progdata &progdata);
bool LavaStatus(Progdata &progdata);
void PapierStatus(Progdata &progdata);

extern const char* LOADSAVEDATAPATH;
extern WINDOW* BANNERWINDOW;
extern WINDOW* MAINWINDOW;
extern WINDOW* INPUTWINDOW;

#endif // !R136_INCLUDE

