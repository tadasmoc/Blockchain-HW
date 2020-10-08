#include "hash.h"

void Hash::hashReadConsole()
{
	std::cout << "Please type in your value:" << std::endl;
	std::getline(std::cin, input);
	std::cout << "input: " << input << std::endl;

	toBinary(input);
}

void Hash::hashReadFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::getline(file, input);
	std::cout << "input: " << input << std::endl;

	toBinary(input);
}

void Hash::toBinary(std::string input)
{
	std::string bin;

	/*for (int i = 0; i <= input.size(); i++)
	{
		int val = int(input[i]);
		val = 

		// Convert ASCII value to binary 
		std::string bin = "";
		while (val > 0)
		{
			(val % 2) ? bin.push_back('1') :
				bin.push_back('0');
			val /= 2;
		}
		reverse(bin.begin(), bin.end());

		std::cout << bin << " ";
	}
}*/

	for (std::size_t i = 0; i < input.size(); ++i)
	{
		bin += std::bitset<8>(input[i]).to_string();
	}

	//std::cout << "converted to bin: " << bin << std::endl;

	padding(bin);
}

void Hash::padding(std::string bin)
{
	if (bin.size() % 512 != 0) {
		bin += "1";
		while (bin.size() % 512 != 0) {
			bin += "0";
		}
	}
	//std::cout << "padded: " << bin << std::endl;

	compression(bin);
}

void Hash::compression(std::string bin)
{
	//std::vector<std::string> block512;
	std::deque<std::string> block32; // 32bitai x 16. viso - 512.
	std::vector<std::string> hashBin; // 32bitai x 8. viso - 256.


	// Viskas isdeliojama po 32 bitus i block32.
	int t = 0;
	while (bin.size() != 0) {
		block32.push_back(bin.substr(bin.size() - 32, bin.size()));
		for (int i = 0; i < 32; i++) bin.pop_back(); // potentialy slow.

		//std::cout << "block[" << t << "] " << block32[t] << std::endl;
		//std::cout << "size: " << bin.size() << std::endl;

		t++;
	}

	while (block32.size() != 0) {

		//std::cout << "po pirmo maisymo: \n";
		for (int i = 15; i > 0; i--) {
			block32[i - 1] = xorString(block32[i - 1], block32[i]);
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		//std::cout << "po antro maisymo: \n";
		for (int i = 1; i < 16; i++) {
			std::rotate(block32[i].begin(), block32[i].begin() + i, block32[i].end());
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		//std::cout << "po trecio maisymo: \n";
		for (int i = 15; i > 0; i--) {
			block32[i - 1] = xorString(block32[i - 1], block32[i]);
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}

		//std::cout << "po ketvirto maisymo: \n";
		for (int i = 0; i < 16; i += 2) {

			hashBin.push_back(xorString(block32[i], block32[i + 1]));
			//std::cout << "block[" << i << "] " << block32[i] << std::endl;
		}


		// TODO: butinai pakeist del avalanche efekto ir collisionu.
		//std::cout << "po test maisymo: \n";
		for (int i = 0; i < 8; i++) {
			test[i] = xorString(test[i], hashBin[i]);
			//std::cout << "block[" << i << "] " << test[i] << std::endl;
		}
		hashBin.clear();

		for (int i = 0; i < 16; i++) block32.pop_front();
		//std::cout << "---------------Block32 size after iteration: " << block32.size() << std::endl;
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