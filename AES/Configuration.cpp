#include "Configuration.h"

Configuration& Configuration::getInstance()
{
	static Configuration configuration;
	return configuration;
}

bool Configuration::isMode() const
{
	return mode;
}

void Configuration::setMode(bool mode)
{
	this->mode = mode;
}

int Configuration::getNumberOfThreads() const
{
	return numberOfThreads;
}

void Configuration::setNumberOfThreads(int numberOfThreads)
{
	this->numberOfThreads = numberOfThreads;
}

void Configuration::setSourceFilePath(std::string path)
{
	this->sourceFilePath = path;
}

std::string Configuration::getSourceFilePath() const
{
	return this->sourceFilePath;
}

void Configuration::setKeyFilePath(std::string path)
{
	this->keyFilePath = path;
}

std::string Configuration::getKeyFilePath() const
{
	return this->keyFilePath;
}

void Configuration::setOutputFilePath(std::string path)
{
	this->outputFilePath = path;
}

std::string Configuration::getOutputFilePath() const
{
	return this->outputFilePath;
}

void Configuration::setDefaultConfiguration(bool mode)
{
	this->mode = mode;
	keyFilePath = "Files/key.txt";
	if (mode)
	{
		sourceFilePath = "Files/text.txt";
		outputFilePath = "Files/result_en.txt";
		numberOfThreads = 4;
	}
	else
	{
		sourceFilePath = "Files/result_en.txt";
		outputFilePath = "Files/result_dec.txt";
		numberOfThreads = 4;
	}
}

void Configuration::setConfiguration(std::tuple<bool, int, std::string, std::string, std::string> conf)
{
	setMode(std::get<0>(conf));
	setNumberOfThreads(std::get<1>(conf));
	setSourceFilePath(std::get<2>(conf));
	setKeyFilePath(std::get<3>(conf));
	setOutputFilePath(std::get<4>(conf));
}
