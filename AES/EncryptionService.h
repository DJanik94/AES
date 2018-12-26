#pragma once
#include "Types.h"

class Key;
class Text;

class EncryptionService
{
public:
	static EncryptionService& getInstance();
	void addRoundKey(int i, byte block[4][4]);
	void subBytes(byte block[4][4]);
	void shiftRows(byte block[4][4]);
	void mixColumns(byte block[4][4]);
	Text encrypt(Key key, Text& text, int numberOfThreads);
};
