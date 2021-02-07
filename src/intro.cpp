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
			printfsblocksectionat(0, spiderx, COLORS_INVERSE, spider[spiderswitch], dropindex - 1, 0, spiderbottomy, spiderrightx);

			updatefs();
			mssleep(50);
		}
	}

	// Lower it to its final place, leaving a silk thread
	for (dropindex = 0; dropindex < SPIDER_DROPHEIGHT; dropindex++)
	{
		printfsat(dropindex, spiderx, COLORS_INVERSE, linesection);

		for (spiderswitch = 0; spiderswitch < 2; spiderswitch++)
		{
			printfsblockat(dropindex + 1, spiderx, COLORS_INVERSE, spider[spiderswitch], BLOCK_ROW_COUNT);

			updatefs();
			mssleep(50);
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
		printfsblocksectionat(2, 0, COLORS_INVERSE, letters[LETTER_R], 0, letterrightx - flowindex, letterbottomy, letterrightx);
		printfsblocksectionat(2, screenrightx - flowindex, COLORS_INVERSE, letters[LETTER_P], 0, 0, letterbottomy, flowindex);

		updatefs();
	}

	rightletterfirstx = screenrightx - LETTER_WIDTH;

	// Bring the letters to the center
	for (flowindex = 0; flowindex < leftletterfinalx; flowindex++)
	{
		printfsblockat(2, flowindex, COLORS_INVERSE, verticalspace, BLOCK_ROW_COUNT);
		printfsblockat(2, flowindex + 1, COLORS_INVERSE, letters[LETTER_R], BLOCK_ROW_COUNT);

		printfsblockat(2, rightletterfirstx - flowindex, COLORS_INVERSE, letters[LETTER_P], BLOCK_ROW_COUNT);
		printfsblockat(2, screenrightx - flowindex, COLORS_INVERSE, verticalspace, BLOCK_ROW_COUNT);

		updatefs();
	}

	// If the silk thread is just left of center due to screen width, bump the P one more place to the left
	if ((screenrightx % 2) == 0)
	{
		printfsblockat(2, rightletterfirstx - flowindex, COLORS_INVERSE, letters[LETTER_P], BLOCK_ROW_COUNT);
		printfsblockat(2, screenrightx - flowindex, COLORS_INVERSE, verticalspace, BLOCK_ROW_COUNT);

		updatefs();
	}

	// Cut the silk thread to create the letter I
	printfsat(1, screenmiddlex, COLORS_INVERSE, L"▀");
	printfsat(1 + BLOCK_ROW_COUNT, screenmiddlex, COLORS_INVERSE, L"▄");

	updatefs();
}

void SwoopInDigits(int screenbottomy, int screenrightx, int screenmiddlex, int spiderx, int leftletterfinalx)
{
	int flowindex, digitsfinalx, digitsbottomy;

	int letterstopy = (screenbottomy - BLOCK_ROW_COUNT) / 2;
	if (letterstopy < 2)
		letterstopy = 2;

	// clear everything except for the R
	printfsat(0, screenmiddlex, COLORS_INVERSE, L" ");
	printfsat(1, screenmiddlex, COLORS_INVERSE, L" ");
	for (int i = 2; i < 2 + BLOCK_ROW_COUNT; i++)
	{
		printfsat(i, screenmiddlex, COLORS_INVERSE, clearrightletterspaces);
	}

	for (int i = 2 + BLOCK_ROW_COUNT; i < SPIDER_DROPHEIGHT; i++)
	{
		printfsat(i, screenmiddlex, COLORS_INVERSE, L" ");
	}

	for (int i = SPIDER_DROPHEIGHT; i < SPIDER_DROPHEIGHT + BLOCK_ROW_COUNT; i++)
	{
		printfsat(i, spiderx, COLORS_INVERSE, clearspiderspaces);
	}

	// Lower the R to the vertical middle of the screen
	for (int i = 2; i < letterstopy; i++)
	{
		printfsblockat(i, leftletterfinalx, COLORS_INVERSE, letters[LETTER_R_LOW], BLOCK_ROW_COUNT);

		updatefs();
		mssleep(5);

		printfsat(i, leftletterfinalx, COLORS_INVERSE, clearleftletterspaces);
		printfsblockat(i + 1, leftletterfinalx, COLORS_INVERSE, letters[LETTER_R], BLOCK_ROW_COUNT);

		updatefs();
		mssleep(5);
	}

	digitsfinalx = leftletterfinalx + LETTER_WIDTH + 3;
	digitsbottomy = BLOCK_ROW_COUNT - 1;

	// Introduce the digits from the right-hand side of the screen
	for (flowindex = 0; flowindex < DIGITS_WIDTH; flowindex++)
	{
		printfsblocksectionat(letterstopy, screenrightx - flowindex, COLORS_INVERSERED, digits, 0, 0, digitsbottomy, flowindex);

		updatefs();
	}

	// Bring the digits to the center
	for (flowindex = screenrightx - DIGITS_WIDTH; flowindex >= digitsfinalx; flowindex--)
	{
		printfsblockat(letterstopy, flowindex, COLORS_INVERSERED, digits, BLOCK_ROW_COUNT);
		printfsblockat(letterstopy, flowindex + DIGITS_WIDTH, COLORS_INVERSERED, verticalspace, BLOCK_ROW_COUNT);

		updatefs();
	}
}

void RunIntro()
{
	int screenbottomy, screenrightx, screenmiddlex;
	int spiderx, leftletterfinalx;

	getfssize(screenbottomy, screenrightx);
	screenrightx--;

	clrfs(COLORS_INVERSE);

	spiderx = (screenrightx - SPIDER_WIDTH) / 2;

	LowerSpider(spiderx);

	leftletterfinalx = screenrightx / 2 - LETTER_WIDTH - LETTER_SPACEWIDTH;

	screenmiddlex = screenrightx / 2;
	if ((screenrightx % 2) == 0)
		screenmiddlex--;

	SwoopInLetters(screenrightx, screenmiddlex, leftletterfinalx);

	mssleep(2000);

	SwoopInDigits(screenbottomy, screenrightx, screenmiddlex, spiderx, leftletterfinalx);

	mssleep(2500);

	clrfs(COLORS_NORMAL);
}

