#include <iostream>
#include <vector>
#include <queue>
enum Colors { WHITE, GRAY, BLACK };
struct Coord {
    int64_t sign_ = 0;
    int64_t ratio_ = 0;
    Coord(int64_t sign, int64_t ratio) : sign_(sign), ratio_(ratio) {
    }
    Coord() = default;
};
struct Edge {
    int64_t vert_ = 0;
    int64_t weight_ = 0;
    Edge(int64_t vert, int64_t weight) : vert_(vert), weight_(weight) {
    }
    Edge() = default;
};
class Graph {
public:
    Graph(const int64_t new_quantity_vert, int64_t quantity_edges)
            : quantity_vert_(new_quantity_vert), quantity_edges_(quantity_edges) {
        edges_.resize(quantity_vert_ + 1);
        new_coord_.resize(quantity_vert_ + 1);
        num_is_used_.resize(quantity_vert_ + 1, false);
        final_coord_.resize(quantity_vert_ + 1, -1);
        colors_.resize(quantity_vert_ + 1, Colors::WHITE);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
        edges_[first_vert].emplace_back(Edge(second_vert, weight));
        edges_[second_vert].emplace_back(Edge(first_vert, weight));
    }
    void PrintGraphVert() {
        if (FindGraphVert()) {
            for (int64_t i = 1; i <= quantity_vert_; ++i) {
                std::cout << final_coord_[i] << ' ';
            }
        }
    }

private:
    std::vector<std::vector<Edge>> edges_;
    std::vector<Coord> new_coord_;
    std::vector<bool> num_is_used_;
    std::vector<int64_t> final_coord_;
    std::vector<int64_t> colors_;
    int64_t quantity_vert_;
    int64_t quantity_edges_;
    int64_t begin_vertex_;
    Coord min_coord_plus_ = Coord(1, 1);
    Coord min_coord_minus_ = Coord(-1, 1000000000);
    int64_t min_vert_plus_ = 1;
    int64_t min_vert_minus_ = -1;
    void CheckMinCoord(const Coord &coord_vert, int64_t vert) {
        if ((coord_vert.sign_ == 1) && (coord_vert.ratio_ < min_coord_plus_.ratio_)) {
            min_coord_plus_ = coord_vert;
            min_vert_plus_ = vert;
        }
        if ((coord_vert.sign_ == -1) && (coord_vert.ratio_ < min_coord_minus_.ratio_)) {
            min_coord_minus_ = coord_vert;
            min_vert_minus_ = vert;
        }
    }
    void BFS() {
        std::queue<int64_t> queue;
        queue.push(begin_vertex_);
        int64_t new_vertex = 0;
        while (!queue.empty()) {
            new_vertex = queue.front();
            queue.pop();
            for (auto neighbor : edges_[new_vertex]) {
                if ((new_coord_[neighbor.vert_].sign_ == 0) && (new_coord_[neighbor.vert_].ratio_ == 0)) {
                    new_coord_[neighbor.vert_].sign_ = -new_coord_[new_vertex].sign_;
                    new_coord_[neighbor.vert_].ratio_ = neighbor.weight_ - new_coord_[new_vertex].ratio_;
                    CheckMinCoord(new_coord_[neighbor.vert_], neighbor.vert_);
                    queue.push(neighbor.vert_);
                }
            }
        }
    }
    bool FindGraphVert() {
        begin_vertex_ = 1;
        new_coord_[begin_vertex_].sign_ = 1;
        new_coord_[begin_vertex_].ratio_ = 0;
        BFS();
        begin_vertex_ = min_vert_plus_;
        final_coord_[begin_vertex_] = 1;
        num_is_used_[1] = true;
        int64_t x = -min_coord_plus_.ratio_ + 1;
        if (CheckCorrectDFS(begin_vertex_, x)) {
            for (int64_t i = 1; i <= quantity_vert_; ++i) {
                std::cout << final_coord_[i] << ' ';
            }
            return false;
        }

        std::fill(num_is_used_.begin(), num_is_used_.end(), false);
        std::fill(final_coord_.begin(), final_coord_.end(), -1);
        std::fill(colors_.begin(), colors_.end(), Colors::WHITE);
        begin_vertex_ = min_vert_minus_;
        x = min_coord_minus_.ratio_ - 1;
        final_coord_[begin_vertex_] = 1;
        num_is_used_[1] = true;
        CheckCorrectDFS(begin_vertex_, x);
        return true;
    }
    bool CheckCorrectDFS(int64_t begin_vertex, int64_t x) {
        colors_[begin_vertex] = Colors::GRAY;
        for (auto neighbor : edges_[begin_vertex]) {
            if (colors_[neighbor.vert_] == Colors::WHITE) {
                final_coord_[neighbor.vert_] = x * new_coord_[neighbor.vert_].sign_ + new_coord_[neighbor.vert_].ratio_;
                if ((num_is_used_[final_coord_[neighbor.vert_]]) || (final_coord_[neighbor.vert_] > quantity_vert_)) {
                    return false;
                }
                num_is_used_[final_coord_[neighbor.vert_]] = true;
                if (!CheckCorrectDFS(neighbor.vert_, x)) {
                    return false;
                }
            } else {
                if (final_coord_[neighbor.vert_] != -1) {
                    int64_t sum = final_coord_[neighbor.vert_] + final_coord_[begin_vertex];
                    if (neighbor.weight_ != sum) {
                        return false;
                    }
                }
            }
        }
        colors_[begin_vertex] = Colors::GRAY;
        return true;
    }
};

int main() {
    int64_t quantity_edges = 0;
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes, quantity_edges);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight;
        graph.PushEdge(first_vert, second_vert, weight);
    }
    graph.PrintGraphVert();
    return 0;
}
