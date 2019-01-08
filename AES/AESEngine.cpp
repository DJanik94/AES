#include "AESEngine.h"

AESEngine::AESEngine()
{
	settingsService = &SettingsService::getInstance();
	configuration = &Configuration::getInstance();
	fileService = &FileService::getInstance();
	
}

void AESEngine::start()
{
	//configuration->setMode(true);//
	setConfiguration();
	settingsService->load(key,text);
	key.prepareRoundKeys();

	if (configuration->isMode()) {
		EncryptionService *encryptionService = &EncryptionService::getInstance();
		auto result = encryptionService->encrypt(key, text, configuration->getNumberOfThreads());
		fileService->saveFile(std::get<0>(result), "Files/result_en.txt", std::get<1>(result));
		
	}
	else {
		//configuration->setMode(false);//
		//settingsService->load(key, text);//
		key.prepareRoundKeys();
		DecryptionService *decryptionService = &DecryptionService::getInstance();
		auto result = decryptionService->decrypt(key, text, configuration->getNumberOfThreads());
		fileService->saveFile(std::get<0>(result), "Files/result_dec.txt", std::get<1>(result)); 


	}

}


AESEngine::~AESEngine()
{
}

void AESEngine::setConfiguration()
{
	auto conf = fileService->loadSettings();
	configuration->setMode(std::get<0>(conf));
	configuration->setNumberOfThreads(std::get<1>(conf));
	configuration->setSourceFilePath(std::get<2>(conf));
	configuration->setKeyFilePath(std::get<3>(conf));
	configuration->setOutputFilePath(std::get<4>(conf));
}
