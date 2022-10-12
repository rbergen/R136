#pragma once

// types/base.h

#include <vector>
#include <map>
#include <memory>
#include <string>

#define get_y_or_n() (tolower(console.main().get_char_input(select("jJnN", "yYnN"))) == select((int)'j', (int)'y'))

using std::string;
using std::wstring;

// this is obviously a template, but of such a general and fundamental nature that it is included here
template <class E>
constexpr auto to_value(E e) noexcept
{
	return static_cast<std::underlying_type_t<E>>(e);
}

enum class RoomType : char
{
	forest,
	cave,
	outdoor,
	indoor,
	undefined = -1
};

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

	COUNT, undefined = -1, in_posession = -2
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
	language,

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

	status_6 = 6,

	undefined = -1
};

enum class Language : int
{
	Dutch = 0,
	English,

	COUNT, undefined = -1
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
	const std::vector<wstring> names;
	const std::vector<wstring> descriptions;
	RoomType type;
	RoomConnections connections;

protected:
	Room(const std::vector<wstring> names, const std::vector<wstring> descriptions, RoomType type) : names(names), descriptions(descriptions), type(type) {}
	Room(const std::vector<wstring> names, RoomType type) : names(names), descriptions(), type(type) {}
};

struct Forest : public Room
{
	Forest(const std::vector<wstring> names, const std::vector<wstring> descriptions) : Room(names, descriptions, RoomType::forest) {}
	Forest(const std::vector<wstring> names) : Room(names, RoomType::forest) {}
};

struct Outdoor : public Room
{
	Outdoor(const std::vector<wstring> names, const std::vector<wstring> descriptions) : Room(names, descriptions, RoomType::outdoor) {}
	Outdoor(const std::vector<wstring> names) : Room(names, RoomType::outdoor) {}
};

struct Indoor : public Room
{
	Indoor(const std::vector<wstring> names, const std::vector<wstring> descriptions) : Room(names, descriptions, RoomType::indoor) {}
	Indoor(const std::vector<wstring> names) : Room(names, RoomType::indoor) {}
};

struct Cave : public Room
{
	Cave(const std::vector<wstring> names, const std::vector<wstring> descriptions) : Room(names, descriptions, RoomType::cave) {}
	Cave(const std::vector<wstring> names) : Room(names, RoomType::cave) {}
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
	const std::vector<string> names;
	const std::vector<wstring> descriptions;
	RoomID room;
	AnimateID usable_on;

	Item(const std::vector <string> names, const std::vector <wstring> descriptions, RoomID room, AnimateID usable_on, AnimateStatus sets_target_to_status = AnimateStatus::undefined);
	Item(const std::vector <string> names, const std::vector <wstring> descriptions, RoomID room)
		: Item(names, descriptions, room, AnimateID::undefined) {}

	Item(const std::vector <string> names, const std::vector <wstring> descriptions, AnimateID usable_on, AnimateStatus sets_target_to_status = AnimateStatus::undefined)
		: Item(names, descriptions, RoomID::undefined, usable_on, sets_target_to_status) {}

	Item(const std::vector <string> names, const std::vector <wstring> descriptions)
		: Item(names, descriptions, RoomID::undefined, AnimateID::undefined) {}

	void inspect(CoreData& core);
	virtual bool use(CoreData& core);
	bool is_in_posession();

protected:
	AnimateStatus sets_target_to_status;
	bool is_target_present(CoreData& core);
	AnimateStatus& target_status(CoreData& core);
	void report_pointless_use();

	virtual bool use_with_target_present(CoreData& core);
	virtual bool use_to_status(CoreData& core, AnimateStatus to_status = AnimateStatus::undefined);
};

struct Status
{
	char paper_route_pos;
	RoomID current_room;
	char life_points;
	bool has_tree_burned;
};

template<class TKey, class TValue>
class EntityMap
{
	static_assert(std::is_base_of<Entity<TKey>, TValue>::value, "TValue must inherit from Entity<TKey>");

	std::map<TKey, std::unique_ptr<TValue>> map;

public:
	void add_or_set(std::unique_ptr<TValue> value);
	bool contains(TKey key);
	void clear();
	TValue& operator[](TKey key);
	typename std::map<TKey, std::unique_ptr<TValue>>::iterator begin();
	typename std::map<TKey, std::unique_ptr<TValue>>::iterator end();
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

#include "types/items.h"

struct CoreData
{
	EntityMap<RoomID, Room> rooms;
	EntityMap<AnimateID, Animate> animates;
	EntityMap<ItemID, Item> items;
	Inventory inventory;
	Flashlight& flashlight();
	std::vector<RoomID> paperroute;
	Status status{};
	Language language;

	CoreData();

	void set_flashlight(Flashlight* flashlight_ptr);

private:
	Flashlight* flashlight_ptr;
};