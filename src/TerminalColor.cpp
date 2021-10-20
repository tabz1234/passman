#include "TerminalColor.hpp"

std::ostream&
operator<<(std::ostream& os, const TerminalColor& obj)
{
    os << obj.esc_seq_;
    return os;
}

TerminalColor::TerminalColor(const RGB& rgb) noexcept
  : rgb_{ rgb }
{
    esc_seq_ =
      "\033[__;2;" + std::to_string(rgb_.red_) + ";" + std::to_string(rgb_.green_) + ";" + std::to_string(rgb_.blue_) + "m";
}

FGColor::FGColor(const int r, const int g, const int b) noexcept
  : TerminalColor({ r, g, b })
{
    esc_seq_.replace(2, 2, attr_);
}
BGColor::BGColor(const int r, const int g, const int b) noexcept
  : TerminalColor({ r, g, b })
{
    esc_seq_.replace(2, 2, attr_);
}
