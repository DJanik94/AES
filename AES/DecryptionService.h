#pragma once
#include "AesBase.h"
class Key;
class Text;

class DecryptionService : public AesBase
{
public:
	static DecryptionService* getInstance();
	void execute(byte(&safe)[4][4]) override;

private:
	void mixColumns(byte(&safe)[4][4]);
	void subBytes(byte(&safe)[4][4]);
	void shiftRows(byte(&safe)[4][4]);
};
