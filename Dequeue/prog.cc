#include "my_dequeue.h"

#include <sstream>
#include <string>
// Уточнить как обрабатывается первая входная строка с set_size

static bool has_trailing_chars(std::istringstream &iss) {
    std::string rest;
    std::getline(iss, rest);
    if (!rest.empty() && rest.back() == '\r') rest.pop_back();
    return !rest.empty();
}

inline bool cmd_is_valid(std::string& line) {
    int i = 0;
    while (i < line.length() && line[i] != ' ') ++i;
    if (i == line.length()) return 1;
    ++i;
    if (i == line.length() && line[i - 1] == ' ') return 0;
    while (i < line.length() && line[i] != ' ') ++i;
    if (i == line.length()) return 1;
    return 0;
}

int main() {
    MyDequeue deq;
    std::string first_line;
    // bool got_size = false;
    while (std::getline(std::cin, first_line)) {
        if (first_line.empty()) continue;
        if (!cmd_is_valid(first_line)) {
            std::cout << "error\n";
            break;
        }
        std::istringstream iss(first_line);
        std::string cmd;
        std::string tmp;
        if (!(iss >> cmd)) {
            std::cout << "error\n";
        } else if (cmd == "set_size") {
            int n;
            if (iss >> n) {
                deq = MyDequeue(n);
                // got_size = true;
            } else {
                std::cout << "error\n";
            }
            break;
        }
    }
    // if (!got_size) return -1;

    std::string line = "";
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string cmd;
        std::string tmp;
        if (!cmd_is_valid(line)) {
            std::cout << "error\n";
            continue;
        }
        if (!(iss >> cmd)) continue;
        if (cmd == "pushb") {
            std::string x;
            if ((iss >> x)) {
                // if (has_trailing_chars(iss)) {
                //     std::cout << "error\n";
                //     continue;
                // }
                if (deq.push_back(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error\n";
            continue;
        }
        if (cmd == "pushf") {
            std::string x;
            if ((iss >> x)) {
                // if (has_trailing_chars(iss)) {
                //     std::cout << "error\n";
                //     continue;
                // }
                if (deq.push_front(x) == -1) std::cout << "overflow\n";
            } else std::cout << "error\n";
            continue;
        }
        if (cmd == "popb") {
            // if (has_trailing_chars(iss)) {
            //     std::cout << "error\n";
            //     continue;
            // }
            std::string res = deq.pop_back();
            if (res.empty()) std::cout << "underflow\n";
            else std::cout << res << '\n';
            continue;
        }
        if (cmd == "popf") {
            // if (has_trailing_chars(iss)) {
            //     std::cout << "error\n";
            //     continue;
            // }
            std::string res = deq.pop_front();
            if (res.empty()) std::cout << "underflow\n";
            else std::cout << res << '\n';
            continue;
        }
        if (cmd == "print") {
            // if (has_trailing_chars(iss)) {
            //     std::cout << "error\n";
            //     continue;
            // }
            deq.print();
            continue;
        }
        std::cout << "error\n";
    }

    return 0;
}
