#include "base.h"
#include "console.h"
#include "constants.h"
#include "items.h"

void Bandage::use(CoreData& core)
{
	if (core.status.life_points == constants::max_life_points)
	{
		console.main().print("Je bent nog helemaal heel!\n");
		return;
	}

	console.main().print("Je pakt het verband en de pleisters en plaatst ze over je wonden. Je bijt even\n"
		"op je lippen van de pijn als het verband je nog bloedende wonden raakt.\n\n"
		"Je bent weer zo goed als nieuw.\n");

	core.status.life_points = constants::max_life_points;

	core.inventory.remove(*this);

	console.main().wait_for_key(true);
}