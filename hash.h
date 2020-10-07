#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
#include <vector>

class Hash
{
private:
	std::string input;
	std::string hash;
public:
	void hashReadConsole();
	void hashReadFile(std::string fileName);
	void toBinary(std::string input);
	void padding(std::string bin);
	void compression(std::string bin);
};