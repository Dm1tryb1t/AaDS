#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <queue>

template <typename Key, typename Val>
class BST {
private:
    struct Node {
        Key key;
        Val value;
        Node *left_child, *right_child;
        Node *parent;

        Node(Key key, Val value);
    };
    
    Node *root;

    Node* search_node(Key key) const;
    Node* search_min_node(Node *root) const;
    Node* search_max_node(Node *root) const;

public:
    BST() noexcept;
    ~BST() noexcept;
    
    bool add_node(Key key, Val value);
    bool set(Key key, Val newValue);
    bool delete_node(Key key);
    Val search(Key key) const;
    std::pair<Key, Val> min() const;
    std::pair<Key, Val> max() const;
    void print() const;
};



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



template <typename Key, typename Val>
BST<Key, Val>::Node::Node(Key key, Val value) :
    key(key), value(value),
    left_child(nullptr), right_child(nullptr), parent(nullptr) {}


template <typename Key, typename Val>
BST<Key, Val>::BST() noexcept : root(nullptr) {}
template <typename Key, typename Val>
BST<Key, Val>::~BST() noexcept {
    if (root) {
        std::queue<Node*> nodes_queue;
        nodes_queue.push(root);
        Node *cur_node;
        while (!nodes_queue.empty()) {
            cur_node = nodes_queue.front();
            nodes_queue.pop();
            if (cur_node->left_child) nodes_queue.push(cur_node->left_child);
            if (cur_node->right_child) nodes_queue.push(cur_node->right_child);
            delete cur_node;
        }
    }
}



template <typename Key, typename Val>
typename BST<Key, Val>::Node* BST<Key, Val>::search_node(Key key) const {
    Node *cur_node = root;
    while (cur_node) {
        if (key == cur_node->key) {
            break;
        }
        cur_node = ((key < cur_node->key) ? cur_node->left_child : cur_node->right_child);
    }
    return cur_node;
}
template <typename Key, typename Val>
typename BST<Key, Val>::Node* BST<Key, Val>::search_min_node(Node *root) const {
    if (!root) return nullptr;
    Node *cur_node = root;
    while (cur_node->left_child) {
        cur_node = cur_node->left_child;
    }
    return cur_node;
}
template <typename Key, typename Val>
typename BST<Key, Val>::Node* BST<Key, Val>::search_max_node(Node *root) const {
    if (!root) return nullptr;
    Node *cur_node = root;
    while (cur_node->right_child) {
        cur_node = cur_node->right_child;
    }
    return cur_node;
}



template <typename Key, typename Val>
bool BST<Key, Val>::add_node(Key key, Val value) {
    if (!root) {
        root = new Node(key, value);
        return 1;
    }
    Node *cur_node = nullptr;
    Node *next_node = root;
    while (next_node) {
        cur_node = next_node;
        if (key == cur_node->key) return 0;
        next_node = ((key < cur_node->key) ? cur_node->left_child : cur_node->right_child);
    }
    if (key < cur_node->key) {
        cur_node->left_child = new Node(key, value);
        cur_node->left_child->parent = cur_node;
    } else {
        cur_node->right_child = new Node(key, value);
        cur_node->right_child->parent = cur_node;
    }
    return 1;
}
template <typename Key, typename Val>
bool BST<Key, Val>::set(Key key, Val newValue) {
    Node* found_node = search_node(key);
    if (found_node) {
        found_node->value = newValue;
        return true;
    } 
    return false;
}
template <typename Key, typename Val>
bool BST<Key, Val>::delete_node(Key key) {
    Node* node_to_del = search_node(key);
    if (!node_to_del) return false;

    auto transplant = [&](Node* u, Node* v) {
        if (!u->parent) {
            root = v;
        } else if (u == u->parent->left_child) {
            u->parent->left_child = v;
        } else {
            u->parent->right_child = v;
        }
        if (v) {
            v->parent = u->parent;
        }
    };

    if (!node_to_del->left_child) {
        transplant(node_to_del, node_to_del->right_child);
    } else if (!node_to_del->right_child) {
        transplant(node_to_del, node_to_del->left_child);
    } else {
        Node* max_node_in_left_subtree = search_max_node(node_to_del->left_child);
        if (max_node_in_left_subtree->parent != node_to_del) {
            max_node_in_left_subtree->parent->right_child = max_node_in_left_subtree->left_child;
            if (max_node_in_left_subtree->left_child)
                max_node_in_left_subtree->left_child->parent = max_node_in_left_subtree->parent;
            max_node_in_left_subtree->left_child = node_to_del->left_child;
            max_node_in_left_subtree->left_child->parent = max_node_in_left_subtree;
        }
        transplant(node_to_del, max_node_in_left_subtree);
        max_node_in_left_subtree->right_child = node_to_del->right_child;
        max_node_in_left_subtree->right_child->parent = max_node_in_left_subtree;
    }

    delete node_to_del;
    return true;
}
template <typename Key, typename Val>
Val BST<Key, Val>::search(Key key) const {
    Node* found_node = search_node(key);
    if (!found_node) throw std::runtime_error("value not found");
    return found_node->value;
}
template <typename Key, typename Val>
std::pair<Key, Val> BST<Key, Val>::min() const {
    Node *min_node_in_tree = search_min_node(root);
    if (!min_node_in_tree) throw std::runtime_error("min is not found");
    return {min_node_in_tree->key, min_node_in_tree->value};
}
template <typename Key, typename Val>
std::pair<Key, Val> BST<Key, Val>::max() const {
    Node *max_node = search_max_node(root);
    if (!max_node) throw std::runtime_error("max is not found");
    return {max_node->key, max_node->value};
}
template <typename Key, typename Val>
void BST<Key, Val>::print() const {
    if (!root) {
        std::cout << "_" << std::endl;
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int levelSize = (int)q.size();
        bool all_null = true;
        std::vector<Node*> levelNodes;
        for (int i = 0; i < levelSize; ++i) {
            Node* cur = q.front();
            q.pop();
            levelNodes.push_back(cur);
            if (cur) {
                all_null = false;
                q.push(cur->left_child);
                q.push(cur->right_child);
            } else {
                q.push(nullptr);
                q.push(nullptr);
            }
        }
        if (all_null) break;
        for (size_t i = 0; i < levelNodes.size(); ++i) {
            Node* n = levelNodes[i];
            if (!n) {
                std::cout << "_";
            } else {
                if (n == root)
                    std::cout << "[" << n->key << " " << n->value << "]";
                else
                    std::cout << "[" << n->key << " " << n->value << " " << n->parent->key << "]";
            }
            if (i + 1 < levelNodes.size())
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}
