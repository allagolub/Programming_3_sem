#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes) : quantity_vertexes_(quantity_vertexes) {
        adjacency_matrix_.resize(quantity_vertexes_);
        for (int64_t i = 0; i < quantity_vertexes_; ++i) {
            adjacency_matrix_[i].resize(quantity_vertexes_, k_max_weight_);
        }
    }
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight);
    void PrintMinDistances();

private:
    const int64_t k_max_weight_ = 10000000000;
    int64_t quantity_vertexes_;
    std::vector<std::vector<int64_t>> adjacency_matrix_;
    void FloydWarshall();
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight) {
    adjacency_matrix_[first_vert][second_vert] = weight;
}
void Graph::FloydWarshall() {
    for (int64_t quantity = 0; quantity < quantity_vertexes_; ++quantity) {
        for (int64_t first_vertex = 0; first_vertex < quantity_vertexes_; ++first_vertex) {
            for (int64_t second_vertex = 0; second_vertex < quantity_vertexes_; ++second_vertex) {
                adjacency_matrix_[first_vertex][second_vertex] =
                        std::min(adjacency_matrix_[first_vertex][second_vertex],
                                 adjacency_matrix_[first_vertex][quantity] + adjacency_matrix_[quantity][second_vertex]);
            }
        }
    }
}
void Graph::PrintMinDistances() {
    FloydWarshall();
    for (int64_t i = 0; i < quantity_vertexes_; ++i) {
        for (int64_t j = 0; j < quantity_vertexes_; ++j) {
            std::cout << adjacency_matrix_[i][j] << ' ';
        }
        std::cout << '\n';
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_vertexes;
    Graph graph(quantity_vertexes);
    int64_t weight = 0;
    for (int64_t i = 0; i < quantity_vertexes; ++i) {
        for (int64_t j = 0; j < quantity_vertexes; ++j) {
            std::cin >> weight;
            graph.PushEdge(i, j, weight);
        }
    }
    graph.PrintMinDistances();
    return 0;
}