#pragma once

#include <string_view>
#include <vector>

struct TerminalPrinter final {

    TerminalPrinter(const std::size_t to_reserve = 8192) noexcept;

    template <typename T, typename... Args>
    void queue(T first, Args... args) noexcept
    {
        queue_T(first);
        queue(args...);
    }

    void flush() noexcept;

    ~TerminalPrinter();

  private:
    std::vector<char> buffer_;

    void queue_T(const std::string_view) noexcept;
    void queue_T(const char) noexcept;
    void queue_T(const int) noexcept = delete;
    void queue() noexcept;
};

extern TerminalPrinter tprinter;
