#include <algorithm>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
struct Edge {
    int64_t to_;
    int64_t weight_;
    Edge(const int64_t& to, const int64_t& weight) : to_(to), weight_(weight) {
    }
    Edge() = default;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes, int64_t quantity_edges_in_path, int64_t begin_vertex, int64_t end_vertex)
            : quantity_vertexes_(quantity_vertexes)
            , quantity_edges_in_path_(quantity_edges_in_path)
            , begin_vertex_(begin_vertex)
            , end_vertex_(end_vertex) {
        edges_.resize(quantity_vertexes_);
        dist_.resize(quantity_edges_in_path + 1);
        for (int64_t i = 0; i <= quantity_edges_in_path; ++i) {
            dist_[i].resize(quantity_vertexes_, k_max_weight_);
        }
    }
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight);
    void PrintMinDist();

private:
    const int64_t k_max_weight_ = 1000000000;
    int64_t quantity_vertexes_;
    int64_t quantity_edges_in_path_;
    int64_t begin_vertex_;
    int64_t end_vertex_;
    std::vector<std::vector<Edge>> edges_;
    std::vector<std::vector<int64_t>> dist_;
    bool Relax(int64_t order, int64_t from, const Edge& edge);
    void BellmanFord();
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    edges_[first_vert].emplace_back(Edge(second_vert, weight));
}
bool Graph::Relax(int64_t order, int64_t from, const Edge& edge) {
    if (dist_[order + 1][edge.to_] > dist_[order][from] + edge.weight_) {
        dist_[order + 1][edge.to_] = dist_[order][from] + edge.weight_;
        return true;
    }
    return false;
}
void Graph::BellmanFord() {
    dist_[0][begin_vertex_] = 0;
    std::vector<std::queue<int64_t>> queues;
    queues.resize(quantity_edges_in_path_ + 2);
    queues[0].push(begin_vertex_);
    for (int64_t k = 0; (!queues[k].empty() && k < quantity_edges_in_path_); ++k) {
        bool is_change = false;
        while (!queues[k].empty()) {
            auto new_vert = queues[k].front();
            queues[k].pop();
            for (auto& edge : edges_[new_vert]) {
                if (Relax(k, new_vert, edge)) {
                    queues[k + 1].push(edge.to_);
                    is_change = true;
                }
            }
        }
        if (!is_change) {
            break;
        }
    }
}
void Graph::PrintMinDist() {
    BellmanFord();
    int64_t min_weight = k_max_weight_;
    for (int64_t i = 0; i <= quantity_edges_in_path_; ++i) {
        if (dist_[i][end_vertex_] < min_weight) {
            min_weight = dist_[i][end_vertex_];
        }
    }
    if (min_weight == k_max_weight_) {
        min_weight = -1;
    }
    std::cout << min_weight;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    int64_t quantity_edges_in_path = 0;
    int64_t begin_vert = 0;
    int64_t end_vert = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    std::cin >> quantity_edges_in_path >> begin_vert >> end_vert;
    Graph graph(quantity_vertexes, quantity_edges_in_path, begin_vert - 1, end_vert - 1);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight;
        graph.PushEdge(first_vert - 1, second_vert - 1, weight);
    }
    graph.PrintMinDist();
    return 0;
}