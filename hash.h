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
	//std::string hash;
public:
	std::string A = "01010010011000010111001101110000";
	std::string B = "01110101011101000110100101101110";
	std::string C = "01001100011011110111011001100101";
	std::string D = "01110010011011110110011001110100";
	std::string E = "01101000011001010101001001110101";
	std::string F = "01110011011100110110100101100001";
	std::string G = "01101110011100010111010101100101";
	std::string H = "01100101011011100010000100111111";

	std::vector<std::string> test =
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


	// Default constructor
	Hash();

	// Constructor for hashig from file
	Hash(std::string fileName);

	// Constructor for timing hashes
	Hash(int x, std::string input);

	// Destructor
	~Hash();


	void hashReadConsole();
	void hashReadFile(std::string fileName);
	std::string toBinary(std::string text);
	void padding(std::string bin);
	void compression(std::string bin);
	std::string xorString(std::string a, std::string b);
	std::string binaryAddition(std::string a, std::string b);
	void binToHex(std::vector<std::string> hashBin);
	std::string binEnd();
	void expand(std::deque<std::string> &block32);


};