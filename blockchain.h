#pragma once

#include <string>
#include <chrono>
#include <vector>
#include "user.h"
#include "hash.h"

class Transaction {
private:
	std::string transaction_id;
	std::string sender_key;
	std::string receiver_key;
	int sum;
public:
	// Constructor
	Transaction();

	// Overload contructor
	Transaction(std::string, std::string, std::string, int);

	// Destructor
	~Transaction();

	// Get functions
	std::string getTransaction_id();
	std::string getSender_key();
	std::string getReceiver_key();
	int getSum();

	// Set functions
	void setTransaction_id(std::string);
	void setSender_key(std::string);
	void setReceiver_key(std::string);
	void setSum(int);

	void printTransaction();
};

class Block {
private:
	std::string block_hash;
	std::string merkle_hash;	// current block transactions merkle hash
	std::string prev_hash;
	long long int timestamp;
	int version;				// block no#
	long int nonce;
	int difficulty;

	std::vector<Transaction> Btransactions;

public:
	// Constructor
	Block();

	// Overload contructor
	Block(std::string, std::string, int, long int, int);

	// Destructor
	~Block();

	// Get functions
	std::string getBlock_hash();
	std::string getMerkle_hash();
	std::string getPrev_hash();
	long long int getTimestamp();
	int getVersion();
	long int getNonce();
	int getDifficulty();
	std::vector<Transaction> getTransactions();

	// Set functions
	void setBlock_hash(std::string);
	void setMerkle_hash(std::string);
	void setPrev_hash(std::string);
	void setTimestamp(long long int);
	void setVersion(int);
	void setNonce(long int);
	void setDifficulty(int);
	void push_transaction(Transaction);

	long long int timestampFunct();
	bool validateTrans(Transaction trans, std::vector<User>&);
	void execTrans(std::vector<User>&);
	void printBlock();

};