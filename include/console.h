#pragma once

#include "r136.h"
#include <locale.h>
#include <map>
#include <stdexcept>

/* Value that determines the settings for Insert for all functions.
	== 0: Insert off at start, use block cursor to indicate Insert on.
	== 1: Insert on at start, use block cursor to indicate Insert on.
	== 2: Insert off at start, use block cursor to indicate Insert off.
	== 3: Insert on at start, use block cursor to indicate Insert off. */
constexpr int insert_flag = 3;

class ColorSet
{
	static std::map<Color, ColorSet*> color_sets;

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
		value(),
		is_initialized(false)
	{}

	void initialize();

	chtype get_attrs();

	static void add(Color c, short fg, short bg, chtype s);

	static void add(Color c, short fg, short bg);

	static void add(ColorSet set);

	static chtype get_attrs(Color color);
};

void clear_line(WINDOW* win);
int get_string_input(WINDOW* win, const char* allowed_characters, char* input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals);
int advanced_scanf(WINDOW* win, int check_input, int length, const char* allowed_characters, const char* format_string, ...);