#include "AESEngine.h"

AESEngine::AESEngine()
{
	settingsService = &SettingsService::getInstance();
	configuration = &Configuration::getInstance();
	fileService = &FileService::getInstance();
	
}

void AESEngine::start()
{
	settingsService->load(key,text);
	key.prepareRoundKeys();

	if (configuration->isMode()) {
		EncryptionService *encryptionService = &EncryptionService::getInstance();
		auto result = encryptionService->encrypt(key, text, configuration->getNumberOfThreads());
		fileService->saveFile(std::get<0>(result), "Files/result.txt", std::get<1>(result));
	}
	else {
		DecryptionService *decryptionService = &DecryptionService::getInstance();
		auto result = decryptionService->decrypt(key, text, configuration->getNumberOfThreads());
		fileService->saveFile(std::get<0>(result), "Files/result.txt", std::get<1>(result)); 


	}

}


AESEngine::~AESEngine()
{
}
