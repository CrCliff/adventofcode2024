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
    const std::regex regex("([0-9]+)\\|([0-9]+)");
    int sum = 0;
    std::string line;
    std::unordered_map<int, std::vector<int>> ordering_rules;

    while (std::getline(std::cin, line) && !line.empty())
    {
        std::sregex_iterator end;
        std::sregex_iterator it(line.begin(), line.end(), regex);

        while (it != end)
        {
            const std::smatch match = *(it++);

            const int m1 = std::stoi(match[1].str());
            const int m2 = std::stoi(match[2].str());
            const auto it = ordering_rules.find(m1);

            if (it != ordering_rules.end())
            {
                auto &v = it->second;
                v.push_back(m2);
            }
            else
            {
                std::vector<int> v{m2};
                ordering_rules[m1] = v;
            }
        }
    }

    while (std::getline(std::cin, line) && !line.empty())
    {
        std::vector<int> ns;
        std::stringstream ss(line);
        std::string tmp;

        while (std::getline(ss, tmp, ','))
            ns.push_back(std::stoi(tmp));

        std::vector<int> cp = ns;

        // Sort updates according to ordering rules
        std::sort(cp.begin(), cp.end(), [&ordering_rules](const int n1, const int n2) {
            const auto it = ordering_rules.find(n1);
            if (it != ordering_rules.end())
            {
                auto &v = it->second;
                auto itv = std::find(v.begin(), v.end(), n2);

                if (itv != v.end())
                    return true;
            }

            return false;
        });

        if (ns == cp)
            sum += ns[ns.size() / 2];
    }

    // 5166
    std::cout << sum << std::endl;

    return 0;
}
