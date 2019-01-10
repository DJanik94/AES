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
	configuration = &Configuration::getInstance();
}

void SettingsService::load(Key& key, Text& text)
{
	

	bool mode = configuration->isMode();
	int numberOfThread = configuration->getNumberOfThreads();
	string pathToKey = configuration->getKeyFilePath();


	string pathToText = mode==true ? "Files/text.txt" : "Files/result_en.txt";


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
