#pragma once

// inlines/random.h

#include "../base.h"
#include "types/random.h"

inline int get_number(int max)
{
	return rand() % max;
}

inline AnimateStatus get_status(int lowest, int highest)
{
	return static_cast<AnimateStatus>((rand() % (highest - lowest + 1)) + lowest);
}

inline AnimateStatus get_status(AnimateStatus lowest, AnimateStatus highest)
{
	return get_status(to_value(lowest), to_value(highest));
}

