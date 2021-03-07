/***************************************************************************
 * Includes necessary for functions to work
 ***************************************************************************/
#include "r136.h"
#include <locale.h>

/***************************************************************************
 * #defines of constants used by the functions
 ***************************************************************************/

/* Value used to indicate Escape keypress */
#define L_ESC     -2
/* Value used to indicate Enter keypress */
#define L_ENTER    5
/* Value used to indicate arrow up keypress */
#define L_UP       8
/* Value used to indicate arrow down keypress */
#define L_DOWN     2
/* Value used to indicate Tab keypress */
#define L_TAB      6
/* Value used to indicate Shift Tab keypress */
#define L_STAB     4
/* Value that determines the settings for Insert for all functions.
	== 0: Insert off at start, use block cursor to indicate Insert on.
	== 1: Insert on at start, use block cursor to indicate Insert on.
	== 2: Insert off at start, use block cursor to indicate Insert off.
	== 3: Insert on at start, use block cursor to indicate Insert off. */
#define L_INSFLAG  3

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
#define ATTR_BOLD		(COLOR_PAIR(COLORS_BOLD) | A_BOLD)
#define ATTR_BANNER		(COLOR_PAIR(COLORS_BANNER) | A_UNDERLINE)
#define ATTR_ERROR		(COLOR_PAIR(COLORS_ERROR) | A_BOLD)
#define ATTR_INVERSE	(COLOR_PAIR(COLORS_INVERSE))
#define ATTR_INVERSERED	(COLOR_PAIR(COLORS_INVERSERED) | A_BOLD)
#define ATTR_NORMAL		(COLOR_PAIR(COLORS_NORMAL))

chtype attributes[7];

WINDOW *BANNERWINDOW = NULL;
WINDOW* MAINWINDOW = NULL;
WINDOW *INPUTWINDOW = NULL;
WINDOW* FULLSCREEN = NULL;


 /***************************************************************************
  * Definitions of the functions
  ***************************************************************************/

void setupwindows()
{
	int height, width;

	getmaxyx(stdscr, height, width);

	if (BANNERWINDOW)
	{
		wresize(BANNERWINDOW, 2, width);
		touchwin(BANNERWINDOW);
	}
	else
		BANNERWINDOW = subwin(stdscr, 2, width, 0, 0);

	if (MAINWINDOW)
	{
		wresize(MAINWINDOW, height - 3, width);
		touchwin(MAINWINDOW);
	}
	else 
	{
		MAINWINDOW = subwin(stdscr, height - 3, width, 2, 0);
		keypad(MAINWINDOW, TRUE);
		touchwin(MAINWINDOW);
	}

	if (INPUTWINDOW)
	{
		wresize(INPUTWINDOW, 1, width);
		mvwin(INPUTWINDOW, height - 1, 0);
		touchwin(INPUTWINDOW);
	}
	else 
	{
		INPUTWINDOW = subwin(stdscr, 1, width, height - 1, 0);
		keypad(INPUTWINDOW, true);
	}

	wattron(BANNERWINDOW, ATTR_BANNER);
	wmove(BANNERWINDOW, 0, 0);
	printcentered(BANNERWINDOW, "Missiecode: R136");

	scrollok(MAINWINDOW, true);

	wrefresh(BANNERWINDOW);
	wrefresh(MAINWINDOW);
	wrefresh(INPUTWINDOW);
}

int printmw(const char* fmt, ...)
{
	va_list args;
	int retval;

	va_start(args, fmt);
	retval = vw_printw(MAINWINDOW, fmt, args);
	va_end(args);

	return retval;
}

int writemw(const wchar_t *text)
{
	return waddwstr(MAINWINDOW, text);
}



void initcolors()
{
	start_color();

	init_pair(COLORS_BOLD, FG_BOLD, BG_BOLD);
	attributes[COLORS_BOLD] = ATTR_BOLD;

	init_pair(COLORS_BANNER, FG_BANNER, BG_BANNER);
	attributes[COLORS_BANNER] = ATTR_BANNER;

	init_pair(COLORS_ERROR, FG_ERROR, BG_ERROR);
	attributes[COLORS_ERROR] = ATTR_ERROR;

	init_pair(COLORS_INVERSE, FG_INVERSE, BG_INVERSE);
	attributes[COLORS_INVERSE] = ATTR_INVERSE;

	init_pair(COLORS_INVERSERED, FG_INVERSERED, BG_INVERSERED);
	attributes[COLORS_INVERSERED] = ATTR_INVERSERED;

	init_pair(COLORS_NORMAL, FG_NORMAL, BG_NORMAL);
	attributes[COLORS_NORMAL] = ATTR_NORMAL;

}

void initconsole()
{
	char *oldlocale = setlocale(LC_ALL, "en_US.UTF-8");

	initscr();
	noecho();
	keypad(stdscr, true);

	FULLSCREEN = stdscr;
	
	initcolors();
}

void releaseconsole()
{
	if (INPUTWINDOW)
		delwin(INPUTWINDOW);

	if (MAINWINDOW)
		delwin(MAINWINDOW);

	if (BANNERWINDOW)
		delwin(BANNERWINDOW);

	endwin();
}

void printfsblockat(int y, int x, int colors, const wchar_t** block, int rowcount) 
{
	wattron(FULLSCREEN, attributes[colors]);
	
	for (int i  = 0; i < rowcount; i++)
		mvwaddwstr(FULLSCREEN, y + i, x, block[i]);

	wattroff(FULLSCREEN, attributes[colors]);
}

void printfsblocksectionat(int y, int x, int colors, const wchar_t** block, int topy, int leftx, int bottomy, int rightx)
{
	wattron(FULLSCREEN, attributes[colors]);

	for (int i = topy; i <= bottomy; i++)
		mvwaddnwstr(FULLSCREEN, y + i - topy, x, &block[i][leftx], rightx - leftx + 1);

	wattroff(FULLSCREEN, attributes[colors]);
}


void printfsat(int y, int x, int colors, const wchar_t* text) 
{
	wattron(FULLSCREEN, attributes[colors]);
	mvwaddwstr(FULLSCREEN, y, x, text);
	wattroff(FULLSCREEN, attributes[colors]);
}

void clrfs(int colors) 
{
	wbkgd(FULLSCREEN, attributes[colors]);
	werase(FULLSCREEN);
}

void updatefs()
{
	wrefresh(FULLSCREEN);
}

void clrscr()
{
	werase(MAINWINDOW);
}

void getfssize(int& y, int& x)
{
	getmaxyx(FULLSCREEN, y, x);
}

void waitforkeyengine(WINDOW* window, bool dosetup) 
{
	int y, x;

	wrefresh(window);

	while (true)
	{
		getyx(window, y, x);
	
		if (mvwgetch(window, y, x) == KEY_RESIZE)
		{
			resize_term(0, 0);
			if (dosetup)
			{
				setupwindows();
			}
		}
		else
			break;
	}
}

void waitforfskey()
{
	waitforkeyengine(FULLSCREEN, false);
}

void waitforkey()
{
	waitforkeyengine(MAINWINDOW, true);
}

void printcentered(WINDOW* win, const char* str)
{
	int winwidth = getmaxx(win);
	int strlength = strlen(str);

	clearline(win);

	int x = (winwidth - strlength) / 2;
	mvwaddstr(win, getcury(win), x < 0 ? 0 : x, str);
}

/*
void setcursor(int mode)
{
	static int normalcursorheight = UNDEFINED;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	GetConsoleCursorInfo(console, &cursor);

	if (normalcursorheight == UNDEFINED)
	{
		normalcursorheight = cursor.dwSize;
	}

	switch (mode)
	{
	case CURSOR_NORMAL:
		cursor.dwSize = normalcursorheight;
		SetConsoleCursorInfo(console, &cursor);
		break;
	case CURSOR_FULL:
		cursor.dwSize = 100;
		SetConsoleCursorInfo(console, &cursor);
		break;
	}
}
*/

void getcmdstr(char *input, int maxlength) 
{
	memset(input, ' ', maxlength);
	input[maxlength] = 0;

	wrefresh(MAINWINDOW);

	wmove(INPUTWINDOW, 0, 0);
	clearline(INPUTWINDOW);

	wattron(INPUTWINDOW, ATTR_BOLD);
	waddstr(INPUTWINDOW, "> ");

	strinp(INPUTWINDOW, " abcdefghijklmnopqrstuvwxyz", input, 0, getcurx(INPUTWINDOW), -1, 0, 0);

	clearline(INPUTWINDOW);
	wmove(INPUTWINDOW, 0, 0);

	wattroff(INPUTWINDOW, ATTR_BOLD);
}

void printcmdstr(const char* fmt, ...)
{
	wmove(INPUTWINDOW, 0, 0);
	clearline(INPUTWINDOW);

	va_list args;

	wattron(INPUTWINDOW, ATTR_ERROR);

	va_start(args, fmt);
	vw_printw(INPUTWINDOW, fmt, args);
	va_end(args);

	wattroff(INPUTWINDOW, ATTR_ERROR);

	wrefresh(INPUTWINDOW);
	wgetch(INPUTWINDOW);
}

/*=========================================================================*
 * function: int agetchar(char *allowed)
 * description: gets a character from the keyboard. It only accepts
 *              characters that are in the string allowed points to.
 * parameters: allowed: pointer to string that contains valid characters.
 *                      Characters that are not in this string will be
 *                      ignored.
 * return: the character that is entered, or L_ESC if Escape is pressed.
 * remarks: 1. before return, the function sets the cursor position to what it
 *             was before the function was called.
 *          2. Unlike the standard getchar function, agetchar waits for Enter
 *             to be pressed.
 *
 * example: y_or_n = agetchar("yYnN");
 *=========================================================================*/
int agetchar(const char *allowed)
{  
	char input = 0;
	int y = getcury(MAINWINDOW);
	int x = getcurx(MAINWINDOW);

	wattron(MAINWINDOW, ATTR_BOLD);

	do
	{  
		wmove(MAINWINDOW, y, x);

		if (ascanf(MAINWINDOW, 0, 1, allowed, "%c", &input) == L_ESC)
			input = L_ESC;
	}
	while (input == ' ');

	wattroff(MAINWINDOW, ATTR_BOLD);

	return input;
}

/*=========================================================================*
 * function: int ascanf(int chckinp, int length, char *allowed, char *frmstr,
 *                      ...)
 * description: extended version of scanf. Allows you to specify how many
 *              and which characters can be used for input.
 * parameters:  chckinp: 0: don't check if input was succesful, always exit
 *                           after Enter is pressed.
 *                       != 0: check if input was succesful. If not, repeat
 *                             the input process until it is.
 *              length: number of characters that can be entered during input.
 *              allowed: pointer to string that contains valid input-
 *                       characters. Characters that are not in this string
 *                       will be ignored.
 *              frmstr: format string that specifies the types of variables
 *                      to which the given input must be written, equal to the
 *                      format string of for instance scanf.
 *              ...: parameters to which the input has to be written, similar
 *                   to those of scanf.
 * return: L_ESC: Escape was pressed during input.
 *         EOF: error occured during writing input to parameters.
 *         other: number of input fields scanned.
 * remarks: 1. the function does not check if the input is too long for one
 *             line. If you make length so great that the last part of the
 *             input field runs off the screen line the results are undefined,
 *             but messy.
 *          2. before return, the function sets the cursor position to what
 *             it was before the function was called.
 *
 * example: ascanf(1, 25, "1234567890.", "%d %f", &intvar, &floatvar);
 *=========================================================================*/
int ascanf(WINDOW *win, int chckinp, int length, const char *allowed, const char *frmstr, ...)
{  
	va_list argp;
	char *inpstr;
	int toret = 0;

	inpstr = (char *) calloc((size_t)length + 1, sizeof(char));

	if (!inpstr)
		return L_ESC;

	do
	{  
		memset(inpstr, ' ', length);
		if (!((toret = strinp(win, allowed, inpstr, getcury(win), getcurx(win), 0, 1, 0)) == L_ESC))
		{  
			va_start(argp, frmstr);
			toret = vsscanf(inpstr, frmstr, argp);
			va_end(argp);
		}
	}
	while (chckinp && (toret == EOF || !toret));

	free(inpstr);

	return toret;
}

void clearline(WINDOW *win) 
{
	wmove(win, getcury(win), 0);
	wclrtoeol(win);
}

/*=========================================================================*
 * function: int strinp (unsigned char *allowed, unsigned char *input,
 *                       int inpx, int inpy, int caps, int esc, int curm)
 * description: routine to read a string from stdin. It accepts all 'standard'
 *              editing keys (arrow right & left, BS, DEL, Home, End, INS).
 *              The characters that are valid for input can be specified,
 *              they can be auto-converted to upper- or lowercase and it is
 *              possible to make strinp return if arrow up, arrow down, Tab
 *              or Shift-Tab are pressed.
 * parameters:  allowed: pointer to string that contains valid input-
 *                       characters. Characters that are not in this string
 *                       will be ignored.
 *              input: pointer to string that has to be edited. Input is
 *                     started using this string as a basis. Any characters
 *                     that are entered are immediately processed into this
 *                     string.
 *              inpx: x-position where the first character of the input field
 *                    will be placed.
 *              inpy: y-position where the first character of the input field
 *                    will be placed.
 *              caps: < 0: all characters received from keyboard will be auto-
 *                         converted to lower case.
 *                    == 0: no converting will take place.
 *                    > 0: all characters received from keyboard will be auto-
 *                         converted to upper case.
 *              esc: == 0: Escape-keypresses will be ignored.
 *                   != 0: strinp will return on Escape-keypress.
 *              curm: == 0: strikes of Arrow up & down, Tab and Shift-Tab will
 *                          be ignored.
 *                    != 0: strikes of Arrow up & down, Tab and Shift-Tab will
 *                          make strinp return.
 * return: L_ESC: Escape was pressed during input and esc != 0.
 *         L_UP: Arrow up was pressed during input and curm != 0.
 *         L_DOWN: Arrow down was pressed during input and curm != 0.
 *         L_TAB: Tab was pressed during input and curm != 0.
 *         L_STAB: Shift-Tab was pressed during input and curm != 0.
 *         L_ENTER: strinp returned after Enter being pressed.
 * remarks: 1. the function does not check if the input is too long for one
 *             line. If you make length so great that the last part of the
 *             input field runs off the screen line the results are undefined,
 *             but messy.
 *          2. before return, the function sets the cursor position to what
 *             it was before the function was called.
 *
 * example: whyreturn = strinp("1234567890.", myinp, 10, 12, 0, 1, 1);
 *=========================================================================*/
int strinp (WINDOW *win, const char *allowed, char *input, int inpy, int inpx, int caps, int esc, int curm)
{
	static int ins = 0;
	int ilen, ipos = 0, toret = 0, curx, cury;
	int ichar;

	ilen = (int)strlen(input) - 1;
	curx = getcurx(win);
	cury = getcury(win);

	ins = L_INSFLAG & 1;

/*
	if ((ins && L_INSFLAG & 2) || (!ins && !(L_INSFLAG & 2)))
		setcursor(CURSOR_NORMAL);
	else
		setcursor(CURSOR_FULL);
*/

	do
	{  
		wmove(win, inpy, inpx + ipos);
		wrefresh(INPUTWINDOW);

		ichar = wgetch(win);

		switch (ichar)
		{
		case KEY_RESIZE:

			resize_term(0, 0);
			setupwindows();

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
			if (curm)
				toret = L_UP;

			break;

		case KEY_DOWN: /* Arrow down */

			if (curm)
				toret = L_DOWN;

			break;

		case KEY_BTAB: /* Shift-Tab */

			if (curm)
				toret = L_STAB;

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
				mvwdelch(win, inpy, inpx + --ipos);
			}

			break;

		case KEY_STAB: /* Tab */

			if (curm)
				toret = L_TAB;

			break;

		case KEY_ENTER: /* Enter */
		case 10:

			toret = L_ENTER;
			break;

		case 27: /* Escape */

			if (esc)
				toret = L_ESC;
			else
			{
				memset(input, ' ', ilen);
				mvwaddstr(win, inpy, inpx, input);
				ipos = 0;
			}

			break;

		default:

			if (caps > 0)
				ichar = toupper(ichar);
			else if (caps < 0)
				ichar = tolower(ichar);

			if (strchr(allowed, ichar))
			{  
				if (ins)
				{  
					memmove(input + ipos + 1, input + ipos, (size_t)ilen - ipos);

					mvwdelch(win, inpy, inpx + ilen);
					mvwinsch(win, inpy, inpx + ipos, ichar);
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
