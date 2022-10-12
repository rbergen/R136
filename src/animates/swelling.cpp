#include "base.h"
#include "console.h"
#include "animates.h"

Swelling::Swelling(RoomID room) : Animate(room) {}

bool Swelling::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::swelling].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"Er staat hier een wezen dat nog het meest lijkt op een gezwel. Het kijkt je aan met 2 gluiperige ogen, "
			"op zijn huid zitten schurftvlekken, en op zijn mondhoeken groeien algen. Met zijn lange, glibberige tentakels houdt het zich "
			"vast aan alle wanden van de grot en verspert zo je weg."
		,
			"There is a creature here that can be best described as a lump. It looks at you with two sneaky eyes, "
			"scavy spots are on its skin, and algae grow on the corners of its mouth. With its long, slippery tentacles it holds on "
			"to all walls of the cave, blocking your path."
		));

		core.animates[AnimateID::swelling].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print(select(
			"Het gezwel zit nog steeds aan de grotwanden vastgezogen, en het trilt licht."
		,
			"The lump is still sucked solidly to the cave walls, and it trembles lightly."
		));

		break;

	case AnimateStatus::swelling_gassed:
		if (core.items[ItemID::gasmask].room == RoomID::in_posession)
			// gas mask is on
		{
			console.main().print(select(
				"Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n"
				"Het gezwel begint langzaam steeds heftiger te trillen, en langzaam komen overal scheuren in zijn schurfterige huid. "
				"Zijn tentakels komen langzaam met een luid slurpend geluid los van de rotswanden, en hij zakt helemaal in elkaar."
			,
				"When you push the lever down, you see a brown-grey gas spray out of the cartridge.\n"
				"The lump's trembling increases, and cracks start to appear in its scavy skin. "
				"Making a slurping sound, its tentacles start to come loose from the rock walls, and it collapses into a heap."
			));
		}
		else
			// no mask... oops!
		{
			console.main().print(select(
				"Als je op de hendel drukt, zie je een bruingrijs gas uit het patroon spuiten.\n"
				"Je kunt nog zien dat het gezwel langzaam steeds heftiger begint te trillen, voordat je zelf een kloppende hoofdpijn "
				"krijgt en onderuit gaat. Je hebt niets om je tegen het gas te beschermen, en je valt flauw. Na een tijdje kom je weer bij."
			,
				"When you push the lever down, you see a brown-grey gas spray out of the cartridge.\n"
				"You can see that the lump trembling starts to increase, before you are hit by a pounding headache and fall over. "
				"You have nothing to protect against the gas, and you lose consciousness. After a while, you come to."
			));

			core.status.life_points -= 4; //    Serious injury
		}

		core.rooms[RoomID::bat_cave].connections.set(Command::north, RoomID::damnation_cave);
		core.animates[AnimateID::swelling].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print(select(
			"Op het gescheurde lichaam van het gezwel zitten allemaal schimmels. Uit zijn maag kruipen pissebedden en oorkruipers. "
			"Er verspreidt zich een sterke rotlucht, en er ontstaat langzaam een klein slijmplasje."
		,
			"The lump's torn body is covered in fungus. Isopods and earwigs crawl out of its stomach. "
			"A strong smell of rotting emerges, and a small puddle of slime slowly appears."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}