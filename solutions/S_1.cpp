#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
class Trie {
public:
    Trie(int64_t number_system_new, int64_t len_num_new) {
        Node root;
        trie_.emplace_back(root);
        number_system = number_system_new;
        len_num = len_num_new;
        int64_t price_fruits = 0;
        price.resize(len_num);
        for (int64_t i = 0; i < len_num; i++) {
            std::cin >> price_fruits;
            price[i] = price_fruits;
        }
    };
    void Insert(const std::string &str) {
        int64_t state = 0;
        int64_t size = str.size();
        for (int64_t i = 0; i < size; ++i) {
            if (!trie_[state].dict.count(str[i])) {
                trie_.emplace_back(Node());
                trie_[state].dict[str[i]] = (trie_.size()) - 1;
            }
            state = trie_[state].dict[str[i]];
            trie_[state].len = i + 1;
            trie_[state].quantity++;
        }
        trie_[state].is_terminal = true;
        trie_[state].len = str.size();
    }
    int64_t CountPath(int64_t ind) {
        if (dp[ind] > 0) {
            return dp[ind];
        }
        int64_t sum = 0;
        if (ind > 0) {
            sum += trie_[ind].quantity * price[trie_[ind].len - 1];
        }
        if ((trie_[ind].dict.size() < number_system) && (ind == 0)) {
            dp[ind] = 0;
            for (int64_t i = '0'; i < number_system + '0'; ++i) {
                if (trie_[ind].dict.find(i) == trie_[ind].dict.end()) {
                    trie_[ind].min_str = i;
                    break;
                }
            }
            return 0;
        }
        if (trie_[ind].dict.size() < number_system) {
            dp[ind] = trie_[ind].quantity * price[trie_[ind].len - 1];
            for (int64_t i = '0'; i < number_system + '0'; ++i) {
                if (trie_[ind].dict.find(i) == trie_[ind].dict.end()) {
                    if (trie_[ind].len != len_num) {
                        trie_[ind].min_str = i;
                    }
                    break;
                }
            }
            return dp[ind];
        }
        if (trie_[ind].len == len_num) {
            dp[ind] = trie_[ind].quantity * price[trie_[ind].len - 1];
            trie_[ind].min_str = "";
            return dp[ind];
        }
        int64_t min_price = 10000000000000;
        int64_t price_next = 0;
        char min_symb = 0;
        int64_t min_ind = 0;
        for (auto it : trie_[ind].dict) {
            if (ind != 0) {
                price_next = CountPath(it.second) - trie_[it.second].quantity * price[trie_[ind].len - 1];
            } else {
                price_next = CountPath(it.second);
            }
            if (min_price > price_next) {
                min_price = price_next;
                min_symb = it.first;
                min_ind = it.second;
            }
        }
        trie_[ind].min_str = min_symb + trie_[min_ind].min_str;
        sum += min_price;
        dp[ind] = sum;
        return sum;
    }
    struct Node {
        std::map<char, int64_t> dict;
        bool is_terminal = false;
        Node() = default;
        int64_t len = 0;
        int64_t quantity = 0;
        std::string min_str;
    };
    std::vector<Node> trie_;
    int64_t number_system;
    int64_t len_num;
    std::vector<int64_t> price;
    std::vector<int64_t> dp;

};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity_participants = 0;
    std::cin >> quantity_participants;
    int64_t len_num = 0;
    std::cin >> len_num;
    int64_t number_system = 0;
    std::cin >> number_system;
    std::string str;
    Trie trie(number_system, len_num);
    for (int64_t i = 0; i < quantity_participants; ++i) {
        std::cin >> str;
        trie.Insert(str);
    }
    trie.dp.resize(trie.trie_.size());
    trie.CountPath(0);
    std::cout << trie.trie_[0].min_str;
    if (trie.trie_[0].min_str.size() < len_num) {
        for (int64_t i = trie.trie_[0].min_str.size() + 1; i <= len_num; ++i) {
            std::cout << 0;
        }
    }
    std::cout << '\n';
    std::cout << trie.dp[0];
    return 0;
}