#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

constexpr int BLINKS = 75;

std::map<std::pair<long, int>, long> MEM;

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

template <int N>
long nstones(const long n)
{
    const auto pr = std::make_pair(n, N);

    if (MEM.contains(pr))
    {
        return MEM[pr];
    }
    else
    {
        const auto s = std::to_string(n);
        const auto l = std::size(s);

        if (n == 0)
        {
            MEM[pr] = nstones<N - 1>(1);
            return MEM[pr];
        }
        else if (l % 2 == 0)
        {
            const auto s0 = std::stol(s.substr(0, l / 2));
            const auto s1 = std::stol(s.substr(l / 2));
            MEM[pr] = nstones<N - 1>(s0) + nstones<N - 1>(s1);
            return MEM[pr];
        }
        else
        {
            MEM[pr] = nstones<N - 1>(n * 2024);
            return MEM[pr];
        }
    }
}

template <>
long nstones<0>(const long n)
{
    return 1;
}

int main()
{
    auto ns = readns<long>();

    std::vector<long> stones(ns.size());
    constexpr auto count_stones = [](long i) {
        return nstones<BLINKS>(i);
    };
    std::transform(ns.cbegin(), ns.cend(), stones.begin(), count_stones);
    const auto sum = std::accumulate(stones.cbegin(), stones.cend(), 0LL);

    // 241651071960597
    std::cout << sum << std::endl;

    return 0;
}
