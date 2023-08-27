#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
std::vector<int64_t> ZFunction(const std::string& str) {
    int64_t size_str = str.size();
    std::vector<int64_t> zf(size_str, 0);
    zf[0] = size_str;
    int64_t left = 0;
    int64_t right = 0;
    for (int64_t i = 1; i < size_str; ++i) {
        if (std::min(right - i, zf[i - left]) > 0) {
            zf[i] = std::min(right - i, zf[i - left]);
        }
        while ((i + zf[i] < size_str) && (str[zf[i]]== str[i + zf[i]])) {
            ++zf[i];
        }
        if (i + zf[i] > right) {
            right = i + zf[i];
            left = i;
        }
    }
    return zf;
}
int main() {
    std::string first_word;
    std::string second_word;
    std::cin >> first_word >> second_word;
    bool correct_word = false;
    std::vector<int64_t> zf(ZFunction(first_word + '#' + second_word));
    int64_t size = first_word.size() + 1 + second_word.size();
    int64_t first_size = first_word.size() + 1;
    int64_t second_size = second_word.size();
    int64_t max_ind_pos = first_size;
    int64_t quantity_words = 0;
    std::vector<int64_t> ind_pos_pref(second_size);
    if (zf[first_size] != 0) {
        for (int64_t i = first_size; i < size; i++) {
            if ((i >= max_ind_pos) && (zf[i] == 0)) {
                correct_word = true;
                break;
            }
            if (max_ind_pos <= zf[i] + i) {
                max_ind_pos = zf[i] + i;
                ind_pos_pref[quantity_words] = i;
                ++quantity_words;
            }
        }
    } else {
        correct_word = true;
    }
    if (correct_word) {
        std::cout << "Yes";
    } else {
        std::cout << "No" << '\n';
        int64_t new_pos = ind_pos_pref[1] - first_size;
        int64_t last_pos = 0;
        for (int64_t i = 1; i < quantity_words; i++) {
            for(int64_t j = last_pos; j < new_pos; j++) {
                std::cout << second_word[j];
            }
            std:: cout << ' ';
            last_pos = new_pos;
            new_pos = ind_pos_pref[(i + 1) % second_size] - first_size;
        }
        for(int64_t j = last_pos; j < second_size; j++) {
            std::cout << second_word[j];
        }

    }
    return 0;
}

