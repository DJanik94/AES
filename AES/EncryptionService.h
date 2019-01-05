#pragma once
#include "Types.h"
#include <tuple>
#include "AesBase.h"

class Key;
class Text;

class EncryptionService : public AesBase
{
private:
	void mixColumns();
	void subBytes();
	void shiftRows();
	void cipher();

public:
	static EncryptionService& getInstance();
	std::tuple<byte*, int> encrypt(Key& key, Text& text, int numberOfThreads);
};
