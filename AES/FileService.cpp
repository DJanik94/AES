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
	std::ifstream textFile(text_file_name.c_str(), std::ios::binary);
	textFile.seekg(0, std::ios::end);
	int text_size = textFile.tellg();
	textFile.seekg(0, std::ios::beg);
	auto* text_content = new unsigned char[size];
	textFile.read((char*)text_content, text_size);
	textFile.close();
	auto* text = new Text(text_content, text_size, text_file_name);

	std::ifstream keyFile(key_file_name.c_str(), std::ios::binary);
	keyFile.seekg(0, std::ios::end);
	int key_size = keyFile.tellg();
	keyFile.seekg(0, std::ios::beg);
	auto* key_content = new unsigned char[key_size];
	keyFile.read((char*)key_content, key_size);
	keyFile.close();

	auto* key = new Key(key_content, key_size);

	return std::make_tuple(text, key);
}

int FileService::loadFile(std::string file_name)
{
	std::ifstream file(file_name.c_str(), std::ios::binary);
	if (!file.is_open()) return -1;

	fileName = file_name;
	file.seekg(0, std::ios::end);
	size = file.tellg();
	file.seekg(0, std::ios::beg);

	if (content != nullptr) delete[] content;

	content = new unsigned char[size];

	file.read(reinterpret_cast<char*>(content), size);
	
	file.close();
	return 0;
}

void FileService::saveFile(byte* content, std::string file_name) const
{
	
	std::ofstream file(file_name.c_str(), std::ios::binary);
	char* test = (char*)content;
	file.write((char*)content, size);
	file.close();
}
