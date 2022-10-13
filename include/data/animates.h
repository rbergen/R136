#include "base.h"
#include "types/animates.h"

std::unique_ptr<Animate> animates[]{ // { room, strike }
	std::make_unique<HellHound>(RoomID::forest2, 4),
	std::make_unique<RedTroll>(RoomID::horny_cave),
	std::make_unique<Plant>(RoomID::neglected_cave, 6),
	std::make_unique<Gnu>(RoomID::gnu_cave),
	std::make_unique<Dragon>(RoomID::torture_cave),
	std::make_unique<Swelling>(RoomID::bat_cave),
	std::make_unique<Door>(RoomID::empty_cave45),
	std::make_unique<Voices>(RoomID::talking_cave),
	std::make_unique<Barbecue>(RoomID::open_space17),
	std::make_unique<Tree>(RoomID::forest10),
	std::make_unique<GreenCrystal>(RoomID::forest4),
	std::make_unique<Computer>(RoomID::echo_cave),
	std::make_unique<DragonHead>(RoomID::small_cave),
	std::make_unique<Lava>(RoomID::lava_pit),
	std::make_unique<Vacuum>(RoomID::vacuum_cave),
	std::make_unique<Hatch>(RoomID::r_cave),
	std::make_unique<Swamp>(RoomID::north_swamp),
	std::make_unique<Swamp>(RoomID::middle_swamp),
	std::make_unique<Swamp>(RoomID::south_swamp),
	std::make_unique<Mist>(RoomID::mist_cave),
	std::make_unique<Teleporter>(RoomID::teleport_cave)
};
