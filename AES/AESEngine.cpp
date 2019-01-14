#include "AESEngine.h"
#include <iostream>
#include "mpi.h"

AESEngine::AESEngine()
{
	settingsService = &SettingsService::getInstance();
	configuration = &Configuration::getInstance();
	fileService = &FileService::getInstance();
	
}

void AESEngine::start()
{
	configuration->setDefaultConfiguration();
	settingsService->load(key,text);
	key.prepareRoundKeys();
	AesBase* service;
	if (configuration->isMode()) {
		service = EncryptionService::getInstance();	
	}
	else {
		service = DecryptionService::getInstance(); 
	}
	auto result = service->proceed(key, text, configuration->getNumberOfThreads(), configuration->getMethod());
	fileService->saveFile(std::get<0>(result), configuration->getOutputFilePath(), std::get<1>(result));
}


AESEngine::~AESEngine()
{
}

/*void AESEngine::setConfigurationFromFile()
{
	auto conf = fileService->loadSettings();
	configuration->setMode(std::get<0>(conf));
	configuration->setNumberOfThreads(std::get<1>(conf));
	configuration->setSourceFilePath(std::get<2>(conf));
	configuration->setKeyFilePath(std::get<3>(conf));
	configuration->setOutputFilePath(std::get<4>(conf));
}*/
