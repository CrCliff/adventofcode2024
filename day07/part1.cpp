#include <iostream>
#include <sstream>
#include <string>
#include <ranges>
#include <algorithm>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

long long eval(const std::vector<int> &ns, const int64_t bits)
{
    long long init = ns[0];
    for (int i = 0; i < ns.size()-1; i++)
    {
        if (bits & (1 << i))
            init *= ns[i+1];
        else
            init += ns[i+1];
    }
    return init;
}

int main()
{
    long long sum = 0;
    std::string line;
    char _c;

    while (std::getline(std::cin, line) && !line.empty())
    {
        std::stringstream ss(line);

        long long total;
        int n;
        std::vector<int> ns;

        ss >> total >> _c;

        while (ss >> n)
            ns.push_back(n);

        const auto is = std::views::iota(0, 1 << (ns.size() - 1));
        const auto evals = is | std::views::transform([ns](int i) { return eval(ns, i); });
        const auto found = std::ranges::find(evals, total);

        if (found != evals.end())
            sum += total;
    }

    // 5540634308362
    std::cout << sum << std::endl;

    return 0;
}
