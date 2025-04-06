#include "pch.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

std::unordered_set<std::string> FillRuleSet(std::ifstream& file)
{
	std::vector<std::string> rules;
	do { rules.push_back({}); } while (std::getline(file, rules.back()) && !rules.back().empty());

	rules.pop_back();

	return std::unordered_set<std::string>(rules.begin(), rules.end());
}

bool IsValidUpdate(std::unordered_set<std::string>& rules, std::string update)
{
	while (update.size() > 2)
	{
		std::string TempUpdate = update;

		while (TempUpdate.size() > 3)
		{
			if (rules.find(TempUpdate.substr(0, 5)) == rules.end())
			{
				return false;
			}
			
			TempUpdate.erase(3, 3);
		}

		update.erase(0, 3);
	}

	return true;
}

int d5p1()
{
	std::ifstream file("d:\\input.txt");
	std::unordered_set<std::string> rules = FillRuleSet(file);
	
	std::vector<std::string> updates;
	do { updates.push_back({}); } while (std::getline(file, updates.back()));

	file.close();
	updates.pop_back();

	int result = 0;

	for (std::string& update : updates)
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

void FixUpdate(std::unordered_set<std::string>& rules, std::string& update)
{
	std::stringstream ss(update);
	std::vector<int> nums;

	for (std::string StrNum; std::getline(ss, StrNum, '|'); nums.emplace_back(std::stoi(StrNum)));

	const int sz = static_cast<int>(nums.size());
	std::vector<int> pos(sz, 0);

	for (int i = 0; i < sz; ++i)
	{
		const int TargNum = nums[i];

		for (int num : nums)
		{
			if (num == TargNum) continue;

			const std::string query = std::to_string(TargNum) + '|' + std::to_string(num);

			if (rules.find(query) == rules.end()) ++pos[i];
		}
	}

	std::vector<int> NewUpdate(sz);

	for (int i = 0; i < sz; ++i)
	{
		NewUpdate[pos[i]] = nums[i];
	}

	std::ostringstream oss;

	for (int i = 0; i < sz; ++i)
	{
		oss << NewUpdate[i];
		if (i < sz - 1) oss << '|';
	}

	update = oss.str();
}

int main()
{
	std::ifstream file("d:\\input.txt");
	std::unordered_set<std::string> rules = FillRuleSet(file);

	std::vector<std::string> updates;
	do { updates.push_back({}); } while (std::getline(file, updates.back()));

	file.close();
	updates.pop_back();

	int result = 0;

	for (std::string& update : updates)
	{
		std::replace(update.begin(), update.end(), ',', '|');

		if (!IsValidUpdate(rules, update))
		{
			FixUpdate(rules, update); 

			const int MidOffset = std::count(update.begin(), update.end(), '|') * 1.5f;
			result += std::stoi(update.substr(MidOffset));
		}
	}

	std::cout << "Result: " << result << '\n';

	return 0;
}