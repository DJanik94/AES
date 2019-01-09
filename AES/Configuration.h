#pragma once
//#include <memory>
#include<string>
#include <tuple>

class Configuration
{
	bool mode;
	int numberOfThreads;
	std::string sourceFilePath;
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
	void setDefaultConfiguration(bool mode);
	void setConfiguration(std::tuple<bool, int, std::string, std::string, std::string> conf);
};
