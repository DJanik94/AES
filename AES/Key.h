#pragma once
#include "Types.h"

class Key
{
	unsigned char content[4][4];
	int rcon[11] = {0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };
	byte round_key[4][60];
	int size;
	
public:
	
	Key();
	Key(unsigned char* content, int size);
	byte getRoundKeyValue(int i, int j);
	void prepareRoundKeys();
	int getSize();
	~Key();
};

