#include <iostream>
#include <vector>
enum Colors { WHITE, GRAY, BLACK };
class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        colors_.resize(quantity_vert_ + 1, Colors::WHITE);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
        edges_[second_vert].push_back(first_vert);
    }
    void PrintComponenets() {
        DFS();
        std::cout << graf_components_ << '\n';
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> colors_;
    std::vector<int64_t> parent_;
    int64_t graf_components_ = 0;

    void DFS() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (colors_[i] == Colors::WHITE) {
                DfsVisit(i);
                ++graf_components_;
            }
        }
    }
    void DfsVisit(int64_t begin_vertex) {
        colors_[begin_vertex] = Colors::GRAY;
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == Colors::WHITE) {
                DfsVisit(neighbor);
            }
        }
        colors_[begin_vertex] = Colors::BLACK;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_vertexes;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    for (int64_t i = 1; i <= quantity_vertexes; ++i) {
        std::cin >> first_vert;
        graph.PushEdge(first_vert, i);
    }
    graph.PrintComponenets();
    return 0;
}
