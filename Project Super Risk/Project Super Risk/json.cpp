#include "json.h"

#include <iostream>
#include <fstream>

namespace fs = std::filesystem;
using json_utils::JsonException;

JsonSerializable::~JsonSerializable() {}

JsonException::JsonException(const std::string& msg) :
	exception{ msg.c_str() }
{}

JsonSerializable& operator<< (JsonSerializable& object, const Json& json)
{
	object.unserialize(json);
	return object;
}

const JsonSerializable& operator>> (const JsonSerializable& object, Json& json)
{
	json = std::move(object.serialize());
	return object;
}

Json json_utils::read(const fs::path& file_path)
{
	try
	{
		std::fstream f{ file_path, std::fstream::in };
		Json j;
		f >> j;
		f.close();
		return std::move(j);
	}
	catch (...)
	{
		std::cerr << "An error has been ocurred during json reading in file: " << file_path << std::endl;
		throw JsonException{ "Read error in method: json_utils::read" };
	}
}

Json json_utils::read(const std::string& file_path)
{
	return std::move(json_utils::read(fs::path{ file_path }));
}

void json_utils::write(const fs::path& file_path, const Json& json)
{
	try
	{
		std::fstream f{ file_path, std::fstream::out };
		f << json;
		f.flush();
		f.close();
	}
	catch (...)
	{
		std::cerr << "An error has been ocurred during json writting in file: " << file_path << std::endl;
		throw JsonException{ "Read error in method: json_utils::write" };
	}
}

void json_utils::write(const std::string& file_path, const Json& json)
{
	json_utils::write(fs::path{ file_path }, json);
}

void json_utils::inject(JsonSerializable& object, const Json& json)
{
	object.unserialize(json);
}

Json json_utils::extract(const JsonSerializable& object)
{
	return std::move(object.serialize());
}

void json_utils::read_and_inject(JsonSerializable& object, const std::filesystem::path& file_path)
{
	json_utils::inject(object, json_utils::read(file_path));
}

void json_utils::read_and_inject(JsonSerializable& object, const std::string& file_path)
{
	json_utils::inject(object, json_utils::read(file_path));
}

void json_utils::extract_and_write(const JsonSerializable& object, const std::filesystem::path& file_path)
{
	json_utils::write(file_path, extract(object));
}

void json_utils::extract_and_write(const JsonSerializable& object, const std::string& file_path)
{
	json_utils::write(file_path, extract(object));
}

