#include "TerminalUtils.hpp"

#include <iostream>

using namespace std::string_literals;

void
set_color(const FG& color) noexcept
{
    std::cout << "\033["s + FG::attr_ + ";2;" +
                   std::to_string(color.rgb_.red_) + ";" +
                   std::to_string(color.rgb_.green_) + ";" +
                   std::to_string(color.rgb_.blue_) + "m";
}
void
set_color(const BG& color) noexcept
{
    std::cout << "\033["s + BG::attr_ + ";2;" +
                   std::to_string(color.rgb_.red_) + ";" +
                   std::to_string(color.rgb_.green_) + ";" +
                   std::to_string(color.rgb_.blue_) + "m";
}
void
reset_all_attributes() noexcept
{
    std::cout << "\033[0m";
}

