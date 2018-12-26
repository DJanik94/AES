#include "AESEngine.h"

AESEngine::AESEngine()
{
	settingsService = &SettingsService::getInstance();
	configuration = &Configuration::getInstance();
}

void AESEngine::start()
{
	settingsService->load(key,text);
	key.prepareRoundKeys();

	if (configuration->isMode()) {
		EncryptionService *encryptionService = &EncryptionService::getInstance();
		encryptionService->encrypt(key, text, configuration->getNumberOfThreads());
	}
	else {
		DecryptionService *decryptionService = &DecryptionService::getInstance();
		decryptionService->decrypt(key, text, configuration->getNumberOfThreads());
	}

}


AESEngine::~AESEngine()
{
}
