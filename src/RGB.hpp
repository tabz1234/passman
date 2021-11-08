#ifndef RGB_HPP
#define RGB_HPP

struct RGB
{
    int red_;
    int green_;
    int blue_;

    constexpr RGB(const int red, const int green, const int blue)
      : red_{ red }
      , green_{ green }
      , blue_{ blue }
    {}

    constexpr virtual ~RGB() = default;
};

#endif
