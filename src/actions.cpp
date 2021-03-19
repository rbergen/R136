#include "base.h"
#include "console.h"
#include "general.h"
#include "parser.h"
#include "commands.h"
#include "actions.h"

namespace actions
{
	namespace
	{
		InputWindow& input_window()
		{
			static InputWindow* window = &console.input();
			return *window;
		}
	}

	bool progress_animates(CoreData& core)
	{
		for (auto& element : core.animates)
		{
			Animate& animate = *element.second;

			if (animate.room == core.status.current_room)
				return animate.progress_status(core);
		}

		return true;
	}

	bool perform_command(CoreData& core)
	{
		static Parser parser{};

		if (core.status.life_points <= 0)
		{
			console.main().print("Badend in je eigen bloed bezwijk je aan je verwondingen. Terwijl je liggend op\n");
			console.main().print("de grond met moeite naar adem snakt, hoor je in de verte een luid gelach.\n");
			console.main().print("Dan zakken je ogen dicht en stopt je hart met kloppen.\n");
			console.main().print("Op hetzelfde moment ontploft de bom en sterft de aarde met jou.");
			console.main().empty_line();
			general::force_exit();
		}

		core.flashlight().decrease_battery_level(core);

		ParseData parse_data{};

		do
		{
			string input_string;

			do
			{
				input_string = string(65, ' ');
				console.input().get_string_input(input_string);
				parse_data = parser.parse_input(core, input_string);
			} 
			while (parse_data.parse_error);

			console.main().empty_line();
			console.main().print_centered("---***---");
			console.main().empty_line();

			auto& status = core.status;

			switch (parse_data.command)
			{
			case Command::east:
			case Command::west:
			case Command::north:
			case Command::south:
			case Command::up:
			case Command::down:
				commands::go(core, parse_data.command);
				return true;

			case Command::use:
				commands::use(core, parse_data.item1);
				break;

			case Command::combine:
				commands::combine(core, parse_data.item1, parse_data.item2);
				break;

			case Command::pickup:
				commands::pickup(core, parse_data.item1);
				break;

			case Command::lay_down:
				commands::lay_down(core, parse_data.item1);
				break;

			case Command::inspect:
				commands::inspect(core, parse_data.item1);
				break;

			case Command::wait:
				commands::wait();
				break;

			case Command::finish:
				if (!commands::finish())
					return false;

				break;

			case Command::status:
				commands::show_status(core);
				break;

			case Command::help:
				commands::show_help();
				break;
			}

			console.main().empty_line();
		} 	
		while (parse_data.command == Command::status || parse_data.command == Command::help || parse_data.command == Command::finish);

		return true;
	}
}

