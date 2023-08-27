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
    int64_t SetCount();
    int64_t FindSet(int64_t vertex);
    bool Union(int64_t first_vertex, int64_t second_vertex);
    explicit DSU(int64_t quantity_vert) : quantity_components_(quantity_vert) {
        parent_.resize(quantity_vert);
        rank_.resize(quantity_vert);
        for (int64_t i = 0; i < quantity_vert; ++i) {
            MakeSet(i);
        }
    }
    DSU() = default;

private:
    std::vector<int64_t> parent_;
    std::vector<int64_t> rank_;
    int64_t quantity_components_;
};
class Graph {
public:
    explicit Graph(int64_t quantity_vertexes) : quantity_vertexes_(quantity_vertexes) {
        dsu_ = DSU(quantity_vertexes);
    }
    int64_t Boruvka();
    void PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight);

private:
    std::vector<Edge> edges_;
    int64_t quantity_vertexes_;
    DSU dsu_;
    int64_t k_max_weight_ = 10000000000;
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
int64_t DSU::SetCount() {
    return quantity_components_;
}
bool DSU::Union(int64_t first_vertex, int64_t second_vertex) {
    first_vertex = FindSet(first_vertex);
    second_vertex = FindSet(second_vertex);
    if (first_vertex == second_vertex) {
        return false;
    }
    if (rank_[first_vertex] < rank_[second_vertex]) {
        parent_[first_vertex] = second_vertex;
    } else if (rank_[first_vertex] > rank_[second_vertex]) {
        parent_[second_vertex] = first_vertex;
    } else {
        parent_[first_vertex] = second_vertex;
        rank_[second_vertex] += 1;
    }
    quantity_components_--;
    return true;
}
void Graph::PushEdge(int64_t first_vert, int64_t second_vert, int64_t weight) {
    edges_.emplace_back(Edge(first_vert, second_vert, weight));
}
int64_t Graph::Boruvka() {
    int64_t weight_mst = 0;
    while (dsu_.SetCount() > 1) {
        std::vector<Edge> min_edge;
        min_edge.resize(quantity_vertexes_, Edge(-1, -1, k_max_weight_));
        for (auto& edge : edges_) {
            int64_t component_from = dsu_.FindSet(edge.from_);
            int64_t component_to = dsu_.FindSet(edge.to_);
            if (component_from != component_to) {
                if (edge.weight_ < min_edge[component_to].weight_) {
                    min_edge[component_to] = edge;
                }
                if (edge.weight_ < min_edge[component_from].weight_) {
                    min_edge[component_from] = edge;
                }
            }
        }
        for (auto& edge : min_edge) {
            if (edge.from_ == -1) {
                continue;
            }
            if (dsu_.Union(edge.from_, edge.to_)) {
                weight_mst += edge.weight_;
            }
        }
    }
    return weight_mst;
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
    int64_t weight = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight;
        graph.PushEdge(first_vert - 1, second_vert - 1, weight);
    }
    int64_t min_weight = graph.Boruvka();
    std::cout << min_weight;
    return 0;
}