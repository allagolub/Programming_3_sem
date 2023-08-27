#include <functional>
#include <iostream>
#include <set>
#include <vector>
struct Edge {
    int64_t vertex_;
    int64_t weight_;
    Edge(const int64_t& vertex, const int64_t& weight) : vertex_(vertex), weight_(weight) {
    }
    Edge() = default;
    friend bool operator<(const Edge& first, const Edge& second) {
        return ((first.weight_ < second.weight_) ||
                ((first.weight_ == second.weight_) && (first.vertex_ < second.vertex_)));
    }
};
class Graph {
public:
    explicit Graph(const int64_t& new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_);
        dist_.resize(quantity_vert_, k_max_dist_);
        prev_.resize(quantity_vert_, -1);
        used_.resize(quantity_vert_, false);
    }
    void PrintMinDist(int64_t begin_vertex, int64_t end_vertex);
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight);

private:
    const int64_t k_max_dist_ = 2009000999;
    std::vector<std::vector<Edge>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> dist_;
    std::vector<int64_t> prev_;
    std::vector<bool> used_;
    void Dijkstra(int64_t begin_vertex);
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    if (first_vert == second_vert) {
        return;
    }
    edges_[first_vert].emplace_back(Edge(second_vert, weight));
}
void Graph::Dijkstra(int64_t begin_vertex) {
    std::vector<int64_t> array_vertexes;
    dist_[begin_vertex] = 0;
    int64_t size = array_vertexes.size();
    while (size != quantity_vert_) {
        int64_t min_dist = k_max_dist_ + 1;
        int64_t min_dist_vert = -1;
        for (int64_t j = 0; j < quantity_vert_; ++j) {
            if ((!used_[j]) && (dist_[j] < min_dist)) {
                min_dist = dist_[j];
                min_dist_vert = j;
            }
        }
        array_vertexes.emplace_back(min_dist_vert);
        for (auto& edge : edges_[min_dist_vert]) {
            if ((!used_[edge.vertex_]) && (edge.weight_ + dist_[min_dist_vert] < dist_[edge.vertex_])) {
                prev_[edge.vertex_] = min_dist_vert;
                dist_[edge.vertex_] = edge.weight_ + dist_[min_dist_vert];
            }
        }
        used_[min_dist_vert] = true;
        size = array_vertexes.size();
    }
}
void Graph::PrintMinDist(int64_t begin_vertex, int64_t end_vertex) {
    Dijkstra(begin_vertex);
    if (dist_[end_vertex] == k_max_dist_) {
        dist_[end_vertex] = -1;
    }
    std::cout << dist_[end_vertex];
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t begin_vert = 0;
    int64_t end_vert = 0;
    int64_t weight = 0;
    std::cin >> quantity_vertexes >> begin_vert >> end_vert;
    Graph graph(quantity_vertexes);
    for (int64_t j = 0; j < quantity_vertexes; ++j) {
        for (int64_t i = 0; i < quantity_vertexes; ++i) {
            std::cin >> weight;
            if (-1 == weight) {
                continue;
            }
            graph.PushEdge(j, i, weight);
        }
    }
    graph.PrintMinDist(begin_vert - 1, end_vert - 1);
    std::cout << '\n';
    return 0;
}
