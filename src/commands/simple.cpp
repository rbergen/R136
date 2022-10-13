#include "base.h"
#include "console.h"
#include "random.h"
#include "actions.h"

namespace commands
{
	bool finish(CoreData& core)
	{
		console.main().print(select("Weet je zeker dat je de aarde laat vergaan? ", "Are you sure you want to leave the earth to die? "));
		if (get_y_or_n())
			return false;
		console.main().empty_line();
		console.main().print(select("Mooi zo!", "Good!"));

		return true;
	}

	void wait(CoreData& core)
	{
		switch (randomizer::get_number(5))
		{
		case 0:
			console.main().print(select("Je pulkt wat in je neus.", "You pick your nose a little."));
			break;

		case 1:
			console.main().print(select("Je krabt wat achter je oren.", "You scratch a little behind your ears."));
			break;

		case 2:
			console.main().print(select("Je gaapt even uitgebreid.", "You yawn extensively."));
			break;

		case 3:
			console.main().print(select("Je trekt je broek even op.", "You pull up your pants."));
			break;

		case 4:
			console.main().print(select("Je pulkt wat smeer uit je oren.", "You pick some grease from your ears."));
			break;
		}
	}

	void show_status(CoreData& core)
	{
		auto& status = core.status;

		console.main().print(select("--- STATUSRAPPORT ---", "--- STATUS REPORT ---"));
		console.main().empty_line();
		console.main().print(
			select("Je hebt nog {0} levenspunten.\n", "You have {0} life points left.\n")
		, 
			std::to_string(status.life_points)
		);

		auto& inventory = core.inventory;
		if (core.flashlight().is_in_posession())
			console.main().print(
				select("Je zaklamp staat {0}.\n", "Your flashlight is {0}.\n")
			, 
				core.flashlight().is_on ? select("aan", "on") : select("uit", "off")
			);

		if (inventory.count() == 0)
		{
			console.main().print(select("Je draagt niets.\n", "You have nothing on you.\n"));
			return;
		}

		console.main().print(select("Je hebt in je bezit:\n", "You have in your posession:\n"));

		for (auto& item : core.inventory)
			console.main().print("* {0}\n", select(core.items[item].names));
	}

	void switch_language(CoreData& core)
	{
		switch (core.language)
		{
		case Language::Dutch:
			core.language = Language::English;
			break;

		case Language::English:
			core.language = Language::Dutch;
			break;

		default:
			break;
		}

		console.set_language(core.language);

		console.main().print(select(
			"Ok, we gaan in het Nederlands verder. Type h voor help."
		,
			"Okay, we'll continue in English. Type h for help."
		));
	}

	void show_help(CoreData& core)
	{
		console.main().print("--- HELP ---");
		console.main().empty_line();
		console.main().print(select(
			"Commando's:\n"
			"* oost\n"
			"* west\n"
			"* noord\n"
			"* zuid\n"
			"* klim\n"
			"* daal\n"
			"* gebruik <voorwerp>\n"
			"* combineer <voorwerp> en/met <voorwerp>\n"
			"* pak <voorwerp>\n"
			"* leg <voorwerp>\n"
			"* bekijk <voorwerp>\n"
			"* afwachten\n"
			"* einde\n"
			"* status\n"
			"* help\n"
			"* taal\n"
			"\n"
			"Type taal to switch to English.\n"
		,
			"Commands:\n"
			"* east\n"
			"* west\n"
			"* north\n"
			"* south\n"
			"* ascend\n"
			"* descend\n"
			"* use <object>\n"
			"* combine <object> and/with <object>\n"
			"* pickup <object>\n"
			"* lay <object>\n"
			"* inspect <object>\n"
			"* bide\n"
			"* finish\n"
			"* report\n"
			"* help\n"
			"* todutch\n"
			"\n"
			"Type todutch om over te schakelen naar Nederlands.\n"
		));
	}
}