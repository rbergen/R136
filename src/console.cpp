#include "r136.h"
#include "console.h"
#include <stdexcept>
#include <clocale>
#include <cstring>

ColorMap color_map;
Console console;

enum class Key : char 
{
	kEscape = -2,
	kEnter = 5,
	up = 8,
	down = 2,
	kTab = 6,
	kShiftTab = 4
};

void ColorSet::initialize()
{
	auto color_value = to_value(color);
	init_pair(color_value, foreground, background);
	value = COLOR_PAIR(color_value) | style;

	is_initialized = true;
}

ColorMap::~ColorMap()
{
	for (auto element = color_sets.begin(); element != color_sets.end();) 
	{
		delete element->second;
		element = color_sets.erase(element);
	}
}

void ColorMap::initialize()
{
	start_color();

	add(Color::bold, COLOR_WHITE, COLOR_BLACK, A_BOLD);
	add(Color::banner, COLOR_RED, COLOR_BLACK, A_UNDERLINE);
	add(Color::error, COLOR_RED, COLOR_BLACK, A_BOLD);
	add(Color::inverse, COLOR_BLACK, COLOR_WHITE);
	add(Color::inverse_red, COLOR_RED, COLOR_WHITE, A_BOLD);
	add(Color::normal, COLOR_WHITE, COLOR_BLACK);
}

int Window::scanf(int check_input, int length, const char* allowed_characters, const char* format_string, ...)
{
	va_list argp;
	char* input_string;
	int result = 0;

	input_string = new char[length + 1];

	if (!input_string)
		return to_value(Key::kEscape);

	input_string[length] = 0;
	do
	{
		memset(input_string, ' ', length);
		if (!((result = get_string_input(allowed_characters, input_string, get_y(), get_x(), 0, 1, 0)) == to_value(Key::kEscape)))
		{
			va_start(argp, format_string);
			result = vsscanf(input_string, format_string, argp);
			va_end(argp);
		}
	} while (check_input && (result == EOF || !result));

	delete[] input_string;

	return result;
}

Window::Window(WINDOW* wnd, bool enable_keypad, Color standard_color) :
	wnd(wnd),
	standard_color(standard_color),
	notify_console_of_resize(true)
{
	keypad(wnd, enable_keypad);
	touchwin(wnd);
}

int Window::get_string_input(const char* allowed_characters, char* input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals)
{
	static bool insert_on = 0;
	int input_length, input_pos = 0, result = 0, current_x, current_y;
	int input_char;

	input_length = (int)strlen(input) - 1;
	get_position(current_y, current_x);

	insert_on = insert_flag & 1;

	do
	{
		set_position(input_y, input_x + input_pos);
		refresh();

		input_char = wgetch(wnd);

		switch (input_char)
		{
		case KEY_RESIZE:
			resize_term(0, 0);

			if (notify_console_of_resize)
				console.process_resize();

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
			break;

		case KEY_DC: /* Delete */
			memmove(input + input_pos, input + input_pos + 1, (size_t)input_length - input_pos);

			input[input_length] = ' ';
			wdelch(wnd);

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
			if (!input_pos)
				break;

			memmove(input + input_pos - 1, input + input_pos, (size_t)input_length - input_pos + 1);
			input[input_length] = ' ';

			set_position(input_y, input_x + --input_pos);
			wdelch(wnd);

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
				set_position(input_y, input_x);
				print(input);
				input_pos = 0;
			}

			break;

		default:
			if (force_case > 0)
				input_char = toupper(input_char);
			else if (force_case < 0)
				input_char = tolower(input_char);

			if (!strchr(allowed_characters, input_char))
				break;

			if (insert_on)
			{
				memmove(input + input_pos + 1, input + input_pos, (size_t)input_length - input_pos);

				set_position(input_y, input_x + input_length);
				wdelch(wnd);
				set_position(input_y, input_x + input_pos);
				winsch(wnd, input_char);
			}
			else
				print(input_char);

			input[input_pos] = input_char;

			if (input_pos < input_length)
				input_pos++;

			break;
		}
	} 
	while (!result);

	if (input_pos == input_length)
		current_x++;

	set_position(current_y, current_x);

	return result;
}

void Window::print_centered(const char* str)
{
	set_color(standard_color);

	int winwidth = getmaxx(wnd);
	int strlength = (int)strlen(str);

	clear_line();

	int x = (winwidth - strlength) / 2;
	mvwaddstr(wnd, getcury(wnd), x < 0 ? 0 : x, str);

	unset_color(standard_color);
}

int Window::print(const char* format, ...)
{
	va_list args;
	int return_value;

	va_start(args, format);
	return_value = vw_printw(wnd, format, args);
	va_end(args);

	return return_value;
}

void Window::write_block(int y, int x, Color color, const wchar_t** block, int rowcount)
{
	set_color(color);

	for (int i = 0; i < rowcount; i++)
		mvwaddwstr(wnd, y + i, x, block[i]);

	unset_color(color);
}

void Window::write_block(int y, int x, Color color, const wchar_t** block, int topy, int leftx, int bottomy, int rightx)
{
	set_color(color);

	for (int i = topy; i <= bottomy; i++)
		mvwaddnwstr(wnd, y + i - topy, x, &block[i][leftx], rightx - leftx + 1);

	unset_color(color);
}

void Window::write(int y, int x, Color color, const wchar_t* text)
{
	set_color(color);

	set_position(y, x);
	write(text);

	unset_color(color);
}

void Window::wait_for_key(bool prompt)
{
	if (prompt)
	{
		set_color(Color::bold);
		print("[Druk op een toets]");
		unset_color(Color::bold);
	}

	refresh();

	while (true)
	{
		if (wgetch(wnd) == KEY_RESIZE)
		{
			resize_term(0, 0);

			if (notify_console_of_resize)
				console.process_resize();
		}
		else
			break;
	}

	if (prompt)
	{
		set_position(get_y(), 0);
		clear_line();
	}
}

int Window::get_char_input(const char* allowed)
{
	char input = 0;
	int y, x;

	get_position(y, x);

	set_color(Color::bold);

	do
	{
		set_position(y, x);

		if (scanf(0, 1, allowed, "%c", &input) == to_value(Key::kEscape))
			input = to_value(Key::kEscape);
	} 		while (input == ' ');

	unset_color(Color::bold);

	return input;
}

void InputWindow::get_string_input(char* input, int max_length)
{
	memset(input, ' ', max_length);
	input[max_length] = 0;

	console.main().refresh();

	set_position(0, 0);
	clear_line();

	set_color(standard_color);
	print("> ");

	Window::get_string_input(" abcdefghijklmnopqrstuvwxyz", input, 0, get_x(), -1, 0, 0);

	clear_line();
	set_position(0, 0);

	unset_color(standard_color);
}

void InputWindow::print_error(const char* format, ...)
{
	set_position(0, 0);
	clear_line();

	va_list args;

	set_color(Color::error);

	print("< ");

	va_start(args, format);
	vw_printw(wnd, format, args);
	va_end(args);

	unset_color(Color::error);

	refresh();
	wait_for_key();
}

void Console::setup_windows()
{
	int height, width;

	if (!fullscreen_window)
	{
		fullscreen_window = new Window(stdscr, true);
		fullscreen_window->notify_console_of_resize = false;
	}

	fullscreen_window->get_size(height, width);

	if (banner_window)
		banner_window->resize(2, width);
	else
		banner_window = new Window(subwin(stdscr, 2, width, 0, 0), Color::banner);

	if (main_window)
		main_window->resize(height - 3, width);
	else
		main_window = new Window(subwin(stdscr, height - 3, width, 2, 0), true);

	if (input_window)
		input_window->move(height - 1, 0, 1, width);
	else
		input_window = new InputWindow(subwin(stdscr, 1, width, height - 1, 0));

	banner_window->set_position(0, 0);
	banner_window->print_centered("Missiecode: R136");

	main_window->set_scrollable(true);

	banner_window->refresh();
	main_window->refresh();
	input_window->refresh();
}

void Console::initialize()
{
	setlocale(LC_ALL, "");

	initscr();
	noecho();

	color_map.initialize();

	setup_windows();
}

void Console::release()
{
	if (input_window)
		delwin(input_window->wnd);

	if (main_window)
		delwin(main_window->wnd);

	if (banner_window)
		delwin(banner_window->wnd);

	endwin();

	is_released = true;
}

