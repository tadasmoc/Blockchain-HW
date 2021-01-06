#pragma once

#include <string>
#include <chrono>
#include <vector>
#include "user.h"

// For random name generation
#include <cstdlib>
#include <ctime>


class Block {
private:
	std::string merkel_hash;	// current block hash
	std::string prev_hash;
	long long int timestamp;
	int version;				// block no#
	long int nonce;
	int difficulty;
public:
	// Constructor
	Block();

	// Overload contructor
	Block(std::string, std::string, int, long int, int);

	// Destructor
	~Block();

	/*
	// Get functions
	std::string getMerkel_hash();
	std::string getPrev_hash();
	long long int getTimestamp();
	int getVersion();
	long int getNonce();
	int getDifficulty();

	// Set functions
	void getMerkel_hash(std::string);
	void getPrev_hash(std::string);
	void getTimestamp(long long int);
	void getVersion(int);
	void getNonce(long int);
	void getDifficulty(int);
	*/

	long long int timestampFunct();
	
};

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

};

class Generator {
public:
	std::string randName();
	void generateUsers(std::vector<User>&, int);
};