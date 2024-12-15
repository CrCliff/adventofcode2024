#include <iostream>
#include <string>
#include "lib.hpp"

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

    for (int x = 1; x < w-1; x++)
    {
        for (int y = 1; y < h-1; y++)
        {
            const grid g = grid(all_lines, w, h, 3, 3, x, y);
            
            // Now we only check for "X's" on the diagonal axes
            int cmas = 0;

            if (g.centats<UPR>(1, 1, 3) == MAS)
                cmas += 1;
            if (g.centats<UPL>(1, 1, 3) == MAS)
                cmas += 1;
            if (g.centats<DOWNL>(1, 1, 3) == MAS)
                cmas += 1;
            if (g.centats<DOWNR>(1, 1, 3) == MAS)
                cmas += 1;

            if (cmas > 1)
                sum += 1;
        }
    }

    // 1974
    std::cout << sum << std::endl;

    return 0;
}
