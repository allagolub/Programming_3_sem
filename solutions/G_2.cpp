#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    Graph(const int64_t new_quantity_vert, const int64_t new_begin_vertex, const int64_t new_end_vertex)
            : quantity_vert_(new_quantity_vert), begin_vertex_(new_begin_vertex), end_vertex_(new_end_vertex) {
        edges_.resize(quantity_vert_ + 1);
        dist_.resize(quantity_vert_ + 1);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
        if (weight == 1) {
            edges_[first_vert].push_back(second_vert);
            return;
        }
        int64_t old_size = edges_.size();
        int64_t new_size = old_size + weight - 1;
        edges_.resize(new_size);
        dist_.resize(new_size, 0);
        edges_[first_vert].push_back(old_size);
        quantity_vert_ += weight - 1;
        for (int64_t i = old_size; i < new_size - 1; ++i) {
            edges_[i].push_back(i + 1);
        }
        edges_[new_size - 1].push_back(second_vert);
    }
    void PrintShortestPath() {
        BFS();
        if (begin_vertex_ == end_vertex_) {
            std::cout << 0 << '\n';
            return;
        }
        if ((dist_[end_vertex_] == 0) && (begin_vertex_ != end_vertex_)) {
            std::cout << -1 << '\n';
            return;
        }
        std::cout << dist_[end_vertex_] << '\n';
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    int64_t begin_vertex_;
    int64_t end_vertex_;
    std::vector<int64_t> dist_;
    void BFS() {
        std::queue<int64_t> queue;
        queue.push(begin_vertex_);
        dist_[begin_vertex_] = 0;
        int64_t new_vertex = 0;
        while (!queue.empty()) {
            new_vertex = queue.front();
            queue.pop();
            for (auto neighbor : edges_[new_vertex]) {
                if (dist_[neighbor] == 0) {
                    dist_[neighbor] = dist_[new_vertex] + 1;
                    queue.push(neighbor);
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
