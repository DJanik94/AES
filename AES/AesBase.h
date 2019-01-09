#pragma once
#include "Types.h"
#include "Text.h"
#include "Key.h"
#include <tuple>

// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}  
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// Multiply is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))


class AesBase
{
protected:
	Key* key=nullptr;
	byte state[4][4];
	byte round_key[4][60];
	int numberOfRounds;
	byte* output;
	void addRoundKey(int round);
	void loadBlock(Text& input, int block_num);
	void saveBlock(int block_num);


public:
	AesBase();
	~AesBase();
	virtual void cipher_decipher() = 0;
	std::tuple<byte*, int> proceed(Key& key, Text& text, int numberOfThreads);
};

class AESLookupTable
{
	AESLookupTable();

public:
	static AESLookupTable& getInstance();
	~AESLookupTable();
	static int getSBoxValue(int n);
	static int getInvSBoxValue(int n);
};