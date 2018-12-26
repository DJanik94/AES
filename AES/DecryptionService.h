#pragma once

class Key;
class Text;

class DecryptionService
{
public:
	static DecryptionService& getInstance();
	void decrypt(Key key, Text& text, int numberOfThreads);
};
