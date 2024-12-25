#include <iostream>
#include <sstream>
#include <string>
#include <ranges>
#include <algorithm>
#include <cmath>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

std::string b3(int i)
{
    std::string b;
    if (i == 0)
        b = "0";

    while (i > 0)
    {
        b += std::to_string(i % 3);
        i /= 3;
    }

    if (b.length() < 64)
    {
        for (int i = b.length(); i < 64; i++)
            b += '0';
    }
    return b;
}

long long eval(const std::vector<int> &ns, const std::string base3)
{
    long long init = ns[0];
    for (int i = 0; i < ns.size() - 1; i++)
    {
        const char &c = base3[i];
        switch (c)
        {
            case '0': // ||
                init = std::stoll(std::to_string(init) + std::to_string(ns[i+1]));
                break;
            case '1': // +
                init += ns[i+1];
                break;
            case '2': // *
                init *= ns[i+1];
                break;
        }
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
        DEBUG(std::cout << total << std::endl);

        while (ss >> n)
            ns.push_back(n);

        const auto is = std::views::iota(0, pow(3, ns.size() - 1));
        const auto evals = is | std::views::transform([ns](int i) { return eval(ns, b3(i)); });
        const auto found = std::ranges::find(evals, total);

        if (found != evals.end())
            sum += total;
    }

    // 472290821152397
    std::cout << sum << std::endl;

    return 0;
}
