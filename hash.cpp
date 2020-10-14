#include "hash.h"

Hash::Hash()
{
	hashReadConsole();
}

Hash::Hash(std::string fileName)
{
	hashReadFile(fileName);
}

Hash::Hash(int x, std::string in)
{
	input = in;
	padding(input);
}

Hash::~Hash()
{

}


void Hash::hashReadConsole()
{
	std::cout << "Please type in your value:" << std::endl;
	std::getline(std::cin, input);
	std::cout << "input: " << input << std::endl;

	padding(input);
}

void Hash::hashReadFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::getline(file, input);
	std::cout << "input: " << input << std::endl;

	padding(input);
}

std::string Hash::toBinary(std::string text)
{
	std::string binary; // String to hold binary string value.

	for (std::size_t i = 0; i < text.size(); ++i)
	{
		binary += std::bitset<8>(text[i]).to_string();
	}

	std::cout << "Converted to bin: " << binary << std::endl;

	return binary;
}

std::string Hash::binEnd()
{
	std::string result;

	for (int i = 0; i < input.size(); i++) {
		result += std::to_string(int(input[i]) * i);
		std::cout << "result: " << result << std::endl;
	}

	return toBinary(result);
}

void Hash::padding(std::string bin)
{
	bin = toBinary(bin);
	std::string BinEnd = binEnd(); // A string generated from the length of input and ASCII values. This will be added to the end of padded bin variable.
	
	if ((bin.size() + BinEnd.size()) % 512 != 0) {                    // kintamsis galetu saugoti .size(), galimai butu greiciau, reik istestuot.
		bin += "1";
	}
		
	while ((bin.size() + BinEnd.size()) % 512 != 0) {
		bin += "0";
	}
	bin += BinEnd;

	std::cout << "padded: " << bin << std::endl;

	compression(bin);
}

std::string Hash::binaryAddition(std::string a, std::string b)
{
	std::string result = "";
	int temp = 0;
	int size_a = a.size() - 1;
	int size_b = b.size() - 1;
	while (size_a >= 0 || size_b >= 0 || temp == 1) {
		temp += ((size_a >= 0) ? a[size_a] - '0' : 0);
		temp += ((size_b >= 0) ? b[size_b] - '0' : 0);
		result = char(temp % 2 + '0') + result;
		temp /= 2;
		size_a--; size_b--;
	}
	return result;
}

void Hash::expand(std::deque<std::string> &block32)
{
	for (int i = 16; i < 64; i++) {
		std::string a = xorString(block32[i - 2], block32[i - 7]); //    binaryAddition(xorString(block32[i - 2], block32[i - 7]), xorString(block32[i - 15], block32[i - 16]));
		std::string b = xorString(block32[i - 15], block32[i - 16]);
		std::rotate(b.begin(), b.begin() + 5, b.end());
		b = xorString(a, b);
		block32.push_back(b);
	}
}

void Hash::compression(std::string bin)
{
	//std::vector<std::string> block512;
	std::deque<std::string> block32; // 32bitai x 16. viso - 512. Po to bus extendinama iki 32 x 64.
	std::vector<std::string> hashBin; // 32bitai x 8. viso - 256.
	std::vector<std::string> temporary;



	// Viskas isdeliojama po 32 bitus i block32.
	int t = 0;
	while (bin.size() != 0) {
		block32.push_back(bin.substr(bin.size() - 32, bin.size()));
		for (int i = 0; i < 32; i++) bin.pop_back(); // potentialy slow.

		//std::cout << "block[" << t << "] " << block32[t] << std::endl;
		//std::cout << "size: " << bin.size() << std::endl;

		t++;
	}

	expand(block32);

	for (int i = 0; i < 64; i++) {
		std::cout << i << ".  " << block32[i] << std::endl;
	}

	while (block32.size() != 0) {

		std::cout << "po pirmo maisymo: \n";
		for (int i = 63; i > 0; i--) {
			block32[i - 1] = xorString(block32[i - 1], block32[i]);
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		std::cout << "po antro maisymo: \n";
		for (int i = 1; i < 64; i++) {
			std::rotate(block32[i].begin(), block32[i].begin() + 3, block32[i].end());
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		std::cout << "po trecio maisymo: \n";
		for (int i = 63; i > 0; i--) {
			block32[i - 1] = xorString(block32[i - 1], block32[i]);
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		std::cout << "po ketvirto maisymo, kompresavimo: \n";
		for (int i = 0; i < 64; i += 2) {

			temporary.push_back(xorString(block32[i], block32[i + 1]));
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		std::cout << "po penkto maisymo, kompresavimo: \n";
		for (int i = 0; i < 32; i += 2) {

			temporary.push_back(xorString(temporary[i], temporary[i + 1]));
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		std::cout << "po sesto maisymo, kompresavimo: \n";
		for (int i = 32; i < 48; i += 2) {

			hashBin.push_back(xorString(temporary[i], temporary[i + 1]));
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		temporary.clear();


		// TODO: butinai pakeist del avalanche efekto ir collisionu.
		//std::cout << "po test maisymo: \n";
		for (int i = 0; i < 8; i++) {
			test[i] = xorString(test[i], hashBin[i]);
			//std::cout << "block[" << i << "] " << test[i] << std::endl;
		}

		hashBin.clear();
		//block32.clear();

		for (int i = 0; i < 64; i++) block32.pop_front();
		std::cout << "---------------Block32 size after iteration: " << block32.size() << std::endl;
	}

	//std::cout << "compression ended" << std::endl;
	binToHex(test);
}

std::string Hash::xorString(std::string a, std::string b)
{
	std::string ans;

	for (int i = 0; i < a.size(); i++)
	{
		// If the Character matches 
		if (a[i] == b[i])
			ans += "0";
		else
			ans += "1";
	}
	return ans;
}

void Hash::binToHex(std::vector<std::string> hashBin)
{
	//std::cout << "Bin to Hex started\n\n";

	for (int i = 0; i < 8; i++) {
		//std::cout << i << ".   " << hashBin[i] << std::endl;
		std::bitset<32> set(hashBin[i]);
		std::cout << std::hex << set.to_ulong(); // << std::endl;
	}
	std::cout << std::endl;
}