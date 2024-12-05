#include <iostream>
#include <string>
#include "lib.hpp"

char grid::at(std::string s, const int w, const int h, const int x, const int y) const
{
    const int pos = y * w + x;
    const bool out_of_bounds = x < 0 || y < 0 || x >= w || y >= h;

    if (pos >= s.length() || pos < 0 || out_of_bounds)
        return '0';
    else
        return s.at(pos);
}

template <orientation O>
std::string grid::ats(int x, int y, int l) const
{
    static_assert(-1 <= O.wx <= 1);
    static_assert(-1 <= O.wy <= 1);

    std::string news;

    for (int i = 0; i < l; i++)
        news = news + this->at(this->_s, this->_w, this->_h, x + (O.wx * i), y + (O.wy * i));

    return news;
}

template <orientation O>
std::string grid::centats(int x, int y, int l) const
{
    static_assert(-1 <= O.wx <= 1);
    static_assert(-1 <= O.wy <= 1);

    std::string news;

    for (int i = -(l/2); i <= l/2; i++)
        news = news + this->at(this->_s, 3, 3, x + (O.wx * i), y + (O.wy * i));

    return news;
}

template std::string grid::ats<RIGHT>(int x, int y, int l) const;
template std::string grid::ats<UPR>(int x, int y, int l) const;
template std::string grid::ats<UP>(int x, int y, int l) const;
template std::string grid::ats<UPL>(int x, int y, int l) const;
template std::string grid::ats<LEFT>(int x, int y, int l) const;
template std::string grid::ats<DOWNL>(int x, int y, int l) const;
template std::string grid::ats<DOWN>(int x, int y, int l) const;
template std::string grid::ats<DOWNR>(int x, int y, int l) const;

template std::string grid::centats<RIGHT>(int x, int y, int l) const;
template std::string grid::centats<UPR>(int x, int y, int l) const;
template std::string grid::centats<UP>(int x, int y, int l) const;
template std::string grid::centats<UPL>(int x, int y, int l) const;
template std::string grid::centats<LEFT>(int x, int y, int l) const;
template std::string grid::centats<DOWNL>(int x, int y, int l) const;
template std::string grid::centats<DOWN>(int x, int y, int l) const;
template std::string grid::centats<DOWNR>(int x, int y, int l) const;
