#include "Text.h"



Text::Text()
{
}

Text::Text(unsigned char* cont, int size_, std::string fileName_)
{
	content = cont;
	size = size_;
	fileName = fileName_;
}


Text::~Text()
{
}

byte Text::getByte(int byte_num)
{
	return content[byte_num];
}

int Text::getSize()
{
	return size;
}
