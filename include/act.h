#pragma once

#include "types/base.h"

bool perform_command(CoreData& core);

void use(CoreData& core, ItemID item_id);

void use_item_to_status(CoreData& core, Item& item, AnimateID animate, AnimateStatus status);

void combine(CoreData& core, ItemID item1, ItemID item2);

void lay_down(CoreData& core, ItemID item_id);

void pickup(CoreData& core, ItemID item_id);

void inspect(CoreData& core, ItemID item_id);

void wait(void);

void show_status(CoreData& core);

void show_help(void);
