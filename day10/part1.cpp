#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <cassert>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

constexpr int INF = 99;
constexpr int UNDEF = -99;
constexpr int X = 8;
constexpr int Y = 8;

void dist(int G[X][Y], int DIST[X][Y], int i, int j)
{
    assert(0 <= i && i < Y);
    assert(0 <= j && j < X);

    if (G[i][j] == 9)
        return;

    if (G[i][j] == UNDEF)
    {
        DIST[i][j] = INF;
        return;
    }

    // Up
    if (j - 1 >= 0 && (G[i][j - 1] - G[i][j]) == 1)
    {
        DIST[i][j - 1] = G[i][j - 1];
        dist(G, DIST, i, j - 1);
    }
    // Down
    if (j + 1 < X && (G[i][j + 1] - G[i][j]) == 1)
    {
        DIST[i][j + 1] = G[i][j + 1];
        dist(G, DIST, i, j + 1);
    }
    // Left
    if (i - 1 >= 0 && (G[i - 1][j] - G[i][j]) == 1)
    {
        DIST[i - 1][j] = G[i - 1][j];
        dist(G, DIST, i - 1, j);
    }
    // Right
    if (i + 1 < Y && (G[i + 1][j] - G[i][j]) == 1)
    {
        DIST[i + 1][j] = G[i + 1][j];
        dist(G, DIST, i + 1, j);
    }
}

int main()
{
    long sum = 0;

    int y = 0;
    int G[X][Y];

    for (std::string line; std::getline(std::cin, line);)
    {
        for (int x = 0; x < X; x++)
        {
            if (line.at(x) == '.')
                G[y][x] = UNDEF;
            else
                G[y][x] = std::stoi(std::string(1, line.at(x)));
        }
        y++;
    }

    int DIST[X][Y];
    for (int x = 0; x < Y; x++)
    {
        for (int y = 0; y < X; y++)
        {
            if (G[x][y] == 0)
            {
                std::fill_n(&DIST[0][0], X * Y, UNDEF);
                int score = 0;
                DIST[x][y] = 0;
                dist(G, DIST, x, y);

                for (int i = 0; i < Y; i++)
                    for (int j = 0; j < X; j++)
                        if (DIST[i][j] == 9)
                            score++;
                sum += score;

                DEBUG(
                    std::printf("(%3d, %3d): %d\n", x, y, score);
                    for (int i = 0; i < Y; i++) {
                        for (int j = 0; j < X; j++)
                        {
                            std::printf("%3d ", DIST[i][j]);
                        }
                        std::cout << std::endl;
                    })
            }
        }
    }

    // 535
    std::cout << sum << std::endl;

    return 0;
}
