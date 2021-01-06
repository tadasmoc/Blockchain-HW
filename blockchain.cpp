#include "blockchain.h"

// Block

long long int Block::timestampFunct()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Block::Block()
{
	merkel_hash = "";
	prev_hash = "";
	timestamp = timestampFunct();
	version = 0;
	nonce = 0;
	difficulty = 0;
}

Block::Block(std::string Merkel_hash, std::string Prev_hash, int Version, long int Nonce, int Difficulty)
{
	merkel_hash = Merkel_hash;
	prev_hash = Prev_hash;
	timestamp = timestampFunct();
	version = Version;
	nonce = Nonce;
	difficulty = Difficulty;
}

Block::~Block(){}

// Transaction

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