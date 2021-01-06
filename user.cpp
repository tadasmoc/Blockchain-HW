#include "user.h"

// Constructor & destructor

User::User()
{
	name = "Tadas";
	public_key = "321";
	balance = 3000;
}

User::User(std::string Name, std::string publicKey, int Balance)
{
	name = Name;
	public_key = publicKey;
	balance = Balance;
}

User::~User(){}

// Get functions

std::string User::getName()
{
	return name;
}

std::string User::getPublic_key()
{
	return public_key;
}

int User::getBalance()
{
	return balance;
}

// Set functions

void User::setName(std::string Name)
{
	name = Name;
}

void User::setPublic_key(std::string publicKey)
{
	public_key = publicKey;
}

void User::setBalance(int Balance)
{
	balance = Balance;
}


void User::printUser()
{
	std::cout << "Name:       " << name << std::endl;
	std::cout << "Public key: " << public_key << std::endl;
	std::cout << "Balance:    " << balance << std::endl << std::endl;
}