#include "base.h"
#include "console.h"
#include "animates.h"

Teleporter::Teleporter(RoomID room) : Animate(room) {}

bool Teleporter::progress_status(CoreData& core)
{
	console.main().print(select(
		"Als je deze grot binnenloopt zie je een aantal pulserende lampen aan het plafond en tegen een van de wanden "
		"een enorm apparaat met een aantal bedieningspanelen en beeldschermen.\n"
		"Terwijl je ernaartoe loopt om het beter te bekijken struikel je over een pedaal in de grond, waarna een sirene begint te loeien. "
		"Van de schrik blijf je liggen, en je ziet dat de lampen aan het plafond feller gaan branden en er grote hoeveelheden data over de "
		"beeldschermen flitsen. Even later zie je een oogverblindende flits en voel je je even gewichtloos.\n"
		"Als je weer kunt zien, merk je dat de lampen en de machine zijn verdwenen.\n"
		"Sterker nog, je ligt buiten..."
	,
		"When you walk into this cave, you see a number of pulsating lights on the ceiling. Against one of the walls, "
		"there's an enormous machine with a number of control panels and displays.\n"
		"As you walk over there to take a better look, you trip over a pedal in the floor, after which a siren stars wailing. "
		"Overcome by fear you stay down, and you see that the lights on the ceiling start burning brighter and large amounts of data flash "
		"across the computer screens. Then you see a blinding flash and you feel weightless for a moment.\n"
		"When you can see again, you notice that the lights and the machine have disappeared.\n"
		"More so, you're outside..."
	));
	console.main().empty_line();

	core.status.current_room = RoomID::forest1;

	return false;
}