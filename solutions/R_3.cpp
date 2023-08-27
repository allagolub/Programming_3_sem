#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
struct Edge {
    int64_t from_;
    int64_t to_;
    int64_t time_in_;
    int64_t time_out_;
    Edge(const int64_t& from, const int64_t& to, const int64_t& time_in, const int64_t& time_out)
            : from_(from), to_(to), time_in_(time_in), time_out_(time_out) {
    }
    friend bool operator<(const Edge& first, const Edge& second) {
        return first.time_in_ > second.time_in_;
    }
    Edge() = default;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes, int64_t begin_vertex, int64_t end_vertex)
            : quantity_vertexes_(quantity_vertexes), begin_vertex_(begin_vertex), end_vertex_(end_vertex) {
        dist_.resize(quantity_vertexes_, k_max_weight_);
    }
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& time_in, const int64_t& time_out);
    void PrintMinDist();

private:
    const int64_t k_max_weight_ = std::numeric_limits<int64_t>::max();
    int64_t quantity_vertexes_;
    int64_t begin_vertex_;
    int64_t end_vertex_;
    std::vector<Edge> edges_;
    std::vector<int64_t> dist_;
    bool Relax(const Edge& edge);
    void BellmanFord();
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& time_in,
                     const int64_t& time_out) {
    edges_.emplace_back(Edge(first_vert, second_vert, time_in, time_out));
}
bool Graph::Relax(const Edge& edge) {
    if ((edge.time_in_ >= dist_[edge.from_]) && (edge.time_out_ < dist_[edge.to_])) {
        dist_[edge.to_] = edge.time_out_;
        return true;
    }
    return false;
}
void Graph::BellmanFord() {
    dist_[begin_vertex_] = 0;
    std::sort(edges_.begin(), edges_.end());
    for (int64_t i = 0; i <= quantity_vertexes_; ++i) {
        for (auto& edge : edges_) {
            Relax(edge);
        }
    }
}
void Graph::PrintMinDist() {
    BellmanFord();
    std::cout << dist_[end_vertex_] << ' ';
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    std::cin >> quantity_vertexes;
    int64_t begin_vertex = 0;
    int64_t end_vertex = 0;
    std::cin >> begin_vertex >> end_vertex;
    Graph graph(quantity_vertexes, begin_vertex - 1, end_vertex - 1);
    int64_t from = 0;
    int64_t to = 0;
    int64_t time_in = 0;
    int64_t time_out = 0;
    std::cin >> quantity_edges;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> from >> time_in >> to >> time_out;
        graph.PushEdge(from - 1, to - 1, time_in, time_out);
    }
    graph.PrintMinDist();
    return 0;
}