#pragma once
//#include <memory>
#include<string>
#include <tuple>
#include "Method.h"

class Configuration
{

	bool mode;
	int numberOfThreads;
	Method method;
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
	Method getMethod() const;
	void setMethod(Method method);
	void setDefaultConfiguration();
	void setConfiguration(std::tuple<bool, int, Method, std::string, std::string, std::string> conf);
};
