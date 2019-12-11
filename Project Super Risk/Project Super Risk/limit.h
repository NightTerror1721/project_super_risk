#pragma once

#include <algorithm>
#include <string>
#include <cctype>

namespace utils
{
	using std::max;
	using std::min;

	template<class _Ty>
	inline _Ty&& range(_Ty&& min, _Ty&& value, _Ty&& max)
	{
		return utils::min(max, utils::max(min, value));
	}

	bool is_blank(const std::string& s);

	inline const std::string& non_blank(const std::string& s, const std::string& default_value = "")
	{
		return utils::is_blank(s) ? default_value : s;
	}
}



bool utils::is_blank(const std::string& s)
{
	if (s.empty())
		return true;

	for (const char* s_ptr = s.data(); *s_ptr != '\0'; ++s_ptr)
		if (!std::isblank(*s_ptr))
			return false;
	return true;
}
