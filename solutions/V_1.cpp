#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
struct State{
    int64_t len;
    int64_t link;
    int64_t end_pos;
    std::map<char, int64_t> next;
};
class SuffixAutomation {
public:
    std::vector<State> st;
    int64_t size;
    SuffixAutomation (): st(1), size(0), last_(0) {
        st[0].link = -1;
        st[0].len = 0;
        st[0].end_pos = 0;
    }
    int64_t EndPos (int64_t ind) {
        return st[ind].end_pos;
    }
    explicit SuffixAutomation (const std::string& s): st(2 * s.size()), size(0), last_(0) {
        st[0].link = -1;
        st[0].len = 0;
        st[0].end_pos = -1;
        int64_t size_str = s.size();
        for (int64_t i = 0; i < size_str; ++i) {
            AddChar(s[i]);
        }
    }
    void AddChar(char c) {
        int64_t curr = size + 1;
        ++size;
        st[curr].len = st[last_].len + 1;
        st[curr].end_pos = st[last_].end_pos + 1;
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
                st[copy].end_pos = st[q].end_pos;
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
private:
    int64_t last_;
};
struct Node {
    int64_t begin;
    int64_t len;
    std::map<char, int64_t> transitions;
};
class SuffixTree : public SuffixAutomation {
public:
    std::vector<Node> states_tree;
    int64_t size;
    std::string str;
    void ExtractTransitions(SuffixAutomation& sa, int64_t ind) {
        int64_t suffix_ind = sa.st[ind].link;
        states_tree[ind].begin = str.size() - 1 - (sa.st[ind].end_pos - sa.st[suffix_ind].len);
        states_tree[ind].len = sa.st[ind].len - sa.st[suffix_ind].len;
        states_tree[suffix_ind].transitions[str[states_tree[ind].begin]] = ind;
    }
    explicit SuffixTree (const std::string& s) :str(s) {
        std::string new_reverse_str(s);
        std::reverse(new_reverse_str.begin(), new_reverse_str.end());
        SuffixAutomation sa(new_reverse_str);
        size = sa.size;
        states_tree.resize(size + 1);
        states_tree[0].begin = -1;
        states_tree[0].len = 0;
        for (int64_t i = 1; i <= size; i++) {
            ExtractTransitions(sa, i);
        }
    }
};
int main() {
    std::string str;
    std::cin >> str;
    SuffixTree suffix_tree(str + '#');
    std::cout << suffix_tree.size + 1 << '\n';
    for (int64_t i = 0; i <= suffix_tree.size; i++) {
        for (auto it = suffix_tree.states_tree[i].transitions.begin(); it != suffix_tree.states_tree[i].transitions.end(); it++) {
            std::cout << i << ' ' << it->first << ' ' << suffix_tree.states_tree[it->second].len << ' ' << it->second << '\n';
        }
    }

}