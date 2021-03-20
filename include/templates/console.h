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

	if (text.back() != c)
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
			is_empty_line = false;
	}
}

template<class TChar>
void Window::print_centered_template(const std::basic_string<TChar>& str)
{
	set_color(standard_color);

	int win_width = getmaxx(wnd);
	int str_length = (int)str.length();

	clear_line();

	int x = (win_width - str_length) / 2;
	set_position(get_y(), x < 0 ? 0 : x);
	print(str);

	unset_color(standard_color);
}

template<class TChar>
void Window::print_template(const std::basic_string<TChar>& text, TChar space, TChar line_break)
{
	std::basic_string<TChar> copy = text;
	int width = getmaxx(wnd);
	size_t break_index;

	while (copy.length() > (width - get_x()))
	{
		break_index = copy.find(line_break);

		if (break_index == string::npos || break_index > (width - get_x()))
			break_index = copy.find_last_of(space, width - get_x());
	
		if (break_index == string::npos) 
		{
			if (get_x() == 0)
				break_index = width;
			else
			{
				print(line_break);
				continue;
			}
		}

		print_line(copy.substr(0, break_index));

		if (break_index != width)
			print(line_break);

		copy.erase(0, break_index + 1);
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

