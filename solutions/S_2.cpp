#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        degrees_.resize(quantity_vert_ + 1);
        colors_.resize(quantity_vert_ + 1, 0);
        is_used_.resize(quantity_vert_ + 1, false);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
        is_used_[first_vert] = true;
        is_used_[second_vert] = true;
        ++degrees_[first_vert];
        --degrees_[second_vert];
    }
    void ResultCycle() {
        if (!CheckCorrectEuler()) {
            std::cout << 0;
            return;
        }
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (is_used_[i]) {
                begin_vert_ = i;
                break;
            }
        }
        DfsEulerCycle(-1, begin_vert_);
        int64_t size_new_path = euler_cycle_.size();
        std::cout << size_new_path << '\n';
        for (int64_t i = 0; i < size_new_path; ++i) {
            std::cout << euler_cycle_[i] << ' ';
        }
    }

private:
    std::vector<int64_t> colors_;
    std::vector<std::vector<int64_t>> edges_;
    std::vector<int64_t> degrees_;
    std::vector<bool> is_used_;
    int64_t quantity_vert_;
    std::vector<int64_t> euler_cycle_;
    int64_t graph_components_ = 0;
    int64_t begin_vert_ = 0;
    bool CheckCorrectEuler() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (degrees_[i] != 0) {
                return false;
            }
        }
        DFS();
        return (graph_components_ == 1);
    }
    void DFS() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if ((graph_components_ == 1) && (colors_[i] == 0) && (is_used_[i])) {
                graph_components_++;
                return;
            }
            if ((colors_[i] == 0) && (is_used_[i])) {
                DfsVisit(i);
                ++graph_components_;
            }
        }
    }
    void DfsVisit(int64_t begin_vertex) {
        colors_[begin_vertex] = 1;
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == 0) {
                DfsVisit(neighbor);
            }
        }
        colors_[begin_vertex] = 2;
    }
    void DfsEulerCycle(int64_t parent, int64_t current_vert) {
        while (!edges_[current_vert].empty()) {
            int64_t size = edges_[current_vert].size();
            if ((size != 1) && (edges_[current_vert][0] == parent)) {
                int64_t neighbor = edges_[current_vert][1];
                edges_[current_vert].erase(edges_[current_vert].begin() + 1);
                DfsEulerCycle(current_vert, neighbor);
            } else {
                int64_t neighbor = edges_[current_vert][0];
                edges_[current_vert].erase(edges_[current_vert].begin());
                DfsEulerCycle(current_vert, neighbor);
            }
        }
        euler_cycle_.emplace_back(current_vert);
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_buses = 0;
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_buses >> quantity_vertexes;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t len = 0;
    for (int64_t i = 0; i < quantity_buses; ++i) {
        std::cin >> len;
        std::cin >> first_vert;
        for (int64_t j = 0; j < len; ++j) {
            std::cin >> second_vert;
            graph.PushEdge(first_vert, second_vert);
            first_vert = second_vert;
        }
    }
    graph.ResultCycle();
    return 0;
}
