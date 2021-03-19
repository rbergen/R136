#include "base.h"
#include "console.h"
#include "animates.h"

GreenCrystal::GreenCrystal(RoomID room) : Animate(room) {}

bool GreenCrystal::progress_status(CoreData& core)
{
	if (core.animates[AnimateID::green_crystal].status == AnimateStatus::initial)
	{
		console.main().print(L"Je struikelt over iets. Door de begroeïing zie je niet wat het is.");
		console.main().empty_line();
	}

	return true;
}