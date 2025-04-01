#define increasing 1
#define decreasing 0

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

bool IsSafe(std::vector<int>& report)
{
	bool direction;

	for (int i = 0; i < report.size() - 1; ++i)
	{
		// Validating the difference between levels

		const int dif = report[i] - report[i + 1];
		if (!dif || std::abs(dif) > 3) return false;

		// Validating the difference between directions

		if (!i) direction = dif < 0;
		else if ((direction == decreasing && dif < 0) || (direction == increasing && dif > 0)) return false;
	}

	return true;
}

int d2p1()
{
	std::ifstream file("d:\\input.txt");
	std::string line;

	int SafeReports = 0;

	while (std::getline(file, line))
	{
		std::vector<int> report;

		while (true)
		{
			std::stringstream ss(line);
			int num;

			while (ss >> num)
			{
				report.emplace_back(num);
			}

			if (!IsSafe(report)) break;

			++SafeReports;
		}
	}

	std::cout << "Safe reports: " << SafeReports << '\n';

	return 0;
}

int main() 
{
    std::ifstream file("d:\\input.txt");
    std::string line;

    int SafeReports = 0;

    while (std::getline(file, line)) 
	{
		std::vector<int> report;

		std::stringstream ss(line);
		int num;

		while (ss >> num)
		{
			report.emplace_back(num);
		}

		std::vector<int> TempReport = report;

		for (int i = 0, sz = report.size();; ++i)
		{
			if (IsSafe(TempReport))
			{
				++SafeReports;
				break;
			}

			if (i == sz) break;

			TempReport = report;
			TempReport.erase(TempReport.begin() + i);
		}
    }

    std::cout << "Safe reports: " << SafeReports << '\n';
    return 0;
}