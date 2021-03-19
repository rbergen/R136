#pragma once

// inlines/console.h

#include "types/console.h"

inline ColorSet::ColorSet(Color color, short foreground, short background) : ColorSet(color, foreground, background, 0) {}

inline ColorSet::ColorSet(Color color, short foreground, short background, chtype style) :
	color(color),
	foreground(foreground),
	background(background),
	style(style),
	value(),
	is_initialized(false)
{}

inline Color ColorSet::get_color()
{
	return color;
}

inline chtype ColorSet::get_attrs()
{
	if (!is_initialized)
		initialize();

	return value;
}

inline void ColorMap::add(Color color, short foreground, short background, chtype style)
{
	add(std::make_unique<ColorSet>(color, foreground, background, style));
}

inline void ColorMap::add(Color color, short foreground, short background)
{
	add(std::make_unique <ColorSet>(color, foreground, background));
}

inline void ColorMap::add(std::unique_ptr<ColorSet> set)
{
	auto element = color_sets.find(set->get_color());
	if (element == color_sets.end())
		color_sets.insert(std::make_pair(set->get_color(), std::move(set)));
	else
		element->second.reset(set.get());
}

inline chtype ColorMap::get_attrs(Color color)
{
	auto element = color_sets.find(color);
	if (element == color_sets.end())
		throw std::out_of_range("color");

	return element->second->get_attrs();
}

inline Window::Window(WINDOW* wnd) : Window(wnd, false, Color::undefined) {}

inline Window::Window(WINDOW* wnd, bool enable_keypad) : Window(wnd, enable_keypad, Color::undefined) {}

inline Window::Window(WINDOW* wnd, Color standard_color) : Window(wnd, false, standard_color) {}

inline void Window::resize(int height, int width)
{
	wresize(wnd, height, width);
	touchwin(wnd);
}

inline void Window::move(int y, int x, int height, int width)
{
	wresize(wnd, height, width);
	mvwin(wnd, y, x);
}

inline void Window::set_color(Color color)
{
	if (color != Color::undefined)
		wattron(wnd, color_map.get_attrs(color));
}

inline void Window::unset_color(Color color)
{
	if (color != Color::undefined)
		wattroff(wnd, color_map.get_attrs(color));
}

inline void Window::get_position(int& y, int& x)
{
	getyx(wnd, y, x);
}

inline int Window::get_x()
{
	return getcurx(wnd);
}

inline int Window::get_y()
{
	return getcury(wnd);
}

inline void Window::set_position(int y, int x)
{
	wmove(wnd, y, x);
}

inline void Window::clear_line()
{
	wmove(wnd, getcury(wnd), 0);
	wclrtoeol(wnd);
	register_line_end();
}

inline void Window::set_scrollable(bool enable)
{
	scrollok(wnd, enable);
}

inline void Window::get_size(int& y, int& x)
{
	getmaxyx(wnd, y, x);
}

inline void Window::clear()
{
	werase(wnd);
}

inline void Window::register_line_end()
{
	if (is_line_ended)
		is_empty_line = true;

	is_line_ended = true;
}

inline void Window::clear(Color color)
{
	wbkgd(wnd, color_map.get_attrs(color));
	werase(wnd);
}

inline void Window::clear_line_end()
{
	is_empty_line = is_line_ended = false;
}

inline void Window::set_attribute(chtype attr)
{
	wattron(wnd, attr);
}

inline void Window::unset_attribute(chtype attr)
{
	wattroff(wnd, attr);
}

inline void Window::refresh()
{
	wrefresh(wnd);
}

inline int Window::print(char c)
{
	if (c == new_line)
		register_line_end();
	else
		clear_line_end();

	return waddch(wnd, c);
}

inline int Window::print(const string& text)
{
	check_line_ends(text, new_line);

	return waddstr(wnd, text.c_str());
}

inline int Window::print(const wstring& text)
{
	check_line_ends(text, wnew_line);

	return waddwstr(wnd, text.c_str());
}

inline void Window::print_centered(const string& text)
{
	print_centered_template(text);
}

inline void Window::print_centered(const wstring& text)
{
	print_centered_template(text);
}

inline int Window::print(const string& format, const string& value)
{
	return print(replace(format, string("{0}"), value));
}

inline int Window::print(const wstring& format, const wstring& value)
{
	return print(replace(format, wstring(L"{0}"), value));
}

inline bool Window::end_line()
{
	if (is_line_ended)
		return false;

	print(new_line);
	return true;
}

inline bool Window::empty_line()
{
	if (is_empty_line)
		return false;

	end_line();
	print(new_line);
	return true;
}

inline InputWindow::InputWindow(WINDOW* wnd) : Window(wnd, true, Color::bold) {}

inline void InputWindow::print_error(const string& format, const string& value)
{
	print_error(replace(format, string("{0}"), value));
}

inline void InputWindow::print_error(const wstring& format, const wstring& value)
{
	print_error(replace(format, wstring(L"{0}"), value));
}

inline void InputWindow::print_error(const string& text)
{
	print_error_template(text);
}

inline void InputWindow::print_error(const wstring& text)
{
	print_error_template(text);
}


inline Console::Console() :
	banner_window(nullptr),
	fullscreen_window(nullptr),
	input_window(nullptr),
	main_window(nullptr),
	is_released(false)
{}

inline Console::~Console()
{
	if (!is_released)
		release();
}

inline Window& Console::banner()
{
	return *banner_window;
}

inline void Console::process_resize()
{
	setup_windows();
}

inline Window& Console::fullscreen()
{
	return *fullscreen_window;
}

inline Window& Console::main()
{
	return *main_window;
}

inline InputWindow& Console::input()
{
	return *input_window;
}
