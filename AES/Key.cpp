#include "Key.h"
#include "AESEngine.h"


Key::Key()
{
}

Key::Key(unsigned char* content, int size)
{
	int n = 0;
	for(auto i=0; i<4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			this->content[i][j] = content[n];
			n++;
		}
	}
	this->size = size;
}

byte Key::getRoundKeyValue(int i, int j)
{
	return round_key[i][j];
}


void Key::prepareRoundKeys()
{
	int i, j;
	int n = size / 4; // key length in 32-bit words
	int r = n + 6; // number of AES rounds
	unsigned char temp[4], k;

	/*for (int h = 0; h < 4; h++)
	{
		if (round_key[h] != nullptr) delete[] round_key[h];
		round_key[h] = new byte[4*(r + 1)];
	}*/

	
	// The first round key is the key itself.
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			round_key[i][j] = content[i][j];
		}
	}

	while (j < (r * 4)) {

		// Copying the previous column
		for (i = 0; i < 4; i++) {
			temp[i] = round_key[i][j - 1];
		}

		if (i % n == 0) {
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
			temp[0] = AESLookupTable::getSBoxValue(temp[0]);
			temp[1] = AESLookupTable::getSBoxValue(temp[1]);
			temp[2] = AESLookupTable::getSBoxValue(temp[2]);
			temp[3] = AESLookupTable::getSBoxValue(temp[3]);

			// Column XOR round constant
			temp[0] = temp[0] ^ rcon[i / n];
		}

		else if (n > 6 && i % n == 4) {
			// Function Subword()
			temp[0] = AESLookupTable::getSBoxValue(temp[0]);
			temp[1] = AESLookupTable::getSBoxValue(temp[1]);
			temp[2] = AESLookupTable::getSBoxValue(temp[2]);
			temp[3] = AESLookupTable::getSBoxValue(temp[3]);
		}
		round_key[0][j] = round_key[0][j - n] ^ temp[0];
		round_key[1][j] = round_key[1][j - n] ^ temp[1];
		round_key[2][j] = round_key[2][j - n] ^ temp[2];
		round_key[3][j] = round_key[3][j - n] ^ temp[3];
		j++;
	}
}


int Key::getSize()
{
	return size;
}

Key::~Key()
{
}


