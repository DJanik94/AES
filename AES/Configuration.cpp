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
	this->sourcePath = path;
}

std::string Configuration::getSourceFilePath() const
{
	return this->sourcePath;
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

