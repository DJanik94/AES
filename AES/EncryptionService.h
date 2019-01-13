#pragma once
#include "AesBase.h"

class Key;
class Text;

class EncryptionService : public AesBase
{
public:
	static EncryptionService* getInstance();
	void execute(byte(&safe)[4][4]) override;

private:
	void mixColumns(byte(&safe)[4][4]);
	void subBytes(byte(&safe)[4][4]);
	void shiftRows(byte(&safe)[4][4]);
};
