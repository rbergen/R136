﻿#include "base.h"
#include "console.h"
#include "general.h"
#include "startup.h"

namespace startup
{
	namespace {
		constexpr char block_row_count = 8;

		const wstring spider[2][block_row_count] =
		{
			{
				L"  ▄▄▄        ▄ █ ▄        ▄▄▄  ",
				L" ▄▀  ▀▀▄▄  ▄▀ ▀█▀ ▀▄  ▄▄▀▀  ▀▄ ",
				L"▄█ ▄▄▄▄  ███ ▀ ▄ ▀ ███  ▄▄▄▄ █▄",
				L"   █   ▀▀████▄███▄████▀▀   █   ",
				L" ▄█    ▄▄▄▀█████████▀▄▄▄    █▄ ",
				L"   ▄▀▀▀                 ▀▀▀▄   ",
				L"  █                         █  ",
				L" ▀▀                         ▀▀ ",
			},
			{
				L"               █               ",
				L"  █▀▀▄▄     ▄▀▄█▄▀▄     ▄▄▀▀█  ",
				L" █     ▀▀▄▄█ ▄ ▀ ▄ █▄▄▀▀     █ ",
				L"▀▀ █▀▀▀▄▄███▄ ▄█▄ ▄███▄▄▀▀▀█ ▀▀",
				L"  ▄▀     ▀███████████▀     ▀▄  ",
				L" ▀▀ ▄▄▄▀▀▀ ▀▀▀▀▀▀▀▀▀ ▀▀▀▄▄▄ ▀▀ ",
				L"  ▄▀                       ▀▄  ",
				L" ▄█                         █▄ "
			}
		};

		constexpr char spider_upper = 0;
		constexpr char spider_lower = 1;
		constexpr char spider_drop_height = 13;
		const int spider_width = (int)spider[0][0].size();

		const wstring line_section = L"               █               ";
		const wstring clear_spider_spaces = L"                               ";

		const wstring letters[3][block_row_count] =
		{
			{
				L"█▀▀▀▀▀▀▀▀▀▀▄",
				L"█          █",
				L"█          █",
				L"█▄▄▄▄▄▄▄▄▄▄▀",
				L"█     ▀▄    ",
				L"█       ▀▄  ",
				L"█         ▀▄",
				L"            "
			},
			{
				L"█▀▀▀▀▀▀▀▀▀▀▄",
				L"█          █",
				L"█          █",
				L"█▄▄▄▄▄▄▄▄▄▄▀",
				L"█           ",
				L"█           ",
				L"█           ",
				L"            "
			},
			{
				L"▄▄▄▄▄▄▄▄▄▄▄ ",
				L"█          █",
				L"█          █",
				L"█          █",
				L"█▀▀▀▀▀█▀▀▀▀ ",
				L"█      ▀▄   ",
				L"█        ▀▄ ",
				L"▀          ▀"
			}
		};

		const wstring clear_left_letter_spaces = L"            ";
		const wstring clear_right_letter_spaces = L"                    ";

		constexpr char letter_r = 0;
		constexpr char letter_p = 1;
		constexpr char letter_r_low = 2;
		const int letter_width = (int)letters[0][0].size();
		constexpr char letter_space_width = 6;

		const wstring vertical_space[block_row_count] =
		{
			L" ",
			L" ",
			L" ",
			L" ",
			L" ",
			L" ",
			L" ",
			L" "
		};

		const wstring digits[block_row_count] =
		{
			L"▄█   ▄▀▀▀▀▀▄   ▄▀▀▀▀▀▄",
			L" █         █   █      ",
			L" █         █   █      ",
			L" █    ▀▀▀▀▀▄   █▀▀▀▀▀▄",
			L" █         █   █     █",
			L" █         █   █     █",
			L" █   ▀▄▄▄▄▄▀   ▀▄▄▄▄▄▀",
			L"                      "
		};

		const int digits_width = (int)digits[0].size();

		void lower_spider(int spider_x)
		{
			int spider_bottom_y = block_row_count - 1;
			int spider_right_x = spider_width - 1;

			// Introduce the spider from the top of the screen
			for (int drop_index = block_row_count; drop_index > 0; drop_index--)
			{
				for (int spider_switch = 0; spider_switch < 2; spider_switch++)
				{
					console.fullscreen().print(0, spider_x, Color::inverse, spider[spider_switch], drop_index - 1, 0, spider_bottom_y, spider_right_x);
					console.fullscreen().refresh();

					general::sleep_ms(50);
				}
			}

			// Lower it to its final place, leaving a silk thread
			for (int drop_index = 0; drop_index < spider_drop_height; drop_index++)
			{
				console.fullscreen().print(drop_index, spider_x, Color::inverse, line_section);

				for (int spider_switch = 0; spider_switch < 2; spider_switch++)
				{
					console.fullscreen().print(drop_index + 1, spider_x, Color::inverse, spider[spider_switch], block_row_count);

					console.fullscreen().refresh();
					general::sleep_ms(50);
				}
			}
		}

		void swoop_in_letters(int screen_right_x, int screen_middle_x, int left_letter_final_x)
		{
			int letter_bottom_y = block_row_count - 1;
			int letter_right_x = letter_width - 1;

			// Introduce letters from either side of the screen
			for (int flow_index = 0; flow_index < letter_width; flow_index++)
			{
				console.fullscreen().print(2, 0, Color::inverse, letters[letter_r], 0, letter_right_x - flow_index, letter_bottom_y, letter_right_x);
				console.fullscreen().print(2, screen_right_x - flow_index, Color::inverse, letters[letter_p], 0, 0, letter_bottom_y, flow_index);

				console.fullscreen().refresh();
			}

			int right_letter_first_x = screen_right_x - letter_width;

			int flow_index;

			// Bring the letters to the center
			for (flow_index = 0; flow_index < left_letter_final_x; flow_index++)
			{
				console.fullscreen().print(2, flow_index, Color::inverse, vertical_space, block_row_count);
				console.fullscreen().print(2, flow_index + 1, Color::inverse, letters[letter_r], block_row_count);

				console.fullscreen().print(2, right_letter_first_x - flow_index, Color::inverse, letters[letter_p], block_row_count);
				console.fullscreen().print(2, screen_right_x - flow_index, Color::inverse, vertical_space, block_row_count);

				console.fullscreen().refresh();
			}

			// If the silk thread is just left of center due to screen width, bump the P one more place to the left
			if ((screen_right_x % 2) == 0)
			{
				console.fullscreen().print(2, right_letter_first_x - flow_index, Color::inverse, letters[letter_p], block_row_count);
				console.fullscreen().print(2, screen_right_x - flow_index, Color::inverse, vertical_space, block_row_count);

				console.fullscreen().refresh();
			}

			// Cut the silk thread to create the letter I
			console.fullscreen().print(1, screen_middle_x, Color::inverse, L"▀");
			console.fullscreen().print(1 + block_row_count, screen_middle_x, Color::inverse, L"▄");

			console.fullscreen().refresh();
		}

		void swoop_in_digits(int screen_bottom_y, int screen_right_x, int screen_middle_x, int spider_x, int left_letter_final_x)
		{
			int letters_top_y = (screen_bottom_y - block_row_count) / 2;
			if (letters_top_y < 2)
				letters_top_y = 2;

			// clear everything except for the R
			console.fullscreen().print(0, screen_middle_x, Color::inverse, L" ");
			console.fullscreen().print(1, screen_middle_x, Color::inverse, L" ");
			for (int i = 2; i < 2 + block_row_count; i++)
			{
				console.fullscreen().print(i, screen_middle_x, Color::inverse, clear_right_letter_spaces);
			}

			for (int i = 2 + block_row_count; i < spider_drop_height; i++)
			{
				console.fullscreen().print(i, screen_middle_x, Color::inverse, L" ");
			}

			for (int i = spider_drop_height; i < spider_drop_height + block_row_count; i++)
			{
				console.fullscreen().print(i, spider_x, Color::inverse, clear_spider_spaces);
			}

			// Lower the R to the vertical middle of the screen
			for (int i = 2; i < letters_top_y; i++)
			{
				console.fullscreen().print(i, left_letter_final_x, Color::inverse, letters[letter_r_low], block_row_count);

				console.fullscreen().refresh();
				general::sleep_ms(5);

				console.fullscreen().print(i, left_letter_final_x, Color::inverse, clear_left_letter_spaces);
				console.fullscreen().print(i + 1, left_letter_final_x, Color::inverse, letters[letter_r], block_row_count);

				console.fullscreen().refresh();
				general::sleep_ms(5);
			}

			int digits_final_x = left_letter_final_x + letter_width + 3;
			int digits_bottom_y = block_row_count - 1;

			// Introduce the digits from the right-hand side of the screen
			for (int flow_index = 0; flow_index < digits_width; flow_index++)
			{
				console.fullscreen().print(letters_top_y, screen_right_x - flow_index, Color::inverse_red, digits, 0, 0, digits_bottom_y, flow_index);

				console.fullscreen().refresh();
			}

			// Bring the digits to the center
			for (int flow_index = screen_right_x - digits_width; flow_index >= digits_final_x; flow_index--)
			{
				console.fullscreen().print(letters_top_y, flow_index, Color::inverse_red, digits, block_row_count);
				console.fullscreen().print(letters_top_y, flow_index + digits_width, Color::inverse_red, vertical_space, block_row_count);

				console.fullscreen().refresh();
			}
		}
	}

	void run_intro()
	{
		CursorType cursor = console.get_cursor();
		console.set_cursor(CursorType::off);

		int screen_bottom_y, screen_right_x;

		console.fullscreen().get_size(screen_bottom_y, screen_right_x);
		screen_right_x--;

		console.fullscreen().clear(Color::inverse);

		int spider_x = (screen_right_x - spider_width) / 2;

		lower_spider(spider_x);

		int left_letter_final_x = screen_right_x / 2 - letter_width - letter_space_width;

		int screen_middle_x = screen_right_x / 2;
		if ((screen_right_x % 2) == 0)
			screen_middle_x--;

		swoop_in_letters(screen_right_x, screen_middle_x, left_letter_final_x);

		general::sleep_ms(2000);

		swoop_in_digits(screen_bottom_y, screen_right_x, screen_middle_x, spider_x, left_letter_final_x);

		general::sleep_ms(2500);

		console.fullscreen().clear(Color::normal);
		console.process_resize();

		console.set_cursor(cursor);
	}

	void show_splashscreen(CoreData& core)
	{
		console.main().clear();

		console.main().set_attribute(A_BOLD);
		console.main().print_centered("*** R136 ***");
		console.main().empty_line();

		console.main().set_attribute(A_UNDERLINE);
		console.main().print_centered(select("Ontwerp", "Design"));
		console.main().unset_attribute(A_BOLD | A_UNDERLINE);
		console.main().end_line();

		console.main().print_centered("Peter Wouda");
		console.main().end_line();
		console.main().print_centered("Rutger van Bergen");
		console.main().empty_line();

		console.main().set_attribute(A_BOLD | A_UNDERLINE);
		console.main().print_centered("Code");
		console.main().unset_attribute(A_BOLD | A_UNDERLINE);
		console.main().end_line();

		console.main().print_centered("Rutger van Bergen");
		console.main().empty_line();

		console.main().set_attribute(A_BOLD | A_UNDERLINE);
		console.main().print_centered(select("Testen", "Testing"));
		console.main().unset_attribute(A_BOLD | A_UNDERLINE);
		console.main().end_line();

		console.main().print_centered("Machiel Keizer");
		console.main().end_line();
		console.main().print_centered("Peter Wouda");
		console.main().end_line();
		console.main().print_centered("Rutger van Bergen");
		console.main().end_line();
		console.main().empty_line();

		console.main().set_attribute(A_BOLD);
		console.main().print_centered(select("Versie 3.4.2, (C) 1998, 2023 R.I.P.", "Version 3.4.2, (C) 1998, 2023 R.I.P."));
		console.main().unset_attribute(A_BOLD);
		console.main().empty_line();
	}

	void show_start_message(CoreData &core)
	{
		console.main().clear();

		console.main().print(select(
			"Terwijl je op het punt staat je avontuur te beginnen, denk je nog even na over waarom je hier, in deze verlaten, "
			"neertroostige omgeving staat."
		,
			"As you're about to start your adventure, you think back to why you are here, standing in this desolate, "
			"depressing environment."
		));
		console.main().empty_line();
		console.main().print(select(
			"Het verhaal begint op het moment dat je met drie andere wetenschappers een project begon over straling. "
			"In een vergevorderd stadium van het onderzoek werd er een fout gemaakt. In plaats van de gebruikelijke stoffen werden er andere, "
			"agressievere in de kernsplitser gebracht.\n"
		,
			"The story starts when you joined a radiation-related project with three other scientists. In an advanced stage of the research, "
			"a mistake was made. Instead of the usual matter, a different, more agressive one was introduced into the fission reactor.\n"
		));
		console.main().print(select(
			L"Het resultaat was even interessant als bedreigend: er ontstond een nieuwe straling, de positronenstraling. Deze straling heft elektronen "
			"op waardoor stoffen compleet in het niets verdwijnen. Een bepaald gedeelte van de reactor loste dan ook op in de lucht, en net op tijd "
			"kon een wereldramp voorkomen worden door het heldhaftig optreden van één van je collega's.\n"
		,
			L"The result was as interesting as it was threatening: a new radiation occurred, being positron radiation. This radiation dissolves electrons, "
			"due to which matter it comes in contact with completely dissolves into nothing. Part of the reactor dissolved into thin air, and a global "
			"catastrophy could just be avoided by the heroic intervention of one of your colleagues.\n"
		));
		console.main().print(select(
			"De betreffende wetenschapper werd even blootgesteld aan de straling, en na het gebeuren zonderde hij zich af."
		,
			"The scientist in question was briefly exposed to the radiation, and he isolated himself after the event."
		));
		console.main().empty_line();
		console.main().print(select(
			"Geschrokken door wat er gebeurde werd er besloten alles geheim te houden en het project te stoppen.\n"
			"De wetenschapper die aan de straling was blootgesteld hield zich niet aan de afspraak en stal wat van de agressieve stof. "
			"Hij bouwde een bom, de positronenbom genaamd."
		,
			"Shocked by what happened, it was decided to keep everything a secret and end the project.\n"
			"The scientist who was exposed to the radiation did not stick to the agreement, and stole some of the aggressive matter. "
			"He built a new kind of bomb, a positron bomb."
		));

		console.main().wait_for_key(true, core.language);
		console.main().clear();

		console.main().print(select(
			"Hij vond dat de wereld de schuld had van zijn mutaties en hij wilde de wereld daarvoor laten boeten. "
			"Daarom verborg hij de bom, met een tijdmechanisme op een plaats die niemand zou durven betreden; de vallei der verderf."
		,
			"It was his opinion that the world was to blame for his mutations, and he wanted the world to pay for it. "
			"For that reason he hid the bomb with a time mechanism, in a place no one would dare to enter: the valley of perdition."
		));
		console.main().empty_line();
		console.main().print(select(
			L"Eén van de wetenschappers rook onraad en wilde de zaak gaan onderzoeken.\n"
		,
			L"One of the scientists suspected malice and wanted to investigate the matter.\n"
		));
		console.main().print(select(
			"Drie dagen later werd hij met een vleesmes in zijn rug op de stoep van zijn huis gevonden.\n"
			"Toen zijn huis werd doorzocht stootte men op twee dingen: de plaats waar de bom lag en licht radioactieve voetstappen.\n"
			"Jij en je collega begrepen wat er aan de hand was, en jullie besloten dat er moest worden ingegrepen. Aangezien je niet echt een held bent, "
			"werd er besloten dat de andere wetenschapper op pad zou gaan. Jij zou achterblijven om zijn reis te coördineren via een geheime radiofrequentie.\n"
			"Je hebt nooit meer iets van hem gehoord."
		,
			"Three days later, he was found in front of his house with a butcher's knife in his back.\n"
			"When his house was searched, two things were found: the location of the bomb, and low-level radioactive footsteps.\n"
			"Your colleague and you understood what was going on, and you decided that it was necessary to intervene. Because you're not really a hero, "
			"it was decided that the other scientist would make the trip. You would stay behind to coordinate his travels via a secret radio frequency.\n"
			"You never heard from him again."
		));
		console.main().empty_line();
		console.main().print(select("Nu ben jij aan de beurt.", "Now it's your turn."));
		console.main().empty_line();
		console.main().print(select(
			"Je staat op de trap die naar de vallei leidt. Rechts van je staat een verweerd bordje: \"Betreden op eigen risico\". "
		,
			"You're on the stairs that lead to the valley. A weathered sign stands to the right of you: \"Enter at your own risk\". "
		));
		console.main().print(select(
			L"Je kijkt nog één keer achterom, en met trillende benen loop je naar beneden..."
		,
			L"You look back one more time, and walk down with trembling legs..."
		));

		console.main().wait_for_key(true, core.language);
		console.main().clear();

		console.main().print("Type h voor help. / Type h for help.");
		console.main().empty_line();
	}
}
