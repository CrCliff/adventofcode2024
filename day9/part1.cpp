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
        std::cout << i << " ";
    std::cout << std::endl;
    )

    int end = vsparse.size() - 1;
    for (int i = 0; i < vsparse.size() && end > i; i++)
    {
        if (vsparse[i] == -1)
        {
            while (vsparse[end] == -1 && end >= 0 && end > i)
                end--;

            if (end < 0 || end <= i)
                break;

            std::swap(vsparse[i], vsparse[end]);
        }

        sum += i * vsparse[i];
    }

    DEBUG(
        for (auto &i : vsparse)
                std::cout
            << i << " ";
        std::cout << std::endl;)

    // 6607511583593
    std::cout << sum << std::endl;

    return 0;
}
