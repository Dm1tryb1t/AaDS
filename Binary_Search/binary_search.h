#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <vector>

class BinarySearch {
private:
    static int lower_bound_helper(const std::vector<int>&, int, int, int);

public:
    static int lower_bound(const std::vector<int>&, int);
};

#endif
