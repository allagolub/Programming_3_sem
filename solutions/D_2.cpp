#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
    Graph(const int64_t new_begin_vertex, const int64_t new_end_vertex)
            : begin_vertex_(new_begin_vertex), end_vertex_(new_end_vertex) {
        edges_.resize(quantity_vert_ + 1);
        dist_.resize(quantity_vert_ + 1, -1);
        parent_.resize(quantity_vert_ + 1);
    }
    bool PushEdge(int64_t first_vert) {
        bool is_find_num = false;
        int64_t new_num = first_vert + 1000;
        if ((first_vert / 1000) != 9) {
            edges_[first_vert].push_back(new_num);
            is_find_num |= (new_num == end_vertex_);
        }
        new_num = first_vert - 1;
        if (first_vert % 10 != 1) {
            edges_[first_vert].push_back(new_num);
            is_find_num |= (new_num == end_vertex_);
        }
        new_num = first_vert / 10 + (first_vert % 10) * 1000;
        edges_[first_vert].push_back(new_num);
        is_find_num |= (new_num == end_vertex_);
        new_num = first_vert % 1000 * 10 + first_vert / 1000;
        edges_[first_vert].push_back(new_num);
        is_find_num |= (new_num == end_vertex_);
        return is_find_num;
    }
    void PrintShortestPath() {
        BFS();
        if ((dist_[end_vertex_] == -1) && (begin_vertex_ != end_vertex_)) {
            std::cout << -1 << '\n';
            return;
        }
        if (begin_vertex_ == end_vertex_) {
            std::cout << 1 << '\n';
            std::cout << begin_vertex_;
            return;
        }
        std::cout << dist_[end_vertex_] + 1 << '\n';
        std::vector<int64_t> result_path;
        result_path.push_back(end_vertex_);
        for (int64_t i = parent_[end_vertex_]; i != begin_vertex_; i = parent_[i]) {
            result_path.push_back(i);
        }
        result_path.push_back(begin_vertex_);
        for (int64_t i = result_path.size() - 1; i >= 0; --i) {
            std::cout << result_path[i] << '\n';
        }
    }

private:
    std::vector<std::vector<int64_t>> edges_;
    int64_t quantity_vert_ = 9999;
    int64_t begin_vertex_;
    int64_t end_vertex_;
    std::vector<int64_t> dist_;
    std::vector<int64_t> parent_;
    void BFS() {
        std::queue<int64_t> queue;
        queue.push(begin_vertex_);
        dist_[begin_vertex_] = 0;
        int64_t new_vertex = 0;
        bool is_find_end_num = false;
        while (!is_find_end_num) {
            new_vertex = queue.front();
            queue.pop();
            is_find_end_num = PushEdge(new_vertex);
            for (auto neighbor : edges_[new_vertex]) {
                if (dist_[neighbor] == -1) {
                    dist_[neighbor] = dist_[new_vertex] + 1;
                    parent_[neighbor] = new_vertex;
                    queue.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int64_t begin_vertex = 0;
    int64_t end_vertex = 0;
    std::cin >> begin_vertex >> end_vertex;
    Graph graph(begin_vertex, end_vertex);
    graph.PrintShortestPath();
    return 0;
}
