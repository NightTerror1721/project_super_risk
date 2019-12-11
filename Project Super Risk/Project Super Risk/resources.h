#pragma once

#include <filesystem>
#include <functional>
#include <vector>

#include "json.h"

namespace fs = std::filesystem;

using Path = fs::path;

namespace resource
{
	class ResourceFolder
	{
	private:
		Path _base;

	public:
		ResourceFolder(const std::string& spath);
		ResourceFolder(const ResourceFolder& base, const std::string& spath);

		void readAndInject(JsonSerializable& object, const Path& file) const;
		void readAndInject(JsonSerializable& object, const std::string& file) const;
		void readAndInject(JsonSerializable& object, const char* file) const;

		void extractAndWrite(const JsonSerializable& object, const Path& file) const;
		void extractAndWrite(const JsonSerializable& object, const std::string& file) const;
		void extractAndWrite(const JsonSerializable& object, const char* file) const;

		bool readFile(const Path& file, std::function<void(std::ifstream&)>& action) const;
		bool readFile(const std::string& file, std::function<void(std::ifstream&)>& action) const;
		bool readFile(const char* file, std::function<void(std::ifstream&)>& action) const;

		bool writeFile(const Path& file, std::function<void(std::ofstream&)>& action) const;
		bool writeFile(const std::string& file, std::function<void(std::ofstream&)>& action) const;
		bool writeFile(const char* file, std::function<void(std::ofstream&)>& action) const;

	private:
		Path file(const Path& other, bool check_exists, bool& error) const;
	};

	extern const ResourceFolder Root;
	extern const ResourceFolder Maps;
}
