#include <iostream>
#include <cstring>
#include <string>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

// constexpr int MX = 12;
// constexpr int MY = 12;

constexpr int MX = 50;
constexpr int MY = 50;

int main()
{
    int sum = 0;
    int y = 0;
    char G[MX][MY];
    char G1[MX][MY];
    memset(G1, '.', sizeof(G1));

    for (std::string line; std::getline(std::cin, line);)
    {
        for (int x = 0; x < MX; x++)
            G[y][x] = line.at(x);
        y++;
    }

    for (int ay = 0; ay < MY; ay++)
    {
        for (int ax = 0; ax < MX; ax++)
        {
            const char x = G[ay][ax];
            if (x != '.')
            {
                for (int by = ay; by < MY; by++)
                {
                    for (int bx = (by == ay ? ax + 1 : 0); bx < MX; bx++)
                    {
                        const char y = G[by][bx];

                        if (x == y)
                        {
                            const int dx = bx - ax;
                            const int dy = by - ay;
                            DEBUG(std::printf("%c -> (%d,%d) and (%d,%d)\n", x, ax, ay, bx, by));

                            // (ax - dx, ay - dy)
                            if (ax - dx >= 0 && ay - dy >= 0 && ax - dx < MX && ay - dy < MY)
                                G1[ay - dy][ax - dx] = '#';
                            // (bx + dx, by + dy)
                            if (bx + dx >= 0 && by + dy >= 0 && bx + dx < MX && by + dy < MY)
                                G1[by + dy][bx + dx] = '#';
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < MY; i++)
    {
        for (int j = 0; j < MX; j++)
        {
            DEBUG(std::cout << G1[i][j]);
            if (G1[i][j] == '#')
                sum += 1;
        }
        DEBUG(std::cout << std::endl);
    }

    // 392
    std::cout << sum << std::endl;

    return 0;
}
