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

constexpr int X = 20;
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
        int x = 0;
        for (auto &c : line)
        {
            switch (c)
            {
            case 'O':
                G[y][x] = '[';
                G[y][x + 1] = ']';
                break;
            case '@':
                G[y][x] = '@';
                G[y][x + 1] = '.';
                py = y;
                px = x;
                break;
            default:
                G[y][x] = c;
                G[y][x + 1] = c;
                break;
            }
            x += 2;
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
        int ny = py, nx = px;
        switch (c)
        {
        case '^':
            ny += -1;
            if (G[ny][nx] == '[' || G[ny][nx] == ']')
            {
                std::stack<std::pair<int, int>> stk;
                std::stack<std::pair<int, int>> s0;
                auto init = G[ny][nx] == '['
                        ? std::make_pair(nx, ny)
                        : std::make_pair(nx - 1, ny);
                s0.push(init);
                stk.push(init);

                bool can_push = true;
                while (!stk.empty() && can_push)
                {
                    const auto &p = stk.top();
                    stk.pop();

                    const int x = p.first;
                    const int y = p.second;

                    if (G[y - 1][x] == '#' || G[y - 1][x + 1] == '#')
                        can_push = false;

                    if (G[y - 1][x] == '[')
                    {
                        stk.push(std::make_pair(x, y - 1));
                        s0.push(std::make_pair(x, y - 1));
                    }
                    if (G[y - 1][x - 1] == '[')
                    {
                        stk.push(std::make_pair(x - 1, y - 1));
                        s0.push(std::make_pair(x - 1, y - 1));
                    }
                    if (G[y - 1][x + 1] == '[')
                    {
                        stk.push(std::make_pair(x + 1, y - 1));
                        s0.push(std::make_pair(x + 1, y - 1));
                    }
                }

                if (can_push)
                {
                    while (!s0.empty())
                    {
                        const auto &p = s0.top();
                        s0.pop();

                        const int x = p.first;
                        const int y = p.second;

                        G[y][x] = '.';
                        G[y][x + 1] = '.';
                        G[y - 1][x] = '[';
                        G[y - 1][x + 1] = ']';
                    }

                    px = nx;
                    py = ny;
                    G[py][px] = '@';
                    G[py + 1][px] = '.';
                }
            }
            break;

        case 'v':
            ny += 1;
            if (G[ny][nx] == '[' || G[ny][nx] == ']')
            {
                std::stack<std::pair<int, int>> stk;
                std::stack<std::pair<int, int>> s0;
                auto init = G[ny][nx] == '['
                        ? std::make_pair(nx, ny)
                        : std::make_pair(nx - 1, ny);
                s0.push(init);
                stk.push(init);

                bool can_push = true;
                while (!stk.empty() && can_push)
                {
                    const auto &p = stk.top();
                    stk.pop();

                    const int x = p.first;
                    const int y = p.second;

                    if (G[y + 1][x] == '#' || G[y + 1][x + 1] == '#')
                        can_push = false;

                    if (G[y + 1][x] == '[')
                    {
                        stk.push(std::make_pair(x, y + 1));
                        s0.push(std::make_pair(x, y + 1));
                    }
                    if (G[y + 1][x - 1] == '[')
                    {
                        stk.push(std::make_pair(x - 1, y + 1));
                        s0.push(std::make_pair(x - 1, y + 1));
                    }
                    if (G[y + 1][x + 1] == '[')
                    {
                        stk.push(std::make_pair(x + 1, y + 1));
                        s0.push(std::make_pair(x + 1, y + 1));
                    }
                }

                if (can_push)
                {
                    while (!s0.empty())
                    {
                        const auto &p = s0.top();
                        s0.pop();

                        const int x = p.first;
                        const int y = p.second;

                        G[y][x] = '.';
                        G[y][x + 1] = '.';
                        G[y + 1][x] = '[';
                        G[y + 1][x + 1] = ']';
                    }

                    px = nx;
                    py = ny;
                    G[py][px] = '@';
                    G[py - 1][px] = '.';
                }
            }
            break;

        case '<':
            nx += -1;
            if (G[ny][nx] == ']')
            {
                int i;
                for (i = 2; G[ny][nx - i] == ']'; i += 2)
                {
                }

                if (G[ny][nx - i] == '.')
                {
                    px = nx;
                    py = ny;

                    for (int j = 1; j < i; j += 2)
                    {
                        G[py][px - j] = ']';
                        G[py][px - j - 1] = '[';
                    }

                    G[py][px] = '@';
                    G[py][px + 1] = '.';
                }
            }
            break;

        case '>':
            nx += 1;
            if (G[ny][nx] == '[')
            {
                int i;
                for (i = 2; G[ny][nx + i] == '['; i += 2)
                {
                }

                if (G[ny][nx + i] == '.')
                {
                    px = nx;
                    py = ny;

                    for (int j = 1; j < i; j += 2)
                    {
                        G[py][px + j] = '[';
                        G[py][px + j + 1] = ']';
                    }

                    G[py][px] = '@';
                    G[py][px - 1] = '.';
                }
            }
            break;

        }

        if (G[ny][nx] == '.')
        {
            G[py][px] = '.';
            px = nx;
            py = ny;
            G[py][px] = '@';
        }
        else if (G[ny][nx] == '#')
        {
            G[py][px] = '@';
        }
    }
    DEBUG(pprint(G));

    for (int y = 1; y < Y - 1; y++)
    {
        for (int x = 1; x < X - 1; x++)
        {
            if (G[y][x] == '[')
                sum += (100 * y) + x;
        }
    }

    // 1475512
    std::cout << sum << std::endl;

    return 0;
}
