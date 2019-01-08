#pragma once
#include <string>
#include "Key.h"
#include "Text.h"
#include <tuple>
#include "Configuration.h"

class FileService
{
	FileService();
	//int size;
	byte* content;
	std::string fileName;
	Configuration* configuration;


public:
	static FileService& getInstance();
	~FileService();
	/*Key loadKey(std::string file_name);
	Text loadText(std::string file_name);*/
	std::tuple<Text*, Key*> loadFiles(std::string text_file_name, std::string key_file_name);
	//int loadFile(std::string file_name);
	void saveFile(byte* content, std::string file_name, int file_size) const;
	std::tuple<bool, int, std::string, std::string, std::string> loadSettings();
};

