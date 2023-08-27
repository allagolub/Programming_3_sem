#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    Graph(const int64_t new_quantity_vert, const int64_t new_begin_vertex, const int64_t new_end_vertex)
            : quantity_vert_(new_quantity_vert), begin_vertex_(new_begin_vertex), end_vertex_(new_end_vertex) {
        edges_.resize(quantity_vert_ + 1);
        dist_.resize(quantity_vert_ + 1);
        parent_.resize(quantity_vert_ + 1);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
        edges_[second_vert].push_back(first_vert);
    }
    void PrintShortestPath() {
        BFS();
        if ((dist_[end_vertex_] == 0) && (begin_vertex_ != end_vertex_)) {
            std::cout << -1 << '\n';
            return;
        }
        if (begin_vertex_ == end_vertex_) {
            std::cout << 0 << '\n';
            std::cout << begin_vertex_;
            return;
        }
        std::cout << dist_[end_vertex_] << '\n';
        std::vector<int64_t> result_path;
        result_path.push_back(end_vertex_);
        for (int64_t i = parent_[end_vertex_]; i != begin_vertex_; i = parent_[i]) {
            result_path.push_back(i);
        }
        result_path.push_back(begin_vertex_);
        for (int64_t i = result_path.size() - 1; i >= 0; --i) {
            std::cout << result_path[i] << ' ';
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    int64_t begin_vertex_;
    int64_t end_vertex_;
    std::vector<int64_t> dist_;
    std::vector<int64_t> parent_;
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
                    parent_[neighbor] = new_vertex;
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
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert;
        graph.PushEdge(first_vert, second_vert);
    }
    graph.PrintShortestPath();
    return 0;
}
