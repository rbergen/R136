#include "base.h"
#include "console.h"
#include "animates.h"

Swelling::Swelling(RoomID room) : Animate(room) {}

bool Swelling::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::swelling].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je aan met 2 gluiperige ogen, "
			"op zijn huid zitten schurftvlekken, en op zijn mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich "
			"vast aan alle wanden van de grot en verspert zo je weg.");

		core.animates[AnimateID::swelling].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.");

		break;

	case AnimateStatus::swelling_gassed:
		if (core.items[ItemID::gasmask].room == RoomID::in_posession)
			// gasmasker op
		{
			console.main().print("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n"
			"Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen overal scheuren in zijn schurfterige huid. "
				"Zijn tentakels komen langzaam met een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in elkaar.");
		}
		else
			// geen masker... oeps!
		{
			console.main().print("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen, voordat je zelf een kloppende hoofdpijn "
				"krijgt en onderuit gaat. Je hebt niets om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer bij.");

			core.status.life_points -= 4; //    Grote wond
		}

		core.rooms[RoomID::bat_cave].connections.set(Command::north, RoomID::damnation_cave);
		core.animates[AnimateID::swelling].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn maag kruipen pissebedden en oorkruipers. "
			"Er verspreidt zich een sterke rotlucht, en er ontstaat langzaam een klein slijmplasje.");

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}