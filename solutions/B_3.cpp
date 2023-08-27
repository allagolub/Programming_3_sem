#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
struct Edge {
    int64_t from_;
    int64_t to_;
    int64_t weight_;
    Edge(const int64_t& from, const int64_t& to, const int64_t& weight) : from_(from), to_(to), weight_(weight) {
    }
    Edge() = default;
};
class DSU {
public:
    void MakeSet(int64_t vertex);
    int64_t FindSet(int64_t vertex);
    void Union(int64_t first_vertex, int64_t second_vertex, int64_t weight);
    explicit DSU(int64_t quantity_vert) {
        parent_.resize(quantity_vert + 1);
        rank_.resize(quantity_vert + 1);
        weight_.resize(quantity_vert + 1, 0);
        for (int64_t i = 0; i < quantity_vert; ++i) {
            MakeSet(i);
        }
    }
    DSU() = default;
    std::vector<int64_t> weight_;

private:
    std::vector<int64_t> parent_;
    std::vector<int64_t> rank_;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes) {
        dsu_ = DSU(quantity_vertexes);
    }
    void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight);
    int64_t RequestSum(int64_t vertex);

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
void DSU::Union(int64_t first_vertex, int64_t second_vertex, int64_t weight) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex == second_vertex) {
        weight_[first_vertex] += weight;
        return;
    }
    if (rank_[first_vertex] < rank_[second_vertex]) {
        parent_[first_vertex] = second_vertex;
        weight_[second_vertex] += weight + weight_[first_vertex];
    } else if (rank_[first_vertex] > rank_[second_vertex]) {
        parent_[second_vertex] = first_vertex;
        weight_[first_vertex] += weight + weight_[second_vertex];
    } else {
        parent_[first_vertex] = second_vertex;
        weight_[second_vertex] += weight + weight_[first_vertex];
        rank_[second_vertex] += 1;
    }
}
void Graph::PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
    dsu_.Union(first_vert, second_vert, weight);
}
int64_t Graph::RequestSum(int64_t vertex) {
    int root = dsu_.FindSet(vertex);
    return dsu_.weight_[root];
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_requests = 0;
    int64_t quantity_vertexes = 0;
    std::cin >> quantity_vertexes >> quantity_requests;
    Graph graph(quantity_vertexes);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    int64_t operation = 0;
    for (int64_t i = 0; i < quantity_requests; ++i) {
        std::cin >> operation;
        if (1 == operation) {
            std::cin >> first_vert >> second_vert >> weight;
            graph.PushEdge(first_vert, second_vert, weight);
        } else {
            std::cin >> first_vert;
            int64_t sum_weight = graph.RequestSum(first_vert);
            std::cout << sum_weight << '\n';
        }
    }
    return 0;
}