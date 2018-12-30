#include "DecryptionService.h"
#include "Key.h"

int DecryptionService::getSBoxDecrypt(int n)
{
	return rsbox_decrypt[n];
}

void DecryptionService::mixColumns(byte block[4][4])
{
}

void DecryptionService::subBytes(byte block[4][4])
{

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			block[i][j] = getSBoxDecrypt(block[i][j]);
		}
	}
}

void DecryptionService::shiftRows(byte block[4][4])
{
	byte temp;

	// Rotate first row 1 columns to right
	temp = block[1][3];
	block[1][3] = block[1][2];
	block[1][2] = block[1][1];
	block[1][1] = block[1][0];
	block[1][0] = temp;

	// Rotate second row 2 columns to right
	temp = block[2][0];
	block[2][0] = block[2][2];
	block[2][2] = temp;

	temp = block[2][1];
	block[2][1] = block[2][3];
	block[2][3] = temp;

	// Rotate third row 3 columns to right
	temp = block[3][0];
	block[3][0] = block[3][1];
	block[3][1] = block[3][2];
	block[3][2] = block[3][3];
	block[3][3] = temp;
}

void DecryptionService::decipher(byte block[4][4])
{
	int round;

	addRoundKey(Nr, block);

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for (round = Nr - 1; round > 0; round--)
	{
		shiftRows(block);
		subBytes(block);
		addRoundKey(round, block);
		mixColumns(block);
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	shiftRows(block);
	subBytes(block);
	addRoundKey(0, block);

}

DecryptionService& DecryptionService::getInstance()
{
	static DecryptionService decryptionService;
	return decryptionService;
}

void DecryptionService::decrypt(Key key, Text& text, int numberOfThreads)
{

}

