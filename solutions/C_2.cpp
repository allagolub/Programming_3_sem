#include <iostream>
#include <vector>
#include <queue>
struct Coord {
    int64_t x_;
    int64_t y_;
    Coord(int64_t coord_x, int64_t coord_y) : x_(coord_x), y_(coord_y) {
    }
    Coord() = default;
    friend bool operator==(const Coord& first, const Coord& second) {
        return ((first.x_ == second.x_) && (first.y_ == second.y_));
    }
};
class Graph {
public:
    Graph(const int64_t& size, const int64_t& begin_coord_x, const int64_t& begin_coord_y, const int64_t& end_coord_x,
          const int64_t& end_coord_y)
            : size_(size), begin_coord_(begin_coord_x, begin_coord_y), end_coord_(end_coord_x, end_coord_y) {
        edges_.resize(size + 1);
        for (int64_t i = 0; i < size + 1; ++i) {
            edges_[i].resize(size + 1);
        }
        dist_.resize(size + 1);
        for (int64_t i = 0; i < size + 1; ++i) {
            dist_[i].resize(size + 1, -1);
        }
        parent_.resize(size_ + 1);
        for (int64_t i = 0; i < size + 1; ++i) {
            parent_[i].resize(size + 1);
        }
    }
    void NewCoord(const Coord& first_coord, const int64_t& first_shift, const int64_t& second_shift) {
        Coord new_coord(first_coord.x_ + first_shift, first_coord.y_ + second_shift);
        if ((new_coord.x_ > 0) && (new_coord.y_ > 0) && (new_coord.x_ < size_ + 1) && (new_coord.y_ < size_ + 1)) {
            edges_[first_coord.x_][first_coord.y_].push_back(new_coord);
            is_find_coord_ |= (new_coord == end_coord_);
        }
    }
    bool PushEdge(Coord first_coord) {
        NewCoord(first_coord, -2, 1);
        NewCoord(first_coord, -2, -1);
        NewCoord(first_coord, 2, 1);
        NewCoord(first_coord, 2, -1);
        NewCoord(first_coord, -1, 2);
        NewCoord(first_coord, -1, -2);
        NewCoord(first_coord, 1, -2);
        NewCoord(first_coord, 1, 2);
        return is_find_coord_;
    }
    void PrintShortestPath() {
        if (begin_coord_ == end_coord_) {
            std::cout << 1 << '\n';
            std::cout << begin_coord_.x_ << ' ' << begin_coord_.y_;
            return;
        }
        BFS();
        if ((dist_[end_coord_.x_][end_coord_.y_] == -1) && !(begin_coord_ == end_coord_)) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << dist_[end_coord_.x_][end_coord_.y_] << '\n';
        std::vector<Coord> result_path;
        result_path.push_back(end_coord_);
        for (Coord i = parent_[end_coord_.x_][end_coord_.y_]; !(i == begin_coord_); i = parent_[i.x_][i.y_]) {
            result_path.push_back(i);
        }
        result_path.push_back(begin_coord_);
        for (int64_t i = result_path.size() - 1; i >= 0; --i) {
            std::cout << result_path[i].x_ << ' ' << result_path[i].y_ << '\n';
        }
    }

private:
    std::vector<std::vector<std::vector<Coord>>> edges_;
    bool is_find_coord_ = false;
    int64_t size_;
    Coord begin_coord_;
    Coord end_coord_;
    std::vector<std::vector<int64_t>> dist_;
    std::vector<std::vector<Coord>> parent_;
    void BFS() {
        std::queue<Coord> queue;
        queue.push(begin_coord_);
        dist_[begin_coord_.x_][begin_coord_.y_] = 0;
        Coord new_vertex;
        bool is_find_end_num = false;
        while (!is_find_end_num) {
            new_vertex = queue.front();
            queue.pop();
            is_find_end_num = PushEdge(new_vertex);
            for (auto neighbor : edges_[new_vertex.x_][new_vertex.y_]) {
                if (dist_[neighbor.x_][neighbor.y_] == -1) {
                    dist_[neighbor.x_][neighbor.y_] = dist_[new_vertex.x_][new_vertex.y_] + 1;
                    parent_[neighbor.x_][neighbor.y_] = new_vertex;
                    queue.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int64_t size = 0;
    int64_t begin_coord_x = 0;
    int64_t end_coord_x = 0;
    int64_t begin_coord_y = 0;
    int64_t end_coord_y = 0;
    std::cin >> size >> begin_coord_x >> begin_coord_y >> end_coord_x >> end_coord_y;
    Graph graph(size, begin_coord_x, begin_coord_y, end_coord_x, end_coord_y);
    graph.PrintShortestPath();
    return 0;
}
