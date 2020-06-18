/*
 * File:   LRUBufferPool.h
 * Author: Anthony Natale
 * Created on June 14, 2020
 */

#ifndef LRUBUFFERPOOL_H
#define	LRUBUFFERPOOL_H

#include <string>

// Include the ADT for the Buffer Pool
#include "BufferPoolADT.h"

// Include the Buffer Block implementation class
#include "LRUBufferBlock.h"

using namespace std;

// ADT for buffer pools using the message-passing style
class LRUBufferPool : public BufferPoolADT {
private:

	// Array of Buffer Blocks
	LRUBufferBlock* blockArr[POOL_SIZE];
	int totalBlocksInFile;
	int finalBlockSize;


public:


	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096) {

		// Set the block IDs
		for (int i = 0; i < POOL_SIZE; i++) {
			blockArr[i]->setID(i);
		}

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

		// Figure out how many full blocks we can make
		int numOfFullBlocks = fileSize / blockSize;
		// Add 1 for the total number of blocks
		totalBlocksInFile = numOfFullBlocks + 1;
		// If there are remaining characters, find the size of the final block
		finalBlockSize = fileSize % blockSize;

		// Store the first 5 blocks in the char arrays
		for (int i = 0; i < POOL_SIZE; i++) {
			char* temp = new char[BLOCKSIZE];
			input.read(temp, 4096); // Currently doing the whole file, how do we change this?
			blockArr[i]->setBlock(temp);
		}

		cout << "Block 0 info is " << blockArr[0]->getBlock() << endl;
		cout << "check" << endl;

	}
	~LRUBufferPool() {
		delete blockArr;
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

