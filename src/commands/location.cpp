#include "base.h"
#include "console.h"
#include "random.h"
#include "commands.h"

namespace commands
{
	namespace
	{
		void handle_gnu_room(CoreData& core)
		{
			auto& gnu = core.animates[AnimateID::gnu];

			if (gnu.room == core.status.current_room && gnu.status != AnimateStatus::dead)
			{
				switch (random::get_number(5))
				{
				case 0:
					gnu.room = RoomID::gnu_cave;
					break;
				case 1:
					gnu.room = RoomID::rock_cave;
					break;
				case 2:
					gnu.room = RoomID::emptiness;
					break;
				case 3:
					gnu.room = RoomID::sandbank;
					break;
				case 4:
					gnu.room = RoomID::oil_cave;
					break;
				}
			}
		}

		void handle_paper_route(CoreData& core)
		{
			auto& status = core.status;

			if (status.paper_route_pos != core.paperroute.size())
			{
				if (status.current_room == core.paperroute[status.paper_route_pos])
					status.paper_route_pos++;
				else
					status.paper_route_pos = 0;

				if (status.paper_route_pos == core.paperroute.size())
					core.animates[AnimateID::hatch].status = AnimateStatus::hatch_opening;
			}
		}
	}

	void go(CoreData& core, Command direction)
	{
		auto& status = core.status;

		if (!core.rooms[status.current_room].connections.is_open(direction))
		{
			console.main().print("Daar kun je niet heen.\n");
			return;
		}

		handle_gnu_room(core);

		status.current_room = core.rooms[status.current_room].connections[direction];

		handle_paper_route(core);
	}
}