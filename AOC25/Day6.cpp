#include "pch.h"
#include <vector>
#include <algorithm>

#define up    '^'
#define down  'v'
#define left  '<'
#define right '>'

bool CheckChar(std::vector<std::string>& data, int y, int x, int& steps)
{
	char& ch = data[y][x];

	if (ch == '#') return true;
	if (ch != 'X')
	{
		++steps;
		ch = 'X';
	}

	return false;
}

bool MoveGuard(std::vector<std::string>& data, int GuardPos[2], int8_t& direction, int& steps)
{
	switch (direction)
	{
	case up:
	{
		for (int i = GuardPos[1] - 1; i >= 0; --i)
		{
			if (CheckChar(data, i, GuardPos[0], steps))
			{
				direction = right;
				return true;
			}

			--GuardPos[1];
		}

		break;
	}
	case down:
	{
		for (int i = GuardPos[1] + 1, sz = data.size(); i < sz; ++i)
		{
			if (CheckChar(data, i, GuardPos[0], steps))
			{
				direction = left;
				return true;
			}

			++GuardPos[1];
		}

		break;
	}
	case left:
	{
		for (int i = GuardPos[0] - 1; i >= 0; --i)
		{
			if (CheckChar(data, GuardPos[1], i, steps))
			{
				direction = up;
				return true;
			}

			--GuardPos[0];
		}

		break;
	}
	case right:
	{
		for (int i = GuardPos[0] + 1, sz = data[0].size(); i < sz; ++i)
		{
			if (CheckChar(data, GuardPos[1], i, steps))
			{
				direction = down;
				return true;
			}

			++GuardPos[0];
		}
	}
	}

	return false;
}

int main()
{
	std::ifstream file("d:\\input.txt");
	std::vector<std::string> data;

	do { data.push_back({}); } while (std::getline(file, data.back()));
	file.close();
	data.pop_back();

	int GuardPos[2]; // GuardPos[0] == X, GuardPos[1] == Y
	int8_t GuardDir = 0;

	// Getting the position/direction of the guard

	for (int i = 0, sz = data.size(); i < sz; ++i)
	{
		const std::string& line = data[i];
		const int8_t directions[4] = { up, down, left, right };

		for (char direction : directions)
		{
			const size_t pos = line.find(direction);

			if (pos != std::string::npos)
			{
				GuardPos[0] = pos;
				GuardPos[1] = i;

				GuardDir = direction;

				break;
			}
		}
	}

	// Simulating the guards path

	int result = 1;
	while (MoveGuard(data, GuardPos, GuardDir, result)) {}

	std::cout << "Result: " << result << '\n';

	return 0;
}