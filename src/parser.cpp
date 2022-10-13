#include "base.h"
#include "console.h"
#include "status.h"
#include "parser.h"

void Parser::parse_combine_parameters(CoreData& core, ParseData& parse_data, const string& param_string)
{
	size_t position = string::npos;
	size_t interjection_length;
	const std::vector<string>& my_interjections = select(interjections);

	for (auto& interjection : my_interjections)
	{
		position = param_string.find(interjection);

		if (position != string::npos) 
		{
			interjection_length = interjection.length();

			break;
		}
	}

	if (position == string::npos)
	{
		console.input().print_error(select(
			"syntax: combineer <voorwerp> en/met <voorwerp>"
		, 
			"syntax: {command} <object> and/with <object>"
		));
		parse_data.parse_error = true;

		return;
	}

	string item_name = param_string.substr(0, position);

	parse_data.item1 = find_owned_item(core, item_name);

	if (!check_found_item(core, parse_data, parse_data.item1, item_name, select(dont_own_item_format_string)))
		return;

	// second item starts just after interjection word
	item_name = param_string.substr(position + interjection_length);

	parse_data.item2 = find_owned_item(core, item_name);

	if (!check_found_item(core, parse_data, parse_data.item2, item_name, select(dont_own_item_format_string)))
		return;

	if (parse_data.item1 == parse_data.item2)
	{
		console.input().print_error(select(
			"je kunt een voorwerp niet met zichzelf combineren"
		, 
			"you can't combine an object with itself"
		));
		parse_data.parse_error = true;
	}
}

bool Parser::parse_owned_item_command_param(CoreData& core, ParseData& parse_data, const string& command, const string& parse_string)
{
	if (parse_string.size() == 0)
	{
		console.input().print_error(select("syntax: {0} <voorwerp>", "syntax: {0} <object>"), command);
		parse_data.parse_error = true;

		return false;
	}

	parse_data.item1 = find_owned_item(core, parse_string);

	return check_found_item(core, parse_data, parse_data.item1, parse_string, select(dont_own_item_format_string));
}

bool Parser::check_found_item(CoreData& core, ParseData& parse_data, ItemID item, const string& item_name, const string undefined_item_format_string)
{
	switch (item)
	{
	case ItemID::undefined:

		console.input().print_error(undefined_item_format_string, item_name);
		parse_data.parse_error = true;

		return false;

	case ItemID::ambiguous:

		console.input().print_error(select(
			"de afkorting \"{0}\" is dubbelzinnig"
		, 
			"the abbreviation \"{0}\" is ambiguous"
		), item_name);

		parse_data.parse_error = true;

		return false;

	default:
		break;
	}

	return true;
}

ItemID Parser::find_owned_item(CoreData& core, const string& item_name)
{
	ItemID item_id = ItemID::undefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (auto& inventory_item : core.inventory)
	{
		if (select(core.items[inventory_item].names).find(item_name) == string::npos)
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
	if (!status::is_room_lit(core))
		return ItemID::undefined;

	auto item_id = ItemID::undefined;

	// this search finds the occurrance of the name entered by the user in any part of the item names, and signals multiple matches
	for (auto& element : core.items)
	{
		auto& item = *element.second;
		if (item.room != core.status.current_room || select(item.names).find(item_name) == string::npos)
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
		console.input().print_error(command.size() == 0 ? 
			select("geen commando gegeven", "no command entered") 
		: 
			select("ongeldig commando gegeven", "invalid command entered")
		);
		parse_data.parse_error = true;
		return parse_data;
	}

	parse_data.command = Command::undefined;

	for (i = 0; parse_data.command == Command::undefined && i < to_value(Command::COUNT); i++)
	{
		// this search assumes that the commands each start with a different letter
		// it finds the first command that starts with whatever is the command (abbreviation) entered by the user 
		if (select(commands[i]).find(command) == 0)
			parse_data.command = static_cast<Command>(i);
	}

	switch (parse_data.command)
	{
	case Command::undefined:
		console.input().print_error(select("ongeldig commando gegeven", "invalid command entered"));
		parse_data.parse_error = true;
		break;

	case Command::use:
	case Command::lay_down:
	case Command::inspect:
		parse_owned_item_command_param(core, parse_data, select(commands[to_value(parse_data.command)]), input_string);
		break;

	case Command::combine:
		parse_combine_parameters(core, parse_data, input_string);
		break;

	case Command::pickup:
		if (input_string.size() == 0)
		{
			console.input().print_error(select("syntax: pak <voorwerp>", "syntax: pickup <object>"));
			parse_data.parse_error = true;

			break;
		}

		parse_data.item1 = find_laying_item(core, input_string);
		check_found_item(core, parse_data, parse_data.item1, input_string, select(
			"je ziet hier geen \"{0}\" die je kunt meenemen"
		,
			"you don't see any \"{0}\" that you can pick up"
		));

		break;

	default:
		break;
	}

	return parse_data;
}

const std::vector<string> Parser::dont_own_item_format_string = { "je hebt geen \"{0}\"", "you don't have any \"{0}\"" };

// note: one command per line, one comma-separated entry per language
const std::vector<string> Parser::commands[] = {
	{ "oost", "east" },
	{ "west", "west" },
	{ "noord", "north" },
	{ "zuid", "south" },
	{ "klim", "ascend" },
	{ "daal", "descend" },
	{ "gebruik", "use" },
	{ "combineer", "combine" },
	{ "pak", "pickup" },
	{ "leg", "lay" },
	{ "bekijk", "inspect" },
	{ "afwachten", "bide" },
	{ "einde", "finish" },
	{ "status", "report" },
	{ "help", "help" },
	{ "taal", "todutch" }
};

// note: one language per line, comma-separated interjections 
const std::vector<string> Parser::interjections[] = { 
	{ " en ", " met " }, 
	{ " and ", " with " } 
};
