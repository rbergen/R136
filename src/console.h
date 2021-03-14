#pragma once
#include "r136.h"

void clear_line(WINDOW* win);
int get_string_input(WINDOW* win, const char* allowed_characters, char* input, int input_y, int input_x, int force_case, int enable_escape, int enable_directionals);
int advanced_scanf(WINDOW* win, int check_input, int length, const char* allowed_characters, const char* format_string, ...);