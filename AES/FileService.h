#pragma once
class FileService
{
	FileService();

public:
	static FileService& getInstance();
	~FileService();
};

