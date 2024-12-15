#include <string>
#include <array>

struct orientation
{
    const int wx;
    const int wy;
};

constexpr const char* XMAS = "XMAS";
constexpr const char* MAS = "MAS";

constexpr orientation RIGHT = orientation{wx : 1, wy : 0};
constexpr orientation UPR = orientation{wx : 1, wy : -1};
constexpr orientation UP = orientation{wx : 0, wy : -1};
constexpr orientation UPL = orientation{wx : -1, wy : -1};
constexpr orientation LEFT = orientation{wx : -1, wy : 0};
constexpr orientation DOWNL = orientation{wx : -1, wy : 1};
constexpr orientation DOWN = orientation{wx : 0, wy : 1};
constexpr orientation DOWNR = orientation{wx : 1, wy : 1};

class grid
{

public:
    grid(const std::string s,
         const int gw,
         const int gh,
         const int w,
         const int h,
         const int x,
         const int y) : _w(w),
                        _h(h)
    {
        std::string news;

        for (int j = -(h/2); j <= (h/2); j++)
            for (int i = -(w/2); i <= (w/2); i++)
                news = news + this->at(s, gw, gh, x + i, y + j);

        this->_s = news;
    }

    char at(const std::string s, const int w, const int h, const int x, const int y) const;

    template <orientation O>
    std::string ats(int x, int y, int l) const;

    template <orientation O>
    std::string centats(int x, int y, int l) const;


private:
    std::string _s;
    const int _w;
    const int _h;
};
