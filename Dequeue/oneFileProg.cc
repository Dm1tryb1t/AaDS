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

static bool has_trailing_chars(std::istringstream &iss) {
    std::string rest;
    std::getline(iss, rest);
    if (!rest.empty() && rest.back() == '\r') rest.pop_back();
    return !rest.empty();
}
// Пробелы в конце строк - невалидный вход, нужно обработать
// Пустые строки - игнорировать
// Проверить и переделать все вводы и проверки, X - строка
int main() {
    MyDequeue deq;
    std::string first_line;
    bool got_size = false;
    if (std::getline(std::cin, first_line)) {
        std::istringstream iss(first_line);
        std::string cmd;
        std::string tmp;
        if (!(iss >> cmd)) {
            std::cout << "error\n";
        } else if (cmd == "set_size") {
            int n;
            if (iss >> n) {
                if (has_trailing_chars(iss)) {
                    std::cout << "error\n";
                } else {
                    deq = MyDequeue(n);
                    got_size = true;
                }
            } else {
                std::cout << "error\n";
            }
        }
    }
    // if (!got_size) return -1;
    
    std::string line = "";
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        std::string tmp;
        if (!(iss >> cmd)) continue;
        if (cmd == "pushb") {
            int x;
            if ((iss >> x)) {
                if (has_trailing_chars(iss)) {
                    std::cout << "error\n";
                    continue;
                }
                if (deq.push_back(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error\n";
            continue;
        }
        if (cmd == "pushf") {
            int x;
            if ((iss >> x)) {
                if (has_trailing_chars(iss)) {
                    std::cout << "error\n";
                    continue;
                }
                if (deq.push_front(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error\n";
            continue;
        }
        if (cmd == "popb") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            int res = deq.pop_back();
            if (res == INF) std::cout << "underflow\n";
            else std::cout << res << '\n';
            continue;
        }
        if (cmd == "popf") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            int res = deq.pop_front();
            if (res == INF) std::cout << "underflow\n";
            else std::cout << res << '\n';
            continue;
        }
        if (cmd == "print") {
            if (has_trailing_chars(iss)) {
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
    if (sz == 0) std::cout << "empty";
    for (int i = l; i < l + sz; ++i) {
        std::cout << values[i % capacity] << ' ';
    }
    std::cout << '\n';
}

