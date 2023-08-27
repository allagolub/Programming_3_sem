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
    Graph(const int64_t& first_size, const int64_t& second_size)
            : first_size_(first_size), second_size_(second_size), size_(first_size * second_size) {
        int64_t new_crossroad = 0;
        for (int64_t i = 0; i < first_size; ++i) {
            for (int64_t j = 0; j < second_size; ++j) {
                std::cin >> new_crossroad;
                if (new_crossroad) {
                    terminal_crossroad_.emplace_back(Coord(i + 1, j + 1));
                }
            }
        }
        cout_crossroad_ = terminal_crossroad_.size();
        dist_.resize(first_size_ + 1);
        for (int64_t i = 0; i < first_size_ + 1; ++i) {
            dist_[i].resize(second_size_ + 1, -1);
        }
    }
    void NewCoord(const Coord& first_coord, const int64_t& first_shift, const int64_t& second_shift) {
        Coord new_coord(first_coord.x_ + first_shift, first_coord.y_ + second_shift);
        if ((new_coord.x_ > 0) && (new_coord.y_ > 0) && (new_coord.x_ < first_size_ + 1) &&
            (new_coord.y_ < second_size_ + 1)) {
            edge_.emplace_back(Coord{first_coord.x_ + first_shift, first_coord.y_ + second_shift});
        }
    }
    void PushEdge(const Coord& first_coord) {
        NewCoord(first_coord, 0, 1);
        NewCoord(first_coord, 0, -1);
        NewCoord(first_coord, 1, 0);
        NewCoord(first_coord, -1, 0);
    }
    void PrintShortestPath() {
        BFS();
        for (int64_t i = 1; i < first_size_ + 1; ++i) {
            for (int64_t j = 1; j < second_size_ + 1; ++j) {
                std::cout << dist_[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    std::vector<Coord> edge_;
    int64_t first_size_;
    int64_t second_size_;
    int64_t cout_crossroad_;
    int64_t size_;
    std::vector<std::vector<int64_t>> dist_;
    std::vector<Coord> terminal_crossroad_;
    void BFS() {
        std::queue<Coord> queue;
        int64_t terminal_size = terminal_crossroad_.size();
        for (int64_t i = 0; i < terminal_size; ++i) {
            queue.push(terminal_crossroad_[i]);
            dist_[terminal_crossroad_[i].x_][terminal_crossroad_[i].y_] = 0;
        }
        Coord new_vertex;
        while (cout_crossroad_ != size_) {
            new_vertex = queue.front();
            queue.pop();
            PushEdge(new_vertex);
            for (auto neighbor : edge_) {
                if (dist_[neighbor.x_][neighbor.y_] == -1) {
                    dist_[neighbor.x_][neighbor.y_] = dist_[new_vertex.x_][new_vertex.y_] + 1;
                    ++cout_crossroad_;
                    queue.push(neighbor);
                }
            }
            edge_.resize(0);
        }
    }
};

int main() {
    int64_t first_size = 0;
    int64_t second_size = 0;
    std::cin >> first_size >> second_size;
    Graph graph(first_size, second_size);
    graph.PrintShortestPath();
    return 0;
}
