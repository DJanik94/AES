#pragma once
#include "Types.h"
#include <string>

class Text
{
	int size;
	unsigned char* content;
	std::string fileName;
public:
	Text();
	Text(unsigned char *cont, int size_, std::string fileName_);
	~Text();
	byte* get16Bytes(int currentBlock);
	byte getByte(int byte_num);
	int getSize();
};

