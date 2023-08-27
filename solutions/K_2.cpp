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
        edges_[second_vert].push_back(first_vert);
    }
    void PrintComponenets() {
        DFS();
        std::cout << graph_components_ << '\n';
        int64_t size = graph_components_;
        for (int64_t i = 0; i < size; ++i) {
            int64_t component_size = component_vert_[i].size();
            std::cout << component_size << '\n';
            for (int64_t j = 0; j < component_size; ++j) {
                std::cout << component_vert_[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    std::vector<std::vector<int64_t>> component_vert_;
    int64_t quantity_vert_;
    std::vector<int64_t> colors_;
    std::vector<int64_t> parent_;
    int64_t graph_components_ = 0;

    void DFS() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (colors_[i] == 0) {
                DfsVisit(i);
                ++graph_components_;
            }
        }
    }
    void DfsVisit(int64_t begin_vertex) {
        colors_[begin_vertex] = 1;
        component_vert_.emplace_back();
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == 0) {

                DfsVisit(neighbor);
            }
        }
        colors_[begin_vertex] = 2;
        component_vert_[graph_components_].emplace_back(begin_vertex);
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
    graph.PrintComponenets();
    return 0;
}
