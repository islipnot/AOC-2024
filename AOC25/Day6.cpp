#include "pch.h"
#include <array>
#include <vector>
#include <algorithm>

#define up    '^'
#define down  'v'
#define left  '<'
#define right '>'

int CheckChar(std::vector<std::string>& grid, int y, int x, int& steps, bool DrawPath)
{
	char& ch = grid[y][x];

	if (ch == '#' || ch == 'Z') return true;
	if (ch != 'X' && DrawPath)
	{
		++steps;
		ch = 'X';
	}

	return false;
}

int MoveGuard(std::vector<std::string>& grid, int GuardPos[2], int8_t& GuardDir, bool DrawPath = true)
{
	int steps = 0;
	bool turned = false;

	switch (GuardDir)
	{
	case up:
	{
		for (int i = GuardPos[1] - 1; i >= 0; --i)
		{
			if (CheckChar(grid, i, GuardPos[0], steps, DrawPath))
			{
				GuardDir = right;
				turned = true;

				break;
			}

			--GuardPos[1];
		}

		break;
	}
	case down:
	{
		for (int i = GuardPos[1] + 1, sz = grid.size(); i < sz; ++i)
		{
			if (CheckChar(grid, i, GuardPos[0], steps, DrawPath))
			{
				GuardDir = left;
				turned = true;

				break;
			}

			++GuardPos[1];
		}

		break;
	}
	case left:
	{
		for (int i = GuardPos[0] - 1; i >= 0; --i)
		{
			if (CheckChar(grid, GuardPos[1], i, steps, DrawPath))
			{
				GuardDir = up;
				turned = true;

				break;
			}

			--GuardPos[0];
		}

		break;
	}
	case right:
	{
		for (int i = GuardPos[0] + 1, sz = grid[0].size(); i < sz; ++i)
		{
			if (CheckChar(grid, GuardPos[1], i, steps, DrawPath))
			{
				GuardDir = down;
				turned = true;

				break;
			}

			++GuardPos[0];
		}
	}
	}

	// Increment is done for DetectLoop() and will only ever occur then

	if (!steps && turned) ++steps;
	
	return steps;
}

void GetGuardPos(std::vector<std::string>& grid, int GuardPos[2], int8_t& GuardDir)
{
	for (int i = 0, sz = grid.size(); i < sz; ++i)
	{
		const std::string& line = grid[i];
		constexpr int8_t directions[4] = { up, down, left, right };

		for (const char direction : directions)
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
}

int d6p1()
{
	// Parsing input

	std::ifstream input("d:\\input.txt");
	std::vector<std::string> grid;

	do { grid.push_back({}); } while (std::getline(input, grid.back()));
	input.close();
	grid.pop_back();

	// Parsing data regarding the gaurds starting position

	int GuardPos[2]; // GuardPos[0] == X, GuardPos[1] == Y
	int8_t GuardDir = 0;

	GetGuardPos(grid, GuardPos, GuardDir);

	// Simulating the guards path

	int result = 0;

	while (true)
	{
		const int steps = MoveGuard(grid, GuardPos, GuardDir);

		if (steps) result += steps;
		else break;
	}

	std::cout << "Result: " << result << '\n';

	return 0;
}

bool DetectLoop(std::vector<std::string>& grid, std::array<int, 2> GuardPos, int8_t GuardDir)
{
	std::vector<std::array<int, 3>> CoordLog;

	while (MoveGuard(grid, GuardPos.data(), GuardDir, false))
	{
		for (auto& coords : CoordLog)
		{
			if (coords[0] == GuardPos[0] && coords[1] == GuardPos[1] && coords[2] == GuardDir)
			{
				return true;
			}
		}

		CoordLog.emplace_back(std::array<int, 3>{ GuardPos[0], GuardPos[1], static_cast<int>(GuardDir) });
	}

	return false;
}

int main()
{
	// Parsing input

	std::ifstream input("d:\\input.txt");
	std::vector<std::string> grid, TempGrid;

	do { grid.push_back({}); } while (std::getline(input, grid.back()));
	input.close();
	grid.pop_back();

	// Parsing data regarding the gaurds starting position

	int GuardPos[2]; // GuardPos[0] == X, GuardPos[1] == Y
	int8_t GuardDir = 0;

	GetGuardPos(grid, GuardPos, GuardDir);

	const int GuardStart[2] = { GuardPos[0], GuardPos[1] };

	// Getting the default gaurd path

	while (MoveGuard(grid, GuardPos, GuardDir)) {}

	TempGrid = grid;

	// For each iteration, the next line from the input is parsed
	// Each position on the line visited by the guard will have a barrier placement simulated

	int loops = 0;

	for (int y = 0, GridLen = grid.size(); y < GridLen; ++y)
	{
		std::string& line = grid[y];
		std::string& TempLine = TempGrid[y];

		for (int i = 0, LineSz = line.size(); i < LineSz; ++i)
		{
			if (line[i] != 'X') continue;

			char& ch = TempLine[i];
			const char OldCh = ch;

			ch = 'Z';

			// Checking if the current barrier placement resulted in a loop

			if (DetectLoop(TempGrid, { GuardStart[0], GuardStart[1] }, GuardDir)) ++loops;

			ch = OldCh;
		}
	}

	std::cout << "Result: " << loops << '\n';

	return 0;
}