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
            : first_size_(first_size), second_size_(second_size), count_components_(0) {
        first_matrix_.resize(first_size_ + 1);
        for (int64_t i = 0; i < first_size_ + 1; ++i) {
            first_matrix_[i].resize(second_size_ + 1, -1);
        }
        second_matrix_.resize(first_size_ + 1);
        for (int64_t i = 0; i < first_size_ + 1; ++i) {
            second_matrix_[i].resize(second_size_ + 1, -1);
        }
        for (int64_t i = 1; i <= first_size; ++i) {
            for (int64_t j = 1; j <= second_size; ++j) {
                std::cin >> first_matrix_[i][j];
            }
        }
        for (int64_t i = 1; i <= first_size; ++i) {
            for (int64_t j = 1; j <= second_size; ++j) {
                if (second_matrix_[i][j] == -1) {
                    count_components_++;
                    second_matrix_[i][j] = count_components_;
                    CheckEdgeComponents(Coord(i, j));
                }
            }
        }
    }
    void PrintResultSquares() {
        CheckHeightDifferences();
        int64_t result_squares = 0;
        for (int64_t i = 1; i <= count_components_; ++i) {
            if (edges_in_components_out_[i] < 1) {
                result_squares++;
            }
        }
        std::cout << result_squares;
    }

private:
    int64_t first_size_;
    int64_t second_size_;
    int64_t count_components_;
    std::vector<int64_t> edges_in_components_out_;
    std::vector<std::vector<int64_t>> first_matrix_;
    std::vector<std::vector<int64_t>> second_matrix_;
    void NewCoordComponents(const Coord& first_coord, const int64_t& first_shift, const int64_t& second_shift) {
        Coord new_coord(first_coord.x_ + first_shift, first_coord.y_ + second_shift);
        if ((new_coord.x_ > 0) && (new_coord.y_ > 0) && (new_coord.x_ < first_size_ + 1) &&
            (new_coord.y_ < second_size_ + 1) && (second_matrix_[new_coord.x_][new_coord.y_] == -1)) {
            if ((first_matrix_[new_coord.x_][new_coord.y_] == first_matrix_[first_coord.x_][first_coord.y_]) &&
                (second_matrix_[first_coord.x_][first_coord.y_] > 0)) {
                second_matrix_[new_coord.x_][new_coord.y_] = second_matrix_[first_coord.x_][first_coord.y_];
                CheckEdgeComponents(new_coord);
            }
        }
    }
    void CheckEdgeComponents(const Coord& first_coord) {
        NewCoordComponents(first_coord, 0, 1);
        NewCoordComponents(first_coord, 0, -1);
        NewCoordComponents(first_coord, 1, 0);
        NewCoordComponents(first_coord, -1, 0);
    }
    void NewCoordOut(const Coord& first_coord, const int64_t& first_shift, const int64_t& second_shift) {
        Coord new_coord(first_coord.x_ + first_shift, first_coord.y_ + second_shift);
        if ((new_coord.x_ > 0) && (new_coord.y_ > 0) && (new_coord.x_ < first_size_ + 1) &&
            (new_coord.y_ < second_size_ + 1)) {
            if (first_matrix_[new_coord.x_][new_coord.y_] > first_matrix_[first_coord.x_][first_coord.y_]) {
                edges_in_components_out_[second_matrix_[new_coord.x_][new_coord.y_]] = 1;
            } else if (first_matrix_[new_coord.x_][new_coord.y_] < first_matrix_[first_coord.x_][first_coord.y_]) {
                edges_in_components_out_[second_matrix_[first_coord.x_][first_coord.y_]] = 1;
            }
        }
    }
    void CheckEdgeOut(const Coord& first_coord) {
        NewCoordOut(first_coord, 0, 1);
        NewCoordOut(first_coord, 0, -1);
        NewCoordOut(first_coord, 1, 0);
        NewCoordOut(first_coord, -1, 0);
    }
    void CheckHeightDifferences() {
        edges_in_components_out_.resize(count_components_ + 1);
        for (int64_t i = 1; i <= first_size_; ++i) {
            for (int64_t j = 1; j <= second_size_; ++j) {
                if (edges_in_components_out_[second_matrix_[i][j]] < 1) {
                    CheckEdgeOut(Coord(i, j));
                }
            }
        }
    }
};

int main() {
    int64_t first_size = 0;
    int64_t second_size = 0;
    std::cin >> first_size >> second_size;
    Graph graph(first_size, second_size);
    graph.PrintResultSquares();
    return 0;
}
