#pragma once

// actions.h - service interface: public API of src/actions.cpp

#include "types/base.h"

namespace actions
{
	bool progress_animates(CoreData& core);

	bool perform_command(CoreData& core);
}