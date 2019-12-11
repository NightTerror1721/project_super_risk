#pragma once

#include <filesystem>
#include <functional>
#include <vector>

#include "json.h"

namespace fs = std::experimental::filesystem;

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

		void readAndInject(JsonSerializable& object, const Path& file);
		void readAndInject(JsonSerializable& object, const std::string& file);

		void extractAndWrite(const JsonSerializable& object, const Path& file);
		void extractAndWrite(const JsonSerializable& object, const std::string& file);

		bool readFile(const Path& file, std::function<void(std::ifstream&)>& action);
		bool readFile(const std::string& file, std::function<void(std::ifstream&)>& action);

		bool writeFile(const Path& file, std::function<void(std::ofstream&)>& action);
		bool writeFile(const std::string& file, std::function<void(std::ofstream&)>& action);

	private:
		Path file(const Path& other, bool& error) const;
	};

	extern const ResourceFolder Root;
	extern const ResourceFolder Maps;
}
