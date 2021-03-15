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
	~ColorMap();

	std::map<Color, ColorSet*> color_sets;

	void add(Color color, short foreground, short background, chtype style);

	void add(Color color, short foreground, short background);

	void add(ColorSet* set);

public:
	chtype get_attrs(Color color);

	void initialize();
};