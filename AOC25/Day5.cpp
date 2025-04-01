#include "pch.h"
#include <vector>
#include <algorithm>

bool IsValidUpdate(std::vector<std::string>& rules, std::string update)
{
	while (update.size() > 2)
	{
		std::string TempUpdate = update;

		while (TempUpdate.size() > 3)
		{
			bool FoundRule = false;
			const std::string NeededRule = TempUpdate.substr(0, 5);

			for (std::string& rule : rules)
			{
				if (rule == NeededRule)
				{
					FoundRule = true;
					break;
				}
			}

			if (!FoundRule) return false;
			
			TempUpdate.erase(3, 3);
		}

		update.erase(0, 3);
	}

	return true;
}

int main()
{
	std::ifstream file("d:\\input.txt");
	
	std::vector<std::string> rules;
	do { rules.push_back({}); } while (std::getline(file, rules.back()) && !rules.back().empty());
	
	std::vector<std::string> updates;
	do { updates.push_back({}); } while (std::getline(file, updates.back()));

	file.close();
	rules.pop_back();
	updates.pop_back();

	int result = 0;

	for (std::string update : updates)
	{
		std::replace(update.begin(), update.end(), ',', '|');

		if (IsValidUpdate(rules, update))
		{
			const int MidOffset = std::count(update.begin(), update.end(), '|') * 1.5f;
			result += std::stoi(update.substr(MidOffset));
		}
	}

	std::cout << "Result: " << result << '\n';

	return 0;
}