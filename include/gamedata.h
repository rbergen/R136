#pragma once

// gamedata.h - service interface: public API of src/gamedata.cpp

#include "types/base.h"

namespace game_data
{
	bool load(CoreData& core);
	bool save(CoreData& core);
	void remove();
}
