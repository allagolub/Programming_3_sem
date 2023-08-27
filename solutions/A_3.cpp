#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
struct Edge {
    int64_t from_;
    int64_t to_;
    int64_t quantity_vertex_;
    Edge(const int64_t& from, const int64_t& to, const int64_t& weight) : from_(from), to_(to), quantity_vertex_(weight) {
    }
    Edge() = default;
};
class DSU {
public:
    void MakeSet(int64_t vertex);
    int64_t FindSet(int64_t vertex);
    bool Union(int64_t first_vertex, int64_t second_vertex);
    explicit DSU(int64_t quantity_vert) : graph_quantity_vertexes(quantity_vert) {
        parent_.resize(quantity_vert + 1);
        rank_.resize(quantity_vert + 1);
        quantity_vertex_.resize(quantity_vert + 1, 1);
        for (int64_t i = 0; i < quantity_vert; ++i) {
            MakeSet(i);
        }
    }
    DSU() = default;
    std::vector<int64_t> quantity_vertex_;
    int64_t graph_quantity_vertexes;

private:
    std::vector<int64_t> parent_;
    std::vector<int64_t> rank_;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes) {
        dsu_ = DSU(quantity_vertexes);
    }
    bool CheckEdge(int64_t first_vert, int64_t second_vert);

private:
    DSU dsu_;
};
void DSU::MakeSet(int64_t vertex) {
    parent_[vertex] = vertex;
    rank_[vertex] = 1;
}
int64_t DSU::FindSet(int64_t vertex) {
    if (vertex == parent_[vertex]) {
        return vertex;
    }
    return parent_[vertex] = FindSet((parent_[vertex]));
}
bool DSU::Union(int64_t first_vertex, int64_t second_vertex) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex == second_vertex) {
        return false;
    }
    if (rank_[first_vertex] < rank_[second_vertex]) {
        parent_[first_vertex] = second_vertex;
        quantity_vertex_[second_vertex] += quantity_vertex_[first_vertex];
    } else if (rank_[first_vertex] > rank_[second_vertex]) {
        parent_[second_vertex] = first_vertex;
        quantity_vertex_[first_vertex] += quantity_vertex_[second_vertex];
    } else {
        parent_[first_vertex] = second_vertex;
        quantity_vertex_[second_vertex] += quantity_vertex_[first_vertex];
        rank_[second_vertex] += 1;
    }
    return ((quantity_vertex_[first_vertex] == graph_quantity_vertexes) ||
            (quantity_vertex_[second_vertex] == graph_quantity_vertexes));
}
bool Graph::CheckEdge(int64_t first_vert, int64_t second_vert) {
    return dsu_.Union(first_vert, second_vert);
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_edges = 0;
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert;
        if (graph.CheckEdge(first_vert, second_vert)) {
            std::cout << i + 1;
            break;
        };
    }
    return 0;
}