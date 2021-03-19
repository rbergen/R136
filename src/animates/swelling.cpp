#include "base.h"
#include "console.h"
#include "animates.h"

Swelling::Swelling(RoomID room) : Animate(room) {}

bool Swelling::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::swelling].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je\n");
		console.main().print("aan met 2 gluiperige ogen, op zijn huid zitten schurftvlekken, en op zijn\n");
		console.main().print("mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich\n");
		console.main().print("vast aan alle wanden van de grot en verspert zo je weg.\n\n");

		core.animates[AnimateID::swelling].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht.\n\n");

		break;

	case AnimateStatus::swelling_gassed:
		if (core.items[ItemID::gasmask].room == RoomID::owned)
			// gasmasker op
		{
			console.main().print("Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n");
			console.main().print("Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen\n");
			console.main().print("overal scheuren in zijn schurfterige huid. Zijn tentakels komen langzaam met\n");
			console.main().print("een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in el-\n");
			console.main().print("kaar.\n\n");
		}
		else
			// geen masker... oeps!
		{
			console.main().print("Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen,\n");
			console.main().print("voordat je zelf een kloppende hoofdpijn krijgt en onderuit gaat. Je hebt niets\n");
			console.main().print("om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer\n");
			console.main().print("bij.\n\n");

			core.status.life_points -= 4; //    Grote wond
		}

		core.rooms[RoomID::bat_cave].connections.set(Command::north, RoomID::damnation_cave);
		core.animates[AnimateID::swelling].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print("Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn\n");
		console.main().print("maag kruipen pissebedden en oorkruipers. Er verspreidt zich een sterke rot-\n");
		console.main().print("lucht, en er ontstaat langzaam een klein slijmplasje.\n\n");

		break;
	}

	return true;
}