#include "utils.h"

bool utils::is_blank(const std::string& s)
{
	if (s.empty())
		return true;

	for (const char* s_ptr = s.data(); *s_ptr != '\0'; ++s_ptr)
		if (!std::isblank(*s_ptr))
			return false;
	return true;
}


utils::UniqueID::UniqueID(const int64_t value) :
	_code{ utils::max(-1LL, value) }
{}
utils::UniqueID::UniqueID(const UniqueID& value) :
	_code{ utils::max(-1LL, value._code) }
{}

utils::UniqueID& utils::UniqueID::operator= (const UniqueID& value)
{
	_code = utils::max(-1LL, value._code);
	return *this;
}
utils::UniqueID& utils::UniqueID::operator= (const int64_t value)
{
	_code = utils::max(-1LL, value);
	return *this;
}

bool utils::UniqueID::operator== (const UniqueID& value) const { return _code == value._code; }
bool utils::UniqueID::operator!= (const UniqueID& value) const { return _code != value._code; }
bool utils::UniqueID::operator> (const UniqueID& value) const { return _code > value._code; }
bool utils::UniqueID::operator< (const UniqueID& value) const { return _code < value._code; }
bool utils::UniqueID::operator>= (const UniqueID& value) const { return _code >= value._code; }
bool utils::UniqueID::operator<= (const UniqueID& value) const { return _code <= value._code; }

bool utils::UniqueID::operator! () const { return _code < 0; }
utils::UniqueID::operator bool() const { return _code >= 0; }

utils::UniqueID::operator int64_t() const { return _code; }

bool utils::UniqueID::isValid() const { return _code >= 0; }
int64_t utils::UniqueID::getCode() const { return _code; }

const utils::UniqueID utils::UniqueID::Invalid{ -1 };



utils::UniqueIDGenerator::UniqueIDGenerator() :
	_value{ -1 }
{}

utils::UniqueIDGenerator& utils::UniqueIDGenerator::operator>> (UniqueID& value)
{
	value = ++_value;
	return *this;
}

utils::UniqueID utils::UniqueIDGenerator::next() { return { ++_value }; }
utils::UniqueID utils::UniqueIDGenerator::current() const { return { _value }; }
