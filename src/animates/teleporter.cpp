#include "base.h"
#include "console.h"
#include "animates.h"

Teleporter::Teleporter(RoomID room) : Animate(room) {}

bool Teleporter::progress_status(CoreData& core)
{
	console.main().print("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het plafond en tegen een van de wanden "
		"een enorm apparaat met een aantal bedieningspanelen en beeldschermen.\n"
		"Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal in de grond, waarna een sirene begint te loeien. "
		"Van de schrik blijf je liggen, en je ziet dat de lampen aan het plafond feller gaan branden en er grote hoeveelheden data over de "
		"beeldschermen flitsen. Even later zie je een oogverblindende flits en voel je je even gewichtloos.\n"
		"Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\n"
		"Sterker nog, je ligt buiten...");
	console.main().empty_line();

	core.status.current_room = RoomID::forest1;

	return false;
}