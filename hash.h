#pragma once

#include <bit>
#include <cstdint>
#include <limits>

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <vector>
#include <deque>
#include <algorithm>


class Hash
{
private:
	std::string input;
	std::vector<std::string> binaryHash =
	{
		"01010010011000010111001101110000",
		"01110101011101000110100101101110",
		"01001100011011110111011001100101",
		"01110010011011110110011001110100",
		"01101000011001010101001001110101",
		"01110011011100110110100101100001",
		"01101110011100010111010101100101",
		"01100101011011100010000100111111"
	};

public:
	// Default constructor
	Hash();

	// Constructor for hashing from file
	Hash(std::string arg1, std::string arg2);

	// Constructor for hasing a word from cli
	//Hash(std::string& in, int& x);

	// Constructor for timing hashes
	Hash(int& x, std::string& in);

	// Destructor
	~Hash();

	void hashReadConsole();
	void hashReadFile(std::string fileName);
	void padding();
	void compression();
	void expand(std::vector<std::string>& block32);
	void printToHex(std::vector<std::string>& hashBin);
	void printToHexFile(std::vector<std::string>& hashBin);

	std::string toBinary(std::string text);
	std::string binEnd();

	// Shuffle functions
	std::string xorString(std::string a, std::string b);
	std::string addBinary(std::string a, std::string b);
	std::string lshift(std::string a, int n);
	std::string A(std::string a);
	std::string B(std::string a);
	std::string C(std::string a);
	std::string D(std::string a);

};