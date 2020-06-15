/*
 * File:   LRUBufferPool.h
 * Author: Anthony Natale
 * Created on June 14, 2020
 */

#ifndef LRUBUFFERPOOL_H
#define	LRUBUFFERPOOL_H

#include <string>
#include "BufferPoolADT.h"
using namespace std;

// ADT for buffer pools using the message-passing style
class LRUBufferPool : public BufferPoolADT {
private:

public:
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096) {
		cout << "Running LRUBufferPool constructor" << endl;

		// Build out all the blocks
		ifstream input;
		input.open(filename, ifstream::in | ifstream::binary);

		input.seekg(0, ifstream::end);
		int fileSize = input.tellg();

		char* wholeFile = new char[fileSize];

		input.read(wholeFile, fileSize);

		//for (int i = 0; i < POOL_SIZE; i++) {
		//	char* buffer = new char[BLOCKSIZE];
		//}

		//for (int i = 0; i < POOL_SIZE; i++) {
		//	input.read(buffer, BLOCKSIZE)
		//	buffer[i] = input.read()

		//}


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

