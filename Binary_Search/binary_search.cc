#include "binary_search.h"

int BinarySearch::lower_bound_helper(const std::vector<int>& nums, int key, int l, int r) {
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

int BinarySearch::lower_bound(const std::vector<int>& nums, int key) {
    if (nums.empty()) return -1;
    return lower_bound_helper(nums, key, 0, static_cast<int>(nums.size() - 1));
}
