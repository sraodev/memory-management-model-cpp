# Memory Management Model

## Allocating and Initializing memory for M3
```
****** Welcome to M3 ******!

Enter memory size for M3 (bytes) : 100
Allocating and Initializing memory for M3 ...

*---------------------------------------------------*
|                    Memory Status                  |
*---------------------------------------------------*
| Total     Memory         :     100    bytes       |
| Allocated Memory         :       0    bytes       |
| Available Memory         :      96    bytes       |
| Header    Size           :       2    bytes       |
*---------------------------------------------------*
| Actual Addr       VA    | Size (bytes)   | Status |
*---------------------------------------------------*
| 0x1005000b0       0     |           98   |     A  |
*---------------------------------------------------*
Memory Status:     A -> Available     M -> Malloc

Enter action (h -> help) : h
p - Get memory status
m - Allocate memory block
f - Free allocated memory block
w - Write to memory block
r - Read from memory block
d - Defragment memory block
q - Quit

Enter action (h -> help) :
```

## Allocating # bytes memory block in M3
```
Enter action (h -> help) : m
Malloc: Enter size (bytes) : 20

*---------------------------------------------------*
|                    Memory Status                  |
*---------------------------------------------------*
| Total     Memory            :        100    bytes |
| Allocated Memory            :         53    bytes |
| Available Memory            :         43    bytes |
| Header    Size              :          2    bytes |
*---------------------------------------------------*
| Actual Addr          VA   | Size (bytes)  | Status|
*---------------------------------------------------*
| 0x1005000b0          1    |         10    |   M   |
| 0x1005000bc         13    |          5    |   M   |
| 0x1005000c3         20    |         10    |   M   |
| 0x1005000cf         32    |         20    |   M   |
| 0x1005000e5          0    |         45    |   A   |
*---------------------------------------------------*
Memory Status:     A -> Available     M -> Malloc

```
## Writing to the allocated memory block
```
Enter action (h -> help) : w
writeToBlock: Enter VA: 1
writeToBlock: Enter size (bytes): 10
writeToBlock: Enter data: abcdefgh

*---------------------------------------------------*
|                    Memory Status                    |
*---------------------------------------------------*
| Total     Memory            :        100    bytes    |
| Allocated Memory            :         46    bytes    |
| Available Memory            :         50    bytes    |
| Header    Size            :          2    bytes    |
*---------------------------------------------------*
| Actual Addr          VA    | Size (bytes)    | Status|
*---------------------------------------------------*
| 0x1005000b0          1    |         10    |     M    |
| 0x1005000bc          0    |          5    |     A    |
| 0x1005000c3         20    |         10    |     M    |
| 0x1005000cf         32    |         20    |     M    |
| 0x1005000e5          0    |         45    |     A    |
*---------------------------------------------------*
Memory Status:     A -> Available     M -> Malloc
```

## Freeing allocated memory block
```
Enter action (h -> help) : f
Free: Enter VA : 13

*---------------------------------------------------*
|                    Memory Status                  |
*---------------------------------------------------*
| Total     Memory            :        100    bytes |
| Allocated Memory            :         46    bytes |
| Available Memory            :         50    bytes |
| Header    Size              :          2    bytes |
*---------------------------------------------------*
| Actual Addr          VA    | Size (bytes) | Status|
*---------------------------------------------------*
| 0x1005000b0          1    |         10    |   M   |
| 0x1005000bc          0    |          5    |   A   |
| 0x1005000c3         20    |         10    |   M   |
| 0x1005000cf         32    |         20    |   M   |
| 0x1005000e5          0    |         45    |   A   |
*---------------------------------------------------*
Memory Status:     A -> Available     M -> Malloc
```
## Reading from the memory block
```
Enter action (h -> help) : r
readFromBlock: Enter addr: 1
readFromBlock: Enter size (bytes): 10

*---------------------------------------------------*
|                    Memory Status                  |
*---------------------------------------------------*
| Total     Memory            :        100    bytes |
| Allocated Memory            :         46    bytes |
| Available Memory            :         50    bytes |
| Header    Size              :          2    bytes |
*---------------------------------------------------*
| Actual Addr          VA    | Size (bytes) | Status|
*---------------------------------------------------*
| 0x1005000b0          1    |         10    |   M   |
| 0x1005000bc          0    |          5    |   A   |
| 0x1005000c3         20    |         10    |   M   |
| 0x1005000cf         32    |         20    |   M   |
| 0x1005000e5          0    |         45    |   A   |
*---------------------------------------------------*
Memory Status:     A -> Available     M -> Malloc

Buffer value :abcdefgh
Enter action (h -> help) :
```
## Freeing allocated memory block
```
Enter action (h -> help) : f
Free: Enter VA : 13

*---------------------------------------------------*
|                    Memory Status                  |
*---------------------------------------------------*
| Total     Memory            :        100    bytes |
| Allocated Memory            :         46    bytes |
| Available Memory            :         50    bytes |
| Header    Size              :          2    bytes |
*---------------------------------------------------*
| Actual Addr          VA    | Size (bytes) | Status|
*---------------------------------------------------*
| 0x1005000b0          1    |         10    |   M   |
| 0x1005000bc          0    |          5    |   A   |
| 0x1005000c3         20    |         10    |   M   |
| 0x1005000cf         32    |         20    |   M   |
| 0x1005000e5          0    |         45    |   A   |
*---------------------------------------------------*
Memory Status:     A -> Available     M -> Malloc
```
