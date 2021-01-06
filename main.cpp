#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hash.h"
#include "timer.h"
#include "user.h"
#include "blockchain.h"
#include "generator.h"

int main(int argc, char* argv[])
{
	std::cout << "Program has started.\n" << std::endl;

	std::ofstream fileReset("Output.txt");

	if (argc == 1) {
		Hash hash;
	}
	else if (argc == 3 && std::string(argv[1]) == "hashtime") { //Time to has a file

		std::cout << "Reading file..." << std::endl;

		std::string input;
		std::vector<std::string> fullinput;

		std::ifstream file(argv[2]);
		while (!file.eof()) {
			std::getline(file, input);
			fullinput.push_back(input);
		}

		std::cout << "Hashing..." << std::endl;
		Timer timer("Total time to hash the file (read time not included):");
		for (int i = 0; i < fullinput.size() - 1; i++) {

			Hash hash(i, fullinput[i]);
		}
	}
	else if (argc == 3) { //Hash a file or a word.
		Hash hash(argv[1], argv[2]);
	}
	else
	{
		std::cout << "Invalid argument number" << std::endl;
	}

	/*User user("Tadas", "123", 12);
	std::cout << "Name: " << user.getName();
	std::cout << "public key: " << user.getPublic_key();
	std::cout << "Balance: " << user.getBalance();*/







	std::cout << "Testaaaasss: " << std::endl;
	Hash hash;
	std::cout << std::endl << "\nTiesiai is klases: " << std::endl << hash.toHash("labadiena") << std::endl << hash.toHash("labasvakaras");

	Generator generator;
	std::vector<User> users;
	std::vector<Transaction> transactions;
	
	// Useriu generacija

	std::cout << "\n\nGenerating users..." << std::endl;
	generator.generateUsers(users, 100);
	for (int i = 0; i < 100; i++) users[i].printUser();
	std::cout << "User generation has been completed" << std::endl;


	std::cout << "\n\nGenerating transactions..." << std::endl;
	generator.generateTransactions(transactions, users, 100);
	//for (int i = 0; i < 100; i++) users[i].printUser();
	std::cout << "Transaction generation has been completed" << std::endl;


	return 0;
}