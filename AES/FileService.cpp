#include "FileService.h"
#include <fstream>


FileService::FileService()
{
}

FileService& FileService::getInstance()
{
	static FileService fileService;
	return fileService;
}


FileService::~FileService()
{
}

std::tuple<Text*, Key*> FileService::loadFiles(std::string text_file_name, std::string key_file_name)
{

	//Load text
	std::ifstream textFile(text_file_name.c_str(), std::ios::binary);
	textFile.seekg(0, std::ios::end);
	const int text_size = textFile.tellg();
	textFile.seekg(0, std::ios::beg);
	auto* text_content = new unsigned char[text_size];
	textFile.read(reinterpret_cast<char*>(text_content), text_size);
	textFile.close();
	auto* text = new Text(text_content, text_size, text_file_name);

	//Load key
	std::ifstream keyFile(key_file_name.c_str(), std::ios::binary);
	keyFile.seekg(0, std::ios::end);
	const int key_size = keyFile.tellg();
	keyFile.seekg(0, std::ios::beg);
	auto* key_content = new unsigned char[key_size];
	keyFile.read(reinterpret_cast<char*>(key_content), key_size);
	keyFile.close();

	auto* key = new Key(key_content, key_size);

	return std::make_tuple(text, key);
}



void FileService::saveFile(byte* content, std::string file_name, int file_size) const
{
	std::ofstream file(file_name.c_str(), std::ios::binary);
	file.write(reinterpret_cast<char*>(content), file_size);
	file.close();
}
