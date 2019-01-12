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
	/*TODO zmodyfikowac tak, aby mozna wczytac konfiguracje z pliku lub przez uzytkownika*/
	int choice = 0;
	bool mode;
	std::string methodString;
	Method method;
	std::cout << "1 - Konfiguracja domyslna, 2 - Z pliku \"Files/conf.txt\" 3 - podaj parametry" << std::endl;
	std::cin >> choice;

	std::tuple<bool, int, Method, std::string, std::string, std::string> conf;
	int number_of_threads;
	std::string input_path, key_path, out_path;

	switch (choice)
	{
	case 1:
		std::cout << "Wybierz tryb: 0-deszyfrowanie, 1-szyfrowanie"<<std::endl;
		std::cin >> mode;
		configuration->setDefaultConfiguration(mode);
		break;
		
	case 2:
		conf = fileService->loadSettings();
		configuration->setConfiguration(conf);
		break;
	case 3:	
		
		std::cout << "Wybierz tryb: 0-deszyfrowanie, 1-szyfrowanie" << std::endl;
		std::cin >> mode;
		std::cout << "Podaj liczbe watkow" << std::endl;
		std::cin >> number_of_threads;
		std::cout << "Podaj sciezke pliku wejsciowego" << std::endl;
		std::cin >> input_path;
		std::cout << "Podaj sciezke pliku z kluczem" << std::endl;
		std::cin >> key_path;
		std::cout << "Podaj sciezke pliku wyjsciowego" << std::endl;
		std::cin >> out_path;
		std::cout << "Podaj metode (SEQUENCE, OMP, MPI): " << std::endl;
		std::cin >> methodString;
		method = methodMap.find(methodString)->second;

		configuration->setConfiguration
			(std::make_tuple(mode, number_of_threads, methodMap.find(methodString)->second, input_path, key_path, out_path));
		break;
	default:
		configuration->setDefaultConfiguration(true);
	}
	

	
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
