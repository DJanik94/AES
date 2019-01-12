#pragma once
#include "Types.h"
#include "Text.h"
#include "Key.h"
#include <tuple>
#include "Method.h"

// xtime is a macro that finds the product of {02} and the argument to xtime modulo {1b}  
#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// Multiply is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))


class AesBase
{
public:
	static byte* output;
	static byte state[4][4];

protected:
	Key* key=nullptr;
	byte round_key[4][60];
	int numberOfRounds;
	void addRoundKey(int round);
	void loadBlock(Text& input, int blockNumber);
	void saveBlock(int blockNumber);


public:
	AesBase();
	~AesBase();
	virtual void execute() = 0;
	std::tuple<byte*, int> proceed(Key& key, Text& text, int numberOfThreads, Method method);
};