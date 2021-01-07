# Blockchain Home Works - Create a simplified blockchain

## How to start the program
1. Open the folder of the program in your terminal.
2. Type in the command `g++ main.cpp blockchain.h blockchain.cpp user.h user.cpp generator.h generator.cpp timer.h timer.cpp hash.h hash.cpp`.
3. Then execute the generated file `./a.out`.
4. Then, depending of the program settings, it will generate some amount of users and transactions (pool). After that, the program will randomly pick transactions from the generated transaction pool and will put it in to the new block as well as generate Merkle hash from them. Then, proof of work will be done and after that, the picked transactions will be deleted from the pool, the transactions will be executed and the new block will be added to the blockchain.

## Program settings
To access progrma settings, open the `main.cpp` file. Setting will be at the top:
```C++
//-Settings------------------------------------------------
#define USR_NO 50     // Users number
#define TRNS_NO 100   // Transactions number
#define DIFF 3        // Mining difficulty
#define BLOCK_SIZE 10 // How many transactions in the block.
//---------------------------------------------------------
```
There the numbers can be adjusted to suit the needs of the test better.

## How the hash works
1. Program starts and reads a string either form console or from a .txt file.
2. Given input is converted to binary.
3. Binary is then padded until it's length is divisible by 512.
4. Then binary is divided into 512bit blocks and those blocks are divided into 16 32bit blocks.
5. Then those 16 32bit blocks are expanded into 64 32bit blocks.
6. The blocks then are shuffled, compressed and mashed together with 8 constant variables.
7. Binary is onverted to hexadecimal and output is given.
