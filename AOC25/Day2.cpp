#include <iostream>
#include <fstream>
#include <string>

int Part1()
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
			else if ((!status && dif > 0) || (status == 1 && dif < 0))
			{
				break;
			}
			
			const int spc = line.find_first_of(' ');

			if (spc == std::string::npos)
			{
				++SafeReports;
				break;
			}
		}
	}

	std::cout << "Safe reports: " << SafeReports << '\n';

	return 0;
}

int main()
{
	std::ifstream file("D:\\input.txt");
	std::string line;

	return 0;
}