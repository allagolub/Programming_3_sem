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
    std::string second_str;
    std::string first_str;
    std::cin >> second_str;
    std::cin >> first_str;
    int first_size = first_str.size();
    std::string new_str(first_str+'#'+second_str);
    int new_size = new_str.size();
    std::vector<int> z_function(ZFunction(new_str));
    for (int i = first_size + 1; i < new_size; i++) {
        if (z_function[i] == first_size) {
            std::cout << i - first_size - 1  << '\n';
        }
    }
    return 0;
}