#pragma once

// inlines/general.h

#include "types/general.h"
#include <thread>

inline void general::sleep_ms(int count)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(count));
}
