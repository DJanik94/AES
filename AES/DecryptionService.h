#pragma once
#include "AesBase.h"
class Key;
class Text;

class DecryptionService : public AesBase
{
public:
	static DecryptionService* getInstance();
	void execute() override;

private:
	void mixColumns();
	void subBytes();
	void shiftRows();
};
