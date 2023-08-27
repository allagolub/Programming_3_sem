#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int PrefixfFunction(const std::string& str) {
    int size_str = str.size();
    int max_pf = - 1;
    std::vector<int> pf(size_str, 0);
    for (int i = 1; i < size_str; ++i) {
        int count = pf[i - 1];
        while ((count > 0) && (str[i] != str[count])) {
            count = pf[count - 1];
        }
        if (str[i] == str[count]) {
            pf[i] = count + 1;
        }
        if (pf[i] > max_pf) {
            max_pf = pf[i];
        }
    }
    return max_pf;
}

int main() {
    std::string str;
    std::cin >> str;
    int str_size = str.size();
    int unique_words = 1;
    std::string new_str;
    for (int i = 1; i < str_size; ++i) {
        std::string tmp_str(std::make_reverse_iterator(str.begin() + i),str.rend());
        new_str = str[i] + tmp_str;
        int max_pf = PrefixfFunction(new_str);
        unique_words += i + 1 - max_pf;
    }
    std::cout << unique_words;
    return 0;
}
