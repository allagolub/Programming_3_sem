#include <iostream>
#include <vector>
#include <queue>
struct Edge {
    int64_t vertex_;
    int64_t weight_;
    Edge(const int64_t& vertex, const int64_t& weight) : vertex_(vertex), weight_(weight) {
    }
    Edge() = default;
};
class Graph {
public:
    Graph(const int64_t new_quantity_vert, const int64_t new_begin_vertex, const int64_t new_end_vertex)
            : quantity_vert_(new_quantity_vert), begin_vertex_(new_begin_vertex), end_vertex_(new_end_vertex) {
        edges_.resize(quantity_vert_ + 1);
        dist_.resize(quantity_vert_ + 1, -1);
        queues_.resize(max_weight_);
        used_.resize(quantity_vert_, false);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
        edges_[first_vert].emplace_back(Edge(second_vert, weight));
    }
    void PrintShortestPath() {
        BFS();
        if ((dist_[end_vertex_] == -1) && (begin_vertex_ != end_vertex_)) {
            std::cout << -1 << '\n';
            return;
        }
        if (begin_vertex_ == end_vertex_) {
            std::cout << 0 << '\n';
            return;
        }
        std::cout << dist_[end_vertex_] << '\n';
    }

private:
    std::vector<std::vector<Edge>> edges_;
    std::vector<std::queue<int64_t>> queues_;
    int64_t quantity_vert_;
    int64_t begin_vertex_;
    int64_t end_vertex_;
    std::vector<int64_t> dist_;
    std::vector<bool> used_;
    const int64_t max_weight_ = 31;
    int64_t quantity_vert_in_queues_ = 0;
    void BFS() {
        queues_[0].push(begin_vertex_);
        dist_[begin_vertex_] = 0;
        int64_t new_vertex = 0;
        quantity_vert_in_queues_++;
        for (int64_t i = 0; quantity_vert_in_queues_ > 0; i = (i + 1) % max_weight_) {
            while (!queues_[i].empty()) {
                new_vertex = queues_[i].front();
                quantity_vert_in_queues_--;
                queues_[i].pop();
                if (used_[new_vertex]) {
                    continue;
                }
                used_[new_vertex] = true;
                for (auto neighbor : edges_[new_vertex]) {
                    if ((dist_[neighbor.vertex_] == -1) || ((dist_[neighbor.vertex_] > dist_[new_vertex] + neighbor.weight_))) {
                        dist_[neighbor.vertex_] = dist_[new_vertex] + neighbor.weight_;
                        queues_[dist_[neighbor.vertex_] % max_weight_].push(neighbor.vertex_);
                        quantity_vert_in_queues_++;
                    }
                }
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_edges = 0;
    int64_t quantity_vertexes = 0;
    int64_t begin_vertex = 0;
    int64_t end_vertex = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    std::cin >> begin_vertex >> end_vertex;
    Graph graph(quantity_vertexes, begin_vertex, end_vertex);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight;
        graph.PushEdge(first_vert, second_vert, weight);
    }
    graph.PrintShortestPath();
    return 0;
}
