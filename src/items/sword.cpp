#include "base.h"
#include "console.h"
#include "actions.h"
#include "items.h"
#include "random.h"

void Sword::use(CoreData& core)
{
	AnimateID monsterID;
	auto& animates = core.animates;
	auto& current_room = core.status.current_room;

	if (animates[AnimateID::hellhound].room == current_room && animates[AnimateID::hellhound].strikes_left)
		monsterID = AnimateID::hellhound;
	else if (animates[AnimateID::plant].room == current_room && animates[AnimateID::plant].strikes_left)
		monsterID = AnimateID::plant;
	else
	{
		report_pointless_use();
		return;
	}

	auto& monster = animates[monsterID];

	while (true)
	{
		console.main().print("Je haalt uit met je zwaard");

		if (random::get_number(100) > 70)
			console.main().print(", maar het monster ontwijkt.\n");
		else
		{
			console.main().print(" en je raakt het monster hard.\n");
			monster.strikes_left--;
		}

		if (monster.strikes_left == 1)
			console.main().print("\nHet monster is zwaar gewond en je baadt in zijn bloed.\n");

		if (!monster.strikes_left || random::get_number(100) > 30)
			break;

		console.main().print("\nJe kunt nog een slag uitdelen. Wil je dat? ");

		if (tolower(console.main().get_char_input("jJnN")) != 'j')
		{
			console.main().print("\n");
			break;
		}

		console.main().print("\n");
	}
	console.main().print("\n");

	if (!monster.strikes_left)
	{
		monster.status = AnimateStatus::dead;
		actions::progress_animates(core);
	}

	console.main().wait_for_key(true);
}