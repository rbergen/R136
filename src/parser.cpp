#include "r136.h"
#include "parser.h"

void Parser::parse_combine_parameters(CoreData& core, ParseData& parse_data, const string& param_string)
{
	if (param_string.find(" en ") == string::npos && param_string.find(" met ") == string::npos)
	{
		console.input().print_error("syntax: combineer <voorwerp> en/met <voorwerp>");
		parse_data.parse_error = true;

		return;
	}

	size_t position;
	int interjection_length;

	// first item ends with interjection word
	if ((interjection_length = 4, (position = param_string.find(" en "))) == string::npos)
		interjection_length = 5, position = param_string.find(" met ");

	string item_name = param_string.substr(0, position);

	parse_data.item1 = find_owned_item(core, item_name);

	if (!check_found_item(parse_data, parse_data.item1, item_name, dont_own_item_format_string))
		return;

	// second item starts just after interjection word
	item_name = param_string.substr(position + interjection_length);

	parse_data.item2 = find_owned_item(core, item_name);

	if (!check_found_item(parse_data, parse_data.item2, item_name, dont_own_item_format_string))
		return;

	if (parse_data.item1 == parse_data.item2)
	{
		console.input().print_error("je kunt een voorwerp niet met zichzelf combineren");
		parse_data.parse_error = true;
	}
}

bool Parser::parse_owned_item_command_param(CoreData& core, ParseData& parse_data, const string& command, const string& parse_string)
{
	if (parse_string.size() == 0)
	{
		console.input().print_error("syntax: {0} <voorwerp>", command);
		parse_data.parse_error = true;

		return false;
	}

	parse_data.item1 = find_owned_item(core, parse_string);

	return check_found_item(parse_data, parse_data.item1, parse_string, dont_own_item_format_string);
}

bool Parser::check_found_item(ParseData& parse_data, ItemID item, const string& item_name, const string undefined_item_format_string)
{
	switch (item)
	{
	case ItemID::undefined:

		console.input().print_error(undefined_item_format_string, item_name);
		parse_data.parse_error = true;

		return false;

	case ItemID::ambiguous:

		console.input().print_error("de afkorting \"{0}\" is dubbelzinnig", item_name);
		parse_data.parse_error = true;

		return false;
	}

	return true;
}

ItemID Parser::find_owned_item(CoreData& core, const string& item_name)
{
	ItemID item_id = ItemID::undefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (auto& inventory_item : core.inventory)
	{
		if (core.items[inventory_item].name.find(item_name) == string::npos)
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

ItemID Parser::find_laying_item(CoreData& core, string& item_name)
{
	if (!is_room_lit(core))
		return ItemID::undefined;

	auto item_id = ItemID::undefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (auto& element : core.items)
	{
		auto& item = *element.second;
		if (item.room != core.status.current_room || item.name.find(item_name) == string::npos)
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

Parser::Parser() :
	parse_data(ParseData())
{}

ParseData& Parser::parse_input(CoreData& core, string& input_string)
{
	int i;

	parse_data.parse_error = false;

	while (input_string.size() > 0 && input_string[0] == ' ')
		input_string.erase(0, 1);

	while (input_string.size() > 0 && input_string[input_string.size() - 1] == ' ')
		input_string.erase(input_string.size() - 1);

	auto space_position = input_string.find(' ');

	auto &command = (const string&)(space_position == string::npos ? input_string : input_string.substr(0, space_position));
	input_string = (space_position == string::npos) ? "" : input_string.substr(space_position + 1);

	// 9 is the length of the longest commands
	if (command.size() == 0 || command.size() > 9)
	{
		console.input().print_error(command.size() == 0 ? "geen commando gegeven" : "ongeldig commando gegeven");
		parse_data.parse_error = true;
		return parse_data;
	}

	parse_data.command = Command::undefined;

	for (i = 0; parse_data.command == Command::undefined && i < to_value(Command::COUNT); i++)
	{
		// this search assumes that the commands each start with a different letter
		// it finds the first command that starts with whatever is the command (abbreviation) entered by the user 
		if (commands[i].find(command) == 0)
			parse_data.command = static_cast<Command>(i);
	}

	switch (parse_data.command)
	{
	case Command::undefined:
		console.input().print_error("ongeldig commando gegeven");
		parse_data.parse_error = true;
		break;

	case Command::use:
	case Command::lay_down:
	case Command::inspect:
		parse_owned_item_command_param(core, parse_data, commands[to_value(parse_data.command)], input_string);
		break;

	case Command::combine:
		parse_combine_parameters(core, parse_data, input_string);
		break;

	case Command::pickup:
		if (input_string.size() == 0)
		{
			console.input().print_error("syntax: pak <voorwerp>");
			parse_data.parse_error = true;

			break;
		}

		parse_data.item1 = find_laying_item(core, input_string);
		check_found_item(parse_data, parse_data.item1, input_string, "je ziet hier geen \"{0}\" die je kunt meenemen");

		break;
	}

	return parse_data;
}

string Parser::dont_own_item_format_string = "je hebt geen \"{0}\"";

string Parser::commands[] = { "oost", "west", "noord", "zuid", "klim", "daal", "gebruik", "combineer", "pak", "leg", "bekijk", "afwachten", "einde", "status", "help" };
