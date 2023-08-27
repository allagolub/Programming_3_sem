#include <iostream>
#include <set>
#include <vector>

class Graph {
public:
    explicit Graph(const int64_t new_quantity_vert) : quantity_vert_(new_quantity_vert) {
        edges_.resize(quantity_vert_ + 1);
        colors_.resize(quantity_vert_ + 1, 0);
        time_in_.resize(quantity_vert_ + 1, -1);
        time_up_.resize(quantity_vert_ + 1, -1);
        quantity_children_.resize(quantity_vert_ + 1, 0);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert) {
        edges_[first_vert].push_back(second_vert);
        edges_[second_vert].push_back(first_vert);
    }
    void PrintComponents() {
        DFS();
        int64_t size_articulation_points = articulation_points_.size();
        std::cout << size_articulation_points << '\n';
        for (auto it : articulation_points_) {
            std::cout << it << '\n';
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_;
    std::vector<int64_t> colors_;
    std::vector<int64_t> parent_;
    std::vector<int64_t> time_in_;
    std::vector<int64_t> time_up_;
    std::set<int64_t> articulation_points_;
    int64_t graph_components_ = 0;
    int64_t time_ = 0;
    std::vector<int64_t> quantity_children_;
    void DFS() {
        for (int64_t i = 1; i <= quantity_vert_; ++i) {
            if (colors_[i] == 0) {
                DfsVisit(i, true);
                ++graph_components_;
            }
        }
    }
    void DfsVisit(int64_t begin_vertex, bool is_root) {
        colors_[begin_vertex] = 1;
        time_in_[begin_vertex] = time_;
        time_up_[begin_vertex] = time_;
        time_++;
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor] == 1) {
                time_up_[begin_vertex] = std::min(time_up_[begin_vertex], time_in_[neighbor]);
            }
            if (colors_[neighbor] == 0) {
                quantity_children_[begin_vertex]++;
                DfsVisit(neighbor, false);
                time_up_[begin_vertex] = std::min(time_up_[begin_vertex], time_up_[neighbor]);
                if ((!is_root) && (time_in_[begin_vertex] <= time_up_[neighbor])) {
                    articulation_points_.insert(begin_vertex);
                }
            }
        }
        if ((is_root) && (quantity_children_[begin_vertex] > 1)) {
            articulation_points_.insert(begin_vertex);
        }
        colors_[begin_vertex] = 2;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    for (int64_t i = 1; i <= quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert;
        graph.PushEdge(first_vert, second_vert);
    }
    graph.PrintComponents();
    return 0;
}
