#include "DecryptionService.h"
#include "Key.h"

int DecryptionService::getSBoxDecrypt(int n)
{
	return rsbox_decrypt[n];
}

void DecryptionService::mixColumns()
{
	unsigned char a, b, c, d;
	for (int i = 0; i < 4; i++)
	{
		a = block[0][i];
		b = block[1][i];
		c = block[2][i];
		d = block[3][i];

		block[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		block[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		block[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		block[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}

}

void DecryptionService::subBytes()
{

	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			block[i][j] = getSBoxDecrypt(block[i][j]);
		}
	}
	
}

void DecryptionService::shiftRows()
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

void DecryptionService::decipher()
{
	int round;

	addRoundKey(Nr);

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for (round = Nr - 1; round > 0; round--)
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

DecryptionService& DecryptionService::getInstance()
{
	static DecryptionService decryptionService;
	return decryptionService;
}

byte* DecryptionService::decrypt(Key& key, Text& text, int numberOfThreads)
{
	int output_size = ((text.getSize() / 16) + 1) * 16;
	if (output != nullptr) delete[] output;

	output = new byte[output_size];
	int numberOfBlocks = output_size / 16;
	int currentBlock;
	byte* state;

	for(currentBlock=0; currentBlock<numberOfBlocks; currentBlock++)
	{
		//state = text.get16Bytes(currentBlock);
		loadBlock(text, currentBlock);
		decipher();
		saveBlock(currentBlock);

	}
	return output;
}

