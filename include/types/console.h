#pragma once

// types/console.h

#if !defined(CURSES_WIDE) && !defined(PDC_WIDE)
#error (PD)Curses must be built with wide-character support
#endif

#include "types/base.h"

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

enum class CursorType : char
{
	off = 0,
	normal = 1,
	block = 2
};

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
	std::map<Color, std::unique_ptr<ColorSet>> color_sets;
	void add(Color color, short foreground, short background, chtype style);
	void add(Color color, short foreground, short background);
	void add(std::unique_ptr<ColorSet> set);

public:
	chtype get_attrs(Color color);
	void initialize();
};

class Window
{
	friend class Console;

	bool has_line_ended;
	bool have_empty_line;

	template<class TChar>
	void print_centered_template(const std::basic_string<TChar>& str);

	template<class TChar>
	void print_template(const std::basic_string<TChar>& text, TChar space, TChar line_break);

protected:
	static const char new_line = '\n';
	static const wchar_t wnew_line = L'\n';

	WINDOW* wnd;
	Color standard_color;
	bool notify_console_of_resize;

	Window(WINDOW* wnd);
	Window(WINDOW* wnd, bool enable_keypad);
	Window(WINDOW* wnd, Color standard_color);
	Window(WINDOW* wnd, bool enable_keypad, Color standard_color);

	template<class TChar>
	const std::basic_string<TChar> replace(const std::basic_string<TChar>& format, const std::basic_string<TChar>& tag, const std::basic_string<TChar>& value);

	template<class TChar>
	void check_line_ends(const std::basic_string<TChar>& text, TChar c);

	void resize(int height, int width);
	void move(int y, int x, int height, int width);
	void set_color(Color color);
	void unset_color(Color color);
	void get_position(int& y, int& x);
	int get_x();
	int get_y();
	int get_width();
	void set_position(int y, int x);
	void clear_line();
	void register_line_end();
	void clear_line_end();
	void set_scrollable(bool enable);
	int get_string_input(const string& allowed_characters, string& input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals);

public:
	void clear();
	void clear(Color color);
	void set_attribute(chtype attr);
	void unset_attribute(chtype attr);
	void refresh();
	void get_size(int& y, int& x);
	
	void print(const string& format, const string& value);
	void print(const wstring& format, const wstring& value);

	int print(char c);
	int print(wchar_t c);

	int print_line(const string& text);
	int print_line(const wstring& text);

	void print(const string& text);
	void print(const wstring& text);

	void print_centered(const string& text);
	void print_centered(const wstring& text);

	void print(int y, int x, Color color, const wstring* block, int rowcount);
	void print(int y, int x, Color color, const wstring* block, int topy, int leftx, int bottomy, int rightx);
	void print(int y, int x, Color color, const wstring& text);
	
	bool end_line();
	bool empty_line();

	void wait_for_key(bool prompt = false, Language language = static_cast<Language>(0));
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
	CursorType cursor;

	Window& banner();

	void setup_windows(Language language = Language::undefined);

public:
	Console();
	~Console();

	Window& fullscreen();
	Window& main();
	InputWindow& input();

	void process_resize();
	void initialize(Language language);
	void set_language(Language language);
	void release();
	CursorType get_cursor();
	void set_cursor(CursorType type);
};

extern ColorMap color_map;
extern Console console;

