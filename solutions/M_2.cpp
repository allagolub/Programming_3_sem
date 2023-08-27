#include <iostream>
#include <vector>

class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        colors_.resize(quantity_vert_ + 1, 0);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
    }
    void ResultCycle() {
        if (GraphHasCycle()) {
            std::cout << "NO" << '\n';
        } else {
            std::cout << "YES";
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> colors_;
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
    bool HasCycle(int64_t begin_vertex) {
        colors_[begin_vertex] = 1;
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == 1) {
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
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_vertexes;
    Graph graph(quantity_vertexes);
    std::string colors;
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    for (int64_t i = 0; i < quantity_vertexes - 1; ++i) {
        std::cin >> colors;
        int64_t str_size = colors.size();
        first_vert = i + 1;
        for (int64_t j = 0; j < str_size; ++j) {
            second_vert = first_vert + j + 1;
            if (colors[j] == 'R') {
                graph.PushEdge(first_vert, second_vert);
            } else {
                graph.PushEdge(second_vert, first_vert);
            }
        }
    }
    graph.ResultCycle();
    return 0;
}
