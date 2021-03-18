#pragma once

#include "types/base.h"

namespace random
{
	int get_number(int max);

	AnimateStatus get_status(int lowest, int highest);

	AnimateStatus get_status(AnimateStatus lowest, AnimateStatus highest);
}
