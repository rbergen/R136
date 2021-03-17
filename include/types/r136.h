#pragma once

// types/r136.h

#include <vector>
#include <map>
#include <string>

using std::string;
using std::wstring;

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
	const wstring name;
	const wstring description;
	bool is_forest;
	RoomConnections connections;

	Room(const wstring name, const wstring description, bool is_forest) : name(name), description(description), is_forest(is_forest) {}
	Room(const wstring name, const wstring description) : Room(name, description, false) {}
	Room(const wstring name, bool is_forest) : Room(name, L"", is_forest) {}
	Room(const wstring name) : Room(name, L"" , false) {}
};

struct CoreData;

struct Animate : Entity<AnimateID>
{
	RoomID room;
	char strikes_left;
	AnimateStatus status;

	virtual bool progress_status(CoreData& core) { return true; }
	void load(Animate& source);

	Animate() : Animate(RoomID::undefined, 0) {}
	Animate(RoomID room, char strikes_to_kill) : room(room), strikes_left(strikes_to_kill), status(AnimateStatus::initial) {}
	Animate(RoomID room) : Animate(room, 0) {}
};

struct Item : Entity<ItemID>
{
	const string name;
	const wstring description;
	RoomID room;
	AnimateID usable_on;

	Item(const string name, const wstring description, RoomID room, AnimateID usable_on) : name(name), description(description), room(room), usable_on(usable_on) {}
	Item(const string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::undefined) {}
	Item(const string name, const wstring description, AnimateID usable_on) : Item(name, description, RoomID::undefined, usable_on) {}
	Item(const string name, const wstring description) : Item(name, description, RoomID::undefined, AnimateID::undefined) {}

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
	static_assert(std::is_base_of<Entity<TKey>, TValue>::value, "TValue must inherit from Entity<TKey>");

	std::map<TKey, TValue*> map;
	bool delete_values;

public:
	EntityMap(bool delete_values = false);
	~EntityMap();

	void add_or_set(TValue& value);
	void add_or_set(TValue* value);
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
	Inventory inventory;
	std::vector<RoomID> paperroute;
	Status status{};

	CoreData();
};
