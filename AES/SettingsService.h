#pragma once
#include "FileService.h"
#include "Key.h"
#include "Text.h"

class SettingsService
{
	FileService *fileService;
	Text* text_;
	Key* key_;
	Configuration *configuration;
	SettingsService();
	void loadConfigurationFromConsole();
	void loadNumberOfThreads();
	void loadInputPath();
	void loadKeyPath();
	void loadOutPath();
	void loadMethod();
	void loadMode();
	void loadFromConfFile();

public:
	static SettingsService& getInstance();
	void load(Key& key, Text& text);

	~SettingsService();
};

