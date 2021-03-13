#ifndef R136_INCLUDE

#define R136_INCLUDE

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <type_traits>
#include <map>


#if !defined(CURSES_WIDE) && !defined(PDC_WIDE)
	#error (PD)Curses must be built with wide-character support
#endif

// Figure out which (n)curses header to include
#ifdef HAVE_NCURSES_NCURSES_H
	#include <ncursesw/ncurses.h>
#elif HAVE_NCURSES_CURSES_H 
	#include <ncursesw/curses.h>
#elif HAVE_NCURSES_H
	#include <ncurses.h>
#else
	#include <curses.h>
#endif

// This following section is a little bit of nastiness due to major OS platforms not agreeing in 2021 on one approach to idle-wait for a number of milliseconds
#ifdef _WIN32
#include <windows.h>
void sleep_ms(int n) 
{
	Sleep(n);
}
#else
#include <unistd.h>
#include <map>
void sleep_ms(int n)
{
	usleep(n * 1000);
}

#endif

template <typename E>
constexpr auto to_value(E e) noexcept
{
	return static_cast<std::underlying_type_t<E>>(e);
}

/*
	Defines
*/
enum class Color : short 
{
	bold,
	banner,
	error,
	inverse,
	inverse_red,
	normal,
	COUNT
};

enum class Cursor : char
{
	normal,
	block
};

constexpr int undefined	= -1;

enum class Command : char
{
	east = 0,
	west,
	north,
	south,
	up,
	down,
	use,
	combine,
	pickup,
	lay_down,
	inspect,
	wait,
	finish,
	status,
	help,
	COUNT
};

enum class AnimateID : char
{
	hellhound = 0,
	red_troll,
	plant,
	gnu,
	dragon,
	swelling,
	door,
	voices,
	barbecue,
	tree,
	green_crystal,
	computer,
	dragon_head,
	lava,
	vacuum,
	hatch,
	north_swamp,
	middle_swamp,
	south_swamp,
	mist,
	teleporter,
	COUNT,
	undefined
};

enum class ItemID : char
{
	hound_meat,
	thermal_suit,
	green_crystal,
	sword,
	bone,
	diskette,
	hashis,
	red_crystal,
	nightcap,
	bomb,
	flashlight,
	bandage,
	flamethrower,
	cookbook,
	tnt,
	gas_capsule,
	poisined_meat,
	ignition,
	batteries,
	gasmask,
	hatch,
	booklet,
	blue_crystal,
	cookie,
	gas_grenade,
	COUNT
};

constexpr AnimateID connectToItem(ItemID item) { return static_cast<AnimateID>(-(to_value(item) + 2)); }

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

constexpr char paper_route_length = 6;
constexpr char max_life_points = 20;
constexpr char max_owned_items = 10;

enum class AnimateStatus : char {
	dead = 3,
	hatch_opening = 1,
	door_open = 1,
	initial_burn = 0,
	hashis_on_fire = 1,
	meat_on_fire = 2,
	ingredients_burning = 3,
	cookie_is_baking = 4,
	computer_is_reading = 2,
	cookie_is_thrown = 3,
	sleeping_lightly = 4,
	nightcap_on_head = 5,
	bomb_dropped = 1,
	tree_on_fire = 1,
	poisonous_meat_fed = 2,
	booklet_thrown = 4,
	swelling_gassed = 2
};


#define item_owned				-2

/*
	Structures
*/

struct LevelConnection 
{
	char from;
	Command direction;
	char to;
};

struct BlockedConnection
{
	char room;
	Command direction;
};

struct Room
{
	const wchar_t* name;
	const wchar_t* descript;
	char connect[6];
};

struct Animate
{
	char room;
	char strike;
	char status;
};

struct Item
{
	const char* name;
	const wchar_t* descript;
	char room;
	AnimateID useableon;
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
	std::map<AnimateID, Animate> animates;
	std::map<ItemID, Item> items;
	char owneditems[max_owned_items];
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

int get_random_number(int max);
void setup_windows();
int print_to_main_window(const char* fmt, ...);
void initialize_console();
void release_console();
void print_fullscreen_block(int y, int x, Color colors, const wchar_t** block, int rowcount);
void print_fullscreen_block_section(int y, int x, Color colors, const wchar_t** block, int uppery, int leftx, int lowery, int rightx);
void print_fullscreen(int y, int x, Color colors, const wchar_t* text);
void clear_fullscreen(Color colors);
void get_fullscreen_size(int& y, int& x);
void update_fullscreen();
void clear_window();
void wait_for_key();
void wait_for_fullscreen_key();
int write_to_main_window(const wchar_t *text);
void write_centered(WINDOW* win, const char* str);
void clear_line(WINDOW *win);
void get_command_string(char* input, int maxlength);
void print_command_string(const char* fmt, ...);
int advanced_getchar(const char *allowed);
int advanced_scanf(WINDOW *win, int chckinp, int length, const char *allowed, const char *frmstr, ...);
int get_string_input (WINDOW *win, const char *allowed, char *input, int inpx, int inpy, int caps, int esc, int curm);

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

void show_splashscreen(void);
void show_start_message(void);
void force_exit(void);

void show_room_status(Progdata &progdata);
void show_open_directions(char *connect);
void show_items(Progdata &progdata);
bool progress_animate_status(Progdata &progdata);
void progress_hellhound_status(Progdata &progdata);
void progress_red_troll_status(Progdata &progdata);
void progress_plant_status(Progdata &progdata);
void progress_gnu_status(Progdata &progdata);
void progress_dragon_status(Progdata &progdata);
void progress_swelling_status(Progdata &progdata);
void progress_door_status(Progdata &progdata);
void progress_voices_status(Progdata &progdata);
void progress_barbecue_status(Progdata &progdata);
void progress_tree_status(Progdata &progdata);
void progress_green_crystal_status(Progdata &progdata);
void progress_computer_status(Progdata &progdata);
void progress_dragon_head_status(Progdata &progdata);
bool progress_lava_status(Progdata &progdata);
void progress_hatch_status(Progdata &progdata);

extern const char* LOADSAVEDATAPATH;
extern WINDOW* banner_window;
extern WINDOW* main_window;
extern WINDOW* input_window;

#endif // !R136_INCLUDE

