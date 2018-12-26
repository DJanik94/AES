#include "FileService.h"



FileService::FileService()
{
}

FileService& FileService::getInstance()
{
	static FileService fileService;
	return fileService;
}


FileService::~FileService()
{
}
