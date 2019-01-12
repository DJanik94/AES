#include "Text.h"



Text::Text()
{
}

Text::Text(byte* content, int size, std::string fileName)
{
	this->content = content;
	this->size = size;
	this->fileName = fileName;
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

void Text::setText(byte* content, int size, std::string filename)
{
	this->content = content;
	this->size = size;
	this->fileName = filename;
}
