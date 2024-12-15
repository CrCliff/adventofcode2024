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

        if (!safe) {
            for (int j = 0; j < report.size(); j++) {
                std::vector<int> cp = report;
                bool nsafe = true;
                cp.erase(cp.begin() + j);

                for (int i = 1; i < cp.size(); i++) {
                    if ((incr && (cp[i] <= cp[i-1]))
                        || (!incr && (cp[i] >= cp[i-1]))
                        || (abs(cp[i] - cp[i-1]) > 3)) {
                        nsafe = false;
                    }
                }

                if (nsafe)
                    safe = nsafe;
            }
        }

        // std::cout << safe << std::endl;
        if (safe)
            sum += 1;
    }

    // 601
    std::cout << sum << std::endl;

    return 0;
}
