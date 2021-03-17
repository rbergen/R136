#include "types/console.h"

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

