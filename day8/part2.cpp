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
                            DEBUG(std::printf("%c -> (%d,%d) and (%d,%d)\n", x, ax, ay, bx, by));
                            const int dx = bx - ax;
                            const int dy = by - ay;

                            // ax, ax-dx, ax-2dx, ...
                            // ay, ay-dy, ay-2dy, ...
                            for (int cx = ax, cy = ay;
                                 0 <= cx && cx < MX && 0 <= cy && cy < MY;
                                 cx -= dx, cy -= dy)
                                G1[cy][cx] = '#';

                            // bx, bx+dx, bx+2dx, ...
                            // by, by+dy, by+2dy, ...
                            for (int cx = bx, cy = by;
                                 0 <= cx && cx < MX && 0 <= cy && cy < MY;
                                 cx += dx, cy += dy)
                                G1[cy][cx] = '#';
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

    // 1235
    std::cout << sum << std::endl;

    return 0;
}
