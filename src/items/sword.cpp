#include "base.h"
#include "console.h"
#include "actions.h"
#include "items.h"
#include "random.h"

bool Sword::use(CoreData& core)
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
		return false;
	}

	auto& monster = animates[monsterID];

	while (true)
	{
		console.main().print("Je haalt uit met je zwaard");

		if (randomizer::get_number(100) > 70)
			console.main().print(", maar het monster ontwijkt.");
		else
		{
			console.main().print(" en je raakt het monster hard.");
			monster.strikes_left--;
		}

		console.main().empty_line();

		if (monster.strikes_left == 1) 
		{
			console.main().print("Het monster is zwaar gewond en je baadt in zijn bloed.");
			console.main().empty_line();
		}

		if (!monster.strikes_left || randomizer::get_number(100) > 30)
		{
			console.main().wait_for_key(true);
			break;
		}

		console.main().print("Je kunt nog een slag uitdelen. Wil je dat? ");

		if (tolower(console.main().get_char_input("jJnN")) != 'j')
		{
			console.main().empty_line();
			break;
		}

		console.main().empty_line();
	}

	console.main().empty_line();

	if (!monster.strikes_left)
	{
		monster.status = AnimateStatus::dead;
		return true;
	}

	return false;
}