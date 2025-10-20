#include "graph.h"

#include <algorithm>
#include <stack>

Graph::Graph() : oriented(false) {}
Graph::Graph(char type) : oriented(type == 'd') {}

bool Graph::add_edge(const std::pair<std::string, std::string>& edge) {
    const std::string& from = edge.first;
    const std::string& to = edge.second;

    adjacency_list[from]; // создаём ключ, если его нет
    adjacency_list[to];
    adjacency_list[from].push_back(to);
    if (!oriented) adjacency_list[to].push_back(from);
    return true;
}

std::queue<std::string> Graph::dfs(const std::string& start) {
    for (auto& adjacency : adjacency_list) {
        auto& neighbours = adjacency.second;
        std::sort(neighbours.begin(), neighbours.end(), std::greater<std::string>());
    }

    std::queue<std::string> result;
    std::stack<std::string> stack;
    std::unordered_map<std::string, bool> visited;

    stack.push(start);
    while (!stack.empty()) {
        std::string cur = stack.top();
        stack.pop();
        if (visited[cur]) continue;
        visited[cur] = true;

        for (const auto& next : adjacency_list[cur])
            stack.push(next);

        result.push(cur);
    }
    return result;
}

std::queue<std::string> Graph::bfs(const std::string& start) {
    for (auto& adjacency : adjacency_list) {
        auto& neighbours = adjacency.second;
        std::sort(neighbours.begin(), neighbours.end());
    }

    std::queue<std::string> result;
    std::queue<std::string> q;
    std::unordered_map<std::string, bool> visited;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        std::string cur = q.front();
        q.pop();

        for (const auto& next : adjacency_list[cur])
            if (!visited[next]) {
                visited[next] = true;
                q.push(next);
            }

        result.push(cur);
    }
    return result;
}

std::queue<std::string> Graph::crawl(const std::string& start_vertex, char type) {
    bool traversal_is_bfs = (type == 'b');
    return traversal_is_bfs ? bfs(start_vertex) : dfs(start_vertex);
}

// void Graph::delete_edge(std::pair<int, int> edge) {
//     int from = edge.first - 1, to = edge.second - 1;
//     adjacency_matrix[from][to] = 0;
//     if (!oriented) adjacency_matrix[to][from] = 0;
// } переделать
