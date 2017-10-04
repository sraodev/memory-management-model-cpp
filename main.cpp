//
//  main.cpp
//  MemoryManager
//
//  Created by श्री  on 15/09/17.
//  Copyright © 2017 Sri. All rights reserved.
//

#include <iostream>
#include "memory.h"

void Usage(){
    std::cout << ("p - print memory\n");
    std::cout << ("m - malloc\n");
    std::cout << ("f - free\n");
    std::cout << ("w - write (as unsigned integer, will will be scliced bitly by entered size)\n");
    std::cout << ("r - read (same as write, will be readed as unsigned integer)\n");
    std::cout << ("q - quit\n\n");
}

int main() {
    int rStatus = 0;
    VA va;
    int buff;
    size_t memorySize;
    size_t size;
    char action[10];
    std::cout << "****** Welcome to M3 ******!\n\n";
    std::cout << "Enter memory size for M3 (bytes) : "; std::cin >> memorySize;
    initMemory(1, memorySize);
    PrintMemory();

    while (action[0] != 'q') {
        std::cout << "Enter action (h -> help) : "; std::cin >> action;
        switch (action[0]) {
            case 'q':
                break;
            case 'm':
                std::cout << "Malloc: Enter size : "; std::cin >> size;
                rStatus = mallocBlock(size);
                PrintMemory();
                if(rStatus == -1)
                    std::cout << ("Invalid params\n");
                if(rStatus == -2)
                    std::cout << ("Not enough memory\n");
                if(rStatus == 1)
                    std::cout << ("Unknown error\n");
                break;
            case 'f':
                std::cout << "Free: Enter VA : "; std::cin >> va;
                rStatus = freeBlock(va);
                PrintMemory();
                if(rStatus == -1)
                    std::cout << ("Invalid params\n");
                if(rStatus == 1)
                    std::cout << ("Unknown error\n");
                break;
            case 'w':
                printf("write: enter addr>> ");  scanf("%d", &va);
                printf("write: enter size>> ");  scanf("%ld", &size);
                printf("write: enter data>> ");scanf("%d", &buff);
                rStatus = writeToBlock(va, &buff, size);
                PrintMemory();
                if(rStatus == -1)
                    std::cout << "invalid params\n";
                if(rStatus == -2)
                    std::cout << "trying to access memory outside the block\n";
                if(rStatus == 1)
                    std::cout << ("unknown error\n");
                
                break;
            case 'r':
                std::cout << "read: enter addr>>";  std::cin >> va;
                std::cout << "read: enter size>>"; std::cin >> size;
                rStatus = readFromBlock(va, &buff, size);
                PrintMemory();
                if(rStatus == -1)
                    std::cout << "invalid params\n";
                if(rStatus == -2)
                    std::cout << "trying to access memory outside the block\n";
                if(rStatus == 1)
                    std::cout << "unknown error\n";
                if(rStatus == 0)
                    std::cout << "read rStatus:%d" << buff << std::endl;
                break;

            case 'h':
                Usage();
                break;
            default:
                PrintMemory();
                break;
        }
    }
    std::cout << "\n****** M3 Cleaned Up ******!\n";
    return 0;
}
