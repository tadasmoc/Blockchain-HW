#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hash.h"
#include "timer.h"

int main(int argc, char* argv[])
{	
	std::cout << "Program has started\n" << std::endl;

	//Hash hash;

	if (argc == 1) {
		Hash hash;
	}
	else if (argc == 3 && (std::string(argv[1]) == "hash" || std::string(argv[1]) == "Hash")) {
		Hash hash(1, argv[2]);
	}
	else if (argc == 3 && (std::string(argv[1]) == "hashfile" || std::string(argv[1]) == "hashFile" || std::string(argv[1]) == "HashFile")) {
		Hash hash(1, argv[2]);
	}
	else if (argc == 3 && std::string(argv[1]) == "time") {

		std::cout << "Timer has started" << std::endl;
			
		std::string input;
		std::vector<std::string> fullinput;

		std::ifstream file(argv[2]);
		while (!file.eof()) {
			std::getline(file, input);
			fullinput.push_back(input);
		}

		Timer timer("Total time to hash the file:");
		for (int i = 0; i < fullinput.size()-1; i++) {
			Hash hash(1, fullinput[i]);
		}
	}
	else
	{
		std::cout << "Invalid argument number" << std::endl;
	}

	return 0;
}