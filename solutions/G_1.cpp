#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
std::vector<int> ZFunction(const std::string& str) {
    int size_str = str.size();
    std::vector<int> zf(size_str, 0);
    zf[0] = size_str;
    int left = 0;
    int right = 0;
    for (int i = 1; i < size_str; ++i) {
        zf[i] = std::max(0, std::min(right - i, zf[i - left]));
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
    int size = 0;
    std::cin >> size;
    std::string second_str;
    std::string first_str;
    std::cin >> first_str;
    std::cin >> second_str;
    int first_size = first_str.size();
    int quantity_ans = 0;
    char num = '0';
    bool is_zero = false;
    int new_size = 3 * first_size + 2;
    for (int j = 0; j < 2; j++) {
        std::string new_first(first_str + '#' + second_str + num + second_str);
        std::vector<int> z_function(ZFunction(new_first));
        for (int i = first_size + 1; i < new_size; i++) {
            if (z_function[i] == first_size) {
                if (num == '1') {
                    quantity_ans++;
                } else if (num == '0') {
                    quantity_ans++;
                    is_zero = true;
                }
                break;
            }
        }
        num++;
    }
    if (quantity_ans == 2) {
        std::cout << "Random";
    } else if (is_zero) {
        std::cout << "No";
    } else {
        std::cout << "Yes";
    }
    return 0;
}
