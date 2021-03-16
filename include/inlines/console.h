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
	add(new ColorSet(color, foreground, background, style));
}

inline void ColorMap::add(Color color, short foreground, short background)
{
	add(new ColorSet(color, foreground, background));
}

inline void ColorMap::add(ColorSet* set)
{
	auto element = color_sets.find(set->get_color());
	if (element == color_sets.end())
		color_sets.insert(std::make_pair(set->get_color(), set));
	else
		element->second = set;
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

inline void Window::clear(Color color)
{
	wbkgd(wnd, color_map.get_attrs(color));
	werase(wnd);
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

inline void Window::print(char c)
{
	waddch(wnd, c);
}

inline int Window::write(const wchar_t* text)
{
	return waddwstr(wnd, text);
}

inline InputWindow::InputWindow(WINDOW* wnd) : Window(wnd, true, Color::bold) {}

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
