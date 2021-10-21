#ifndef PASSMANFATALERROR_HPP
#define PASSMANFATALERROR_HPP

#include "TerminalColor.hpp"

#include <stdexcept>

class PassmanFatalError : public std::exception
{
    std::string msg_;

  public:
    PassmanFatalError(const std::string& msg) noexcept
      : msg_{ msg }
    {
        msg_ = std::string(FGColor(255, 0, 0)) + msg_ + std::string(FGColor(255, 255, 255));
    }
    const char* what() const noexcept { return msg_.c_str(); }
};

#endif
