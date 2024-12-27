#include <iostream>
#include <sstream>
#include <string>
#include <ranges>
#include <algorithm>
#include <numeric>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

constexpr int BLINKS = 25;

template <typename T>
auto readns()
{
    std::string line;
    std::vector<T> ns;

    std::getline(std::cin, line);
    std::stringstream ss(line);

    T n;
    while (ss >> n)
        ns.push_back(n);

    return ns;
}

template <typename T>
std::vector<long> blink(const T &container)
{
    std::vector<long> ns;
    for (const auto n : container)
    {
        const auto s = std::to_string(n);
        const auto l = std::size(s);

        if (n == 0)
        {
            ns.push_back(1);
        }
        else if (l % 2 == 0)
        {
            const auto s0 = std::stol(s.substr(0, l / 2));
            const auto s1 = std::stol(s.substr(l / 2));
            ns.insert(ns.end(), {s0, s1});
        }
        else
        {
            ns.push_back(n * 2024);
        }
    }
    return ns;
}

int main()
{
    auto ns = readns<long>();

    for (auto _ : std::views::iota(0, BLINKS))
        ns = blink(ns);

    // 204022
    std::cout << ns.size() << std::endl;

    return 0;
}
