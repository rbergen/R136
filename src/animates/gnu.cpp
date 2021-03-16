#include "r136.h"
#include "animates.h"

Gnu::Gnu(RoomID room) : Animate(room) {}

bool Gnu::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::gnu].status)
	{
	case AnimateStatus::initial:
		console.main().print("Er staat hier een grote behaarde gnoe die je met twee geniepige oogjes aan-\n");
		console.main().print("kijkt. Tussen de haren van zijn vacht bevinden zich allerlei kleine kruipende\n");
		console.main().print("beestjes, die je nog nooit eerder gezien hebt. Het beest verspreidt een\n");
		console.main().print("afschuwelijke lucht. Kweilend en zwaar snuivend komt hij langzaam naar je toe.\n\n");

		core.animates[AnimateID::gnu].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print("De gnoe neemt een sprong, en stoot met zijn grote kop hard in je maag. Je\n");
		console.main().print("hebt het gevoel alsof je longen uit je lijf worden geperst. Versuft sta je\n");
		console.main().print("weer op.\n\n");

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::poisonous_meat_fed:
		console.main().write(L"De gnoe ziet het vlees, snuffelt er aan, en slokt het in één hap naar binnen.\n");
		console.main().print("Je ziet hem langzaam opzwellen en zijn hersens komen door zijn oogkassen naar\n");
		console.main().print("buiten. Hij zakt in elkaar en blijft roerloos liggen.\n\n");

		core.animates[AnimateID::gnu].status = AnimateStatus::dead;

		break;

	case AnimateStatus::dead:
		console.main().print("Het bultachtige lichaam van de gnoe ligt op de grond en de hersens liggen er\n");
		console.main().print("als een papje naast.\n\n");

		break;
	}

	return true;
}