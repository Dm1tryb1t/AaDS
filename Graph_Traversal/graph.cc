#include "graph.h"

#include <stack>

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
