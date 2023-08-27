#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
struct Edge {
    int64_t vertex_;
    int64_t weight_;
    Edge(const int64_t& vertex, const int64_t& weight) : vertex_(vertex), weight_(weight) {
    }
    Edge() = default;
    friend bool operator<(const Edge& first, const Edge& second) {
        return ((first.weight_ > second.weight_) ||
                ((first.weight_ == second.weight_) && (first.vertex_ > second.vertex_)));
    }
};
class Graph {
public:
    explicit Graph(const int64_t& new_quantity_vert, int64_t quantity_edges)
            : quantity_vert_(new_quantity_vert), quantity_edges_(quantity_edges) {
        edges_.resize(quantity_vert_);
        dist_.resize(quantity_vert_, k_max_dist_);
        prev_.resize(quantity_vert_, -1);
    }
    void PrintMinDist(const int64_t& begin_vertex, const int64_t& end_vertex, const std::vector<int64_t>& infections);
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight);

private:
    const int64_t k_max_dist_ = std::numeric_limits<int64_t>::max();
    std::vector<std::vector<Edge>> edges_;
    int64_t quantity_vert_;
    int64_t quantity_edges_;
    std::vector<int64_t> dist_;
    std::vector<int64_t> prev_;
    void Dijkstra(int64_t begin_vertex);
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    edges_[first_vert].emplace_back(Edge(second_vert, weight));
    edges_[second_vert].emplace_back(Edge(first_vert, weight));
}
void Graph::Dijkstra(int64_t begin_vertex) {
    std::priority_queue<Edge> queue_vertexes;
    dist_[begin_vertex] = 0;
    queue_vertexes.push(Edge(begin_vertex, dist_[begin_vertex]));
    while (!queue_vertexes.empty()) {
        auto new_vertex = queue_vertexes.top();
        queue_vertexes.pop();
        if (new_vertex.weight_ > dist_[new_vertex.vertex_]) {
            continue;
        }
        for (auto& edge : edges_[new_vertex.vertex_]) {
            if (edge.weight_ + dist_[new_vertex.vertex_] < dist_[edge.vertex_]) {
                queue_vertexes.push(Edge(edge.vertex_, edge.weight_ + dist_[new_vertex.vertex_]));
                prev_[edge.vertex_] = new_vertex.vertex_;
                dist_[edge.vertex_] = edge.weight_ + dist_[new_vertex.vertex_];
            }
        }
    }
}
void Graph::PrintMinDist(const int64_t& begin_vertex, const int64_t& end_vertex,
                         const std::vector<int64_t>& infections) {
    Dijkstra(end_vertex);
    int64_t min_dist = dist_[begin_vertex];
    int64_t size = infections.size();
    for (int64_t i = 0; i < size; ++i) {
        if (dist_[infections[i]] <= min_dist) {
            dist_[begin_vertex] = -1;
            break;
        }
    }
    std::cout << dist_[begin_vertex];
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    int64_t quantity_infections = 0;
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    std::cin >> quantity_infections;
    std::vector<int64_t> infections;
    int64_t city = 0;
    for (int64_t i = 0; i < quantity_infections; ++i) {
        std::cin >> city;
        infections.emplace_back(city - 1);
    }
    Graph graph(quantity_vertexes, quantity_edges);
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight;
        graph.PushEdge(first_vert - 1, second_vert - 1, weight);
    }
    int64_t begin_vertex = 0;
    int64_t end_vertex = 0;
    std::cin >> begin_vertex >> end_vertex;
    graph.PrintMinDist(begin_vertex - 1, end_vertex - 1, infections);
    std::cout << '\n';
    return 0;
}
