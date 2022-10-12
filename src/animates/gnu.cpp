#include "base.h"
#include "console.h"
#include "animates.h"

Gnu::Gnu(RoomID room) : Animate(room) {}

bool Gnu::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::gnu].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aankijkt. "
			"Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende beestjes, die je nog nooit eerder gezien hebt. "
			"Het beest verspreidt een afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe."
		,
			"There is a big, hairy gnu here, that looks at you with two sneaky eyes. "
			"Between the hairs of its fur there are all kinds of small creeping creatures that you have never seen before. "
			"A horrible smell comes off the beast. Drooling and puffing heavily, it approaches you."
		));

		core.animates[AnimateID::gnu].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print(select(
			"De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je hebt het gevoel alsof je longen uit je lijf worden geperst. "
			"Versuft sta je weer op."
		,
			"The gnu takes a leap and thrusts its large head hard into your stomach. You feel like your lungs are being pressed out of your body. "
			"Dazed, you get back on your feet."
		));

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::poisonous_meat_fed:
		console.main().print(select(
			L"De gnoe ziet het vlees, snuffelt er aan, en slokt het in één hap naar binnen.\n"
			 "Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar buiten. Hij zakt in elkaar en blijft roerloos liggen."
		,
			L"The gnu sees the meat, sniffs it and gobbles it up in one go.\n"
			 "You see it swell up slowly and its brains come out through its eye sockets. It collapses and remains completely still."
		));

		core.animates[AnimateID::gnu].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print(select(
			"Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er als een papje naast."
		,
			"The bobbed body of the gnu are on the floor, with its brains forming a puddle next to it."
		));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}