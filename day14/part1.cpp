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

    int q0 = 0, q1 = 0, q2 = 0, q3 = 0;
    for (int i = 0; i < pxs.size(); i++)
    {
        const int px_o = pxs[i];
        const int py_o = pys[i];
        const int vx = vxs[i];
        const int vy = vys[i];

        const int px_f = mod(px_o + (100*vx), MX+1);
        const int py_f = mod(py_o + (100*vy), MY+1);

        if (px_f < MX / 2 && py_f < MY / 2)
            q0++;
        else if (px_f < MX / 2 && py_f > MY / 2)
            q1++;
        else if (px_f > MX / 2 && py_f < MY / 2)
            q2++;
        else if (px_f > MX / 2 && py_f > MY / 2)
            q3++;

        DEBUG(std::printf("(%d, %d) -> (%d, %d)\n", px_o, py_o, px_f, py_f));
    }

    DEBUG(std::printf("q0: %d\n", q0));
    DEBUG(std::printf("q1: %d\n", q1));
    DEBUG(std::printf("q2: %d\n", q2));
    DEBUG(std::printf("q3: %d\n", q3));

    // 226179492
    std::cout << q0 * q1 * q2 * q3 << std::endl;

    return 0;
}
