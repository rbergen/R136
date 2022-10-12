#pragma once

#include "base.h"

namespace commands
{
	bool finish(CoreData& core);

	void wait(CoreData& core);

	void show_status(CoreData& core);

	void show_help(CoreData& core);

	void use(CoreData& core, ItemID item_id);

	void combine(CoreData& core, ItemID item1, ItemID item2);

	void lay_down(CoreData& core, ItemID item_id);

	void pickup(CoreData& core, ItemID item_id);

	void inspect(CoreData& core, ItemID item_id);

	void go(CoreData& core, Command direction);
}