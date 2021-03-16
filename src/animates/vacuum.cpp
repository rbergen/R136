#include "r136.h"
#include "animates.h"

Vacuum::Vacuum(RoomID room) : Animate(room) {}

bool Vacuum::progress_status(CoreData& core)
{
	console.main().print("Doordat er in deze grot geen lucht is, klappen allebei je longen dicht. Een\n");
	console.main().print("verschrikkelijke pijn kraakt als een bliksem door je lijf. Je valt naar achte-\n");
	console.main().print("ren de grot uit, en daar val je even flauw.\n\n");

	core.status.life_points -= 4; //   Levenswond
	core.status.current_room = RoomID::snake_cave; //   Grot terug

	return false;
}