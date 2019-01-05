#pragma once
#include "AesBase.h"
class Key;
class Text;

class DecryptionService : public AesBase
{
private:
	void mixColumns();
	void subBytes();
	void shiftRows();
	void decipher();
	
public:
	static DecryptionService& getInstance();
	std::tuple<byte*, int> decrypt(Key& key, Text& text, int numberOfThreads);
};
