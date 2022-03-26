#include "TerminalPrinter.hpp"

extern "C" {
#include <unistd.h>
}

TerminalPrinter tprinter{};

TerminalPrinter::TerminalPrinter(const std::size_t to_reserve) noexcept
{
    buffer_.reserve(to_reserve);
}
void TerminalPrinter::flush() noexcept
{
    write(STDOUT_FILENO, buffer_.data(), buffer_.size());
    buffer_.clear();
}

void TerminalPrinter::queue_T(const std::string_view sv) noexcept
{
    buffer_.insert(buffer_.begin() + buffer_.size(), sv.begin(), sv.end());
}
void TerminalPrinter::queue_T(const char ch) noexcept
{
    buffer_.emplace_back(ch);
}
void TerminalPrinter::queue() noexcept
{
}

TerminalPrinter::~TerminalPrinter()
{
    flush();
}
