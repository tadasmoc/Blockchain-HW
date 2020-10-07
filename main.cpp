#include <iostream>
#include <string>
#include "hash.h"

int main(int argc, char* argv[])
{	
	std::cout << "Program has started\n" << std::endl;

	Hash hash;

	if (argc == 1) {
		hash.hashReadConsole();
	}
	else if (argc == 2) {
		hash.hashReadFile(argv[1]);
	}
	else
	{
		std::cout << "Invalid argument number" << std::endl;
	}




	return 0;
}