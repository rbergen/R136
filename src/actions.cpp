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
			console.main().print(select(
				"Badend in je eigen bloed bezwijk je aan je verwondingen. Terwijl je liggend op de grond met moeite naar adem snakt, "
				"hoor je in de verte een luid gelach.\n"
				"Dan zakken je ogen dicht en stopt je hart met kloppen.\n"
				"Op hetzelfde moment ontploft de bom en sterft de aarde met jou."
			,
				"Bathing in your own blood, you succumb to your injuries. While you're gasping for air on the ground, "
				"you hear loud laughter from a distance.\n"
				"Then your eyes close and your heart stops beating.\n"
				"At the same time, the bomb explodes and the earth dies with you."
			));

			console.main().empty_line();
			general::force_exit(core.language);
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
				commands::wait(core);
				break;

			case Command::finish:
				if (!commands::finish(core))
					return false;

				break;

			case Command::status:
				commands::show_status(core);
				break;

			case Command::language:
				commands::switch_language(core);
				break;

			case Command::help:
				commands::show_help(core);
				break;

			default:
				break;
			}

			console.main().empty_line();
		} 	
		while (
			parse_data.command == Command::status || 
			parse_data.command == Command::help || 
			parse_data.command == Command::finish || 
			parse_data.command == Command::language
		);

		return true;
	}
}

