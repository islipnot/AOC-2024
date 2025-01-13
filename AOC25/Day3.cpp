#include <iostream>
#include <fstream>
#include <string>

int d3p1()
{
	std::ifstream file("D:\\input.txt");
	std::string line;

	std::getline(file, line);

	int result = 0;

	do
	{
		line.erase(0, line.find("mul(") + 4);
		if (!std::isdigit(line[0])) continue;

		const int LeftNum = std::stoi(line);
		line.erase(0, std::to_string(LeftNum).size());
		if (line[0] != ',' || !std::isdigit(line[1])) continue;
		line.erase(0, 1);

		const int RightNum = std::stoi(line);
		line.erase(0, std::to_string(RightNum).size());
		if (line[0] != ')') continue;

		result += LeftNum * RightNum;

	} while (line.find("mul") != std::string::npos || std::getline(file, line));

	std::cout << "Result: " << result << '\n';

	return 0;
}

int main()
{
	std::ifstream file("D:\\input.txt");
	std::string line;

	int result = 0;

	std::cout << "Result: " << result << '\n';

	return 0;
}