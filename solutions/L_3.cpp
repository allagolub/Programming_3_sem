#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
struct Edge {
    int64_t to_;
    int64_t weight_;
    Edge(const int64_t& to, const int64_t& weight) : to_(to), weight_(weight) {
    }
    friend bool operator<(const Edge& first, const Edge& second) {
        return ((first.weight_ < second.weight_) || ((first.weight_ == second.weight_) && (first.to_ < second.to_)));
    }
    Edge() = default;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes)
            : quantity_vertexes_(quantity_vertexes), begin_vertex_(quantity_vertexes - 1) {
        potentials_.resize(quantity_vertexes_, k_max_weight_);
        dist_.resize(quantity_vertexes_, std::vector<int64_t>(quantity_vertexes_, k_max_weight_));
        edges_.resize(quantity_vertexes);
    }
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight);
    void PrintMinDist();

private:
    const int64_t k_max_weight_ = 10000000;
    int64_t quantity_vertexes_;
    int64_t begin_vertex_;
    int64_t max_distance_ = -10000000;
    std::vector<std::vector<Edge>> edges_;
    std::vector<int64_t> potentials_;
    std::vector<std::vector<int64_t>> dist_;
    bool Relax(const int64_t& from, const Edge& edge);
    void BellmanFord();
    void Dijkstra(int64_t begin_vertex);
    void Johnson();
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    edges_[first_vert].emplace_back(Edge(second_vert, weight));
}
bool Graph::Relax(const int64_t& from, const Edge& edge) {
    if ((potentials_[from] != k_max_weight_) && (potentials_[edge.to_] > potentials_[from] + edge.weight_)) {
        potentials_[edge.to_] = potentials_[from] + edge.weight_;
        return true;
    }
    return false;
}
void Graph::BellmanFord() {
    potentials_[begin_vertex_] = 0;
    std::queue<int64_t> queues;
    queues.push(begin_vertex_);
    for (int64_t k = 0; (!queues.empty() && k <= quantity_vertexes_); ++k) {
        auto new_vert = queues.front();
        queues.pop();
        for (auto& edge : edges_[new_vert]) {
            if (Relax(new_vert, edge)) {
                queues.push(edge.to_);
            }
        }
    }
}
void Graph::Dijkstra(int64_t begin_vertex) {
    std::vector<bool> used;
    used.resize(quantity_vertexes_, false);
    std::set<Edge> set_vertexes;
    dist_[begin_vertex][begin_vertex] = 0;
    set_vertexes.insert(Edge(begin_vertex, dist_[begin_vertex][begin_vertex]));
    while (!set_vertexes.empty()) {
        auto new_vertex = *set_vertexes.begin();
        set_vertexes.erase(set_vertexes.begin());
        used[new_vertex.to_] = true;
        for (auto& edge : edges_[new_vertex.to_]) {
            if ((edge.weight_ + dist_[begin_vertex][new_vertex.to_] - potentials_[edge.to_] + potentials_[new_vertex.to_] <
                 dist_[begin_vertex][edge.to_]) &&
                (!used[edge.to_])) {
                set_vertexes.erase(Edge(edge.to_, dist_[begin_vertex][edge.to_]));
                set_vertexes.insert(Edge(edge.to_, edge.weight_ + dist_[begin_vertex][new_vertex.to_] - potentials_[edge.to_] +
                                                   potentials_[new_vertex.to_]));
                dist_[begin_vertex][edge.to_] =
                        edge.weight_ + dist_[begin_vertex][new_vertex.to_] - potentials_[edge.to_] + potentials_[new_vertex.to_];
            }
        }
    }
}
void Graph::Johnson() {
    BellmanFord();
    quantity_vertexes_--;
    for (int64_t i = 0; i < quantity_vertexes_; ++i) {
        Dijkstra(i);
    }
    for (int64_t i = 0; i < quantity_vertexes_; ++i) {
        for (int64_t j = 0; j < quantity_vertexes_; ++j) {
            int64_t new_dist = dist_[i][j] + potentials_[j] - potentials_[i];
            if ((dist_[i][j] != k_max_weight_) && (i != j) && (new_dist > max_distance_)) {
                max_distance_ = new_dist;
            }
            dist_[i][j] -= potentials_[i] - potentials_[j];
        }
    }
}
void Graph::PrintMinDist() {
    Johnson();
    std::cout << max_distance_;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes + 1);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight;
        graph.PushEdge(first_vert, second_vert, weight);
    }
    for (int64_t i = 0; i < quantity_vertexes; ++i) {
        graph.PushEdge(quantity_vertexes, i, 0);
    }
    graph.PrintMinDist();
    return 0;
}