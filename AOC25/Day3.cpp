#include <iostream>
#include <fstream>
#include <string>

long GetNextMul(std::string& line)
{
	while (true)
	{
		// Finding the next multiplication, breaking if there is none

		const size_t MulPos = line.find("mul(");
		if (MulPos == std::string::npos) return -1;

		line.erase(0, MulPos + 4);

		// Parsing and validating the equation

		if (!std::isdigit(line[0])) continue;

		const int LeftNum = std::stoi(line);
		line.erase(0, std::to_string(LeftNum).size());

		if (line[0] != ',' || !std::isdigit(line[1])) continue;

		const int RightNum = std::stoi(line.substr(1));
		line.erase(0, std::to_string(RightNum).size() + 1);

		if (line[0] != ')') continue;

		return LeftNum * RightNum;
	}
}

int d3p1()
{
	std::ifstream file("d:\\input.txt");
	std::string line;

	long result = 0;

	while (std::getline(file, line))
	{
		while (true)
		{
			const long MulResult = GetNextMul(line);
			if (MulResult != -1) result += MulResult;
			else break;
		}
	}

	std::cout << "Result: " << result << '\n';

	return 0;
}

int d3p2()
{
	std::ifstream file("d:\\input.txt");
	std::string line;

	while (std::getline(file, line))
	{

	}

	return 0;
}