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
void printMemory();

/**
   @func initMemory
   @brief Initializing the Memory Manager Model
  
   @param [in] n number of pages
   @param [in] szPage page size
  
   In version 1 and 2, the total memory is calculated as n * szPage
  
   @return error code
   @retval 0 successful execution
   @retval -1 incorrect parameters
   @retval 1 unknown error
   **/
int initMemory(int n, size_t szPage);

/**
 @func    mallocBlock
 @brief     Selects a block of memory of a certain size
 
 @param [in] blockSize block size
  
 @return error code
 @retval 0 successful execution
 @retval -1 incorrect parameters
 @retval -2 lack of memory
 @retval 1 unknown error
 **/
int mallocBlock(size_t blockSize);

/**
   @func _free
   @brief Removing a Memory Block
  
   @param [in] va address of the block
  
   @return error code
   @retval 0 successful execution
   @retval -1 incorrect parameters
   @retval 1 unknown error
   **/
int freeBlock(VA va);

/**
   @func _write
   @brief Writing information to a memory block
  
   @param [in] va address of the block
   @param [in] pBuffer the address of the buffer to which the information is copied
   @param [in] bufferSize buffer size
  
   @return error code
   @retval 0 successful execution
   @retval -1 incorrect parameters
   @retval -2 access outside the block
   @retval 1 unknown error
   **/
int writeToBlock(VA va, void *pBuffer, size_t bufferSize);

/**
   @func _read
   @brief Reading information from a memory block
  
   @param [in] va address of the block
   @param [in] pBuffer buffer address where the info is copied
   @param [in] bufferSize buffer size
  
   @return error code
   @retval 0 successful execution
   @retval -1 incorrect parameters
   @retval -2 access outside the block
   @retval 1 unknown error
   **/
int readFromBlock(VA va, void *pBuffer, size_t bufferSize);

#endif /* memory_h */
