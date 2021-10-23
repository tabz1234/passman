#ifndef TERMINALCOLOR_HPP
#define TERMINALCOLOR_HPP

#include <iostream>
#include <string>

struct RGB
{
    int red_;
    int green_;
    int blue_;
};
struct FG
{
    RGB rgb_;

    static constexpr auto attr_ = "38";

    constexpr FG(const int red, const int green, const int blue) noexcept
      : rgb_{ red, green, blue }
    {}
};
struct BG
{
    RGB rgb_;

    static constexpr auto attr_ = "48";

    constexpr BG(const int red, const int green, const int blue) noexcept
      : rgb_{ red, green, blue }
    {}
};

void
set_color(const FG& fg_rgb) noexcept;
void
set_color(const BG& bg_rgb) noexcept;

void
reset_all_attributes() noexcept;

template<FG fg_color>
void
ColorfulText(const std::string& text) noexcept
{
    set_color(fg_color);
    std::cout << text;
    reset_all_attributes();
}
template<BG bg_color>
void
ColorfulText(const std::string& text) noexcept
{
    set_color(bg_color);
    std::cout << text;
    reset_all_attributes();
}
#endif
