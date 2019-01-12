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
byte AesBase::state[4][4];

void AesBase::addRoundKey(int round)
{
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {

			state[i][j] ^= key->getRoundKeyValue(i, round * 4 + j);
		}
	}

	
}

void AesBase::loadBlock(Text& input,  int block_num)
{
	int byte_num = 16 * block_num;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(byte_num<input.getSize())
			{
				state[i][j] = input.getByte(byte_num);
				byte_num++;
			}
			else
			{
				state[i][j] = 0x00;
				byte_num++;
			}
		}
	}
}

void AesBase::saveBlock(int block_num)
{
	int byte_number = block_num * 16;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			output[byte_number] = state[i][j];
			byte_number++;
		}
	}
}



AesBase::AesBase()
{
}


AesBase::~AesBase()
{
}



std::tuple<byte*, int> AesBase::proceed(Key& key, Text& text, int numberOfThreads, Method method)
{
	this->key = &key;
	numberOfRounds = key.getSize() / 4 + 6;
	int num_of_threads;

	const int output_size = ((text.getSize() / 16) + 1) * 16;
	const int numberOfBlocks = output_size / 16;

	if (output != nullptr) delete[] output;
	output = new byte[output_size];
	int currentBlock = 0;
	auto start = std::chrono::high_resolution_clock::now();
	switch (method)
	{
		case Method::SEQUENCE:
		{
			if (numberOfThreads == 1)
			{
				while (currentBlock < numberOfBlocks)
				{
					loadBlock(text, currentBlock);
					execute();
					saveBlock(currentBlock);
					++currentBlock;
				}
			}
			break;
		}
		case Method::OMP:
		{
			int tmpNumberOfThreads;
			Configuration configuration = Configuration::getInstance();
			bool mode = configuration.isMode();
			omp_set_num_threads(numberOfThreads);
			#pragma omp parallel private(state,currentBlock,tmpNumberOfThreads) shared(output,text,numberOfBlocks,mode)
			{
				currentBlock = omp_get_thread_num();
				tmpNumberOfThreads = omp_get_num_threads();

				while (currentBlock < numberOfBlocks)
				{
					loadBlock(text, currentBlock);
					execute();
					saveBlock(currentBlock);
					currentBlock += tmpNumberOfThreads;
				}
			}
			break;
		}
		case Method::MPI:
		{
			int myRank, p;
			SystemInformation systemInformation = SystemInformation::getInstance();
			int globalArgC = systemInformation.getGlobalArgC();
			char** globalArgV = systemInformation.getGlobalArgV();
			MPI_Init(&globalArgC, &globalArgV);
			//MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
			//MPI_Comm_size(MPI_COMM_WORLD, &p);

			for (currentBlock = 0; currentBlock < numberOfBlocks; currentBlock++)
			{
				std::cout << "Daj znak zycia" << std::endl;
				loadBlock(text, currentBlock);
				execute();
				saveBlock(currentBlock);
			}

			//std::cout << myRank << std::endl;
			//std::cout << p << std::endl;

			MPI_Finalize();

			break;
		}
	}
	auto finish = std::chrono::high_resolution_clock::now();
	auto elapsed = (finish - start) / 1000000000;
	std::cout << "Czas wykonania: " << elapsed.count() << std::endl;
	return std::make_tuple(output, output_size);
}