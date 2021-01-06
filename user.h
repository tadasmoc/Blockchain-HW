#pragma once

#include <string>
#include <iostream>

class User {
private:
	std::string name;
	std::string public_key;
	int balance;
public:
	// Constructor
	User();

	// Overload contructor
	User(std::string, std::string, int);

	// Destructor
	~User();

	// Get functions
	std::string getName();
	std::string getPublic_key();
	int getBalance();

	// Set functions
	void setName(std::string);
	void setPublic_key(std::string);
	void setBalance(int);

	void printUser();

};
