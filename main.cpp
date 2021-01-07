#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hash.h"
#include "timer.h"
#include "user.h"
#include "blockchain.h"
#include "generator.h"

//-Settings------------------------------------------------
#define USR_NO 50     // Users number
#define TRNS_NO 100   // Transactions number
#define DIFF 3        // Mining difficulty
#define BLOCK_SIZE 10 // How many transactions in the block.
//---------------------------------------------------------

int main()
{
	std::cout << "Blockchain Home Works\n\nProgram status:\n\n";
	Hash hash;
	Generator generator;
	std::vector<User> users;
	std::vector<Transaction> transactions;
	
	// Users generation

	std::cout << "Generating " << USR_NO << " users..." << std::endl;
	generator.generateUsers(users, USR_NO);
	//for (int i = 0; i < users.size(); i++) users[i].printUser(); // Print generated users

	// Transaction generation

	std::cout << "\nGenerating " << TRNS_NO << " transactions..." << std::endl;
	generator.generateTransactions(transactions, users, TRNS_NO);
	//for (int i = 0; i < transactions.size(); i++) transactions[i].printTransaction(); // Print generated transactions

	// Blockchain start

	std::cout << "\nBlockchain simulation has been started" << std::endl;

	std::string diff; // Var, used for checking the difficulty
	for (int i = 0; i < DIFF; i++) diff += "0";


	std::vector<Block> blocks; // Var which stores the 'blockchain'
	std::string merkel_hash;
	long int nonce = 0;
	Block Gblock; // Genesis block

	// Genesis block generation

	Gblock.setTimestamp(Gblock.timestampFunct()); // Block start time.
	Gblock.setPrev_hash("0000000000000000000000000000000000000000000000000000000000000000");
	Gblock.setDifficulty(DIFF);
	Gblock.setVersion(0);

	// --- Random selection of transactions

	int r; // Random number for choosing the transactions.
	if (transactions.size() - BLOCK_SIZE != 0) {
		srand(time(0));
		r = rand() % (transactions.size() - BLOCK_SIZE);
	}
	else r = 0;
	std::cout << "\nTransactions " << r << " to " << r + BLOCK_SIZE << " have been selected from the pool" << std::endl;

	for (int t = 0; t < BLOCK_SIZE; t++) Gblock.push_transaction(transactions[r + t]);
	
	// --- Proof of Work

	std::cout << "Proof of work started with difficulty of " << DIFF << std::endl;
	do {
		nonce++;
		merkel_hash = hash.toHash(Gblock.getPrev_hash() + std::to_string(Gblock.getTimestamp()) + std::to_string(Gblock.getVersion()) + std::to_string(nonce) + std::to_string(Gblock.getDifficulty()));
	} while (merkel_hash.substr(0, DIFF) != diff);
	Gblock.setNonce(nonce);
	Gblock.setMerkel_hash(merkel_hash);
	std::cout << "Hash has been found: " << merkel_hash << ", nonce value: " << nonce << std::endl;

	// Delete old transactions from the pool
	transactions.erase(transactions.begin() + r, transactions.begin() + r + BLOCK_SIZE);

	// Execute the block transactions
	Gblock.execTrans(users);

	blocks.push_back(Gblock);

	std::cout << "0. Transaction sucessfully executed, block added to the chain" << std::endl;

	// Blocks generation after genesis

	for (int i = 1; i < transactions.size(); i++) {

		nonce = 0;
		Block block;

		block.setTimestamp(block.timestampFunct()); // Block start time.
		block.setPrev_hash(blocks[i - 1].getMerkel_hash());
		block.setDifficulty(DIFF);
		block.setVersion(i);

		// --- Random selection of transactions

		if (transactions.size() - BLOCK_SIZE != 0) {
			srand(time(0));
			r = rand() % (transactions.size() - BLOCK_SIZE);
		}
		else r = 0;
		std::cout << "\nTransactions " << r << " to " << r + BLOCK_SIZE << " have been selected from the pool" << std::endl;

		for (int t = 0; t < BLOCK_SIZE; t++) block.push_transaction(transactions[r + t]);

		// --- Proof of Work

		std::cout << "Proof of work started with difficulty of " << DIFF << std::endl;
		do {
			nonce++;
			merkel_hash = hash.toHash(block.getPrev_hash() + std::to_string(block.getTimestamp()) + std::to_string(block.getVersion()) + std::to_string(nonce) + std::to_string(block.getDifficulty()));
		} while (merkel_hash.substr(0, DIFF) != diff);
		block.setNonce(nonce);
		block.setMerkel_hash(merkel_hash);
		std::cout << "Hash has been found: " << merkel_hash << ", nonce value: " << nonce << std::endl;

		// Delete old transactions from the pool
		transactions.erase(transactions.begin() + r, transactions.begin() + r + BLOCK_SIZE);

		// Execute the block transactions
		block.execTrans(users);

		blocks.push_back(block);
		std::cout << i << ". Transaction sucessfully executed, block added to the chain" << std::endl;
	}

	// Printing BlockChain

	std::cout << std::endl;
	for (int i = 0; i < blocks.size(); i++) {
		blocks[i].printBlock();
		std::cout << "--------------------------------------" << std::endl;
	}

	return 0;
}