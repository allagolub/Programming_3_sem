#include <algorithm>
#include <iostream>
#include <limits>
#include <set>
#include <queue>
#include <vector>
struct Edge {
    int64_t to_;
    int64_t weight_;
    int64_t time_;
    Edge(const int64_t& to, const int64_t& weight, const int64_t& time) : to_(to), weight_(weight), time_(time) {
    }
    Edge() = default;
};
struct MinDist {
    int64_t prev_;
    int64_t prev_time_;
    int64_t min_dist_;
    MinDist(const int64_t& prev, const int64_t& prev_time, const int64_t& min_dist)
            : prev_(prev), prev_time_(prev_time), min_dist_(min_dist) {
    }
    MinDist() = default;
};
struct MinTimeCost {
    int64_t time_;
    int64_t cost_;
    MinTimeCost(const int64_t& time, const int64_t& cost) : time_(time), cost_(cost) {
    }
    MinTimeCost() = default;
};
class Graph {
public:
    explicit Graph(const int64_t& quantity_vertexes, const int64_t& quantity_edges_in_path)
            : quantity_vertexes_(quantity_vertexes)
            , quantity_edges_in_path_(quantity_edges_in_path)
            , end_vertex_(quantity_vertexes - 1) {
        edges_.resize(quantity_vertexes_);
        dist_.resize(quantity_edges_in_path + 1);
        for (int64_t i = 0; i <= quantity_edges_in_path; ++i) {
            dist_[i].resize(quantity_vertexes_, {-1, -1, k_max_weight_});
        }
        min_time_and_cost_.resize(quantity_vertexes_ + 1, {k_max_weight_, k_max_weight_});
    }
    void PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight, const int64_t& time);
    void PrintMinDist();

private:
    const int64_t k_max_weight_ = std::numeric_limits<int64_t>::max();
    int64_t quantity_vertexes_;
    int64_t quantity_edges_in_path_;
    int64_t begin_vertex_ = 0;
    int64_t end_vertex_;
    int64_t min_res_weight_ = k_max_weight_;
    std::vector<MinTimeCost> min_time_and_cost_;
    int64_t index_end_vertex_ = -1;
    std::vector<std::vector<Edge>> edges_;
    std::vector<int64_t> min_path_;
    std::vector<std::vector<MinDist>> dist_;
    bool Relax(const int64_t& order, const int64_t& from, const Edge& edge);
    void BellmanFord();
    void FindMinDist();
};
void Graph::PushEdge(const int64_t& first_vert, const int64_t& second_vert, const int64_t& weight,
                     const int64_t& time) {
    edges_[first_vert].emplace_back(Edge(second_vert, weight, time));
    edges_[second_vert].emplace_back(Edge(first_vert, weight, time));
}
bool Graph::Relax(const int64_t& order, const int64_t& from, const Edge& edge) {
    if (order + edge.time_ > quantity_edges_in_path_) {
        return false;
    }
    if (dist_[order][from].prev_ == edge.to_) {
        return false;
    }
    if ((dist_[order][from].min_dist_ != k_max_weight_) &&
        (dist_[order + edge.time_][edge.to_].min_dist_ > dist_[order][from].min_dist_ + edge.weight_)) {
        dist_[order + edge.time_][edge.to_].min_dist_ = dist_[order][from].min_dist_ + edge.weight_;
        dist_[order + edge.time_][edge.to_].prev_ = from;
        dist_[order + edge.time_][edge.to_].prev_time_ = order;
        return true;
    }
    return false;
}
void Graph::BellmanFord() {
    dist_[0][begin_vertex_] = {-1, 0, 0};
    std::vector<std::queue<int64_t>> queues;
    queues.resize(quantity_edges_in_path_ + 1);
    queues[0].push(begin_vertex_);
    for (int64_t k = 0; k <= quantity_edges_in_path_; ++k) {
        if (queues[k].empty()) {
            continue;
        }
        bool is_change = false;
        while (!queues[k].empty()) {
            auto new_vert = queues[k].front();
            queues[k].pop();
            for (auto& edge : edges_[new_vert]) {
                if (Relax(k, new_vert, edge)) {
                    if (((min_time_and_cost_[edge.to_].cost_ > edge.weight_ + dist_[k][new_vert].min_dist_) ||
                         (min_time_and_cost_[edge.to_].time_ > k + edge.time_))) {
                        min_time_and_cost_[edge.to_].cost_ =
                                std::min(edge.weight_ + dist_[k][new_vert].min_dist_, min_time_and_cost_[edge.to_].cost_);
                        min_time_and_cost_[edge.to_].time_ = std::min(k + edge.time_, min_time_and_cost_[edge.to_].time_);
                        queues[k + edge.time_].push(edge.to_);
                    }
                    is_change = true;
                }
            }
        }
        if (!is_change) {
            break;
        }
    }
}
void Graph::FindMinDist() {
    BellmanFord();
    for (int64_t i = 0; i <= quantity_edges_in_path_; ++i) {
        if (dist_[i][end_vertex_].min_dist_ < min_res_weight_) {
            min_res_weight_ = dist_[i][end_vertex_].min_dist_;
            index_end_vertex_ = i;
        }
    }
    if (min_res_weight_ == k_max_weight_) {
        min_res_weight_ = -1;
        return;
    }
    min_path_.emplace_back(end_vertex_ + 1);
    int64_t prev_time = dist_[index_end_vertex_][end_vertex_].prev_time_;
    int64_t vertex = dist_[index_end_vertex_][end_vertex_].prev_;
    if (vertex == 0) {
        min_path_.emplace_back(vertex + 1);
        std::reverse(min_path_.begin(), min_path_.end());
        return;
    }
    while (vertex != 0) {
        int64_t old_time = prev_time;
        min_path_.emplace_back(vertex + 1);
        prev_time = dist_[prev_time][vertex].prev_time_;
        vertex = dist_[old_time][vertex].prev_;
    }
    min_path_.emplace_back(vertex + 1);
    std::reverse(min_path_.begin(), min_path_.end());
}
void Graph::PrintMinDist() {
    FindMinDist();
    if (-1 == min_res_weight_) {
        std::cout << min_res_weight_;
        return;
    }
    std::cout << min_res_weight_ << '\n';
    int64_t size = min_path_.size();
    std::cout << size << '\n';
    for (int64_t i = 0; i < size; ++i) {
        std::cout << min_path_[i] << ' ';
    }
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t time = 0;
    int64_t quantity_vertexes = 0;
    int64_t quantity_edges = 0;
    int64_t quantity_edges_in_path = 0;
    std::cin >> quantity_vertexes >> quantity_edges;
    std::cin >> quantity_edges_in_path;
    Graph graph(quantity_vertexes, quantity_edges_in_path);
    int64_t first_vert = 0;
    int64_t second_vert = 0;
    int64_t weight = 0;
    for (int64_t i = 0; i < quantity_edges; ++i) {
        std::cin >> first_vert >> second_vert >> weight >> time;
        graph.PushEdge(first_vert - 1, second_vert - 1, weight, time);
    }
    graph.PrintMinDist();
}