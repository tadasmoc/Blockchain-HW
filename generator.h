#pragma once

#include <cstdlib>
#include <ctime>
#include "blockchain.h"
#include "user.h"

class Generator {
public:
	std::string randName();
	void generateUsers(std::vector<User>&, int);
	void generateTransactions(std::vector<Transaction>&, std::vector<User>&, int);
};