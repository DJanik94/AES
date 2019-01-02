#include "SettingsService.h"
#include <iostream>
#include "Configuration.h"

using namespace std;

SettingsService& SettingsService::getInstance()
{
	static SettingsService settingsService;
	return settingsService;
}

SettingsService::SettingsService()
{
	fileService = &FileService::getInstance();
}


void SettingsService::load(Key& key, Text& text)
{
	Configuration *configuration = &Configuration::getInstance();

	bool mode = 1;
	int numberOfThread = 1;
	string pathToKey = "Files/key.txt";
	string pathToText = "Files/text.txt";


	//cin from user


	std::tuple<Text*, Key*> data = fileService->loadFiles(pathToText, pathToKey);

	text = *std::get<0>(data);
	key = *std::get<1>(data);

	configuration->setMode(mode);
	configuration->setNumberOfThreads(numberOfThread);
}

SettingsService::~SettingsService()
{
}
