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

	if (configuration->isMode() && false) {
		EncryptionService *encryptionService = &EncryptionService::getInstance();
		encryptionService->encrypt(key, text, configuration->getNumberOfThreads());
	}
	else {
		DecryptionService *decryptionService = &DecryptionService::getInstance();
		byte* result = decryptionService->decrypt(key, text, configuration->getNumberOfThreads());
		fileService->saveFile(result, "Files/result.txt", 48); //TODO: zmodyfikowac 


	}

}


AESEngine::~AESEngine()
{
}
