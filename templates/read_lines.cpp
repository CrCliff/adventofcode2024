#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>

constexpr bool DEBUG = false;

int main() {
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        std::istringstream stream(line);
        std::string n1, n2; //...
        stream >> n1 >> n2;
        // Do something;
    }

    return 0;
}
