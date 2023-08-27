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
    }

    void PrintSortedGraph() {
        TopSort();
        if (!is_correct_) {
            std::cout << -1;
            return;
        }
        for (int64_t i = quantity_vert_ - 1; i >= 0; --i) {
            std::cout << top_sorted_[i] << ' ';
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    std::vector<int64_t> top_sorted_;
    std::vector<int64_t> colors_;
    int64_t quantity_vert_;
    int64_t is_correct_ = true;

    void TopSort() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (colors_[i] == Colors::WHITE) {
                if (!TopSortDFS(i)) {
                    is_correct_ = false;
                    break;
                }
            }
        }
    }
    bool TopSortDFS(int64_t begin_vertex) {
        colors_[begin_vertex] = Colors::GRAY;
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == Colors::GRAY) {
                return false;
            }
            if (colors_[neighbor] == Colors::WHITE) {
                if (!TopSortDFS(neighbor)) {
                    return false;
                }
            }
        }
        colors_[begin_vertex] = Colors::BLACK;
        top_sorted_.emplace_back(begin_vertex);
        return true;
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
    graph.PrintSortedGraph();
    return 0;
}
