#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
int PrefixFunction(const std::string& str) {
    int size_str = str.size();
    std::vector<int> pref(size_str, 0);
    for (int i = 1; i < size_str; ++i) {
        int count = pref[i - 1];
        while ((count > 0) && (str[i] != str[count])) {
            count = pref[count - 1];
        }
        if (str[i] == str[count]) {
            ++count;
        }
        pref[i] = count;
    }
    return pref[size_str - 1];
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int quantity = 0;
    std::cin >> quantity;
    std::string second_str;
    std::string first_str;
    std::cin >> first_str;
    int first_size = 0;
    int second_size = 0;
    std::string new_str_same_part;
    for (int i = 2; i <= quantity; i++) {
        std::cin >> second_str;
        first_size = first_str.size();
        second_size = second_str.size();
        if (first_size > second_size) {
            std::string tmp_first_part(first_str.begin() + first_size - second_size, first_str.end());
            new_str_same_part = second_str + '#' + tmp_first_part;
        } else {
            new_str_same_part = second_str + '#' + first_str;
        }
        int max_len = PrefixFunction(new_str_same_part);
        first_str += second_str.substr(max_len);
    }
    std::cout << first_str;
    return 0;
}