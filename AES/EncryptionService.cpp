#include "EncryptionService.h"
#include "Types.h"
#include "Text.h"
#include "Key.h"


EncryptionService& EncryptionService::getInstance()
{
	static EncryptionService encryptionService;
	return encryptionService;
}

std::tuple<byte*, int> EncryptionService::encrypt(Key& key, Text& text, int numberOfThreads)
{
	this->key = &key;
	numberOfRounds = key.getSize() / 4 + 6;

	const int output_size = ((text.getSize() / 16) + 1) * 16;
	const int numberOfBlocks = output_size / 16;

	if (output != nullptr) delete[] output;
	output = new byte[output_size];

	for (auto currentBlock = 0; currentBlock < numberOfBlocks; currentBlock++)
	{
		loadBlock(text, currentBlock);
		cipher();
		saveBlock(currentBlock);

	}
	return std::make_tuple(output, output_size);
}


void EncryptionService::mixColumns()
{
	int i;
	byte Tmp, Tm, t;
	for (i = 0; i < 4; i++) {
		t = state[0][i];
		Tmp = state[0][i] ^ state[1][i] ^ state[2][i] ^ state[3][i];
		Tm = state[0][i] ^ state[1][i]; Tm = xtime(Tm); state[0][i] ^= Tm ^ Tmp;
		Tm = state[1][i] ^ state[2][i]; Tm = xtime(Tm); state[1][i] ^= Tm ^ Tmp;
		Tm = state[2][i] ^ state[3][i]; Tm = xtime(Tm); state[2][i] ^= Tm ^ Tmp;
		Tm = state[3][i] ^ t; Tm = xtime(Tm); state[3][i] ^= Tm ^ Tmp;
	}
}

void EncryptionService::subBytes()
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			state[i][j] = AESLookupTable::getSBoxValue(state[i][j]);
		}
	}
}

void EncryptionService::shiftRows()
{
	byte temp;

	// Rotate first row 1 columns to left
	temp = state[1][0];
	state[1][0] = state[1][1];
	state[1][1] = state[1][2];
	state[1][2] = state[1][3];
	state[1][3] = temp;

	// Rotate second row 2 columns to left
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	// Rotate third row 3 columns to left
	temp = state[3][0];
	state[3][0] = state[3][3];
	state[3][3] = state[3][2];
	state[3][2] = state[3][1];
	state[3][1] = temp;
}

void EncryptionService::cipher()
{
	for (auto round = numberOfRounds - 1; round > 0; round--)
	{
		shiftRows();
		subBytes();
		addRoundKey(round);
		mixColumns();
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	shiftRows();
	subBytes();
	addRoundKey(0);

}



