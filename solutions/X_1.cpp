#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
struct State{
    int64_t len;
    int64_t link;
    bool is_terminal = false;
    int64_t end_pos;
    std::map<char, int64_t> next;
};
class SuffixAutomation {
    int64_t last_;
public:
    std::vector<State> st;
    std::vector<int64_t> dp;
    int64_t size;
    SuffixAutomation (): last_(0), st(1), dp(1), size(0) {
        st[0].link = -1;
        st[0].len = 0;
        st[0].end_pos = 0;
    }
    int64_t CountPath(int64_t ind) {
        if (dp[ind] > 0) {
            return dp[ind];
        }
        int64_t sum_path = 0;
        if (st[ind].is_terminal) {
            sum_path = 1;
        }
        for (auto it: st[ind].next) {
            sum_path += CountPath(it.second);
        }
        dp[ind] = sum_path;
        return sum_path;
    }
    explicit SuffixAutomation (const std::string& s): last_(0), st(2 * s.size()), dp(2 * s.size()),size(0) {
        st[0].link = -1;
        st[0].len = 0;
        int64_t size_str = s.size();
        for (int64_t i = 0; i < size_str; ++i) {
            AddChar(s[i]);
        }
        AddTerminal(last_);
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
    void AddTerminal(int64_t ind) {
        int64_t curr_link = ind;
        while (curr_link!= 0) {
            st[curr_link].is_terminal = true;
            curr_link = st[curr_link].link;
        }
    }
};
int main() {
    int64_t quantity = 0;
    int64_t max_digit = 0;
    std::cin >> quantity >> max_digit;
    std::string str;
    int64_t digit = 0;
    for (int64_t i = 0; i < quantity; i++) {
        std::cin >> digit;
        str += static_cast<char>(digit % 10);
    }
    SuffixAutomation suff_aut(str);
    suff_aut.CountPath(0);
    int64_t max_refrain = 0;
    int64_t max_len = 0;
    int64_t max_left = 0;
    int64_t max_right = 0;
    for (int64_t i = 1; i <= suff_aut.size; i++) {
        if (suff_aut.st[i].len * suff_aut.dp[i] > max_refrain) {
            max_refrain = suff_aut.st[i].len * suff_aut.dp[i];
            max_len = suff_aut.st[i].len;
            max_left = suff_aut.st[i].end_pos - max_len + 1;
            max_right = suff_aut.st[i].end_pos;
        }
    }
    std:: cout << max_refrain << '\n';
    std:: cout << max_len << '\n';
    for (int64_t i = max_left; i <= max_right; i++) {
        if (static_cast<int>(str[i]) == 0) {
            std::cout << 10 << ' ';
        } else {
            std::cout << static_cast<int>(str[i]) << ' ';
        }
    }
}