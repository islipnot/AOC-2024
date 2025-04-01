#include <iostream>
#include <fstream>
#include <string>

long GetNextMul(std::string& line)
{
	while (true)
	{
		// Finding the next multiplication, returning if there is none

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
	std::string line, data;

	while (std::getline(file, line))
	{
		data += line;
	}

	line.clear();

	long result = 0;

	while (true)
	{
		const long MulResult = GetNextMul(data);
		if (MulResult != -1) result += MulResult;
		else break;
	}
	
	std::cout << "Result: " << result << '\n';

	return 0;
}

void ClearDisabledMuls(std::string& line)
{
	while (true)
	{
		const size_t DontPos = line.find("don't()");

		if (DontPos == std::string::npos) break;

		const size_t DoPos = line.substr(DontPos).find("do()");

		if (DoPos == std::string::npos)
		{
			line.erase(DontPos);
			break;
		}

		line.erase(DontPos, DoPos + 4);
	}
}

int main()
{
	std::ifstream file("d:\\input.txt");
	std::string line, data;

	while (std::getline(file, line)) 
	{ 
		data += line; 
	}
	
	ClearDisabledMuls(data);

	long result = 0;

	while (true)
	{
		const long MulResult = GetNextMul(data);
		if (MulResult != -1) result += MulResult;
		else break;
	}
	
	std::cout << "Result: " << result << '\n';

	return 0;
}