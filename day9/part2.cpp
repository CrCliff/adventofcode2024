#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <vector>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

int main()
{
    long sum = 0;

    std::string dense;
    std::getline(std::cin, dense);
    std::stringstream ss(dense);

    std::vector<int> vdense;
    for (auto &c : dense)
        vdense.push_back(std::stoi(std::string(1, c)));

    std::vector<int> vsparse;
    int idx = 0;
    for (int i = 0; i < vdense.size(); i++)
    {
        int c = vdense.at(i);
        if ((i % 2) == 0)
        {
            for (int j = 0; j < c; j++)
                vsparse.push_back(idx);
            idx++;
        }
        else
        {
            for (int j = 0; j < c; j++)
                vsparse.push_back(-1);
        }
    }

    DEBUG(
        for (auto &i : vsparse)
                std::cout
            << i << " ";
        std::cout << std::endl;)

    for (int i = vsparse.size() - 1; i > 0; i--)
    {
        int l = 1;
        int n = vsparse[i];

        if (n == -1)
            continue;

        while (vsparse[i - 1] == n)
        {
            l++;
            i--;
        }

        // Find next open space
        int ospace = -1;
        int ll = 0;
        for (int j = 0; j < i; j++)
        {
            if (vsparse[j] == -1)
                ll++;
            else
                ll = 0;

            if (ll >= l)
            {
                ospace = j - ll + 1;
                break;
            }
        }

        DEBUG(
            std::cout << l << " " << n << " " << ospace << std::endl;)

        // Swap "l" chars to open space
        if (ospace > -1)
            for (int j = 0; j < l; j++)
                std::swap(vsparse[ospace + j], vsparse[i + j]);
    }

    for (int i = 0; i < vsparse.size(); i++)
        if (vsparse[i] != -1)
            sum += i * vsparse[i];

    DEBUG(
        for (auto &i : vsparse)
                std::cout
            << i << " ";
        std::cout << std::endl;)

    // 6636608781232
    std::cout << sum << std::endl;

    return 0;
}
