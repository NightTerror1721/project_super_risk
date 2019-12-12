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


	class UniqueID
	{
	private:
		int64_t _code;

	public:
		UniqueID(const int64_t value);
		UniqueID(const UniqueID& value);

		UniqueID& operator= (const UniqueID& value);
		UniqueID& operator= (const int64_t value);

		bool operator== (const UniqueID& value) const;
		bool operator!= (const UniqueID& value) const;
		bool operator> (const UniqueID& value) const;
		bool operator< (const UniqueID& value) const;
		bool operator>= (const UniqueID& value) const;
		bool operator<= (const UniqueID& value) const;

		bool operator! () const;
		operator bool() const;

		operator int64_t() const;

		bool isValid() const;
		int64_t getCode() const;

	public:
		static const UniqueID Invalid;

	};

	class UniqueIDGenerator
	{
	private:
		int64_t _value;

	public:
		UniqueIDGenerator();

		UniqueIDGenerator& operator>> (UniqueID& value);

		UniqueID next();
		UniqueID current() const;
	};
}
