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
