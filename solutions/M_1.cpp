#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <vector>
struct  Borders {
    int64_t left_border;
    int64_t right_border;
    int64_t index_pattern;
    Borders(int64_t new_left_border, int64_t new_right_border, int64_t new_index_pattern) : left_border(new_left_border), right_border(new_right_border), index_pattern(new_index_pattern) {}
};
struct Node {
    std::unordered_map<char, int64_t> next;
    std::vector<Borders> borders;
    int64_t link;
    int64_t exit_link;
    int64_t len_pattern;
    bool is_terminal = false;
    Node() = default;
};
struct SuffQueue {
    char symbol;
    int64_t parent;
    int64_t ind_curr_node;
    SuffQueue(char symbol_new, int64_t parent_new, int64_t ind_curr_node_new) : symbol(symbol_new), parent(parent_new), ind_curr_node(ind_curr_node_new) {}
    SuffQueue() = default;
};

class Trie {
public:
    std::vector<Node> st;
    std::vector<bool> result_index;
    void Insert(std::string& str, int64_t order_pattern, int64_t left_ind, int64_t right_ind) {
        int64_t curr_node_ind = 0;
        for (auto& symb: str) {
            int64_t next_ind = st[curr_node_ind].next[symb];
            if (next_ind == 0) {
                st.emplace_back(Node());
                next_ind = st.size() - 1;
                st[curr_node_ind].next[symb] = next_ind;
            }
            curr_node_ind = next_ind;
        }
        st[curr_node_ind].is_terminal = true;
        st[curr_node_ind].len_pattern = str.size();
        Borders new_border(left_ind, right_ind, order_pattern);
        st[curr_node_ind].borders.push_back(new_border);
    }
    void BuildSuffixReferences() {
        st[0].link = -1;
        std::queue<SuffQueue> queue;
        for (auto& pair: st[0].next) {
            queue.push(SuffQueue(pair.first, 0, pair.second));
        }
        SuffQueue tmp;
        while (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
            int64_t curr_ind_suff = tmp.parent;
            int64_t curr_suff_link = st[curr_ind_suff].link;
            while ((curr_suff_link != -1) && (st[curr_suff_link].next.find(tmp.symbol) == st[curr_suff_link].next.end())) {
                curr_suff_link = st[curr_ind_suff].link;
                curr_ind_suff = curr_suff_link;
            }
            if (curr_suff_link == -1) {
                st[tmp.ind_curr_node].link = 0;
            } else {
                st[tmp.ind_curr_node].link = st[curr_suff_link].next[tmp.symbol];
            }
            for (auto& pair: st[tmp.ind_curr_node].next) {
                queue.push(SuffQueue(pair.first, tmp.ind_curr_node, pair.second));
            }
        }
    }
    void BuildExitSuffixReferences() {
        st[0].exit_link = -1;
        std::queue<int64_t> queue;
        for (auto& pair: st[0].next) {
            queue.push(pair.second);
        }
        int64_t tmp = 0;
        while (!queue.empty()) {
            tmp = queue.front();
            queue.pop();
            int64_t suff_link = st[tmp].link;
            if (suff_link != 0) {
                if (st[suff_link].is_terminal) {
                    st[tmp].exit_link = suff_link;
                } else {
                    st[tmp].exit_link = st[suff_link].exit_link;
                }
            }
            for (auto& pair: st[tmp].next) {
                queue.push(pair.second);
            }
        }
    }
    explicit Trie(int64_t size) {
        std::string dict_str;
        st.emplace_back(Node());
        result_index.resize(size);
        std::fill(result_index.begin(), result_index.end(), false);
        int64_t left_ind = 0;
        int64_t right_ind = 0;
        for (int i = 0; i < size; ++i) {
            std::cin >> left_ind >> right_ind;
            std::cin >> dict_str;
            Insert(dict_str, i, left_ind, right_ind);
        }
        BuildSuffixReferences();
        BuildExitSuffixReferences();
    }
    int64_t NextState(int64_t ind, char symbol) {
        while ((ind != -1) && (st[ind].next.find(symbol) == st[ind].next.end())) {
            ind = st[ind].link;
        }
        if (ind == -1) {
            return 0;
        }
        return st[ind].next[symbol];
    }
    void PrintEntries(int64_t ind, int64_t node_index) {
        if (!st[node_index].is_terminal) {
            node_index = st[node_index].exit_link;
        }
        while ((node_index != 0) && (node_index != -1)){
            for (int64_t i = 0; i < int64_t(st[node_index].borders.size()); ++i) {
                if ((ind + 1 <= st[node_index].borders[i].right_border) && ((ind - st[node_index].len_pattern + 2) >= st[node_index].borders[i].left_border)) {
                    result_index[st[node_index].borders[i].index_pattern] = true;
                }
            }
            node_index = st[node_index].exit_link;
        }
    }
};
void AhoCorasik(std::string& str, int64_t size_patterns) {
    Trie trie_for_aho_corasik(size_patterns);
    int64_t node = 0;
    int64_t str_size = str.size();
    for (int64_t i = 0; i < str_size; ++i) {
        node = trie_for_aho_corasik.NextState(node, str[i]);
        trie_for_aho_corasik.PrintEntries(i, node);
    }
    int64_t quantity_patterns =  trie_for_aho_corasik.result_index.size();
    for (int64_t i = 0; i < quantity_patterns; ++i) {
        if (trie_for_aho_corasik.result_index[i]) {
            std::cout << '+';
        } else {
            std::cout << '-';
        }
    }
}
int main() {
    std::string str;
    std::cin >> str;
    int64_t size_dict = 0;
    std::cin >> size_dict;
    AhoCorasik(str, size_dict);
    return 0;
}