#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ranges>
#include <regex>

constexpr bool DEBUG = false;

int main()
{
    const std::regex regex("mul\\(([0-9]+),([0-9]+)\\)");
    const std::sregex_iterator end;

    int sum = 0;
    std::string line;

    while (std::getline(std::cin, line) && !line.empty())
    {
        std::sregex_iterator it(line.begin(), line.end(), regex);

        while (it != end)
        {
            const std::smatch match = *(it++);
            sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
        }
    }

    // 181345830
    std::cout << sum << std::endl;

    return 0;
}
