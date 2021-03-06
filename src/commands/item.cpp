#include "base.h"
#include "console.h"
#include "items.h"
#include "actions.h"

namespace commands
{
	void use(CoreData& core, ItemID item_id)
	{
		if (core.items[item_id].use(core))
		{
			actions::progress_animates(core);

			console.main().wait_for_key(true);
		}
	}

	void combine(CoreData& core, ItemID item1, ItemID item2)
	{
		auto combinable_item = dynamic_cast<CombinableItem*>(&core.items[item1]);

		if (combinable_item == nullptr || !combinable_item->combines_with(item2))
		{
			console.main().print("Dat levert niets bruikbaars op.");
			return;
		}

		switch (item1)
		{
		case ItemID::flashlight:
		case ItemID::batteries:

			console.main().print("Je schroeft de zaklamp open en schudt totdat de oude batterijen er uit komen vallen. "
				"Daarna steek je de \"trommelbatterijen\" erin en schroeft de lamp weer dicht. Nadat je een paar keer op de zaklantaarn hebt geslagen zie je dat hij het doet.");

			core.flashlight().has_bunny_batteries = true;
			core.inventory.remove(core.items[ItemID::batteries]);

			break;

		case ItemID::gas_capsule:
		case ItemID::ignition:

			console.main().print("Je plaatst de ontsteker op het mosterdgaspatroon. Na enig friemelen is het resultaat een werkende mosterdgasgranaat.");

			core.inventory.remove(core.items[ItemID::gas_capsule]);
			core.inventory.remove(core.items[ItemID::ignition]);
			core.inventory.add(core.items[ItemID::gas_grenade]);

			break;

		default:
			break;
		}
	}

	void lay_down(CoreData& core, ItemID item_id)
	{

		if (item_id == ItemID::flashlight)
		{
			console.main().print("Je bent inmiddels zo aan je zaklamp gehecht geraakt dat je hem niet meer kunt missen.");

			return;
		}

		if (item_id == ItemID::batteries)
		{
			console.main().print("Je bent inmiddels zo aan je batterijen gehecht geraakt dat je ze niet meer kunt missen.");

			return;
		}

		auto& item = core.items[item_id];
		console.main().print("Je legt {0} neer.\n", item.name);


		core.inventory.remove(item);
		item.room = core.status.current_room;
	}

	void pickup(CoreData& core, ItemID item_id)
	{
		auto& item = core.items[item_id];

		if (core.inventory.is_full())
		{
			console.main().print("Je zakken zitten tjokvol, en je krijgt {0} er niet in.", item.name);
			return;
		}

		console.main().print("Je pakt {0} op en steekt deze in een van je zakken.", item.name);

		core.inventory.add(item);
	}

	void inspect(CoreData& core, ItemID item_id)
	{
		core.items[item_id].inspect(core);
	}
}