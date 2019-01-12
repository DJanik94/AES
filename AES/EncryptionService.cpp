#include "EncryptionService.h"
#include "Types.h"
#include "AESLookupTable.h"


EncryptionService* EncryptionService::getInstance()
{
	static EncryptionService* encryptionService;
	if (encryptionService == nullptr) encryptionService = new EncryptionService;
	return encryptionService;
}

void EncryptionService::mixColumns()
{
	int i;
	byte Tmp, Tm, t;
	for (i = 0; i < 4; i++) {
		t = safe[0][i];
		Tmp = safe[0][i] ^ safe[1][i] ^ safe[2][i] ^ safe[3][i];
		Tm = safe[0][i] ^ safe[1][i]; Tm = xtime(Tm); safe[0][i] ^= Tm ^ Tmp;
		Tm = safe[1][i] ^ safe[2][i]; Tm = xtime(Tm); safe[1][i] ^= Tm ^ Tmp;
		Tm = safe[2][i] ^ safe[3][i]; Tm = xtime(Tm); safe[2][i] ^= Tm ^ Tmp;
		Tm = safe[3][i] ^ t; Tm = xtime(Tm); safe[3][i] ^= Tm ^ Tmp;
	}
}

void EncryptionService::subBytes()
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			safe[i][j] = AESLookupTable::getSBoxValue(safe[i][j]);
		}
	}
}

void EncryptionService::shiftRows()
{
	byte temporary;

	temporary = safe[1][0];
	safe[1][0] = safe[1][1];
	safe[1][1] = safe[1][2];
	safe[1][2] = safe[1][3];
	safe[1][3] = temporary;

	temporary = safe[2][0];
	safe[2][0] = safe[2][2];
	safe[2][2] = temporary;

	temporary = safe[2][1];
	safe[2][1] = safe[2][3];
	safe[2][3] = temporary;

	temporary = safe[3][0];
	safe[3][0] = safe[3][3];
	safe[3][3] = safe[3][2];
	safe[3][2] = safe[3][1];
	safe[3][1] = temporary;
}

void EncryptionService::execute()
{
	addRoundKey(0);

	for (auto round = 1; round<numberOfRounds; round++)
	{
		subBytes();
		shiftRows();
		mixColumns();
		addRoundKey(round);
	}

	subBytes();
	shiftRows();
	addRoundKey(numberOfRounds);
}



