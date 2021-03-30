#pragma once

// types/items.h

#include "base.h"

struct Diskette : Item
{
	Diskette(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::computer, AnimateStatus::computer_is_reading) {}
	Diskette(string name, const wstring description) : Diskette(name, description, RoomID::undefined) {}
};

struct Cookie : Item
{
	Cookie(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::dragon, AnimateStatus::cookie_is_thrown) {}
	Cookie(string name, const wstring description) : Cookie(name, description, RoomID::undefined) {}
};

struct Bomb: Item
{
	Bomb(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::lava, AnimateStatus::bomb_dropped) {}
	Bomb(string name, const wstring description) : Bomb(name, description, RoomID::undefined) {}
};

struct PoisonedMeat : Item
{
	PoisonedMeat(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::gnu, AnimateStatus::poisonous_meat_fed) {}
	PoisonedMeat(string name, const wstring description) : PoisonedMeat(name, description, RoomID::undefined) {}
};

struct Booklet : Item
{
	Booklet(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::red_troll, AnimateStatus::booklet_thrown) {}
	Booklet(string name, const wstring description) : Booklet(name, description, RoomID::undefined) {}
};

struct GasGrenade : Item
{
	GasGrenade(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::swelling, AnimateStatus::swelling_gassed) {}
	GasGrenade(string name, const wstring description) : GasGrenade(name, description, RoomID::undefined) {}
};

struct Flamethrower : Item
{
	Flamethrower(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::tree, AnimateStatus::tree_on_fire) {}
	Flamethrower(string name, const wstring description) : Flamethrower(name, description, RoomID::undefined) {}
};

struct Nightcap : Item
{
	Nightcap(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::dragon, AnimateStatus::nightcap_on_head) {}
	Nightcap(string name, const wstring description) : Nightcap(name, description, RoomID::undefined) {}

protected:
	bool use_with_target_present(CoreData& core) override;
};

struct Bone : Item 
{
	Bone(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::computer, AnimateStatus::computer_is_reading) {}
	Bone(string name, const wstring description) : Bone(name, description, RoomID::undefined) {}

protected:
	bool use_with_target_present(CoreData& core) override;
};

struct TNT : Item
{
	TNT(string name, const wstring description, RoomID room) : Item(name, description, room) {}
	TNT(string name, const wstring description) : TNT(name, description, RoomID::undefined) {}

	bool use(CoreData& core) override;
};

struct Bandage : Item
{
	Bandage(string name, const wstring description, RoomID room) : Item(name, description, room) {}
	Bandage(string name, const wstring description) : Bandage(name, description, RoomID::undefined) {}

	bool use(CoreData& core) override;
};

struct Sword : Item
{
	Sword(string name, const wstring description, RoomID room) : Item(name, description, room) {}
	Sword(string name, const wstring description) : Sword(name, description, RoomID::undefined) {}

	bool use(CoreData& core) override;
};

struct CombinableItem : Item
{
	CombinableItem(string name, const wstring description, RoomID room, ItemID combines_with);
	CombinableItem(string name, const wstring description, ItemID combines_with) : CombinableItem(name, description, RoomID::undefined, combines_with) {}

	bool combines_with(ItemID item);
};

struct Flashlight : CombinableItem
{
	bool is_on;
	bool has_bunny_batteries;
	int battery_level;

	Flashlight(string name, const wstring description, RoomID room);
	Flashlight(string name, const wstring description) : Flashlight(name, description, RoomID::undefined) {}

	bool use(CoreData& core) override;
	void decrease_battery_level(CoreData& core);
};

struct Gasmask : Item
{
	Gasmask(string name, const wstring description, RoomID room) : Item(name, description, room) {}
	Gasmask(string name, const wstring description) : Gasmask(name, description, RoomID::undefined) {}

protected:
	bool use(CoreData& core) override;
};

struct ThermalSuit : Item
{
	ThermalSuit(string name, const wstring description, RoomID room) : Item(name, description, room) {}
	ThermalSuit(string name, const wstring description) : ThermalSuit(name, description, RoomID::undefined) {}

protected:
	bool use(CoreData& core) override;
};

struct Ingredient : Item
{
	Ingredient(string name, const wstring description, RoomID room, AnimateStatus sets_target_to_status) 
		: Item(name, description, room, AnimateID::barbecue, sets_target_to_status) {}

protected:
	bool use_with_target_present(CoreData& core) override;

};

struct Hashis : Ingredient
{
	Hashis(string name, const wstring description, RoomID room) : Ingredient(name, description, room, AnimateStatus::hashis_on_fire) {}
	Hashis(string name, const wstring description) : Hashis(name, description, RoomID::undefined) {}
};

struct HoundMeat : Ingredient
{
	HoundMeat(string name, const wstring description, RoomID room) : Ingredient(name, description, room, AnimateStatus::meat_on_fire) {}
	HoundMeat(string name, const wstring description) : HoundMeat(name, description, RoomID::undefined) {}
};

struct Crystal : Item
{
	Crystal(string name, const wstring description, RoomID room) : Item(name, description, room, AnimateID::dragon_head) {}
	Crystal(string name, const wstring description) : Crystal(name, description, RoomID::undefined) {}

protected:
	bool use_with_target_present(CoreData& core) override;
};

