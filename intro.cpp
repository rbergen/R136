#include "r136.h"

#define BLOCK_ROW_COUNT	8

const char* spider[2][BLOCK_ROW_COUNT] = { {
	u8"  ▄▄▄        ▄ █ ▄        ▄▄▄  ",
	u8" ▄▀  ▀▀▄▄  ▄▀ ▀█▀ ▀▄  ▄▄▀▀  ▀▄ ",
	u8"▄█ ▄▄▄▄  ███ ▀ ▄ ▀ ███  ▄▄▄▄ █▄",
	u8"   █   ▀▀████▄███▄████▀▀   █   ",
	u8" ▄█    ▄▄▄▀█████████▀▄▄▄    █▄ ",
	u8"   ▄▀▀▀                 ▀▀▀▄   ",
	u8"  █                         █  ",
	u8" ▀▀                         ▀▀ ",
}, {
	u8"               █               ",
	u8"  █▀▀▄▄     ▄▀▄█▄▀▄     ▄▄▀▀█  ",
	u8" █     ▀▀▄▄█ ▄ ▀ ▄ █▄▄▀▀     █ ",
	u8"▀▀ █▀▀▀▄▄███▄ ▄█▄ ▄███▄▄▀▀▀█ ▀▀",
	u8"  ▄▀     ▀███████████▀     ▀▄  ",
	u8" ▀▀ ▄▄▄▀▀▀ ▀▀▀▀▀▀▀▀▀ ▀▀▀▄▄▄ ▀▀ ",
	u8"  ▄▀                       ▀▄  ",
	u8" ▄█                         █▄ "
} };

#define SPIDER_UPPER		0
#define SPIDER_LOWER		1
#define SPIDER_DROPHEIGHT	13
#define SPIDER_WIDTH		31

const char* linesection = u8"               █               ";
const char* clearspiderspaces = u8"                               ";

const char* letters[3][BLOCK_ROW_COUNT] = { {
	u8"█▀▀▀▀▀▀▀▀▀▀▄",
	u8"█          █",
	u8"█          █",
	u8"█▄▄▄▄▄▄▄▄▄▄▀",
	u8"█     ▀▄    ",
	u8"█       ▀▄  ",
	u8"█         ▀▄",
	u8"            "
}, {
	u8"█▀▀▀▀▀▀▀▀▀▀▄",
	u8"█          █",
	u8"█          █",
	u8"█▄▄▄▄▄▄▄▄▄▄▀",
	u8"█           ",
	u8"█           ",
	u8"█           ",
	u8"            "
}, {
	u8"▄▄▄▄▄▄▄▄▄▄▄ ",
	u8"█          █",
	u8"█          █",
	u8"█          █",
	u8"█▀▀▀▀▀█▀▀▀▀ ",
	u8"█      ▀▄   ",
	u8"█        ▀▄ ",
	u8"▀          ▀"
} };

const char* clearleftletterspaces = u8"            ";
const char* clearrightletterspaces = u8"                    ";

#define LETTER_R			0
#define LETTER_P			1
#define LETTER_R_LOW		2
#define LETTER_WIDTH		12
#define LETTER_SPACEWIDTH	6

const char* verticalspace[BLOCK_ROW_COUNT] =
{
	u8" ",
	u8" ",
	u8" ",
	u8" ",
	u8" ",
	u8" ",
	u8" ",
	u8" "
};

const char* digits[BLOCK_ROW_COUNT] = {
	u8"▄█   ▄▀▀▀▀▀▄   ▄▀▀▀▀▀▄",
	u8" █         █   █      ",
	u8" █         █   █      ",
	u8" █    ▀▀▀▀▀▄   █▀▀▀▀▀▄",
	u8" █         █   █     █",
	u8" █         █   █     █",
	u8" █   ▀▄▄▄▄▄▀   ▀▄▄▄▄▄▀",
	u8"                      "
};

#define DIGITS_WIDTH	22

void RunIntro()
{
	int dropindex, flowindex, spiderindex;
	int screenbottomy, screenrightx;
	int spiderx, spiderbottomy, spiderrightx;
	bool screenwidthisodd;

	getfssize(screenbottomy, screenrightx);
	screenrightx--;

	clrfs(COLORS_INVERSE);

	screenwidthisodd = (screenrightx % 2 == 1);
	spiderx = (screenrightx - SPIDER_WIDTH) / 2;

	spiderbottomy = BLOCK_ROW_COUNT - 1;
	spiderrightx = SPIDER_WIDTH - 1;

	for (dropindex = BLOCK_ROW_COUNT; dropindex > 0; dropindex--)
	{
		for (spiderindex = 0; spiderindex < 2; spiderindex++)
		{
			printfsblocksectionat(0, spiderx, COLORS_INVERSE, spider[spiderindex], dropindex - 1, 0, spiderbottomy, spiderrightx);

			updatefs();
			mssleep(50);
		}
	}

	for (dropindex = 0; dropindex < SPIDER_DROPHEIGHT; dropindex++)
	{
		printfsat(dropindex, spiderx, COLORS_INVERSE, linesection);

		for (spiderindex = 0; spiderindex < 2; spiderindex++)
		{
			printfsblockat(dropindex + 1, spiderx, COLORS_INVERSE, spider[spiderindex], BLOCK_ROW_COUNT);

			updatefs();
			mssleep(50);
		}
	}

	int letterbottomy = BLOCK_ROW_COUNT - 1;
	int letterrightx = LETTER_WIDTH - 1;

	for (flowindex = 0; flowindex < LETTER_WIDTH; flowindex++)
	{
		printfsblocksectionat(2, 0, COLORS_INVERSE, letters[LETTER_R], 0, letterrightx - flowindex, letterbottomy, letterrightx);
		printfsblocksectionat(2, screenrightx - flowindex, COLORS_INVERSE, letters[LETTER_P], 0, 0, letterbottomy, flowindex);

		updatefs();
		mssleep(10);
	}

	int leftletterfinalx = screenrightx / 2 - LETTER_WIDTH - LETTER_SPACEWIDTH;
	int rightletterfirstx = screenrightx - LETTER_WIDTH;

	for (flowindex = 0; flowindex < leftletterfinalx; flowindex++)
	{
		printfsblockat(2, flowindex, COLORS_INVERSE, verticalspace, BLOCK_ROW_COUNT);
		printfsblockat(2, flowindex + 1, COLORS_INVERSE, letters[LETTER_R], BLOCK_ROW_COUNT);

		printfsblockat(2, rightletterfirstx - flowindex, COLORS_INVERSE, letters[LETTER_P], BLOCK_ROW_COUNT);
		printfsblockat(2, screenrightx - flowindex, COLORS_INVERSE, verticalspace, BLOCK_ROW_COUNT);

		updatefs();
		mssleep(10);
	}

	if (!screenwidthisodd)
	{
		printfsblockat(2, rightletterfirstx - flowindex, COLORS_INVERSE, letters[LETTER_P], BLOCK_ROW_COUNT);
		printfsblockat(2, screenrightx - flowindex, COLORS_INVERSE, verticalspace, BLOCK_ROW_COUNT);

		updatefs();
		mssleep(10);
	}

	int screenmiddlex = screenrightx / 2;
	if (!screenwidthisodd)
		screenmiddlex--;
	printfsat(1, screenmiddlex, COLORS_INVERSE, u8"▀");
	printfsat(1 + BLOCK_ROW_COUNT, screenmiddlex, COLORS_INVERSE, u8"▄");

	updatefs();
	mssleep(2000);

	int letterstopy = (screenbottomy - BLOCK_ROW_COUNT) / 2;
	if (letterstopy < 2)
		letterstopy = 2;

	printfsat(0, screenmiddlex, COLORS_INVERSE, u8" ");
	printfsat(1, screenmiddlex, COLORS_INVERSE, u8" ");
	for (int i = 2; i < 2 + BLOCK_ROW_COUNT; i++)
	{
		printfsat(i, screenmiddlex, COLORS_INVERSE, clearrightletterspaces);
	}

	for (int i = 2 + BLOCK_ROW_COUNT; i < SPIDER_DROPHEIGHT; i++)
	{
		printfsat(i, screenmiddlex, COLORS_INVERSE, u8" ");
	}

	for (int i = SPIDER_DROPHEIGHT; i < SPIDER_DROPHEIGHT + BLOCK_ROW_COUNT; i++)
	{
		printfsat(i, spiderx, COLORS_INVERSE, clearspiderspaces);
	}

	for (int i = 2; i < letterstopy; i++)
	{
		printfsblockat(i, leftletterfinalx, COLORS_INVERSE, letters[LETTER_R_LOW], BLOCK_ROW_COUNT);

		updatefs();
		mssleep(10);

		printfsat(i, leftletterfinalx, COLORS_INVERSE, clearleftletterspaces);
		printfsblockat(i + 1, leftletterfinalx, COLORS_INVERSE, letters[LETTER_R], BLOCK_ROW_COUNT);
	
		updatefs();
		mssleep(10);
	}

	int digitsfinalx = leftletterfinalx + LETTER_WIDTH + 3;
	int digitsbottomy = BLOCK_ROW_COUNT - 1;

	for (flowindex = 0; flowindex < DIGITS_WIDTH; flowindex++)
	{
		printfsblocksectionat(letterstopy, screenrightx - flowindex, COLORS_INVERSERED, digits, 0, 0, digitsbottomy, flowindex);

		updatefs();
		mssleep(10);
	}

	for (flowindex = screenrightx - DIGITS_WIDTH; flowindex >= digitsfinalx; flowindex--)
	{
		printfsblockat(letterstopy, flowindex, COLORS_INVERSERED, digits, BLOCK_ROW_COUNT);
		printfsblockat(letterstopy, flowindex + DIGITS_WIDTH, COLORS_INVERSERED, verticalspace, BLOCK_ROW_COUNT);

		updatefs();
		mssleep(10);
	}

	mssleep(2500);

	clrfs(COLORS_NORMAL);
}