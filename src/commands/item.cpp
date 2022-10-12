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
			console.main().print(select("Dat levert niets bruikbaars op.", "That doesn't yield anything useful."));
			return;
		}

		switch (item1)
		{
		case ItemID::flashlight:
		case ItemID::batteries:

			console.main().print(select(
				"Je schroeft de zaklamp open en schudt totdat de oude batterijen er uit komen vallen. "
				"Daarna steek je de \"trommelbatterijen\" erin en schroeft de lamp weer dicht. Nadat je een paar keer op de zaklantaarn hebt geslagen zie je dat hij het doet."
			,
				"You screw the cap off the flashlight and shake until the old batteries fall out. "
				"Then, you stick in the \"bunny batteries\" and screw the cap back on. After you've hit the flashlight a few times, you see that it works."
			));

			core.flashlight().has_bunny_batteries = true;
			core.inventory.remove(core.items[ItemID::batteries]);

			break;

		case ItemID::gas_capsule:
		case ItemID::ignition:

			console.main().print(select(
				"Je plaatst de ontsteker op het mosterdgaspatroon. Na enig friemelen is het resultaat een werkende mosterdgasgranaat."
			,
				"You put the ignition on the mustard gas cartridge. After some fiddling, the result is a functioning mustard gas grenade."
			));

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
			console.main().print(select(
				"Je bent inmiddels zo aan je zaklamp gehecht geraakt dat je hem niet meer kunt missen."
			,
				"You've become so attached to your flashlight that you can't part from it anymore."
			));

			return;
		}

		if (item_id == ItemID::batteries)
		{
			console.main().print(select(
				"Je bent inmiddels zo aan je batterijen gehecht geraakt dat je ze niet meer kunt missen."
			,
				"You've become so attached to your batteries that you can't part from them anymore."
			));

			return;
		}

		auto& item = core.items[item_id];
		console.main().print(select("Je legt {0} neer.\n", "You put {0} down.\n"), select(item.names));


		core.inventory.remove(item);
		item.room = core.status.current_room;
	}

	void pickup(CoreData& core, ItemID item_id)
	{
		auto& item = core.items[item_id];

		if (core.inventory.is_full())
		{
			console.main().print(
				select(
					"Je zakken zitten tjokvol, en je krijgt {0} er niet in."
				,
					"Your pockets are filled to the brim and you can't fit {0} in them."
				), 
				select(item.names)
			);
			return;
		}

		console.main().print(
			select(
				"Je pakt {0} op en steekt deze in een van je zakken."
			,
				"You pick up {0} and put it in one of your pockets."
			),
			select(item.names)
		);

		core.inventory.add(item);
	}

	void inspect(CoreData& core, ItemID item_id)
	{
		core.items[item_id].inspect(core);
	}
}