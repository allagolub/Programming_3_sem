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
        edges_.resize(quantity_vert_ + 1);
        dist_.resize(quantity_vert_ + 1, k_max_dist_);
        prev_.resize(quantity_vert_ + 1, -1);
        used_.resize(quantity_vert_ + 1, false);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight);
    int64_t Prim();

private:
    const int64_t k_max_dist_ = 10000000;
    std::vector<std::vector<Edge>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> dist_;
    std::vector<int64_t> prev_;
    std::vector<bool> used_;
};
void Graph::PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
    edges_[first_vert].emplace_back(Edge(second_vert, weight));
    edges_[second_vert].emplace_back(Edge(first_vert, weight));
}
int64_t Graph::Prim() {
    int64_t weight_mst = 0;
    std::set<Edge> set_vertexes;
    dist_[1] = 0;
    for (int64_t i = 1; i <= quantity_vert_; ++i) {
        set_vertexes.insert(Edge(i, dist_[i]));
    }
    while (!set_vertexes.empty()) {
        auto new_vertex = *set_vertexes.begin();
        set_vertexes.erase(set_vertexes.begin());
        used_[new_vertex.vertex_] = true;
        if (prev_[new_vertex.vertex_] != -1) {
            weight_mst += new_vertex.weight_;
        }
        for (auto& edge : edges_[new_vertex.vertex_]) {
            if ((!used_[edge.vertex_]) && (edge.weight_ < dist_[edge.vertex_])) {
                set_vertexes.erase(Edge(edge.vertex_, dist_[edge.vertex_]));
                set_vertexes.insert(Edge(edge.vertex_, edge.weight_));
                prev_[edge.vertex_] = new_vertex.vertex_;
                dist_[edge.vertex_] = edge.weight_;
            }
        }
    }
    return weight_mst;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    for (int64_t i = 1; i <= quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight;
        graph.PushEdge(first_vert, second_vert, weight);
    }
    int64_t min_weight = graph.Prim();
    std::cout << min_weight;
    return 0;
}
