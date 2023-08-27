#include <algorithm>
#include <iostream>
#include <vector>

class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        edges_transpos_.resize(quantity_vert_ + 1);
        colors_.resize(quantity_vert_ + 1, 0);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
    }

    void SortNumComponents() {
        for (int64_t i = 0; i < quantity_components_; ++i) {
            int64_t size_components = components_[i].size();
            for (int64_t j = 0; j < size_components; ++j) {
                colors_[components_[i][j]] = i + 1;
            }
        }
    }
    void PrintSSC() {
        SCC();
        std::cout << quantity_components_ << '\n';
        SortNumComponents();
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            std::cout << colors_[i] << ' ';
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    std::vector<int64_t> top_sorted_;
    std::vector<int64_t> colors_;
    std::vector<std::vector<int64_t>> edges_transpos_;
    std::vector<std::vector<int64_t>> components_;
    int64_t quantity_vert_;
    int64_t quantity_components_ = 0;

    void DfsVisit(int64_t begin_vertex) {
        colors_[begin_vertex] = 1;
        for (auto neighbor : edges_transpos_[begin_vertex]) {
            if (colors_[neighbor] == 0) {
                DfsVisit(neighbor);
            }
        }
        colors_[begin_vertex] = 2;
        components_[quantity_components_].push_back(begin_vertex);
    }
    void SCC() {
        TopSortNoCycles();
        TranspositionGraf();
        DFS();
    }
    void DFS() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            colors_[i] = 0;
        }
        for (int64_t i = 0; i < quantity_vert_; ++i) {
            if (colors_[top_sorted_[i]] == 0) {
                components_.emplace_back();
                DfsVisit(top_sorted_[i]);
                quantity_components_++;
            }
        }
    }
    void TranspositionGraf() {
        int64_t old_vert = 0;
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            while (!edges_[i].empty()) {
                old_vert = edges_[i][0];
                edges_transpos_[old_vert].emplace_back(i);
                edges_[i].erase(edges_[i].begin());
            }
            edges_[i].reserve(0);
        }
    }
    void TopSortNoCycles() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (colors_[i] == 0) {
                TopSortDFS(i);
            }
        }
        std::reverse(top_sorted_.begin(), top_sorted_.end());
    }
    void TopSortDFS(int64_t begin_vertex) {
        colors_[begin_vertex] = 1;
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == 0) {
                TopSortDFS(neighbor);
            }
        }
        colors_[begin_vertex] = 2;
        top_sorted_.emplace_back(begin_vertex);
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
    graph.PrintSSC();
    return 0;
}
