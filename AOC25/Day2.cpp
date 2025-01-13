#define increasing 1
#define decreasing 0

#include <iostream>
#include <fstream>
#include <string>

int d2p1()
{
	std::ifstream file("D:\\input.txt");
	std::string line;

	int SafeReports = 0;

	while (std::getline(file, line))
	{
		int8_t status = -1;

		while (true)
		{
			const int left = std::stoi(line);
			line.erase(0, line.find_first_of(' ') + 1);

			const int right = std::stoi(line);

			const int dif = left - right;
			if (std::abs(dif) > 3 || !dif) break;

			if (status == -1)
			{
				status = dif > 0;
			}
			else if ((status == decreasing && dif > 0) || (status == increasing && dif < 0))
			{
				break;
			}

			if (line.find_first_of(' ') == std::string::npos)
			{
				++SafeReports;
				break;
			}
		}
	}

	std::cout << "Safe reports: " << SafeReports << '\n';

	return 0;
}

int d2p2() // unfinished
{
	std::ifstream file("D:\\input.txt");
	std::string line;

	int SafeReports = 0;

	while (std::getline(file, line))
	{
		int8_t status = -1;

		bool IgnoredLvl = false;

		std::cout << line;

		std::string LineCpy = line;

		while (true)
		{
			const int left = std::stoi(line);

			const int OldLineSz = line.size();
			line.erase(0, line.find_first_of(' ') + 1);

			const int right = std::stoi(line);

			const int dif = left - right;

			if (status == -1)
			{
				status = dif > 0;
			}

			if (line.find_first_of(' ') == std::string::npos)
			{
				std::cout << " -> SAFE";
				++SafeReports;
				break;
			}
		}

		std::cout << '\n';
	}

	std::cout << "Safe reports: " << SafeReports << '\n';

	return 0;
}