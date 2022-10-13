#include "base.h"
#include "console.h"
#include "gamedata.h"
#include "status.h"
#include "actions.h"
#include "startup.h"

int main(int argc, char* argv[])
{
	CoreData core;

	startup::parse_arguments(core, argc, argv);

	console.initialize(core.language);

	startup::run_intro();

	startup::initialize(core);

	startup::show_splashscreen(core);

	if (game_data::load(core))
		console.set_language(core.language);
	else
		startup::show_start_message(core);

	while (true)
	{
		status::show_room_status(core);
		if (actions::progress_animates(core) && !actions::perform_command(core))
			break;
	}

	game_data::save(core);

	console.main().wait_for_key(true, core.language);
	console.main().clear();

	console.release();

	return 0;
}

