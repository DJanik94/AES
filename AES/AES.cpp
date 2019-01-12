#include <iostream>
#include "AESEngine.h"
#include "SystemInformation.h"

int main(int argc, char *argv[])
{
	SystemInformation systemInformation = SystemInformation::getInstance();
	systemInformation.setSystemInformation(argc, argv);
	AESEngine aesEngine;
	aesEngine.start();
	getchar();
}
