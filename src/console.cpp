/***************************************************************************
 * Includes necessary for functions to work
 ***************************************************************************/
#include "console.h"
#include <locale.h>
#include <map>

/***************************************************************************
 * #defines of constants used by the functions
 ***************************************************************************/

enum class Key : char {
	kEscape = -2,
	kEnter = 5,
	up = 8,
	down = 2,
	kTab = 6,
	kShiftTab = 4
};

/* Value that determines the settings for Insert for all functions.
	== 0: Insert off at start, use block cursor to indicate Insert on.
	== 1: Insert on at start, use block cursor to indicate Insert on.
	== 2: Insert off at start, use block cursor to indicate Insert off.
	== 3: Insert on at start, use block cursor to indicate Insert off. */
constexpr int insert_flag = 3;

class ColorSet 
{
	static std::map<Color, ColorSet> color_sets;

	Color color;
	short foreground, background;
	chtype style, value;
	bool is_initialized;

public:
	ColorSet(Color c, short fg, short bg) : ColorSet(c, fg, bg, 0) {}

	ColorSet(Color c, short fg, short bg, chtype s) :
		color(c),
		foreground(fg),
		background(bg),
		style(s),
		is_initialized(false)
	{}

	void initialize() 
	{
		auto color_value = to_value(color);
		init_pair(color_value, foreground, background);
		value = COLOR_PAIR(color_value) | style;

		is_initialized = true;
	}

	chtype get_attrs()
	{
		if (!is_initialized)
			initialize();

		return value;
	}

	static void add(Color c, short fg, short bg, chtype s)
	{
		add(ColorSet(c, fg, bg, s));
	}

	static void add(Color c, short fg, short bg)
	{
		add(ColorSet(c, fg, bg));
	}

	static void add(ColorSet set) 
	{
		color_sets[set.color] = set;
	}

	static chtype get_attrs(Color color) 
	{
		return color_sets[color].get_attrs();
	}
};

WINDOW* banner_window = NULL;
WINDOW* main_window = NULL;
WINDOW* input_window = NULL;
WINDOW* full_screen = NULL;


 /***************************************************************************
  * Definitions of the functions
  ***************************************************************************/

void setup_windows()
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

	wattron(banner_window, ColorSet::get_attrs(Color::banner));
	wmove(banner_window, 0, 0);
	write_centered(banner_window, "Missiecode: R136");

	scrollok(main_window, true);

	wrefresh(banner_window);
	wrefresh(main_window);
	wrefresh(input_window);
}

int print_to_main_window(const char* format, ...)
{
	va_list args;
	int return_value;

	va_start(args, format);
	return_value = vw_printw(main_window, format, args);
	va_end(args);

	return return_value;
}

int write_to_main_window(const wchar_t* text)
{
	return waddwstr(main_window, text);
}

void initialize_colors()
{
	start_color();

	ColorSet::add(Color::bold, COLOR_WHITE, COLOR_BLACK, A_BOLD);
	ColorSet::add(Color::banner, COLOR_RED, COLOR_BLACK, A_UNDERLINE);
	ColorSet::add(Color::error, COLOR_RED, COLOR_BLACK, A_BOLD);
	ColorSet::add(Color::inverse, COLOR_BLACK, COLOR_WHITE);
	ColorSet::add(Color::inverse_red, COLOR_RED, COLOR_WHITE, A_BOLD);
	ColorSet::add(Color::normal, COLOR_WHITE, COLOR_BLACK);
}

void initialize_console()
{
	setlocale(LC_ALL, "");

	initscr();
	noecho();
	keypad(stdscr, true);

	full_screen = stdscr;
	
	initialize_colors();
}

void release_console()
{
	if (input_window)
		delwin(input_window);

	if (main_window)
		delwin(main_window);

	if (banner_window)
		delwin(banner_window);

	endwin();
}

void print_fullscreen_block(int y, int x, Color colors, const wchar_t** block, int rowcount) 
{
	wattron(full_screen, ColorSet::get_attrs(colors));
	
	for (int i  = 0; i < rowcount; i++)
		mvwaddwstr(full_screen, y + i, x, block[i]);

	wattroff(full_screen, ColorSet::get_attrs(colors));
}

void print_fullscreen_block_section(int y, int x, Color color, const wchar_t** block, int topy, int leftx, int bottomy, int rightx)
{
	wattron(full_screen, ColorSet::get_attrs(color));

	for (int i = topy; i <= bottomy; i++)
		mvwaddnwstr(full_screen, y + i - topy, x,& block[i][leftx], rightx - leftx + 1);

	wattroff(full_screen, ColorSet::get_attrs(color));
}


void print_fullscreen(int y, int x, Color color, const wchar_t* text) 
{
	wattron(full_screen, ColorSet::get_attrs(color));
	mvwaddwstr(full_screen, y, x, text);
	wattroff(full_screen, ColorSet::get_attrs(color));
}

void clear_fullscreen(Color colors) 
{
	wbkgd(full_screen, ColorSet::get_attrs(colors));
	werase(full_screen);
}

void update_fullscreen()
{
	wrefresh(full_screen);
}

void clear_window()
{
	werase(main_window);
}

void get_fullscreen_size(int& y, int& x)
{
	getmaxyx(full_screen, y, x);
}

void wait_for_key_core(WINDOW* window, bool do_setup) 
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
				setup_windows();
		}
		else
			break;
	}
}

void wait_for_fullscreen_key()
{
	wait_for_key_core(full_screen, false);
}

void wait_for_key()
{
	wait_for_key_core(main_window, true);
}

void write_centered(WINDOW* win, const char* str)
{
	int winwidth = getmaxx(win);
	int strlength = strlen(str);

	clear_line(win);

	int x = (winwidth - strlength) / 2;
	mvwaddstr(win, getcury(win), x < 0 ? 0 : x, str);
}

void get_command_string(char* input, int max_length) 
{
	memset(input, ' ', max_length);
	input[max_length] = 0;

	wrefresh(main_window);

	wmove(input_window, 0, 0);
	clear_line(input_window);

	wattron(input_window, ColorSet::get_attrs(Color::bold));
	waddstr(input_window, "> ");

	get_string_input(input_window, " abcdefghijklmnopqrstuvwxyz", input, 0, getcurx(input_window), -1, 0, 0);

	clear_line(input_window);
	wmove(input_window, 0, 0);

	wattroff(input_window, ColorSet::get_attrs(Color::bold));
}

void print_command_string(const char* format, ...)
{
	wmove(input_window, 0, 0);
	clear_line(input_window);

	va_list args;

	wattron(input_window, ColorSet::get_attrs(Color::error));

	va_start(args, format);
	vw_printw(input_window, format, args);
	va_end(args);

	wattroff(input_window, ColorSet::get_attrs(Color::error));

	wrefresh(input_window);
	wgetch(input_window);
}

int advanced_getchar(const char* allowed)
{  
	char input = 0;
	int y = getcury(main_window);
	int x = getcurx(main_window);

	wattron(main_window, ColorSet::get_attrs(Color::bold));

	do
	{  
		wmove(main_window, y, x);

		if (advanced_scanf(main_window, 0, 1, allowed, "%c",& input) == to_value(Key::kEscape))
			input = to_value(Key::kEscape);
	}
	while (input == ' ');

	wattroff(main_window, ColorSet::get_attrs(Color::bold));

	return input;
}

int advanced_scanf(WINDOW* win, int check_input, int length, const char* allowed_characters, const char* format_string, ...)
{  
	va_list argp;
	char* input_string;
	int result = 0;

	input_string =  new char[length + 1];

	if (!input_string)
		return to_value(Key::kEscape);

	do
	{  
		memset(input_string, ' ', length);
		if (!((result = get_string_input(win, allowed_characters, input_string, getcury(win), getcurx(win), 0, 1, 0)) == to_value(Key::kEscape)))
		{  
			va_start(argp, format_string);
			result = vsscanf(input_string, format_string, argp);
			va_end(argp);
		}
	}
	while (check_input && (result == EOF || !result));

	delete[] input_string;

	return result;
}

void clear_line(WINDOW* win) 
{
	wmove(win, getcury(win), 0);
	wclrtoeol(win);
}

int get_string_input (WINDOW* win, const char* allowed_characters, char* input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals)
{
	static bool insert_on = 0;
	int input_length, input_pos = 0, result = 0, current_x, current_y;
	int input_char;

	input_length = (int)strlen(input) - 1;
	current_x = getcurx(win);
	current_y = getcury(win);

	insert_on = insert_flag & 1;

	do
	{  
		wmove(win, input_y, input_x + input_pos);
		wrefresh(input_window);

		input_char = wgetch(win);

		switch (input_char)
		{
		case KEY_RESIZE:
			resize_term(0, 0);
			setup_windows();

			break;

		case KEY_LEFT: /* Arrow left */
			if (input_pos)
				input_pos--;

			break;

		case KEY_RIGHT: /* Arrow right */
			if (input_pos < input_length)
				input_pos++;

			break;

		case KEY_HOME: /* Home */
			input_pos = 0;

			break;

		case KEY_END: /* End */
			input_pos = input_length;

			if (input[input_pos] == ' ')
				while (input_pos && input[input_pos - 1] == ' ')
					input_pos--;

			break;

		case KEY_IC: /* Insert */
			insert_on = !insert_on;

		case KEY_DC: /* Delete */
			memmove(input + input_pos, input + input_pos + 1, (size_t)input_length - input_pos);

			input[input_length] = ' ';
			wdelch(win);

			break;

		case KEY_UP: /* Arrow up */
			if (enable_directionals)
				result = to_value(Key::up);

			break;

		case KEY_DOWN: /* Arrow down */
			if (enable_directionals)
				result = to_value(Key::down);

			break;

		case KEY_BTAB: /* Shift-Tab */
			if (enable_directionals)
				result = to_value(Key::kShiftTab);

			break;

		case KEY_BACKSPACE: /* Backspace */
			#ifdef __APPLE__
			case 127:
			#else
			case 8:
			#endif

			if (input_pos)
			{  
				memmove(input + input_pos - 1, input + input_pos, (size_t)input_length - input_pos + 1);
				input[input_length] = ' ';
				mvwdelch(win, input_y, input_x + --input_pos);
			}

			break;

		case KEY_STAB: /* Tab */

			if (enable_directionals)
				result = to_value(Key::kTab);

			break;

		case KEY_ENTER: /* Enter */
		case 10:
			result = to_value(Key::kEnter);
			break;

		case 27: /* Escape */
			if (enable_escape)
				result = to_value(Key::kEscape);
			else
			{
				memset(input, ' ', input_length);
				mvwaddstr(win, input_y, input_x, input);
				input_pos = 0;
			}

			break;

		default:
			if (force_case > 0)
				input_char = toupper(input_char);
			else if (force_case < 0)
				input_char = tolower(input_char);

			if (strchr(allowed_characters, input_char))
			{  
				if (insert_on)
				{  
					memmove(input + input_pos + 1, input + input_pos, (size_t)input_length - input_pos);

					mvwdelch(win, input_y, input_x + input_length);
					mvwinsch(win, input_y, input_x + input_pos, input_char);
				}
				else 
					waddch(win, input_char);

				input[input_pos] = input_char;

				if (input_pos < input_length)
					input_pos++;
			}

			break;
		}
	}
	while (!result);
//	setcursor(CURSOR_NORMAL);

	if (input_pos == input_length) 
		current_x++;

	wmove(win, current_y, current_x);

	return result;
}
