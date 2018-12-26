#pragma once
#include "FileService.h"
#include "Key.h"
#include "Text.h"

class SettingsService
{
	FileService *fileService;

	SettingsService();

public:
	static SettingsService& getInstance();
	void load(Key& key, Text& text);
	~SettingsService();
};

