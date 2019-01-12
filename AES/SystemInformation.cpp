#include "SystemInformation.h"

SystemInformation::SystemInformation()
{
}

SystemInformation& SystemInformation::getInstance()
{
	static SystemInformation systemInformation;
	return systemInformation;
}

void SystemInformation::setSystemInformation(int globalArgC, char** globalArgV)
{
	this->globalArgC = globalArgC;
	this->globalArgV = globalArgV;
}

int SystemInformation::getGlobalArgC() const
{
	return globalArgC;
}

char** SystemInformation::getGlobalArgV() const
{
	return globalArgV;
}
