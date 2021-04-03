#include "types/console.h"

// templates/console.h

template<class TChar>
const std::basic_string<TChar> Window::replace(const std::basic_string<TChar>& format, const std::basic_string<TChar>& tag, const std::basic_string<TChar>& value)
{
	size_t search_pos = 0;
	size_t tag_pos = string::npos;

	std::basic_string<TChar> result;
	bool found = false;

	while (true)
	{
		tag_pos = format.find(tag, search_pos);
		if (tag_pos == std::basic_string<TChar>::npos)
			return found ? result : format;

		if (!found) 
		{
			found = true;
			result = std::basic_string<TChar>(format);
		}

		result.replace(tag_pos, 3, value);
		search_pos = tag_pos + value.size();
	}
}

template<class TChar>
void Window::check_line_ends(const std::basic_string<TChar>& text, TChar c)
{
	if (text.empty())
		return;

	// line break can be explicit (through c), or implicit because the text on the last line of output is as wide as the window
	if (text.back() != c && (text.length() + get_x()) % get_width())
	{
		clear_line_end();
		return;
	}

	register_line_end();

	if (text.length() > 1)
	{
		if (text[text.length() - 2] == c)
			register_line_end();
		else
			have_empty_line = false;
	}
}

template<class TChar>
void Window::print_centered_template(const std::basic_string<TChar>& text)
{
	set_color(standard_color);

	clear_line();

	int x = (get_width() - (int)text.length()) / 2;
	set_position(get_y(), x < 0 ? 0 : x);
	print(text);

	unset_color(standard_color);
}

template<class TChar>
void Window::print_template(const std::basic_string<TChar>& text, TChar space, TChar line_break)
{
	std::basic_string<TChar> copy = text;
	int width = get_width();
	size_t break_index;

	// we may not be at the start of the line
	size_t remaining_width = (size_t)width - get_x();
	while (copy.length() > remaining_width)
	{
		// find the first line break within remaining width, or the last space if there is none
		break_index = copy.find(line_break);
		if (break_index == string::npos || break_index > remaining_width)
			break_index = copy.find_last_of(space, remaining_width);
	
		// check if we have an uninterrupted character sequence that surpasses remaining width
		if (break_index == string::npos) 
		{
			// if so, try again on a new line or make a hard cut at window width if this already is one
			if (get_x() == 0)
				break_index = width;
			else
			{
				print(line_break);
				remaining_width = width;
				continue;
			}
		}

		// print the line we found (terminated by a line break, a space, or a hard cut), adding a line break if necessary 
		print_line(copy.substr(0, break_index));
		if (break_index != width)
			print(line_break);

		remaining_width = width;

		copy.erase(0, break_index);

		// remove the break character, unless we made a hard cut in an uninterrupted character sequence
		if (copy.front() == space || copy.front() == line_break)
			copy.erase(0, 1);

		// remove leading spaces in the remaining text
		while (!copy.empty() && copy.front() == space)
			copy.erase(0, 1);
	} 

	if (!copy.empty())
		print_line(copy);
}

template<class TChar>
void InputWindow::print_error_template(const std::basic_string<TChar>& text)
{
	set_position(0, 0);
	clear_line();

	set_color(Color::error);

	print("< ");

	print(text);

	unset_color(Color::error);

	refresh();
	wait_for_key();
}

