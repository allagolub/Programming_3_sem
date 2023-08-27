#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
class Trie {
public:
    Trie() {
        Node root;
        trie_.emplace_back(root);
    };
    void Print(int64_t ind, bool max_str_find) {
        if ((trie_[ind].is_terminal) && (trie_[ind].dict.empty())) {
            res_operations.emplace_back('P');
            return;
        }
        if ((trie_[ind].is_terminal) && (!trie_[ind].dict.empty())) {
            res_operations.emplace_back('P');
        }
        for (auto it: trie_[ind].dict) {
            if ((!max_str_find) || (it.first != max_str[curr_max_ind])) {
                res_operations.emplace_back(it.first);
                Print(it.second, false);
                res_operations.emplace_back('-');
            }
        }
        if (max_str_find) {
            res_operations.emplace_back(max_str[curr_max_ind]);
            curr_max_ind++;
            Print(trie_[ind].dict[max_str[curr_max_ind - 1]], true);
        }

    }
    int64_t curr_max_ind = 0;
    std::vector<char> res_operations;
    void Insert(const std::string &str) {
        int64_t state = 0;
        int64_t size = str.size();
        for (int64_t i = 0; i < size; ++i) {
            if (!trie_[state].dict.count(str[i])) {
                trie_.emplace_back(Node());
                trie_[state].dict[str[i]] = (trie_.size()) - 1;
            }
            state = trie_[state].dict[str[i]];
        }
        trie_[state].is_terminal = true;
    }
    std::string max_str;
private:
    struct Node {
        std::map<char, int64_t> dict;
        bool is_terminal = false;
        Node() = default;
        int64_t order = 0;

    };
    std::vector<Node> trie_;
};
int main() {
    int64_t quantity = 0;
    std::cin >> quantity;
    std::string surname;
    Trie trie;
    int64_t max_len = 0;
    int64_t sum_len = 0;
    for (int64_t i = 0; i < quantity; ++i) {
        std::cin >> surname;
        if (surname.size() > max_len) {
            max_len = surname.size();
            trie.max_str = surname;
        }
        sum_len += surname.size();
        trie.Insert(surname);
    }
    trie.Print(0, true);
    std::cout << trie.res_operations.size() <<'\n';
    for (int64_t i = 0; i < trie.res_operations.size(); ++i) {
        std::cout << trie.res_operations[i] << '\n';
    }
    return 0;

}