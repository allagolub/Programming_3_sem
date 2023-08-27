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
    Graph(const int64_t& first_size, const int64_t& second_size, const int64_t& begin_coord_x,
          const int64_t& begin_coord_y, const int64_t& end_coord_x, const int64_t& end_coord_y)
            : first_size_(first_size)
            , second_size_(second_size)
            , begin_coord_(begin_coord_x, begin_coord_y)
            , end_coord_(end_coord_x, end_coord_y) {
        edges_.resize(first_size_ + 1);
        dist_.resize(first_size_ + 1);
        for (int64_t i = 1; i < first_size + 1; ++i) {
            edges_[i].resize(second_size + 1);
        }
        for (int64_t i = 0; i < first_size_ + 1; ++i) {
            dist_[i].resize(second_size_ + 1, -1);
        }
        size_ = first_size * second_size;
    }
    void PushEdge(int64_t first_x, int64_t first_y, int64_t second_x, int64_t second_y) {
        edges_[first_x][first_y].emplace_back(Coord(second_x, second_y));
    }
    void PrintShortestPath() {
        if (begin_coord_ == end_coord_) {
            std::cout << 1 << '\n';
            return;
        }
        BFS();
        if ((dist_[end_coord_.x_][end_coord_.y_] == -1) && !(begin_coord_ == end_coord_)) {
            std::cout << -1 << '\n';
            return;
        }

        std::cout << dist_[end_coord_.x_][end_coord_.y_] << '\n';
    }

private:
    std::vector<std::vector<std::vector<Coord>>> edges_;
    int64_t first_size_;
    int64_t second_size_;
    Coord begin_coord_;
    Coord end_coord_;
    int64_t count_cells_ = 0;
    int64_t size_;
    std::vector<std::vector<int64_t>> dist_;
    void BFS() {
        std::queue<Coord> queue;
        queue.push(begin_coord_);
        dist_[begin_coord_.x_][begin_coord_.y_] = 0;
        Coord new_vertex;
        while (!queue.empty()) {
            new_vertex = queue.front();
            queue.pop();
            for (auto neighbor : edges_[new_vertex.x_][new_vertex.y_]) {
                if (dist_[neighbor.x_][neighbor.y_] == -1) {
                    dist_[neighbor.x_][neighbor.y_] = dist_[new_vertex.x_][new_vertex.y_] + 1;
                    queue.push(neighbor);
                }
            }
        }
    }
};

int main() {
    int64_t first_size = 0;
    int64_t second_size = 0;
    int64_t begin_coord_x = 0;
    int64_t begin_coord_y = 0;
    int64_t end_coord_x = 0;
    int64_t end_coord_y = 0;
    std::vector<std::vector<char>> field;
    std::cin >> first_size >> second_size;
    field.resize(first_size + 2);
    for (int64_t i = 0; i <= first_size + 1; ++i) {
        field[i].resize(second_size + 2);
    }
    for (int64_t i = 1; i <= first_size; ++i) {
        for (int64_t j = 1; j <= second_size; ++j) {
            std::cin >> field[i][j];
            if (field[i][j] == 'S') {
                begin_coord_x = i;
                begin_coord_y = j;
            } else if (field[i][j] == 'T') {
                end_coord_x = i;
                end_coord_y = j;
            }
        }
    }
    std::fill(field[0].begin(), field[0].end(), '#');
    std::fill(field[first_size + 1].begin(), field[first_size + 1].end(), '#');
    for (int64_t i = 0; i <= first_size; ++i) {
        field[i][0] = '#';
        field[i][second_size + 1] = '#';
    }
    int64_t neighbor_i = 0;
    int64_t neighbor_j = 0;
    Graph graph(first_size, second_size, begin_coord_x, begin_coord_y, end_coord_x, end_coord_y);
    for (int64_t i = 1; i <= first_size; ++i) {
        for (int64_t j = 1; j <= second_size; ++j) {
            if (field[i][j] != '#') {
                neighbor_i = i;
                neighbor_j = j;
                while (field[neighbor_i][neighbor_j] != '#') {
                    neighbor_i++;
                }
                graph.PushEdge(i, j, (neighbor_i - i) / 2 + i, neighbor_j);
                neighbor_i = i;
                neighbor_j = j;
                while (field[neighbor_i][neighbor_j] != '#') {
                    neighbor_j++;
                }
                graph.PushEdge(i, j, neighbor_i, (neighbor_j - j) / 2 + j);
                neighbor_i = i;
                neighbor_j = j;
                while (field[neighbor_i][neighbor_j] != '#') {
                    neighbor_i--;
                }
                graph.PushEdge(i, j, i - (i - neighbor_i) / 2, neighbor_j);
                neighbor_i = i;
                neighbor_j = j;
                while (field[neighbor_i][neighbor_j] != '#') {
                    neighbor_j--;
                }
                graph.PushEdge(i, j, neighbor_i, j - (j - neighbor_j) / 2);
            }
        }
    }
    graph.PrintShortestPath();
    return 0;
}
