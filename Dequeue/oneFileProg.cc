#include <iostream>
#include <sstream>
#include <string>

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

    int push_back(int);
    int push_front(int);
    int pop_back();
    int pop_front();
    
    void print();
};

int main() {
    MyDequeue deq;
    std::string first_line;
    bool got_size = false;
    while (std::getline(std::cin, first_line)) {
        if (!first_line.empty() && first_line.back() == '\r') first_line.pop_back();
        std::istringstream iss(first_line);
        std::string cmd;
        if (!(iss >> cmd)) continue;
        if (cmd == "set_size") {
            int n;
            if (iss >> n) {
                deq = MyDequeue(n);
                got_size = true;
                break;
            }
        }
    }
    if (!got_size) return 0;
    
    std::string line = "";
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        std::string tmp;
        if (!(iss >> cmd)) continue;
        if (cmd == "pushb") {
            int x;
            if ((iss >> x)) {
                if (iss >> tmp && !tmp.empty()) {
                    std::cout << "error\n";
                    continue;
                }
                if (deq.push_back(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error";
            continue;
        }
        if (cmd == "pushf") {
            int x;
            if ((iss >> x)) {
                if (iss >> tmp && !tmp.empty()) {
                    std::cout << "error\n";
                    continue;
                }
                if (deq.push_front(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error";
            continue;
        }
        if (cmd == "popb") {
            if (iss >> tmp && !tmp.empty()) {
                std::cout << "error\n";
                continue;
            }
            if (deq.pop_back() != INF) std::cout << "underflow\n";
            continue;
        }
        if (cmd == "popf") {
            if (iss >> tmp && !tmp.empty()) {
                std::cout << "error\n";
                continue;
            }
            if (deq.pop_front() != INF) std::cout << "underflow\n";
            continue;
        }
        if (cmd == "print") {
            if (iss >> tmp && !tmp.empty()) {
                std::cout << "error\n";
                continue;
            }
            deq.print();
            continue;
        }
        std::cout << "error\n";
    }

    return 0;
}

MyDequeue::MyDequeue() {
    l = r = -1;
    capacity = sz = 0;
    values = nullptr;
}
MyDequeue::MyDequeue(int maxsz) : capacity(maxsz) {
    l = r = -1;
    sz = 0;
    values = new int[maxsz];
}
MyDequeue::~MyDequeue() {
    if (values) delete[] values;
    values = nullptr;
    capacity = sz = 0;
    l = r = -1;
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
    } else l = (l - 1 + capacity) % capacity;
    values[l] = newValue;

    ++sz;
    return 1;
}
int MyDequeue::pop_back() {
    if (sz == 0) return INF;

    int val = values[r];
    r = (r - 1 + capacity) % capacity;

    if ((--sz) == 0) l = r = -1;

    return val;
}
int MyDequeue::pop_front() {
    if (sz == 0) return INF;

    int val = values[l];
    l = (l + 1) % capacity;
    
    if ((--sz) == 0) l = r = -1;

    return val;
}

void MyDequeue::print() {
    for (int i = l; i < l + sz; ++i) {
        std::cout << values[i % capacity] << ' ';
    }
    std::cout << '\n';
}

