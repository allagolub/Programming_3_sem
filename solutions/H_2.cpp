#include <iostream>
#include <vector>
#include <queue>
struct Node {
    int64_t vert;
    int64_t cost;
    Node() = default;
    Node(int64_t new_vert, int64_t new_cost) : vert(new_vert), cost(new_cost) {
    }
};
class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        dist_.resize(quantity_vert_ + 1, -1);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].emplace_back(Node(second_vert, 0));
        edges_[second_vert].emplace_back(Node(first_vert, 1));
    }
    void PrintShortestPath(int64_t begin_vertex, int64_t end_vertex) {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            dist_[i] = -1;
        }
        BFS(begin_vertex);
        if (dist_[end_vertex] == -1) {
            std::cout << -1 << '\n';
            return;
        }
        if (begin_vertex == end_vertex) {
            std::cout << 0 << '\n';
            return;
        }
        std::cout << dist_[end_vertex] << '\n';
    }

private:
    std::vector<std::vector<Node>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> dist_;
    void BFS(int64_t begin_vertex) {
        std::queue<int> queue;
        queue.push(begin_vertex);
        dist_[begin_vertex] = 0;
        int64_t new_vertex = 0;
        while (!queue.empty()) {
            new_vertex = queue.front();
            queue.pop();
            for (auto neighbor : edges_[new_vertex]) {
                if ((dist_[neighbor.vert] == -1) || (dist_[neighbor.vert] > dist_[new_vertex] + neighbor.cost)) {
                    dist_[neighbor.vert] = dist_[new_vertex] + neighbor.cost;
                    queue.push(neighbor.vert);
                }
            }
        }
    }
};

int main() {
    int64_t quantity_edges = 0;
    int64_t quantity_vertexes = 0;
    int64_t begin_vertex = 0;
    int64_t end_vertex = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert;
        graph.PushEdge(first_vert, second_vert);
    }
    int64_t quantity_requests = 0;
    std::cin >> quantity_requests;

    for (int64_t i = 0; i < quantity_requests; ++i) {
        std::cin >> begin_vertex >> end_vertex;
        graph.PrintShortestPath(begin_vertex, end_vertex);
    }

    return 0;
}
