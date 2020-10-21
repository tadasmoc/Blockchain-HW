#include "hash.h"

Hash::Hash()
{
	hashReadConsole();
	printToHex(binaryHash);
}

Hash::Hash(std::string arg1, std::string arg2)
{
	if(arg1 == "hashfile") hashReadFile(arg2);
	else {
		input = arg2;
		std::cout << "Input: " << input << std::endl << std::endl;
		padding();
	}

	printToHex(binaryHash);
}

/*Hash::Hash(std::string& in, int& x)
{
	input = in;
	std::cout << "Input: " << input << std::endl << std::endl;
	padding();
}*/

Hash::Hash(int& x, std::string& in)
{
	input = in;
	padding();
	//printToHexFile(binaryHash); // Prints hashes to file.
}

Hash::~Hash()
{
	//std::cout << "\nDESTRUCTED\n\n";
}


void Hash::hashReadConsole()
{
	std::cout << "Please type in your value:" << std::endl;
	std::getline(std::cin, input);
	std::cout << "Input: " << input << std::endl << std::endl;

	padding();
}

void Hash::hashReadFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::getline(file, input);
	std::cout << "Input: " << input << std::endl << std::endl;

	padding();
}

std::string Hash::toBinary(std::string text)
{
	std::string binary; // String to hold binary string value.

	for (std::size_t i = 0; i < text.size(); ++i)
	{
		binary += std::bitset<8>(text[i]).to_string();
	}
	//std::cout << "Converted to bin: " << binary << std::endl;

	return binary;
}

std::string Hash::binEnd()
{
	std::string result;
	int asciiSize = 0;

	for (int i = 0; i < input.size(); i++) {
		asciiSize += int(input[i]);
	}

	for (int i = 0; i < input.size(); i++) {
		result += std::to_string(int(input[i]) * (i+1));
		//std::cout << "result: " << result << std::endl;
	}
	result += std::to_string(asciiSize);

	return toBinary(result);
}

void Hash::padding()
{
	std::string BinEnd = binEnd(); // A string generated from the length of input and ASCII values. This will be added to the end of padded bin variable.
	input = toBinary(input); // Initial input.
	
	int binEndSize = BinEnd.size();
	if ((input.size() + binEndSize) % 512 != 0) {
		input += "1";
	}
		
	while ((input.size() + binEndSize) % 512 != 0) {
		input += "0";
	}
	input += BinEnd;

	//std::cout << "Padded: " << input << std::endl;

	compression();
}

std::string Hash::binaryAddition(std::string a, std::string b) //For future?
{
	std::string result = "";
	
	return result;
}

void Hash::expand(std::vector<std::string> &block32)
{
	for (int i = 16; i < 64; i++) {
		block32.push_back(addBinary(addBinary(B(block32[i-5]), block32[i-2]), addBinary(A(block32[i-13]), block32[i-16])));
	}
}

void Hash::compression()
{
	std::vector<std::string> block512;
	std::vector<std::string> block32; // 32bit x 16. total - 512. Later extended to 32bit x 64 and then compressed to 32bit x 8.
	std::vector<std::string> temporary;

	//Everything is split into 512bit blocks.
	while (input.size() != 0) {
		block512.push_back(input.substr(input.size() - 512, input.size()));

		input.erase(input.end() - 512, input.end());
	}

	for (int z = 0; z < block512.size(); z++)
	{
		//From 512bit block to 32bit x 16 blocks
		while (block512[z].size() != 0) {
			block32.push_back(block512[z].substr(block512[z].size() - 32, block512[z].size()));

			block512[z].erase(block512[z].end()-32, block512[z].end());
		}

		//Expanding from 32bit x 16 blocks to 32bit x 64.
		expand(block32);

		//First shuffle + compression
		for (int i = 0; i < 64; i += 2) {
			temporary.push_back(xorString(block32[i], block32[i + 1]));
		}
		block32 = temporary;
		temporary.clear();
		std::swap(block32[5], block32[27]);
		for (int i = 1; i < 9; i+=2) {
			addBinary(D(block32[i * 3]), binaryHash[i-1]);
		}

		//Second shuffle + compression
		for (int i = 0; i < 32; i += 2) {
			temporary.push_back(xorString(block32[i], block32[i + 1]));
		}
		block32 = temporary;
		temporary.clear();
		for (int i = 0; i < 8; i+= 2) {
			xorString(C(block32[i*2]), binaryHash[i]);
		}

		//Third shuffle + compression
		for (int i = 0; i < 16; i += 2) {
			temporary.push_back(xorString(block32[i], block32[i + 1]));
		}
		block32 = temporary;
		temporary.clear();

		//Fourth shuffle
		for (int i = 0; i < 8; i++) {
			binaryHash[i] = xorString(binaryHash[i], B(block32[i]));
		}
		std::swap(binaryHash[0], binaryHash[7]);

		block32.clear();
	}
}

void Hash::printToHex(std::vector<std::string>& binaryHash)
{
	for (int t = 0; t < 8; t++) {
		std::string rest(""), tmp, chr = "";
		int len = binaryHash[t].length() / 4;
		chr = chr.substr(0, len);
		binaryHash[t] = chr + binaryHash[t];
		for (int i = 0; i < binaryHash[t].length(); i += 4)
		{
			tmp = binaryHash[t].substr(i, 4);
			if (!tmp.compare("0000"))
			{
				rest = rest + "0";
			}
			else if (!tmp.compare("0001"))
			{
				rest = rest + "1";
			}
			else if (!tmp.compare("0010"))
			{
				rest = rest + "2";
			}
			else if (!tmp.compare("0011"))
			{
				rest = rest + "3";
			}
			else if (!tmp.compare("0100"))
			{
				rest = rest + "4";
			}
			else if (!tmp.compare("0101"))
			{
				rest = rest + "5";
			}
			else if (!tmp.compare("0110"))
			{
				rest = rest + "6";
			}
			else if (!tmp.compare("0111"))
			{
				rest = rest + "7";
			}
			else if (!tmp.compare("1000"))
			{
				rest = rest + "8";
			}
			else if (!tmp.compare("1001"))
			{
				rest = rest + "9";
			}
			else if (!tmp.compare("1010"))
			{
				rest = rest + "A";
			}
			else if (!tmp.compare("1011"))
			{
				rest = rest + "B";
			}
			else if (!tmp.compare("1100"))
			{
				rest = rest + "C";
			}
			else if (!tmp.compare("1101"))
			{
				rest = rest + "D";
			}
			else if (!tmp.compare("1110"))
			{
				rest = rest + "E";
			}
			else if (!tmp.compare("1111"))
			{
				rest = rest + "F";
			}
			else
			{
				continue;
			}
		}
		std::cout << rest;
	}
	std::cout << std::endl;
}

void Hash::printToHexFile(std::vector<std::string>& binaryHash)
{
	std::ofstream output;
	output.open("Output.txt", std::ofstream::app);
	
	for (int t = 0; t < 8; t++) {
		std::string rest(""), tmp, chr = "";
		int len = binaryHash[t].length() / 4;
		chr = chr.substr(0, len);
		binaryHash[t] = chr + binaryHash[t];
		for (int i = 0; i < binaryHash[t].length(); i += 4)
		{
			tmp = binaryHash[t].substr(i, 4);
			if (!tmp.compare("0000"))
			{
				rest = rest + "0";
			}
			else if (!tmp.compare("0001"))
			{
				rest = rest + "1";
			}
			else if (!tmp.compare("0010"))
			{
				rest = rest + "2";
			}
			else if (!tmp.compare("0011"))
			{
				rest = rest + "3";
			}
			else if (!tmp.compare("0100"))
			{
				rest = rest + "4";
			}
			else if (!tmp.compare("0101"))
			{
				rest = rest + "5";
			}
			else if (!tmp.compare("0110"))
			{
				rest = rest + "6";
			}
			else if (!tmp.compare("0111"))
			{
				rest = rest + "7";
			}
			else if (!tmp.compare("1000"))
			{
				rest = rest + "8";
			}
			else if (!tmp.compare("1001"))
			{
				rest = rest + "9";
			}
			else if (!tmp.compare("1010"))
			{
				rest = rest + "A";
			}
			else if (!tmp.compare("1011"))
			{
				rest = rest + "B";
			}
			else if (!tmp.compare("1100"))
			{
				rest = rest + "C";
			}
			else if (!tmp.compare("1101"))
			{
				rest = rest + "D";
			}
			else if (!tmp.compare("1110"))
			{
				rest = rest + "E";
			}
			else if (!tmp.compare("1111"))
			{
				rest = rest + "F";
			}
			else
			{
				continue;
			}
		}
		output << rest;
	}
	output << std::endl;
	output.close();
}

// Shuffle functions

std::string Hash::xorString(std::string a, std::string b)
{
	std::string ans;

	for (int i = 0; i < a.size(); i++)
	{
		// If the Character matches 
		if (a[i] == b[i])
			ans += "0";
		else
			ans += "1";
	}
	return ans;
}

std::string Hash::addBinary(std::string a, std::string b)
{
	std::string s = "";
	int c = 0, i = a.size() - 1, j = b.size() - 1;
	while (i >= 0 || j >= 0 || c == 1)
	{
		c += i >= 0 ? a[i--] - '0' : 0;
		c += j >= 0 ? b[j--] - '0' : 0;
		s = char(c % 2 + '0') + s;
		c /= 2;
	}

	while (s.size() != 32) {
		s.pop_back();
	}

	return s;
}

std::string Hash::lshift(std::string a, int n)
{
	for (int i = 1; i <= n; i++) {
		for (int t = 0; t < a.size() - 1; t++) {
			a[t] = a[t + 1];
		}
		a[a.size() - i] = '0';
	}
	return a;
}

std::string Hash::A(std::string a)
{
	std::string b = a;
	std::string c = a;

	std::rotate(a.begin(), a.begin() + 3, a.end());
	std::rotate(b.begin(), b.begin() + 7, b.end());

	a = xorString(a, b);
	c = lshift(c, 10);
	a = xorString(a, c);

	return a;
}

std::string Hash::B(std::string a)
{
	std::string b = a;
	std::string c = a;

	std::rotate(a.begin(), a.begin() + 19, a.end());
	std::rotate(b.begin(), b.begin() + 13, b.end());

	a = xorString(a, b);
	c = lshift(c, 3);
	a = xorString(a, c);

	return a;
}

std::string Hash::C(std::string a)
{
	std::string b = a;
	std::string c = a;

	std::rotate(a.begin(), a.begin() + 10, a.end());
	std::rotate(b.begin(), b.begin() + 18, b.end());
	std::rotate(c.begin(), c.begin() + 2, c.end());

	b = xorString(a, b);
	a = xorString(b, c);

	return a;
}

std::string Hash::D(std::string a)
{
	std::string b = a;
	std::string c = a;

	std::rotate(a.begin(), a.begin() + 3, a.end());
	std::rotate(b.begin(), b.begin() + 18, b.end());
	std::rotate(c.begin(), c.begin() + 12, c.end());

	b = xorString(a, b);
	a = xorString(b, c);

	return a;
}