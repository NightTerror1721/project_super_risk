#include "resources.h"

#include <iostream>
#include <fstream>

const resource::ResourceFolder resource::Root{ "data" };
const resource::ResourceFolder resource::Maps{ resource::Root, "maps" };

resource::ResourceFolder::ResourceFolder(const std::string& spath) :
	_base{ spath }
{
	fs::create_directories(_base);
}

resource::ResourceFolder::ResourceFolder(const ResourceFolder& base, const std::string& spath) :
	_base{ base._base / Path{ spath } }
{
	fs::create_directories(_base);
}

Path resource::ResourceFolder::file(const Path& other, bool check_exists, bool& error) const
{
	Path fpath = _base / other;
	error = check_exists && (!fs::exists(fpath) || !fs::is_regular_file(fpath));
	return std::move(fpath);
}

void resource::ResourceFolder::readAndInject(JsonSerializable& object, const Path& file) const
{
	bool error = false;
	Path path = this->file(file, true, error);
	if (error)
		return;

	try { json_utils::read_and_inject(object, path); }
	catch (json_utils::JsonException ex) { std::cerr << ex.what() << std::endl; }
	catch (...) {}
}

void resource::ResourceFolder::readAndInject(JsonSerializable& object, const std::string& file) const
{
	readAndInject(object, Path{ file });
}

void resource::ResourceFolder::readAndInject(JsonSerializable& object, const char* file) const
{
	readAndInject(object, Path{ file });
}

void resource::ResourceFolder::extractAndWrite(const JsonSerializable& object, const Path& file) const
{
	bool error = false;
	Path path = this->file(file, false, error);
	if (error)
		return;

	try { json_utils::extract_and_write(object, path); }
	catch (json_utils::JsonException ex) { std::cerr << ex.what() << std::endl; }
	catch (...) {}
}

void resource::ResourceFolder::extractAndWrite(const JsonSerializable& object, const std::string& file) const
{
	extractAndWrite(object, Path{ file });
}

void resource::ResourceFolder::extractAndWrite(const JsonSerializable& object, const char* file) const
{
	extractAndWrite(object, Path{ file });
}


bool resource::ResourceFolder::readFile(const Path& file, std::function<void(std::ifstream&)>& action) const
{
	bool error = false;
	Path path = this->file(file, true, error);
	if (error)
		return false;

	std::ifstream f{ path, std::fstream::in };
	action(f);
	f.close();
	return true;
}

bool resource::ResourceFolder::readFile(const std::string& file, std::function<void(std::ifstream&)>& action) const
{
	return readFile(Path{ file }, action);
}

bool resource::ResourceFolder::readFile(const char* file, std::function<void(std::ifstream&)>& action) const
{
	return readFile(Path{ file }, action);
}

bool resource::ResourceFolder::writeFile(const Path& file, std::function<void(std::ofstream&)>& action) const
{
	bool error = false;
	Path path = this->file(file, false, error);
	if (error)
		return false;

	std::ofstream f{ path, std::fstream::out };
	action(f);
	f.close();
	return true;
}

bool resource::ResourceFolder::writeFile(const std::string& file, std::function<void(std::ofstream&)>& action) const
{
	return writeFile(Path{ file }, action);
}

bool resource::ResourceFolder::writeFile(const char* file, std::function<void(std::ofstream&)>& action) const
{
	return writeFile(Path{ file }, action);
}
