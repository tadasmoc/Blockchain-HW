#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hash.h"
#include "timer.h"
#include "user.h"
#include "blockchain.h"
#include "generator.h"

#define USR_NO 10    // Users number
#define TRNS_NO 20   // Transactions number
#define DIFF 2       // Mining difficulty
#define BLOCK_SIZE 5 // How many transactions in the block.

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


	std::cout << "Blockchain pradzia" << std::endl << std::endl;
	Hash hash;
	Generator generator;
	std::vector<User> users;
	std::vector<Transaction> transactions;
	
	// Users generation

	std::cout << "\n\nGenerating users..." << std::endl;
	generator.generateUsers(users, USR_NO);
	for (int i = 0; i < users.size(); i++) users[i].printUser();
	std::cout << "User generation has been completed" << std::endl;

	// Transaction generation

	std::cout << "\n\nGenerating transactions..." << std::endl;
	generator.generateTransactions(transactions, users, TRNS_NO);
	for (int i = 0; i < transactions.size(); i++) transactions[i].printTransaction();
	std::cout << "Transaction generation has been completed" << std::endl;



	// Blockchain start
	std::cout << "Blockchain start" << std::endl;

	std::vector<Block> blocks;

	std::string diff; // Var for determining if correct hash has correct difficulty.
	for (int i = 0; i < DIFF; i++) {
		diff += "0";
	}



	// ---Genesis block generation---

	std::string merkel_hash = "";
	long int nonce = 0;
	Block Gblock;

	Gblock.setTimestamp(Gblock.timestampFunct()); // Bloko starto laikas.

	Gblock.setPrev_hash("0000000000000000000000000000000000000000000000000000000000000000");
	Gblock.setVersion(0); // Cia po to bus 'i'.


		// ---Selection of transactions---

	int r; // Random number for choosing the transactions.
	if (transactions.size() - BLOCK_SIZE != 0) {
		srand(time(0));
		r = rand() % (transactions.size() - BLOCK_SIZE);
	}
	else r = 0;
	std::cout << "RAND: " << r << std::endl;

	for (int i = 0; i < BLOCK_SIZE; i++) {
		Gblock.push_transaction(transactions[r + i]);
	}
	
	// ---Proof of Work---
	do {
		nonce++;
		merkel_hash = hash.toHash(Gblock.getPrev_hash() + std::to_string(Gblock.getTimestamp()) + std::to_string(Gblock.getVersion()) + std::to_string(nonce) + std::to_string(Gblock.getDifficulty()));
	} while (merkel_hash.substr(0, DIFF) != diff);
	Gblock.setNonce(nonce);
	Gblock.setMerkel_hash(merkel_hash);

		// Deletion of transaction from pool.
	transactions.erase(transactions.begin() + r, transactions.begin() + r + BLOCK_SIZE);

		// Execution of transactions in the block.
	Gblock.execTrans(users);
	std::cout << "0. Transaction sucessfully executed!!!" << std::endl;

	std::cout << "nonce: " << nonce << std::endl;
	std::cout << "hash: " << merkel_hash << std::endl;

	blocks.push_back(Gblock);


	for (int i = 1; i < transactions.size(); i++) {
		merkel_hash = "";
		nonce = 0;
		Block block;

		block.setTimestamp(block.timestampFunct()); // Bloko starto laikas.

		block.setPrev_hash(blocks[i - 1].getMerkel_hash());
		block.setVersion(i);

			// ---Selection of transactions---

		//int r; // Random number for choosing the transactions.
		if (transactions.size() - BLOCK_SIZE != 0) {
			srand(time(0));
			r = rand() % (transactions.size() - BLOCK_SIZE);
		}
		else r = 0;
		std::cout << "RAND: " << r << std::endl;

		for (int t = 0; t < BLOCK_SIZE; t++) {
			block.push_transaction(transactions[r + t]);
		}

		// ---Proof of Work---
		do {
			nonce++;
			merkel_hash = hash.toHash(block.getPrev_hash() + std::to_string(block.getTimestamp()) + std::to_string(block.getVersion()) + std::to_string(nonce) + std::to_string(block.getDifficulty()));
		} while (merkel_hash.substr(0, DIFF) != diff);
		block.setNonce(nonce);
		block.setMerkel_hash(merkel_hash);

		// Deletion of transaction from pool.
		transactions.erase(transactions.begin() + r, transactions.begin() + r + BLOCK_SIZE);

		// Execution of transactions in the block.
		block.execTrans(users);
		std::cout << i << ". Transaction sucessfully executed!!!" << std::endl;

		std::cout << "nonce: " << nonce << std::endl;
		std::cout << "hash: " << merkel_hash << std::endl;

		blocks.push_back(block);

		std::cout << std::endl;
	}

	// Printing BlockChain

	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].printBlock();
		std::cout << std::endl;
	}

	return 0;
}