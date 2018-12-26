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
	string pathToKey;
	string pathToText;

	//cin from user

	configuration->setMode(mode);
	configuration->setNumberOfThreads(numberOfThread);
}

SettingsService::~SettingsService()
{
}
