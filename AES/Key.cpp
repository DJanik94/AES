#include "Key.h"



Key::Key()
{
}

Key::Key(unsigned char* content_char, int size_)
{
	int n = 0;
	for(int i=0; i<4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			content[i][j] = content_char[n];
			n++;
		}
	}
	size = size_;
}

Key::Key(unsigned char cont_[4][4], int size_)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			content[i][j] = cont_[i][j];
		}
	}
	size = size_;
}

/*Key::Key(const Key & key)
{
	
	

}*/

int Key::getSBoxValue(int n)
{
	return sbox[n];
}

void Key::prepareRoundKeys()
{
	int i, j;
	unsigned char temp[4], k;

	// The first round key is the key itself.
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			round_key[i][j] = content[i][j];
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
}


int Key::getSize()
{
	return size;
}

Key::~Key()
{
}

/*::Key& Key::operator=(const Key& key)
{
	Key newKey = Key(content, size);
	return newKey;
}*/
