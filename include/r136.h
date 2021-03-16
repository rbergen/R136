#pragma once

#if !defined(CURSES_WIDE) && !defined(PDC_WIDE)
#error (PD)Curses must be built with wide-character support
#endif

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <type_traits>
#include <map>
#include <vector>
#include <stdexcept>

// Figure out which (name)curses header to include
#ifdef HAVE_NCURSES_NCURSES_H
	#include <ncursesw/ncurses.h>
#elif HAVE_NCURSES_CURSES_H 
	#include <ncursesw/curses.h>
#elif HAVE_NCURSES_H
	#include <ncurses.h>
#else
	#include <curses.h>
#endif

extern const char* saved_status_path;

enum class RoomID : char 
{
	forest0 = 0, forest1, forest2, north_swamp, forest4,
	forest5, cemetery, forest7, middle_swamp, open_space9,
	forest10, forest11, open_space12, swamp_path, open_space14,
	forest15, forest16, open_space17, south_swamp, ruin,

	slime_cave, black_cave, drugs_cave, horny_cave, straitjacket_cave,
	neglected_cave, empty_cave26, main_cave, hieroglyphs_cave, stench_cave,
	gloomy_cave, fluorescent_cave, small_cave, ice_cave, cactus_cave,
	stalagmite_cave, storm_cave, mist_cave, stairwell_cave1, tentacle_cave,
	
	garbage_cave, echo_cave, secret_cave, food_cave, gnu_cave,
	empty_cave45, eyes_cave, rock_cave, emptiness, sandbank,
	torture_cave, empty_cave51, safe_cave, narrow_cleft, oil_cave,
	empty_cave55, stairwell_cave2, spider_cave, talking_cave, lava_pit,

	scooby_cave, radioactive_cave, i_cave, p_cave, a_cave, 
	death_cave, r_cave, e_cave, stairwell_cave3, capital_p_cave,
	damnation_cave, vacuum_cave, red_cave, neon_cave, blood_cave,
	bat_cave, snake_cave, lobe_cave, slippery_cave, teleport_cave,
	
	COUNT, undefined = -1, owned = -2
};

enum class Color : short
{
	bold,
	banner,
	error,
	inverse,
	inverse_red,
	normal,

	COUNT, undefined = -1
};

enum class Cursor : char
{
	normal,
	block
};

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
	
	COUNT, undefined = -1
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
	north_swamp, middle_swamp, south_swamp,
	mist,
	teleporter,

	COUNT, undefined = -1
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

	COUNT, undefined = -1, ambiguous = -2
};

enum class AnimateStatus : char
{
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

constexpr int undefined = -1;
constexpr char max_life_points = 20;
constexpr char max_lamp_points = 60;
constexpr char max_owned_items = 10;

/*
	Structures
*/

class RoomConnections 
{
	std::map<Command, RoomID> connections;
	bool is_direction_command(Command command) const;

public:
	size_t count() const;
	RoomID operator[](Command direction) const;
	bool is_open(Command direction) const;
	bool set(Command direction, RoomID room);
	bool erase(Command direction);
	void clear();
	std::map<Command, RoomID>::iterator begin();
	std::map<Command, RoomID>::iterator end();
};

template<class Tid>
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

	Room(const wchar_t* name, const wchar_t* description, bool is_forest) : name(name), description(description), is_forest(is_forest) {}
	Room(const wchar_t* name, const wchar_t* description) : Room(name, description, false) {}
	Room(const wchar_t* name, bool is_forest) : Room(name, nullptr, is_forest) {}
	Room(const wchar_t* name) : Room(name, nullptr, false) {}
};

struct Animate : Entity<AnimateID>
{
	RoomID room;
	char strikes_left;
	AnimateStatus status;

	Animate() : Animate(RoomID::undefined, 0) {} 
	Animate(RoomID room, char strikes_to_kill) : room(room), strikes_left(strikes_to_kill), status(AnimateStatus::initial) {}
	Animate(RoomID room) : Animate(room, 0) {}
};

struct Item : Entity<ItemID>
{
	const char* name;
	const wchar_t* description;
	RoomID room;
	AnimateID usable_on;

	Item(const char* name, const wchar_t* description, RoomID room, AnimateID usable_on) : name(name), description(description), room(room), usable_on(usable_on) {}
	Item(const char* name, const wchar_t* description, RoomID room) : Item(name, description, room, AnimateID::undefined) {}
	Item(const char* name, const wchar_t* description, AnimateID usable_on) : Item(name, description, RoomID::undefined, usable_on) {}
	Item(const char* name, const wchar_t* description) : Item(name, description, RoomID::undefined, AnimateID::undefined)	{}

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
	void clear();
	TValue& operator[](TKey key);
	typename std::map<TKey, TValue*>::iterator begin();
	typename std::map<TKey, TValue*>::iterator end();
};

template<class TEntity>
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
	bool add(Item& item);
	bool add(ItemID item);
	bool remove(Item& item);
};

struct CoreData
{
	EntityMap<RoomID, Room> rooms;
	EntityMap<AnimateID, Animate> animates;
	EntityMap<ItemID, Item> items;
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

class Window
{
	friend class Console;

	int scanf(int check_input, int length, const char* allowed_characters, const char* format_string, ...);

protected:
	WINDOW* wnd;
	Color standard_color;
	bool notify_console_of_resize;

	Window(WINDOW* wnd);
	Window(WINDOW* wnd, bool enable_keypad);
	Window(WINDOW* wnd, Color standard_color);
	Window(WINDOW* wnd, bool enable_keypad, Color standard_color);

	void resize(int height, int width);
	void move(int y, int x, int height, int width);
	void set_color(Color color);
	void unset_color(Color color);
	void get_position(int& y, int& x);
	int get_x();
	int get_y();
	void set_position(int y, int x);
	void clear_line();
	void set_scrollable(bool enable);
	int get_string_input(const char* allowed_characters, char* input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals);

public:
	void clear();
	void clear(Color color);
	void set_attribute(chtype attr);
	void unset_attribute(chtype attr);
	void refresh();
	void get_size(int& y, int& x);
	void print_centered(const char* str);
	int print(const char* format, ...);
	void print(char c);
	int write(const wchar_t* text);
	void write_block(int y, int x, Color color, const wchar_t** block, int rowcount);
	void write_block(int y, int x, Color color, const wchar_t** block, int topy, int leftx, int bottomy, int rightx);
	void write(int y, int x, Color color, const wchar_t* text);
	void wait_for_key();
	int get_char_input(const char* allowed);
};

class InputWindow : protected Window
{
	friend class Console;

	InputWindow(WINDOW* wnd);

public:
	void get_string_input(char* input, int max_length);
	void print_error(const char* format, ...);
};

class Console
{
	Window* fullscreen_window;
	Window* main_window;
	Window* banner_window;
	InputWindow* input_window;
	bool is_released;

	Window& banner();

	void setup_windows();

public:
	Console();
	~Console();

	Window& fullscreen();
	Window& main();
	InputWindow& input();

	void process_resize();
	void initialize();
	void release();
};

int get_random_number(int max);
AnimateStatus get_random_status(AnimateStatus lowest, AnimateStatus highest);
void run_intro();
bool save_status(CoreData& core);
bool load_status(CoreData& core);
void initialize(CoreData& core);
bool perform_command(CoreData& core);
void force_exit(void);
void show_room_status(CoreData& core);
bool progress_animate_status(CoreData& core);
void sleep_ms(int name);
AnimateStatus next_status(AnimateStatus status);
AnimateStatus operator++(AnimateStatus& status, int);
AnimateStatus& operator++(AnimateStatus& status);

extern Console console;

#include "r136_templates.h"
#include "r136_inlines.h"
#include "console_inlines.h"