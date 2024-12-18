#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <cassert>
#include <queue>
#include <vector>
#include <memory>

const char *DEBUG_ENV = std::getenv("DEBUG");
const bool _DEBUG = (DEBUG_ENV && DEBUG_ENV[0] == '1');
#define DEBUG(x) \
    if (_DEBUG)  \
    {            \
        x;       \
    }

constexpr int X = 7;
constexpr int Y = 7;
constexpr int STEPS = 12;

struct point
{
    int x;
    int y;
    bool head;
    std::shared_ptr<point> parent;
};

inline bool bounds(std::shared_ptr<point> &p)
{
    return (p->x >= 0 && p->x < X && p->y >= 0 && p->y < Y);
}

void pprint(std::shared_ptr<point> &p)
{
    if (!p->head)
        std::printf("(%d, %d) FROM (%d, %d)\n", p->x, p->y, p->parent->x, p->parent->y);
    else
        std::printf("(%d, %d)\n", p->x, p->y);
}

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
    char G[Y][X];
    std::vector<int> xs, ys;

    std::fill_n(&G[0][0], X * Y, '.');

    for (std::string line; std::getline(std::cin, line) && line.size() > 0;)
    {
        std::stringstream ss(line);

        int a, b;
        char _c;

        ss >> a;
        ss >> _c >> b;

        DEBUG(std::printf("(%d,%d)\n", a, b));
        xs.push_back(a);
        ys.push_back(b);
    }

    for (int i = 0; i < STEPS; i++)
    {
        int x = xs.at(i), y = ys.at(i);
        G[y][x] = '#';
    }

    DEBUG(
        pprint(G);
        std::cout << std::endl;)

    std::shared_ptr<point> fin;
    bool EXPL[Y][X];
    std::queue<std::shared_ptr<point>> Q;

    EXPL[0][0] = true;
    std::fill_n(&EXPL[0][0], X * Y, false);
    Q.push(std::make_shared<point>(0, 0, true));

    while (!Q.empty())
    {
        auto p = Q.front();
        Q.pop();

        if (p->x == (X - 1) && p->y == (Y - 1))
        {
            fin = p;
            break;
        }

        // Up
        {
            auto w = std::make_shared<point>(p->x, p->y - 1, false, p);
            if (bounds(w) && !EXPL[w->y][w->x] && G[w->y][w->x] != '#')
            {
                EXPL[w->y][w->x] = true;
                Q.push(w);
            }
        }
        // Down
        {
            auto w = std::make_shared<point>(p->x, p->y + 1, false, p);
            if (bounds(w) && !EXPL[w->y][w->x] && G[w->y][w->x] != '#')
            {
                EXPL[w->y][w->x] = true;
                Q.push(w);
            }
        }
        // Left
        {
            auto w = std::make_shared<point>(p->x - 1, p->y, false, p);
            if (bounds(w) && !EXPL[w->y][w->x] && G[w->y][w->x] != '#')
            {
                EXPL[w->y][w->x] = true;
                Q.push(w);
            }
        }
        // Right
        {
            auto w = std::make_shared<point>(p->x + 1, p->y, false, p);
            if (bounds(w) && !EXPL[w->y][w->x] && G[w->y][w->x] != '#')
            {
                EXPL[w->y][w->x] = true;
                Q.push(w);
            }
        }
    }

    while (fin)
    {
        G[fin->y][fin->x] = 'O';
        fin = fin->parent;
    }

    if (fin && fin->head)
        G[fin->y][fin->x] = 'O';

    DEBUG(pprint(G));

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            if (G[y][x] == 'O')
                sum += 1;

    // 1485257
    std::cout << sum - 1 << std::endl;

    return 0;
}
