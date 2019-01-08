#include "DecryptionService.h"
#include "Key.h"
#include <tuple>
#include <OMP.h>


void DecryptionService::mixColumns()
{
	byte a, b, c, d;
	for (int i = 0; i < 4; i++)
	{
		a = state[0][i];
		b = state[1][i];
		c = state[2][i];
		d = state[3][i];

		state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}

}

void DecryptionService::subBytes()
{

	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			state[i][j] = AESLookupTable::getInvSBoxValue(state[i][j]);
		}
	}
	
}

void DecryptionService::shiftRows()
{
	byte temp;

	// Rotate first row 1 columns to right
	temp = state[1][3];
	state[1][3] = state[1][2];
	state[1][2] = state[1][1];
	state[1][1] = state[1][0];
	state[1][0] = temp;

	// Rotate second row 2 columns to right
	temp = state[2][0];
	state[2][0] = state[2][2];
	state[2][2] = temp;

	temp = state[2][1];
	state[2][1] = state[2][3];
	state[2][3] = temp;

	// Rotate third row 3 columns to right
	temp = state[3][0];
	state[3][0] = state[3][1];
	state[3][1] = state[3][2];
	state[3][2] = state[3][3];
	state[3][3] = temp;

	
}

void DecryptionService::decipher()
{

	addRoundKey(numberOfRounds);

	// There will be numberOfRounds rounds.
	// The first numberOfRounds-1 rounds are identical.
	// These numberOfRounds-1 rounds are executed in the loop below.
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

DecryptionService& DecryptionService::getInstance()
{
	static DecryptionService decryptionService;
	return decryptionService;
}

std::tuple<byte*, int> DecryptionService::decrypt(Key& key, Text& text, int numberOfThreads)
{
	this->key = &key;
	numberOfRounds = key.getSize() / 4 + 6;

	const int output_size = ((text.getSize() / 16) + 1) * 16;
	const int numberOfBlocks = output_size / 16;

	if(output != nullptr) delete[] output;
	output = new byte[output_size];
	int currentBlock = 0;
	int num_of_threads;
	if (numberOfThreads == 1)
	{
		for (currentBlock = 0; currentBlock < numberOfBlocks; currentBlock++)
		{
			loadBlock(text, currentBlock);
			decipher();
			saveBlock(currentBlock);

		}
	}
	else if ( numberOfThreads > 1)
	{
		omp_set_num_threads(numberOfThreads);
#pragma omp parallel private(currentBlock, state, num_of_threads) shared(output, text, numberOfBlocks)
		{
			//num_of_threads = omp_get_num_threads();
			currentBlock = omp_get_num_threads();
			while (currentBlock < numberOfBlocks)
			{
				loadBlock(text, currentBlock);
				decipher();
				saveBlock(currentBlock);
				currentBlock += omp_get_num_threads();
			}
		}
	}

	/*for(auto currentBlock=0; currentBlock<numberOfBlocks; currentBlock++)
	{
		loadBlock(text, currentBlock);
		decipher();
		saveBlock(currentBlock);

	}*/
	//return output;
	return std::make_tuple(output, output_size);
}

