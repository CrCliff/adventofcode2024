#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <cassert>
#include <stack>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

constexpr int INF = 99;
constexpr int UNDEF = -99;
constexpr int X = 10;
constexpr int Y = 10;

void pprint(char G[Y][X])
{
    for (int y = 0; y < Y; y++)
    {
        for (int x = 0; x < X; x++)
        {
            std::cout << G[y][x];
        }
        std::cout << std::endl;
    }
}

int main()
{
    long sum = 0;
    int px = 0, py = 0;
    int y = 0;
    char G[Y][X];

    for (std::string line; std::getline(std::cin, line) && line.size() > 0;)
    {
        for (int x = 0; x < X; x++)
        {
            G[y][x] = line.at(x);
            if (G[y][x] == '@')
            {
                px = x;
                py = y;
            }
        }
        y++;
    }

    std::string moves;
    for (std::string line; std::getline(std::cin, line);)
        moves.append(line);

    DEBUG(std::cout << moves << std::endl);

    for (auto &c : moves)
    {
        DEBUG(
            std::printf("(%d,%d)\n", px, py);
            pprint(G);)
        G[py][px] = '.';
        int ny = py, nx = px;
        switch (c)
        {
        case '^':
            ny += -1;
            if (G[ny][nx] == 'O')
            {
                int i;
                for (i = 1; G[ny - i][nx] == 'O'; i++)
                {
                }

                if (G[ny - i][nx] == '.')
                {
                    px = nx;
                    py = ny;
                    G[py - i][px] = 'O';
                    G[py][px] = '@';
                }
            }
            break;

        case 'v':
            ny += 1;
            if (G[ny][nx] == 'O')
            {
                int i;
                for (i = 1; G[ny + i][nx] == 'O'; i++)
                {
                }

                if (G[ny + i][nx] == '.')
                {
                    px = nx;
                    py = ny;
                    G[py + i][px] = 'O';
                    G[py][px] = '@';
                }
            }
            break;

        case '<':
            nx += -1;
            if (G[ny][nx] == 'O')
            {
                int i;
                for (i = 1; G[ny][nx - i] == 'O'; i++)
                {
                }

                if (G[ny][nx - i] == '.')
                {
                    px = nx;
                    py = ny;
                    G[py][px - i] = 'O';
                    G[py][px] = '@';
                }
            }
            break;

        case '>':
            nx += 1;
            if (G[ny][nx] == 'O')
            {
                int i;
                for (i = 1; G[ny][nx + i] == 'O'; i++)
                {
                }

                if (G[ny][nx + i] == '.')
                {
                    px = nx;
                    py = ny;
                    G[py][px + i] = 'O';
                    G[py][px] = '@';
                }
            }
            break;

        }

        if (G[ny][nx] == '.')
        {
            px = nx;
            py = ny;
            G[py][px] = '@';
        }
        else if (G[ny][nx] == '#')
        {
            G[py][px] = '@';
        }
    }

    for (int y = 1; y < Y - 1; y++)
    {
        for (int x = 1; x < X - 1; x++)
        {
            if (G[y][x] == 'O')
                sum += (100 * y) + x;
        }
    }

    // 1485257
    std::cout << sum << std::endl;

    return 0;
}
