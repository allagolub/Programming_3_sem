#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
struct State{
    int64_t len;
    int64_t link;
    std::map<char, int64_t> next;
};
class SuffixAutomation {
    int64_t last_;
public:
    std::vector<State> st;
    int64_t size;
    SuffixAutomation (): last_(0), st(1), size(0) {
        st[0].link = -1;
        st[0].len = 0;
    }
    explicit SuffixAutomation (const std::string& s): last_(0), st(2 * s.size()), size(0) {
        st[0].link = -1;
        st[0].len = 0;
        int64_t size_str = s.size();
        for (int64_t i = 0; i < size_str; ++i) {
            AddChar(s[i]);
        }
    }
    void AddChar(char c) {
        int64_t curr = size + 1;
        ++size;
        st[curr].len = st[last_].len + 1;
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
                for (; p != -1 && st[p].next[c] == q; p = st[p].link) {
                    st[p].next[c] = copy;
                }
                st[q].link = copy;
                st[curr].link = copy;
            }
        }
        last_ = curr;
    }
};
int main() {
    std::string str;
    std::cin >> str;
    SuffixAutomation suff_aut(str);
    std::cout << suff_aut.size + 1 << '\n';
    for (int64_t i = 0; i <= suff_aut.size; i++) {
        for (auto it = suff_aut.st[i].next.begin(); it != suff_aut.st[i].next.end(); it++) {
            std::cout << i << ' ' << it->first << ' ' << it->second << '\n';
        }
    }
}