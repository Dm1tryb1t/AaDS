#include "graph.h"

#include <iostream>
#include <sstream>
#include <string>

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
        if ((iss >> tmp) || !tmp.empty()) return -1;
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
