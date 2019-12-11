#pragma once

#include <nlohmann/json.hpp>
#include <filesystem>
#include<exception>

using Json = nlohmann::json;

namespace json_utils
{
	class JsonException : public std::exception
	{
	public:
		JsonException(const std::string& msg);
	};
}

class JsonSerializable
{
public:
	virtual Json serialize() const = 0;
	virtual void unserialize(const Json& json) = 0;
};

JsonSerializable& operator<< (JsonSerializable& object, const Json& json);
const JsonSerializable& operator>> (const JsonSerializable& object, Json& json);

namespace json_utils
{
	Json read(const std::experimental::filesystem::path& file_path);
	Json read(const std::string& file_path);

	void write(const std::experimental::filesystem::path& file_path, const Json& json);
	void write(const std::string& file_path, const Json& json);


	void inject(JsonSerializable& object, const Json& json);

	Json extract(const JsonSerializable& object);


	void read_and_inject(JsonSerializable& object, const std::experimental::filesystem::path& file_path);
	void read_and_inject(JsonSerializable& object, const std::string& file_path);

	void extract_and_write(const JsonSerializable& object, const std::experimental::filesystem::path& file_path);
	void extract_and_write(const JsonSerializable& object, const std::string& file_path);


	inline bool has(const Json& json, const std::string& name)
	{
		return json.find(name) != json.cend();
	}

	template<class _Ty>
	const _Ty& get_or_default(const Json& json, const std::string& name, const _Ty& default_value)
	{
		auto it = json.find(name);
		return it != json.cend() ? it.value().get<_Ty>() : default_value;
	}
}

