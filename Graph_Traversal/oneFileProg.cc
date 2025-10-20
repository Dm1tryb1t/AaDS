#include <algorithm>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

class Graph {
private:
    bool oriented;
    std::unordered_map<std::string, std::vector<std::string>> adjacency_list;

    std::queue<std::string> dfs(const std::string&);
    std::queue<std::string> bfs(const std::string&);

public:
    Graph() : oriented(false) {}
    Graph(char type) : oriented(type == 'd') {}

    bool add_edge(const std::pair<std::string, std::string>&);
    std::queue<std::string> crawl(const std::string&, char);
};

int main() {
    std::string first_line;
    char graph_type;
    std::string start_vertex;
    char crawl_type;

    if (!std::getline(std::cin, first_line)) return -1;
    {
        std::istringstream iss(first_line);
        if (!(iss >> graph_type) || !(graph_type == 'd' || graph_type == 'u')) return -1;
        if (!(iss >> start_vertex)) return 0;
        if (!(iss >> crawl_type) || !(crawl_type == 'd' || crawl_type == 'b')) return -1;
    }

    Graph graph(graph_type);

    std::string line;
    std::vector<std::pair<std::string, std::string>> edges;
    while (std::getline(std::cin, line)) {
        if (line.empty()) break;
        std::istringstream iss(line);
        std::string from, to, extra;
        if (!(iss >> from >> to)) return -1;
        if ((iss >> extra) && !extra.empty()) return -1;
        edges.push_back({from, to});
    }

    for (const auto& edge : edges)
        if (!graph.add_edge(edge)) return -1;

    std::queue<std::string> vertex_queue = graph.crawl(start_vertex, crawl_type);
    while (!vertex_queue.empty()) {
        std::cout << vertex_queue.front() << '\n';
        vertex_queue.pop();
    }

    return 0;
}

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
