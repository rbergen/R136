#pragma once
#include "r136.h"

bool parse_owned_item_command_param(CoreData& core, ParseData& parse_data, const char* command, const char* parseString);

bool check_found_item(ParseData& parse_data, ItemID item, const char* itemname, const char* undefinedItemFormatString);

ItemID find_owned_item(CoreData& core, const char* item_name);

bool is_room_lit(Status& status);

ItemID find_laying_item(CoreData& core, const char* item_name);

void parse_input(CoreData& core, char* inpstr, ParseData& parse_data);

void parse_combine_parameters(CoreData& core, ParseData& parse_data, const char* currentMatch);

bool perform_command(CoreData& core);

void use(CoreData& core, ItemID item_id);

void use_item_to_status(CoreData& core, Item item, AnimateID animate, AnimateStatus status);

void combine(CoreData& core, ItemID item1, ItemID item2);

void lay_down(CoreData& core, ItemID item_id);

void pickup(CoreData& core, ItemID item_id);

void inspect(CoreData& core, ItemID item_id);

void wait(void);

void show_status(CoreData& core);

void show_help(void);
