/***************************************************************************
 * Includes necessary for functions to work
 ***************************************************************************/
#include "r136.h"
#include <locale.h>

/***************************************************************************
 * #defines of constants used by the functions
 ***************************************************************************/

enum class Key : char {
	kEscape = -2,
	kEnter = 5,
	kUp = 8,
	kDown = 2,
	kTab = 6,
	kShiftTab = 4
};

/* Value that determines the settings for Insert for all functions.
	== 0: Insert off at start, use block cursor to indicate Insert on.
	== 1: Insert on at start, use block cursor to indicate Insert on.
	== 2: Insert off at start, use block cursor to indicate Insert off.
	== 3: Insert on at start, use block cursor to indicate Insert off. */
constexpr int kInsertFlag = 3;

#define FG_BOLD			COLOR_WHITE
#define FG_BANNER		COLOR_RED
#define FG_ERROR		COLOR_RED
#define FG_INVERSE		COLOR_BLACK
#define FG_INVERSERED	COLOR_RED
#define FG_NORMAL		COLOR_WHITE
#define BG_BOLD			COLOR_BLACK
#define BG_BANNER		COLOR_BLACK
#define BG_ERROR		COLOR_BLACK
#define BG_INVERSE		COLOR_WHITE
#define BG_INVERSERED	COLOR_WHITE
#define BG_NORMAL		COLOR_BLACK
#define ATTR_BOLD		(COLOR_PAIR(Color::kBold) | A_BOLD)
#define ATTR_BANNER		(COLOR_PAIR(Color::kBanner) | A_UNDERLINE)
#define ATTR_ERROR		(COLOR_PAIR(Color::kError) | A_BOLD)
#define ATTR_INVERSE	(COLOR_PAIR(Color::kInverse))
#define ATTR_INVERSERED	(COLOR_PAIR(Color::kInverseRed) | A_BOLD)
#define ATTR_NORMAL		(COLOR_PAIR(Color::kNormal))

chtype attributes[Color::COUNT];

WINDOW *banner_window = NULL;
WINDOW* main_window = NULL;
WINDOW *input_window = NULL;
WINDOW* full_screen = NULL;


 /***************************************************************************
  * Definitions of the functions
  ***************************************************************************/

void SetupWindows()
{
	int height, width;

	getmaxyx(stdscr, height, width);

	if (banner_window)
	{
		wresize(banner_window, 2, width);
		touchwin(banner_window);
	}
	else
		banner_window = subwin(stdscr, 2, width, 0, 0);

	if (main_window)
	{
		wresize(main_window, height - 3, width);
		touchwin(main_window);
	}
	else 
	{
		main_window = subwin(stdscr, height - 3, width, 2, 0);
		keypad(main_window, TRUE);
		touchwin(main_window);
	}

	if (input_window)
	{
		wresize(input_window, 1, width);
		mvwin(input_window, height - 1, 0);
		touchwin(input_window);
	}
	else 
	{
		input_window = subwin(stdscr, 1, width, height - 1, 0);
		keypad(input_window, true);
	}

	wattron(banner_window, ATTR_BANNER);
	wmove(banner_window, 0, 0);
	WriteCentered(banner_window, "Missiecode: R136");

	scrollok(main_window, true);

	wrefresh(banner_window);
	wrefresh(main_window);
	wrefresh(input_window);
}

int PrintToMainWindow(const char* format, ...)
{
	va_list args;
	int return_value;

	va_start(args, format);
	return_value = vw_printw(main_window, format, args);
	va_end(args);

	return return_value;
}

int WriteToMainWindow(const wchar_t *text)
{
	return waddwstr(main_window, text);
}

void InitializeColors()
{
	start_color();

	init_pair(kBold, FG_BOLD, BG_BOLD);
	attributes[kBold] = ATTR_BOLD;

	init_pair(kBanner, FG_BANNER, BG_BANNER);
	attributes[kBanner] = ATTR_BANNER;

	init_pair(kError, FG_ERROR, BG_ERROR);
	attributes[kError] = ATTR_ERROR;

	init_pair(Color::kInverse, FG_INVERSE, BG_INVERSE);
	attributes[Color::kInverse] = ATTR_INVERSE;

	init_pair(Color::kInverseRed, FG_INVERSERED, BG_INVERSERED);
	attributes[Color::kInverseRed] = ATTR_INVERSERED;

	init_pair(kNormal, FG_NORMAL, BG_NORMAL);
	attributes[kNormal] = ATTR_NORMAL;

}

void InitializeConsole()
{
	setlocale(LC_ALL, "");

	initscr();
	noecho();
	keypad(stdscr, true);

	full_screen = stdscr;
	
	InitializeColors();
}

void ReleaseConsole()
{
	if (input_window)
		delwin(input_window);

	if (main_window)
		delwin(main_window);

	if (banner_window)
		delwin(banner_window);

	endwin();
}

void PrintFullScreenBlockAt(int y, int x, Color colors, const wchar_t** block, int rowcount) 
{
	wattron(full_screen, attributes[colors]);
	
	for (int i  = 0; i < rowcount; i++)
		mvwaddwstr(full_screen, y + i, x, block[i]);

	wattroff(full_screen, attributes[colors]);
}

void PrintFullScreenBlockSectionAt(int y, int x, Color colors, const wchar_t** block, int topy, int leftx, int bottomy, int rightx)
{
	wattron(full_screen, attributes[colors]);

	for (int i = topy; i <= bottomy; i++)
		mvwaddnwstr(full_screen, y + i - topy, x, &block[i][leftx], rightx - leftx + 1);

	wattroff(full_screen, attributes[colors]);
}


void PrintFullScreenAt(int y, int x, Color colors, const wchar_t* text) 
{
	wattron(full_screen, attributes[colors]);
	mvwaddwstr(full_screen, y, x, text);
	wattroff(full_screen, attributes[colors]);
}

void ClearFullScreen(Color colors) 
{
	wbkgd(full_screen, attributes[colors]);
	werase(full_screen);
}

void UpdateFullScreen()
{
	wrefresh(full_screen);
}

void ClearWindow()
{
	werase(main_window);
}

void GetFullScreenSize(int& y, int& x)
{
	getmaxyx(full_screen, y, x);
}

void WaitForKeyCore(WINDOW* window, bool do_setup) 
{
	int y, x;

	wrefresh(window);

	while (true)
	{
		getyx(window, y, x);
	
		if (mvwgetch(window, y, x) == KEY_RESIZE)
		{
			resize_term(0, 0);
			if (do_setup)
			{
				SetupWindows();
			}
		}
		else
			break;
	}
}

void WaitForFullScreenKey()
{
	WaitForKeyCore(full_screen, false);
}

void WaitForKey()
{
	WaitForKeyCore(main_window, true);
}

void WriteCentered(WINDOW* win, const char* str)
{
	int winwidth = getmaxx(win);
	int strlength = strlen(str);

	ClearLine(win);

	int x = (winwidth - strlength) / 2;
	mvwaddstr(win, getcury(win), x < 0 ? 0 : x, str);
}

void GetCommandString(char *input, int max_length) 
{
	memset(input, ' ', max_length);
	input[max_length] = 0;

	wrefresh(main_window);

	wmove(input_window, 0, 0);
	ClearLine(input_window);

	wattron(input_window, ATTR_BOLD);
	waddstr(input_window, "> ");

	GetStringInput(input_window, " abcdefghijklmnopqrstuvwxyz", input, 0, getcurx(input_window), -1, 0, 0);

	ClearLine(input_window);
	wmove(input_window, 0, 0);

	wattroff(input_window, ATTR_BOLD);
}

void PrintCommandString(const char* format, ...)
{
	wmove(input_window, 0, 0);
	ClearLine(input_window);

	va_list args;

	wattron(input_window, ATTR_ERROR);

	va_start(args, format);
	vw_printw(input_window, format, args);
	va_end(args);

	wattroff(input_window, ATTR_ERROR);

	wrefresh(input_window);
	wgetch(input_window);
}

int AdvancedGetChar(const char *allowed)
{  
	char input = 0;
	int y = getcury(main_window);
	int x = getcurx(main_window);

	wattron(main_window, ATTR_BOLD);

	do
	{  
		wmove(main_window, y, x);

		if (AdvancedScanF(main_window, 0, 1, allowed, "%c", &input) == to_underlying(Key::kEscape))
			input = to_underlying(Key::kEscape);
	}
	while (input == ' ');

	wattroff(main_window, ATTR_BOLD);

	return input;
}

int AdvancedScanF(WINDOW *win, int check_input, int length, const char *allowed_characters, const char *format_string, ...)
{  
	va_list argp;
	char *inpstr;
	int toret = 0;

	inpstr = (char *) calloc((size_t)length + 1, sizeof(char));

	if (!inpstr)
		return to_underlying(Key::kEscape);

	do
	{  
		memset(inpstr, ' ', length);
		if (!((toret = GetStringInput(win, allowed_characters, inpstr, getcury(win), getcurx(win), 0, 1, 0)) == to_underlying(Key::kEscape)))
		{  
			va_start(argp, format_string);
			toret = vsscanf(inpstr, format_string, argp);
			va_end(argp);
		}
	}
	while (check_input && (toret == EOF || !toret));

	free(inpstr);

	return toret;
}

void ClearLine(WINDOW *win) 
{
	wmove(win, getcury(win), 0);
	wclrtoeol(win);
}

int GetStringInput (WINDOW *win, const char *allowed_characters, char *input, int input_y, int input_x, int capslock_forced, int enable_escape, int enable_directionals)
{
	static int ins = 0;
	int ilen, ipos = 0, toret = 0, curx, cury;
	int ichar;

	ilen = (int)strlen(input) - 1;
	curx = getcurx(win);
	cury = getcury(win);

	ins = kInsertFlag & 1;

/*
	if ((ins && L_INSFLAG & 2) || (!ins && !(L_INSFLAG & 2)))
		setcursor(CURSOR_NORMAL);
	else
		setcursor(CURSOR_FULL);
*/

	do
	{  
		wmove(win, input_y, input_x + ipos);
		wrefresh(input_window);

		ichar = wgetch(win);

		switch (ichar)
		{
		case KEY_RESIZE:

			resize_term(0, 0);
			SetupWindows();

			break;

		case KEY_LEFT: /* Arrow left */

			if (ipos)
				ipos--;

			break;

		case KEY_RIGHT: /* Arrow right */

			if (ipos < ilen)
				ipos++;

			break;

		case KEY_HOME: /* Home */

			ipos = 0;

			break;

		case KEY_END: /* End */

			ipos = ilen;

			if (input[ipos] == ' ')
				while (ipos && input[ipos - 1] == ' ')
					ipos--;

			break;

		case KEY_IC: /* Insert */

			ins = ins ? 0 : 1;
/*
			if ((ins && L_INSFLAG & 2) || (!ins && !(L_INSFLAG & 2)))
				setcursor(CURSOR_NORMAL);
			else
				setcursor(CURSOR_FULL);
			break;
*/
		case KEY_DC: /* Delete */

			memmove(input + ipos, input + ipos + 1, (size_t)ilen - ipos);

			input[ilen] = ' ';
			wdelch(win);

			break;

		case KEY_UP: /* Arrow up */
			if (enable_directionals)
				toret = to_underlying(Key::kUp);

			break;

		case KEY_DOWN: /* Arrow down */

			if (enable_directionals)
				toret = to_underlying(Key::kDown);

			break;

		case KEY_BTAB: /* Shift-Tab */

			if (enable_directionals)
				toret = to_underlying(Key::kShiftTab);

			break;

		case KEY_BACKSPACE: /* Backspace */

			#ifdef __APPLE__
			case 127:
			#else
			case 8:
			#endif

			if (ipos)
			{  
				memmove(input + ipos - 1, input + ipos, (size_t)ilen - ipos + 1);
				input[ilen] = ' ';
				mvwdelch(win, input_y, input_x + --ipos);
			}

			break;

		case KEY_STAB: /* Tab */

			if (enable_directionals)
				toret = to_underlying(Key::kTab);

			break;

		case KEY_ENTER: /* Enter */
		case 10:

			toret = to_underlying(Key::kEnter);
			break;

		case 27: /* Escape */

			if (enable_escape)
				toret = to_underlying(Key::kEscape);
			else
			{
				memset(input, ' ', ilen);
				mvwaddstr(win, input_y, input_x, input);
				ipos = 0;
			}

			break;

		default:

			if (capslock_forced > 0)
				ichar = toupper(ichar);
			else if (capslock_forced < 0)
				ichar = tolower(ichar);

			if (strchr(allowed_characters, ichar))
			{  
				if (ins)
				{  
					memmove(input + ipos + 1, input + ipos, (size_t)ilen - ipos);

					mvwdelch(win, input_y, input_x + ilen);
					mvwinsch(win, input_y, input_x + ipos, ichar);
				}
				else 
				{
					waddch(win, ichar);

				}

				input[ipos] = ichar;

				if (ipos < ilen)
					ipos++;
			}

			break;
		}
	}
	while (!toret);
//	setcursor(CURSOR_NORMAL);

	if (ipos == ilen) 
	{
		curx++;
	}

	wmove(win, cury, curx);

	return toret;
}
