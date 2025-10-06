#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class MyBinarySearch {
private:
    static int lower_bound_helper(const std::vector<int>&, int, int, int);

public:
    static int lower_bound(const std::vector<int>&, int);
};

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

        int res = MyBinarySearch::lower_bound(nums, k);
        std::cout << res << '\n';
    }

	return 0;
}

int MyBinarySearch::lower_bound_helper(const std::vector<int>& nums, int key, int l, int r) {
    if (l > r) return -1;
    int m = l + (r - l) / 2;
    if (nums[m] == key) {
        int left = lower_bound_helper(nums, key, l, m - 1);
        return (left == -1 ? m : left);
    } else if (nums[m] < key) {
        return lower_bound_helper(nums, key, m + 1, r);
    } else {
        return lower_bound_helper(nums, key, l, m - 1);
    }
}

int MyBinarySearch::lower_bound(const std::vector<int>& nums, int key) {
    if (nums.empty()) return -1;
    return lower_bound_helper(nums, key, 0, static_cast<int>(nums.size() - 1));
}
