#include "println.hpp"

#include <cstdio>

void Passman::println(const std::string_view msg) noexcept
{
    printf("=== %s\n", msg.data());
}
