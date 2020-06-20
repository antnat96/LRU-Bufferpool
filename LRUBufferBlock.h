/*
 * File:   LRUBufferBlock.h
 * Author: Anthony Natale
 * Created on June 14, 2020
 */

#ifndef LRUBUFFERBLOCK_H
#define	LRUBUFFERBLOCK_H

#include <string>
#include "BufferBlockADT.h"
using namespace std;

// ADT implementation for a single buffer block
class LRUBufferBlock : public BufferBlockADT {
private:
	// ID
	int blockID;
	// Size (4096)
	int blockSize;
	// Pointer to char array of block content
	char* block;
	// The starting point of the current block content in the text file
	int blockStart;
	// The ending point of the current block content in the text file
	int blockEnd;

public:
	LRUBufferBlock() {
	}
	LRUBufferBlock(char* data, int sz = 4096) {
		// Set the size-will be 4096 in all cases except the last "block" of the file
		blockSize = sz;

		// Set the block character array
		block = data;
	}

	~LRUBufferBlock() {
		// Set the start & end points to -1 (until they're set again next time the block is reassigned)
		blockStart = -1;
		blockEnd = -1;
	}

	// Set the ID of the block
	void setID(int id) {
		blockID = id;
	}

	//set the block
	void setBlock(char* blk) {
		block = blk;
		blockSize = strlen(block);
	}

	void setBlockStart(int start) {
		blockStart = start;
	}

	void setBlockEnd(int end) {
		blockEnd = end;
	}

	// Getters
	//read the block from pos to pos + sz-1 (or to the end of the block)
	void getData(int pos, int sz, char* data) {
		pos = pos % BLOCKSIZE;
		int j = 0;
		for (int i = pos; i < (pos + sz); i++) {
			// Assign the characters from block to temp
			data[j] = block[i];
			j++;
		}
		return;
	}

	//getID
	int getID() const {
		return blockID;
	}

	//getBlockSize
	int getBlockSize() const {
		return blockSize;
	}

	//return the block
	char* getBlock() const {
		return block;
	}

	int getBlockStart() {
		return blockStart;
	}

	int getBlockEnd() {
		return blockEnd;
	}

};

#endif	/* LRUBUFFERBLOCK_H */

