#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <queue>
struct Edge {
    int64_t to_;
    int64_t flow_;
    int64_t capacity_;
    int64_t index_back_edge_;
    Edge(const int64_t& to, const int64_t& flow, const int64_t& capacity, const int64_t& index_back_edge)
            : to_(to), flow_(flow), capacity_(capacity), index_back_edge_(index_back_edge) {
    }
    Edge() = default;
};
class Graph {
public:
    explicit Graph(int64_t quantity_lines, int64_t quantity_columns)
            : quantity_vertexes_(quantity_columns * quantity_lines + 2) {
        end_vertex_ = quantity_vertexes_ - 1;
        used_.resize(quantity_vertexes_, -1);
        edges_.resize(quantity_vertexes_);
        quantity_lines_ = quantity_lines;
        quantity_columns_ = quantity_columns;
    }
    bool IsCorrectElement();
    void PushVertex(const int& first_vert_line, const int& first_vert_column, const int64_t& capacity);
    void PrintMaxFlow();

private:
    const int64_t k_max_weight_ = 100000000;
    int64_t quantity_vertexes_;
    int64_t max_flow_ = 0;
    int64_t first_flow_ = 0;
    int64_t second_flow_ = 0;
    int64_t begin_vertex_ = 0;
    int64_t end_vertex_;
    int64_t quantity_lines_;
    int64_t quantity_columns_;
    bool is_find_element_ = false;
    int time_in_ = 1;
    std::vector<std::vector<Edge>> edges_;
    std::vector<int> used_;
    void FordFulkerson();
    int64_t DFSFlow(const int64_t& begin_vertex, const int64_t& curr_flow);
    void PushNeighborsEdges(const int& first_vert_line, const int& first_vert_column, const int& line_shift,
                            const int& column_shift);
};
void Graph::PushVertex(const int& first_vert_line, const int& first_vert_column, const int64_t& capacity) {
    int first_vert = (first_vert_line - 1) * quantity_columns_ + first_vert_column;
    is_find_element_ = true;
    if ((first_vert_column + first_vert_line) % 2 == 0) {
        int64_t index_back_edge = edges_[first_vert].size();
        edges_[begin_vertex_].emplace_back(Edge(first_vert, 0, capacity, index_back_edge));
        index_back_edge = edges_[begin_vertex_].size() - 1;
        edges_[first_vert].emplace_back(Edge(first_vert, 0, 0, index_back_edge));
        first_flow_ += capacity;
    } else {
        int64_t index_back_edge = edges_[end_vertex_].size();
        edges_[first_vert].emplace_back(Edge(end_vertex_, 0, capacity, index_back_edge));
        index_back_edge = edges_[first_vert].size() - 1;
        edges_[end_vertex_].emplace_back(Edge(first_vert, 0, 0, index_back_edge));
        second_flow_ += capacity;
    }
}
void Graph::PushNeighborsEdges(const int& first_vert_line, const int& first_vert_column, const int& line_shift,
                               const int& column_shift) {
    int current_element = (first_vert_line - 1) * quantity_columns_ + first_vert_column;
    int neighbor = (first_vert_line + line_shift - 1) * quantity_columns_ + first_vert_column + column_shift;
    if (edges_[current_element].empty()) {
        return;
    }
    if ((neighbor >= (quantity_vertexes_ - 1)) || (neighbor <= 0) || (edges_[neighbor].empty())) {
        return;
    }
    if ((first_vert_line + line_shift >= 1) && (first_vert_line + line_shift <= quantity_lines_) &&
        (first_vert_column + column_shift >= 1) && (first_vert_column + column_shift <= quantity_columns_)) {
        int64_t index_back_edge = edges_[neighbor].size();
        edges_[current_element].emplace_back(Edge(neighbor, 0, 1, index_back_edge));
        index_back_edge = edges_[current_element].size() - 1;
        edges_[neighbor].emplace_back(Edge(current_element, 0, 0, index_back_edge));
    }
}
int64_t Graph::DFSFlow(const int64_t& begin_vertex, const int64_t& curr_flow) {
    if (begin_vertex == quantity_vertexes_ - 1) {
        return curr_flow;
    }
    used_[begin_vertex] = time_in_;
    for (auto& edge : edges_[begin_vertex]) {
        if ((used_[edge.to_] != time_in_) && (edge.flow_ < edge.capacity_)) {
            int64_t delta = DFSFlow(edge.to_, std::min(curr_flow, edge.capacity_ - edge.flow_));
            if (delta > 0) {
                edge.flow_ += delta;
                edges_[edge.to_][edge.index_back_edge_].flow_ -= delta;
                return delta;
            }
        }
    }
    return 0;
}
void Graph::FordFulkerson() {
    int delta = DFSFlow(0, k_max_weight_);
    while (delta) {
        max_flow_ += delta;
        time_in_++;
        delta = DFSFlow(0, k_max_weight_);
    }
}
bool Graph::IsCorrectElement() {
    if (!is_find_element_) {
        return false;
    }
    if (first_flow_ != second_flow_) {
        return false;
    }
    for (int64_t i = 1; i < quantity_vertexes_ - 1; ++i) {
        if ((((i - 1) / quantity_columns_ + 1 + (i - 1) % quantity_columns_ + 1) % 2 == 0) && (!edges_[i].empty())) {
            PushNeighborsEdges((i - 1) / quantity_columns_ + 1, (i - 1) % quantity_columns_ + 1, -1, 0);
            PushNeighborsEdges((i - 1) / quantity_columns_ + 1, (i - 1) % quantity_columns_ + 1, 1, 0);
            PushNeighborsEdges((i - 1) / quantity_columns_ + 1, (i - 1) % quantity_columns_ + 1, 0, -1);
            PushNeighborsEdges((i - 1) / quantity_columns_ + 1, (i - 1) % quantity_columns_ + 1, 0, 1);
        }
    }
    FordFulkerson();
    return (max_flow_ == first_flow_);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_lines = 0;
    int64_t quantity_columns = 0;
    std::cin >> quantity_lines >> quantity_columns;
    Graph graph(quantity_lines, quantity_columns);
    char element = 0;
    for (int64_t i = 1; i <= quantity_lines; ++i) {
        for (int64_t j = 1; j <= quantity_columns; ++j) {
            std::cin >> element;
            switch (element) {
                case 'H':
                    graph.PushVertex(i, j, 1);
                    break;
                case 'O':
                    graph.PushVertex(i, j, 2);
                    break;
                case 'N':
                    graph.PushVertex(i, j, 3);
                    break;
                case 'C':
                    graph.PushVertex(i, j, 4);
                    break;
            }
        }
    }
    if (graph.IsCorrectElement()) {
        std::cout << "Valid";
    } else {
        std::cout << "Invalid";
    }
    return 0;
}