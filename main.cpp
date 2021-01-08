#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "hash.h"
#include "timer.h"
#include "user.h"
#include "blockchain.h"
#include "generator.h"

//--Settings--------------------------------------------------
#define USR_NO 50		// Users number
#define TRNS_NO 99		// Transactions number
#define DIFF 2			// Mining difficulty
#define BLOCK_SIZE 10	// How many transactions in the block.
//------------------------------------------------------------


std::string toMerkleHash(Block& block)
{
	Hash hash;
	std::vector<std::string> Htrans; // Hashed transactions
	std::vector<Transaction> trans = block.getTransactions();

	// Convert to each transaction to hash

	if (trans.size() == 0) {
		Htrans.push_back("");
	}
	else {
		for (int i = 0; i < trans.size(); i++) {
			Htrans.push_back(hash.toHash(trans[i].getReceiver_key() + trans[i].getSender_key() + trans[i].getTransaction_id() + std::to_string(trans[i].getSum())));
		}
	}

	// Find merkle tree root hash

	std::vector<std::string> temporary;
	do {
		if (Htrans.size() % 2 != 0) Htrans.push_back(Htrans[Htrans.size() - 1]);

		for (int i = 0; i < Htrans.size(); i += 2) {
			temporary.push_back(hash.toHash(Htrans[i] + Htrans[i + 1]));
		}
		Htrans = temporary;
		temporary.clear();

	} while (Htrans.size() != 1);

	return Htrans[0];
}

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
	
	//  Uncomment bellow to make the transactions invalid

	/*for (int i = 0; i < transactions.size(); i++) {
		transactions[i].setTransaction_id("123");
	}*/

	// Blockchain start

	std::cout << "\nBlockchain simulation has been started" << std::endl;

	std::vector<Block> blocks; // Var which stores the 'blockchain'
	std::vector<Transaction> Btransactions;
	std::string block_hash;
	long int nonce = 0;
	int r; // Random number for choosing the transactions.
	std::string diff; // Var, used for checking the difficulty
	for (int i = 0; i < DIFF; i++) diff += "0";

	// Blocks generation

	int i = 0;
	while (transactions.size() > 0) {
		int maxSize = 0; // integer for setting max block size if there is less transaction in the pool than standard block size

		Block block;
		block.setTimestamp(block.timestampFunct()); // Block start time.
		nonce = 0;

		if (i == 0) block.setPrev_hash("0000000000000000000000000000000000000000000000000000000000000000");
		else block.setPrev_hash(blocks[i - 1].getBlock_hash());

		block.setDifficulty(DIFF);
		block.setVersion(i);

		// --- Random selection of transactions

		if (transactions.size() > BLOCK_SIZE) {
			srand(time(0));
			r = rand() % (transactions.size() - BLOCK_SIZE);
		}
		else if (transactions.size() < BLOCK_SIZE) {
			maxSize = BLOCK_SIZE - transactions.size();
			r = 0;
		}
		else r = 0;

		std::cout << "\nTransactions " << r << " to " << r + (BLOCK_SIZE - maxSize) << " have been selected from the pool" << std::endl;
		for (int t = 0; t < (BLOCK_SIZE - maxSize); t++) {

			// Transaction validation

			bool valid = block.validateTrans(transactions[r + t], users);
			if (valid) block.push_transaction(transactions[r + t]);
		}

		// Merkle hash of blocks transactions

		block.setMerkle_hash(toMerkleHash(block));

		// --- Proof of Work

		std::cout << "Proof of work started with the difficulty of " << DIFF << std::endl;

		do {
			nonce++;			
			block_hash = hash.toHash(block.getMerkle_hash() + block.getPrev_hash() + std::to_string(block.getTimestamp()) + std::to_string(block.getVersion()) + std::to_string(nonce) + std::to_string(block.getDifficulty()));

		} while (block_hash.substr(0, DIFF) != diff);
		block.setNonce(nonce);
		block.setBlock_hash(block_hash);
		std::cout << "Hash has been found: " << block_hash << ", nonce value: " << nonce << std::endl;

		// Delete old transactions from the pool
		transactions.erase(transactions.begin() + r, transactions.begin() + r + (BLOCK_SIZE - maxSize));

		// Execute the block transactions
		block.execTrans(users);

		blocks.push_back(block);
		std::cout << i << ". Transaction sucessfully executed, block added to the chain" << std::endl;

		i++;
	}

	// Printing BlockChain

	std::cout << std::endl;
	for (int t = 0; t < blocks.size(); t++) {
		blocks[t].printBlock();
		std::cout << "--------------------------------------" << std::endl;
	}

	return 0;
}