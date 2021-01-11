/***************************************************************************
 * Includes necessary for functions to work
 ***************************************************************************/
#include <conio.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
/* Character that will be written to screen in front of the actual input
	string if any the functions is used.
	Set to 0 to prevent a leading character being written. */
#define L_INPSTART 0
/* Character that will be written to screen behind the actual input string if
	any of the functions is used.
	Set to 0 to prevent a closing character being written. */
#define L_INPEND   0
/* Value that determines the settings for Insert for all functions.
	== 0: Insert off at start, use block cursor to indicate Insert on.
	== 1: Insert on at start, use block cursor to indicate Insert on.
	== 2: Insert off at start, use block cursor to indicate Insert off.
	== 3: Insert on at start, use block cursor to indicate Insert off. */
#define L_INSFLAG  3

/***************************************************************************
 * Declarations of the functions
 ***************************************************************************/
void clrscr();
int wherex();
int wherey();
void gotoxy(int x, int y);
void setcursor(int mode);
int agetchar(const char *allowed);
int ascanf(int chckinp, int length, const char *allowed, const char *frmstr, ...);
int strinp (const char *allowed, char *input, int inpx, int inpy, int caps, int esc, int curm);

#define CURSOR_NORMAL		0
#define CURSOR_FULL			1
#define CURSOR_UNDEFINED	-1

/*-------------------------------------------------------------------------*
 * Remarks: 1. to create a header file for the  functions, the code shown
 *             until so far has to be used for that purpose.
 *          2. the routines use functions that can write to screen via either
 *             BIOS routines or direct video memory access.
 *             To use the BIOS routines (slower but valid for any MS-DOS
 *             computer and default), include this code in your source file:
 *             directvideo = 0;
 *             To use the memory routines (faster but unusable for some
 *             computers), include this code in your source file:
 *             directvideo = 1;
 *-------------------------------------------------------------------------*/

 /***************************************************************************
  * Definitions of the functions
  ***************************************************************************/

void clrscr()
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
	
	SetConsoleCursorPosition(console, topLeft);
}

int wherex()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;

	GetConsoleScreenBufferInfo(console, &screen);
	return screen.dwCursorPosition.X + 1;
}

int wherey()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;

	GetConsoleScreenBufferInfo(console, &screen);
	return screen.dwCursorPosition.Y + 1;
}

void gotoxy(int x, int y)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { (SHORT)x - 1, (SHORT)y - 1};

	SetConsoleCursorPosition(console, position);
}

void setcursor(int mode)
{
	static int normalcursorheight = CURSOR_UNDEFINED;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor;

	GetConsoleCursorInfo(console, &cursor);

	if (normalcursorheight == CURSOR_UNDEFINED)
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
{  char input = 0;

	do
	{  if (ascanf(0, 1, allowed, "%c", &input) == L_ESC)
			input = L_ESC;
	}
	while (input == ' ');
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
int ascanf(int chckinp, int length, const char *allowed, const char *frmstr, ...)
{  va_list argp;
	char *inpstr;
	int toret = 0;

	inpstr = (char *) calloc((size_t)length + 1, sizeof(char));
	if (!inpstr)
		return L_ESC;

	do
	{  memset(inpstr, ' ', length);
		if (!((toret = strinp(allowed, inpstr, wherex(), wherey(), 0, 1, 0)) == L_ESC))
		{  va_start(argp, frmstr);
			toret = vsscanf(inpstr, frmstr, argp);
			va_end(argp);
		}
	}
	while (chckinp && (toret == EOF || !toret));
	free(inpstr);
	return toret;
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
int strinp (const char *allowed, char *input, int inpx, int inpy, int caps, int esc, int curm)
{
	static int ins = 0;
	int ilen, ipos = 0, toret = 0, curx, cury;
	int ichar;

	ilen = (int)strlen(input) - 1;
	curx = wherex();
	cury = wherey();
	gotoxy(inpx, inpy);
	if (L_INPSTART)
	{  _putch(L_INPSTART);
		inpx++;
	}
	_cputs(input);
	if (L_INPEND)
		_putch(L_INPEND);

	ins = L_INSFLAG & 1;

	if ((ins && L_INSFLAG & 2) || (!ins && !(L_INSFLAG & 2)))
		setcursor(CURSOR_NORMAL);
	else
		setcursor(CURSOR_FULL);

	do
	{  gotoxy(inpx + ipos, inpy);
		switch (ichar = _getch())
		{  
		case 0:
		case 0xE0:
			switch (_getch())
			{  
			case 75: /* Arrow left */
				if (ipos)
					ipos--;
				break;
			case 77: /* Arrow right */
				if (ipos < ilen)
					ipos++;
				break;
			case 71: /* Home */
				ipos = 0;
				break;
			case 79: /* End */
				ipos = ilen;
				if (input[ipos] == ' ')
					while (ipos && input[ipos - 1] == ' ')
						ipos--;
				break;
			case 82: /* Insert */
				ins = ins ? 0 : 1;
				if ((ins && L_INSFLAG & 2) || (!ins && !(L_INSFLAG & 2)))
					setcursor(CURSOR_NORMAL);
				else
					setcursor(CURSOR_FULL);
				break;
			case 83: /* Delete */
				memmove(input + ipos, input + ipos + 1, (size_t)ilen - ipos);
				input[ilen] = ' ';
				_cputs(input + ipos);
				break;
			case 72: /* Arrow up */
				if (curm)
					toret = L_UP;
				break;
			case 80: /* Arrow down */
				if (curm)
					toret = L_DOWN;
				break;
			case 15: /* Shift-Tab */
				if (curm)
					toret = L_STAB;
				break;
			}
			break;
		case 8: /* Backspace */
			if (ipos)
			{  memmove(input + ipos - 1, input + ipos, (size_t)ilen - ipos + 1);
				input[ilen] = ' ';
				gotoxy(inpx + --ipos, inpy);
				_cputs(input + ipos);
			}
			break;
		case 9: /* Tab */
			if (curm)
				toret = L_TAB;
			break;
		case 13: /* Enter */
			toret = L_ENTER;
			break;
		case 27: /* Escape */
			if (esc)
				toret = L_ESC;
			break;
		default:
			if (caps > 0)
				ichar = toupper(ichar);
			else if (caps < 0)
				ichar = tolower(ichar);
			if (strchr(allowed, ichar))
			{  _putch(ichar);
				if (ins)
				{  memmove(input + ipos + 1, input + ipos, (size_t)ilen - ipos);
					_cputs(input + ipos + 1);
				}
				input[ipos] = ichar;
				if (ipos < ilen)
					ipos++;
			}
			break;
		}
	}
	while (!toret);
	setcursor(CURSOR_NORMAL);
	gotoxy(curx, cury);
	return toret;
}
