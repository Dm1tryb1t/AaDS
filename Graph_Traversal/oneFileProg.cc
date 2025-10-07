#include <iostream>
#include <sstream>
#include <stack>
#include <string>
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

int main() {
    std::string first_line = "";
    char graph_type;
    int start_vertex;
    char crawl_type;
    if (!std::getline(std::cin, first_line)) return -1;
    {
        std::istringstream iss(first_line);
        if (!(iss >> graph_type) || !(graph_type == 'd' || graph_type == 'u')) return -1;
        if (!(iss >> start_vertex)) return 0;
        if (!(iss >> crawl_type) || !(crawl_type == 'd' || crawl_type == 'b')) return -1;
    }

    std::string line;
    int vertex_count = 0;
    std::vector<std::pair<int, int>> edges;
    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        std::istringstream iss(line);
        int from, to;
        std::string tmp;
        if (!(iss >> from >> to)) return -1;
        if ((iss >> tmp) && !tmp.empty()) return -1;
        edges.push_back({from, to});
        vertex_count = std::max(std::max(from, to), vertex_count);
    }

    Graph graph(graph_type, vertex_count);
    for (const auto& edge : edges) if (!graph.add_edge(edge)) return -1;
    std::queue<int> vertex_queue = graph.crawl(start_vertex, crawl_type);
    while (!vertex_queue.empty()) {
        int vertex = vertex_queue.front();
        vertex_queue.pop();
        std::cout << vertex << '\n';
    }

    return 0;
}

Graph::Graph() : vertex_count(0) { }
Graph::Graph(char type, int n) : vertex_count(n), oriented(type == 'd') {
    adjacency_matrix = std::vector<std::vector<bool>>(n, std::vector<bool> (n, 0));
}

std::queue<int> Graph::dfs(int start) {
    std::queue<int> dfs_queue;
    std::stack<int> vertex_queue;
    std::vector<bool> visited(vertex_count, 0);
    vertex_queue.push(start);
    while(!vertex_queue.empty()) {
        int cur_vertex = vertex_queue.top();
        vertex_queue.pop();
        if (visited[cur_vertex]) continue;
        visited[cur_vertex] = 1;
        for (int vertex = 0; vertex < vertex_count; ++vertex)
            if (adjacency_matrix[cur_vertex][vertex])
                vertex_queue.push(vertex);
        dfs_queue.push(cur_vertex + 1);
    }
    return dfs_queue;
}
std::queue<int> Graph::bfs(int start) {
    std::queue<int> bfs_queue;
    std::queue<int> vertex_queue;
    std::vector<bool> visited(vertex_count, 0);
    vertex_queue.push(start);
    visited[start] = 1;
    while(!vertex_queue.empty()) {
        int cur_vertex = vertex_queue.front();
        vertex_queue.pop();
        for (int vertex = 0; vertex < vertex_count; ++vertex)
            if (adjacency_matrix[cur_vertex][vertex] && !visited[vertex]) {
                vertex_queue.push(vertex);
                visited[vertex] = 1;
            }
        bfs_queue.push(cur_vertex + 1);
    }
    return bfs_queue;
}

bool Graph::add_edge(std::pair<int, int> edge) {
    int from = edge.first - 1, to = edge.second - 1;
    if (from >= vertex_count || to >= vertex_count) return 0;
    adjacency_matrix[from][to] = 1;
    if (!oriented) adjacency_matrix[to][from] = 1;
    return 1;
}
void Graph::delete_edge(std::pair<int, int> edge) {
    int from = edge.first - 1, to = edge.second - 1;
    adjacency_matrix[from][to] = 0;
    if (!oriented) adjacency_matrix[to][from] = 0;
}

std::queue<int> Graph::crawl(int start_vertex, char type) {
    return ((type == 'b') ? bfs(start_vertex - 1) : dfs(start_vertex - 1));
}
