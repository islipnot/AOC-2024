#include "pch.h"
#include <vector>
#include <algorithm>

int HorizontalCheck(std::string line, size_t xPos)
{	
	// Checking if XMAS is spelled horizontally

	size_t StrStart = xPos;
	size_t StrLen = 4;

	if (xPos > 2)
	{
		StrStart -= 3;

		if (xPos < line.size() - 3) StrLen += 3;
	}

	int result = 0;

	line = line.substr(StrStart, StrLen);
	if (line.find("XMAS") != std::string::npos) ++result;
	if (line.find("SAMX") != std::string::npos) ++result;

	return result;
}

int VerticalCheck(std::vector<std::string>& data, int TargetIndex, size_t xPos)
{
	// Checking if XMAS is spelled vertically/diagonally

	int CurrentIndex = TargetIndex - 3;
	if (CurrentIndex < 0) CurrentIndex = 0;

	int FinalIndex = TargetIndex + 3;
	if (FinalIndex >= data.size()) FinalIndex -= 3;

	std::string vUp, vDown, dlUp, dlDown, drUp, drDown; // v=vert, d=diagonal, l=left, r=right

	const bool CheckLeft  = xPos > 2; // Check left-diagonal
	const bool CheckRight = xPos < data[0].size() - 3; // Check right-diagonal

	for (int i = 0; CurrentIndex <= FinalIndex; ++i, ++CurrentIndex)
	{
		const std::string& line = data[CurrentIndex];

		if (CurrentIndex < TargetIndex)
		{
			if (CheckLeft) dlUp += line[xPos - (3 - i)];
			if (CheckRight) drUp += line[xPos + (3 - i)];

			vUp += line[xPos];
		}

		else if (CurrentIndex > TargetIndex)
		{
			if (CheckLeft) dlDown += line[xPos - (1 + i)];
			if (CheckRight) drDown += line[xPos + i + 1];

			vDown += line[xPos];
		}

		else i = -1;
	}

	int result = 0;

	result += vUp    == "SAM";
	result += dlUp   == "SAM";
	result += drUp   == "SAM";
	result += vDown  == "MAS";
	result += dlDown == "MAS";
	result += drDown == "MAS";

	return result;
}

int main()
{
	std::ifstream file("d:\\input.txt");
	std::vector<std::string> data;

	// You could optimize this if you assume the amount of lines, but I don't want to do that

	do { data.push_back({}); } while (std::getline(file, data.back()));
	file.close();
	data.pop_back();

	// Checking each line for the character 'X', then checking the connecting character positions

	int result = 0;

	for (int i = 0, sz = data.size(); i < sz; ++i)
	{
		const std::string& line = data[i];
		size_t xPos = line.find('X');

		while (xPos != std::string::npos)
		{
			result += HorizontalCheck(line, xPos);
			result += VerticalCheck(data, i, xPos);

			const size_t NextX = line.substr(xPos + 1).find('X');
			if (NextX == std::string::npos) break;

			xPos += NextX + 1;
		}
	}

	std::cout << "Result: " << result << '\n';

	return 0;
}

int d4p2()
{
	std::ifstream file("d:\\input.txt");
	std::vector<std::string> data;

	do { data.reserve(1); } while (std::getline(file, data.back()));
	file.close();

	

	return 0;
}