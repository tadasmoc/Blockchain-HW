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

	std::cout << "converted to bin: " << bin << std::endl;

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
	std::cout << "padded: " << bin << std::endl;

	compression(bin);
}

void Hash::compression(std::string bin)
{
	while (bin.size() != 0) {
		std::string block = bin.substr(bin.size() - 512, bin.size());
		for (int i = 0; i < 512; i++) bin.pop_back(); // potentialy slow.

		std::cout << "size: " << bin.size() << std::endl;
		std::cout << "block: " << block << std::endl;
	}


	
	std::cout << "compression ended" << std::endl;
}