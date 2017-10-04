//
//  memory.cpp
//  MemoryManager
//
//  Created by श्री  on 15/09/17.
//  Copyright © 2017 Sri. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "memory.h"

void *pMemory;
void *pMemoryEnd;
int addrSize;
size_t totalMemory;
size_t allocMemory;
size_t availMemory;

unsigned createMask(unsigned from, unsigned to){
    unsigned mask = 0;
    for (unsigned i = from; i <= to; i++) {
        mask |= 1 << i;
    }
    return mask;
}

/**
 * @brief getHeaderSize
 * @return size of memory block rounded to bytes
 */
size_t getHeaderSize(){
    return ceil((double)addrSize * 2 / 8);
}

/**
 * @brief readHeader
 * @param addr - reader header information from the the memory block
 * @return header
 * Fills header from memory adress
 */
BlockHeader readHeader(void *addr){
    BlockHeader header;
    unsigned va = 0;
    unsigned size = 0;
    va |= *((unsigned*)addr) & createMask(0, addrSize - 1);
    size |= (*((unsigned*)addr) & (createMask(0, addrSize) << addrSize)) >> addrSize;
    header.left = va;
    header.size = size;
    return header;
}

/**
 * @brief writeHeader
 * @param addr - Block of memory
 * @param header - Block header info
 * Writes header to memory
 */
void writeHeader(void *addr, BlockHeader header){
    *((unsigned*)addr) &= ~createMask(0, addrSize * 2);
    *((unsigned*)addr) |= header.left & createMask(0, addrSize - 1);
    *((unsigned*)addr) |= (header.size & createMask(0, addrSize)) << addrSize;
}

void *getNextBlock(void *block){
    BlockHeader blockHeader = readHeader(block);
    block = static_cast<uint8_t*>(block) + getHeaderSize() + blockHeader.size;
    return block;
}

void *getFreeBlock(size_t blockSize){
    void *block = pMemory;
    while (block < pMemoryEnd) {
        BlockHeader blockHeader = readHeader(block);
        if (blockHeader.left == 0 && blockHeader.size >= blockSize + getHeaderSize()) {
            return block;
        }
        block = getNextBlock(block);
    }
    return NULL;
}

void switchBlocks(void *firstBlock, void *nextBlock){
    BlockHeader firstBlockHeader = readHeader(firstBlock);
    BlockHeader nextBlockHeader = readHeader(nextBlock);
    BlockHeader tmpBlockHeader = firstBlockHeader;
    firstBlockHeader = nextBlockHeader;
    writeHeader(firstBlock, firstBlockHeader);
    memcpy((char*)firstBlock + getHeaderSize(), (char*)nextBlock + getHeaderSize(), firstBlockHeader.size);
    nextBlock = getNextBlock(firstBlock);
    nextBlockHeader = tmpBlockHeader;
    writeHeader(nextBlock, nextBlockHeader);
}

void mergeBlocks(void *firstBlock, void *nextBlock){
    BlockHeader firstBlockHeader = readHeader(firstBlock);
    BlockHeader nextBlockHeader = readHeader(nextBlock);
    firstBlockHeader.size += getHeaderSize() + nextBlockHeader.size;
    writeHeader(firstBlock, firstBlockHeader);
}

/**
 * @brief MergeWithNextEmptyBlock
 * @param block
 * Merging empty block with following empty block if exist
 */
void mergeWithNextEmptyBlock(void *block){
    void *nextBlock = getNextBlock(block);
    if (nextBlock < pMemoryEnd) {
        BlockHeader nextBlockHeader = readHeader(nextBlock);
        if (nextBlockHeader.left == 0) {
            mergeBlocks(block, nextBlock);
        }
    }
}

/**
 * @brief mergeWithPreviousEmptyBlock
 * @param block
 * Merging empty block with previous empty blocks if they exist
 */
void mergeWithPreviousEmptyBlock(void* block){
    void *prevBlock = pMemory;
    if (block == pMemory) {
        return;
    }
    while (getNextBlock(prevBlock) != block) {
        prevBlock = getNextBlock(prevBlock);
    }
    BlockHeader prevBlockHeader = readHeader(prevBlock);
    if (prevBlockHeader.left == 0) {
        mergeBlocks(prevBlock, block);
    }
}


/**
 * @brief defragment
 * Defragmentates memory
 */
void defragMemory(){
    void *block = pMemory;
    void *nextBlock = getNextBlock(block);
    while (nextBlock < pMemoryEnd) {
        BlockHeader blockHeader = readHeader(block);
        BlockHeader nextBlockHeader = readHeader(nextBlock);
        
        if (blockHeader.left != 0) {
            block = nextBlock;
            nextBlock = getNextBlock(block);
            continue;
        }
        
        if (nextBlockHeader.left != 0) {
            switchBlocks(block, nextBlock);
            nextBlock = getNextBlock(block);
        } else {
            mergeWithNextEmptyBlock(block);
            nextBlock = getNextBlock(block);
        }
    }
}

/**
 * @brief getByVA
 * @param va virtual address
 * @return pointer to block start
 * Finds block with given VA
 */
void *getByVA(VA va){
    void *block = pMemory;
    while (block < pMemoryEnd) {
        BlockHeader header = readHeader(block);
        if (header.left <= va && va < header.left + header.size) {
            return block;
        }
        block = getNextBlock(block);
    }
    return NULL;
}

int writeToBlock(VA va, void *pBuffer, size_t bufferSize){
    void *block = getByVA(va);
    void *destBuffer = NULL;
    if (!block) {
        return -1;
    }
    BlockHeader header  = readHeader(block);
    if (bufferSize + (va - header.left) > header.size) {
        return -2;
    }
    *((unsigned*)destBuffer) = *((unsigned*)block) + getHeaderSize() + (va - header.left);
    memcpy(destBuffer, pBuffer, bufferSize);
    return 0;
}

int readFromBlock(VA va, void *pBuffer, size_t bufferSize){
    void *block = getByVA(va);
    void *srcBlock = NULL;
    if (!block) {
        return -1;
    }
    BlockHeader header = readHeader(block);
    if (bufferSize + (va - header.left) > header.size) {
        return -2;
    }
    *((unsigned*)srcBlock) = *((unsigned*)block) + getHeaderSize() + (va - header.left);
    memcpy(pBuffer, srcBlock, bufferSize);
    return 0;
}

int mallocBlock(size_t blockSize){
    void *block = NULL;
    if (blockSize <= 0) {
        return  -1;
    }
    if (blockSize >= availMemory) {
        return -2;
    }
    block = getFreeBlock(blockSize);
    if (!block) {
        defragMemory();
        block = getFreeBlock(blockSize);
        if (!block) {
            return -2;
        }
    }
    BlockHeader blockHeader = readHeader(block);
    availMemory = blockHeader.size;
    blockHeader.size = blockSize;
    blockHeader.left = static_cast<uint8_t*>(block) - static_cast<uint8_t*>(pMemory) + 1;
    writeHeader(block, blockHeader);
    BlockHeader newBlockHeader = {0, availMemory - blockSize - getHeaderSize()};
    writeHeader(getNextBlock(block), newBlockHeader);
    allocMemory += blockSize + getHeaderSize();
    availMemory = availMemory - blockSize - getHeaderSize();
    return 0;
}

int freeBlock(VA va){
    void *block = getByVA(va);
    if (!block) {
        return -1;
    }
    BlockHeader blockHeader = readHeader(block);
    blockHeader.left = NULL;
    availMemory += getHeaderSize() + blockHeader.size;
    allocMemory -= (getHeaderSize() + blockHeader.size);
    writeHeader(block, blockHeader);
    mergeWithNextEmptyBlock(block);
    mergeWithPreviousEmptyBlock(block);
    return 0;
}

int initMemory(int n, size_t pageSize){
    size_t memorySize = n * pageSize;
    addrSize = ceil(log(memorySize) / log(2));
    if (n <= 0 || pageSize <= 1) {
        printf("\nMemory size should be greater than 1 byte \n");
        return -1;
    }
    printf("Allocating and Initializing memory for M3 ...\n");
    pMemory = malloc(memorySize);
    if (!pMemory) {
        perror("Unable to allocate memory");
        return -2;
    }
    BlockHeader header;
    header.left = NULL;
    header.size = memorySize - getHeaderSize();
    writeHeader(pMemory, header);
    pMemoryEnd = static_cast<uint8_t*>(pMemory) + memorySize;
    totalMemory = memorySize;
    availMemory = header.size;
    allocMemory = 0;
    return 0;
}

/**
 * @brief printMemory
 * Prints memory state
 */
void PrintMemory(){
    if (pMemory) {
        void* block = pMemory;
        printf("\n*---------------------------------------------------*\n");
        printf("|                    Memory Status                \t|\n");
        printf("*---------------------------------------------------*\n");
        printf("| Total     Memory\t\t\t:   %8lu\tbytes\t|\n", totalMemory);
        printf("| Allocated Memory\t\t\t:   %8lu\tbytes\t|\n", mallocBlock);
        printf("| Available Memory\t\t\t:   %8lu\tbytes\t|\n", (availMemory !=0 ? availMemory - getHeaderSize() : availMemory));
        printf("| Header    Size\t\t\t:   %8lu\tbytes\t|\n", getHeaderSize());
        printf("*---------------------------------------------------*\n");
        printf("| Actual Addr\t\t  VA\t| Size (bytes)\t| Status|\n");
        printf("*---------------------------------------------------*\n");
        while(block < pMemoryEnd){
            BlockHeader blockHeader = readHeader(block);
            const char memoryStatus = (blockHeader.left != 0 ?  'M' : 'A' );
            printf("| %p %10d\t| %10zu\t| \t%c\t|\n", block, blockHeader.left, blockHeader.size, memoryStatus);
            block = static_cast<uint8_t*>(block) +  getHeaderSize()+ blockHeader.size;
        }
        printf("*---------------------------------------------------*\n");
        printf("Memory Status:\t A -> Available\t M -> Malloc\n");
        printf("\n");
    }
}

