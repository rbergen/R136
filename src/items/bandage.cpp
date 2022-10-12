#include "base.h"
#include "console.h"
#include "constants.h"
#include "items.h"

bool Bandage::use(CoreData& core)
{
	if (core.status.life_points == constants::max_life_points)
	{
		console.main().print(select("Je bent nog helemaal heel!\n", "You're still in one piece!\n"));
		return false;
	}

	console.main().print(select(
		"Je pakt het verband en de pleisters en plaatst ze over je wonden. Je bijt even op je lippen van de pijn als het verband je nog bloedende wonden raakt."
		,
		"You take the bandages and band-aids and puts them over your wounds. You bite your lips when you feel the pain of the bandages touchting your wounds that are still bleeding."
	));
	console.main().empty_line();
	console.main().print(select("Je bent weer zo goed als nieuw.", "You're as good as new."));
	console.main().empty_line();

	core.status.life_points = constants::max_life_points;

	core.inventory.remove(*this);

	console.main().wait_for_key(true, core.language);
	return true;
}