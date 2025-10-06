#include "my_dequeue.h"

MyDequeue::MyDequeue() {
    l = r = -1;
    capacity = sz = 0;
    values = nullptr;
}
MyDequeue::MyDequeue(int maxsz) : capacity(maxsz) {
    l = r = -1;
    sz = 0;
    values = new int(maxsz);
}
MyDequeue::~MyDequeue() {
    if (values) delete[] values;
    values = nullptr;
    capacity = sz = 0;
    l = r = -1;
}

void MyDequeue::setsz(int newsz) {
    if (newsz == 0) {
        if (values) delete[] values;
        values = nullptr;
        capacity = sz = 0;
        l = r = -1;
        return;
    }

    int* newValues = new int(newsz);
    if (values) {
        for (int i = 0; i < std::min(sz, newsz); ++i) {
            newValues[i] = values[(l + i) % capacity];
        }
        delete[] values;
        // values = nullptr;
    }
    values = newValues;
    newValues = nullptr;
}
int MyDequeue::push_back(int newValue) {
    if (sz == capacity) return -1;

    if (sz == 0) {
        l = r = 0;
    } else r = (r + 1) % capacity;
    values[r] = newValue;

    return ++sz;
}
int MyDequeue::push_front(int newValue) {
    if (sz == capacity) return -1;

    if (sz == 0) {
        l = r = 0;
    } else l = (l - 1) % capacity;
    values[l] = newValue;

    return 1;
}
bool MyDequeue::pop_back() {
    if (sz == 0) return 0;

    r = (r - 1) % capacity;
    --sz;

    return 1;
}
bool MyDequeue::pop_front() {
    if (sz == 0) return 0;

    l = (l + 1) % capacity;
    --sz;

    return 1;
}

int MyDequeue::front() {
    if (sz == 0) return INF;
    return values[l];
}
int MyDequeue::back() {
    if (sz == 0) return INF;
    return values[r];
}

void MyDequeue::print() {
    for (int i = l; i < l + sz; ++i) {
        std::cout << values[i % capacity] << ' ';
    }
    std::cout << '\n';
}
