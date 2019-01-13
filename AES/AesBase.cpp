#include "AesBase.h"
#include <OMP.h>
#include "Method.h"
#include <mpi.h>
#include <iostream>
#include "SystemInformation.h"
#include <chrono>
#include "Configuration.h"

int globalArgC;
char **globalArgV;

byte* AesBase::output;
byte AesBase::safe_[4][4];

std::tuple<byte*, int> AesBase::proceed(Key& key, Text& text, int numberOfThreads, Method method)
{
	int output_size;
	int numberOfBlocks;
	int currentBlock;
	prepareData(key, text, output_size, numberOfBlocks, currentBlock);

	auto start = std::chrono::high_resolution_clock::now();

	switch (method)
	{
		case Method::SEQUENCE:
		{
			doSequence(text, numberOfBlocks, currentBlock);
			//doOpenMP(text, numberOfThreads, numberOfBlocks, currentBlock);
			break;
		}
		case Method::OMP:
		{
			doOpenMP(text, numberOfThreads, numberOfBlocks, currentBlock);
			break;
		}
		case Method::MPI:
		{
			doMPI(text, numberOfBlocks, currentBlock);
			break;
		}
	}
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = (finish - start) / 1000000000;
	std::cout << "Czas wykonania: " << elapsed.count() << std::endl;
	return std::make_tuple(output, output_size);
}

void AesBase::prepareData(Key& key, Text& text, int& output_size, int& numberOfBlocks, int& currentBlock)
{
	this->key = &key;
	numberOfRounds = key.getSize() / 4 + 6;
	int num_of_threads;

	output_size = ((text.getSize() / 16) + 1) * 16;
	numberOfBlocks = output_size / 16;

	if (output != nullptr) delete[] output;
	output = new byte[output_size];
	currentBlock = 0;
}

void AesBase::addRoundKey(int round, byte(&safe)[4][4])
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {

			safe[i][j] ^= key->getRoundKeyValue(i, round * 4 + j);
		}
	}
}

void AesBase::loadBlock(Text& input, int block_num, byte(&safe)[4][4])
{
	int byte_num = 16 * block_num;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (byte_num < input.getSize())
			{
				(safe)[i][j] = input.getByte(byte_num);
				byte_num++;
			}
			else
			{
				safe[i][j] = 0x00;
				byte_num++;
			}
		}
	}
}

void AesBase::saveBlock(int block_num, byte(&safe)[4][4])
{
	int byte_number = block_num * 16;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			output[byte_number] = safe[i][j];
			byte_number++;
		}
	}
}

void AesBase::doSequence(Text& text, const int numberOfBlocks, int& currentBlock)
{
	byte tmpBlock[4][4];
	while (currentBlock < numberOfBlocks)
	{
		//byte tmpBlock[4][4];
		loadBlock(text, currentBlock, tmpBlock);
		execute(tmpBlock);
		saveBlock(currentBlock, tmpBlock);
	}
}

void AesBase::doOpenMP(Text& text, int numberOfThreads, const int numberOfBlocks, int currentBlock)
{
	//int tmpNumberOfThreads;
	Configuration configuration = Configuration::getInstance();
	bool mode = configuration.isMode();
	omp_set_num_threads(numberOfThreads);
	byte tmpBlock[4][4];
#pragma omp parallel for private(tmpBlock) 
	for(int currentBlock = 0; currentBlock <numberOfBlocks; currentBlock++)
	{
		//byte tmpBlock[4][4];
		loadBlock(text, currentBlock, tmpBlock);
		int g = 0;
		execute(tmpBlock);
		saveBlock(currentBlock, tmpBlock);
	}
}

void AesBase::doMPI(Text& text, const int numberOfBlocks, int& currentBlock)
{
	int myRank, p;
	SystemInformation systemInformation = SystemInformation::getInstance();
	int globalArgC = systemInformation.getGlobalArgC();
	char** globalArgV = systemInformation.getGlobalArgV();
	MPI_Init(&globalArgC, &globalArgV);
	//MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
	//MPI_Comm_size(MPI_COMM_WORLD, &p);
	byte tmpBlock[4][4];
	for (currentBlock = 0; currentBlock < numberOfBlocks; currentBlock++)
	{
		//byte tmpBlock[4][4];
		std::cout << "Daj znak zycia" << std::endl;
		loadBlock(text, currentBlock, tmpBlock);
		execute(tmpBlock);
		saveBlock(currentBlock, tmpBlock);
	}

	//std::cout << myRank << std::endl;
	//std::cout << p << std::endl;

	MPI_Finalize();
}

AesBase::AesBase()
{
}


AesBase::~AesBase()
{
}