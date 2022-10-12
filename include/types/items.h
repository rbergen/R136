#pragma once

// types/items.h

#include "base.h"

struct Diskette : Item
{
	Diskette(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::computer, AnimateStatus::computer_is_reading) {}
	Diskette(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Diskette(names, descriptions, RoomID::undefined) {}
};

struct Cookie : Item
{
	Cookie(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::dragon, AnimateStatus::cookie_is_thrown) {}
	Cookie(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Cookie(names, descriptions, RoomID::undefined) {}
};

struct Bomb: Item
{
	Bomb(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::lava, AnimateStatus::bomb_dropped) {}
	Bomb(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Bomb(names, descriptions, RoomID::undefined) {}
};

struct PoisonedMeat : Item
{
	PoisonedMeat(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::gnu, AnimateStatus::poisonous_meat_fed) {}
	PoisonedMeat(const std::vector <const string> names, const std::vector <const wstring> descriptions) : PoisonedMeat(names, descriptions, RoomID::undefined) {}
};

struct Booklet : Item
{
	Booklet(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::red_troll, AnimateStatus::booklet_thrown) {}
	Booklet(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Booklet(names, descriptions, RoomID::undefined) {}
};

struct GasGrenade : Item
{
	GasGrenade(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::swelling, AnimateStatus::swelling_gassed) {}
	GasGrenade(const std::vector <const string> names, const std::vector <const wstring> descriptions) : GasGrenade(names, descriptions, RoomID::undefined) {}
};

struct Flamethrower : Item
{
	Flamethrower(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::tree, AnimateStatus::tree_on_fire) {}
	Flamethrower(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Flamethrower(names, descriptions, RoomID::undefined) {}
};

struct Nightcap : Item
{
	Nightcap(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::dragon, AnimateStatus::nightcap_on_head) {}
	Nightcap(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Nightcap(names, descriptions, RoomID::undefined) {}

protected:
	bool use_with_target_present(CoreData& core) override;
};

struct Bone : Item 
{
	Bone(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::computer, AnimateStatus::computer_is_reading) {}
	Bone(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Bone(names, descriptions, RoomID::undefined) {}

protected:
	bool use_with_target_present(CoreData& core) override;
};

struct TNT : Item
{
	TNT(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room) {}
	TNT(const std::vector <const string> names, const std::vector <const wstring> descriptions) : TNT(names, descriptions, RoomID::undefined) {}

	bool use(CoreData& core) override;
};

struct Bandage : Item
{
	Bandage(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room) {}
	Bandage(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Bandage(names, descriptions, RoomID::undefined) {}

	bool use(CoreData& core) override;
};

struct Sword : Item
{
	Sword(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room) {}
	Sword(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Sword(names, descriptions, RoomID::undefined) {}

	bool use(CoreData& core) override;
};

struct CombinableItem : Item
{
	CombinableItem(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room, ItemID combines_with);
	CombinableItem(const std::vector <const string> names, const std::vector <const wstring> descriptions, ItemID combines_with) 
		: CombinableItem(names, descriptions, RoomID::undefined, combines_with) {}

	bool combines_with(ItemID item);
};

struct Flashlight : CombinableItem
{
	bool is_on;
	bool has_bunny_batteries;
	int battery_level;

	Flashlight(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room);
	Flashlight(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Flashlight(names, descriptions, RoomID::undefined) {}

	bool use(CoreData& core) override;
	void decrease_battery_level(CoreData& core);
};

struct Gasmask : Item
{
	Gasmask(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room) {}
	Gasmask(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Gasmask(names, descriptions, RoomID::undefined) {}

protected:
	bool use(CoreData& core) override;
};

struct ThermalSuit : Item
{
	ThermalSuit(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room) {}
	ThermalSuit(const std::vector <const string> names, const std::vector <const wstring> descriptions) : ThermalSuit(names, descriptions, RoomID::undefined) {}

protected:
	bool use(CoreData& core) override;
};

struct Ingredient : Item
{
	Ingredient(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room, AnimateStatus sets_target_to_status)
		: Item(names, descriptions, room, AnimateID::barbecue, sets_target_to_status) {}

protected:
	bool use_with_target_present(CoreData& core) override;

};

struct Hashis : Ingredient
{
	Hashis(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Ingredient(names, descriptions, room, AnimateStatus::hashis_on_fire) {}
	Hashis(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Hashis(names, descriptions, RoomID::undefined) {}
};

struct HoundMeat : Ingredient
{
	HoundMeat(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Ingredient(names, descriptions, room, AnimateStatus::meat_on_fire) {}
	HoundMeat(const std::vector <const string> names, const std::vector <const wstring> descriptions) : HoundMeat(names, descriptions, RoomID::undefined) {}
};

struct Crystal : Item
{
	Crystal(const std::vector <const string> names, const std::vector <const wstring> descriptions, RoomID room) : Item(names, descriptions, room, AnimateID::dragon_head) {}
	Crystal(const std::vector <const string> names, const std::vector <const wstring> descriptions) : Crystal(names, descriptions, RoomID::undefined) {}

protected:
	bool use_with_target_present(CoreData& core) override;
};

