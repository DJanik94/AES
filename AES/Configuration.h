#pragma once
#include <memory>
#include<string>

class Configuration
{
	bool mode;
	int numberOfThreads;
	std::string sourcePath;
	std::string keyFilePath;
	std::string outputFilePath;

public:
	static Configuration& getInstance();
	bool isMode() const;
	void setMode(bool mode);
	int getNumberOfThreads() const;
	void setNumberOfThreads(int numberOfThreads);
	void setSourceFilePath(std::string);
	std::string getSourceFilePath() const;
	void setKeyFilePath(std::string);
	std::string getKeyFilePath() const;
	void setOutputFilePath(std::string);
	std::string getOutputFilePath() const;
};
