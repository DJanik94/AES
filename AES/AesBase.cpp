#include "AesBase.h"



int AesBase::getSBoxValue(int n)
{
	return sbox[n];
}

/*void AesBase::keyExpansion()
{
	int i, j;
	byte temp[4], k;

	// The first round key is the key itself.
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			round_key[i][j] = key[i][j];
		}
	}

	while (j < (Nr * 4)) {

		// Copying the previous column
		for (i = 0; i < 4; i++) {
			temp[i] = round_key[i][j - 1];
		}

		if (i % Nk == 0) {
			// This function rotates the 4 bytes in a word to the left once.
			// [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

			// Function RotWord()
			k = temp[0];
			temp[0] = temp[1];
			temp[1] = temp[2];
			temp[2] = temp[3];
			temp[3] = k;

			// SubWord() is a function that takes a four-byte input word and 
			// applies the S-box to each of the four bytes to produce an output word.

			// Function Subword()
			temp[0] = getSBoxValue(temp[0]);
			temp[1] = getSBoxValue(temp[1]);
			temp[2] = getSBoxValue(temp[2]);
			temp[3] = getSBoxValue(temp[3]);

			// Column XOR round constant
			temp[0] = temp[0] ^ rcon[i / Nk];
		}

		else if (Nk > 6 && i % Nk == 4) {
			// Function Subword()
			temp[0] = getSBoxValue(temp[0]);
			temp[1] = getSBoxValue(temp[1]);
			temp[2] = getSBoxValue(temp[2]);
			temp[3] = getSBoxValue(temp[3]);
		}
		round_key[0][j] = round_key[0][j - Nk] ^ temp[0];
		round_key[1][j] = round_key[1][j - Nk] ^ temp[1];
		round_key[2][j] = round_key[2][j - Nk] ^ temp[2];
		round_key[3][j] = round_key[3][j - Nk] ^ temp[3];
		j++;
	}
}*/

void AesBase::addRoundKey(int round)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			block[i][j] ^= round_key[i][round * 4 + j];
		}
	}

	
}

void AesBase::loadBlock(Text& input,  int block_num)
{
	int byte_num = 16 * block_num;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(byte_num<input.getSize())
			{
				block[i][j] = input.getByte(byte_num);
				byte_num++;
			}
			else
			{
				block[i][j] = 0x00;
				byte_num++;
			}
		}
	}
}

void AesBase::saveBlock(int block_num)
{
	int n = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			output[block_num + n] = block[i][j];
			n++;
		}
	}
}

void AesBase::loadKeyToMatrix(Text & key_file)
{
}

AesBase::AesBase()
{
}


AesBase::~AesBase()
{
}
