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
	LRUBufferBlock blockArr[POOL_SIZE];
	int totalBlocksInFile;
	int finalBlockSize;
	string currentFileName;

public:

	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096) {
		currentFileName = filename;

		// Set the block ID, start, end, and size
		for (int i = 0; i < POOL_SIZE; i++) {
			blockArr[i].setID(i);
			blockArr[i].setBlockStart(i * BLOCKSIZE);
			blockArr[i].setBlockEnd((i + 1) * BLOCKSIZE);
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
			input.read(temp, BLOCKSIZE); // Currently doing the whole file, how do we change this?
			blockArr[i].setBlock(temp);
		}
	}
	~LRUBufferPool() {
		delete blockArr;
	}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos) {
		// Check if the desired condition is in a buffer block
		for (int i = 0; i < POOL_SIZE; i++) {
			// If the entirety of the position + size are between the block start and end
			if (pos > blockArr[i].getBlockStart() && (pos + sz) > blockArr[i].getBlockStart() && pos < blockArr[i].getBlockEnd() && (pos + sz) < blockArr[i].getBlockEnd()) {
				// The desired position is in a buffer block, from the block, pull the characters
				blockArr[i].getData(pos, sz, space);
				reorderBlocksWithoutPushingLast(i);
				return;
			}
		}
		// Otherwise, look to the file (on disk rather than in RAM)
		ifstream tempStream;
		// Use binary option
		tempStream.open(currentFileName, ifstream::in | ifstream::binary);
		// Move to the get pointer
		tempStream.seekg(pos);
		// Read the characters into space
		tempStream.read(space, sz);
		reorderBlocksWithPush(currentFileName, pos);
		return;
	}

	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder() {
		cout << "My buffer block order from most recently used to LRU is:" << endl;
		for (int i = 0; i < POOL_SIZE; i++) {
			cout << blockArr[i].getID();
			if (i != (POOL_SIZE - 1)) {
				cout << ", ";
			}
			else {
				cout << "\n" << endl;
			}
		}
		return;
	}

	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID() {
		return blockArr[POOL_SIZE - 1].getID();
	}

	void reorderBlocksWithoutPushingLast(int arrPosOfBlockJustUsed) {
		if (arrPosOfBlockJustUsed == 0) return; // No changes needed
		LRUBufferBlock tempBlock = blockArr[arrPosOfBlockJustUsed]; // Block just accessed
		for (int i = (arrPosOfBlockJustUsed - 1); i > -1; i--) {
			blockArr[i + 1] = blockArr[i];
		}
		blockArr[0] = tempBlock;
		return;
	}

	void reorderBlocksWithPush(string fileName, int pos) {
		for (int i = (POOL_SIZE - 2); i > -1; i--) {
			blockArr[i + 1] = blockArr[i];
		}
		// Build temporary block
		LRUBufferBlock tempBlock;
		char* tempCharArr = new char[BLOCKSIZE];

		// Otherwise, look to the file (on disk rather than in RAM)
		ifstream tempStream;
		// Use binary option
		tempStream.open(currentFileName, ifstream::in | ifstream::binary);
		// Find the multiple of the BLOCKSIZE closest to but not greater than pos
		int blockID = pos / BLOCKSIZE;
		int startingPoint = blockID * BLOCKSIZE;
		// Move to the get pointer
		tempStream.seekg(startingPoint);
		// Read the characters into tempCharArr
		tempStream.read(tempCharArr, BLOCKSIZE);

		tempBlock.setBlock(tempCharArr);
		tempBlock.setBlockStart(startingPoint);
		tempBlock.setBlockEnd(startingPoint + BLOCKSIZE);
		tempBlock.setID(blockID);

		blockArr[0] = tempBlock;
		return;
	}

};

#endif	/* LRUBUFFERPOOL_H */

