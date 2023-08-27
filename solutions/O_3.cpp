#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <queue>
struct Edge {
    int64_t to_;
    int64_t flow_;
    int64_t capacity_;
    int64_t index_back_edge_;
    Edge(const int& to, const int& flow, const int64_t& capacity, const int64_t& index_back_edge)
            : to_(to), flow_(flow), capacity_(capacity), index_back_edge_(index_back_edge) {
    }
    Edge() = default;
};
struct BackEdge {
    int64_t vertex_;
    int64_t index_back_edge_;
    BackEdge(const int64_t& vertex, const int64_t& index_back_edge) : vertex_(vertex), index_back_edge_(index_back_edge) {
    }
    BackEdge() = default;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes) : quantity_vertexes_(quantity_vertexes) {
        edges_.resize(quantity_vertexes);
    }
    void PushEdge(const int& first_vert, const int& second_vert, const int64_t& weight);
    void PrintMaxFlow();

private:
    const int64_t k_max_weight_ = 10000000000000;
    int64_t quantity_vertexes_;
    int64_t max_flow_ = 0;
    std::vector<BackEdge> path_;
    std::vector<std::vector<Edge>> edges_;
    void EdmondsCarp();
    int64_t BFSFlow(const int& begin_vertex);
};
void Graph::PushEdge(const int& first_vert, const int& second_vert, const int64_t& weight) {
    int64_t index_back_edge = edges_[second_vert].size();
    edges_[first_vert].emplace_back(Edge(second_vert, 0, weight, index_back_edge));
    index_back_edge = edges_[first_vert].size() - 1;
    edges_[second_vert].emplace_back(Edge(first_vert, 0, 0, index_back_edge));
}
int64_t Graph::BFSFlow(const int& begin_vertex) {
    std::vector<bool> used;
    std::vector<int64_t> flows;
    used.resize(quantity_vertexes_, false);
    flows.resize(quantity_vertexes_, 0);
    std::queue<int> queue_vertexes;
    queue_vertexes.push(begin_vertex);
    int64_t new_vertex = 0;
    flows[begin_vertex] = k_max_weight_;
    while (!queue_vertexes.empty()) {
        new_vertex = queue_vertexes.front();
        queue_vertexes.pop();
        for (auto& edge : edges_[new_vertex]) {
            if ((!used[edge.to_]) && (edge.flow_ < edge.capacity_)) {
                if (std::min(edge.capacity_ - edge.flow_, flows[new_vertex]) > flows[edge.to_]) {
                    flows[edge.to_] = std::min(edge.capacity_ - edge.flow_, flows[new_vertex]);
                    used[edge.to_] = true;
                    path_[edge.to_] = BackEdge(new_vertex, edge.index_back_edge_);
                    queue_vertexes.push(edge.to_);
                }
            }
        }
    }
    return flows[quantity_vertexes_ - 1];
}
void Graph::EdmondsCarp() {
    path_.resize(quantity_vertexes_, {-1, -1});
    int64_t delta = BFSFlow(0);
    while (delta) {
        max_flow_ += delta;
        int64_t current_vertex = quantity_vertexes_ - 1;
        int64_t index_current_edge = 0;
        int64_t index_current_back_edge = 0;
        while (current_vertex != 0) {
            index_current_edge = path_[current_vertex].index_back_edge_;
            edges_[current_vertex][index_current_edge].flow_ -= delta;
            index_current_back_edge = edges_[current_vertex][index_current_edge].index_back_edge_;
            current_vertex = path_[current_vertex].vertex_;
            edges_[current_vertex][index_current_back_edge].flow_ += delta;
        }
        delta = BFSFlow(0);
    }
}
void Graph::PrintMaxFlow() {
    EdmondsCarp();
    std::cout << max_flow_;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes);
    int64_t first_vertex = 0;
    int64_t second_vertex = 0;
    int64_t capacity = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vertex >> second_vertex >> capacity;
        graph.PushEdge(first_vertex - 1, second_vertex - 1, capacity);
    }
    graph.PrintMaxFlow();
    return 0;
}