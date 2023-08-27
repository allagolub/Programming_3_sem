
#include <iostream>
#include <string>
#include <vector>
std::vector<int> PrefixFunction(const std::string& str) {
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
    return pref;
}
int main() {
    std::string str;
    std::cin >> str;
    int size = str.size();
    std::vector<int> pref(PrefixFunction(str));
    for (int i = 0; i < size; i++) {
        std::cout << pref[i] << ' ';
    }
    return 0;
}