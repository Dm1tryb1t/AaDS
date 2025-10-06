#ifndef BINARY_SEARCHH
#define BINARY_SEARCHH

#include <vector>

class BinarySearch {
private:
    static int lower_bound_helper(const std::vector<int>&, int, int, int);

public:
    static int lower_bound(const std::vector<int>&, int);
};

#endif
