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
		console.main().print("\nMooi zo!\n");

		return true;
	}

	void wait(void)
	{
		switch (random::get_number(5))
		{
		case 0:
			console.main().print("Je pulkt wat in je neus.\n");
			break;

		case 1:
			console.main().print("Je krabt wat achter je oren.\n");
			break;

		case 2:
			console.main().print("Je gaapt even uitgebreid.\n");
			break;

		case 3:
			console.main().print("Je trekt je broek even op.\n");
			break;

		case 4:
			console.main().print("Je pulkt wat smeer uit je oren.\n");
			break;
		}
	}

	void show_status(CoreData& core)
	{
		auto& status = core.status;

		console.main().print("--- STATUSRAPPORT ---\n\n");
		console.main().print("Je hebt nog {0} levenspunten.\n", std::to_string(status.life_points));

		auto& inventory = core.inventory;
		if (inventory.contains(ItemID::flashlight))
			console.main().print("Je zaklamp staat {0}.\n", core.flashlight().is_on ? "aan" : "uit");

		if (inventory.count() == 0)
		{
			console.main().print("Je draagt niets.\n");
			return;
		}

		console.main().print("Je hebt in je bezit:\n");

		for (auto& item : core.inventory)
			console.main().print("    {0}\n", core.items[item].name);
	}

	void show_help(void)
	{
		console.main().print("--- HELP ---\n\n");
		console.main().print("Commando's:\n");
		console.main().print("   oost\n");
		console.main().print("   west\n");
		console.main().print("   noord\n");
		console.main().print("   zuid\n");
		console.main().print("   klim\n");
		console.main().print("   daal\n");
		console.main().print("   gebruik <voorwerp>\n");
		console.main().print("   combineer <voorwerp> en/met <voorwerp>\n");
		console.main().print("   pak <voorwerp>\n");
		console.main().print("   leg <voorwerp>\n");
		console.main().print("   bekijk <voorwerp>\n");
		console.main().print("   afwachten\n");
		console.main().print("   einde\n");
		console.main().print("   status\n");
		console.main().print("   help\n");
	}
}