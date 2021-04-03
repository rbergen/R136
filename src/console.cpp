#include "base.h"
#include "console.h"
#include <stdexcept>
#include <clocale>
#include <cstring>

ColorMap color_map;
Console console;

enum class Key : char 
{
	escape = -2,
	enter = 5,
	up = 8,
	down = 2,
	tab = 6,
	shift_tab = 4
};

void ColorSet::initialize()
{
	auto color_value = to_value(color);
	init_pair(color_value, foreground, background);
	value = COLOR_PAIR(color_value) | style;

	is_initialized = true;
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

Window::Window(WINDOW* wnd, bool enable_keypad, Color standard_color) :
	wnd(wnd),
	standard_color(standard_color),
	notify_console_of_resize(true),
	has_line_ended(true),
	have_empty_line(true)
{
	keypad(wnd, enable_keypad);
	touchwin(wnd);
}

int Window::get_string_input(const string& allowed_characters, string& input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals)
{
	static bool insert_on = 0;
	int input_pos = 0;
	int result = 0, current_x, current_y;
	int input_char;

	int input_length = (int)input.length();
	get_position(current_y, current_x);

	insert_on = insert_flag & 1;

	do
	{
		console.set_cursor(insert_on ? CursorType::normal : CursorType::block);
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
			if (input_pos < input_length - 1)
				input_pos++;

			break;

		case KEY_HOME: /* Home */
			input_pos = 0;

			break;

		case KEY_END: /* End */
			input_pos = input_length - 1;

			if (input[input_pos] == ' ')
				while (input_pos && input[(size_t)input_pos - 1] == ' ')
					input_pos--;

			break;

		case KEY_IC: /* Insert */
			insert_on = !insert_on;
			break;

		case KEY_DC: /* Delete */
			input.erase(input_pos, 1);
			input += ' ';
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
				result = to_value(Key::shift_tab);

			break;

		case KEY_BACKSPACE: /* Backspace */
#ifdef __APPLE__
		case 127:
#else
		case 8:
#endif
			if (!input_pos)
				break;

			input.erase((size_t)input_pos - 1, 1);
			input += ' ';

			set_position(input_y, input_x + --input_pos);
			wdelch(wnd);

			break;

		case KEY_STAB: /* Tab */
			if (enable_directionals)
				result = to_value(Key::tab);

			break;

		case KEY_ENTER: /* Enter */
		case 10:
			result = to_value(Key::enter);
			break;

		case 27: /* Escape */
			if (enable_escape)
				result = to_value(Key::escape);
			else
			{
				input.assign(' ', input_length);
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

			if (allowed_characters.find(input_char) == string::npos)
				break;

			if (insert_on)
			{
				input.insert(input_pos, 1, input_char);
				input.erase(input_length);

				set_position(input_y, input_x + input_length - 1);
				wdelch(wnd);
				set_position(input_y, input_x + input_pos);
				winsch(wnd, input_char);
			}
			else 
			{
				input[input_pos] = input_char;
				print((char)input_char);
			}

			if (input_pos < input_length - 1)
				input_pos++;

			break;
		}
	} 
	while (!result);

	if (input_pos == input_length - 1)
		current_x++;

	set_position(current_y, current_x);

	clear_line_end();
	console.set_cursor(CursorType::normal);

	return result;
}

void Window::print(int y, int x, Color color, const wstring* block, int rowcount)
{
	set_color(color);

	for (int i = 0; i < rowcount; i++)
	{
		set_position(y + i, x);
		print_line(block[i]);
	}

	unset_color(color);
}

void Window::print(int y, int x, Color color, const wstring* block, int top_y, int left_x, int bottom_y, int right_x)
{
	set_color(color);

	for (int i = top_y; i <= bottom_y; i++)
	{
		set_position(y + i - top_y, x);
		print_line(block[i].substr(left_x, (size_t)right_x - left_x + 1));
	}

	unset_color(color);
}

void Window::print(int y, int x, Color color, const wstring& text)
{
	set_color(color);

	set_position(y, x);
	print_line(text);

	unset_color(color);
}

void Window::wait_for_key(bool prompt)
{
	if (prompt)
	{
		empty_line();
		set_color(Color::bold);
		print("[Druk op een toets]");
		unset_color(Color::bold);
	}

	refresh();

	console.set_cursor(CursorType::off);

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

	console.set_cursor(CursorType::normal);

	if (prompt)
	{
		set_position(get_y(), 0);
		clear_line();
		register_line_end();
	}
}

int Window::get_char_input(const string& allowed)
{
	refresh();

	int y, x;
	get_position(y, x);

	set_color(Color::bold);

	string input = " ";

	do
	{
		set_position(y, x);

		get_string_input(allowed, input, y, x, 0, false, false);
		
	} 	
	while (input[0] == ' ');

	unset_color(Color::bold);

	return input[0];
}

void InputWindow::get_string_input(string& input)
{
	int max_length = (int)input.length();

	console.main().refresh();

	set_position(0, 0);
	clear_line();

	set_color(standard_color);
	print("> ");

	Window::get_string_input(" abcdefghijklmnopqrstuvwxyz", input, 0, get_x(), -1, false, false);

	clear_line();
	set_position(0, 0);

	unset_color(standard_color);
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

