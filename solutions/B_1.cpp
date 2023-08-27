
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string BuildWordPrefix(const std::vector<int>& pf) {
    std::string str("a");
    size_t size = pf.size();
    for (size_t i = 1; i < size; ++i) {
        if (pf[i] != 0) {
            str += str[pf[i] - 1];
        } else {
            char first_letter = 'a';
            int count = pf[i - 1];
            std::vector<bool> used_letters(26,false);
            used_letters[0] = true;
            while (count > 0) {
                used_letters[str[count] - first_letter] = true;
                count = pf[count - 1];
            }
            char min_letter = 'b';
            while (used_letters[min_letter - first_letter]) {
                ++min_letter;
            }
            str += min_letter;
        }
    }
    return str;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    size_t size = 0;
    std::cin >> size;
    if (size != 0) {
        std::vector<int> pf(size);
        for (size_t i = 0; i < size; ++i) {
            std::cin >> pf[i];
        }
        std::cout << BuildWordPrefix(pf);
        return 0;
    }
}
