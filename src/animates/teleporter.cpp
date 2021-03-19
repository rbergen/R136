#include "base.h"
#include "console.h"
#include "animates.h"

Teleporter::Teleporter(RoomID room) : Animate(room) {}

bool Teleporter::progress_status(CoreData& core)
{
	console.main().print("Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het\n");
	console.main().print("plafond en tegen een van de wanden een enorm apparaat met een aantal\n");
	console.main().print("bedieningspanelen en beeldschermen.\n");
	console.main().print("Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal\n");
	console.main().print("in de grond, waarna een sirene begint te loeien. Van de schrik blijf je liggen,\n");
	console.main().print("en je ziet dat de lampen aan het plafond feller gaan branden en er grote\n");
	console.main().print("hoeveelheden data over de beeldschermen flitsen. Even later zie je een\n");
	console.main().print("oogverblindende flits en voel je je even gewichtloos.\n");
	console.main().print("Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\n");
	console.main().print("Sterker nog, je ligt buiten...\n\n");

	core.status.current_room = RoomID::forest1;

	return false;
}