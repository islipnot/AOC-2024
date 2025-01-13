#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

int Part1()
{
	std::ifstream file("d:\\input.txt");
	std::string line;

	int TotalDist = 0;
	std::vector<int> LeftRow, RightRow;

	while (std::getline(file, line))
	{
		static const int RowOffset = line.find_last_of(' ') + 1;

		LeftRow.emplace_back(std::stoi(line));
		RightRow.emplace_back(std::stoi(line.substr(RowOffset)));
	}

	std::sort(LeftRow.begin(), LeftRow.end());
	std::sort(RightRow.begin(), RightRow.end());

	for (int i = 0, s = LeftRow.size(); i < s; ++i)
	{
		TotalDist += std::abs(LeftRow[i] - RightRow[i]);
	}

	std::cout << "Total distance: " << TotalDist << '\n';

	return 0;
}

int Part2()
{
	std::ifstream file("d:\\input.txt");
	std::string line;

	uint32_t score = 0;
	std::vector<int> LeftRow, RightRow;

	while (std::getline(file, line))
	{
		static const int RowOffset = line.find_last_of(' ') + 1;

		LeftRow.emplace_back(std::stoi(line));
		RightRow.emplace_back(std::stoi(line.substr(RowOffset)));
	}

	for (int num : LeftRow)
	{
		score += num * std::count(RightRow.begin(), RightRow.end(), num);
	}

	std::cout << "Similarity score: " << score << '\n';

	return 0;
}