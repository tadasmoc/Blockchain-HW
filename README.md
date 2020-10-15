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
|Action|Argument #1|Argument #2|
|---|---|---|
|Input string from console|[no argument]|[no argument]| 
|Input string from cli|hash|[your string]|
|Input string from text file|hashfile|[your_file_name.txt]|
|Count the time to hash a txt file|time|[your_file_name.txt]|
