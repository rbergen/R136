#include "act.h"

const char* dontOwnItemFormatString = "je hebt geen \"%s\"";

const char* commands[to_value(Command::COUNT)] = 
	{"oost", "west", "noord", "zuid", "klim", "daal", "gebruik", "combineer", "pak", "leg", "bekijk", "afwachten", 
	"einde", "status", "help"};

InputWindow& input_window()
{
	static InputWindow* window = &console.input();
	return *window;
}

bool perform_command(CoreData& core)
{
	ParseData parse_data{};

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
		switch(--core.status.lamp_points)
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

	do
	{
		char input_string[65];

		do 
		{
			console.input().get_string_input(input_string, 64);
			parse_input(core, input_string, parse_data);
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
			console.main().print("Dat heeft geen zin.\n\n");
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

		console.main().wait_for_key();
		break;
	}
	case ItemID::flashlight:

		if (status.is_lamp_on)
		{
			status.is_lamp_on = !status.is_lamp_on;
			console.main().print("Je zet de zaklamp uit.%s", is_room_lit(status) ? "\n" : " Je ziet niets meer.\n");
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

		console.main().wait_for_key();
		break;

	case ItemID::tnt:

		console.main().print("Je pakt een staafje en gooit het op de grond. Er volgt een explosie die samen-\n"
				 "gaat met een harde knal. Je wordt even verblind door de flits van de ontplof-\n"
				 "fing. Door de klap val je even flauw.\n");

		status.life_points--;

		console.main().wait_for_key();
		break;

	case ItemID::thermal_suit:

		console.main().print("Je hebt het pak al aan.\n");

		break;

	case ItemID::gasmask:

		console.main().print("Je hebt het gasmasker al op.\n");

		break;

	default:
		auto target_animate = item.usable_on;

		if (target_animate == AnimateID::undefined
			 || animates[target_animate].room != current_room)
		{
			console.main().print("Dat heeft geen zin.\n\n");
			break;
		}

		switch (item_id)
		{
		case ItemID::bone:

			animates[AnimateID::door].status = AnimateStatus::door_open;

			break;

		case ItemID::diskette:

			use_item_to_status(core, item, AnimateID::computer, AnimateStatus::computer_is_reading);

			break;

		case ItemID::hashis:

			use_item_to_status(core, item, AnimateID::barbecue, animates[AnimateID::barbecue].status == AnimateStatus::initial_burn
				? AnimateStatus::hashis_on_fire : AnimateStatus::cookie_is_baking);

			break;

		case ItemID::hound_meat:

			use_item_to_status(core, item, AnimateID::barbecue, animates[AnimateID::barbecue].status == AnimateStatus::initial_burn
				? AnimateStatus::meat_on_fire : AnimateStatus::cookie_is_baking);

			break;

		case ItemID::red_crystal:
		case ItemID::green_crystal:
		case ItemID::blue_crystal:

			use_item_to_status(core, item, AnimateID::dragon_head, next_status(animates[AnimateID::dragon_head].status));

			break;

		case ItemID::cookie:

			use_item_to_status(core, item, AnimateID::dragon, AnimateStatus::cookie_is_thrown);

			break;

		case ItemID::nightcap:

			if (animates[AnimateID::dragon].status != AnimateStatus::sleeping_lightly)
			{
				console.main().print("Dat heeft geen zin.\n\n");
				return;
			}

			use_item_to_status(core, item, AnimateID::dragon, AnimateStatus::nightcap_on_head);

			break;

		case ItemID::bomb:

			use_item_to_status(core, item, AnimateID::lava, AnimateStatus::bomb_dropped);

			break;

		case ItemID::flamethrower:

			use_item_to_status(core, item, AnimateID::tree, AnimateStatus::tree_on_fire);

			break;

		case ItemID::poisined_meat:

			use_item_to_status(core, item, AnimateID::gnu, AnimateStatus::poisonous_meat_fed);

			break;

		case ItemID::booklet:

			use_item_to_status(core, item, AnimateID::red_troll, AnimateStatus::booklet_thrown);

			break;

		case ItemID::gas_grenade:

			use_item_to_status(core, item, AnimateID::swelling, AnimateStatus::swelling_gassed);

			break;
		}

		progress_animate_status(core);

		console.main().wait_for_key();;
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
	console.main().print("Je legt %s neer.\n", item.name);


	core.inventory.remove(item);
	item.room = core.status.current_room;
}

void pickup(CoreData& core, ItemID item_id)
{
	auto& item = core.items[item_id];

	if (core.inventory.is_full())
	{
		console.main().print("Je zakken zitten tjokvol, en je krijgt %s er niet in.\n", item.name);
		return;
	}

	console.main().print("Je pakt %s op en steekt deze in een van je zakken.\n", item.name);

	core.inventory.add(item);
}

void inspect(CoreData& core, ItemID item_id)
{
	if (!is_room_lit(core.status))
	{
		console.main().print("Het is veel te donker om wat dan ook te bekijken.\n");
		return;
	}

	console.main().write(core.items[item_id].description);
	console.main().print("\n");
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
	console.main().print("Je hebt nog %d levenspunten.\n", status.life_points);

	auto& inventory = core.inventory;
	if (inventory.contains(ItemID::flashlight))
		console.main().print("Je zaklamp staat %s.\n", status.is_lamp_on ? "aan" : "uit");

	if (inventory.count() == 0)
	{
		console.main().print("Je draagt niets.\n");
		return;
	}

	console.main().print("Je hebt in je bezit:\n");

	for (auto& item : core.inventory)
		console.main().print("    %s\n", core.items[item].name);
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

void parse_input(CoreData& core, char* inpstr, ParseData& parse_data)
{
	char* eoword;
	char* curp;
	char workstr[65];
	int i;

	parse_data.parse_error = false;

	strncpy(workstr, inpstr, 64);
	workstr[64] = 0;

	// trim input at both sides
	for (i = (int)strlen(workstr) - 1; i >= 0 && workstr[i] == ' '; i--);
	workstr[i + 1] = 0;
	for (curp = workstr; curp < (workstr + strlen(workstr)) && *curp == ' '; curp++);

	eoword = strchr(curp, ' ');
	if (eoword == NULL)
		eoword = curp + strlen(curp);

	// 9 is the length of the longest commands
	if (eoword == curp || eoword > curp + 9)
	{
		parse_data.parse_error = true;

		if (eoword == curp)
			console.input().print_error("geen commando gegeven");
		else
			console.input().print_error("ongeldig commando gegeven");

		return;
	}

	parse_data.command = Command::undefined;

	for (i = 0; parse_data.command == Command::undefined && i < to_value(Command::COUNT); i++)
	{
		// this search assumes that the commands each start with a different letter
		// it finds the first command that starts with whatever is the command (abbreviation) entered by the user 
		if (!strncmp(commands[i], curp, int(eoword - curp)))
			parse_data.command = static_cast<Command>(i);
	}

	switch (parse_data.command)
	{
	case Command::undefined:

		console.input().print_error("ongeldig commando gegeven");
		parse_data.parse_error = true;
		return;

	case Command::use:
	case Command::lay_down:
	case Command::inspect:

		parse_owned_item_command_param(core, parse_data, commands[to_value(parse_data.command)], eoword);	
		break;

	case Command::combine:

		parse_combine_parameters(core, parse_data, eoword);
		break;

	case Command::pickup:

		if (*eoword != ' ')
		{
			console.input().print_error("syntax: pak <voorwerp>");
			parse_data.parse_error = true;

			return;
		}

		parse_data.item1 = find_laying_item(core, eoword + 1);
		check_found_item(parse_data, parse_data.item1, eoword + 1, "< je ziet hier geen \"%s\" die je kunt meenemen");

		break;
	}
}

void parse_combine_parameters(CoreData& core, ParseData& parse_data, const char* currentMatch)
{
	const char* previousMatch;
	char itemname[25];

	if (*currentMatch != ' ' || (!strstr(currentMatch + 1, " en ") && !strstr(currentMatch + 1, " met ")))
	{
		console.input().print_error("syntax: combineer <voorwerp> en/met <voorwerp>");
		parse_data.parse_error = true;

		return;
	}

	previousMatch = currentMatch + 1;

	// first item ends with interjection word
	if (!(currentMatch = strstr(previousMatch, " en ")))
		currentMatch = strstr(previousMatch, " met ");

	int itemLength = (int)(currentMatch - previousMatch);

	if (itemLength > 24)
		itemLength = 24;

	strncpy(itemname, previousMatch, itemLength);
	itemname[itemLength] = 0;

	parse_data.item1 = find_owned_item(core, itemname);

	if (!check_found_item(parse_data, parse_data.item1, itemname, dontOwnItemFormatString))
		return;

	// second item starts just after interjection word
	previousMatch = currentMatch + ((strstr(currentMatch, " en ") == currentMatch) ? 4 : 5);

	itemLength = (int)strlen(previousMatch);

	if (itemLength >= 25)
		itemLength = 24;

	strncpy(itemname, previousMatch, itemLength);
	itemname[itemLength] = 0;

	parse_data.item2 = find_owned_item(core, itemname);

	if (!check_found_item(parse_data, parse_data.item2, itemname, dontOwnItemFormatString))
		return;
	
	if (parse_data.item1 == parse_data.item2)
	{
		console.input().print_error("je kunt een voorwerp niet met zichzelf combineren");
		parse_data.parse_error = true;
	}
}

bool parse_owned_item_command_param(CoreData& core, ParseData& parse_data, const char* command, const char* parseString)
{
	if (*parseString != ' ')
	{
		console.input().print_error("syntax: %s <voorwerp>", command);
		parse_data.parse_error = true;

		return false;
	}

	parse_data.item1 = find_owned_item(core, parseString + 1);

	return check_found_item(parse_data, parse_data.item1, parseString + 1, dontOwnItemFormatString);
}

bool check_found_item(ParseData& parse_data, ItemID item, const char* itemname, const char* undefinedItemFormatString)
{
	switch (item)
	{
	case ItemID::undefined:

		console.input().print_error(undefinedItemFormatString, itemname);
		parse_data.parse_error = true;

		return false;

	case ItemID::ambiguous:

		console.input().print_error("de afkorting \"%s\" is dubbelzinnig", itemname);
		parse_data.parse_error = true;

		return false;
	}

	return true;
}

ItemID find_owned_item(CoreData& core, const char* item_name)
{
	ItemID item_id = ItemID::undefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (auto& inventory_item : core.inventory)
	{
		if (!strstr(core.items[inventory_item].name, item_name))
			continue;

		if (item_id != ItemID::undefined) 
		{
			item_id = ItemID::ambiguous;
			break;
		}

		item_id = inventory_item;
	}

	return item_id;
}

bool is_room_lit(Status& status) 
{
	return status.current_room == RoomID::radioactive_cave || status.current_room == RoomID::fluorescent_cave
		|| to_value(status.current_room) < to_value(RoomID::slime_cave) || status.is_lamp_on;
}

ItemID find_laying_item(CoreData& core, const char* item_name)
{
	if (!is_room_lit(core.status))
		return ItemID::undefined;

	auto item_id = ItemID::undefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (auto& element : core.items) 
	{
		auto& item = *element.second;
		if (item.room != core.status.current_room || !strstr(item.name, item_name))
			continue;

		if (item_id != ItemID::undefined) 
		{
			item_id = ItemID::ambiguous;
			break;
		}

		item_id = element.first;
	}

	return item_id;
}


