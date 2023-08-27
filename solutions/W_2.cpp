#include <algorithm>
#include <iostream>
#include <vector>
enum Colors { WHITE, GRAY, BLACK };

class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert, const std::string& atoms) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        colors_.resize(quantity_vert_ + 1, Colors::WHITE);
        parent_.resize(quantity_vert_ + 1);
        atoms_ = atoms;
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
        edges_[second_vert].push_back(first_vert);
    }
    bool NotFindVertex(int64_t begin_vert, int64_t end_vertex) {
        return (edges_[begin_vert].end() == std::find(edges_[begin_vert].begin(), edges_[begin_vert].end(), end_vertex));
    }
    void PrintIsCorrectConnections() {
        if (!CorrectConnections()) {
            std::cout << "NO" << '\n';
            return;
        }
        DFS();
        if ((graph_components_ == 1) && (!has_cycle_)) {
            std::cout << "YES" << '\n';
        } else {
            std::cout << "NO" << '\n';
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    std::string atoms_;
    std::vector<int64_t> colors_;
    std::vector<int64_t> parent_;
    int64_t graph_components_ = 0;
    int64_t has_cycle_ = false;
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
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == Colors::WHITE) {
                parent_[neighbor] = begin_vertex;
                DfsVisit(neighbor);
            } else if ((colors_[neighbor] == Colors::GRAY) && (parent_[begin_vertex] != neighbor)) {
                has_cycle_ = true;
            }
        }
        colors_[begin_vertex] = Colors::GRAY;
    }
    bool CorrectConnections() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if ((atoms_[i - 1] == 'C') && (edges_[i].size() != 4)) {
                return false;
            }
            if ((atoms_[i - 1] == 'H') && (edges_[i].size() != 1)) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    std::string atoms;
    std::cin >> quantity_vertexes >> quantity_edges;
    std::cin >> atoms;
    Graph graph(quantity_vertexes, atoms);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert;
        if (((atoms[first_vert - 1] == 'H') && (atoms[second_vert - 1] == 'H')) || (first_vert == second_vert)) {
            std::cout << "NO";
            return 0;
        }
        if (!graph.NotFindVertex(first_vert, second_vert)) {
            std::cout << "NO";
            return 0;
        }
        graph.PushEdge(first_vert, second_vert);
    }
    graph.PrintIsCorrectConnections();
}
