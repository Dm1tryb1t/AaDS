#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <queue>
#include <vector>

class Graph {
private:
    bool oriented;
    std::unordered_map<std::string, std::vector<std::string>> adjacency_list;

    std::queue<std::string> dfs(const std::string&);
    std::queue<std::string> bfs(const std::string&);

public:
    Graph();
    Graph(char type);

    bool add_edge(const std::pair<std::string, std::string>&);
    std::queue<std::string> crawl(const std::string&, char);
};

#endif
