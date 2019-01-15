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

void SettingsService::loadConfigurationFromConsole()
{
	loadMode();
	loadNumberOfThreads();
	loadInputPath();
	loadKeyPath();
	loadOutPath();
	loadMethod();
}

void SettingsService::loadMode()
{
	bool mode;
	std::cout << "Wybierz tryb: 0-deszyfrowanie, 1-szyfrowanie" << std::endl;
	std::cin >> mode;
}

void SettingsService::loadFromConfFile()
{
	std::tuple<bool, int, Method, std::string, std::string, std::string> configurationTuple = fileService->loadSettings();
	configuration->setConfiguration(configurationTuple);
}

void SettingsService::loadNumberOfThreads()
{
	int numberOfThreads;
	std::cout << "Podaj liczbe watkow" << std::endl;
	std::cin >> numberOfThreads;
	configuration->setNumberOfThreads(numberOfThreads);
}

void SettingsService::loadInputPath()
{
	std::string inputPath;
	std::cout << "Podaj sciezke pliku wejsciowego" << std::endl;
	std::cin >> inputPath;
	configuration->setSourceFilePath(inputPath);
}

void SettingsService::loadKeyPath()
{
	std::string keyPath;
	std::cout << "Podaj sciezke pliku z kluczem" << std::endl;
	std::cin >> keyPath;
	configuration->setKeyFilePath(keyPath);
}

void SettingsService::loadOutPath()
{
	std::string outPath;
	std::cout << "Podaj sciezke pliku wyjsciowego" << std::endl;
	std::cin >> outPath;
	configuration->setOutputFilePath(outPath);
}

void SettingsService::loadMethod()
{
	std::string methodString;
	Method method;
	std::cout << "Podaj metode (SEQUENCE, OMP, MPI): " << std::endl;
	std::cin >> methodString;
	method = methodMap.find(methodString)->second;
	configuration->setMethod(method);
}

void SettingsService::load(Key& key, Text& text)
{
	if (configuration->getMethod() != MPI)
	{
		int choice;
		std::cout << "1 - Konfiguracja domyslna, 2 - Z pliku \"Files/conf.txt\" 3 - podaj parametry" << std::endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			configuration->setDefaultConfiguration();
			break;

		case 2:
			loadFromConfFile();
			break;
		case 3:
			loadConfigurationFromConsole();
			break;
		default:
			configuration->setDefaultConfiguration();
		}
	}

	fileService->loadFiles(key, text);
}

SettingsService::~SettingsService()
{
}
