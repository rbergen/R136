#include "r136.h"

#define BLOCK_ROW_COUNT	8

const wchar_t* spider[2][BLOCK_ROW_COUNT] = { {
	L"  ▄▄▄        ▄ █ ▄        ▄▄▄  ",
	L" ▄▀  ▀▀▄▄  ▄▀ ▀█▀ ▀▄  ▄▄▀▀  ▀▄ ",
	L"▄█ ▄▄▄▄  ███ ▀ ▄ ▀ ███  ▄▄▄▄ █▄",
	L"   █   ▀▀████▄███▄████▀▀   █   ",
	L" ▄█    ▄▄▄▀█████████▀▄▄▄    █▄ ",
	L"   ▄▀▀▀                 ▀▀▀▄   ",
	L"  █                         █  ",
	L" ▀▀                         ▀▀ ",
}, {
	L"               █               ",
	L"  █▀▀▄▄     ▄▀▄█▄▀▄     ▄▄▀▀█  ",
	L" █     ▀▀▄▄█ ▄ ▀ ▄ █▄▄▀▀     █ ",
	L"▀▀ █▀▀▀▄▄███▄ ▄█▄ ▄███▄▄▀▀▀█ ▀▀",
	L"  ▄▀     ▀███████████▀     ▀▄  ",
	L" ▀▀ ▄▄▄▀▀▀ ▀▀▀▀▀▀▀▀▀ ▀▀▀▄▄▄ ▀▀ ",
	L"  ▄▀                       ▀▄  ",
	L" ▄█                         █▄ "
} };

#define SPIDER_UPPER		0
#define SPIDER_LOWER		1
#define SPIDER_DROPHEIGHT	13
#define SPIDER_WIDTH		31

const wchar_t* linesection = L"               █               ";
const wchar_t* clearspiderspaces = L"                               ";

const wchar_t* letters[3][BLOCK_ROW_COUNT] = { {
	L"█▀▀▀▀▀▀▀▀▀▀▄",
	L"█          █",
	L"█          █",
	L"█▄▄▄▄▄▄▄▄▄▄▀",
	L"█     ▀▄    ",
	L"█       ▀▄  ",
	L"█         ▀▄",
	L"            "
}, {
	L"█▀▀▀▀▀▀▀▀▀▀▄",
	L"█          █",
	L"█          █",
	L"█▄▄▄▄▄▄▄▄▄▄▀",
	L"█           ",
	L"█           ",
	L"█           ",
	L"            "
}, {
	L"▄▄▄▄▄▄▄▄▄▄▄ ",
	L"█          █",
	L"█          █",
	L"█          █",
	L"█▀▀▀▀▀█▀▀▀▀ ",
	L"█      ▀▄   ",
	L"█        ▀▄ ",
	L"▀          ▀"
} };

const wchar_t* clearleftletterspaces = L"            ";
const wchar_t* clearrightletterspaces = L"                    ";

#define LETTER_R			0
#define LETTER_P			1
#define LETTER_R_LOW		2
#define LETTER_WIDTH		12
#define LETTER_SPACEWIDTH	6

const wchar_t* verticalspace[BLOCK_ROW_COUNT] =
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

const wchar_t* digits[BLOCK_ROW_COUNT] = {
	L"▄█   ▄▀▀▀▀▀▄   ▄▀▀▀▀▀▄",
	L" █         █   █      ",
	L" █         █   █      ",
	L" █    ▀▀▀▀▀▄   █▀▀▀▀▀▄",
	L" █         █   █     █",
	L" █         █   █     █",
	L" █   ▀▄▄▄▄▄▀   ▀▄▄▄▄▄▀",
	L"                      "
};

#define DIGITS_WIDTH	22

void LowerSpider(int spiderx)
{
	int spiderbottomy, spiderrightx, dropindex, spiderswitch;

	spiderbottomy = BLOCK_ROW_COUNT - 1;
	spiderrightx = SPIDER_WIDTH - 1;

	// Introduce the spider from the top of the screen
	for (dropindex = BLOCK_ROW_COUNT; dropindex > 0; dropindex--)
	{
		for (spiderswitch = 0; spiderswitch < 2; spiderswitch++)
		{
			print_fullscreen_block_section(0, spiderx, Color::inverse, spider[spiderswitch], dropindex - 1, 0, spiderbottomy, spiderrightx);

			update_fullscreen();
			sleep_ms(50);
		}
	}

	// Lower it to its final place, leaving a silk thread
	for (dropindex = 0; dropindex < SPIDER_DROPHEIGHT; dropindex++)
	{
		print_fullscreen(dropindex, spiderx, Color::inverse, linesection);

		for (spiderswitch = 0; spiderswitch < 2; spiderswitch++)
		{
			print_fullscreen_block(dropindex + 1, spiderx, Color::inverse, spider[spiderswitch], BLOCK_ROW_COUNT);

			update_fullscreen();
			sleep_ms(50);
		}
	}
}

void SwoopInLetters(int screenrightx, int screenmiddlex, int leftletterfinalx)
{
	int flowindex, rightletterfirstx;
	int letterbottomy = BLOCK_ROW_COUNT - 1;
	int letterrightx = LETTER_WIDTH - 1;

	// Introduce letters from either side of the screen
	for (flowindex = 0; flowindex < LETTER_WIDTH; flowindex++)
	{
		print_fullscreen_block_section(2, 0, Color::inverse, letters[LETTER_R], 0, letterrightx - flowindex, letterbottomy, letterrightx);
		print_fullscreen_block_section(2, screenrightx - flowindex, Color::inverse, letters[LETTER_P], 0, 0, letterbottomy, flowindex);

		update_fullscreen();
	}

	rightletterfirstx = screenrightx - LETTER_WIDTH;

	// Bring the letters to the center
	for (flowindex = 0; flowindex < leftletterfinalx; flowindex++)
	{
		print_fullscreen_block(2, flowindex, Color::inverse, verticalspace, BLOCK_ROW_COUNT);
		print_fullscreen_block(2, flowindex + 1, Color::inverse, letters[LETTER_R], BLOCK_ROW_COUNT);

		print_fullscreen_block(2, rightletterfirstx - flowindex, Color::inverse, letters[LETTER_P], BLOCK_ROW_COUNT);
		print_fullscreen_block(2, screenrightx - flowindex, Color::inverse, verticalspace, BLOCK_ROW_COUNT);

		update_fullscreen();
	}

	// If the silk thread is just left of center due to screen width, bump the P one more place to the left
	if ((screenrightx % 2) == 0)
	{
		print_fullscreen_block(2, rightletterfirstx - flowindex, Color::inverse, letters[LETTER_P], BLOCK_ROW_COUNT);
		print_fullscreen_block(2, screenrightx - flowindex, Color::inverse, verticalspace, BLOCK_ROW_COUNT);

		update_fullscreen();
	}

	// Cut the silk thread to create the letter I
	print_fullscreen(1, screenmiddlex, Color::inverse, L"▀");
	print_fullscreen(1 + BLOCK_ROW_COUNT, screenmiddlex, Color::inverse, L"▄");

	update_fullscreen();
}

void SwoopInDigits(int screenbottomy, int screenrightx, int screenmiddlex, int spiderx, int leftletterfinalx)
{
	int flowindex, digitsfinalx, digitsbottomy;

	int letterstopy = (screenbottomy - BLOCK_ROW_COUNT) / 2;
	if (letterstopy < 2)
		letterstopy = 2;

	// clear everything except for the R
	print_fullscreen(0, screenmiddlex, Color::inverse, L" ");
	print_fullscreen(1, screenmiddlex, Color::inverse, L" ");
	for (int i = 2; i < 2 + BLOCK_ROW_COUNT; i++)
	{
		print_fullscreen(i, screenmiddlex, Color::inverse, clearrightletterspaces);
	}

	for (int i = 2 + BLOCK_ROW_COUNT; i < SPIDER_DROPHEIGHT; i++)
	{
		print_fullscreen(i, screenmiddlex, Color::inverse, L" ");
	}

	for (int i = SPIDER_DROPHEIGHT; i < SPIDER_DROPHEIGHT + BLOCK_ROW_COUNT; i++)
	{
		print_fullscreen(i, spiderx, Color::inverse, clearspiderspaces);
	}

	// Lower the R to the vertical middle of the screen
	for (int i = 2; i < letterstopy; i++)
	{
		print_fullscreen_block(i, leftletterfinalx, Color::inverse, letters[LETTER_R_LOW], BLOCK_ROW_COUNT);

		update_fullscreen();
		sleep_ms(5);

		print_fullscreen(i, leftletterfinalx, Color::inverse, clearleftletterspaces);
		print_fullscreen_block(i + 1, leftletterfinalx, Color::inverse, letters[LETTER_R], BLOCK_ROW_COUNT);

		update_fullscreen();
		sleep_ms(5);
	}

	digitsfinalx = leftletterfinalx + LETTER_WIDTH + 3;
	digitsbottomy = BLOCK_ROW_COUNT - 1;

	// Introduce the digits from the right-hand side of the screen
	for (flowindex = 0; flowindex < DIGITS_WIDTH; flowindex++)
	{
		print_fullscreen_block_section(letterstopy, screenrightx - flowindex, Color::inverse_red, digits, 0, 0, digitsbottomy, flowindex);

		update_fullscreen();
	}

	// Bring the digits to the center
	for (flowindex = screenrightx - DIGITS_WIDTH; flowindex >= digitsfinalx; flowindex--)
	{
		print_fullscreen_block(letterstopy, flowindex, Color::inverse_red, digits, BLOCK_ROW_COUNT);
		print_fullscreen_block(letterstopy, flowindex + DIGITS_WIDTH, Color::inverse_red, verticalspace, BLOCK_ROW_COUNT);

		update_fullscreen();
	}
}

void RunIntro()
{
	int screenbottomy, screenrightx, screenmiddlex;
	int spiderx, leftletterfinalx;

	get_fullscreen_size(screenbottomy, screenrightx);
	screenrightx--;

	clear_fullscreen(Color::inverse);

	spiderx = (screenrightx - SPIDER_WIDTH) / 2;

	LowerSpider(spiderx);

	leftletterfinalx = screenrightx / 2 - LETTER_WIDTH - LETTER_SPACEWIDTH;

	screenmiddlex = screenrightx / 2;
	if ((screenrightx % 2) == 0)
		screenmiddlex--;

	SwoopInLetters(screenrightx, screenmiddlex, leftletterfinalx);

	sleep_ms(2000);

	SwoopInDigits(screenbottomy, screenrightx, screenmiddlex, spiderx, leftletterfinalx);

	sleep_ms(2500);

	clear_fullscreen(Color::normal);
}

