#include "r136.h"
#include "act.h"
#include "parser.h"

InputWindow& input_window()
{
	static InputWindow* window = &console.input();
	return *window;
}

bool perform_command(CoreData& core)
{
	static Parser parser{};

	if (core.status.life_points <= 0)
	{
		console.main().print("Badend in je eigen bloed bezwijk je aan je verwondingen. Terwijl je liggend op\n");
		console.main().print("de grond met moeite naar adem snakt, hoor je in de verte een luid gelach.\n");
		console.main().print("Dan zakken je ogen dicht en stopt je hart met kloppen.\n");
		console.main().print("Op hetzelfde moment ontploft de bom en sterft de aarde met jou.\n\n");
		force_exit();
	}

	if (core.status.lamp_points > 0 && core.status.is_lamp_on)
	{
		switch (--core.status.lamp_points)
		{
		case 10:
			console.main().print("De zaklamp gaat zwakker branden.\n\n");
			break;
		case 0:
			console.main().print("De batterijen van de zaklamp zijn uitgeput. Langzaam dooft hij.\n\n");
			core.status.is_lamp_on = false;
			break;
		}
	}

	ParseData parse_data{};
	
	do
	{
		string input_string;

		do 
		{
			input_string = string(65, ' ');
			console.input().get_string_input(input_string);
			parse_data = parser.parse_input(core, input_string);
		} 
		while (parse_data.parse_error);

		console.main().print_centered("---***---");
		console.main().print("\n\n");

		auto& gnu = core.animates[AnimateID::gnu];
		auto& status = core.status;

		switch(parse_data.command)
		{
		case Command::east:
		case Command::west:
		case Command::north:
		case Command::south:
		case Command::up:
		case Command::down:

			if (!core.rooms[status.current_room].connections.is_open(parse_data.command)) 
			{
				console.main().print("Daar kun je niet heen.\n");
				break;
			}

			if (gnu.room == status.current_room && gnu.status != AnimateStatus::dead)
			{
				switch (get_random_number(5))
				{
				case 0:
					gnu.room = RoomID::gnu_cave;
					break;
				case 1:
					gnu.room = RoomID::rock_cave;
					break;
				case 2:
					gnu.room = RoomID::emptiness;
					break;
				case 3:
					gnu.room = RoomID::sandbank;
					break;
				case 4:
					gnu.room = RoomID::oil_cave;
					break;
				}
			}
				
			status.current_room = core.rooms[status.current_room].connections[parse_data.command];
				
			if (status.paper_route_pos != core.paperroute.size())
			{
				if (status.current_room == core.paperroute[status.paper_route_pos])
					status.paper_route_pos++;
				else
					status.paper_route_pos = 0;

				if (status.paper_route_pos == core.paperroute.size())
					core.animates[AnimateID::hatch].status = AnimateStatus::hatch_opening;
			}

			return true;

		case Command::use:
			use(core, parse_data.item1);
			break;

		case Command::combine:
			combine(core, parse_data.item1, parse_data.item2);
			break;

		case Command::pickup:
			pickup(core, parse_data.item1);
			break;

		case Command::lay_down:
			lay_down(core, parse_data.item1);
			break;

		case Command::inspect:
			inspect(core, parse_data.item1);
			break;

		case Command::wait:
			wait();
			break;

		case Command::finish:
			console.main().print("Weet je zeker dat je de aarde laat vergaan? ");
			if (tolower(console.main().get_char_input("jJnN")) == 'j')
				return false;
			console.main().print("\nMooi zo!\n");
			break;

		case Command::status:
			show_status(core);
			break;

		case Command::help:
			show_help();
			break;
		}

		console.main().print("\n");
	}
	while (parse_data.command == Command::status || parse_data.command == Command::help || parse_data.command == Command::finish);

	return true;
}

void use(CoreData& core, ItemID item_id)
{
	auto& animates = core.animates;
	auto& status = core.status;
	auto current_room = status.current_room;
	auto& item = core.items[item_id];

	switch (item.id)
	{
	case ItemID::sword:
	{
		AnimateID monsterID;

		if (animates[AnimateID::hellhound].room == current_room && animates[AnimateID::hellhound].strikes_left)
			monsterID = AnimateID::hellhound;
		else if (animates[AnimateID::plant].room == current_room && animates[AnimateID::plant].strikes_left)
			monsterID = AnimateID::plant;
		else
		{
			console.main().print("Dat heeft geen zin.\n");
			return;
		}

		auto& monster = animates[monsterID];

		while (true)
		{
			console.main().print("Je haalt uit met je zwaard");

			if (get_random_number(100) > 70)
				console.main().print(", maar het monster ontwijkt.\n");
			else
			{
				console.main().print(" en je raakt het monster hard.\n");
				monster.strikes_left--;
			}

			if (monster.strikes_left == 1)
				console.main().print("\nHet monster is zwaar gewond en je baadt in zijn bloed.\n");

			if (!monster.strikes_left || get_random_number(100) > 30)
				break;

			console.main().print("\nJe kunt nog een slag uitdelen. Wil je dat? ");

			if (tolower(console.main().get_char_input("jJnN")) != 'j')
			{
				console.main().print("\n");
				break;
			}

			console.main().print("\n");
		}
		console.main().print("\n");

		if (!monster.strikes_left)
		{
			monster.status = AnimateStatus::dead;
			progress_animate_status(core);
		}

		console.main().wait_for_key(true);
		break;
	}
	case ItemID::flashlight:

		if (status.is_lamp_on)
		{
			status.is_lamp_on = !status.is_lamp_on;
			console.main().print("Je zet de zaklamp uit.{0}", is_room_lit(core) ? "\n" : " Je ziet niets meer.\n");
			break;
		}

		if (status.lamp_points)
		{
			status.is_lamp_on = !status.is_lamp_on;
			console.main().print("Je zet de zaklamp aan. De straal verlicht de omtrek.\n");
		}
		else
			console.main().print("Zonder nieuwe batterijen doet'ie het niet...\n");

		break;

	case ItemID::bandage:
		// class implemented

		if (status.life_points == max_life_points)
		{
			console.main().print("Je bent nog helemaal heel!\n");
			break;
		}

		console.main().print("Je pakt het verband en de pleisters en plaatst ze over je wonden. Je bijt even\n"
				 "op je lippen van de pijn als het verband je nog bloedende wonden raakt.\n\n"
				 "Je bent weer zo goed als nieuw.\n");

		status.life_points = max_life_points;
		
		core.inventory.remove(item);

		console.main().wait_for_key(true);
		break;

	case ItemID::tnt:
		// class implemented

		console.main().print("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samen-\n"
				 "gaat met een harde knal. Je wordt even verblind door de flits van de ontplof-\n"
				 "fing. Door de klap val je even flauw.\n");

		status.life_points--;

		console.main().wait_for_key(true);
		break;

	case ItemID::thermal_suit:
		// class implemented
		console.main().print("Je hebt het pak al aan.\n");

		break;

	case ItemID::gasmask:
		// class implemented
		console.main().print("Je hebt het gasmasker al op.\n");

		break;

	default:
		auto target_animate = item.usable_on;

		if (target_animate == AnimateID::undefined
			 || animates[target_animate].room != current_room)
		{
			console.main().print("Dat heeft geen zin.\n");
			break;
		}

		switch (item_id)
		{
		case ItemID::bone:
			// class implemented

			animates[AnimateID::door].status = AnimateStatus::door_open;

			break;

		case ItemID::diskette:
			// class implemented

			use_item_to_status(core, item, AnimateID::computer, AnimateStatus::computer_is_reading);

			break;

		case ItemID::hashis:
			// class implemented

			use_item_to_status(core, item, AnimateID::barbecue, animates[AnimateID::barbecue].status == AnimateStatus::initial_burn
				? AnimateStatus::hashis_on_fire : AnimateStatus::cookie_is_baking);

			break;

		case ItemID::hound_meat:
			// class implemented

			use_item_to_status(core, item, AnimateID::barbecue, animates[AnimateID::barbecue].status == AnimateStatus::initial_burn
				? AnimateStatus::meat_on_fire : AnimateStatus::cookie_is_baking);

			break;

		case ItemID::red_crystal:
		case ItemID::green_crystal:
		case ItemID::blue_crystal:
			// class implemented

			use_item_to_status(core, item, AnimateID::dragon_head, next_status(animates[AnimateID::dragon_head].status));

			break;

		case ItemID::cookie:
			// class implemented
			use_item_to_status(core, item, AnimateID::dragon, AnimateStatus::cookie_is_thrown);

			break;

		case ItemID::nightcap:
			// class implemented

			if (animates[AnimateID::dragon].status != AnimateStatus::sleeping_lightly)
			{
				console.main().print("Dat heeft geen zin.\n");
				return;
			}

			use_item_to_status(core, item, AnimateID::dragon, AnimateStatus::nightcap_on_head);

			break;

		case ItemID::bomb:
			// class implemented

			use_item_to_status(core, item, AnimateID::lava, AnimateStatus::bomb_dropped);

			break;

		case ItemID::flamethrower:
			// class implemented

			use_item_to_status(core, item, AnimateID::tree, AnimateStatus::tree_on_fire);

			break;

		case ItemID::poisined_meat:
			// class implemented

			use_item_to_status(core, item, AnimateID::gnu, AnimateStatus::poisonous_meat_fed);

			break;

		case ItemID::booklet:
			// class implemented

			use_item_to_status(core, item, AnimateID::red_troll, AnimateStatus::booklet_thrown);

			break;

		case ItemID::gas_grenade:
			// class implemented

			use_item_to_status(core, item, AnimateID::swelling, AnimateStatus::swelling_gassed);

			break;
		}

		progress_animate_status(core);

		console.main().wait_for_key(true);
		break;
	}
}

void use_item_to_status(CoreData& core, Item& item, AnimateID animate, AnimateStatus status)
{
	core.inventory.remove(item);
	core.animates[animate].status = status;
}

void combine(CoreData& core, ItemID item1, ItemID item2)
{

	if (combines_with(core.items[item1].usable_on) != item2)
	{
		console.main().print("Dat levert niets bruikbaars op.\n");
		return;
	}

	switch(item1)
	{
	case ItemID::flashlight:
	case ItemID::batteries:

		console.main().print("Je schroeft de zaklamp open en schudt totdat de oude batterijen er uit komen\n"
				 "vallen. Daarna steek je de \"trommelbatterijen\" erin en schroeft de lamp weer\n"
				 "dicht. Nadat je een paar keer op de zaklantaarn hebt geslagen zie je dat hij\n"
				 "het doet.\n");

		core.status.lamp_points = undefined;
		core.inventory.remove(core.items[ItemID::batteries]);

		break;

	case ItemID::gas_capsule:
	case ItemID::ignition:

		console.main().print("Je plaatst de ontsteker op het mosterdgaspatroon. Na enig friemelen is het\n"
				 "resultaat een werkende mosterdgasgranaat.\n");

		core.inventory.remove(core.items[ItemID::gas_capsule]);
		core.inventory.remove(core.items[ItemID::ignition]);
		core.inventory.add(core.items[ItemID::gas_grenade]);

		break;
	}
}

void lay_down(CoreData& core, ItemID item_id)
{
	
	if (item_id == ItemID::flashlight)
	{
		console.main().print("Je bent inmiddels zo aan je zaklamp gehecht geraakt dat je hem niet meer kunt\n"
				 "missen.\n");

		return;
	}

	if (item_id == ItemID::batteries)
	{
		console.main().print("Je bent inmiddels zo aan je batterijen gehecht geraakt dat je ze niet meer kunt\n"
				 "missen.\n");

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
		console.main().print("Je zakken zitten tjokvol, en je krijgt {0} er niet in.\n", item.name);
		return;
	}

	console.main().print("Je pakt {0} op en steekt deze in een van je zakken.\n", item.name);

	core.inventory.add(item);
}

void wait(void)
{
	switch(get_random_number(5))
	{
	case 0:
		console.main().print("Je pulkt wat in je neus.\n");
		break;

	case 1:
		console.main().print("Je krabt wat achter je oren.\n");
		break;

	case 2:
		console.main().print("Je gaapt even uitgebreid.\n");
		break;

	case 3:
		console.main().print("Je trekt je broek even op.\n");
		break;

	case 4:
		console.main().print("Je pulkt wat smeer uit je oren.\n");
		break;
	}
}

void show_status(CoreData& core)
{
	auto& status = core.status;

	console.main().print("--- STATUSRAPPORT ---\n\n");
	console.main().print("Je hebt nog {0} levenspunten.\n", std::to_string(status.life_points));

	auto& inventory = core.inventory;
	if (inventory.contains(ItemID::flashlight))
		console.main().print("Je zaklamp staat {0}.\n", status.is_lamp_on ? "aan" : "uit");

	if (inventory.count() == 0)
	{
		console.main().print("Je draagt niets.\n");
		return;
	}

	console.main().print("Je hebt in je bezit:\n");

	for (auto& item : core.inventory)
		console.main().print("    {0}\n", core.items[item].name);
}

void show_help(void)
{
	console.main().print("--- HELP ---\n\n");
	console.main().print("Commando's:\n");
	console.main().print("   oost\n");
	console.main().print("   west\n");
	console.main().print("   noord\n");
	console.main().print("   zuid\n");
	console.main().print("   klim\n");
	console.main().print("   daal\n");
	console.main().print("   gebruik <voorwerp>\n");
	console.main().print("   combineer <voorwerp> en/met <voorwerp>\n");
	console.main().print("   pak <voorwerp>\n");
	console.main().print("   leg <voorwerp>\n");
	console.main().print("   bekijk <voorwerp>\n");
	console.main().print("   afwachten\n");
	console.main().print("   einde\n");
	console.main().print("   status\n");
	console.main().print("   help\n");
}


