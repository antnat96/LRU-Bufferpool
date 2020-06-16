/*
 * File:   LRUBufferPool.h
 * Author: Anthony Natale
 * Created on June 14, 2020
 */

#ifndef LRUBUFFERPOOL_H
#define	LRUBUFFERPOOL_H

#include <string>
#include "BufferPoolADT.h"
#include "LRUBufferBlock.h"

using namespace std;

// ADT for buffer pools using the message-passing style
class LRUBufferPool : public BufferPoolADT {
private:

	// Our buffer block array
	LRUBufferBlock* blockArr[POOL_SIZE];

	void createInitialBlocks(char* wholeFile, int fileSize, int blockSize, int poolSize) {
		char* data[BLOCKSIZE];

		// Make poolSize blocks
		for (int i = 0; i < poolSize; i++) {
			int startingPoint = blockSize * i;
			int endingPoint = startingPoint + blockSize;
			for (int j = startingPoint; j < endingPoint; j++) {
				data[j] = wholeFile[j];
			}

			blockArr[i] = new LRUBufferBlock(data, blockSize);
			blockArr[i]->setID(i);
		}

		// Figure out how many full blocks we can make
		int numOfFullBlocks = fileSize / blockSize;
		// Add 1 for the total number of blocks
		int numOfTotalBlocks = numOfFullBlocks + 1;
		// If there are remaining characters, find the size of the final block
		int finalBlockSize = fileSize % blockSize;

		//char* temp = new char[blockSize];
		//for (int i = 0; i < poolSize; i++) {
		//	int startingPoint = blockSize * i;
		//	int endingPoint = startingPoint + blockSize;
		//	for (int j = startingPoint; j < endingPoint; j++) {
		//		temp[j] = wholeFile[j];
		//		temp = nullptr;
		//	}
		//}

	}

public:
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096) {
		cout << "Running LRUBufferPool constructor" << endl;

		// Open file stream
		ifstream input;
		// Use binary option
		input.open(filename, ifstream::in | ifstream::binary);

		// Get the total file size in bytes
		input.seekg(0, ifstream::end);
		// tellg returns the position of the pointer at the end of the file
		int fileSize = input.tellg();
		// Return the pointer to the beginning
		input.seekg(0, ifstream::beg);

		// Store the entire file in a char array
		char* wholeFile = new char[fileSize];
		input.read(wholeFile, fileSize);

		// Make those blocks
		createInitialBlocks(wholeFile, fileSize, blockSize, poolSize);

	}
	~LRUBufferPool() {
		cout << "Running pool deconstructor" << endl;
	}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos) {
	}

	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder() {
		cout << "print buffer block order" << endl;
	
	}

	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID() {
		return 1;
	}

};

#endif	/* LRUBUFFERPOOL_H */

