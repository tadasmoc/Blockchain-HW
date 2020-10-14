# Blockchain-HW

## How the program works
1. Program starts and reads a string either form console or from a .txt file.
2. Given input is converted to binary.
3. Binary is then padded until it's length is divisible by 512.
4. Then binary is divided into 512bit blocks and those blocks are divided into 16 32bit blocks.
5. Then those 16 32bit blocks are expanded into 64 32bit blocks.
6. The blocks then are shuffled, compressed and mashed together with 8 constant variables.
7. Binary is onverted to hexadecimal and output is given.

## How to start the program
0 arguments - console input.  
1 argument - argument corresponds to the name of the file to read.  
2 arguments - first argument needs to be "time", second the name of the file to read. Starting the prgoram this way, will count the time to hash a file.  
