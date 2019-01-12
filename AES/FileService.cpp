#include "FileService.h"
#include <fstream>
#include<exception>
#include "Configuration.h"
#include <iostream>


FileService::FileService()
{
	configuration = &Configuration::getInstance();
}

FileService& FileService::getInstance()
{
	
	static FileService fileService;
	return fileService;
}


FileService::~FileService()
{
}

void FileService::loadFiles(Key& key, Text& text)
{
	loadText(text);
	loadKey(key);
}

void FileService::loadText(Text& text)
{
	std::ifstream textFile(configuration->getSourceFilePath().c_str(), std::ios::binary);
	textFile.seekg(0, std::ios::end);
	const int text_size = textFile.tellg();
	textFile.seekg(0, std::ios::beg);
	auto* text_content = new byte[text_size];
	text_content[text_size] = 0x00;
	textFile.read(reinterpret_cast<char*>(text_content), text_size);
	textFile.close();
	text.setText(text_content, text_size, configuration->getSourceFilePath());
}

void FileService::loadKey(Key& key)
{
	std::ifstream keyFile(configuration->getKeyFilePath().c_str(), std::ios::binary);
	keyFile.seekg(0, std::ios::end);
	const int key_size = keyFile.tellg();
	keyFile.seekg(0, std::ios::beg);
	auto* key_content = new byte[key_size];
	key_content[key_size] = 0x00;
	keyFile.read(reinterpret_cast<char*>(key_content), key_size);
	keyFile.close();
	key.setSize(key_size);
	key.setContent(key_content);
}


void FileService::saveFile(byte* content, std::string file_name, int file_size) const
{
	std::ofstream file(file_name.c_str(), std::ios::binary);
	//std::string contentString = ((char*)content);
	file.write((char*)content, file_size);
	file.close();
	std::cout << "Zakonczono" << std::endl;
}


std::tuple<bool, int, Method,  std::string, std::string, std::string> FileService::loadSettings()
{
	std::string confFileName = "Files/conf.txt";
	bool mode;
	int numOfThreads;
	Method method;
	std::string methodString;
	std::string inputFileName, keyFileName, outputFileName, line;

	//TODO validation

	std::ifstream file (confFileName.c_str(), std::ios::binary);
	if (!file.is_open()) throw std::exception("Conf file not found");
	else
	{
		std::getline(file, line);
		if (line[line.size() - 1] == '\r')
			line.resize(line.size() - 1);
		mode = (line == "encrypt");
		std::getline(file, line);
		numOfThreads = std::stoi(line.c_str());
		std::getline(file, methodString);
		std::getline(file, inputFileName);
		if (inputFileName[inputFileName.size() - 1] == '\r')
			inputFileName.resize(inputFileName.size() - 1);
		std::getline(file, keyFileName);
		if (keyFileName[keyFileName.size() - 1] == '\r')
			keyFileName.resize(keyFileName.size() - 1);
		std::getline(file, outputFileName);
		if (outputFileName[outputFileName.size() - 1] == '\r')
			outputFileName.resize(outputFileName.size() - 1);
		file.close();

		method = methodMap.find(methodString)->second;
	}

	return std::make_tuple(mode, numOfThreads, method, inputFileName, keyFileName, outputFileName);
}
