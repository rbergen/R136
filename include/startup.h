#pragma once

// startup.h - service interface: public API of src/startup.cpp and src/intro.cpp

#include "types/base.h"

namespace startup
{
	void run_intro();
	void show_splashscreen(CoreData& core);
	void show_start_message(CoreData& core);
	void initialize(CoreData& core);
	void parse_arguments(CoreData& core, int argc, char* argv[]);
}