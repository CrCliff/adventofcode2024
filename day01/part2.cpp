#include <algorithm>
#include <numeric>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr bool DEBUG = false;

int main() {
    std::vector<int> leftns, rightns;

    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        std::istringstream stream(line);
        int nl, nr;
        stream >> nl >> nr;
        leftns.push_back(nl);
        rightns.push_back(nr);
    }

    std::sort(rightns.begin(), rightns.end(), std::greater<int>());

    // Initialize lookup table with all counts 0..max(rightns)
    std::unordered_map<int, int> count;
    for (int i = 0; i < rightns.front(); i++) {
        count[i] = 0;
    }

    for (auto& n : rightns) {
        count[n] += 1;
    }

    // Calculate similarity score from lookup table
    std::transform(leftns.begin(), leftns.end(), leftns.begin(),
            [&count](int n) { return (n * count[n]); } );
    const int sim_score = std::reduce(leftns.begin(), leftns.end(), 0);

    // 24931009
    std::cout << sim_score << std::endl;

    return 0;
}
