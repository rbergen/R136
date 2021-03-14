#include "r136.h"

int get_random_number(int max)
{
	return rand() % max;
}

AnimateStatus get_random_status(int lowest, int highest)
{
	return static_cast<AnimateStatus>((rand() % (highest - lowest + 1)) + lowest);
}

AnimateStatus get_random_status(AnimateStatus lowest, AnimateStatus highest)
{
	return get_random_status(to_value(lowest), to_value(highest));
}

