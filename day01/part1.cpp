#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>

constexpr bool DEBUG = false;

int main() {
    std::vector<int> leftns, rightns;
    int sum = 0;

    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        std::istringstream stream(line);
        int nl, nr;
        stream >> nl >> nr;
        leftns.push_back(nl);
        rightns.push_back(nr);
    }

    std::sort(leftns.begin(), leftns.end());
    std::sort(rightns.begin(), rightns.end());

    auto il = leftns.begin(), ir = rightns.begin();
    while (il != rightns.end() && ir != rightns.end()) {
        sum += abs(*(il++) - *(ir++));
    }

    // 2066446
    std::cout << sum << std::endl;
    return 0;
}
