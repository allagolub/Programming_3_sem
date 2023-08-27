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
    std::string str;
    std::cin >> str;
    int size = str.size();
    std::vector<int> pref(ZFunction(str));
    for (int i = 0; i < size; i++) {
        std::cout << pref[i] << ' ';
    }
    return 0;
}
