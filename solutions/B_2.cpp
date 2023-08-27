#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        dist_.resize(quantity_vert_ + 1, -1);
        parent_.resize(quantity_vert_ + 1);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
        edges_[second_vert].push_back(first_vert);
    }
    void ResultPaint() {
        if (GraphBFS()) {
            std::cout << "YES";
        } else {
            std::cout << "NO";
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> dist_;
    std::vector<int64_t> parent_;
    bool GraphBFS() {
        bool is_correct = true;
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (dist_[i] == -1) {
                is_correct = BFS(i);
                if (!(is_correct)) {
                    return false;
                }
            }
        }
        return true;
    }
    bool BFS(int64_t begin_vertex) {
        std::queue<int64_t> queue;
        queue.push(begin_vertex);
        dist_[begin_vertex] = 0;
        int64_t new_vertex = 0;
        while (!queue.empty()) {
            new_vertex = queue.front();
            queue.pop();
            for (auto neighbor : edges_[new_vertex]) {
                if (dist_[neighbor] == -1) {
                    dist_[neighbor] = (dist_[new_vertex] + 1) % 2;
                    parent_[neighbor] = new_vertex;
                    queue.push(neighbor);
                } else if ((dist_[neighbor] != -1) && (dist_[neighbor] == dist_[new_vertex])) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    int64_t quantity_edges = 0;
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert;
        graph.PushEdge(first_vert, second_vert);
    }
    graph.ResultPaint();
    return 0;
}
