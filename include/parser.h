#include "types/r136.h"

struct ParseData
{
	Command command;
	ItemID item1;
	ItemID item2;
	bool parse_error;
};

class Parser {
	static string dont_own_item_format_string;
	static string commands[];

	ParseData parse_data;

	void parse_combine_parameters(CoreData& core, ParseData& parse_data, const string& param_string);
	bool parse_owned_item_command_param(CoreData& core, ParseData& parse_data, const string& command, const string& parse_string);
	bool check_found_item(ParseData& parse_data, ItemID item, const string& item_name, const string undefined_item_format_string);
	ItemID find_owned_item(CoreData& core, const string& item_name);
	ItemID find_laying_item(CoreData& core, string& item_name);

public:
	Parser();

	ParseData& parse_input(CoreData& core, string& input_string);
};
