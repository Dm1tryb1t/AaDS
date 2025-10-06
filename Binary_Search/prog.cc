#include "binary_search.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>


int main() {
	std::string first_line;
    std::getline(std::cin, first_line);
    // if (!std::getline(std::cin, first_line)) return 0;
	std::vector<int> nums;
	{
		std::istringstream iss(first_line);
		int num;
		while (iss >> num) nums.push_back(num);
	}
    std::sort(nums.begin(), nums.end());

	std::string line;
	while (std::getline(std::cin, line)) {
		if (line.empty()) break;
		std::istringstream iss(line);
		std::string cmd;
        iss >> cmd;
		// if (!(iss >> cmd) || cmd != "search") continue;
        int k;
        iss >> k;
        // if (!(iss >> k)) continue;

        int res = BinarySearch::lower_bound(nums, k);
        std::cout << res << '\n';
    }

	return 0;
}
