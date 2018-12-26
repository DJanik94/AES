#include "DecryptionService.h"
#include "Key.h"

DecryptionService& DecryptionService::getInstance()
{
	static DecryptionService decryptionService;
	return decryptionService;
}

void DecryptionService::decrypt(Key key, Text& text, int numberOfThreads)
{

}
