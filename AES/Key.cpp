#include "Key.h"
#include "AESEngine.h"
#include "AesBase.h"
#include "AESLookupTable.h"


Key::Key()
{
}

Key::Key(byte* content, int size)
{
	if (!(size == 16 || size == 24 || size == 32)) throw std::exception("Nieprawidlowy rozmiar klucza");
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
	return roundKey[i][j];
}


void Key::prepareRoundKeys()
{
	int i, j;
	int keyLengthIn32BitWords = size / 4;
	int numberOfAESRounds = keyLengthIn32BitWords + 6;
	byte temp[4], k;

	// The first round key is the key itself.
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			roundKey[i][j] = content[i][j];
		}
	}

	while (j < ((numberOfAESRounds+1) * 4)) {//Dodane =

		// Copying the previous column
		for (i = 0; i < 4; i++) {
			temp[i] = roundKey[i][j - 1];
		}

		if (i % keyLengthIn32BitWords == 0) {
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
			temp[0] = temp[0] ^ roundConstant[i / keyLengthIn32BitWords];
		}

		else if (keyLengthIn32BitWords > 6 && i % keyLengthIn32BitWords == 4) {
			// Function Subword()
			temp[0] = AESLookupTable::getSBoxValue(temp[0]);
			temp[1] = AESLookupTable::getSBoxValue(temp[1]);
			temp[2] = AESLookupTable::getSBoxValue(temp[2]);
			temp[3] = AESLookupTable::getSBoxValue(temp[3]);
		}
		roundKey[0][j] = roundKey[0][j - keyLengthIn32BitWords] ^ temp[0];
		roundKey[1][j] = roundKey[1][j - keyLengthIn32BitWords] ^ temp[1];
		roundKey[2][j] = roundKey[2][j - keyLengthIn32BitWords] ^ temp[2];
		roundKey[3][j] = roundKey[3][j - keyLengthIn32BitWords] ^ temp[3];
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


