#include "AesBase.h"
#include <OMP.h>
#include "Method.h"
#include <mpi.h>


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
	int n = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			output[block_num*16 + n] = state[i][j];
			n++;
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
	switch (method)
	{
		case Method::SEQUENCE:
			if (numberOfThreads == 1 && method == Method::SEQUENCE)
			{
				for (currentBlock = 0; currentBlock < numberOfBlocks; currentBlock++)
				{
					loadBlock(text, currentBlock);
					execute();
					saveBlock(currentBlock);

				}
			}
			break;
		case Method::OMP:
			omp_set_num_threads(numberOfThreads);

#pragma omp parallel private(currentBlock, state) shared(output, text, numberOfBlocks)
			{
				currentBlock = omp_get_thread_num();
				while (currentBlock < numberOfBlocks)
				{
					loadBlock(text, currentBlock);
					execute();
					saveBlock(currentBlock);
					currentBlock += omp_get_num_threads();
				}
			}
		case Method::MPI:
			//MPI_Init()
			break;

	}
	return std::make_tuple(output, output_size);
}