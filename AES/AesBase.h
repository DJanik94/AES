#pragma once
#include "Types.h"
#include "Text.h"
#include "Key.h"
#include <tuple>
#include "Method.h"

#define tx(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
#define propagate(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * tx(x)) ^ ((y>>2 & 1) * tx(tx(x))) ^ ((y>>3 & 1) * tx(tx(tx(x)))) ^ ((y>>4 & 1) * tx(tx(tx(tx(x))))))

class AesBase
{
public:
	static byte* output;
	static byte safe_[4][4];

protected:
	Key* key=nullptr;
	byte round_key[4][60];
	int numberOfRounds;
	void addRoundKey(int round, byte (&safe)[4][4]);
	void loadBlock(Text& input, int blockNumber, byte (&safe)[4][4]);
	void saveBlock(int blockNumber, byte(&safe)[4][4]);

public:
	AesBase();
	~AesBase();
	virtual void execute(byte (&safe)[4][4]) = 0;
	std::tuple<byte*, int> proceed(Key& key, Text& text, int numberOfThreads, Method method);

private:
	void doSequence(Text& text, int numberOfBlocks, int& currentBlock);
	void doOpenMP(Text& text, int numberOfThreads, int numberOfBlocks, int currentBlock);
	void doMPI(Text& text, int numberOfBlocks, int& currentBlock, int outputSize);
	void prepareData(Key& key, Text& text, int& output_size, int& numberOfBlocks, int& currentBlock);
};