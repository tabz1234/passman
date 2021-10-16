#ifndef PASSWORD_HPP
#define PASSWORD_HPP

#include "PasswordInfo.hpp"

class Password
{
    std::string str_;
    PasswordInfo info_;

  public:
    Password(const PasswordInfo& info) noexcept;

    std::string str() noexcept;
};

#endif
