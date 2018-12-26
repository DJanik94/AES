#pragma once
#include <memory>
#include "SettingsService.h"
#include "Configuration.h"
#include "EncryptionService.h"
#include "DecryptionService.h"

class AESEngine
{
	SettingsService *settingsService;
	Configuration *configuration;
	Key key;
	Text text;

public:
	AESEngine();
	void start();
	~AESEngine();
};

