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
	//virtual ~BufferPoolADT() {}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos) {

	}

	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder() {
	
	}

	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID() {
	}

};

#endif	/* LRUBUFFERPOOL_H */

