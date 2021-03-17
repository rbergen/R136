#include "types/console.h"

template<class TChar>
const std::basic_string<& Window::replace(const string& format, const string& value)
{
	size_t search_pos = 0;
	size_t tag_pos = string::npos;

	string result;
	bool found = false;

	while (true)
	{
		tag_pos = format.find("{0}", search_pos);
		if (tag_pos == string::npos)
			return found ? format : result;

		if (!found) {
			found = true;
			result = string(format);
		}

		result.replace(tag_pos, 3, value);
		search_pos = tag_pos + value.size();
	}
}

void Window::print(const string& format, const string& value)
{
	print(replace(format, value))
}
