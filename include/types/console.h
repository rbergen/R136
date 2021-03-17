#pragma once

// types/console.h

#if !defined(CURSES_WIDE) && !defined(PDC_WIDE)
#error (PD)Curses must be built with wide-character support
#endif

#include "types/r136.h"

// Figure out which (name)curses header to include
#ifdef HAVE_NCURSES_NCURSES_H
#include <ncursesw/ncurses.h>
#elif HAVE_NCURSES_CURSES_H 
#include <ncursesw/curses.h>
#elif HAVE_NCURSES_H
#include <ncurses.h>
#else
#include <curses.h>
#endif

class ColorSet
{
	Color color;
	short foreground, background;
	chtype style, value;
	bool is_initialized;

public:
	ColorSet(Color color, short foreground, short background);
	ColorSet(Color color, short foreground, short background, chtype style);
	void initialize();
	Color get_color();
	chtype get_attrs();
};

class ColorMap
{
	std::map<Color, ColorSet*> color_sets;
	void add(Color color, short foreground, short background, chtype style);
	void add(Color color, short foreground, short background);
	void add(ColorSet* set);

public:
	~ColorMap();

	chtype get_attrs(Color color);
	void initialize();
};

class Window
{
	friend class Console;

protected:
	WINDOW* wnd;
	Color standard_color;
	bool notify_console_of_resize;

	Window(WINDOW* wnd);
	Window(WINDOW* wnd, bool enable_keypad);
	Window(WINDOW* wnd, Color standard_color);
	Window(WINDOW* wnd, bool enable_keypad, Color standard_color);

	template<class TChar>
	const std::basic_string<TChar> replace(const std::basic_string<TChar>& format, const std::basic_string<TChar>& tag, const std::basic_string<TChar>& value);

	void resize(int height, int width);
	void move(int y, int x, int height, int width);
	void set_color(Color color);
	void unset_color(Color color);
	void get_position(int& y, int& x);
	int get_x();
	int get_y();
	void set_position(int y, int x);
	void clear_line();
	void set_scrollable(bool enable);
	int get_string_input(const string& allowed_characters, string& input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals);

public:
	void clear();
	void clear(Color color);
	void set_attribute(chtype attr);
	void unset_attribute(chtype attr);
	void refresh();
	void get_size(int& y, int& x);
	void print_centered(const string& str);

	int print(const string& format, const string& value);
	int print(const wstring& format, const wstring& value);

	int print(char c);
	int print(const string& text);
	int print(const wstring& text);

	void print(int y, int x, Color color, const wstring* block, int rowcount);
	void print(int y, int x, Color color, const wstring* block, int topy, int leftx, int bottomy, int rightx);
	void print(int y, int x, Color color, const wstring& text);
	void wait_for_key(bool prompt = false);
	int get_char_input(const string& allowed);
};

class InputWindow : protected Window
{
	friend class Console;

	InputWindow(WINDOW* wnd);

	template<class TChar>
	void print_error_template(const std::basic_string<TChar>& text);

public:
	void get_string_input(string& input);

	void print_error(const string& format, const string& value);
	void print_error(const wstring& format, const wstring& value);

	void print_error(const string& text);
	void print_error(const wstring& text);

};

class Console
{
	Window* fullscreen_window;
	Window* main_window;
	Window* banner_window;
	InputWindow* input_window;
	bool is_released;

	Window& banner();

	void setup_windows();

public:
	Console();
	~Console();

	Window& fullscreen();
	Window& main();
	InputWindow& input();

	void process_resize();
	void initialize();
	void release();
};

extern ColorMap color_map;