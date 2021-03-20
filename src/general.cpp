#include "base.h"
#include "console.h"
#include "gamedata.h"
#include "general.h"

namespace general
{
	void force_exit(void)
	{
		console.main().wait_for_key(true);

		game_data::remove();
		console.main().clear();
		console.release();

		exit(0);
	}
}