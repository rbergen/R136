#include "r136.h"
#include "gamedata.h"
#include "status.h"
#include "main.h"
#include "startup.h"

int main()
{
	CoreData core;

	console.initialize();

	startup::run_intro();

	startup::initialize(core);

	startup::show_splashscreen();

	if (!game_data::load(core))
		startup::show_start_message();

	while (true)
	{
		status::show_room_status(core);
		if (progress_animates(core))
			if (!perform_command(core))
				break;
	}

	game_data::save(core);

	console.main().wait_for_key(true);
	console.main().clear();

	console.release();

	return 0;
}

