#include "base.h"
#include "console.h"
#include "gamedata.h"
#include "general.h"
#include <iostream>

namespace general
{
	void force_exit(Language language)
	{
		console.main().wait_for_key(true, language);

		game_data::remove();
		console.main().clear();
		console.release();

		exit(0);
	}

	void show_arguments()
	{
		std::cout << "R136\n";
		std::cout << '\n';
		std::cout << "Opties (English below):\n";
		std::cout << "-e, --engels     : Speel R136 in het Engels\n";
		std::cout << "-n, --nederlands : Speel R136 in het Nederlands (standaard)\n";
		std::cout << "-h, --help       : Toon deze helptekst\n";
		std::cout << '\n';
		std::cout << "Arguments:\n";
		std::cout << "-d, --dutch      : Play R136 in the Dutch language (default)\n";
		std::cout << "-e, --english    : Play R136 in the English language\n";
		std::cout << "-h, --help       : Show this help text\n";

		exit(0);
	}
}