#pragma once
#include "AesBase.h"

class Key;
class Text;

class EncryptionService : public AesBase
{
public:
	static EncryptionService* getInstance();
	void execute() override;

private:
	void mixColumns();
	void subBytes();
	void shiftRows();
};
