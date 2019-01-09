#pragma once
//#include "Types.h"
//#include <tuple>
#include "AesBase.h"

class Key;
class Text;

class EncryptionService : public AesBase
{
private:
	void mixColumns();
	void subBytes();
	void shiftRows();
	void cipher();

public:
	static EncryptionService* getInstance();
	
	void cipher_decipher() override;
};
