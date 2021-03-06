#include "blockchain.h"

// -----
// Block
// -----

long long int Block::timestampFunct()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

bool Block::validateTrans(Transaction trans, std::vector<User>& users)
{
	Hash hash;
	bool valid = false;

	if (trans.getTransaction_id() == hash.toHash(trans.getSender_key() + trans.getReceiver_key() + std::to_string(trans.getSum()))) {
		valid = true;
	}

	if (valid) {
		for (int i = 0; i < users.size(); i++) {
			if (trans.getSender_key() == users[i].getPublic_key()) {
				if (users[i].getBalance() - trans.getSum() >= 0) {
					valid = true;
					break;
				}
				else {
					valid = false;
					break;
				}
			}
		}
	}
	return valid;
}

void Block::execTrans(std::vector<User>& users)
{
	for (int i = 0; i < Btransactions.size(); i++) {
		//sender - sum
		for (int t = 0; t < users.size(); t++) {
			if (Btransactions[i].getSender_key() == users[t].getPublic_key()) {
				users[t].reduceBalance(Btransactions[i].getSum());
				break;
			}
		}
		//receiver + sum
		for (int t = 0; t < users.size(); t++) {
			if (Btransactions[i].getSender_key() == users[t].getPublic_key()) {
				users[t].increaseBalance(Btransactions[i].getSum());
				break;
			}
		}
	}
}

void Block::printBlock()
{
	std::cout << "block_hash:  " << block_hash << std::endl;
	std::cout << "merkle_hash: " << merkle_hash << std::endl;
	std::cout << "prev_hash:   " << prev_hash << std::endl;
	std::cout << "timestamp:   " << timestamp << std::endl;
	std::cout << "version:     " << version << std::endl;
	std::cout << "nonce:       " << nonce << std::endl;
	std::cout << "difficulty:  " << difficulty << std::endl;
	std::cout << "\n-Block-transactions-" << std::endl;

	for (int i = 0; i < Btransactions.size(); i++) {
		std::cout << i << "\n";
		Btransactions[i].printTransaction();
	}
}

// Constructor, etc.

Block::Block()
{
	merkle_hash = "";
	prev_hash = "";
	timestamp = timestampFunct();
	version = 0;
	nonce = 0;
	difficulty = 0;
}

Block::Block(std::string Merkle_hash, std::string Prev_hash, int Version, long int Nonce, int Difficulty)
{
	merkle_hash = Merkle_hash;
	prev_hash = Prev_hash;
	timestamp = timestampFunct();
	version = Version;
	nonce = Nonce;
	difficulty = Difficulty;
}

Block::~Block(){}

// Get functions

std::string Block::getBlock_hash()
{
	return block_hash;
}

std::string Block::getMerkle_hash()
{
	return merkle_hash;
}

std::string Block::getPrev_hash()
{
	return prev_hash;
}

long long int Block::getTimestamp()
{
	return timestamp;
}

int Block::getVersion()
{
	return version;
}

long int Block::getNonce()
{
	return nonce;
}

int Block::getDifficulty()
{
	return difficulty;
}

std::vector<Transaction> Block::getTransactions()
{
	return Btransactions;
}


// Set functions

void Block::setBlock_hash(std::string Block_hash)
{
	block_hash = Block_hash;
}

void Block::setMerkle_hash(std::string Merkle_hash)
{
	merkle_hash = Merkle_hash;
}

void Block::setPrev_hash(std::string Prev_hash)
{
	prev_hash = Prev_hash;
}

void Block::setTimestamp(long long int Timestamp)
{
	timestamp = Timestamp;
}

void Block::setVersion(int Version)
{
	version = Version;
}

void Block::setNonce(long int Nonce)
{
	nonce = Nonce;
}

void Block::setDifficulty(int Difficulty)
{
	difficulty = Difficulty;
}

void Block::push_transaction(Transaction trans)
{
	Btransactions.push_back(trans);
}








// -----------
// Transaction
// -----------

Transaction::Transaction()
{
	transaction_id = "";
	sender_key = "";
	receiver_key = "";
	sum = 0;
}

Transaction::Transaction(std::string Transaction_id, std::string Sender_key, std::string Receiver_key, int Sum)
{
	transaction_id = Transaction_id;
	sender_key = Sender_key;
	receiver_key = Receiver_key;
	sum = Sum;
}

Transaction::~Transaction(){}

// Get functions

std::string Transaction::getTransaction_id()
{
	return transaction_id;
}

std::string Transaction::getSender_key()
{
	return sender_key;
}

std::string Transaction::getReceiver_key()
{
	return receiver_key;
}

int Transaction::getSum()
{
	return sum;
}

// Set funtions

void Transaction::setTransaction_id(std::string Transaction_id)
{
	transaction_id = Transaction_id;
}

void Transaction::setSender_key(std::string Sender_key)
{
	sender_key = Sender_key;
}

void Transaction::setReceiver_key(std::string Receiver_key)
{
	receiver_key = Receiver_key;
}

void Transaction::setSum(int Sum)
{
	sum = Sum;
}

// Print function
void Transaction::printTransaction()
{
	std::cout << "transaction_id: " << transaction_id << std::endl;
	std::cout << "sender_key:     " << sender_key << std::endl;
	std::cout << "receiver_key:   " << receiver_key << std::endl;
	std::cout << "sum:            " << sum << std::endl << std::endl;
}