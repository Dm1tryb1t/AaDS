#include "bst.hpp"

#include <iostream>
#include <sstream>
#include <string>

static bool has_trailing_chars(std::istringstream &iss) {
    std::string rest;
    std::getline(iss, rest);
    if (!rest.empty() && rest.back() == '\r') rest.pop_back();
    return !rest.empty();
}

inline bool cmd_is_normalized(std::string& line) {
    if (line[0] == ' ' || line[line.size() - 1] == ' ') return 0;
    for (size_t i = 2; i < line.size() - 1; ++i)
        if (line[i] == ' ' && line[i - 1] == ' ')
            return 0;
    return 1;
}

int main() {
    BST<long long, std::string>* tree = new BST<long long, std::string>();

    std::string line;
    std::string cmd;
    long long key;
    std::string value;
    std::pair<long long, std::string> found_node;

    while (std::getline(std::cin, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) continue;
        if (!cmd_is_normalized(line)) {
            // std::cerr << "DEBUG: normalized failed for: [" << line << "]" << std::endl;
            std::cout << "error\n";
            continue;
        }
        std::istringstream iss(line);
        iss >> cmd;
        if (cmd == "add") {
            if (!(iss >> key >> value)) {
                std::cout << "error\n";
                continue;
            }
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            if (!tree->add_node(key, value)) std::cout << "error\n";
            continue;
        }
        if (cmd == "set") {
            if (!(iss >> key >> value)) {
                std::cout << "error\n";
                continue;
            }
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            if (!tree->set(key, value)) std::cout << "error\n";
            continue;
        }
        if (cmd == "delete") {
            if (!(iss >> key)) {
                std::cout << "error\n";
                continue;
            }
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            if (!tree->delete_node(key)) std::cout << "error\n";
            continue;
        }
        if (cmd == "search") {
            if (!(iss >> key)) {
                std::cout << "error\n";
                continue;
            }
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            try {
                found_node = {key, tree->search(key)};
                std::cout << "1 " << found_node.second << std::endl;
            } catch (std::runtime_error e) {
                std::cout << "0\n";
            }
            continue;
        }
        if (cmd == "min") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            try {
                found_node = tree->min();
                std::cout << found_node.first << ' ' << found_node.second << std::endl;
            } catch (std::runtime_error e) {
                std::cout << "error\n";
            }
            continue;
        }
        if (cmd == "max") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            try {
                found_node = tree->max();
                std::cout << found_node.first << ' ' << found_node.second << std::endl;
            } catch (std::runtime_error e) {
                std::cout << "error\n";
            }
            continue;
        }
        if (cmd == "print") {
            if (has_trailing_chars(iss)) {
                std::cout << "error\n";
                continue;
            }
            tree->print();
            continue;
        }
        std::cout << "error\n";
    }

    delete tree;
    return 0;
}
