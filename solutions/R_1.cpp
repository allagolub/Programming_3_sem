#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
int64_t Pow(int64_t first_num, int64_t second_num);
class Trie {
public:
    explicit Trie(int64_t max_digit_new) {
        Node root;
        trie_.emplace_back(root);
        max_digit_ = max_digit_new;
    };
    Trie() = default;

    void Insert(const std::string &str, const std::string &city_name) {
        int64_t state = 0;
        int64_t size = str.size();
        for (int64_t i = 0; i < size; ++i) {
            if (!trie_[state].dict.count(str[i])) {
                trie_.emplace_back(Node());
                trie_[state].dict[str[i]] = (trie_.size()) - 1;
                trie_[state].depth = i;
            }
            state = trie_[state].dict[str[i]];
        }
        trie_[state].depth = size;
        trie_[state].city = city_name;
        trie_[state].is_terminal = true;
    }
    int64_t CountCakes(int64_t ind) {
        if ((trie_[ind].depth > max_digit_) && (trie_[ind].is_terminal)) {
            trie_[ind].sum_cakes = 0;
            std::cout << trie_[ind].city << ' ' << trie_[ind].sum_cakes << '\n';
            for (auto it : trie_[ind].dict) {
                CountCakes(it.second);
            }
            return 0;
        }
        if (trie_[ind].is_terminal) {
            trie_[ind].sum_cakes = Pow(10, max_digit_ - trie_[ind].depth);
            for (auto it : trie_[ind].dict) {
                if (trie_[it.second].depth <= max_digit_) {
                    if (trie_[it.second].is_terminal) {
                        CountCakes(it.second);
                        trie_[ind].sum_cakes -= Pow(10, max_digit_ - trie_[ind].depth - 1);
                    } else {
                        trie_[ind].sum_cakes -= CountCakes(it.second);
                    }
                } else {
                    CountCakes(it.second);
                }
            }
            std::cout << trie_[ind].city << ' ' << trie_[ind].sum_cakes << '\n';
            return trie_[ind].sum_cakes;
        }
        for (auto it : trie_[ind].dict) {
            if (trie_[it.second].depth <= max_digit_) {
                if (trie_[it.second].is_terminal) {
                    CountCakes(it.second);
                    trie_[ind].sum_cakes += Pow(10, max_digit_ - trie_[ind].depth - 1);
                } else {
                    trie_[ind].sum_cakes += CountCakes(it.second);;
                }
            } else {
                CountCakes(it.second);
            }
        }
        return trie_[ind].sum_cakes;
    }

    struct Node {
        std::map<char, int64_t> dict;
        bool is_terminal = false;
        Node() = default;
        int64_t depth = 0;
        int64_t sum_cakes = 0;
        std::string city;
    };
    int64_t max_digit_ = 0;
    std::vector<Node> trie_;
};
int64_t Pow(int64_t first_num, int64_t second_num) {
    int64_t res_pow = 1;
    for (int64_t i = 0; i < second_num; ++i) {
        res_pow *= first_num;
    }
    return  res_pow;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity = 0;
    std::cin >> quantity;
    int64_t max_digit = 0;
    std::cin >> max_digit;
    Trie trie(max_digit);
    std::string city_name;
    std::string city_index;
    for (int64_t i = 0; i < quantity; ++i) {
        std::cin >> city_index >> city_name;
        trie.Insert(city_index, city_name);
    }
    trie.CountCakes(0);
    return 0;
}
