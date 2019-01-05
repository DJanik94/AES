#pragma once
#include <string>
#include "Key.h"
#include "Text.h"
#include <tuple>

class FileService
{
	FileService();
	//int size;
	unsigned char* content;
	std::string fileName;


public:
	static FileService& getInstance();
	~FileService();
	/*Key loadKey(std::string file_name);
	Text loadText(std::string file_name);*/
	std::tuple<Text*, Key*> loadFiles(std::string text_file_name, std::string key_file_name);
	//int loadFile(std::string file_name);
	void saveFile(byte* content, std::string file_name, int file_size) const;
};

