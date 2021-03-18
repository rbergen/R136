#pragma once

#include "types/base.h"

struct Diskette : Item
{
	Diskette(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::computer, AnimateStatus::computer_is_reading) {}
};

struct Cookie : Item
{
	Cookie(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::dragon, AnimateStatus::cookie_is_thrown) {}
};

struct Bomb: Item
{
	Bomb(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::lava, AnimateStatus::bomb_dropped) {}
};

struct PoisonedMeat : Item
{
	PoisonedMeat(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::gnu, AnimateStatus::poisonous_meat_fed) {}
};

struct Booklet : Item
{
	Booklet(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::red_troll, AnimateStatus::booklet_thrown) {}
};

struct GasGrenade : Item
{
	GasGrenade(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::swelling, AnimateStatus::swelling_gassed) {}
};

struct Flamethrower : Item
{
	Flamethrower(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::tree, AnimateStatus::tree_on_fire) {}
};

struct Nightcap : Item
{
	Nightcap(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::dragon, AnimateStatus::nightcap_on_head) {}

protected:
	void use_if_target_present(CoreData& core) override;
};

struct Bone : Item 
{
	Bone(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::computer, AnimateStatus::computer_is_reading) {}

protected:
	void use_if_target_present(CoreData& core) override;
};

struct TNT : Item
{
	TNT(string name, const wstring description, RoomID room) : Item(name, description, room) {}

	void use(CoreData& core) override;
};

struct Bandage : Item
{
	Bandage(string name, const wstring description, RoomID room) : Item(name, description, room) {}

	void use(CoreData& core) override;
};

struct Flashlight : Item
{
	bool is_on;
	bool has_batteries;
	int battery_level;

	Flashlight(string name, const wstring description, RoomID room);

	void use(CoreData& core) override;
};

struct Gasmask : Item
{
	Gasmask(string name, const wstring description, RoomID room) : Item(name, description, room) {}

protected:
	void use(CoreData& core) override;
};

struct HeatSuit : Item
{
	HeatSuit(string name, const wstring description, RoomID room) : Item(name, description, room) {}

protected:
	void use(CoreData& core) override;
};

struct Ingredient : Item
{
	Ingredient(string name, const wstring description, RoomID room, AnimateStatus sets_target_to_status) : Item(name, description, room, AnimateID::barbecue, sets_target_to_status) {}

protected:
	void use_if_target_present(CoreData& core) override;

};

struct Hashis : Ingredient
{
	Hashis(string name, const wstring description, RoomID room) : Ingredient(name, description, room, AnimateStatus::hashis_on_fire) {}
};

struct HoundMeat : Ingredient
{
	HoundMeat(string name, const wstring description, RoomID room) : Ingredient(name, description, room, AnimateStatus::meat_on_fire) {}
};

struct Crystal : Item
{
	Crystal(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::dragon_head) {}

protected:
	void use_if_target_present(CoreData& core) override;
};

