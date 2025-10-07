#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <vector>

class Graph {
private:
    bool oriented;
    int vertex_count;
    std::vector<std::vector<bool>> adjacency_matrix;

    // void dfs_helper(int);
    // void bfs_helper(int);
    std::queue<int> dfs(int);
    std::queue<int> bfs(int);

public:
    Graph();
    Graph(char, int);

    bool add_edge(std::pair<int, int>);
    void delete_edge(std::pair<int, int>);
    
    std::queue<int> crawl(int, char);
};

#endif
