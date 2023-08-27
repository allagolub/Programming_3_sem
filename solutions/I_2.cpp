#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        colors_.resize(quantity_vert_ + 1, 0);
        parent_.resize(quantity_vert_ + 1);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
    }
    void ResultCycle() {
        if (GraphHasCycle()) {
            std::cout << "YES" << '\n';
            PrintCycle();
        } else {
            std::cout << "NO";
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> colors_;
    std::vector<int64_t> parent_;
    int64_t vert_cycle_ = 0;
    bool GraphHasCycle() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (colors_[i] == 0) {
                if (HasCycle(i)) {
                    return true;
                }
            }
        }
        return false;
    }
    void PrintCycle() {
        std::vector<int64_t> cycle;
        cycle.emplace_back(vert_cycle_);
        for (int64_t i = parent_[vert_cycle_]; i != vert_cycle_; i = parent_[i]) {
            cycle.emplace_back(i);
        }
        int64_t size = cycle.size();
        for (int64_t i = size - 1; i >= 0; --i) {
            std::cout << cycle[i] << ' ';
        }
    }
    bool HasCycle(int64_t begin_vertex) {
        colors_[begin_vertex] = 1;
        for (auto neighbor : edges_[begin_vertex]) {
            parent_[neighbor] = begin_vertex;
            if (colors_[neighbor] == 1) {
                vert_cycle_ = neighbor;
                return true;
            }
            if (colors_[neighbor] == 0) {
                if (HasCycle(neighbor)) {
                    return true;
                }
            }
        }
        colors_[begin_vertex] = 2;
        return false;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
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
    graph.ResultCycle();
    return 0;
}
