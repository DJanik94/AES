#pragma once
#include "Types.h"

class Key
{
	byte content[4][4];
	int roundConstant[11] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
	byte roundKey[4][60] = {{0x00}, {0x00}, {0x00}, {0x00}};
	int size;
	
public:
	Key();
	Key(byte* content, int size);
	byte getRoundKeyValue(int i, int j);
	void prepareRoundKeys();
	int getSize();
	void setSize(int size);
	void setContent(byte* content);
	~Key();
};

