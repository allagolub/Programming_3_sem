#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
std::vector<int> PalindromeFunction(const std::vector<int>& num) {
    int size_str = num.size();
    std::vector<int> pl(size_str, 0);
    int left = 0;
    int right = 0;
    for (int i = 1; i < size_str; ++i) {
        if (i <= right) {
            pl[i] = std::max(0, std::min(right - i + 1, pl[right - i + 1 + left]));
        }
        while ((i + pl[i] < size_str) && (i - pl[i] - 1 >= 0) && (num[i + pl[i]]== num[i - pl[i] - 1])) {
            ++pl[i];
        }
        if (i + pl[i] - 1 > right) {
            right = i + pl[i] - 1;
            left = i - pl[i];
        }
    }
    return pl;
}
int main() {
    int quantity = 0;
    int num_colors = 0;
    std::cin >> quantity >> num_colors;
    std::vector<int> cubes(quantity);
    for (int i = 0; i < quantity; ++i) {
        std::cin >> cubes[i];
    }
    std::vector<int> pl(PalindromeFunction(cubes));
    for (int i = quantity - 1; i >= 0; --i) {
        if (pl[i] - i == 0) {
            std::cout << quantity - pl[i] << ' ';
        }
    }
    return 0;
}
