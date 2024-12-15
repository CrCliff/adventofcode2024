#include <iostream>
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

constexpr int mod(int a, int b)
{
    return ((a % b) + b) % b;
}

int main()
{
    std::vector<int> pxs, pys, vxs, vys;

    for (std::string line; std::getline(std::cin, line);)
    {
        std::stringstream ss(line);
        int px, py, vx, vy;
        ss >> px;
        ss >> py;
        ss >> vx;
        ss >> vy;

        pxs.push_back(px);
        pys.push_back(py);
        vxs.push_back(vx);
        vys.push_back(vy);
    }

    const int MX = *std::max_element(pxs.begin(), pxs.end());
    const int MY = *std::max_element(pys.begin(), pys.end());

    DEBUG(std::printf("MX: %d, MY: %d\n", MX, MY));

    for (int sec = 0; ; sec++)
    {
        std::vector<int> npxs, npys;
        for (int i = 0; i < pxs.size(); i++)
        {
            const int px_o = pxs[i];
            const int py_o = pys[i];
            const int vx = vxs[i];
            const int vy = vys[i];

            const int px_f = mod(px_o + (sec * vx), MX + 1);
            const int py_f = mod(py_o + (sec * vy), MY + 1);
            npxs.push_back(px_f);
            npys.push_back(py_f);
        }

        bool on_same_tile = false;
        for (int i = 0; i < npxs.size() && !on_same_tile; i++)
        {
            for (int j = 0; j < npxs.size() && !on_same_tile; j++)
            {
                // Check for two robots on the same tile
                if (i != j && npxs[i] == npxs[j] && npys[i] == npys[j])
                    on_same_tile = true;
            }
        }

        if (!on_same_tile)
        {
            // 7502
            std::cout << sec << std::endl;
            break;
        }
    }

    return 0;
}
