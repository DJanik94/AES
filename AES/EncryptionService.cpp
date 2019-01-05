#include "EncryptionService.h"
#include "Types.h"
#include "Text.h"
#include "Key.h"

EncryptionService& EncryptionService::getInstance()
{
	static EncryptionService encryptionService;
	return encryptionService;
}

Text EncryptionService::encrypt(Key key, Text& text, int numberOfThreads)
{
	Text result;
	/*int currentBlock = 0;
	int numberOfBlocks = 100;
	while (currentBlock < numberOfBlocks) {
		byte state[4][4];
		addRoundKey(0, state);

		for (int i = 1; i < key.size(); i++) {
			subBytes(state);
			shiftRows(state);
			mixColumns(state);
			addRoundKey(i, state);
		}

		subBytes(state);
		shiftRows(state);
		addRoundKey(key.size(), state);

		currentBlock++;
	}*/
	return result;
}

void EncryptionService::addRoundKey(int i, byte block[4][4])
{
}

void EncryptionService::subBytes(byte block[4][4])
{
}

void EncryptionService::shiftRows(byte block[4][4])
{
}

void EncryptionService::mixColumns(byte block[4][4])
{
}
