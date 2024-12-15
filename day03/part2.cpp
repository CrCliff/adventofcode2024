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
    const std::regex regex("mul\\(([0-9]+),([0-9]+)\\)|do\\(\\)|don't\\(\\)");
    const std::sregex_iterator end;

    int sum = 0;
    bool menabled = true;
    std::string line;

    while (std::getline(std::cin, line) && !line.empty())
    {
        std::sregex_iterator it(line.begin(), line.end(), regex);

        while (it != end)
        {
            const std::smatch match = *(it++);
            const std::string matchs = match.str();

            if (matchs == "don't()")
                menabled = false;
            else if (matchs == "do()")
                menabled = true;
            else
            {
                if (menabled)
                    sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
            }
        }
    }

    // 98729041
    std::cout << sum << std::endl;

    return 0;
}
