#include "base.h"

struct LevelConnection
{
	RoomID from;
	Command direction;
	RoomID to;
};

struct BlockedConnection
{
	RoomID room;
	Command direction;
};

std::vector<LevelConnection> level_connections = { // { from, direction, to }
	{ RoomID::cemetery, Command::down, RoomID::cactus_cave },
	{ RoomID::ruin, Command::down, RoomID::black_cave },
	{ RoomID::black_cave, Command::up, RoomID::ruin },
	{ RoomID::hieroglyphs_cave, Command::down, RoomID::talking_cave },
	{ RoomID::storm_cave, Command::down, RoomID::eyes_cave },
	{ RoomID::stairwell_cave1, Command::down, RoomID::stairwell_cave2 },
	{ RoomID::eyes_cave, Command::up, RoomID::storm_cave },
	{ RoomID::stairwell_cave2, Command::up, RoomID::stairwell_cave1 },
	{ RoomID::stairwell_cave2, Command::down, RoomID::stairwell_cave3 },
	{ RoomID::talking_cave, Command::up, RoomID::hieroglyphs_cave },
	{ RoomID::stairwell_cave3, Command::up, RoomID::stairwell_cave2 }
};

std::vector<BlockedConnection> blocked_connections = { // { room, direction }
	{RoomID::north_swamp, Command::west}, {RoomID::north_swamp, Command::east}, {RoomID::north_swamp, Command::south},
	{RoomID::middle_swamp, Command::west}, {RoomID::middle_swamp, Command::east}, {RoomID::middle_swamp, Command::north}, {RoomID::middle_swamp, Command::south},
	{RoomID::forest5, Command::east},
	{RoomID::cemetery, Command::west},
	{RoomID::forest11, Command::east},
	{RoomID::open_space12, Command::west},
	{RoomID::south_swamp, Command::west}, {RoomID::south_swamp, Command::east}, {RoomID::south_swamp, Command::north},
	{RoomID::ruin, Command::west},
	{RoomID::slime_cave, Command::east},
	{RoomID::black_cave, Command::west},
	{RoomID::drugs_cave, Command::east}, {RoomID::drugs_cave, Command::south},
	{RoomID::horny_cave, Command::west}, {RoomID::horny_cave, Command::east},
	{RoomID::straitjacket_cave, Command::west},
	{RoomID::neglected_cave, Command::east}, {RoomID::neglected_cave, Command::north},
	{RoomID::empty_cave26, Command::west}, {RoomID::empty_cave26, Command::east},
	{RoomID::main_cave, Command::east}, {RoomID::main_cave, Command::west}, {RoomID::main_cave, Command::north},
	{RoomID::hieroglyphs_cave, Command::west},
	{RoomID::fluorescent_cave, Command::south},
	{RoomID::small_cave, Command::north},
	{RoomID::ice_cave, Command::east},
	{RoomID::cactus_cave, Command::west}, {RoomID::cactus_cave, Command::south},
	{RoomID::storm_cave, Command::north},
	{RoomID::mist_cave, Command::west}, {RoomID::mist_cave, Command::north}, {RoomID::mist_cave, Command::east},
	{RoomID::tentacle_cave, Command::north},
	{RoomID::garbage_cave, Command::east},
	{RoomID::echo_cave, Command::west}, {RoomID::echo_cave, Command::east},
	{RoomID::secret_cave, Command::west}, {RoomID::secret_cave, Command::east},
	{RoomID::food_cave, Command::west}, {RoomID::food_cave, Command::east},
	{RoomID::gnu_cave, Command::west},
	{RoomID::empty_cave45, Command::north},
	{RoomID::eyes_cave, Command::east},
	{RoomID::rock_cave, Command::west},
	{RoomID::emptiness, Command::south},
	{RoomID::safe_cave, Command::east}, {RoomID::safe_cave, Command::south},
	{RoomID::narrow_cleft, Command::north}, {RoomID::narrow_cleft, Command::east}, {RoomID::narrow_cleft, Command::south},
	{RoomID::oil_cave, Command::west},
	{RoomID::empty_cave55, Command::east},
	{RoomID::stairwell_cave2, Command::west},
	{RoomID::spider_cave, Command::north},
	{RoomID::talking_cave, Command::east},
	{RoomID::lava_pit, Command::west},
	{RoomID::scooby_cave, Command::east},
	{RoomID::radioactive_cave, Command::west}, {RoomID::radioactive_cave, Command::south},
	{RoomID::death_cave, Command::south},
	{RoomID::r_cave, Command::north}, {RoomID::r_cave, Command::south},
	{RoomID::e_cave, Command::south},
	{RoomID::damnation_cave, Command::north}, {RoomID::damnation_cave, Command::east},
	{RoomID::vacuum_cave, Command::west}, {RoomID::vacuum_cave, Command::north}, {RoomID::vacuum_cave, Command::east},
	{RoomID::red_cave, Command::west}, {RoomID::red_cave, Command::north}, {RoomID::red_cave, Command::east},
	{RoomID::neon_cave, Command::west},
	{RoomID::blood_cave, Command::south},
	{RoomID::bat_cave, Command::north},
	{RoomID::teleport_cave, Command::west}, {RoomID::teleport_cave, Command::north}
};
