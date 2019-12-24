#pragma once

#include <algorithm>
#include <string>
#include <cctype>
#include <type_traits>

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


template<class _Ty>
class Accessor
{
private:
	_Ty* _ptr;

public:
	inline Accessor(_Ty* ptr) :
		_ptr{ ptr }
	{}

	inline Accessor<_Ty> operator= (const Accessor<_Ty>& a)
	{
		_ptr = a._ptr;
		return *this;
	}

	inline bool operator== (const Accessor<_Ty>& a) const { return _ptr == a._ptr; }
	inline bool operator!= (const Accessor<_Ty>& a) const { return _ptr != a._ptr; }
	inline bool operator> (const Accessor<_Ty>& a) const { return _ptr > a._ptr; }
	inline bool operator< (const Accessor<_Ty>& a) const { return _ptr < a._ptr; }
	inline bool operator>= (const Accessor<_Ty>& a) const { return _ptr >= a._ptr; }
	inline bool operator<= (const Accessor<_Ty>& a) const { return _ptr <= a._ptr; }

	inline operator bool() const { return _ptr; }
	inline bool operator! () const { return !_ptr; }

	inline _Ty* operator-> () { return _ptr; }
	inline const _Ty* operator-> () const { return _ptr; }

	inline const _Ty* operator* () const { return _ptr; }

	template<class _Ty2>
	inline operator Accessor<_Ty2>()
	{
		static_assert(std::is_convertible(_Ty2, _Ty) || std::is_base_of(_Ty, _Ty2));
		return { reinterpret_cast<_Ty2*>(_ptr) };
	}

	template<class _Ty, class _Ty2>
	inline Accessor<_Ty2> safe_cast() { return { dynamic_cast<_Ty2*>(_ptr) }; }

	template<class _Ty, class _Ty2>
	inline Accessor<_Ty2> unsafe_cast() { return static_cast<Accessor<_Ty2>>(*this); }
};
