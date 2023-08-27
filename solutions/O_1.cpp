#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
struct State{
    int64_t len;
    int64_t link;
    int64_t end_pos;
    std::map<char, int64_t> next;
};
class SuffixAutomation {
    int64_t last_;
public:
    std::vector<State> st;
    int64_t size;
    explicit SuffixAutomation (int64_t quantity): last_(0), st(2 * quantity), size(0) {
        st[0].link = -1;
        st[0].len = 0;
        st[0].end_pos = 0;
    }
    void AddChar(char c) {
        int64_t curr = size + 1;
        ++size;
        st[curr].len = st[last_].len + 1;
        st[curr].end_pos = st[curr].len - 1;
        int64_t p = 0;
        for (p = last_; p != -1 && st[p].next.find(c) == st[p].next.end(); p = st[p].link) {
            st[p].next[c] = curr;
        }
        if (p == -1) {
            st[curr].link = 0;
        } else {
            int64_t q = st[p].next[c];
            if (st[q].len == st[p].len + 1) {
                st[curr].link = q;
            }
            else {
                int64_t copy = size + 1;
                ++size;
                st[copy].len = st[p].len + 1;
                st[copy].next = st[q].next;
                st[copy].link = st[q].link;
                st[copy].end_pos = st[q].end_pos;
                for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
                    st[p].next[c] = copy;
                }
                st[q].link = copy;
                st[curr].link = copy;
            }
        }
        last_ = curr;
    }
    bool Find(const int64_t& len_suff) {
        int64_t max_len = st[last_].link;
        return st[max_len].len < len_suff;
    }
};
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int64_t quantity = 0;
    char symbol_command = 0;
    char symbol_str = 0;
    int64_t pos = 0;
    std::cin >> quantity;
    SuffixAutomation suff_aut(quantity);
    for (int64_t i = 0; i < quantity; ++i) {
        std::cin >> symbol_command;
        if (symbol_command == '+') {
            std::cin >> symbol_str;
            suff_aut.AddChar(symbol_str);
        } else {
            std::cin >> pos;
            if (suff_aut.Find(pos)) {
                std::cout << '+' << '\n';
            } else {
                std::cout << '-' << '\n';
            }
        }
    }
}