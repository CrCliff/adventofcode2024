#include <iostream>
#include "lib.hpp"

constexpr bool DEBUG = false;

int main()
{
    int sum = 0, w = 0, h = 0;
    std::string line;
    std::string all_lines;

    while (std::getline(std::cin, line) && !line.empty())
    {
        w = line.length();
        h++;
        all_lines.append(line);
    }

    for (int x = 0; x < w; x++)
    {
        for (int y = 0; y < h; y++)
        {
            const grid g = grid(all_lines, w, h, 7, 7, x, y);

            if (g.ats<RIGHT>(3, 3, 4) == XMAS)
                sum += 1;
            if (g.ats<UPR>(3, 3, 4) == XMAS)
                sum += 1;
            if (g.ats<UP>(3, 3, 4) == XMAS)
                sum += 1;
            if (g.ats<UPL>(3, 3, 4) == XMAS)
                sum += 1;
            if (g.ats<LEFT>(3, 3, 4) == XMAS)
                sum += 1;
            if (g.ats<DOWNL>(3, 3, 4) == XMAS)
                sum += 1;
            if (g.ats<DOWN>(3, 3, 4) == XMAS)
                sum += 1;
            if (g.ats<DOWNR>(3, 3, 4) == XMAS)
                sum += 1;
        }
    }

    // 2642
    std::cout << sum << std::endl;

    return 0;
}
