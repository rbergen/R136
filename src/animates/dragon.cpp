#include "base.h"
#include "console.h"
#include "animates.h"

Dragon::Dragon(RoomID room) : Animate(room) {}

bool Dragon::progress_status(CoreData& core)
{
	switch (core.animates[AnimateID::dragon].status)
	{
	case AnimateStatus::initial:
		console.main().print(select(
			"In deze grot bevindt zich een grote draak. Hij heeft meerdere koppen, die je allemaal bespieden met gele oogjes. "
			"Zijn hele huid is bedekt met schimmel, en uit zijn bekken hangen lange, bruine tongen, waar een bijtend zuur af druppelt. "
			"Opeens komt uit een van de bekken een rommelend geluid. Met moeite versta je \"Ben jij een koekie?\""
		,
			"A large dragon resides in this cave. It has multiple heads, each of which watch you with yellow eyes. "
			"It's entire skin is covered in mold, and from its mouths hang long, brown tongues, from which a biting acid drips. ",
			"Suddenly, a rumbling noise comes from one of the mouths. With difficulty you make out \"Are you a cookie?\""
		));

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_1:
		console.main().print(select(
			"De koppen van de draak bewegen nu agressiever heen en weer en beginnen hevig te snuiven.\n"
			"De lucht uit de drakekoppen ruikt afgrijselijk, en je slaat achterover van walging. Een van de bekken spert zich wijd open, en harder dan eerst klinkt "
			"\"BEN JIJ EEN KOEKIE?!?\""
		,
			"The heads of the dragon are now moving more agressively and start to puff heavily.\n"
			"The air from the dragon heads smells awful, and you bounce back of disgust. One of the mouths open wide, and louder than before it sounds "
			"\"ARE YOU A COOKIE?!?\""
		));

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_2:
		console.main().print(select(
			"De draak heft langzaam een van zijn gore poten op, en geeft opeens een ontzettende harde klap. Er kraakt iets in je hoofd, "
			"en een duizeling maakt zich van je meester. Hij maakt aanstalten je nog een klap te verkopen."
		,
			"The dragon slowly lifts one of its filthy legs, and suddenly strikes hard. Something in your head crunches, and dizziness takes you. "
			"The dragon gets ready to hit you again."
		));

		core.status.life_points--; //   Wond

		break;

	case AnimateStatus::cookie_is_thrown:
		console.main().print(select(
			"De draak grijpt het koekje, en steekt hem gelijk in een van zijn grote bekken.\n"
			"Langzaam begint hij te wankelen, en met een doffe dreun klapt hij op de grond.\n"
			"Uit de bek waar juist het koekje in verdween druipt wat kwijl. De draak slaapt."
		,
			"The dragon grabs the cookie, and instantly sticks it in of its large mouths.\n"
			"Slowly it starts to wobble, and with a muted thump it slams to the ground.\n"
			"A little drool runs from the mouth in which the cooky just disappeared. The dragon sleeps."
		));

		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::sleeping_lightly:
		console.main().print(select(
			"De draak slaapt onrustig. Soms beweegt een van zijn koppen iets, en uit zijn lijf klinkt een diep gegrom."
		,
			"The dragon sleeps restlessly. Sometimes, one of its heads moves slightly, and a deep growl emerges from its body."
		));

		break;

	case AnimateStatus::nightcap_on_head:
		console.main().print(select(
			"Voorzichtig zet je de draak de slaapmuts op. De vrolijke kleuren van de muts steken af tegen de beschimmelde huid, "
			"en de muts zakt iets scheef. Op een ge geven moment valt er iets, en het klettert tegen de harde rotsvloer."
		,
			"Carefully, you put the nightcap on the dragon. The happy colours of the cap stand out against the molded skin, "
			"and the cap slides to the side a litte. Suddenly something falls, and it clatters on the hard rock floor."
		));

		core.items[ItemID::gas_capsule].room = core.status.current_room;
		core.animates[AnimateID::dragon].status++;

		break;

	case AnimateStatus::status_6:

		console.main().print(select("De draak slaapt rustig.", "The dragon sleeps peacefully."));

		break;

	default:
		return true;
	}

	console.main().empty_line();
	return true;
}