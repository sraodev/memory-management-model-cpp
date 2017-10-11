//
//  main.cpp
//  MemoryManager
//
//  Created by श्री  on 15/09/17.
//  Copyright © 2017 Sri. All rights reserved.
//

#include <iostream>
#include "Memory.h"

void usage(){
    printf("p - Get memory status\n");
    printf("m - Allocate memory block\n");
    printf("f - Free allocated memory block\n");
    printf("w - Write to memory block\n");
    printf("r - Read from memory block\n");
    printf("d - Defragment memory block\n");
    printf("q - Quit\n\n");
}

int main() {
    VA va;
    int rStatus = 0;
    char *voidBuffer;
    size_t memorySize = 0;
    size_t size;
    char action[10];
    printf("****** Welcome to M3 ******!\n\n");
    printf("Enter memory size for M3 (bytes) : "); scanf("%zd",&memorySize);
    initMemory(1, memorySize);
    printMemory();
    while (action[0] != 'q') {
        printf("Enter action (h -> help) : "); scanf("%s", action);
        switch (action[0]) {
            case 'q':
                break;
            case 'm':
                printf("Malloc: Enter size (bytes) : "); scanf("%zd", &size);
                rStatus = mallocBlock(size);
                printMemory();
                if(rStatus == -1)
                    printf("Invalid params\n");
                if(rStatus == -2)
                    printf("Not enough memory\n");
                if(rStatus == 1)
                    printf("Unknown error\n");
                break;
            case 'f':
                printf("Free: Enter VA : "); scanf("%d", &va);
                rStatus = freeBlock(va);
                printMemory();
                if(rStatus == -1)
                    printf("Invalid VA\n");
                if(rStatus == 1)
                    printf("Unknown error\n");
                break;
            case 'w':
                printf("writeToBlock: Enter VA: "); scanf("%d", &va);
                printf("writeToBlock: Enter size (bytes): "); scanf("%zd", &size);
                voidBuffer = (char*)malloc(size);
                printf("writeToBlock: Enter data: "); scanf("%s", voidBuffer);
                rStatus = writeToBlock(va, &voidBuffer, size);
                printMemory();
                if(rStatus == -1)
                    printf("Invalid params\n");
                if(rStatus == -2)
                    printf("trying to access memory outside the block\n");
                if(rStatus == 1)
                    printf("Unknown error\n");
                break;
            case 'r':
                printf("readFromBlock: Enter addr: ");  scanf("%d", &va);
                std::cout << "readFromBlock: Enter size (bytes): "; scanf("%zd", &size);
                rStatus = readFromBlock(va, &voidBuffer, size);
                printMemory();
                if(rStatus == -1)
                    printf("Invalid params\n");
                if(rStatus == -2)
                    printf("trying to access memory outside the block\n");
                if(rStatus == 1)
                    printf("Unknown error\n");
                if(rStatus == 0)
                    printf("Buffer value :%s\n", voidBuffer);
                break;
            case 'h':
                usage();
                break;
            case 'd':
                defragMemory();
                break;
            default:
                printMemory();
                break;
        }
    }
    printf("\n****** M3 Cleaned Up ******!\n");
    return 0;
}
