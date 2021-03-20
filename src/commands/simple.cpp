#include "base.h"
#include "console.h"
#include "random.h"
#include "actions.h"

namespace commands
{
	bool finish()
	{
		console.main().print("Weet je zeker dat je de aarde laat vergaan? ");
		if (tolower(console.main().get_char_input("jJnN")) == 'j')
			return false;
		console.main().empty_line();
		console.main().print("Mooi zo!");

		return true;
	}

	void wait(void)
	{
		switch (randomizer::get_number(5))
		{
		case 0:
			console.main().print("Je pulkt wat in je neus.");
			break;

		case 1:
			console.main().print("Je krabt wat achter je oren.");
			break;

		case 2:
			console.main().print("Je gaapt even uitgebreid.");
			break;

		case 3:
			console.main().print("Je trekt je broek even op.");
			break;

		case 4:
			console.main().print("Je pulkt wat smeer uit je oren.");
			break;
		}
	}

	void show_status(CoreData& core)
	{
		auto& status = core.status;

		console.main().print("--- STATUSRAPPORT ---");
		console.main().empty_line();
		console.main().print("Je hebt nog {0} levenspunten.\n", std::to_string(status.life_points));

		auto& inventory = core.inventory;
		if (core.flashlight().is_in_posession())
			console.main().print("Je zaklamp staat {0}.\n", core.flashlight().is_on ? "aan" : "uit");

		if (inventory.count() == 0)
		{
			console.main().print("Je draagt niets.\n");
			return;
		}

		console.main().print("Je hebt in je bezit:\n");

		for (auto& item : core.inventory)
			console.main().print("* {0}\n", core.items[item].name);
	}

	void show_help(void)
	{
		console.main().print("--- HELP ---");
		console.main().empty_line();
		console.main().print("Commando's:\n"
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
			"* help\n");
	}
}