#pragma once
#include <string>
#include "Key.h"
#include "Text.h"
#include <tuple>
//#include <cstdlib>
#include "Configuration.h"

class FileService
{
	FileService();
	byte* content;
	std::string fileName;
	Configuration* configuration;

	void loadText(Text& text);
	void loadKey(Key& key);

public:
	static FileService& getInstance();
	~FileService();

	void loadFiles(Key& key, Text& text);
	void saveFile(byte* content, std::string file_name, int file_size) const;
	std::tuple<bool, int, Method, std::string, std::string, std::string> loadSettings();
};

