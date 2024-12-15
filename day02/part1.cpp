#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>

constexpr bool DEBUG = false;

int main() {
    int sum = 0;

    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        std::vector<int> report;
        std::istringstream stream(line);
        int n;
        while (stream >> n) {
            report.push_back(n);
        }

        bool incr = report.front() < report.back();
        bool safe = true;

        for (int i = 1; i < report.size(); i++) {
            if ((incr && (report[i] <= report[i-1]))
                || (!incr && (report[i] >= report[i-1]))
                || (abs(report[i] - report[i-1]) > 3)) {
                safe = false;
            }
        }

        // std::cout << safe << std::endl;
        if (safe)
            sum += 1;
    }

    // 559
    std::cout << sum << std::endl;

    return 0;
}
