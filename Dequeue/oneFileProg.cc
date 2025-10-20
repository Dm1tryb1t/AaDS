#include <iostream>
#include <sstream>
#include <string>
// Уточнить как обрабатывается первая входная строка с set_size

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
    
    int size();
    std::string front();
    std::string back();

    void print();
};

static bool has_trailing_chars(std::istringstream &iss) {
    std::string rest;
    std::getline(iss, rest);
    if (!rest.empty() && rest.back() == '\r') rest.pop_back();
    return !rest.empty();
}

inline bool cmd_is_valid(const std::string& line) {
    int i = 0;
    while (i < line.length() && line[i] != ' ') ++i;
    if (i == line.length()) return 1;
    if (i == 0) return 0;
    ++i;
    if (i == line.length() && line[i - 1] == ' ') return 0;
    while (i < line.length() && line[i] != ' ') ++i;
    if (i == line.length()) return 1;
    return 0;
}

int main() {
    MyDequeue* deq = nullptr;
    std::string first_line;
    // bool got_size = false;
    
    while (std::getline(std::cin, first_line)) {
        if (first_line.empty()) continue;
        if (!cmd_is_valid(first_line)) {
            std::cout << "error\n";
            continue;
        }
        std::istringstream iss(first_line);
        std::string cmd;
        std::string tmp;
        if (!(iss >> cmd)) {
            std::cout << "error\n";
            continue;
        }
        if (cmd == "set_size") {
            int n;
            if (iss >> n && n >= 0) {
                deq = new MyDequeue(n);
                break;
            }
            std::cout << "error\n";
            continue;
        }
        std::cout << "error\n";
    }
    
    // if (deq == nullptr) deq = new MyDequeue();
    // if (!got_size || deq == nullptr) {
    //     std::cout << "error\n";
    //     return -1;
    // }
    
    std::string line = "";
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        if (!cmd_is_valid(line)) {
            std::cout << "error\n";
            continue;
        }
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        if (cmd == "pushb") {
            std::string x;
            if ((iss >> x)) {
                if (deq->push_back(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error\n";
            continue;
        }
        if (cmd == "pushf") {
            std::string x;
            if ((iss >> x)) {
                if (deq->push_front(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error\n";
            continue;
        }
        if (cmd == "popb") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            std::string res = deq->pop_back();
            if (res.empty()) std::cout << "underflow\n";
            else std::cout << res << '\n';
            continue;
        }
        if (cmd == "popf") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            std::string res = deq->pop_front();
            if (res.empty()) std::cout << "underflow\n";
            else std::cout << res << '\n';
            continue;
        }
        if (cmd == "print") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            deq->print();
            continue;
        }
        std::cout << "error\n";
    }

    delete deq;
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
    if (maxsz > 0) values = new std::string[maxsz];
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

    std::string* newValues = new std::string[newsz];
    if (values && sz > 0) {
        int copySize = std::min(sz, newsz);
        for (int i = 0; i < copySize; ++i) {
            newValues[i] = values[(l + i) % capacity];
        }
        delete[] values;
        sz = copySize;
        if (sz > 0) {
            l = 0;
            r = sz - 1;
        } else {
            l = r = -1;
        }
    } else {
        sz = 0;
        l = r = -1;
    }
    values = newValues;
    capacity = newsz;
}

int MyDequeue::push_back(std::string newValue) {
    if (sz == capacity) return -1;

    if (sz == 0) {
        l = r = 0;
    } else {
        r = (r + 1) % capacity;
    }
    values[r] = newValue;
    ++sz;

    return 1;
}

int MyDequeue::push_front(std::string newValue) {
    if (sz == capacity) return -1;

    if (sz == 0) {
        l = r = 0;
    } else {
        l = (l - 1 + capacity) % capacity;
    }
    values[l] = newValue;
    ++sz;

    return 1;
}

std::string MyDequeue::pop_back() {
    if (sz == 0) return "";

    std::string val = values[r];
    if (sz == 1) {
        l = r = -1;
    } else {
        r = (r - 1 + capacity) % capacity;
    }
    --sz;

    return val;
}

std::string MyDequeue::pop_front() {
    if (sz == 0) return "";

    std::string val = values[l];
    if (sz == 1) {
        l = r = -1;
    } else {
        l = (l + 1) % capacity;
    }
    --sz;

    return val;
}

int MyDequeue::size() {
    return sz;
}

std::string MyDequeue::front() {
    if (sz == 0) return "";
    return values[l];
}

std::string MyDequeue::back() {
    if (sz == 0) return "";
    return values[r];
}

void MyDequeue::print() {
    if (sz == 0) {
        std::cout << "empty\n";
        return;
    }
    for (int i = 0; i < sz; ++i) {
        std::cout << values[(l + i) % capacity];
        if (i < sz - 1) std::cout << " ";
    }
    std::cout << '\n';
}
