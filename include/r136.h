#ifndef R136_INCLUDE

#define R136_INCLUDE

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <type_traits>
#include <map>
#include <vector>


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

// This following section is a little bit of nastiness due to major OS platforms not agreeing in 2021, on one approach to idle-wait for a number of milliseconds
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
	usleep(n * 1000,);
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
	COUNT,
	undefined = -1
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
	undefined = -1
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
	paper,
	booklet,
	blue_crystal,
	cookie,
	gas_grenade,
	COUNT,
	undefined = -1,
	ambiguous = -2
};

template<typename L>
constexpr L combines_with(L value) { return -(value + 2); }

constexpr AnimateID combines_with(ItemID item) { return static_cast<AnimateID>(combines_with(to_value(item))); }
constexpr ItemID combines_with(AnimateID animate) { return static_cast<ItemID>(combines_with(to_value(animate))); }

enum class RoomID : char {
	forest0 = 0,
	forest1,
	forest2,
	north_swamp,
	forest4,
	forest5,
	cemetery,
	forest7,
	middle_swamp,
	open_space9,
	forest10,
	forest11,
	open_space12,
	swamp_path,
	open_space14,
	forest15,
	forest16,
	open_space17,
	south_swamp,
	ruin,
	slime_cave,
	black_cave,
	drugs_cave,
	horny_cave,
	straitjacket_cave,
	neglected_cave,
	empty_cave26,
	main_cave,
	hieroglyphs_cave,
	stench_cave,
	gloomy_cave,
	fluorescent_cave,
	small_cave,
	ice_cave,
	cactus_cave,
	stalagmite_cave,
	storm_cave,
	mist_cave,
	stairwell_cave1,
	tentacle_cave,
	garbage_cave,
	echo_cave,
	secret_cave,
	food_cave,
	gnu_cave,
	empty_cave45,
	eyes_cave,
	rock_cave,
	emptiness,
	sandbank,
	torture_cave,
	empty_cave51,
	safe_cave,
	narrow_cleft,
	oil_cave,
	empty_cave55,
	stairwell_cave2,
	spider_cave,
	talking_cave,
	lava_pit,
	scooby_cave,
	radioactive_cave,
	i_cave,
	p_cave,
	a_cave,
	death_cave,
	r_cave,
	e_cave,
	stairwell_cave3,
	capital_p_cave,
	damnation_cave,
	vacuum_cave,
	red_cave,
	neon_cave,
	blood_cave,
	bat_cave,
	snake_cave,
	lobe_cave,
	slippery_cave,
	teleport_cave,
	COUNT,
	undefined = -1,
	owned = -2
};

constexpr char max_life_points = 20;
constexpr char max_lamp_points = 60;
constexpr char max_owned_items = 10;

enum class AnimateStatus : char {
	initial = 0,
	initial_burn = 0,

	status_1 = 1,
	hashis_on_fire = 1,
	hatch_opening = 1,
	door_open = 1,
	bomb_dropped = 1,
	tree_on_fire = 1,
	visible = 1,

	status_2 = 2,
	meat_on_fire = 2,
	computer_is_reading = 2,
	poisonous_meat_fed = 2,
	swelling_gassed = 2,

	status_3 = 3,
	dead = 3,
	ingredient_burning = 3,
	cookie_is_thrown = 3,

	status_4 = 4,
	cookie_is_baking = 4,
	sleeping_lightly = 4,
	booklet_thrown = 4,

	status_5 = 5,
	nightcap_on_head = 5,

	status_6 = 6
};

AnimateStatus next_status(AnimateStatus status) 
{
	return static_cast<AnimateStatus>(to_value(status) + 1);
}

AnimateStatus operator++(AnimateStatus& status)
{
	return next_status(status);
}

/*
	Structures
*/

class RoomConnections {
	std::map<Command, RoomID> connections;
	bool is_direction_command(Command command) const;

public:
	size_t count() const;
	RoomID operator[](Command direction) const;
	bool is_open(Command direction) const;
	bool set(Command direction, RoomID room);
	bool erase(Command direction);
	std::map<Command, RoomID>::iterator begin();
	std::map<Command, RoomID>::iterator end();
};

template<typename Tid>
struct Entity
{
	Tid id;
};

struct Room : Entity<RoomID>
{
	const wchar_t* name;
	const wchar_t* description;
	bool is_forest;
	RoomConnections connections;

	Room(const wchar_t* n, const wchar_t* d, bool f) :
		name(n),
		description(d),
		is_forest(f)
	{}

	Room(const wchar_t* n, const wchar_t* d) : Room(n, d, false) {}

	Room(const wchar_t* n, bool f) : Room(n, nullptr, f) {}

	Room(const wchar_t* n) : Room(n, nullptr, false) {}

};

struct Animate : Entity<AnimateID>
{
	RoomID room;
	char strikes_left;
	AnimateStatus status;

	Animate() : Animate(RoomID::undefined, 0) {}

	Animate(RoomID r, char s) :
		room(r),
		strikes_left(s),
		status(AnimateStatus::initial)
	{}

	Animate(RoomID r) : Animate(r, 0) {}
};

struct Item : Entity<ItemID>
{
	const char* name;
	const wchar_t* description;
	RoomID room;
	AnimateID usable_on;

	Item(const char* n, const wchar_t* d, RoomID r, AnimateID u) :
		name(n),
		description(d),
		room(r),
		usable_on(u)
	{}

	Item(const char* n, const wchar_t* d, RoomID r) : Item(n, d, r, AnimateID::undefined) {}

	Item(const char* n, const wchar_t* d, AnimateID u) : Item(n, d, RoomID::undefined, u) {}

	Item(const char* n, const wchar_t* d) : Item(n, d, RoomID::undefined, AnimateID::undefined)	{}

};

struct Status
{
	char paper_route_pos;
	RoomID current_room;
	char life_points;
	bool is_lamp_on;
	char lamp_points;
	bool has_tree_burned;
};

template<class TKey, class TValue>
class EntityMap
{
	std::map<TKey, TValue*> map;

public:
	void add_or_set(TKey key, TValue& value);
	bool contains(TKey key);
	TValue& operator[](TKey key);
};

template<typename TEntity>
class BoundedCollection
{
	std::vector<TEntity> items;
	int max_item_count;

public:
	BoundedCollection(int capacity);
	size_t count() const;
	bool is_full() const;
	bool contains(TEntity item) const;
	bool add(TEntity item);
	bool remove(TEntity item);
	typename std::vector<TEntity>::iterator begin();
	typename std::vector<TEntity>::iterator end();
};

class Inventory : public BoundedCollection<ItemID> 
{
public:
	Inventory(int capacity);
	bool add(Item item);
	bool remove(Item item);
};

struct CoreData
{
	std::map<RoomID, Room> rooms;
	std::map<AnimateID, Animate> animates;
	std::map<ItemID, Item> items;
	Inventory inventory = Inventory(max_owned_items);
	std::vector<RoomID> paperroute;
	Status status;
};

struct ParseData
{
	Command command;
	ItemID item1;
	ItemID item2;
	bool parse_error;
};


/*
	Functions
*/

int get_random_number(int max);
AnimateStatus get_random_status(int lowest, int highest);
AnimateStatus get_random_status(AnimateStatus lowest, AnimateStatus highest);

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
int write_to_main_window(const wchar_t* text);
void write_centered(WINDOW* win, const char* str);
void get_command_string(char* input, int maxlength);
void print_command_string(const char* fmt, ...);
int advanced_getchar(const char* allowed);

void run_intro();

void save_status(CoreData& core);
bool load_status(CoreData& core);

bool initialize(CoreData& core);

bool perform_command(CoreData& core);

void force_exit(void);

void show_room_status(CoreData& core);
bool progress_animate_status(CoreData& core);

extern const char* saved_status_path;
extern WINDOW* banner_window;
extern WINDOW* main_window;
extern WINDOW* input_window;

#endif // !R136_INCLUDE

