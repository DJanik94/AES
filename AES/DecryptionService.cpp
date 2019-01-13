#include "DecryptionService.h"
#include "AESLookupTable.h"

void DecryptionService::mixColumns(byte(&safe)[4][4])
{
	byte a, b, c, d;
	for (int i = 0; i < 4; i++)
	{
		a = safe[0][i];
		b = safe[1][i];
		c = safe[2][i];
		d = safe[3][i];

		safe[0][i] = propagate(a, 0x0e) ^ propagate(b, 0x0b) ^ propagate(c, 0x0d) ^ propagate(d, 0x09);
		safe[1][i] = propagate(a, 0x09) ^ propagate(b, 0x0e) ^ propagate(c, 0x0b) ^ propagate(d, 0x0d);
		safe[2][i] = propagate(a, 0x0d) ^ propagate(b, 0x09) ^ propagate(c, 0x0e) ^ propagate(d, 0x0b);
		safe[3][i] = propagate(a, 0x0b) ^ propagate(b, 0x0d) ^ propagate(c, 0x09) ^ propagate(d, 0x0e);
	}
}

void DecryptionService::subBytes(byte(&safe)[4][4])
{
	for (auto i = 0; i < 4; i++)
	{
		for (auto j = 0; j < 4; j++)
		{
			safe[i][j] = AESLookupTable::getInvSBoxValue(safe[i][j]);
		}
	}	
}

void DecryptionService::shiftRows(byte(&safe)[4][4])
{
	byte temp;

	temp = safe[1][3];
	safe[1][3] = safe[1][2];
	safe[1][2] = safe[1][1];
	safe[1][1] = safe[1][0];
	safe[1][0] = temp;

	temp = safe[2][0];
	safe[2][0] = safe[2][2];
	safe[2][2] = temp;

	temp = safe[2][1];
	safe[2][1] = safe[2][3];
	safe[2][3] = temp;

	temp = safe[3][0];
	safe[3][0] = safe[3][1];
	safe[3][1] = safe[3][2];
	safe[3][2] = safe[3][3];
	safe[3][3] = temp;

	
}

void DecryptionService::execute(byte(&safe)[4][4])

{
	addRoundKey(numberOfRounds,  safe);

	for (auto round = numberOfRounds - 1; round > 0; round--)
	{
		shiftRows(safe);
		subBytes(safe);
		addRoundKey(round, safe);
		mixColumns(safe);
	}

	shiftRows(safe);
	subBytes(safe);
	addRoundKey(0, safe);

}

DecryptionService* DecryptionService::getInstance()
{
	static DecryptionService *instance;
	if (instance == nullptr) instance = new DecryptionService;
	return instance;
}



