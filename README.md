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
|Input string from text file|hashfile|`[your_file_name.txt]`|
|Count the time to hash a txt file|time|`[your_file_name.txt]`|

## Analysis
### 1. Created the required files.

### 2. After hashing the files, got these results
|File name|Result|
|---|---|
|1charA|1E8D149A03F4696E4C6F766504EF667468655275A373696FBE71756B2CD11100|
|1charB|A621749F37F4696E4C6F766530EF667468655275237369693E71756D14DC120C|
|1001charA|3FD021FD500C3B4AB4AA4362E26A183F6599084684EB2E90E4C8508CD6FA8F50|
|1001charB|868A92CE27462076B29BBE17CE9CDFAD6F6D26DE24B6282F7DA06F4EF3424EE0|
|similar1001charA|2D8B41E372735239406695F0829EE9AA7B51B4502DFDEC7169C78218996BA697|
|similar1001charB|E34540265D72523741A8941FAC5EE9AA7AB1B450CDFDED9A89C983F2B7A5A6B6|
|empty|526173707574696E4C6F7665726F667468655275737369616E717565656E213F|

Conclusion: The hash function accepsts any size strings. Independently from the input, output stays the same size - 64 symbols long hexadecimal string. If we try to hash the same string again, we will get the same output value. Hence, the function meets the 1-3 requirements.

### 3. Hashing big files
To hash the file `konstitucija.txt` function needed 12.9274s. The time is not ideal, and there is lots of room for improvements.