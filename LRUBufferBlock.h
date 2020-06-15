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
	// Some private variables
	int blockID;
	char* block;
	int blockSize;

public:
	LRUBufferBlock(char* data, int sz = 4096) {
		cout << "Running LRUBufferBlock constructor" << endl;
		block = data;
		blockSize = sz;
	}

	~LRUBufferBlock() {

	}

	// Setters
	//setID
	void setID(int id) {
		blockID = id;
	}

	//set the block
	void setBlock(char* blk) {
		block = blk;
		blockSize = strlen(block);
	}

	// Getters
	//read the block from pos to pos + sz-1 (or to the end of the block)
	void getData(int pos, int sz, char* data) {
		cout << "My data for block " << blockID << " is: \"";
		for (int i = pos; i < sz; i++) {
			cout << "Getting the block data, iteration #" << i << endl;
		}
		cout << "\"\n";
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

};

#endif	/* LRUBUFFERBLOCK_H */

