#include "hash.h"

Hash::Hash()
{
	hashReadConsole();
	printToHex(binaryHash);
}

Hash::Hash(std::string fileName)
{
	hashReadFile(fileName);
	printToHex(binaryHash);
}

Hash::Hash(std::string x, std::string in)
{
	input = in;
	std::cout << "Input: " << input << std::endl << std::endl;
	padding(input);
}

Hash::Hash(int x, std::string in)
{
	input = in;
	padding(input);
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

	padding(input);
}

void Hash::hashReadFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::getline(file, input);
	std::cout << "Input: " << input << std::endl << std::endl;

	padding(input);
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

	for (int i = 0; i < input.size(); i++) {
		asciiSize += int(input[i]);
	}

	for (int i = 0; i < input.size(); i++) {
		result += std::to_string(int(input[i]) + asciiSize);
		//std::cout << "result: " << result << std::endl;
	}

	return toBinary(result);
}

void Hash::padding(std::string &bin)
{
	bin = toBinary(bin);
	std::string BinEnd = binEnd(); // A string generated from the length of input and ASCII values. This will be added to the end of padded bin variable.
	
	int binEndSize = BinEnd.size();
	if ((bin.size() + binEndSize) % 512 != 0) {
		bin += "1";
	}
		
	while ((bin.size() + binEndSize) % 512 != 0) {
		bin += "0";
	}
	bin += BinEnd;

	//std::cout << "Padded: " << bin << std::endl;

	compression(bin);
}

std::string Hash::binaryAddition(std::string a, std::string b) //For future?
{
	std::string result = "";
	
	return result;
}

void Hash::expand(std::vector<std::string> &block32)
{
	//std::cout << "Expanding started, current size: " << block32.size() << std::endl;
	for (int i = 16; i < 64; i++) {
		std::string a = xorString(block32[i - 2], block32[i - 7]); //    binaryAddition(xorString(block32[i - 2], block32[i - 7]), xorString(block32[i - 15], block32[i - 16]));
		std::string b = xorString(block32[i - 15], block32[i - 16]);
		std::rotate(b.begin(), b.begin() + 5, b.end());
		b = xorString(a, b);
		block32.push_back(a);
	}
}

void Hash::compression(std::string bin)
{
	std::vector<std::string> block512;
	std::vector<std::string> block32; // 32bit x 16. total - 512. Later extended to 32bit x 64 and then compressed to 32bit x 8.
	std::vector<std::string> temporary;

	//Everything is split into 512bit blocks.
	int t = 0;
	while (bin.size() != 0) {
		block512.push_back(bin.substr(bin.size() - 512, bin.size()));
		for (int i = 0; i < 512; i++) bin.pop_back(); // potentialy slow.

		//std::cout << "block[" << t << "] " << block512[t] << std::endl;
		//std::cout << "size: " << bin.size() << std::endl;

		t++;
	}

	for (int z = 0; z < block512.size(); z++)
	{

		//From 512bit block to 32bit x 16 blocks
		t = 0;
		while (block512[z].size() != 0) {
			block32.push_back(block512[z].substr(block512[z].size() - 32, block512[z].size()));
			for (int i = 0; i < 32; i++) block512[z].pop_back(); // Potentialy slow.
			t++;
		}

		//Expanding from 32bit x 16 blocks to 32bit x 64.
		expand(block32);

		//Pirmas maisymas
		for (int i = 63; i > 0; i--) {
			block32[i - 1] = xorString(block32[i - 1], block32[i]);
		}
		std::swap(block32[3], block32[60]);

		//Antras maisymas
		for (int i = 1; i < 64; i += 3) {
			std::rotate(block32[i].begin(), block32[i].begin() + 5, block32[i].end());
		}
		std::swap(block32[10], block32[53]);


		//Trecias maisymas
		for (int i = 63; i > 0; i--) {
			block32[i - 1] = xorString(block32[i - 1], block32[i]);
		}
		std::swap(block32[19], block32[44]);


		//Ketvirtas maisymas + kompresavimas
		for (int i = 0; i < 64; i += 2) {
			temporary.push_back(xorString(block32[i], block32[i + 1]));
		}
		block32 = temporary;
		temporary.clear();
		std::swap(block32[5], block32[27]);

		//Penktas maisymas + kompresavimas
		for (int i = 0; i < 32; i += 2) {
			temporary.push_back(xorString(block32[i], block32[i + 1]));
		}
		block32 = temporary;
		temporary.clear();


		//Sestas maisymas + kompresavimas
		for (int i = 0; i < 16; i += 2) {
			temporary.push_back(xorString(block32[i], block32[i + 1]));
		}
		block32 = temporary;
		temporary.clear();



		// TODO: butinai pakeist del avalanche efekto ir collisionu.
		for (int i = 0; i < 8; i++) {
			binaryHash[i] = xorString(binaryHash[i], block32[i]);
		}

		block32.clear();
	}
}

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

void Hash::printToHex(std::vector<std::string> binaryHash)
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