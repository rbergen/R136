#include "base.h"
#include "console.h"
#include "animates.h"

Vacuum::Vacuum(RoomID room) : Animate(room) {}

bool Vacuum::progress_status(CoreData& core)
{
	console.main().print(select(
		"Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een verschrikkelijke pijn kraakt als een bliksem door je lijf. "
		"Je valt naar achteren de grot uit, en daar val je even flauw."
	,
		"Because there is no air in this cave, both your lungs collapse. A horrible pain shoots through you like a lightning bolt. "
		"You fall backwards out of the cave, where you briefly lose consciousness."
	));
	console.main().empty_line();

	core.status.life_points -= 4; //   Levenswond
	core.status.current_room = RoomID::snake_cave; //   Grot terug

	return false;
}