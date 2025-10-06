#ifndef MY_DEQUEUEH
#define MY_DEQUEUEH

#include <iostream>

#define INF 1e9

class MyDequeue {
private:
    int* values;
    int l, r;
    int sz;
    int capacity;

public:
    MyDequeue();
    MyDequeue(int);
    ~MyDequeue();

    void setsz(int);
    int push_back(int);
    int push_front(int);
    int pop_back();
    int pop_front();
    
    int front();
    int back();

    void print();
};

#endif
