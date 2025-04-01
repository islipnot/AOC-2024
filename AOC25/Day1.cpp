#include "pch.h"
#include <vector>
#include <algorithm>

int d1p1()
{
	std::ifstream file("d:\\input.txt");
	std::string line;

	std::vector<int> LeftLine, RightLine;

	while (std::getline(file, line))
	{
		static const size_t offset = line.find_last_of(' ');

		LeftLine.emplace_back(std::stoi(line));
		RightLine.emplace_back(std::stoi(line.substr(offset)));
	}

	file.close();

	std::sort(LeftLine.begin(), LeftLine.end());
	std::sort(RightLine.begin(), RightLine.end());

	int result = 0;

	for (int i = 0; i < LeftLine.size(); ++i)
	{
		result += std::abs(LeftLine[i] - RightLine[i]);
	}

	std::cout << "Similarity score: " << result << '\n';

	return 0;
}

int d1p2()
{
	std::ifstream file("d:\\input.txt");
	std::string line;

	std::vector<int> LeftLine, RightLine;

	while (std::getline(file, line))
	{
		static const size_t offset = line.find_last_of(' ');

		LeftLine.emplace_back(std::stoi(line));
		RightLine.emplace_back(std::stoi(line.substr(offset)));
	}

	file.close();

	int result = 0;

	for (int num : LeftLine)
	{
		result += num * std::count(RightLine.begin(), RightLine.end(), num);
	}

	std::cout << "Similarity score: " << result << '\n';

	return 0;
}