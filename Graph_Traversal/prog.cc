#include "graph.h"

#include <iostream>
#include <sstream>
#include <string>

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
