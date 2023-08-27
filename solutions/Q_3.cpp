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
    Edge(const int64_t& to, const int64_t& flow, const int64_t& capacity, const int64_t& index_back_edge)
            : to_(to), flow_(flow), capacity_(capacity), index_back_edge_(index_back_edge) {
    }
    Edge() = default;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes) : quantity_vertexes_(quantity_vertexes) {
        edges_.resize(quantity_vertexes);
        dist_.resize(quantity_vertexes);
        deleted_edges_.resize(quantity_vertexes);
    }
    void PushEdge(const int& first_vert, const int& second_vert, const int64_t& weight);
    void PrintMaxFlow();

private:
    const int64_t k_max_weight_ = 10000000000000;
    int64_t quantity_vertexes_;
    int64_t max_flow_ = 0;
    std::vector<int64_t> dist_;
    std::vector<int64_t> deleted_edges_;
    std::vector<std::vector<Edge>> edges_;
    void Dinic();
    bool BFSFlow(const int& begin_vertex);
    int64_t DFSFlow(const int64_t& begin_vertex, const int64_t& curr_flow);
};
void Graph::PushEdge(const int& first_vert, const int& second_vert, const int64_t& weight) {
    int64_t index_back_edge = edges_[second_vert].size();
    edges_[first_vert].emplace_back(Edge(second_vert, 0, weight, index_back_edge));
    index_back_edge = edges_[first_vert].size() - 1;
    edges_[second_vert].emplace_back(Edge(first_vert, 0, 0, index_back_edge));
}
bool Graph::BFSFlow(const int& begin_vertex) {
    std::queue<int> queue_vertexes;
    queue_vertexes.push(begin_vertex);
    int64_t new_vertex = 0;
    std::fill(dist_.begin(), dist_.end(), k_max_weight_);
    dist_[begin_vertex] = 0;
    while (!queue_vertexes.empty()) {
        new_vertex = queue_vertexes.front();
        queue_vertexes.pop();
        for (auto& edge : edges_[new_vertex]) {
            if ((dist_[edge.to_] == k_max_weight_) && (edge.flow_ < edge.capacity_)) {
                dist_[edge.to_] = dist_[new_vertex] + 1;
                queue_vertexes.push(edge.to_);
            }
        }
    }
    return dist_[quantity_vertexes_ - 1] != k_max_weight_;
}
int64_t Graph::DFSFlow(const int64_t& begin_vertex, const int64_t& curr_flow) {
    if ((begin_vertex == quantity_vertexes_ - 1) || (!curr_flow)) {
        return curr_flow;
    }
    int64_t size = edges_[begin_vertex].size();
    for (int64_t i = deleted_edges_[begin_vertex]; i < size; ++i) {
        if ((dist_[begin_vertex] + 1) == dist_[edges_[begin_vertex][i].to_]) {
            if ((edges_[begin_vertex][i].flow_ < edges_[begin_vertex][i].capacity_)) {
                int64_t delta = DFSFlow(edges_[begin_vertex][i].to_,
                                        std::min(curr_flow, edges_[begin_vertex][i].capacity_ - edges_[begin_vertex][i].flow_));
                if (delta > 0) {
                    edges_[begin_vertex][i].flow_ += delta;
                    edges_[edges_[begin_vertex][i].to_][edges_[begin_vertex][i].index_back_edge_].flow_ -= delta;
                    return delta;
                }
            }
        }
        deleted_edges_[begin_vertex]++;
    }
    return 0;
}
void Graph::Dinic() {
    int delta = 0;
    while (BFSFlow(0)) {
        std::fill(deleted_edges_.begin(), deleted_edges_.end(), 0);
        delta = DFSFlow(0, k_max_weight_);
        while (delta != 0) {
            max_flow_ += delta;
            delta = DFSFlow(0, k_max_weight_);
        }
    }
}
void Graph::PrintMaxFlow() {
    Dinic();
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