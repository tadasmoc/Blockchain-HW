# Blockchain Home Works - Hash function

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
|Input string from console|`[no argument]`|`[no argument]`| 
|Input string from cli|`hashstring` / `hashword`|`[your string]`|
|Input string from text file|`hashfile`|`[your_file_name.txt]`|
|Count the time to hash a txt file|`hashtime`|`[your_file_name.txt]`|

## Analysis
Ananlysis and its numbering dirrectly corresponds the task given ("Komentarai dėl eksperimentinio tyrimo-analizės atlikimo").
### 1. - Created the required files.

### 2. - After hashing the files, got these results
|File name|Result|
|---|---|
|1charA.txt|4C025E224FB6B8DBF02EA2EE735865C65EAB1201FD9E5656DF668F37B3A195B6|
|1charB.txt|F1315484AF6C08DE3CB849556C3826FBFF3C1EBB890622B83F06D61694A7B5B7|
|1001charA.txt|0B40C3A9639B610D472CF802C95B31355522F58CFF9CB74F658D26F3DAA1BFAB|
|1001charB.txt|B7257D9A3306F14A6869AE1223626367C1BCAAF35201AE910EC373E4D1273C2F|
|similar1001charA.txt|13326D53DDE7A6FBDAE632064A675DA4EE52AD1AC23F545E138BFB1108A07401|
|similar1001charB.txt|23FF830C6684FE71986006F24DA06D091709960250413D227241DAE22818B439|
|empty.txt|3FF2DCDF285A54690A0EF60421AFF883DC1E9D8D8BF11C0EF9FFFCD853E772F0|

Conclusion: The hash function accepts any size strings. Independently from the input, output stays the same size - 64 symbols long hexadecimal string. If we try to hash the same string again, we will get the same output value. Hence, the function meets the 1-3 requirements.

### 3. - Hashing big files
Total time to hash the file `"konstitucija.txt"` (read time not included): 4.30591s. The time to hash has been improved since the previuos versions, but there is still room for improvements.

### 4.& 5. - Collisions
The task is to hash 100k lines of random strings and then check the for collisions. However, the hash function is quite slow, thus, the test is only carried out with 50k (file: `"50000.txt"`) lines of random strings: 12.5k lines of 10 char strings, 12.5k lines of 100 char strings, 12.5k lines of 500 char strings, 12.5k lines of 1000 char strings. In total hash function needed 34 minutes to hash the whole file (including the output time). The results are in `"50k strings hashed.txt"` file. No collisions were detected. To conclude, the function proves to be reliable in terms of collisions.

### 6. - Statistics of difference
15k of similar string lines were used (file: `"similar15k.txt"`). There are two outputs of the file: `"15k output hex.txt"` - hexadecimal hashes, `"15k output bin.txt"` - binary hashes. The whole hexadecimal output has been checked for matching hashes and none were found.
#### Percentage of difference in hexadecimal output
91.8671%
#### Percentage of difference in binary output
48.2558%
