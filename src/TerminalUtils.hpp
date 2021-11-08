#ifndef TERMINALCOLOR_HPP
#define TERMINALCOLOR_HPP

#include "RGB.hpp"

#include <iostream>
#include <string>

struct FG
{
    RGB rgb_;

    static constexpr auto attr_ = "38";

    constexpr FG(const int red, const int green, const int blue)
      : rgb_{ red, green, blue }
    {}
};
struct BG
{
    RGB rgb_;

    static constexpr auto attr_ = "48";

    constexpr BG(const int red, const int green, const int blue)
      : rgb_{ red, green, blue }
    {}
};

void
set_color(const FG& fg_rgb);
void
set_color(const BG& bg_rgb);

void
reset_all_attributes();

template<FG fg_color>
void
printColorfulText(const std::string& text)
{
    set_color(fg_color);
    std::cout << text;
    reset_all_attributes();
}
template<BG bg_color>
void
printColorfulText(const std::string& text)
{
    set_color(bg_color);
    std::cout << text;
    reset_all_attributes();
}
#endif
