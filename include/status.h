#pragma once

// status.h - service interface: public API of src/status.cpp

#include "types/base.h"

namespace status
{
	bool is_room_lit(CoreData& core);
	void show_room_status(CoreData& core);
}