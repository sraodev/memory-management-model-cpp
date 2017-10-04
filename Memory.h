//
//  memory.h
//  MemoryManager
//
//  Created by श्री  on 15/09/17.
//  Copyright © 2017 Sri. All rights reserved.
//

#ifndef memory_h
#define memory_h

typedef unsigned VA;   // Type describing the address of the block

typedef struct header{
    unsigned left;
    size_t size;
}BlockHeader;


/**
 * @brief defragment
 * Defragmentates memory
 */
void defragMemory();

/**
 * @brief printMemory
 * Prints memory state
 */
void PrintMemory();

int initMemory(int n, size_t szPage);
int mallocBlock(size_t blockSize);
int freeBlock(VA va);
int writeToBlock(VA va, void *pBuffer, size_t bufferSize);
int readFromBlock(VA va, void *pBuffer, size_t bufferSize);

#endif /* memory_h */
