#ifndef MY_DEQUEUE_H
#define MY_DEQUEUE_H

#include <iostream>

#define INF 1e9

class MyDequeue {
private:
    std::string* values;
    int l, r;
    int sz;
    int capacity;

public:
    MyDequeue();
    MyDequeue(int);
    ~MyDequeue();

    void setsz(int);
    int push_back(std::string);
    int push_front(std::string);
    std::string pop_back();
    std::string pop_front();
    
    std::string front();
    std::string back();

    void print();
};

#endif
