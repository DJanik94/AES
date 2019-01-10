#pragma once
class AESLookupTable
{
	AESLookupTable();

public:
	static AESLookupTable& getInstance();
	~AESLookupTable();
	static int getSBoxValue(int n);
	static int getInvSBoxValue(int n);
};
