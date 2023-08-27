#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
struct Edge {
    int64_t to_;
    int64_t flow_;
    int64_t capacity_;
    int64_t index_back_edge_;
    Edge(const int64_t& to, const int64_t& flow, const int64_t& capacity, const int64_t& index_back_edge)
            : to_(to), flow_(flow), capacity_(capacity), index_back_edge_(index_back_edge) {
    }
    Edge() = default;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes) : quantity_vertexes_(quantity_vertexes) {
        used_.resize(quantity_vertexes, -1);
        edges_.resize(quantity_vertexes);
    }
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight);
    void PrintMaxFlow();

private:
    const int64_t k_max_weight_ = 100000000;
    int64_t quantity_vertexes_;
    int64_t max_flow_ = 0;
    int time_in_ = 1;
    std::vector<std::vector<Edge>> edges_;
    std::vector<int> used_;
    void FordFulkerson();
    int64_t DFSFlow(const int64_t& begin_vertex, const int64_t& curr_flow);
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    int64_t index_back_edge = edges_[second_vert].size();
    edges_[first_vert].emplace_back(Edge(second_vert, 0, weight, index_back_edge));
    index_back_edge = edges_[first_vert].size() - 1;
    edges_[second_vert].emplace_back(Edge(first_vert, 0, 0, index_back_edge));
}
int64_t Graph::DFSFlow(const int64_t& begin_vertex, const int64_t& curr_flow) {
    if (begin_vertex == quantity_vertexes_ - 1) {
        return curr_flow;
    }
    used_[begin_vertex] = time_in_;
    for (auto& edge : edges_[begin_vertex]) {
        if ((used_[edge.to_] != time_in_) && (edge.flow_ < edge.capacity_)) {
            int64_t delta = DFSFlow(edge.to_, std::min(curr_flow, edge.capacity_ - edge.flow_));
            if (delta > 0) {
                edge.flow_ += delta;
                edges_[edge.to_][edge.index_back_edge_].flow_ -= delta;
                return delta;
            }
        }
    }
    return 0;
}
void Graph::FordFulkerson() {
    int delta = DFSFlow(0, k_max_weight_);
    while (delta) {
        max_flow_ += delta;
        time_in_++;
        delta = DFSFlow(0, k_max_weight_);
    }
}
void Graph::PrintMaxFlow() {
    FordFulkerson();
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