#include "my_dequeue.h"

#include <sstream>
#include <string>

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
        // Обработать неверный ввод после команды !!!!
        std::istringstream iss(line);
        std::string cmd;
        if (!(iss >> cmd)) continue;
        if (cmd == "pushb") {
            int x;
            if ((iss >> x)) {
                if (deq.push_back(x) == -1) std::cout << "overflow\n";
            }
            continue;
        }
        if (cmd == "pushf") {
            int x;
            if ((iss >> x)) {
                if (deq.push_front(x) == -1) std::cout << "overflow\n";
            }
            continue;
        }
        if (cmd == "popb") {
            if (!deq.pop_back()) std::cout << "underflow\n";
            continue;
        }
        if (cmd == "popf") {
            if (!deq.pop_front()) std::cout << "underflow\n";
            continue;
        }
        if (cmd == "print") {
            deq.print();
            continue;
        }
        std::cout << "error\n";
    }

    return 0;
}
