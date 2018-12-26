#pragma once
#include <memory>

class Configuration
{
	bool mode;
	int numberOfThreads;

public:
	static Configuration& getInstance();
	bool isMode() const;
	void setMode(bool mode);
	int getNumberOfThreads() const;
	void setNumberOfThreads(int numberOfThreads);
};
