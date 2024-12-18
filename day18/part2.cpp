#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <cassert>
#include <queue>
#include <vector>
#include <memory>
#include <thread>
#include <atomic>
#include <cmath>

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
constexpr int THREADS = 2;

struct point
{
    int x;
    int y;
    bool head;
    std::shared_ptr<point> parent;
};

std::pair<int, point> RESULT[THREADS];

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

void bfs(const char G0[Y][X], const std::vector<int> &xs, const std::vector<int> &ys, const int s, const int e, const int slstart, const int slend, const int n)
{
    char G[Y][X];

    std::copy(&G0[0][0], &G0[0][0] + (X * Y), &G[0][0]);

    DEBUG(std::printf("%d %d %d %d\n", s, e, slstart, slend));

    for (int i = s; i < slstart; i++)
    {
        int x = xs.at(i), y = ys.at(i);
        G[y][x] = '#';
    }

    for (int i = slstart; i < slend; i++)
    {
        std::shared_ptr<point> fin;
        bool EXPL[Y][X];
        std::queue<std::shared_ptr<point>> Q;

        int x = xs.at(i), y = ys.at(i);

        G[y][x] = '#';
        std::fill_n(&EXPL[0][0], X * Y, false);
        EXPL[0][0] = true;
        Q.push(std::make_shared<point>(0, 0, true));

        DEBUG(std::printf("(%d,%d)\n", x, y));

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

        if (!fin)
        {
            DEBUG(pprint(G));
            RESULT[n] = std::make_pair(i, point{x, y, false});
            break;
        }

        while (fin)
        {
            G[fin->y][fin->x] = 'O';
            fin = fin->parent;
        }

        if (fin && fin->head)
            G[fin->y][fin->x] = 'O';

        DEBUG(pprint(G));
        // Reset
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                if (G[y][x] == 'X')
                    G[y][x] == '.';
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

    for (int i = 0; i < STEPS + 1; i++)
    {
        int x = xs.at(i), y = ys.at(i);
        G[y][x] = '#';
    }
    DEBUG(
        pprint(G);
        std::cout << std::endl;)

    // Split remaining steps into count THREADS slices and search for first
    // "byte" which we can't find a path through.
    std::vector<std::thread> threads;
    const int slice = std::ceil((static_cast<double>(xs.size()) - STEPS - 1) / THREADS);
    for (int i = 0; i < THREADS; i++)
    {
        const int slstart = std::min(static_cast<int>(xs.size()), STEPS + 1 + i * slice);
        const int slend = std::min(static_cast<int>(xs.size()), STEPS + 1 + i * slice + slice);

        threads.push_back(
            std::thread(bfs, G, xs, ys, STEPS + 1, xs.size(), slstart, slend, i));
    }

    for (auto &t : threads)
        t.join();

    // Find the minimum "byte" index from all threads.
    // This index is our result.
    point mnp;
    int mn = std::numeric_limits<int>::max();
    for (auto &result : RESULT)
    {
        int i = result.first;
        point p = result.second;

        if (i > STEPS && i < mn)
        {
            mn = i;
            mnp = p;
        }
    }

    DEBUG(std::printf("%d -> (%d,%d)\n", mn, mnp.x, mnp.y));
    std::printf("%d,%d\n", mnp.x, mnp.y);

    return 0;
}
